/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1990, 1998 by LEAD Technologies, Inc.                         |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   :                                                                 |
| FILE NAME : ltcRstDlg.h                                                     |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/
#ifndef  _LEAD_RSTDLG_H_
#define  _LEAD_RSTDLG_H_
/*----------------------------------------------------------------------------+
| INCLUDES                                                                    |
+----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------+
| Class     : LRasterDialog                                                   |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : May  2000                                                       |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LRasterDialog: public LBase
{
   LEAD_DECLAREOBJECT(LRasterDialog);

   public:
      LRasterDialog();
      ~LRasterDialog();
      L_INT DoModalBrush(HWND hWnd, pPAINTDLGBRUSHINFO  pBrushDlgInfo);
      L_INT DoModalShape(HWND hWnd, pPAINTDLGSHAPEINFO  pShapeDlgInfo);
      L_INT DoModalRegion(HWND hWnd, pPAINTDLGREGIONINFO pRegionDlgInfo);
      L_INT DoModalFill(HWND hWnd, pPAINTDLGFILLINFO   pFillDlgInfo);
      L_INT DoModalText(HWND hWnd, pPAINTDLGTEXTINFO   pTextDlgInfo);
};
#endif //_LEAD_RSTDLG_H_
/*================================================================= EOF =====*/
