#include "stdafx.h"

#include <vinfomfc.h>
#include "vismod.h"

#include "TKarten.h"
#include <math.h>
#include <Com/Thunk.h>

#import "TRiASCS.tlb" \
	raw_interfaces_only	\
	raw_dispinterfaces	\
	no_implementation	\
	no_namespace		\
	named_guids

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// die kleinen Helferlein...

CGCP::CGCP() {
	Clear();
}

void CGCP::Clear() {
	m_ptlPict.x = m_ptlPict.y = 0;
	m_ptlCoord.x = m_ptlCoord.y = 0;
}

////////////////////////////////////////////////////////////////////////////

CInfoForMap::CInfoForMap()
	: m_chAddChar( '\0' )
	, m_nCropBorder( 0 )
	, m_nSubfile( 0 )
	, m_szPicture( 0, 0 )
	, m_pRTPicture( NULL )
{
	m_nSubfile = 0;
	m_bHaveSubFiles = FALSE;
	m_nSampleRate = 0;
	m_chAddChar = '\0';
	m_nCropBorder = 0;
	m_pListOfGCP	= new CObArray;
	for (int i = 0; i < 4; i++ )
		m_pListOfGCP->Add(new CGCP);

	m_bUsesSubDirs = FALSE;
	m_bModifiesSubDirs = FALSE;
	m_nSubLevels = 6;
}

CInfoForMap::~CInfoForMap() 
{
	for (int i = 0; i < m_pListOfGCP->GetSize(); i++ )
		delete m_pListOfGCP->GetAt( i );
	delete m_pListOfGCP;
}

void CInfoForMap::ClearGCPList() 
{
	CGCP	*pGCP;
	for (int i = 0; i < 4; i++) {
		pGCP = (CGCP *) m_pListOfGCP->GetAt(i);
		pGCP->Clear();
	}
	for (/**/; i < m_pListOfGCP->GetSize(); i++) 
		delete m_pListOfGCP->GetAt(i);
}

BOOL CInfoForMap::SubDirFits(LPCTSTR pcPath)
{
CString path(pcPath);

	path.TrimRight('\\');
	if (m_strBaseDir.GetLength() > 0 &&
		0 == m_strBaseDir.CompareNoCase(path.Right(m_strBaseDir.GetLength())))
	{
		return TRUE;
	}
	return FALSE;
}

////////////////////////////////////////////////////////////////////////////

CRGBClut::CRGBClut() 
{
	Clear();
}

void CRGBClut::Clear() 
{
	memset((void FAR*) m_nColors, 0x00, sizeof(m_nColors));
	memset((void FAR*) m_cluTables, 0x00, sizeof(m_cluTables));
}

void CRGBClut::SetPalette(CPicture *pPicture) 
{
	int	nColors = pPicture->GetUsedColors();
	double	Y709;
	double	Boff = 128.0;
	LPRGBQUAD	pC, pG1, pG2;

	if (0 == m_nColors[0] && nColors <= 256) {
        _ASSERTE(N_PALETTETYPES >= 3);

		pPicture->GetClut(m_cluTables[0], pPicture->GetUsedColors());
		
		m_nColors[0] = nColors;
		m_nColors[1] = nColors;
		m_nColors[2] = nColors;

        pC = m_cluTables[0];
		pG1 = m_cluTables[1];
		pG2 = m_cluTables[2];
		for (int i = 0; i < nColors; i++)
		{
			Y709 = 0.2125 * (double) pC->rgbRed + 
                   0.7154 * (double) pC->rgbGreen + 
                   0.0721 * (double) pC->rgbBlue;
			pG1->rgbRed = pG1->rgbGreen = pG1->rgbBlue = (BYTE)(int)Y709;

			Y709 = ((255.0 - Boff) / 255.0) * Y709 + Boff;
			pG2->rgbRed = pG2->rgbGreen = pG2->rgbBlue = (BYTE)(int)Y709;

			pC++;
			pG1++;
			pG2++;
		}
	}
}

LPRGBQUAD CRGBClut::GetPalette( int nPalIndex) 
{
	ASSERT(N_PALETTETYPES > nPalIndex);
	return m_cluTables[nPalIndex];
}

////////////////////////////////////////////////////////////////////////////
// die eigentliche Implementierung...

#ifndef WIN32
#include <ctype.h>
#define iswalnum	isalnum
#define	towlower	tolower
#endif

static BOOL MatchMapName( LPCTSTR lpszMapName, LPCTSTR lpszFileName) 
{
	CString	strMapName( lpszMapName );
	CString	strFileName;
	TCHAR	c1, c2;
	::AfxExtractSubString(strFileName, lpszFileName, 0, '.');
	int	mapLen = strMapName.GetLength();
	int	fileLen = strFileName.GetLength();
	for (/**/; mapLen && fileLen; /**/) {
		mapLen--;
		fileLen--;
		c1 = strMapName[mapLen];
		c2 = strFileName[fileLen];
		if (iswalnum(c1)) {
			if (towlower(c1) != towlower(c2))
				return FALSE;
		}
	}
	if (0 == fileLen)
		return FALSE;
	return TRUE;
}

static inline
void AddToGCPList (CGCP *pGCP, GCPList *pGCPs, IUnknown *pICS)
{
double dKoords[2];
COORDTRANSFORMEX CT;

	INITSTRUCT(CT, COORDTRANSFORMEX);
	CT.m_Pts = (long *)&pGCP->m_ptlCoord;
	CT.m_rcPts = dKoords;
	CT.m_pICS = pICS;
	DEX_OCtoRC(CT);

	pGCPs->push_back (GCP (
			GEOPOINT(dKoords[0], dKoords[1]), 
			GEOPOINT(pGCP->m_ptlPict.x, pGCP->m_ptlPict.y)
		)
	);
}

static inline
void CorrectGCP (GCP &rGCP, CGCP *pGCP, IUnknown *pICS)
{
long lKoords[2];
COORDTRANSFORMEX CT;

	INITSTRUCT(CT, COORDTRANSFORMEX);
	CT.m_rcPts = (double *)&rGCP.m_ptGeoCoord;
	CT.m_Pts = lKoords;
	CT.m_pICS = pICS;
	DEX_RCtoOC(CT);

	pGCP->m_ptlCoord.x = lKoords[0];
	pGCP->m_ptlCoord.y = lKoords[1];
	pGCP->m_ptlPict.x = (long)rGCP.m_ptPictPoint.X;
	pGCP->m_ptlPict.y = (long)rGCP.m_ptPictPoint.Y;
}

///////////////////////////////////////////////////////////////////////////////
// Hilfsfunktion, um die Größe des zu bedruckenden Bereiches zu bestimmen
CSize GetRealViewportSize(CDC *pDC, CDC *pTarget)
{
CSize szView;

	if (pDC->IsPrinting() || pTarget->IsPrinting())
		VERIFY(0 != ::Escape(pTarget->GetSafeHdc(), GETPHYSPAGESIZE, 0, NULL, &szView));
	else
		szView = pDC -> GetViewportExt();
	return szView;
}

///////////////////////////////////////////////////////////////////////////////
// 
#define N_COORDS	5		// eine Karte hat fünf Koordinaten...

#include <io.h>		// _access

#define	HPDESKJET660C	11

