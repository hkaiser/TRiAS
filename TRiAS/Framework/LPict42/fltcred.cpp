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

IMPLEMENT_SERIAL( CMedianCut, CPictFilter, 1 );

#define	new	DEBUG_NEW

#define	RGB15( r, g, b )	(COLORREF) ( ((r) << 10) | ((g) << 5) | (b) )

//////////////////////////////////////////////////////////////////////////

CMedianCut::CMedianCut( ) {
	m_pClut = (LPRGBQUAD) new char[ 256 * sizeof( RGBQUAD ) ];
	m_pIdxTab = (HPBYTE) new char[ 32768 * sizeof( BYTE ) ];
	Init( );
}

CMedianCut::~CMedianCut( ) {
	ASSERT( NULL != m_pClut );
	ASSERT( NULL != m_pIdxTab );
	delete m_pIdxTab;
	delete m_pClut;
}

void CMedianCut::Init( ) {
	memset( (void FAR*) m_pClut, 0x00, 256 * sizeof( RGBQUAD ) );
	memset( (void FAR*) m_pIdxTab, 0x00, 32768 * sizeof( BYTE ) );
	m_nIdxs = 32768;
	m_nColors = 256;
}

BOOL	CMedianCut::Filter( CPictFilter *pInFlt, CFilterProgress* proc ) {
	ASSERT_KINDOF( CPictHistogramm, pInFlt );
	PICTHISTPARAM	p;
	INIT_FILTERSTRUCT( &p, CPictHistogramm );
	VERIFY( pInFlt->GetFilterData( &p.p ) );

	LPRGBQUAD		pClut = m_pClut;
	m_clutIndex = 0;

	MedianCut( p.pHist, pClut, p.nPixels );
	ReduceColors( p.pHist, pClut );
/*
	ofstream f( "pstyler.pal", ios::out );

	f << "CWPAL" << endl << "100" << endl << "256" << endl;

	for( int i = 0; i < 256; i++ )
		f << (int) m_pClut[i].rgbRed << ' ' << (int) m_pClut[i].rgbGreen << ' ' << (int) m_pClut[i].rgbBlue << endl;
*/

	return TRUE;
}

