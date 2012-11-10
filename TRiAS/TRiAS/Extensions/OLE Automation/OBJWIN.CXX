// Ein ObjektrechercheFenster in TRiAS ----------------------------------------
// File: OBJWIN.CXX

#include "precomp.hxx"

#include <dirisole.h>
#include <resstrg.h>

#include "oleautor.h"   // Resource constants

#include "clsarray.hxx"
#include "enumclss.hxx"
#include "class.hxx"
#include "classes.hxx"

#include "objarray.hxx"
#include "enumobjs.hxx"
#include "obj.hxx"
#include "objs.hxx"

#include "objwin.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if _TRiAS_VER >= 0x0300
using std::bad_alloc;
#endif // _TRiAS_VER >= 0x0300

///////////////////////////////////////////////////////////////////////////////
// zugehörige CriticalSection
//CComGlobalsThreadModel::AutoCriticalSection CGeoObjectWin::m_cs;

///////////////////////////////////////////////////////////////////////////////
// benötigte SmartInterfaces
DefineSmartInterface(ObjectProperty);			// WObjectProperty
DefineSmartInterface2(_DGeoObject, IID_DGeoObject);			// W_DGeoObject

///////////////////////////////////
// Objektrecherchefenster in OLE //
///////////////////////////////////
CGeoObjectWin::CGeoObjectWin (void)
	: m_fValid(false)
{
	CONSTRUCT_TRACE(CGeoObjectWin);
	
	m_pUnk = NULL;
	m_pApp = NULL;
	m_pDoc = NULL;

	m_hORWnd = INVALID_HWND;
	m_pName = NULL;
}

CGeoObjectWin::~CGeoObjectWin (void)
{
	DESTRUCT_TRACE(CGeoObjectWin);
	
//	RELEASE (m_pUnk);	// Parent wieder loslassen
//	RELEASE_CAST(_DApplication, m_pApp);	// Applikation wieder loslassen
//	RELEASE_CAST(_DDocument, m_pDoc);		// Document wieder loslassen
}

bool CGeoObjectWin::FInit (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, HWND hWnd, GEOOBJWINMODE rgMode)
{
	if (pUnk == NULL || pApp == NULL || pDoc == NULL) 
		return false;

	m_hORWnd = hWnd;
		
// create object, if applicable
	switch (rgMode) {
	case GEOOBJWINMODE_Get:
	case GEOOBJWINMODE_Replace:	
		{
			if (!IsWindow (m_hORWnd) || !DEX_IsORWindow (m_hORWnd))	
				return false;
		}
		break;
		
	case GEOOBJWINMODE_Add:
		{
			if (INVALID_HWND != m_hORWnd) return false;
								
		CREATEOBJEKTINFOEX COI;
		CString strCaption; 
		CPoint pt (0, 0);

			TRY {
				strCaption.LoadString (IDS_OBJWINCAPTION);
			} CATCH (CMemoryException, e) {
				return false;
			} END_CATCH;

			INITSTRUCT (COI, CREATEOBJEKTINFOEX);
			COI.lpCaption = (char *)(const char *)strCaption;
			COI.plObjs = NULL;
			COI.iNumObjs = 0;
			COI.cMColor = RGB(255, 0, 0);
			COI.pntPos = pt;
			COI.m_iFlags = ROCreateHidden;
			
			m_hORWnd = DEX_CreateObjektInfo (COI);	// ORFenster erzeugen
			if (INVALID_HWND == m_hORWnd)
				return false;

			if (NULL == GetName (true))		// Namen intern speichern (mit '(.../...)')
				return false;
		}
		break;

	case GEOOBJWINMODE_Remove:			// Ne Tut!
		return false;

	default:
		return false;
	}

	m_pUnk = pUnk;		// parent
	m_pApp = pApp;		// Applikation festhalten
	m_pDoc = pDoc;		// Document festhalten
	
return true;
}

bool CGeoObjectWin::FInit (
	LPUNKNOWN  pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	LPCSTR bName, GEOOBJWINMODE rgMode)
{
	if (pUnk == NULL || pApp == NULL || pDoc == NULL) 
		return false;

	if (!SetName (bName, false, true))		// copy ObjWin Name
		return false;
		
// create object, if applicable
	switch (rgMode) {
	case GEOOBJWINMODE_Get:
	case GEOOBJWINMODE_Replace:	
		{
			m_hORWnd = pDoc -> GethWndFromObjWinName (bName);

			if (m_hORWnd == INVALID_HWND) return false;
			if (!IsWindow (m_hORWnd) || !DEX_IsORWindow (m_hORWnd)) 
				return false;	
		}
		break;

	case GEOOBJWINMODE_Add:
		{
			if (INVALID_HWND != m_hORWnd)	return false;
			
		CREATEOBJEKTINFOEX COI;
		CPoint pt (0, 0);

			INITSTRUCT (COI, CREATEOBJEKTINFOEX);
			COI.lpCaption = (char *)(const char *)bName;
			COI.plObjs = NULL;
			COI.iNumObjs = 0;
			COI.cMColor = RGB(255, 0, 0);
			COI.pntPos = pt;
			COI.m_iFlags = ROCreateHidden;
		
			m_hORWnd = DEX_CreateObjektInfo (COI);	// ORFenster erzeugen
			if (INVALID_HWND == m_hORWnd)
				return false;
			
			if (NULL == GetName(true))		// Namen intern speichern (mit '(.../...)')
				return false;
		}
		break;

	case GEOOBJWINMODE_Remove:			// Ne Tut!
		return false;

	default:
		return false;
	}

	m_pUnk = pUnk;		// parent
	m_pApp = pApp;		// Applikation festhalten
	m_pDoc = pDoc;		// Document festhalten
	
return true;
}

