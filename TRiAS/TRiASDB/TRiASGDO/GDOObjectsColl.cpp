// GDOObjectsColl.cpp : Implementation of CTRiASGDOApp and DLL registration.

#include "stdafx.h"
#include "TRiASGDOImpl.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#include "GDOObjectsColl.h"
#include "GDOObjects.h"

//HRESULT CGDOObjectsCollection::CreateInstance(IGDOObjectsCollection** ppObjectsCollection) 
//{
//CComObject<CGDOObjectsCollection> *pObjectsCollection = NULL;
//
//	RETURN_FAILED_HRESULT(CComObject<CGDOObjectsCollection>::CreateInstance(&pObjectsCollection));
//	(*ppObjectsCollection = pObjectsCollection) -> AddRef();
//	return S_OK;
//}

/////////////////////////////////////////////////////////////////////////////
//

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOObjectsCollection, InitTarget
		, /*[in]SAFEARRAY(IUnknown*)*/ SAFEARRAY*, pObjects
		, VARIANT_BOOL, bWritable
)
{
	COM_TRY {
	CComSemaphore<_ThreadModel> Sem(m_lInitData);	// doppeltes Initialisieren verhindern
	MC::ArrayUnknown arr;
	
		arr.Attach(pObjects);
		m_pDGMConnection = arr[0];
		m_pGDatabase = arr[1];
		m_pDGMCoordSystemsMgr = arr[2];
		m_bWritable = bWritable;

	WTRiASConnection Conn;

		ERROR_FAILED_HRESULT(FindSpecificParent(GetUnknown(), Conn.ppi()), E_FAIL);

	WTRiASMDSMap MDSMap (GetPropertyFrom(WTRiASPropertyBase(Conn), g_cbMetaDataMap, (IDispatch *)NULL), false);

		m_pTRiASMDSMap = MDSMap;
		CHECK_INITIALIZED();

	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_0(CGDOObjectsCollection, SetupCollection) 
{
HRESULT	hr;
CComBSTR strTablename;
CComBSTR strClassname;
CComBSTR strDescription;
CComVariant	vData;
CComBSTR strPrimGeom;
long lGeomType;
WTRiASObjects pTRiASObjects;

	RETURN_FAILED_HRESULT(ClearMDSMap());

// Metadaten auslesen
CComVariant vTableNames;
long lTableMask = 0;			// alle Tabellen
W_MetadataService pMetadataService;
IDispatch *pRawDisp = m_pDGMConnection;

	RETURN_FAILED_HRESULT(pMetadataService.CreateInstance (CLSID_MetadataService));
	EXT_ERROR_FAILED_HRESULT(pMetadataService -> putref_Connection(&pRawDisp), NDB_E_NATIVEDB);
	RETURN_FAILED_HRESULT(pMetadataService -> GetTables(&lTableMask, CLEARED(vTableNames)));
	ERROR_EXPR_FALSE(V_ISARRAY(&vTableNames) && V_ISBSTR(&vTableNames), E_FAIL);

MC::ArrayString	arrTables;

	arrTables.Attach(V_ARRAY(&vTableNames));
	for (long nTable = 0; nTable < arrTables.Elements(); ++nTable) {
		strTablename = arrTables[nTable];
		if (0 == strTablename.Length())
			continue;

	W_TableProperty	tblProp = W_TableProperty(CLSID_TableProperty);
	IDispatch *pDisp = tblProp;		// kein QI, kein AddRef() !!
	long lValid;			// ???
		
		RETURN_FAILED_HRESULT(pMetadataService -> put_TableName(&strTablename));
		if (FAILED(hr = pMetadataService -> GetTableMetadata(&pDisp, &lValid)))
		{
			_ASSERTE(SUCCEEDED(hr));
			continue;
		}

		RETURN_FAILED_HRESULT(tblProp -> get_GeometryType(&lGeomType));
		if (gdbPoint != lGeomType && gdbLinear != lGeomType && gdbAreal != lGeomType && 
			gdbAnySpatial != lGeomType && gdbCoverage != lGeomType && gdbGraphicsText != lGeomType && 
			gdbGraphic != lGeomType) 
		{
			continue;		// keine Geometrie ==> normale Datentabelle ==> ignorieren
		}
		if (gdbCoverage == lGeomType || gdbGraphicsText == lGeomType)
		{
			_ASSERTE(E_FAIL == S_OK);		// anhalten; muß untersucht werden...
			continue;
		}
	
	// sicherstellen, daß Primärgeometriefeld existiert
		RETURN_FAILED_HRESULT(tblProp -> get_PrimaryGeometryFieldName(CLEARED(strPrimGeom)));

	HRESULT hrSearch;
	CComBSTR strOKS;
	
		ERROR_FAILED_HRESULT(hrSearch = SearchMDSMap(m_pTRiASMDSMap, strTablename, strOKS, lSearchName), GDO_E_METADATA);
		if (S_FALSE == hrSearch) {
		// noch nicht in der Map; Eintrag erzeugen und sinnvoll vorbelegen
			strClassname = strTablename;
			tblProp -> get_Description(CLEARED(strDescription));
			strOKS = _T("0");

		// einen NULL-Eintrag erzeugen; bei Objekterzeugung wird umklassifiziert und zwar
		// vom OKS "0" (mit dem das Objekt erstmal initialisiert wird) zum eigentlichen OKS; 
		// dazu muß der OKS "0" aber auch vorhanden sein.
			m_pTRiASMDSMap -> SetAt(strOKS, strTablename, strClassname, strDescription, vData);
		} 
		else {
			m_pTRiASMDSMap -> GetAt(strOKS, CLEARED(strTablename), CLEARED(strClassname), CLEARED(strDescription), CLEARED(vData));
		}

	// jetzt Objekt erzeugen/wiederfinden
		RETURN_FAILED_HRESULT(GetOrCreateObjectsDef(strOKS, strTablename, strClassname, strDescription, lGeomType, pTRiASObjects.ppi()));
	}
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////
// eine einzelne Tabelle löschen

HRESULT	CGDOObjectsCollection::DeleteTable(W_MetadataService& pMetadataService, /*const*/ CComBSTR& strTablename) 
{
long lValid;
W_TableProperty	tblProp(CLSID_TableProperty); 
IDispatch *pDispTblProp = tblProp;
WGTableDefs pGTableDefs;
WGTableDef pGTableDef;
HRESULT	hr;

	{
	DBTransaction	dbTrans(m_pGDatabase);

		EXT_ERROR_FAILED_HRESULT(pMetadataService -> put_TableName(&strTablename), NDB_E_NATIVEDB);
		hr = pMetadataService -> GetTableMetadata(&pDispTblProp, &lValid);
		_ASSERTE(SUCCEEDED(hr));		// zwar nicht fatal aber immerhin debuggenswert

		hr = pMetadataService -> DeleteTableMetadata(&lValid);
		_ASSERTE(SUCCEEDED(hr));

		EXT_ERROR_FAILED_HRESULT(m_pGDatabase -> get_GTableDefs(pGTableDefs.ppi()), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(pGTableDefs -> Delete(strTablename), NDB_E_NATIVEDB);
		dbTrans.Succeeded();
	}
	return S_OK;
}

HRESULT	CGDOObjectsCollection::DeleteTables(W_MetadataService& pMetadataService, VARIANT_BOOL* pbChanged) 
{
CComBSTR strTablename;
CComBSTR strClassname;
CComBSTR strDescription;
CComVariant	vData;
map<CComBSTR, bool>::iterator i = m_strTablesToDelete.begin();

	for (/**/; m_strTablesToDelete.end() != i; ++i)
	{
		m_pTRiASMDSMap -> GetAt((*i).first, CLEARED(strTablename), CLEARED(strClassname), CLEARED(strDescription), CLEARED(vData));
		if (SUCCEEDED(DeleteTable(pMetadataService, strTablename)))
		{
			m_pTRiASMDSMap -> RemoveAt((*i).first);
		}
		*pbChanged = VARIANT_TRUE;
	}
	m_strTablesToDelete.clear();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////
// einen einzelnen Tabellennamen ändern

HRESULT	CGDOObjectsCollection::UpdateTable(W_MetadataService& pMetadataService, WTRiASObjects& pTRiASObjects, /*const*/ CComBSTR& strOldTablename, /*const*/ CComBSTR& strNewTablename) 
{
long lValid;
W_TableProperty	tblProp(CLSID_TableProperty); 
IDispatch *pDispTblProp = tblProp;

// Teil 1... der Tabellenname
WGTableDefs	pGTableDefs;
WGTableDef	pGTableDef;
HRESULT		hr;

	EXT_ERROR_FAILED_HRESULT(m_pGDatabase -> get_GTableDefs(pGTableDefs.ppi()), NDB_E_NATIVEDB);
	EXT_ERROR_FAILED_HRESULT(pGTableDefs -> get_Item(CComVariant(strOldTablename), pGTableDef.ppi()), NDB_E_NATIVEDB);
	{
	DBTransaction	dbTrans(m_pGDatabase);

		EXT_ERROR_FAILED_HRESULT(pMetadataService -> put_TableName(&strOldTablename), NDB_E_NATIVEDB);
		hr = pMetadataService -> GetTableMetadata(&pDispTblProp, &lValid);
		_ASSERTE(SUCCEEDED(hr));		// zwar nicht fatal aber immerhin debuggenswert

	CComBSTR bstrPrimGeomName, bstrDescription;

		EXT_ERROR_FAILED_HRESULT(tblProp -> get_PrimaryGeometryFieldName(&bstrPrimGeomName), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(tblProp -> get_Description(&bstrDescription), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(pMetadataService -> DeleteTableMetadata(&lValid), NDB_E_NATIVEDB);

		EXT_ERROR_FAILED_HRESULT(pGTableDef -> put_Name(strNewTablename), NDB_E_NATIVEDB);
		tblProp.Assign(NULL);		// wird nicht mehr benötigt
		pGTableDef.Assign(NULL);

#if defined(_DEBUG)
	WGTableDefs Tables;
	short lCount = 0;

		EXT_ERROR_FAILED_HRESULT(m_pGDatabase -> get_GTableDefs(Tables.ppi()), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(Tables -> get_Count(&lCount), NDB_E_NATIVEDB);
		for (long i = 0; i < lCount; ++i) {
		WGTableDef Table;
		CComBSTR bstrTableName;

			EXT_ERROR_FAILED_HRESULT(Tables -> get_Item(CComVariant(i), Table.ppi()), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(Table -> get_Name(CLEARED(bstrTableName)), NDB_E_NATIVEDB);
		}
#endif // defined(_DEBUG)

	// Metadaten nachführen
		EXT_ERROR_FAILED_HRESULT(pMetadataService -> put_TableName(&strNewTablename), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(pMetadataService -> VerifyMetadata(&lValid), NDB_E_NATIVEDB);

//	W_TableProperty	tblPropNew(CLSID_TableProperty); 
//
//		pDispTblProp = tblPropNew;
//		EXT_ERROR_FAILED_HRESULT(tblPropNew -> put_Name(&strNewTablename), NDB_E_NATIVEDB);
//		EXT_ERROR_FAILED_HRESULT(tblPropNew -> put_PrimaryGeometryFieldName(&bstrPrimGeomName), NDB_E_NATIVEDB);
//		EXT_ERROR_FAILED_HRESULT(tblPropNew -> put_Description(&bstrDescription), NDB_E_NATIVEDB);
//		EXT_ERROR_FAILED_HRESULT(pMetadataService -> AddTableMetadata(&pDispTblProp, &lValid), NDB_E_NATIVEDB);

		dbTrans.Succeeded();
	}
	return S_OK;
}

HRESULT CGDOObjectsCollection::UpdateTables(W_MetadataService& pMetadataService, VARIANT_BOOL *pbChanged) 
{
CComBSTR strOKS;
CComBSTR strTablename, strNewTablename;
CComBSTR strClassname;
CComBSTR strDescription;
CComVariant	vData;

CComVariant 	vTRiASObjects;
WTRiASObjects pTRiASObjects;
WGDOObjects pGDOObjects;
WEnumVARIANT Enum;

	ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTSCOLLECTION -> _NewEnum(Enum.ppu()), E_FAIL);
	for (Enum -> Reset(); S_OK == Enum -> Next(1, CLEARED(vTRiASObjects), NULL); /**/)
	{
		ERROR_EXPR_FALSE(V_ISDISPATCH(&vTRiASObjects), E_FAIL);
		ERROR_FAILED_HRESULT(V_DISPATCH(&vTRiASObjects) -> QueryInterface(pTRiASObjects.GetIID(), pTRiASObjects.ppv()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASObjects -> QueryInterface(pGDOObjects.GetIID(), pGDOObjects.ppv()), E_FAIL);

		ERROR_FAILED_HRESULT(pTRiASObjects -> get_OKS(CLEARED(strOKS)), GDO_E_OBJECTS);
		ERROR_FAILED_HRESULT(m_pTRiASMDSMap -> GetAt(strOKS, CLEARED(strTablename), CLEARED(strClassname), CLEARED(strDescription), CLEARED(vData)), GDO_E_METADATA);
#if defined(_DEBUG)
		{	// Konsistenz testen
		CComBSTR strObjTablename, strObjClassname, strObjDescription;
		
			ERROR_FAILED_HRESULT(pGDOObjects -> get_Tablename(CLEARED(strObjTablename)), GDO_E_OBJECTS);
			ERROR_FAILED_HRESULT(pTRiASObjects -> get_Name(CLEARED(strObjClassname)), GDO_E_OBJECTS);
			ERROR_FAILED_HRESULT(pTRiASObjects -> get_Description(CLEARED(strObjDescription)), GDO_E_OBJECTS);
			_ASSERTE(strTablename == strObjTablename);
			_ASSERTE(strClassname == strObjClassname);
			_ASSERTE(strDescription == strObjDescription);
		}
#endif

	// Feldnamensänderungen in der Tabelle rückschreiben
		ERROR_FAILED_HRESULT(pGDOObjects -> Save(pbChanged), E_FAIL);

		ERROR_FAILED_HRESULT(NormalizeName(strClassname, strNewTablename), E_FAIL);
		if (strTablename == strNewTablename)
			continue;

	// jetzt eigentliche Tabelle ändern
	long lValid;

		RETURN_FAILED_HRESULT(UpdateTable(pMetadataService, pTRiASObjects, strTablename, strNewTablename));

		EXT_ERROR_FAILED_HRESULT(pMetadataService -> VerifyMetadata(&lValid), NDB_E_NATIVEDB);
		ERROR_FAILED_HRESULT(pGDOObjects -> put_Tablename(strNewTablename), GDO_E_OBJECTS);
		ERROR_FAILED_HRESULT(m_pTRiASMDSMap -> SetAt(strOKS, strNewTablename, strClassname, strDescription, vData), GDO_E_METADATA);
		*pbChanged = VARIANT_TRUE;
	}
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_0(CGDOObjectsCollection, Save)
{
	if (!m_bWritable)
		return S_FALSE;

	COM_TRY {
	W_MetadataService	pMetadataService(CLSID_MetadataService);
	IDispatch	*pRawDisp = m_pDGMConnection;
	
		EXT_ERROR_FAILED_HRESULT(pMetadataService -> putref_Connection(&pRawDisp), NDB_E_NATIVEDB);
	
	VARIANT_BOOL	bChanged = VARIANT_FALSE;
	
		RETURN_FAILED_HRESULT(UpdateTables(pMetadataService, &bChanged));
		RETURN_FAILED_HRESULT(DeleteTables(pMetadataService, &bChanged));

	// Änderungen in Metadaten einfach über VerifyMetadata; ist schneller und übersichtlicher
	// als alle Änderungen von Hand mitzuziehen
		if (bChanged) {
		long lValid;

			EXT_ERROR_FAILED_HRESULT(pMetadataService -> VerifyMetadata(&lValid), NDB_E_NATIVEDB);
		}

	// Langbeschreibungen in jedem Fall aktualisieren
		RedescribeTableMetadata(pMetadataService);

	} COM_CATCH;
	return S_OK;
}

HRESULT CGDOObjectsCollection::FindClassname(const BSTR& strFullOKS, CComBSTR& strFoundOKS) 
{
CComBSTR strOKS;
CComBSTR strClassname;
CComBSTR strTablename;

	ERROR_FAILED_HRESULT(m_pTRiASMDSKey -> SplitOKS(strFullOKS, CLEARED(strClassname), CLEARED(strOKS)), E_FAIL);
	if (0 == strClassname.Length())		// kein Kurzbezeichner angegeben, erst mal OKS nehmen
		strClassname = strOKS;
	NormalizeName(strClassname, strTablename);
	if (S_OK == SearchMDSMap(m_pTRiASMDSMap, strOKS, strFoundOKS, lSearchKey))
		return S_OK;
	if (S_OK == SearchMDSMap(m_pTRiASMDSMap, strTablename, strFoundOKS, lSearchName))
		return S_OK;
	return E_FAIL;
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOObjectsCollection, Item
	, VARIANT, vIndex
	, VARIANT*, vItem
)
{
	COM_TRY {
		ERROR_EXPR_FALSE(V_ISBSTR(&vIndex), E_INVALIDARG);

	HRESULT hr;
	CComBSTR strOKS;
	WTRiASObjects pTRiASObjects;
		
//		FindClassname(V_BSTR(&vIndex), strOKS);
		if (FAILED(hr = BASE_OF_GDOOBJECTSCOLLECTION  ->  Item(vIndex, /*CComVariant(strOKS), */pTRiASObjects.ppi()))) 
			return hr;

	CComVariant	vObjects(pTRiASObjects);

		vObjects.Detach(vItem);
	} COM_CATCH
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////
// diejenigen Einträge aus den Metadaten entfernen, die nicht oder nicht mehr als
// Tablle vorhanden sind (wenn z.B. Tabellennamen außerhalb geändert wurden)

HRESULT	CGDOObjectsCollection::ClearMDSMap() 
{
WEnumVARIANT vEnum;
CComVariant vOKS;
CComBSTR strTablename;
CComBSTR strClassname;
CComBSTR strDescription;
CComVariant	vData;

W_MetadataService pMetadataService;
IDispatch *pRawDisp = m_pDGMConnection;

	RETURN_FAILED_HRESULT(pMetadataService.CreateInstance(CLSID_MetadataService));
	EXT_ERROR_FAILED_HRESULT(pMetadataService -> putref_Connection(&pRawDisp), NDB_E_NATIVEDB);

long lValid;
W_TableProperty	tblProp(CLSID_TableProperty); 
IDispatch *pDispTblProp = tblProp;

	m_pTRiASMDSMap -> _NewEnum(vEnum.ppu());
	for (vEnum -> Reset(); S_OK == vEnum -> Next(1, CLEARED(vOKS), NULL); /**/)
	{
		ERROR_EXPR_FALSE(V_ISBSTR(&vOKS), E_FAIL);
		m_pTRiASMDSMap -> GetAt(V_BSTR(&vOKS), CLEARED(strTablename), CLEARED(strClassname), CLEARED(strDescription), CLEARED(vData));
		EXT_ERROR_FAILED_HRESULT(pMetadataService -> put_TableName(&strTablename), NDB_E_NATIVEDB);
		if (FAILED(pMetadataService -> GetTableMetadata(&pDispTblProp, &lValid)))
		{
			m_pTRiASMDSMap -> RemoveAt(V_BSTR(&vOKS));
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////
// Irgendwo haben sich Tabellennamen / Feldnamen geändert; die entsprechenden
// Metadaten müssen mit den neuen Beschreibungen versehen werden...

HRESULT	CGDOObjectsCollection::RedescribeTableMetadata(W_MetadataService& pMetadataService) 
{
	WEnumVARIANT	objsEnum;
	CComVariant		vTRiASObjects;
	WTRiASObjects	pTRiASObjects;
	CComBSTR		strOKS;
	CComBSTR		strTablename;
	CComBSTR		strClassname;
	CComBSTR		strDescription;
	CComVariant		vData;

	WTRiASFeatures	pTRiASFeatures;

	long	lValid;
	W_TableProperty	tblProp(CLSID_TableProperty); 
	IDispatch	*pDispTblProp = tblProp;

	ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTSCOLLECTION -> _NewEnum(objsEnum.ppu()), E_FAIL);
	for (objsEnum -> Reset(); S_OK == objsEnum -> Next(1, CLEARED(vTRiASObjects), NULL); /**/)
	{
		ERROR_EXPR_FALSE(V_ISDISPATCH(&vTRiASObjects), E_FAIL);
		ERROR_FAILED_HRESULT(V_DISPATCH(&vTRiASObjects) -> QueryInterface(pTRiASObjects.GetIID(), pTRiASObjects.ppv()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASObjects -> get_OKS(CLEARED(strOKS)), E_FAIL);
		ERROR_FAILED_HRESULT(m_pTRiASMDSMap -> GetAt(strOKS, CLEARED(strTablename), CLEARED(strClassname), CLEARED(strDescription), CLEARED(vData)), GDO_E_METADATA);

		EXT_ERROR_FAILED_HRESULT(pMetadataService -> put_TableName(&strTablename), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(pMetadataService -> GetTableMetadata(&pDispTblProp, &lValid), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(tblProp -> put_Description(&strDescription), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(pMetadataService -> SetTableMetadata(&pDispTblProp, &lValid), NDB_E_NATIVEDB);
		
		ERROR_FAILED_HRESULT(pTRiASObjects -> get_Features(pTRiASFeatures.ppi()), E_FAIL);
		RETURN_FAILED_HRESULT(RedescribeFieldMetadata(pMetadataService, pTRiASFeatures));
		ERROR_FAILED_HRESULT(pTRiASObjects -> get_GeometryFeatures(pTRiASFeatures.ppi()), E_FAIL);
		RETURN_FAILED_HRESULT(RedescribeFieldMetadata(pMetadataService, pTRiASFeatures));
	}
	return S_OK;
}

HRESULT	CGDOObjectsCollection::RedescribeFieldMetadata(W_MetadataService& pMetadataService, ITRiASFeatures* pTRiASFeatures) 
{
	WEnumVARIANT	featEnum;
	CComVariant		vTRiASFeature;
	WTRiASFeature	pTRiASFeature;
	WGDOFeature		pGDOFeature;
	CComBSTR		strFieldname;
	CComBSTR		strDescription;

	long	lValid;
	W_FieldProperty	fldProp(CLSID_FieldProperty);
	IDispatch	*pDispFldProp = fldProp;

	ERROR_FAILED_HRESULT(pTRiASFeatures -> _NewEnum(featEnum.ppu()), E_FAIL);
	for (featEnum -> Reset(); S_OK == featEnum -> Next(1, CLEARED(vTRiASFeature), NULL); /**/)
	{
		ERROR_EXPR_FALSE(V_ISDISPATCH(&vTRiASFeature), E_FAIL);
		ERROR_FAILED_HRESULT(V_DISPATCH(&vTRiASFeature) -> QueryInterface(pTRiASFeature.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASFeature -> QueryInterface(pGDOFeature.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pGDOFeature -> get_Fieldname(CLEARED(strFieldname)), E_FAIL);
		pTRiASFeature -> get_Description(CLEARED(strDescription));		// existiert ggf. nicht

		EXT_ERROR_FAILED_HRESULT(fldProp -> put_Name(&strFieldname), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(pMetadataService -> GetFieldMetadata(&pDispFldProp, &lValid), NDB_E_NATIVEDB);
		if (strDescription.Length() > 0)
		{
			EXT_ERROR_FAILED_HRESULT(fldProp -> put_Description(&strDescription), E_FAIL);
		}
		EXT_ERROR_FAILED_HRESULT(pMetadataService -> SetFieldMetadata(&pDispFldProp, &lValid), NDB_E_NATIVEDB);
	}
	return S_OK;
}

HRESULT CGDOObjectsCollection::SetDirty() 
{
	WTRiASDatabase	pTRiASDatabase;
	ERROR_FAILED_HRESULT(FindSpecificParent(GetUnknown(), pTRiASDatabase.GetIID(), pTRiASDatabase.ppv()), E_FAIL);
	ERROR_FAILED_HRESULT(pTRiASDatabase -> put_IsDirty(VARIANT_TRUE), E_FAIL);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////
// Name oder OKS hat sich geändert; d.h. daß wir unter dem neuen Namen für die
// Klasse nicht mehr das korrekte Handle finden werden 
//      ==> altes Handle dem neuen Namen zuordnen

HRESULT CGDOObjectsCollection::RemapObjects(WTRiASObjects& pTRiASObjects) 
{
INT_PTR hObjects = 0;
WTRiASObjects pOldTRiASObjects;

	ERROR_FAILED_HRESULT(pTRiASObjects -> get_Handle(&hObjects), E_FAIL);
	ERROR_FAILED_HRESULT(m_pTRiASObjectHandleMap -> GetObject(hObjects, 
		pOldTRiASObjects.ppu()), E_FAIL);
	ERROR_FAILED_HRESULT(m_pTRiASObjectHandleMap -> RemoveObject(hObjects, 
		OBJECTMAPMODE_RemoveAllReferences), E_FAIL);

WMoniker pMk;
CComBSTR strObjName;

	RETURN_FAILED_HRESULT(MkGetMoniker(pTRiASObjects, OLEGETMONIKER_ONLYIFTHERE, 
		OLEWHICHMK_OBJFULL, pMk.ppi()));
	RETURN_FAILED_HRESULT(MkGetDisplayName(pMk, CLEARED(strObjName)));

	ERROR_FAILED_HRESULT(m_pTRiASObjectHandleMap -> GetObjectHandle(
		CComVariant(strObjName), pTRiASObjects, 
		(OBJECTMAPMODE)(OBJECTMAPMODE_UsePredefinedHandle | OBJECTMAPMODE_CreateObjectHandle), 
		&hObjects), E_FAIL);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////
// eine Objektklasse hat einen neuen OKS bekommen...

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOObjectsCollection, ReclassObjects
		, IGDOObjects*, pGDOObjects
		, BSTR, strOldOKS
)
{
	COM_TRY {
	WTRiASObjects pTRiASObjects(pGDOObjects);
	CComBSTR strNewOKS;
	CComBSTR strTablename;
	CComBSTR strClassname;
	CComBSTR strDescription;
	CComVariant	vData;

		RETURN_FAILED_HRESULT(RemapObjects(pTRiASObjects));
		ERROR_FAILED_HRESULT(pTRiASObjects -> get_OKS(CLEARED(strNewOKS)), GDO_E_OBJECTS);
		ERROR_FAILED_HRESULT(m_pTRiASMDSMap -> GetAt(strOldOKS, CLEARED(strTablename), 
			CLEARED(strClassname), CLEARED(strDescription), CLEARED(vData)), GDO_E_METADATA);
		ERROR_FAILED_HRESULT(m_pTRiASMDSMap -> RemoveAt(strOldOKS), GDO_E_METADATA);
		ERROR_FAILED_HRESULT(m_pTRiASMDSMap -> SetAt(strNewOKS, strTablename, 
			strClassname, strDescription, vData), GDO_E_METADATA);
		ERROR_FAILED_HRESULT(SetDirty(), E_FAIL);

	} COM_CATCH
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////
// eine Objektklasse hat einen neuen Namen bekommen...

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDOObjectsCollection, RenameObjects
	, IGDOObjects*, pGDOObjects
	, BSTR, bstrOldname
)
{
	COM_TRY {
	WTRiASObjects pTRiASObjects(pGDOObjects);
	CComBSTR strOKS;
	CComBSTR strTablename;
	CComBSTR strClassname;
	CComBSTR strDescription;
	CComVariant	vData;

		RETURN_FAILED_HRESULT(RemapObjects(pTRiASObjects));
		ERROR_FAILED_HRESULT(pTRiASObjects -> get_OKS(CLEARED(strOKS)), GDO_E_OBJECTS);
		ERROR_FAILED_HRESULT(m_pTRiASMDSMap -> GetAt(strOKS, CLEARED(strTablename), 
			CLEARED(strClassname), CLEARED(strDescription), CLEARED(vData)), GDO_E_METADATA);
//		ERROR_FAILED_HRESULT( m_pTRiASMDSMap -> RemoveAt( strOKS ), GDO_E_METADATA );
		ERROR_FAILED_HRESULT(pTRiASObjects -> get_Name(CLEARED(strClassname)), GDO_E_OBJECTS);
		ERROR_FAILED_HRESULT(m_pTRiASMDSMap -> SetAt(strOKS, strTablename, 
			strClassname, strDescription, vData), GDO_E_METADATA);

	// Tabellennamen in GDO und der eigenen MDS-Map *jetzt* noch nicht umbenennen, das 
	// darf erst bei Save() gemacht werden, ansonsten wird der ganze Laden 
	// in sich inkonsistent!!
		ERROR_FAILED_HRESULT(SetDirty(), E_FAIL);

	} COM_CATCH
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////
// eine Objektklasse hat eine neue Beschreibung bekommen...

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOObjectsCollection, RedescribeObjects
		, IGDOObjects*, pGDOObjects
)
{
	COM_TRY {
	WTRiASObjects	pTRiASObjects(pGDOObjects);
	CComBSTR	strOKS;
	CComBSTR	strTablename;
	CComBSTR	strClassname;
	CComBSTR	strDescription;
	CComVariant	vData;

		ERROR_FAILED_HRESULT(pTRiASObjects -> get_OKS(CLEARED(strOKS)), GDO_E_OBJECTS);
		ERROR_FAILED_HRESULT(m_pTRiASMDSMap -> GetAt(strOKS, CLEARED(strTablename), 
			CLEARED(strClassname), CLEARED(strDescription), CLEARED(vData)), GDO_E_METADATA);
//		ERROR_FAILED_HRESULT( m_pTRiASMDSMap -> RemoveAt( strOKS ), GDO_E_METADATA );
		ERROR_FAILED_HRESULT(pTRiASObjects -> get_Description(CLEARED(strDescription)), GDO_E_OBJECTS);
		ERROR_FAILED_HRESULT(m_pTRiASMDSMap -> SetAt(strOKS, strTablename, 
			strClassname, strDescription, vData), GDO_E_METADATA);
		ERROR_FAILED_HRESULT(SetDirty(), E_FAIL);
	
	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOObjectsCollection, get_DefaultType, BSTR*, pbstrType) 
{
	CHECKOUTPOINTER(pbstrType);
	COM_TRY {
		CIID Guid(CLSID_GDOObjects);		// DefaultType der _Elemente_ !
		CComBSTR bstrType(Guid.ProgID().c_str());
		*pbstrType = bstrType.Detach();
	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_4(CGDOObjectsCollection, OnCreate, VARIANT, NameOrHandle, 
	BSTR, Type, OBJECTSCOLLECTIONTYPE, rgType, ITRiASObjects**, ppIObjs)  
{
	CHECKOUTPOINTER(ppIObjs);
	ERROR_EXPR_TRUE(VARIANT_FALSE == m_bWritable, GDO_E_READONLY);
	COM_TRY {
		CIID ClsId(Type, CIID::INITCIID_InitFromProgId);
		if (!ClsId)
			ClsId = CLSID_GDOObjects;		// default ClsId
		RETURN_FAILED_HRESULT(CreateObjectsDef(NameOrHandle, rgType, &ClsId, ppIObjs));
	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDOObjectsCollection, OnDelete, VARIANT, vTRiASObjects) 
{
	ERROR_EXPR_TRUE(VARIANT_FALSE == m_bWritable, GDO_E_READONLY);
	COM_TRY {
		ERROR_EXPR_FALSE(V_ISDISPATCH(&vTRiASObjects), E_FAIL);
		WTRiASObjects	pTRiASObjects;
		CComBSTR		strOKS;
		ERROR_FAILED_HRESULT(V_DISPATCH(&vTRiASObjects) -> QueryInterface(pTRiASObjects.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASObjects -> get_OKS(CLEARED(strOKS)), E_FAIL);
		///////////////////////////////////////////////////////////////////////////
		// nicht aus der Map löschen, das passiert, wenn überhaupt erst beim Speichern
		m_strTablesToDelete.insert(strOKS, true);
	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_0(CGDOObjectsCollection, OnFinalRelease) 
{
	return S_OK;
}

HRESULT CGDOObjectsCollection::CreateObjectsDef(VARIANT vNameOrHandle, DWORD dwType, 
	const CLSID *pClsId, ITRiASObjects **ppIObjects) 
{
	CHECK_INITIALIZED();

CComBSTR	strOKS;
CComBSTR	strTablename;
CComBSTR	strClassname;
CComBSTR	strDescription;
CComVariant	vData;
WTRiASObjects	pTRiASObjects;
	
	ERROR_EXPR_FALSE(V_ISBSTR(&vNameOrHandle), E_UNEXPECTED);
	
	ERROR_FAILED_HRESULT(m_pTRiASMDSKey -> SplitOKS(V_BSTR(&vNameOrHandle), CLEARED(strClassname), CLEARED(strOKS)), E_FAIL);
	if (0 == strClassname.Length())		// kein Kurzbezeichner angegeben, erst mal OKS nehmen
		strClassname = strOKS;
	NormalizeName(strClassname, strTablename);
	
CComBSTR	strFoundOKS;

	ERROR_EXPR_TRUE(S_OK == SearchMDSMap(m_pTRiASMDSMap, strOKS, strFoundOKS, lSearchKey), OBC_E_CLASSEXISTS);
	ERROR_EXPR_TRUE(S_OK == SearchMDSMap(m_pTRiASMDSMap, strTablename, strFoundOKS, lSearchName), OBC_E_CLASSEXISTS);

CComBSTR	strPKeyName;
CComBSTR	strPGeomName;
	
	RETURN_FAILED_HRESULT(CreateTableDef(strTablename, strPKeyName, strPGeomName, gdbAutoIncrField, 16));
	RETURN_FAILED_HRESULT(GetOrCreateObjectsDef(strOKS, strTablename, strClassname, strDescription, gdbSpatial, pTRiASObjects.ppi()));
	ERROR_FAILED_HRESULT(m_pTRiASMDSMap -> SetAt(strOKS, strTablename, strClassname, strDescription, vData), E_FAIL);

	ERROR_FAILED_HRESULT(pTRiASObjects -> put_PrimaryKey(strPKeyName), E_FAIL);
	ERROR_FAILED_HRESULT(pTRiASObjects -> put_DefaultGeometry(strPGeomName), E_FAIL);
	if (ppIObjects)
	{
		*ppIObjects = pTRiASObjects.Detach();
	}
	return S_OK;
}

//////////////////////////////////////////////////////////////////////
// das erste beste Koordinatensystem ermitteln
HRESULT CGDOObjectsCollection::GetPrimaryCS(CComBSTR &strCSGUID) 
{
	CComBSTR	strAliasTable;
	CComBSTR	strCSTable;
	EXT_RETURN_FAILED_HRESULT(m_pGDatabase -> get_GAliasTable(CLEARED(strAliasTable)));
	USES_CONVERSION;
	TCHAR	_buf[_MAX_PATH];

// Block: Recordset schließt automatisch
	{
		wsprintf(_buf, _T("Select TableName From %ls WHERE TableType=\'%s\'"), 
			strAliasTable, gdbCoordSystem);

	CComBSTR	S(_buf);
	AC_GRecordset	rs;
	CComVariant		vCSTable;

		EXT_RETURN_FAILED_HRESULT(m_pGDatabase -> OpenRecordset(S, 
			CComVariant(gdbOpenDynaset), vtMissing, vtMissing, vtMissing, 
			vtMissing, rs.ppi()));
		EXT_RETURN_FAILED_HRESULT(rs -> MoveFirst());
		EXT_RETURN_FAILED_HRESULT(GetFieldValue(rs, L"TableName", vCSTable));
		WIN_ERROR_NOTSUCCESS(vCSTable.ChangeType(VT_BSTR), GDO_E_COERCE);
		strCSTable = V_BSTR(&vCSTable);
	}

// Block: Recordset schließt automatisch
	{
		wsprintf(_buf, _T("SELECT CSGUID FROM %s"), OLE2A(strCSTable));

	CComBSTR	S(_buf);
	AC_GRecordset	rs;
	CComVariant		vCSGUID;

		EXT_RETURN_FAILED_HRESULT(m_pGDatabase -> OpenRecordset(S, 
			CComVariant(gdbOpenDynaset), vtMissing, vtMissing, vtMissing, 
			vtMissing, rs.ppi()));
		EXT_RETURN_FAILED_HRESULT(rs -> MoveFirst());
		EXT_RETURN_FAILED_HRESULT(GetFieldValue(rs, L"CSGUID", vCSGUID));
		WIN_ERROR_NOTSUCCESS(vCSGUID.ChangeType(VT_BSTR), GDO_E_COERCE);
		strCSGUID = V_BSTR(&vCSGUID);
	}
	return S_OK;
}

HRESULT	CGDOObjectsCollection::CreateTableDef(CComBSTR& strTablename, CComBSTR& strPKeyName, CComBSTR& strPGeomName, short sTypeOfPKey /*=gdbText*/, long lSizeOfPKey /*=16*/) 
{
	ERROR_EXPR_FALSE(gdbText == sTypeOfPKey || gdbAutoIncrField == sTypeOfPKey, E_FAIL);

	//////////////////////////////////////////////////////////////////////
	// jetzt Feldnamen für GDO
	strPKeyName = L"UNIQUEIDENT";
	CComBSTR	strIdxName(L"PKey_");
	strIdxName.AppendBSTR(strPKeyName);
	strPGeomName = L"Geometry1";
//	CComBSTR	strTxtGeomname(L"TEXT_");
//	strTxtGeomname.Append(strTablename);
	CComBSTR	strCSGUID;
	RETURN_FAILED_HRESULT(GetPrimaryCS(strCSGUID));
	
	{
	CComBSTR bstr (L"TAB_");

		bstr.AppendBSTR(strTablename);
		strTablename = bstr;
	}

	W_MetadataService	pMetadataService(CLSID_MetadataService);
	IDispatch	*pRawDisp = m_pDGMConnection;
	EXT_ERROR_FAILED_HRESULT(pMetadataService -> putref_Connection(&pRawDisp), NDB_E_NATIVEDB);

	//////////////////////////////////////////////////////////////////////
	// Transaktion in separatem Block; die anderen Blöcke nur, damit die
	// Logik sichtbar ist...
	WGTableDef	pGTableDef;
	{
		DBTransaction	dbTrans(m_pGDatabase);
		{
			//////////////////////////////////////////////////////////////////////
			// Tabellendefinition erstellen
			WGTableDefs	pGTableDefs;
			WGFields	pGFields;
			WGField		pGField;
			EXT_ERROR_FAILED_HRESULT(m_pGDatabase -> get_GTableDefs(pGTableDefs.ppi()), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(m_pGDatabase -> CreateTableDef(CComVariant(strTablename), pGTableDef.ppi()), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(pGTableDef -> get_GFields(pGFields.ppi()), NDB_E_NATIVEDB);
			//////////////////////////////////////////////////////////////////////
			// Primärfeld
			{
				EXT_ERROR_FAILED_HRESULT(pGTableDef -> CreateField(CComVariant(strPKeyName), CComVariant(gdbLong), vtMissing, pGField.ppi()), NDB_E_NATIVEDB);
				if (gdbAutoIncrField == sTypeOfPKey)
				{
					EXT_ERROR_FAILED_HRESULT(pGField -> put_Attributes(gdbAutoIncrField), NDB_E_NATIVEDB);
				} else 
				{
					EXT_ERROR_FAILED_HRESULT(pGField -> put_Type(gdbText), NDB_E_NATIVEDB);
					EXT_ERROR_FAILED_HRESULT(pGField -> put_Size(lSizeOfPKey), NDB_E_NATIVEDB);
				}
				EXT_ERROR_FAILED_HRESULT(pGField -> put_Required(VARIANT_TRUE), NDB_E_NATIVEDB);
				EXT_ERROR_FAILED_HRESULT(pGFields -> Append(pGField), NDB_E_NATIVEDB);
			}
			//////////////////////////////////////////////////////////////////////
			// Primärgeometrie
			{
				EXT_ERROR_FAILED_HRESULT(pGTableDef -> CreateField(CComVariant(strPGeomName), CComVariant(gdbSpatial), vtMissing, pGField.ppi()), NDB_E_NATIVEDB);
				EXT_ERROR_FAILED_HRESULT(pGField -> put_SubType(gdbAnySpatial), NDB_E_NATIVEDB);
				EXT_ERROR_FAILED_HRESULT(pGField -> put_CoordSystemGUID(CComVariant(strCSGUID)), NDB_E_NATIVEDB);
				EXT_ERROR_FAILED_HRESULT(pGField -> put_Required(VARIANT_TRUE), NDB_E_NATIVEDB);
				EXT_ERROR_FAILED_HRESULT(pGFields -> Append(pGField), NDB_E_NATIVEDB);
			}
			//////////////////////////////////////////////////////////////////////
			// Primärindex; Achtung! Es darf als Eigenschaft NUR(!!!) primär gesetzt werden
			{
				WGIndexes	idxDefs;
					WGIndex		idxDef;
				EXT_ERROR_FAILED_HRESULT(pGTableDef -> get_GIndexes(idxDefs.ppi()), NDB_E_NATIVEDB);
				EXT_ERROR_FAILED_HRESULT(pGTableDef -> CreateIndex(CComVariant(strIdxName), idxDef.ppi()), NDB_E_NATIVEDB);
				//////////////////////////////////////////////////////////////////////
				// dazu gehört das Feld...
				{
					WGFields	pGFields;
					 WGField		pGField;
					EXT_ERROR_FAILED_HRESULT(idxDef -> get_GFields(pGFields.ppi()), NDB_E_NATIVEDB);
					EXT_ERROR_FAILED_HRESULT(idxDef -> CreateField(CComVariant(strPKeyName), CComVariant(gdbLong), vtMissing, pGField.ppi()), NDB_E_NATIVEDB);
					EXT_ERROR_FAILED_HRESULT(pGFields -> Append(pGField), NDB_E_NATIVEDB);
				}
				EXT_ERROR_FAILED_HRESULT(idxDef -> put_Primary(VARIANT_TRUE), NDB_E_NATIVEDB);
				EXT_ERROR_FAILED_HRESULT(idxDefs -> Append(idxDef), NDB_E_NATIVEDB);
			}
			EXT_ERROR_FAILED_HRESULT(pGTableDefs -> Append(pGTableDef), NDB_E_NATIVEDB);
		}
		//////////////////////////////////////////////////////////////////////////////////
		// Metadaten nachziehen
		IDispatch		*pDisp = NULL;		// kein QI, kein AddRef() !!
		long		lValid;
		VARIANT_BOOL		sTrue = VARIANT_TRUE;
		{
			W_TableProperty	tblProp(CLSID_TableProperty); 
			pDisp = tblProp;
			EXT_ERROR_FAILED_HRESULT(pMetadataService -> put_TableName(&strTablename), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(tblProp -> put_Name(&strTablename), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(tblProp -> put_PrimaryGeometryFieldName(&strPGeomName), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(pMetadataService -> AddTableMetadata(&pDisp, &lValid), NDB_E_NATIVEDB);
		}
		EXT_ERROR_FAILED_HRESULT(pMetadataService -> put_TableName(&strTablename), NDB_E_NATIVEDB);
		{
			W_FieldProperty	fldProp(CLSID_FieldProperty);
			pDisp = fldProp;
			short		mdFieldType = gdbAutoIncrField == sTypeOfPKey ? gdbLong : gdbText;
			EXT_ERROR_FAILED_HRESULT(fldProp -> put_Name(&strPKeyName), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(fldProp -> put_FieldType(&mdFieldType), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(fldProp -> put_Key(&sTrue), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(fldProp -> put_Displayable(&sTrue), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(pMetadataService -> AddFieldMetadata(&pDisp, &lValid), NDB_E_NATIVEDB);
		}
		{
			W_FieldProperty	fldProp(CLSID_FieldProperty);
			pDisp = fldProp;
			short		fldType = gdbSpatial;
			long		geomType = gdbAnySpatial;
			EXT_ERROR_FAILED_HRESULT(fldProp -> put_Name(&strPGeomName), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(fldProp -> put_FieldType(&fldType), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(fldProp -> put_GeometryType(&geomType), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(fldProp -> put_PrimaryGeometryFlag(&sTrue), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(pMetadataService -> AddFieldMetadata(&pDisp, &lValid), NDB_E_NATIVEDB);
		}

		//////////////////////////////////////////////////////////////////////
		// alles OK, Transaktion bestätigen
		dbTrans.Succeeded();
	}
	return S_OK;
}

HRESULT CGDOObjectsCollection::GetOrCreateObjectsDef(CComBSTR& strOKS, const CComBSTR& strTablename, const CComBSTR& strClassname, const CComBSTR& strDescription, long lGeomType, ITRiASObjects** ppIObjects /*= NULL*/) 
{
	///////////////////////////////////////////////////////////////////////////////////
	// Initialisierungsobjekt basteln
	WDispatch		pApplication;
	WDispatch		pParent = GetUnknown();
	ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTSCOLLECTION -> get_Application(pApplication.ppi()), GDO_E_NOAPPLICATION);
	CInitGDOObjects InitObjs(pApplication, pParent, m_pDGMConnection, m_pGDatabase, m_pDGMCoordSystemsMgr, m_bWritable, OT_GDO2TRiAS(lGeomType), strOKS, strTablename, strClassname, strDescription);

	WTRiASObjects	pTRiASObjects;
	INT_PTR			hObjects = NULL;
	HRESULT			hrCreated;
	ERROR_FAILED_HRESULT(hrCreated = FindInMapOrCreateObject(m_pTRiASObjectHandleMap, hObjects, pTRiASObjects, CLSID_GDOObjects, InitObjs), E_FAIL);

	///////////////////////////////////////////////////////////////////////////////////
	// S_OK ... Objekt wurde neu angelegt...
	if (S_OK == hrCreated)
	{
		ERROR_FAILED_HRESULT(BASE_OF_GDOOBJECTSCOLLECTION -> _Add(pTRiASObjects, VARIANT_FALSE), E_FAIL);
	}
	///////////////////////////////////////////////////////////////////////////////////
	// ==> "0" => OKS war noch nicht bekannt
	// ==> zunächst mit aktuell vergebenem Handle belegen
	if (strOKS == CComBSTR(_T("0")))
	{
		TCHAR	_buf[64];
		wsprintf(_buf, _T("%08lx"), hObjects);
		strOKS = _buf;
	}
	///////////////////////////////////////////////////////////////////////////////////
	// jetzt OKS zuordnen, wir landen dann über WTRiASObjects -> OnChangedOKS wieder 
	// in ReclassObjects, da wird die eigentliche Arbeit erledigt
	ERROR_FAILED_HRESULT(pTRiASObjects -> put_OKS(strOKS), E_FAIL);
	if (ppIObjects)
	{
		*ppIObjects = pTRiASObjects.Detach();
	}
	return S_OK;
}

#if 0
	/////////////////////////////////////////////////////////////////////////////////
	// Teil 2... die Metadaten
{
	DBTransaction	dbTrans(m_pGDatabase);
	EXT_ERROR_FAILED_HRESULT(pMetadataService -> VerifyMetadata(&lValid), NDB_E_NATIVEDB);
	dbTrans.Succeeded();
}
	/////////////////////////////////////////////////////////////////////
	// Teil 3... nach Löschen der Tabellenmetadaten sind auch die 
	// Feldmetadaten futsch ==> selbige neu aufbauen
	EXT_ERROR_FAILED_HRESULT(pMetadataService -> put_TableName(&strNewTablename), NDB_E_NATIVEDB);
	WTRiASFeatures	pTRiASFeatures;
{
	DBTransaction	dbTrans(m_pGDatabase);
	ERROR_FAILED_HRESULT(pTRiASObjects -> get_Features(pTRiASFeatures.ppi()), E_FAIL);
	RETURN_FAILED_HRESULT(RedescribeFieldMetadata(pMetadataService, pTRiASFeatures));
	ERROR_FAILED_HRESULT(pTRiASObjects -> get_GeometryFeatures(pTRiASFeatures.ppi()), E_FAIL);
	RETURN_FAILED_HRESULT(RedescribeFieldMetadata(pMetadataService, pTRiASFeatures));
	dbTrans.Succeeded();
}
#endif
