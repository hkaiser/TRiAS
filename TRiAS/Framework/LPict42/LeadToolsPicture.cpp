// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 25.11.2004 19:14:07 
//
// @doc
// @module LeadToolsPicture.cpp | Definition of the <c CLeadToolsPicture> class

#include "stdafx.h"

#include <Com/Thunk.h>
#include <ospace/file/path.h>

#include <ltwrappr.h>
#include <pgr.h>

#include "LPictImpl.h"
#include "lpict/LeadToolsPicture.h"
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

IMPLEMENT_SERIAL(CLeadToolsPicture, CPicture, 1);

#define	new	DEBUG_NEW

///////////////////////////////////////////////////////////////////////////////
// Initialisierung etc.
CLeadToolsPicture::CLeadToolsPicture() :
	CPictureBase() 
{
	Init();
}

void CLeadToolsPicture::Init() 
{
	CPicture::Init();
	m_compression = PICT_COMPR_NOCOMPR;		// Komprimierung wird nicht hier behandelt
	m_bitsPerSample = 24;
	m_samplesPerPixel = 3;
	m_colorspace = PICT_COLOR_RGB;
	m_nPlanarConfiguration = PICT_PLANARCFG_CHUNKED;
	m_orientation = PICT_ORIENT_LOWERLEFT;

//	TAGMAP[PICT_PROP_SAMPLESPERPIXEL] = TAG(PICT_PROP_SAMPLESPERPIXEL, (WORD)m_samplesPerPixel);
	TAGMAP[PICT_PROP_BITSPERSAMPLE] = TAG(PICT_PROP_BITSPERSAMPLE, (WORD)m_bitsPerSample);
	TAGMAP[PICT_PROP_COLORSPACE] = TAG(PICT_PROP_COLORSPACE, (WORD)m_colorspace);
	TAGMAP[PICT_PROP_COMPRESSION] = TAG(PICT_PROP_COMPRESSION, (WORD)m_compression);
	TAGMAP[PICT_PROP_PLANARCONFIGURATION] = TAG(PICT_PROP_PLANARCONFIGURATION, (WORD)PICT_PLANARCFG_CHUNKED);
	TAGMAP[PICT_PROP_ORIENTATION] = TAG(PICT_PROP_ORIENTATION, (WORD)m_orientation);
}

///////////////////////////////////////////////////////////////////////////////
// 
BOOL CLeadToolsPicture::Clone(CPicture *pPicture, CPictException *pE)
{
	return FALSE;
}

