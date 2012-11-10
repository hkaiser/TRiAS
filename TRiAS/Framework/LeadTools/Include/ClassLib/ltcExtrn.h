/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcExtrn.h                                                      |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_EXTERN_H_
#define  _LEAD_EXTERN_H_

/*----------------------------------------------------------------------------+
| extern LWRP_EXPORT LWRP_EXPORTAL VARIABLES                                                          |   
+----------------------------------------------------------------------------*/
extern HINSTANCE     hWrpDLLInst;
extern LWRP_EXPORT   LBitmapDictionary    BitmapDictionary;
extern               LDictionary          LStatusDictionary;

//--LEAD FUNCTIONS POINTERS----------------------------------------------------
#ifdef USE_POINTERS_TO_LEAD_FUNCTIONS

//-----------------------------------------------------------------------------
//--LTKRN.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------
extern LWRP_EXPORT pL_ACCESSBITMAP  pL_AccessBitmap ;
extern LWRP_EXPORT pL_ALLOCATEBITMAP  pL_AllocateBitmap ;
extern LWRP_EXPORT pL_CHANGEBITMAPHEIGHT  pL_ChangeBitmapHeight ;
extern LWRP_EXPORT pL_CHANGEBITMAPVIEWPERSPECTIVE pL_ChangeBitmapViewPerspective;
extern LWRP_EXPORT pL_CHANGEFROMDIB  pL_ChangeFromDIB ;
extern LWRP_EXPORT pL_CHANGETODIB  pL_ChangeToDIB ;
extern LWRP_EXPORT pL_CLEARBITMAP  pL_ClearBitmap ;
extern LWRP_EXPORT pL_CLEARNEGATIVEPIXELS pL_ClearNegativePixels;
extern LWRP_EXPORT pL_COLORRESBITMAP  pL_ColorResBitmap ;
extern LWRP_EXPORT pL_COLORRESBITMAPLIST  pL_ColorResBitmapList ;
extern LWRP_EXPORT pL_COMBINEBITMAP  pL_CombineBitmap ;
extern LWRP_EXPORT pL_COMBINEBITMAPWARP  pL_CombineBitmapWarp ;
extern LWRP_EXPORT pL_COMPRESSROW pL_CompressRow;
extern LWRP_EXPORT pL_COMPRESSROWS pL_CompressRows;
extern LWRP_EXPORT pL_CONVERTBUFFER  pL_ConvertBuffer ;
extern LWRP_EXPORT pL_CONVERTBUFFEREXT  pL_ConvertBufferExt ;
extern LWRP_EXPORT pL_CONVERTFROMDIB  pL_ConvertFromDIB ;
extern LWRP_EXPORT pL_CONVERTTODIB  pL_ConvertToDIB ;
extern LWRP_EXPORT pL_COPYBITMAP  pL_CopyBitmap ;
extern LWRP_EXPORT pL_COPYBITMAPDATA  pL_CopyBitmapData ;
extern LWRP_EXPORT pL_COPYBITMAPHANDLE  pL_CopyBitmapHandle ;
extern LWRP_EXPORT pL_COPYBITMAPLISTITEMS pL_CopyBitmapListItems;
extern LWRP_EXPORT pL_COPYBITMAPRECT  pL_CopyBitmapRect ;
extern LWRP_EXPORT pL_CREATEBITMAP  pL_CreateBitmap ;
extern LWRP_EXPORT pL_CREATEBITMAPLIST pL_CreateBitmapList;
extern LWRP_EXPORT pL_CREATELEADDC  pL_CreateLeadDC ;
extern LWRP_EXPORT pL_CREATEUSERMATCHTABLE  pL_CreateUserMatchTable ;
extern LWRP_EXPORT pL_DEFAULTDITHERING  pL_DefaultDithering ;
extern LWRP_EXPORT pL_DELETEBITMAPLISTITEMS pL_DeleteBitmapListItems;
extern LWRP_EXPORT pL_DESTROYBITMAPLIST pL_DestroyBitmapList;
extern LWRP_EXPORT pL_DELETELEADDC  pL_DeleteLeadDC ;
extern LWRP_EXPORT pL_DITHERLINE  pL_DitherLine ;
extern LWRP_EXPORT pL_DUPPALETTE  pL_DupPalette ;
extern LWRP_EXPORT pL_DUPBITMAPPALETTE  pL_DupBitmapPalette ;
extern LWRP_EXPORT pL_EXPANDROW pL_ExpandRow;
extern LWRP_EXPORT pL_EXPANDROWS pL_ExpandRows;
extern LWRP_EXPORT pL_FILLBITMAP  pL_FillBitmap ;
extern LWRP_EXPORT pL_FLIPBITMAP  pL_FlipBitmap ;
extern LWRP_EXPORT pL_FREEBITMAP  pL_FreeBitmap ;
extern LWRP_EXPORT pL_FREEUSERMATCHTABLE  pL_FreeUserMatchTable ;
extern LWRP_EXPORT pL_GETBITMAPALPHA  pL_GetBitmapAlpha ;
extern LWRP_EXPORT pL_GETBITMAPCOLORS  pL_GetBitmapColors ;
extern LWRP_EXPORT pL_GETBITMAPLISTCOUNT pL_GetBitmapListCount;
extern LWRP_EXPORT pL_GETBITMAPLISTITEM pL_GetBitmapListItem;
extern LWRP_EXPORT pL_GETBITMAPROW  pL_GetBitmapRow ;
extern LWRP_EXPORT pL_GETBITMAPROWCOL  pL_GetBitmapRowCol ;
extern LWRP_EXPORT pL_GETBITMAPROWCOLCOMPRESSED  pL_GetBitmapRowColCompressed ;
extern LWRP_EXPORT pL_GETBITMAPROWCOMPRESSED  pL_GetBitmapRowCompressed ;
extern LWRP_EXPORT pL_GETFIXEDPALETTE  pL_GetFixedPalette ;
extern LWRP_EXPORT pL_GETPIXELCOLOR  pL_GetPixelColor ;
extern LWRP_EXPORT pL_GETSTATUSCALLBACK  pL_GetStatusCallBack ;
extern LWRP_EXPORT pL_GRAYSCALEBITMAP  pL_GrayScaleBitmap ;
extern LWRP_EXPORT pL_INITBITMAP  pL_InitBitmap ;
extern LWRP_EXPORT pL_INSERTBITMAPLISTITEM pL_InsertBitmapListItem;
extern LWRP_EXPORT pL_ISGRAYSCALEBITMAP  pL_IsGrayScaleBitmap ;
extern LWRP_EXPORT pL_ISSUPPORTLOCKED  pL_IsSupportLocked ;
extern LWRP_EXPORT pL_POINTFROMBITMAP pL_PointFromBitmap;
extern LWRP_EXPORT pL_POINTTOBITMAP pL_PointToBitmap;
extern LWRP_EXPORT pL_PUTBITMAPCOLORS  pL_PutBitmapColors ;
extern LWRP_EXPORT pL_PUTBITMAPROW  pL_PutBitmapRow ;
extern LWRP_EXPORT pL_PUTBITMAPROWCOL  pL_PutBitmapRowCol ;
extern LWRP_EXPORT pL_PUTBITMAPROWCOLCOMPRESSED  pL_PutBitmapRowColCompressed ;
extern LWRP_EXPORT pL_PUTBITMAPROWCOMPRESSED  pL_PutBitmapRowCompressed ;
extern LWRP_EXPORT pL_PUTPIXELCOLOR  pL_PutPixelColor ;
extern LWRP_EXPORT pL_RECTFROMBITMAP pL_RectFromBitmap;
extern LWRP_EXPORT pL_RECTTOBITMAP pL_RectToBitmap;
extern LWRP_EXPORT pL_REDIRECTIO  pL_RedirectIO ;
extern LWRP_EXPORT pL_RELEASEBITMAP  pL_ReleaseBitmap ;
extern LWRP_EXPORT pL_REMOVEBITMAPLISTITEM pL_RemoveBitmapListItem;
extern LWRP_EXPORT pL_RESIZE  pL_Resize ;
extern LWRP_EXPORT pL_RESIZEBITMAP  pL_ResizeBitmap ;
extern LWRP_EXPORT pL_REVERSEBITMAP  pL_ReverseBitmap ;
extern LWRP_EXPORT pL_ROTATEBITMAP  pL_RotateBitmap ;
extern LWRP_EXPORT pL_ROTATEBITMAPVIEWPERSPECTIVE  pL_RotateBitmapViewPerspective ;
extern LWRP_EXPORT pL_SETBITMAPALPHA  pL_SetBitmapAlpha ;
extern LWRP_EXPORT pL_SETBITMAPDATAPOINTER  pL_SetBitmapDataPointer ;
extern LWRP_EXPORT pL_SETBITMAPLISTITEM pL_SetBitmapListItem;
extern LWRP_EXPORT pL_SETHOTKEYCALLBACK pL_SetHotKeyCallback;
extern LWRP_EXPORT pL_SETSTATUSCALLBACK  pL_SetStatusCallBack ;
extern LWRP_EXPORT pL_SETUSERMATCHTABLE  pL_SetUserMatchTable ;
extern LWRP_EXPORT pL_SHEARBITMAP  pL_ShearBitmap ;
extern LWRP_EXPORT pL_SIZEBITMAP pL_SizeBitmap;
extern LWRP_EXPORT pL_STARTDITHERING  pL_StartDithering ;
extern LWRP_EXPORT pL_STARTRESIZE  pL_StartResize ;
extern LWRP_EXPORT pL_STOPDITHERING  pL_StopDithering ;
extern LWRP_EXPORT pL_STOPRESIZE  pL_StopResize ;
extern LWRP_EXPORT pL_TRANSLATEBITMAPCOLOR pL_TranslateBitmapColor;
extern LWRP_EXPORT pL_TOGGLEBITMAPCOMPRESSION pL_ToggleBitmapCompression;
extern LWRP_EXPORT pL_TRIMBITMAP  pL_TrimBitmap ;
extern LWRP_EXPORT pL_UNLOCKSUPPORT  pL_UnlockSupport ;
extern LWRP_EXPORT pL_VERSIONINFO  pL_VersionInfo ;
extern LWRP_EXPORT pL_FLIPBITMAPVIEWPERSPECTIVE pL_FlipBitmapViewPerspective;
extern LWRP_EXPORT pL_REVERSEBITMAPVIEWPERSPECTIVE pL_ReverseBitmapViewPerspective;
extern LWRP_EXPORT pL_STARTRESIZEBITMAP pL_StartResizeBitmap;
extern LWRP_EXPORT pL_GETRESIZEDROWCOL pL_GetResizedRowCol;
extern LWRP_EXPORT pL_STOPRESIZEBITMAP pL_StopResizeBitmap;
extern LWRP_EXPORT pL_MOVEBITMAPLISTITEMS pL_MoveBitmapListItems;
extern LWRP_EXPORT pL_GETPIXELDATA pL_GetPixelData;
extern LWRP_EXPORT pL_PUTPIXELDATA pL_PutPixelData;
extern LWRP_EXPORT pL_CHANGEBITMAPCOMPRESSION pL_ChangeBitmapCompression;
extern LWRP_EXPORT pL_SETBITMAPPALETTE  pL_SetBitmapPalette;

extern LWRP_EXPORT pL_CREATEBITMAPLISTOPTPAL  pL_CreateBitmapListOptPal ;

//-----------------------------------------------------------------------------
//--LTIMG.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------

