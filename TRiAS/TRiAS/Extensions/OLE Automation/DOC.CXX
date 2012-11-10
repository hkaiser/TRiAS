// Ein geöffnetes Dokumente (Controlling Unknown) -----------------------------
// File: DOC.CXX

#include "precomp.hxx"

#include <dirisole.h>
#include <xtensnn.h>
#include <registrx.hxx>

#include "oleautor.h"
#include "Strings.h"

#include "viewtree.hxx"
#include "objtrees.hxx"
#include "clstrees.hxx"

#include "connect.hxx"

#include "obj.hxx"		// Collection: GeoObjects
#include "objarray.hxx"
#include "enumobjs.hxx"
#include "objs.hxx"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// zugehörige CriticalSection
//CComGlobalsThreadModel::AutoCriticalSection CGeoDoc::m_cs;

///////////////////////////////////////////////////////////////////////////////
// Registrieen der notwendigen Document-Keys
static _ATL_REGMAP_ENTRY regEntryMapDoc[] = 
{
// TRiAS.Document
#if _ATL_VER >= 0x0200
	{ L"TRIASMODULE", NULL },
	{ L"PROGID", L"TRiAS.Document" },
	{ L"CLSID", L"{937EEB40-2234-101B-AAE1-E7E7E7E7E7E7}" },
#else
	{ TEXT("TRIASMODULE"), NULL },
	{ TEXT("PROGID"), TEXT("TRiAS.Document") },
	{ TEXT("CLSID"), TEXT("{937EEB40-2234-101B-AAE1-E7E7E7E7E7E7}") },
#endif // _ATL_VER
	{ NULL, NULL },		// EndeKennung
};

HRESULT WINAPI CGeoDoc::UpdateRegistry(BOOL fRegister)
{
TCHAR szModule[_MAX_PATH];

	GetModuleFileName (GetModuleHandle(NULL), szModule, _MAX_PATH);

TCHAR szModuleShort[_MAX_PATH];
int cbShortName = GetShortPathName (szModule, szModuleShort, _MAX_PATH);
LPOLESTR pszModule;

	USES_CONVERSION;
	if (cbShortName == _MAX_PATH)
		return E_OUTOFMEMORY;
	pszModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? T2OLE(szModule) : T2OLE(szModuleShort);
	strcpy (g_pDLLName, OLE2A(pszModule));

#if _ATL_VER >= 0x0200
	regEntryMapDoc[0].szData = pszModule;
#else
	USES_CONVERSION;
	regEntryMapDoc[0].szData = OLE2A(pszModule);
#endif // _ATL_VER

#if _TRiAS_VER >= 0x0400
	return _Module.UpdateRegistryFromResource(IDR_DOCUMENT_RGS, fRegister, regEntryMapDoc);
#else
// schon mal TRiAS V4 vorbereiten (OPLE registrieren)
CCurrentUser regCfg (KEY_READ, g_cbRegConfig);
DWORD dwVer4 = 0;

	regCfg.GetDWORD ("FakeTRiAS4", dwVer4);
	return _Module.UpdateRegistryFromResource(dwVer4 ? IDR_DOCUMENT_RGS : IDR_DOCUMENT_WITHOUTOLE_RGS, fRegister, regEntryMapDoc);
#endif // _TRiAS_VER >= 0x0400
}

///////////////////////////////////////////////////////////////////////////////
// Das eigentliche DocumentObject 
CGeoDoc::CGeoDoc (void)
	: m_fValid(false)
{
	CONSTRUCT_TRACE(CGeoDoc);

	m_pUnk = NULL;
	m_pApp = NULL;

	m_pViewTree   = NULL;
	m_pClsTrees   = NULL;
	m_pObjTrees   = NULL;
	m_pObjWinTree = NULL;

	m_pName = NULL;
	m_hPr = NULL;
	m_hPrCtx = HACTCONNECTION;
	m_pBuffer = NULL;

	m_dwCookie = 0L;
	m_dwRegROT = 0L;
	m_dwRegROTAll = 0L;

	m_pDocObjectServer = NULL;

// #AD000510, Synchronisation Paint und GetData
	m_bWait4StopPaint = false;
	m_bPaintStarted = false;
}

