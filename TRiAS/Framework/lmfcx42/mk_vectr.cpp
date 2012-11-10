#include	"stdafx.h"
#include	<math.h>

#ifdef LAFX_MATH_SEG
#pragma code_seg(LAFX_MATH_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: mk_vectr.cpp 1.1 1996/07/12 17:16:22 andy Exp $";
/* $Log: mk_vectr.cpp $
// Revision 1.1  1996/07/12  17:16:22  andy
// initial version
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CVector,CObject,0x0001)

#define new	DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////

void CVector::Construct( const short r )
{
	m_r = r;
	if( m_data != NULL ) delete[] m_data;
//	m_data = new double[ m_r * sizeof( double ) ];
	m_data = new double[ m_r ];
	Clear( );
}

void CVector::Load( const short nValues, const double *v, short startRow )
{
	memcpy( m_data + startRow, v, nValues * sizeof( double ) );
}

void CVector::Load( const short nValues, const long *v, short startRow )
{
	long 	*pL = (long*) v;
	double	*pD = m_data + startRow;

	for( int i = 0; i < nValues; i++ )
		*pD++ = (double) *pL++;
}

void CVector::Copy( const CVector& rV )
{
	Construct( rV.m_r );
	memcpy( m_data, rV.m_data, m_r * sizeof( double ) );
}

CVector& CVector::Add( const CVector& rV )
{
	if( rV.m_r != m_r ) return *this;
	double	*pD = m_data;
	double	*pS = rV.m_data;
	for( int i = 0; i < m_r; i++ ) *pD++ += *pS++;
	return *this;
}

CVector& CVector::Multiply( const double v )
{
	double	*pD = m_data;
	for( int i = 0; i < m_r; i++ ) *pD++ *= v;
	return *this;
}

double CVector::Multiply( const CVector& rV )
{
	if( rV.m_r != m_r ) return 0.0;
	double	*pS1 = m_data;
	double	*pS2 = rV.m_data;
	double	v = 0.0;
	for( int i = 0; i < m_r; i++ ) v += *pS1++ * *pS2++;
	return v;
}