extern LWRP_EXPORT pL_ADDBITMAPNOISE  pL_AddBitmapNoise ;
extern LWRP_EXPORT pL_AUTOTRIMBITMAP pL_AutoTrimBitmap;
extern LWRP_EXPORT pL_AVERAGEFILTERBITMAP  pL_AverageFilterBitmap ;
extern LWRP_EXPORT pL_BINARYFILTERBITMAP  pL_BinaryFilterBitmap ;
extern LWRP_EXPORT pL_CHANGEBITMAPCONTRAST  pL_ChangeBitmapContrast ;
extern LWRP_EXPORT pL_CHANGEBITMAPHUE  pL_ChangeBitmapHue ;
extern LWRP_EXPORT pL_CHANGEBITMAPINTENSITY  pL_ChangeBitmapIntensity ;
extern LWRP_EXPORT pL_CHANGEBITMAPSATURATION  pL_ChangeBitmapSaturation ;
extern LWRP_EXPORT pL_COLORMERGEBITMAP  pL_ColorMergeBitmap ;
extern LWRP_EXPORT pL_COLORSEPARATEBITMAP  pL_ColorSeparateBitmap ;
extern LWRP_EXPORT pL_DESKEWBITMAP  pL_DeskewBitmap ;
extern LWRP_EXPORT pL_DESPECKLEBITMAP  pL_DespeckleBitmap ;
extern LWRP_EXPORT pL_SMOOTHBITMAP  pL_SmoothBitmap ;
extern LWRP_EXPORT pL_LINEREMOVEBITMAP pL_LineRemoveBitmap;
extern LWRP_EXPORT pL_BORDERREMOVEBITMAP pL_BorderRemoveBitmap;
extern LWRP_EXPORT pL_INVERTEDTEXTBITMAP pL_InvertedTextBitmap;
extern LWRP_EXPORT pL_DOTREMOVEBITMAP pL_DotRemoveBitmap;
extern LWRP_EXPORT pL_HOLEPUNCHREMOVEBITMAP pL_HolePunchRemoveBitmap;
extern LWRP_EXPORT pL_STAPLEREMOVEBITMAP pL_StapleRemoveBitmap;
extern LWRP_EXPORT pL_EMBOSSBITMAP  pL_EmbossBitmap ;
extern LWRP_EXPORT pL_GAMMACORRECTBITMAP  pL_GammaCorrectBitmap ;
extern LWRP_EXPORT pL_GETAUTOTRIMRECT pL_GetAutoTrimRect;
extern LWRP_EXPORT pL_GETBITMAPCOLORCOUNT pL_GetBitmapColorCount;
extern LWRP_EXPORT pL_GETBITMAPHISTOGRAM  pL_GetBitmapHistogram ;
extern LWRP_EXPORT pL_GETMINMAXBITS pL_GetMinMaxBits;
extern LWRP_EXPORT pL_GETMINMAXVAL pL_GetMinMaxVal;
extern LWRP_EXPORT pL_HISTOCONTRASTBITMAP  pL_HistoContrastBitmap ;
extern LWRP_EXPORT pL_INTENSITYDETECTBITMAP  pL_IntensityDetectBitmap ;
extern LWRP_EXPORT pL_INVERTBITMAP  pL_InvertBitmap ;
extern LWRP_EXPORT pL_MAXFILTERBITMAP pL_MaxFilterBitmap;
extern LWRP_EXPORT pL_MEDIANFILTERBITMAP  pL_MedianFilterBitmap ;
extern LWRP_EXPORT pL_MINFILTERBITMAP pL_MinFilterBitmap;
extern LWRP_EXPORT pL_MOSAICBITMAP  pL_MosaicBitmap ;
extern LWRP_EXPORT pL_OILIFYBITMAP  pL_OilifyBitmap ;
extern LWRP_EXPORT pL_POSTERIZEBITMAP  pL_PosterizeBitmap ;
extern LWRP_EXPORT pL_PICTURIZEBITMAP pL_PicturizeBitmap;
extern LWRP_EXPORT pL_REMAPBITMAPINTENSITY  pL_RemapBitmapIntensity ;
extern LWRP_EXPORT pL_SHARPENBITMAP  pL_SharpenBitmap ;
extern LWRP_EXPORT pL_SOLARIZEBITMAP  pL_SolarizeBitmap ;
extern LWRP_EXPORT pL_SPATIALFILTERBITMAP  pL_SpatialFilterBitmap ;
extern LWRP_EXPORT pL_STRETCHBITMAPINTENSITY  pL_StretchBitmapIntensity ;
extern LWRP_EXPORT pL_WINDOWLEVELBITMAP pL_WindowLevelBitmap;
extern LWRP_EXPORT pL_CONTOURFILTERBITMAP pL_ContourFilterBitmap;
extern LWRP_EXPORT pL_GAUSSIANFILTERBITMAP pL_GaussianFilterBitmap;
extern LWRP_EXPORT pL_UNSHARPMASKBITMAP pL_UnsharpMaskBitmap;
extern LWRP_EXPORT pL_GRAYSCALEBITMAPEXT pL_GrayScaleBitmapExt;
extern LWRP_EXPORT pL_CONVERTTOCOLOREDGRAY pL_ConvertToColoredGray;
extern LWRP_EXPORT pL_BALANCECOLORS pL_BalanceColors;
extern LWRP_EXPORT pL_SWAPCOLORS pL_SwapColors;
extern LWRP_EXPORT pL_LINEPROFILE pL_LineProfile;
extern LWRP_EXPORT pL_HISTOEQUALIZEBITMAP pL_HistoEqualizeBitmap;
extern LWRP_EXPORT pL_ADDBITMAPS pL_AddBitmaps;
extern LWRP_EXPORT pL_ANTIALIASBITMAP pL_AntiAliasBitmap;
extern LWRP_EXPORT pL_EDGEDETECTORBITMAP pL_EdgeDetectorBitmap;
extern LWRP_EXPORT pL_REMOVEREDEYEBITMAP pL_RemoveRedeyeBitmap;
extern LWRP_EXPORT pL_RESIZEBITMAPRGN pL_ResizeBitmapRgn;
extern LWRP_EXPORT pL_ALPHABLENDBITMAP pL_AlphaBlendBitmap;
extern LWRP_EXPORT pL_FEATHERALPHABLENDBITMAP pL_FeatherAlphaBlendBitmap;
extern LWRP_EXPORT pL_CREATEFADEDMASK pL_CreateFadedMask;
extern LWRP_EXPORT pL_MOTIONBLURBITMAP pL_MotionBlurBitmap;
extern LWRP_EXPORT pL_PICTURIZEBITMAPLIST pL_PicturizeBitmapList;
extern LWRP_EXPORT pL_PICTURIZEBITMAPSINGLE pL_PicturizeBitmapSingle;
extern LWRP_EXPORT pL_HALFTONEBITMAP pL_HalfToneBitmap;
extern LWRP_EXPORT pL_GETFUNCTIONALLOOKUPTABLE pL_GetFunctionalLookupTable;
extern LWRP_EXPORT pL_GETUSERLOOKUPTABLE pL_GetUserLookUpTable;
extern LWRP_EXPORT pL_COMBINEBITMAPEXT pL_CombineBitmapExt;
extern LWRP_EXPORT pL_ADDBORDER pL_AddBorder;
extern LWRP_EXPORT pL_ADDFRAME pL_AddFrame;
extern LWRP_EXPORT pL_CONVERTBITMAPSIGNEDTOUNSIGNED pL_ConvertBitmapSignedToUnsigned;

//-----------------------------------------------------------------------------
//--LTDIS.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------

extern LWRP_EXPORT pL_APPENDPLAYBACK pL_AppendPlayback;
extern LWRP_EXPORT pL_BITMAPHASRGN pL_BitmapHasRgn;
extern LWRP_EXPORT pL_CANCELPLAYBACKWAIT pL_CancelPlaybackWait;
extern LWRP_EXPORT pL_CHANGEFROMDDB  pL_ChangeFromDDB ;
extern LWRP_EXPORT pL_CHANGETODDB  pL_ChangeToDDB ;
extern LWRP_EXPORT pL_CLEARPLAYBACKUPDATERECT pL_ClearPlaybackUpdateRect;
extern LWRP_EXPORT pL_CLIPBOARDREADY  pL_ClipboardReady ;
extern LWRP_EXPORT pL_CONVERTCOLORSPACE  pL_ConvertColorSpace ;
extern LWRP_EXPORT pL_CONVERTFROMDDB  pL_ConvertFromDDB ;
extern LWRP_EXPORT pL_CONVERTTODDB  pL_ConvertToDDB ;
extern LWRP_EXPORT pL_COPYFROMCLIPBOARD  pL_CopyFromClipboard ;
extern LWRP_EXPORT pL_COPYTOCLIPBOARD  pL_CopyToClipboard ;
extern LWRP_EXPORT pL_COPYTOCLIPBOARDEXT  pL_CopyToClipboardExt ;
extern LWRP_EXPORT pL_CREATEPAINTPALETTE  pL_CreatePaintPalette ;
extern LWRP_EXPORT pL_CREATEMASKFROMBITMAPRGN pL_CreateMaskFromBitmapRgn;
extern LWRP_EXPORT pL_CREATEPLAYBACK pL_CreatePlayback;
extern LWRP_EXPORT pL_DESTROYPLAYBACK pL_DestroyPlayback;
extern LWRP_EXPORT pL_FRAMEBITMAPRGN pL_FrameBitmapRgn;
extern LWRP_EXPORT pL_COLORBITMAPRGN pL_ColorBitmapRgn;
extern LWRP_EXPORT pL_FREEBITMAPRGN pL_FreeBitmapRgn;
extern LWRP_EXPORT pL_GETBITMAPRGNAREA pL_GetBitmapRgnArea;
extern LWRP_EXPORT pL_GETBITMAPRGNBOUNDS pL_GetBitmapRgnBounds;
extern LWRP_EXPORT pL_GETBITMAPRGNHANDLE pL_GetBitmapRgnHandle;
extern LWRP_EXPORT pL_GETDISPLAYMODE  pL_GetDisplayMode ;
extern LWRP_EXPORT pL_GETPAINTCONTRAST pL_GetPaintContrast;
extern LWRP_EXPORT pL_GETPAINTGAMMA pL_GetPaintGamma;
extern LWRP_EXPORT pL_GETPAINTINTENSITY pL_GetPaintIntensity;
extern LWRP_EXPORT pL_GETPLAYBACKDELAY pL_GetPlaybackDelay;
extern LWRP_EXPORT pL_GETPLAYBACKINDEX pL_GetPlaybackIndex;
extern LWRP_EXPORT pL_GETPLAYBACKSTATE pL_GetPlaybackState;
extern LWRP_EXPORT pL_GETPLAYBACKUPDATERECT pL_GetPlaybackUpdateRect;
extern LWRP_EXPORT pL_ISPTINBITMAPRGN pL_IsPtInBitmapRgn;
extern LWRP_EXPORT pL_OFFSETBITMAPRGN pL_OffsetBitmapRgn;
extern LWRP_EXPORT pL_PAINTDC  pL_PaintDC ;
extern LWRP_EXPORT pL_PAINTDCBUFFER  pL_PaintDCBuffer ;
extern LWRP_EXPORT pL_PAINTRGNDC  pL_PaintRgnDC ;
extern LWRP_EXPORT pL_PAINTRGNDCBUFFER  pL_PaintRgnDCBuffer ;
extern LWRP_EXPORT pL_PRINTBITMAP  pL_PrintBitmap ;
extern LWRP_EXPORT pL_PRINTBITMAPEXT  pL_PrintBitmapExt ;
extern LWRP_EXPORT pL_PRINTBITMAPFAST  pL_PrintBitmapFast ;
extern LWRP_EXPORT pL_PROCESSPLAYBACK pL_ProcessPlayback;
extern LWRP_EXPORT pL_SCREENCAPTUREBITMAP  pL_ScreenCaptureBitmap ;
extern LWRP_EXPORT pL_SETBITMAPRGNCOLOR pL_SetBitmapRgnColor;
extern LWRP_EXPORT pL_SETBITMAPRGNMAGICWAND pL_SetBitmapRgnMagicWand;
extern LWRP_EXPORT pL_SETBITMAPRGNELLIPSE pL_SetBitmapRgnEllipse;
extern LWRP_EXPORT pL_SETBITMAPRGNFROMMASK pL_SetBitmapRgnFromMask;
extern LWRP_EXPORT pL_SETBITMAPRGNHANDLE pL_SetBitmapRgnHandle;
extern LWRP_EXPORT pL_SETBITMAPRGNPOLYGON pL_SetBitmapRgnPolygon;
extern LWRP_EXPORT pL_SETBITMAPRGNRECT pL_SetBitmapRgnRect;
extern LWRP_EXPORT pL_SETBITMAPRGNROUNDRECT pL_SetBitmapRgnRoundRect;
extern LWRP_EXPORT pL_SETDISPLAYMODE  pL_SetDisplayMode ;
extern LWRP_EXPORT pL_SETPAINTCONTRAST pL_SetPaintContrast;
extern LWRP_EXPORT pL_SETPAINTGAMMA pL_SetPaintGamma;
extern LWRP_EXPORT pL_SETPAINTINTENSITY pL_SetPaintIntensity;
extern LWRP_EXPORT pL_SETPLAYBACKINDEX pL_SetPlaybackIndex;
extern LWRP_EXPORT pL_UNDERLAYBITMAP  pL_UnderlayBitmap ;
extern LWRP_EXPORT pL_VALIDATEPLAYBACKLINES pL_ValidatePlaybackLines;
extern LWRP_EXPORT pL_WINDOWLEVEL pL_WindowLevel;
extern LWRP_EXPORT pL_CREATEPANWINDOW pL_CreatePanWindow;
extern LWRP_EXPORT pL_UPDATEPANWINDOW pL_UpdatePanWindow;
extern LWRP_EXPORT pL_DESTROYPANWINDOW pL_DestroyPanWindow;
extern LWRP_EXPORT pL_WINDOWLEVELFILLLUT pL_WindowLevelFillLUT;
extern LWRP_EXPORT pL_CONVERTFROMWMF pL_ConvertFromWMF;
extern LWRP_EXPORT pL_CHANGEFROMWMF pL_ChangeFromWMF;
extern LWRP_EXPORT pL_CONVERTTOWMF pL_ConvertToWMF;
extern LWRP_EXPORT pL_CHANGETOWMF pL_ChangeToWMF;
extern LWRP_EXPORT pL_CONVERTFROMEMF pL_ConvertFromEMF;
extern LWRP_EXPORT pL_CHANGEFROMEMF pL_ChangeFromEMF;
extern LWRP_EXPORT pL_CONVERTTOEMF pL_ConvertToEMF;
extern LWRP_EXPORT pL_CHANGETOEMF pL_ChangeToEMF;
extern LWRP_EXPORT pL_STARTMAGGLASS pL_StartMagGlass;
extern LWRP_EXPORT pL_STOPMAGGLASS pL_StopMagGlass;
extern LWRP_EXPORT pL_UPDATEMAGGLASSRECT pL_UpdateMagGlassRect;
extern LWRP_EXPORT pL_WINDOWHASMAGGLASS pL_WindowHasMagGlass;
extern LWRP_EXPORT pL_SETBITMAPRGNCURVE pL_SetBitmapRgnCurve;
extern LWRP_EXPORT pL_CURVETOBEZIER pL_CurveToBezier;
extern LWRP_EXPORT pL_GETBITMAPCLIPSEGMENTS pL_GetBitmapClipSegments;
extern LWRP_EXPORT pL_GETBITMAPCLIPSEGMENTSMAX pL_GetBitmapClipSegmentsMax;


