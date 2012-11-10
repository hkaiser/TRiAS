// Eine ListViewCtrl, das alle Identifikator/Objekttypen der Datenbasis enthält 
// File: SELIDLVC.CXX

#include "trias03p.hxx"
#include "trias03.h"		// ResourceKonstanten

#include <funcs03.h>
#include <selidlvc.hxx>
#include <eieruhr.hxx>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
//
extern char g_pDLLName[_MAX_PATH];

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CSelIdentListView::CSelIdentListView (
	pDialogWindow pW, ResID uiRes, CSelIdentListViewWindow *pControlWnd)
	       : CListViewCtrl (pW, uiRes), m_pControlWnd (pControlWnd),
		     m_iOTypes(0), m_iMode(0), m_pFcnOvl(NULL), m_pFcnCmp(NULL), m_dwData(0),
			 m_pFcnAdd(NULL)
{
	m_pBuff = NULL;
	m_lLastIdent = 0L;
	m_iLastTypes = 0;
	m_iCurrItem = 0;
	m_fInitialized = false;
}

CSelIdentListView::~CSelIdentListView (void)
{
	DELETE_OBJ (m_pBuff);

	if (!(m_iMode & SELIDMODE_NOICONS)) {
	// ImageList wird vom Destruktor ~CImageList freigegeben, hier 
	// doppeltes Freigeben verhindern
	CImageList *pIL = SetImageList (NULL, LVSIL_SMALL);

		if (pIL) delete pIL;
	}
}

///////////////////////////////////////////////////////////////////////////////
// RückrufFunktionen
typedef struct tagFILLIDENTDATA {
	CListViewCtrl *m_pLV;
	char *m_pOutBuff;
	int m_iCnt;
	int m_iMode;
	DWORD m_iOTypes;
	SELIDOVLPROC m_pFcnOvl;
	ADDENTRYPROC m_pFcnAdd;
	DWORD m_dwData;
} FILLIDENTDATA;

static 
void AddTypeString (FILLIDENTDATA *pFI, long lIdent, char *pKText, int iOTypes, int iImage, int iOvl, int iMode)
{
#if defined(_DEBUG)
	TX_ASSERT(NULL != pFI);
	TX_ASSERT(NULL != pFI -> m_pOutBuff);
	if (!(iMode & SELIDMODE_NOICONS)) 
		TX_ASSERT(IMAGEOVL_FIRST <= iOvl && IMAGEOVL_LAST >= iOvl);
#endif // _DEBUG

// in der ersten Spalte steht der Ident selbst
	ClassFromIdent (lIdent, pFI -> m_pOutBuff);

LV_ITEM lvi;
int iItem = -1;

	memset (&lvi, 0, sizeof(LV_ITEM));
	if (iMode & SELIDMODE_NOICONS) {
		lvi.mask = LVIF_TEXT|LVIF_PARAM;
		lvi.iItem = pFI -> m_iCnt++;
		lvi.iSubItem = GetColIndex (IDENT_COLUMN, iMode);
		lvi.pszText = pFI -> m_pOutBuff;
		lvi.lParam = reinterpret_cast<DWORD>(new CSelIdentItem (static_cast<ULONG>(lIdent), iOTypes));

		iItem = pFI -> m_pLV -> InsertItem (&lvi);
	} else {
	// Bildchen jetzt in separater Spalte
		lvi.mask = LVIF_IMAGE|LVIF_PARAM|LVIF_STATE;
		lvi.iItem = pFI -> m_iCnt++;
		lvi.iSubItem = PICTURE_COLUMN;
		lvi.iImage = iImage;
		lvi.lParam = reinterpret_cast<DWORD>(new CSelIdentItem (static_cast<ULONG>(lIdent), iOTypes));
		lvi.stateMask = LVIS_OVERLAYMASK;
		lvi.state = INDEXTOOVERLAYMASK(iOvl);

		iItem = pFI -> m_pLV -> InsertItem (&lvi);
		if (-1 != iItem) {
			memset (&lvi, 0, sizeof(LV_ITEM));
			lvi.mask = LVIF_TEXT;
			lvi.pszText = pFI -> m_pOutBuff;
			lvi.iItem = iItem;
			lvi.iSubItem = GetColIndex (IDENT_COLUMN, iMode);
			pFI -> m_pLV -> SetItem (&lvi);
		}
	}
	if (-1 == iItem) return;

// zweite Spalte enthält den KurzText
	memset (&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.pszText = pKText;
	lvi.iItem = iItem;
	lvi.iSubItem = GetColIndex (KTEXT_COLUMN, iMode);
	pFI -> m_pLV -> SetItem (&lvi);

	if (iMode & SELIDMODE_SHOWCONNECTIONS) {
	// dritte Spalte enthält Connections
	HPROJECT hPr = DEX_GetObjectsProject (lIdent);

		TX_ASSERT(NULL != hPr);
		if (NULL != DEX_GetDataSourceShortName (hPr, pFI -> m_pOutBuff)) {
			memset (&lvi, 0, sizeof(LV_ITEM));
			lvi.mask = LVIF_TEXT;
			lvi.pszText = pFI -> m_pOutBuff;
			lvi.iItem = iItem;
			lvi.iSubItem = GetColIndex (CONNECTION_COLUMN, iMode);
			pFI -> m_pLV -> SetItem (&lvi);
		}
	}
}

static int GetLargeImage (DWORD dwType)
{
	if (dwType & OTPunkt) return IMAGELARGE_POINT;
	if (dwType & OTLinie) return IMAGELARGE_LINE;
	if (dwType & OTFlaeche) return IMAGELARGE_AREA;
	if (dwType & OTText) return IMAGELARGE_TEXT;
	return -1;	
}

static short GetOTypFromLargeImage (int iImage)
{
	switch (iImage) {
	case IMAGELARGE_POINT:		return OTPunkt;
	case IMAGELARGE_LINE:		return OTLinie;
	case IMAGELARGE_AREA:		return OTFlaeche;
	case IMAGELARGE_TEXT:		return OTText;
	default:
		TX_ASSERT(false);
		break;
	}

return 0;
}

#pragma optimize ("", off)
static void AddTypeEntry (FILLIDENTDATA *pFI, long lIdent, char *pKText, int iOType)
{
	if (NULL != pFI -> m_pFcnAdd && !(*pFI -> m_pFcnAdd)(lIdent, iOType, pFI -> m_dwData))
		return;		// nicht einfügen

int iImage = GetLargeImage (iOType);

	if (-1 != iImage) {		// Eintrag generieren
	int iOvl = 0;

		if (pFI -> m_pFcnOvl)
			iOvl = static_cast<int>((pFI -> m_pFcnOvl)(lIdent, pFI -> m_dwData));

		AddTypeString (pFI, lIdent, pKText, iOType, iImage, iOvl, pFI -> m_iMode);
	}
}
#pragma optimize ("", on)

extern "C" 
BOOL _XTENSN_EXPORT PASCAL FillIdentsLV (long lIdent, DWORD dwTypes, void *pData)
{
// Beschreibbarkeit testen
FILLIDENTDATA *pFI = (FILLIDENTDATA *)pData;

	if ((pFI -> m_iMode & SELIDMODE_ONLYWRITABLE) && DEX_GetROModeIdent (lIdent))
		return TRUE;		// Ident/Datenquelle ist schreibgeschützt

	if ((pFI -> m_iMode & SELIDMODE_NOQUERYDEFS) && (HACTPROJECT == DEX_GetObjectsProject(lIdent)))
		return TRUE;		// Zuordnungsobjektklassen nicht mit anzeigen

// Kurztext des Idents besorgen
PBDDATA pbdData;
char cbKText[34];

	memset (cbKText, '\0', sizeof(cbKText));

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = cbKText;
	pbdData.pbdKTextLen = sizeof(cbKText) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);
	cbKText[32] = '\0';

// Einträge generieren
	if (pFI -> m_iMode & SELIDMODE_SINGLETYPE) {
	// große Bildchen
		if (pFI -> m_iOTypes & OTPunkt && dwTypes & OTPunkt)
			AddTypeEntry (pFI, lIdent, pbdData.pbdKText, OTPunkt);
		if (pFI -> m_iOTypes & OTLinie && dwTypes & OTLinie)
			AddTypeEntry (pFI, lIdent, pbdData.pbdKText, OTLinie);
		if (pFI -> m_iOTypes & OTFlaeche && dwTypes & OTFlaeche)
			AddTypeEntry (pFI, lIdent, pbdData.pbdKText, OTFlaeche);
		if (pFI -> m_iOTypes & OTText && dwTypes & OTText)
			AddTypeEntry (pFI, lIdent, pbdData.pbdKText, OTText);

	} else if (pFI -> m_iMode & SELIDMODE_MULTITYPES) {
		if (NULL != pFI -> m_pFcnAdd) {
		DWORD dwNewTypes = (*pFI -> m_pFcnAdd)(lIdent, dwTypes, pFI -> m_dwData);

			if (0 == dwNewTypes)
				return TRUE;		// nicht einfügen

			dwTypes = dwNewTypes;	// nur die gewünschten hinzufügen
		}

	// kleine Bildchen
	int iImage = static_cast<int>(dwTypes) + IMAGESMALL_FIRST;
	int iOvl = 0;

		if (pFI -> m_pFcnOvl)
			iOvl = static_cast<int>((pFI -> m_pFcnOvl)(lIdent, pFI -> m_dwData));

	// gekoppelten Eintrag generieren
		AddTypeString (pFI, lIdent, pbdData.pbdKText, dwTypes, iImage, iOvl, pFI -> m_iMode);

	} else if (pFI -> m_iMode & SELIDMODE_ALLIDENTSPBD) {
	// gekoppelten Eintrag generieren (ohne Bildchen)
		if (NULL != pFI -> m_pFcnAdd) {
		DWORD dwNewTypes = (*pFI -> m_pFcnAdd)(lIdent, dwTypes, pFI -> m_dwData);

			if (0 == dwNewTypes)
				return TRUE;		// nicht einfügen

			dwTypes = dwNewTypes;	// nur die gewünschten hinzufügen
		}
		AddTypeString (pFI, lIdent, pbdData.pbdKText, dwTypes, 0, 0, pFI -> m_iMode);
	}
	return true;	// weitermachen
}

