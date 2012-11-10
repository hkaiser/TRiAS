// EDBS_FachparameterDerLinie.cpp : Implementierung von CEDBS_FachparameterDerLinie
#include "stdafx.h"
#include "Edbs.h"
#include "EDBS_Fachparameter.h"
#include "EDBS_FachparameterDerLinie.h"
#include "EDBS_FachparameterENUM.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_FachparameterDerLinie


CEDBS_FachparameterDerLinie::CEDBS_FachparameterDerLinie( void )
{

}

CEDBS_FachparameterDerLinie::~CEDBS_FachparameterDerLinie( void )
{
	POSITION pos;
	CComObject<CEDBS_Fachparameter> *pobjFachparameter;

	for( pos = mlstFachparameter.GetHeadPosition(); pos != NULL; ) {
		pobjFachparameter = (CComObject<CEDBS_Fachparameter> *)mlstFachparameter.GetNext( pos );
		if(pobjFachparameter->Release())
			ASSERT(0);
	}
	mlstFachparameter.RemoveAll();
}

STDMETHODIMP CEDBS_FachparameterDerLinie::get_Count(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = mlstFachparameter.GetCount();

	return S_OK;
}

STDMETHODIMP CEDBS_FachparameterDerLinie::get__NewEnum(IUnknown **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CComObject<CEDBS_FachparameterENUM> *pobjENUM;
 IEnumVARIANT *pIENUM;

	hResult = CComObject<CEDBS_FachparameterENUM>::CreateInstance(&pobjENUM); 
	pobjENUM->mpobjsFachparameter = this;
	hResult = pobjENUM->QueryInterface(IID_IUnknown,(void**)pVal);
	
	pIENUM = NULL;
	hResult = pobjENUM->QueryInterface(IID_IEnumVARIANT,(void**)&pIENUM);
	pIENUM->Reset();

	return S_OK;
}

STDMETHODIMP CEDBS_FachparameterDerLinie::get_Item(VARIANT *vntIndexKey, VARIANT *pVal)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CComObject<CEDBS_Fachparameter> *pobjFachparameter;
 POSITION pos;
 IDispatch *pIObjekt;
 CString key;
 long lx;

	switch(vntIndexKey->vt) {
	case VT_I4|VT_BYREF:
		if( 0 < *vntIndexKey->plVal && *vntIndexKey->plVal <= mlstFachparameter.GetCount() ) {
			pos = mlstFachparameter.GetHeadPosition();
			lx = 0;
			while( lx != *vntIndexKey->plVal && pos != NULL ) {
				lx++;
				pobjFachparameter = (CComObject<CEDBS_Fachparameter>*)mlstFachparameter.GetNext(pos);
			};
			if( lx == *vntIndexKey->plVal ) {
				hResult = pobjFachparameter->QueryInterface(IID_IDispatch,(void**)&pIObjekt);
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

