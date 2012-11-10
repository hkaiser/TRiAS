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

IMPLEMENT_SERIAL( CBmpPicture, CPictureBase, 1 );

#define	new	DEBUG_NEW

//////////////////////////////////////////////////////////////////////////

#include	<limits.h>

CBmpPicture::CBmpPicture( ) {
	Init( );
}

CBmpPicture::CBmpPicture( CMemBlock *pMemBlock )
	: CPictureBase( pMemBlock )
{
	Init( );
}

void CBmpPicture::Init( ) {
	CPictureBase::Init( );
	memset( (void FAR*) &m_BFH, 0x00, sizeof( BITMAPFILEHEADER ) );
	memset( (void FAR*) &m_BIH, 0x00, sizeof( BITMAPINFOHEADER ) );
	SetOrientation( PICT_ORIENT_UPPERLEFT );
	TAGMAP[PICT_PROP_PLANARCONFIGURATION] = TAG( PICT_PROP_PLANARCONFIGURATION, (WORD) PICT_PLANARCFG_CHUNKED );
	SetResolutionUnit( PICT_UNIT_PELS );
}

void CBmpPicture::SetPictRect( const CRect& rcPict ) {
	m_rcImage = m_rcPicture = rcPict;
	m_rcImage.right = Align( m_rcPicture.Width(), m_bitsPerSample, sizeof( DWORD ) );
	TAGMAP[PICT_PROP_IMAGEWIDTH] = TAG( PICT_PROP_IMAGEWIDTH, (ULONG) rcPict.Width() );
	TAGMAP[PICT_PROP_IMAGELENGTH] = TAG( PICT_PROP_IMAGELENGTH, (ULONG) rcPict.Height() );
}

const CRect CBmpPicture::GetBestCorePictRect() {
	CRect rcCore = m_rcPicture;
	rcCore.bottom = TIFFhowmany( m_pMemBlock->Size(), Align( m_rcPicture.Width(), m_bitsPerSample, sizeof( DWORD ) ) );
	rcCore.bottom = min( rcCore.bottom, m_rcPicture.bottom );
	return rcCore;
}

BOOL CBmpPicture::SetCompression( PICT_COMPR compr, CPictException *pE /*= NULL*/ ) {
	if( PICT_COMPR_NOCOMPR == compr 
		|| PICT_COMPR_RLE4 == compr
		|| PICT_COMPR_RLE8 == compr
		)
		m_compression = compr;
	else {
		m_compression = PICT_UNKNOWN_COMPR;
		if( NULL != pE ) {
			CPictCrack	C;
			pE->m_cause = CPictException::errCompression;
			pE->m_strPictType = GetRuntimeClass()->m_lpszClassName;
			pE->m_strCause = C.Crack( PICT_PROP_COMPRESSION, compr );
			pE->m_strPictName = GetFileName();
		}
		return FALSE;
	}
	TAGMAP[PICT_PROP_COMPRESSION] = TAG( PICT_PROP_COMPRESSION, (WORD) m_compression );
	SetPictRect( m_rcPicture );
	return TRUE;
}

BOOL CBmpPicture::SetColorspace( PICT_COLOR color, CPictException *pE /*= NULL*/ ) {
	if( PICT_COLOR_PALETTE == color || PICT_COLOR_PAL8 == color ) {
		m_colorspace = PICT_COLOR_PAL8;
		m_bitsPerSample = 8;
		m_samplesPerPixel = 1;
		m_nColors = m_nUsedColors = 256;
	} else if( PICT_COLOR_PAL4 == color ) {
		m_colorspace = color;
		m_bitsPerSample = 4;
		m_samplesPerPixel = 1;
		m_nColors = m_nUsedColors = 16;
	} else if( PICT_COLOR_MONOBIZ == color || PICT_COLOR_MONOWIZ == color ) {
		m_colorspace = color;
		m_bitsPerSample = 1;
		m_samplesPerPixel = 1;
		m_nColors = m_nUsedColors = 2;
	} else if( PICT_COLOR_RGB == color ) {
		m_colorspace = color;
		m_bitsPerSample = 24;
		m_samplesPerPixel = 1;
		m_nColors = m_nUsedColors = 0;
	} else {
		m_colorspace = PICT_UNKNOWN_COLOR;
		if( NULL != pE ) {
			CPictCrack	C;
			pE->m_cause = CPictException::errCompression;
			pE->m_strPictType = GetRuntimeClass()->m_lpszClassName;
			pE->m_strCause = C.Crack( PICT_PROP_COLORSPACE, color );
			pE->m_strPictName = GetFileName();
		}
		return FALSE;
	}
	TAGMAP[PICT_PROP_BITSPERSAMPLE] = TAG( PICT_PROP_BITSPERSAMPLE, (WORD) m_bitsPerSample );
	TAGMAP[PICT_PROP_COLORSPACE] = TAG( PICT_PROP_COLORSPACE, (WORD) m_colorspace );
	TAGMAP[PICT_PROP_SAMPLESPERPIXEL] = TAG( PICT_PROP_SAMPLESPERPIXEL, (WORD) m_samplesPerPixel );
	SetPictRect( m_rcPicture );
	return TRUE;
}

