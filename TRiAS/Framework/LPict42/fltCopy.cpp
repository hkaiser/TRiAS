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

IMPLEMENT_SERIAL( CPictCopy, CPictFilter, 1 );

#define	new	DEBUG_NEW

CPictCopy::CPictCopy() {
	m_l = m_t = m_r = m_b = 0;
	m_pBitmap = NULL;
}

CPictCopy::~CPictCopy() {
}

BOOL CPictCopy::SetFilterData( LPFILTERPARAM pData ) {
	LPPICTCOPYPARAM	p = (LPPICTCOPYPARAM) pData;
	CHECK_FILTERSTRUCT( p );

	if( !CPictFilter::SetFilterData( pData ) )
		return FALSE;
	m_l = p->m_l;
	m_t = p->m_t;
	m_r = p->m_r;
	m_b = p->m_b;
	return TRUE;
}

BOOL CPictCopy::Filter( CPicture *pI, CPicture *pO, CFilterProgress* proc /*= NULL*/ ) {
	pO->Clone( pI );

	CRect	rcSrc( m_l, m_t, m_r, m_b );
	if( !rcSrc.IsRectEmpty() ) {
		if( rcSrc.Width() <= 0 || rcSrc.Height() <= 0 )
			return FALSE;
		m_rcSrcBand = rcSrc;
		rcSrc.OffsetRect( -rcSrc.left, -rcSrc.top );
		pO->SetPictRect( rcSrc );
	}

	GetPictureInfo( pI, pO );

	WORD	spp = pI->GetBitsPerSample( );

	MergeTags( pO );
	pO->WriteHeader( );

	m_rcDstBand = pO->GetBestCorePictRect();
	m_rcSrcBand.bottom = m_rcSrcBand.top + max( m_rcSrcBand.Height(), m_rcDstBand.Height() );
	m_pBitmap = PICT_FILLORD_SEVENISZERO == pI->GetFillOrder( ) ? &BitRevTable[0] : &NoBitRevTable[0];

	BOOL ret = FALSE;

	while( m_rcDstBand.top < m_rcDstBand.bottom ) {
		if( proc ) {
			CString	S;
			S.Format( _T("Read: %ld,%ld"), m_rcSrcBand.top, m_rcSrcBand.Height() );
			proc->ReportingStatus( m_rcSrcBand.top / m_rcSrcBand.Height(), S );
		}
		if( !pI->Read( m_rcSrcBand ) ) {
			CString	S;
			S.Format( "Band: [%ld,%ld,%ld,%ld]", m_rcDstBand.left, m_rcDstBand.top, m_rcDstBand.right, m_rcDstBand.bottom );
			::LAfxThrowPictException( CPictException::errFilterSrcRead, GetRuntimeClass()->m_lpszClassName, S );
			return FALSE;
		}
		pO->SetCoreRect( m_rcDstBand );

		m_rcSrcCore = pI->GetCoreImageRect();
		m_rcDstCore = pO->GetCoreImageRect();
		m_pSrcPictData = pI->GetDataPointer();
		m_pDstPictData = pO->GetDataPointer();
		m_BytesPerSrcLine = m_rcSrcCore.Width();
		m_BytesPerDstLine = m_rcDstCore.Width();

		switch( spp ) {
		case 1 : ret = Copy1(); break;
		}

		if( FALSE == ret ) {
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
	pO->WriteTrailer( );
	return TRUE;
}

BOOL CPictCopy::Copy1( ) {
	HPBYTE	pDstLine, pDstPixel;
	HPBYTE	pSrcLine, pSrcPixel;
	int		off = ( ( m_rcSrcBand.left - m_rcSrcCore.left * 8 ) + 7 ) / 8;

	pSrcLine = m_pSrcPictData + off;
	pDstLine = m_pDstPictData;
	
	long	Line, Col;
	long	srcLines = m_rcSrcBand.Height();
	long	srcCols = m_rcSrcBand.Width();
	int		srcBit, dstBit;
	BYTE	srcData, dstData;

	for( Line = 0; Line < srcLines; Line++ ) {
		pSrcPixel = pSrcLine;
		pDstPixel = pDstLine;
		srcBit = m_l % 8;
		dstBit = 0;
		srcData = m_pBitmap[*pSrcPixel] >> srcBit;
		dstData = 0;
		for( Col = 0; Col < srcCols; Col++ ) {
			dstData |= ( srcData & 0x01 );

			if( 8 == ++srcBit ) {
#ifdef	_DEBUG
				ASSERT( TRUE == m_pI->CheckDataPointer( (HPBYTE) pSrcPixel ) );
#endif
				srcData = m_pBitmap[*pSrcPixel++];
				srcBit = 0;
			}
			else
				srcData >>= 1;

			if( 8 == ++dstBit ) {
#ifdef	_DEBUG
				ASSERT( TRUE == m_pO->CheckDataPointer( pDstPixel ) );
#endif
				*pDstPixel++ = dstData;
				dstBit = 0;
				dstData = 0;
			}
			else
				dstData <<= 1;
		}
#ifdef	_DEBUG
		ASSERT( TRUE == m_pO->CheckDataPointer( pDstPixel ) );
#endif
		*pDstPixel = dstData;

		pSrcLine += m_BytesPerSrcLine;
		pDstLine += m_BytesPerDstLine;
	}
	return TRUE;
}

void CPictCopy::Serialize( CArchive& ar ) {
}
