// PropertyPages --------------------------------------------------------------
// File: PROPPAGE.CXX

#include "tfrmpre.hxx"
#include <_link.hxx>
#include <commctrl.h>

CPropertyPage :: CPropertyPage (ResID RscID, LPCSTR pCaption)
{
	ec_Imp = new PPageWind_Imp (this, RscID, pCaption);
}

CPropertyPage :: CPropertyPage (void)
{
	ec_Imp = NULL;
}

CPropertyPage :: ~CPropertyPage (void)
{
	if (ec_Imp) {
		delete ec_Imp;
		ec_Imp = NULL;
	}
}

CPropertySheet *CPropertyPage :: GetPropertySheet (void)
{
PSheetWind_Imp *pPSImp = ((PPageWind_Imp*)ec_Imp) -> GetPSheetImp();

	if (pPSImp) return (CPropertySheet *)CV_RunTime::Wind_Requestor(pPSImp);

return NULL;
}

// CancelToClose: Changes the Cancel button to read Close after an unrecoverable change in the page of a modal property sheet.
void CPropertyPage :: CancelToClose (void)
{
	 ((PPageWind_Imp*)ec_Imp) -> CancelToClose();
}

// SetModified: Call to activate or deactivate the Apply Now button.
void CPropertyPage :: SetModified (BOOL bChanged)
{
	 ((PPageWind_Imp*)ec_Imp) -> SetModified (bChanged);
}

LRESULT CPropertyPage::QuerySiblings (WPARAM wParam, LPARAM lParam)
{
	return ((PPageWind_Imp*)ec_Imp) -> QuerySiblings (wParam, lParam);
}

void CPropertyPage::SetSheetWizardButtons (DWORD dwFlags)
{
	 ((PPageWind_Imp*)ec_Imp) -> SetSheetWizardButtons (dwFlags);
}

void CPropertyPage::PressSheetButton (DWORD dwFlags)
{
	 ((PPageWind_Imp*)ec_Imp) -> PressSheetButton (dwFlags);
}

void CPropertyPage :: SetIcon (ResID resID)
{
	 ((PPageWind_Imp *)ec_Imp) -> SetIcon (resID);
}

void CPropertyPage :: SetIcon (Icon *pIcon)
{
	 ((PPageWind_Imp *)ec_Imp) -> SetIcon (CV_RunTime::Icon_Imp(pIcon));
}

// OnCancel: Called by the framework when the Cancel button is clicked.
void CPropertyPage :: OnCancel (NotifyEvt e)
{
	Default ((Event &)e);
}

// OnQueryCancel: Called by the framework to verify the cancel operation
BOOL CPropertyPage :: OnQueryCancel (NotifyEvt e)
{
	Default ((Event &)e);
	return false;		// allow processing
}

// OnOK: Called by the framework when the OK, Apply Now, or Close button is clicked.
BOOL CPropertyPage :: OnOK (NotifyEvt e)
{
	Default ((Event &)e);
	return false;		// allow processing
}

// OnSetActive: Called by the framework when the page is made the active page.
BOOL CPropertyPage :: OnSetActive (NotifyEvt e)
{
	Default ((Event &)e);
	return 0;
}

// OnKillActive: Called by the framework when the current page is no longer the active page. Perform data validation here.
BOOL CPropertyPage :: OnKillActive (NotifyEvt e)
{
	Default ((Event &)e);
	return false;		// allow processing
}

void CPropertyPage :: OnHelp (NotifyEvt e)
{
	Default ((Event &)e);
}

int CPropertyPage :: OnWizBack (NotifyEvt e)	// -1:cancel
{
	Default ((Event &)e);
	return 0;
}

int CPropertyPage :: OnWizNext (NotifyEvt e)	// -1: cancel
{
	Default ((Event &)e);
	return 0;
}

BOOL CPropertyPage :: OnWizFinish (NotifyEvt e)	// true:cancel
{
	Default ((Event &)e);
	return false;		// allow processing
}



void CPropertyPage :: Show (ShowState)	// darf nicht gerufen werden
{
	// do nothing, never called
}

HWND CPropertyPage :: Handle (Service s)
{
	if (NULL == this) return NULL;

	switch (s) {
	case API_WINDOW_HWND:
		return CV_RunTime :: Handle((pWind_Imp)ec_Imp);

	case API_WINDOW_HDC:
		return (HWND)CV_RunTime :: Window_hDC((pWind_Imp)ec_Imp);

	case API_WINDOW_TARGETHDC:		// #HK940119
		return (HWND)CV_RunTime :: Window_GetTargetDC ((pWind_Imp)ec_Imp);
	
	case API_WINDOW_HPROPSHEETPAGE:
		return (HWND)CV_RunTime :: PropPage_GethPage ((pWind_Imp)ec_Imp);

	default:
		return 0;
	}
}

HPROPSHEETPAGE CPropertyPage :: CreatePage (void)
{
	return ((PPageWind_Imp*)ec_Imp) -> CreatePage (NULL);
}

// #HK030116: Wizard97 only: set HeaderTitle and HeaderSubTitle
void CPropertyPage::SetHeaderTitle(char const *pcHeaderTitle)
{
	((PPageWind_Imp*)ec_Imp) -> SetHeaderTitle (pcHeaderTitle);
}

void CPropertyPage::SetHeaderSubTitle(char const *pcHeaderSubTitle)
{
	((PPageWind_Imp*)ec_Imp) -> SetHeaderSubTitle (pcHeaderSubTitle);
}

