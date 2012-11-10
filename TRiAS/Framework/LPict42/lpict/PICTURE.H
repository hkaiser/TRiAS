// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 22.03.2002 20:36:12 
//
// @doc
// @module PICTURE.H | Declaration of the <c CPICTURE> class

#ifndef	__PICTURE_H__
#define	__PICTURE_H__

#include "LibTopoMap/LibTopoMapStructs.h"

///////////////////////////////////////////////////////////////////////////////
// class	CObject;
	class	CMemBlock;
	class	CPicture;
		class	CTifPicture;
		class	CBmpPicture;

// class	CObject;
	class	CColorFilter;
	class	CPictCodec;
	class	CPictFilter;

// class	CException;
	class	CPictException;

#pragma warning(disable: 4275)
#pragma warning(disable: 4251)

#ifdef	_WIN32
typedef void*			HPVOID;
typedef	unsigned char*	HPBYTE;
typedef unsigned short*	HPWORD;
typedef	unsigned long*	HPDWORD;
#else
typedef void __huge*			HPVOID;
typedef	unsigned char __huge*	HPBYTE;
typedef unsigned short __huge*	HPWORD;
typedef	unsigned long __huge*	HPDWORD;
#define	memset	_fmemset
#define	memcpy	_fmemcpy
#endif	// _WIN32

/////////////////////////////////////////////////////////////////////
//	eine Klasse zum sicheren Handling von Speicherblöcken
//	setzt (im Gegensatz zu new/delete auf dem Mechanismus
//	der globalen Halde auf
//	Hinweise:
//	   zu Alloc( DWORD dwNewSize ):
//		diese Funktion vereinigt in sich die Funktionalität
//		zum Allokieren/Deallokieren
//		(letzteres wenn dwNewSize == 0L)
//	   zum operator*()
//		überwacht automatisch die Verriegelung des Blocks
//		bevor die nutzende Funktion 'out of scope' geht
//		sollte explizit UnLock( ) gerufen werden!
/////////////////////////////////////////////////////////////////////

#define	Size1K		1024L
#define	Size2K		( 2 * Size1K )
#define	Size64K		( 64 * Size1K )
#define	Size512K	( 512 * Size1K )
#define	Size1MB		( Size1K * Size1K )
#define	Size2MB		( 2 * Size1MB )
#define	Size4MB		( 4 * Size1MB )
#define	Size8MB		( 8 * Size1MB )
#define	Size16MB	( 16 * Size1MB )

class	AFX_EXT_CLASS CMemBlock : public CObject {
	DECLARE_SERIAL(CMemBlock)
private:
	BOOL		m_bIsLocked;		// verriegelt oder nicht?
	HANDLE		m_hMem;				// der Handle auf den Block
	long		m_lBlockSize;		// aktuell reservierte Größe
	HPBYTE		m_pData;
	CString		m_strBlockName;
	int			m_nCacheHits;
public:
	CMemBlock( long lSize = Size1MB, UINT Flags = GMEM_MOVEABLE | GMEM_ZEROINIT );
	~CMemBlock( );
	
	// Attributes
	BOOL 		IsValid( );
	long		Size( );
	operator HPBYTE( );			// der Zeiger auf den Speicher
	
	// Implementation
private:
	HPBYTE		Lock( );		// explizit verriegeln
	void		UnLock( );		// explizit entriegeln
	void		Initialize( );
	void		ReInitialize( );
	BOOL		_Alloc( long dwSize, UINT uFlags );

public:
	BOOL		Alloc( long dwSize, UINT uFlags = GMEM_MOVEABLE | GMEM_ZEROINIT );
	void		SetBlockName( LPCTSTR lpszName );
	CString		GetBlockName();

	BOOL		CheckPointer( HPBYTE p );
	BOOL		CheckRange( HPBYTE p1, HPBYTE p2 );
	BOOL		CheckRange( HPBYTE p, long size );
	void		CacheHit( BOOL nHit = TRUE );	// FALSE -> Zähler rücksetzen
};

////////////////////////////////////////////////////////////////////
// in Anlehnung an die TIFF-Definition werden alle Daten in TAGS's
// gehalten

typedef struct tagURATIO {
	ULONG	num;
	ULONG	denom;
} URATIO;

typedef struct tagSRATIO {
	long	num;
	long	denom;
} SRATIO;

