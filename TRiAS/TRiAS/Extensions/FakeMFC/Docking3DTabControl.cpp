// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 02.03.2001 21:54:13 
//
// @doc
// @module Docking3DTabControl.cpp | Definition of the <c CDocking3DTabControl> class

#include "stdafx.h"

#if defined(_USE_DOCKEDTABWINDOW)

#include "fakemfc.h"
#include "Docking3DTabControl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDocking3DTabControl, SEC3DTabControl)

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// CDocking3DTabControl

CDocking3DTabControl::CDocking3DTabControl()
{
}

CDocking3DTabControl::~CDocking3DTabControl()
{
}


BEGIN_MESSAGE_MAP(CDocking3DTabControl, SEC3DTabControl)
	//{{AFX_MSG_MAP(CDocking3DTabControl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDocking3DTabControl::InitializeFonts(DWORD dwStyle)
{
	// incase they already exist
	m_fonts[SEC3DTAB_ACTIVE].DeleteObject();
	m_fonts[SEC3DTAB_INACTIVE].DeleteObject();

	// Initialize the LOGFONT structure for font creation
LOGFONT lf;

	lf.lfHeight = -8;
	lf.lfWidth = 0;
	lf.lfEscapement = 0;	// default, for top and bottom tabs
	lf.lfOrientation = 0;
	lf.lfWeight = FW_NORMAL;
	lf.lfItalic = FALSE;
	lf.lfUnderline = FALSE;
	lf.lfStrikeOut = 0;
#ifdef _SEC_INTL_
	lf.lfCharSet = DEFAULT_CHARSET;
#else
	lf.lfCharSet = ANSI_CHARSET;
#endif
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = DEFAULT_QUALITY;
	lf.lfPitchAndFamily = DEFAULT_PITCH | FF_SWISS;
	_tcsncpy(lf.lfFaceName, _T("MS Sans Serif"), LF_FACESIZE);

	// rotated fonts
	if (dwStyle & TCS_TABS_ON_LEFT)
		lf.lfEscapement = 900;
	else if (dwStyle & TCS_TABS_ON_RIGHT)
		lf.lfEscapement = -900; 
	
// Create Fonts
	m_fonts[SEC3DTAB_INACTIVE].CreateFontIndirect(&lf);

// Make font of active tab bold
//	lf.lfWeight += 200;
	m_fonts[SEC3DTAB_ACTIVE].CreateFontIndirect(&lf);
}

///////////////////////////////////////////////////////////////////////////////
//// CDocking3DTabControl message handlers

#endif // defined(_USE_DOCKEDTABWINDOW)
