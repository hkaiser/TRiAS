// Dialog, welcher einen Ident auswählbar macht, um Objekte umzuklassifizieren
// File: MODIDENT.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <funcs02.h>
#include <funcs03.h>
#include <xtsnguid.h>
#include <eonrguid.h>
#include <propguid.h>
#include <statguid.h>

#include <eieruhr.hxx>
#include <IPropSeq.hxx>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "enumonr.hxx"
#include "modident.hxx"
#include "modidprp.hxx"

// JG 980918
#include "ownmacros.h"

///////////////////////////////////////////////////////////////////////////////
//
short OTypToBits (ObjTyp iOTyp);

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ObjectWithSite);
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(DataObject);
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG

///////////////////////////////////////////////////////////////////////////////
//
extern char g_pDLLName[_MAX_PATH];

// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CModifyIdentDlg::CModifyIdentDlg (CModIDPropAct *pParent, ResID uiDlg, 
									LPCSTR pcCaption)
		 : CPropertyPage (uiDlg, pcCaption),
		   m_cbAddToView (this, IDC_ADDTOVIEW),
		   m_ftAdjustIdent (this, IDC_STATIC_SELECTIDENT),
		   m_cbAdjustIdent (this, IDC_CHECK_SELECTIDENT),
		   m_pbDefine (this, IDC_DEFINENEW),
		   m_dwFlags(0), m_pParent(pParent)
{
	m_pIdents = NULL;	// ListViewCtrl

	m_lResult = 0;		// ErgebnisIdent
	m_fAddToView = true;
	m_fShowConnections = true;
	m_fCheckMode = false;
	m_fCheckModeChecked = false;
	m_iCopyMode = 0;

	m_pIEnumObjs = NULL;
}

#pragma warning (default: 4355)

CModifyIdentDlg::~CModifyIdentDlg (void)
{
	DELETE_OBJ (m_pIdents);
	if (m_pIEnumObjs) m_pIEnumObjs -> Release();
}

CModifyIdentDlg *CModifyIdentDlg::CreateInstance (
		CModIDPropAct *pParent, ResID resID, LPCSTR pcCaption)
{
	try {
	CModifyIdentDlg *pDlg = NULL;
	
		pDlg = new CModifyIdentDlg (pParent, resID, pcCaption);
		if (pDlg == NULL || !pDlg -> FInit()) {
			DELETE_OBJ (pDlg);
			return NULL;
		}
		return pDlg;
	} catch (...) {
		return NULL;
	}
}

bool CModifyIdentDlg::FInit (void)
{
// IdentifikatorListBox füllen
	m_pIdents = new CSelIdentListViewWindow (this, IDC_LISTDESTIDENTS);
	if (m_pIdents == NULL) return false;

	m_pIEnumObjs = NULL;
	CoCreateInstance (CLSID_EnumObjectsByNumber, NULL, CLSCTX_INPROC_SERVER,
					  IID_IEnumLONG, (LPVOID *)&m_pIEnumObjs);

	return (NULL != m_pIEnumObjs) ? true : false;
}

void CModifyIdentDlg::SetFlags (DWORD dwFlags)
{
	m_dwFlags = dwFlags;
}

DWORD __stdcall EnsureUnique (INT_PTR lIdent, DWORD dwTypes, UINT_PTR dwData)
{
CSelIdentListViewWindow *pIdents = reinterpret_cast<CSelIdentListViewWindow *>(dwData);
os_string strOKS;
char cbBuffer[_MAX_PATH];

// Objektklassenschlüssel besorgen
	ClassFromIdent (lIdent, cbBuffer);
	strOKS = cbBuffer;

// KurzText besorgen
PBDDATA pbdData;

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = cbBuffer;
	pbdData.pbdKTextLen = sizeof(cbBuffer) -1;
	DEX_GetPBDData (pbdData);

LVFINDINFO lvfi;

	lvfi.flags = LVFI_STRING;
	lvfi.psz = strOKS.c_str();

int iIndex = -1;

	while (-1 != (iIndex = (*pIdents) -> FindItem (&lvfi, iIndex))) {
	os_string strItem = (*pIdents) -> GetItemText (iIndex, GetColIndex(KTEXT_COLUMN, SELIDMODE_NOICONS));

		if (strItem == cbBuffer)
			return 0L;	// existiert bereits in der Liste
	}
	return dwTypes;		// alle einfügen
}

