#include "stdafx.h"
#include "LPictImpl.h"

#ifdef	PICTFLT_SAMPLE_RELEASED

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL( CPictSample, CPictFilter, 1 );

#define	new	DEBUG_NEW

//////////////////////////////////////////////////////////////////////////

BOOL CPictSample::SetFilterData( LPFILTERPARAM pData ) {
	LPPICTSAMPLEPARAM	p = (LPPICTSAMPLEPARAM) pData;
	CHECK_FILTERSTRUCT( p );

	if( !CPictFilter::SetFilterData( pData ) )
		return FALSE;

	long	sr = p->sampleRate;
	if( 1 != sr && 2 != sr && 4 != sr && 8 != sr && 16 != sr ) {
		CString	S;
		S.Format( "SampleRate: %d; require 1, 2, 4, 8, 16", sr );
		::LAfxThrowPictException( CPictException::errFilterParam, GetRuntimeClass()->m_lpszClassName, S );
		return FALSE;
	}

	m_sampleRate = p->sampleRate;
	m_sampleParam = p->sampleParam;
	return TRUE;
}

#include <limits.h>

static double ColorDiff( RGBQUAD &r1, RGBQUAD &r2 ) 
{
    double	dr = r1.rgbRed - r2.rgbRed;
    double	dg = r1.rgbGreen - r2.rgbGreen;
    double	db = r1.rgbBlue - r2.rgbBlue;

    return  dr * dr + dg * dg + db * db;
}

static int FindBestIndex( RGBQUAD clut[256], int r, int g, int b ) {
	int	idx;
	int best = 0;
	double	bestDiff=3 * 256 * 256;
	double	diff;
	RGBQUAD q;
	q.rgbRed = r;
	q.rgbGreen = g;
	q.rgbBlue = b;

	for( idx = 0; idx < 256; idx++ ) {
		diff = ColorDiff( clut[idx], q );
		if( diff < bestDiff ) {
			bestDiff = diff;
			best = idx;
		}
	}
	return best;
}

static void BuildColors( RGBQUAD clut[256], BYTE colors[32768] ) {
	int	r,g,b;
	int	idx;
//	BYTE	logPal[sizeof(LOGPALETTE) + 256 * sizeof(PALETTEENTRY)];
//	LPLOGPALETTE	lpLogPal = (LPLOGPALETTE) logPal;
//	LPPALETTEENTRY	lpPE = lpLogPal->palPalEntry;

//	lpLogPal->palVersion = 0x0300;
//	lpLogPal->palNumEntries = 256;

//	for( idx = 0; idx < 256; idx++ ) {
//		lpPE->peRed = clut[idx].rgbRed;
//		lpPE->peGreen = clut[idx].rgbGreen;
//		lpPE->peBlue = clut[idx].rgbBlue;
//		lpPE->peFlags = 0;
//	}
//	CPalette	palette;
//	if( !palette.CreatePalette( lpLogPal ) )
//		return;
	for( r = 0; r < 32; r++ ) {
		for( g = 0; g < 32; g++ ) {
			for( b = 0; b < 32; b++ ) {
				idx = r + ( g << 5 ) + ( b << 10 );
//				colors[idx] = (BYTE) ( r + g + b );
				colors[idx] = FindBestIndex( clut, r << 3, g << 3, b << 3 );
			}
		}
	}
}

typedef map< long, RGBQUAD, less<long> > CColorMap;

