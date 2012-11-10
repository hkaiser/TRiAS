// Dynamische Erweiterungen zu DIRIS/Win ueber Nutzer-DLL's -------------------
// File: EXTMAIN2.HXX

#if !defined(_EXTMAIN_HXX)
#define _EXTMAIN_HXX

#include <xtensnxx.h>

// Ausgezogener Event, um an die EventParameter ranzukommen -------------------
#if !defined(NAKEDEVT)
#define NAKEDEVT
class NakedEvt : public Event {
public:
	UINT wmsg (void) { return wMsg; }
	WPARAM WParam (void) { return wParam; }
	WPARAM wparam (void) { return wParam; }
	LPARAM LParam (void) { return lParam; }
	LPARAM lparam (void) { return lParam; }
};
#endif // NAKEDEVT

// Eine derzeit geladenen Erweiterung -----------------------------------------
class MenuItemList;

typedef enum tagEXTENSIONFLAG {
	EF_Global = 0x01,
	EF_UnLoadable = 0x02,
	EF_Visible = 0x04,
	EF_CanImport = 0x08,
	EF_NoFlags = 0x00,
	EF_Flags = 0x0f,
} EXTENSIONFLAG;

class Extension {
public:
	enum ExtensionType {
		DirectExt = 1,
		OleExt = 2,
	};

private:
	ULONG m_ulRefCnt;	// ReferenzZähler
	
	UINT m_uiMenuOffset;	// ItemOffset

	int m_iMenuIndex;	// Index im HauptMenu
	int m_iORMenuIndex;	// Index im ObjRechMenu
	string m_strMenuString;	// Text im HauptMenu
	string m_strORMenuString;	// Text im ORMenu

	HMENU m_hMenuHandle;	// Handle des PopupMenu's
	HMENU m_hORMenuHandle;	// ObjRechMenu

	string m_strExtName;	// Bezeichnung dieser Erweiterung
	string m_strDLLName;	// Name dieser Erweiterung

	unsigned int m_iToLoad : 2;	// Erweiterung ist geladen

	unsigned int m_fIsGlobal : 1;	// Erweiterung ist global
	unsigned int m_fUnLoadable : 1;	// darf entladen werden
#if defined(WIN32)
	unsigned int m_fVisible : 1;	// in Dialogen angezeigt
#endif // WIN32
	unsigned int m_fCanImport : 1;	// ImportErweiterung

protected:
	HWND m_hWnd;		// FensterHandle

public:
// Konstruktor/Destruktor
		Extension (HWND, LPCSTR pExtName, LPCSTR pDLLName, int);
		Extension (Extension &);
	virtual	~Extension (void);

virtual	bool MenuInit (MenuInitEvt, HWND = 0) = 0;
virtual	bool MenuSelect (MenuSelectEvt, HWND = 0) = 0;
virtual	bool MenuCommand (MenuCommandEvt, HWND = 0) = 0;
virtual	HDEX Load (TRIASLOADEX &) = 0;
virtual	bool UnLoad (void) = 0;
virtual	bool Init (short iMode) = 0;

virtual	int GetCapability (WPARAM iCapType) = 0;
virtual	bool EnumObjPropFuncs (ENUMOBJPROPDATA *pEOPD) = 0;
virtual	char *InvokePropFunc (INVOKEOBJPROPDATA *) = 0;
virtual	char *GetHelpText (GETHELPTEXTDATA *) = 0;

virtual HDEX hLib (void) = 0;

virtual ExtensionType isA (void) = 0;
virtual	LRESULT Notify (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam) = 0;

// sonstige Memberfunktionen
	short isMyMenu (MenuInitEvt);
	bool isMyORMenu (MenuInitEvt);
	bool isMyID (UINT);
	bool hasMenuItems (short);

inline	ULONG AddRef (void) { return ++m_ulRefCnt; }
inline	ULONG Release (void) { return m_ulRefCnt ? --m_ulRefCnt : 0L; }

// InlineFunktionen für den direkten Zugriff auf diverse Member
inline	UINT &MenuOffset (void) { return m_uiMenuOffset; }
inline	int &MenuIndex (void) { return m_iMenuIndex; }
inline	int &ORMenuIndex (void) { return m_iORMenuIndex; }
inline	HMENU &MenuHandle (void) { return m_hMenuHandle; }
inline	HMENU &ORMenuHandle (void) { return m_hORMenuHandle; }
inline	string &ExtName (void) { return m_strExtName; }
inline	const string &DLLName (void) const { return m_strDLLName; }
inline	string &MenuString (void) { return m_strMenuString; }
inline	string &ORMenuString (void) { return m_strORMenuString; }
inline	int isLoaded (void) const { return m_iToLoad; }
inline	void SetLoaded (int iLoaded) { m_iToLoad = iLoaded; }
inline	bool isGlobal (void) const { return m_fIsGlobal ? true : false; }
inline	void SetGlobal (bool fGlobal) { m_fIsGlobal = (fGlobal ? true : false); }
inline	bool isUnLoadable (void) const { return m_fUnLoadable ? true : false; }
inline	void SetUnLoadable (bool fUnLoadable) { m_fUnLoadable = (fUnLoadable ? true : false); }
inline	HWND hWnd (void) const { return m_hWnd; }
#if defined(WIN32)
inline	bool isVisible (void) const { return m_fVisible ? true : false; }
inline	void SetVisible (bool fVisible) { m_fVisible = (fVisible ? true : false); }
#else
inline	bool isVisible (void) const { return true; }
inline	void SetVisible (bool fVisible) {}
#endif
inline	bool FCanImport (void) const { return m_fCanImport ? true : false; }
inline	void SetImport (bool fImport) { m_fCanImport = (fImport ? true : false); }

