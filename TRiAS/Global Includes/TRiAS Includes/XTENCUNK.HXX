// Basisklasse und Controlling Unknown einer Erweiterung ----------------------
// File: XTSNCUNK.HXX

#if !defined(_XTSNCUNK_HXX)
#define _XTSNCUNK_HXX

// Deklarationen für alle Fälle -----------------------------------------------
typedef void (FAR PASCAL DESTROYNOTIFYPROC)(void);
typedef DESTROYNOTIFYPROC *DESTROYNOTIFYPROCPTR;
 
extern DESTROYNOTIFYPROC ObjectDestroyed;		// EntladeFunktion

// Plattform-spezifische Datendeklarationen -----------------------------------
#if defined(__CV__)	// CommonVu
class Menu;
class ResourceFile;
#endif

#if _TRiAS_VER >= 0x0300 && !defined(_XTENSIONSITE_INTERFACE) && !defined(_NO_XTENSIONSITE_INTERFACE)
#define _XTENSIONSITE_INTERFACE	
#endif // _TRiAS_VER >= 0x0300 ...

#if _TRiAS_VER < 0x0400
// Name des Hauptmodules ------------------------------------------------------
#undef TRIASMODULE
#if !defined(WIN16)
#if defined(_DEBUG)
#define TRIAS_MODULENAME	TEXT("TRIAS32D.EXE")
#else
#define TRIAS_MODULENAME	TEXT("TRIAS32.EXE")
#endif // _DEBUG
#else // WIN16
#define TRIAS_MODULENAME	TEXT("TRIAS.EXE")
#endif // WIN16
#endif // _TRiAS_VER < 0x0400

// eigentliche Basisklasse ----------------------------------------------------

// Diese Klasse implementiert zusätzlich alle Funktionen des StandardInterfaces 
// einer Erweiterung mit einer rudimentären Funktionalität. Der Nutzer der 
// Erweiterungsbibliothek muß genau die Funktionen neu definieren, die er 
// implementiert haben will. 

class CImpTriasXtension;	// forward declaration

class CTriasExtension 
	: public IUnknown 
{
private:
	LONG 		m_dwRefCnt;		// reference count

	DESTROYNOTIFYPROCPTR	m_pNotifProc;	// im Destruktor zu rufen

protected:
	LPUNKNOWN	m_pUnk;			// controlling unknown

public:
	ITriasXtensionSite *	m_pXtnSite;	// Interface, in welches wir eingebaut sind
#if defined(_XTENSIONSITE_INTERFACE)
	ITRiASServiceProvider *m_pIServiceProvider;
#endif // _XTENSIONSITE_INTERFACE

private:
// eigentliches Interface der Erweiterung
	CImpTriasXtension *	m_pTXtsn;

// spezifische Member einer TriasErweiterung
	HWND		m_hWndM;		// Hauptfenster der zugehörigen App
	HDEX 		m_hDex;			// Handle dieser Erweiterung
	UINT 		m_uiMenuOffset;		// in Trias verwendeter MenuOffset
	UINT 		m_uiMenuID;		// HauptMenu
	HMENU		m_hPopUpMenu;
	string		m_strMenuEntry;
	UINT 		m_uiORMenuID;		// ObjektMenu
	HMENU 		m_hPopUpORMenu;
	string		m_strORMenuEntry;

	short 		m_iMode;		// aktueller LadeMode dieser Erweiterung

#if defined(__CV__)	// CommonVu
	ResourceFile *	m_pRF;			// Verweis auf aktuellen ModuleNamen
	Menu *		m_pLoadedMenu;		// gesamtes Menu
	Menu *		m_pLoadedORMenu;	// Menu für ObjektFenster
	Window *	m_pMainWnd;			// HauptFenster
#if !defined(WIN16)
	Window *	m_pViewWnd;			// AnzeigeFenster
#endif // WIN16
#else // __CV__
	CMenu *		m_pLoadedMenu;   	// gesamtes Menu
	CMenu *		m_pLoadedORMenu; 	// Menu für ObjektFenster
	CWnd *		m_pWnd;			// Hauptfenster
#endif	// __CV__

	unsigned int 	m_fLoaded : 1;		// Erweiterung ist durch TRiAS geladen
#if !defined(__CV__)
	unsigned int 	m_fAttached : 1;	// m_pWnd wurde neu erzeugt
#endif // !__CV__

public:
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG, AddRef) (THIS);
	STDMETHOD_(ULONG, Release) (THIS);

