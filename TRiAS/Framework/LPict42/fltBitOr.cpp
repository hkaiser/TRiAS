#include "stdafx.h"
#include "LPictImpl.h"

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL( CPictBitOr, CPictFilter, 1 );

#define	new	DEBUG_NEW

CPictBitOr::CPictBitOr() {
	m_nLevelToOr = 0;
	m_pBitmap = NULL;
}

CPictBitOr::~CPictBitOr() {
}

BOOL CPictBitOr::SetFilterData( LPFILTERPARAM pData ) {
	LPBITORPARAM	p = (LPBITORPARAM) pData;
	CHECK_FILTERSTRUCT( p );

	if( !CPictFilter::SetFilterData( pData ) )
		return FALSE;
	if( p->m_nLevelToOr > 255 ) {
		CString	S;
		S.Format( "%d; require 0...255", p->m_nLevelToOr );
		::LAfxThrowPictException( CPictException::errFilterParam, GetRuntimeClass()->m_lpszClassName, S );
		return FALSE;
	}
	m_nLevelToOr = p->m_nLevelToOr;
	m_l = p->m_l;
	m_t = p->m_t;
	m_r = p->m_r;
	m_b = p->m_b;
	return TRUE;
}

BOOL CPictBitOr::Filter( CPicture *pI, CPicture *pO, CFilterProgress* proc /*= NULL*/ ) {
	CRect	rcSrc( m_l, m_t, m_r, m_b );
	if( !rcSrc.IsRectEmpty() ) {
		if( rcSrc.Width() > pO->GetPictRect().Width() 
			|| rcSrc.Height() > pO->GetPictRect().Height() )
		{
			CString	S;
			S.Format( "Invalid Source: [%ld,%ld,%ld,%ld]", rcSrc.left, rcSrc.top, rcSrc.right, rcSrc.bottom );
			::LAfxThrowPictException( CPictException::errFilterParam, GetRuntimeClass()->m_lpszClassName, S );
			return FALSE;
		}
		m_rcSrcBand = rcSrc;
		rcSrc.OffsetRect( -rcSrc.left, -rcSrc.top );
	}

	GetPictureInfo( pI, pO );
	MergeTags( pO );

	m_rcDstBand = pO->GetBestCorePictRect();
	m_rcSrcBand.bottom = m_rcSrcBand.top + m_rcDstBand.Height();

	m_pBitmap = PICT_FILLORD_SEVENISZERO == pI->GetFillOrder( ) ? &BitRevTable[0] : &NoBitRevTable[0];

	while( m_rcDstBand.top < m_rcDstBand.bottom ) {
		if( !pO->Read( m_rcDstBand ) ) {
			CString	S;
			S.Format( "Band: [%ld,%ld,%ld,%ld]", m_rcDstBand.left, m_rcDstBand.top, m_rcDstBand.right, m_rcDstBand.bottom );
			::LAfxThrowPictException( CPictException::errFilterDstRead, GetRuntimeClass()->m_lpszClassName, S );
			return FALSE;
		}
		if( !pI->Read( m_rcSrcBand ) ) {
			CString	S;
			S.Format( "Band: [%ld,%ld,%ld,%ld]", m_rcDstBand.left, m_rcDstBand.top, m_rcDstBand.right, m_rcDstBand.bottom );
			::LAfxThrowPictException( CPictException::errFilterSrcRead, GetRuntimeClass()->m_lpszClassName, S );
			return FALSE;
		}
		m_rcSrcCore = pI->GetCoreImageRect();
		m_rcDstCore = pO->GetCoreImageRect();
		m_pSrcPictData = pI->GetDataPointer();
		m_pDstPictData = pO->GetDataPointer();
		m_BytesPerSrcLine = m_rcSrcCore.Width();
		m_BytesPerDstLine = m_rcDstCore.Width();
		if( !DoFilter() ) {
			CString	S;
			S.Format( "Band: [%ld,%ld,%ld,%ld]", m_rcDstBand.left, m_rcDstBand.top, m_rcDstBand.right, m_rcDstBand.bottom );
			::LAfxThrowPictException( CPictException::errFilterProcess, GetRuntimeClass()->m_lpszClassName, S );
			return FALSE;
		}
		if( FALSE == pO->Write( m_rcDstBand ) ) {
			CString	S;
			S.Format( "Band: [%ld,%ld,%ld,%ld]", m_rcDstBand.left, m_rcDstBand.top, m_rcDstBand.right, m_rcDstBand.bottom );
			::LAfxThrowPictException( CPictException::errFilterWrite, GetRuntimeClass()->m_lpszClassName, S );
			return FALSE;
		}
		m_rcDstBand.OffsetRect( 0, m_rcDstBand.Height() );
		m_rcDstBand.bottom = min( m_rcDstBand.bottom, m_rcDstPict.bottom );
		m_rcSrcBand.OffsetRect( 0, m_rcSrcBand.Height() );
		m_rcSrcBand.bottom = min( m_rcSrcBand.bottom, m_rcSrcPict.bottom );
	}
	return TRUE;
}

BOOL CPictBitOr::DoFilter( ) {
	HPBYTE	pDstLine, pDstPixel;
	HPBYTE	pSrcLine, pSrcPixel;
	int		off = ( ( m_rcSrcBand.left - m_rcSrcCore.left * 8 ) + 7 ) / 8;

	pSrcLine = m_pSrcPictData + off;
	pDstLine = m_pDstPictData;
	
	long	Line, Col, bit;
	long	srcLines = m_rcDstBand.Height();
	long	srcCols = m_rcDstBand.Width();
	long	srcData;

	for( Line = 0; Line < srcLines; Line++ ) {
		pSrcPixel = pSrcLine;
		pDstPixel = pDstLine;
		bit = 0;
		for( Col = 0; Col < srcCols; Col++ ) {
			if( 0 == bit ) {
#ifdef	_DEBUG
				ASSERT( TRUE == m_pI->CheckDataPointer( pSrcPixel ) );
#endif
				srcData = m_pBitmap[*pSrcPixel++];
				bit = 8;
			}
#ifdef	_DEBUG
			ASSERT( TRUE == m_pO->CheckDataPointer( pDstPixel ) );
#endif
//			*pDstPixel++ = *pDstPixel + ( ( srcData & 0x01 ) << m_nLevelToOr );
			if( srcData & 0x01 )
				*pDstPixel = m_nLevelToOr;
			pDstPixel++;
			srcData >>= 1;
			bit--;
		}
		pSrcLine += m_BytesPerSrcLine;
		pDstLine += m_BytesPerDstLine;
	}
	return TRUE;
}

void CPictBitOr::Serialize( CArchive& ar ) {
}
