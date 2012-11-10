// Auswahl aller Objekte verschiedener Objektklassen --------------------------
// File: SELECTID.CXX

#include "triaspre.hxx"

#include "triasres.h"

#include <istatus.h>
#include <statguid.h>

#include <funcs03.h>
#include <ipropseq.hxx>
#include <selidprp.h>
#include <DstObWnd.h>
#include <DelObPrp.h>

#include "selectid.hxx"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's etc.
DefineSmartInterface(ProgressIndicator);

///////////////////////////////////////////////////////////////////////////////
// Objekte eines/mehrerer Idents selektieren 
#if !defined(_FORCE_LEGACY_CODE)
#if !defined(_USE_XML_GEOCOMPONENTS)

static const CLSID *cbSelIdClsIds[] = {
	&CLSID_SelectIdentObjTyp,
	&CLSID_DestinationObjectWindow,
};
#if !defined(_TRIAS_OLDIMPLEMTATION1)
static VARIANT *pvSelIdData[] = {
	NULL,
	NULL,
};
#endif // _TRIAS_OLDIMPLEMTATION1
static CALPCLSID calSelIdClsIds = {
	sizeof(cbSelIdClsIds)/sizeof(cbSelIdClsIds[0]),
	cbSelIdClsIds,
	NULL,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	const_cast<const VARIANT **>(pvSelIdData),
#endif // _TRIAS_OLDIMPLEMTATION1
};

bool IrisWind::doSelIdents (void)
{
	COM_TRY {
	ResString resCap (IDS_SELECTIDENT_CAPTION, 128);
	WProgressIndicator Status;

		Status.CreateInstance(CLSID_ProgressIndicator);
		if (Status.IsValid()) 
			Status -> InitNew (Handle(API_WINDOW_HWND), PIFLAG_RESULT);

	#if !defined(_TRIAS_OLDIMPLEMTATION1)
	CComVariant v (L"CheckMode=0;Checked=0;ShowConnections=1");

		pvSelIdData[0] = &v;		// Initialisierungsdaten setzen
	#endif // _TRIAS_OLDIMPLEMTATION1
		return SUCCEEDED(RunPropertyActionSequence (
					Handle(API_WINDOW_HWND), resCap, &calSelIdClsIds, NULL, NULL, NULL));
	} COM_CATCH_RETURN(false);
	return true;
}

#endif // !defined(_USE_XML_GEOCOMPONENTS)
#else // !_FORCE_LEGACY_CODE

///////////////////////////////////////////////////////////////////////////////
// externe Funktionen
HRESULT DeleteObjsInitProgress (HWND hWnd, int iCntSel, IProgressIndicator **ppIProgInd);

bool IrisWind::doSelIdents (void)
{
CSelectIdentDlg *pDlg = CSelectIdentDlg::CreateInstance (this, 
						IDD_SELECTIDENTSDLG, IDL_IDENTSLIST);
	if (pDlg == NULL) return false;
	
	pDlg -> Show (Centre);
	if (pDlg -> Result()) {		// OK gedrückt: Ident Enumerieren
	CEierUhr Wait (this);
	ObjFeld Objs;
	long lIdent = -1L;
	short iOTyp = 0;
	
		if (pDlg -> GetFirstIdent (lIdent, iOTyp)) {
			do {
				if (!AddObjects (Objs, lIdent, iOTyp))
					break;
			} while (pDlg -> GetNextIdent (lIdent, iOTyp));
		}
		if (Objs.Count()) {
		// Dialogfenster generieren
		DEXXCREATEOBJEKTINFO crOI;
		
			crOI.dwSize = sizeof(DEXXCREATEOBJEKTINFO);
			crOI.lpCaption = StrDupF (ResString (IDS_OBJINFOCAPTION, 30));
			crOI.lcObjs = &Objs;
			crOI.pcMColor = new Color (RED);
			crOI.ppntPos = new Point (0, 0);
			crOI.fcnPos = NULL;
			crOI.pData = NULL;
		
			DEXX_CreateObjektInfo (crOI);	// RechercheFenster generieren
		
			if (crOI.ppntPos) delete crOI.ppntPos;
			if (crOI.pcMColor) delete crOI.pcMColor;
			if (crOI.lpCaption) delete crOI.lpCaption;	// Speicher wieder freigeben
		}
	}
	DELETE_OBJ(pDlg);
	return true;
}
#endif // !_FORCE_LEGACY_CODE