HRESULT CGeoDoc::FInit (LPUNKNOWN pUnk, CTriasApp *pApp, DOCMODE rgMode, LPCSTR bName)
{
// Parent festhalten
	if (NULL == pUnk || NULL == pApp || NULL == bName) 
		return E_INVALIDARG;

// Copy Doc name
HRESULT hr = SetName (bName, true);

	if (FAILED(hr)) return hr;
	 
	m_hPr = DEX_GetProjectHandle(bName);
	if (NULL == m_hPr) 
		return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);		// Projekt existiert nicht

	m_hPrCtx = DEX_GetDataSourceHandle();			// derzeit aktivierte DatenQuelle
	if ((HPROJECT)-2 == m_hPrCtx) {
		_ASSERTE(HACTCONNECTION == m_hPrCtx || 0 < (long)m_hPrCtx);
		m_hPrCtx = HACTCONNECTION;
	}

	switch (rgMode) {
	case DOCMODE_Get:			// Get Project (from currently opened )
	case DOCMODE_Add:
		break;

	case DOCMODE_Replace:		// replace Active Project
		DEX_MakeProjectActive(m_hPr);	
		break;

	case  DOCMODE_Remove:		// Close Project --> ne tut
	default:
		return E_INVALIDARG;		// Invalid DOCMODE_xxxxx
	}

	m_pUnk = pUnk;
	m_pApp = pApp;		// Applikation festhalten

// init GeoViews Tree 
	m_pViewTree = CViewTree::CreateInstance (m_pApp, this);
	if (m_pViewTree == NULL) return E_OUTOFMEMORY;

// init GeoClasses Trees 
	m_pClsTrees = CClsTrees::CreateInstance (m_pApp, this);
	if (m_pClsTrees == NULL) return E_OUTOFMEMORY;

// init GeoObjects Trees 
	m_pObjTrees = CObjTrees::CreateInstance (m_pApp, this);
	if (m_pObjTrees == NULL) return E_OUTOFMEMORY;

// init GeoObjectWin Tree 
	m_pObjWinTree = CObjWinTree::CreateInstance (m_pApp, this);
	if (m_pObjWinTree == NULL) return E_OUTOFMEMORY;

	return S_OK;
}

bool CGeoDoc::FInitInternal (LPCSTR bName)
{
// Copy Doc name
	if (NULL == bName || FAILED(SetName (bName, true)))
		return false;
	 
// Parent festhalten
CTriasApp *pApp = ((OLE2AutoExtension *)g_pTE) -> App();

	m_pUnk = (_DApplication *)pApp;
//	ADDREF (m_pUnk);
	
// Applikation festhalten
	m_pApp = pApp;
//	ADDREF (m_pApp);

// init GeoViews Tree 
	m_pViewTree = CViewTree::CreateInstance (m_pApp, this);
	if (m_pViewTree == NULL) return false;

// init GeoClasses Trees 
	m_pClsTrees = CClsTrees::CreateInstance (m_pApp, this);
	if (m_pClsTrees == NULL) return false;

// init GeoObjects Trees 
	m_pObjTrees = CObjTrees::CreateInstance (m_pApp, this);
	if (m_pObjTrees == NULL) return false;

// init GeoObjectWin Tree 
	m_pObjWinTree = CObjWinTree::CreateInstance (m_pApp, this);
	if (m_pObjWinTree == NULL) return false;

	return true;
}

CGeoDoc::~CGeoDoc (void)
{
	D_OUTF(1, "[%p] Destruct CGeoDoc!", this);
	DESTRUCT_TRACE(CGeoDoc);

	if (m_dwCookie) {
		FDisconnect (m_dwCookie);	// cancel connection
		m_dwCookie = 0L;
	}
	if (m_dwRegROTAll) 
		RevokeAsRunning (&m_dwRegROTAll);
	if (m_dwRegROT) 
		RevokeAsRunning (&m_dwRegROT);

//	RELEASE (m_pUnk);	// Parent wieder loslassen
//	RELEASE (m_pApp);	// Applikation wieder loslassen
	
	DELETE_OBJ (m_pViewTree);
	DELETE_OBJ (m_pClsTrees);
	DELETE_OBJ (m_pObjTrees);
	DELETE_OBJ (m_pObjWinTree);

	DELETE_OBJ (m_pName);
	DELETE_OBJ (m_pBuffer);
}

