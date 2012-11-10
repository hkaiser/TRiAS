// Eine Objektklasse (ProgrammierInterface) -----------------------------------
// File: CLSDISP.CXX

#include "precomp.hxx"

#include "oleautor.h"

#include <dirisole.h>
#include <visinfo.h>

#include "class.hxx"

#include "objarray.hxx"
#include "enumobjs.hxx"
#include "obj.hxx"
#include "objs.hxx"

#include "ftsarray.hxx"
#include "enumfts.hxx"
#include "feat.hxx"
#include "fts.hxx"

#include "viewarry.hxx"
#include "enuviews.hxx"
#include "view.hxx"
#include "views.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// verwendete SmartInterface's etc.

DefineSmartInterface(Dispatch);			// WDispatch
DefineSmartInterface(VisObjExt);		// IVisObjExt
DefineSmartInterface2(DVisInfo, IID_DVisInfo);				// WDVisInfo

DefineSmartInterface(TRiASConnection);	// WTRiASConnection

const CLSID CLSID_DefaultVisInfo = {0x289BE0C4,0x92F6,0x11D1,{0xBA,0x03,0x08,0x00,0x36,0xD6,0x38,0x03}};

// ProgrammierInterfaceFunktionen ---------------------------------------------
STDMETHODIMP CClass::get_isA (LONG *plRTTI)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::get_isA");
	if (NULL == plRTTI) 
		return E_POINTER;
	*plRTTI = RTTI_GeoClass;
	return NOERROR;
}

STDMETHODIMP CClass::get_Parent (IDispatch **ppIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::get_Parent");
	return m_pUnk -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

STDMETHODIMP CClass::get_Application (IDispatch **ppIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::get_Application");
	return ((_DApplication *)m_pApp) -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

STDMETHODIMP CClass::put_Parent (IDispatch *pIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::put_Parent");
	return E_NOTIMPL;
}

STDMETHODIMP CClass::put_Application (IDispatch *pIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::put_Application");
	return E_NOTIMPL;
}

// Liefert den KurzText dieser ObjektKlasse -----------------------------------
STDMETHODIMP CClass::get_Name (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::get_Name");

	if (NULL == pbstrValue) return E_POINTER;

// Class nach KurzText fragen
	*pbstrValue = NULL;
	if (NULL != GetName()) 
		*pbstrValue = SysAllocString (WideString(GetName()));

	if (NULL == *pbstrValue)
		return E_OUTOFMEMORY;

return NOERROR;
}


// Setzt/löscht den KurzText dieser ObjektKlasse ------------------------------
STDMETHODIMP CClass::put_Name (BSTR bstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::put_Name");

	if (NULL == bstrValue) return E_UNEXPECTED;

	m_pDoc -> SetClassName (GetValue(), AnsiString(bstrValue));
	return NOERROR;
}


// Liefert den Identifikator dieser Objektklasse ------------------------------
STDMETHODIMP CClass::get_Value (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::get_Value");

	if (NULL == pbstrValue) return E_POINTER;

char cbTmp[66] = { '\0' };
HRESULT hr = ClassFromIdentX (GetValue(), cbTmp);

	if (FAILED(hr)) return hr;

// OKS evtl. in '[...]' einfassen
	if (strncmp (cbTmp, OKS_SCOPE_BEGIN, OKS_SCOPE_BEGIN_LEN)) {
		memmove (&cbTmp[OKS_SCOPE_BEGIN_LEN], cbTmp, strlen(cbTmp));
		strncpy (cbTmp, OKS_SCOPE_BEGIN, OKS_SCOPE_BEGIN_LEN);
		strcat (cbTmp, OKS_SCOPE_END);
	}
	*pbstrValue = SysAllocString (WideString(cbTmp));
	if (NULL == *pbstrValue)
		return E_OUTOFMEMORY;

	return NOERROR;
}

STDMETHODIMP CClass::put_Value (BSTR bstrOKS)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::put_Value");
	if (NULL == bstrOKS)
		return E_INVALIDARG;

	USES_CONVERSION;

HPROJECT hPr = DEX_GetObjectsProject (GetValue());
LPCSTR pcClass = OLE2A(bstrOKS);
char cbTmp[66] = { OKS_SCOPE_BEGIN };

	if (strncmp(pcClass, OKS_SCOPE_BEGIN, OKS_SCOPE_BEGIN_LEN)) {
	// evtl '[' und ']' hinzufügen
		strcpy (&cbTmp[OKS_SCOPE_BEGIN_LEN], pcClass);
		strcat (cbTmp, OKS_SCOPE_END);
		pcClass = cbTmp;
	}

ULONG lIdent = NULL;
HRESULT hr = IdentFromClassX (hPr, pcClass, &lIdent);

	if (S_OK == hr && lIdent != GetValue())
		return E_INVALIDARG;	// OKS bereits anderweitig vergeben

MODOBJCLASSCODE MOCC;

	INITSTRUCT(MOCC, MODOBJCLASSCODE);
	MOCC.ulIdent = GetValue();
	MOCC.pcClass = OLE2A(bstrOKS);
	MOCC.fOverWrite = true;
	return DEX_ModObjectClassCodeEx(hPr, MOCC);
}

STDMETHODIMP CClass::get_Code (THIS_ LONG *pulIdent)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::get_Code");

	if (NULL == pulIdent)
		return E_NOTIMPL;

	*pulIdent = GetValue();
	return S_OK;
}

