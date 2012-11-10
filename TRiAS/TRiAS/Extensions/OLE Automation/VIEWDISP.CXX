// Eine View (ProgrammierInterface) -----------------------------------
// File: VIEWDISP.CXX

#include "precomp.hxx"

#include "oleautor.h"

#include <dirisole.h>
#include <objcontx.hxx>

#include "viewarry.hxx"
#include "enuviews.hxx"
#include "view.hxx"

#include "clsarray.hxx"
#include "enumclss.hxx"
#include "class.hxx"
#include "classes.hxx"

#include "objarray.hxx"
#include "enumobjs.hxx"
#include "obj.hxx"
#include "objs.hxx"

#include "ftsarray.hxx"
#include "enumfts.hxx"
#include "feat.hxx"
#include "fts.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// benötigte SmartInterfaces
DefineSmartInterface2(_DGeoObject, IID_DGeoObject);			// W_IGeoObject
DefineSmartInterface2(_DGeoClass, IID_DGeoClass);

///////////////////////////////////////////////////////////////////////////////
// externe Funktionen
bool RealCoords (LONG lX, LONG lY, double *pdblX, double *pdblY);
bool InternalCoords (double dblX, double dblY, LONG *plX, LONG *plY);

// ProgrammierInterfaceFunktionen ---------------------------------------------
STDMETHODIMP CGeoView::get_isA (LONG *plRTTI)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::get_isA");
	if (NULL == plRTTI) 
		return E_POINTER;
	*plRTTI = RTTI_GeoView;
	return NOERROR;
}