//typedef long tifftag_t;

class AFX_EXT_CLASS TAG 
{
	void Init();
	void ReadArray( int sizeofItem, int nItems, void* pItems );
protected:
	CString		m_strName;
	PICT_PROPERTY	m_tt;

	////////////////////////////////////////////////////////
	// numerische Datentypen
	struct {
		PICT_DATATYPE	m_tt;
		long	m_count;
		long	m_extraSpace;
		union {
			void*	m_pVal;		// Felddaten
			BYTE	m_ubVal;	// 1
			WORD	m_usVal;	// 2
			ULONG	m_ulVal;	// 3
			URATIO	m_urVal;	// 4
								// 5 ASCII in m_str
			char	m_sbVal;	// 6
								// 7 UNDEFINED
			short	m_ssVal;	// 8
			long	m_slVal;	// 9
			SRATIO	m_srVal;	// 10
			float	m_fVal;		// 11
			double	m_dVal;		// 12
		};
	} m_tv;
public:
	TAG( );
	virtual ~TAG();

	TAG( PICT_PROPERTY t, BYTE v, int count = 1, void* pData = NULL );
	TAG( PICT_PROPERTY t, WORD v, int count = 1, void* pData = NULL );
	TAG( PICT_PROPERTY t, ULONG v, int count = 1, void* pData = NULL );
	TAG( PICT_PROPERTY t, ULONG num, ULONG denom );
	TAG( PICT_PROPERTY t, LPCTSTR p, int count );		// ASCII
	
	TAG( PICT_PROPERTY t, char v, int count = 1, void* pData = NULL );
	TAG( PICT_PROPERTY t, short v, int count = 1, void* pData = NULL );
	TAG( PICT_PROPERTY t, long v, int count = 1, void* pData = NULL );
	TAG( PICT_PROPERTY t, long num, long denom );
	TAG( PICT_PROPERTY t, float v, int count = 1, void* pData = NULL );
	TAG( PICT_PROPERTY t, double v, int count = 1, void* pData = NULL );

	TAG( const TAG& t );			// Copy - Konstruktor
	TAG& operator=( const TAG& t_ );

	const long operator*();
	PICT_PROPERTY	Num() const;
	PICT_DATATYPE	Type() const;
	long	Space( ) const;		// 0 -> kein zusätzlicher Platz
	long	Count() const;		// Anzahl Elemente
	CString& Name();
	LPCTSTR	Name() const;

	void*	pVal() const;
	BYTE	ubVal() const;
	WORD	usVal() const;
	ULONG	ulVal() const;
	URATIO	urVal() const;
	LPCTSTR strVal() const;

	char	sbVal() const;
	short	ssVal() const;
	long	slVal() const;
	SRATIO	srVal() const;
	float	fVal() const;
	double	dVal() const;
};

struct CPictCrack {
	const CString Crack( PICT_PROPERTY tag, long subtag = -1 );
	const CString Crack( PICT_PROPERTY tag, const CPicture* pPicture );
};

#ifdef _CONSOLE
ostream& operator<<( ostream& os, const TAG& t );
#endif // _CONSOLE