	EXTENSIONFLAG GetFlags (void);
};

class CDirectExtension : public Extension {
private:
	DLLBind *m_pDLL;
	DEXENTRY m_pExtEntry;	// DLL-Einstiegsfunktion

public:
		CDirectExtension (HWND, LPCSTR pExtName, LPCSTR pDLLName, int);
		CDirectExtension (HWND, LPCSTR pExtName, DLLBind *pDLL, LPCSTR pDLLName, int);
		CDirectExtension (CDirectExtension &);
		~CDirectExtension (void);

// virtuelle Funktionen
	HDEX Load (TRIASLOADEX &);
	bool UnLoad (void);
	bool Init (short iMode);

	bool MenuInit (MenuInitEvt, HWND = 0);
	bool MenuSelect (MenuSelectEvt, HWND = 0);
	bool MenuCommand (MenuCommandEvt, HWND = 0);

	ExtensionType isA (void);

	int GetCapability (WPARAM iCapType);
	bool EnumObjPropFuncs (ENUMOBJPROPDATA *pEOPD);
	char *InvokePropFunc (INVOKEOBJPROPDATA *);
	char *GetHelpText (GETHELPTEXTDATA *);
	
	LRESULT Notify (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

inline	DEXENTRY &Entry (void) const { return (DEXENTRY &)m_pExtEntry; }

	HDEX hLib (void); 
};

class COleExtension : public Extension {
private:
	LPTRIASXTENSION	m_pTE;		// OLE-Interface
	LPOBJECTPROPS m_pOPs;		// ObjektProperties
	HDEX m_hDex;
	CLSID m_ClsId;			// CLSID dieser Erweiterung

	unsigned int m_fHasOPs : 1;	// hat Objekteigenschaften

public:
		COleExtension (HWND hWnd, LPCSTR pTypeName, LPCSTR pProgID, 
			       REFCLSID rClsId, int toLoad);
		COleExtension (COleExtension &);
		~COleExtension (void);

// virtuelle Funktionen
	HDEX Load (TRIASLOADEX &);
	bool UnLoad (void);
	bool Init (short iMode);

	bool MenuInit (MenuInitEvt, HWND = 0);
	bool MenuSelect (MenuSelectEvt, HWND = 0);
	bool MenuCommand (MenuCommandEvt, HWND = 0);

	ExtensionType isA (void);

	int GetCapability (WPARAM iCapType);
	bool EnumObjPropFuncs (ENUMOBJPROPDATA *pEOPD);
	char *InvokePropFunc (INVOKEOBJPROPDATA *);
	char *GetHelpText (GETHELPTEXTDATA *);

