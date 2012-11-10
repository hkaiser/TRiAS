/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcdraw.h                                                       |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_DRAW_H_
#define  _LEAD_DRAW_H_

/*----------------------------------------------------------------------------+
| INCLUDES                                                                    |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LDraw                                                           |
| Desc      :                                                                 |
| Return    :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September 1998                                                  |
+----------------------------------------------------------------------------*/
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
class LWRP_EXPORT LDraw : public LBase 
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
   LEAD_DECLAREOBJECT(LDraw);

   public:
      L_VOID *m_extLDraw;
   
   protected: 
      LBitmapBase L_FAR*   m_pBitmap;      
      HDC                  m_hDC;
   public :
      LDraw();
      virtual ~LDraw();

      HDC     SetDC(HDC hDC);
      HDC     GetDC();
      L_VOID  SetBitmap(LBitmapBase L_FAR* pBitmap);
      L_BOOL  IsValid();
};

/*----------------------------------------------------------------------------+
| Class     : LPaint                                                          |
| Desc      :                                                                 |
| Return    :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September 1998                                                  |
+----------------------------------------------------------------------------*/
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
class LWRP_EXPORT LPaint: public LDraw  
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
      LEAD_DECLAREOBJECT(LPaint);

   public:
      L_VOID *m_extLPaint;
      
   
   public : 
      LPaint();
      LPaint(LBitmapBase L_FAR* pBitmap,HDC hDC);
      virtual ~LPaint();

      virtual  L_INT FrameRgn(L_UINT  uType,       pRGNXFORM pXForm=NULL);   
      virtual  L_INT ColorRgn(COLORREF crRgnColor, pRGNXFORM pXForm=NULL);   
      virtual  L_INT PaintDCBuffer(LBuffer& LBuff,L_INT nRow,L_INT nCount=1,L_UINT32 uROP3=SRCCOPY);  
      virtual  L_INT PaintDC(L_UINT32 uROP3=SRCCOPY);    
      virtual  L_INT PaintRgnDC(L_UINT32 uROP3=SRCCOPY); 
      virtual  L_INT PaintRgnDCBuffer(LBuffer& LBuff,L_INT nRow,L_INT nCount=1,L_UINT32 uROP3=SRCCOPY);  
};

