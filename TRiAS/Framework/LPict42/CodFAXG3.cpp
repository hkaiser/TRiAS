#include "stdafx.h"
#include "LPictImpl.h"

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE( CCodecFaxG3, CCodecFax );

#define	new	DEBUG_NEW

BOOL CCodecFaxG3::Setup( ) {
	if( !CCodecFax::Setup() )
		return FALSE;
	m_pCodecfunc = (PICT_G3OPTIONS) m_dwOptions & PICT_G3_2DENCODING  ? Decode2D : Decode1D;

#ifdef NDEBUG
	if( (PICT_G3OPTIONS) m_dwOptions & PICT_G3_2DENCODING )
		return FALSE;
#endif
	return NULL != m_pCodecfunc;
}

long CCodecFaxG3::Decode1D( long occ ) {
	long	nBytes = -1;
	BYTE	*pByte = m_l.cp;

	m_l.ep = &m_pSrc[ m_srcEnd ];

	if( occ > 0 ) {
		m_l.a0 = 0;
		m_l.RunLength = 0;
		m_l.pa = m_l.thisrun = m_l.curruns;
		if( !_SYNC_EOL() )
			_CLEANUP_RUNS();
		else {
			if( _EXPAND1D() )
				nBytes = m_l.cp - pByte;
		}
		CopyFaxRuns( m_pDst, m_l.curruns, m_l.pa, m_l.lastx );
	}
	return nBytes;
}

#define	SWAP(t,a,b)	{ t x; x = (a); (a) = (b); (b) = x; }

long CCodecFaxG3::Decode2D( long occ ) {
	int is1D;						// current line is 1d/2d-encoded
	long	nBytes = -1;
	BYTE	*pByte = m_l.cp;

	m_l.ep = &m_pSrc[ m_srcEnd ];

	if( occ > 0) {
		m_l.a0 = 0;
		m_l.RunLength = 0;
		m_l.pa = m_l.thisrun = m_l.curruns;
//		TRACE("BitAcc=%08X, BitsAvail = %d EOLcnt = %d\n", m_l.BitAcc, m_l.BitsAvail, m_l.EOLcnt);
		if( !_SYNC_EOL() )
			goto EOF2D;
		if( !_NeedBits8(1) )
			goto EOF2D;
		is1D = _GetBits(1);			// 1D/2D-encoding tag bit
		_ClrBits(1);
		m_l.pb = m_l.refruns;
		m_l.b1 = *m_l.pb++;
		if (is1D)
			if( !_EXPAND1D() )
				goto EOF2Da;
		else
			if( !_EXPAND2D() )
				goto EOF2Da;
		CopyFaxRuns( m_pDst, m_l.curruns, m_l.pa, m_l.lastx );
		_SETVAL(0);					// imaginary change for reference
		SWAP(uint16*, m_l.curruns, m_l.refruns);
		nBytes = m_l.cp - pByte;
		goto done;
	}

EOF2D:				/* premature EOF */
	_CLEANUP_RUNS();
EOF2Da:				/* premature EOF */
	CopyFaxRuns( m_pDst, m_l.curruns, m_l.pa, m_l.lastx );
done:
	return nBytes;
}

long CCodecFaxG3::DecodeLine( long occ ) {
	return (PICT_G3OPTIONS) m_dwOptions & PICT_G3_2DENCODING  ? Decode2D(occ) : Decode1D(occ);
}

BOOL CCodecFaxG3::Encode( HPBYTE pSrcData, HPBYTE& pDstData, long nSrcBytes ) {
	return FALSE;
}

