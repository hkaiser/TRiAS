#ifndef __LAFX_H__
#define __LAFX_H__

#include	<afx.h>
#include	<afxcoll.h>
#include	<strstrea.h>

#include	"lmfcx/lafxver_.h"

#ifdef _AFXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#pragma warning(disable: 4275)
#pragma warning(disable: 4251)

//class CObject
		class CPath;
		class CRex;

class CDSize;
class CDPoint;
class CDRect;

//class CObject
	class CLine;
	class CStraith;
	class CTriangle;

//CObject
	class CVector;
	class CMatrix;
	// class CException
		class CMathException;

/////////////////////////////////////////////////////////////////////
//	CPath
/////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CPath : public CObject
{
	DECLARE_SERIAL( CPath );
protected:
	int		m_Drive;
	CString	m_sDrv, m_sDir, m_sPfx, m_sExt;
	CString	m_sPath;

	void	Cleanup( );
	void	NewFile( );
public:
	CPath( );
	CPath( LPCTSTR pszFullPath );

	void	Path( LPCTSTR pszFullPath );      
	void	Drive( LPCTSTR pszDrive );
	void	Dir( LPCTSTR pszDir );
	void	Prefix( LPCTSTR pszPrefixOfFileName );
	void	Suffix( LPCTSTR pszSuffixOfFileName );
	void	FileName( LPCTSTR pszFileName );

	operator LPCTSTR   () const;
	LPCTSTR  operator()() const;
        
	CString	Path( ) const;
	CString	Drive( ) const;
	CString	Dir( ) const;
	CString	Prefix( ) const;
	CString	Suffix( ) const;
	CString	FileName( ) const;

	// Overrides
public:
	virtual	~CPath( );
	virtual void Serialize( CArchive& ar );

#ifdef _DEBUG
	virtual void	Dump( CDumpContext& dc ) const;
	virtual void	AssertValid( ) const;
#endif
};

/////////////////////////////////////////////////////////////////////
// UNIX-like Optionsauswertung

AFX_EXT_API	int getopt(int argc, LPCTSTR *argv, LPCTSTR optstring, int& optind, LPCTSTR& optarg );

/////////////////////////////////////////////////////////////////////
//	CRegExpString
//	-	supports string matching with regular expressions
/////////////////////////////////////////////////////////////////////

#define	NBRA	9					// maximum number of brackets
#define DEF_EOF '\0'				// default EOF - character

class AFX_EXT_CLASS CRex : public CObject
{
	DECLARE_DYNAMIC( CRex );
public:
	typedef enum {
		E_REXSTRING_EMPTY = 41,		// 
		E_REXSTRING_NEWLINE = 36,	// newline in rex-string

		E_REXBUF_OVERFLOW = 50,		//
		
		E_BRACKET_CLOSE = 42,		// number of closed brackets > opened brackets
		E_BRACKET_COUNT = 43,		// number of open brackets > NBRA
		E_BRACKET_UNDEF = 25,		// undefined bracket; i.e: /\(ab\)/\2/

		E_RANGE_INVALIDCHAR = 16,	// invalid char in range
		E_RANGE_TOBIG = 11,			// count > 255
		E_RANGE_COMMA = 44,			// two commas in range; i.e. {1,,3}
		E_RANGE_SIZE = 46,			// first count in range > second count; i.e.: {3,1}
		E_RANGE_NOTCLOSED = 45,		// missing closed bracket in range; i.e. {1,3...
		E_RANGE_EOF = 49			// eof in range ('\0' or '\n')
	} REXERR;

protected:
	void	Construct();
	void	Initialize();
	BOOL	Advance( LPCTSTR  string, BYTE * exprBuf );
	void	GetRange( BYTE * string, int& nLow, int& nSize );
	BOOL	Ecmp( LPCTSTR str1, LPCTSTR str2, int count );

	BYTE	*m_pEB;				// buffer for compiled expr - string
	BYTE	*m_pEBEnd;			// end of buffer
	BYTE	*m_pEBCurr;			// current position in compiled expr - string

	LPCTSTR	*m_pszBrackSList;	// list of opened brackets
	LPCTSTR	*m_pszBrackEList;	// list of closed brackets
	int		m_nBrackets;		// number of brackets found in expr - string

	BOOL	m_bIsSed;			// 'sed(1)' use this Class
	BOOL	m_bIsCircf;			// expr. string starts with circumflex '^'
	BOOL	m_bIsNoDelim;		// expr. string has no delimiter
	char	m_nEof;				// EOF - marker for expr. - string

	LPCTSTR	m_pszStart;

