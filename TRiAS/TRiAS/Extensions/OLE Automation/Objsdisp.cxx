// Collection vor Objects (ProgrammierInterface) -----------------
// File: OBJSDISP.CXX

#include "precomp.hxx"

#include "oleautor.h"

#include <dirisole.h>
#include <operguid.h>
#include <ifndlong.h>

#include <ospace/com/iterenum.h>
#include <ospace/std/algorithm>
#include <Atl/Ciid.h>

#include "GlobalFuncs.h"
#include "objarray.hxx"
#include "enumobjs.hxx"
#include "objs.hxx"			// Collection: Objects

#include "obj.hxx"			// Object
#include "objwin.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if defined(_SUPPORT_QUERYDEFS)
EXTERN_C const CLSID CLSID_TRiASCollectObjects;
#endif // defined(_SUPPORT_QUERYDEFS)

///////////////////////////////////////////////////////////////////////////////
// verwendete SmartInterface's etc.
DefineSmartInterface(EnumLONG);			// WEnumLONG
DefineSmartInterface(QueryEnumLONG);	// WQueryEnumLONG
DefineSmartInterface2(_DGeoObject, IID_DGeoObject);		// W_DGeoObject
DefineSmartInterface2(_DGeoObjects, IID_DGeoObjects);	// W_DGeoObjects

// IEnum<LONG> und entsprechende Iteratoren
DefineSortingEnumerator(LONG);			// SEnumLONG
DefineEnumInputIterator(LONG);			// InEnumLONG
DefineEnumOutputIterator(LONG);			// OutEnumLONG

DefineSmartInterface(ExtendObjOper);	// WExtendObjOper

// ProgrammierInterfaceFunktionen ---------------------------------------------
// Das StandardProperty Parent liefert das übergeordnete Objekt, über welches 
// diese Collection angelegt wurde.

STDMETHODIMP CGeoObjects::get_isA (LONG *plRTTI)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObjects::get_isA");

	if (NULL == plRTTI) 
		return E_POINTER;
	*plRTTI = RTTI_GeoObjects;
	return NOERROR;
}

STDMETHODIMP CGeoObjects::get_Parent (IDispatch **ppIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObjects::get_Parent");
	return m_pUnk -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

// Dieses StandardProperty liefert das ApplicationInterface (das allen anderen
// Objekten übergeordnete)
STDMETHODIMP CGeoObjects::get_Application (IDispatch **ppIDisp)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObjects::get_Application");
	return ((_DApplication *)m_pApp) -> QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);
}

STDMETHODIMP CGeoObjects::put_Parent (IDispatch *pIDisp)
{
	return E_NOTIMPL;
}

STDMETHODIMP CGeoObjects::put_Application (IDispatch *pIDisp)
{
	return E_NOTIMPL;
}

// Liefert die Anzahl der Objects ---------------------------------
STDMETHODIMP CGeoObjects::get_Count (long *plCount)
{
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObjects::get_Count");
	if (NULL == plCount) return E_POINTER;

	*plCount = Count();
	return NOERROR;
}

