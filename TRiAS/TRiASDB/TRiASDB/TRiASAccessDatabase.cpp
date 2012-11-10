// @doc
// @module TRiASAccessDatabase.cpp | Implementation of the <c CTRiASDatabase> and
// <c CTRiASCompatibleDatabase> classes, implementation of the functions of the
// <i ITRiASAccessDatabase>- Interface

#include "stdafx.h"

//#include <tstring>
#include <ospace/file/path.h>
#include <ospace/utility/autoptr.h>

#include <Com/SafeArray.h>
#include <Com/PropertyHelper.h>
#include <Com/MkHelper.h>

#include <fprotos.h>
#include <KoOrd.h>			// MAXKOORD

#include <NativeView.h>
#include <NativeIdent.h>
#include <CSRectGeom.h>
#include <ViewPropHeader.h>
#include <ScaleHeader.h>

#include "Strings.h"
#include "GlobalVars.h"
#include "Wrapper.h"
#include "TRiASDBGuids.h"

#include "TRiASDatabase.h"
#include "GenObjectMap.h"
#include "TRiASSimpleObjects.h"
#include "TRiASObjectsCollection.h"

#import "Tlb/TRiASCS.tlb" raw_interfaces_only raw_dispinterfaces no_namespace \
	named_guids 

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface2(DVisInfo, IID_DVisInfo);
DefineSmartInterface(TRiASSimpleObjects);
DefineSmartInterface(TRiASObjectHandleMap);
DefineSmartInterface(TRiASViewItem);
DefineSmartInterface(TRiASSearchObjects)		// WTRiASSearchObjects
DefineSmartInterface(TRiASCSTransform)			// WTRiASCSTransform
DefineSmartInterface(TRiASTransformGeometry)	// WTRiASTransformGeometry
DefineSmartInterface(TRiASSimpleRectangle);
DefineSmartInterface(TRiASSimplePoints);
DefineSmartInterface(TRiASCSGeometryProperties);

DefineSmartInterface(OleObject);
DefineSmartInterface(BindCtx);

DefineSmartInterface2(_DGMPoints, IID__DGMPoints);	// W_DGMPoints
DefineSmartInterface2(_DGMPolygonGeometry, IID__DGMPolygonGeometry);	// W_DGMPolylineGeometry

#if defined(_USE_CLASSFACTORY_CACHE)
///////////////////////////////////////////////////////////////////////////////
// ClassFactorycache benutzen
#include <Com/ClassFactoryCache.h>
typedef CClassFactoryCache<&CLSID_TRiASSimpleObjects> CSimpleObjectsFactory;
typedef CClassFactoryCache<&CLSID_TRiASViewItem> CViewItemFactory;
CSimpleObjectsFactory MakeSimpleObjectsFact;
CViewItemFactory MakeViewItemFact;
#endif // defined(_USE_CLASSFACTORY_CACHE)

///////////////////////////////////////////////////////////////////////////////
// Callbackfunktion zur Enumeration aller Einträge einer Ansicht

OBJECTTYPE VisTypeToOBJECTTYPE (CNativeView::VisType rgType)
{
	switch (rgType) {
	case CNativeView::VT_Punkt:
	case CNativeView::VT_PunktDef:
		return OBJECTTYPE_Point;

	case CNativeView::VT_Linie:
	case CNativeView::VT_LinieDef:
		return OBJECTTYPE_Line;

	case CNativeView::VT_Flaeche:
	case CNativeView::VT_FlaecheDef:
		return OBJECTTYPE_Area;

	case CNativeView::VT_Text:
	case CNativeView::VT_TextDef:
		return OBJECTTYPE_Text;

	default:
	case CNativeView::VT_Default:
		break;
	}
	return OBJECTTYPE_Unknown;
}