// *** ITriasXtension specific functions *** 
	STDMETHOD_(HDEX, LoadExtension) (THIS_ TRIASLOADEX *pTL, HWND hWnd);
	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);
	STDMETHOD_(BOOL, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuSelect) (THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);
	STDMETHOD_(LRESULT, WindowsNotification) (THIS_ UINT wMsg, WPARAM wParam, 
						  LPARAM lParam);
	STDMETHOD_(LRESULT, GetCapabilities) (THIS_ UINT uiCap);
				      
// *** ITriasXtension2 specific functions ***
	STDMETHOD(SetXtensionSite) (THIS_ ITriasXtensionSite *pXtnSite);

// Konstruktor/Destruktor/Initialisierung
		CTriasExtension (UINT uiMenuID = 0, UINT uiORMenuID = 0);
	virtual	~CTriasExtension (void);

	HWND UnsubclassWindow(void);
		
private:
	BOOL __FInit (LPUNKNOWN lpUnk, DESTROYNOTIFYPROCPTR pProc);	// Initialisierung der Basisklasse
	BOOL __TestObjProps (void);
	BOOL __TestClassProps (void);

public:
// An-/Abmelden einer Notifikation von TRiAS(R)
	LRESULT RegisterNotification (UINT wMsg, BOOL = TRUE);
	LRESULT UnRegisterNotification (UINT wMsg, BOOL = TRUE);

// MenuPunkte in TRiAS installieren und wieder entfernen
#if _TRiAS_VER < 0x0300
	UINT InstallMenuItem (UINT iMenuID, UINT iMenuStr, bool iORMenu, 
			      short iPopupNum, short iMenuPos = -1);
	void RemoveMenuItem (UINT iMenuID, bool iORMenu, short iPopupNum);
#else
	UINT InstallMenuItem (UINT iMenuID, UINT iMenuStr, UINT iORMenu, 
			      short iPopupNum, short iMenuPos = -1);
	void RemoveMenuItem (UINT iMenuID, UINT iORMenu, short iPopupNum, short iMenuPos = -1);
#endif // _TRiAS_VER < 0x0300

// Werkzeug in TRiAS installieren und wieder entfernen
#if defined(__CV__)
	short InstallTool (ResID, LPCTSTR);
#else
	short InstallTool (UINT, const char *);
	short InstallTool (const char *, const char *);
#endif // __CV__
	void RemoveTool (short);

// Ladezustand der Erweiterung
	BOOL isLoaded (void) { return m_fLoaded ? true : false; }

// Menu's freigeben
	HMENU EmptyMenu (void);
	HMENU EmptyORMenu (void);
 
inline	HWND hWnd (void) { return m_hWndM; }	// HauptFenster
	HWND GetActiveORWindow (void);		// derzeit aktives ORFenster liefern

#if defined(__CV__)	// CommonVu
	pWindow MWind (void);			// Hauptfenster in TRIAS(R) (C++ - Klasse)
	pWindow ORWind (HWND hWnd);		// RechWindow zu Handle suchen
#if !defined(WIN16)
	pWindow MVWind (void);			// Liefert ViewFenster
#else // WIN16
inline pWindow MVWind (void) { return MWind(); }	// Liefert ViewFenster
#endif // WIN16)
#else
inline	CWnd *MWind (void) { return m_pWnd; }	// Hauptfenster in TRiAS
#endif // __CV__

// diverse Zugriffsfunktionen auf die Member (plattformunabhängig)
inline	HDEX hDex (void) { return m_hDex; }			// Handle dieser Erweiterung
inline	UINT MenuOffset (void) { return m_uiMenuOffset; }	// MenuOffset in TRiAS(R)
inline	short LoadState (void) { return m_iMode; }		// LadeMode der Erweiterung
inline	string &MenuEntry (void) const { return (string &)m_strMenuEntry; }	// Text für Hauptmenu
inline	string &ORMenuEntry (void) const { return (string &)m_strORMenuEntry; }
inline	HMENU MenuHandle (void) { return m_hPopUpMenu; }	// MenuHandle für Hauptmenu
inline	HMENU ORMenuHandle (void) { return m_hPopUpORMenu; } 	// MenuHandle für ORMenu

#if defined(__CV__)	// CommonVu
inline	ResourceFile &RF (void) { return *m_pRF; }		// der Resource-Module
inline	Menu *pExtMenu (void) const { return m_pLoadedMenu; }	// Hauptmenu (CommonVu)
inline	Menu *pExtORMenu (void) const { return m_pLoadedORMenu; } // ORMenu (CommonVu)
#else
inline	CMenu *pExtMenu (void) const { return m_pLoadedMenu; }  // HauptMenu (MFC)
inline	CMenu *pExtORMenu (void) const { return m_pLoadedORMenu; }
#endif // __CV__

