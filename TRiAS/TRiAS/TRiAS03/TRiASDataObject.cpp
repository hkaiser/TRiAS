// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 30.10.2002 13:57:56 
//
// @doc
// @module TRiASDataObject.cpp | Definition of the <c CTRiASDataObject> class

#include "trias03p.hxx"
#include "trias03.h"

#include <Com/VariantHelpers.h>

#include <funcs03.h>
#include <dirisole.h>
#include <triastlb.h>
#include <igeoobjs.h>
#include <itriasap.h>		// IGetTRiASApplication
#include <oleguid.h>

#include "TRiASDataObject.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(DataObject);
DefineSmartInterface(EnumObjectsByNumber);
DefineSmartInterface(QueryGeoObjects);
DefineSmartInterface(QueryEnumLONG);
DefineSmartInterface2(DGeoObjects, IID_DGeoObjects);
DefineSmartEnumerator(LONG);
DefineSmartInterface(GetTRiASApplication);
DefineSmartInterface2(DApplication, IID_DApplication);
DefineSmartInterface2(DDocument, IID_DDocument);
DefineSmartInterface2(DGeoObjectWin, IID_DGeoObjectWin);

///////////////////////////////////////////////////////////////////////////////
// 
STDMETHODIMP CTRiASDataObject::SetObjects(DGeoObjects *pIObjs)
{
	ATLTRACE(_T("CTRiASDataObject::SetObjects\n"));

	COM_TRY {
	WDataObject DO (m_DataObj);
	__Interface<IEnumLONG> EnumObj;

		THROW_FAILED_HRESULT(WQueryEnumLONG(pIObjs) -> QueryEnumLONG(EnumObj.ppi()));
		THROW_FAILED_HRESULT(SetEnumLONGData(WEnumLONG(EnumObj), DO));

	} COM_CATCH;
	return S_OK;
}

// Implementation of GetObjects
STDMETHODIMP CTRiASDataObject::GetObjects(DGeoObjects **ppIObjs)
{
	ATLTRACE(_T("CTRiASDataObject::GetObjects\n"));
	if (NULL == ppIObjs) 
		return E_POINTER;
	*ppIObjs = NULL;

	COM_TRY {
	WDataObject DO (m_DataObj);
	WEnumObjectsByNumber EnumObj;
	WDGeoObjects Objs;

		if (S_OK == GetEnumLONGData(DO, IID_IEnumObjectsByNumber, EnumObj.ppv())) {
			THROW_FAILED_HRESULT(WQueryGeoObjects(EnumObj) -> GetGeoObjects(Objs.ppi()));
			*ppIObjs = Objs.detach();
		}

	} COM_CATCH;
	return (NULL != *ppIObjs) ? S_OK : E_FAIL;
}


// Implementation of SetData
STDMETHODIMP CTRiASDataObject::SetData(BSTR bstrName, VARIANT vData)
{
	ATLTRACE(_T("CTRiASDataObject::SetData\n"));

	USES_CONVERSION;
	COM_TRY {
	WDataObject DO (m_DataObj);
	TYMED rgTymed = (V_ISUNKNOWN(&vData) || V_ISDISPATCH(&vData)) ? 
		TYMED_HGLOBAL : TYMED_ISTREAM;
	FORMATETC fe = {
			RegisterClipboardFormat (OLE2A(bstrName)),
			NULL, DVASPECT_CONTENT, -1,	rgTymed,
		};

		THROW_FAILED_HRESULT(SetVariantData(CComVariant(vData), DO, &fe));

	} COM_CATCH;
	return S_OK;
}

// Implementation of GetData
STDMETHODIMP CTRiASDataObject::GetData(BSTR bstrName, VARIANT *pvData)
{
	ATLTRACE(_T("CTRiASDataObject::GetData\n"));
	if (NULL == pvData) 
		return E_POINTER;

	USES_CONVERSION;
	COM_TRY {
	WDataObject DO (m_DataObj);
	CComVariant vData;
	FORMATETC fe = {
			RegisterClipboardFormat (OLE2A(bstrName)),
			NULL, DVASPECT_CONTENT, -1,	TYMED_HGLOBAL|TYMED_ISTREAM,
		};

		if (FAILED(GetVariantData(DO, &fe, &vData))) 
			return E_UNEXPECTED;
		THROW_FAILED_HRESULT(vData.Detach(pvData));

	} COM_CATCH;
	return S_OK;
}


// Implementation of GetObjectWin
STDMETHODIMP CTRiASDataObject::GetObjectWin(DGeoObjectWin **ppIObjWin)
{
	ATLTRACE(_T("CTRiASDataObject::GetObjectWin\n"));
	if (NULL != ppIObjWin) 
		return E_POINTER;
	*ppIObjWin = NULL;

	COM_TRY {
	HWND hWnd = NULL;
	WDataObject DO (m_DataObj);

		if (S_OK != GetHWNDData(DO, &hWnd)) 
			return E_FAIL;

	WGetTRiASApplication GetApp (CLSID_OleAutoExtension);	//throws hr
	WDApplication App;

		THROW_FAILED_HRESULT(GetApp->GetApplication (IID_DApplication, App.ppv()));

	WDDocument Doc;
	WDGeoObjectWin Win;	

		THROW_FAILED_HRESULT(App -> get_ActiveDocument (Doc.ppi()));
		THROW_FAILED_HRESULT(Doc -> GetGeoObjectWin(CComVariant((long)hWnd), 
			vtMissing, Win.ppi()));
		*ppIObjWin = Win.detach();

	} COM_CATCH;
	return S_OK;
}

