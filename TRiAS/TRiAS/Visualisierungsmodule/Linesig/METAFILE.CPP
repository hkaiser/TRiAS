#include	"stdafx.h"
#include	"metafile.h"
#include	<limits.h>
#include	<ctype.h>
#include	<math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC( CMetaFile, CObject )

#define	new	DEBUG_NEW

CMetaFile::CMetaFile( ) {
	m_hSrcMF = NULL;
	m_hMemMF = NULL;
	m_bMarkSegments = FALSE;
	m_bClipDefault = TRUE;
	m_bClipExtended = TRUE;

	m_lpEnumParseMetaProc = (MFENUMPROC) EnumOnParse;
	m_lpEnumDrawMetaProc = (MFENUMPROC) EnumOnDraw;

#if defined(_DEBUG) || defined(_RDEBUG)
	InitDebug( );
#endif
}

CMetaFile::~CMetaFile( ) {
	if( NULL != m_hMemMF ) ::DeleteMetaFile( m_hMemMF );
	if( NULL != m_hSrcMF ) ::DeleteMetaFile( m_hSrcMF );

#if defined(_DEBUG) || defined(_RDEBUG)
	DeInitDebug( );
#endif	
}

BOOL CMetaFile::Create( const char *pszFileName ) {
	HFILE	hFile = ::_lopen( pszFileName, OF_READ );
	if( HFILE_ERROR == hFile )
		return FALSE;
	long	nBytes = ::_llseek( hFile, 0L, 2 );
	HGLOBAL	hMem = ::GlobalAlloc( GMEM_DISCARDABLE | GMEM_MOVEABLE, nBytes );
	HPBYTE pData = (HPBYTE) ::GlobalLock( hMem );
	::_llseek( hFile, 0L, 0 );
	::_lread( hFile, (HPVOID) pData, (UINT) nBytes );
	::_lclose( hFile );
	BOOL ret = Create( pData, nBytes );
	::GlobalUnlock( hMem );
	::GlobalFree( hMem );
	return ret;
}

BOOL CMetaFile::Create( UINT nResrcID ) {
	HRSRC	hResrc = ::FindResource( AfxGetResourceHandle(), MAKEINTRESOURCE( nResrcID ), "LINESIG" );

	if( NULL == hResrc )
		return FALSE;

	DWORD	nBytes = ::SizeofResource( AfxGetResourceHandle(), hResrc );
	HGLOBAL	hData = ::LoadResource( AfxGetResourceHandle(), hResrc );
	HPBYTE	pData = (HPBYTE) ::LockResource( hData );			// ::GlobalLock( hData );
	BOOL ret = Create( pData, nBytes );
	UnlockResource( hData );	// ::GlobalUnlock( hData )
	::FreeResource( hData );	// ::GlobalFree( hData );

	return ret;
}

