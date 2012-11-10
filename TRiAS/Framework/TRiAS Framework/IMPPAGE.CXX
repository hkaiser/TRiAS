// Implementor der CPropertyPage-Klasse ---------------------------------------
// File IMPPPAGE.CXX

#include "tfrmpre.hxX"
#include <_Link.hxx>   

// Konstruktor/Destruktor/Initialisierung -------------------------------------
PPageWind_Imp :: PPageWind_Imp (CPropertyPage *pPage, ResID RscID, 
				LPCSTR pCaption)
	       : DWind_Imp (pPage)
{
	dialogID  = (uint)RscID;

	m_hPage = NULL;
	m_nPage = 0;

	m_pcHeaderTitle = NULL;
	m_pcHeaderSubTitle = NULL;

// CreatePropertySheetPage vorbereiten, erfolgt dann in CreatePage
DWORD dwFlags = PSP_DEFAULT;
pApp_Imp AppImpInst = _AppImpFind();

	DlgFlags.IsShown = 0;
	DlgFlags.fParentsDisabled = false;

	if (NULL != pCaption) {
		dwFlags |= PSP_USETITLE;
		WndCapt = CV_strdup (pCaption);	// Take a copy
	}
	WindMgt.isPropPage = true;

	memset (&m_psp, 0, sizeof(PROPSHEETPAGE));
	m_psp.dwSize = sizeof(PROPSHEETPAGE);
	m_psp.dwFlags = dwFlags;
	m_psp.hInstance = CV_RunTime::ResID_handle (RscID, AppImpInst, RT_DIALOG);
	m_psp.pszTemplate = (char *)((ulong)((uint)dialogID));
	m_psp.pszIcon = NULL;
	m_psp.pfnDlgProc = (DLGPROC)PropertyPageDispatcher;
	m_psp.pszTitle = WndCapt;
	m_psp.lParam = (DWORD)this;
}

PPageWind_Imp :: ~PPageWind_Imp (void)
{
	if (NULL != m_pcHeaderSubTitle) {
		delete (char *)m_pcHeaderSubTitle;
		m_pcHeaderSubTitle = NULL;
	}
	if (NULL != m_pcHeaderTitle) {
		delete (char *)m_pcHeaderTitle;
		m_pcHeaderTitle = NULL;
	}
}

PSheetWind_Imp *PPageWind_Imp :: GetPSheetImp (void)
{
	return (PSheetWind_Imp *)WndParent;
}

BOOL PPageWind_Imp :: FInit (HWND hWnd)
{
	if (NULL == hWnd) 
		return false;

// zugehörigen PropertySheet initialisieren
pApp_Imp pAppImpInst = _AppImpFind();

	CV_ASSERT(IsWindow(hWnd) && IsWindow(::GetParent(hWnd)));
	if (!WndParent) 
		WndParent = (pWind_Imp)(pAppImpInst -> ContextList() -> Find ((HANDLE)::GetParent(hWnd)));

	if (WndParent) {
		if (!((PSheetWind_Imp *)WndParent) -> FInit (::GetParent(hWnd)))
			return false;
		WindMgt.isModal = WndParent -> WindMgt.isModal;
	}

	hEContext = hModeless = hWnd;
	pAppImpInst -> ContextList() -> Insert ((HANDLE)hEContext, this);

// Caption merken
char cbBuffer[129];

	if (GetWindowText (hEContext, cbBuffer, 128)) {
		cbBuffer[128] = '\0';
		SetCaption (cbBuffer);
	}

// FensterGröße initialisieren
	InitSize();

Rectangle r ;

	GetClientRect (hEContext, (RECT *)&r);

long lDBUnits = GetDialogBaseUnits();

	Xbase = LOWORD(lDBUnits) ;
	Ybase = HIWORD(lDBUnits) ;

	Xchars = r.Right()/Xbase;
	Ychars = r.Bottom()/Ybase;

	if (!WindMgt.Initialised)
        	Initialise();

return true;
}

// Erzeugen dieser PropertyPage -----------------------------------------------
HPROPSHEETPAGE PPageWind_Imp :: CreatePage (PSheetWind_Imp *pSheet)
{
	if (NULL == m_hPage) {	// nur einmal rufen
		m_hPage = CreatePropertySheetPage (&m_psp);
		WndParent = pSheet;		// Rückverweis
	}

return m_hPage;
}

