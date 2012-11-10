// PropertySheet im TRiAS®-Framework ------------------------------------------
// File: PROPSHET.CXX

#include "tfrmpre.hxx"
#include <_link.hxx>
#include <commctrl.h>

CPropertySheet::CPropertySheet (LPCSTR pszCaption, Window *parent, DWORD dwFlags, UINT iSelPage)
{
	ec_Imp = new PSheetWind_Imp (this, pszCaption, 
			(pWind_Imp)(parent ? CV_RunTime::pWindow_to_pImp(parent) : 0), 
			dwFlags, iSelPage);
}

CPropertySheet::~CPropertySheet (void)
{
	if (ec_Imp) {
		delete ec_Imp;
		ec_Imp = NULL;
	}
}

// GetPageCount: Retrieves the number of pages in the property sheet.
int CPropertySheet::GetPageCount (void)
{
	return ((PSheetWind_Imp *)ec_Imp) -> GetPageCount();
}

// GetPage: Retrieves a pointer to the specified page.
CPropertyPage* CPropertySheet::GetPage (UINT nPage) const
{
PPageWind_Imp *pPPImp = ((PSheetWind_Imp *)ec_Imp) -> GetPage (nPage);

	if (pPPImp) return (CPropertyPage *)CV_RunTime::Wind_Requestor(pPPImp);

return NULL;
}


// Show: Displays a modal property sheet.
void CPropertySheet::Show (ShowState s)
{
	((PSheetWind_Imp *)ec_Imp) -> Show (s);
}

// AddPage: Adds a page to the property sheet.
UINT CPropertySheet::AddPage (CPropertyPage *pPage)
{
	return ((PSheetWind_Imp *)ec_Imp) -> AddPage ((PPageWind_Imp *)CV_RunTime::pWindow_to_pImp(pPage));
}

// AddPage: Adds a page to the property sheet.
UINT CPropertySheet::AddPage (HPROPSHEETPAGE hPage)
{
	return ((PSheetWind_Imp *)ec_Imp) -> AddPage (hPage);
}

// RemovePage: Removes a page from the property sheet.
BOOL CPropertySheet::RemovePage (CPropertyPage *pPage)
{
	return ((PSheetWind_Imp *)ec_Imp) -> RemovePage ((PPageWind_Imp *)CV_RunTime::pWindow_to_pImp(pPage));
}

BOOL CPropertySheet::RemovePage (HPROPSHEETPAGE hPage)
{
	return ((PSheetWind_Imp *)ec_Imp) -> RemovePage (hPage);
}

BOOL CPropertySheet::RemovePage (UINT nPage)
{
	return ((PSheetWind_Imp *)ec_Imp) -> RemovePage (nPage);
}

// EndDialog: Terminates the property sheet.
void CPropertySheet::EndDialog (int nEndID)
{
	((PSheetWind_Imp *)ec_Imp) -> EndDlg (nEndID);
}

// SetCurSel: Aktivieren einer Seite
BOOL CPropertySheet::SetCurSel (CPropertyPage *pPage)
{
	return ((PSheetWind_Imp *)ec_Imp) -> SetCurSel ((PPageWind_Imp *)CV_RunTime::pWindow_to_pImp(pPage));
}

BOOL CPropertySheet::SetCurSel (UINT nPage)
{
	return ((PSheetWind_Imp *)ec_Imp) -> SetCurSel (nPage);
}

BOOL CPropertySheet::SetCurSel (HPROPSHEETPAGE hPage)
{
	return ((PSheetWind_Imp *)ec_Imp) -> SetCurSel (hPage);
}

void CPropertySheet::PressButton (DWORD btns)
{
	((PSheetWind_Imp *)ec_Imp) -> PressButton(btns);
}

void CPropertySheet::SetWizardButtons (DWORD btns)
{
	((PSheetWind_Imp *)ec_Imp) -> SetWizButtons(btns);
}

void CPropertySheet::SetIcon (ResID resID)
{
	 ((PSheetWind_Imp *)ec_Imp) -> SetIcon (resID);
}

void CPropertySheet::SetIcon (Icon *pIcon)
{
	 ((PSheetWind_Imp *)ec_Imp) -> SetIcon (CV_RunTime::Icon_Imp(pIcon));
}

// #HK030116: Wizard97: Headerbitmap und Watermark setzen
void CPropertySheet::SetHeaderBitmap (ResID resID)
{
	 ((PSheetWind_Imp *)ec_Imp) -> SetHeaderBitmap (resID);
}

void CPropertySheet::SetHeaderBitmap (pBitmap pBitmap)
{
	 ((PSheetWind_Imp *)ec_Imp) -> SetHeaderBitmap (CV_RunTime::pBitmap_to_pImp(pBitmap));
}

void CPropertySheet::SetWatermark (ResID resID)
{
	 ((PSheetWind_Imp *)ec_Imp) -> SetWatermark (resID);
}

void CPropertySheet::SetWatermark (pBitmap pBitmap)
{
	 ((PSheetWind_Imp *)ec_Imp) -> SetWatermark (CV_RunTime::pBitmap_to_pImp(pBitmap));
}


// #HK990623 -----------------------------------------------------------------
BOOL CPropertySheet::PreTranslateMsg (MSG *pMsg)
{
// allow sheet to translate Ctrl+Tab, Shift+Ctrl+Tab,
//  Ctrl+PageUp, and Ctrl+PageDown
	if (pMsg->message == WM_KEYDOWN && GetAsyncKeyState(VK_CONTROL) < 0 &&
		(pMsg->wParam == VK_TAB || pMsg->wParam == VK_PRIOR || pMsg->wParam == VK_NEXT))
	{
		if (ForwardEvent (PSM_ISDIALOGMESSAGE, 0, (LPARAM)pMsg))
			return TRUE;
	}
	return DialogWindow::PreTranslateMsg (pMsg);
}

