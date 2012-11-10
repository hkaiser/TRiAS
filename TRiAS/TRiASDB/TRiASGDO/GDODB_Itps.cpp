#include "stdafx.h"
#include "TRiASGDOImpl.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#include "GDODatabase.h"

DefineSmartInterface(TRiASPropertyCallback);

/////////////////////////////////////////////////////////////////////////////
// CGDODatabase
// (I)(T)RiAS(P)roperty(S)upport

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDODatabase,CreateProperty, BSTR, Which, ITRiASProperty**, ppProperty ) {
	CHECKOUTPOINTER(ppProperty);
	USES_CONVERSION;
	COM_TRY {
		VARIANT_BOOL fVal = VARIANT_FALSE;
		RETURN_FAILED_HRESULT( Fire_CreatingProperty (Which,&fVal) );
		if (VARIANT_FALSE != fVal)
			return S_FALSE;
		RETURN_FAILED_HRESULT( Fire_PropertyToCreate(Which) );
		WTRiASProperty New(CLSID_TRiASProperty);
		WTRiASPropertyCallback Supp;
		RETURN_FAILED_HRESULT( New -> put_Name(Which) );
		RETURN_FAILED_HRESULT( GetPropertySupportSite(Which, GetUnknown(), this, Supp.ppi()) );
		RETURN_FAILED_HRESULT( WObjectWithSite(New)->SetSite(Supp) );		// using IObjectWithSite
		*ppProperty = New.detach();
		RETURN_FAILED_HRESULT( Fire_PropertyCreated (*ppProperty) );
	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase,RemoveProperty,BSTR, Which) {
	USES_CONVERSION;
	COM_TRY {
#pragma TODO("Property löschen - ist das richtig so?????")
		VARIANT_BOOL fVal = VARIANT_FALSE;
		RETURN_FAILED_HRESULT( Fire_DeletingProperty (Which, &fVal) );
		if (VARIANT_FALSE != fVal)
			return S_FALSE;
		RETURN_FAILED_HRESULT( Fire_PropertyToDelete (Which) );
		RETURN_FAILED_HRESULT( Fire_PropertyDeleted (Which) );
	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDODatabase,PutValue,BSTR, Which, VARIANT, Value) {
	CHECKINPOINTER(Which);
	COM_TRY {
	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDODatabase,GetValue,BSTR, Which, VARIANT*, pVal) {
	CHECKINPOINTER(Which);
	CHECKINPOINTER(pVal);
	COM_TRY {
	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDODatabase,PutType,BSTR, Which, PROPERTY_TYPE, Type) {
	CHECKINPOINTER(Which);
	COM_TRY {
	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDODatabase,GetType,BSTR, Which, PROPERTY_TYPE*, pType) {
	CHECKINPOINTER(Which);
	CHECKINPOINTER(pType);
	COM_TRY {
	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_3(CGDODatabase,PutValueAndType,BSTR, Which, VARIANT, Val, PROPERTY_TYPE, Type) {
	CHECKINPOINTER(Which);
	COM_TRY {
		VARIANT_BOOL fVal = VARIANT_FALSE;
		RETURN_FAILED_HRESULT( Fire_ModifyingProperty (Which, &fVal) );
		if( VARIANT_FALSE != fVal)
			return S_FALSE;
		RETURN_FAILED_HRESULT( Fire_PropertyToModify (Which) );
		RETURN_FAILED_HRESULT( Fire_PropertyModified (Which) );
	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, Refresh, BSTR, Name) {
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_3(CGDODatabase,GetValueAndType,BSTR, Which, VARIANT*, pVal, PROPERTY_TYPE*, pType) {
	CHECKINPOINTER(Which);
	CHECKINPOINTER(pVal);
	CHECKINPOINTER(pType);
	COM_TRY {
	} COM_CATCH;
	return S_OK;
}
