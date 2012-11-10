// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 17.03.2002 13:57:54 
//
// @doc
// @module PolyGISPicture.cpp | Definition of the <c CPolyGISPicture> class

#include "stdafx.h"

#include <Com/Thunk.h>
#include <ospace/file/path.h>
#include <ltwrappr.h>
#include <pgr.h>

#include "LPictImpl.h"
#include "lpict/PolyGISPicture.h"
#include "PgrHolder.h"
#include "PictureCache.h"
#include "LeadToolsInit.h"

#import "TRiASCS.tlb" raw_interfaces_only raw_dispinterfaces no_implementation \
	no_namespace named_guids

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CPolyGISPicture, CPicture, 1);

#define	new	DEBUG_NEW

///////////////////////////////////////////////////////////////////////////////
// LEADTOOLS 
CLeadToolsInit g_LeadTools;

///////////////////////////////////////////////////////////////////////////////
// Der PictureCache in seiner vollen Schönheit (:-)
typedef map<CString, CCacheItem<CPgrTileHolder>, less<CString> > CCacheMap;
typedef CCachedItems<CString, CPgrTileHolder, CCacheMap> CPictureCache;

///////////////////////////////////////////////////////////////////////////////
// hält die letzten N geladenen Pgrholders
const int CACHED_PICTURE_COUNT = 4;

CPictureCache g_pictCache(CACHED_PICTURE_COUNT);

void CPolyGISPicture::ReleaseCache()
{
	g_pictCache.ReleaseItems();
}

///////////////////////////////////////////////////////////////////////////////
// Initialisierung etc.
CPolyGISPicture::CPolyGISPicture() :
	CPicture() 
{
	Init();
}

void CPolyGISPicture::Init() 
{
	CPicture::Init();
	m_compression = PICT_COMPR_NOCOMPR;		// Komprimierung wird nicht hier behandelt
	m_bitsPerSample = 24;
	m_samplesPerPixel = 3;
	m_colorspace = PICT_COLOR_RGB;
	m_nPlanarConfiguration = PICT_PLANARCFG_CHUNKED;
	m_orientation = PICT_ORIENT_LOWERLEFT;

	TAGMAP[PICT_PROP_SAMPLESPERPIXEL] = TAG(PICT_PROP_SAMPLESPERPIXEL, (WORD)m_samplesPerPixel);
	TAGMAP[PICT_PROP_BITSPERSAMPLE] = TAG(PICT_PROP_BITSPERSAMPLE, (WORD)m_bitsPerSample);
	TAGMAP[PICT_PROP_COLORSPACE] = TAG(PICT_PROP_COLORSPACE, (WORD)m_colorspace);
	TAGMAP[PICT_PROP_COMPRESSION] = TAG(PICT_PROP_COMPRESSION, (WORD)m_compression);
	TAGMAP[PICT_PROP_PLANARCONFIGURATION] = TAG(PICT_PROP_PLANARCONFIGURATION, (WORD)PICT_PLANARCFG_CHUNKED);
	TAGMAP[PICT_PROP_ORIENTATION] = TAG(PICT_PROP_ORIENTATION, (WORD)m_orientation);

#if defined(_DEBUG)
	m_lDrawnTiles = 0;
#endif // defined(_DEBUG)
}

///////////////////////////////////////////////////////////////////////////////
// 
BOOL CPolyGISPicture::Clone(CPicture *pPicture, CPictException *pE)
{
	return FALSE;
}

