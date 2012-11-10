// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 08.02.2000 00:49:24
//
// @doc
// @module GDOObjects.cpp | Implementation of the <c CGDOObjects> class

#include "stdafx.h"
#include "TRiASGDOImpl.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#include "GDODBEngine.h"
#include "GDOObjects.h"
#include "GDOObject.h"
#include "GDOFeature.h"
#include "GDOFeatures.h"

// HRESULT CGDOObjects::CreateInstance( IGDOObjects** ppObjects ) {
//	CComObject<CGDOObjects>	*pObjects = NULL;
//	RETURN_FAILED_HRESULT( CComObject<CGDOObjects>::CreateInstance( &pObjects ) );
//	(*ppObjects = pObjects) -> AddRef();
//	return S_OK;
//}

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASPropertyMapHandler);

///////////////////////////////////////////////////////////////////////////////
// ClassFactorycache benutzen
#if defined(_USE_CLASSFACTORY_CACHE)
typedef CClassFactoryCache < &CLSID_GDOObject> CGDOObjectFactory;
CGDOObjectFactory MakeGDOObject;
typedef CClassFactoryCache < &CLSID_GDOFeature> CGDOFeatureFactory;
CGDOFeatureFactory MakeGDOFeature;
#endif // defined(_USE_CLASSFACTORY_CACHE)

/////////////////////////////////////////////////////////////////////////////
// IGDOObjects

IMPLEMENT_DEBUG_FUNCENTRY_6(CGDOObjects, InitTarget
		, /*[in]SAFEARRAY(IUnknown*)*/ SAFEARRAY*, pObjects
		, /*[in]*/ VARIANT_BOOL, bWritable
		, /*[in]*/ long, objsTypes
		, /*[in]*/ BSTR, strOKS
		, /*[in]*/ BSTR, strTablename
		, /*[in]*/ BSTR, strClassname
)
{
	CComBSTR	strDescription(L"");
	return InitTarget(pObjects, bWritable, objsTypes, strOKS, strTablename, strClassname, strDescription);
}