////////////////////////////////////////////////////////////////////
// allgemeine Basisklasse für Rasterbilder
class AFX_EXT_CLASS CPicture : 
	public CObject 
{
protected:
	DECLARE_DYNAMIC(CPicture);

	CPicture();
	virtual ~CPicture();

	void*		m_pTagMap;				// Bildeigenschaften als TAG's
	void		DumpTags( ostream& os, bool bRaw = false );

	CString		m_strPictName;			// interner Bilddateiname

	CRect		m_rcPicture;			// log. Ausmaße des Bildes
	CRect		m_rcPictInCore;			// davon ist das Rechteck im Speicher
	CRect		m_rcImage;				// physische Ausmaße des Bildes
	CRect		m_rcImageInCore;		// davon ist das Rechteck im Speicher
	CRect		m_rcStrip;				// Größe eines Strip
	CSize		m_szStrips;				// Striplayout / Kachelung

	CFile			*m_pFile;			// verbundene Datei

	PICT_COMPR		m_compression;
	PICT_FORDER		m_nFillOrder;
	PICT_PLANARCFG	m_nPlanarConfiguration;
	WORD			m_samplesPerPixel;
	WORD			m_bitsPerSample;	// 1, 2, 4, 8 ... mit Farbtabelle; 24 ... ohne Farbtabelle

	PICT_COLOR		m_colorspace;
	PICT_ORIENT		m_orientation;

	double			m_XResolution;
	double			m_YResolution;

public:
	virtual HPBYTE	GetDataPointer() = 0;		// protected... Zugriff nur für Filter
	virtual HPBYTE	GetTmpPointer() = 0;		// dito

// Diagnostic
#ifdef	_DEBUG	
	virtual BOOL	CheckDataPointer(HPBYTE p)	{ return TRUE; }
#endif

	virtual BOOL	GetTag( const PICT_PROPERTY tagNum, TAG& rTag ) const;
	virtual BOOL	SetTag( const PICT_PROPERTY tagNum, const TAG& rTag );
	virtual BOOL	MergeTag( const PICT_PROPERTY tagNum, LPCTSTR lpszString );	// nur für _ASCII - Tags!!

////////////////////////////////////////////////////////////////////////
// Bildoperationen
	BOOL	Attach(CFile* pFile);
	void	Detach();
	BOOL	Read( const CRect& rcRect );

///////////////////////////////////////////////////////////////////////////////
// setzen von Bildparametern; einige Eigenschaften können immer gesetzt werden; 
// diese sind vom Typ *void*, Eigenschaften vom Typ BOOL sind abhängig vom konkreten
// Bilddateiformat; CPictException gibt Auskunft im Fehlerfall
	void SetXResolution(double xRes);
	void SetYResolution(double yRes);

	virtual BOOL SetCoreRect(const CRect& rcCore);

	const CString	GetFileName();			// Bilddateiname
	long			GetFileSize();
	const CString	GetPictName();			// TAGDOCUMENTNAME
	BOOL			SetPictName(LPCTSTR lpszPictName);

	PICT_COMPR		GetCompression();		// TAGCOMPRESSION

	PICT_ORIENT		GetOrientation();		// TAGORIENTATION
	PICT_PLANARCFG	GetPlanarConfig();		// TAGPLANARCONFIG
	WORD			GetBitsPerSample();		// TAGBITSPERSAMPLE
	WORD			GetSamplesPerPixel();	// TAGSAMPLESPERPIXEL
	PICT_FORDER		GetFillOrder();			// TAGFILLORDER
	PICT_COLOR		GetColorspace();		// TAGCOLORSPACE
	
	const CRect		GetPictRect();			// logische Bildausmaße (Spalten, Zeilen)
	const CRect		GetImageRect();			// physische Bildausmaße (Bytes, Zeilen )
	const CRect		GetCorePictRect();
	const CRect		GetCoreImageRect();
	const CRect		GetStripRect();
	const CSize		GetStripLayout();

public:
// zu implementierende Funktionen
	virtual	void Init();
	virtual	BOOL Clone(CPicture *pPicture, CPictException *pE = NULL);

	virtual	long AlignTop(long line) = 0;
	virtual	long FillBuffer(long nBytes, long startRestBytes, long nRestBytes) = 0;
	virtual	long StoreScanLine(HPBYTE pLine, long line, const CRect& rcCore) = 0;
	virtual	BOOL ReadRaw(const CRect& rcRect) = 0;
	virtual BOOL Decode(const CRect& rcRect) = 0;

	virtual	BOOL ReadHeader( CPictException *e = NULL, int nPicture = 0 ) = 0;
	virtual BOOL SelectSubFile( int nFile ) = 0;

	virtual	void SetPictRect( const CRect& rcPict ) = 0;
	virtual	BOOL WriteHeader() = 0;
	virtual	BOOL WriteTrailer() = 0;
	virtual	BOOL Write( const CRect& rcRect, PICT_ORIENT srcOrient = PICT_ORIENT_UPPERLEFT ) = 0;

	virtual const CRect GetBestCorePictRect() = 0;
	virtual	long GetNeededFileSize() = 0;

	virtual BOOL SetCompression( PICT_COMPR compr, CPictException *pE = NULL ) = 0;
	virtual	BOOL SetColorspace( PICT_COLOR color, CPictException *pE = NULL ) = 0;
	virtual BOOL SetResolutionUnit( PICT_RESUNIT resUnit, CPictException *pE = NULL ) = 0;
	virtual BOOL SetOrientation( PICT_ORIENT orient, CPictException *pE = NULL ) = 0;

	virtual	long GetImageBytes( const CRect& rcSrc, HPBYTE lpBuf );
	virtual	long SetImageBytes( const CRect& rcDst, HPBYTE lpBuf );
	
	virtual const CString GetPictType() = 0;
	virtual BOOL GetClut (LPRGBQUAD pClut, long items = 256) = 0;
	virtual BOOL SetClut (LPRGBQUAD pClut, long items = 256) = 0;
	virtual long GetUsedColors() = 0;
	virtual void SetTransparency(int nChannel, COLORREF rgb) = 0;
    virtual BOOL KnowsPaletteBeforeDrawing() = 0;

	virtual CString GetBlockName() = 0;
	virtual void SetBlockName(LPCTSTR pcBlockName) = 0;
	virtual void CacheHit (BOOL bHit = TRUE) = 0;

    typedef BOOL (__stdcall * HandlePaletteFunc)(CPicture *pPicture);

	virtual BOOL Draw (CDC* pDC, const CRect& rcSrc, const CRect& rcDst, 
        BOOL bRealizePalette = TRUE, HandlePaletteFunc handlePal = NULL) = 0;

	virtual BOOL GetGeoPoints (GCPList *pGcpList, CPictException *e = NULL);
	virtual BOOL GetGeoPointCS (IUnknown **ppICS, GCPList &rGCPList, CPictException *e = NULL);
	virtual BOOL WantsToCorrectGeoPoints();
	virtual BOOL CorrectGeoPoints (CSize &rSize, GCPList &rGCPList, int iSubFile, CPictException *e = NULL);

// Serialization
public:
	virtual	void	Serialize( CArchive& ar );
};

