#ifdef _AFX_INLINE

_AFX_INLINE	BOOL CMemBlock::IsValid( )
	{ return m_hMem != NULL; }

_AFX_INLINE	long CMemBlock::Size( )
	{ return m_lBlockSize; }

_AFX_INLINE	HPBYTE	CMemBlock::Lock( )
	{
		if( FALSE == m_bIsLocked )
		{
			m_bIsLocked = (NULL != (m_pData = (HPBYTE) ::GlobalLock( m_hMem ) ) );
		}
		return m_pData;
	}
_AFX_INLINE CMemBlock::operator HPBYTE()
	{ return Lock( ); }

_AFX_INLINE	void	CMemBlock::UnLock( )
	{ if( TRUE == m_bIsLocked ) { ::GlobalUnlock( m_hMem ); m_bIsLocked = FALSE; m_pData = NULL; } }
_AFX_INLINE	void	CMemBlock::SetBlockName( LPCTSTR lpszBlockName )
	{ ASSERT_POINTER( lpszBlockName, LPCTSTR ); m_strBlockName = lpszBlockName; }
_AFX_INLINE	CString CMemBlock::GetBlockName()
	{ return m_strBlockName; }
_AFX_INLINE	void CMemBlock::CacheHit( BOOL bHit /*=TRUE*/)
	{ m_nCacheHits = TRUE == bHit ? 0 : m_nCacheHits + 1; }

_AFX_INLINE	BOOL CMemBlock::CheckPointer( HPBYTE p )
{
#ifdef _DEBUG
	if( m_pData && ( p >= m_pData ) && ( p < m_pData + m_lBlockSize ) )
		return TRUE;
	else
		_asm { int 3 };
	return FALSE;
#else
	return m_pData && ( p >= m_pData ) && ( p < m_pData + m_lBlockSize ) ;
#endif
}

_AFX_INLINE	BOOL CMemBlock::CheckRange( HPBYTE p1, HPBYTE p2 )
{
	return CheckPointer( p1 ) && CheckPointer( p2 );
}

_AFX_INLINE	BOOL CMemBlock::CheckRange( HPBYTE p, long size )
{
	return CheckPointer( p ) && CheckPointer( p + size );
}

//////////////////////////////////////////////////////////////////////////////
// CPicture

_AFX_INLINE void TAG::Init()
	{ memset( (void*) &m_tv, 0x00, sizeof( m_tv ) ); m_tv.m_tt = PICT_DATA_UNKNOWN; }

_AFX_INLINE TAG::TAG()
	{ Init(); }
_AFX_INLINE TAG::~TAG()
	{ if( m_tv.m_extraSpace > 0 && PICT_DATA_RATIONAL != m_tv.m_tt && PICT_DATA_SRATIONAL != m_tv.m_tt ) delete[] m_tv.m_pVal; }

_AFX_INLINE const long TAG::operator*()
	{ return m_tt; }
_AFX_INLINE PICT_PROPERTY TAG::Num() const
	{ return m_tt; }

_AFX_INLINE TAG::TAG( PICT_PROPERTY t, BYTE v, int count /*= 1*/, void* pData /*= NULL*/ )
	{ Init(); m_tt = t; m_tv.m_tt = PICT_DATA_BYTE; m_tv.m_count = count; if( 1 == count ) m_tv.m_ubVal = v; else ReadArray( sizeof( BYTE ), count, pData ); }
_AFX_INLINE TAG::TAG( PICT_PROPERTY t, WORD v, int count /*= 1*/, void* pData /*= NULL*/ )
	{ Init(); m_tt = t; m_tv.m_tt = PICT_DATA_SHORT; m_tv.m_count = count; if( 1 == count ) m_tv.m_usVal = v; else ReadArray( sizeof( WORD ), count, pData ); }