//-----------------------------------------------------------------------------
//--LTFIL.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------
extern LWRP_EXPORT pL_COMPRESSBUFFER  pL_CompressBuffer ;
extern LWRP_EXPORT pL_DELETEPAGE pL_DeletePage;
extern LWRP_EXPORT pL_ENDCOMPRESSBUFFER  pL_EndCompressBuffer ;
extern LWRP_EXPORT pL_READLOADRESOLUTIONS  pL_ReadLoadResolutions ;
extern LWRP_EXPORT pL_READFILETRANSFORMS  pL_ReadFileTransforms ;
extern LWRP_EXPORT pL_WRITEFILETRANSFORMS  pL_WriteFileTransforms ;
extern LWRP_EXPORT pL_FEEDLOAD  pL_FeedLoad ;
extern LWRP_EXPORT pL_FILECONVERT  pL_FileConvert ;
extern LWRP_EXPORT pL_FILEINFO  pL_FileInfo ;
extern LWRP_EXPORT pL_FILEINFOMEMORY  pL_FileInfoMemory ;
extern LWRP_EXPORT pL_GETCOMMENT  pL_GetComment ;
extern LWRP_EXPORT pL_GETLOADRESOLUTION  pL_GetLoadResolution ;
extern LWRP_EXPORT pL_GETFILECOMMENTSIZE  pL_GetFileCommentSize ;
extern LWRP_EXPORT pL_GETPCDRESOLUTION  pL_GetPCDResolution ;
extern LWRP_EXPORT pL_GETWMFRESOLUTION  pL_GetWMFResolution ;
extern LWRP_EXPORT pL_GETTAG  pL_GetTag ;
extern LWRP_EXPORT pL_IGNOREFILTERS  pL_IgnoreFilters ;
extern LWRP_EXPORT pL_LOADBITMAP  pL_LoadBitmap ;
extern LWRP_EXPORT pL_LOADBITMAPLIST  pL_LoadBitmapList ;
extern LWRP_EXPORT pL_LOADBITMAPMEMORY  pL_LoadBitmapMemory ;
extern LWRP_EXPORT pL_LOADFILE  pL_LoadFile ;
extern LWRP_EXPORT pL_LOADFILETILE  pL_LoadFileTile ;
extern LWRP_EXPORT pL_LOADFILEOFFSET  pL_LoadFileOffset ;
extern LWRP_EXPORT pL_LOADMEMORY  pL_LoadMemory ;
extern LWRP_EXPORT pL_PRELOADFILTERS  pL_PreLoadFilters ;
extern LWRP_EXPORT pL_READFILECOMMENT  pL_ReadFileComment ;
extern LWRP_EXPORT pL_READFILECOMMENTEXT  pL_ReadFileCommentExt ;
extern LWRP_EXPORT pL_READFILECOMMENTMEMORY  pL_ReadFileCommentMemory ;
extern LWRP_EXPORT pL_READFILETAG  pL_ReadFileTag ;
extern LWRP_EXPORT pL_READFILETAGMEMORY  pL_ReadFileTagMemory ;
extern LWRP_EXPORT pL_READFILESTAMP  pL_ReadFileStamp ;
extern LWRP_EXPORT pL_SAVEBITMAP  pL_SaveBitmap ;
extern LWRP_EXPORT pL_SAVEBITMAPLIST  pL_SaveBitmapList ;
extern LWRP_EXPORT pL_SAVEBITMAPMEMORY  pL_SaveBitmapMemory ;
extern LWRP_EXPORT pL_SAVEFILE  pL_SaveFile ;
extern LWRP_EXPORT pL_SAVEFILEMEMORY pL_SaveFileMemory;
extern LWRP_EXPORT pL_SAVEFILETILE  pL_SaveFileTile ;
extern LWRP_EXPORT pL_SAVEFILEOFFSET  pL_SaveFileOffset ;
extern LWRP_EXPORT pL_SETCOMMENT  pL_SetComment ;
extern LWRP_EXPORT pL_SETLOADINFOCALLBACK  pL_SetLoadInfoCallback ;
extern LWRP_EXPORT pL_SETLOADRESOLUTION  pL_SetLoadResolution ;
extern LWRP_EXPORT pL_SETPCDRESOLUTION  pL_SetPCDResolution ;
extern LWRP_EXPORT pL_SETWMFRESOLUTION  pL_SetWMFResolution ;
extern LWRP_EXPORT pL_SETTAG pL_SetTag;
extern LWRP_EXPORT pL_STARTCOMPRESSBUFFER  pL_StartCompressBuffer ;
extern LWRP_EXPORT pL_STARTFEEDLOAD  pL_StartFeedLoad ;
extern LWRP_EXPORT pL_STOPFEEDLOAD  pL_StopFeedLoad ;
extern LWRP_EXPORT pL_WRITEFILECOMMENTEXT  pL_WriteFileCommentExt ;
extern LWRP_EXPORT pL_WRITEFILESTAMP  pL_WriteFileStamp ;
extern LWRP_EXPORT pL_SETSAVERESOLUTION  pL_SetSaveResolution ;
extern LWRP_EXPORT pL_GETSAVERESOLUTION  pL_GetSaveResolution ;
extern LWRP_EXPORT pL_2DSETVIEWPORT pL_2DSetViewport;
extern LWRP_EXPORT pL_2DGETVIEWPORT pL_2DGetViewport;
extern LWRP_EXPORT pL_2DSETVIEWMODE pL_2DSetViewMode;
extern LWRP_EXPORT pL_2DGETVIEWMODE pL_2DGetViewMode;
extern LWRP_EXPORT pL_VECLOADFILE pL_VecLoadFile;
extern LWRP_EXPORT pL_VECLOADMEMORY  pL_VecLoadMemory ;
extern LWRP_EXPORT pL_VECSTARTFEEDLOAD  pL_VecStartFeedLoad ;
extern LWRP_EXPORT pL_VECFEEDLOAD pL_VecFeedLoad;
extern LWRP_EXPORT pL_VECSTOPFEEDLOAD pL_VecStopFeedLoad;
extern LWRP_EXPORT pL_VECSAVEFILE pL_VecSaveFile;
extern LWRP_EXPORT pL_VECSAVEMEMORY pL_VecSaveMemory;
extern LWRP_EXPORT pL_GETDEFAULTLOADFILEOPTION  pL_GetDefaultLoadFileOption ;
extern LWRP_EXPORT pL_GETDEFAULTSAVEFILEOPTION  pL_GetDefaultSaveFileOption ;
extern LWRP_EXPORT pL_WRITEFILETAG pL_WriteFileTag;
extern LWRP_EXPORT pL_WRITEFILECOMMENT pL_WriteFileComment;
extern LWRP_EXPORT pL_DOCLOADFILE pL_DocLoadFile;
extern LWRP_EXPORT pL_DOCLOADMEMORY  pL_DocLoadMemory ;
extern LWRP_EXPORT pL_DOCSTARTFEEDLOAD  pL_DocStartFeedLoad ;
extern LWRP_EXPORT pL_DOCFEEDLOAD pL_DocFeedLoad;
extern LWRP_EXPORT pL_DOCSTOPFEEDLOAD pL_DocStopFeedLoad;
extern LWRP_EXPORT pL_DOCSAVEFILE pL_DocSaveFile;
extern LWRP_EXPORT pL_DOCSAVEMEMORY pL_DocSaveMemory;
extern LWRP_EXPORT pL_GETJ2KOPTIONS pL_GetJ2KOptions;
extern LWRP_EXPORT pL_GETDEFAULTJ2KOPTIONS pL_GetDefaultJ2KOptions;
extern LWRP_EXPORT pL_SETJ2KOPTIONS pL_SetJ2KOptions;
extern LWRP_EXPORT pL_LOADBITMAPRESIZE pL_LoadBitmapResize;
extern LWRP_EXPORT pL_SAVEBITMAPBUFFER pL_SaveBitmapBuffer;
extern LWRP_EXPORT pL_SAVEFILEBUFFER pL_SaveFileBuffer;
extern LWRP_EXPORT pL_LOADLAYER pL_LoadLayer;
extern LWRP_EXPORT pL_SAVEBITMAPWITHLAYERS pL_SaveBitmapWithLayers;
extern LWRP_EXPORT pL_READFILEEXTENSIONS pL_ReadFileExtensions;
extern LWRP_EXPORT pL_FREEEXTENSIONS pL_FreeExtensions;
extern LWRP_EXPORT pL_LOADEXTENSIONSTAMP pL_LoadExtensionStamp;
extern LWRP_EXPORT pL_GETEXTENSIONAUDIO pL_GetExtensionAudio;
extern LWRP_EXPORT pL_TRANSFORMFILE pL_TransformFile;

//-----------------------------------------------------------------------------
//--LTEFX.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------
extern LWRP_EXPORT pL_EFXPAINTTRANSITION               pL_EfxPaintTransition;
extern LWRP_EXPORT pL_EFXPAINTBITMAP                   pL_EfxPaintBitmap;
extern LWRP_EXPORT pL_EFXDRAWFRAME                     pL_EfxDrawFrame;
extern LWRP_EXPORT pL_EFXGRADIENTFILLRECT              pL_EfxGradientFillRect;
extern LWRP_EXPORT pL_EFXPATTERNFILLRECT               pL_EfxPatternFillRect;
extern LWRP_EXPORT pL_EFXDRAW3DTEXT                    pL_EfxDraw3dText;
extern LWRP_EXPORT pL_EFXDRAWROTATED3DTEXT             pL_EfxDrawRotated3dText;
extern LWRP_EXPORT pL_EFXDRAW3DSHAPE                   pL_EfxDraw3dShape;
extern LWRP_EXPORT pL_EFXEFFECTBLT                     pL_EfxEffectBlt;
extern LWRP_EXPORT pL_PAINTDCEFFECT                    pL_PaintDCEffect;
extern LWRP_EXPORT pL_PAINTRGNDCEFFECT                 pL_PaintRgnDCEffect;

//-----------------------------------------------------------------------------
//--LTDLG.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------
extern LWRP_EXPORT pL_DLGFILEOPEN                      pL_DlgFileOpen;
extern LWRP_EXPORT pL_DLGGETANGLE                      pL_DlgGetAngle;
extern LWRP_EXPORT pL_DLGGETSIZE                       pL_DlgGetSize;
extern LWRP_EXPORT pL_DLGGETFILTER                     pL_DlgGetFilter;
extern LWRP_EXPORT pL_DLGGETCHANGE                     pL_DlgGetChange;
extern LWRP_EXPORT pL_DLGGETGAMMA                      pL_DlgGetGamma;
extern LWRP_EXPORT pL_DLGGETNOISE                      pL_DlgGetNoise;
extern LWRP_EXPORT pL_DLGGETEMBOSS                     pL_DlgGetEmboss;
extern LWRP_EXPORT pL_DLGGETRANGE                      pL_DlgGetRange;
extern LWRP_EXPORT pL_DLGCOLORRES                      pL_DlgColorRes;
extern LWRP_EXPORT pL_DLGFILESAVE                      pL_DlgFileSave;
extern LWRP_EXPORT pL_DLGWINDOWLEVEL                   pL_DlgWindowLevel;
extern LWRP_EXPORT pL_DLGGETEFFECT                     pL_DlgGetEffect;
extern LWRP_EXPORT pL_DLGGETSHAPE                      pL_DlgGetShape;
extern LWRP_EXPORT pL_DLGGETTEXT                       pL_DlgGetText;
extern LWRP_EXPORT pL_DLGGETGRADIENT                   pL_DlgGetGradient;
extern LWRP_EXPORT pL_DLGGETTRANSITION                 pL_DlgGetTransition;
extern LWRP_EXPORT pL_DLGGETDIRECTORY                  pL_DlgGetDirectory;
extern LWRP_EXPORT pL_DLGCONTOURFILTER                 pL_DlgContourFilter;
extern LWRP_EXPORT pL_DLGGETSTRINGLEN                  pL_DlgGetStringlen;
extern LWRP_EXPORT pL_DLGGETSTRING                     pL_DlgGetString;          
extern LWRP_EXPORT pL_DLGSETSTRING                     pL_DlgSetString;       
extern LWRP_EXPORT pL_DLGSETFONT                       pL_DlgSetFont;
extern LWRP_EXPORT pL_DLGHALFTONE                      pL_DlgHalftone;