bool CModifyIdentDlg::ReInitList()
{
DWORD dwMode = SELIDMODE_NOICONS|SELIDMODE_ALLIDENTSPBD|SELIDMODE_ONLYWRITABLE|SELIDMODE_NOQUERYDEFS;
int iTypes = OTPunkt|OTLinie|OTFlaeche|OTText;
ADDENTRYPROC pEntryProc = EnsureUnique;

	if (m_fShowConnections && DEX_GetOpenConnectionCount (QDCAllOpen) > 1) {
		dwMode |= SELIDMODE_SHOWCONNECTIONS;
		pEntryProc = NULL;		// doch alle Einträge anzeigen
	}
	if (!(*m_pIdents) -> InitControl(iTypes, dwMode, NULL, CmpEntries, (DWORD)m_pIdents, pEntryProc))
		return false;

// vorhergehende Einstellungen wieder einstellen
	if (0 != m_lResult) {
	int iIndex = SelectIdent (m_lResult);

		if (-1 != iIndex) {	// Focus setzen, ins Bild rollen
			(*m_pIdents) -> EnsureVisible (iIndex, false);
			(*m_pIdents) -> SelectItemFocus (iIndex);
		}
		m_cbAddToView.SetChecked (m_fAddToView);
	}
	return true;
}

// Der wohl wichtigste Unterschied zu einem normalen Dialogfenster besteht
// darin, daß alle Controls dieser Dialogseite explizit im WindowInit()-Event-
// handler initialisiert werden müssen (s.u.). Alle inhaltlichen Initialisierungen
// können erst danach erfolgen (und nicht wie gewohnt im Konstruktor)
void CModifyIdentDlg::WindowInit (Event)
{
CEierUhr Wait (this);		// EierUhr anzeigen

// ListViewCtrl initialisieren/Identifikatoren laden
	if (NULL == m_pIdents || !m_pIdents -> FInit() || !ReInitList())
		return;
	
// new for 'Nashville' (#HK960823)
#if defined(ListView_GetExtendedListViewStyle)
	if (IsWin40()) {
	DWORD dwStyleEx = (*m_pIdents) -> GetExtendedStyle();

		(*m_pIdents) -> SetExtendedStyle (dwStyleEx | LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_INFOTIP);
	}
#endif 

// Mode voreinstellen: Text ist eingeblendet und Checkbox ist aus (alter Mode)
	m_ftAdjustIdent.FInit();
	m_cbAdjustIdent.FInit();
	AdjustCheckMode();

	m_cbAddToView.FInit();
	m_cbAddToView.SetChecked (true);

	m_pbDefine.FInit();
//	m_pbDefine.Disable();

	AdjustOK();

// vorhergehende Einstellungen wieder einstellen
	if (0 != m_lResult) {
	int iIndex = SelectIdent (m_lResult);

		if (-1 != iIndex) {	// Focus setzen, ins Bild rollen
			(*m_pIdents) -> EnsureVisible (iIndex, false);
			(*m_pIdents) -> SelectItemFocus (iIndex);
		}
		m_cbAddToView.SetChecked (m_fAddToView);
	}
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler ---------------------------------------------------------------
void CModifyIdentDlg::OnItemChanged (NotifyEvt e)
{
NM_LISTVIEW *pNfyData = reinterpret_cast<NM_LISTVIEW *>(e.GetNotifyInfo());

	if (!(pNfyData -> uChanged & LVIF_STATE))
		return;		// Status nicht geändert

// Selektion erhalten/verloren
	if (pNfyData -> uOldState & LVIS_SELECTED || pNfyData -> uNewState & LVIS_SELECTED)
		AdjustOK();
}

int CModifyIdentDlg::OnSetActive (NotifyEvt)
{
	m_pParent -> ReInitFromData();
	AdjustCheckMode();
	AdjustOK();
	return 0;
}

// Der Dialog wurde mit Cancel geschlossen ------------------------------------
void CModifyIdentDlg::OnCancel (NotifyEvt)
{
	// hier evtl. Aufräumarbeiten durchführen
}

int CModifyIdentDlg::OnWizNext (NotifyEvt)
{
	if (PrepareResult()) 	// Ergebnisse zwischenspeichern
		return 0;

	return -1;
}

// Finish wurde gedrückt ------------------------------------------------------
int CModifyIdentDlg::OnWizFinish (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return 0;
}

void CModifyIdentDlg::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDC_CHECK_SELECTIDENT:
		{
			if (!m_fCheckMode)
				return;

			CPropertyPage::ButtonClick(e);
			m_fCheckModeChecked = m_cbAdjustIdent.isChecked();
			AdjustCheckMode();
			AdjustOK();
		}
		break;

	case IDC_DEFINENEW:
		{
		DEFINEIDENTDLG DlgData;

			INITSTRUCT(DlgData, DEFINEIDENTDLG);
			DlgData.hWnd = Handle(API_WINDOW_HWND);
			DlgData.lIdent = 0;
			DlgData.hPr = HACTCONNECTION;

		long lIdent = DEX_DefineNewObjectsDesc(DlgData);	// neue Identbeschreibung erzeugen

		// Daten neu einlesen, dazu ListViewCtrl initialisieren/Identifikatoren laden
			if (0 != lIdent) {
				TX_ASSERT(NULL != m_pIdents);
				(*m_pIdents) -> FillWithData (true);
				(*m_pIdents) -> SelectIdent (lIdent, 0, true);
			}

			if (m_fCheckMode && !m_fCheckModeChecked) {
				m_fCheckModeChecked = true;
				AdjustCheckMode();
			}
		}
		break;

	default:
		break;
	}
}