//////////////////////////////////////////////////////////////////////////
// Basisklasse für Bilder mit interner Behandlung
class	AFX_EXT_CLASS CPictureBase : 
	public CPicture 
{
	friend class CPictCodec;
	friend class CPictFilter;
protected:
	RGBQUAD m_rgbTranspColor;
	DECLARE_DYNAMIC( CPictureBase );

	CMemBlock	*m_pMemBlock;			// Speicherblock für Bilddaten
	BOOL		m_bHaveOwnMemory;		// ist der von uns selbst angelegt worden?
	CMemBlock	*m_pTmpBlock;			// Speicherblock für temporäre Bilddaten

	LPRGBQUAD	m_pClut;				// Farbtabelle
	long		m_nColors;				// Anzahl Farben in Farbtabelle (Standard: 256)
	long		m_nUsedColors;			// davon werden nur soviel benutzt
										// m_nUsedColors  > 0 -> Bild ist Palettenbild
										// m_nUsedColors == 0 -> Bild ist Echtfarbbild
	CColorFilter*	*m_pFilters;		// Farbfilter

//	PICT_G3OPTIONS	m_optG3;
//	PICT_G4OPTIONS	m_optG4;

	virtual	void	Init();

	CPictCodec		*m_pCodec;			// folgende Funktionen im wesentlichen für die Codecs
	virtual HPBYTE	GetDataPointer();		// protected... Zugriff nur für Filter
	virtual HPBYTE	GetTmpPointer();		// dito
	virtual	long	AlignTop(long line) = 0;
	virtual	long	FillBuffer(long line, long startRestBytes, long nRestBytes) = 0;
	virtual	long	StoreScanLine( HPBYTE pLine, long line, const CRect& rcCore) = 0;

	virtual	BOOL	ReadRaw(const CRect& rcRect) = 0;
	virtual BOOL	Decode(const CRect& rcRect);

// Diagnostic
#ifdef	_DEBUG	
	virtual BOOL	CheckDataPointer(HPBYTE p) { return m_pMemBlock->CheckPointer(p); }
#endif

// Operations
public:

	CPictureBase();
	CPictureBase(CMemBlock *pMemBlock);
	virtual	~CPictureBase();

////////////////////////////////////////////////////////////////////////
// Bildoperationen
	virtual	BOOL	Clone(CPicture *pPicture, CPictException *pE = NULL);

	virtual	BOOL	ReadHeader(CPictException *e = NULL, int nPicture = 0) = 0;
	virtual BOOL	SelectSubFile(int nFile) = 0;

	virtual	BOOL	WriteHeader() = 0;
	virtual	BOOL	WriteTrailer() = 0;
	virtual	BOOL	Write(const CRect& rcRect, PICT_ORIENT srcOrient = PICT_ORIENT_UPPERLEFT) = 0;

	void	RemoveColorFilters();
	void	AddColorFilter(CColorFilter* pFilter);		// siehe PictFlt.h
	virtual void SetTransparency(int nChannel, COLORREF rgb);
    virtual BOOL KnowsPaletteBeforeDrawing();

	virtual BOOL	Draw(CDC* pDC, const CRect& rcSrc, const CRect& rcDst, 
        BOOL bRealizePalette = TRUE, HandlePaletteFunc handlePal = NULL);

protected:
    BOOL DrawRawDIB(CDC *pDC, LPBITMAPINFO pBI, HPBYTE lpData, 
        CRect const &rcBand, CRect const &rcDst, BOOL bRealizePalette);

public:
	////////////////////////////////////////////////////////////////////////
	// Bildeigenschaften
	////////////////////////////////////////////////////////////////////////

	virtual const CString	GetPictType() = 0;		// TIFF, BMP, GIF...

	virtual long			GetUsedColors( );		//
	PICT_THRESHOLDING	GetTresholding();	// TAGTRESHOLDING

//	PICT_RESUNIT	GetResolutionUnit();
//	double			GetXResolution();		// TAGYRESOLUTION
//	double			GetYResolution();		// TAGXRESOLUTION

	virtual const CRect GetBestCorePictRect() = 0;
	virtual	long	GetNeededFileSize( ) = 0;

	virtual BOOL GetClut( LPRGBQUAD pClut, long items = 256 );

/////////////////////////////////////////////////////////
// setzen von Bildparametern; einige Eigenschaften können
// immer gesetzt werden; diese sind vom Typ *void*,
// Eigenschaften vom Typ BOOL sind abhängig vom konkreten
// Bilddateiformat; CPictException gibt Auskunft im
// Fehlerfall
	virtual void SetPictRect(const CRect& rcPict) = 0;
	virtual BOOL SetCoreRect(const CRect& rcCore);

	virtual	BOOL SetColorspace(PICT_COLOR color, CPictException *pE = NULL) = 0;
	virtual BOOL SetCompression(PICT_COMPR compr, CPictException *pE = NULL) = 0;
	virtual BOOL SetResolutionUnit(PICT_RESUNIT resUnit, CPictException *pE = NULL) = 0;
	virtual BOOL SetOrientation(PICT_ORIENT orient, CPictException *pE = NULL) = 0;

	virtual BOOL SetClut(LPRGBQUAD pClut, long items = 256);

	virtual CString GetBlockName();
	virtual void SetBlockName(LPCTSTR pcBlockName);
	virtual void CacheHit (BOOL bHit = TRUE);

// Serialization
public:
	virtual	void	Serialize(CArchive& ar);
};