BOOL CKartenCtrl::OnDrawObject(
						CDC *pDC,
						CDC *pTarget,
						const DWORD lObjNr, 
						class VisInfo* pVI, 
						LPCTSTR pszVisString, 
						short& fDrawFlags )
{
	_ASSERTE( __hWndM != NULL );
	_ASSERTE( __DexCmd != 0 );
	_ASSERTE( lObjNr > 0L );

	m_bProjDrawn = TRUE;
	m_bViewDrawn = TRUE;
    m_pVI = pVI;

//	double		fScale = 0.0, tScale = 0.0;
	CString		S;						// zum Extrahieren
//	::AfxExtractSubString( S, pVI->VisName(), 1, ';' );
//	fScale = atof( S );
//	::AfxExtractSubString( S, pVI->VisName(), 2, ';' );
//	tScale = atof( S );

	int	cap = pDC->GetDeviceCaps( TECHNOLOGY );

	if (DT_RASDISPLAY != cap 
		&& DT_RASPRINTER != cap 
		&& HPDESKJET660C != cap)				// HP-Deskjet 660C - Drucksystem
	{
		return FALSE;
	}
	m_pCurrMap = NULL;

	if (!ParseVisInfoString(lObjNr, pszVisString))
		return FALSE;

	ASSERT_VALID(m_pCurrMap);
	double	dx = 0;

//	if (0 != m_mysticFactor && m_activeZoom >= 1.0) 
	{
	COORDCONVERT	C;
	POINTL			ptlP;
	POINT			ptP;
	double	mapWidth;
	
	 	C.lpPt = &ptP; 
		C.lpPkt = (long *)&ptlP;
		ptlP = ((CGCP *)m_pCurrMap->m_pListOfGCP->GetAt(1))->m_ptlCoord; 
		DEX_OCtoDCEx(C);	// ptlP --> ptP
		mapWidth  = ptP.x;

		ptlP = ((CGCP *)m_pCurrMap->m_pListOfGCP->GetAt(0))->m_ptlCoord; 
		DEX_OCtoDCEx(C);	// ptlP --> ptP
		mapWidth -= ptP.x;
		if (mapWidth < m_minSize)
			return FALSE;
	}

int	i;
CString	strUID;
CPath	pathOfPicture;
CFile	fileOfPicture;
BOOL	bHavePictureFound = FALSE;

	if (NULL == m_pCurrMap->m_pRTPicture) {
	UINT nOldErrMode = ::SetErrorMode(SEM_FAILCRITICALERRORS);
		
		for (i = 0; i < m_strMapDirs.GetSize(); i++) {
			if (m_pCurrMap->m_bUsesSubDirs) {
			// Unterverzeichnis am Bild gegeben
				if (m_pCurrMap -> SubDirFits(m_strMapDirs[i])) {
				// letzter Teil des Suchpfades paßt zum Bildunterverzeichnis
					strUID = m_strMapDirs[i] + m_pCurrMap->m_strSubDir + m_pCurrMap->m_strPictName;

					if (m_pCurrMap->m_bModifiesSubDirs) {
						pathOfPicture.Path(m_strMapDirs[i] + 
							m_pCurrMap->m_strSubDir + m_pCurrMap->m_strDirSuffix + "\\");
					}
					else {
						pathOfPicture.Path(m_strMapDirs[i] + m_pCurrMap->m_strSubDir + "\\");
					}
					pathOfPicture.FileName(m_pCurrMap->m_strPictName);
				} else
					continue;		// kann gar nicht passen
			}
			else {
			// normales Bild (ohne Unterverzeichnisse)
				strUID = m_strMapDirs[i] + m_pCurrMap->m_strPictName;
				pathOfPicture.Path(m_strMapDirs[i]);
				pathOfPicture.FileName(m_pCurrMap->m_strPictName);
			}
			if (0 == _access(pathOfPicture.Path(), 04)) {
				if (!fileOfPicture.Open(pathOfPicture.Path(), CFile::modeRead | CFile::shareDenyWrite | CFile::typeBinary ) )
					return FALSE;

			// Bilddatei gefunden
			BOOL fHasToMatch = m_bMatchMapName || m_strDQ.GetMatchMapName(lObjNr);

				if(!fHasToMatch || MatchMapName(m_pCurrMap->m_strMapUID, strUID))
				{
					CRuntimeClass	*pRT = NULL;
					CPicture		*pPicture = NULL;
					for (POSITION pos = m_pictTypes.GetStartPosition(); pos; /**/)
					{
						m_pictTypes.GetNextAssoc( pos, (void*&) pRT, (void*&) pPicture );
						if (pPicture->Attach( &fileOfPicture ) && pPicture->ReadHeader() )
						{
							CRect	rcPict = pPicture->GetPictRect();
							m_pCurrMap->m_szPicture.cx = rcPict.Width();
							m_pCurrMap->m_szPicture.cy = rcPict.Height();
							m_pCurrMap->m_pRTPicture = pRT;
							break;
						} else
							pRT = NULL;
					}
					if (NULL == pRT) {
						if (NULL != ( pRT = GetPictureType( &fileOfPicture ) )) {
							m_pCurrMap->m_pRTPicture = pRT;
							pPicture = (CPicture*) pRT->CreateObject();
							pPicture->Attach( &fileOfPicture );
							m_pictTypes.SetAt( (void*) pRT, (void*) pPicture );
						}
					}
					if (NULL != pPicture) {
						if (pPicture->ReadHeader(NULL, 5)) {
							m_pCurrMap->m_strPictPath = strUID;
							m_pCurrMap->m_bHaveSubFiles = TRUE;		// Bild beherrscht Subfiles
						}
						pPicture->Detach();
					}
					fileOfPicture.Close();
					break;
				}
				fileOfPicture.Close();
			}
		}
		::SetErrorMode( nOldErrMode );
	}

	if (NULL == m_pCurrMap->m_pRTPicture )
		return FALSE;

	VERIFY(m_pictTypes.Lookup((void *)m_pCurrMap->m_pRTPicture, (void *&)m_pPicture));

	if (!SelectSubFile())
		return FALSE;

	if (m_pCurrMap->m_bHaveSubFiles)
		pathOfPicture.Path( m_pCurrMap->m_strPictPath );
	else {
	// if (m_pCurrMap->m_strPictPath.IsEmpty() )
	UINT nOldErrMode = ::SetErrorMode(SEM_FAILCRITICALERRORS);
	
		bHavePictureFound = FALSE;
		for (i = 0; i < m_strMapDirs.GetSize(); i++) {
			if (m_pCurrMap->m_bUsesSubDirs) {
				if (m_pCurrMap ->SubDirFits(m_strMapDirs[i])) {
					strUID = m_strMapDirs[i] + m_pCurrMap->m_strSubDir + m_pCurrMap->m_strPictName;
					if (m_pCurrMap->m_bModifiesSubDirs) {
						pathOfPicture.Path(m_strMapDirs[i]
							+ m_pCurrMap->m_strSubDir + m_pCurrMap->m_chAddChar + "\\");
						pathOfPicture.FileName(m_pCurrMap->m_strPictName);
					}
					else {
						pathOfPicture.Path(m_strMapDirs[i] + m_pCurrMap->m_strSubDir + "\\");
						pathOfPicture.FileName(m_pCurrMap->m_strPictName);
						pathOfPicture.Prefix(pathOfPicture.Prefix() + m_pCurrMap->m_chAddChar);
					}
				} else
					continue;
			}
			else {
				strUID = m_strMapDirs[i] + m_pCurrMap->m_strPictName;
				pathOfPicture.Path(m_strMapDirs[i]);
				pathOfPicture.FileName(m_pCurrMap->m_strPictName);
				pathOfPicture.Prefix(pathOfPicture.Prefix() + m_pCurrMap->m_chAddChar);
			}

			if (0 == _access(pathOfPicture.Path(), 04)) {
			BOOL fHasToMatch = m_bMatchMapName || m_strDQ.GetMatchMapName(lObjNr);

				if(!fHasToMatch || MatchMapName(m_pCurrMap->m_strMapUID, strUID))
				{
					bHavePictureFound = TRUE;
					break;
				}
			}
		}
		::SetErrorMode(nOldErrMode);
		if (!bHavePictureFound)
			return FALSE;
	}

	if (!fileOfPicture.Open(pathOfPicture.Path(), CFile::modeRead | CFile::shareDenyWrite | CFile::typeBinary))
		return FALSE;
	if (!m_pPicture->Attach(&fileOfPicture))
		return FALSE;
	if (!m_pPicture->SetPictName(pathOfPicture.Path()))
        return FALSE;

	if (!m_pPicture->ReadHeader(NULL, m_pCurrMap->m_bHaveSubFiles ? m_pCurrMap->m_nSubfile : 0)) {
		m_pPicture->Detach();
		return FALSE;
	}

// ggf. GCP's korrigieren (s. PolyGIS, jedes Bild hat eine eigene Größe)
BOOL fReSize = TRUE;

	if (m_pPicture->WantsToCorrectGeoPoints()) {
	// Koordinatensystem über die Koordinaten im Bild holen
	GCPList GCPs;
	ITRiASCS *pICS = NULL;

		if (0 == m_pCurrMap->m_strCoordSys.GetLength() ||
			FAILED(CoCreateInstance(CLSID_TRIASCS, NULL, CLSCTX_INPROC_SERVER, 
					IID_ITRiASCS, (LPVOID *)&pICS)) ||
			FAILED(pICS->LoadFromFile(_bstr_t(m_pCurrMap->m_strCoordSys))))
		{
		GCPList listPts;

			m_pPicture->GetGeoPoints(&listPts);
			m_pPicture->GetGeoPointCS((IUnknown **)&pICS, listPts);
		}

	// mit Hilfe dieses Koordinatensystemes die Koordinaten des TRiAS Objektes
	// umrechnen
		for (int i = 0; i < 4; ++i)
			AddToGCPList((CGCP *)m_pCurrMap->m_pListOfGCP->GetAt(i), &GCPs, pICS);

		if (!m_pPicture->CorrectGeoPoints (m_pCurrMap->m_szPicture, GCPs, m_pCurrMap->m_nSubfile)) {
			m_pPicture->Detach();
			if (NULL != pICS)
				pICS -> Release();
			return FALSE;
		}

		for (int j = 0; j < 4; ++j)
			CorrectGCP (GCPs[j], (CGCP *)m_pCurrMap->m_pListOfGCP->GetAt(j), pICS);

		fReSize = FALSE;
		if (NULL != pICS)
			pICS -> Release();
	}

// Palette behandeln
    if (m_pPicture->KnowsPaletteBeforeDrawing()) 
        HandlePalette(m_pPicture);

BOOL ret;
CRect rcSrc, rcDst;

//CSize szVwpExt = pDC->GetViewportExt();
CSize szVwpExt = GetRealViewportSize(pDC, pTarget);
PICT_COLOR cs = m_pPicture->GetColorspace();

	if (PICT_COLOR_MONOWIZ == cs || PICT_COLOR_MONOBIZ == cs || PICT_COLOR_PALETTE == cs) {
		PALETTEENTRY pe;
		_ASSERTE(pVI->isType() & TPFlaeche);
		::GetPaletteEntries(DEX_GetActivePalette(), ((FVisInfo*) pVI) ->SecColor().Red(), 1, &pe);
		m_pPicture->SetTransparency( m_nTranspChannel, RGB(pe.peRed, pe.peGreen, pe.peBlue));
	}

	if (DT_RASDISPLAY == cap) {
		rcDst = CalculateDstArea(pDC, pTarget, CRect(-5, szVwpExt.cy + 5, szVwpExt.cx + 5, -5));
		rcSrc = CalculateSrcArea(pDC, rcDst, fReSize);

	// zur Sicherheit begrenzen; falls doch noch Rundungsfehler 
	// auftreten
		if (rcSrc.left < 0)
			rcSrc.left = 0;
		if (rcSrc.top < 0)
			rcSrc.top = 0;

		rcSrc.bottom = min(rcSrc.bottom, m_pPicture->GetPictRect().bottom);
		rcSrc.right = min(rcSrc.right, m_pPicture->GetPictRect().right);

        if (m_pPicture->KnowsPaletteBeforeDrawing())
		    ret = m_pPicture->Draw(pDC, &rcSrc, &rcDst, TRUE);
        else {
		CStdThunkImpl<CKartenCtrl, CPicture::HandlePaletteFunc> 
            thunk(this, &CKartenCtrl::HandlePalette);

            ret = m_pPicture->Draw(pDC, &rcSrc, &rcDst, TRUE, thunk.GetThunk());
	    }
    } 
	else {								// muss'n Rasterdrucker sein (s.o.)
	int	nBandSize = 256;
	int	nBandDiff;
	int	nBands=0;

		rcDst = CalculateDstArea(pDC, pTarget, CRect(-5, szVwpExt.cy + 5, szVwpExt.cx + 5, -5));

	CRect	rcBand = rcDst;
	CRect	rcViewBand;

		rcBand.bottom = rcBand.top - nBandSize;
		rcSrc = CalculateSrcArea(pDC, rcBand, fReSize); // _rcDst );
		if (0 != ( nBandDiff = rcSrc.Height() )) {
			nBandDiff = nBandSize / nBandDiff;
			nBandDiff *= 2;
		}
		nBandDiff = max( nBandDiff, 10 );
		nBandDiff = 0;

		while( rcBand.top > rcBand.bottom) {
			rcViewBand = CalculateDstArea(pDC, pTarget, rcBand);
			rcSrc = CalculateSrcArea(pDC, rcViewBand, fReSize);
			rcSrc.top = __max(rcSrc.top, 0);

//			TRACE( "%ld\t%ld\t%ld\t%ld\t", _rcSrc.left, _rcSrc.top, _rcSrc.right, _rcSrc.bottom );
//			TRACE( "%ld\t%ld\t%ld\t%ld\n", rcBand.left, rcBand.top, rcBand.right, rcBand.bottom );

			m_pPicture->Draw(pDC, &rcSrc, &rcBand);
			
			rcBand.OffsetRect( 0, -(nBandSize + nBandDiff));
			rcBand.bottom = max(rcBand.bottom, rcDst.bottom);
			nBands++;
		}
		ret = TRUE;
	}

	m_pPicture->Detach();
	fileOfPicture.Close();
	return ret;
}

// Palette behandeln
BOOL CKartenCtrl::HandlePalette(CPicture *pPicture)
{
	m_pCurrMap->m_clut.SetPalette(pPicture);

CString	strPalType;
DWORD w = 0;

	if (m_strViewPalette.IsEmpty()) {
        _ASSERTE(NULL != m_pVI);
		::AfxExtractSubString(strPalType, m_pVI->VisName(), 0, ';');
	}
    else
		strPalType = m_strViewPalette;

	if (!m_listOfPalTypes.Lookup(strPalType, (void *&)w))
		w = 0;

	pPicture->SetClut(m_pCurrMap->m_clut.GetPalette((int)w), 
        pPicture->GetUsedColors());
    return TRUE;
}

