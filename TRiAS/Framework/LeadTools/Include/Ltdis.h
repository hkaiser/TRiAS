/*
   LTDIS.H - display module header file
   Copyright (c) 1991-2000 LEAD Technologies, Inc.
   All Rights Reserved.
*/

#ifndef _LTDIS_H_
#define _LTDIS_H_

#include "lttyp.h"
#include "lterr.h"

#define _HEADER_ENTRY_
#include "ltpck.h"

/*
   flags for L_CopyToClipboardExt
*/
#define COPY2CB_EMPTY 0x0001    /* Empty the clipboard */
#define COPY2CB_DIB   0x0002    /* Copy DIB data to the clipboard */
#define COPY2CB_DDB   0x0004    /* Copy DDB data to the clipboard */
#define COPY2CB_PALETTE 0x0008  /* Copy palette data to the clipboard */
#define COPY2CB_RGN   0x0010  /* Copy region data to the clipboard */

/*
   flags for L_ConvertColorSpace & L_ClrInit
*/
#define CCS_RGB         0x00    /* Color space is RGB    */
#define CCS_YUV         0x01    /* Color space is YUV    */
#define CCS_CMYK        0x02    /* Color space is CMYK   */
#define CCS_HSV         0x03    /* Color space is HSV    */
#define CCS_HLS         0x04    /* Color space is HLS    */
#define CCS_YIQ         0x05    /* Color space is YIQ    */
#define CCS_CMY         0x06    /* Color space is CMY    */
#define CCS_LAB         0x07    /* Color space is CIELAB */
#define CCS_XYZ         0x08    /* Color space is XYZ    */
#define CCS_YCCK        0x0B    /* Color space is YCCK   */
#define CCS_BGR         0x0C    /* Color space is BGR    */

#define CCS_Y41P        0x0D    /* Color space is Y41P   */
#define CCS_UYVY        0x0E    /* Color space is UYVY   */
#define CCS_YUY2        0x09    /* Color space is YUY2   */
#define CCS_YVU9        0x0A    /* Color space is YVU9   */
#define CCS_YCC         0x0F    /* Color space is YCC    */
#define CCS_RGB16       0x10    /* Color space is RGB    */
#define CCS_YUV16       0x20    /* Color space is YUV    */
#define CCS_YIQ16       0x30    /* Color space is YIQ    */
#define CCS_HSV16       0x40    /* Color space is HSV    */
#define CCS_HLS16       0x50    /* Color space is HLS    */
#define CCS_CMY16       0x60    /* Color space is CMY    */
#define CCS_CMYK16      0x70    /* Color space is CMYK   */

#define CCS_IHS         0x80    /* Color space is IHS    */

/*
   Constants for L_PaintDCBuffer
*/

#define PAINTDC_COMPRESSED          -1

/*
   Types for L_HalftoneBitmap - Moved to LTIMG.H
*/
//
//#define HT_PRINT                  0
//#define HT_VIEW                   1

/*
   flags for L_UnderlayBitmap
*/
#define UB_TILE                      0x00 /* Tile the underlay. */
#define UB_STRETCH                   0x01 /* Stretch the underlay. */

/*
   flags for L_SetDisplayMode
*/
#define DISPLAYMODE_ORDEREDDITHER   0x00000001
#define DISPLAYMODE_FASTPAINT       0x00000002
#define DISPLAYMODE_INDEXEDPAINT    0x00000004
#define DISPLAYMODE_DITHEREDPAINT   0x00000008
#define DISPLAYMODE_SCALETOGRAY     0x00000010
#define DISPLAYMODE_HALFTONEPRINT   0x00000020
#define DISPLAYMODE_FAVORBLACK      0x00000040
#define DISPLAYMODE_FIXEDPALETTE    0x00000080
#define DISPLAYMODE_NETSCAPEPALETTE 0x00000100
#define DISPLAYMODE_RESAMPLE        0x00000200
#define DISPLAYMODE_BICUBIC         0x00000400
//Reserved
//#define DISPLAYMODE_INVALIDATEPAN 0x10000000 
#define DISPLAYMODE_RESETPOSITIONS  0xFFFFFFFF