	HDEX hLib (void);

	LRESULT Notify (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

	HRESULT GetImportIF (LPIMPORTGEODATA *);

	HRESULT HandleLicense (void);
};

#define LENoLoad	0x00
#define LEInitOnly	0x01
#define LEFullLoad	0x02

// Liste aller derzeit aktivierten Erweiterungen ------------------------------
class ExtensionList : public CListContainer {
private:
	FARPROC m_pDefaultProc;
	MenuItemList *m_pMIL;

protected:
	void UserDelete (void *pObj);

public:
// Konstruktor/Destruktor
		ExtensionList (void);
		~ExtensionList (void);

	short CountLoaded (short *piNotUnLoadable = NULL);
//	short CountUnLoaded (void) { return short(Count() - CountLoaded()); }
	LPSTR RetrieveDLLName (LPCSTR pExtName);
	LPSTR RetrieveExtName (LPCSTR pDLLName);

	short isLoaded (LPCSTR pDLLName, HDEX &hDex);

	bool isGlobal (LPCSTR pDLLName);
	bool isUnLoadable (LPCSTR pDLLName);
	bool isVisible (LPCSTR pDLLName);
	bool FCanImport (LPCSTR pDLLName);

	EXTENSIONFLAG GetFlags (LPCSTR pDLLName);

	DEXCALLBACK DefaultProc (void) { return (DEXCALLBACK)m_pDefaultProc; }

	bool DispatchMenuCommand (MenuCommandEvt, HWND = 0);

	bool hasMIL (void) { return m_pMIL != NULL; }
	MenuItemList &MIL (void) { return *m_pMIL; }
	
	long AddRef (LPCSTR pDLLName);
	long Release (LPCSTR pDLLName);

	Extension *FindExt (HDEX hDex);

friend class ExtDirisWindow;
};
DeclareLock (ExtensionList, Extension);

#if !defined(NOEXTDIRISWINDOW)

// HauptfensterKlasse, die Erweiterungen verwaltet ----------------------------
class QueryNotifyHash;

typedef struct tagCREATEOBJEKTINFO CREATEOBJEKTINFO;

class ExtDirisWindow : public IrisWind {
private:
	ExtensionList *m_pEL;
	QueryNotifyHash *m_pQNH;		// HashTabelle für QNFY's
	UINT m_iMenuOffset;

	unsigned m_fIsShown : 1;	// Fenster ist angezeigt
	unsigned m_fToShow : 1;		// Fenster soll angezeigt werden
	unsigned m_fToInit3d : 1;	// CTL3D.DLL verwenden

typedef LRESULT (ExtDirisWindow :: *DEXMESSAGE_PROC)(LPARAM);

	DEXMESSAGE_PROC *m_cbDexProcs;	// Sprungverteiler
	unsigned short m_i1stDexProc;	// erste Funktion
	unsigned short m_iDexProcsNum;	// Anzahl der Funktionen in Tabelle

#if defined(WIN32)
	class CManageUndoRedo *m_pUndoRedo;	// Undo/Redo - Verwaltung

	bool ShowRedoList (void);
	bool ShowUndoList (void);
#endif // WIN32

// Fehlerbehandlung für LoadExtension
	ErrInstall m_eiExt;

	bool FInitDexProcs (void);	// Initialisierung des Sprungverteilers

protected:
// Funktionen für Menuverarbeitung
	void Expose (ExposeEvt);		// zeichnen
	void MenuCommand (MenuCommandEvt);	// alle MenuCommands
	void MenuSelect (MenuSelectEvt);	// MenuAuswahl
	void MenuInit (MenuInitEvt);		// MenuInitialisierungen
	LRESULT Dispatch (Event);		// eigener Dispatcher
	bool QueryClose (Event);		// EndeAbfrage
	void Close (Event);			// Fenster wird geschlossen

	bool GenObjectProperties (void);

public:
// Konstruktor/Destruktor
		ExtDirisWindow (Rectangle &MWnd);
		~ExtDirisWindow (void);

	void Show (ShowState = Normal);

// sonstige Memberfunktionen
//	bool ParseCmdString (const int, const char **);

