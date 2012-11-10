/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : tcprnt.h                                                        |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_FUNCTIONS_TYPEDEFINES_H_
#define  _LEAD_FUNCTIONS_TYPEDEFINES_H_

/*----------------------------------------------------------------------------+
| MACROS                                                                      |
+----------------------------------------------------------------------------*/
#ifdef USE_POINTERS_TO_LEAD_FUNCTIONS

//-----------------------------------------------------------------------------
//--LTKRN.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------

typedef L_VOID ( pEXT_FUNCTION pL_ACCESSBITMAP )(pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_ALLOCATEBITMAP )(pBITMAPHANDLE pBitmap,
                                      L_INT nMemoryType);

typedef L_INT ( pEXT_FUNCTION pL_CHANGEBITMAPHEIGHT )(pBITMAPHANDLE pBitmap,
                                          L_INT nHeight);

typedef L_INT ( pEXT_FUNCTION pL_CHANGEBITMAPVIEWPERSPECTIVE)(pBITMAPHANDLE pDstBitmap,
                                          pBITMAPHANDLE pSrcBitmap,
                                          L_INT   ViewPerspective);

typedef L_INT ( pEXT_FUNCTION pL_CHANGEFROMDIB )(pBITMAPHANDLE pBitmap,
                                     HGLOBAL hDIB);

typedef HGLOBAL ( pEXT_FUNCTION pL_CHANGETODIB )(pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_CLEARBITMAP )(pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_CLEARNEGATIVEPIXELS)( pBITMAPHANDLE pBitmap );

typedef L_INT ( pEXT_FUNCTION pL_COLORRESBITMAP )(pBITMAPHANDLE pBitmapSrc,
                                      pBITMAPHANDLE pBitmapDst,
                                      L_INT nBitsPerPixel,
                                      L_UINT32 uFlags,
                                      LPRGBQUAD pPalette,
                                      HPALETTE hPalette,
                                      L_UINT uColors,
                                      COLORRESCALLBACK pfnCallback,
                                      L_VOID L_FAR * pUserData);

typedef L_INT ( pEXT_FUNCTION pL_COLORRESBITMAPLIST )(HBITMAPLIST hList,
                                      L_INT nBitsPerPixel,
                                      L_UINT32 uFlags,
                                      LPRGBQUAD pPalette,
                                      HPALETTE hPalette,
                                      L_UINT uColors);

typedef L_INT ( pEXT_FUNCTION pL_COMBINEBITMAP )(pBITMAPHANDLE pBitmapDst,
                                     L_INT nXDst,
                                     L_INT nYDst,
                                     L_INT nWidth,
                                     L_INT nHeight,
                                     pBITMAPHANDLE pBitmapSrc,
                                     L_INT nXSrc,
                                     L_INT nYSrc,
                                     L_UINT32 uFlags);

typedef L_INT ( pEXT_FUNCTION pL_COMBINEBITMAPWARP )(pBITMAPHANDLE pBitmapDst,
                                     POINT         nDst[],
                                     pBITMAPHANDLE pBitmapSrc,
                                     POINT         nSrc,
                                     L_INT         nSrcWidth,
                                     L_INT         nSrcHeight,
                                     L_UINT32      uFlags);

typedef L_INT ( pEXT_FUNCTION pL_COMPRESSROW)( L_UINT16 L_HUGE * pRunBuffer,
                                  L_UCHAR L_HUGE * pBuffer,
                                  L_INT nCol,
                                  L_INT nWidth);

typedef L_INT ( pEXT_FUNCTION pL_COMPRESSROWS)(  L_UINT16 L_HUGE*pRunBuffer,
                                    L_UCHAR L_HUGE*pBuffer,
                                    L_UINT nWidth,
                                    L_UINT nRows);

typedef L_INT ( pEXT_FUNCTION pL_CONVERTBUFFER )(L_UCHAR L_FAR * pBuffer,
                                     L_INT nWidth,
                                     L_INT nBitsPerPixelSrc,
                                     L_INT nBitsPerPixelDst,
                                     L_INT nOrderSrc,
                                     L_INT nOrderDst,
                                     LPRGBQUAD pPaletteSrc,
                                     LPRGBQUAD pPaletteDst);

typedef L_INT ( pEXT_FUNCTION pL_CONVERTBUFFEREXT )(L_UCHAR L_FAR * pBuffer,
                                     L_INT nWidth,
                                     L_INT nBitsPerPixelSrc,
                                     L_INT nBitsPerPixelDst,
                                     L_INT nOrderSrc,
                                     L_INT nOrderDst,
                                     LPRGBQUAD pPaletteSrc,
                                     LPRGBQUAD pPaletteDst,
                                     L_UINT  uFlags,
                                     L_INT   uLowBit,
                                     L_INT   uHighBit);

typedef L_INT ( pEXT_FUNCTION pL_CONVERTFROMDIB )(pBITMAPHANDLE pBitmap,
                                      BITMAPINFO L_FAR * pInfo,
                                      L_UCHAR L_FAR * pBits);

typedef HGLOBAL ( pEXT_FUNCTION pL_CONVERTTODIB )(pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_COPYBITMAP )(pBITMAPHANDLE pBitmapDst,
                                  pBITMAPHANDLE pBitmapSrc);

typedef L_INT ( pEXT_FUNCTION pL_COPYBITMAPDATA )(pBITMAPHANDLE pBitmapDst,
                                      pBITMAPHANDLE pBitmapSrc);

typedef L_VOID ( pEXT_FUNCTION pL_COPYBITMAPHANDLE )(pBITMAPHANDLE pBitmapDst,
                                         pBITMAPHANDLE pBitmapSrc);

typedef L_INT ( pEXT_FUNCTION pL_COPYBITMAPLISTITEMS)(pHBITMAPLIST phList,
                                        HBITMAPLIST hList,
                                        L_UINT uIndex,
                                        L_UINT uCount);

typedef L_INT ( pEXT_FUNCTION pL_COPYBITMAPRECT )(pBITMAPHANDLE pBitmapDst,
                                      pBITMAPHANDLE pBitmapSrc,
                                      L_INT nCol,
                                      L_INT nRow,
                                      L_UINT uWidth,
                                      L_UINT uHeight);

typedef L_INT ( pEXT_FUNCTION pL_CREATEBITMAP )(pBITMAPHANDLE pBitmap,
                                    L_UINT uMemory,
                                    L_UINT uWidth,
                                    L_UINT uHeight,
                                    L_UINT uBitsPerPixel,
                                    L_UINT uOrder,
                                    LPRGBQUAD pPalette,
                                    L_UINT uViewPerspective,
                                    L_UCHAR L_FAR*pData,
                                    L_UINT32 dwSize);

typedef L_INT ( pEXT_FUNCTION pL_CREATEBITMAPLIST)(pHBITMAPLIST phList);

typedef HDC ( pEXT_FUNCTION pL_CREATELEADDC )(pBITMAPHANDLE pBitmap);

typedef L_UINT L_FAR *( pEXT_FUNCTION pL_CREATEUSERMATCHTABLE )(LPRGBQUAD pPalette,
                                                    L_UINT uColors);

typedef L_INT ( pEXT_FUNCTION pL_DEFAULTDITHERING )(L_UINT uMethod);

typedef L_INT ( pEXT_FUNCTION pL_DELETEBITMAPLISTITEMS)(HBITMAPLIST hList,
                                           L_UINT uIndex,
                                           L_UINT uCount);

typedef L_INT ( pEXT_FUNCTION pL_DESTROYBITMAPLIST)(HBITMAPLIST hList);

typedef L_BOOL ( pEXT_FUNCTION pL_DELETELEADDC )(HDC hDC);

typedef L_INT ( pEXT_FUNCTION pL_DITHERLINE )(pBITMAPHANDLE pBitmap,
                                  L_UCHAR L_FAR * pBufferSrc,
                                  L_UCHAR L_FAR * pBufferDst);

typedef HPALETTE ( pEXT_FUNCTION pL_DUPPALETTE )(HPALETTE hPalette);
typedef HPALETTE ( pEXT_FUNCTION pL_DUPBITMAPPALETTE )(pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_EXPANDROW)(L_UINT16 L_HUGE * pRunBuffer, 
                               L_UCHAR L_HUGE * pBuffer, 
                               L_UINT nCol, 
                               L_INT nWidth);

typedef L_INT ( pEXT_FUNCTION pL_EXPANDROWS)( L_UINT16 L_HUGE *pRun, 
                                 L_UCHAR L_HUGE*pBuffer, 
                                 L_UINT nWidth, 
                                 L_UINT nRows);

typedef L_INT ( pEXT_FUNCTION pL_FILLBITMAP )(pBITMAPHANDLE pBitmap,
                                  COLORREF crFill);

typedef L_INT ( pEXT_FUNCTION pL_FLIPBITMAP )(pBITMAPHANDLE pBitmap);

typedef L_VOID ( pEXT_FUNCTION pL_FREEBITMAP )(pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_FREEUSERMATCHTABLE )(L_UINT L_FAR * pTable);

typedef L_INT ( pEXT_FUNCTION pL_GETBITMAPALPHA )(pBITMAPHANDLE pBitmap,
                                     pBITMAPHANDLE pAlpha);

typedef L_INT ( pEXT_FUNCTION pL_GETBITMAPCOLORS )(pBITMAPHANDLE pBitmap,
                                       L_INT nIndex,
                                       L_INT nCount,
                                       LPRGBQUAD pPalette);

typedef L_INT ( pEXT_FUNCTION pL_GETBITMAPLISTCOUNT)(HBITMAPLIST hList,
                                           L_UINT L_FAR *puCount);

typedef L_INT ( pEXT_FUNCTION pL_GETBITMAPLISTITEM)(HBITMAPLIST hList,
                                       L_UINT uIndex,
                                       pBITMAPHANDLE pBitmap);

typedef L_INT32 ( pEXT_FUNCTION pL_GETBITMAPROW )(pBITMAPHANDLE pBitmap,
                                      L_UCHAR L_FAR * pBuffer,
                                      L_INT nRow,
                                      L_UINT32 uBytes);

typedef L_INT32 ( pEXT_FUNCTION pL_GETBITMAPROWCOL )(pBITMAPHANDLE pBitmap,
                                         L_UCHAR L_FAR * pBuffer,
                                         L_INT nRow,
                                         L_INT nCol,
                                         L_UINT32 uBytes);

typedef L_INT32 ( pEXT_FUNCTION pL_GETBITMAPROWCOLCOMPRESSED )(pBITMAPHANDLE pBitmap,
                                         L_UCHAR L_FAR * pWorkBuffer,
                                         L_UINT16 L_FAR * pRunBuffer,
                                         L_INT nRow,
                                         L_INT nCol,
                                         L_UINT32 uWidth);

typedef L_INT ( pEXT_FUNCTION pL_GETBITMAPROWCOMPRESSED )(pBITMAPHANDLE pBitmap,
                                         L_UCHAR L_FAR * pWorkBuffer,
                                         L_UINT16 L_FAR * pRunBuffer,
                                         L_UINT nRow,
                                         L_UINT nLines);

typedef L_INT ( pEXT_FUNCTION pL_GETFIXEDPALETTE )(LPRGBQUAD pPalette,
                                       L_INT nBitsPerPixel);

typedef COLORREF ( pEXT_FUNCTION pL_GETPIXELCOLOR )(pBITMAPHANDLE pBitmap,
                                        L_INT nRow,
                                        L_INT nCol);

typedef STATUSCALLBACK ( pEXT_FUNCTION pL_GETSTATUSCALLBACK )(L_VOID L_FAR* L_FAR*ppUserData);

typedef L_INT ( pEXT_FUNCTION pL_GRAYSCALEBITMAP )(pBITMAPHANDLE pBitmap,
                                      L_INT nBitsPerPixel);

typedef L_INT ( pEXT_FUNCTION pL_INITBITMAP )(pBITMAPHANDLE pBitmap,
                                  L_INT nWidth,
                                  L_INT nHeight,
                                  L_INT nBitsPerPixel);

typedef L_INT ( pEXT_FUNCTION pL_INSERTBITMAPLISTITEM)(HBITMAPLIST hList,
                                           L_UINT uIndex,
                                           pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_ISGRAYSCALEBITMAP )(pBITMAPHANDLE pBitmap);

typedef L_BOOL ( pEXT_FUNCTION pL_ISSUPPORTLOCKED )(L_UINT uType);

typedef L_INT ( pEXT_FUNCTION pL_POINTFROMBITMAP)(pBITMAPHANDLE pBitmap, 
                                     L_INT ViewPerspective, 
                                     L_INT L_FAR*px, 
                                     L_INT L_FAR*py);

typedef L_INT ( pEXT_FUNCTION pL_POINTTOBITMAP)(pBITMAPHANDLE pBitmap,
                                   L_INT ViewPerspective,
                                   L_INT L_FAR*px,
                                   L_INT L_FAR*py);

typedef L_INT ( pEXT_FUNCTION pL_PUTBITMAPCOLORS )(pBITMAPHANDLE pBitmap,
                                       L_INT nIndex,
                                       L_INT nCount,
                                       LPRGBQUAD pPalette);

typedef L_INT32 ( pEXT_FUNCTION pL_PUTBITMAPROW )(pBITMAPHANDLE pBitmap,
                                      L_UCHAR L_FAR * pBuffer,
                                      L_INT nRow,
                                      L_UINT32 uBytes);

typedef L_INT32 ( pEXT_FUNCTION pL_PUTBITMAPROWCOL )(pBITMAPHANDLE pBitmap,
                                         L_UCHAR L_FAR * pBuffer,
                                         L_INT nRow,
                                         L_INT nCol,
                                         L_UINT32 uBytes);

typedef L_INT32 ( pEXT_FUNCTION pL_PUTBITMAPROWCOLCOMPRESSED )(pBITMAPHANDLE pBitmap,
                                         L_UCHAR L_FAR * pWorkBuffer,
                                         L_UINT16 L_FAR * pRunBuffer,
                                         L_INT nRow,
                                         L_INT nCol,
                                         L_UINT32 uWidth);

typedef L_INT ( pEXT_FUNCTION pL_PUTBITMAPROWCOMPRESSED )(pBITMAPHANDLE pBitmap,
                                         L_UCHAR L_FAR * pWorkBuffer,
                                         L_UINT16 L_FAR * pRunBuffer,
                                         L_UINT nRow,
                                         L_UINT nLines);

typedef L_INT ( pEXT_FUNCTION pL_PUTPIXELCOLOR )(pBITMAPHANDLE pBitmap,
                                     L_INT nRow,
                                     L_INT nCol,
                                     COLORREF crColor);

typedef L_INT ( pEXT_FUNCTION pL_RECTFROMBITMAP)(pBITMAPHANDLE pBitmap, 
                                    L_INT ViewPerspective,
                                    LPRECT lprc);

typedef L_INT ( pEXT_FUNCTION pL_RECTTOBITMAP)(  pBITMAPHANDLE pBitmap, 
                                    L_INT nViewPerspective,
                                    LPRECT lprc);

typedef L_VOID ( pEXT_FUNCTION pL_REDIRECTIO )(REDIRECTOPEN pfnOpen,
                                   REDIRECTREAD pfnRead,
                                   REDIRECTWRITE pfnWrite,
                                   REDIRECTSEEK pfnSeek,
                                   REDIRECTCLOSE pfnClose,
                                   L_VOID L_FAR* pUserData);

typedef L_VOID ( pEXT_FUNCTION pL_RELEASEBITMAP )(pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_REMOVEBITMAPLISTITEM)(HBITMAPLIST hList,
                                           L_UINT uIndex,
                                           pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_RESIZE )(L_UCHAR L_FAR * pBuffer,
                              L_INT nRow,
                              L_INT nBitsPerPixel,
                              L_INT L_FAR * pXSize,
                              L_INT L_FAR * pYSize,
                              L_VOID L_FAR * pResizeData);

typedef L_INT ( pEXT_FUNCTION pL_RESIZEBITMAP )(pBITMAPHANDLE pBitmapSrc,
                                    pBITMAPHANDLE pBitmapDst);

typedef L_INT ( pEXT_FUNCTION pL_REVERSEBITMAP )(pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_ROTATEBITMAP )(pBITMAPHANDLE pBitmap,
                                        L_INT32 nAngle,
                                        L_UINT uFlags,
                                        COLORREF crFill);

typedef L_INT ( pEXT_FUNCTION pL_ROTATEBITMAPVIEWPERSPECTIVE )(pBITMAPHANDLE pBitmap,
                                   L_INT nAngle);

typedef L_INT ( pEXT_FUNCTION pL_SETBITMAPALPHA )(pBITMAPHANDLE pBitmap,
                                     pBITMAPHANDLE pAlpha);

typedef L_INT ( pEXT_FUNCTION pL_SETBITMAPDATAPOINTER )(pBITMAPHANDLE pBitmap, 
                                           L_UCHAR L_FAR*pData, 
                                           L_UINT32 dwSize);

typedef L_INT ( pEXT_FUNCTION pL_SETBITMAPLISTITEM)(HBITMAPLIST hList,
                                           L_UINT uIndex,
                                           pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_SETHOTKEYCALLBACK)(L_INT nHotKey, 
                                       L_UINT uHotKeyModifiers, 
                                       HOTKEYCALLBACK pfnHotKeyCallback, 
                                       L_VOID L_FAR* pUserData);

typedef STATUSCALLBACK ( pEXT_FUNCTION pL_SETSTATUSCALLBACK )(STATUSCALLBACK pfnCallback, 
                                                 L_VOID L_FAR*pUserData);

typedef L_UINT L_FAR *( pEXT_FUNCTION pL_SETUSERMATCHTABLE )(L_UINT L_FAR * pTable);

typedef L_INT ( pEXT_FUNCTION pL_SHEARBITMAP )(pBITMAPHANDLE pBitmap,
                                   L_INT nAngle,
                                   L_BOOL fHorizontal,
                                   COLORREF crFill);

typedef L_INT ( pEXT_FUNCTION pL_SIZEBITMAP)(pBITMAPHANDLE pBitmap,
                                    L_INT nWidth,
                                    L_INT nHeight,
                                    L_UINT32 uFlags);

typedef L_INT ( pEXT_FUNCTION pL_STARTDITHERING )(pBITMAPHANDLE pBitmap,
                                      LPRGBQUAD pPalette,
                                      L_UINT uColors);

typedef L_INT ( pEXT_FUNCTION pL_STARTRESIZE )(L_INT nOldWidth,
                                   L_INT nOldHeight,
                                   L_INT nNewWidth,
                                   L_INT nNewHeight,
                                   L_VOID L_FAR * L_FAR * ppResizeData);

typedef L_INT ( pEXT_FUNCTION pL_STOPDITHERING )(pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_STOPRESIZE )(L_VOID L_FAR * pResizeData);

typedef COLORREF ( pEXT_FUNCTION pL_TRANSLATEBITMAPCOLOR)(pBITMAPHANDLE pBitmapDst,
                                             pBITMAPHANDLE pBitmapSrc,
                                             COLORREF crColor);

typedef L_INT ( pEXT_FUNCTION pL_TOGGLEBITMAPCOMPRESSION)(pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_TRIMBITMAP )( pBITMAPHANDLE pBitmap,
                                      L_INT nCol,
                                      L_INT nRow,
                                      L_UINT uWidth,
                                      L_UINT uHeight);

typedef L_VOID ( pEXT_FUNCTION pL_UNLOCKSUPPORT )(L_UINT uType, L_CHAR L_FAR * pKey);

typedef L_INT ( pEXT_FUNCTION pL_VERSIONINFO )(pVERSIONINFO pVersionInfo);

typedef L_INT ( pEXT_FUNCTION pL_FLIPBITMAPVIEWPERSPECTIVE)(pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_REVERSEBITMAPVIEWPERSPECTIVE)(pBITMAPHANDLE pBitmap);

typedef L_INT (pEXT_CALLBACK RESIZECALLBACK) (pBITMAPHANDLE, L_UCHAR L_FAR *, L_INT, L_INT, L_UINT32, L_VOID L_FAR *);

typedef L_INT ( pEXT_FUNCTION pL_STARTRESIZEBITMAP)(pBITMAPHANDLE pBitmap, 
                                       L_INT nNewWidth, 
                                       L_INT nNewHeight, 
                                       L_INT nNewBits,
                                       LPRGBQUAD pPalette, 
                                       L_INT nColors, 
                                       L_UINT32 uFlags, 
                                       RESIZECALLBACK pfnCallback, 
                                       L_VOID L_FAR*pCallbackData, 
                                       L_VOID L_FAR*L_FAR*ppResizeData);

typedef L_INT ( pEXT_FUNCTION pL_GETRESIZEDROWCOL)(L_VOID L_FAR*pResizeData, 
                                      L_UCHAR L_FAR*pBuffer,
                                      L_INT nRow,
                                      L_INT nCol,
                                      L_INT32 uBytes);

typedef L_INT ( pEXT_FUNCTION pL_STOPRESIZEBITMAP)(L_VOID L_FAR*pResizeData);

typedef L_INT ( pEXT_FUNCTION pL_MOVEBITMAPLISTITEMS)(pHBITMAPLIST phList,
                                        HBITMAPLIST hList,
                                        L_UINT uIndex,
                                        L_UINT uCount);

typedef L_INT (pEXT_FUNCTION pL_GETPIXELDATA) (pBITMAPHANDLE pBitmap, L_VOID * pData, L_INT nRow, L_INT nCol, L_INT nBytes);

typedef L_INT (pEXT_FUNCTION pL_PUTPIXELDATA) (pBITMAPHANDLE pBitmap, L_VOID * pData, L_INT nRow, L_INT nCol, L_INT nBytes);

typedef L_INT (pEXT_FUNCTION pL_CHANGEBITMAPCOMPRESSION) (pBITMAPHANDLE pBitmap, L_INT nComp);

typedef L_INT (pEXT_FUNCTION pL_CREATEBITMAPLISTOPTPAL)(HBITMAPLIST hList,
                                 LPRGBQUAD pPalette,
                                 L_UINT L_FAR *puColors,
                                 L_UINT L_FAR * L_FAR * ppMatchTable,
                                 L_BOOL L_FAR*pbGenerated);


typedef L_INT (pEXT_FUNCTION pL_SETBITMAPPALETTE)(pBITMAPHANDLE pBitmap,HPALETTE hPalette);




//-----------------------------------------------------------------------------
//--LTIMG.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------

typedef L_INT ( pEXT_FUNCTION pL_ADDBITMAPNOISE )(pBITMAPHANDLE pBitmap,
                                      L_UINT uRange,
                                      L_UINT uChannel);

typedef L_INT ( pEXT_FUNCTION pL_AUTOTRIMBITMAP)(pBITMAPHANDLE pBitmap,
                                     L_UINT uThreshold);

typedef L_INT ( pEXT_FUNCTION pL_AVERAGEFILTERBITMAP )(pBITMAPHANDLE pBitmap,
                                           L_UINT uDim);

typedef L_INT ( pEXT_FUNCTION pL_BINARYFILTERBITMAP )(pBITMAPHANDLE pBitmap,
                                          LPBINARYFLT pFilter);

typedef L_INT ( pEXT_FUNCTION pL_CHANGEBITMAPCONTRAST )(pBITMAPHANDLE pBitmap,
                                            L_INT nChange);

typedef L_INT ( pEXT_FUNCTION pL_CHANGEBITMAPHUE )(pBITMAPHANDLE pBitmap,
                                       L_INT nAngle);

typedef L_INT ( pEXT_FUNCTION pL_CHANGEBITMAPINTENSITY )(pBITMAPHANDLE pBitmap,
                                             L_INT nChange);

typedef L_INT ( pEXT_FUNCTION pL_CHANGEBITMAPSATURATION )(pBITMAPHANDLE pBitmap,
                                              L_INT nChange);

typedef L_INT ( pEXT_FUNCTION pL_COLORMERGEBITMAP )(pBITMAPHANDLE pBitmap,
                                        pBITMAPHANDLE L_FAR * ppBitmap,
                                        L_UINT32 uFlags);

typedef L_INT ( pEXT_FUNCTION pL_COLORSEPARATEBITMAP )(pBITMAPHANDLE pBitmap,
                                           pBITMAPHANDLE L_FAR * ppBitmap,
                                           L_UINT32 uFlags);

typedef L_INT ( pEXT_FUNCTION pL_DESKEWBITMAP )(pBITMAPHANDLE pBitmap,
                                   L_INT32 L_FAR *pnAngle);

typedef L_INT ( pEXT_FUNCTION pL_DESPECKLEBITMAP )(pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_SMOOTHBITMAP )( pBITMAPHANDLE pBitmap, 
                                    LPSMOOTH pSmooth,
                                    SMOOTHCALLBACK pfnCallback,
                                    L_VOID L_FAR * pUserData);


typedef L_INT ( pEXT_FUNCTION pL_LINEREMOVEBITMAP)(   pBITMAPHANDLE pBitmap,
                                         LPLINEREMOVE pLineRemove,
                                         LINEREMOVECALLBACK pfnCallback,
                                         L_VOID L_FAR * pUserData);