BOOL CBmpPicture::SetResolutionUnit( PICT_RESUNIT resUnit, CPictException *pE /*= NULL*/ ) {
	BOOL	bRet = TRUE;
	if( PICT_UNIT_PELS != resUnit ) {
		resUnit = PICT_UNKNOWN_UNIT;
		bRet = FALSE;
		if( NULL != pE ) {
			CPictCrack	C;
			pE->m_cause = CPictException::errCompression;
			pE->m_strPictType = GetRuntimeClass()->m_lpszClassName;
			pE->m_strCause = C.Crack( PICT_PROP_RESOLUTIONUNIT, resUnit );
			pE->m_strPictName = GetFileName();
		}
	}
	TAGMAP[PICT_PROP_RESOLUTIONUNIT] = TAG( PICT_PROP_RESOLUTIONUNIT, (WORD) resUnit );
	return bRet;
}

BOOL CBmpPicture::SetOrientation( PICT_ORIENT orient, CPictException *pE /*= NULL*/ ) {
	if( PICT_ORIENT_UPPERLEFT == orient ) {
		m_orientation = orient;
	} else {
		if( NULL != pE ) {
			CPictCrack	C;
			pE->m_cause = CPictException::errCompression;
			pE->m_strPictType = GetRuntimeClass()->m_lpszClassName;
			pE->m_strCause = C.Crack( PICT_PROP_ORIENTATION, orient );
			pE->m_strPictName = GetFileName();
		}
		return FALSE;
	}
	TAGMAP[PICT_PROP_ORIENTATION] = TAG( PICT_PROP_ORIENTATION, (WORD) m_orientation );
	return TRUE;
}

BOOL CBmpPicture::ReadHeader( CPictException *e, int nPicture ) {
	if( 0 != nPicture )
		return FALSE;

	ASSERT( NULL != m_pFile );
	ASSERT_VALID( m_pFile );

	Init( );

	m_pFile->Seek( 0L, CFile::begin );
	m_pFile->Read( (void FAR*) &m_BFH, sizeof( BITMAPFILEHEADER ) );
	if( BF_BMP != m_BFH.bfType ) {
		if( NULL != e ) e->m_cause = CPictException::errFormat;
		return FALSE;
	}
	if( m_BFH.bfSize != m_pFile->GetLength( ) ) {
		if( NULL != e ) e->m_cause = CPictException::errFileSize;
		return FALSE;
	}

	m_pFile->Read( (void FAR*) &m_BIH, sizeof( BITMAPINFOHEADER ) );

	if( sizeof( BITMAPINFOHEADER ) != m_BIH.biSize ) {
		if( NULL != e )
			e->m_cause = CPictException::errFormat;
		return FALSE;
	}
	if( m_BIH.biBitCount != 24 && m_BIH.biBitCount != 8 && m_BIH.biBitCount != 4 && m_BIH.biBitCount != 1 ) {
		if( NULL != e )
			e->m_cause = CPictException::errSample;
		return FALSE;
	} else {
		SetColorspace(
			1 == m_BIH.biBitCount ? PICT_COLOR_MONOBIZ :
			4 == m_BIH.biBitCount ? PICT_COLOR_PAL4 :
			8 == m_BIH.biBitCount ? PICT_COLOR_PAL8 :
			PICT_COLOR_RGB
			);
	}
	if( m_BIH.biCompression != BI_RGB && m_BIH.biCompression != BI_RLE4 && m_BIH.biCompression != BI_RLE8 ) {
		if( NULL != e )
			e->m_cause = CPictException::errCompression;
		return FALSE;
	} else {
		SetCompression(
			BI_RLE4 == m_BIH.biCompression ? PICT_COMPR_RLE4 :
			BI_RLE8 == m_BIH.biCompression ? PICT_COMPR_RLE8 :
			PICT_COMPR_NOCOMPR
			);
	}

	SetPictRect( CRect( 0, 0, m_BIH.biWidth, m_BIH.biHeight ) );
	SetResolutionUnit( PICT_UNIT_PELS );
	SetXResolution( m_BIH.biXPelsPerMeter );
	SetYResolution( m_BIH.biYPelsPerMeter );

	if( m_nUsedColors > 0 )
		m_pFile->Read( (void FAR*) m_pClut, m_nUsedColors * sizeof( RGBQUAD ) );

	////////////////////////////////////////////////////////////////
	// Layout; BMP kennt keine Strips und Tiles

	m_rcStrip = m_rcPicture;

	////////////////////////////////////////////////////////////////
	// Dateigröße muß korrekt sein

	if( PICT_COMPR_NOCOMPR == m_compression 
		&& ( m_rcImage.Width() * m_rcImage.Height() != ( (long) m_pFile->GetLength( ) - (long) m_BFH.bfOffBits ) ) )
	{
		if( NULL != e )
			e->m_cause = CPictException::errFileSize;
		return FALSE;
	}

	////////////////////////////////////////////////////////////////
	// Codec

	ASSERT( NULL == m_pCodec );
	CRuntimeClass	*pRT = NULL;

	switch( m_compression ) {
	case PICT_COMPR_RLE4:
		break;
	case PICT_COMPR_RLE8:
		pRT = RUNTIME_CLASS( CCodecRLE8 );
		break;
	}

	if( NULL != pRT ) {
		VERIFY( m_pCodec = (CPictCodec*) pRT->CreateObject( ) );
		m_pCodec->Attach( this );
	}
	return TRUE;
}