CGeoObjectWin *CGeoObjectWin::CreateInstance (
	LPUNKNOWN  pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	HWND hWnd, GEOOBJWINMODE rgMode)
{
CComObject<CGeoObjectWin> *pObjWin = NULL;

	try {
	// Create an instance of CGeoObject.  Exit if an error occurs.
	HRESULT hr = CComObject<CGeoObjectWin>::CreateInstance (&pObjWin);

		if (FAILED(hr)) _com_issue_error(hr);
		if (!pObjWin -> FInit (pUnk, pApp, pDoc, hWnd, rgMode)) 
			_com_issue_error(E_FAIL);

		pObjWin -> AddRef();	// fertig initialisiert

	} catch (_com_error&) {
		DELETE_OBJ (pObjWin);
		return NULL;
	}
	
// If execution has reached this point, then no errors have occurred.
	pObjWin -> Validate();
	return pObjWin;
}

CGeoObjectWin *CGeoObjectWin::CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	LPCSTR bName, GEOOBJWINMODE rgMode)
{
CComObject<CGeoObjectWin> *pObjWin = NULL;

	try {
	// Create an instance of CGeoObject.  Exit if an error occurs.
	HRESULT hr = CComObject<CGeoObjectWin>::CreateInstance (&pObjWin);

		if (FAILED(hr)) _com_issue_error(hr);
		if (!pObjWin -> FInit (pUnk, pApp, pDoc, bName, rgMode)) 
			_com_issue_error(E_FAIL);

		pObjWin -> AddRef();	// fertig initialisiert

	} catch (_com_error&) {
		DELETE_OBJ (pObjWin);
		return NULL;
	}
	
// If execution has reached this point, then no errors have occurred.
	pObjWin -> Validate();
	return pObjWin;
}

// sonstige Member
bool CGeoObjectWin::ClassIsMemberOfObjWin (CClass *pClass)
{
HWND hWnd = GetValue();

	if (hWnd == NULL) return false;
	
return true;
}

bool CGeoObjectWin::FRemoveIdentFromObjWin (ULONG lIdent)
{
HWND hWnd = GetValue();

	if (hWnd == NULL) return false;
	
return true;
}

bool CGeoObjectWin::ObjectIsMemberOfObjWin (CGeoObject *pObject)
{
HWND hWnd = GetValue();

	if (hWnd == NULL) return false;
	
return true;
}

bool CGeoObjectWin::AddObjectToObjWin (CGeoObject *pObject)
{
HWND hWnd = GetValue();

	if (hWnd == NULL) return false;

	DEXOR_AddObjectToList (hWnd, pObject -> GetValue());	

return true;
}

bool CGeoObjectWin::RemoveObjectFromObjWin (CGeoObject *pObject)
{
HWND hWnd = GetValue();

	if (hWnd == NULL) return false;
	
	DEXOR_RemoveFromListObject (hWnd, pObject -> GetValue());

return true;
}


HWND CGeoObjectWin::GetValue (bool fForce)
{
	if (!fForce && !m_fValid) 
		return NULL;

	if (!IsWindow (m_hORWnd) || !DEX_IsORWindow (m_hORWnd)) {
		m_fValid = false;
		return NULL;
	}
	
	return m_hORWnd;
}

char *CGeoObjectWin::GetName (bool fForce)
{
	if (!fForce && !m_fValid) 
		return NULL;

	if (fForce) {
		DELETE_OBJ(m_pName);
	}

	if (m_pName == NULL) { 		// noch nicht eingelesen
		try {
			m_pName = new char [LTEXTLEN +1];
			if (NULL == m_pName) return NULL;
		} catch (bad_alloc) {
			return NULL;
		}

		if (0 == GetWindowText (m_hORWnd, m_pName, LTEXTLEN))
			return false;
	}	

return m_pName;
}

bool CGeoObjectWin::SetName (
	const char *pName, bool fCreate, bool fIgnoreValid)
{
	if (!fIgnoreValid && !m_fValid) 
		return false;

// als erstes alten Name freigeben
	DELETE_OBJ(m_pName);
		
// neuen Namen kopieren
	if (pName) {
		try {
			m_pName = new char [strlen(pName)+1];
			if (m_pName == NULL) return false;
		
		} catch (bad_alloc) {
			return false;
		}
		strcpy (m_pName, pName);
	}

// write to Caption
	if (fCreate) 
		DEXOR_SetText (m_hORWnd, pName);
	        
return true;
}

