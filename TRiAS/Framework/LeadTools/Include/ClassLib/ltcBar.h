/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcBar.h                                                        |
| DESC      : Annotation classes                                              |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_BAR_H_
#define  _LEAD_BAR_H_

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LBarCode                                                        |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1999                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LBarCode : public LBase
{
   LEAD_DECLAREOBJECT(LBarCode);
   
   public:
      L_VOID *m_extLBarCode;
   

   protected:
      LBitmapBase    L_FAR *  m_pLBitmap;
      pBARCODEDATA            m_pBarCodeData;
      BARCODEREADOPT          m_BarCodeReadOpt;

   private:
      /* To check bar code type and return it */
      L_BOOL   CheckBarCodeType(L_INT nBarMode);

   public:
      LBarCode();    /* Default Bar Code Class Constructor */
      LBarCode(LBitmapBase L_FAR * pLBitmap); /* Bar Code Class Constructor */
      virtual ~LBarCode();   /* Bar Code Class Destructor */

      /* To check if the Bitmap is valid or not */
      L_BOOL   IsValid(L_VOID);

      /* To set the bitmap that the class will use it for Read/Write functions */
      L_VOID   SetBitmap(LBitmapBase L_FAR * pLBitmap);

      /* To set the Read options before you call Read function */
      L_INT    SetReadOptions(pBARCODEREADOPT pBarCodeReadOpt);

      /* To get the Bar Code Read options */
      L_INT    GetReadOptions(pBARCODEREADOPT pBarCodeReadOpt);

      /* To get the found BARCODEDATA that the Read function recognize */
      pBARCODEDATA GetBarCodeDataItem(L_INT nIndex);

      /* To search for Bar Code in that bitmap */
      L_INT    Read (L_INT             nBarType,
                     pBARCODE1D        pBarCode1D  = NULL,
                     pBARCODEREADPDF   pBarCodePDF = NULL);

      /* To write a Bar Code over that bitmap */
      L_INT    Write(pBARCODEDATA         pBarCodeData,
                     L_UINT32             ulFlags = 0,
                     pBARCODECOLOR        pBarColor = NULL,
                     pBARCODE1D           pBarCode1D = NULL,
                     pBARCODEWRITECODEONE pBarCode2D = NULL,
                     pBARCODEWRITEPDF     pBarCodePDF = NULL,
                     LPRECT               lprcSize = NULL);

      L_INT    WriteExt(pBARCODEDATA         pBarCodeData,
                        L_UINT32             ulFlags = 0,
                        pBARCODECOLOR        pBarColor = NULL,
                        pBARCODE1D           pBarCode1D = NULL,
                        pBARCODEWRITEPDF     pBarCodePDF = NULL,
                        pBARCODEWRITEDM      pBarCodeDM = NULL,
                        LPRECT               lprcSize = NULL);

      /* To free the Bar Code Data */
      static L_INT Free(pBARCODEDATA pBarCodeData);

      /* The following functions for Duplication feature */

      /* To check whether the specified barcode by an index is duplicated or not */
      L_BOOL   IsDuplicated(L_INT nIndex);

      /* To get the total number of duplicated bar code that are similar 
         to the specifed barcode by an index */
      L_INT    GetDuplicatedCount(L_INT nIndex);

      /* To get the first duplicated bar code occurrence for a specified barcode by an index */
      L_INT    GetFirstDuplicated(L_INT nIndex);

      /* To get the next duplicated bar code occurrence for a specified barcode by an index */
      L_INT    GetNextDuplicated(L_INT nIndex);

      /* To retrieves a version information for Bar Code Toolkit */
      static L_INT BarVersionInfo(pBARCODEVERSION   pBarCodeVersion);
};

#endif //_LEAD_BAR_H_
/*================================================================= EOF =====*/