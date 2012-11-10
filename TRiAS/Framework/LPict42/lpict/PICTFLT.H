////////////////////////////////////////////////////////////////////
//	Bildfilter
////////////////////////////////////////////////////////////////////

#ifndef	__PICTFILT_H__
#define	__PICTFILT_H__

#include	"lpict/picture.h"

#ifdef _AFXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

////////////////////////////////////////////////////////////////////
// das gibt's hier alles...

// class	CObject;
	class	CPictFilter;
		class	CPictCopy;
		class	CPictSample;
		class	CPictFlip;
		class	CPictHistogramm;
		class	CPictBitOr;
		class	CMedianCut;

	class	CColorFilter;
		class	CRGBtoHSB;
		class	CHSBtoRGB;
		class	CExpandColorChannel;
		class	CArrangeColorChannels;

////////////////////////////////////////////////////////////////////
// Modulfreigabe

#define	PICTFLT_RELEASED			// Basisklasse für Bildfilter
#define	PICTFLT_HIST_RELEASED		// Histogrammberechnung
#define	PICTFLT_MCUT_RELEASED		// Farbreduktion / Floydberg-Stein
#define	PICTFLT_SAMPLE_RELEASED		// Größenreduktion

#define	PICTCOLOR_RELEASED			// Farbmanipulation
#define	PICTCOLOR_RGBHSB_RELEASED	// RGB -> HSB
#define	PICTCOLOR_HSBRGB_RELEASED	// HSB -> RGB
#define	PICTCOLOR_EXPAND_RELEASED	// Verteilung eines Kanals auf die anderen
#define	PICTCOLOR_ARRANGE_RELEASED	// Umsortieren von Farbkanälen

////////////////////////////////////////////////////////////////////
//	Filterstruktur zur Parameterübergabe
// tagsToMerge:
//	"tagNum,tagValue|tagNum,tagValue..."
////////////////////////////////////////////////////////////////////

typedef struct tagFILTERPARAM {
	DWORD			dwSizeOfStruct;
	CRuntimeClass	*pRtStructUser;
	LPCTSTR			lpszTagsToMerge;
} FILTERPARAM;

typedef FILTERPARAM FAR* LPFILTERPARAM;

#define INIT_FILTERSTRUCT( pS, o ) \
	memset(	pS, 0x00, sizeof(*pS) ); \
	(pS)->p.dwSizeOfStruct = sizeof((*pS)); \
	(pS)->p.pRtStructUser = RUNTIME_CLASS( o );

#define	CHECK_FILTERSTRUCT( p ) \
	ASSERT( sizeof(*(p)) == (p)->p.dwSizeOfStruct ); \
	ASSERT( GetRuntimeClass() == (p)->p.pRtStructUser ); \
	if( sizeof(*(p)) != (p)->p.dwSizeOfStruct || GetRuntimeClass() != (p)->p.pRtStructUser ) \
		return FALSE;

class CFilterProgress {
public:
	virtual	void StartingFilter() = 0;
	virtual void ReportingStatus( double havePercent, LPCTSTR lpszMsg = NULL ) = 0;
	virtual void EndingFilter() = 0;
};

////////////////////////////////////////////////////////////////////
//	CPictFilter ist Basisklasse für alle anderen
////////////////////////////////////////////////////////////////////

#ifdef	PICTFLT_RELEASED

class AFX_EXT_CLASS CPictFilter : public CObject {
protected:
	DECLARE_DYNAMIC( CPictFilter );

	HPBYTE	m_pSrcPictData;
	HPBYTE	m_pDstPictData;

	CRect	m_rcSrcPict;			// Quellbild logisch
	CRect	m_rcDstPict;			// Zielbild logisch
	CRect	m_rcSrcImage;			// Quellbild physisch
	CRect	m_rcDstImage;			// Zielbild physisch
	CRect	m_rcSrcBand;			// Quellband logisch
	CRect	m_rcDstBand;			// Zielband logisch
	CRect	m_rcSrcCore;			// Quellspeicher physisch
	CRect	m_rcDstCore;			// Zielspeicher physisch

private:
	CString	m_strTagsToMerge;
protected:
	void MergeTags( CPicture* pO );

#ifdef	_DEBUG
	CPicture	*m_pI, *m_pO;						// für 'CheckDataPointer'
#endif

	void	GetPictureInfo( CPicture *pI, CPicture *pO = NULL );
	virtual	BOOL	DoFilter( );
public:
	CPictFilter( );
	virtual	~CPictFilter( );