long Align(long column, long bitsPerSample, long bitAlignment);

////////////////////////////////////////////////////////////////////
//
//       Die eigentlichen Implementationen für die Bildtypen
//
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
// Windows-Bitmap

class	AFX_EXT_CLASS CBmpPicture : 
	public CPictureBase 
{
	BITMAPFILEHEADER	m_BFH;
	BITMAPINFOHEADER	m_BIH;
	void	UpdateHeaderInfo( );

protected:
	DECLARE_SERIAL( CBmpPicture );

	virtual	void	Init( );

	virtual	long	AlignTop( long line );
	virtual	long	FillBuffer( long nBytes, long startRestBytes, long nRestBytes );
	virtual	long	StoreScanLine( HPBYTE pLine, long line, const CRect& rcCore );
	virtual	BOOL	ReadRaw( const CRect& rcRect );

	// Implementation
public:
	CBmpPicture( );
	CBmpPicture( CMemBlock *pMemBlock );
	virtual ~CBmpPicture( );

	// Overrides
public:

	virtual	BOOL	ReadHeader( CPictException *e = NULL, int nPicture = 0 );
	virtual BOOL	SelectSubFile( int nFile );

	virtual	void	SetPictRect( const CRect& rcPict );
	virtual	BOOL	WriteHeader( );
	virtual	BOOL	WriteTrailer( );
	virtual	BOOL	Write( const CRect& rcRect, PICT_ORIENT srcOrient = PICT_ORIENT_UPPERLEFT );

	virtual const CRect GetBestCorePictRect();
	virtual	long	GetNeededFileSize( );

	virtual const CString	GetPictType();		// "BMP"

	virtual BOOL SetCompression( PICT_COMPR compr, CPictException *pE = NULL );
	virtual	BOOL SetColorspace( PICT_COLOR color, CPictException *pE = NULL );
	virtual BOOL SetResolutionUnit( PICT_RESUNIT resUnit, CPictException *pE = NULL );
	virtual BOOL SetOrientation( PICT_ORIENT orient, CPictException *pE = NULL );

	// Serialization
public:
	virtual	void	Serialize( CArchive& ar );
};