	LPCTSTR m_pszMatchStart;
	LPCTSTR	m_pszMatchEnd;

	int		m_nRegErr;
	LPCTSTR	m_pszRegErr;

public:
	CRex( );
	CRex( LPCTSTR  instring, char seof = DEF_EOF );
	~CRex( );

	BOOL	Compile( LPCTSTR  instring, char seof = DEF_EOF );
	BOOL	Compare( LPCTSTR  string );
	CString	Found( int nItem = 0 );		// 0 ... returns the entire string that matches the pattern
										// > 0 ... returns the n'th Substring found in brackets

//	char*	Value( int nIndex );

	int	Error( ) { return m_nRegErr; }
	LPCTSTR	ErrorPos( ) { return m_pszRegErr; }
//	LPCTSTR	Matched( ) { return m_pszMatchStart; }

// Diagnostic Support
#ifdef	_DEBUG
public:
	void	Dump( CDumpContext& dc );
protected:
	void	DumpCCHR( BYTE*& cp, strstream& s );
	void	DumpCCL( BYTE*& cp, strstream& s );
	void	DumpRange( BYTE*& cp, strstream& s );
#endif
};

#ifndef __DOUBLE_GEOM_DEFINED__
#define __DOUBLE_GEOM_DEFINED__

typedef struct tagDSIZE {
	double	cx, cy;
} DSIZE;

typedef struct tagDPOINT {
	double	x, y;
} DPOINT;

typedef struct tagDRECT {
	double	left, top, right, bottom;
} DRECT;

typedef const DRECT* LPCDRECT;    // pointer to read/only DRECT
typedef DRECT *LPRECTD;
typedef const DPOINT* LPCDPOINT;
typedef DPOINT* LPDPOINT;
typedef const DSIZE* LPCDSIZE;
typedef DSIZE* LPDSIZE;

/////////////////////////////////////////////////////////////////////////////
// CDSize

class AFX_EXT_CLASS CDSize : public tagDSIZE
{
public:

// Constructors
	CDSize();
	CDSize(double initCX, double initCY);
	CDSize(DSIZE initSize);
	CDSize(DPOINT initPt);
	CDSize(DWORD dwSize);

// Operations
	BOOL operator==(DSIZE size) const;
	BOOL operator!=(DSIZE size) const;

	void operator+=(DSIZE size);
	void operator-=(DSIZE size);

// Operators returning CDSize values
	CDSize operator+(DSIZE size) const;
	CDSize operator-(DSIZE size) const;
	CDSize operator-() const;

// Operators returning CDPoint values
	CDPoint operator+(DPOINT point) const;
	CDPoint operator-(DPOINT point) const;

// Operators returning CDRect values
	CDRect operator+(const DRECT* lpRect) const;
	CDRect operator-(const DRECT* lpRect) const;
};

/////////////////////////////////////////////////////////////////////////////
// CDPoint - A 2-D point

class AFX_EXT_CLASS CDPoint : public tagDPOINT
{
public:

// Constructors
	CDPoint();
	CDPoint(double initX, double initY);
	CDPoint(DPOINT initPt);
	CDPoint(DSIZE initSize);
	CDPoint(DWORD dwPoint);

// Operations
	void Offset(double xOffset, double yOffset);
	void Offset(DPOINT point);
	void Offset(DSIZE size);
	BOOL operator==(DPOINT point) const;
	BOOL operator!=(DPOINT point) const;

	void operator+=(DSIZE size);
	void operator-=(DSIZE size);
	void operator+=(DPOINT point);
	void operator-=(DPOINT point);

	void operator+=(SIZE size);
	void operator-=(SIZE size);
	void operator+=(POINT point);
	void operator-=(POINT point);

// Operators returning CDPoint values
	void operator=(const DPOINT& srcPoint);
	CDPoint operator+(DSIZE size) const;
	CDPoint operator-(DSIZE size) const;
	CDPoint operator-() const;
	CDPoint operator+(DPOINT point) const;

// Operators returning CDSize values
	CDSize operator-(DPOINT point) const;

// Operators returning CDRect values
	CDRect operator+(const DRECT* lpRect) const;
	CDRect operator-(const DRECT* lpRect) const;
};

/////////////////////////////////////////////////////////////////////////////
// CDRect - A 2-D rectangle