typedef L_INT ( pEXT_FUNCTION pL_BORDERREMOVEBITMAP)(   pBITMAPHANDLE pBitmap, 
                                           LPBORDERREMOVE pBorderRemove,
                                           BORDERREMOVECALLBACK pfnCallback,
                                           L_VOID L_FAR *pUserData);

typedef L_INT ( pEXT_FUNCTION pL_INVERTEDTEXTBITMAP)(pBITMAPHANDLE pBitmap,
                                        LPINVERTEDTEXT pInvertedText,
                                        INVERTEDTEXTCALLBACK pfnCallback,
                                        L_VOID L_FAR *pUserData);

typedef L_INT ( pEXT_FUNCTION pL_DOTREMOVEBITMAP)(
                                     pBITMAPHANDLE pBitmap,
                                     LPDOTREMOVE pDotRemove,
                                     DOTREMOVECALLBACK pfnCallback,
                                     L_VOID L_FAR *pUserData);


typedef L_INT ( pEXT_FUNCTION pL_HOLEPUNCHREMOVEBITMAP)(
                                           pBITMAPHANDLE pBitmap,
                                           LPHOLEPUNCH pHolePunch,
                                           HOLEPUNCHREMOVECALLBACK pfnCallback,
                                           L_VOID L_FAR *pUserData);


typedef L_INT ( pEXT_FUNCTION pL_STAPLEREMOVEBITMAP)(
                                           pBITMAPHANDLE pBitmap,
                                           LPSTAPLE pStaplePunch,
                                           STAPLEREMOVECALLBACK pfnCallback,
                                           L_VOID L_FAR *pUserData);

typedef L_INT ( pEXT_FUNCTION pL_EMBOSSBITMAP )(pBITMAPHANDLE pBitmap,
                                    L_UINT uDirection,
                                    L_UINT uDepth);

typedef L_INT ( pEXT_FUNCTION pL_GAMMACORRECTBITMAP )(pBITMAPHANDLE pBitmap,
                                          L_UINT uGamma);

typedef L_INT ( pEXT_FUNCTION pL_GETAUTOTRIMRECT)(pBITMAPHANDLE pBitmap,
                                     L_UINT uThreshold,
                                     RECT L_FAR *pRect);

typedef L_INT ( pEXT_FUNCTION pL_GETBITMAPCOLORCOUNT)(pBITMAPHANDLE pBitmap,
                                         L_UINT32 L_FAR *puCount);

typedef L_INT (pEXT_FUNCTION pL_GETBITMAPHISTOGRAM) (pBITMAPHANDLE pBitmap, L_UINT32 * pHisto, L_UINT uHistoLen, L_UINT uChannel);

typedef L_INT ( pEXT_FUNCTION pL_GETMINMAXBITS)(pBITMAPHANDLE pBitmap,
                                  L_INT L_FAR*pLowBit,
                                  L_INT L_FAR*pHighBit);

typedef L_INT ( pEXT_FUNCTION pL_GETMINMAXVAL)(pBITMAPHANDLE pBitmap,
                                  L_UINT L_FAR*pMinVal,
                                  L_UINT L_FAR*pMaxVal);

typedef L_INT ( pEXT_FUNCTION pL_HISTOCONTRASTBITMAP )(pBITMAPHANDLE pBitmap,
                                           L_INT nChange);

typedef L_INT ( pEXT_FUNCTION pL_INTENSITYDETECTBITMAP )(pBITMAPHANDLE pBitmap,
                                             L_UINT uLow,
                                             L_UINT uHigh);

typedef L_INT ( pEXT_FUNCTION pL_INVERTBITMAP )(pBITMAPHANDLE pBitmap);


typedef L_INT ( pEXT_FUNCTION pL_MAXFILTERBITMAP)(pBITMAPHANDLE pBitmap,
                                     L_UINT uDim);

typedef L_INT ( pEXT_FUNCTION pL_MEDIANFILTERBITMAP )(pBITMAPHANDLE pBitmap,
                                          L_UINT uDim);

typedef L_INT ( pEXT_FUNCTION pL_MINFILTERBITMAP)(pBITMAPHANDLE pBitmap,
                                     L_UINT uDim);

typedef L_INT ( pEXT_FUNCTION pL_MOSAICBITMAP )(pBITMAPHANDLE pBitmap,
                                    L_UINT uDim);

typedef L_INT ( pEXT_FUNCTION pL_OILIFYBITMAP )(pBITMAPHANDLE pBitmap,
                                     L_UINT uDim);

typedef L_INT ( pEXT_FUNCTION pL_POSTERIZEBITMAP )(pBITMAPHANDLE pBitmap,
                                       L_UINT uLevels);

typedef L_INT ( pEXT_FUNCTION pL_PICTURIZEBITMAP)(pBITMAPHANDLE pBitmap, 
                                    L_CHAR L_FAR*pszDirName, 
                                    L_UINT uFlags,
                                    L_INT nCellWidth,
                                    L_INT nCellHeight,
                                    PICTURIZECALLBACK pfnCallback,
                                    L_VOID L_FAR*pUserData);

typedef L_INT (pEXT_FUNCTION pL_REMAPBITMAPINTENSITY) (pBITMAPHANDLE pBitmap, L_UINT * pLUT, L_UINT uLUTLen, L_UINT uChannel);

typedef L_INT ( pEXT_FUNCTION pL_SHARPENBITMAP )(pBITMAPHANDLE pBitmap,
                                     L_INT nSharpness);

typedef L_INT ( pEXT_FUNCTION pL_SOLARIZEBITMAP )(pBITMAPHANDLE pBitmap,
                                     L_UINT uThreshold);

typedef L_INT ( pEXT_FUNCTION pL_SPATIALFILTERBITMAP )(pBITMAPHANDLE pBitmap,
                                           LPSPATIALFLT pFilter);

typedef L_INT ( pEXT_FUNCTION pL_STRETCHBITMAPINTENSITY )(pBITMAPHANDLE pBitmap);


typedef L_INT ( pEXT_FUNCTION pL_WINDOWLEVELBITMAP)( pBITMAPHANDLE pBitmap,
                                 L_INT nLowBit,
                                 L_INT nHighBit,
                                 RGBQUAD L_HUGE*pLUT,
                                 L_UINT32 uLUTLength,
                                 L_INT nOrderDst);

typedef L_INT ( pEXT_FUNCTION pL_CONTOURFILTERBITMAP)( pBITMAPHANDLE pBitmap,
                                          L_INT16 nThreshold,
                                          L_INT16 nDeltaDirection,
                                          L_INT16 nMaximumError,
                                          L_INT nOption);

typedef L_INT (pEXT_FUNCTION pL_GAUSSIANFILTERBITMAP) (pBITMAPHANDLE pBitmap, L_INT nRadius);

typedef L_INT (pEXT_FUNCTION pL_UNSHARPMASKBITMAP) (pBITMAPHANDLE pBitmap, L_INT nAmount, L_INT nRadius, L_INT nThreshold, L_UINT uColorType);

typedef L_INT (pEXT_FUNCTION pL_GRAYSCALEBITMAPEXT) (pBITMAPHANDLE pBitmap, L_INT RedFact, L_INT GreenFact, L_INT BlueFact);

typedef L_INT (pEXT_FUNCTION pL_CONVERTTOCOLOREDGRAY) (pBITMAPHANDLE pBitmapHndl, L_INT RedFact, L_INT GreenFact, L_INT BlueFact, L_INT RedGrayFact, L_INT GreenGrayFact, L_INT BlueGrayFact);

typedef L_INT (pEXT_FUNCTION pL_BALANCECOLORS) (pBITMAPHANDLE pBitmapHndl, BALANCING * pRedFact, BALANCING * pGreenFact, BALANCING * pBlueFact);

typedef L_INT (pEXT_FUNCTION pL_SWAPCOLORS) (pBITMAPHANDLE pBitmapHndl, L_INT nFlags);

typedef L_INT (pEXT_FUNCTION pL_LINEPROFILE) (pBITMAPHANDLE pBitmapHndl, POINT FirstPoint, POINT SecondPoint, L_UINT ** pRed, L_UINT ** pGreen, L_UINT ** pBlue);

typedef L_INT (pEXT_FUNCTION pL_HISTOEQUALIZEBITMAP) (BITMAPHANDLE * pBitmap, L_INT nFlag);

typedef L_INT (pEXT_FUNCTION pL_ADDBITMAPS) (HBITMAPLIST hList, L_UINT uFlag);

typedef L_INT (pEXT_FUNCTION pL_ANTIALIASBITMAP) (pBITMAPHANDLE pBitmap, L_UINT uThreshold, L_UINT uDim, L_UINT uFilter);

typedef L_INT (pEXT_FUNCTION pL_EDGEDETECTORBITMAP) (pBITMAPHANDLE pBitmap, L_UINT  uThreshold, L_UINT  uFilter);

typedef L_INT (pEXT_FUNCTION pL_REMOVEREDEYEBITMAP) (pBITMAPHANDLE pBitmap, COLORREF rcNewColor, L_UINT uThreshold, L_INT nLightness);

typedef L_INT (pEXT_FUNCTION pL_RESIZEBITMAPRGN) (pBITMAPHANDLE pBitmap, L_UINT uInflate, L_UINT uFlag, L_BOOL bAsFrame);

typedef L_INT (pEXT_FUNCTION pL_ALPHABLENDBITMAP) (pBITMAPHANDLE pBitmapDest, L_INT nXDst, L_INT nYDst, L_INT nWidth, L_INT nHeight, pBITMAPHANDLE pBitmapSrc, L_INT nXSrc, L_INT nYSrc, L_INT nOpacity);

typedef L_INT (pEXT_FUNCTION pL_FEATHERALPHABLENDBITMAP) (pBITMAPHANDLE pBitmapDest, L_INT nXDst, L_INT nYDst, L_INT nWidth, L_INT nHeight, pBITMAPHANDLE pBitmapSrc, L_INT nXSrc, L_INT nYSrc, pBITMAPHANDLE pBitmapMsk);

typedef L_INT (pEXT_FUNCTION pL_CREATEFADEDMASK) (pBITMAPHANDLE pBitmap, pBITMAPHANDLE pMaskBitmap, L_INT nLength, L_INT nFadeRate, L_INT nStepSize, L_INT nInflate, L_UINT uFlag, L_INT nMaxGray, COLORREF crTransparent);

typedef L_INT (pEXT_FUNCTION pL_MOTIONBLURBITMAP) (pBITMAPHANDLE pBitmap, L_UINT uDim, L_INT  nAngle, L_BOOL bUnidirectional);

typedef L_INT (pEXT_FUNCTION pL_PICTURIZEBITMAPLIST) (pBITMAPHANDLE pBitmap, L_UINT uxDim, L_UINT uyDim, L_UINT uLightnessFact, HBITMAPLIST hList);

typedef L_INT (pEXT_FUNCTION pL_PICTURIZEBITMAPSINGLE) (pBITMAPHANDLE pBitmap, pBITMAPHANDLE pThumbBitmap, L_UINT uxDim, L_UINT uyDim, L_UINT uGammaFact);

typedef L_INT (pEXT_FUNCTION pL_HALFTONEBITMAP) (pBITMAPHANDLE pBitmap, L_UINT uType, L_INT32 nAngle, L_UINT uDim);

typedef L_INT (pEXT_FUNCTION pL_GETFUNCTIONALLOOKUPTABLE) (L_UINT * pLookupTable, L_UINT uLookupLen, L_UINT uStart, L_UINT uEnd, L_INT nFactor, L_UINT uFlag);

typedef L_INT (pEXT_FUNCTION pL_GETUSERLOOKUPTABLE) (L_UINT * pLookupTable, L_UINT uLookupLen, POINT * apUserPoint, L_UINT UserPointCount, L_UINT * puPointCount);

typedef L_INT (pEXT_FUNCTION pL_COMBINEBITMAPEXT) (pBITMAPHANDLE pBitmapDst, L_INT nXDst, L_INT nYDst, L_INT nWidth, L_INT nHeight, pBITMAPHANDLE pBitmapSrc, L_INT nXSrc, L_INT nYSrc, L_UINT uFlag);

typedef L_INT (pEXT_FUNCTION pL_ADDBORDER) (pBITMAPHANDLE pBitmap, LPADDBORDERINFO pAddBorderInfo);

typedef L_INT (pEXT_FUNCTION pL_ADDFRAME) (pBITMAPHANDLE pBitmap, LPADDFRAMEINFO pAddFrameInfo);

typedef L_INT (pEXT_FUNCTION pL_CONVERTBITMAPSIGNEDTOUNSIGNED) (pBITMAPHANDLE pBitmap, L_UINT uShift);



//-----------------------------------------------------------------------------
//--LTDIS.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------


typedef L_INT ( pEXT_FUNCTION pL_APPENDPLAYBACK)(HPLAYBACK hPlayback,
                                     pBITMAPHANDLE pBitmap);

typedef L_BOOL ( pEXT_FUNCTION pL_BITMAPHASRGN)(pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_CANCELPLAYBACKWAIT)(HPLAYBACK hPlayback);

typedef L_INT ( pEXT_FUNCTION pL_CHANGEFROMDDB )(HDC hDC,
                                     pBITMAPHANDLE pBitmap,
                                     HBITMAP hBitmap,
                                     HPALETTE hPalette);

typedef HBITMAP ( pEXT_FUNCTION pL_CHANGETODDB )(HDC hDC,
                                     pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_CLEARPLAYBACKUPDATERECT)(HPLAYBACK hPlayback);

typedef L_BOOL ( pEXT_FUNCTION pL_CLIPBOARDREADY )(L_VOID);

typedef L_INT ( pEXT_FUNCTION pL_CONVERTCOLORSPACE )(L_UCHAR L_FAR * pBufferSrc,
                                         L_UCHAR L_FAR * pBufferDst,
                                         L_INT nWidth,
                                         L_INT nFormatSrc,
                                         L_INT nFormatDst);

typedef L_INT ( pEXT_FUNCTION pL_CONVERTFROMDDB )(HDC hDC,
                                      pBITMAPHANDLE pBitmap,
                                      HBITMAP hBitmap,
                                      HPALETTE hPalette);

typedef HBITMAP ( pEXT_FUNCTION pL_CONVERTTODDB )(HDC hDC,
                                      pBITMAPHANDLE pBitmap);

typedef L_BOOL ( pEXT_FUNCTION pL_COPYFROMCLIPBOARD )(HWND hWnd,
                                          pBITMAPHANDLE pBitmap);

typedef L_BOOL ( pEXT_FUNCTION pL_COPYTOCLIPBOARD )(HWND hWnd,
                                        pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_COPYTOCLIPBOARDEXT )(HWND hWnd,
                                          pBITMAPHANDLE pBitmap,
                                          L_UINT uFlags);

typedef HPALETTE ( pEXT_FUNCTION pL_CREATEPAINTPALETTE )(HDC hDC,
                                             pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_CREATEMASKFROMBITMAPRGN)(pBITMAPHANDLE pBitmap,
                                     pBITMAPHANDLE pMask);

typedef L_INT ( pEXT_FUNCTION pL_CREATEPLAYBACK)(pHPLAYBACK phPlayback,
                                    pBITMAPHANDLE pBitmap,
                                    HBITMAPLIST hList);

typedef L_INT ( pEXT_FUNCTION pL_DESTROYPLAYBACK)(HPLAYBACK hPlayback,
                                     pHBITMAPLIST phList);

typedef L_INT ( pEXT_FUNCTION pL_FRAMEBITMAPRGN)(HDC hDC,
                                       pBITMAPHANDLE pBitmap,
                                       pRGNXFORM pXForm,
                                       L_UINT uType);

typedef L_INT ( pEXT_FUNCTION pL_COLORBITMAPRGN)(HDC hDC, 
                                    pBITMAPHANDLE pBitmap, 
                                    pRGNXFORM pXForm, 
                                    COLORREF crRgnColor);

typedef L_INT ( pEXT_FUNCTION pL_FREEBITMAPRGN)(pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_GETBITMAPRGNAREA)(pBITMAPHANDLE pBitmap,
                                       L_UINT32 L_FAR *puArea);

typedef L_INT ( pEXT_FUNCTION pL_GETBITMAPRGNBOUNDS)(pBITMAPHANDLE pBitmap,
                                       pRGNXFORM pXForm,
                                       RECT L_FAR *pRect);

typedef L_INT ( pEXT_FUNCTION pL_GETBITMAPRGNHANDLE)(pBITMAPHANDLE pBitmap,
                                       pRGNXFORM pXForm,
                                       HRGN L_FAR *phRgn);

typedef L_UINT32 ( pEXT_FUNCTION pL_GETDISPLAYMODE )(L_VOID);


typedef L_INT ( pEXT_FUNCTION pL_GETPAINTCONTRAST)(pBITMAPHANDLE pBitmap);

typedef L_UINT ( pEXT_FUNCTION pL_GETPAINTGAMMA)(pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_GETPAINTINTENSITY)(pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_GETPLAYBACKDELAY)(HPLAYBACK hPlayback,
                                      L_UINT32 L_FAR *puDelay);

typedef L_INT ( pEXT_FUNCTION pL_GETPLAYBACKINDEX)(HPLAYBACK hPlayback,
                                      L_INT L_FAR *pnIndex);

typedef L_INT ( pEXT_FUNCTION pL_GETPLAYBACKSTATE)(HPLAYBACK hPlayback,
                                      L_UINT L_FAR *puState);

typedef L_INT ( pEXT_FUNCTION pL_GETPLAYBACKUPDATERECT)(HPLAYBACK hPlayback,
                                      LPRECT prcUpdate,
                                      L_BOOL fClear);

typedef L_BOOL ( pEXT_FUNCTION pL_ISPTINBITMAPRGN)(pBITMAPHANDLE pBitmap,
                                       L_INT nRow,
                                       L_INT nCol);

typedef L_INT ( pEXT_FUNCTION pL_OFFSETBITMAPRGN)(pBITMAPHANDLE pBitmap,
                                       L_INT nRowOffset,
                                       L_INT nColOffset);

typedef L_INT ( pEXT_FUNCTION pL_PAINTDC )(HDC hDC,
                               pBITMAPHANDLE pBitmap,
                               LPRECT pSrc,
                               LPRECT pClipSrc,
                               LPRECT pDst,
                               LPRECT pClipDst,
                               L_UINT32 uROP3);

typedef L_INT ( pEXT_FUNCTION pL_PAINTDCBUFFER )(HDC hDC,
                                     pBITMAPHANDLE pBitmap,
                                     LPRECT pSrc,
                                     LPRECT pClipSrc,
                                     LPRECT pDst,
                                     LPRECT pClipDst,
                                     L_UINT32 uROP3,
                                     L_UCHAR L_FAR * pBuffer,
                                     L_INT nRow,
                                     L_INT nCount);

typedef L_INT ( pEXT_FUNCTION pL_PAINTRGNDC )(HDC hDC,
                                       pBITMAPHANDLE pBitmap,
                                       LPRECT pSrc,
                                       LPRECT pClipSrc,
                                       LPRECT pDst,
                                       LPRECT pClipDst,
                                       L_UINT32 uROP3);

typedef L_INT ( pEXT_FUNCTION pL_PAINTRGNDCBUFFER )(HDC hDC,
                                       pBITMAPHANDLE pBitmap,
                                       LPRECT pSrc,
                                       LPRECT pClipSrc,
                                       LPRECT pDst,
                                       LPRECT pClipDst,
                                       L_UINT32 uROP3,
                                       L_UCHAR L_FAR * pBuffer,
                                       L_INT nRow,
                                       L_INT nCount);

typedef HDC ( pEXT_FUNCTION pL_PRINTBITMAP )(pBITMAPHANDLE pBitmap,
                                 L_INT nX,
                                 L_INT nY,
                                 L_INT nWidth,
                                 L_INT nHeight,
                                 L_BOOL fEndDoc);

typedef HDC ( pEXT_FUNCTION pL_PRINTBITMAPEXT )(HDC hDC,
                                    pBITMAPHANDLE pBitmap,
                                    L_INT nX,
                                    L_INT nY,
                                    L_INT nWidth,
                                    L_INT nHeight,
                                    L_BOOL fEndDoc);

typedef HDC ( pEXT_FUNCTION pL_PRINTBITMAPFAST )(HDC hDC,
                                     pBITMAPHANDLE pBitmap,
                                     L_INT nX,
                                     L_INT nY,
                                     L_INT nWidth,
                                     L_INT nHeight,
                                     L_BOOL fEndDoc);

typedef L_INT ( pEXT_FUNCTION pL_PROCESSPLAYBACK)(HPLAYBACK hPlayback,
                                     L_UINT L_FAR *puState);

typedef L_INT ( pEXT_FUNCTION pL_SCREENCAPTUREBITMAP )(HDC hDC,
                                           pBITMAPHANDLE pBitmap,
                                           LPRECT pRect);

typedef L_INT ( pEXT_FUNCTION pL_SETBITMAPRGNCOLOR)(pBITMAPHANDLE pBitmap,
                                       COLORREF crColor,
                                       L_UINT uCombineMode);
typedef L_INT ( pEXT_FUNCTION pL_SETBITMAPRGNMAGICWAND)(pBITMAPHANDLE pBitmap,
                                           L_INT x, L_INT y,
                                           L_UCHAR uTolerance,
                                           L_UINT uCombineMode);

typedef L_INT ( pEXT_FUNCTION pL_SETBITMAPRGNELLIPSE)(pBITMAPHANDLE pBitmap,
                                       pRGNXFORM pXForm,
                                       RECT L_FAR *pRect,
                                       L_UINT uCombineMode);

typedef L_INT ( pEXT_FUNCTION pL_SETBITMAPRGNFROMMASK)(pBITMAPHANDLE pBitmap,
                                    pRGNXFORM pXForm,
                                    pBITMAPHANDLE pMask,
                                    L_UINT uCombineMode);

typedef L_INT ( pEXT_FUNCTION pL_SETBITMAPRGNHANDLE)(pBITMAPHANDLE pBitmap,
                                       pRGNXFORM pXForm,
                                       HRGN hRgn,
                                       L_UINT uCombineMode);

typedef L_INT ( pEXT_FUNCTION pL_SETBITMAPRGNPOLYGON)(pBITMAPHANDLE pBitmap,
                                       pRGNXFORM pXForm,
                                       POINT L_FAR *pPoints,
                                       L_UINT uPoints,
                                       L_UINT uFillMode,
                                       L_UINT uCombineMode);

typedef L_INT ( pEXT_FUNCTION pL_SETBITMAPRGNRECT)(pBITMAPHANDLE pBitmap,
                                       pRGNXFORM pXForm,
                                       RECT L_FAR *pRect,
                                       L_UINT uCombineMode);

typedef L_INT ( pEXT_FUNCTION pL_SETBITMAPRGNROUNDRECT)(pBITMAPHANDLE pBitmap,
                                       pRGNXFORM pXForm,
                                       RECT L_FAR *pRect,
                                       L_INT nWidthEllipse,
                                       L_INT nHeightEllipse,
                                       L_UINT uCombineMode);

typedef L_UINT32 ( pEXT_FUNCTION pL_SETDISPLAYMODE )(L_UINT32 uFlagPos,
                                         L_UINT32 uFlagSet);

typedef L_INT ( pEXT_FUNCTION pL_SETPAINTCONTRAST)(pBITMAPHANDLE pBitmap, 
                                      L_INT nValue);

typedef L_INT ( pEXT_FUNCTION pL_SETPAINTGAMMA)(pBITMAPHANDLE pBitmap, 
                                   L_UINT uValue);

typedef L_INT ( pEXT_FUNCTION pL_SETPAINTINTENSITY)(pBITMAPHANDLE pBitmap, 
                                       L_INT nValue);

typedef L_INT ( pEXT_FUNCTION pL_SETPLAYBACKINDEX)(HPLAYBACK hPlayback,
                                      L_INT nIndex);

typedef L_INT ( pEXT_FUNCTION pL_UNDERLAYBITMAP )(pBITMAPHANDLE pBitmapDst,
                                      pBITMAPHANDLE pUnderlay,
                                      L_UINT uFlags);

typedef L_INT ( pEXT_FUNCTION pL_VALIDATEPLAYBACKLINES)(HPLAYBACK hPlayback,
                                           L_INT nRow,
                                           L_INT nLines);

typedef L_INT ( pEXT_FUNCTION pL_WINDOWLEVEL)(pBITMAPHANDLE pBitmap,
                                 L_INT nLowBit,
                                 L_INT nHighBit,
                                 L_RGBQUAD L_HUGE*pLUT,
                                 L_UINT32 ulLUTLength,
                                 L_UINT   uFlags);


typedef L_INT ( pEXT_FUNCTION pL_CREATEPANWINDOW)(HWND hWndParent, pBITMAPHANDLE pBitmap,
                                     L_UINT32 ulDisplayFlags,
                                     L_INT nLeft, L_INT nTop,
                                     L_INT nWidth, L_INT nHeight,
                                     L_CHAR L_FAR* pszClassName,
                                     HICON hIcon, HCURSOR hCursor,
                                     L_BOOL bSysMenu,
                                     PANWNDCALLBACK pfnPanCallback,
                                     L_VOID L_FAR* pUserData );