/*
   playback state constants
*/
#define PLAYSTATE_PRECLEAR    0x0000
#define PLAYSTATE_POSTCLEAR   0x0001
#define PLAYSTATE_PRERENDER   0x0002
#define PLAYSTATE_RENDER      0x0003
#define PLAYSTATE_POSTRENDER  0x0004
#define PLAYSTATE_WAITINPUT   0x0005
#define PLAYSTATE_WAITDELAY   0x0006
#define PLAYSTATE_WAITINPUTDELAY  0x0007
#define PLAYSTATE_PREDISPOSE  0x0008
#define PLAYSTATE_POSTDISPOSE 0x0009
#define PLAYSTATE_END         0x000A

#define PLAYDISPOSE_NONE              0
#define PLAYDISPOSE_LEAVE             1
#define PLAYDISPOSE_RESTOREBACKGROUND 2
#define PLAYDISPOSE_RESTOREPREVIOUS   3

/*
   region processing
*/
#define L_RGN_AND             0
#define L_RGN_SET             1
#define L_RGN_ANDNOTBITMAP    2
#define L_RGN_ANDNOTRGN       3
#define L_RGN_OR              4
#define L_RGN_XOR             5
#define L_RGN_SETNOT          6

#define L_POLY_WINDING        0
#define L_POLY_ALTERNATE      1

#define L_FRAME_MOVING0       0
#define L_FRAME_MOVING1       1
#define L_FRAME_MOVING2       2
#define L_FRAME_MOVING3       3
#define L_FRAME_MOVING4       4
#define L_FRAME_MOVING5       5
#define L_FRAME_MOVING6       6
#define L_FRAME_MOVING7       7

/*
   flags for L_WindowLevel
*/
#define WINDOWLEVEL_PAINT                 0x00
#define WINDOWLEVEL_PAINT_AND_PROCESSING  0x01

#if !defined(_WIN32_WCE)
typedef struct _RGNXFORM
{
   L_UINT uViewPerspective;
   L_INT nXScalarNum;
   L_INT nXScalarDen;
   L_INT nYScalarNum;
   L_INT nYScalarDen;
   L_INT nXOffset;
   L_INT nYOffset;
} RGNXFORM, L_FAR *pRGNXFORM;
#endif

typedef struct _HSVREF
{
   L_UCHAR uH;
   L_UCHAR uS;
   L_UCHAR uV;
   L_UCHAR uReserved;
} HSVREF, L_FAR *pHSVREF;

/*
   constants for nCrosshair in L_StartMagGlass
*/
#define CROSSHAIR_NONE         0
#define CROSSHAIR_FINE         1
#define CROSSHAIR_INVERTPEN    2
#define CROSSHAIR_INVERTSCREEN 3

/*
   constants for uMagGlassFlags in L_StartMagGlass
*/
#define MAGGLASS_MASK_NORMAL        0x0000
#define MAGGLASS_MASK_INVERT        0x0001
#define MAGGLASS_MANUAL_UPDATE      0x0002
#if !defined(_WIN32_WCE)
#define MAGGLASS_MASK_FROM_REGION   0x0004
#endif /* _WIN32_WCE */

/*
   constants for uMagGlassShape in L_UpdateMagGlassShape
*/
#define MAGGLASS_SHAPE_RECT      0
#if !defined(_WIN32_WCE)
#define MAGGLASS_SHAPE_ELLIPSE   1
#endif /* _WIN32_WCE */
#define MAGGLASS_SHAPE_HRGN      2

#if !defined(_WIN32_WCE)
typedef struct tagCurve
{
   L_INT32        nSize;              
   L_INT32        nType;            //RGNCURVE_BEZIER, RGNCURVE_CURVE
   L_INT32        nPointCount;
   POINT         *pPoints;
   L_UINT         uFillMode;
   L_DOUBLE       dTension;       //0.0 to 1.0
   L_INT          nClose;
   L_INT32        nReserved;
} CURVE, L_FAR * pCURVE;


#define CURVE_BEZIER       (0)
#define CURVE_STANDARD     (1)      // Catmull Rom
#define CURVE_NATURAL_CUBIC_SPLINE  (2)

#define CURVE_NO_CLOSE        (0)   //Process only included points -- For n points draw (n-3) segments
#define CURVE_CLOSE           (1)   //For n points draw (n-1) segments
#define CURVE_PARTIAL_CLOSE   (2)   //Repeat first three points -- For n points draw (n) segments
#endif