// Liefert den LangText dieser Objektklasse -----------------------------------
STDMETHODIMP CClass::get_FullName (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::get_FullName");

	if (NULL == pbstrValue) return E_POINTER;

// Class nach KurzText fragen
	*pbstrValue = NULL;
	if (NULL != GetFullName()) 
		*pbstrValue = SysAllocString (WideString(GetFullName()));

	if (NULL == *pbstrValue)
		return E_OUTOFMEMORY;

return NOERROR;
}

// Setzt/löscht den LangText dieser Objektklasse ------------------------------
STDMETHODIMP CClass::put_FullName (BSTR bstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::put_FullName");

	if (NULL == bstrValue) return E_UNEXPECTED;

	SetFullName (AnsiString(bstrValue));
	return NOERROR;
}

// DELETEVIEWCOLLECTIONPROC ----------------------------------------------------
extern "C" 
bool PASCAL _XTENSN_EXPORT DeleteViewFromClass (LPCSTR bName, CGeoDoc *pDoc)
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
BOOL PASCAL _XTENSN_EXPORT _GetViewsFromClass (char *bName, DWORD, void *pData)
{
ENUMVIEWDATA *pEOD = (ENUMVIEWDATA *)pData;
CGeoView *pView = pEOD -> m_pDoc -> FGetViewDisp (bName);

	if (pView && pEOD -> m_pCr -> InsertPtr (pView)) 
		((_DView *)pView) -> AddRef(); 

	return true;
}


// INITVIEWCOLLECTIONPROC -----------------------------------------------------
typedef struct tagIDENTOBJTYPE {
	ULONG m_ulIdent;
	short m_iObjTypes;
} IDENTOBJTYPE;

extern "C" 
INITVIEWSTATUS PASCAL GetViewsFromClass (
	LPUNKNOWN  pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	container_wrappers::CCreator  &rCollCr, DWORD dwData, string *pbName)
{
ENUMVIEWDATA EFD;

	EFD.m_pCr = (CGeoViewCreator *)&rCollCr;
	EFD.m_pUnk = pUnk;
	EFD.m_pApp = pApp;
	EFD.m_pDoc = pDoc;
	
	if (pbName == NULL) {			// Complete fill
	ENUMLONGKEYEX ELK;
	IDENTOBJTYPE *pIOT = (IDENTOBJTYPE *)dwData;
	
		ELK.eKey = (LONG)pIOT -> m_ulIdent;
		ELK.eFcn = (ENUMLONGKEYEXPROC)_GetViewsFromClass;	// zu rufende Funktion
		ELK.ePtr = &EFD;				// durchzureichende Daten
		ELK.eData = pIOT -> m_iObjTypes;
		if(DEX_EnumIdentSightsEx (ELK))			// mit Views füllen
			return INITVIEWSTATUS_Exists;
	} 
	return INITVIEWSTATUS_Error;		
} 


// Liefert alle Ansichten, in denen diese Klasse vertreten ist ----------------
STDMETHODIMP CClass::GetViews (VARIANT vObjType, DViews **ppIViews)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::GetViews");

	TEST_E_POINTER("CClass::GetViews", ppIViews);

CComVariant vArg;
IDENTOBJTYPE IOT;
HRESULT hr = VariantChangeType (&vArg, &vObjType, 0, VT_I2);

	IOT.m_ulIdent = GetValue();
	IOT.m_iObjTypes = SUCCEEDED(hr) ? V_I2(&vArg) : (OTPunkt|OTLinie|OTFlaeche|OTText);
	