//void CModifyIdentDlg::OnClick (NotifyEvt e)
//{
//NMHDR *pNMHdr = e.GetNotifyInfo();
//POINT pt;
//
//	GetCursorPos (&pt);
//	ScreenToClient (pNMHdr -> hwndFrom, &pt);
//	pt.x = 1;	// ganz am linken Rand testen
//
//UINT uiFlags = 0L;
//int iIndex = (*m_pIdents) -> HitTest ((Point &)pt, &uiFlags);
//
//	if (uiFlags & LVHT_ONITEM && 0 <= iIndex) {
//		(*m_pIdents) -> SetItemState (iIndex, LVIS_SELECTED|LVIS_FOCUSED, 
//								   LVIS_SELECTED|LVIS_FOCUSED);
//		(*m_pIdents) -> Update (iIndex);
//	}
//}

// HilfeRoutine ---------------------------------------------------------------
void CModifyIdentDlg::HelpRequest (HelpRequestEvt e)
{
const HELPINFO *pHI = e.GetHelpInfo();

	TX_ASSERT(pHI);
}

///////////////////////////////////////////////////////////////////////////////
// Fragt den Dialog nach seinen Daten 

namespace {

// umklassifizieren (Datenquelle bleibt gleich)
	BOOL ModObjectIdent(HOBJECT lONr, HOBJECTS lIdent, BOOL fAddToView)
	{
		if (DEX_GetObjIdent(lONr) == lIdent)
			return TRUE;		// nothing to do

	MODOBJIDENT MOI;

		INITSTRUCT(MOI, MODOBJIDENT);
		MOI.lONr = lONr;
		MOI.lNewIdent = lIdent;
		MOI.iMode = OTypToBits ((ObjTyp)DEX_GetObjectType(lONr));
		if (fAddToView)
			MOI.iMode |= MODIDENT_ADDTOVIEW;
		return DEX_ModObjectIdentEx (MOI);		// mit Undo
	}

	HOBJECT CopyObject(HPROJECT hPr, HOBJECT lONr, HOBJECTS lIdent, BOOL fAddToView)
	{
	// Objekt kopieren _und_ umklassifizieren
	CLONEOBJECT CO;

		INITSTRUCT(CO, CLONEOBJECT);
		CO.lONrToCopy = lONr;
		CO.lNewIdent = lIdent;
		if (DEX_CloneObjectEx(hPr, CO)) {
		// ggf. Objektklasse zur Ansicht hinzunehmen
			if (fAddToView) {
			VIEWIDENTOBJECT VIO;

				INITSTRUCT(VIO, VIEWIDENTOBJECT);
				VIO.m_pView = NULL;
				VIO.m_lIdent = lIdent;
				VIO.m_iOTyp = OTypToBits ((ObjTyp)DEX_GetObjectType(CO.lNewONr));
			}
			return CO.lNewONr;
		}
		return INVALID_HOBJECT;
	}
}

