// Eine Feature (ProgrammierInterface) -----------------------------------
// File: FEATDISP.CXX

#include "precomp.hxx"

#include <dirisole.h>
#include <xtsnguid.h>

#include "feat.hxx"

#include "viewarry.hxx"
#include "enuviews.hxx"
#include "view.hxx"
#include "views.hxx"

#include "clsarray.hxx"
#include "enumclss.hxx"
#include "class.hxx"
#include "classes.hxx"

#include "objarray.hxx"
#include "enumobjs.hxx"
#include "obj.hxx"
#include "objs.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// SamrtIF's
DefineSmartInterface(PropertyInfo2);
DefineSmartInterface(PropertyInfo);

// ProgrammierInterfaceFunktionen ---------------------------------------------
STDMETHODIMP CGeoFeatureBase::get_isA (LONG *plRTTI)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoFeatureBase::get_isA");

	if (NULL == plRTTI) 
		return E_POINTER;
	*plRTTI = RTTI_GeoFeature;
	return NOERROR;
}

STDMETHODIMP CGeoFeatureBase::get_Parent (IDispatch **ppIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoFeatureBase::get_Parent");
	return m_pUnk -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

STDMETHODIMP CGeoFeatureBase::get_Application (IDispatch **ppIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoFeatureBase::get_Application");
	return ((_DApplication *)m_pApp) -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

STDMETHODIMP CGeoFeatureBase::put_Parent (IDispatch *pIDisp)
{
	return E_NOTIMPL;
}

STDMETHODIMP CGeoFeatureBase::put_Application (IDispatch *pIDisp)
{
	return E_NOTIMPL;
}

// Liefert den Feature Name  dieses Featurees -----------------------------------
STDMETHODIMP CGeoFeatureBase::get_Value (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoFeatureBase::get_Value");

	if (NULL == pbstrValue) return E_POINTER;

// Feature code As text fragen
	*pbstrValue = NULL;
	if (GetValue()) 
		*pbstrValue = SysAllocString (WideString(GetValue()));

	if (NULL == *pbstrValue)
		return E_OUTOFMEMORY;

return NOERROR;
}


// Liefert den Feature Name ------------------------------------
STDMETHODIMP CGeoFeatureBase::get_Name (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoFeatureBase::get_Name");

	if (NULL == pbstrValue) return E_POINTER;

// Feature nach KurzText fragen
	*pbstrValue = NULL;
	if (NULL != GetName()) 
		*pbstrValue = SysAllocString (WideString(GetName()));

	if (NULL == *pbstrValue)
		return E_OUTOFMEMORY;

return NOERROR;
}


// Setzt/löscht den Feature Name-------------------------------
STDMETHODIMP CGeoFeatureBase::put_Name (BSTR bstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoFeatureBase::put_Name");

	if (NULL == bstrValue) return E_UNEXPECTED;

	SetName (AnsiString(bstrValue));
	return NOERROR;
}

// Liefert den Feature Fullname  dieses Features ------------------------------------
STDMETHODIMP CGeoFeatureBase::get_FullName (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoFeatureBase::get_FullName");

	if (NULL == pbstrValue) return E_POINTER;

// Feature nach KurzText fragen
	*pbstrValue = NULL;
	if (NULL != GetFullName()) 
		*pbstrValue = SysAllocString (WideString(GetFullName()));

	if (NULL == *pbstrValue)
		return E_OUTOFMEMORY;

return NOERROR;
}

// Setzt/löscht den Fullname  dieses Features ------------------------------------
STDMETHODIMP CGeoFeatureBase::put_FullName (BSTR bstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoFeatureBase::put_FullName");

	if (NULL == bstrValue) return E_UNEXPECTED;

	SetFullName (AnsiString(bstrValue));
	return NOERROR;
}

 
// Liefert den Feature  ------------------------------------
STDMETHODIMP CGeoFeatureBase::get_Feature (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoFeatureBase::get_Feature");

	if (NULL == pbstrValue) return E_POINTER;

// Feature nach Featurenamen fragen
	if (NULL != GetFeat()) {
		*pbstrValue = SysAllocString (WideString(GetFeat()));
		if (NULL == *pbstrValue) 
			return E_OUTOFMEMORY;
	} else 
		return E_OUTOFMEMORY;

	D_OUTF2(1, "%s: ", m_pName, "\'%s\'", AnsiString(*pbstrValue));
	return NOERROR;
}

// Setzt/löscht den Feature -------------------------------
STDMETHODIMP CGeoFeatureBase::put_Feature (BSTR bstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoFeatureBase::put_Feature");
	if (NULL == bstrValue) 
		return E_POINTER;

	D_OUTF2(1, "%s: ", m_pName, "\'%s\'", AnsiString(bstrValue));
	return SetFeat (AnsiString(bstrValue));
}

STDMETHODIMP CGeoFeatureBase::get_Flags (PROPERTYCAPS *pdwValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	ATLTRACENOTIMPL("CGeoFeatureBase::get_Flags");
}

STDMETHODIMP CGeoFeatureBase::put_Flags (PROPERTYCAPS dwValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	ATLTRACENOTIMPL("CGeoFeatureBase::put_Flags");
}

STDMETHODIMP CGeoFeatureVC::get_ConfigData (VARIANT *pvOptData)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoFeatureBase::get_ConfigData");

	if (NULL == pvOptData) return E_POINTER;

	VariantInit (pvOptData);
	V_VT(pvOptData) = VT_I4;
	V_I4(pvOptData) = m_lFCd;

	return S_OK;
}

// DELETEVIEWCOLLECTIONPROC ----------------------------------------------------
extern "C" bool PASCAL _XTENSN_EXPORT DeleteViewFromFeat (LPCSTR bName, CGeoDoc *pDoc)
{
	return true;		// do nothing
}

// Liefert eine Collection von Views  -----------------------------------------
typedef struct tagENUMVIEWDATA {
	CGeoViewCreator *m_pCr;
	LPUNKNOWN m_pUnk;
	CTriasApp *m_pApp;
	CGeoDoc *m_pDoc;
} ENUMVIEWDATA;

extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetViewsFromFeat (char *bName, DWORD, void *pData)
{
ENUMVIEWDATA *pEOD = (ENUMVIEWDATA *)pData;
CGeoView *pView = pEOD -> m_pDoc -> FGetViewDisp (bName);

	if (pView && pEOD -> m_pCr -> InsertPtr (pView))
		((_DView *)pView) -> AddRef(); 

	return true;
}

// INITVIEWCOLLECTIONPROC -----------------------------------------------------
extern "C" INITVIEWSTATUS PASCAL GetViewsFromFeat ( LPUNKNOWN  pUnk, 
													CTriasApp *pApp, 
													CGeoDoc   *pDoc, 
													container_wrappers::CCreator  &rCollCr, 
													DWORD, 
													string    *pbName )
{
ENUMVIEWDATA EFD;

	EFD.m_pCr = (CGeoViewCreator *)&rCollCr;
	EFD.m_pUnk = pUnk;
	EFD.m_pApp = pApp;
	EFD.m_pDoc = pDoc;
	
	if (pbName == NULL) {			// Complete fill
		ENUMNOKEY ENK;
	
		ENK.eFcn = (ENUMNOKEYPROC)_GetViewsFromFeat;	// zu rufende Funktion
		ENK.ePtr = &EFD;								// durchzureichende Daten

//???		if( DEX_EnumFeatSights (ENK) )						// mit Views füllen
                   	return INITVIEWSTATUS_Exists;
	} 

	return INITVIEWSTATUS_Error;		
} 

// Liefert alle Ansichten, in denen diese Klasse vertreten ist ----------------
STDMETHODIMP CGeoFeatureBase::GetViews (DViews **ppIViews)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoFeatureBase::GetViews");

	TEST_E_POINTER("CGeoFeatureBase::GetViews", ppIViews);

CGeoViews *pCGeoViews = CGeoViews::CreateInstance (
							(_DGeoFeature *)this, m_pApp, m_pDoc, 
							GetViewsFromFeat, NULL, DeleteViewFromFeat);

	if (NULL == pCGeoViews) return E_OUTOFMEMORY;

	*ppIViews = (DViews *)pCGeoViews;		// übernimmt AddRef
	return S_OK;
}

