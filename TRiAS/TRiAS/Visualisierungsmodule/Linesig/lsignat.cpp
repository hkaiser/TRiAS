#include "stdafx.h"
#include "LinesigImpl.h"

#include "lsignat.h"
#include "lsigppg.h"
#include "metafile.h"
#include "PgError.h"
#include "ctype.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////

#define	new	DEBUG_NEW

IMPLEMENT_DYNAMIC( CLineResource, CObject )
IMPLEMENT_DYNCREATE(CLineSigCtrl, CTriasVMD)
IMPLEMENT_OLETYPELIB(CLineSigCtrl, _tlid, _wVerMajor, _wVerMinor)

const CString StrToASCII( LPCTSTR lpszString ) {
	CString	S;
	for( ; *lpszString; lpszString++ ) {
		S += isascii(*lpszString) ? *lpszString : '#';
	}
	return S;
}

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CLineSigCtrl, CTriasVMD)
	//{{AFX_MSG_MAP(CLineSigCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
//	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CLineSigCtrl, CTriasVMD)
	//{{AFX_DISPATCH_MAP(CLineSigCtrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CLineSigCtrl, CTriasVMD)
	//{{AFX_EVENT_MAP(CLineSigCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()

/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CLineSigCtrl, 1)
	PROPPAGEID(CLinesigPropPage::guid)
END_PROPPAGEIDS(CLineSigCtrl)

/////////////////////////////////////////////////////////////////////////////
// Interface Maps

BEGIN_INTERFACE_MAP(CLineSigCtrl, CTriasVMD)
	INTERFACE_MAP_VISMODULE(CLineSigCtrl)
END_INTERFACE_MAP()

IMPLEMENT_VISMOD_INTERFACE(CLineSigCtrl)

/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid
// 07963892-3123-101C-BB62-00AA0018497C	- Liniensignaturen

IMPLEMENT_OLECREATE_EX(CLineSigCtrl, _T( "TRiAS.VMLineSig.1" ),
	0x07963892L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C)

/////////////////////////////////////////////////////////////////////////////
//  Event dispatch interface for CLineSigCtrl

//	[ uuid(51C39830-04B2-11d0-AC38-00A024145748),
const IID BASED_CODE IID_DLinesig =
	{ 0x51C39830, 0x04B2, 0x11d0, { 0xAC, 0x38, 0x00, 0xa0, 0x24, 0x14, 0x57, 0x48 } };

//	[ uuid(51C39831-04B2-11d0-AC38-00A024145748),
const IID BASED_CODE IID_DLinesigEvents =
	{ 0x51C39831, 0x04B2, 0x11d0, { 0xAC, 0x38, 0x00, 0xa0, 0x24, 0x14, 0x57, 0x48 } };

/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwLinesigOleMisc =
	OLEMISC_INVISIBLEATRUNTIME |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CLineSigCtrl, IDS_LINESIG, _dwLinesigOleMisc)

/////////////////////////////////////////////////////////////////////////////
// CLineSigCtrl::CKartenCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CLineSigCtrl

static LPCTSTR g_szTKLongName = TEXT( "Spezielle Liniensignaturen\nlinesig" );

LPCTSTR CLineSigCtrl::GetProgIdent()		// liefert ProgIdent "TRiAS.VM...."
	{ return _T("TRiAS.VMLineSig.1"); }

BOOL CLineSigCtrl::CLineSigCtrlFactory::UpdateRegistry(BOOL bRegister) {
	if( bRegister )
		return VMDRegister( AfxGetInstanceHandle(), m_clsid, m_lpszProgID, g_szTKLongName, OTLinie );
	else
		return VMDUnRegister( m_clsid, m_lpszProgID );
}

/////////////////////////////////////////////////////////////////////////////
// CLineSigCtrl::DoPropExchange - Persistence support