void CMedianCut::MedianCut( HPDWORD pHist, LPRGBQUAD pClut, LONG lPixels,
						   UINT nColors, 
						   UINT r1, UINT r2, 
						   UINT g1, UINT g2, 
						   UINT b1, UINT b2, WORD depth )
{
	int  nRLength;	// Länge der Rot-Kante
	int  nGLength;	// Länge der Grün-Kante
	int  nBLength;	// Länge der Blau-Kante
	UINT r;				// Rot-Zähler
	UINT g;				// Grün-Zähler
	UINT b;				// Blau-Zähler
	COLORREF rgb;
	LONG sumR;			// Rot-Summe für Mittelwertbildung
	LONG sumG;		// Grün-Summe für Mittelwertbildung
	LONG sumB;			// Blau-Summe für Mittelwertbildung
	LONG lPix;			// Anzahl der Pixel eines Farbwerts
	LONG lPixelsOld;	// Anzahl der Pixel in einem Teilquader
	LONG lPixelsNew;	// Anzahl der Pixel in einem Teilquader
	
	++depth;

#ifdef	_DEBUG
//	TRACE( "  %d %d %ld %d %d %d %d %d %d\n", depth, nColors, lPixels, r1, r2, g1, g2, b1, b2 );
#endif

	if (lPixels == 0l) {
		return;
	}

	nRLength   = r2 - r1;
	nGLength = g2 - g1;
	nBLength  = b2 - b1;

	// Kantenlänge = 1?
	if (nRLength == 0 && nGLength == 0 && nBLength == 0) {
		// Es liegt ein Würfel mit der Kantenlänge 1 vor
		// Farbwert in Farbtabelle eintragen
		if (pHist[RGB15(r1, g1, b1)]) {
			pClut[m_clutIndex].rgbRed   = (r1) << 3;
			pClut[m_clutIndex].rgbGreen = (g1) << 3;
			pClut[m_clutIndex].rgbBlue  = (b1) << 3;
			m_clutIndex++;
#ifdef _DEBUG
			TRACE( "L=1: [%d] (%d,%d,%d)\n", m_clutIndex - 1, r1, g1, b1 );
			if( m_clutIndex > 255 ) _asm { int 3 }
#endif
		} else {
		}
		return;
	}

	if( nColors == 1 || lPixels == 1 ) {
		sumR   = 0l;
		sumG = 0l;
		sumB  = 0l;
		for (r = r1; r <= r2; r++)
			for (g = g1; g <= g2; g++)
				for (b = b1; b <= b2; b++) {
					rgb = RGB15( r, g, b );
					lPix = (LONG) pHist[ rgb ];
					if (lPix) {
						sumR += (LONG) r * (LONG) lPix;
						sumG += (LONG) g * (LONG) lPix;
						sumB += (LONG) b * (LONG) lPix;
					}
				}
		r = (UINT) (sumR / lPixels);
		g = (UINT) (sumG / lPixels);
		b = (UINT) (sumB / lPixels);

		pClut[m_clutIndex].rgbRed   = (r) << 3;
		pClut[m_clutIndex].rgbGreen = (g) << 3;
		pClut[m_clutIndex].rgbBlue  = (b) << 3;
		m_clutIndex++;
#ifdef _DEBUG
		TRACE( "C=1: [%d] (%d,%d,%d)\n", m_clutIndex - 1, r, g, b );
		ASSERT( m_clutIndex < 256 );
#endif
		return;
	}

	// Teile den Quader bei seiner längsten Kante

	if (nBLength > nGLength && nBLength > nRLength) {	// Teile die Blau-Kante
		lPixelsNew = 0l;
		b      = b1 - 1;
		while (lPixelsNew < lPixels / 2) {
			b++;
			lPixelsOld = lPixelsNew;
			for (r = r1; r <= r2; r++) {
				for (g = g1; g <= g2; g++) {
					rgb = RGB15( r, g, b );
					lPixelsNew += (LONG) pHist[ rgb ];
				}
			}
		}
		TRACE( " B %d %d %d\n", b1, b, b2 );
		if (b < b2) {
			MedianCut(pHist, pClut, lPixelsNew,           nColors / 2, r1, r2, g1, g2, b1   , b , depth );
			MedianCut(pHist, pClut, lPixels - lPixelsNew, nColors / 2, r1, r2, g1, g2, b + 1, b2, depth );
		} else {
			MedianCut(pHist, pClut, lPixelsOld,           nColors / 2, r1, r2, g1, g2, b1, b - 1, depth );
			MedianCut(pHist, pClut, lPixels - lPixelsOld, nColors / 2, r1, r2, g1, g2, b , b2   , depth );
		}
		return;
	}

	if (nGLength > nRLength) {			// teile die Grün-Kante
		lPixelsNew = 0l;
		g     = g1 - 1;
		while (lPixelsNew < lPixels / 2)
		{
			g++;
			lPixelsOld = lPixelsNew;
			for (r = r1; r <= r2; r++)
			{
				for (b = b1; b <= b2; b++)
				{
					rgb = RGB15( r, g, b );
					lPixelsNew += (LONG) pHist[ rgb ];
				}
			}
		}
		TRACE( " G %d %d %d\n", g1, g, g2 );
		if (g < g2) {
			MedianCut(pHist, pClut, lPixelsNew,           nColors / 2,  r1, r2, g1  , g , b1, b2, depth );
			MedianCut(pHist, pClut, lPixels - lPixelsNew, nColors / 2, r1, r2, g + 1, g2, b1, b2, depth );
		} else {
			MedianCut(pHist, pClut, lPixelsOld,           nColors / 2, r1, r2, g1, g - 1, b1, b2, depth );
			MedianCut(pHist, pClut, lPixels - lPixelsOld, nColors / 2, r1, r2, g , g2   , b1, b2, depth );
		}
		return;
	} else {									// teile die Rot-Kante
		lPixelsNew = 0l;
		r       = r1 - 1;
		while (lPixelsNew < lPixels / 2) {
			r++;
			lPixelsOld = lPixelsNew;
			for (g = g1; g <= g2; g++) {
				for (b = b1; b <= b2; b++) {
					rgb = RGB15( r, g, b );
					lPixelsNew += (LONG) pHist[ rgb ];
				}
			}
		}
		TRACE( " R %d %d %d\n", r1, r, r2 );
		if (r < r2) {
			MedianCut(pHist, pClut, lPixelsNew,           nColors / 2, r1   , r , g1, g2, b1, b2, depth );
			MedianCut(pHist, pClut, lPixels - lPixelsNew, nColors / 2, r + 1, r2, g1, g2, b1, b2, depth );
		} else {
			MedianCut(pHist, pClut, lPixelsOld,           nColors / 2, r1, r - 1, g1, g2, b1, b2, depth );
			MedianCut(pHist, pClut, lPixels - lPixelsOld, nColors / 2, r , r2   , g1, g2, b1, b2, depth );
		}
		return;
	}
}

