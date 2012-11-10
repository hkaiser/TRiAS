// AuxUIOwner.h : Declaration of the CAuxUIOwner

#if !defined(_AUXUIOWNER_H)
#define _AUXUIOWNER_H

///////////////////////////////////////////////////////////////////////////////
// Datentypen für tabellengesteuerte Arbeit des CAuxUIOwner

class CAuxUIOwner;		// forward declaration
typedef struct tagUIOWNERPROCS UIOWNERPROCS;
typedef struct tagUIOWNERDATA UIOWNERDATA;

// Funktionen für das Enable/Disable/SetCheck der Controls
typedef bool (CAuxUIOwner::* ENABLEPROC)(ITRiASBar *pIBar, UINT uiID);
typedef int (CAuxUIOwner::* CHECKSTATEPROC)(ITRiASBar *pIBar, UINT uiID);

// Funktionen für das generieren der Status/TooltipStrings 
typedef UINT (CAuxUIOwner::* SELECTSTRINGIDPROC) (ITRiASBar *pIBar, UINT uiID);
typedef bool (CAuxUIOwner::* SELECTSTRINGSTRINGPROC) (ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG ulLen);

// Funktionen, die das betreffende Kommando auslösen
typedef HRESULT (CAuxUIOwner::* COMMANDPROC) (ITRiASBar *pIBar, UINT uiID, int nCode);

///////////////////////////////////////////////////////////////////////////////
// CAuxUIOwner

class CAuxUIOwner : 
	public ITRiASUIOwner,
	public ITRiASNotificationSink,
	public CComObjectRoot
{
public:
	typedef multimap<UINT, const UIOWNERPROCS *, less<UINT> > UIOwnerData;

		CAuxUIOwner();
		~CAuxUIOwner() { DisConnectFromServer(); }

	BEGIN_COM_MAP(CAuxUIOwner)
		COM_INTERFACE_ENTRY(ITRiASUIOwner)
		COM_INTERFACE_ENTRY(ITRiASNotificationSink)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CAuxUIOwner)

	HRESULT FinalConstruct (void);

public:
// *** ITRiASUIOwner specific functions ***
	STDMETHOD(OnUpdateUI) (THIS_ ITRiASBar *pIBar, ITRiASCmdUI *pCmdUI);
	STDMETHOD(OnSelect) (THIS_ ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG uiLen, ULONG *pulWritten);
	STDMETHOD(OnCommand) (THIS_ ITRiASBar *pIBar, UINT uiID, int nCode);

// *** ITRiASNotificationSink specific functions ***
	STDMETHOD(ServerEvent) (THIS_ SERVEREVT se);
	STDMETHOD(ProjectEvent) (THIS_ long hPr, PROJECTEVT pe, VARIANT vProj);
	STDMETHOD(GeoViewEvent) (THIS_ long hPr, GEOVIEWEVT ve, VARIANT vData);
	STDMETHOD(GeoClassEvent) (THIS_ long hPr, GEOCLASSEVT ce, long ulIdent);
	STDMETHOD(GeoObjectEvent) (THIS_ long hPr, GEOOBJECTEVT oe, long lONr);
	STDMETHOD(GeoFeatureEvent) (THIS_ long hPr, GEOFEATUREEVT fe, long ulMCode);
	STDMETHOD(GeoRelationEvent) (THIS_ long hPr, GEORELATIONEVT re, long ulRCode);
	STDMETHOD(ObjectWindowEvent)(THIS_ OBJWNDEVT oe, long hORWnd);

	HRESULT SetXtsnSite (ITriasXtensionSite *pSite);
	HRESULT DisConnectFromServer (void);

private:
	UIOwnerData m_Data;

	bool m_fOpenProject;
	bool m_fIsRO;
	bool m_fIsDirty;
	bool m_fActiveView;
	bool m_fViewPainted;
	bool m_fPaintingView;

// ConnectionPoint
	WConnectionPointContainer m_Cont;
	DWORD m_dwCookie;

	static const UIOWNERDATA m_rgUIOwnerData[];

private:
///////////////////////////////////////////////////////////////////////////////
// Funktionsprototypen

// ENABLEPROC
	bool EnableAlways (ITRiASBar *pIBar, UINT uiID);			// immer 'true'
	bool DisableAlways (ITRiASBar *pIBar, UINT uiID);			// immer 'false'
	
	bool EnableOnWriteAble (ITRiASBar *pIBar, UINT uiID);		// wenn RO, dann passiviert

	bool EnableOnViewCont (ITRiASBar *pIBar, UINT uiID);		// Enable, wenn SichtContainer definiert ist
	bool EnableOnViewExist (ITRiASBar *pIBar, UINT uiID);		// Enable, wenn mindestens eine Ansicht existiert
	bool EnableViewActivated (ITRiASBar *pIBar, UINT uiID);		// Enable, wenn Sicht aktiviert ist
	bool EnableViewActivatedAndWriteAble (ITRiASBar *pIBar, UINT uiID);	// Enable, wenn nicht RO und Sicht ausgewählt

	bool EnableOnCanUndo (ITRiASBar *pIBar, UINT uiID);			// Enable, wenn Undo möglich ist
	bool EnableOnCanRedo (ITRiASBar *pIBar, UINT uiID);			// Enable, wenn Redo möglich ist

	bool EnableOnDirty (ITRiASBar *pIBar, UINT uiID);			// Enable, wenn GeoDB Dirty ist
	bool EnableOnCanCTFConfig (ITRiASBar *pIBar, UINT uiID);	// Enable, Sicht aktiv und CTF konfigurierbar ist

	bool EnableOnORWndsExist (ITRiASBar *pIBar, UINT uiID);		// Enable, wenn zumindest ein Objektrecherchefenster existiert

	bool EnableNotPainting (ITRiASBar *pIBar, UINT uiID);		// Enable, wenn derzeit nicht gezeichnet wird (für Overview)