class AFX_EXT_CLASS CDRect : public tagDRECT
{
public:

// Constructors
	CDRect();
	CDRect(double l, double t, double r, double b);
	CDRect(const DRECT& srcRect);
	CDRect(LPCDRECT lpSrcRect);
	CDRect(DPOINT point, DSIZE size);
	CDRect(DPOINT topLeft, DPOINT bottomRight);

// Attributes (in addition to DRECT members)
	double Width() const;
	double Height() const;
	CDSize Size() const;
	CDPoint& TopLeft();
	CDPoint& BottomRight();
	const CDPoint& TopLeft() const;
	const CDPoint& BottomRight() const;
	CDPoint CenterPoint() const;

	// convert between CDRect and LPRECT/LPCDRECT (no need for &)
	operator LPRECTD();
	operator LPCDRECT() const;

	BOOL IsRectEmpty() const;
	BOOL IsRectNull() const;
	BOOL PtInRect(DPOINT point) const;

// Operations
	void SetRect(double x1, double y1, double x2, double y2);
	void SetRect(DPOINT topLeft, DPOINT bottomRight);
	void SetRectEmpty();
	void CopyRect(LPCDRECT lpSrcRect);
	BOOL EqualRect(LPCDRECT lpRect) const;

	void InflateRect(double x, double y);
	void InflateRect(DSIZE size);
	void InflateRect(LPCDRECT lpRect);
	void InflateRect(double l, double t, double r, double b);
	void DeflateRect(double x, double y);
	void DeflateRect(DSIZE size);
	void DeflateRect(LPCDRECT lpRect);
	void DeflateRect(double l, double t, double r, double b);

	void OffsetRect(double x, double y);
	void OffsetRect(DSIZE size);
	void OffsetRect(DPOINT point);
	void NormalizeRect();

	// operations that fill '*this' with result
	BOOL IntersectRect(LPCDRECT lpRect1, LPCDRECT lpRect2);
	BOOL UnionRect(LPCDRECT lpRect1, LPCDRECT lpRect2);
	BOOL SubtractRect(LPCDRECT lpRectSrc1, LPCDRECT lpRectSrc2);

// Additional Operations
	void operator=(const DRECT& srcRect);
	BOOL operator==(const DRECT& rect) const;
	BOOL operator!=(const DRECT& rect) const;

	void operator+=(DPOINT point);
	void operator-=(DPOINT point);
	void operator+=(DSIZE size);
	void operator-=(DSIZE size);
	void operator+=(LPCDRECT lpRect);
	void operator-=(LPCDRECT lpRect);

	void operator+=(POINT point);
	void operator-=(POINT point);
	void operator+=(SIZE size);
	void operator-=(SIZE size);
	void operator+=(LPCRECT lpRect);
	void operator-=(LPCRECT lpRect);

	void operator&=(const DRECT& rect);
	void operator|=(const DRECT& rect);

// Operators returning CDRect values
	CDRect operator+(DPOINT point) const;
	CDRect operator-(DPOINT point) const;
	CDRect operator+(LPCDRECT lpRect) const;
	CDRect operator+(DSIZE size) const;
	CDRect operator-(DSIZE size) const;
	CDRect operator-(LPCDRECT lpRect) const;
	CDRect operator&(const DRECT& rect2) const;
	CDRect operator|(const DRECT& rect2) const;
	CDRect MulDiv(double nMultiplier, double nDivisor) const;
};

#endif // __DOUBLE_GEOM_DEFINED__

//////////////////////////////////////////////////////////////////////
// Konstantendefinitionen

#include	<math.h>

#define	PI	(atan2( 0.0, -1.0 ))
#define	halfPI	(atan2( 0.0, -1.0 ) / 2.0 )
#define	twoPI	(atan2( 0.0, -1.0 ) * 2.0 )

//////////////////////////////////////////////////////////////////////
// (1)	der Punkt

BOOL operator==( const POINT& rP1, const POINT& rP2 );
BOOL operator!=( const POINT& rP1, const POINT& rP2 );

BOOL operator==( const POINTL& rP1, const POINTL& rP2 );
BOOL operator!=( const POINTL& rP1, const POINTL& rP2 );

BOOL operator==( const DPOINT& rP1, const DPOINT& rP2 );
BOOL operator!=( const DPOINT& rP1, const DPOINT& rP2 );

//////////////////////////////////////////////////////////////////////
// (2) Strecke / Linie

class AFX_EXT_CLASS CLine : public CObject
{
	DECLARE_SERIAL( CLine );
	double	m_A, m_B, m_C;
public:
	CLine( );
	CLine( CLine& rLine );
	CLine( CStraith& rStraith );
	CLine( DPOINT& rP1, DPOINT& rP2 );
	CLine( DPOINT& rP, double angle );
	CLine( double x0, double y0, double x1, double y1 );
	CLine( double a, double b, double c );
	