///////////////////////////////////////////////////////////////////////////////
// Objekte eine oder mehrerer Idents löschen 
#if !defined(_FORCE_LEGACY_CODE)

#if !defined(_USE_XML_GEOCOMPONENTS)

static const CLSID *cbDelIdClsIds[] = {
	&CLSID_SelectIdentObjTyp,
	&CLSID_DeleteObjects,
};
#if !defined(_TRIAS_OLDIMPLEMTATION1)
static VARIANT *pvDelIdData[] = {
	NULL,
	NULL,
};
#endif // _TRIAS_OLDIMPLEMTATION1
static CALPCLSID calDelIdClsIds = {
	sizeof(cbDelIdClsIds)/sizeof(cbDelIdClsIds[0]),
	cbDelIdClsIds,
	NULL,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	const_cast<const VARIANT **>(pvDelIdData),
#endif // _TRIAS_OLDIMPLEMTATION1
};

bool IrisWind::doDelIdents (void)
{
	COM_TRY {
	ResString resCap (IDS_DELETEIDENT_CAPTION, 128);
	WProgressIndicator Status;

		Status.CreateInstance(CLSID_ProgressIndicator);
		if (Status.IsValid()) 
			Status -> InitNew (Handle(API_WINDOW_HWND), PIFLAG_RESULT);

	#if !defined(_TRIAS_OLDIMPLEMTATION1)
	CComVariant v (L"CheckMode=0;Checked=0;ShowConnections=1");

		pvDelIdData[0] = &v;		// Initialisierungsdaten setzen
	#endif // _TRIAS_OLDIMPLEMTATION1
		return SUCCEEDED(RunPropertyActionSequence(
					Handle(API_WINDOW_HWND), resCap, &calDelIdClsIds, Status, NULL, NULL));
	} COM_CATCH_RETURN(false);
	return true;
}

#endif // !defined(_USE_XML_GEOCOMPONENTS)

#else // !defined(_FORCE_LEGACY_CODE)

bool IrisWind::doDelIdents (void)
{
CSelectIdentDlg *pDlg = CSelectIdentDlg::CreateInstance (this, 
				IDD_DELETEIDENTSDLG, IDL_DELETEIDENTSLIST);
	if (pDlg == NULL) return false;
	
	pDlg -> Show (Centre);
	if (pDlg -> Result()) {		// OK gedrückt: Ident Enumerieren
	CEierUhr Wait (this);

	long lIdent = -1L;
	short iOTyp = 0;
	bool fDeleted = false;
	WProgressIndicator Status;
	ResString resUndo (IDS_UNDODELETEOBJECT, 30);
	int iCntSel = pDlg -> GetNoSelected();

		DEX_BeginUndoLevel (resUndo.Addr());
		DeleteObjsInitProgress (Handle(API_WINDOW_HWND), iCntSel*100, Status.ppi());		// Fehler nicht fatal

		if (pDlg -> GetFirstIdent (lIdent, iOTyp)) {
			iCntSel = 0;	// Zähler der Ident/OTypes

			do {
			ObjFeld Objs;

				if (!AddObjects (Objs, lIdent, iOTyp))
					break;

			long lObjCnt = Objs.Count();

				if (0 == lObjCnt) continue;
			
			CRing r(Objs);
			ErrInstall EI (EC_DELRECORD);
			bool fCanceled = false;
			int iCurr = 0;		// Zähler der Objekte dieses Ident/OTypes

				for (r.First(); r.Valid(); r.Next()) {
				ObjNummerLock l(r);
			
					TX_ASSERT(NULL != (ObjNummer *)l);
					DEX_DeleteObjectEx (l -> _ON);
					fDeleted = true;

				// StatusFenster weiterstellen
					if (NULL != (IProgressIndicator *)Status) {
						Status -> SetPosition(iCntSel*100+((iCurr++*100)/lObjCnt));
						if (Status -> WasCanceled()) {
							fCanceled = true;
							break;	// 'Abbrechen' gedrückt
						}
					}
				}
				if (fCanceled) break;	// 'Abbrechen' gedrückt

			// Identifikator/ObjektTyp aus IdentListe entfernen
				DBO().Idents().DeleteIdent (lIdent, iOTyp);

				iCntSel++;
			} while (pDlg -> GetNextIdent (lIdent, iOTyp));
		}

		if (!fDeleted) {
			DEX_CancelUndoLevel (false);
			return false;		// nichts gemacht
		}

		DEX_EndUndoLevel();

	// Legende auf den neuesten Stand bringen
		DEX_RefreshLegend();
		DEX_RepaintLegend();

		SetShouldRedraw (true);
		RePaint();	// Anzeige neu aufbauen
	}
	DELETE_OBJ(pDlg);
	return true;
}
#endif // !defined(_FORCE_LEGACY_CODE)