#if _TRiAS_VER < 0x0400
	bool EnableWhenVer4 (ITRiASBar *pIBar, UINT uiID);			// Enable, wenn Version 4 emuliert werden soll
#endif // _TRiAS_VER < 0x0400

	bool EnableConnectFiltersExist (ITRiASBar *pIBar, UINT uiID);		// Enable, wenn ConnectFilter existieren

///////////////////////////////////////////////////////////////////////////////
// CHECKSTATEPROC
	int LegendeState (ITRiASBar *pIBar, UINT uiID);				// Legende anzeigen/ausblenden
	int HoldZoomState (ITRiASBar *pIBar, UINT uiID);			// Ausschnitt beibehalten/nicht beibehalten
	int OverviewState (ITRiASBar *pIBar, UINT uiID);			// Gesamtansicht anzeigen/ausblenden
	int PreventRepaintState (ITRiASBar *pIBar, UINT uiID);		// Neuzeichnen unterbinden
	int ShowConnectFilters (ITRiASBar *pIBar, UINT uiID);		// ConnectFilter anzeigen

///////////////////////////////////////////////////////////////////////////////
// SELECTSTRINGIDPROC
	UINT CtrlIdIsStringID (ITRiASBar *pIBar, UINT uiID);		// ControlID ist gleichzeitig StringID
	UINT DefaultStringID (ITRiASBar *pIBar, UINT uiID);			// immer AFX_IDLE_MESSAGE
	UINT StringIDForLegend (ITRiASBar *pIBar, UINT uiID);		// Legende mit Checkstate
	UINT StringIDForOverview (ITRiASBar *pIBar, UINT uiID);		// Overview mit Checkstate
	UINT StringIDForConnectFilter (ITRiASBar *pIBar, UINT uiID); // ConnectFilter mit Checkstate

///////////////////////////////////////////////////////////////////////////////
// SELECTSTRINGSTRINGPROC
	bool UndoSelectString (ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG ulLen);		// spezielles UndoString generieren
	bool RedoSelectString (ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG ulLen);

///////////////////////////////////////////////////////////////////////////////
// COMMANDPROC 
	HRESULT OnTRiASCmd (ITRiASBar *pIBar, UINT uiID, int nCode);			// TRiAS-Menubefehl zuordnen
	HRESULT OnSelectView (ITRiASBar *pIBar, UINT uiID, int nCode);			// Sicht aus ComboBox auswählen
	HRESULT OnSelectZoom (ITRiASBar *pIBar, UINT uiID, int nCode);			// Maßstab aus ComboBox auswählen
	HRESULT OnTRiASCmdFullScreen (ITRiASBar *pIBar, UINT uiID, int nCode);	// toggle FullScreenMode
	HRESULT	OnNewProject (ITRiASBar *pIBar, UINT uiID, int nCode);			// Neues Projekt erzeugen
	HRESULT	OnOpenProject (ITRiASBar *pIBar, UINT uiID, int nCode);			// Projekt öffnen
	HRESULT	OnHoldZoom (ITRiASBar *pIBar, UINT uiID, int nCode);			// Ausschnitt beibehalten
	HRESULT	OnPreventRepaint (ITRiASBar *pIBar, UINT uiID, int nCode);		// Neuzeichnen unterbinden
	HRESULT	OnManageDataSources (ITRiASBar *pIBar, UINT uiID, int nCode);	// Datenquellen verwalten
	HRESULT	OnPrintPreview (ITRiASBar *pIBar, UINT uiID, int nCode);		// Druckvorschau anzeigen
	HRESULT	OnLegendCmd (ITRiASBar *pIBar, UINT uiID, int nCode);			// Legende behandeln
	HRESULT	OnOverViewCmd (ITRiASBar *pIBar, UINT uiID, int nCode);			// Gesamtübersicht behandeln

	HRESULT	OnManageConnectFilters (ITRiASBar *pIBar, UINT uiID, int nCode);	// Connectfilter verwalten
	HRESULT	OnCreateConnectFilter (ITRiASBar *pIBar, UINT uiID, int nCode);		// Connectfilter erzeugen
	HRESULT	OnShowConnectFilters (ITRiASBar *pIBar, UINT uiID, int nCode);		// Connectfilter anzeigen

// helper routines
	bool GetZoom (ITRiASBar *pIBar, UINT uiID, long &rlZoom, bool fTestModify = true);
};

///////////////////////////////////////////////////////////////////////////////
// Datentypen, die statisch die Informationen zu allen behandelten Knöpfen 
// enthalten. Diese Informationen werden zur Laufzeit in einer map gespeichert.

typedef struct tagUIOWNERPROCS {
	ENABLEPROC pFcnClosed;			// Enable bei geschlossenem Projekt
	ENABLEPROC pFcnOpened;			// Enable bei geöffnetem Projekt
	CHECKSTATEPROC pFcnCheck;		// CheckState
	SELECTSTRINGIDPROC pFcnResID;	// StatusText aus Resource
	SELECTSTRINGSTRINGPROC pFcnResStr;	// StatusText aus String

	int iCode;						// nCode von WM_COMMAND, der ausgewertet werden soll
	COMMANDPROC pFcnCmd;			// Befehl ausführen
} UIOWNERPROCS;

typedef struct tagUIOWNERDATA {
	UINT uiCtrlID;		// ControlID für den diese Daten gelten
	UIOWNERPROCS Procs;	// Funktionen, die das Verhalten steuern
} UIOWNERDATA;

#endif // _AUXUIOWNER_H