CGeoViews *pCGeoViews = CGeoViews::CreateInstance (
							(_DGeoClass *)this, m_pApp, m_pDoc, 
							GetViewsFromClass, (DWORD)&IOT, DeleteViewFromClass);

	if (NULL == pCGeoViews) return E_OUTOFMEMORY;

	*ppIViews = (DViews *)pCGeoViews;		// übernimmt AddRef
	return S_OK;
}

// DELETEOBJCOLLECTIONPROC ----------------------------------------------------
extern "C" 
bool PASCAL _XTENSN_EXPORT DeleteObjectFromClass (LONG lONr, CGeoDoc *pDoc, DWORD)
{
CGeoObject *pObject = pDoc -> FGetObjectDisp (lONr);

	if (pObject == NULL) return false;

return (pObject -> ChangeObjIdent (DEX_GetUnknownIdent()) != INVALID_IDENT);
}


// Liefert eine Collection von GeoClass's, die in dieser GeoDB enthalten sind -
typedef struct tagENUMIDENTDATA {
	CGeoObjectCreator *m_pCr;
	LPUNKNOWN m_pUnk;
	CTriasApp *m_pApp;
	CGeoDoc *m_pDoc;
} ENUMOBJECTDATA;

extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetObjectsFromIdent (long lONr, BOOL, void *pData)
{
ENUMOBJECTDATA *pEOD = (ENUMOBJECTDATA *)pData;
CGeoObject *pObject = pEOD -> m_pDoc -> FGetObjectDisp (lONr);

	if (pObject && pEOD -> m_pCr -> InsertPtr (pObject))
		((_DGeoObject *)pObject) -> AddRef();

	return true;
}

// INITOBJCOLLECTIONPROC ------------------------------------------------------
extern "C" 
INITOBJSTATUS PASCAL GetObjectsFromIdent (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	container_wrappers::CCreator &rCollCr, DWORD dwData, long *plONr)
{
ENUMLONGKEYEX EObjs;
ENUMOBJECTDATA EOD;

	EOD.m_pCr = (CGeoObjectCreator *)&rCollCr;
	EOD.m_pUnk = pUnk;
	EOD.m_pApp = pApp;
	EOD.m_pDoc = pDoc;
		
GETOBJECTSDATA *pGOD = (GETOBJECTSDATA *)dwData;

	if (plONr == NULL) {
	// fill all objects
		EObjs.eKey = (long)pGOD->dwData;	// this IS the Ident
		EObjs.eFcn = (ENUMLONGKEYEXPROC)_GetObjectsFromIdent;	// zu rufende Funktion
		EObjs.ePtr = &EOD;					// durchzureichende Daten
		EObjs.eData = pGOD->iObjBits;

		if (DEX_EnumIdentObjectsEx (EObjs))		// mit Objekten füllen
			return INITOBJSTATUS_Exists;
	} else if (*plONr != INVALID_ONR) {
	// fill only one object
		if (_GetObjectsFromIdent (*plONr, false, &EOD)) {
			pDoc -> ChangeObjectIdent (*plONr, pGOD->dwData);	// this IS the Ident
			return INITOBJSTATUS_Exists;
		}
	} 
	return INITOBJSTATUS_Error;		// error !
}


// Liefert die Liste aller Objekte, die dieser Obvjektklasse angehören --------
STDMETHODIMP CClass::GetObjects (VARIANT vObjType, VARIANT /*vLogMode*/, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::GetObjects");

	TEST_E_POINTER("CClass::GetObjects", ppIObjs);

CComVariant vArg;

HRESULT hr = VariantChangeType (&vArg, &vObjType, 0, VT_I4);
long lObjBits = OTPunkt|OTLinie|OTFlaeche|OTText;

	if (SUCCEEDED(hr)) 
		lObjBits = V_I4(&vArg);

GETOBJECTSDATA GOD;

	INITSTRUCT(GOD, GETOBJECTSDATA);
	GOD.dwData = (DWORD)GetValue();
	GOD.iObjBits = (short)lObjBits;

CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(DGeoClass *)this, m_pApp, m_pDoc,
							GetObjectsFromIdent, (DWORD)&GOD, DeleteObjectFromClass); 

	if (NULL == pCObjects) return E_UNEXPECTED;
	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CClass::GetObject (VARIANT vObj, VARIANT vMode, DGeoObject **ppIObj)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::GetObject");

	TEST_E_POINTER("CClass::GetObject", ppIObj);