typedef L_INT ( pEXT_FUNCTION pL_UPDATEPANWINDOW)(HWND hPanWindow,
                                     pBITMAPHANDLE pBitmap,
                                     L_UINT32 ulDisplayFlags,
                                     COLORREF crPen,
                                     LPCSTR pszTitle,
                                     LPRECT prcDst );

typedef L_INT ( pEXT_FUNCTION pL_DESTROYPANWINDOW)( HWND hPanWindow );



typedef L_INT ( pEXT_FUNCTION pL_WINDOWLEVELFILLLUT)(RGBQUAD L_HUGE* pLUT,
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


typedef L_INT ( pEXT_FUNCTION pL_CONVERTFROMWMF)(pBITMAPHANDLE pBitmap, 
                                    HMETAFILE hWmf, 
                                    L_UINT uWidth, 
                                    L_UINT uHeight);

typedef L_INT ( pEXT_FUNCTION pL_CHANGEFROMWMF)(pBITMAPHANDLE pBitmap, 
                                   HMETAFILE hWmf, 
                                   L_UINT uWidth, 
                                   L_UINT uHeight);

typedef HMETAFILE ( pEXT_FUNCTION pL_CONVERTTOWMF)(pBITMAPHANDLE pBitmap);

typedef HMETAFILE ( pEXT_FUNCTION pL_CHANGETOWMF)(pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_CONVERTFROMEMF)(pBITMAPHANDLE pBitmap, 
                                    HENHMETAFILE hWmf, 
                                    L_UINT uWidth, 
                                    L_UINT uHeight);

typedef L_INT ( pEXT_FUNCTION pL_CHANGEFROMEMF)(pBITMAPHANDLE pBitmap, 
                                   HENHMETAFILE hWmf, 
                                   L_UINT uWidth, 
                                   L_UINT uHeight);

typedef HENHMETAFILE ( pEXT_FUNCTION pL_CONVERTTOEMF)(pBITMAPHANDLE pBitmap);

typedef HENHMETAFILE ( pEXT_FUNCTION pL_CHANGETOEMF)(pBITMAPHANDLE pBitmap);

typedef L_INT ( pEXT_FUNCTION pL_STARTMAGGLASS)(HWND hWnd, pBITMAPHANDLE pBitmap, RECT L_FAR* prcDst,
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

typedef L_INT ( pEXT_FUNCTION pL_STOPMAGGLASS)(HWND hWnd);

typedef L_INT ( pEXT_FUNCTION pL_UPDATEMAGGLASSRECT)(HWND hWnd, RECT L_FAR* prcDst);

typedef L_BOOL (pEXT_FUNCTION pL_WINDOWHASMAGGLASS) (HWND hWnd);

typedef L_INT (pEXT_FUNCTION pL_SETBITMAPRGNCURVE) (pBITMAPHANDLE pBitmap, pRGNXFORM pXForm, pCURVE pCurve, L_UINT uCombineMode);

typedef L_INT (pEXT_FUNCTION pL_CURVETOBEZIER) (pCURVE pCurve, L_INT * pOutPointCount, POINT * pOutPoint);

typedef L_INT (pEXT_FUNCTION pL_GETBITMAPCLIPSEGMENTS) (pBITMAPHANDLE pBitmap, L_INT nRow, L_UINT * pSegmentBuffer, L_UINT * puSegmentCount);

typedef L_INT (pEXT_FUNCTION pL_GETBITMAPCLIPSEGMENTSMAX) (pBITMAPHANDLE pBitmap, L_UINT * puMaxSegments);


//-----------------------------------------------------------------------------
//--LTFIL.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------
typedef L_INT(pEXT_FUNCTION pL_COMPRESSBUFFER )(L_UCHAR L_FAR * pBuffer);

typedef L_INT(pEXT_FUNCTION pL_DELETEPAGE)(L_CHAR L_FAR*pszFile, 
                                L_INT nPage,
                                L_UINT uFlags,
                                pSAVEFILEOPTION pSaveOptions);

typedef L_INT(pEXT_FUNCTION pL_ENDCOMPRESSBUFFER )(L_VOID);

typedef L_INT(pEXT_FUNCTION pL_READLOADRESOLUTIONS )(L_CHAR L_FAR *pszFile, 
                                     pDIMENSION pDimensions, 
                                     L_INT L_FAR *pDimensionCount,
                                     pLOADFILEOPTION pLoadOptions);

typedef L_INT(pEXT_FUNCTION pL_READFILETRANSFORMS )(L_CHAR L_FAR *pszFile,
                                         pFILETRANSFORMS pTransforms,
                                         pLOADFILEOPTION pLoadOptions);

typedef L_INT(pEXT_FUNCTION pL_WRITEFILETRANSFORMS )(L_CHAR L_FAR *pszFile,
                                          pFILETRANSFORMS pTransforms,
                                          L_INT nFlags,
                                          pSAVEFILEOPTION pSaveOptions);

typedef L_INT(pEXT_FUNCTION pL_FEEDLOAD )(HGLOBAL hLoad,
                                L_UCHAR L_FAR * pBuffer,
                                L_UINT32 dwBufferSize);

typedef L_INT(pEXT_FUNCTION pL_FILECONVERT )(L_CHAR L_FAR * pszFileSrc,
                                   L_CHAR L_FAR * pszFileDst,
                                   L_INT nType,
                                   L_INT nWidth,
                                   L_INT nHeight,
                                   L_INT nBitsPerPixel,
                                   L_INT nQFactor,
                                   pLOADFILEOPTION pLoadOptions,
                                   pSAVEFILEOPTION pSaveOptions,
                                   pFILEINFO pFileInfo);

typedef L_INT(pEXT_FUNCTION pL_FILEINFO )(L_CHAR L_FAR * pszFile,
                                pFILEINFO pFileInfo,
                                L_UINT uFlags,
                                pLOADFILEOPTION pLoadOptions);

typedef L_INT(pEXT_FUNCTION pL_FILEINFOMEMORY )(L_CHAR L_FAR * pBuffer,
                                      pFILEINFO pFileInfo,
                                      L_INT32 nBufferSize,
                                      L_UINT uFlags,
                                      pLOADFILEOPTION pLoadOptions);

typedef L_INT(pEXT_FUNCTION pL_GETCOMMENT )(L_UINT uType,
                                  L_UCHAR L_FAR * pComment,
                                  L_UINT uLength);

typedef L_INT(pEXT_FUNCTION pL_GETLOADRESOLUTION )(L_INT nFormat,
                                   L_UINT32 L_FAR *pWidth,
                                   L_UINT32 L_FAR *pHeight,
                                   pLOADFILEOPTION pLoadOptions);

typedef L_INT(pEXT_FUNCTION pL_GETFILECOMMENTSIZE )(L_CHAR L_FAR *pszFile,
                                       L_UINT uType,
                                       L_UINT L_FAR *uLength,
                                       pLOADFILEOPTION pLoadOptions);

typedef L_INT(pEXT_FUNCTION pL_GETPCDRESOLUTION )(L_CHAR L_FAR * pszFile,
                                        pPCDINFO pPCDInfo);

typedef L_INT(pEXT_FUNCTION pL_GETWMFRESOLUTION )(L_INT L_FAR* lpResolution);

typedef L_INT32(pEXT_FUNCTION pL_GETTAG )(L_UINT16 uTag,
                              L_UINT16 L_FAR*pType,
                              L_UINT32 L_FAR*pCount,
                              L_VOID L_FAR*pData);

typedef L_INT(pEXT_FUNCTION pL_IGNOREFILTERS )(L_CHAR L_FAR*pszFilters);

typedef L_INT(pEXT_FUNCTION pL_LOADBITMAP )(L_CHAR L_FAR * pszFile,
                                  pBITMAPHANDLE pBitmap,
                                  L_INT nBitsPerPixel,
                                  L_INT nOrder,
                                  pLOADFILEOPTION pLoadOptions,
                                  pFILEINFO pFileInfo);

typedef L_INT(pEXT_FUNCTION pL_LOADBITMAPLIST )(LPSTR lpszFile,
                                     pHBITMAPLIST phList,
                                     L_INT nBitsTo,
                                     L_INT nColorOrder,
                                     pLOADFILEOPTION pLoadOptions,
                                     pFILEINFO pFileInfo);

typedef L_INT(pEXT_FUNCTION pL_LOADBITMAPMEMORY )(L_CHAR L_FAR * pBuffer,
                                        pBITMAPHANDLE pBitmap,
                                        L_INT nBitsPerPixel,
                                        L_INT nOrder,
                                        L_INT32 nBufferSize,
                                        pLOADFILEOPTION pLoadOptions,
                                        pFILEINFO pFileInfo);

typedef L_INT(pEXT_FUNCTION pL_LOADFILE )(L_CHAR L_FAR * pszFile,
                                pBITMAPHANDLE pBitmap,
                                L_INT nBitsPerPixel,
                                L_INT nOrder,
                                L_UINT uFlags,
                                FILEREADCALLBACK pfnCallback,
                                L_VOID L_FAR * pUserData,
                                pLOADFILEOPTION pLoadOptions,
                                pFILEINFO pFileInfo);

typedef L_INT(pEXT_FUNCTION pL_LOADFILETILE )(L_CHAR L_FAR * pszFile,
                                   pBITMAPHANDLE pBitmap,
                                   L_INT nCol,
                                   L_INT nRow,
                                   L_UINT uWidth,
                                   L_UINT uHeight,
                                   L_INT nBitsPerPixel,
                                   L_INT nOrder,
                                   L_UINT uFlags,
                                   FILEREADCALLBACK pfnCallback,
                                   L_VOID L_FAR * pUserData,
                                   pLOADFILEOPTION pLoadOptions,
                                   pFILEINFO pFileInfo);

typedef L_INT(pEXT_FUNCTION pL_LOADFILEOFFSET )(L_INT fd,
                                      L_INT32 nOffsetBegin,
                                      L_INT32 nBytesToLoad,
                                      pBITMAPHANDLE pBitmap,
                                      L_INT nBitsPerPixel,
                                      L_INT nOrder,
                                      L_UINT uFlags,
                                      FILEREADCALLBACK pfnCallback,
                                      L_VOID L_FAR * pUserData,
                                      pLOADFILEOPTION pLoadOptions,
                                      pFILEINFO pFileInfo);

typedef L_INT(pEXT_FUNCTION pL_LOADMEMORY )(L_CHAR L_FAR * pBuffer,
                                  pBITMAPHANDLE pBitmap,
                                  L_INT nBitsPerPixel,
                                  L_INT nOrder,
                                  L_UINT uFlags,
                                  FILEREADCALLBACK pfnCallback,
                                  L_VOID L_FAR * pUserData,
                                  L_INT32 nBufferSize,
                                  pLOADFILEOPTION pLoadOptions,
                                  pFILEINFO pFileInfo);

typedef L_INT(pEXT_FUNCTION pL_PRELOADFILTERS )(L_INT nFixedFilters, 
                                     L_INT nCachedFilters,
                                     L_CHAR L_FAR*pszFilters);

typedef L_INT(pEXT_FUNCTION pL_READFILECOMMENT )(L_CHAR L_FAR *pszFile,
                                       L_UINT uType,
                                       L_UCHAR L_FAR *pComment,
                                       L_UINT uLength,
                                       pLOADFILEOPTION pLoadOptions);

typedef L_INT(pEXT_FUNCTION pL_READFILECOMMENTEXT )(L_CHAR L_FAR *pszFile,
                                       L_UINT uType,
                                       LPFILECOMMENTS pComments,
                                       L_UCHAR L_HUGE *pBuffer,
                                       L_UINT L_FAR *uLength,
                                       pLOADFILEOPTION pLoadOptions);

typedef L_INT(pEXT_FUNCTION pL_READFILECOMMENTMEMORY )(L_CHAR L_FAR * pBuffer,
                                       L_UINT uType,
                                       L_UCHAR L_FAR * pComment,
                                       L_UINT uLength,
                                       L_INT32 nBufferSize,
                                       pLOADFILEOPTION pLoadOptions);

typedef L_INT32(pEXT_FUNCTION pL_READFILETAG )(L_CHAR L_FAR * pFile,
                                 L_UINT16 uTag,
                                 L_UINT16 L_FAR*pType,
                                 L_UINT32 L_FAR*pCount,
                                 L_VOID L_FAR*pData,
                                 pLOADFILEOPTION pLoadOptions);

typedef L_INT32(pEXT_FUNCTION pL_READFILETAGMEMORY )(L_CHAR L_FAR * pBuffer,
                                 L_UINT16 uTag,
                                 L_UINT16 L_FAR*pType,
                                 L_UINT32 L_FAR*pCount,
                                 L_VOID L_FAR*pData,
                                 L_INT32  nBufferSize,
                                 pLOADFILEOPTION pLoadOptions);

typedef L_INT(pEXT_FUNCTION pL_READFILESTAMP )(L_CHAR L_FAR * pszFile,
                                    pBITMAPHANDLE pBitmap,
                                    pLOADFILEOPTION pLoadOptions);

typedef L_INT(pEXT_FUNCTION pL_SAVEBITMAP )(L_CHAR L_FAR * pszFile,
                                  pBITMAPHANDLE pBitmap,
                                  L_INT nFormat,
                                  L_INT nBitsPerPixel,
                                  L_INT nQFactor,
                                  pSAVEFILEOPTION pSaveOptions);

typedef L_INT(pEXT_FUNCTION pL_SAVEBITMAPLIST )(LPSTR lpszFile,
                                  HBITMAPLIST hList,
                                  L_INT nFormat,
                                  L_INT nBits,
                                  L_INT nQFactor,
                                  pSAVEFILEOPTION pSaveOptions);

typedef L_INT(pEXT_FUNCTION pL_SAVEBITMAPMEMORY )(HGLOBAL L_FAR * phHandle,
                                        pBITMAPHANDLE pBitmap,
                                        L_INT nFormat,
                                        L_INT nBitsPerPixel,
                                        L_INT nQFactor,
                                        L_UINT32 L_FAR * puSize,
                                        pSAVEFILEOPTION pSaveOptions);

typedef L_INT(pEXT_FUNCTION pL_SAVEFILE )(L_CHAR L_FAR * pszFile,
                                pBITMAPHANDLE pBitmap,
                                L_INT nFormat,
                                L_INT nBitsPerPixel,
                                L_INT nQFactor,
                                L_UINT uFlags,
                                FILESAVECALLBACK pfnCallback,
                                L_VOID L_FAR * pUserData,
                                pSAVEFILEOPTION pSaveOptions);

typedef L_INT(pEXT_FUNCTION pL_SAVEFILEMEMORY)(HANDLE L_FAR *hHandle,
                                   pBITMAPHANDLE pBitmap,
                                   L_INT nFormat,
                                   L_INT nBitsPerPixel,
                                   L_INT nQFactor,
                                   L_UINT uFlags,
                                   FILESAVECALLBACK pFunction,
                                   L_VOID L_FAR * lpUserData,
                                   L_UINT32 L_FAR *uSize,
                                   pSAVEFILEOPTION pSaveOptions);

typedef L_INT(pEXT_FUNCTION pL_SAVEFILETILE )(L_CHAR L_FAR * pszFile,
                                   pBITMAPHANDLE pBitmap,
                                   L_INT nCol,
                                   L_INT nRow,
                                   FILESAVECALLBACK pfnCallback,
                                   L_VOID L_FAR * pUserData,
                                   pSAVEFILEOPTION pSaveOptions);

typedef L_INT(pEXT_FUNCTION pL_SAVEFILEOFFSET )(L_INT fd,
                                      L_INT32 nOffsetBegin,
                                      L_INT32 L_FAR * nSizeWritten,
                                      pBITMAPHANDLE pBitmap,
                                      L_INT nFormat,
                                      L_INT nBitsPerPixel,
                                      L_INT nQFactor,
                                      L_UINT uFlags,
                                      FILESAVECALLBACK pfnCallback,
                                      L_VOID L_FAR * pUserData,
                                      pSAVEFILEOPTION pSaveOptions);

typedef L_INT(pEXT_FUNCTION pL_SETCOMMENT )(L_UINT uType,
                                  L_UCHAR L_FAR * pComment,
                                  L_UINT uLength);

typedef LOADINFOCALLBACK(pEXT_FUNCTION pL_SETLOADINFOCALLBACK )(LOADINFOCALLBACK pfnCallback, 
                                                     L_VOID L_FAR*pUserData);

typedef L_INT(pEXT_FUNCTION pL_SETLOADRESOLUTION )(L_INT nFormat,
                                  L_UINT32 nWidth,
                                  L_UINT32 nHeight);

typedef L_INT(pEXT_FUNCTION pL_SETPCDRESOLUTION )(L_INT nResolution);

typedef L_INT(pEXT_FUNCTION pL_SETWMFRESOLUTION )(L_INT nResolution);

typedef L_INT(pEXT_FUNCTION pL_SETTAG)(L_UINT16 uTag, 
                                 L_UINT16 uType,
                                 L_UINT32 uCount,
                                 L_VOID L_FAR*pData);

typedef L_INT(pEXT_FUNCTION pL_STARTCOMPRESSBUFFER )(pBITMAPHANDLE pBitmap,
                                           COMPBUFFCALLBACK pfnCallback,
                                           L_UINT32 uInputBytes,
                                           L_UINT uOutputBytes,
                                           L_CHAR L_FAR * pOutputBuffer,
                                           L_INT nOutputType,
                                           L_INT nQFactor,
                                           L_VOID L_FAR * pUserData,
                                           pSAVEFILEOPTION pSaveOptions);


typedef L_INT(pEXT_FUNCTION pL_STARTFEEDLOAD )(pBITMAPHANDLE pBitmap,
                                     L_INT nBitsPerPixel,
                                     L_INT nOrder,
                                     L_UINT uFlags,
                                     FILEREADCALLBACK pfnCallback,
                                     L_VOID L_FAR * pUserData,
                                     HGLOBAL L_FAR * phLoad,
                                     pLOADFILEOPTION pLoadOptions,
                                     pFILEINFO pFileInfo);

typedef L_INT(pEXT_FUNCTION pL_STOPFEEDLOAD )(HGLOBAL hLoad);

typedef L_INT(pEXT_FUNCTION pL_WRITEFILECOMMENTEXT )(L_CHAR L_FAR *pszFile,
                                       L_UINT uType,
                                       LPFILECOMMENTS pComments,
                                       pSAVEFILEOPTION pSaveOptions);

typedef L_INT(pEXT_FUNCTION pL_WRITEFILESTAMP )(L_CHAR L_FAR * pszFile,
                                    pBITMAPHANDLE pBitmap,
                                    pSAVEFILEOPTION pSaveOptions);

typedef L_INT(pEXT_FUNCTION pL_SETSAVERESOLUTION )(L_UINT uCount, 
                                        pDIMENSION pResolutions);

typedef L_INT(pEXT_FUNCTION pL_GETSAVERESOLUTION )(L_UINT L_FAR*puCount, 
                                        pDIMENSION pResolutions);

typedef L_INT(pEXT_FUNCTION pL_2DSETVIEWPORT)(L_INT nWidth, 
                                   L_INT nHeight);

typedef L_INT(pEXT_FUNCTION pL_2DGETVIEWPORT)(L_INT L_FAR*pnWidth, 
                                   L_INT L_FAR*pnHeight);

typedef L_INT(pEXT_FUNCTION pL_2DSETVIEWMODE)(L_INT nViewMode);

typedef L_INT(pEXT_FUNCTION pL_2DGETVIEWMODE)(L_VOID);

typedef L_INT(pEXT_FUNCTION pL_VECLOADFILE)(LPSTR pszFile, 
                                  pVECTORHANDLE pVector,
                                  pLOADFILEOPTION pLoadOptions,
                                  pFILEINFO pFileInfo);

typedef L_INT(pEXT_FUNCTION pL_VECLOADMEMORY )(L_CHAR L_FAR * pBuffer,
                                    pVECTORHANDLE pVector,
                                    L_INT32 nBufferSize,
                                    pLOADFILEOPTION pLoadOptions,
                                    pFILEINFO pFileInfo);

typedef L_INT(pEXT_FUNCTION pL_VECSTARTFEEDLOAD )(pVECTORHANDLE pVector,
                                       HANDLE L_FAR *phLoad,
                                       pLOADFILEOPTION pLoadOptions,
                                       pFILEINFO pFileInfo);

typedef L_INT(pEXT_FUNCTION pL_VECFEEDLOAD)(HANDLE hLoad,
                                L_UCHAR L_FAR *pInBuffer,
                                L_UINT32 dwBufferSize);

typedef L_INT(pEXT_FUNCTION pL_VECSTOPFEEDLOAD)(HANDLE hLoad);

typedef L_INT(pEXT_FUNCTION pL_VECSAVEFILE)(LPSTR pszFile, 
                                   pVECTORHANDLE pVector, 
                                   L_INT nFormat,
                                   pSAVEFILEOPTION pSaveOptions);

typedef L_INT(pEXT_FUNCTION pL_VECSAVEMEMORY)(HANDLE L_FAR *hHandle,
                                   pVECTORHANDLE pVector,
                                   L_INT nFormat,
                                   L_UINT32 L_FAR *uSize,
                                   pSAVEFILEOPTION pSaveOptions);

typedef L_INT (pEXT_FUNCTION pL_GETDEFAULTLOADFILEOPTION) (pLOADFILEOPTION pLoadOptions, L_UINT32 uSize);

typedef L_INT (pEXT_FUNCTION pL_GETDEFAULTSAVEFILEOPTION) (pSAVEFILEOPTION pSaveOptions, L_UINT32 uSize);

typedef L_INT(pEXT_FUNCTION pL_WRITEFILETAG)(L_CHAR L_FAR*pszFile,
                                  pSAVEFILEOPTION pSaveOptions);

typedef L_INT(pEXT_FUNCTION pL_WRITEFILECOMMENT)(L_CHAR L_FAR*pszFile,
                                  pSAVEFILEOPTION pSaveOptions);

typedef L_INT(pEXT_FUNCTION pL_DOCLOADFILE)(LPSTR pszFile, 
                                  pDOCHANDLE pDocument,
                                  pLOADFILEOPTION pLoadOptions);

typedef L_INT(pEXT_FUNCTION pL_DOCLOADMEMORY )(L_CHAR L_FAR * pBuffer,
                                    pDOCHANDLE pDocument,
                                    L_INT32 nBufferSize,
                                    pLOADFILEOPTION pLoadOptions);

typedef L_INT(pEXT_FUNCTION pL_DOCSTARTFEEDLOAD )(pDOCHANDLE pDocument,
                                       HANDLE L_FAR *phLoad,
                                       pLOADFILEOPTION pLoadOptions);

typedef L_INT(pEXT_FUNCTION pL_DOCFEEDLOAD)(HANDLE hLoad,
                                L_UCHAR L_FAR *pInBuffer,
                                L_UINT32 dwBufferSize);

typedef L_INT(pEXT_FUNCTION pL_DOCSTOPFEEDLOAD)(HANDLE hLoad);

typedef L_INT(pEXT_FUNCTION pL_DOCSAVEFILE)(LPSTR pszFile, 
                                   pDOCHANDLE pDocument, 
                                   L_INT nFormat,
                                   pSAVEFILEOPTION pSaveOptions);

typedef L_INT(pEXT_FUNCTION pL_DOCSAVEMEMORY)(HANDLE L_FAR *hHandle,
                                   pDOCHANDLE pDocument,
                                   L_INT nFormat,
                                   L_UINT32 L_FAR *uSize,
                                   pSAVEFILEOPTION pSaveOptions);


typedef L_INT ( pEXT_FUNCTION pL_GETJ2KOPTIONS)( pFILEJ2KOPTIONS pOptions, L_INT nSize );

typedef L_INT ( pEXT_FUNCTION pL_GETDEFAULTJ2KOPTIONS)( pFILEJ2KOPTIONS pOptions, L_INT nSize );

typedef L_INT ( pEXT_FUNCTION pL_SETJ2KOPTIONS)( const pFILEJ2KOPTIONS pOptions);

typedef L_INT (pEXT_FUNCTION pL_LOADBITMAPRESIZE) (L_CHAR * pszFile, pBITMAPHANDLE pSmallBitmap, L_INT nDestWidth, L_INT nDestHeight, L_INT nDestBits, L_UINT32 uFlags, L_INT nOrder, pLOADFILEOPTION pLoadOptions, pFILEINFO pFileInfo);

typedef L_INT (pEXT_FUNCTION pL_SAVEBITMAPBUFFER) (L_UCHAR * pBuffer, L_UINT32 uInitialBufferSize, L_UINT32 * puFinalFileSize, pBITMAPHANDLE pBitmap, L_INT nFormat, L_INT nBitsPerPixel, L_INT nQFactor, SAVEBUFFERCALLBACK pfnSaveBufferCB, L_VOID * lpUserData, pSAVEFILEOPTION pSaveOptions);

typedef L_INT (pEXT_FUNCTION pL_SAVEFILEBUFFER) (L_UCHAR * pBuffer, L_UINT32 uInitialBufferSize, L_UINT32 * puFinalFileSize, pBITMAPHANDLE pBitmap, L_INT nFormat, L_INT nBitsPerPixel, L_INT nQFactor, L_UINT uFlags, FILESAVECALLBACK pfnFileSaveCB, SAVEBUFFERCALLBACK pfnSaveBufferCB, L_VOID * lpUserData, pSAVEFILEOPTION pSaveOptions);

typedef L_INT (pEXT_FUNCTION pL_LOADLAYER) (L_CHAR * pszFile, pBITMAPHANDLE pBitmap, L_INT nBitsPerPixel, L_INT nOrder, L_INT nLayer, pLAYERINFO pLayerInfo, pLOADFILEOPTION pLoadOptions);

typedef L_INT (pEXT_FUNCTION pL_SAVEBITMAPWITHLAYERS) (L_CHAR * pszFile, pBITMAPHANDLE pBitmap, L_INT nFormat, L_INT nBitsPerPixel, L_INT nQFactor, HBITMAPLIST hLayers, pLAYERINFO pLayerInfo, L_INT nLayers, pSAVEFILEOPTION pSaveOptions);

typedef L_INT (pEXT_FUNCTION pL_READFILEEXTENSIONS) (L_CHAR * pszFile, pEXTENSIONLIST * ppExtensionList, pLOADFILEOPTION pLoadOptions);

typedef L_INT (pEXT_FUNCTION pL_FREEEXTENSIONS) (pEXTENSIONLIST pExtensionList);

typedef L_INT (pEXT_FUNCTION pL_LOADEXTENSIONSTAMP) (pEXTENSIONLIST pExtensionList, pBITMAPHANDLE pBitmap);

typedef L_INT (pEXT_FUNCTION pL_GETEXTENSIONAUDIO) (pEXTENSIONLIST pExtensionList, L_INT nStream, L_CHAR ** ppBuffer, L_UINT * puSize);

typedef L_INT (pEXT_FUNCTION pL_TRANSFORMFILE) (L_CHAR * pszFileSrc, L_CHAR * pszFileDst, L_UINT uTransform, TRANSFORMFILECALLBACK pfnCallback, L_VOID * pUserData, pLOADFILEOPTION pLoadOptions);


//-----------------------------------------------------------------------------
//--LTEFX.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------
typedef L_INT (pEXT_FUNCTION pL_EFXPAINTTRANSITION) (HDC ,
                                     L_UINT ,
                                     COLORREF ,
                                     COLORREF ,
                                     L_UINT ,
                                     RECT L_FAR *,
                                     L_UINT ,
                                     L_UINT ,
                                     L_UINT ,
                                     L_UINT ,
                                     L_UINT ,
                                     L_BOOL ,
                                     COLORREF ,
                                     L_UINT ,
                                     COLORREF ,
                                     L_UINT32 );

typedef L_INT (pEXT_FUNCTION pL_EFXPAINTBITMAP) (HDC ,
                                     pBITMAPHANDLE ,
                                     RECT L_FAR *,
                                     RECT L_FAR *,
                                     RECT L_FAR *,
                                     RECT L_FAR *,
                                     L_UINT ,
                                     L_UINT ,
                                     L_UINT ,
                                     L_UINT ,
                                     L_UINT ,
                                     L_BOOL ,
                                     COLORREF ,
                                     L_UINT ,
                                     COLORREF ,
                                     L_UINT32 );

typedef L_INT (pEXT_FUNCTION pL_EFXDRAWFRAME)(HDC ,
                                  RECT L_FAR *,
                                  L_UINT ,
                                  L_UINT ,
                                  COLORREF ,
                                  L_UINT ,
                                  COLORREF ,
                                  COLORREF ,
                                  L_UINT ,
                                  COLORREF ,
                                  COLORREF );

typedef L_INT (pEXT_FUNCTION pL_EFXGRADIENTFILLRECT)(HDC , RECT L_FAR *,
                                         L_UINT , COLORREF ,
                                         COLORREF , L_UINT );

typedef L_INT (pEXT_FUNCTION pL_EFXPATTERNFILLRECT)(HDC , RECT L_FAR *,
                                         L_UINT , COLORREF ,
                                         COLORREF );

typedef L_INT (pEXT_FUNCTION pL_EFXDRAW3DTEXT)(HDC ,
                                 LPSTR ,
                                 RECT L_FAR *,
                                 L_UINT ,
                                 L_INT , L_INT ,
                                 COLORREF ,
                                 COLORREF ,
                                 COLORREF ,
                                 HFONT ,
                                 HDC );

typedef L_INT (pEXT_FUNCTION pL_EFXDRAWROTATED3DTEXT)(HDC ,
                                 LPSTR ,
                                 RECT L_FAR *,
                                 L_INT ,
                                 L_UINT ,
                                 L_INT , L_INT ,
                                 COLORREF ,
                                 COLORREF ,
                                 COLORREF ,
                                 HFONT ,
                                 HDC );

typedef L_INT (pEXT_FUNCTION pL_EFXDRAW3DSHAPE)(HDC ,
                                 L_UINT ,
                                 RECT L_FAR *,
                                 COLORREF ,
                                 HDC ,
                                 RECT L_FAR *,
                                 L_UINT ,
                                 COLORREF ,
                                 L_UINT ,
                                 COLORREF ,
                                 L_UINT ,
                                 L_UINT ,
                                 COLORREF ,
                                 COLORREF ,
                                 L_UINT ,
                                 L_UINT ,
                                 COLORREF ,
                                 COLORREF ,
                                 L_UINT ,
                                 L_UINT ,
                                 L_INT ,
                                 L_INT ,
                                 COLORREF ,
                                 HRGN );

typedef L_INT (pEXT_FUNCTION pL_EFXEFFECTBLT)(HDC ,
                                  L_INT ,
                                  L_INT ,
                                  L_INT ,
                                  L_INT ,
                                  HDC ,
                                  L_INT ,
                                  L_INT ,
                                  L_UINT ,
                                  L_UINT ,
                                  L_UINT ,
                                  L_UINT ,
                                  L_UINT ,
                                  L_BOOL ,
                                  COLORREF ,
                                  L_UINT ,
                                  COLORREF ,
                                  L_UINT32 );


typedef L_INT (pEXT_FUNCTION pL_PAINTDCEFFECT)(HDC ,
                                     pBITMAPHANDLE ,
                                     LPRECT ,
                                     LPRECT ,
                                     LPRECT ,
                                     LPRECT ,
                                     L_UINT32 ,
                                     L_UINT );


typedef L_INT (pEXT_FUNCTION pL_PAINTRGNDCEFFECT )(HDC ,
                                       pBITMAPHANDLE ,
                                       LPRECT ,
                                       LPRECT ,
                                       LPRECT ,
                                       LPRECT ,
                                       L_UINT32 ,
                                       L_UINT );

typedef L_INT (pEXT_FUNCTION pL_SETSAVERESOLUTION )(L_UINT uCount, 
                                        pDIMENSION pResolutions);

typedef L_INT (pEXT_FUNCTION pL_GETSAVERESOLUTION )(L_UINT L_FAR*puCount, 
                                        pDIMENSION pResolutions);
//-----------------------------------------------------------------------------
//--LTDLG.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------
/* EXTERNAL PROTOTYPES */
typedef L_INT (pEXT_FUNCTION pL_DLGFILEOPEN)( HWND hWnd,
                                  LPOPENFILENAME pOpenFileName,
                                  LPFILEOPENPARM pFileOpenParm,
                                  L_UINT32 uFlags,
                                  LTCOMMDLGHELPCB pfnCallback,
                                  L_VOID L_FAR* pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGGETANGLE) (HWND hWndOwner, pBITMAPHANDLE pBitmap, LPGETANGLEDLGPARM pDlgParams, L_UINT32 uFlags, LTCOMMDLGHELPCB pfnCallback, L_VOID * pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGGETSIZE) (HWND hWndOwner, pBITMAPHANDLE pBitmap, LPGETSIZEDLGPARM pDlgParams, L_UINT32 uFlags, LTCOMMDLGHELPCB pfnCallback, L_VOID * pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGGETFILTER) (HWND hWndOwner, pBITMAPHANDLE pBitmap, LPGETFILTERDLGPARM pDlgParams, L_UINT32 uFlags, LTCOMMDLGHELPCB pfnCallback, L_VOID * pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGGETCHANGE) (HWND hWndOwner, pBITMAPHANDLE pBitmap, LPGETCHANGEDLGPARM pDlgParams, L_UINT32 uFlags, LTCOMMDLGHELPCB pfnCallback, L_VOID * pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGGETGAMMA) (HWND hWndOwner, pBITMAPHANDLE pBitmap, LPGETGAMMADLGPARM pDlgParams, L_UINT32 uFlags, LTCOMMDLGHELPCB pfnCallback, L_VOID * pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGGETNOISE) (HWND hWndOwner, pBITMAPHANDLE pBitmap, LPGETNOISEDLGPARM pDlgParams, L_UINT32 uFlags, LTCOMMDLGHELPCB pfnCallback, L_VOID * pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGGETEMBOSS) (HWND hWndOwner, pBITMAPHANDLE pBitmap, LPGETEMBOSSDLGPARM pDlgParams, L_UINT32 uFlags, LTCOMMDLGHELPCB pfnCallback, L_VOID * pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGGETRANGE) (HWND hWndOwner, pBITMAPHANDLE pBitmap, LPGETRANGEDLGPARM pDlgParams, L_UINT32 uFlags, LTCOMMDLGHELPCB pfnCallback, L_VOID * pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGCOLORRES) (HWND hWndOwner, pBITMAPHANDLE pBitmap, LPCOLORRESDLGPARM pDlgParams, L_UINT32 uFlags, L_UINT32 uExFlags, LTCOMMDLGHELPCB pfnCallback, L_VOID * pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGFILESAVE)( HWND hWnd,
                                  LPOPENFILENAME pOpenFileName,
                                  LPFILESAVEPARM pFileSaveParm,
                                  L_UINT32 uFlags,
                                  LPFILESAVEFORMAT pSaveFormats,
                                  L_INT nSaveFormats,
                                  LTCOMMDLGHELPCB pfnCallback,
                                  L_VOID L_FAR* pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGWINDOWLEVEL) (HWND hWndOwner, pBITMAPHANDLE pBitmap, LPWINDOWLEVELDLGPARM pDlgParams, L_UINT32 uFlags, LTCOMMDLGHELPCB pfnCallback, L_VOID * pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGGETEFFECT)( HWND hWnd,
                                   pBITMAPHANDLE pBitmap,
                                   EFXDLGPARM L_FAR * pEfxDlgParm,
                                   L_UINT32 uFlags,
                                   LTCOMMDLGHELPCB pfnCallback,
                                   L_VOID L_FAR* pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGGETSHAPE)( HWND hWnd, pBITMAPHANDLE pBitmap,
                                  pBITMAPHANDLE pBackgroundBitmap,
                                  SHAPEDLGPARM L_FAR * pShapeDlgParm,
                                  L_UINT32 uFlags, LTCOMMDLGHELPCB pfnCallback,
                                  L_VOID L_FAR* pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGGETTEXT)( HWND hWnd, pBITMAPHANDLE pBitmap,
                                 pBITMAPHANDLE pForegroundBitmap,
                                 TEXTDLGPARM L_FAR * pTextDlgParm,
                                 L_UINT32 uFlags, LTCOMMDLGHELPCB pfnCallback,
                                 L_VOID L_FAR* pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGGETGRADIENT)( HWND hWnd, pBITMAPHANDLE pBitmap,
                                     GRADDLGPARM L_FAR * pGradDlgParm,
                                     L_UINT32 uFlags, LTCOMMDLGHELPCB pfnCallback,
                                     L_VOID L_FAR* pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGGETTRANSITION)( HWND hWnd,
                                       pBITMAPHANDLE pBitmap,
                                       TRANSDLGPARM L_FAR * pTransDlgParm,
                                       L_UINT32 uFlags,
                                       LTCOMMDLGHELPCB pfnCallback,
                                       L_VOID L_FAR* pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGGETDIRECTORY) (HWND hWndOwner, LPGETDIRECTORYDLGPARM pDlgParams, L_UINT32 uFlags, LTCOMMDLGHELPCB pfnCallback, L_VOID * pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGCONTOURFILTER) (HWND hWndOwner, pBITMAPHANDLE pBitmap, LPCONTOURFILTERDLGPARM pDlgParams, L_UINT32 uFlags, LTCOMMDLGHELPCB pfnCallback, L_VOID * pUserData);

typedef L_INT (pEXT_FUNCTION pL_DLGGETSTRINGLEN)( L_UINT32 uString, L_UINT L_FAR* puLen );

typedef L_INT (pEXT_FUNCTION pL_DLGGETSTRING)( L_UINT32 uString, L_CHAR L_FAR* pString );

typedef L_INT (pEXT_FUNCTION pL_DLGSETSTRING)( L_UINT32 uString, L_CHAR L_FAR* pString );

typedef HFONT (pEXT_FUNCTION pL_DLGSETFONT)( HFONT hFont );

typedef L_INT (pEXT_FUNCTION pL_DLGHALFTONE) (HWND hWndOwner, pBITMAPHANDLE pBitmap, LPHALFTONEDLGPARM pDlgParams, L_UINT32 uFlags, LTCOMMDLGHELPCB pfnCallback, L_VOID * pUserData);


//-----------------------------------------------------------------------------
//--LTISI.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------
typedef L_BOOL (pEXT_FUNCTION pL_ISISISAVAILABLE)(L_VOID);

typedef L_INT (pEXT_FUNCTION pL_ISISACQUIRE)(HWND , 
                                 pBITMAPHANDLE , 
                                 L_UINT32 );

typedef L_INT (pEXT_FUNCTION pL_ISISACQUIREMULTI)(HWND , 
                                      L_CHAR L_FAR * , 
                                      L_UINT32 , 
                                      L_INT , 
                                      L_BOOL , 
                                      L_INT L_FAR *, 
                                      ISISCALLBACK , 
                                      L_VOID L_FAR * );

typedef L_INT (pEXT_FUNCTION pL_ISISSELECT)(HWND , 
                                L_CHAR L_FAR* );

typedef L_INT (pEXT_FUNCTION pL_ISISLOADDRIVER)(L_CHAR L_FAR* );

typedef L_INT (pEXT_FUNCTION pL_ISISUNLOADDRIVER)(L_VOID);

typedef L_INT (pEXT_FUNCTION pL_ISISSETTAGLONG)(L_UINT , 
                                    L_INT32 );

typedef L_INT (pEXT_FUNCTION pL_ISISGETTAGLONG)(L_UINT , 
                                    L_INT32 L_FAR * );

typedef L_INT (pEXT_FUNCTION pL_ISISSETTAGSHORT)(L_UINT , 
                                     L_INT );

typedef L_INT (pEXT_FUNCTION pL_ISISGETTAGSHORT)(L_UINT , 
                                     L_INT L_FAR * );

typedef L_INT (pEXT_FUNCTION pL_ISISSETSCANOPTIONS)(HWND );

typedef L_INT (pEXT_FUNCTION pL_ISISSETTAGASCII) (L_UINT uTag, L_CHAR * pszValue);

typedef L_INT (pEXT_FUNCTION pL_ISISGETTAGASCII) (L_UINT uTag, L_CHAR * pszValue, L_UINT32 * puSize, L_BOOL bDefault);

typedef L_INT (pEXT_FUNCTION pL_ISISGETTAGASCIICHOICE) (L_UINT uTag, L_INT32 nIndex, L_CHAR * pszValue, L_UINT32 * puSize);

typedef L_INT (pEXT_FUNCTION pL_ISISGETTAGLONGCHOICE) (L_UINT uTag, L_INT32 nIndex, L_INT32 * plValue);

typedef L_INT (pEXT_FUNCTION pL_ISISGETTAGSHORTCHOICE) (L_UINT uTag, L_INT32 nIndex, L_INT * pnValue);


//-----------------------------------------------------------------------------
//--LTTWN.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------

typedef L_INT (pEXT_FUNCTION pL_TWAINACQUIRE )(HWND hWnd, pBITMAPHANDLE pBitmap);

typedef L_INT (pEXT_FUNCTION pL_TWAINACQUIREEXT )(HWND hWnd,
                                       pBITMAPHANDLE pBitmap,
                                       L_UINT uFlags,
                                       TWAINCALLBACK pfnCallback,
                                       L_VOID L_FAR * pUserData);

typedef L_INT (pEXT_FUNCTION pL_TWAINCLOSESESSION)(HWND hWnd);

typedef L_INT (pEXT_FUNCTION pL_TWAINENUMSOURCES )(HWND hWnd,
                                        ENUMSOURCECALLBACK pfnCallback,
                                        L_VOID L_FAR * pUserData);

typedef L_INT (pEXT_FUNCTION pL_TWAINSELECT )(HWND hWnd);

typedef L_INT (pEXT_FUNCTION pL_TWAINSETPROPS )(HWND hWnd, pTWAINPROPERTIES pTwain, L_UINT32 uFlags);
typedef L_INT (pEXT_FUNCTION pL_TWAINGETPROPS )(pTWAINPROPERTIES pTwain);

typedef L_BOOL (pEXT_FUNCTION pL_ISTWAINAVAILABLE)(HWND hWnd);

//-----------------------------------------------------------------------------
//--LTANN.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------


typedef L_INT ( pEXT_FUNCTION pL_ANNBRINGTOFRONT )(HANNOBJECT hObject);
typedef L_INT ( pEXT_FUNCTION pL_ANNCLIPBOARDREADY)(L_BOOL L_FAR *pfReady);
typedef L_INT ( pEXT_FUNCTION pL_ANNCOPY)(HANNOBJECT hSource,
                                 pHANNOBJECT phDest);
typedef L_INT ( pEXT_FUNCTION pL_ANNCOPYFROMCLIPBOARD)(HWND hWnd,
                                          pHANNOBJECT phContainer);
typedef L_INT ( pEXT_FUNCTION pL_ANNCOPYTOCLIPBOARD)(HANNOBJECT hObject,
                                        L_UINT uFormat,
                                        L_BOOL fSelected,
                                        L_BOOL fEmpty,
                                        L_BOOL fCheckMenu);
typedef L_INT ( pEXT_FUNCTION pL_ANNCUTTOCLIPBOARD)(HANNOBJECT hObject,
                                        L_UINT uFormat,
                                        L_BOOL fSelected,
                                        L_BOOL fEmpty,
                                        L_BOOL fCheckMenu);
typedef L_INT ( pEXT_FUNCTION pL_ANNCREATE )(L_UINT uObjectType,
                                 pHANNOBJECT phObject);
typedef L_INT ( pEXT_FUNCTION pL_ANNCREATECONTAINER )(HWND hWnd,
                                          pANNRECT pRect,
                                          L_BOOL fVisible,
                                          pHANNOBJECT phObject);
typedef L_INT ( pEXT_FUNCTION pL_ANNCREATEITEM )(HANNOBJECT hContainer,
                                     L_UINT uObjectType,
                                     L_BOOL fVisible,
                                     pHANNOBJECT phObject);
typedef L_INT ( pEXT_FUNCTION pL_ANNCREATETOOLBAR)(HWND hwndParent,
                                      LPPOINT pPoint,
                                      L_UINT uAlign,
                                      L_BOOL fVisible,
                                      HWND L_FAR *phWnd,
                                      L_UINT uButtons,
                                      pANNBUTTON pButtons);
typedef L_INT ( pEXT_FUNCTION pL_ANNDEFINE )(HANNOBJECT hObject,
                                 LPPOINT pPoint,
                                 L_UINT uState);
typedef L_INT ( pEXT_FUNCTION pL_ANNDELETEPAGEOFFSET)(L_INT fd,	
                                         L_INT32 nOffset,
                                         L_INT32 nPage);
typedef L_INT ( pEXT_FUNCTION pL_ANNDELETEPAGE)(L_CHAR L_FAR * pFile, 
                                   L_INT32 nPage);
typedef L_INT ( pEXT_FUNCTION pL_ANNDELETEPAGEMEMORY )(HGLOBAL hMem, L_UINT32 *puMemSize, L_INT32 nPage);
typedef L_INT ( pEXT_FUNCTION pL_ANNDESTROY )(HANNOBJECT hObject,
                                 L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNDRAW )(HDC hDC,
                               LPRECT prcInvalid,
                               HANNOBJECT hObject);
typedef L_INT ( pEXT_FUNCTION pL_ANNENUMERATE )(HANNOBJECT hObject,
                                    ANNENUMCALLBACK pfnCallback,
                                    L_VOID L_FAR * pUserData,
                                    L_UINT uFlags,
                                    L_CHAR L_FAR*pUserList);
typedef L_INT ( pEXT_FUNCTION pL_ANNFILEINFO )(L_CHAR *pszFile, 
                                  pANNFILEINFO pAnnFileInfo);
typedef L_INT ( pEXT_FUNCTION pL_ANNFILEINFOOFFSET )(L_INT fd, 
                                        pANNFILEINFO pAnnFileInfo);
typedef L_INT ( pEXT_FUNCTION pL_ANNFILEINFOMEMORY )(L_UCHAR L_FAR * pMem, 
                                        L_UINT32 uMemSize, 
                                        pANNFILEINFO pAnnFileInfo);
typedef L_INT ( pEXT_FUNCTION pL_ANNFLIP)(HANNOBJECT hObject,
                                    pANNPOINT pCenter,
                                    L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETACTIVESTATE )(HANNOBJECT hObject,
                                         L_UINT L_FAR * puState);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETAUTOCONTAINER )(HANNOBJECT hObject,
                                          pHANNOBJECT phContainer);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETAUTODRAWENABLE )(HANNOBJECT hObject,
                                          L_BOOL L_FAR *pfEnable);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETAUTOMENUENABLE )(HANNOBJECT hObject,
                                          L_BOOL L_FAR *pfEnable);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETAUTOTEXT )(HANNOBJECT hObject,
                                     L_UINT uItem,
                                     L_CHAR L_FAR *pText);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETAUTOTEXTLEN )(HANNOBJECT hObject,
                                     L_UINT uItem,
                                     L_UINT L_FAR * puLen);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETBACKCOLOR )(HANNOBJECT hObject,
                                       COLORREF L_FAR * pcrBack);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETBITMAP )(HANNOBJECT hObject,
                                    pBITMAPHANDLE pBitmap);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETBITMAPDPIX)(HANNOBJECT hObject,
                                      L_DOUBLE  L_FAR*pdDpiX);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETBITMAPDPIY)(HANNOBJECT hObject,
                                      L_DOUBLE  L_FAR*pdDpiY);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETBOUNDINGRECT )(HANNOBJECT hObject, 
                                         LPRECT pRect, 
                                         LPRECT pRectName);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETCONTAINER )(HANNOBJECT hObject,
                                       pHANNOBJECT phContainer);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETDISTANCE)(HANNOBJECT hObject,
                                    L_DOUBLE L_FAR*pdDistance,
                                    L_DOUBLE L_FAR*pdDistance2);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETDPIX )(HANNOBJECT hObject,
                                 L_DOUBLE L_FAR * pdDpiX);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETDPIY )(HANNOBJECT hObject,
                                 L_DOUBLE L_FAR * pdDpiY);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETFILLMODE )(HANNOBJECT hObject,
                                      L_UINT L_FAR * puFillMode);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETFILLPATTERN )(HANNOBJECT hObject,
                                         L_UINT L_FAR * puFillPattern);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETFONTBOLD )(HANNOBJECT hObject,
                                      L_BOOL L_FAR * pfFontBold);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETFONTITALIC )(HANNOBJECT hObject,
                                        L_BOOL L_FAR * pfFontItalic);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETFONTNAME )(HANNOBJECT hObject,
                                      L_CHAR L_FAR * pFontName);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETFONTNAMELEN )(HANNOBJECT hObject,
                                         L_UINT L_FAR * puLen);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETFONTSIZE )(HANNOBJECT hObject,
                                      L_DOUBLE L_FAR * pdFontSize);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETFONTSTRIKETHROUGH )(HANNOBJECT hObject,
                                        L_BOOL L_FAR * pfFontStrikeThrough);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETFONTUNDERLINE )(HANNOBJECT hObject,
                                           L_BOOL L_FAR * pfFontUnderline);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETFORECOLOR )(HANNOBJECT hObject,
                                       COLORREF L_FAR * pcrFore);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETGAUGELENGTH)(HANNOBJECT hObject,
                                       L_DOUBLE L_FAR*pdLength);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETHYPERLINK )(HANNOBJECT hObject,
                                       L_UINT L_FAR*puType,
                                       L_UINT L_FAR*puMsg,
                                       WPARAM L_FAR*pwParam,
                                       L_CHAR L_FAR*pLink);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETHYPERLINKLEN )(HANNOBJECT hObject,
                                       L_UINT L_FAR*puLen);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETHYPERLINKMENUENABLE)(HANNOBJECT hObject,
                              L_BOOL L_FAR*pfEnable);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETLINESTYLE )(HANNOBJECT hObject,
                                       L_UINT L_FAR * puLineStyle);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETLINEWIDTH )(HANNOBJECT hObject,
                                       L_DOUBLE L_FAR * pdLineWidth);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETLOCKED )(HANNOBJECT hObject, 
                                   L_BOOL L_FAR * pfLocked);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETOFFSETX )(HANNOBJECT hObject,
                                     L_DOUBLE L_FAR * pdOffsetX);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETOFFSETY )(HANNOBJECT hObject,
                                     L_DOUBLE L_FAR * pdOffsetY);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETPOINTCOUNT )(HANNOBJECT hObject,
                                     L_UINT L_FAR *puCount);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETPOINTS )(HANNOBJECT hObject,
                                     pANNPOINT pPoints);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETPOLYFILLMODE )(HANNOBJECT hObject,
                                      L_UINT L_FAR * puPolyFillMode);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETRECT )(HANNOBJECT hObject, 
                                 pANNRECT pRect, 
                                 pANNRECT pRectName);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETROP2 )(HANNOBJECT hObject,
                                  L_UINT L_FAR*puRop2);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETSCALARX )(HANNOBJECT hObject,
                                     L_DOUBLE L_FAR * pdScalarX);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETSCALARY )(HANNOBJECT hObject,
                                     L_DOUBLE L_FAR * pdScalarY);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETSELECTCOUNT )(HANNOBJECT hObject,
                                      L_UINT L_FAR *puCount);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETSELECTED )(HANNOBJECT hObject,
                                      L_BOOL L_FAR * pfSelected);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETSELECTITEMS)(HANNOBJECT hObject, 
                                       pHANNOBJECT pItems);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETSELECTRECT)(HANNOBJECT hObject,
                                       LPRECT pRect);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETTAG )(HANNOBJECT hObject,
                                 L_UINT32 L_FAR * puTag);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETTEXT )(HANNOBJECT hObject,
                                  L_CHAR L_FAR * pText);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETTEXTLEN )(HANNOBJECT hObject,
                                     L_UINT L_FAR * puLen);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETTOOL )(HANNOBJECT hObject,
                                    L_UINT L_FAR * puTool);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETTOOLBARBUTTONVISIBLE)(HWND hwndToolBar,
                                     L_UINT uButton,
                                     L_BOOL L_FAR *pfVisible);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETTOOLBARCHECKED )(HWND hwndToolBar,
                                     L_UINT L_FAR *puChecked);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETTRANSPARENT )(HANNOBJECT hObject,
                                  L_BOOL L_FAR*pbTransparent);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETTYPE )(HANNOBJECT hObject,
                                  L_UINT L_FAR * puObjectType);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETTOPCONTAINER )(HANNOBJECT hObject,
                                  pHANNOBJECT phContainer);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETUNIT)(HANNOBJECT hObject,
                                L_UINT L_FAR*puUnit,
                                L_CHAR L_FAR*pUnitAbbrev,
                                L_UINT L_FAR*puPrecision);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETUNITLEN)(HANNOBJECT hObject,
                                   L_UINT L_FAR*puLen);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETUSERMODE )(HANNOBJECT hObject,
                                      L_UINT L_FAR * puMode);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETVISIBLE )(HANNOBJECT hObject,
                                     L_BOOL L_FAR * pfVisible);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETWND )(HANNOBJECT hObject,
                                 HWND L_FAR * phWnd);
