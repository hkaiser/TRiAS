// EDBS_Fachparameter.cpp : Implementierung von CEDBS_Fachparameter
#include "stdafx.h"
#include "Edbs.h"
#include "EDBS_Fachparameter.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_Fachparameter

CEDBS_Fachparameter::CEDBS_Fachparameter( void )
{
}

CEDBS_Fachparameter::~CEDBS_Fachparameter( void )
{
}

STDMETHODIMP CEDBS_Fachparameter::get_Art(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CComBSTR bstrArt(mstrArtDesFachparameters);

	*pVal = bstrArt.Detach();


	return S_OK;
}

/*
STDMETHODIMP CEDBS_Fachparameter::put_Art(BSTR newVal)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mstrArtDesFachparameters = OLE2A(newVal);

	return S_OK;
}
*/

STDMETHODIMP CEDBS_Fachparameter::get_Kennung(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CComBSTR bstrKennung(mstrKennungDesFachparameters);

	*pVal = bstrKennung.Detach();

	return S_OK;
}

/*
STDMETHODIMP CEDBS_Fachparameter::put_Kennung(BSTR newVal)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mstrKennungDesFachparameters = OLE2A(newVal);

	return S_OK;
}
*/

STDMETHODIMP CEDBS_Fachparameter::get_Wert(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CComBSTR bstrWert(mstrWertDesFachparameters);

	*pVal = bstrWert.Detach();

	return S_OK;
}

/*
STDMETHODIMP CEDBS_Fachparameter::put_Wert(BSTR newVal)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mstrWertDesFachparameters = OLE2A(newVal);

	return S_OK;
}
*/