CComVariant vArg; 
CComVariant vArgMode;
HRESULT hr = VariantChangeType (&vArgMode, &vMode, 0, VT_I4);
GEOOBJECTMODE rgMode = GEOOBJECTMODE_Get;

	if (SUCCEEDED(hr)) 
		rgMode = (GEOOBJECTMODE)V_I4(&vArgMode);
		
	*ppIObj = NULL;

	if (VT_BSTR != V_VT(&vObj)) {
	// nur auf Zahl testen, wenn nicht direkt als BSTR gegeben
	// damit Objektnamen eine Zahl sein dürfen
		hr = VariantChangeType (&vArg, &vObj, 0, VT_I4); // Argument is Object Number	
		if (SUCCEEDED(hr)) {
		CGeoObject *pObject = m_pDoc -> FGetObjectDisp (V_I4(&vArg), ppIObj, GEOOBJECTMODE_Get);

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
			
		hr = HandleGeoObject (pObject, rgMode);
		if (FAILED(hr) && NULL != ppIObj && NULL != *ppIObj) {
			(*ppIObj) -> Release();
			*ppIObj = NULL;
		}
		return hr;
	}

return hr;
}

// helper function ------------------------------------------------------------
HRESULT CClass::HandleGeoObject (CGeoObject *pObject, GEOOBJECTMODE rgMode)
{
	if (NULL == pObject) return E_UNEXPECTED;
	
	switch (rgMode) {		
	case GEOOBJECTMODE_Get:		// default
		if (pObject -> GetObjIdent() != GetValue()) 
			return E_UNEXPECTED;
		break;
			
	case GEOOBJECTMODE_Remove:	// remove item
		{
		ULONG lUnknownIdent = DEX_GetUnknownIdent();

			if (lUnknownIdent != pObject -> GetObjIdent()) {
			// change class of this object to 'unknown class'
				if (!pObject -> ChangeObjIdent (lUnknownIdent)) 
					return E_UNEXPECTED;
			}
		}
		break;
			
	case GEOOBJECTMODE_Add:		// create, if not existent
		{
			if (pObject -> GetObjIdent() != GetValue ()) {
			// change class of this object
				if (!pObject -> ChangeObjIdent (GetValue())) 
					return E_UNEXPECTED;
			} else
				return E_UNEXPECTED;
		}
		break;
			
	case GEOOBJECTMODE_Replace:	// remove old, create new
	default:
		return E_UNEXPECTED;
	}

return NOERROR;
}


// DELETEFEATCOLLECTIONPROC ----------------------------------------------------
extern "C" bool PASCAL _XTENSN_EXPORT DeleteFeatureFromIdent (LPCSTR bName, void *pCls)
{
	return ((CClass *)pCls) -> FDelFeature (bName);
}

///////////////////////////////////////////////////////////////////////////////
// Liefert eine Collection von GeoObjectFeature's, die zu diesem Ident gehören 
typedef struct tagENUMFEATUREDATA {
	CGeoFeatureBaseCreator *m_pCr;
	LPUNKNOWN m_pUnk;
	CTriasApp *m_pApp;
	CGeoDoc *m_pDoc;
	CClass *m_pClass;
	long m_lIdent;
} ENUMFEATUREDATA;
															 
extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetFeaturesFromIdent (long lFCd, BOOL, void *pData)
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
CGeoFeatureBase *pFeature = pEFD -> m_pClass -> FGetFeatureDisp (cbName);

	if (NULL != pFeature && NULL != pEFD -> m_pCr -> InsertPtr (pFeature)) 
	{
		((_DGeoFeature *)pFeature) -> AddRef(); 
		return true;
	}
	return false;	
}

extern "C" 
INITFEATSTATUS PASCAL _CreateFeatureIdent (ENUMFEATUREDATA *pEFD, string &bName)
{
CGeoFeatureBase *pFeature = pEFD -> m_pClass -> FGetFeatureDisp (bName.c_str());
INITFEATSTATUS iResult = INITFEATSTATUS_Exists;

	if (pFeature == NULL) {
		pFeature = pEFD -> m_pClass -> FGetFeatureDisp (bName.c_str(), NULL, FEATUREMODE_Add);
		iResult = INITFEATSTATUS_Created;
	}
	if (NULL != pFeature && NULL != pEFD -> m_pCr -> InsertPtr (pFeature)) 
	{
		((_DGeoFeature *)pFeature) -> AddRef();
		return iResult;
	}
	
return INITFEATSTATUS_Error;
}


