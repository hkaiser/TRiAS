/////////////////////////////////////////////////////////////////////////////
// ITRiASNotificationSink wrapper class für interne BasicScripte

DefineSmartInterface(ExtendBScript);

class CTRiASNotificationSinkBScript : 
	public ITRiASNotificationSink,
	public CComObjectRoot
{
public:
	CTRiASNotificationSinkBScript() {}		// Calls COleDispatchDriver default constructor
	~CTRiASNotificationSinkBScript() {}

// dieses Objekt ist gleichzeitig das NotificationSink selbst
	BEGIN_COM_MAP(CTRiASNotificationSinkBScript)
		COM_INTERFACE_ENTRY(ITRiASNotificationSink)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CTRiASNotificationSinkBScript)

	HRESULT FInit (CTriasApp *pApp, IExtendBScript *pIScript);

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

protected:
	HRESULT FireProjectEvent (HPROJECT hPr, LPCSTR pcRoutine, int iCnt, BSPARAM *pPar);
	HRESULT FireViewEvent (HPROJECT hPr, LPCSTR pcView, LPCSTR pcRoutine, BSPARAM *pPar, bool fCreate = false);
	HRESULT FireViewEventName (HPROJECT hPr, LPCSTR pcView, LPCSTR pcRoutine, BSPARAM *pPar);
	HRESULT FireObjectEvent (HPROJECT hPr, LONG lONr, LPCSTR pcRoutine, BSPARAM *pPar);
	HRESULT FireWindowEvent (HWND hWnd, LPCSTR pcRoutine, BSPARAM *pPar);
#if _TRiAS_VER >= 0x0300
	HRESULT FireFeatureEvent (HPROJECT hPr, LONG lONr, LPCSTR pcObjProp, LPCSTR pcRoutine, BSPARAM *pPar);
#endif // _TRiAS_VER >= 0x0300

private:
	CTriasApp *m_pApp;
	WExtendBScript m_Sink;		// hier soll's hin
};

