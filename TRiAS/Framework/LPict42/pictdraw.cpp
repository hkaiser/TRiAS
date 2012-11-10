#include "stdafx.h"
#include "LPictImpl.h"
#include "ROP3.h"

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

#define GC( v ) pDC->GetDeviceCaps( (v) )

#if defined(_DEBUG)
static void DCInfo( CDC* pDC ) {
	int	cap;
	cap = GC( HORZSIZE );
	cap = GC( VERTSIZE );
	cap = GC( HORZRES );
	cap = GC( VERTRES );
	cap = GC( LOGPIXELSX );
	cap = GC( LOGPIXELSY );
	cap = GC( BITSPIXEL );
	cap = pDC->GetMapMode();
	CPoint	pt;
	CSize	sz;
	pt = pDC->GetViewportOrg();
	pt = pDC->GetWindowOrg();
	sz = pDC->GetViewportExt();
	sz = pDC->GetWindowExt();
}
#else
inline void DCInfo(CDC * /*pDC*/) {}
#endif

#define PALVERSION   0x300

static int MergePalette( CDC *pDC, LPRGBQUAD pC, int nColors ) 
{
	WORD	nOldEntries, nNewEntries;
	COLORREF	rgb;
	int	idx, i;

	CPalette*	pPal = pDC->GetCurrentPalette();
	pPal->GetObject( sizeof( nOldEntries ), &nOldEntries );
	LPLOGPALETTE	lp = (LPLOGPALETTE) new BYTE[ sizeof( LOGPALETTE ) + ( nOldEntries + nColors ) * sizeof ( PALETTEENTRY ) ];
	LPPALETTEENTRY	pe = lp->palPalEntry;

	if( pPal->GetPaletteEntries( 0, nOldEntries, pe ) )
		pe += nOldEntries;

	for( i = 0, nNewEntries = 0; i < nColors; i++ ) {
		rgb = RGB(pC->rgbRed,pC->rgbGreen,pC->rgbBlue);
		idx = pPal->GetNearestPaletteIndex( rgb );
		pPal->GetPaletteEntries( idx, 1, pe );
		if( ( pe->peRed != GetRValue( rgb ) )
			|| pe->peGreen != GetGValue( rgb )
			|| pe->peBlue != GetBValue( rgb ) )
		{
			pe->peRed	= GetRValue( rgb );
			pe->peGreen	= GetGValue( rgb );
			pe->peBlue	= GetBValue( rgb );
			pe->peFlags	= NULL;
			pe++;
			nNewEntries++;
		}
		pC++;
	}
	if( nNewEntries > 0 ) {
		lp->palVersion = PALVERSION;
		lp->palNumEntries = nOldEntries + nNewEntries;
		CPalette	pal, *pOldPal;
		pal.CreatePalette( lp );
		pOldPal = pDC->SelectPalette( &pal, FALSE );
		pDC->RealizePalette();
	}
	delete lp;
	return (int) nNewEntries;
}