_AFX_INLINE TAG::TAG( PICT_PROPERTY t, ULONG v, int count /*= 1*/, void* pData /*= NULL*/ )
	{ Init(); m_tt = t; m_tv.m_tt = PICT_DATA_LONG; m_tv.m_count = count; if( 1 == count ) m_tv.m_ulVal = v; else ReadArray( sizeof( ULONG ), count, pData ); }
_AFX_INLINE TAG::TAG( PICT_PROPERTY t, ULONG num, ULONG denom )
	{ Init(); m_tt = t; m_tv.m_tt = PICT_DATA_RATIONAL; m_tv.m_count = 1; m_tv.m_urVal.num = num; m_tv.m_urVal.denom = denom; m_tv.m_extraSpace = 2 * sizeof( ULONG ); }
_AFX_INLINE TAG::TAG( PICT_PROPERTY t, LPCTSTR v, int count )
	{ Init(); m_tt = t; m_tv.m_count = count; ReadArray( sizeof( char ), count, (void*) v ); m_tv.m_tt = PICT_DATA_ASCII; }		// '\0' mitzählen!

_AFX_INLINE TAG::TAG( PICT_PROPERTY t, char v, int count /*= 1*/, void* pData /*= NULL*/ )
	{ Init(); m_tt = t; m_tv.m_tt = PICT_DATA_SBYTE; m_tv.m_count = count; if( 1 == count ) m_tv.m_sbVal = v; else ReadArray( sizeof( char ), count, pData ); }
_AFX_INLINE TAG::TAG( PICT_PROPERTY t, short v, int count /*= 1*/, void* pData /*= NULL*/ )
	{ Init(); m_tt = t; m_tv.m_tt = PICT_DATA_SSHORT; m_tv.m_count = count; if( 1 == count ) m_tv.m_ssVal = v; else ReadArray( sizeof( short ), count, pData ); }
_AFX_INLINE TAG::TAG( PICT_PROPERTY t, long v, int count /*= 1*/, void* pData /*= NULL*/ )
	{ Init(); m_tt = t; m_tv.m_tt = PICT_DATA_SLONG; m_tv.m_count = count; if( 1 == count ) m_tv.m_slVal = v; else ReadArray( sizeof( long ), count, pData ); }
_AFX_INLINE TAG::TAG( PICT_PROPERTY t, long num, long denom )
	{ Init(); m_tt = t; m_tv.m_tt = PICT_DATA_SRATIONAL;  m_tv.m_count = 1; m_tv.m_srVal.num = num; m_tv.m_srVal.denom = denom; m_tv.m_extraSpace = 2 * sizeof( long ); }
_AFX_INLINE TAG::TAG( PICT_PROPERTY t, double v, int count /*= 1*/, void* pData /*= NULL*/ )
	{ Init(); m_tt = t; m_tv.m_tt = PICT_DATA_DOUBLE; m_tv.m_count = count; if( 1 == count ) m_tv.m_dVal = v; else ReadArray( sizeof( double ), count, pData ); }
_AFX_INLINE TAG::TAG( PICT_PROPERTY t, float v, int count /*= 1*/, void* pData /*= NULL*/ )
	{ Init(); m_tt = t; m_tv.m_tt = PICT_DATA_FLOAT; m_tv.m_count = count; if( 1 == count ) m_tv.m_fVal = v; else ReadArray( sizeof( float ), count, pData ); }

_AFX_INLINE void* TAG::pVal() const
	{ return m_tv.m_pVal; }

_AFX_INLINE PICT_DATATYPE TAG::Type() const
	{ return m_tv.m_tt; }
_AFX_INLINE long TAG::Space( ) const
	{ return m_tv.m_extraSpace; }
_AFX_INLINE long TAG::Count() const
	{ return m_tv.m_count; }
_AFX_INLINE CString& TAG::Name()
	{ return m_strName; }
_AFX_INLINE LPCTSTR TAG::Name() const
	{ return (LPCTSTR) m_strName; }