	virtual	void	Init( );
	virtual	BOOL	Filter( CPicture *pPicture, CFilterProgress* proc = NULL );
	virtual	BOOL	Filter( CPicture *pInPict, CPicture *pOutPict, CFilterProgress* proc = NULL  );
	virtual	BOOL	Filter( CPictFilter *pFlt, CFilterProgress* proc = NULL  );
	virtual	BOOL	Filter( CPictFilter *pFlt1, CPictFilter *pFlt2, CFilterProgress* proc = NULL  );

	virtual	BOOL	SetFilterData( LPFILTERPARAM pData );
	virtual	BOOL	GetFilterData( LPFILTERPARAM pData );
public:
	virtual	void	Serialize( CArchive& ar );
};

#endif	// PICTFLT_RELEASED

////////////////////////////////////////////////////////////////////
//	kopieren, stauchen, strecken usw.
////////////////////////////////////////////////////////////////////

typedef struct tagPICTCOPYPARAM {
	FILTERPARAM	p;
	int	m_l, m_t, m_r, m_b;
} PICTCOPYPARAM;

typedef PICTCOPYPARAM FAR* LPPICTCOPYPARAM;

class AFX_EXT_CLASS CPictCopy : public CPictFilter {
	long	m_BytesPerSrcLine;
	long	m_BytesPerDstLine;
	int		m_l, m_t, m_r, m_b;
	const	BYTE * m_pBitmap;
	BOOL	Copy1( );
	BOOL	Copy4( );
	BOOL	Copy8( );
	BOOL	Copy24( );
protected:
	DECLARE_SERIAL( CPictCopy );
public:
	CPictCopy();
	virtual ~CPictCopy();
public:
	virtual	BOOL	SetFilterData( LPFILTERPARAM pData );
	BOOL	Filter( CPicture *pIPic, CPicture *pOPic, CFilterProgress* proc = NULL );
public:
	virtual	void	Serialize( CArchive& ar );
};

#ifdef	PICTFLT_SAMPLE_RELEASED

typedef struct tagPICTSAMPLEPARAM {
	FILTERPARAM	p;
	int		sampleRate;
	int		sampleParam;
} PICTSAMPLEPARAM;

typedef PICTSAMPLEPARAM FAR* LPPICTSAMPLEPARAM;

class AFX_EXT_CLASS CPictSample : public CPictFilter {
	long	m_BytesPerSrcLine;
	long	m_BytesPerDstLine;
	long	m_sampleParam;
	RGBQUAD	m_clut[256];
	BYTE	m_colors[32768];

protected:
	DECLARE_SERIAL( CPictSample );

private:
	int		m_sampleRate;
	BOOL	Sample1( long nLinesInPicture = 0, long nStartOffset = 0, CFilterProgress* proc = NULL );
	BOOL	Sample4( long nLinesInPicture = 0, long nStartOffset = 0, CFilterProgress* proc = NULL );
	BOOL	Sample8( long nLinesInPicture = 0, long nStartOffset = 0, CFilterProgress* proc = NULL );
	BOOL	Sample24( long nLinesInPicture = 0, long nStartOffset = 0, CFilterProgress* proc = NULL );
public:
	CPictSample( );
	virtual	~CPictSample( );

	virtual	BOOL	Filter( CPicture *pInPicture, CPicture *pOutPicture, CFilterProgress* proc = NULL );
	virtual	BOOL	SetFilterData( LPFILTERPARAM pData );
public:
	virtual	void	Serialize( CArchive& ar );
};

#endif	// PICTFLT_SAMPLE_RELEASED

////////////////////////////////////////////////////////////////////
//	Farben usw.
////////////////////////////////////////////////////////////////////

#ifdef	PICTFLT_HIST_RELEASED

typedef struct tagPICTHISTPARAM {
	FILTERPARAM	p;
	DWORD	nPixels;		// Anzahl der zur Histogrammberechnung verw. Pixel
	DWORD	nSamples;		// Anzahl Stützstellen im Histogramm
	HPDWORD	pHist;			// Histogrammdaten
} PICTHISTPARAM;

typedef PICTHISTPARAM FAR* LPPICTHISTPARAM;

class AFX_EXT_CLASS CPictHistogramm : public CPictFilter {
	DWORD	m_nPoints;						// Anzahl Punkte im Histogramm
	HPDWORD	m_pHistData;					// Zeiger auf Histogrammdaten
	long	m_BytesPerSrcLine;
protected:
	DECLARE_SERIAL( CPictHistogramm );
	CMemBlock	*m_pHistogramm;
	void	Accumulate( CFilterProgress* proc = NULL );
public:
	CPictHistogramm( );
	virtual	~CPictHistogramm( );

