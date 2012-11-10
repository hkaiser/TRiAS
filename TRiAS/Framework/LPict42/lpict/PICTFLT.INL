#ifdef _AFX_INLINE

#ifdef	PICTFLT_RELEASED

_AFX_INLINE	CPictFilter::~CPictFilter( )
	{ }

_AFX_INLINE	void CPictFilter::Init( )
	{ }
_AFX_INLINE	BOOL CPictFilter::SetFilterData( LPFILTERPARAM pData )
	{ 
		if( NULL != pData->lpszTagsToMerge )
			m_strTagsToMerge = pData->lpszTagsToMerge;
		return TRUE;
	}
_AFX_INLINE	BOOL CPictFilter::GetFilterData( LPFILTERPARAM pData )
	{ return FALSE; }

_AFX_INLINE	BOOL CPictFilter::Filter( CPicture *pPicture, CFilterProgress* proc )
	{ return FALSE; }
_AFX_INLINE	BOOL CPictFilter::Filter( CPicture *pInPict, CPicture *pOutPict, CFilterProgress* proc )
	{ return FALSE; }
_AFX_INLINE	BOOL CPictFilter::Filter( CPictFilter *pFlt, CFilterProgress* proc )
	{ return FALSE; }
_AFX_INLINE	BOOL CPictFilter::Filter( CPictFilter *pFlt1, CPictFilter *pFlt2, CFilterProgress* proc )
	{ return FALSE; }

#endif	// PICTFLT_RELEASED

//////////////////////////////////////////////////////////////////////////////
// CPictFlip

#ifdef	PICTFLT_FLIP_RELEASED

_AFX_INLINE	CPictFlip::CPictFlip( )
	{ }

#endif	PICTFLT_FLIP_RELEASED

//////////////////////////////////////////////////////////////////////////////
// CPictSample

#ifdef	PICTFLT_SAMPLE_RELEASED
_AFX_INLINE	CPictSample::CPictSample( )
	{ m_sampleRate = 1; m_sampleParam = 0; }
_AFX_INLINE	CPictSample::~CPictSample( )
	{ }
#endif	// PICTFLT_SAMPLE_RELEASED

////////////////////////////////////////////////////////////////////
//	CPictHistogramm

#ifdef	PICTFLT_HIST_RELEASED
#endif	// PICTFLT_HIST_RELEASED

//////////////////////////////////////////////////////////////////////////////
// CMedianCut

#ifdef	PICTFLT_MCUT_RELEASED

_AFX_INLINE	LONG CMedianCut::RGBDist( short dR, short dG, short dB )
	{ return (LONG) dR * (LONG) dR + (LONG) dG * (LONG) dG + (LONG) dB * (LONG) dB; }

#endif	// PICTFLT_MCUT_RELEASED

//////////////////////////////////////////////////////////////////////////////
// CFitClut

#ifdef	PICTFLT_FITCLUT_RELEASED
#endif	// PICTFLT_FITCLUT_RELEASED

//////////////////////////////////////////////////////////////////////////////
// CColorFilter

#ifdef	PICTCOLOR_RELEASED

_AFX_INLINE	CColorFilter::CColorFilter()
	{}
_AFX_INLINE	CColorFilter::~CColorFilter( )
	{}
_AFX_INLINE	void CColorFilter::Init()
	{}
_AFX_INLINE	BOOL CColorFilter::SetFilterData( LPFILTERPARAM pData )
	{ return FALSE; }
_AFX_INLINE	BOOL CColorFilter::GetFilterData( LPFILTERPARAM pData )
	{ return FALSE; }
_AFX_INLINE	BOOL CColorFilter::Filter( LPRGBQUAD pInClut, LPRGBQUAD pOutClut, int nColors, CFilterProgress* proc )
	{ return FALSE; }
_AFX_INLINE	COLORREF CColorFilter::Filter( COLORREF color, CFilterProgress* proc )
	{ return RGB( 0, 0, 0 ); }
_AFX_INLINE	const COLORREF CColorFilter::operator()( COLORREF color )
	{ return RGB( 0, 0, 0 ); }

#endif	// PICTCOLOR_RELEASED

//////////////////////////////////////////////////////////////////////////////

#ifdef	PICTCOLOR_RGBHSB_RELEASED

_AFX_INLINE	CRGBtoHSB::CRGBtoHSB()
	{}
_AFX_INLINE	CRGBtoHSB::~CRGBtoHSB()
	{}

#endif	// PICTCOLOR_RGBHSB_RELEASED

#ifdef	PICTCOLOR_HSBRGB_RELEASED

_AFX_INLINE	CHSBtoRGB::CHSBtoRGB()
	{}
_AFX_INLINE	CHSBtoRGB::~CHSBtoRGB()
	{}

#endif	// PICTCOLOR_HSBRGB_RELEASED

#ifdef	PICTCOLOR_EXPAND_RELEASED

_AFX_INLINE	CExpandColorChannel::CExpandColorChannel()
	{ m_nChannel = 0; }
_AFX_INLINE	CExpandColorChannel::~CExpandColorChannel()
	{}

#endif	// PICTCOLOR_EXPAND_RELEASED

#ifdef	PICTCOLOR_ARRANGE_RELEASED

_AFX_INLINE	CArrangeColorChannels::CArrangeColorChannels()
	{ memset( (void*) &m_channelOrder[0], 0x00, sizeof(m_channelOrder) ); }
_AFX_INLINE	CArrangeColorChannels::~CArrangeColorChannels()
	{}

#endif	// PICTCOLOR_ARRANGE_RELEASED

#endif	// _AFX_INLINE