HRESULT CModifyIdentDlg::GetEnumLONG (IEnum<LONG> **ppIEnum)
{
	if (NULL == ppIEnum) return E_POINTER;
	if (NULL == m_pIEnumObjs) return E_OUTOFMEMORY;

	*ppIEnum = NULL;

// IEnumLONG erzeugen und während der iteration neu füllen
WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);				// Ausgabeobjektmenge

	{
	OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));

	// Verarbeitungsteil
	INT_PTR lONr;
	ResourceFile RF (g_pDLLName);
	ResString resUndo (ResID(IDS_UNDOMODIDENTS, &RF), 128);

	// JG980914 Ermitteln der Anzahl der Operationen
	long counter = m_pIEnumObjs -> Count();
	long ind = 0;		// zum Abbruch testen
	long lCnt = 0;

		SetMaxTicks(counter);	

	HPROJECT hPrCls = DEX_GetObjectsProject (m_lResult);
	os_string strKText, strLText, strOKS;

		RETURN_FAILED_HRESULT(RetrieveObjClassDesc (m_lResult, strOKS, strKText, strLText));

		D_OUTF(3, "Objektklasse modifizieren: %lx\r\n", m_lResult); 
		DEX_BeginUndoLevel(resUndo.Addr());
		for (m_pIEnumObjs -> Reset(); S_OK == m_pIEnumObjs -> Next (1, &lONr, NULL); /**/) {
		// sicherstellen, daß in der Ziel-(Objekt-)datenquelle diese Objektklasse vorhanden ist
		LONG lIdent = m_lResult;

			D_OUTF(3, "Objekt: %lx\r\n", lONr);
			if (FAILED(EnsureObjClass (hPrCls, strOKS.c_str(), strKText.c_str(), 
				strLText.c_str(), lONr, &lIdent)))
			{
				continue;		// irgend ein blöder Fehler
			}
			_ASSERTE(0 != lIdent);

			switch (m_iCopyMode) {
			default:
			case 0:
				{
				// Objekt bleibt in seiner Datenquelle
					_ASSERTE(DEX_GetObjectsProject(lIdent) == DEX_GetObjectProject(lONr));

				// umklassifizieren (Datenquelle bleibt gleich)
					ModObjectIdent(lONr, lIdent, m_fAddToView);
					++iter_out = lONr;
				} 
				break;

#if _TRiAS_VER >= 0x0420
			case 1:
				{
				// Objekt kopieren _und_ umklassifizieren
				HOBJECT lNewONr = CopyObject(hPrCls, lONr, lIdent, m_fAddToView);

					if (INVALID_HOBJECT != lNewONr)
						++iter_out = lNewONr;
				}
				break;

#if _TRiAS_VER >= 0x0500
			case 2:
				{
				// Objekt kopieren, wenn neue Datenquelle, ansonsten nur
				// umklassifizieren
					if (DEX_GetObjectsProject(lIdent) == DEX_GetObjectProject(lONr)) {
					// umklassifizieren (Datenquelle bleibt gleich)
						ModObjectIdent(lONr, lIdent, m_fAddToView);
						++iter_out = lONr;
					}
					else {
					HOBJECT lNewONr = CopyObject(hPrCls, lONr, lIdent, m_fAddToView);

						if (INVALID_HOBJECT != lNewONr)
							++iter_out = lNewONr;
					}
				}
				break;

			case 3:
				{
				// Objekt kopieren, wenn neue Datenquelle, ansonsten nur
				// umklassifizieren, anschließend altes Objekt weglöschen
					if (DEX_GetObjectsProject(lIdent) == DEX_GetObjectProject(lONr)) {
					// umklassifizieren (Datenquelle bleibt gleich)
						ModObjectIdent(lONr, lIdent, m_fAddToView);
						++iter_out = lONr;
					}
					else {
					HOBJECT lNewONr = CopyObject(hPrCls, lONr, lIdent, m_fAddToView);

						if (INVALID_HOBJECT != lNewONr) {
							++iter_out = lNewONr;
							DEX_DeleteObjectEx(lONr);
						}
					}
				}
				break;
#endif // _TRiAS_VER >= 0x0500
#endif // _TRiAS_VER >= 0x0420
			}

		// JG Abbruchhandling, aller 50 Objekte mal nachgucken
			Tick();
			if (++ind >= 50) {
				if (S_OK != GoOn())	{
				// den aktuellen Undo Level zurücksetzen
					DEX_CancelUndoLevel(true);
					return E_ABORT;
				}
				ind = 0;				// Zähler neu starten
			}
			lCnt++;
		}

		DEX_EndUndoLevel();
		DEX_RefreshLegend();
		DEX_RepaintLegend();
		
		D_OUTF(3, "Objektklasse für %ld Objekte modifiziert.\r\n", lCnt);
	} // iter_out goes out of scope