// INITFEATCOLLECTIONPROC
extern "C" 
INITFEATSTATUS PASCAL GetFeaturesFromIdent (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, void *pCls,
	container_wrappers::CCreator &rCollCr, DWORD dwData, string *pbName, DWORD dwFlags)
{
ENUMFEATUREDATA EFD;

	EFD.m_pCr = (CGeoFeatureBaseCreator *)&rCollCr;
	EFD.m_pUnk = pUnk;
	EFD.m_pApp = pApp;
	EFD.m_pDoc = pDoc;
	EFD.m_pClass = (CClass *)pCls;
	EFD.m_lIdent = (long)dwData;
	
	if (pbName == NULL) {							// Complete fill
	ENUMLONGKEY EFCds;

		EFCds.eKey = (long)dwData;								// this IS the Identifier
		EFCds.eFcn = (ENUMLONGKEYPROC)_GetFeaturesFromIdent;	// zu rufende Funktion
		EFCds.ePtr = &EFD;										// durchzureichende Daten

		if(DEX_EnumIdentMerkmale (EFCds))			// mit Fetaures füllen
            return INITFEATSTATUS_Exists;
	} else 
			return _CreateFeatureIdent (&EFD, *pbName);

	return INITFEATSTATUS_Error;		
}

STDMETHODIMP CClass::GetFeatures (VARIANT /*vFeatures*/, VARIANT /*vLogMode*/, DGeoFeatures **ppIFeats)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::GetFeatures");

	TEST_E_POINTER("CClass::GetFeatures", ppIFeats);

CGeoFeatures *pCFeatures = CGeoFeatures::CreateInstance (
							(DGeoClass *)this, m_pApp, m_pDoc,
							this, GetFeaturesFromIdent, (DWORD)GetValue(), 
							DeleteFeatureFromIdent); 

	if (NULL == pCFeatures) return E_OUTOFMEMORY;

	*ppIFeats = (DGeoFeatures *)pCFeatures;
	return S_OK;
}

STDMETHODIMP CClass::GetFeature (VARIANT vFeature, VARIANT vMode, DGeoFeature **ppIFeat)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::GetFeature");

	TEST_E_POINTER("CClass::GetFeature", ppIFeat);

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

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaften, die einer Objektklasse zugeordnet sind
// Liefert eine Collection von GeoFeature's, die zu diesem Objekt gehören ----------------------
typedef struct tagENUMFEATUREDATAIDENT {
	CGeoFeatureBaseCreator *m_pCr;
	LPUNKNOWN m_pUnk;
	CTriasApp *m_pApp;
	CGeoDoc *m_pDoc;
	CClass *m_pGeoClass;
	IObjectProperty *m_pIObjProp;
	DWORD m_dwFlags;
} ENUMFEATUREDATAIDENT;

extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetObjectFeaturesFromIdent (ENUMFEATUREDATAIDENT *pEFD)
{
char cbBuffer[_MAX_PATH+1];
DWORD dwFlags = (DWORD)PROPCAPS_NONE;
HRESULT hr = pEFD -> m_pIObjProp -> GetPropInfo (cbBuffer, _MAX_PATH, &dwFlags);

	if (FAILED(hr)) return false;

	if (dwFlags & PROPCAPS_INTERACTIVE)
		return true;	// interaqktive niemals nicht
	if ((PROPCAPS_NONE != pEFD -> m_dwFlags) && !(dwFlags & pEFD -> m_dwFlags))
		return true;	// welche, die wir nicht haben wollen auch nicht

CGeoFeatureBase *pFeature = pEFD -> m_pGeoClass -> FGetObjectFeatureDisp (
					cbBuffer, NULL, (PROPCAPS)dwFlags, FEATUREMODE_Get, NULL, pEFD -> m_pIObjProp);

	if (pFeature && pEFD -> m_pCr -> InsertPtr (pFeature)) 
		((_DGeoFeature *)pFeature) -> AddRef(); 
	
	return true;
}

extern "C" 
INITFEATSTATUS PASCAL _CreateObjectFeatureIdent (ENUMFEATUREDATAIDENT *pEFD, string &bName)
{
CGeoFeatureBase *pFeature = pEFD -> m_pGeoClass -> FGetObjectFeatureDisp (bName.c_str());
INITFEATSTATUS iResult = INITFEATSTATUS_Exists;

	if (pFeature == NULL) {
		pFeature = pEFD -> m_pGeoClass -> FGetObjectFeatureDisp (
						bName.c_str(), NULL, PROPCAPS_NONE, FEATUREMODE_Add);
		iResult = INITFEATSTATUS_Created;
	}
	
	if (pFeature && pEFD -> m_pCr -> InsertPtr (pFeature)) {
		((_DGeoFeature *)pFeature) -> AddRef();
		return iResult;
	}
	return INITFEATSTATUS_Error;
}

