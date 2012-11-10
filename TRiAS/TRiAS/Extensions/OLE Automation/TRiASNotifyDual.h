/////////////////////////////////////////////////////////////////////////////
// DTRiASNotificationSink wrapper class

DefineSmartInterface2(DTRiASNotificationSink, IID_DTRiASNotificationSink);

class COleTRiASNotificationSinkDual :
	public ITRiASNotificationSink,
	public CComObjectRoot
{
public:
		COleTRiASNotificationSinkDual();
		~COleTRiASNotificationSinkDual();

// dieses Objekt ist gleichzeitig Objekteigenschaft selbst
	BEGIN_COM_MAP(COleTRiASNotificationSinkDual)
		COM_INTERFACE_ENTRY(ITRiASNotificationSink)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(COleTRiASNotificationSinkDual)

	HRESULT FInit (DTRiASNotificationSink *pISinkDual);

// Attributes
public:

// Operations
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
	WDTRiASNotificationSink m_Sink;
};