/*----------------------------------------------------------------------------+
| Class     : LPaintEffect                                                    |
| Desc      :                                                                 |
| Return    :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September 1998                                                  |
+----------------------------------------------------------------------------*/
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
class LWRP_EXPORT LPaintEffect: public LDraw  
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
   LEAD_DECLAREOBJECT(LPaintEffect);

   public:
      L_VOID *m_extLPaintEffect;
      
   private:
      HBITMAP              hbmMem;
      HDC                  GetBackDC();
      L_VOID               ReleaseBackDC(HDC hdcBack);
      L_INT                Draw3dShape(LPRECT pRect, L_UINT uShape, HRGN hRgn);
      L_VOID               InitializeClass();

   protected:
      LBitmapBase L_FAR*   m_pBackBitmap /*=NULL*/;
      RECT                 m_rcBack;
      L_UINT               m_uFrameWidth;
      L_UINT               m_uInnerWidth;
      L_UINT               m_uOuterWidth;
      COLORREF             m_crFrame;
      COLORREF             m_crInnerShadow;
      COLORREF             m_crInnerHilite;
      COLORREF             m_crOuterShadow;
      COLORREF             m_crOuterHilite;
      COLORREF             m_crFill;
      COLORREF             m_crBack;
      GRADDLGPARM          m_GradDlgParm;
      SHAPEDLGPARM         m_ShapeDlgParm;
      TEXTDLGPARM          m_TextDlgParm;
      TRANSDLGPARM         m_TransDlgParm;
      EFXDLGPARM           m_EfxDlgParm;
      
   public:
      LPaintEffect();
      LPaintEffect(LPGRADDLGPARM  pGradDlgParm);
      LPaintEffect(LPSHAPEDLGPARM pShapeDlgParm);
      LPaintEffect(LPTEXTDLGPARM  pTextDlgParm);
      LPaintEffect(LPTRANSDLGPARM pTransDlgParm);
      LPaintEffect(LPEFXDLGPARM   pEfxDlgParm);

      virtual ~LPaintEffect();

      //Accessor functions
      L_INT          SetFillBitmap (LBitmapBase L_FAR* pBitmap, LPRECT prcBack=NULL);
      LBitmapBase L_FAR* GetFillBitmap(L_VOID);
      COLORREF       GetForegroundColor();
      L_INT          SetForegroundColor(COLORREF crFill);
      COLORREF       GetBackgroundColor();
      L_INT          SetBackgroundColor(COLORREF crBack);
      COLORREF       GetMiddleBandColor();
      L_INT          SetMiddleBandColor(COLORREF crFrame);
      L_UINT         GetMiddleBandWidth();
      L_INT          SetMiddleBandWidth(L_UINT uFrameWidth);
      L_UINT         GetOuterBandWidth();
      L_INT          SetOuterBandWidth(L_UINT uOuterWidth);
      COLORREF       GetOuterBandShadowColor();
      L_INT          SetOuterBandShadowColor(COLORREF crOuterShadow);
      COLORREF       GetOuterBandHilite();
      L_INT          SetOuterBandHilite(COLORREF crOuterHilite);
      L_UINT         GetInnerBandWidth();
      L_INT          SetInnerBandWidth(L_UINT uInnerWidth);
      COLORREF       GetInnerBandShadowColor();
      L_INT          SetInnerBandShadowColor(COLORREF crInnerShadow);
      COLORREF       GetInnerBandHilite();
      L_INT          SetInnerBandHilite(COLORREF crInnerHilite);
      
      L_INT          SetGradientParameters(LPGRADDLGPARM pGradDlgParm);
      L_INT          GetGradientParameters(LPGRADDLGPARM pGradDlgParm);

      L_INT          SetShapeParameters(LPSHAPEDLGPARM pShapeDlgParm);
      L_INT          GetShapeParameters(LPSHAPEDLGPARM pShapeDlgParm);

      L_INT          SetTextParameters(LPTEXTDLGPARM pTextDlgParm);
      L_INT          GetTextParameters(LPTEXTDLGPARM pTextDlgParm);

      L_INT          SetTransitionParameters(LPTRANSDLGPARM pTransDlgParm);
      L_INT          GetTransitionParameters(LPTRANSDLGPARM pTransDlgParm);

      L_INT          SetEffectParameters(LPEFXDLGPARM  pEfxDlgParm);
      L_INT          GetEffectParameters(LPEFXDLGPARM  pEfxDlgParm);

      //operations:         
      virtual L_INT  Draw3dShape(LPRECT pRect, L_UINT uShape);
      virtual L_INT  Draw3dShape(LPRECT pRect, HRGN hRgn);
      virtual L_INT  Draw3dText(LPRECT pRect, L_CHAR L_FAR* pszText, L_INT nAngle);
      virtual L_INT  DrawFrame(LPRECT pRect, L_UINT uFrameStyle= EFX_FRAME_OUTER_RAISED|EFX_FRAME_ADJUST_RECT);
      virtual L_INT  DrawGradient (LPRECT pRect, L_UINT uStyle);
      virtual L_INT  DrawPattern(LPRECT pRect, L_UINT uStyle);
      virtual L_INT  PaintTransition(LPRECT pRect, L_UINT uTransition, L_UINT uEffect= EFX_EFFECT_WIPE_L_TO_R, L_UINT uPass=1, L_UINT uMaxPass=1, L_UINT32 uROP= SRCCOPY);
      virtual L_INT  EffectBlt(L_INT nXDest, L_INT nYDest, L_INT nWidth, L_INT nHeight, HDC hdcSrc, L_INT nXSrc, L_INT nYSrc, L_UINT uEffect,L_UINT uPass, L_UINT uMaxPass,L_UINT32 uROP=SRCCOPY);
      virtual L_INT  PaintBitmap(L_UINT uEffect,L_UINT uPass,L_UINT uMaxPass,L_UINT32 uROP3=SRCCOPY);   
      virtual L_INT  PaintRgnDCEffect(L_UINT  uEffect=EFX_EFFECT_NONE, L_UINT32 uROP3=SRCCOPY);
};

#endif //_LEAD_DRAW_H_
/*================================================================= EOF =====*/
