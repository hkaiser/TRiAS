// AuxUIOwner.h : Declaration of the CAuxUIOwner

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
// benötigte Interfaces

DefineSmartInterface(TRiASToolBar);
DefineSmartInterface(ConnectionPointContainer);

///////////////////////////////////////////////////////////////////////////////
// CAuxUIOwner

class CAuxUIOwner : 
	public ITRiASUIOwner,
	public ITRiASNotificationSink,
	public CComObjectRoot
{
public:
	typedef map<UINT, const UIOWNERPROCS *, less<UINT> > UIOwnerData;

		CAuxUIOwner();
		~CAuxUIOwner() {}

	BEGIN_COM_MAP(CAuxUIOwner)
		COM_INTERFACE_ENTRY(ITRiASUIOwner)
		COM_INTERFACE_ENTRY(ITRiASNotificationSink)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CAuxUIOwner)

	HRESULT FinalConstruct (void);
	HRESULT SetExtension (class CIdentsDBExtension *pExt);

public:
// *** ITRiASUIOwner specific functions ***
	STDMETHOD(OnUpdateUI) (THIS_ ITRiASBar *pIBar, ITRiASCmdUI *pCmdUI);
	STDMETHOD(OnSelect) (THIS_ ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG uiLen, ULONG *pulWritten);
	STDMETHOD(OnCommand) (THIS_ ITRiASBar *pIBar, UINT uiID, int nCode);

// *** ITRiASNotificationSink specific functions ***
	STDMETHOD(ServerEvent) (THIS_ SERVEREVT se);
	STDMETHOD(ProjectEvent) (THIS_ long hPr, PROJECTEVT pe, VARIANT vData);
	STDMETHOD(GeoViewEvent) (THIS_ long hPr, GEOVIEWEVT ve, VARIANT vData);
	STDMETHOD(GeoClassEvent) (THIS_ long hPr, GEOCLASSEVT ce, long ulIdent);
	STDMETHOD(GeoObjectEvent) (THIS_ long hPr, GEOOBJECTEVT oe, long lONr);
	STDMETHOD(GeoFeatureEvent) (THIS_ long hPr, GEOFEATUREEVT fe, long ulMCode);
	STDMETHOD(GeoRelationEvent) (THIS_ long hPr, GEORELATIONEVT re, long ulRCode);
	STDMETHOD(ObjectWindowEvent)(THIS_ OBJWNDEVT oe, long hORWnd);

	HRESULT DisConnectFromServer (void);

private:
	UIOwnerData m_Data;
	class CIdentsDBExtension *m_pXtsn;

	static const UIOWNERDATA m_rgUIOwnerData[];

	bool m_fOpenProject;
	bool m_fIsRO;

// ConnectionPoint
	WConnectionPointContainer m_Cont;
	DWORD m_dwCookie;

private:
///////////////////////////////////////////////////////////////////////////////
// Funktionsprototypen

// ENABLEPROC
	bool EnableAlways (ITRiASBar *pIBar, UINT uiID);			// immer 'true'
	bool DisableAlways (ITRiASBar *pIBar, UINT uiID);			// immer 'false'
	
	bool EnableOnWriteAble (ITRiASBar *pIBar, UINT uiID);		// wenn RO, dann passiviert

///////////////////////////////////////////////////////////////////////////////
// SELECTSTRINGIDPROC
	UINT CtrlIdIsStringID (ITRiASBar *pIBar, UINT uiID);		// ControlID ist gleichzeitig StringID

///////////////////////////////////////////////////////////////////////////////
// SELECTSTRINGSTRINGPROC

///////////////////////////////////////////////////////////////////////////////
// COMMANDPROC 
	HRESULT OnMetaCmdModIdent (ITRiASBar *pIBar, UINT uiID, int nCode);
	HRESULT OnMetaCmdDelIdent (ITRiASBar *pIBar, UINT uiID, int nCode);
	HRESULT OnMetaCmdModMCode (ITRiASBar *pIBar, UINT uiID, int nCode);
	HRESULT OnMetaCmdDelMCode (ITRiASBar *pIBar, UINT uiID, int nCode);
	HRESULT OnMetaCmdModRCode (ITRiASBar *pIBar, UINT uiID, int nCode);
	HRESULT OnMetaCmdDelRCode (ITRiASBar *pIBar, UINT uiID, int nCode);
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
	COMMANDPROC pFcnCmd;			// Befehl ausführen
} UIOWNERPROCS;

typedef struct tagUIOWNERDATA {
	UINT uiCtrlID;		// ControlID für den diese Daten gelten
	UIOWNERPROCS Procs;	// Funktionen, die das Verhalten steuern
} UIOWNERDATA;