	void	Construct( );
	void	Construct( CLine& rLine );
	void	Construct( CStraith& rStraith );
	void	Construct( DPOINT& rP1, DPOINT& rP2 );
	void	Construct( DPOINT& rP, double angle );
	void	Construct( double x0, double y0, double x1, double y1 );
	void	Construct( double a, double b, double c );

//	CLine( POINTL& rP1, POINTL& rP2 );
//	CLine( POINTL& rP, double angle );
//	void	Construct( POINTL& rP1, POINTL& rP2 );
//	void	Construct( POINTL& rP, double angle );

	const double	A() const;
	const double	B() const;
	const double	C() const;

	CLine&	operator=( CLine& rL );

protected:
	void	Construct( long x0, long y0, double angle );

// Overrides
public:
	virtual	void	Serialize( CArchive& ar );
#ifdef	_DEBUG
	virtual	void	AssertValid( ) const;
	virtual	void	Dump( CDumpContext& dc ) const;
#endif
};

BOOL operator==( CLine& rL1, CLine& rL2 );
BOOL operator!=( CLine& rL1, CLine& rL2 );

class AFX_EXT_CLASS CStraith : public CObject
{
	DECLARE_SERIAL( CStraith );
	DPOINT	m_P0, m_P1;
public:
	CStraith( );
	CStraith( CStraith& rStraith );
	CStraith( DPOINT& rP1, DPOINT& rP2 );
	CStraith( DPOINT& rP, double distance, double angle );
	CStraith( double x0, double y0, double x1, double y1 );

	void	Construct( );
	void	Construct( CStraith& rStraith );
	void	Construct( DPOINT& rP1, DPOINT& rP2 );
	void	Construct( DPOINT& rP, double distance, double angle );
	void	Construct( double x0, double y0, double x1, double y1 );

	const DPOINT	P0( ) const;
	const DPOINT	P1( ) const;

	CStraith& operator=( CStraith& rS );
	
// Overrides
	virtual	void	Serialize( CArchive& ar );
#ifdef	_DEBUG
	virtual	void	AssertValid( ) const;
	virtual	void	Dump( CDumpContext& dc ) const;
#endif
};

BOOL operator==( CStraith& rS1, CStraith& rS2 );
BOOL operator!=( CStraith& rS1, CStraith& rS2 );

class AFX_EXT_CLASS CTriangle : public CObject
{
	DECLARE_SERIAL( CTriangle );
	DPOINT	m_p0, m_p1, m_p2;

// Overrides
public:
	virtual	void	Serialize( CArchive& ar );
#ifdef	_DEBUG
	virtual	void	AssertValid( ) const;
	virtual	void	Dump( CDumpContext& dc ) const;
#endif
};

//////////////////////////////////////////////////////////////////////
// verschiedene Hilfsfunktionen, die nicht unbedingt sinnvoll in
// den Klassen unterzubringen sind

long AFX_EXT_API  froundl( double v );	// Runden; double -> long
short AFX_EXT_API  frounds( double v );	// Runden; double -> short

double AFX_EXT_API  Distance( double X0, double Y0, double X1, double Y1 );
double AFX_EXT_API  Distance( POINT& rP1, POINT& rP2 );
double AFX_EXT_API  Distance( POINTL& rP1, POINTL& rP2 );
double AFX_EXT_API  Distance( DPOINT& rP1, DPOINT& rP2 );

BOOL AFX_EXT_API  CutPoint( POINT& rCutPoint, const CLine& rLine1, const CLine& rLine2 );
BOOL AFX_EXT_API  CutPoint( POINTL& rCutPoint, const CLine& rLine1, const CLine& rLine2 );

BOOL AFX_EXT_API  CutPoint( POINT& rCutPoint, const CStraith& rStraith1, const CStraith& rStraith2 );
BOOL AFX_EXT_API  CutPoint( POINTL& rCutPoint, const CStraith& rStraith1, const CStraith& rStraith2 );

BOOL AFX_EXT_API  CutPoint( POINT& rCutPoint, const CLine& rLine, const CStraith& rStraith );
BOOL AFX_EXT_API  CutPoint( POINTL& rCutPoint, const CLine& rLine, const CStraith& rStraith );

AFX_EXT_API  CStraith&	HalfAngle( CStraith& rS1, CStraith& rS2, LONG length = 100 );

/////////////////////////////////////////////////////////////////////
//	CVector, CMatrix
//	-	Implementierung von Vektoren / Matrizen
/////////////////////////////////////////////////////////////////////

#include	<math.h>
	
