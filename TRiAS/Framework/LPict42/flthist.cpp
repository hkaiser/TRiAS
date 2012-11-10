#include "stdafx.h"
#include "LPictImpl.h"

#ifdef	PICTFLT_HIST_RELEASED

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL( CPictHistogramm, CPictFilter, 1 );

#define	new	DEBUG_NEW

//////////////////////////////////////////////////////////////////////////

CPictHistogramm::CPictHistogramm( ) {
	m_pHistogramm = new CMemBlock( 32768 * sizeof( DWORD ) );
	Init();
}

CPictHistogramm::~CPictHistogramm( ) {
	if( NULL != m_pHistogramm )
		delete m_pHistogramm;
}

void CPictHistogramm::Init( ) {
	ASSERT_VALID( m_pHistogramm );
	memset( (HPVOID) ((HPBYTE) *m_pHistogramm), 0x00, m_pHistogramm->Size() );
	m_nPoints = 0;
}

BOOL CPictHistogramm::GetFilterData( LPFILTERPARAM pData ) {
	LPPICTHISTPARAM	p = (LPPICTHISTPARAM) pData;
	CHECK_FILTERSTRUCT( p );

	p->pHist = (HPDWORD) ((HPBYTE) *m_pHistogramm);
	p->nPixels = m_nPoints;
	p->nSamples = 32768;
	return TRUE;
}

BOOL CPictHistogramm::Filter( CPicture *pI, CFilterProgress* proc ) {
	DWORD	startLine = 0;

	if( !pI->SetCoreRect( pI->GetBestCorePictRect() ) ) {
		::LAfxThrowPictException( CPictException::errMemory, GetRuntimeClass()->m_lpszClassName );
		return FALSE;
	}
	GetPictureInfo( pI );
//	pI->SetCoreRect( CRect( 0, 0, 0, 0 ) );

	m_rcSrcBand = pI->GetCorePictRect();
//	m_rcSrcBand.bottom = m_rcSrcBand.top + pI->GetMaxInCoreLines( m_rcSrcBand.Width() );
//	m_rcSrcBand.bottom = min( m_rcSrcBand.bottom, m_rcSrcPict.Height() );

	while( m_rcSrcBand.top < m_rcSrcPict.bottom ) {
		if( !pI->Read( m_rcSrcBand ) ) {
			CString	S;
			S.Format( "Band: [%ld,%ld,%ld,%ld]", m_rcDstBand.left, m_rcDstBand.top, m_rcDstBand.right, m_rcDstBand.bottom );
			::LAfxThrowPictException( CPictException::errFilterSrcRead, GetRuntimeClass()->m_lpszClassName, S );
			return FALSE;
		}
		m_rcSrcCore = pI->GetCoreImageRect();
		m_pSrcPictData = pI->GetDataPointer();
		m_BytesPerSrcLine = m_rcSrcCore.Width();

		Accumulate( proc );

		m_rcSrcBand.OffsetRect( 0, m_rcSrcBand.Height() );
		if( m_rcSrcBand.bottom > m_rcSrcPict.bottom )
			m_rcSrcBand.bottom = m_rcSrcPict.bottom;
	}
	return TRUE;
}

void CPictHistogramm::Accumulate( CFilterProgress* proc ) {
	register HPBYTE	pSrcPixel;
	HPBYTE	pLine;
	long	dX, dY;
	register COLOR		C;
	HPDWORD		pHistData = (HPDWORD) ((HPBYTE) *m_pHistogramm);

	long	nLines = m_rcSrcBand.Height();
	long	nCols = m_rcSrcBand.Width();
	long	imageWidth = m_rcSrcCore.Width();

	pLine = m_pSrcPictData;
	for( dY = 0L; dY < nLines; dY++ ) {
		pSrcPixel = pLine;
		for( dX = 0L; dX < nCols; dX++ ) {
			C.d = *((DWORD*)pSrcPixel);
			C.b.b4 = 0;
			C.b.b3 >>= 3;
			C.m.w >>= 3;
			C.d >>= 3;
			pHistData[C.w.w1]++;

			pSrcPixel += 3;
			m_nPoints++;
		}
		pLine += imageWidth;
	}
}

void CPictHistogramm::Serialize( CArchive& ar ) {
	HPBYTE	pData = (HPBYTE) *m_pHistogramm;
	DWORD	size = m_pHistogramm->Size( );
	long	BytesToTransfer = (long) ( 32768 * sizeof( DWORD ) ) ;
	long	offset = 0;
	long	blkSize =  16384;

	CPictFilter::Serialize( ar );

	if( ar.IsStoring( ) ) {
		DWORD	w = 32768;
		ar << w;
		ar << m_nPoints;
		while( BytesToTransfer > 0 ) {
			if( BytesToTransfer < blkSize )
				blkSize = BytesToTransfer;
			ar.Write( (void FAR*) &pData[ offset ], (UINT) blkSize );
			offset += blkSize;
			BytesToTransfer -= blkSize;
		}
	} else {
		ar >> size;
		ar >> m_nPoints;
		while( BytesToTransfer > 0 ) {
			if( BytesToTransfer < blkSize )
				blkSize = BytesToTransfer;
			ar.Read( (void FAR*) &pData[ offset ], (UINT) blkSize );
			offset += blkSize;
			BytesToTransfer -= blkSize;
		}
	}
}

#endif	// PICTFLT_HIST_RELEASED