// INITFEATCOLLECTIONPROC
INITFEATSTATUS PASCAL GetObjectFeaturesFromIdent (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	void *pCls, container_wrappers::CCreator &rCollCr, DWORD dwData, 
	string *pbName, DWORD dwFlags)
{
ENUMFEATUREDATAIDENT EFD;

	EFD.m_pCr = (CGeoFeatureBaseCreator *)&rCollCr;
	EFD.m_pUnk = pUnk;
	EFD.m_pApp = pApp;
	EFD.m_pDoc = pDoc;
	EFD.m_pGeoClass = (CClass *)pCls;
	EFD.m_pIObjProp = NULL;
	EFD.m_dwFlags = dwFlags;

	if (pbName == NULL) {							// Complete fill
	IEnumObjProps *pIEnum = NULL;
	HRESULT hr = pApp -> GetEnumObjPropsIdent ((long)dwData, &pIEnum);

		if (FAILED(hr)) return INITFEATSTATUS_Error;

	IObjectProperty *pIObjProp = NULL;
														 
		for (pIEnum -> Reset(); S_OK == pIEnum -> Next (1, (LPUNKNOWN *)&pIObjProp, NULL); /**/)
		{
			EFD.m_pIObjProp = pIObjProp;
			_GetObjectFeaturesFromIdent (&EFD);
			pIObjProp -> Release();
		}
		if (pIEnum) pIEnum -> Release(); 
		
		return INITFEATSTATUS_Exists;
	} else 
		return _CreateObjectFeatureIdent (&EFD, *pbName);

	return INITFEATSTATUS_Error;		
}

// DELETEFEATCOLLECTIONPROC ----------------------------------------------------
extern "C" 
bool PASCAL _XTENSN_EXPORT DeleteObjectFeatureFromIdent (LPCSTR bName, void *pObj)
{
	return ((CClass *)pObj) -> FDelFeature (bName);
}

STDMETHODIMP CClass::GetObjectFeatures (VARIANT /*vFeatures*/, VARIANT /*vLogMode*/, DGeoFeatures **ppIFeats)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::GetObjectFeatures");

	TEST_E_POINTER("CClass::GetObjectFeatures", ppIFeats);

CGeoFeatures *pCFeatures = CGeoFeatures::CreateInstance (
							(DGeoClass *)this, m_pApp, m_pDoc,
							this, GetObjectFeaturesFromIdent, (DWORD)GetValue(), 
							DeleteObjectFeatureFromIdent); 

	if (NULL == pCFeatures) return E_OUTOFMEMORY;

	*ppIFeats = (DGeoFeatures *)pCFeatures;
	return S_OK;
}

STDMETHODIMP CClass::GetObjectFeature (VARIANT vFeature, VARIANT vMode, DGeoFeature **ppIFeat)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::GetObjectFeature");

	TEST_E_POINTER("CClass::GetObjectFeature", ppIFeat);

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

// Suchen aller Objekte eines Idents, die in einem bestimmten Fenster liegen
typedef struct tagENUMIDENTDATAEX {
	CGeoObjectCreator *m_pCr;
	LPUNKNOWN m_pUnk;
	CTriasApp *m_pApp;
	CGeoDoc *m_pDoc;
	long m_lIdent;
} ENUMOBJECTDATAEX;

extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetObjectsInWindowFromIdent (long lONr, BOOL, void *pData)
{
ENUMOBJECTDATAEX *pEOD = (ENUMOBJECTDATAEX *)pData;

	if (DEX_GetObjIdent (lONr) != pEOD -> m_lIdent)
		return true;	// nicht für uns, da anderer ident

CGeoObject *pObject = pEOD -> m_pDoc -> FGetObjectDisp (lONr);

	if (NULL != pObject && NULL != pEOD -> m_pCr -> InsertPtr(pObject)) 
		((_DGeoObject *)pObject) -> AddRef();

	return true;
}

// INITOBJCOLLECTIONPROC ------------------------------------------------------
typedef struct tagOBJSINWINDOWIDENT {
	double m_rgdCont[4];		// XMin, XMax, YMin, Ymax
	long m_lIdent;				// Sichtname
} OBJSINWINDOWIDENT;

