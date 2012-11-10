#include	"stdafx.h"
#include	"metafile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#pragma	pack( push, _AFX_PACKING )
#pragma	pack(1)

typedef	struct tagAPMHEADER {
	DWORD	apmTag;
	WORD	apmZeroWord;
	short	apmLeft;
	short	apmTop;
	short	apmRight;
	short	apmBottom;
	WORD	apmDPI;
	DWORD	apmReserved;
	WORD	apmChecksum;
	} APMHEADER;

static short Direction( const double dx1, const double dy1, const double dx2, const double dy2 );

#pragma	pack( pop, _AFX_PACKING )

BOOL CMetaFile::Create( HPBYTE pMemData, DWORD nBytes ) {
	APMHEADER	*pApmHdr;
	METAHEADER	metaHdr;
	long		dataLength = (long) nBytes;				// nicht DWORD, um negative Werte behandeln zu können
	HPBYTE		pData = pMemData;

	if( dataLength < sizeof( APMHEADER ) )
		return FALSE;
	pApmHdr = (APMHEADER*) pData;
	if( 0x9ac6cdd7L == pApmHdr->apmTag ) {
		dataLength -= sizeof( APMHEADER );
		pData += sizeof( APMHEADER );
	}

	if( dataLength < sizeof( METAHEADER ) )
		return FALSE;
	metaHdr = *(METAHEADER*) pData;

	if( metaHdr.mtHeaderSize * sizeof( WORD ) != sizeof( METAHEADER ) )
		return FALSE;
	if( metaHdr.mtVersion != 0x0100 && metaHdr.mtVersion != 0x0300 )
		return FALSE;
	dataLength -= sizeof( METAHEADER );
	pData += sizeof( METAHEADER );

	if( metaHdr.mtSize * sizeof( WORD ) == (DWORD) dataLength + sizeof( METAHEADER ) )		// typisch für Corel
		metaHdr.mtSize -= sizeof( METAHEADER ) / sizeof( WORD );

	if( NULL != m_hSrcMF ) {
		::DeleteMetaFile( m_hSrcMF );
		m_hSrcMF = NULL;
	}

	HPBYTE	pBytes;
	HGLOBAL	hMem;

	if( NULL == ( hMem = ::GlobalAlloc( GHND, sizeof( METAHEADER ) + dataLength ) ) )
		return FALSE;

	if( NULL == ( pBytes = (HPBYTE) ::GlobalLock( hMem ) ) ) {
		::GlobalFree( hMem );
		return FALSE;
	}

	memcpy( (void FAR*) pBytes, (void FAR*) &metaHdr, (size_t) sizeof( METAHEADER ) );
	memcpy( (void FAR*) ( pBytes + sizeof( METAHEADER ) ), (void FAR*) pData, (size_t) dataLength );

	if( NULL == ( m_hSrcMF = (HMETAFILE) ::SetMetaFileBitsEx( sizeof( METAHEADER ) + dataLength, pBytes ) ) ) {
		::GlobalUnlock( hMem );
		::GlobalFree( hMem );
		return FALSE;
	}
	::GlobalUnlock( hMem );
	::GlobalFree( hMem );

	return TRUE;
}

#if defined(_RDEBUG)
#define META_FORMAT	if(NULL != lpMEP->m_pStrFormat) lpMEP->m_pStrFormat->Format
#define META_TRACE \
	if( NULL != lpMEP->m_pStrings && NULL != lpMEP->m_pStrFormat ) \
		lpMEP->m_pStrings->Add(*lpMEP->m_pStrFormat)
#else
inline void __F__(LPCTSTR,...){}
#define META_FORMAT __F__
#define META_TRACE (void) 0
#endif

static LPCTSTR brStyles[] = {
	_T("BS_SOLID")
	, _T("BS_NULL")
	, _T("BS_HATCHED")
	, _T("BS_PATTERN")
	, _T("BS_INDEXED")
	, _T("BS_DIBPATTERN")
	, _T("BS_DIBPATTERNPT")
	, _T("BS_PATTERN8X8")
	, _T("BS_DIBPATTERN8X8")
	, _T("BS_MONOPATTERN")
};

static LPCTSTR penStyles[] = {
	_T("PS_SOLID")
	, _T("PS_DASH")
	, _T("PS_DOT")
	, _T("PS_DASHDOT")
	, _T("PS_DASHDOTDOT")
	, _T("PS_NULL")
	, _T("PS_INSIDEFRAME")
	, _T("PS_USERSTYLE")
	, _T("PS_ALTERNATE")
};

typedef struct tagSRECT {
	short	bottom;
	short	right;
	short	top;
	short	left;
} SRECT;
typedef SRECT FAR* LPSRECT;

///////////////////////////////////////////////////////////////////
// die Koordinaten in den Metafiles werden umgebaut;
// daher müssen die neuen Koordinaten in einen zusätzlichen Puffer
// geschrieben werden
///////////////////////////////////////////////////////////////////

static	WORD	MFRBuf[ 8192 + sizeof( METARECORD ) ];			// max. 4096 Koordinaten + Header

