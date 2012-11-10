// Eine ListViewCtrl, das alle Identifikator/Objekttypen der Datenbasis enthält 
// File: SELIDLST.CXX

#include "featurep.hxx"
#include "feature.h"		// ResourceKonstanten

#include "selidlst.hxx"

#define KTEXT_COLUMN	0
#define OTYP_COLUMN	1
#define IDENT_COLUMN	2

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CSelIdentList :: CSelIdentList (pDialogWindow pW, ResID uiRes, ResourceFile &rRF)
	       : CListViewCtrl (pW, uiRes), m_rRF(rRF)
{
	m_pBuff = NULL;
	m_lLastIdent = 0L;
	m_iLastTypes = 0;
	m_iCurrItem = 0;
	m_iIdBase = DEX_GetIdBase();
}

CSelIdentList :: ~CSelIdentList (void)
{
	DELETE (m_pBuff);
}

typedef struct tagFILLIDENTDATA {
	CListViewCtrl *m_pLV;
	short m_iIdBase;
	char *m_pOutBuff;
	int m_iCnt;
} FILLIDENTDATA;


static void AddTypeString (FILLIDENTDATA *pFI, long lIdent, char *pTyp, char *pKText)
{
int iItem = pFI -> m_pLV -> InsertItem (pFI -> m_iCnt++, pKText);

	if (-1 == iItem) return;

LV_ITEM lvi;

	memset (&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.pszText = pTyp;
	lvi.iItem = iItem;
	lvi.iSubItem = OTYP_COLUMN;
	pFI -> m_pLV -> SetItem (&lvi);

	if (pFI -> m_iIdBase == 10) 
		wsprintf (pFI -> m_pOutBuff, "%08ld", lIdent);
	else
		wsprintf (pFI -> m_pOutBuff, "%08lx", lIdent);

	memset (&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.pszText = pFI -> m_pOutBuff;
	lvi.iItem = iItem;
	lvi.iSubItem = IDENT_COLUMN;
	pFI -> m_pLV -> SetItem (&lvi);
}


extern "C" 
bool _XTENSN_EXPORT PASCAL FillIdentsLV (long lIdent, DWORD dwTypes, void *pData)
{
PBDDATA pbdData;
char cbKText[34];
FILLIDENTDATA *pFI = (FILLIDENTDATA *)pData;

	memset (cbKText, '\0', sizeof(cbKText));

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = cbKText;
	pbdData.pbdKTextLen = sizeof(cbKText) -1;
	pbdData.pbdLTextLen = 0;
	DEX_GetPBDData (pbdData);
	cbKText[32] = '\0';
	
	if (dwTypes & OTPunkt)	 AddTypeString (pFI, lIdent, "Punkte", pbdData.pbdKText);
	if (dwTypes & OTLinie)	 AddTypeString (pFI, lIdent, "Linien", pbdData.pbdKText);
	if (dwTypes & OTFlaeche) AddTypeString (pFI, lIdent, "Flächen", pbdData.pbdKText);
	if (dwTypes & OTText)	 AddTypeString (pFI, lIdent, "Texte", pbdData.pbdKText);

return true;	// weitermachen
}


// Initialisierung des Controls -----------------------------------------------
bool CSelIdentList :: InitControl (void)
{
	if (!Control::FInit()) return false;		// Initialisieren

	SetStyle (LVS_SHOWSELALWAYS);

// HeaderBezeicher eintragen
ResString resIdent (ResID (IDS_HEADERIDENT, &m_rRF), 16);	// "Identifikator"
ResString resType (ResID (IDS_HEADERTYPE, &m_rRF), 16);		// "Objekttyp"
ResString resDesc (ResID (IDS_HEADERDESC, &m_rRF), 16);		// "Beschreibung"

	InsertColumn (KTEXT_COLUMN, resDesc, LVCFMT_LEFT, -1, 0);
	InsertColumn (OTYP_COLUMN, resType, LVCFMT_LEFT, -1, 0);
	InsertColumn (IDENT_COLUMN, resIdent, LVCFMT_LEFT, -1, 0);

// ZeichenKette anlegen
	m_pBuff = new char [_MAX_PATH];
	if (m_pBuff == NULL) return false;

FILLIDENTDATA FID;

	FID.m_pLV = this;
	FID.m_iIdBase = m_iIdBase;
	FID.m_pOutBuff = m_pBuff;
	FID.m_iCnt = 0;

ENUMTEXTKEYEX ETK;

	ETK.eKey = NULL;			// aktuelle Sicht
	ETK.eFcn = (ENUMLONGKEYEXPROC)FillIdentsLV;
	ETK.ePtr = &FID;
	ETK.eData = OTPunkt|OTLinie|OTFlaeche|OTText;
	if (!DEX_EnumSightIdentsEx (ETK))	// alle Idents dieser Sicht
		return false;

// Spalten entsprechend richten
	FitColumn (KTEXT_COLUMN);
	FitColumn (OTYP_COLUMN);
	FitColumn (IDENT_COLUMN);

return true;
}


// ZugriffsFunktionen auf ausgewählte Identifikatoren -------------------------
// Diese Funktionen liefern jetzt alle selektierten Objekttypen für einen Ident
// mit einem mal.
bool CSelIdentList :: GetFirstIdent (long &rlIdent, short &riOTyp)
{
// anfängliche Initialisierungen
	m_lLastIdent = 0L;
	m_iLastTypes = 0;
	
	if (!DecodeEntry (GetFirstSelected(), m_lLastIdent, m_iLastTypes))
		return false;		// kein Eintrag verfügbar

return GetNextIdent (rlIdent, riOTyp);
}


bool CSelIdentList :: GetNextIdent (long &rlIdent, short &riOTyp)
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

int CSelIdentList :: GetFirstSelected (void)
{
	m_iCurrItem = -1;

return GetNextSelected();
}

int CSelIdentList :: GetNextSelected (void)
{
	return (m_iCurrItem = GetNextItem (m_iCurrItem, LVNI_ALL|LVNI_SELECTED));
}

bool CSelIdentList :: SelectIdent (long lIdent, short iOTyp, bool fSel)
{
int iCnt = GetItemCount();
long lCurrIdent = 0L;
short iCurrOTyp = 0;

	for (int iIndex = 0; iIndex < iCnt; iIndex++) {
	// Alle Einträge der Listbox abarbeiten
	
		if (DecodeEntry (iIndex, lCurrIdent, iCurrOTyp)) {
			if (lCurrIdent == lIdent && iCurrOTyp == iOTyp) {
			// Eintrag gefunden
			UINT uiState = GetItemState (iIndex, LVIS_SELECTED);

				if (fSel) uiState |= LVIS_SELECTED;
				else	  uiState &= ~LVIS_SELECTED;

				SetItemState (iIndex, uiState, LVIS_SELECTED);

				Update (iIndex);
				return true;
			}
		}
	}

return false;
}


bool CSelIdentList :: ChangeSelectedAll (bool fSel)
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
bool CSelIdentList :: DecodeEntry (int iIndex, long &rlIdent, short &riOTyp)
{
	if (iIndex == -1) return false;
	
	rlIdent = 0;
	riOTyp = 0;

	if (0 == GetItemText (iIndex, IDENT_COLUMN, m_pBuff, _MAX_PATH))
		return false;
	rlIdent = strtoul (m_pBuff, NULL, m_iIdBase);
	
	if (0 == GetItemText (iIndex, OTYP_COLUMN, m_pBuff, _MAX_PATH))
		return false;

	riOTyp = GetOTyp (m_pBuff);

return true;
}

short CSelIdentList :: GetOTyp (LPCSTR pTyp)
{
	switch (*pTyp) {
	case 'P':	return OTPunkt;
	case 'L':	return OTLinie;
	case 'F':	return OTFlaeche;
	case 'T':	return OTText;
	}

return 0;
}


void CSelIdentList :: FitColumn (int iCol)
{
int iCnt = GetItemCount();
int iMax = 0, iWidth = 0;
string str;

	for (int i = 0; i < iCnt; i++) {
		str = GetItemText (i, iCol);

		iWidth = GetStringWidth (str.c_str());
		if (iWidth > iMax) iMax = iWidth;
	}
	if (iMax > 0)
		SetColumnWidth (iCol, iMax+25);
}