BOOL CBmpPicture::SelectSubFile( int nFile ) {
	return 0 == nFile ? TRUE : FALSE;		// Eine Bitmap hat nur ein (Teil)bild
}

long CBmpPicture::FillBuffer( long line, long startRestBytes, long nRestBytes ) {
	long	nBytes = m_pTmpBlock->Size();
	HPBYTE	pBuffer = *m_pTmpBlock;
	if( 0 == line ) {
		ASSERT_VALID( m_pFile );
		ASSERT( 0 == startRestBytes && 0 == nRestBytes );
		m_pFile->Seek( (long) m_BFH.bfOffBits, CFile::begin );
	}
#ifdef _DEBUG
	m_pTmpBlock->CheckPointer( pBuffer + startRestBytes + nRestBytes );
#endif
	memcpy( (void FAR*) pBuffer, (void FAR*) (pBuffer + startRestBytes), nRestBytes );
	pBuffer += nRestBytes;
	nBytes -= nRestBytes;
	nBytes = m_pFile->ReadHuge( (void FAR*) pBuffer, nBytes );
	return nBytes;
}

long CBmpPicture::AlignTop( long line ) {
	return 0;
}

long CBmpPicture::StoreScanLine( HPBYTE pLine, long line, const CRect& rcCore ) {
	HPBYTE	pSrcLine = pLine;
	HPBYTE	pDstLine;
	long col = rcCore.left;
	long nBytes = rcCore.Width();

	pDstLine = *m_pMemBlock + m_rcImageInCore.Width() * line;

	if( 24 == m_bitsPerSample ) {
		col *= 3;
		nBytes *= 3;
	}
	memcpy( (void FAR*) pDstLine, (void FAR*) &pSrcLine[col], nBytes );
	return nBytes;
}

#ifndef WIN32
#pragma	function( _fmemcpy )
#endif

BOOL CBmpPicture::ReadRaw( const CRect& rcSrc ) {
	ASSERT( NULL != m_pFile );
	ASSERT_VALID( m_pFile );

	long	offset, sizeOfBuf, line;

	offset = m_rcImage.Height() - rcSrc.top - rcSrc.Height(); //rcSrc.top;
	offset *= m_rcImage.Width();
	offset += m_rcImageInCore.left; // Align( rcSrc.left, m_bitsPerSample, sizeof( BYTE ) );
	offset += m_BFH.bfOffBits;

	CRect	rcBand = rcSrc;

	CRect	rcTmp = m_rcImage;
	rcTmp.bottom = TIFFhowmany( m_pTmpBlock->Size(), m_rcImage.Width() ) - 1;
	rcTmp.bottom = min( rcTmp.bottom, rcBand.Height() );

	HPBYTE pTmp = (HPBYTE) *(m_pTmpBlock);
	HPBYTE pDst = (HPBYTE) *(m_pMemBlock);
	HPBYTE pSrc;
//	pDst += m_rcImageInCore.Width() * ( rcBand.Height() - 1 );

	m_pFile->Seek( offset, CFile::begin );

	while( rcBand.top < rcBand.bottom ) {
		sizeOfBuf = rcTmp.Width() * rcTmp.Height();
		m_pFile->Read( (void FAR*) pTmp, (UINT) sizeOfBuf );
		pSrc = pTmp;

		for( line = rcTmp.top; line < rcTmp.bottom; line++ ) {
			memcpy( (void FAR*) pDst, (void FAR*) pSrc, (size_t) m_rcImageInCore.Width() );
			pSrc += m_rcImage.Width();
			pDst += m_rcImageInCore.Width();
		}
		rcBand.OffsetRect( 0, rcTmp.Height() );
		rcBand.bottom = min( rcBand.bottom, rcSrc.bottom );
		rcTmp.bottom = min( rcTmp.bottom, rcBand.Height() );
	}
	return TRUE;
}