// Funktionen werden gerufen, wenn externe Locks entstehen bzw.
// verschwinden
ULONG CGeoDoc::InternalAddRef()
{
//	D_OUTF2(3, "[%p] CGeoDoc::InternalAddRef, ", this, "new refcnt: %ld", m_dwRef+1);
	_ASSERTE(m_dwRef != -1L);
	Lock();

long l = CComObjectRoot::InternalAddRef();

	if (m_dwRef == DOC_EXTERNAL_THRESHOLD+1) {
		Unlock();
		FinalExternalConstruct();
	} else 
		Unlock();
	return l;
}

ULONG CGeoDoc::InternalRelease()
{
//	D_OUTF2(3, "[%p] CGeoDoc::InternalRelease, ", this, "new refcnt: %ld", m_dwRef-1);
	Lock();

long l = CComObjectRoot::InternalRelease();

	if (m_dwRef == DOC_EXTERNAL_THRESHOLD) {
		Unlock();
		FinalExternalRelease();
	} else 
		Unlock();
	return l;
}

HRESULT CGeoDoc::FinalExternalConstruct (void)
{
//	D_OUTF(1, "[%p] CGeoDoc::FinalExternalConstruct", this);

	ADDREF(m_pUnk);
	ADDREF_CAST(_DApplication, m_pApp);
	return S_OK;
}

void CGeoDoc::FinalExternalRelease (void)
{
//	D_OUTF(1, "[%p] CGeoDoc::FinalExternalRelease", this);
	RELEASE_NONULL(m_pUnk);						// Parent wieder loslassen
	RELEASE_CAST(_DApplication, m_pApp);	// Applikation wieder loslassen
}

HRESULT CGeoDoc::CreateInstance (
	LPUNKNOWN pUnk, CTriasApp *pApp, LPCSTR bName, CGeoDoc **ppDoc, DOCMODE rgMode)
{
	D_OUTF(1, "[static] CGeoDoc::CreateInstance", "");

	if (NULL == ppDoc) {
		D_OUTF(1, "[static] CGeoDoc::CreateInstance ==> E_POINTER", "");
		return E_POINTER;
	}
	*ppDoc = NULL;

CComObject<CGeoDoc> *pDoc = NULL;

	try {
	// Create an instance of CGeoDoc.  Exit if an error occurs.
		THROW_FAILED_HRESULT(CComObject<CGeoDoc>::CreateInstance (&pDoc));
		THROW_FAILED_HRESULT(pDoc -> FInit (pUnk, pApp, rgMode, bName));

		pDoc -> AddRef();	// fertig initialisiert

	// establish connection to the application-supplied notifications
		THROW_FAILED_HRESULT(pDoc -> FConnect (&pDoc -> m_dwCookie));

	// Dokument bei OLE anmelden
		THROW_FAILED_HRESULT(pDoc -> Rename (bName));
	
	} catch (_com_error& hr) {
		D_OUTF(1, "[static] CGeoDoc::CreateInstance ==> Failed", "");
		DELETE_OBJ(pDoc);
		return _COM_ERROR(hr);
	}

// If execution has reached this point, then no errors have occurred.
	pDoc -> Validate();		// CGeoDoc is now valid
	*ppDoc = pDoc;
		
	return S_OK;
}


// Connection to the application-supplied notifications -----------------------
HRESULT CGeoDoc::FConnect (DWORD *pdwCookie)
{
	D_OUTF(1, "[%p] CGeoDoc::FConnect", this);
	
// besorgen des ConnectionPoint- Interfaces
LPCONNECTIONPOINT pCP = m_pApp -> GetConnectionPoint();

	if (pCP == NULL) return ResultFromScode (E_OUTOFMEMORY);

// Erzeugen der CExternalConnection
CDocumentConnection *pDC = CDocumentConnection::CreateInstance (this);

	if (pDC == NULL) {
		pCP -> Release();	// wird nicht mehr gebraucht
		return ResultFromScode (E_OUTOFMEMORY);
	}

HRESULT hr = pCP -> Advise (pDC, pdwCookie);

	pDC -> Release();	// wird jetzt vom ConnectionPoint gehalten
	pCP -> Release();	// wird nicht mehr gebraucht
	return hr;
}