	bool doLoadExtension (void);		// MenuKommandos
	bool doUnLoadExtension (void);

	HDEX LoadExtension (LPCSTR pExtName, LPCSTR pDLLName, short iToLoad, 
		EXTENSIONFLAG rgFlags = EXTENSIONFLAG(EF_Visible|EF_Global));
	bool UnLoadExtension (LPCSTR pExtName, bool fForce = false);
	bool ReUnLoadExtension (LPCSTR pExtName, LPCSTR pDLLName, 
				short iMode = LEInitOnly);

	ErrCode LoadAllExtensions (const char *pIni, bool isGlobal = true);
	ErrCode LoadAllExtensionsINI (LPCSTR pIni, bool isGlobal = true);
	bool LoadAllExtensionsRegistry (void);
#if defined(WIN32)
	bool LoadExtensionRegistry (string &szTRiASKey);
#endif

	LRESULT FullFillWill (WPARAM, LPARAM);		// Messages bearbeiten
	LRESULT FullFillCPPWill (WPARAM, LPARAM);
	LRESULT Dispatch (UINT, WPARAM, LPARAM);	// QueryNotifications
	LRESULT DispatchNotification (WPARAM, LPARAM);
	
// Funktionen, die die Messages der Extension bearbeiten
	char *RetrieveActiveProject (char *);
	char *RetrieveMainProFile (char *);

	HWND CreateObjektInfo (DEXXCREATEOBJEKTINFO *);
	HWND CreateObjektInfo (CREATEOBJEKTINFO *);

	HMENU InstallMenuItem (INSTALLMENUITEM *);	// MenuPunkt installieren
	bool RemoveMenuItem (REMOVEMENUITEM *);		// und wieder rausnehmen

	short InstallTool (INSTALLTOOL *);		// Werkzeug einhängen
	bool RemoveTool (short);

	bool LoadLocalExtensions (void);
	bool UnLoadLocalExtensions (void);		// ProjektErweiterungen entladen

	bool FIsShown (void) { return m_fIsShown; }
	bool FToShow (void) { return m_fToShow; }
	bool FToInit3d (void) { return m_fToInit3d; }
	void FToShow (bool fToShow) { m_fToShow = fToShow ? true : false; }
	void FToInit3d (bool fToInit) { m_fToInit3d = fToInit ? true : false; }

	bool RenderGeoDB (RENDERGEODB *);
	bool doImport (void);	
	
_TRIAS_ENTRY friend LRESULT PASCAL EXPORTTRIAS DexExtensionProc (WPARAM w, LPARAM l);
_TRIAS_ENTRY friend LRESULT PASCAL EXPORTTRIAS DexxExtensionProc (WPARAM w, LPARAM l);
_TRIAS_ENTRY friend LRESULT PASCAL EXPORTTRIAS DexNotificationProc (WPARAM w, LPARAM l);
_TRIAS_ENTRY friend LRESULT PASCAL EXPORTTRIAS DexNotificationProcEx (WPARAM w, LPARAM l, bool fPost);

#if defined(DECLAREMAPFUNCTIONS)
#include "extfcns.hxx"		// Funktionsdeklarationen für MessageMap
#endif
};

typedef LRESULT (ExtDirisWindow :: *DEXMESSAGE_PROC)(LPARAM);
typedef struct tagDEXMESSAGE_ENTRY {
	UINT m_uiMsg;			// MessageID
	DEXMESSAGE_PROC m_pProc;	// zugehörige Funktion
} DEXMESSAGE_ENTRY;

// vorgegebene FunktionsTabelle (compilergeneriert) ---------------------------
#if !defined(WIN32)
extern "C" const DEXMESSAGE_ENTRY __cdecl __based(__segname("_CODE"))
		 DexMessageEntries[];
#else
extern "C" const DEXMESSAGE_ENTRY __cdecl DexMessageEntries[];
#endif // WIN32

#define DEXMESSAGE_ENTRYNUM sizeof(DexMessageEntries)/sizeof(DexMessageEntries[0])

#endif // NOEXTDIRISWINDOW

#endif // _EXTMAIN_HXX
