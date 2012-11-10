//
// File: ProgressProxy.h
// mit ATL generiert



// globale Parameter
extern ResourceFile* pRF;


#if defined(__ATL_20_USED__)
//////////////////////////////////////////////////////////////////////////////
// CProxyIProgressIndicator2
template <class T>
class CProxyIProgressIndicator2 : 
	public IConnectionPointImpl<T, &IID_IProgressIndicator2, CComDynamicUnkArray>,
	public BaseProgressStatus
{
public:

//IProgressIndicator2 : IDispatch
public:
	HRESULT InitNew(
		HWND hWndParent,
		unsigned long dwReserved,
		HWND * phWnd)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;	// für den Fall, daß while-Schleife nicht durchlaufen wird
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(*pp);
				ret = pIProgressIndicator2->InitNew((LONG)hWndParent, dwReserved, (LONG *)phWnd);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Restart(
		unsigned long ulMinPos,
		unsigned long ulMaxPos,
		tagPIFLAGS rgFlags)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;	// für den Fall, daß while-Schleife nicht durchlaufen wird
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
	HRESULT ChangeText(
		tagPIFLAGS rgWhichText,
		BSTR bstrNewText)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;	// für den Fall, daß while-Schleife nicht durchlaufen wird
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
//	HRESULT RetrieveText(
//		tagPIFLAGS rgWhichText,
//		BSTR * pbstrOutText)
//	{
//		T* pT = (T*)this;
//		pT->Lock();
//		HRESULT ret;
//		IUnknown** pp = m_vec.begin();
//		while (pp < m_vec.end())
//		{
//			if (*pp != NULL)
//			{
//				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(*pp);
//				ret = pIProgressIndicator2->RetrieveText(rgWhichText, pbstrOutText);
//			}
//			pp++;
//		}
//		pT->Unlock();
//		return ret;
//	}
//	HRESULT SetPosition(
//		unsigned long ulNewPos,
//		int * piPercent)
//	{
//		T* pT = (T*)this;
//		pT->Lock();
//		HRESULT ret;
//		IUnknown** pp = m_vec.begin();
//		while (pp < m_vec.end())
//		{
//			if (*pp != NULL)
//			{
//				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(*pp);
//				ret = pIProgressIndicator2->SetPosition(ulNewPos, piPercent);
//			}
//			pp++;
//		}
//		pT->Unlock();
//		return ret;
//	}
	HRESULT IncrementPosition(
		int * piPercent)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;	// für den Fall, daß while-Schleife nicht durchlaufen wird
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
	HRESULT IsCanceled()
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_FALSE;	// für den Fall, daß while-Schleife nicht durchlaufen wird
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
	HRESULT SetObjNr(
		long lONr)
	{
		T* pT = (T*)this;
		pT->Lock();

	HRESULT ret = S_OK;	// für den Fall, daß while-Schleife nicht durchlaufen wird

	tagPIFLAGS rgWhichText = PIFLAGS_RESULT;
	const short iBufferSize = 100;
	char pcBuffer [iBufferSize];
	ResString resObjekt (ResID (IDS_BEARB_OBJEKT, pRF), iBufferSize);
								
		wsprintf (pcBuffer, resObjekt.Addr (), lONr);

	CComBSTR bstrNewText (pcBuffer);	// char* in Bi-String konvertieren

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
};
#elif defined(__ATL_11_USED__)
//////////////////////////////////////////////////////////////////////////////
// CProxyIProgressIndicator2
class CProxyIProgressIndicator2 : public CComConnectionPoint<>, public BaseProgressStatus
{
public:
	CProxyIProgressIndicator2(IConnectionPointContainer* pCont) :
		CComConnectionPoint<>(pCont, &IID_IProgressIndicator2)
	{
	}

//IProgressIndicator2 : IDispatch
public:
	HRESULT InitNew (HWND hWndParent, unsigned long dwReserved, HWND* phWnd)
	{
		Lock();
		HRESULT ret = S_OK;	// für den Fall, daß while-Schleife nicht durchlaufen wird
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(pcd->pUnk);
				ret = pIProgressIndicator2->InitNew((INT_PTR)hWndParent, dwReserved, (INT_PTR*)phWnd);
			}
			pcd++;
		}
		Unlock();
		return ret;
	}


	HRESULT Restart (unsigned long ulMinPos, unsigned long ulMaxPos, tagPIFLAGS rgFlags)
	{
		Lock();
		HRESULT ret = S_OK;	// für den Fall, daß while-Schleife nicht durchlaufen wird
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(pcd->pUnk);
				ret = pIProgressIndicator2->Restart(ulMinPos, ulMaxPos, rgFlags);
			}
			pcd++;
		}
		Unlock();
		return ret;
	}


	HRESULT ChangeText (tagPIFLAGS rgWhichText, BSTR bstrNewText)
	{
		Lock();
		HRESULT ret = S_OK;	// für den Fall, daß while-Schleife nicht durchlaufen wird
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(pcd->pUnk);
				ret = pIProgressIndicator2->ChangeText(rgWhichText, bstrNewText);
			}
			pcd++;
		}
		Unlock();
		return ret;
	}