_AFX_INLINE BYTE TAG::ubVal() const
	{ return m_tv.m_ubVal; }
_AFX_INLINE WORD TAG::usVal() const
	{ return m_tv.m_usVal; }
_AFX_INLINE ULONG TAG::ulVal() const
	{ return m_tv.m_ulVal; } 
_AFX_INLINE URATIO TAG::urVal() const
	{ return m_tv.m_urVal; }
_AFX_INLINE LPCTSTR TAG::strVal() const
	{ return (LPCTSTR) m_tv.m_pVal; }

_AFX_INLINE char TAG::sbVal() const
	{ return m_tv.m_sbVal; }
_AFX_INLINE short TAG::ssVal() const
	{ return m_tv.m_ssVal; }
_AFX_INLINE long TAG::slVal() const
	{ return m_tv.m_slVal; } 
_AFX_INLINE SRATIO TAG::srVal() const
	{ return m_tv.m_srVal; }
_AFX_INLINE float TAG::fVal() const
	{ return m_tv.m_fVal; }
_AFX_INLINE double TAG::dVal() const
	{ return m_tv.m_dVal; }

//////////////////////////////////////////////////////////////////////////////
// CPicture
//////////////////////////////////////////////////////////////////////////////

_AFX_INLINE const CString CPicture::GetPictName()
	{ return m_strPictName; }
_AFX_INLINE BOOL CPicture::SetPictName( LPCTSTR lpszPictName )
	{ m_strPictName = lpszPictName; return TRUE; }
_AFX_INLINE	const CString CPicture::GetFileName()
	{ return m_pFile ? m_pFile->GetFilePath() : _T(""); }
_AFX_INLINE	long CPicture::GetFileSize()
	{ return m_pFile ? m_pFile->GetLength() : -1; }

_AFX_INLINE	PICT_COMPR CPicture::GetCompression()
	{ return m_compression; }

_AFX_INLINE	PICT_ORIENT CPicture::GetOrientation()
	{ return m_orientation; }
_AFX_INLINE	PICT_PLANARCFG CPicture::GetPlanarConfig()
	{ return m_nPlanarConfiguration; }
_AFX_INLINE	WORD CPicture::GetSamplesPerPixel( )
	{ return m_samplesPerPixel; }
_AFX_INLINE	WORD CPicture::GetBitsPerSample( )
	{ return m_bitsPerSample; }

_AFX_INLINE	const CRect CPicture::GetImageRect()
	{ return m_rcImage; }
_AFX_INLINE	const CRect CPicture::GetPictRect()
	{ return m_rcPicture; }
_AFX_INLINE	const CRect CPicture::GetCorePictRect()
	{ return m_rcPictInCore; }
_AFX_INLINE	const CRect CPicture::GetCoreImageRect()
	{ return m_rcImageInCore; }

_AFX_INLINE	PICT_FORDER CPicture::GetFillOrder()
	{ return m_nFillOrder; }

_AFX_INLINE	long	CPicture::GetImageBytes( const CRect& rcSrc, HPBYTE lpBuf )
	{ return 0; }
_AFX_INLINE	long	CPicture::SetImageBytes( const CRect& rcDst, HPBYTE lpBuf )
	{ return 0; }

_AFX_INLINE	const CRect CPicture::GetStripRect()
	{ return m_rcStrip; }
_AFX_INLINE	const CSize CPicture::GetStripLayout()
	{ return m_szStrips; }

_AFX_INLINE	PICT_COLOR	CPicture::GetColorspace()
	{ return m_colorspace; }

//////////////////////////////////////////////////////////////////////////////
// CPictureBase
//////////////////////////////////////////////////////////////////////////////

_AFX_INLINE	HPBYTE	CPictureBase::GetDataPointer()
	{ return (HPBYTE) *m_pMemBlock; }
_AFX_INLINE	HPBYTE	CPictureBase::GetTmpPointer()
	{ return (HPBYTE) *m_pTmpBlock; }

