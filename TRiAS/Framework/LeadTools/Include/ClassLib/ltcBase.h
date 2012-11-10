/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcbase.h                                                       |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_BASE_H_
#define  _LEAD_BASE_H_
/*----------------------------------------------------------------------------+
| INCLUDES                                                                    |
+----------------------------------------------------------------------------*/
//#include "ltwrappr.h"

#define  ERRORS_COUNT                  993 //find out after link 
#define  MAX_ERR_SIZE                  256
#define  LEAD_INITALIZE_ERROR_DEPTH     1


/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LBase                                                    |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September  1998                                                 |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LBase
{
   LEAD_DECLAREOBJECT(LBase);

   public:
      L_VOID *m_extLBase;

   private:
      static L_CHAR           m_ErrorStr[ERRORS_COUNT][MAX_ERR_SIZE];
      static HGLOBAL          m_hErrorList;
      static L_UINT           m_uErrorsCount;
      static L_UINT           m_uListDepth;
      static L_INT*           m_pnErrorList;
      static L_UINT32         m_uErrorFlags;
      static L_UINT           m_uLastErrorIndex;
      static L_INT            m_nInstanceCounter; 

      static HINSTANCE        m_hLTDisDll;
      static HINSTANCE        m_hLTAnnDll;
      static HINSTANCE        m_hLTCapDll;
      static HINSTANCE        m_hLTDlgDll;
      static HINSTANCE        m_hLTEfxDll;
      static HINSTANCE        m_hLTFilDll;
      static HINSTANCE        m_hLTImgDll;
      static HINSTANCE        m_hLTIsiDll;
      static HINSTANCE        m_hLTKrnDll;
      static HINSTANCE        m_hLTNetDll;
      static HINSTANCE        m_hLTScrDll;
      static HINSTANCE        m_hLTTwnDll;
      static HINSTANCE        m_hLTWebDll;
      static HINSTANCE        m_hLTVidDll;
      static HINSTANCE        m_hLTTmbDll;
      static HINSTANCE        m_hLTLstDll;
      static HINSTANCE        m_hLVKrnDll;
      static HINSTANCE        m_hLVDlgDll;
      static HINSTANCE        m_hLTBarDll;
      static HINSTANCE        m_hLDKrnDll;
      static HINSTANCE        m_hLTAutDll;
      static HINSTANCE        m_hLTConDll;
      static HINSTANCE        m_hLTPntDll;
      static HINSTANCE        m_hLTTlbDll;
      static HINSTANCE        m_hLTPdgDll;
      static HINSTANCE        m_hLTSgmDll;

      static L_BOOL           m_bAutoErrorDisplay;

      L_BOOL                  m_bEnableCallBack;
      L_BOOL                  m_bEnableStatusCallBack;

   protected: 

   private:
      static  L_BOOL CALLBACK DisplayAllErrorDlgProc(HWND hDlg,UINT uMsg, WPARAM wParam, LPARAM lParam);

   protected: 
      static  L_INT   EXT_CALLBACK StatusCS(L_INT nPercentComplete, L_VOID L_FAR*pUserData);
      virtual L_INT   StatusCallBack(L_INT nPercentComplete);

   public:
      LBase();
      ~LBase();
      
      static L_INT            VersionInfo(pVERSIONINFO pVersionInfo);
      L_BOOL                  IsCallBackEnabled();
      L_BOOL                  EnableCallBack(L_BOOL bEnable);

      L_BOOL                  IsStatusCallBackEnabled();
      L_BOOL                  EnableStatusCallBack(L_BOOL bEnable);

      static  L_BOOL          IsAutoErrorDisplayEnabled();
      static  L_BOOL          EnableAutoErrorDisplay(L_BOOL bEnable);

      static  L_INT           GetErrorFromList(L_UINT uIndex=LEAD_LAST_ERROR); 
      static  L_UINT          SetErrorListDepth(L_UINT uListDepth);
      static  L_UINT          GetErrorListDepth(L_VOID);
      static  L_VOID          ClearErrorList(L_VOID);
      static  L_UINT          GetErrorsNumber();
      static  L_VOID          DisplayErrorList(HWND hWndParent,L_BOOL bShowLastErrorFirst=TRUE);
      static  L_VOID          DisplayErrorFromList(HWND  hWndParent=NULL, L_UINT uIndex=LEAD_LAST_ERROR);

      static  L_VOID          DisplayError(HWND hWndParent, L_INT nErrorCode);
      static  L_VOID          DisplayError(HWND hWndParent,L_CHAR L_FAR* lpszStr);
      static  L_CHAR L_FAR*   GetErrorString(L_INT nErrorCode);
      static  L_VOID          SetErrorString(L_INT nErrorCode, L_CHAR L_FAR* pszNewErrString, L_CHAR L_FAR* pszOldErrString=NULL,L_UINT uSizeOldErrStrBuff=0);
      static  L_VOID          RecordError(L_INT nErrorCode);
      static  LBase*          LEAD_ObjectManager(LWRAPPEROBJECTTYPE nType,LBase* This,LPLEADCREATEOBJECT* pCreateObj);

      static  L_UINT32        LoadLibraries(L_UINT32 uLibraries);
      static  L_VOID          UnloadLibraries(L_UINT32 uLibraries);
      static  L_UINT32        GetLoadedLibraries();
};

#endif //_LEAD_BASE_H_

/*================================================================= EOF =====*/