BOOL CBmpPicture::Write( const CRect& rcBand, PICT_ORIENT srcOrient /* = PICT_ORIENT_UPPERLEFT */ ) {
	CRect	rcPart;
	if( !rcPart.IntersectRect( m_rcPictInCore, rcBand ) )
		return FALSE;

	long	offset;

	offset = rcPart.top - m_rcPictInCore.top;
	offset *= m_rcImageInCore.Width();
	offset += Align( rcPart.left - m_rcPictInCore.left, m_bitsPerSample, sizeof( BYTE ) );

	HPBYTE	pData = (HPBYTE) *m_pMemBlock;
	pData += offset;

	long left = Align( rcPart.left, m_bitsPerSample, sizeof( BYTE ) );
	long nBytes = Align( rcPart.Width(), m_bitsPerSample, rcPart.Width() == m_rcPicture.Width() ? sizeof( DWORD ) : sizeof( BYTE ) );
	long line = rcPart.top;
	long bOff = m_rcImage.Height() - rcPart.bottom - rcPart.top;
	TRY {
		while( line < rcPart.bottom ) {
			offset = bOff + line;
			offset *= m_rcImage.Width();
			offset += left;
			offset += m_BFH.bfOffBits;
			m_pFile->Seek( offset, CFile::begin );
			m_pFile->WriteHuge( (void FAR*) pData, nBytes );
			pData += m_rcImageInCore.Width();
			line++;
		}
	} CATCH( CFileException, e ) {
		lpictdll::ReportFileException( e );
		DELETE_EXCEPTION( e );
		return FALSE;
	}
	END_CATCH
	return TRUE;
}

long CBmpPicture::GetNeededFileSize( ) {
	long	imageBytes = GetImageRect().Width() * GetImageRect().Height();
	return sizeof( BITMAPFILEHEADER )
		+ sizeof( BITMAPINFOHEADER )
		+ m_nColors * sizeof( RGBQUAD )
		+ imageBytes;
}

BOOL CBmpPicture::WriteHeader( ) {
	UpdateHeaderInfo( );
	DWORD clutSize = m_nColors * sizeof( RGBQUAD );

	TRY {
		m_pFile->Seek( 0, CFile::begin );
		m_pFile->Write( (void FAR*) &m_BFH, sizeof( BITMAPFILEHEADER ) );
		m_pFile->Write( (void FAR*) &m_BIH, sizeof( BITMAPINFOHEADER ) );
		m_pFile->Write( (void FAR*) m_pClut, (UINT) clutSize );
	} CATCH( CFileException, e ) {
		lpictdll::ReportFileException( e );
		DELETE_EXCEPTION( e );
		return FALSE;
	}
	END_CATCH
	return TRUE;
}

BOOL CBmpPicture::WriteTrailer( ) {
	return TRUE;
}

void CBmpPicture::UpdateHeaderInfo( ) {
	DWORD clutSize = m_nColors * sizeof( RGBQUAD );

	m_BFH.bfType		= BF_BMP;
	m_BFH.bfSize		= sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER );
		m_BFH.bfSize += clutSize;
		m_BFH.bfSize += m_rcImage.Width() * m_rcImage.Height();
	m_BFH.bfReserved1	= 0;
	m_BFH.bfReserved2	= 0;
	m_BFH.bfOffBits		= sizeof( BITMAPFILEHEADER ) + sizeof( BITMAPINFOHEADER ) + clutSize;

	m_BIH.biSize		= sizeof( BITMAPINFOHEADER );
	m_BIH.biWidth		= m_rcPicture.Width();
	m_BIH.biHeight		= m_rcPicture.Height();
	m_BIH.biPlanes		= 1;
	m_BIH.biBitCount	= m_bitsPerSample;
	m_BIH.biCompression	= BI_RGB;
	m_BIH.biSizeImage	= m_rcImage.Width() * m_rcImage.Height();
	m_BIH.biXPelsPerMeter = 0;
	m_BIH.biYPelsPerMeter = 0;
	m_BIH.biClrUsed		= m_nColors;
	m_BIH.biClrImportant = m_nUsedColors;
}

void CBmpPicture::Serialize( CArchive& ar ) {
	CPictureBase::Serialize( ar );
}
