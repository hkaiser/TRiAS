// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/05/1998 09:47:35 PM
//
// @doc
// @module MouseAction.cpp | Implementation of the <c CMouseAction> class

#include "stdafx.h"

//#include <objcontx.hxx>

#include "MsgBlast.h"
#include "MouseAction.h"

#include "Afxpriv.h"
// 
void CDrawAction::Undo()	// löscht die Linie wieder
{
	// nichts zu tun
	if (false == m_bShowLine)
		return;
	
	Line();
	m_bShowLine = false;	// jetzt ist alles wieder i.o.
}

// Helper functions
/*inline*/ void DCtoOCEx (const CPoint &rPt, long *pPt)
{
	COORDCONVERT CT;

	long Koords[2];				// Ergebnispuffer
	CT.lpPt = (POINT *)&rPt;
	CT.lpPkt = Koords;
	DEX_DCtoOC(CT);

	double Koordinaten[2];
	COORDTRANSFORM CTrans;
	INITSTRUCT(CTrans, CTrans);
	
	CTrans.m_Pts = Koords;
	CTrans.m_rcPts = Koordinaten;

	DEX_OCtoRC(CTrans);

	pPt[0] = (long) (Koordinaten[0] + 0.5);
	pPt[1] = (long) (Koordinaten[1] + 0.5);
}

long Handle(UINT wParam)
{
	long KeyCode = 0;
	if (wParam & MK_SHIFT)
	{
		KeyCode |= MOUSEKEY_Shift;
	}	
	if	(wParam & MK_CONTROL)
	{
		KeyCode |= MOUSEKEY_Control;
	}
	if (0 > GetAsyncKeyState(VK_MENU))
	{
		KeyCode |= MOUSEKEY_Alt;
	}

	// Maustasten
	if (wParam & MK_LBUTTON)
	{
		KeyCode |= MOUSEKEY_Left;
	}
	if (wParam & MK_MBUTTON)
	{
		KeyCode |= MOUSEKEY_Middle;
	}
	if (wParam & MK_RBUTTON)
	{
		KeyCode |= MOUSEKEY_Right;
	}

	return KeyCode;	// zurück gibts einen long der das ganze anzeigt
}

/////////////////////////////////////////////////////////////////////////////
// CMouseAction
STDMETHODIMP CMouseAction::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMouseAction,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CMouseAction::GetPoint(BSTR Prompt, double * pdX, double * pdY)
{
	CDrawAction action;
	return GetPoint(Prompt, pdX, pdY, action);
}

STDMETHODIMP CMouseAction::GetPointDrag(BSTR Prompt, double * pdX, double * pdY)
{
	CRealDrawAction action;
	return GetPoint(Prompt, pdX, pdY, action);
}

HRESULT CMouseAction::GetPoint(BSTR Prompt, double * pdX, double * pdY, CDrawAction& action)
{
	ASSERT(pdX);
	if (NULL == pdX) 
		return E_POINTER;

	ASSERT(pdY);
	if (NULL == pdY)
		return E_POINTER;

	AFX_MANAGE_STATE(AfxGetAppModuleState())

	// Schrift anzeigen
	CString strPrompt(Prompt);
	DEX_SetMessageStringNoKickIdle((LPCSTR)strPrompt);

	// auf Benutzereingabe warten
	MsgProc(action);

	// umrechnen
	CPoint sourcePt(m_OldX, m_OldY);
	long  ergVals[2];
	DCtoOCEx (sourcePt, ergVals);

	*pdX = ergVals[0];
	*pdY = ergVals[1];

	// Text zurücksetzen 
	CWnd* pWnd = g_pTE -> MWind();
	if (NULL == pWnd )
		return NULL;

	pWnd -> SendMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE);
	return S_OK;
}

STDMETHODIMP CMouseAction::get_LastKey(long * pVal)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	if (NULL == pVal) return E_POINTER;

	*pVal = m_rgLastKey;
	return S_OK;
}

void CMouseAction::MsgProc(CDrawAction& action)
{
	// action initialisieren
	action.SetBase(m_OldX, m_OldY);

	// set capture to the window which received this message
	CWnd * pWnd = action.GetWindow();
	if (NULL == pWnd) 
		return;

	CWnd * pOldWnd = pWnd->SetCapture();

	ASSERT(pWnd == CWnd::GetCapture());
	pWnd -> UpdateWindow();

	CDC * pDC = action.GetDC();

	AfxLockTempMaps();  // protect maps while looping

	int dcx = 0, dcy = 0;
	m_rgLastKey = MOUSEKEY_Unknown;
	// get messages until capture lost or cancelled/accepted
	for (;;)
	{
		MSG msg;
		VERIFY(::GetMessage(&msg, pWnd -> GetSafeHwnd(), 0, 0));
		CString strPrompt;

		pWnd->SetCapture();

		if (pWnd->GetCapture() != pWnd)
		{
			// wirkt wie Abbruch
			msg.message = WM_KEYDOWN;
			msg.wParam = VK_ESCAPE;
		}
		
		switch (msg.message)
		{
		// handle movement/accept messages
		case WM_LBUTTONUP:
		case WM_MOUSEMOVE:
			{
				// Tracking the Mouse positions
				int x = (int)(short) LOWORD(msg.lParam);
				int y = (int)(short) HIWORD(msg.lParam);

				// nochmal neu zeichnen
//				action.Draw(dcx, dcy);

				// umrechnen
				CPoint Pt(x, y);
				pDC -> DPtoLP(&Pt);

//				pWnd -> SetCapture();
//				pWnd -> SetFocus();

				// Point in wnd
/*				CRect rect;
				pWnd -> GetClientRect(rect);

				if	(	(rect.bottom < y) 
					&&	(rect.top > y)
					&&  (rect.left < x)
					&&  (rect.right > x))
				{*/
					dcx = Pt.x;
					dcy = Pt.y;
					action.Draw(dcx, dcy);
//				}

				// einfach weiterreichen
				DispatchMessage(&msg);
			}
			break;

		// handle cancel messages
		case WM_KEYDOWN:
			if (msg.wParam == VK_ESCAPE)
			{
				m_rgLastKey = MOUSEKEY_Breaked;		// Schluß ist
				dcx = m_OldX;						// neue Mausposition = alte Position 
				dcy = m_OldY;

				goto ExitLoop;
			}
			break;
		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
			{
				m_rgLastKey = Handle(msg.wParam);		// Tasten speichern
				goto ExitLoop;
			}
		// just dispatch rest of the messages
		default:
			DispatchMessage(&msg);
			break;
		}
	}

ExitLoop:
	// Vorsicht! Pixelbug im TRiAS	(?????????)
//	++dcy;

	// store data
	m_OldX = dcx;
	m_OldY = dcy;	

	ReleaseCapture();

	AfxUnlockTempMaps(FALSE);

	if (NULL != pOldWnd )
		pOldWnd -> SetCapture();

	return;
}