//-----------------------------------------------------------------------------
//--LTISI.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------
extern LWRP_EXPORT pL_ISISISAVAILABLE                  pL_IsISISAvailable;
extern LWRP_EXPORT pL_ISISACQUIRE                      pL_ISISAcquire;
extern LWRP_EXPORT pL_ISISACQUIREMULTI                 pL_ISISAcquireMulti;
extern LWRP_EXPORT pL_ISISSELECT                       pL_ISISSelect;
extern LWRP_EXPORT pL_ISISLOADDRIVER                   pL_ISISLoadDriver;
extern LWRP_EXPORT pL_ISISUNLOADDRIVER                 pL_ISISUnloadDriver;
extern LWRP_EXPORT pL_ISISSETTAGLONG                   pL_ISISSetTagLong;
extern LWRP_EXPORT pL_ISISGETTAGLONG                   pL_ISISGetTagLong;
extern LWRP_EXPORT pL_ISISSETTAGSHORT                  pL_ISISSetTagShort;
extern LWRP_EXPORT pL_ISISGETTAGSHORT                  pL_ISISGetTagShort;
extern LWRP_EXPORT pL_ISISSETSCANOPTIONS               pL_ISISSetScanOptions;
extern LWRP_EXPORT pL_ISISSETTAGASCII                  pL_ISISSetTagASCII;
extern LWRP_EXPORT pL_ISISGETTAGASCII                  pL_ISISGetTagASCII;
extern LWRP_EXPORT pL_ISISGETTAGASCIICHOICE            pL_ISISGetTagASCIIChoice;
extern LWRP_EXPORT pL_ISISGETTAGLONGCHOICE             pL_ISISGetTagLongChoice;
extern LWRP_EXPORT pL_ISISGETTAGSHORTCHOICE            pL_ISISGetTagShortChoice;

//-----------------------------------------------------------------------------
//--LTTWN.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------
extern LWRP_EXPORT pL_TWAINACQUIRE                     pL_TwainAcquire;
extern LWRP_EXPORT pL_TWAINACQUIREEXT                  pL_TwainAcquireExt;
extern LWRP_EXPORT pL_TWAINCLOSESESSION                pL_TwainCloseSession;
extern LWRP_EXPORT pL_TWAINENUMSOURCES                 pL_TwainEnumSources;
extern LWRP_EXPORT pL_TWAINSELECT                      pL_TwainSelect;
extern LWRP_EXPORT pL_TWAINSETPROPS                    pL_TwainSetProps;
extern LWRP_EXPORT pL_TWAINGETPROPS                    pL_TwainGetProps;
extern LWRP_EXPORT pL_ISTWAINAVAILABLE                 pL_IsTwainAvailable;

//-----------------------------------------------------------------------------
//--LTANN.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------


extern LWRP_EXPORT pL_ANNBRINGTOFRONT  pL_AnnBringToFront ;
extern LWRP_EXPORT pL_ANNCLIPBOARDREADY pL_AnnClipboardReady;
extern LWRP_EXPORT pL_ANNCOPY pL_AnnCopy;
extern LWRP_EXPORT pL_ANNCOPYFROMCLIPBOARD pL_AnnCopyFromClipboard;
extern LWRP_EXPORT pL_ANNCOPYTOCLIPBOARD pL_AnnCopyToClipboard;
extern LWRP_EXPORT pL_ANNCUTTOCLIPBOARD pL_AnnCutToClipboard;
extern LWRP_EXPORT pL_ANNCREATE  pL_AnnCreate ;
extern LWRP_EXPORT pL_ANNCREATECONTAINER  pL_AnnCreateContainer ;
extern LWRP_EXPORT pL_ANNCREATEITEM  pL_AnnCreateItem ;
extern LWRP_EXPORT pL_ANNCREATETOOLBAR pL_AnnCreateToolBar;
extern LWRP_EXPORT pL_ANNDEFINE  pL_AnnDefine ;
extern LWRP_EXPORT pL_ANNDELETEPAGEOFFSET pL_AnnDeletePageOffset;
extern LWRP_EXPORT pL_ANNDELETEPAGE pL_AnnDeletePage;
extern LWRP_EXPORT pL_ANNDELETEPAGEMEMORY  pL_AnnDeletePageMemory ;
extern LWRP_EXPORT pL_ANNDESTROY  pL_AnnDestroy ;
extern LWRP_EXPORT pL_ANNDRAW  pL_AnnDraw ;
extern LWRP_EXPORT pL_ANNENUMERATE  pL_AnnEnumerate ;
extern LWRP_EXPORT pL_ANNFILEINFO  pL_AnnFileInfo ;
extern LWRP_EXPORT pL_ANNFILEINFOOFFSET  pL_AnnFileInfoOffset ;
extern LWRP_EXPORT pL_ANNFILEINFOMEMORY  pL_AnnFileInfoMemory ;
extern LWRP_EXPORT pL_ANNFLIP pL_AnnFlip;
extern LWRP_EXPORT pL_ANNGETACTIVESTATE  pL_AnnGetActiveState ;
extern LWRP_EXPORT pL_ANNGETAUTOCONTAINER  pL_AnnGetAutoContainer ;
extern LWRP_EXPORT pL_ANNGETAUTODRAWENABLE  pL_AnnGetAutoDrawEnable ;
extern LWRP_EXPORT pL_ANNGETAUTOMENUENABLE  pL_AnnGetAutoMenuEnable ;
extern LWRP_EXPORT pL_ANNGETAUTOTEXT  pL_AnnGetAutoText ;
extern LWRP_EXPORT pL_ANNGETAUTOTEXTLEN  pL_AnnGetAutoTextLen ;
extern LWRP_EXPORT pL_ANNGETBACKCOLOR  pL_AnnGetBackColor ;
extern LWRP_EXPORT pL_ANNGETBITMAP  pL_AnnGetBitmap ;
extern LWRP_EXPORT pL_ANNGETBITMAPDPIX pL_AnnGetBitmapDpiX;
extern LWRP_EXPORT pL_ANNGETBITMAPDPIY pL_AnnGetBitmapDpiY;
extern LWRP_EXPORT pL_ANNGETBOUNDINGRECT  pL_AnnGetBoundingRect ;
extern LWRP_EXPORT pL_ANNGETCONTAINER  pL_AnnGetContainer ;
extern LWRP_EXPORT pL_ANNGETDISTANCE pL_AnnGetDistance;
extern LWRP_EXPORT pL_ANNGETDPIX  pL_AnnGetDpiX ;
extern LWRP_EXPORT pL_ANNGETDPIY  pL_AnnGetDpiY ;
extern LWRP_EXPORT pL_ANNGETFILLMODE  pL_AnnGetFillMode ;
extern LWRP_EXPORT pL_ANNGETFILLPATTERN  pL_AnnGetFillPattern ;
extern LWRP_EXPORT pL_ANNGETFONTBOLD  pL_AnnGetFontBold ;
extern LWRP_EXPORT pL_ANNGETFONTITALIC  pL_AnnGetFontItalic ;
extern LWRP_EXPORT pL_ANNGETFONTNAME  pL_AnnGetFontName ;
extern LWRP_EXPORT pL_ANNGETFONTNAMELEN  pL_AnnGetFontNameLen ;
extern LWRP_EXPORT pL_ANNGETFONTSIZE  pL_AnnGetFontSize ;
extern LWRP_EXPORT pL_ANNGETFONTSTRIKETHROUGH  pL_AnnGetFontStrikeThrough ;
extern LWRP_EXPORT pL_ANNGETFONTUNDERLINE  pL_AnnGetFontUnderline ;
extern LWRP_EXPORT pL_ANNGETFORECOLOR  pL_AnnGetForeColor ;
extern LWRP_EXPORT pL_ANNGETGAUGELENGTH pL_AnnGetGaugeLength;
extern LWRP_EXPORT pL_ANNGETHYPERLINK  pL_AnnGetHyperlink ;
extern LWRP_EXPORT pL_ANNGETHYPERLINKLEN  pL_AnnGetHyperlinkLen ;
extern LWRP_EXPORT pL_ANNGETHYPERLINKMENUENABLE pL_AnnGetHyperlinkMenuEnable;
extern LWRP_EXPORT pL_ANNGETLINESTYLE  pL_AnnGetLineStyle ;
extern LWRP_EXPORT pL_ANNGETLINEWIDTH  pL_AnnGetLineWidth ;
extern LWRP_EXPORT pL_ANNGETLOCKED  pL_AnnGetLocked ;
extern LWRP_EXPORT pL_ANNGETOFFSETX  pL_AnnGetOffsetX ;
extern LWRP_EXPORT pL_ANNGETOFFSETY  pL_AnnGetOffsetY ;
extern LWRP_EXPORT pL_ANNGETPOINTCOUNT  pL_AnnGetPointCount ;
extern LWRP_EXPORT pL_ANNGETPOINTS  pL_AnnGetPoints ;
extern LWRP_EXPORT pL_ANNGETPOLYFILLMODE  pL_AnnGetPolyFillMode ;
extern LWRP_EXPORT pL_ANNGETRECT  pL_AnnGetRect ;
extern LWRP_EXPORT pL_ANNGETROP2  pL_AnnGetROP2 ;
extern LWRP_EXPORT pL_ANNGETSCALARX  pL_AnnGetScalarX ;
extern LWRP_EXPORT pL_ANNGETSCALARY  pL_AnnGetScalarY ;
extern LWRP_EXPORT pL_ANNGETSELECTCOUNT  pL_AnnGetSelectCount ;
extern LWRP_EXPORT pL_ANNGETSELECTED  pL_AnnGetSelected ;
extern LWRP_EXPORT pL_ANNGETSELECTITEMS pL_AnnGetSelectItems;
extern LWRP_EXPORT pL_ANNGETSELECTRECT pL_AnnGetSelectRect;
extern LWRP_EXPORT pL_ANNGETTAG  pL_AnnGetTag ;
extern LWRP_EXPORT pL_ANNGETTEXT  pL_AnnGetText ;
extern LWRP_EXPORT pL_ANNGETTEXTLEN  pL_AnnGetTextLen ;
extern LWRP_EXPORT pL_ANNGETTOOL  pL_AnnGetTool ;
extern LWRP_EXPORT pL_ANNGETTOOLBARBUTTONVISIBLE pL_AnnGetToolBarButtonVisible;
extern LWRP_EXPORT pL_ANNGETTOOLBARCHECKED  pL_AnnGetToolBarChecked ;
extern LWRP_EXPORT pL_ANNGETTRANSPARENT  pL_AnnGetTransparent ;
extern LWRP_EXPORT pL_ANNGETTYPE  pL_AnnGetType ;
extern LWRP_EXPORT pL_ANNGETTOPCONTAINER  pL_AnnGetTopContainer ;
extern LWRP_EXPORT pL_ANNGETUNIT pL_AnnGetUnit;
extern LWRP_EXPORT pL_ANNGETUNITLEN pL_AnnGetUnitLen;
extern LWRP_EXPORT pL_ANNGETUSERMODE  pL_AnnGetUserMode ;
extern LWRP_EXPORT pL_ANNGETVISIBLE  pL_AnnGetVisible ;
extern LWRP_EXPORT pL_ANNGETWND  pL_AnnGetWnd ;
extern LWRP_EXPORT pL_ANNHITTEST  pL_AnnHitTest ;
extern LWRP_EXPORT pL_ANNINSERT  pL_AnnInsert ;
extern LWRP_EXPORT pL_ANNGETITEM  pL_AnnGetItem ;
extern LWRP_EXPORT pL_ANNLOAD  pL_AnnLoad ;
extern LWRP_EXPORT pL_ANNLOADOFFSET  pL_AnnLoadOffset ;
extern LWRP_EXPORT pL_ANNLOADMEMORY  pL_AnnLoadMemory ;
extern LWRP_EXPORT pL_ANNLOCK  pL_AnnLock ;
extern LWRP_EXPORT pL_ANNMOVE pL_AnnMove;
extern LWRP_EXPORT pL_ANNPRINT pL_AnnPrint;
extern LWRP_EXPORT pL_ANNREALIZE pL_AnnRealize;
extern LWRP_EXPORT pL_ANNRESIZE pL_AnnResize;
extern LWRP_EXPORT pL_ANNREVERSE pL_AnnReverse;
extern LWRP_EXPORT pL_ANNREMOVE  pL_AnnRemove ;
extern LWRP_EXPORT pL_ANNROTATE pL_AnnRotate;
extern LWRP_EXPORT pL_ANNSAVE  pL_AnnSave ;
extern LWRP_EXPORT pL_ANNSAVEOFFSET  pL_AnnSaveOffset ;
extern LWRP_EXPORT pL_ANNSAVEMEMORY  pL_AnnSaveMemory ;
extern LWRP_EXPORT pL_ANNSAVETAG pL_AnnSaveTag;
extern LWRP_EXPORT pL_ANNSELECTPOINT pL_AnnSelectPoint;
extern LWRP_EXPORT pL_ANNSELECTRECT pL_AnnSelectRect;
extern LWRP_EXPORT pL_ANNSENDTOBACK  pL_AnnSendToBack ;
extern LWRP_EXPORT pL_ANNSETACTIVESTATE  pL_AnnSetActiveState ;
extern LWRP_EXPORT pL_ANNSETAUTOCONTAINER  pL_AnnSetAutoContainer ;
extern LWRP_EXPORT pL_ANNSETAUTODRAWENABLE  pL_AnnSetAutoDrawEnable ;
extern LWRP_EXPORT pL_ANNSETAUTOMENUENABLE  pL_AnnSetAutoMenuEnable ;
extern LWRP_EXPORT pL_ANNSETAUTOTEXT  pL_AnnSetAutoText ;
extern LWRP_EXPORT pL_ANNSETBACKCOLOR  pL_AnnSetBackColor ;
extern LWRP_EXPORT pL_ANNSETBITMAP  pL_AnnSetBitmap ;
extern LWRP_EXPORT pL_ANNSETBITMAPDPIX pL_AnnSetBitmapDpiX;
extern LWRP_EXPORT pL_ANNSETBITMAPDPIY pL_AnnSetBitmapDpiY;
extern LWRP_EXPORT pL_ANNSETDPIX pL_AnnSetDpiX;
extern LWRP_EXPORT pL_ANNSETDPIY pL_AnnSetDpiY;
extern LWRP_EXPORT pL_ANNSETFILLMODE  pL_AnnSetFillMode ;
extern LWRP_EXPORT pL_ANNSETFILLPATTERN  pL_AnnSetFillPattern ;
extern LWRP_EXPORT pL_ANNSETFONTBOLD  pL_AnnSetFontBold ;
extern LWRP_EXPORT pL_ANNSETFONTITALIC  pL_AnnSetFontItalic ;
extern LWRP_EXPORT pL_ANNSETFONTNAME  pL_AnnSetFontName ;
extern LWRP_EXPORT pL_ANNSETFONTSIZE  pL_AnnSetFontSize ;
extern LWRP_EXPORT pL_ANNSETFONTSTRIKETHROUGH  pL_AnnSetFontStrikeThrough ;
extern LWRP_EXPORT pL_ANNSETFONTUNDERLINE  pL_AnnSetFontUnderline ;
extern LWRP_EXPORT pL_ANNSETFORECOLOR  pL_AnnSetForeColor ;
extern LWRP_EXPORT pL_ANNSETGAUGELENGTH pL_AnnSetGaugeLength;
extern LWRP_EXPORT pL_ANNSETHYPERLINK  pL_AnnSetHyperlink ;
extern LWRP_EXPORT pL_ANNSETHYPERLINKMENUENABLE pL_AnnSetHyperlinkMenuEnable;
extern LWRP_EXPORT pL_ANNSETLINESTYLE  pL_AnnSetLineStyle ;
extern LWRP_EXPORT pL_ANNSETLINEWIDTH  pL_AnnSetLineWidth ;
extern LWRP_EXPORT pL_ANNSETOFFSETX pL_AnnSetOffsetX;
extern LWRP_EXPORT pL_ANNSETOFFSETY pL_AnnSetOffsetY;
extern LWRP_EXPORT pL_ANNSETPOINTS  pL_AnnSetPoints ;
extern LWRP_EXPORT pL_ANNSETPOLYFILLMODE  pL_AnnSetPolyFillMode ;
extern LWRP_EXPORT pL_ANNSETROP2  pL_AnnSetROP2 ;
extern LWRP_EXPORT pL_ANNSETRECT  pL_AnnSetRect ;
extern LWRP_EXPORT pL_ANNSETSELECTED  pL_AnnSetSelected ;
extern LWRP_EXPORT pL_ANNSETSCALARX pL_AnnSetScalarX;
extern LWRP_EXPORT pL_ANNSETSCALARY pL_AnnSetScalarY;
extern LWRP_EXPORT pL_ANNSETTAG  pL_AnnSetTag ;
extern LWRP_EXPORT pL_ANNSETTEXT  pL_AnnSetText ;
extern LWRP_EXPORT pL_ANNSETTOOL  pL_AnnSetTool ;
extern LWRP_EXPORT pL_ANNSETTOOLBARBUTTONVISIBLE pL_AnnSetToolBarButtonVisible;
extern LWRP_EXPORT pL_ANNSETTOOLBARCHECKED pL_AnnSetToolBarChecked;
extern LWRP_EXPORT pL_ANNSETTRANSPARENT  pL_AnnSetTransparent ;
extern LWRP_EXPORT pL_ANNSETUNDODEPTH  pL_AnnSetUndoDepth ;
extern LWRP_EXPORT pL_ANNSETUNIT pL_AnnSetUnit;
extern LWRP_EXPORT pL_ANNSETUSERMODE  pL_AnnSetUserMode ;
extern LWRP_EXPORT pL_ANNSETVISIBLE  pL_AnnSetVisible ;
extern LWRP_EXPORT pL_ANNSETWND  pL_AnnSetWnd ;
extern LWRP_EXPORT pL_ANNSHOWLOCKEDICON  pL_AnnShowLockedIcon ;
extern LWRP_EXPORT pL_ANNUNDO  pL_AnnUndo ;
extern LWRP_EXPORT pL_ANNUNLOCK  pL_AnnUnlock ;
extern LWRP_EXPORT pL_ANNUNREALIZE pL_AnnUnrealize;
extern LWRP_EXPORT pL_ANNSETNODES pL_AnnSetNodes;
extern LWRP_EXPORT pL_ANNGETNODES pL_AnnGetNodes;
extern LWRP_EXPORT pL_ANNSETPROTRACTOROPTIONS pL_AnnSetProtractorOptions;
extern LWRP_EXPORT pL_ANNGETPROTRACTOROPTIONS pL_AnnGetProtractorOptions;
extern LWRP_EXPORT pL_ANNSETNAME  pL_AnnSetName ;
extern LWRP_EXPORT pL_ANNGETNAME  pL_AnnGetName ;
extern LWRP_EXPORT pL_ANNSETSHOWFLAGS  pL_AnnSetShowFlags ;
extern LWRP_EXPORT pL_ANNGETSHOWFLAGS  pL_AnnGetShowFlags ;
extern LWRP_EXPORT pL_ANNGETANGLE pL_AnnGetAngle;
extern LWRP_EXPORT pL_ANNSETMETAFILE  pL_AnnSetMetafile ;
extern LWRP_EXPORT pL_ANNGETMETAFILE  pL_AnnGetMetafile ;
extern LWRP_EXPORT pL_ANNSETPREDEFINEDMETAFILE pL_AnnSetPredefinedMetafile;
extern LWRP_EXPORT pL_ANNGETPREDEFINEDMETAFILE pL_AnnGetPredefinedMetafile;
extern LWRP_EXPORT pL_ANNSETSECONDARYBITMAP  pL_AnnSetSecondaryBitmap ;
extern LWRP_EXPORT pL_ANNGETSECONDARYBITMAP  pL_AnnGetSecondaryBitmap ;
extern LWRP_EXPORT pL_ANNSETAUTOMENUITEMENABLE pL_AnnSetAutoMenuItemEnable;
extern LWRP_EXPORT pL_ANNGETAUTOMENUITEMENABLE pL_AnnGetAutoMenuItemEnable;
extern LWRP_EXPORT pL_ANNSETAUTOMENUSTATE pL_AnnSetAutoMenuState;
extern LWRP_EXPORT pL_ANNGETAUTOMENUSTATE pL_AnnGetAutoMenuState;
extern LWRP_EXPORT pL_ANNSETUSER pL_AnnSetUser;
extern LWRP_EXPORT pL_ANNSETTOOLBARBUTTONS pL_AnnSetToolBarButtons;
extern LWRP_EXPORT pL_ANNGETTOOLBARBUTTONS pL_AnnGetToolBarButtons;
extern LWRP_EXPORT pL_ANNFREETOOLBARBUTTONS pL_AnnFreeToolBarButtons;
extern LWRP_EXPORT pL_ANNGETTOOLBARINFO pL_AnnGetToolBarInfo;
extern LWRP_EXPORT pL_ANNSETTOOLBARCOLUMNS pL_AnnSetToolBarColumns;
extern LWRP_EXPORT pL_ANNSETTOOLBARROWS pL_AnnSetToolBarRows;
extern LWRP_EXPORT pL_ANNSETAUTODEFAULTS pL_AnnSetAutoDefaults;
extern LWRP_EXPORT pL_ANNSETTRANSPARENTCOLOR  pL_AnnSetTransparentColor ;
extern LWRP_EXPORT pL_ANNGETTRANSPARENTCOLOR  pL_AnnGetTransparentColor ;
extern LWRP_EXPORT pL_ANNGETUNDODEPTH  pL_AnnGetUndoDepth ;
extern LWRP_EXPORT pL_ANNGROUP  pL_AnnGroup ;
extern LWRP_EXPORT pL_ANNUNGROUP  pL_AnnUngroup ;
extern LWRP_EXPORT pL_ANNSETAUTOOPTIONS  pL_AnnSetAutoOptions ;
extern LWRP_EXPORT pL_ANNGETAUTOOPTIONS  pL_AnnGetAutoOptions ;
extern LWRP_EXPORT pL_ANNGETOBJECTFROMTAG  pL_AnnGetObjectFromTag ;
extern LWRP_EXPORT pL_ANNGETRGNHANDLE pL_AnnGetRgnHandle;
extern LWRP_EXPORT pL_ANNGETAREA pL_AnnGetArea;
extern LWRP_EXPORT pL_ANNSETAUTODIALOGFONTSIZE pL_AnnSetAutoDialogFontSize;
extern LWRP_EXPORT pL_ANNGETAUTODIALOGFONTSIZE pL_AnnGetAutoDialogFontSize;
extern LWRP_EXPORT pL_ANNSETGROUPING pL_AnnSetGrouping;
extern LWRP_EXPORT pL_ANNGETGROUPING pL_AnnGetGrouping;
extern LWRP_EXPORT pL_ANNSETAUTOBACKCOLOR pL_AnnSetAutoBackColor;
extern LWRP_EXPORT pL_ANNGETAUTOBACKCOLOR pL_AnnGetAutoBackColor;
extern LWRP_EXPORT pL_ANNADDUNDONODE pL_AnnAddUndoNode;
extern LWRP_EXPORT pL_ANNSETAUTOUNDOENABLE pL_AnnSetAutoUndoEnable;
extern LWRP_EXPORT pL_ANNGETAUTOUNDOENABLE pL_AnnGetAutoUndoEnable;
extern LWRP_EXPORT pL_ANNSETTOOLBARPARENT pL_AnnSetToolBarParent;