static void OptimizeColorTable( CPicture *pPicture, RGBQUAD* pClut ) {
	const BYTE bitval[8] = { 1,2,4,8,16,32,64,128 };
	CColorMap haveColor, failColor;
	RGBQUAD	clutOld[256];
	bool	bHaveBlack = false;

	int	i, R, G, B;
	ASSERT_VALID( pPicture );
	pPicture->GetClut( clutOld, 256 );

	for( i = 0; i < 256; ++i ) {
		R = clutOld[i].rgbRed;
		G = clutOld[i].rgbGreen;
		B = clutOld[i].rgbBlue;
		if( 0 == R && 0 == G && 0 == B ) {
			if( bHaveBlack ) {
				failColor.insert( i, clutOld[i] );
				continue;
			}
			bHaveBlack = true;
		}
		haveColor.insert( i, clutOld[i] );
		pClut[i] = clutOld[i];
	}
	int	nGood = haveColor.size();
	int	idx0, idx1;
	for( CColorMap::iterator it = failColor.begin(); failColor.end() != it; ++it ) {
		idx0 = (*it).first;
		idx1 = idx0 % nGood;
		R = haveColor[idx1].rgbRed;
		R = ( R + idx0 ) / 2;
		G = haveColor[idx1].rgbGreen;
		G = ( G + idx0 ) / 2;
		B = haveColor[idx1].rgbBlue;
		B = ( B + idx0 ) / 2;
		pClut[idx0].rgbRed = R;
		pClut[idx0].rgbGreen = G;
		pClut[idx0].rgbBlue = B;
	}
}

//		if( defined( $Ldef{$Schema}{L}{$i} ) ) {
//			$R = $Ldef{$Schema}{$i}{R};
//			$G = $Ldef{$Schema}{$i}{G};
//			$B = $Ldef{$Schema}{$i}{B};
//			$S = sprintf( "%.0f %0.f %.0f", $R, $G, $B );
//			print CLUT "$S\n";
//			$haveColor{$i}=[$R,$G,$B];
//		} else {
//			$failColor{$i}=[$R,$G,$B];
//		}
//	}
//	($nGood,$nItem) = split(/\//, %haveColor);
//	foreach( keys %failColor ) {
//		$R = $haveColor{$_ % $nGood }[0];
//		$R = ( $R + $_ ) / 2;
//		$G = $haveColor{$_ % $nGood }[1];
//		$G = ( $G + $_ ) / 2;
//		$B = $haveColor{$_ % $nGood }[2];
//		$B = ( $B + $_ ) / 2;
//		$S = sprintf( "%.0f %0.f %.0f", $R, $G, $B );
//		print CLUT "$S\n";
//	}
//	close( CLUT );

