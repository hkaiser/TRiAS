#include "stdafx.h"
#include "LPictImpl.h"

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE( CCodecPackBits, CPictCodec );

#define	new	DEBUG_NEW

BOOL CCodecPackBits::Encode( HPBYTE pSrcData, HPBYTE& pDstData, long nSrcBytes ) {
	ASSERT( NULL != m_pPicture );
	return FALSE;
}

long CCodecPackBits::DecodeLine( long nBytes ) {
	long	nb = nBytes;
	BYTE	b;
Decode:
	while( 0 != m_nCopy && nBytes ) {
		m_pDst[m_dstPos++] = m_pSrc[m_srcPos++];
		m_nCopy--;
		nBytes--;
	}
	if( 0 != m_nExpand ) {
		b = m_pSrc[m_srcPos++];
		nBytes--;
	}
	while( 0 != m_nExpand ) {
		m_pDst[m_dstPos++] = b;
		m_nExpand--;
	}
	if( m_dstPos >= m_lineLength )
		return nb - nBytes;
	if( 0 != nBytes ) {
NextByte:
		register signed char n = (char) m_pSrc[m_srcPos++];
		nBytes--;
		if( n >= 128 ) {
			n = (char) ( (short) n - 256 );
		}

		if( n < 0 ) {
			if( -128 == n )
				goto NextByte;
			m_nExpand = -n + 1;
		} else {
			m_nCopy = n + 1;
		}
		if( 0 == nBytes )
			return nb - nBytes;
		goto Decode;
	}
	return nb;
}