class AFX_EXT_CLASS CVector : public CObject
{
friend class CMatrix;
	short	m_r;					// Anzahl an Zeilen
	double	*m_data;				// Zeiger auf die Elemente
	DECLARE_SERIAL(CVector);
public:
	CVector( );
	~CVector( );
	CVector( const short r );
	CVector( const short r, const double *v );

	CVector( const CVector& rV );

	// Attributes
public:	
	const short	R( ) const;				// Anzahl an Zeilen
	double&	operator()( short i );
	const double operator()( short i ) const;

	// Implementation
protected:
	void	Copy( const CVector& rV );
	void	Construct( const short r );

public:
	void		Load( const short nValues, const double *v, short startRow = 0 );
	void		Load( const short nValues, const long *v, short startRow = 0 );
	void		Clear( );

	CVector&	Multiply( const double v );			// Multiplikation mit einer Konstanten

	CVector&	Add( const CVector& rV );			// Addition zweier Vektoren
	double		Multiply( const CVector& rV );			// Skalarprodukt
	
	CVector&	operator=( CVector& rV );

// Serialization
	virtual void Serialize( CArchive& ar );
};

/////////////////////////////////////////////////////////////////////////////
//
//	M[i,j]
//
//	  j --->
//	i m11 m12 m13 m14 m15
//	| m21 m22 m23 m24 m25
//	| m31 m32 m33 m44 ...
//	v m41 m42 m43 .......
//	  ...................
/////////////////////////////////////////////////////////////////////////////

class AFX_EXT_CLASS CMatrix : public CObject
{
	short	m_r;					// Anzahl Zeilen
	short	m_c;					// Anzahl Spalten
	double	*m_data;				// Zeiger auf die Elemente
	DECLARE_SERIAL(CMatrix);
public:
	CMatrix( );
	~CMatrix( );

	CMatrix( short n );				// Konstruktion einer quadratischen Matrix (0-init)
	CMatrix( short n, double *v );			// dito, mit Werten
	CMatrix( short r, short c );
	CMatrix( short r, short c, double *v );

	CMatrix( CMatrix& rM );

	// Attributes
public:
	const short	R( ) const;						// Anzahl Zeilen
	const short	C( ) const;						// Anzahl Spalten
	double&	operator()( short i, short j );		// Zugriff auf Elemente
	const double operator()( short i, short j ) const;

	double	MNorm( );

	// Implementation
protected:
	void	Copy( const CMatrix& rM );
	void	Construct( const short n );
	void	Construct( const short r, const short c );
	
public:
	void		Load( const short nRows, const double *v, short startRow = 0 );
	void		Load( const short nRows, const long *v, short startRow = 0 );
	void		Clear( );

	CMatrix&	Add( const CMatrix& rM );
	CMatrix&	Add( const CMatrix& rM1, const CMatrix& rM2 );
	CMatrix&	Multiply( const double v );								// Multiplitation mit einer Konstanten
	CMatrix&	Multiply( const CMatrix& rM1, const CMatrix& rM2 );		// Multiplikation zweier Matrizen

	int			GaussBanach( CVector& rVC, CVector& rVR );				// Lvsung eines lin. GLS nach Gauss-Banachiewitz
	CVector&	GaussSeidel( const CVector& rV, double eps = 0.05 );	// Lvsung eines lin. GLS nach Gauss-Seidel (iterativ!)

	CMatrix&	operator=( const CMatrix& rM );

// Serialization
	virtual void Serialize( CArchive& ar );
};

/////////////////////////////////////////////////////////////////////////////
// Lösung linearer Gleichungssysteme:
//			rRes * M = rC
//
// (1) Gauss-Banachiewitz (geschlossen)
// (2) Gauss-Seidel (iterativ)

BOOL AFX_EXT_API GaussBanach( CVector& rRes, const CMatrix& rM, const CVector& rC, CMathException *pE = NULL );
BOOL AFX_EXT_API GaussSeidel( CVector& rRes, const CMatrix& rM, const CVector& rC, double eps = 0.05, CMathException *pE = NULL );

/////////////////////////////////////////////////////////////////////////////

class CMathException : public CException
{
	DECLARE_DYNAMIC( CMathException )
public:
	enum {
		none
		, errDIV0
		, errOVERFLOW
	};
	int	m_cause;
	CString	m_strCause;
	CString m_strObject;
#ifdef _DEBUG
	void	Dump( CDumpContext& dc ) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

#ifdef	_AFX_ENABLE_INLINES
#if !defined(_AFX_INLINE)
#define	_AFX_INLINE inline
#endif
#include	"lmfcx/lafx.inl"
#endif

#ifdef _AFXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif

#endif	// __LAFX_H__