void CGeoDoc::FDisconnect (DWORD dwCookie)
{
	D_OUTF(1, "[%p] CGeoDoc::FDisconnect", this);

LPCONNECTIONPOINT pCP = m_pApp -> GetConnectionPoint();

	if (pCP != NULL) {
		pCP -> Unadvise (dwCookie);
		pCP -> Release();
	} 
}

// sonstige Memberfunktionen --------------------------------------------------
HPROJECT CGeoDoc::GetProjectHandle (void)
{
	if (!m_fValid) return NULL;
	
	if (NULL == m_hPr)
		m_hPr = DEX_GetProjectHandle (GetName());

	return m_hPr;
}

bool CGeoDoc::CloseIt (void)
{
	D_OUTF(1, "[%p] CGeoDoc::CloseIt", this);

	if (!m_fValid) return false;
	
	if (NULL == m_hPr)
		GetProjectHandle();

	return DEX_CloseProject(m_hPr);
}

// Diverse ZugriffsFunktionen -------------------------------------------------
char *CGeoDoc::GetName (bool fForce)
{
	if (!fForce && !m_fValid) return NULL;
	return m_pName;
}

// Setzen/löschen eines neuen Textes --------------------------------------
HRESULT CGeoDoc::SetName (const char *pName, bool fIgnoreValid)
{
	if ((!fIgnoreValid && !m_fValid)) 
		return E_FAIL;
	if (NULL == pName)
		return E_INVALIDARG;

	if (pName) {
		DELETE_OBJ(m_pName);
		m_pName = NULL;
		
		ATLTRY(m_pName = new char [strlen(pName)+1]);
		if (NULL == m_pName)
			return E_OUTOFMEMORY;

		strcpy (m_pName, pName);
		strupr (m_pName);

		return S_OK;
	}
	 
/*	
RENAMEDOC RP;

	RP.m_pOldName = m_pName;
	RP.m_pNewName = pName;
	if (DEX_RenameProject (RP)) {
	// als erstes alten Text freigeben
		SysFreeString (m_pName);
		m_pName = NULL;
		
	// neuen Text kopieren
		m_pName = SysAllocString (pName);
		return true;
	}
*/

	return E_UNEXPECTED;
}

// remove physically ----------------------------------------------------------
bool CGeoDoc::Remove (void)
{
	if (!m_fValid) return false;
	
	if (CloseIt()) {
		m_mapTags.DeleteAll();
		Invalidate();
		return true;
	}
	return false;
}

char *CGeoDoc::ProjectName (void)
{
	if (!m_fValid) 
		return NULL;
	return m_pName;
}

// Teile eines Dokumentes neu zeichnen ----------------------------------------
void CGeoDoc::RePaint (long iXMin, long iYMin, long iXMax, long iYMax)
{
	if (!m_fValid) return;
	
	if (iXMin == -1)
		DEX_RePaint();
	else {
	RECT rcT;
	COORDCONVERT CC;
	long pts[2];

		CC.lpPkt = pts;
		CC.lpPt = (POINT *)&rcT.left;
		pts[0] = iXMin; pts[1] = iYMax;
		DEX_OCtoDC (CC);
			
		CC.lpPt = (POINT *)&rcT.right;
		pts[0] = iXMax; pts[1] = iYMin;
		DEX_OCtoDC (CC);
		DEX_RePaintRectWait (rcT);		
	}
}

// aktuelle Sicht neu generieren-----------------------------------------------
void CGeoDoc::ReBuildMethod (bool fFull)
{
	if (m_fValid) {
		if (fFull) {
			DEXN_ReScale();
			DEXN_ReReadIdents();
			DEXN_ReReadContainer();
		}
		DEX_RebuildSight();
	}
}


// Dokument ist nicht mehr geöffnet, alles zerlegen ---------------------------
void CGeoDoc::InvDoc (void)
{
	m_fValid = false;

	InternalAddRef();		// künstliches AddRef, damit nichts passiert	
	{
	// Bäume zerlegen
		DELETE_OBJ (m_pViewTree);
		DELETE_OBJ (m_pObjTrees);
		DELETE_OBJ (m_pClsTrees);
		DELETE_OBJ (m_pObjWinTree);

	// Notifikationen abschrauben
		if (m_dwCookie) {
			FDisconnect (m_dwCookie);	// cancel connection
			m_dwCookie = 0L;
		}

	// document isn't running any more
		if (m_dwRegROTAll) 
			RevokeAsRunning (&m_dwRegROTAll);
		if (m_dwRegROT) 
			RevokeAsRunning (&m_dwRegROT);
	}
	InternalRelease();		// künstliches AddRef aufheben
}

