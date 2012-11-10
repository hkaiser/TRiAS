#include "stdafx.h"

#include <new>

// GUIDS
#include "objmanguid.h"
#include "iobjmex.h"
#include <iObjMan.h>

#include "enumex.h"
#include "ObjMn.h"

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100
 
////////////////////////////////////////////////////////////////////////////
// Smarts
DefineSmartInterface(ObjectHolder);
DefineEnumerator2(WUnknown, IID_IUnknown);

/////////////////////////////////////////////////////////////////////////////
// CEnumObjects
CEnumObjects::CEnumObjects()
{
	m_lDelayDel = -1;
	m_cRef = 0;
	m_itcur = m_listUnknowns.begin();
}
CEnumObjects::~CEnumObjects()
{
}

// *** IEnumUnknown methods
STDMETHODIMP CEnumObjects::Next(ULONG celt, IUnknown ** rgelt, ULONG * pceltFetched)
{
	DWORD cReturn = 0L;

	if (pceltFetched) *pceltFetched = 0L;
	if (NULL == rgelt || m_listUnknowns.end() == m_itcur) 
		return S_FALSE;
        	
	while (m_itcur != m_listUnknowns.end() && 0 < celt) 
	{
		*rgelt = (*m_itcur);
		
		if (NULL == *rgelt) return E_FAIL;

		(*rgelt) -> AddRef();
		rgelt++; m_itcur++;	// weiterzählen
		celt--;
		cReturn++;
	}
	if (pceltFetched) 
		*pceltFetched = (cReturn - celt);	// gelieferte Werte

	return S_OK;
}

STDMETHODIMP CEnumObjects::Skip(ULONG celt)
{
	if (0 == celt) return NOERROR;

	TYPEUnknownList::iterator it = m_itcur;

	while (it != m_listUnknowns.end()) 
	{
		++it;
		if (--celt == 0) 
		{
			m_itcur = it;
			return NOERROR;
		}
	}
	return S_FALSE;
}

STDMETHODIMP CEnumObjects::Reset(void)
{
	m_itcur = m_listUnknowns.begin();
	return S_OK;
}

STDMETHODIMP CEnumObjects::Clone(IEnumUnknown ** ppEnumUnk)
{
	ASSERT(ppEnumUnk);
	if (NULL == ppEnumUnk) return E_POINTER;

	NEnumWUnknown *pEnumUnk = NULL;

	*ppEnumUnk = NULL;

	try
	{// Geladenen enumerieren
	TYPEUnknownList::iterator it = m_listUnknowns.begin();
		
		pEnumUnk = new NEnumWUnknown;		// Neuen Enumerator erzeugen
		while (it != m_listUnknowns.end())
		{// Liste der ObjectWrapper durchlaufen
		WObjectHolder IOH (*it);
		WUnknown IU;

			THROW_FAILED_HRESULT(IOH -> GetObject(IU.ppi()));

			// AddRef(,..
			pEnumUnk -> AddItem(IU);
			it++;
		}
	}
	catch (_com_error &e)
	{
		if (pEnumUnk) pEnumUnk -> Release();
		pEnumUnk = NULL;
		return _COM_ERROR(e);
	}
	catch (bad_alloc)
	{
		if (pEnumUnk) pEnumUnk -> Release();
		pEnumUnk = NULL;
		return E_OUTOFMEMORY;
	}

	*ppEnumUnk = (LPENUMUNKNOWN)pEnumUnk;
	(*ppEnumUnk) -> Reset();
	
	return NOERROR;
}

// *** IEnumUnknownExtended methods
STDMETHODIMP CEnumObjects::Delete(BSTR bstr)
{
	HRESULT hr = NOERROR;
	try
	{
		WUnknown IU;
		THROW_FAILED_HRESULT(Find(bstr, IU.ppi()));

		WObjectHolder IOH = IU;
		m_listUnknowns.remove(IU);
	/*	if (S_FALSE == IOH -> SetDelayedDel())
		{// Später löschen, wenn RefCount von internem Objekt == 1
			m_listUnknowns.remove(IU);
		}			*/
	} 
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	Reset();
	return hr;
}