void CMedianCut::ReduceColors( HPDWORD pHistData, LPRGBQUAD pClutData, WORD nColors ) {
	UINT		i, ii, idx;
	BYTE		r, g, b;
	LONG		err1, err2;

	memset( (void FAR*) m_pIdxTab, 0x00, 32768 * sizeof( BYTE ) );

	for( i = 0; i < 32768; i++ ) {
		r = ( i >> 10 & 31 ) << 3;
		g = ( i >>  5 & 31 ) << 3;
		b = ( i       & 31 ) << 3;
		err1 = RGBDist( (int) m_pClut[0].rgbRed - (int) r, (int) m_pClut[0].rgbGreen - (int) g, (int) m_pClut[0].rgbBlue - (int) b );
			
		idx = 0;
		for( ii = 1; ii < 256; ii++ ) {
			err2 = RGBDist( (int) m_pClut[ii].rgbRed - (int) r, (int) m_pClut[ii].rgbGreen - (int) g, (int) m_pClut[ii].rgbBlue - (int) b );
			if( err2 < err1 ) {
				idx = ii;
				err1 = err2;
			}
		}
		m_pIdxTab[i] = (BYTE) idx;
	}
}

BOOL CMedianCut::Filter( CPicture *pI, CPicture *pO, CFilterProgress* proc ) 
{
	if( PICT_COLOR_RGB != pI->GetColorspace( ) )
		return FALSE;
	BOOL ret = FALSE;

	pO->Clone( pI );
	pO->SetColorspace( PICT_COLOR_PAL8 );
	pO->SetClut( m_pClut, 256 );
	MergeTags( pO );
	pO->WriteHeader( );

	GetPictureInfo( pI, pO );

	m_rcSrcBand = pI->GetBestCorePictRect();

	while( m_rcSrcBand.top < m_rcSrcPict.bottom ) {
		if( FALSE == pI->Read( m_rcSrcBand ) ) {
			CString	S;
			S.Format( "Band: [%ld,%ld,%ld,%ld]", m_rcSrcBand.left, m_rcSrcBand.top, m_rcSrcBand.right, m_rcSrcBand.bottom );
			::LAfxThrowPictException( CPictException::errFilterSrcRead, GetRuntimeClass()->m_lpszClassName, S );
			return FALSE;
		}
		m_rcSrcCore = pI->GetCoreImageRect();
		if( FALSE == pO->SetCoreRect( m_rcSrcBand ) )
			break;
		m_rcDstCore = pO->GetCoreImageRect();

		m_pSrcPictData = pI->GetDataPointer();
		m_pDstPictData = pO->GetDataPointer();
		switch( m_method ) {
		case DITHER_3 : ret = Dither3(); break;
		case DITHER_4 : ret = Dither3(); break;		// Dither4 noch nicht implementiert
		default :
			ret = Dither0();
		}
		if( FALSE == ret ) {
			CString	S;
			S.Format( "Band: [%ld,%ld,%ld,%ld]", m_rcSrcBand.left, m_rcSrcBand.top, m_rcSrcBand.right, m_rcSrcBand.bottom );
			::LAfxThrowPictException( CPictException::errFilterProcess, GetRuntimeClass()->m_lpszClassName, S );
			return FALSE;
		}
		if( FALSE == pO->Write( m_rcSrcBand, pI->GetOrientation() ) ) {
			CString	S;
			S.Format( "Band: [%ld,%ld,%ld,%ld]", m_rcSrcBand.left, m_rcSrcBand.top, m_rcSrcBand.right, m_rcSrcBand.bottom );
			::LAfxThrowPictException( CPictException::errFilterWrite, GetRuntimeClass()->m_lpszClassName, S );
			return FALSE;
		}
		m_rcSrcBand.OffsetRect( 0, m_rcSrcBand.Height() );
		m_rcSrcBand.bottom = min( m_rcSrcBand.bottom, m_rcSrcPict.bottom );
	}
	return ret & pO->WriteTrailer();
}

