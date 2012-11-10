
//////////////////////////////////////////////////////////////////////////////
// CProxyITRiASBarNotifySink
template <class T>
class CProxyITRiASBarNotifySink : 
	public IConnectionPointImpl<T, &IID_ITRiASBarNotifySink, CComDynamicUnkArray>
{
public:

// ITRiASBarNotifySink : IUnknown
public:
	HRESULT Fire_OnRequestAddButtons(
		ITRiASBar *pIBar, 
		int iIndex, 
		const TBBUTTON *pBttn, 
		int iCnt)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASBarNotifySink* pITRiASBarNotifySink = reinterpret_cast<ITRiASBarNotifySink*>(*pp);
				ret = pITRiASBarNotifySink->OnRequestAddButtons(pIBar, iIndex, pBttn, iCnt);
				if (S_OK != ret) break;
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_OnAddedButtons(
		ITRiASBar *pIBar, 
		int iIndex, 
		const TBBUTTON *pBttn, 
		int iCnt)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASBarNotifySink* pITRiASBarNotifySink = reinterpret_cast<ITRiASBarNotifySink*>(*pp);
				ret = pITRiASBarNotifySink->OnAddedButtons(pIBar, iIndex, pBttn, iCnt);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_OnRequestDeleteItem(
		ITRiASBar *pIBar, 
		UINT uiCtrlID, 
		DWORD dwStyle)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASBarNotifySink* pITRiASBarNotifySink = reinterpret_cast<ITRiASBarNotifySink*>(*pp);
				ret = pITRiASBarNotifySink->OnRequestDeleteItem(pIBar, uiCtrlID, dwStyle);
				if (S_OK != ret) break;
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_OnDeletedItem(
		ITRiASBar *pIBar, UINT uiCtrlID)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASBarNotifySink* pITRiASBarNotifySink = reinterpret_cast<ITRiASBarNotifySink*>(*pp);
				ret = pITRiASBarNotifySink->OnDeletedItem(pIBar, uiCtrlID);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