long CLeadToolsPicture::AlignTop(long line)
{
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// FillBuffer wird für den eigenen Codec support benötigt, entfällt hier
long CLeadToolsPicture::FillBuffer(long nBytes, long startRestBytes, long nRestBytes)
{
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
// StoreScanLine wird für den eigenen Codec support benötigt, entfällt hier
long CLeadToolsPicture::StoreScanLine(HPBYTE pLine, long line, const CRect& rcCore)
{
	_ASSERTE(FALSE);		// dürfte nie gerufen werden
	return 0;
}

BOOL CLeadToolsPicture::ReadRaw(const CRect& rcRect)
{
	return TRUE;
}

BOOL CLeadToolsPicture::Decode(const CRect& rcRect)
{
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// FillPictException
BOOL CLeadToolsPicture::FillPictException(int iCause, LPCTSTR pcPath, 
    CPictException *e, LPCSTR pcCause)
{
	if (NULL != e) {
		e->m_cause = iCause;
		e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
		e->m_strPictName = pcPath;
        if (NULL != pcCause)
            e->m_strCause = pcCause;
	}
	return FALSE;
}

BOOL CLeadToolsPicture::TagError(int cause, long tagNum, CPictException *e /*= NULL*/) 
{
	if( NULL != e ) {
		CString	S;
		S.Format( _T("%d [0x%04x]"), tagNum, tagNum );
		e->m_cause = cause;
		e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
		e->m_strCause = S;
		e->m_strPictName = m_pFile->GetFilePath();
	}
	return false;
}

BOOL CLeadToolsPicture::TagError(int cause, LPCTSTR lpszDescr, 
    CPictException *e /*= NULL*/) 
{
	if( NULL != e ) {
		e->m_cause = cause;
		e->m_strPictType = GetRuntimeClass()->m_lpszClassName;
		e->m_strCause = lpszDescr;
		e->m_strPictName = m_pFile->GetFilePath();
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// 
BOOL CLeadToolsPicture::ReadHeader(CPictException *e, int nPicture)
{
	if (0 != nPicture)
		return FALSE;	// no subpicture support

	ASSERT(NULL != m_pFile);
	ASSERT_VALID(m_pFile);

// fertig initialisieren
	Init();
	if (!g_LeadTools.EnsureLoaded(e))
		return FALSE;

L_INT nErrorCode;
LFile file;
LBitmapBase pict;
FILEINFO fileinfo;

    memset(&fileinfo, 0, sizeof(FILEINFO));
    file.SetBitmap(&pict);
    file.SetFileName((LPSTR)(LPCSTR)m_pFile->GetFilePath());

    nErrorCode = file.GetInfo(&fileinfo);
    if (nErrorCode < 1) {
        return FillPictException(CPictException::errMissingInfo, 
            m_pFile->GetFilePath(), e, LBase::GetErrorString (nErrorCode)); 
    }

    switch(fileinfo.Format) {
    case FILE_TIF:          // RGB or 8-bit grayscale, uncompressed
    case FILE_TIFLZW:       // RGB, LZW compressed
    case FILE_TIF_PACKBITS: // RGB, packbits compressed
    case FILE_TIF_JBIG:     // JBIG compressed
    case FILE_TIF_CMP:      // CMP compressed
    case FILE_TIF_J2K:      // J2K compressed
    case FILE_JTIF:         // JPEG compression (lossless) YUV 4:4:4 color space
    case FILE_LEAD2JTIF:    // JPEG compression and YUV 4:2:2 color space 
    case FILE_LEAD1JTIF:    // JPEG compression and YUV 4:1:1 color space.
    case FILE_CCITT:        // CCITT compressed
    case FILE_CCITT_GROUP3_1DIM:
    case FILE_CCITT_GROUP3_2DIM:
    case FILE_CCITT_GROUP4:
        break;

    case FILE_BMP:          // Windows BMP format, uncompressed
    case FILE_BMP_RLE:      // Windows BMP, RLE compression
    case FILE_OS2:          // OS/2 BMP version 1.x. 
    case FILE_OS2_2:        // OS/2 BMP version 2.x. 
        break;

    default:
        return FALSE;       // unsupported file format
    }

    nErrorCode = file.LoadTile(0, 0, 1, 1);
    if (nErrorCode < 1) {
        return FillPictException(CPictException::errMissingInfo, 
            m_pFile->GetFilePath(), e, LBase::GetErrorString (nErrorCode)); 
    }

// Tags füllen
    m_bitsPerSample = fileinfo.BitsPerPixel;

	m_orientation = PICT_ORIENT_LOWERLEFT;
	TAGMAP[PICT_PROP_BITSPERSAMPLE] = TAG(PICT_PROP_BITSPERSAMPLE, 
        (WORD)m_bitsPerSample);

	SetPictRect(CRect (0, 0, fileinfo.Width, fileinfo.Height));
	SetResolutionUnit(PICT_UNIT_PELS);
	SetXResolution(fileinfo.XResolution);
	SetYResolution(fileinfo.YResolution);

L_INT iGray = pict.IsGrayScale();

    if (GRAY_NO != iGray) {
        _ASSERTE(GRAY_NOTORDERED != iGray);     // not supported (yet)
        m_colorspace = (GRAY_ORDEREDNORMAL == iGray) ? PICT_COLOR_MONOBIZ : PICT_COLOR_MONOWIZ;
    }
    else if (m_bitsPerSample < 16) {
        m_colorspace = PICT_COLOR_PALETTE;
    }
    else {
        m_colorspace = PICT_COLOR_RGB;
    }

	if ((PICT_COLOR_MONOWIZ == m_colorspace || PICT_COLOR_MONOBIZ == m_colorspace) &&
		(8 == m_bitsPerSample || 4 == m_bitsPerSample)) 
    {
		_ASSERTE(NULL != m_pClut);
		m_nColors = m_nUsedColors = (1 << m_bitsPerSample);
		if (PICT_COLOR_MONOWIZ == m_colorspace) {
			for (int i = 0; i < m_nColors; i++) {
				m_pClut[i].rgbBlue = m_pClut[i].rgbGreen = m_pClut[i].rgbRed = (BYTE) ((m_nColors - 1) - i);
				m_pClut[i].rgbReserved = (BYTE) 0;
			}
		} 
        else {
        // 1 ... Black Is Zero; zugl. default
			for (int i = 0; i < m_nColors; i++) {
				m_pClut[i].rgbBlue = m_pClut[i].rgbGreen = m_pClut[i].rgbRed = (BYTE) i;
				m_pClut[i].rgbReserved = (BYTE) 0;
			}
		}
		m_colorspace = PICT_COLOR_PALETTE;
		SetClut(m_pClut, m_nColors);
	} 
    else if ((PICT_COLOR_MONOWIZ == m_colorspace || PICT_COLOR_MONOBIZ == m_colorspace) &&
		     (1 == m_bitsPerSample)) 
    {
		_ASSERTE(NULL != m_pClut);
		m_nColors = 2;
		if (PICT_COLOR_MONOWIZ == m_colorspace) {
			m_pClut[0].rgbBlue = m_pClut[0].rgbGreen = m_pClut[0].rgbRed = 0xff;
			m_pClut[1].rgbBlue = m_pClut[1].rgbGreen = m_pClut[1].rgbRed = 0x00;
		} 
        else {
        // 1 ... Black Is Zero; zugl. default
			m_pClut[0].rgbBlue = m_pClut[0].rgbGreen = m_pClut[0].rgbRed = 0x00;
			m_pClut[1].rgbBlue = m_pClut[1].rgbGreen = m_pClut[1].rgbRed = 0xff;
		}
	} 
    else if ((PICT_COLOR_PALETTE == m_colorspace) &&
		     (8 == m_bitsPerSample || 4 == m_bitsPerSample)) 
    {
		_ASSERT(NULL != m_pClut);

    // try to initialise color table from TIFF tags
    L_UINT16 tagtype = 0;
    L_UINT32 count = 0;

        nErrorCode = file.ReadTag(TAGCOLORMAP, &tagtype, &count, NULL);
        if (nErrorCode >= 1) {
            if (TAG_SHORT != tagtype) 
			    return TagError(CPictException::errMissingInfo, TAGCOLORMAP, e);

        LBuffer buffer(count * sizeof(short));

            nErrorCode = file.ReadTag(TAGCOLORMAP, &tagtype, &count, &buffer);
            if (nErrorCode < 1 || TAG_SHORT != tagtype) 
			    return TagError(CPictException::errMissingInfo, TAGCOLORMAP, e);

		    m_nColors = (1 << m_bitsPerSample);
		    m_nUsedColors = count / 3;

        short *pLoopData = (short *)buffer.Lock();

            for (int i = 0; i < m_nUsedColors; ++i, ++pLoopData) {
                m_pClut[i].rgbRed = (BYTE)(pLoopData[0] / 256);
                m_pClut[i].rgbGreen = (BYTE)(pLoopData[m_nUsedColors] / 256);
                m_pClut[i].rgbBlue = (BYTE)(pLoopData[2*m_nUsedColors] / 256);
                m_pClut[i].rgbReserved = (BYTE)0;
            }

            buffer.Unlock();
        }
	} 
    else if ((PICT_COLOR_RGB == m_colorspace && 24 == m_bitsPerSample)) {
		_ASSERTE(NULL != m_pClut);
		m_nColors = 0;
	} 
    else {
        return FillPictException(CPictException::errColorSpace, 
            m_pFile->GetFilePath(), e, szUnknown);
	}

	m_rcStrip = m_rcPicture;
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// 
BOOL CLeadToolsPicture::SelectSubFile(int nFile)
{
	return 0 == nFile ? TRUE : FALSE;
}

void CLeadToolsPicture::SetPictRect(const CRect& rcPict)
{
	m_rcImage = m_rcPicture = rcPict;
	m_rcImage.right = Align(m_rcPicture.Width(), m_bitsPerSample, sizeof(DWORD));
	TAGMAP[PICT_PROP_IMAGEWIDTH] = TAG(PICT_PROP_IMAGEWIDTH, (ULONG)rcPict.Width());
	TAGMAP[PICT_PROP_IMAGELENGTH] = TAG(PICT_PROP_IMAGELENGTH, (ULONG)rcPict.Height());
}

BOOL CLeadToolsPicture::WriteHeader()
{
	return TRUE;
}

BOOL CLeadToolsPicture::WriteTrailer()
{
	return TRUE;
}

BOOL CLeadToolsPicture::Write(const CRect& rcRect, PICT_ORIENT srcOrient)
{
	return TRUE;
}

const CRect CLeadToolsPicture::GetBestCorePictRect()
{
	return CRect();
}

long CLeadToolsPicture::GetNeededFileSize()
{
	return 0;
}

BOOL CLeadToolsPicture::SetCompression(PICT_COMPR compr, CPictException *pE)
{
	return TRUE;
}

BOOL CLeadToolsPicture::SetColorspace(PICT_COLOR color, CPictException *pE)
{
	return TRUE;
}

BOOL CLeadToolsPicture::SetResolutionUnit(PICT_RESUNIT resUnit, CPictException *pE)
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

BOOL CLeadToolsPicture::SetOrientation(PICT_ORIENT orient, CPictException *pE)
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

long CLeadToolsPicture::GetImageBytes(const CRect& rcSrc, HPBYTE lpBuf)
{
	return 0;
}

long CLeadToolsPicture::SetImageBytes(const CRect& rcDst, HPBYTE lpBuf)
{
	return 0;
}

void CLeadToolsPicture::SetTransparency(int nChannel, COLORREF rgb)
{
    CPictureBase::SetTransparency(nChannel, rgb);
}

///////////////////////////////////////////////////////////////////////////////
// Zeichnen eines Ausschnittes der Karte
BOOL CLeadToolsPicture::Draw (CDC* pDC, CRect const &rcSrc, CRect const &rcDst, 
	BOOL bRealizePalette, HandlePaletteFunc handlePal)
{
BOOL bRet = FALSE;
long height = min(rcSrc.Height(), GetPictRect().Height());
long width = min(rcSrc.Width(), GetPictRect().Width());
CRect rcBand(rcSrc.left, rcSrc.top, rcSrc.left + width, rcSrc.top + height);

    if (CPicture::SetCoreRect(rcBand)) {
    L_INT nErrorCode;
    LFile file;
    LBitmapBase pict;

        file.SetBitmap(&pict);
        file.SetFileName((LPSTR)(LPCSTR)m_pFile->GetFilePath());

	    rcBand.OffsetRect(-rcSrc.left, -rcSrc.top);
	    rcBand.OffsetRect(rcSrc.left - m_rcPictInCore.left, rcSrc.top - m_rcPictInCore.top);

        nErrorCode = file.LoadTile(
            m_rcPictInCore.left, m_rcPictInCore.top, m_rcPictInCore.Width(), m_rcPictInCore.Height());
        if (nErrorCode < 1) return FALSE;

    HGLOBAL hDIBBits = LChange::ChangeToDIB(&pict);

    BITMAPINFO *pBMI = (BITMAPINFO *)GlobalLock(hDIBBits);
    BYTE *pData = (BYTE *)pBMI + sizeof(BITMAPINFOHEADER);
    long ulSize = GlobalSize(hDIBBits);
    int nColorData = 0;

        if(pBMI->bmiHeader.biBitCount <= 8)
            nColorData = 1 << pBMI->bmiHeader.biBitCount;
        pData += nColorData * sizeof(RGBQUAD);

        _ASSERTE(pBMI->bmiHeader.biWidth == m_rcPictInCore.Width());
        _ASSERTE(pBMI->bmiHeader.biHeight == m_rcPictInCore.Height());

        if (NULL != handlePal && PICT_COLOR_PALETTE == m_colorspace &&
		    (8 == m_bitsPerSample || 4 == m_bitsPerSample))
        {
        // Palette behandeln
            SetClut(pBMI->bmiColors, pBMI->bmiHeader.biClrUsed);
            handlePal(this);
		    memcpy(pBMI->bmiColors, m_pClut, m_nColors * sizeof(RGBQUAD));
        }

        bRet = CPictureBase::DrawRawDIB(pDC, pBMI, pData, rcBand, rcDst, bRealizePalette);

        GlobalUnlock(hDIBBits);
        GlobalFree(hDIBBits);
    }
    return bRet;
}

CString CLeadToolsPicture::GetBlockName()
{
	return CString();
}

void CLeadToolsPicture::SetBlockName(LPCTSTR pcBlockName)
{
}

void CLeadToolsPicture::CacheHit (BOOL bHit)
{
}

HPBYTE CLeadToolsPicture::GetDataPointer()
{
	return NULL;
}

HPBYTE CLeadToolsPicture::GetTmpPointer()
{
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// 
void CLeadToolsPicture::Serialize(CArchive& ar) 
{
	CPicture::Serialize(ar);
}

