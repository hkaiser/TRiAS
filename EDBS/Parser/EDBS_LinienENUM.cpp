// EDBS_LinienENUM.cpp : Implementierung von CEDBS_LinienENUM
#include "stdafx.h"
#include "Edbs.h"
#include "EDBS_LinienENUM.h"
#include "EDBS_Linie.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_LinienENUM

CEDBS_LinienENUM::CEDBS_LinienENUM( void )
{
	mpos = NULL;
}

STDMETHODIMP CEDBS_LinienENUM::Reset()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mpos = mpobjsLinien->mlstLinien.GetHeadPosition();

	return S_OK;
}

STDMETHODIMP CEDBS_LinienENUM::Clone(IEnumVARIANT * * ppenum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (ppenum == NULL)
		return E_POINTER;
		
	return E_NOTIMPL;
}

STDMETHODIMP CEDBS_LinienENUM::Skip(ULONG celt)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	return E_NOTIMPL;
}

STDMETHODIMP CEDBS_LinienENUM::Next(ULONG celt, VARIANT *rgvar, ULONG * pceltFetched)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CString key;
 CComObject<CEDBS_Linie> *pobjLinie;
 IDispatch *pIObjekt;
 VARIANT *vx;
 ULONG ux;

	if( celt == 1 ) {
		if( mpos == NULL ) {
			hResult = S_FALSE;
		}
		else {
			pobjLinie = (CComObject<CEDBS_Linie>*)mpobjsLinien->mlstLinien.GetNext(mpos);
			hResult = pobjLinie->QueryInterface(IID_IDispatch,(void**)&pIObjekt);
			rgvar->vt = VT_DISPATCH;
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
				pobjLinie = (CComObject<CEDBS_Linie>*)mpobjsLinien->mlstLinien.GetNext(mpos);
				hResult = pobjLinie->QueryInterface(IID_IDispatch,(void**)&pIObjekt);
				vx->vt = VT_DISPATCH;
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