IMPLEMENT_DEBUG_FUNCENTRY_7(CGDOObjects, InitTarget
		, /*[in]SAFEARRAY(IUnknown*)*/ SAFEARRAY*, pObjects
		, /*[in]*/ VARIANT_BOOL, bWritable
		, /*[in]*/ long, objsTypes
		, /*[in]*/ BSTR, strOKS
		, /*[in]*/ BSTR, strTablename
		, /*[in]*/ BSTR, strClassname
		, /*[in]*/ BSTR, strDescription
)
{
	COM_TRY {
	// jetzt sonstige Initialisierung
	CComSemaphore<_ThreadModel>	Sem(m_lInitData);	// doppeltes Initialisieren verhindern
	MC::ArrayUnknown arr;

		arr.Attach(pObjects);
		m_pDGMConnection = arr[0];
		m_pGDatabase = arr[1];
		m_pDGMCoordSystemsMgr = arr[2];

		m_bWritable = bWritable ? true : false;
		m_strTablename = strTablename;

		RETURN_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> _Reset());

		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> put_OKS(strOKS), E_FAIL);
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> put_Name(strClassname), E_FAIL);
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> put_Types((OBJECTTYPE) objsTypes), E_FAIL);
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> put_CollectionType(OBJECTSCOLLECTIONTYPE_Class), E_FAIL);
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> put_Description(strDescription), E_FAIL);

	// MetaDataService ist an der Connection gespeichert
	WTRiASConnection Conn;

		ERROR_FAILED_HRESULT(FindSpecificParent(GetUnknown(), Conn.ppi()), E_FAIL);

	WTRiASPropertyBase PropBase (Conn);
	WTRiASMDSMap MDSMap (GetPropertyFrom (PropBase, m_strTablename, (IDispatch *)NULL), false);

		if (!MDSMap.IsValid())
		{
			MDSMap.CreateInstance (CLSID_TRiASMDSMap);
			SetPropertyBy(PropBase, m_strTablename, MDSMap, true);
		}
		m_pTRiASMDSMap = MDSMap;

	// FeatureMap ist an der Objektklasse (hier) gespeichert
	WTRiASObjectHandleMap FeatMap(GetPropertyFrom (BASE_OF_GDOOBJECTS(), 
		g_cbGenericMap, (IDispatch *)NULL), false);		// GetProperty liefert AddRef'ed ab

		m_pTRiASFeatureHandleMap = FeatMap;

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ein Objekt aus meiner Klasse möchte seine Eigenschaften haben...
// Features bezogen auf ein Objekt zusamenstellen
IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOObjects, CreateFeatures
	, /*[in]*/ IGDOObject*, pGDOObject
	, /*[in]*/ IGDOFeatures**, ppGDOFeatures
)
{
	CHECKINPOINTER(pGDOObject);
	CHECKOUTPOINTER(ppGDOFeatures);
	COM_TRY {
	// Features erzeugen...
	WGDOFeatures pGDOFeatures;

		ERROR_FAILED_HRESULT(CGDOFeatures::CreateInstance(pGDOFeatures.ppi()), E_FAIL);
	
	MC::ArrayUnknown arr(2);
	
		arr[0] = WUnknown(m_pDGMConnection).detach();
		arr[1] = WUnknown(m_pGDatabase).detach();
		ERROR_FAILED_HRESULT(pGDOFeatures -> InitTarget(&arr, CComBool(m_bWritable)), OBS_E_INITFEATURES);

	// ...und einlesen
	WTRiASFeatures pTRiASFeatures (pGDOFeatures);
	CComBSTR strPrimaryfeature;
	CComBSTR strPrimarygeometry;

		ERROR_FAILED_HRESULT(ReloadFeatures(pTRiASFeatures, strPrimaryfeature, NULL, strPrimarygeometry), E_FAIL);
//		ERROR_FAILED_HRESULT(QueryFeatures(pTRiASFeatures, pGDOObject), E_FAIL);
		*ppGDOFeatures = pGDOFeatures.Detach();
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOObjects, SetupFeatures
		, /*[in]*/ IGDOFeatures*, pGDOFeatures
)
{
	CHECKINPOINTER(pGDOFeatures);
	COM_TRY {
	WTRiASFeatures	pTRiASFeatures;
	CComBSTR		strPrimaryfeature;
	CComBSTR		strPrimarygeometry;

		ERROR_FAILED_HRESULT(pGDOFeatures -> QueryInterface(pTRiASFeatures.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(ReloadFeatures(pTRiASFeatures, strPrimaryfeature, NULL, strPrimarygeometry), E_FAIL);
	} COM_CATCH
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// eine neue Eigenschaft erstellen

IMPLEMENT_DEBUG_FUNCENTRY_5(CGDOObjects, CreateFeature
		, /*[in]*/ IGDOFeatures*, pGDOFeatures
		, /*[in]*/ VARIANT, vNameOrHandle
		, /*[in]*/ BSTR, bstrType
		, /*[in]*/ long, lType
		, /*[out, retval]*/ IGDOFeature**, ppIGDOFeature
)
{
	ERROR_EXPR_TRUE(!m_bWritable, GDO_E_READONLY);

	COM_TRY {
	CComBSTR	strFeaturename;
	CComBSTR	strFieldname;
	
		if (V_ISBSTR(&vNameOrHandle))
		{
			strFeaturename = V_BSTR(&vNameOrHandle);
		} 
		else if (V_ISINTEGER(&vNameOrHandle)) {
			CComVariant	v(vNameOrHandle);
			WIN_ERROR_NOTSUCCESS(v.ChangeType(VT_BSTR), GDO_E_INVALIDHANDLE);
			strFeaturename = V_BSTR(&v);
		} 
		else {
			MAKE_ERROR(GDO_E_INVALIDHANDLE);
		}
		NormalizeName(strFeaturename, strFieldname);

	WGTableDef	pGTableDef;
	W_MetadataService	pMetadataService(CLSID_MetadataService);
	IDispatch	*pRawDisp = m_pDGMConnection;

		EXT_ERROR_FAILED_HRESULT(pMetadataService -> putref_Connection(&pRawDisp), NDB_E_NATIVEDB);

		RETURN_FAILED_HRESULT(GetGTableDef(pGTableDef));
		{
		// (1) versuchen Feld in der Tabelle zu erzeugen
			DBTransaction	dbTrans(m_pGDatabase);
			WGField		pGField;
			WGFields	pGFields;
			EXT_ERROR_FAILED_HRESULT(pGTableDef -> CreateField(CComVariant(strFieldname), CComVariant(gdbText), CComVariant(255), pGField.ppi()), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(pGField -> put_AllowZeroLength(VARIANT_TRUE), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(pGTableDef -> get_GFields(pGFields.ppi()), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(pGFields -> Append(pGField), NDB_E_NATIVEDB);

		// (2) GDO-Metadaten nachziehen
			long	lValid;
			W_FieldProperty	fldProp(CLSID_FieldProperty); 
			IDispatch		*pDisp = fldProp;		// kein QI, kein AddRef() !!
			VARIANT_BOOL	bTrue(VARIANT_TRUE);
			EXT_ERROR_FAILED_HRESULT(pMetadataService -> put_TableName(&m_strTablename), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(fldProp -> put_Name(&strFieldname), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(fldProp -> put_Displayable(&bTrue), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(pMetadataService -> AddFieldMetadata(&pDisp, &lValid), NDB_E_NATIVEDB);
			dbTrans.Succeeded();
		}

	// (3) wenn wir hier sind sieht's gut aus, also Feature im TRiAS anlegen
		CComBSTR		strMCode(_T("0"));
		CComVariant		vData;
		m_pTRiASMDSMap -> SetAt(strMCode, strFieldname, strFeaturename, CComBSTR(_T("")), vData);
		WTRiASFeatures	pTRiASFeatures(pGDOFeatures);
		WTRiASFeature	pTRiASFeature;
		RETURN_FAILED_HRESULT(GetOrCreateFeature(strFieldname, strFeaturename, strMCode, lType, 
			pTRiASFeatures, pTRiASFeature.ppi()));
		ERROR_FAILED_HRESULT(pTRiASFeature -> QueryInterface(ppIGDOFeature), E_FAIL);
	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOObjects, DeleteFeature
		, /*[in]*/ IGDOFeatures*, pGDOFeatures
		, /*[in]*/ VARIANT, vNameOrHandle
)
{
	COM_TRY {
	CComBSTR	strMCode;
	CComBSTR	strToSearch;
	CComBSTR	strFieldname;
	CComBSTR	strFeaturename;
	CComBSTR	strDescription;
	CComVariant	vData;
	CComBSTR	strPKey;
	CComBSTR	strPGeom;
	long		lMode = lSearchName;

		if (V_ISBSTR(&vNameOrHandle)) {
			NormalizeName(V_BSTR(&vNameOrHandle), strToSearch);
//			lMode = lSearchName;
		} 
		else if (V_ISINTEGER(&vNameOrHandle)) {
		CComVariant	v(vNameOrHandle);
		
			WIN_ERROR_NOTSUCCESS(v.ChangeType(VT_BSTR), GDO_E_COERCE);
			NormalizeName(V_BSTR(&v), strToSearch);
			lMode = lSearchKey;
		}
		ERROR_FAILED_HRESULT(SearchMDSMap(m_pTRiASMDSMap, strToSearch, strMCode, lMode), E_FAIL);
		m_pTRiASMDSMap -> GetAt(strMCode, CLEARED(strFieldname), CLEARED(strFeaturename), 
			CLEARED(strDescription), CLEARED(vData));

		BASE_OF_GDOOBJECTS() -> get_PrimaryKey(CLEARED(strPKey));
		BASE_OF_GDOOBJECTS() -> get_DefaultGeometry(CLEARED(strPGeom));
		ERROR_EXPR_TRUE(strPKey == strFeaturename || strPGeom == strFeaturename, OBS_E_PKEYNOTDELETABLE);

	// nicht aus der Map löschen, das passiert, wenn überhaupt erst beim Speichern
		m_strFeaturesToDelete.insert(strMCode, true);

	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOObjects, RenameFeature
	, /*[in]*/ IGDOFeature*, pGDOFeature
	, /*[in]*/ VARIANT, vOldname
)
{
	CHECKINPOINTER(pGDOFeature);
	COM_TRY {
		ERROR_EXPR_FALSE(V_ISBSTR(&vOldname), GDO_E_COERCE);
		WTRiASFeature	pTRiASFeature;
		ERROR_FAILED_HRESULT(pGDOFeature -> QueryInterface(pTRiASFeature.ppi()), E_FAIL);

	CComBSTR	strMCode;
	CComBSTR	strFieldname;
	CComBSTR	strFeaturename;
	CComBSTR	strDescription;
	CComVariant	vData;

		ERROR_FAILED_HRESULT(pGDOFeature -> get_MCode(CLEARED(strMCode)), E_FAIL);
		if (SUCCEEDED(m_pTRiASMDSMap -> GetAt(strMCode, CLEARED(strFieldname), 
			CLEARED(strFeaturename), CLEARED(strDescription), CLEARED(vData))))
		{
			ERROR_FAILED_HRESULT(m_pTRiASMDSMap -> RemoveAt(strMCode), E_FAIL);
		}
		ERROR_FAILED_HRESULT(pTRiASFeature -> get_Name(CLEARED(strFeaturename)), E_FAIL);
		ERROR_FAILED_HRESULT(m_pTRiASMDSMap -> SetAt(strMCode, strFieldname, 
			strFeaturename, strDescription, vData), E_FAIL);

	CComBSTR strPKeyName;
	CComBSTR strPGeoName;

		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_PrimaryKey(CLEARED(strPKeyName)), E_FAIL);
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_DefaultGeometry(CLEARED(strPGeoName)), E_FAIL);

		if (V_BSTR(&vOldname) == strPKeyName)
		{
			ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> put_PrimaryKey(strFeaturename), E_FAIL);
		}
		if (V_BSTR(&vOldname) == strPGeoName)
		{
			ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> put_DefaultGeometry(strFeaturename), E_FAIL);
		}
		SetDirty();

	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOObjects, ReclassFeature
	, /*[in]*/ IGDOFeature*, pGDOFeature
	, /*[in]*/ VARIANT, vOldMCode
)
{
	COM_TRY {
		ERROR_EXPR_FALSE(V_ISBSTR(&vOldMCode), E_FAIL);
		CComBSTR	strMCode;
		CComBSTR	strFieldname;
		CComBSTR	strFeaturename;
		CComBSTR	strDescription;
		CComVariant	vData;
		ERROR_FAILED_HRESULT(pGDOFeature -> get_MCode(CLEARED(strMCode)), E_FAIL);
		if (SUCCEEDED(m_pTRiASMDSMap -> GetAt(V_BSTR(&vOldMCode), CLEARED(strFieldname), 
			CLEARED(strFeaturename), CLEARED(strDescription), CLEARED(vData))))
		{
			ERROR_FAILED_HRESULT(m_pTRiASMDSMap -> RemoveAt(V_BSTR(&vOldMCode)), E_FAIL);
		}
		ERROR_FAILED_HRESULT(m_pTRiASMDSMap -> SetAt(strMCode, strFieldname, 
			strFeaturename, strDescription, vData), E_FAIL);
		SetDirty();

	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOObjects, RedescribeFeature
	, /*[in]*/ IGDOFeature*, pGDOFeature
)
{
	COM_TRY {
		WTRiASFeature	pTRiASFeature;
		ERROR_FAILED_HRESULT(pGDOFeature -> QueryInterface(pTRiASFeature.ppi()), E_FAIL);
		CComBSTR	strMCode;
		CComBSTR	strFieldname;
		CComBSTR	strFeaturename;
		CComBSTR	strDescription;
		CComVariant	vData;
		ERROR_FAILED_HRESULT(pGDOFeature -> get_MCode(CLEARED(strMCode)), E_FAIL);
		if (SUCCEEDED(m_pTRiASMDSMap -> GetAt(strMCode, CLEARED(strFieldname), 
			CLEARED(strFeaturename), CLEARED(strDescription), CLEARED(vData))))
		{
			ERROR_FAILED_HRESULT(m_pTRiASMDSMap -> RemoveAt(strMCode), E_FAIL);
		}
		pTRiASFeature -> get_Description(CLEARED(strDescription));
		ERROR_FAILED_HRESULT(m_pTRiASMDSMap -> SetAt(strMCode, strFieldname, 
			strFeaturename, strDescription, vData), E_FAIL);
		SetDirty();
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_3(CGDOObjects, UpdateFeature
	, /*[in]*/ IGDOFeature*, pGDOFeature
	, /*[in]*/ IGDOObject*, pGDOObject
	, /*[in]*/ VARIANT, vValue
)
{
	COM_TRY {
	CComVariant		vNewValue(vValue);
	CComBSTR		strFieldname;
	CComBSTR		strObjectname;
	WTRiASObject	pTRiASObject;

		ERROR_FAILED_HRESULT(pGDOObject -> QueryInterface(pTRiASObject.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASObject -> get_Name(CLEARED(strObjectname)), E_FAIL);
		ERROR_FAILED_HRESULT(pGDOFeature -> get_Fieldname(CLEARED(strFieldname)), E_FAIL);

		{
		CComBSTR	strPrimaryKey;
		AC_GRecordset	rs;
		DBTransaction	dbTrans(m_pGDatabase);

			RETURN_FAILED_HRESULT(LocateRecord(strObjectname, rs, strPrimaryKey));
			if (V_ISERROR(&vNewValue)) {
				vNewValue.Clear();
				vNewValue.ChangeType(VT_NULL);
			}
			if (V_ISBSTR(&vNewValue))
			{
				UINT len = ::SysStringLen(V_BSTR(&vNewValue));
				long	gmType = 0, gmAttr = 0, gmSize = 0;
				GetFieldType(rs, strFieldname, gmType, gmAttr, gmSize);
				if (len > gmSize)
				{
					CComBSTR	strTruncated(gmSize, V_BSTR(&vNewValue));
					vNewValue = strTruncated;
				}
			}
			EXT_ERROR_FAILED_HRESULT(rs -> Edit(), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(SetFieldValue(rs, strFieldname, vNewValue), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(rs -> Update(), NDB_E_NATIVEDB);
			dbTrans.Succeeded();
		}
	} COM_CATCH;
	return S_OK;
}

HRESULT CGDOObjects::CacheLocatedFeatures(AC_GRecordset &rs, ITRiASFeatures* pTRiASFeatures)
{
WEnumVARIANT pEnumVARIANT;

	RETURN_FAILED_HRESULT(pTRiASFeatures -> _NewEnum(pEnumVARIANT.ppu()));
	_ASSERTE(SupportsInterface(pEnumVARIANT, (IEnumVARIANT *)NULL));

WGFields flds;
CComVariant vFeature;

	EXT_ERROR_FAILED_HRESULT(rs -> get_GFields (flds.ppi()), NDB_E_NATIVEDB);
	for (pEnumVARIANT -> Reset(); S_OK == pEnumVARIANT -> Next(1, CLEARED(vFeature), NULL); /**/)
	{
	WGDOFeature pGDOFeature;

		if (V_ISDISPATCH(&vFeature))
			pGDOFeature = V_DISPATCH(&vFeature);
		else if (V_ISUNKNOWN(&vFeature)) 
			pGDOFeature = V_UNKNOWN(&vFeature);
		else 
			MAKE_ERROR(E_FAIL);

	WGField fld;
	CComVariant vValue;
	CComBSTR strFieldname;

		RETURN_FAILED_HRESULT(pGDOFeature -> get_Fieldname(CLEARED(strFieldname)));
		EXT_ERROR_FAILED_HRESULT(flds -> get_Item(CComVariant(strFieldname), fld.ppi()), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(fld -> get_Value(CLEARED(vValue)), NDB_E_NATIVEDB);
		RETURN_FAILED_HRESULT(pGDOFeature -> put_FieldValue(vValue));
	}
	return S_OK;
}

HRESULT CGDOObjects::QueryFeatures(ITRiASFeatures* pTRiASFeatures, IGDOObject* pGDOObject) 
{
//	ERROR_EXPR_TRUE(NULL == pGDOObject || NULL == pTRiASFeatures, E_INVALIDARG);
//
//CComBSTR strObjectname;
//WTRiASObject pTRiASObject;
//
//	ERROR_FAILED_HRESULT(pGDOObject -> QueryInterface(pTRiASObject.ppi()), E_FAIL);
//	ERROR_FAILED_HRESULT(pTRiASObject -> get_Name(CLEARED(strObjectname)), E_FAIL);
//	if (strObjectname != m_bstrLastObjName)
//	{
//	CComBSTR strPrimaryKey;
//	AC_GRecordset rs;
//
//		RETURN_FAILED_HRESULT(LocateRecord(strObjectname, rs, strPrimaryKey));
//		RETURN_FAILED_HRESULT(CacheLocatedFeatures(rs, pTRiASFeatures));
//		m_bstrLastObjName = strObjectname;
//	} 
	_ASSERTE(SUCCEEDED(E_NOTIMPL));		// should not be called anymore
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// sämtliche Anfragen nach dem Wert einer Objekteigenschaft kommen hier an
IMPLEMENT_DEBUG_FUNCENTRY_3(CGDOObjects, QueryFeature
	, /*[in]*/ IGDOFeature*, pGDOFeature
	, /*[in]*/ IGDOObject*, pGDOObject
	, /*[out, retval]*/ VARIANT*, pvNewValue
)
{
	CHECKOUTPOINTER(pvNewValue);
	COM_TRY {
	CComBSTR strObjectname;
	WTRiASObject pTRiASObject (pGDOObject);

		ERROR_FAILED_HRESULT(pTRiASObject -> get_Name(CLEARED(strObjectname)), E_FAIL);
		if (strObjectname != m_bstrLastObjName) {
		CComBSTR strPrimaryKey;
		AC_GRecordset rs;

			RETURN_FAILED_HRESULT(LocateRecord (strObjectname, rs, strPrimaryKey));

		WTRiASFeatures pTRiASFeatures;

			RETURN_FAILED_HRESULT(pTRiASObject -> get_Features(pTRiASFeatures.ppi()));
			RETURN_FAILED_HRESULT(CacheLocatedFeatures (rs, pTRiASFeatures));
			m_bstrLastObjName = strObjectname;
		}
		EXT_ERROR_FAILED_HRESULT(pGDOFeature -> get_FieldValue(pvNewValue), E_FAIL);

	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOObjects, RenameObject
	, /*[in]*/ IGDOObject*, pGDOObject
	, /*[in]*/ BSTR, strOldname
)
{
	ERROR_EXPR_TRUE(!m_bWritable, GDO_E_READONLY);

	COM_TRY {
	CComBSTR strObjectname(strOldname);
	CComBSTR strNewname;
	WTRiASObject pTRiASObject;

		ERROR_FAILED_HRESULT(pGDOObject -> QueryInterface(pTRiASObject.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASObject -> get_Name(CLEARED(strNewname)), E_FAIL);

		{
		CComBSTR strPrimaryKey;
		AC_GRecordset rs;
		DBTransaction dbTrans(m_pGDatabase);

			RETURN_FAILED_HRESULT(LocateRecord(strObjectname, rs, strPrimaryKey));
			EXT_ERROR_FAILED_HRESULT(rs -> Edit(), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(SetFieldValue(rs, strPrimaryKey, CComVariant(strNewname)), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(rs -> Update(), NDB_E_NATIVEDB);
			dbTrans.Succeeded();
		}
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOObjects, get_Tablename, /*[in]*/ BSTR*, pVal) 
{
	CHECKOUTPOINTER(pVal);
	COM_TRY {
		*pVal = ::SysAllocString(m_strTablename);
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOObjects, put_Tablename, /*[out, retval]*/ BSTR, pVal) 
{
	COM_TRY {
	CComBSTR strOldTablename = m_strTablename;
	CComBSTRChangeHelper helper(m_strTablename);

		m_strTablename = pVal;

	// Tabellenname wurde vom Papa (GDOObjectsCollection) geändert;
	// jetzt noch mal überprüfen ob alles korrekt ist
	WGTableDef	pGTableDef;

		RETURN_FAILED_HRESULT(GetGTableDef(pGTableDef));
		helper.Succeeded();

	// scheint gut gegangen zu sein ... Map für MCodes umhängen
	WGDODatabase		pGDODatabase;
	WDispatch			pDispTRiASPropertyBase;
	WTRiASPropertyBase	pTRiASPropertyBase;

		ERROR_FAILED_HRESULT(FindSpecificParent(GetUnknown(), pGDODatabase.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(WTRiASBase(pGDODatabase) -> get_Parent(pDispTRiASPropertyBase.ppi()), GDO_E_NOPARENT);
		ERROR_FAILED_HRESULT(pDispTRiASPropertyBase -> QueryInterface(pTRiASPropertyBase.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASPropertyBase -> RemoveProperty(strOldTablename), E_FAIL);
		ERROR_FAILED_HRESULT(SetPropertyBy(pTRiASPropertyBase, m_strTablename, m_pTRiASMDSMap, true), E_FAIL);
	
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// (1) alle Änderungen in Featuredefinitionen rückschreiben
// (2) alle Änderungen in Geometriefeaturedefinitionen rückschreiben
// (3) alle "gelöschten" Features auch wirklich in GDO löschen

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOObjects, Save
		, /*[in, out]*/ VARIANT_BOOL*, pbHaveChanced
) 
{
	if (!m_bWritable)
		return S_OK;

	COM_TRY {
		WTRiASFeatures	pTRiASFeatures;
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_Features(pTRiASFeatures.ppi()), E_FAIL);
		UpdateFeatures(pTRiASFeatures, pbHaveChanced);	// (1)
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_GeometryFeatures(pTRiASFeatures.ppi()), E_FAIL);
		UpdateFeatures(pTRiASFeatures, pbHaveChanced);	// (2)
		DeleteFeatures(pbHaveChanced);					// (3)
	} COM_CATCH;
	return S_OK;
}

HRESULT CGDOObjects::SetDirty() 
{
	WTRiASDatabase	pTRiASDatabase;
	ERROR_FAILED_HRESULT(FindSpecificParent(GetUnknown(), pTRiASDatabase.ppi()), E_FAIL);
	ERROR_FAILED_HRESULT(pTRiASDatabase -> put_IsDirty(VARIANT_TRUE), E_FAIL);
	m_fIsDirty = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////
// diejenigen Einträge aus den Metadaten entfernen, die nicht oder nicht mehr als
// Feldname vorhanden sind (wenn z.B. Feldnamen außerhalb geändert wurden)

HRESULT	CGDOObjects::ClearMDSMap() 
{
WEnumVARIANT	vEnum;
CComVariant		vHandle;
CComBSTR		strFieldname;
CComBSTR		strFeaturename;
CComBSTR		strDescription;
CComVariant	vData;
W_MetadataService	pMetadataService(CLSID_MetadataService);
IDispatch	*pRawDisp = m_pDGMConnection;

	EXT_ERROR_FAILED_HRESULT(pMetadataService -> putref_Connection(&pRawDisp), NDB_E_NATIVEDB);

long	lValid;
W_TableProperty	tblProp(CLSID_TableProperty); 
W_FieldProperty	fldProp(CLSID_FieldProperty);
IDispatch	*pDispTblProp = tblProp;
IDispatch	*pDispFldProp = fldProp;

	EXT_ERROR_FAILED_HRESULT(pMetadataService -> put_TableName(&m_strTablename), NDB_E_NATIVEDB);
	EXT_ERROR_FAILED_HRESULT(pMetadataService -> GetTableMetadata(&pDispTblProp, &lValid), NDB_E_NATIVEDB);

	m_pTRiASMDSMap -> _NewEnum(vEnum.ppu());
	for (vEnum -> Reset(); S_OK == vEnum -> Next(1, CLEARED(vHandle), NULL); /**/)
	{
		ERROR_EXPR_FALSE(V_ISBSTR(&vHandle), E_FAIL);
		m_pTRiASMDSMap -> GetAt(V_BSTR(&vHandle), CLEARED(strFieldname), CLEARED(strFeaturename), 
			CLEARED(strDescription), CLEARED(vData));
		EXT_ERROR_FAILED_HRESULT(fldProp -> put_Name(&strFieldname), NDB_E_NATIVEDB);
		if (FAILED(pMetadataService -> GetFieldMetadata(&pDispFldProp, &lValid)))
		{
			m_pTRiASMDSMap -> RemoveAt(V_BSTR(&vHandle));
		}
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Helferfunktionen für Features...

HRESULT CGDOObjects::GetOrCreateFeature(
	const CComBSTR& strFieldname, const CComBSTR& strFeaturename, CComBSTR& strMCode, 
	DWORD dwTypeOfFeature, ITRiASFeatures* pTRiASFeatures, ITRiASFeature **ppITRiASFeature) 
{
// Initialisierungsobjekt
WDispatch App;

	ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_Application(App.ppi()), GDO_E_NOAPPLICATION);

CInitGDOFeature InitFeat(App, GetDispatch(), m_pDGMConnection, m_pGDatabase, 
	CComBool(m_bWritable), dwTypeOfFeature, strMCode, strFieldname, strFeaturename);
WTRiASFeature pTRiASFeature;
INT_PTR	hFeature = 0;
HRESULT	hrCreated;

#if defined(_USE_CLASSFACTORY_CACHE)
WMoniker Mk;

	::CreateItemMoniker(g_cbMkDelW, strFieldname, Mk.ppi());
	ERROR_FAILED_HRESULT(hrCreated = FindInMapOrCreateObject(m_pTRiASFeatureHandleMap, 
		Mk, hFeature, pTRiASFeature, MakeGDOFeature, InitFeat), hrCreated);
#else
	ERROR_FAILED_HRESULT(hrCreated = FindInMapOrCreateObject(m_pTRiASFeatureHandleMap, 
		hFeature, pTRiASFeature, CLSID_GDOFeature, InitFeat), hrCreated);
#endif // defined(_USE_CLASSFACTORY_CACHE)

	if (SUCCEEDED(hrCreated))
	{
		if (S_OK == hrCreated) {
		// S_OK ... Feature wurde neu angelegt...
			ERROR_FAILED_HRESULT(WTRiASHandle(pTRiASFeature) -> PutHandle(hFeature), E_FAIL);
		}
		ERROR_FAILED_HRESULT(pTRiASFeatures -> _Add(pTRiASFeature, VARIANT_FALSE), E_FAIL);
	}

// MCode war noch nicht bekannt; mit aktuell vergebenem Handle belegen und zuordnen
// wir landen dann wieder in ReclassFeature, da wird die eigentliche Arbeit erledigt
WGDOFeature	pGDOFeature;

	if (strMCode == CComBSTR(_T("0"))) {
	TCHAR _buf[64];
	
		wsprintf(_buf, _T("%ld"), hFeature);
		strMCode = _buf;
	}
	ERROR_FAILED_HRESULT(pTRiASFeature -> QueryInterface(pGDOFeature.ppi()), E_FAIL);
	ERROR_FAILED_HRESULT(pGDOFeature -> put_MCode(strMCode), E_FAIL);
	if (ppITRiASFeature) 
		*ppITRiASFeature = pTRiASFeature.Detach();

	return hrCreated;
}

///////////////////////////////////////////////////////////////////////////////
// Initialisieren der Features-Collections der Basisklasse (Features, die dieser
// Objektklasse zugeordnet sind)
HRESULT CGDOObjects::EnsureFeatures() 
{
	COM_TRY {
		CHECK_INITIALIZED();
		if (m_bFeaturesLoaded)
			return S_OK;

	// neue Features erzeugen,
	WGDOFeatures pGDOFeatures;
	WGDOFeatures pGDOGeoFeatures;

		ERROR_FAILED_HRESULT(CGDOFeatures::CreateInstance(pGDOFeatures.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(CGDOFeatures::CreateInstance(pGDOGeoFeatures.ppi()), E_FAIL);
		
	// initialisieren,
	MC::ArrayUnknown arr(2);

		arr[0] = WUnknown(m_pDGMConnection).Detach();
		arr[1] = WUnknown(m_pGDatabase).Detach();

		ERROR_FAILED_HRESULT(pGDOFeatures -> InitTarget(&arr, CComBool(m_bWritable)), OBS_E_INITFEATURES);
		ERROR_FAILED_HRESULT(pGDOGeoFeatures -> InitTarget(&arr, CComBool(m_bWritable)), OBS_E_INITFEATURES);

	// mit Featuredefinitionen füllen,
	WTRiASFeatures pTRiASFeatures (pGDOFeatures);
	WTRiASFeatures pTRiASGeoFeatures (pGDOGeoFeatures);
	CComBSTR strPrimaryfeature;
	CComBSTR strPrimarygeometry;

		ERROR_FAILED_HRESULT(ReloadFeatures(pTRiASFeatures, strPrimaryfeature, pTRiASGeoFeatures, strPrimarygeometry), OBS_E_LOADINGFEATURES);

	// wenn wir hier sind sieht's gut aus, also Basisklasse mit Features versorgen
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> put_Features(pTRiASFeatures), OBS_E_INITFEATURES);
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> put_PrimaryKey(strPrimaryfeature), E_FAIL);
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> put_GeometryFeatures(pTRiASGeoFeatures), OBS_E_INITFEATURES);
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> put_DefaultGeometry(strPrimarygeometry), E_FAIL);
		m_bFeaturesLoaded = true;		// sonst gibt's eine while(1) Schleife

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// GDO-Felddefinitionen einlesen

HRESULT CGDOObjects::ReloadFeatures(
	ITRiASFeatures *pTRiASFeatures, CComBSTR& strPrimaryfeature, ITRiASFeatures* pTRiASGeoFeatures, 
	CComBSTR& strPrimarygeometry, bool fForce) 
{
CComBSTR strMCode;
CComBSTR strFieldname;
CComBSTR strFeaturename;
CComBSTR strDescription;
ITRiASFeatures *pDstTRiASFeatures;
WTRiASFeature pTRiASFeature;

	if (m_fReloaded && !fForce) {
	// nicht das erste mal, also aus der Map laden
	WEnumVARIANT Enum;
	CComVariant v;

		RETURN_FAILED_HRESULT(m_pTRiASMDSMap -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(v), NULL); /**/) {
		CComVariant vData;

			RETURN_FAILED_HRESULT(v.ChangeType (VT_BSTR));
			RETURN_FAILED_HRESULT(m_pTRiASMDSMap -> GetAt (V_BSTR(&v), 
				CLEARED(strFieldname), CLEARED(strFeaturename), CLEARED(strDescription), 
				CLEARED(vData)));

		// KeyFeldnamen setzen
			if (V_I4(&vData) & FEATURETYPE_Geometry) {
			// erste gefundene Geometrie wird zunächst mal als die Standardgeometrie angenommen...
				if (!strPrimarygeometry || 0 == strPrimarygeometry.Length())
					strPrimarygeometry = strFeaturename;

			// Standardgeometrie kann aber auch explizit gegeben sein (Access kennt so was, ArcView nicht)
				if (V_I4(&vData) & FEATURETYPE_IsPrimaryFeature)
					strPrimarygeometry = strFeaturename;	// Standardgeometrie explizit gegeben
				pDstTRiASFeatures = pTRiASGeoFeatures;
			} 
			else {
				if (V_I4(&vData) & FEATURETYPE_IsPrimaryFeature) 
					strPrimaryfeature = strFeaturename;
				pDstTRiASFeatures = pTRiASFeatures;
			}
			if (NULL == pDstTRiASFeatures)		// diese Collection soll nicht geladen werden
				continue;

		CComBSTR bstrMCode (V_BSTR(&v));

			ERROR_FAILED_HRESULT(GetOrCreateFeature(strFieldname, strFeaturename, 
				bstrMCode, LOWORD(V_I4(&vData)), pDstTRiASFeatures, pTRiASFeature.ppi()), E_FAIL);
			pTRiASFeature -> put_Description(strDescription);
		}
		return S_OK;
	}

W_MetadataService pMetadataService(CLSID_MetadataService);
IDispatch *pRawDisp = m_pDGMConnection;

	EXT_ERROR_FAILED_HRESULT(pMetadataService -> putref_Connection(&pRawDisp), NDB_E_NATIVEDB);
	RETURN_FAILED_HRESULT(ClearMDSMap());

WGTableDef pGTableDef;

	ERROR_FAILED_HRESULT(GetGTableDef(pGTableDef), E_FAIL);

IDispatch *pDisp = NULL;
long lValid;
W_TableProperty	tblProp (CLSID_TableProperty);

	pDisp = tblProp;		// kein QI, kein AddRef() !!
	EXT_ERROR_FAILED_HRESULT(pMetadataService -> put_TableName(&m_strTablename), NDB_E_NATIVEDB);
	EXT_ERROR_FAILED_HRESULT(pMetadataService -> GetTableMetadata(&pDisp, &lValid), NDB_E_NATIVEDB);

W_FieldProperty	fldProp(CLSID_FieldProperty);

	pDisp = fldProp;		// !!kein AddRef!!

CComVariant vGField;
WEnumVARIANT Enum;
WGFields pGFields;
WGField pGField;
short fldType;
long fldAttribs;
long lFieldMask = 0;		// alle Felder
VARIANT_BOOL bIsDisplayable = VARIANT_FALSE;
	
	EXT_ERROR_FAILED_HRESULT(pGTableDef -> get_GFields(pGFields.ppi()), NDB_E_NATIVEDB);
	EXT_ERROR_FAILED_HRESULT(pGFields -> _NewEnum(Enum.ppu()), NDB_E_NATIVEDB);
 	for (Enum -> Reset(); S_OK == Enum -> Next(1, CLEARED(vGField), NULL); /**/)
	{
		ERROR_EXPR_FALSE(V_ISDISPATCH(&vGField), E_FAIL);
		pGField = V_DISPATCH(&vGField);

		EXT_ERROR_FAILED_HRESULT(pGField -> get_Name(CLEARED(strFieldname)), E_FAIL);
		EXT_ERROR_FAILED_HRESULT(pGField -> get_Attributes(&fldAttribs), E_FAIL);

		EXT_ERROR_FAILED_HRESULT(fldProp -> put_Name(&strFieldname), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(pMetadataService -> GetFieldMetadata(&pDisp, &lFieldMask), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(fldProp -> get_Displayable(&bIsDisplayable), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(fldProp -> get_FieldType(&fldType), E_FAIL);

	// den Typ dieses Feldes zusammenstellen
	DWORD dwFeatureType = FEATURETYPE_Object;
	CComBool bIsKey;
	CComBool bIsGeoKey;

		if (!bIsDisplayable)
			dwFeatureType |= (FEATURETYPE_System | FEATURETYPE_ReadOnly);

		if (gdbSpatial == fldType || gdbGraphic == fldType) {
			EXT_ERROR_FAILED_HRESULT(fldProp -> get_PrimaryGeometryFlag(&bIsGeoKey), NDB_E_NATIVEDB);
			if (bIsGeoKey)	
				dwFeatureType |= FEATURETYPE_IsPrimaryFeature;

			dwFeatureType |= FEATURETYPE_Geometry;
			pDstTRiASFeatures = pTRiASGeoFeatures;

		// Objekttypen in höherwertigem Wort speichern
		long geoType = 0;

			EXT_ERROR_FAILED_HRESULT(fldProp -> get_GeometryType(&geoType), E_FAIL);
			dwFeatureType = MAKELONG(dwFeatureType, OT_GDO2TRiAS(geoType));
		} 
		else {
			EXT_ERROR_FAILED_HRESULT(fldProp -> get_Key(&bIsKey), NDB_E_NATIVEDB);
			if (bIsKey) 
				dwFeatureType |= FEATURETYPE_IsPrimaryFeature;

			pDstTRiASFeatures = pTRiASFeatures;
		}

	CComVariant vData (dwFeatureType, VT_I4);
	HRESULT	hrSearch;
	
		ERROR_FAILED_HRESULT(hrSearch = SearchMDSMap(m_pTRiASMDSMap, strFieldname, 
			strMCode, lSearchName), GDO_E_METADATA);

		if (S_FALSE == hrSearch) {
		// noch nicht in der Map; Eintrag erzeugen und sinnvoll vorbelegen
			strFeaturename = strFieldname;
			EXT_ERROR_FAILED_HRESULT(fldProp -> get_Description(CLEARED(strDescription)), E_FAIL);
			strMCode = _T("0");

		// einen NULL-Eintrag erzeugen; bei Featureerzeugung wird umklassifiziert und zwar
		// vom MCode "0" (mit dem das Feature erstmal initialisiert wird) zum eigentlichen MCode;
		// dazu muß der MCode "0" aber auch vorhanden sein.
			m_pTRiASMDSMap -> SetAt(CComBSTR(_T("0")), strFieldname, strFeaturename, strDescription, vData);
		} 
		else {
		CComVariant vDummy;

			m_pTRiASMDSMap -> GetAt(strMCode, CLEARED(strFieldname), CLEARED(strFeaturename), 
				CLEARED(strDescription), CLEARED(vDummy));
			if (V_ISEMPTY(&vDummy) || V_I4(&vDummy) != V_I4(&vData))		// FeatureType nachreichen
				m_pTRiASMDSMap -> SetAt(strMCode, strFieldname, strFeaturename, strDescription, vData);
		}

	// KeyFeldnamen setzen
		if (gdbSpatial == fldType || gdbGraphic == fldType) {
		// erste gefundene Geometrie wird zunächst mal als die Standardgeometrie angenommen...
			if (bIsGeoKey || !strPrimarygeometry || 0 == strPrimarygeometry.Length())
				strPrimarygeometry = strFeaturename;

		// Standardgeometrie kann aber auch explizit gegeben sein (Access kennt so was, ArcView nicht)
			if (bIsGeoKey)
				strPrimarygeometry = strFeaturename;	// Standardgeometrie explizit gegeben
		} 
		else if (bIsKey || !strPrimaryfeature || 0 == strPrimaryfeature.Length()) 
			strPrimaryfeature = strFeaturename;

		if (NULL == pDstTRiASFeatures)		// diese Collection soll nicht geladen werden
			continue;

		ERROR_FAILED_HRESULT(GetOrCreateFeature(strFieldname, strFeaturename, strMCode, 
			dwFeatureType, pDstTRiASFeatures, pTRiASFeature.ppi()), E_FAIL);
		pTRiASFeature -> put_Description(strDescription);
	}

	m_pTRiASMDSMap -> RemoveAt(CComBSTR(_T("0")));
	m_fReloaded = true;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// die Eigenschaften einer TRiASFeature zurückschreiben

HRESULT	CGDOObjects::UpdateFeature(
	CComBSTR& strOldFieldname, CComBSTR& strNewFieldname, CComBSTR& strDescription) 
{
DBTransaction dbTrans(m_pGDatabase);
WGTableDef pGTableDef;
WGFields pGFields;
WGField pGField;

	RETURN_FAILED_HRESULT(GetGTableDef(pGTableDef));

W_MetadataService pMetadataService(CLSID_MetadataService);
IDispatch *pRawDisp = m_pDGMConnection;

	EXT_ERROR_FAILED_HRESULT(pMetadataService -> putref_Connection(&pRawDisp), NDB_E_NATIVEDB);

long lValid;
W_FieldProperty	fldProp(CLSID_FieldProperty); 
IDispatch *pDisp = fldProp;		// kein QI, kein AddRef() !!

	EXT_ERROR_FAILED_HRESULT(pMetadataService -> put_TableName(&m_strTablename), NDB_E_NATIVEDB);
	EXT_ERROR_FAILED_HRESULT(fldProp -> put_Name(&strOldFieldname), NDB_E_NATIVEDB);
	EXT_ERROR_FAILED_HRESULT(pMetadataService -> GetFieldMetadata(&pDisp, &lValid), NDB_E_NATIVEDB);

	EXT_ERROR_FAILED_HRESULT(pGTableDef -> get_GFields(pGFields.ppi()), NDB_E_NATIVEDB);
	EXT_ERROR_FAILED_HRESULT(pGFields -> get_Item(CComVariant(strOldFieldname), pGField.ppi()), NDB_E_NATIVEDB);

	EXT_ERROR_FAILED_HRESULT(pMetadataService -> DeleteFieldMetadata(&strOldFieldname, &lValid), NDB_E_NATIVEDB);

	EXT_ERROR_FAILED_HRESULT(pGField -> put_Name(strNewFieldname), NDB_E_NATIVEDB);
	EXT_ERROR_FAILED_HRESULT(fldProp -> put_Name(&strNewFieldname), NDB_E_NATIVEDB);
	EXT_ERROR_FAILED_HRESULT(pMetadataService -> AddFieldMetadata(&pDisp, &lValid), NDB_E_NATIVEDB);

	EXT_ERROR_FAILED_HRESULT(fldProp -> put_Description(&strDescription), NDB_E_NATIVEDB);
	dbTrans.Succeeded();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// alle Features durchgehen und Änderungen rückschreiben

HRESULT	CGDOObjects::UpdateFeatures(ITRiASFeatures* pTRiASFeatures, VARIANT_BOOL* pbChanged) 
{
WEnumVARIANT Enum;
CComVariant vTRiASFeature;
CComBSTR strMCode;
CComBSTR strFieldname;
CComBSTR strOldFieldname;
CComBSTR strNewFieldname;
CComBSTR strFeaturename;
CComBSTR strDescription;
CComVariant vData;

	ERROR_FAILED_HRESULT(pTRiASFeatures -> _NewEnum(Enum.ppu()), E_FAIL);
	for (Enum -> Reset(); S_OK == Enum -> Next(1, CLEARED(vTRiASFeature), NULL); /**/) 
	{
		ERROR_EXPR_FALSE(V_ISDISPATCH(&vTRiASFeature), E_FAIL);

	WGDOFeature pGDOFeature;

		ERROR_FAILED_HRESULT(V_DISPATCH(&vTRiASFeature) -> QueryInterface(pGDOFeature.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pGDOFeature -> get_Fieldname(CLEARED(strFieldname)), E_FAIL);

	HRESULT hrSearch = SearchMDSMap(m_pTRiASMDSMap, strFieldname, strMCode, lSearchName);

		_ASSERTE(S_OK == hrSearch);			// muß!! gefunden werden
		m_pTRiASMDSMap -> GetAt(strMCode, CLEARED(strOldFieldname), CLEARED(strFeaturename), 
			CLEARED(strDescription), CLEARED(vData));
		
		NormalizeName(strFeaturename, strNewFieldname);
		if (strNewFieldname == strFieldname)
			continue;						// hat sich nichts geändert

	WTRiASFeature pTRiASFeature;

		ERROR_FAILED_HRESULT(V_DISPATCH(&vTRiASFeature) -> QueryInterface(pTRiASFeature.ppi()), E_FAIL);
		if (!SUCCEEDED(UpdateFeature(strOldFieldname, strNewFieldname, strDescription)))
			continue;

		ERROR_FAILED_HRESULT(m_pTRiASMDSMap -> SetAt(strMCode, strNewFieldname, 
			strFeaturename, strDescription, vData), E_FAIL);
		pGDOFeature -> put_Fieldname(strNewFieldname);
		*pbChanged = VARIANT_TRUE;
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// das "wahre" Feldlöschen

HRESULT	CGDOObjects::DeleteFeature(/*const*/ CComBSTR& strFieldname) 
{
DBTransaction	dbTrans(m_pGDatabase);
WGTableDef	pGTableDef;
WGFields	pGFields;
WGField		pGField;

	RETURN_FAILED_HRESULT(GetGTableDef(pGTableDef));

W_MetadataService	pMetadataService(CLSID_MetadataService);
IDispatch	*pRawDisp = m_pDGMConnection;

	EXT_ERROR_FAILED_HRESULT(pMetadataService -> putref_Connection(&pRawDisp), NDB_E_NATIVEDB);

long lValid;
//W_FieldProperty	fldProp(CLSID_FieldProperty); 
//IDispatch *pDisp = fldProp;		// kein QI, kein AddRef() !!
	
	EXT_ERROR_FAILED_HRESULT(pMetadataService -> put_TableName(&m_strTablename), NDB_E_NATIVEDB);
	EXT_ERROR_FAILED_HRESULT(pMetadataService -> DeleteFieldMetadata(&strFieldname, &lValid), NDB_E_NATIVEDB);
	EXT_ERROR_FAILED_HRESULT(pGTableDef -> get_GFields(pGFields.ppi()), NDB_E_NATIVEDB);
	EXT_ERROR_FAILED_HRESULT(pGFields -> Delete(strFieldname), NDB_E_NATIVEDB);
	dbTrans.Succeeded();
	return S_OK;
}

HRESULT	CGDOObjects::DeleteFeatures(VARIANT_BOOL* pbChanged) 
{
CComBSTR	strFieldname;
CComBSTR	strFeaturename;
CComBSTR	strDescription;
CComVariant	vData;
map<CComBSTR, bool>::iterator i = m_strFeaturesToDelete.begin();
	
	for (/**/; m_strFeaturesToDelete.end() != i; ++i)
	{
		m_pTRiASMDSMap -> GetAt((*i).first, CLEARED(strFieldname), CLEARED(strFeaturename), 
			CLEARED(strDescription), CLEARED(vData));
		if (SUCCEEDED(DeleteFeature(strFieldname)))
		{
			m_pTRiASMDSMap -> RemoveAt((*i).first);
		}
		*pbChanged = VARIANT_TRUE;
	}
	m_strFeaturesToDelete.clear();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASObjectsCallback

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOObjects, get_DefaultType,/*[out, retval]*/BSTR*, pStrProgID) 
{
	CHECKINPOINTER(pStrProgID);
	COM_TRY {
	CComBSTR bstrType(GetObjectCLSID());
	
		*pStrProgID = bstrType.Detach();
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOObjects, SetupObjects, SETUPOBJECTSMODE, mode) 
{
	ERROR_EXPR_FALSE(SETUPOBJECTSMODE_Count == mode || 
		SETUPOBJECTSMODE_Load == mode ||
		SETUPOBJECTSMODE_InitOrLoad == mode, TRIASDB_E_INVALID_PARAMETER);

	switch (mode) {
	case SETUPOBJECTSMODE_Count:
		RETURN_FAILED_HRESULT(EnsureFeatures());
		RETURN_FAILED_HRESULT(EnsureObjectsCounted());
		break;

	case SETUPOBJECTSMODE_Load:
		RETURN_FAILED_HRESULT(EnsureFeatures());
		RETURN_FAILED_HRESULT(EnsureObjectsCounted());
		RETURN_FAILED_HRESULT(EnsureObjectsLoaded());
		break;

	case SETUPOBJECTSMODE_InitOrLoad:
		m_bCounted = false;
		m_fIsDirty = true;
		break;
	}
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOObjects, SetupFeatures, SETUPFEATURESMODE, SetupMode) 
{
	return EnsureFeatures();
}

/////////////////////////////////////////////////////////////////////////////
// ein neues Objekt erstellen

IMPLEMENT_DEBUG_FUNCENTRY_4(CGDOObjects, OnCreate,/*[in]*/ BSTR, Name, 
	/*[in]*/ BSTR, progId, OBJECTTYPE, objType, ITRiASObject**, ppIObject) 
{
	CHECKOUTPOINTER(ppIObject);
	ERROR_EXPR_TRUE(!m_bWritable, GDO_E_READONLY);

	COM_TRY {
	WGDODatabase pGDODatabase;
	WDispatch pApplication;
	
		ERROR_FAILED_HRESULT(FindSpecificParent(GetUnknown(), pGDODatabase.ppi()), GDO_E_NOPARENT);
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_Application(pApplication.ppi()), GDO_E_NOAPPLICATION);

	CComBSTR strObjName;
		
		ERROR_FAILED_HRESULT(pGDODatabase -> CreateObject(this, CLEARED(strObjName)), E_FAIL);

	CInitGDOObject InitObj(pApplication, GetDispatch(), m_pDGMConnection, m_pGDatabase, CComBool(m_bWritable));

		InitObj.SetIdent(strObjName);
		InitObj.SetType(objType);

	INT_PTR	hNewObject = 0L;	// Objekt auf jeden Fall neu erzeugen
	WTRiASObject pNewObject;	

//#if defined(_USE_CLASSFACTORY_CACHE)
//	HRESULT	hrCreated = FindInMapOrCreateObject (m_pTRiASObjectHandleMap, hNewObject, pNewObject, MakeGDOObject, InitObj);
//#else
	HRESULT	hrCreated = FindInMapOrCreateObject(m_pTRiASObjectHandleMap, hNewObject, 
		pNewObject, CLSID_GDOObject, InitObj);
//#endif // defined(_USE_CLASSFACTORY_CACHE)

		if (S_OK == hrCreated)
		{
		// Objekt wurde neu erzeugt
			ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> _Add(pNewObject, VARIANT_TRUE), E_FAIL);
		}
		m_bCounted = false;
		*ppIObject = pNewObject.detach();
	} COM_CATCH
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ein Objekt löschen

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOObjects, OnDelete,/*[in]*/ INT_PTR, vWhich) 
{
	ERROR_EXPR_TRUE(!m_bWritable, GDO_E_READONLY);

	COM_TRY {
	CComBSTR	strObjectname;
	CComBSTR	strPKeyname;
	WTRiASObject	pTRiASObject;

		ERROR_FAILED_HRESULT(m_pTRiASObjectHandleMap -> GetObject(vWhich, pTRiASObject.ppu()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASObject -> get_Name(CLEARED(strObjectname)), E_FAIL);
		{
			DBTransaction	dbTrans(m_pGDatabase);
			AC_GRecordset	rs;
			RETURN_FAILED_HRESULT(LocateRecord(strObjectname, rs, strPKeyname));
			EXT_ERROR_FAILED_HRESULT(rs -> Delete(), NDB_E_NATIVEDB);
			dbTrans.Succeeded();
			m_bCounted = false;
		}
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOObjects, OnAdd,/*[in]*/ ITRiASObject*, pObject, CLASSIFYMODE, mode) 
{
	if (CLASSIFYMODE_DoNotClassify == mode)
		return S_OK;
	else if (CLASSIFYMODE_DatasourceOnly == mode) {
		ERROR_EXPR_TRUE(!m_bWritable, GDO_E_READONLY);
		return E_NOTIMPL;
	} 
	return E_UNEXPECTED;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOObjects, OnRemove, ITRiASObject*, Obj) 
{
	FUNC_NOT_IMPL();
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOObjects, MapFeatureHandle, VARIANT, NameOrHandle, VARIANT *, NewNameOrHandle) 
{
CComVariant	vNewHandle(NameOrHandle);

	vNewHandle.Detach(NewNameOrHandle);
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_0(CGDOObjects, OnFinalRelease) 
{
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_3(CGDOObjects, OnChanging
		, /*[in]*/ CHANGEDOBJECTS, rgWhat
		, /*[in]*/ VARIANT, vNewValue
		, /*[in, out]*/ VARIANT_BOOL*, pbDisallow
)
{
	if (IsSemaphoreSignaled(m_lInitData, *this))		// Initialisierungsphase?
		return S_OK;

	CHECKINPOINTER(pbDisallow);
	COM_TRY {
		switch (rgWhat)	{
		case CHANGEDOBJECTS_Name: 
			return OnChangingName(vNewValue, pbDisallow);
		
		case CHANGEDOBJECTS_Description:  
			return OnChangingDescription(vNewValue, pbDisallow);
		
		case CHANGEDOBJECTS_OKS:  
			return OnChangingOKS(vNewValue, pbDisallow);
		
		case CHANGEDOBJECTS_Handle:  
			return OnChangingHandle(vNewValue, pbDisallow);
		
		case CHANGEDOBJECTS_Types:  
			return OnChangingTypes(vNewValue, pbDisallow);

		case CHANGEDOBJECTS_ROMode:
#pragma TODO("CHANGEDOBJECTS_ROMode in CGDOObjects::OnChanging implementieren.")
			break;

		default:
			_ASSERTE(FALSE);
		}
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOObjects, OnChanged,/*[in]*/ CHANGEDOBJECTS, rgWhat, VARIANT, vOldValue) 
{
	if (IsSemaphoreSignaled(m_lInitData, *this))		// Initialisierungsphase?
		return S_OK;
	
	COM_TRY {
		switch (rgWhat)	{
		case CHANGEDOBJECTS_Name: 
			return OnChangedName(vOldValue);
	
		case CHANGEDOBJECTS_Description:  
			return OnChangedDescription(vOldValue);
	
		case CHANGEDOBJECTS_OKS:  
			return OnChangedOKS(vOldValue);
	
		case CHANGEDOBJECTS_Handle:  
			return OnChangedHandle(vOldValue);
	
		case CHANGEDOBJECTS_Types:  
			return OnChangedTypes(vOldValue);
	
		case CHANGEDOBJECTS_ROMode:
#pragma TODO("CHANGEDOBJECTS_ROMode in CGDOObjects::OnChanged implementieren.")
			break;

		default:
			_ASSERTE(NULL);
		}
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Änderungen im Objektklassenschlüssel, im Namen und in der Beschreibung
// an den Papa (GDOObjectsCollection) weiterleiten da der das zusammen mit 
// dem Metadatenservice behandeln muß und korrekt weiß wie's geht...

HRESULT CGDOObjects::OnChangingOKS(const VARIANT& vNewOKS, VARIANT_BOOL* pbDisallow) 
{
	CHECKINPOINTER(pbDisallow);
	*pbDisallow = VARIANT_TRUE;
	ERROR_EXPR_FALSE(V_ISBSTR(&vNewOKS), GDO_E_COERCE);
	*pbDisallow = VARIANT_FALSE;
	return S_OK;
}

HRESULT CGDOObjects::OnChangedOKS(const VARIANT& vOldOKS) 
{
	ERROR_EXPR_FALSE(V_ISBSTR(&vOldOKS), GDO_E_COERCE);
	WGDOObjectsCollection	pGDOObjectsCollection;
	ERROR_FAILED_HRESULT(FindSpecificParent(GetUnknown(), pGDOObjectsCollection.ppi()), GDO_E_NOPARENT);
	ERROR_FAILED_HRESULT(pGDOObjectsCollection -> ReclassObjects(this, V_BSTR(&vOldOKS)), E_FAIL);
	return S_OK;
}

HRESULT CGDOObjects::OnChangingName(const VARIANT& vNewName, VARIANT_BOOL* pbDisallow) 
{
	CHECKINPOINTER(pbDisallow);
	*pbDisallow = VARIANT_TRUE;
	ERROR_EXPR_FALSE(V_ISBSTR(&vNewName), GDO_E_COERCE);
	ERROR_FAILED_HRESULT(ParseName(V_BSTR(&vNewName)), GDO_E_INVALIDNAME);
	*pbDisallow = VARIANT_FALSE;
	return S_OK;
}

HRESULT CGDOObjects::OnChangedName(const VARIANT& vOldName) 
{
	ERROR_EXPR_FALSE(V_ISBSTR(&vOldName), GDO_E_COERCE);
	WGDOObjectsCollection	pGDOObjectsCollection;
	ERROR_FAILED_HRESULT(FindSpecificParent(GetUnknown(), pGDOObjectsCollection.ppi()), GDO_E_NOPARENT);
	ERROR_FAILED_HRESULT(pGDOObjectsCollection -> RenameObjects(this, V_BSTR(&vOldName)), E_FAIL);
	return S_OK;
}

HRESULT CGDOObjects::OnChangingDescription(const VARIANT& vNewDescr, VARIANT_BOOL *pbDisallow) 
{
	CHECKINPOINTER(pbDisallow);
	*pbDisallow = VARIANT_TRUE;
	ERROR_EXPR_FALSE(V_ISBSTR(&vNewDescr), GDO_E_COERCE);
	*pbDisallow = VARIANT_FALSE;
	return S_OK;
}

HRESULT CGDOObjects::OnChangedDescription(const VARIANT& vOldValue) 
{
	ERROR_EXPR_FALSE(V_ISBSTR(&vOldValue), GDO_E_COERCE);
	WGDOObjectsCollection	pGDOObjectsCollection;
	ERROR_FAILED_HRESULT(FindSpecificParent(GetUnknown(), pGDOObjectsCollection.ppi()), GDO_E_NOPARENT);
	ERROR_FAILED_HRESULT(pGDOObjectsCollection -> RedescribeObjects(this), E_FAIL);
	return S_OK;
}

HRESULT CGDOObjects::OnChangingHandle(const VARIANT& /*vNewHandle*/, VARIANT_BOOL* /*pbDisallow*/) 
{
	return S_OK;
}

HRESULT CGDOObjects::OnChangedHandle(const VARIANT& /*vOldHandle*/) 
{
	return S_OK;
}

HRESULT CGDOObjects::OnChangingTypes(const VARIANT& /*vNewTypes*/, VARIANT_BOOL* /*pbDisallow*/) 
{
	return S_OK;
}

HRESULT CGDOObjects::OnChangedTypes(const VARIANT& /*vOldTypes*/) 
{
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// OleItemContainerSupport
HRESULT CGDOObjects::GetFeature(
	LPCTSTR lpszFeaturename, DWORD /*dwSpeedNeeded*/, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly) 
{
	COM_TRY {
		_ASSERTE(0);	// unbedingt anhalten wenn's kommt; muß getestet werden
	
	CComBSTR strFeaturename(lpszFeaturename);
	WTRiASFeatures	pTRiASFeatures;
	WTRiASFeature	pTRiASFeature;
	
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_Features(pTRiASFeatures.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASFeatures -> Item(CComVariant(strFeaturename), pTRiASFeature.ppi()), E_FAIL);
		if (!fTestRunningOnly && NULL != ppvObj)
		{
			ERROR_FAILED_HRESULT(pTRiASFeature -> QueryInterface(riid, ppvObj), E_FAIL);
		}
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Helferfunktionen

HRESULT CGDOObjects::EnsureObjectsCounted() 
{
	if (m_bCounted) 
		return S_OK;

	COM_TRY {
	AC_GRecordset rs;		// selbst schließender Recordset

//	WOriginatingPipe pO;
//	CComBSTR strGeometry;
//
//		RETURN_FAILED_HRESULT(GetPipe (pO));
//		EXT_RETURN_FAILED_HRESULT(pO -> get_OutputRecordset(rs.ppi()));
//
//	long lCount = 0;
//		
//		if (S_OK == rs -> MoveFirst())
//		{
//			EXT_ERROR_FAILED_HRESULT(rs -> MoveLast(), NDB_E_NATIVEDB);
//			EXT_ERROR_FAILED_HRESULT(rs -> get_RecordCount(&lCount), NDB_E_NATIVEDB);
//		}

	// 'Select Count(*) As Cnt From TableName Where Geometry Is Not Null'
	CComBSTR bstrPGeomName;

		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_DefaultGeometry(CLEARED(bstrPGeomName)), E_FAIL);

	CComBSTR bstrSQL(L"Select Count(*) As Cnt From ");
	CComBSTR bstrWhere(L"Where ");

		bstrSQL.AppendBSTR(m_strTablename);
		bstrWhere.AppendBSTR(bstrPGeomName);
		bstrWhere.Append(L" Is Not Null");
		RETURN_FAILED_HRESULT(m_pGDatabase->OpenRecordset(bstrSQL, CComVariant(gdbOpenSnapshot), 
			CComVariant(gdbReadOnly|gdbForwardOnly), vtMissing, vtMissing, vtMissing, rs.ppi()));

	CComVariant vCnt;

		GetFieldValue(rs, L"Cnt", vCnt);
		RETURN_FAILED_HRESULT(vCnt.ChangeType(VT_I4));
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> put_Count(V_I4(&vCnt)), E_FAIL);
		m_bCounted = true;

	} COM_CATCH;
	return S_OK;
}

HRESULT CGDOObjects::EnsureObjectsLoaded() 
{
	COM_TRY {
		TIMER_START(0, L"CGDOObjects::EnsureObjectsLoaded")

	AC_GRecordset rs;

#if defined(_GEOMETRYCACHEDBYOBJECT)
	WOriginatingPipe pO;
	CComBSTR strGeometryname;
	WDGMCSSTransformPipe	pT;
	WISpatialFilterPipe		pF;

		RETURN_FAILED_HRESULT(GetPipes(strGeometryname, pO, pT, pF));
		ConnectPipes(pO, pT, strGeometryname);
		PrepareTransformation(g_DBEngine -> GetGMServerTransService(), pO, m_pDGMCoordSystemsMgr, strGeometryname);
		EXT_ERROR_FAILED_HRESULT(pT -> get_OutputRecordset(rs.ppi()), NDB_E_NATIVEDB);
#else
//	WOriginatingPipe pO;
//
//		RETURN_FAILED_HRESULT(GetPipe (pO));
//		EXT_RETURN_FAILED_HRESULT(pO -> get_OutputRecordset(rs.ppi()));

	// 'Select ID From TableName Where Geometry Is Not Null'
	CComBSTR strPKeyName;
	CComBSTR bstrPGeomName;

		RETURN_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_PrimaryKey(CLEARED(strPKeyName)));
		RETURN_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_DefaultGeometry(CLEARED(bstrPGeomName)));

	CComBSTR bstrSQL(L"Select ");
	
		bstrSQL.AppendBSTR(strPKeyName);
		bstrSQL.Append(L" From ");
		bstrSQL.AppendBSTR(m_strTablename);

	CComBSTR bstrWhere(L" Where ");

		bstrWhere.AppendBSTR(bstrPGeomName);
		bstrWhere.Append(L" Is Not Null");
		bstrSQL.AppendBSTR(bstrWhere);

		RETURN_FAILED_HRESULT(m_pGDatabase->OpenRecordset(bstrSQL, CComVariant(gdbOpenSnapshot), 
			CComVariant(gdbReadOnly|gdbForwardOnly), vtMissing, vtMissing, vtMissing, rs.ppi()));
#endif
	long nObjects = 0;
	CPostFilter	postFilter;
	
		TIMER_CHECKPOINT(0, nObjects)
		RETURN_FAILED_HRESULT(DoLoadObjects(rs, BASE_OF_GDOOBJECTS(), postFilter, nObjects));
		TIMER_CHECKPOINT(0, nObjects)
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// der eigentliche "Objektlader"; bekommt einen vorbereiteten(!!) Recordset,
// liest ihn einfach nur aus und bastelt die Objekte

namespace {
	inline 
	HRESULT GetGeometryType(AC_GRecordset& rs, const LPCOLESTR& strFieldName, long& lType) 
	{
	WGFields flds;
	WGField f;
	HRESULT hr;

		if (S_OK != (hr = rs -> get_GFields(flds.ppi())))
			return hr;
		if (S_OK != (hr = flds -> get_Item(CComVariant(strFieldName), f.ppi())))
			return hr;
		_ASSERTE(f.IsValid());
	
	short t = 0;
	
		if (S_OK != (hr = f -> get_Type(&t)))
			return hr;
		if (gdbSpatial != t) {
			_ASSERTE(SUCCEEDED(E_FAIL));
			return E_FAIL;
		}

		if (S_OK != (hr = f -> get_SubType(&lType)))
			return hr;
		return S_OK;
	}
}

HRESULT CGDOObjects::DoLoadObjects(
	AC_GRecordset& rs, ITRiASObjects* pTRiASObjects, 
	CPostFilter& postFilter, long& nObjects, bool bForceAdd /*=false*/) 
{
	if (S_OK != rs -> MoveFirst())
		return S_FALSE;

WDispatch pApplication;

	ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_Application(pApplication.ppi()), GDO_E_NOAPPLICATION);

CComBSTR strPKeyName;
CComBSTR strPGeomName;

	RETURN_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_PrimaryKey(CLEARED(strPKeyName)));
	RETURN_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_DefaultGeometry(CLEARED(strPGeomName)));

//long gmType = 0, gmAttr = 0, gmSize = 0;
//
//	GetFieldType(rs, strPGeomName, gmType, gmAttr, gmSize);
CComBSTR strMCode;
CComBSTR strFieldname;
CComBSTR strFeaturename;
CComBSTR strDescription;
CComVariant vData;

	ERROR_FAILED_HRESULT(SearchMDSMap(m_pTRiASMDSMap, strPGeomName, strMCode, lSearchName), E_FAIL);
	m_pTRiASMDSMap -> GetAt(strMCode, CLEARED(strFieldname), CLEARED(strFeaturename), 
		CLEARED(strDescription), CLEARED(vData));
	_ASSERTE(0 != HIWORD(V_I4(&vData)));

CInitGDOObject InitObj(pApplication, WDispatch(GetUnknown()), m_pDGMConnection, m_pGDatabase, CComBool(m_bWritable));
VARIANT_BOOL bEOF = VARIANT_TRUE;

WMoniker pMkObject;
WMoniker pMkThis;

	MkGetMoniker(GetControllingUnknown(), OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, pMkThis.ppi());

	InitObj.SetType(OBJECTTYPE(HIWORD(V_I4(&vData))));	//OT_GDO2TRiAS(gmType));

WGFields flds;
WGField fldPKeyName;

	EXT_ERROR_FAILED_HRESULT(rs -> get_GFields(flds.ppi()), NDB_E_NATIVEDB);
	EXT_ERROR_FAILED_HRESULT(flds -> get_Item(CComVariant(strPKeyName), fldPKeyName.ppi()), NDB_E_NATIVEDB);

	while (S_OK == rs -> get_EOF(&bEOF) && !bEOF) {
	HRESULT hr = postFilter(rs);

		if (S_OK == postFilter(rs))	{
		CComVariant vObjName;

			++nObjects;
			EXT_ERROR_FAILED_HRESULT(fldPKeyName -> get_Value(CLEARED(vObjName)), NDB_E_NATIVEDB);
			ERROR_FAILED_HRESULT(vObjName.ChangeType(VT_BSTR), GDO_E_COERCE);

			InitObj.SetIdent(V_BSTR(&vObjName));
			CGDOObject::GetObjectMoniker(V_BSTR(&vObjName), pMkThis, OLEWHICHMK_OBJFULL, pMkObject.ppi());

		WTRiASObject pNewObject;	
		INT_PTR hNewObject = 0;
#if defined(_USE_CLASSFACTORY_CACHE)
		HRESULT	hrCreated = FindInMapOrCreateObject(m_pTRiASObjectHandleMap, pMkObject, 
			hNewObject, pNewObject, MakeGDOObject, InitObj);
#else
		HRESULT	hrCreated = FindInMapOrCreateObject(m_pTRiASObjectHandleMap, pMkObject, 
			hNewObject, pNewObject, CLSID_GDOObject, InitObj);
#endif // defined(_USE_CLASSFACTORY_CACHE)
			
			_ASSERTE(pNewObject.IsValid());
			if (S_OK == hrCreated || bForceAdd) 
			{
				ERROR_FAILED_HRESULT(pTRiASObjects -> _Add(pNewObject, VARIANT_TRUE), E_FAIL);
			}
		}
		else if (GDB_E_FEATUREDOESNOTEXIST == hr)
			return S_FALSE;

	// next record
		EXT_ERROR_FAILED_HRESULT(rs -> MoveNext(), E_FAIL);
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ITRiASSearchObjects

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOObjects, ConsiderSearch, /*[in]*/ BSTR, Command, 
	/*[in, optional]*/ SAFEARRAY*, pParams) 
{
	COM_TRY {
		if (!wcsicmp(L"IntersectsWindow", Command))
			return S_OK;

	HRESULT hr;
	CPostFilter	postFilter;
	CComBSTR strKey;				// Feld in dem gesucht werden soll
	CComBSTR strFilter;				// Ausdruck nach dem gesucht werden soll
	CComBSTR strWhereClause;		// resultierende WHERE-Klausel
	short gmType;

		RETURN_FAILED_HRESULT(hr = RetrieveTextSearchParams(pParams, strKey, strFilter, gmType));
		if (FAILED(hr = postFilter.Setup (Command, strKey, strFilter, gmType, strWhereClause)))
			return hr;

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Parameter für Geometrierecherche

HRESULT CGDOObjects::RetrieveGeoSearchParams(SAFEARRAY *pParams, 
	WGDODatabase& rpGDODatabase, IDispatch **ppIGeometry, BOOL& bExact) 
{
	_ASSERTE(NULL != ppIGeometry);
	*ppIGeometry = NULL;

MC::ArrayVariant	arr;

	bExact = FALSE;
	arr.Attach(pParams);
	_ASSERTE(arr.Elements() > 0);

	if (arr.Elements() > 0)
	{
	CComVariant vRect = arr[0];

		ERROR_EXPR_FALSE(V_ISDISPATCH(&vRect), E_FAIL);

	////////////////////////////////////////////////////////////////
	// Rechteckgeometrie in ein Polygon umwandeln...
	W_DGMRectangleGeometry	rect(V_DISPATCH(&vRect));
	W_DGMPolygonGeometry	triasPoly(CLSID_TRiASCSPolygonGeometry);

		ERROR_FAILED_HRESULT(WPersistStreamInit(triasPoly)  ->  InitNew(), E_FAIL);
		ERROR_FAILED_HRESULT(MakePolyFromRect(triasPoly, rect), E_FAIL);

	////////////////////////////////////////////////////////////////
	// ... selbiges zurücktransformieren ...
		rpGDODatabase -> TransformGeometryInverse(triasPoly);

	////////////////////////////////////////////////////////////////
	// ... in ein Geomedia-Polygon verwandeln ...
	W_DGMPolygonGeometry	gmPoly(CLSID_PolygonGeometry);

		ERROR_FAILED_HRESULT(CopyPolygon(gmPoly, triasPoly), E_FAIL);
		*ppIGeometry = gmPoly.detach();
	}
	if (arr.Elements() > 1)
	{
		CComVariant vExact = arr[1];
		bExact = V_BOOL(&vExact) ? TRUE : FALSE;
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Parameter für Textrecherche

HRESULT CGDOObjects::RetrieveTextSearchParams(SAFEARRAY *pParams, CComBSTR& strKey, 
	CComBSTR& strFilter, short& gmType) 
{
	MC::ArrayVariant	arr;
	arr.Attach(pParams);
	_ASSERTE(arr.Elements() >= 2);
	if (arr.Elements() < 2)
		return S_FALSE;
	if (!V_ISBSTR(&arr[0]))
		return S_FALSE;
	WTRiASFeature pTRiASFeature;
	if (V_ISDISPATCH(&arr[1]))
	{
		pTRiASFeature = V_DISPATCH(&arr[1]);
	} 
	else if (V_ISI4(&arr[1])) {
		WTRiASObjectHandleMap Map(CLSID_TRiASFeatureHandleMap);		// throws hr
		RETURN_FAILED_HRESULT(Map -> GetObject(V_I4(&arr[1]), pTRiASFeature.ppu()));
	} else {
		return S_FALSE;
	}
	strFilter = V_BSTR(&arr[0]);
	RETURN_FAILED_HRESULT(pTRiASFeature -> get_Name(CLEARED(strKey)));

	{
		WTRiASFeatures	pTRiASFeatures;
		WTRiASFeature	pTRiASFeature2;
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_Features(pTRiASFeatures.ppi()), E_FAIL);
		HRESULT hr = pTRiASFeatures -> Item(CComVariant(strKey), pTRiASFeature2.ppi());
		if (TRIASDB_E_UNKNOWN_FEATURE == hr)
			return S_FALSE;
		ERROR_FAILED_HRESULT(hr, E_FAIL);
	}
	RETURN_FAILED_HRESULT(WGField(pTRiASFeature) -> get_Type(&gmType));
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Geometrierecherche

HRESULT CGDOObjects::DoSearchObjects(ITRiASObjects* pTRiASObjects, 
	IDispatch *pIGeometry, long lSpatialOperator) 
{
	TIMER_START(0, L"CGDOObjects::DoSearchObjects::Geometry")

// Filter in richtiges Koordinatensystem umrechnen
CComVariant vFilter;
CComBSTR bstrCSSGuid (GetPropertyFrom(BASE_OF_GDOOBJECTS(), g_cbCSSGuid, g_bstrNil));
HRESULT hr = E_FAIL;

	if (bstrCSSGuid.Length() > 0) {
	// CSS ist bekannt
	WAltCoordSystemPath path;

		if (SUCCEEDED(g_pDBEngine -> GetGMServerTransService() -> 
			CreateSimpleTransFromCSMtoServer(m_pDGMCoordSystemsMgr, 
				CComVariant(bstrCSSGuid), m_pGDatabase, path.ppi())))
		{
			hr = g_pDBEngine -> GetGMServerTransService() -> TransformGeometry(
				pIGeometry, path, gmtdToServer);
		}
	}

// Filter in Storageformat (Blob) umrechnen
	EXT_ERROR_FAILED_HRESULT(g_pDBEngine -> GetGMGeometryStorageService() -> 
		GeometryToStorage(pIGeometry, &vFilter), E_FAIL);

// Recordset geben lassen
AC_GRecordset rs;
WOriginatingPipe pO;
WDGMCSSTransformPipe pT;
CComBSTR strGeometryname;

	if (SUCCEEDED(hr)) {
	// SpatialFilter in OriginatingPipe (Server) auswerten
		RETURN_FAILED_HRESULT(GetPipes(strGeometryname, pO, pT));
		EXT_ERROR_FAILED_HRESULT(pO -> put_SpatialFilter(vFilter), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(pO -> put_SpatialOperator(CComVariant(lSpatialOperator)), NDB_E_NATIVEDB);
		ConnectPipes(pO, pT, strGeometryname);
		PrepareTransformation(g_pDBEngine -> GetGMServerTransService(), pO, m_pDGMCoordSystemsMgr, strGeometryname);
		EXT_ERROR_FAILED_HRESULT(pT -> get_OutputRecordset(rs.ppi()), NDB_E_NATIVEDB);
	}
	else {
	// SpatialFilter lokal (Client) auswerten
	WISpatialFilterPipe pF;

		RETURN_FAILED_HRESULT(GetPipes(strGeometryname, pO, pT, pF.ppi()));
		EXT_ERROR_FAILED_HRESULT(pF -> put_SpatialFilter(vFilter), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(pF -> put_SpatialOperator(lSpatialOperator), NDB_E_NATIVEDB);
		ConnectPipes(pO, pT, strGeometryname);
		PrepareTransformation(g_pDBEngine -> GetGMServerTransService(), pO, m_pDGMCoordSystemsMgr, strGeometryname);
		ConnectPipes(pT, pF, strGeometryname);
		EXT_ERROR_FAILED_HRESULT(pF -> get_OutputRecordset(rs.ppi()), NDB_E_NATIVEDB);
	}

long nObjects = 0;
CPostFilter	postFilter; 

	TIMER_CHECKPOINT(0, nObjects)
	RETURN_FAILED_HRESULT(DoLoadObjects(rs, pTRiASObjects, postFilter, nObjects, true));
	TIMER_CHECKPOINT(0, nObjects)
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Textrecherche

HRESULT	CGDOObjects::DoSearchObjects(ITRiASObjects* pTRiASObjects, 
	const CComBSTR& strTextFilter, CPostFilter& postFilter) 
{
	TIMER_START(0, L"CGDOObjects::DoSearchObjects::Text")

// sicherstellen, daß zusätzlich nicht existierende Geometrien weggefangen werden
CComBSTR bstrWhere(strTextFilter.Length() > 0 ? L" And " : L"");
CComBSTR bstrPGeomName;

	ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTS() -> get_DefaultGeometry(CLEARED(bstrPGeomName)), E_FAIL);
	bstrWhere.AppendBSTR(bstrPGeomName);
	bstrWhere.Append(L" Is Not Null");

AC_GRecordset rs;
WOriginatingPipe pO;

	RETURN_FAILED_HRESULT(GetPipe(pO));
	EXT_ERROR_FAILED_HRESULT(pO -> put_Filter(strTextFilter), NDB_E_NATIVEDB);
	EXT_ERROR_FAILED_HRESULT(pO -> get_OutputRecordset(rs.ppi()), NDB_E_NATIVEDB);
		
long nObjects = 0;

	TIMER_CHECKPOINT(0, nObjects)
	RETURN_FAILED_HRESULT(DoLoadObjects(rs, pTRiASObjects, postFilter, nObjects, true));
	TIMER_CHECKPOINT(0, nObjects)
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Recherche; hier wird alles verteilt...

CGDOObjects::CPostFilter::CPostFilter()
	: m_fFirst(true)
{
}

CGDOObjects::CPostFilter::~CPostFilter() 
{
}

HRESULT CGDOObjects::CPostFilter::operator() (AC_GRecordset& rs) 
{
	if (m_pDMatchString.IsValid()) {
		if (m_fFirst) {
			_ASSERTE(!m_fldToSearch.IsValid());

		WGFields flds;

			RETURN_FAILED_HRESULT(rs -> get_GFields (flds.ppi()));
			if (FAILED(flds -> get_Item(CComVariant(m_strKeyToSearch), 
				m_fldToSearch.ppi())))
			{
				return GDB_E_FEATUREDOESNOTEXIST;
			}

			m_fFirst = false;
		}
		if (!m_fldToSearch.IsValid())
			return E_UNEXPECTED;

	CComVariant	vValue;

		m_fldToSearch -> get_Value (CLEARED(vValue));
		vValue.ChangeType(VT_BSTR);
	
	int	nMatched;
	HRESULT hr = m_pDMatchString -> MatchString(V_BSTR(&vValue), &nMatched);
	
		return SUCCEEDED(hr) ? (nMatched > 0 ? S_OK : S_FALSE) : hr;
	}
	return S_OK;	// keine Vergleichsfunktion; also immer wahr
}

#include <TRiASDBModuleStrings.h>

const OLECHAR g_cbOpEqual[] = L" = ";
const OLECHAR g_cbOpLike[] = L" LIKE ";
const OLECHAR g_cbOpIS[] = L" IS ";
const OLECHAR g_cbOpNOT[] = L" NOT ";
const OLECHAR g_cbOpNULL[] = L" NULL ";
const OLECHAR g_cbMultiPattern[] = L"*";

// const OLECHAR SEARCHCOMMAND_MatchComplete[]		= L"MatchComplete";
// const OLECHAR SEARCHCOMMAND_MatchRegExpr[]		= L"MatchRegExpr";
// const OLECHAR SEARCHCOMMAND_MatchLike[]			= L"MatchLike";
// const OLECHAR SEARCHCOMMAND_ExistanceOnly[]		= L"ExistanceOnly";
// const OLECHAR SEARCHCOMMAND_IntersectsWindow[]	= L"IntersectsWindow";
//
// const OLECHAR SEARCHOPTION_PartialMatch[]		= L"PartialMatch";
// const OLECHAR SEARCHOPTION_PartialMatchBOB[]	= L"PartialMatchBOB";
// const OLECHAR SEARCHOPTION_IgnoreCase[]			= L"IgnoreCase";
// const OLECHAR SEARCHOPTION_NegateResult[]		= L"NegateResult";

DefineSmartInterface(MatchPlainText);					// WMatchPlainText
DefineSmartInterface(MatchRegExpr);						// WMatchRegExpr

HRESULT CGDOObjects::CPostFilter::Setup (
	const BSTR& strCommand, const CComBSTR& strKey, const CComBSTR& _strFilter, 
	const short gmType, CComBSTR& strWhereClause) 
{
WParseStringPairs pParseStringPairs(CLSID_ParseStringPairs);
long lPairs = 0;
CComBSTR strValue;

	RETURN_FAILED_HRESULT(pParseStringPairs -> put_Pattern(CComBSTR(g_cbCollatePattern)));
	RETURN_FAILED_HRESULT(pParseStringPairs -> Parse(strCommand, &lPairs));

CComBSTR strFilter(_strFilter);
CComBSTR strOperator(g_cbOpEqual);

bool bSubMatch = false;
bool bBOBMatch = false;
bool bNegMatch = false;
bool bLowMatch = false;

	if (S_OK == pParseStringPairs -> get_Value(CComBSTR(SEARCHOPTION_PartialMatch), 
		CLEARED(strValue)) && strValue && L"1" == strValue)
	{
		bSubMatch = true;
	}
	if (S_OK == pParseStringPairs -> get_Value(CComBSTR(SEARCHOPTION_PartialMatchBOB), 
		CLEARED(strValue)) && strValue && L"1" == strValue)
	{
		bSubMatch = true;
		bBOBMatch = true;
	}
	if (S_OK == pParseStringPairs -> get_Value(CComBSTR(SEARCHOPTION_NegateResult), 
		CLEARED(strValue)) && strValue && L"1" == strValue)
	{
		bNegMatch = true;
	}
	if (S_OK == pParseStringPairs -> get_Value(CComBSTR(SEARCHOPTION_IgnoreCase), 
		CLEARED(strValue)) && strValue && L"1" == strValue)
	{
		bLowMatch = true;
	}

LPCWSTR	pEnd = wcschr(strCommand, L';');
int nChars = (NULL == pEnd) ? wcslen(strCommand) - 1 : pEnd - strCommand;

	RETURN_EXPR_FALSE(nChars > 0, E_FAIL);
	if (!wcsnicmp(strCommand, SEARCHCOMMAND_ExistanceOnly, nChars))
	{
	// ==>> WHERE Key IS NOT NULL
		strFilter = g_cbOpNOT;
		strFilter.Append(g_cbOpNULL);
		strOperator=g_cbOpIS;
	} 
	else if (gdbText == gmType && !wcsnicmp(strCommand, SEARCHCOMMAND_MatchComplete, nChars)) 
	{
		if (bBOBMatch)
		{
		// ==>> WHERE Key LIKE 'foo*'
			strFilter.Append(g_cbMultiPattern);
			strOperator=g_cbOpLike;
		} 
		else if (bSubMatch)
		{
		// ==>> WHERE Key LIKE '*foo*'
		CComBSTR S(g_cbMultiPattern);
	
			S.Append(strFilter);
			S.Append(g_cbMultiPattern);
			strFilter = S;
			strOperator=g_cbOpLike;
		} else 
		{
			return TRIASDB_S_SEARCH_NOT_SUPPORTED;
		}
		strFilter = QuoteStatement(strFilter);
	} 
	else {
	WUnknown pUnknown;

		if (!wcsnicmp(strCommand, SEARCHCOMMAND_MatchComplete, nChars))
		{
			WMatchPlainText	pMatchPlainText;
			RETURN_FAILED_HRESULT(::CoCreateInstance(CLSID_MatchPlainTextExakt, NULL, CLSCTX_INPROC_SERVER, pUnknown.GetIID(), pUnknown.ppv()));
			RETURN_FAILED_HRESULT(pUnknown -> QueryInterface(pMatchPlainText.ppi()));
			RETURN_FAILED_HRESULT(pMatchPlainText -> put_FullMatch(bSubMatch ? VARIANT_FALSE : VARIANT_TRUE));
			RETURN_FAILED_HRESULT(pMatchPlainText -> put_TestBOB(bBOBMatch ? VARIANT_TRUE : VARIANT_FALSE));
		} 
		else if (0 == wcsnicmp(strCommand, SEARCHCOMMAND_MatchRegExpr, nChars)) 
		{
			WMatchRegExpr	pMatchRegExpr;
			RETURN_FAILED_HRESULT(::CoCreateInstance(CLSID_MatchRegExprExakt, NULL, CLSCTX_INPROC_SERVER, pUnknown.GetIID(), pUnknown.ppv()));
			RETURN_FAILED_HRESULT(pUnknown -> QueryInterface(pMatchRegExpr.GetIID(), pMatchRegExpr.ppv()));
			RETURN_FAILED_HRESULT(pMatchRegExpr -> put_FullMatch(bSubMatch ? VARIANT_FALSE : VARIANT_TRUE));
		} 
		else if (0 == wcsnicmp(strCommand, SEARCHCOMMAND_MatchLike, nChars)) 
		{
			RETURN_FAILED_HRESULT(::CoCreateInstance(CLSID_MatchFuzzy, NULL, CLSCTX_INPROC_SERVER, pUnknown.GetIID(), pUnknown.ppv()));
		} 
		else {
			return TRIASDB_S_SEARCH_NOT_SUPPORTED;
		}
		
		RETURN_FAILED_HRESULT(pUnknown -> QueryInterface(m_pDMatchString.ppi()));
		RETURN_FAILED_HRESULT(m_pDMatchString -> put_MatchText(strFilter));
		m_strKeyToSearch = strKey;
		strOperator.Empty();	// kein Operator, also kein SQL ;-))
	}
	strWhereClause.Empty();
	if (!strOperator)
	{
		RETURN_FAILED_HRESULT(m_pDMatchString -> put_NegateMatch(bNegMatch ? VARIANT_TRUE : VARIANT_FALSE));
		RETURN_FAILED_HRESULT(m_pDMatchString -> put_MatchCase(bLowMatch ? VARIANT_FALSE : VARIANT_TRUE));
	} 
	else {
		if (bNegMatch)
		{
			strWhereClause.Append(g_cbOpNOT);		// ==>> WHERE NOT Key ...
			strWhereClause.Append(L" ");
		}
		strWhereClause.Append(strKey);
		strWhereClause.Append(strOperator);
		strWhereClause.Append(strFilter);
	}
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_3(CGDOObjects, SearchObjects, /*[in]*/ BSTR, Command, 
	/*[in]*/ ITRiASObjects*, pTRiASObjects, /*[in, optional]*/ SAFEARRAY *, pParams) 
{
	COM_TRY {
	CComBSTR strCommand(Command);
	HRESULT hr;

		if (!wcsicmp(L"IntersectsWindow", Command))	{
		WGDODatabase pGDODatabase;
		WDispatch Geometry;
		BOOL bExact;

			ERROR_FAILED_HRESULT(FindSpecificParent(GetUnknown(), pGDODatabase.ppi()), GDO_E_NOPARENT);
			RETURN_FAILED_HRESULT(hr = RetrieveGeoSearchParams(pParams, pGDODatabase, Geometry.ppi(), bExact));
			if (S_FALSE == hr)
				return hr;
			RETURN_FAILED_HRESULT(DoSearchObjects(pTRiASObjects, Geometry, gdbTouches));
		} 
		else {
		CPostFilter	postFilter;
		CComBSTR strKey;				// Feld in dem gesucht werden soll
		CComBSTR strFilter;				// Ausdruck nach dem gesucht werden soll
		CComBSTR strWhereClause;		// resultierende WHERE-Klausel
		short gmType;

			RETURN_FAILED_HRESULT(hr = RetrieveTextSearchParams(pParams, strKey, strFilter, gmType));
			RETURN_FAILED_HRESULT(hr = postFilter.Setup(Command, strKey, strFilter, gmType, strWhereClause));
			RETURN_FAILED_HRESULT(hr = DoSearchObjects(pTRiASObjects, strWhereClause, postFilter));
			if (S_FALSE == hr)
				return hr;
		}	
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOObjects, ConstraintObjects, /*[in]*/ ITRiASObjects*, pObjs) 
{
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist

STDMETHODIMP CGDOObjects::GetClassID(CLSID *pClassID)
{
	if (NULL == pClassID) 
		return E_POINTER;

	*pClassID = CLSID_GDOObjects;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPersistStream

STDMETHODIMP CGDOObjects::IsDirty(void)
{
	return m_fIsDirty ? S_OK : WPersistStreamInit(m_BaseUnk) -> IsDirty();
}

STDMETHODIMP CGDOObjects::Load(LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;

	COM_TRY {
	// Properties modifizieren
	WTRiASPropertyMapHandler MapHandler(m_BaseUnk);

		THROW_FAILED_HRESULT(MapHandler -> AddMapEntry(CComBSTR(g_cbGenericMap), 
			(INT_PTR)&CLSID_TRiASGenericHandleMap, PROPERTYSUPPORT_NOFLAGS, vtMissing));

	// unsere daten laden
	long lSignature = 0L;

		THROW_FAILED_HRESULT(LoadLong(pStm, lSignature));			// Signatur
		if (GDOOBJECTS_SIGNATURE != lSignature)
			return E_UNEXPECTED;

	long lVersion = 0L;

		THROW_FAILED_HRESULT(LoadLong(pStm, lVersion));			// VersionInfo
		if (lVersion > LASTKNOWN_GDOOBJECTS_VERSION)
			return E_UNEXPECTED;

	// jetzt alles andere laden
		THROW_FAILED_HRESULT(WPersistStreamInit(m_BaseUnk) -> Load(pStm));

	} COM_CATCH;
	m_fIsDirty = false;
	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CGDOObjects::Save(LPSTREAM pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(SaveLong(pStm, GDOOBJECTS_SIGNATURE));
	RETURN_FAILED_HRESULT(SaveLong(pStm, LASTKNOWN_GDOOBJECTS_VERSION));

	RETURN_FAILED_HRESULT(WPersistStreamInit(m_BaseUnk) -> Save(pStm, fClearDirty));
	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CGDOObjects::GetSizeMax(ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) 
		return E_POINTER;

	RETURN_FAILED_HRESULT(WPersistStreamInit(m_BaseUnk) -> GetSizeMax(pcbSize));
	pcbSize -> QuadPart += 3*sizeof(long);
	return S_OK;
}

STDMETHODIMP CGDOObjects::InitNew(void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;

	COM_TRY {
	// Properties modifizieren
	WTRiASPropertyMapHandler MapHandler(m_BaseUnk);

		THROW_FAILED_HRESULT(MapHandler -> AddMapEntry(CComBSTR(g_cbGenericMap), 
			(INT_PTR)&CLSID_TRiASGenericHandleMap, PROPERTYSUPPORT_NOFLAGS, vtMissing));

	// jetzt fertig initialiseren
		THROW_FAILED_HRESULT(WPersistStreamInit(m_BaseUnk) -> InitNew());

	} COM_CATCH;
	m_fIsDirty = false;	
	m_fIsInitialized = true;
	return S_OK;
}