STDMETHODIMP CGeoView::get_Parent (IDispatch **ppIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::get_Parent");
	return m_pUnk -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

STDMETHODIMP CGeoView::get_Application (IDispatch **ppIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::get_Application");
	return ((_DApplication *)m_pApp) -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

STDMETHODIMP CGeoView::put_Parent (IDispatch *pIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::put_Parent");
	return E_NOTIMPL;
}

STDMETHODIMP CGeoView::put_Application (IDispatch *pIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::put_Application");
	return E_NOTIMPL;
}

// Liefert den Text dieser View -----------------------------------
STDMETHODIMP CGeoView::get_Name (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::get_Name");

	if (NULL == pbstrValue) return E_POINTER;

// View nach Text fragen
	*pbstrValue = NULL;
	if (NULL != GetName()) 
		*pbstrValue = SysAllocString (WideString(GetName()));

	if (NULL == *pbstrValue)
		return E_OUTOFMEMORY;

return NOERROR;
}


// Setzt/löscht den Text dieser View ------------------------------
STDMETHODIMP CGeoView::put_Name (BSTR bstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::put_Name");

	if (NULL == bstrValue) return E_UNEXPECTED;

	SetName (AnsiString(bstrValue));
	return NOERROR;
}


// Liefert den Name dieser View ------------------------------
STDMETHODIMP CGeoView::get_Value (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::get_Value");

	if (NULL == pbstrValue) return E_POINTER;

	*pbstrValue = NULL;
	if (GetName()) 
		*pbstrValue = SysAllocString (WideString(GetName()));

	if (NULL == *pbstrValue) 
		return E_OUTOFMEMORY;
	
return NOERROR;
}

STDMETHODIMP CGeoView::GetClipObject (DGeoObject **ppIObj)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::GetClipObject");

	if (NULL == ppIObj) return E_POINTER;

	*ppIObj = NULL;

// ClippingObject besorgen
LONG lONr = DEX_GetClipObject(GetName());

	if (INVALID_ONR == lONr)
		return E_FAIL;		// kein ClippObjekt gesetzt

// GeoObject besorgen
CGeoObject *pObject = m_pDoc -> FGetObjectDisp (
							lONr, ppIObj, GEOOBJECTMODE_Get);
	if (NULL == pObject)
		return E_UNEXPECTED;

	return NOERROR;
}

STDMETHODIMP CGeoView::ResetClipObject (void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::ResetClipObject");

	return SetClipObject (NULL);
}

STDMETHODIMP CGeoView::SetClipObject (DGeoObject *pIObj)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::SetClipObject");

LONG lONr = 0L;

	try {
		if (NULL != pIObj)
			THROW_FAILED_HRESULT(pIObj -> get_Value (&lONr));

	CLIPOBJECTSET COS;

		INITSTRUCT (COS, CLIPOBJECTSET);
		COS.m_pcView = GetName();
		COS.m_lONr = lONr;
		if (!DEX_SetClipObject(COS))
			_com_issue_error(E_FAIL);

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return S_OK;
}


// DELETECLSCOLLECTIONPROC ----------------------------------------------------
extern "C" 
bool PASCAL _XTENSN_EXPORT DeleteClassFromView (
	ULONG lIdent, CGeoDoc *pDoc, DWORD dwData)
{
CGeoView *pView = pDoc -> FGetViewDisp ((char *)dwData);

	return pView -> FRemoveIdentFromView (lIdent, (OBJECTTYPE)(OTPunkt|OTLinie|OTFlaeche|OTText));
}


// Liefert eine Collection von GeoClass's, die in dieser GeoDB enthalten sind -
typedef struct tagENUMIDENTDATA {
	CClassCreator *m_pCr;
	LPUNKNOWN m_pUnk;
	CTriasApp *m_pApp;
	CGeoDoc *m_pDoc;
} ENUMIDENTDATA;

extern "C" BOOL PASCAL _XTENSN_EXPORT _GetAllViewIdents (long lIdent, BOOL, void *pData)
{
ENUMIDENTDATA *pEID = (ENUMIDENTDATA *)pData;

CClass *pClass = pEID -> m_pDoc -> FGetClassDisp ((ULONG)lIdent);

	if (pClass && pEID -> m_pCr -> InsertPtr (pClass))
		((_DGeoClass *)pClass) -> AddRef();
	
	return true;
}

// INITCLASSCOLLECTIONPROC -----------------------------------------------------
extern "C" 
INITCLSSTATUS PASCAL GetAllViewIdents (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	container_wrappers::CCreator &rCollCr, DWORD dwData, ULONG *plIdent)
{
ENUMIDENTDATA EID;

	EID.m_pCr = (CClassCreator *)&rCollCr;
	EID.m_pUnk = pUnk;
	EID.m_pApp = pApp;
	EID.m_pDoc = pDoc;

	if (plIdent == NULL) {		// complete fill
	ENUMTEXTKEY ETK;

		ETK.eKey = (char *)dwData;
		ETK.eFcn = (ENUMTEXTKEYPROC)_GetAllViewIdents;	// zu rufende Funktion
		ETK.ePtr = &EID;				// durchzureichende Daten
		if (DEX_EnumSightIdents (ETK))			// mit Idents füllen
			return INITCLSSTATUS_Exists;
	} else if (*plIdent != INVALID_IDENT) {
		if (_GetAllViewIdents (*plIdent, true, &EID))
			return INITCLSSTATUS_Exists;
	}
	
	return INITCLSSTATUS_Error;
}


// Liefert die Liste aller in diesem View enthaltenen Objektklassen 
// (Identifikatoren)
STDMETHODIMP CGeoView::GetClasses (VARIANT /*vClss*/, VARIANT /*vLogMode*/, DGeoClasses **ppIClss)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::GetClasses");

	TEST_E_POINTER("CGeoView::GetClasses", ppIClss);

CClasses *pCIdents = CClasses::CreateInstance (
						(_DView *)this, m_pApp, m_pDoc, 
						GetAllViewIdents, (DWORD)GetName(), DeleteClassFromView);

	if (NULL == pCIdents) return E_OUTOFMEMORY;

	*ppIClss = (DGeoClasses *)pCIdents;
	return S_OK;
}