STDMETHODIMP CGeoObjects::Item (VARIANT vt, IDispatch **ppIDisp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObjects::Item");

// versuchen, Parameter auszuwerten
CComVariant vArg;
HRESULT hr = VariantChangeType (&vArg, &vt, 0, VT_I4);	// Zahl als Index 

	if (SUCCEEDED(hr)) {
		if (V_I4(&vArg) > 0 && ULONG(V_I4(&vArg)) <= Count()) 
		// Index ist gültig: Dispatch-Interface abfragen
			return GetObjectDisp (V_I4(&vArg)-1, (LPVOID *)ppIDisp);

		return DISP_E_BADINDEX;
	}


// 2. Versuch vt als String interpretieren (Name ?)
	hr = VariantChangeType (&vArg, &vt, 0, VT_BSTR);
	if (SUCCEEDED(hr)) {
	LONG lONr = INVALID_ONR;
	string strArg = AnsiString (V_BSTR(&vArg));

		if (':' == strArg[0]) {	 // first char == ':' ? --> ':ONr'
			lONr = strtol (strArg.c_str()+1, NULL, 10); 
			return GetObjectDispValue (lONr, (LPVOID *)ppIDisp);
		} 
	
	// Object name given
		return GetObjectDisp (strArg.c_str(), (LPVOID *)ppIDisp);
	}

// 3. Versuch: evtl. ist Parameter nicht gegeben
	hr = VariantChangeType (&vArg, &vt, 0, VT_ERROR);
	if (SUCCEEDED(hr) && V_ERROR(&vArg) == DISP_E_PARAMNOTFOUND) 
	// liefert sich selbst (ObjectCollection)
		hr = ((_DGeoObjects *)this)->QueryInterface (IID_IDispatch, (LPVOID *)ppIDisp);

	return hr;
}


// Dieses StandardInterface liefert einen neuen Enumerator IEnumVARIANT mit
// allen Objekten
// Dieses gelieferte Interface ist allerdings von VB aus schlecht verwendbar.
//
STDMETHODIMP CGeoObjects::_NewEnum (IUnknown **ppIUnk)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObjects::_NewEnum");

	if (NULL == ppIUnk) return E_POINTER;

// neuen Enumerator anlegen
CEnumGeoObjs *pEGeoObjs = CEnumGeoObjs::CreateInstance (m_pObjs -> m_pGeoObjArray);

	if (NULL == pEGeoObjs) return E_OUTOFMEMORY;
	
HRESULT hr = pEGeoObjs -> QueryInterface (IID_IEnumVARIANT, (LPVOID *)ppIUnk);

	pEGeoObjs -> Release();

return hr;
}

HRESULT CGeoObjects::HandleAddObject (long lONr, IDispatch **ppIDisp)
{
	if (lONr == 0L) lONr = INVALID_ONR;
	
long lIndex = m_pObjs -> m_pGeoObjArray -> hasObject (lONr);
INITOBJSTATUS rgIOS = INITOBJSTATUS_Error;

	if (lIndex == -1L) {
	CGeoObjectCreator ObCr (*(m_pObjs -> m_pGeoObjArray));
	
		rgIOS = m_pICProc (m_pUnk, m_pApp, m_pDoc, ObCr, m_dwData, &lONr);
		if (rgIOS == INITOBJSTATUS_Error) 
			return E_FAIL;
	} else  
		rgIOS = INITOBJSTATUS_Exists;

	if (rgIOS == INITOBJSTATUS_Created || rgIOS == INITOBJSTATUS_Exists) {
		if (-1 == lIndex)
			lIndex = m_pObjs -> m_pGeoObjArray -> hasObject (lONr);

		ASSERT(-1 != lIndex);
		return GetObjectDisp (lIndex, (LPVOID *)ppIDisp);
	}

	return E_FAIL;
}

STDMETHODIMP CGeoObjects::Add (VARIANT vObj, IDispatch **ppIDisp)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObjects::Add");

// versuchen, Parameter auszuwerten
CComVariant vArg; 
INITOBJSTATUS rgIOS = INITOBJSTATUS_Error;
HRESULT hr = VariantChangeType (&vArg, &vObj, 0, VT_UNKNOWN);	// Pointer auf GeoObject

	if (SUCCEEDED(hr)) {
		try {
		W_DGeoObject IObj(V_UNKNOWN(&vArg));		// throws hr
		LONG lONr = INVALID_ONR;

			THROW_FAILED_HRESULT(IObj -> get_Value(&lONr));
			THROW_FAILED_HRESULT(HandleAddObject (lONr, ppIDisp));

		} catch (_com_error& hr) {
			return _COM_ERROR(hr);
		}
	}

	if (VT_BSTR != V_VT(&vObj)) {
	// nur auf Zahl testen, wenn nicht direkt als BSTR gegeben
	// damit Objektnamen eine Zahl sein dürfen
		hr = VariantChangeType (&vArg, &vObj, 0, VT_I4);	// Zahl als Index 
		if (SUCCEEDED(hr))		// ObjektNummer gegeben
			return HandleAddObject(V_I4(&vArg), ppIDisp);
	}

