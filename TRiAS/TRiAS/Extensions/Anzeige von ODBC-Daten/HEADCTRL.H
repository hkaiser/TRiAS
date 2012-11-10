// This is a part of the Objective Grid C++ Library.
// Copyright (C) 1995-1997 ClassWorks, Stefan Hoenig.
// All rights reserved.
//
// This source code is only intended as a supplement to
// the Objective Grid Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Grid product.
//

// HeadCtrl.h : header file
//

#ifndef _GXCTRLI_H_
#include "gxctrli.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CHeaderBtnControl control

class CHeaderBtnControl: public CGXStatic
{
	DECLARE_CONTROL(CHeaderBtnControl)

public:
	// Member functions

	CHeaderBtnControl(CGXGridCore* pGrid);
	virtual ~CHeaderBtnControl();

	virtual void InvertBorders(CDC* pDC, const CRect& r);
	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	virtual BOOL MouseMove(UINT nFlags, CPoint pt, UINT nHitState);
	virtual BOOL LButtonDown(UINT nFlags, CPoint pt, UINT nHitState);
	virtual BOOL RButtonDown(UINT nFlags, CPoint pt, UINT nHitState);
	virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	virtual BOOL RButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);

	// Attributes:
protected:
	BOOL m_bPressed;
	BOOL m_bMouseDown;
};

/////////////////////////////////////////////////////////////////////////////