typedef L_INT ( pEXT_FUNCTION pL_ANNHITTEST )(HANNOBJECT hObject,
                                  LPPOINT pPoint,
                                  L_UINT L_FAR * puResult,
                                  pHANNOBJECT phObjectHit);
typedef L_INT ( pEXT_FUNCTION pL_ANNINSERT )(HANNOBJECT hContainer,
                                 HANNOBJECT hObject,
                                 L_BOOL fStripContainer);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETITEM )(HANNOBJECT hContainer,
                                 pHANNOBJECT phItem);
typedef L_INT ( pEXT_FUNCTION pL_ANNLOAD )(L_CHAR L_FAR * pFile,
                               pHANNOBJECT phObject,
                               pLOADFILEOPTION pLoadOptions);
typedef L_INT ( pEXT_FUNCTION pL_ANNLOADOFFSET )(L_INT fd,
                               L_INT32 nOffset,
                               L_UINT32 nLength,
                               pHANNOBJECT phObject,
                               pLOADFILEOPTION pLoadOptions);
typedef L_INT ( pEXT_FUNCTION pL_ANNLOADMEMORY )(L_UCHAR L_FAR * pMem,
                               L_UINT32 uMemSize,
                               pHANNOBJECT phObject,
                               pLOADFILEOPTION pLoadOptions);