////////////////////////////////////////////////////////////////////
// TIFF-Bilder

class	AFX_EXT_CLASS CTifPicture : 
	public CPictureBase 
{
	// TIFF-Header
	typedef struct {
		WORD	wByteOrder;				// Byte-Reihenfolge: II oder MM
		WORD	wIdentifier;			// TIFF-Identifikationsnummer: 42
		DWORD	dwIFD;					// Offset des ersten IFD
	} TIFHEADER;
	typedef TIFHEADER FAR *LPTIFHEADER;

	typedef struct {
		WORD	wTag;					// Tag
		WORD	wType;					// Datentyp
		DWORD	dwCount;				// Zähler
		DWORD	dwValue;				// Wert oder Offset
	} FILETAG;
	typedef FILETAG FAR *LPFILETAG;

	typedef	struct	TagSTRIPINFO
	{
		long	stripOffset;
		long	stripSize;
		long	rawRead;
		long	rawWritten;
	} STRIPINFO;
	typedef STRIPINFO FAR *LPSTRIPINFO;

	typedef struct {
		WORD nTags;
		LPFILETAG	pTags;
		LPSTRIPINFO	pStrips;
	} IFD;
	typedef IFD FAR* LPIFD;

	TIFHEADER	m_tifHeader;
	LPIFD		m_pIFD;					// alle Teilbilder
	LPIFD		m_pCurrIFD;

	BOOL	m_bIsII;

	long	m_nExtraSamples;
	long	m_nPredictor;

	STRIPINFO	*m_pStripInfo;

protected:
	DECLARE_SERIAL( CTifPicture );

	virtual	void	Init( );
	virtual	BOOL	Clone( CPicture *pPicture, CPictException *pE = NULL );

	virtual	long	AlignTop( long line );
	virtual	long	FillBuffer( long nBytes, long startRestBytes, long nRestBytes );
	virtual	long	StoreScanLine( HPBYTE pLine, long line, const CRect& rcCore );
	virtual	BOOL	ReadRaw( const CRect& rcRect );

private:
	bool	TagError( int cause, long tagNum, CPictException *e = NULL );
	bool	TagError( int cause, LPCTSTR lpszDescr, CPictException *e = NULL );
	void	DeleteStripInfo( );
	BOOL	ReadStripInfo( const TAG& rTagOffsets, const TAG& rTagSizes, CPictException *e = NULL );
	WORD	ReadShort( WORD val );
	DWORD	ReadLong( DWORD val );
	PICT_PROPERTY	Tag( FILETAG *pTag );
	WORD	TagType( FILETAG *pTag );
	DWORD	TagCount( FILETAG *pTag );
	WORD	TagSVal( FILETAG *pTag );
	DWORD	TagLVal( FILETAG *pTag );

	// Implementation
public:
	CTifPicture( );
	CTifPicture( CMemBlock *pMemBlock );
	virtual	~CTifPicture( );

	virtual	BOOL	ReadHeader( CPictException *e = NULL, int nPicture = 0 );
	virtual BOOL	SelectSubFile( int nFile );

	virtual	void	SetPictRect( const CRect& rcPict );
	virtual	BOOL	WriteHeader( );
	virtual	BOOL	WriteTrailer( );
	virtual	BOOL	Write( const CRect& rcRect, PICT_ORIENT srcOrient = PICT_ORIENT_UPPERLEFT );

	virtual const CRect GetBestCorePictRect();
	virtual	long	GetNeededFileSize( );

	virtual BOOL SetCompression( PICT_COMPR compr, CPictException *pE = NULL );
	virtual	BOOL SetColorspace( PICT_COLOR color, CPictException *pE = NULL );
	virtual BOOL SetResolutionUnit( PICT_RESUNIT resUnit, CPictException *pE = NULL );
	virtual BOOL SetOrientation( PICT_ORIENT orient, CPictException *pE = NULL );

	virtual	long	GetImageBytes( const CRect& rcSrc, HPBYTE lpBuf );
	virtual	long	SetImageBytes( const CRect& rcDst, HPBYTE lpBuf );
	
	virtual const CString	GetPictType();		// "TIFF"
	virtual BOOL SetClut( LPRGBQUAD pClut, long items = 256 );

	// Serialization
public:
	virtual	void	Serialize( CArchive& ar );
};

