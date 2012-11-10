// Basisklasse und Controlling Unknown einer Erweiterung ----------------------
// File: XTSNCATL.HXX

#if !defined(_XTSNCATL_HXX)
#define _XTSNCATL_HXX

// Plattform-spezifische Datendeklarationen -----------------------------------
#if defined(__CV__)	// CommonVu
class Menu;
class ResourceFile;
#endif

// Name des Hauptmodules ------------------------------------------------------
#undef TRIASMODULE
#if defined(_DEBUG)
#define TRIAS_MODULENAME	TEXT("TRIAS32D.EXE")
#else
#define TRIAS_MODULENAME	TEXT("TRIAS32.EXE")
#endif // _DEBUG

class CTriasExtension;				// fwd declaration only
extern CTriasExtension *g_pTE;		// In jedem AddressRaum genau eine Instanz

EXTERN_C const GUID IID_ITriasXtension;
EXTERN_C const GUID IID_ITriasXtension2;

// spezielle CreatorClass für Erweiterungen, die jeweils nur _eine_ Instanz zuläßt
template <class T1, class CTriasExtension *pTE>
class CComCreatorSingle
{
public:
	static HRESULT WINAPI CreateInstance(void* pv, REFIID riid, LPVOID* ppv)
	{
		_ASSERTE(*ppv == NULL);
		HRESULT hRes = E_OUTOFMEMORY;
		T1* p = NULL;
		if (NULL == pTE) 
		{
			ATLTRY(p = new T1(pv))
			if (p != NULL)
			{
				pTE = p;
				p->SetVoid(pv);
				p->InternalFinalConstructAddRef();
				hRes = p->FinalConstruct();
				p->InternalFinalConstructRelease();
				if (hRes == S_OK)
					hRes = p->QueryInterface(riid, ppv);
				if (hRes != S_OK) {
					delete p; p = NULL;
				}
			}
		} else 
			hRes = pTE->QueryInterface(riid, ppv);
		return hRes;
	}
};

#define DECLARE_NOT_AGGREGATABLE_SINGLE(x,p) public:\
	typedef CComCreator2< CComCreatorSingle< CComObject<x>, p >, CComFailCreator<CLASS_E_NOAGGREGATION> > _CreatorClass;
#define DECLARE_AGGREGATABLE_SINGLE(x,p) public:\
	typedef CComCreator2< CComCreatorSingle< CComObject<x>, p >, CComCreatorSingle< CComAggObject<x>, p > > _CreatorClass;
#define DECLARE_ONLY_AGGREGATABLE_SINGLE(x,p) public:\
	typedef CComCreator2< CComFailCreator<E_FAIL>, CComCreatorSingle< CComAggObject<x>, p > > _CreatorClass;

// eigentliche Basisklasse ----------------------------------------------------

// Diese Klasse implementiert zusätzlich alle Funktionen des StansdardInterfaces 
// einer Erweiterung mit einer rudimentären Funktionalität. Der Nutzer der 
// Erweiterungsbibliothek muß genau die Funktionen neu definieren, die er 
// implementiert haben will. 

