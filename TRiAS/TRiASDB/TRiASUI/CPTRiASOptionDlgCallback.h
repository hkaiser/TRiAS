
//////////////////////////////////////////////////////////////////////////////
// CProxyITRiASOptionDlgCallback
template <class T>
class CProxyITRiASOptionDlgCallback : public IConnectionPointImpl<T, &IID_ITRiASOptionDlgCallback, CComDynamicUnkArray>
{
public:

//ITRiASOptionDlgCallback : IDispatch
public:
	HRESULT Fire_OnInitDialog(
		ITRiASOptionDlg * Dlg)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASOptionDlgCallback* pITRiASOptionDlgCallback = reinterpret_cast<ITRiASOptionDlgCallback*>(*pp);
				ret = pITRiASOptionDlgCallback->OnInitDialog(Dlg);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_OnGetDispInfoChildren(
		ITRiASOptionDlg * Dlg,
		ULONG ulItem,
		int * Children)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASOptionDlgCallback* pITRiASOptionDlgCallback = reinterpret_cast<ITRiASOptionDlgCallback*>(*pp);
				ret = pITRiASOptionDlgCallback->OnGetDispInfoChildren(Dlg, ulItem, Children);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_OnGetDispInfoImage(
		ITRiASOptionDlg * Dlg,
		ULONG ulItem,
		IDispatch * * Image)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASOptionDlgCallback* pITRiASOptionDlgCallback = reinterpret_cast<ITRiASOptionDlgCallback*>(*pp);
				ret = pITRiASOptionDlgCallback->OnGetDispInfoImage(Dlg, ulItem, Image);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_OnGetDispInfoExpandedImage(
		ITRiASOptionDlg * Dlg,
		ULONG ulItem,
		IDispatch * * SelImage)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASOptionDlgCallback* pITRiASOptionDlgCallback = reinterpret_cast<ITRiASOptionDlgCallback*>(*pp);
				ret = pITRiASOptionDlgCallback->OnGetDispInfoExpandedImage(Dlg, ulItem, SelImage);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_OnGetDispInfoText(
		ITRiASOptionDlg * Dlg,
		ULONG ulItem,
		BSTR * Text)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASOptionDlgCallback* pITRiASOptionDlgCallback = reinterpret_cast<ITRiASOptionDlgCallback*>(*pp);
				ret = pITRiASOptionDlgCallback->OnGetDispInfoText(Dlg, ulItem, Text);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_OnQueryContextMenu(
		ITRiASOptionDlg * Dlg,
		ULONG ulItem,
		INT_PTR hMenu,
		UINT uiFirst,
		UINT uiLast,
		UINT *puiLastID)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_FALSE;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASOptionDlgCallback* pITRiASOptionDlgCallback = reinterpret_cast<ITRiASOptionDlgCallback*>(*pp);
				ret = pITRiASOptionDlgCallback->OnQueryContextMenu(Dlg, ulItem, hMenu, uiFirst, uiLast, puiLastID);
				if (S_OK == ret) break;
				uiFirst = *puiLastID;		// der nächste braucht einen neuen Anfang
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_OnGetCommandString(
		ITRiASOptionDlg * Dlg,
		ULONG ulItem, 
		UINT uiCmd,
		DWORD dwFlags,
		BSTR * Desc)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_FALSE;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASOptionDlgCallback* pITRiASOptionDlgCallback = reinterpret_cast<ITRiASOptionDlgCallback*>(*pp);
				ret = pITRiASOptionDlgCallback->OnGetCommandString(Dlg, ulItem, uiCmd, dwFlags, Desc);
				if (S_OK == ret) break;
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_OnInvokeCommand(
		ITRiASOptionDlg * Dlg,
		ULONG ulItem, 
		INT_PTR hWnd,
		UINT uiCmd)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_FALSE;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASOptionDlgCallback* pITRiASOptionDlgCallback = reinterpret_cast<ITRiASOptionDlgCallback*>(*pp);
				ret = pITRiASOptionDlgCallback->OnInvokeCommand(Dlg, ulItem, hWnd, uiCmd);
				if (S_OK == ret) break;
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_OnOk(
		ITRiASOptionDlg * Dlg)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASOptionDlgCallback* pITRiASOptionDlgCallback = reinterpret_cast<ITRiASOptionDlgCallback*>(*pp);
				ret = pITRiASOptionDlgCallback->OnOk(Dlg);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_OnCancel(
		ITRiASOptionDlg * Dlg)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ITRiASOptionDlgCallback* pITRiASOptionDlgCallback = reinterpret_cast<ITRiASOptionDlgCallback*>(*pp);
				ret = pITRiASOptionDlgCallback->OnCancel(Dlg);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