// helper function ------------------------------------------------------------
HRESULT CGeoView::HandleClass (
	CClass *pClass, OBJECTTYPE rgOTypes, GEOCLASSMODE rgMode)
{
	if (NULL == pClass) return E_UNEXPECTED;
	
	switch (rgMode) {		
	case GEOCLASSMODE_Get:		// default
		if (!ClassIsMemberOfView (pClass, rgOTypes))
			return E_UNEXPECTED;
		break;
			
	case GEOCLASSMODE_Remove:	// remove item
		FRemoveIdentFromView (pClass -> GetValue(), rgOTypes);
		break;
			
	case GEOCLASSMODE_Add:		// add Ident to view, if not in view
		if (ClassIsMemberOfView (pClass, rgOTypes) || 
			!FAddIdentToView (pClass, rgOTypes)) 
		{
			return E_UNEXPECTED;
		}
		break;

	case GEOCLASSMODE_Replace:	// add Ident to view, default visualisation
	default:
		return E_UNEXPECTED;
	}

return NOERROR;
} 
	
STDMETHODIMP CGeoView::GetClass (
	VARIANT vCls, VARIANT vOTypes, VARIANT vMode, DGeoClass **ppICls)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::GetClass");

CComVariant vArg; 
CComVariant vArgMode;
CComVariant vArgTypes;

HRESULT hr = VariantChangeType (&vArgMode, &vMode, 0, VT_I4);
GEOCLASSMODE rgMode = GEOCLASSMODE_Get;

	if (SUCCEEDED(hr)) 
		rgMode = (GEOCLASSMODE)V_I4(&vArgMode);

OBJECTTYPE rgOTypes = (OBJECTTYPE)(OTPunkt|OTLinie|OTFlaeche|OTText);

	hr = VariantChangeType (&vArgTypes, &vOTypes, 0, VT_I4);
	if (SUCCEEDED(hr)) 
		rgOTypes = (OBJECTTYPE)V_I4(&vArgTypes);

	if (NULL != ppICls) *ppICls = NULL;

HOBJECTS hObjs = INVALID_HOBJECTS;

	hr = E_FAIL;
	if (GEOCLASSMODE_Get == rgMode && 
		(VT_DISPATCH == V_VT(&vCls) || VT_UNKNOWN == V_VT(&vCls))) 
	{
		ATLTRY(W_DGeoClass(V_UNKNOWN(&vCls)) -> get_Code(&hObjs));
		hr = (INVALID_HOBJECTS == hObjs) ? E_FAIL : S_OK;
	}

	if (FAILED(hr)) {
		hr = VariantChangeType (&vArg, &vCls, 0, VT_I4);	// Zahl als Ident
		if (SUCCEEDED(hr))
			hObjs = V_I4(&vArg);
	}

	if (SUCCEEDED(hr)){
		_ASSERTE(INVALID_HOBJECTS != hObjs);

	CClass *pClass = m_pDoc -> FGetClassDisp (hObjs, ppICls, GEOCLASSMODE_Get);

		hr = HandleClass (pClass, rgOTypes, rgMode);
		if (FAILED(hr) && NULL != ppICls && NULL != *ppICls) {
			(*ppICls) -> Release();
			*ppICls = NULL;
		}
		return hr;
	}
	
	hr = VariantChangeType (&vArg, &vCls, 0, VT_BSTR); 	// Argument is Class Name
	if (SUCCEEDED(hr)) {
	CClass *pClass = m_pDoc -> FGetClassDisp (AnsiString(V_BSTR(&vArg)), 
						ppICls, GEOCLASSMODE_Get);
			
		hr = HandleClass (pClass, rgOTypes, rgMode);
		if (FAILED(hr) && NULL != ppICls && NULL != *ppICls) {
			(*ppICls) -> Release();
			*ppICls = NULL;
		}
		return hr;
	}

return hr;
}


// DELETEOBJECTCOLLECTIONPROC -------------------------------------------------
extern "C" bool PASCAL _XTENSN_EXPORT DeleteObjectFromView (LONG, CGeoDoc *, DWORD)
{
	return false;	// not implemented yet
}

// Liefert eine Collection von GeoObject, die in dieser GeoDB enthalten sind -
typedef struct tagENUMOBJECTDATA {
	CGeoObjectCreator *m_pCr;
	LPUNKNOWN m_pUnk;
	CTriasApp *m_pApp;
	CGeoDoc *m_pDoc;
} ENUMOBJECTDATA;

extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetObjectsFromView (long lONr, DWORD, void *pData)
{
ENUMOBJECTDATA *pEOD = (ENUMOBJECTDATA *)pData;
CGeoObject *pObject = pEOD -> m_pDoc -> FGetObjectDisp (lONr);

	if (pObject && pEOD -> m_pCr -> InsertPtr (pObject))
		((_DGeoObject *)pObject) -> AddRef();

	return true;
}

extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetIdentsFromView (long lIdent, DWORD dwData, void *pData)
{
ENUMLONGKEYEX ELK;

	ELK.eKey = lIdent;
	ELK.eFcn = (ENUMLONGKEYEXPROC)_GetObjectsFromView;
	ELK.ePtr = pData;
	ELK.eData = dwData;	// objecttypes for this ident
	
	return DEX_EnumIdentObjectsEx (ELK);
}

// INITOBJCOLLECTIONPROC
extern "C" 
INITOBJSTATUS PASCAL GetObjectsFromView (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	container_wrappers::CCreator &rCollCr, DWORD dwData, long *plONr)
{
	if (plONr != NULL) return INITOBJSTATUS_Error;
	
ENUMTEXTKEYEX EObjs;
ENUMOBJECTDATA EOD;

	EOD.m_pCr = (CGeoObjectCreator *)&rCollCr;
	EOD.m_pUnk = pUnk;
	EOD.m_pApp = pApp;
	EOD.m_pDoc = pDoc;
	
	EObjs.eKey = (char *)dwData;	// this IS the ViewName
	EObjs.eFcn = (ENUMTEXTKEYEXPROC)_GetIdentsFromView;	// zu rufende Funktion
	EObjs.ePtr = &EOD;					// durchzureichende Daten
	EObjs.eData = (OTPunkt|OTLinie|OTFlaeche|OTText);
	
	if (DEX_EnumSightIdentsEx (EObjs))		// mit Idents füllen
		return INITOBJSTATUS_Exists;

	return INITOBJSTATUS_Error;
}

// Liefert die Liste aller Objekte, die zu dieser Sicht angehören -------------
STDMETHODIMP CGeoView::GetObjects (VARIANT vObjs, VARIANT vLogMode, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::GetObjects");

	TEST_E_POINTER("CGeoView::GetObjects", ppIObjs);

CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(DView *)this, m_pApp, m_pDoc, 
							GetObjectsFromView, (DWORD)GetValue(), 
							DeleteObjectFromView); 

	if (NULL == pCObjects) return E_UNEXPECTED;
	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

HRESULT CGeoView::HandleGeoObject (CGeoObject *pObject, GEOOBJECTMODE rgMode)
{
	if (NULL == pObject) return E_UNEXPECTED;
	
	switch (rgMode) {		
	case GEOOBJECTMODE_Get:		// default
		if (!ObjectIsMemberOfView (pObject))
			return E_UNEXPECTED;
		break;
			
	case GEOOBJECTMODE_Remove:	// remove item
	case GEOOBJECTMODE_Add:		// create, if not existent
	case GEOOBJECTMODE_Replace:	// remove old, create new
	default:
		return E_UNEXPECTED;
	}

return NOERROR;
}

STDMETHODIMP CGeoView::GetObject (VARIANT vObj, VARIANT vMode, DGeoObject **ppIObj)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::GetObject");

	TEST_E_POINTER("CGeoView::GetObject", ppIObj);

VARIANTARG vArg; VariantInit (&vArg);
VARIANTARG vArgMode; VariantInit (&vArgMode);