// Sonstige Member ------------------------------------------------------------
void PPageWind_Imp :: CancelToClose (void)
{
	CV_ASSERT_VALID(hEContext);

	PropSheet_CancelToClose (::GetParent(hEContext));
}

void PPageWind_Imp :: SetModified (BOOL bChanged)
{
	CV_ASSERT_VALID(hEContext);

	if (bChanged)
		PropSheet_Changed (::GetParent(hEContext), hEContext);
	else
		PropSheet_UnChanged (::GetParent(hEContext), hEContext);
}

// Icon für TabLasche setzen --------------------------------------------------
void PPageWind_Imp :: SetIcon (ResID resID)
{
	if (NULL != hEContext) return;	// bereits angezeigt, zu spät

pApp_Imp pAppImpInst = _AppImpFind();

	m_psp.hIcon = LoadIcon (CV_RunTime::ResID_handle (resID, pAppImpInst, RT_ICON),
				(char *)((ulong)((uint)resID)));
	if (NULL != m_psp.hIcon) 
		m_psp.dwFlags |= PSP_USEHICON;
}

void PPageWind_Imp :: SetIcon (Icon_Imp *pIcon)
{
	if (NULL != hEContext) return;	// bereits angezeigt, zu spät

	m_psp.hIcon = CV_RunTime::IconImp_hIcon(pIcon);
	if (NULL != m_psp.hIcon) 
		m_psp.dwFlags |= PSP_USEHICON;
}

LRESULT PPageWind_Imp::QuerySiblings (WPARAM wParam, LPARAM lParam)
{
	return PropSheet_QuerySiblings(::GetParent(hEContext), wParam, lParam);
}

void PPageWind_Imp::SetSheetWizardButtons (DWORD dwFlags)
{
	PropSheet_SetWizButtons (::GetParent(hEContext), dwFlags);
}

void PPageWind_Imp::PressSheetButton (DWORD dwFlags)
{
	PropSheet_PressButton(::GetParent(hEContext), dwFlags);
}

// Standardbehandlung der Events ----------------------------------------------
void PPageWind_Imp :: Default (Event e)
{
	 CV_RunTime::EC_SetRetval (this, 0L);
	 SetDlgMsgResult (hEContext, CV_RunTime::Event_wMsg(e), false);
}	// End of "PPageWind_Imp" FUNCTION "Default"


