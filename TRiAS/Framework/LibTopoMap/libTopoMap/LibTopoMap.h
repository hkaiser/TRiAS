#ifndef	__LAFX_GEODAET_H__
#define __LAFX_GEODAET_H__

#if !defined(__STL_OSPACE5__)
#error "LibTopoMap benötigt __STL_OSPACE5__"
#endif

#if defined(_DEBUG)
#pragma comment(lib,"libTopoMapD.lib")
#elif defined(_RDEBUG)
#pragma comment(lib,"libTopoMapR.lib")
#else
#pragma comment(lib,"libTopoMap.lib")
#endif

#include "LibTopoMap/LibTopoMapStructs.h"

/////////////////////////////////////////////////////////////////////////
// Transformationsmatrix
// Koeffizienten unskaliert / skaliert
#define	A11(m)	((m).m_matrix[0])
#define	A12(m)	((m).m_matrix[1])
#define	A13(m)	((m).m_matrix[2])
#define	A21(m)	((m).m_matrix[4])
#define	A22(m)	((m).m_matrix[5])
#define	A23(m)	((m).m_matrix[6])
#define	A31(m)	((m).m_matrix[8])
#define	A32(m)	((m).m_matrix[9])
#define	A33(m)	((m).m_matrix[10])

#define	T1(m)	((m).m_matrix[3])
#define	T2(m)	((m).m_matrix[7])
#define	T3(m)	((m).m_matrix[11])

#define	A11_S(m)	((m).m_matrix[0] / (m).m_scale)
#define	A12_S(m)	((m).m_matrix[1] / (m).m_scale)
#define	A13_S(m)	((m).m_matrix[2] / (m).m_scale)
#define	A21_S(m)	((m).m_matrix[4] / (m).m_scale)
#define	A22_S(m)	((m).m_matrix[5] / (m).m_scale)
#define	A23_S(m)	((m).m_matrix[6] / (m).m_scale)
#define	A31_S(m)	((m).m_matrix[8] / (m).m_scale)
#define	A32_S(m)	((m).m_matrix[9] / (m).m_scale)
#define	A33_S(m)	((m).m_matrix[10] / (m).m_scale)

#define	T1_S(m)	((m).m_matrix[3] / (m).m_scale)
#define	T2_S(m)	((m).m_matrix[7] / (m).m_scale)
#define	T3_S(m)	((m).m_matrix[11] / (m).m_scale)

//#define	A41(m)	(m).m_matrix[0]
//#define	A42(m)	(m).m_matrix[1]
//#define	A43(m)	(m).m_matrix[2]
//#define	T4(m)	(m).m_matrix[3]

typedef struct TRANSFORMINFO {
	GEOPOINT	m_origin;
	double		m_matrix[16];
	double		m_scale;
	
	TRANSFORMINFO() : m_scale(1) 
	{
		memset( m_matrix, 0, sizeof(m_matrix) );
	}
} TRANSFORMINFO;

/////////////////////////////////////////////////////////////////////////
// eine topographische Karte
// Die Enumerationen werden mit:
/*
#import "E:\Entwickl\TRIAS200\TRiASCsD.dll" \
	raw_interfaces_only	\
	raw_dispinterfaces	\
	no_implementation	\
	no_namespace
*/
// erzeugt

/////////////////////////////////////////////////////////////////////////////
// Grad-Minuten-Sekunden

#pragma warning( disable : 4270 )

#include <iostream.h>
#include <iomanip.h>
#include <math.h>

struct tagDMSFORMAT {
	LPCTSTR	pszFormat;
	double	val;
	int		prec;
};

IOMANIPdeclare( double );
IOMANIPdeclare( tagDMSFORMAT );

OMANIP(double)			DMS( double coord );
OMANIP(tagDMSFORMAT)	DMS( LPCTSTR pszFormat, double coord, int prec = 0 );

long DMSToL( const long D, const long M, const long S );
void LToDMS( const long lGeoCoord, long& rD, long& rM, long& rS );