int CALLBACK EnumOnParse( HDC hdc, HANDLETABLE FAR* lpHTable, LPMETARECORD lpSrcMFR, int cObj, METAENUMPARAM* lpMEP) {
	LPSPOINT		pSP, pDP;
	register short	x, y;
	int				i, nPoints;
	LPMETARECORD	lpPlayMFR;
	LPMETARECORD	lpDstMFR;

#if defined(_RDEBUG)
	META_FORMAT( _T("%3ld 0x%04x %s\n")
			, lpSrcMFR->rdSize
			, lpSrcMFR->rdFunction
			, lpMEP->pObject->RecType( lpSrcMFR->rdFunction )
			);
	META_TRACE;
#endif

	lpPlayMFR = lpSrcMFR;
	lpDstMFR = (LPMETARECORD) MFRBuf;
	*lpDstMFR = *lpSrcMFR;							// als 'default' annehmen; wird ggf. überschrieben
	nPoints = 0;

	switch( lpSrcMFR->rdFunction ) {
	case META_ESCAPE : {							// ESCAPE wird ignoriert
			META_FORMAT( "\t[%d]\n", lpSrcMFR->rdParm[0] );
			META_TRACE;
			return 1;
		}
	case META_SETWINDOWORG : {
			META_FORMAT( "\t[%d,%d]\n", (short) lpSrcMFR->rdParm[1], (short) lpSrcMFR->rdParm[0] );
			META_TRACE;
			lpMEP->m_rcWBound.left = (short) lpSrcMFR->rdParm[1];
			lpMEP->m_rcWBound.top = (short) lpSrcMFR->rdParm[0];

			lpMEP->m_ptParseOffsetX = (short) lpSrcMFR->rdParm[1];
			lpMEP->m_ptParseOffsetY = 0;
			return 1;
		}
	case META_SETWINDOWEXT : {
			META_FORMAT( "\t[%d,%d]\n", (int) lpSrcMFR->rdParm[1], (int) lpSrcMFR->rdParm[0] );
			META_TRACE;
			lpMEP->m_rcWBound.right = lpMEP->m_rcWBound.left + (int) lpSrcMFR->rdParm[1];
			lpMEP->m_rcWBound.bottom = lpMEP->m_rcWBound.top + (int) lpSrcMFR->rdParm[0];
			lpMEP->m_rcBound.right = (int) lpSrcMFR->rdParm[1];
			return 1;
		}
	case META_RECTANGLE : {
			LPCTSTR	s = _T("<???>");
			pSP = (LPSPOINT) &lpSrcMFR->rdParm[0];
			pDP = (LPSPOINT) &lpDstMFR->rdParm[1];
			LPSRECT	pR = (LPSRECT) &lpSrcMFR->rdParm[0];

			COLORREF c = ( lpMEP->m_PSelected > -1  ) ? lpMEP->m_gdiObjects[lpMEP->m_PSelected].pen.Color & 0x00ffffff : 0x00000000;
			if( c == 0x000000ff ) {
				lpMEP->m_rcFBound.left   = pR->left - lpMEP->m_ptParseOffsetX;
				lpMEP->m_rcFBound.top    = pR->top;
				lpMEP->m_rcFBound.right  = pR->right - lpMEP->m_ptParseOffsetX;
				lpMEP->m_rcFBound.bottom = pR->bottom;
				s = _T("FORCE BOUNDS");
				nPoints = 0;
			} else {
				/////////////////////////////////////////////////////////////////////
				// wenn ein Rechteck mehr als 90% der Gesamtfläche belegt, raus damit
				double	areaBnd = (double) (lpMEP->m_rcWBound.bottom - lpMEP->m_rcWBound.top) * (double) (lpMEP->m_rcWBound.right - lpMEP->m_rcWBound.left);
				double	areaRect = (double) (pSP[1].x - pSP[0].x) * (double) (pSP[1].y - pSP[0].y);
				areaRect /= areaBnd;
				areaRect = fabs( areaRect );
				if( areaRect > 0.9 ) {
					s = _T("IGNORE");
					nPoints = 0;
				} else {		// ...ansonsten zum Polgon umbauen
					s = _T("MAKE POLYGON");
					pDP[0].x = pSP[0].y; pDP[0].y = pSP[0].x;
					pDP[1].x = pSP[1].y; pDP[1].y = pSP[0].x;
					pDP[2].x = pSP[1].y; pDP[2].y = pSP[1].x;
					pDP[3].x = pSP[0].y; pDP[3].y = pSP[1].x;
					pDP[4].x = pSP[0].y; pDP[4].y = pSP[0].x;
					lpDstMFR->rdSize = sizeof( METARECORD ) + 5 * 2 * sizeof( WORD );
					lpDstMFR->rdFunction = META_POLYGON;
					lpDstMFR->rdParm[0] = 5;
					nPoints = 5;
					pSP = pDP;									// Koordinaten 'in place' konvertieren
				}
			}
			META_FORMAT( "\t%s: [%d,%d,%d,%d]\n", s, pR->left, pR->top, pR->right, pR->bottom );
			META_TRACE;
			if( 0 == nPoints )
				return 1;
		}
		break;
	case META_POLYGON : {
			pSP = (LPSPOINT) &lpSrcMFR->rdParm[1];
			pDP = (LPSPOINT) &lpDstMFR->rdParm[1];
			nPoints = (int) lpSrcMFR->rdParm[0];
			break;
		}
	case META_ELLIPSE : {
			pSP = (LPSPOINT) &lpSrcMFR->rdParm[0];
			pDP = (LPSPOINT) &lpDstMFR->rdParm[0];
			pDP[0].x = pSP[0].y; pDP[0].y = pSP[0].x;
			pDP[1].x = pSP[1].y; pDP[1].y = pSP[1].x;
			nPoints = 2;
			pSP = pDP;									// Koordinaten 'in place' konvertieren
			break;
		}
	case META_EXTTEXTOUT :								// Text wird übernommen
		META_FORMAT( "\t%s\n", (LPCTSTR) &lpSrcMFR->rdParm[4] );
		META_TRACE;
		if( NULL != lpMEP->m_pStrSigname ) {
			int		nChars = lpSrcMFR->rdParm[2];
			char*	pszText = (char*) &lpSrcMFR->rdParm[4];
			*( lpMEP->m_pStrSigname ) += CString( pszText, nChars );
			*( lpMEP->m_pStrSigname ) += ';';
		}
		return 1;
	case META_CREATEBRUSHINDIRECT : {
			LPSLOGBRUSH	pS = (LPSLOGBRUSH) &lpSrcMFR->rdParm[0];
			LPSLOGBRUSH	pD = (LPSLOGBRUSH) &lpDstMFR->rdParm[0];
			*pD = *pS;
			lpPlayMFR = lpDstMFR;
			META_FORMAT( _T("\t%s\t0x%08lx\t%d\n"), brStyles[pS->lbStyle], pS->Color, pS->lbHatch );
			META_TRACE;
		}
		break;
	case META_CREATEPENINDIRECT : {
			LPSLOGPEN pS = (LPSLOGPEN) &lpSrcMFR->rdParm[0];
			LPSLOGPEN pD = (LPSLOGPEN) &lpDstMFR->rdParm[0];
			*pD = *pS;
			lpPlayMFR = lpDstMFR;
			META_FORMAT(_T("\t%s\t[%d,%d] 0x%08lx\n"), penStyles[pS->lopnStyle], pS->lopnWidth.x, pS->lopnWidth.y, pS->Color );
			META_TRACE;
		}
		break;
	case META_CREATEFONTINDIRECT : {
			LPSLOGFONT	pS = (LPSLOGFONT) &lpSrcMFR->rdParm[0];
			META_FORMAT( "\t[%d,%d] %s\n", (long) pS->lfHeight, (long) pS->lfWidth, pS->lfFaceName );
			META_TRACE;
		}
		break;

	case META_MOVETO : {
			pSP = (LPSPOINT) &lpSrcMFR->rdParm[0];
			pDP = (LPSPOINT) &lpDstMFR->rdParm[0];
			META_FORMAT( "\t[%d,%d]\n", pSP[0].x, pSP[0].y );
			META_TRACE;
		}
		return 1;
	case META_LINETO : {
			pSP = (LPSPOINT) &lpSrcMFR->rdParm[0];
			pDP = (LPSPOINT) &lpDstMFR->rdParm[0];
			META_FORMAT( "\t[%d,%d]\n", pSP[0].x, pSP[0].y );
			META_TRACE;
		}
		return 1;
	case META_POLYLINE :
	case META_POLYPOLYGON : {
			META_FORMAT( "\t%d\t%d\n", lpSrcMFR->rdParm[0], lpSrcMFR->rdParm[1] );
			META_TRACE;
		}
		return 1;

	/////////////////////////////////////////////////////////////////////

	case META_SETTEXTJUSTIFICATION : {
			META_FORMAT( _T("\t[%d,%d]\n"), lpSrcMFR->rdParm[0], lpSrcMFR->rdParm[1] );
			META_TRACE;
		}
		return 1;
	case META_SETTEXTALIGN : {
			META_FORMAT( _T("\t[%d]\n"), lpSrcMFR->rdParm[0] );
			META_TRACE;
		}
		return 1;
	case META_SETTEXTCHAREXTRA :
	case META_TEXTOUT :
		return 1;

	case META_SELECTPALETTE	:
	case META_REALIZEPALETTE :
	case META_ANIMATEPALETTE :
	case META_SETPALENTRIES :
	case META_RESIZEPALETTE :
		break;
	case META_SETBKMODE :
		META_FORMAT( _T("\t[%s]\n"), 1 == lpSrcMFR->rdParm[0] ? _T("Transparent") : _T("Opaque") );
		META_TRACE;
		break;

	case META_SETTEXTCOLOR :
	case META_SETBKCOLOR :
	case META_SETROP2 :
		META_FORMAT( _T("\t[0x%08lx]\n"), *( (DWORD*) &lpSrcMFR->rdParm[0] ) );
		META_TRACE;
		return 1;
	default :
		break;
	}

	if( META_CREATEBRUSHINDIRECT == lpSrcMFR->rdFunction
		|| META_CREATEPENINDIRECT == lpSrcMFR->rdFunction 
		|| META_CREATEFONTINDIRECT == lpSrcMFR->rdFunction 
		|| META_CREATEPALETTE == lpSrcMFR->rdFunction
		)
	{
		for( i = 0; i < NGDIOBJECTS; i++ ) {
			if( 0 == lpMEP->m_gdiObjects[i].isA.rdFunction )
				break;
		}
		lpMEP->m_gdiObjects[i].isA = *lpSrcMFR;
		switch( lpSrcMFR->rdFunction ) {
		case META_CREATEBRUSHINDIRECT : lpMEP->m_gdiObjects[i].brush = *( (LPSLOGBRUSH) lpSrcMFR->rdParm); break;
		case META_CREATEPENINDIRECT : lpMEP->m_gdiObjects[i].pen = *( (LPSLOGPEN) lpSrcMFR->rdParm); break;
		case META_CREATEFONTINDIRECT : lpMEP->m_gdiObjects[i].font = *( (LPSLOGFONT) lpSrcMFR->rdParm); break;
		case META_CREATEPALETTE : lpMEP->m_gdiObjects[i].pal = *( (LPSLOGPALETTE) &lpSrcMFR->rdParm ); break;
		}
	}
	if( META_DELETEOBJECT == lpSrcMFR->rdFunction ) {
#if defined(_RDEBUG)
		LPCTSTR	s;
		switch( lpMEP->m_gdiObjects[lpSrcMFR->rdParm[0]].isA.rdFunction ) {
		case META_CREATEBRUSHINDIRECT : s = _T("BRUSH"); break;
		case META_CREATEPENINDIRECT : s = _T("PEN"); break;
		case META_CREATEFONTINDIRECT : s = _T("FONT"); break; 
		case META_CREATEPALETTE : s = _T("PALETTE"); break;
		default: s = _T("UNKNOWN");
		}
		META_FORMAT( "\t[%d] %s\n", lpSrcMFR->rdParm[0], s );
		META_TRACE;
#endif
		lpMEP->m_gdiObjects[lpSrcMFR->rdParm[0]].isA.rdFunction = 0;
	} else if( META_SELECTOBJECT == lpSrcMFR->rdFunction || META_SELECTPALETTE == lpSrcMFR->rdFunction ) {
#if defined(_RDEBUG)
		LPCTSTR	s;
		switch( lpMEP->m_gdiObjects[lpSrcMFR->rdParm[0]].isA.rdFunction ) {
		case META_CREATEBRUSHINDIRECT : s = _T("BRUSH"); break;
		case META_CREATEPENINDIRECT : s = _T("PEN"); break;
		case META_CREATEFONTINDIRECT : s = _T("FONT"); break; 
		case META_CREATEPALETTE : s = _T("PALETTE"); break;
		default: s = _T("UNKNOWN");
		}
		META_FORMAT( "\t[%d] %s\n", lpSrcMFR->rdParm[0], s );
		META_TRACE;
#endif
		switch( lpMEP->m_gdiObjects[lpSrcMFR->rdParm[0]].isA.rdFunction ) {
		case META_CREATEBRUSHINDIRECT : lpMEP->m_BSelected = lpSrcMFR->rdParm[0]; break;
		case META_CREATEPENINDIRECT : lpMEP->m_PSelected = lpSrcMFR->rdParm[0]; break;
		case META_CREATEFONTINDIRECT : lpMEP->m_FSelected = lpSrcMFR->rdParm[0]; break;
		case META_CREATEPALETTE : break;
		}
	}

	if( nPoints > 0 ) {
		lpPlayMFR = lpDstMFR;
		META_FORMAT( _T("\t") );
		META_TRACE;
		for( i = 0; i < nPoints; i++ ) {
			x = pSP->x;
			y = pSP->y;

			x -= lpMEP->m_ptParseOffsetX;
			y -= lpMEP->m_ptParseOffsetY;

			lpMEP->m_rcBound.top	= min( lpMEP->m_rcBound.top, y );
			lpMEP->m_rcBound.left	= min( lpMEP->m_rcBound.left, x );
			lpMEP->m_rcBound.bottom	= max( lpMEP->m_rcBound.bottom, y );
			lpMEP->m_rcBound.right	= max( lpMEP->m_rcBound.right, x );

			pDP->x = x;
			pDP->y = y;

			META_FORMAT( _T("[%5d,%5d]->[%5d,%5d]%s")
				, pSP->x
				, pSP->y
				, pDP->x
				, pDP->y
				, (0 == (i+1) % 3 ) ? _T("\n\t") : _T(" ")
				);
			META_TRACE;
			pSP++;
			pDP++;
		}
		META_FORMAT( _T("\n") );
		META_TRACE;
	}

	PlayMetaFileRecord(hdc, lpHTable, lpPlayMFR, cObj);
	return 1;
}