#include "lpict/PolyGISPicture.h"
#include "lpict/LeadToolsPicture.h"

//////////////////////////////////////////////////////////////////////////////
//	PictException
//////////////////////////////////////////////////////////////////////////////

class	AFX_EXT_CLASS CPictException : 
	public CException 
{
	DECLARE_DYNAMIC( CPictException )

public:
	enum {
		none
		, errMissingInfo		// Bildheaderinformation fehlt
		, errInvalidInfo		// Bildheaderinformation inkonsistent
		, errFormat				// Bildtyp paßt nicht / interner Formatfehler
		, errFileSize			// berechnete Bildgröße stimmt nicht mit Dateigröße überein
		, errStripInfo			// Strip / Tile - Informationen fehlen
		, errImageLayout		// bei Tiled Images fehlt Breite und/oder Höhe
		, errColorSpace			// nicht unterstützter Farbraum
		, errCompression		// nicht unterstützter Kompressionstyp
		, errPictSize			// Bildhöhe oder Breite ist null
		, errSample				// nicht unterstützte Farbtiefe
		, errMemory				// Speicherfehler
		, errDatatype			// Fehlerhafter Datentyp
		, errSubfileNotFound	// ...
		, errOrientation		// nicht unterstützte Orientierung...
		, errFilterParam		// fehlerhafter Filterparameter
		, errFilterSrcRead		// Fehler beim Lesen eines Bildbereiches
		, errFilterDstRead		// Fehler beim Lesen eines Bildbereiches
		, errFilterWrite		// Fehler beim Schreiben eines Bildbereiches
		, errFilterProcess		// Fehler in der Bildfilterung
		, errTransparency		// Bild kann nicht transparent dargestellt werden
		, errLTInitFailure		// LeadTools sind nicht initialisierbar
	};
	
	CPictException( int cause = CPictException::none, LPCTSTR lpszPictType = NULL, LPCTSTR lpszCause = NULL, LPCTSTR lpszPictName = NULL );
	int	m_cause;
	CString	m_strCause;
	CString	m_strPictType;		// Filtertyp bei CPictFilter
	CString	m_strPictName;		// Filterfehler bei CPictFilter
#ifdef	_DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif
};

void AFXAPI LAfxThrowPictException(int cause = CPictException::none, LPCTSTR lpszPictType = NULL, LPCTSTR lpszCause = NULL, LPCTSTR lpszPictName = NULL );
void AFXAPI LAfxThrowPictMemException( CMemBlock *pBlock, HPBYTE pByte, long lSize = 0, LPCTSTR lpszPictType = NULL, LPCTSTR lpszPictName = NULL );

namespace lpictdll {
	void AFX_EXT_API ReportPictException( CPictException *e, LPCTSTR lpszAddInf = NULL );
	void AFX_EXT_API ReportFileException( CFileException *e, LPCTSTR lpszAddInf = NULL );
	void AFX_EXT_API ReportMemoryException( CMemoryException *e, LPCTSTR lpszAddInf = NULL );
};

//////////////////////////////////////////////////////////////////////////////
//	Bildateityp ermitteln
//////////////////////////////////////////////////////////////////////////////

AFX_EXT_API CRuntimeClass* GetPictureType(CFile* pFile, CPictException* e = NULL);
AFX_EXT_API CRuntimeClass* GetWritablePictureType(CFile* pFile, CPictException* e = NULL);

//////////////////////////////////////////////////////////////////////////////

#ifdef	_AFX_ENABLE_INLINES
#if !defined(_AFX_INLINE)
#define	_AFX_INLINE inline
#endif
#include	"lpict/picture.inl"
#endif

#ifdef _AFXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif

#endif	// __PICTURE_H__
