// Import aus dem DIRIS-ASC Austaschformat ------------------------------------
// File: DYNQUERY.CXX

#include "StdAfx.h"

#include <dirisole.h>
#include "DynQueryRes.h"	// ResourceKonstanten
#include "version.h"

#include <iobjman.h>
#include <initguid.h>		// nur im einem Module notwendig

#include <bscrguid.h>		// BSCRIPT.EXT
#include "dynqguid.h"

#include "Strings.h"
#include "DynQuery.hxx"		// die Erweiterung selbst

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(EnumLONG);							// WEnumLONG
DefineSmartInterface(QueryEnumLONG);
DefineSmartInterface(ExtendBScript);					// WExtendBScript
DefineSmartInterface(MergeVisInfo);
DefineSmartInterface(PersistStorage);					// WPersistStorage
DefineSmartInterface(PersistStream);

DefineSmartInterface2(DGeoObjects, IID_DGeoObjects);	// WDGeoObjects
DefineSmartInterface2(DAreaVisInfo, IID_DAreaVisInfo);	// WDAreaVisInfo

///////////////////////////////////////////////////////////////////////////////
// NEU: An Stelle der Funktionen NewExtension und GetExtensionCLSID muß die 
// Erweiterung jetzt in der ATL ObjectMap eingetragen werden (zusammen 
// mit allen anderen ATL-Objekten)
BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_DynQueryObjEnums, CDynQueryObjEnums)
	OBJECT_ENTRY(CLSID_DynamicQuery, CDynQueryExt)
// hier evtl. andere Objekte eintragen
// ...
END_OBJECT_MAP()

// mit der folgenden Funktion wird die ObjectMap in den ClassFactory-Mechanismus
// dieser Erweiterung eingebunden
_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// liefert ObjectMap
}

///////////////////////////////////////////////////////////////////////////////
// Alles weitere bleibt beim alten
// ...
//
// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll (empfohlen!!).
// Der ProgID (hier 'TRiAS.Simple.1') ist eine ZeichenKette, die die Erweiterung
// in der RegDB repräsentiert. Das Format sollte beibehalten werden. Die '... .1'
// steht für die VersionsNummer.
// Der KlassenName (hier die Stringresource hinter IDS_LONGCLASSNAME) ist eine 
// normal-lesbare Zeichenkette, die lokalisiert wird (deshalb in der Resource) und
// die Bezeichnung der Erweiterung definiert.
//
bool UpdateRegistry (bool fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
		return ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_DynamicQuery, 
				TEXT("TRiAS.DynamicQuery.1"), IDS_LONGCLASSNAME,
				DYNQUERY_MAJORVERSION, DYNQUERY_MINORVERSION,
				EFUnLoadable|EFVisible);
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_DynamicQuery, 
					      TEXT("TRiAS.DynamicQuery.1"));
	}

return true;	// alles ok
}


// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muß von der Klasse 'CTriasExtension'
// abgeleitet sein, welche wiederum als einzige Parameter die ResID's der
// im Hauptfenster und ORFenster einzuhängeneden Menu's übergeben bekommt.
CDynQueryExt::CDynQueryExt (void)
	: CTriasExtension (0, IDR_ORWNDMENU)
{
	m_pIScript = NULL;
	m_pIVisObj = NULL;
	m_dwCookie = 0L;
	m_StgMode = STGMODE_Unknown;	// noch nicht initialisiert
	m_fSelViewReg = false;
}

CDynQueryExt::~CDynQueryExt (void)
{
	ASSERT(NULL == m_pIScript);
	ASSERT(NULL == m_pIVisObj);
	ASSERT(!m_Stg);
	ASSERT(!m_ObjMan);
}

STDMETHODIMP_(bool) CDynQueryExt::InitExtension (short iMode) 
{
	if (!CTriasExtension::InitExtension(iMode))
		return false;

	RegisterNotification (DEX_N_EXTENSIONSLOADED);
	RegisterNotification (DEX_N_SAVESAMESTORAGE);
	RegisterNotification (DEX_N_SAVEOTHERSTORAGE);
	RegisterNotification (DEX_N_SAVECOMPLETED);
	RegisterNotification (DEX_N_HANDSOFFSTORAGE);
	RegisterNotification (DEX_PROJECTOPEN);
	RegisterNotification (DEX_N_PROJECTTOCLOSE);

	RegisterNotification (__DexCmd, FALSE);

// unser SubStorage öffnen, wenn Projekt geöffnet ist
	InitStorage();

// versuchen, die anderen Erweiterungen zu binden
	GetIBScript();
	RegisterVisQuery();		
	return true;
}

