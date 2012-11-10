#ifndef	__METAFILE_H__
#define	__METAFILE_H__

// class CObject
	class	CMetaFile;

#pragma	pack( push, _AFX_PACKING )
#pragma	pack(1)

typedef METARECORD FAR* LPMETARECORD;

class CMetaMemory : public CObject {
	friend class CMetaFile;

	DWORD	m_dwMemSize;
	DWORD	m_dwMemRemain;
	DWORD	m_dwMemLast;
	DWORD	m_dwRecSize;
	DWORD	m_dwRecRemain;
protected:
	HPBYTE			m_pMemory;
	LPMETARECORD	*m_pRecords;
	DWORD	m_dwRecLast;
public:
	CMetaMemory();
	~CMetaMemory();
	void	Push( METARECORD FAR* );
	CMetaMemory& operator+=( const CMetaMemory& m );
	void	ImportObjects( CDC *pDC, const CRgn& clipRegion, const CMetaMemory& rSrc );
	void	Reset();
};

typedef struct tagSPOINT {
	short	x;
	short	y;
	} SPOINT;
typedef SPOINT FAR* LPSPOINT;

typedef struct tagSLOGBRUSH {
	WORD	lbStyle;
	COLORREF	Color;
	WORD		lbHatch;
	} SLOGBRUSH;
typedef SLOGBRUSH FAR* LPSLOGBRUSH;

typedef struct tagSLOGPEN {
	WORD		lopnStyle;
	SPOINT		lopnWidth;
	COLORREF	Color;
} SLOGPEN;
typedef SLOGPEN FAR* LPSLOGPEN;

typedef struct tagSLOGFONT { // lf  
   WORD lfHeight; 
   WORD lfWidth; 
   WORD lfEscapement; 
   WORD lfOrientation; 
   WORD lfWeight; 
   BYTE lfItalic; 
   BYTE lfUnderline; 
   BYTE lfStrikeOut; 
   BYTE lfCharSet; 
   BYTE lfOutPrecision; 
   BYTE lfClipPrecision; 
   BYTE lfQuality; 
   BYTE lfPitchAndFamily; 
   TCHAR lfFaceName[LF_FACESIZE]; 
} SLOGFONT; 
typedef SLOGFONT FAR* LPSLOGFONT;

typedef struct tagSLOGPALETTE { // lgpl  
    WORD         palVersion; 
    WORD         palNumEntries; 
    PALETTEENTRY palPalEntry[256]; 
} SLOGPALETTE;
typedef SLOGPALETTE FAR* LPSLOGPALETTE;


typedef struct tagGDIOBJECT {
	METARECORD	isA;
	union {
		SLOGBRUSH	brush;
		SLOGPEN		pen;
		SLOGFONT	font;
		SLOGPALETTE	pal;
	};
} GDIOBJECT;

#define	NGDIOBJECTS	20

typedef	struct	tagMETAENUMPARAM {
#if defined(_DEBUG) || defined(_RDEBUG)
	CMetaFile	*pObject;
#if defined (_RDEBUG)
	CStringArray*	m_pStrings;
	CString*		m_pStrFormat;
#endif
#endif
	CMetaMemory	*m_pMetaMemory;
	BOOL		m_bReplaceColor;
	GDIOBJECT	m_gdiObjects[NGDIOBJECTS];
	int			m_BSelected;
	int			m_PSelected;
	int			m_FSelected;

	BOOL		m_bClip;
	double		m_dx1L;
	double		m_dy1L;
	double		m_dx1R;
	double		m_dy1R;
	double		m_x2L;
	double		m_y2L;
	double		m_x2R;
	double		m_y2R;

	RECT		m_rcBound;					// Bounding Box aus (R)ealen (min/max) Koordinaten
	RECT		m_rcWBound;					// Bounding Box aus (W)mf (SetWindowOrg/SetWindowExt)
	RECT		m_rcFBound;					// Bounding Box aus (f)orcierten Koordinaten
	short		m_ptParseOffsetX, m_ptParseOffsetY;
	BOOL		m_bSwapX, m_bSwapY;
	CString*	m_pStrSigname;
	COLORREF	m_rgbBrush;
	int			m_nObjects;
	void		Init();
	void		ReInit();
	//////////////////////////////////////////////////////
	// Geometrietransformation
	void CalculateTransformMatrix( double phi );
	void TransformPoint( short& x, short& y );
	double zoom();

	double		m_offsetPictX, m_offsetPictY;
	double		m_offsetDrawX, m_offsetDrawY;	// aktuelle Zeichenposition der Signatur
	double		m_r11, m_r12, m_r21, m_r22;		// 'r' - Rotations-Matrix
	double		m_zx, m_zy;						// Zoomfaktoren in x und y
} METAENUMPARAM;

inline double METAENUMPARAM::zoom() {
	return m_zy;
}

