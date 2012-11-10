/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright(c) 1991-2000 LEAD Technologies, Inc.                              |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : tcprnt.h                                                        |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_FUNCTIONS_MACROS_H_
#define  _LEAD_FUNCTIONS_MACROS_H_

/*----------------------------------------------------------------------------+
| MACROS                                                                      |
+----------------------------------------------------------------------------*/
#ifdef USE_POINTERS_TO_LEAD_FUNCTIONS

//-----------------------------------------------------------------------------
//--LTKRN.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
#define L_ACCESSBITMAP(pBitmap)      \
   ((pL_AccessBitmap)? pL_AccessBitmap(pBitmap):LBase::RecordError(WRPERR_LTKRN_DLL_NOT_LOADED))

#define L_ALLOCATEBITMAP(pBitmap,nMemoryType)   \
   ((pL_AllocateBitmap)? pL_AllocateBitmap(pBitmap,nMemoryType):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_CHANGEBITMAPHEIGHT(pBitmap,nHeight)   \
   ((pL_ChangeBitmapHeight)? pL_ChangeBitmapHeight(pBitmap,nHeight):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_CHANGEBITMAPVIEWPERSPECTIVE(pDstBitmap,pSrcBitmap,ViewPerspective)  \
   ((pL_ChangeBitmapViewPerspective)? pL_ChangeBitmapViewPerspective(pDstBitmap,pSrcBitmap,ViewPerspective):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_CHANGEFROMDIB(pBitmap,hDIB)  \
   ((pL_ChangeFromDIB)? pL_ChangeFromDIB(pBitmap,hDIB):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_CHANGETODIB(pBitmap)   \
   ((pL_ChangeToDIB)? pL_ChangeToDIB(pBitmap):(LBase::RecordError(WRPERR_LTKRN_DLL_NOT_LOADED),(HGLOBAL)0))

#define L_CLEARBITMAP(pBitmap)   \
   ((pL_ClearBitmap)? pL_ClearBitmap(pBitmap):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_CLEARNEGATIVEPIXELS(pBitmap) \
   ((pL_ClearNegativePixels)? pL_ClearNegativePixels(pBitmap):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_COLORRESBITMAP(pBitmapSrc,pBitmapDst,nBitsPerPixel,uFlags,pPalette,hPalette,uColors,pfnCallback,pUserData) \
   ((pL_ColorResBitmap)? pL_ColorResBitmap(pBitmapSrc,pBitmapDst,nBitsPerPixel,uFlags,pPalette,hPalette,uColors,pfnCallback,pUserData):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_COLORRESBITMAPLIST(hList,nBitsPerPixel,uFlags,pPalette,hPalette,uColors)  \
   ((pL_ColorResBitmapList)? pL_ColorResBitmapList(hList,nBitsPerPixel,uFlags,pPalette,hPalette,uColors):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_COMBINEBITMAP(pBitmapDst,nXDst,nYDst,nWidth,nHeight,pBitmapSrc,nXSrc,nYSrc,uFlags) \
   ((pL_CombineBitmap)? pL_CombineBitmap(pBitmapDst,nXDst,nYDst,nWidth,nHeight,pBitmapSrc,nXSrc,nYSrc,uFlags):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_COMBINEBITMAPWARP(pBitmapDst,nDst,pBitmapSrc,nSrc,nSrcWidth,nSrcHeight,uFlags) \
   ((pL_CombineBitmapWarp)? pL_CombineBitmapWarp(pBitmapDst,nDst,pBitmapSrc,nSrc,nSrcWidth,nSrcHeight,uFlags):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_COMPRESSROW(pRunBuffer,pBuffer,nCol,nWidth) \
   ((pL_CompressRow)? pL_CompressRow(pRunBuffer,pBuffer,nCol,nWidth):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_COMPRESSROWS(pRunBuffer,pBuffer,nWidth,nRows)  \
   ((pL_CompressRows)? pL_CompressRows(pRunBuffer,pBuffer,nWidth,nRows):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_CONVERTBUFFER(pBuffer,nWidth,nBitsPerPixelSrc,nBitsPerPixelDst,nOrderSrc,nOrderDst,pPaletteSrc,pPaletteDst)   \
   ((pL_ConvertBuffer)? pL_ConvertBuffer(pBuffer,nWidth,nBitsPerPixelSrc,nBitsPerPixelDst,nOrderSrc,nOrderDst,pPaletteSrc,pPaletteDst):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_CONVERTBUFFEREXT(pBuffer,nWidth,nBitsPerPixelSrc,nBitsPerPixelDst,nOrderSrc,nOrderDst,pPaletteSrc,pPaletteDst,uFlags,uLowBit,uHighBit)   \
   ((pL_ConvertBufferExt)? pL_ConvertBufferExt(pBuffer,nWidth,nBitsPerPixelSrc,nBitsPerPixelDst,nOrderSrc,nOrderDst,pPaletteSrc,pPaletteDst,uFlags,uLowBit,uHighBit):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_CONVERTFROMDIB(pBitmap,pInfo,pBits)   \
   ((pL_ConvertFromDIB)? pL_ConvertFromDIB(pBitmap,pInfo,pBits):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_CONVERTTODIB(pBitmap)  \
   ((pL_ConvertToDIB)? pL_ConvertToDIB(pBitmap):(LBase::RecordError(WRPERR_LTKRN_DLL_NOT_LOADED),(HGLOBAL)0))

#define L_COPYBITMAP(pBitmapDst,pBitmapSrc)  \
   ((pL_CopyBitmap)? pL_CopyBitmap(pBitmapDst,pBitmapSrc):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_COPYBITMAPDATA(pBitmapDst,pBitmapSrc) \
   ((pL_CopyBitmapData)? pL_CopyBitmapData(pBitmapDst,pBitmapSrc):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_COPYBITMAPHANDLE(pBitmapDst,pBitmapSrc)  \
   ((pL_CopyBitmapHandle)? pL_CopyBitmapHandle(pBitmapDst,pBitmapSrc):LBase::RecordError(WRPERR_LTKRN_DLL_NOT_LOADED))

#define L_COPYBITMAPLISTITEMS(phList,hList,uIndex,uCount)   \
   ((pL_CopyBitmapListItems)? pL_CopyBitmapListItems(phList,hList,uIndex,uCount):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_COPYBITMAPRECT(pBitmapDst,pBitmapSrc,nCol,nRow,uWidth,uHeight)   \
   ((pL_CopyBitmapRect)? pL_CopyBitmapRect(pBitmapDst,pBitmapSrc,nCol,nRow,uWidth,uHeight):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_CREATEBITMAP(pBitmap,uMemory,uWidth,uHeight,uBitsPerPixel,uOrder,pPalette,uViewPerspective,pData,dwSize)  \
   ((pL_CreateBitmap )?pL_CreateBitmap(pBitmap,uMemory,uWidth,uHeight,uBitsPerPixel,uOrder,pPalette,uViewPerspective,pData,dwSize):WRPERR_LTKRN_DLL_NOT_LOADED)                                    ;

#define L_CREATEBITMAPLIST(phList)  \
   ((pL_CreateBitmapList)? pL_CreateBitmapList(phList):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_CREATELEADDC(pBitmap)  \
   ((pL_CreateLeadDC)? pL_CreateLeadDC(pBitmap):(LBase::RecordError(WRPERR_LTKRN_DLL_NOT_LOADED),(HDC)0))

#define L_CREATEUSERMATCHTABLE(pPalette,uColors)   \
   ((pL_CreateUserMatchTable)? pL_CreateUserMatchTable(pPalette,uColors):(LBase::RecordError(WRPERR_LTKRN_DLL_NOT_LOADED),(L_UINT L_FAR *)0))

#define L_DEFAULTDITHERING(uMethod) \
   ((pL_DefaultDithering)? pL_DefaultDithering(uMethod):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_DELETEBITMAPLISTITEMS(hList,uIndex,uCount)  \
   ((pL_DeleteBitmapListItems)? pL_DeleteBitmapListItems(hList,uIndex,uCount):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_DESTROYBITMAPLIST(hList)  \
   ((pL_DestroyBitmapList)? pL_DestroyBitmapList(hList):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_DELETELEADDC(hDC)   \
   ((pL_DeleteLeadDC)? pL_DeleteLeadDC(hDC):(LBase::RecordError(WRPERR_LTKRN_DLL_NOT_LOADED),FALSE))

#define L_DITHERLINE(pBitmap,pBufferSrc,pBufferDst)   \
   ((pL_DitherLine)? pL_DitherLine(pBitmap,pBufferSrc,pBufferDst):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_DUPPALETTE(hPalette)   \
   ((pL_DupPalette)? pL_DupPalette(hPalette):(LBase::RecordError(WRPERR_LTKRN_DLL_NOT_LOADED),(HPALETTE)0))

#define L_DUPBITMAPPALETTE(pBitmap)   \
   ((pL_DupBitmapPalette)? pL_DupBitmapPalette(pBitmap):(LBase::RecordError(WRPERR_LTKRN_DLL_NOT_LOADED),(HPALETTE)0))

#define L_EXPANDROW(pRunBuffer,pBuffer,nCol,nWidth)   \
   ((pL_ExpandRow)? pL_ExpandRow(pRunBuffer,pBuffer,nCol,nWidth):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_EXPANDROWS(pRun,pBuffer,nWidth,nRows) \
   ((pL_ExpandRows)? pL_ExpandRows(pRun,pBuffer,nWidth,nRows):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_FILLBITMAP(pBitmap,crFill)   \
   ((pL_FillBitmap)? pL_FillBitmap(pBitmap,crFill):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_FLIPBITMAP(pBitmap) \
   ((pL_FlipBitmap)? pL_FlipBitmap(pBitmap):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_FREEBITMAP(pBitmap) \
   ((pL_FreeBitmap)? pL_FreeBitmap(pBitmap):LBase::RecordError(WRPERR_LTKRN_DLL_NOT_LOADED))

#define L_FREEUSERMATCHTABLE(pTable)   \
   ((pL_FreeUserMatchTable)? pL_FreeUserMatchTable(pTable):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_GETBITMAPALPHA(pBitmap,pAlpha)  \
   ((pL_GetBitmapAlpha)? pL_GetBitmapAlpha(pBitmap,pAlpha):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_GETBITMAPCOLORS(pBitmap,nIndex,nCount,pPalette)   \
   ((pL_GetBitmapColors)? pL_GetBitmapColors(pBitmap,nIndex,nCount,pPalette):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_GETBITMAPLISTCOUNT(hList,puCount)  \
   ((pL_GetBitmapListCount)? pL_GetBitmapListCount(hList,puCount):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_GETBITMAPLISTITEM(hList,uIndex,pBitmap)  \
   ((pL_GetBitmapListItem)? pL_GetBitmapListItem(hList,uIndex,pBitmap):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_GETBITMAPROW(pBitmap,pBuffer,nRow,uBytes)   \
   ((pL_GetBitmapRow)? pL_GetBitmapRow(pBitmap,pBuffer,nRow,uBytes):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_GETBITMAPROWCOL(pBitmap,pBuffer,nRow,nCol,uBytes) \
   ((pL_GetBitmapRowCol)? pL_GetBitmapRowCol(pBitmap,pBuffer,nRow,nCol,uBytes):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_GETBITMAPROWCOLCOMPRESSED(pBitmap,pWorkBuffer,pRunBuffer,nRow,nCol,uWidth)   \
   ((pL_GetBitmapRowColCompressed)? pL_GetBitmapRowColCompressed(pBitmap,pWorkBuffer,pRunBuffer,nRow,nCol,uWidth):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_GETBITMAPROWCOMPRESSED(pBitmap,pWorkBuffer,pRunBuffer,nRow,nLines)  \
   ((pL_GetBitmapRowCompressed)? pL_GetBitmapRowCompressed(pBitmap,pWorkBuffer,pRunBuffer,nRow,nLines):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_GETFIXEDPALETTE(pPalette,nBitsPerPixel)  \
   ((pL_GetFixedPalette)? pL_GetFixedPalette(pPalette,nBitsPerPixel):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_GETPIXELCOLOR(pBitmap,nRow,nCol)   \
   ((pL_GetPixelColor)? pL_GetPixelColor(pBitmap,nRow,nCol):(LBase::RecordError(WRPERR_LTKRN_DLL_NOT_LOADED),0))

#define L_GRAYSCALEBITMAP(pBitmap,nBitsPerPixel)   \
   ((pL_GrayScaleBitmap)? pL_GrayScaleBitmap(pBitmap,nBitsPerPixel):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_INITBITMAP(pBitmap,nWidth,nHeight,nBitsPerPixel)  \
   ((pL_InitBitmap)? pL_InitBitmap(pBitmap,nWidth,nHeight,nBitsPerPixel):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_INSERTBITMAPLISTITEM(hList,uIndex,pBitmap)  \
   ((pL_InsertBitmapListItem)? pL_InsertBitmapListItem(hList,uIndex,pBitmap):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_ISGRAYSCALEBITMAP(pBitmap)   \
   ((pL_IsGrayScaleBitmap)? pL_IsGrayScaleBitmap(pBitmap):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_ISSUPPORTLOCKED(uType) \
   ((pL_IsSupportLocked)? pL_IsSupportLocked(uType):(LBase::RecordError(WRPERR_LTKRN_DLL_NOT_LOADED),FALSE))

#define L_POINTFROMBITMAP(pBitmap,ViewPerspective,px,py) \
   ((pL_PointFromBitmap)? pL_PointFromBitmap(pBitmap,ViewPerspective,px,py):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_POINTTOBITMAP(pBitmap,ViewPerspective,px,py)   \
   ((pL_PointToBitmap)? pL_PointToBitmap(pBitmap,ViewPerspective,px,py):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_PUTBITMAPCOLORS(pBitmap,nIndex,nCount,pPalette)   \
   ((pL_PutBitmapColors)? pL_PutBitmapColors(pBitmap,nIndex,nCount,pPalette):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_PUTBITMAPROW(pBitmap,pBuffer,nRow,uBytes)   \
   ((pL_PutBitmapRow)? pL_PutBitmapRow(pBitmap,pBuffer,nRow,uBytes):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_PUTBITMAPROWCOL(pBitmap,pBuffer,nRow,nCol,uBytes) \
   ((pL_PutBitmapRowCol)? pL_PutBitmapRowCol(pBitmap,pBuffer,nRow,nCol,uBytes):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_PUTBITMAPROWCOLCOMPRESSED(pBitmap,pWorkBuffer,pRunBuffer,nRow,nCol,uWidth)   \
   ((pL_PutBitmapRowColCompressed)? pL_PutBitmapRowColCompressed(pBitmap,pWorkBuffer,pRunBuffer,nRow,nCol,uWidth):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_PUTBITMAPROWCOMPRESSED(pBitmap,pWorkBuffer,pRunBuffer,nRow,nLines)  \
   ((pL_PutBitmapRowCompressed)? pL_PutBitmapRowCompressed(pBitmap,pWorkBuffer,pRunBuffer,nRow,nLines):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_PUTPIXELCOLOR(pBitmap,nRow,nCol,crColor) \
   ((pL_PutPixelColor)? pL_PutPixelColor(pBitmap,nRow,nCol,crColor):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_RECTFROMBITMAP(pBitmap,ViewPerspective,lprc)   \
   ((pL_RectFromBitmap)? pL_RectFromBitmap(pBitmap,ViewPerspective,lprc):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_RECTTOBITMAP(pBitmap,nViewPerspective,lprc) \
   ((pL_RectToBitmap)? pL_RectToBitmap(pBitmap,nViewPerspective,lprc):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_REDIRECTIO(pfnOpen,pfnRead,pfnWrite,pfnSeek,pfnClose,pUserData) \
   ((pL_RedirectIO )? pL_RedirectIO(pfnOpen,pfnRead,pfnWrite,pfnSeek,pfnClose,pUserData):LBase::RecordError(WRPERR_LTKRN_DLL_NOT_LOADED))                                   

#define L_RELEASEBITMAP(pBitmap) \
   ((pL_ReleaseBitmap)? pL_ReleaseBitmap(pBitmap):LBase::RecordError(WRPERR_LTKRN_DLL_NOT_LOADED))

#define L_REMOVEBITMAPLISTITEM(hList,uIndex,pBitmap)  \
   ((pL_RemoveBitmapListItem)? pL_RemoveBitmapListItem(hList,uIndex,pBitmap):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_RESAMPLEBITMAP(pBitmap,nWidth,nHeight)   \
   ((pL_ResampleBitmap)? pL_ResampleBitmap(pBitmap,nWidth,nHeight):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_RESIZE(pBuffer,nRow,nBitsPerPixel,pXSize,pYSize,pResizeData)  \
   ((pL_Resize)? pL_Resize(pBuffer,nRow,nBitsPerPixel,pXSize,pYSize,pResizeData):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_RESIZEBITMAP(pBitmapSrc,pBitmapDst)   \
   ((pL_ResizeBitmap)? pL_ResizeBitmap(pBitmapSrc,pBitmapDst):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_REVERSEBITMAP(pBitmap) \
   ((pL_ReverseBitmap)? pL_ReverseBitmap(pBitmap):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_ROTATEBITMAP(pBitmap,nAngle,uFlags,crFill) \
   ((pL_RotateBitmap )? pL_RotateBitmap(pBitmap,nAngle,uFlags,crFill):WRPERR_LTKRN_DLL_NOT_LOADED)                                        

#define L_ROTATEBITMAPVIEWPERSPECTIVE(pBitmap,nAngle) \
   ((pL_RotateBitmapViewPerspective)? pL_RotateBitmapViewPerspective(pBitmap,nAngle):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_SETBITMAPALPHA(pBitmap,pAlpha)  \
   ((pL_SetBitmapAlpha)? pL_SetBitmapAlpha(pBitmap,pAlpha):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_SETBITMAPDATAPOINTER(pBitmap,pData,dwSize)   \
   ((pL_SetBitmapDataPointer )?pL_SetBitmapDataPointer(pBitmap,pData,dwSize):WRPERR_LTKRN_DLL_NOT_LOADED);

#define L_SETBITMAPLISTITEM(hList,uIndex,pBitmap)  \
   ((pL_SetBitmapListItem)? pL_SetBitmapListItem(hList,uIndex,pBitmap):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_SETHOTKEYCALLBACK(nHotKey,uHotKeyModifiers,pfnHotKeyCallback,pUserData)   \
   ((pL_SetHotKeyCallback)? pL_SetHotKeyCallback(nHotKey,uHotKeyModifiers,pfnHotKeyCallback,pUserData):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_SETSTATUSCALLBACK(pfnCallback, pUserData)  \
   ((pL_SetStatusCallBack)? pL_SetStatusCallBack(pfnCallback,pUserData):(LBase::RecordError(WRPERR_LTKRN_DLL_NOT_LOADED),(STATUSCALLBACK)0))

#define L_SETUSERMATCHTABLE(pTable) \
   ((pL_SetUserMatchTable)? pL_SetUserMatchTable(pTable):(LBase::RecordError(WRPERR_LTKRN_DLL_NOT_LOADED),(L_UINT L_FAR *)0))

#define L_SHEARBITMAP(pBitmap,nAngle,fHorizontal,crFill) \
   ((pL_ShearBitmap)? pL_ShearBitmap(pBitmap,nAngle,fHorizontal,crFill):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_SIZEBITMAP(pBitmap,nWidth,nHeight,uFlags)   \
   ((pL_SizeBitmap)? pL_SizeBitmap(pBitmap,nWidth,nHeight,uFlags):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_STARTDITHERING(pBitmap,pPalette,uColors) \
   ((pL_StartDithering)? pL_StartDithering(pBitmap,pPalette,uColors):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_STARTRESIZE(nOldWidth,nOldHeight,nNewWidth,nNewHeight,ppResizeData) \
   ((pL_StartResize)? pL_StartResize(nOldWidth,nOldHeight,nNewWidth,nNewHeight,ppResizeData):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_STOPDITHERING(pBitmap) \
   ((pL_StopDithering)? pL_StopDithering(pBitmap):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_STOPRESIZE(pResizeData)   \
   ((pL_StopResize)? pL_StopResize(pResizeData):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_TOGGLEBITMAPCOMPRESSION(pBitmap) \
   ((pL_ToggleBitmapCompression)?pL_ToggleBitmapCompression(pBitmap):WRPERR_LTKRN_DLL_NOT_LOADED);

#define L_TRANSLATEBITMAPCOLOR(pBitmapDst,pBitmapSrc,crColor)  \
   ((pL_TranslateBitmapColor)? pL_TranslateBitmapColor(pBitmapDst,pBitmapSrc,crColor):(LBase::RecordError(WRPERR_LTKRN_DLL_NOT_LOADED),0))

#define L_TRIMBITMAP(pBitmap,nCol,nRow,uWidth,uHeight)   \
   ((pL_TrimBitmap)? pL_TrimBitmap(pBitmap,nCol,nRow,uWidth,uHeight):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_UNLOCKSUPPORT(uType,pKey) \
   ((pL_UnlockSupport)? pL_UnlockSupport(uType,pKey):LBase::RecordError(WRPERR_LTKRN_DLL_NOT_LOADED))

#define L_VERSIONINFO(pVersionInfo) \
   ((pL_VersionInfo)? pL_VersionInfo(pVersionInfo):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_FLIPBITMAPVIEWPERSPECTIVE(pBitmap) \
   ((pL_FlipBitmapViewPerspective)? pL_FlipBitmapViewPerspective(pBitmap):WRPERR_LTKRN_DLL_NOT_LOADED)   

#define L_REVERSEBITMAPVIEWPERSPECTIVE(pBitmap) \
   ((pL_ReverseBitmapViewPerspective)? pL_ReverseBitmapViewPerspective(pBitmap):WRPERR_LTKRN_DLL_NOT_LOADED)   

#define L_STARTRESIZEBITMAP(pBitmap, nNewWidth, nNewHeight, nNewBits, pPalette, nColors, uFlags, pfnCallback, pCallbackData, ppResizeData) \
   ((pL_StartResizeBitmap)? pL_StartResizeBitmap(pBitmap, nNewWidth, nNewHeight, nNewBits, pPalette, nColors, uFlags, pfnCallback, pCallbackData, ppResizeData):WRPERR_LTKRN_DLL_NOT_LOADED)                                       

#define L_GETRESIZEDROWCOL(pResizeData,pBuffer, nRow, nCol, uBytes) \
   ((pL_GetResizedRowCol)? pL_GetResizedRowCol(pResizeData,pBuffer, nRow, nCol, uBytes):WRPERR_LTKRN_DLL_NOT_LOADED)                                      

#define L_STOPRESIZEBITMAP(pResizeData) \
   ((pL_StopResizeBitmap)? pL_StopResizeBitmap(pResizeData):WRPERR_LTKRN_DLL_NOT_LOADED)   

#define L_MOVEBITMAPLISTITEMS(phList,hList,uIndex,uCount) \
   ((pL_MoveBitmapListItems)? pL_MoveBitmapListItems(phList,hList,uIndex,uCount):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_GETPIXELDATA(pBitmap, pData, nRow, nCol, nBytes) \
   ((pL_GetPixelData) ? pL_GetPixelData(pBitmap, pData, nRow, nCol, nBytes) : WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_PUTPIXELDATA(pBitmap, pData, nRow, nCol, nBytes) \
   ((pL_PutPixelData) ? pL_PutPixelData(pBitmap, pData, nRow, nCol, nBytes) : WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_CHANGEBITMAPCOMPRESSION(pBitmap, nComp) \
   ((pL_ChangeBitmapCompression) ? pL_ChangeBitmapCompression(pBitmap, nComp) : WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_CREATEBITMAPLISTOPTPAL(hList, pPalette, puColors, ppMatchTable, pbGenerated) \
   ((pL_CreateBitmapListOptPal) ? pL_CreateBitmapListOptPal(hList, pPalette, puColors, ppMatchTable, pbGenerated):WRPERR_LTKRN_DLL_NOT_LOADED)

#define L_SETBITMAPPALETTE(pBitmap, hPalette)\
   ((pL_SetBitmapPalette) ? pL_SetBitmapPalette(pBitmap, hPalette):WRPERR_LTKRN_DLL_NOT_LOADED)

//-----------------------------------------------------------------------------
//--LTIMG.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------

#define L_ADDBITMAPNOISE(pBitmap,uRange,uChannel)  \
   ((pL_AddBitmapNoise)? pL_AddBitmapNoise(pBitmap,uRange,uChannel):WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_AUTOTRIMBITMAP( pBitmap,uThreshold) \
   ((pL_AutoTrimBitmap)? pL_AutoTrimBitmap( pBitmap,uThreshold):WRPERR_LTIMG_DLL_NOT_LOADED)                                     

#define L_AVERAGEFILTERBITMAP(pBitmap,uDim)  \
   ((pL_AverageFilterBitmap)? pL_AverageFilterBitmap(pBitmap,uDim):WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_BINARYFILTERBITMAP( pBitmap, pFilter) \
   ((pL_BinaryFilterBitmap )? pL_BinaryFilterBitmap( pBitmap, pFilter):WRPERR_LTIMG_DLL_NOT_LOADED)                                          

#define L_CHANGEBITMAPCONTRAST( pBitmap, nChange) \
   ((pL_ChangeBitmapContrast )? pL_ChangeBitmapContrast( pBitmap, nChange):WRPERR_LTIMG_DLL_NOT_LOADED)                                            

#define L_CHANGEBITMAPHUE( pBitmap,nAngle) \
   ((pL_ChangeBitmapHue )? pL_ChangeBitmapHue( pBitmap,nAngle):WRPERR_LTIMG_DLL_NOT_LOADED)                                       

#define L_CHANGEBITMAPINTENSITY( pBitmap,nChange) \
   ((pL_ChangeBitmapIntensity )? pL_ChangeBitmapIntensity( pBitmap,nChange):WRPERR_LTIMG_DLL_NOT_LOADED)                                             

#define L_CHANGEBITMAPSATURATION( pBitmap,nChange) \
   ((pL_ChangeBitmapSaturation )? pL_ChangeBitmapSaturation( pBitmap,nChange):WRPERR_LTIMG_DLL_NOT_LOADED)                                              

#define L_COLORMERGEBITMAP( pBitmap,ppBitmap,uFlags) \
   ((pL_ColorMergeBitmap )? pL_ColorMergeBitmap( pBitmap,ppBitmap,uFlags):WRPERR_LTIMG_DLL_NOT_LOADED)                                        

#define L_COLORSEPARATEBITMAP( pBitmap,ppBitmap,uFlags) \
   ((pL_ColorSeparateBitmap )? pL_ColorSeparateBitmap( pBitmap,ppBitmap,uFlags):WRPERR_LTIMG_DLL_NOT_LOADED)                                           

#define L_DESKEWBITMAP( pBitmap,pnAngle) \
   ((pL_DeskewBitmap )? pL_DeskewBitmap( pBitmap,pnAngle):WRPERR_LTIMG_DLL_NOT_LOADED)                                   

#define L_DESPECKLEBITMAP( pBitmap) \
   ((pL_DespeckleBitmap )? pL_DespeckleBitmap( pBitmap):WRPERR_LTIMG_DLL_NOT_LOADED)   

#define L_SMOOTHBITMAP(  pBitmap, pSmooth,pfnCallback, pUserData) \
   ((pL_SmoothBitmap )? pL_SmoothBitmap(  pBitmap, pSmooth,pfnCallback, pUserData):WRPERR_LTIMG_DLL_NOT_LOADED)                                    

#define L_LINEREMOVEBITMAP(pBitmap, pLineRemove,pfnCallback,pUserData) \
   ((pL_LineRemoveBitmap)? pL_LineRemoveBitmap(    pBitmap, pLineRemove,pfnCallback,pUserData):WRPERR_LTIMG_DLL_NOT_LOADED)                                         

#define L_BORDERREMOVEBITMAP(pBitmap, pBorderRemove,pfnCallback,pUserData) \
   ((pL_BorderRemoveBitmap)? pL_BorderRemoveBitmap(    pBitmap, pBorderRemove,pfnCallback,pUserData):WRPERR_LTIMG_DLL_NOT_LOADED)                                           

#define L_INVERTEDTEXTBITMAP( pBitmap,pInvertedText,pfnCallback,pUserData) \
   ((pL_InvertedTextBitmap)? pL_InvertedTextBitmap( pBitmap,pInvertedText,pfnCallback,pUserData):WRPERR_LTIMG_DLL_NOT_LOADED)                                        

#define L_DOTREMOVEBITMAP(pBitmap,pDotRemove,pfnCallback,pUserData) \
   ((pL_DotRemoveBitmap)? pL_DotRemoveBitmap(pBitmap,pDotRemove,pfnCallback,pUserData):WRPERR_LTIMG_DLL_NOT_LOADED)                                     

#define L_HOLEPUNCHREMOVEBITMAP(pBitmap,pHolePunch,pfnCallback,pUserData) \
   ((pL_HolePunchRemoveBitmap)? pL_HolePunchRemoveBitmap(pBitmap,pHolePunch,pfnCallback,pUserData):WRPERR_LTIMG_DLL_NOT_LOADED)                                           

#define L_STAPLEREMOVEBITMAP(pBitmap,pStaplePunch,pfnCallback,pUserData) \
   ((pL_StapleRemoveBitmap)? pL_StapleRemoveBitmap(pBitmap,pStaplePunch,pfnCallback,pUserData):WRPERR_LTIMG_DLL_NOT_LOADED)                                           

#define L_EMBOSSBITMAP( pBitmap,uDirection,uDepth) \
   ((pL_EmbossBitmap )? pL_EmbossBitmap( pBitmap,uDirection,uDepth):WRPERR_LTIMG_DLL_NOT_LOADED)                                    

#define L_GAMMACORRECTBITMAP( pBitmap,uGamma) \
   ((pL_GammaCorrectBitmap )? pL_GammaCorrectBitmap( pBitmap,uGamma):WRPERR_LTIMG_DLL_NOT_LOADED)                                          

#define L_GETAUTOTRIMRECT( pBitmap,uThreshold,pRect) \
   ((pL_GetAutoTrimRect)? pL_GetAutoTrimRect( pBitmap,uThreshold,pRect):WRPERR_LTIMG_DLL_NOT_LOADED)                                     

#define L_GETBITMAPCOLORCOUNT( pBitmap,puCount) \
   ((pL_GetBitmapColorCount)? pL_GetBitmapColorCount( pBitmap,puCount):WRPERR_LTIMG_DLL_NOT_LOADED)                                         

#define L_GETBITMAPHISTOGRAM(pBitmap, pHisto, uHistoLen, uChannel) \
   ((pL_GetBitmapHistogram) ? pL_GetBitmapHistogram(pBitmap, pHisto, uHistoLen, uChannel) : WRPERR_LTIMG_DLL_NOT_LOADED)
                                        
#define L_GETMINMAXBITS( pBitmap,pLowBit,pHighBit) \
   ((pL_GetMinMaxBits)? pL_GetMinMaxBits( pBitmap,pLowBit,pHighBit):WRPERR_LTIMG_DLL_NOT_LOADED)                                  

#define L_GETMINMAXVAL( pBitmap,pMinVal,pMaxVal) \
   ((pL_GetMinMaxVal)? pL_GetMinMaxVal( pBitmap,pMinVal,pMaxVal):WRPERR_LTIMG_DLL_NOT_LOADED)                                  

#define L_HISTOCONTRASTBITMAP( pBitmap,nChange) \
   ((pL_HistoContrastBitmap )? pL_HistoContrastBitmap( pBitmap,nChange):WRPERR_LTIMG_DLL_NOT_LOADED)                                           

#define L_INTENSITYDETECTBITMAP( pBitmap,uLow,uHigh) \
   ((pL_IntensityDetectBitmap )? pL_IntensityDetectBitmap( pBitmap,uLow,uHigh):WRPERR_LTIMG_DLL_NOT_LOADED)                                             

#define L_INVERTBITMAP( pBitmap) \
   ((pL_InvertBitmap )? pL_InvertBitmap( pBitmap):WRPERR_LTIMG_DLL_NOT_LOADED)   

#define L_MAXFILTERBITMAP( pBitmap,uDim) \
   ((pL_MaxFilterBitmap)? pL_MaxFilterBitmap( pBitmap,uDim):WRPERR_LTIMG_DLL_NOT_LOADED)                                     

#define L_MEDIANFILTERBITMAP( pBitmap,uDim) \
   ((pL_MedianFilterBitmap )? pL_MedianFilterBitmap( pBitmap,uDim):WRPERR_LTIMG_DLL_NOT_LOADED)                                          

#define L_MINFILTERBITMAP( pBitmap,uDim) \
   ((pL_MinFilterBitmap)? pL_MinFilterBitmap( pBitmap,uDim):WRPERR_LTIMG_DLL_NOT_LOADED)                                     

#define L_MOSAICBITMAP( pBitmap,uDim) \
   ((pL_MosaicBitmap )? pL_MosaicBitmap( pBitmap,uDim):WRPERR_LTIMG_DLL_NOT_LOADED)                                    

#define L_OILIFYBITMAP( pBitmap,uDim) \
   ((pL_OilifyBitmap )? pL_OilifyBitmap( pBitmap,uDim):WRPERR_LTIMG_DLL_NOT_LOADED)                                     

#define L_POSTERIZEBITMAP( pBitmap,uLevels) \
   ((pL_PosterizeBitmap )? pL_PosterizeBitmap( pBitmap,uLevels):WRPERR_LTIMG_DLL_NOT_LOADED)                                       

#define L_PICTURIZEBITMAP( pBitmap, pszDirName, uFlags,nCellWidth,nCellHeight,pfnCallback,pUserData) \
   ((pL_PicturizeBitmap)? pL_PicturizeBitmap( pBitmap, pszDirName, uFlags,nCellWidth,nCellHeight,pfnCallback,pUserData):WRPERR_LTIMG_DLL_NOT_LOADED)                                    

#define L_REMAPBITMAPINTENSITY(pBitmap, pLUT, uLUTLen, uChannel) \
   ((pL_RemapBitmapIntensity) ? pL_RemapBitmapIntensity(pBitmap, pLUT, uLUTLen, uChannel) : WRPERR_LTIMG_DLL_NOT_LOADED)                                          

#define L_SHARPENBITMAP( pBitmap,nSharpness) \
   ((pL_SharpenBitmap )? pL_SharpenBitmap( pBitmap,nSharpness):WRPERR_LTIMG_DLL_NOT_LOADED)                                     

#define L_SOLARIZEBITMAP( pBitmap,uThreshold) \
   ((pL_SolarizeBitmap )? pL_SolarizeBitmap( pBitmap,uThreshold):WRPERR_LTIMG_DLL_NOT_LOADED)                                     

#define L_SPATIALFILTERBITMAP( pBitmap,pFilter) \
   ((pL_SpatialFilterBitmap )? pL_SpatialFilterBitmap( pBitmap,pFilter):WRPERR_LTIMG_DLL_NOT_LOADED)                                           

#define L_STRETCHBITMAPINTENSITY( pBitmap) \
   ((pL_StretchBitmapIntensity )? pL_StretchBitmapIntensity( pBitmap):WRPERR_LTIMG_DLL_NOT_LOADED)   

#define L_WINDOWLEVELBITMAP(  pBitmap,nLowBit,nHighBit,pLUT,uLUTLength,nOrderDst) \
   ((pL_WindowLevelBitmap)? pL_WindowLevelBitmap(  pBitmap,nLowBit,nHighBit,pLUT,uLUTLength,nOrderDst):WRPERR_LTIMG_DLL_NOT_LOADED)                                 

#define L_CONTOURFILTERBITMAP(  pBitmap,nThreshold,nDeltaDirection,nMaximumError,nOption) \
   ((pL_ContourFilterBitmap)? pL_ContourFilterBitmap(  pBitmap,nThreshold,nDeltaDirection,nMaximumError,nOption):WRPERR_LTIMG_DLL_NOT_LOADED)                                          

#define L_GAUSSIANFILTERBITMAP(pBitmap, nRadius) \
   ((pL_GaussianFilterBitmap) ? pL_GaussianFilterBitmap(pBitmap, nRadius) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_UNSHARPMASKBITMAP(pBitmap, nAmount, nRadius, nThreshold, uColorType) \
   ((pL_UnsharpMaskBitmap) ? pL_UnsharpMaskBitmap(pBitmap, nAmount, nRadius, nThreshold, uColorType) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_GRAYSCALEBITMAPEXT(pBitmap, RedFact, GreenFact, BlueFact) \
   ((pL_GrayScaleBitmapExt) ? pL_GrayScaleBitmapExt(pBitmap, RedFact, GreenFact, BlueFact) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_CONVERTTOCOLOREDGRAY(pBitmapHndl, RedFact, GreenFact, BlueFact, RedGrayFact, GreenGrayFact, BlueGrayFact) \
   ((pL_ConvertToColoredGray) ? pL_ConvertToColoredGray(pBitmapHndl, RedFact, GreenFact, BlueFact, RedGrayFact, GreenGrayFact, BlueGrayFact) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_BALANCECOLORS(pBitmapHndl, pRedFact, pGreenFact, pBlueFact) \
   ((pL_BalanceColors) ? pL_BalanceColors(pBitmapHndl, pRedFact, pGreenFact, pBlueFact) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_SWAPCOLORS(pBitmapHndl, nFlags) \
   ((pL_SwapColors) ? pL_SwapColors(pBitmapHndl, nFlags) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_LINEPROFILE(pBitmapHndl, FirstPoint, SecondPoint, pRed, pGreen, pBlue) \
   ((pL_LineProfile) ? pL_LineProfile(pBitmapHndl, FirstPoint, SecondPoint, pRed, pGreen, pBlue) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_HISTOEQUALIZEBITMAP(pBitmap, nFlag) \
   ((pL_HistoEqualizeBitmap) ? pL_HistoEqualizeBitmap(pBitmap, nFlag) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_ADDBITMAPS(hList, uFlag) \
      ((pL_AddBitmaps) ? pL_AddBitmaps(hList, uFlag) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_ANTIALIASBITMAP(pBitmap, uThreshold, uDim, uFilter) \
   ((pL_AntiAliasBitmap) ? pL_AntiAliasBitmap(pBitmap, uThreshold, uDim, uFilter) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_EDGEDETECTORBITMAP(pBitmap, uThreshold, uFilter) \
   ((pL_EdgeDetectorBitmap) ? pL_EdgeDetectorBitmap(pBitmap, uThreshold, uFilter) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_REMOVEREDEYEBITMAP(pBitmap, rcNewColor, uThreshold, nLightness) \
   ((pL_RemoveRedeyeBitmap) ? pL_RemoveRedeyeBitmap(pBitmap, rcNewColor, uThreshold, nLightness) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_RESIZEBITMAPRGN(pBitmap, uInflate, uFlag, bAsFrame) \
   ((pL_ResizeBitmapRgn) ? pL_ResizeBitmapRgn(pBitmap, uInflate, uFlag, bAsFrame) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_ALPHABLENDBITMAP(pBitmapDest, nXDst, nYDst, nWidth, nHeight, pBitmapSrc, nXSrc, nYSrc, nOpacity) \
   ((pL_AlphaBlendBitmap) ? pL_AlphaBlendBitmap(pBitmapDest, nXDst, nYDst, nWidth, nHeight, pBitmapSrc, nXSrc, nYSrc, nOpacity) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_FEATHERALPHABLENDBITMAP(pBitmapDest, nXDst, nYDst, nWidth, nHeight, pBitmapSrc, nXSrc, nYSrc, pBitmapMsk) \
   ((pL_FeatherAlphaBlendBitmap) ? pL_FeatherAlphaBlendBitmap(pBitmapDest, nXDst, nYDst, nWidth, nHeight, pBitmapSrc, nXSrc, nYSrc, pBitmapMsk) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_CREATEFADEDMASK(pBitmap, pMaskBitmap, nLength, nFadeRate, nStepSize, nInflate, uFlag, nMaxGray, crTransparent) \
   ((pL_CreateFadedMask) ? pL_CreateFadedMask(pBitmap, pMaskBitmap, nLength, nFadeRate, nStepSize, nInflate, uFlag, nMaxGray, crTransparent) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_MOTIONBLURBITMAP(pBitmap, uDim, nAngle, bUnidirectional) \
   ((pL_MotionBlurBitmap) ? pL_MotionBlurBitmap(pBitmap, uDim, nAngle, bUnidirectional) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_PICTURIZEBITMAPLIST(pBitmap, uxDim, uyDim, uLightnessFact, hList) \
   ((pL_PicturizeBitmapList) ? pL_PicturizeBitmapList(pBitmap, uxDim, uyDim, uLightnessFact, hList) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_PICTURIZEBITMAPSINGLE(pBitmap, pThumbBitmap, uxDim, uyDim, uGammaFact) \
   ((pL_PicturizeBitmapSingle) ? pL_PicturizeBitmapSingle(pBitmap, pThumbBitmap, uxDim, uyDim, uGammaFact) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_HALFTONEBITMAP(pBitmap, uType, nAngle, uDim) \
   ((pL_HalfToneBitmap) ? pL_HalfToneBitmap(pBitmap, uType, nAngle, uDim) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_GETFUNCTIONALLOOKUPTABLE(pLookupTable, uLookupLen, uStart, uEnd, nFactor, uFlag) \
   ((pL_GetFunctionalLookupTable) ? pL_GetFunctionalLookupTable(pLookupTable, uLookupLen, uStart, uEnd, nFactor, uFlag) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_GETUSERLOOKUPTABLE(pLookupTable, uLookupLen, apUserPoint, UserPointCount, puPointCount) \
   ((pL_GetUserLookUpTable) ? pL_GetUserLookUpTable(pLookupTable, uLookupLen, apUserPoint, UserPointCount, puPointCount) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_COMBINEBITMAPEXT(pBitmapDst, nXDst, nYDst, nWidth, nHeight, pBitmapSrc, nXSrc, nYSrc, uFlag) \
   ((pL_CombineBitmapExt) ? pL_CombineBitmapExt(pBitmapDst, nXDst, nYDst, nWidth, nHeight, pBitmapSrc, nXSrc, nYSrc, uFlag) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_ADDBORDER(pBitmap, pAddBorderInfo) \
   ((pL_AddBorder) ? pL_AddBorder(pBitmap, pAddBorderInfo) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_ADDFRAME(pBitmap, pAddFrameInfo) \
   ((pL_AddFrame) ? pL_AddFrame(pBitmap, pAddFrameInfo) : WRPERR_LTIMG_DLL_NOT_LOADED)

#define L_CONVERTBITMAPSIGNEDTOUNSIGNED(pBitmap, uShift) \
   ((pL_ConvertBitmapSignedToUnsigned) ? pL_ConvertBitmapSignedToUnsigned(pBitmap, uShift) : WRPERR_LTIMG_DLL_NOT_LOADED)


//-----------------------------------------------------------------------------
//--LTDIS.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------

#define L_APPENDPLAYBACK( hPlayback,pBitmap) \
   ((pL_AppendPlayback)? pL_AppendPlayback( hPlayback,pBitmap):WRPERR_LTDIS_DLL_NOT_LOADED)                                        

#define L_BITMAPHASRGN( pBitmap) \
   ((pL_BitmapHasRgn)? pL_BitmapHasRgn( pBitmap):WRPERR_LTDIS_DLL_NOT_LOADED)   

#define L_CANCELPLAYBACKWAIT( hPlayback) \
   ((pL_CancelPlaybackWait)? pL_CancelPlaybackWait( hPlayback):WRPERR_LTDIS_DLL_NOT_LOADED)   

#define L_CHANGEFROMDDB( hDC,pBitmap,hBitmap,hPalette) \
   ((pL_ChangeFromDDB )? pL_ChangeFromDDB( hDC,pBitmap,hBitmap,hPalette):WRPERR_LTDIS_DLL_NOT_LOADED)                                     

#define L_CHANGETODDB(hDC,pBitmap)  \
   ((pL_ChangeToDDB)? pL_ChangeToDDB(hDC,pBitmap):(LBase::RecordError(WRPERR_LTDIS_DLL_NOT_LOADED),(HBITMAP)0))

#define L_CLEARPLAYBACKUPDATERECT( hPlayback) \
   ((pL_ClearPlaybackUpdateRect)? pL_ClearPlaybackUpdateRect( hPlayback):WRPERR_LTDIS_DLL_NOT_LOADED)   

#define L_CLIPBOARDREADY() \
   ((pL_ClipboardReady)? pL_ClipboardReady():(LBase::RecordError(WRPERR_LTDIS_DLL_NOT_LOADED),FALSE))


#define L_CONVERTCOLORSPACE(pBufferSrc,pBufferDst,nWidth,nFormatSrc,nFormatDst) \
   ((pL_ConvertColorSpace )? pL_ConvertColorSpace(pBufferSrc,pBufferDst,nWidth,nFormatSrc,nFormatDst):WRPERR_LTDIS_DLL_NOT_LOADED)                                         

#define L_CONVERTFROMDDB(hDC,pBitmap,hBitmap,hPalette)   \
   ((pL_ConvertFromDDB)? pL_ConvertFromDDB(hDC,pBitmap,hBitmap,hPalette):WRPERR_LTDIS_DLL_NOT_LOADED)

#define L_CONVERTTODDB(hDC,pBitmap) \
   ((pL_ConvertToDDB)? pL_ConvertToDDB(hDC,pBitmap):(LBase::RecordError(WRPERR_LTDIS_DLL_NOT_LOADED),(HBITMAP)0))

#define L_COPYFROMCLIPBOARD(hWnd,pBitmap) \
   ((pL_CopyFromClipboard)? pL_CopyFromClipboard(hWnd,pBitmap):(LBase::RecordError(WRPERR_LTDIS_DLL_NOT_LOADED),FALSE))

#define L_COPYTOCLIPBOARD(hWnd,pBitmap)   \
   ((pL_CopyToClipboard)? pL_CopyToClipboard(hWnd,pBitmap):(LBase::RecordError(WRPERR_LTDIS_DLL_NOT_LOADED),FALSE))

#define L_COPYTOCLIPBOARDEXT(hWnd,pBitmap,uFlags)  \
   ((pL_CopyToClipboardExt)? pL_CopyToClipboardExt(hWnd,pBitmap,uFlags):WRPERR_LTDIS_DLL_NOT_LOADED)

#define L_CREATEPAINTPALETTE(hDC,pBitmap) \
   ((pL_CreatePaintPalette)? pL_CreatePaintPalette(hDC,pBitmap):(LBase::RecordError(WRPERR_LTDIS_DLL_NOT_LOADED),(HPALETTE)0))

#define L_CREATEMASKFROMBITMAPRGN( pBitmap,pMask) \
   ((pL_CreateMaskFromBitmapRgn)? pL_CreateMaskFromBitmapRgn( pBitmap,pMask):WRPERR_LTDIS_DLL_NOT_LOADED)                                     

#define L_CREATEPLAYBACK( phPlayback,pBitmap,hList) \
   ((pL_CreatePlayback)? pL_CreatePlayback( phPlayback,pBitmap,hList):WRPERR_LTDIS_DLL_NOT_LOADED)                                    

#define L_DESTROYPLAYBACK( hPlayback,phList) \
   ((pL_DestroyPlayback)? pL_DestroyPlayback( hPlayback,phList):WRPERR_LTDIS_DLL_NOT_LOADED)                                     

#define L_FRAMEBITMAPRGN( hDC,pBitmap,pXForm,uType) \
   ((pL_FrameBitmapRgn)? pL_FrameBitmapRgn( hDC,pBitmap,pXForm,uType):WRPERR_LTDIS_DLL_NOT_LOADED)                                       

#define L_COLORBITMAPRGN( hDC,pBitmap,pXForm,crRgnColor) \
   ((pL_ColorBitmapRgn)? pL_ColorBitmapRgn( hDC,pBitmap,pXForm,crRgnColor):WRPERR_LTDIS_DLL_NOT_LOADED)                                    

#define L_FREEBITMAPRGN( pBitmap) \
   ((pL_FreeBitmapRgn)? pL_FreeBitmapRgn( pBitmap):WRPERR_LTDIS_DLL_NOT_LOADED)   

#define L_GETBITMAPRGNAREA( pBitmap,puArea) \
   ((pL_GetBitmapRgnArea)? pL_GetBitmapRgnArea( pBitmap,puArea):WRPERR_LTDIS_DLL_NOT_LOADED)                                       

#define L_GETBITMAPRGNBOUNDS( pBitmap,pXForm,pRect) \
   ((pL_GetBitmapRgnBounds)? pL_GetBitmapRgnBounds( pBitmap,pXForm,pRect):WRPERR_LTDIS_DLL_NOT_LOADED)                                       

#define L_GETBITMAPRGNHANDLE( pBitmap,pXForm,phRgn) \
   ((pL_GetBitmapRgnHandle)? pL_GetBitmapRgnHandle( pBitmap,pXForm,phRgn):WRPERR_LTDIS_DLL_NOT_LOADED)                                       

#define L_GETDISPLAYMODE() \
   ((pL_GetDisplayMode )? pL_GetDisplayMode():WRPERR_LTDIS_DLL_NOT_LOADED)   


#define L_GETPAINTCONTRAST( pBitmap) \
   ((pL_GetPaintContrast)? pL_GetPaintContrast( pBitmap):WRPERR_LTDIS_DLL_NOT_LOADED)   

#define L_GETPAINTGAMMA( pBitmap) \
   ((pL_GetPaintGamma)? pL_GetPaintGamma( pBitmap):WRPERR_LTDIS_DLL_NOT_LOADED)   

#define L_GETPAINTINTENSITY( pBitmap) \
   ((pL_GetPaintIntensity)? pL_GetPaintIntensity( pBitmap):WRPERR_LTDIS_DLL_NOT_LOADED)   

#define L_GETPLAYBACKDELAY( hPlayback,puDelay) \
   ((pL_GetPlaybackDelay)? pL_GetPlaybackDelay( hPlayback,puDelay):WRPERR_LTDIS_DLL_NOT_LOADED)                                      

#define L_GETPLAYBACKINDEX( hPlayback,pnIndex) \
   ((pL_GetPlaybackIndex)? pL_GetPlaybackIndex( hPlayback,pnIndex):WRPERR_LTDIS_DLL_NOT_LOADED)                                      

#define L_GETPLAYBACKSTATE( hPlayback,puState) \
   ((pL_GetPlaybackState)? pL_GetPlaybackState( hPlayback,puState):WRPERR_LTDIS_DLL_NOT_LOADED)                                      

#define L_GETPLAYBACKUPDATERECT( hPlayback,prcUpdate,fClear) \
   ((pL_GetPlaybackUpdateRect)? pL_GetPlaybackUpdateRect( hPlayback,prcUpdate,fClear):WRPERR_LTDIS_DLL_NOT_LOADED)                                      

#define L_ISPTINBITMAPRGN( pBitmap,nRow,nCol) \
   ((pL_IsPtInBitmapRgn)? pL_IsPtInBitmapRgn( pBitmap,nRow,nCol):WRPERR_LTDIS_DLL_NOT_LOADED)                                       

#define L_OFFSETBITMAPRGN( pBitmap,nRowOffset,nColOffset) \
   ((pL_OffsetBitmapRgn)? pL_OffsetBitmapRgn( pBitmap,nRowOffset,nColOffset):WRPERR_LTDIS_DLL_NOT_LOADED)                                       

#define L_PAINTDC( hDC,pBitmap,pSrc,pClipSrc,pDst,pClipDst,uROP3) \
   ((pL_PaintDC )? pL_PaintDC( hDC,pBitmap,pSrc,pClipSrc,pDst,pClipDst,uROP3):WRPERR_LTDIS_DLL_NOT_LOADED)                               

#define L_PAINTDCBUFFER( hDC,pBitmap,pSrc,pClipSrc,pDst,pClipDst,uROP3,pBuffer,nRow,nCount) \
   ((pL_PaintDCBuffer )? pL_PaintDCBuffer( hDC,pBitmap,pSrc,pClipSrc,pDst,pClipDst,uROP3,pBuffer,nRow,nCount):WRPERR_LTDIS_DLL_NOT_LOADED)                                     

#define L_PAINTRGNDC( hDC,pBitmap,pSrc,pClipSrc,pDst,pClipDst,uROP3) \
   ((pL_PaintRgnDC )? pL_PaintRgnDC( hDC,pBitmap,pSrc,pClipSrc,pDst,pClipDst,uROP3):WRPERR_LTDIS_DLL_NOT_LOADED)                                       

#define L_PAINTRGNDCBUFFER( hDC,pBitmap,pSrc,pClipSrc,pDst,pClipDst,uROP3,pBuffer,nRow,nCount) \
   ((pL_PaintRgnDCBuffer )? pL_PaintRgnDCBuffer( hDC,pBitmap,pSrc,pClipSrc,pDst,pClipDst,uROP3,pBuffer,nRow,nCount):WRPERR_LTDIS_DLL_NOT_LOADED)                                       

#define L_PRINTBITMAP(pBitmap,nX,nY,nWidth,nHeight,fEndDoc) \
   ((pL_PrintBitmap)? pL_PrintBitmap(pBitmap,nX,nY,nWidth,nHeight,fEndDoc):(LBase::RecordError(WRPERR_LTDIS_DLL_NOT_LOADED),(HDC)0))

#define L_PRINTBITMAPEXT(hDC,pBitmap,nX,nY,nWidth,nHeight,fEndDoc)   \
   ((pL_PrintBitmapExt)? pL_PrintBitmapExt(hDC,pBitmap,nX,nY,nWidth,nHeight,fEndDoc):(LBase::RecordError(WRPERR_LTDIS_DLL_NOT_LOADED),(HDC)0))

#define L_PRINTBITMAPFAST(hDC,pBitmap,nX,nY,nWidth,nHeight,fEndDoc)  \
   ((pL_PrintBitmapFast)? pL_PrintBitmapFast(hDC,pBitmap,nX,nY,nWidth,nHeight,fEndDoc):(LBase::RecordError(WRPERR_LTDIS_DLL_NOT_LOADED),(HDC)0))

#define L_PROCESSPLAYBACK( hPlayback,puState) \
   ((pL_ProcessPlayback)? pL_ProcessPlayback( hPlayback,puState):WRPERR_LTDIS_DLL_NOT_LOADED)                                     

#define L_SCREENCAPTUREBITMAP( hDC,pBitmap,pRect) \
   ((pL_ScreenCaptureBitmap )? pL_ScreenCaptureBitmap( hDC,pBitmap,pRect):WRPERR_LTDIS_DLL_NOT_LOADED)                                           

#define L_SETBITMAPRGNCOLOR( pBitmap,crColor,uCombineMode) \
   ((pL_SetBitmapRgnColor)? pL_SetBitmapRgnColor( pBitmap,crColor,uCombineMode):WRPERR_LTDIS_DLL_NOT_LOADED)                                       
#define L_SETBITMAPRGNMAGICWAND( pBitmap,x,y,uTolerance,uCombineMode) \
   ((pL_SetBitmapRgnMagicWand)? pL_SetBitmapRgnMagicWand( pBitmap,x,y,uTolerance,uCombineMode):WRPERR_LTDIS_DLL_NOT_LOADED)                                           

#define L_SETBITMAPRGNELLIPSE( pBitmap,pXForm,pRect,uCombineMode) \
   ((pL_SetBitmapRgnEllipse)? pL_SetBitmapRgnEllipse( pBitmap,pXForm,pRect,uCombineMode):WRPERR_LTDIS_DLL_NOT_LOADED)                                       

#define L_SETBITMAPRGNFROMMASK( pBitmap,pXForm,pMask,uCombineMode) \
   ((pL_SetBitmapRgnFromMask)? pL_SetBitmapRgnFromMask( pBitmap,pXForm,pMask,uCombineMode):WRPERR_LTDIS_DLL_NOT_LOADED)                                    

#define L_SETBITMAPRGNHANDLE( pBitmap,pXForm,hRgn,uCombineMode) \
   ((pL_SetBitmapRgnHandle)? pL_SetBitmapRgnHandle( pBitmap,pXForm,hRgn,uCombineMode):WRPERR_LTDIS_DLL_NOT_LOADED)                                       

#define L_SETBITMAPRGNPOLYGON( pBitmap,pXForm,pPoints,uPoints,uFillMode,uCombineMode) \
   ((pL_SetBitmapRgnPolygon)? pL_SetBitmapRgnPolygon( pBitmap,pXForm,pPoints,uPoints,uFillMode,uCombineMode):WRPERR_LTDIS_DLL_NOT_LOADED)                                       

#define L_SETBITMAPRGNRECT( pBitmap,pXForm,pRect,uCombineMode) \
   ((pL_SetBitmapRgnRect)? pL_SetBitmapRgnRect( pBitmap,pXForm,pRect,uCombineMode):WRPERR_LTDIS_DLL_NOT_LOADED)                                       

#define L_SETBITMAPRGNROUNDRECT( pBitmap,pXForm,pRect,nWidthEllipse,nHeightEllipse,uCombineMode) \
   ((pL_SetBitmapRgnRoundRect)? pL_SetBitmapRgnRoundRect( pBitmap,pXForm,pRect,nWidthEllipse,nHeightEllipse,uCombineMode):WRPERR_LTDIS_DLL_NOT_LOADED)                                       

#define L_SETDISPLAYMODE( uFlagPos,uFlagSet) \
   ((pL_SetDisplayMode )? pL_SetDisplayMode( uFlagPos,uFlagSet):WRPERR_LTDIS_DLL_NOT_LOADED)                                         

#define L_SETPAINTCONTRAST( pBitmap,nValue) \
   ((pL_SetPaintContrast)? pL_SetPaintContrast( pBitmap,nValue):WRPERR_LTDIS_DLL_NOT_LOADED)                                      

#define L_SETPAINTGAMMA( pBitmap,uValue) \
   ((pL_SetPaintGamma)? pL_SetPaintGamma( pBitmap,uValue):WRPERR_LTDIS_DLL_NOT_LOADED)                                   

#define L_SETPAINTINTENSITY( pBitmap, nValue) \
   ((pL_SetPaintIntensity)? pL_SetPaintIntensity( pBitmap, nValue):WRPERR_LTDIS_DLL_NOT_LOADED)                                       

#define L_SETPLAYBACKINDEX( hPlayback,nIndex) \
   ((pL_SetPlaybackIndex)? pL_SetPlaybackIndex( hPlayback,nIndex):WRPERR_LTDIS_DLL_NOT_LOADED)                                      

#define L_UNDERLAYBITMAP(pBitmapDst,pUnderlay,uFlags) \
   ((pL_UnderlayBitmap)? pL_UnderlayBitmap(pBitmapDst,pUnderlay,uFlags):WRPERR_LTDIS_DLL_NOT_LOADED)

#define L_VALIDATEPLAYBACKLINES( hPlayback,nRow,nLines) \
   ((pL_ValidatePlaybackLines)? pL_ValidatePlaybackLines( hPlayback,nRow,nLines):WRPERR_LTDIS_DLL_NOT_LOADED)                                           

#define L_WINDOWLEVEL( pBitmap,nLowBit,nHighBit,pLUT,ulLUTLength,uFlags) \
   ((pL_WindowLevel)? pL_WindowLevel( pBitmap,nLowBit,nHighBit,pLUT,ulLUTLength,uFlags):WRPERR_LTDIS_DLL_NOT_LOADED)                                 


#define L_CREATEPANWINDOW( hWndParent,pBitmap,ulDisplayFlags,nLeft,nTop,nWidth,nHeight,pszClassName,hIcon,hCursor,bSysMenu,pfnPanCallback,pUserData ) \
   ((pL_CreatePanWindow)? pL_CreatePanWindow( hWndParent,pBitmap,ulDisplayFlags,nLeft,nTop,nWidth,nHeight,pszClassName,hIcon,hCursor,bSysMenu,pfnPanCallback,pUserData ):WRPERR_LTDIS_DLL_NOT_LOADED)                                     

#define L_UPDATEPANWINDOW( hPanWindow,pBitmap,ulDisplayFlags,crPen,pszTitle,prcDst ) \
   ((pL_UpdatePanWindow)? pL_UpdatePanWindow( hPanWindow,pBitmap,ulDisplayFlags,crPen,pszTitle,prcDst ):WRPERR_LTDIS_DLL_NOT_LOADED)                                     

#define L_DESTROYPANWINDOW(  hPanWindow ) \
   ((pL_DestroyPanWindow)? pL_DestroyPanWindow(  hPanWindow ):WRPERR_LTDIS_DLL_NOT_LOADED)   

#define L_WINDOWLEVELFILLLUT(pLUT,ulLUTLen,crStart,crEnd,nLow,nHigh,nLowBit,nHighBit,nMinValue,nMaxValue,bInside) \
   ((pL_WindowLevelFillLUT)? pL_WindowLevelFillLUT(pLUT,ulLUTLen,crStart,crEnd,nLow,nHigh,nLowBit,nHighBit,nMinValue,nMaxValue,bInside):WRPERR_LTDIS_DLL_NOT_LOADED)                                        


#define L_CONVERTFROMWMF( pBitmap,hWmf,uWidth,uHeight) \
   ((pL_ConvertFromWMF)? pL_ConvertFromWMF( pBitmap,hWmf,uWidth,uHeight):WRPERR_LTDIS_DLL_NOT_LOADED)                                    

#define L_CHANGEFROMWMF( pBitmap,hWmf,uWidth,uHeight) \
   ((pL_ChangeFromWMF)? pL_ChangeFromWMF( pBitmap,hWmf,uWidth,uHeight):WRPERR_LTDIS_DLL_NOT_LOADED)                                   

#define L_CONVERTTOWMF( pBitmap) \
   ((pL_ConvertToWMF)? pL_ConvertToWMF( pBitmap):WRPERR_LTDIS_DLL_NOT_LOADED)   

#define L_CHANGETOWMF( pBitmap) \
   ((pL_ChangeToWMF)? pL_ChangeToWMF( pBitmap):WRPERR_LTDIS_DLL_NOT_LOADED)   

#define L_CONVERTFROMEMF( pBitmap,hWmf,uWidth,uHeight) \
   ((pL_ConvertFromEMF)? pL_ConvertFromEMF( pBitmap,hWmf,uWidth,uHeight):WRPERR_LTDIS_DLL_NOT_LOADED)                                    

#define L_CHANGEFROMEMF( pBitmap,hWmf,uWidth,uHeight) \
   ((pL_ChangeFromEMF)? pL_ChangeFromEMF( pBitmap,hWmf,uWidth,uHeight):WRPERR_LTDIS_DLL_NOT_LOADED)                                   

#define L_CONVERTTOEMF( pBitmap) \
   ((pL_ConvertToEMF)? pL_ConvertToEMF( pBitmap):WRPERR_LTDIS_DLL_NOT_LOADED)   

#define L_CHANGETOEMF( pBitmap) \
   ((pL_ChangeToEMF)? pL_ChangeToEMF( pBitmap):WRPERR_LTDIS_DLL_NOT_LOADED)   

#define L_STARTMAGGLASS( hWnd,pBitmap,prcDst,nWidth,nHeight,nZoom,clrPen,hMagCursor,clrBack,bEllipse,nBorderSize,b3D,uPaintFlags,pMask,uMaskCount,nCrosshair,bIgnoreRgn,bCenter) \
   ((pL_StartMagGlass)? pL_StartMagGlass( hWnd,pBitmap,prcDst,nWidth,nHeight,nZoom,clrPen,hMagCursor,clrBack,bEllipse,nBorderSize,b3D,uPaintFlags,pMask,uMaskCount,nCrosshair,bIgnoreRgn,bCenter):WRPERR_LTDIS_DLL_NOT_LOADED)                                   

#define L_STOPMAGGLASS( hWnd) \
   ((pL_StopMagGlass)? pL_StopMagGlass(hWnd):WRPERR_LTDIS_DLL_NOT_LOADED)   

#define L_UPDATEMAGGLASSRECT(hWnd, prcDst) \
   ((pL_UpdateMagGlassRect)? pL_UpdateMagGlassRect(hWnd, prcDst):WRPERR_LTDIS_DLL_NOT_LOADED)

#define L_WINDOWHASMAGGLASS(hWnd) \
   ((pL_WindowHasMagGlass) ? pL_WindowHasMagGlass(hWnd) : WRPERR_LTDIS_DLL_NOT_LOADED)

#define L_SETBITMAPRGNCURVE(pBitmap, pXForm, pCurve, uCombineMode) \
   ((pL_SetBitmapRgnCurve) ? pL_SetBitmapRgnCurve(pBitmap, pXForm, pCurve, uCombineMode) : WRPERR_LTDIS_DLL_NOT_LOADED)

#define L_CURVETOBEZIER(pCurve, pOutPointCount, pOutPoint) \
   ((pL_CurveToBezier) ? pL_CurveToBezier(pCurve, pOutPointCount, pOutPoint) : WRPERR_LTDIS_DLL_NOT_LOADED)

#define L_GETBITMAPCLIPSEGMENTS(pBitmap, nRow, pSegmentBuffer, puSegmentCount) \
   ((pL_GetBitmapClipSegments) ? pL_GetBitmapClipSegments(pBitmap, nRow, pSegmentBuffer, puSegmentCount) : WRPERR_LTDIS_DLL_NOT_LOADED)

#define L_GETBITMAPCLIPSEGMENTSMAX(pBitmap, puMaxSegments) \
   ((pL_GetBitmapClipSegmentsMax) ? pL_GetBitmapClipSegmentsMax(pBitmap, puMaxSegments) : WRPERR_LTDIS_DLL_NOT_LOADED)


//-----------------------------------------------------------------------------
//--LTFIL.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
#define L_COMPRESSBUFFER(pBuffer) \
  ((pL_CompressBuffer )? pL_CompressBuffer(pBuffer):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_DELETEPAGE(pszFile, nPage, uFlags, pSaveOptions) \
  ((pL_DeletePage)? pL_DeletePage(pszFile, nPage, uFlags, pSaveOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_ENDCOMPRESSBUFFER() \
  ((pL_EndCompressBuffer )? pL_EndCompressBuffer():WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_READLOADRESOLUTIONS(pszFile, pDimensions, pDimensionCount, pLoadOptions) \
  ((pL_ReadLoadResolutions )? pL_ReadLoadResolutions(pszFile, pDimensions, pDimensionCount, pLoadOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_READFILETRANSFORMS(pszFile, pTransforms, pLoadOptions) \
  ((pL_ReadFileTransforms )? pL_ReadFileTransforms(pszFile, pTransforms, pLoadOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_WRITEFILETRANSFORMS(pszFile, pTransforms, nFlags, pSaveOptions) \
  ((pL_WriteFileTransforms )? pL_WriteFileTransforms(pszFile, pTransforms, nFlags, pSaveOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_FEEDLOAD(hLoad, pBuffer, dwBufferSize) \
  ((pL_FeedLoad )? pL_FeedLoad(hLoad, pBuffer, dwBufferSize):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_FILECONVERT(pszFileSrc, pszFileDst, nType, nWidth, nHeight, nBitsPerPixel, nQFactor, pLoadOptions, pSaveOptions, pFileInfo) \
  ((pL_FileConvert )? pL_FileConvert(pszFileSrc, pszFileDst, nType, nWidth, nHeight, nBitsPerPixel, nQFactor, pLoadOptions, pSaveOptions, pFileInfo):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_FILEINFO(pszFile, pFileInfo, uFlags, pLoadOptions) \
  ((pL_FileInfo )? pL_FileInfo(pszFile, pFileInfo, uFlags, pLoadOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_FILEINFOMEMORY(pBuffer, pFileInfo, nBufferSize, uFlags, pLoadOptions) \
  ((pL_FileInfoMemory )? pL_FileInfoMemory(pBuffer, pFileInfo, nBufferSize, uFlags, pLoadOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_GETCOMMENT(uType, pComment, uLength) \
  ((pL_GetComment )? pL_GetComment(uType, pComment, uLength):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_GETLOADRESOLUTION(nFormat, pWidth, pHeight, pLoadOptions) \
  ((pL_GetLoadResolution )? pL_GetLoadResolution(nFormat, pWidth, pHeight, pLoadOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_GETFILECOMMENTSIZE(pszFile, uType, uLength, pLoadOptions) \
  ((pL_GetFileCommentSize )? pL_GetFileCommentSize(pszFile, uType, uLength, pLoadOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_GETPCDRESOLUTION(pszFile, pPCDInfo) \
  ((pL_GetPCDResolution )? pL_GetPCDResolution(pszFile, pPCDInfo):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_GETWMFRESOLUTION(lpResolution) \
  ((pL_GetWMFResolution )? pL_GetWMFResolution(lpResolution):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_GETTAG(uTag, pType, pCount, pData) \
  ((pL_GetTag )? pL_GetTag(uTag, pType, pCount, pData):(LBase::RecordError(WRPERR_LTFIL_DLL_NOT_LOADED),(L_INT32)0))


#define L_IGNOREFILTERS(pszFilters) \
  ((pL_IgnoreFilters )? pL_IgnoreFilters(pszFilters):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_LOADBITMAP(pszFile, pBitmap, nBitsPerPixel, nOrder, pLoadOptions, pFileInfo) \
  ((pL_LoadBitmap )? pL_LoadBitmap(pszFile, pBitmap, nBitsPerPixel, nOrder, pLoadOptions, pFileInfo):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_LOADBITMAPLIST(lpszFile, phList, nBitsTo, nColorOrder, pLoadOptions, pFileInfo) \
  ((pL_LoadBitmapList )? pL_LoadBitmapList(lpszFile, phList, nBitsTo, nColorOrder, pLoadOptions, pFileInfo):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_LOADBITMAPMEMORY(pBuffer, pBitmap, nBitsPerPixel, nOrder, nBufferSize, pLoadOptions, pFileInfo) \
  ((pL_LoadBitmapMemory )? pL_LoadBitmapMemory(pBuffer, pBitmap, nBitsPerPixel, nOrder, nBufferSize, pLoadOptions, pFileInfo):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_LOADFILE(pszFile, pBitmap, nBitsPerPixel, nOrder, uFlags, pfnCallback, pUserData, pLoadOptions, pFileInfo) \
  ((pL_LoadFile )? pL_LoadFile(pszFile, pBitmap, nBitsPerPixel, nOrder, uFlags, pfnCallback, pUserData, pLoadOptions, pFileInfo):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_LOADFILETILE(pszFile, pBitmap, nCol, nRow, uWidth, uHeight, nBitsPerPixel, nOrder, uFlags, pfnCallback, pUserData, pLoadOptions, pFileInfo) \
  ((pL_LoadFileTile )? pL_LoadFileTile(pszFile, pBitmap, nCol, nRow, uWidth, uHeight, nBitsPerPixel, nOrder, uFlags, pfnCallback, pUserData, pLoadOptions, pFileInfo):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_LOADFILEOFFSET(fd, nOffsetBegin, nBytesToLoad, pBitmap, nBitsPerPixel, nOrder, uFlags, pfnCallback, pUserData, pLoadOptions, pFileInfo) \
  ((pL_LoadFileOffset )? pL_LoadFileOffset(fd, nOffsetBegin, nBytesToLoad, pBitmap, nBitsPerPixel, nOrder, uFlags, pfnCallback, pUserData, pLoadOptions, pFileInfo):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_LOADMEMORY(pBuffer, pBitmap, nBitsPerPixel, nOrder, uFlags, pfnCallback, pUserData, nBufferSize, pLoadOptions, pFileInfo) \
  ((pL_LoadMemory )? pL_LoadMemory(pBuffer, pBitmap, nBitsPerPixel, nOrder, uFlags, pfnCallback, pUserData, nBufferSize, pLoadOptions, pFileInfo):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_PRELOADFILTERS(nFixedFilters, nCachedFilters, pszFilters) \
  ((pL_PreLoadFilters )? pL_PreLoadFilters(nFixedFilters, nCachedFilters, pszFilters):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_READFILECOMMENT(pszFile, uType, pComment, uLength, pLoadOptions) \
  ((pL_ReadFileComment )? pL_ReadFileComment(pszFile, uType, pComment, uLength, pLoadOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_READFILECOMMENTEXT(pszFile, uType, pComments, pBuffer, uLength, pLoadOptions) \
  ((pL_ReadFileCommentExt )? pL_ReadFileCommentExt(pszFile, uType, pComments, pBuffer, uLength, pLoadOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_READFILECOMMENTMEMORY(pBuffer, uType, pComment, uLength, nBufferSize, pLoadOptions) \
  ((pL_ReadFileCommentMemory )? pL_ReadFileCommentMemory(pBuffer, uType, pComment, uLength, nBufferSize, pLoadOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_READFILETAG(pFile, uTag, pType, pCount, pData, pLoadOptions) \
  ((pL_ReadFileTag )? pL_ReadFileTag(pFile, uTag, pType, pCount, pData, pLoadOptions):(LBase::RecordError(WRPERR_LTFIL_DLL_NOT_LOADED),(L_INT32)0))


#define L_READFILETAGMEMORY(pBuffer, uTag, pType, pCount, pData, nBufferSize, pLoadOptions) \
  ((pL_ReadFileTagMemory )? pL_ReadFileTagMemory(pBuffer, uTag, pType, pCount, pData, nBufferSize, pLoadOptions):(LBase::RecordError(WRPERR_LTFIL_DLL_NOT_LOADED),(L_INT32)0))


#define L_READFILESTAMP(pszFile, pBitmap, pLoadOptions) \
  ((pL_ReadFileStamp )? pL_ReadFileStamp(pszFile, pBitmap, pLoadOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_SAVEBITMAP(pszFile, pBitmap, nFormat, nBitsPerPixel, nQFactor, pSaveOptions) \
  ((pL_SaveBitmap )? pL_SaveBitmap(pszFile, pBitmap, nFormat, nBitsPerPixel, nQFactor, pSaveOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_SAVEBITMAPLIST(lpszFile, hList, nFormat, nBits, nQFactor, pSaveOptions) \
  ((pL_SaveBitmapList )? pL_SaveBitmapList(lpszFile, hList, nFormat, nBits, nQFactor, pSaveOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_SAVEBITMAPMEMORY(phHandle, pBitmap, nFormat, nBitsPerPixel, nQFactor, puSize, pSaveOptions) \
  ((pL_SaveBitmapMemory )? pL_SaveBitmapMemory(phHandle, pBitmap, nFormat, nBitsPerPixel, nQFactor, puSize, pSaveOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_SAVEFILE(pszFile, pBitmap, nFormat, nBitsPerPixel, nQFactor, uFlags, pfnCallback, pUserData, pSaveOptions) \
  ((pL_SaveFile )? pL_SaveFile(pszFile, pBitmap, nFormat, nBitsPerPixel, nQFactor, uFlags, pfnCallback, pUserData, pSaveOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_SAVEFILEMEMORY(hHandle, pBitmap, nFormat, nBitsPerPixel, nQFactor, uFlags, pFunction, lpUserData, uSize, pSaveOptions) \
  ((pL_SaveFileMemory)? pL_SaveFileMemory(hHandle, pBitmap, nFormat, nBitsPerPixel, nQFactor, uFlags, pFunction, lpUserData, uSize, pSaveOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_SAVEFILETILE(pszFile, pBitmap, nCol, nRow, pfnCallback, pUserData, pSaveOptions) \
  ((pL_SaveFileTile )? pL_SaveFileTile(pszFile, pBitmap, nCol, nRow, pfnCallback, pUserData, pSaveOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_SAVEFILEOFFSET(fd, nOffsetBegin, nSizeWritten, pBitmap, nFormat, nBitsPerPixel, nQFactor, uFlags, pfnCallback, pUserData, pSaveOptions) \
  ((pL_SaveFileOffset )? pL_SaveFileOffset(fd, nOffsetBegin, nSizeWritten, pBitmap, nFormat, nBitsPerPixel, nQFactor, uFlags, pfnCallback, pUserData, pSaveOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_SETCOMMENT(uType, pComment, uLength) \
  ((pL_SetComment )? pL_SetComment(uType, pComment, uLength):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_SETLOADINFOCALLBACK(pfnCallback, pUserData) \
  ((pL_SetLoadInfoCallback )? pL_SetLoadInfoCallback(pfnCallback, pUserData):(LBase::RecordError(WRPERR_LTFIL_DLL_NOT_LOADED),(LOADINFOCALLBACK)0))


#define L_SETLOADRESOLUTION(nFormat, nWidth, nHeight) \
  ((pL_SetLoadResolution )? pL_SetLoadResolution(nFormat, nWidth, nHeight):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_SETPCDRESOLUTION(nResolution) \
  ((pL_SetPCDResolution )? pL_SetPCDResolution(nResolution):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_SETWMFRESOLUTION(nResolution) \
  ((pL_SetWMFResolution )? pL_SetWMFResolution(nResolution):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_SETTAG(uTag, uType, uCount, pData) \
  ((pL_SetTag)? pL_SetTag(uTag, uType, uCount, pData):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_STARTCOMPRESSBUFFER(pBitmap, pfnCallback, uInputBytes, uOutputBytes, pOutputBuffer, nOutputType, nQFactor, pUserData, pSaveOptions) \
  ((pL_StartCompressBuffer )? pL_StartCompressBuffer(pBitmap, pfnCallback, uInputBytes, uOutputBytes, pOutputBuffer, nOutputType, nQFactor, pUserData, pSaveOptions):WRPERR_LTFIL_DLL_NOT_LOADED)



#define L_STARTFEEDLOAD(pBitmap, nBitsPerPixel, nOrder, uFlags, pfnCallback, pUserData, phLoad, pLoadOptions, pFileInfo) \
  ((pL_StartFeedLoad )? pL_StartFeedLoad(pBitmap, nBitsPerPixel, nOrder, uFlags, pfnCallback, pUserData, phLoad, pLoadOptions, pFileInfo):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_STOPFEEDLOAD(hLoad) \
  ((pL_StopFeedLoad )? pL_StopFeedLoad(hLoad):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_WRITEFILECOMMENTEXT(pszFile, uType, pComments, pSaveOptions) \
  ((pL_WriteFileCommentExt )? pL_WriteFileCommentExt(pszFile, uType, pComments, pSaveOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_WRITEFILESTAMP(pszFile, pBitmap, pSaveOptions) \
  ((pL_WriteFileStamp )? pL_WriteFileStamp(pszFile, pBitmap, pSaveOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_SETSAVERESOLUTION(uCount, pResolutions) \
  ((pL_SetSaveResolution )? pL_SetSaveResolution(uCount, pResolutions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_GETSAVERESOLUTION(puCount, pResolutions) \
  ((pL_GetSaveResolution )? pL_GetSaveResolution(puCount, pResolutions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_2DSETVIEWPORT(nWidth, nHeight) \
  ((pL_2DSetViewport)? pL_2DSetViewport(nWidth, nHeight):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_2DGETVIEWPORT(pnWidth, pnHeight) \
  ((pL_2DGetViewport)? pL_2DGetViewport(pnWidth, pnHeight):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_2DSETVIEWMODE(nViewMode) \
  ((pL_2DSetViewMode)? pL_2DSetViewMode(nViewMode):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_2DGETVIEWMODE() \
  ((pL_2DGetViewMode)? pL_2DGetViewMode():WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_VECLOADFILE(pszFile, pVector, pLoadOptions, pFileInfo) \
  ((pL_VecLoadFile)? pL_VecLoadFile(pszFile, pVector, pLoadOptions, pFileInfo):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_VECLOADMEMORY(pBuffer, pVector, nBufferSize, pLoadOptions, pFileInfo) \
  ((pL_VecLoadMemory )? pL_VecLoadMemory(pBuffer, pVector, nBufferSize, pLoadOptions, pFileInfo):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_VECSTARTFEEDLOAD(pVector, phLoad, pLoadOptions, pFileInfo) \
  ((pL_VecStartFeedLoad )? pL_VecStartFeedLoad(pVector, phLoad, pLoadOptions, pFileInfo):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_VECFEEDLOAD(hLoad, pInBuffer, dwBufferSize) \
  ((pL_VecFeedLoad)? pL_VecFeedLoad(hLoad, pInBuffer, dwBufferSize):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_VECSTOPFEEDLOAD(hLoad) \
  ((pL_VecStopFeedLoad)? pL_VecStopFeedLoad(hLoad):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_VECSAVEFILE(pszFile, pVector, nFormat, pSaveOptions) \
  ((pL_VecSaveFile)? pL_VecSaveFile(pszFile, pVector, nFormat, pSaveOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_VECSAVEMEMORY(hHandle, pVector, nFormat, uSize, pSaveOptions) \
  ((pL_VecSaveMemory)? pL_VecSaveMemory(hHandle, pVector, nFormat, uSize, pSaveOptions):WRPERR_LTFIL_DLL_NOT_LOADED)



#define L_GETDEFAULTLOADFILEOPTION(pLoadOptions, uSize) \
   ((pL_GetDefaultLoadFileOption) ? pL_GetDefaultLoadFileOption(pLoadOptions, uSize) : WRPERR_LTFIL_DLL_NOT_LOADED)

#define L_GETDEFAULTSAVEFILEOPTION(pSaveOptions, uSize) \
   ((pL_GetDefaultSaveFileOption) ? pL_GetDefaultSaveFileOption(pSaveOptions, uSize) : WRPERR_LTFIL_DLL_NOT_LOADED)

#define L_WRITEFILETAG(pszFile, pSaveOptions) \
  ((pL_WriteFileTag)? pL_WriteFileTag(pszFile, pSaveOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_WRITEFILECOMMENT(pszFile, pSaveOptions) \
  ((pL_WriteFileComment)? pL_WriteFileComment(pszFile, pSaveOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_DOCLOADFILE(pszFile, pDocument, pLoadOptions) \
  ((pL_DocLoadFile)? pL_DocLoadFile(pszFile, pDocument, pLoadOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_DOCLOADMEMORY(pBuffer, pDocument, nBufferSize, pLoadOptions) \
  ((pL_DocLoadMemory )? pL_DocLoadMemory(pBuffer, pDocument, nBufferSize, pLoadOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_DOCSTARTFEEDLOAD(pDocument, phLoad, pLoadOptions) \
  ((pL_DocStartFeedLoad )? pL_DocStartFeedLoad(pDocument, phLoad, pLoadOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_DOCFEEDLOAD(hLoad, pInBuffer, dwBufferSize) \
  ((pL_DocFeedLoad)? pL_DocFeedLoad(hLoad, pInBuffer, dwBufferSize):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_DOCSTOPFEEDLOAD(hLoad) \
  ((pL_DocStopFeedLoad)? pL_DocStopFeedLoad(hLoad):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_DOCSAVEFILE(pszFile, pDocument, nFormat, pSaveOptions) \
  ((pL_DocSaveFile)? pL_DocSaveFile(pszFile, pDocument, nFormat, pSaveOptions):WRPERR_LTFIL_DLL_NOT_LOADED)


#define L_DOCSAVEMEMORY(hHandle, pDocument, nFormat, uSize, pSaveOptions) \
  ((pL_DocSaveMemory)? pL_DocSaveMemory(hHandle, pDocument, nFormat, uSize, pSaveOptions):WRPERR_LTFIL_DLL_NOT_LOADED)

#define L_GETJ2KOPTIONS( pOptions, nSize ) \
   ((pL_GetJ2KOptions)? pL_GetJ2KOptions( pOptions, nSize ):WRPERR_LTFIL_DLL_NOT_LOADED)

#define L_GETDEFAULTJ2KOPTIONS( pOptions, nSize ) \
   ((pL_GetDefaultJ2KOptions)? pL_GetDefaultJ2KOptions( pOptions, nSize ):WRPERR_LTFIL_DLL_NOT_LOADED)

#define L_SETJ2KOPTIONS( pOptions) \
   ((pL_SetJ2KOptions)? pL_SetJ2KOptions( pOptions):WRPERR_LTFIL_DLL_NOT_LOADED)

#define L_LOADBITMAPRESIZE(pszFile, pSmallBitmap, nDestWidth, nDestHeight, nDestBits, uFlags, nOrder, pLoadOptions, pFileInfo) \
   ((pL_LoadBitmapResize) ? pL_LoadBitmapResize(pszFile, pSmallBitmap, nDestWidth, nDestHeight, nDestBits, uFlags, nOrder, pLoadOptions, pFileInfo) : WRPERR_LTFIL_DLL_NOT_LOADED)

#define L_SAVEBITMAPBUFFER(pBuffer, uInitialBufferSize, puFinalFileSize, pBitmap, nFormat, nBitsPerPixel, nQFactor, pfnSaveBufferCB, lpUserData, pSaveOptions) \
   ((pL_SaveBitmapBuffer) ? pL_SaveBitmapBuffer(pBuffer, uInitialBufferSize, puFinalFileSize, pBitmap, nFormat, nBitsPerPixel, nQFactor, pfnSaveBufferCB, lpUserData, pSaveOptions) : WRPERR_LTFIL_DLL_NOT_LOADED)

#define L_SAVEFILEBUFFER(pBuffer, uInitialBufferSize, puFinalFileSize, pBitmap, nFormat, nBitsPerPixel, nQFactor, uFlags, pfnFileSaveCB, pfnSaveBufferCB, lpUserData, pSaveOptions) \
   ((pL_SaveFileBuffer) ? pL_SaveFileBuffer(pBuffer, uInitialBufferSize, puFinalFileSize, pBitmap, nFormat, nBitsPerPixel, nQFactor, uFlags, pfnFileSaveCB, pfnSaveBufferCB, lpUserData, pSaveOptions) : WRPERR_LTFIL_DLL_NOT_LOADED)

#define L_LOADLAYER(pszFile, pBitmap, nBitsPerPixel, nOrder, nLayer, pLayerInfo, pLoadOptions) \
   ((pL_LoadLayer) ? pL_LoadLayer(pszFile, pBitmap, nBitsPerPixel, nOrder, nLayer, pLayerInfo, pLoadOptions) : WRPERR_LTFIL_DLL_NOT_LOADED)

#define L_SAVEBITMAPWITHLAYERS(pszFile, pBitmap, nFormat, nBitsPerPixel, nQFactor, hLayers, pLayerInfo, nLayers, pSaveOptions) \
   ((pL_SaveBitmapWithLayers) ? pL_SaveBitmapWithLayers(pszFile, pBitmap, nFormat, nBitsPerPixel, nQFactor, hLayers, pLayerInfo, nLayers, pSaveOptions) : WRPERR_LTFIL_DLL_NOT_LOADED)

#define L_READFILEEXTENSIONS(pszFile, ppExtensionList, pLoadOptions) \
      ((pL_ReadFileExtensions) ? pL_ReadFileExtensions(pszFile, ppExtensionList, pLoadOptions) : WRPERR_LTFIL_DLL_NOT_LOADED)

#define L_FREEEXTENSIONS(pExtensionList) \
      ((pL_FreeExtensions) ? pL_FreeExtensions(pExtensionList) : WRPERR_LTFIL_DLL_NOT_LOADED)

#define L_LOADEXTENSIONSTAMP(pExtensionList, pBitmap) \
      ((pL_LoadExtensionStamp) ? pL_LoadExtensionStamp(pExtensionList, pBitmap) : WRPERR_LTFIL_DLL_NOT_LOADED)

#define L_GETEXTENSIONAUDIO(pExtensionList, nStream, ppBuffer, puSize) \
      ((pL_GetExtensionAudio) ? pL_GetExtensionAudio(pExtensionList, nStream, ppBuffer, puSize) : WRPERR_LTFIL_DLL_NOT_LOADED)

#define L_TRANSFORMFILE(pszFileSrc, pszFileDst, uTransform, pfnCallback, pUserData, pLoadOptions) \
      ((pL_TransformFile) ? pL_TransformFile(pszFileSrc, pszFileDst, uTransform, pfnCallback, pUserData, pLoadOptions) : WRPERR_LTFIL_DLL_NOT_LOADED)


//-----------------------------------------------------------------------------
//--LTEFX.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
#define L_EFXPAINTTRANSITION(hDC,uTransition,crBack,crFore,uSteps,pDest,uEffect,uGrain,uDelay,uPass,uMaxPass,fTransparency,crTransparency,uWandWidth,crWand,uROP) \
   ((pL_EfxPaintTransition)? pL_EfxPaintTransition(hDC,uTransition,crBack,crFore,uSteps,pDest,uEffect,uGrain,uDelay,uPass,uMaxPass,fTransparency,crTransparency,uWandWidth,crWand,uROP):WRPERR_LTEFX_DLL_NOT_LOADED)

#define L_EFXPAINTBITMAP(hDC,pBitmap,pSrc,pSrcClip,pDest,pDestClip,uEffect,uGrain,uDelay,uPass,uMaxPass,fTransparency,crTransparency,uWandWidth,crWand,uROP)   \
   ((pL_EfxPaintBitmap)? pL_EfxPaintBitmap(hDC,pBitmap,pSrc,pSrcClip,pDest,pDestClip,uEffect,uGrain,uDelay,uPass,uMaxPass,fTransparency,crTransparency,uWandWidth,crWand,uROP):WRPERR_LTEFX_DLL_NOT_LOADED)

#define L_EFXDRAWFRAME(hDC,pRect,uFlags,uFrameWidth,crFrame,uInnerWidth,crInner1,crInner2,uOuterWidth,crOuter1,crOuter2)   \
   ((pL_EfxDrawFrame)? pL_EfxDrawFrame(hDC,pRect,uFlags,uFrameWidth,crFrame,uInnerWidth,crInner1,crInner2,uOuterWidth,crOuter1,crOuter2):WRPERR_LTEFX_DLL_NOT_LOADED)

#define L_EFXGRADIENTFILLRECT(hDC,pRect,uStyle,crStart,crEnd,uSteps) \
   ((pL_EfxGradientFillRect)? pL_EfxGradientFillRect(hDC,pRect,uStyle,crStart,crEnd,uSteps):WRPERR_LTEFX_DLL_NOT_LOADED)

#define L_EFXPATTERNFILLRECT(hDC,pRect,uStyle,crBack,crFore)   \
   ((pL_EfxPatternFillRect)? pL_EfxPatternFillRect(hDC,pRect,uStyle,crBack,crFore):WRPERR_LTEFX_DLL_NOT_LOADED)

#define L_EFXDRAW3DTEXT(hDC,pszText,pRect,uFlags,nXDepth,nYDepth,crText,crShadow,crHilite,hFont,hdcFore) \
   ((pL_EfxDraw3dText)? pL_EfxDraw3dText(hDC,pszText,pRect,uFlags,nXDepth,nYDepth,crText,crShadow,crHilite,hFont,hdcFore):WRPERR_LTEFX_DLL_NOT_LOADED)

#define L_EFXDRAWROTATED3DTEXT(hDC,pszText,pRect,nAngle,uFlags,nXDepth,nYDepth,crText,crShadow,crHilite,hFont,hdcFore)  \
   ((pL_EfxDrawRotated3dText)? pL_EfxDrawRotated3dText(hDC,pszText,pRect,nAngle,uFlags,nXDepth,nYDepth,crText,crShadow,crHilite,hFont,hdcFore):WRPERR_LTEFX_DLL_NOT_LOADED)

#define L_EFXDRAW3DSHAPE(hDC,uShape,pRect,crBack,hdcBack,prcBack,uBackStyle,crFill,uFillStyle,crBorder,uBorderStyle,uBorderWidth,crInnerHilite,crInnerShadow,uInnerStyle,uInnerWidth,crOuterHilite,crOuterShadow,uOuterStyle,uOuterWidth,nShadowX,nShadowY,crShadow,hRgn)  \
   ((pL_EfxDraw3dShape)? pL_EfxDraw3dShape(hDC,uShape,pRect,crBack,hdcBack,prcBack,uBackStyle,crFill,uFillStyle,crBorder,uBorderStyle,uBorderWidth,crInnerHilite,crInnerShadow,uInnerStyle,uInnerWidth,crOuterHilite,crOuterShadow,uOuterStyle,uOuterWidth,nShadowX,nShadowY,crShadow,hRgn):WRPERR_LTEFX_DLL_NOT_LOADED)

#define L_EFXEFFECTBLT(hdcDest,nXDest,nYDest,nWidth,nHeight,hdcSrc,nXSrc,nYSrc,uEffect,uGrain,uDelay,uPass,uMaxPass,fTransparency,crTransparency,uWandWidth,crWand,uROP)   \
   ((pL_EfxEffectBlt)? pL_EfxEffectBlt(hdcDest,nXDest,nYDest,nWidth,nHeight,hdcSrc,nXSrc,nYSrc,uEffect,uGrain,uDelay,uPass,uMaxPass,fTransparency,crTransparency,uWandWidth,crWand,uROP):WRPERR_LTEFX_DLL_NOT_LOADED)

#define L_PAINTDCEFFECT(hDC,pBitmap,pSrc,pClipSrc,pDst,pClipDst,uROP3,uEffect)   \
   ((pL_PaintDCEffect)? pL_PaintDCEffect(hDC,pBitmap,pSrc,pClipSrc,pDst,pClipDst,uROP3,uEffect):WRPERR_LTEFX_DLL_NOT_LOADED)

#define L_PAINTRGNDCEFFECT(hDC,pBitmap,pSrc,pClipSrc,pDst,pClipDst,uROP3,uEffect)   \
   ((pL_PaintRgnDCEffect)? pL_PaintRgnDCEffect(hDC,pBitmap,pSrc,pClipSrc,pDst,pClipDst,uROP3,uEffect):WRPERR_LTEFX_DLL_NOT_LOADED)

//-----------------------------------------------------------------------------
//--LTDLG.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
#define L_DLGFILEOPEN(hWnd,pOpenFileName,pFileOpenParm,uFlags,pfnCallback, pUserData) \
   ((pL_DlgFileOpen)? pL_DlgFileOpen(hWnd,pOpenFileName,pFileOpenParm,uFlags,pfnCallback, pUserData):WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGGETANGLE(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) \
   ((pL_DlgGetAngle) ? pL_DlgGetAngle(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) : WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGGETSIZE(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) \
   ((pL_DlgGetSize) ? pL_DlgGetSize(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) : WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGGETFILTER(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) \
   ((pL_DlgGetFilter) ? pL_DlgGetFilter(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) : WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGGETCHANGE(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) \
   ((pL_DlgGetChange) ? pL_DlgGetChange(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) : WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGGETGAMMA(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) \
   ((pL_DlgGetGamma) ? pL_DlgGetGamma(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) : WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGGETNOISE(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) \
   ((pL_DlgGetNoise) ? pL_DlgGetNoise(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) : WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGGETEMBOSS(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) \
   ((pL_DlgGetEmboss) ? pL_DlgGetEmboss(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) : WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGGETRANGE(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) \
   ((pL_DlgGetRange) ? pL_DlgGetRange(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) : WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGCOLORRES(hWndOwner, pBitmap, pDlgParams, uFlags, uExFlags, pfnCallback, pUserData) \
   ((pL_DlgColorRes) ? pL_DlgColorRes(hWndOwner, pBitmap, pDlgParams, uFlags, uExFlags, pfnCallback, pUserData) : WRPERR_LTDLG_DLL_NOT_LOADED)


#define L_DLGFILESAVE(hWnd,pOpenFileName,pFileSaveParm,uFlags,pSaveFormats,nSaveFormats,pfnCallback, pUserData)   \
   ((pL_DlgFileSave)? pL_DlgFileSave(hWnd,pOpenFileName,pFileSaveParm,uFlags,pSaveFormats,nSaveFormats,pfnCallback, pUserData):WRPERR_LTDLG_DLL_NOT_LOADED)

//New functions
#define L_DLGCONTOURFILTER(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) \
   ((pL_DlgContourFilter) ? pL_DlgContourFilter(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) : WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGGETSTRINGLEN(uString, puLen) \
   ((pL_DlgGetStringlen)? pL_DlgGetStringlen(uString, puLen):WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGGETSTRING(uString, pString ) \
   ((pL_DlgGetString)? pL_DlgGetString(uString, pString):WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGSETSTRING(uString, pString ) \
   ((pL_DlgSetString)?pL_DlgSetString(uString, pString):WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGSETFONT(hFont) \
   ((pL_DlgSetFont)? pL_DlgSetFont(hFont):(LBase::RecordError(WRPERR_LTDIS_DLL_NOT_LOADED),(HFONT)0))

#define L_DLGWINDOWLEVEL(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) \
   ((pL_DlgWindowLevel) ? pL_DlgWindowLevel(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) : WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGGETEFFECT(hWnd,pBitmap,pEfxDlgParm,uFlags,pfnCallback, pUserData)  \
   ((pL_DlgGetEffect)? pL_DlgGetEffect(hWnd,pBitmap,pEfxDlgParm,uFlags,pfnCallback, pUserData):WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGGETSHAPE(hWnd,pBitmap,pBackgroundBitmap,pShapeDlgParm,uFlags,pfnCallback, pUserData) \
   ((pL_DlgGetShape)? pL_DlgGetShape(hWnd,pBitmap,pBackgroundBitmap,pShapeDlgParm,uFlags,pfnCallback, pUserData):WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGGETTEXT(hWnd,pBitmap,pForegroundBitmap,pTextDlgParm,uFlags,pfnCallback, pUserData)   \
   ((pL_DlgGetText)? pL_DlgGetText(hWnd,pBitmap,pForegroundBitmap,pTextDlgParm,uFlags,pfnCallback, pUserData):WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGGETGRADIENT(hWnd,pBitmap,pGradDlgParm,uFlags,pfnCallback, pUserData)  \
   ((pL_DlgGetGradient)? pL_DlgGetGradient(hWnd,pBitmap,pGradDlgParm,uFlags,pfnCallback, pUserData):WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGGETTRANSITION(hWnd,pBitmap,pTransDlgParm,uFlags,pfnCallback, pUserData)  \
   ((pL_DlgGetTransition)? pL_DlgGetTransition(hWnd,pBitmap,pTransDlgParm,uFlags,pfnCallback, pUserData):WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGGETDIRECTORY(hWndOwner, pDlgParams, uFlags, pfnCallback, pUserData) \
   ((pL_DlgGetDirectory) ? pL_DlgGetDirectory(hWndOwner, pDlgParams, uFlags, pfnCallback, pUserData) : WRPERR_LTDLG_DLL_NOT_LOADED)

#define L_DLGHALFTONE(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) \
   ((pL_DlgHalftone) ? pL_DlgHalftone(hWndOwner, pBitmap, pDlgParams, uFlags, pfnCallback, pUserData) : WRPERR_LTDLG_DLL_NOT_LOADED)


//-----------------------------------------------------------------------------
//--LTISI.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
#define L_ISISISAVAILABLE()   \
   ((pL_IsISISAvailable)? pL_IsISISAvailable():(LBase::RecordError(WRPERR_LTISI_DLL_NOT_LOADED),FALSE))

#define L_ISISACQUIRE(hWnd,pBitmap,uFlags)   \
   ((pL_ISISAcquire)? pL_ISISAcquire(hWnd,pBitmap,uFlags):WRPERR_LTISI_DLL_NOT_LOADED)

#define L_ISISACQUIREMULTI(hWnd,pszBaseFileName,uFlags,nFormat,bMultiPageFile,pnPagesDiscarded,pfnCallback,pUserData)   \
   ((pL_ISISAcquireMulti)? pL_ISISAcquireMulti(hWnd,pszBaseFileName,uFlags,nFormat,bMultiPageFile,pnPagesDiscarded,pfnCallback,pUserData):WRPERR_LTISI_DLL_NOT_LOADED)

#define L_ISISSELECT(hWnd,pszCurScanDriver)  \
   ((pL_ISISSelect)? pL_ISISSelect(hWnd,pszCurScanDriver):WRPERR_LTISI_DLL_NOT_LOADED)

#define L_ISISLOADDRIVER(pszDriverName)   \
   ((pL_ISISLoadDriver)? pL_ISISLoadDriver(pszDriverName):WRPERR_LTISI_DLL_NOT_LOADED)

#define L_ISISUNLOADDRIVER()  \
   ((pL_ISISUnloadDriver)? pL_ISISUnloadDriver():WRPERR_LTISI_DLL_NOT_LOADED)

#define L_ISISSETTAGLONG(uTag,lValue)  \
   ((pL_ISISSetTagLong)? pL_ISISSetTagLong(uTag,lValue):WRPERR_LTISI_DLL_NOT_LOADED)

#define L_ISISGETTAGLONG(uTag,plValue) \
   ((pL_ISISGetTagLong)? pL_ISISGetTagLong(uTag,plValue):WRPERR_LTISI_DLL_NOT_LOADED)

#define L_ISISSETTAGSHORT(uTag,nValue) \
   ((pL_ISISSetTagShort)? pL_ISISSetTagShort(uTag,nValue):WRPERR_LTISI_DLL_NOT_LOADED)

#define L_ISISGETTAGSHORT(uTag,pnValue)   \
   ((pL_ISISGetTagShort)? pL_ISISGetTagShort(uTag,pnValue):WRPERR_LTISI_DLL_NOT_LOADED)

#define L_ISISSETSCANOPTIONS(hWnd)  \
   ((pL_ISISSetScanOptions)? pL_ISISSetScanOptions(hWnd):WRPERR_LTISI_DLL_NOT_LOADED)

#define L_ISISSETTAGASCII(uTag, pszValue) \
((pL_ISISSetTagASCII) ? pL_ISISSetTagASCII(uTag, pszValue) : WRPERR_LTISI_DLL_NOT_LOADED)

#define L_ISISGETTAGASCII(uTag, pszValue, puSize, bDefault) \
((pL_ISISGetTagASCII) ? pL_ISISGetTagASCII(uTag, pszValue, puSize, bDefault) : WRPERR_LTISI_DLL_NOT_LOADED)

#define L_ISISGETTAGASCIICHOICE(uTag, nIndex, pszValue, puSize) \
((pL_ISISGetTagASCIIChoice) ? pL_ISISGetTagASCIIChoice(uTag, nIndex, pszValue, puSize) : WRPERR_LTISI_DLL_NOT_LOADED)

#define L_ISISGETTAGLONGCHOICE(uTag, nIndex, plValue) \
((pL_ISISGetTagLongChoice) ? pL_ISISGetTagLongChoice(uTag, nIndex, plValue) : WRPERR_LTISI_DLL_NOT_LOADED)

#define L_ISISGETTAGSHORTCHOICE(uTag, nIndex, pnValue) \
((pL_ISISGetTagShortChoice) ? pL_ISISGetTagShortChoice(uTag, nIndex, pnValue) : WRPERR_LTISI_DLL_NOT_LOADED)


//-----------------------------------------------------------------------------
//--LTTWN.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
#define L_TWAINACQUIRE(hWnd,pBitmap)   \
   ((pL_TwainAcquire)? pL_TwainAcquire(hWnd,pBitmap):WRPERR_LTTWN_DLL_NOT_LOADED)

#define L_TWAINACQUIREEXT(hWnd,pBitmap,uFlags,pfnCallback,pUserData) \
   ((pL_TwainAcquireExt)? pL_TwainAcquireExt(hWnd,pBitmap,uFlags,pfnCallback,pUserData):WRPERR_LTTWN_DLL_NOT_LOADED)

#define L_TWAINCLOSESESSION(hWnd)   \
   ((pL_TwainCloseSession)? pL_TwainCloseSession(hWnd):WRPERR_LTTWN_DLL_NOT_LOADED)

#define L_TWAINENUMSOURCES(hWnd,pfnCallback,pUserData)   \
   ((pL_TwainEnumSources)? pL_TwainEnumSources(hWnd,pfnCallback,pUserData):WRPERR_LTTWN_DLL_NOT_LOADED)

#define L_TWAINSELECT(hWnd)   \
   ((pL_TwainSelect)? pL_TwainSelect(hWnd):WRPERR_LTTWN_DLL_NOT_LOADED)

#define L_TWAINSETPROPS(hWnd,pTwain,uFlags)  \
   ((pL_TwainSetProps)? pL_TwainSetProps(hWnd,pTwain,uFlags):WRPERR_LTTWN_DLL_NOT_LOADED)

#define L_TWAINGETPROPS(pTwain)  \
   ((pL_TwainGetProps)? pL_TwainGetProps(pTwain):WRPERR_LTTWN_DLL_NOT_LOADED)

#define L_ISTWAINAVAILABLE(hWnd) \
   ((pL_IsTwainAvailable)? pL_IsTwainAvailable(hWnd):(LBase::RecordError(WRPERR_LTTWN_DLL_NOT_LOADED),FALSE))

//-----------------------------------------------------------------------------
//--LTANN.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------

#define L_ANNBRINGTOFRONT(hObject)\
   ((pL_AnnBringToFront)? pL_AnnBringToFront(hObject):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNCLIPBOARDREADY(pfReady)\
   ((pL_AnnClipboardReady)? pL_AnnClipboardReady(pfReady):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNCOPY(hSource, phDest)\
   ((pL_AnnCopy)? pL_AnnCopy(hSource, phDest):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNCOPYFROMCLIPBOARD(hWnd, phContainer)\
   ((pL_AnnCopyFromClipboard)? pL_AnnCopyFromClipboard(hWnd, phContainer):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNCOPYTOCLIPBOARD(hObject, uFormat, fSelected, fEmpty, fCheckMenu)\
   ((pL_AnnCopyToClipboard)? pL_AnnCopyToClipboard(hObject, uFormat, fSelected, fEmpty, fCheckMenu):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNCUTTOCLIPBOARD(hObject, uFormat, fSelected, fEmpty, fCheckMenu)\
   ((pL_AnnCutToClipboard)? pL_AnnCutToClipboard(hObject, uFormat, fSelected, fEmpty, fCheckMenu):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNCREATE(uObjectType, phObject)\
   ((pL_AnnCreate)? pL_AnnCreate(uObjectType, phObject):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNCREATECONTAINER(hWnd, pRect, fVisible, phObject)\
   ((pL_AnnCreateContainer)? pL_AnnCreateContainer(hWnd, pRect, fVisible, phObject):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNCREATEITEM(hContainer, uObjectType, fVisible, phObject)\
   ((pL_AnnCreateItem)? pL_AnnCreateItem(hContainer, uObjectType, fVisible, phObject):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNCREATETOOLBAR(hwndParent, pPoint, uAlign, fVisible, phWnd, uButtons, pButtons)\
   ((pL_AnnCreateToolBar)? pL_AnnCreateToolBar(hwndParent, pPoint, uAlign, fVisible, phWnd, uButtons, pButtons):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNDEFINE(hObject, pPoint, uState)\
   ((pL_AnnDefine)? pL_AnnDefine(hObject, pPoint, uState):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNDESTROY(hObject, uFlags)\
   ((pL_AnnDestroy)? pL_AnnDestroy(hObject, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNDRAW(hDC, prcInvalid, hObject)\
   ((pL_AnnDraw)? pL_AnnDraw(hDC, prcInvalid, hObject):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNENUMERATE(hObject, pfnCallback, pUserData, uFlags, pUserList)\
   ((pL_AnnEnumerate)? pL_AnnEnumerate(hObject, pfnCallback, pUserData, uFlags, pUserList):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNFLIP(hObject, pCenter, uFlags)\
   ((pL_AnnFlip)? pL_AnnFlip(hObject, pCenter, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETACTIVESTATE(hObject, puState)\
   ((pL_AnnGetActiveState)? pL_AnnGetActiveState(hObject, puState):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETAUTOCONTAINER(hObject, phContainer)\
   ((pL_AnnGetAutoContainer)? pL_AnnGetAutoContainer(hObject, phContainer):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETAUTODRAWENABLE(hObject, pfEnable)\
   ((pL_AnnGetAutoDrawEnable)? pL_AnnGetAutoDrawEnable(hObject, pfEnable):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETAUTOMENUENABLE(hObject, pfEnable)\
   ((pL_AnnGetAutoMenuEnable)? pL_AnnGetAutoMenuEnable(hObject, pfEnable):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETAUTOTEXT(hObject, uItem, pText)\
   ((pL_AnnGetAutoText)? pL_AnnGetAutoText(hObject, uItem, pText):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETAUTOTEXTLEN(hObject, uItem, puLen)\
   ((pL_AnnGetAutoTextLen)? pL_AnnGetAutoTextLen(hObject, uItem, puLen):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETBACKCOLOR(hObject, pcrBack)\
   ((pL_AnnGetBackColor)? pL_AnnGetBackColor(hObject, pcrBack):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETBITMAP(hObject, pBitmap)\
   ((pL_AnnGetBitmap)? pL_AnnGetBitmap(hObject, pBitmap):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETBITMAPDPIX(hObject, pdDpiX)\
   ((pL_AnnGetBitmapDpiX)? pL_AnnGetBitmapDpiX(hObject, pdDpiX):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETBITMAPDPIY(hObject, pdDpiY)\
   ((pL_AnnGetBitmapDpiY)? pL_AnnGetBitmapDpiY(hObject, pdDpiY):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETBOUNDINGRECT(hObject, pRect, pRectName) \
   ((pL_AnnGetBoundingRect) ? pL_AnnGetBoundingRect(hObject, pRect, pRectName) : WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETCONTAINER(hObject, phContainer)\
   ((pL_AnnGetContainer)? pL_AnnGetContainer(hObject, phContainer):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETDISTANCE(hObject, pdDistance, pdDistance2)\
   ((pL_AnnGetDistance)? pL_AnnGetDistance(hObject, pdDistance, pdDistance2):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETDPIX(hObject, pdDpiX)\
   ((pL_AnnGetDpiX)? pL_AnnGetDpiX(hObject, pdDpiX):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETDPIY(hObject, pdDpiY)\
   ((pL_AnnGetDpiY)? pL_AnnGetDpiY(hObject, pdDpiY):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETFILLMODE(hObject, puFillMode)\
   ((pL_AnnGetFillMode)? pL_AnnGetFillMode(hObject, puFillMode):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETFILLPATTERN(hObject, puFillPattern)\
   ((pL_AnnGetFillPattern)? pL_AnnGetFillPattern(hObject, puFillPattern):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETFONTBOLD(hObject, pfFontBold)\
   ((pL_AnnGetFontBold)? pL_AnnGetFontBold(hObject, pfFontBold):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETFONTITALIC(hObject, pfFontItalic)\
   ((pL_AnnGetFontItalic)? pL_AnnGetFontItalic(hObject, pfFontItalic):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETFONTNAME(hObject, pFontName)\
   ((pL_AnnGetFontName)? pL_AnnGetFontName(hObject, pFontName):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETFONTNAMELEN(hObject, puLen)\
   ((pL_AnnGetFontNameLen)? pL_AnnGetFontNameLen(hObject, puLen):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETFONTSIZE(hObject, pdFontSize)\
   ((pL_AnnGetFontSize)? pL_AnnGetFontSize(hObject, pdFontSize):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETFONTSTRIKETHROUGH(hObject, pfFontStrikeThrough)\
   ((pL_AnnGetFontStrikeThrough)? pL_AnnGetFontStrikeThrough(hObject, pfFontStrikeThrough):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETFONTUNDERLINE(hObject, pfFontUnderline)\
   ((pL_AnnGetFontUnderline)? pL_AnnGetFontUnderline(hObject, pfFontUnderline):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETFORECOLOR(hObject, pcrFore)\
   ((pL_AnnGetForeColor)? pL_AnnGetForeColor(hObject, pcrFore):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETGAUGELENGTH(hObject, pdLength)\
   ((pL_AnnGetGaugeLength)? pL_AnnGetGaugeLength(hObject, pdLength):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETHYPERLINK(hObject, puType, puMsg, pwParam, pLink)\
   ((pL_AnnGetHyperlink)? pL_AnnGetHyperlink(hObject, puType, puMsg, pwParam, pLink):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETHYPERLINKLEN(hObject, puLen)\
   ((pL_AnnGetHyperlinkLen)? pL_AnnGetHyperlinkLen(hObject, puLen):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETHYPERLINKMENUENABLE(hObject, pfEnable)\
   ((pL_AnnGetHyperlinkMenuEnable)? pL_AnnGetHyperlinkMenuEnable(hObject, pfEnable):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETLINESTYLE(hObject, puLineStyle)\
   ((pL_AnnGetLineStyle)? pL_AnnGetLineStyle(hObject, puLineStyle):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETLINEWIDTH(hObject, pdLineWidth)\
   ((pL_AnnGetLineWidth)? pL_AnnGetLineWidth(hObject, pdLineWidth):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETLOCKED(hObject, pfLocked)\
   ((pL_AnnGetLocked)? pL_AnnGetLocked(hObject, pfLocked):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETOFFSETX(hObject, pdOffsetX)\
   ((pL_AnnGetOffsetX)? pL_AnnGetOffsetX(hObject, pdOffsetX):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETOFFSETY(hObject, pdOffsetY)\
   ((pL_AnnGetOffsetY)? pL_AnnGetOffsetY(hObject, pdOffsetY):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETPOINTCOUNT(hObject, puCount)\
   ((pL_AnnGetPointCount)? pL_AnnGetPointCount(hObject, puCount):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETPOINTS(hObject, pPoints)\
   ((pL_AnnGetPoints)? pL_AnnGetPoints(hObject, pPoints):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETPOLYFILLMODE(hObject, puPolyFillMode)\
   ((pL_AnnGetPolyFillMode)? pL_AnnGetPolyFillMode(hObject, puPolyFillMode):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETRECT(hObject, pRect, pRectName) \
   ((pL_AnnGetRect) ? pL_AnnGetRect(hObject, pRect, pRectName) : WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETROP2(hObject, puRop2)\
   ((pL_AnnGetROP2)? pL_AnnGetROP2(hObject, puRop2):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETSCALARX(hObject, pdScalarX)\
   ((pL_AnnGetScalarX)? pL_AnnGetScalarX(hObject, pdScalarX):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETSCALARY(hObject, pdScalarY)\
   ((pL_AnnGetScalarY)? pL_AnnGetScalarY(hObject, pdScalarY):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETSELECTCOUNT(hObject, puCount)\
   ((pL_AnnGetSelectCount)? pL_AnnGetSelectCount(hObject, puCount):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETSELECTED(hObject, pfSelected)\
   ((pL_AnnGetSelected)? pL_AnnGetSelected(hObject, pfSelected):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETSELECTITEMS(hObject, pItems)\
   ((pL_AnnGetSelectItems)? pL_AnnGetSelectItems(hObject, pItems):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETSELECTRECT(hObject, pRect)\
   ((pL_AnnGetSelectRect)? pL_AnnGetSelectRect(hObject, pRect):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETTAG(hObject, puTag)\
   ((pL_AnnGetTag)? pL_AnnGetTag(hObject, puTag):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETTEXT(hObject, pText)\
   ((pL_AnnGetText)? pL_AnnGetText(hObject, pText):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETTEXTLEN(hObject, puLen)\
   ((pL_AnnGetTextLen)? pL_AnnGetTextLen(hObject, puLen):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETTOOL(hObject, puTool)\
   ((pL_AnnGetTool)? pL_AnnGetTool(hObject, puTool):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETTOOLBARBUTTONVISIBLE(hwndToolBar, uButton, pfVisible)\
   ((pL_AnnGetToolBarButtonVisible)? pL_AnnGetToolBarButtonVisible(hwndToolBar, uButton, pfVisible):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETTOOLBARCHECKED(hwndToolBar, puChecked)\
   ((pL_AnnGetToolBarChecked)? pL_AnnGetToolBarChecked(hwndToolBar, puChecked):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETTRANSPARENT(hObject, pbTransparent)\
   ((pL_AnnGetTransparent)? pL_AnnGetTransparent(hObject, pbTransparent):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETTYPE(hObject, puObjectType)\
   ((pL_AnnGetType)? pL_AnnGetType(hObject, puObjectType):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETTOPCONTAINER(hObject, phContainer)\
   ((pL_AnnGetTopContainer)? pL_AnnGetTopContainer(hObject, phContainer):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETUNIT(hObject, puUnit, pUnitAbbrev, puPrecision)\
   ((pL_AnnGetUnit)? pL_AnnGetUnit(hObject, puUnit, pUnitAbbrev, puPrecision):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETUNITLEN(hObject, puLen)\
   ((pL_AnnGetUnitLen)? pL_AnnGetUnitLen(hObject, puLen):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETUSERMODE(hObject, puMode)\
   ((pL_AnnGetUserMode)? pL_AnnGetUserMode(hObject, puMode):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETVISIBLE(hObject, pfVisible)\
   ((pL_AnnGetVisible)? pL_AnnGetVisible(hObject, pfVisible):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETWND(hObject, phWnd)\
   ((pL_AnnGetWnd)? pL_AnnGetWnd(hObject, phWnd):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNHITTEST(hObject, pPoint, puResult, phObjectHit)\
   ((pL_AnnHitTest)? pL_AnnHitTest(hObject, pPoint, puResult, phObjectHit):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNINSERT(hContainer, hObject, fStripContainer)\
   ((pL_AnnInsert)? pL_AnnInsert(hContainer, hObject, fStripContainer):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETITEM(hContainer, phItem)\
   ((pL_AnnGetItem)? pL_AnnGetItem(hContainer, phItem):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNLOAD(pFile, phObject, pLoadOptions)\
   ((pL_AnnLoad)? pL_AnnLoad(pFile, phObject, pLoadOptions):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNLOADOFFSET(fd, nOffset, nLength, phObject, pLoadOptions)\
   ((pL_AnnLoadOffset)? pL_AnnLoadOffset(fd, nOffset, nLength, phObject, pLoadOptions):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNLOADMEMORY(pMem, uMemSize, phObject, pLoadOptions)\
   ((pL_AnnLoadMemory)? pL_AnnLoadMemory(pMem, uMemSize, phObject, pLoadOptions):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNLOCK(hObject, pLockKey, uFlags)\
   ((pL_AnnLock)? pL_AnnLock(hObject, pLockKey, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNMOVE(hObject, dDx, dDy, uFlags)\
   ((pL_AnnMove)? pL_AnnMove(hObject, dDx, dDy, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNPRINT(hDC, prcBounds, hObject)\
   ((pL_AnnPrint)? pL_AnnPrint(hDC, prcBounds, hObject):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNREALIZE(pBitmap, prcBounds, hObject, fRedactOnly)\
   ((pL_AnnRealize)? pL_AnnRealize(pBitmap, prcBounds, hObject, fRedactOnly):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNRESIZE(hObject, dFactorX, dFactorY, pCenter, uFlags)\
   ((pL_AnnResize)? pL_AnnResize(hObject, dFactorX, dFactorY, pCenter, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNREVERSE(hObject, pCenter, uFlags)\
   ((pL_AnnReverse)? pL_AnnReverse(hObject, pCenter, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNREMOVE(hObject)\
   ((pL_AnnRemove)? pL_AnnRemove(hObject):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNROTATE(hObject, dAngle, pCenter, uFlags)\
   ((pL_AnnRotate)? pL_AnnRotate(hObject, dAngle, pCenter, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSAVE(pFile, hObject, uFormat, fSelected, pSaveOptions) \
   ((pL_AnnSave) ? pL_AnnSave(pFile, hObject, uFormat, fSelected, pSaveOptions) : WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSAVEOFFSET(fd, nOffset, puSizeWritten, hObject, uFormat, fSelected, pSaveOptions) \
   ((pL_AnnSaveOffset ) ? pL_AnnSaveOffset(fd, nOffset, puSizeWritten, hObject, uFormat, fSelected, pSaveOptions) : WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSAVEMEMORY(hObject, uFormat, fSelected, phMem, puMemSize, pSaveOptions) \
   ((pL_AnnSaveMemory) ? pL_AnnSaveMemory(hObject, uFormat, fSelected, phMem, puMemSize, pSaveOptions) : WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSAVETAG(hObject, uFormat, fSelected)\
   ((pL_AnnSaveTag)? pL_AnnSaveTag(hObject, uFormat, fSelected):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSELECTPOINT(hObject, pPoint)\
   ((pL_AnnSelectPoint)? pL_AnnSelectPoint(hObject, pPoint):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSELECTRECT(hObject, pRect)\
   ((pL_AnnSelectRect)? pL_AnnSelectRect(hObject, pRect):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSENDTOBACK(hObject)\
   ((pL_AnnSendToBack)? pL_AnnSendToBack(hObject):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETACTIVESTATE(hObject, uState)\
   ((pL_AnnSetActiveState)? pL_AnnSetActiveState(hObject, uState):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETAUTOCONTAINER(hObject, hContainer)\
   ((pL_AnnSetAutoContainer)? pL_AnnSetAutoContainer(hObject, hContainer):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETAUTODRAWENABLE(hObject, fEnable)\
   ((pL_AnnSetAutoDrawEnable)? pL_AnnSetAutoDrawEnable(hObject, fEnable):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETAUTOMENUENABLE(hObject, fEnable)\
   ((pL_AnnSetAutoMenuEnable)? pL_AnnSetAutoMenuEnable(hObject, fEnable):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETAUTOTEXT(hObject, uItem, pText)\
   ((pL_AnnSetAutoText)? pL_AnnSetAutoText(hObject, uItem, pText):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETBACKCOLOR(hObject, crBack, uFlags)\
   ((pL_AnnSetBackColor)? pL_AnnSetBackColor(hObject, crBack, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETBITMAP(hObject, pBitmap, uFlags)\
   ((pL_AnnSetBitmap)? pL_AnnSetBitmap(hObject, pBitmap, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETBITMAPDPIX(hObject, dDpiX, uFlags)\
   ((pL_AnnSetBitmapDpiX)? pL_AnnSetBitmapDpiX(hObject, dDpiX, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETBITMAPDPIY(hObject, dDpiY, uFlags)\
   ((pL_AnnSetBitmapDpiY)? pL_AnnSetBitmapDpiY(hObject, dDpiY, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETDPIX(hObject, dDpiX, uFlags)\
   ((pL_AnnSetDpiX)? pL_AnnSetDpiX(hObject, dDpiX, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETDPIY(hObject, dDpiY, uFlags)\
   ((pL_AnnSetDpiY)? pL_AnnSetDpiY(hObject, dDpiY, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETFILLMODE(hObject, uFillMode, uFlags)\
   ((pL_AnnSetFillMode)? pL_AnnSetFillMode(hObject, uFillMode, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETFILLPATTERN(hObject, uFillPattern, uFlags)\
   ((pL_AnnSetFillPattern)? pL_AnnSetFillPattern(hObject, uFillPattern, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETFONTBOLD(hObject, fFontBold, uFlags)\
   ((pL_AnnSetFontBold)? pL_AnnSetFontBold(hObject, fFontBold, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETFONTITALIC(hObject, fFontItalic, uFlags)\
   ((pL_AnnSetFontItalic)? pL_AnnSetFontItalic(hObject, fFontItalic, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETFONTNAME(hObject, pFontName, uFlags)\
   ((pL_AnnSetFontName)? pL_AnnSetFontName(hObject, pFontName, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETFONTSIZE(hObject, dFontSize, uFlags)\
   ((pL_AnnSetFontSize)? pL_AnnSetFontSize(hObject, dFontSize, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETFONTSTRIKETHROUGH(hObject, fFontStrikeThrough, uFlags)\
   ((pL_AnnSetFontStrikeThrough)? pL_AnnSetFontStrikeThrough(hObject, fFontStrikeThrough, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETFONTUNDERLINE(hObject, fFontUnderline, uFlags)\
   ((pL_AnnSetFontUnderline)? pL_AnnSetFontUnderline(hObject, fFontUnderline, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETFORECOLOR(hObject, crFore, uFlags)\
   ((pL_AnnSetForeColor)? pL_AnnSetForeColor(hObject, crFore, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETGAUGELENGTH(hObject, dLength, uFlags)\
   ((pL_AnnSetGaugeLength)? pL_AnnSetGaugeLength(hObject, dLength, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETHYPERLINK(hObject, uType, uMsg, wParam, pLink, uFlags)\
   ((pL_AnnSetHyperlink)? pL_AnnSetHyperlink(hObject, uType, uMsg, wParam, pLink, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETHYPERLINKMENUENABLE(hObject, fEnable, uFlags)\
   ((pL_AnnSetHyperlinkMenuEnable)? pL_AnnSetHyperlinkMenuEnable(hObject, fEnable, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETLINESTYLE(hObject, uLineStyle, uFlags)\
   ((pL_AnnSetLineStyle)? pL_AnnSetLineStyle(hObject, uLineStyle, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETLINEWIDTH(hObject, dLineWidth, uFlags)\
   ((pL_AnnSetLineWidth)? pL_AnnSetLineWidth(hObject, dLineWidth, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETOFFSETX(hObject, dOffsetX, uFlags)\
   ((pL_AnnSetOffsetX)? pL_AnnSetOffsetX(hObject, dOffsetX, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETOFFSETY(hObject, dOffsetY, uFlags)\
   ((pL_AnnSetOffsetY)? pL_AnnSetOffsetY(hObject, dOffsetY, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETPOINTS(hObject, pPoints, uCount)\
   ((pL_AnnSetPoints)? pL_AnnSetPoints(hObject, pPoints, uCount):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETPOLYFILLMODE(hObject, uPolyFillMode, uFlags)\
   ((pL_AnnSetPolyFillMode)? pL_AnnSetPolyFillMode(hObject, uPolyFillMode, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETROP2(hObject, uROP2, uFlags)\
   ((pL_AnnSetROP2)? pL_AnnSetROP2(hObject, uROP2, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETRECT(hObject, pRect)\
   ((pL_AnnSetRect)? pL_AnnSetRect(hObject, pRect):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETSELECTED(hObject, fSelected, uFlags)\
   ((pL_AnnSetSelected)? pL_AnnSetSelected(hObject, fSelected, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETSCALARX(hObject, dScalarX, uFlags)\
   ((pL_AnnSetScalarX)? pL_AnnSetScalarX(hObject, dScalarX, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETSCALARY(hObject, dScalarY, uFlags)\
   ((pL_AnnSetScalarY)? pL_AnnSetScalarY(hObject, dScalarY, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETTAG(hObject, uTag, uFlags)\
   ((pL_AnnSetTag)? pL_AnnSetTag(hObject, uTag, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETTEXT(hObject, pText, uFlags)\
   ((pL_AnnSetText)? pL_AnnSetText(hObject, pText, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETTOOL(hObject, uTool)\
   ((pL_AnnSetTool)? pL_AnnSetTool(hObject, uTool):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETTOOLBARBUTTONVISIBLE(hwndToolBar, uButton, fVisible)\
   ((pL_AnnSetToolBarButtonVisible)? pL_AnnSetToolBarButtonVisible(hwndToolBar, uButton, fVisible):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETTOOLBARCHECKED(hwndToolBar, uChecked)\
   ((pL_AnnSetToolBarChecked)? pL_AnnSetToolBarChecked(hwndToolBar, uChecked):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETTRANSPARENT(hObject, bTransparent, uFlags)\
   ((pL_AnnSetTransparent)? pL_AnnSetTransparent(hObject, bTransparent, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETUNDODEPTH(hObject, uLevels)\
   ((pL_AnnSetUndoDepth)? pL_AnnSetUndoDepth(hObject, uLevels):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETUNIT(hObject, uUnit, pUnitAbbrev, uPrecision, uFlags)\
   ((pL_AnnSetUnit)? pL_AnnSetUnit(hObject, uUnit, pUnitAbbrev, uPrecision, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETUSERMODE(hObject, uMode)\
   ((pL_AnnSetUserMode)? pL_AnnSetUserMode(hObject, uMode):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETVISIBLE(hObject, fVisible, uFlags, pUserList)\
   ((pL_AnnSetVisible)? pL_AnnSetVisible(hObject, fVisible, uFlags, pUserList):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETWND(hObject, hWnd)\
   ((pL_AnnSetWnd)? pL_AnnSetWnd(hObject, hWnd):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSHOWLOCKEDICON(hObject, bShow, uFlags)\
   ((pL_AnnShowLockedIcon)? pL_AnnShowLockedIcon(hObject, bShow, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNUNDO(hObject)\
   ((pL_AnnUndo)? pL_AnnUndo(hObject):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNUNLOCK(hObject, pUnlockKey, uFlags)\
   ((pL_AnnUnlock)? pL_AnnUnlock(hObject, pUnlockKey, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNUNREALIZE(pBitmap, prcBounds, hObject, fSelected)\
   ((pL_AnnUnrealize)? pL_AnnUnrealize(pBitmap, prcBounds, hObject, fSelected):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETNODES(hObject, bShowNodes, uGapNodes, uFlags)\
   ((pL_AnnSetNodes)? pL_AnnSetNodes(hObject, bShowNodes, uGapNodes, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETNODES(hObject, pbShowNodes, puGapNodes)\
   ((pL_AnnGetNodes)? pL_AnnGetNodes(hObject, pbShowNodes, puGapNodes):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETPROTRACTOROPTIONS(hObject, bAcute, uUnit, pszAbbrev, uPrecision, dArcRadius, uFlags)\
   ((pL_AnnSetProtractorOptions)? pL_AnnSetProtractorOptions(hObject, bAcute, uUnit, pszAbbrev, uPrecision, dArcRadius, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETPROTRACTOROPTIONS(hObject, pbAcute, puUnit, puAbbrevLen, pszAbbrev, puPrecision, pdArcRadius)\
   ((pL_AnnGetProtractorOptions)? pL_AnnGetProtractorOptions(hObject, pbAcute, puUnit, puAbbrevLen, pszAbbrev, puPrecision, pdArcRadius):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETNAME(hObject, bShowName, pText, pNameOffset, bNameRestrict, uFlags) \
   ((pL_AnnSetName) ? pL_AnnSetName(hObject, bShowName, pText, pNameOffset, bNameRestrict, uFlags) : WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETNAME(hObject, pbShowName, puNameLen, pName, pNameOffset, pbNameRestrict) \
   ((pL_AnnGetName) ? pL_AnnGetName(hObject, pbShowName, puNameLen, pName, pNameOffset, pbNameRestrict) : WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETSHOWFLAGS(hObject, uShowFlags, uFlags)\
   ((pL_AnnSetShowFlags)? pL_AnnSetShowFlags(hObject, uShowFlags, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETSHOWFLAGS(hObject, puShowFlags)\
   ((pL_AnnGetShowFlags)? pL_AnnGetShowFlags(hObject, puShowFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETANGLE(hObject, pdAngle)\
   ((pL_AnnGetAngle)? pL_AnnGetAngle(hObject, pdAngle):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETMETAFILE(hObject, hMetafile, uType, uFlags)\
   ((pL_AnnSetMetafile)? pL_AnnSetMetafile(hObject, hMetafile, uType, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETMETAFILE(hObject, phMetafile)\
   ((pL_AnnGetMetafile)? pL_AnnGetMetafile(hObject, phMetafile):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETPREDEFINEDMETAFILE(uType, hMetafile)\
   ((pL_AnnSetPredefinedMetafile)? pL_AnnSetPredefinedMetafile(uType, hMetafile):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETPREDEFINEDMETAFILE(uType, phMetafile, pbEnhanced)\
   ((pL_AnnGetPredefinedMetafile)? pL_AnnGetPredefinedMetafile(uType, phMetafile, pbEnhanced):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETSECONDARYBITMAP(hObject, pBitmap, uFlags)\
   ((pL_AnnSetSecondaryBitmap)? pL_AnnSetSecondaryBitmap(hObject, pBitmap, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETSECONDARYBITMAP(hObject, pBitmap)\
   ((pL_AnnGetSecondaryBitmap)? pL_AnnGetSecondaryBitmap(hObject, pBitmap):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETAUTOMENUITEMENABLE(hObject, nObjectType, uItem, uEnable, uFlags, pUserList)\
   ((pL_AnnSetAutoMenuItemEnable)? pL_AnnSetAutoMenuItemEnable(hObject, nObjectType, uItem, uEnable, uFlags, pUserList):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETAUTOMENUITEMENABLE(hObject, nObjectType, uItem, puEnable)\
   ((pL_AnnGetAutoMenuItemEnable)? pL_AnnGetAutoMenuItemEnable(hObject, nObjectType, uItem, puEnable):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETAUTOMENUSTATE(hObject, nObjectType, pEnable, pEnableFlags, uBits, uFlags)\
   ((pL_AnnSetAutoMenuState)? pL_AnnSetAutoMenuState(hObject, nObjectType, pEnable, pEnableFlags, uBits, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETAUTOMENUSTATE(hObject, nObjectType, pEnable, pEnableFlags, uBits)\
   ((pL_AnnGetAutoMenuState)? pL_AnnGetAutoMenuState(hObject, nObjectType, pEnable, pEnableFlags, uBits):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETUSER(hObject, pOldUser, pNewUser, uFlags)\
   ((pL_AnnSetUser)? pL_AnnSetUser(hObject, pOldUser, pNewUser, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETTOOLBARBUTTONS(hwndToolBar, pButtons, uButtons)\
   ((pL_AnnSetToolBarButtons)? pL_AnnSetToolBarButtons(hwndToolBar, pButtons, uButtons):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETTOOLBARBUTTONS(hwndToolBar, pButtons, puButtons)\
   ((pL_AnnGetToolBarButtons)? pL_AnnGetToolBarButtons(hwndToolBar, pButtons, puButtons):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNFREETOOLBARBUTTONS(pButtons, uButtons)\
   ((pL_AnnFreeToolBarButtons)? pL_AnnFreeToolBarButtons(pButtons, uButtons):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETTOOLBARINFO(hwndToolBar, pInfo)\
   ((pL_AnnGetToolBarInfo)? pL_AnnGetToolBarInfo(hwndToolBar, pInfo):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETTOOLBARCOLUMNS(hwndToolBar, uColumns)\
   ((pL_AnnSetToolBarColumns)? pL_AnnSetToolBarColumns(hwndToolBar, uColumns):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETTOOLBARROWS(hwndToolBar, uColumns)\
   ((pL_AnnSetToolBarRows)? pL_AnnSetToolBarRows(hwndToolBar, uColumns):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETAUTODEFAULTS(hAutomation, hObject, uFlags)\
   ((pL_AnnSetAutoDefaults)? pL_AnnSetAutoDefaults(hAutomation, hObject, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETTRANSPARENTCOLOR(hObject, crTransparent, uFlags)\
   ((pL_AnnSetTransparentColor)? pL_AnnSetTransparentColor(hObject, crTransparent, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETTRANSPARENTCOLOR(hObject, pcrTransparent)\
   ((pL_AnnGetTransparentColor)? pL_AnnGetTransparentColor(hObject, pcrTransparent):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETUNDODEPTH(hObject, puUsedLevels, puMaxLevels)\
   ((pL_AnnGetUndoDepth)? pL_AnnGetUndoDepth(hObject, puUsedLevels, puMaxLevels):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGROUP(hObject, uFlags, pUserList)\
   ((pL_AnnGroup)? pL_AnnGroup(hObject, uFlags, pUserList):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNUNGROUP(hObject, uFlags, pUserList)\
   ((pL_AnnUngroup)? pL_AnnUngroup(hObject, uFlags, pUserList):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETAUTOOPTIONS(hObject, uFlags)\
   ((pL_AnnSetAutoOptions)? pL_AnnSetAutoOptions(hObject, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETAUTOOPTIONS(hObject, puFlags)\
   ((pL_AnnGetAutoOptions)? pL_AnnGetAutoOptions(hObject, puFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETOBJECTFROMTAG(hContainer, uFlags, uTag, phTagObject)\
   ((pL_AnnGetObjectFromTag)? pL_AnnGetObjectFromTag(hContainer, uFlags, uTag, phTagObject):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETRGNHANDLE(hObject, pXForm, phRgn)\
   ((pL_AnnGetRgnHandle)? pL_AnnGetRgnHandle(hObject, pXForm, phRgn):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETAREA(hObject, puCount)\
   ((pL_AnnGetArea)? pL_AnnGetArea(hObject, puCount):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETAUTODIALOGFONTSIZE(hObject, nFontSize)\
   ((pL_AnnSetAutoDialogFontSize)? pL_AnnSetAutoDialogFontSize(hObject, nFontSize):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETAUTODIALOGFONTSIZE(hObject, pnFontSize)\
   ((pL_AnnGetAutoDialogFontSize)? pL_AnnGetAutoDialogFontSize(hObject, pnFontSize):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETGROUPING(hObject, bAutoGroup, uFlags)\
   ((pL_AnnSetGrouping)? pL_AnnSetGrouping(hObject, bAutoGroup, uFlags):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETGROUPING(hObject, pbAutoGroup)\
   ((pL_AnnGetGrouping)? pL_AnnGetGrouping(hObject, pbAutoGroup):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETAUTOBACKCOLOR(hObject, uObjectType, crBack)\
   ((pL_AnnSetAutoBackColor)? pL_AnnSetAutoBackColor(hObject, uObjectType, crBack):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETAUTOBACKCOLOR(hObject, uObjectType, pcrBack)\
   ((pL_AnnGetAutoBackColor)? pL_AnnGetAutoBackColor(hObject, uObjectType, pcrBack):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNADDUNDONODE(hObject)\
   ((pL_AnnAddUndoNode)? pL_AnnAddUndoNode(hObject):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNSETAUTOUNDOENABLE(hObject, bEnable)\
   ((pL_AnnSetAutoUndoEnable)? pL_AnnSetAutoUndoEnable(hObject, bEnable):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNGETAUTOUNDOENABLE(hObject, pbEnable)\
   ((pL_AnnGetAutoUndoEnable)? pL_AnnGetAutoUndoEnable(hObject, pbEnable):WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNFILEINFO(pszFile, pAnnFileInfo) \
   ((pL_AnnFileInfo) ? pL_AnnFileInfo(pszFile, pAnnFileInfo) : WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNFILEINFOMEMORY(pMem, uMemSize, pAnnFileInfo) \
   ((pL_AnnFileInfoMemory) ? pL_AnnFileInfoMemory(pMem, uMemSize, pAnnFileInfo) : WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNFILEINFOOFFSET(fd, pAnnFileInfo) \
   ((pL_AnnFileInfoOffset) ? pL_AnnFileInfoOffset(fd, pAnnFileInfo) : WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNDELETEPAGE(pFile, nPage) \
   ((pL_AnnDeletePage) ? pL_AnnDeletePage(pFile, nPage) : WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNDELETEPAGEMEMORY(hMem, puMemSize, nPage) \
   ((pL_AnnDeletePageMemory) ? pL_AnnDeletePageMemory(hMem, puMemSize, nPage) : WRPERR_LTANN_DLL_NOT_LOADED)

#define L_ANNDELETEPAGEOFFSET(fd, nOffset, nPage) \
   ((pL_AnnDeletePageOffset) ? pL_AnnDeletePageOffset(fd, nOffset, nPage) : WRPERR_LTANN_DLL_NOT_LOADED)


//-----------------------------------------------------------------------------
//--LTSCR.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
#define L_SETCAPTUREOPTION(pOptions)   \
   ((pL_SetCaptureOption)? pL_SetCaptureOption(pOptions):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_GETCAPTUREOPTION(pOptions)   \
   ((pL_GetCaptureOption)? pL_GetCaptureOption(pOptions):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_CAPTUREWINDOW(pBitmap,hWnd,wctCaptureType,pCaptureInfo,pfnCaptureCallback,pUserData)  \
   ((pL_CaptureWindow)? pL_CaptureWindow(pBitmap,hWnd,wctCaptureType,pCaptureInfo,pfnCaptureCallback,pUserData):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_CAPTUREACTIVEWINDOW(pBitmap,pCaptureInfo,pfnCaptureCallback,pUserData) \
   ((pL_CaptureActiveWindow)? pL_CaptureActiveWindow(pBitmap,pCaptureInfo,pfnCaptureCallback,pUserData):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_CAPTUREACTIVECLIENT(pBitmap,pCaptureInfo,pfnCaptureCallback,pUserData) \
   ((pL_CaptureActiveClient)? pL_CaptureActiveClient(pBitmap,pCaptureInfo,pfnCaptureCallback,pUserData):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_CAPTUREWALLPAPER(pBitmap,pCaptureInfo,pfnCaptureCallback,pUserData) \
   ((pL_CaptureWallPaper)? pL_CaptureWallPaper(pBitmap,pCaptureInfo,pfnCaptureCallback,pUserData):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_CAPTUREFULLSCREEN(pBitmap,pCaptureInfo,pfnCaptureCallback,pUserData)   \
   ((pL_CaptureFullScreen)? pL_CaptureFullScreen(pBitmap,pCaptureInfo,pfnCaptureCallback,pUserData):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_CAPTUREMENUUNDERCURSOR(pBitmap,pCaptureInfo,pfnCaptureCallback,pUserData) \
   ((pL_CaptureMenuUnderCursor)? pL_CaptureMenuUnderCursor(pBitmap,pCaptureInfo,pfnCaptureCallback,pUserData):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_CAPTUREWINDOWUNDERCURSOR(pBitmap,pCaptureInfo,pfnCaptureCallback,pUserData)  \
   ((pL_CaptureWindowUnderCursor)? pL_CaptureWindowUnderCursor(pBitmap,pCaptureInfo,pfnCaptureCallback,pUserData):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_CAPTURESELECTEDOBJECT(pBitmap,pObjectOptions,pCaptureInfo,pfnCaptureCallback,pUserData)  \
   ((pL_CaptureSelectedObject)? pL_CaptureSelectedObject(pBitmap,pObjectOptions,pCaptureInfo,pfnCaptureCallback,pUserData):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_CAPTUREAREA(pBitmap,pCaptureAreaOption,pCaptureInfo,pfnCaptureCallback,pUserData)  \
   ((pL_CaptureArea)? pL_CaptureArea(pBitmap,pCaptureAreaOption,pCaptureInfo,pfnCaptureCallback,pUserData):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_CAPTUREMOUSECURSOR(pBitmap,crFill,pCaptureInfo,pfnCaptureCallback,pUserData) \
   ((pL_CaptureMouseCursor)? pL_CaptureMouseCursor(pBitmap,crFill,pCaptureInfo,pfnCaptureCallback,pUserData):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_CAPTURESETHOTKEYCALLBACK(pfnCaptureHotKeyCB,pUserData)  \
   ((pL_CaptureSetHotKeyCallback)? pL_CaptureSetHotKeyCallback(pfnCaptureHotKeyCB,pUserData):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_SETCAPTUREOPTIONDLG(hwndOwner,pOptions)  \
   ((pL_SetCaptureOptionDlg)? pL_SetCaptureOptionDlg(hwndOwner,pOptions):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_CAPTUREAREAOPTIONDLG(hParentWnd,pCaptureAreaOption,nUseDefault)  \
   ((pL_CaptureAreaOptionDlg)? pL_CaptureAreaOptionDlg(hParentWnd,pCaptureAreaOption,nUseDefault):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_CAPTUREOBJECTOPTIONDLG(hParentWnd,pObjectOptions,nUseDefault) \
   ((pL_CaptureObjectOptionDlg)? pL_CaptureObjectOptionDlg(hParentWnd,pObjectOptions,nUseDefault):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_GETDEFAULTAREAOPTION(pCaptureAreaOption) \
   ((pL_GetDefaultAreaOption)? pL_GetDefaultAreaOption(pCaptureAreaOption):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_GETDEFAULTOBJECTOPTION(pObjectOptions)   \
   ((pL_GetDefaultObjectOption)? pL_GetDefaultObjectOption(pObjectOptions):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_STOPCAPTURE() \
   ((pL_StopCapture)? pL_StopCapture():WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_CAPTUREFROMEXEDLG(pBitmap,pszFileName,pTransparentColor,nResType,nDialogType,pCaptureInfo,pfnCaptureCallback,pUserData)   \
   ((pL_CaptureFromExeDlg)? pL_CaptureFromExeDlg(pBitmap,pszFileName,pTransparentColor,nResType,nDialogType,pCaptureInfo,pfnCaptureCallback,pUserData):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_CAPTUREFROMEXE(pBitmap,pszFileName,nResType,pResID,bCaptureByIndex,clrBackGnd,pfnCaptureCallback,pUserData)   \
   ((pL_CaptureFromExe)? pL_CaptureFromExe(pBitmap,pszFileName,nResType,pResID,bCaptureByIndex,clrBackGnd,pfnCaptureCallback,pUserData):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_CAPTUREGETRESCOUNT(pszFileName,nResType,pnCount)  \
   ((pL_CaptureGetResCount)? pL_CaptureGetResCount(pszFileName,nResType,pnCount):WRPERR_LTSCR_DLL_NOT_LOADED)

#define L_ISCAPTUREACTIVE()   \
   ((pL_IsCaptureActive)? pL_IsCaptureActive():(LBase::RecordError(WRPERR_LTSCR_DLL_NOT_LOADED),FALSE))

//-----------------------------------------------------------------------------
//--LTNET.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
#define L_INETCREATEPACKETFROMPARAMS( phPacket, uExtra, pExtra, uParama, pParams) \
   ((pL_InetCreatePacketFromParams)? pL_InetCreatePacketFromParams( phPacket, uExtra, pExtra, uParama, pParams):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETFREEPACKET( hPacket) \
   ((pL_InetFreePacket)? pL_InetFreePacket( hPacket):(LBase::RecordError(WRPERR_LTNET_DLL_NOT_LOADED)))

#define L_INETSENDCMD( hComputer, uCommand, uCommandID, hPacket) \
   ((pL_InetSendCmd)? pL_InetSendCmd( hComputer, uCommand, uCommandID, hPacket):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDRSP( hComputer, uCommand, uCommandID, hPacket, nStatus) \
   ((pL_InetSendRsp)? pL_InetSendRsp( hComputer, uCommand, uCommandID, hPacket, nStatus):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDLOADCMD( hComputer, uCommandID, pszFile, nBitsPerPixel, nOrder, uFlags) \
   ((pL_InetSendLoadCmd)? pL_InetSendLoadCmd( hComputer, uCommandID, pszFile, nBitsPerPixel, nOrder, uFlags):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDLOADRSP( hComputer, uCommandID, uBitmapID, uExtra, pExtra, nStatus) \
   ((pL_InetSendLoadRsp)? pL_InetSendLoadRsp( hComputer, uCommandID, uBitmapID, uExtra, pExtra, nStatus):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDSAVECMD( hComputer, uCommandID, pszFile, uBitmapID, nFormat, nBitsPerPixel, nQFactor, uFlags) \
   ((pL_InetSendSaveCmd)? pL_InetSendSaveCmd( hComputer, uCommandID, pszFile, uBitmapID, nFormat, nBitsPerPixel, nQFactor, uFlags):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDSAVERSP( hComputer, uCommandID, uExtra, pExtra, nStatus) \
   ((pL_InetSendSaveRsp)? pL_InetSendSaveRsp( hComputer, uCommandID, uExtra, pExtra, nStatus):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDCREATEWINCMD( hComputer, uCommandID, pszClassName, pszWindowName, ulFlags, nLeft, nTop, nWidth, nHeight, uParentID) \
   ((pL_InetSendCreateWinCmd)? pL_InetSendCreateWinCmd( hComputer, uCommandID, pszClassName, pszWindowName, ulFlags, nLeft, nTop, nWidth, nHeight, uParentID):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDCREATEWINRSP( hComputer, uCommandID, uWindowID, uLength, pExtraInfo, nStatus) \
   ((pL_InetSendCreateWinRsp)? pL_InetSendCreateWinRsp( hComputer, uCommandID, uWindowID, uLength, pExtraInfo, nStatus):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDSIZEWINCMD( hComputer, uCommandID, uWindowID, nLeft, nTop, nWidth, nHeight) \
   ((pL_InetSendSizeWinCmd)? pL_InetSendSizeWinCmd( hComputer, uCommandID, uWindowID, nLeft, nTop, nWidth, nHeight):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDSIZEWINRSP( hComputer, uCommandID, uLength, pExtraInfo, nStatus) \
   ((pL_InetSendSizeWinRsp)? pL_InetSendSizeWinRsp( hComputer, uCommandID, uLength, pExtraInfo, nStatus):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDSHOWWINCMD( hComputer, uCommandID, uWindowID, nCmdShow) \
   ((pL_InetSendShowWinCmd)? pL_InetSendShowWinCmd( hComputer, uCommandID, uWindowID, nCmdShow):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDSHOWWINRSP( hComputer, uCommandID, uLength, pExtraInfo, nStatus) \
   ((pL_InetSendShowWinRsp)? pL_InetSendShowWinRsp( hComputer, uCommandID, uLength, pExtraInfo, nStatus):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDCLOSEWINCMD( hComputer, uCommandID, uWindowID) \
   ((pL_InetSendCloseWinCmd)? pL_InetSendCloseWinCmd( hComputer, uCommandID, uWindowID):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDCLOSEWINRSP( hComputer, uCommandID, uLength, pExtraInfo, nStatus) \
   ((pL_InetSendCloseWinRsp)? pL_InetSendCloseWinRsp( hComputer, uCommandID, uLength, pExtraInfo, nStatus):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDFREEBITMAPCMD( hComputer, uCommandID, uBitmapID) \
   ((pL_InetSendFreeBitmapCmd)? pL_InetSendFreeBitmapCmd( hComputer, uCommandID, uBitmapID):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDFREEBITMAPRSP( hComputer, uCommandID, uLength, pExtraInfo, nStatus) \
   ((pL_InetSendFreeBitmapRsp)? pL_InetSendFreeBitmapRsp( hComputer, uCommandID, uLength, pExtraInfo, nStatus):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDSETRECTCMD( hComputer, uCommandID, uWindowID, nType, nLeft, nTop, nWidth, nHeight) \
   ((pL_InetSendSetRectCmd)? pL_InetSendSetRectCmd( hComputer, uCommandID, uWindowID, nType, nLeft, nTop, nWidth, nHeight):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDSETRECTRSP( hComputer, uCommandID, uLength, pExtraInfo, nStatus) \
   ((pL_InetSendSetRectRsp)? pL_InetSendSetRectRsp( hComputer, uCommandID, uLength, pExtraInfo, nStatus):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSETCOMMANDCALLBACK( hComputer, pfnCallback, pUserData) \
   ((pL_InetSetCommandCallback)? pL_InetSetCommandCallback( hComputer, pfnCallback, pUserData):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSETRESPONSECALLBACK( hComputer, pfnCallback, pUserData) \
   ((pL_InetSetResponseCallback)? pL_InetSetResponseCallback( hComputer, pfnCallback, pUserData):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDATTACHBITMAPCMD( hComputer, uCommandID, uBitmapID, uWindowID) \
   ((pL_InetSendAttachBitmapCmd)? pL_InetSendAttachBitmapCmd( hComputer, uCommandID, uBitmapID, uWindowID):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDATTACHBITMAPRSP( hComputer, uCommandID, uExtra, pExtra, nStatus) \
   ((pL_InetSendAttachBitmapRsp)? pL_InetSendAttachBitmapRsp( hComputer, uCommandID, uExtra, pExtra, nStatus):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETCONNECT( pszAddress, nPort, phComputer, pfnCallback, pUserData) \
   ((pL_InetConnect)? pL_InetConnect( pszAddress, nPort, phComputer, pfnCallback, pUserData):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSERVERINIT( nPort, phComputer, pfnCallback, pUserData) \
   ((pL_InetServerInit)? pL_InetServerInit( nPort, phComputer, pfnCallback, pUserData):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETCLOSE( hComputer, bGraceful) \
   ((pL_InetClose)? pL_InetClose( hComputer, bGraceful):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDDATA( hComputer, pBuffer, pulBufferLength, uDataType) \
   ((pL_InetSendData)? pL_InetSendData( hComputer, pBuffer, pulBufferLength, uDataType):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDMMDATA( hComputer, pBuffer, pulBufferLength) \
   ((pL_InetSendMMData)? pL_InetSendMMData( hComputer, pBuffer, pulBufferLength):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETREADDATA( hComputer, pBuffer, pulBufferLength) \
   ((pL_InetReadData)? pL_InetReadData( hComputer, pBuffer, pulBufferLength):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETGETHOSTNAME( hHost, pszName, nType, pulBufferLength) \
   ((pL_InetGetHostName)? pL_InetGetHostName( hHost, pszName, nType, pulBufferLength):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETACCEPTCONNECT( hHost, phRemote, pfnCallback, pUserData) \
   ((pL_InetAcceptConnect)? pL_InetAcceptConnect( hHost, phRemote, pfnCallback, pUserData):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDBITMAP( hComputer, pBitmap, nFormat, nBitsPerPixel, nQFactor, pulImageLength) \
   ((pL_InetSendBitmap)? pL_InetSendBitmap( hComputer, pBitmap, nFormat, nBitsPerPixel, nQFactor, pulImageLength):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETAUTOPROCESS( hComputer, bProcess) \
   ((pL_InetAutoProcess)? pL_InetAutoProcess( hComputer, bProcess):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDRAWDATA( hComputer, pBuffer, pulBufferLength) \
   ((pL_InetSendRawData)? pL_InetSendRawData( hComputer, pBuffer, pulBufferLength):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETGETQUEUESIZE( hComputer, pulLength) \
   ((pL_InetGetQueueSize)? pL_InetGetQueueSize( hComputer, pulLength):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETCLEARQUEUE( hComputer) \
   ((pL_InetClearQueue)? pL_InetClearQueue( hComputer):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSTARTUP() \
   ((pL_InetStartUp)? pL_InetStartUp():WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSHUTDOWN() \
   ((pL_InetShutDown)? pL_InetShutDown():WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSENDSOUND( hComputer, pWaveFormatData, pWaveData, pdwDataSize) \
   ((pL_InetSendSound)? pL_InetSendSound( hComputer, pWaveFormatData, pWaveData, pdwDataSize):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETATTACHTOSOCKET( phComputer, hSocket, pfnCallback, pUserData) \
   ((pL_InetAttachToSocket)? pL_InetAttachToSocket( phComputer, hSocket, pfnCallback, pUserData):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETDETACHFROMSOCKET( hComputer, bWaitTillQueueEmpty, phSocket) \
   ((pL_InetDetachFromSocket)? pL_InetDetachFromSocket( hComputer, bWaitTillQueueEmpty, phSocket):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETSETCALLBACK( hComputer, pfnCallback, pUserData) \
   ((pL_InetSetCallback)? pL_InetSetCallback( hComputer, pfnCallback, pUserData):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETGETCALLBACK( hComputer, ppfnCallback, ppUserData) \
   ((pL_InetGetCallback)? pL_InetGetCallback( hComputer, ppfnCallback, ppUserData):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETGETPARAMETERS( puParams, ppParams, pszFormat, pArgs) \
   ((pL_InetGetParameters)? pL_InetGetParameters( puParams, ppParams, pszFormat, pArgs):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETCOPYPARAMETERS( ppParams, uParams, pParams) \
   ((pL_InetCopyParameters)? pL_InetCopyParameters( ppParams, uParams, pParams):WRPERR_LTNET_DLL_NOT_LOADED)

#define L_INETFREEPARAMETERS( pParams, nCount) \
   ((pL_InetFreeParameters)? pL_InetFreeParameters( pParams, nCount):(LBase::RecordError(WRPERR_LTNET_DLL_NOT_LOADED)))


//-----------------------------------------------------------------------------
//--LTWEB.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------

#define L_INETHTTPCONNECT( pszServer, iPort, pszUserName, pszPassword, pHttp) \
   ((pL_InetHttpConnect)? pL_InetHttpConnect( pszServer, iPort, pszUserName, pszPassword, pHttp):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETHTTPDISCONNECT( hHttp) \
   ((pL_InetHttpDisconnect)? pL_InetHttpDisconnect( hHttp):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETHTTPOPENREQUEST( hHttp, uType, pszTarget, pszReferer, pszVersion, dwReserved) \
   ((pL_InetHttpOpenRequest)? pL_InetHttpOpenRequest( hHttp, uType, pszTarget, pszReferer, pszVersion, dwReserved):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETHTTPCLOSEREQUEST( hHttp) \
   ((pL_InetHttpCloseRequest)? pL_InetHttpCloseRequest( hHttp):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETHTTPSENDBITMAP( hHttp, pBitmap, nFormat, nBitsPerPixel, nQFactor, pszContentType, pNameValue, pSaveOptions) \
   ((pL_InetHttpSendBitmap)? pL_InetHttpSendBitmap( hHttp, pBitmap, nFormat, nBitsPerPixel, nQFactor, pszContentType, pNameValue, pSaveOptions):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETHTTPSENDDATA( hHttp, pData, uSize, pszContentType, pNameValue) \
   ((pL_InetHttpSendData)? pL_InetHttpSendData( hHttp, pData, uSize, pszContentType, pNameValue):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETHTTPSENDFORM( hHttp, pNameValue, uCount) \
   ((pL_InetHttpSendForm)? pL_InetHttpSendForm( hHttp, pNameValue, uCount):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETHTTPSENDREQUEST( hHttp, pszHeader, ulHeaderSize, pszOptional, ulOptionalSize) \
   ((pL_InetHttpSendRequest)? pL_InetHttpSendRequest( hHttp, pszHeader, ulHeaderSize, pszOptional, ulOptionalSize):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETHTTPGETRESPONSE( hHttp, pszData, ulSize) \
   ((pL_InetHttpGetResponse)? pL_InetHttpGetResponse( hHttp, pszData, ulSize):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETHTTPGETSERVERSTATUS( hHttp, uStatus) \
   ((pL_InetHttpGetServerStatus)? pL_InetHttpGetServerStatus( hHttp, uStatus):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETFTPCONNECT( pszServer, iPort, pszUserName, pszPassword, pFtp) \
   ((pL_InetFtpConnect)? pL_InetFtpConnect( pszServer, iPort, pszUserName, pszPassword, pFtp):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETFTPDISCONNECT( hFtp) \
   ((pL_InetFtpDisconnect)? pL_InetFtpDisconnect( hFtp):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETFTPSENDFILE( hFtp, pszLocal, pszRemote, uSendAs) \
   ((pL_InetFtpSendFile)? pL_InetFtpSendFile( hFtp, pszLocal, pszRemote, uSendAs):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETFTPGETFILE( hFtp, pszRemote, pszLocal, bOverwrite, uSendAs) \
   ((pL_InetFtpGetFile)? pL_InetFtpGetFile( hFtp, pszRemote, pszLocal, bOverwrite, uSendAs):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETFTPRENAMEFILE( hFtp, pszOld, pszNew) \
   ((pL_InetFtpRenameFile)? pL_InetFtpRenameFile( hFtp, pszOld, pszNew):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETFTPDELETEFILE( hFtp, pszRemote) \
   ((pL_InetFtpDeleteFile)? pL_InetFtpDeleteFile( hFtp, pszRemote):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETFTPCREATEDIR( hFtp, pszRemoteDir) \
   ((pL_InetFtpCreateDir)? pL_InetFtpCreateDir( hFtp, pszRemoteDir):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETFTPDELETEDIR( hFtp, pszRemoteDir) \
   ((pL_InetFtpDeleteDir)? pL_InetFtpDeleteDir( hFtp, pszRemoteDir):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETFTPGETCURRENTDIR( hFtp, pszRemoteDir, ulSize) \
   ((pL_InetFtpGetCurrentDir)? pL_InetFtpGetCurrentDir( hFtp, pszRemoteDir, ulSize):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETFTPBROWSEDIR( hFtp, pszSearch, pfnCallback, pData) \
   ((pL_InetFtpBrowseDir)? pL_InetFtpBrowseDir( hFtp, pszSearch, pfnCallback, pData):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETFTPCHANGEDIR( hFtp, pszDirectory) \
   ((pL_InetFtpChangeDir)? pL_InetFtpChangeDir( hFtp, pszDirectory):WRPERR_LTWEB_DLL_NOT_LOADED)

#define L_INETFTPSENDBITMAP( hFtp, pBitmap, nFormat, nBitsPerPixel, nQFactor, pSaveOptions, pszRemote, uSendAs) \
   ((pL_InetFtpSendBitmap)? pL_InetFtpSendBitmap( hFtp, pBitmap, nFormat, nBitsPerPixel, nQFactor, pSaveOptions, pszRemote, uSendAs):WRPERR_LTWEB_DLL_NOT_LOADED)

//#endif


//-----------------------------------------------------------------------------
//--LTTMB.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
#define L_BROWSEDIR(pszPath, pszFilter, nThumbWidth, nThumbHeight,    \
                    nBits, uCRFlags, bMaintainAspect, bForceSize,     \
                    crBackColor, bLoadStamp, bResample, bStopOnError, \
                    bIncludeSubDirs, bExpandMultipage, lSizeDisk,     \
                    lSizeMem, pfnBrowseDirCB, pUserData)              \
   ((pL_BrowseDir)? pL_BrowseDir(pszPath, pszFilter, nThumbWidth, nThumbHeight,    \
                    nBits, uCRFlags, bMaintainAspect, bForceSize,     \
                    crBackColor, bLoadStamp, bResample, bStopOnError, \
                    bIncludeSubDirs, bExpandMultipage, lSizeDisk,     \
                    lSizeMem, pfnBrowseDirCB, pUserData):(LBase::RecordError(WRPERR_LTTMB_DLL_NOT_LOADED),FALSE))

//-----------------------------------------------------------------------------
//--LTLST.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
#define L_USEIMAGELISTCONTROL() \
   ((pL_UseImageListControl)? pL_UseImageListControl():(LBase::RecordError(WRPERR_LTLST_DLL_NOT_LOADED)))


#define L_CREATEIMAGELISTCONTROL( dwStyle, x, y, nWidth, nHeight, hWndParent, nID, crBack) \
   ((pL_CreateImageListControl)? pL_CreateImageListControl( dwStyle, x, y, nWidth, nHeight, hWndParent, nID, crBack):(LBase::RecordError(WRPERR_LTLST_DLL_NOT_LOADED),(HWND)0))


//-----------------------------------------------------------------------------
//--LVKRN.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
#define L_VECDUPLICATEOBJECTDESCRIPTOR(nType, pObjectDescDst, pObjectDescSrc ) \
   ((pL_VecDuplicateObjectDescriptor)? pL_VecDuplicateObjectDescriptor( nType, pObjectDescDst, pObjectDescSrc ):WRPERR_LVKRN_DLL_NOT_LOADED)

//Do not remove the one above
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  General functions.                                                   []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
#define L_VECINIT( pVector ) \
   ((pL_VecInit)? pL_VecInit( pVector ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECFREE( pVector ) \
   ((pL_VecFree)? pL_VecFree( pVector ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECEMPTY( pVector ) \
   ((pL_VecEmpty)? pL_VecEmpty( pVector ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECISEMPTY( pVector ) \
   ((pL_VecIsEmpty)? pL_VecIsEmpty( pVector ):(LBase::RecordError(WRPERR_LVKRN_DLL_NOT_LOADED),(L_BOOL)0))

#define L_VECCOPY( pDst, pSrc, dwFlags ) \
   ((pL_VecCopy)? pL_VecCopy( pDst, pSrc, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECSETDISPLAYOPTIONS( pVector, pOptions ) \
   ((pL_VecSetDisplayOptions)? pL_VecSetDisplayOptions( pVector, pOptions ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETDISPLAYOPTIONS( pVector, pOptions ) \
   ((pL_VecGetDisplayOptions)? pL_VecGetDisplayOptions( pVector, pOptions ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECINVERTCOLORS( pVector ) \
   ((pL_VecInvertColors)? pL_VecInvertColors( pVector ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECSETVIEWPORT( pVector, pViewport ) \
   ((pL_VecSetViewport)? pL_VecSetViewport( pVector, pViewport ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETVIEWPORT( pVector, pViewport ) \
   ((pL_VecGetViewport)? pL_VecGetViewport( pVector, pViewport ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECSETPAN( pVector, pPan ) \
   ((pL_VecSetPan)? pL_VecSetPan( pVector, pPan ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETPAN( pVector, pPan ) \
   ((pL_VecGetPan)? pL_VecGetPan( pVector, pPan ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECPAINT( hDC, pVector, bEraseBkgnd ) \
   ((pL_VecPaint)? pL_VecPaint( hDC, pVector, bEraseBkgnd ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECREALIZE( pBitmap, pVetcor, bEraseBkgnd ) \
   ((pL_VecRealize)? pL_VecRealize( pBitmap, pVetcor, bEraseBkgnd ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECPAINTDC( hDC, pVector, uWidth, uHeight, pSrc, pSrcClip, pDest, pDestClip, dwFlags ) \
   ((pL_VecPaintDC)? pL_VecPaintDC( hDC, pVector, uWidth, uHeight, pSrc, pSrcClip, pDest, pDestClip, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECIS3D( pVector) \
   ((pL_VecIs3D)? pL_VecIs3D( pVector):(LBase::RecordError(WRPERR_LVKRN_DLL_NOT_LOADED),(L_BOOL)0))

#define L_VECISLOCKED( pVector ) \
   ((pL_VecIsLocked)? pL_VecIsLocked( pVector ):(LBase::RecordError(WRPERR_LVKRN_DLL_NOT_LOADED),(L_BOOL)0))

#define L_VECSETLOCKED( pVector, bLock ) \
   ((pL_VecSetLocked)? pL_VecSetLocked( pVector, bLock ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECSETBACKGROUNDCOLOR( pVector, Color ) \
   ((pL_VecSetBackgroundColor)? pL_VecSetBackgroundColor( pVector, Color ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETBACKGROUNDCOLOR( pVector ) \
   ((pL_VecGetBackgroundColor)? pL_VecGetBackgroundColor( pVector ):(LBase::RecordError(WRPERR_LVKRN_DLL_NOT_LOADED),(COLORREF)0))

#define L_VECLOGICALTOPHYSICAL( pVector, pDst, pSrc ) \
   ((pL_VecLogicalToPhysical)? pL_VecLogicalToPhysical( pVector, pDst, pSrc ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECPHYSICALTOLOGICAL( pVector, pDst, pSrc ) \
   ((pL_VecPhysicalToLogical)? pL_VecPhysicalToLogical( pVector, pDst, pSrc ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECSETPALETTE( pVector, hPalette ) \
   ((pL_VecSetPalette)? pL_VecSetPalette( pVector, hPalette ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETPALETTE( pVector ) \
   ((pL_VecGetPalette)? pL_VecGetPalette( pVector ):(LBase::RecordError(WRPERR_LVKRN_DLL_NOT_LOADED),(HPALETTE)0))

#define L_VECSETVIEWMODE( pVector, nMode ) \
   ((pL_VecSetViewMode)? pL_VecSetViewMode( pVector, nMode ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETVIEWMODE( pVector ) \
   ((pL_VecGetViewMode)? pL_VecGetViewMode( pVector ):WRPERR_LVKRN_DLL_NOT_LOADED)

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Transformation function.                                             []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
#define L_VECSETTRANSLATION( pVector, pTranslation, pObject, dwFlags ) \
   ((pL_VecSetTranslation)? pL_VecSetTranslation( pVector, pTranslation, pObject, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETTRANSLATION( pVector, pTranslation ) \
   ((pL_VecGetTranslation)? pL_VecGetTranslation( pVector, pTranslation ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECSETROTATION( pVector, pRotation, pObject, pOrigin, dwFlags ) \
   ((pL_VecSetRotation)? pL_VecSetRotation( pVector, pRotation, pObject, pOrigin, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETROTATION( pVector, pRotation) \
   ((pL_VecGetRotation)? pL_VecGetRotation( pVector, pRotation):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECSETSCALE( pVector, pScale, pObject, pOrigin, dwFlags ) \
   ((pL_VecSetScale)? pL_VecSetScale( pVector, pScale, pObject, pOrigin, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETSCALE( pVector, pScale ) \
   ((pL_VecGetScale)? pL_VecGetScale( pVector, pScale ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECSETORIGIN( pVector, pOrigin ) \
   ((pL_VecSetOrigin)? pL_VecSetOrigin( pVector, pOrigin ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETORIGIN( pVector, pOrigin ) \
   ((pL_VecGetOrigin)? pL_VecGetOrigin( pVector, pOrigin ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECAPPLYTRANSFORMATION( pVector ) \
   ((pL_VecApplyTransformation)? pL_VecApplyTransformation( pVector ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECZOOMRECT( pVector, pRect ) \
   ((pL_VecZoomRect)? pL_VecZoomRect( pVector, pRect ):WRPERR_LVKRN_DLL_NOT_LOADED)

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Attributes functions.                                                []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
#define L_VECSETBINDVERTICESMODE( pVector, nMode ) \
   ((pL_VecSetBindVerticesMode)? pL_VecSetBindVerticesMode( pVector, nMode ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETBINDVERTICESMODE( pVector ) \
   ((pL_VecGetBindVerticesMode)? pL_VecGetBindVerticesMode( pVector ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECSETPARALLELOGRAM( pVector, pMin, pMax ) \
   ((pL_VecSetParallelogram)? pL_VecSetParallelogram( pVector, pMin, pMax ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETPARALLELOGRAM( pVector, pMin, pMax ) \
   ((pL_VecGetParallelogram)? pL_VecGetParallelogram( pVector, pMin, pMax ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECENUMVERTICES( pVector, pEnumProc, pUserData, dwFlags ) \
   ((pL_VecEnumVertices)? pL_VecEnumVertices( pVector, pEnumProc, pUserData, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Camera functions.                                                    []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
#define L_VECSETCAMERA( pVector, pCamera ) \
   ((pL_VecSetCamera)? pL_VecSetCamera( pVector, pCamera ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETCAMERA( pVector, pCamera ) \
   ((pL_VecGetCamera)? pL_VecGetCamera( pVector, pCamera ):WRPERR_LVKRN_DLL_NOT_LOADED)

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Metafile functions.                                                  []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
#define L_VECCONVERTTOWMF( hDC, pVector, pRect, uDPI ) \
   ((pL_VecConvertToWMF)? pL_VecConvertToWMF( hDC, pVector, pRect, uDPI ):(LBase::RecordError(WRPERR_LVKRN_DLL_NOT_LOADED),(HMETAFILE)0))

#define L_VECCONVERTFROMWMF( hDC, pVector, hWMF ) \
   ((pL_VecConvertFromWMF)? pL_VecConvertFromWMF( hDC, pVector, hWMF ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECCONVERTTOEMF( hDC, pVector, pRect, uDPI ) \
   ((pL_VecConvertToEMF)? pL_VecConvertToEMF( hDC, pVector, pRect, uDPI ):(LBase::RecordError(WRPERR_LVKRN_DLL_NOT_LOADED),(HENHMETAFILE)0))

#define L_VECCONVERTFROMEMF( hDC, pVector, hEMF ) \
   ((pL_VecConvertFromEMF)? pL_VecConvertFromEMF( hDC, pVector, hEMF ):WRPERR_LVKRN_DLL_NOT_LOADED)

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Engine functions.                                                    []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
#define L_VECGETENGINE( pVector ) \
   ((pL_VecGetEngine)? pL_VecGetEngine( pVector ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECATTACHTOWINDOW( hWnd, pVector, nEngine, dwFlags ) \
   ((pL_VecAttachToWindow)? pL_VecAttachToWindow( hWnd, pVector, nEngine, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Marker functions.                                                    []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
#define L_VECSETMARKER( pVector, pMarker ) \
   ((pL_VecSetMarker)? pL_VecSetMarker( pVector, pMarker ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETMARKER( pVector, pMarker ) \
   ((pL_VecGetMarker)? pL_VecGetMarker( pVector, pMarker ):WRPERR_LVKRN_DLL_NOT_LOADED)

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Unit functions.                                                      []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
/* Reserved for internal use */
#define L_VECSETUNIT( pVector, pUnit ) \
   ((pL_VecSetUnit)? pL_VecSetUnit( pVector, pUnit ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETUNIT( pVector, pUnit ) \
   ((pL_VecGetUnit)? pL_VecGetUnit( pVector, pUnit ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECCONVERTPOINTTOUNITS( pVector, pptDst, pptSrc, UnitToUse ) \
   ((pL_VecConvertPointToUnits)? pL_VecConvertPointToUnits( pVector, pptDst, pptSrc, UnitToUse ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECCONVERTPOINTFROMUNITS( pVector, pptDst, pptSrc, UnitToUse ) \
   ((pL_VecConvertPointFromUnits)? pL_VecConvertPointFromUnits( pVector, pptDst, pptSrc, UnitToUse ):WRPERR_LVKRN_DLL_NOT_LOADED)

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Hit test functions.                                                  []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
#define L_VECSETHITTEST( pVector, pHitTest ) \
   ((pL_VecSetHitTest)? pL_VecSetHitTest( pVector, pHitTest ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETHITTEST( pVector, pHitTest ) \
   ((pL_VecGetHitTest)? pL_VecGetHitTest( pVector, pHitTest ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECHITTEST( pVector, pPoint, pObject ) \
   ((pL_VecHitTest)? pL_VecHitTest( pVector, pPoint, pObject ):WRPERR_LVKRN_DLL_NOT_LOADED)

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Polygon functions.                                                   []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
#define L_VECSETPOLYGONMODE( pVector, nMode ) \
   ((pL_VecSetPolygonMode)? pL_VecSetPolygonMode( pVector, nMode ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETPOLYGONMODE( pVector ) \
   ((pL_VecGetPolygonMode)? pL_VecGetPolygonMode( pVector ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECSETUSELIGHTS( pVector, bUseLights ) \
   ((pL_VecSetUseLights)? pL_VecSetUseLights( pVector, bUseLights ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETUSELIGHTS( pVector ) \
   ((pL_VecGetUseLights)? pL_VecGetUseLights( pVector ):(LBase::RecordError(WRPERR_LVKRN_DLL_NOT_LOADED),(L_BOOL)0))

#define L_VECSETAMBIENTCOLOR( pVector, Color ) \
   ((pL_VecSetAmbientColor)? pL_VecSetAmbientColor( pVector, Color ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETAMBIENTCOLOR( pVector ) \
   ((pL_VecGetAmbientColor)? pL_VecGetAmbientColor( pVector ):(LBase::RecordError(WRPERR_LVKRN_DLL_NOT_LOADED),(COLORREF)0))

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Clipboard functions.                                                 []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
#define L_VECCLIPBOARDREADY() \
   ((pL_VecClipboardReady)? pL_VecClipboardReady():(LBase::RecordError(WRPERR_LVKRN_DLL_NOT_LOADED),(L_BOOL)0))

#define L_VECCOPYTOCLIPBOARD( hWnd, pVector, dwFlags ) \
   ((pL_VecCopyToClipboard)? pL_VecCopyToClipboard( hWnd, pVector, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECCOPYFROMCLIPBOARD( hWnd, pVector, dwFlags ) \
   ((pL_VecCopyFromClipboard)? pL_VecCopyFromClipboard( hWnd, pVector, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Layer functions.                                                     []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
#define L_VECADDLAYER( pVector, pLayerDesc, pLayer, dwFlags ) \
   ((pL_VecAddLayer)? pL_VecAddLayer( pVector, pLayerDesc, pLayer, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDELETELAYER( pVector, pLayer ) \
   ((pL_VecDeleteLayer)? pL_VecDeleteLayer( pVector, pLayer ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECEMPTYLAYER( pVector, pLayer ) \
   ((pL_VecEmptyLayer)? pL_VecEmptyLayer( pVector, pLayer ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECCOPYLAYER( pVectorDst, pLayerDst, pVectorSrc, pLayerSrc, dwFlags ) \
   ((pL_VecCopyLayer)? pL_VecCopyLayer( pVectorDst, pLayerDst, pVectorSrc, pLayerSrc, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETLAYERBYNAME( pVector, pszName, pLayer ) \
   ((pL_VecGetLayerByName)? pL_VecGetLayerByName( pVector, pszName, pLayer ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETLAYERCOUNT( pVector ) \
   ((pL_VecGetLayerCount)? pL_VecGetLayerCount( pVector ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETLAYERBYINDEX( pVector, nIndex, pLayer ) \
   ((pL_VecGetLayerByIndex)? pL_VecGetLayerByIndex( pVector, nIndex, pLayer ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETLAYER( pVector, pLayer, pLayerDesc ) \
   ((pL_VecGetLayer)? pL_VecGetLayer( pVector, pLayer, pLayerDesc ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECFREELAYER( pLayerDesc) \
   ((pL_VecFreeLayer)? pL_VecFreeLayer( pLayerDesc):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECSETLAYER( pVector, pLayer, pLayerDesc ) \
   ((pL_VecSetLayer)? pL_VecSetLayer( pVector, pLayer, pLayerDesc ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECSETACTIVELAYER( pVector, pLayer ) \
   ((pL_VecSetActiveLayer)? pL_VecSetActiveLayer( pVector, pLayer ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETACTIVELAYER( pVector, pLayer ) \
   ((pL_VecGetActiveLayer)? pL_VecGetActiveLayer( pVector, pLayer ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECENUMLAYERS( pVector, pEnumProc, pUserData ) \
   ((pL_VecEnumLayers)? pL_VecEnumLayers( pVector, pEnumProc, pUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Group functions.                                                     []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
#define L_VECADDGROUP( pVector, pGroupDesc, pGroup, dwFlags ) \
   ((pL_VecAddGroup)? pL_VecAddGroup( pVector, pGroupDesc, pGroup, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDELETEGROUP( pVector, pGroup ) \
   ((pL_VecDeleteGroup)? pL_VecDeleteGroup( pVector, pGroup ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDELETEGROUPCLONES( pVector, pGroup, dwFlags ) \
   ((pL_VecDeleteGroupClones)? pL_VecDeleteGroupClones( pVector, pGroup, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECEMPTYGROUP( pVector, pGroup ) \
   ((pL_VecEmptyGroup)? pL_VecEmptyGroup( pVector, pGroup ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECCOPYGROUP( pVectorDst, pGroupDst, pVectorSrc, pGroupSrc, dwFlags ) \
   ((pL_VecCopyGroup)? pL_VecCopyGroup( pVectorDst, pGroupDst, pVectorSrc, pGroupSrc, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETGROUPBYNAME( pVector, pszName, pGroup ) \
   ((pL_VecGetGroupByName)? pL_VecGetGroupByName( pVector, pszName, pGroup ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETGROUPCOUNT( pVector ) \
   ((pL_VecGetGroupCount)? pL_VecGetGroupCount( pVector ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETGROUPBYINDEX( pVector, nIndex, pGroup ) \
   ((pL_VecGetGroupByIndex)? pL_VecGetGroupByIndex( pVector, nIndex, pGroup ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETGROUP( pVector, pGroup, pGroupDesc ) \
   ((pL_VecGetGroup)? pL_VecGetGroup( pVector, pGroup, pGroupDesc ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECFREEGROUP( pGroupDesc ) \
   ((pL_VecFreeGroup)? pL_VecFreeGroup( pGroupDesc ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECSETGROUP( pVector, pGroup, pGroupDesc ) \
   ((pL_VecSetGroup)? pL_VecSetGroup( pVector, pGroup, pGroupDesc ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECENUMGROUPS( pVector, pEnumProc, pUserData ) \
   ((pL_VecEnumGroups)? pL_VecEnumGroups( pVector, pEnumProc, pUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Object functions.                                                    []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
#define L_VECINITOBJECT( pObject ) \
   ((pL_VecInitObject)? pL_VecInitObject( pObject ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECADDOBJECT( pVector, pLayer, nType, pObjectDesc, pNewObject) \
   ((pL_VecAddObject)? pL_VecAddObject( pVector, pLayer, nType, pObjectDesc, pNewObject):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDELETEOBJECT( pVector, pObject, dwFlags ) \
   ((pL_VecDeleteObject)? pL_VecDeleteObject( pVector, pObject, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECCOPYOBJECT( pVectorDst, pLayerDst, pObjectDst, pVectorSrc, pObjectSrc ) \
   ((pL_VecCopyObject)? pL_VecCopyObject( pVectorDst, pLayerDst, pObjectDst, pVectorSrc, pObjectSrc ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETOBJECT( pVector, pObject, nType, pObjectDesc ) \
   ((pL_VecGetObject)? pL_VecGetObject( pVector, pObject, nType, pObjectDesc ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECFREEOBJECT( nType, pObjectDesc ) \
   ((pL_VecFreeObject)? pL_VecFreeObject( nType, pObjectDesc ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECSETOBJECT( pVector, pObject, nType, pObjectDesc ) \
   ((pL_VecSetObject)? pL_VecSetObject( pVector, pObject, nType, pObjectDesc ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECEXPLODEOBJECT( pVector, pObject, dwFlags ) \
   ((pL_VecExplodeObject)? pL_VecExplodeObject( pVector, pObject, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETOBJECTPARALLELOGRAM( pVector, pObject, pMin, pMax, dwFlags ) \
   ((pL_VecGetObjectParallelogram)? pL_VecGetObjectParallelogram( pVector, pObject, pMin, pMax, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECGETOBJECTRECT( pVector, pObject, pRect, dwFlags ) \
   ((pL_VecGetObjectRect)? pL_VecGetObjectRect( pVector, pObject, pRect, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECISOBJECTINSIDEPARALLELOGRAM( pVector, pObject, pMin, pMax, dwFlags ) \
   ((pL_VecIsObjectInsideParallelogram)? pL_VecIsObjectInsideParallelogram( pVector, pObject, pMin, pMax, dwFlags ):(LBase::RecordError(WRPERR_LVKRN_DLL_NOT_LOADED),(L_BOOL)0))

#define L_VECISOBJECTINSIDERECT( pVector, pObject, pRect, dwFlags ) \
   ((pL_VecIsObjectInsideRect)? pL_VecIsObjectInsideRect( pVector, pObject, pRect, dwFlags ):(LBase::RecordError(WRPERR_LVKRN_DLL_NOT_LOADED),(L_BOOL)0))

#define L_VECSELECTOBJECT( pVector, pObject, bSelect ) \
   ((pL_VecSelectObject)? pL_VecSelectObject( pVector, pObject, bSelect ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECISOBJECTSELECTED( pVector, pObject ) \
   ((pL_VecIsObjectSelected)? pL_VecIsObjectSelected( pVector, pObject ):(LBase::RecordError(WRPERR_LVKRN_DLL_NOT_LOADED),(L_BOOL)0))

#define L_VECHIDEOBJECT( pVector, pObject, bHide ) \
   ((pL_VecHideObject)? pL_VecHideObject( pVector, pObject, bHide ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECISOBJECTHIDDEN( pVector, pObject ) \
   ((pL_VecIsObjectHidden)? pL_VecIsObjectHidden( pVector, pObject ):(LBase::RecordError(WRPERR_LVKRN_DLL_NOT_LOADED),(L_BOOL)0))

#define L_VECENUMOBJECTS( pVector, pEnumProc, pUserData, dwFlags ) \
   ((pL_VecEnumObjects)? pL_VecEnumObjects( pVector, pEnumProc, pUserData, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECENUMOBJECTSINLAYER( pVector, pLayer, pEnumProc, pUserData, dwFlags ) \
   ((pL_VecEnumObjectsInLayer)? pL_VecEnumObjectsInLayer( pVector, pLayer, pEnumProc, pUserData, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECSETOBJECTATTRIBUTES( pVector, pObject, pnROP, pPen, pBrush, pFont, dwFlags ) \
   ((pL_VecSetObjectAttributes)? pL_VecSetObjectAttributes( pVector, pObject, pnROP, pPen, pBrush, pFont, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECSETOBJECTTOOLTIP( pVector, pObject, pszTooltip ) \
   ( ( pL_VecSetObjectTooltip ) ? pL_VecSetObjectTooltip( pVector, pObject, pszTooltip ):WRPERR_LVKRN_DLL_NOT_LOADED )

#define L_VECGETOBJECTTOOLTIP( pVector, pObject, pBuffer, uSize ) \
   ( ( pL_VecGetObjectTooltip ) ? pL_VecGetObjectTooltip( pVector, pObject, pBuffer, uSize ): 0 )

#define L_VECSHOWOBJECTTOOLTIP( pVector, pObject, pTooltipDesc ) \
   ( ( pL_VecShowObjectTooltip ) ? pL_VecShowObjectTooltip( pVector, pObject, pTooltipDesc ):WRPERR_LVKRN_DLL_NOT_LOADED )

#define L_VECHIDEOBJECTTOOLTIP( pVector, pObject ) \
   ( ( pL_VecHideObjectTooltip ) ? pL_VecHideObjectTooltip( pVector, pObject ):WRPERR_LVKRN_DLL_NOT_LOADED )

#define L_VECSETOBJECTVIEWCONTEXT( pVector, pObject, pMin, pMax ) \
   ( ( pL_VecSetObjectViewContext ) ? pL_VecSetObjectViewContext( pVector, pObject, pMin, pMax ):WRPERR_LVKRN_DLL_NOT_LOADED )

#define L_VECGETOBJECTVIEWCONTEXT( pVector, pObject, pMin, pMax ) \
   ( ( pL_VecGetObjectViewContext ) ? pL_VecGetObjectViewContext( pVector, pObject, pMin, pMax ):WRPERR_LVKRN_DLL_NOT_LOADED )

#define L_VECREMOVEOBJECTVIEWCONTEXT( pVector, pObject ) \
   ( ( pL_VecRemoveObjectViewContext ) ? pL_VecRemoveObjectViewContext( pVector, pObject ):WRPERR_LVKRN_DLL_NOT_LOADED )

#define L_VECADDHYPERLINK( pVector, pObject, pTarget ) \
   ( ( pL_VecAddHyperlink ) ? pL_VecAddHyperlink( pVector, pObject, pTarget ):WRPERR_LVKRN_DLL_NOT_LOADED )

#define L_VECSETHYPERLINK( pVector, pObject, uIndex, pTarget ) \
   ( ( pL_VecSetHyperlink ) ? pL_VecSetHyperlink( pVector, pObject, uIndex, pTarget ):WRPERR_LVKRN_DLL_NOT_LOADED )

#define L_VECGETHYPERLINK( pVector, pObject, uIndex, pTarget ) \
   ( ( pL_VecGetHyperlink ) ? pL_VecGetHyperlink( pVector, pObject, uIndex, pTarget ):WRPERR_LVKRN_DLL_NOT_LOADED )

#define L_VECGETHYPERLINKCOUNT( pVector, pObject ) \
   ( ( pL_VecGetHyperlinkCount ) ? pL_VecGetHyperlinkCount( pVector, pObject ): 0 )

#define L_VECGOTOHYPERLINK( pVector, pObject, uIndex ) \
   ( ( pL_VecGotoHyperlink ) ? pL_VecGotoHyperlink( pVector, pObject, uIndex ):WRPERR_LVKRN_DLL_NOT_LOADED )

#define L_VECSETOBJECTDESCRIPTION( pVector, pObject, pszTarget ) \
   ( ( pL_VecSetObjectDescription ) ? pL_VecSetObjectDescription( pVector, pObject, pszTarget ):WRPERR_LVKRN_DLL_NOT_LOADED )

#define L_VECGETOBJECTDESCRIPTION( pVector, pObject, pBuffer, uSize ) \
   ( ( pL_VecGetObjectDescription ) ? pL_VecGetObjectDescription( pVector, pObject, pBuffer, uSize ): 0 )

#define L_VECGETOBJECTATTRIBUTES( pVector, pObject, pnROP, pPen, pBrush, pFont ) \
   ((pL_VecGetObjectAttributes)? pL_VecGetObjectAttributes( pVector, pObject, pnROP, pPen, pBrush, pFont ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECADDOBJECTTOGROUP( pVector, pGroup, nType, pObjectDesc, pNewObject ) \
   ((pL_VecAddObjectToGroup)? pL_VecAddObjectToGroup( pVector, pGroup, nType, pObjectDesc, pNewObject ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECENUMOBJECTSINGROUP( pVector, pGroup, pEnumProc, pUserData, dwFlags ) \
   ((pL_VecEnumObjectsInGroup)? pL_VecEnumObjectsInGroup( pVector, pGroup, pEnumProc, pUserData, dwFlags ):WRPERR_LVKRN_DLL_NOT_LOADED)

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Event functions.                                                     []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
#define L_VECSETEVENTCALLBACK( pVector, pProc, pUserData, pOldProc, pOldUserData ) \
   ((pL_VecSetEventCallback)? pL_VecSetEventCallback( pVector, pProc, pUserData, pOldProc, pOldUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECEVENT( pVECTORHANDLE, pVECTOREVENT ) \
   ((pL_VecEvent)? pL_VecEvent( pVECTORHANDLE, pVECTOREVENT ):WRPERR_LVKRN_DLL_NOT_LOADED)


//-----------------------------------------------------------------------------
//--LVDLG.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
#define L_VECDLGROTATE( hWnd, pVector, pRotation, pOrigin, dwFlags, pfnHelpCallback, pUserData ) \
   ((pL_VecDlgRotate)? pL_VecDlgRotate( hWnd, pVector, pRotation, pOrigin, dwFlags, pfnHelpCallback, pUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGSCALE( hWnd, pVector, pScale, pOrigin, dwFlags, pfnHelpCallback, pUserData ) \
   ((pL_VecDlgScale)? pL_VecDlgScale( hWnd, pVector, pScale, pOrigin, dwFlags, pfnHelpCallback, pUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGTRANSLATE( hWnd, pVector, pTranslation, dwFlags, pfnHelpCallback, pUserData ) \
   ((pL_VecDlgTranslate)? pL_VecDlgTranslate( hWnd, pVector, pTranslation, dwFlags, pfnHelpCallback, pUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGCAMERA( hWnd, pVector, pCamera, dwFlags, pfnHelpCallback, pUserData ) \
   ((pL_VecDlgCamera)? pL_VecDlgCamera( hWnd, pVector, pCamera, dwFlags, pfnHelpCallback, pUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGRENDER( hWnd, pVector, pbUseLights, pColorAmbient, pnPolygonMode, dwFlags, pfnHelpCallback, pUserData ) \
   ((pL_VecDlgRender)? pL_VecDlgRender( hWnd, pVector, pbUseLights, pColorAmbient, pnPolygonMode, dwFlags, pfnHelpCallback, pUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGVIEWMODE( hWnd, pVector, pnViewMode, dwFlags, pfnHelpCallback, pUserData ) \
   ((pL_VecDlgViewMode)? pL_VecDlgViewMode( hWnd, pVector, pnViewMode, dwFlags, pfnHelpCallback, pUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGHITTEST( hWnd, pVector, pHitTest, dwFlags, pfnHelpCallback, pUserData ) \
   ((pL_VecDlgHitTest)? pL_VecDlgHitTest( hWnd, pVector, pHitTest, dwFlags, pfnHelpCallback, pUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGEDITALLLAYERS( hWnd, pVector, dwFlags, pfnHelpCallback, pUserData ) \
   ((pL_VecDlgEditAllLayers)? pL_VecDlgEditAllLayers( hWnd, pVector, dwFlags, pfnHelpCallback, pUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGNEWLAYER( hWnd, pVector, pLayerDesc, pLayer, pbActiveLayer, dwFlags, pfnHelpCallback, pUserData ) \
   ((pL_VecDlgNewLayer)? pL_VecDlgNewLayer( hWnd, pVector, pLayerDesc, pLayer, pbActiveLayer, dwFlags, pfnHelpCallback, pUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGEDITLAYER( hWnd, pVector, pLayer, pLayerDesc, pbActiveLayer, dwFlags, pfnHelpCallback, pUserData ) \
   ((pL_VecDlgEditLayer)? pL_VecDlgEditLayer( hWnd, pVector, pLayer, pLayerDesc, pbActiveLayer, dwFlags, pfnHelpCallback, pUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGEDITALLGROUPS( hWnd, pVector, dwFlags, pfnHelpCallback, pUserData ) \
   ((pL_VecDlgEditAllGroups)? pL_VecDlgEditAllGroups( hWnd, pVector, dwFlags, pfnHelpCallback, pUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGNEWGROUP( hWnd, pVector, pGroupDesc, pGroup, dwFlags, pfnHelpCallback, pUserData ) \
   ((pL_VecDlgNewGroup)? pL_VecDlgNewGroup( hWnd, pVector, pGroupDesc, pGroup, dwFlags, pfnHelpCallback, pUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGEDITGROUP( hWnd, pVector, pGroup, pGroupDesc, dwFlags, pfnHelpCallback, pUserData ) \
   ((pL_VecDlgEditGroup)? pL_VecDlgEditGroup( hWnd, pVector, pGroup, pGroupDesc, dwFlags, pfnHelpCallback, pUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGNEWOBJECT( hWnd, pVector, pLayer, nType, pObjectDesc, pVECTOROBJECT, dwFlags, pfnHelpCallback, pUserData ) \
   ((pL_VecDlgNewObject)? pL_VecDlgNewObject( hWnd, pVector, pLayer, nType, pObjectDesc, pVECTOROBJECT, dwFlags, pfnHelpCallback, pUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGEDITOBJECT( hWnd, pVector, pObject, nType, pObjectDesc, dwFlags, pfnHelpCallback, pUserData ) \
   ((pL_VecDlgEditObject)? pL_VecDlgEditObject( hWnd, pVector, pObject, nType, pObjectDesc, dwFlags, pfnHelpCallback, pUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGOBJECTATTRIBUTES( hWnd, pVector, pObject, pbSelected, pnROP, pPen, pBrush, pFont, dwFlags, pfnHelpCallback, pUserData ) \
   ((pL_VecDlgObjectAttributes)? pL_VecDlgObjectAttributes( hWnd, pVector, pObject, pbSelected, pnROP, pPen, pBrush, pFont, dwFlags, pfnHelpCallback, pUserData ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGGETSTRINGLEN( uString, puLen ) \
   ((pL_VecDlgGetStringLen)? pL_VecDlgGetStringLen( uString, puLen ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGGETSTRING( uString, pszString ) \
   ((pL_VecDlgGetString)? pL_VecDlgGetString( uString, pszString ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGSETSTRING( uString, pszString ) \
   ((pL_VecDlgSetString)? pL_VecDlgSetString( uString, pszString ):WRPERR_LVKRN_DLL_NOT_LOADED)

#define L_VECDLGSETFONT( hFont ) \
   ((pL_VecDlgSetFont)? pL_VecDlgSetFont( hFont ):(LBase::RecordError(WRPERR_LVKRN_DLL_NOT_LOADED),(HFONT)0))


//-----------------------------------------------------------------------------
//--LTBAR.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
#define L_BARCODEREAD( pBitmap, prcSearch, ulSearchType, nUnits, ulFlags, nMultipleMaxCount, pBarCode1D, pBarCodePDF, pBarCodeColor, ppBarCodeData) \
   ((pL_BarCodeRead)? pL_BarCodeRead( pBitmap, prcSearch, ulSearchType, nUnits, ulFlags, nMultipleMaxCount, pBarCode1D, pBarCodePDF, pBarCodeColor, ppBarCodeData):WRPERR_LTBAR_DLL_NOT_LOADED)

#define L_BARCODEWRITE( pBitmap, pBarCodeData, pBarCodeColor, ulFlags, pBarCode1D, pBarCode2D, pBarCodePDF, lprcSize) \
   ((pL_BarCodeWrite)? pL_BarCodeWrite( pBitmap, pBarCodeData, pBarCodeColor, ulFlags, pBarCode1D, pBarCode2D, pBarCodePDF, lprcSize):WRPERR_LTBAR_DLL_NOT_LOADED)

#define L_BARCODEFREE(ppBarCodeData) \
   ((pL_BarCodeFree)? pL_BarCodeFree(ppBarCodeData):(LBase::RecordError(WRPERR_LTBAR_DLL_NOT_LOADED)))

#define L_BARCODEISDUPLICATED( pBarCodeDataItem) \
   ((pL_BarCodeIsDuplicated)? pL_BarCodeIsDuplicated( pBarCodeDataItem):(LBase::RecordError(WRPERR_LTBAR_DLL_NOT_LOADED),(L_BOOL)0))

#define L_BARCODEGETDUPLICATED( pBarCodeDataItem) \
   ((pL_BarCodeGetDuplicated)? pL_BarCodeGetDuplicated( pBarCodeDataItem):WRPERR_LTBAR_DLL_NOT_LOADED)

#define L_BARCODEGETFIRSTDUPLICATED( pBarCodeData, nIndex) \
   ((pL_BarCodeGetFirstDuplicated)? pL_BarCodeGetFirstDuplicated( pBarCodeData, nIndex):WRPERR_LTBAR_DLL_NOT_LOADED)

#define L_BARCODEGETNEXTDUPLICATED( pBarCodeData, nCurIndex) \
   ((pL_BarCodeGetNextDuplicated)? pL_BarCodeGetNextDuplicated( pBarCodeData, nCurIndex):WRPERR_LTBAR_DLL_NOT_LOADED)

#define L_BARCODEINIT(nMajorType) \
   ((pL_BarCodeInit )? pL_BarCodeInit(nMajorType):WRPERR_LTBAR_DLL_NOT_LOADED)

#define L_BARCODEEXIT() \
   ((pL_BarCodeExit)? pL_BarCodeExit():(LBase::RecordError(WRPERR_LTBAR_DLL_NOT_LOADED)))

#define L_BARCODEVERSIONINFO( pBarCodeVersion) \
   ((pL_BarCodeVersionInfo)? pL_BarCodeVersionInfo( pBarCodeVersion):(LBase::RecordError(WRPERR_LTBAR_DLL_NOT_LOADED),(L_INT  )0))

#define L_BARCODEWRITEEXT(pBitmap, pBarCodeData, pBarCodeColor, ulFlags, pBarCode1D, pBarCodePDF, pBarCodeDM, lprcSize) \
   ((pL_BarCodeWriteExt)? pL_BarCodeWriteExt(pBitmap, pBarCodeData, pBarCodeColor, ulFlags, pBarCode1D, pBarCodePDF, pBarCodeDM, lprcSize):(LBase::RecordError(WRPERR_LTBAR_DLL_NOT_LOADED),(L_INT  )0))

//-----------------------------------------------------------------------------
//--LTAUT.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
// General functions.
#define L_AUTISVALID(pAutomation)\
   ((pL_AutIsValid)? pL_AutIsValid(pAutomation):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTINIT(ppAutomation)\
   ((pL_AutInit)? pL_AutInit(ppAutomation):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTCREATE(pAutomation, nMode, dwFlags)\
   ((pL_AutCreate)? pL_AutCreate(pAutomation, nMode, dwFlags):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTFREE(pAutomation)\
   ((pL_AutFree)? pL_AutFree(pAutomation):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTSETUNDOLEVEL(pAutomation, uLevel)\
   ((pL_AutSetUndoLevel)? pL_AutSetUndoLevel(pAutomation, uLevel):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTGETUNDOLEVEL(pAutomation, puLevel)\
   ((pL_AutGetUndoLevel)? pL_AutGetUndoLevel(pAutomation, puLevel):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTCANUNDO(pAutomation, pfCanUndo)\
   ((pL_AutCanUndo)? pL_AutCanUndo(pAutomation, pfCanUndo):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTCANREDO(pAutomation, pfCanRedo)\
   ((pL_AutCanRedo)? pL_AutCanRedo(pAutomation, pfCanRedo):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTUNDO(pAutomation, dwFlags)\
   ((pL_AutUndo)? pL_AutUndo(pAutomation, dwFlags):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTREDO(pAutomation, dwFlags)\
   ((pL_AutRedo)? pL_AutRedo(pAutomation, dwFlags):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTSETUNDOENABLED(pAutomation, bEnabled)\
   ((pL_AutSetUndoEnabled)? pL_AutSetUndoEnabled(pAutomation, bEnabled):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTADDUNDONODE(pAutomation, dwFlags)\
   ((pL_AutAddUndoNode)? pL_AutAddUndoNode(pAutomation, dwFlags):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTSELECT(pAutomation, nSelect, dwFlags)\
   ((pL_AutSelect)? pL_AutSelect(pAutomation, nSelect, dwFlags):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTCLIPBOARDDATAREADY(pAutomation, pfReady)\
   ((pL_AutClipboardDataReady)? pL_AutClipboardDataReady(pAutomation, pfReady):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTCUT(pAutomation, dwFlags)\
   ((pL_AutCut)? pL_AutCut(pAutomation, dwFlags):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTCOPY(pAutomation, dwFlags)\
   ((pL_AutCopy)? pL_AutCopy(pAutomation, dwFlags):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTPASTE(pAutomation, dwFlags)\
   ((pL_AutPaste)? pL_AutPaste(pAutomation, dwFlags):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTDELETE(pAutomation, dwFlags)\
   ((pL_AutDelete)? pL_AutDelete(pAutomation, dwFlags):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTPRINT(pAutomation, dwFlags)\
   ((pL_AutPrint)? pL_AutPrint(pAutomation, dwFlags):WRPERR_LTAUT_DLL_NOT_LOADED)


// Container Functions.
#define L_AUTADDCONTAINER(pAutomation, pContainer , pModeData)\
   ((pL_AutAddContainer)? pL_AutAddContainer(pAutomation, pContainer , pModeData):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTREMOVECONTAINER(pAutomation, pContainer)\
   ((pL_AutRemoveContainer)? pL_AutRemoveContainer(pAutomation, pContainer):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTSETACTIVECONTAINER(pAutomation, pContainer)\
   ((pL_AutSetActiveContainer)? pL_AutSetActiveContainer(pAutomation, pContainer):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTGETACTIVECONTAINER(pAutomation, ppContainer)\
   ((pL_AutGetActiveContainer)? pL_AutGetActiveContainer(pAutomation, ppContainer):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTENUMCONTAINERS(pAutomation, pEnumProc, pUserData)\
   ((pL_AutEnumContainers)? pL_AutEnumContainers(pAutomation, pEnumProc, pUserData):WRPERR_LTAUT_DLL_NOT_LOADED)


// Painting Functionts.
#define L_AUTSETPAINTPROPERTY(pAutomation, nGroup, pProperty)\
   ((pL_AutSetPaintProperty)? pL_AutSetPaintProperty(pAutomation, nGroup, pProperty):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTGETPAINTPROPERTY(pAutomation, nGroup, pProperty)\
   ((pL_AutGetPaintProperty)? pL_AutGetPaintProperty(pAutomation, nGroup, pProperty):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTSETPAINTBKCOLOR(pAutomation, rcBKColor)\
   ((pL_AutSetPaintBkColor)? pL_AutSetPaintBkColor(pAutomation, rcBKColor):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTGETPAINTBKCOLOR(pAutomation, prcBKColor)\
   ((pL_AutGetPaintBkColor)? pL_AutGetPaintBkColor(pAutomation, prcBKColor):WRPERR_LTAUT_DLL_NOT_LOADED)


// Vector Functions.
#define L_AUTSETVECTORPROPERTY(pAutomation, pAUTOMATIONVECTORPROPERTIES)\
   ((pL_AutSetVectorProperty)? pL_AutSetVectorProperty(pAutomation, pAUTOMATIONVECTORPROPERTIES):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTGETVECTORPROPERTY(pAutomation, pAUTOMATIONVECTORPROPERTIES)\
   ((pL_AutGetVectorProperty)? pL_AutGetVectorProperty(pAutomation, pAUTOMATIONVECTORPROPERTIES):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTEDITVECTOROBJECT(pAUTOMATIONHANDLE, pVECTOROBJECT)\
   ((pL_AutEditVectorObject)? pL_AutEditVectorObject(pAUTOMATIONHANDLE, pVECTOROBJECT):WRPERR_LTAUT_DLL_NOT_LOADED)


//Toolbar Functions.
#define L_AUTSETTOOLBAR(pAutomation, pToolbar)\
   ((pL_AutSetToolbar)? pL_AutSetToolbar(pAutomation, pToolbar):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTGETTOOLBAR(pAutomation, ppToolbar)\
   ((pL_AutGetToolbar)? pL_AutGetToolbar(pAutomation, ppToolbar):WRPERR_LTAUT_DLL_NOT_LOADED)


#define L_AUTSETCURRENTTOOL(pAutomation, nTool)\
   ((pL_AutSetCurrentTool)? pL_AutSetCurrentTool(pAutomation, nTool):WRPERR_LTAUT_DLL_NOT_LOADED)

#define L_AUTGETCURRENTTOOL(pAutomation, pnTool)\
   ((pL_AutGetCurrentTool)? pL_AutGetCurrentTool(pAutomation, pnTool):WRPERR_LTAUT_DLL_NOT_LOADED)




//-----------------------------------------------------------------------------
//--LTCON.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
// general container operations funtions.
#define L_CONTAINERISVALID(pContainer)  \
   ((pL_ContainerIsValid)? pL_ContainerIsValid(pContainer):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERINIT(ppContainer)  \
   ((pL_ContainerInit)? pL_ContainerInit(ppContainer):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERCREATE(pContainer, hwndOwner)  \
   ((pL_ContainerCreate)? pL_ContainerCreate(pContainer, hwndOwner):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERFREE(pContainer)  \
   ((pL_ContainerFree)? pL_ContainerFree(pContainer):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERUPDATE(pContainer, prcPaint)  \
   ((pL_ContainerUpdate)? pL_ContainerUpdate(pContainer, prcPaint):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERRESET(pContainer)  \
   ((pL_ContainerReset)? pL_ContainerReset(pContainer):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINEREDITOBJECT(pContainer, pObjectData)  \
   ((pL_ContainerEditObject)? pL_ContainerEditObject(pContainer, pObjectData):WRPERR_LTCON_DLL_NOT_LOADED)


// setting functions.
#define L_CONTAINERSETOWNER(pContainer, hWndOwner)  \
   ((pL_ContainerSetOwner)? pL_ContainerSetOwner(pContainer, hWndOwner):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERSETMETRICS(pContainer, pMetrics)  \
   ((pL_ContainerSetMetrics)? pL_ContainerSetMetrics(pContainer, pMetrics):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERSETOFFSET(pContainer, nXOffset, nYOffset, nZOffset)  \
   ((pL_ContainerSetOffset)? pL_ContainerSetOffset(pContainer, nXOffset, nYOffset, nZOffset):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERSETSCALAR(pContainer, pvptScalarNum, pvptScalarDen)  \
   ((pL_ContainerSetScalar)? pL_ContainerSetScalar(pContainer, pvptScalarNum, pvptScalarDen):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERSETOBJECTTYPE(pContainer, nObjectType)  \
   ((pL_ContainerSetObjectType)? pL_ContainerSetObjectType(pContainer, nObjectType):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERSETOBJECTCURSOR(pContainer, nObjectType, hCursor)  \
   ((pL_ContainerSetObjectCursor)? pL_ContainerSetObjectCursor(pContainer, nObjectType, hCursor):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERSETENABLED(pContainer, fEnable)  \
   ((pL_ContainerSetEnabled)? pL_ContainerSetEnabled(pContainer, fEnable):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERSETCALLBACK(pContainer, pCallback, pUserData)  \
   ((pL_ContainerSetCallback)? pL_ContainerSetCallback(pContainer, pCallback, pUserData):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERSETOWNERDRAW(pContainer, fOwnerDraw, dwFlags)  \
   ((pL_ContainerSetOwnerDraw)? pL_ContainerSetOwnerDraw(pContainer, fOwnerDraw, dwFlags):WRPERR_LTCON_DLL_NOT_LOADED)


// getting functions.
#define L_CONTAINERGETOWNER(pContainer, phwndOwner)  \
   ((pL_ContainerGetOwner)? pL_ContainerGetOwner(pContainer, phwndOwner):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERGETMETRICS(pContainer, pMetrics)  \
   ((pL_ContainerGetMetrics)? pL_ContainerGetMetrics(pContainer, pMetrics):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERGETOFFSET(pContainer, pnXOffset, pnYOffset, pnZOffset)  \
   ((pL_ContainerGetOffset)? pL_ContainerGetOffset(pContainer, pnXOffset, pnYOffset, pnZOffset):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERGETSCALAR(pContainer, pvptScalarNum, pvptScalarDen)  \
   ((pL_ContainerGetScalar)? pL_ContainerGetScalar(pContainer, pvptScalarNum, pvptScalarDen):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERGETOBJECTTYPE(pContainer, pnObjectType)  \
   ((pL_ContainerGetObjectType)? pL_ContainerGetObjectType(pContainer, pnObjectType):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERGETOBJECTCURSOR(pContainer, nObjectType, phCursor)  \
   ((pL_ContainerGetObjectCursor)? pL_ContainerGetObjectCursor(pContainer, nObjectType, phCursor):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERGETCALLBACK(pContainer, ppCallback, ppUserData)  \
   ((pL_ContainerGetCallback)? pL_ContainerGetCallback(pContainer, ppCallback, ppUserData):WRPERR_LTCON_DLL_NOT_LOADED)


// status query functions.
#define L_CONTAINERISENABLED(pContainer, pfEnabled)  \
   ((pL_ContainerIsEnabled)? pL_ContainerIsEnabled(pContainer, pfEnabled):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERISOWNERDRAW(pContainer, pfOwnerDraw)  \
   ((pL_ContainerIsOwnerDraw)? pL_ContainerIsOwnerDraw(pContainer, pfOwnerDraw):WRPERR_LTCON_DLL_NOT_LOADED)


#define L_CONTAINERSETAUTOMATIONCALLBACK(pContainer, pAutomationCallback, pAutomationData)  \
   ((pL_ContainerSetAutomationCallback)? pL_ContainerSetAutomationCallback(pContainer, pAutomationCallback, pAutomationData):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_SCREENTOCONTAINER(pContainer, pptPoint)  \
   ((pL_ScreenToContainer)? pL_ScreenToContainer(pContainer, pptPoint):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERTOSCREEN(pContainer, pptPoint)  \
   ((pL_ContainerToScreen)? pL_ContainerToScreen(pContainer, pptPoint):WRPERR_LTCON_DLL_NOT_LOADED)

#define L_CONTAINERENABLEUPDATE(pContainer, fEnableUpdate)  \
   ((pL_ContainerEnableUpdate)? pL_ContainerEnableUpdate(pContainer, fEnableUpdate):WRPERR_LTCON_DLL_NOT_LOADED)

//-----------------------------------------------------------------------------
//--LTPNT.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
#define L_PNTISVALID(pPaint)  \
   ((pL_PntIsValid)? pL_PntIsValid(pPaint):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTINIT(ppPaint)  \
   ((pL_PntInit)? pL_PntInit(ppPaint):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTFREE(pPaint)  \
   ((pL_PntFree)? pL_PntFree(pPaint):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTSETPROPERTY(pPaint, nGroup, pProperty)  \
   ((pL_PntSetProperty)? pL_PntSetProperty(pPaint, nGroup, pProperty):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTGETPROPERTY(pPaint, nGroup, pProperty)  \
   ((pL_PntGetProperty)? pL_PntGetProperty(pPaint, nGroup, pProperty):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTSETMETRICS(pPaint, UserDC, pBitmap, hRestrictionPalette)  \
   ((pL_PntSetMetrics)? pL_PntSetMetrics(pPaint, UserDC, pBitmap, hRestrictionPalette):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTSETTRANSFORMATION(pPaint, pXForm)  \
   ((pL_PntSetTransformation)? pL_PntSetTransformation(pPaint, pXForm):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTGETTRANSFORMATION(pPaint, pXForm)  \
   ((pL_PntGetTransformation)? pL_PntGetTransformation(pPaint, pXForm):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTSETDCEXTENTS(pPaint, prcRect)  \
   ((pL_PntSetDCExtents)? pL_PntSetDCExtents(pPaint, prcRect):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTGETDCEXTENTS(pPaint, prcRect)  \
   ((pL_PntGetDCExtents)? pL_PntGetDCExtents(pPaint, prcRect):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTSETCLIPRGN(pPaint, hClipRng)  \
   ((pL_PntSetClipRgn)? pL_PntSetClipRgn(pPaint, hClipRng):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTGETCLIPRGN(pPaint, phClipRng)  \
   ((pL_PntGetClipRgn)? pL_PntGetClipRgn(pPaint, phClipRng):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTOFFSETCLIPRGN(pPaint, nDX, nDY )  \
   ((pL_PntOffsetClipRgn)? pL_PntOffsetClipRgn(pPaint, nDX, nDY ):WRPERR_LTPNT_DLL_NOT_LOADED)

// brush fucntions.
#define L_PNTBRUSHMOVETO(pPaint, UserDC, nX, nY)  \
   ((pL_PntBrushMoveTo)? pL_PntBrushMoveTo(pPaint, UserDC, nX, nY):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTBRUSHLINETO(pPaint, UserDC, nX, nY)  \
   ((pL_PntBrushLineTo)? pL_PntBrushLineTo(pPaint, UserDC, nX, nY):WRPERR_LTPNT_DLL_NOT_LOADED)


// shape functions.
#define L_PNTDRAWSHAPELINE(pPaint, UserDC, nXStart, nYStart, nEndX, nEndY)  \
   ((pL_PntDrawShapeLine)? pL_PntDrawShapeLine(pPaint, UserDC, nXStart, nYStart, nEndX, nEndY):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTDRAWSHAPERECTANGLE(pPaint, UserDC, prcRect)  \
   ((pL_PntDrawShapeRectangle)? pL_PntDrawShapeRectangle(pPaint, UserDC, prcRect):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTDRAWSHAPEROUNDRECT(pPaint, UserDC, prcRect)  \
   ((pL_PntDrawShapeRoundRect)? pL_PntDrawShapeRoundRect(pPaint, UserDC, prcRect):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTDRAWSHAPEELLIPSE(pPaint, UserDC, prcRect)  \
   ((pL_PntDrawShapeEllipse)? pL_PntDrawShapeEllipse(pPaint, UserDC, prcRect):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTDRAWSHAPEPOLYGON(pPaint, UserDC, pptPoints, nCount)  \
   ((pL_PntDrawShapePolygon)? pL_PntDrawShapePolygon(pPaint, UserDC, pptPoints, nCount):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTDRAWSHAPEPOLYBEZIER(pPaint, UserDC, pptPoints, nCount)  \
   ((pL_PntDrawShapePolyBezier)? pL_PntDrawShapePolyBezier(pPaint, UserDC, pptPoints, nCount):WRPERR_LTPNT_DLL_NOT_LOADED)

// region functions.
#define L_PNTREGIONRECT(pPaint, UserDC, prcRect, phDestRgn)  \
   ((pL_PntRegionRect)? pL_PntRegionRect(pPaint, UserDC, prcRect, phDestRgn):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTREGIONROUNDRECT(pPaint, UserDC, prcRect, phDestRgn)  \
   ((pL_PntRegionRoundRect)? pL_PntRegionRoundRect(pPaint, UserDC, prcRect, phDestRgn):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTREGIONELLIPSE(pPaint, UserDC, prcRect, phDestRgn)  \
   ((pL_PntRegionEllipse)? pL_PntRegionEllipse(pPaint, UserDC, prcRect, phDestRgn):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTREGIONPOLYGON(pPaint, UserDC, pptPoints, nCount, phDestRgn)  \
   ((pL_PntRegionPolygon)? pL_PntRegionPolygon(pPaint, UserDC, pptPoints, nCount, phDestRgn):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTREGIONSURFACE(pPaint, UserDC, pptPoint, phDestRgn)  \
   ((pL_PntRegionSurface)? pL_PntRegionSurface(pPaint, UserDC, pptPoint, phDestRgn):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTREGIONBORDER(pPaint, UserDC, pptPoint, crBorderColor, phDestRgn)  \
   ((pL_PntRegionBorder)? pL_PntRegionBorder(pPaint, UserDC, pptPoint, crBorderColor, phDestRgn):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTREGIONCOLOR(pPaint, UserDC, crColor, phDestRgn)  \
   ((pL_PntRegionColor)? pL_PntRegionColor(pPaint, UserDC, crColor, phDestRgn):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTREGIONTRANSLATE(pPaint, dx, dy, phRgn)  \
   ((pL_PntRegionTranslate)? pL_PntRegionTranslate(pPaint, dx, dy, phRgn):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTREGIONSCALE(pPaint, nHScaleFactor, nVScaleFactor, nAlignment, phDestRgn)  \
   ((pL_PntRegionScale)? pL_PntRegionScale(pPaint, nHScaleFactor, nVScaleFactor, nAlignment, phDestRgn):WRPERR_LTPNT_DLL_NOT_LOADED)

// fill functions.
#define L_PNTFILLSURFACE(pPaint, UserDC, pptPoint)  \
   ((pL_PntFillSurface)? pL_PntFillSurface(pPaint, UserDC, pptPoint):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTFILLBORDER(pPaint, UserDC, pptPoint, crBorderColor)  \
   ((pL_PntFillBorder)? pL_PntFillBorder(pPaint, UserDC, pptPoint, crBorderColor):WRPERR_LTPNT_DLL_NOT_LOADED)

#define L_PNTFILLCOLORREPLACE(pPaint, UserDC, crColor)  \
   ((pL_PntFillColorReplace)? pL_PntFillColorReplace(pPaint, UserDC, crColor):WRPERR_LTPNT_DLL_NOT_LOADED)


// text functions.
#define L_PNTAPPLYTEXT(pPaint, UserDC, prcRect)  \
   ((pL_PntApplyText)? pL_PntApplyText(pPaint, UserDC, prcRect):WRPERR_LTPNT_DLL_NOT_LOADED)


// paint helping functions.
#define L_PNTPICKCOLOR(pPaint, UserDC, nX, nY, pcrDestColor)  \
   ((pL_PntPickColor)? pL_PntPickColor(pPaint, UserDC, nX, nY, pcrDestColor):WRPERR_LTPNT_DLL_NOT_LOADED)

//-----------------------------------------------------------------------------
//--LTTLB.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
//{DOCUMENTED FUNCTIONS

// general toolbar operations funtions.
#define L_TBISVALID(pToolbar)  \
   ((pL_TBIsValid)? pL_TBIsValid(pToolbar):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBINIT(ppToolbar)  \
   ((pL_TBInit)? pL_TBInit(ppToolbar):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBFREE(pToolbar)  \
   ((pL_TBFree)? pL_TBFree(pToolbar):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBCREATE(pToolbar, hwndParent, szTitle, dwFlags)  \
   ((pL_TBCreate)? pL_TBCreate(pToolbar, hwndParent, szTitle, dwFlags):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBFREETOOLBARINFO(pToolbar, pToolbarInfo)  \
   ((pL_TBFreeToolbarInfo)? pL_TBFreeToolbarInfo(pToolbar, pToolbarInfo):WRPERR_LTTLB_DLL_NOT_LOADED)


// status query functions.
#define L_TBISVISIBLE(pToolbar, pfVisible)  \
   ((pL_TBIsVisible)? pL_TBIsVisible(pToolbar, pfVisible):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBISBUTTONENABLED(pToolbar, uButtonID, pfEnable)  \
   ((pL_TBIsButtonEnabled)? pL_TBIsButtonEnabled(pToolbar, uButtonID, pfEnable):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBISBUTTONVISIBLE(pToolbar, uButtonID, pfVisible)  \
   ((pL_TBIsButtonVisible)? pL_TBIsButtonVisible(pToolbar, uButtonID, pfVisible):WRPERR_LTTLB_DLL_NOT_LOADED)


// setting functions.
#define L_TBSETVISIBLE(pToolbar, fVisible)  \
   ((pL_TBSetVisible)? pL_TBSetVisible(pToolbar, fVisible):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBSETPOSITION(pToolbar, lpptPos, dwFlags)  \
   ((pL_TBSetPosition)? pL_TBSetPosition(pToolbar, lpptPos, dwFlags):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBSETROWS(pToolbar, nRows)  \
   ((pL_TBSetRows)? pL_TBSetRows(pToolbar, nRows):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBSETBUTTONCHECKED(pToolbar, uButtonID)  \
   ((pL_TBSetButtonChecked)? pL_TBSetButtonChecked(pToolbar, uButtonID):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBSETBUTTONENABLED(pToolbar, uButtonID, fEnable)  \
   ((pL_TBSetButtonEnabled)? pL_TBSetButtonEnabled(pToolbar, uButtonID, fEnable):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBSETBUTTONVISIBLE(pToolbar, uButtonID, fVisible)  \
   ((pL_TBSetButtonVisible)? pL_TBSetButtonVisible(pToolbar, uButtonID, fVisible):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBSETTOOLBARINFO(pToolbar, pToolbarInfo)  \
   ((pL_TBSetToolbarInfo)? pL_TBSetToolbarInfo(pToolbar, pToolbarInfo):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBSETCALLBACK(pToolbar, pCallback, pUserData)  \
   ((pL_TBSetCallback)? pL_TBSetCallback(pToolbar, pCallback, pUserData):WRPERR_LTTLB_DLL_NOT_LOADED)


// getting functions.
#define L_TBGETPOSITION(pToolbar, lpptPos, dwFlags)  \
   ((pL_TBGetPosition)? pL_TBGetPosition(pToolbar, lpptPos, dwFlags):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBGETROWS(pToolbar, pnRows)  \
   ((pL_TBGetRows)? pL_TBGetRows(pToolbar, pnRows):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBGETBUTTONCHECKED(pToolbar, pnChecked)  \
   ((pL_TBGetButtonChecked)? pL_TBGetButtonChecked(pToolbar, pnChecked):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBGETTOOLBARINFO(pToolbar, pToolbarInfo)  \
   ((pL_TBGetToolbarInfo)? pL_TBGetToolbarInfo(pToolbar, pToolbarInfo):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBGETCALLBACK(pToolbar, ppCallback, ppUserData)  \
   ((pL_TBGetCallback)? pL_TBGetCallback(pToolbar, ppCallback, ppUserData):WRPERR_LTTLB_DLL_NOT_LOADED)


// new functions
#define L_TBADDBUTTON(pToolbar, uButtonRefId, pButtonInfo, dwFlags) \
   ((pL_TBAddButton)? pL_TBAddButton(pToolbar, uButtonRefId, pButtonInfo, dwFlags):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBREMOVEBUTTON(pToolbar, uButtonId) \
   ((pL_TBRemoveButton)? pL_TBRemoveButton(pToolbar, uButtonId):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBGETBUTTONINFO(pToolbar, uButtonId, pButtonInfo) \
   ((pL_TBGetButtonInfo)? pL_TBGetButtonInfo(pToolbar, uButtonId, pButtonInfo):WRPERR_LTTLB_DLL_NOT_LOADED)

#define L_TBSETBUTTONINFO(pToolbar, uButtonId, pButtonInfo) \
   ((pL_TBSetButtonInfo)? pL_TBSetButtonInfo(pToolbar, uButtonId, pButtonInfo):WRPERR_LTTLB_DLL_NOT_LOADED)


#define L_TBSETAUTOMATIONCALLBACK(pToolbar, pAutomationCallback, pAutomationData)  \
   ((pL_TBSetAutomationCallback)? pL_TBSetAutomationCallback(pToolbar, pAutomationCallback, pAutomationData):WRPERR_LTTLB_DLL_NOT_LOADED)

     
//-----------------------------------------------------------------------------
//--LTPDG.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
#define L_PNTDLGBRUSH( hWnd, pBrushDlgInfo )  \
   ((pL_PntDlgBrush )? pL_PntDlgBrush ( hWnd, pBrushDlgInfo ):WRPERR_LTPDG_DLL_NOT_LOADED)

#define L_PNTDLGSHAPE( hWnd, pShapeDlgInfo )  \
   ((pL_PntDlgShape )? pL_PntDlgShape ( hWnd, pShapeDlgInfo ):WRPERR_LTPDG_DLL_NOT_LOADED)

#define L_PNTDLGREGION( hWnd, pRegionDlgInfo)  \
   ((pL_PntDlgRegion)? pL_PntDlgRegion( hWnd, pRegionDlgInfo):WRPERR_LTPDG_DLL_NOT_LOADED)

#define L_PNTDLGFILL( hWnd, pFillDlgInfo  )  \
   ((pL_PntDlgFill  )? pL_PntDlgFill  ( hWnd, pFillDlgInfo  ):WRPERR_LTPDG_DLL_NOT_LOADED)

#define L_PNTDLGTEXT( hWnd, pTextDlgInfo  )  \
   ((pL_PntDlgText  )? pL_PntDlgText  ( hWnd, pTextDlgInfo  ):WRPERR_LTPDG_DLL_NOT_LOADED)

//-----------------------------------------------------------------------------
//--LTSGM.H FUNCTIONS MACROS---------------------------------------------------
//-----------------------------------------------------------------------------
#define L_MRCSTARTBITMAPSEGMENTATION(phSegment, nWidth, nHeight, clrBackground, clrForeground) \
   ((pL_MrcStartBitmapSegmentation) ? pL_MrcStartBitmapSegmentation(phSegment, nWidth, nHeight, clrBackground, clrForeground) : WRPERR_LTSGM_DLL_NOT_LOADED)

#define L_MRCENDBITMAPSEGMENTATION(hSegment) \
   ((pL_MrcEndBitmapSegmentation) ? pL_MrcEndBitmapSegmentation(hSegment) : WRPERR_LTSGM_DLL_NOT_LOADED)

#define L_MRCSEGMENTBITMAP(hSegment, pBitmap, pMinSeg, uSegFactor, pfnCallback, pUserData) \
   ((pL_MrcSegmentBitmap) ? pL_MrcSegmentBitmap(hSegment, pBitmap, pMinSeg, uSegFactor, pfnCallback, pUserData) : WRPERR_LTSGM_DLL_NOT_LOADED)

#define L_MRCSETNEWSTRIPE(hSegment, nStripeStartRow, nStripeEndRow) \
   ((pL_MrcSetNewStripe) ? pL_MrcSetNewStripe(hSegment, nStripeStartRow, nStripeEndRow) : WRPERR_LTSGM_DLL_NOT_LOADED)

#define L_MRCSETSTRIPESEGMENT(hSegment, nStripeIndex, pSegment) \
   ((pL_MrcSetStripeSegment) ? pL_MrcSetStripeSegment(hSegment, nStripeIndex, pSegment) : WRPERR_LTSGM_DLL_NOT_LOADED)

#define L_MRCSETSTRIPEMAXHEIGHT(hSegment, nStripeMaxHeight) \
   ((pL_MrcSetStripeMaxHeight) ? pL_MrcSetStripeMaxHeight(hSegment, nStripeMaxHeight) : WRPERR_LTSGM_DLL_NOT_LOADED)

#define L_MRCENUMSEGMENTS(hSegment, pEnumProc, pUserData, dwFlags) \
   ((pL_MrcEnumSegments) ? pL_MrcEnumSegments(hSegment, pEnumProc, pUserData, dwFlags) : WRPERR_LTSGM_DLL_NOT_LOADED)

#define L_MRCUPDATESEGMENTDATA(hSegment, nSegId, pSegmentData, bVerifyUpdate) \
   ((pL_MrcUpdateSegmentData) ? pL_MrcUpdateSegmentData(hSegment, nSegId, pSegmentData, bVerifyUpdate) : WRPERR_LTSGM_DLL_NOT_LOADED)

#define L_MRCDELETESEGMENT(hSegment, nSegId) \
   ((pL_MrcDeleteSegment) ? pL_MrcDeleteSegment(hSegment, nSegId) : WRPERR_LTSGM_DLL_NOT_LOADED)

#define L_MRCSAVEBITMAP(hSegment, pBitmap, pCmpOption, pszFileName, pfnCallback, pUserData) \
   ((pL_MrcSaveBitmap) ? pL_MrcSaveBitmap(hSegment, pBitmap, pCmpOption, pszFileName, pfnCallback, pUserData) : WRPERR_LTSGM_DLL_NOT_LOADED)

#define L_MRCSAVEBITMAPT44(hSegment, pBitmap, pCmpOption, pszFileName, pfnCallback, pUserData) \
   ((pL_MrcSaveBitmapT44) ? pL_MrcSaveBitmapT44(hSegment, pBitmap, pCmpOption, pszFileName, pfnCallback, pUserData) : WRPERR_LTSGM_DLL_NOT_LOADED)

#define L_MRCLOADBITMAP(pszFileName, pBitmap, nPageNo, pfnCallback, pUserData) \
   ((pL_MrcLoadBitmap) ? pL_MrcLoadBitmap(pszFileName, pBitmap, nPageNo, pfnCallback, pUserData) : WRPERR_LTSGM_DLL_NOT_LOADED)

#define L_MRCGETPAGESCOUNT(pszFileName, pnPages) \
   ((pL_MrcGetPagesCount) ? pL_MrcGetPagesCount(pszFileName, pnPages) : WRPERR_LTSGM_DLL_NOT_LOADED)


#endif //USE_POINTERS_TO_LEAD_FUNCTIONS

#endif //_LEAD_FUNCTIONS_MACROS_H_
/*================================================================= EOF =====*/