	virtual	void	Init( );
	virtual	BOOL	Filter( CPicture *pPicture, CFilterProgress* proc = NULL );	// akkumuliert die RGB-Werte eines Bildblocks
	virtual	BOOL	GetFilterData( LPFILTERPARAM pData );
public:
	virtual	void	Serialize( CArchive& ar );
};

#endif	// PICTFLT_HIST_RELEASED

#ifdef	PICTFLT_MCUT_RELEASED

enum DITHER_METHOD {
	DITHER_NONE,
	DITHER_3,
	DITHER_4,
};

typedef struct tagMEDIANCUTPARAM {
	FILTERPARAM		p;
	DITHER_METHOD	m;
} MEDIANCUTPARAM;

typedef MEDIANCUTPARAM FAR* LPMEDIANCUTPARAM;

class AFX_EXT_CLASS CMedianCut : public CPictFilter {
protected:
	LPRGBQUAD	m_pClut;						// errechnete Farbtabelle
	WORD		m_nColors;
	UINT		m_clutIndex;					// wird im Median-Cut Algorithmus gebraucht

	HPBYTE		m_pIdxTab;
	WORD		m_nIdxs;
	DITHER_METHOD	m_method;

	DECLARE_SERIAL( CMedianCut );
	void	MedianCut( HPDWORD pHist, LPRGBQUAD pClut, LONG lPixels,
		UINT nColors = 256,
		UINT uR1 = 0, UINT uR2 = 31, 
		UINT uG1 = 0, UINT uG2 = 31, 
		UINT uB1 = 0, UINT uB2 = 31, 
		WORD depth = 0 );
	LONG	RGBDist( short dR, short dG, short dB );
	void	ReduceColors( HPDWORD pHistData, LPRGBQUAD pClutData, WORD nColors = 256 );
	BOOL	Dither0( );
	BOOL	Dither3( );
	BOOL	Dither4( );
public:
	CMedianCut( );
	virtual	~CMedianCut( );

	virtual	void Init( );
	virtual	BOOL	SetFilterData( LPFILTERPARAM pData );
	virtual	BOOL	GetFilterData( LPFILTERPARAM pData );
	virtual	BOOL	Filter( CPictFilter *pFilter, CFilterProgress* proc = NULL );							// Histogramm wird erwartet!
	virtual	BOOL	Filter( CPicture *pInPicture, CPicture *pOutPicture, CFilterProgress* proc = NULL );
public:
	virtual	void	Serialize( CArchive& ar );
};

#endif	// PICTFLT_MCUT_RELEASED

#ifdef	PICTFLT_FITCLUT_RELEASED

typedef struct tagFITCLUTPARAM {
	FILTERPARAM	p;
	LPRGBQUAD	pDstClut;
	UINT		nClutEntries;
} FITCLUTPARAM;

typedef FITCLUTPARAM FAR* LPFITCLUTPARAM;

class AFX_EXT_CLASS CFitClut : public CPictFilter {
	LPRGBQUAD	m_pInClut;
	LPRGBQUAD	m_pOutClut;
	HPALETTE	m_hOutPal;
	UINT		m_newIdxs[256];
protected:
	DECLARE_SERIAL( CFitClut );
	BOOL	DoFilter( );
public:
	CFitClut( );
	virtual ~CFitClut( );
	virtual	void	Init( );
	virtual	BOOL	Filter( CPicture *pI, CPicture *pO, CFilterProgress* proc = NULL );
	virtual BOOL	SetFilterData( LPFILTERPARAM pData );		// Setzen der Palette, an die das Bild anzupassen ist
public:
	virtual	void	Serialize( CArchive& ar );
};

#endif	// PICTFLT_FITCLUT_RELEASED

typedef struct tagFITCLUTPARAM {
	FILTERPARAM	p;
	UINT		m_nLevelToOr;
	int			m_l, m_t, m_r, m_b;
} BITORPARAM;

typedef BITORPARAM FAR* LPBITORPARAM;

class AFX_EXT_CLASS CPictBitOr : public CPictFilter {
	long	m_BytesPerSrcLine;
	long	m_BytesPerDstLine;
	const	BYTE* m_pBitmap;
	int		m_l, m_t, m_r, m_b;
	UINT	m_nLevelToOr;
protected:
	DECLARE_SERIAL( CPictBitOr );
	virtual	BOOL	DoFilter( );
public:
	CPictBitOr();
	virtual ~CPictBitOr();
	virtual BOOL SetFilterData( LPFILTERPARAM pData );
	virtual	BOOL Filter( CPicture *pI, CPicture *pO, CFilterProgress* proc = NULL );
public:
	virtual	void	Serialize( CArchive& ar );
};

////////////////////////////////////////////////////////////////////
//	Farbfilter

#ifdef	PICTCOLOR_RELEASED