//////////////////////////////////////////////////////////////////////////////////////
// Enumerator für's Zeichnen


int CALLBACK EnumOnDraw( HDC hdc, HANDLETABLE FAR* lpHTable, LPMETARECORD lpSrcMFR, int cObj, METAENUMPARAM* lpMEP) {
	LPSPOINT		pSP, pDP;
	register short	x, y, w;
	int				i, nPoints;
	LPMETARECORD	lpPlayMFR;
	LPMETARECORD	lpDstMFR;

#if defined(_RDEBUG)
	META_FORMAT( _T("%3ld 0x%04x %s\n")
			, lpSrcMFR->rdSize
			, lpSrcMFR->rdFunction
			, lpMEP->pObject->RecType( lpSrcMFR->rdFunction )
			);
	META_TRACE;
#endif
	
	lpDstMFR = (LPMETARECORD) MFRBuf;
	*lpDstMFR = *lpSrcMFR;
	lpPlayMFR = lpSrcMFR;

	nPoints = 0;

	switch( lpSrcMFR->rdFunction ) {
	case META_POLYGON :
	case META_ELLIPSE : {
//			return 1;
		}
	}

	switch( lpSrcMFR->rdFunction ) {				// Geometrien skalieren
	case META_POLYGON :
		pSP = (LPSPOINT) &lpSrcMFR->rdParm[1];
		pDP = (LPSPOINT) &lpDstMFR->rdParm[1];
		nPoints = (short) lpSrcMFR->rdParm[0];
		break;
	case META_ESCAPE :
	case META_MOVETO :
	case META_RECTANGLE :
	case META_LINETO :
	case META_POLYLINE :
	case META_POLYPOLYGON :
		return 1;

	case META_ELLIPSE : {
			pSP = (LPSPOINT) &lpSrcMFR->rdParm[0];
			pDP = (LPSPOINT) &lpDstMFR->rdParm[0];

			///////////////////////////////////////////////////////////////////////////
			// etwas spezielles :-)

			pDP[0].x = ( pSP[0].x + pSP[1].x ) / 2;		// Kreismittelpunkt
			pDP[0].y = ( pSP[0].y + pSP[1].y ) / 2;

			pDP[1].x = pSP[1].x - pSP[0].x;				// Höhe
			pDP[1].x = abs( pDP[1].x );
			pDP[1].y = pSP[1].y - pSP[0].y;				// Breite
			pDP[1].y = abs( pDP[1].y );

			pDP[1].x = max( pDP[1].x, pDP[1].y );
			pDP[1].x /= 2;

			pSP = pDP;				// inPlace transformieren
			nPoints = 1;
		}
		break;
	case META_CREATEBRUSHINDIRECT : {
			LPSLOGBRUSH	pS = (LPSLOGBRUSH) &lpSrcMFR->rdParm[0];
			LPSLOGBRUSH	pD = (LPSLOGBRUSH) &lpDstMFR->rdParm[0];
			*pD = *pS;
			if( lpMEP->m_bReplaceColor )
				pD->Color = lpMEP->m_rgbBrush;
			lpPlayMFR = lpDstMFR;
			META_FORMAT( _T("\t%s\t0x%08lx\t%d\n"), brStyles[pS->lbStyle], pS->Color, pS->lbHatch );
			META_TRACE;
		}
		break;
	case META_CREATEPENINDIRECT : {
			LPSLOGPEN pS = (LPSLOGPEN) &lpSrcMFR->rdParm[0];
			LPSLOGPEN pD = (LPSLOGPEN) &lpDstMFR->rdParm[0];
			*pD = *pS;
			if( lpMEP->m_bReplaceColor )
				pD->Color = lpMEP->m_rgbBrush;
			lpPlayMFR = lpDstMFR;
			META_FORMAT(_T("\t%s\t[%d,%d] 0x%08lx\n"), penStyles[pS->lopnStyle], pS->lopnWidth.x, pS->lopnWidth.y, pS->Color );
			META_TRACE;
		}
		break;
	case META_SETBKMODE : {
			META_FORMAT( _T("\t%s\n"), 1 == lpSrcMFR->rdParm[0] ? _T("Transparent") : _T("Opaque") );
			META_TRACE;
		}
		break;
	case META_SETTEXTCOLOR : {
			META_FORMAT( _T("\t0x%08lx\n"), *( (DWORD*) &lpSrcMFR->rdParm[0] ) );
			META_TRACE;
		}
		break;
	case META_CREATEFONTINDIRECT : {
			LPSLOGFONT	pS = (LPSLOGFONT) &lpSrcMFR->rdParm[0];
			META_FORMAT( "\t[%d,%d] %s\n", (long) pS->lfHeight, (long) pS->lfWidth, pS->lfFaceName );
			META_TRACE;
		}
		break;
	}
	
	if( META_CREATEBRUSHINDIRECT == lpSrcMFR->rdFunction
		|| META_CREATEPENINDIRECT == lpSrcMFR->rdFunction 
		|| META_CREATEFONTINDIRECT == lpSrcMFR->rdFunction 
		|| META_CREATEPALETTE == lpSrcMFR->rdFunction
		)
	{
		for( i = 0; i < NGDIOBJECTS; i++ ) {
			if( 0 == lpMEP->m_gdiObjects[i].isA.rdFunction )
				break;
		}
		lpMEP->m_gdiObjects[i].isA = *lpSrcMFR;
		switch( lpSrcMFR->rdFunction ) {
		case META_CREATEBRUSHINDIRECT : lpMEP->m_gdiObjects[i].brush = *( (LPSLOGBRUSH) lpSrcMFR->rdParm); break;
		case META_CREATEPENINDIRECT : lpMEP->m_gdiObjects[i].pen = *( (LPSLOGPEN) lpSrcMFR->rdParm); break;
		case META_CREATEFONTINDIRECT : lpMEP->m_gdiObjects[i].font = *( (LPSLOGFONT) lpSrcMFR->rdParm); break;
		case META_CREATEPALETTE : lpMEP->m_gdiObjects[i].pal = *( (LPSLOGPALETTE) &lpSrcMFR->rdParm ); break;
		}
	}
	if( META_DELETEOBJECT == lpSrcMFR->rdFunction ) {
#if defined(_RDEBUG)
		LPCTSTR	s;
		switch( lpMEP->m_gdiObjects[lpSrcMFR->rdParm[0]].isA.rdFunction ) {
		case META_CREATEBRUSHINDIRECT : s = _T("BRUSH"); break;
		case META_CREATEPENINDIRECT : s = _T("PEN"); break;
		case META_CREATEFONTINDIRECT : s = _T("FONT"); break; 
		case META_CREATEPALETTE : s = _T("PALETTE"); break;
		default: s = _T("UNKNOWN");
		}
		META_FORMAT( "\t[%d] %s\n", lpSrcMFR->rdParm[0], s );
		META_TRACE;
#endif
		lpMEP->m_gdiObjects[lpSrcMFR->rdParm[0]].isA.rdFunction = 0;
	} else if( META_SELECTOBJECT == lpSrcMFR->rdFunction || META_SELECTPALETTE == lpSrcMFR->rdFunction ) {
#if defined(_RDEBUG)
		LPCTSTR	s;
		switch( lpMEP->m_gdiObjects[lpSrcMFR->rdParm[0]].isA.rdFunction ) {
		case META_CREATEBRUSHINDIRECT : s = _T("BRUSH"); break;
		case META_CREATEPENINDIRECT : s = _T("PEN"); break;
		case META_CREATEFONTINDIRECT : s = _T("FONT"); break; 
		case META_CREATEPALETTE : s = _T("PALETTE"); break;
		default: s = _T("UNKNOWN");
		}
		META_FORMAT( "\t[%d] %s\n", lpSrcMFR->rdParm[0], s );
		META_TRACE;
#endif
		switch( lpMEP->m_gdiObjects[lpSrcMFR->rdParm[0]].isA.rdFunction ) {
		case META_CREATEBRUSHINDIRECT : lpMEP->m_BSelected = lpSrcMFR->rdParm[0]; break;
		case META_CREATEPENINDIRECT : lpMEP->m_PSelected = lpSrcMFR->rdParm[0]; break;
		case META_CREATEFONTINDIRECT : lpMEP->m_FSelected = lpSrcMFR->rdParm[0]; break;
		case META_CREATEPALETTE : break;
		}
	}
	
	BOOL bClip = FALSE;
	BOOL	bClipR = FALSE;
	BOOL	bClipL = FALSE;
	short	DL, DR, D;
	DL = DR = -3;
	if( nPoints > 0 ) {
		lpPlayMFR = lpDstMFR;
		if( lpMEP->m_bClip ) {
			COLORREF c;
			bClip = FALSE;
			if( -1 != lpMEP->m_BSelected ) {
				c = lpMEP->m_gdiObjects[lpMEP->m_BSelected].brush.Color & 0x00ffffff;
				if( 0x00ff0000 == c ) {
					bClip = TRUE;
				}
			}
			if( -1 != lpMEP->m_PSelected ) {
				c = lpMEP->m_gdiObjects[lpMEP->m_PSelected].pen.Color & 0x00ffffff;
				if( 0x00ff0000 == c ) {
					bClip = TRUE;
				}
			}
		}
		for( i = 0; i < nPoints; i++ ) {
			x = pSP->x;
			y = pSP->y;
			if( lpMEP->m_bSwapX )
				x = lpMEP->m_rcBound.right - x;
			if( lpMEP->m_bSwapY )
				y = -y;
			lpMEP->TransformPoint( x, y );
	
			pDP->x = x;				// an Position schieben
			pDP->y = y;
			
			if(bClip) {
				D = Direction( lpMEP->m_dx1L, lpMEP->m_dy1L, x - lpMEP->m_x2L, y - lpMEP->m_y2L );
				if( -3 == DL )
					DL = D;
				else if( DL != D ) {
					bClipL = TRUE;
				}
				D = Direction( lpMEP->m_dx1R, lpMEP->m_dy1R, x - lpMEP->m_x2R, y - lpMEP->m_y2R );
				if( -3 == DR )
					DR = D;
				else if( DR != D ) {
					bClipR = TRUE;
				}
			}
			META_FORMAT( _T("[%5d,%5d]->[%5d,%5d]%s"), pSP->x, pSP->y, pDP->x, pDP->y, (0 == (i+1) % 3 ) ? _T("\n\t") : _T(" ") );
			META_TRACE;
			pSP++;
			pDP++;
		}
		META_FORMAT( _T("\n") );
		META_TRACE;
	}

	if( META_ELLIPSE == lpSrcMFR->rdFunction ) {
		pDP = (LPSPOINT) &lpDstMFR->rdParm[0];		// Parameterzeiger richten

		x = pDP[0].x;
		y = pDP[0].y;
		w = (short) ( (double) pDP[1].x * fabs( lpMEP->zoom() ) );

		pDP[0].x = (WORD) (y - w);							// und aus (x,y) Koordinaten wieder ein RECT machen
		pDP[0].y = (WORD) (x - w);
		pDP[1].x = (WORD) (y + w);
		pDP[1].y = (WORD) (x + w);
		if( bClip ) {
			D = Direction( lpMEP->m_dx1L, lpMEP->m_dy1L, pDP[0].y - lpMEP->m_x2L, pDP[0].x - lpMEP->m_y2L );
			
			if( D != Direction( lpMEP->m_dx1L, lpMEP->m_dy1L, pDP[1].y - lpMEP->m_x2L, pDP[0].x - lpMEP->m_y2L ) ) {
				bClipL = TRUE;
			}
			if( D != Direction( lpMEP->m_dx1L, lpMEP->m_dy1L, pDP[1].y - lpMEP->m_x2L, pDP[1].x - lpMEP->m_y2L ) ) {
				bClipL = TRUE;
			}
			if( D != Direction( lpMEP->m_dx1L, lpMEP->m_dy1L, pDP[0].y - lpMEP->m_x2L, pDP[1].x - lpMEP->m_y2L ) ) {
				bClipL = TRUE;
			}

			D = Direction( lpMEP->m_dx1R, lpMEP->m_dy1R, pDP[1].y - lpMEP->m_x2R, pDP[1].x - lpMEP->m_y2R );
			if( D != Direction( lpMEP->m_dx1R, lpMEP->m_dy1R, pDP[1].y - lpMEP->m_x2R, pDP[0].x - lpMEP->m_y2R ) ) {
				bClipR = TRUE;
			}
			if( D != Direction( lpMEP->m_dx1R, lpMEP->m_dy1R, pDP[1].y - lpMEP->m_x2R, pDP[1].x - lpMEP->m_y2R ) ) {
				bClipR = TRUE;
			}
			if( D != Direction( lpMEP->m_dx1R, lpMEP->m_dy1R, pDP[0].y - lpMEP->m_x2R, pDP[1].x - lpMEP->m_y2R ) ) {
				bClipR = TRUE;
			}
		}
	}

	if( bClipR || bClipL ) {
		if( NULL != lpMEP->m_pMetaMemory ) {
			lpMEP->m_pMetaMemory->Push( &lpMEP->m_gdiObjects[lpMEP->m_BSelected].isA );
			lpMEP->m_pMetaMemory->Push( &lpMEP->m_gdiObjects[lpMEP->m_PSelected].isA );
			lpMEP->m_pMetaMemory->Push( lpPlayMFR );
			META_FORMAT( _T("\t\tCLIPPING %s\n"), bClipR ? _T("right") : _T("left") );
			META_TRACE;
		}
	} else {
		PlayMetaFileRecord(hdc, lpHTable, lpPlayMFR, cObj);
	}
    return 1;
}