extern "C" 
INITOBJSTATUS PASCAL GetObjectsInWindowFromIdent (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	container_wrappers::CCreator &rCollCr, DWORD dwData, long *plONr)
{
	if (plONr != NULL) 
		return INITOBJSTATUS_Error;	// can't add single object

ENUMOBJECTDATAEX EOD;
OBJSINWINDOWIDENT *pData = (OBJSINWINDOWIDENT *)dwData;

	EOD.m_pCr = (CGeoObjectCreator *)&rCollCr;
	EOD.m_pUnk = pUnk;
	EOD.m_pApp = pApp;
	EOD.m_pDoc = pDoc;
	EOD.m_lIdent = pData -> m_lIdent;

// fill all objects
ENUMRECHGEOMETRIE ERG;

	INITSTRUCT(ERG, ENUMRECHGEOMETRIE);
	ERG.lCont = pData -> m_rgdCont;
	ERG.iMode = (ERGExact|ERGConverted);
	ERG.eFcn = (RECHGEOMETRIEPROC)_GetObjectsInWindowFromIdent;
	ERG.pData = &EOD;					// durchzureichende Daten

	if (DEX_EnumRechGeometrie (ERG))	// mit Objekten füllen
		return INITOBJSTATUS_Exists;

return INITOBJSTATUS_Error;		// error !
}

STDMETHODIMP CClass::GetObjectsInRect (
		double dX1, double dY1, VARIANT vX2, VARIANT vY2, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::GetObjectsInRect");

	TEST_E_POINTER("CClass::GetObjectsInRect", ppIObjs);

// Parameter enthalten Eckkoordinaten
OBJSINWINDOWIDENT ownd;

	ownd.m_rgdCont[0] = dX1;
	ownd.m_rgdCont[2] = dY1;

// 2. Koordinatenpaar ist optional
CComVariant vArg; 
HRESULT hr = VariantChangeType (&vArg, &vX2, 0, VT_R8);

	ownd.m_rgdCont[1] = FAILED(hr) ? ownd.m_rgdCont[0] : V_R8(&vArg);

	hr = VariantChangeType (&vArg, &vY2, 0, VT_R8);
	ownd.m_rgdCont[3] = FAILED(hr) ? ownd.m_rgdCont[2] : V_R8(&vArg);
	ownd.m_lIdent = GetValue();

// Collection anlegen
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
				(DGeoClass *)this, m_pApp, m_pDoc, GetObjectsInWindowFromIdent, 
				(DWORD)&ownd, DeleteObjectFromClass); 
	
	if (pCObjects == NULL) return E_OUTOFMEMORY;

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

// VisualisierungsInfo bearbeiten ---------------------------------------------
HRESULT CClass::GetVisInfoClsId (OBJECTTYPE rgOTyp, CLSID *pClsId)
{
	switch (rgOTyp) {
	case OBJECTTYPE_Point:	*pClsId = CLSID_PointVisInfo; break;
	case OBJECTTYPE_Line:	*pClsId = CLSID_LineVisInfo; break;
	case OBJECTTYPE_Area:	*pClsId = CLSID_AreaVisInfo; break;
	case OBJECTTYPE_Text:	*pClsId = CLSID_TextVisInfo; break;
	default:				*pClsId = CLSID_DefaultVisInfo; break;
	}

return NOERROR;
}

VISINFOTYPE GetVisType (OBJECTTYPE rgOTyp)
{
	switch (rgOTyp) {
    case OBJECTTYPE_Point:	return VISINFOTYPE_Point;
	case OBJECTTYPE_Line:	return VISINFOTYPE_Line;
	case OBJECTTYPE_Area:	return VISINFOTYPE_Area;
	case OBJECTTYPE_Text:	return VISINFOTYPE_Text;
	default:				break;
	}
	return VISINFOTYPE_Default;
}

STDMETHODIMP CClass::GetVisInfo (
	OBJECTTYPE rgOTyp, VARIANT vView, DVisInfo **ppIVisInfo)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::GetVisInfo");

	TEST_E_POINTER("CClass::GetVisInfo", ppIVisInfo);