inline void LToDMS( double dms, double& rD, double& rM, double& rS ) 
{
	bool	bNeg = dms < 0 ? true : false;
	dms = fabs( dms );
	dms /= 3600; rD = floor( dms ); dms = ( dms - rD ) * 3600;
	dms /= 60;   rM = floor( dms ); dms = ( dms - rM ) * 60;
	rS = dms;
	if( bNeg )
		rD = -rD;
}

inline double DMSToL( const double D, const double M, const double S ) 
{
	return 3600 * D + 60 * M + S;
}

/////////////////////////////////////////////////////////////////////////////
// Parsen von Kartennamen

namespace ParserForASMap {
BOOL ParseMapName( LPCTSTR lpszMapIdent, GEOPOINT& rPt, GEOSIZE& rSz, long& rScale );
BOOL IsMapName( LPCTSTR lpszName, CString& strRealName );
}

namespace ParserForAVMap {
BOOL ParseMapName( LPCTSTR lpszMapIdent, GEOPOINT& rPt, GEOSIZE& rSz, long& rScale );
BOOL IsMapName( LPCTSTR lpszName, CString& strRealName );
}

namespace ParserForNMap {
BOOL ParseMapName( LPCTSTR lpszMapIdent, GEOPOINT& rPt, GEOSIZE& rSz, long& rScale );
BOOL IsMapName( LPCTSTR lpszName, CString& strRealName );
}

BOOL MatchMapName( LPCTSTR lpszMapIdent, LPCTSTR lpszFileName );

//inline const GCP& GCP::operator=( GCP& rSrc ) {
//	m_ptGeoCoord = rSrc.m_ptGeoCoord;
//	m_ptPictPoint = rSrc.m_ptPictPoint;
//	return *this;
//}

/////////////////////////////////////////////////////////////////////////////
// Der folgende Teil ist ist nur mit der MFC zusammen verfügbar
// ... wird bald rausreschmissen

#if defined(__AFXWIN_H__)
typedef struct TOPOMAP {
	CString							m_strIdent;			// Ident (z.B.: TK@AS@N-33-12-A-b)
	CString							m_strName;			// Name (z.B.: N-33-12-A-b)
	CString							m_strSrcPath;
	CString							m_strDstPath;
	CSize							m_sizeOfPicture;
	GCPList							m_listOfGCP;
	TRANSFORMINFO					m_transform;
	enum TRIASCSTYPE				m_csType;
	enum TRIASCSGEODETICDATUM		m_csDatum;
	enum TRIASCSPRIMEMERIDIAN		m_csMeridian;
	enum TRIASCSPROJECTIONALGORITHM	m_csProjection;
} TOPOMAP;

#include <afxtempl.h>

typedef	CArray<GEOPOINT,GEOPOINT&>GPArray;
typedef CArray<GCP,GCP&> CGCPArray;
// typedef CMap<CString,LPCTSTR,CGCPArray*,CGCPArray*&> CGCPMap;

/////////////////////////////////////////////////////////////////////////////
// topographische Karten

typedef enum {
	MPT_INVALID = 0,
	MPT_UNKNOWN	= 1,
	MPT_AS = 2,
	MPT_AS_L = 34,		//  2 + 32 #fje
	MPT_AV = 3,
	MPT_N = 4,
	MPT_N_L = 36,		//  4 + 32 #fje
	MPT_BESSELGK = 5,	// user defined
	MPT_BEGEOD = 6,
	MPT_KRASSGK = 7,
	MPT_KRGEOD = 8,
	MPT_SOE1 = 6	// Soeldner (1)
} TOPOMAPTYPE;

typedef enum {
	COORD_DMS = 0,
	COORD_GK = 1,
	COORD_XY = 2
} COORDTYPE;

typedef struct tagMAPTYPE {
	TOPOMAPTYPE	m_mtType;
	BOOL		m_bHaveParser;
	COORDTYPE	m_coordType;
	LPCTSTR		m_strCtf;		// Coordtransform (DEFAULT, KRGEOD...)
	LPCTSTR		m_strShortName;	// AS, AV, N, ...
	LPCTSTR		m_strLongName;
} MAPTYPE;

