#include "stdafx.h"
#include "LPictImpl.h"

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE( CCodecRLE8, CPictCodec );

#define	new	DEBUG_NEW

BOOL CCodecRLE8::Encode( HPBYTE pSrcData, HPBYTE& pDstData, long nSrcBytes ) {
	ASSERT( NULL != m_pPicture );
	return FALSE;
}

long CCodecRLE8::DecodeLine( long nBytes ) {
	long	nb = nBytes;
	register signed char n;
	if( TRUE == m_bHaveSymbol )
		goto DecodeSymbol;
Decode:
	if( 0 != m_nCopy ) {
		while( 0 != m_nCopy && nBytes ) {
			m_pDst[m_dstPos++] = m_pSrc[m_srcPos++];
			m_nCopy--;
			nBytes--;
			if( 0 == nBytes )
				return nb - nBytes;
		}
		if( 0 != m_nCopyAdd ) {
			m_nCopyAdd = 0;
			m_srcPos++;
			nBytes--;
			if( 0 == nBytes )
				return nb - nBytes;
		}
	}
	if( 0 != m_nExpand ) {
		n = m_pSrc[m_srcPos++];
		nBytes--;
		while( 0 != m_nExpand ) {
			m_pDst[m_dstPos++] = n;
			m_nExpand--;
		}
		if( 0 == nBytes )
			return nb - nBytes;
	}
	if( m_dstPos > m_lineLength ) {
		return nb - nBytes;
	}
	if( 0 == nBytes )
		return nb - nBytes;

	n = m_pSrc[m_srcPos++];
	nBytes--;
	if( 0 != n )
		m_nExpand = (short) (unsigned char) n;
	else {
		if( 0 == nBytes ) {
			m_nSymbol = n;
			m_bHaveSymbol = TRUE;
			return nb - nBytes;
		}
DecodeSymbol:
		m_bHaveSymbol = FALSE;
		n = m_pSrc[m_srcPos++];
		nBytes--;
		if( 0 == n ) {
			return nb - nBytes;			// EndOfLine
		} else if( 1 == n ) {
			return nb - nBytes;			// EndOfBitmap
		} else if( 2 == n ) {
			m_dx = m_pSrc[m_srcPos++];
			nBytes--;
			m_dy = m_pSrc[m_srcPos++];
			nBytes--;
		} else {
			m_nCopy = (short) (unsigned char) n;
			m_nCopyAdd = n & 0x01;
		}
	}
	goto Decode;
}