BOOL CMetaFile::Parse( CStringArray *pParserLog /*=NULL*/ ) {
	if( NULL == m_hSrcMF )
		return FALSE;

	if( NULL != m_hMemMF )
		::DeleteMetaFile( m_hMemMF );

	m_metaParam.Init();
	m_metaParam.m_pStrSigname = &m_strIdent;

#if defined(_RDEBUG)
	CString	strFormat;
	m_metaParam.pObject		= this;
	m_metaParam.m_pStrings = pParserLog;
	m_metaParam.m_pStrFormat = &strFormat;
#endif
	CDC			metaDC;
	metaDC.Attach( ::CreateMetaFile( NULL ) );
	::EnumMetaFile( metaDC.GetSafeHdc( ), m_hSrcMF, m_lpEnumParseMetaProc, (LPARAM) &m_metaParam );
	m_hMemMF = ::CloseMetaFile( metaDC.Detach( ) );
#if defined(_RDEBUG)
	if( pParserLog ) {
		strFormat.Format(_T("* Offset [%d,%d]\n* m_rcWBound [%d,%d,%d,%d]\n* m_rcFBound [%d,%d,%d,%d]\n* m_rcBound [%d,%d,%d,%d]\n")
			, m_metaParam.m_ptParseOffsetX, m_metaParam.m_ptParseOffsetY
			, m_metaParam.m_rcWBound.left, m_metaParam.m_rcWBound.top, m_metaParam.m_rcWBound.right, m_metaParam.m_rcWBound.bottom
			, m_metaParam.m_rcFBound.left, m_metaParam.m_rcFBound.top, m_metaParam.m_rcFBound.right, m_metaParam.m_rcFBound.bottom
			, m_metaParam.m_rcBound.left, m_metaParam.m_rcBound.top, m_metaParam.m_rcBound.right, m_metaParam.m_rcBound.bottom
			);
		pParserLog->Add( strFormat );
	}
#endif
	if( !::IsRectEmpty( &m_metaParam.m_rcFBound ) ) {
		m_metaParam.m_rcBound =  m_metaParam.m_rcFBound;
	} else {					// wir nehmen an, daß das Bild immer an der linken Kante beginnt
		m_metaParam.m_rcBound.left	= 0;
	}
#if defined(_RDEBUG)
	if( pParserLog ) {
		strFormat.Format(_T("* m_rcBound\' [%d,%d,%d,%d]\n")
			, m_metaParam.m_rcBound.left, m_metaParam.m_rcBound.top, m_metaParam.m_rcBound.right, m_metaParam.m_rcBound.bottom
			);
		pParserLog->Add( strFormat );
	}
#endif

	if( !::AfxExtractSubString( m_strName, m_strIdent, 0, ';' ) )
		return FALSE;
	m_metaParam.m_bReplaceColor = _T("Liniensignatur") == m_strName ? FALSE : TRUE;
#if defined(_RDEBUG)
	m_metaParam.m_pStrings = NULL;
	m_metaParam.m_pStrFormat = NULL;
#endif
	return TRUE;
}

void METAENUMPARAM::Init() {
	memset( (void FAR*) this, 0x00, sizeof( *this ) );
	m_rcBound.top = SHRT_MAX;
	m_rcBound.left	= SHRT_MAX;
	m_rcBound.bottom	= SHRT_MIN;
	m_rcBound.right	= SHRT_MIN;
	ReInit();
}

void METAENUMPARAM::ReInit() {
	memset( m_gdiObjects, 0x00, sizeof( m_gdiObjects ) );
	m_BSelected = -1;
	m_PSelected = -1;
	m_FSelected = -1;
}


void METAENUMPARAM::CalculateTransformMatrix( double phi ) {
	m_r11 = m_r22 = cos( phi );
	m_r12 = m_r21 = sin( phi );
	m_r21 = -m_r21;
}

void METAENUMPARAM::TransformPoint( short& x, short& y ) {
	double	x11, x22;

	x11 = m_offsetPictX + x;
	x22 = m_offsetPictY + y;
	x11 *= m_zx;
	x22 *= m_zy;
/*
	x11 = (double) x * m_zx;
	x22 = (double) y * m_zy;
	x11 += m_offsetPictX;
	x22 += m_offsetPictY;
*/
	x = frounds( m_r11 * x11 + m_r21 * x22 + m_offsetDrawX );
	y = frounds( m_r12 * x11 + m_r22 * x22 + m_offsetDrawY );
}

void CMetaFile::BrushColor( COLORREF rgbBrush ) {
	m_metaParam.m_rgbBrush = rgbBrush;
}

const CRect CMetaFile::GetFigureRect( ) {
	static CRect R;
	R.SetRect( m_metaParam.m_rcBound.left, m_metaParam.m_rcBound.top, m_metaParam.m_rcBound.right, m_metaParam.m_rcBound.bottom);
	return R;
}

int _matherr( struct _exception *except ) {
	CString	S;
	S.Format( "Fehler in mathematischer Funktion: %s\ndx: %f\ndy:%f", except->name, except->arg1, except->arg2 );
//	AfxMessageBox( S );
	return 1;
}

