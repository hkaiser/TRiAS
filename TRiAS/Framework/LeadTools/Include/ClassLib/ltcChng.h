/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcCnvrt.h                                                      |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_CHANGE_H_
#define  _LEAD_CHANGE_H_

/*----------------------------------------------------------------------------+
| DEFINES                                                                     |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LChange                                                         |
| Desc      :                                                                 |
| Return    :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : september 1998                                                  |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LChange : public LBase
{
   LEAD_DECLAREOBJECT(LChange);

   public:
      L_VOID *m_extLChange;

   public : 
      LChange();
      virtual ~LChange();

      static HGLOBAL ChangeToDIB(LBitmapBase L_FAR* pLBitmap);
      static L_INT   ChangeFromDIB(LBitmapBase L_FAR* pLBitmap,HGLOBAL hDIB);
      static L_INT   ChangeFromDDB(HDC hDC,
                                   LBitmapBase L_FAR* pLBitmap,
                                   HBITMAP hBitmap,
                                   HPALETTE hPalette
                                  );
      static HBITMAP ChangeToDDB(HDC hDC,LBitmapBase L_FAR* pLBitmap);

      /*v12
      static L_INT   ChangeFromEMF(
                                   LBitmapBase L_FAR* pLBitmap,
                                   HENHMETAFILE hEmf, 
                                   L_UINT uWidth, 
                                   L_UINT uHeight);

      static L_INT   ChangeFromWMF(
                                         LBitmapBase L_FAR* pLBitmap,
                                         HMETAFILE hWmf, 
                                         L_UINT uWidth, 
                                         L_UINT uHeight);
      static HENHMETAFILE ChangeToEMF(LBitmapBase L_FAR* pLBitmap);
      static HMETAFILE ChangeToWMF(LBitmapBase L_FAR* pLBitmap);
      */
};

#endif //_LEAD_CHANGE_H_
/*================================================================= EOF =====*/
