// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 17.03.2002 13:57:19 
//
// @doc
// @module picttif.cpp | Definition of the <c Cpicttif> class

#include "stdafx.h"
#include "LPictImpl.h"
//#include "LPict42.ver"

//#include "lpict/PictProp.h"
#include <ctype.h>

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL( CTifPicture, CPictureBase, 1 );

#define	new	DEBUG_NEW
#define	NOT_IMPLEMENTED	FALSE

//////////////////////////////////////////////////////////////////////////
BYTE FlipBYTE( BYTE b1 )
{
	BYTE b2;
	b2 =      ((b1 << 7) & 0x80);
	b2 = b2 | ((b1 << 5) & 0x40);
	b2 = b2 | ((b1 << 3) & 0x20);
	b2 = b2 | ((b1 << 1) & 0x10);
	b2 = b2 | ((b1 >> 1) & 0x08);
	b2 = b2 | ((b1 >> 3) & 0x04);
	b2 = b2 | ((b1 >> 5) & 0x02);
	b2 = b2 | ((b1 >> 7) & 0x01);
	return b2;
}

//////////////////////////////////////////////////////////////////////////
// Konvertierung eines Double-Wertes in einen Rational - Wert

void dbl2ratio( double d, ULONG& div, ULONG& denom );

CTifPicture::CTifPicture( )
	: CPictureBase( ) {
	m_pStripInfo = NULL;
	Init( );
}

CTifPicture::CTifPicture( CMemBlock *pMemBlock )
	: CPictureBase( pMemBlock ) {
	m_pStripInfo = NULL;
	Init( );
}

CTifPicture::~CTifPicture( ) {
	DeleteStripInfo();
}

void CTifPicture::Init( ) {
	CPictureBase::Init( );
	TAGMAP[PICT_PROP_G4OPTIONS] = TAG( PICT_PROP_G4OPTIONS, (DWORD) PICT_G4_NOOPTION );
	DeleteStripInfo();
	m_nExtraSamples			= -1;
	m_nPredictor			= -1;
	m_bIsII					= TRUE;
	memset( (void*) &m_tifHeader, 0x00, sizeof( TIFHEADER ) );
}

//static LPCTSTR szArtist = _T("FEZ Potsdam GmbH");
static LPCTSTR szArtist = _T("Hartmut Kaiser");

