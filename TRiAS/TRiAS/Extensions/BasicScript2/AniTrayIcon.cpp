// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 21.03.2000 12:50:48
//
// @doc
// @module AniTrayIcon.cpp | Implementation of the <c CAnimatedTrayIcon> class

// This class gives the implementation for an animated tray icon 
// This can be freely used by any one , but in case there are any changes
// to this, please let me know at kirant.s@usa.net.
// That'll help me fix the problems and/or make improvements if any.

#include "bscriptp.hxx"

#include <process.h>
#include "AniTrayIcon.h"

#define NIF_ALL		NIF_ICON | NIF_MESSAGE | NIF_TIP 
#define TIMER_ID	200

LRESULT CALLBACK TrayWindowProc(HWND hWnd, UINT msg, WPARAM wParam , LPARAM lParam)
{
static NOTIFYICONDATA stNotifyIconData;
static UINT hTimer = NULL;
static int nTimerInterval = 0;
static HICON *hIconArray = NULL;
static bShellIconAdded = false;
static int nCurrIndex = 0;
static int nArraySize = 0;
	
	switch (msg) {
	case WM_CLOSE: 
		DestroyWindow(hWnd);
		break;

	case WM_CREATE:
		{
			stNotifyIconData.cbSize = sizeof(NOTIFYICONDATA);
			stNotifyIconData.hIcon = NULL;
			stNotifyIconData.hWnd = NULL;
			lstrcpy(stNotifyIconData.szTip, "");
			stNotifyIconData.uCallbackMessage = 0;
			stNotifyIconData.uFlags = 0;
			stNotifyIconData.uID = 0;
		}
		break;

	case WM_DESTROY: 
		{
		// clean up 
			if (hTimer)
				KillTimer(hWnd, hTimer);
			if (hIconArray)
				delete[] hIconArray;
			if (bShellIconAdded)
			{
				stNotifyIconData.uFlags = NIF_ALL;
				Shell_NotifyIcon(NIM_DELETE, &stNotifyIconData);
			}
			PostQuitMessage(0);
		}
		break;

	case WM_TIM_START: 
		{
			if (!bShellIconAdded)
			{
				stNotifyIconData.uFlags = NIF_ALL;
				nCurrIndex = 0;
				if (hIconArray)
					stNotifyIconData.hIcon = hIconArray[nCurrIndex];
				bShellIconAdded = Shell_NotifyIcon(NIM_ADD, &stNotifyIconData);
			}
		}
		break;

	case WM_TIMER:
		{
			if (bShellIconAdded)
			{
				stNotifyIconData.uFlags = NIF_ALL;
				if (hIconArray)
					stNotifyIconData.hIcon = hIconArray[nCurrIndex];
				Shell_NotifyIcon(NIM_MODIFY, &stNotifyIconData);
				nCurrIndex++;
				if (nArraySize == nCurrIndex)
					nCurrIndex = 0;
			}
		}
		break;

	case WM_TIM_CONTINUE:
		{
			if (NULL == hTimer)	
				hTimer = SetTimer(hWnd, TIMER_ID, nTimerInterval, NULL);
		}
		break;

	case WM_TIM_STOP:
		{
			if (hTimer)	
				KillTimer(hWnd, hTimer);
			hTimer = NULL;
		}
		break;

	case WM_TIM_REMOVE:
		{
			if (bShellIconAdded)
			{
				Shell_NotifyIcon(NIM_DELETE, &stNotifyIconData);
				bShellIconAdded = false;
			}			
		}
		break;

	case WM_TIM_FRAMEINFO:
		{
			if (hIconArray)
			{
				delete[] hIconArray;
				hIconArray = NULL;
			}
			nArraySize = (int)lParam;
			if (nArraySize != 0)
			{
				hIconArray = new HICON[nArraySize];
				for (int i = 0; i < nArraySize; i++)
					hIconArray[i] = ((HICON *)wParam)[i];
			}
		}
		break;

	case WM_TIM_FRAMERATE:
		{
			// kill the old timer and set the new frame rate
			if (hTimer)
				KillTimer(hWnd, hTimer);
			nTimerInterval = (int)lParam;
			hTimer = SetTimer(hWnd, TIMER_ID, nTimerInterval, NULL);
		}
		break;

	case WM_TIM_SET_CALLBACK_WND:
		{
			stNotifyIconData.hWnd = (HWND)lParam;
			if (bShellIconAdded)
			{
				stNotifyIconData.uFlags = NIF_ALL;
				Shell_NotifyIcon(NIM_MODIFY, &stNotifyIconData);
			}
		}
		break;

	case WM_TIM_SET_CALLBACK_MSG:
		{
			stNotifyIconData.uCallbackMessage = (UINT)lParam;
			if (bShellIconAdded)
			{
				stNotifyIconData.uFlags = NIF_ALL;
				Shell_NotifyIcon(NIM_MODIFY, &stNotifyIconData);
			}
		}
		break;

	case WM_TIM_SET_ID:
		{
			stNotifyIconData.uID = (UINT)lParam;
			if (bShellIconAdded)
			{
				stNotifyIconData.uFlags = NIF_ALL;
				Shell_NotifyIcon(NIM_MODIFY, &stNotifyIconData);
			}
		}
		break;

	case WM_TIM_SET_TOOLTIP:
		{
			lstrcpy(stNotifyIconData.szTip, (LPSTR)lParam);
			if (bShellIconAdded)
			{
				stNotifyIconData.uFlags = NIF_ALL;
				Shell_NotifyIcon(NIM_MODIFY, &stNotifyIconData);
			}
		}
		break;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

void CreateTrayWindow(CAnimatedTrayIcon* pAniWnd)
{
WNDCLASSEX wndclass;
char cbWindowClass[64];

	wsprintf (cbWindowClass, "TRiAS_TrayWnd_%lx", GetCurrentProcessId());
	memset (&wndclass, '\0', sizeof(WNDCLASSEX));
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = NULL;
	wndclass.hCursor = NULL;
	wndclass.hIcon = NULL;
	wndclass.hIconSm = NULL;
	wndclass.hInstance = GetModuleHandle(NULL);
	wndclass.lpfnWndProc = TrayWindowProc;
	wndclass.lpszClassName = cbWindowClass;
	wndclass.lpszMenuName = NULL;
	wndclass.style = 0;
	RegisterClassEx(&wndclass);

HWND hTrayWindow = ::CreateWindow(cbWindowClass, "", WS_POPUP, 0, 0, 0, 0, NULL, NULL, GetModuleHandle(NULL), NULL);

	pAniWnd -> SetTrayWindowHandle(hTrayWindow);
	SetEvent (pAniWnd->m_hEvent);

// start the message loop 
MSG msg;

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

CAnimatedTrayIcon::CAnimatedTrayIcon()
{
	m_hWnd = NULL;
	m_hEvent = NULL;
}

bool CAnimatedTrayIcon::EnsureRunningThread()
{
	if (::IsWindow(m_hWnd))
		return true;		// thread bereits aktiv
		
	m_hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (NULL != m_hEvent) {
	UINT threadID = 0;

		if (0 != _beginthreadex(NULL, 0, (unsigned int(__stdcall *)(void *))CreateTrayWindow, this, 0, &threadID))
		{
			WaitForSingleObject(m_hEvent, INFINITE);
		}
		CloseHandle(m_hEvent);
	}
	m_hEvent = NULL;
	return ::IsWindow(m_hWnd);
}

CAnimatedTrayIcon::~CAnimatedTrayIcon()
{
	if (::IsWindow(m_hWnd))
		::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
	Sleep(100);
}

void CAnimatedTrayIcon::SetFrameRate(int nFrameRate)
{
	if (EnsureRunningThread())
		::SendMessage(m_hWnd, WM_TIM_FRAMERATE, 0, (LPARAM)nFrameRate);
}

void CAnimatedTrayIcon::SetFrameIconInfo(HICON* hIconArray, int nNoOfIcons)
{
	if (EnsureRunningThread())
		::SendMessage(m_hWnd, WM_TIM_FRAMEINFO, (WPARAM)hIconArray, (LPARAM)nNoOfIcons);
}

void CAnimatedTrayIcon::Start()
{
	if (EnsureRunningThread())
		::SendMessage(m_hWnd, WM_TIM_START, 0, 0);
}

void CAnimatedTrayIcon::Continue()
{
	if (EnsureRunningThread())
		::SendMessage(m_hWnd, WM_TIM_CONTINUE, 0, 0);
}

void CAnimatedTrayIcon::Stop()
{
	if (EnsureRunningThread())
		::SendMessage(m_hWnd, WM_TIM_STOP, 0, 0);
}

void CAnimatedTrayIcon::Remove()
{
	if (EnsureRunningThread())
		::SendMessage(m_hWnd, WM_TIM_REMOVE, 0, 0);
}

void CAnimatedTrayIcon::SetTrayWindowHandle(HWND hWnd)
{
	if (!m_hWnd)
		m_hWnd = hWnd;
}

void CAnimatedTrayIcon::SetTrayCallbackWindowHandle(HWND hWnd)
{
	if (EnsureRunningThread())
		::SendMessage(m_hWnd, WM_TIM_SET_CALLBACK_WND, 0, (LPARAM)hWnd);
}

void CAnimatedTrayIcon::SetTrayCallBackMessage(UINT uCallBackMsg)
{
	if (EnsureRunningThread())
		::SendMessage(m_hWnd, WM_TIM_SET_CALLBACK_MSG, 0, (LPARAM)uCallBackMsg);
}

void CAnimatedTrayIcon::SetTrayID(UINT uId)
{
	if (EnsureRunningThread())
		::SendMessage(m_hWnd, WM_TIM_SET_ID, 0, (LPARAM)uId);
}

void CAnimatedTrayIcon::SetTrayToolTip(LPCSTR szTip)
{
	if (EnsureRunningThread())
		::SendMessage(m_hWnd, WM_TIM_SET_TOOLTIP, 0, (LPARAM)szTip);
}
