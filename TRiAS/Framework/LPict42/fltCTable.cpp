#include "stdafx.h"
#include "LPictImpl.h"

#include <math.h>

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//

IMPLEMENT_DYNAMIC( CColorFilter, CObject );
IMPLEMENT_SERIAL( CRGBtoHSB, CColorFilter, 1 );
IMPLEMENT_SERIAL( CHSBtoRGB, CColorFilter, 1 );
IMPLEMENT_SERIAL( CExpandColorChannel, CColorFilter, 1 );
IMPLEMENT_SERIAL( CArrangeColorChannels, CColorFilter, 1 );

#define	new	DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
//

BOOL CRGBtoHSB::Filter( LPRGBQUAD pInClut, LPRGBQUAD pOutClut, int nColors, CFilterProgress* proc ) {
	return TRUE;
}

COLORREF CRGBtoHSB::Filter( COLORREF color, CFilterProgress* proc ) {
	return operator()( color );
}

const COLORREF CRGBtoHSB::operator()( COLORREF color ) {
	double R = (double) GetRValue(color);
	double G = (double) GetGValue(color);
	double B = (double) GetBValue(color);
	double h = 0.0;
	double s = 0.0;
	double b = 0.0;

	double mx = max( R, G ); mx = max( mx, B );
	double mn = min( R, G ); mn = min( mn, B );
	double d = mx - mn;

	b = mx / 255.0;
	if( 0.0 != mx )
		s = d / mx;
	if( 0.0 == s )
		h = 0.0;
	else {
		double rc = ( mx - R ) / d;
		double gc = ( mx - G ) / d;
		double bc = ( mx - B ) / d;
		if( R == mx ) {
			h = bc - gc;
		} else {
			if( G == mx ) {
				h = 2.0 + rc - bc;
			} else {
				h = 4.0 + gc - rc;
			}
		}
		h *= 60.0;
		if( h < 0.0 )
			h += 360.0;
	}
	COLORREF	rgb = RGB( (int) ( h * 255.0 / 360.0 ), (int) ( s * 255.0  ), (int) ( b * 255.0 ) );
	return rgb;
}

/////////////////////////////////////////////////////////////////////////////
//

BOOL CHSBtoRGB::Filter( LPRGBQUAD pInClut, LPRGBQUAD pOutClut, int nColors, CFilterProgress* proc ) {
	return TRUE;
}

COLORREF CHSBtoRGB::Filter( COLORREF color, CFilterProgress* proc ) {
	return operator()( color );
}

const COLORREF CHSBtoRGB::operator()( COLORREF color ) {
	double H = (double) GetRValue(color);
	double S = (double) GetGValue(color) / 255.0;
	double B = (double) GetBValue(color) / 255.0;
	double r = 0.0;
	double g = 0.0;
	double b = 0.0;

	H /= 255.0;
	H *= 360.0;
	if( 0.0 == S ) {
		 r = g = b = B;
	} else {
		while( H >= 360.0 )
			H -= 360.0;

		double f, p, q, t;
	
		H /= 60.0;
		f = H - floor (H);
		p = B * ( 1.0 - S );
		q = B * ( 1.0 - ( S * f) );
		t = B * ( 1.0 - ( S * ( 1.0 - f ) ) );
	
		switch ( (int) H ) {
		case 0 :	r = B; g = t; b = p; break;
		case 1 :	r = q; g = B; b = p; break;
		case 2 :	r = p; g = B; b = t; break;
		case 3 :	r = p; g = q; b = B; break;
		case 4 :	r = t; g = p; b = B; break;
		case 5 :	r = B; g = p; b = q; break;
		}
	}
	return RGB( (int) ( r * 255.0 ), (int) ( g * 255.0 ), (int) ( b * 255.0 ) );
}

/////////////////////////////////////////////////////////////////////////////
//