BOOL CKartenCtrl::ParseVisInfoString(DWORD dwObjNr, LPCTSTR pszVI) 
{
	int			field = 0;
	CString		strMapName, strVI, S, strUID;
#ifdef _NEWCODE
	double		x1, y1, x2, y2;
#else
	long		x1, y1, x2, y2;
#endif
	char		ch;
	int			i;

bool fLeaveSpaces = false;
int iSpacesToSkip = 0;

	for (i = 0, ch = pszVI[i]; ch; ch = pszVI[++i]) {
		switch(ch) {
		case ' ' :
			if (fLeaveSpaces) {
				strVI += ' ';
				++iSpacesToSkip;
			}
			else if (0 == field++)
				strVI += ' ';
			break;

		case '\r' :
		case '\n' :
		case '\t' :
			if (0 == field++)
				strVI += ' ';
			break;

		case '\"':
			fLeaveSpaces = !fLeaveSpaces;
			if (!fLeaveSpaces)
				field = 0;
			break;

		default :
			field = 0;
			strVI += ch;
		}
	}

	_ASSERTE(!fLeaveSpaces);		// '"' müssen paarig sein
	if (fLeaveSpaces)
		return FALSE;

// Extraktion des Kartennamens
	field = 0;
	if (iSpacesToSkip > 0) {
	// evtl. space im Kartennamen
		strMapName.Empty();
		for (int j = 0; j <= iSpacesToSkip; ++j) {
		CString str;
		
			if (!::AfxExtractSubString(str, strVI, field++, ' '))
				break;
			if (j > 0)
				strMapName += " ";
			strMapName += str;
		}
	}
	else
		::AfxExtractSubString(strMapName, strVI, field++, ' ');

// ggf. hat Kartenname die Struktur 
// 'BasisVerzeichnis@SubVerzeichnisPrefix@SubVerzeichnisSuffixOfMain@KartenName@LevelCount@CoordSys'
CString strBaseDir;
CString strSubDir;
CString strSuffix;
CString strCoordSys;
BOOL fUsesSubDirs = FALSE;
BOOL fModifiesSubDirs = FALSE;
int nSubLevels = 0;

	if (::AfxExtractSubString(strBaseDir, strMapName, 0, '@')) {		// BasisVerzeichnis
	CString strOrgMapName = strMapName;

		if (::AfxExtractSubString(strSubDir, strOrgMapName, 1, '@')) {	// SubVerzeichnisPrefix
			if (!strSubDir.IsEmpty())
				strSubDir = "\\" + strSubDir;

			if (!::AfxExtractSubString(strSuffix, strOrgMapName, 2, '@'))	// SubVerzeichnisSuffixOfMain	
				return FALSE;		// snh

			if (!strSuffix.IsEmpty())
				fModifiesSubDirs = TRUE;

			if (!::AfxExtractSubString(strMapName, strOrgMapName, 3, '@'))	// KartenName	
				return FALSE;		// snh

		long iLevels = 0;

			if (::LAfxExtractSubLong(iLevels, strOrgMapName, 4, '@'))		// LevelCount
				nSubLevels = iLevels;

			if (::AfxExtractSubString(strCoordSys, strOrgMapName, 5, '@'))		// CoordSys
				nSubLevels = iLevels;

			fUsesSubDirs = TRUE;
		}
		else {
			strBaseDir.Empty();
		}
	}

// Unique Ident enthält vollständigen Namen (komplette Nomenklatur)
	GetUniqueIdentValue(dwObjNr, S);
	::AfxExtractSubString(strUID, S, 2, '@');
	if (strUID.IsEmpty()) {
		if (fUsesSubDirs) {
			strUID = S;		// UIdent enthält den letzten Teil des Verzeichnisses
			strBaseDir = S;
		} else 
			::AfxExtractSubString(strUID, strMapName, 0, _T('.'));
	}

	if (!m_listOfMaps.Lookup (strUID, (CObject *&)m_pCurrMap)) {
		m_pCurrMap = new CInfoForMap;
		m_pCurrMap->m_strPictName = strMapName;
		m_pCurrMap->m_strMapUID = strUID;
		m_pCurrMap->m_bUsesSubDirs = fUsesSubDirs;
		if (fUsesSubDirs) {
			m_pCurrMap->m_strBaseDir = strBaseDir;
			m_pCurrMap->m_strSubDir = strSubDir;
			m_pCurrMap->m_strDirSuffix = strSuffix;
			m_pCurrMap->m_bModifiesSubDirs = fModifiesSubDirs;
			m_pCurrMap->m_strCoordSys = strCoordSys;
		}
		if (0 != nSubLevels)
			m_pCurrMap->m_nSubLevels = nSubLevels;
		m_listOfMaps.SetAt(strUID, (CObject *&) m_pCurrMap);
	}

// Die ersten 2 Werte enthalten die Größe der Bitmap
#ifdef _NEWCODE
	::LAfxExtractSubDouble(x1, strVI, field++, ' ');
	::LAfxExtractSubDouble(y1, strVI, field++, ' ');
	m_pCurrMap->m_szPicture.cx = x1;
	m_pCurrMap->m_szPicture.cy = y1;
#else
	::LAfxExtractSubLong(x1, strVI, field++, ' ');
	::LAfxExtractSubLong(y1, strVI, field++, ' ');
	m_pCurrMap->m_szPicture.cx = (int)x1;
	m_pCurrMap->m_szPicture.cy = (int)y1;
#endif

// für die GCP-Liste holen wir uns die Eckkoordinaten der Karte

// Ecken der Karte (links unten, rechts unten, rechts oben, links oben)
long MapR[N_COORDS];					
long MapH[N_COORDS];

OBJSTATISTIK OS;

	INITSTRUCT(OS, OBJSTATISTIK);
	OS.lONr	= dwObjNr;
	DEX_GetObjStatistik(OS);
	if (N_COORDS != OS.lCnt)
		return FALSE;		// kein Polygon mit 5 Punkten

	memset(MapR, 0x00, sizeof(MapR));
	memset(MapH, 0x00, sizeof(MapH));

OBJGEOMETRIE OG;

	INITSTRUCT(OG, OBJGEOMETRIE);

	OG.lONr	 = dwObjNr;
	OG.lCnt	 = OS.lCnt;
	OG.pdblX = (void *)MapR;
	OG.pdblY = (void *)MapH;
	DEX_GetObjGeometrie(OG);

// Prüfen, ob 1. Koordinate der linken unteren Ecke entspricht, sonst drehen	#fje20000222
	i = 0;
	while (++i < 4 &&  !(MapR[0] < MapR[1] && MapR[2] > MapR[3] && MapH[3] > MapH[0] && MapH[2] > MapH[1])) 
	{
		memmove(&MapR[0], &MapR[1], sizeof(long)*4);
		MapR[4] = MapR[0];
		memmove(&MapH[0], &MapH[1], sizeof(long)*4);
		MapH[4] = MapH[0];
	}

// Die nächsten 8 Werte geben die Abstände vom Rand in den Eckpunkten an
CGCP *pGCP;
	
	for (i = 0; i < N_COORDS - 1; i++) {
		pGCP = (CGCP *)m_pCurrMap->m_pListOfGCP->GetAt(i);
#ifdef _NEWCODE
		::LAfxExtractSubDouble( x1, strVI, field++, ' ' );
		::LAfxExtractSubDouble( y1, strVI, field++, ' ' );

		pGCP->m_ptlCoord.x = MapR[i];	// Koordinaten des Referenzpunktes
		pGCP->m_ptlCoord.y = MapH[i];
		pGCP->m_ptlPict.x = x1;			// erst mal nur Randoffsets eintragen; weiter s.u.
		pGCP->m_ptlPict.y = y1;
#else
		::LAfxExtractSubLong(x1, strVI, field++, ' ');
		::LAfxExtractSubLong(y1, strVI, field++, ' ');

		pGCP->m_ptlCoord.x = MapR[i];	// Koordinaten des Referenzpunktes
		pGCP->m_ptlCoord.y = MapH[i];
		pGCP->m_ptlPict.x = x1;			// erst mal nur Randoffsets eintragen; weiter s.u.
		pGCP->m_ptlPict.y = y1;
#endif
	}

// aus den eingetragenen Randoffsets und der Bildateigröße die Lage der
// Referenzpunkte im Bild berechnen
// - für den Bildverarbeiter ist im Bild links oben (0,0); TRiAS zeichnet aber mit links
//   links unten (0,0) -> die Koordinaten müssen daher vertauscht werden...
	x1 = m_pCurrMap->m_szPicture.cx;
	y1 = m_pCurrMap->m_szPicture.cy;

	pGCP = (CGCP *) m_pCurrMap->m_pListOfGCP->GetAt(0);
	pGCP->m_ptlPict.y = y1 - pGCP->m_ptlPict.y;
	
	pGCP = (CGCP *) m_pCurrMap->m_pListOfGCP->GetAt(1);
	pGCP->m_ptlPict.x = x1 - pGCP->m_ptlPict.x; 
	pGCP->m_ptlPict.y = y1 - pGCP->m_ptlPict.y;
	
	pGCP = (CGCP *) m_pCurrMap->m_pListOfGCP->GetAt(2);
	pGCP->m_ptlPict.x = x1 - pGCP->m_ptlPict.x;
	
//	pGCP = (CGCP *) m_pCurrMap->m_pListOfGCP->GetAt(3);
//	pGCP->m_ptlPict.y = y1 - pGCP->m_ptlPict.y;

// Im weiteren kommen direkte Punktzuordnungen
#ifdef _NEWCODE
	for (i = N_COORDS - 1; ; i++) {
		if (!::LAfxExtractSubDouble( x1, strVI, field++, ' ' )
			|| !::LAfxExtractSubDouble( y1, strVI, field++, ' ' )
			|| !::LAfxExtractSubDouble( x2, strVI, field++, ' ' )
			|| !::LAfxExtractSubDouble( y2, strVI, field++, ' ' ) )
			break;

		pGCP = new CGCP;
		m_pCurrMap->m_pListOfGCP->SetAtGrow( i, pGCP );
		pGCP->m_ptlCoord.x = x1;
		pGCP->m_ptlCoord.y = y1;
		pGCP->m_ptlPict.x = x2;
		pGCP->m_ptlPict.y = y2;
	}
#else
	for (i = N_COORDS - 1; /**/; i++) {
		if (!::LAfxExtractSubLong(x1, strVI, field++, ' ')
			|| !::LAfxExtractSubLong(y1, strVI, field++, ' ')
			|| !::LAfxExtractSubLong(x2, strVI, field++, ' ')
			|| !::LAfxExtractSubLong(y2, strVI, field++, ' '))
		{
			break;
		}

		pGCP = new CGCP;
		m_pCurrMap->m_pListOfGCP->SetAtGrow(i, pGCP);
		pGCP->m_ptlCoord.x = x1;
		pGCP->m_ptlCoord.y = y1;
		pGCP->m_ptlPict.x = x2;
		pGCP->m_ptlPict.y = y2;
	}
#endif
	return TRUE;
}

#ifdef _NEWCODE
/////////////////////////////////////////////////////////////////////
// Koordinatenumrechnung mit double-Zahlen

/////////////////////////////////////////////////////////////////////
// OC -> DC
DPOINT CKartenCtrl::D_OCtoDC(const POINTL& ptOC) 
{
COORDCONVERT	C;
POINTL	ptlOC;
POINT	ptiDC;

 	C.lpPt = &ptiDC;
	C.lpPkt = (long*) &ptlOC;
	ptlOC.x = ptOC.x;
	ptlOC.y = ptOC.y;
	DEX_OCtoDCEx( C );

DPOINT	ptDC;

	ptDC.x = ptiDC.x;
	ptDC.y = ptiDC.y;
	return ptDC;
}

DPOINT CKartenCtrl::D_OCtoDC(const DPOINT& ptOC) 
{
COORDCONVERT	C;
POINTL	ptlOC;
POINT	ptiDC;

 	C.lpPt = &ptiDC;
	C.lpPkt = (long*) &ptlOC;
	ptlOC.x = froundl( ptOC.x );
	ptlOC.y = froundl( ptOC.y );
	DEX_OCtoDCEx( C );

DPOINT	ptDC;

	ptDC.x = ptiDC.x;
	ptDC.y = ptiDC.y;
	return ptDC;
}

/////////////////////////////////////////////////////////////////////
// DC -> OC

DPOINT CKartenCtrl::D_DCtoOC(const DPOINT& ptDC) 
{
COORDCONVERT	C;
POINTL	ptlDC;
POINT	ptiOC;

	C.lpPkt = (long*) &ptlDC;
 	C.lpPt = &ptiOC;
	ptlDC.x = froundl( ptDC.x );
	ptlDC.y = froundl( ptDC.y );
	DEX_OCtoDCEx( C );

DPOINT	ptOC;

	ptOC.x = ptiOC.x;
	ptOC.y = ptiOC.y;
	return ptOC;
}

DPOINT CKartenCtrl::D_DCtoOC( const POINTL& ptDC) 
{
COORDCONVERT	C;
POINTL	ptlDC;
POINT	ptiOC;

	C.lpPkt = (long*) &ptlDC;
 	C.lpPt = &ptiOC;
	ptlDC.x = ptDC.x;
	ptlDC.y = ptDC.y;
	DEX_OCtoDCEx( C );

DPOINT	ptOC;

	ptOC.x = ptiOC.x;
	ptOC.y = ptiOC.y;
	return ptOC;
}

DPOINT CKartenCtrl::D_DCtoOC( const POINT& ptDC) 
{
COORDCONVERT	C;
POINTL	ptlDC;
POINT	ptiOC;

	C.lpPkt = (long*) &ptlDC;
 	C.lpPt = &ptiOC;
	ptlDC.x = ptDC.x;
	ptlDC.y = ptDC.y;
	DEX_OCtoDCEx( C );

DPOINT	ptOC;

	ptOC.x = ptiOC.x;
	ptOC.y = ptiOC.y;
	return ptOC;
}
#endif // _NEWCODE

