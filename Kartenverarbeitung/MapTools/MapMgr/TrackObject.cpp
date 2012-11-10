#include "stdafx.h"
#include "TrackObject.h"

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: trackobject.cpp 1.1 1996/07/12 10:50:03 andy Exp andy $";
/* $Log: trackobject.cpp $
// Revision 1.1  1996/07/12  10:50:03  andy
// initial version
//
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

CTrackObject::CTrackObject() {
	m_bTrackOn = FALSE;
}

CTrackObject::~CTrackObject() {
	ASSERT( FALSE == m_bTrackOn );
}

CTrackPoint::CTrackPoint() : CTrackObject() {
}

CTrackPoint::~CTrackPoint() {
}

void CTrackPoint::Invert(CDC *pDC) {
	CPen	pen1, pen2, *pOldPen;
	int		oldROP;

	pen1.CreatePen( PS_SOLID, 3, RGB( 0x0f, 0x0f, 0x0f ) );
	pen2.CreatePen( PS_SOLID, 3, RGB( 0, 0, 0 ) );
	oldROP = pDC->SetROP2( R2_NOTXORPEN );
	pOldPen = pDC->SelectObject( &pen1 );

	pDC->MoveTo( froundl( x - 10 ), froundl( y ) );
	pDC->LineTo( froundl( x + 10 ), froundl( y ) );
	pDC->MoveTo( froundl( x ), froundl( y - 10 ) );
	pDC->LineTo( froundl( x ), froundl( y + 10 ) );

	pDC->SelectObject( pOldPen );
	pDC->SetROP2( oldROP );
}

void CTrackPoint::Attach(LPVOID lpPoint) {
	m_pPoint = (LPDPOINT) lpPoint;
}

void CTrackPoint::StartTracking(CDC *pDC, LPPOINT point) {
	ASSERT( FALSE == m_bTrackOn );
	m_bTrackOn = TRUE;
	x = point->x;
	y = point->y;
	Invert(pDC);
}

void CTrackPoint::Track( CDC *pDC, LPPOINT point ) {
	if( FALSE == m_bTrackOn )
		return;
	Invert(pDC);
	x = point->x;
	y = point->y;
	Invert(pDC);
}

void CTrackPoint::StopTracking(CDC *pDC, LPPOINT point) {
	ASSERT( TRUE == m_bTrackOn );
	Invert(pDC);
	x = point->x;
	y = point->y;
	m_bTrackOn = FALSE;
}

void CTrackPoint::StopTracking(LPPOINT point) {
	m_pPoint->x = point->x;
	m_pPoint->y = point->y;
}

CDPoint CTrackPoint::GetTrackPoint() {
	ASSERT( NULL != m_pPoint );
	return CDPoint( m_pPoint->x, m_pPoint->y );
}

CDRect CTrackPoint::GetBoundingRect() {
	ASSERT( NULL != m_pPoint );
	return CDRect( m_pPoint->x - 100, m_pPoint->y - 100, m_pPoint->x + 100, m_pPoint->y + 100 );
}
