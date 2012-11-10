// EDBS_ObjekteENUM.cpp : Implementierung von CEDBS_ObjekteENUM
#include "stdafx.h"
#include "Edbs.h"
#include "EDBS_ObjekteENUM.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_ObjekteENUM

CEDBS_ObjekteENUM::CEDBS_ObjekteENUM( void )
{
	mpos = NULL;
}

STDMETHODIMP CEDBS_ObjekteENUM::Reset()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mpos = mpobjsEDBS->mmapObjects.GetStartPosition();

	return S_OK;
}

STDMETHODIMP CEDBS_ObjekteENUM::Clone(IEnumVARIANT * * ppenum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (ppenum == NULL)
		return E_POINTER;
		
	return E_NOTIMPL;
}

STDMETHODIMP CEDBS_ObjekteENUM::Skip(ULONG celt)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	return E_NOTIMPL;
}

STDMETHODIMP CEDBS_ObjekteENUM::Next(ULONG celt, VARIANT *rgvar, ULONG * pceltFetched)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CString key;
 CComObject<CEDBS_Objekt> *pobjEDBS;
 IDispatch *pIObjekt;
 VARIANT *vx;
 ULONG ux;

	if( celt == 1 ) {
		if( mpos == NULL ) {
			hResult = S_FALSE;
		}
		else {
			mpobjsEDBS->mmapObjects.GetNextAssoc(mpos, key, (CObject*&)pobjEDBS);
			hResult = pobjEDBS->QueryInterface(IID_IDispatch,(void**)&pIObjekt);
			rgvar->vt = VT_DISPATCH;
//			pIObjekt->AddRef();
			rgvar->pdispVal = pIObjekt;
		}
	}
	else {
		if (pceltFetched == NULL)
			return E_POINTER;
		if( mpos == NULL ) {
			*pceltFetched = 0;
			hResult = S_FALSE;
		}
		else {
			ux = 0;
			vx = rgvar;
			while( mpos != NULL && ux < celt ) {
				ux++;
				mpobjsEDBS->mmapObjects.GetNextAssoc(mpos, key, (CObject*&)pobjEDBS);
				hResult = pobjEDBS->QueryInterface(IID_IDispatch,(void**)&pIObjekt);
				vx->vt = VT_DISPATCH;
//				pIObjekt->AddRef();
				vx->pdispVal = pIObjekt;
				vx++;
			}
			*pceltFetched = ux;
			hResult = S_OK;
		}
		hResult = S_FALSE;
	}

	return hResult;
}
