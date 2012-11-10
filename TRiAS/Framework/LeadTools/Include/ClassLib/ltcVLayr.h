/*----------------------------------------------------------------------------+
| LEADTOOLS for Windows -                                                     |
| Copyright (c) 1991-2000 LEAD Technologies, Inc.                             |
| All Rights Reserved.                                                        |
|-----------------------------------------------------------------------------|
| PROJECT   : LEAD wrappers                                                   |
| FILE NAME : ltcVLayr.h                                                      |
| DESC      :                                                                 |
+----------------------------------------------------------------------------*/
#ifndef  _LEAD_VECTOR_LAYER_H_
#define  _LEAD_VECTOR_LAYER_H_

/*----------------------------------------------------------------------------+
| Class     : LVectorLayer                                                   |
| Desc      :                                                                 |
| Return    :                                                                 | 
| Notes     :                                                                 |
+-----------------------------------------------------------------------------+*/
class LWRP_EXPORT LVectorLayer : public LBase
{
   LEAD_DECLAREOBJECT(LVectorLayer);
   friend LVectorBase;
   friend LVectorDialog;
   
private:  
   LVectorBase L_FAR* m_pLVector;
   VECTORLAYER        m_Layer;        //this is returned
   VECTORLAYERDESC    m_LayerDesc;    //fill this out
         
private:  
   L_VOID InitializeClass(pVECTORLAYERDESC pLayerDesc, pVECTORLAYER pLayer, LVectorBase L_FAR *pVector);
   static L_INT EXT_CALLBACK EnumObjectsCS ( pVECTORHANDLE pVector, const pVECTOROBJECT pObject, L_VOID L_FAR * pUserData);
   
   
protected:
   virtual L_INT  EnumObjectsCallBack( pVECTORHANDLE pVector, pVECTOROBJECT pObject);
   
public : 
   LVectorLayer::LVectorLayer(pVECTORLAYER pLayer, LVectorBase L_FAR *pVector = NULL);
   LVectorLayer(LVectorBase L_FAR *pVector);
   LVectorLayer(pVECTORLAYERDESC pLayerDesc = NULL, LVectorBase L_FAR *pVector = NULL);
   ~LVectorLayer();
   
   L_VOID      SetVector(LVectorBase L_FAR* pVector);
      
   virtual L_INT DeleteLayer();
   virtual L_INT EmptyLayer();
   virtual L_INT GetLayerDesc(pVECTORLAYERDESC pLayerDesc=NULL);
   virtual L_INT SetLayerDesc(pVECTORLAYERDESC pLayerDesc);
   
   virtual L_INT AddObject(LVectorObject *pVectorObject);

   virtual L_INT EnumObjects(L_UINT32 dwFlags = 0);
   
};
#endif //_LEAD_VECTOR_LAYER_H_
/*================================================================= EOF =====*/