// DELETECLSCOLLECTIONPROC ----------------------------------------------------
extern "C" bool PASCAL _XTENSN_EXPORT DeleteClassFromFeat (ULONG    lIdent, 
														   CGeoDoc *pDoc, 
														   DWORD)
{
	return true;		// do nothing
}


// Liefert eine Collection von GeoClass's, die in dieser GeoDB enthalten sind -
typedef struct tagENUMIDENTDATA {
	CClassCreator *m_pCr;
	LPUNKNOWN      m_pUnk;
	CTriasApp     *m_pApp;
	CGeoDoc       *m_pDoc;
} ENUMIDENTDATA;

extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetAllFeatIdents (long lIdent, BOOL, void *pData)
{
ENUMIDENTDATA *pEID = (ENUMIDENTDATA *)pData;
CClass *pClass = pEID -> m_pDoc -> FGetClassDisp ((ULONG)lIdent);

	if (pClass && pEID -> m_pCr -> InsertPtr (pClass)) 
		((_DGeoClass *)pClass) -> AddRef();

	return true;
}

// INITCLASSCOLLECTIONPROC ----------------------------------------------------
extern "C" 
INITCLSSTATUS PASCAL GetAllFeatIdents (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	container_wrappers::CCreator &rCollCr, DWORD dwData, ULONG *plIdent)
{
ENUMIDENTDATA EID;

	EID.m_pCr = (CClassCreator *)&rCollCr;
	EID.m_pUnk = pUnk;
	EID.m_pApp = pApp;
	EID.m_pDoc = pDoc; 
		
    if (plIdent == NULL) {		// Complete fill
	ENUMTEXTKEY ETK;

		ETK.eKey = (char *)dwData;
		ETK.eFcn = (ENUMTEXTKEYPROC)_GetAllFeatIdents;	// zu rufende Funktion
		ETK.ePtr = &EID;								// durchzureichende Daten
//???	if (DEX_EnumFeatIdents (ETK))					// mit Idents füllen
			return INITCLSSTATUS_Exists;

	} else if (*plIdent != INVALID_IDENT) {
		if (_GetAllFeatIdents (*plIdent, true, &EID))
			return INITCLSSTATUS_Exists;
	}
	
return INITCLSSTATUS_Error;
}


