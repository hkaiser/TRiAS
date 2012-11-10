// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 17.03.2002 13:59:07 
//
// @doc
// @module PolyGISPicture.h | Declaration of the <c CPolyGISPicture> class

#if !defined(_POLYGISPICTURE_H__3879FF3C_DF5D_40E1_90EC_A401729DF74D__INCLUDED_)
#define _POLYGISPICTURE_H__3879FF3C_DF5D_40E1_90EC_A401729DF74D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "PgrHolder.h"

///////////////////////////////////////////////////////////////////////////////
// eine Ebene eines PolyGIS eigenen Rasterwerkes (maps.dat)
class AFX_EXT_CLASS CPolyGISPicture : 
	public CPicture 
{
private:

protected:
	DECLARE_SERIAL(CPolyGISPicture);

	virtual	void Init();
	virtual	BOOL Clone(CPicture *pPicture, CPictException *pE = NULL);

	virtual	long AlignTop(long line);
	virtual	long FillBuffer(long nBytes, long startRestBytes, long nRestBytes);
	virtual	long StoreScanLine(HPBYTE pLine, long line, const CRect& rcCore);
	virtual	BOOL ReadRaw(const CRect& rcRect);
	virtual BOOL Decode(const CRect& rcRect);

	BOOL FillPictureList (CFile &rFile, PGRHEADER &rHdr, CPgrTileHolder *pPgrTile, CPictException *e = NULL);
	BOOL FillPictureList2 (CFile &rFile, PGRHEADER2 &rHdr, CPgrTileHolder *pPgrTile, CPictException *e = NULL);
	BOOL FillPictureListOld (CFile &rFile, PGRHEADEROLD &rHdr, CPgrTileHolder *pPgrTile, CPictException *e = NULL);

	BOOL FillPictException(int iCause, LPCTSTR pcPath, CPictException *e = NULL);

	void SetTileSize(long lSizeX, long lSizeY);

// Implementation
public:
	CPolyGISPicture();
	virtual	~CPolyGISPicture();

	virtual HPBYTE GetDataPointer();
	virtual HPBYTE GetTmpPointer();

	virtual	BOOL ReadHeader(CPictException *e = NULL, int nPicture = 0 );
	virtual BOOL SelectSubFile(int nFile );

	virtual	void SetPictRect(const CRect& rcPict );
	virtual	BOOL WriteHeader();
	virtual	BOOL WriteTrailer();
	virtual	BOOL Write(const CRect& rcRect, PICT_ORIENT srcOrient = PICT_ORIENT_UPPERLEFT);

	virtual const CRect GetBestCorePictRect();
	virtual	long GetNeededFileSize();

	virtual BOOL SetCompression(PICT_COMPR compr, CPictException *pE = NULL);
	virtual	BOOL SetColorspace(PICT_COLOR color, CPictException *pE = NULL);
	virtual BOOL SetResolutionUnit(PICT_RESUNIT resUnit, CPictException *pE = NULL);
	virtual BOOL SetOrientation(PICT_ORIENT orient, CPictException *pE = NULL);

	virtual	long GetImageBytes(const CRect& rcSrc, HPBYTE lpBuf);
	virtual	long SetImageBytes(const CRect& rcDst, HPBYTE lpBuf);
	
	virtual const CString GetPictType();		// "PGIS"
	virtual BOOL GetClut (LPRGBQUAD pClut, long items = 256);
	virtual BOOL SetClut (LPRGBQUAD pClut, long items = 256);
	virtual void SetTransparency(int nChannel, COLORREF rgb);
	virtual long GetUsedColors();
    virtual BOOL KnowsPaletteBeforeDrawing();

	virtual CString GetBlockName();
	virtual void SetBlockName(LPCTSTR pcBlockName);
	virtual void CacheHit (BOOL bHit = TRUE);

	virtual BOOL Draw (CDC *pDC, const CRect& rcSrc, const CRect& rcDst, 
        BOOL bRealizePalette = TRUE, HandlePaletteFunc handlePal = NULL);

	virtual BOOL GetGeoPoints (GCPList *pGcpList, CPictException *e = NULL);
	virtual BOOL GetGeoPointCS (IUnknown **ppICS, GCPList &rGCPList, CPictException *e = NULL);
	virtual BOOL WantsToCorrectGeoPoints();
	virtual BOOL CorrectGeoPoints (CSize &rSize, GCPList &GCPList, int iSubFile, CPictException *e = NULL);

	HRESULT __stdcall DrawTile (CPgrTile *pTile, CDC *pDC, CRect const &rSrc, CRect const &rDest);

	static void ReleaseCache();

// Serialization
public:
	virtual	void Serialize(CArchive& ar);

#if defined(_DEBUG)
private:
	long m_lDrawnTiles;
#endif // defined(_DEBUG)
};

#endif // !defined(_POLYGISPICTURE_H__3879FF3C_DF5D_40E1_90EC_A401729DF74D__INCLUDED_)
