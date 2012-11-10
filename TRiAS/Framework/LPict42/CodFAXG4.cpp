#include "stdafx.h"
#include "LPictImpl.h"

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE( CCodecFaxG4, CCodecFax );

#define	new	DEBUG_NEW

#define	SWAP(t,a,b)	{ t x; x = (a); (a) = (b); (b) = x; }

long CCodecFaxG4::DecodeLine( long occ ) {
	int	nBytes = 0;
	BYTE	*pByte;

	m_l.ep = &m_pSrc[ m_srcEnd ];

	if( (long) occ > 0 ) {
		m_l.a0 = 0;
		m_l.RunLength = 0;
		m_l.pa = m_l.thisrun = m_l.curruns;
		m_l.pb = m_l.refruns;
		m_l.b1 = *m_l.pb++;
		pByte = m_l.cp;
		if( _EXPAND2D() ) {
			CopyFaxRuns( m_pDst, m_l.curruns, m_l.pa, m_l.lastx );				// (*sp->fill)(buf, thisrun, pa, lastx);
			_SETVAL(0);					/* imaginary change for reference */
			SWAP(uint16*, m_l.curruns, m_l.refruns);
			nBytes = m_l.cp - pByte;
			return nBytes;
		}
	}
	CopyFaxRuns( m_pDst, m_l.thisrun, m_l.pa, m_l.lastx );				// (*sp->fill)(buf, thisrun, pa, lastx);
	return (-1);
}

BOOL CCodecFaxG4::Encode( HPBYTE pSrcData, HPBYTE& pDstData, long nSrcBytes ) {
	return FALSE;
}