BOOL CTifPicture::Clone( CPicture *pPicture, CPictException *pE /*= NULL*/ ) {
	AFX_MANAGE_STATE(AfxGetModuleState());
	CString	strSoftware;
	CString strSoftware1;
	CString strSoftware2;
	VERIFY(strSoftware1.LoadString(1));		// Versionsnummer
	VERIFY(strSoftware2.LoadString(2));		// Dateiname

	strSoftware = strSoftware2;
	strSoftware += _T(" ");
	strSoftware += strSoftware1;

	if( !CPictureBase::Clone( pPicture, pE ) )
		return FALSE;
	SetCompression( PICT_COMPR_NOCOMPR );

	CString	S;
	CString U, H;
	char	strHost[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD	dwLength = sizeof( strHost );
	if( ::GetComputerName( strHost, &dwLength ) )
		H = strHost;
	if( ::GetUserName( strHost, &dwLength ) )
		U = strHost;

	if( H.GetLength() > 0 )
		H += " ";
	if( U.GetLength() > 0 ) {
		H += "(";
		H += U;
		H += ")";
	}
	CTime	t = CTime::GetCurrentTime();
	CString	T = t.Format( _T("%Y:%m:%d %H:%M:%S") );

	MergeTag( PICT_PROP_ARTIST, szArtist );
	MergeTag( PICT_PROP_HOSTCOMPUTER, H );
	MergeTag( PICT_PROP_SOFTWARE, strSoftware );
	SetTag( PICT_PROP_DATETIME, TAG( PICT_PROP_DATETIME, T, T.GetLength() + 1 ) );
	return TRUE;
}

void CTifPicture::SetPictRect( const CRect& rcPict ) {
	m_rcPicture = m_rcImage = rcPict;
	m_rcImage.right = Align( m_rcPicture.right, m_bitsPerSample, sizeof( BYTE ) );

	TAGMAP[PICT_PROP_IMAGEWIDTH] = TAG( PICT_PROP_IMAGEWIDTH, (ULONG) rcPict.Width() );
	TAGMAP[PICT_PROP_IMAGELENGTH] = TAG( PICT_PROP_IMAGELENGTH, (ULONG) rcPict.Height() );
}

const CRect CTifPicture::GetBestCorePictRect() {
	CRect rcCore = m_rcPicture;
	rcCore.bottom = TIFFhowmany( m_pMemBlock->Size(), Align( m_rcPicture.Width(), m_bitsPerSample, sizeof( BYTE ) ) );
	rcCore.bottom = min( rcCore.bottom, m_rcPicture.bottom );
	return rcCore;
}

BOOL CTifPicture::SetCompression( PICT_COMPR compr, CPictException *pE /*= NULL*/ ) {
	if( PICT_COMPR_NOCOMPR == compr )
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
//	SetPictRect( m_rcPicture );
	return TRUE;
}

BOOL CTifPicture::SetColorspace( PICT_COLOR color, CPictException *pE /*= NULL*/ ) {
	if( PICT_COLOR_PAL4 == color ) {
		color = PICT_COLOR_PALETTE;
		m_bitsPerSample = 4;
		m_samplesPerPixel = 1;
	} else if( PICT_COLOR_PAL8 == color ) {
		color = PICT_COLOR_PALETTE;
		m_bitsPerSample = 8;
		m_samplesPerPixel = 1;
	}

	if( PICT_COLOR_PALETTE == color ) {
		m_colorspace = PICT_COLOR_PALETTE;
		ASSERT( 0 != m_bitsPerSample && 0 != m_samplesPerPixel );
		m_nColors = m_nUsedColors = ( 1 << m_bitsPerSample );
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

	if (24 == m_bitsPerSample) {
	WORD bits[3] = { 8, 8, 8 };

		TAGMAP[PICT_PROP_BITSPERSAMPLE] = TAG( PICT_PROP_BITSPERSAMPLE, (WORD) m_bitsPerSample, 3, bits );
		TAGMAP[PICT_PROP_SAMPLESPERPIXEL] = TAG( PICT_PROP_SAMPLESPERPIXEL, (WORD) 3 );
	}
	else {
		TAGMAP[PICT_PROP_BITSPERSAMPLE] = TAG( PICT_PROP_BITSPERSAMPLE, (WORD) m_bitsPerSample );
		TAGMAP[PICT_PROP_SAMPLESPERPIXEL] = TAG( PICT_PROP_SAMPLESPERPIXEL, (WORD) m_samplesPerPixel );
	}
	TAGMAP[PICT_PROP_COLORSPACE] = TAG( PICT_PROP_COLORSPACE, (WORD) m_colorspace );

//	SetPictRect( m_rcPicture );
	return TRUE;
}

BOOL CTifPicture::SetResolutionUnit( PICT_RESUNIT resUnit, CPictException *pE /*= NULL*/ ) {
	BOOL	bRet = TRUE;
	if( PICT_UNIT_NOUNIT != resUnit && PICT_UNIT_INCH != resUnit && PICT_UNIT_CM != resUnit ) {
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

BOOL CTifPicture::SetOrientation( PICT_ORIENT orient, CPictException *pE /*= NULL*/ ) {
	m_orientation = orient;
	return TRUE;
}

BOOL CTifPicture::SetClut( LPRGBQUAD pClut, long items /*= 256*/ ) {
	if( !( PICT_COLOR_PALETTE == m_colorspace ) )
		return FALSE;
	if( !CPictureBase::SetClut( pClut, items ) )
		return FALSE;

	ASSERT( NULL != m_pClut );

	WORD	tifPal[ 3 * 256 ], *pColor;
	memset( (void*) tifPal, 0x00, sizeof( tifPal ) );

	int	i;
	pColor = &tifPal[0 * 256];
	for( i = 0; i < m_nUsedColors; i++ )
		pColor[i] = m_pClut[i].rgbRed << 8;
	pColor = &tifPal[1 * 256];
	for( i = 0; i < m_nUsedColors; i++ )
		pColor[i] = m_pClut[i].rgbGreen	<< 8;
	pColor = &tifPal[2 * 256];
	for( i = 0; i < m_nUsedColors; i++ )
		pColor[i] = m_pClut[i].rgbBlue << 8;
	TAGMAP[PICT_PROP_COLORMAP] = TAG( PICT_PROP_COLORMAP, (WORD) ( 3 * 256 ), ( 3 * 256 ), (void*) tifPal );
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////
// Zusammenbasteln von Fehlerzuständen, in Erzeugen von 'false', so daß
// Funktion mit 'return TagError(...)' verlassen werden kann

bool CTifPicture::TagError( int cause, long tagNum, CPictException *e /*= NULL*/ ) {
	if( NULL != e ) {
		CString	S;
		S.Format( _T("%d [0x%04x]"), tagNum, tagNum );
		e->m_cause = cause;
		e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
		e->m_strCause = S;
		e->m_strPictName = m_pFile->GetFilePath();
	}
	return false;
}

bool CTifPicture::TagError( int cause, LPCTSTR lpszDescr, CPictException *e /*= NULL*/ ) {
	if( NULL != e ) {
		e->m_cause = cause;
		e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
		e->m_strCause = lpszDescr;
		e->m_strPictName = m_pFile->GetFilePath();
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////
// Ein 'intelligenter Puffer'; Allokiert und hält Zeiger auf Speicherblock

typedef struct tagBYTEBUFFER {
	long	m_nSize;
	BYTE	*m_pData;
	void	Alloc( long nBytes );
	operator	void*() const;
	operator	HPBYTE() const;
	operator	HPDWORD() const;
	operator	HPWORD() const;
	BYTE&	operator[]( long nItem );
	tagBYTEBUFFER() : m_nSize(0), m_pData(NULL) {}
	~tagBYTEBUFFER() { if( m_pData ) delete m_pData; }
} BYTEBUFFER;

#define BUFSIZE	2048

inline void BYTEBUFFER::Alloc( long nBytes ) {
	if( m_nSize > nBytes )
		return;
	if( m_pData )
		delete m_pData;
	m_pData = NULL;
	TRY {
		long	newSize = ( ( nBytes + BUFSIZE ) / BUFSIZE ) * BUFSIZE;
		m_pData = new BYTE[newSize];
		m_nSize = newSize;
	} CATCH( CMemoryException, e ) {
		DELETE_EXCEPTION(e);
	} END_CATCH
	if( NULL == m_pData )
		AfxThrowMemoryException();
}

inline BYTEBUFFER::operator void*() const {
	return (void*) m_pData;
}

inline BYTEBUFFER::operator HPBYTE() const {
	return m_pData;
}

inline BYTEBUFFER::operator HPDWORD() const {
	return (HPDWORD) m_pData;
}

inline BYTEBUFFER::operator HPWORD() const {
	return (HPWORD) m_pData;
}

inline BYTE& BYTEBUFFER::operator[]( long nItem ) {
	ASSERT( m_nSize > nItem );
	return m_pData[nItem];
}

BOOL CTifPicture::ReadHeader( CPictException *e, int nPicture ) {
	ASSERT( NULL != m_pFile );
	ASSERT_VALID( m_pFile );

	BYTEBUFFER	byteBuf;
	BYTEBUFFER	tagBuf;
	TIFHEADER	tifHeader;

//	DWORD	stripOffsetCount = 0L;	// Anzahl der Streifenoffsets
//	DWORD	stripOffsetOffset = 0L;	// wo stehen sie in der Datei?
//	WORD	stripOffsetType = 0;	// Typ für Offsetangaben

//	DWORD	stripSizeCount = 0L;	// Anzahl der Größenangaben
//	DWORD	stripSizeOffset = 0L;	// wo stehen sie in der Datei?
//	WORD	stripSizeType = 0;		// Typ für Größenangaben

	FILETAG	*pTag = NULL;			// aktuelles Tag
	short	nTags;					// Anzahl Image-File-Descriptoren
	BOOL	bRet = TRUE;

	Init( );

	if( m_pFile->GetLength() < sizeof( TIFHEADER ) )
		return FALSE;
	m_pFile->SeekToBegin();
	
	TRY {
		m_pFile->Read( (void FAR*) &tifHeader, sizeof( TIFHEADER ) );

		switch( tifHeader.wByteOrder ) {
		case BYTEORDER_II :
			m_bIsII = TRUE;
			break;
		case BYTEORDER_MM :
			m_bIsII = FALSE;
			break;
		default :
			return FALSE;
		}

		DWORD	offset = ReadLong( tifHeader.dwIFD );
		m_pFile->Seek( offset, CFile::begin );
		m_pFile->Read( (void FAR*) &nTags, sizeof( short ) );
		nTags = ReadShort( nTags );

		while( nPicture ) {
			m_pFile->Seek( nTags * sizeof( FILETAG ), CFile::current );
			m_pFile->Read( (void FAR*) &offset, sizeof( offset ) );
			offset = ReadLong( offset );
			if( 0 == offset )
				break;
			m_pFile->Seek( offset, CFile::begin );
			m_pFile->Read( (void FAR*) &nTags, sizeof( short ) );
			nTags = ReadShort( nTags );
			nPicture--;
		}
		if( nPicture ) {
			if( NULL != e ) {
				e->m_cause = CPictException::errSubfileNotFound;
				e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
				e->m_strCause = szUnknown;
				e->m_strPictName = m_pFile->GetFilePath();
			}
			return FALSE;			// Subbilder gefordert, aber keine da
		}

		tagBuf.Alloc( nTags * sizeof( FILETAG ) + sizeof(DWORD) );

		m_pFile->Read( tagBuf, nTags * sizeof( FILETAG ) + sizeof( DWORD ) );

		pTag = (FILETAG*) ((void*) tagBuf);

		for( short i = 0; i < nTags; i++ ) {
			PICT_PROPERTY	prop = Tag(pTag);
			switch( Tag( pTag ) ) {
	
			case PICT_PROP_BITSPERSAMPLE:	
				if( 1 == TagCount( pTag ) ) {
					m_bitsPerSample = (WORD) TagSVal( pTag );
					m_nColors = ( 1 << m_bitsPerSample );
				} else {
					byteBuf.Alloc( 3 * sizeof( short ) );
					m_pFile->Seek( TagLVal( pTag ), CFile::begin );
					m_pFile->Read( byteBuf, 3 * sizeof( short ) );
					short* pShort = (short*) (BYTE*) byteBuf;
					ASSERT( pShort );
					if( ReadShort( pShort[0] ) == 8 &&
						ReadShort( pShort[1] ) == 8 &&
						ReadShort( pShort[2] ) == 8 ) {
						m_bitsPerSample = 24;
						m_nColors = 0;
					} else {
						m_bitsPerSample = 0;  // Unbekanntes Farbformat
						m_nColors = 0;
					}
				}
				break;

			case PICT_PROP_STRIPOFFSETS:
//				stripOffsetCount	= TagCount( pTag );		// Anzahl Werte im Offset-Feld
//				stripOffsetType		= TagType( pTag );		// Typ der Werte
//				stripOffsetOffset	= TagLVal( pTag );		// wo sind sie in der Datei
				break;
			case PICT_PROP_STRIPBYTECOUNTS:
//				stripSizeCount		= TagCount( pTag );
//				stripSizeType		= TagType( pTag );
//				stripSizeOffset		= TagLVal( pTag );
				break;
			case PICT_PROP_TILEOFFSETS:
//				stripOffsetCount	= TagCount( pTag );		// Anzahl Werte im Offset-Feld
//				stripOffsetType		= TagType( pTag );		// Typ der Werte
//				stripOffsetOffset	= TagLVal( pTag );		// wo sind sie in der Datei
				break;
			case PICT_PROP_TILEBYTECOUNTS:
//				stripSizeCount		= TagCount( pTag );
//				stripSizeType		= TagType( pTag );
//				stripSizeOffset		= TagLVal( pTag );
				break;
			case PICT_PROP_SAMPLESPERPIXEL:
				m_samplesPerPixel = (WORD) TagSVal( pTag );
				break;
			case PICT_PROP_EXTRASAMPLES:
				m_nExtraSamples = TagSVal( pTag );
				break;
			case PICT_PROP_TILEWIDTH:
				m_rcStrip.SetRect( 0, 0, PICT_DATA_SHORT == TagType( pTag ) ? TagSVal( pTag ) : TagLVal( pTag ), m_rcStrip.Height() );
				break;
			case PICT_PROP_TILELENGTH:
				m_rcStrip.SetRect( 0, 0, m_rcStrip.Width(), PICT_DATA_SHORT == TagType( pTag ) ? TagSVal( pTag ) : TagLVal( pTag ) );
				break;
			case PICT_PROP_FILLORDER:
				this->m_nFillOrder = (PICT_FORDER)TagSVal( pTag );
				break;
			case PICT_PROP_COLORSPACE:
				this->m_colorspace = (PICT_COLOR)TagSVal( pTag );
				break;
			default:
				break;
			}
			if( TagCount( pTag ) > 1
				|| PICT_DATA_RATIONAL == TagType( pTag )
				|| PICT_DATA_SRATIONAL == TagType( pTag ) ) {
				long size;
				switch( TagType( pTag ) ) {
				case PICT_DATA_BYTE	: size = sizeof( BYTE ); break;
				case PICT_DATA_SHORT	: size = sizeof( SHORT ); break;
				case PICT_DATA_LONG	: size = sizeof( LONG ); break;
				case PICT_DATA_ASCII	: size = sizeof( char ); break;
				case PICT_DATA_FLOAT : size = sizeof( float ); break;
				case PICT_DATA_DOUBLE : size = sizeof( double ); break;
				case PICT_DATA_RATIONAL : size = sizeof( URATIO ); break;
				case PICT_DATA_SRATIONAL : size = sizeof( SRATIO ); break;
				default : size = 0;
				}
				size *= TagCount( pTag );
				byteBuf.Alloc( size );
				/////////////////////////////////////////////////////////////////////
				// Hack für TIFF-Writer die ASCII Felder <= 4 falsch rausschreiben;
				// - in diesem Fall müssen die ASCII - Daten in pTag->dwValue stehen
				//   (pTag->dwValue wird als ein Array von 4 Bytes aufgefaßt)
				//   die fehlerhaften Writer schreiben den Taginhalt allerdings
				//   nach außerhalb
				// - wir versuchen einfach das bestpassende zu finden
				if( size <= 4 ) {
					if( PICT_DATA_ASCII == TagType( pTag ) ) {
						BYTE	b1[4], b2[4], *pB = NULL;
						if( TagLVal( pTag ) + size < m_pFile->GetLength() ) {
							m_pFile->Seek( TagLVal( pTag ), CFile::begin );
							m_pFile->Read( b1, size );
							*( (DWORD*) b2 ) = TagLVal( pTag );
							for( int i = 0; i < size; ++i ) {
								if( b1[i] < ' ' || b1[i] > '~' ) {
									pB = b2;
									break;
								}
								if( b2[i] < ' ' || b2[i] > '~' ) {
									pB = b1;
									break;
								}
							}
						} else {
							pB = (BYTE*) &pTag->dwValue;
						}
						if( NULL == pB )
							pB = (BYTE*) "xxxxx";
						memcpy( byteBuf, pB, size );
						byteBuf[size] = 0x00;
					} else {
						memcpy( byteBuf, &pTag->dwValue, size );
					}
				} else {
					m_pFile->Seek( TagLVal( pTag ), CFile::begin );
					m_pFile->Read( byteBuf, size );
				}
			}
			
			switch( TagType( pTag ) ) {
			case PICT_DATA_BYTE		:
				TAGMAP[Tag(pTag)] = TAG( Tag(pTag), (BYTE) TagSVal( pTag ), TagCount( pTag ), byteBuf );
				break;
			case PICT_DATA_SHORT	:
				TAGMAP[Tag(pTag)] = TAG( Tag(pTag), TagSVal( pTag ), TagCount( pTag ), byteBuf );
				break;
			case PICT_DATA_LONG		:
				TAGMAP[Tag(pTag)] = TAG( Tag(pTag), TagLVal( pTag ), TagCount( pTag ), byteBuf );
				break;
			case PICT_DATA_RATIONAL	: {
					DWORD* p = (DWORD*) ((BYTE*) byteBuf);
					ASSERT( p );
					TAGMAP[Tag(pTag)] = TAG( Tag(pTag), (ULONG) ReadLong(p[0]),(ULONG)ReadLong(p[1]));
				} 
				break;
			case PICT_DATA_ASCII		: {
					if( TagCount( pTag ) > 1 ) {
						LPCTSTR p = (LPCTSTR) ((BYTE*) byteBuf);
						ASSERT( p );
						TAGMAP[Tag(pTag)] = TAG( Tag(pTag), p, TagCount( pTag ) ); 
					}
					else
						TAGMAP[Tag(pTag)] = TAG( Tag(pTag), "", TagCount( pTag ) ); 
				}
				break;
			case PICT_DATA_FLOAT	:
				TAGMAP[Tag(pTag)] = TAG( Tag(pTag), (float) 0, TagCount( pTag ), byteBuf );
				break;
			case PICT_DATA_DOUBLE	:
				TAGMAP[Tag(pTag)] = TAG( Tag(pTag), (double) 0, TagCount( pTag ), byteBuf ); 
				break;
			}
			TAGMAP[Tag(pTag)].Name() = tagMasterMap[Tag(pTag)].Name();

			pTag++;
		}
		offset = *( (DWORD*) pTag );
	} CATCH( CFileException, e ) {
		CString	S;
		S.Format( _T("\nFilename: %s\nTiffTag: %d"), m_pFile->GetFilePath(), Tag( pTag ) );
		lpictdll::ReportFileException( e, S );
	} AND_CATCH( CMemoryException, e ) {
		lpictdll::ReportMemoryException( e );
	}
	END_CATCH

	// ... alles eingelesen; jetzt auswerten ...
	///////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// ... erst mal was ganz prinzipielles ...

	static PICT_PROPERTY needTags[] = {
		PICT_PROP_IMAGEWIDTH				// 256
		, PICT_PROP_IMAGELENGTH			// 257
		, PICT_PROP_COMPRESSION			// 259
		, PICT_PROP_COLORSPACE				// 262
		, (PICT_PROPERTY) 0
	};

	CTagMap::const_iterator tag1, tag2, tag3;		// werden jetzt öfters gebraucht
	TAG	dbgtag;
	long	p1, p2;							// die auch...

	for( int i = 0; needTags[i]; ++i ) {
		if( TAGMAP.end() == TAGMAP.find( needTags[i] ) ) {
			return TagError( CPictException::errMissingInfo, needTags[i], e );
		}
	}

	///////////////////////////////////////////////////////////////////////////
	// Bildbreite / höhe

	tag1 = TAGMAP.find( PICT_PROP_IMAGEWIDTH );
	tag2 = TAGMAP.find( PICT_PROP_IMAGELENGTH );

	dbgtag = (*tag1).second;
	if( PICT_DATA_LONG == (*tag1).second.Type() ) { p1 = (*tag1).second.slVal(); }
	else if( PICT_DATA_SHORT == (*tag1).second.Type() ) { p1 = (long) (*tag1).second.usVal(); }
	else return TagError( CPictException::errDatatype, PICT_PROP_IMAGEWIDTH, e );

	dbgtag = (*tag2).second;
	if( PICT_DATA_LONG == (*tag2).second.Type() ) { p2 = (*tag2).second.slVal(); }
	else if( PICT_DATA_SHORT == (*tag2).second.Type() ) { p2 = (long) (*tag2).second.usVal(); }
	else return TagError( CPictException::errDatatype, PICT_PROP_IMAGELENGTH, e );

	if( p1 <= 0 || p2 <= 0) {
		CString	S;
		S.Format( _T("%ld x %ld"), p1, p2 );
		return TagError( CPictException::errPictSize, S, e );
	}

	SetPictRect( CRect( 0, 0, p1, p2 ) );

	///////////////////////////////////////////////////////////////////////////
	// Striplayout

	if( ( tag1 = TAGMAP.find( PICT_PROP_STRIPOFFSETS ) ) != TAGMAP.end() 
		&& ( tag2 = TAGMAP.find( PICT_PROP_STRIPBYTECOUNTS ) ) != TAGMAP.end() ) {
		///////////////////////////////////////////////////////////////////////////
		// (1) stripped Images
		CTagMap::const_iterator tag3 = TAGMAP.find( PICT_PROP_ROWSPERSTRIP );
		TAG	t = (*tag3).second;
		if( tag3 != TAGMAP.end() ) {
			if( PICT_DATA_SHORT == (*tag3).second.Type() ) { p2 = (long) (*tag3).second.usVal(); }
			else if( PICT_DATA_LONG == (*tag3).second.Type() ) { p2 = (*tag3).second.slVal(); }
			else return TagError( CPictException::errDatatype, PICT_PROP_ROWSPERSTRIP, e );
		}
		if( -1 == p2 )
			p2 = m_rcPicture.Height();
		m_rcStrip.SetRect( 0, 0, p1, p2 );
		if( !ReadStripInfo( (*tag1).second, (*tag2).second, e ) )
			return FALSE;
	} else if( ( tag1 = TAGMAP.find( PICT_PROP_TILEOFFSETS ) ) != TAGMAP.end() 
		&& ( tag2 = TAGMAP.find( PICT_PROP_TILEBYTECOUNTS ) ) != TAGMAP.end() ) {
		///////////////////////////////////////////////////////////////////////////
		// (2) tiled Images
		p1 = p2 = -1;
		tag3 = TAGMAP.find( PICT_PROP_TILEWIDTH );
		if( tag3 != TAGMAP.end() ) {
			if( PICT_DATA_SHORT == (*tag3).second.Type() ) { p1 = (long) (*tag3).second.usVal(); }
			else if( PICT_DATA_LONG == (*tag3).second.Type() ) { p1 = (*tag3).second.slVal(); }
			else return TagError( CPictException::errDatatype, PICT_PROP_TILEWIDTH, e );
		}
		tag3 = TAGMAP.find( PICT_PROP_TILELENGTH );
		if( tag3 != TAGMAP.end() ) {
			if( PICT_DATA_SHORT == (*tag3).second.Type() ) { p2 = (long) (*tag3).second.usVal(); }
			else if( PICT_DATA_LONG == (*tag3).second.Type() ) { p2 = (*tag3).second.slVal(); }
			else return TagError( CPictException::errDatatype, PICT_PROP_TILELENGTH, e );
		}
		if( -1 == p1 || -1 == p2 ) {
			if( e ) {
				CString S;
				S.Format( _T("W x H: %ld x %ld"), p1, p2 );
				e->m_cause = CPictException::errImageLayout;
				e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
				e->m_strCause = S;
				e->m_strPictName = m_pFile->GetFilePath();
			}
			return FALSE;
		}
		m_rcStrip.SetRect( 0, 0, p1, p2 );
		if( !ReadStripInfo( (*tag1).second, (*tag2).second, e ) )
			return FALSE;
	} else {
		///////////////////////////////////////////////////////////////////////////
		// (3) gibt's nicht
		if( e ) {
			CString S;
			e->m_cause = CPictException::errStripInfo;
			e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
			e->m_strCause = "";
			e->m_strPictName = m_pFile->GetFilePath();
		}
		return FALSE;
	}

	m_szStrips.cx = ( m_rcPicture.Width() + m_rcStrip.Width() - 1 ) / m_rcStrip.Width();
	m_szStrips.cy = ( m_rcPicture.Height() + m_rcStrip.Height() - 1 ) / m_rcStrip.Height();

#ifdef NDEBUG
	if( 1 != m_szStrips.cx ) {				// keine Tiled Images in Release
		return TagError( CPictException::errFormat, _T("tiled Image"), e );
	}
#endif

	///////////////////////////////////////////////////////////////////////////
	// Kompression

	tag1 = TAGMAP.find( PICT_PROP_COMPRESSION );
	if( PICT_DATA_SHORT == (*tag1).second.Type() ) { m_compression = (PICT_COMPR) (*tag1).second.usVal(); }
	else if( PICT_DATA_LONG == (*tag1).second.Type() ) { m_compression = (PICT_COMPR) (*tag1).second.slVal(); }
	else return TagError( CPictException::errDatatype, PICT_PROP_COMPRESSION, e );

	if( TRUE == bRet && 0 == m_bitsPerSample ) {		// 's gibt sowas!!!
		switch( m_compression ) {
		case PICT_COMPR_FAXG3:
		case PICT_COMPR_FAXG4:
		case PICT_COMPR_CCITTRLE:
		case PICT_COMPR_CCITTRLEW:
			m_bitsPerSample = 1;
			break;
		case PICT_COMPR_LZW:
			break;
		default:
			if( NULL != e ) {
				e->m_cause = CPictException::errFormat;
				e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
				e->m_strCause = szUnknown;
				e->m_strPictName = m_pFile->GetFilePath();
			}
			bRet = FALSE;
			break;
		}
	}

	ASSERT( NULL == m_pCodec );
	
	if( TRUE == bRet ) {
		CRuntimeClass	*pRTCodec = NULL;
		switch( m_compression ) {
		case PICT_COMPR_NOCOMPR :	break;
		case PICT_COMPR_FAXG4:		pRTCodec = RUNTIME_CLASS( CCodecFaxG4 ); break;
		case PICT_COMPR_PACKBITS:	pRTCodec = RUNTIME_CLASS( CCodecPackBits ); break;
		case PICT_COMPR_LZW:		pRTCodec = RUNTIME_CLASS( CCodecLZWTiff ); break;
		case PICT_COMPR_CCITTRLE:
		case PICT_COMPR_JPEG:
		case PICT_COMPR_FAXG3:		// pRTCodec = RUNTIME_CLASS( CCodecFaxG3 ); break;
		default:
			bRet = FALSE;		// not implemented
			if( NULL != e ) {
				e->m_cause = CPictException::errCompression;
				e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
				e->m_strCause = szUnknown;
				e->m_strPictName = m_pFile->GetFilePath();
			}
			break;
		}
		if( NULL != pRTCodec ) {
			VERIFY( m_pCodec = (CPictCodec*) pRTCodec->CreateObject( ) );
			if( !m_pCodec->Attach( this ) ) {
				if( NULL != e ) {
					e->m_cause = CPictException::errCompression;
					e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
					e->m_strCause = pRTCodec->m_lpszClassName;
					e->m_strPictName = m_pFile->GetFilePath();
				}
				bRet = FALSE;
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////
	// Orientierung

	tag1 = TAGMAP.find( PICT_PROP_ORIENTATION );
	if( PICT_DATA_SHORT == (*tag1).second.Type() ) { m_orientation = (PICT_ORIENT) (*tag1).second.usVal(); }
	else if( PICT_DATA_LONG == (*tag1).second.Type() ) { m_orientation = (PICT_ORIENT) (*tag1).second.slVal(); }
	else return TagError( CPictException::errDatatype, PICT_PROP_ORIENTATION, e );

	switch( m_orientation ) {
	// case PICT_ORIENT_UPPERLEFT :
	// case PICT_ORIENT_LOWERLEFT :
	case PICT_ORIENT_UPPERRIGHT :
	case PICT_ORIENT_LOWERRIGHT :
	case PICT_ORIENT_LEFTUPPER :
	case PICT_ORIENT_RIGHTUPPER :
	case PICT_ORIENT_RIGHTLOWER :
	case PICT_ORIENT_LEFTLOWER :
		if( NULL != e ) {
			e->m_cause = CPictException::errFormat;
			e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
			e->m_strCause = szUnknown;
			e->m_strPictName = m_pFile->GetFilePath();
		}
		bRet = FALSE;
		break;
	}

	////////////////////////////////////////////////////////////////
	// Farbraum

	tag1 = TAGMAP.find( PICT_PROP_COLORSPACE );
	if( PICT_DATA_SHORT == (*tag1).second.Type() ) { m_colorspace = (PICT_COLOR) (*tag1).second.usVal(); }
	else if( PICT_DATA_LONG == (*tag1).second.Type() ) { m_colorspace = (PICT_COLOR) (*tag1).second.slVal(); }
	else return TagError( CPictException::errDatatype, PICT_PROP_COLORSPACE, e );

	if( TRUE == bRet
		&& ( PICT_COLOR_MONOWIZ == m_colorspace || PICT_COLOR_MONOBIZ == m_colorspace ) 
		&& ( 8 == m_bitsPerSample || 4 == m_bitsPerSample ) ) {
		ASSERT( NULL != m_pClut );
		m_nColors = m_nUsedColors = ( 1 << m_bitsPerSample );
		if( PICT_COLOR_MONOWIZ  == m_colorspace ) {
			for( int i = 0; i < m_nColors; i++ ) {
				m_pClut[i].rgbBlue = m_pClut[i].rgbGreen = m_pClut[i].rgbRed = (BYTE) ( ( m_nColors - 1 ) - i );
				m_pClut[i].rgbReserved = (BYTE) 0;
			}
		} else {										// 1 ... Black Is Zero; zugl. default
			for( int i = 0; i < m_nColors; i++ ) {
				m_pClut[i].rgbBlue = m_pClut[i].rgbGreen = m_pClut[i].rgbRed = (BYTE) i;
				m_pClut[i].rgbReserved = (BYTE) 0;
			}
		}
		m_colorspace = PICT_COLOR_PALETTE;
		SetClut( m_pClut, m_nColors );
	} else if( TRUE == bRet
		&& ( PICT_COLOR_MONOWIZ == m_colorspace || PICT_COLOR_MONOBIZ == m_colorspace )
		&& ( 1 == m_bitsPerSample ) ) {
		ASSERT( NULL != m_pClut );
		m_nColors = 2;
		if( PICT_COLOR_MONOWIZ  == m_colorspace ) {
			m_pClut[0].rgbBlue = m_pClut[0].rgbGreen = m_pClut[0].rgbRed = 0xff;
			m_pClut[1].rgbBlue = m_pClut[1].rgbGreen = m_pClut[1].rgbRed = 0x00;
		} else {										// 1 ... Black Is Zero; zugl. default
			m_pClut[0].rgbBlue = m_pClut[0].rgbGreen = m_pClut[0].rgbRed = 0x00;
			m_pClut[1].rgbBlue = m_pClut[1].rgbGreen = m_pClut[1].rgbRed = 0xff;
		}
	} else if( TRUE == bRet 
		&& ( PICT_COLOR_PALETTE == m_colorspace )
		&& ( 8 == m_bitsPerSample || 4 == m_bitsPerSample )
		) {
		ASSERT( NULL != m_pClut );
		tag1 = TAGMAP.find( PICT_PROP_COLORMAP );
		if( tag1 == TAGMAP.end() )
			return TagError( CPictException::errMissingInfo, PICT_PROP_COLORMAP, e );
		long	palBytes = (*tag1).second.Count() * sizeof( short );
		m_nColors = ( 1 << m_bitsPerSample );
		m_nUsedColors = palBytes / ( 3 * sizeof( short ) );
		short *pS = (short*) (*tag1).second.pVal();
		int	i;
		for( i = 0; i < m_nUsedColors; i++ )
			m_pClut[i].rgbRed	= ( ReadShort( *pS++ ) >> 8 );
		for( i = 0; i < m_nUsedColors; i++ )
			m_pClut[i].rgbGreen	= ( ReadShort( *pS++ ) >> 8 );
		for( i = 0; i < m_nUsedColors; i++ )
			m_pClut[i].rgbBlue	= ( ReadShort( *pS++ ) >> 8 );
		for( i = 0; i < m_nUsedColors; i++ )
			m_pClut[i].rgbReserved = (BYTE) 0;
	} else if( TRUE == bRet && ( PICT_COLOR_RGB == m_colorspace && 24 == m_bitsPerSample ) ) {
		ASSERT( NULL != m_pClut );
		m_nColors = 0;
	} else {
		bRet = FALSE;
		if( NULL != e ) {
			e->m_cause = CPictException::errColorSpace;
			e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
			e->m_strCause = szUnknown;
			e->m_strPictName = m_pFile->GetFilePath();
		}
	}

	////////////////////////////////////////////////////////////////
	// nochmal alles überprüfen, was wir so können
//return bRet;
//#if defined(NDEBUG) || defined(_RDEBUG)
//	switch(m_compression) { 
//	case PICT_COMPR_NOCOMPR :
//	case PICT_COMPR_FAXG4:
//	case PICT_COMPR_PACKBITS:
//		break;
//	default:
//		bRet = FALSE;
//	}
//	switch( m_orientation ) {
//	case PICT_ORIENT_UPPERLEFT :
//	case PICT_ORIENT_LOWERLEFT :
//		break;
//	default:
//		bRet = FALSE;
//	}
//	switch(m_colorspace) {
//	case PICT_COLOR_PALETTE :
//	case PICT_COLOR_MONOWIZ :
//	case PICT_COLOR_MONOBIZ :
//	case PICT_COLOR_RGB :
//		break;
//	default:
//		bRet = FALSE;
//	}
//	if( m_szStrips.cx > 1 || m_szStrips.cy > 1 ) {
//		bRet = FALSE;
//	}
//#endif
	return bRet;
}

BOOL CTifPicture::SelectSubFile( int nFile ) {
	return 0 == nFile ? TRUE : FALSE;
}

BOOL CTifPicture::ReadStripInfo( const TAG& rTO, const TAG& rTS, CPictException *e /*= NULL */ ) {
	if( rTO.Count() != rTS.Count() ) {
		if( NULL != e ) {
			CString S;
			S.Format( _T("Size mismatch: %d,%d %d,%d"), rTO.Num(), rTO.Count(), rTS.Num(), rTS.Count() );
			e->m_cause = CPictException::errInvalidInfo;
			e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
			e->m_strCause = S;
			e->m_strPictName = m_pFile->GetFilePath();
		}
		return FALSE;
	}
	DeleteStripInfo( );
	long nStrips = rTO.Count();

	TRY {
		m_pStripInfo = new STRIPINFO[ nStrips ];
	} CATCH( CMemoryException, e ) {
		DELETE_EXCEPTION( e );
		::AfxThrowMemoryException();
	} END_CATCH

	memset( m_pStripInfo, 0x00, (UINT) nStrips * sizeof( STRIPINFO ) );
	if( 1 == rTO.Count() ) {
		m_pStripInfo[0].stripOffset = rTO.slVal();
		m_pStripInfo[0].stripSize = rTS.slVal();
		return TRUE;
	}

	long	i;
	if( PICT_DATA_PSHORT == rTO.Type() ) {
		HPWORD p = (HPWORD) rTO.pVal();
		for( i = 0; i < (long) nStrips; i++ ) {
			m_pStripInfo[i].stripOffset = (DWORD) ReadShort( p[i] );
		}
	} else if( PICT_DATA_PLONG == rTO.Type() ) {
		HPDWORD p = (HPDWORD) rTO.pVal();
		for( i = 0; i < (long) nStrips; i++ ) {
			m_pStripInfo[i].stripOffset = ReadLong( p[i] );
		}
	} else {
		return TagError( CPictException::errDatatype, rTO.Num(), e );
	}
	if( PICT_DATA_PSHORT == rTS.Type() ) {
		HPWORD p = (HPWORD) rTS.pVal();
		for( i = 0; i < (long) nStrips; i++ ) {
			m_pStripInfo[i].stripSize = (DWORD) ReadShort( p[i] );
		}
	} else if( PICT_DATA_PLONG == rTS.Type() ) {
		HPDWORD p = (HPDWORD) rTS.pVal();
		for( i = 0; i < (long) nStrips; i++ ) {
			m_pStripInfo[i].stripSize = ReadLong( p[ i ] );
		}
	} else {
		return TagError( CPictException::errDatatype, rTS.Num(), e );
	}
	return TRUE;
}

long	CTifPicture::GetImageBytes( const CRect& rcSrc, HPBYTE lpBuf ) {
	CMemBlock	*pTmp = m_pMemBlock;
	CRect	rcTmp = m_rcPictInCore;

	DWORD	nBytes = ( ( rcSrc.Width() * m_bitsPerSample ) / 8 ) * rcSrc.Height();
	m_pMemBlock = new CMemBlock( nBytes + 1 );

	if( Read( rcSrc ) )
		memcpy( (void*) lpBuf, (void*) *(m_pMemBlock), nBytes );
	else
		nBytes = 0;
	delete m_pMemBlock;

	m_pMemBlock = pTmp;
	m_rcPictInCore = rcTmp;

	return nBytes;
}

long	CTifPicture::SetImageBytes( const CRect& rcDst, HPBYTE lpBuf ) {
	long	stripNo;
	long	stripOffset;
	long	lineNumberInStrip;
	long	rowsPerStrip = m_rcStrip.Height();

	long	nLines = (DWORD) rcDst.Height();
	long	startLine = rcDst.top;
	long	startCol = rcDst.left;
	int		nBytes = rcDst.Width() * rcDst.Height();
	HPBYTE	pSrcData = lpBuf + ( nLines * rcDst.Width() );

	TRY {
		while( nLines > 0 ) {
			lineNumberInStrip = startLine % rowsPerStrip;

			stripNo = startLine / rowsPerStrip;
			stripOffset = m_pStripInfo[ stripNo ].stripOffset;
			stripOffset += lineNumberInStrip * m_rcImage.Width() + startCol;

			m_pFile->Seek( stripOffset, CFile::begin );

			for( ; lineNumberInStrip < rowsPerStrip && nLines; lineNumberInStrip++ ) {
				pSrcData -= rcDst.Width();
				m_pFile->Write( (void FAR*) pSrcData, rcDst.Width() );
				m_pFile->Seek( m_rcImage.Width() - rcDst.Width(), CFile::current );
				nLines--;
				startLine++;
			}
		}
	} CATCH( CFileException, e ); {
	} END_CATCH

	return nBytes;
}

#include	<strstrea.h>
#ifndef	WIN32
#pragma	function( _fmemcpy )
#endif

long CTifPicture::AlignTop( long line ) {
	long stripNo = line / m_rcStrip.Height();
	line = stripNo * m_rcStrip.Height();
	return line;
}

long CTifPicture::FillBuffer( long line, long startRestBytes, long nRestBytes ) {
	long	stripNo = line / m_rcStrip.Height();
	long	bufSize = min( (long) m_pTmpBlock->Size(), m_pStripInfo[ stripNo ].stripSize );
	long	nRead = 0;

//	long	ix;	// KK000713

	if( !m_pTmpBlock->CheckRange( *m_pTmpBlock, nRestBytes ) )
		LAfxThrowPictMemException( m_pTmpBlock, *m_pTmpBlock, nRestBytes, GetRuntimeClass()->m_lpszClassName, m_pFile->GetFilePath() );
	if( 0 != nRestBytes )
		memcpy( (void FAR*) *m_pTmpBlock, (void FAR*) (*m_pTmpBlock + startRestBytes), nRestBytes );
	bufSize -= nRestBytes;
	TRY {
		m_pFile->Seek( m_pStripInfo[stripNo].stripOffset + nRestBytes, CFile::begin );
		nRead = m_pFile->ReadHuge( (void FAR*) *(m_pTmpBlock + startRestBytes), bufSize );
	} CATCH( CFileException, e ) {
		DELETE_EXCEPTION( e );
		nRead = 0;
	} END_CATCH


/* --- KK000713
	if( PICT_FILLORD_ZEROISZERO == GetFillOrder() ) {	//#fje+
		for( ix = 0; ix < nRead; ix++  )
			*(*m_pTmpBlock + ix) = FlipBYTE(*(*m_pTmpBlock + ix));
	}

	if( PICT_COLOR_MONOBIZ == GetColorspace() ) {	//#fje+
		for( ix = 0; ix < nRead; ix++  )
			*(*m_pTmpBlock + ix) = ~(*(*m_pTmpBlock + ix));
	}
//*/

	return nRead;
}

long CTifPicture::StoreScanLine( HPBYTE pLine, long line, const CRect& rcCore ) {
	HPBYTE	pSrcLine = pLine;
	HPBYTE	pDstData;

//	long ix; // Frank

	long nBytes = m_rcImageInCore.Width();

	long	offset;
	switch( m_orientation ) {
	case PICT_ORIENT_LOWERLEFT :
		offset = line - m_rcImageInCore.top;
		break;
	case PICT_ORIENT_UPPERLEFT :
		offset = m_rcImageInCore.bottom - line - 1;
		break;
	default: {
			CPictCrack	C;
			LAfxThrowPictException( 
				CPictException::errOrientation,
				GetRuntimeClass()->m_lpszClassName,
				C.Crack( PICT_PROP_ORIENTATION, m_orientation ),
				m_pFile->GetFilePath()
				);
		}
		return 0;
	}

	pDstData = *m_pMemBlock + nBytes * ( offset );

	if( !m_pMemBlock->CheckRange( pDstData, nBytes ) )
		LAfxThrowPictMemException( m_pMemBlock, pDstData, nBytes, GetRuntimeClass()->m_lpszClassName, m_pFile->GetFilePath() );

	if( 24 == m_bitsPerSample ) {
		long col = m_rcImageInCore.left;
		long nCols = m_rcImageInCore.Width();
		while( col < nCols ) {
			pDstData[col] = pSrcLine[col+2];
			pDstData[col+1] = pSrcLine[col+1];
			pDstData[col+2] = pSrcLine[col];
			col += 3;
		}
	} else if( 8 == m_bitsPerSample ) {
		memcpy( (void FAR*) pDstData, (void FAR*) (pSrcLine + m_rcImageInCore.left), nBytes );
	} else if( 4 == m_bitsPerSample ) {
		memcpy( (void FAR*) pDstData, (void FAR*) (pSrcLine + m_rcImageInCore.left), nBytes );
	} else if( 1 == m_bitsPerSample ) {


// KK000622
// Frank raus
/*--
		if( PICT_FILLORD_ZEROISZERO != GetFillOrder() ) {	//#fje+
			if( PICT_COLOR_MONOBIZ != GetColorspace() ) {	//#fje+
				for( ix = 0; ix < nBytes; ix++  )
					*(pDstData + ix) = FlipBYTE(*(pSrcLine + m_rcImageInCore.left + ix));
			}
			else {
				for( ix = 0; ix < nBytes; ix++  )
					*(pDstData + ix) = ~FlipBYTE(*(pSrcLine + m_rcImageInCore.left + ix));
			}	
		}
		else {
			if( PICT_COLOR_MONOBIZ == GetColorspace() ) {	//#fje+
				for( ix = 0; ix < nBytes; ix++  )
					*(pDstData + ix) = ~(*(pSrcLine + m_rcImageInCore.left + ix));
			}
			else
*/

				memcpy( (void FAR*) pDstData, (void FAR*) (pSrcLine + m_rcImageInCore.left), nBytes );
//		}	//KK000626

	} else {
		ASSERT(FALSE);
	}
	return nBytes;
}

BOOL CTifPicture::ReadRaw( const CRect& rcSrc ) {
	ASSERT_VALID( m_pFile );

	long	nLines = rcSrc.Height();
	HPBYTE	pSrcData, pDstData;

	long	rowsPerStrip = m_rcStrip.Height();
	long	lineNumberInStrip, linesRead, linesWritten;
	long	stripNo, stripOffset, stripSize;
	long	srcLine = 0			// der gelesene Strip...
			, srcOffs = 0
			, srcWidth = 0
			;
	long	dstLine = 0			// der Bildspeicher
			, dstOffs = 0
			, dstIncr = 0
			, dstWidth = 0
			;

	long	bufSize;
// KK010312 - Frank raus
//	long	ix;

	/////////////////////////////////////////////////////////////////////////////
	// für Anpassen der Farbebenen bei 24-bit 
	HPBYTE	pSrcPixel, pDstPixel;
	int		nCols = m_rcPictInCore.Width();
	int		col;

	srcWidth = m_rcImage.Width();
	dstWidth = m_rcImageInCore.Width();

	switch( m_orientation ) {
	case PICT_ORIENT_LOWERLEFT :
		srcLine = m_rcPicture.bottom - rcSrc.bottom; // rcSrc.top;
		srcOffs = m_rcImageInCore.left;
		dstIncr = m_rcImageInCore.Width();
		dstOffs = 0;
		break;
	case PICT_ORIENT_UPPERLEFT :
		srcLine = rcSrc.top; // m_rcPicture.bottom - rcSrc.bottom;
		srcOffs = m_rcImageInCore.left;
		dstIncr = -m_rcImageInCore.Width();
		dstOffs = ( rcSrc.Height() - 1 ) * m_rcImageInCore.Width();
		break;
	default:
		return FALSE;
	}

	pDstData = (HPBYTE) *m_pMemBlock;
	pDstData += dstOffs;

	TRY {
		while( nLines > 0 ) {
			//////////////////////////////////////////////////////////////////////////////////
			// zunächst mal versuchen, soviel wie möglich aus dem gewünschten Strip zu lesen

			stripNo = srcLine / rowsPerStrip;
			lineNumberInStrip = srcLine % rowsPerStrip;
			stripOffset = m_pStripInfo[ stripNo ].stripOffset + lineNumberInStrip * srcWidth;
			stripSize = m_pStripInfo[ stripNo ].stripSize;
			if( 0 == stripSize )		// CPictException...
				break;
			bufSize = nLines * srcWidth;
			bufSize = min( bufSize, stripSize );
			bufSize = min( bufSize, (long) m_pTmpBlock->Size() );
			bufSize /= srcWidth;
			bufSize *= srcWidth;
			m_pFile->Seek( stripOffset, CFile::begin );
			if( bufSize != ( linesRead = m_pFile->Read( (void FAR*) *m_pTmpBlock, (UINT) bufSize ) ) )
				break;
			linesRead /= srcWidth;
			pSrcData = (HPBYTE) *m_pTmpBlock;
			pSrcData += srcOffs;

			//////////////////////////////////////////////////////////////////////////////////
			// Daten in den Bildpuffer übertragen

			for( linesWritten = 0; linesWritten < linesRead && lineNumberInStrip < rowsPerStrip && nLines > 0; ) {
				if( !m_pTmpBlock->CheckRange( pSrcData, srcWidth - srcOffs ) )
					LAfxThrowPictMemException( m_pTmpBlock, pSrcData, srcWidth - srcOffs, GetRuntimeClass()->m_lpszClassName, m_pFile->GetFilePath() );
				if( !m_pMemBlock->CheckRange( pDstData, dstWidth - 1 ) )
					LAfxThrowPictMemException( m_pMemBlock, pDstData, dstWidth - 1, GetRuntimeClass()->m_lpszClassName, m_pFile->GetFilePath() );

				if( 24 == m_bitsPerSample ) {
					pSrcPixel = pSrcData;
					pDstPixel = pDstData;
					for( col = 0; col < nCols; col++ ) {
						*(pDstPixel) = *(pSrcPixel+2);
						*(pDstPixel+1) = *(pSrcPixel+1);
						*(pDstPixel+2) = *(pSrcPixel);
						pSrcPixel += 3;
						pDstPixel += 3;
					}
				} else {

	/*- KK010312--Frank raus
					if( PICT_FILLORD_ZEROISZERO == GetFillOrder() ) {
						if( PICT_COLOR_MONOBIZ == GetColorspace() ) {	//#fje+
							for( ix = 0; ix < dstWidth; ix++  )
								*(pDstData + ix) = ~FlipBYTE(*(pSrcData + ix));
						}
						else {
							for( ix = 0; ix < dstWidth; ix++  )
								*(pDstData + ix) = FlipBYTE(*(pSrcData + ix));
						}
					}
					else
						if( PICT_COLOR_MONOBIZ == GetColorspace() ) {	//#fje+
							for( ix = 0; ix < dstWidth; ix++  )
								*(pDstData + ix) = ~(*(pSrcData + ix));
						}
						else
	--------------------------------*/
							memcpy( (void*) pDstData, (void*) pSrcData, dstWidth );
				}
				pDstData += dstIncr;
				pSrcData += srcWidth;
				++linesWritten;
				++lineNumberInStrip;
				srcLine++;
				nLines--;
			}
		}
	} CATCH( CFileException, e ) {
		DELETE_EXCEPTION( e );
		return FALSE;
	} END_CATCH

	return TRUE;
}

BOOL CTifPicture::Write( const CRect& rcBand, PICT_ORIENT srcOrient /* = PICT_ORIENT_UPPERLEFT */ ) {
	ASSERT_VALID( m_pFile );

	long	nLines = rcBand.Height();
	long	stripNo, stripLine;
	long	dstData;
	long	srcLine = 0			// der Bildspeicher
			, srcIncr = 0
			, srcWidth = 0
			;
	long	dstLine = 0			// der gelesene Strip...
			, dstOffs = 0
			, dstLineIncr = 0
			, dstWidth = 0
			;

	CRect	_rcBand, rcStrip;
	_rcBand.IntersectRect( rcBand, m_rcPictInCore );

	srcWidth = m_rcImageInCore.Width();
	dstWidth = m_rcImage.Width();

	switch( m_orientation ) {
	case PICT_ORIENT_LOWERLEFT : {
			LAfxThrowPictException(CPictException::errOrientation, GetRuntimeClass()->m_lpszClassName );
//			srcLine = m_rcPictInCore.bottom - _rcBand.top - _rcBand.Height();
//			srcIncr = srcWidth;
//			dstLine = _rcBand.bottom - 1; // - _rcBand.Height();
//			dstLineIncr = -1;
		}
		break;
	case PICT_ORIENT_UPPERLEFT : {
			srcLine = m_rcPictInCore.bottom - _rcBand.top - _rcBand.Height();
			srcIncr = srcWidth;
			dstLine = _rcBand.bottom - 1; // - _rcBand.Height();
			dstLineIncr = -1;
		}
		break;
	default:
		return FALSE;
	}

	HPBYTE	pSrcData = 	*m_pMemBlock;
	pSrcData += srcLine * srcWidth;

	long	rowsPerStrip = m_rcStrip.Height();

	for( nLines = _rcBand.Height(); nLines; --nLines ) {
		stripNo = dstLine / rowsPerStrip;
		stripLine = dstLine % rowsPerStrip;
		dstData = m_pStripInfo[ stripNo ].stripOffset + stripLine * dstWidth;

		if( 24 == m_bitsPerSample ) {
		HPBYTE pSrcPixel = pSrcData;
		int nCols = m_rcPictInCore.Width();

			for(int col = 0; col < nCols; ++col) {
			BYTE bT = *(pSrcPixel);

				*(pSrcPixel) = *(pSrcPixel+2);
				*(pSrcPixel+2) = bT;
				pSrcPixel += 3;
			}
		} 

		m_pFile->Seek( dstData, CFile::begin );
		m_pFile->Write( (void*) pSrcData, dstWidth );

		pSrcData += srcWidth;
		dstLine += dstLineIncr;
		++srcLine;
	}
	return TRUE;
}

static const long g_optStripSize = 16 * 1024;	// 16 K

BOOL CTifPicture::WriteHeader( ) {
	ASSERT( NULL != m_pFile );
	ASSERT_VALID( m_pFile );

	SetPictRect( m_rcPicture );

	m_tifHeader.wByteOrder = BYTEORDER_II;
	m_tifHeader.wIdentifier = 42;
	m_tifHeader.dwIFD = sizeof( TIFHEADER ) + m_rcImage.Width() * m_rcImage.Height();
	m_tifHeader.dwIFD = ( ( m_tifHeader.dwIFD + 1 ) / sizeof( WORD ) ) * sizeof( WORD );

	////////////////////////////////////////////////////////////////////
	// Striplayout berechnen

	m_rcStrip.left = m_rcStrip.top = 0;
	m_rcStrip.right = m_rcPicture.right;
	m_rcStrip.bottom = ( m_rcImage.Width() + g_optStripSize - 1 ) / m_rcImage.Width();
	if( 0 == m_rcStrip.bottom )			// mindestens eine Zeile...
		m_rcStrip.bottom = 1;
	m_rcStrip.bottom = min( m_rcStrip.bottom, m_rcPicture.bottom );

//	m_rcStrip.bottom = m_rcPicture.Height();

	m_szStrips.cx = TIFFhowmany( m_rcPicture.Width(), m_rcStrip.Width() );
	m_szStrips.cy = TIFFhowmany( m_rcPicture.Height(), m_rcStrip.Height() );

	TAGMAP[PICT_PROP_ROWSPERSTRIP] = TAG( PICT_PROP_ROWSPERSTRIP, (WORD) m_rcStrip.Height() );

	ULONG dwStrips = m_szStrips.cx * m_szStrips.cy;

	if( NULL != m_pStripInfo )
		DeleteStripInfo( );

	m_pStripInfo = (STRIPINFO*) new char[ dwStrips * sizeof( STRIPINFO ) ];
	memset( (void FAR*) m_pStripInfo, 0x00, (UINT) dwStrips * sizeof( STRIPINFO ) );

	int	nStrip;
	long stripSize = m_rcImage.Width() * m_rcStrip.Height();
	if( 1 == dwStrips ) {
		TAGMAP[PICT_PROP_STRIPOFFSETS] = TAG( PICT_PROP_STRIPOFFSETS, (ULONG) sizeof( TIFHEADER ) );
		TAGMAP[PICT_PROP_STRIPBYTECOUNTS] = TAG( PICT_PROP_STRIPBYTECOUNTS, (ULONG) stripSize );
		m_pStripInfo[0].stripOffset = sizeof( TIFHEADER );
		m_pStripInfo[0].stripSize = stripSize;
	} else {
		TAGMAP[PICT_PROP_STRIPOFFSETS] = TAG( PICT_PROP_STRIPOFFSETS, dwStrips, dwStrips, (void*) m_pStripInfo );
		TAGMAP[PICT_PROP_STRIPBYTECOUNTS] = TAG( PICT_PROP_STRIPBYTECOUNTS, dwStrips, dwStrips, (void*) m_pStripInfo );
		LPDWORD	pOffsets = (LPDWORD) TAGMAP[PICT_PROP_STRIPOFFSETS].pVal();
		LPDWORD	pSizes = (LPDWORD) TAGMAP[PICT_PROP_STRIPBYTECOUNTS].pVal();
		for( nStrip = 0; nStrip < m_szStrips.cy - 1; ++nStrip ) {
			pOffsets[nStrip] = m_pStripInfo[nStrip].stripOffset = sizeof( TIFHEADER ) + nStrip * stripSize;
			pSizes[nStrip] = m_pStripInfo[nStrip].stripSize = stripSize;
			m_pStripInfo[nStrip].stripOffset = sizeof( TIFHEADER ) + nStrip * stripSize;
			m_pStripInfo[nStrip].stripSize = stripSize;
		}
		pOffsets[nStrip] = m_pStripInfo[nStrip].stripOffset = sizeof( TIFHEADER ) + nStrip * stripSize;
		m_pStripInfo[nStrip].stripOffset = sizeof( TIFHEADER ) + nStrip * stripSize;
		if( 0 == ( m_rcImage.Width() * m_rcImage.Height() ) % stripSize )
			m_pStripInfo[nStrip].stripSize = stripSize;
		else
			m_pStripInfo[nStrip].stripSize = ( m_rcImage.Width() * m_rcImage.Height() ) % stripSize;
		pSizes[nStrip] = m_pStripInfo[nStrip].stripSize;
	}
	return TRUE;
}

BOOL CTifPicture::WriteTrailer( ) {
	ASSERT( NULL != m_pFile );
	ASSERT_VALID( m_pFile );
	long	nTags = TAGMAP.size();
	long	nTagSpace = sizeof( WORD ) + nTags * sizeof( FILETAG ) + sizeof( DWORD );
	long	nExtraSpace = 0;

	CTagMap::const_iterator i;
	for( i = TAGMAP.begin(); i != TAGMAP.end(); ++i ) {
		if( PICT_PROP_XRESOLUTION == (*i).first || PICT_PROP_YRESOLUTION == (*i).first )
			nExtraSpace += sizeof( URATIO );
		else {
			if( TAGMAP[(*i).first].Space() > 4 ) {
				nExtraSpace += TAGMAP[(*i).first].Space();
			}
		}
	}

	LPFILETAG	pTags = (LPFILETAG) new BYTE[ nTagSpace ];
	LPFILETAG	pTag = (LPFILETAG) ( (WORD*) pTags + 1 );
	HPBYTE pExtraBytes = new BYTE[ nExtraSpace ];
	HPBYTE pExtra = pExtraBytes;

	memset( (void*) pTags, 0x00, nTagSpace );
	memset( (void*) pExtraBytes, 0x00, nExtraSpace );

	*(WORD*) pTags = (WORD) nTags;
	long	extraOffset = m_tifHeader.dwIFD + nTagSpace;

	for( i = TAGMAP.begin(); i != TAGMAP.end(); ++i ) {
		ASSERT( (*i).first < USHRT_MAX );
		pTag->wTag = (WORD) (*i).first;
		pTag->wType = (*i).second.Type() % 100;
		pTag->dwCount = (*i).second.Count();
		if( PICT_PROP_XRESOLUTION == pTag->wTag || PICT_PROP_YRESOLUTION == pTag->wTag ) {
			URATIO	r;
			if( PICT_DATA_DOUBLE == (*i).second.Type() ) {
				dbl2ratio( (*i).second.dVal(), r.num, r.denom );
			} else if( PICT_DATA_FLOAT == (*i).second.Type() ) {
				dbl2ratio( (double) (*i).second.dVal(), r.num, r.denom );
			} else if( PICT_DATA_SRATIONAL == (*i).second.Type() ) {
				SRATIO	s = (*i).second.srVal();
				r.num = (ULONG) s.num;
				r.denom = (ULONG) s.denom;
			} else if( PICT_DATA_RATIONAL == (*i).second.Type() ) {
				r = (*i).second.urVal();
			} else {
				delete[] pTags;
				delete[] pExtraBytes;
				LAfxThrowPictException(CPictException::errDatatype, GetRuntimeClass()->m_lpszClassName );
			}
			memcpy( (void*) pExtra, (void*) &r, sizeof( URATIO ) );
			pTag->wType = PICT_DATA_RATIONAL;
			pTag->dwCount = 1;
			pTag->dwValue = extraOffset;
			pExtra += sizeof(URATIO);
			extraOffset += sizeof(URATIO);
		} else if( 1 == pTag->dwCount ) {
			switch( pTag->wType ) {
			case PICT_DATA_BYTE		: pTag->dwValue = (DWORD) (*i).second.ubVal(); break;
			case PICT_DATA_SHORT	: pTag->dwValue = (DWORD) (*i).second.usVal(); break;
			case PICT_DATA_LONG		: pTag->dwValue = (DWORD) (*i).second.ulVal(); break;

			case PICT_DATA_SBYTE	: pTag->dwValue = (DWORD) (*i).second.sbVal(); break;
			case PICT_DATA_SSHORT	: pTag->dwValue = (DWORD) (*i).second.ssVal(); break;
			case PICT_DATA_SLONG	: pTag->dwValue = (DWORD) (*i).second.slVal(); break;
			}
		} else {
			if( TAGMAP[(*i).first].Space() > 4 ) {
				memcpy( (void*) pExtra, (*i).second.pVal(), (*i).second.Space() );
				pTag->dwValue = extraOffset;
				pExtra += (*i).second.Space();
				extraOffset += (*i).second.Space();
			} else {
				memcpy( &pTag->dwValue, (*i).second.pVal(), (*i).second.Space() );
			}
		}
		++pTag;
	}
	*((DWORD*)pTag) = 0L;

	TRY {
		m_pFile->Seek( m_tifHeader.dwIFD, CFile::begin );
		m_pFile->Write( (void*) pTags, nTagSpace );
		m_pFile->Write( (void*) pExtraBytes, nExtraSpace );

		m_pFile->SeekToBegin();
		m_pFile->Write( (void*) &m_tifHeader, sizeof( TIFHEADER ) );
	} CATCH( CFileException, e ) {
#ifdef _DEBUG
		lpictdll::ReportFileException( e );
#endif
		DELETE_EXCEPTION( e );
	}
	END_CATCH

	delete[] pTags;
	delete[] pExtraBytes;
	return TRUE;
}

void CTifPicture::Serialize( CArchive& ar )
	{ CPictureBase::Serialize( ar ); }