// Dispatch/Notifications -----------------------------------------------------
LRESULT PPageWind_Imp :: Dispatch (Event e)
{
LRESULT lRetVal = true;
LRESULT	*pOldPtr = CV_RunTime::EC_pRetval (this);
	
	CV_RunTime::EC_SetpRetval (this, &lRetVal);

	switch (CV_RunTime::Event_wMsg (e)) {
	case WM_NOTIFY:
	{
	HWND hwndfrom = ((LPNMHDR)CV_RunTime::Event_lParam(e)) -> hwndFrom;
	pWind_Imp pWI = NULL;
	
		if (::IsWindow(hwndfrom))
			pWI = (pWind_Imp)(_AppImpFind() -> ContextList() -> Find ((HANDLE)hwndfrom));

		CV_RunTime::Event_SetExtra (e, pWI);

		switch (((LPNMHDR)CV_RunTime::Event_lParam(e)) -> code) {
		case PSN_APPLY:
			Report (this, CVEVT_NfyApply, e);
			if (!((pPDW)pRequestor) -> _NfyApply ((NotifyEvt &)e))
				SetWindowLong (hEContext, DWL_MSGRESULT, lRetVal = PSNRET_NOERROR);
			else
				SetWindowLong (hEContext, DWL_MSGRESULT, lRetVal = PSNRET_INVALID_NOCHANGEPAGE);
			break;

		case PSN_SETACTIVE:
			Report (this, CVEVT_NfySetActive, e);
			SetWindowLong (hEContext, DWL_MSGRESULT, 
				lRetVal = (LONG)((pPDW)pRequestor) -> _NfySetActive ((NotifyEvt &)e));
			break;

		case PSN_KILLACTIVE:
			Report (this, CVEVT_NfyKillActive, e);
			SetWindowLong(hEContext, DWL_MSGRESULT, 
				lRetVal = (LONG)((pPDW)pRequestor) -> _NfyKillActive ((NotifyEvt &)e));
			break;

		case PSN_RESET:		// Cancel pressed
			Report (this, CVEVT_NfyCancel, e);
			((pPDW)pRequestor) -> _NfyCancel ((NotifyEvt &)e);	
			break;

		case PSN_QUERYCANCEL:
			Report (this, CVEVT_NfyQueryCancel, e);
			SetWindowLong (hEContext, DWL_MSGRESULT, 
				lRetVal = (LONG)((pPDW)pRequestor) -> _NfyQueryCancel ((NotifyEvt &)e));
			break;

		case PSN_HELP:
			Report (this, CVEVT_NfyHelp, e);
			((pPDW)pRequestor) -> _NfyHelp ((NotifyEvt &)e);	
			break;

		case PSN_WIZBACK:
			Report (this, CVEVT_NfyWizBack, e);
			SetWindowLong (hEContext, DWL_MSGRESULT, 
				lRetVal = (LONG)((pPDW)pRequestor) -> _NfyWizBack ((NotifyEvt &)e));
			break;

		case PSN_WIZNEXT:
			Report (this, CVEVT_NfyWizNext, e);
			SetWindowLong (hEContext, DWL_MSGRESULT, 
				lRetVal = (LONG)((pPDW)pRequestor) -> _NfyWizNext ((NotifyEvt &)e));
			break;

		case PSN_WIZFINISH:
			Report (this, CVEVT_NfyWizFinish, e);
			SetWindowLong (hEContext, DWL_MSGRESULT, 
				lRetVal = (LONG)((pPDW)pRequestor) -> _NfyWizFinish ((NotifyEvt &)e));
			break;

		default:
			lRetVal = DWind_Imp :: Dispatch (e);	// andre Notify's gibt's auch noch
			break;
		}
		break;
	}

	default:
		lRetVal = DWind_Imp :: Dispatch (e);
		break;
	}

	CV_RunTime::EC_SetpRetval (this, pOldPtr);

return lRetVal;
}

// FensterRoutine -------------------------------------------------------------
extern "C" LRESULT WINAPI _DISPATCH_ENTRY
PropertyPageDispatcher (HWND hEContext, UINT ecMsg, WPARAM wParam, LPARAM lParam)
{
	if (WM_INITDIALOG == ecMsg) {	// Page initialisieren
	PROPSHEETPAGE *pPage = (PROPSHEETPAGE *)lParam;

		return ((PPageWind_Imp *)(pPage -> lParam)) -> FInit (hEContext);
	}

return (BOOL)EventDispatcher (hEContext, ecMsg, wParam, lParam);
}

// #HK030116: Wizard97 only: set HeaderTitle and HeaderSubTitle
void PPageWind_Imp::SetHeaderTitle(char const *pcHeaderTitle)
{
	if (NULL == pcHeaderTitle) 
		return;

	if (NULL != m_pcHeaderTitle) {
		delete (char *)m_pcHeaderTitle;
		m_pcHeaderTitle = NULL;
	}

	m_pcHeaderTitle = CV_strdup (pcHeaderTitle);
	if (NULL != m_pcHeaderTitle) {
		m_psp.dwFlags |= (PSP_USEHEADERTITLE|PSP_USETITLE);
		m_psp.pszHeaderTitle = m_pcHeaderTitle;
	}
}

void PPageWind_Imp::SetHeaderSubTitle(char const *pcHeaderSubTitle)
{
	if (NULL == pcHeaderSubTitle) 
		return;

	if (NULL != m_pcHeaderSubTitle) {
		delete (char *)m_pcHeaderSubTitle;
		m_pcHeaderSubTitle = NULL;
	}

	m_pcHeaderSubTitle = CV_strdup (pcHeaderSubTitle);
	if (NULL != m_pcHeaderSubTitle) {
		m_psp.dwFlags |= (PSP_USEHEADERSUBTITLE|PSP_USETITLE|PSP_HIDEHEADER);
		m_psp.pszHeaderSubTitle = m_pcHeaderSubTitle;
	}
}

