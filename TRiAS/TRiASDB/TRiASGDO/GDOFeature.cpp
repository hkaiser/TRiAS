/////////////////////////////////////////////////////////////////////////////
// @doc
// @module GDOFeature.cpp | Implementation of the <c CGDOFeature> class

#include "stdafx.h"
#include "TRiASGDOImpl.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#include "GDOFeature.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CGDOFeature);

//HRESULT CGDOFeature::CreateInstance( IGDOFeature** ppFeature ) {
//	CComObject<CGDOFeature>	*pFeature = NULL;
//	RETURN_FAILED_HRESULT( CComObject<CGDOFeature>::CreateInstance( &pFeature ) );
//	(*ppFeature = pFeature)->AddRef();
//	return S_OK;
//}

/////////////////////////////////////////////////////////////////////////////
// IGDOFeature

IMPLEMENT_DEBUG_FUNCENTRY_6(CGDOFeature,InitTarget,
		, /*[in]SAFEARRAY(IUnknown*)*/ SAFEARRAY*, pObjects
		, /*[in]*/ VARIANT_BOOL, bWritable
		, /*[in]*/ DWORD, dwTypeOfFeature
		, /*[in]*/ BSTR, strMCode
		, /*[in]*/ BSTR, strFieldname
		, /*[in]*/ BSTR, strFeaturename
	)
{
	COM_TRY {
	CComSemaphore<_ThreadModel> Sem (m_lInitData);	// doppeltes Initialisieren verhindern
	MC::ArrayUnknown	arr;

		arr.Attach(pObjects);
		m_pDGMConnection = arr[0];
		//m_pGDatabase = arr[0];
		//m_pMetadataService = arr[1];
		m_bWritable = bWritable;
		m_strFieldname = strFieldname;				// der wirkliche Feldname!!
		m_strMCode = strMCode;

	WDispatch	pDisp;

		EXT_ERROR_FAILED_HRESULT( m_pDGMConnection->get_Database( pDisp.ppi() ), E_FAIL );
		m_pGDatabase = pDisp;

	WGField	pGField;

		ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );

	/////////////////////////////////////////////////////////////////////////////
	// Eigenschaften anpassen
	long			fldAttribs;
	short			fldType;
	VARIANT_BOOL	fldRequired;
	VARIANT_BOOL	fldAllowZero;

		EXT_ERROR_FAILED_HRESULT( pGField->get_Type( &fldType ), E_FAIL );
		EXT_ERROR_FAILED_HRESULT( pGField->get_Attributes( &fldAttribs ), E_FAIL );
		EXT_ERROR_FAILED_HRESULT( pGField->get_Required( &fldRequired ), E_FAIL );
		EXT_ERROR_FAILED_HRESULT( pGField->get_AllowZeroLength( &fldAllowZero ), E_FAIL );
		if( fldAttribs & gdbAutoIncrField ) {
			dwTypeOfFeature |= (FEATURETYPE_System | FEATURETYPE_ReadOnly);
			m_bWritable = VARIANT_FALSE;
		} 
		else if( gdbSpatial == fldType || gdbGraphic == fldType ) {
			dwTypeOfFeature |= FEATURETYPE_System;
			long	lGeomType;
			EXT_ERROR_FAILED_HRESULT( pGField->get_SubType( &lGeomType ), E_FAIL );
			WGDODatabase	pGDODatabase;
			ERROR_FAILED_HRESULT( FindSpecificParent( GetUnknown(), pGDODatabase.GetIID(), pGDODatabase.ppv() ), E_FAIL );
			ERROR_FAILED_HRESULT( pGDODatabase->GetDefaultGeometry( lGeomType, CLEARED(m_vDefault) ), E_FAIL );
			m_bIsGeoFeature = true;
		} 
		else {
			CComBSTR	vFldDefault;
			if( SUCCEEDED( pGField->get_DefaultValue( CLEARED(vFldDefault)) ) )
				m_vDefault = vFldDefault;
		}
		if( !m_bWritable ) 
			dwTypeOfFeature |= FEATURETYPE_ReadOnly;

		RETURN_FAILED_HRESULT(BASE_OF_GDOFEATURE->put_Name( strFeaturename ) );
		RETURN_FAILED_HRESULT(BASE_OF_GDOFEATURE->put_Type( (FEATURETYPE) dwTypeOfFeature ) );

	} COM_CATCH;
	return S_OK;
}