HRESULT hr = VariantChangeType (&vArgMode, &vMode, 0, VT_I4);
GEOOBJECTMODE rgMode = GEOOBJECTMODE_Get;

	if (SUCCEEDED(hr)) 
		rgMode = (GEOOBJECTMODE)V_I4(&vArgMode);
	VariantClear (&vArgMode);

	*ppIObj = NULL;

	if (VT_BSTR != V_VT(&vObj)) {
	// nur auf Zahl testen, wenn nicht direkt als BSTR gegeben
	// damit Objektnamen eine Zahl sein dürfen
		hr = VariantChangeType (&vArg, &vObj, 0, VT_I4); // Argument is Object Number	
		if (SUCCEEDED(hr)) {
		CGeoObject *pObject = m_pDoc -> FGetObjectDisp (V_I4(&vArg), 
									ppIObj, GEOOBJECTMODE_Get);

			hr = HandleGeoObject (pObject, rgMode);
			if (FAILED(hr) && NULL != ppIObj && NULL != *ppIObj) {
				(*ppIObj) -> Release();
				*ppIObj = NULL;
			}
			return hr;
		}
	}
		
	hr = VariantChangeType (&vArg, &vObj, 0, VT_BSTR); // Argument is Object Name
	if (SUCCEEDED(hr)) {
	CGeoObject *pObject = m_pDoc -> FGetObjectDisp (V_BSTR(&vArg), ppIObj, GEOOBJECTMODE_Get);
			
		VariantClear (&vArg);
		hr = HandleGeoObject (pObject, rgMode);
		if (FAILED(hr) && NULL != ppIObj && NULL != *ppIObj) {
			(*ppIObj) -> Release();
			*ppIObj = NULL;
		}
		return hr;
	}

	return hr;
}


// DELETEFEATCOLLECTIONPROC ----------------------------------------------------
extern "C" bool PASCAL _XTENSN_EXPORT DeleteFeatureFromView (LPCSTR bName, void *pView)
{
	return ((CGeoView *)pView) -> FDelFeature (bName);
}


// Liefert eine Collection von GeoFeature's, die zu diesem Ident gehören ----------------------
typedef struct tagENUMFEATUREDATA {
	CGeoFeatureBaseCreator *m_pCr;
	LPUNKNOWN m_pUnk;
	CTriasApp *m_pApp;
	CGeoDoc *m_pDoc;
	CGeoView *m_pView;
	char *m_pViewName;
} ENUMFEATUREDATA;
															
extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetFeaturesFromView (long lFCd, BOOL, void *pData)
{
char cbName[KTEXTLEN+2];
PBDDATA pbdData;

	INITSTRUCT (pbdData, PBDDATA);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lFCd;
	pbdData.pbdKText = cbName;	// gesucht
	pbdData.pbdLText = NULL;
	pbdData.pbdKTextLen = KTEXTLEN+1;
	pbdData.pbdLTextLen = 0;

	*cbName = '\0';
	if (DEX_GetPBDData (pbdData) == EC_OKAY) {
		if (pbdData.pbdKTextLen > 0) 
			cbName[KTEXTLEN] = '\0';
	} else {
	CString strRes; strRes.LoadString (IDS_MERKMAL);

		wsprintf (cbName, 10 == DEX_GetMkBase() ? "%s: %ld" : "%s: %lx", 
				  (LPCSTR)strRes, lFCd);
	}

ENUMFEATUREDATA *pEFD = (ENUMFEATUREDATA *)pData;
CGeoFeatureBase *pFeature = pEFD -> m_pView -> FGetFeatureDisp (cbName);

	if (pFeature && pEFD -> m_pCr -> InsertPtr (pFeature)) {
		((_DGeoFeature *)pFeature) -> AddRef(); 
		return true;
	}
	
return false;	
}

extern "C" 
INITFEATSTATUS PASCAL _CreateFeatureView (ENUMFEATUREDATA *pEFD, string &bName)
{
CGeoFeatureBase *pFeature = pEFD -> m_pView -> FGetFeatureDisp (bName.c_str());
INITFEATSTATUS iResult = INITFEATSTATUS_Exists;

	if (pFeature == NULL) {
		pFeature = pEFD -> m_pView -> FGetFeatureDisp (bName.c_str(), NULL, FEATUREMODE_Add);
		iResult = INITFEATSTATUS_Created;
	}
	if (pFeature && pEFD -> m_pCr -> InsertPtr (pFeature)) {
		((_DGeoFeature *)pFeature) -> AddRef();
		return iResult;
	}
	
return INITFEATSTATUS_Error;
}



