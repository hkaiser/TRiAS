//////////////////////////////////////////////////////////////////////////////
// CProxyIVisQuery

#if _ATL_VER >= 0x200

template <class T>
class CProxyIVisQuery : 
	public IConnectionPointImpl<T, &IID_IVisQuery, CComDynamicUnkArray>
{
public:

//IVisQuery : IUnknown
public:
	HRESULT Fire_GetIdentMode(
		long Ident,
		BSTR View,
		IDENTVISMODE * VisMode)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_FALSE;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
			// der erste, der antwortet, bleibt der letzte
				IVisQuery* pIVisQuery = reinterpret_cast<IVisQuery*>(*pp);
				ret = pIVisQuery->GetIdentMode(Ident, View, VisMode);
				if (S_OK == ret) break;
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_GetObjectVis(
		long ObjNr,
		DVisInfo ** Vis)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_FALSE;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IVisQuery* pIVisQuery = reinterpret_cast<IVisQuery*>(*pp);
				ret = pIVisQuery->GetObjectVis(ObjNr, Vis);
				if (S_OK == ret) break;
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

#else // _ATL_VER >= 0x0200

class CProxyIVisQuery : public CComConnectionPoint<>
{
public:
	CProxyIVisQuery(IConnectionPointContainer* pCont) :
		CComConnectionPoint<>(pCont, &IID_IVisQuery)
	{
	}

	int empty() { return m_vec.end() > m_vec.begin() ? false : true; }

//IVisQuery : IUnknown
public:
	HRESULT Fire_GetIdentMode(
		long Ident,
		BSTR View,
		IDENTVISMODE * VisMode)
	{
		Lock();
		HRESULT ret = S_FALSE;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				IVisQuery* pIVisQuery = reinterpret_cast<IVisQuery*>(pcd->pUnk);
				ret = pIVisQuery->GetIdentMode(Ident, View, VisMode);
				if (S_OK == ret) break;
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
	HRESULT Fire_GetObjectVis(
		long ObjNr,
		DVisInfo ** Vis)
	{
		Lock();
		HRESULT ret = S_FALSE;
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				IVisQuery* pIVisQuery = reinterpret_cast<IVisQuery*>(pcd->pUnk);
				ret = pIVisQuery->GetObjectVis(ObjNr, Vis);
				if (S_OK == ret) break;
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
};

#endif // _ATL_VER >= 0x0200
