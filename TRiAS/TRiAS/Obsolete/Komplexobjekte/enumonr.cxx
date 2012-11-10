// Implementation des IEnumObjectsByNumber - Interfaces -----------------------
// File: ENUMONR.CXX

#include "featurep.hxx"

#include <eonrguid.h>
#include "enumonr.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Funktionen der Basisklasse -------------------------------------------------
#pragma warning (disable: 4355)

CEnumObjectNumbers :: CEnumObjectNumbers (void)		// Konstruktor
				    : m_Persist (this, this)
{
	m_fIsDirty = false;
	Reset();
}

#pragma warning (default: 4355)

CEnumObjectNumbers *CEnumObjectNumbers :: CreateInstance (void)
{
	try {
	CEnumObjectNumbers *pEnum = new CEnumObjectNumbers();
		
		if (pEnum == NULL || !pEnum -> FInit()) {
			DELETE(pEnum);
			return NULL;
		}
		pEnum -> AddRef();
		return pEnum;
	} catch (...) {		// alle Fehler abfangen
		return NULL;
	}
}

// Objekt zu Array hinzufügen -------------------------------------------------
bool CEnumObjectNumbers :: AddObject (LONG lONr)
{
	try {
		AddItem (lONr);
		m_fIsDirty = true;
	} catch (...) {
		TX_ASSERT(false);
		return false;
	}

return true;
}

// IPersistStreamInterface ////////////////////////////////////////////////////
CEnumObjectNumbers:: 
CPersistEnumLONG::CPersistEnumLONG (IUnknown *pIUnk, CEnumObjectNumbers *pEnum)
{
#if defined(_DEBUG)
	m_dwRefCnt = 0;
#endif // _DEBUG

	m_pIUnk = pIUnk;	// ohne AddRef !
	m_pEnum = pEnum;
}

CEnumObjectNumbers:: 
CPersistEnumLONG::~CPersistEnumLONG (void)
{
	// nothing to do
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP_(ULONG) CEnumObjectNumbers:: 
CPersistEnumLONG::AddRef (void)
{
#if defined(_DEBUG)
	++m_dwRefCnt;
#endif // _DEBUG
	return m_pIUnk -> AddRef();
}


STDMETHODIMP_(ULONG) CEnumObjectNumbers:: 
CPersistEnumLONG::Release (void)
{
#if defined(_DEBUG)
	TX_ASSERT(m_dwRefCnt > 0);
	--m_dwRefCnt;
#endif // _DEBUG
	return m_pIUnk -> Release();
}

STDMETHODIMP CEnumObjectNumbers::
CPersistEnumLONG::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	return m_pIUnk -> QueryInterface (riid, ppvObj);
}

// *** IPersist methods *** ---------------------------------------------------
STDMETHODIMP CEnumObjectNumbers:: 
CPersistEnumLONG::GetClassID (CLSID *pClsID)
{
	*pClsID = CLSID_EnumObjectsByNumber;
	return NOERROR;
}

// *** IPersistStream methods *** ---------------------------------------------
STDMETHODIMP CEnumObjectNumbers:: 
CPersistEnumLONG::IsDirty (void)
{
	return ResultFromScode (m_pEnum -> GetDirty() ? S_OK : S_FALSE);
}


STDMETHODIMP CEnumObjectNumbers:: 
CPersistEnumLONG::Load (IStream *pIStream)
{
	if (NULL == pIStream)
		return ResultFromScode (E_POINTER);

// Enum füllen
ULONG ulCnt = 0;
HRESULT hr = ResultFromScode (E_FAIL);

	try {
		hr = pIStream -> Read (&ulCnt, sizeof(ULONG), NULL);
		if (FAILED(hr)) throw hr;

	LONG lItem = 0;

		for (ULONG ui = 0; ui < ulCnt; ui++) {
			hr = pIStream -> Read (&lItem, sizeof(LONG), NULL);
			if (FAILED(hr)) throw hr;

			if (!m_pEnum -> AddObject (lItem))
				throw (hr = ResultFromScode (E_OUTOFMEMORY));
		}
		m_pEnum -> SetDirty (false);

	} catch (HRESULT hr_result) {
		m_pEnum -> SetDirty (false);
		return hr_result;
	}

return NOERROR;
}


STDMETHODIMP CEnumObjectNumbers:: 
CPersistEnumLONG::Save (IStream *pIStream, BOOL fClearDirty)
{
	if (NULL == pIStream)
		return ResultFromScode (E_POINTER);

HRESULT hr = ResultFromScode (E_FAIL);

	try {
	// Daten wegschreiben
	ULONG ulSize = m_pEnum -> Count();
	LONG lItem = 0L;

		hr = pIStream -> Write (&ulSize, sizeof(ulSize), NULL);
		if (FAILED(hr)) throw hr;

		for (CObjectNumbers::const_iterator it = m_pEnum -> Objs().begin(); 
		     it != m_pEnum -> Objs().end(); it++) 
		{
			lItem = *it;
			hr = pIStream -> Write (&lItem, sizeof(LONG), NULL);
			if (FAILED(hr)) throw hr;
		}

		if (fClearDirty) m_pEnum -> SetDirty (false);

	} catch (HRESULT hr_result) {
		return hr_result;
	}

return NOERROR;
}


STDMETHODIMP CEnumObjectNumbers:: 
CPersistEnumLONG::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return ResultFromScode (E_POINTER);

// Die StreamGröße wird bestimmt durch die Anzahl der Objekte im Enumerator
// plus die Größe des Zählers.
	LISet32 (*pcbSize, m_pEnum->Count() * sizeof(LONG) + sizeof(ULONG));

return NOERROR;
}

