#include "stdafx.h"
#include "LPictImpl.h"

#ifdef	PICTFLT_FITCLUT_RELEASED

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL( CFitClut, CPictFilter, 1 );

#define	new	DEBUG_NEW

//////////////////////////////////////////////////////////////////////////

CFitClut::CFitClut( ) {
	m_pInClut = (LPRGBQUAD) new char[ 256 * sizeof( RGBQUAD ) ];
	m_pOutClut = (LPRGBQUAD) new char[ 256 * sizeof( RGBQUAD ) ];
	m_hOutPal = NULL;
	Init( );
}

CFitClut::~CFitClut( ) {
	ASSERT( NULL != m_pInClut );
	delete m_pInClut;
	ASSERT( NULL != m_pOutClut );
	delete m_pOutClut;

	if( NULL != m_hOutPal )
		::DeleteObject( m_hOutPal );
}

void	CFitClut::Init( ) {
	memset( (void FAR*) m_pInClut, 0x00, 256 * sizeof( RGBQUAD ) );
	memset( (void FAR*) m_pOutClut, 0x00, 256 * sizeof( RGBQUAD ) );
}

BOOL CFitClut::SetFilterData( LPFILTERPARAM pData ) {
	LPFITCLUTPARAM	p = (LPFITCLUTPARAM) pData;
	CHECK_FILTERSTRUCT( p );

	int	i;
	HLOCAL	localMemBlock;
	
	memcpy( (void FAR*) m_pOutClut, p->pDstClut, 256 * sizeof( RGBQUAD ) );
	localMemBlock = ::LocalAlloc( LPTR, sizeof( LOGPALETTE ) + 256 * sizeof( PALETTEENTRY ) );
	LPLOGPALETTE	pOutPal = (LPLOGPALETTE) ::LocalLock( localMemBlock );

	pOutPal->palNumEntries = 256;
	pOutPal->palVersion = 0x300;
	
	for( i = 0; i < 256; i++ ) {
		pOutPal->palPalEntry[i].peRed   = m_pOutClut[i].rgbRed;
		pOutPal->palPalEntry[i].peGreen = m_pOutClut[i].rgbGreen;
		pOutPal->palPalEntry[i].peBlue  = m_pOutClut[i].rgbBlue;
		pOutPal->palPalEntry[i].peFlags = PC_RESERVED;
	}
	if( NULL != m_hOutPal )
		::DeleteObject( m_hOutPal );
	m_hOutPal = ::CreatePalette( pOutPal );
	::LocalUnlock( localMemBlock );
	::LocalFree( localMemBlock );
	return TRUE;
}

BOOL	CFitClut::Filter( CPicture *pI, CPicture *pO, ostream* pstr ) {
	DWORD	startSrcLine = 0;
	DWORD	startDstLine = 0;
	BYTE	r, g, b;
	COLORREF	rgb;
	int	i;

	pI->GetClut( m_pInClut, 256 );

	memset( (void FAR*) m_newIdxs, 0x00, 256 * sizeof( UINT ) );

	for( i = 0; i < 256; i++ ) {
		r = m_pInClut[i].rgbRed;
		g = m_pInClut[i].rgbGreen;
		b = m_pInClut[i].rgbBlue;
		rgb = RGB( r, g, b );
		m_newIdxs[i] = ::GetNearestPaletteIndex( m_hOutPal, rgb );
	}
	
	pO->Clone( pI );
	pO->SetClut( m_pOutClut, 256 );
	pO->WriteHeader( );

	GetPictureInfo( pI, pO );

	while( m_linesToProcess > 0 ) {
		if( !pI->Read( startSrcLine, m_LinesInSrcCore ) ) {
			CString	S;
			S.Format( "Band: [%ld,%ld,%ld,%ld]", m_rcDstBand.left, m_rcDstBand.top, m_rcDstBand.right, m_rcDstBand.bottom );
			::LAfxThrowPictException( CPictException::errFilterRead, GetRuntimeClass()->m_lpszClassName, S );
			return FALSE;
		}
		if( !DoFilter( ) ) {
			CString	S;
			S.Format( "Band: [%ld,%ld,%ld,%ld]", m_rcDstBand.left, m_rcDstBand.top, m_rcDstBand.right, m_rcDstBand.bottom );
			::LAfxThrowPictException( CPictException::errFilterProcess, GetRuntimeClass()->m_lpszClassName, S );
			return FALSE;
		}
		if( FALSE == pO->Write( startSrcLine, m_LinesInSrcCore ) ) {
			CString	S;
			S.Format( "Band: [%ld,%ld,%ld,%ld]", m_rcDstBand.left, m_rcDstBand.top, m_rcDstBand.right, m_rcDstBand.bottom );
			::LAfxThrowPictException( CPictException::errFilterWrite, GetRuntimeClass()->m_lpszClassName, S );
			return FALSE;
		}
		startSrcLine += m_LinesInSrcCore;
		m_linesToProcess -= (long) m_LinesInSrcCore;			// ansonsten klappt's nicht mit negativen Werten
		if( m_linesToProcess < (long) m_LinesInSrcCore )
			m_LinesInSrcCore = (DWORD) m_linesToProcess;
	}
	return TRUE;
}

BOOL	CFitClut::DoFilter( ) {
	HPBYTE	pSrcLine = m_pSrcPictData;
	HPBYTE	pDstLine = m_pDstPictData;
	HPBYTE	pSrcPixel, pDstPixel;
	DWORD	Row, Col;

	for( Row = 0; Row < m_LinesInSrcCore; Row++ ) {
		pSrcPixel = pSrcLine;
		pDstPixel = pDstLine;
		for( Col = 0; Col < m_SrcPictWidth; Col++ ) {
#ifdef	_DEBUG
			if( !m_pI->CheckDataPointer( pSrcPixel ) ) {
				_asm { int 3 }
				DWORD diff = pSrcPixel - m_pSrcPictData;
			}
			if( !m_pO->CheckDataPointer( pDstPixel ) )  {
				_asm { int 3 }
				DWORD diff = pDstPixel - m_pDstPictData;
			}
#endif
			*pDstPixel = m_newIdxs[ *pSrcPixel ];
			pSrcPixel++;
			pDstPixel++;
		}
		pSrcLine += m_BytesPerSrcLine;
		pDstLine += m_BytesPerDstLine;
	}
	return TRUE;
}

void	CFitClut::Serialize( CArchive& ar ) {
	CPictFilter::Serialize( ar );
}

#endif	// PICTFLT_FITCLUT_RELEASED
