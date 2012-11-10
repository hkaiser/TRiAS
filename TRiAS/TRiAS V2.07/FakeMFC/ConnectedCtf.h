// Connected CTF for maintenance of coordinate system configuration
// File: ConnectedCtf.h

#if !defined(_CONNECTEDCTF_H)
#define _CONNECTEDCTF_H

#include <ctfxmfc.h>

class CConnectedCtf :
	public ITRiASNotificationSink,
	public CComObjectRoot
{
public:
		CConnectedCtf() { m_pCTF = NULL; }
		~CConnectedCtf() { DisConnectFromServer(); }

	BEGIN_COM_MAP(CConnectedCtf)
		COM_INTERFACE_ENTRY(ITRiASNotificationSink)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CConnectedCtf)

	HRESULT FinalConstruct(void);

public:
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

public:
	bool LoadCTF (void);
	void ReleaseCTF (void);
	bool EnsureLoaded(void);

	bool Transform (double *pX, double *pY)
		{ if(!EnsureLoaded()) return false; ASSERT(NULL != m_pCTF); return m_pCTF -> Transform(pX, pY); }
	bool UnScale (const KoOrd &rX, const KoOrd &rY, double *pdX, double *pdY)
		{ if(!EnsureLoaded()) return false; ASSERT(NULL != m_pCTF); return m_pCTF -> UnScale (rX, rY, pdX, pdY); }
	char *CoordTransToStringEx (double dX, double dY, bool isX, char *pBuffer, short iLen)
		{ if(!EnsureLoaded()) return false; ASSERT(NULL != m_pCTF); return m_pCTF -> CoordTransToStringEx (dX, dY, isX, pBuffer, iLen); }
	double CoordTransDistance (const DoublePair *pDP1, const DoublePair *pDP2)
		{ if(!EnsureLoaded()) return false; ASSERT(NULL != m_pCTF); return m_pCTF -> CoordTransDistance (pDP1, pDP2); }
	char *CoordTransDescription (char *pBuffer, short iLen)
		{ if(!EnsureLoaded()) return false; ASSERT(NULL != m_pCTF); return m_pCTF -> CoordTransDescription (pBuffer, iLen); }

	bool CanConfig (void) 
		{ ASSERT(NULL != m_pCTF); return m_pCTF -> CanConfig(); }

private:
	WConnectionPointContainer m_Cont;
	DWORD m_dwCookie;
	CCoordTransX *m_pCTF;
};

#endif // _CONNECTEDCTF_H