HRESULT CALLBACK CTRiASDatabaseBase::EnumViewEntryCallBack (LONG lIdent, CNativeView::VisType rgType, DWORD dwData)
{
	_ASSERTE(0L != dwData);
	COM_TRY {
	CEnumViewEntryCallback *pData = reinterpret_cast<CEnumViewEntryCallback *>(dwData);

		_ASSERTE(NULL != pData);

	// VisInfo aus Ansicht lesen
	WDVisInfo VisInfo;
	WDispatch App;

		THROW_FAILED_HRESULT(pData -> m_pTarget -> GetViewEntry (lIdent, rgType, VisInfo.ppi()));
		THROW_FAILED_HRESULT(pData -> m_View -> get_Application (App.ppi()));

	// Objects-Collection erzeugen bzw. wiederverwenden
	// Objekt evtl. aus der DatabaseMap holen
	WTRiASObjects Objects;
	WTRiASObjectHandleMap Map (GetPropertyFrom (WTRiASPropertyBase(pData -> m_pDB), g_cbObjectsMap, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab
	OBJECTTYPE rgObjType = VisTypeToOBJECTTYPE(rgType);
	CInitializeSimpleObjects InitObjs(App, static_cast<ITRiASDatabase *>(pData -> m_pDB), rgObjType);
	INT_PTR hObjs = NULL;

#if defined(_USE_CLASSFACTORY_CACHE)
	HRESULT hr = FindInMapOrCreateObjectEx(Map, lIdent, hObjs, Objects, MakeSimpleObjectsFact, InitObjs, OBJECTMAPMODE_CreateObjectHandle);
#else
	HRESULT hr = FindInMapOrCreateObjectEx(Map, lIdent, hObjs, Objects, CLSID_TRiASSimpleObjects, InitObjs, OBJECTMAPMODE_CreateObjectHandle);
#endif // defined(_USE_CLASSFACTORY_CACHE)

		THROW_FAILED_HRESULT(hr);
		if (TRIASDB_I_OBJECTS_NOT_EXISTS == hr)	return S_OK;

	// ViewItem wiederfinden bzw. erzeugen und initialisieren
	WTRiASViewItem ViewItem;
	bool fCreated = false;

		if (FAILED(pData -> m_View -> get_ViewItem (CComVariant(Objects), VARIANT_FALSE, g_bstrNil, ViewItem.ppi()))) {
#if defined(_USE_CLASSFACTORY_CACHE)
			THROW_FAILED_HRESULT(MakeViewItemFact.CreateInstance(ViewItem.ppi()));
#else
			ViewItem = WTRiASViewItem(CLSID_TRiASViewItem);		// throws hr
#endif // defined(_USE_CLASSFACTORY_CACHE)
			THROW_FAILED_HRESULT(WPersistStreamInit(ViewItem) -> InitNew());
			THROW_FAILED_HRESULT(ViewItem -> put_Application (App));
			THROW_FAILED_HRESULT(ViewItem -> put_Parent (pData -> m_View));
			fCreated = true;
		}

		THROW_FAILED_HRESULT(VisInfo -> put_Application (App));
		THROW_FAILED_HRESULT(VisInfo -> put_Parent (pData -> m_View));

	OBJECTTYPE rgRealTypes = OBJECTTYPE_Unknown;
#if defined(_DEBUG)
	bool fNoObjects = false;
#endif // _DEBUG

		THROW_FAILED_HRESULT(Objects -> get_Types (&rgRealTypes));
		THROW_FAILED_HRESULT(ViewItem -> put_VisInfo (rgObjType, VisInfo));
		if (rgRealTypes & rgObjType) {
		// Objektklasse enthält real Objekte des definierten Typs
			THROW_FAILED_HRESULT(ViewItem -> put_Objects (rgObjType, Objects));
		} 
		else {
		// es gibt keine Objekte dieses Typs in dieser Objektklasse, da es jedoch möglicherweise
		// der einzige Objekttyp dieser Objektklasse ist, muß dem LegendenEintrag sein Name
		// explizit mitgeteilt werden.

		// ViewItem wird unter dem Objs-Moniker angelegt
		WMoniker mk;
		CComBSTR bstrMkName;

			RETURN_FAILED_HRESULT(MkGetMoniker (Objects, OLEGETMONIKER_FORCEASSIGN, OLEWHICHMK_OBJFULL, mk.ppi()));
			RETURN_FAILED_HRESULT(MkGetDisplayName (mk, CLEARED(&bstrMkName)));

			THROW_FAILED_HRESULT(ViewItem -> put_Description (bstrMkName));
			THROW_FAILED_HRESULT(ViewItem -> put_ObjectTypes (rgObjType));
#if defined(_DEBUG)
			fNoObjects = true;
#endif // _DEBUG
		}

	// wenn Item neu erzeugt wurde, dann zur Ansicht hinzufügen
		if (fCreated) {
		// objektbezogene Visualisierung anpassen
		CNativeIdent Ident (pData -> m_pDB -> m_hPr, lIdent);
		os_string strMode (g_cbNil);
		char cbBuffer[_MAX_PATH];

			_ASSERTE(!!Ident);		// Ident muß gültig sein
			if (0 != pData -> m_lObjVisMCode && 
				SUCCEEDED(Ident.GetTextMerkmal (pData -> m_lObjVisMCode, strMode))) 
			{
			// Objekte dieser Objektklasse sind in dieser Ansicht objektbezogen visualisiert
				strMode += g_cbComma;
				strMode += _ltoa (pData -> m_lObjVisMCode, cbBuffer, 10);

			// jetzt am Legendeneintrag wegschreiben
				wsprintf (cbBuffer, g_cbSysProperty, pData -> m_lObjVisMCode);
				THROW_FAILED_HRESULT(SetPropertyBy (WTRiASPropertyBase(ViewItem), cbBuffer, CComVariant(strMode.c_str()), true));
			}

		// LegendenInfo umkopieren
		os_string strLegEntry;

			if (0 != pData -> m_lLegVisMCode && 
				SUCCEEDED(Ident.GetTextMerkmal (pData -> m_lLegVisMCode, strLegEntry))) 
			{
			// Objektklasse besitzt LegendenInfo/Objekte sind in dieser Ansicht in Legende enthalten

			// jetzt am Legendeneintrag wegschreiben
				wsprintf (cbBuffer, g_cbSysProperty, pData -> m_lLegVisMCode);
				THROW_FAILED_HRESULT(SetPropertyBy (WTRiASPropertyBase(ViewItem), cbBuffer, CComVariant(strLegEntry.c_str()), true));
			}

		// Maßstabsbereiche umkopieren
			for (int i = 0; i < 4; i++) {
			string strScale (g_cbNil);

				if (0 != pData -> m_lScaleMCode[i] && 
					SUCCEEDED(Ident.GetTextMerkmal (pData -> m_lScaleMCode[i], strScale))) 
				{
				// Objekte dieser Objektklasse und des Objekttypes haben Maßstabsbereich für 
				// Darstellungsparameter

				// jetzt am Legendeneintrag wegschreiben
					wsprintf (cbBuffer, g_cbSysProperty, pData -> m_lScaleMCode[i]);
					THROW_FAILED_HRESULT(SetPropertyBy (WTRiASPropertyBase(ViewItem), cbBuffer, CComVariant(strScale.c_str()), true));
				}
			}

		// und zur Ansicht hinzufügen ...
			THROW_FAILED_HRESULT(pData -> m_View -> AddViewItem (ViewItem));
		}

#if defined(_DEBUG)
// Überprüfen, ob Typen etc. richtig angekommen sind
		COM_TRY {
		CComBSTR bstrName;

			_ASSERTE(SUCCEEDED(ViewItem -> get_Name (CLEARED(&bstrName))));

		WTRiASViewItem TstItem;

			_ASSERTE(SUCCEEDED(pData -> m_View -> get_ViewItem (CComVariant(bstrName), VARIANT_FALSE, g_bstrNil, TstItem.ppi())));

		OBJECTTYPE rgTstTypes = OBJECTTYPE_Unknown;
		WTRiASObjects TstObjs;
		WDVisInfo TstVis;

			_ASSERTE(SUCCEEDED(TstItem -> get_Types (&rgTstTypes)));
			_ASSERTE(rgTstTypes & rgObjType);		// neuer Typ muß da sein
			_ASSERTE(SUCCEEDED(TstItem -> get_VisInfo (rgObjType, TstVis.ppi())));
			_ASSERTE(fNoObjects || SUCCEEDED(TstItem -> get_Objects (rgObjType, TstObjs.ppi())));
		} COM_CATCH_IGNORE;
#endif // _DEBUG
	} COM_CATCH;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Callbackfunktion zur Enumeration aller Ansichten 
HRESULT CTRiASDatabaseBase::CorrectViewEntry (
	CNativeView &rView, LPCOLESTR pcoleEntry, ULONG &rulMCodeView, ULONG &rlMCode)
{
	USES_CONVERSION;
	COM_TRY {
	CViewPropHeader Hdr (m_hPr);
	os_string strMCode;

		rulMCodeView = Hdr.GetMCode (OLE2A(pcoleEntry));
		if (0 != rulMCodeView && SUCCEEDED(rView.GetTextMerkmal (rulMCodeView, strMCode))) {
		// MerkmalsCode für Idents merken
			rlMCode = strtoul (strMCode.c_str(), NULL, 10);

			if (0 != rlMCode) {
			// im ProjektHeader MCode der Ansichten wegschreiben
			WTRiASProject Prj;

				THROW_FAILED_HRESULT(FindSpecificParent (m_Parent, Prj.ppi()));
			
			WTRiASPropertyBase PropBase (Prj);
			ULONG ulViewMCodeT = GetPropertyFrom (PropBase, pcoleEntry, 0L);

				if (0 == ulViewMCodeT)
					SetPropertyBy (PropBase, pcoleEntry, CComVariant ((long)rulMCodeView, VT_I4), true);
				else
					rulMCodeView = ulViewMCodeT;	// bereits vergebenen MCode verwenden

			// VisualisierungsMerkmale sind i.a. keine Objektmerkmale, sie müssen daher explizit
			// zu den existierenden Objekteigenschaften hinzugefügt werden
			WTRiASFeatures Feats (GetPropertyFrom (WTRiASPropertyBase(GetDispatch()), g_cbSimpleFeatures, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab
			WTRiASFeature Feat;
			CComVariant vMCode((long)rlMCode, VT_I4);

				_ASSERTE(Feats.IsValid());
				if (FAILED(Feats -> Item (vMCode, Feat.ppi()))) {
				// existiert noch nicht, also zur Sammlung der Objekteigenschaften hinzufügen
				FEATURETYPE rgType = FEATURETYPE(DATATYPE_FROM_VT(VT_BSTR) | CNativePbdMerkmal::PBDFEATURETYPE_Object);

					THROW_FAILED_HRESULT(Feats -> Add (vMCode, g_bstrNil, rgType, Feat.ppi()));

				// für die weiteren Male muß das entsprechende Merkmal in der GeoDB auf 'ObjektMerkmal' 
				// gesetzt werden
				CNativeMerkmal Merkmal (m_hPr, rlMCode);

					if (!!Merkmal) 
						Merkmal.SetTyp (CNativePbdMerkmal::PBDFEATURETYPE_Object);
				}
			}
		} else 
			rlMCode = 0L;		// in dieser Ansicht keine objektbezogene Visualisierung

	} COM_CATCH;
	return S_OK;
}

HRESULT CALLBACK CTRiASDatabaseBase::EnumViewCallBack (LPCSTR pcKey, DWORD dwData)
{
	_ASSERTE(0L != dwData);

//#if defined(_DEBUG)
//	if (!strcmp (pcKey, "__DefaultVisInfo__"))
//		return S_OK;
//#endif // _DEBUG

CEnumViewCallback *pData = (CEnumViewCallback *)dwData;
CTRiASDatabaseBase *pDB = pData -> m_pDB;

	_ASSERTE(NULL != pDB);
	USES_CONVERSION;
	COM_TRY {
	// wenn Ansicht bereits existiert (evtl. mit anderer Groß-/Kleinschreibung), 
	// dann neuen Ansichtsnamen erzeugen, dazu solange Name_%iCnt% hinzufügen, bis es 
	// eindeutig ist
	WTRiASView View;
	CComBSTR bstrView (pcKey);
	int iCnt = 0;

		while (SUCCEEDED(pData -> m_Views -> Item (CComVariant(bstrView), View.ppi()))) {
		wchar_t cbBuffer[32];

			_ltow (++iCnt, cbBuffer, 10);
			bstrView = pcKey;
			bstrView.Append (g_cbUnderScore);
			bstrView.Append (cbBuffer);
		}

	// jetzt neue Ansicht erzeugen
	WDispatch App;

		THROW_FAILED_HRESULT(pDB -> get_Application (App.ppi()));

		THROW_FAILED_HRESULT(View.CreateInstance(CLSID_TRiASView));
		THROW_FAILED_HRESULT(WPersistStreamInit(View) -> InitNew());

		THROW_FAILED_HRESULT(View -> put_Application(App));
		THROW_FAILED_HRESULT(View -> put_Parent((ITRiASDatabase *)pDB));
		THROW_FAILED_HRESULT(View -> put_Name(bstrView));

	// bei dieser Gelegenheit gleich noch objektbezogene Visualisierung etc. übernehmen
	CEnumViewEntryCallback CallBackData;
	CNativeView TargetView (pDB -> m_hPr, pcKey);			// Ansicht in der TRiAS-GeoDB
	ULONG lObjVisMCode = 0L;

		THROW_FAILED_HRESULT(pDB -> CorrectViewEntry (TargetView, g_cbObjVisInfoMCode, lObjVisMCode, CallBackData.m_lObjVisMCode));

	// Legendeneinträge umhängen
	ULONG lLegVisMCode = 0L;

		THROW_FAILED_HRESULT(pDB -> CorrectViewEntry (TargetView, g_cbLegendInfoMCode, lLegVisMCode, CallBackData.m_lLegVisMCode));

	// Maßstabsbereiche einzelner Visualisierungen umhängen
	ULONG lScaleMCode[4];

		ZeroMemory (lScaleMCode, 4*sizeof(ULONG));
		THROW_FAILED_HRESULT(pDB -> CorrectViewEntry (TargetView, g_cbScaleViewPMCode, lScaleMCode[0], CallBackData.m_lScaleMCode[0]));
		THROW_FAILED_HRESULT(pDB -> CorrectViewEntry (TargetView, g_cbScaleViewLMCode, lScaleMCode[1], CallBackData.m_lScaleMCode[1]));
		THROW_FAILED_HRESULT(pDB -> CorrectViewEntry (TargetView, g_cbScaleViewAMCode, lScaleMCode[2], CallBackData.m_lScaleMCode[2]));
		THROW_FAILED_HRESULT(pDB -> CorrectViewEntry (TargetView, g_cbScaleViewTMCode, lScaleMCode[3], CallBackData.m_lScaleMCode[3]));

	// AnsichtsEinträge enumerieren
		CallBackData.m_pDB = pDB;
		CallBackData.m_View = View;
		CallBackData.m_pTarget = &TargetView;

		if (S_OK == TargetView.EnumEntries (EnumViewEntryCallBack, (DWORD)&CallBackData)) {
		// jetzt noch diverse Properties übernehmen
		CViewPropHeader Hdr (pDB -> m_hPr);
		LONG lMasstab = Hdr.GetBMasstab (pcKey);	// Bezugsmasstab
		WTRiASPropertyBase PropBase (View);

			if (0 != lMasstab) 
				THROW_FAILED_HRESULT(SetPropertyBy (PropBase, g_cbViewBMasstab, lMasstab, true, LOCALE_ENGLISH));

		string str = Hdr.GetDescription (pcKey);	// BeschreibungsInfo

			if (str.size() > 0)
				THROW_FAILED_HRESULT(SetPropertyBy (PropBase, g_cbViewCaption, str.c_str(), true));

		// evtl. definierten AnsichtsAusschnitt übernehmen
		double dCont[4];

			if (SUCCEEDED(Hdr.GetContainer (pcKey, dCont))) {
			CCSRectangleGeometry Rect (dCont[0], dCont[2], dCont[1], dCont[3], 1);
			WDispatch dispRect (Rect);

				THROW_FAILED_HRESULT(SetPropertyBy (PropBase, g_cbSichtContMCode, (IDispatch *)dispRect, true));
			}

		// MerkmalsCode der Objektbezogenen Visualisierung umhängen
		char cbBuffer[_MAX_PATH];

			if (0 != CallBackData.m_lObjVisMCode) {
				_ASSERTE(0 != lObjVisMCode);
				wsprintf (cbBuffer, g_cbSysProperty, lObjVisMCode);
				THROW_FAILED_HRESULT(SetPropertyBy (PropBase, cbBuffer, CComVariant((long)CallBackData.m_lObjVisMCode, VT_I4), true));
			}

		// MerkmalsCode der LegendenInfo umhängen
			if (0 != CallBackData.m_lLegVisMCode) {
				_ASSERTE(0 != lLegVisMCode);
				wsprintf (cbBuffer, g_cbSysProperty, lLegVisMCode);
				THROW_FAILED_HRESULT(SetPropertyBy (PropBase, cbBuffer, CComVariant((long)CallBackData.m_lLegVisMCode, VT_I4), true));
			}

		// MerkmalsCodes der Maßstabsbereiche umhängen
			for (int i = 0; i < 4; i++) {
				if (0 != CallBackData.m_lScaleMCode[i]) {
					_ASSERTE(0 != lScaleMCode[i]);
					wsprintf (cbBuffer, g_cbSysProperty, lScaleMCode[i]);
					THROW_FAILED_HRESULT(SetPropertyBy (PropBase, cbBuffer, CComVariant((long)CallBackData.m_lScaleMCode[i], VT_I4), true));
				}
			}

		// nur dann zur Sammlung hinzufügen, wenn wenigsten ein Eintrag vorhanden ist
			THROW_FAILED_HRESULT(pData -> m_Views -> _Add(View, VARIANT_TRUE));
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert sämtliche Ansichten der Target-Datenbank im neuen Format
STDMETHODIMP CTRiASDatabaseBase::get_Views (ITRiASViews **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDatabaseBase::get_Views");

	COM_TRY {
	WTRiASViews Views (CLSID_TRiASViews);
	CEnumViewCallback CallBackData;
	CActDB ActDB (m_hPr);

	// die Ansichten gehören hier noch zur Database
		THROW_FAILED_HRESULT(Views -> put_Application(m_Application));
		THROW_FAILED_HRESULT(Views -> put_Parent(m_Parent));

		CallBackData.m_pDB = this;
		CallBackData.m_Views = Views;
		THROW_FAILED_HRESULT(CNativeView::EnumViews (m_hPr, EnumViewCallBack, (DWORD)&CallBackData));

		*pVal = Views.detach();

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert die Start-Ansichten der Target-Datenbank
STDMETHODIMP CTRiASDatabaseBase::get_StartViewName (BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDatabaseBase::get_Views");

	USES_CONVERSION;

// Ini-Namen erzeugen
os_path Name = os_string(OLE2A(m_bstrName));

	Name.extension (g_cbIni);

// ProfileString einlesen
char cbBuffer[MAXVIEWNAMELEN+3];

	GetPrivateProfileString (g_cbSights, g_cbStandard, g_cbNil, cbBuffer, MAXVIEWNAMELEN+3, (LPCSTR)Name);

// In Windows Zeichensatz konvertieren
	OemToChar (cbBuffer, cbBuffer);

// Ergebnis liefern
CComBSTR bstrName (cbBuffer);

	*pVal = bstrName.Detach();
	return bstrName.Length() > 0 ? S_OK : S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Callbackfunktion zur Enumeration aller Objektklassen (Identifikatoren)

HRESULT CALLBACK CTRiASDatabaseBase::EnumIdentCallBack (INT_PTR lIdent, DWORD dwTypes, UINT_PTR dwData)
{
	_ASSERTE(0L != dwData);
	COM_TRY {
	CEnumIdentEntryCallback *pData = reinterpret_cast<CEnumIdentEntryCallback *>(dwData);

		_ASSERTE(NULL != pData);

	// Objects-Collection erzeugen bzw. wiederverwenden
	WDispatch App;

		THROW_FAILED_HRESULT(pData -> m_pDB -> get_Application (App.ppi()));

	// Objekt evtl. aus der DatabaseMap holen bzw. neu erzeugen
	WTRiASObjects Objects;
	WTRiASObjectHandleMap Map (GetPropertyFrom (pData -> m_pDB -> GetDispatch(), g_cbObjectsMap, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab
	CInitializeSimpleObjects InitObjs(App, pData -> m_pDB -> GetDispatch(), (OBJECTTYPE)dwTypes);
	INT_PTR hObjs = NULL;

		THROW_FAILED_HRESULT(FindInMapOrCreateObjectEx(Map, lIdent, hObjs, Objects, CLSID_TRiASSimpleObjects, InitObjs));
		THROW_FAILED_HRESULT(pData -> m_Coll -> _Add (Objects, VARIANT_TRUE));	// zur Collection hinzufügen

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::get_ObjectsDefs (ITRiASObjectsCollection **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDatabaseBase::get_ObjectsDef");

// wenn die Collection bereits existiert, dann lediglich diese zurückliefern
	if (!!m_ObjectsDefs) {
		*pVal = m_ObjectsDefs;
		(*pVal) -> AddRef();
		return S_OK;
	}

// ansonsten neu erzeugen
	return EnsureObjectsDefs (pVal);
}

HRESULT CTRiASDatabaseBase::EnsureObjectsDefs (ITRiASObjectsCollection **pVal)
{
	_ASSERTE(!m_ObjectsDefs);

	COM_TRY {
	WTRiASObjectsCollection ObjsColl (CLSID_TRiASSimpleObjectsCollection);
	CEnumIdentEntryCallback CallBackData;

		THROW_FAILED_HRESULT(ObjsColl -> put_Application(m_Application));
		THROW_FAILED_HRESULT(ObjsColl -> put_Parent(GetDispatch()));

		CallBackData.m_pDB = this;
		CallBackData.m_Coll = ObjsColl;
		THROW_FAILED_HRESULT(CNativeIdent::EnumIdents (m_hPr, EnumIdentCallBack, reinterpret_cast<DWORD>(&CallBackData)));

		m_ObjectsDefs = ObjsColl;
		if (NULL != pVal)
			*pVal = ObjsColl.detach();
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::get_ObjectsDef(
	VARIANT vItem, VARIANT_BOOL fCreate, BSTR Type, ITRiASObjects **pIObjDef)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == pIObjDef) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDatabaseBase::get_ObjectsDef");

	if (!m_ObjectsDefs.IsValid())
	{
		RETURN_FAILED_HRESULT(EnsureObjectsDefs());
	}
	_ASSERTE(m_ObjectsDefs.IsValid());

HRESULT hr = m_ObjectsDefs -> Item (vItem, pIObjDef);

	if (TRIASDB_E_UNKNOWN_OBJECTS == hr && fCreate) {	// evtl. neu erzeugen
	CComVariant v;

		hr = v.ChangeType (VT_BSTR, &vItem);
		if (SUCCEEDED(hr)) {
		CIID ClsId (Type, CIID::INITCIID_InitFromProgId);

			if (!ClsId)	ClsId = CLSID_TRiASSimpleObjects;	// default ClsId

			hr = m_ObjectsDefs -> Add (V_BSTR(&v), CComBSTR(ClsId.ProgID().c_str()), pIObjDef);
			if (S_OK == hr) hr = S_FALSE;				// Objektmenge wurde neu erzeugt
		}
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Umschließenden Datenbank-Container liefern
STDMETHODIMP CTRiASDatabaseBase::get_Envelope (ENVELOPETYPE rgType, IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDatabaseBase::get_Container");

GUID *pGuids = NULL;

	COM_TRY {
	CActDB ActDB (m_hPr);
	long Cont[4];	// XMin, XMax, YMin, YMax
	ErrCode EC = EC_OKAY;
	
		switch (rgType) {
		case ENVELOPETYPE_AllGeometries:		// derzeit umschließendes Rechteck
			{
				EC = (ErrCode)dbcodb_ (m_hPr, Cont);
				if (WC_RETURN != EC)
					break;		// ok oder Fehler
//				EC = EC_OKAY;
			}
		// WC_RETURN: wenn keine Objekte da sind, dann hier durchfallen...

		default:
		case ENVELOPETYPE_MaxPossible:
			Cont[0] = 0;			// XMin
			Cont[1] = MAXKOORD;		// XMax
			Cont[2] = 0;			// YMin
			Cont[3] = MAXKOORD;		// YMax
			break;
		}

	// Rechteck skalieren und transformieren
		if (EC_OKAY != EC)  
			return HRESULT_FROM_ERRCODE(EC);	// Fehler beim Cont bestimmen

	// Koordinaten deskalieren
	CScaleHeader Hdr (m_hPr);
	double dXMin, dYMin, dXMax, dYMax;

		dXMin = Hdr.UnScaleX (Cont[0], Cont[2]);
		dYMin = Hdr.UnScaleY (Cont[0], Cont[2]);
		dXMax = Hdr.UnScaleX (Cont[1], Cont[3]);
		dYMax = Hdr.UnScaleY (Cont[1], Cont[3]);

	// CS-Transformator, Guid besorgen
	WTRiASCSTransform CST (GetPropertyFrom (GetDispatch(), g_cbTRiASCSTransform, (IDispatch *)NULL), false);
	long lCnt = 0;

		THROW_FAILED_HRESULT(::GetGeometryGuids(m_hPr, &lCnt, &pGuids));
		_ASSERTE(CST.IsValid());
		_ASSERTE(1 == lCnt);		// GeoDB's haben immer nur _ein_ Koordinatensystem

	// DBContainer setzen
	CCSRectangleGeometry Rect (dXMin, dYMin, dXMax, dYMax, 1);
	WDispatch dispRect(Rect);
	
		THROW_FAILED_HRESULT(WTRiASTransformGeometry(dispRect) -> Transform (*(CSID *)pGuids, CST));
		::CoTaskMemFree(pGuids);
		pGuids = NULL;		// doppeltes Freigeben verhindern

		*pVal = dispRect.detach();

	} COM_CATCH_OP(
		if (NULL != pGuids) ::CoTaskMemFree(pGuids);
	);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Anzahl der Objekte liefern
STDMETHODIMP CTRiASDatabaseBase::get_ObjectCount (long *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == m_hPr)
		return REPORT_DBERROR(TRIASDB_E_DATABASE_NOT_OPENED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDatabaseBase::get_ObjectCount");

	COM_TRY {
	CActDB ActDB (m_hPr);
	short iFNr = (VERSION0500000E <= ::GetDBVersion(m_hPr)) ? OBL_NEW : OBL_OLD;

		*pVal = ladr_ (m_hPr, &iFNr, false);

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Recherchefunktionalität
STDMETHODIMP CTRiASDatabaseBase::ConsiderSearch(BSTR bstrCommand, SAFEARRAY *pParams)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASDatabaseBase::SearchObjects(BSTR bstrCommand, ITRiASObjects *pIObjs, SAFEARRAY *pParams)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pIObjs)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDatabaseBase::SearchObjects");

// 1. betroffene Objekteigenschaft finden
WTRiASFeature Feat;
HRESULT hr = GetSearchFeature (pParams, Feat.ppi());

	if (FAILED(hr)) {
		if (hr == TRIASDB_E_REQUESTED_OBJECT_NOT_LOADED)
			return TRIASDB_E_REQUESTED_OBJECT_NOT_LOADED;		// darf fehlschlagen
		RETURN_FAILED_HRESULT(hr);		// alles andere ist suspekt
	} else if (S_FALSE == hr)
		return S_FALSE;					// Feature gehört nicht zu dieser Datenquelle

// alles ok, Objekteigenschaft zuerst versuchen, global zu behandeln
WTRiASSearchObjects ToSearch;

	if (SUCCEEDED(Feat.QueryInterface(ToSearch)) &&
		S_OK == ToSearch -> ConsiderSearch (bstrCommand, pParams)) 
	{
	// gesuchte Objektmenge erzeugen
		hr = ToSearch -> SearchObjects (bstrCommand, pIObjs, pParams);
	} 
	else {
	// die Objekteigenschaft unterstützt diese Recherche nicht, jede Objektklasse einzeln testen
		if (FAILED(m_ObjectsDefs.QueryInterface(ToSearch)))
			return TRIASDB_S_SEARCH_NOT_SUPPORTED;

		hr = ToSearch -> ConsiderSearch (bstrCommand, pParams);
		if (S_OK != hr) return hr;
			
		hr = ToSearch -> SearchObjects (bstrCommand, pIObjs, pParams);
	}
	return hr;
}

STDMETHODIMP CTRiASDatabaseBase::ConstraintObjects(ITRiASObjects *pIObjs)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// Eine bestimmte Objekteigenschaft liefern
HRESULT CTRiASDatabaseBase::GetSearchFeature (SAFEARRAY *pParams, ITRiASFeature **ppIFeat)
{
	_ASSERTE(NULL != ppIFeat);
	*ppIFeat = NULL;

	COM_TRY {
	// Objekteigenschaft aus Parameterfeld herauslösen
	CSafeArray sa(VT_VARIANT);

		if (NULL == pParams || !sa.Attach (pParams, true)) 
			return E_INVALIDARG;

	CSafeArrayLock<VARIANT> lock(sa);

	WTRiASFeature Feat;
	CComVariant v;

		_ASSERTE(lock.Size() >= 2);		// mindestens 2 Elemente müssen gegeben sein
		if (VT_DISPATCH == V_VT(&lock[1])) {
		// Objekteigenschaft ist direkt gegeben
			Feat = WTRiASFeature (V_DISPATCH(&lock[1]));

		} 
		else if (VT_BSTR != V_VT(&lock[1]) && SUCCEEDED(v.ChangeType (VT_I4, &lock[1]))) {
		// Handle gegeben, über globale Map wiederfinden 
		HRESULT hr = g_pDBEngine -> GetFeaturesObject ((HFEATURE)V_I4(&v), Feat.ppu());

			if(FAILED(hr))
				return hr;		// evtl.existiert Objekteigenschaft mit diesem MCode noch nicht
		} 
		else if (SUCCEEDED(v.ChangeType (VT_BSTR, &lock[1]))) {
		// Name der Objekteigenschaft ist gegeben
		// In TRiAS Datenbanken haben alle Objektklassen identische Objekteigenschaften,
		// daher kann die erstbeste Objektklasse nach dem Feature-Objekt gefragt werden
		WTRiASObjects Objs;

			if (!m_ObjectsDefs)
			{
				THROW_FAILED_HRESULT(EnsureObjectsDefs());
			}
			_ASSERTE(m_ObjectsDefs.IsValid());

		HRESULT hr = m_ObjectsDefs -> Item (CComVariant(1), Objs.ppi());

			if (FAILED(hr)) {
				if (TRIASDB_E_INVALID_PARAMETER != hr)
					THROW_FAILED_HRESULT(hr);
				return S_FALSE;		// 'leere' Datenquelle, also nichts gefunden
			}

			if (FAILED(Objs -> get_Feature (v, VARIANT_FALSE, g_bstrNil, Feat.ppi())))
			{
				THROW_FAILED_HRESULT(Objs -> get_GeometryFeature (v, VARIANT_FALSE, g_bstrNil, Feat.ppi()));
			}
		}

	// Noch abtesten, ob gefundene Feature zu dieser Datenquelle gehört
	HPROJECT hPrFeat = NULL;

		THROW_FAILED_HRESULT(RetrieveDBHandle (Feat, &hPrFeat));
		if (hPrFeat != m_hPr) return S_FALSE;		// nicht von dieser Welt

	// Feature liefern
		*ppIFeat = Feat.detach();

	} COM_CATCH;
	return S_OK;
}

// Implementation of get_AttachedCS
STDMETHODIMP CTRiASDatabaseBase::get_AttachedCS(BSTR bstrDbName, BSTR *pbstrAssocCS)
{
	return E_NOTIMPL;
}

// Implementation of get_ConnectFilter
STDMETHODIMP CTRiASDatabaseBase::get_ConnectionFilter(ITRiASConnectionFilter **ppIFilter)
{
	if (NULL == ppIFilter)
		return E_POINTER;
	*ppIFilter = NULL;

	COM_TRY {
	WTRiASConnectionFilter ConnectFilter (m_ConnectFilter);

		*ppIFilter = ConnectFilter.detach();
	
	} COM_CATCH;
	return S_OK;
}

// Implementation of put_ConnectFilter
STDMETHODIMP CTRiASDatabaseBase::put_ConnectionFilter(ITRiASConnectionFilter *pIFilter)
{
	COM_TRY {
		if (NULL == pIFilter) {
			THROW_FAILED_HRESULT(::ResetConnectFilter(m_hPr)); 
		}
		else {
		WDispatch GeomFilt;
		CONNECTIONFILTERTYPE rgType = CONNECTIONFILTERTYPE_Rectangle_OverlappedContainers;

			THROW_FAILED_HRESULT(pIFilter -> get_Geometry(GeomFilt.ppi()));
			THROW_FAILED_HRESULT(pIFilter -> get_Type(&rgType));

		// an der Datenquelle selbst setzen
		CONNECTFILTER ConnFilt;
		CScaleHeader Hdr (m_hPr);

		// Koordinatensystem 
		WTRiASPropertyBase Props (GetUnknown());
		WTRiASCSTransform CST (GetPropertyFrom (Props, g_cbTRiASCSTransform, (IDispatch *)NULL), false);
		_GUID GeomGuid;

			THROW_FAILED_HRESULT(::GetGeometryGuid (m_hPr, INVALID_HOBJECTS, "Geometry", &GeomGuid));

		auto_ptr<double> pX;
		auto_ptr<double> pY;

			switch(rgType) {
			case CONNECTIONFILTERTYPE_Rectangle_OverlappedContainers:
			case CONNECTIONFILTERTYPE_Rectangle_ContainedContainers:
			case CONNECTIONFILTERTYPE_Rectangle_OverlappedPoints:
			case CONNECTIONFILTERTYPE_Rectangle_ContainedPoints:
			case CONNECTIONFILTERTYPE_Rectangle_OverlappedObjects:
			case CONNECTIONFILTERTYPE_Rectangle_ContainedObjects:
				{
				// Rechtecke
				WTRiASSimpleRectangle Rect;
				WTRiASCSGeometryProperties GeomProps (GeomFilt);
				double dXMin, dYMin, dXMax, dYMax;

					THROW_FAILED_HRESULT(GeomProps->get_Envelope(Rect.ppi()));

				// ins Koordinatensystem der Datenquelle umsetzen
					THROW_FAILED_HRESULT(WTRiASTransformGeometry(Rect) -> TransformInverse (*(CSID *)&GeomGuid, CST));
					THROW_FAILED_HRESULT(Rect->GetRect(&dXMin, &dYMin, &dXMax, &dYMax));

					pX = auto_ptr<double>(ConnFilt.m_pX = new double[2]);
					pY = auto_ptr<double>(ConnFilt.m_pY = new double[2]);
					ConnFilt.m_lCnt = 2;

					ConnFilt.m_pX[0] = Hdr.ScaleX (dXMin, dYMin);
					ConnFilt.m_pY[0] = Hdr.ScaleY (dXMin, dYMin);
					ConnFilt.m_pX[1] = Hdr.ScaleX (dXMax, dYMax);
					ConnFilt.m_pY[1] = Hdr.ScaleY (dXMax, dYMax);
				}
				break;

			case CONNECTIONFILTERTYPE_Polygon_OverlappedContainers:
			case CONNECTIONFILTERTYPE_Polygon_ContainedContainers:
			case CONNECTIONFILTERTYPE_Polygon_OverlappedPoints:
			case CONNECTIONFILTERTYPE_Polygon_ContainedPoints:
			case CONNECTIONFILTERTYPE_Polygon_OverlappedObjects:
			case CONNECTIONFILTERTYPE_Polygon_ContainedObjects:
				{
				// Polygone
				WTRiASCSGeometryProperties GeomProps (GeomFilt);
				GEOMETRYTYPE rgGeoType = GEOMETRYTYPE_Unknown;

					THROW_FAILED_HRESULT(GeomProps->get_Type(&rgGeoType));
					if (GEOMETRYTYPE_Area != rgGeoType)
						_com_issue_error(E_INVALIDARG);		// muß eine Fläche sein

				WDispatch ClonedGeom;
				W_DGMPoints Pts;
				long lCount = 0;

					THROW_FAILED_HRESULT(GeomProps->Clone(ClonedGeom.ppi()));
					THROW_FAILED_HRESULT(WTRiASTransformGeometry(ClonedGeom) -> 
						TransformInverse (*(CSID *)&GeomGuid, CST));
					THROW_FAILED_HRESULT(W_DGMPolygonGeometry(ClonedGeom) ->
						get_Points(Pts.ppi()));
					THROW_FAILED_HRESULT(Pts -> get_Count(&lCount));	// Anzahl der Punkte holen

				auto_ptr<CSCOORD> pCoords (new CSCOORD[lCount]);

					THROW_FAILED_HRESULT(WTRiASSimplePoints(Pts) -> GetPoints (1, 
						lCount, (double *)pCoords.get()));	// direkt von den Points die Koordinaten abrufen

					pX = auto_ptr<double>(ConnFilt.m_pX = new double[lCount]);
					pY = auto_ptr<double>(ConnFilt.m_pY = new double[lCount]);
					ConnFilt.m_lCnt = lCount;

					for (long i = 0; i < lCount; ++i) {
					CSCOORD &rCoord = pCoords.get()[i];

						ConnFilt.m_pX[i] = Hdr.ScaleX (rCoord.X, rCoord.Y);
						ConnFilt.m_pY[i] = Hdr.ScaleY (rCoord.X, rCoord.Y);
					}
				}
				break;

			default:
				_ASSERTE((FALSE, "Wrong CF_... constant"));
				break;
			}

		// SetConnectFilter übernimmt die double-Felder
			ConnFilt.m_iMode = rgType;
			THROW_FAILED_HRESULT(::ResetConnectFilter(m_hPr)); 
			THROW_FAILED_HRESULT(::SetConnectFilter(m_hPr, &ConnFilt));

		// Speicher wird jetzt von der Datenbank gehalten
			pX.release();
			pY.release();
		}

	// ConnectFilter lokal speichern
		m_ConnectFilter = pIFilter;

	} COM_CATCH;
	return S_OK;
}

