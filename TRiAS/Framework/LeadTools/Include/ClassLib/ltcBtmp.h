/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcbtmap.h                                                      |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_BITMAP_H_
#define  _LEAD_BITMAP_H_  


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
class LWRP_EXPORT LBitmap:public LBitmapBase
{
   LEAD_DECLAREOBJECT(LBitmap);
   LEAD_DECLARE_CLASS_MAP();

   public:
      L_VOID *m_extLBitmap;
      

private:
   //BITMAPHANDLE BitmapRegion;       //Used for Document Imaging functions
   //LBitmapBase *pBitmapRgn;      //Used for Document Imaging functions


   static L_INT EXT_CALLBACK PicturizeCS(
      pBITMAPHANDLE pCellBitmap,
      L_INT x,L_INT y,
      L_VOID L_FAR * pUserData
      );
   
   static L_INT EXT_CALLBACK SmoothCS(  
      L_UINT32       uBumpOrNick,
      L_INT32        iStartRow, 
      L_INT32        iStartCol, 
      L_INT32        iLength,
      L_UINT32       uHorV,
      L_VOID L_FAR  *pUserData
      );
   
   static L_INT EXT_CALLBACK LineRemoveCS(
      HRGN           hRgn, 
      L_INT32        iStartRow, 
      L_INT32        iStartCol, 
      L_INT32        iLength, 
      L_VOID L_FAR  *pUserData
      );
   
   static L_INT EXT_CALLBACK BorderRemoveCS(
      HRGN          hRgn, 
      L_UINT32      uBorderToRemove, 
      PRECT         pBoundingRect, 
      L_VOID L_FAR *pUserData
      );
   
   static L_INT EXT_CALLBACK InvertedTextCS(
      HRGN          hRgn, 
      PRECT         pBoundingRect, 
      L_INT32       iWhiteCount, 
      L_INT32       iBlackCount, 
      L_VOID L_FAR *pUserData
      );
   
   static L_INT EXT_CALLBACK DotRemoveCS(
      HRGN          hRgn, 
      PRECT         pBoundingRect, 
      L_INT32       iWhiteCount, 
      L_INT32       iBlackCount, 
      L_VOID L_FAR *pUserData
      );
   
   static L_INT EXT_CALLBACK HolePunchRemoveCS(
      HRGN          hRgn, 
      PRECT         pBoundingRect, 
      L_INT32       iHoleIndex,  
      L_INT32       iHoleTotalCount, 
      L_INT32       iWhiteCount, 
      L_INT32       iBlackCount, 
      L_VOID L_FAR *pUserData
      );
   
protected : 
   virtual L_INT PicturizeCallBack(
      pBITMAPHANDLE pCellBitmap,
      L_INT x,L_INT y
      );
   
   virtual L_INT SmoothCallBack(  
      L_UINT32       uBumpOrNick,
      L_INT32        iStartRow, 
      L_INT32        iStartCol, 
      L_INT32        iLength,
      L_UINT32       uHorV
      );
   
   virtual L_INT LineRemoveCallBack(
      HRGN           hRgn, 
      L_INT32        iStartRow, 
      L_INT32        iStartCol, 
      L_INT32        iLength
      );
   
   virtual L_INT BorderRemoveCallBack(
      HRGN          hRgn, 
      L_UINT32      uBorderToRemove, 
      PRECT         pBoundingRect
      );
   
   virtual L_INT InvertedTextCallBack(
      HRGN          hRgn, 
      PRECT         pBoundingRect, 
      L_INT32       iWhiteCount, 
      L_INT32       iBlackCount
      );
   
   virtual L_INT DotRemoveCallBack(
      HRGN          hRgn, 
      PRECT         pBoundingRect, 
      L_INT32       iWhiteCount, 
      L_INT32       iBlackCount
      );
   
