/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcDictn.h                                                      |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/

#ifndef  _LEAD_DICTIONARY_H_
#define  _LEAD_DICTIONARY_H_

/*----------------------------------------------------------------------------+
| CLASSES DECLARATION                                                         |
+----------------------------------------------------------------------------*/
#define ALLOCATED_DICTIONARY_SIZE    50
/*----------------------------------------------------------------------------+
| Class     : LDictionary                                                     |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September 1998                                                  |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LDictionary :public LBase
{
   public:
      L_VOID *m_extLDictionary;
      
   protected:
      HGLOBAL                    m_hDictionary;
      L_VOID L_FAR* L_FAR*       m_pItem;
      L_INT                      m_nCount;
      L_INT                      m_nSize;
   public : 
      LDictionary();
      virtual ~LDictionary();

      L_INT                      GetCount();
      L_VOID L_FAR*              GetItem(L_INT nIndex);
      L_VOID                     AddItem(L_VOID L_FAR* pItem);
      L_VOID                     RemoveItem(L_VOID L_FAR* pItem);
      L_BOOL                     IsItem(L_VOID L_FAR* pItem);
};

/*----------------------------------------------------------------------------+
| Class     : LBitmapDictionary                                               |
| Desc      :                                                                 |
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+
| Date      : September 1998                                                  |
+----------------------------------------------------------------------------*/
class LWRP_EXPORT LBitmapDictionary :public LDictionary
{
   public:
      L_VOID *m_extLBitmapDictionary;
      
   public : 
      L_VOID               DisconnectBitmapList(LBitmapList L_FAR* pLBitmaplist);
};

#endif //_LEAD_DICTIONARY_H_
/*================================================================= EOF =====*/



