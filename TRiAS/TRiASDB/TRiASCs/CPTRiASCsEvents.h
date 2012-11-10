
//////////////////////////////////////////////////////////////////////////////
// CProxyITRiASCSEvents
template <class T>
class CProxyITRiASCSEvents : public IConnectionPointImpl<T, &IID_ITRiASCSEvents, CComDynamicUnkArray>
{
public:

//ITRiASCSEvents : IDispatch
public:
	HRESULT Fire_ChangingCS(
		ITRiASCS * PCS,
		VARIANT_BOOL * canChange)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASCSEvents* pITRiASCSEvents = reinterpret_cast<ITRiASCSEvents*>(*pp);
				ret = pITRiASCSEvents->ChangingCS(PCS, canChange);
				if (*canChange != VARIANT_FALSE) break;		// nicht erzeugen
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_CSToChange(
		ITRiASCS * PCS)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASCSEvents* pITRiASCSEvents = reinterpret_cast<ITRiASCSEvents*>(*pp);
				ret = pITRiASCSEvents->CSToChange(PCS);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_CSChanged(
		ITRiASCS * PCS)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASCSEvents* pITRiASCSEvents = reinterpret_cast<ITRiASCSEvents*>(*pp);
				ret = pITRiASCSEvents->CSChanged(PCS);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