BOOL CKartenCtrl::SelectSubFile() 
{
	ASSERT_VALID(m_pCurrMap);

double	mapWidth;
double	rx;

#ifdef _NEWCODE
	//////////////////////////////////////////
	// neuer Code (erstmal testweise)
	CDPoint	ptTL, ptBR;
	CDRect	rcMapInDC;
	ptTL = D_OCtoDC( ( (CGCP*) m_pCurrMap->m_pListOfGCP->GetAt( 0 ) )->m_ptlCoord );
	ptBR = D_OCtoDC( ( (CGCP*) m_pCurrMap->m_pListOfGCP->GetAt( 2 ) )->m_ptlCoord );
	rcMapInDC.SetRect( ptTL, ptBR );
	mapWidth = rcMapInDC.Width();
	rx = m_pCurrMap->m_szPicture.cx / mapWidth;
	// ...neuer Code (erstmal testweise)
	//////////////////////////////////////////
#else
COORDCONVERT	C;
POINTL			ptlP;
POINT			ptP;
	
 	C.lpPt = &ptP; 
	C.lpPkt = (long *)&ptlP;
	ptlP = ((CGCP *) m_pCurrMap->m_pListOfGCP->GetAt(1))->m_ptlCoord; 
	DEX_OCtoDCEx(C);	// ptlP --> ptP
	mapWidth = ptP.x;

	ptlP = ((CGCP *) m_pCurrMap->m_pListOfGCP->GetAt(0))->m_ptlCoord; 
	DEX_OCtoDCEx(C);	// ptlP --> ptP
	mapWidth -= ptP.x;
	if (mapWidth < m_minSize )
		return FALSE;
	rx = (double) m_pCurrMap->m_szPicture.cx / mapWidth;
#endif // _DEBUG

//	if (rx > 128.0)
//		return FALSE;

	m_pCurrMap->m_nSubfile =
				rx > 256.0 ? 8 :
				rx > 128.0 ? 7 :
				rx >  64.0 ? 6 :
				rx >  32.0 ? 5 :
				rx >  16.0 ? 4 :
				rx >   8.0 ? 3 :
				rx >   4.0 ? 2 :
				rx >   2.0 ? 1 :
				0;

	if (m_pCurrMap->m_nSubfile >= m_pCurrMap->m_nSubLevels)
		m_pCurrMap->m_nSubfile = m_pCurrMap->m_nSubLevels-1;

	m_pCurrMap->m_nCropBorder = 0; 
	switch (m_pCurrMap->m_nSubfile) {
	case 0:
		m_pCurrMap->m_chAddChar = m_pCurrMap->m_bModifiesSubDirs ? '1' : '\0'; 
		m_pCurrMap->m_nSampleRate = 1;
		break;

	case 1: 
		m_pCurrMap->m_chAddChar = m_pCurrMap->m_bModifiesSubDirs ? '2' : 'a'; 
		m_pCurrMap->m_nSampleRate = 2;
		break;

	case 2: 
		m_pCurrMap->m_chAddChar = m_pCurrMap->m_bModifiesSubDirs ? '3' : 'b'; 
		m_pCurrMap->m_nSampleRate = 4;
		break;

	case 3: 
		m_pCurrMap->m_chAddChar = m_pCurrMap->m_bModifiesSubDirs ? '4' : 'c'; 
		m_pCurrMap->m_nSampleRate = 8;
		break;

	case 4: 
		m_pCurrMap->m_chAddChar = m_pCurrMap->m_bModifiesSubDirs ? '5' : 'd'; 
		m_pCurrMap->m_nSampleRate = 16;
		break;

	case 5: 
		m_pCurrMap->m_chAddChar = m_pCurrMap->m_bModifiesSubDirs ? '6' : 'e'; 
		m_pCurrMap->m_nSampleRate = 32;
		break;

	case 6: 
		m_pCurrMap->m_chAddChar = m_pCurrMap->m_bModifiesSubDirs ? '7' : 'f'; 
		m_pCurrMap->m_nSampleRate = 64;
		break;

	case 7: 
		m_pCurrMap->m_chAddChar = m_pCurrMap->m_bModifiesSubDirs ? '8' : 'g'; 
		m_pCurrMap->m_nSampleRate = 128;
		break;

	default: 
		m_pCurrMap->m_chAddChar = m_pCurrMap->m_bModifiesSubDirs ? '9' : 'h'; 
		m_pCurrMap->m_nSampleRate = 256;
		break;
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
////
////	Dafür, daß es jetzt so richtig in die Vollen geht, leisten wir uns mal
////	                      'nen DICKEN KOMMENTAR
////
//// der lautet: Code NICHT ANFASSEN UND IHN SO NEHMEN, wie er ist (ich mach's
////                   auch nicht mehr (das Anfassen)
////
////                                   :-)
////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

typedef struct tagLine {
	double A, B, C;
} LINE;

#define FROUND(d) \
    ((d)-floor(d)>0.5?ceil(d):floor(d))

static	BOOL	QuadIntersect( POINTL P1[4], POINTL P2[4], POINTL PS[4] );
static	void	LineParam(POINTL const &rP1, POINTL const &rP2, LINE &rL);
static	BOOL	LineCutPoint(LINE const &rL1, LINE const &rL2, POINTL &rP);
static	BOOL	StraithCutPoint(POINTL const &rPA1, POINTL const &rPA2, 
    POINTL const &rPB1, POINTL const &rPB2, POINTL &P, BOOL *bIsInner = NULL);
static	BOOL	RubberBand( short nCoords, POINTL *pSPoints, POINTL *dPoints, POINTL lpCs1[4], POINTL lpCs2[4] );
static	BOOL	PS_Intersect(POINTL P1[4], POINTL P2[4], POINTL &PS);

//////////////////////////////////////////////////////////////////////////////
// Der Zielbereich für die Darstellung wird bestmöglich an die Kartenlage
// und Geometrie angepasst
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
// die Rechtecke laufen alle andersrum; deshalb geht
// "IntersectRect" nicht ... also Handarbeit... :-(
static inline CRect IntersectViewRects( LPCRECT lpRect1, LPCRECT lpRect2 )
{
	CRect	rcI;
	rcI.SetRectEmpty();

	if (lpRect1->right <= lpRect2->left || lpRect2->top <= lpRect1->bottom
		|| lpRect2->right <= lpRect1->left || lpRect1->top <= lpRect2->bottom )
		return rcI;

	rcI.SetRect( max( lpRect1->left, lpRect2->left ),
			min( lpRect1->top, lpRect2->top ),
			min( lpRect1->right, lpRect2->right ),
			max( lpRect1->bottom, lpRect2->bottom )
			);
	return rcI;
}

#ifdef _NEWCODE
//////////////////////////////////////////
// neuer Code (erstmal testweise)
static	DPOINT	MapPoints[4];			// Karten-Polygon
static	DPOINT	PicPoints[4];			// (B)itmap
static	DPOINT	ClientPoints[4];		// (C)lient-Area in geogr. Koordinaten
static	DPOINT	IsectPoints[4];			// (I)ntersection-Polygon
// ...neuer Code (erstmal testweise)
//////////////////////////////////////////
#else
static	POINTL	MapPoints[4];			// Karten-Polygon
static	POINTL	PicPoints[4];			// (B)itmap
static	POINTL	ClientPoints[4];		// (C)lient-Area in geogr. Koordinaten
static	POINTL	IsectPoints[4];			// (I)ntersection-Polygon
#endif

#ifdef _NEWCODE
CDRect CKartenCtrl::CalculateDstArea(CDC *pDC)
#else
CRect CKartenCtrl::CalculateDstArea(CDC *pDC, CDC *pTarget, CRect& rcDst)
#endif
{
#ifdef _NEWCODE
//////////////////////////////////////////
// neuer Code (erstmal testweise)
	int i;
//	CSize	szView = pDC->GetViewportExt();
	CSize szView = GetRealViewportSize(pDC, pTarget);
//	if (pDC->IsPrinting())
//		szView.cy = -szView.cy;

	CDRect	rcView( -5, szView.cy + 5, szView.cx + 5, -5 );

	for (i = 0; i < N_COORDS - 1; i++ )
	{
		MapPoints[i] = ( (CGCP*) m_pCurrMap->m_pListOfGCP->GetAt(i) )->m_ptlCoord;
		PicPoints[i] = ( (CGCP*) m_pCurrMap->m_pListOfGCP->GetAt(i) )->m_ptlPict;
	}
	ClientPoints[0] = D_DCtoOC( CDPoint( rcDst.left,  rcDst.bottom ) );
	ClientPoints[1] = D_DCtoOC( CDPoint( rcDst.right, rcDst.bottom ) );
	ClientPoints[2] = D_DCtoOC( CDPoint( rcDst.right, rcDst.top    ) );
	ClientPoints[3] = D_DCtoOC( CDPoint( rcDst.left,  rcDst.top    ) );
	QuadIntersect( IsectPoints, ClientPoints, MapPoints );	// Überschneidung ermitteln
	CDPoint	ptTopLeft = D_OCtoDC(
		CDPoint(
			( IsectPoints[3].x + IsectPoints[0].x ) / 2,
			( IsectPoints[3].y + IsectPoints[2].y ) / 2
		)
		);
	CDPoint	ptBtmRight = D_OCtoDC(
		CDPoint(
			( IsectPoints[1].x + IsectPoints[2].x ) / 2,
			( IsectPoints[1].y + IsectPoints[0].y ) / 2
		)
		);
	rcView.SetRect( ptTopLeft, ptBtmRight );
#else
	ASSERT_VALID( m_pCurrMap );

int	i;
//CSize szView = pDC->GetViewportExt();
CSize szView = GetRealViewportSize(pDC, pTarget);

//	if (pDC->IsPrinting() || pTarget->IsPrinting())
//		szView.cy = -szView.cy;

CRect rcView(-5, szView.cy + 5, szView.cx + 5, -5);

	rcView = IntersectViewRects(rcView, rcDst);

COORDCONVERT	C;
POINTL			ptlP;
POINT			ptP;

	memset(MapPoints, 0x00, sizeof(MapPoints));
	memset(PicPoints, 0x00, sizeof(PicPoints));
	memset(ClientPoints, 0x00, sizeof(ClientPoints));
	memset(IsectPoints, 0x00, sizeof(IsectPoints));

	for (i = 0; i < N_COORDS - 1; i++ )
	{
		MapPoints[i] = ((CGCP *) m_pCurrMap->m_pListOfGCP->GetAt(i))->m_ptlCoord;
		PicPoints[i] = ((CGCP *) m_pCurrMap->m_pListOfGCP->GetAt(i))->m_ptlPict;
	}

	C.lpPt = &ptP;

	ptP.x = rcView.left ; ptP.y = rcView.bottom; C.lpPkt = (long *) &ClientPoints[0]; DEX_DCtoOCEx(C);
	ptP.x = rcView.right; ptP.y = rcView.bottom; C.lpPkt = (long *) &ClientPoints[1]; DEX_DCtoOCEx(C);
	ptP.x = rcView.right; ptP.y = rcView.top   ; C.lpPkt = (long *) &ClientPoints[2]; DEX_DCtoOCEx(C);
	ptP.x = rcView.left ; ptP.y = rcView.top   ; C.lpPkt = (long *) &ClientPoints[3]; DEX_DCtoOCEx(C);

	QuadIntersect(ClientPoints, MapPoints, IsectPoints);					// Überschneidung ermitteln

	C.lpPkt = (long *)&ptlP;						// am besten passendes Rechteck ermitteln

	ptlP.x = (IsectPoints[3].x + IsectPoints[0].x) / 2;
	ptlP.y = (IsectPoints[3].y + IsectPoints[2].y) / 2;
	DEX_OCtoDCEx(C);
	rcView.left = ptP.x;
	rcView.top = ptP.y;

	ptlP.x = (IsectPoints[1].x + IsectPoints[2].x) / 2;
	ptlP.y = (IsectPoints[1].y + IsectPoints[0].y) / 2;
	DEX_OCtoDCEx(C);
	rcView.right = ptP.x;
	rcView.bottom = ptP.y;
#endif		// _NEWCODE

	return rcView;
}

//////////////////////////////////////////////////////////////////////////////
// Für einen vorgegebenen Zielbereich wird der zugehörige Quellbereich
// ermittelt
//////////////////////////////////////////////////////////////////////////////

#ifdef _NEWCODE
CDRect CKartenCtrl::CalculateSrcArea(CDC* pDC, CDRect& rcDst, BOOL fReSize)
#else
CRect CKartenCtrl::CalculateSrcArea(CDC* pDC, CRect& rcDst, BOOL fReSize)
#endif
{
	ASSERT_VALID( m_pCurrMap );

#ifdef _NEWCODE
	CDRect	rcSrc;

	DPOINT	dPD[4];
	DPOINT	dPS[4];
	memset(dPD,0x00,sizeof(dPD));
	memset(dPS,0x00,sizeof(dPS));
	dPD[0] = D_DCtoOC( CDPoint( rcDst.left,  rcDst.bottom ) );
	dPD[1] = D_DCtoOC( CDPoint( rcDst.right, rcDst.bottom ) );
	dPD[2] = D_DCtoOC( CDPoint( rcDst.right, rcDst.top    ) );
	dPD[3] = D_DCtoOC( CDPoint( rcDst.top,   rcDst.top    ) );

	RubberBand( 4, &dPS[0], &dPD[0], MapPoints, PicPoints );

	rcSrc.left   = ( dPS[3].x + dPS[0].x ) / 2;
	rcSrc.top    = ( dPS[3].y + dPS[2].y ) / 2;
	rcSrc.right  = ( dPS[1].x + dPS[2].x ) / 2;
	rcSrc.bottom = ( dPS[1].y + dPS[0].y ) / 2;

	if (fReSize) {
		rcSrc.left   += m_pCurrMap->m_nSampleRate + 1;
		rcSrc.top    += m_pCurrMap->m_nSampleRate + 1;
		rcSrc.right  += m_pCurrMap->m_nSampleRate + 1;
		rcSrc.bottom += m_pCurrMap->m_nSampleRate + 1;

		rcSrc.left   /= m_pCurrMap->m_nSampleRate;
		rcSrc.top    /= m_pCurrMap->m_nSampleRate;
		rcSrc.right  /= m_pCurrMap->m_nSampleRate;
		rcSrc.bottom /= m_pCurrMap->m_nSampleRate;
	}
	rcSrc.NormalizeRect();
	rcSrc.InflateRect( m_pCurrMap->m_nCropBorder, m_pCurrMap->m_nCropBorder );
#else
CRect rcSrc;

//POINTL lPD[4];			// (D)estination in geogr. Koordinaten
POINTL lPS[4];			// (S)ource in der Bitmap

//	memset(lPD, 0x00, sizeof(lPD));
	memset(lPS, 0x00, sizeof(lPS));

//COORDCONVERT C;
//POINT ptP;

//	C.lpPt = &ptP;

//	ptP.x = rcDst.left ; ptP.y = rcDst.bottom; C.lpPkt = (long*) &lPD[0]; DEX_DCtoOCEx(C);
//	ptP.x = rcDst.right; ptP.y = rcDst.bottom; C.lpPkt = (long*) &lPD[1]; DEX_DCtoOCEx(C);
//	ptP.x = rcDst.right; ptP.y = rcDst.top   ; C.lpPkt = (long*) &lPD[2]; DEX_DCtoOCEx(C);
//	ptP.x = rcDst.left ; ptP.y = rcDst.top   ; C.lpPkt = (long*) &lPD[3]; DEX_DCtoOCEx(C);

	RubberBand(4, &lPS[0], IsectPoints /* &lPD[0] */, MapPoints, PicPoints);

	rcSrc.left   = (int) ( lPS[3].x + lPS[0].x ) / 2;
	rcSrc.top    = (int) ( lPS[3].y + lPS[2].y ) / 2;
	rcSrc.right  = (int) ( lPS[1].x + lPS[2].x ) / 2;
	rcSrc.bottom = (int) ( lPS[1].y + lPS[0].y ) / 2;

	if (fReSize) {
		rcSrc.left   += m_pCurrMap->m_nSampleRate - 1;
		rcSrc.top    += m_pCurrMap->m_nSampleRate - 1;
		rcSrc.right  -= ( m_pCurrMap->m_nSampleRate - 1 );
		rcSrc.bottom -= ( m_pCurrMap->m_nSampleRate - 1 );

		rcSrc.left   /= m_pCurrMap->m_nSampleRate;
		rcSrc.top    /= m_pCurrMap->m_nSampleRate;
		rcSrc.right  /= m_pCurrMap->m_nSampleRate;
		rcSrc.bottom /= m_pCurrMap->m_nSampleRate;
	}
	rcSrc.NormalizeRect();
	rcSrc.InflateRect(m_pCurrMap->m_nCropBorder, m_pCurrMap->m_nCropBorder);
#endif // _NEWCODE

	return rcSrc;
}

//////////////////////////////////////////////////////////////////////////////
// QuadIntersect - ermittelt die Intersection zweier Vierecke
//
//	POINTL	P1[4]	- Koordinatenliste des ersten Vierecks
//	POINTL	P2[4]	- Koordinatenliste des zweiten Vierecks
//	POINTL	PI[4]	- Koordinatenliste des resultierenden Vierecks
//
//////////////////////////////////////////////////////////////////////////////

inline double Area (POINTL P1, POINTL P2, POINTL P3)
{
    return (
            (double)P1.x * (double)(P2.y - P3.y) +
            (double)P2.x * (double)(P3.y - P1.y) +
            (double)P3.x * (double)(P1.y - P2.y)
        ) / 2;
}

#ifdef _NEWCODE
static	BOOL	QuadIntersect( DPOINT PS[4], const DPOINT P1[4], const DPOINT P2[4] )
#else
static	BOOL	QuadIntersect( POINTL P1[4], POINTL P2[4], POINTL PS[4] )
#endif
{
	int	i, ii;
	short	bP1Inner[4];	// Pkt.Def. Client(P1) : 0 außen, 1 innen
	short	bP2Inner[4];	// Pkt.Def. Map(P2) : 0 außen, 1 innen
	short	bP1Change = 0;
	short	bP2Change = 0;
	double	x1, y1, x2, y2, x3, y3;


// Erstes Viereck - P1 = Clientpoints
	for (i = 0; i < 4; i++ )
	{
		bP1Inner[i] = 1;

		x3 = (double) P1[i].x;
		y3 = (double) P1[i].y;

		for (ii = 0; ii < 4; ii++ )
		{
			x1 = (double) P2[ii].x;
			y1 = (double) P2[ii].y;
			x2 = (double) ( ii == 3 ? P2[0].x : P2[ii+1].x );
			y2 = (double) ( ii == 3 ? P2[0].y : P2[ii+1].y );

		// Fläche des Dreiecks P1, P2, P3 (falls negativ - P3 außerhalb)
			if (x1 * ( y2 - y3 ) + x2 * ( y3 - y1 ) + x3 * ( y1 - y2 ) < 0.0 )
			{
				bP1Inner[i] = 0;	// Punkt außerhalb P2
				break;
			}
		}
		if (i > 0 && bP1Inner[i] != bP1Inner[i-1] )
			bP1Change++;
	}

// Zweites Viereck - P2 = Mappoints
	for (i = 0; i < 4; i++ )		// Clip-Area-Polygon
	{
		bP2Inner[i] = 1;

		x3 = (double) P2[i].x;
		y3 = (double) P2[i].y;

		for (ii = 0; ii < 4; ii++ )	// Karten-Polygon
		{
			x1 = (double) P1[ii].x;
			y1 = (double) P1[ii].y;

			x2 = (double) ( ii == 3 ? P1[0].x : P1[ii+1].x );
			y2 = (double) ( ii == 3 ? P1[0].y : P1[ii+1].y );

			if (x1 * ( y2 - y3 ) + x2 * ( y3 - y1 ) + x3 * ( y1 - y2 ) < 0.0 )
			{
				bP2Inner[i] = 0;	// Punkt außerhalb P1
				break;
			}
		}
		if (i > 0 && bP2Inner[i] != bP2Inner[i-1] )
			bP2Change++;
	}


	int	np1, np2;
#ifdef _NEWCODE
	DPOINT	P10, P1v, P1n;					// Punkt, Vorgänger, Nachfolger
	DPOINT	P20, P2v, P2n;					// Punkt, Vorgänger, Nachfolger
	DPOINT	PS1, PS2;					// Schnittpunkte 1, 2
#else
	POINTL	P10, P1v, P1n;					// Punkt, Vorgänger, Nachfolger
	POINTL	P20, P2v, P2n;					// Punkt, Vorgänger, Nachfolger
	POINTL	PS1, PS2;					// Schnittpunkte 1, 2
#endif

// Auswertung der Schnittmöglichkeiten
	if (bP1Change > 0 || bP2Change > 0)			// Polygone überlappen 	sich ...
	{
		if (bP1Change > 0 && bP2Change > 0)		// ... in Ecken
		{
			for (np1 = 0; np1 < 4; np1++) {
				if (bP1Inner[np1] > 0) 
                    break; 
            }
            P10 = P1[np1];
			
            for (np2 = 0; np2 < 4; np2++) {
                if (bP2Inner[np2] > 0) 
                    break; 
            }
            P20 = P2[np2];

		// KK000921
		// offensichtlich müssen  np1 und np2 um 2 differieren
		// alles etwas durcheinander - Kombinationen sind noch genauer zu bestimmen !!!
		// 	StraithCutPoint ist BOOL - RC auswerten + Koordinaten prüfen !!!

		// KK000921 - Partner suchen, da sonst falsche SP entstehen (np1 + 2 !!!)
			if (2 != abs (np1-np2)) {
		    int npp = np1 + 2;

				if (npp > 3)
					npp -= 4;

				if (bP2Inner[npp] > 0) {	// erst bP1 - fest  mit bP2
					np2 = npp;
					P20 = P2[np2];
				} 
                else {	// falls nicht bP2 fest, nächsten bP1
					npp = np1+1;
				    if (npp > 3)
					    npp -= 4;

					if (bP1Inner[npp] > 0) {
						np1 = npp;
						P10 = P1[np1];
					}

				}
			}
		// KK000921 

			P1n = P1[ np1 == 4 - 1 ?   0 : ( np1 + 1 ) ];
			P1v = P1[ ( np1 == 0       ? 4 : np1 ) - 1 ];
			P2n = P2[ np2 == 4 - 1 ?   0 : ( np2 + 1 ) ];
			P2v = P2[ ( np2 == 0       ? 4 : np2 ) - 1 ];

		// KK000921 - BOOL auswerten ??!! - genauer prüfen - jetzt erst ohne (Standard-Andy)
			StraithCutPoint( P10, P1v, P20, P2n, PS1 );

		// PS1 ist falsch - dafür entsprechende P1 ( ClientPoint) - Koordinate nutzen
			if (!PS_Intersect (P1, P2, PS1)) {	// Koordinaten fehlerhaft
			int npp = np1 + 3;
				
                if (npp > 3)
					npp = npp - 4;
				PS1 = P1[npp];
				ASSERT (np1 == npp);
			}
			
		// KK000921 
			StraithCutPoint(P10, P1n, P20, P2v, PS2);

		// PS2 ist falsch - dafür entsprechende P1 ( ClientPoint) - Koordinate nutzen
			if (!PS_Intersect (P1, P2, PS2)) {	// Koordinaten fehlerhaft - nicht im Testbereich
			int npp = np1 + 1;
				
                if (npp > 3)
					npp = npp - 4;
				PS2 = P1[npp];
				ASSERT(np1 == npp);
			}
		// KK000921 

			switch(np1)	{
			case 0: 
				PS[0] = P10; PS[1] = PS2; PS[2] = P20; PS[3] = PS1; 
				break;
			
			case 1: 
				PS[0] = PS1; PS[1] = P10; PS[2] = PS2; PS[3] = P20; 
				break;

			case 2: 
				PS[0] = P20; PS[1] = PS1; PS[2] = P10; PS[3] = PS2; 
				break;

			case 3: 
				PS[0] = PS2; PS[1] = P20; PS[2] = PS1; PS[3] = P10; 
				break;

			default:
				ASSERT(0 <= np1 && np1 < 4);
				break;
			}
		} 
		else if (bP1Change > 0 && bP2Change == 0)		// ... P1 überlappt P2
		{
			if (bP1Inner[1] == 1 && bP1Inner[2] == 1)	// X11X
			{	// ... von links
				if (bP1Inner[0] == 0 && bP1Inner[3] == 0) {	
				// Standard 0110
					StraithCutPoint( P1[0], P1[1], P2[3], P2[0], PS1 );
					StraithCutPoint( P1[2], P1[3], P2[3], P2[0], PS2 );
					PS[0] = PS1; PS[1] = P1[1]; PS[2] = P1[2]; PS[3] = PS2;
				} 
				else {
					if (1 == bP1Inner[0]) {
				    // Kombination 1110
						StraithCutPoint(P1[3], P1[0], P2[2], P2[3], PS2);
						PS[0] = P1[0]; PS[1] = P1[1]; PS[2] = P1[2]; PS[3] = PS2;
					} 
					else {
					// Kombination 0111
						StraithCutPoint(P1[0], P1[1], P2[3], P2[0], PS1 );
						PS[0] = PS1; PS[1] = P1[1]; PS[2] = P1[2]; PS[3] = P1[3];
					}
				}
			} 
			else if (bP1Inner[2] == 1 && bP1Inner[3] == 1)	//XX11
			{	// ... von oben
				if (bP1Inner[0] == 0 && bP1Inner[1] == 0) {	
				// Standard 0011
					StraithCutPoint( P1[1], P1[2], P2[0], P2[1], PS1 );
					StraithCutPoint( P1[3], P1[0], P2[0], P2[1], PS2 );
					PS[0] = PS2; PS[1] = PS1; PS[2] = P1[2]; PS[3] = P1[3];
				} 
				else {
					if (bP1Inner[0] == 1) {
				    // Kombination 1011
						StraithCutPoint( P1[1], P1[2], P2[0], P2[1], PS1 );
						PS[0] = P1[0]; PS[1] = PS1; PS[2] = P1[2]; PS[3] = P1[3];
					} 
					else {
					// Kombination 0111 - doppelt
						StraithCutPoint( P1[3], P1[0], P2[0], P2[1], PS2 );
						PS[0] = PS2; PS[1] = P1[1]; PS[2] = P1[2]; PS[3] = P1[3];
					}
				}
			} 
			else if (bP1Inner[0] == 1 && bP1Inner[3] == 1 )	//1XX1
			{	// ... von rechts
				if (bP1Inner[1] == 0 && bP1Inner[2] == 0) {	
                // Standard 1001
					StraithCutPoint( P1[0], P1[1], P2[1], P2[2], PS1 );
					StraithCutPoint( P1[2], P1[3], P2[1], P2[2], PS2 );
					PS[0] = P1[0]; PS[1] = PS1; PS[2] = PS2; PS[3] = P1[3];
				} 
				else {
					if (bP1Inner[1] == 1) {
				    // Kombination 1101
						StraithCutPoint( P1[2], P1[3], P2[1], P2[2], PS2 );
						PS[0] = P1[0]; PS[1] = P1[1]; PS[2] = PS2; PS[3] = P1[3];
					} 
					else {
					// Kombination 1011 - doppelt
						StraithCutPoint( P1[0], P1[1], P2[1], P2[2], PS1 );
						PS[0] = P1[0]; PS[1] = PS1; PS[2] = P1[2]; PS[3] = P1[3];
					}
				}
			} 
			else if (bP1Inner[0] == 1 && bP1Inner[1] == 1 )	//11XX
			{	// ... von unten
				if (bP1Inner[2] == 0 && bP1Inner[3] == 0) {	
				// Standard 1100
					StraithCutPoint( P1[3], P1[0], P2[2], P2[3], PS1 );
					StraithCutPoint( P1[1], P1[2], P2[2], P2[3], PS2 );
					PS[0] = P1[0]; PS[1] = P1[1]; PS[2] = PS2; PS[3] = PS1;
				} 
				else {
					if (bP1Inner[1] == 1) {
				    // Kombination 1101 - doppelt
						StraithCutPoint( P1[1], P1[2], P2[2], P2[3], PS2 );
						PS[0] = P1[0]; PS[1] = P1[1]; PS[2] = PS2; PS[3] = P1[3];
					} 
					else {
					// Kombination 1110 - doppelt
						StraithCutPoint( P1[3], P1[0], P2[2], P2[3], PS2 );
						PS[0] = P1[0]; PS[1] = P1[1]; PS[2] = P1[2]; PS[3] = PS2;
					}
				}
			} 
			else {
			// P1 überlappt P2 Streifen als Trapez mit mind. 2 Punkten außen
			// Hier muß geschnitten werden !!!

			// Kombination 1010
				if (bP1Inner[0] == 1 && bP1Inner[1] == 0 && bP1Inner[2] == 1 && bP1Inner[3] == 0) {	
					StraithCutPoint( P1[0], P1[1], P2[1], P2[2], PS1 );
					StraithCutPoint( P1[2], P1[3], P2[3], P2[0], PS2 );
					PS[0] = P1[0]; PS[1] = PS1; PS[2] = P1[2]; PS[3] = PS2;
					return TRUE;
				}

			// Kombination 0101
				if (bP1Inner[0] == 0 && bP1Inner[1] == 1 && bP1Inner[2] == 0 && bP1Inner[3] == 1) {	
					StraithCutPoint( P1[0], P1[1], P2[3], P2[0], PS1 );
					StraithCutPoint( P1[2], P1[3], P2[1], P2[2], PS2 );
					PS[0] = PS1; PS[1] = P1[1]; PS[2] = PS2; PS[3] = P1[3];
					return TRUE;
				}

			// Kombination 1000
				if (bP1Inner[0] == 1 && bP1Inner[1] == 0 && bP1Inner[2] == 0 && bP1Inner[3] == 0) {	
					StraithCutPoint( P1[0], P1[1], P2[1], P2[2], PS1 );
					StraithCutPoint( P1[3], P1[0], P2[2], P2[3], PS2 );
					StraithCutPoint( P1[1], P1[2], P2[2], P2[3], P20 );
					PS[0] = P1[0]; PS[1] = PS1; PS[2] = P20; PS[3] = PS2;
					return TRUE;
				}

			// Kombination 0100
				if (bP1Inner[0] == 0 && bP1Inner[1] == 1 && bP1Inner[2] == 0 && bP1Inner[3] == 0) {	
					StraithCutPoint( P1[0], P1[1], P2[3], P2[0], PS1 );
					StraithCutPoint( P1[2], P1[3], P2[1], P2[2], PS2 );
					StraithCutPoint( P1[2], P1[3], P2[3], P2[0], P20 );

//					StraithCutPoint( P1[1], P1[2], P2[2], P2[3], PS2 );
//					StraithCutPoint( P1[3], P1[0], P2[2], P2[3], P20 );
					PS[0] = PS1; PS[1] = P1[1]; PS[2] = PS2; PS[3] = P20;
					return TRUE;
				}

			// Kombination 0010
				if (bP1Inner[0] == 0 && bP1Inner[1] == 0 && bP1Inner[2] == 1 && bP1Inner[3] == 0) {	
					StraithCutPoint( P1[1], P1[2], P2[0], P2[1], PS1 );
					StraithCutPoint( P1[2], P1[3], P2[3], P2[0], PS2 );
					StraithCutPoint( P1[3], P1[0], P2[0], P2[1], P20 );
					PS[0] = P20; PS[1] = PS1; PS[2] = P1[2]; PS[3] = PS2;
					return TRUE;
				}

			// Kombination 0001
				if (bP1Inner[0] == 0 && bP1Inner[1] == 0 && bP1Inner[2] == 0 && bP1Inner[3] == 1) {	
					StraithCutPoint( P1[3], P1[0], P2[0], P2[1], PS1 );
					StraithCutPoint( P1[1], P1[2], P2[0], P2[1], P20 );
					StraithCutPoint( P1[2], P1[3], P2[1], P2[2], PS2 );
					PS[0] = PS1; PS[1] = P20; PS[2] = PS2; PS[3] = P1[3];
					return TRUE;
				}

			// Hier ist interessant, was noch durchkommt 
				ASSERT(FALSE);
				PS[0] = P1[0]; PS[1] = P1[1]; PS[2] = P1[2]; PS[3] = P1[3];
			}
		} 
		else if (bP1Change == 0 && bP2Change > 0)	// ... P2 überlappt P1
		{
			if (bP2Inner[1] == 1 && bP2Inner[2] == 1)	// x11x
			{				// ... von links
				if (bP2Inner[0] == 0 && bP2Inner[3] == 0) {	
                // Standard 0110
					StraithCutPoint( P2[0], P2[1], P1[3], P1[0], PS1 );
					StraithCutPoint( P2[2], P2[3], P1[3], P1[0], PS2 );
					PS[0] = PS1; PS[1] = P2[1]; PS[2] = P2[2]; PS[3] = PS2;
				} 
				else {
				// Kombination 1110
					if (bP2Inner[0] == 1) {
						StraithCutPoint( P2[2], P2[3], P1[3], P1[0], PS2 );
						PS[0] = P2[0]; PS[1] = P2[1]; PS[2] = P2[2]; PS[3] = PS2;
					} 
					else {
					// Kombination 0111
						StraithCutPoint( P2[0], P2[1], P1[3], P1[0], PS1 );
						PS[0] = PS1; PS[1] = P2[1]; PS[2] = P2[2]; PS[3] = P2[3];
					}
				}
			} 
			else if (bP2Inner[2] == 1 && bP2Inner[3] == 1)	//xx11
			{		// ... von unten
				if (bP2Inner[0] == 0 && bP2Inner[1] == 0) {	
				// Standard 0011
					StraithCutPoint( P2[1], P2[2], P1[0], P1[1], PS1 );
					StraithCutPoint( P2[3], P2[0], P1[0], P1[1], PS2 );
					PS[0] = PS2; PS[1] = PS1; PS[2] = P2[2]; PS[3] = P2[3];
				} 
				else {
					if (bP2Inner[0] == 1) {
				    // Kombination 1011
						StraithCutPoint( P2[1], P2[2], P1[0], P1[1], PS1 );
						PS[0] = P2[0]; PS[1] = PS1; PS[2] = P2[2]; PS[3] = P2[3];
					}
					else {
					// Kombination 0111 - doppelt
						StraithCutPoint( P2[3], P2[0], P1[0], P1[1], PS1 );
						PS[0] = PS1; PS[1] = P2[1]; PS[2] = P2[2]; PS[3] = P2[3];
					}
				}
			} 
			else if (bP2Inner[0] == 1 && bP2Inner[3] == 1)	//1xx1
			{		// ... von rechts
				if (bP2Inner[1] == 0 && bP2Inner[2] == 0) {	
                // Standard 1001
					StraithCutPoint( P2[0], P2[1], P1[1], P1[2], PS1 );
					StraithCutPoint( P2[2], P2[3], P1[1], P1[2], PS2 );
					PS[0] = P2[0]; PS[1] = PS1; PS[2] = PS2; PS[3] = P2[3];
				} 
				else {
					if (bP2Inner[1] == 1) {
				    // Kombination 1101
						StraithCutPoint( P2[2], P2[3], P1[1], P1[2], PS2 );
						PS[0] = P2[0]; PS[1] = P2[1]; PS[2] = PS2; PS[3] = P2[3];
					}
                    else {
				    // Kombination 1011 - doppelt
						StraithCutPoint( P2[0], P2[1], P1[1], P1[2], PS2 );
						PS[0] = P2[0]; PS[1] = PS2; PS[2] = P2[2]; PS[3] = P2[3];
                    }
				}
			} 
			else if (bP2Inner[0] == 1 && bP2Inner[1] == 1)	//11xx
			{		// ... von oben
				if (bP2Inner[2] == 0 && bP2Inner[3] == 0) {	
                // Standard 1100
				    StraithCutPoint( P2[3], P2[0], P1[2], P1[3], PS1 );
				    StraithCutPoint( P2[1], P2[2], P1[2], P1[3], PS2 );
				    PS[0] = P2[0]; PS[1] = P2[1]; PS[2] = PS2; PS[3] = PS1;
                }
                else {
                    if (bP2Inner[2] == 1) {
                    // Kombination 1110
						StraithCutPoint( P2[3], P2[0], P1[2], P1[3], PS1 );
						PS[0] = P2[0]; PS[1] = P2[1]; PS[2] = P2[2]; PS[3] = PS1;
                    }
                    else {
                    // Kombination 1101 - doppelt
						StraithCutPoint( P2[1], P2[2], P1[2], P1[3], PS2 );
						PS[0] = P2[0]; PS[1] = P2[1]; PS[2] = PS2; PS[3] = P2[3];
                    }
                }
			} 
			else {
			// Im Gegensatz zu P1/P2 könnte hier der Streifen so genommen werden 
			// Kombination 1010
				if (bP2Inner[0] == 1 && bP2Inner[1] == 0 && bP2Inner[2] == 1 && bP2Inner[3] == 0) {	
					if (StraithCutPoint(P2[0], P2[1], P1[1], P1[2], PS1) &&
					    StraithCutPoint(P2[2], P2[3], P1[3], P1[0], PS2)) 
                    {
					    PS[0] = P2[0]; PS[1] = PS1; PS[2] = P2[2]; PS[3] = PS2;
					    return TRUE;
				    }
                }

			// Kombination 0101
				if (bP2Inner[0] == 0 && bP2Inner[1] == 1 && bP2Inner[2] == 0 && bP2Inner[3] == 1) {	
					if (StraithCutPoint(P2[0], P2[1], P1[3], P1[0], PS1) &&
					    StraithCutPoint(P2[2], P2[3], P1[1], P1[2], PS2))
                    {
					    PS[0] = PS1; PS[1] = P2[1]; PS[2] = PS2; PS[3] = P2[3];
					    return TRUE;
                    }
				}

			// Kombination 1000
				if (bP2Inner[0] == 1 && bP2Inner[1] == 0 && bP2Inner[2] == 0 && bP2Inner[3] == 0) {	
					if (StraithCutPoint(P2[0], P2[1], P1[1], P1[2], PS1) &&
					    StraithCutPoint(P2[3], P2[0], P1[1], P1[2], PS2))
                    {
					    PS[0] = P2[0]; PS[1] = PS1; PS[2] = PS2; PS[2].x += 1; PS[3] = PS2; // ist das ok?
					    return TRUE;
				    }
                }

			// Kombination 0100
				if (bP2Inner[0] == 0 && bP2Inner[1] == 1 && bP2Inner[2] == 0 && bP2Inner[3] == 0) {	
					if (StraithCutPoint(P2[0], P2[1], P1[3], P1[0], PS1) &&
					    StraithCutPoint(P2[1], P2[2], P1[3], P1[0], PS2))
                    {
					    PS[0] = PS1; PS[1] = P2[1]; PS[2] = PS2; PS[3] = PS2; PS[3].x -= 1; // ist das ok?
					    return TRUE;
                    }
				}

			// Kombination 0010
				if (bP2Inner[0] == 0 && bP2Inner[1] == 0 && bP2Inner[2] == 1 && bP2Inner[3] == 0) {	
					if (StraithCutPoint(P2[0], P2[1], P1[3], P1[0], PS1) &&
					    StraithCutPoint(P2[2], P2[3], P1[0], P1[3], PS2))
                    {
					    PS[0] = PS1; PS[0].x -= 1; PS[1] = PS1; PS[2] = P2[2]; PS[3] = PS2;
					    return TRUE;
                    }
				}

			// Kombination 0001
				if (bP2Inner[0] == 0 && bP2Inner[1] == 0 && bP2Inner[2] == 0 && bP2Inner[3] == 1) {	
					if (StraithCutPoint( P2[3], P2[0], P1[1], P1[2], PS1) &&
					    StraithCutPoint( P2[2], P2[3], P1[1], P1[2], PS2))
                    {
					    PS[0] = PS1; PS[1] = PS1; PS[1].x += 1; PS[2] = PS2; PS[3] = P2[3];
					    return TRUE;
				    }
                }

            // wenn irgend welche Linien sich nicht schneiden lassen, nehmen
            // wir den Kartenausschnitt
				PS[0] = P1[0]; PS[1] = P1[1]; PS[2] = P1[2]; PS[3] = P1[3];
			}
		}
	}
	else {
	// bP1Change und bP2Change = 0
		if (bP1Inner[0] > 0) {	
		// 1111 - d.h. Streifen liegt innen
			PS[0] = P1[0]; PS[1] = P1[1]; PS[2] = P1[2]; PS[3] = P1[3];
		}
		else {
			if (bP2Inner[0] > 0) {	
			// 0000 - 1111 : P2 vollständig innen !!!
				PS[0] = P2[0]; PS[1] = P2[1]; PS[2] = P2[2]; PS[3] = P2[3];
			}
			else {
			// 0000 - 0000 : alle Pkte außen
				StraithCutPoint( P1[0], P1[1], P2[3], P2[0], PS1 );
				StraithCutPoint( P1[0], P1[1], P2[1], P2[2], PS2 );
				StraithCutPoint( P1[2], P1[3], P2[1], P2[2], P10 );
				StraithCutPoint( P1[2], P1[3], P2[3], P2[0], P20 );

				PS[0] = PS1; PS[1] = PS2; PS[2] = P10; PS[3] = P20;
			}
		}
	}
	return TRUE;
}


/////////////////////////////////////////////////////////////////////
// PS - Koordinaten auf Richtigkeit abschätzen
/////////////////////////////////////////////////////////////////////
static	BOOL PS_Intersect(POINTL P1[4], POINTL P2[4], POINTL &PS)
{
	if (PS.x < 0.0 || PS.y < 0.0)
		return FALSE;

long lXMin1 = min( P1[0].x, P2[0].x );
long lXMax1 = max( P1[1].x, P2[1].x );

long lXMin2 = min( P1[3].x, P2[3].x );
long lXMax2 = max( P1[2].x, P2[2].x );

long lYMin1 = min( P1[0].y, P2[0].y );
long lYMax1 = max( P1[3].y, P2[3].y );

long lYMin2 = min( P1[1].y, P2[1].y );
long lYMax2 = max( P1[2].y, P2[2].y );

long lXMin = min( lXMin1, lXMin2 );
long lXMax = max( lXMax1, lXMax2 );

long lYMin = min( lYMin1, lYMin2 );
long lYMax = max( lYMax1, lYMax2 );

long lXDiff = (lXMax - lXMin)/2;
long lYDiff = (lYMax - lYMin)/2;

	if (PS.x < lXMin - lXDiff || PS.x > lXMax + lXDiff || PS.y < lYMin - lYDiff || PS.y > lYMax + lYDiff)
		return FALSE;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// ermittelt die Parameter für die Geradengleichung Ax + By + C = 0
//////////////////////////////////////////////////////////////////////
static void	
LineParam(POINTL const &P11, POINTL const &P12, LINE &L1)
{
	L1.A = (double) ( P12.y - P11.y );
	L1.B = (double) ( P11.x - P12.x );
//	L1.C = (double) P12.x * (double) P11.y - (double) P11.x * (double) P12.y;
    L1.C = -((double) P11.y * L1.B + (double) P11.x * L1.A);
}

//////////////////////////////////////////////////////////////////////
// ermittelt Schnittpunkt zweier Geraden
//////////////////////////////////////////////////////////////////////
static BOOL	
LineCutPoint(LINE const &L1, LINE const &L2, POINTL &P)
{       
	double	p1 = L1.B * L2.C - L2.B * L1.C;
	double	q1 = L2.B * L1.A - L1.B * L2.A;

	double	p2 = L1.A * L2.C - L2.A * L1.C;
	double	q2 = L2.A * L1.B - L1.A * L2.B;
	
	if (q1 == 0.0 || q2 == 0.0)
		return FALSE;   // Linien sind parallel oder identisch

	P.x = (long) (p1 / q1);
	P.y = (long) (p2 / q2);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// ermittelt Schnittpunkt zweier Strecken (!)
//////////////////////////////////////////////////////////////////////
static BOOL	
StraithCutPoint(POINTL const &P11, POINTL const &P12, POINTL const &P21, 
    POINTL const &P22, POINTL &P, BOOL *bIsInner)
{
	LINE L1;
	LINE L2;
	
	LineParam(P11, P12, L1);
    LineParam(P21, P22, L2);

	if (LineCutPoint(L1, L2, P)) {
        if ((P11.x - P.x) * (P12.x - P.x) <= 0) {
        // Schnittpunkt existiert und liegt zwischen den beiden Endpunkten
		    if (NULL != bIsInner)
                *bIsInner = TRUE;
        }
        else {
        // Schnittpunkt existiert und liegt _nicht_ zwischen den beiden Endpunkten
		    if (NULL != bIsInner)
                bIsInner = FALSE;
        }
        return TRUE;
    }
    else {
        _ASSERTE(FALSE);
    }
	return FALSE;
}

//////////////////////////////////////////////////////////////////////
// RubberBand - rechnet eine Liste von Koordinaten aus einem 
// schiefwinkligen System in ein anderes um (Entzerrung)
//
//	short nCoords	- Anzahl der umzurechnenden Koordinaten
//	POINTL *pPD		- Liste der umgerechneten Koordinaten
//	POINTL *pPS		- Liste der umzurechnenden Koordinaten
//	POINTL lpCs1[4]	- Koordinatenliste, die das Quellsystem beschreibt
//	POINTL lpCs2[4]	- Koordinatenliste, die das Zielsystem beschreibt
//////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//	alle möglichen Koordinatenwerte
//	für jeden logisch zusammenhängenden Block beginnen wir auf
//	einer 10-er Position; es ist im Debugger besser lesbar
/////////////////////////////////////////////////////////////////////////////
/*
#if	defined( USE_double )
	#define	fabs( _arg_ )	ffabs( (_arg_) )
#elif	defined( USE_LONGdouble )
	#define	fabs( _arg_ )	ffabsl( (_arg_) )
#endif
*/
// Die folgenden Elemente enthalten die Koordinaten der Karte

#define	M_XP	V[  0 ]
#define	M_YP	V[  1 ]

#define	B_XP	V[  2 ]
#define	B_YP	V[  3 ]

#define	M_XLU	V[  4 ]
#define	M_YLU	V[  5 ]

#define	M_X0	V[  10 ]		// Die Koordinaten selbst
#define	M_Y0	V[  11 ]
#define	M_X1	V[  12 ]
#define	M_Y1	V[  13 ]

#define	M_X2	V[  14 ]
#define	M_Y2	V[  15 ]
#define	M_X3	V[  16 ]
#define	M_Y3	V[  17 ]

#define	M_X4	V[  10 ]		// nur für bessere Lesbarkeit
#define	M_Y4	V[  11 ]		// damit P3 einen Nachfolger hat

#define	M_XQ	V[  20 ]		// Schnittpunktkoordinaten
#define	M_YQ	V[  21 ]
#define	M_XR	V[  22 ]
#define	M_YR	V[  23 ]

#define	M_XS	V[  24 ]
#define	M_YS	V[  25 ]
#define	M_XT	V[  26 ]
#define	M_YT	V[  27 ]

#define	M_XRQ	V[  28 ]		// Koordinaten der Bezugspunkte
#define	M_YRQ	V[  29 ]
#define	M_XRR	V[  30 ]
#define	M_YRR	V[  31 ]

#define	M_XRS	V[  32 ]
#define	M_YRS	V[  33 ]
#define	M_XRT	V[  34 ]
#define	M_YRT	V[  35 ]
 
// Koordinaten der Bitmap
#define	B_X0	V[  40 ]		// Die Koordinaten selbst
#define	B_Y0	V[  41 ]
#define	B_X1	V[  42 ]
#define	B_Y1	V[  43 ]

#define	B_X2	V[  44 ]
#define	B_Y2	V[  45 ]
#define	B_X3	V[  46 ]
#define	B_Y3	V[  47 ]

#define	B_X4	V[  40 ]		// nur für bessere Lesbarkeit
#define	B_Y4	V[  41 ]		// damit P3 einen Nachfolger hat

#define	B_XQ	V[  48 ]		// Schnittpunktkoordinaten
#define	B_YQ	V[  49 ]
#define	B_XR	V[  50 ]
#define	B_YR	V[  51 ]

#define	B_XS	V[  52 ]
#define	B_YS	V[  53 ]
#define	B_XT	V[  54 ]
#define	B_YT	V[  55 ]

#define	B_XRQ	V[  56 ]		// Koordinaten der Bezugspunkte
#define	B_YRQ	V[  57 ]
#define	B_XRR	V[  58 ]
#define	B_YRR	V[  59 ]

#define	B_XRS	V[  60 ]
#define	B_YRS	V[  61 ]
#define	B_XRT	V[  62 ]
#define	B_YRT	V[  63 ]

/////////////////////////////////////////////////////////////////////////////
//	Parameter der Geradengleichungen sowie
//	ihre Lösungen in den Schnittpunkten
/////////////////////////////////////////////////////////////////////////////

// zunächst wieder die Karte
#define	M_A0	V[ 70 ]
#define	M_B0	V[ 71 ]
#define	M_C0	V[ 72 ]
#define	M_G0	V[ 73 ]

#define	M_A1	V[ 74 ]
#define	M_B1	V[ 75 ]
#define	M_C1	V[ 76 ]
#define	M_G1	V[ 77 ]

#define	M_A2	V[ 78 ]
#define	M_B2	V[ 79 ]
#define	M_C2	V[ 80 ]
#define	M_G2	V[ 81 ]

#define	M_A3	V[ 82 ]
#define	M_B3	V[ 83 ]
#define	M_C3	V[ 84 ]
#define	M_G3	V[ 85 ]

#define	M_AQ	V[ 86 ]
#define	M_BQ	V[ 87 ]
#define	M_CQ	V[ 88 ]
#define	M_GQ	V[ 89 ]

#define	M_AR	V[ 90 ]
#define	M_BR	V[ 91 ]
#define	M_CR	V[ 92 ]
#define	M_GR	V[ 93 ]

// und jetzt die Bitmap

#define	B_A0	V[ 100 ]
#define	B_B0	V[ 101 ]
#define	B_C0	V[ 102 ]
#define	B_G0	V[ 103 ]

#define	B_A1	V[ 104 ]
#define	B_B1	V[ 105 ]
#define	B_C1	V[ 106 ]
#define	B_G1	V[ 107 ]

#define	B_A2	V[ 108 ]
#define	B_B2	V[ 109 ]
#define	B_C2	V[ 110 ]
#define	B_G2	V[ 111 ]

#define	B_A3	V[ 112 ]
#define	B_B3	V[ 113 ]
#define	B_C3	V[ 114 ]
#define	B_G3	V[ 115 ]

#define	B_AQ	V[ 116 ]
#define	B_BQ	V[ 117 ]
#define	B_CQ	V[ 118 ]
#define	B_GQ	V[ 119 ]

#define	B_AR	V[ 120 ]
#define	B_BR	V[ 121 ]
#define	B_CR	V[ 122 ]
#define	B_GR	V[ 123 ]

/////////////////////////////////////////////////////////////////////////////
//	Kantenlängen
/////////////////////////////////////////////////////////////////////////////

#define	M_R0	V[ 130 ]
#define	M_R1	V[ 131 ]
#define	M_R2	V[ 132 ]
#define	M_R3	V[ 133 ]

#define	M_RQ	V[ 134 ]
#define	M_RR	V[ 135 ]
#define	M_RS	V[ 136 ]
#define	M_RT	V[ 137 ]

#define	B_R0	V[ 138 ]
#define	B_R1	V[ 139 ]
#define	B_R2	V[ 140 ]
#define	B_R3	V[ 141 ]

#define	B_RQ	V[ 142 ]
#define	B_RR	V[ 143 ]
#define	B_RS	V[ 144 ]
#define	B_RT	V[ 145 ]

double	DISTANCE( double _X0_, double _Y0_, double _X1_, double _Y1_ )
{
	double	d1, d2;
	d1 = _X1_ - _X0_; d2 = _Y1_ - _Y0_;
	d1 *= d1;
	d2 *= d2;
	d1 = sqrt( d1 + d2 );
	return d1;
}

#ifdef _NEWCODE
static	BOOL	RubberBand( short nCoords, DPOINT* pPD, const DPOINT* pPS, const DPOINT lpCs1[4], const DPOINT lpCs2[4] )
#else
static	BOOL	RubberBand( short nCoords, POINTL *pPD, POINTL *pPS, POINTL lpCs1[4], POINTL lpCs2[4] )
#endif
{
	double *V = (double*) new char[ 150 * sizeof(double) ];		// Wertespeicher (Definitionen siehe oben)
	double	*pD;
	
	CMatrix	M( 8, 8 );
	CVector	VC( 8 );
	CVector	VR( 8 );

	int	i, ret;
	double	d1, d2;

	BOOL	bIsGood;
	double	eps = 1.0;

	memset( (void*) V, 0x00, 150 * sizeof( double ) );

	/////////////////////////////////////////////////////////////////////
	// Übernahme der Koordinatendaten
	/////////////////////////////////////////////////////////////////////
	
	for (i = 0, pD = &M_X0; i < 4; i++ )
	{
		*pD++ = (double) lpCs1[i].x;
		*pD++ = (double) lpCs1[i].y;
	}
	for (i = 0, pD = &B_X0; i < 4; i++ )
	{
		*pD++ = (double) lpCs2[i].x;
		*pD++ = (double) lpCs2[i].y;
	}
	
	/////////////////////////////////////////////////////////////////////
	// um Bereichsüberschreitungen zu vermeiden, werden die Koordinaten
	// in der Karte auf den Punkt links unten bezogen
	/////////////////////////////////////////////////////////////////////

	M_XLU = M_X0; M_YLU = M_Y0; 

	M_X0 -= M_XLU; M_Y0 -= M_YLU;
	M_X1 -= M_XLU; M_Y1 -= M_YLU;
	M_X2 -= M_XLU; M_Y2 -= M_YLU;
	M_X3 -= M_XLU; M_Y3 -= M_YLU;

	/////////////////////////////////////////////////////////////////////
	// Berechnung der Kantenlängen
	/////////////////////////////////////////////////////////////////////

	M_R0 = DISTANCE( M_X0, M_Y0, M_X1, M_Y1 );
	M_R1 = DISTANCE( M_X1, M_Y1, M_X2, M_Y2 );
	M_R2 = DISTANCE( M_X2, M_Y2, M_X3, M_Y3 );
	M_R3 = DISTANCE( M_X3, M_Y3, M_X4, M_Y4 );

	B_R0 = DISTANCE( B_X0, B_Y0, B_X1, B_Y1 );
	B_R1 = DISTANCE( B_X1, B_Y1, B_X2, B_Y2 );
	B_R2 = DISTANCE( B_X2, B_Y2, B_X3, B_Y3 );
	B_R3 = DISTANCE( B_X3, B_Y3, B_X4, B_Y4 );

	/////////////////////////////////////////////////////////////////////
	// Parameter der Geradengleichnungen der Kanten 
	/////////////////////////////////////////////////////////////////////

	M_A0 = M_Y1 - M_Y0; M_B0 = M_X0 - M_X1; M_C0 = M_X1 * M_Y0 - M_X0 * M_Y1;
	M_A1 = M_Y2 - M_Y1; M_B1 = M_X1 - M_X2; M_C1 = M_X2 * M_Y1 - M_X1 * M_Y2;
	M_A2 = M_Y3 - M_Y2; M_B2 = M_X2 - M_X3; M_C2 = M_X3 * M_Y2 - M_X2 * M_Y3;
	M_A3 = M_Y4 - M_Y3; M_B3 = M_X3 - M_X4; M_C3 = M_X4 * M_Y3 - M_X3 * M_Y4;

	B_A0 = B_Y1 - B_Y0; B_B0 = B_X0 - B_X1; B_C0 = B_X1 * B_Y0 - B_X0 * B_Y1;
	B_A1 = B_Y2 - B_Y1; B_B1 = B_X1 - B_X2; B_C1 = B_X2 * B_Y1 - B_X1 * B_Y2;
	B_A2 = B_Y3 - B_Y2; B_B2 = B_X2 - B_X3; B_C2 = B_X3 * B_Y2 - B_X2 * B_Y3;
	B_A3 = B_Y4 - B_Y3; B_B3 = B_X3 - B_X4; B_C3 = B_X4 * B_Y3 - B_X3 * B_Y4;

	for (short coord = 0; coord < nCoords; coord++ )
	{
		/////////////////////////////////////////////////////////////////////
		// Punkt transformieren
		/////////////////////////////////////////////////////////////////////

		M_XP = pPS[ coord ].x - M_XLU;
		M_YP = pPS[ coord ].y - M_YLU;

		/////////////////////////////////////////////////////////////////////
		// erste Schätzung für die Schnittpunkte
		/////////////////////////////////////////////////////////////////////
	
		M_XQ =                M_XP; M_YQ = ( M_Y0 + M_Y1 ) / 2;
		M_XR = ( M_X1 + M_X2 ) / 2; M_YR =                M_YP;
		M_XS =                M_XP; M_YS = ( M_Y2 + M_Y3 ) / 2;
		M_XT = ( M_X3 + M_X4 ) / 2; M_YT =                M_YP;
	
		/////////////////////////////////////////////////////////////////////
		// wo ergeben sich die größten fabstandsverhältnisse?
		/////////////////////////////////////////////////////////////////////

		if (fabs( M_XQ - M_X0 ) > fabs( M_XQ - M_X1 ) )
		{ 
			M_XRQ = M_X0; M_YRQ = M_Y0; M_XRS = M_X3; M_YRS = M_Y3;
			B_XRQ = B_X0; B_YRQ = B_Y0; B_XRS = B_X3; B_YRS = B_Y3;
		}
		else
		{
        	M_XRQ = M_X1; M_YRQ = M_Y1; M_XRS = M_X2; M_YRS = M_Y2;
			B_XRQ = B_X1; B_YRQ = B_Y1; B_XRS = B_X2; B_YRS = B_Y2;
		}

		if (fabs( M_YR - M_Y1 ) > fabs( M_YR - M_Y2 ) )
		{
			M_XRR = M_X1; M_YRR = M_Y1; M_XRT = M_X4; M_YRT = M_Y4;
			B_XRR = B_X1; B_YRR = B_Y1; B_XRT = B_X4; B_YRT = B_Y4;
		}
		else
		{
			M_XRR = M_X2; M_YRR = M_Y2; M_XRT = M_X3; M_YRT = M_Y3;
			B_XRR = B_X2; B_YRR = B_Y2; B_XRT = B_X3; B_YRT = B_Y3;
		}
		
		/////////////////////////////////////////////////////////////////////
		// erster Schritt ... berechnen der Punkte auf den Kanten
		/////////////////////////////////////////////////////////////////////

		M.Clear();

		/////////////////////////////////////////////////////////////////////
		// die folgenden Matrixelemente sind für jede Iteration konstant
		/////////////////////////////////////////////////////////////////////

		M( 1, 0) = M_A0; M( 1, 1) = M_B0;
		M( 2, 2) = M_A1; M( 2, 3) = M_B1;
		M( 5, 4) = M_A2; M( 5, 5) = M_B2;
		M( 6, 6) = M_A3; M( 6, 7) = M_B3;

        for (i = 0, bIsGood = FALSE; ( i < 5 ) && ( FALSE == bIsGood ); i++ )
        {
			/////////////////////////////////////////////////////////////////////
	 		// Kantenlängen von den Ziel- zu den Bezugspunkten
			/////////////////////////////////////////////////////////////////////
	
			M_RQ = DISTANCE( M_XQ, M_YQ, M_XRQ, M_YRQ );
			M_RR = DISTANCE( M_XR, M_YR, M_XRR, M_YRR );
			M_RS = DISTANCE( M_XS, M_YS, M_XRS, M_YRS );
			M_RT = DISTANCE( M_XT, M_YT, M_XRT, M_YRT );

			/////////////////////////////////////////////////////////////////////
			// Parameter der Geradengleichungen der Zielpunkte
			/////////////////////////////////////////////////////////////////////

			M_AQ = M_YS - M_YQ; M_BQ = M_XQ - M_XS; M_CQ = M_XS * M_YQ - M_XQ * M_YS;
			M_AR = M_YT - M_YR; M_BR = M_XR - M_XT; M_CR = M_XT * M_YR - M_XR * M_YT;

			/////////////////////////////////////////////////////////////////////
			// aufbauen des Zielvektors (rechte Seite des GLS)
			/////////////////////////////////////////////////////////////////////

			VC(0)  = -( M_R2 * M_RQ - M_R0 * M_RS );
			VC(1)  = -( M_A0 * M_XQ + M_B0 * M_YQ + M_C0 );
			VC(2)  = -( M_A1 * M_XR + M_B1 * M_YR + M_C1 );
			VC(3)  = -( M_AR * M_XP + M_BR * M_YP + M_CR );

			VC(4)  = -( M_AQ * M_XP + M_BQ * M_YP + M_CQ );
			VC(5)  = -( M_A2 * M_XS + M_B2 * M_YS + M_C2 );
			VC(6)  = -( M_A3 * M_XT + M_B3 * M_YT + M_C3 );
			VC(7)  = -( M_R3 * M_RR - M_R1 * M_RT );

			/////////////////////////////////////////////////////////////////////
			// aufbauen der Jacobi-Matrix (linke Seite des GLS)
			/////////////////////////////////////////////////////////////////////

			M( 0, 0) =  ( ( M_XQ - M_XRQ ) * M_R2 ) / M_RQ;
			M( 0, 1) =  ( ( M_YQ - M_YRQ ) * M_R2 ) / M_RQ;
			M( 0, 4) = -( ( M_XS - M_XRS ) * M_R0 ) / M_RS;
			M( 0, 5) = -( ( M_YS - M_YRS ) * M_R0 ) / M_RS;

			M( 3, 2) = M_YP - M_YT;
			M( 3, 3) = M_XT - M_XP;
			M( 3, 6) = M_YR - M_YP;
			M( 3, 7) = M_XP - M_XR;

			M( 4, 0) = M_YP - M_YS;
			M( 4, 1) = M_XS - M_XP;
			M( 4, 4) = M_YQ - M_YP;
			M( 4, 5) = M_XP - M_XQ;
	
			M( 7, 2) =  ( ( M_XR - M_XRR ) * M_R3 ) / M_RR;
			M( 7, 3) =  ( ( M_YR - M_YRR ) * M_R3 ) / M_RR;
			M( 7, 6) = -( ( M_XT - M_XRT ) * M_R1 ) / M_RT;
			M( 7, 7) = -( ( M_YT - M_YRT ) * M_R1 ) / M_RT;
	
			/////////////////////////////////////////////////////////////////////
			// lösen des GLS
			/////////////////////////////////////////////////////////////////////

			ret = GaussBanach( VR, M, VC );
		
			/////////////////////////////////////////////////////////////////////
			// Differenzwerte addieren
			/////////////////////////////////////////////////////////////////////

			bIsGood = TRUE;

			d1 = VR(0); d2 = VR(1); 
			M_XQ += d1; M_YQ += d2;
			if (( fabs( d1 ) > eps ) || ( fabs( d2 ) > eps ) ) 
				bIsGood = FALSE;

			d1 = VR(2); d2 = VR(3); 
			M_XR += d1; M_YR += d2;
			if (( fabs( d1 ) > eps ) || ( fabs( d2 ) > eps ) ) 
				bIsGood = FALSE; 
	
			d1 = VR(4); d2 = VR(5); 
			M_XS += d1; M_YS += d2;
			if (( fabs( d1 ) > eps ) || ( fabs( d2 ) > eps ) ) 
				bIsGood = FALSE; 

			d1 = VR(6); d2 = VR(7); 
			M_XT += d1; M_YT += d2;
			if (( fabs( d1 ) > eps ) || ( fabs( d2 ) > eps ) ) 
				bIsGood = FALSE; 
		}

		/////////////////////////////////////////////////////////////////////
		// zweiter Schritt ... suchen der zugehörigen Punkte auf den
		// Kanten des Zielvierecks
		/////////////////////////////////////////////////////////////////////

		M.Clear();

		/////////////////////////////////////////////////////////////////////
		// die Abstände brauchen wir wieder
		/////////////////////////////////////////////////////////////////////

		M_RQ = DISTANCE( M_XQ, M_YQ, M_XRQ, M_YRQ );
		M_RR = DISTANCE( M_XR, M_YR, M_XRR, M_YRR );
		M_RS = DISTANCE( M_XS, M_YS, M_XRS, M_YRS );
		M_RT = DISTANCE( M_XT, M_YT, M_XRT, M_YRT );

		/////////////////////////////////////////////////////////////////////
		// erste Schätzung für die Schnittpunkte
		/////////////////////////////////////////////////////////////////////
	
		B_XQ = ( B_X0 + B_X1 ) / 2; B_YQ = ( B_Y0 + B_Y1 ) / 2;
		B_XR = ( B_X1 + B_X2 ) / 2; B_YR = ( B_Y1 + B_Y2 ) / 2;
		B_XS = ( B_X2 + B_X3 ) / 2; B_YS = ( B_Y2 + B_Y3 ) / 2;
		B_XT = ( B_X3 + B_X4 ) / 2; B_YT = ( B_Y3 + B_Y4 ) / 2;

		/////////////////////////////////////////////////////////////////////
		// die folgenden Matrixelemente sind für jede Iteration konstant
		/////////////////////////////////////////////////////////////////////

		M( 1, 0) = B_A0; M( 1, 1) = B_B0;
		M( 2, 2) = B_A1; M( 2, 3) = B_B1;
		M( 5, 4) = B_A2; M( 5, 5) = B_B2;
		M( 6, 6) = B_A3; M( 6, 7) = B_B3;

        for (i = 0, bIsGood = FALSE; ( i < 5 ) && ( FALSE == bIsGood ); i++ )
		{
			/////////////////////////////////////////////////////////////////////
	 		// Kantenlängen von den Ziel- zu den Bezugspunkten
			/////////////////////////////////////////////////////////////////////

			B_RQ = DISTANCE( B_XQ, B_YQ, B_XRQ, B_YRQ );
			B_RR = DISTANCE( B_XR, B_YR, B_XRR, B_YRR );
			B_RS = DISTANCE( B_XS, B_YS, B_XRS, B_YRS );
			B_RT = DISTANCE( B_XT, B_YT, B_XRT, B_YRT );

			/////////////////////////////////////////////////////////////////////
			// aufbauen des Zielvektors (rechte Seite des GLS)
			/////////////////////////////////////////////////////////////////////

			VC(0) = -( B_R0 * M_RQ - M_R0 * B_RQ );		// hor. unten
			VC(1) = -( B_A0 * B_XQ + B_B0 * B_YQ + B_C0 );	// Punkt unten
			VC(2) = -( B_A1 * B_XR + B_B1 * B_YR + B_C1 );	// Punkt rechts
			VC(3) = -( B_R1 * M_RR - M_R1 * B_RR );		// vert. rechts
		
			VC(4) = -( B_R2 * M_RS - M_R2 * B_RS );		// hor. oben
			VC(5) = -( B_A2 * B_XS + B_B2 * B_YS + B_C2 );	// Punkt oben
			VC(6) = -( B_A3 * B_XT + B_B3 * B_YT + B_C3 );	// Punkt links
			VC(7) = -( B_R3 * M_RT - M_R3 * B_RT );		// vert. links
		
			/////////////////////////////////////////////////////////////////////
			// aufbauen der Jacobi-Matrix (linke Seite des GLS)
			/////////////////////////////////////////////////////////////////////

			M( 0, 0) = -( ( B_XQ - B_XRQ ) * M_R0 ) / B_RQ;
			M( 0, 1) = -( ( B_YQ - B_YRQ ) * M_R0 ) / B_RQ;
			M( 3, 2) = -( ( B_XR - B_XRR ) * M_R1 ) / B_RR;
			M( 3, 3) = -( ( B_YR - B_YRR ) * M_R1 ) / B_RR;
		
			M( 4, 4) = -( ( B_XS - B_XRS ) * M_R2 ) / B_RS;
			M( 4, 5) = -( ( B_YS - B_YRS ) * M_R2 ) / B_RS;
			M( 7, 6) = -( ( B_XT - B_XRT ) * M_R3 ) / B_RT;
			M( 7, 7) = -( ( B_YT - B_YRT ) * M_R3 ) / B_RT;
		
			/////////////////////////////////////////////////////////////////////
			// lösen des GLS
			/////////////////////////////////////////////////////////////////////

//			ret = M.GaussBanach( VC, VR );
			ret = GaussBanach( VR, M, VC );

			/////////////////////////////////////////////////////////////////////
			// Differenzwerte addieren
			/////////////////////////////////////////////////////////////////////

			bIsGood = TRUE;

			d1 = VR(0); d2 = VR(1); 
			B_XQ += d1; B_YQ += d2;
			if (( fabs( d1 ) > eps ) || ( fabs( d2 ) > eps ) ) 
				bIsGood = FALSE; 

			d1 = VR(2); d2 = VR(3); 
			B_XR += d1; B_YR += d2;
			if (( fabs( d1 ) > eps ) || ( fabs( d2 ) > eps ) ) 
				bIsGood = FALSE; 

			d1 = VR(4); d2 = VR(5); 
			B_XS += d1; B_YS += d2;
			if (( fabs( d1 ) > eps ) || ( fabs( d2 ) > eps ) ) 
				bIsGood = FALSE; 
	
			d1 = VR(6); d2 = VR(7); 
			B_XT += d1; B_YT += d2;
			if (( fabs( d1 ) > eps ) || ( fabs( d2 ) > eps ) ) 
				bIsGood = FALSE; 
		}

		/////////////////////////////////////////////////////////////////////
		// transformierten Punkt berechnen
		/////////////////////////////////////////////////////////////////////

		LINE	B_Q, B_R;

		B_Q.A = B_YQ - B_YS; 
		B_Q.B = B_XS - B_XQ; 
		B_Q.C = B_XQ * B_YS - B_XS * B_YQ;
		
		B_R.A = B_YR - B_YT; 
		B_R.B = B_XT - B_XR; 
		B_R.C = B_XR * B_YT - B_XT * B_YR;
		
#ifdef _NEWCODE
		LineCutPoint( pPD[ coord ], B_Q, B_R );
#else
		LineCutPoint( B_Q, B_R, pPD[ coord ] );
#endif
	}
	
	delete[] V;
	return TRUE;
}

