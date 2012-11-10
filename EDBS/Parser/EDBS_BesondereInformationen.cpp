// EDBS_BesondereInformationen.cpp : Implementierung von CEDBS_BesondereInformationen
#include "stdafx.h"
#include "Edbs.h"
#include "EDBS_BesondereInformation.h"
#include "EDBS_BesondereInformationen.h"
#include "EDBS_BesondereInformationenENUM.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_BesondereInformationen

CEDBS_BesondereInformationen::CEDBS_BesondereInformationen( void )
{

}

CEDBS_BesondereInformationen::~CEDBS_BesondereInformationen( void )
{
	POSITION pos;
	CComObject<CEDBS_BesondereInformation> *pobjBesondereInformation;

	for( pos = mlstBesondereInformationen.GetHeadPosition(); pos != NULL; ) {
		pobjBesondereInformation = (CComObject<CEDBS_BesondereInformation> *)mlstBesondereInformationen.GetNext( pos );
		if(pobjBesondereInformation->Release())
			ASSERT(0);
	}
	mlstBesondereInformationen.RemoveAll();
}

STDMETHODIMP CEDBS_BesondereInformationen::get_Count(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = mlstBesondereInformationen.GetCount();

	return S_OK;
}

STDMETHODIMP CEDBS_BesondereInformationen::get__NewEnum(IUnknown **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CComObject<CEDBS_BesondereInformationenENUM> *pobjENUM;
 IEnumVARIANT *pIENUM;

	hResult = CComObject<CEDBS_BesondereInformationenENUM>::CreateInstance(&pobjENUM); 
	pobjENUM->mpobjsBesondereInformationen = this;
	hResult = pobjENUM->QueryInterface(IID_IUnknown,(void**)pVal);
	
	pIENUM = NULL;
	hResult = pobjENUM->QueryInterface(IID_IEnumVARIANT,(void**)&pIENUM);
	pIENUM->Reset();

	return S_OK;
}

STDMETHODIMP CEDBS_BesondereInformationen::get_Item(VARIANT *vntIndexKey, VARIANT *pVal)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CComObject<CEDBS_BesondereInformation> *pobjBesondereInformation;
 POSITION pos;
 IDispatch *pIObjekt;
 CString key;
 long lx;

	switch(vntIndexKey->vt) {
	case VT_I4|VT_BYREF:
		if( 0 < *vntIndexKey->plVal && *vntIndexKey->plVal <= mlstBesondereInformationen.GetCount() ) {
			pos = mlstBesondereInformationen.GetHeadPosition();
			lx = 0;
			while( lx != *vntIndexKey->plVal && pos != NULL ) {
				lx++;
				pobjBesondereInformation = (CComObject<CEDBS_BesondereInformation>*)mlstBesondereInformationen.GetNext(pos);
			};
			if( lx == *vntIndexKey->plVal ) {
				hResult = pobjBesondereInformation->QueryInterface(IID_IDispatch,(void**)&pIObjekt);
				pVal->vt = VT_DISPATCH;
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
