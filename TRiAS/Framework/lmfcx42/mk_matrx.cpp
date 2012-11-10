#include	"stdafx.h"
#include	<math.h>

#ifdef LAFX_MATH_SEG
#pragma code_seg(LAFX_MATH_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CMatrix,CObject,0x0001)

#define new	DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////

void CMatrix::Construct( const short n )
{
	m_r = m_c = n;
//	m_data = new double[ m_r * m_c * sizeof( double ) ];
	m_data = new double[ m_r * m_c ];
	Clear( );
}

void CMatrix::Construct( const short r, const short c )
{
	m_r = r;
	m_c = c;
	if( NULL != m_data )
		delete[] m_data;
//	m_data = new double[ m_r * m_c * sizeof( double ) ];
	m_data = new double[ m_r * m_c ];
	Clear( );
}

void CMatrix::Load( const short nRows, const double *v, short startRow )
{
	memcpy( m_data + startRow * m_c, v, nRows * m_c * sizeof( double ) );
}

void CMatrix::Load( const short nRows, const long *v, short startRow )
{
	long 	*pL = (long*) v;
	double	*pD = m_data + startRow * m_c;

	for( int i = 0; i < nRows; i++ )
		for( int ii = 0; ii < m_c;  ii++ )
			*pD++ = (double) *pL++;
}

void CMatrix::Copy( const CMatrix& rM )
{
	Construct( rM.m_r, rM.m_c );
	memcpy( m_data, rM.m_data, m_r * m_c * sizeof( double ) );
}

CMatrix& CMatrix::Add( const CMatrix& rM )
{
	if( m_r == rM.m_r && m_c == rM.m_c )
	{
		double	*pS1 = rM.m_data;
		double	*pD  = m_data;

		for( int i = 0; i < m_r; i++ )
		{
			for( int ii = 0; ii < m_c; ii++ )
			{
				*pD++ += *pS1++;
			}
		}
	}
	return *this;
}

CMatrix& CMatrix::Add( const CMatrix& rM1, const CMatrix& rM2 )
{
	if( rM1.m_r == rM2.m_r && rM1.m_c == rM2.m_c )
	{
		Construct( rM1.m_r, rM2.m_c );
		double	*pS1 = rM1.m_data;
		double	*pS2 = rM2.m_data;
		double	*pD  = m_data;

		for( int i = 0; i < m_r; i++ )
		{
			for( int ii = 0; ii < m_c; ii++ )
			{
				*pD++ = *pS1++ + *pS2++;
			}
		}
	}
	return *this;
}

CMatrix& CMatrix::Multiply( const CMatrix& rM1, const CMatrix& rM2 )
{
	if( rM1.m_c == rM2.m_r )
	{
		Construct( rM1.m_r, rM2.m_c );
		double	*pD, *pS1, *pS2;
		int	i, j, k;

		pD = m_data;
		for( i = 0; i < m_r; i++ )
		{
			for( j = 0; j < m_c; j++ )
			{
				pS1 = &rM1.m_data[ i * rM1.m_c ];
				pS2 = &rM2.m_data[ j ];
				*pD = 0.0;
				for( k = 0; k < rM1.m_c; k++ )
				{
					*pD += *pS1 * *pS2;
					pS1 += 1;
					pS2 += rM2.m_c;
				}
				pD++;
			}
		}
	}
	return *this;
}