/*
	HRESULT RetrieveText (tagPIFLAGS rgWhichText, BSTR* pbstrOutText)
	{
		Lock();
		HRESULT ret = S_OK;	// für den Fall, daß while-Schleife nicht durchlaufen wird
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(pcd->pUnk);
				ret = pIProgressIndicator2->RetrieveText(rgWhichText, pbstrOutText);
			}
			pcd++;
		}
		Unlock();
		return ret;
	}


	HRESULT SetPosition (unsigned long ulNewPos, int* piPercent)
	{
		Lock();
		HRESULT ret = S_OK;	// für den Fall, daß while-Schleife nicht durchlaufen wird
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(pcd->pUnk);
				ret = pIProgressIndicator2->SetPosition(ulNewPos, piPercent);
			}
			pcd++;
		}
		Unlock();
		return ret;
	}
*/

	HRESULT IncrementPosition (int* piPercent)
	{
		Lock();
		HRESULT ret = S_OK;	// für den Fall, daß while-Schleife nicht durchlaufen wird
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(pcd->pUnk);
				ret = pIProgressIndicator2->IncrementPosition(piPercent);
			}
			pcd++;
		}
		Unlock();
		return ret;
	}


	HRESULT IsCanceled()
	{
		Lock();
		HRESULT ret = S_FALSE;	// für den Fall, daß while-Schleife nicht durchlaufen wird
		CONNECTDATA* pcd = m_vec.begin();
		CONNECTDATA* pcdend = m_vec.end();
		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(pcd->pUnk);
				ret = pIProgressIndicator2->IsCanceled();
			}
			pcd++;
		}
		Unlock();
		return ret;
	}


	// Objektnummer des gerade bearbeiteten Objektes an der Position PIFLAGS_RESULT
	// anzeigen
	HRESULT SetObjNr (long lONr)
	{
		Lock();

	HRESULT ret = S_OK;	// für den Fall, daß while-Schleife nicht durchlaufen wird
	CONNECTDATA* pcd = m_vec.begin();
	CONNECTDATA* pcdend = m_vec.end();

	tagPIFLAGS rgWhichText = PIFLAGS_RESULT;
	const short iBufferSize = 100;
	char pcBuffer [iBufferSize];
	ResString resObjekt (ResID (IDS_BEARB_OBJEKT, pRF), iBufferSize);
								
		wsprintf (pcBuffer, resObjekt.Addr (), lONr);

	CComBSTR bstrNewText (pcBuffer);	// char* in Bi-String konvertieren

		while (pcd < pcdend)
		{
			if (pcd->pUnk != NULL)
			{
				IProgressIndicator2* pIProgressIndicator2 = reinterpret_cast<IProgressIndicator2*>(pcd->pUnk);
				ret = pIProgressIndicator2->ChangeText(rgWhichText, bstrNewText);
			}
			pcd++;
		}

		Unlock();
		return ret;

	} // SetObjNr
};
#else
#error "Must define '__ATL_11_USED__ or __ATL_20_USED__'"
#endif // __ATL__