   virtual L_INT HolePunchRemoveCallBack(
      HRGN          hRgn, 
      PRECT         pBoundingRect, 
      L_INT32       iHoleIndex,  
      L_INT32       iHoleTotalCount, 
      L_INT32       iWhiteCount, 
      L_INT32       iBlackCount
      );
   
public : 
   LBitmap();
   LBitmap(
      L_UINT      uWidth,
      L_UINT      uHeight,
      L_UINT      uBitsPerPixel=24,
      L_UINT      uOrder=ORDER_BGRORGRAY,
               LPRGBQUAD   pPalette=NULL,
               L_UINT      uViewPerspective=TOP_LEFT,
               COLORREF    crFill=0,
               L_UINT      uMemory=TYPE_CONV
             );
      LBitmap(
               BITMAPINFO L_FAR *pInfo,
               L_UCHAR L_FAR *  pBits
             );
      LBitmap(
               HDC hDC,
               HBITMAP hBitmap,
               HPALETTE hPalette
             );
      LBitmap(pBITMAPHANDLE pBitmapHandle);

      virtual ~LBitmap();
      LBitmap(LBitmap& LBitmapSrc);
      LBitmap&      operator =(LBitmap& LBitmapSrc); 

      virtual L_INT HalfTone(L_UINT uType, L_INT32 nAngle, L_UINT uDim);
      virtual L_INT AddNoise(L_UINT uRange=500,L_UINT uChannel=CHANNEL_MASTER);
      virtual L_INT AutoTrim(L_INT uThreshold=0); 
      virtual L_INT AverageFilter(L_UINT uDim=3);
      virtual L_INT BinaryFilter(LPBINARYFLT pFilter);
      virtual L_INT ChangeContrast(L_INT nChange);
      virtual L_INT ChangeHue(L_INT nAngle); 
      virtual L_INT ChangeIntensity(L_INT nChange);
      virtual L_INT ChangeSaturation(L_INT nChange);
      virtual L_INT ColorMerge(LBitmap L_FAR* pLBitmaps,L_UINT32  uFlags);
      virtual L_INT ColorSeparate(LBitmap L_FAR* pLBitmaps,L_UINT32 uFlags);
      virtual L_INT Deskew(L_INT32 L_FAR* pnAngle=NULL); 
      virtual L_INT Despeckle(); 
      
      virtual L_INT Smooth(LPSMOOTH pSmooth);
      virtual L_INT LineRemove(LPLINEREMOVE pLineRemove);
      virtual L_INT BorderRemove(LPBORDERREMOVE pBorderRemove);
      virtual L_INT InvertedText(LPINVERTEDTEXT pInvertedText);
      virtual L_INT DotRemove(LPDOTREMOVE pDotRemove);
      virtual L_INT HolePunchRemove(LPHOLEPUNCH pHolePunchRemove);
      
      virtual L_INT Emboss(L_UINT uDirection=EMBOSS_N,L_UINT uDepth=500);
      virtual L_INT GammaCorrect(L_UINT uGamma);
      virtual L_INT GetAutoTrimRect(L_UINT uThreshold,LPRECT pRect);
      virtual L_INT GetHistogram(L_UINT32 * pHisto, L_UINT uHistoLen, L_UINT uChannel);
      virtual L_INT Invert();    
      virtual L_INT HistoContrast(L_INT nChange);
      virtual L_INT IntensityDetect(L_UINT uLow,L_UINT uHigh);
      virtual L_INT MaxFilter(L_UINT uDim=3); 
      virtual L_INT MedianFilter(L_UINT uDim=3);
      virtual L_INT MinFilter(L_UINT uDim=3);
      virtual L_INT Oilify(L_UINT uDim=4);
      virtual L_INT Posterize(L_UINT uLevels=4);
      virtual L_INT Solarize(L_UINT uThreshold);
      virtual L_INT SpatialFilter(LPSPATIALFLT pFilter);
      virtual L_INT StretchIntensity(); 
      virtual L_INT GetMinMaxBits(L_INT L_FAR* pnLowBit,L_INT L_FAR* pnHighBit);
      virtual L_INT GetMinMaxVal(L_UINT L_FAR* puMinVal,L_UINT L_FAR* puMaxVal);
      