STDMETHODIMP CGeoFeatureBase::GetClasses (VARIANT /*vClss*/, VARIANT /*vLogMode*/, DGeoClasses **ppIClss)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoFeatureBase::GetClasses");

	TEST_E_POINTER("CGeoFeatureBase::GetClasses", ppIClss);

CClasses *pCIdents = CClasses::CreateInstance (
						(_DGeoFeature *)this, m_pApp, m_pDoc, 
						GetAllFeatIdents, NULL, DeleteClassFromFeat);

	if (NULL == pCIdents) return E_OUTOFMEMORY;

	*ppIClss = (DGeoClasses *)pCIdents;
	return S_OK;
}


// DELETEOBJCOLLECTIONPROC ----------------------------------------------------
extern "C" 
bool PASCAL _XTENSN_EXPORT DeleteObjectFromFeat (LONG lONr, CGeoDoc *pDoc, DWORD)
{
	return true;		// do nothing
}

// Liefert eine Collection von GeoObject
typedef struct tagENUMOBJECTDATA {
	CGeoObjectCreator *m_pCr;
	LPUNKNOWN  m_pUnk;
	CTriasApp *m_pApp;
	CGeoDoc   *m_pDoc;
} ENUMOBJECTDATA;

extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetObjectsFromIdentFeat (long lONr, DWORD, void *pData)
{
ENUMOBJECTDATA *pEOD = (ENUMOBJECTDATA *)pData;
CGeoObject *pObject = pEOD -> m_pDoc -> FGetObjectDisp (lONr);

	if (pObject && pEOD -> m_pCr -> InsertPtr (pObject))
		((_DGeoObject *)pObject) -> AddRef();
	
	return true;
}

extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetIdentsFromFeat (long lIdent, DWORD dwData, void *pData)
{
ENUMLONGKEYEX ELK;

	ELK.eKey = lIdent;
	ELK.eFcn = (ENUMLONGKEYEXPROC)_GetObjectsFromIdentFeat;
	ELK.ePtr = pData;
	ELK.eData = dwData;	// objecttypes for this ident
	
	return DEX_EnumIdentObjectsEx (ELK);
}