// Menge der Objekte liefern
	*ppIEnum = EnumOut.detach();

// explizit Statusanzeige auf 100 %
	TickToEnd();
	return S_OK;
}

// alle Infos über eine Objektklasse besorgen
HRESULT CModifyIdentDlg::RetrieveObjClassDesc (
	LONG lIdent, os_string &rStrOKS, os_string &rStrKText, os_string &rStrLText)
{
PBDDATA pbdData;
char cbKText[34] = { '\0' };
char cbLText[5*_MAX_PATH] = { '\0' };

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = lIdent;
	pbdData.pbdKText = cbKText;
	pbdData.pbdLText = cbLText;
	pbdData.pbdKTextLen = sizeof(cbKText) -1;
	pbdData.pbdLTextLen = sizeof(cbLText) -1;
	
ErrCode RC = DEX_GetPBDData (pbdData);

	if (EC_OKAY != RC && WC_RETURN != RC)
		return HRESULT_FROM_ERRCODE(WC_NOTFOUND);

	rStrKText = cbKText;
	rStrLText = cbLText;
	
	cbLText[0] = '\0';

HRESULT hr = ClassFromIdent (lIdent, cbLText);

	rStrOKS = cbLText;
	return hr;
}

// sicherstellen, daß in der Zieldatenquelle diese Objektklasse vorhanden ist
HRESULT CModifyIdentDlg::EnsureObjClass (
	HPROJECT hPrCls, LPCSTR pcOKS, LPCSTR pcKText, LPCSTR pcLText, LONG lONr, LONG *plIdent)
{
	COM_TRY {
	HPROJECT hPrObj = DEX_GetObjectProject(lONr);

		if (hPrCls != hPrObj) {
		// nur wenn Objektklasse aus anderer Datenquelle kommt
		LONG lIdent = DEX_GetIdentFromClassNameEx (hPrObj, pcKText);

			if (0 == lIdent) {
			// muß neu erzeugt werden
				IdentFromClass (hPrObj, pcOKS, (ULONG *)&lIdent, TRUE);		// ggf. neuen Ident erzeugen

			// Beschreibungsdaten erzeugen
			PBDDATA pbdData;

				INITSTRUCT(pbdData, PBDDATA);
				pbdData.pbdTyp = 'i';
				pbdData.pbdCode = lIdent;
				pbdData.pbdKText = (LPSTR)pcKText;
				pbdData.pbdLText = (LPSTR)pcLText;
				pbdData.pbdKTextLen = (NULL != pcKText) ? strlen(pcKText) : 0;
				pbdData.pbdLTextLen = (NULL != pcLText) ? strlen(pcLText) : 0;
				DEX_ModPBDDataEx (hPrObj, pbdData);
				lIdent = pbdData.pbdCode;		// kann sich geändert haben
			}
			*plIdent = lIdent;
		} 
	} COM_CATCH;
	return  S_OK;
}