BOOL CMedianCut::Dither0( ) {
	HPBYTE	pSrcLine = m_pSrcPictData;
	HPBYTE	pDstLine = m_pDstPictData;
	long	rows = m_rcSrcBand.Height();
	long	cols = m_rcSrcBand.Width();
	long	rw, co;
	register COLOR		C;
	register HPBYTE	pSrcPixel, pDstPixel;

	for( rw = 0; rw < rows; rw++ ) {
		pSrcPixel = pSrcLine;
		pDstPixel = pDstLine;
		for( co = 0; co < cols; co++ ) {
#ifdef	_DEBUG
			ASSERT( TRUE == m_pI->CheckDataPointer( pSrcPixel ) );
			ASSERT( TRUE == m_pO->CheckDataPointer( pDstPixel ) );
#endif
			C.d = *((DWORD*)pSrcPixel);

			C.b.b4 = 0;
			C.b.b3 >>= 3;
			C.m.w >>= 3;
			C.d >>= 3;
			*pDstPixel = m_pIdxTab[C.w.w1];
			pSrcPixel += 3;
			pDstPixel++;
		}
		pSrcLine += m_rcSrcCore.Width();
		pDstLine += m_rcDstCore.Width();
	}
	return TRUE;
}

#define	CHECKBYTE( b )	(max( 0, min( (b), 255 ) ) )
BOOL CMedianCut::Dither3( ) {
	HPBYTE	pSrcLine = m_pSrcPictData;
	HPBYTE	pDstLine = m_pDstPictData;
	HPBYTE	pSrcPixel, pNextSrcPixel, pDstPixel;
	long	rows = m_rcSrcBand.Height();
	long	cols = m_rcSrcBand.Width();
	long	rw, co;
	BYTE		r, g, b;
	short		er, eg, eb;				// Farbfehler
	short		nr, ng, nb;				// neue RGB-Werte
	COLORREF	rgb;
	BYTE		pal;					// Paletteenindex

	memset( m_pDstPictData, 0x00, rows * cols );
	for( rw = 0; rw < rows; rw++ ) {
		pSrcPixel = pSrcLine;
		pDstPixel = pDstLine;
		for( co = 0; co < cols; co++ ) {
#ifdef	_DEBUG
			ASSERT( TRUE == m_pI->CheckDataPointer( pSrcPixel ) );
			ASSERT( TRUE == m_pO->CheckDataPointer( pDstPixel ) );
#endif
			r = *(pSrcPixel + 2);
			g = *(pSrcPixel + 1);
			b = *(pSrcPixel + 0);
			rgb = RGB15( r >> 3, g >> 3, b >> 3 );
			pal = m_pIdxTab[ rgb ];
			*pDstPixel = pal;
			
			er = (short) r - (short) m_pClut[ pal ].rgbRed;
			eg = (short) g - (short) m_pClut[ pal ].rgbGreen;
			eb = (short) b - (short) m_pClut[ pal ].rgbBlue;

			if( co < cols - 1 ) {
				pNextSrcPixel = pSrcPixel + 3;
				nr = (short) *(pNextSrcPixel + 2) + ( (er + er + er) / 8 );
				ng = (short) *(pNextSrcPixel + 1) + ( (eg + eg + eg) / 8 );
				nb = (short) *(pNextSrcPixel + 0) + ( (eb + eb + eb) / 8 );
				*(pNextSrcPixel + 2) = (BYTE) CHECKBYTE( nr );
				*(pNextSrcPixel + 1) = (BYTE) CHECKBYTE( ng );
				*(pNextSrcPixel + 0) = (BYTE) CHECKBYTE( nb );
			}
			if( rw < rows - 1 ) {
				pNextSrcPixel = pSrcPixel + 3 * cols;
				nr = (short) *(pNextSrcPixel + 2) + ( (er + er + er) / 8 );
				ng = (short) *(pNextSrcPixel + 1) + ( (eg + eg + eg) / 8 );
				nb = (short) *(pNextSrcPixel + 0) + ( (eb + eb + eb) / 8 );
				*(pNextSrcPixel + 2) = (BYTE) CHECKBYTE( nr );
				*(pNextSrcPixel + 1) = (BYTE) CHECKBYTE( ng );
				*(pNextSrcPixel + 0) = (BYTE) CHECKBYTE( nb );
			}
			if( rw < rows - 1 && co < cols - 1 ) {
				pNextSrcPixel = pSrcPixel + 3 * cols + 3;
				nr = (short) *(pNextSrcPixel + 2) + ( er / 4 );
				ng = (short) *(pNextSrcPixel + 1) + ( eg / 4 );
				nb = (short) *(pNextSrcPixel + 0) + ( eb / 4 );
				*(pNextSrcPixel + 2) = (BYTE) CHECKBYTE( nr );
				*(pNextSrcPixel + 1) = (BYTE) CHECKBYTE( ng );
				*(pNextSrcPixel + 0) = (BYTE) CHECKBYTE( nb );
			}
			pSrcPixel += 3;
			pDstPixel++;
		}
		pSrcLine += m_rcSrcCore.Width();
		pDstLine += m_rcDstCore.Width();
	}
	return TRUE;
}