// INITOBJCOLLECTIONPROC ------------------------------------------------------
extern "C" 
INITOBJSTATUS PASCAL GetObjectsFromFeat (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	container_wrappers::CCreator &rCollCr, DWORD dwData, long *plONr)
{
	if (plONr != NULL) return INITOBJSTATUS_Error;
	
ENUMLONGKEYEX EObjs;
ENUMOBJECTDATA EOD;
GETOBJECTSDATA *pGOD = (GETOBJECTSDATA *)dwData;

	EOD.m_pCr = (CGeoObjectCreator *)&rCollCr;
	EOD.m_pUnk = pUnk;
	EOD.m_pApp = pApp;
	EOD.m_pDoc = pDoc;
	
	EObjs.eKey = (long)pGOD->dwData;	
	EObjs.eFcn = (ENUMTEXTKEYEXPROC)_GetIdentsFromFeat;	// zu rufende Funktion
	EObjs.ePtr = &EOD;									// durchzureichende Daten
	EObjs.eData = pGOD->iObjBits;
	
//???	if (DEX_EnumFeatIdentsEx (EObjs))					// mit Idents füllen
		return INITOBJSTATUS_Exists;

return INITOBJSTATUS_Error;
}

STDMETHODIMP CGeoFeatureBase::GetObjects (VARIANT vObjType, VARIANT /*vLogMode*/, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoFeatureBase::GetObjects");

	TEST_E_POINTER("CGeoFeatureBase::GetObjects", ppIObjs);

CComVariant vArg;

HRESULT hr = VariantChangeType (&vArg, &vObjType, 0, VT_I2);
long lObjBits = OTPunkt|OTLinie|OTFlaeche|OTText;

	if (SUCCEEDED(hr)) 
		lObjBits = V_I4(&vArg);
	VariantClear (&vArg);

GETOBJECTSDATA GOD;

	INITSTRUCT(GOD, GETOBJECTSDATA);
	GOD.dwData = (DWORD)GetValue();
	GOD.iObjBits = (short)lObjBits;

CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(DGeoFeature *)this, m_pApp, m_pDoc,
							GetObjectsFromFeat, (DWORD)&GOD, DeleteObjectFromFeat);

	if (NULL == pCObjects) return E_OUTOFMEMORY;
	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CGeoFeatureBase::get_Properties (_DTRiASProperties **ppIProps)
{
	return E_NOTIMPL;
}

STDMETHODIMP CGeoFeatureBase::CreateProperty (VARIANT vName, VARIANT vType, VARIANT vValue, _DTRiASProperty **ppIProp)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// CGeoFeatureObj:: _IGeoFeature methods (partailly)
STDMETHODIMP CGeoFeatureObj::get_Flags (PROPERTYCAPS *pdwValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoFeatureObj::get_Flags");

	if (NULL == pdwValue) return E_POINTER;
	
	*pdwValue = m_rgProps;
	return S_OK;
}

STDMETHODIMP CGeoFeatureObj::put_Flags (PROPERTYCAPS dwValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoFeatureObj::put_Flags");

	if (m_rgProps == dwValue) return S_OK;

	m_rgProps = dwValue;

		ASSERT (m_ObjProp.IsValid());

WPropertyInfo ObjSetHI;
HRESULT hr = m_ObjProp -> QueryInterface (IID_IPropertyInfo, ObjSetHI.ppv());
		
	if (FAILED(hr))	return false;

	return ObjSetHI -> SetPropInfo (m_pName, (DWORD)m_rgProps);
}