//////////////////////////////////////////////////////////////////////////////
namespace {

BOOL TransparentBlt(
    CDC *pDC, int nXDest, int nYDest, int nWidth, int nHeight, 
    void const *pData, BITMAPINFO const *pBMI, UINT dibMode,
    int nXSrc, int nYSrc, int nSrcWidth, int nSrcHeight,
    COLORREF colorTransparent)
{
CDC memDC, maskDC;

	maskDC.CreateCompatibleDC(pDC);
	memDC.CreateCompatibleDC(pDC);
	
// add these to store return of SelectObject() calls
CBitmap bmpImage;
CBitmap *pOldMemBmp = NULL;

	bmpImage.CreateCompatibleBitmap(pDC, nSrcWidth, nSrcHeight);
	pOldMemBmp = memDC.SelectObject(&bmpImage);

// make a copy of the original bitmap
    ::StretchDIBits(memDC.m_hDC, 0, 0, nSrcWidth, nSrcHeight,
        nXSrc, nYSrc, nSrcWidth, nSrcHeight,
        pData, pBMI, dibMode,
        SRCCOPY);

// Create monochrome bitmap for the mask
CBitmap maskBitmap;
CBitmap *pOldMaskBmp = NULL;

	maskBitmap.CreateBitmap(nSrcWidth, nSrcHeight, 1, 1, NULL);
	pOldMaskBmp = maskDC.SelectObject(&maskBitmap);
	
// Create the mask from the memory DC
	memDC.SetBkColor(colorTransparent);
	maskDC.BitBlt(0, 0, nSrcWidth, nSrcHeight, &memDC, 0, 0, SRCCOPY);
	
// Set the background in memDC to black. Using SRCPAINT with black 
// and any other color results in the other color, thus making 
// black the transparent color
	memDC.SetBkColor(RGB(0, 0, 0));
	memDC.SetTextColor(RGB(255, 255, 255));
	memDC.BitBlt(0, 0, nSrcWidth, nSrcHeight, &maskDC, 0, 0, SRCAND);
	
// Set the foreground to black. See comment above.
	pDC->SetBkColor(RGB(255, 255, 255));
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SetStretchBltMode(STRETCH_DELETESCANS);
	pDC->StretchBlt(nXDest, nYDest, nWidth, nHeight, 
        &maskDC, 0, 0, nSrcWidth, nSrcHeight, SRCAND);
	
// Combine the foreground with the background
	pDC->StretchBlt(nXDest, nYDest, nWidth, nHeight, 
        &memDC, 0, 0, nSrcWidth, nSrcHeight, SRCPAINT);

	if (NULL != pOldMaskBmp)
		maskDC.SelectObject(pOldMaskBmp);
	if (NULL != pOldMemBmp)
		memDC.SelectObject(pOldMemBmp);

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
}   // namespace

BOOL CPictureBase::Draw(CDC* pDC, const CRect& rcSrc, const CRect& rcDst, 
    BOOL bRealizePalette, HandlePaletteFunc handlePal) 
{
    _ASSERTE(NULL == handlePal);    // muss hier immer NULL sein

	BYTE			BI[ sizeof( BITMAPINFO ) + 256 * sizeof( RGBQUAD ) ];	// zum Zeichnen
	LPBITMAPINFO	pBI = (LPBITMAPINFO) BI;

	long height = min( rcSrc.Height(), GetPictRect().Height() );
	long width = min( rcSrc.Width(), GetPictRect().Width() );

	CRect	rcBand( rcSrc.left, rcSrc.top, rcSrc.left + width, rcSrc.top + height );
	
	if( !Read( rcBand ) )
		return FALSE;

	rcBand.OffsetRect( -rcSrc.left, -rcSrc.top );
	rcBand.OffsetRect( rcSrc.left - m_rcPictInCore.left, rcSrc.top - m_rcPictInCore.top );

	memset( (void FAR*) BI, 0x00, sizeof( BI ) );

	pBI->bmiHeader.biSize			= sizeof( BITMAPINFOHEADER );
	pBI->bmiHeader.biWidth			= m_rcPictInCore.Width();
	pBI->bmiHeader.biHeight			= m_rcPictInCore.Height();
	pBI->bmiHeader.biPlanes			= 1;
	pBI->bmiHeader.biBitCount		= m_bitsPerSample;
	pBI->bmiHeader.biCompression	= BI_RGB;
	pBI->bmiHeader.biSizeImage		= m_rcImageInCore.Width() * m_rcImageInCore.Height();
	pBI->bmiHeader.biClrUsed		= m_nColors;
	pBI->bmiHeader.biClrImportant	= m_nColors;

	if( 0 != m_nColors ) {
		memcpy( (void FAR*) pBI->bmiColors, (void FAR*) m_pClut, m_nColors * sizeof( RGBQUAD ) );
	}

    return DrawRawDIB(pDC, pBI, (HPBYTE) *m_pMemBlock, rcBand, rcDst,
        bRealizePalette);
}

BOOL CPictureBase::DrawRawDIB(CDC *pDC, LPBITMAPINFO pBI, HPBYTE lpData, 
    CRect const &rcBand, CRect const &rcDst, BOOL bRealizePalette)
{
	if((8 == m_bitsPerSample || 4 == m_bitsPerSample ) && bRealizePalette) {		// Palettenbild
		if(NULL != m_pFilters) {
        // ggf. Farben filtern
		DWORD	i;
		LPRGBQUAD	pRGB;
		COLORREF	rgb;

		    for (pRGB = pBI->bmiColors, i = 0; i < pBI->bmiHeader.biClrUsed; ++pRGB, ++i) {

			    rgb = RGB(pRGB->rgbRed, pRGB->rgbGreen, pRGB->rgbBlue);

				for(CColorFilter **pFilter = m_pFilters; NULL != *pFilter; ++pFilter) 
                {
					ASSERT_KINDOF(CColorFilter, *pFilter);
					rgb = (*pFilter)->operator()(rgb);
			    }
			    
                pRGB->rgbRed = GetRValue(rgb);
			    pRGB->rgbGreen = GetGValue(rgb);
			    pRGB->rgbBlue = GetBValue(rgb);
            }
		}
		MergePalette(pDC, pBI->bmiColors, pBI->bmiHeader.biClrUsed);
	}

	DCInfo(pDC);

    COLORREF clrTransparent = RGB(m_rgbTranspColor.rgbRed, 
        m_rgbTranspColor.rgbGreen, m_rgbTranspColor.rgbBlue);
	CBrush	br(clrTransparent), *pOldBrush;
	DWORD dwROP = SRCCOPY;
	if (1 == m_bitsPerSample && 0 != m_rgbTranspColor.rgbReserved) {
		pOldBrush = pDC->SelectObject( &br );
		if( 1 == m_rgbTranspColor.rgbReserved )
			dwROP = R3_PSDPxax;
		else
			dwROP = R3_DSPDxax;
	}
    else if (8 == m_bitsPerSample && 0 != m_rgbTranspColor.rgbReserved) {
    // auch Palettenbilder können jetzt transparent sein (#HK041130)
        return TransparentBlt(
            pDC, rcDst.left, rcDst.top, rcDst.right - rcDst.left, rcDst.bottom - rcDst.top,
            lpData, pBI, DIB_RGB_COLORS, 
            rcBand.left, m_rcPictInCore.Height() - rcBand.top - rcBand.Height(), 
		    rcBand.Width(), rcBand.Height(),
            clrTransparent);
    }


	int iStretchMode = pDC->GetStretchBltMode();
	pDC->SetStretchBltMode(STRETCH_DELETESCANS);

	::StretchDIBits(
		pDC->GetSafeHdc( ),
		rcDst.left,
		rcDst.top,
		rcDst.Width(),
		rcDst.bottom - rcDst.top,
		rcBand.left, m_rcPictInCore.Height() - rcBand.top - rcBand.Height(), 
		rcBand.Width(),	rcBand.Height(),
		lpData, pBI, DIB_RGB_COLORS, 
        dwROP);

	pDC->SetStretchBltMode( iStretchMode );
	if( 1 == m_bitsPerSample && 0 != m_rgbTranspColor.rgbReserved ) {
		pDC->SelectObject( pOldBrush );
	}
	return TRUE;
}