void CGeoObjectWin::Invalidate (void) 
{ 
	m_fValid = false; 
}

// remove physically
bool CGeoObjectWin::Remove (void)
{
	if (!m_fValid) 
		return false;
	
bool fResult = DEX_RemoveORWnd (m_hORWnd);

	Invalidate();
	return fResult;
}

///////////////////////////////////////////////////////////////////////////////
// ProgrammierInterfaceFunktionen 
STDMETHODIMP CGeoObjectWin::get_isA (LONG *plRTTI)
{
	if (NULL == plRTTI) 
		return E_POINTER;
	*plRTTI = RTTI_GeoObjectWin;
	return S_OK;
}


// Das StandardProperty Parent liefert das übergeordnete Objekt, über welches 
// diese DocumenCollection angelegt wurde.
STDMETHODIMP CGeoObjectWin::get_Parent (IDispatch **ppIDisp)
{
	return m_pUnk -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

// Dieses StandardProperty liefert das ApplicationInterface (das allen anderen
// Objekten übergeordnete)
STDMETHODIMP CGeoObjectWin::get_Application (IDispatch **ppIDisp)
{
	return ((_DApplication *)m_pApp) -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

STDMETHODIMP CGeoObjectWin::put_Parent (IDispatch *pIDisp)
{
	return E_NOTIMPL;
}

STDMETHODIMP CGeoObjectWin::put_Application (IDispatch *pIDisp)
{
	return E_NOTIMPL;
}

// Eigentliches IDispatchInterface --------------------------------------------
// Liefert FensterHandle ------------------------------------------------------
STDMETHODIMP CGeoObjectWin::get_Value (long *phWnd)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == phWnd) 
		return E_POINTER;
	*phWnd = NULL;
	if (!m_fValid)
		return E_UNEXPECTED;

	*phWnd = reinterpret_cast<long>(GetValue());
	return S_OK;
}

// Caption des ORFensters liefern ---------------------------------------------
STDMETHODIMP CGeoObjectWin::get_Name (BSTR *pbstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pbstrValue) 
		return E_POINTER;
	*pbstrValue = NULL;
	if (!m_fValid)
		return E_UNEXPECTED;

	if (NULL != GetName()) 
		*pbstrValue = SysAllocString (WideString(GetName()));

	if (NULL == *pbstrValue)
		return E_OUTOFMEMORY;

	return S_OK;
}

STDMETHODIMP CGeoObjectWin::put_Name (BSTR bstrValue)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == bstrValue) 
		return E_INVALIDARG;
	if (!m_fValid)
		return E_UNEXPECTED;

	SetName (AnsiString(bstrValue));
	return S_OK;
}

STDMETHODIMP CGeoObjectWin::get_Visible (VARIANT_BOOL *pfVisible)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pfVisible) 
		return E_POINTER;
	*pfVisible = VARIANT_FALSE;
	if (!m_fValid)
		return E_UNEXPECTED;

// aktuellen Stand liefern
	*pfVisible = IsWindowVisible (GetValue()) ? -1 : 0;	
	return S_OK;
}

STDMETHODIMP CGeoObjectWin::put_Visible (VARIANT_BOOL fVisibleArg)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (!m_fValid)
		return E_UNEXPECTED;

// versuchen, Parameter auszuwerten
HWND hWnd =	GetValue();

	ASSERT(IsWindow(hWnd) && DEX_IsORWindow(hWnd));
	if (NULL == hWnd || !DEX_IsORWindow(hWnd))
		return E_UNEXPECTED;

bool fIsVisible = IsWindowVisible(hWnd);

	if (fIsVisible && !fVisibleArg) 
		ShowWindow (hWnd, SW_HIDE);
	else if (!fIsVisible && fVisibleArg)
		ShowWindow (hWnd, SW_SHOW);

	return S_OK;
}

STDMETHODIMP CGeoObjectWin::GetActObject (DGeoObject **ppIObj)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	TEST_E_POINTER("CGeoObjectWin::GetActObject", ppIObj);

	*ppIObj = NULL;
	if (!m_fValid)
		return E_UNEXPECTED;

HWND hWnd =	GetValue();

	ASSERT(IsWindow(hWnd) && DEX_IsORWindow(hWnd));
	if (NULL == hWnd || !DEX_IsORWindow(hWnd))
		return E_UNEXPECTED;

long lONr = DEX_GetActiveObject(hWnd);
CGeoObject *pObject = m_pDoc -> FGetObjectDisp (lONr, ppIObj, GEOOBJECTMODE_Get);

	if (NULL == pObject || !ObjectIsMemberOfObjWin (pObject)) {
		if (NULL != *ppIObj) 
			(*ppIObj) -> Release();
		return E_UNEXPECTED;
	}
	
return S_OK;
}

