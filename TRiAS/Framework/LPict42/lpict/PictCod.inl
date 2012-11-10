#ifdef _AFX_INLINE

_AFX_INLINE	CPictCodec::CPictCodec( )
	{
		m_pPicture = NULL;
		m_pSrc = NULL;
		TRY { m_pDst = new BYTE[LINEBUFSIZE]; }
		CATCH( CMemoryException, e ) { m_pDst = NULL; }
		END_CATCH
		Reset();
	}
_AFX_INLINE	CPictCodec::~CPictCodec( )
	{ 
		if( NULL != m_pDst )
			delete[] m_pDst;
	}
_AFX_INLINE	BOOL CPictCodec::Attach( CPicture* pPicture )
	{ m_pPicture = pPicture; Reset(); return Setup(); }
_AFX_INLINE	void CPictCodec::Reset()
	{ m_srcPos = m_dstPos = 0; }
_AFX_INLINE	BOOL CPictCodec::Init()
	{ 
		ASSERT_VALID( m_pPicture );
		m_pSrc = m_pPicture->GetTmpPointer();
		m_srcStart = m_srcEnd = 0;
		return TRUE;
	}
_AFX_INLINE	BOOL CPictCodec::Setup()
	{
		ASSERT_VALID( m_pPicture );
		ASSERT( NULL != m_pDst );
		memset( (void*) m_pDst, 0x00, LINEBUFSIZE );
		return TRUE;
	}

//////////////////////////////////////////////////////////////////
// TIFF-Codecs

_AFX_INLINE	CCodecFax::CCodecFax( )
	: CPictCodec()
	{ memset( (void*) &m_l, 0x00, sizeof( m_l ) ); }
_AFX_INLINE	CCodecFax::~CCodecFax()
	{
		if( NULL != m_l.runs )
			delete[] m_l.runs;
	}

// CCodecFaxG3

_AFX_INLINE	CCodecFaxG3::CCodecFaxG3( )
	: CCodecFax()
	{ }
_AFX_INLINE	CCodecFaxG3::~CCodecFaxG3()
	{ }
_AFX_INLINE	void CCodecFaxG3::Reset( )
	{ CCodecFax::Reset(); }
_AFX_INLINE	BOOL CCodecFaxG3::Init( )
	{ return CCodecFax::Init(); }

// CCodecFaxG4

_AFX_INLINE	CCodecFaxG4::CCodecFaxG4( )
	: CCodecFax()
	{ }
_AFX_INLINE	CCodecFaxG4::~CCodecFaxG4()
	{ }
_AFX_INLINE	void CCodecFaxG4::Reset( )
	{ CCodecFax::Reset(); }
_AFX_INLINE	BOOL CCodecFaxG4::Setup( )
	{ return CCodecFax::Setup(); }
_AFX_INLINE	BOOL CCodecFaxG4::Init( )
	{ return CCodecFax::Init(); }

// CCodecPackBits

_AFX_INLINE	CCodecPackBits::CCodecPackBits( )
	: CPictCodec()
	{ }
_AFX_INLINE	CCodecPackBits::~CCodecPackBits()
	{ }
_AFX_INLINE	void CCodecPackBits::Reset( )
	{ 
		CPictCodec::Reset();
		m_nCopy = m_nExpand = 0;
	}
_AFX_INLINE	BOOL CCodecPackBits::Setup()
	{ return CPictCodec::Setup( ); }
_AFX_INLINE	BOOL CCodecPackBits::Init()
	{ return CPictCodec::Init( ); }

// CCodecLZWTiff

_AFX_INLINE	CCodecLZWTiff::CCodecLZWTiff( )
	: CPictCodec()
	{ }
_AFX_INLINE	CCodecLZWTiff::~CCodecLZWTiff()
	{ }
_AFX_INLINE	BOOL CCodecLZWTiff::Setup()
#ifdef _DEBUG
 	{ return TRUE; }
#else
 	{ return FALSE; }
#endif

_AFX_INLINE	BOOL CCodecLZWTiff::Init()
#ifdef _DEBUG
 	{ return TRUE; }
#else
 	{ return FALSE; }
#endif

//////////////////////////////////////////////////////////////////
// BMP-Codecs

// CCodecRLE4

_AFX_INLINE	CCodecRLE4::CCodecRLE4( )
	: CPictCodec()
	{ }
_AFX_INLINE	CCodecRLE4::~CCodecRLE4()
	{ }
_AFX_INLINE	BOOL CCodecRLE4::Setup()
	{ return FALSE; }
_AFX_INLINE	BOOL CCodecRLE4::Init()
	{ return FALSE; }

// CCodecRLE8

_AFX_INLINE	CCodecRLE8::CCodecRLE8( )
	: CPictCodec()
	{ }
_AFX_INLINE	CCodecRLE8::~CCodecRLE8()
	{ }
_AFX_INLINE	void CCodecRLE8::Reset( )
	{
		CPictCodec::Reset();
		m_nCopy = m_nCopyAdd = m_nExpand = 0;
		m_bHaveSymbol = FALSE;
	}
_AFX_INLINE	BOOL CCodecRLE8::Setup()
	{ return CPictCodec::Setup( ); }
_AFX_INLINE	BOOL CCodecRLE8::Init()
	{ return CPictCodec::Init( ); }

#endif // _AFX_INLINE