#if !defined(_USE_XML_GEOCOMPONENTS)
///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaften löschen
static const CLSID *cbDelObjPropClsIds[] = {
	&CLSID_SelectIdentObjTyp,
	&CLSID_DeleteObjectProperty,
};
#if !defined(_TRIAS_OLDIMPLEMTATION1)
static VARIANT *pvDelObjPropData[] = {
	NULL,
	NULL,
};
#endif // _TRIAS_OLDIMPLEMTATION1
static CALPCLSID calDelObjPropClsIds = {
	sizeof(cbDelObjPropClsIds)/sizeof(cbDelObjPropClsIds[0]),
	cbDelObjPropClsIds,
	NULL,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	const_cast<const VARIANT **>(pvDelObjPropData),
#endif // _TRIAS_OLDIMPLEMTATION1
};

bool IrisWind::doDeleteObjProps (void)
{
	COM_TRY {
	ResString resCap (IDS_DELETEOBJEPROP_CAPTION, 128);
	WProgressIndicator Status;

		Status.CreateInstance(CLSID_ProgressIndicator);
		if (Status.IsValid()) 
			Status -> InitNew (Handle(API_WINDOW_HWND), PIFLAG_RESULT);

	#if !defined(_TRIAS_OLDIMPLEMTATION1)
	CComVariant v (L"CheckMode=0;Checked=0;ShowConnections=1");

		pvDelObjPropData[0] = &v;		// Initialisierungsdaten setzen
	#endif // _TRIAS_OLDIMPLEMTATION1
		return SUCCEEDED(RunPropertyActionSequence (
					Handle(API_WINDOW_HWND), resCap, &calDelObjPropClsIds, NULL, NULL, NULL));
	} COM_CATCH_RETURN(false);
	return true;
}
#endif // !defined(_USE_XML_GEOCOMPONENTS)

///////////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CSelectIdentDlg::CSelectIdentDlg (pWindow pW, uint uiDlg)
		 : DialogWindow (pW, uiDlg),
		   m_pbOK (this, IDOK),
		   m_pbSelAll (this, IDB_ALLCLASSES)
{
	m_pIdents = NULL;
	m_pbOK.Disable();
	m_pbSelAll.Disable();
}

#pragma warning (default: 4355)

CSelectIdentDlg::~CSelectIdentDlg (void)
{
	DELETE_OBJ (m_pIdents);
}

CSelectIdentDlg *CSelectIdentDlg::CreateInstance (pWindow pW, uint uiDlg, uint uiList)
{
CEierUhr Wait (pW);
CSelectIdentDlg *pDlg = new CSelectIdentDlg (pW, uiDlg);

	if (pDlg == NULL || !pDlg -> FInit (uiList)) {
		DELETE_OBJ (pDlg);
		return NULL;
	}
	
return pDlg;
}

bool CSelectIdentDlg::FInit (uint uiList)
{
// IdentifikatorListBox füllen
	m_pIdents = new CSelIdentListViewWindow (this, uiList);
	if (m_pIdents == NULL) return false;

// Identifikatoren laden
DWORD dwMode = SELIDMODE_SINGLETYPE;

	if (DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) > 1) 
		dwMode |= SELIDMODE_SHOWCONNECTIONS;
	m_pIdents -> FInit();
	(*m_pIdents) -> InitControl (OTPunkt|OTLinie|OTFlaeche|OTText, dwMode, NULL, CmpEntries); 