STDMETHODIMP CGeoObjectWin::SetActObject (DGeoObject *pIObj)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	TEST_E_POINTER("CGeoObjectWin::SetActObject", pIObj);
	if (!m_fValid)
		return E_UNEXPECTED;

HWND hWnd =	GetValue();

	ASSERT(IsWindow(hWnd) && DEX_IsORWindow(hWnd));
	if (NULL == hWnd || !DEX_IsORWindow(hWnd))
		return E_UNEXPECTED;

LONG lONr = 0L;
HRESULT hr = pIObj -> get_Value(&lONr);

	if (FAILED(hr) || INVALID_ONR == lONr) return hr;
	DEXOR_ActivateObject (hWnd, lONr);

	return S_OK;
}

// DELETECLSCOLLECTIONPROC ----------------------------------------------------
extern "C" 
bool PASCAL _XTENSN_EXPORT DeleteClassFromObjWin (ULONG lIdent, CGeoDoc *pDoc, DWORD)
{
	return false;		// not implemented yet (TODO)
}


// Liefert eine Collection von GeoClass's, die in diesem ObjWin enthalten sind 
typedef struct tagENUMIDENTDATA {
	CClassCreator *m_pCr;
	LPUNKNOWN m_pUnk;
	CTriasApp *m_pApp;
	CGeoDoc *m_pDoc;
} ENUMIDENTDATA;

extern "C" 
bool PASCAL _XTENSN_EXPORT _GetAllIdentsObjWin (long lIdent, bool, void *pData)
{
ENUMIDENTDATA *pEID = (ENUMIDENTDATA *)pData;
CClass *pClass = pEID -> m_pDoc -> FGetClassDisp ((ULONG)lIdent);

	if (pClass && pEID -> m_pCr -> InsertPtr (pClass)) {
		((_DGeoClass *)pClass) -> AddRef();
		return true;
	}
	return false;
}

// INITCLASSCOLLECTIONPROC ----------------------------------------------------
extern "C" 
INITCLSSTATUS PASCAL GetAllIdentsObjWin (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, container_wrappers::CCreator &rCollCr, 
	DWORD dwhORWnd, ULONG *plIdent)
{
	if (dwhORWnd == NULL) 
		return INITCLSSTATUS_Error;	// illegal hWnd
	
ENUMIDENTDATA EID;

	EID.m_pCr = (CClassCreator *)&rCollCr;
	EID.m_pUnk = pUnk;
	EID.m_pApp = pApp;
	EID.m_pDoc = pDoc; 
		
	if (plIdent == NULL) {		// Complete fill
	ENUMNOKEY EIds;

		EIds.eFcn = (ENUMNOKEYPROC)_GetAllIdentsObjWin;	// zu rufende Funktion
		EIds.ePtr = &EID;				// durchzureichende Daten
	
	// mit Idents dieses ObjWin's füllen
		if (DEXOR_EnumIdents ((HWND)dwhORWnd, EIds))
			return INITCLSSTATUS_Exists;
			
	} else if (*plIdent != INVALID_IDENT) {			// Fill only dwSingle
		if (_GetAllIdentsObjWin (*plIdent, true, &EID))
			return INITCLSSTATUS_Exists;
	}
	return INITCLSSTATUS_Error;
}


// Liefert die Liste aller in diesem Fenster enthaltenen Objektklassen 
// (Identifikatoren)
STDMETHODIMP CGeoObjectWin::GetClasses (VARIANT /*vClss*/, VARIANT /*vLogMode*/, DGeoClasses **ppIClss)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	TEST_E_POINTER("CGeoObjectWin::GetClasses", ppIClss);
	*ppIClss = NULL;
	if (!m_fValid)
		return E_UNEXPECTED;

CClasses *pCIdents = CClasses::CreateInstance (
						(DGeoObjectWin *)this, m_pApp, m_pDoc, 
						GetAllIdentsObjWin, (DWORD)(void *)GetValue(),
						DeleteClassFromObjWin);

	if (NULL == pCIdents) 
		return E_OUTOFMEMORY;

	*ppIClss = (DGeoClasses *)pCIdents;
	return S_OK;
}

// helper function ------------------------------------------------------------
HRESULT CGeoObjectWin::HandleClass (CClass *pClass, GEOCLASSMODE rgMode)
{
	if (NULL == pClass) 
		return E_UNEXPECTED;
	
	switch (rgMode) {		
	case GEOCLASSMODE_Get:		// default
		if (!ClassIsMemberOfObjWin (pClass))
			return E_UNEXPECTED;
		break;
			
	case GEOCLASSMODE_Remove:	// remove all objects with lIdent from ObjWin
		FRemoveIdentFromObjWin (pClass -> GetValue());
		break;
			
	case GEOCLASSMODE_Add:		// nonsense
	case GEOCLASSMODE_Replace:
	default:
		return E_UNEXPECTED;
	}
	return S_OK;
} 
	