BOOL CMetaFile::Play( CDC* pDC, CDRect& dstRect, CPoint *pPtDraw, BOOL swapX, BOOL swapY ) {
	m_metaParam.m_offsetPictX = m_metaParam.m_offsetPictY = 0;
	m_metaParam.m_offsetDrawX = pPtDraw->x;
	m_metaParam.m_offsetDrawY = ( dstRect.bottom + dstRect.top ) / 2;

	m_metaParam.ReInit();
	m_metaParam.m_bSwapX 	= swapX;
	m_metaParam.m_bSwapY 	= swapY;
	m_metaParam.m_bClip = FALSE;

#if defined(_RDEBUG)
	m_metaParam.m_pStrings = NULL;
	m_metaParam.m_pStrFormat = NULL;
#endif

	CRect	rectWmf = GetFigureRect( );

	m_metaParam.m_zx = (double) dstRect.Width() / (double) rectWmf.Width();
	m_metaParam.m_zy = (double) dstRect.Height() / (double) rectWmf.Height();

	m_metaParam.CalculateTransformMatrix( 0 );
	::EnumMetaFile( pDC->GetSafeHdc( ), m_hMemMF, m_lpEnumDrawMetaProc, (LPARAM) &m_metaParam );
	return TRUE;
}

double CMetaFile::PlaySegment( CDC *pDC, CRect &rcClipDC, SEGMENT &segCurr ) {
	CRgn		clipRgn;
	CDPoint		ptDraw;
	double		lengthDrawn = 0;			// die auf der Strecke gezeichnete Länge
	CMetaMemory	m;

	segCurr.CreateClipRgn( pDC, clipRgn );

	ptDraw = segCurr.P0();
	m_metaParam.CalculateTransformMatrix( segCurr.Phi() );

	lengthDrawn = m_metaParam.m_offsetPictX;

	m_metaParam.m_pMetaMemory = &m;
	m_metaParam.m_bClip = m_bClipExtended;

	m_metaParam.m_dx1L = segCurr.ClipPoint(2).x - segCurr.ClipPoint(0).x;
	m_metaParam.m_dy1L = segCurr.ClipPoint(2).y - segCurr.ClipPoint(0).y;
	m_metaParam.m_x2L = segCurr.ClipPoint(2).x;
	m_metaParam.m_y2L = segCurr.ClipPoint(2).y;
	m_metaParam.m_dx1R = segCurr.ClipPoint(3).x - segCurr.ClipPoint(5).x;
	m_metaParam.m_dy1R = segCurr.ClipPoint(3).y - segCurr.ClipPoint(5).y;
	m_metaParam.m_x2R = segCurr.ClipPoint(3).x;
	m_metaParam.m_y2R = segCurr.ClipPoint(3).y;
	do {
		m_metaParam.ReInit();
		m_metaParam.m_offsetDrawX = ptDraw.x;
		m_metaParam.m_offsetDrawY = ptDraw.y;
		m_metaParam.m_nObjects	= 0;
		m_metaParam.m_BSelected = -1;
		m_metaParam.m_PSelected = -1;

		if( m_bClipDefault ) {
			pDC->SelectClipRgn( &clipRgn );
			pDC->IntersectClipRect( &rcClipDC );
		}

		::EnumMetaFile( pDC->GetSafeHdc( ), m_hMemMF, m_lpEnumDrawMetaProc, (LPARAM) &m_metaParam );

		if( TRUE == m_bMarkSegments )
			::MarkPoint( pDC, ptDraw, RGB( 255, 255, 255 ), 1 );
		ptDraw.x += segCurr.m_dx;
		ptDraw.y += segCurr.m_dy;
		lengthDrawn += segCurr.Width();
	} while( lengthDrawn < segCurr.Length() );
	m_metaMemory.ImportObjects( pDC, clipRgn, m );
	m_metaParam.m_pMetaMemory = NULL;
	clipRgn.DeleteObject( );
	pDC->SelectClipRgn( NULL );
	return lengthDrawn;
}

