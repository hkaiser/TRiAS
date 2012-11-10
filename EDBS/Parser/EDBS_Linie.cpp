// EDBS_Linie.cpp : Implementierung von CEDBS_Linie
#include "stdafx.h"
#include "Edbs.h"
#include "EDBS_Linie.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_Linie

STDMETHODIMP CEDBS_Linie::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IEDBS_Linie
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

CEDBS_Linie::CEDBS_Linie( void )
{
 HRESULT hResult;
	mpobjGeometrie = NULL;
	hResult = CComObject<CEDBS_FachparameterDerLinie>::CreateInstance(&mpobjsFachparameter); 
	mpobjsFachparameter->AddRef();
}

CEDBS_Linie::~CEDBS_Linie( void )
{
 	if( mpobjGeometrie )
		mpobjGeometrie->Release();
	if(mpobjsFachparameter->Release())
		ASSERT(0);
}

STDMETHODIMP CEDBS_Linie::get_Folie(short *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = msFolie;

	return S_OK;
}

/*
STDMETHODIMP CEDBS_Linie::put_Folie(short newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	msFolie = newVal;

	return S_OK;
}
*/

STDMETHODIMP CEDBS_Linie::get_Objektart(short *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = msObjektart;

	return S_OK;
}

/*
STDMETHODIMP CEDBS_Linie::put_Objektart(short newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	msObjektart = newVal;

	return S_OK;
}
*/

STDMETHODIMP CEDBS_Linie::get_Geometrieart(short *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if( mpobjGeometrie == NULL )
		*pVal = 0;
	else
		*pVal = mpobjGeometrie->mbGeometrieart;

	return S_OK;
}
/*
STDMETHODIMP CEDBS_Linie::put_Geometrieart(short newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		mbGeometrieart = (BYTE)newVal;

	return S_OK;
}
*/
STDMETHODIMP CEDBS_Linie::get_Linienteilung(short *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = mbLinienteilung;

	return S_OK;
}

/*
STDMETHODIMP CEDBS_Linie::put_Linienteilung(short newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mbLinienteilung = (BYTE)newVal;

	return S_OK;
}
*/
STDMETHODIMP CEDBS_Linie::get_Fachparameter(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
	if( mpobjsFachparameter == NULL )
		*pVal = NULL;
	else {
		hResult = mpobjsFachparameter->QueryInterface(IID_IEDBS_FachparameterDerLinie,(void**)pVal);
		if( hResult )
			*pVal = NULL;
	}

	return S_OK;
}

STDMETHODIMP CEDBS_Linie::get_Objektteilnummer(short *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = msObjektteilnummer;

	return S_OK;
}

STDMETHODIMP CEDBS_Linie::get_Geometrie(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
	if( mpobjGeometrie == NULL )
		*pVal = NULL;
	else {
		hResult = mpobjGeometrie->QueryInterface(IID_IEDBS_Geometrie,(void**)pVal);
		if( hResult )
			*pVal = NULL;
	}

	return S_OK;
}