int CMatrix::GaussBanach( CVector& rVC, CVector& rVR )
{
	CVector	Vz( m_r );				// Zwischenvektor
	CMatrix	M( m_r, m_c );				// Rechenmatrix
	short	r, c, cc;				// Zählvariablen
	
	double	d1;
	
	for( r = 0; r < m_r; r++ )
	{
		for( c = 0; c < r; c++ )		// c(i,i)
		{
			M( r, c ) = operator()( r, c );
			for( cc = 0; cc < c; cc++ ) M( r, c ) += M( r, cc ) * M( cc, c );
			d1 = M( cc, c );
			if( 0.0 == d1 ) return -(r + 1);
				M( r, c ) /= -d1; 
		}
		for( ; c < m_c; c++ )			// b(i,i)
		{
			M( r, c ) = operator()( r, c );
			for( cc = 0; cc < r; cc++ ) M( r, c ) += M( r, cc ) * M( cc, c );
		}
		Vz( r ) = rVC( r );
		for( cc = 0; cc < r; cc++ ) Vz( r ) += M( r, cc ) * Vz( cc );
	}
	for( r = 0, c = m_c - 1; r < m_r; r++, c-- )	// Ergebnisvektor
	{
		rVR( c ) = Vz( c );
		cc = m_c - 1;
		for( ; cc > c; cc-- ) { rVR( c ) -= M( c, cc ) * rVR( cc ); }
		d1 = M( c, c );
		if( 0.0 == d1 ) return -(r + 1);
		rVR( c ) /= d1;
	}
	return 0;
}

BOOL AFX_EXT_API GaussBanach( CVector& rVR, const CMatrix& M, const CVector& rVC, CMathException *pE /*=NULL*/ )
{
	short	m_r = M.R();
	short	m_c = M.C();
	CVector	Vz( m_r );				// Zwischenvektor
	CMatrix	Mz( m_r, m_c );			// Rechenmatrix
	short	r, c, cc;				// Zählvariablen
	
	double	d1;
	
	for( r = 0; r < m_r; r++ )
	{
		for( c = 0; c < r; c++ )		// c(i,i)
		{
			Mz( r, c ) = M( r, c );
			for( cc = 0; cc < c; cc++ )
				Mz( r, c ) += Mz( r, cc ) * Mz( cc, c );
			d1 = Mz( cc, c );
			if( 0.0 == d1 )
			{
				if( NULL != pE )
				{
					pE->m_cause = CMathException::errDIV0;
					pE->m_strCause.Format( _T("GaussBanach(1): %d,%d,%lf"), r, c, d1 );
				}
				return FALSE;
			}
			Mz( r, c ) /= -d1;
		}
		for( ; c < m_c; c++ )			// b(i,i)
		{
			Mz( r, c ) = M( r, c );
			for( cc = 0; cc < r; cc++ )
				Mz( r, c ) += Mz( r, cc ) * Mz( cc, c );
		}
		Vz( r ) = rVC( r );
		for( cc = 0; cc < r; cc++ )
			Vz( r ) += Mz( r, cc ) * Vz( cc );
	}
	for( r = 0, c = m_c - 1; r < m_r; r++, c-- )	// Ergebnisvektor
	{
		rVR( c ) = Vz( c );
		cc = m_c - 1;
		for( ; cc > c; cc-- )
		{
			rVR( c ) -= Mz( c, cc ) * rVR( cc );
		}
		d1 = Mz( c, c );
		if( 0.0 == d1 )
		{
			if( NULL != pE )
			{
				pE->m_cause = CMathException::errDIV0;
				pE->m_strCause.Format( _T("GaussBanach(2): %d,%lf"), r, d1 );
			}
			return FALSE;
		}
		rVR( c ) /= d1;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//	Normen einer Matrix;  
//	- nur definiert für (n,n)-Matrizen
//	- -1 wird als Fehlerwert zurückgegeben (eine Norm ist immer > 0 )
/////////////////////////////////////////////////////////////////////////////

#pragma	optimize( "", off )

double	CMatrix::MNorm( )
{
	if( m_r != m_c ) return -1;
	double	aij, dMax = 0;
	double	*pd = m_data;

	int		i, ii;
	
	for( i = 0; i < m_r; i++ )
	{
		for( ii = 0; ii < m_c; ii++ )
		{
			aij = fabs( *pd );
			if( aij > dMax )
				dMax = aij;
		}
	}
	return dMax;
}

/////////////////////////////////////////////////////////////////////////////

void CMatrix::Serialize( CArchive& ar )
{
}

void CVector::Serialize( CArchive& ar )
{
}