//-----------------------------------------------------------------------------
//--LTSCR.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------
extern LWRP_EXPORT pL_SETCAPTUREOPTION                 pL_SetCaptureOption;
extern LWRP_EXPORT pL_GETCAPTUREOPTION                 pL_GetCaptureOption;
extern LWRP_EXPORT pL_CAPTUREWINDOW                    pL_CaptureWindow;
extern LWRP_EXPORT pL_CAPTUREACTIVEWINDOW              pL_CaptureActiveWindow;
extern LWRP_EXPORT pL_CAPTUREACTIVECLIENT              pL_CaptureActiveClient;
extern LWRP_EXPORT pL_CAPTUREWALLPAPER                 pL_CaptureWallPaper;
extern LWRP_EXPORT pL_CAPTUREFULLSCREEN                pL_CaptureFullScreen;
extern LWRP_EXPORT pL_CAPTUREMENUUNDERCURSOR           pL_CaptureMenuUnderCursor;
extern LWRP_EXPORT pL_CAPTUREWINDOWUNDERCURSOR         pL_CaptureWindowUnderCursor;
extern LWRP_EXPORT pL_CAPTURESELECTEDOBJECT            pL_CaptureSelectedObject;
extern LWRP_EXPORT pL_CAPTUREAREA                      pL_CaptureArea;
extern LWRP_EXPORT pL_CAPTUREMOUSECURSOR               pL_CaptureMouseCursor;
extern LWRP_EXPORT pL_CAPTURESETHOTKEYCALLBACK         pL_CaptureSetHotKeyCallback;
extern LWRP_EXPORT pL_SETCAPTUREOPTIONDLG              pL_SetCaptureOptionDlg;
extern LWRP_EXPORT pL_CAPTUREAREAOPTIONDLG             pL_CaptureAreaOptionDlg;
extern LWRP_EXPORT pL_CAPTUREOBJECTOPTIONDLG           pL_CaptureObjectOptionDlg;
extern LWRP_EXPORT pL_GETDEFAULTAREAOPTION             pL_GetDefaultAreaOption;
extern LWRP_EXPORT pL_GETDEFAULTOBJECTOPTION           pL_GetDefaultObjectOption;
extern LWRP_EXPORT pL_STOPCAPTURE                      pL_StopCapture;
extern LWRP_EXPORT pL_CAPTUREFROMEXEDLG                pL_CaptureFromExeDlg;
extern LWRP_EXPORT pL_CAPTUREFROMEXE                   pL_CaptureFromExe;
extern LWRP_EXPORT pL_CAPTUREGETRESCOUNT               pL_CaptureGetResCount;
extern LWRP_EXPORT pL_ISCAPTUREACTIVE                  pL_IsCaptureActive;

