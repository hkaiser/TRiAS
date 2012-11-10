#include "stdafx.h"
#include "TRiASGDOImpl.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#include "GDODatabase.h"
#include "GDOObject.h"

#include <strstrea.h>

/////////////////////////////////////////////////////////////////////////////
// IGDOAccess 

inline 
HRESULT CGDODatabase::GetObjectNames(IGDOObjects* pGDOObjects, 
	IGDOObject* pGDOObject, CComBSTR& strObjectname, CComBSTR& strPKeyname) 
{
WTRiASObject pTRiASObject;

	ERROR_FAILED_HRESULT(pGDOObject -> QueryInterface(pTRiASObject.ppi()), E_FAIL);
	ERROR_FAILED_HRESULT(pTRiASObject -> get_Name(CLEARED(strObjectname)), GDO_E_OBJECT);

WTRiASObjects pTRiASObjects;
WTRiASFeatures pTRiASFeatures;
WTRiASFeature pTRiASFeature;
WGDOFeature pGDOFeature;

	ERROR_FAILED_HRESULT(pGDOObjects -> QueryInterface(pTRiASObjects.ppi()), E_FAIL);
	ERROR_FAILED_HRESULT(pTRiASObjects -> get_Features(pTRiASFeatures.ppi()), E_FAIL);
	ERROR_FAILED_HRESULT(pTRiASObjects -> get_PrimaryKey(CLEARED(strPKeyname)), GDO_E_OBJECTS);

	ERROR_FAILED_HRESULT(pTRiASFeatures -> Item(CComVariant(strPKeyname), pTRiASFeature.ppi()), E_FAIL);
	ERROR_FAILED_HRESULT(pTRiASFeature -> QueryInterface(pGDOFeature.ppi()), E_FAIL);
	ERROR_FAILED_HRESULT(pGDOFeature -> get_Fieldname(CLEARED(strPKeyname)), E_FAIL);
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, TransformGeometry, IUnknown*, pGeomObject) 
{
	COM_TRY {
	WTRiASTransformGeometry pTRiASTransformGeometry(pGeomObject);

		ERROR_FAILED_HRESULT(pTRiASTransformGeometry -> Transform(m_csGUID, m_pTRiASCSTransform), E_FAIL);
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, TransformGeometryInverse, IUnknown*, pGeomObject) 
{
	COM_TRY {
	WTRiASTransformGeometry pTRiASTransformGeometry(pGeomObject);

		ERROR_FAILED_HRESULT(pTRiASTransformGeometry -> TransformInverse(m_csGUID, m_pTRiASCSTransform), E_FAIL);
	} COM_CATCH;
	return S_OK;
}

HRESULT CGDODatabase::CopyDefaults(WGFields& flds, WTRiASFeatures& feats) 
{
	WEnumVARIANT	Enum;
	CComVariant		v;
	DWORD			nFetched;

	WGField			pTRiASField;
	WGDOFeature		pTRiasFeature;
	WGField			pGDOField;
	CComBSTR		strFldname;
	CComVariant		vFldValue;
	long			fldAttribs;

	RETURN_FAILED_HRESULT(feats -> _NewEnum(Enum.ppu()));
	for (Enum -> Reset(); S_OK == Enum -> Next(1, CLEARED(v), &nFetched);/**/)
	{
		RETURN_FAILED_HRESULT(v.ChangeType(VT_UNKNOWN));
		pTRiASField = pTRiasFeature = V_UNKNOWN(&v);
		RETURN_FAILED_HRESULT(pTRiASField -> get_Attributes(&fldAttribs));
		if (fldAttribs & gdbAutoIncrField)
			continue;
		RETURN_FAILED_HRESULT(pTRiASField -> get_Name(CLEARED(strFldname)));
		RETURN_FAILED_HRESULT(pTRiasFeature -> get_DefaultValue(CLEARED(vFldValue)));
		EXT_RETURN_FAILED_HRESULT(flds -> get_Item(CComVariant(strFldname), pGDOField.ppi()));
		EXT_RETURN_FAILED_HRESULT(pGDOField -> put_Value(vFldValue));
	}
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDODatabase, CreateObject
		, IGDOObjects*, pGDOObjects
		, /*[out, retval]*/ BSTR*, pstrObjectname
)
{
	COM_TRY {
		CHECKINPOINTER(pGDOObjects);
		CHECK_INITIALIZED();

	WTRiASObjects	pTRiASObjects;
	WTRiASFeatures	pTRiASFeatures;
	WTRiASFeatures	pTRiASGeoFeatures;
	WTRiASFeature	pTRiASFeature;
	WTRiASFeature	pTRiASGeoFeature;
	WGDOFeature		pGDOFeature;
	CComBSTR		strTablename;
	CComBSTR		strPKeyname;
	CComBSTR		strGeometryname;
#pragma TODO("Prüfen: pstrObjectname ist ein [out, retval] ??")
	CComBSTR		strObjectname = *pstrObjectname;

		ERROR_FAILED_HRESULT(pGDOObjects -> QueryInterface(pTRiASObjects.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pGDOObjects -> get_Tablename(CLEARED(strTablename)), E_FAIL);

	// der wirkliche Feldname ist über GDOFeature zu holen
		ERROR_FAILED_HRESULT(pTRiASObjects -> get_PrimaryKey(CLEARED(strPKeyname)), GDO_E_OBJECTS);
		ERROR_FAILED_HRESULT(pTRiASObjects -> get_Features(pTRiASFeatures.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASFeatures -> Item(CComVariant(strPKeyname), pTRiASFeature.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASFeature -> QueryInterface(pGDOFeature.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pGDOFeature -> get_Fieldname(CLEARED(strPKeyname)), E_FAIL);

	// der wirkliche Feldname ist über GDOFeature zu holen
		ERROR_FAILED_HRESULT(pTRiASObjects -> get_DefaultGeometry(CLEARED(strGeometryname)), GDO_E_OBJECTS);
		ERROR_FAILED_HRESULT(pTRiASObjects -> get_GeometryFeatures(pTRiASGeoFeatures.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASGeoFeatures -> Item(CComVariant(strGeometryname), pTRiASGeoFeature.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pTRiASGeoFeature -> QueryInterface(pGDOFeature.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(pGDOFeature -> get_Fieldname(CLEARED(strGeometryname)), E_FAIL);

		{
		DBTransaction dbTrans(m_pGDatabase);

		AC_GRecordset rs;
		WOriginatingPipe pO;
		WDGMCSSTransformPipe pT;
		WISpatialFilterPipe pF;

			RETURN_FAILED_HRESULT(GetPipes(pO.ppu(), pT.ppu(), pF.ppu()));

			EXT_RETURN_FAILED_HRESULT(pO -> put_Table(EnBraceStatement(strTablename)));
			EXT_RETURN_FAILED_HRESULT(pO -> put_GeometryFieldName(CComVariant(strGeometryname)));
			ConnectPipes(pO, pT, strGeometryname);
			PrepareTransformation(m_pDGMServerTransService, pO, m_pDGMCoordSystemsMgr, strGeometryname);

			EXT_RETURN_FAILED_HRESULT(pT -> get_OutputRecordset(rs.ppi()));

		VARIANT_BOOL bUpd;

			EXT_ERROR_FAILED_HRESULT(rs -> get_Updatable(&bUpd), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(rs -> AddNew(), NDB_E_NATIVEDB);

		WGFields flds;

			EXT_ERROR_FAILED_HRESULT(rs -> get_GFields(flds.ppi()), NDB_E_NATIVEDB);

			ERROR_FAILED_HRESULT(CopyDefaults(flds, pTRiASFeatures), GDB_E_CANNOTINITRECORDDATA);
			ERROR_FAILED_HRESULT(CopyDefaults(flds, pTRiASGeoFeatures), GDB_E_CANNOTINITRECORDDATA);

		long gmType = 0, gmAttr = 0, gmSize = 0;
		
			GetFieldType(rs, strPKeyname, gmType, gmAttr, gmSize);
			if (gdbAutoIncrField & gmAttr) {
			CComVariant	 vObjName;
			
				EXT_ERROR_FAILED_HRESULT(GetFieldValue(rs, strPKeyname, vObjName), NDB_E_NATIVEDB);
				WIN_ERROR_NOTSUCCESS(vObjName.ChangeType(VT_BSTR), GDO_E_COERCE);
				strObjectname = V_BSTR(&vObjName);
				EXT_ERROR_FAILED_HRESULT(rs -> Update(), NDB_E_NATIVEDB);
			} 
			else if (gdbText == gmType) {
			TCHAR _buf[64];
			CComVariant	vObjName;
			int	nTrial = 5;			// irgendwann ist Schluß mit 'Update'...

				do {
					sprintf(_buf, _T("%08lx"), m_randGen.rand());
					SetFieldValue(rs, strPKeyname, CComVariant(_buf));
					if (SUCCEEDED(TryUpdate(rs)))
						break;
					m_randGen.srand(); 
				} while (--nTrial);
				ERROR_EXPR_TRUE(0 == nTrial, E_FAIL);
				strObjectname = _buf;
			} 
			else {
				MAKE_ERROR(E_FAIL);
			}
			*pstrObjectname = strObjectname.Detach();
			dbTrans.Succeeded();
		} // rs und dbTrans gehen 'out of scope'

	} COM_CATCH
	return S_OK;
}

//////////////////////////////////////////////////////////////////////
//	Operationen für Objekte

IMPLEMENT_DEBUG_FUNCENTRY_5(CGDODatabase, QueryGeometry
		, IGDOObjects*, pGDOObjects
		, IGDOObject*, pGDOObject
		, IGDOFeature*, pGDOFeature
		, /*[in, out]*/ SAFEARRAY**, ppConstraints
		, /*[in, out]*/ VARIANT*, pGeometry
) 
{
	COM_TRY {
		ERROR_EXPR_FALSE(S_OK == IsInitialized(), DBE_E_DATABASE_NOT_OPENED);

	CComBSTR strTablename;
	CComBSTR strObjectname;
	CComBSTR strPKeyname;
	CComBSTR strGeometryname;

		ERROR_FAILED_HRESULT(pGDOObjects -> get_Tablename(CLEARED(strTablename)), E_FAIL);
		ERROR_FAILED_HRESULT(pGDOFeature -> get_Fieldname(CLEARED(strGeometryname)), E_FAIL);

		RETURN_FAILED_HRESULT(GetObjectNames(pGDOObjects, pGDOObject, strObjectname, strPKeyname));

	// Geometrien dieser Klasse geladen?
		if (strTablename != m_strCurrGeomR)
		{
			ERROR_FAILED_HRESULT(LoadGeometrys(pGDOObjects, strTablename, strGeometryname, strPKeyname), 
				GDB_E_CANNOTLOADGEOMETRIES);
			m_strCurrGeomR = strTablename;
		}

	// Geometrie des Objektes holen, Geometrieobjekt bauen...
	MapOfGeometrys::iterator i = m_mapOfGeometrysR.find(strObjectname);
	
		ERROR_EXPR_TRUE(m_mapOfGeometrysR.end() == i, GDB_E_CANNOTLOADGEOMETRY);

	GEOMETRYTYPE geoType;
	WDispatch geoObject;
	HRESULT hr;

		ERROR_FAILED_HRESULT(hr = m_pTRiASCSStorageServiceGDO -> 
			StorageToGeometryGDO((*i).second, &geoType, geoObject.ppi()), 
			GDB_E_CANNOTBUILDOBJECT);
		if (S_FALSE == hr)
		{
			MAKE_ERROR(GDB_E_CANNOTBUILDOBJECT);
		}

	// ...und Geometrie transformieren lassen
	WTRiASTransformGeometry trnsGeo(geoObject);

		ERROR_EXPR_TRUE(!trnsGeo, GDO_E_SERVICE_NOTAVAILABLE);
		ERROR_FAILED_HRESULT(trnsGeo -> Transform(m_csGUID, m_pTRiASCSTransform), 
			GDB_E_CANNOTBUILDOBJECT);

	// Datenbankcontainer mitrechnen
	WTRiASSimpleRectangle Cont;
	W_DGMRectangleGeometry envelope;
	WTRiASCSGeometryProperties geomProp(geoObject);

		geomProp -> get_Envelope(Cont.ppi());
		envelope = Cont;

		if (m_bInitContainer) {
		double x0, y0;
		W_DGMPoint pt;

			envelope -> get_Origin(pt.ppi());
			pt -> get_X(&x0);
			pt -> get_Y(&y0);
			_ASSERTE(0 != x0 && 0 != y0);

			m_rcContainer.put_XMin(x0);
			m_rcContainer.put_YMin(y0);
			m_rcContainer.put_XMax(x0);
			m_rcContainer.put_YMax(y0);
			m_bInitContainer = false;
		}
		m_rcContainer = m_rcContainer + CCSRectangleGeometry(envelope);

	CComVariant	v(geoObject);
	MC::ArrayVariant sa;

		sa.Attach(*ppConstraints);

	// Window überprüfen
/*		if (sa.Elements() > EVALEXPARAM_Window) {
		// zweiter optionaler Parameter enthält evtl. Suchfenster
		double		window[4];
		W_DGMPoint	Point;
		W_DGMRectangleGeometry	rectWindow;

			rectWindow = V_DISPATCH(&sa[EVALEXPARAM_Window]);
			RETURN_FAILED_HRESULT(rectWindow -> get_Origin(Point.ppi()));
			RETURN_FAILED_HRESULT(Point -> get_X(&window[0]));
			RETURN_FAILED_HRESULT(Point -> get_Y(&window[1]));
			RETURN_FAILED_HRESULT(rectWindow -> get_Width(&window[2]));
			RETURN_FAILED_HRESULT(rectWindow -> get_Height(&window[3]));
			window[2] += window[0];
			window[3] += window[1];
		}
*/
		if (sa.Elements() > EVALEXPARAM_CoordSysGuid) {
		// GUID des Koordinatensystems soll geliefert werden
		CComVariant	vCSGUID;

			sa[EVALEXPARAM_CoordSysGuid] = vCSGUID;
		}
		if (sa.Elements() > EVALEXPARAM_Envelope) {
		// Container soll geliefert werden
			RETURN_FAILED_HRESULT(CComVariant(envelope).Detach(&sa[EVALEXPARAM_Envelope]));
		}
		RETURN_FAILED_HRESULT(v.Detach(pGeometry));

	} COM_CATCH
	return S_OK;
}

HRESULT CGDODatabase::LoadGeometrys(IGDOObjects *pIGDOObjects, 
	const CComBSTR& strClassname, const CComBSTR& strGeometryname, const CComBSTR& strPKeyname) 
{
	m_mapOfGeometrysR.erase(m_mapOfGeometrysR.begin(), m_mapOfGeometrysR.end());
	{
		TIMER_START(0, L"CGDODatabase::LoadGeometrys")
	
	AC_GRecordset rs;
	CComVariant vCSGuid;

		GetRecordset(strClassname, vtMissing, strGeometryname, NULL, 
			CLEARED(vCSGuid), rs.ppu());

//		WOriginatingPipe		pO;
//		WDGMCSSTransformPipe	pT;
//		WISpatialFilterPipe		pF;
//		RETURN_FAILED_HRESULT( GetPipes(pO.ppu(),pT.ppu(),pF.ppu()) );
//
//		EXT_ERROR_FAILED_HRESULT( pO -> put_Table( EnBraceStatement(strClassname) ), E_FAIL );
//		EXT_ERROR_FAILED_HRESULT( pO -> put_GeometryFieldName( CComVariant( strGeometryname ) ), E_FAIL );
//		ConnectPipes( pO, pT, strGeometryname );
//		PrepareTransformation( m_pDGMServerTransService, pO, m_pDGMCoordSystemsMgr, strGeometryname );
//
//		EXT_ERROR_FAILED_HRESULT( pT -> get_OutputRecordset( rs.ppi() ), NDB_E_NATIVEDB );

	// CoordSysGuid an der entsprechenden Objektklasse setzen
	CComBSTR bstrGuid (GetPropertyFrom (pIGDOObjects, g_cbCSSGuid, g_bstrNil));

		if (bstrGuid == g_bstrNil) 
			SetPropertyBy(pIGDOObjects, g_cbCSSGuid, vCSGuid, true);
#if defined(_DEBUG)
		else {
		CComVariant vCSGuidDbg (vCSGuid);

			vCSGuidDbg.ChangeType(VT_BSTR, &vCSGuid);
			_ASSERTE(bstrGuid == V_BSTR(&vCSGuidDbg));
		}
#endif // defined(_DEBUG)

	// Geometrien lesen und zwischenspeichern
	long nObjects = 0;
	VARIANT_BOOL bEOF;
	CComVariant	vGeometry, vName;

		TIMER_CHECKPOINT(0, nObjects)
		EXT_RETURN_FAILED_HRESULT(rs -> MoveFirst());

	// Felder vorher besorgen (#HK000211)
	WGFields flds;
	WGField fldGeometry, fldPKeyName;

		EXT_RETURN_FAILED_HRESULT(rs -> get_GFields (flds.ppi()));
		EXT_RETURN_FAILED_HRESULT(flds -> get_Item (CComVariant(strGeometryname), fldGeometry.ppi()));
		EXT_RETURN_FAILED_HRESULT(flds -> get_Item (CComVariant(strPKeyname), fldPKeyName.ppi()));

		while (S_OK == rs -> get_EOF(&bEOF) && !bEOF) {
			++nObjects;
			EXT_RETURN_FAILED_HRESULT(fldGeometry -> get_Value (CLEARED(vGeometry)));

		// GDO kennt Objekte ohne Geometrie! Diese werden hier der Einfachheit 
		// übergangen (sollten aber auch nicht mehr geliefert werden, da überall
		// ... and Geometrie Is Not Null als Bedingung hinzugefügt ist #HK021024)
			if (V_VT(&vGeometry) == (VT_ARRAY | VT_UI1)) {
				EXT_RETURN_FAILED_HRESULT(fldPKeyName -> get_Value (CLEARED(vName)));
				WIN_ERROR_NOTSUCCESS(vName.ChangeType(VT_BSTR), GDO_E_COERCE);
				m_mapOfGeometrysR.insert(V_BSTR(&vName), vGeometry);
			}
			rs -> MoveNext();
		}
		TIMER_CHECKPOINT(0, nObjects)
	}	// rs geht 'out of scope'
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_4(CGDODatabase, UpdateGeometry
	, IGDOObjects*, pGDOObjects
	, IGDOObject*, pGDOObject
	, IGDOFeature*, pGDOFeature
	, VARIANT, newValue
)
{
	CHECKINPOINTER(pGDOObject);
	CHECKINPOINTER(pGDOFeature);
	ERROR_EXPR_FALSE(V_ISDISPATCH(&newValue), E_FAIL);
	CHECK_INITIALIZED();

	COM_TRY {
		m_strCurrGeomR = L"";		// Cache auf alle Fälle 'leeren'

	CComBSTR strTablename;
	CComBSTR strObjectname;
	CComBSTR strPKeyname;
	CComBSTR strGeometryname;

		ERROR_FAILED_HRESULT(pGDOObjects -> get_Tablename(CLEARED(strTablename)), E_FAIL);
		ERROR_FAILED_HRESULT(pGDOFeature -> get_Fieldname(CLEARED(strGeometryname)), E_FAIL);
		RETURN_FAILED_HRESULT(GetObjectNames(pGDOObjects, pGDOObject, strObjectname, strPKeyname));

	WDispatch geoObjectOrig(V_DISPATCH(&newValue));
	WDispatch geoObject;
	
		ERROR_FAILED_HRESULT(WTRiASCloneGeometry(geoObjectOrig) -> Clone(geoObject.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(WTRiASTransformGeometry(geoObject) -> 
			TransformInverse(m_csGUID, m_pTRiASCSTransform), GDB_E_CANNOTBUILDOBJECT);

	WTRiASCSGeometryProperties geoProps;
	GEOMETRYTYPE typeOfGeom;
	
		ERROR_FAILED_HRESULT(geoObject -> QueryInterface(geoProps.ppi()), E_FAIL);
		ERROR_FAILED_HRESULT(geoProps -> get_Type(&typeOfGeom), E_FAIL);

	CComVariant vGeomBlob;
	
		ERROR_FAILED_HRESULT(m_pTRiASCSStorageServiceGDO -> 
			GeometryToStorageGDO(typeOfGeom, geoObject, CLEARED(vGeomBlob)), 
			GDB_E_CANNOTBUILDOBJECT);

		{
		AC_GRecordset rs;
		WOriginatingPipe pO;
		WDGMCSSTransformPipe pT;
		WISpatialFilterPipe pISpatialFilterPipe;

			RETURN_FAILED_HRESULT(GetPipes(pO.ppu(), pT.ppu(), pISpatialFilterPipe.ppu()));

		CComBSTR strFilter;
		
			RETURN_FAILED_HRESULT(GetFilter(pGDOObject, strFilter));
			EXT_ERROR_FAILED_HRESULT(pO -> put_Table(EnBraceStatement(strTablename)), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(pO -> put_GeometryFieldName(CComVariant(strGeometryname)), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(pO -> put_Filter(strFilter), NDB_E_NATIVEDB);
			
		WGRecordset	rs0;

			EXT_ERROR_FAILED_HRESULT(pO -> get_OutputRecordset(rs0.ppi()), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(pT -> putref_InputRecordset(rs0), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(pT -> put_InputGeometryFieldName(strGeometryname), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(pT -> get_OutputRecordset(rs.ppi()), NDB_E_NATIVEDB);

		// BEGIN??
			EXT_ERROR_FAILED_HRESULT(rs -> MoveFirst(), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(rs -> MoveLast(), NDB_E_NATIVEDB);
		
		long lCount = 0;
			
			EXT_ERROR_FAILED_HRESULT(rs -> get_RecordCount(&lCount), NDB_E_NATIVEDB);
			ERROR_EXPR_FALSE(1 == lCount, E_FAIL);
		// END??

			EXT_ERROR_FAILED_HRESULT(rs -> Edit(), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(SetFieldValue(rs, strGeometryname, vGeomBlob), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(rs -> Update(), NDB_E_NATIVEDB);
		}

	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDODatabase, GetDefaultGeometry
			, long, geometryType
			, /*[out, retval]*/ VARIANT*, vDefaultGeometry
)
{
	CHECKINPOINTER(vDefaultGeometry);
	MapGeoTypeToDefault::iterator i = m_mapGeoTypeToDefault.find(geometryType);
	ERROR_EXPR_TRUE(m_mapGeoTypeToDefault.end() == i, E_FAIL);
	CComVariant	v((*i).second);
	v.Detach(vDefaultGeometry);
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_6(CGDODatabase, GetRecordset
		, BSTR, strTablename
		, VARIANT, vGeometryFilter
		, BSTR, bstrGeometryField
		, /*[in, optional, defaultvalue(NULL)]*/ BSTR, bstrFilter
		, VARIANT *, pvCSGuid, 
		, /*[out, retval]*/ IUnknown**, ppIRecordset
)
{
	COM_TRY {
	WGRecordset pGRecordset;
	WOriginatingPipe pOriginatingPipe;
	CComBSTR strGeometryField(bstrGeometryField);
		
	CComBSTR strFilter(bstrFilter);
	
		EXT_ERROR_FAILED_HRESULT(m_pDBConnection -> 
			CreateOriginatingPipe(pOriginatingPipe.ppi()), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(pOriginatingPipe -> 
			put_Table(EnBraceStatement(strTablename)), NDB_E_NATIVEDB);
//		EXT_ERROR_FAILED_HRESULT(pOriginatingPipe -> 
//			put_GeometryFieldName(CComVariant(strGeometryField)), NDB_E_NATIVEDB);
		if (strFilter && 0 != strFilter.Length())
		{
			EXT_ERROR_FAILED_HRESULT(pOriginatingPipe -> put_Filter(strFilter), NDB_E_NATIVEDB);
		}
		EXT_ERROR_FAILED_HRESULT(pOriginatingPipe -> 
			get_OutputRecordset(pGRecordset.ppi()), NDB_E_NATIVEDB);
		
	WDGMCSSTransformPipe pDGMCSSTransformPipe;
	
		EXT_ERROR_FAILED_HRESULT(pDGMCSSTransformPipe.CreateInstance(CLSID_CSSTransformPipe), E_FAIL);

		EXT_ERROR_FAILED_HRESULT(pDGMCSSTransformPipe -> 
			putref_InputRecordset(pGRecordset), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(pDGMCSSTransformPipe -> 
			put_InputGeometryFieldName(strGeometryField), NDB_E_NATIVEDB);
		EXT_ERROR_FAILED_HRESULT(pDGMCSSTransformPipe -> 
			putref_CoordSystemsMgr(m_pDGMCoordSystemsMgr), NDB_E_NATIVEDB);

	// Transformation vorbereiten
	WGField	pGField;
	CComVariant	vCSGUID;

		GetField(pGRecordset, strGeometryField, pGField);
		pGField -> get_CoordSystemGUID(CLEARED(vCSGUID));

	WAltCoordSystemPath	pAltCoordSystemPath;
		
		m_pDGMServerTransService -> CreateSimpleTransFromCSMtoServer(
			m_pDGMCoordSystemsMgr, vCSGUID, m_pGDatabase, pAltCoordSystemPath.ppi());

	// jetzt (!) erst den Recordset holen
		EXT_ERROR_FAILED_HRESULT(pDGMCSSTransformPipe -> get_OutputRecordset(pGRecordset.ppi()), E_FAIL);
		*ppIRecordset = pGRecordset.Detach();

		if (NULL != pvCSGuid) 
			vCSGUID.Detach(pvCSGuid);

		pOriginatingPipe.Assign(NULL);			// in dieser Reihenfolge ???
		pDGMCSSTransformPipe.Assign(NULL);

	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_3(CGDODatabase, GetPipes
			, /*[out]*/ IUnknown**, ppIOriginatingPipe
			, /*[out]*/ IUnknown**, ppICSSTransformPipe
			, /*[out]*/ IUnknown**, ppISpatialFilterPipe
)
{
	CHECKOUTPOINTER(ppIOriginatingPipe);	// die muß mindestens angefordert werden...
	COM_TRY {
	WOriginatingPipe pOriginatingPipe;

		EXT_ERROR_FAILED_HRESULT(m_pDBConnection -> 
			CreateOriginatingPipe(pOriginatingPipe.ppi()), NDB_E_NATIVEDB);
		*ppIOriginatingPipe = pOriginatingPipe.detach();

		if (NULL != ppICSSTransformPipe) {
		WDGMCSSTransformPipe pDGMCSSTransformPipe(CLSID_CSSTransformPipe);

			EXT_ERROR_FAILED_HRESULT(pDGMCSSTransformPipe -> 
				putref_CoordSystemsMgr(m_pDGMCoordSystemsMgr), NDB_E_NATIVEDB);
			*ppICSSTransformPipe = pDGMCSSTransformPipe.detach();
		}

		if (NULL != ppISpatialFilterPipe) {
		WISpatialFilterPipe pISpatialFilterPipe(CLSID_SpatialFilterPipe);

			*ppISpatialFilterPipe = pISpatialFilterPipe.detach();
		}

	} COM_CATCH
	return S_OK;
}