// Initialisierung des Controls -----------------------------------------------
BOOL CSelIdentListView::InitControl (DWORD iOTypes, int iMode, 
			SELIDOVLPROC pFcnOvl, PFNLVCOMPARE pfnCompare, DWORD dwData, ADDENTRYPROC pFcnAdd)
{
// IdentMode darf nicht verändert werden
	_ASSERTE(!m_fInitialized || (m_iMode & SELIDMODE_IDENTMODE) == (iMode & SELIDMODE_IDENTMODE));

	m_iOTypes = iOTypes;
	m_iMode = iMode;
	m_pFcnOvl = pFcnOvl;
	m_pFcnAdd = pFcnAdd;
	m_pFcnCmp = pfnCompare;
	m_dwData = dwData;

	if (!m_fInitialized) {
		if (!Control::FInit()) 
			return false;		// Initialisieren

		SetStyle (LVS_SHOWSELALWAYS);

	// ImageList initialisieren
	ResourceFile RF (g_pDLLName);
	CImageList *pIL = NULL;

		if (iMode & SELIDMODE_SINGLETYPE) {
			m_ilType.CreateList (ResID (IDB_PLFT_LARGE, &RF), 17, 0, RGB(255, 0, 255));
			m_ilType.SetOverlayImage (0, 1);
			m_ilType.SetOverlayImage (1, 2);
			m_ilType.SetOverlayImage (2, 3);
			m_ilType.SetOverlayImage (3, 4);
			pIL = SetImageList (&m_ilType, LVSIL_SMALL);
		
		} 
		else if (iMode & SELIDMODE_MULTITYPES) {
			m_ilType.CreateList (ResID (IDB_PLFT_SMALL, &RF), 16, 0, RGB(255, 0, 255));
			pIL = SetImageList (&m_ilType, LVSIL_SMALL);
		} 
		DELETE_OBJ(pIL);

	// ZeichenKette anlegen
		ATLTRY(m_pBuff = new char [_MAX_PATH]);
		if (m_pBuff == NULL) return false;
	}

// weitere Spalten einfügen
	if (NULL != m_pControlWnd) {
	// Control ist durch ControlWindow subclassed
		m_pControlWnd -> DeleteAllItems();
		m_pControlWnd -> DeleteAllColumns();
		if (-1 == m_pControlWnd -> InsertColumns (GetColumnCount()))
			return false;
	} else {
	// Control hat kein ControlWindow
		DeleteAllItems();
		DeleteAllColumns();
		if (-1 == InsertColumns (GetColumnCount()))
			return false;
	}

	m_fInitialized = true;
	return FillWithData(false);
}

