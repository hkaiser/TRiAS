///////////////////////////////////////////////////////////
// ebc.cpp (draft 0.2)
//
// BasicScript Classes C++ library.
// Copyright (C) 1994-1995 Summit Software Company,
// All rights reserved.
//
// This source code is intended as a supplement to the
// BasicScript Classes Reference and the BasicScript 2.1 Programmer's Guide.
// See these sources for detailed information regarding the
// BasicScript Classes product.
//
///////////////////////////////////////////////////////////
//
// The .cpp version in the file ebc.cpp will work for compilers
// that are unable to utilize the inlined version in the file
// ebc.inl

// Include this if using precompiler header files with MSVC
#include "bscriptp.hxx"

#ifndef _EBC_ENABLE_INLINES
#  define _EBC_INLINE

#include <ebc.h>
#include <string.h>

#ifdef EBWIN
#  ifndef _WINDLL
#    define _WINDLL
#    include <stdarg.h>
#    undef _WINDLL
#  else
#    include <stdarg.h>
#  endif
#else
#  include <stdarg.h>
#endif

#ifdef EBOS2
#  undef ebCAPI
#  define ebCAPI
#endif // EBOS2

#include <ebc.inl>

#ifdef EBOS2
#  undef ebCAPI
#  define ebCAPI EXPENTRY
#endif // EBOS2

#endif // _EBC_ENABLE_INLINES

char FAR* CebEntryInfo::pszMain = "Main";

#if defined(EBWIN) | defined(EBWIN32) | defined(EBOS2)

CebDebuggerDlg::CebDebuggerDlg(	CebDebugDlgInfo FAR*	pDebugDlgInfo,
				CebInstance FAR&		Instance,
				CebEntryInfo FAR&		EntryInfo,
				HWND		hWndParent,
				ebLPCSTR	pScript,	/* = NULL */
				const ebHCODE hCode,	/* = NULL */
				ebLPCSTR	pWatches,	/* = NULL */
                ebLPCSTR	pszTitle,	/* = NULL */
				HFONT		hFont,		/* = NULL */
				ebDWORD		dwParam		/* = 0 */ )
{
	m_pDebugDlgInfo = pDebugDlgInfo;
	
	m_DebugInfo.lStructSize = sizeof(ebDEBUGGER);
	m_DebugInfo.hInstance = Instance.GetHandle();
	EntryInfo.GetEntryInfo(&m_DebugInfo.ei);
	m_DebugInfo.lpScriptIn = (ebLPSTR) pScript;

	if (hCode == NULL)
		// set to NULL
		CebCode::Initialize(&m_DebugInfo.hCodeIn);
	else
		m_DebugInfo.hCodeIn = hCode;
	
	m_DebugInfo.lpWatchesIn = (ebLPSTR) pWatches;

	m_DebugInfo.hWndParent = hWndParent;
	m_DebugInfo.lpTitle = (ebLPSTR) pszTitle;
	m_DebugInfo.x = pDebugDlgInfo->m_x;
	m_DebugInfo.y = pDebugDlgInfo->m_y;
	m_DebugInfo.width = pDebugDlgInfo->m_nWidth;
	m_DebugInfo.height = pDebugDlgInfo->m_nHeight;
	m_DebugInfo.hFont = hFont;
	
	m_DebugInfo.isMatchCase = pDebugDlgInfo->m_bMatchCase;
	::strcpy(m_DebugInfo.findtext,pDebugDlgInfo->m_szFindText);
	::strcpy(m_DebugInfo.reptext,pDebugDlgInfo->m_szReplaceText);
	
	m_DebugInfo.lParam = dwParam;

	// Initialize remaining members of m_DebugInfo
	m_DebugInfo.lpScriptOut = NULL;
	// set to NULL
	CebCode::Initialize(&m_DebugInfo.hCodeOut);
	m_DebugInfo.lpWatchesOut = NULL;
}

CebDebuggerDlg::~CebDebuggerDlg()
{
}

int CebDebuggerDlg::Invoke()
{
	m_nScode = ::ebDebugger(&m_DebugInfo);
	
	if (!IsError()) SaveState();
	if (IsSave()) SaveScript();
	return m_nScode;
}

void CebDebuggerDlg::SaveState()
{
	m_pDebugDlgInfo->m_x = m_DebugInfo.x;
	m_pDebugDlgInfo->m_y = m_DebugInfo.y;
	m_pDebugDlgInfo->m_nWidth = m_DebugInfo.width;
	m_pDebugDlgInfo->m_nHeight = m_DebugInfo.height;
	m_pDebugDlgInfo->m_nWatchWindowHeight = m_DebugInfo.watchwindowheight;
	
	m_pDebugDlgInfo->m_bMatchCase = m_DebugInfo.isMatchCase;
		
	if (m_pDebugDlgInfo->m_szFindText) { // Copy back the FindText string
		::strcpy(m_pDebugDlgInfo->m_szFindText,m_DebugInfo.findtext);
	}
	if (m_pDebugDlgInfo->m_szReplaceText) { // Copy back the Replace string
		::strcpy(m_pDebugDlgInfo->m_szReplaceText,m_DebugInfo.reptext);
	}

	m_pDebugDlgInfo->m_pWatches = m_DebugInfo.lpWatchesOut;
}

void CebDebuggerDlg::SaveScript()
{
	m_pDebugDlgInfo->m_pScript = m_DebugInfo.lpScriptOut;
	if (m_pDebugDlgInfo->GetCode())
		m_DebugInfo.hCodeOut = m_pDebugDlgInfo->GetCode();
	else
		CebCode::FreeCode(m_DebugInfo.hCodeOut);
}

#endif // EBWIN | EBWIN32 | EBOS2