extern MAPTYPE mapTypes[];

const MAPTYPE	*GetTypeFromType( TOPOMAPTYPE mapType );
const MAPTYPE	*GetTypeFromName( LPCTSTR strShortName );

class CMapInfo : public CObject {
	TOPOMAPTYPE	m_mapType;		// Blattschnitt
	CString		m_strMapIdent;	// Nomenklatur
	GEOPOINT	m_btmleftOfMap;	// Punkt links unten im jeweiligen System
	GEOSIZE		m_sizeOfMap;	// Ausmaße
	long		m_scale;		// Maßstab
	GPArray		m_geoPoints;
public:
	void AddPoint( GEOPOINT& gp );
	CMapInfo();
	virtual ~CMapInfo();
	void	Clear();

	CString		m_strTifPath;
	CString		m_strBmpPath;
	SIZEL		m_sizeOfPict;
	CGCPArray	m_gcpArray;

	BOOL		SetType( TOPOMAPTYPE mapType );
	BOOL		SetCoord( const GEOPOINT& ptBtmLeft, const GEOPOINT& ptTopRight );
	BOOL		Validate();
	TOPOMAPTYPE	GetType();
	BOOL		SetIdent( LPCTSTR lpszMapIdent );
	CString		GetIdent( );

	GEOPOINT	GetBtmLeft();
	GEOSIZE		GetSize();
	long		GetScale();
	CMapInfo& operator=( CMapInfo& rSrcInfo );
};

inline CMapInfo::CMapInfo()
	{ Clear(); }
inline TOPOMAPTYPE CMapInfo::GetType()
	{ return m_mapType; }
inline CString CMapInfo::GetIdent()
	{ return m_strMapIdent; }
inline GEOPOINT CMapInfo::GetBtmLeft()
	{ return m_btmleftOfMap; }
inline GEOSIZE CMapInfo::GetSize()
	{ return m_sizeOfMap; }
inline long CMapInfo::GetScale()
	{ return m_scale; }

inline void CMapInfo::AddPoint( GEOPOINT& gp )
	{ m_geoPoints.Add( gp ); }

#endif //__AFXWIN_H__

#ifdef __AFXWIN_H__

/////////////////////////////////////////////////////////////////////////////
// interaktiver Suchbaum

//class CTreeCtrl
	class CMapTreeCtrl;

class CMapTreeCtrl : public CTreeCtrl {
	// Construction
public:
	CMapTreeCtrl();

	CString		m_strMapIdent;
	TOPOMAPTYPE	m_mapType;

	GEOPOINT	m_ptBtmLeft;
	GEOSIZE	m_szMap;
	long	m_scale;

// Attributes
public:

// Operations
public:
	void	MoveWindow( int x, int y, int nWidth, int nHeight, BOOL bRepaint = TRUE );
	void	MoveWindow( LPCRECT lpRect, BOOL bRepaint = TRUE );

protected:
	friend void DDX_Control(CDataExchange* pDX, int nIDC, CMapTreeCtrl& rControl);
	void	InitTree();
	void	ExpandASMap( HTREEITEM hTreeItem, int iFromLevel );
	void	ExpandAVMap( HTREEITEM hTreeItem, int iFromLevel );
	void	ExpandNMap( HTREEITEM hTreeItem, int iFromLevel );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapTreeCtrl)
	public:
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMapTreeCtrl();
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CMapTreeCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
#ifdef DEBUG
	virtual	void	AssertValid( ) const;
#endif
};

void DDX_Control(CDataExchange* pDX, int nIDC, CMapTreeCtrl& rControl);

#include "libTopoMap/AscFile.h"
#include "libTopoMap/AscIO.h"

/////////////////////////////////////////////////////////////////////////////

#endif // __AFXWIN_H__

#endif // __LAFX_GEODAET_H__
