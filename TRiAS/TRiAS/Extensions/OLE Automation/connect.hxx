// ConnectionKlasse selbst (Node in der Liste aller Connections ---------------
// File: CONNECT.HXX

#if !defined(_CONNECT_HXX)
#define _CONNECT_HXX

///////////////////////////////////////////////////////////////////////////////
// Connection zu einem CTriasApp, das über die Veränderungen in TRiAS 
// informiert werden will
class CAppConnection : public INotificationSink2 
{
private:
	DWORD m_dwRefCnt;
	CTriasApp *m_pApp;

public:
		CAppConnection (CTriasApp *pApp);
		~CAppConnection (void);

static CAppConnection *CreateInstance (CTriasApp *pApp);

	bool FInit (void);

// *** IUnknown members 
	STDMETHOD(QueryInterface)(REFIID, LPVOID *);
	STDMETHOD_(ULONG, AddRef)(void);
	STDMETHOD_(ULONG, Release)(void);

// *** INotificationSink2 members
	STDMETHOD_(ULONG, ServerEvent)(THIS_ SERVEREVT se);
	STDMETHOD_(ULONG, ProjectEvent)(THIS_ PROJECTEVT pe, LPCTSTR pProj);
	STDMETHOD_(ULONG, GeoViewEvent)(THIS_ GEOVIEWEVT ve, LPCTSTR pView);
	STDMETHOD_(ULONG, GeoClassEvent)(THIS_ GEOCLASSEVT ce, ULONG ulIdent);
	STDMETHOD_(ULONG, GeoObjectEvent)(THIS_ GEOOBJECTEVT oe, LONG lONr);
	STDMETHOD_(ULONG, GeoFeatureEvent)(THIS_ GEOFEATUREEVT fe, ULONG ulMCode);
	STDMETHOD_(ULONG, GeoRelationEvent)(THIS_ GEORELATIONEVT re, ULONG ulRCode);
	STDMETHOD_(ULONG, ObjectWindowEvent)(THIS_ OBJWNDEVT oe, HWND hORWnd);

	STDMETHOD_(ULONG, MenuInitEvent)(THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(ULONG, MenuSelectEvent)(THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd);
	STDMETHOD_(ULONG, MenuCommandEvent)(THIS_ WPARAM wParam, HWND hWnd);
};

///////////////////////////////////////////////////////////////////////////////
// Connection zu einem CGeoDoc, das über die Veränderungen in TRiAS 
// informiert werden will
class CDocumentConnection : 
	public INotificationSink2 
{
private:
	DWORD m_dwRefCnt;
	CGeoDoc *m_pDoc;

public:
		CDocumentConnection (CGeoDoc *pDoc);
		~CDocumentConnection (void);

static CDocumentConnection *CreateInstance (CGeoDoc *pDoc);

	bool FInit (void);

// *** IUnknown members 
	STDMETHOD(QueryInterface)(REFIID, LPVOID *);
	STDMETHOD_(ULONG, AddRef)(void);
	STDMETHOD_(ULONG, Release)(void);

// *** INotificationSink2 members
	STDMETHOD_(ULONG, ServerEvent)(THIS_ SERVEREVT se);
	STDMETHOD_(ULONG, ProjectEvent)(THIS_ PROJECTEVT pe, LPCTSTR pProj);
	STDMETHOD_(ULONG, GeoViewEvent)(THIS_ GEOVIEWEVT ve, LPCTSTR pView);
	STDMETHOD_(ULONG, GeoClassEvent)(THIS_ GEOCLASSEVT ce, ULONG ulIdent);
	STDMETHOD_(ULONG, GeoObjectEvent)(THIS_ GEOOBJECTEVT oe, LONG lONr);
	STDMETHOD_(ULONG, GeoFeatureEvent)(THIS_ GEOFEATUREEVT fe, ULONG ulMCode);
	STDMETHOD_(ULONG, GeoRelationEvent)(THIS_ GEORELATIONEVT re, ULONG ulRCode);
	STDMETHOD_(ULONG, ObjectWindowEvent)(THIS_ OBJWNDEVT oe, HWND hORWnd);

	STDMETHOD_(ULONG, MenuInitEvent)(THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(ULONG, MenuSelectEvent)(THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd);
	STDMETHOD_(ULONG, MenuCommandEvent)(THIS_ WPARAM wParam, HWND hWnd);
};

#endif // _CONNECT_HXX

