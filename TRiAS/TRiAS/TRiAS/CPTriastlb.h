
//////////////////////////////////////////////////////////////////////////////
// CProxyITRiASNotificationSink
class CProxyITRiASNotificationSink : public CComConnectionPoint<>
{
public:
	CProxyITRiASNotificationSink(IConnectionPointContainer* pCont) :
		CComConnectionPoint<>(pCont, &IID_ITRiASNotificationSink)
	{
	}

//ITRiASNotificationSink : IDispatch
public:
	HRESULT ServerEvent(
		SERVEREVT se)
	{
		Lock();
		HRESULT ret = S_OK;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				ITRiASNotificationSink* pITRiASNotificationSink = reinterpret_cast<ITRiASNotificationSink*>(pcd->pUnk);

			HRESULT hr = pITRiASNotificationSink->ServerEvent(se);

				if (S_FALSE == hr) {
					ret = S_FALSE;
					break;
				}
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
	HRESULT ProjectEvent(
		long hPr, PROJECTEVT pe,
		VARIANT vProj)
	{
		Lock();
		HRESULT ret = S_OK;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				ITRiASNotificationSink* pITRiASNotificationSink = reinterpret_cast<ITRiASNotificationSink*>(pcd->pUnk);
			
			HRESULT hr = pITRiASNotificationSink->ProjectEvent(hPr, pe, vProj);

				if (S_FALSE == hr) {
					ret = S_FALSE;
					break;
				}
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
	HRESULT GeoViewEvent(
		long hPr, GEOVIEWEVT ve,
		VARIANT vView)
	{
		Lock();
		HRESULT ret = S_OK;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				ITRiASNotificationSink* pITRiASNotificationSink = reinterpret_cast<ITRiASNotificationSink*>(pcd->pUnk);
			
			HRESULT hr = pITRiASNotificationSink->GeoViewEvent(hPr, ve, vView);

				if (S_FALSE == hr) {
					ret = S_FALSE;
					break;
				}
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
	HRESULT GeoClassEvent(
		long hPr, GEOCLASSEVT ce,
		long ulIdent)
	{
		Lock();
		HRESULT ret = S_OK;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				ITRiASNotificationSink* pITRiASNotificationSink = reinterpret_cast<ITRiASNotificationSink*>(pcd->pUnk);
			
			HRESULT hr = pITRiASNotificationSink->GeoClassEvent(hPr, ce, ulIdent);

				if (S_FALSE == hr) {
					ret = S_FALSE;
					break;
				}
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
	HRESULT GeoObjectEvent(
		long hPr, GEOOBJECTEVT oe,
		long lONr)
	{
		Lock();
		HRESULT ret = S_OK;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				ITRiASNotificationSink* pITRiASNotificationSink = reinterpret_cast<ITRiASNotificationSink*>(pcd->pUnk);
			
			HRESULT hr = pITRiASNotificationSink->GeoObjectEvent(hPr, oe, lONr);

				if (S_FALSE == hr) {
					ret = S_FALSE;
					break;
				}
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
	HRESULT GeoFeatureEvent(
		long hPr, GEOFEATUREEVT fe,
		long ulMCode)
	{
		Lock();
		HRESULT ret = S_OK;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				ITRiASNotificationSink* pITRiASNotificationSink = reinterpret_cast<ITRiASNotificationSink*>(pcd->pUnk);
			
			HRESULT hr = pITRiASNotificationSink->GeoFeatureEvent(hPr, fe, ulMCode);

				if (S_FALSE == hr) {
					ret = S_FALSE;
					break;
				}
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
	HRESULT GeoRelationEvent(
		long hPr, GEORELATIONEVT re,
		long ulRCode)
	{
		Lock();
		HRESULT ret = S_OK;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				ITRiASNotificationSink* pITRiASNotificationSink = reinterpret_cast<ITRiASNotificationSink*>(pcd->pUnk);
			
			HRESULT hr = pITRiASNotificationSink->GeoRelationEvent(hPr, re, ulRCode);

				if (S_FALSE == hr) {
					ret = S_FALSE;
					break;
				}
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
	HRESULT ObjectWindowEvent(
		OBJWNDEVT oe,
		long hORWnd)
	{
		Lock();
		HRESULT ret = S_OK;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				ITRiASNotificationSink* pITRiASNotificationSink = reinterpret_cast<ITRiASNotificationSink*>(pcd->pUnk);

			HRESULT hr = pITRiASNotificationSink->ObjectWindowEvent(oe, hORWnd);

				if (S_FALSE == hr) {
					ret = S_FALSE;
					break;
				}
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
};


//////////////////////////////////////////////////////////////////////////////
// CProxyITRiASSysNotificationSink
class CProxyITRiASSysNotificationSink : public CComConnectionPoint<>
{
public:
	CProxyITRiASSysNotificationSink(IConnectionPointContainer* pCont) :
		CComConnectionPoint<>(pCont, &IID_ITRiASSysNotificationSink)
	{
	}

//ITRiASSysNotificationSink : IDispatch
public:
	HRESULT WindowsMessage(
		long hWnd,
		long uiMsg,
		long wParam,
		long lParam)
	{
		Lock();
		HRESULT ret = S_OK;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				ITRiASSysNotificationSink* pITRiASSysNotificationSink = reinterpret_cast<ITRiASSysNotificationSink*>(pcd->pUnk);
				ret = pITRiASSysNotificationSink->WindowsMessage(hWnd, uiMsg, wParam, lParam);
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
};

