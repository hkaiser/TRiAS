/////////////////////////////////////////////////////////////////////////////
// ITRiASNotificationSink wrapper class für externe IDispatch's

#if !defined(_countof)
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif // !_countof

// Namen der DispFunktionen
const LPCOLESTR s_pcoleNames[] = 
{
	L"ServerEvent", 
	L"ProjectEvent", 
	L"GeoViewEvent",
	L"GeoClassEvent", 
	L"GeoObjectEvent", 
	L"GeoFeatureEvent",
	L"GeoRelationEvent", 
	L"ObjectWindowEvent",
};

// alternative Namen der DispFunktionen
const LPCOLESTR s_pcoleAltNames[] = 
{
	L"DTRiASNotificationSink_ServerEvent", 
	L"DTRiASNotificationSink_ProjectEvent", 
	L"DTRiASNotificationSink_GeoViewEvent",
	L"DTRiASNotificationSink_GeoClassEvent", 
	L"DTRiASNotificationSink_GeoObjectEvent", 
	L"DTRiASNotificationSink_GeoFeatureEvent",
	L"DTRiASNotificationSink_GeoRelationEvent", 
	L"DTRiASNotificationSink_ObjectWindowEvent",
};


class CTRiASNotificationSinkDisp : 
	public ITRiASNotificationSink,
	public COleDispatchDriver,
	public CComObjectRoot
{
public:
	CTRiASNotificationSinkDisp();		// Calls COleDispatchDriver default constructor
	~CTRiASNotificationSinkDisp() {}

// dieses Objekt ist gleichzeitig das NotificationSink selbst
	BEGIN_COM_MAP(CTRiASNotificationSinkDisp)
		COM_INTERFACE_ENTRY(ITRiASNotificationSink)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CTRiASNotificationSinkDisp)

	HRESULT FInit (IDispatch *pIDisp);

public:
// *** ITRiASNotificationSink methods
	STDMETHOD(ServerEvent)(THIS_ SERVEREVT se);
	STDMETHOD(ProjectEvent)(THIS_ long hPrj, PROJECTEVT pe, VARIANT vProj);
	STDMETHOD(GeoViewEvent)(THIS_ long hPrj, GEOVIEWEVT ve, VARIANT vData);
	STDMETHOD(GeoClassEvent)(THIS_ long hPrj, GEOCLASSEVT ce, long ulIdent);
	STDMETHOD(GeoObjectEvent)(THIS_ long hPrj, GEOOBJECTEVT oe, long lONr);
	STDMETHOD(GeoFeatureEvent)(THIS_ long hPrj, GEOFEATUREEVT fe, long ulMCode);
	STDMETHOD(GeoRelationEvent)(THIS_ long hPrj, GEORELATIONEVT re, long ulRCode);
	STDMETHOD(ObjectWindowEvent)(THIS_ OBJWNDEVT oe, long hORWnd);

private:
// DispatchID's 
	LCID m_lcid;
	DISPID m_dwDispId[_countof(s_pcoleNames)];
};

#define DISPID_SERVEREVENT			0
#define DISPID_PROJECTEVENT			1
#define DISPID_GEOVIEWEVENT			2
#define DISPID_GEOCLASSEVENT		3
#define DISPID_GEOOBJECTEVENT		4
#define DISPID_GEOFEATUREEVENT		5
#define DISPID_GEORELATIONEVENT		6
#define DISPID_OBJECTWINDOWEVENT	7