// INITFEATCOLLECTIONPROC
extern "C" 
INITFEATSTATUS PASCAL GetFeaturesFromView (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, void *pView,
	container_wrappers::CCreator &rCollCr, DWORD dwData, string *pbName, DWORD dwFlags)
{
ENUMFEATUREDATA EFD;

	EFD.m_pCr = (CGeoFeatureBaseCreator *)&rCollCr;
	EFD.m_pUnk = pUnk;
	EFD.m_pApp = pApp;
	EFD.m_pDoc = pDoc;
	EFD.m_pView = (CGeoView *)pView;
	EFD.m_pViewName = (char *)dwData;
	
	if (pbName == NULL) {							// Complete fill
		ENUMLONGKEY EFCds;

		EFCds.eKey = (long)dwData;								// This is View Name "ident"
		EFCds.eFcn = (ENUMLONGKEYPROC)_GetFeaturesFromView;		// zu rufende Funktion
		EFCds.ePtr = &EFD;										// durchzureichende Daten

		if(DEX_EnumSichtMerkmale (EFCds))			// mit Fetaures füllen
            return INITFEATSTATUS_Exists;

	} else 
			return _CreateFeatureView (&EFD, *pbName);

return INITFEATSTATUS_Error;		
}


STDMETHODIMP CGeoView::GetFeatures (VARIANT /*vFeatures*/, VARIANT /*vLogMode*/, DGeoFeatures **ppIFeats)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::GetFeatures");

	TEST_E_POINTER("CGeoView::GetFeatures", ppIFeats);

CGeoFeatures *pCFeatures = CGeoFeatures::CreateInstance (
							(DView *)this, m_pApp, m_pDoc,
							this, GetFeaturesFromView, (DWORD)GetValue(),
							DeleteFeatureFromView); 

	if (NULL == pCFeatures) return E_OUTOFMEMORY;

	*ppIFeats = (DGeoFeatures *)pCFeatures;
	return S_OK;	
}

STDMETHODIMP CGeoView::GetFeature (VARIANT vFeature, VARIANT vMode, DGeoFeature **ppIFeat)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::GetFeature");

	TEST_E_POINTER("CGeoView::GetFeature", ppIFeat);

CComVariant vArg;
CComVariant vArgMode;

HRESULT hr = vArgMode.ChangeType (VT_I4, &vMode);
FEATUREMODE rgMode = FEATUREMODE_Get;

	if (SUCCEEDED(hr)) 
		rgMode = (FEATUREMODE)V_I4(&vArgMode);
		
	hr = vArg.ChangeType (VT_BSTR, &vFeature);	// Feature name as string
	if (SUCCEEDED(hr)) {
	string strName (AnsiString(V_BSTR(&vArg)));
	
		switch (rgMode) {
		case FEATUREMODE_Get:		// get default
		case FEATUREMODE_Replace:	// remove old, create new
		case FEATUREMODE_Add:		// create, if not existent
			{
			CGeoFeatureBase *pFeature = FGetFeatureDisp (
							strName.c_str(), ppIFeat, rgMode);

				if (NULL == pFeature) 
					return E_UNEXPECTED;
			}
			break;

		case  FEATUREMODE_Remove:		// remove item  tut 
			FDelFeature (strName.c_str());
			*ppIFeat = NULL;
			break;
			
		default:
			return E_UNEXPECTED;
		}
		return NOERROR;
	}

	return hr;
}


// Wird gerufen, um Collection mit allen Objekten der Sicht innerhalb des
// Fensters zu füllen
typedef struct tagOBJSINWINDOWVIEW {
	double m_rgdCont[4];		// XMin, XMax, YMin, Ymax
	const char *m_pView;				// Sichtname
} OBJSINWINDOWVIEW;