class AFX_EXT_CLASS CColorFilter : public CObject {
public:
	virtual const COLORREF operator()( COLORREF color );
protected:
	DECLARE_DYNAMIC( CColorFilter );
public:
	CColorFilter();
	virtual	~CColorFilter( );
	virtual void Init();
	virtual BOOL SetFilterData( LPFILTERPARAM pData );
	virtual	BOOL GetFilterData( LPFILTERPARAM pData );
	virtual BOOL Filter( LPRGBQUAD pInClut, LPRGBQUAD pOutClut, int nColors, CFilterProgress* proc = NULL );
	virtual COLORREF Filter( COLORREF color, CFilterProgress* proc = NULL );
};

#endif	// PICTCOLOR_RELEASED

////////////////////////////////////////////////////////////////////
// RGB<->HSB

#ifdef	PICTCOLOR_RGBHSB_RELEASED

class AFX_EXT_CLASS CRGBtoHSB : public CColorFilter {
protected:
	DECLARE_SERIAL( CRGBtoHSB );
public:
	CRGBtoHSB();
	virtual ~CRGBtoHSB();
	virtual BOOL Filter( LPRGBQUAD pInClut, LPRGBQUAD pOutClut, int nColors, CFilterProgress* proc = NULL );
	virtual COLORREF Filter( COLORREF color, CFilterProgress* proc = NULL );
	virtual const COLORREF operator()( COLORREF color );
};

#endif	// PICTCOLOR_RGBHSB_RELEASED

#ifdef	PICTCOLOR_HSBRGB_RELEASED

class AFX_EXT_CLASS CHSBtoRGB : public CColorFilter {
protected:
	DECLARE_SERIAL( CHSBtoRGB );
public:
	CHSBtoRGB();
	virtual ~CHSBtoRGB();
	virtual BOOL Filter( LPRGBQUAD pInClut, LPRGBQUAD pOutClut, int nColors, CFilterProgress* proc = NULL );
	virtual COLORREF Filter( COLORREF color, CFilterProgress* proc = NULL );
	virtual const COLORREF operator()( COLORREF color );
};

#endif	// PICTCOLOR_HSBRGB_RELEASED

#ifdef	PICTCOLOR_EXPAND_RELEASED

typedef struct tagCOLOREXPANDPARAM {
	FILTERPARAM	p;
	int	nChannel;
} COLOREXPANDPARAM;

typedef COLOREXPANDPARAM FAR* LPCOLOREXPANDPARAM;

class AFX_EXT_CLASS CExpandColorChannel : public CColorFilter {
protected:
	DECLARE_SERIAL( CExpandColorChannel );
	int	m_nChannel;
public:
	CExpandColorChannel();
	virtual ~CExpandColorChannel();
	virtual BOOL SetFilterData( LPFILTERPARAM pData );
	virtual	BOOL GetFilterData( LPFILTERPARAM pData );
	virtual BOOL Filter( LPRGBQUAD pInClut, LPRGBQUAD pOutClut, int nColors, CFilterProgress* proc = NULL );
	virtual COLORREF Filter( COLORREF color, CFilterProgress* proc = NULL );
	virtual const COLORREF operator()( COLORREF color );
};

#endif	// PICTCOLOR_EXPAND_RELEASED

#ifdef	PICTCOLOR_ARRANGE_RELEASED

static const nChannels = 4;

typedef struct tagCOLORARRANGEPARAM {
	FILTERPARAM	p;
	CWordArray	*channelOrder;
} COLORARRANGEPARAM;

typedef COLORARRANGEPARAM FAR* LPCOLORARRANGEPARAM;

class AFX_EXT_CLASS CArrangeColorChannels : public CColorFilter {
protected:
	DECLARE_SERIAL( CArrangeColorChannels );
	WORD	m_channelOrder[nChannels];
	int	m_nChannel;
public:
	CArrangeColorChannels();
	virtual ~CArrangeColorChannels();
	virtual BOOL SetFilterData( LPFILTERPARAM pData );
	virtual	BOOL GetFilterData( LPFILTERPARAM pData );
	virtual BOOL Filter( LPRGBQUAD pInClut, LPRGBQUAD pOutClut, int nColors, CFilterProgress* proc = NULL );
	virtual COLORREF Filter( COLORREF color, CFilterProgress* proc = NULL );
	virtual const COLORREF operator()( COLORREF color );
};

#endif	// PICTCOLOR_ARRANGE_RELEASED

#ifdef	_AFX_ENABLE_INLINES
#if !defined(_AFX_INLINE)
#define	_AFX_INLINE inline
#endif
#include	"lpict/pictflt.inl"
#endif

#ifdef _AFXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#endif	// __PICTFILT_H__
