#ifndef _CPCOOKIEHELPEREVENTS_H_
#define _CPCOOKIEHELPEREVENTS_H_


template <class T>
class CProxyICookieHelperEvents : public IConnectionPointImpl<T, &IID_ICookieHelperEvents, CComDynamicUnkArray>
{
	//Warning this class may be recreated by the wizard.
public:
	HRESULT Fire_CookieHolderInitialized(BSTR Name, INT_PTR NewCookie)
	{
		HRESULT ret = S_FALSE;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			ICookieHelperEvents* pICookieHelperEvents = reinterpret_cast<ICookieHelperEvents*>(sp.p);
			if (pICookieHelperEvents != NULL)
				ret = pICookieHelperEvents->CookieHolderInitialized(Name, NewCookie);
		}	return ret;
	
	}
	HRESULT Fire_IssuedNextCookie(BSTR Name, INT_PTR NextCookie)
	{
		HRESULT ret = S_FALSE;
		T* pT = static_cast<T*>(this);
		int nConnectionIndex;
		int nConnections = m_vec.GetSize();
		
		for (nConnectionIndex = 0; nConnectionIndex < nConnections; nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			ICookieHelperEvents* pICookieHelperEvents = reinterpret_cast<ICookieHelperEvents*>(sp.p);
			if (pICookieHelperEvents != NULL)
				ret = pICookieHelperEvents->IssuedNextCookie(Name, NextCookie);
		}	return ret;
	
	}
};
#endif