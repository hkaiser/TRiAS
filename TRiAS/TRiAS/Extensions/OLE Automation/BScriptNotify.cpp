// IDispatch wrapper class(es) for CTRiASNotificationSinkBScript

#include "precomp.hxx"		// Alle Header auf einen Blick

#include <dirisole.h>
#include <bscrguid.h>

#include "Strings.h"
#include "BScriptNotify.h"
#include "obj.hxx"		// CGeoObject

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface2(DDocument, IID_DDocument)
DefineSmartInterface2(DView, IID_DView)
DefineSmartInterface2(DGeoObject, IID_DGeoObject)
DefineSmartInterface2(DGeoFeature, IID_DGeoFeature)
DefineSmartInterface2(DGeoObjectWin, IID_DGeoObjectWin)

/////////////////////////////////////////////////////////////////////////////
// Initialisierung
HRESULT CTRiASNotificationSinkBScript::FInit (CTriasApp *pApp, IExtendBScript *pIScript)
{
	if (NULL == pIScript || NULL == pApp) 
		return E_POINTER;

	m_Sink = pIScript;
	m_pApp = pApp;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASNotificationSinkBScript operations
HRESULT CTRiASNotificationSinkBScript::ServerEvent(SERVEREVT se)
{
// Strukturen für Rückkehrwert/Parameter (höchstens ein Parameter)
ebPARAM Pars[2];
LPVOID cbParam[2];
BSPARAM bs = { Pars, cbParam };

	switch (se) {
    case SERVEREVT_ClosingServer:
	// Function OnClosingServer() As Boolean
		{
		ebINT iRet = false;
		
			Pars[0].wType = TYP_BOOLEAN;	// Funktion liefern BOOL
			Pars[0].szExtType[0] = '\0';
			cbParam[0] = &iRet;

		HRESULT hr = m_Sink -> FireEvent ("OnClosingServer", 0, &bs);

			if (SUCCEEDED(hr) && iRet)
				return S_FALSE;		// nicht schließen
		}
		break;

    case SERVEREVT_ServerToClose:		// das letzte vom Tage
	// Sub OnServerToClose()
		{
			Pars[0].wType = 0;				// SubRoutine
			Pars[0].szExtType[0] = '\0';
			cbParam[0] = NULL;

			m_Sink -> FireEvent ("OnServerToClose", 0, &bs);
		}
		break;

    case SERVEREVT_InitializedServer:	// das erste vom Tage
    case SERVEREVT_ExtensionsLoaded:
	// diese hier kommen zu zeitig, um irgend etwas auszulösen
		break;

    case SERVEREVT_ShowToolTips:
    case SERVEREVT_ShowNoMoreToolTips:
	// Sub OnShowTooltips (fShow As Boolean)
		{
		ebINT fTT = (se == SERVEREVT_ShowToolTips) ? true : false;

			Pars[0].wType = 0;				// SubRoutine
			Pars[0].szExtType[0] = '\0';
			cbParam[0] = NULL;

			Pars[1].wType = TYP_BOOLEAN;
			Pars[1].szExtType[0] = '\0';
			cbParam[1] = &fTT;

			m_Sink -> FireEvent ("OnShowTooltips", 1, &bs);
		}
		break;

	default:
		ASSERT(false);
		break;
	}
	return S_OK;
}

HRESULT CTRiASNotificationSinkBScript::FireProjectEvent (
	HPROJECT hPr, LPCSTR pcRoutine, int iCnt, BSPARAM *pPar)
{
// GeoDocument wiederfinden
WDDocument Doc;
CGeoDoc *pDoc = m_pApp -> FGetGeoDocument (hPr, Doc.ppi());
DDocument *pIDoc = (DDocument *)Doc;

	if (NULL == pDoc) {
		_ASSERTE(NULL == pIDoc);
		return E_INVALIDARG;
	}

	pPar->pTypes[1].wType = TYP_APPOBJECT;
	strcpy (pPar->pTypes[1].szExtType, g_cbGeoDocument);
	pPar->pValues[1] = &pIDoc;

	return m_Sink -> FireEvent (pcRoutine, iCnt, pPar);
}

HRESULT CTRiASNotificationSinkBScript::ProjectEvent(
			long hPr, PROJECTEVT pe, VARIANT vProj)
{
	USES_CONVERSION;

// Strukturen für Parameter/Rückkehrwert (höchstens zwei Parameter)
ebPARAM Pars[3];
LPVOID cbParam[3];
BSPARAM bs = { Pars, cbParam };
HRESULT hr = S_OK;

	Pars[0].wType = 0;				// SubRoutine
	Pars[0].szExtType[0] = '\0';
	cbParam[0] = NULL;

// Event auslösen		
	switch (pe) {
	case PROJECTEVT_ProjectOpened:
	// Sub OnDocumentOpened (Doc As GeoDocument)
		FireProjectEvent ((HPROJECT)hPr, TEXT("OnDocumentOpened"), 1, &bs);
		break;
		
	case PROJECTEVT_ClosingProject:
	// Function OnClosingDocument (Doc As GeoDocument) As Boolean
		{
		ebINT iRet = false;
		
			Pars[0].wType = TYP_BOOLEAN;		// Funktion liefern BOOL
			Pars[0].szExtType[0] = '\0';
			cbParam[0] = &iRet;

			hr = FireProjectEvent ((HPROJECT)hPr, TEXT("OnClosingDocument"), 1, &bs);
			if (SUCCEEDED(hr) && iRet) 
				return S_FALSE;		// nicht schließen

		// wenn Callback nicht existiert, dann wird S_FALSE geliefert
			if (S_FALSE == hr)
				hr = S_OK;
		}		
		break;
		
	case PROJECTEVT_ProjectClosed:
	// Sub OnDocumentClosed()
		m_Sink -> FireEvent (TEXT("OnDocumentClosed"), 0, &bs);
		break;

    case PROJECTEVT_ProjectIsDirty:
    case PROJECTEVT_ProjectIsNotDirty:
	// Sub OnSetDocumentDirty (Doc As GeoDocument, fDirty As Boolean)
		{
		ebINT fDirty = (PROJECTEVT_ProjectIsNotDirty == pe) ? false : true;

			Pars[2].wType = TYP_BOOLEAN;
			Pars[2].szExtType[0] = '\0';
			cbParam[2] = &fDirty;
			FireProjectEvent ((HPROJECT)hPr, TEXT("OnSetDocumentDirty"), 2, &bs);
		}
		break;

    case PROJECTEVT_ProjectToClose:
	// Sub OnDocumentToClose (Doc As GeoDocument)
		FireProjectEvent ((HPROJECT)hPr, TEXT("OnDocumentToClose"), 1, &bs);
		break;

    case PROJECTEVT_ChangedCoordFormat:
	// Sub OnChangedCoordFormat()
		m_Sink -> FireEvent (TEXT("OnChangedCoordFormat"), 0, &bs);
		break;

    case PROJECTEVT_ReReadHeader:
	// Sub OnChangedHeader (Doc As GeoDocument, Str As String)
		{
			Pars[2].wType = TYP_STRING;
			Pars[2].szExtType[0] = '\0';
			cbParam[2] = (VT_BSTR == vProj.vt) ? OLE2A(V_BSTR(&vProj)) : NULL;
			FireProjectEvent ((HPROJECT)hPr, TEXT("OnChangedHeader"), 2, &bs);
		}
		break;

	case PROJECTEVT_RenamingFile:
	case PROJECTEVT_FileRenamed:
	// werden diese als Notification in Basic gebraucht ?
		break;

	case PROJECTEVT_ObjectSplitted:		// Objekt wurde geteilt
	// Sub OnObjectSplitted (ObjOrig As GeoObject, ObjNew1 As GeoObject, ObjNew2 As GeoObject)
		break;

	default:
		ASSERT(false);
		break;
	}
	return hr;		// weiterleiten
}

HRESULT CTRiASNotificationSinkBScript::FireViewEvent (
	HPROJECT hPr, LPCSTR pcView, LPCSTR pcRoutine, BSPARAM *pPar, bool fCreate)
{
// GeoDocument wiederfinden
CGeoDoc *pDoc = m_pApp -> FGetGeoDocument(hPr);

	if (NULL == pDoc) return E_INVALIDARG;

WDView View;
HRESULT hr = pDoc -> FGetGeoView (pcView, fCreate, View.ppi());
DView *pIView = (DView *)View;

	if (FAILED(hr))	{
		_ASSERTE(NULL == pIView);
		return hr;
	}

	pPar->pTypes[1].wType = TYP_APPOBJECT;
	strcpy (pPar->pTypes[1].szExtType, g_cbGeoView);
	pPar->pValues[1] = &pIView;

	return m_Sink -> FireEvent (pcRoutine, 1, pPar);
}

HRESULT CTRiASNotificationSinkBScript::FireViewEventName (
	HPROJECT hPr, LPCSTR pcView, LPCSTR pcRoutine, BSPARAM *pPar)
{
	ASSERT(NULL != pcView);

// GeoDocument wiederfinden
WDDocument Doc;
CGeoDoc *pDoc = m_pApp -> FGetGeoDocument (hPr, Doc.ppi());
DDocument *pIDoc = (DDocument *)Doc;

	if (NULL == pDoc) {
		_ASSERTE(NULL == pIDoc);
		return E_INVALIDARG;
	}

	pPar->pTypes[1].wType = TYP_APPOBJECT;
	strcpy (pPar->pTypes[1].szExtType, g_cbGeoDocument);
	pPar->pValues[1] = &pIDoc;

	pPar->pTypes[2].wType = TYP_STRING;
	pPar->pTypes[2].szExtType[0] = '\0';
	pPar->pValues[2] = (void *)pcView;

	return m_Sink -> FireEvent (pcRoutine, 2, pPar);
}

HRESULT CTRiASNotificationSinkBScript::GeoViewEvent(long hPr, GEOVIEWEVT ve, VARIANT vData)
{
	USES_CONVERSION;

// Strukturen für Parameter/Rückkehrwert (höchstens zwei Parameter)
ebPARAM Pars[3];
LPVOID cbParam[3];
BSPARAM bs = { Pars, cbParam };
HRESULT hr = S_OK;

	Pars[0].wType = 0;				// SubRoutine
	Pars[0].szExtType[0] = '\0';
	cbParam[0] = NULL;

// Event auslösen		
	switch (ve) {
    case GEOVIEWEVT_SelectingView:
	// Function OnSelectingView (View As GeoView) As Boolean
		{
			if (VT_BSTR != vData.vt) return E_INVALIDARG;

		ebINT iRet = false;
		
			Pars[0].wType = TYP_BOOLEAN;		// Funktion liefern BOOL
			Pars[0].szExtType[0] = '\0';
			cbParam[0] = &iRet;

			hr = FireViewEvent ((HPROJECT)hPr, OLE2A(V_BSTR(&vData)), TEXT("OnSelectingView"), &bs);
			if (SUCCEEDED(hr) && iRet) 
				return S_FALSE;		// nicht schließen
		}		
		break;

    case GEOVIEWEVT_ViewSelected:
	// Sub OnViewSelected (View As GeoView)
		if (VT_BSTR != vData.vt)
			return E_INVALIDARG;
		FireViewEvent ((HPROJECT)hPr, OLE2A(V_BSTR(&vData)), TEXT("OnViewSelected"), &bs);
		break;

    case GEOVIEWEVT_DeletingView:
	// Function OnDeletingView (View As GeoView) As Boolean
		{
			if (VT_BSTR != vData.vt) return E_INVALIDARG;

		ebINT iRet = false;
		
			Pars[0].wType = TYP_BOOLEAN;		// Funktion liefern BOOL
			Pars[0].szExtType[0] = '\0';
			cbParam[0] = &iRet;

			hr = FireViewEvent ((HPROJECT)hPr, OLE2A(V_BSTR(&vData)), TEXT("OnDeletingView"), &bs);
			if (SUCCEEDED(hr) && iRet) 
				return S_FALSE;		// nicht schließen
		}		
		break;

    case GEOVIEWEVT_ViewDeleted:
	// Sub OnViewDeleted (Doc As GeoDocument, DeletedViewName As String)
		if (VT_BSTR != vData.vt)
			return E_INVALIDARG;
		FireViewEventName ((HPROJECT)hPr, OLE2A(V_BSTR(&vData)), TEXT("OnViewDeleted"), &bs);
		break;

    case GEOVIEWEVT_ViewCreated:
	// Sub OnViewCreated (View As GeoView)
		if (VT_BSTR != vData.vt)
			return E_INVALIDARG;
		FireViewEvent ((HPROJECT)hPr, OLE2A(V_BSTR(&vData)), TEXT("OnViewCreated"), &bs);
		break;

    case GEOVIEWEVT_ZoomChanged:
	// Sub OnZoomChanged (NewZoom As Long)
		{
			if (VT_I4 != vData.vt) 
				return E_INVALIDARG;

			Pars[1].wType = TYP_LONG;
			Pars[1].szExtType[0] = '\0';
			cbParam[1] = & V_I4(&vData);

			m_Sink -> FireEvent (TEXT("OnZoomChanged"), 1, &bs);
		}
		break;

    case GEOVIEWEVT_PaintingView:
	// Sub OnPaintingView()
		m_Sink -> FireEvent (TEXT("OnPaintingView"), 0, &bs);
		break;

    case GEOVIEWEVT_ViewPainted:
	// Sub OnViewPainted()
		m_Sink -> FireEvent (TEXT("OnViewPainted"), 0, &bs);
		break;

    case GEOVIEWEVT_ScrollingHorz:
		m_Sink -> FireEvent (TEXT("OnScrollingHorz"), 0, &bs);
		break;

    case GEOVIEWEVT_ScrollingVert:
		m_Sink -> FireEvent (TEXT("OnScrollingVert"), 0, &bs);
		break;

	case GEOVIEWEVT_ReReadAll:
		break;

	default:
		ASSERT(false);
		break;
	}

return S_OK;
}

HRESULT CTRiASNotificationSinkBScript::GeoClassEvent(long hPr, GEOCLASSEVT ce, long ulIdent)
{
	switch (ce) {
    case GEOCLASSEVT_DrawingClass:
		break;

    case GEOCLASSEVT_ClassChanged:
		break;

    case GEOCLASSEVT_ClassesChanged:
		break;

    case GEOCLASSEVT_DeletingClass:
		break;

    case GEOCLASSEVT_ClassDeleted:
		break;

	default:
		ASSERT(false);
		break;
	}

return S_OK;
}

HRESULT CTRiASNotificationSinkBScript::FireObjectEvent (
	HPROJECT hPr, LONG lONr, LPCSTR pcRoutine, BSPARAM *pPar)
{
// GeoDocument wiederfinden
CGeoDoc *pDoc = m_pApp -> FGetGeoDocument(hPr);

	if (NULL == pDoc) return E_INVALIDARG;

HRESULT hr = S_OK;

	if (0L != lONr) {
	// zuerst Entrypoint abprüfen
		pPar->pTypes[1].wType = TYP_APPOBJECT;
		strcpy (pPar->pTypes[1].szExtType, g_cbGeoObject);
		pPar->pValues[1] = NULL;
		if (S_OK != m_Sink -> EntryExists (pcRoutine, 1, pPar))
			return S_OK;

	// jetzt wirklich rufen
	WDGeoObject Obj;

		hr = pDoc -> FGetGeoObject (lONr, Obj.ppi());
		if (FAILED(hr))	{
			_ASSERTE(SUCCEEDED(hr));
			return hr;
		}

	DGeoObject *pIObj = (DGeoObject *)Obj;

		pPar->pValues[1] = &pIObj;
		hr = m_Sink -> FireEvent (pcRoutine, 1, pPar);
	} 
	else 
		hr = m_Sink -> FireEvent (pcRoutine, 0, pPar);

	return hr;
}

HRESULT CTRiASNotificationSinkBScript::GeoObjectEvent(
	long hPr, GEOOBJECTEVT oe, long lONr)
{
// Strukturen für Parameter/Rückkehrwert (höchstens ein Parameter)
ebPARAM Pars[2];
LPVOID cbParam[2];
BSPARAM bs = { Pars, cbParam };
HRESULT hr = S_OK;

	Pars[0].wType = 0;				// SubRoutine
	Pars[0].szExtType[0] = '\0';
	cbParam[0] = NULL;

// Event auslösen		
	switch (oe) {
    case GEOOBJECTEVT_DrawingObject:
		break;

    case GEOOBJECTEVT_InquiringObject:
	// Function OnInquiringObjectInfo (Obj As GeoObject) As String
		break;

    case GEOOBJECTEVT_ObjectSelected:
	// Sub OnObjectSelected (Obj As GeoObject)
		if (INVALID_ONR == lONr) 
			return E_INVALIDARG;
		FireObjectEvent ((HPROJECT)hPr, lONr, TEXT("OnObjectSelected"), &bs);
		break;

    case GEOOBJECTEVT_ObjectUnSelected:
	// Sub OnObjectUnSelected (Obj As GeoObject)
		if (INVALID_ONR == lONr) 
			return E_INVALIDARG;
		FireObjectEvent ((HPROJECT)hPr, lONr, TEXT("OnObjectUnSelected"), &bs);
		break;

    case GEOOBJECTEVT_DeletingObject:
	// Function OnDeletingObject (Obj As GeoObject) As Boolean
		{
			if (INVALID_ONR == lONr) 
				return E_INVALIDARG;

		ebINT iRet = false;
		
			Pars[0].wType = TYP_BOOLEAN;		// Funktion liefern BOOL
			Pars[0].szExtType[0] = '\0';
			cbParam[0] = &iRet;

			hr = FireObjectEvent ((HPROJECT)hPr, lONr, TEXT("OnDeletingObject"), &bs);
			if (SUCCEEDED(hr) && iRet) 
				return S_FALSE;		// nicht löschen
		}
		break;

	case GEOOBJECTEVT_ObjectToDelete:
	// Sub OnObjectToDelete (Obj As GeoObject)
		if (INVALID_ONR == lONr) 
			return E_INVALIDARG;
		FireObjectEvent ((HPROJECT)hPr, lONr, TEXT("OnObjectToDelete"), &bs);
		break;

	case GEOOBJECTEVT_ObjectCreated:
	// Sub OnObjectCreated (Obj As GeoObject)
		if (INVALID_ONR == lONr) 
			return E_INVALIDARG;
		FireObjectEvent ((HPROJECT)hPr, lONr, TEXT("OnObjectCreated"), &bs);
		break;

	case GEOOBJECTEVT_ObjectAdded:
	// Sub OnObjectAdded (Obj As GeoObject)
		if (INVALID_ONR == lONr) 
			return E_INVALIDARG;
		FireObjectEvent ((HPROJECT)hPr, lONr, TEXT("OnObjectAdded"), &bs);
		break;

    case GEOOBJECTEVT_ObjectDeleted:
		FireObjectEvent ((HPROJECT)hPr, 0L, TEXT("OnObjectDeleted"), &bs);
		break;

	case GEOOBJECTEVT_ObjectActivated:
	// Sub OnObjectActivated (Obj As GeoObject)
		if (INVALID_ONR == lONr) 
			return E_INVALIDARG;
		FireObjectEvent ((HPROJECT)hPr, lONr, TEXT("OnObjectActivated"), &bs);
		break;

	case GEOOBJECTEVT_ObjectDeActivated:
	// Sub OnObjectDeActivated (Obj As GeoObject)
		if (INVALID_ONR == lONr) 
			return E_INVALIDARG;
		FireObjectEvent ((HPROJECT)hPr, lONr, TEXT("OnObjectDeActivated"), &bs);
		break;

    case GEOOBJECTEVT_ChangingGeometry:
	// Function OnChangingGeometry (Obj As GeoObject) As Boolean
		{
			if (INVALID_ONR == lONr) 
				return E_INVALIDARG;

		ebINT iRet = false;
		
			Pars[0].wType = TYP_BOOLEAN;		// Funktion liefern BOOL
			Pars[0].szExtType[0] = '\0';
			cbParam[0] = &iRet;

			hr = FireObjectEvent ((HPROJECT)hPr, lONr, TEXT("OnChangingGeometry"), &bs);
			if (SUCCEEDED(hr) && iRet) 
				return S_FALSE;		// nicht löschen
		}
		break;

	case GEOOBJECTEVT_GeometryChanged:
	// Sub OnGeometryChanged (Obj As GeoObject)
		if (INVALID_ONR == lONr) 
			return E_INVALIDARG;
		FireObjectEvent ((HPROJECT)hPr, lONr, TEXT("OnGeometryChanged"), &bs);
		break;

	case GEOOBJECTEVT_ObjectToClassify:
	case GEOOBJECTEVT_ObjectClassified:
	case GEOOBJECTEVT_AddingObject:
	case GEOOBJECTEVT_ObjectToAdd:
		break;

	default:
		ASSERT(false);
		break;
	}

	return S_OK;
}

#if _TRiAS_VER >= 0x0300
HRESULT CTRiASNotificationSinkBScript::FireFeatureEvent (
	HPROJECT hPr, LONG lONr, LPCSTR pcObjProp, LPCSTR pcRoutine, BSPARAM *pPar)
{
// zuerst Existenz des Entrypoints absichern
	pPar->pTypes[1].wType = TYP_APPOBJECT;
	strcpy (pPar->pTypes[1].szExtType, g_cbGeoObject);
	pPar->pValues[1] = NULL;

	pPar->pTypes[2].wType = TYP_APPOBJECT;
	strcpy (pPar->pTypes[2].szExtType, g_cbGeoFeature);
	pPar->pValues[2] = NULL;
	if (S_OK != m_Sink -> EntryExists (pcRoutine, 2, pPar))
		return S_OK;	// dieser Entrypoint existiert nicht

// jetzt alles machen, was wirklich Zeit kostet ...
// GeoDocument wiederfinden
CGeoDoc *pDoc = m_pApp -> FGetGeoDocument(hPr);

	if (NULL == pDoc) 
		return E_INVALIDARG;

WDGeoObject Obj;
CGeoObject *pObj = pDoc -> FGetObjectDisp (lONr, Obj.ppi());
DGeoObject *pIObj = (DGeoObject *)Obj;

	if (NULL == pObj) 
		return E_UNEXPECTED;

	pPar->pValues[1] = &pIObj;

WDGeoFeature Feat;
CGeoFeatureBase *pFeat = pObj -> FGetFeatureDisp (pcObjProp, Feat.ppi());
DGeoFeature *pIFeat = (DGeoFeature *)Feat;

	if (NULL == pFeat) 
		return E_INVALIDARG;

	pPar->pValues[2] = &pIFeat;

	return m_Sink -> FireEvent (pcRoutine, 2, pPar);
}
#endif // _TRiAS_VER >= 0x0300

HRESULT CTRiASNotificationSinkBScript::GeoFeatureEvent(long hPr, GEOFEATUREEVT fe, LPARAM lParam)
{
#if _TRiAS_VER >= 0x0300
// Strukturen für Parameter/Rückkehrwert (höchstens zwei Parameter)
ebPARAM Pars[3];
LPVOID cbParam[3];
BSPARAM bs = { Pars, cbParam };
HRESULT hr = S_OK;

	Pars[0].wType = 0;				// SubRoutine
	Pars[0].szExtType[0] = '\0';
	cbParam[0] = NULL;

	switch (fe) {
	case GEOFEATUREEVT_FeatureChanged:
	// Sub OnFeatureChanged (Obj As GeoObject, Feat As GeoFeature)
		{
		FEATUREMODIFIED *pFM = (FEATUREMODIFIED *)lParam;

			if (INVALID_ONR == pFM -> lONr || NULL == pFM -> pcName) 
				return E_INVALIDARG;
			FireFeatureEvent ((HPROJECT)hPr, pFM -> lONr, pFM -> pcName, TEXT("OnFeatureChanged"), &bs);
		}
		break;

    case GEOFEATUREEVT_FeaturesChanged:
		break;

	default:
		ASSERT(false);
		break;
	}
#endif // _TRiAS_VER >= 0x0300

	return S_OK;
}

HRESULT CTRiASNotificationSinkBScript::GeoRelationEvent(long hPr, GEORELATIONEVT re, long ulRCode)
{
	switch (re) {
	case GEORELATIONEVT_RelationChanged:
		break;

    case GEORELATIONEVT_RelationsChanged:
		break;

	default:
		ASSERT(false);
		break;
	}
	return S_OK;
}

HRESULT CTRiASNotificationSinkBScript::FireWindowEvent (
	HWND hWnd, LPCSTR pcRoutine, BSPARAM *pPar)
{
// zuerst Existenz des Entrypoints testen
	pPar->pTypes[1].wType = TYP_APPOBJECT;
	strcpy (pPar->pTypes[1].szExtType, g_cbGeoObjectWin);
	pPar->pValues[1] = NULL;
	if (S_OK != m_Sink ->EntryExists (pcRoutine, 1, pPar))
		return S_OK;		// Entrypoint existiert hier nicht

// GeoDocument wiederfinden
CGeoDoc *pDoc = m_pApp -> FActGeoDocument();

	if (NULL == pDoc) return E_INVALIDARG;

WDGeoObjectWin Win;
HRESULT hr = pDoc -> FGetGeoObjectWin (hWnd, Win.ppi());
DGeoObjectWin *pIWin = (DGeoObjectWin *)Win;

	if (FAILED(hr))	{
		_ASSERTE(NULL == pIWin);
		return hr;
	}

	pPar->pValues[1] = &pIWin;
	return m_Sink -> FireEvent (pcRoutine, 1, pPar);
}

HRESULT CTRiASNotificationSinkBScript::ObjectWindowEvent(OBJWNDEVT oe, long hORWnd)
{
// Strukturen für Parameter/Rückkehrwert (höchstens ein Parameter)
ebPARAM Pars[2];
LPVOID cbParam[2];
BSPARAM bs = { Pars, cbParam };
HRESULT hr = S_OK;

	Pars[0].wType = 0;				// SubRoutine
	Pars[0].szExtType[0] = '\0';
	cbParam[0] = NULL;

// Event auslösen		
	switch (oe) {
    case OBJWNDEVT_WindowCreated:
	// Sub OnObjectWinCreated (Win As GeoObjectWin)
		if (NULL == hORWnd) 
			return E_INVALIDARG;
		FireWindowEvent (HWND(hORWnd), TEXT("OnObjectWinCreated"), &bs);
		break;

    case OBJWNDEVT_GotFocus:
	// Sub OnObjectWinGotFocus (Win As GeoObjectWin)
		if (NULL == hORWnd) 
			return E_INVALIDARG;
		FireWindowEvent (HWND(hORWnd), TEXT("OnObjectWinGotFocus"), &bs);
		break;

    case OBJWNDEVT_LostFocus:
	// Sub OnObjectWinLostFocus (Win As GeoObjectWin)
		if (NULL == hORWnd) 
			return E_INVALIDARG;
		FireWindowEvent (HWND(hORWnd), TEXT("OnObjectWinLostFocus"), &bs);
		break;

    case OBJWNDEVT_WindowToDestroy:
	// Function OnObjectWinToDestroy (Win As GeoObjectWin) As Boolean
		{
			if (NULL == hORWnd) 
				return E_INVALIDARG;

		ebINT iRet = false;
		
			Pars[0].wType = TYP_BOOLEAN;		// Funktion liefern BOOL
			Pars[0].szExtType[0] = '\0';
			cbParam[0] = &iRet;

			hr = FireWindowEvent (HWND(hORWnd), TEXT("OnObjectWinToDestroy"), &bs);
			if (SUCCEEDED(hr) && iRet) 
				return S_FALSE;		// nicht schließen
		}
		break;

	case OBJWNDEVT_DestroyingWindow:
	case OBJWNDEVT_WindowDestroyed:
		break;

	default:
		ASSERT(false);
		break;
	}
	return S_OK;
}
