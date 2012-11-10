/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcVGrp.h                                                      |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/
#ifndef  _LEAD_VECTOR_GROUP_H_
#define  _LEAD_VECTOR_GROUP_H_

class LVectorClone;
/*----------------------------------------------------------------------------+
| Class     : LVectorGroup                                                   |
| Desc      :                                                                 |
| Return    :                                                                 | 
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+*/
class LWRP_EXPORT LVectorGroup : public LBase
{
   LEAD_DECLAREOBJECT(LVectorGroup);
   friend LVectorBase;
   friend LVectorDialog;
   friend LVectorClone;
   
private:  
   LVectorBase L_FAR* m_pLVector;
   VECTORGROUP        m_Group;        //this is returned
   VECTORGROUPDESC    m_GroupDesc;    //fill this out
         
private:  
   L_VOID InitializeClass(pVECTORGROUPDESC pGroupDesc, pVECTORGROUP pGroup, LVectorBase L_FAR *pVector);
   static L_INT EXT_CALLBACK EnumObjectsCS ( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_VOID L_FAR * pUserData);
   
   
protected:
   virtual L_INT  EnumObjectsCallBack( pVECTORHANDLE pVector, pVECTOROBJECT pObject);
   
public : 
   LVectorGroup::LVectorGroup(pVECTORGROUP pGroup, LVectorBase L_FAR *pVector = NULL);
   LVectorGroup(LVectorBase L_FAR *pVector);
   LVectorGroup(pVECTORGROUPDESC pGroupDesc = NULL, LVectorBase L_FAR *pVector = NULL);
   ~LVectorGroup();
   
   L_VOID      SetVector(LVectorBase L_FAR* pVector);
      
   virtual L_INT DeleteGroup();
   virtual L_INT DeleteGroupClones(L_UINT32 dwFlags = 0);
   virtual L_INT EmptyGroup();
   virtual L_INT GetGroupDesc(pVECTORGROUPDESC pGroupDesc=NULL);
   virtual L_INT SetGroupDesc(pVECTORGROUPDESC pGroupDesc);
   
   virtual L_INT AddObject(LVectorObject *pVectorObject);
   virtual L_INT EnumObjects(L_UINT32 dwFlags = 0);
   
};
#endif //_LEAD_VECTOR_GROUP_H_
/*================================================================= EOF =====*/