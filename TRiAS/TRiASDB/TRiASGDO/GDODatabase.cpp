// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.02.2000 20:44:56
//
// @doc
// @module GDODatabase.cpp | Implementation of the <c CGDODatabase> class

#include "stdafx.h"
#include "TRiASGDOImpl.h"

#include <Atl/Ciid.h>

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#include "GDODatabase.h"

#include "CSPointGeom.h"
#include "CSLineGeom.h"

#include <stdlib.h>			// splitpath / makepath

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASSimpleRectangle);
DefineSmartInterface(CreateDatabase);
DefineSmartInterface2(ExtendedPropertySet, IID_ExtendedPropertySet);

inline HRESULT NormalizeDir(CComBSTR& strDir) 
{
	USES_CONVERSION;

TCHAR drv[_MAX_PATH];
TCHAR dir[_MAX_PATH];
TCHAR path[_MAX_PATH];

	_splitpath(OLE2A(strDir), drv, dir, NULL, NULL);
	_makepath(path, drv, dir, NULL, NULL);

CComBSTR strPath(path);	// definitiv ein Backslash am Ende (von makepath)

	if (strPath.Length() < 1)	// 's sollte schon was da sein ;-)
		return E_FAIL;

	strDir = CComBSTR(strPath.Length() - 1, strPath);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CGDODatabase
// GDODatabase.cpp : Implementation of CGDODatabase

DefineSmartInterface2(GDatabase, IID_GDatabase)				// WGDatabase
DefineSmartInterface2(DGMConnection, IID_DGMConnection)		// WDGMConnection

///////////////////////////////////////////////////////////////////////////
// CGDODatabase

CGDODatabase::~CGDODatabase() 
{
}

typedef struct _G {
	union {
		GUID	g;
		CSID	c;
	};
	explicit _G(const GUID &_g) { g = _g; }
	explicit _G(const CSID &_c) { c = _c; }
} _G;


IMPLEMENT_DEBUG_FUNCENTRY_0(CGDODatabase, FinalConstruct) 
{
	COM_TRY 
	{
	/////////////////////////////////////////////////////////////////////
	// alle Services basteln die wir so brauchen...
	// (1) Geomedia
		m_pDGMServerTransService	= WDGMServerTransService(CLSID_ServerTransService);
		m_stgGMService				= WDGMGeometryStorageService(CLSID_GeometryStorageService);
		m_pDGMCoordSystemsMgr		= WDGMCoordSystemsMgr(CLSID_CoordSystemsMgr);

	/////////////////////////////////////////////////////////////////////
	// (2) TRiAS
		m_pTRiASCSStorageServiceGDO		= WTRiASCSStorageServiceGDO(CLSID_TRiASCSStorageService);
		m_pTRiASCSTransform		= WTRiASCSTransform(CLSID_TRiASCSTransform);
		m_csIn					= WTRiASCS(CLSID_TRIASCS);

	/////////////////////////////////////////////////////////////////////
	// Koordinatensystem für Geomedia als geographisch/WGS84 festlegen
	WIGMCoordSystem		gmcsOut = m_pDGMCoordSystemsMgr -> GetCoordSystem();
	WRefSpaceMgr		gmrsOut = gmcsOut -> GetRefSpaceMgr();
	WGeogSpace			gmgsOut = gmrsOut -> GetGeogSpace();
	WUnitFormatSpec		pUnitFormatSpec = gmrsOut -> GetUnitFormatSpec();
	WDGMUnitsOfMeasure	pDGMUnitsOfMeasure(CLSID_UnitsOfMeasure);

		gmcsOut -> put_BaseStorageType(csbsGeographic);
		gmgsOut -> PutGeodeticDatumVal(csgdWGS84);

	CComBSTR strUnit = pUnitFormatSpec -> GetAngUnit();
	UnitConstants lUnitID = (UnitConstants) pDGMUnitsOfMeasure -> GetUnitID(igUnitAngle, strUnit);

	/////////////////////////////////////////////////////////////////////
	// Eingangskoordinatensystem wie Geomedia-Output
	// Koordinatensystem ist als WGS84/CylEqui initialisiert, deshalb nur
	// noch als geographisch setzen; Winkeleinheit wird aus Geomedia-CS übernommen
		RETURN_FAILED_HRESULT(m_csIn -> put_CoordSystemType(tcsCS_Geographic));
	
	TRIASCSUNITOFANGLE angleUnit(tcsUOA_Undefined);
	WTRiASCSGCS	pTRiASCSGCS;

		switch (lUnitID) {
		case igAngleRadian : 
			angleUnit = tcsUOA_Radian; 
			break;

		case igAngleDegree : 
			angleUnit = tcsUOA_Degree; 
			break;

		default: 
			MAKE_ERROR(E_FAIL);
			break;
		}
		RETURN_FAILED_HRESULT(m_csIn -> get_GeographicCS(pTRiASCSGCS.ppi()));
		pTRiASCSGCS -> put_UnitOfAngle(angleUnit);

	/////////////////////////////////////////////////////////////////////
	// GUID des Koordinatensystems merken
	CComBSTR strGUID;
	GUID csGUID;

		RETURN_FAILED_HRESULT(m_csIn -> get_GUID(CLEARED(strGUID)));
		RETURN_FAILED_HRESULT(::CLSIDFromString(strGUID, &csGUID));
		m_csGUID = _G(csGUID).c;

	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_0(CGDODatabase, FinalRelease) 
{
	RETURN_FAILED_HRESULT(DoCloseDatabase());
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_Parent,/*[out, retval]*/ IDispatch**, ppIDispatch) 
{
	CHECKOUTPOINTER(ppIDispatch);
	COM_TRY {
		*ppIDispatch = m_pParent;
		if (*ppIDispatch)
			(*ppIDispatch) -> AddRef();
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, put_Parent,/*[in]*/ IDispatch*, newVal) 
{
	COM_TRY 
	{
		m_pParent = newVal;
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_Application,/*[out, retval]*/ IDispatch**, ppIDispatch) 
{
	CHECKOUTPOINTER(ppIDispatch);
	COM_TRY {
		*ppIDispatch = m_pApplication;
		if (*ppIDispatch)
			(*ppIDispatch) -> AddRef();
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, put_Application,/*[in]*/ IDispatch*, newVal) 
{
	COM_TRY 
	{
		m_pApplication = newVal;
//		_ASSERTE( m_pApplication );
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_TemporaryName,/*[out, retval]*/ BSTR*, pVal) 
{
	FUNC_NOT_IMPL();
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_Temporary,/*[out, retval]*/ VARIANT_BOOL*, pVal) 
{
	FUNC_NOT_IMPL();
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, put_Temporary,/*[in]*/ VARIANT_BOOL, newVal) 
{
	FUNC_NOT_IMPL();
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_IsDirty,/*[out, retval]*/ VARIANT_BOOL*, pVal) 
{
	CHECKINPOINTER(pVal);
	*pVal = m_bDirty ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, put_IsDirty,/*[in]*/ VARIANT_BOOL, newVal) 
{
	m_bDirty = VARIANT_FALSE == newVal ? false : true;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_Handle,/*[out, retval]*/ INT_PTR *, pVal) 
{
	CHECKINPOINTER(pVal);
	*pVal = reinterpret_cast < long>(this);
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_VersionLong,/*[out, retval]*/ LONG*, pVal) 
{
	CHECKINPOINTER(pVal);
	COM_TRY 
	{
		_ASSERTE(!!m_pGDatabase);
		CComBSTR	s;
		EXT_ERROR_FAILED_HRESULT(m_pGDatabase -> get_Version(&s), NDB_E_NATIVEDB);
		*pVal = 0x06000000;
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_Version, BSTR*, Version) 
{
	CHECKINPOINTER(Version);
	COM_TRY 
	{
		_ASSERTE(!!m_pGDatabase);
		EXT_ERROR_FAILED_HRESULT(m_pGDatabase -> get_Version(Version), NDB_E_NATIVEDB);
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_SchemaUpdatable,/*[out, retval]*/ VARIANT_BOOL*, pVal) 
{
	CHECKINPOINTER(pVal);
	COM_TRY 
	{
		_ASSERTE(!!m_pGDatabase);
		EXT_ERROR_FAILED_HRESULT(m_pGDatabase -> get_SchemaUpdatable(pVal), NDB_E_NATIVEDB);
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_Name,/*[out, retval]*/ BSTR*, pVal) 
{
	CHECKINPOINTER(pVal);
	COM_TRY 
	{
		_ASSERTE(!!m_pGDatabase);
		EXT_ERROR_FAILED_HRESULT(m_pGDatabase -> get_Name(pVal), NDB_E_NATIVEDB);
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Erzeugen der GDO-Connection
namespace {
	DATABASESTORAGEMODE RetrieveStorageMode (ITRiASDataServerRegEntry *pIEntry)
	{
	DATABASESTORAGEMODE rgStgMode = DATABASESTORAGEMODE_Unknown;

		COM_TRY {
		CComBool fIsDirectory, fIsFile, fIsStorage, fMultiFile;

			THROW_FAILED_HRESULT(pIEntry -> get_NameIsDirectory(&fIsDirectory));
			THROW_FAILED_HRESULT(pIEntry -> get_NameIsFile(&fIsFile));
			THROW_FAILED_HRESULT(pIEntry -> get_NameIsSubStorage(&fIsStorage));
			THROW_FAILED_HRESULT(pIEntry -> get_MultipleFiles(&fMultiFile));

			if (fIsFile)
				rgStgMode = DATABASESTORAGEMODE_FileBased;
			else if (fMultiFile)
				rgStgMode = DATABASESTORAGEMODE_MultiFileBased;
			else if (fIsStorage)
				rgStgMode = DATABASESTORAGEMODE_StorageBased;
			else if (fIsDirectory)
				rgStgMode = DATABASESTORAGEMODE_DirectoryBased;
			else
				rgStgMode = DATABASESTORAGEMODE_ConnectStringBased;

		} COM_CATCH_IGNORE;
		return rgStgMode;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Connectstring für Datenbanken umbauen, übernimmt alles außer 'ProgID'
namespace {
	HRESULT RebuildConnInfo (IParseStringPairs *pIPairs)
	{
		_ASSERTE(NULL != pIPairs);

	WParseStringPairs2 Pairs2;

		RETURN_FAILED_HRESULT(pIPairs -> QueryInterface(Pairs2.ppi()));

	// Fehler einfach ignorieren
		Pairs2 -> DeletePair(CComBSTR(L"PROGID"));
		Pairs2 -> DeletePair(CComBSTR(L"CustomConnInfo"));
		return S_OK;
	}
}

HRESULT	CGDODatabase::DoCreateConnection(const BSTR &bstrLocation, const BSTR &connName,
	const BSTR &Source, const VARIANT_BOOL fExclusive, const VARIANT_BOOL fReadOnly,
	const VARIANT_BOOL fModTrack)
{
WDGMConnection pDBConnection;
W_MetadataService pMetadataService;

	COM_TRY {
	WParseStringPairs Parse(CLSID_ParseStringPairs);
	long lPairs = 0;
	CComBSTR strType;

		RETURN_FAILED_HRESULT(Parse -> put_Pattern(CComBSTR(g_cbCollatePattern)));
		RETURN_FAILED_HRESULT(Parse -> Parse(Source, &lPairs));
		if (0 < lPairs && S_OK == Parse -> get_Value(CComBSTR(_T("PROGID")), CLEARED(strType))) {
		// ist der Server R/W?
		WTRiASDataServerRegEntries servers (CLSID_TRiASDataServerRegEntries);
		WTRiASDataServerRegEntry server;

			ERROR_FAILED_HRESULT(servers -> FindFromServerProgID(strType, server.ppi()), 
				DBE_E_FAILED_TOACCESSDATASERVER);

		VARIANT_BOOL bIsDirectory;
		CComBSTR strLocation(bstrLocation);

			EXT_ERROR_FAILED_HRESULT(server -> get_IsReadWrite(&m_bWritable), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(server -> get_NameIsDirectory(&bIsDirectory), NDB_E_NATIVEDB);
			if (bIsDirectory)
			{
				RETURN_FAILED_HRESULT(NormalizeDir(strLocation));
			}

		// jetzt alles in die Connection reinstopfen
			pDBConnection = WDGMConnection(CLSID_Connection);
			EXT_ERROR_FAILED_HRESULT(pDBConnection -> put_Type(strType), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(pDBConnection -> put_Location(strLocation), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(pDBConnection -> put_ConnectionName(connName), NDB_E_NATIVEDB);

		CComBSTR bstrHasConnInfo;

			if (S_OK == Parse -> get_Value(CComBSTR(_T("CustomConnInfo")), CLEARED(bstrHasConnInfo)) &&
				!wcscmp(bstrHasConnInfo, L"1"))
			{
			// ggf. neue Connectinfo bauen
				RETURN_FAILED_HRESULT(RebuildConnInfo(Parse));

			WComposeStringPairs ConnInfoPairs(Parse);
			CComBSTR bstrConnInfo;

				RETURN_FAILED_HRESULT(ConnInfoPairs->get_ComposedData(
					CComBSTR(g_cbCollatePattern), CLEARED(bstrConnInfo)));
				EXT_ERROR_FAILED_HRESULT(pDBConnection -> 
					put_ConnectInfo(bstrConnInfo), NDB_E_NATIVEDB);
			}

			_ASSERTE(m_bWritable || fReadOnly);
			EXT_ERROR_FAILED_HRESULT(pDBConnection -> put_Mode(!fReadOnly ? 
				gmcModeReadWrite : gmcModeReadOnly), NDB_E_NATIVEDB);

			if (FAILED(pDBConnection -> Connect())) {
				pDBConnection -> Disconnect();
				return TRIASDB_E_SINGLEDATABASE_NOT_FOUND;
			}

		// alle Änderungen dieser Session an alle anderen weiterleiten
			EXT_ERROR_FAILED_HRESULT(pDBConnection -> BroadcastDatabaseChanges(
				CComVariant(VARIANT_TRUE)), NDB_E_NATIVEDB);

		// Metadatenservice
			pMetadataService = W_MetadataService(CLSID_MetadataService);

		IDispatch *pRawDisp = pDBConnection;
		
			EXT_ERROR_FAILED_HRESULT(pMetadataService -> putref_Connection(&pRawDisp), 
				NDB_E_NATIVEDB);
		
		WDispatch pDisp;
		
			EXT_ERROR_FAILED_HRESULT(pDBConnection -> get_Database(pDisp.ppi()), NDB_E_NATIVEDB);
		
		CComBSTR strMetadataTable;
		HRESULT hr = pMetadataService -> get_MetadataTableName(CLEARED(strMetadataTable));

			if (0 == strMetadataTable.Length())	{
			long lValid;
				
				EXT_ERROR_FAILED_HRESULT(pMetadataService -> VerifyMetadata(&lValid), NDB_E_NATIVEDB);
			}
			hr = pMetadataService -> get_MetadataTableName(CLEARED(strMetadataTable));
			ERROR_EXPR_TRUE(0 == strMetadataTable.Length(), E_FAIL);

		// alles gelungen, eigene Zeiger initialisieren
			m_pDBConnection = pDBConnection;
			m_pGDatabase = pDisp;

		// ModTrack an Datenbank setzen, SessionID abfragen
		WDispatch EPS;
		CComBool fDisableTrack (!fModTrack);
		long lStatus = 0;

			EXT_ERROR_FAILED_HRESULT(m_pGDatabase -> GetExtension(
				CComBSTR(L"ExtendedPropertySet"), EPS.ppi()), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(WExtendedPropertySet(EPS) -> 
				SetValue(CComBSTR(L"DisableModificationLogging"), 
				fDisableTrack, &lStatus), NDB_E_NATIVEDB);

			if (fModTrack) {
			// SessionId abfragen
			CComVariant vSessionId;

				EXT_ERROR_FAILED_HRESULT(WExtendedPropertySet(EPS) -> 
					GetValue(CComBSTR(L"SessionID"), CLEARED(vSessionId)), 
					NDB_E_NATIVEDB);
				WIN_ERROR_NOTSUCCESS(vSessionId.ChangeType(VT_I4), GDO_E_COERCE);
				m_lSessionId = V_I4(&vSessionId);

			// letzten irrelevanten ModLogEintrag abfragen
			CComBSTR bstrModLogName;

			// Block: Recordset schließt automatisch
				{
				TCHAR cbBuffer[_MAX_PATH];
				CComBSTR strAliasTable;

					EXT_RETURN_FAILED_HRESULT(m_pGDatabase -> get_GAliasTable(CLEARED(strAliasTable)));
					wsprintf(cbBuffer, _T("Select TableName From %ls Where TableType=\'%s\'"), 
						strAliasTable, gdbModifications);

				CComBSTR bstrSQL(cbBuffer);
				AC_GRecordset rs;
				CComVariant	vModLogTable;

					EXT_RETURN_FAILED_HRESULT(m_pGDatabase -> OpenRecordset(bstrSQL, 
						CComVariant(gdbOpenSnapshot), CComVariant(gdbReadOnly|gdbForwardOnly),
						vtMissing, vtMissing, vtMissing, rs.ppi()));
					if (SUCCEEDED(rs -> MoveFirst())) {
						EXT_RETURN_FAILED_HRESULT(GetFieldValue(rs, L"TableName", vModLogTable));
						WIN_ERROR_NOTSUCCESS(vModLogTable.ChangeType(VT_BSTR), GDO_E_COERCE);
						bstrModLogName = V_BSTR(&vModLogTable);
					}
				}

			// Block: Recordset schließt automatisch
				if (bstrModLogName.Length() > 0) {
				CComBSTR bstrSQL (L"Select MAX(ModificationNumber) As MaxNum From ");

					bstrSQL.AppendBSTR(bstrModLogName);

				AC_GRecordset rs;
				CComVariant	vMaxNum;

					if (SUCCEEDED(m_pGDatabase->OpenRecordset(bstrSQL, 
						CComVariant(gdbOpenSnapshot), CComVariant(gdbReadOnly|gdbForwardOnly), 
						vtMissing, vtMissing, vtMissing, rs.ppi()))) 
					{
						m_lMaxModEntry = 0;			// kein Eintrag vorhanden
						if (SUCCEEDED(rs -> MoveFirst())) 
						{
							EXT_RETURN_FAILED_HRESULT(GetFieldValue(rs, L"MaxNum", vMaxNum));
							if (SUCCEEDED(vMaxNum.ChangeType(VT_I4)))
								m_lMaxModEntry = V_I4(&vMaxNum);
						}
					}
				}
			}

		// Sicherstellen, daß entweder beides gegeben ist oder eben auch nicht
			if (-1 == m_lMaxModEntry)
				m_lSessionId = 0;

		// 
		long lSQLConformance;
			
			EXT_ERROR_FAILED_HRESULT(m_pGDatabase -> get_SQLConformance(&lSQLConformance), NDB_E_NATIVEDB);

		// DATABASESTORAGEMODE speichern
			m_rgStgMode = RetrieveStorageMode (server);
		}
	} COM_CATCH_OP(
		pMetadataService.Assign(NULL);
		if (pDBConnection.IsValid())
			pDBConnection -> Disconnect();
	);
	return S_OK;
}

HRESULT CGDODatabase::DoCloseDatabase() 
{
	m_pDBConnection.Assign(NULL);
	m_pGDatabase.Assign(NULL);
	if (m_pGDOObjectsCollection.IsValid()) {
		 WTRiASBase(m_pGDOObjectsCollection) -> put_Parent(NULL);
		 m_pGDOObjectsCollection.Assign(NULL);
	}
	if (m_pTRiASCSTransform.IsValid())
		m_pTRiASCSTransform -> ShutDown();

	ReleasePropertySupportObjects();
	FreePropertiesCollection();

	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_5(CGDODatabase, OpenDatabase
	, /*[in]*/ BSTR, Name
	, /*[in, optional, defaultvalue]*/ VARIANT_BOOL, Exclusive
	, /*[in, optional, defaultvalue]*/ VARIANT_BOOL, ReadOnly
	, /*[in, optional, defaultvalue]*/ VARIANT_BOOL, ModTrack
	, /*[in, optional, defaultvalue]*/ BSTR, Source
) 
{
	COM_TRY {
		ERROR_EXPR_TRUE(!m_pParent, E_FAIL);

	// zur Sicherheit schließen...
		ERROR_FAILED_HRESULT(DoCloseDatabase(), GDB_E_CANTOPENDATABASE);

	// jetzt Connection usw. zusammenbasteln
	CComBSTR bStr;
	
		WTRiASConnection(m_pParent) -> get_Name(&bStr);

	HRESULT hr = DoCreateConnection(Name, bStr, Source, Exclusive, ReadOnly, ModTrack);

		if (FAILED(hr)) return hr;

		RETURN_FAILED_HRESULT(CreatePropertiesCollection());

	// die Objekterzeugung braucht folgende Hilfestellung
		SetPropertyBy (GetDispatch(), g_cbObjectHandleIsValid, VARIANT_TRUE, true);

	// ohne Koordinatensystem geht glattweg gar nichts, selbiges deshalb zuallererst:
	WTRiASPropertyBase PropBase (m_pParent);
	WTRiASCS csOut (GetPropertyFrom (PropBase, g_cbTRiASCSService, (IDispatch *)NULL), false);
	TRIASCSTYPE	csType;

		csOut -> get_CoordSystemType(&csType);
		ERROR_EXPR_TRUE(tcsCS_Undefined == csType, GDB_E_INVALIDCOORDSYSTEM);
		ERROR_FAILED_HRESULT(m_pTRiASCSTransform -> AddInputCS(m_csIn), E_FAIL);
		ERROR_FAILED_HRESULT(m_pTRiASCSTransform -> putref_OutputCS(csOut), E_FAIL);
		ERROR_FAILED_HRESULT(csOut -> Recompute(), E_FAIL);

	WTRiASMDSMap MDSMap (GetPropertyFrom(PropBase, g_cbMetaDataMap, (IDispatch *)NULL), false);

		if (!MDSMap.IsValid())
		{
			MDSMap.CreateInstance (CLSID_TRiASMDSMap);
			SetPropertyBy(PropBase, g_cbMetaDataMap, MDSMap, true);
		}

	// gut passendes umschließendes Rechteck ermitteln
	WTRiASSimpleRectangle Rect (GetPropertyFrom (PropBase, g_cbDatabaseContainer, (IDispatch *)NULL), false);

		if (!Rect.IsValid()) {
		double X[2], Y[2];

			m_pTRiASCSTransform -> GetGoodEnvelope(&X[0], &Y[0], &X[1], &Y[1]);

		CCSRectangleGeometry rcGoodEnvelope;

			rcGoodEnvelope.put_XMin(X[0]);
			rcGoodEnvelope.put_XMax(X[1]);
			rcGoodEnvelope.put_YMin(Y[0]);
			rcGoodEnvelope.put_YMax(Y[1]);

		// und als Initialwert für Container festlegen
			Rect = rcGoodEnvelope;
			SetPropertyBy(PropBase, g_cbDatabaseContainer, Rect, true);
			m_bInitContainer = true;	// neuer Container ==> also unbedingt korrigieren
		}
		m_rcContainer = Rect;
		RETURN_FAILED_HRESULT(SetupDefaultGeometries());

	// ganz zu Anfang sind wir erstmal "sauber"
		m_bDirty = false;
	} COM_CATCH;
	return S_OK;
}

HRESULT CGDODatabase::SetupDefaultGeometries() 
{
	m_mapGeoTypeToDefault.clear();
	double	X[2];
	double	Y[2];

/////////////////////////////////////////////////////////////////////
// gut passendes umschließendes Rechteck ermitteln
	m_pTRiASCSTransform -> GetGoodEnvelope(&X[0], &Y[0], &X[1], &Y[1]);

/////////////////////////////////////////////////////////////////////
// Standardgeometrien für Fläche / Line / Punkt
CCSRectangleGeometry	rect(X[0], Y[0], X[1], Y[1], 1);
CCSPointGeometry		ptLL(X[0], Y[0]);	// links unten
CCSPointGeometry		ptUR(X[1], Y[1]);	// rechts oben
W_DGMPolygonGeometry	poly(CLSID_TRiASCSPolygonGeometry);

	ERROR_FAILED_HRESULT(WPersistStreamInit(poly) -> InitNew(), E_FAIL);
	ERROR_FAILED_HRESULT(MakePolyFromRect(poly, rect), E_FAIL);

CComVariant	vPoly, vLine, vPoint, vText;
WTRiASTransformGeometry geoTransform;

//	vPoly = poly;
	geoTransform = poly;
	ERROR_FAILED_HRESULT(geoTransform -> TransformInverse(m_csGUID, m_pTRiASCSTransform), GDB_E_CANNOTBUILDOBJECT);
	ERROR_FAILED_HRESULT(m_pTRiASCSStorageServiceGDO -> GeometryToStorageGDO(GEOMETRYTYPE_Area, poly, CLEARED(vPoly)), GDB_E_CANNOTBUILDOBJECT);
	m_mapGeoTypeToDefault.insert(gdbAreal, CComVariant(vPoly));

CCSLineGeometry		line(2, X, Y);

//	vLine = line;
	geoTransform = line;
	ERROR_FAILED_HRESULT(geoTransform -> TransformInverse(m_csGUID, m_pTRiASCSTransform), GDB_E_CANNOTBUILDOBJECT);
	ERROR_FAILED_HRESULT(m_pTRiASCSStorageServiceGDO -> GeometryToStorageGDO(GEOMETRYTYPE_Line, line, CLEARED(vLine)), GDB_E_CANNOTBUILDOBJECT);
	m_mapGeoTypeToDefault.insert(gdbLinear, CComVariant(vLine));

CCSPointGeometry	point((X[0] + X[1]) / 2, (Y[0] + Y[1]) / 2);

//	vPoint = point;
	geoTransform = point;
	ERROR_FAILED_HRESULT(geoTransform -> TransformInverse(m_csGUID, m_pTRiASCSTransform), GDB_E_CANNOTBUILDOBJECT);
	ERROR_FAILED_HRESULT(m_pTRiASCSStorageServiceGDO -> GeometryToStorageGDO(GEOMETRYTYPE_Point, point, CLEARED(vPoint)), GDB_E_CANNOTBUILDOBJECT);
	m_mapGeoTypeToDefault.insert(gdbPoint, CComVariant(vPoint));

	m_mapGeoTypeToDefault.insert(gdbAnySpatial, CComVariant(vPoint));

W_DGMTextPointGeometry text(CLSID_TRiASCSTextPointGeometry);

	WPersistStreamInit(text) -> InitNew();

CCSPointGeometry ptOfText(text);

	ptOfText.put_X((X[0] + X[1]) / 2);
	ptOfText.put_Y((Y[0] + Y[1]) / 2);

CComBSTR strText;

	strText.LoadString(IDS_APP_VERSION_STRING);
	text -> put_text(strText);

//	vText = text;
	ERROR_FAILED_HRESULT(m_pTRiASCSStorageServiceGDO -> GeometryToStorageGDO(GEOMETRYTYPE_Text, text, CLEARED(vText)), GDB_E_CANNOTBUILDOBJECT);
	m_mapGeoTypeToDefault.insert(gdbGraphicsText, CComVariant(vText));

	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_5(CGDODatabase, OpenFilesAsDatabase
	, /*[in]*/ IUnknown*, pEnum
	, /*[in, optional, defaultvalue]*/ VARIANT_BOOL, bExclusive
	, /*[in, optional, defaultvalue]*/ VARIANT_BOOL, fReadOnly
	, /*[in, optional, defaultvalue]*/ VARIANT_BOOL, bModTrack
	, /*[in, optional, defaultvalue]*/ BSTR, Source
) 
{
	FUNC_NOT_IMPL();
}

IMPLEMENT_DEBUG_FUNCENTRY_3(CGDODatabase, CreateDatabaseFromFiles, IUnknown*, pIEnum, BSTR, Locale, BSTR, Source) 
{
	FUNC_NOT_IMPL();
}

IMPLEMENT_DEBUG_FUNCENTRY_5(CGDODatabase, OpenStorageAsDatabase, IUnknown *, pIStorage, VARIANT_BOOL, Exclusive, VARIANT_BOOL, fReadOnly, VARIANT_BOOL, ModTrack, BSTR, Source) 
{
	FUNC_NOT_IMPL();
}

IMPLEMENT_DEBUG_FUNCENTRY_4(CGDODatabase, CreateDatabaseOnStg, IUnknown *, pIUnk, BSTR, Name, BSTR, Locale, BSTR, Source) 
{
	FUNC_NOT_IMPL();
}

IMPLEMENT_DEBUG_FUNCENTRY_0(CGDODatabase, Close) 
{
	ERROR_FAILED_HRESULT(DoCloseDatabase(), GDB_E_CANTCLOSEDATABASE);
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_CollatingOrder, long*, pCollatingOrder) 
{
	CHECKINPOINTER(pCollatingOrder);
	COM_TRY {
		_ASSERTE(!!m_pGDatabase);
		EXT_ERROR_FAILED_HRESULT(m_pGDatabase -> get_CollatingOrder(pCollatingOrder), NDB_E_NATIVEDB);
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_Transactions, VARIANT_BOOL*, Transactions) 
{
	CHECKINPOINTER(Transactions);
	COM_TRY {
		_ASSERTE(!!m_pGDatabase);
		EXT_ERROR_FAILED_HRESULT(m_pGDatabase -> get_Transactions(Transactions), NDB_E_NATIVEDB);
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_GAliasTable, BSTR*, AliasTableName) 
{
	CHECKINPOINTER(AliasTableName);
	COM_TRY {
		_ASSERTE(!!m_pGDatabase);
		EXT_ERROR_FAILED_HRESULT(m_pGDatabase -> get_GAliasTable(AliasTableName), NDB_E_NATIVEDB);
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_SQLConformance, long*, pSQLConformance) 
{
	CHECKINPOINTER(pSQLConformance);
	COM_TRY {
		_ASSERTE(!!m_pGDatabase);
		EXT_ERROR_FAILED_HRESULT(m_pGDatabase -> get_SQLConformance(pSQLConformance), NDB_E_NATIVEDB);
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_0(CGDODatabase, BeginTrans) 
{
	FUNC_NOT_IMPL();
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, ClearModificationLog,/*[in, optional, defaultvalue]*/ LONG, Entry) 
{
	FUNC_NOT_IMPL();
}

IMPLEMENT_DEBUG_FUNCENTRY_0(CGDODatabase, CommitTrans) 
{
	FUNC_NOT_IMPL();
}

IMPLEMENT_DEBUG_FUNCENTRY_0(CGDODatabase, Rollback) 
{
	FUNC_NOT_IMPL();
}

IMPLEMENT_DEBUG_FUNCENTRY_2(CGDODatabase, GetExtension, BSTR, Name, IDispatch**, ppGExtension) 
{
	FUNC_NOT_IMPL();
}

HRESULT CGDODatabase::OnReloadEnvelope()
{
	m_bInitContainer = true;
	return S_OK;
}

HRESULT CGDODatabase::OnReloadObjects()
{
	if (!m_pGDOObjectsCollection)
	{
		RETURN_FAILED_HRESULT(EnsureObjectsColl());
	} else 
	{
		RETURN_FAILED_HRESULT(ReloadObjectsColl());
	}
	return S_OK;
}

HRESULT CGDODatabase::OnResetLookupWindow()
{
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, ReLoad, /*[in]*/ RELOADDATABASE, ToReLoad) 
{
	COM_TRY 
	{
		switch (ToReLoad)
		{
			case RELOADDATABASE_Envelope:
				OnReloadEnvelope();
				break;
			
			case RELOADDATABASE_Objects:
				OnReloadObjects();
				break;
			
			case RELOADDATABASE_ResetLookupWindow:
				OnResetLookupWindow();
				break;

			case RELOADDATABASE_All:
				OnReloadObjects();
				OnReloadEnvelope();
				OnResetLookupWindow();
				break;

			default:
				MAKE_ERROR(E_INVALIDARG);
		}
	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, RefreshChangesFromModificationLog, 
	/*[in]*/ ITRiASRefreshChangesCallback *, pICallback) 
{
	FUNC_NOT_IMPL();
}

///////////////////////////////////////////////////////////////////////////////
// 
#include <io.h>

class CErrorMode 
{
private:
	UINT m_uiEMode;

public:
	explicit CErrorMode(UINT uiEMode) { m_uiEMode = ::SetErrorMode(uiEMode); }
	~CErrorMode() { ::SetErrorMode(m_uiEMode); }
};

IMPLEMENT_DEBUG_FUNCENTRY_3(CGDODatabase, CreateDatabase,/*[in]*/ BSTR, Name, 
	/*[in]*/ BSTR, Locale, BSTR, Source) 
{
	HRESULT	hr = E_FAIL;
	USES_CONVERSION;
	CComBSTR dbType(_T(""));
	CComBSTR csName(_T(""));
		
	COM_TRY {
	// (1) neue Datenbank erzeugen
	WParseStringPairs parse(CLSID_ParseStringPairs);
	long lPairs = 0;

		THROW_FAILED_HRESULT(parse -> put_Pattern(CComBSTR(g_cbCollatePattern)));
		THROW_FAILED_HRESULT(parse -> Parse(Source, &lPairs));
		ERROR_EXPR_TRUE(0 == lPairs, GDB_E_INVALID_PARAMETER);
		ERROR_FAILED_HRESULT(parse -> get_Value(CComBSTR(_T("PROGID")), 
			CLEARED(dbType)), GDB_E_INVALID_PARAMETER);
		ERROR_FAILED_HRESULT(parse -> get_Value(CComBSTR(g_cbCSFFileKey), 
			CLEARED(csName)), GDB_E_INVALID_PARAMETER);

	WTRiASDataServerRegEntries servers (CLSID_TRiASDataServerRegEntries);
	WTRiASDataServerRegEntry server;

		ERROR_FAILED_HRESULT(servers -> FindFromServerProgID(dbType, server.ppi()), 
			DBE_E_FAILED_TOACCESSDATASERVER);

	// sicherstellen, daß wirklich was erzeugt werden kann
		EXT_ERROR_FAILED_HRESULT(server -> get_IsReadWrite(&m_bWritable), NDB_E_NATIVEDB);
		ERROR_EXPR_FALSE(m_bWritable, TRIASDB_E_DATABASENOTUPDATABLE);

	CIID CreateDbGuid(GUID_NULL);
	CComBSTR bstrProgId;

		if (SUCCEEDED(server -> get_CreateDatabase(CLEARED(bstrProgId))))
			CreateDbGuid = CIID(bstrProgId, CIID::INITCIID_InitFromProgId);

	AC_GDatabase pDatabase;

		if (CreateDbGuid.IsValid()) {
		// SQLServer et.al.
		WCreateDatabase CreateDb (CreateDbGuid);

			EXT_ERROR_FAILED_HRESULT(CreateDb->CreateDatabase(Name, Locale, 
				Source), NDB_E_NATIVEDB);

			RETURN_FAILED_HRESULT(DoCreateConnection(Name, Name, Source, 
				VARIANT_TRUE, VARIANT_FALSE, VARIANT_FALSE));
			pDatabase = m_pGDatabase;
		}
		else {
		// Access et.al.
		CErrorMode	em(SEM_NOOPENFILEERRORBOX);

			if (0 == ::_waccess(Name, 00) && 0 == ::_waccess(Name, 06))	{
				SYS_ERROR(0 != ::_wunlink(Name), DBE_E_FAILED_TOACCESSDATABASE);
			} 
			else if (0 == ::_waccess(Name, 00) && 0 == ::_waccess(Name, 04)) {
				MAKE_ERROR(DBE_E_FAILED_TOACCESSDATABASE);
			}

		WUnknown pObj;
		CIID Guid(dbType, CIID::INITCIID_InitFromProgId);

			CO_ERROR_FAILED_HRESULT(pObj.CreateInstance(Guid), DBE_E_SERVICE_NOTAVAILABLE);
			pDatabase = pObj;
			EXT_ERROR_FAILED_HRESULT(pDatabase -> CreateDatabase(Name, Locale), NDB_E_NATIVEDB);
		}

	// (2) Koordinatensystem einpflanzen
	CComBSTR strAliasTable;

		EXT_ERROR_FAILED_HRESULT(pDatabase -> get_GAliasTable(CLEARED(strAliasTable)), NDB_E_NATIVEDB);

	CComBSTR S(_T("SELECT TableName FROM "));

		S.Append(strAliasTable);
		S.Append(_T(" WHERE TableType=\'"));
		S.Append(gdbCoordSystem);
		S.Append(_T("\'"));

	WGFields flds;
	WGField	f;
	CComVariant	v;

		{
		AC_GRecordset rs;

			EXT_ERROR_FAILED_HRESULT(pDatabase -> OpenRecordset(S, 
				CComVariant(gdbOpenDynaset), vtMissing, vtMissing, vtMissing, 
				vtMissing, rs.ppi()), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(rs -> get_GFields(flds.ppi()), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(flds -> get_Item(CComVariant(0L), f.ppi()), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(f -> get_Value(CLEARED(v)), NDB_E_NATIVEDB);
		}	// rs geht 'out of scope'

		ERROR_EXPR_TRUE(!V_ISBSTR(&v), E_FAIL);

	CComBSTR strCSTable(V_BSTR(&v));
	short nFields, nField;

		{
		AC_GRecordset rs;

			EXT_ERROR_FAILED_HRESULT(pDatabase -> OpenRecordset(strCSTable, 
				CComVariant(gdbOpenDynaset), vtMissing, vtMissing, vtMissing, 
				vtMissing, rs.ppi()), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(rs -> get_GFields(flds.ppi()), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(flds -> get_Count(&nFields), NDB_E_NATIVEDB);

		WIGMCoordSystem	cs(CLSID_CoordSystem);			// Initialisiert als WGS84 / CylEqui
		MC::ArrayVariant arrayOfVariants(MC::Dim((long) nFields));
		SAFEARRAY *pArr = &arrayOfVariants;

			EXT_ERROR_FAILED_HRESULT(cs -> FormatGCoordSystemTableRow(pArr), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(rs -> AddNew(), NDB_E_NATIVEDB);
			EXT_ERROR_FAILED_HRESULT(rs -> get_GFields(flds.ppi()), NDB_E_NATIVEDB);
			for (nField = 0; nField < nFields; ++nField)
			{
				EXT_ERROR_FAILED_HRESULT(flds -> get_Item(CComVariant((long) nField), f.ppi()), NDB_E_NATIVEDB);
				EXT_ERROR_FAILED_HRESULT(f -> put_Value(arrayOfVariants[nField]), NDB_E_NATIVEDB);
			}
			EXT_ERROR_FAILED_HRESULT(rs -> Update(), NDB_E_NATIVEDB);
		}	// rs geht 'out of scope'

	// (3) fertig
		if (CreateDbGuid.IsValid()) {
			EXT_ERROR_FAILED_HRESULT(DoCloseDatabase(), NDB_E_NATIVEDB);
		}
		else {
			EXT_ERROR_FAILED_HRESULT(pDatabase -> Close(), NDB_E_NATIVEDB);
		}

	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, SaveAs,/*[in]*/ BSTR, NewName) 
{
	FUNC_NOT_IMPL();
}

IMPLEMENT_DEBUG_FUNCENTRY_0(CGDODatabase, Save) 
{
	COM_TRY {
		if (m_bWritable)
		{
			ERROR_FAILED_HRESULT(m_pGDOObjectsCollection -> Save(), E_FAIL);
		}
		m_bDirty = false;
	} COM_CATCH;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_OpenedAsCopy,/*[out, retval]*/ VARIANT_BOOL*, pVal) 
{
	*pVal = VARIANT_FALSE;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_CouldOpenTarget,/*[out, retval]*/ VARIANT_BOOL*, pVal) 
{
	FUNC_NOT_IMPL();
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_Updatable,/*[out, retval]*/ VARIANT_BOOL*, pVal) 
{
	COM_TRY {
		_ASSERTE(!!m_pGDatabase);
		EXT_ERROR_FAILED_HRESULT(m_pGDatabase -> get_Updatable(pVal), NDB_E_NATIVEDB);
	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_Type, /*[out, retval]*/ BSTR*, pStrProgID) 
{
	COM_TRY {
		_ASSERTE(!!m_pDBConnection);
		EXT_ERROR_FAILED_HRESULT(m_pDBConnection -> get_Type(pStrProgID), NDB_E_NATIVEDB);
	} COM_CATCH
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_StorageMode, /*[out, retval]*/ DATABASESTORAGEMODE*, pVal) 
{
	*pVal = m_rgStgMode;
	return S_OK;
}

IMPLEMENT_DEBUG_FUNCENTRY_1(CGDODatabase, get_Connect, BSTR*, Connect) 
{
	COM_TRY {
		_ASSERTE(!!m_pDBConnection);
		EXT_ERROR_FAILED_HRESULT(m_pDBConnection -> get_ConnectInfo(Connect), NDB_E_NATIVEDB);
	} COM_CATCH
	return S_OK;
}

#include "../TRiASDB/PropertySupportImpl.cpp"