STDMETHODIMP CGeoFeatureObj::get_ConfigData (VARIANT *pvOptData)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoFeatureObj::get_ConfigData");

	if (NULL == pvOptData) 
		return E_POINTER;

	try {
	INT_PTR hObjs = m_lONrOrIdent;
	CClass *pCls = NULL;

		if (IsGeoObject())
			hObjs = DEX_GetObjIdent(m_lONrOrIdent);

		if (NULL == hObjs)
			return E_INVALIDARG;
		return WPropertyInfo2(m_ObjProp) -> GetConfigDataEx (hObjs, pvOptData);

	} catch (_com_error& hr) {
		V_VT(pvOptData) = VT_ERROR;
		V_ERROR(pvOptData) = DISP_E_PARAMNOTFOUND;
		return _COM_ERROR(hr);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Suchen aller Objekte, die für diese Objekteigenschaft das übergebene 
// Kriterium erfüllen

extern "C" 
BOOL PASCAL _XTENSN_EXPORT GetObjectFromSearchFeat (long lONr, BOOL, void *pData)
{
ENUMOBJECTDATA *pEOD = reinterpret_cast<ENUMOBJECTDATA *>(pData);
CGeoObject *pObject = pEOD -> m_pDoc -> FGetObjectDisp (lONr);

	if (pObject && pEOD -> m_pCr -> InsertPtr (pObject))
		((_DGeoObject *)pObject) -> AddRef();
	
	return TRUE;
}

// INITOBJCOLLECTIONPROC 
typedef struct tagGETOBJECTSFEATDATA {
	DWORD dwSize;
	LPSTR pView;
	long lMCode;
	LPSTR pToSearch;
	int iMode;
} GETOBJECTSFEATDATA;

extern "C" 
INITOBJSTATUS PASCAL GetSearchObjectsFromFeat (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	container_wrappers::CCreator &rCollCr, DWORD dwData, long *plONr)
{
	if (plONr != NULL)	
		return INITOBJSTATUS_Error;		// Einzelobjekt soll hinzugefügt werden
	
ENUMRECHTEXTMERKMAL ERTM;
GETOBJECTSFEATDATA *pGOD = reinterpret_cast<GETOBJECTSFEATDATA *>(dwData);
ENUMOBJECTDATA EOD;

	EOD.m_pCr = (CGeoObjectCreator *)&rCollCr;
	EOD.m_pUnk = pUnk;
	EOD.m_pApp = pApp;
	EOD.m_pDoc = pDoc;

	INITSTRUCT(ERTM, ENUMRECHTEXTMERKMAL);
	ERTM.pView = pGOD -> pView;	
	ERTM.lMCode = pGOD -> lMCode;	// MerkmalsCode
	ERTM.pMWert = pGOD -> pToSearch;	// Suchpattern
	ERTM.iMode = pGOD -> iMode;		// Suchmode
	ERTM.eFcn = reinterpret_cast<RECHTEXTMERKMALCALLBACK>(GetObjectFromSearchFeat);
	ERTM.pData = &EOD;

	if (DEX_EnumRechTextMerkmal (ERTM))					// mit Idents füllen
		return INITOBJSTATUS_Exists;
	return INITOBJSTATUS_Error;
}

STDMETHODIMP CGeoFeatureObj::GetObjects (VARIANT vToSearch, VARIANT vSrchMode, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoFeatureObj::GetObjects");

	TEST_E_POINTER("CGeoFeatureObj::GetObjects", ppIObjs);

	USES_CONVERSION;

CComVariant vArg;
CComVariant vMode;
int rgMode = SMExactMatch;		// default: exakt suchen
LPSTR pToSearch = NULL;			// default: alle Objekte, kein Suchkriterium

	if (SUCCEEDED(vArg.ChangeType (VT_BSTR, &vToSearch)))
		pToSearch = OLE2A(V_BSTR(&vArg));
	if (SUCCEEDED(vMode.ChangeType (VT_I4, &vSrchMode)))
		rgMode = V_I4(&vMode);

GETOBJECTSFEATDATA GOD;

	INITSTRUCT(GOD, GETOBJECTSFEATDATA);
	GOD.pView = NULL;				// aktuelle Ansicht
	GOD.lMCode = (DWORD)GetValue();
	GOD.pToSearch = pToSearch;
	GOD.iMode = rgMode;

CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(DGeoFeature *)this, m_pApp, m_pDoc,
							GetSearchObjectsFromFeat, (DWORD)&GOD, NULL);

	if (NULL == pCObjects) 
		return E_OUTOFMEMORY;

	pCObjects -> m_dwData = NULL;		// can't regenerate
	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

