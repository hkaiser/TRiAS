// EDBS_Linien.cpp : Implementierung von CEDBS_Linien
#include "stdafx.h"
#include "Edbs.h"
#include "EDBS_Linie.h"
#include "EDBS_Linien.h"
#include "EDBS_LinienENUM.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_Linien

CEDBS_Linien::CEDBS_Linien( void )
{

}

CEDBS_Linien::~CEDBS_Linien( void )
{
	POSITION pos;
	CComObject<CEDBS_Linie> *pobjLinie;

	for( pos = mlstLinien.GetHeadPosition(); pos != NULL; ) {
		pobjLinie = (CComObject<CEDBS_Linie> *)mlstLinien.GetNext( pos );
		if(pobjLinie->Release())
			ASSERT(0);
	}
	mlstLinien.RemoveAll();
}

STDMETHODIMP CEDBS_Linien::get_Count(long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = mlstLinien.GetCount();

	return S_OK;
}

STDMETHODIMP CEDBS_Linien::get__NewEnum(IUnknown **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CComObject<CEDBS_LinienENUM> *pobjENUM;
 IEnumVARIANT *pIENUM;

	hResult = CComObject<CEDBS_LinienENUM>::CreateInstance(&pobjENUM); 
	pobjENUM->mpobjsLinien = this;
	hResult = pobjENUM->QueryInterface(IID_IUnknown,(void**)pVal);
	
	pIENUM = NULL;
	hResult = pobjENUM->QueryInterface(IID_IEnumVARIANT,(void**)&pIENUM);
	pIENUM->Reset();

	return S_OK;
}

STDMETHODIMP CEDBS_Linien::get_Item(VARIANT *vntIndexKey, VARIANT *pVal)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
 CComObject<CEDBS_Linie> *pobjLinie;
 POSITION pos;
 IDispatch *pIObjekt;
 CString key;
 long lx;

	switch(vntIndexKey->vt) {
	case VT_I4|VT_BYREF:
		if( 0 < *vntIndexKey->plVal && *vntIndexKey->plVal <= mlstLinien.GetCount() ) {
			pos = mlstLinien.GetHeadPosition();
			lx = 0;
			while( lx != *vntIndexKey->plVal && pos != NULL ) {
				lx++;
				pobjLinie = (CComObject<CEDBS_Linie>*)mlstLinien.GetNext(pos);
			};
			if( lx == *vntIndexKey->plVal ) {
				hResult = pobjLinie->QueryInterface(IID_IDispatch,(void**)&pIObjekt);
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