typedef L_INT ( pEXT_FUNCTION pL_ANNLOCK )(HANNOBJECT hObject, 
                              L_CHAR L_FAR* pLockKey, 
                              L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNMOVE)(HANNOBJECT hObject,
                               L_DOUBLE dDx,
                               L_DOUBLE dDy,
                               L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNPRINT)(HDC hDC,
                              LPRECT prcBounds,
                              HANNOBJECT hObject);
typedef L_INT ( pEXT_FUNCTION pL_ANNREALIZE)(pBITMAPHANDLE pBitmap,
                               LPRECT prcBounds,
                               HANNOBJECT hObject,
                               L_BOOL fRedactOnly);
typedef L_INT ( pEXT_FUNCTION pL_ANNRESIZE)(HANNOBJECT hObject,
                               L_DOUBLE dFactorX,
                               L_DOUBLE dFactorY,
                               pANNPOINT pCenter,
                               L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNREVERSE)(HANNOBJECT hObject,
                               pANNPOINT pCenter,
                               L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNREMOVE )(HANNOBJECT hObject);
typedef L_INT ( pEXT_FUNCTION pL_ANNROTATE)(HANNOBJECT hObject,
                               L_DOUBLE dAngle,
                               pANNPOINT pCenter,
                               L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSAVE )(L_CHAR L_FAR * pFile,
                               HANNOBJECT hObject,
                               L_UINT uFormat,
                               L_BOOL fSelected,
                               pSAVEFILEOPTION pSaveOptions);
typedef L_INT ( pEXT_FUNCTION pL_ANNSAVEOFFSET )(L_INT fd,
                               L_INT32 nOffset,
                               L_UINT32 L_FAR *puSizeWritten,
                               HANNOBJECT hObject,
                               L_UINT uFormat,
                               L_BOOL fSelected,
                               pSAVEFILEOPTION pSaveOptions);
typedef L_INT ( pEXT_FUNCTION pL_ANNSAVEMEMORY )(HANNOBJECT hObject,
                               L_UINT uFormat,
                               L_BOOL fSelected,
                               HGLOBAL L_FAR *phMem,
                               L_UINT32 L_FAR * puMemSize,
                               pSAVEFILEOPTION pSaveOptions);
typedef L_INT ( pEXT_FUNCTION pL_ANNSAVETAG)(HANNOBJECT hObject,
                               L_UINT uFormat,
                               L_BOOL fSelected);
typedef L_INT ( pEXT_FUNCTION pL_ANNSELECTPOINT)(HANNOBJECT hObject,
                                     LPPOINT pPoint);
typedef L_INT ( pEXT_FUNCTION pL_ANNSELECTRECT)(HANNOBJECT hObject,
                                     LPRECT pRect);
typedef L_INT ( pEXT_FUNCTION pL_ANNSENDTOBACK )(HANNOBJECT hObject);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETACTIVESTATE )(HANNOBJECT hObject,
                                         L_UINT uState);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETAUTOCONTAINER )(HANNOBJECT hObject,
                                          HANNOBJECT hContainer);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETAUTODRAWENABLE )(HANNOBJECT hObject,
                                          L_BOOL fEnable);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETAUTOMENUENABLE )(HANNOBJECT hObject,
                                          L_BOOL fEnable);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETAUTOTEXT )(HANNOBJECT hObject,
                                     L_UINT uItem,
                                     L_CHAR L_FAR *pText);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETBACKCOLOR )(HANNOBJECT hObject,
                                       COLORREF crBack,
                                       L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETBITMAP )(HANNOBJECT hObject,
                                    pBITMAPHANDLE pBitmap,
                                    L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETBITMAPDPIX)(HANNOBJECT hObject,
                                      L_DOUBLE  dDpiX,
                                      L_UINT    uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETBITMAPDPIY)(HANNOBJECT hObject,
                                      L_DOUBLE  dDpiY,
                                      L_UINT    uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETDPIX)(HANNOBJECT hObject,
                                 L_DOUBLE dDpiX,
                                 L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETDPIY)(HANNOBJECT hObject,
                                 L_DOUBLE dDpiY,
                                 L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETFILLMODE )(HANNOBJECT hObject,
                                      L_UINT uFillMode,
                                      L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETFILLPATTERN )(HANNOBJECT hObject,
                                         L_UINT uFillPattern,
                                         L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETFONTBOLD )(HANNOBJECT hObject,
                                      L_BOOL fFontBold,
                                      L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETFONTITALIC )(HANNOBJECT hObject,
                                        L_BOOL fFontItalic,
                                        L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETFONTNAME )(HANNOBJECT hObject,
                                      L_CHAR L_FAR * pFontName,
                                      L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETFONTSIZE )(HANNOBJECT hObject,
                                      L_DOUBLE dFontSize,
                                      L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETFONTSTRIKETHROUGH )(HANNOBJECT hObject,
                                               L_BOOL fFontStrikeThrough,
                                               L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETFONTUNDERLINE )(HANNOBJECT hObject,
                                           L_BOOL fFontUnderline,
                                           L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETFORECOLOR )(HANNOBJECT hObject,
                                       COLORREF crFore,
                                       L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETGAUGELENGTH)(HANNOBJECT hObject,
                                       L_DOUBLE dLength,
                                       L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETHYPERLINK )(HANNOBJECT hObject,
                                       L_UINT uType,
                                       L_UINT uMsg,
                                       WPARAM wParam,
                                       L_CHAR L_FAR*pLink,
                                       L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETHYPERLINKMENUENABLE)(HANNOBJECT hObject,
                            L_BOOL fEnable,
                            L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETLINESTYLE )(HANNOBJECT hObject,
                                       L_UINT uLineStyle,
                                       L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETLINEWIDTH )(HANNOBJECT hObject,
                                       L_DOUBLE dLineWidth,
                                       L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETOFFSETX)(HANNOBJECT hObject,
                                  L_DOUBLE dOffsetX,
                                  L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETOFFSETY)(HANNOBJECT hObject,
                                  L_DOUBLE dOffsetY,
                                  L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETPOINTS )(HANNOBJECT hObject,
                                    pANNPOINT pPoints,
                                    L_UINT uCount);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETPOLYFILLMODE )(HANNOBJECT hObject,
                                      L_UINT uPolyFillMode,
                                      L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETROP2 )(HANNOBJECT hObject,
                                      L_UINT uROP2,
                                      L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETRECT )(HANNOBJECT hObject,
                                  pANNRECT pRect);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETSELECTED )(HANNOBJECT hObject,
                                      L_BOOL fSelected,
                                      L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETSCALARX)(HANNOBJECT hObject,
                                 L_DOUBLE dScalarX,
                                 L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETSCALARY)(HANNOBJECT hObject,
                                 L_DOUBLE dScalarY,
                                 L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETTAG )(HANNOBJECT hObject,
                                 L_UINT32 uTag,
                                 L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETTEXT )(HANNOBJECT hObject,
                                  L_CHAR L_FAR * pText,
                                  L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETTOOL )(HANNOBJECT hObject,
                                 L_UINT uTool);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETTOOLBARBUTTONVISIBLE)(HWND hwndToolBar,
                                  L_UINT uButton,
                                  L_BOOL fVisible);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETTOOLBARCHECKED)(HWND hwndToolBar,
                                  L_UINT uChecked);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETTRANSPARENT )(HANNOBJECT hObject,
                                      L_BOOL bTransparent,
                                      L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETUNDODEPTH )(HANNOBJECT hObject,
                                      L_UINT uLevels);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETUNIT)(HANNOBJECT hObject,
                                L_UINT uUnit,
                                L_CHAR L_FAR* pUnitAbbrev,
                                L_UINT uPrecision,
                                L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETUSERMODE )(HANNOBJECT hObject,
                                      L_UINT uMode);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETVISIBLE )(HANNOBJECT hObject,
                                     L_BOOL fVisible,
                                     L_UINT uFlags,
                                     L_CHAR L_FAR*pUserList);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETWND )(HANNOBJECT hObject,
                                 HWND hWnd);
typedef L_INT ( pEXT_FUNCTION pL_ANNSHOWLOCKEDICON )(HANNOBJECT hObject,
                                     L_BOOL bShow,
                                     L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNUNDO )(HANNOBJECT hObject);
typedef L_INT ( pEXT_FUNCTION pL_ANNUNLOCK )(HANNOBJECT hObject, 
                              L_CHAR L_FAR* pUnlockKey, 
                              L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNUNREALIZE)(pBITMAPHANDLE pBitmap, 
                                LPRECT prcBounds, 
                                HANNOBJECT hObject, 
                                L_BOOL fSelected);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETNODES)(HANNOBJECT hObject, 
                                 L_BOOL bShowNodes, 
                                 L_UINT uGapNodes, 
                                 L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETNODES)(HANNOBJECT hObject, 
                                 L_BOOL L_FAR*pbShowNodes, 
                                 L_UINT L_FAR*puGapNodes);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETPROTRACTOROPTIONS)(HANNOBJECT hObject, 
                                        L_BOOL  bAcute,
                                        L_UINT  uUnit,
                                        L_CHAR L_FAR*pszAbbrev,
                                        L_UINT  uPrecision,
                                        L_DOUBLE dArcRadius,
                                        L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETPROTRACTOROPTIONS)(HANNOBJECT hObject,
                                        L_BOOL  L_FAR*pbAcute,
                                        L_UINT  L_FAR*puUnit,
                                        L_UINT L_FAR*puAbbrevLen,
                                        L_CHAR L_FAR*pszAbbrev,
                                        L_UINT  L_FAR*puPrecision,
                                        L_DOUBLE L_FAR*pdArcRadius);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETNAME )(HANNOBJECT    hObject, 
                                 L_BOOL        bShowName, 
                                 L_CHAR L_FAR *pText,
                                 pANNPOINT     pNameOffset,
                                 L_BOOL        bNameRestrict,
                                 L_UINT        uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETNAME )(HANNOBJECT     hObject, 
                                 L_BOOL L_FAR  *pbShowName, 
                                 L_UINT L_FAR  *puNameLen, 
                                 L_CHAR L_FAR  *pName,
                                    pANNPOINT      pNameOffset,
                                    L_BOOL L_FAR  *pbNameRestrict);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETSHOWFLAGS )(HANNOBJECT hObject,
                                       L_UINT uShowFlags,
                                       L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETSHOWFLAGS )(HANNOBJECT hObject,
                                       L_UINT L_FAR*puShowFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETANGLE)(HANNOBJECT hObject,
                                 L_DOUBLE L_FAR*pdAngle);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETMETAFILE )(HANNOBJECT hObject, 
                                     HMETAFILE hMetafile, 
                                     L_UINT uType, 
                                     L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETMETAFILE )(HANNOBJECT hObject, 
                                     HMETAFILE L_FAR*phMetafile);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETPREDEFINEDMETAFILE)(L_UINT uType, 
                                              HMETAFILE hMetafile);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETPREDEFINEDMETAFILE)(L_UINT uType, 
                                              HMETAFILE L_FAR*phMetafile,
                                              L_BOOL L_FAR*pbEnhanced);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETSECONDARYBITMAP )(HANNOBJECT hObject, 
                                            pBITMAPHANDLE pBitmap, 
                                            L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETSECONDARYBITMAP )(HANNOBJECT hObject, 
                                            pBITMAPHANDLE pBitmap);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETAUTOMENUITEMENABLE)(HANNOBJECT hObject, 
                                              L_INT nObjectType, 
                                              L_UINT uItem, 
                                              L_UINT uEnable, 
                                              L_UINT uFlags,
                                              L_CHAR L_FAR*pUserList);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETAUTOMENUITEMENABLE)(HANNOBJECT hObject, 
                                              L_INT nObjectType, 
                                              L_UINT uItem, 
                                              L_UINT L_FAR*puEnable);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETAUTOMENUSTATE)(HANNOBJECT hObject, 
                                         L_INT nObjectType, 
                                         L_UCHAR L_FAR*pEnable, 
                                         L_UCHAR L_FAR*pEnableFlags, 
                                         L_UINT uBits, 
                                         L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETAUTOMENUSTATE)(HANNOBJECT hObject, 
                                         L_INT nObjectType, 
                                         L_UCHAR L_FAR*pEnable, 
                                         L_UCHAR L_FAR*pEnableFlags, 
                                         L_UINT uBits);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETUSER)(HANNOBJECT hObject, 
                                L_CHAR L_FAR*pOldUser, 
                                L_CHAR L_FAR*pNewUser, 
                                L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETTOOLBARBUTTONS)(HWND hwndToolBar,
                                          pANNBUTTON pButtons,
                                          L_UINT uButtons);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETTOOLBARBUTTONS)(HWND hwndToolBar,
                                          pANNBUTTON pButtons,
                                          L_UINT L_FAR*puButtons);
typedef L_INT ( pEXT_FUNCTION pL_ANNFREETOOLBARBUTTONS)(pANNBUTTON pButtons,
                                           L_UINT uButtons);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETTOOLBARINFO)(HWND hwndToolBar,
                                       pANNTOOLBARINFO pInfo);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETTOOLBARCOLUMNS)(HWND hwndToolBar,
                                          L_UINT uColumns);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETTOOLBARROWS)(HWND hwndToolBar,
                                          L_UINT uColumns);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETAUTODEFAULTS)(HANNOBJECT hAutomation, 
                                        HANNOBJECT hObject, 
                                        L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETTRANSPARENTCOLOR )(HANNOBJECT hObject, 
                                             COLORREF crTransparent, 
                                             L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETTRANSPARENTCOLOR )(HANNOBJECT hObject, 
                                             COLORREF L_FAR * pcrTransparent);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETUNDODEPTH )(HANNOBJECT hObject,
                                      L_UINT L_FAR*puUsedLevels,
                                      L_UINT L_FAR*puMaxLevels);
typedef L_INT ( pEXT_FUNCTION pL_ANNGROUP )(HANNOBJECT hObject, 
                               L_UINT uFlags, 
                               L_CHAR L_FAR*pUserList);
typedef L_INT ( pEXT_FUNCTION pL_ANNUNGROUP )(HANNOBJECT hObject, 
                               L_UINT uFlags, 
                               L_CHAR L_FAR*pUserList);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETAUTOOPTIONS )(HANNOBJECT hObject,
                                        L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETAUTOOPTIONS )(HANNOBJECT hObject,
                                        L_UINT L_FAR *puFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETOBJECTFROMTAG )(HANNOBJECT hContainer,
                                          L_UINT uFlags,
                                          L_UINT32 uTag,
                                          pHANNOBJECT phTagObject);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETRGNHANDLE)(HANNOBJECT hObject,
                                    pRGNXFORM pXForm,
                                    HRGN L_FAR *phRgn);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETAREA)(HANNOBJECT hObject, 
                                L_UINT32 L_FAR*puCount);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETAUTODIALOGFONTSIZE)(HANNOBJECT hObject,
                                        L_INT   nFontSize);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETAUTODIALOGFONTSIZE)(HANNOBJECT hObject,
                                        L_INT L_FAR* pnFontSize);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETGROUPING)(HANNOBJECT hObject,
                                    L_BOOL bAutoGroup,
                                    L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETGROUPING)(HANNOBJECT hObject,
                                    L_BOOL L_FAR* pbAutoGroup);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETAUTOBACKCOLOR)(HANNOBJECT hObject,
                                         L_UINT uObjectType,
                                         COLORREF crBack);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETAUTOBACKCOLOR)(HANNOBJECT hObject,
                                         L_UINT uObjectType,
                                         COLORREF L_FAR*pcrBack);
typedef L_INT ( pEXT_FUNCTION pL_ANNADDUNDONODE)(HANNOBJECT hObject);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETAUTOUNDOENABLE)(HANNOBJECT hObject,
                                          L_BOOL      bEnable);
typedef L_INT ( pEXT_FUNCTION pL_ANNGETAUTOUNDOENABLE)(HANNOBJECT hObject,
                                          L_BOOL L_FAR*pbEnable);
typedef L_INT ( pEXT_FUNCTION pL_ANNSETTOOLBARPARENT)(HWND hwndToolBar, HWND hwndParent);

//-----------------------------------------------------------------------------
//--LTSCR.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------
typedef L_INT (pEXT_FUNCTION pL_SETCAPTUREOPTION)(pLEADCAPTUREOPTION );
typedef L_INT (pEXT_FUNCTION pL_GETCAPTUREOPTION)(pLEADCAPTUREOPTION );

typedef L_INT (pEXT_FUNCTION pL_CAPTUREWINDOW)(pBITMAPHANDLE , HWND , WINDOWCAPTURETYPE ,pLEADCAPTUREINFO , CAPTURECALLBACK , L_VOID L_FAR* );
typedef L_INT (pEXT_FUNCTION pL_CAPTUREACTIVEWINDOW)(pBITMAPHANDLE , pLEADCAPTUREINFO , CAPTURECALLBACK , L_VOID L_FAR* );
typedef L_INT (pEXT_FUNCTION pL_CAPTUREACTIVECLIENT)(pBITMAPHANDLE , pLEADCAPTUREINFO , CAPTURECALLBACK , L_VOID L_FAR* );

typedef L_INT (pEXT_FUNCTION pL_CAPTUREWALLPAPER)(pBITMAPHANDLE , pLEADCAPTUREINFO , CAPTURECALLBACK , L_VOID L_FAR* );
typedef L_INT (pEXT_FUNCTION pL_CAPTUREFULLSCREEN)(pBITMAPHANDLE , pLEADCAPTUREINFO , CAPTURECALLBACK , L_VOID L_FAR* );
typedef L_INT (pEXT_FUNCTION pL_CAPTUREMENUUNDERCURSOR)(pBITMAPHANDLE , pLEADCAPTUREINFO , CAPTURECALLBACK , L_VOID L_FAR* );
typedef L_INT (pEXT_FUNCTION pL_CAPTUREWINDOWUNDERCURSOR)(pBITMAPHANDLE , pLEADCAPTUREINFO , CAPTURECALLBACK , L_VOID L_FAR* );

typedef L_INT (pEXT_FUNCTION pL_CAPTURESELECTEDOBJECT)(pBITMAPHANDLE ,pLEADCAPTUREOBJECTOPTION ,pLEADCAPTUREINFO ,CAPTURECALLBACK ,L_VOID L_FAR* );
typedef L_INT (pEXT_FUNCTION pL_CAPTUREAREA)(pBITMAPHANDLE ,pLEADCAPTUREAREAOPTION , pLEADCAPTUREINFO , CAPTURECALLBACK , L_VOID L_FAR* );

typedef L_INT (pEXT_FUNCTION pL_CAPTUREMOUSECURSOR)(pBITMAPHANDLE , COLORREF , pLEADCAPTUREINFO , CAPTURECALLBACK , L_VOID L_FAR* );
typedef L_INT (pEXT_FUNCTION pL_CAPTURESETHOTKEYCALLBACK)(CAPTUREHOTKEYCALLBACK , L_VOID L_FAR* );

typedef L_INT (pEXT_FUNCTION pL_SETCAPTUREOPTIONDLG)(HWND , pLEADCAPTUREOPTION );
typedef L_INT (pEXT_FUNCTION pL_CAPTUREAREAOPTIONDLG)(HWND ,pLEADCAPTUREAREAOPTION ,L_INT );
typedef L_INT (pEXT_FUNCTION pL_CAPTUREOBJECTOPTIONDLG)(HWND ,pLEADCAPTUREOBJECTOPTION ,L_INT );

typedef L_INT (pEXT_FUNCTION pL_GETDEFAULTAREAOPTION)(pLEADCAPTUREAREAOPTION );
typedef L_INT (pEXT_FUNCTION pL_GETDEFAULTOBJECTOPTION)(pLEADCAPTUREOBJECTOPTION );
typedef L_INT (pEXT_FUNCTION pL_STOPCAPTURE)();

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                          C A P T U R E       E X E       F U N C T I O N S
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef L_INT (pEXT_FUNCTION pL_CAPTUREFROMEXEDLG)
(
   pBITMAPHANDLE ,   
   L_CHAR L_FAR* ,   
   LPCOLORREF ,      
   L_INT ,           
   L_INT ,           
   pLEADCAPTUREINFO ,
   CAPTURECALLBACK ,
   L_VOID L_FAR* 
);