BOOL CPictSample::Filter( CPicture *pI, CPicture *pO, CFilterProgress* proc ) {
	pO->Clone( pI );
	CRect rcDst = pI->GetPictRect();
	rcDst.right /= 2;
	rcDst.bottom /= 2;
	pO->SetPictRect( rcDst );

	GetPictureInfo( pI, pO );

	m_rcDstBand = pO->GetBestCorePictRect();
	m_rcSrcBand = pI->GetBestCorePictRect();
	m_rcSrcBand.bottom = m_rcDstBand.bottom * 2; // gerade Anzahl an Zeilen

	WORD	spp = pI->GetBitsPerSample( );
	BOOL	ret = FALSE;

	if( 8 == spp && m_sampleParam > 2 ) {
		if( m_sampleParam > 3 ) {
			OptimizeColorTable( pI, m_clut );
			pO->SetClut( m_clut, 256 );
		} else {
			pI->GetClut( m_clut, 256 );
		}
		BuildColors( m_clut, m_colors );
	}

	if( 0 == m_rcSrcBand.Height() )
		return FALSE;

	MergeTags( pO );
//	pO->SetTag( TAGNEWSUBFILETYPE, TAG( (ULONG) 0x01 ) );
	pO->WriteHeader( );

	CString S;
	while( m_rcDstBand.top < m_rcDstPict.bottom ) {
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
		case 1 : ret = Sample1( rcDst.Height(), m_rcDstBand.top, proc ); break;
		case 4 : ret = Sample4( rcDst.Height(), m_rcDstBand.top, proc ); break;
		case 8 : ret = Sample8( rcDst.Height(), m_rcDstBand.top, proc ); break;
		case 24 : ret = Sample24( rcDst.Height(), m_rcDstBand.top, proc ); break;
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
	return pO->WriteTrailer( );
}

extern unsigned short BitWeightTable[0x10000];

inline 
void StatusReport( CFilterProgress* proc, long line, long nLines ) 
{
	if( line > 0 && nLines > 0 && (line % 50) == 0 ) {
		proc->ReportingStatus( ( (double) line / (double) nLines ) * 100 );
	}
}


BOOL CPictSample::Sample1( long nLinesInPicture, long StartOffset, CFilterProgress* proc ) 
{
	typedef union tagB {
		BYTE	b[2];
		WORD	w;
	} B;

	long	SrcLineIncrement = 2 * m_BytesPerSrcLine;
	HPBYTE	pSrcLine1, pSrcLine2, pDstLine;
	HPWORD	pSrcDat1, pSrcDat2;
	HPBYTE	pDstDat;
	B		S1, S2, W;
	BYTE	T, D;
	int		shift = 0 == m_sampleParam ? 0 :
					1 == m_sampleParam ? 4 :
					2 == m_sampleParam ? 8 :
					3 == m_sampleParam ? 12 :
					0;

	WORD	mask = 0x000f << shift;

	long	Line, Col;
	long	dstLines = m_rcDstBand.Height();
	long	dstCols = m_rcDstBand.Width();

	pSrcLine1 = m_pSrcPictData;
	pSrcLine2 = m_pSrcPictData + SrcLineIncrement / 2;
	pDstLine = m_pDstPictData;

	for( Line = 0; Line < dstLines; Line++ ) {
		if( proc ) {
			StatusReport( proc, Line + StartOffset, nLinesInPicture );
		}
		pSrcDat1 = (HPWORD) pSrcLine1;
		pSrcDat2 = (HPWORD) pSrcLine2;
		pDstDat = pDstLine;
		for( Col = 0; Col < dstCols; Col += 8 ) {
			D = 0;
			S1.w = *pSrcDat1++;
			S2.w = *pSrcDat2++;
			W.b[0] = S1.b[0];
			W.b[1] = S2.b[0];
			T = ( BitWeightTable[W.w] & mask ) >> shift;
			D |= T << 4;
			W.b[0] = S1.b[1];
			W.b[1] = S2.b[1];
			T = ( BitWeightTable[W.w] & mask ) >> shift;
			D |= T;
			*pDstDat++ = D;
		}
		pSrcLine1 += SrcLineIncrement;
		pSrcLine2 += SrcLineIncrement;
		pDstLine += m_BytesPerDstLine;
	}
	return TRUE;
}

BOOL CPictSample::Sample4( long nLinesInPicture, long StartOffset, CFilterProgress* proc ) 
{
	long	nLine, nCol;
	long	nDstLines = m_rcDstBand.Height();
	long	nDstCols = m_rcDstBand.Width();
	long	SrcLineIncrement = 2 * m_BytesPerSrcLine;
	HPBYTE pSrcDat1, pSrcLine1 = m_pSrcPictData;
	HPBYTE pSrcDat2, pSrcLine2 = m_pSrcPictData + SrcLineIncrement / 2;
	HPBYTE pDstData, pDstLine = m_pDstPictData;
	for( nLine = 0; nLine < nDstLines; ++nLine ) {
		pSrcDat1 = pSrcLine1;
		pSrcDat2 = pSrcLine2;
		pDstData = pDstLine;
		if( proc ) { StatusReport( proc, nLine + StartOffset, nLinesInPicture ); }
		for( nCol = 0; nCol < nDstCols; ++nCol ) {
			*pDstData++ = *pSrcDat1++;
			pSrcDat1++;
		}
		pSrcLine1 += SrcLineIncrement;
		pSrcLine2 += SrcLineIncrement;
		pDstLine += m_BytesPerDstLine;
	}
	return TRUE;
}

namespace {

    inline void
    ColorAv1(RGBQUAD& c1, RGBQUAD const& c2)
    {
        if (255 != c2.rgbBlue || 255 != c2.rgbGreen || 255 != c2.rgbRed) {
		    c1.rgbRed = (c1.rgbRed + c2.rgbRed) / 2;
		    c1.rgbGreen = (c1.rgbGreen + c2.rgbGreen) / 2;
		    c1.rgbBlue = (c1.rgbBlue + c2.rgbBlue) / 2;
        }
    }

    inline void
    ColorAv2(RGBQUAD& c1, RGBQUAD const& c2)
    {
        if (255 == c1.rgbBlue && 255 == c1.rgbGreen && 255 == c1.rgbRed) {
		    c1.rgbRed = c2.rgbRed;
		    c1.rgbGreen = c2.rgbGreen;
		    c1.rgbBlue = c2.rgbBlue;
        }
        else if (255 != c2.rgbBlue || 255 != c2.rgbGreen || 255 != c2.rgbRed) {
		    c1.rgbRed = (c1.rgbRed + c2.rgbRed) / 2;
		    c1.rgbGreen = (c1.rgbGreen + c2.rgbGreen) / 2;
		    c1.rgbBlue = (c1.rgbBlue + c2.rgbBlue) / 2;
        }
    }
}

BOOL CPictSample::Sample8( long nLinesInPicture, long StartOffset, CFilterProgress* proc ) 
{
	HPBYTE	pDstLine, pDstPixel;
	HPBYTE	pSrcLine1, pSrcPixel1, pSrcLine2, pSrcPixel2;
	RGBQUAD	r1, r2;
	int		idx;

	pSrcLine1 = m_pSrcPictData;
	pSrcLine2 = m_pSrcPictData + m_BytesPerSrcLine;
	pDstLine = m_pDstPictData;
	
	long	Line, Col;
	long	srcLines = m_rcSrcBand.Height();
	long	srcCols = m_rcSrcBand.Width();

	for( Line = 0; Line < srcLines; Line += 2 ) {
		if( proc ) {
			StatusReport( proc, Line + StartOffset, nLinesInPicture );
		}
		pSrcPixel1 = pSrcLine1;
		pSrcPixel2 = pSrcLine2;
		pDstPixel = pDstLine;
		if( 0 == m_sampleParam ) {
			for( Col = 0; Col < srcCols; Col += 2 ) {
	#ifdef	_DEBUG
				ASSERT( TRUE == m_pI->CheckDataPointer( (HPBYTE) pSrcPixel1 ) );
				ASSERT( TRUE == m_pO->CheckDataPointer( pDstPixel ) );
	#endif
				*pDstPixel = *pSrcPixel1;
				pSrcPixel1 += 2;
				pSrcPixel2 += 2;
				pDstPixel++;
			}
		} else if( m_sampleParam > 0 ) {
			for( Col = 0; Col < srcCols; Col += 2 ) {
	#ifdef	_DEBUG
				ASSERT( TRUE == m_pI->CheckDataPointer( (HPBYTE) pSrcPixel1 ) );
				ASSERT( TRUE == m_pO->CheckDataPointer( pDstPixel ) );
	#endif
				r1 = m_clut[pSrcPixel1[0]];
				r2 = m_clut[pSrcPixel1[1]];
                ColorAv2(r1, r2);
//				r1.rgbRed = ( r1.rgbRed + r2.rgbRed ) / 2;
//				r1.rgbGreen = ( r1.rgbGreen + r2.rgbGreen ) / 2;
//				r1.rgbBlue = ( r1.rgbBlue + r2.rgbBlue ) / 2;

				r2 = m_clut[pSrcPixel2[0]];
                ColorAv1(r1, r2);
//				r1.rgbRed = ( r1.rgbRed + r2.rgbRed ) / 2;
//				r1.rgbGreen = ( r1.rgbGreen + r2.rgbGreen ) / 2;
//				r1.rgbBlue = ( r1.rgbBlue + r2.rgbBlue ) / 2;
				
                r2 = m_clut[pSrcPixel2[1]];
                ColorAv1(r1, r2);
//				r1.rgbRed = ( r1.rgbRed + r2.rgbRed ) / 2;
//				r1.rgbGreen = ( r1.rgbGreen + r2.rgbGreen ) / 2;
//				r1.rgbBlue = ( r1.rgbBlue + r2.rgbBlue ) / 2;
				
                idx = ( r1.rgbRed >> 3 ) + ( ( r1.rgbGreen >> 3 ) << 5 ) + ( ( r1.rgbBlue >> 3 ) << 10 );
				*pDstPixel = m_colors[idx];
				pSrcPixel1 += 2;
				pSrcPixel2 += 2;
				pDstPixel++;
			}
		}
		pSrcLine1 += 2 * m_BytesPerSrcLine;
		pSrcLine2 += 2 * m_BytesPerSrcLine;
		pDstLine += m_BytesPerDstLine;
	}
	return TRUE;
}

BOOL CPictSample::Sample24( long nLinesInPicture, long StartOffset, CFilterProgress* proc ) 
{
	RGBTRIPLE *pDstLine, *pDstPixel;
	RGBTRIPLE *pSrcLine1, *pSrcPixel1, *pSrcLine2, *pSrcPixel2;

	pSrcLine1 = (RGBTRIPLE *)m_pSrcPictData;
	pSrcLine2 = (RGBTRIPLE *)(m_pSrcPictData + m_BytesPerSrcLine);
	pDstLine = (RGBTRIPLE *)m_pDstPictData;
	
	long	Line, Col;
	long	srcLines = m_rcSrcBand.Height();
	long	srcCols = m_rcSrcBand.Width();

	for( Line = 0; Line < srcLines; Line += 2 ) {
		if( proc ) {
			StatusReport( proc, Line + StartOffset, nLinesInPicture );
		}
		pSrcPixel1 = pSrcLine1;
		pSrcPixel2 = pSrcLine2;
		pDstPixel = pDstLine;
		if( 0 == m_sampleParam ) {
			for( Col = 0; Col < srcCols; Col += 2 ) {
#ifdef	_DEBUG
				ASSERT( TRUE == m_pI->CheckDataPointer( (HPBYTE) pSrcPixel1 ) );
				ASSERT( TRUE == m_pO->CheckDataPointer( (HPBYTE)pDstPixel ) );
#endif
				*pDstPixel = *pSrcPixel1;
				pSrcPixel1 += 2;
				pSrcPixel2 += 2;
				pDstPixel++;
			}
		} 
		else if( m_sampleParam > 0 ) {
		RGBTRIPLE r1, r2;

			for( Col = 0; Col < srcCols; Col += 2 ) {
#ifdef	_DEBUG
				ASSERT( TRUE == m_pI->CheckDataPointer( (HPBYTE) pSrcPixel1 ) );
				ASSERT( TRUE == m_pO->CheckDataPointer( (HPBYTE) pDstPixel ) );
#endif
				r1 = pSrcPixel1[0];
				r2 = pSrcPixel1[1];
				r1.rgbtRed = ( r1.rgbtRed + r2.rgbtRed ) / 2;
				r1.rgbtGreen = ( r1.rgbtGreen + r2.rgbtGreen ) / 2;
				r1.rgbtBlue = ( r1.rgbtBlue + r2.rgbtBlue ) / 2;
				r2 = pSrcPixel2[0];
				r1.rgbtRed = ( r1.rgbtRed + r2.rgbtRed ) / 2;
				r1.rgbtGreen = ( r1.rgbtGreen + r2.rgbtGreen ) / 2;
				r1.rgbtBlue = ( r1.rgbtBlue + r2.rgbtBlue ) / 2;
				r2 = pSrcPixel2[1];
				r1.rgbtRed = ( r1.rgbtRed + r2.rgbtRed ) / 2;
				r1.rgbtGreen = ( r1.rgbtGreen + r2.rgbtGreen ) / 2;
				r1.rgbtBlue = ( r1.rgbtBlue + r2.rgbtBlue ) / 2;
				*pDstPixel = r1;
				pSrcPixel1 += 2;
				pSrcPixel2 += 2;
				pDstPixel++;
			}
		}
		pSrcLine1 = (RGBTRIPLE *)((HPBYTE)pSrcLine1 + 2 * m_BytesPerSrcLine);
		pSrcLine2 = (RGBTRIPLE *)((HPBYTE)pSrcLine2 + 2 * m_BytesPerSrcLine);
		pDstLine = (RGBTRIPLE *)((HPBYTE)pDstLine + m_BytesPerDstLine);
	}
	return TRUE;
}

void CPictSample::Serialize( CArchive& ar ) {
	CPictFilter::Serialize( ar );
}

#endif	// PICTFLT_SAMPLE_RELEASED
