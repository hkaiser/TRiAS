// OBJS_EDBS.cpp : Implementierung von CEDBS_Objekte
#include "stdafx.h"
#include "Edbs.h"
#include "EDBS_Objekte.h"
#include "EDBS_ObjekteENUM.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_Objekte

CEDBS_Objekte::CEDBS_Objekte( void )
{

}

CEDBS_Objekte::~CEDBS_Objekte( void )
{
	POSITION pos;
	CString strKey;
	CComObject<CEDBS_Objekt> *pobjEDBS;

	for ( pos = mmapObjects.GetStartPosition(); pos != NULL; ) {
		mmapObjects.GetNextAssoc( pos, strKey, (CObject*&)pobjEDBS );
		if(pobjEDBS->Release())
			ASSERT(0);
	}
	mmapObjects.RemoveAll();
}


CComObject<CEDBS_Objekt> *CEDBS_Objekte::GetObjekt( CString strKey )
{
	CComObject<CEDBS_Objekt> *pobjEDBS;
	HRESULT hResult;
	
	if( 0 == mmapObjects.Lookup( strKey, (CObject*&)pobjEDBS ) ) {
		hResult = CComObject<CEDBS_Objekt>::CreateInstance(&pobjEDBS); 
		pobjEDBS->AddRef();
		pobjEDBS->mstrObjektnummer = strKey;
		mmapObjects.SetAt( strKey, (CObject*)pobjEDBS );
	}
	return pobjEDBS;
}

IEDBS_Objekt *CEDBS_Objekte::GetObjEDBS( CString strKey )
{
	IEDBS_Objekt *pobjEDBS;
	HRESULT hResult;

	if( 0 == mmapObjects.Lookup( strKey, (CObject*&)pobjEDBS ) ) {
		hResult = CoCreateInstance( CLSID_EDBS_Objekt, NULL, CLSCTX_INPROC_SERVER, IID_IEDBS_Objekt, (LPVOID *)&pobjEDBS );
		pobjEDBS->AddRef();

		pobjEDBS->put_Objektnummer(CComBSTR(strKey));
		mmapObjects.SetAt( strKey, (CObject*)pobjEDBS );
	}
	return pobjEDBS;
}

STDMETHODIMP CEDBS_Objekte::get_Object(BSTR Objektnummer, IDispatch **pVal)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;

	IEDBS_Objekt *pobjEDBS;

	if( mmapObjects.Lookup( OLE2A(Objektnummer), (CObject*&)pobjEDBS ) )
		*pVal = (IDispatch*)pobjEDBS;
	else {
		hResult = CoCreateInstance( CLSID_EDBS_Objekt, NULL, CLSCTX_INPROC_SERVER, IID_IEDBS_Objekt, (LPVOID *)&pobjEDBS );
		pobjEDBS->put_Objektnummer(Objektnummer);
		mmapObjects.SetAt(OLE2A(Objektnummer),(CObject*)pobjEDBS);
		pobjEDBS->AddRef();
//	*pVal = NULL;
	}

	return S_OK;
}

STDMETHODIMP CEDBS_Objekte::get_Count(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = mmapObjects.GetCount();

	return S_OK;
}


STDMETHODIMP CEDBS_Objekte::get__NewEnum(IUnknown **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CComObject<CEDBS_ObjekteENUM> *pobjENUM;
 IEnumVARIANT *pIENUM;

	hResult = CComObject<CEDBS_ObjekteENUM>::CreateInstance(&pobjENUM); 
	pobjENUM->mpobjsEDBS = this;
	hResult = pobjENUM->QueryInterface(IID_IUnknown,(void**)pVal);
	
	pIENUM = NULL;
	hResult = pobjENUM->QueryInterface(IID_IEnumVARIANT,(void**)&pIENUM);
	pIENUM->Reset();

	return S_OK;
}
/*
STDMETHODIMP CEDBS_Objekte::get_Item(VARIANT *vntIndexKey, IDispatch **pVal)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CComObject<CEDBS_Objekt> *pobjEDBS;
 POSITION pos;
 CString key;
 long lx;

	switch(vntIndexKey->vt) {
	case VT_BSTR:
		if( 0 == mmapObjects.Lookup( OLE2A(vntIndexKey->bstrVal), (CObject*&)pobjEDBS ) )
			hResult = S_FALSE;
		else
			hResult = S_OK;
		break;
	case VT_I4|VT_BYREF:
		pos = mmapObjects.GetStartPosition();
		lx = 0;
		while( lx != *vntIndexKey->plVal && pos != NULL ) {
			lx++;
			mmapObjects.GetNextAssoc(pos, key, (CObject*&)pobjEDBS);
		};
		if( lx == *vntIndexKey->plVal ) {
			hResult = pobjEDBS->QueryInterface(IID_IEDBS_Objekt,(void**)pVal);
			hResult = S_OK;
		}
		else
			hResult = S_FALSE;
		break;
	default:
		ASSERT(0);
		hResult = S_FALSE;
		break;
	}
	return hResult;
}
*/

STDMETHODIMP CEDBS_Objekte::get_Item(VARIANT *vntIndexKey, VARIANT *pVal)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CComObject<CEDBS_Objekt> *pobjEDBS;
 POSITION pos;
 IDispatch *pIObjekt;
 CString key;
 long lx;

	switch(vntIndexKey->vt) {
	case VT_BSTR:
		if( 0 == mmapObjects.Lookup( OLE2A(vntIndexKey->bstrVal), (CObject*&)pobjEDBS ) ) {
//			hResult = S_FALSE;
			pVal->vt = VT_DISPATCH;
			pVal->pdispVal = NULL;
			hResult = S_OK;
		}
		else {
			hResult = pobjEDBS->QueryInterface(IID_IDispatch,(void**)&pIObjekt);
			if( 0 == hResult ) {
				pVal->vt = VT_DISPATCH;
//				pIObjekt->AddRef();
				pVal->pdispVal = pIObjekt;
				hResult = S_OK;
			}
			else
				hResult = S_FALSE;
		}
		break;
	case VT_I4|VT_BYREF:
		if( 0 < *vntIndexKey->plVal && *vntIndexKey->plVal <= mmapObjects.GetCount() ) {
			pos = mmapObjects.GetStartPosition();
			lx = 0;
			while( lx != *vntIndexKey->plVal && pos != NULL ) {
				lx++;
				mmapObjects.GetNextAssoc(pos, key, (CObject*&)pobjEDBS);
			};
			if( lx == *vntIndexKey->plVal ) {
				hResult = pobjEDBS->QueryInterface(IID_IDispatch,(void**)&pIObjekt);
				pVal->vt = VT_DISPATCH;
//				pIObjekt->AddRef();
				pVal->pdispVal = pIObjekt;
				hResult = S_OK;
			}
			else
				hResult = S_FALSE;
		}
		else {
			hResult = S_FALSE;
		}
		break;
	default:
		ASSERT(0);
		hResult = S_FALSE;
		break;
	}
	return hResult;
}