void CMetaFile::Replay( CDC *pDC ) {
	LPMETARECORD lpMFR;
	COLORREF	c;
	if( m_bMarkSegments ) {
		c = RGB( 255 - GetRValue( m_metaParam.m_rgbBrush ), 255 - GetGValue( m_metaParam.m_rgbBrush ), 255 - GetBValue( m_metaParam.m_rgbBrush ) );
	} else {
		c = m_metaParam.m_rgbBrush;
	}
	CBrush	br( c ), *pOldBr;
	CPen	pen( PS_SOLID, 0, c ), *pOldPen;
	pOldBr = pDC->SelectObject( &br );
	pOldPen = pDC->SelectObject( &pen );
	for( DWORD i = 0; i < m_metaMemory.m_dwRecLast; i++ ) {
		lpMFR = m_metaMemory.m_pRecords[i];
		switch( lpMFR->rdFunction ) {
		case META_CREATEBRUSHINDIRECT : {
				LOGBRUSH	lb;
				LPSLOGBRUSH	p = (LPSLOGBRUSH) lpMFR->rdParm;
				lb.lbStyle = p->lbStyle;
				lb.lbColor = c;
				lb.lbHatch = p->lbHatch;
				pDC->SelectObject( pOldBr );
				br.DeleteObject();
				br.CreateBrushIndirect( &lb );
				pOldBr = pDC->SelectObject( &br );
			}
			break;
		case META_CREATEPENINDIRECT : {
				LOGPEN	lp;
				LPSLOGPEN p = (LPSLOGPEN) lpMFR->rdParm;
				lp.lopnStyle = p->lopnStyle;
				lp.lopnColor = c;
				lp.lopnWidth.x = p->lopnWidth.x;
				lp.lopnWidth.y = p->lopnWidth.y;
				pDC->SelectObject( pOldPen );
				pen.DeleteObject();
				pen.CreatePenIndirect( &lp );
				pOldPen = pDC->SelectObject( &pen );
			}
			break;
		case META_ELLIPSE :
				pDC->Ellipse( (short) lpMFR->rdParm[1], (short) lpMFR->rdParm[0], (short) lpMFR->rdParm[3], (short) lpMFR->rdParm[2] );
			break;
		case META_POLYGON :
			break;
		}
	}
	pDC->SelectObject( pOldBr );
	pDC->SelectObject( pOldPen );
}