inline	HRESULT GetXtensionSite (ITriasXtensionSite **ppXtsnSite);

friend class CXtensionClassFactory;
};

#if !defined(__CV__) // && !defined(WIN32)

//      DLL-spezische Klasse zur Verbindung mit den MFC-Klassen
class CExtDLL : public CWinApp
{
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtDLL)
	public:
	virtual BOOL InitInstance (void);	// Initialization
	virtual int ExitInstance (void);	// Termination (WEP-like code)
	//}}AFX_VIRTUAL

// nothing special for the constructor
		CExtDLL (const char* pszAppName) 
			: CWinApp(pszAppName) {}

//	virtual BOOL OnIdle (LONG lCount);

	//{{AFX_MSG(CExtDLL)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !__CV__ && !WIN32
						
// inline-Funktionen ----------------------------------------------------------
HRESULT CTriasExtension :: GetXtensionSite (ITriasXtensionSite **ppXtnSite)
{
	if (m_pXtnSite) {
		*ppXtnSite = m_pXtnSite;
		LPUNKNOWN(*ppXtnSite) -> AddRef();
		return NOERROR;
	} 
	return ResultFromScode (E_NOINTERFACE);
}

// sonstige globale Funktionen ------------------------------------------------
// Folgende Funktionen müssen von einer Implementation einer Erweiterung zur 
// Verfügung gestellt werden.
CTriasExtension *NewExtension (void);	// virtual constructor
BOOL GetExtensionCLSID (CLSID &);	// Liefert CLSID der Erweiterung

// die folgende Funktion muß nur dann zur Verfügung gestellt werden, wenn 
// eine TypeLibrary registriert werden soll
BOOL GetTypeLibGUID (GUID &);		// Liefert GUID der TypeLibrary

// die folgende Funktionen muß nur dann zur Verfügung gestellt werden, wenn 
// die TypeLibrary nicht als Resource an der Erweiterung gespeichert ist.
BOOL GetTypeLibName (TCHAR *cbBuffer);	// Liefert Namen der TypeLibrary

// Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung sich 
// selbst in der RegDB registrieren soll.
BOOL UpdateRegistry (BOOL fRegister);	// RegDB aktualisieren (initialisieren/löschen)

// Die Funktion GetLicenseKey muß definiert werden, wenn die Erweiterung lizensiert 
// sein soll. Der Parameter zeigt auf einen Puffer der gegebenen Größe (UNICODE), 
// in dem der Lizensierungsschlüssel dieser Erweiterung abzulegen ist.
#if defined(WIN16) || defined(OLE2ANSI)
BOOL GetLicenseKey (LPSTR, size_t iLen);
#else
BOOL GetLicenseKey (LPWSTR, size_t iLen);
#endif

// Die Funktion SetLicensed muß definiert werden, wenn die Erweiterung lizensiert
// sein soll. Sie wird gerufen, um abzufragen, ob die Erweiterung
// auf diesem Rechner lizensiert ist. Sie muß einen entsprechenden Rückkehrwert
// liefern (true für lizensiert, false für nicht lizensiert). 
BOOL GetLicensed (void);

// Die Funktion SetLicensed muß definiert werden, wenn die Erweiterung lizensiert
// sein soll. Sie wird gerufen, um der Erweiterung mitzuteilen, daß eine 
// erfolgreiche Abfrage der Lizenz beim Nutzer durchgeführt wurde. Normalerweise
// speichert diese Funktion an einer nur ihr bekannten Stelle diesen Fakt, damit
// die o.g. Funktion GetLicenseKey richtig reagieren kann.
#if !defined(WIN16)
BOOL SetLicensed (LPCSTR lpwNewKey);
#else
void SetLicensed (void);
#endif // WIN16

extern CTriasExtension *g_pTE;				// In jedem AddressRaum genau eine Instanz
extern "C" TCHAR FAR g_pDLLName[_MAX_PATH];
extern "C" HINSTANCE g_hInstance;

// FunktionsTypen, die bei Objekteigenschaften verwendet werden ---------------
// (hier lediglich für Kompatibilität mit alten ObjekteigenschaftsFunktionen)
typedef LPSTR (CALLBACK *OBJPROPCALLBACK)(LONG, LPSTR, short);
typedef LPSTR (CALLBACK *OBJPROPEXCALLBACK)(LONG, LPSTR, short, DWORD);
typedef void (CALLBACK *OBJPROPDELCALLBACK)(DWORD);