long CPolyGISPicture::AlignTop(long line)
{
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// FillBuffer wird für den eigenen Codec support benötigt, entfällt hier
long CPolyGISPicture::FillBuffer(long nBytes, long startRestBytes, long nRestBytes)
{
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// StoreScanLine wird für den eigenen Codec support benötigt, entfällt hier
long CPolyGISPicture::StoreScanLine(HPBYTE pLine, long line, const CRect& rcCore)
{
	_ASSERTE(FALSE);		// dürfte nie gerufen werden
	return 0;
}

BOOL CPolyGISPicture::ReadRaw(const CRect& rcRect)
{
	return TRUE;
}

BOOL CPolyGISPicture::Decode(const CRect& rcRect)
{
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// FillPictException
BOOL CPolyGISPicture::FillPictException(int iCause, LPCTSTR pcPath, CPictException *e)
{
	if (NULL != e) {
		e->m_cause = iCause;
		e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
		e->m_strPictName = pcPath;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// 
BOOL CPolyGISPicture::ReadHeader(CPictException *e, int nPicture)
{
	if (0 != nPicture)
		return FALSE;	// no subpicture support

	ASSERT(NULL != m_pFile);
	ASSERT_VALID(m_pFile);

// fertig initialisieren
	Init();
	if (!g_LeadTools.EnsureLoaded(e))
		return FALSE;

os_path pgrpath = (LPCTSTR)m_pFile->GetFilePath();

	pgrpath.extension("pgr");

// Im Cache den passenden PgrHolder sicherstellen
CString pgr(pgrpath);

	pgr.MakeLower();

CPgrTileHolder *pPgrTiles = g_pictCache.EnsureItem(pgr);

	if (NULL == pPgrTiles)	// should not happen
		return FillPictException(CPictException::errMissingInfo, (LPCTSTR)pgrpath, e);

	if (!*pPgrTiles) {
	// wurde noch nicht geladen

	// zugehörige *.pgr-Datei öffnen
	CFile pgrFile;

		if (!pgrFile.Open((LPCTSTR)pgrpath, 
			CFile::modeRead|CFile::shareDenyWrite|CFile::typeBinary))
		{
			return FillPictException(CPictException::errMissingInfo, (LPCTSTR)pgrpath, e);
		}

	// PGR Header einlesen
	DWORD dwMagic = 0;

		if (sizeof(DWORD) != pgrFile.Read(&dwMagic, sizeof(DWORD))) 
			return FillPictException(CPictException::errMissingInfo, (LPCTSTR)pgrpath, e);

		if (MAGIC_OLD_PGR == dwMagic) {
		long lCurrent = pgrFile.Seek(0, CFile::current);
		unsigned short cMagic[2];

			if (2*sizeof(unsigned short) != pgrFile.Read(cMagic, 2*sizeof(unsigned short))) 
				return FillPictException(CPictException::errMissingInfo, (LPCTSTR)pgrpath, e);
			pgrFile.Seek(lCurrent, CFile::begin);

			if (MAGIC_PGR2 == cMagic[1]) {
			PGRHEADER2 hdr;

				if (sizeof(PGRHEADER2) != pgrFile.Read(&hdr, sizeof(PGRHEADER2))) 
					return FillPictException(CPictException::errFormat, (LPCTSTR)pgrpath, e);
				if (/*MAGIC_PGR2_BYTE1 != hdr.iMagic1 ||*/ MAGIC_PGR2_BYTE2 != hdr.iMagic2) 
					return FillPictException(CPictException::errFormat, (LPCTSTR)pgrpath, e);

				if (!FillPictureList2(pgrFile, hdr, pPgrTiles, e))
					return FALSE;
			}
			else {
			PGRHEADEROLD hdr;

				if (sizeof(PGRHEADEROLD) != pgrFile.Read(&hdr, sizeof(PGRHEADEROLD))) 
					return FillPictException(CPictException::errFormat, (LPCTSTR)pgrpath, e);
				if (MAGIC_PGR2_BYTE2 != LOBYTE(hdr.iMagic1)) 
					return FillPictException(CPictException::errFormat, (LPCTSTR)pgrpath, e);

				if (!FillPictureListOld(pgrFile, hdr, pPgrTiles, e))
					return FALSE;
			}
		}
		else if (MAGIC_PGR == dwMagic) {
		PGRHEADER hdr;

			if (sizeof(PGRHEADER) != pgrFile.Read(&hdr, sizeof(PGRHEADER))) 
				return FillPictException(CPictException::errFormat, (LPCTSTR)pgrpath, e);

			if (!FillPictureList(pgrFile, hdr, pPgrTiles, e))
				return FALSE;
		}
		else 
			return FillPictException(CPictException::errFormat, (LPCTSTR)pgrpath, e);
	}

// Tags füllen
	SetPictRect(CRect (0, 0, pPgrTiles->GetSizeX(), pPgrTiles->GetSizeY()));
	SetResolutionUnit(PICT_UNIT_PELS);
	SetXResolution(pPgrTiles->GetXResolution());
	SetYResolution(pPgrTiles->GetYResolution());

// Kachelgröße speichern
	SetTileSize(pPgrTiles->GetTileSizeX(), pPgrTiles->GetTileSizeY());
	
// Layout: CMP kennt keine Strips und Tiles
	m_rcStrip = m_rcPicture;
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Einlesen der Lister der Kacheln einer Bilddatei
BOOL CPolyGISPicture::FillPictureList(CFile &rFile, PGRHEADER &rHdr, 
	CPgrTileHolder *pPgrTiles, CPictException *e)
{
	pPgrTiles->Clear();
	return pPgrTiles->LoadTiles(rFile, rHdr, e);
}

BOOL CPolyGISPicture::FillPictureListOld(CFile &rFile, PGRHEADEROLD &rHdr, 
	CPgrTileHolder *pPgrTiles, CPictException *e)
{
	pPgrTiles->Clear();
	return pPgrTiles->LoadTiles(rFile, rHdr, e);
}

BOOL CPolyGISPicture::FillPictureList2(CFile &rFile, PGRHEADER2 &rHdr, 
	CPgrTileHolder *pPgrTiles, CPictException *e)
{
	pPgrTiles->Clear();
	return pPgrTiles->LoadTiles(rFile, *m_pFile, rHdr, e);
}

///////////////////////////////////////////////////////////////////////////////
// 
BOOL CPolyGISPicture::SelectSubFile(int nFile)
{
	return 0 == nFile ? TRUE : FALSE;		// Ein PolyGIS Bild hat nur ein (Teil)bild
}

void CPolyGISPicture::SetPictRect(const CRect& rcPict)
{
	m_rcImage = m_rcPicture = rcPict;
	m_rcImage.right = Align(m_rcPicture.Width(), m_bitsPerSample, sizeof(DWORD));
	TAGMAP[PICT_PROP_IMAGEWIDTH] = TAG(PICT_PROP_IMAGEWIDTH, (ULONG)rcPict.Width());
	TAGMAP[PICT_PROP_IMAGELENGTH] = TAG(PICT_PROP_IMAGELENGTH, (ULONG)rcPict.Height());
}

void CPolyGISPicture::SetTileSize(long lSizeX, long lSizeY)
{
	TAGMAP[PICT_PROP_TILEWIDTH] = TAG(PICT_PROP_TILEWIDTH, (ULONG)lSizeX);
	TAGMAP[PICT_PROP_TILELENGTH] = TAG(PICT_PROP_TILELENGTH, (ULONG)lSizeY);
}

BOOL CPolyGISPicture::WriteHeader()
{
	return TRUE;
}

BOOL CPolyGISPicture::WriteTrailer()
{
	return TRUE;
}

BOOL CPolyGISPicture::Write(const CRect& rcRect, PICT_ORIENT srcOrient)
{
	return TRUE;
}

const CRect CPolyGISPicture::GetBestCorePictRect()
{
	return CRect();
}

long CPolyGISPicture::GetNeededFileSize()
{
	return 0;
}

BOOL CPolyGISPicture::SetCompression(PICT_COMPR compr, CPictException *pE)
{
	return TRUE;
}

BOOL CPolyGISPicture::SetColorspace(PICT_COLOR color, CPictException *pE)
{
	return TRUE;
}

BOOL CPolyGISPicture::SetResolutionUnit(PICT_RESUNIT resUnit, CPictException *pE)
{
BOOL bRet = TRUE;

	if (PICT_UNIT_PELS != resUnit) {
		resUnit = PICT_UNKNOWN_UNIT;
		bRet = FALSE;
		if(NULL != pE) {
		CPictCrack	C;
		
			pE->m_cause = CPictException::errCompression;
			pE->m_strPictType = GetRuntimeClass()->m_lpszClassName;
			pE->m_strCause = C.Crack(PICT_PROP_RESOLUTIONUNIT, resUnit);
			pE->m_strPictName = GetFileName();
		}
	}
	TAGMAP[PICT_PROP_RESOLUTIONUNIT] = TAG(PICT_PROP_RESOLUTIONUNIT, (WORD)resUnit);
	return bRet;
}

BOOL CPolyGISPicture::SetOrientation(PICT_ORIENT orient, CPictException *pE)
{
	if (PICT_ORIENT_LOWERLEFT == orient) {
		m_orientation = orient;
	} 
	else {
		if (NULL != pE) {
		CPictCrack	C;
		
			pE->m_cause = CPictException::errCompression;
			pE->m_strPictType = GetRuntimeClass()->m_lpszClassName;
			pE->m_strCause = C.Crack(PICT_PROP_ORIENTATION, orient);
			pE->m_strPictName = GetFileName();
		}
		return FALSE;
	}
	TAGMAP[PICT_PROP_ORIENTATION] = TAG(PICT_PROP_ORIENTATION, (WORD)m_orientation);
	return TRUE;
}

long CPolyGISPicture::GetImageBytes(const CRect& rcSrc, HPBYTE lpBuf)
{
	return 0;
}

long CPolyGISPicture::SetImageBytes(const CRect& rcDst, HPBYTE lpBuf)
{
	return 0;
}

BOOL CPolyGISPicture::SetClut (LPRGBQUAD pClut, long items)
{
	return TRUE;
}

BOOL CPolyGISPicture::GetClut (LPRGBQUAD pClut, long items)
{
	return FALSE;
}

BOOL CPolyGISPicture::KnowsPaletteBeforeDrawing()
{
    return FALSE;
}

void CPolyGISPicture::SetTransparency(int nChannel, COLORREF rgb)
{
}

long CPolyGISPicture::GetUsedColors()
{
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Zeichnen eines Ausschnittes der Karte
inline
CRect CalcSourceRect (CPgrTile *pTile, CRect const &rcSrc)
{
// from left, top, right, and bottom
	return CRect(
		max(rcSrc.left - (long)pTile->GetXMin(), 0),
		TILE_SIZE_Y - min(rcSrc.top - (long)pTile->GetYMin(), TILE_SIZE_Y),
		min(rcSrc.right - (long)pTile->GetXMin(), TILE_SIZE_X),
		TILE_SIZE_Y - max(rcSrc.bottom - (long)pTile->GetYMin(), 0)
	);
}

inline
long D2L (double dToRound)
{
	if (0.0 == dToRound)
		return 0;
	if (dToRound >= 0) 
		return long(dToRound + 0.5);
	return long (dToRound - 0.5);
}

inline
CRect CalcDestinationRect (CPgrTile *pTile, CRect const &rcSrc, CRect const &rcDest)
{
double dScaleX = double(rcDest.Width())/double(rcSrc.Width());
double dScaleY = double(rcDest.Height())/double(rcSrc.Height());
double dScale = (dScaleX + dScaleY) / 2.0;

CRect rcT (
		D2L((pTile->GetXMin() - rcSrc.left) * dScale) + rcDest.left,
		D2L((pTile->GetYMin() - rcSrc.bottom) * dScale) + rcDest.bottom,
		D2L((pTile->GetXMax() - rcSrc.left) * dScale) + rcDest.left,
		D2L((pTile->GetYMax() - rcSrc.bottom) * dScale) + rcDest.bottom
	);

	rcT.left = max(rcT.left, rcDest.left);
	rcT.top = max(rcT.top, rcDest.bottom);
	rcT.right = min(rcT.right, rcDest.right);
	rcT.bottom = min(rcT.bottom, rcDest.top);
	return rcT;
}

HRESULT CPolyGISPicture::DrawTile(CPgrTile *pTile, CDC* pDC, CRect const &rcSrc, 
	CRect const &rcDst)
{
#if defined(_DEBUG)
	++m_lDrawnTiles;
#endif // defined(_DEBUG)

CRect rcSrcT = CalcSourceRect(pTile, rcSrc);
CRect rcDstT = CalcDestinationRect(pTile, rcSrc, rcDst);

LBitmapBase bmp;
FILEINFO FI;

	memset(&FI, 0, sizeof(FILEINFO));
	FI.Format = FILE_CMP;
	FI.Flags = FILEINFO_FORMATVALID;

	_ASSERTE(NULL != m_pFile->m_hFile);
	VERIFY(SUCCESS <= bmp.File()->LoadOffset(m_pFile->m_hFile, pTile->GetOffset(), pTile->GetByteCount(), 
		m_bitsPerSample, ORDER_BGR, LOADFILE_ALLOCATE | LOADFILE_STORE, NULL, &FI));
	bmp.SetViewPerspective(BOTTOM_LEFT);

	VERIFY(SUCCESS <= bmp.SetSrcRect(&rcSrcT));					// QuellBereich setzen
	VERIFY(SUCCESS <= bmp.SetDstRect(&rcDstT));					// Zielbereich setzen
//	VERIFY(SUCCESS <= bmp.SetClipDstRect(&rcClip));				// ZielClippingArea setzen

	bmp.Paint()->SetDC (pDC->GetSafeHdc());
	return (bmp.Paint()->PaintDC() >= SUCCESS) ? S_OK : E_FAIL;
}

BOOL CPolyGISPicture::Draw (CDC* pDC, CRect const &rcSrc, CRect const &rcDst, 
	BOOL bRealizePalette, HandlePaletteFunc handlePal)
{
    _ASSERTE(NULL == handlePal);

// Im Cache den passenden PgrHolder wiederfinden
os_path pgrpath = (LPCTSTR)m_pFile->GetFilePath();

	pgrpath.extension("pgr");

CString pgr(pgrpath);

	pgr.MakeLower();

CPgrTileHolder *pPgrTiles = g_pictCache.EnsureItem(pgr, false);

	_ASSERTE(NULL != pPgrTiles);
	if (NULL == pPgrTiles) 
		return FALSE;		// snh

#if defined(_DEBUG)
	m_lDrawnTiles = 0;
#endif // defined(_DEBUG)

// suchen aller Kacheln, die durch dieses Zeichnen betroffen sind
CStdThunkImpl<CPolyGISPicture, DRAWTILEPROC> Thunk(this, &CPolyGISPicture::DrawTile);

// (0, 0) ist links unten
CRect rcSrcCopy = rcSrc;
long lHeight = m_rcPicture.Height();

	rcSrcCopy.top = lHeight-rcSrc.top;
	rcSrcCopy.bottom = lHeight-rcSrc.bottom;

BOOL fReturn = SUCCEEDED(pPgrTiles->EnumTiles(Thunk.GetThunk(), pDC, rcSrcCopy, rcDst));

#if defined(_DEBUG)
	TRACE1("TRiAS: PolyGISPicture: Anzahl der gezeichneten Tiles: %ld\r\n", m_lDrawnTiles);
#endif // defined(_DEBUG)

	return fReturn;
}

CString CPolyGISPicture::GetBlockName()
{
	return CString();
}

void CPolyGISPicture::SetBlockName(LPCTSTR pcBlockName)
{
}

void CPolyGISPicture::CacheHit (BOOL bHit)
{
}

HPBYTE CPolyGISPicture::GetDataPointer()
{
	return NULL;
}

HPBYTE CPolyGISPicture::GetTmpPointer()
{
	return NULL;
}

BOOL CPolyGISPicture::GetGeoPoints (GCPList *pGcpList, CPictException *e)
{
// Im Cache den passenden PgrHolder wiederfinden
os_path pgrpath = (LPCTSTR)m_pFile->GetFilePath();

	pgrpath.extension("pgr");

CString pgr(pgrpath);

	pgr.MakeLower();

CPgrTileHolder *pPgrTiles = g_pictCache.EnsureItem(pgr, false);

	_ASSERTE(NULL != pPgrTiles);
	if (NULL == pPgrTiles)	// should not happen
		return FALSE;

	if (!*pPgrTiles) {
		if (NULL != e) {
			e->m_cause = CPictException::errMissingInfo;
			e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
			e->m_strPictName = GetFileName();
		}
		return FALSE;
	}

	try {
	// Paßpunkte liefern
	double dXMin, dYMin, dXMax, dYMax;

		pPgrTiles->GetMBR(dXMin, dYMin, dXMax, dYMax);
		pGcpList->clear();
		pGcpList->push_back (
			GCP(
				GEOPOINT(dXMin, dYMin, 0), 
				GEOPOINT(0, pPgrTiles->GetSizeY(), 0)
			)
		);
		pGcpList->push_back (
			GCP(
				GEOPOINT(dXMax, dYMin, 0), 
				GEOPOINT(pPgrTiles->GetSizeX(), pPgrTiles->GetSizeY(), 0)
			)
		);
		pGcpList->push_back (
			GCP(
				GEOPOINT(dXMax, dYMax, 0), 
				GEOPOINT(pPgrTiles->GetSizeX(), 0, 0)
			)
		);
		pGcpList->push_back (
			GCP(
				GEOPOINT(dXMin, dYMax, 0), 
				GEOPOINT(0, 0, 0)
			)
		);
	}
	catch (...) {
		if (NULL != e) {
			e->m_cause = CPictException::errMemory;
			e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
			e->m_strPictName = GetFileName();
		}
		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert Koordinatensystem für die Paßpunkte
const double tcsPI = 3.1415926535897932384626433;
const double ARC_PI = 180.0 / tcsPI;

inline 
double GetFalseEastingGK (double dX)
{
	return ((int)( dX / 1000000.0 ) * 1000000.0 + 500000.0);
}

inline 
double GetLonOriginGK (double dX)
{
	return (int)( dX / 1000000.0 ) * 3 * 3600;
}

BOOL CPolyGISPicture::GetGeoPointCS (IUnknown **ppICS, GCPList &rGCPList, 
	CPictException *e)
{
	if (NULL == ppICS) {
		if (NULL != e) {
			e->m_cause = CPictException::errMissingInfo;
			e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
			e->m_strPictName = GetFileName();
		}
		return FALSE;
	}
	*ppICS = NULL;

	try {
	// ggf. zugehöriges Koordinatensystem liefern 
	GCP &rGCP0 = rGCPList[0];		// links unten

	double dFalseEast = GetFalseEastingGK(rGCP0.m_ptGeoCoord.X);
	double dMeridian = GetLonOriginGK(rGCP0.m_ptGeoCoord.X);
	
	ITRiASCSPtr pCS;
	HRESULT	hr = pCS.CreateInstance(CLSID_TRIASCS);

		pCS->put_CoordSystemType(tcsCS_Projected);

	ITRiASCSGCSPtr pGCS;
	ITRiASCSPCSPtr pPCS;

		pCS->get_GeographicCS(&pGCS);
		pCS->get_ProjectedCS(&pPCS);

		pGCS->put_GeodeticDatum(tcsGD_DeutscheHauptdreiecksnetz);
		pGCS->put_PrimeMeridian(tcsPM_Greenwich);
		pGCS->put_UnitOfAngle(tcsUOA_Second);

	ITRiASCSDatumTransformationPtr pDT;

		pCS->get_DatumTransformation(&pDT);
		pDT->put_TransformationAlgorithm(tcsDTA_PositionVector7ParamTransformation);
		pDT->put_GeodeticDatum(tcsGD_DeutscheHauptdreiecksnetz);

		pPCS->put_ProjectionAlgorithm(tcsPA_TransverseMercator);
		pPCS->put_ProjectionParameter(tcsPP_GaussKrueger_LongitudeOfNaturalOrigin, dMeridian);
		pPCS->put_ProjectionParameter(tcsPP_GaussKrueger_FalseEasting, dFalseEast);
		pPCS->put_ProjectionParameter(tcsPP_GaussKrueger_FalseNorthing, 0.0);
		pPCS->put_ProjectionParameter(tcsPP_GaussKrueger_LatitudeOfNaturalOrigin, 0.0);
		pPCS->put_ProjectionParameter(tcsPP_GaussKrueger_ScaleFactorAtNaturalOrigin, 1.0);

		*ppICS = pCS.Detach();
	}
	catch (...) {
		if (NULL != e) {
			e->m_cause = CPictException::errMemory;
			e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
			e->m_strPictName = GetFileName();
		}
		return FALSE;
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// PolyGIS Rasterkartenwerke haben im allgemeinen weiße Ränder in den Bildern
// mit geringerer Auflösung (raster2..rasterN), daher muß für jedes Bild der 
// Rand mit anderen Werten ausgeblendet werden, zumal sich die Geokodiertung
// auf die 'richtigen' Pixel bezieht.
BOOL CPolyGISPicture::WantsToCorrectGeoPoints()
{
	return TRUE;	// GeoPunkte müssen korrigiert werden
}

BOOL CPolyGISPicture::CorrectGeoPoints (CSize &rSize, GCPList &rGCPList, 
	int iSubFile, CPictException *e)
{
// Im Cache den passenden PgrHolder wiederfinden
os_path pgrpath = (LPCTSTR)m_pFile->GetFilePath();

	pgrpath.extension("pgr");

CString pgr(pgrpath);

	pgr.MakeLower();

CPgrTileHolder *pPgrTiles = g_pictCache.EnsureItem(pgr, false);

	_ASSERTE(NULL != pPgrTiles);
	if (NULL == pPgrTiles)	// should not happen
		return FALSE;

// original Bildgröße (muß später hochgerechnet werden)
long lSizeX = pPgrTiles->GetSizeX();
long lSizeY = pPgrTiles->GetSizeY();

GCP &rGCP0 = rGCPList[0];		// links unten
GCP &rGCP2 = rGCPList[2];		// rechts oben
long lGCPX = long(lSizeX * (((rGCP2.m_ptGeoCoord.X-rGCP0.m_ptGeoCoord.X))/pPgrTiles->GetRealSizeX()) + 0.5);
long lGCPY = long(lSizeY * (((rGCP2.m_ptGeoCoord.Y-rGCP0.m_ptGeoCoord.Y))/pPgrTiles->GetRealSizeY()) + 0.5);

	_ASSERTE(lGCPX <= lSizeX);
	_ASSERTE(lGCPY <= lSizeY);

// links unten
	rGCP0.m_ptPictPoint.X = 0;
	rGCP0.m_ptPictPoint.Y =  lSizeY;

// rechts unten
	rGCPList[1].m_ptPictPoint.X = lGCPX; 
	rGCPList[1].m_ptPictPoint.Y = lSizeY; 

// rechts oben
	rGCP2.m_ptPictPoint.X = lGCPX;
	rGCP2.m_ptPictPoint.Y = lSizeY-lGCPY;

// links oben	
	rGCPList[3].m_ptPictPoint.X = 0; 
	rGCPList[3].m_ptPictPoint.Y = lSizeY-lGCPY; 

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// 
void CPolyGISPicture::Serialize(CArchive& ar) 
{
	CPicture::Serialize(ar);
}

