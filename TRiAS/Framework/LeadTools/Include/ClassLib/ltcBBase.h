/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcbtmap.h                                                      |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_BITMAP_BASE_H_
#define  _LEAD_BITMAP_BASE_H_

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LBitmap                                                         |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : 27 may 1998                                                     |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LBitmapBase:public LBase
{
   LEAD_DECLAREOBJECT(LBitmapBase);
   LEAD_DECLARE_CLASS_MAP();

   friend class LPaint;
   friend class LBitmapList;
   friend class LPaintEffect;
   friend class LBitmapDictionary;
   
   friend LWRP_EXPORT LBase L_FAR* LEAD_GetObject(LWRAPPEROBJECTTYPE nType,LBase L_FAR* This,LPLEADCREATEOBJECT pCreateObj);

   public:
      L_VOID *m_extLBitmapBase;
      
   private:
      LFile          L_FAR*         m_pLFile;                                
      LIsis          L_FAR*         m_pLIsis;                                
      LTwain         L_FAR*         m_pLTwain;                               
      LPrint         L_FAR*         m_pLPrint;                               
      LPaint         L_FAR*         m_pLPaint;                               
      LDialog        L_FAR*         m_pLDialog;                              
      LBitmapRgn     L_FAR*         m_pLBitmapRgn;                           
      LMemoryFile    L_FAR*         m_pLMemoryFile;                          
      LPaintEffect   L_FAR*         m_pLPaintEffect;                         
      LScreenCapture L_FAR*         m_pLScreenCapture;                         
      LBarCode       L_FAR*         m_pLBarCode;

      L_BOOL                        m_bAccessExist;
      L_BOOL                        m_bDitherStarted;

      L_BOOL                        m_bLocalSettingsEnabled;
      BITMAPSETTINGS                m_LocalSettings;
      BITMAPSETTINGS                m_GlobalSettings;

      L_BOOL                        m_bNotifyOnChange;
      L_BOOL                        m_bAlwaysEndNotification;

      L_BOOL                        m_bRedirectStatusCallBack;

      L_INT32                       m_nRotateAngle;     
      L_BOOL                        m_bRotateResize;   
      ANNPOINT                      m_imageOldCenter;
      L_BOOL                        m_bIsShallowCopy;


   protected:  
      LBitmapList L_FAR*            m_pBitmapList;
      L_INT                         m_BitmapListItemIndex;
      L_BOOL                        m_bBitmapListLocked;

      L_CHAR                        m_szFileName[MAX_PATH+1];
      L_BOOL                        m_bEnableFileName;

      BITMAPHANDLE                  m_BitmapHandle;
      pBITMAPHANDLE                 m_pBitmapHandle;
      HPALETTE                      m_hBitmapPalette;

      RECT                          m_rcSrc;
      RECT                          m_rcClipSrc;
      RECT                          m_rcDst;
      RECT                          m_rcClipDst;

    private:  
      L_VOID InitializeClass();
      static L_INT  EXT_CALLBACK ColorResBitmapCS(
                                       pBITMAPHANDLE pBitmap,  
                                       L_UCHAR L_FAR * pBuffer,
                                       L_INT nLines, 
                                       L_VOID L_FAR * pUserData
                                     );

      L_INT          LockBitmapList(L_BOOL bLock);
      L_VOID         SetRotateParams(L_INT32 nAngle, L_BOOL bResize, pANNPOINT pOldCenter);


   protected : 
      virtual L_INT  ColorResBitmapCallBack(
                                       pBITMAPHANDLE pBitmap,
                                       L_UCHAR L_FAR * pBuffer,
                                       L_INT nLines
                                     );

      L_VOID         SetLocalSettings();
      L_VOID         RestoreGlobalSettings();
      L_VOID         GetRotateParams( L_INT32 * nAngle, L_BOOL *bResize, pANNPOINT pOldCenter);


   public : 
      LBitmapBase();
      LBitmapBase(
                  L_UINT         uWidth,
                  L_UINT         uHeight,
                  L_UINT         uBitsPerPixel=24,
                  L_UINT         uOrder=ORDER_BGRORGRAY,
                  LPRGBQUAD      pPalette=NULL,
                  L_UINT         uViewPerspective=TOP_LEFT,
                  COLORREF       crFill=0,
                  L_UINT         uMemory=TYPE_CONV,
                  L_UCHAR L_FAR* pData=NULL,
                  L_UINT32       dwSize=0
                 );
      LBitmapBase(
                  BITMAPINFO L_FAR *pInfo,
                  L_UCHAR L_FAR *  pBits
                 );
      LBitmapBase(
                  HDC hDC,
                  HBITMAP hBitmap,
                  HPALETTE hPalette
                 );
      LBitmapBase(pBITMAPHANDLE pBitmapHandle);

      virtual ~LBitmapBase();

      pBITMAPHANDLE        GetHandle(); 
      L_INT                SetHandle(pBITMAPHANDLE pBitmapHandle,L_BOOL bFreePrev=TRUE);

      L_INT                GetWidth();
      L_INT                GetHeight();
      L_UINT32             GetMemSize();
      L_BOOL               IsAllocated();
      L_INT                GetColorOrder();
      L_INT                GetXResolution();
      L_INT                GetYResolution();
      L_VOID               SetXResolution(L_INT nXRes);
      L_VOID               SetYResolution(L_INT nYRes);
      L_BOOL               IsMemoryLocked();
      L_INT                GetBitsPerPixel();
      L_INT                GetBytesPerLine();
      L_BOOL               Is1BitCompressed();
      L_BOOL               IsUsingDiskMemory();
      L_INT                GetViewPerspective();
      L_VOID               SetViewPerspective(L_INT nViewPerspective);
      L_BOOL               IsUsingConventionalMemory();
      L_BOOL               IsProgressive();
      L_BOOL               IsPlayBackWaitUserInput();
      L_BOOL               EnablePlayBackWaitUserInput(L_BOOL bEnable);
      L_BOOL               IsPlayBackTransparencyEnabled();
      L_BOOL               EnablePlayBackTransparency(L_BOOL bEnable);
      L_VOID               SetPlayBackTransparentColor(COLORREF crTransparent);
      COLORREF             GetPlayBackTransparentColor();
      L_BOOL               IsPixelsSigned();
      L_UINT               GetDitheringMethod();
      L_VOID               SetDitheringMethod(L_UINT uDitheringMethod);
      L_INT                GetPlayBackLeft();
      L_VOID               SetPlayBackLeft(L_INT nLeft);
      L_INT                GetPlayBackTop();
      L_VOID               SetPlayBackTop(L_INT nTop);
      L_UINT               GetPlayBackDisposalMethod();
      L_VOID               SetPlayBackDisposalMethod(L_UINT uMethod);
      COLORREF             GetPlayBackBackGroundColor();
      L_VOID               SetPlayBackBackGroundColor(COLORREF crBackGround);
      L_VOID               SetPlayBackDelay(L_UINT32 uDelay);
      L_UINT32             GetPlayBackDelay();
      L_BOOL               IsInterlaced();
      L_BOOL               IsSuperCompressed();

      HPALETTE             GetPalette();
      L_VOID               SetPalette(HPALETTE hPalette);
      
      L_INT                GetFileName(L_CHAR L_FAR* pszBuffer,L_UINT L_FAR* puBuffSize);
      L_VOID               SetFileName(L_CHAR L_FAR* pszFileName);
      L_BOOL               IsFileNameEnabled();
      L_BOOL               EnableFileName(L_BOOL bEnableFileName);

      L_BOOL               IsBitmapListLocked();

      LBitmapBase&         operator=(LBitmapBase& LBitmapSrc); 

      L_UINT               GetDefaultDithering();
      L_INT                SetDefaultDithering(L_UINT uMethod);
      L_INT                GetPaintContrast();
      L_INT                SetPaintContrast(L_INT nValue);
      L_UINT               GetPaintGamma();
      L_INT                SetPaintGamma(L_UINT uValue); 
      L_INT                GetPaintIntensity();
      L_INT                SetPaintIntensity(L_INT nValue);
      L_UINT32             GetDisplayMode();
      L_INT                SetDisplayMode(
                                          L_UINT32 uFlagPos,
                                          L_UINT32 uFlagSet
                                         );
      L_BOOL               EnableLocalSettings(L_BOOL bEnable);
      L_BOOL               IsLocalSettingsEnabled();

      virtual L_VOID       GetRects(LPRECT prcSrc,LPRECT prcClipSrc,LPRECT prcDst,LPRECT prcClipDst);
      virtual L_INT        SetSrcRect(LPRECT prcSrc);
      virtual L_INT        SetClipSrcRect(LPRECT prcClipSrc);
      virtual L_INT        SetDstRect(LPRECT prcDst);
      virtual L_INT        SetClipDstRect(LPRECT prcClipDst);

      virtual L_INT        StartChanging(L_UINT nChangeType,L_UINT nChangeCategory);
      virtual L_VOID       EndChanging(L_UINT nChangeType,L_UINT nChangeCategory,L_INT nRetCode);
      virtual L_BOOL       EnableChangeNotification(L_BOOL bEnable=TRUE);
      virtual L_BOOL       IsChangeNotificationEnabled();
      virtual L_BOOL       EnableAlwaysEndNotification(L_BOOL bEnable=TRUE);
      virtual L_BOOL       IsAlwaysEndNotification();

      virtual L_BOOL       EnableRedirectStatusCallBack(L_BOOL bEnable=TRUE);
      virtual L_BOOL       IsRedirectStatusCallBackEnabled();

      virtual L_INT        Free();
      virtual L_INT        Access();
      virtual L_INT        Release();
      virtual L_INT        Allocate(L_INT nMemoryType=TYPE_CONV);
      virtual L_INT        ChangeHeight(L_INT nHeight);  
      virtual L_INT        Clear();
      virtual L_INT        Combine(
                                    LBitmapBase L_FAR* pLBitmapSrc,
                                    L_INT nWidth,
                                    L_INT nHeight,
                                    L_INT nXDst=0,
                                    L_INT nYDst=0,
                                    L_INT nXSrc=0,
                                    L_INT nYSrc=0,
                                    L_UINT32 uFlags=CB_OP_ADD|CB_DST_0
                                  );
      virtual L_INT        Copy(LBitmapBase& LBitmapSrc);     
      virtual L_INT        CopyData(LBitmapBase& LBitmapSrc);
      virtual L_INT        CopyHandle(LBitmapBase& LBitmapSrc);
      virtual L_INT        CopyRect(
                                       LBitmapBase& LBitmapSrc,
                                      L_INT           nCol,
                                      L_INT           nRow,
                                      L_UINT          uWidth,
                                      L_UINT          uHeight
                                   );
      virtual L_INT        CopyRect(
                                       LBitmapBase& LBitmapSrc,
                                       RECT&    rect
                                   );
      virtual L_INT        Create(
                                    L_UINT         uWidth=100,
                                    L_UINT         uHeight=100,
                                    L_UINT         uBitsPerPixel=24,
                                    L_UINT         uOrder=ORDER_BGRORGRAY,
                                    LPRGBQUAD      pPalette=NULL,
                                    L_UINT         uViewPerspective=TOP_LEFT,
                                    L_UINT         uMemory=TYPE_CONV,
                                    L_UCHAR L_FAR* pData=NULL,
                                    L_UINT32       dwSize=0
                                 );

      virtual L_INT        SetDataPointer( L_UCHAR L_FAR*pData, 
                                           L_UINT32 dwSize);

      virtual L_INT        ToggleCompression();


      virtual L_INT        CreateAlphaBitmap(LBitmapBase& LBitmapSrc); 
      virtual L_INT        GetColors(
                                       L_INT nIndex,
                                       L_INT nCount,
                                       LPRGBQUAD pPalette
                                    );
      virtual L_INT32      GetRow(
                                    LBuffer L_FAR* pLBuffer,
                                    L_INT nRow
                                 );
      virtual L_INT32      GetRowCol(
                                       LBuffer L_FAR* pLBuffer,
                                       L_INT nRow,
                                       L_INT nCol
                                    );
      virtual L_INT32      GetRowColCompressed(
                                                LBuffer L_FAR* pLRunBuffer,
                                                L_INT nRow,
                                                L_INT nCol,
                                                L_UINT32 uWidth,
                                                LBuffer L_FAR* pWorkBuffer=NULL
                                              );
      virtual L_INT        GetRowCompressed(
                                             LBuffer L_FAR*  pLRunBuffer,
                                             L_INT  nRow,
                                             L_INT  nLines=1,
                                             LBuffer L_FAR* pWorkBuffer=NULL
                                           );
      virtual L_INT32      PutRow(
                                    LBuffer& LBuff,
                                    L_INT nRow
                                 );
      virtual L_INT32      PutRowCol(
                                       LBuffer& LBuff,
                                       L_INT nRow,
                                       L_INT nCol
                                    );
      virtual L_INT        PutRowCompressed(
                                             LBuffer& LRunBuffer,
                                             L_INT nRow,
                                             L_INT nLines=1,
                                             LBuffer L_FAR* pWorkBuffer=NULL
                                           );
      virtual L_INT32      PutRowColCompressed(
                                                LBuffer& LRunBuffer,
                                                L_INT nRow,
                                                L_INT nCol,
                                                L_UINT32  uWidth,
                                                LBuffer L_FAR* pWorkBuffer=NULL
                                              );
      virtual COLORREF     GetPixelColor(
                                          L_INT nRow,
                                          L_INT nCol
                                        );
      virtual L_INT        GrayScale(L_INT nBitsPerPixel=8); 
      virtual L_INT        Initialize(
                                       L_INT nWidth=0,
                                       L_INT nHeight=0,
                                       L_INT nBitsPerPixel=0
                                     );
      virtual L_INT        IsGrayScale();   
      virtual L_INT        PointFromBitmap(
                                             L_INT nViewPerspective,
                                             L_INT L_FAR* px,
                                             L_INT L_FAR* py
                                          );
      virtual L_INT        PointToBitmap(
                                          L_INT nViewPerspective,
                                          L_INT L_FAR* px,
                                          L_INT L_FAR* py
                                        );
      virtual L_INT        PutColors(
                                       L_INT nIndex,
                                       L_INT nCount,
                                       LPRGBQUAD pPalette
                                    );
      virtual L_INT        PutPixelColor(
                                          L_INT  nRow,
                                          L_INT  nCol,
                                          COLORREF  crColor
                                        );

      virtual L_INT        RectFromBitmap(
                                          L_INT nViewPerspective,
                                          LPRECT pRect
                                         );
      virtual L_INT        RectToBitmap(
                                          L_INT nViewPerspective,
                                          LPRECT pRect
                                       );
      virtual L_INT        SetAlpha(LBitmapBase& LBitmapAlpha);
      virtual L_INT        Size(
                                 L_INT nWidth,
                                 L_INT nHeight,
                                 L_UINT32 uFlags=SIZE_NORMAL
                               );
      virtual L_INT        StartDithering(
                                          LPRGBQUAD pPalette,
                                          L_UINT uColors
                                         );
      virtual L_INT        DitherLine(
                                       LBuffer L_FAR* pLBufferSrc,
                                       LBuffer L_FAR* pLBufferDst
                                     );
      virtual L_INT        StopDithering();  
      virtual COLORREF     TranslateColor(
                                          LBitmapBase& LBitmapSrc,
                                          COLORREF crColor
                                         );
      virtual L_INT        Trim(
                                 L_INT nCol,
                                 L_INT nRow,
                                 L_UINT uWidth,
                                 L_UINT uHeight
                               );
      virtual L_INT        Trim(LPRECT prcTrim);
      virtual L_BOOL       HasRgn();        
      virtual L_INT        GetColorCount(L_UINT32 L_FAR* puCount);
      virtual L_INT        Resize(LBitmapBase L_FAR* pLBitmapDst);
      virtual L_INT        ConvertFromDIB(
                                          BITMAPINFO L_FAR *pInfo,
                                          L_UCHAR L_FAR *  pBits
                                         );
      virtual HGLOBAL      ConvertToDIB();
      virtual HBITMAP      ConvertToDDB(HDC hDC);
      virtual L_INT        ConvertFromDDB(
                                          HDC hDC,
                                          HBITMAP hBitmap,
                                          HPALETTE hPalette
                                         );
      virtual L_INT        ColorRes(
                                    LBitmapBase& BitmapSrc,
                                    L_INT  nBitsPerPixel,
                                    L_UINT32 uFlags=CRF_FIXEDPALETTE|CRF_FLOYDSTEINDITHERING,
                                    LPRGBQUAD pPalette=NULL,
                                    HPALETTE hPalette=NULL,
                                    L_UINT uColors=0
                                   );
      virtual L_INT        ColorRes(
                                    L_INT  nBitsPerPixel,
                                    L_UINT32 uFlags=CRF_FIXEDPALETTE|CRF_FLOYDSTEINDITHERING,
                                    LPRGBQUAD pPalette=NULL,
                                    HPALETTE hPalette=NULL,
                                    L_UINT uColors=0
                                   );
      virtual L_INT        ChangeViewPerspective(
                                                   LBitmapBase& LBitmapSrc,
                                                   L_INT nViewPerspective
                                                );
      virtual L_INT        ChangeViewPerspective(L_INT nViewPerspective);
      virtual L_BOOL       IsClipboardReady();  
      virtual L_INT        CopyFromClipboard(HWND hWnd); 
      virtual L_INT        CopyToClipboard(HWND hWnd,L_UINT uFlags=COPY2CB_EMPTY|COPY2CB_DIB|COPY2CB_DDB|COPY2CB_PALETTE);
      virtual HPALETTE     DupPalette(HPALETTE hPalette=0);
      virtual L_INT        GetFixedPalette(
                                             LPRGBQUAD pPalette,
                                             L_INT nBitsPerPixel
                                          );
      virtual HPALETTE     CreatePaintPalette(HDC hDC);
      virtual HDC          CreateLeadDC();
      virtual L_BOOL       DeleteLeadDC(HDC hDC);
      virtual L_INT        Load(
                                L_INT nBitsPerPixel=0,
                                L_INT nOrder=ORDER_BGRORGRAY,
                                pLOADFILEOPTION pLoadFileOption=NULL,
                                pFILEINFO = NULL
                                );
      virtual L_INT        Load(
                                L_INT nBitsPerPixel,
                                L_INT nOrder,
                                L_INT nPage,
                                pFILEINFO = NULL
                                );
      virtual L_INT        Load(L_CHAR L_FAR *pszFileName, 
                                L_INT nBitsPerPixel=0,
                                L_INT nOrder=ORDER_BGRORGRAY,
                                pLOADFILEOPTION pLoadFileOption=NULL,
                                pFILEINFO = NULL
                                );
      virtual L_INT        Load(L_CHAR L_FAR *pszFileName, 
                                L_INT nBitsPerPixel,
                                L_INT nOrder,
                                L_INT nPage,
                                pFILEINFO = NULL
                                );

      virtual L_INT        LoadResize(L_INT nDestWidth,
                                      L_INT nDestHeight,
                                      L_INT nDestBits,
                                      L_UINT32 uFlags,
                                      L_INT nOrder,
                                      pLOADFILEOPTION pLoadOptions,
                                      pFILEINFO pFileInfo);

      virtual L_INT        LoadResize(L_CHAR * pszFile,
                                      L_INT nDestWidth,
                                      L_INT nDestHeight,
                                      L_INT nDestBits,
                                      L_UINT32 uFlags,
                                      L_INT nOrder,
                                      pLOADFILEOPTION pLoadOptions,
                                      pFILEINFO pFileInfo);

      virtual L_INT        Save(//Save(yes file name, no page number)
                           L_CHAR L_FAR * pszFile,
                           L_INT nFormat,
                           L_INT nBitsPerPixel,
                           L_INT nQFactor,
                           L_UINT uFlags=SAVE_OVERWRITE,
                           pSAVEFILEOPTION pSaveFileOption=NULL
                               );
      virtual L_INT        Save(//Save(yes file name, yes nPageNumber)
                           L_CHAR L_FAR * pszFile,
                           L_INT nFormat,
                           L_INT nBitsPerPixel,
                           L_INT nQFactor,
                           L_INT nPageNumber,
                           L_UINT uFlags
                               );
      virtual L_INT        Save(//Save(no file name, no page number)
                           L_INT nFormat,
                           L_INT nBitsPerPixel,
                           L_INT nQFactor,
                           L_UINT uFlags=SAVE_OVERWRITE,
                           pSAVEFILEOPTION pSaveFileOption=NULL
                               );
      virtual L_INT        Save(//Save(no file name, yes page number)
                           L_INT nFormat,
                           L_INT nBitsPerPixel,
                           L_INT nQFactor,
                           L_INT nPageNumber,
                           L_UINT uFlags
                               );
      virtual L_INT        Fill(COLORREF crFill=0); 
      virtual L_INT        Flip();                
      virtual L_INT        Reverse();        
      virtual L_INT        Rotate(L_INT nAngle, L_UINT uFlags=ROTATE_RESIZE, COLORREF crFill=0);
      virtual L_INT        Shear(
                                 L_INT nAngle,
                                 L_BOOL bHorizontal=TRUE,
                                 COLORREF crFill=0
                                );
      virtual L_INT        Underlay(
                                       LBitmapBase& LUnderlayBmp,
                                       L_UINT uFlags=UB_TILE
                                   );
      virtual L_INT        RotateViewPerspective(L_INT nAngle);
      virtual L_INT        ClearNegativePixels();

      virtual L_INT        Add(LBitmapList * pBitmapList, L_UINT uFlag = BC_ADD);
      
      virtual L_INT        AlphaBlend(L_INT nXDst, L_INT nYDst, 
                                      L_INT nWidth, L_INT nHeight, 
                                      LBitmapBase * pBitmapSrc, 
                                      L_INT nXSrc, L_INT nYSrc, 
                                      L_INT nOpacity);
      
      virtual L_INT        CreateFadedMask(LBitmapBase * pMaskBitmap,
                                           L_INT nLength,
                                           L_INT nFadeRate,
                                           L_INT nStepSize,
                                           L_INT nInflate,
                                           L_UINT uFlag,
                                           L_INT nMaxGray,
                                           COLORREF crTransparent);

      virtual L_INT        FeatherAlphaBlend(L_INT nXDst, L_INT nYDst,
                                             L_INT nWidth, L_INT nHeight,
                                             LBitmapBase * pBitmapSrc,
                                             L_INT nXSrc, L_INT nYSrc,
                                             LBitmapBase * pBitmapMsk);

      virtual L_INT        CombineExt(LBitmapBase * pBitmapSrc,
                                      L_INT nWidth, L_INT nHeight,
                                      L_INT nXDst, L_INT nYDst,
                                      L_INT nXSrc, L_INT nYSrc, L_UINT uFlag);

      virtual L_INT        GetPixelData(L_VOID * pData, L_INT nRow, L_INT nCol, L_INT nBytes);

      virtual L_INT        PutPixelData(L_VOID * pData, L_INT nRow, L_INT nCol, L_INT nBytes);

      virtual L_INT        ConvertSignedToUnsigned(L_UINT uShift);

      virtual L_INT        ChangeCompression(L_INT nComp);

      virtual L_INT        CombineBitmapWarp(POINT        nDst[],
                                             LBitmapBase* pBitmapSrc,
                                             POINT        nSrc,
                                             L_INT        nSrcWidth,
                                             L_INT        nSrcHeight,
                                             L_UINT       uFlags);
      /* v12 
      virtual L_INT        FlipViewPerspective();
      virtual L_INT        ReverseViewPerspective();
      virtual L_INT        ConvertFromEMF(HBITMAP  hBitmap,HENHMETAFILE hEMF, L_UINT uWidth, L_UINT uHeight);
      virtual L_INT        ConvertFromWMF(HBITMAP  hBitmap,HMETAFILE hWMF, L_UINT uWidth, L_UINT uHeight);
      virtual HENHMETAFILE ConvertToEMF();
      virtual HMETAFILE    ConvertToWMF();
      */
            
};

#endif //_LEAD_BITMAP_BASE_H_
/*================================================================= EOF =====*/