typedef L_INT (pEXT_FUNCTION pL_CAPTUREFROMEXE)
(
   pBITMAPHANDLE ,
   L_CHAR L_FAR* ,
   L_INT ,
   L_CHAR L_FAR * ,
   L_BOOL ,
   COLORREF ,
   CAPTURECALLBACK ,
   L_VOID L_FAR* 
);

typedef L_INT (pEXT_FUNCTION pL_CAPTUREGETRESCOUNT)
(
   L_CHAR L_FAR * ,
   L_INT ,        
   L_INT32 L_FAR* 
);


typedef L_BOOL (pEXT_FUNCTION pL_ISCAPTUREACTIVE)();

//-----------------------------------------------------------------------------
//--LTNET.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------
/************************************************************************************
 *                                                                                  *
 *                  INTERNET FUNCTIONS                                              *
 *                                                                                  *
 ************************************************************************************/
typedef L_INT ( pEXT_FUNCTION pL_INETCREATEPACKET)(pHINETPACK phPacket,
                                       L_UINT uExtra,
                                       L_VOID L_FAR*pExtra,
                                       L_CHAR L_FAR*pszFormat,
                                       ...);
typedef L_INT ( pEXT_FUNCTION pL_INETCREATEPACKETFROMPARAMS)(pHINETPACK phPacket,
                                       L_UINT uExtra,
                                       L_VOID L_FAR*pExtra,
                                       L_UINT uParama,
                                       pPARAMETER pParams);
typedef L_VOID ( pEXT_FUNCTION pL_INETFREEPACKET)(HINETPACK hPacket);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDCMD)(L_COMP hComputer, 
                                 CMDTYPE uCommand,
                                 L_UINT uCommandID,
                                 HINETPACK hPacket);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDRSP)(L_COMP hComputer, 
                                 CMDTYPE uCommand,
                                 L_UINT uCommandID,
                                 HINETPACK hPacket,
                                 L_INT nStatus);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDLOADCMD)(L_COMP hComputer,
                                     L_UINT uCommandID,
                                     L_CHAR L_FAR*pszFile,
                                     L_INT nBitsPerPixel,
                                     L_INT nOrder,
                                     L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDLOADRSP)(L_COMP hComputer,
                                     L_UINT uCommandID,
                                     L_UINT uBitmapID,
                                     L_UINT uExtra,
                                     L_CHAR L_FAR*pExtra,
                                     L_INT nStatus);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDSAVECMD)(L_COMP hComputer,
                                     L_UINT uCommandID,
                                     L_CHAR L_FAR*pszFile,
                                     L_UINT uBitmapID,
                                     L_INT nFormat,
                                     L_INT nBitsPerPixel, 
                                     L_INT nQFactor,
                                     L_UINT uFlags);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDSAVERSP)(L_COMP hComputer,
                                      L_UINT uCommandID,
                                      L_UINT uExtra,
                                      L_CHAR L_FAR*pExtra,
                                      L_INT nStatus);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDCREATEWINCMD)(L_COMP hComputer,
                                          L_UINT uCommandID,
                                          L_CHAR L_FAR*pszClassName,
                                          L_CHAR L_FAR*pszWindowName,
                                          L_UINT ulFlags,
                                          L_INT nLeft,
                                          L_INT nTop,
                                          L_INT nWidth, 
                                          L_INT nHeight,
                                          L_UINT uParentID);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDCREATEWINRSP)(L_COMP hComputer,
                                          L_UINT uCommandID,
                                          L_UINT uWindowID,
                                          L_UINT uLength,
                                          L_CHAR L_FAR*pExtraInfo,
                                          L_INT nStatus);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDSIZEWINCMD)(L_COMP hComputer,
                                        L_UINT uCommandID,
                                        L_UINT uWindowID,
                                        L_INT nLeft,
                                        L_INT nTop,
                                        L_INT nWidth,
                                        L_INT nHeight);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDSIZEWINRSP)(L_COMP hComputer,
                                        L_UINT uCommandID,
                                        L_UINT uLength,
                                        L_CHAR L_FAR*pExtraInfo,
                                        L_INT nStatus);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDSHOWWINCMD)(L_COMP hComputer,
                                        L_UINT uCommandID,
                                        L_UINT uWindowID,
                                        L_INT nCmdShow);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDSHOWWINRSP)(L_COMP hComputer,
                                        L_UINT uCommandID,
                                        L_UINT uLength,
                                        L_CHAR L_FAR*pExtraInfo,
                                        L_INT nStatus);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDCLOSEWINCMD)(L_COMP hComputer,
                                         L_UINT uCommandID,
                                         L_UINT uWindowID);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDCLOSEWINRSP)(L_COMP hComputer,
                                         L_UINT uCommandID,
                                         L_UINT uLength,
                                         L_CHAR L_FAR*pExtraInfo,
                                         L_INT nStatus);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDFREEBITMAPCMD)(L_COMP hComputer,
                                         L_UINT uCommandID,
                                         L_UINT uBitmapID);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDFREEBITMAPRSP)(L_COMP hComputer,
                                         L_UINT uCommandID,
                                         L_UINT uLength,
                                         L_CHAR L_FAR*pExtraInfo,
                                         L_INT nStatus);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDSETRECTCMD)(L_COMP hComputer,
                                        L_UINT uCommandID,
                                        L_UINT uWindowID,
                                        RECTTYPE nType,
                                        L_INT nLeft,
                                        L_INT nTop,
                                        L_INT nWidth,
                                        L_INT nHeight);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDSETRECTRSP)(L_COMP hComputer,
                                        L_UINT uCommandID,
                                        L_UINT uLength,
                                        L_CHAR L_FAR*pExtraInfo,
                                        L_INT nStatus);
typedef L_INT ( pEXT_FUNCTION pL_INETSETCOMMANDCALLBACK)(L_COMP hComputer, 
                                            INETCOMMANDCALLBACK pfnCallback,
                                            L_VOID L_FAR *pUserData);
typedef L_INT ( pEXT_FUNCTION pL_INETSETRESPONSECALLBACK)(L_COMP hComputer,
                                             INETRESPONSECALLBACK pfnCallback,
                                             L_VOID L_FAR *pUserData);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDATTACHBITMAPCMD)(L_COMP hComputer,
                                             L_UINT uCommandID,
                                             L_UINT uBitmapID,
                                             L_UINT uWindowID);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDATTACHBITMAPRSP)(L_COMP hComputer,
                                             L_UINT uCommandID,
                                             L_UINT uExtra,
                                             L_CHAR L_FAR *pExtra,
                                             L_INT nStatus);
typedef L_INT ( pEXT_FUNCTION pL_INETCONNECT)(L_CHAR L_FAR *pszAddress,
                                 L_INT nPort,
                                 L_COMP L_FAR *phComputer,
                                 INETCALLBACK pfnCallback,
                                 L_VOID L_FAR *pUserData);
typedef L_INT ( pEXT_FUNCTION pL_INETSERVERINIT)(L_INT nPort,
                                    L_COMP L_FAR *phComputer,
                                    INETCALLBACK pfnCallback,
                                    L_VOID L_FAR *pUserData);
typedef L_INT ( pEXT_FUNCTION pL_INETCLOSE)(L_COMP hComputer, L_BOOL bGraceful);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDDATA)(L_COMP hComputer, 
                                  L_CHAR L_FAR *pBuffer, 
                                  L_UINT32 L_FAR *pulBufferLength,
                                  IDATATYPE uDataType);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDMMDATA)(L_COMP hComputer, 
                                    L_CHAR L_FAR *pBuffer, 
                                    L_UINT32 L_FAR*pulBufferLength);
typedef L_INT ( pEXT_FUNCTION pL_INETREADDATA)(L_COMP hComputer, 
                                  L_CHAR L_FAR *pBuffer, 
                                  L_UINT32 L_FAR *pulBufferLength);
typedef L_INT ( pEXT_FUNCTION pL_INETGETHOSTNAME)(L_COMP hHost,
                                     L_CHAR L_FAR *pszName,
                                     L_INT nType,
                                     L_UINT32 L_FAR *pulBufferLength);
typedef L_INT ( pEXT_FUNCTION pL_INETACCEPTCONNECT)(L_COMP hHost, 
                                       L_COMP L_FAR *phRemote,
                                       INETCALLBACK pfnCallback,
                                       L_VOID L_FAR *pUserData);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDBITMAP)(L_COMP hComputer, 
                                    pBITMAPHANDLE pBitmap,
                                    L_INT nFormat, 
                                    L_INT nBitsPerPixel, 
                                    L_INT nQFactor,
                                    L_UINT32 L_FAR*pulImageLength);
typedef L_INT ( pEXT_FUNCTION pL_INETAUTOPROCESS)(L_COMP hComputer,
                                     L_BOOL bProcess);
typedef L_INT ( pEXT_FUNCTION pL_INETSENDRAWDATA)(L_COMP hComputer, 
                                     L_CHAR L_FAR *pBuffer,
                                     L_UINT32 L_FAR *pulBufferLength);
typedef L_INT ( pEXT_FUNCTION pL_INETGETQUEUESIZE)(L_COMP hComputer, 
                                      L_UINT32 L_FAR *pulLength);
typedef L_INT ( pEXT_FUNCTION pL_INETCLEARQUEUE)(L_COMP hComputer);
typedef L_INT ( pEXT_FUNCTION pL_INETSTARTUP)();
typedef L_INT ( pEXT_FUNCTION pL_INETSHUTDOWN)();
typedef L_INT ( pEXT_FUNCTION pL_INETSENDSOUND)(L_COMP hComputer, 
                                   LPWAVEFORMATDATA pWaveFormatData, 
                                   LPWAVEDATA pWaveData, 
                                   L_UINT32 L_FAR *pdwDataSize);
typedef L_INT ( pEXT_FUNCTION pL_INETATTACHTOSOCKET)(L_COMP L_FAR *phComputer,
                                       SOCKET hSocket,
                                       INETCALLBACK pfnCallback,
                                       L_VOID L_FAR *pUserData);
typedef L_INT ( pEXT_FUNCTION pL_INETDETACHFROMSOCKET)(L_COMP hComputer,
                                          L_BOOL bWaitTillQueueEmpty,
                                          SOCKET L_FAR*phSocket);
typedef L_INT ( pEXT_FUNCTION pL_INETSETCALLBACK)(L_COMP hComputer,
                                     INETCALLBACK  pfnCallback,
                                     L_VOID L_FAR* pUserData);
typedef L_INT ( pEXT_FUNCTION pL_INETGETCALLBACK)(L_COMP hComputer,
                                     INETCALLBACK L_FAR*ppfnCallback,
                                     L_VOID L_FAR* L_FAR* ppUserData);
typedef L_INT ( pEXT_FUNCTION pL_INETGETPARAMETERS)(L_UINT L_FAR*puParams, 
                                       pPARAMETER *ppParams, 
                                       L_CHAR *pszFormat, 
                                       va_list pArgs);
typedef L_INT ( pEXT_FUNCTION pL_INETCOPYPARAMETERS)(pPARAMETER L_FAR*ppParams, 
                                        L_UINT uParams, 
                                        pPARAMETER pParams);

typedef L_VOID ( pEXT_FUNCTION pL_INETFREEPARAMETERS)(pPARAMETER pParams, L_INT nCount);


//-----------------------------------------------------------------------------
//--LTWEB.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------
typedef L_INT ( pEXT_FUNCTION pL_INETHTTPCONNECT)(L_CHAR L_FAR *pszServer, L_INT iPort,
                                   L_CHAR L_FAR *pszUserName, L_CHAR L_FAR *pszPassword,
                                   pHINET pHttp);
typedef L_INT ( pEXT_FUNCTION pL_INETHTTPDISCONNECT)(HINET hHttp);
typedef L_INT ( pEXT_FUNCTION pL_INETHTTPOPENREQUEST)(HINET hHttp,L_UINT uType, L_CHAR L_FAR *pszTarget,
                                   L_CHAR L_FAR *pszReferer,L_CHAR L_FAR *pszVersion,
                                   L_UINT32 dwReserved);
typedef L_INT ( pEXT_FUNCTION pL_INETHTTPCLOSEREQUEST)(HINET hHttp);
typedef L_INT ( pEXT_FUNCTION pL_INETHTTPSENDBITMAP)(HINET hHttp, pBITMAPHANDLE pBitmap,
                                   L_INT nFormat, L_INT nBitsPerPixel, L_INT nQFactor,
                                   L_CHAR L_FAR *pszContentType, pNAMEVALUE pNameValue,
                                   pSAVEFILEOPTION pSaveOptions);
typedef L_INT ( pEXT_FUNCTION pL_INETHTTPSENDDATA)(HINET hHttp, L_CHAR L_FAR *pData, L_UINT32 uSize,
                                   L_CHAR L_FAR *pszContentType, pNAMEVALUE pNameValue);
typedef L_INT ( pEXT_FUNCTION pL_INETHTTPSENDFORM)(HINET hHttp, pNAMEVALUE pNameValue, L_UINT uCount);
typedef L_INT ( pEXT_FUNCTION pL_INETHTTPSENDREQUEST)(HINET hHttp, L_CHAR L_FAR *pszHeader,
                                   L_UINT32 ulHeaderSize, L_CHAR L_FAR *pszOptional, L_UINT32 ulOptionalSize);
typedef L_INT ( pEXT_FUNCTION pL_INETHTTPGETRESPONSE)(HINET hHttp, L_CHAR L_FAR *pszData, L_UINT32 L_FAR *ulSize);
typedef L_INT ( pEXT_FUNCTION pL_INETHTTPGETSERVERSTATUS)(HINET hHttp, L_UINT L_FAR *uStatus);
typedef L_INT ( pEXT_FUNCTION pL_INETFTPCONNECT)(L_CHAR L_FAR *pszServer,L_INT iPort,L_CHAR L_FAR *pszUserName,
                           L_CHAR L_FAR *pszPassword,pHFTP pFtp);
typedef L_INT ( pEXT_FUNCTION pL_INETFTPDISCONNECT)(HFTP hFtp);
typedef L_INT ( pEXT_FUNCTION pL_INETFTPSENDFILE)(HFTP hFtp,L_CHAR L_FAR *pszLocal,L_CHAR L_FAR *pszRemote,L_UINT uSendAs);
typedef L_INT ( pEXT_FUNCTION pL_INETFTPGETFILE)(HFTP hFtp, L_CHAR L_FAR *pszRemote,   L_CHAR L_FAR *pszLocal,
                                    L_BOOL bOverwrite, L_UINT uSendAs);
typedef L_INT ( pEXT_FUNCTION pL_INETFTPRENAMEFILE)(HFTP hFtp, L_CHAR L_FAR *pszOld, L_CHAR L_FAR *pszNew);
typedef L_INT ( pEXT_FUNCTION pL_INETFTPDELETEFILE)(HFTP hFtp, L_CHAR L_FAR *pszRemote);
typedef L_INT ( pEXT_FUNCTION pL_INETFTPCREATEDIR)(HFTP hFtp, L_CHAR L_FAR *pszRemoteDir);
typedef L_INT ( pEXT_FUNCTION pL_INETFTPDELETEDIR)(HFTP hFtp, L_CHAR L_FAR *pszRemoteDir);
typedef L_INT ( pEXT_FUNCTION pL_INETFTPGETCURRENTDIR)(HFTP hFtp, L_CHAR L_FAR *pszRemoteDir, L_UINT32 ulSize);
typedef L_INT ( pEXT_FUNCTION pL_INETFTPBROWSEDIR)(HFTP hFtp, L_CHAR L_FAR *pszSearch, FTPBROWSECALLBACK pfnCallback, L_VOID L_FAR *pData);
typedef L_INT ( pEXT_FUNCTION pL_INETFTPCHANGEDIR)(HFTP hFtp, L_CHAR L_FAR *pszDirectory);
typedef L_INT ( pEXT_FUNCTION pL_INETFTPSENDBITMAP)(HFTP hFtp, pBITMAPHANDLE pBitmap,
                                   L_INT nFormat, L_INT nBitsPerPixel, L_INT nQFactor,
                                   pSAVEFILEOPTION pSaveOptions, L_CHAR L_FAR *pszRemote,
                                   L_UINT uSendAs);


//-----------------------------------------------------------------------------
//--LTTMB.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------

typedef L_INT (pEXT_FUNCTION pL_BROWSEDIR )(L_CHAR L_FAR*,
                                             L_CHAR L_FAR*,
                                             L_INT,
                                             L_INT,
                                             L_INT,
                                             L_UINT32,
                                             L_BOOL,
                                             L_BOOL,
                                             COLORREF,
                                             L_BOOL,
                                             L_BOOL,
                                             L_BOOL,
                                             L_BOOL,
                                             L_BOOL,
                                             L_INT32,
                                             L_INT32,
                                             BROWSEDIRCALLBACK,
                                             L_VOID L_FAR *);

//-----------------------------------------------------------------------------
//--LTLST.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------
typedef L_VOID (pEXT_FUNCTION pL_USEIMAGELISTCONTROL )(L_VOID);

typedef HWND (pEXT_FUNCTION pL_CREATEIMAGELISTCONTROL )(DWORD,
                                                        L_INT,
                                                        L_INT,
                                                        L_INT,
                                                        L_INT,
                                                        HWND,
                                                        L_INT,
                                                        COLORREF);

