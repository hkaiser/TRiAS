// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 13.02.2000 19:46:40
//
// @doc
// @module GDOFeatures.cpp | Implementation of the <c CGDOFeatures> class

#include "stdafx.h"
#include "TRiASGDOImpl.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#include "GDOFeatures.h"
#include "GDOFeature.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CGDOFeatures);

/////////////////////////////////////////////////////////////////////////////
// CGDOFeatures

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOFeatures, InitTarget
		, /*[in]SAFEARRAY(IUnknown*)*/ SAFEARRAY*, pObjects
		, /*[in]*/ VARIANT_BOOL, bWritable
)
{
	COM_TRY {
	CComSemaphore<_ThreadModel> Sem(m_lInitData);	// doppeltes Initialisieren verhindern
	MC::ArrayUnknown	arr;
		
		arr.Attach(pObjects);
		m_pDGMConnection = arr[0];
		m_pGDatabase = arr[1];
		m_bWritable = bWritable;
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASFeaturesCallback

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOFeatures, get_DefaultType, BSTR*, pbstrType) 
{
	CHECKINPOINTER(pbstrType);
	COM_TRY {
		CComBSTR bstrType(GetObjectCLSID());
		*pbstrType = bstrType.Detach();
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// 

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOFeatures, SetupFeatures, IDispatch*, pObjects, SETUPFEATURESMODE, SetupMode) 
{
	COM_TRY {
		WGDOObjects	pGDOObjects;
//		WUnknown	pUnknown;
		ERROR_FAILED_HRESULT(pObjects->QueryInterface(pGDOObjects.GetIID(), pGDOObjects.ppv()), E_FAIL);
//		ERROR_FAILED_HRESULT( BASE_OF_GDOFEATURES->QueryInterface( pUnknown.GetIID(), pUnknown.ppv() ), E_FAIL );
		ERROR_FAILED_HRESULT(pGDOObjects->SetupFeatures(this), E_FAIL);
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// alles an den Papa (IGDOObjects) delegieren da bei ihm die ganze Metadaten-
// verwaltung läuft

IMPLEMENT_DEBUG_FUNCENTRY_4(CGDOFeatures, OnCreate, VARIANT, vNameOrHandle, BSTR, bstrType, FEATURETYPE, rgType, ITRiASFeature**, ppIFeature) 
{
	CHECKOUTPOINTER(ppIFeature);
	COM_TRY {
		ERROR_EXPR_TRUE(VARIANT_FALSE == m_bWritable, GDO_E_READONLY);
		WDispatch	pDisp;
		WGDOObjects	pGDOObjects;
		WGDOFeature	pGDOFeature;
		ERROR_FAILED_HRESULT(BASE_OF_GDOFEATURES->get_Parent(pDisp.ppi()), GDO_E_NOPARENT);
		ERROR_FAILED_HRESULT(pDisp->QueryInterface(pGDOObjects.GetIID(), pGDOObjects.ppv()), E_FAIL);
		ERROR_FAILED_HRESULT(pGDOObjects->CreateFeature(this, vNameOrHandle, bstrType, rgType, pGDOFeature.ppi()), E_FAIL);
		*ppIFeature = WTRiASFeature(pGDOFeature).Detach();
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOFeatures, OnDelete, VARIANT, vWhich) 
{
	COM_TRY {
		ERROR_EXPR_TRUE(VARIANT_FALSE == m_bWritable, GDO_E_READONLY);
		WDispatch	pDisp;
		WGDOObjects	pGDOObjects;
		ERROR_FAILED_HRESULT(BASE_OF_GDOFEATURES->get_Parent(pDisp.ppi()), GDO_E_NOPARENT);
		ERROR_FAILED_HRESULT(pDisp->QueryInterface(pGDOObjects.GetIID(), pGDOObjects.ppv()), E_FAIL);
		ERROR_FAILED_HRESULT(pGDOObjects->DeleteFeature(this, vWhich), E_FAIL);
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_3(CGDOFeatures, OnChanging,/*[in]*/ CHANGEDFEATURES, rgWhat, VARIANT, vNewValue, VARIANT_BOOL*, pbDisallow) 
{
	COM_TRY {
		if (IsSemaphoreSignaled(m_lInitData, *this)) 
			return S_OK;
		switch (rgWhat)
		{
			case CHANGEDFEATURES_Name: 
			return OnChangingName(vNewValue, pbDisallow);
			case CHANGEDFEATURES_Description: 
			return OnChangingDescription(vNewValue, pbDisallow);
			case CHANGEDFEATURES_Handle: 
			return OnChangingHandle(vNewValue, pbDisallow);
		}
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOFeatures, OnChanged, CHANGEDFEATURES, rgWhat, VARIANT, vOldValue) 
{
	COM_TRY {
		if (IsSemaphoreSignaled(m_lInitData, *this)) 
			return S_OK;
		switch (rgWhat)
		{
			case CHANGEDFEATURES_Name: 
			return OnChangedName(vOldValue);
			case CHANGEDFEATURES_Description: 
			return OnChangedDescription(vOldValue);
			case CHANGEDFEATURES_Handle: 
			return OnChangedHandle(vOldValue);
			default:
				_ASSERTE(NULL);
		}
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_0(CGDOFeatures, OnFinalRelease) 
{
	return S_OK;
}

HRESULT	CGDOFeatures::OnChangingName(const VARIANT& vNewName, VARIANT_BOOL *pbDisallow) 
{
	return S_OK;
}

HRESULT CGDOFeatures::OnChangedName(const VARIANT& vOldName) 
{
	return S_OK;
}

HRESULT CGDOFeatures::OnChangingDescription(const VARIANT& vNewDescr, VARIANT_BOOL *pbDisallow) 
{
	return S_OK;
}
HRESULT CGDOFeatures::OnChangedDescription(const VARIANT& vOldValue) 
{
	return S_OK;
}

HRESULT CGDOFeatures::OnChangingHandle(const VARIANT& vNewHandle, VARIANT_BOOL* pbDisallow) 
{
	return S_OK;
}
HRESULT CGDOFeatures::OnChangedHandle(const VARIANT& vOldValue) 
{
	return S_OK;
}
