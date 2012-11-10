
//////////////////////////////////////////////////////////////////////////////
// CProxyIProgressIndicator2
template <class T>
class CProxyIProgressIndicator2 : public IConnectionPointImpl<T, &IID_IProgressIndicator2, CComDynamicUnkArray>
{
public:

//IProgressIndicator2 : IDispatch
public:
	HRESULT Fire_InitNew(
		long hWndParent,
		unsigned long dwReserved,
		long * phWnd)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(*pp);
				ret = pIProgressIndicator2->InitNew(hWndParent, dwReserved, phWnd);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_Restart(
		unsigned long ulMinPos,
		unsigned long ulMaxPos,
		tagPIFLAGS rgFlags)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(*pp);
				ret = pIProgressIndicator2->Restart(ulMinPos, ulMaxPos, rgFlags);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ChangeText(
		tagPIFLAGS rgWhichText,
		BSTR bstrNewText)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(*pp);
				ret = pIProgressIndicator2->ChangeText(rgWhichText, bstrNewText);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_RetrieveText(
		tagPIFLAGS rgWhichText,
		BSTR * pbstrOutText)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(*pp);
				ret = pIProgressIndicator2->RetrieveText(rgWhichText, pbstrOutText);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_SetPosition(
		unsigned long ulNewPos,
		int * piPercent)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(*pp);
				ret = pIProgressIndicator2->SetPosition(ulNewPos, piPercent);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_IncrementPosition(
		int * piPercent)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(*pp);
				ret = pIProgressIndicator2->IncrementPosition(piPercent);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_IsCanceled()
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(*pp);
				ret = pIProgressIndicator2->IsCanceled();
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_get_Flags(
		tagPIFLAGS * prgFlags)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(*pp);
				ret = pIProgressIndicator2->get_Flags(prgFlags);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_put_Flags(
		tagPIFLAGS prgFlags)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(*pp);
				ret = pIProgressIndicator2->put_Flags(prgFlags);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_RetrieveRange(
		unsigned long * pulMinPos,
		unsigned long * pulMaxPos)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(*pp);
				ret = pIProgressIndicator2->RetrieveRange(pulMinPos, pulMaxPos);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

