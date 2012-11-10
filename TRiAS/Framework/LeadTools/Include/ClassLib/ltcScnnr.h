/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcscnnr.h                                                      |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_SCANNER_H_
#define  _LEAD_SCANNER_H_

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LScanner                                                        |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September 1998                                                  |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LScanner: public LBase
{
   LEAD_DECLAREOBJECT(LScanner);

   public:
      L_VOID *m_extLScanner;
      
   protected :
      LBitmapBase L_FAR*   m_pBitmap;
      HWND                 m_hWnd;

   public : 
      LScanner();
      virtual ~LScanner();

      L_BOOL         IsValid();
      virtual L_VOID SetWindow(HWND hWnd);
      virtual L_VOID SetBitmap(LBitmapBase L_FAR* pBitmap);
};

/*----------------------------------------------------------------------------+
| Class     : LScanner                                                        |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : 26 may 1998                                                     |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LTwain : public LScanner
{
   LEAD_DECLAREOBJECT(LTwain);

   public:
      L_VOID *m_extLTwain;
      
   private:  
      static L_INT  EXT_CALLBACK AcquireCS(pBITMAPHANDLE pBitmap,L_VOID L_FAR*  pUserData);
      static L_INT  EXT_CALLBACK EnumSourcesCS(L_TCHAR L_FAR * pBuffer,L_INT   uBytes,
                                        L_VOID  L_FAR* pUserData);
   protected:
      virtual L_INT  EnumSourcesCallBack(L_TCHAR L_FAR * pBuffer,L_INT uBytes);   
      virtual L_INT  AcquireCallBack();

   public : 
      LTwain();
      LTwain(HWND hWnd,LBitmapBase L_FAR* pBitmap);

      virtual ~LTwain();

      virtual L_INT  Acquire(L_UINT uFlags=0); 
      virtual L_BOOL IsAvailable();              
      virtual L_INT  EnumSources();
      virtual L_INT  Select(); 
      virtual L_INT  SetProperties(pTWAINPROPERTIES pTwain,L_UINT32 uFlags);
      virtual L_INT  GetProperties(pTWAINPROPERTIES pTwain); 
      virtual L_INT  CloseSession();  
};

/*----------------------------------------------------------------------------+
| Class     : LIsis                                                           |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : 26 may 1998                                                     |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LIsis : public LScanner
{
   public:
      L_VOID *m_extLIsis;
      
   private:  
      LEAD_DECLAREOBJECT(LIsis);
      static L_INT EXT_CALLBACK AcquireMultiCS(
                                    pBITMAPHANDLE pBitmap,
                                    L_INT32 nPage,
                                    L_CHAR L_FAR* pszFileName,
                                    L_VOID  L_FAR* pUserData
                                  );

   protected : 
      virtual L_INT AcquireMultiCallBack(
                                          L_INT32 nPage,
                                          L_CHAR L_FAR* pszFileName
                                        );

   public : 
      LIsis();
      LIsis(HWND hWnd,LBitmapBase L_FAR* pBitmap);
      virtual ~LIsis();

      virtual L_BOOL IsAvailable();               
      virtual L_INT  Acquire(L_UINT uFlags=0);        
      virtual L_INT  AcquireMulti(
                                    L_CHAR L_FAR * pszBaseFileName,
                                    L_UINT32  uFlags=0,
                                    L_INT  nFormat=FILE_TIF,
                                    L_BOOL bMultiPageFile=TRUE, 
                                    L_INT L_FAR* pnPagesDiscarded=NULL
                                 );
      virtual L_INT Select(L_CHAR L_FAR* pszCurScanDriver);  
      virtual L_INT LoadDriver(L_CHAR L_FAR* pszDriverName=0); 
      virtual L_INT UnloadDriver();  
      virtual L_INT SetTagShort(L_UINT uTag,L_INT nValue);  
      virtual L_INT GetTagShort(L_UINT uTag,L_INT L_FAR* pnValue); 
      virtual L_INT SetTagLong(L_UINT uTag,L_INT32 nValue);  
      virtual L_INT GetTagLong(L_UINT uTag,L_INT32 L_FAR* pnValue); 
      virtual L_INT SetScanOptions();

      virtual L_INT SetTagASCII(L_UINT uTag, L_CHAR * pszValue);
      virtual L_INT GetTagASCII(L_UINT uTag, L_CHAR * pszValue, L_UINT32 * puSize, L_BOOL bDefault);
      virtual L_INT GetTagASCIIChoice(L_UINT uTag, L_INT32 nIndex, L_CHAR * pszValue, L_UINT32 * puSize);
      virtual L_INT GetTagLongChoice(L_UINT uTag, L_INT32 nIndex, L_INT32 * plValue);
      virtual L_INT GetTagShortChoice(L_UINT uTag, L_INT32 nIndex, L_INT * pnValue);
};
   
#endif //_LEAD_SCANNER_H_
/*================================================================= EOF =====*/