WDVisInfo VisInfo;

	try {
	CLSID ClsId;
	WVisObjExt VisExt;

		THROW_FAILED_HRESULT(GetVisInfoClsId (rgOTyp, &ClsId));
		THROW_FAILED_HRESULT(((OLE2AutoExtension *)g_pTE) -> GetIVisInfo (VisExt.ppi()));
		THROW_FAILED_HRESULT(VisExt -> GetVisInfoClass (
			GetValue(), GetVisType(rgOTyp), vView, VisInfo.ppi()));

	// in die Hierarchie der TRiASObjekt einordnen
		{
		WDispatch Disp;

			THROW_FAILED_HRESULT(GetDispatchIF (Disp.ppi()));
			THROW_FAILED_HRESULT(VisInfo -> put_Parent (Disp));

			THROW_FAILED_HRESULT(m_pApp -> GetDispatchIF (Disp.ppi()));
			THROW_FAILED_HRESULT(VisInfo -> put_Application (Disp));
		}

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	*ppIVisInfo = VisInfo.detach();
	return S_OK;
}

VISINFOTYPE GetVisType (DVisInfo *pIVisInfo)
{
long lRTTI = RTTI_Unknown;

	pIVisInfo -> get_isA(&lRTTI);

	switch (lRTTI) {
    case RTTI_PointVisInfo:	return VISINFOTYPE_Point;
	case RTTI_LineVisInfo:	return VISINFOTYPE_Line;
	case RTTI_AreaVisInfo:	return VISINFOTYPE_Area;
	case RTTI_TextVisInfo:	return VISINFOTYPE_Text;
	default:				break;
	}
	return VISINFOTYPE_Default;
}

STDMETHODIMP CClass::SetVisInfo (DVisInfo *pIVisInfo, VARIANT vView)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::SetVisInfo");

	TEST_E_POINTER("CClass::SetVisInfo", pIVisInfo);

	try {
	WVisObjExt VisExt;

		THROW_FAILED_HRESULT(((OLE2AutoExtension *)g_pTE) -> GetIVisInfo (VisExt.ppi()));
		THROW_FAILED_HRESULT(VisExt -> SetVisInfoClass (
			GetValue(), GetVisType(pIVisInfo), pIVisInfo, vView));

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return NOERROR;
}

STDMETHODIMP CClass::ResetVisInfo (OBJECTTYPE rgOTyp, VARIANT vView)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::ResetVisInfo");

	try {
	WVisObjExt VisExt;

		THROW_FAILED_HRESULT(((OLE2AutoExtension *)g_pTE) -> GetIVisInfo (VisExt.ppi()));
		THROW_FAILED_HRESULT(VisExt -> ResetVisInfoClass (
			GetValue(), GetVisType(rgOTyp), vView));

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}
	return S_OK;
}

STDMETHODIMP CClass::get_Properties (DTRiASProperties **ppIProps)
{
	ATLTRACENOTIMPL("CClass::get_Properties");
}

STDMETHODIMP CClass::CreateProperty (VARIANT vName, VARIANT vType, VARIANT vValue, _DTRiASProperty **ppIProp)
{
	ATLTRACENOTIMPL("CClass::CreateProperty");
}

///////////////////////////////////////////////////////////////////////////////
// Connection
STDMETHODIMP CClass::get_Connection (ITRiASConnection **ppIConn)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::get_Connection");

	if (NULL == ppIConn)
		return E_POINTER;
	*ppIConn = NULL;

HPROJECT hPr = DEX_GetObjectsProject (GetValue());

	if (HACTCONNECTION == hPr)
		return E_UNEXPECTED;

	if (!DEX_GetDataSourcePtr (hPr, *ppIConn)) {
		_ASSERTE(NULL == *ppIConn);
		return E_UNEXPECTED;
	}
	return S_OK;
}

// Schreibschutzmode der Objektklasse
STDMETHODIMP CClass::get_Updatable (VARIANT_BOOL *pfValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::get_Updatable");

	if (NULL == pfValue) 
		return E_POINTER;

// Class nach KurzText fragen
	*pfValue = DEX_GetROModeIdent(GetValue()) ? FALSE : TRUE;
	return NOERROR;
}

STDMETHODIMP CClass::put_Updatable (VARIANT_BOOL fValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::put_Updatable");

MODIFYROMODE MRM;

	INITSTRUCT(MRM, MODIFYROMODE);
	MRM.lTarget = GetValue();
	MRM.fROMode = fValue ? FALSE : TRUE;
	DEX_SetROModeIdent(MRM);
	return NOERROR;
}

STDMETHODIMP CClass::get_IsQueryDef (VARIANT_BOOL *pfValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CClass::get_IsQueryDef");

	if (NULL == pfValue) 
		return E_POINTER;

// Class ist Rechercheobjektmenge, wenn der Parent das TRiASProject ist
	*pfValue = (HACTPROJECT == DEX_GetObjectsProject(GetValue())) ? TRUE : FALSE;
	return NOERROR;
}