      virtual L_INT RemapIntensity(L_UINT * pLUT, L_UINT uLUTLen, L_UINT uChannel);
      
      virtual L_INT Mosaic(L_UINT uDim=3);
      virtual L_INT Sharpen(L_INT nSharpness);
      virtual L_INT Picturize(
                              L_CHAR L_FAR * pszDirName,
                              L_UINT uFlags,
                              L_INT nCellWidth,
                              L_INT nCellHeight
                             );
      virtual L_INT WindowLevel(
                                 L_INT nLowBit,
                                 L_INT nHighBit,
                                 RGBQUAD L_HUGE *pLUT,
                                 L_UINT uLUTLength,
                                 L_UINT uFlags
                               );
      virtual L_INT WindowLevelBitmap(
                                       L_INT nLowBit,
                                       L_INT nHighBit,
                                       RGBQUAD L_HUGE *pLUT,
                                       L_UINT uLUTLength,
                                       L_INT nOrderDst
                                     );

      static L_INT WindowLevelFillLUT(RGBQUAD L_HUGE* pLUT,
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

      virtual L_INT ContourFilter(
                                   L_INT16 nThreshold,
                                   L_INT16 nDeltaDirection,
                                   L_INT16 nMaximumError,
                                   L_INT nOption
                                   );

      virtual L_INT GaussianFilter(L_INT nRadius);
      
      virtual L_INT UnsharpMask(L_INT nAmount, L_INT nRadius, L_INT nThreshold, L_UINT uColorType);

      virtual L_INT GrayScaleExt(L_INT RedFact, L_INT GreenFact, L_INT BlueFact);

      virtual L_INT ConvertToColoredGray(L_INT RedFact, L_INT GreenFact, L_INT BlueFact, L_INT RedGrayFact, L_INT GreenGrayFact, L_INT BlueGrayFact);

      virtual L_INT BalanceColors(BALANCING * pRedFact, BALANCING * pGreenFact, BALANCING * pBlueFact);

      virtual L_INT SwapColors(L_INT nFlags);

      virtual L_INT LineProfile(POINT FirstPoint, POINT SecondPoint, L_UINT ** ppRed, L_UINT ** ppGreen, L_UINT ** ppBlue);

      virtual L_INT HistoEqualize(L_INT nFlag);

      virtual L_INT AntiAlias(L_UINT uThreshold, L_UINT uDim, L_UINT uFilter);

      virtual L_INT EdgeDetector(L_UINT uThreshold, L_UINT uFilter);

      virtual L_INT RemoveRedEye(COLORREF rcNewColor, L_UINT uThreshold, L_INT nLightness);

      virtual L_INT MotionBlur(L_UINT uDim, L_INT nAngle, L_BOOL bUnidirectional);

      virtual L_INT PicturizeList(L_UINT uxDim, L_UINT uyDim, L_UINT uLightnessFact,
                                  LBitmapList * pBitmapList);

      virtual L_INT PicturizeSingle(LBitmapBase * pThumbBitmap,
                                    L_UINT uxDim, L_UINT uyDim,
                                    L_UINT uGammaFact);

      virtual L_INT GetFunctionalLookupTable(L_UINT * pLookupTable, L_UINT uLookupLen,
                                             L_UINT uStart, L_UINT uEnd,
                                             L_INT nFactor, L_UINT uFlag);

      virtual L_INT GetUserLookupTable(L_UINT * pLookupTable, L_UINT uLookupLen,
                                       POINT * apUserPoint, L_UINT uUserPointCount,
                                       L_UINT * puPointCount);

      virtual L_INT AddBorder(LPADDBORDERINFO pAddBorderInfo);

      virtual L_INT AddFrame(LPADDFRAMEINFO pAddFrameInfo);
      
      //Used for Document Imaging functions
      //virtual L_INT LBitmap::GetDocImageRgn(LBitmapBase *pDocImageRgn);

};

#endif //_LEAD_BITMAP_H_
/*================================================================= EOF =====*/