///////////////////////////////////////////////////////////////////////////////
// Prototypen für Umwandlung Ident <--> ObjektKlassenSchlüssel
const int MAX_OKS_LENX = 32;		// max. Zeichenkettenlänge für ObjektKlassenSchlüssel
HRESULT ClassFromIdentX (ULONG ulIdent, char *pBuffer, int iBuffLen = MAX_OKS_LENX);
HRESULT IdentFromClassX (LPCSTR pcClass, ULONG *pulIdent, BOOL fCreateNew = false);
HRESULT ClassFromIdentX (HPROJECT hPr, ULONG ulIdent, char *pBuffer, int iBuffLen = MAX_OKS_LENX);
HRESULT IdentFromClassX (HPROJECT hPr, LPCSTR pcClass, ULONG *pulIdent, BOOL fCreateNew = false);

#if !defined(_DEBUG)
///////////////////////////////////////////////////////////////////////////////
// Funktionen, die bei !_DEBUG als inline generiert werden

#if defined(__XT) && defined(__DEXPROCS) 
// zusätzliche Funktionen, die TRiAS direkt rufen -----------------------------
inline LRESULT DexExtensionProc (WPARAM w, LPARAM l)
{
#if defined(_XTENSIONSITE_INTERFACE)
	if (NULL != g_pTE && NULL != g_pTE -> m_pIServiceProvider)
		return LRESULT(g_pTE -> m_pIServiceProvider -> DexExtensionProc (w, l));
#endif // _XTENSIONSITE_INTERFACE

	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	return ::SendMessage (__hWndM, __DexCmd, w, l);
}
// zusätzliche Funktionen, die TRiAS direkt rufen -----------------------------
inline LRESULT DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l)
{
#if defined(_XTENSIONSITE_INTERFACE)
	if (NULL != g_pTE && NULL != g_pTE -> m_pIServiceProvider)
		return LRESULT(g_pTE -> m_pIServiceProvider -> DexExtensionProc2 (hPr, w, l));
#endif // _XTENSIONSITE_INTERFACE

	if (g_pDexExtensionProc2)
		return (*g_pDexExtensionProc2)(hPr, w, l);
		
	return ::SendMessage (__hWndM, __DexCmd, w, l);
}
#endif // __XT && __DEXPROCS 

inline 
HRESULT ClassFromIdentX (ULONG ulIdent, char *pBuffer, int iBuffLen)
{
CLASSFROMIDENT CFI;

	INITSTRUCT(CFI, CLASSFROMIDENT);
	CFI.ulIdent = ulIdent;
	CFI.pClass = pBuffer;
	CFI.iBuffLen = iBuffLen;
	if (NULL != pBuffer && iBuffLen > 0)
		pBuffer[0] = '\0';
	return DEX_GetClassFromIdent(CFI);
}

inline
HRESULT IdentFromClassX (LPCSTR pcClass, ULONG *pulIdent, BOOL fCreateNew)
{
	if (NULL == pulIdent) return E_POINTER;

IDENTFROMCLASS IFC;

	INITSTRUCT(IFC, IDENTFROMCLASS);
	IFC.pcClass = pcClass;
	IFC.fCreateNew = fCreateNew;

HRESULT hr = DEX_GetIdentFromClass(IFC);

	if (SUCCEEDED(hr)) 
		*pulIdent = IFC.ulIdent;

	return hr;
}

inline
HRESULT ClassFromIdentX (HPROJECT hPr, ULONG ulIdent, char *pBuffer, int iBuffLen)
{
CLASSFROMIDENT CFI;

	INITSTRUCT(CFI, CLASSFROMIDENT);
	CFI.ulIdent = ulIdent;
	CFI.pClass = pBuffer;
	CFI.iBuffLen = iBuffLen;
	if (NULL != pBuffer && iBuffLen > 0)
		pBuffer[0] = '\0';
	return DEX_GetClassFromIdentEx(hPr, CFI);
}

inline
HRESULT IdentFromClassX (HPROJECT hPr, LPCSTR pcClass, ULONG *pulIdent, BOOL fCreateNew)
{
	if (NULL == pulIdent) return E_POINTER;

IDENTFROMCLASS IFC;

	INITSTRUCT(IFC, IDENTFROMCLASS);
	IFC.pcClass = pcClass;
	IFC.fCreateNew = fCreateNew;

HRESULT hr = DEX_GetIdentFromClassEx(hPr, IFC);

	if (SUCCEEDED(hr)) 
		*pulIdent = IFC.ulIdent;

	return hr;
}
#endif // !_DEBUG

#endif // _XTSNCUNK_HXX