HRESULT CGDOFeature::EvalDefaultValue( CComVariant& vDefaultValue ) {
	WGField	pGField;
	ERROR_FAILED_HRESULT( GetGField( pGField ), E_FAIL );
	long			fldAttribs;
	short			fldType;
	VARIANT_BOOL	fldRequired;
	VARIANT_BOOL	fldAllowZero;
	EXT_ERROR_FAILED_HRESULT( pGField->get_Type( &fldType ), E_FAIL );
	EXT_ERROR_FAILED_HRESULT( pGField->get_Attributes( &fldAttribs ), E_FAIL );
	EXT_ERROR_FAILED_HRESULT( pGField->get_Required( &fldRequired ), E_FAIL );
	EXT_ERROR_FAILED_HRESULT( pGField->get_AllowZeroLength( &fldAllowZero ), E_FAIL );
	if( fldAttribs & gdbAutoIncrField ) {
		vDefaultValue.ChangeType( VT_NULL);
	} else if( gdbSpatial == fldType || gdbGraphic == fldType ) {
		ERROR_EXPR_FALSE( V_ISARRAY(&m_vDefault) && V_ISUI1(&m_vDefault), E_FAIL );
		vDefaultValue = m_vDefault;
	} else if( 0 == fldRequired ) {
		vDefaultValue.ChangeType( VT_NULL );
	} else {
		CComBSTR	vFldDefault;
		if( SUCCEEDED( pGField->get_DefaultValue( CLEARED(vFldDefault)) ) )
			vDefaultValue = vFldDefault;
	}
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOFeature,get_Fieldname,/*[out, retval]*/ BSTR*, pVal) 
{
	CHECKOUTPOINTER(pVal);
	*pVal = ::SysAllocString (m_strFieldname);
	if (NULL == *pVal)
		return E_OUTOFMEMORY;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOFeature,put_Fieldname,/*[in]*/ BSTR, pVal) 
{
	CHECKINPOINTER(pVal);
	COM_TRY {
	CComBSTRChangeHelper helper(m_strFieldname);
	
		m_strFieldname = pVal;

	// Feldname wurde vom Papa (GDOObjects) geändert;
	// jetzt noch mal überprüfen ob alles korrekt ist
	WGField	pGField;

		RETURN_FAILED_HRESULT(GetGField(pGField));
		helper.Succeeded();
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOFeature,get_FieldValue,/*[out, retval]*/ VARIANT*, pVal) 
{
	CHECKOUTPOINTER(pVal);

CComVariant	vValue(m_vValue);

	vValue.Detach(pVal);
	return S_OK;
}
IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOFeature,put_FieldValue,/*[in]*/ VARIANT, vValue ) 
{
	m_vValue = vValue;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASFeatureCallback

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOFeature,get_DefaultType,/*[out, retval]*/BSTR*, pbstrType) {
	CHECKOUTPOINTER(pbstrType);
	COM_TRY {
		CComBSTR bstrType(GetObjectCLSID());
		*pbstrType = bstrType.Detach();
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOFeature,SetupFeature,SETUPFEATUREMODE, rgMode) 
{
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_3(CGDOFeature,OnChanging 
		, /*[in]*/ CHANGEDFEATURE, rgWhat
		, /*[in]*/ VARIANT, vNewValue
		, /*[in,out]*/ VARIANT_BOOL*, pbDisallow
		)
{
	if (IsSemaphoreSignaled (m_lInitData, *this)) 
		return S_OK;
	CHECKOUTPOINTER(pbDisallow);
	COM_TRY {
		switch (rgWhat) {
		case CHANGEDFEATURE_Name: 
			return OnChangingName(vNewValue, pbDisallow);

		case CHANGEDFEATURE_Description: 
			return OnChangingDescription(vNewValue, pbDisallow);

		case CHANGEDFEATURE_Handle: 
			return OnChangingHandle(vNewValue, pbDisallow);

		case CHANGEDFEATURE_Type:
			break;
		
		default:
			_ASSERTE(FALSE);
			break;
		}

	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOFeature,OnChanged, CHANGEDFEATURE, rgWhat, VARIANT, vOldValue) 
{
	if (IsSemaphoreSignaled (m_lInitData, *this)) 
		return S_OK;

	COM_TRY {
		switch (rgWhat) {
		case CHANGEDFEATURE_Name: 
			return OnChangedName(vOldValue); 

		case CHANGEDFEATURE_Description: 
			return OnChangedDescription(vOldValue);

		case CHANGEDFEATURE_Handle: 
			return OnChangedHandle(vOldValue);

		case CHANGEDFEATURE_Type:
			break;

		default:
			_ASSERTE(FALSE);
			break;
		}
	} COM_CATCH;
	return S_OK;
}

HRESULT CGDOFeature::OnChangingName( const VARIANT& vNewName, VARIANT_BOOL *pbDisallow ) {
	*pbDisallow = VARIANT_TRUE;
	CComVariant	v( vNewName );
	WIN_ERROR_NOTSUCCESS( v.ChangeType( VT_BSTR ), GDO_E_COERCE );
	ERROR_FAILED_HRESULT( ParseName(V_BSTR(&v)), GDO_E_INVALIDNAME );
	*pbDisallow = VARIANT_FALSE;
	return S_OK;
}

HRESULT CGDOFeature::OnChangedName( const VARIANT& vOldName ) {
	WGDOObjects	gdoObjs;
	RETURN_FAILED_HRESULT( FindSpecificParent( GetUnknown(), gdoObjs.GetIID(), gdoObjs.ppv() ) );
	ERROR_FAILED_HRESULT( gdoObjs->RenameFeature( this, vOldName ), E_FAIL );
	return S_OK;
}

HRESULT CGDOFeature::OnChangingDescription( const VARIANT& vNewDescr, VARIANT_BOOL *pbDisallow ) {
	*pbDisallow = VARIANT_FALSE;
	return S_OK;
}

HRESULT CGDOFeature::OnChangedDescription( const VARIANT& vOldValue ) {
	WGDOObjects	gdoObjs;
	RETURN_FAILED_HRESULT( FindSpecificParent( GetUnknown(), gdoObjs.GetIID(), gdoObjs.ppv() ) );
	ERROR_FAILED_HRESULT( gdoObjs->RedescribeFeature( this ), E_FAIL );
	return S_OK;
}

HRESULT CGDOFeature::OnChangingHandle( const VARIANT& vNewHandle, VARIANT_BOOL *pbDisallow ) {
	return S_OK;
}

HRESULT CGDOFeature::OnChangedHandle( const VARIANT& vOldValue ) {
	return S_OK;
}

STDMETHODIMP CGDOFeature::get_MCode(BSTR *pVal) {
	CHECKOUTPOINTER(pVal);
	COM_TRY {
		CComBSTR	strMCode(m_strMCode);
		*pVal = strMCode.Detach();
	} COM_CATCH
	return S_OK;
}

STDMETHODIMP CGDOFeature::put_MCode(BSTR newVal) {
	if (IsSemaphoreSignaled (m_lInitData, *this)) 
		return S_OK;
	COM_TRY {
		CComVariant	vOldMCode(m_strMCode);
		WGDOObjects	gdoObjs;
		RETURN_FAILED_HRESULT( FindSpecificParent( GetUnknown(), gdoObjs.GetIID(), gdoObjs.ppv() ) );
		m_strMCode = newVal;
		ERROR_FAILED_HRESULT( gdoObjs->ReclassFeature( this, vOldMCode ), E_FAIL );
	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOFeature,Update,/*[in]*/ITRiASObject*, pTRiASObject,/*[in]*/VARIANT, newValue) 
{
	CHECKINPOINTER(pTRiASObject);
	ERROR_EXPR_TRUE(!m_bWritable, GDO_E_READONLY);

	COM_TRY {
	WTRiASObjects pTRiASObjects;

		ERROR_FAILED_HRESULT(FindSpecificParent (GetUnknown(), pTRiASObjects.ppi()), E_FAIL);

	WGDOObjects pGDOObjects (pTRiASObjects);
	WGDOObject pGDOObject (pTRiASObject);
	CComBSTR strPKeyname;
	CComBSTR strFeaturename;

		ERROR_FAILED_HRESULT(BASE_OF_GDOFEATURE -> get_Name (CLEARED(strFeaturename)), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASObjects -> get_PrimaryKey (CLEARED(strPKeyname)), E_FAIL);

		if (m_bIsGeoFeature) {
		// Geometrie schreiben
			ERROR_EXPR_FALSE(V_ISDISPATCH(&newValue), E_FAIL);

		WGDODatabase pGDODatabase;
			
			RETURN_FAILED_HRESULT(FindSpecificParent (GetUnknown(), pGDODatabase.ppi()));
			RETURN_FAILED_HRESULT(pGDODatabase -> UpdateGeometry (pGDOObjects, pGDOObject, this, newValue));
		} 
		else if (strFeaturename == strPKeyname) {
		// wenn PKey aktualisiert werden soll, dann über Änderung des Namens
			if (V_ISNULL(&newValue) || V_ISEMPTY(&newValue) || V_ISERROR(&newValue)) 
				return S_FALSE;

		CComVariant	vObjName (newValue);

			WIN_ERROR_NOTSUCCESS(vObjName.ChangeType (VT_BSTR), GDO_E_COERCE);
			ERROR_FAILED_HRESULT(pTRiASObject->put_Name (V_BSTR(&vObjName)), E_FAIL);
		} 
		else {
		// sonstiges Attribut: Objektklasse ist verantwortlich
			ERROR_FAILED_HRESULT (pGDOObjects -> UpdateFeature (this, pGDOObject, newValue), E_FAIL);
		} 
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Eval: Das, worum es eigentlich geht ...

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOFeature,Eval,/*[in]*/ITRiASObject*, pObj,/*[out, retval]*/VARIANT*, pVal) 
{
	CHECKINPOINTER(pObj);
	CHECKINPOINTER(pVal);
	COM_TRY {
	MC::ArrayVariant sa (MC::Dim(1));
	
		sa.Lock();
	
	SAFEARRAY *psa = &sa;
	
		return EvalEx(pObj, &psa, pVal);
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_3(CGDOFeature,EvalEx,/*[in]*/ITRiASObject*, pTRiASObject, 
	/*[in, out]*/SAFEARRAY**, ppConstraints,/*[out, retval]*/VARIANT*, pValue) 
{
	CHECKINPOINTER(pTRiASObject);
	CHECKINPOINTER(pValue);

	COM_TRY {
		if (m_bIsGeoFeature) {
		// Geometrie einlesen: Datenbank ist verantwortlich
		WGDODatabase pGDODatabase;
		WGDOObjects pGDOObjects;
		WGDOObject pGDOObject (pTRiASObject);

			RETURN_FAILED_HRESULT(FindSpecificParent (GetUnknown(), pGDOObjects.ppi()));
			RETURN_FAILED_HRESULT(FindSpecificParent (pGDOObjects, pGDODatabase.ppi()));
			RETURN_FAILED_HRESULT(pGDODatabase -> QueryGeometry (pGDOObjects, pGDOObject, 
				this, ppConstraints, pValue));
		} 
		else {
		// Wert abfragen: Objektklasse ist verantwortlich
		WGDOObjects pGDOObjects;
		WGDOObject pGDOObject (pTRiASObject);

			ERROR_FAILED_HRESULT(FindSpecificParent (GetUnknown(), pGDOObjects.ppi()), E_FAIL);
			ERROR_FAILED_HRESULT(pGDOObjects -> QueryFeature (this, pGDOObject, pValue), E_FAIL);
			_ASSERTE(!V_ISEMPTY(&m_vValue));	// sollte jetzt gecached sein

#pragma TODO("Kann ich wirklich nicht ermitteln ob ein Feature zu einem Objekt gehört????")
#if defined(_0_)
		// Wenn das Feature direkt einem Objekt gehört ist der Wert in m_vValue gecacht
		// (nicht VT_EMPTY) kann also sofort rausgegeben werden. 
		// Diese Bedingung wird aber erst noch mal eingehend begutachtet
			HRESULT	hr;
			WTRiASFeatures	pTRiASFeatures;
			WTRiASObjects	pTRiASObjects;
			hr = FindSpecificParent( GetUnknown(), pTRiASObjects.GetIID(), pTRiASObjects.ppv() );
			RETURN_FAILED_HRESULT( pTRiASObjects->get_Features( pTRiASFeatures.ppi() ) );
			WDispatch	pDispatch;
			if( V_ISEMPTY(&m_vValue) ) {
				WGDOObjects	pGDOObjects;
				RETURN_FAILED_HRESULT( pTRiASFeatures->get_RelatedObject( pDispatch.ppi() ) );
				HRESULT hr = pDispatch->QueryInterface( pGDOObjects.GetIID(), pGDOObjects.ppv() );
				_ASSERTE(SUCCEEDED(hr));
			} else {
				WGDOObject	pGDOObject;
				RETURN_FAILED_HRESULT( pTRiASFeatures->get_RelatedObject( pDispatch.ppi() ) );
				HRESULT hr = pDispatch->QueryInterface( pGDOObject.GetIID(), pGDOObject.ppv() );
				_ASSERTE(SUCCEEDED(hr));
			}
#endif
		}
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOFeature,Clone, ITRiASFeature**, NewFeat ) 
{
	FUNC_NOT_IMPL();
}

IMPLEMENT_DEBUG_FUNCENTRY_0(CGDOFeature, OnFinalRelease) 
{
	COM_TRY {
	// aus Objects-Tabelle entfernen
	LONG lHandle = 0;

		if (SUCCEEDED(GetHandle (&lHandle)) && 0 != lHandle) {
		WTRiASObjects Parent;

			if (SUCCEEDED(FindSpecificParent (m_BaseUnk, Parent.ppi()))) {
			WTRiASObjectHandleMap Map (GetPropertyFrom (Parent, g_cbGenericMap, (IDispatch *)NULL), false);

				if (Map.IsValid()) 
					Map -> RemoveObject (lHandle, OBJECTMAPMODE_RemoveThisReference);
			}
		}
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Helferfunktionen

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOFeature,get_DefaultValue, VARIANT*, pVal) 
{
	CHECKINPOINTER(pVal);
	COM_TRY {
		CComVariant	vDefaultValue;
		ERROR_FAILED_HRESULT( EvalDefaultValue( vDefaultValue ), E_FAIL );
		ERROR_FAILED_HRESULT( vDefaultValue.Detach(pVal), E_FAIL );
	} COM_CATCH;
	return S_OK;
}