class SEGMENT  {
	DRECT		m_rcPict;				// 
	double		m_rectWidth;
	double		m_rectTop;
	double		m_rectBtm;
	DPOINT		m_P0;					// Lage des Segments
	DPOINT		m_P1;
	double		m_length;				// L‰nge der Strecke
	double		m_phi;					// Anstieg
#ifdef _DEBUG
	double		m_dms;
#endif
	DPOINT		m_ptBound[4];			// umschlieﬂende Punkte
	DPOINT		m_ptClip[8];			// Clipping-Polygon

	void	Construct( );
public:
	SEGMENT( const DRECT& rc );
	double		m_dx;					// Koordinatendifferenz eines Segmentes
	double		m_dy;

	// ein Segment konstruieren
	void	Construct( const DPOINT& p0, const DPOINT& p1 );
	void	Construct( const DPOINT& p0, const POINT& p1 );

	// Operationen

	void	Rotate( double phi );
	void	Offset( double dx, double dy );

	// die Eigenschaften eines Segmentes
	double	Length();
	DPOINT	P0();
	DPOINT	P1();
	DPOINT	ClipPoint(int nCP);
	double	Phi();
	double	Width();

	void	Clip( SEGMENT& cp );
	void	CreateClipRgn( CDC *pDC, CRgn& clipRgn );
	void	Mark( CDC *pDC );

	SEGMENT& operator=( SEGMENT& cp );
};

inline DPOINT SEGMENT::ClipPoint(int nCP) {
	return m_ptClip[nCP];
}

inline double SEGMENT::Length()
	{ return m_length; }
inline DPOINT SEGMENT::P0()
	{ return m_P0; }
inline DPOINT SEGMENT::P1()
	{ return m_P1; }
inline double SEGMENT::Phi()
	{ return m_phi; }
inline double SEGMENT::Width()
	{ return m_rectWidth; }

inline void SEGMENT::Construct( const DPOINT& p0, const DPOINT& p1 ) {
	m_P0 = p0;
	m_P1 = p1;
	Construct();
}

inline void SEGMENT::Construct( const DPOINT& p0, const POINT& p1 ) {
	m_P0 = p0;
	m_P1.x = p1.x;
	m_P1.y = p1.y;
	Construct();
}

//#pragma	pack( pop, _AFX_PACKING )

class CMetaFile : public CObject {
	DECLARE_DYNAMIC( CMetaFile )

#if defined(_DEBUG) || defined(_RDEBUG)
public:
	CMapWordToPtr	m_listOfRecTypes;
	void			InitDebug( );
	void			DeInitDebug( );
	LPCTSTR			RecType( const UINT rdFunction );
#endif

protected:
	CString			m_strIdent;
	CString			m_strName;
	HMETAFILE		m_hSrcMF;
	HMETAFILE		m_hMemMF;

	MFENUMPROC		m_lpEnumParseMetaProc;
	MFENUMPROC		m_lpEnumDrawMetaProc;
	METAENUMPARAM	m_metaParam;
	CMetaMemory		m_metaMemory;

	BOOL	m_bMarkSegments;
	BOOL	m_bClipDefault;
	BOOL	m_bClipExtended;
	BOOL	Create( HPBYTE pData, DWORD nBytes );

public:
	CMetaFile( );
	virtual ~CMetaFile( );

	BOOL	Create( UINT nResrcID );
	BOOL	Create( const char *pszFileName );
	void	MarkSegments( BOOL bMark = TRUE );
	void	ClipExtended( BOOL bClip = TRUE );
	void	ClipDefault( BOOL bClip = TRUE );

	LPCTSTR	GetName();
	LPCTSTR GetIdent();

	void	BrushColor( COLORREF rgbBrush );

	BOOL	Parse( CStringArray *pParserLog = NULL );
	BOOL	Play( CDC* pDC, CDRect& dstRect, CPoint *pPtDraw, BOOL swapX, BOOL swapY );
	BOOL	Play( CDC* pDC, const CPoint& rPtOffset, CDRect& dstRect, CPointArray& ptList, BOOL swapX, BOOL swapY );
	double	PlaySegment( CDC *pDC, CRect &rcClipDC, SEGMENT &segCurr );
	void	Replay( CDC *pDC );

	const CRect	GetFigureRect( );				// liefert das die Figur umschlieﬂende Rechteck
};

inline LPCTSTR CMetaFile::GetName() {
	return m_strName;
}
inline LPCTSTR CMetaFile::GetIdent() {
	return m_strIdent;
}
inline void	CMetaFile::MarkSegments( BOOL bMark ) {
	m_bMarkSegments = bMark;
}
inline void CMetaFile::ClipDefault( BOOL bClip ) {
	m_bClipDefault = bClip;
}
inline void CMetaFile::ClipExtended( BOOL bClip ) {
	m_bClipExtended = bClip;
}

extern "C" int CALLBACK EnumOnParse( HDC, HANDLETABLE FAR*, METARECORD FAR*, int, METAENUMPARAM*);
extern "C" int CALLBACK EnumOnDraw( HDC, HANDLETABLE FAR*, METARECORD FAR*, int, METAENUMPARAM*);

#pragma	pack( pop, _AFX_PACKING )

#endif	// __METAFILE_H__