// Übergibt die zu verarbeitende Objektmenge ----------------------------------
HRESULT CModifyIdentDlg::SetEnumLONG (IEnum<LONG> *pIEnum)
{
	// JG
	LONG lONr;
	if (m_pIEnumObjs)
	{
		for (pIEnum -> Reset(); S_OK == pIEnum -> Next (1, &lONr, NULL);/**/)
		{
			// und zu lokalem Enumerator aller umklassifizieren Objekte hinzufügen
			m_pIEnumObjs -> AddItem (lONr);
		}
	}

	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// HilfsRoutinen 
void CModifyIdentDlg::AdjustCheckMode()
{
	if (m_fCheckMode) {
		m_ftAdjustIdent.Disable();
		m_ftAdjustIdent.Hide();
		m_cbAdjustIdent.Enable();
		m_cbAdjustIdent.Show();
		if (m_fCheckModeChecked) {
			m_cbAdjustIdent.SetChecked (TRUE);
			(*m_pIdents) -> Enable();
			m_cbAddToView.Enable();
		} else {
			m_cbAdjustIdent.SetChecked (FALSE);
			(*m_pIdents) -> Disable();
			m_cbAddToView.Disable();
		}
	} else {
		m_ftAdjustIdent.Enable();
		m_ftAdjustIdent.Show();
		m_cbAdjustIdent.Disable();
		m_cbAdjustIdent.Hide();

		m_cbAddToView.Enable();
		(*m_pIdents) -> Enable();
	}
}

void CModifyIdentDlg::AdjustOK (bool fDisableNext)
{
DWORD dwBttns = 0;
int iCnt = (*m_pIdents) -> GetSelectedCount();
bool fEnable = (0 < iCnt) || (m_fCheckMode && !m_fCheckModeChecked);

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns |= PSWIZB_BACK;

	if (fEnable && !fDisableNext) {
		if (m_dwFlags & ADDPAGES_LASTPAGE)
			dwBttns |= PSWIZB_FINISH;
		else
			dwBttns |= PSWIZB_NEXT;
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	SetSheetWizardButtons (dwBttns);
}

// Ergebnisdaten aus Controls lesen und zwischenspeichern ---------------------
bool CModifyIdentDlg::PrepareResult (void)
{
// Daten (Ident) aus Page lesen und speichern
bool fHasIdent = GetSelectedIdent (m_lResult);

	TX_ASSERT(!fHasIdent || IsValidIdent(m_lResult));

	m_fAddToView = m_cbAddToView.isChecked() ? true : false;
	if (m_fCheckMode) {
		m_fCheckModeChecked = m_cbAdjustIdent.isChecked() ? true : false;
		if (!m_fCheckModeChecked) return true;
	}

// ProjektHandle der ausgewählten Datenquelle im KontextObjekt ablegen
	if (fHasIdent) 
		PrepareResultIdent();
	return fHasIdent;
}

void CModifyIdentDlg::PrepareResultIdent()
{
	if (0 == m_lResult)
		return;		// nur, wenn Ident gegeben ist

	COM_TRY {
	WDataObject DO;
	WPropertyActionSequence Seq;

		THROW_FAILED_HRESULT(WObjectWithSite(m_pParent) -> GetSite (IID_IPropertyActionSequence, Seq.ppv()));
		THROW_FAILED_HRESULT(Seq -> GetSequenceContext (DO.ppi()));

	CComVariant vData (reinterpret_cast<LONG>(DEX_GetObjectsProject (m_lResult)), VT_I4);

		THROW_FAILED_HRESULT(SetVariantData (vData, DO, &c_feDataSourceHandle));

	} COM_CATCH_IGNORE;
}

///////////////////////////////////////////////////////////////////////////////
// AbfrageRoutinen ------------------------------------------------------------
bool CModifyIdentDlg::GetSelectedIdent (long &rlIdent)
{
short iOTyp = 0;	// dummy

	if (m_pIdents) 
		return (*m_pIdents) -> GetFirstIdent (rlIdent, iOTyp);
		
	return false;
}

int CModifyIdentDlg::GetItemCount (void)
{
	if (m_pIdents) 
		return (*m_pIdents) -> GetItemCount();
		
return 0;
}

int CModifyIdentDlg::SelectIdent (long lIdent, bool fSel)
{
	if (m_pIdents) {
	int fResult = (*m_pIdents) -> SelectIdent (lIdent, 0, fSel);

		AdjustOK();
		return fResult;
	} else if (fSel)
		m_lResult = lIdent;		// lediglich vormerken
		
return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CModifyIdentDlg::SetDirty (bool fDirty)
{ 
	if (m_pParent) m_pParent -> SetDirty (fDirty); 
}