BOOL CMetaFile::Play( CDC* pDC, const CPoint& rPtOffset, CDRect& dstRect, CPointArray& ptList, BOOL swapX, BOOL swapY  ) {
	if( ptList.GetSize( ) < 2 )
		return FALSE;

	CRect		rcClipDC;
	CRect		R2, R1;
	double		length = 0;
	double		lengthDrawn = 0;			// die auf der Strecke gezeichnete Länge
	double		phiDiffMin, phiDiff, phiDiffAbs;
	POINT		theLastPoint;
	int			nPoint, nPoints;

#if defined (_RDEBUG)
	CStringArray	Strings;
	CString			strFormat;
	m_metaParam.m_pStrings = &Strings;
	m_metaParam.m_pStrFormat = &strFormat;
#endif

	//////////////////////////////////////////////////////////
	// wir basteln ein bischen am DC rum ;-)

	int savedDC = pDC->SaveDC();
	pDC->GetClipBox( &rcClipDC );

	CPoint	pt = pDC->GetWindowOrg( );
	CSize	sz = pDC->GetWindowExt( );

	CRect	winRect( pDC->GetWindowOrg( ), pDC->GetWindowExt( ) );

	winRect.SetRect( pt.x, pt.y, pt.x + sz.cx, pt.y + abs( sz.cy ) );
	winRect.NormalizeRect( );

	m_metaParam.m_zx = (double) dstRect.Width() / (double) GetFigureRect( ).Width();
	m_metaParam.m_zy = (double) dstRect.Height() / (double) GetFigureRect( ).Height();

	double	off = (double) ( m_metaParam.m_rcBound.right - m_metaParam.m_rcBound.left );
	off *= (double) rPtOffset.x;
	off /= 100;

	m_metaParam.m_offsetPictX = -frounds(off);
	m_metaParam.m_offsetPictY = ( dstRect.bottom + dstRect.top ) / 2;

	// am Ende der Punktliste einen zusätzlichen Punkt anhängen, der genau 
	// in Richtung der letzten Strecke liegt, um das letzte Segment sauber zu zeichnen

	POINT	PP0;
	for( nPoint = 0; nPoint < ptList.GetSize(); nPoint++ ) {
		PP0 = ptList[nPoint];
	}

	theLastPoint.x = 2 * ptList[ ptList.GetSize() - 1 ].x - ptList[ ptList.GetSize() - 2 ].x;
	theLastPoint.y = 2 * ptList[ ptList.GetSize() - 1 ].y - ptList[ ptList.GetSize() - 2 ].y;
	ptList.Add( theLastPoint );

	SEGMENT	segCurr( dstRect );
	SEGMENT	segNext( dstRect );
//	segTmp.Construct( dstRect );

	segNext.Construct( CDPoint( ptList[0].x, ptList[0].y ), CDPoint( ptList[1].x, ptList[1].y ) );

	phiDiffMin = ( 0 * PI ) / 180;

	nPoints = ptList.GetSize( );

	m_metaMemory.Reset();

	for( nPoint = 2; nPoint < nPoints; nPoint++ ) {
		segCurr = segNext;
		length += segCurr.Length();

		segNext.Construct( segCurr.P1(), ptList[nPoint] );

		R1.SetRect(
			frounds( segCurr.P0().x ),
			frounds( segCurr.P0().y ),
			frounds( segCurr.P1().x ),
			frounds( segCurr.P1().y )
			);
		R1.NormalizeRect( );
		R1.InflateRect( 5, 5 );

		if( R2.IntersectRect( &R1, &winRect ) ) {		//  Zeichnen nur, wenn Strecke (auch nur teilweise) sichtbar
#if defined(_RDEBUG)
			CString	S;
			S.Format( "(%03d) %.5f %.5f\n", nPoint - 2, segCurr.Width(), lengthDrawn );
			Strings.Add(S);
#endif
			phiDiff = segNext.Phi() - segCurr.Phi();
			phiDiffAbs = fabs( phiDiff );

			///////////////////////////////////////////////////////
			// solange die Gesamtwinkeldifferenz der Teilstrecken
			// kleiner ist als Mindestdifferenz, nächstes Segment
			// suchen

/*
			while( phiDiffAbs < phiDiffMin && nPoint < nPoints - 1 ) {
				if( 0 != m_nMark )
					::MarkPoint( pDC, segCurr.P1() );

				segCurr.Construct( segCurr.P0(), ptList[nPoint++] );
				nPoint++;
				segNext.Construct( segCurr.P1(), ptList[nPoint] );
				phiDiff += ( segNext.Phi() - segCurr.Phi() );
				phiDiffAbs = fabs( phiDiff );
			}
*/
			segCurr.Clip( segNext );

/*
			if( phiDiffAbs < halfPI )
			else if( PI - phiDiffAbs < 0.35 )
				segCurr.AddClip( PI - phiDiffAbs );
				segCurr.Clip( segNext );
			else
			{
				segTmp = segNext;
				segTmp.Rotate( halfPI + ( PI - phiDiff ) / 2 );
				segTmp.Offset( -( segTmp.P1().x - segTmp.P0().x ) / 2, -( segTmp.P1().y - segTmp.P0().y ) / 2 );
				if( FALSE != m_bMark )
					segTmp.Mark( pDC );
				segCurr.Clip( segTmp );
			}
*/
			if( TRUE == m_bMarkSegments )
				segCurr.Mark( pDC );
			lengthDrawn = PlaySegment( pDC, rcClipDC, segCurr );
		} else {			// ansonsten nur hochzählen
			for( lengthDrawn = m_metaParam.m_offsetPictX; lengthDrawn < segCurr.Length(); lengthDrawn += segCurr.Width() )
				;
		}
		m_metaParam.m_offsetPictX = -fmod( length, segCurr.Width() );
	}

#if defined(_RDEBUG)
	if( NULL != m_metaParam.m_pStrings ) {
		CString	S;
		CStdioFile	f( "play.txt", CFile::modeCreate | CFile::modeWrite | CFile::typeText );
		f.WriteString( m_strIdent + _T("\n") );
		for( int i = 0; i < Strings.GetSize(); ++i ) {
			f.WriteString(Strings.GetAt(i));
		}
		S.Format( "-----------------------------\nCLIPPED Objects: %ld\n", m_metaMemory.m_dwRecLast );
		f.WriteString(S);
	}
	m_metaParam.m_pStrings = NULL;
	m_metaParam.m_pStrFormat = NULL;
#endif

	//////////////////////////////////////////////////////////
	// zusätzlichen letzten Punkt aus der Liste rausnehmen

	ptList.SetSize( ptList.GetSize() - 1 );

	//////////////////////////////////////////////////////////
	// aufgesammelte geclippte Elemente abspielen

	if( 0 != m_metaMemory.m_dwRecLast )
		Replay( pDC );

	//////////////////////////////////////////////////////////
	// den verbastelten DC wiederherstellen

	pDC->RestoreDC( savedDC );

	m_metaParam.m_pMetaMemory = NULL;

	return TRUE;
}

/*
double GetHalfAngle( CStraith& rS1, CStraith& rS2 ) {
	double  phi1 = atan2( rS1.P1().y - rS1.P0().y, rS1.P1().x - rS1.P0().x ) + halfPI;
	double  phi2 = atan2( rS2.P1().y - rS2.P0().y, rS2.P1().x - rS2.P0().x ) + halfPI;

	phi1 = phi1 < 0 ? phi1 + twoPI : phi1;
	phi2 = phi2 < 0 ? phi2 + twoPI : phi2;

	phi1 = ( phi1 + phi2 ) / 2;
	while( phi1 > twoPI ) {
		phi1 -= twoPI;
	}
	return phi1;
}
*/