// Objektname gegeben
	hr = VariantChangeType (&vArg, &vObj, 0, VT_BSTR);
	if (SUCCEEDED(hr)) {
	string strName = AnsiString(V_BSTR(&vArg));
	long lONr = m_pDoc -> GetONrFromObjName (strName.c_str());

		return HandleAddObject(lONr, ppIDisp);
	}

return hr;
}

STDMETHODIMP CGeoObjects::Remove(VARIANT vObj)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObjects::Remove");

// versuchen, Parameter auszuwerten
CComVariant vArg;
HRESULT hr = vArg.ChangeType (VT_I4, &vObj);	// Zahl als Index 

	if (SUCCEEDED(hr)) {
	// ObjektNummer
	long lONr = V_I4(&vArg);
	
		if (NULL != m_pDCProc && !(*m_pDCProc)(lONr, m_pDoc, m_dwData))
			return E_FAIL;

		m_pObjs -> DeleteObject (lONr);
		return NOERROR;
	}
	
	hr = vArg.ChangeType (VT_BSTR, &vObj);
	if (SUCCEEDED(hr)) {
	long lONr = m_pDoc -> GetONrFromObjName (AnsiString(V_BSTR(&vArg)));

		if (NULL != m_pDCProc && !(*m_pDCProc)(lONr, m_pDoc, m_dwData))
			return E_FAIL;

		m_pObjs -> DeleteObject (lONr);
		return NOERROR;
	}

	hr = vArg.ChangeType (VT_UNKNOWN, &vObj);
	if (SUCCEEDED(hr)) {
	W_DGeoObject Obj;
	
		hr = V_UNKNOWN(&vArg) -> QueryInterface(Obj.ppi());
		if (SUCCEEDED(hr)) {
		long lONr = NULL;

			hr = Obj -> get_Value(&lONr);
			if (SUCCEEDED(hr)) {
				if (NULL != m_pDCProc && !(*m_pDCProc)(lONr, m_pDoc, m_dwData))
					return E_FAIL;

				m_pObjs -> DeleteObject (lONr);
			}
			return hr;
		}
	}
	return hr;
}

STDMETHODIMP CGeoObjects::Refresh (void)
{
// wenn Informationen über Herkunft existieren, dann neu erzeugen, ansonsten
// tote Seelen beseitigen
	if (CanRegenerate()) 
		return Regenerate() ? NOERROR : E_OUTOFMEMORY;

	return m_pObjs -> m_pGeoObjArray -> Refresh();
}

STDMETHODIMP CGeoObjects::CreateGeoObjectWin (VARIANT vFlags, DGeoObjectWin **ppIWin)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObjects::CreateGeoObjectWin");

CComVariant vFlagArg; 
HRESULT hr = vFlagArg.ChangeType (VT_I4, &vFlagArg);
long iFlags = 0;

	if (SUCCEEDED(hr)) 
		iFlags = V_I4(&vFlagArg);

// Objektfeld zusammenstellen
HOBJECT *pObjs = GetObjectsAsArray();

	if (pObjs == NULL) return E_OUTOFMEMORY;

// ORFenster mit Result aufbauen
CREATEOBJEKTINFOEX COI;

CString strCaption; strCaption.LoadString (IDS_OBJWINCAPTION);
POINT pt;

	pt.x = 0, pt.y = 0;
	INITSTRUCT (COI, CREATEOBJEKTINFOEX);
	COI.lpCaption = (char *)(const char *)strCaption;
	COI.plObjs = pObjs;
	COI.iNumObjs = short(Count());
	COI.cMColor = RGB(255, 0, 0);
	COI.pntPos = pt;
	COI.m_iFlags = iFlags;

