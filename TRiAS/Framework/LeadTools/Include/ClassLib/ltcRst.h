/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1990, 1998 by LEAD Technologies, Inc.                         |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   :                                                                 |
| FILE NAME : ltcRst.h                                                        |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_RST_H_
#define  _LEAD_RST_H_
/*----------------------------------------------------------------------------+
| INCLUDES                                                                    |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------+
| Class     : LRasterPaint                                                    |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : March  2000                                                     |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LRasterPaint: public LBase
{
   LEAD_DECLAREOBJECT(LRasterPaint);

   private:
     pPAINTHANDLE  m_RasterPaint;

   public:
      LRasterPaint();
      ~LRasterPaint();

      L_INT       IsValid();
      L_INT       Initialize();
      L_INT       Free();
      L_INT       SetProperty(PAINTGROUP nGroup,  L_VOID *pProperty);
      L_INT       GetProperty(PAINTGROUP nGroup,  L_VOID *pProperty) ;
      L_INT       SetMetrics(HDC UserDC, pBITMAPHANDLE pBitmap, HPALETTE hRestrictionPalette);
      L_INT       SetTransformation(pPAINTXFORM pXForm);
      L_INT       GetTransformation(pPAINTXFORM pXForm) ;
      L_INT       SetDCExtents(const LPRECT prcRect);
      L_INT       GetDCExtents(LPRECT prcRect) ;
      L_INT       BrushMoveTo(HDC UserDc, L_INT nX, L_INT nY);
      L_INT       BrushLineTo(HDC UserDc, L_INT nX, L_INT nY);
      L_INT       DrawShapeLine(HDC UserDC, L_INT nXStart, L_INT nYStart, L_INT nEndX, L_INT nEndY);
      L_INT       DrawShapeRectangle(HDC UserDC,  LPRECT prcRect);
      L_INT       DrawShapeRoundRect(HDC UserDC,  LPRECT prcRect);
      L_INT       DrawShapeEllipse  (HDC UserDC,  LPRECT prcRect);
      L_INT       DrawShapePolygon(HDC UserDC,  LPPOINT pptPoints, L_INT nCount);
      L_INT       DrawShapePolyBezier(HDC UserDC,  LPPOINT pptPoints, L_INT nCount);
      // Start of New Updates
      L_INT    SetClipRgn(HRGN hClipRgn);
      L_INT    GetClipRgn(pHRGN phClipRgn);
      L_INT    OffsetClipRgn(L_INT nDX, L_INT nDY);
      L_INT    RegionRect(HDC UserDC,  LPRECT prcRect, pHRGN phDestRgn);
      L_INT    RegionRoundRect(HDC UserDC,  LPRECT prcRect, pHRGN phDestRgn);
      L_INT    RegionEllipse(HDC UserDC,  LPRECT prcRect, pHRGN phDestRgn);
      L_INT    RegionPolygon(HDC UserDC,  LPPOINT pptPoints, L_INT nCount, pHRGN phDestRgn);
      L_INT    RegionSurface(HDC UserDC,  LPPOINT pptPoint, pHRGN phDestRgn);
      L_INT    RegionBorder(HDC UserDC,  LPPOINT pptPoint,  COLORREF crBorderColor, pHRGN phDestRgn);
      L_INT    RegionColor(HDC UserDC,  COLORREF crColor, pHRGN phDestRgn);
      L_INT    RegionScale(L_INT nHScaleFactor, L_INT nVScaleFactor, PAINTALIGNMENT nAlignment, pHRGN phDestRgn);
      // End of New Updates
      L_INT       RegionTranslate(L_INT dx, L_INT dy, pHRGN phRgn);
      L_INT       FillSurface(HDC UserDC,  LPPOINT pptPoint);
      L_INT       FillBorder(HDC UserDC,  LPPOINT pptPoint,  COLORREF crBorderColor);
      L_INT       FillColorReplace(HDC UserDC,  COLORREF crColor);
      L_INT       ApplyText(HDC UserDC,  LPRECT prcRect);
      L_INT       PickColor(HDC UserDC, L_INT nX, L_INT nY, COLORREF *pcrDestColor);
};

#endif //_LEAD_PNT_H_

/*================================================================= EOF =====*/