// Liefert eine Klasse des ObjWin's -------------------------------------------
STDMETHODIMP CGeoObjectWin::GetClass (VARIANT vCls, VARIANT vMode, DGeoClass **ppICls)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

CComVariant vArg; 
CComVariant vArgMode; 

HRESULT hr = VariantChangeType (&vArgMode, &vMode, 0, VT_I4);
GEOCLASSMODE rgMode = GEOCLASSMODE_Get;

	if (SUCCEEDED(hr)) 
		rgMode = (GEOCLASSMODE)V_I4(&vArgMode);

	if (NULL != ppICls) *ppICls = NULL;

	hr = VariantChangeType (&vArg, &vCls, 0, VT_I4);	// Zahl als Ident
	if (SUCCEEDED(hr)){
	CClass *pClass = m_pDoc -> FGetClassDisp (V_I4(&vArg), ppICls, GEOCLASSMODE_Get);

		hr = HandleClass (pClass, rgMode);
		if (FAILED(hr) && NULL != ppICls && NULL != *ppICls) {
			(*ppICls) -> Release();
			*ppICls = NULL;
		}
		return hr;			
	}
	
	hr = VariantChangeType (&vArg, &vCls, 0, VT_BSTR); 	// Argument is Class Name
	if (SUCCEEDED(hr)) {
	CClass *pClass = m_pDoc -> FGetClassDisp (AnsiString(V_BSTR(&vArg)), ppICls, GEOCLASSMODE_Get);
			
		hr = HandleClass (pClass, rgMode);
		if (FAILED(hr) && NULL != ppICls && NULL != *ppICls) {
			(*ppICls) -> Release();
			*ppICls = NULL;
		}
		return hr;			
	}
	return hr;
}

// DELETEOBJCOLLECTIONPROC ----------------------------------------------------
extern "C" 
bool PASCAL _XTENSN_EXPORT DeleteObjectFromObjWin (LONG lONr, CGeoDoc *pDoc, DWORD dwhORWnd)
{
	if (IsWindow((HWND)dwhORWnd) && DEX_IsORWindow(dwhORWnd))
		DEXOR_RemoveFromListObject((HWND)dwhORWnd, lONr);
	return true;
}

// Liefert eine Collection von GeoObject's, die in diesem ObjWin enthalten sind
typedef struct tagENUMDOCDATA {
	CGeoObjectCreator *m_pCr;
	LPUNKNOWN m_pUnk;
	CTriasApp *m_pApp;
	CGeoDoc *m_pDoc;
} ENUMDOCDATA;

extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetObjectsFromObjWin (LONG lONr, BOOL, void *pData)
{
ENUMDOCDATA *pEOD = (ENUMDOCDATA *)pData;
CGeoObject *pObject = pEOD -> m_pDoc -> FGetObjectDisp (lONr);

	if (pObject && pEOD -> m_pCr -> InsertPtr (pObject)) {
		((_DGeoObject *)pObject) -> AddRef();
		return true;
	}
	
return false;
}

// INITOBJCOLLECTIONPROC ------------------------------------------------------
extern "C" 
INITOBJSTATUS PASCAL GetObjectsFromObjWin (
	LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
	container_wrappers::CCreator &rCollCr, DWORD dwhORWnd, long *plONr)
{
	if (dwhORWnd == NULL) return INITOBJSTATUS_Error;	// illegal hWnd

ENUMDOCDATA EDD;

	EDD.m_pCr = (CGeoObjectCreator *)&rCollCr;
	EDD.m_pUnk = pUnk;
	EDD.m_pApp = pApp;
	EDD.m_pDoc = pDoc;

	if (plONr == NULL) {
	// complete fill 
	ENUMLONGKEY ENK;
		
		ENK.eKey = dwhORWnd;
		ENK.eFcn = (ENUMLONGKEYPROC)_GetObjectsFromObjWin;	// zu rufende Funktion
		ENK.ePtr = &EDD;									// durchzureichende Daten

		if (DEX_EnumAllORObjects (ENK))		// mit allen Objekten füllen
			return INITOBJSTATUS_Exists;
	} else if (*plONr != INVALID_ONR) {
	// fill only dwSingle
		if (_GetObjectsFromObjWin (*plONr, true, &EDD)) {
			if (IsWindow((HWND)dwhORWnd) && DEX_IsORWindow(dwhORWnd))
				DEXOR_AddObjectToList((HWND)dwhORWnd, *plONr);		// Add to ORWnd
			return INITOBJSTATUS_Exists;
		}
	} 

return INITOBJSTATUS_Error;
}

STDMETHODIMP CGeoObjectWin::GetObjects (VARIANT /*vObjs*/, VARIANT /*vLogMode*/, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	TEST_E_POINTER("CGeoObjectWin::GetObjects", ppIObjs);
	*ppIObjs = NULL;
	if (!m_fValid)
		return E_UNEXPECTED;

CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
					(DGeoObjectWin *)this, m_pApp, m_pDoc,
					GetObjectsFromObjWin, (DWORD)(void *)GetValue(), DeleteObjectFromObjWin);

	if (NULL == pCObjects) return E_UNEXPECTED;
	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

