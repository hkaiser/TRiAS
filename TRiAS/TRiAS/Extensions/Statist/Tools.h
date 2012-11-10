// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 01.09.99 21:50:53 
//
// @doc
// @module Tools.h | Declaration of the <c CTools> class

#if !defined(_TOOLS_H__45E6208D_395F_40CE_A489_6A802E7585EC__INCLUDED_)
#define _TOOLS_H__45E6208D_395F_40CE_A489_6A802E7585EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Usefull macros
#define KEYDOWN(Key) ((GetKeyState(Key)&0x8000)!=0)
#define VIRTUAL_KEY(nChar,nFlags) (((nFlags)&0x0100)||(nChar)<=VK_ESCAPE||(nChar)>=VK_F1)
#define ANSI_KEY(nChar) ((nChar)>VK_ESCAPE)
#define VK_CTRL_A 1
#define VK_CTRL_Z 26
#define VK_ALT VK_MENU

// To not have to type the 4 fields !
#define EXPAND_RECT(rc) (rc).left,(rc).top,(rc).right,(rc).bottom

///////////////////////////////////////////////////////////////////////////////
// Helper classes
class CClientRect : 
	public CRect
{
public:
    CClientRect (HWND hWnd)
    {
        ::GetClientRect (hWnd, this);
    }
    CClientRect (const CWindow *pWnd)
    {
        pWnd->GetClientRect (this);
    }
};

class CWindowRect : 
	public CRect
{
public:
    CWindowRect (HWND hWnd)
    {
        ::GetWindowRect (hWnd, this);
    }
    CWindowRect (const CWindow *pWnd)
    {
        pWnd->GetWindowRect (this);
    }
};

#endif // !defined(_TOOLS_H__45E6208D_395F_40CE_A489_6A802E7585EC__INCLUDED_)