// new for 'Nashville' (#HK960823)
#if defined(ListView_GetExtendedListViewStyle)
	if (IsWin40()) {
	DWORD dwStyleEx = (*m_pIdents) -> GetExtendedStyle();

		(*m_pIdents) -> SetExtendedStyle (dwStyleEx | LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP);
	}
#endif 

// Controls initialisieren
	if ((*m_pIdents) -> GetItemCount() > 0) 
		m_pbSelAll.Enable();		// Button SelectAll richten

	AdjustOK();

return true;
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler ---------------------------------------------------------------
void CSelectIdentDlg::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (1);
		break;
		
	case IDCANCEL:
		EndDlg (0);	// abbrechen
		break;
		
	case IDB_ALLCLASSES:	// alle markieren
		(*m_pIdents) -> ChangeSelectedAll(true);
		AdjustOK();
		break;
	}
}

// neues Item wurde ausgewählt ------------------------------------------------
void CSelectIdentDlg::OnItemChanged (NotifyEvt e)
{
NM_LISTVIEW *pNfyData = reinterpret_cast<NM_LISTVIEW *>(e.GetNotifyInfo());

	if (!(pNfyData -> uChanged & LVIF_STATE))
		return;		// Status nicht geändert

// Selektion erhalten/verloren
	if (pNfyData -> uOldState & LVIS_SELECTED ||
		pNfyData -> uNewState & LVIS_SELECTED)
	{
		AdjustOK();
	}
}

// HilfeRoutine ---------------------------------------------------------------
void CSelectIdentDlg::HelpRequest (HelpRequestEvt e)
{
const HELPINFO *pHI = e.GetHelpInfo();

	TX_ASSERT(pHI);
}

// Ein Eintrag wurde aus der Liste gelöscht -----------------------------------
void CSelectIdentDlg::OnDeleteItem (NotifyEvt e)
{
NM_LISTVIEW *pNLV = reinterpret_cast<NM_LISTVIEW *>(e.GetNotifyInfo());

	if (0 == pNLV -> iSubItem)	// ItemData freigeben
		(*m_pIdents) -> OnDeleteItem (pNLV);
}

void CSelectIdentDlg::OnDeleteAllItems (NotifyEvt)
{
	(*m_pIdents) -> OnDeleteAllItems();
}

///////////////////////////////////////////////////////////////////////////////
// HilfsRoutinen --------------------------------------------------------------
void CSelectIdentDlg::AdjustOK (void)
{
	if (!m_pIdents || (*m_pIdents) -> GetSelectedCount() == 0)
		m_pbOK.Disable();
	else
		m_pbOK.Enable();
}

///////////////////////////////////////////////////////////////////////////////
// AbfrageRoutinen ------------------------------------------------------------
bool CSelectIdentDlg::GetFirstIdent (long &rlIdent, short &riOTyp)
{
	if (m_pIdents) 
		return (*m_pIdents) -> GetFirstIdent (rlIdent, riOTyp);
		
return false;
}

bool CSelectIdentDlg::GetNextIdent (long &rlIdent, short &riOTyp)
{
	if (m_pIdents) 
		return (*m_pIdents) -> GetNextIdent (rlIdent, riOTyp);
		
return false;
}

bool CSelectIdentDlg::SelectIdent (long lIdent, short iOTyp, bool fSel)
{
	if (m_pIdents) {
	bool fResult = (*m_pIdents) -> SelectIdent (lIdent, iOTyp, fSel);

		AdjustOK();
		return fResult;
	}
		
return false;
}

///////////////////////////////////////////////////////////////////////////////
// Durchschreiben der Visinfo in eine andere Sicht
//
#pragma warning (disable: 4355)

