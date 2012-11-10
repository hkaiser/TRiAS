// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 18.01.2001 08:27:53 
//
// @doc
// @module TRiASCSWktService.cpp | Definition of the <c CTRiASCSWktService> class

#include "stdafx.h"

#if defined(_USE_WKTSERVICE)

#include "TRiASCs.h"
#include "TRiASCSWktService.h"

/////////////////////////////////////////////////////////////////////////////
// CTRiASCSWktService

STDMETHODIMP CTRiASCSWktService::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASCSWktService
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// TRiASCS Objekt aus Wkt erzeugen
STDMETHODIMP CTRiASCSWktService::CreateFromWkt(WKTFORMAT rgFormat, BSTR bstrWktCS, ITRiASCS **ppICS)
{
	CHECKOUTPOINTER(ppICS);
	CHECKINPOINTER(bstrWktCS);

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// aus TRiASCS Wkt erzeugen
STDMETHODIMP CTRiASCSWktService::ExportAsWkt(WKTFORMAT rgFormat, ITRiASCS *pCS, BSTR *pbstrWktCS)
{
	CHECKOUTPOINTER(pbstrWktCS);
	CHECKINPOINTER(pCS);

	if (WKTFORMAT_OgcWkt != rgFormat)
		return E_INVALIDARG;

	COM_TRY {
	// ist's einprojektives System
	CComBSTR bstrWkt;
	CComBSTR bstr;
	TRIASCSTYPE rgType;
	WTRiASCSPCS PCS;

		THROW_FAILED_HRESULT(pCS -> get_CoordSystemType(&rgType));
		if (tcsCS_Projected == rgType) {
			bstrWkt.Append(L"PROJCS[\"");

		// Namen der Projektion ausgeben
			THROW_FAILED_HRESULT(RetrieveProjectedName (pCS, CLEARED(&bstr)));
			bstrWkt.Append(bstr);
		}

	// Datumsbeschreibung ausgeben
	WTRiASCSGCS GCS;

		THROW_FAILED_HRESULT(pCS -> get_GeographicCS(GCS.ppi()));
		THROW_FAILED_HRESULT(ExportGeographicSystem(GCS, CLEARED(&bstr)));
		bstrWkt.Append(bstr);

	// ggf. Projektionsparameter ausgeben
		if (tcsCS_Projected == rgType) {
			_ASSERTE(PCS.IsValid());

			THROW_FAILED_HRESULT(ExportProjectionParams(PCS, CLEARED(&bstr)));
			bstrWkt.Append(bstr);
			bstrWkt.Append(L"]");
		}

	// Resultat liefern
		*pbstrWktCS = bstrWkt.Detach();

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSWktService::RetrieveProjectedName (ITRiASCS *pICS, BSTR *pbstrName)
{
	COM_TRY {
	// projektives System holen
	WTRiASCSPCS PCS;

		THROW_FAILED_HRESULT(pICS -> get_ProjectedCS(PCS.ppi()));

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSWktService::ExportGeographicSystem (ITRiASCSGCS *pIGCS, BSTR *pbstrGCS)
{
	CHECKOUTPOINTER(pbstrGCS);

	COM_TRY {
	CComBSTR bstrWkt;

		bstrWkt.Append(L"GEOGCS[\"");


		bstrWkt.Append(L"]");
		*pbstrGCS = bstrWkt.Detach();

	} COM_CATCH;
	return S_OK;
}

HRESULT CTRiASCSWktService::ExportProjectionParams (ITRiASCSPCS *pIPCS, BSTR *pbstrParams)
{
	return S_OK;
}

#endif // defined(_USE_WKTSERVICE)
