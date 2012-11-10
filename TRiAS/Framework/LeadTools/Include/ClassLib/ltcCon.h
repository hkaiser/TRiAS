/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1990, 1998 by LEAD Technologies, Inc.                         |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   :                                                                 |
| FILE NAME : ltcCon.h                                                        |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_CON_H_
#define  _LEAD_CON_H_
/*----------------------------------------------------------------------------+
| INCLUDES                                                                    |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------+
| Class     : LContainer                                                    |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : March  2000                                                     |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LContainer: public LBase 
{
   friend LAutomation;

   LEAD_DECLAREOBJECT(LContainer);

   private:
      L_BOOL               m_bEnableCallBack;

   protected:
      pCONTAINERHANDLE     m_pContainer;

   private:
      static L_INT         EXT_CALLBACK ContainerCS(pCONTAINERHANDLE   pContainer, 
                                                     CONTAINEREVENTTYPE nEventType,
                                                     L_VOID L_FAR       *pEventData, 
                                                     L_VOID L_FAR       *pUserData);

   protected:
      virtual L_INT        ContainerCallBack(CONTAINEREVENTTYPE nEventType, L_VOID L_FAR *pEventData);

   public:
      LContainer();
      ~LContainer();
      L_BOOL               IsValid(); 
      L_INT                Initialize(); 
      L_INT                Create(HWND hwndOwner);
      L_INT                Update(LPRECT prcPaint); 
      L_INT                Reset(); 
      L_INT                EditObject(const pCONTAINEROBJECTDATA pObjectData);
      L_INT                SetOwner(HWND hWndOwner);
      L_INT                SetMetrics(pCONTAINERMETRICS pMetrics); 
      L_INT                SetOffset(L_INT nXOffset, L_INT nYOffset, L_INT nZOffset = 0); 
      L_INT                SetScalar(pVECTORPOINT pvptScalarNum, pVECTORPOINT pvptScalarDen); 
      L_INT                SetObjectType(CONTAINEROBJECTTYPE nObjectType);
      L_INT                SetObjectCursor(CONTAINEROBJECTTYPE nObjectType, HCURSOR hCursor);
      L_INT                SetEnabled(L_BOOL bEnable);
      L_INT                SetOwnerDraw(L_BOOL bOwnerDraw, L_UINT32 dwFlags);
      L_INT                GetOwner(HWND* phwndOwner);
      L_INT                GetMetrics(pCONTAINERMETRICS pMetrics);
      L_INT                GetOffset(L_INT *pnXOffset, L_INT *pnYOffset, L_INT *pnZOffset); 
      L_INT                GetScalar(pVECTORPOINT pvptScalarNum, pVECTORPOINT pvptScalarDen);
      L_INT                GetObjectType(pCONTAINEROBJECTTYPE pnObjectType);
      L_INT                GetObjectCursor(CONTAINEROBJECTTYPE nObjectType, HCURSOR* phCursor);
      L_BOOL               IsEnabled();
      L_BOOL               IsOwnerDraw();
      L_BOOL               EnableContainerCallBack(L_BOOL bEnable);
      L_INT                Free();
};

#endif //_LEAD_CON_H_
/*================================================================= EOF =====*/
