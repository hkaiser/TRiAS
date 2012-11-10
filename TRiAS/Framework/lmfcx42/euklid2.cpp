#include	"stdafx.h"

#ifdef LAFX_GEOM_SEG
#pragma code_seg(LAFX_GEOM_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: euklid2.cpp 1.2 1996/08/20 19:10:27 andy Exp andy $";
/* $Log: euklid2.cpp $
// Revision 1.2  1996/08/20  19:10:27  andy
// initial version
//
// Revision 1.1  1996/07/12  17:16:11  andy
// initial version
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Schnittpunkt zweier Geraden

BOOL AFX_EXT_API CutPoint( POINTL& P, const CLine& L1, const CLine& L2 )
{
	P.x = 0;
	P.y = 0;

	double	q1 = L1.B() * L2.A() - L2.B() * L1.A();
	double	q2 = L1.A() * L2.B() - L2.A() * L1.B();
	
	if( q1 == 0.0 || q2 == 0.0 )
		return FALSE;

	double	p1 = L2.B() * L1.C() - L1.B() * L2.C();
	double	p2 = L2.A() * L1.C() - L1.A() * L2.C();

	P.x = (long) ( p1 / q1 );
	P.y = (long) ( p2 / q2 );
	return TRUE;
}

BOOL AFXAPI CutPoint( POINT& P, const CLine& L1, CLine& L2 )
{
	P.x = 0;
	P.y = 0;

	double	q1 = L1.B() * L2.A() - L2.B() * L1.A();
	double	q2 = L1.A() * L2.B() - L2.A() * L1.B();
	
	if( q1 == 0.0 || q2 == 0.0 )
		return FALSE;

	double	p1 = L2.B() * L1.C() - L1.B() * L2.C();
	double	p2 = L2.A() * L1.C() - L1.A() * L2.C();

	P.x = (long) ( p1 / q1 );
	P.y = (long) ( p2 / q2 );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// Schnittpunkt zweier Strecken (!)

BOOL AFX_EXT_API CutPoint( POINTL& rP, CStraith& rS1, CStraith& rS2 )
{
	CLine	L1( rS1 );
	CLine	L2( rS2 );
	
//	if( CutPoint( rP, L1, L2 ) && ( rS1.P0().x - rP.x  ) * ( m_P1.x - rP.x ) <= 0.0 )
	return CutPoint( rP, L1, L2 );
}

AFX_EXT_API  CStraith& HalfAngle( CStraith& rS1, CStraith& rS2, long length )
{
	static	CStraith	S;
	double	phi1 = atan2( (double) ( rS1.P1().y - rS1.P0().y ), (double) ( rS1.P1().x - rS1.P0().x ) ) + halfPI;
	double	phi2 = atan2( (double) ( rS2.P1().y - rS2.P0().y ), (double) ( rS2.P1().x - rS2.P0().x ) ) + halfPI;

	phi1 = phi1 < 0 ? phi1 + twoPI : phi1;
	phi2 = phi2 < 0 ? phi2 + twoPI : phi2;
	
	phi1 = ( phi1 + phi2 ) / 2;
	while( phi1 > twoPI )
		phi1 -= twoPI;

	if( rS1.P1() == rS2.P0() )
	{
		DPOINT	P2, P3;
		P2.x = rS1.P1().x + ( (length / 2) * cos( phi1 ) );
		P2.y = rS1.P1().y + ( (length / 2) * sin( phi1 ) );
		P3.x = rS1.P1().x - ( P2.x - rS1.P1().x );
		P3.y = rS1.P1().y - ( P2.y - rS1.P1().y );
		S.Construct( P2, P3 );
	}
	return S;
}
