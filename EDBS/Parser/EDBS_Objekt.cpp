// OBJ_EDBS.cpp : Implementierung von CEDBS_Objekt
#include "stdafx.h"
#include "Edbs.h"
#include "EDBS_Objekt.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_Objekt

CEDBS_Objekt::CEDBS_Objekt( void )
{
 HRESULT hResult;

	mtFLOE = false;
	hResult = CComObject<CEDBS_Linien>::CreateInstance(&mpobjsLinien); 
	mpobjsLinien->AddRef();
	hResult = CComObject<CEDBS_BesondereInformationen>::CreateInstance(&mpobjsBesondereInformationen); 
	mpobjsBesondereInformationen->AddRef();
}

CEDBS_Objekt::~CEDBS_Objekt( void )
{
	if(mpobjsLinien->Release())
		ASSERT(0);
	if(mpobjsBesondereInformationen->Release())
		ASSERT(0);
}

STDMETHODIMP CEDBS_Objekt::get_Folie(short *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = msFolie;

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::put_Folie(short newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	msFolie = newVal;

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::get_Objektnummer(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CComBSTR bstrObjektnummer(mstrObjektnummer);

	*pVal = bstrObjektnummer.Detach();

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::put_Objektnummer(BSTR newVal)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mstrObjektnummer = OLE2A(newVal);

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::get_Objektart(short *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = msObjektart;

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::put_Objektart(short newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	msObjektart = newVal;

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::get_Objekttyp(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CComBSTR bstrObjekttyp(mstrObjekttyp);

	*pVal = bstrObjekttyp.Detach();

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::put_Objekttyp(BSTR newVal)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mstrObjekttyp = OLE2A(newVal);

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::get_Aktualitaet(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CComBSTR bstrAktualitaet(mstrAktualitaet);

	*pVal = bstrAktualitaet.Detach();

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::put_Aktualitaet(BSTR newVal)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mstrAktualitaet = OLE2A(newVal);

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::get_Modelltyp(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CComBSTR bstrModelltyp(mstrModelltyp);

	*pVal = bstrModelltyp.Detach();

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::put_Modelltyp(BSTR newVal)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mstrModelltyp = OLE2A(newVal);

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::get_Veraenderungskennung(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CComBSTR bstrVeraenderungskennung(mstrVeraenderungskennung);

	*pVal = bstrVeraenderungskennung.Detach();

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::put_Veraenderungskennung(BSTR newVal)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mstrVeraenderungskennung = OLE2A(newVal);

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::get_Entstehungsdatum(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CComBSTR bstrEntstehungsdatum(mstrEntstehungsdatum);

	*pVal = bstrEntstehungsdatum.Detach();

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::put_Entstehungsdatum(BSTR newVal)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mstrEntstehungsdatum = OLE2A(newVal);

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::get_Linien(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;

	hResult = mpobjsLinien->QueryInterface(IID_IEDBS_Linien,(void**)pVal);
	if( hResult )
		*pVal = NULL;
	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::get_BesondereInformationen(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

 HRESULT hResult;
	hResult = mpobjsBesondereInformationen->QueryInterface(IID_IEDBS_BesondereInformationen,(void**)pVal);
	if( hResult )
		*pVal = NULL;

	return S_OK;
}


STDMETHODIMP CEDBS_Objekt::get_GrundpunktH(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = mdblHA;

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::put_GrundpunktH(double newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mdblHA = newVal;

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::get_GrundpunktR(double *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = mdblRA;

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::put_GrundpunktR(double newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mdblRA = newVal;

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::get_FLOE(BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	*pVal = mtFLOE;

	return S_OK;
}

STDMETHODIMP CEDBS_Objekt::put_FLOE(BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	mtFLOE = newVal;

	return S_OK;
}