//-----------------------------------------------------------------------------
//--LTNET.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------
extern LWRP_EXPORT pL_INETCREATEPACKET pL_InetCreatePacket;
extern LWRP_EXPORT pL_INETCREATEPACKETFROMPARAMS pL_InetCreatePacketFromParams;
extern LWRP_EXPORT pL_INETFREEPACKET pL_InetFreePacket;
extern LWRP_EXPORT pL_INETSENDCMD pL_InetSendCmd;
extern LWRP_EXPORT pL_INETSENDRSP pL_InetSendRsp;
extern LWRP_EXPORT pL_INETSENDLOADCMD pL_InetSendLoadCmd;
extern LWRP_EXPORT pL_INETSENDLOADRSP pL_InetSendLoadRsp;
extern LWRP_EXPORT pL_INETSENDSAVECMD pL_InetSendSaveCmd;
extern LWRP_EXPORT pL_INETSENDSAVERSP pL_InetSendSaveRsp;
extern LWRP_EXPORT pL_INETSENDCREATEWINCMD pL_InetSendCreateWinCmd;
extern LWRP_EXPORT pL_INETSENDCREATEWINRSP pL_InetSendCreateWinRsp;
extern LWRP_EXPORT pL_INETSENDSIZEWINCMD pL_InetSendSizeWinCmd;
extern LWRP_EXPORT pL_INETSENDSIZEWINRSP pL_InetSendSizeWinRsp;
extern LWRP_EXPORT pL_INETSENDSHOWWINCMD pL_InetSendShowWinCmd;
extern LWRP_EXPORT pL_INETSENDSHOWWINRSP pL_InetSendShowWinRsp;
extern LWRP_EXPORT pL_INETSENDCLOSEWINCMD pL_InetSendCloseWinCmd;
extern LWRP_EXPORT pL_INETSENDCLOSEWINRSP pL_InetSendCloseWinRsp;
extern LWRP_EXPORT pL_INETSENDFREEBITMAPCMD pL_InetSendFreeBitmapCmd;
extern LWRP_EXPORT pL_INETSENDFREEBITMAPRSP pL_InetSendFreeBitmapRsp;
extern LWRP_EXPORT pL_INETSENDSETRECTCMD pL_InetSendSetRectCmd;
extern LWRP_EXPORT pL_INETSENDSETRECTRSP pL_InetSendSetRectRsp;
extern LWRP_EXPORT pL_INETSETCOMMANDCALLBACK pL_InetSetCommandCallback;
extern LWRP_EXPORT pL_INETSETRESPONSECALLBACK pL_InetSetResponseCallback;
extern LWRP_EXPORT pL_INETSENDATTACHBITMAPCMD pL_InetSendAttachBitmapCmd;
extern LWRP_EXPORT pL_INETSENDATTACHBITMAPRSP pL_InetSendAttachBitmapRsp;
extern LWRP_EXPORT pL_INETCONNECT pL_InetConnect;
extern LWRP_EXPORT pL_INETSERVERINIT pL_InetServerInit;
extern LWRP_EXPORT pL_INETCLOSE pL_InetClose;
extern LWRP_EXPORT pL_INETSENDDATA pL_InetSendData;
extern LWRP_EXPORT pL_INETSENDMMDATA pL_InetSendMMData;
extern LWRP_EXPORT pL_INETREADDATA pL_InetReadData;
extern LWRP_EXPORT pL_INETGETHOSTNAME pL_InetGetHostName;
extern LWRP_EXPORT pL_INETACCEPTCONNECT pL_InetAcceptConnect;
extern LWRP_EXPORT pL_INETSENDBITMAP pL_InetSendBitmap;
extern LWRP_EXPORT pL_INETAUTOPROCESS pL_InetAutoProcess;
extern LWRP_EXPORT pL_INETSENDRAWDATA pL_InetSendRawData;
extern LWRP_EXPORT pL_INETGETQUEUESIZE pL_InetGetQueueSize;
extern LWRP_EXPORT pL_INETCLEARQUEUE pL_InetClearQueue;
extern LWRP_EXPORT pL_INETSTARTUP pL_InetStartUp;
extern LWRP_EXPORT pL_INETSHUTDOWN pL_InetShutDown;
extern LWRP_EXPORT pL_INETSENDSOUND pL_InetSendSound;
extern LWRP_EXPORT pL_INETATTACHTOSOCKET pL_InetAttachToSocket;
extern LWRP_EXPORT pL_INETDETACHFROMSOCKET pL_InetDetachFromSocket;
extern LWRP_EXPORT pL_INETSETCALLBACK pL_InetSetCallback;
extern LWRP_EXPORT pL_INETGETCALLBACK pL_InetGetCallback;
extern LWRP_EXPORT pL_INETGETPARAMETERS pL_InetGetParameters;
extern LWRP_EXPORT pL_INETCOPYPARAMETERS pL_InetCopyParameters;
extern LWRP_EXPORT pL_INETFREEPARAMETERS pL_InetFreeParameters;

//-----------------------------------------------------------------------------
//--LTWEB.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------
extern LWRP_EXPORT pL_INETHTTPCONNECT pL_InetHttpConnect;
extern LWRP_EXPORT pL_INETHTTPDISCONNECT pL_InetHttpDisconnect;
extern LWRP_EXPORT pL_INETHTTPOPENREQUEST pL_InetHttpOpenRequest;
extern LWRP_EXPORT pL_INETHTTPCLOSEREQUEST pL_InetHttpCloseRequest;
extern LWRP_EXPORT pL_INETHTTPSENDBITMAP pL_InetHttpSendBitmap;
extern LWRP_EXPORT pL_INETHTTPSENDDATA pL_InetHttpSendData;
extern LWRP_EXPORT pL_INETHTTPSENDFORM pL_InetHttpSendForm;
extern LWRP_EXPORT pL_INETHTTPSENDREQUEST pL_InetHttpSendRequest;
extern LWRP_EXPORT pL_INETHTTPGETRESPONSE pL_InetHttpGetResponse;
extern LWRP_EXPORT pL_INETHTTPGETSERVERSTATUS pL_InetHttpGetServerStatus;
extern LWRP_EXPORT pL_INETFTPCONNECT pL_InetFtpConnect;
extern LWRP_EXPORT pL_INETFTPDISCONNECT pL_InetFtpDisconnect;
extern LWRP_EXPORT pL_INETFTPSENDFILE pL_InetFtpSendFile;
extern LWRP_EXPORT pL_INETFTPGETFILE pL_InetFtpGetFile;
extern LWRP_EXPORT pL_INETFTPRENAMEFILE pL_InetFtpRenameFile;
extern LWRP_EXPORT pL_INETFTPDELETEFILE pL_InetFtpDeleteFile;
extern LWRP_EXPORT pL_INETFTPCREATEDIR pL_InetFtpCreateDir;
extern LWRP_EXPORT pL_INETFTPDELETEDIR pL_InetFtpDeleteDir;
extern LWRP_EXPORT pL_INETFTPGETCURRENTDIR pL_InetFtpGetCurrentDir;
extern LWRP_EXPORT pL_INETFTPBROWSEDIR pL_InetFtpBrowseDir;
extern LWRP_EXPORT pL_INETFTPCHANGEDIR pL_InetFtpChangeDir;
extern LWRP_EXPORT pL_INETFTPSENDBITMAP pL_InetFtpSendBitmap;

//-----------------------------------------------------------------------------
//--LTTMB.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------
extern LWRP_EXPORT pL_BROWSEDIR                        pL_BrowseDir;

//-----------------------------------------------------------------------------
//--LTLST.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------
extern LWRP_EXPORT pL_CREATEIMAGELISTCONTROL           pL_CreateImageListControl;
extern LWRP_EXPORT pL_USEIMAGELISTCONTROL              pL_UseImageListControl;

//-----------------------------------------------------------------------------
//--LVKRN.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------
extern LWRP_EXPORT pL_VECDUPLICATEOBJECTDESCRIPTOR pL_VecDuplicateObjectDescriptor;
//Do not remove the one above

/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  General functions.                                                   []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
extern LWRP_EXPORT pL_VECINIT pL_VecInit;
extern LWRP_EXPORT pL_VECFREE pL_VecFree;
extern LWRP_EXPORT pL_VECEMPTY pL_VecEmpty;
extern LWRP_EXPORT pL_VECISEMPTY pL_VecIsEmpty;
extern LWRP_EXPORT pL_VECCOPY pL_VecCopy;
extern LWRP_EXPORT pL_VECSETDISPLAYOPTIONS pL_VecSetDisplayOptions;
extern LWRP_EXPORT pL_VECGETDISPLAYOPTIONS pL_VecGetDisplayOptions;
extern LWRP_EXPORT pL_VECINVERTCOLORS pL_VecInvertColors;
extern LWRP_EXPORT pL_VECSETVIEWPORT pL_VecSetViewport;
extern LWRP_EXPORT pL_VECGETVIEWPORT pL_VecGetViewport;
extern LWRP_EXPORT pL_VECSETPAN pL_VecSetPan;
extern LWRP_EXPORT pL_VECGETPAN pL_VecGetPan;
extern LWRP_EXPORT pL_VECPAINT pL_VecPaint;
extern LWRP_EXPORT pL_VECREALIZE pL_VecRealize;
extern LWRP_EXPORT pL_VECPAINTDC pL_VecPaintDC;
extern LWRP_EXPORT pL_VECIS3D pL_VecIs3D;
extern LWRP_EXPORT pL_VECISLOCKED pL_VecIsLocked;
extern LWRP_EXPORT pL_VECSETLOCKED pL_VecSetLocked;
extern LWRP_EXPORT pL_VECSETBACKGROUNDCOLOR pL_VecSetBackgroundColor;
extern LWRP_EXPORT pL_VECGETBACKGROUNDCOLOR pL_VecGetBackgroundColor;
extern LWRP_EXPORT pL_VECLOGICALTOPHYSICAL pL_VecLogicalToPhysical;
extern LWRP_EXPORT pL_VECPHYSICALTOLOGICAL pL_VecPhysicalToLogical;
extern LWRP_EXPORT pL_VECSETPALETTE pL_VecSetPalette;
extern LWRP_EXPORT pL_VECGETPALETTE pL_VecGetPalette;
extern LWRP_EXPORT pL_VECSETVIEWMODE pL_VecSetViewMode;
extern LWRP_EXPORT pL_VECGETVIEWMODE pL_VecGetViewMode;
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Transformation function.                                             []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
extern LWRP_EXPORT pL_VECSETTRANSLATION pL_VecSetTranslation;
extern LWRP_EXPORT pL_VECGETTRANSLATION pL_VecGetTranslation;
extern LWRP_EXPORT pL_VECSETROTATION pL_VecSetRotation;
extern LWRP_EXPORT pL_VECGETROTATION pL_VecGetRotation;
extern LWRP_EXPORT pL_VECSETSCALE pL_VecSetScale;
extern LWRP_EXPORT pL_VECGETSCALE pL_VecGetScale;
extern LWRP_EXPORT pL_VECSETORIGIN pL_VecSetOrigin;
extern LWRP_EXPORT pL_VECGETORIGIN pL_VecGetOrigin;
extern LWRP_EXPORT pL_VECAPPLYTRANSFORMATION pL_VecApplyTransformation;
extern LWRP_EXPORT pL_VECZOOMRECT pL_VecZoomRect;
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Attributes functions.                                                []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
extern LWRP_EXPORT pL_VECSETBINDVERTICESMODE pL_VecSetBindVerticesMode;
extern LWRP_EXPORT pL_VECGETBINDVERTICESMODE pL_VecGetBindVerticesMode;
extern LWRP_EXPORT pL_VECSETPARALLELOGRAM pL_VecSetParallelogram;
extern LWRP_EXPORT pL_VECGETPARALLELOGRAM pL_VecGetParallelogram;
extern LWRP_EXPORT pL_VECENUMVERTICES pL_VecEnumVertices;
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Camera functions.                                                    []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
extern LWRP_EXPORT pL_VECSETCAMERA pL_VecSetCamera;
extern LWRP_EXPORT pL_VECGETCAMERA pL_VecGetCamera;
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Metafile functions.                                                  []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
extern LWRP_EXPORT pL_VECCONVERTTOWMF pL_VecConvertToWMF;
extern LWRP_EXPORT pL_VECCONVERTFROMWMF pL_VecConvertFromWMF;
extern LWRP_EXPORT pL_VECCONVERTTOEMF pL_VecConvertToEMF;
extern LWRP_EXPORT pL_VECCONVERTFROMEMF pL_VecConvertFromEMF;
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Engine functions.                                                    []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
extern LWRP_EXPORT pL_VECGETENGINE pL_VecGetEngine;
extern LWRP_EXPORT pL_VECATTACHTOWINDOW pL_VecAttachToWindow;
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Marker functions.                                                    []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
extern LWRP_EXPORT pL_VECSETMARKER pL_VecSetMarker;
extern LWRP_EXPORT pL_VECGETMARKER pL_VecGetMarker;
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Unit functions.                                                      []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
/* Reserved for internal use */
extern LWRP_EXPORT pL_VECSETUNIT pL_VecSetUnit;
extern LWRP_EXPORT pL_VECGETUNIT pL_VecGetUnit;
extern LWRP_EXPORT pL_VECCONVERTPOINTTOUNITS pL_VecConvertPointToUnits;
extern LWRP_EXPORT pL_VECCONVERTPOINTFROMUNITS pL_VecConvertPointFromUnits;
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Hit test functions.                                                  []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
extern LWRP_EXPORT pL_VECSETHITTEST pL_VecSetHitTest;
extern LWRP_EXPORT pL_VECGETHITTEST pL_VecGetHitTest;
extern LWRP_EXPORT pL_VECHITTEST pL_VecHitTest;
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Polygon functions.                                                   []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
extern LWRP_EXPORT pL_VECSETPOLYGONMODE pL_VecSetPolygonMode;
extern LWRP_EXPORT pL_VECGETPOLYGONMODE pL_VecGetPolygonMode;
extern LWRP_EXPORT pL_VECSETUSELIGHTS pL_VecSetUseLights;
extern LWRP_EXPORT pL_VECGETUSELIGHTS pL_VecGetUseLights;
extern LWRP_EXPORT pL_VECSETAMBIENTCOLOR pL_VecSetAmbientColor;
extern LWRP_EXPORT pL_VECGETAMBIENTCOLOR pL_VecGetAmbientColor;
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Clipboard functions.                                                 []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
extern LWRP_EXPORT pL_VECCLIPBOARDREADY pL_VecClipboardReady;
extern LWRP_EXPORT pL_VECCOPYTOCLIPBOARD pL_VecCopyToClipboard;
extern LWRP_EXPORT pL_VECCOPYFROMCLIPBOARD pL_VecCopyFromClipboard;
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Layer functions.                                                     []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
extern LWRP_EXPORT pL_VECADDLAYER pL_VecAddLayer;
extern LWRP_EXPORT pL_VECDELETELAYER pL_VecDeleteLayer;
extern LWRP_EXPORT pL_VECEMPTYLAYER pL_VecEmptyLayer;
extern LWRP_EXPORT pL_VECCOPYLAYER pL_VecCopyLayer;
extern LWRP_EXPORT pL_VECGETLAYERBYNAME pL_VecGetLayerByName;
extern LWRP_EXPORT pL_VECGETLAYERCOUNT pL_VecGetLayerCount;
extern LWRP_EXPORT pL_VECGETLAYERBYINDEX pL_VecGetLayerByIndex;
extern LWRP_EXPORT pL_VECGETLAYER pL_VecGetLayer;
extern LWRP_EXPORT pL_VECFREELAYER pL_VecFreeLayer;
extern LWRP_EXPORT pL_VECSETLAYER pL_VecSetLayer;
extern LWRP_EXPORT pL_VECSETACTIVELAYER pL_VecSetActiveLayer;
extern LWRP_EXPORT pL_VECGETACTIVELAYER pL_VecGetActiveLayer;
extern LWRP_EXPORT pL_VECENUMLAYERS pL_VecEnumLayers;
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Group functions.                                                     []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
extern LWRP_EXPORT pL_VECADDGROUP pL_VecAddGroup;
extern LWRP_EXPORT pL_VECDELETEGROUP pL_VecDeleteGroup;
extern LWRP_EXPORT pL_VECDELETEGROUPCLONES pL_VecDeleteGroupClones;
extern LWRP_EXPORT pL_VECEMPTYGROUP pL_VecEmptyGroup;
extern LWRP_EXPORT pL_VECCOPYGROUP pL_VecCopyGroup;
extern LWRP_EXPORT pL_VECGETGROUPBYNAME pL_VecGetGroupByName;
extern LWRP_EXPORT pL_VECGETGROUPCOUNT pL_VecGetGroupCount;
extern LWRP_EXPORT pL_VECGETGROUPBYINDEX pL_VecGetGroupByIndex;
extern LWRP_EXPORT pL_VECGETGROUP pL_VecGetGroup;
extern LWRP_EXPORT pL_VECFREEGROUP pL_VecFreeGroup;
extern LWRP_EXPORT pL_VECSETGROUP pL_VecSetGroup;
extern LWRP_EXPORT pL_VECENUMGROUPS pL_VecEnumGroups;
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Object functions.                                                    []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
extern LWRP_EXPORT pL_VECINITOBJECT pL_VecInitObject;
extern LWRP_EXPORT pL_VECADDOBJECT pL_VecAddObject;
extern LWRP_EXPORT pL_VECDELETEOBJECT pL_VecDeleteObject;
extern LWRP_EXPORT pL_VECCOPYOBJECT pL_VecCopyObject;
extern LWRP_EXPORT pL_VECGETOBJECT pL_VecGetObject;
extern LWRP_EXPORT pL_VECFREEOBJECT pL_VecFreeObject;
extern LWRP_EXPORT pL_VECSETOBJECT pL_VecSetObject;
extern LWRP_EXPORT pL_VECEXPLODEOBJECT pL_VecExplodeObject;
extern LWRP_EXPORT pL_VECGETOBJECTPARALLELOGRAM pL_VecGetObjectParallelogram;
extern LWRP_EXPORT pL_VECGETOBJECTRECT pL_VecGetObjectRect;
extern LWRP_EXPORT pL_VECISOBJECTINSIDEPARALLELOGRAM pL_VecIsObjectInsideParallelogram;
extern LWRP_EXPORT pL_VECISOBJECTINSIDERECT pL_VecIsObjectInsideRect;
extern LWRP_EXPORT pL_VECSELECTOBJECT pL_VecSelectObject;
extern LWRP_EXPORT pL_VECISOBJECTSELECTED pL_VecIsObjectSelected;
extern LWRP_EXPORT pL_VECHIDEOBJECT pL_VecHideObject;
extern LWRP_EXPORT pL_VECISOBJECTHIDDEN pL_VecIsObjectHidden;
extern LWRP_EXPORT pL_VECENUMOBJECTS pL_VecEnumObjects;
extern LWRP_EXPORT pL_VECENUMOBJECTSINLAYER pL_VecEnumObjectsInLayer;
extern LWRP_EXPORT pL_VECSETOBJECTTOOLTIP pL_VecSetObjectTooltip;
extern LWRP_EXPORT pL_VECGETOBJECTTOOLTIP pL_VecGetObjectTooltip;
extern LWRP_EXPORT pL_VECSHOWOBJECTTOOLTIP pL_VecShowObjectTooltip;
extern LWRP_EXPORT pL_VECHIDEOBJECTTOOLTIP pL_VecHideObjectTooltip;
extern LWRP_EXPORT pL_VECSETOBJECTVIEWCONTEXT pL_VecSetObjectViewContext;
extern LWRP_EXPORT pL_VECGETOBJECTVIEWCONTEXT pL_VecGetObjectViewContext;
extern LWRP_EXPORT pL_VECREMOVEOBJECTVIEWCONTEXT pL_VecRemoveObjectViewContext;
extern LWRP_EXPORT pL_VECADDHYPERLINK pL_VecAddHyperlink;
extern LWRP_EXPORT pL_VECSETHYPERLINK pL_VecSetHyperlink;
extern LWRP_EXPORT pL_VECGETHYPERLINK pL_VecGetHyperlink;
extern LWRP_EXPORT pL_VECGETHYPERLINKCOUNT pL_VecGetHyperlinkCount;
extern LWRP_EXPORT pL_VECGOTOHYPERLINK pL_VecGotoHyperlink;
extern LWRP_EXPORT pL_VECSETOBJECTDESCRIPTION pL_VecSetObjectDescription;
extern LWRP_EXPORT pL_VECGETOBJECTDESCRIPTION pL_VecGetObjectDescription;
extern LWRP_EXPORT pL_VECSETOBJECTATTRIBUTES pL_VecSetObjectAttributes;
extern LWRP_EXPORT pL_VECGETOBJECTATTRIBUTES pL_VecGetObjectAttributes;
extern LWRP_EXPORT pL_VECADDOBJECTTOGROUP pL_VecAddObjectToGroup;
extern LWRP_EXPORT pL_VECENUMOBJECTSINGROUP pL_VecEnumObjectsInGroup;
/*[]-----------------------------------------------------------------------[]*/
/*[]                                                                       []*/
/*[]  Event functions.                                                     []*/
/*[]                                                                       []*/
/*[]-----------------------------------------------------------------------[]*/
extern LWRP_EXPORT pL_VECSETEVENTCALLBACK pL_VecSetEventCallback;
extern LWRP_EXPORT pL_VECEVENT pL_VecEvent;


