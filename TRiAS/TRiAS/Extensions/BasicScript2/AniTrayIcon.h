// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 21.03.2000 12:49:17 
//
// @doc
// @module AniTrayIcon.h | Declaration of the <c CAnimatedTrayIcon> class

#if !defined(_ANITRAYICON_H__2D22F446_BFEB_4BA2_BDD0_4D065FDA27E8__INCLUDED_)
#define _ANITRAYICON_H__2D22F446_BFEB_4BA2_BDD0_4D065FDA27E8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Tray Icon Messages 
#define WM_TIM_START			WM_USER + 1		// starts animation
#define WM_TIM_CONTINUE			WM_USER + 2		// continues a paused animation
#define WM_TIM_STOP				WM_USER + 3		// stops(pauses) animation
#define WM_TIM_REMOVE			WM_USER + 4		// removes icon from tray
#define WM_TIM_FRAMEINFO		WM_USER + 5		// to set the frame icons in the tray
#define WM_TIM_FRAMERATE		WM_USER + 6		// to set the frame rate
#define WM_TIM_SET_CALLBACK_WND		WM_USER + 7	// to set the call back window
#define WM_TIM_SET_CALLBACK_MSG		WM_USER + 8	// to set the call back message id
#define WM_TIM_SET_ID			WM_USER + 9		// to set the tray icon id
#define WM_TIM_SET_TOOLTIP		WM_USER + 10 	// to set the tool tip for the icon

///////////////////////////////////////////////////////////////////////////////
// 
class CAnimatedTrayIcon
{
public :
	CAnimatedTrayIcon();
	~CAnimatedTrayIcon();
	
// set methods 
	void SetFrameRate(int nFrameRate);		// sets the frame rate for animation . time in milliseconds
	void SetFrameIconInfo(HICON* hIconArray,int nNoOfIcons); //sets the icons for the different frames 
	void SetTrayWindowHandle(HWND hWnd);	// sets the hWnd used for tray icon
	void SetTrayCallbackWindowHandle(HWND hWnd);
	void SetTrayCallBackMessage(UINT uCallBackMsg);
	void SetTrayID(UINT uId);
	void SetTrayToolTip(LPCSTR szTip);

// status manipulation methods 
	void Start();							// start animation
	void Stop();							// stop animation
	void Remove();							// remove icon from tray
	void Continue();						// continue stopped animation

	HANDLE m_hEvent;						// event object used for syncing .This should've been a private member

protected:
	bool EnsureRunningThread();

private:
	HWND m_hWnd;							// hWnd which handles tray status notifications
};

#endif // !defined(_ANITRAYICON_H__2D22F446_BFEB_4BA2_BDD0_4D065FDA27E8__INCLUDED_)
