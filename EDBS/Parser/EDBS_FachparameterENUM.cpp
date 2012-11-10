// EDBS_FachparameterENUM.cpp : Implementierung von CEDBS_FachparameterENUM
#include "stdafx.h"
#include "Edbs.h"
#include "EDBS_FachparameterENUM.h"
#include "EDBS_Fachparameter.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_FachparameterENUM

CEDBS_FachparameterENUM::CEDBS_FachparameterENUM( void )
{
	mpos = NULL;
}

STDMETHODIMP CEDBS_FachparameterENUM::Reset()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mpos = mpobjsFachparameter->mlstFachparameter.GetHeadPosition();

	return S_OK;
}

STDMETHODIMP CEDBS_FachparameterENUM::Clone(IEnumVARIANT * * ppenum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (ppenum == NULL)
		return E_POINTER;
		
	return E_NOTIMPL;
}

STDMETHODIMP CEDBS_FachparameterENUM::Skip(ULONG celt)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	return E_NOTIMPL;
}

STDMETHODIMP CEDBS_FachparameterENUM::Next(ULONG celt, VARIANT *rgvar, ULONG * pceltFetched)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CString key;
 CComObject<CEDBS_Fachparameter> *pobjFachparameter;
 IDispatch *pIObjekt;
 VARIANT *vx;
 ULONG ux;

	if( celt == 1 ) {
		if( mpos == NULL ) {
			hResult = S_FALSE;
		}
		else {
			pobjFachparameter = (CComObject<CEDBS_Fachparameter>*)mpobjsFachparameter->mlstFachparameter.GetNext(mpos);
			hResult = pobjFachparameter->QueryInterface(IID_IDispatch,(void**)&pIObjekt);
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
				pobjFachparameter = (CComObject<CEDBS_Fachparameter>*)mpobjsFachparameter->mlstFachparameter.GetNext(mpos);
				hResult = pobjFachparameter->QueryInterface(IID_IDispatch,(void**)&pIObjekt);
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