void CMetaMemory::ImportObjects( CDC *pDC, const CRgn& clipRegion, const CMetaMemory& rSrc ) {
	LPMETARECORD lpMFR;
	GDIOBJECT	br;
	GDIOBJECT	pen;
	BOOL	bBrPush = FALSE, bPenPush = FALSE;
	memset( &br, 0x00, sizeof(br) );
	memset( &pen, 0x00, sizeof(pen) );

	for( DWORD i = 0; i < rSrc.m_dwRecLast; i++ ) {
		lpMFR = rSrc.m_pRecords[i];
		switch( lpMFR->rdFunction ) {
		case META_CREATEBRUSHINDIRECT : {
				LPSLOGBRUSH	p = (LPSLOGBRUSH) lpMFR->rdParm;
				if( 0 == br.isA.rdFunction || br.brush.lbStyle != p->lbStyle || br.brush.lbHatch != p->lbHatch ) {
					br.isA = *lpMFR;
					br.brush = *p;
					bBrPush = TRUE;
				} else {
					bBrPush = FALSE;
				}
			}
			break;
		case META_CREATEPENINDIRECT : {
				LPSLOGPEN	p = (LPSLOGPEN) lpMFR->rdParm;
				if( 0 == pen.isA.rdFunction 
					|| pen.pen.lopnStyle != p->lopnStyle 
					|| pen.pen.lopnWidth.x != p->lopnWidth.x 
					|| pen.pen.lopnWidth.y != p->lopnWidth.y
					)
				{
					pen.isA = *lpMFR;
					pen.pen = *p;
					bPenPush = TRUE;
				} else {
					bPenPush = FALSE;
				}
			}
			break;
		case META_ELLIPSE : {
				int	nInRgn = 0;
				CPoint	P;
				P.x = (int) ( lpMFR->rdParm[1] + lpMFR->rdParm[3] ) / 2;
				P.y = (int) ( lpMFR->rdParm[0] + lpMFR->rdParm[0] ) / 2;
				pDC->LPtoDP( &P, 1 );
				if( bBrPush )
					Push( &br.isA );
				if( bPenPush )
					Push( &pen.isA );
				bBrPush = bPenPush = FALSE;
				if( clipRegion.PtInRegion( P ) ) {
					Push( lpMFR );
				}
			}
			break;
		case META_POLYGON :
			break;
		}
	}
}