STDMETHODIMP_(bool) CDynQueryExt::UnLoadExtension (void)
{
	if (0 != m_dwCookie) {
		AtlUnadvise (m_pIVisObj, IID_IVisQuery, m_dwCookie);
		m_dwCookie = 0;
	}
	RELEASE(m_pIVisObj);
	RELEASE(m_pIScript);

	ReleaseStorage(false);

	UnRegisterNotification (__DexCmd, FALSE);

	UnRegisterNotification (DEX_N_SAVESAMESTORAGE);
	UnRegisterNotification (DEX_N_SAVEOTHERSTORAGE);
	UnRegisterNotification (DEX_N_SAVECOMPLETED);
	UnRegisterNotification (DEX_N_HANDSOFFSTORAGE);
	UnRegisterNotification (DEX_PROJECTOPEN);
	UnRegisterNotification (DEX_N_PROJECTTOCLOSE);

	HandleNotification (DEX_SIGHTSELECTED, m_fSelViewReg, false);

	return CTriasExtension::UnLoadExtension();
}

STDMETHODIMP_(bool) CDynQueryExt::MenuCommand (WPARAM wParam, HWND hWnd)
{
	TX_ASSERT(NULL != g_pTE);
	switch (wParam) {
	case IDM_SELECTEDOBJECTS:
		if (NULL != hWnd)
			return HilightSelectedObjects (hWnd);
		break;

	default:
		break;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// Handler für notifications
STDMETHODIMP_(LRESULT) CDynQueryExt::Notification (WPARAM wParam, LPARAM lParam)
{
	switch (wParam) {
	case DEX_PROJECTOPEN:
		OnProjectOpen();
		break;

	case DEX_N_PROJECTTOCLOSE:
		OnProjectToClose();
		break;

	case DEX_SIGHTSELECTED:
		OnViewSelected ((char *)lParam);
		break;

	case DEX_N_EXTENSIONSLOADED:
		OnExtensionsLoaded();
		break;
	
	case DEX_N_SAVESAMESTORAGE:
		OnSaveDocument ((IStorage *)lParam, true);
		break;

	case DEX_N_SAVEOTHERSTORAGE:
		OnSaveDocument ((IStorage *)lParam, false);
		break;

	case DEX_N_SAVECOMPLETED:
		OnSaveCompleted ((IStorage *)lParam);
		break;

	case DEX_N_HANDSOFFSTORAGE:
		OnHandsOffStorage();
		break;

	default:
		break;
	}

	return CTriasExtension::Notification (wParam, lParam);
}

STDMETHODIMP_(LRESULT) CDynQueryExt::WindowsNotification (
	UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	if (wMsg == __DexCmd) switch (wParam) {
	case DEX_QUERYPBDDATA:
		return OnQueryPbdData ((PBDDATA *)lParam);

	case DEX_MODPBDDATA:
		return OnModPbdData ((PBDDATA *)lParam);

	case DEX_DELPBDDATA:
		return OnDelPbdData ((PBDDATA *)lParam);

	case DEX_ENUMVIEWIDENTSEX:
		return OnEnumViewIdentsX ((ENUMTEXTKEYEX *)lParam);

	default:
		break;
	}
	
	return CTriasExtension::WindowsNotification (wMsg, wParam, lParam);
}

///////////////////////////////////////////////////////////////////////////////
// Notifications
bool CDynQueryExt::OnExtensionsLoaded (void)
{
	UnRegisterNotification (DEX_N_EXTENSIONSLOADED);

	GetIBScript();
	RegisterVisQuery();
	return true;
}

HRESULT CDynQueryExt::OnSaveDocument (IStorage *pIStg, bool fSameAsLoaded)
{
	ASSERT(STGMODE_Normal == m_StgMode);

	try {
	WStorage Stg (m_Stg);

		if (!fSameAsLoaded) 
			THROW_FAILED_HRESULT(GetSubStorage (pIStg, Stg.ppi(), true));

	WPersistStorage Init (m_ObjMan);

		THROW_FAILED_HRESULT(Init -> Save (Stg, fSameAsLoaded));
		THROW_FAILED_HRESULT(Stg -> Commit (STGC_DEFAULT));
		DEX_SetDirtyGeoDB (true);
		
		m_StgMode = STGMODE_NoScribble;

	} catch (_com_error& e) {
		return _COM_ERROR(e);
	}

	return S_OK;
}

HRESULT CDynQueryExt::OnSaveCompleted (IStorage *pIStg)
{
	ASSERT(STGMODE_NoScribble == m_StgMode || STGMODE_HandsOff == m_StgMode);

	try {
		if (NULL == pIStg) {
		// kann nicht zum Schreiben auf Storage freigegeben werden, da StoragePointer
		// NULL	nach HandsOffStorage()
			if (NULL == pIStg && STGMODE_HandsOff == m_StgMode) 
				return E_POINTER;

		WPersistStorage Init (m_ObjMan);

			THROW_FAILED_HRESULT(Init -> SaveCompleted (NULL));
		} else {
		// vorheriges Storage freigeben, neues geben lassen
			THROW_FAILED_HRESULT(GetSubStorage (pIStg, m_Stg.ppi()));

		WPersistStorage Init (m_ObjMan);

			THROW_FAILED_HRESULT(Init -> SaveCompleted (m_Stg));
		}
		m_StgMode = STGMODE_Normal;

	} catch (_com_error& e) {
		m_Stg.Assign(NULL);
		return _COM_ERROR(e);
	}

	return S_OK;
}

HRESULT CDynQueryExt::OnHandsOffStorage (void)
{
	try {
	WPersistStorage Init (m_ObjMan);

		THROW_FAILED_HRESULT(Init -> HandsOffStorage());
		
		m_Stg.Assign(NULL);
		m_StgMode = STGMODE_HandsOff;

	} catch (_com_error& e) {
		return _COM_ERROR(e);
	}

	return S_OK;
}

bool CDynQueryExt::OnProjectOpen()
{
	HandleNotification (DEX_SIGHTSELECTED, m_fSelViewReg);
	InitStorage();
	return true;
}

bool CDynQueryExt::OnProjectToClose()
{
	HandleNotification (DEX_SIGHTSELECTED, m_fSelViewReg, false);
	ReleaseStorage(false);
	return true;
}

bool CDynQueryExt::OnViewSelected (char *pcView)
{
	if (NULL == pcView) {		// keine Ansicht mehr aktiv
		m_Enums.Assign(NULL);
		return S_OK;
	}

	return SUCCEEDED(InitObjEnums (pcView));
}

///////////////////////////////////////////////////////////////////////////////
// PseudoIdentBehandlung
bool CDynQueryExt::OnQueryPbdData (PBDDATA *pData)
{
#if defined(_DEBUG)
	ASSERT_POINTER(pData, DWORD);
	if (sizeof(PBDMERKMAL) == pData -> dwSize) {
		ASSERT(AfxIsValidAddress(pData, sizeof(PBDMERKMAL), true));
	} else if (sizeof(PBDRELATION) == pData -> dwSize) {
		ASSERT(AfxIsValidAddress(pData, sizeof(PBDRELATION), true));
	} else {
		ASSERT(sizeof(PBDDATA) == pData -> dwSize);
		ASSERT(AfxIsValidAddress(pData, sizeof(PBDDATA), true));
	}
	ASSERT(NULL == pData -> pbdKText || AfxIsValidAddress(pData -> pbdKText, pData -> pbdKTextLen, true));
	ASSERT(NULL == pData -> pbdLText || AfxIsValidAddress(pData -> pbdLText, pData -> pbdLTextLen, true));
#endif // _DEBUG

	if ('i' != pData -> pbdTyp) return false;		// nur Idents behandeln

// Objektlisten durchsehen, ob dieser Ident bei uns bekannt ist
CComBSTR bstrOKS;

	if (S_OK == m_Enums -> ClassFromIdent (pData -> pbdCode, &bstrOKS)) {
		USES_CONVERSION;

	LPCSTR pcOKS = OLE2A(bstrOKS);
	int iLen = strlen (pcOKS);
	
		if (NULL != pData -> pbdKText) {		// KurzText
		int iKLen = min(iLen, pData -> pbdKTextLen-1);

			strncpy (pData -> pbdKText, pcOKS, iKLen);
			pData -> pbdKText[iKLen] = '\0';
			pData -> pbdKTextLen = iKLen;
		}
		
		if (NULL != pData -> pbdLText) {		// LangText
		int iLLen = min(iLen, pData -> pbdLTextLen-1);

			strncpy (pData -> pbdKText, pcOKS, iLLen);
			pData -> pbdLText[iLLen] = '\0';
			pData -> pbdLTextLen = iLLen;
		}
		return true;
	}

// nichts gefunden, normale Bearbeitung 
	return false;
}

bool CDynQueryExt::OnModPbdData (PBDDATA *pData)
{
#if defined(_DEBUG)
	ASSERT_POINTER(pData, DWORD);
	if (sizeof(PBDMERKMAL) == pData -> dwSize) {
		ASSERT_POINTER(pData, PBDMERKMAL);
	} else if (sizeof(PBDRELATION) == pData -> dwSize) {
		ASSERT_POINTER(pData, PBDRELATION);
	} else {
		ASSERT(sizeof(PBDDATA) == pData -> dwSize);
		ASSERT_POINTER(pData, PBDDATA);
	}
	ASSERT(NULL == pData -> pbdKText || AfxIsValidString(pData -> pbdKText));
	ASSERT(NULL == pData -> pbdLText || AfxIsValidString(pData -> pbdLText));
#endif // _DEBUG

	if ('i' != pData -> pbdTyp) return false;		// nur Idents behandeln

	return false;
}

bool CDynQueryExt::OnDelPbdData (PBDDATA *pData)
{
#if defined(_DEBUG)
	ASSERT_POINTER(pData, DWORD);
	if (sizeof(PBDMERKMAL) == pData -> dwSize) {
		ASSERT_POINTER(pData, PBDMERKMAL);
	} else if (sizeof(PBDRELATION) == pData -> dwSize) {
		ASSERT_POINTER(pData, PBDRELATION);
	} else {
		ASSERT(sizeof(PBDDATA) == pData -> dwSize);
		ASSERT_POINTER(pData, PBDDATA);
	}
#endif // _DEBUG

	if ('i' != pData -> pbdTyp) return false;		// nur Idents behandeln

	return false;
}

inline bool EnumIdentsCallback (bool (*pFcn)(long, DWORD, void *), 
				 long lKey, DWORD dwData, void *pData) 
{
	return ((ENUMLONGKEYEXCALLBACK)pFcn)(lKey, dwData, pData);
}

bool CDynQueryExt::OnEnumViewIdentsX (ENUMTEXTKEYEX *pEnumData)
{
	ASSERT_POINTER(pEnumData, ENUMTEXTKEYEX);
	ASSERT(AfxIsValidAddress(pEnumData -> eFcn, 1, false));

	if (NULL != pEnumData -> eKey && '\0' != *(pEnumData -> eKey))
		return false;		// aktuelle oder temporäre Sicht
	if (!(pEnumData -> eData & EnumVirtualData))
		return false;		// virtuelle Objektklassen nicht gefordert
		 
// Erstmal alle Idents der aktuellen Identlisten enumerieren
	try {
	WUnknown Unk;

		THROW_FAILED_HRESULT(m_Enums -> EnumIdents (Unk.ppi()));

	// alle derzeitigen Idents enumerieren
	WEnumLONG Enum (Unk);
	long lIdent;

		for (Enum -> Reset(); S_OK == Enum -> Next (1, &lIdent, NULL); /**/)
		{
		// erstmal alle geforderten ObjektTypen bestätigen
			if (false == EnumIdentsCallback (pEnumData -> eFcn, lIdent, pEnumData -> eData, pEnumData -> ePtr))
				throw LRESULT(false);	// abbrechen
		}

	} catch (_com_error &) {
		return false; 
	}

// nichts gefunden, bzw. normale Bearbeitung anschließen
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// StorageHandling

// Öffnen des SubStorages für die Objektlisten
HRESULT CDynQueryExt::GetSubStorage (IStorage *pIRootStg, IStorage **ppIStg, bool fCreate)
{
	if (NULL == ppIStg) return E_POINTER;

WStorage RootStg (pIRootStg);		// evtl. RootStorage besorgen

	if (!RootStg && !DEX_GetProjectStorage(*RootStg.ppv()))
		return E_FAIL;

	USES_CONVERSION;

WStorage IStg;
HRESULT hr = E_FAIL;

	{
	bool fRO = false;

		hr = RootStg -> OpenStorage (A2OLE(g_cbObjectLists), NULL, 
							STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
							NULL, 0L, IStg.ppi());
		if (FAILED(hr)) {
			if (STG_E_FILENOTFOUND == GetScode(hr) && fCreate) {
			// existiert nicht, evtl. neu erzeugen
				hr = RootStg -> CreateStorage (A2OLE(g_cbObjectLists), 
									STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED|STGM_CREATE, 
									0L, 0L, IStg.ppi());
				if (SUCCEEDED(hr))
					hr = WriteClassStg (IStg, CLSID_CObjectManagement);
				DEX_SetDirtyGeoDB (true);

			} else if (STG_E_ACCESSDENIED == GetScode(hr)) {
			// mit Schreibschutz versuchen
				hr = RootStg -> OpenStorage (A2OLE(g_cbObjectLists), NULL, 
								STGM_READ|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
								NULL, 0L, IStg.ppi());
				fRO = true;
			
			} else
				return hr;
		} 

		if (SUCCEEDED(hr)) {
		CLSID clsId;

			hr = ReadClassStg (IStg, &clsId);
			if (FAILED(hr)) return hr;

			if (!IsEqualCLSID(clsId, CLSID_CObjectManagement) && 
				!IsEqualCLSID(clsId, CLSID_NULL))
			{
				return E_FAIL;
			}

			if (IsEqualCLSID(clsId, CLSID_NULL) && !fRO)
				hr = WriteClassStg (IStg, CLSID_CObjectManagement);
		}
	}

	if (FAILED(hr)) return hr;

	*ppIStg = IStg.detach();
	return hr;
}

HRESULT CDynQueryExt::InitStorage (void)
{
	if (!DEX_TestActiveProject())		// nur bei bereits geöffnetem Projekt
		return E_UNEXPECTED;

	ASSERT(!m_Stg);
	ASSERT(!m_ObjMan);
	if (NULL != (IUnknown *)m_Stg) 
		m_Stg.Assign(NULL);
	if (NULL != (IUnknown *)m_ObjMan)
		m_ObjMan.Assign(NULL);

	try {
		THROW_FAILED_HRESULT(GetSubStorage (NULL, m_Stg.ppi(), true));

	WObjectManagement ObjMan (CLSID_CObjectManagement);

		m_ObjMan = ObjMan;

		{
		WPersistStorage Init (ObjMan);
		HRESULT hr = Init -> Load (m_Stg);

			if (S_FALSE == hr)
				hr = Init -> InitNew (m_Stg);
			
			if (FAILED(hr)) _com_issue_error(hr);
		}
		
		m_StgMode = STGMODE_Normal;
		THROW_FAILED_HRESULT(InitObjEnums());

	} catch (_com_error& e) {
		return _COM_ERROR(e);
	}

	return S_OK;
}

HRESULT CDynQueryExt::InitObjEnums (LPCSTR pcView)
{
	if (!DEX_TestActiveProject())		// nur bei bereits geöffnetem Projekt
		return E_UNEXPECTED;

char cbView[_MAX_PATH];

	if (NULL == pcView) {
		if (NULL == DEX_GetActiveSight(cbView))
			return S_FALSE;		// keine aktuelle Ansicht
		pcView = cbView;
	}

	USES_CONVERSION;

LPOLESTR pwView = A2OLE(cbView);
HRESULT hr = m_ObjMan -> GetObject (pwView, (IUnknown **)m_Enums.ppi());

	if (FAILED(hr)) {
		hr = m_ObjMan -> CreateObject (CLSID_DynQueryObjEnums, pwView, STGM_CREATE, (IUnknown **)m_Enums.ppi(), false);
		if (SUCCEEDED(hr)) {
			DEX_SetDirtyGeoDB(true);
			hr = m_Enums -> put_ViewName (CComBSTR(pwView));
		}
	}

	return hr;
}

HRESULT CDynQueryExt::ReleaseStorage (bool fSave)
{
HRESULT hr = S_OK;

	OnViewSelected (NULL);		// aktuellen Zustand speichern

	if (fSave && NULL != (IUnknown *)m_Stg) {
		hr = m_Stg -> Commit (STGC_DEFAULT);
		DEX_SetDirtyGeoDB (true);
	}
	m_Stg.Assign(NULL);
	m_StgMode = STGMODE_Unknown;

	m_ObjMan.Assign(NULL);
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Notifikationen sicher zuschalten/abschalten
bool CDynQueryExt::HandleNotification (UINT uiMsg, bool &rfFlag, bool fRegister)
{
	if (rfFlag == fRegister)
		return false;

	if (fRegister) {
		RegisterNotification (uiMsg);
		rfFlag = true;
	} else {
		UnRegisterNotification (uiMsg);
		rfFlag = false;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Erweiterung für BasicScripte binden 
HRESULT CDynQueryExt::GetIBScript (IExtendBScript **ppIBScript)
{
	if (NULL != ppIBScript) 
		*ppIBScript = NULL;		// für alle Fälle
	
	if (m_pIScript == NULL) {
	// zum ersten mal
	HRESULT hr = m_pXtnSite -> GetXtension (
			CLSID_MacroScriptExtension, IID_IExtendBScript, 
			(LPVOID *)&m_pIScript);

		if (FAILED(hr))	return hr;
	}

// erfolgreich gebunden
	if (NULL != ppIBScript) {
		*ppIBScript = m_pIScript;
		(*ppIBScript) -> AddRef();
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Erweiterung für Visualisierung binden 
HRESULT CDynQueryExt::GetIVisInfo (IVisObjExt **ppIVisObj)
{
	if (NULL != ppIVisObj) 
		*ppIVisObj = NULL;		// für alle Fälle
	
	if (m_pIVisObj == NULL) {
	// zum ersten mal
	HRESULT hr = m_pXtnSite -> GetXtension (
			CLSID_ObjVisInfoExtension, IID_IVisObjExt, (LPVOID *)&m_pIVisObj);

		if (FAILED(hr))	return hr;
	}

// erfolgreich gebunden
	if (NULL != ppIVisObj) {
		*ppIVisObj = m_pIVisObj;
		(*ppIVisObj) -> AddRef();
	}
	return S_OK;
}

HRESULT CDynQueryExt::RegisterVisQuery (void)
{
	if (0 != m_dwCookie)
		return E_UNEXPECTED;		// bereits initialisiert

	try {
		THROW_FAILED_HRESULT(GetIVisInfo());	// VisObj binden
		THROW_FAILED_HRESULT(AtlAdvise(m_pIVisObj, (IVisQuery *)this, IID_IVisQuery, &m_dwCookie));

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IVisQuery
STDMETHODIMP CDynQueryExt::GetIdentMode (LONG lIdent, BSTR bstrView, IDENTVISMODE *prgVisMode)
{
	TEST_E_POINTER("CDynQueryExt::GetIdentMode", prgVisMode);
	
	*prgVisMode = IDENTVISMODE_HasNewVI;
	return S_OK;
}

STDMETHODIMP CDynQueryExt::GetObjectVis (LONG lONr, DVisInfo **ppIVis)
{
	try {
	CComBSTR bstrName;
	WDVisInfo Vis;

		if (S_OK == m_Enums -> Find (lONr, &bstrName, Vis.ppi())) {
		WMergeVisInfo MergeVis (Vis);

			THROW_FAILED_HRESULT(MergeVis -> MergeVisInfo (-1, ppIVis));
			return S_OK;
		}
	
	} catch (_com_error& e) {
		return _COM_ERROR(e);
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// MenuBefehle
bool CDynQueryExt::HilightSelectedObjects (HWND hWnd)
{
WExtendBScript Bscript;
HRESULT hr = GetIBScript (Bscript.ppi());

	if (FAILED(hr)) return false;

// Function GetObjectsFromORWnd(ByVal hWnd As Long) As GeoObjects

const int OBJECTSFROMWND_NUMPARS = 1;
ebPARAM Pars[OBJECTSFROMWND_NUMPARS+1];
LPVOID cbParam[OBJECTSFROMWND_NUMPARS+1];
BSPARAM bs = { Pars, cbParam };

WDGeoObjects Objs;

	Pars[0].wType = TYP_APPOBJECT;	// Objs As GeoObjects (retval)
	_tcscpy (Pars[0].szExtType, g_cbGeoObjects);
	cbParam[0] = Objs.ppv();

	Pars[1].wType = TYP_LONG;		// hWnd As Long
	cbParam[1] = &hWnd;

	hr = Bscript -> RunCode (g_hInstance, IDR_SCRIPT_OBJFROMORWND,
					g_cbGetObjectsFromORWnd, OBJECTSFROMWND_NUMPARS, &bs);
	if (FAILED(hr)) return false;

	if (NULL != (IUnknown *)Objs) {
		try {
		WQueryEnumLONG Query (Objs);	// throws hr
		WEnumLONG Enum;
		WDAreaVisInfo Vis (CLSID_AreaVisInfo);

			Vis -> put_MainColor ((TRIASCOLOR)RGB(255, 0, 0));
			THROW_FAILED_HRESULT(Query -> QueryEnumLONG (Enum.ppi()));
			if (S_OK != m_Enums -> Insert (CComBSTR("test"), WEnumObjectsByNumber(Enum), Vis))
				_com_issue_error(E_FAIL);
			DEX_SetDirtyGeoDB(true);

		} catch (_com_error&) {
			return false;
		}

		return true;
	}

	return false;
}

