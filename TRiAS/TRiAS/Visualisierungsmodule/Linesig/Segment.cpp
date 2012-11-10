#include	"stdafx.h"
#include	"metafile.h"

static BOOL CalculateCropPoint( DPOINT& p, DPOINT& s1P0, DPOINT& s1P1, DPOINT& s2P0, DPOINT& s2P1 ) {
	double	A1 = s1P1.y - s1P0.y;
	double	B1 = s1P0.x - s1P1.x;
	double	C1 = s1P1.x * s1P0.y - s1P0.x * s1P1.y;

	double	A2 = s2P1.y - s2P0.y;
	double	B2 = s2P0.x - s2P1.x;
	double	C2 = s2P1.x * s2P0.y - s2P0.x * s2P1.y;
	
	double	NX = A1 * B2 - A2 * B1;
	double	NY = A2 * B1 - A1 * B2;

	if( 0 == NX || 0 == NY )
		return FALSE;
	
	double	ZX = B1 * C2 - B2 * C1;
	double	ZY = A1 * C2 - A2 * C1;

	if( fabs( ZX ) < 0.05 || fabs( ZY ) < 0.05 ) {
		p.x = ( s1P1.x + s2P0.x ) / 2;
		p.y = ( s1P1.y + s2P0.y ) / 2;
	} else {
		p.x = ZX / NX;
		p.y = ZY / NY;
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////
//
// Das Segment...
//
//   m_ptBound[3] +----------------------------------+ m_ptBound[2]
//                |                                  |
//                |                                  |
//           m_P0 + - - - - - - - - - - - - - - - - -+ m_P1
//                |                                  |
//                |                                  |
//   m_ptBound[0] +----------------------------------+ m_ptBound[1]
//
// Das Segment...
//
//   m_ptClip[0]  +----------------------------------+ m_ptClip[5]
//                |                                  |
//                +                                  +
//                |                                  |
//   m_ptClip[1]  + - - - - - - - - - - - - - - - - -+ m_ptClip[4]
//                |                                  |
//                +                                  +
//                |                                  |
//   m_ptClip[2]  +----------------------------------+ m_ptClip[3]
//

SEGMENT::SEGMENT( const DRECT& rc ) {
	memset( (void FAR*) this, 0x00, sizeof( *this ) );
	m_rectWidth = rc.right - rc.left;
	m_rectTop = rc.top;
	m_rectBtm = rc.bottom;
}

void SEGMENT::Mark( CDC *pDC ) {
	CStraith	s;
	COLORREF	colors[6] = { RGB_RED, RGB_GREEN, RGB_BLUE, RGB_BLUE, RGB_GREEN, RGB_RED };

	s.Construct( m_P0, m_P1 );		
	::MarkStraith( pDC, s, RGB_BLACK, 1 );
	for( int i = 0; i < 5; i++ ) {
		s.Construct( m_ptClip[i], m_ptClip[i+1] );
		::MarkStraith( pDC, s, colors[i], 1 ); 
	}
	s.Construct( m_ptClip[i], m_ptClip[0] );
	::MarkStraith( pDC, s, colors[i], 1 ); 
}

void SEGMENT::Construct( ) {	
	m_dx = m_P1.x - m_P0.x;
	m_dy = m_P1.y - m_P0.y;
	m_length = sqrt( m_dx * m_dx + m_dy * m_dy );
	m_phi = atan2( m_dy, m_dx );
#ifdef _DEBUG
	m_dms = ( m_phi * 180 ) / PI;
#endif

	m_dx = m_rectWidth * cos( m_phi );
	m_dy = m_rectWidth * sin( m_phi );

	double	sinPhi = sin( m_phi - halfPI );
	double	cosPhi = cos( m_phi - halfPI );

	double dx = cosPhi * m_rectTop;
	double dy = sinPhi * m_rectTop;

	m_ptBound[0].x = m_P0.x + dx; m_ptBound[0].y = m_P0.y + dy;
	m_ptBound[1].x = m_P1.x + dx; m_ptBound[1].y = m_P1.y + dy;

	dx = cosPhi * m_rectBtm;
	dy = sinPhi * m_rectBtm;

	m_ptBound[3].x = m_P0.x + dx; m_ptBound[3].y = m_P0.y + dy;
	m_ptBound[2].x = m_P1.x + dx; m_ptBound[2].y = m_P1.y + dy;

	m_ptClip[0] = m_ptBound[0];
	m_ptClip[1] = m_P0;
	m_ptClip[2] = m_ptBound[3];
	m_ptClip[3] = m_ptBound[2];
	m_ptClip[4] = m_P1;
	m_ptClip[5] = m_ptBound[1];
}

SEGMENT& SEGMENT::operator=( SEGMENT& cp ) {
	m_length = cp.m_length;
	m_phi = cp.m_phi;
#ifdef _DEBUG
	m_dms = cp.m_dms;
#endif
	m_dx = cp.m_dx;
	m_dy = cp.m_dy;
	m_P0 = cp.m_P0;
	m_P1 = cp.m_P1;
	memcpy( (void FAR*) m_ptBound, (void FAR*) cp.m_ptBound, sizeof( m_ptBound ) );
	memcpy( (void FAR*) m_ptClip, (void FAR*) cp.m_ptClip, sizeof( m_ptClip ) );
	return *this;
}

static const double phiDiffMin = 0.35;

void SEGMENT::Clip( SEGMENT& cp ) {
	DPOINT		pt;
	if( !CalculateCropPoint( pt, m_ptClip[0], m_ptClip[5], cp.m_ptClip[0], cp.m_ptClip[5] ) )
		return;
	m_ptClip[5] = cp.m_ptClip[0] = pt;
	if( !CalculateCropPoint( pt, m_ptClip[2], m_ptClip[3], cp.m_ptClip[2], cp.m_ptClip[3] ) )
		return;
	m_ptClip[3] = cp.m_ptClip[2] = pt;

	double	phi = cp.Phi() - Phi();
	double	dms = phi * 180 / PI;
	phi = fabs( phi );
	if( PI - phi < phiDiffMin ) {
		if( phi < 0 ) {
			m_ptClip[3] = m_ptBound[2];
			cp.m_ptClip[0] = cp.m_ptBound[0];
		} else {
			m_ptClip[3] = m_ptBound[2];
			cp.m_ptClip[2] = cp.m_ptBound[3];
		}

		phi = ( Phi() + cp.Phi() ) / 2;
		dms = phi * 180 / PI;
		double dx = sin( phi ) * m_rectTop;
		double dy = cos( phi ) * m_rectTop;
		m_ptClip[4].x += dx; cp.m_ptClip[1].x += dx;
		m_ptClip[4].y += dy; cp.m_ptClip[1].y += dy;
	}
}

void SEGMENT::CreateClipRgn( CDC *pDC, CRgn& rg ) {
	POINT	pts[6];
	for( int i = 0; i < 6; i++ ) {
		pts[i].x = froundl(m_ptClip[i].x);
		pts[i].y = froundl(m_ptClip[i].y);
	}
	pDC->LPtoDP( pts, 6 );
	rg.CreatePolygonRgn( pts, 6, WINDING );
}

void SEGMENT::Rotate( double phi ) {
	CDPoint	P;
	double	myPhi = m_phi + phi;
	double dx = cos( myPhi ) * Length();
	double dy = sin( myPhi ) * Length();
	m_P1.x = m_P0.x + dx;
	m_P1.y = m_P0.y + dy;
	Construct( );
}

void SEGMENT::Offset( double dx, double dy ) {
	m_P0.x += dx; m_P0.y += dy;
	m_P1.x += dx; m_P1.y += dy;
	Construct();
}
