// MainUIOwner.h : Declaration of the CMainUIOwner

///////////////////////////////////////////////////////////////////////////////
// CMainUIOwner

// Map CommandID's to ToolNumbers ---------------------------------------------
// ... from tool.hxx
#define NUMARROW 	0
#define NUMZOOM		1
#define NUMLUPE 	2
#define NUMSCHERE 	3
#define NUMLINEAL	4
#define NUMSCHRIFT	5

class CMainUIOwner : 
	public ITRiASUIOwner,
	public ITRiASNotificationSink,
	public CComObjectRoot
{
public:
	CMainUIOwner();
	~CMainUIOwner() { DisConnectFromServer(); }

	BEGIN_COM_MAP(CMainUIOwner)
		COM_INTERFACE_ENTRY(ITRiASUIOwner)
		COM_INTERFACE_ENTRY(ITRiASNotificationSink)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CMainUIOwner)

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
// ConnectionPoint
	WConnectionPointContainer m_Cont;
	DWORD m_dwCookie;

	bool m_fOpenProject;
	bool m_fActiveView;
	bool m_fViewPainted;
};