class CSetRedraw
{
public:
	CSetRedraw(CListViewCtrl &rCtrl) :
		m_rCtrl(rCtrl)
	{
		m_rCtrl.ForwardEvent (WM_SETREDRAW, FALSE);
	}
	~CSetRedraw()
	{
		m_rCtrl.ForwardEvent (WM_SETREDRAW, TRUE);
	}

private:
	CListViewCtrl &m_rCtrl;
};

bool CSelIdentListView::FillWithData (bool fClear)
{
CSetRedraw Redraw(*this);

	if (fClear)
		DeleteAllItems();

	TX_ASSERT(NULL != m_pBuff);		// muß initialisiert sein

FILLIDENTDATA FID;

	FID.m_pLV = this;
	FID.m_pOutBuff = m_pBuff;
	FID.m_iCnt = 0;
	FID.m_iMode = m_iMode;
	FID.m_iOTypes = m_iOTypes;
	FID.m_pFcnOvl = m_pFcnOvl;
	FID.m_pFcnAdd = m_pFcnAdd;
	FID.m_dwData = m_dwData;

	if (m_iMode & SELIDMODE_ALLIDENTS) {
	// alle Idents enumerieren
	ENUMNOKEYLONGEX ELK;

		ELK.eFcn = (ENUMLONGKEYEXPROC)FillIdentsLV;
		ELK.ePtr = &FID;
		ELK.eData = m_iOTypes;
		if (!DEX_EnumIdentsEx (ELK))	// alle Idents der GeoDB
			return false;

	} else if (m_iMode & (SELIDMODE_MULTITYPES|SELIDMODE_SINGLETYPE)) {
	// nur über Ansicht enumerieren
	ENUMTEXTKEYEX ETK;

		ETK.eKey = NULL;			// aktuelle Sicht
		ETK.eFcn = (ENUMLONGKEYEXPROC)FillIdentsLV;
		ETK.ePtr = &FID;
		ETK.eData = m_iOTypes;
		if (!DEX_EnumSightIdentsEx (ETK))	// alle Idents dieser Sicht
			return false;

	} else if (m_iMode & SELIDMODE_ALLIDENTSPBD) {
	ENUMLONGKEY ELK;

		FID.m_iOTypes = OTPunkt|OTLinie|OTFlaeche|OTText;
		ELK.eKey = 'i';
		ELK.eFcn = (ENUMLONGKEYPROC)FillIdentsLV;
		ELK.ePtr = &FID;
		if (!DEX_EnumPBDData (ELK))		// alle Idents der Pbd
			return false;
	}

// Spalten entsprechend richten
	if (!(m_iMode & SELIDMODE_NOICONS))
		FitColumn (PICTURE_COLUMN);

	FitColumn (GetColIndex (KTEXT_COLUMN, m_iMode));
	FitColumn (GetColIndex (IDENT_COLUMN, m_iMode));
	if (m_iMode & SELIDMODE_SHOWCONNECTIONS) 
		FitColumn (GetColIndex (CONNECTION_COLUMN, m_iMode));

// evtl. Zeilen sortieren
	if (NULL != m_pFcnCmp)
		SortItems (m_pFcnCmp, m_dwData);

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// ZugriffsFunktionen auf _alle_ Identifikatoren 
// Diese Funktionen liefern jetzt alle Objekttypen für einen Ident mit einem mal.
int CSelIdentListView::GetFirstIdentInList (long &rlIdent, short &riOTyp)
{
// anfängliche Initialisierungen
	m_lLastIdent = 0L;
	m_iLastTypes = 0;
	
	if (!DecodeEntry (GetFirstInList(), m_lLastIdent, m_iLastTypes))
		return -1;		// kein Eintrag verfügbar

	return GetNextIdentInList (rlIdent, riOTyp);
}

int CSelIdentListView::GetNextIdentInList (long &rlIdent, short &riOTyp)
{
// wenn wir bereits am Ende sind
	if (m_lLastIdent == -1L)
		return -1;	// kein weiterer Eintrag verfügbar
		
// ersten Ident gefunden
	rlIdent = m_lLastIdent;
	riOTyp = m_iLastTypes;

// jetzt solange suchen, bis neuer Ident kommt
int iIndex = m_iCurrItem;

	do {
		if (!DecodeEntry (GetNextInList(), m_lLastIdent, m_iLastTypes)) {
			m_lLastIdent = -1L;	// das war der letzte Eintrag
			m_iLastTypes = 0;
			return iIndex;
		}
		if (rlIdent != m_lLastIdent)
			break;

		iIndex = m_iCurrItem;
		riOTyp |= m_iLastTypes;		// Typ hinzufügen
	} while (true);

	return iIndex;
}

int CSelIdentListView::GetFirstIdentInListEx (long &rlIdent, short &riOTyp, int &riCnt)
{
// anfängliche Initialisierungen
	m_lLastIdent = 0L;
	m_iLastTypes = 0;

	if (!DecodeEntry (GetFirstInList(), m_lLastIdent, m_iLastTypes))
		return -1;			// kein Eintrag verfügbar

	return GetNextIdentInListEx (rlIdent, riOTyp, riCnt);
}

int CSelIdentListView::GetNextIdentInListEx (long &rlIdent, short &riOTyp, int &riCnt)
{
// wenn wir bereits am Ende sind
	if (m_lLastIdent == -1L)
		return -1;	// kein weiterer Eintrag verfügbar
		
// ersten Ident gefunden
	rlIdent = m_lLastIdent;
	riOTyp = m_iLastTypes;
	riCnt++;
	
// jetzt solange suchen, bis neuer Ident kommt
int iIndex = m_iCurrItem;

	do {
		if (!DecodeEntry (GetNextInList(), m_lLastIdent, m_iLastTypes)) {
			m_lLastIdent = -1L;	// das war der letzte Eintrag
			m_iLastTypes = 0;
			return iIndex;
		}
		if (rlIdent != m_lLastIdent)
			break;

		iIndex = m_iCurrItem;
		riOTyp |= m_iLastTypes;		// Typ hinzufügen
		riCnt++;
	} while (true);

	return iIndex;
}

int CSelIdentListView::GetFirstInList (void)
{
	m_iCurrItem = -1;				// aufsteigend
	return GetNextInList();
}

int CSelIdentListView::GetLastInList (void)
{
	m_iCurrItem = GetItemCount()-1;	// absteigend
	return m_iCurrItem;				// der Letzte wird geliefert
}

int CSelIdentListView::GetNextInList (void)
{
	return (m_iCurrItem = GetNextItem (m_iCurrItem, LVNI_ALL));
}

int CSelIdentListView::GetPrevInList (void)
{
	return (m_iCurrItem = GetNextItem (m_iCurrItem, LVNI_ALL|LVNI_ABOVE));
}

// ZugriffsFunktionen auf ausgewählte Identifikatoren -------------------------
// Diese Funktionen liefern jetzt alle selektierten Objekttypen für einen Ident
// mit einem mal.
BOOL CSelIdentListView::GetFirstIdent (long &rlIdent, short &riOTyp)
{
// anfängliche Initialisierungen
	m_lLastIdent = 0L;
	m_iLastTypes = 0;
	
	if (!DecodeEntry (GetFirstSelected(), m_lLastIdent, m_iLastTypes))
		return false;		// kein Eintrag verfügbar

	return GetNextIdent (rlIdent, riOTyp);
}

BOOL CSelIdentListView::GetNextIdent (long &rlIdent, short &riOTyp)
{
// wenn wir bereits am Ende sind
	if (m_lLastIdent == -1L)
		return false;	// kein weiterer Eintrag verfügbar
		
// ersten Ident gefunden
	rlIdent = m_lLastIdent;
	riOTyp = m_iLastTypes;
	
// jetzt solange suchen, bis neuer Ident kommt
	do {
		if (!DecodeEntry (GetNextSelected(), m_lLastIdent, m_iLastTypes)) {
			m_lLastIdent = -1L;	// das war der letzte Eintrag
			m_iLastTypes = 0;
			return true;
		}
		if (rlIdent != m_lLastIdent)
			break;
		riOTyp |= m_iLastTypes;		// Typ hinzufügen
	} while (true);
	return true;
}

BOOL CSelIdentListView::GetFirstIdentEx (long &rlIdent, short &riOTyp, int &riCnt)
{
// anfängliche Initialisierungen
	m_lLastIdent = 0L;
	m_iLastTypes = 0;

	if (!DecodeEntry (GetFirstSelected(), m_lLastIdent, m_iLastTypes))
		return false;		// kein Eintrag verfügbar

	return GetNextIdentEx (rlIdent, riOTyp, riCnt);
}

BOOL CSelIdentListView::GetNextIdentEx (long &rlIdent, short &riOTyp, int &riCnt)
{
// wenn wir bereits am Ende sind
	if (m_lLastIdent == -1L)
		return false;	// kein weiterer Eintrag verfügbar
		
// ersten Ident gefunden
	rlIdent = m_lLastIdent;
	riOTyp = m_iLastTypes;
	riCnt++;
	
// jetzt solange suchen, bis neuer Ident kommt
	do {
		if (!DecodeEntry (GetNextSelected(), m_lLastIdent, m_iLastTypes)) {
			m_lLastIdent = -1L;	// das war der letzte Eintrag
			m_iLastTypes = 0;
			return true;
		}
		if (rlIdent != m_lLastIdent)
			break;
		riOTyp |= m_iLastTypes;		// Typ hinzufügen
		riCnt++;
	} while (true);
	return true;
}

int CSelIdentListView::GetFirstSelected (void)
{
	m_iCurrItem = -1;				// aufsteigend
	return GetNextSelected();
}

int CSelIdentListView::GetLastSelected (void)
{
	m_iCurrItem = GetItemCount()-1;	// absteigend
	if (IsItemSelected (m_iCurrItem))
		return m_iCurrItem;			// der Letzte ist selektiert

	return GetPrevSelected();
}

int CSelIdentListView::GetNextSelected (void)
{
	return (m_iCurrItem = GetNextItem (m_iCurrItem, LVNI_ALL|LVNI_SELECTED));
}

int CSelIdentListView::GetPrevSelected (void)
{
	return (m_iCurrItem = GetNextItem (m_iCurrItem, LVNI_SELECTED|LVNI_ABOVE));
}

void CSelIdentListView::SelectItem (int iIndex, BOOL fSel)
{
UINT uiState = GetItemState (iIndex, LVIS_SELECTED);

	if (fSel) uiState |= LVIS_SELECTED;
	else	  uiState &= ~LVIS_SELECTED;

	SetItemState (iIndex, uiState, LVIS_SELECTED);

	Update (iIndex);
}

void CSelIdentListView::SelectItemFocus (int iIndex, BOOL fSel)
{
UINT uiState = GetItemState (iIndex, LVIS_FOCUSED);

	if (fSel) uiState |= LVIS_FOCUSED;
	else	  uiState &= ~LVIS_FOCUSED;

	SetItemState (iIndex, uiState, LVIS_FOCUSED);

	Update (iIndex);
}

int CSelIdentListView::GetItemFocus (void)
{
int iCnt = GetItemCount();

	for (int iIndex = 0; iIndex < iCnt; iIndex++) {
	// Alle Einträge der Listbox abarbeiten
	UINT uiState = GetItemState (iIndex, LVIS_FOCUSED);

		if (uiState & LVIS_FOCUSED)
			return iIndex;
	}
	return -1;
}

BOOL CSelIdentListView::IsItemSelected (int iIndex)
{
	TX_ASSERT(iIndex >= 0 && iIndex < GetItemCount());

UINT uiState = GetItemState (iIndex, LVIS_SELECTED);

	return (GetItemState(iIndex, LVIS_SELECTED) & LVIS_SELECTED) ? true : false;
}

int CSelIdentListView::SelectIdent (long lIdent, short iOTyp, BOOL fSel)
{
	if (0 == lIdent) {
		SelectItem (0, fSel);
		return 0;
	} else {
	int iCnt = GetItemCount();
	long lCurrIdent = 0L;
	short iCurrOTyp = 0;

		for (int iIndex = 0; iIndex < iCnt; iIndex++) {
		// Alle Einträge der Listbox abarbeiten
		
			if (DecodeEntry (iIndex, lCurrIdent, iCurrOTyp)) {
				if (lCurrIdent == lIdent && ((0 == iOTyp) || (iCurrOTyp == iOTyp))) {
				// Eintrag gefunden
					SelectItem (iIndex, fSel);
					return iIndex;
				}
			}
		}
	}

return -1;
}

BOOL CSelIdentListView::ChangeSelectedAll (BOOL fSel)
{
int iCnt = GetItemCount();

	if (0 == iCnt) return false;

	for (int iIndex = 0; iIndex < iCnt; iIndex++) {
	// Alle Einträge der Listbox abarbeiten
	UINT uiState = GetItemState (iIndex, LVIS_SELECTED);

		if (fSel) uiState |= LVIS_SELECTED;
		else	  uiState &= ~LVIS_SELECTED;

		SetItemState (iIndex, uiState, LVIS_SELECTED);
		Update (iIndex);
	}
	return true;
}

// HilfsFunktionen ------------------------------------------------------------
BOOL CSelIdentListView::DecodeEntry (int iIndex, long &rlIdent, short &riOTyp)
{
	if (iIndex == -1) return false;
	
	rlIdent = 0;
	riOTyp = 0;

DWORD dwData = GetItemData (iIndex);
CSelIdentItem *pItem = reinterpret_cast<CSelIdentItem *>(dwData);

	if (NULL == pItem) return false;
	rlIdent = static_cast<LONG>(pItem -> m_ulIdent);
	riOTyp = pItem -> m_iOTypes;
	return true;
}

BOOL CSelIdentListView::GetDescription (int iIndex, char *pBuffer, int iLen)
{
	if (iIndex == -1) 
		return false;

	return (0 != GetItemText (iIndex, GetColIndex (KTEXT_COLUMN, m_iMode), pBuffer, iLen));
}

void CSelIdentListView::FitColumn (int iCol)
{
// Call this after your list control is filled     
	SetRedraw(false);

int mincol = iCol < 0 ? 0 : iCol;
int maxcol = iCol < 0 ? GetColumnCount()-1 : iCol;

	for (int col = mincol; col <= maxcol; col++) {
		SetColumnWidth(col, LVSCW_AUTOSIZE);

	int wc1 = GetColumnWidth (col);

		SetColumnWidth (col, LVSCW_AUTOSIZE_USEHEADER);

	int wc2 = GetColumnWidth (col);
	int wc = max (MINCOLWIDTH, max(wc1, wc2));

		SetColumnWidth (col, wc);     
	}

//	RecalcHeaderTips(); 
	SetRedraw (true);
	InvalidateRect (Handle(), NULL, true); 
}

void CSelIdentListView::SetRedraw (BOOL fRedraw)
{
	::SendMessage(Handle(), WM_SETREDRAW, fRedraw, 0);
}

///////////////////////////////////////////////////////////////////////////////
// Image neu setzen
BOOL CSelIdentListView::UpdateImage (int iIndex)
{
	if (iIndex < 0) return false;
	if (m_iMode & SELIDMODE_NOICONS) 
		return false;		// keine Bildchen vorhanden

long lIdent = 0L;
short iOTyp = 0;

	if (!DecodeEntry (iIndex, lIdent, iOTyp))
		return false;

int iImage = -1;
int iOvl = 0;

	if (m_iMode & SELIDMODE_SINGLETYPE) {
	// große Bildchen
		iImage = GetLargeImage (iOTyp);
	} else {
	// kleine Bildchen
		iImage = static_cast<int>(iOTyp) + IMAGESMALL_FIRST;
	}
	if (-1 == iImage) return false;		// trotzdem weitermachen
	if (m_pFcnOvl)
		iOvl = static_cast<int>((m_pFcnOvl)(lIdent, m_dwData));

LV_ITEM lvi;

	memset (&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_IMAGE|LVIF_STATE;
	lvi.iItem = iIndex;
	lvi.iSubItem = GetColIndex (IDENT_COLUMN, m_iMode);
	lvi.iImage = iImage;
	lvi.stateMask = LVIS_OVERLAYMASK;
	lvi.state = INDEXTOOVERLAYMASK(iOvl);

	SetItem (&lvi);
	Update (iIndex);
	return true;
}

int CSelIdentListView::GetColumnCount(void)
{
HWND hCtrl = GetDlgItem (Handle(), 0);

	TX_ASSERT(::IsWindow(hCtrl));
	return Header_GetItemCount (hCtrl);
}


///////////////////////////////////////////////////////////////////////////////
// EventHandler
void CSelIdentListView::OnDeleteItem (NM_LISTVIEW *pNLV)
{
	if (pNLV -> iItem != -1) {
	DWORD dwData = GetItemData (pNLV -> iItem);

		if (0L != dwData) {
			delete reinterpret_cast<CSelIdentItem *>(dwData);
			SetItemData (pNLV -> iItem, 0L);
		}
	}
}

void CSelIdentListView::OnDeleteAllItems (void)
{
int iCnt = GetItemCount();

	for (int i = 0; i < iCnt; i++) {
	DWORD dwData = GetItemData (i);

		if (0L != dwData) {
			delete reinterpret_cast<CSelIdentItem *>(dwData);
			SetItemData (i, 0L);
		}
	}
}

void CSelIdentListView::DeleteAllColumns()
{
int iCnt = GetColumnCount();

	if (iCnt > 0) {
		for (int i = iCnt-1; i >= 0; --i)
			DeleteColumn(i);
	}
}

int CSelIdentListView::InsertColumns (int iCount)
{
// HeaderBezeicher eintragen
ResourceFile RF (g_pDLLName);
ResString resIdent (ResID (IDS_HEADERIDENT, &RF), 32);	// "Objektklassenschlüssel"
ResString resDesc (ResID (IDS_HEADERDESC, &RF), 32);	// "Beschreibung"

	if (!(m_iMode & SELIDMODE_NOICONS)) {
	ResString resTyp (ResID (IDS_HEADERTYP, &RF), 32);	// "Typ"

		InsertColumn (PICTURE_COLUMN, resTyp, LVCFMT_LEFT, -1, PICTURE_COLUMN);
	}

int iIdentCol = GetColIndex (IDENT_COLUMN, m_iMode);
int iKTextCol = GetColIndex (KTEXT_COLUMN, m_iMode);

	InsertColumn (iIdentCol, resIdent, LVCFMT_LEFT, -1, iIdentCol);
	InsertColumn (iKTextCol, resDesc, LVCFMT_LEFT, -1, iKTextCol);

	if (SELIDMODE_SHOWCONNECTIONS & m_iMode) {
	ResString resConn (ResID(IDS_HEADERCONN, &RF), 32);
	int iConnCol = GetColIndex (CONNECTION_COLUMN, m_iMode);

		InsertColumn (iConnCol, resConn, LVCFMT_LEFT, -1, iConnCol);
	}
	return GetColumnCount();		// returns number of existing columns
}

///////////////////////////////////////////////////////////////////////////////
// subclassed CSelIdentListView
CSelIdentListViewWindow::CSelIdentListViewWindow (DialogWindow *pW, UINT uiID, DWORD dwStyle)
		: ControlWindow (new CSelIdentListView (pW, uiID, this))
{
	if (0 != dwStyle)
		SetStyle (dwStyle);
	
	m_hWnd = NULL;
#if defined(_FORCE_LEGACY_CODE)
	m_nHighlight = HIGHLIGHT_ROW;
#endif // defined(_FORCE_LEGACY_CODE)

	m_iSortedColumn = -1;				// not sorted at all
	m_rgSortOrder = SORTORDER_Unknown;
	m_pTypes = NULL;
	m_nNumCols = 0;
}

CSelIdentListViewWindow::~CSelIdentListViewWindow (void)
{
	if (NULL != GetControl())
		delete (CSelIdentListView *)GetControl();
	DELETE_OBJ(m_pTypes);
}

LRESULT CSelIdentListViewWindow::Dispatch (Event e)
{
	if (NULL == m_hWnd)		// bei der ersten Gelegenheit unser Handle speichern
		m_hWnd = Handle(API_WINDOW_HWND);

	switch (e.Msg()) {
#if defined(_FORCE_LEGACY_CODE)
	case WM_PAINT:
		Expose ((ExposeEvt &)e);	// StandardHandler von ControlWindow umgehen
		return TRUE;
#endif // defined(_FORCE_LEGACY_CODE)

	case WM_NOTIFY:
		{
		NMHDR *pNMHDR = reinterpret_cast<NMHDR *>(e.LParam());

			switch (pNMHDR -> code) {
			case HDN_ITEMCLICKA:
			case HDN_ITEMCLICKW:
				return OnHeaderClicked (pNMHDR);

			default:
				break;
			}
		}
		break;

	default:
		break;
	}
	return ControlWindow::Dispatch(e);
}

#if defined(_FORCE_LEGACY_CODE)
///////////////////////////////////////////////////////////////////////////////
// ownerdraw messages
BOOL CSelIdentListViewWindow::DrawItemFocus (DrawItemEvt e)
{
	return true;
}

BOOL CSelIdentListViewWindow::DrawItemSelect (DrawItemEvt e)
{
	return true;
}

BOOL CSelIdentListViewWindow::DrawEntireItem (DrawItemEvt e)
{
	if (NULL == m_hWnd)
		m_hWnd = Handle(API_WINDOW_HWND);

HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);
Rectangle rcItem (e.ItemSize());
int nItem = e.GetItemID();
CImageList *pImageList = NULL;

// Save dc state
int nSavedDC = SaveDC (hDC);

// Get item image and state info
LV_ITEM lvi;

	lvi.mask = LVIF_IMAGE | LVIF_STATE;
	lvi.iItem = nItem;
	lvi.iSubItem = 0;
	lvi.stateMask = 0xFFFF;		// get all state flags
	GetListCtrl() -> GetItem (&lvi);

// Should the item be highlighted
BOOL bHighlight = ((lvi.state & LVIS_DROPHILITED) ||
					( (lvi.state & LVIS_SELECTED) &&
						((::GetFocus() == m_hWnd) ||
							(GetStyle() & LVS_SHOWSELALWAYS)
						)
					)
				  );


// Get rectangles for drawing
RECT rcBounds, rcLabel, rcIcon;

	GetListCtrl() -> GetItemRect (nItem, &rcBounds, LVIR_BOUNDS);
	GetListCtrl() -> GetItemRect (nItem, &rcLabel, LVIR_LABEL);
	GetListCtrl() -> GetItemRect (nItem, &rcIcon, LVIR_ICON);

RECT rcCol = rcBounds; 
string sLabel = GetListCtrl() -> GetItemText (nItem, 0);

// Labels are offset by a certain amount  
// This offset is related to the width of a space character
SIZE sz;

	::GetTextExtentPoint32 (hDC, TEXT(" "), 1, &sz);

int offset = 2*sz.cx;
RECT rcHighlight;
RECT rcWnd;
int nExt;

	switch (m_nHighlight) {
	case HIGHLIGHT_NORMAL: 
		::GetTextExtentPoint32 (hDC, sLabel.c_str(), sLabel.length(), &sz);
		nExt = sz.cx + offset;
		rcHighlight = rcLabel;
		if (rcLabel.left + nExt < rcLabel.right)
			rcHighlight.right = rcLabel.left + nExt;
		break;

	case HIGHLIGHT_ALLCOLUMNS:
		rcHighlight = rcBounds;
		rcHighlight.left = rcLabel.left;
		break;

	case HIGHLIGHT_ROW:
		::GetClientRect (m_hWnd, &rcWnd);
		rcHighlight = rcBounds;
		rcHighlight.left = rcLabel.left;
		rcHighlight.right = rcWnd.right + 1;
		break;

	default:
		rcHighlight = rcLabel;
	}

	// Draw the background color
	if (bHighlight) {
		::SetTextColor (hDC, ::GetSysColor(COLOR_HIGHLIGHTTEXT));
		::SetBkColor (hDC, ::GetSysColor(COLOR_HIGHLIGHT));

	HBRUSH hBr = ::CreateSolidBrush (::GetSysColor(COLOR_HIGHLIGHT));

		::FillRect (hDC, &rcHighlight, hBr);
		::DeleteObject (hBr);
	} else {
	HBRUSH hBr = ::CreateSolidBrush (::GetSysColor(COLOR_WINDOW));

		::FillRect (hDC, &rcHighlight, hBr);
		::DeleteObject (hBr);
	}
	
// Set clip region
	rcCol.right = rcCol.left + GetListCtrl() -> GetColumnWidth(0);

HRGN hRgn = ::CreateRectRgnIndirect (&rcCol);

	::SelectClipRgn(hDC, hRgn);
	::DeleteObject (hRgn);

// Draw state icon
	if (lvi.state & LVIS_STATEIMAGEMASK) {
	int nImage = ((lvi.state & LVIS_STATEIMAGEMASK)>>12) - 1;
	
		pImageList = GetListCtrl() -> GetImageList(LVSIL_STATE);
		if (pImageList) {
			pImageList-> Draw (hDC, nImage, Point(rcCol.left, rcCol.top), ILD_TRANSPARENT);
			delete pImageList;
		}
	}
	
// Draw normal and overlay icon
	pImageList = GetListCtrl() -> GetImageList (LVSIL_SMALL);
	if (pImageList) {
	UINT nOvlImageMask = lvi.state & LVIS_OVERLAYMASK;
		
		pImageList->Draw (hDC, lvi.iImage, Point(rcIcon.left, rcIcon.top),
			(bHighlight ? ILD_BLEND50 : 0) | ILD_TRANSPARENT | nOvlImageMask);
		delete pImageList;
	}
	
// Draw item label - Column 0
	rcLabel.left += offset/2;
	rcLabel.right -= offset;

	::DrawText (hDC, sLabel.c_str(), -1, &rcLabel, 
		DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER | DT_END_ELLIPSIS);

// Draw labels for remaining columns
LV_COLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_WIDTH;
	if (m_nHighlight == HIGHLIGHT_NORMAL)		// Highlight only first column
	{
		::SetTextColor (hDC, ::GetSysColor(COLOR_WINDOWTEXT));
		::SetBkColor (hDC, ::GetSysColor(COLOR_WINDOW));
	}
	
	rcBounds.right = rcHighlight.right > rcBounds.right ? rcHighlight.right :
							rcBounds.right;

	hRgn = ::CreateRectRgnIndirect (&rcBounds);
	::SelectClipRgn(hDC, hRgn);
	::DeleteObject (hRgn);
					   
	for (int nColumn = 1; GetListCtrl() -> GetColumn (nColumn, &lvc); nColumn++) 
	{
		rcCol.left = rcCol.right;
		rcCol.right += lvc.cx;

		sLabel = GetListCtrl() -> GetItemText (nItem, nColumn);
		if (sLabel.length() == 0)
			continue;

	// Get the text justification
	UINT nJustify = DT_LEFT;
	
		switch (lvc.fmt & LVCFMT_JUSTIFYMASK) {
		case LVCFMT_RIGHT:
			nJustify = DT_RIGHT;
			break;

		case LVCFMT_CENTER:
			nJustify = DT_CENTER;
			break;

		default:
			break;
		}

		rcLabel = rcCol;
		rcLabel.left += offset;
		rcLabel.right -= offset;

		::DrawText (hDC, sLabel.c_str(), -1, &rcLabel, nJustify | DT_SINGLELINE | 
					DT_NOPREFIX | DT_VCENTER | DT_END_ELLIPSIS);
	}

// Draw focus rectangle if item has focus
	if (lvi.state & LVIS_FOCUSED && (GetFocus() == m_hWnd))
		::DrawFocusRect (hDC, &rcHighlight);

// Restore dc
	::RestoreDC (hDC, nSavedDC);
	return true;
}

void CSelIdentListViewWindow::RepaintSelectedItems()
{
RECT rcBounds, rcLabel;

// Invalidate focused item so it can repaint 
int nItem = GetListCtrl() -> GetNextItem (-1, LVNI_FOCUSED);

	if(nItem != -1)
	{
		GetListCtrl() -> GetItemRect(nItem, &rcBounds, LVIR_BOUNDS);
		GetListCtrl() -> GetItemRect(nItem, &rcLabel, LVIR_LABEL);
		rcBounds.left = rcLabel.left;
		rcBounds.right++;

		::InvalidateRect (m_hWnd, &rcBounds, FALSE);
	}

	// Invalidate selected items depending on LVS_SHOWSELALWAYS
	if(!(GetStyle() & LVS_SHOWSELALWAYS))
	{
		for(nItem = GetListCtrl() -> GetNextItem(-1, LVNI_SELECTED);
			nItem != -1; 
			nItem = GetListCtrl() -> GetNextItem(nItem, LVNI_SELECTED))
		{
			GetListCtrl() -> GetItemRect(nItem, &rcBounds, LVIR_BOUNDS);
			GetListCtrl() -> GetItemRect(nItem, &rcLabel, LVIR_LABEL);
			rcBounds.left = rcLabel.left;
			rcBounds.right++;

			::InvalidateRect (m_hWnd, &rcBounds, FALSE);
		}
	}

	Update();
}

void CSelIdentListViewWindow::Expose (ExposeEvt e)
{
	if (NULL == m_hWnd)
		m_hWnd = Handle(API_WINDOW_HWND);

// in full row select mode, we need to extend the clipping region
// so we can paint a selection all the way to the right
	if (m_nHighlight == HIGHLIGHT_ROW &&
		(GetStyle() & LVS_TYPEMASK) == LVS_REPORT )
	{
	RECT rcBounds;
		
		GetListCtrl() -> GetItemRect (0, &rcBounds, LVIR_BOUNDS);

	RECT rcClient;
		
		::GetClientRect (m_hWnd, &rcClient);
		if(rcBounds.right < rcClient.right) {
		HDC hDC = GetDC (m_hWnd);
		RECT rcClip;

			::GetClipBox (hDC, &rcClip);

			rcClip.left = min ((long)(rcBounds.right-1), rcClip.left);
			rcClip.right = rcClient.right;

			::InvalidateRect (m_hWnd, &rcClip, FALSE);
			::ReleaseDC (m_hWnd, hDC);
		}
	}
	Default (e);
}

void CSelIdentListViewWindow::FocusChange (FocusChangeEvt e)
{
	if (NULL == m_hWnd)
		m_hWnd = Handle(API_WINDOW_HWND);

	ControlWindow::FocusChange (e);

	if (!e.gotFocus()) {
	// WM_KILLFOCUS
	// check if we are losing focus to label edit box
		if(e.WParam() != NULL && ::GetParent ((HWND)e.WParam()) == m_hWnd)
			return;

	// repaint items that should change appearance
		if((GetStyle() & LVS_TYPEMASK) == LVS_REPORT)
			RepaintSelectedItems();
	} else {
	// WM_SETFOCUS
		// check if we are getting focus from label edit box
		if(e.WParam() != NULL && ::GetParent ((HWND)e.WParam()) == m_hWnd)
			return;

		// repaint items that should change appearance
		if((GetStyle() & LVS_TYPEMASK) == LVS_REPORT)
			RepaintSelectedItems();
	}
}

CSelIdentListViewWindow::EHighlight 
CSelIdentListViewWindow::SetHighlightType (EHighlight hilite)
{
EHighlight oldhilite = m_nHighlight;

	if (hilite <= HIGHLIGHT_ROW)
	{
		m_nHighlight = hilite;
		RePaint();
	}
	return oldhilite;
}
#endif // defined(_FORCE_LEGACY_CODE)

int CSelIdentListViewWindow::InsertColumns (int iCount)
{
	return GetListCtrl() -> InsertColumns (iCount);
}

void CSelIdentListViewWindow::DeleteAllColumns()
{
	GetListCtrl() -> DeleteAllColumns();
}

BOOL CSelIdentListViewWindow::DeleteAllItems()
{
	return GetListCtrl() -> DeleteAllItems();
}

///////////////////////////////////////////////////////////////////////////////
// Sortierfunktionalität
bool CSelIdentListViewWindow::SetColumnTypes (unsigned char *pColTypes, unsigned nColCnt)
{
	TX_ASSERT(nColCnt >= GetListCtrl() -> GetColumnCount());

	DELETE_OBJ(m_pTypes);
	ATLTRY(m_pTypes = new unsigned char[nColCnt]);
	if(m_pTypes == NULL) {
		m_nNumCols = 0;
		return false;
	}

	for (unsigned int i = 0; i < nColCnt; i++) {
		if(pColTypes[i] > LVEX_LAST) {
			m_nNumCols = 0;
			delete m_pTypes;
			return false;
		}
		m_pTypes[i] = pColTypes[i];
	}
	m_nNumCols = nColCnt;
	return true;
}

string GetObjectTypes (DWORD dwTypes)
{
string str;

	if (OTPunkt & dwTypes) str += "P";
	if (OTLinie & dwTypes) str += "L";
	if (OTFlaeche & dwTypes) str += "F";
	if (OTText & dwTypes) str += "T";

	return str;
}

LRESULT CSelIdentListViewWindow::OnHeaderClicked (NMHDR *pNMHDR)
{
HD_NOTIFY *phdn = (HD_NOTIFY *)pNMHDR;

	if(phdn -> iButton == 0) {
	// Button is the left mouse button 
	// User clicked on header using left mouse button
		if(phdn -> iItem == m_iSortedColumn) {
			if (SORTORDER_Descending != m_rgSortOrder)
				m_rgSortOrder = SORTORDER_Descending;
			else 
				m_rgSortOrder = SORTORDER_Ascending;
		} else
			m_rgSortOrder = SORTORDER_Ascending;

		m_iSortedColumn = phdn -> iItem;

	// replace Item data with pointer to ListData structure
		COM_TRY {
		// evtl. Types-Feld initialisieren
			if (NULL == m_pTypes) {
				m_nNumCols = GetListCtrl() -> GetColumnCount();
				m_pTypes = new unsigned char[m_nNumCols];
				if (NULL == m_pTypes) 
					_com_issue_error(E_OUTOFMEMORY);

				for (int i = 0; i < m_nNumCols; i++)
					m_pTypes[i] = LVEX_CASE;		// beim sortieren Groß-/Kleinschreibung beachten
			}

		// jetzt sortieren
		int NumItems = GetListCtrl() -> GetItemCount();	

			if (LVEX_NOSORT != m_pTypes[m_iSortedColumn]) {
			// nur sortieren, wenn notwendig
			CEierUhr Wait (this);

				for (int i = 0; i < NumItems; i++)	{
				DWORD dwData = GetListCtrl() -> GetItemData(i); // save current data to restore it later
				string strText = GetListCtrl() -> GetItemText(i, m_iSortedColumn);

					if (PICTURE_COLUMN == m_iSortedColumn && 0 == strText.size()) 
					// Sonderbehandlung für Bildchen
						strText = GetObjectTypes (reinterpret_cast<CSelIdentItem *>(dwData) -> m_iOTypes);

				ListData *pNewData = NULL;
					
					pNewData = new ListData (dwData, strText);
					GetListCtrl() -> SetItemData (i, (DWORD)pNewData);	
				}

				TX_ASSERT(m_iSortedColumn <= m_nNumCols);
				GetListCtrl() -> SortItems (Compare, m_rgSortOrder | (m_pTypes[m_iSortedColumn] << 8));

				for(i = 0; i < NumItems; i++) {
				ListData *pData = (ListData *)GetListCtrl() -> GetItemData(i);

					GetListCtrl() -> SetItemData(i, pData -> m_dwOldData);
					DELETE_OBJ(pData);
				}
			}
		} COM_CATCH_IGNORE;
	}
	return 0;
}

/*static*/
int CALLBACK CSelIdentListViewWindow::Compare (
	LPARAM lParam1, LPARAM lParam2, LPARAM lParSortAsc)
{
string str1 = ((ListData *)lParam1)->m_strText;
string str2 = ((ListData *)lParam2)->m_strText;
unsigned char Type = unsigned char (lParSortAsc >> 8);

// restore data type and sort order from lParamSort
// if lParamSort positive - ascending sort order, negative - descending
int  sOrder = (lParSortAsc & 0xFF) ? 1 : -1; 
	
	switch (Type) {
	// integer number columns
	case LVEX_NUM:		
		return (atol(str1.c_str()) - atol(str2.c_str())) * sOrder;

	// float number columns
	case LVEX_NUM_FLOAT:
		return (atof(str1.c_str()) < atof(str2.c_str()) ? -1 : 1) * sOrder;

	// text columns (no case)
	case LVEX_NOCASE:		
		return stricmp(str1.c_str(), str2.c_str()) * sOrder;

	// text columns (case sensitive)
	case LVEX_CASE:
		return strcmp (str1.c_str(), str2.c_str()) * sOrder;	
	}
	return 0;
}
