/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : tcprnt.h                                                        |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_PRINT_H_
#define  _LEAD_PRINT_H_

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LPrint                                                          |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September 1998                                                  |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LPrint :public LBase
{
   LEAD_DECLAREOBJECT(LPrint);

   public:
      L_VOID *m_extLPrint;
      
   protected:  
      LBitmapBase L_FAR*    m_pBitmap;      

   public : 
      LPrint();
      LPrint(LBitmapBase L_FAR* pLBitmap);
      virtual ~LPrint();

      L_BOOL  IsValid();
      virtual L_VOID SetBitmap(LBitmapBase L_FAR* pBitmap);

      HDC          GetPrinterDC();
      virtual HDC  Print(
                           HDC hDC=NULL,
                           L_INT nX=0,L_INT nY=0,
                           L_INT nWidth=0,L_INT nHeight=0,
                           L_BOOL bEndDoc=TRUE
                        );    
      virtual HDC  PrintFast(
                              HDC hDC=NULL,
                              L_INT nX=0,L_INT nY=0,
                              L_INT nWidth=0,L_INT nHeight=0,
                              L_BOOL bEndDoc=TRUE
                            ); 
};

#endif //_LEAD_PRINT_H_
/*================================================================= EOF =====*/
