// CToolTipCtrl - Interface ---------------------------------------------------
// File: TOOLTIP.CXX

#include "tfrmpre.hxx"
#if _MSC_VER >= 1100
#include <ospace/except/stdex.h>
#endif // _MSC_VER

CToolTipCtrl :: CToolTipCtrl (pWindow parent)
{
	control_Imp = new CToolTipCtrl_Imp (this, (pWind_Imp)CV_RunTime::pWindow_to_pImp(parent));
}

CToolTipCtrl :: ~CToolTipCtrl (void)
{
}

CToolTipCtrl_Imp :: CToolTipCtrl_Imp (pControl req, pWind_Imp parent)
		   : Control_Imp (req, parent, CvID((uint)0), Point(0, 0), Dimension(0, 0),  
		   		  (const char*)CTRL_ToolTipCtrl, WS_POPUP)
{
}

CToolTipCtrl_Imp :: ~CToolTipCtrl_Imp (void)
{
}

void CToolTipCtrl_Imp :: Create (void)
{
	Control_Imp :: Create();
}

BOOL CToolTipCtrl::AddTool (pWindow pWnd, LPCSTR lpszText, LPCRECT lpRectTool, 
			    UINT nIDTool)
{
	CV_ASSERT(::IsWindow(Handle()));
	CV_ASSERT(pWnd != NULL);
	CV_ASSERT(lpszText != NULL);
	// the toolrect and toolid must both be zero or both valid
	CV_ASSERT((lpRectTool != NULL && nIDTool != 0) ||
		   (lpRectTool == NULL) && (nIDTool == 0));

TOOLINFO ti;

	FillInToolInfo(ti, pWnd, nIDTool);
	if (lpRectTool != NULL)
		ti.rect = *lpRectTool;		// copy RECT
	ti.lpszText = (LPTSTR)lpszText;

return (BOOL) ::SendMessage(Handle(), TTM_ADDTOOL, 0, (LPARAM)&ti);
}

BOOL CToolTipCtrl::AddTool (pWindow pWnd, ResID nIDText, LPCRECT lpRectTool, 
			    UINT nIDTool)
{
	CV_ASSERT(nIDText != 0);

string str;

	try {
	char *pText = new char [1025];

		LoadString (CV_RunTime::ResID_handle (nIDText, _AppImpFind(), RT_STRING),
			    (UINT)nIDText, pText, 1024);
		str = pText;
		delete pText;
#if _MSC_VER >= 1100
	} catch (os_length_error) {
#else
	} catch (...) {
#endif // _MSC_VER
		return false;
	}
	return AddTool(pWnd, str.c_str(), lpRectTool, nIDTool);
}

void CToolTipCtrl::DelTool(pWindow pWnd, UINT nIDTool)
{
	CV_ASSERT(::IsWindow(Handle()));
	CV_ASSERT(pWnd != NULL);

TOOLINFO ti;

	FillInToolInfo(ti, pWnd, nIDTool);
	::SendMessage(Handle(), TTM_DELTOOL, 0, (LPARAM)&ti);
}

void CToolTipCtrl::GetText(string& str, pWindow pWnd, UINT nIDTool)
{
	CV_ASSERT(::IsWindow(Handle()));
	CV_ASSERT(pWnd != NULL);

TOOLINFO ti;

	FillInToolInfo(ti, pWnd, nIDTool);
	::SendMessage(Handle(), TTM_GETTEXT, 0, (LPARAM)&ti);
	str = ti.lpszText;
}

BOOL CToolTipCtrl::GetToolInfo(LPTOOLINFO lpToolInfo, pWindow pWnd, UINT nIDTool)
{
	CV_ASSERT(::IsWindow(Handle()));
	CV_ASSERT(pWnd != NULL);
	CV_ASSERT(lpToolInfo != NULL);

	FillInToolInfo(*lpToolInfo, pWnd, nIDTool);

return (BOOL)::SendMessage(Handle(), TTM_GETTOOLINFO, 0, (LPARAM)lpToolInfo);
}

BOOL CToolTipCtrl::HitTest(pWindow pWnd, Point pt, LPTOOLINFO lpToolInfo)
{
	CV_ASSERT(::IsWindow(Handle()));
	CV_ASSERT(pWnd != NULL);
	CV_ASSERT(lpToolInfo != NULL);

TTHITTESTINFO hti;

	memset(&hti, 0, sizeof(hti));
	hti.hwnd = pWnd->Handle();
	hti.pt.x = pt.X();
	hti.pt.y = pt.Y();
	if ((BOOL)::SendMessage(Handle(), TTM_HITTEST, 0, (LPARAM)&hti)) {
		*lpToolInfo = hti.ti;		// copy TOOLINFO
		return true;
	}

return false;
}

void CToolTipCtrl::SetToolRect(pWindow pWnd, UINT nIDTool, LPCRECT lpRect)
{
	CV_ASSERT(::IsWindow(Handle()));
	CV_ASSERT(pWnd != NULL);
	CV_ASSERT(nIDTool != 0);

TOOLINFO ti;

	FillInToolInfo(ti, pWnd, nIDTool);
	ti.rect = *lpRect;	// copy RECT
	::SendMessage(Handle(), TTM_NEWTOOLRECT, 0, (LPARAM)&ti);
}

void CToolTipCtrl::UpdateTipText(LPCSTR lpszText, pWindow pWnd, UINT nIDTool)
{
	CV_ASSERT(::IsWindow(Handle()));
	CV_ASSERT(pWnd != NULL);

TOOLINFO ti;

	FillInToolInfo(ti, pWnd, nIDTool);
	ti.lpszText = (LPTSTR)lpszText;
	::SendMessage(Handle(), TTM_UPDATETIPTEXT, 0, (LPARAM)&ti);
}

void CToolTipCtrl::UpdateTipText(ResID nIDText, pWindow pWnd, UINT nIDTool)
{
	CV_ASSERT(nIDText != 0);

string str;

	try {
	char *pText = new char [1025];

		LoadString (CV_RunTime::ResID_handle (nIDText, _AppImpFind(), RT_STRING),
			    (UINT)nIDText, pText, 1024);
		str = pText;
		delete pText;

#if _MSC_VER >= 1100
	} catch (os_length_error) {
#else
	} catch (...) {
#endif // _MSC_VER
		return;
	}
	UpdateTipText(str.c_str(), pWnd, nIDTool);
}


void CToolTipCtrl::FillInToolInfo(TOOLINFO& ti, pWindow pWnd, UINT nIDTool)
{
	memset(&ti, 0, sizeof(ti));
	ti.cbSize = sizeof(ti);

HWND hwnd = pWnd->Handle();

	if (nIDTool == 0) {
		ti.hwnd = ::GetParent(hwnd);
		ti.uFlags = TTF_IDISHWND;
		ti.uId = (UINT)hwnd;
	} else {
	 	ti.hwnd = hwnd;
		ti.uFlags = 0;
		ti.uId = nIDTool;
	}
}

CToolTipCtrl* CToolBarCtrl::GetToolTips()
{ 
	return (CToolTipCtrl *)(_AppImpFind()->ControlList()->Find((HANDLE)::SendMessage(Handle(), TB_GETTOOLTIPS, 0, 0L))); 
}

