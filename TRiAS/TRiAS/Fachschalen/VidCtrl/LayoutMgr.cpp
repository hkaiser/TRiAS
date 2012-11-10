// --------------------------------------------------------------------------
// Description : several WTL utility classes for managing the layout of window children
// Author	   : Serge Weinstock
//
//	You are free to use, distribute or modify this code
//	as long as the header is not removed or modified.
// --------------------------------------------------------------------------
#include "stdafx.h"
#include "LayoutMgr.h"

//=============================================================================
// Private messages
//=============================================================================
const RegisteredWindowMessage	WMU_PS_ATTACH_PAGE(_T("WTLU_LM::WMU_PS_ATTACH_PAGE"));
const RegisteredWindowMessage	WMU_PS_INIT(_T("WTLU_LM::WMU_PS_INIT"));
const RegisteredWindowMessage	WMU_PS_ATTACH_PS(_T("WTLU_LM::WMU_PS_ATTACH_PS"));

//=====================================================================
// SizeGrip window
//=====================================================================
LRESULT SizeGrip::OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return true;
}

LRESULT SizeGrip::OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	RECT rc;
	GetClientRect(&rc);
	if(wParam != NULL)
		{
		CDCHandle dc = (HDC)wParam;
		dc.DrawFrameControl(&rc, DFC_SCROLL, DFCS_SCROLLSIZEGRIP);
		}
	else
		{
		CPaintDC dc(m_hWnd);
		dc.DrawFrameControl(&rc, DFC_SCROLL, DFCS_SCROLLSIZEGRIP);
		}
	return 0;
}

bool SizeGrip::Create(HWND parent)
{
	RECT	rc;
	int		l = ::GetSystemMetrics(SM_CXHSCROLL);
	int		h = ::GetSystemMetrics(SM_CYHSCROLL);

	ATLASSERT(parent != 0);
	::GetClientRect(parent, &rc);
	rc.left = rc.right - l;
	rc.top = rc.bottom - h;

	if (inherited::Create(parent, rc, _T("SizeGrip"), WS_CHILD) != 0)
		{
		// set the minimum area for the window
		CRgnHandle	rgn;
		POINT		pts[3];
		pts[0].x = 0; pts[0].y = h;
		pts[1].x = l; pts[1].y = h;
		pts[2].x = l; pts[2].y = 0;
		rgn.CreatePolygonRgn(pts, 3, ALTERNATE);
		SetWindowRgn(rgn, false);
		return true;
		}
	return false;
}

