/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1990, 1998 by LEAD Technologies, Inc.                         |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   :                                                                 |
| FILE NAME : ltcTt.h                                                         |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_TB_H_
#define  _LEAD_TB_H_
/*----------------------------------------------------------------------------+
| INCLUDES                                                                    |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------+
| Class     : LToolbar                                                        |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : March  2000                                                     |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LToolbar: public LBase
{
   friend LAutomation;
   friend LRasterPaintWindow;

   LEAD_DECLAREOBJECT(LToolbar);

   public:
     LToolbar();
     ~LToolbar();
   
   private:  
      L_BOOL            m_bEnableCallBack;
   
   protected:
      pTOOLBARHANDLE    m_pToolbar;
   
   private:
      static L_INT EXT_CALLBACK ToolbarCS(pTOOLBARHANDLE  pToolbar, L_UINT nButtonID, L_UINT32 dwData, L_VOID L_FAR  *pUserData);

   protected:
      virtual L_INT     ToolbarCallBack(L_UINT nButtonID, L_UINT32 dwData);

   public:
      L_INT             Free();
      L_BOOL            IsValid();
      L_INT             Initialize(); 
      L_INT             Create(HWND hwndParent, LPCSTR szTitle, L_UINT32 dwFlags);
      L_INT             FreeToolbarInfo(pLTOOLBARINFO pToolbarInfo);
      L_BOOL            IsVisible();
      L_BOOL            IsButtonEnabled(L_UINT uButtonID);
      L_BOOL            IsButtonVisible(L_UINT uButtonID);
      L_INT             SetVisible(L_BOOL bVisible); 
      L_INT             SetPosition(LPPOINT lpptPos, L_UINT32 dwFlags);
      L_INT             SetRows(L_INT nRows);
      L_INT             SetButtonChecked(L_UINT uButtonID);
      L_INT             SetButtonEnabled(L_UINT uButtonID, L_BOOL bEnable);
      L_INT             SetButtonVisible(L_UINT uButtonID, L_BOOL bVisible);
      L_INT             SetToolbarInfo(pLTOOLBARINFO pToolbarInfo);
      POINT             GetPosition(L_UINT32 dwFlags);
      L_INT             GetRows();
      L_INT             GetButtonChecked();
      L_INT             GetToolbarInfo(pLTOOLBARINFO pToolbarInfo);
      L_BOOL            EnableToolbarCallBack(L_BOOL bEnable);
      //YF2 Adding 4 functions on May 1'st 2000
      L_INT             AddButton(L_UINT uButtonRefId, const pLBUTTONINFO pButtonInfo, L_UINT32 dwFlags);
      L_INT             RemoveButton(L_UINT uButtonId);
      L_INT             GetButtonInfo(L_UINT uButtonId, pLBUTTONINFO pButtonInfo);
      L_INT             SetButtonInfo(L_UINT uButtonId, const pLBUTTONINFO pButtonInfo);
};

#endif //_LEAD_TB_H_
/*================================================================= EOF =====*/