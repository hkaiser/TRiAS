#include	"stdafx.h"

#ifdef LAFX_WINF_SEG
#pragma code_seg(LAFX_WINF_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: coordbg.cpp 1.1 1996/07/12 17:16:20 andy Exp $";
/* $Log: coordbg.cpp $
// Revision 1.1  1996/07/12  17:16:20  andy
// initial version
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

#define new DEBUG_NEW

//////////////////////////////////////////////////////////////////////////

void AFX_EXT_API MarkPoint( CDC* pDC, const POINT& pPt, COLORREF color, short width )
{
	CPen		pen, *oldPen;

	pen.CreatePen( PS_SOLID, width, color );
	oldPen = pDC->SelectObject( &pen );

	pDC->MoveTo( pPt.x + 10, pPt.y ); 
	pDC->LineTo( pPt.x - 10, pPt.y );
	pDC->MoveTo( pPt.x, pPt.y + 10 ); 
	pDC->LineTo( pPt.x, pPt.y - 10 );

	pDC->SelectObject( oldPen );
	pen.DeleteObject( );
	::GdiFlush();
}

void AFX_EXT_API MarkPoint( CDC* pDC, const POINTL& pPt, COLORREF color, short width )
{
	CPen		pen, *oldPen;
	
	pen.CreatePen( PS_SOLID, width, color );
	oldPen = pDC->SelectObject( &pen );
	
	pDC->MoveTo( (int) pPt.x + 10, (int) pPt.y ); 
	pDC->LineTo( (int) pPt.x - 10, (int) pPt.y );
	pDC->MoveTo( (int) pPt.x, (int) pPt.y + 10 ); 
	pDC->LineTo( (int) pPt.x, (int) pPt.y - 10 );
	
	pDC->SelectObject( oldPen );
	pen.DeleteObject( );
	::GdiFlush();
}

void AFX_EXT_API MarkPoint( CDC* pDC, const DPOINT& pPt, COLORREF color, short width )
{
	POINTL	p;
	p.x = froundl( pPt.x );
	p.y = froundl( pPt.y );
	MarkPoint( pDC, p, color, width );
}

void AFX_EXT_API MarkStraith( CDC* pDC, const CStraith& pS, COLORREF color, short width )
{	
	::MarkPoint( pDC, pS.P0(), color, width );
	::MarkPoint( pDC, pS.P1(), color, width );
	CPen	pen, *oldPen;
	pen.CreatePen( PS_SOLID, width, color );
	oldPen = pDC->SelectObject( &pen );
	pDC->MoveTo( froundl( pS.P0().x ), froundl( pS.P0().y ) );
	pDC->LineTo( froundl( pS.P1().x ), froundl( pS.P1().y ) );
	pDC->SelectObject( oldPen );
	pen.DeleteObject();
	::GdiFlush();
}

void AFX_EXT_API MarkLine( CDC* pDC, const CLine& pL, COLORREF color, short width )
{
}

void AFX_EXT_API MarkRect( CDC* pDC, const CRect& pR, COLORREF color, short width )
{
	CPen	pen, *oldPen;
	pen.CreatePen( PS_SOLID, width, color );
	oldPen = pDC->SelectObject( &pen );
	pDC->MoveTo( pR.left, pR.bottom );
	pDC->LineTo( pR.right, pR.bottom );
	pDC->LineTo( pR.right, pR.top );
	pDC->LineTo( pR.left, pR.top );
	pDC->LineTo( pR.left, pR.bottom );
	pDC->SelectObject( oldPen );
	pen.DeleteObject();
	::GdiFlush();
}