HWND hWnd = DEX_CreateObjektInfo (COI);	// ORFenster erzeugen

	DELETE_OBJ (pObjs);
	if (NULL == hWnd) return E_UNEXPECTED;

// Window physically was created - now add to tree and get Disp
CGeoObjectWin *pObjWin = m_pDoc -> FGetObjWinDisp (
							hWnd, ppIWin, GEOOBJWINMODE_Get);

	if (NULL == pObjWin) return E_UNEXPECTED;

	return S_OK;
}

// Liefert einen Enumerator mit allen Objekten dieser GeoObjecs-collection ----
HRESULT GetEnumLongFromGeoObjects (DGeoObjects *pIObjs, IEnumLONG **ppIEnum)
{
	if (NULL == ppIEnum) return E_POINTER;
	*ppIEnum = NULL;

	try {
	WQueryEnumLONG Objs (pIObjs);		// throws HRESULT
	HRESULT hr = Objs -> QueryEnumLONG (ppIEnum);

		if (FAILED(hr)) _com_issue_error(hr);

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return S_OK;
}

// aus EnumLong GeoObjects-Collection generieren (für aktuelles Dokument)
HRESULT GetGeoObjectsFromEnumlong (IEnumLONG *pIEnum, DGeoObjects **ppIObjs)
{
	if (NULL == ppIObjs) return E_POINTER;
	*ppIObjs = NULL;

CTriasApp *pApp = ((OLE2AutoExtension *)g_pTE) -> App();
CGeoDoc *pDoc = NULL;
HRESULT hr = pApp -> FGetDocDisp (NULL, &pDoc);

	if (FAILED(hr)) return hr;

CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
	(DDocument *)pDoc, pApp, pDoc, GetObjectsFromEnum, (DWORD)pIEnum, NULL);

	if (pCObjects == NULL) 
		return E_OUTOFMEMORY;

	pCObjects -> m_dwData = NULL;

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

// Geometrische Mengenoperationen aller Objekte dieser Collection -------------
STDMETHODIMP CGeoObjects::GeometryIntersection (DGeoClass *pICls, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObjects::GeometryIntersection");

	TEST_E_POINTER("CGeoObjects::GeometryIntersection", ppIObjs);

WExtendObjOper ObjOper;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIObjOper (ObjOper.ppi());

	if (FAILED(hr)) return hr; 

// Objektmenge in EnumLONG verpacken
IEnumLONG *pIEnum = NULL;		// Resultat
WEnumLONG EnumIn;				// AusgangsMenge

	hr = GetEnumLongFromGeoObjects (this, EnumIn.ppi());
	if (FAILED(hr)) return hr;

ULONG ulIdent = INVALID_IDENT;

	hr = pICls -> get_Code((LONG *)&ulIdent);
	if (FAILED(hr)) return hr;

	hr = ObjOper -> AndArea (EnumIn, ulIdent, SFORM_PERM, &pIEnum);
	if (FAILED(hr)) {
		if (pIEnum) pIEnum -> Release();
		return hr;
	}

// jetzt Collection der GeoObjects generieren
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(DGeoObjects *)this, m_pApp, m_pDoc,
						 	GetObjectsFromEnum, (DWORD)pIEnum, NULL);
// Resultat vorbereiten
	if (NULL == pCObjects) return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;
	if (NULL != pIEnum) pIEnum -> Release(); 

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CGeoObjects::Intersection (DGeoObjects *pIObjs, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObjects::Intersection");

	TEST_E_POINTER("CGeoObjects::Intersection", ppIObjs);

// alle unsere Objekte in einem Enumerator speichern
WEnumLONG EnumMe;
HRESULT hr = GetEnumLongFromGeoObjects (this, EnumMe.ppi());

	if (FAILED(hr)) return hr;

// Resultat der Operation in einem Enumerator speichern
SEnumLONG EnumOut;

	try {
	// alle Objekte der gegebenen Folge in einem Enumerator speichern
	WEnumLONG EnumYou;

		hr = GetEnumLongFromGeoObjects (pIObjs, EnumYou.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

	// neuen Enumerator füllen
	OutEnumLONG iter_out (&EnumOut);		// throws hr

		set_intersection (InEnumLONG(EnumMe), InEnumLONG(),
						  InEnumLONG(EnumYou), InEnumLONG(),
						  iter_out);

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

// das Ergebnis wieder in einer GeoObjects-Collection ablegen
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(DGeoObjects *)this, m_pApp, m_pDoc,
						 	GetObjectsFromEnum, (DWORD)(IEnum<LONG> *)&EnumOut, NULL);
// Resultat vorbereiten
	if (pCObjects == NULL) return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CGeoObjects::Union (DGeoObjects *pIObjs, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObjects::Union");

	TEST_E_POINTER("CGeoObjects::Union", ppIObjs);

// alle unsere Objekte in einem Enumerator speichern
WEnumLONG EnumMe;
HRESULT hr = GetEnumLongFromGeoObjects (this, EnumMe.ppi());

	if (FAILED(hr)) return hr;

// Resultat der Operation in einem Enumerator speichern
SEnumLONG EnumOut;

	try {
	// alle Objekte der gegebenen Folge in einem Enumerator speichern
	WEnumLONG EnumYou;

		hr = GetEnumLongFromGeoObjects (pIObjs, EnumYou.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

	// neuen Enumerator füllen
	OutEnumLONG iter_out (&EnumOut);		// throws hr

		set_union (InEnumLONG(EnumMe), InEnumLONG(),
				   InEnumLONG(EnumYou), InEnumLONG(),
				   iter_out);

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

// das Ergebnis wieder in einer GeoObjects-Collection ablegen
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(DGeoObjects *)this, m_pApp, m_pDoc,
						 	GetObjectsFromEnum, (DWORD)(IEnum<LONG> *)&EnumOut, NULL);
// Resultat vorbereiten
	if (NULL == pCObjects) return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CGeoObjects::Difference (DGeoObjects *pIObjs, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObjects::Difference");

	TEST_E_POINTER("CGeoObjects::Difference", ppIObjs);

// alle unsere Objekte in einem Enumerator speichern
WEnumLONG EnumMe;
HRESULT hr = GetEnumLongFromGeoObjects (this, EnumMe.ppi());

	if (FAILED(hr)) return hr;

// Resultat der Operation in einem Enumerator speichern
SEnumLONG EnumOut;

	try {
	// alle Objekte der gegebenen Folge in einem Enumerator speichern
	WEnumLONG EnumYou;

		hr = GetEnumLongFromGeoObjects (pIObjs, EnumYou.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

	// neuen Enumerator füllen
	OutEnumLONG iter_out (&EnumOut);		// throws hr

		set_difference (InEnumLONG(EnumMe), InEnumLONG(),
						InEnumLONG(EnumYou), InEnumLONG(),
						iter_out);

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

// das Ergebnis wieder in einer GeoObjects-Collection ablegen
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(DGeoObjects *)this, m_pApp, m_pDoc,
						 	GetObjectsFromEnum, (DWORD)(IEnum<LONG> *)&EnumOut, NULL);
// Resultat vorbereiten
	if (pCObjects == NULL) return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CGeoObjects::SymmetricDifference (DGeoObjects *pIObjs, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObjects::SymmetricDifference");

	TEST_E_POINTER("CGeoObjects::SymmetricDifference", ppIObjs);

// alle unsere Objekte in einem Enumerator speichern
WEnumLONG EnumMe;
HRESULT hr = GetEnumLongFromGeoObjects (this, EnumMe.ppi());

	if (FAILED(hr)) return hr;

// Resultat der Operation in einem Enumerator speichern
SEnumLONG EnumOut;

	try {
	// alle Objekte der gegebenen Folge in einem Enumerator speichern
	WEnumLONG EnumYou;

		hr = GetEnumLongFromGeoObjects (pIObjs, EnumYou.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

	// neuen Enumerator füllen
	OutEnumLONG iter_out (&EnumOut);		// throws hr

		set_symmetric_difference (InEnumLONG(EnumMe), InEnumLONG(),
								  InEnumLONG(EnumYou), InEnumLONG(),
								  iter_out);

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

// das Ergebnis wieder in einer GeoObjects-Collection ablegen
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(DGeoObjects *)this, m_pApp, m_pDoc,
						 	GetObjectsFromEnum, (DWORD)(IEnum<LONG> *)&EnumOut, NULL);
// Resultat vorbereiten
	if (pCObjects == NULL) return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CGeoObjects::_GeometryLinesUnion (
	DGeoClass *pICls, VARIANT vFillGap, VARIANT vAsArea, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObjects::_GeometryLinesUnion");

WExtendObjOper ObjOper;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIObjOper (ObjOper.ppi());

	if (FAILED(hr)) return hr;

// Objektmenge in EnumLONG verpacken
IEnumLONG *pIEnum = NULL;		// Resultat
WEnumLONG EnumIn;				// AusgangsMenge

	hr = GetEnumLongFromGeoObjects (this, EnumIn.ppi());
	if (FAILED(hr)) return hr;

CComVariant vaArg; 
ULONG ulFillGap = 0;
	
	hr = vaArg.ChangeType (VT_I4, &vFillGap);
	if (SUCCEEDED(hr)) 
		ulFillGap = (ULONG)V_I4(&vaArg);

bool fAsArea = false;

	hr = vaArg.ChangeType (VT_BOOL, &vAsArea);
	if (SUCCEEDED(hr)) 
		fAsArea = V_BOOL(&vaArg) ? true : false;

ULONG ulIdent = INVALID_IDENT;

	hr = pICls -> get_Code((LONG *)&ulIdent);
	if (FAILED(hr)) return hr;

	hr = ObjOper -> LinesUnion (EnumIn, (ULONG)ulIdent, ulFillGap, fAsArea, SFORM_PERM, &pIEnum);
	if (FAILED(hr)) {
		if (pIEnum) pIEnum -> Release();
		return hr;
	}

// das Ergebnis wieder in einer GeoObjects-Collection ablegen
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(_DGeoObjects *)this, m_pApp, m_pDoc,
						 	GetObjectsFromEnum, (DWORD)pIEnum, NULL);
// Resultat vorbereiten
	if (pCObjects == NULL) return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;
	if (NULL != pIEnum) pIEnum -> Release(); 

	*ppIObjs = (DGeoObjects *)pCObjects;
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Suchen aller Objekte einer GeoObjects-Collection, die in einem bestimmten 
// Fenster liegen
typedef struct tagENUMOBJECTSDATAEX {
	CGeoObjectCreator *m_pCr;
	LPUNKNOWN m_pUnk;
	CTriasApp *m_pApp;
	CGeoDoc *m_pDoc;
	IFindLONG *m_pIFind;
} ENUMOBJECTSDATAEX;

extern "C" 
BOOL PASCAL _XTENSN_EXPORT _GetObjectsInWindowFromGeoObjects (long lONr, BOOL, void *pData)
{
ENUMOBJECTSDATAEX *pEOD = (ENUMOBJECTSDATAEX *)pData;

	if (S_OK != pEOD -> m_pIFind -> HasLONG(lONr))
		return true;	// nicht für uns, da nicht in Bezugsmenge

CGeoObject *pObject = pEOD -> m_pDoc -> FGetObjectDisp (lONr);

	if (pObject) {
		((_DGeoObject *)pObject) -> AddRef();
		pEOD -> m_pCr -> InsertPtr (pObject);
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// INITOBJCOLLECTIONPROC 
typedef struct tagOBJSINWINDOWOBJS {
	long m_rglCont[4];		// XMin, XMax, YMin, Ymax
	IFindLONG *m_pIFind;
} OBJSINWINDOWOBJS;

extern "C" 
INITOBJSTATUS PASCAL GetObjectsInWindowFromGeoObjects (
		LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
		container_wrappers::CCreator &rCollCr, DWORD dwData, long *plONr)
{
	if (plONr != NULL) 
		return INITOBJSTATUS_Error;	// can't add single object

ENUMOBJECTSDATAEX EOD;
OBJSINWINDOWOBJS *pData = (OBJSINWINDOWOBJS *)dwData;

	EOD.m_pCr = (CGeoObjectCreator *)&rCollCr;
	EOD.m_pUnk = pUnk;
	EOD.m_pApp = pApp;
	EOD.m_pDoc = pDoc;
	EOD.m_pIFind = pData -> m_pIFind;

// fill all objects
ENUMRECHGEOMETRIE ERG;

	INITSTRUCT(ERG, ENUMRECHGEOMETRIE);
	ERG.lCont = pData -> m_rglCont;
	ERG.iMode = ERGExact;
	ERG.eFcn = (RECHGEOMETRIEPROC)_GetObjectsInWindowFromGeoObjects;
	ERG.pData = &EOD;					// durchzureichende Daten

	if (DEX_EnumRechGeometrie (ERG))	// mit Objekten füllen
		return INITOBJSTATUS_Exists;

	return INITOBJSTATUS_Error;		// error !
}

bool InternalCoords (double dblX, double dblY, LONG *plX, LONG *plY);

STDMETHODIMP CGeoObjects::GetObjectsInRect (
		double dX1, double dY1, VARIANT vX2, VARIANT vY2, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObjects::GetObjectsInRect");

	TEST_E_POINTER("CGeoObjects::GetObjectsInRect", ppIObjs);

// Parameter enthalten Eckkoordinaten
OBJSINWINDOWOBJS ownd;

    if (!InternalCoords (dX1, dY1, &ownd.m_rglCont[0], &ownd.m_rglCont[2]))
        return E_UNEXPECTED;

// 2. Koordinatenpaar ist optional
VARIANT vArgX, vArgY; VariantInit (&vArgX); VariantInit (&vArgY);
HRESULT hrx = VariantChangeType (&vArgX, &vX2, 0, VT_R8);
HRESULT hry = VariantChangeType (&vArgY, &vY2, 0, VT_R8);

    if (FAILED(hrx) || FAILED(hry)) {
        ownd.m_rglCont[1] = ownd.m_rglCont[0];
	    ownd.m_rglCont[3] = ownd.m_rglCont[2];
    }
    else if (!InternalCoords (V_R8(&vArgX), V_R8(&vArgY), &ownd.m_rglCont[1], &ownd.m_rglCont[3]))
        return E_UNEXPECTED;

	{
	WEnumLONG EnumIn;				// AusgangsMenge
    HRESULT hr = GetEnumLongFromGeoObjects (this, EnumIn.ppi());
		
        if (FAILED(hr)) return hr;

		ownd.m_pIFind = NULL;
		hr = EnumIn -> QueryInterface (IID_IFindLONG, (LPVOID *)&ownd.m_pIFind);
		if (FAILED(hr)) return hr;
	}

// Collection aller Objekte im Container generieren anlegen
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(DGeoObjects *)this, m_pApp, m_pDoc,
						 	GetObjectsInWindowFromGeoObjects, (DWORD)&ownd,	NULL); 
	
	ownd.m_pIFind -> Release();
	if (NULL == pCObjects) return E_OUTOFMEMORY;

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

STDMETHODIMP CGeoObjects::GeometryUnion (DGeoClass *pICls, DGeoObjects **ppIObjs)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObjects::GeometryUnion");

// ObjOperExtension nach allen entsprechenden Objekten befragen
WExtendObjOper ObjOper;
HRESULT hr = ((OLE2AutoExtension *)g_pTE) -> GetIObjOper (ObjOper.ppi());

	if (FAILED(hr)) return hr;

// Objektmenge in EnumLONG verpacken
IEnumLONG *pIEnum = NULL;		// Resultat
WEnumLONG EnumIn;				// AusgangsMenge

	hr = GetEnumLongFromGeoObjects (this, EnumIn.ppi());
	if (FAILED(hr)) return hr;

ULONG ulIdent = INVALID_IDENT;

	hr = pICls -> get_Code((LONG *)&ulIdent);
	if (FAILED(hr)) return hr;

	hr = ObjOper -> OrArea (EnumIn, ulIdent, SFORM_PERM, &pIEnum);
	if (FAILED(hr)) {
		if (pIEnum) pIEnum -> Release();
		return hr;
	}

// jetzt Collection der GeoObjects generieren
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
							(_DGeoObjects *)this, m_pApp, m_pDoc,
						 	GetObjectsFromEnum, (DWORD)pIEnum, NULL);
// Resultat vorbereiten
	if (NULL == pCObjects) return E_OUTOFMEMORY;

// Enumerator freigeben	
	pCObjects -> m_dwData = NULL;
	if (NULL != pIEnum) pIEnum -> Release(); 

	*ppIObjs = (DGeoObjects *)pCObjects;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Rechercheobjektmengen
STDMETHODIMP CGeoObjects::MakeGeoClass (BSTR bstrNameOrOks, DGeoClass **ppIClass)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	D_SCOPE_OUTF(1, "OleAuto: %s", "CGeoObjects::MakeGeoClass");

	if (NULL == ppIClass)
		return E_POINTER;
	*ppIClass = NULL;

#if defined(_SUPPORT_QUERYDEFS)
	if (!((OLE2AutoExtension *)g_pTE) -> HasQueryDef())
		return S_FALSE;		// not supported in this configuration

// Objektklasse finden/sicherstellen
	USES_CONVERSION;

ULONG lIdent = 0;
LPCSTR pcClass = OLE2A(bstrNameOrOks);
CClass *pClass = NULL;

	if (!strncmp(pcClass, OKS_SCOPE_BEGIN, OKS_SCOPE_BEGIN_LEN)) {
	// first char == '[' ? --> '[OKS]'
	HRESULT hr = IdentFromClassX (HACTPROJECT, pcClass/*OKS_SCOPE_BEGIN_LEN*/, &lIdent);

		if (FAILED(hr)) {
		CIID Guid (CLSID_TRiASCollectObjects);
		os_string strGuid = Guid;

			strGuid += (pcClass+OKS_SCOPE_BEGIN_LEN);
			hr = IdentFromClassX (HACTPROJECT, strGuid.c_str(), &lIdent, TRUE);
			if (FAILED(hr))	return E_UNEXPECTED;
		}
	
		pClass = m_pDoc -> FGetClassDisp (lIdent, ppIClass);
		if (NULL == pClass)	return E_UNEXPECTED;

	} else {
	// normaler Kurztext gegeben
		pClass = m_pDoc -> FGetClassDisp (pcClass, ppIClass);
		if (NULL == pClass) {
			pClass = m_pDoc -> FGetClassDisp (pcClass, ppIClass, GEOCLASSMODE_Add, "__ActProject__");
			if (NULL == pClass) return E_UNEXPECTED;
		}
	}

// alle unsere Objekte zu dieser Objektklasse hinzufügen
WEnumLONG EnumIn;				// AusgangsMenge
LONG lONr = 0;

	RETURN_FAILED_HRESULT(GetEnumLongFromGeoObjects (this, EnumIn.ppi()));
	for (EnumIn -> Reset(); S_OK == EnumIn -> Next (1, &lONr, NULL); /**/) 
		m_pDoc -> ChangeObjectIdent (lONr, lIdent);

#endif // defined(_SUPPORT_QUERYDEFS)
	return S_OK;
}