BOOL CExpandColorChannel::SetFilterData( LPFILTERPARAM pData ) {
	LPCOLOREXPANDPARAM	p = (LPCOLOREXPANDPARAM) pData;
	CHECK_FILTERSTRUCT( p );
	if( p->nChannel > 3 || p->nChannel < 0 ) {
		CString	S;
		S.Format( "invalid Channel %d; require 0...3", p->nChannel );
		::LAfxThrowPictException( CPictException::errFilterParam, GetRuntimeClass()->m_lpszClassName, S );
		return FALSE;
	}
	m_nChannel = p->nChannel;
	return TRUE;
}

BOOL CExpandColorChannel::GetFilterData( LPFILTERPARAM pData ) {
	LPCOLOREXPANDPARAM	p = (LPCOLOREXPANDPARAM) pData;
	CHECK_FILTERSTRUCT( p );
	p->nChannel = m_nChannel ;
	return TRUE;
}

BOOL CExpandColorChannel::Filter( LPRGBQUAD pInClut, LPRGBQUAD pOutClut, int nColors, CFilterProgress* proc ) {
	return TRUE;
}

COLORREF CExpandColorChannel::Filter( COLORREF color, CFilterProgress* proc ) {
	return operator()( color );
}

const COLORREF CExpandColorChannel::operator()( COLORREF color ) {
	if( 0 == m_nChannel ) {
		int c = GetRValue( color );
		return RGB( c, c, c );
	} else if( 1 == m_nChannel ) {
		int c = GetGValue( color );
		return RGB( c, c, c );
	} else if( 2 == m_nChannel ) {
		int c = GetBValue( color );
		return RGB( c, c, c );
	} else
		return color;
}

/////////////////////////////////////////////////////////////////////////////
//

BOOL CArrangeColorChannels::SetFilterData( LPFILTERPARAM pData ) {
	LPCOLORARRANGEPARAM	p = (LPCOLORARRANGEPARAM) pData;
	CHECK_FILTERSTRUCT( p );

	ASSERT_NULL_OR_POINTER( p->channelOrder, CWordArray );
	if( NULL == p->channelOrder ) {
		CString	S( "NULL Pointer" );
		::LAfxThrowPictException( CPictException::errFilterParam, GetRuntimeClass()->m_lpszClassName, S );
		return FALSE;
	}
	if( 0 == p->channelOrder->GetSize( ) ) {
		CString	S;
		S.Format( "Channel counter zero" );
		::LAfxThrowPictException( CPictException::errFilterParam, GetRuntimeClass()->m_lpszClassName, S );
		return FALSE;
	}
	for( int i = 0; i < p->channelOrder->GetSize() && i < nChannels; ++i )
		m_channelOrder[i] = p->channelOrder->GetAt(i);
	for( ; i < nChannels; ++i )
		m_channelOrder[i] = i;
	return TRUE;
}

BOOL CArrangeColorChannels::GetFilterData( LPFILTERPARAM pData ) {
	LPCOLORARRANGEPARAM	p = (LPCOLORARRANGEPARAM) pData;
	CHECK_FILTERSTRUCT( p );
	ASSERT_NULL_OR_POINTER( p->channelOrder, CWordArray );
	if( NULL == p->channelOrder )
		return FALSE;
	p->channelOrder->RemoveAll();
	for( int i = 0; i < nChannels; ++i )
		p->channelOrder->SetAt(i, m_channelOrder[i]);
	return TRUE;
}

BOOL CArrangeColorChannels::Filter( LPRGBQUAD pInClut, LPRGBQUAD pOutClut, int nColors, CFilterProgress* proc ) {
	return TRUE;
}

COLORREF CArrangeColorChannels::Filter( COLORREF color, CFilterProgress* proc ) {
	return operator()( color );
}

const COLORREF CArrangeColorChannels::operator()( COLORREF color ) {
	COLOR	c1;
	COLOR	c2;
	register WORD* pB = &m_channelOrder[0];
	c1.d = color;
	c2.a[0] = c1.a[*pB++];
	c2.a[1] = c1.a[*pB++];
	c2.a[2] = c1.a[*pB++];
	c2.a[3] = c1.a[*pB++];
	return c1.d;
}