CCopyVisInfoDlg::CCopyVisInfoDlg (pWindow pW, uint uiDlg)
		 : CSelectIdentDlg (pW, uiDlg),
		   m_rbDefaultView (this, IDR_DEFAULTVIEW),
		   m_rbOtherView (this, IDR_VIEWNAME),
		   m_cbViewNames (this, IDCB_VIEWNAMES)
{
	m_rbDefaultView.SetState (true);	// am Anfang StandardSicht
	m_rbOtherView.SetState (false);
	m_rbOtherView.Disable();
	m_cbViewNames.Disable();
}

#pragma warning (default: 4355)

CCopyVisInfoDlg::~CCopyVisInfoDlg (void)
{
	// nothing else do do
}

CCopyVisInfoDlg *CCopyVisInfoDlg::CreateInstance (pWindow pW, uint uiDlg, uint uiList)
{
CEierUhr Wait (pW);
CCopyVisInfoDlg *pDlg = new CCopyVisInfoDlg (pW, uiDlg);

	if (pDlg == NULL || !pDlg -> FInit (uiList)) {
		DELETE_OBJ (pDlg);
		return NULL;
	}

return pDlg;
}

extern "C" BOOL WINAPI FillViewList (char *pPtr, BOOL, void *pCB);

bool CCopyVisInfoDlg::FInit (uint uiList)
{
// Initialisierung der BasisKlasse
	if (!CSelectIdentDlg::FInit (uiList)) return false;

// ComboBox mit allen SichtNamen füllen
ENUMNOKEY ENK;

	ENK.eFcn = (ENUMNOKEYPROC)FillViewList;
	ENK.ePtr = &m_cbViewNames;

bool fResult = DEX_EnumSights (ENK);

// wenn keine Sichten da sind, dann RadioButton passiviert lassen
	if (fResult && m_cbViewNames.GetCount() > 0) {
	char cbActView[MAXVIEWNAMESIZE+1];

		if (DEX_GetActiveSight (cbActView)) {
		int iIndex = m_cbViewNames.FindString (cbActView, true);

			if (iIndex != -1) m_cbViewNames.DelString (iIndex);
		}
		m_cbViewNames.ChangeCurrentIndex (0);
		m_rbOtherView.Enable();
	}

	AdjustOK();

return fResult;
}

// EventHandler ---------------------------------------------------------------
void CCopyVisInfoDlg::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDR_DEFAULTVIEW:
		m_cbViewNames.Disable();
		m_rbDefaultView.SetState (true);
		m_rbOtherView.SetState (false);
		AdjustOK();
		break;

	case IDR_VIEWNAME:
		m_cbViewNames.Enable();
		m_rbDefaultView.SetState (false);
		m_rbOtherView.SetState (true);
		AdjustOK();
		break;

	default:
		CSelectIdentDlg::ButtonClick (e);
	}
}

// HilfeRoutine ---------------------------------------------------------------
void CCopyVisInfoDlg::HelpRequest (HelpRequestEvt e)
{
const HELPINFO *pHI = e.GetHelpInfo();

	TX_ASSERT(pHI);
}

// Auswahl in ComboBox --------------------------------------------------------
void CCopyVisInfoDlg::ListBoxSel (ControlEvt e)
{
	AdjustOK();
}

///////////////////////////////////////////////////////////////////////////////
// HilfsRoutinen --------------------------------------------------------------
void CCopyVisInfoDlg::AdjustOK (void)
{
	if (m_rbOtherView.GetState() &&
	    (m_cbViewNames.GetCount() == 0 || m_cbViewNames.GetCurrentIndex() == -1))
		m_pbOK.Disable();
	else
		CSelectIdentDlg::AdjustOK();
}

bool CCopyVisInfoDlg::GetViewName (char *pView, int iLen)
{
	if (m_rbDefaultView.GetState()) {
	ResString resDef(IDS_DEFAULTVISINFO, 40);
	int iToCopy = min(iLen-1, resDef.Len());

		strncpy (pView, resDef, iToCopy);
		pView[iToCopy] = '\0';
		return true;
	}

	if (m_rbOtherView.GetState()) {
	int iIndex = m_cbViewNames.GetCurrentIndex();

		if (iIndex != -1) {
			m_cbViewNames.GetString (pView, iIndex, iLen);
			return true;
		}
	}

return false;
}

