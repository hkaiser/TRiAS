// EDBS_BesondereInformationenENUM.cpp : Implementierung von CEDBS_BesondereInformationenENUM
#include "stdafx.h"
#include "Edbs.h"
#include "EDBS_BesondereInformation.h"
#include "EDBS_BesondereInformationenENUM.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_BesondereInformationenENUM

CEDBS_BesondereInformationenENUM::CEDBS_BesondereInformationenENUM( void )
{
	mpos = NULL;
}

STDMETHODIMP CEDBS_BesondereInformationenENUM::Reset()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mpos = mpobjsBesondereInformationen->mlstBesondereInformationen.GetHeadPosition();

	return S_OK;
}

STDMETHODIMP CEDBS_BesondereInformationenENUM::Clone(IEnumVARIANT * * ppenum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (ppenum == NULL)
		return E_POINTER;
		
	return E_NOTIMPL;
}

STDMETHODIMP CEDBS_BesondereInformationenENUM::Skip(ULONG celt)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	return E_NOTIMPL;
}

STDMETHODIMP CEDBS_BesondereInformationenENUM::Next(ULONG celt, VARIANT *rgvar, ULONG * pceltFetched)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CString key;
 CComObject<CEDBS_BesondereInformation> *pobjBesondereInformation;
 IDispatch *pIObjekt;
 VARIANT *vx;
 ULONG ux;

	if( celt == 1 ) {
		if( mpos == NULL ) {
			hResult = S_FALSE;
		}
		else {
			pobjBesondereInformation = (CComObject<CEDBS_BesondereInformation>*)mpobjsBesondereInformationen->mlstBesondereInformationen.GetNext(mpos);
			hResult = pobjBesondereInformation->QueryInterface(IID_IDispatch,(void**)&pIObjekt);
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
				pobjBesondereInformation = (CComObject<CEDBS_BesondereInformation>*)mpobjsBesondereInformationen->mlstBesondereInformationen.GetNext(mpos);
				hResult = pobjBesondereInformation->QueryInterface(IID_IDispatch,(void**)&pIObjekt);
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