//-----------------------------------------------------------------------------
//--LVKRN.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------
typedef L_INT ( pEXT_FUNCTION pL_VECDUPLICATEOBJECTDESCRIPTOR)( L_INT, L_VOID *, const L_VOID * );
//Do not remove the one above

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  General functions.                                                   []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
typedef L_INT ( pEXT_FUNCTION pL_VECINIT)( pVECTORHANDLE pVector );
typedef L_INT ( pEXT_FUNCTION pL_VECFREE)( pVECTORHANDLE pVector );
typedef L_INT ( pEXT_FUNCTION pL_VECEMPTY)( pVECTORHANDLE pVector );
typedef L_BOOL ( pEXT_FUNCTION pL_VECISEMPTY)( const pVECTORHANDLE pVector );
typedef L_INT ( pEXT_FUNCTION pL_VECCOPY)( pVECTORHANDLE pDst, const pVECTORHANDLE pSrc, L_UINT32 dwFlags );
typedef L_INT ( pEXT_FUNCTION pL_VECSETDISPLAYOPTIONS)( pVECTORHANDLE pVector, const pVECTOR_DISPLAY_OPTIONS pOptions );
typedef L_INT ( pEXT_FUNCTION pL_VECGETDISPLAYOPTIONS)( pVECTORHANDLE pVector, pVECTOR_DISPLAY_OPTIONS pOptions );
typedef L_INT ( pEXT_FUNCTION pL_VECINVERTCOLORS)( pVECTORHANDLE pVector );
typedef L_INT ( pEXT_FUNCTION pL_VECSETVIEWPORT)( pVECTORHANDLE pVector, const RECT L_FAR *pViewport );
typedef L_INT ( pEXT_FUNCTION pL_VECGETVIEWPORT)( const pVECTORHANDLE pVector, RECT L_FAR *pViewport );
typedef L_INT ( pEXT_FUNCTION pL_VECSETPAN)( pVECTORHANDLE pVector, const POINT L_FAR *pPan );
typedef L_INT ( pEXT_FUNCTION pL_VECGETPAN)( const pVECTORHANDLE pVector, POINT L_FAR *pPan );
typedef L_INT ( pEXT_FUNCTION pL_VECPAINT)( HDC hDC, const pVECTORHANDLE pVector, L_BOOL bEraseBkgnd );
typedef L_INT ( pEXT_FUNCTION pL_VECREALIZE)( pBITMAPHANDLE pBitmap, const pVECTORHANDLE pVetcor, L_BOOL bEraseBkgnd );
typedef L_INT ( pEXT_FUNCTION pL_VECPAINTDC)( HDC hDC, const pVECTORHANDLE pVector, L_UINT uWidth, L_UINT uHeight, const RECT L_FAR *pSrc, const RECT L_FAR *pSrcClip, const RECT L_FAR *pDest, const RECT L_FAR *pDestClip, L_UINT32 dwFlags );
typedef L_BOOL ( pEXT_FUNCTION pL_VECIS3D)( const pVECTORHANDLE pVector);
typedef L_BOOL ( pEXT_FUNCTION pL_VECISLOCKED)( const pVECTORHANDLE pVector );
typedef L_INT ( pEXT_FUNCTION pL_VECSETLOCKED)( pVECTORHANDLE pVector, L_BOOL bLock );
typedef L_INT ( pEXT_FUNCTION pL_VECSETBACKGROUNDCOLOR)( pVECTORHANDLE pVector, COLORREF Color );
typedef COLORREF ( pEXT_FUNCTION pL_VECGETBACKGROUNDCOLOR)( const pVECTORHANDLE pVector );
typedef L_INT ( pEXT_FUNCTION pL_VECLOGICALTOPHYSICAL)( const pVECTORHANDLE pVector, POINT L_FAR *pDst, const pVECTORPOINT pSrc );
typedef L_INT ( pEXT_FUNCTION pL_VECPHYSICALTOLOGICAL)( const pVECTORHANDLE pVector, pVECTORPOINT pDst, const POINT L_FAR *pSrc );
typedef L_INT ( pEXT_FUNCTION pL_VECSETPALETTE)( pVECTORHANDLE pVector, HPALETTE hPalette );
typedef HPALETTE ( pEXT_FUNCTION pL_VECGETPALETTE)( const pVECTORHANDLE pVector );
typedef L_INT ( pEXT_FUNCTION pL_VECSETVIEWMODE)( pVECTORHANDLE pVector, L_INT nMode );
typedef L_INT ( pEXT_FUNCTION pL_VECGETVIEWMODE)( const pVECTORHANDLE pVector );
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Transformation function.                                             []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
typedef L_INT ( pEXT_FUNCTION pL_VECSETTRANSLATION)( pVECTORHANDLE pVector, const pVECTORPOINT pTranslation, pVECTOROBJECT pObject, L_UINT32 dwFlags );
typedef L_INT ( pEXT_FUNCTION pL_VECGETTRANSLATION)( const pVECTORHANDLE pVector, pVECTORPOINT pTranslation );
typedef L_INT ( pEXT_FUNCTION pL_VECSETROTATION)( pVECTORHANDLE pVector, const pVECTORPOINT pRotation, pVECTOROBJECT pObject, const pVECTORPOINT pOrigin, L_UINT32 dwFlags );
typedef L_INT ( pEXT_FUNCTION pL_VECGETROTATION)( const pVECTORHANDLE pVector, pVECTORPOINT pRotation);
typedef L_INT ( pEXT_FUNCTION pL_VECSETSCALE)( pVECTORHANDLE pVector, const pVECTORPOINT pScale, pVECTOROBJECT pObject, const pVECTORPOINT pOrigin, L_UINT32 dwFlags );
typedef L_INT ( pEXT_FUNCTION pL_VECGETSCALE)( const pVECTORHANDLE pVector, pVECTORPOINT pScale );
typedef L_INT ( pEXT_FUNCTION pL_VECSETORIGIN)( pVECTORHANDLE pVector, const pVECTORPOINT pOrigin );
typedef L_INT ( pEXT_FUNCTION pL_VECGETORIGIN)( const pVECTORHANDLE pVector, pVECTORPOINT pOrigin );
typedef L_INT ( pEXT_FUNCTION pL_VECAPPLYTRANSFORMATION)( pVECTORHANDLE pVector );
typedef L_INT ( pEXT_FUNCTION pL_VECZOOMRECT)( pVECTORHANDLE pVector, const RECT * );
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Attributes functions.                                                []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
typedef L_INT ( pEXT_FUNCTION pL_VECSETBINDVERTICESMODE)( pVECTORHANDLE pVector, L_INT nMode );
typedef L_INT ( pEXT_FUNCTION pL_VECGETBINDVERTICESMODE)( const pVECTORHANDLE pVector );
typedef L_INT ( pEXT_FUNCTION pL_VECSETPARALLELOGRAM)( pVECTORHANDLE pVector, const pVECTORPOINT pMin, const pVECTORPOINT pMax );
typedef L_INT ( pEXT_FUNCTION pL_VECGETPARALLELOGRAM)( const pVECTORHANDLE pVector, pVECTORPOINT pMin, pVECTORPOINT pMax );
typedef L_INT ( pEXT_FUNCTION pL_VECENUMVERTICES)( pVECTORHANDLE pVector, pVECTORENUMVERTICESPROC pEnumProc, L_VOID L_FAR *pUserData, L_UINT32 dwFlags );
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Camera functions.                                                    []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
typedef L_INT ( pEXT_FUNCTION pL_VECSETCAMERA)( pVECTORHANDLE pVector, const pVECTORCAMERA pCamera );
typedef L_INT ( pEXT_FUNCTION pL_VECGETCAMERA)( const pVECTORHANDLE pVector, pVECTORCAMERA pCamera );
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Metafile functions.                                                  []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
typedef HMETAFILE ( pEXT_FUNCTION pL_VECCONVERTTOWMF)( HDC hDC, const pVECTORHANDLE pVector, const RECT L_FAR *pRect, L_UINT uDPI );
typedef L_INT ( pEXT_FUNCTION pL_VECCONVERTFROMWMF)( HDC hDC, pVECTORHANDLE pVector, HMETAFILE hWMF );
typedef HENHMETAFILE ( pEXT_FUNCTION pL_VECCONVERTTOEMF)( HDC hDC, const pVECTORHANDLE pVector, const RECT L_FAR *pRect, L_UINT uDPI );
typedef L_INT ( pEXT_FUNCTION pL_VECCONVERTFROMEMF)( HDC hDC, pVECTORHANDLE pVector, HENHMETAFILE hEMF );
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Engine functions.                                                    []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
typedef L_INT ( pEXT_FUNCTION pL_VECGETENGINE)( const pVECTORHANDLE pVector );
typedef L_INT ( pEXT_FUNCTION pL_VECATTACHTOWINDOW)( HWND hWnd, pVECTORHANDLE pVector, L_INT nEngine, L_UINT32 dwFlags );
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Marker functions.                                                    []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
typedef L_INT ( pEXT_FUNCTION pL_VECSETMARKER)( pVECTORHANDLE pVector, const pVECTORMARKER pMarker );
typedef L_INT ( pEXT_FUNCTION pL_VECGETMARKER)( const pVECTORHANDLE pVector, pVECTORMARKER pMarker );
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Unit functions.                                                      []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
/* Reserved for internal use */
typedef L_INT ( pEXT_FUNCTION pL_VECSETUNIT)( pVECTORHANDLE pVector, const pVECTORUNIT pUnit );
typedef L_INT ( pEXT_FUNCTION pL_VECGETUNIT)( const pVECTORHANDLE pVector, pVECTORUNIT pUnit );
typedef L_INT ( pEXT_FUNCTION pL_VECCONVERTPOINTTOUNITS)( const pVECTORHANDLE pVector, pVECTORPOINT pptDst, const pVECTORPOINT pptSrc, VECTOR_UNIT UnitToUse );
typedef L_INT ( pEXT_FUNCTION pL_VECCONVERTPOINTFROMUNITS)( const pVECTORHANDLE pVector, pVECTORPOINT pptDst, const pVECTORPOINT pptSrc, VECTOR_UNIT UnitToUse );
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Hit test functions.                                                  []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
typedef L_INT ( pEXT_FUNCTION pL_VECSETHITTEST)( pVECTORHANDLE pVector, const pVECTORHITTEST pHitTest );
typedef L_INT ( pEXT_FUNCTION pL_VECGETHITTEST)( const pVECTORHANDLE pVector, pVECTORHITTEST pHitTest );
typedef L_INT ( pEXT_FUNCTION pL_VECHITTEST)( const pVECTORHANDLE pVector, const POINT L_FAR *pPoint, pVECTOROBJECT pObject );
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Polygon functions.                                                   []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
typedef L_INT ( pEXT_FUNCTION pL_VECSETPOLYGONMODE)( pVECTORHANDLE pVector, L_INT nMode );
typedef L_INT ( pEXT_FUNCTION pL_VECGETPOLYGONMODE)( const pVECTORHANDLE pVector );
typedef L_INT ( pEXT_FUNCTION pL_VECSETUSELIGHTS)( pVECTORHANDLE pVector, L_BOOL bUseLights );
typedef L_BOOL ( pEXT_FUNCTION pL_VECGETUSELIGHTS)( const pVECTORHANDLE pVector );
typedef L_INT ( pEXT_FUNCTION pL_VECSETAMBIENTCOLOR)( pVECTORHANDLE pVector, COLORREF Color );
typedef COLORREF ( pEXT_FUNCTION pL_VECGETAMBIENTCOLOR)( const pVECTORHANDLE pVector );
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Clipboard functions.                                                 []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
typedef L_BOOL ( pEXT_FUNCTION pL_VECCLIPBOARDREADY)();
typedef L_INT ( pEXT_FUNCTION pL_VECCOPYTOCLIPBOARD)( HWND hWnd, const pVECTORHANDLE pVector, L_UINT32 dwFlags );
typedef L_INT ( pEXT_FUNCTION pL_VECCOPYFROMCLIPBOARD)( HWND hWnd, pVECTORHANDLE pVector, L_UINT32 dwFlags );
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Layer functions.                                                     []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
typedef L_INT ( pEXT_FUNCTION pL_VECADDLAYER)( pVECTORHANDLE pVector, const pVECTORLAYERDESC pLayerDesc, pVECTORLAYER pLayer, L_UINT32 dwFlags );
typedef L_INT ( pEXT_FUNCTION pL_VECDELETELAYER)( pVECTORHANDLE pVector, const pVECTORLAYER pLayer );
typedef L_INT ( pEXT_FUNCTION pL_VECEMPTYLAYER)( pVECTORHANDLE pVector, const pVECTORLAYER pLayer );
typedef L_INT ( pEXT_FUNCTION pL_VECCOPYLAYER)( pVECTORHANDLE pVectorDst, const pVECTORLAYER pLayerDst, const pVECTORHANDLE pVectorSrc, const pVECTORLAYER pLayerSrc, L_UINT32 dwFlags );
typedef L_INT ( pEXT_FUNCTION pL_VECGETLAYERBYNAME)( const pVECTORHANDLE pVector, const L_CHAR L_FAR *pszName, pVECTORLAYER pLayer );
typedef L_INT ( pEXT_FUNCTION pL_VECGETLAYERCOUNT)( const pVECTORHANDLE pVector );
typedef L_INT ( pEXT_FUNCTION pL_VECGETLAYERBYINDEX)( const pVECTORHANDLE pVector, L_INT nIndex, pVECTORLAYER pLayer );
typedef L_INT ( pEXT_FUNCTION pL_VECGETLAYER)( const pVECTORHANDLE pVector, const pVECTORLAYER pLayer, pVECTORLAYERDESC pLayerDesc );
typedef L_INT ( pEXT_FUNCTION pL_VECFREELAYER)( pVECTORLAYERDESC pLayerDesc);
typedef L_INT ( pEXT_FUNCTION pL_VECSETLAYER)( pVECTORHANDLE pVector, const pVECTORLAYER pLayer, const pVECTORLAYERDESC pLayerDesc );
typedef L_INT ( pEXT_FUNCTION pL_VECSETACTIVELAYER)( pVECTORHANDLE pVector, const pVECTORLAYER pLayer );
typedef L_INT ( pEXT_FUNCTION pL_VECGETACTIVELAYER)( const pVECTORHANDLE pVector, pVECTORLAYER pLayer );
typedef L_INT ( pEXT_FUNCTION pL_VECENUMLAYERS)( pVECTORHANDLE pVector, pVECTORENUMLAYERSPROC pEnumProc, L_VOID L_FAR *pUserData );
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Group functions.                                                     []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
typedef L_INT ( pEXT_FUNCTION pL_VECADDGROUP)( pVECTORHANDLE pVector, const pVECTORGROUPDESC pGroupDesc, pVECTORGROUP pGroup, L_UINT32 dwFlags );
typedef L_INT ( pEXT_FUNCTION pL_VECDELETEGROUP)( pVECTORHANDLE pVector, const pVECTORGROUP pGroup );
typedef L_INT ( pEXT_FUNCTION pL_VECDELETEGROUPCLONES)( pVECTORHANDLE pVector, const pVECTORGROUP pGroup, L_UINT32 dwFlags );
typedef L_INT ( pEXT_FUNCTION pL_VECEMPTYGROUP)( pVECTORHANDLE pVector, const pVECTORGROUP pGroup );
typedef L_INT ( pEXT_FUNCTION pL_VECCOPYGROUP)( pVECTORHANDLE pVectorDst, const pVECTORGROUP pGroupDst, const pVECTORHANDLE pVectorSrc, const pVECTORGROUP pGroupSrc, L_UINT32 dwFlags );
typedef L_INT ( pEXT_FUNCTION pL_VECGETGROUPBYNAME)( const pVECTORHANDLE pVector, const L_CHAR L_FAR *pszName, pVECTORGROUP pGroup );
typedef L_INT ( pEXT_FUNCTION pL_VECGETGROUPCOUNT)( const pVECTORHANDLE pVector );
typedef L_INT ( pEXT_FUNCTION pL_VECGETGROUPBYINDEX)( const pVECTORHANDLE pVector, L_INT nIndex, pVECTORGROUP pGroup );
typedef L_INT ( pEXT_FUNCTION pL_VECGETGROUP)( const pVECTORHANDLE pVector, const pVECTORGROUP pGroup, pVECTORGROUPDESC pGroupDesc );
typedef L_INT ( pEXT_FUNCTION pL_VECFREEGROUP)( pVECTORGROUPDESC pGroupDesc );
typedef L_INT ( pEXT_FUNCTION pL_VECSETGROUP)( pVECTORHANDLE pVector, const pVECTORGROUP pGroup, const pVECTORGROUPDESC pGroupDesc );
typedef L_INT ( pEXT_FUNCTION pL_VECENUMGROUPS)( pVECTORHANDLE pVector, pVECTORENUMGROUPSPROC pEnumProc, L_VOID L_FAR *pUserData );
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Object functions.                                                    []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
typedef L_INT ( pEXT_FUNCTION pL_VECINITOBJECT)( pVECTOROBJECT pObject );
typedef L_INT ( pEXT_FUNCTION pL_VECADDOBJECT)( pVECTORHANDLE pVector, const pVECTORLAYER pLayer, L_INT nType, const L_VOID L_FAR *pObjectDesc, pVECTOROBJECT pNewObject);
typedef L_INT ( pEXT_FUNCTION pL_VECDELETEOBJECT)( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_UINT32 dwFlags );
typedef L_INT ( pEXT_FUNCTION pL_VECCOPYOBJECT)( pVECTORHANDLE pVectorDst, const pVECTORLAYER pLayerDst, pVECTOROBJECT pObjectDst, const pVECTORHANDLE pVectorSrc, const pVECTOROBJECT pObjectSrc );
typedef L_INT ( pEXT_FUNCTION pL_VECGETOBJECT)( const pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_INT nType, L_VOID L_FAR *pObjectDesc );
typedef L_INT ( pEXT_FUNCTION pL_VECFREEOBJECT)( L_INT nType, L_VOID L_FAR *pObjectDesc );
typedef L_INT ( pEXT_FUNCTION pL_VECSETOBJECT)( pVECTORHANDLE pVector, pVECTOROBJECT pObject, L_INT nType, const L_VOID L_FAR *pObjectDesc );
typedef L_INT ( pEXT_FUNCTION pL_VECEXPLODEOBJECT)( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_UINT32 dwFlags );
typedef L_INT ( pEXT_FUNCTION pL_VECGETOBJECTPARALLELOGRAM)( const pVECTORHANDLE pVector, const pVECTOROBJECT pObject, pVECTORPOINT pMin, pVECTORPOINT pMax, L_UINT32 dwFlags );
typedef L_INT ( pEXT_FUNCTION pL_VECGETOBJECTRECT)( const pVECTORHANDLE pVector, const pVECTOROBJECT pObject, RECT L_FAR *pRect, L_UINT32 dwFlags );
typedef L_BOOL ( pEXT_FUNCTION pL_VECISOBJECTINSIDEPARALLELOGRAM)( const pVECTORHANDLE pVector, const pVECTOROBJECT pObject, const pVECTORPOINT pMin, const pVECTORPOINT pMax, L_UINT32 dwFlags );
typedef L_BOOL ( pEXT_FUNCTION pL_VECISOBJECTINSIDERECT)( const pVECTORHANDLE pVector, const pVECTOROBJECT pObject, const RECT L_FAR *pRect, L_UINT32 dwFlags );
typedef L_INT ( pEXT_FUNCTION pL_VECSELECTOBJECT)( const pVECTORHANDLE pVector, pVECTOROBJECT pObject, L_BOOL bSelect );
typedef L_BOOL ( pEXT_FUNCTION pL_VECISOBJECTSELECTED)( const pVECTORHANDLE pVector, const pVECTOROBJECT pObject );
typedef L_INT ( pEXT_FUNCTION pL_VECHIDEOBJECT)( const pVECTORHANDLE pVector, pVECTOROBJECT pObject, L_BOOL bHide );
typedef L_BOOL ( pEXT_FUNCTION pL_VECISOBJECTHIDDEN)( const pVECTORHANDLE pVector, const pVECTOROBJECT pObject );
typedef L_INT ( pEXT_FUNCTION pL_VECENUMOBJECTS)( pVECTORHANDLE pVector, pVECTORENUMOBJECTSPROC pEnumProc, L_VOID L_FAR *pUserData, L_UINT32 dwFlags );
typedef L_INT ( pEXT_FUNCTION pL_VECENUMOBJECTSINLAYER)( pVECTORHANDLE pVector, const pVECTORLAYER pLayer, pVECTORENUMOBJECTSPROC pEnumProc, L_VOID L_FAR *pUserData, L_UINT32 dwFlags );

typedef L_INT ( pEXT_FUNCTION pL_VECSETOBJECTTOOLTIP)( pVECTORHANDLE pVector, pVECTOROBJECT pObject, L_CHAR *pszTooltip );
typedef L_UINT32 ( pEXT_FUNCTION pL_VECGETOBJECTTOOLTIP)( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_CHAR *pBuffer, L_UINT32 uSize );
typedef L_INT ( pEXT_FUNCTION pL_VECSHOWOBJECTTOOLTIP)( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, pVECTORTOOLTIPDESC pTooltipDesc );
typedef L_INT ( pEXT_FUNCTION pL_VECHIDEOBJECTTOOLTIP)( pVECTORHANDLE pVector, const pVECTOROBJECT pObject );

typedef L_INT ( pEXT_FUNCTION pL_VECSETOBJECTVIEWCONTEXT)( pVECTORHANDLE pVector, pVECTOROBJECT pObject, const pVECTORPOINT pMin, const pVECTORPOINT pMax );
typedef L_INT ( pEXT_FUNCTION pL_VECGETOBJECTVIEWCONTEXT)( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, pVECTORPOINT pMin, pVECTORPOINT pMax );
typedef L_INT ( pEXT_FUNCTION pL_VECREMOVEOBJECTVIEWCONTEXT)( pVECTORHANDLE pVector, pVECTOROBJECT pObject );

typedef L_INT ( pEXT_FUNCTION pL_VECADDHYPERLINK)( pVECTORHANDLE pVector, pVECTOROBJECT pObject, pVECTORLINKDESC pTarget );
typedef L_INT ( pEXT_FUNCTION pL_VECSETHYPERLINK)( pVECTORHANDLE pVector, pVECTOROBJECT pObject, L_UINT32 uIndex, pVECTORLINKDESC pTarget );
typedef L_INT ( pEXT_FUNCTION pL_VECGETHYPERLINK)( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_UINT32 uIndex, pVECTORLINKDESC pTarget );
typedef L_UINT32 ( pEXT_FUNCTION pL_VECGETHYPERLINKCOUNT)( pVECTORHANDLE pVector, const pVECTOROBJECT pObject );
typedef L_INT ( pEXT_FUNCTION pL_VECGOTOHYPERLINK)( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_UINT32 uIndex );

typedef L_INT ( pEXT_FUNCTION pL_VECSETOBJECTDESCRIPTION)( pVECTORHANDLE pVector, pVECTOROBJECT pObject, L_CHAR *pszTarget );
typedef L_UINT32 ( pEXT_FUNCTION pL_VECGETOBJECTDESCRIPTION)( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_CHAR *pBuffer, L_UINT32 uSize );

typedef L_INT ( pEXT_FUNCTION pL_VECSETOBJECTATTRIBUTES)( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, const L_INT *pnROP, const pVECTORPEN pPen, const pVECTORBRUSH pBrush, const pVECTORFONT pFont, L_UINT32 dwFlags );
typedef L_INT ( pEXT_FUNCTION pL_VECGETOBJECTATTRIBUTES)( const pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_INT *pnROP, pVECTORPEN pPen, pVECTORBRUSH pBrush, pVECTORFONT pFont );
typedef L_INT ( pEXT_FUNCTION pL_VECADDOBJECTTOGROUP)( pVECTORHANDLE pVector, const pVECTORGROUP pGroup, L_INT nType, const L_VOID L_FAR *pObjectDesc, pVECTOROBJECT pNewObject );
typedef L_INT ( pEXT_FUNCTION pL_VECENUMOBJECTSINGROUP)( pVECTORHANDLE pVector, const pVECTORGROUP pGroup, pVECTORENUMOBJECTSPROC pEnumProc, L_VOID L_FAR *pUserData, L_UINT32 dwFlags );
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Event functions.                                                     []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
typedef L_INT ( pEXT_FUNCTION pL_VECSETEVENTCALLBACK)( pVECTORHANDLE pVector, pVECTOREVENTPROC pProc, L_VOID L_FAR *pUserData, ppVECTOREVENTPROC pOldProc, L_VOID L_FAR **pOldUserData );
typedef L_INT ( pEXT_FUNCTION pL_VECEVENT)( pVECTORHANDLE, pVECTOREVENT );



//-----------------------------------------------------------------------------
//--LVDLG.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------
typedef L_INT ( pEXT_FUNCTION pL_VECDLGROTATE )( HWND hWnd, pVECTORHANDLE pVector, pVECTORPOINT pRotation, const pVECTORPOINT pOrigin, L_UINT32 dwFlags, LVCOMMDLGHELPCB pfnCallback, L_VOID *pUserData );
typedef L_INT ( pEXT_FUNCTION pL_VECDLGSCALE )( HWND hWnd, pVECTORHANDLE pVector, pVECTORPOINT pScale, const pVECTORPOINT pOrigin, L_UINT32 dwFlags, LVCOMMDLGHELPCB pfnCallback, L_VOID *pUserData );
typedef L_INT ( pEXT_FUNCTION pL_VECDLGTRANSLATE )( HWND hWnd, pVECTORHANDLE pVector, pVECTORPOINT pTranslation, L_UINT32 dwFlags, LVCOMMDLGHELPCB pfnCallback, L_VOID *pUserData );
typedef L_INT ( pEXT_FUNCTION pL_VECDLGCAMERA )( HWND hWnd, pVECTORHANDLE pVector, pVECTORCAMERA pCamera, L_UINT32 dwFlags, LVCOMMDLGHELPCB pfnCallback, L_VOID *pUserData );
typedef L_INT ( pEXT_FUNCTION pL_VECDLGRENDER )( HWND hWnd, pVECTORHANDLE pVector, L_BOOL L_FAR *pbUseLights, COLORREF L_FAR *pColorAmbient, L_INT L_FAR *pnPolygonMode, L_UINT32 dwFlags, LVCOMMDLGHELPCB pfnCallback, L_VOID *pUserData );
typedef L_INT ( pEXT_FUNCTION pL_VECDLGVIEWMODE )( HWND hWnd, pVECTORHANDLE pVector, L_INT L_FAR *pnViewMode, L_UINT32 dwFlags, LVCOMMDLGHELPCB pfnCallback, L_VOID *pUserData );
typedef L_INT ( pEXT_FUNCTION pL_VECDLGHITTEST )( HWND hWnd, pVECTORHANDLE pVector, pVECTORHITTEST pHitTest, L_UINT32 dwFlags, LVCOMMDLGHELPCB pfnCallback, L_VOID *pUserData );
typedef L_INT ( pEXT_FUNCTION pL_VECDLGEDITALLLAYERS )( HWND hWnd, pVECTORHANDLE pVector, L_UINT32 dwFlags, LVCOMMDLGHELPCB pfnCallback, L_VOID *pUserData );
typedef L_INT ( pEXT_FUNCTION pL_VECDLGNEWLAYER )( HWND hWnd, pVECTORHANDLE pVector, pVECTORLAYERDESC pLayerDesc, pVECTORLAYER pLayer, L_BOOL L_FAR *pbActiveLayer, L_UINT32 dwFlags, LVCOMMDLGHELPCB pfnCallback, L_VOID *pUserData );
typedef L_INT ( pEXT_FUNCTION pL_VECDLGEDITLAYER )( HWND hWnd, pVECTORHANDLE pVector, pVECTORLAYER pLayer, pVECTORLAYERDESC pLayerDesc, L_BOOL L_FAR *pbActiveLayer, L_UINT32 dwFlags, LVCOMMDLGHELPCB pfnCallback, L_VOID *pUserData );
typedef L_INT ( pEXT_FUNCTION pL_VECDLGEDITALLGROUPS )( HWND hWnd, pVECTORHANDLE pVector, L_UINT32 dwFlags, LVCOMMDLGHELPCB pfnCallback, L_VOID *pUserData );
typedef L_INT ( pEXT_FUNCTION pL_VECDLGNEWGROUP )( HWND hWnd, pVECTORHANDLE pVector, pVECTORGROUPDESC pGroupDesc, pVECTORGROUP pGroup, L_UINT32 dwFlags, LVCOMMDLGHELPCB pfnCallback, L_VOID *pUserData );
typedef L_INT ( pEXT_FUNCTION pL_VECDLGEDITGROUP )( HWND hWnd, pVECTORHANDLE pVector, pVECTORGROUP pGroup, pVECTORGROUPDESC pGroupDesc, L_UINT32 dwFlags, LVCOMMDLGHELPCB pfnCallback, L_VOID *pUserData );
typedef L_INT ( pEXT_FUNCTION pL_VECDLGNEWOBJECT )( HWND hWnd, pVECTORHANDLE pVector, const pVECTORLAYER pLayer, L_INT nType, L_VOID L_FAR *pObjectDesc, pVECTOROBJECT, L_UINT32 dwFlags, LVCOMMDLGHELPCB pfnCallback, L_VOID *pUserData );
typedef L_INT ( pEXT_FUNCTION pL_VECDLGEDITOBJECT )( HWND hWnd, pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_INT nType, L_VOID L_FAR *pObjectDesc, L_UINT32 dwFlags, LVCOMMDLGHELPCB pfnCallback, L_VOID *pUserData );
typedef L_INT ( pEXT_FUNCTION pL_VECDLGOBJECTATTRIBUTES )( HWND hWnd, pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_BOOL *pbSelected, L_INT *pnROP, pVECTORPEN pPen, pVECTORBRUSH pBrush, pVECTORFONT pFont, L_UINT32 dwFlags, LVCOMMDLGHELPCB pfnCallback, L_VOID *pUserData );
typedef L_INT ( pEXT_FUNCTION pL_VECDLGGETSTRINGLEN )( L_UINT32 uString, L_UINT L_FAR *puLen );
typedef L_INT ( pEXT_FUNCTION pL_VECDLGGETSTRING )( L_UINT32 uString, L_CHAR L_FAR *pszString );
typedef L_INT ( pEXT_FUNCTION pL_VECDLGSETSTRING )( L_UINT32 uString, const L_CHAR L_FAR *pszString );
typedef HFONT ( pEXT_FUNCTION pL_VECDLGSETFONT )( HFONT hFont );

//-----------------------------------------------------------------------------
//--LTBAR.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------
typedef L_INT ( pEXT_FUNCTION pL_BARCODEREAD)(pBITMAPHANDLE        pBitmap,
                                 RECT L_FAR *         prcSearch,
                                 L_UINT32             ulSearchType,
                                 L_INT                nUnits,
                                 L_UINT32             ulFlags,
                                 L_INT                nMultipleMaxCount,
                                 pBARCODE1D           pBarCode1D,
                                 pBARCODEREADPDF      pBarCodePDF,
                                 pBARCODECOLOR        pBarCodeColor,
                                 pBARCODEDATA L_FAR * ppBarCodeData);
typedef L_INT ( pEXT_FUNCTION pL_BARCODEWRITE)(pBITMAPHANDLE        pBitmap,
                                  pBARCODEDATA         pBarCodeData,
                                  pBARCODECOLOR        pBarCodeColor,
                                  L_UINT32             ulFlags,
                                  pBARCODE1D           pBarCode1D,
                                  pBARCODEWRITECODEONE pBarCode2D,
                                  pBARCODEWRITEPDF     pBarCodePDF,
                                  LPRECT               lprcSize);
typedef L_VOID ( pEXT_FUNCTION pL_BARCODEFREE)(pBARCODEDATA L_FAR * ppBarCodeData);
typedef L_BOOL ( pEXT_FUNCTION pL_BARCODEISDUPLICATED)(pBARCODEDATA pBarCodeDataItem);
typedef L_INT ( pEXT_FUNCTION pL_BARCODEGETDUPLICATED)(pBARCODEDATA pBarCodeDataItem);
typedef L_INT ( pEXT_FUNCTION pL_BARCODEGETFIRSTDUPLICATED)(pBARCODEDATA pBarCodeData,
                                               L_INT        nIndex);
typedef L_INT ( pEXT_FUNCTION pL_BARCODEGETNEXTDUPLICATED)(pBARCODEDATA pBarCodeData,
                                              L_INT        nCurIndex);
typedef L_INT ( pEXT_FUNCTION pL_BARCODEINIT )(L_INT nMajorType);
typedef L_VOID ( pEXT_FUNCTION pL_BARCODEEXIT )(L_VOID);
typedef L_INT  ( pEXT_FUNCTION pL_BARCODEVERSIONINFO)(pBARCODEVERSION pBarCodeVersion);