// helper function ------------------------------------------------------------
HRESULT CGeoObjectWin::HandleGeoObject (CGeoObject *pObject, GEOOBJECTMODE rgMode)
{
	if (NULL == pObject) return E_UNEXPECTED;
	
	switch (rgMode) {		
	case GEOOBJECTMODE_Get:		// default
		if (!ObjectIsMemberOfObjWin (pObject))
			return E_UNEXPECTED;
		break;
			
	case GEOOBJECTMODE_Remove:	// remove item
		if (!RemoveObjectFromObjWin (pObject)) 
			return E_UNEXPECTED;
		break;
			
	case GEOOBJECTMODE_Add:		// create, if not existent
		if (!AddObjectToObjWin (pObject)) 
			return E_UNEXPECTED;
		break;
			
	case GEOOBJECTMODE_Replace:	// remove old, create new
	default:
		return E_UNEXPECTED;
	}
	return S_OK;
}

STDMETHODIMP CGeoObjectWin::GetObject (VARIANT vObj, VARIANT vMode, DGeoObject **ppIObj)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	TEST_E_POINTER("CGeoObjectWin::GetObject", ppIObj);
	*ppIObj = NULL;
	if (!m_fValid)
		return E_UNEXPECTED;

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


STDMETHODIMP CGeoObjectWin::AddMenuItem (
	int iSubMenu, int iPos, BSTR bstrText, VARIANT vHelpText)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	return E_NOTIMPL;
}

// DELETEOBJCOLLECTIONPROC ----------------------------------------------------
extern "C" 
bool PASCAL _XTENSN_EXPORT UnSelectObjectFromObjWin (LONG lONr, CGeoDoc *pDoc, DWORD dwhORWnd)
{
	if (IsWindow((HWND)dwhORWnd) && DEX_IsORWindow(dwhORWnd))
		DEXOR_UnselectObject((HWND)dwhORWnd, lONr);
	return true;
}

// INITOBJCOLLECTIONPROC ------------------------------------------------------
extern "C" 
INITOBJSTATUS PASCAL GetSelObjectsFromObjWin (
		LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
		container_wrappers::CCreator &rCollCr, DWORD dwhORWnd, long *plONr)
{
	if (dwhORWnd == NULL) return INITOBJSTATUS_Error;	// illegal hWnd

ENUMDOCDATA EDD;

	EDD.m_pCr = (CGeoObjectCreator *)&rCollCr;
	EDD.m_pUnk = pUnk;
	EDD.m_pApp = pApp;
	EDD.m_pDoc = pDoc;

	if (plONr == NULL) {
	// complete fill 
	ENUMLONGKEY ENK;
		
		ENK.eKey = dwhORWnd;
		ENK.eFcn = (ENUMLONGKEYPROC)_GetObjectsFromObjWin;	// zu rufende Funktion
		ENK.ePtr = &EDD;									// durchzureichende Daten

		if (DEX_EnumSelectedObjects (ENK))		// mit Idents füllen
			return INITOBJSTATUS_Exists;
	} else if (*plONr != INVALID_ONR) {
	// fill only dwSingle
		if (_GetObjectsFromObjWin (*plONr, true, &EDD)) {
			if (IsWindow((HWND)dwhORWnd) && DEX_IsORWindow(dwhORWnd)) {
				DEXOR_AddObjectToList((HWND)dwhORWnd, *plONr);		// Add to ORWnd
				DEXOR_SelectObject((HWND)dwhORWnd, *plONr);			// Select it
			}
			return INITOBJSTATUS_Exists;
		}
	} 

return INITOBJSTATUS_Error;
}

STDMETHODIMP CGeoObjectWin::GetSelectedObjects (DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	TEST_E_POINTER("CGeoObjectWin::GetSelectedObjects", ppIObjs);
	*ppIObjs = NULL;
	if (!m_fValid)
		return E_UNEXPECTED;

// jetzt Collection der GeoObjects generieren
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(DGeoObjectWin *)this, m_pApp, m_pDoc,
							GetSelObjectsFromObjWin, (DWORD)(void *)GetValue(),
							UnSelectObjectFromObjWin);

// Resultat vorbereiten
	if (pCObjects == NULL) return E_OUTOFMEMORY;

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CGeoObjectWin::SetShownFeature (BSTR bstrFeatName) 
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (!m_fValid)
		return E_UNEXPECTED;

HWND hWnd =	GetValue();

	ASSERT(IsWindow(hWnd) && DEX_IsORWindow(hWnd));
	if (NULL == hWnd || !DEX_IsORWindow(hWnd))
		return E_UNEXPECTED;

	USES_CONVERSION;

SHOWOBJPROP SOP;
WObjectProperty ObjProp;
HRESULT hr = m_pApp -> GetObjectProperty (OLE2A(bstrFeatName), 0L, ObjProp.ppi());

	if (FAILED(hr)) return hr;

	INITSTRUCT (SOP, SHOWOBJPROP);
	SOP.m_pIObjProp = ObjProp;
	SOP.m_iFlags = SOPReloadProps;		// neu anzeigen

	return DEXOR_SetObjectProperty(hWnd, SOP) ? S_OK : E_FAIL;
}

