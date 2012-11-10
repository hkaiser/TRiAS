
//////////////////////////////////////////////////////////////////////////////
// CProxyITRiASNotificationSink
template <class T>
class CProxyITRiASNotificationSink : public IConnectionPointImpl<T, &IID_ITRiASNotificationSink, CComDynamicUnkArray>
{
public:

//ITRiASNotificationSink : IUnknown
public:
	HRESULT Fire_ServerEvent(
		SERVEREVT Event)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASNotificationSink* pITRiASNotificationSink = reinterpret_cast<ITRiASNotificationSink*>(*pp);
				ret = pITRiASNotificationSink->ServerEvent(Event);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ProjectEvent(
		long Proj,
		PROJECTEVT Event,
		VARIANT Data)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASNotificationSink* pITRiASNotificationSink = reinterpret_cast<ITRiASNotificationSink*>(*pp);
				ret = pITRiASNotificationSink->ProjectEvent(Proj, Event, Data);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_GeoViewEvent(
		long Proj,
		GEOVIEWEVT Event,
		VARIANT Data)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASNotificationSink* pITRiASNotificationSink = reinterpret_cast<ITRiASNotificationSink*>(*pp);
				ret = pITRiASNotificationSink->GeoViewEvent(Proj, Event, Data);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_GeoClassEvent(
		long Proj,
		GEOCLASSEVT Event,
		long Ident)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASNotificationSink* pITRiASNotificationSink = reinterpret_cast<ITRiASNotificationSink*>(*pp);
				ret = pITRiASNotificationSink->GeoClassEvent(Proj, Event, Ident);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_GeoObjectEvent(
		long Proj,
		GEOOBJECTEVT Event,
		long ObjNr)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASNotificationSink* pITRiASNotificationSink = reinterpret_cast<ITRiASNotificationSink*>(*pp);
				ret = pITRiASNotificationSink->GeoObjectEvent(Proj, Event, ObjNr);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_GeoFeatureEvent(
		long Proj,
		GEOFEATUREEVT Event,
		long MCode)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASNotificationSink* pITRiASNotificationSink = reinterpret_cast<ITRiASNotificationSink*>(*pp);
				ret = pITRiASNotificationSink->GeoFeatureEvent(Proj, Event, MCode);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_GeoRelationEvent(
		long Proj,
		GEORELATIONEVT Event,
		long RCode)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASNotificationSink* pITRiASNotificationSink = reinterpret_cast<ITRiASNotificationSink*>(*pp);
				ret = pITRiASNotificationSink->GeoRelationEvent(Proj, Event, RCode);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ObjectWindowEvent(
		OBJWNDEVT Event,
		long ObjWind)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASNotificationSink* pITRiASNotificationSink = reinterpret_cast<ITRiASNotificationSink*>(*pp);
				ret = pITRiASNotificationSink->ObjectWindowEvent(Event, ObjWind);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};


//////////////////////////////////////////////////////////////////////////////
// CProxyITRiASSysNotificationSink
template <class T>
class CProxyITRiASSysNotificationSink : public IConnectionPointImpl<T, &IID_ITRiASSysNotificationSink, CComDynamicUnkArray>
{
public:

//ITRiASSysNotificationSink : IUnknown
public:
	HRESULT Fire_WindowsMessage(
		long hWnd,
		long uiMsg,
		long wParam,
		long lParam)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASSysNotificationSink* pITRiASSysNotificationSink = reinterpret_cast<ITRiASSysNotificationSink*>(*pp);
				ret = pITRiASSysNotificationSink->WindowsMessage(hWnd, uiMsg, wParam, lParam);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