void CLineSigCtrl::DoPropExchange(CPropExchange* pPX) {
//	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
//	CTriasVMD::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}

/////////////////////////////////////////////////////////////////////////////
// CLineSigCtrl::OnResetState - Reset control to default state

void CLineSigCtrl::OnResetState() {
//	CTriasVMD::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}

/////////////////////////////////////////////////////////////////////////////

CLineResource::CLineResource( UINT nID, UINT nDefaultWidth ) {
	m_nResrcID = nID;
	m_nDefaultWidth = nDefaultWidth;
}

CLineSigCtrl::CLineSigCtrl( ) : CTriasVMD( ) {
	InitializeIIDs(&IID_DLinesig,&IID_DLinesigEvents);
	m_maxCoords = 0;
	m_R = NULL;
	m_H = NULL;
	m_scale = 100;
	m_arc = 0;
	m_bMarkSegments = FALSE;
	m_bClipExtended = TRUE;
	LoadSignatures( );
}

CLineSigCtrl::~CLineSigCtrl( ) {
	if( m_maxCoords > 0 && NULL != m_R )
		delete m_R;
	if( m_maxCoords > 0 && NULL != m_H )
		delete m_H;

	MetafileMap::const_iterator i;
	CMetaFile	*pMF;
	int n = m_mapOfSignatures.size();
	for( i = m_mapOfSignatures.begin(); i != m_mapOfSignatures.end(); ++i ) {
		pMF = (*i).second;
		if( NULL != pMF ) {
			ASSERT_VALID( pMF );
			delete pMF;
			pMF = NULL;
		}
	}
	m_mapOfSignatures.erase(m_mapOfSignatures.begin(), m_mapOfSignatures.end());
}

BOOL CLineSigCtrl::LoadSignatures( ) {
	CString		strSigname;
	CStringArray	arrError;
	CStringArray	parserLog;
	long		nID, nLastID;
	HRSRC		hResrc;
	HGLOBAL		hGlobal;
	CMetaFile	*pMF = NULL;
	int			showErr = 1;
	BOOL		bClipDefault = TRUE;

	COleVariant	v;
	if( REG_DWORD == GetRegistryValue( _T("ShowError"), v ) ) {
		showErr = (int) v.lVal;
	}
	if( REG_DWORD == GetRegistryValue( _T("ClipDefault"), v ) ) {
		bClipDefault = v.lVal ? TRUE : FALSE;
	}
	if( REG_DWORD == GetRegistryValue( _T("MarkSegments"), v ) ) {
		m_bMarkSegments = (int) v.lVal;
	}
	if( REG_DWORD == GetRegistryValue( _T("ClipExtended"), v ) ) {
		m_bClipExtended = v.lVal ? TRUE : FALSE;
	}

	VERIFY( hResrc = ::FindResource( AfxGetResourceHandle(), MAKEINTRESOURCE( 255 ), "LINESIG" ) );
	strSigname = (char FAR*) ::LockResource( hGlobal = ::LoadResource( AfxGetResourceHandle(), hResrc ) );
	::FreeResource( hGlobal );

	::LAfxExtractSubLong( nID, strSigname, 0, ';' );
	::LAfxExtractSubLong( nLastID, strSigname, 1, ';' );

	for( ; nID <= nLastID; nID++ ) {
		if( NULL == pMF )
			pMF = new CMetaFile( );
		if( pMF->Create( (UINT) nID ) ) {
			if( pMF->Parse( &parserLog ) ) {
				strSigname = StrToASCII( pMF->GetName() );
				if( m_mapOfSignatures.end() == m_mapOfSignatures.find( strSigname ) ) {
					m_mapOfSignatures[strSigname] = pMF;
					pMF->ClipDefault( bClipDefault );
					parserLog.Add(_T("--------------------------\n"));
					pMF = NULL;
				} else {
					strSigname = _T("doppelter Signaturbezeichner: ");
					strSigname += pMF->GetIdent();
					arrError.Add( strSigname );
					delete pMF;
					pMF = NULL;
				}
			}
		}
	}
	if( showErr && 0 != arrError.GetSize() ) {
		CPgError	pgError( &arrError );
		CPropertySheet	dlg( IDS_LINESIG_ERROR );
		dlg.AddPage( &pgError );
		dlg.DoModal();
	}
//#ifdef _DEBUG
//	CStdioFile	f( "parse.txt", CFile::modeCreate | CFile::modeWrite | CFile::typeText );
//	for( int i = 0; i < parserLog.GetSize(); ++i ) {
//		f.WriteString(parserLog.GetAt(i));
//	}
//#endif
	return TRUE;
}

void CLineSigCtrl::DeleteContents( ) {
	CTriasVMD::DeleteContents( );
}

/////////////////////////////////////////////////////////////////////////////
//

BOOL CLineSigCtrl::OnProjectOpen( LPCTSTR pszNewProject )
	{ return CTriasVMD::OnProjectOpen( pszNewProject ); }

void CLineSigCtrl::OnProjectClose( )
	{ CTriasVMD::OnProjectClose(); }

BOOL CLineSigCtrl::OnViewOpen( LPCTSTR lpszView )
	{ return CTriasVMD::OnViewOpen( lpszView ); }

void CLineSigCtrl::OnViewClose( )
	{ CTriasVMD::OnViewClose( ); }

BOOL CLineSigCtrl::OnChangePalette( CDC *pDC, HPALETTE hPal )
	{ return TRUE; }

BOOL CLineSigCtrl::OnDrawObject(
						CDC *pDC,
						CDC *pTarget,
						const DWORD lObjNr,
						class VisInfo* pVI,
						LPCTSTR pszVisString,
						short& fDrawFlags )
{
	CString	strSigname;
	CDRect	dstRect;
	BOOL	swapX, swapY;
	long	dx, dy;
	int	i;
	
	if( !ParseVisInfoString( pszVisString, strSigname, dx, dy, dstRect, swapX, swapY ) )
		return FALSE;

	CMetaFile	*pMF;
	strSigname = StrToASCII( strSigname );

	if( m_mapOfSignatures.end() == m_mapOfSignatures.find( strSigname ) )
		return FALSE;
	pMF = m_mapOfSignatures[strSigname];

	ASSERT_KINDOF( CMetaFile, pMF );

	CDSize	dpm = GetDotsPerMM( pDC );

	dstRect.left	=  ( ( dstRect.left   * dpm.cx ) / ( m_activeScaling * 100 ) );
	dstRect.top		= -( ( dstRect.top    * dpm.cy ) / ( m_activeScaling * 100 ) );
	dstRect.right	=  ( ( dstRect.right  * dpm.cx ) / ( m_activeScaling * 100 ) );
	dstRect.bottom	= -( ( dstRect.bottom * dpm.cy ) / ( m_activeScaling * 100 ) );
	
	if( fabs( dstRect.Width() ) < 2 || fabs( dstRect.Height() ) < 2 )
		return FALSE;

	OBJSTATISTIK	S;
	INITSTRUCT( S, S );

	S.lONr		= lObjNr;
	DEX_GetObjStatistik( S );

	if( ( OGLinie != S.iObjTyp && OGFlaeche != S.iObjTyp ) || 0 == S.lCnt )
		return FALSE;

	///////////////////////////////////////////////////////////////////////////
	// Koordinatenliste für die Linie aufbauen

	GetCoordBuffers( (short) S.lCnt );
	
	OBJGEOMETRIE	G;
	INITSTRUCT( G, G );
	G.lONr	= lObjNr;
	G.lCnt	= S.lCnt;
	G.pdblX	= (void*) m_R;
	G.pdblY	= (void*) m_H;
	DEX_GetObjGeometrie( G );

	POINTL			ptC;										// Koordinatenpunkt
	POINT			ptDC;									// Punkte im DC
	COORDCONVERT	C;
	CPointArray		ptList;

	ptList.SetSize( 0, (int) max( S.lCnt / 4, 20 ) );

	C.lpPt	= &ptDC;
	C.lpPkt	= (long*) &ptC;

	for( i = 0; i < S.lCnt; i++ ) {
		ptC.x = m_R[i];
		ptC.y = m_H[i];
		DEX_OCtoDCEx( C );
		ptList.Add( ptDC );
	}

	///////////////////////////////////////////////////////////////////////////
	// und abspielen entlang der Koordinatenliste

	double	scale = ( (double) m_scale ) / 100;
	double	arc = ( (double) m_arc ) / 100;

	dstRect.left   *= scale;
	dstRect.top    *= scale;
	dstRect.bottom *= scale;
	dstRect.right  *= scale;

	CPalette 	*pPalOfDC = pDC->GetCurrentPalette();

	COLORREF	rgb = (COLORREF) pVI->PrimColor();
	
	// 's sind neue Farben da...
	if( ::LAfxMergePalette( pPalOfDC, &rgb ) > 0 ) {
		pDC->SelectPalette( pPalOfDC, FALSE );
		pDC->RealizePalette( );
	}
	pMF->BrushColor( rgb );
	pMF->ClipExtended( m_bClipExtended );
	pMF->MarkSegments( m_bMarkSegments );
	return pMF->Play( pDC, CPoint( dx, dy ), dstRect, ptList, swapX, swapY );
}

BOOL CLineSigCtrl::ParseVisInfoString( LPCTSTR pszVisString, CString& sigName, long& rDX, long& rDY, CDRect& rc, BOOL &swapX, BOOL& swapY ) {
	long	l, t, r, b;
	BOOL	res = ParseVisInfoString( pszVisString, sigName, rDX, rDY, l, t, r, b, swapX, swapY );
	rc.left = l;
	rc.top = t;
	rc.right = r;
	rc.bottom = b;
	return res;
}

BOOL CLineSigCtrl::ParseVisInfoString( LPCTSTR pszVisString, CString& sigName, long& dx, long& dy, long& l, long& t, long& r, long& b, BOOL &swapX, BOOL& swapY ) {
	CString		S;
	long	s;
	BOOL		res = TRUE;
	
	res = res && ::AfxExtractSubString( sigName, pszVisString, 0, ';' );
	res = res && ::AfxExtractSubString( S, pszVisString, 1, ';' );
		if( !::LAfxExtractSubLong( dx, S, 0, ',' ) )
			dx = 0;
		if( !::LAfxExtractSubLong( dy, S, 1, ',' ) )
			dy = 0;

	res = res && ::LAfxExtractSubLong( l, pszVisString, 2, ';' );	// w = minmax( w, MIN_WIDTH, MAX_WIDTH );
	res = res && ::LAfxExtractSubLong( t, pszVisString, 3, ';' );	// h = minmax( h, MIN_HEIGHT, MAX_HEIGHT );

	res = res && ::LAfxExtractSubLong( r, pszVisString, 4, ';' );	// x = minmax( x, MIN_XOFFSET, MAX_XOFFSET );
	res = res && ::LAfxExtractSubLong( b, pszVisString, 5, ';' );	// y = minmax( y, MIN_YOFFSET, MAX_YOFFSET );

	res = res && ::LAfxExtractSubLong( s, pszVisString, 6, ';' );	swapX = s > 0L ? TRUE : FALSE;
	res = res && ::LAfxExtractSubLong( s, pszVisString, 7, ';' );	swapY = s > 0L ? TRUE : FALSE;
	return res;
}

BOOL CLineSigCtrl::GetCoordBuffers( short coordCnt ) {
	if( coordCnt > m_maxCoords ) {
		if( NULL != m_R ) delete m_R;
		if( NULL != m_H ) delete m_H;
		m_R = NULL;
		m_H = NULL;
	}
	if( NULL == m_R && NULL == m_H ) {
		m_R = (long*) new char[ coordCnt * sizeof( long ) ];
		m_H = (long*) new char[ coordCnt * sizeof( long ) ];
		m_maxCoords = coordCnt;
	}
	return NULL != m_R && NULL != m_H;
}

const CDSize GetDotsPerMM( CDC* pDC ) {
	CDSize	szRes( pDC->GetDeviceCaps( HORZRES ), pDC->GetDeviceCaps( VERTRES ) );
	CDSize	szSiz( pDC->GetDeviceCaps( HORZSIZE ), pDC->GetDeviceCaps( VERTSIZE ) );

	switch ( pDC->GetMapMode () ) {
	default:							// MM_ANISOTROPIC/MM_ISOTROPIC
	case MM_TEXT:						// der bisherige Stand
		return CDSize( szRes.cx / szSiz.cx, szRes.cy / szSiz.cy );
	case MM_HIMETRIC:					// [0.01 mm]
		return CDSize( 100, 100 );
	case MM_LOMETRIC:					// [0.1 mm]
		return CDSize( 10, 10 );
	case MM_HIENGLISH:					// [0.001 inch]
		return CDSize( 40, 40 );
	case MM_LOENGLISH:					// [0.01 inch]
		return CDSize( 4, 4 );
	case MM_TWIPS:
		return CDSize( 57, 57 );
	}
}