static short Direction( const double dx1, const double dy1, const double dx2, const double dy2 ) {
	if (dx1*dy2 > dy1*dx2)
		return +1;
	if (dx1*dy2 < dy1*dx2)
		return -1;
	if (dx1*dx2 < 0 || dy1*dy2 < 0)
		return -1;
	if (dx1*dx1+dy1*dy1 < dx2*dx2+dy2*dy2)
		return +1;
	return 0;
}

/*
//----------------------------------------------------------------------------------------------
// Bewegungsrichtung, wenn man bei 3 gegebenen real-Punkten vom ersten, zum
// zweiten und dann zum dritten geht; Rückgabewert ist
// +1 bei Drehung im mathem. pos. Sinn (gegen Uhrzeigersinn) bzw. 
//    bei Kollinearität, wenn Pkt2 zwischen Pkt1 und Pkt3 liegt bzw.
//    bei Pkt1==Pkt2
// -1 bei Drehung im mathem. neg. Sinn (im Uhrzeigersinn) bzw.
//    bei Kollinearität, wenn Pkt1 zwischen Pkt3 und Pkt2 liegt
//  0 bei Kollinearität, wenn Pkt3 zwischen Pkt1 und Pkt2 liegt bzw.
//    bei Pkt1==Pkt3, Pkt2==Pkt3, Pkt1==Pkt2==Pkt3

static short BewegRicht_real (double x1, double y1, double x2, double y2, double x3, double y3) {
	double dx1 = x2 - x1;
	double dy1 = y2 - y1;
	double dx2 = x3 - x1;
	double dy2 = y3 - y1;

	if (dx1*dy2 > dy1*dx2)
		return +1;
	if (dx1*dy2 < dy1*dx2)
		return -1;
	if (dx1*dx2 < 0 || dy1*dy2 < 0)
		return -1;
	if (dx1*dx1+dy1*dy1 < dx2*dx2+dy2*dy2)
		return +1;
	return 0;
} // BewegRicht_real
*/