L_INT EXT_FUNCTION L_AppendPlayback(HPLAYBACK hPlayback,
                                     pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_CancelPlaybackWait(HPLAYBACK hPlayback);

L_INT EXT_FUNCTION L_ChangeFromDDB (HDC hDC,
                                     pBITMAPHANDLE pBitmap,
                                     HBITMAP hBitmap,
                                     HPALETTE hPalette);

HBITMAP EXT_FUNCTION L_ChangeToDDB (HDC hDC,
                                     pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_ClearPlaybackUpdateRect(HPLAYBACK hPlayback);

L_BOOL EXT_FUNCTION L_ClipboardReady (L_VOID);

L_INT EXT_FUNCTION L_ConvertColorSpace (L_UCHAR L_FAR * pBufferSrc,
                                         L_UCHAR L_FAR * pBufferDst,
                                         L_INT nWidth,
                                         L_INT nFormatSrc,
                                         L_INT nFormatDst);

L_INT EXT_FUNCTION L_ConvertFromDDB (HDC hDC,
                                      pBITMAPHANDLE pBitmap,
                                      HBITMAP hBitmap,
                                      HPALETTE hPalette);

HBITMAP EXT_FUNCTION L_ConvertToDDB (HDC hDC,
                                      pBITMAPHANDLE pBitmap);

L_BOOL EXT_FUNCTION L_CopyFromClipboard (HWND hWnd,
                                          pBITMAPHANDLE pBitmap);

L_BOOL EXT_FUNCTION L_CopyToClipboard (HWND hWnd,
                                        pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_CopyToClipboardExt (HWND hWnd,
                                          pBITMAPHANDLE pBitmap,
                                          L_UINT uFlags);

HPALETTE EXT_FUNCTION L_CreatePaintPalette (HDC hDC,
                                             pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_CreatePlayback(pHPLAYBACK phPlayback,
                                    pBITMAPHANDLE pBitmap,
                                    HBITMAPLIST hList);

L_INT EXT_FUNCTION L_DestroyPlayback(HPLAYBACK hPlayback,
                                     pHBITMAPLIST phList);

L_UINT32 EXT_FUNCTION L_GetDisplayMode (L_VOID);


L_INT EXT_FUNCTION L_GetPaintContrast(pBITMAPHANDLE pBitmap);

L_UINT EXT_FUNCTION L_GetPaintGamma(pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_GetPaintIntensity(pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_GetPlaybackDelay(HPLAYBACK hPlayback,
                                      L_UINT32 L_FAR *puDelay);

L_INT EXT_FUNCTION L_GetPlaybackIndex(HPLAYBACK hPlayback,
                                      L_INT L_FAR *pnIndex);

L_INT EXT_FUNCTION L_GetPlaybackState(HPLAYBACK hPlayback,
                                      L_UINT L_FAR *puState);

L_INT EXT_FUNCTION L_GetPlaybackUpdateRect(HPLAYBACK hPlayback,
                                      LPRECT prcUpdate,
                                      L_BOOL fClear);

L_INT EXT_FUNCTION L_PaintDC (HDC hDC,
                               pBITMAPHANDLE pBitmap,
                               LPRECT pSrc,
                               LPRECT pClipSrc,
                               LPRECT pDst,
                               LPRECT pClipDst,
                               L_UINT32 uROP3);

L_INT EXT_FUNCTION L_PaintDCBuffer (HDC hDC,
                                     pBITMAPHANDLE pBitmap,
                                     LPRECT pSrc,
                                     LPRECT pClipSrc,
                                     LPRECT pDst,
                                     LPRECT pClipDst,
                                     L_UINT32 uROP3,
                                     L_UCHAR L_FAR * pBuffer,
                                     L_INT nRow,
                                     L_INT nCount);

L_INT EXT_FUNCTION L_ProcessPlayback(HPLAYBACK hPlayback,
                                     L_UINT L_FAR *puState);

HSVREF EXT_FUNCTION L_RGBtoHSV(COLORREF crColor);

COLORREF EXT_FUNCTION L_HSVtoRGB(HSVREF hsvColor);

L_UINT32 EXT_FUNCTION L_SetDisplayMode (L_UINT32 uFlagPos,
                                         L_UINT32 uFlagSet);

L_INT EXT_FUNCTION L_SetPaintContrast(pBITMAPHANDLE pBitmap, 
                                      L_INT nValue);

L_INT EXT_FUNCTION L_SetPaintGamma(pBITMAPHANDLE pBitmap, 
                                   L_UINT uValue);

L_INT EXT_FUNCTION L_SetPaintIntensity(pBITMAPHANDLE pBitmap, 
                                       L_INT nValue);

L_INT EXT_FUNCTION L_SetPlaybackIndex(HPLAYBACK hPlayback,
                                      L_INT nIndex);

L_INT EXT_FUNCTION L_UnderlayBitmap (pBITMAPHANDLE pBitmapDst,
                                      pBITMAPHANDLE pUnderlay,
                                      L_UINT uFlags);

L_INT EXT_FUNCTION L_ValidatePlaybackLines(HPLAYBACK hPlayback,
                                           L_INT nRow,
                                           L_INT nLines);

L_INT EXT_FUNCTION L_WindowLevel(pBITMAPHANDLE pBitmap,
                                 L_INT nLowBit,
                                 L_INT nHighBit,
                                 L_RGBQUAD L_HUGE*pLUT,
                                 L_UINT32 ulLUTLength,
                                 L_UINT   uFlags);

/* new WindowLevel dialog helper function */
L_INT EXT_FUNCTION L_WindowLevelFillLUT(RGBQUAD L_HUGE* pLUT,
                                        L_UINT32 ulLUTLen,
                                        COLORREF crStart,
                                        COLORREF crEnd,
                                        L_UINT nLow,
                                        L_UINT nHigh,
                                        L_UINT nLowBit,
                                        L_UINT nHighBit,
                                        L_UINT nMinValue,
                                        L_UINT nMaxValue,
                                        L_BOOL bInside);
L_INT EXT_FUNCTION L_WindowLevelFillLUT2(RGBQUAD L_HUGE* pLUT,
                                         L_UINT32 ulLUTLen,
                                         COLORREF crStart,
                                         COLORREF crEnd,
                                         L_UINT nLow,
                                         L_UINT nHigh,
                                         L_UINT nLowBit,
                                         L_UINT nHighBit,
                                         L_UINT nMinValue,
                                         L_UINT nMaxValue,
                                         L_BOOL bInside,
                                         L_UINT32 uFlags);

L_INT EXT_FUNCTION L_GetBitmapClipSegments(pBITMAPHANDLE pBitmap,
                               L_INT nRow,
                               L_UINT L_FAR *pSegmentBuffer,
                               L_UINT L_FAR *puSegmentCount);

L_INT EXT_FUNCTION L_GetBitmapClipSegmentsMax(pBITMAPHANDLE pBitmap,
                               L_UINT L_FAR *puMaxSegments);

typedef L_INT (pEXT_CALLBACK MAGGLASSCALLBACKEXT) (HWND hWnd, 
                                                   L_INT nMaskPlaneStart, 
                                                   L_INT nMaskPlaneEnd, 
                                                   L_UCHAR L_FAR *pMaskPlane, 
                                                   L_INT nMaskPlaneSize, 
                                                   L_VOID L_FAR *pUserData);

typedef L_INT (pEXT_CALLBACK MAGGLASSOWNERDRAWCALLBACK) (HWND hWnd, 
                                                         HDC hMemDC, 
                                                         L_INT32 nXPos,
                                                         L_INT32 nYPos,
                                                         LPRECT pMagGlass,
                                                         L_VOID L_FAR *pUserData);

L_INT EXT_FUNCTION L_StartMagGlass(HWND hWnd, pBITMAPHANDLE pBitmap, RECT L_FAR* prcDst,
                                   L_INT32 nWidth, L_INT32 nHeight,
                                   L_INT nZoom, COLORREF clrPen, HCURSOR hMagCursor,
                                   COLORREF clrBack, L_BOOL bEllipse,
                                   L_INT nBorderSize, L_BOOL b3D,
                                   L_UINT32 uPaintFlags,
                                   COLORREF L_FAR* pMask,
                                   L_UINT uMaskCount,
                                   L_INT nCrosshair,
                                   L_BOOL bIgnoreRgn,
                                   L_BOOL bCenter);

L_INT EXT_FUNCTION L_StartMagGlassExt(HWND hWnd, pBITMAPHANDLE pBitmap, RECT L_FAR* prcDst,
                                      L_INT32 nWidth, L_INT32 nHeight,
                                      L_INT nZoom, COLORREF clrPen, HCURSOR hMagCursor,
                                      COLORREF clrBack, L_BOOL bEllipse,
                                      L_INT nBorderSize, L_BOOL b3D,
                                      L_UINT32 uPaintFlags,
                                      COLORREF L_FAR* pMask,
                                      L_UINT uMaskCount,
                                      L_UINT32 uMagGlassFlags,
                                      L_INT nCrosshair,
                                      L_BOOL bIgnoreRgn,
                                      L_BOOL bCenter,
                                      MAGGLASSCALLBACKEXT pfnCallback,
                                      L_VOID L_FAR* pUserData);

L_INT EXT_FUNCTION L_StopMagGlass(HWND hWnd);

L_INT EXT_FUNCTION L_UpdateMagGlassRect(HWND hWnd, RECT L_FAR* prcDst);

L_INT EXT_FUNCTION L_UpdateMagGlassPaintFlags(HWND hWnd, L_UINT32 uPaintFlags);

L_INT EXT_FUNCTION L_UpdateMagGlassExt(HWND hWnd,
                                       COLORREF L_FAR *pColor,
                                       L_UCHAR L_FAR *pMaskPlane, 
                                       L_INT nMaskPlaneStart,
                                       L_INT nMaskPlaneEnd, 
                                       L_BOOL bUpdateBitmap);

L_INT EXT_FUNCTION L_UpdateMagGlassBitmap(HWND hWnd, 
                                          pBITMAPHANDLE pBitmap, 
                                          L_BOOL bUpdateBitmap);

L_BOOL EXT_FUNCTION L_WindowHasMagGlass(HWND hWnd);

L_INT EXT_FUNCTION L_SetMagGlassOwnerDrawCallback(HWND hWnd,
                                                  MAGGLASSOWNERDRAWCALLBACK pfnCallback,
                                                  L_VOID L_FAR* pUserData);

typedef struct tag_MagGlassPaintOptions
{
   L_INT nContrast;
   L_INT nGamma;
   L_INT nIntensity;
} MAGGLASSPAINTOPTIONS, L_FAR* pMAGGLASSPAINTOPTIONS;

L_INT EXT_FUNCTION L_SetMagGlassPaintOptions(HWND hWnd, 
                                             pMAGGLASSPAINTOPTIONS pMagGlassPaintOptions);

L_INT EXT_FUNCTION L_ShowMagGlass(HWND hWnd, L_BOOL bShowMagGlass);

L_INT EXT_FUNCTION L_SetMagGlassPos(HWND hWnd, L_INT xPos, L_INT yPos);

L_INT EXT_FUNCTION L_UpdateMagGlassShape(HWND hWnd, L_UINT32 uMagGlassShape, HRGN hMagGlassRgn);

/* these functions not ported to Windows CE */
#if !defined(_WIN32_WCE)
HDC EXT_FUNCTION L_PrintBitmap (pBITMAPHANDLE pBitmap,
                                 L_INT nX,
                                 L_INT nY,
                                 L_INT nWidth,
                                 L_INT nHeight,
                                 L_BOOL fEndDoc);

HDC EXT_FUNCTION L_PrintBitmapExt (HDC hDC,
                                    pBITMAPHANDLE pBitmap,
                                    L_INT nX,
                                    L_INT nY,
                                    L_INT nWidth,
                                    L_INT nHeight,
                                    L_BOOL fEndDoc);

HDC EXT_FUNCTION L_PrintBitmapFast (HDC hDC,
                                     pBITMAPHANDLE pBitmap,
                                     L_INT nX,
                                     L_INT nY,
                                     L_INT nWidth,
                                     L_INT nHeight,
                                     L_BOOL fEndDoc);

L_INT EXT_FUNCTION L_ScreenCaptureBitmap (HDC hDC,
                                           pBITMAPHANDLE pBitmap,
                                           LPRECT pRect);

L_BOOL EXT_FUNCTION L_BitmapHasRgn(pBITMAPHANDLE pBitmap);
L_INT EXT_FUNCTION L_CreateMaskFromBitmapRgn(pBITMAPHANDLE pBitmap,
                                     pBITMAPHANDLE pMask);
L_INT EXT_FUNCTION L_CurveToBezier(pCURVE pCurve, L_INT *pOutPointCount, POINT *OutPoint);
L_INT EXT_FUNCTION L_FrameBitmapRgn(HDC hDC,
                                       pBITMAPHANDLE pBitmap,
                                       pRGNXFORM pXForm,
                                       L_UINT uType);

L_INT EXT_FUNCTION L_ColorBitmapRgn(HDC hDC, 
                                    pBITMAPHANDLE pBitmap, 
                                    pRGNXFORM pXForm, 
                                    COLORREF crRgnColor);

L_INT EXT_FUNCTION L_FreeBitmapRgn(pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_GetBitmapRgnArea(pBITMAPHANDLE pBitmap,
                                       L_UINT32 L_FAR *puArea);

L_INT EXT_FUNCTION L_GetBitmapRgnBounds(pBITMAPHANDLE pBitmap,
                                       pRGNXFORM pXForm,
                                       RECT L_FAR *pRect);

L_INT EXT_FUNCTION L_GetBitmapRgnHandle(pBITMAPHANDLE pBitmap,
                                       pRGNXFORM pXForm,
                                       HRGN L_FAR *phRgn);
L_BOOL EXT_FUNCTION L_IsPtInBitmapRgn(pBITMAPHANDLE pBitmap,
                                       L_INT nRow,
                                       L_INT nCol);

L_INT EXT_FUNCTION L_OffsetBitmapRgn(pBITMAPHANDLE pBitmap,
                                       L_INT nRowOffset,
                                       L_INT nColOffset);
L_INT EXT_FUNCTION L_PaintRgnDC (HDC hDC,
                                       pBITMAPHANDLE pBitmap,
                                       LPRECT pSrc,
                                       LPRECT pClipSrc,
                                       LPRECT pDst,
                                       LPRECT pClipDst,
                                       L_UINT32 uROP3);

L_INT EXT_FUNCTION L_PaintRgnDCBuffer (HDC hDC,
                                       pBITMAPHANDLE pBitmap,
                                       LPRECT pSrc,
                                       LPRECT pClipSrc,
                                       LPRECT pDst,
                                       LPRECT pClipDst,
                                       L_UINT32 uROP3,
                                       L_UCHAR L_FAR * pBuffer,
                                       L_INT nRow,
                                       L_INT nCount);

L_INT EXT_FUNCTION L_SetBitmapRgnColor(pBITMAPHANDLE pBitmap,
                                       COLORREF crColor,
                                       L_UINT uCombineMode);

L_INT EXT_FUNCTION L_SetBitmapRgnColorHSVRange(pBITMAPHANDLE pBitmap, 
                                               HSVREF hsvLower, 
                                               HSVREF hsvUpper, 
                                               L_UINT uCombineMode);

L_INT EXT_FUNCTION L_SetBitmapRgnColorRGBRange(pBITMAPHANDLE pBitmap, 
                                               COLORREF crLower, 
                                               COLORREF crUpper, 
                                               L_UINT uCombineMode);
L_INT EXT_FUNCTION L_SetBitmapRgnMagicWand(pBITMAPHANDLE pBitmap,
                                           L_INT x, L_INT y,
                                           L_UCHAR uTolerance,
                                           L_UINT uCombineMode);

L_INT EXT_FUNCTION L_SetBitmapRgnEllipse(pBITMAPHANDLE pBitmap,
                                       pRGNXFORM pXForm,
                                       RECT L_FAR *pRect,
                                       L_UINT uCombineMode);

L_INT EXT_FUNCTION L_SetBitmapRgnFromMask(pBITMAPHANDLE pBitmap,
                                    pRGNXFORM pXForm,
                                    pBITMAPHANDLE pMask,
                                    L_UINT uCombineMode);

L_INT EXT_FUNCTION L_SetBitmapRgnHandle(pBITMAPHANDLE pBitmap,
                                       pRGNXFORM pXForm,
                                       HRGN hRgn,
                                       L_UINT uCombineMode);

L_INT EXT_FUNCTION L_SetBitmapRgnPolygon(pBITMAPHANDLE pBitmap,
                                       pRGNXFORM pXForm,
                                       POINT L_FAR *pPoints,
                                       L_UINT uPoints,
                                       L_UINT uFillMode,
                                       L_UINT uCombineMode);

L_INT EXT_FUNCTION L_SetBitmapRgnRect(pBITMAPHANDLE pBitmap,
                                       pRGNXFORM pXForm,
                                       RECT L_FAR *pRect,
                                       L_UINT uCombineMode);

L_INT EXT_FUNCTION L_SetBitmapRgnRoundRect(pBITMAPHANDLE pBitmap,
                                       pRGNXFORM pXForm,
                                       RECT L_FAR *pRect,
                                       L_INT nWidthEllipse,
                                       L_INT nHeightEllipse,
                                       L_UINT uCombineMode);

L_INT EXT_FUNCTION L_SetBitmapRgnCurve(pBITMAPHANDLE pBitmap, 
                                       pRGNXFORM pXForm, 
                                       pCURVE pCurve, 
                                       L_UINT uCombineMode);

/* Pan Window */
/* PanWindow Callback function */
typedef L_VOID (pEXT_CALLBACK PANWNDCALLBACK) (HWND, HWND, L_UINT, LPRECT, L_VOID L_FAR *);

/* flags for PanWindow Callback */
#define PANWIN_CREATED   0
#define PANWIN_UPDATED   1
#define PANWIN_DESTROYED 2
#define PANWIN_MOVED     3
#define PANWIN_REPAINTED 4

/* exported functions */
L_INT EXT_FUNCTION L_CreatePanWindow(HWND hWndParent, pBITMAPHANDLE pBitmap,
                                     L_UINT32 ulDisplayFlags,
                                     L_INT nLeft, L_INT nTop,
                                     L_INT nWidth, L_INT nHeight,
                                     L_TCHAR L_FAR* pszClassName,
                                     HICON hIcon, HCURSOR hCursor,
                                     L_BOOL bSysMenu,
                                     PANWNDCALLBACK pfnPanCallback,
                                     L_VOID L_FAR* pUserData );

#define DISPLAYMODE_INVALIDATEPAN    0x10000000 
L_INT EXT_FUNCTION L_UpdatePanWindow(HWND hPanWindow,
                                     pBITMAPHANDLE pBitmap,
                                     L_UINT32 ulDisplayFlags,
                                     COLORREF crPen,
                                     L_TCHAR L_FAR* pszTitle,
                                     LPRECT prcDst );

L_INT EXT_FUNCTION L_DestroyPanWindow( HWND hPanWindow );

L_INT EXT_FUNCTION L_GetBitmapRgnData(pBITMAPHANDLE pBitmap, pRGNXFORM pXForm, L_INT nDataSize, L_VOID L_FAR* pData);

L_INT EXT_FUNCTION L_SetBitmapRgnData(pBITMAPHANDLE pBitmap, pRGNXFORM pXForm, L_INT nDataSize, L_VOID L_FAR* pData, L_UINT uCombineMode);

/* Sets the bitmap region clipping flag */
L_INT EXT_FUNCTION L_SetBitmapRgnClip (pBITMAPHANDLE pBitmap, 
                                       L_BOOL bClip);

/* Gets the bitmap region clipping flag */
L_INT EXT_FUNCTION L_GetBitmapRgnClip (pBITMAPHANDLE pBitmap, 
                                       L_BOOL L_FAR*pbClip);

/* Gets the bitmap region bounds clipped to the bitmap size */
L_INT EXT_FUNCTION L_GetBitmapRgnBoundsClip(pBITMAPHANDLE pBitmap, 
                                        pRGNXFORM pXForm, 
                                        RECT L_FAR *pRect);

L_INT EXT_FUNCTION L_ConvertFromWMF(pBITMAPHANDLE pBitmap, 
                                    HMETAFILE hWmf, 
                                    L_UINT uWidth, 
                                    L_UINT uHeight);

L_INT EXT_FUNCTION L_ChangeFromWMF(pBITMAPHANDLE pBitmap, 
                                   HMETAFILE hWmf, 
                                   L_UINT uWidth, 
                                   L_UINT uHeight);

HMETAFILE EXT_FUNCTION L_ConvertToWMF(pBITMAPHANDLE pBitmap);

HMETAFILE EXT_FUNCTION L_ChangeToWMF(pBITMAPHANDLE pBitmap);

L_INT EXT_FUNCTION L_ConvertFromEMF(pBITMAPHANDLE pBitmap, 
                                    HENHMETAFILE hWmf, 
                                    L_UINT uWidth, 
                                    L_UINT uHeight);

L_INT EXT_FUNCTION L_ChangeFromEMF(pBITMAPHANDLE pBitmap, 
                                   HENHMETAFILE hWmf, 
                                   L_UINT uWidth, 
                                   L_UINT uHeight);

HENHMETAFILE EXT_FUNCTION L_ConvertToEMF(pBITMAPHANDLE pBitmap);

HENHMETAFILE EXT_FUNCTION L_ChangeToEMF(pBITMAPHANDLE pBitmap);
#endif /* _WIN32_WCE */

#undef _HEADER_ENTRY_
#include "ltpck.h"

#endif                          /* _LTDIS_H_ */