class CTriasExtension :
	public ITriasXtension2,
	public CComObjectRoot
{
public:
	ITriasXtensionSite *m_pXtnSite;	// Interface, in welches wir eingebaut sind

protected:	// spezifische Member einer TriasErweiterung
	HWND		m_hWndM;			// Hauptfenster der zugehörigen App
	HDEX 		m_hDex;				// Handle dieser Erweiterung
	UINT 		m_uiMenuOffset;		// in Trias verwendeter MenuOffset
	UINT 		m_uiMenuID;			// HauptMenu
	HMENU		m_hPopUpMenu;
	string		m_strMenuEntry;
	UINT 		m_uiORMenuID;		// ObjektMenu
	HMENU 		m_hPopUpORMenu;
	string		m_strORMenuEntry;

	short 		m_iMode;			// aktueller LadeMode dieser Erweiterung

#if defined(__CV__)	// CommonVu
	ResourceFile *	m_pRF;			// Verweis auf aktuellen ModuleNamen
	Menu *		m_pLoadedMenu;		// gesamtes Menu
	Menu *		m_pLoadedORMenu;	// Menu für ObjektFenster
	Window *	m_pMainWnd;			// HauptFenster
	Window *	m_pViewWnd;			// AnzeigeFenster
#else // __CV__
	CMenu *		m_pLoadedMenu;   	// gesamtes Menu
	CMenu *		m_pLoadedORMenu; 	// Menu für ObjektFenster
	CWnd *		m_pWnd;				// Hauptfenster
#endif	// __CV__

	unsigned int 	m_fLoaded : 1;	// Erweiterung ist durch TRiAS geladen
#if !defined(__CV__)
	unsigned int 	m_fAttached : 1; // m_pWnd wurde neu erzeugt
#endif // !__CV__

public:
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
		
	BEGIN_COM_MAP(CTriasExtension)
		COM_INTERFACE_ENTRY(ITriasXtension)
		COM_INTERFACE_ENTRY(ITriasXtension2)
	END_COM_MAP()

private:
	BOOL __TestObjProps (void);
	BOOL __TestClassProps (void);

public:
	HRESULT FinalConstruct (void);

// An-/Abmelden einer Notifikation von TRiAS(R)
	LRESULT RegisterNotification (UINT wMsg, BOOL = TRUE);
	LRESULT UnRegisterNotification (UINT wMsg, BOOL = TRUE);

// MenuPunkte in TRiAS installieren und wieder entfernen
	UINT InstallMenuItem (UINT iMenuID, UINT iMenuStr, UINT iORMenu, 
			      short iPopupNum, short iMenuPos = -1);
	void RemoveMenuItem (UINT iMenuID, UINT iORMenu, short iPopupNum);

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
	pWindow MVWind (void);			// Liefert ViewFenster
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

inline	HRESULT GetXtensionSite (ITriasXtensionSite **ppXtsnSite)
	{
		if (m_pXtnSite) {	
			*ppXtsnSite = m_pXtnSite; LPUNKNOWN(*ppXtsnSite) -> AddRef();
			return NOERROR;
		}
		return E_NOINTERFACE;
	}

///////////////////////////////////////////////////////////////////////////////
// Funktionen für Objekteigenschaften
virtual string GetObjectPropertiesGroupName (void) { return string(""); }
virtual DWORD GetObjectPropertiesFlags (void) { return 0L; }
};

#if !defined(__CV__)

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

#endif // !__CV__
						
// sonstige globale Funktionen ------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
// Folgende Funktionen müssen von einer Implementation einer Erweiterung zur 
// Verfügung gestellt werden.
CTriasExtension *NewExtension (void);	// 'virtual' constructor
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
#if defined(OLE2ANSI)
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
BOOL SetLicensed (LPCSTR lpwNewKey);

///////////////////////////////////////////////////////////////////////////////
// sonstige Funktionen, die durch die Erweiterung ggf. Implementiert werden 
// können. Werden diese nicht implementiert, so werden DefaultFunktionen 
// eingebaut.
HRESULT TxGetClassObject (REFCLSID rclsid, REFIID riid, LPVOID *ppv);
HRESULT TxCanUnloadNow (void);
BOOL TxInitInstance (HINSTANCE hInst);
void TxExitInstance (void);

///////////////////////////////////////////////////////////////////////////////
// externe Variablen
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

#if !defined(_DEBUG)
///////////////////////////////////////////////////////////////////////////////
// Funktionen, die bei !_DEBUG als inline generiert werden

#if defined(__XT) && defined(__DEXPROCS) 
// zusätzliche Funktionen, die Trias direkt rufen -----------------------------
inline LRESULT DexExtensionProc (WPARAM w, LPARAM l)
{
	if (g_pDexExtensionProc)
		return (*g_pDexExtensionProc)(w, l);
		
	return ::SendMessage (__hWndM, __DexCmd, w, l);
}
inline LRESULT DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l)
{
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
#endif // !_DEBUG

#endif // _XTSNCATL_HXX