typedef L_INT ( pEXT_FUNCTION pL_BARCODEWRITEEXT)(pBITMAPHANDLE        pBitmap,
                                  pBARCODEDATA         pBarCodeData,
                                  pBARCODECOLOR        pBarCodeColor,
                                  L_UINT32             ulFlags,
                                  pBARCODE1D           pBarCode1D,
                                  pBARCODEWRITEPDF     pBarCodePDF,
                                  pBARCODEWRITEDM      pBarCodeDM,
                                  LPRECT               lprcSize);

//-----------------------------------------------------------------------------
//--LTAUT.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------


// General functions.
typedef L_INT ( pEXT_FUNCTION pL_AUTISVALID            )( pAUTOMATIONHANDLE pAutomation ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTINIT               )( ppAUTOMATIONHANDLE ppAutomation ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTCREATE             )( pAUTOMATIONHANDLE pAutomation, AUTOMATIONMODE nMode, L_UINT32 dwFlags ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTFREE               )( pAUTOMATIONHANDLE pAutomation ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTSETUNDOLEVEL       )( pAUTOMATIONHANDLE pAutomation, L_UINT uLevel ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTGETUNDOLEVEL       )( pAUTOMATIONHANDLE pAutomation, L_UINT *puLevel ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTCANUNDO            )( pAUTOMATIONHANDLE pAutomation, L_BOOL *pfCanUndo ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTCANREDO            )( pAUTOMATIONHANDLE pAutomation, L_BOOL *pfCanRedo ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTUNDO               )( pAUTOMATIONHANDLE pAutomation, L_UINT32 dwFlags ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTREDO               )( pAUTOMATIONHANDLE pAutomation, L_UINT32 dwFlags ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTSETUNDOENABLED     )( pAUTOMATIONHANDLE pAutomation, L_BOOL bEnabled );
typedef L_INT ( pEXT_FUNCTION pL_AUTADDUNDONODE        )( pAUTOMATIONHANDLE pAutomation, L_UINT32 dwFlags );
typedef L_INT ( pEXT_FUNCTION pL_AUTSELECT             )( pAUTOMATIONHANDLE pAutomation, AUTOMATIONSELECT nSelect, L_UINT32 dwFlags ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTCLIPBOARDDATAREADY )( pAUTOMATIONHANDLE pAutomation, L_BOOL *pfReady ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTCUT                )( pAUTOMATIONHANDLE pAutomation, L_UINT32 dwFlags ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTCOPY               )( pAUTOMATIONHANDLE pAutomation, L_UINT32 dwFlags ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTPASTE              )( pAUTOMATIONHANDLE pAutomation, L_UINT32 dwFlags ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTDELETE             )( pAUTOMATIONHANDLE pAutomation, L_UINT32 dwFlags ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTPRINT              )( pAUTOMATIONHANDLE pAutomation, L_UINT32 dwFlags ) ;

// Container Functions.
typedef L_INT ( pEXT_FUNCTION pL_AUTADDCONTAINER       )( pAUTOMATIONHANDLE pAutomation, pCONTAINERHANDLE pContainer , L_VOID L_FAR *pModeData ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTREMOVECONTAINER    )( pAUTOMATIONHANDLE pAutomation, pCONTAINERHANDLE pContainer ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTSETACTIVECONTAINER )( pAUTOMATIONHANDLE pAutomation, pCONTAINERHANDLE pContainer ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTGETACTIVECONTAINER )( pAUTOMATIONHANDLE pAutomation, pCONTAINERHANDLE *ppContainer ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTENUMCONTAINERS     )( pAUTOMATIONHANDLE pAutomation, pAUTOMATIONENUMCONTAINERPROC pEnumProc, L_VOID L_FAR *pUserData ) ;

// Painting Functionts.
typedef L_INT ( pEXT_FUNCTION pL_AUTSETPAINTPROPERTY  )( pAUTOMATIONHANDLE pAutomation, PAINTGROUP nGroup, const L_VOID L_FAR *pProperty ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTGETPAINTPROPERTY  )( pAUTOMATIONHANDLE pAutomation, PAINTGROUP nGroup, L_VOID L_FAR *pProperty ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTSETPAINTBKCOLOR   )( pAUTOMATIONHANDLE pAutomation, COLORREF rcBKColor ) ;
typedef L_INT ( pEXT_FUNCTION pL_AUTGETPAINTBKCOLOR   )( pAUTOMATIONHANDLE pAutomation, COLORREF *prcBKColor ) ;

// Vector Functions.
typedef L_INT ( pEXT_FUNCTION pL_AUTSETVECTORPROPERTY)( pAUTOMATIONHANDLE pAutomation, const pAUTOMATIONVECTORPROPERTIES );
typedef L_INT ( pEXT_FUNCTION pL_AUTGETVECTORPROPERTY)( const pAUTOMATIONHANDLE pAutomation, pAUTOMATIONVECTORPROPERTIES );
typedef L_INT ( pEXT_FUNCTION pL_AUTEDITVECTOROBJECT)( pAUTOMATIONHANDLE, const pVECTOROBJECT );

//Toolbar Functions.
typedef L_INT ( pEXT_FUNCTION pL_AUTSETTOOLBAR )( pAUTOMATIONHANDLE pAutomation, pTOOLBARHANDLE pToolbar );
typedef L_INT ( pEXT_FUNCTION pL_AUTGETTOOLBAR )( pAUTOMATIONHANDLE pAutomation, pTOOLBARHANDLE *ppToolbar ) ;

typedef L_INT ( pEXT_FUNCTION pL_AUTSETCURRENTTOOL)( pAUTOMATIONHANDLE pAutomation, L_INT nTool );
typedef L_INT ( pEXT_FUNCTION pL_AUTGETCURRENTTOOL)( pAUTOMATIONHANDLE pAutomation, L_INT *pnTool );

//-----------------------------------------------------------------------------
//--LTCON.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------
// general container operations funtions.
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERISVALID         )( pCONTAINERHANDLE  pContainer ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERINIT            )( ppCONTAINERHANDLE ppContainer ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERCREATE          )( pCONTAINERHANDLE  pContainer, HWND hwndOwner ) ;
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERFREE            )( pCONTAINERHANDLE  pContainer ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERUPDATE          )( pCONTAINERHANDLE  pContainer, LPRECT prcPaint ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERRESET           )( pCONTAINERHANDLE  pContainer ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINEREDITOBJECT      )( pCONTAINERHANDLE  pContainer, const pCONTAINEROBJECTDATA pObjectData ) ;
   
   // setting functions.
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERSETOWNER        )( pCONTAINERHANDLE pContainer, HWND hWndOwner ) ;
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERSETMETRICS      )( pCONTAINERHANDLE pContainer, pCONTAINERMETRICS pMetrics ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERSETOFFSET       )( pCONTAINERHANDLE pContainer, L_INT nXOffset, L_INT nYOffset, L_INT nZOffset ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERSETSCALAR       )( pCONTAINERHANDLE pContainer, pVECTORPOINT pvptScalarNum, pVECTORPOINT pvptScalarDen ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERSETOBJECTTYPE   )( pCONTAINERHANDLE pContainer, CONTAINEROBJECTTYPE nObjectType ) ;
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERSETOBJECTCURSOR )( pCONTAINERHANDLE pContainer, CONTAINEROBJECTTYPE nObjectType, HCURSOR hCursor ) ;
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERSETENABLED      )( pCONTAINERHANDLE pContainer, L_BOOL fEnable ) ;
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERSETCALLBACK     )( pCONTAINERHANDLE pContainer, const pCONTAINERCALLBACK pCallback, L_VOID L_FAR *pUserData ) ;
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERSETOWNERDRAW    )( pCONTAINERHANDLE pContainer, L_BOOL fOwnerDraw, L_UINT32 dwFlags ) ;
   
   // getting functions.
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERGETOWNER        )( pCONTAINERHANDLE pContainer, HWND* phwndOwner ) ;
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERGETMETRICS      )( pCONTAINERHANDLE pContainer, pCONTAINERMETRICS pMetrics ) ;
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERGETOFFSET       )( pCONTAINERHANDLE pContainer, L_INT *pnXOffset, L_INT *pnYOffset, L_INT *pnZOffset ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERGETSCALAR       )( pCONTAINERHANDLE pContainer, pVECTORPOINT pvptScalarNum, pVECTORPOINT pvptScalarDen ) ;
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERGETOBJECTTYPE   )( pCONTAINERHANDLE pContainer, pCONTAINEROBJECTTYPE pnObjectType ) ;
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERGETOBJECTCURSOR )( pCONTAINERHANDLE pContainer, CONTAINEROBJECTTYPE nObjectType, HCURSOR* phCursor ) ;
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERGETCALLBACK     )( pCONTAINERHANDLE pContainer, pCONTAINERCALLBACK *ppCallback, L_VOID L_FAR **ppUserData ) ;
   
   // status query functions.
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERISENABLED   )( pCONTAINERHANDLE pContainer, L_BOOL* pfEnabled ) ;
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERISOWNERDRAW )( pCONTAINERHANDLE pContainer, L_BOOL* pfOwnerDraw ) ;
   
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERSETAUTOMATIONCALLBACK )( pCONTAINERHANDLE pContainer, const pCONTAINERCALLBACK pAutomationCallback, L_VOID L_FAR *pAutomationData ) ;
   typedef L_INT ( pEXT_FUNCTION pL_SCREENTOCONTAINER              )( pCONTAINERHANDLE pContainer, LPPOINT pptPoint ) ;
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERTOSCREEN              )( pCONTAINERHANDLE pContainer, LPPOINT pptPoint ) ;
   typedef L_INT ( pEXT_FUNCTION pL_CONTAINERENABLEUPDATE          )( pCONTAINERHANDLE pContainer, L_BOOL fEnableUpdate ) ;
   
//-----------------------------------------------------------------------------
//--LTPNT.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------
typedef L_INT ( pEXT_FUNCTION pL_PNTISVALID           )( pPAINTHANDLE pPaint ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTINIT              )( ppPAINTHANDLE ppPaint ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTFREE              )( pPAINTHANDLE pPaint ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTSETPROPERTY       )( pPAINTHANDLE pPaint, PAINTGROUP nGroup, const L_VOID L_FAR *pProperty ) ;
   typedef L_INT ( pEXT_FUNCTION pL_PNTGETPROPERTY       )( pPAINTHANDLE pPaint, PAINTGROUP nGroup, const L_VOID L_FAR *pProperty ) ;
   typedef L_INT ( pEXT_FUNCTION pL_PNTSETMETRICS        )( pPAINTHANDLE pPaint, HDC UserDC, pBITMAPHANDLE pBitmap, HPALETTE hRestrictionPalette ) ;
   typedef L_INT ( pEXT_FUNCTION pL_PNTSETTRANSFORMATION )( pPAINTHANDLE pPaint, pPAINTXFORM pXForm ) ;
   typedef L_INT ( pEXT_FUNCTION pL_PNTGETTRANSFORMATION )( pPAINTHANDLE pPaint, pPAINTXFORM pXForm ) ;
   typedef L_INT ( pEXT_FUNCTION pL_PNTSETDCEXTENTS      )( pPAINTHANDLE pPaint, const LPRECT prcRect ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTGETDCEXTENTS      )( pPAINTHANDLE pPaint, LPRECT prcRect ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTSETCLIPRGN        )( pPAINTHANDLE pPaint, HRGN hClipRng ) ;

   typedef L_INT ( pEXT_FUNCTION pL_PNTGETCLIPRGN        )( pPAINTHANDLE pPaint, pHRGN phClipRng ) ; 
   
   typedef L_INT ( pEXT_FUNCTION pL_PNTOFFSETCLIPRGN     )( pPAINTHANDLE pPaint, L_INT nDX, L_INT nDY ) ;
   
   // brush fucntions.
   typedef L_INT ( pEXT_FUNCTION pL_PNTBRUSHMOVETO )( pPAINTHANDLE pPaint, HDC UserDC, L_INT nX, L_INT nY ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTBRUSHLINETO )( pPAINTHANDLE pPaint, HDC UserDC, L_INT nX, L_INT nY ) ; 
   
   // shape functions.
   typedef L_INT ( pEXT_FUNCTION pL_PNTDRAWSHAPELINE       )( pPAINTHANDLE pPaint, HDC UserDC, L_INT nXStart, L_INT nYStart, L_INT nEndX, L_INT nEndY ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTDRAWSHAPERECTANGLE  )( pPAINTHANDLE pPaint, HDC UserDC, const LPRECT prcRect ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTDRAWSHAPEROUNDRECT  )( pPAINTHANDLE pPaint, HDC UserDC, const LPRECT prcRect ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTDRAWSHAPEELLIPSE    )( pPAINTHANDLE pPaint, HDC UserDC, const LPRECT prcRect ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTDRAWSHAPEPOLYGON    )( pPAINTHANDLE pPaint, HDC UserDC, const LPPOINT pptPoints, L_INT nCount ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTDRAWSHAPEPOLYBEZIER )( pPAINTHANDLE pPaint, HDC UserDC, const LPPOINT pptPoints, L_INT nCount ) ; 
   
   // region functions.
   typedef L_INT ( pEXT_FUNCTION pL_PNTREGIONRECT      )( pPAINTHANDLE pPaint, HDC UserDC, const LPRECT prcRect, pHRGN phDestRgn ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTREGIONROUNDRECT )( pPAINTHANDLE pPaint, HDC UserDC, const LPRECT prcRect, pHRGN phDestRgn ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTREGIONELLIPSE   )( pPAINTHANDLE pPaint, HDC UserDC, const LPRECT prcRect, pHRGN phDestRgn ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTREGIONPOLYGON   )( pPAINTHANDLE pPaint, HDC UserDC, const LPPOINT pptPoints, L_INT nCount, pHRGN phDestRgn ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTREGIONSURFACE   )( pPAINTHANDLE pPaint, HDC UserDC, const LPPOINT pptPoint, pHRGN phDestRgn ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTREGIONBORDER    )( pPAINTHANDLE pPaint, HDC UserDC, const LPPOINT pptPoint, const COLORREF crBorderColor, pHRGN phDestRgn ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTREGIONCOLOR     )( pPAINTHANDLE pPaint, HDC UserDC, const COLORREF crColor, pHRGN phDestRgn ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTREGIONTRANSLATE )( pPAINTHANDLE pPaint, L_INT dx, L_INT dy, pHRGN phRgn ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTREGIONSCALE     )( pPAINTHANDLE pPaint, L_INT nHScaleFactor, L_INT nVScaleFactor, PAINTALIGNMENT nAlignment, pHRGN phDestRgn ) ; 
   
   // fill functions.
   typedef L_INT ( pEXT_FUNCTION pL_PNTFILLSURFACE      )( pPAINTHANDLE pPaint, HDC UserDC, const LPPOINT pptPoint ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTFILLBORDER       )( pPAINTHANDLE pPaint, HDC UserDC, const LPPOINT pptPoint, const COLORREF crBorderColor ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_PNTFILLCOLORREPLACE )( pPAINTHANDLE pPaint, HDC UserDC, const COLORREF crColor ) ; 
   
   // text functions.
   typedef L_INT ( pEXT_FUNCTION pL_PNTAPPLYTEXT )( pPAINTHANDLE pPaint, HDC UserDC, const LPRECT prcRect ) ; 
   
   // paint helping functions.
   typedef L_INT ( pEXT_FUNCTION pL_PNTPICKCOLOR )( pPAINTHANDLE pPaint, HDC UserDC, L_INT nX, L_INT nY, COLORREF* pcrDestColor ) ;
   
//-----------------------------------------------------------------------------
//--LTTLB.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------
//{DOCUMENTED FUNCTIONS

   // general toolbar operations funtions.
   typedef L_INT ( pEXT_FUNCTION pL_TBISVALID         )( pTOOLBARHANDLE pToolbar ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_TBINIT            )( ppTOOLBARHANDLE ppToolbar ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_TBFREE            )( pTOOLBARHANDLE pToolbar ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_TBCREATE          )( pTOOLBARHANDLE pToolbar, HWND hwndParent, LPCSTR szTitle, L_UINT32 dwFlags ) ;
   typedef L_INT ( pEXT_FUNCTION pL_TBFREETOOLBARINFO )( pTOOLBARHANDLE pToolbar, pLTOOLBARINFO pToolbarInfo ) ;

   // status query functions.
   typedef L_INT ( pEXT_FUNCTION pL_TBISVISIBLE       )( pTOOLBARHANDLE pToolbar, L_BOOL *pfVisible ) ;
   typedef L_INT ( pEXT_FUNCTION pL_TBISBUTTONENABLED )( pTOOLBARHANDLE pToolbar, L_UINT uButtonID, L_BOOL *pfEnable ) ;
   typedef L_INT ( pEXT_FUNCTION pL_TBISBUTTONVISIBLE )( pTOOLBARHANDLE pToolbar, L_UINT uButtonID, L_BOOL *pfVisible ) ;

   // setting functions.
   typedef L_INT ( pEXT_FUNCTION pL_TBSETVISIBLE       )( pTOOLBARHANDLE pToolbar, L_BOOL fVisible ) ; 
   typedef L_INT ( pEXT_FUNCTION pL_TBSETPOSITION      )( pTOOLBARHANDLE pToolbar, LPPOINT lpptPos, L_UINT32 dwFlags ) ;
   typedef L_INT ( pEXT_FUNCTION pL_TBSETROWS          )( pTOOLBARHANDLE pToolbar, L_INT nRows ) ;
   typedef L_INT ( pEXT_FUNCTION pL_TBSETBUTTONCHECKED )( pTOOLBARHANDLE pToolbar, L_UINT uButtonID ) ;
   typedef L_INT ( pEXT_FUNCTION pL_TBSETBUTTONENABLED )( pTOOLBARHANDLE pToolbar, L_UINT uButtonID, L_BOOL fEnable ) ;
   typedef L_INT ( pEXT_FUNCTION pL_TBSETBUTTONVISIBLE )( pTOOLBARHANDLE pToolbar, L_UINT uButtonID, L_BOOL fVisible ) ;
   typedef L_INT ( pEXT_FUNCTION pL_TBSETTOOLBARINFO   )( pTOOLBARHANDLE pToolbar, pLTOOLBARINFO pToolbarInfo ) ;
   typedef L_INT ( pEXT_FUNCTION pL_TBSETCALLBACK      )( pTOOLBARHANDLE pToolbar, const pTOOLBARCALLBACK pCallback, L_VOID L_FAR *pUserData ) ;

   // getting functions.
   typedef L_INT ( pEXT_FUNCTION pL_TBGETPOSITION      )( pTOOLBARHANDLE pToolbar, LPPOINT lpptPos, L_UINT32 dwFlags ) ;
   typedef L_INT ( pEXT_FUNCTION pL_TBGETROWS          )( pTOOLBARHANDLE pToolbar, L_INT *pnRows ) ;
   typedef L_INT ( pEXT_FUNCTION pL_TBGETBUTTONCHECKED )( pTOOLBARHANDLE pToolbar, L_INT *pnChecked ) ;
   typedef L_INT ( pEXT_FUNCTION pL_TBGETTOOLBARINFO   )( pTOOLBARHANDLE pToolbar, pLTOOLBARINFO pToolbarInfo ) ;
   typedef L_INT ( pEXT_FUNCTION pL_TBGETCALLBACK      )( pTOOLBARHANDLE pToolbar, pTOOLBARCALLBACK *ppCallback, L_VOID L_FAR **ppUserData ) ;

   // new functions
   typedef L_INT ( pEXT_FUNCTION pL_TBADDBUTTON)( pTOOLBARHANDLE pToolbar, L_UINT uButtonRefId, const pLBUTTONINFO pButtonInfo, L_UINT32 dwFlags );
   typedef L_INT ( pEXT_FUNCTION pL_TBREMOVEBUTTON)( pTOOLBARHANDLE pToolbar, L_UINT uButtonId );
   typedef L_INT ( pEXT_FUNCTION pL_TBGETBUTTONINFO)( const pTOOLBARHANDLE pToolbar, L_UINT uButtonId, pLBUTTONINFO pButtonInfo );
   typedef L_INT ( pEXT_FUNCTION pL_TBSETBUTTONINFO)( pTOOLBARHANDLE pToolbar, L_UINT uButtonId, const pLBUTTONINFO pButtonInfo );

   typedef L_INT ( pEXT_FUNCTION pL_TBSETAUTOMATIONCALLBACK )( pTOOLBARHANDLE pToolbar, const pTOOLBARCALLBACK pAutomationCallback, L_VOID L_FAR *pAutomationData ) ;

//-----------------------------------------------------------------------------
//--LTPDG.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------
   typedef L_INT ( pEXT_FUNCTION pL_PNTDLGBRUSH )( HWND hWnd, pPAINTDLGBRUSHINFO  pBrushDlgInfo ) ;
   typedef L_INT ( pEXT_FUNCTION pL_PNTDLGSHAPE )( HWND hWnd, pPAINTDLGSHAPEINFO  pShapeDlgInfo ) ;
   typedef L_INT ( pEXT_FUNCTION pL_PNTDLGREGION)( HWND hWnd, pPAINTDLGREGIONINFO pRegionDlgInfo) ;
   typedef L_INT ( pEXT_FUNCTION pL_PNTDLGFILL  )( HWND hWnd, pPAINTDLGFILLINFO   pFillDlgInfo  ) ;
   typedef L_INT ( pEXT_FUNCTION pL_PNTDLGTEXT  )( HWND hWnd, pPAINTDLGTEXTINFO   pTextDlgInfo  ) ;

//-----------------------------------------------------------------------------
//--LTSGM.H FUNCTIONS PROTOTYPES-----------------------------------------------
//-----------------------------------------------------------------------------
   typedef L_INT (pEXT_FUNCTION pL_MRCSTARTBITMAPSEGMENTATION) (pHSEGMENTATION phSegment, L_INT nWidth, L_INT nHeight, COLORREF clrBackground, COLORREF clrForeground);
   typedef L_INT (pEXT_FUNCTION pL_MRCENDBITMAPSEGMENTATION) (HSEGMENTATION hSegment);
   typedef L_INT (pEXT_FUNCTION pL_MRCSEGMENTBITMAP) (HSEGMENTATION hSegment, pBITMAPHANDLE pBitmap, pMINSEGMENT pMinSeg, L_UINT32 uSegFactor, pSEGMENTATIONCALLBACK pfnCallback, L_VOID L_FAR * pUserData);
   typedef L_INT (pEXT_FUNCTION pL_MRCSETNEWSTRIPE) (HSEGMENTATION hSegment, L_INT nStripeStartRow, L_INT nStripeEndRow);
   typedef L_INT (pEXT_FUNCTION pL_MRCSETSTRIPESEGMENT) (HSEGMENTATION hSegment, L_INT nStripeIndex, pSEGMENTDATA pSegment);
   typedef L_INT (pEXT_FUNCTION pL_MRCSETSTRIPEMAXHEIGHT) (HSEGMENTATION hSegment, L_INT nStripeMaxHeight);
   typedef L_INT (pEXT_FUNCTION pL_MRCENUMSEGMENTS) (HSEGMENTATION hSegment, pMRCENUMSEGMENTSPROC pEnumProc, L_VOID L_FAR * pUserData, L_UINT32 dwFlags);
   typedef L_INT (pEXT_FUNCTION pL_MRCUPDATESEGMENTDATA) (HSEGMENTATION hSegment, L_INT nSegId, pSEGMENTDATA pSegmentData, L_BOOL bVerifyUpdate);
   typedef L_INT (pEXT_FUNCTION pL_MRCDELETESEGMENT) (HSEGMENTATION hSegment, L_INT nSegId);
   typedef L_INT (pEXT_FUNCTION pL_MRCSAVEBITMAP) (HSEGMENTATION hSegment, pBITMAPHANDLE pBitmap, pCOMPRESSIONOPTIONS pCmpOption, L_CHAR L_FAR * pszFileName, FILESAVECALLBACK pfnCallback, L_VOID L_FAR * pUserData);
   typedef L_INT (pEXT_FUNCTION pL_MRCSAVEBITMAPT44) (HSEGMENTATION hSegment, pBITMAPHANDLE pBitmap, pCOMPRESSIONOPTIONS pCmpOption, L_CHAR L_FAR * pszFileName, FILESAVECALLBACK pfnCallback, L_VOID L_FAR * pUserData);
   typedef L_INT (pEXT_FUNCTION pL_MRCLOADBITMAP) (L_CHAR L_FAR * pszFileName, pBITMAPHANDLE pBitmap, L_INT nPageNo, FILEREADCALLBACK pfnCallback, L_VOID L_FAR * pUserData);
   typedef L_INT (pEXT_FUNCTION pL_MRCGETPAGESCOUNT) (L_CHAR L_FAR * pszFileName, L_INT * pnPages);


#endif //USE_POINTERS_TO_LEAD_FUNCTIONS

#endif //_LEAD_FUNCTIONS_TYPEDEFINES_H_
/*================================================================= EOF =====*/
