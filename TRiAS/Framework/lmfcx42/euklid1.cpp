#include	"stdafx.h"

#ifdef LAFX_GEOM_SEG
#pragma code_seg(LAFX_GEOM_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: euklid1.cpp 1.1 1996/07/12 17:16:12 andy Exp $";
/* $Log: euklid1.cpp $
// Revision 1.1  1996/07/12  17:16:12  andy
// initial version
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL( CLine, CObject, 0 );
IMPLEMENT_SERIAL( CStraith, CObject, 0 );
IMPLEMENT_SERIAL( CTriangle, CObject, 0 );

#define	new DEBUG_NEW

void CLine::Serialize( CArchive& ar )
{
	CObject::Serialize( ar );
	if( ar.IsStoring( ) )
	{
		ar << m_A;
		ar << m_B;
		ar << m_C;
	}
	else
	{
		ar >> m_A;
		ar >> m_B;
		ar >> m_C;
	}
}

#ifdef	_DEBUG
void CLine::Dump( CDumpContext& dc ) const
{
	ASSERT_VALID( this );
	CObject::Dump(dc);
	dc << "(A,B,C)[" << m_A << "," << m_B << "," << m_C << "]\n";
}

void CLine::AssertValid( ) const
{
	CObject::AssertValid( );
	ASSERT( A != 0 || B != 0 );
}
#endif		// _DEBUG

//////////////////////////////////////////////////////////////////////////

void CStraith::Serialize( CArchive& ar )
{
	CObject::Serialize( ar );
	if( ar.IsStoring( ) )
	{
		ar << m_P0.x;
		ar << m_P0.y;
		ar << m_P1.x;
		ar << m_P1.y;
	}
	else
	{
		ar >> m_P0.x;
		ar >> m_P0.y;
		ar >> m_P1.x;
		ar >> m_P1.y;
	}
}

#ifdef	_DEBUG
void CStraith::Dump( CDumpContext& dc ) const
{
	ASSERT_VALID( this );
	CObject::Dump( dc );
	dc << "P0[" << m_P0.x << "," << m_P0.y << "]\n";
	dc << "P1[" << m_P1.x << "," << m_P1.y << "]\n";
}

void CStraith::AssertValid( ) const
{
	CObject::AssertValid( );
	ASSERT( m_P0 != m_P1 && m_P0 != m_P1 );
}
#endif

//////////////////////////////////////////////////////////////////////////

void CTriangle::Serialize( CArchive& ar )
{
	CObject::Serialize( ar );
	if( ar.IsStoring( ) )
	{
		ar << m_p0.x;
		ar << m_p0.y;
		ar << m_p1.x;
		ar << m_p1.y;
		ar << m_p2.x;
		ar << m_p2.y;
	}
	else
	{
		ar >> m_p0.x;
		ar >> m_p0.y;
		ar >> m_p1.x;
		ar >> m_p1.y;
		ar >> m_p2.x;
		ar >> m_p2.y;
	}
}

#ifdef	_DEBUG
void CTriangle::Dump( CDumpContext& dc ) const
{
	ASSERT_VALID( this );
	CObject::Dump( dc );
	dc << "P0[" << m_p0.x << "," << m_p0.y << "]\n";
	dc << "P1[" << m_p1.x << "," << m_p1.y << "]\n";
	dc << "P2[" << m_p2.x << "," << m_p2.y << "]\n";
}

void CTriangle::AssertValid( ) const
{
	CObject::AssertValid( );
	ASSERT( m_p0 != m_p1 && m_p1 != m_p2 && m_p2 != m_p0 );
}
#endif

//////////////////////////////////////////////////////////////////////////

void CDRect::NormalizeRect()
{
	double nTemp;
	if (left > right)
	{
		nTemp = left;
		left = right;
		right = nTemp;
	}
	if (top > bottom)
	{
		nTemp = top;
		top = bottom;
		bottom = nTemp;
	}
}

CDRect CDRect::MulDiv( double nMultiplier, double nDivisor) const
{
	return CDRect(
		( left * nMultiplier ) / nDivisor,
		( top * nMultiplier ) / nDivisor,
		( right * nMultiplier ) / nDivisor,
		( bottom * nMultiplier ) / nDivisor);
}

BOOL CDRect::IntersectRect(LPCDRECT lpRect1, LPCDRECT lpRect2)
{
	if( lpRect1->right <= lpRect2->left || lpRect1->bottom <= lpRect2->top
		|| lpRect2->right <= lpRect1->left || lpRect2->bottom <= lpRect1->top )
	{
		SetRectEmpty();
		return FALSE;
	}
	SetRect( max( lpRect1->left, lpRect2->left ),
			max( lpRect1->top, lpRect2->top ),
			min( lpRect1->right, lpRect2->right ),
			min( lpRect1->bottom, lpRect2->bottom )
			);
	return TRUE;
}

BOOL CDRect::UnionRect(LPCDRECT lpRect1, LPCDRECT lpRect2)
{
	SetRect( min( lpRect1->left, lpRect2->left ),
			min( lpRect1->top, lpRect2->top ),
			max( lpRect1->right, lpRect2->right ),
			max( lpRect1->bottom, lpRect2->bottom )
			);
	return TRUE;
}

BOOL CDRect::SubtractRect(LPCDRECT lpRectSrc1, LPCDRECT lpRectSrc2)
{
	CDRect	r;
	r.IntersectRect( lpRectSrc1, lpRectSrc2 );
	SetRect( lpRectSrc1->left - r.left,
		lpRectSrc1->top - r.top,
		lpRectSrc1->right - r.right,
		lpRectSrc1->bottom - r.bottom
		);
	return TRUE;
}
