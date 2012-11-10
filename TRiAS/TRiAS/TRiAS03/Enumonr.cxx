// Implementation des IEnumObjectsByNumber - Interfaces -----------------------
// File: ENUMONR.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <eonrguid.h>
#include <ifndlong.h>
#include <itriasap.h>		// IGetTRiASApplication
#include <oleguid.h>

#include "enumonr.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumObjectsByNumber);		// WEnumObjectsByNumber
DefineSmartEnumerator(LONG);					// WEnumLONG
DefineSmartInterface(GetTRiASApplication);
DefineSmartInterface(Dispatch);
DefineSmartInterface2(DApplication, IID_DApplication);
DefineSmartInterface2(DDocument, IID_DDocument);
DefineSmartInterface2(DGeoObjects, IID_DGeoObjects);

///////////////////////////////////////////////////////////////////////////////
// Funktionen der Basisklasse 
CEnumObjectNumbers :: CEnumObjectNumbers (void)		// Konstruktor
{
	m_fIsInitialized = false;
	SEnumLONG::Reset();
}

CComObject<CEnumObjectNumbers> *CEnumObjectNumbers :: CreateInstance (void)
{
	try {
	CComObject<CEnumObjectNumbers> *pEnum = new CComObject<CEnumObjectNumbers>();
		
		if (pEnum == NULL || !pEnum -> FInit()) {
			DELETE_OBJ(pEnum);
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
	} catch (...) {
		TX_ASSERT(false);
		return false;
	}

return true;
}

// IPersistStreamInterface ////////////////////////////////////////////////////

// *** IPersist methods *** ---------------------------------------------------
STDMETHODIMP CEnumObjectNumbers::GetClassID (CLSID *pClsID)
{
	*pClsID = CLSID_EnumObjectsByNumber;
	return NOERROR;
}

// *** IPersistStream methods *** ---------------------------------------------
STDMETHODIMP CEnumObjectNumbers::IsDirty (void)
{
	return GetDirty() ? S_OK : S_FALSE;
}


STDMETHODIMP CEnumObjectNumbers::Load (IStream *pIStream)
{
	if (m_fIsInitialized) 
		return E_UNEXPECTED;		// already initialized with InitNew

	if (NULL == pIStream) return E_POINTER;

// Enum füllen
ULONG ulCnt = 0;
HRESULT hr = E_FAIL;

	try {
		hr = pIStream -> Read (&ulCnt, sizeof(ULONG), NULL);
		if (FAILED(hr)) _com_issue_error(hr);

	LONG lItem = 0;

		for (ULONG ui = 0; ui < ulCnt; ui++) {
			hr = pIStream -> Read (&lItem, sizeof(LONG), NULL);
			if (FAILED(hr)) _com_issue_error(hr);

			if (!AddObject (lItem))
				_com_issue_error(E_OUTOFMEMORY);
		}
		Reset();
		m_fIsInitialized = true;
		setdirty(false);

	} catch (_com_error& hr_result) {
		setdirty(false);
		return _COM_ERROR(hr_result);
	}

return NOERROR;
}


STDMETHODIMP CEnumObjectNumbers::Save (IStream *pIStream, BOOL fClearDirty)
{
	if (NULL == pIStream) return E_POINTER;

HRESULT hr = E_FAIL;

	try {
	// Daten wegschreiben
	ULONG ulSize = Count();
	LONG lItem = 0L;

		hr = pIStream -> Write (&ulSize, sizeof(ulSize), NULL);
		if (FAILED(hr)) _com_issue_error(hr);

		for (CObjectNumbers::const_iterator it = Objs().begin(); 
		     it != Objs().end(); it++) 
		{
			lItem = *it;
			hr = pIStream -> Write (&lItem, sizeof(LONG), NULL);
			if (FAILED(hr)) _com_issue_error(hr);
		}

		if (fClearDirty) setdirty(false);

	} catch (_com_error& hr_result) {
		return _COM_ERROR(hr_result);
	}

return NOERROR;
}


STDMETHODIMP CEnumObjectNumbers::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

// Die StreamGröße wird bestimmt durch die Anzahl der Objekte im Enumerator
// plus die Größe des Zählers.
	LISet32 (*pcbSize, Count() * sizeof(LONG) + sizeof(ULONG));

return NOERROR;
}

STDMETHODIMP CEnumObjectNumbers::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_fIsInitialized = true;

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// *** IFindLONG specific members
STDMETHODIMP CEnumObjectNumbers::HasLONG (LONG lFind)
{
	return (m_data.end() == m_data.find (lFind)) ? S_FALSE : S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// *** IEnumObjectsByNumber specific members
STDMETHODIMP CEnumObjectNumbers::Next (ULONG celt, LONG *rgelt, ULONG *pceltFetched)
{
	return SEnumLONG::Next (celt, rgelt, pceltFetched);
}

STDMETHODIMP CEnumObjectNumbers::Skip (ULONG dwSkip)
{
	return SEnumLONG::Skip (dwSkip);
}

STDMETHODIMP CEnumObjectNumbers::Reset (void)
{
	return SEnumLONG::Reset();
}

STDMETHODIMP CEnumObjectNumbers::Clone (IEnumObjectsByNumber **ppenum)
{
	if (NULL == ppenum) return E_POINTER;
	*ppenum = NULL;

	try {
	WEnumLONG EnumL;
	
		THROW_FAILED_HRESULT(SEnumLONG::Clone (EnumL.ppi()));

	WEnumObjectsByNumber Enum (EnumL);
			
		*ppenum = Enum.detach();

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}		

	return S_OK;
}

STDMETHODIMP CEnumObjectNumbers::GetCount (ULONG *pulCount)
{
	if (NULL == pulCount) return E_POINTER;

	*pulCount = Count();
	return S_OK;
}

STDMETHODIMP CEnumObjectNumbers::AddItem (LONG item)
{
	return SEnumLONG::AddItem(item);
}

STDMETHODIMP CEnumObjectNumbers::Clear (void)
{
	return SEnumLONG::Clear();
}

///////////////////////////////////////////////////////////////////////////////
// Liefern einer GeoObjects-Collection für diesen Enumerator
// *** IQueryGeoObjects specific functions ***
STDMETHODIMP CEnumObjectNumbers::GetGeoObjects (_DGeoObjects **ppIGeoObjs)
{
	if (NULL == ppIGeoObjs) return E_POINTER;

	try {
	// Erweiterung laden und binden 
	WGetTRiASApplication GetApp (CLSID_OleAutoExtension);	//throws hr
	WDApplication App;

		THROW_FAILED_HRESULT(GetApp->GetApplication (IID_DApplication, App.ppv()));

	WDDocument Doc;
	WDGeoObjects Objs;	// throws hr

		THROW_FAILED_HRESULT(App -> get_ActiveDocument (Doc.ppi()));
		THROW_FAILED_HRESULT(Doc -> CreateGeoObjectsCollection(Objs.ppi()));

	// ObjektNummern umkopieren
		{
		CLockEnum<CComObjectThreadModel> SyncMe(m_sync);
		CComVariant Obj;
		WDispatch Disp;

			V_VT(&Obj) = VT_I4;
			for (SEnumLONG::iterator it = m_data.begin();
				 it != m_data.end(); ++it)
			{
				V_I4(&Obj) = *it;
				THROW_FAILED_HRESULT(Objs -> Add(Obj, Disp.ppi()));
			}

		// alles ok, und raus
			*ppIGeoObjs = Objs.detach();
		}	// CLockEnum goes out of scope

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return S_OK;
}