//-----------------------------------------------------------------------------
//--LVDLG.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------
extern LWRP_EXPORT pL_VECDLGROTATE pL_VecDlgRotate;
extern LWRP_EXPORT pL_VECDLGSCALE pL_VecDlgScale;
extern LWRP_EXPORT pL_VECDLGTRANSLATE pL_VecDlgTranslate;
extern LWRP_EXPORT pL_VECDLGCAMERA pL_VecDlgCamera;
extern LWRP_EXPORT pL_VECDLGRENDER pL_VecDlgRender;
extern LWRP_EXPORT pL_VECDLGVIEWMODE pL_VecDlgViewMode;
extern LWRP_EXPORT pL_VECDLGHITTEST pL_VecDlgHitTest;
extern LWRP_EXPORT pL_VECDLGEDITALLLAYERS pL_VecDlgEditAllLayers;
extern LWRP_EXPORT pL_VECDLGNEWLAYER pL_VecDlgNewLayer;
extern LWRP_EXPORT pL_VECDLGEDITLAYER pL_VecDlgEditLayer;
extern LWRP_EXPORT pL_VECDLGEDITALLGROUPS pL_VecDlgEditAllGroups;
extern LWRP_EXPORT pL_VECDLGNEWGROUP pL_VecDlgNewGroup;
extern LWRP_EXPORT pL_VECDLGEDITGROUP pL_VecDlgEditGroup;
extern LWRP_EXPORT pL_VECDLGNEWOBJECT pL_VecDlgNewObject;
extern LWRP_EXPORT pL_VECDLGEDITOBJECT pL_VecDlgEditObject;
extern LWRP_EXPORT pL_VECDLGOBJECTATTRIBUTES pL_VecDlgObjectAttributes;
extern LWRP_EXPORT pL_VECDLGGETSTRINGLEN pL_VecDlgGetStringLen;
extern LWRP_EXPORT pL_VECDLGGETSTRING pL_VecDlgGetString;
extern LWRP_EXPORT pL_VECDLGSETSTRING pL_VecDlgSetString;
extern LWRP_EXPORT pL_VECDLGSETFONT pL_VecDlgSetFont;

//-----------------------------------------------------------------------------
//--LTBAR.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------
extern LWRP_EXPORT pL_BARCODEREAD               pL_BarCodeRead;
extern LWRP_EXPORT pL_BARCODEWRITE              pL_BarCodeWrite;
extern LWRP_EXPORT pL_BARCODEFREE               pL_BarCodeFree;
extern LWRP_EXPORT pL_BARCODEISDUPLICATED       pL_BarCodeIsDuplicated;
extern LWRP_EXPORT pL_BARCODEGETDUPLICATED      pL_BarCodeGetDuplicated;
extern LWRP_EXPORT pL_BARCODEGETFIRSTDUPLICATED pL_BarCodeGetFirstDuplicated;
extern LWRP_EXPORT pL_BARCODEGETNEXTDUPLICATED  pL_BarCodeGetNextDuplicated;
extern LWRP_EXPORT pL_BARCODEVERSIONINFO        pL_BarCodeVersionInfo;
extern LWRP_EXPORT pL_BARCODEINIT               pL_BarCodeInit;
extern LWRP_EXPORT pL_BARCODEEXIT               pL_BarCodeExit;
extern LWRP_EXPORT pL_BARCODEWRITEEXT           pL_BarCodeWriteExt;

//-----------------------------------------------------------------------------
//--LTAUT.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------


// General functions.
extern LWRP_EXPORT pL_AUTISVALID             pL_AutIsValid             ;
extern LWRP_EXPORT pL_AUTINIT                pL_AutInit                ;
extern LWRP_EXPORT pL_AUTCREATE              pL_AutCreate              ;
extern LWRP_EXPORT pL_AUTFREE                pL_AutFree                ;
extern LWRP_EXPORT pL_AUTSETUNDOLEVEL        pL_AutSetUndoLevel        ;
extern LWRP_EXPORT pL_AUTGETUNDOLEVEL        pL_AutGetUndoLevel        ;
extern LWRP_EXPORT pL_AUTCANUNDO             pL_AutCanUndo             ;
extern LWRP_EXPORT pL_AUTCANREDO             pL_AutCanRedo             ;
extern LWRP_EXPORT pL_AUTUNDO                pL_AutUndo                ;
extern LWRP_EXPORT pL_AUTREDO                pL_AutRedo                ;
extern LWRP_EXPORT pL_AUTSETUNDOENABLED      pL_AutSetUndoEnabled     ;
extern LWRP_EXPORT pL_AUTADDUNDONODE         pL_AutAddUndoNode        ;
extern LWRP_EXPORT pL_AUTSELECT              pL_AutSelect              ;
extern LWRP_EXPORT pL_AUTCLIPBOARDDATAREADY  pL_AutClipboardDataReady  ;
extern LWRP_EXPORT pL_AUTCUT                 pL_AutCut                 ;
extern LWRP_EXPORT pL_AUTCOPY                pL_AutCopy                ;
extern LWRP_EXPORT pL_AUTPASTE               pL_AutPaste               ;
extern LWRP_EXPORT pL_AUTDELETE              pL_AutDelete              ;
extern LWRP_EXPORT pL_AUTPRINT               pL_AutPrint               ;

// Container Functions.
extern LWRP_EXPORT pL_AUTADDCONTAINER        pL_AutAddContainer        ;
extern LWRP_EXPORT pL_AUTREMOVECONTAINER     pL_AutRemoveContainer     ;
extern LWRP_EXPORT pL_AUTSETACTIVECONTAINER  pL_AutSetActiveContainer  ;
extern LWRP_EXPORT pL_AUTGETACTIVECONTAINER  pL_AutGetActiveContainer  ;
extern LWRP_EXPORT pL_AUTENUMCONTAINERS      pL_AutEnumContainers      ;

// Painting Functionts.
extern LWRP_EXPORT pL_AUTSETPAINTPROPERTY   pL_AutSetPaintProperty   ;
extern LWRP_EXPORT pL_AUTGETPAINTPROPERTY   pL_AutGetPaintProperty   ;
extern LWRP_EXPORT pL_AUTSETPAINTBKCOLOR    pL_AutSetPaintBkColor    ;
extern LWRP_EXPORT pL_AUTGETPAINTBKCOLOR    pL_AutGetPaintBkColor    ;

// Vector Functions.
extern LWRP_EXPORT pL_AUTSETVECTORPROPERTY pL_AutSetVectorProperty;
extern LWRP_EXPORT pL_AUTGETVECTORPROPERTY pL_AutGetVectorProperty;
extern LWRP_EXPORT pL_AUTEDITVECTOROBJECT pL_AutEditVectorObject;

//Toolbar Functions.
extern LWRP_EXPORT pL_AUTSETTOOLBAR  pL_AutSetToolbar ;
extern LWRP_EXPORT pL_AUTGETTOOLBAR  pL_AutGetToolbar  ;