_AFX_INLINE	long	CPictureBase::GetUsedColors()
	{ return m_nUsedColors; }

_AFX_INLINE BOOL CPictureBase::KnowsPaletteBeforeDrawing()
    { return TRUE; }        // alte CPicture's können das

//////////////////////////////////////////////////////////////////////////////
// global inlines

_AFX_INLINE	long Align( long column, long bitsPerSample, long bitAlignment )
{
//	bitAlignment <<= 3;
	column *= bitsPerSample;
	column += 7;
	column /= 8;
	column += (bitAlignment - 1);
	column /= bitAlignment;
	column *= bitAlignment;
	return column;
}

//////////////////////////////////////////////////////////////////////////////
// CBmpPicture
//////////////////////////////////////////////////////////////////////////////

_AFX_INLINE const CString CBmpPicture::GetPictType()
	{ return _T("BMP"); }
_AFX_INLINE CBmpPicture::~CBmpPicture()
	{ }

//////////////////////////////////////////////////////////////////////////////
// CTifPicture
//////////////////////////////////////////////////////////////////////////////

_AFX_INLINE const CString CTifPicture::GetPictType()
	{ return _T("TIFF"); }
_AFX_INLINE long CTifPicture::GetNeededFileSize( )
	{ return m_rcImage.Width() * m_rcImage.Height(); }
_AFX_INLINE	WORD	CTifPicture::ReadShort( WORD val )
	{ return m_bIsII ? val : 
			  ( val << 8 )
			+ ( val >> 8 );
	}
_AFX_INLINE	DWORD	CTifPicture::ReadLong( DWORD val )		
	{ return m_bIsII ? val :
			  ( ( val & 0x000000ffL ) << 24 )
			+ ( ( val & 0x0000ff00L ) << 8 )
			+ ( ( val & 0x00ff0000L ) >> 8 )
			+ ( ( val & 0xff000000L ) >> 24 ) ;
	}
_AFX_INLINE	void CTifPicture::DeleteStripInfo()
	{
		if( NULL != m_pStripInfo )
			delete m_pStripInfo;
		m_pStripInfo = NULL;
	}

_AFX_INLINE	PICT_PROPERTY	CTifPicture::Tag( FILETAG *pTag )			
	{ return (PICT_PROPERTY) ReadShort( pTag->wTag ); }
_AFX_INLINE	WORD	CTifPicture::TagType( FILETAG *pTag )		
	{ return ReadShort( pTag->wType ); }
_AFX_INLINE	DWORD	CTifPicture::TagCount( FILETAG *pTag )		
	{ return ReadLong( pTag->dwCount ); }
_AFX_INLINE	WORD	CTifPicture::TagSVal( FILETAG *pTag )		
	{ return (WORD) ReadShort( (WORD) pTag->dwValue ); }
_AFX_INLINE	DWORD	CTifPicture::TagLVal( FILETAG *pTag )		
	{ return ReadLong( pTag->dwValue ); }

//////////////////////////////////////////////////////////////////////////////
// CPolyGISPicture
//////////////////////////////////////////////////////////////////////////////

_AFX_INLINE const CString CPolyGISPicture::GetPictType()
{ 
	return _T("PGIS"); 
}

_AFX_INLINE CPolyGISPicture::~CPolyGISPicture()
{
}

//////////////////////////////////////////////////////////////////////////////
// CLeadToolsPicture
//////////////////////////////////////////////////////////////////////////////

_AFX_INLINE const CString CLeadToolsPicture::GetPictType()
{ 
	return _T("LEAD"); 
}

_AFX_INLINE CLeadToolsPicture::~CLeadToolsPicture()
{
}

_AFX_INLINE BOOL CLeadToolsPicture::KnowsPaletteBeforeDrawing()
{
    return FALSE;   // LeadTools kennen Palette erst nachdem Bild geladen wurde
}

#endif
