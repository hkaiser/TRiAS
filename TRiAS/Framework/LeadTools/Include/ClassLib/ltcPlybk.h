/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcPlybk.h                                                      |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_PLAYBACK_H_
#define  _LEAD_PLAYBACK_H_

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------+
| Class     : LPlayBack                                                       |
| Desc      :                                                                 |
| Return    :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September 1998                                                  |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LPlayBack: public LBase 
{
   LEAD_DECLAREOBJECT(LPlayBack);
   LEAD_DECLARE_PLAYBACK_BITMAP();

   friend LWRP_EXPORT LBitmapBase L_FAR* LEAD_GetBitmapObject(LWRAPPERBITMAPMEMBER nClassType,LBase L_FAR* This,LPLEADCREATEOBJECT pCreateObj);
   friend class LAnimationWindow;

   public:
      L_VOID *m_extLPlayBack;

   private :
      LBitmapBase L_FAR*   m_pBitmap;  
      L_VOID               SetHandle(HPLAYBACK hPlayBack, L_BOOL bFreePrev = TRUE);
      HPLAYBACK            GetHandle();

   protected :
      HPLAYBACK            m_hPlayback;
      
   public : 
      LPlayBack();
      virtual ~LPlayBack();

      L_BOOL   IsCreated();
      virtual  L_INT       Create(LBitmapBase  L_FAR* pBitmap, LBitmapList L_FAR* pLBitmapList=NULL);
      virtual  L_INT       Destroy(LBitmapList L_FAR* pLBitmapList);
      virtual  L_INT       Append(LBitmapBase L_FAR* pLBitmap);
      virtual  L_INT       ClearUpdateRect();
      virtual  L_INT       GetIndex();
      virtual  L_UINT      GetState();
      virtual  L_INT       GetUpdateRect(LPRECT prcUpdate,L_BOOL bClear);
      virtual  L_UINT      Process();
      virtual  L_INT       SetIndex(L_INT nIndex);
      virtual  L_UINT32    GetDelay();
      virtual  L_INT       ValidateLines(L_INT nRow, L_INT nLines =1);
      virtual  L_INT       CancelWait();
}; 

#endif //_LEAD_PLAYBACK_H_
/*================================================================= EOF =====*/
