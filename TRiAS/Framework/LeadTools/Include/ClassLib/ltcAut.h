/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1990, 1998 by LEAD Technologies, Inc.                         |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   :                                                                 |
| FILE NAME : ltcAut.h                                                        |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/
#ifndef  _LEAD_AUT_H_
#define  _LEAD_AUT_H_
/*----------------------------------------------------------------------------+
| INCLUDES                                                                    |
+----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------+
| Class     : LAutomation                                                    |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : March  2000                                                     |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LAutomation: public LBase
{
   LEAD_DECLAREOBJECT(LAutomation);

   private:
      LContainer           m_ActiveLContainer;  

   protected:
      pAUTOMATIONHANDLE    m_pAutomation;
      LToolbar*            m_pLToolbar;

   private:
      static L_INT   EXT_CALLBACK  EnumContainersCS(pCONTAINERHANDLE pContainer, L_VOID L_FAR *pUserData);

   protected:
      virtual L_VOID       EnumContainersCallBack(LContainer * pLContainer);

   public:
      LAutomation();
      ~LAutomation();
      L_INT                Initialize();
      L_INT                Free();
      L_BOOL               IsValid();
      L_INT                Create(AUTOMATIONMODE nMode, L_UINT32 dwFlags = 0);
      L_INT                SetUndoLevel(L_UINT uLevel );
      L_UINT               GetUndoLevel();
      L_BOOL               CanUndo();
      L_BOOL               CanRedo();
      L_INT                Undo(L_UINT32 dwFlags = 0);
      L_INT                Redo(L_UINT32 dwFlags = 0);
      L_INT                Select(AUTOMATIONSELECT nSelect, L_UINT32 dwFlags =0);
      L_BOOL               ClipboardDataReady();
      L_INT                Cut(L_UINT32 dwFlags = 0);
      L_INT                Copy(L_UINT32 dwFlags = 0);
      L_INT                Paste(L_UINT32 dwFlags = 0);
      L_INT                Delete(L_UINT32 dwFlags = 0);
      L_INT                Print(L_UINT32 dwFlags = 0);
      L_INT                RemoveContainer(LContainer * pLContainer);
      LContainer*          GetActiveContainer();
      L_INT                SetActiveContainer(LContainer *pLContainer);
      L_INT                AddContainer(LContainer * pLContainer, L_VOID L_FAR *pModeData);
      L_INT                EnumContainers();
      L_INT                SetPaintProperty(PAINTGROUP nGroup, const L_VOID L_FAR *pProperty);
      L_INT                GetPaintProperty(PAINTGROUP nGroup, L_VOID L_FAR *pProperty);
      L_INT                SetPaintBkColor(COLORREF rcBKColor);
      COLORREF             GetPaintBkColor();
      L_INT                SetToolbar(LToolbar * pLToolbar);
      LToolbar*            GetToolbar();
      L_INT                SetUndoEnabled(L_BOOL bEnabled=TRUE);

      L_INT                SetVectorProperty(const pAUTOMATIONVECTORPROPERTIES pAutomationVectorProperties);
      L_INT                GetVectorProperty(pAUTOMATIONVECTORPROPERTIES pAutomationVectorProperties);
      L_INT                EditVectorObject(const pVECTOROBJECT pVectorObject);
      L_INT                EditVectorObject(L_FAR LVectorObject *pEditObject);
      L_INT                AddUndoNode(L_UINT32 dwFlags);

      L_INT                SetCurrentTool(L_INT nTool);
      L_INT                GetCurrentTool(L_INT *pnTool);

};
#endif //_LEAD_AUT_H_
/*================================================================= EOF =====*/

