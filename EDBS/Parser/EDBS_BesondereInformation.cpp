// EDBS_BesondereInformation.cpp : Implementierung von CEDBS_BesondereInformation
#include "stdafx.h"
#include "Edbs.h"
#include "EDBS_BesondereInformation.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_BesondereInformation

CEDBS_BesondereInformation::CEDBS_BesondereInformation( void )
{
	mpobjGeometrie = NULL;
}

CEDBS_BesondereInformation::~CEDBS_BesondereInformation( void )
{
	if( mpobjGeometrie )
		if(mpobjGeometrie->Release())
			ASSERT(0);
}

STDMETHODIMP CEDBS_BesondereInformation::get_Objektart(short *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = msObjektart;

	return S_OK;
}

/*
STDMETHODIMP CEDBS_BesondereInformation::put_Objektart(short newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	msObjektart = newVal;

	return S_OK;
}
*/
STDMETHODIMP CEDBS_BesondereInformation::get_Geometrieart(short *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if( mpobjGeometrie == NULL )
		*pVal = 0;
	else
		*pVal = mpobjGeometrie->mbGeometrieart;

	return S_OK;
}
/*
STDMETHODIMP CEDBS_BesondereInformation::put_Geometrieart(short newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

		mbGeometrieart = (BYTE)newVal;

	return S_OK;
}
*/

STDMETHODIMP CEDBS_BesondereInformation::get_Textdaten(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CComBSTR bstrTextdaten(mstrTextdaten);

	*pVal = bstrTextdaten.Detach();

	return S_OK;
}

STDMETHODIMP CEDBS_BesondereInformation::get_Objektteilnummer(short *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = msObjektteilnummer;

	return S_OK;
}

STDMETHODIMP CEDBS_BesondereInformation::get_Informationsart(short *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = mbArtDerInformation;

	return S_OK;
}

STDMETHODIMP CEDBS_BesondereInformation::get_Geometrie(IDispatch **pVal)
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