// INITOBJCOLLECTIONPROC
extern "C" 
INITOBJSTATUS PASCAL GetObjectsInWindowFromView (
		LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
		container_wrappers::CCreator &rCollCr, DWORD dwData, long *plONr)
{
	if (plONr != NULL) return INITOBJSTATUS_Error;
	
ENUMOBJECTDATA EOD;

	EOD.m_pCr = (CGeoObjectCreator *)&rCollCr;
	EOD.m_pUnk = pUnk;
	EOD.m_pApp = pApp;
	EOD.m_pDoc = pDoc;
	
ENUMRECHGEOMETRIEEX ERG;
OBJSINWINDOWVIEW *pData = (OBJSINWINDOWVIEW *)dwData;

	INITSTRUCT(ERG, ENUMRECHGEOMETRIEEX);
	ERG.lCont = pData -> m_rgdCont;
	ERG.iMode = (ERGExact|ERGConverted);
	ERG.eFcn = (RECHGEOMETRIEPROC)_GetObjectsFromView;
	ERG.pData = &EOD;					// durchzureichende Daten
	ERG.m_pView = pData -> m_pView;

	if (DEX_EnumRechGeometrie (ERG))	// mit Objekten füllen
		return INITOBJSTATUS_Exists;

return INITOBJSTATUS_Error;
}

// Liefert alle Objekte dieser Sicht innerhalb des gegebenen Rechteckes -------
STDMETHODIMP CGeoView::GetObjectsInRect (
		double dX1, double dY1, VARIANT vX2, VARIANT vY2, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::GetObjectsInRect");

	TEST_E_POINTER("CGeoView::GetObjectsInRect", ppIObjs);

// Parameter enthalten Eckkoordinaten
CComVariant vArg;
OBJSINWINDOWVIEW ownd;

	ownd.m_rgdCont[0] = dX1;
	ownd.m_rgdCont[2] = dY1;

// 2. Koordinatenpaar ist optional
HRESULT hr = VariantChangeType (&vArg, &vX2, 0, VT_R8);

	ownd.m_rgdCont[1] = FAILED(hr) ? ownd.m_rgdCont[0] : V_R8(&vArg);

	hr = VariantChangeType (&vArg, &vY2, 0, VT_R8);
	ownd.m_rgdCont[3] = FAILED(hr) ? ownd.m_rgdCont[2] : V_R8(&vArg);

	ownd.m_pView = GetValue();

// Collection anlegen
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(_DView *)this, m_pApp, m_pDoc, GetObjectsInWindowFromView, 
							(DWORD)&ownd, DeleteObjectFromView); 
	
	if (pCObjects == NULL) return E_OUTOFMEMORY;

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CGeoView::get_Properties (_DTRiASProperties **ppIProps)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::get_Properties");
	ATLTRACENOTIMPL("CGeoView::get_Properties");
}

STDMETHODIMP CGeoView::CreateProperty (VARIANT vName, VARIANT vType, VARIANT vValue, _DTRiASProperty **ppIProp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::CreateProperty");
	ATLTRACENOTIMPL("CGeoView::CreateProperty");
}

STDMETHODIMP CGeoView::get_RefScale (long *plRefScale)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::get_RefScale");
	ATLTRACENOTIMPL("CGeoView::get_RefScale");
}

STDMETHODIMP CGeoView::put_RefScale (long lRefScale)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::put_RefScale");
	ATLTRACENOTIMPL("CGeoView::put_RefScale");
}

STDMETHODIMP CGeoView::get_Scale (long *plScale)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::get_Scale");

	if (NULL == plScale) return E_POINTER;

double dScale = 0.0;

	if (!DEX_GetActiveZoom(dScale)) 
		return E_FAIL;

	*plScale = (long)(dScale+0.5);
	return S_OK;
}

STDMETHODIMP CGeoView::put_Scale (long lScale)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::put_Scale");

	if (!DEX_SetActiveZoom(lScale))
		return E_FAIL;
	return S_OK;
}

STDMETHODIMP CGeoView::get_Description (BSTR *pbstrDesc)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::get_Description");

	if (NULL == pbstrDesc) return E_POINTER;

