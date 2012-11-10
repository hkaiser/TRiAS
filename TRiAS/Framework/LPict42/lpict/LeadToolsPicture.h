// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 25.11.2004 19:14:07 
//
// @doc
// @module LeadToolsPicture.h | Declaration of the <c CLeadToolsPicture> class

#if !defined(_LEADTOOLSPICTURE_H__3879FF3C_DF5D_40E1_90EC_A401729DF74D__INCLUDED_)
#define _LEADTOOLSPICTURE_H__3879FF3C_DF5D_40E1_90EC_A401729DF74D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// eine Ebene eines PolyGIS eigenen Rasterwerkes (maps.dat)
class AFX_EXT_CLASS CLeadToolsPicture : 
	public CPictureBase
{
private:
    BOOL TagError(int cause, long tagNum, CPictException *e = NULL);
    BOOL TagError(int cause, LPCTSTR lpszDescr, CPictException *e = NULL); 

protected:
	DECLARE_SERIAL(CLeadToolsPicture);

	virtual	void Init();
	virtual	BOOL Clone(CPicture *pPicture, CPictException *pE = NULL);

	virtual	long AlignTop(long line);
	virtual	long FillBuffer(long nBytes, long startRestBytes, long nRestBytes);
	virtual	long StoreScanLine(HPBYTE pLine, long line, const CRect& rcCore);
	virtual	BOOL ReadRaw(const CRect& rcRect);
	virtual BOOL Decode(const CRect& rcRect);

	BOOL FillPictException(int iCause, LPCTSTR pcPath, CPictException *e = NULL,
        LPCSTR pcCause = NULL);

// Implementation
public:
	CLeadToolsPicture();
	virtual	~CLeadToolsPicture();

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
	
	virtual const CString GetPictType();		// "LEAD"
	virtual void SetTransparency(int nChannel, COLORREF rgb);

	virtual CString GetBlockName();
	virtual void SetBlockName(LPCTSTR pcBlockName);
	virtual void CacheHit (BOOL bHit = TRUE);

    virtual BOOL KnowsPaletteBeforeDrawing();

	virtual BOOL Draw (CDC *pDC, const CRect& rcSrc, const CRect& rcDst, 
        BOOL bRealizePalette = TRUE, HandlePaletteFunc handlePal = NULL);

// Serialization
public:
	virtual	void Serialize(CArchive& ar);
};

#endif // !defined(_LEADTOOLSPICTURE_H__3879FF3C_DF5D_40E1_90EC_A401729DF74D__INCLUDED_)