STDMETHODIMP CGeoObjectWin::get_Properties (_DTRiASProperties **ppIProps)
{
	return E_NOTIMPL;
}

STDMETHODIMP CGeoObjectWin::CreateProperty (VARIANT vName, VARIANT vType, VARIANT vValue, _DTRiASProperty **ppIProp)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// Funktionen werden gerufen, wenn externe Locks entstehen bzw.
// verschwinden
ULONG CGeoObjectWin::InternalAddRef()
{
	_ASSERTE(m_dwRef != -1L);
	Lock();

long l = CComObjectRoot::InternalAddRef();

	if (m_dwRef == OBJWIN_EXTERNAL_THRESHOLD+1) {
		Unlock();
		FinalExternalConstruct();
	} else 
		Unlock();
	return l;
}

ULONG CGeoObjectWin::InternalRelease()
{
	Lock();

long l = CComObjectRoot::InternalRelease();

	if (m_dwRef == OBJWIN_EXTERNAL_THRESHOLD) {
		Unlock();
		FinalExternalRelease();
	} else 
		Unlock();
	return l;
}

HRESULT CGeoObjectWin::FinalExternalConstruct (void)
{
	ADDREF(m_pUnk);
	ADDREF_CAST(_DApplication, m_pApp);
	ADDREF_CAST(_DDocument, m_pDoc);
	return S_OK;
}

void CGeoObjectWin::FinalExternalRelease (void)
{
	RELEASE_NONULL(m_pUnk);					// Parent wieder loslassen
	RELEASE_CAST(_DApplication, m_pApp);	// Applikation wieder loslassen
	RELEASE_CAST(_DDocument, m_pDoc);		// Dokument wieder loslassen
}

///////////////////////////////////////////////////////////////////////////////
// FensterPosition und -Größe
STDMETHODIMP CGeoObjectWin::get_Left (long *plLeft)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == plLeft) 
		return E_POINTER;
	*plLeft = 0;
	if (!m_fValid)
		return E_UNEXPECTED;
	
	*plLeft = MoveSize (MOVESIZEACTION_GETLEFT);
	return S_OK;
}

STDMETHODIMP CGeoObjectWin::put_Left (long lLeft)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	MoveSize (MOVESIZEACTION_LEFT, lLeft);
	return S_OK;
}

STDMETHODIMP CGeoObjectWin::get_Top (long *plTop)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == plTop) 
		return E_POINTER;
	*plTop = 0;
	if (!m_fValid)
		return E_UNEXPECTED;
	
	*plTop = MoveSize (MOVESIZEACTION_GETTOP);
	return S_OK;
}

STDMETHODIMP CGeoObjectWin::put_Top (long lTop)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	MoveSize (MOVESIZEACTION_TOP, 0, lTop);
	return S_OK;
}

STDMETHODIMP CGeoObjectWin::get_Width (long *plWidth)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == plWidth) 
		return E_POINTER;
	*plWidth = 0;
	if (!m_fValid)
		return E_UNEXPECTED;
	
	*plWidth = MoveSize (MOVESIZEACTION_GETWIDTH);
	return S_OK;
}

STDMETHODIMP CGeoObjectWin::put_Width (long lWidth)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	MoveSize (MOVESIZEACTION_WIDTH, 0, 0, lWidth);
	return S_OK;
}

STDMETHODIMP CGeoObjectWin::get_Height (long *plHeight)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == plHeight) 
		return E_POINTER;
	*plHeight = 0;
	if (!m_fValid)
		return E_UNEXPECTED;
	
	*plHeight = MoveSize (MOVESIZEACTION_GETHEIGHT);
	return S_OK;
}

STDMETHODIMP CGeoObjectWin::put_Height (long lHeight)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

	MoveSize (MOVESIZEACTION_HEIGHT, 0, 0, 0, lHeight);
	return S_OK;
}

/*
 * CGeoObjectWin::MoveSize
 *
 * Purpose:
 *  Helper function for the Left, Top, Width, and Height properties
 *  that centralizes calls to GetWindowRect and SetWindowPos,
 *  reducing overall code somewhat.
 *
 * Parameters:
 *  iAction         MOVESIZEACTION enum value to indicate what
 *                  type of moving/sizing to perform
 *  x, y            long position coordinates;  x is only meaningful
 *                  with MOVESIZEACTION_LEFT, y only with _TOP
 *  cx, cy          long extents;  cx is only meaningful
 *                  with MOVESIZEACTION_WIDTH, cy only with _HEIGHT
 *
 * Return Value:
 *  long            The current x, y, cx, or cy value depending on
 *                  iAction being _GETLEFT, _GETTOP, _GETWIDTH, or
 *                  _GETHEIGHT.
 */

