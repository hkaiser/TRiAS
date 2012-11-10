//////////////////////////////////////////////////////////////////////////////
// CProxyINotificationSink2

EXTERN_C const IID IID_INotificationSink2;

#if _ATL_VER >= 0x200

template <class T>
class CProxyINotificationSink2 : public IConnectionPointImpl<T, &IID_INotificationSink2, CComDynamicUnkArray>
{
//INotificationSink2 : IDispatch
public:
	ULONG Fire_ServerEvent(
		SERVEREVT se)
	{
		T* pT = (T*)this;
		pT->Lock();
		ULONG ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				INotificationSink2* pINotificationSink2 = reinterpret_cast<INotificationSink2*>(*pp);
				ret = pINotificationSink2->ServerEvent(se);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	ULONG Fire_ProjectEvent(
		PROJECTEVT pe,
		LPCTSTR pProj)
	{
		T* pT = (T*)this;
		pT->Lock();
		ULONG ret;
// Die nachfolgende Änderung ist notwendig, da innerhalb der gerufenen ProjectEvent-Funktion
// ein weiterer ConnectionPoint registriert wird (CDocumentConnection), was bei der Implementation
// in _ATL_VER >= 200 nicht immer, nun sagen wir, sicher ist. Deshalb wird die Laufvariable 
// jedesmal neu geladen.
//		IUnknown** pp = m_vec.begin();
//		while (pp < m_vec.end())
//		{
//			if (*pp != NULL)
//			{
//				INotificationSink2* pINotificationSink2 = reinterpret_cast<INotificationSink2*>(*pp);
//				ret = pINotificationSink2->ProjectEvent(pe, pProj);
//			}
//			pp++;
//		}
		IUnknown** pp = m_vec.begin();
		ULONG i = 0; 
		while (&pp[i] < m_vec.end())
		{
			if (*pp != NULL)
			{
				INotificationSink2* pINotificationSink2 = reinterpret_cast<INotificationSink2*>(*pp);
				ret = pINotificationSink2->ProjectEvent(pe, pProj);
			}
			++i;
			pp = m_vec.begin() + i;
		}
		pT->Unlock();
		return ret;
	}
	ULONG Fire_GeoViewEvent(
		GEOVIEWEVT ve,
		LPCTSTR pView)
	{
		T* pT = (T*)this;
		pT->Lock();
		ULONG ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				INotificationSink2* pINotificationSink2 = reinterpret_cast<INotificationSink2*>(*pp);
				ret = pINotificationSink2->GeoViewEvent(ve, pView);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	ULONG Fire_GeoClassEvent(
		GEOCLASSEVT ce,
		ULONG ulIdent)
	{
		T* pT = (T*)this;
		pT->Lock();
		ULONG ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				INotificationSink2* pINotificationSink2 = reinterpret_cast<INotificationSink2*>(*pp);
				ret = pINotificationSink2->GeoClassEvent(ce, ulIdent);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	ULONG Fire_GeoObjectEvent(
		GEOOBJECTEVT oe,
		LONG lONr)
	{
		T* pT = (T*)this;
		pT->Lock();
		ULONG ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				INotificationSink2* pINotificationSink2 = reinterpret_cast<INotificationSink2*>(*pp);
				ret = pINotificationSink2->GeoObjectEvent(oe, lONr);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	ULONG Fire_GeoFeatureEvent(
		GEOFEATUREEVT fe,
		ULONG ulMCode)
	{
		T* pT = (T*)this;
		pT->Lock();
		ULONG ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				INotificationSink2* pINotificationSink2 = reinterpret_cast<INotificationSink2*>(*pp);
				ret = pINotificationSink2->GeoFeatureEvent(fe, ulMCode);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	ULONG Fire_GeoRelationEvent(
		GEORELATIONEVT re,
		ULONG ulRCode)
	{
		T* pT = (T*)this;
		pT->Lock();
		ULONG ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				INotificationSink2* pINotificationSink2 = reinterpret_cast<INotificationSink2*>(*pp);
				ret = pINotificationSink2->GeoRelationEvent(re, ulRCode);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	ULONG Fire_ObjectWindowEvent(
		OBJWNDEVT oe,
		HWND hORWnd)
	{
		T* pT = (T*)this;
		pT->Lock();
		ULONG ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				INotificationSink2* pINotificationSink2 = reinterpret_cast<INotificationSink2*>(*pp);
				ret = pINotificationSink2->ObjectWindowEvent(oe, hORWnd);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

#else //  _ATL_VER == 0x0110

class CProxyINotificationSink2 : public CComConnectionPoint<>
{
public:
	CProxyINotificationSink2(IConnectionPointContainer* pCont) :
		CComConnectionPoint<>(pCont, &IID_INotificationSink2)
	{
	}

//INotificationSink2 : IDispatch
public:
	ULONG ServerEvent(
		SERVEREVT se)
	{
		Lock();
		ULONG ret;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				INotificationSink2* pINotificationSink2 = reinterpret_cast<INotificationSink2*>(pcd->pUnk);
				ret = pINotificationSink2->ServerEvent(se);
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
	ULONG ProjectEvent(
		PROJECTEVT pe,
		LPCTSTR pProj)
	{
		Lock();
		ULONG ret;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				INotificationSink2* pINotificationSink2 = reinterpret_cast<INotificationSink2*>(pcd->pUnk);
				ret = pINotificationSink2->ProjectEvent(pe, pProj);
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
	ULONG GeoViewEvent(
		GEOVIEWEVT ve,
		LPCTSTR pView)
	{
		Lock();
		ULONG ret;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				INotificationSink2* pINotificationSink2 = reinterpret_cast<INotificationSink2*>(pcd->pUnk);
				ret = pINotificationSink2->GeoViewEvent(ve, pView);
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
	ULONG GeoClassEvent(
		GEOCLASSEVT ce,
		ULONG ulIdent)
	{
		Lock();
		ULONG ret;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				INotificationSink2* pINotificationSink2 = reinterpret_cast<INotificationSink2*>(pcd->pUnk);
				ret = pINotificationSink2->GeoClassEvent(ce, ulIdent);
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
	ULONG GeoObjectEvent(
		GEOOBJECTEVT oe,
		LONG lONr)
	{
		Lock();
		ULONG ret;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				INotificationSink2* pINotificationSink2 = reinterpret_cast<INotificationSink2*>(pcd->pUnk);
				ret = pINotificationSink2->GeoObjectEvent(oe, lONr);
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
	ULONG GeoFeatureEvent(
		GEOFEATUREEVT fe,
		ULONG ulMCode)
	{
		Lock();
		ULONG ret;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				INotificationSink2* pINotificationSink2 = reinterpret_cast<INotificationSink2*>(pcd->pUnk);
				ret = pINotificationSink2->GeoFeatureEvent(fe, ulMCode);
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
	ULONG GeoRelationEvent(
		GEORELATIONEVT re,
		ULONG ulRCode)
	{
		Lock();
		ULONG ret;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				INotificationSink2* pINotificationSink2 = reinterpret_cast<INotificationSink2*>(pcd->pUnk);
				ret = pINotificationSink2->GeoRelationEvent(re, ulRCode);
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
	ULONG ObjectWindowEvent(
		OBJWNDEVT oe,
		HWND hORWnd)
	{
		Lock();
		ULONG ret;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				INotificationSink2* pINotificationSink2 = reinterpret_cast<INotificationSink2*>(pcd->pUnk);
				ret = pINotificationSink2->ObjectWindowEvent(oe, hORWnd);
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
};

#endif // _ATL_VER == 0x0100


