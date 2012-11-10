// GroupByObjList.cpp : Implementation of cGroupByObjList
#include "stdafx.h"
#include "TRiASNativeDB.h"
#include "GroupByObjList.h"
//#include "GroupByObj.h"

/////////////////////////////////////////////////////////////////////////////
// cGroupByObjList

STDMETHODIMP cGroupByObjList::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IGroupByObjList
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

//void cGroupByObjList::Initialize( CGroupByListPtr pList )
//{	
//	m_pList = pList;

//	for ( int i = 0; i < pList->GetSize(); i++ )
//		{
//		CComObject<cGroupByObj>* pObj;
//		CComVariant var;
//		IGroupByObj *pIdent;

//		CComObject<cGroupByObj>::CreateInstance(&pObj);
//		pObj->Initialize( pList->GetAt( i ) );
//		pObj->QueryInterface( &pIdent );
//		var = pIdent;
//		m_coll.push_back(var);
//		pObj->Release();
//		}
//}