extern LWRP_EXPORT pL_AUTSETCURRENTTOOL pL_AutSetCurrentTool;
extern LWRP_EXPORT pL_AUTGETCURRENTTOOL pL_AutGetCurrentTool;



//-----------------------------------------------------------------------------
//--LTCON.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------
// general container operations funtions.
   extern LWRP_EXPORT pL_CONTAINERISVALID          pL_ContainerIsValid          ; 
   extern LWRP_EXPORT pL_CONTAINERINIT             pL_ContainerInit             ; 
   extern LWRP_EXPORT pL_CONTAINERCREATE           pL_ContainerCreate           ;
   extern LWRP_EXPORT pL_CONTAINERFREE             pL_ContainerFree             ; 
   extern LWRP_EXPORT pL_CONTAINERUPDATE           pL_ContainerUpdate           ; 
   extern LWRP_EXPORT pL_CONTAINERRESET            pL_ContainerReset            ; 
   extern LWRP_EXPORT pL_CONTAINEREDITOBJECT       pL_ContainerEditObject       ;
   
   // setting functions.
   extern LWRP_EXPORT pL_CONTAINERSETOWNER         pL_ContainerSetOwner         ;
   extern LWRP_EXPORT pL_CONTAINERSETMETRICS       pL_ContainerSetMetrics       ; 
   extern LWRP_EXPORT pL_CONTAINERSETOFFSET        pL_ContainerSetOffset        ; 
   extern LWRP_EXPORT pL_CONTAINERSETSCALAR        pL_ContainerSetScalar        ; 
   extern LWRP_EXPORT pL_CONTAINERSETOBJECTTYPE    pL_ContainerSetObjectType    ;
   extern LWRP_EXPORT pL_CONTAINERSETOBJECTCURSOR  pL_ContainerSetObjectCursor  ;
   extern LWRP_EXPORT pL_CONTAINERSETENABLED       pL_ContainerSetEnabled       ;
   extern LWRP_EXPORT pL_CONTAINERSETCALLBACK      pL_ContainerSetCallback      ;
   extern LWRP_EXPORT pL_CONTAINERSETOWNERDRAW     pL_ContainerSetOwnerDraw     ;
   
   // getting functions.
   extern LWRP_EXPORT pL_CONTAINERGETOWNER         pL_ContainerGetOwner         ;
   extern LWRP_EXPORT pL_CONTAINERGETMETRICS       pL_ContainerGetMetrics       ;
   extern LWRP_EXPORT pL_CONTAINERGETOFFSET        pL_ContainerGetOffset        ; 
   extern LWRP_EXPORT pL_CONTAINERGETSCALAR        pL_ContainerGetScalar        ;
   extern LWRP_EXPORT pL_CONTAINERGETOBJECTTYPE    pL_ContainerGetObjectType    ;
   extern LWRP_EXPORT pL_CONTAINERGETOBJECTCURSOR  pL_ContainerGetObjectCursor  ;
   extern LWRP_EXPORT pL_CONTAINERGETCALLBACK      pL_ContainerGetCallback      ;
   
   // status query functions.
   extern LWRP_EXPORT pL_CONTAINERISENABLED    pL_ContainerIsEnabled    ;
   extern LWRP_EXPORT pL_CONTAINERISOWNERDRAW  pL_ContainerIsOwnerDraw  ;
   
   extern LWRP_EXPORT pL_CONTAINERSETAUTOMATIONCALLBACK  pL_ContainerSetAutomationCallback  ;
   extern LWRP_EXPORT pL_SCREENTOCONTAINER               pL_ScreenToContainer               ;
   extern LWRP_EXPORT pL_CONTAINERTOSCREEN               pL_ContainerToScreen               ;
   extern LWRP_EXPORT pL_CONTAINERENABLEUPDATE           pL_ContainerEnableUpdate           ;

   //-----------------------------------------------------------------------------
//--LDTLB.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------
//{DOCUMENTED FUNCTIONS

   // general toolbar operations funtions.
   extern LWRP_EXPORT pL_TBISVALID          pL_TBIsValid          ; 
   extern LWRP_EXPORT pL_TBINIT             pL_TBInit             ; 
   extern LWRP_EXPORT pL_TBFREE             pL_TBFree             ; 
   extern LWRP_EXPORT pL_TBCREATE           pL_TBCreate           ;
   extern LWRP_EXPORT pL_TBFREETOOLBARINFO  pL_TBFreeToolbarInfo  ;

   // status query functions.
   extern LWRP_EXPORT pL_TBISVISIBLE        pL_TBIsVisible        ;
   extern LWRP_EXPORT pL_TBISBUTTONENABLED  pL_TBIsButtonEnabled  ;
   extern LWRP_EXPORT pL_TBISBUTTONVISIBLE  pL_TBIsButtonVisible  ;

   // setting functions.
   extern LWRP_EXPORT pL_TBSETVISIBLE        pL_TBSetVisible        ; 
   extern LWRP_EXPORT pL_TBSETPOSITION       pL_TBSetPosition       ;
   extern LWRP_EXPORT pL_TBSETROWS           pL_TBSetRows           ;
   extern LWRP_EXPORT pL_TBSETBUTTONCHECKED  pL_TBSetButtonChecked  ;
   extern LWRP_EXPORT pL_TBSETBUTTONENABLED  pL_TBSetButtonEnabled  ;
   extern LWRP_EXPORT pL_TBSETBUTTONVISIBLE  pL_TBSetButtonVisible  ;
   extern LWRP_EXPORT pL_TBSETTOOLBARINFO    pL_TBSetToolbarInfo    ;
   extern LWRP_EXPORT pL_TBSETCALLBACK       pL_TBSetCallback       ;

   // getting functions.
   extern LWRP_EXPORT pL_TBGETPOSITION       pL_TBGetPosition       ;
   extern LWRP_EXPORT pL_TBGETROWS           pL_TBGetRows           ;
   extern LWRP_EXPORT pL_TBGETBUTTONCHECKED  pL_TBGetButtonChecked  ;
   extern LWRP_EXPORT pL_TBGETTOOLBARINFO    pL_TBGetToolbarInfo    ;
   extern LWRP_EXPORT pL_TBGETCALLBACK       pL_TBGetCallback       ;

   // new functions
   extern LWRP_EXPORT pL_TBADDBUTTON pL_TBAddButton;
   extern LWRP_EXPORT pL_TBREMOVEBUTTON pL_TBRemoveButton;
   extern LWRP_EXPORT pL_TBGETBUTTONINFO pL_TBGetButtonInfo;
   extern LWRP_EXPORT pL_TBSETBUTTONINFO pL_TBSetButtonInfo;
   extern LWRP_EXPORT pL_TBSETAUTOMATIONCALLBACK  pL_TBSetAutomationCallback  ;


   //-----------------------------------------------------------------------------
   //--LTPNT.H FUNCTIONS POINTERS-------------------------------------------------
   //-----------------------------------------------------------------------------
   extern LWRP_EXPORT pL_PNTISVALID            pL_PntIsValid            ; 
   extern LWRP_EXPORT pL_PNTINIT               pL_PntInit               ; 
   extern LWRP_EXPORT pL_PNTFREE               pL_PntFree               ; 
   extern LWRP_EXPORT pL_PNTSETPROPERTY        pL_PntSetProperty        ;
   extern LWRP_EXPORT pL_PNTGETPROPERTY        pL_PntGetProperty        ;
   extern LWRP_EXPORT pL_PNTSETMETRICS         pL_PntSetMetrics         ;
   extern LWRP_EXPORT pL_PNTSETTRANSFORMATION  pL_PntSetTransformation  ;
   extern LWRP_EXPORT pL_PNTGETTRANSFORMATION  pL_PntGetTransformation  ;
   extern LWRP_EXPORT pL_PNTSETDCEXTENTS       pL_PntSetDCExtents       ; 
   extern LWRP_EXPORT pL_PNTGETDCEXTENTS       pL_PntGetDCExtents       ; 
   extern LWRP_EXPORT pL_PNTSETCLIPRGN         pL_PntSetClipRgn         ;
   extern LWRP_EXPORT pL_PNTGETCLIPRGN         pL_PntGetClipRgn         ; 
   extern LWRP_EXPORT pL_PNTOFFSETCLIPRGN      pL_PntOffsetClipRgn      ;
   
   // brush fucntions.
   extern LWRP_EXPORT pL_PNTBRUSHMOVETO  pL_PntBrushMoveTo  ; 
   extern LWRP_EXPORT pL_PNTBRUSHLINETO  pL_PntBrushLineTo  ; 
   
   // shape functions.
   extern LWRP_EXPORT pL_PNTDRAWSHAPELINE        pL_PntDrawShapeLine        ; 
   extern LWRP_EXPORT pL_PNTDRAWSHAPERECTANGLE   pL_PntDrawShapeRectangle   ; 
   extern LWRP_EXPORT pL_PNTDRAWSHAPEROUNDRECT   pL_PntDrawShapeRoundRect   ; 
   extern LWRP_EXPORT pL_PNTDRAWSHAPEELLIPSE     pL_PntDrawShapeEllipse     ; 
   extern LWRP_EXPORT pL_PNTDRAWSHAPEPOLYGON     pL_PntDrawShapePolygon     ; 
   extern LWRP_EXPORT pL_PNTDRAWSHAPEPOLYBEZIER  pL_PntDrawShapePolyBezier  ; 
   
   // region functions.
   extern LWRP_EXPORT pL_PNTREGIONRECT       pL_PntRegionRect       ; 
   extern LWRP_EXPORT pL_PNTREGIONROUNDRECT  pL_PntRegionRoundRect  ; 
   extern LWRP_EXPORT pL_PNTREGIONELLIPSE    pL_PntRegionEllipse    ; 
   extern LWRP_EXPORT pL_PNTREGIONPOLYGON    pL_PntRegionPolygon    ; 
   extern LWRP_EXPORT pL_PNTREGIONSURFACE    pL_PntRegionSurface    ; 
   extern LWRP_EXPORT pL_PNTREGIONBORDER     pL_PntRegionBorder     ; 
   extern LWRP_EXPORT pL_PNTREGIONCOLOR      pL_PntRegionColor      ; 
   extern LWRP_EXPORT pL_PNTREGIONTRANSLATE  pL_PntRegionTranslate  ; 
   extern LWRP_EXPORT pL_PNTREGIONSCALE      pL_PntRegionScale      ; 
   
   // fill functions.
   extern LWRP_EXPORT pL_PNTFILLSURFACE       pL_PntFillSurface       ; 
   extern LWRP_EXPORT pL_PNTFILLBORDER        pL_PntFillBorder        ; 
   extern LWRP_EXPORT pL_PNTFILLCOLORREPLACE  pL_PntFillColorReplace  ; 
   
   // text functions.
   extern LWRP_EXPORT pL_PNTAPPLYTEXT  pL_PntApplyText  ; 
   
   // paint helping functions.
   extern LWRP_EXPORT pL_PNTPICKCOLOR  pL_PntPickColor  ;
   
//-----------------------------------------------------------------------------
//--LTPDG.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------
   extern LWRP_EXPORT pL_PNTDLGBRUSH  pL_PntDlgBrush  ;
   extern LWRP_EXPORT pL_PNTDLGSHAPE  pL_PntDlgShape  ;
   extern LWRP_EXPORT pL_PNTDLGREGION pL_PntDlgRegion ;
   extern LWRP_EXPORT pL_PNTDLGFILL   pL_PntDlgFill   ;
   extern LWRP_EXPORT pL_PNTDLGTEXT   pL_PntDlgText   ;

//-----------------------------------------------------------------------------
//--LTSGM.H FUNCTIONS POINTERS-------------------------------------------------
//-----------------------------------------------------------------------------
   extern LWRP_EXPORT pL_MRCSTARTBITMAPSEGMENTATION pL_MrcStartBitmapSegmentation;
   extern LWRP_EXPORT pL_MRCENDBITMAPSEGMENTATION pL_MrcEndBitmapSegmentation;
   extern LWRP_EXPORT pL_MRCSEGMENTBITMAP pL_MrcSegmentBitmap;
   extern LWRP_EXPORT pL_MRCSETNEWSTRIPE pL_MrcSetNewStripe;
   extern LWRP_EXPORT pL_MRCSETSTRIPESEGMENT pL_MrcSetStripeSegment;
   extern LWRP_EXPORT pL_MRCSETSTRIPEMAXHEIGHT pL_MrcSetStripeMaxHeight;
   extern LWRP_EXPORT pL_MRCENUMSEGMENTS pL_MrcEnumSegments;
   extern LWRP_EXPORT pL_MRCUPDATESEGMENTDATA pL_MrcUpdateSegmentData;
   extern LWRP_EXPORT pL_MRCDELETESEGMENT pL_MrcDeleteSegment;
   extern LWRP_EXPORT pL_MRCSAVEBITMAP pL_MrcSaveBitmap;
   extern LWRP_EXPORT pL_MRCSAVEBITMAPT44 pL_MrcSaveBitmapT44;
   extern LWRP_EXPORT pL_MRCLOADBITMAP pL_MrcLoadBitmap;
   extern LWRP_EXPORT pL_MRCGETPAGESCOUNT pL_MrcGetPagesCount;

#endif //USE_POINTERS_TO_LEAD_FUNCTIONS

#endif //_LEAD_EXTERN_H_
/*================================================================= EOF =====*/