STDMETHODIMP CEnumObjects::Add(LPUNKNOWN lpUnk)
{
	ASSERT(lpUnk);
	// Query...
	WObjectHolder IOH(lpUnk);
	CComBSTR bstr;
	HRESULT hr = IOH -> GetName(&bstr);

	if (SUCCEEDED(hr))
	{
		WUnknown IU;
		// darf noch nicht in der Liste sein
		if (FAILED ( Find(bstr, IU.ppi()) ) )
		{
			m_listUnknowns.push_back(lpUnk);
			Reset();
			return S_OK;
		}
	}

	return E_FAIL;
}

STDMETHODIMP CEnumObjects::Find(BSTR bstrFind, IUnknown ** pp)
{
	ASSERT(NULL != bstrFind);

	*pp = NULL;

TYPEUnknownList::iterator it = m_listUnknowns.begin();

	while (it != m_listUnknowns.end()) {
	LPUNKNOWN lpUnk = (*it);

		if (lpUnk) {
		WObjectHolder IOH(lpUnk);
		CComBSTR bstr;
		HRESULT hr = IOH -> GetName(&bstr);
			
			if (SUCCEEDED(hr)) {
				if (0 == wcscmp(bstr, bstrFind)) {
				// erfolgreich gefunden
					*pp = lpUnk;
					(*pp) -> AddRef();
					return S_OK; 
				}
			}
		}
		it++;
	}
	return E_FAIL;
}

STDMETHODIMP_(UINT) CEnumObjects::Count() 
{
	TYPEUnknownList::iterator it = m_listUnknowns.begin();
	UINT ui = 0;

	while (it != m_listUnknowns.end())
	{
		ui++;
		it++;
	}
	return ui;
}

// *** IUnknown methods ***
///////////////////////////////////////////////////////////////////////////////////
// Unknown-Methods
STDMETHODIMP CEnumObjects::QueryInterface (REFIID riid, LPVOID *ppv)
{
	*ppv = NULL;                  
	
	if ( IsEqualIID (riid, IID_IUnknown) || IsEqualIID (riid, IID_IEnumUnknownExtended) || IsEqualIID(riid, IID_IEnumUnknown))
		*ppv = this;
	if (NULL != *ppv) {
		LPUNKNOWN(*ppv) -> AddRef();
		return NOERROR;
	}
	
	return E_NOINTERFACE;
}
STDMETHODIMP_(ULONG) CEnumObjects::AddRef (void)
{
	return ++m_cRef;
}

STDMETHODIMP_(ULONG) CEnumObjects::Release (void)
{                               
	if(--m_cRef == 0){
		delete this;
     	return 0;
    }
    	
	return m_cRef;
}

HRESULT CEnumObjects::DelayedDelete(void)
{	
// Es können asynchrone Aufrufe zu mehrmaligem
// Aufruf dieser Funktion führen
// also verhindern
	if (0 < InterlockedIncrement(&m_lDelayDel)) {
		InterlockedDecrement(&m_lDelayDel);
		return S_FALSE;
	}

// Es wird regelmässig überprüft, ob noch zu Löschende
// vorhanden sind
HRESULT hr = NOERROR;
IUnknown *pIU = NULL;

	Reset();
	while (S_OK == Next(1, &pIU, NULL)) {
	CComBSTR bstr;
	bool fCanDel = false;
	
		{
		WObjectHolder IOH (pIU);
	
			RELEASE(pIU);
			IOH -> GetName (&bstr);
			fCanDel = false;
			IOH -> GetDelayedDel(fCanDel);
		}

	// Alle internen Objekte,
	// die RefCount == 1 haben 
	// und schon mal gelöscht werden 
	// sollten hier löschen
		if (fCanDel) 
			hr = Delete (bstr);
	}
	Reset();
	InterlockedDecrement(&m_lDelayDel);
	return hr; 
}

HRESULT CEnumObjects::HandsOffStorage()
{
	Reset();
	try {
	WUnknown IU;

		while (S_OK == Next(1, IU.ppi(), NULL)) 
		{
			THROW_FAILED_HRESULT(WObjectHolder(IU) -> ReleaseObject(false));
		}

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