long CGeoObjectWin::MoveSize (CGeoObjectWin::MOVESIZEACTION iAction, long x, long y, long cx, long cy)
{
	ASSERT(IsWindow(m_hORWnd) && DEX_IsORWindow(m_hORWnd));
	if (NULL == m_hORWnd || !DEX_IsORWindow(m_hORWnd))
		return 0;

RECT rc;
long x1, y1, cx1, cy1;
UINT uFlags;

	::GetWindowRect (m_hORWnd, &rc);

CPoint pt1(rc.left, rc.top), pt2 (rc.right, rc.bottom);

// Hier müßte normalerweise das ParentFenster zum Umrechnen verwendet werden,
// da offensichtlich jedoch ein m´nichtmodaler Dialog als Parent nicht ein
// child haben kann und als parent das nächste übergeordnete popup eingesetzt
// wird, muß hier dierekt das ViewWindow reingetrickst werden.
CWnd *pFrame = g_pTE -> MWind();

	ASSERT(NULL != pFrame);

CWnd *pView = pFrame -> GetDlgItem (AFX_IDW_PANE_FIRST);

	::ScreenToClient (pView->GetSafeHwnd(), &pt1);
	::ScreenToClient (pView->GetSafeHwnd(), &pt2);

//By default we'll do nothing
	x1 = pt1.x;
	y1 = pt1.y;
	cx1 = pt2.x-pt1.x;
	cy1 = pt2.y-pt1.y;
	uFlags = 0L;

	switch (iAction) {
	/*
	 * Each individual property modifies the appropriate
	 * variable x1, y1, cx1, cy1, as well as uFlags to set
	 * up SetWindowPos call.
	 */
	case MOVESIZEACTION_LEFT:
		x1 = x;
		uFlags = SWP_NOSIZE;
		break;

	case MOVESIZEACTION_TOP:
		y1 = y;
		uFlags = SWP_NOSIZE;
		break;

	case MOVESIZEACTION_WIDTH:
		cx1 = cx;
		uFlags = SWP_NOMOVE;
		break;

	case MOVESIZEACTION_HEIGHT:
		cy1 = cy;
		uFlags = SWP_NOMOVE;
		break;

	case MOVESIZEACTION_GETLEFT:
		return x1;

	case MOVESIZEACTION_GETTOP:
		return y1;

	case MOVESIZEACTION_GETWIDTH:
		return cx1;

	case MOVESIZEACTION_GETHEIGHT:
		return cy1;

	default:
		return 0;
	}

// Recherchefenster hat eigentlich View als Parent, aber nichtmodale Dialoge
// können offensichtlich kein ChildWindow als parent haben. Daher werden sie
// bei der Initialisieruing an das nächst-übergeordnete PopupFenster
// 'weitergereicht'. 
// Hier müssen die Koordianten also künstlich auf den Parent des ORWnd's
// umgerechnet werden.
CPoint pt(x1, y1);

	::ClientToScreen(pView->GetSafeHwnd(), &pt);
//	::ScreenToClient(::GetParent(m_hORWnd), &pt);

// We only get here on propety changes
	SetWindowPos (m_hORWnd, NULL, (int)pt.x, (int)pt.y, (int)cx1, (int)cy1,
				  SWP_NOZORDER | SWP_NOACTIVATE | uFlags);

return 0;	// Irrelevant for property changes.
}

STDMETHODIMP CGeoObjectWin::IsActive (VARIANT_BOOL *IsActWin)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == IsActWin) 
		return E_POINTER;
	*IsActWin = VARIANT_FALSE;
	if (!m_fValid)
		return E_UNEXPECTED;

HWND hWnd = DEX_GetActiveORWnd();

	TX_ASSERT(NULL == hWnd || DEX_IsORWindow(hWnd));
	if (NULL == hWnd) 
		return E_UNEXPECTED;		// kein ORFenster vorhanden

	*IsActWin = (hWnd == GetValue()) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CGeoObjectWin::SetActive (void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())

#if defined(DEX_SetActiveORWnd)
	if (!m_fValid)
		return E_UNEXPECTED;

HWND hWnd = GetValue();

	TX_ASSERT(NULL == hWnd || DEX_IsORWindow(hWnd));
	if (NULL == hWnd) 
		return E_UNEXPECTED;		// kein ORFenster vorhanden

	DEX_SetActiveORWnd (hWnd);
	return S_OK;
#else
	return E_NOTIMPL;
#endif // DEX_SetActiveORWnd
}

STDMETHODIMP CGeoObjectWin::get_Color (long *plColor)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == plColor) 
		return E_POINTER;
	*plColor = RGB(0, 0, 0);
	if (!m_fValid)
		return E_UNEXPECTED;
	
	*plColor = DEXOR_GetMarkColor(GetValue());
	return S_OK;
}

STDMETHODIMP CGeoObjectWin::put_Color (long lColor)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (!m_fValid)
		return E_UNEXPECTED;

	DEXOR_SetMarkColor(GetValue(), lColor);
	return S_OK;
}