BOOL CMedianCut::Dither4( ) {
	return FALSE;
}

BOOL	CMedianCut::SetFilterData( LPFILTERPARAM pData ) {
	LPMEDIANCUTPARAM	p = (LPMEDIANCUTPARAM) pData;
	CHECK_FILTERSTRUCT( p );
	if( !CPictFilter::SetFilterData( pData ) )
		return FALSE;
	if( DITHER_NONE != p->m && DITHER_3 != p->m && DITHER_4 != p->m ) {
		CString	S;
		S.Format( "unknown Metohd%d", p->m );
		::LAfxThrowPictException( CPictException::errFilterParam, GetRuntimeClass()->m_lpszClassName, S );
		return FALSE;
	}

	m_method = p->m;
	return TRUE;
}

BOOL	CMedianCut::GetFilterData( LPFILTERPARAM pData ) {
	LPMEDIANCUTPARAM	p = (LPMEDIANCUTPARAM) pData;
	CHECK_FILTERSTRUCT( p );
	p->m = m_method;
	return TRUE;
}

void CMedianCut::Serialize( CArchive& ar ) {
	CPictFilter::Serialize( ar );

	WORD	v;

	if( ar.IsStoring( ) ) {
		ar << m_nIdxs;
		ar.Write( (void FAR*) m_pIdxTab, m_nIdxs * sizeof( BYTE ) );
		ar << m_nColors;
		ar.Write( (void FAR*) m_pClut, m_nColors * sizeof( RGBQUAD ) );
	} else {
		ar >> v;
		ar.Read( (void FAR*) m_pIdxTab, m_nIdxs * sizeof( BYTE ) );
		ar >> v;
		ar.Read( (void FAR*) m_pClut, m_nColors * sizeof( RGBQUAD ) );
	}
}