VIEWDESC VD;
HRESULT hr = S_OK;

	memset (&VD, 0, sizeof(VIEWDESC));
	VD.m_dwSize = sizeof(VIEWDESC);
	
	try {
		VD.m_pView = GetName();
		VD.m_pDesc = new char [_MAX_PATH];
		VD.m_iLen = _MAX_PATH;
		
		if (DEX_GetViewDescription (VD)) {
			USES_CONVERSION;
			*pbstrDesc = SysAllocString(A2OLE(VD.m_pDesc));
			if (NULL == *pbstrDesc)
				hr = E_OUTOFMEMORY;
		} 

	} catch (CMemoryException *e) {
		e -> Delete();
		hr = E_OUTOFMEMORY;
	} 

	DELETE_OBJ (VD.m_pDesc);
	return hr;
}

STDMETHODIMP CGeoView::put_Description (BSTR bstrDesc)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::put_Description");

VIEWDESC VD;

	memset (&VD, 0, sizeof(VIEWDESC));
	VD.m_dwSize = sizeof(VIEWDESC);
	USES_CONVERSION;

char *pDesc = OLE2A(bstrDesc);
int iLen = SysStringLen (bstrDesc);

	VD.m_pView = GetName();
	VD.m_pDesc = iLen > 0 ? pDesc : NULL;
	VD.m_iLen = iLen;
	if (NULL == DEX_SetViewDescription (VD))
		return E_FAIL;

	return S_OK;
}

STDMETHODIMP CGeoView::GetActRect (
	double *pdX, double *pdY, VARIANT *pvX, VARIANT *pvY)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::GetActRect");

double dXMax = 0.0;
double dYMax = 0.0;
long lCont[4];

	*pdX = 0.0;
	*pdY = 0.0;
	if (!DEX_GetActiveSightContainer(lCont))
		return E_UNEXPECTED;

ObjContainer OC (lCont[0], lCont[1], lCont[2], lCont[3]);	// Container um unsere Ansicht

// Koordinaten transformieren
	if (!RealCoords (OC.XMin(), OC.YMin(), pdX, pdY) ||
		!RealCoords (OC.XMax(), OC.YMax(), &dXMax, &dYMax))
	{
		return E_UNEXPECTED;
	}

// Ergebnisse liefern
	if (NULL != pvX) {
	CComVariant v (dXMax);

		v.Detach(pvX);
	}
	if (NULL != pvY) {
	CComVariant v (dYMax);

		v.Detach(pvY);
	}
	return S_OK;
}

STDMETHODIMP CGeoView::SetActRect (
	double dX1, double dY1, VARIANT vX2, VARIANT vY2)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::SetActRect");

// Koordinaten transformieren
LONG lCont[4];

	if (!InternalCoords (dX1, dY1, &lCont[0], &lCont[2]))
		return E_INVALIDARG;

	lCont[1] = lCont[0];		// für alle Fälle
	lCont[3] = lCont[2];

CComVariant vX, vY;

	if (SUCCEEDED(vX.ChangeType (VT_R8, &vX2)) && SUCCEEDED(vY.ChangeType (VT_R8, &vY2)))
	{
		if (!InternalCoords (V_R8(&vX), V_R8(&vY), &lCont[1], &lCont[3]))
			return E_UNEXPECTED;
	}

// neuen Bildausschnitt einstellen
	return DEX_SetActiveSightContainer(lCont) ? S_OK : E_UNEXPECTED;
}

STDMETHODIMP CGeoView::GetConstraintRect (
	double *pdX, double *pdY, VARIANT *pvX, VARIANT *pvY)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::GetConstraintRect");
	ATLTRACENOTIMPL("CGeoView::GetConstraintRect");
}

STDMETHODIMP CGeoView::SetConstraintRect (
	double dX1, double dY1, VARIANT vX2, VARIANT vY2)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoView::SetConstraintRect");
	ATLTRACENOTIMPL("CGeoView::SetConstraintRect");
}