// Erzeugen einer leeren GeoObjects-Collection --------------------------------
// INITOBJCOLLECTIONPROC ------------------------------------------------------
extern "C" 
INITOBJSTATUS PASCAL GetObjectsTemplate (
		LPUNKNOWN pUnk, CTriasApp *pApp, CGeoDoc *pDoc, 
		container_wrappers::CCreator &rCollCr, DWORD dwData, long *plONr)
{
	if (plONr == NULL) {
		return INITOBJSTATUS_Exists;		// nothing to do (creates empty collection)
	} else if (*plONr != INVALID_ONR) {
	// fill only one object
	CGeoObject *pObject = pDoc -> FGetObjectDisp (*plONr);

		if (pObject) {
			if (NULL != ((CGeoObjectCreator &)rCollCr).InsertPtr (pObject)) {
				((_DGeoObject *)pObject) -> AddRef();
				return INITOBJSTATUS_Exists;
			}
		}
	} 
	return INITOBJSTATUS_Error;		// error !
}

HRESULT CGeoDoc::CreateNewGeoObjects (_DGeoObjects **ppIObjs)
{
// jetzt Collection der GeoObjects generieren
CGeoObjects *pCObjects = CGeoObjects::CreateInstance (
		(_DDocument *)this, m_pApp, this, GetObjectsTemplate, NULL, NULL);
	
	if (NULL == pCObjects) return E_OUTOFMEMORY;

HRESULT hr = ((_DGeoObjects *)pCObjects) -> QueryInterface (IID_DGeoObjects, (LPVOID *)ppIObjs);

	((_DGeoObjects *)pCObjects) -> Release();
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert ProgrammierInterface einer bestimmten Ansicht
DefineSmartInterface(Dispatch);
DefineSmartInterface2(DView, IID_DView);
DefineSmartInterface2(DGeoObject, IID_DGeoObject);
DefineSmartInterface2(DGeoObjectWin, IID_DGeoObjectWin);

HRESULT CGeoDoc::FGetGeoView (LPCSTR pcView, bool fCreate, _DView **ppIView)
{
	TEST_E_POINTER("CGeoDoc::FGetGeoView", ppIView);
	
	if (NULL == pcView) {		// keine Ansicht gegeben
		*ppIView = NULL;
		return S_OK;
	}

WDView View;

	if (NULL == FGetViewDisp (pcView, View.ppi(), fCreate ? VIEWMODE_Add : VIEWMODE_Get))
		return E_INVALIDARG;
	
	*ppIView = View.detach();
	return S_OK;
}

// Liefert ProgrammierInterface eines bestimmten Objektes
HRESULT CGeoDoc::FGetGeoObject (LONG lONr, _DGeoObject **ppIObj)
{
	if (INVALID_ONR == lONr) return E_INVALIDARG;
	if (NULL == ppIObj) return E_POINTER;

WDGeoObject Obj;

	if (NULL == FGetObjectDisp (lONr, Obj.ppi()))
		return E_INVALIDARG;

	*ppIObj = Obj.detach();
	return S_OK;
}

HRESULT CGeoDoc::FGetGeoObjectWin (HWND hWnd, DGeoObjectWin **ppIWin)
{
	if (NULL == hWnd) return E_INVALIDARG;
	if (NULL == ppIWin) return E_POINTER;

WDGeoObjectWin Win;

	if (NULL == FGetObjWinDisp (hWnd, Win.ppi()))
		return E_INVALIDARG;

	*ppIWin = Win.detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert aktuell eingestellten Moniker
HRESULT CGeoDoc::GetMoniker (IMoniker **ppIMk)
{
	if (NULL == ppIMk) return E_POINTER;

	if (NULL != (IUnknown *)m_FileMK) {
	WMoniker mk (m_FileMK);

		*ppIMk = mk.detach();
		return S_OK;
	}
	return E_UNEXPECTED;
}

