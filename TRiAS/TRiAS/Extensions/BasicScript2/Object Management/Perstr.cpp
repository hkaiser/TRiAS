// @doc
// @module PerStr.cpp | 

#include "stdafx.h"
#include "resource.h"

#include <new>

// GUIDS
#include "objmanguid.h"
#include "macrguid.h"
#include "iobjmex.h"
#include <iObjMan.h>

#include "enumex.h"
#include "ObjMn.h"

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100
 
////////////////////////////////////////////////////////////
// Smarts
DefineSmartInterface(Stream);
DefineSmartInterface(ObjectHolder);
DefineSmartInterface(Moniker);
DefineSmartInterface(PersistStream);

/*
 * CObjectManagement::Load
 *
 * Purpose:
 *  Instructs the object to load itself from a previously saved
 *  IStream that was handled by Save in another object lifetime.
 *  The seek pointer in this stream will be exactly the same as
 *  it was when Save was called, and this function must leave
 *  the seek pointer the same as it was on exit from Save, regardless
 *  of success or failure.  This function should not hold on to
 *  pIStream.
*/

STDMETHODIMP CObjectManagement::Load(LPSTREAM pIStream)
{                      
	// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	ASSERT(pIStream);

LPSTR lpBuf = NULL;
HRESULT hr = NOERROR;
	
	USES_CONVERSION;
	try {
	LARGE_INTEGER li;	 

		LISet32 (li, 0);
		THROW_FAILED_HRESULT(pIStream -> Seek (li,  STREAM_SEEK_SET, NULL));
		
	// NICHT wundern: Kann sein, daß Management-Stream noch vorhanden ist, 
	// neu laden (siehe SaveCompleted() bei z.B. SaveAs()) würde sonst fehlschlagen,
	// also S_FALSE == SUCCEEDED zurückliefern
	ULONG ulBytes = 0;	// 1. Anzahl der Items lesen
	ULONG ulCount = 0;

	// #HK000620: VersionsInfo am Anfang
	DWORD dwSignature = 0;

		if (SUCCEEDED(LoadData (pIStream, dwSignature))) {
			if (OBJECTMANAGEMENT_SIGNATURE == dwSignature) {
				THROW_FAILED_HRESULT(LoadData (pIStream, m_dwVersion));		// Version muß jetzt gegeben sein
				if (LASTKNOWN_OBJECTMANAGEMENT_VERSION < m_dwVersion)
				{
					THROW_FAILED_HRESULT(E_FAIL);
				}
				if (FAILED(LoadData (pIStream, ulCount)))
					ulCount = 0;		// alten Fehler in Save tolerieren

			} else {
				m_dwVersion = OBJECTMANAGEMENT_VERSION_100;
				ulCount = dwSignature;		// ist doch die Anzahl der Items (altes Format)
			}
		} else 
			return S_FALSE;

		for (int i = 0; i < ulCount; i++) {
		// 2. Moniker lesen
		WMoniker IMon;
		
			THROW_FAILED_HRESULT(::OleLoadFromStream(pIStream, IID_IMoniker, IMon.ppv()));
		
		// 3. Grösse des Namens lesen
		int iSize = 0;

			hr = pIStream -> Read (&iSize, sizeof(int), &ulBytes);	
			if (FAILED(hr) || ulBytes != (ULONG)sizeof(int) || 0==iSize) 
				_com_issue_error(E_FAIL);  

			lpBuf = new char[iSize+1];
		
		// 4. Name selbst lesen
			hr = pIStream -> Read (lpBuf, iSize, &ulBytes);	
			if (FAILED(hr) || ulBytes != (ULONG)iSize) 
				_com_issue_error(E_FAIL);  

		// als geladen kennzeichnen
		CComBSTR bstr (lpBuf);
		
			THROW_FAILED_HRESULT(SetLoad (bstr));
			THROW_FAILED_HRESULT(SetMoniker(bstr, IMon));		// Moniker setzen
		}

	} catch (_com_error &e) {
		hr = _COM_ERROR(e);
	} catch (bad_alloc) {
		hr = E_OUTOFMEMORY; 
	}
	DELETE_OBJ(lpBuf);
	return hr;
}

HRESULT CObjectManagement::ReLoad(IStorage *pIStg, IStream *pIStream)
{                      
	// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	ASSERT(NULL != pIStream);

HRESULT hr = NOERROR;
LPSTR lpBuf = NULL;
	
	USES_CONVERSION;
	try {
	LARGE_INTEGER li;	 

		LISet32 (li, 0);
		THROW_FAILED_HRESULT(pIStream -> Seek (li,  STREAM_SEEK_SET, NULL));
		
	// NICHT wundern: Kann sein, daß Management-Stream noch vorhanden ist, 
	// neu laden (siehe SaveCompleted() bei z.B.SaveAs()) würde sonst fehlschlagen,
	// also S_FALSE == SUCCEEDED zurückliefern
	ULONG ulBytes = 0;	// 1. Anzahl der Items lesen
	ULONG ulCount = 0;

	// #HK000620: VersionsInfo am Anfang
	DWORD dwSignature = 0;

		if (SUCCEEDED(LoadData (pIStream, dwSignature))) {
			if (OBJECTMANAGEMENT_SIGNATURE == dwSignature) {
				THROW_FAILED_HRESULT(LoadData (pIStream, m_dwVersion));		// Version muß jetzt gegeben sein
				if (LASTKNOWN_OBJECTMANAGEMENT_VERSION < m_dwVersion)
				{
					THROW_FAILED_HRESULT(E_FAIL);
				}
				if (FAILED(LoadData (pIStream, ulCount)))
					ulCount = 0;		// alten Fehler in Save tolerieren

			} else {
				m_dwVersion = OBJECTMANAGEMENT_VERSION_100;
				ulCount = dwSignature;		// ist doch die Anzahl der Items (altes Format)
			}
		} else 
			return S_FALSE;

		for (int i = 0; i < ulCount; i++) {
		// 2. Moniker lesen
		WMoniker IMon;
		
			THROW_FAILED_HRESULT(::OleLoadFromStream(pIStream, IID_IMoniker, IMon.ppv()));
		
		// 3. Grösse des Namens lesen
		int iSize = 0;

			hr = pIStream -> Read (&iSize, sizeof(int), &ulBytes);	
			if (FAILED(hr) || ulBytes != (ULONG)sizeof(int) || 0==iSize) 
				_com_issue_error(E_FAIL);  

			lpBuf = new char[iSize+1];
		
		// 4. Name selbst lesen
			hr = pIStream -> Read (lpBuf, iSize, &ulBytes);	
			if (FAILED(hr) || ulBytes != (ULONG)iSize) 
				_com_issue_error(E_FAIL);  

		// als geladen kennzeichnen
		CComBSTR bstr (lpBuf);
		
			if (SUCCEEDED(GetLoad(bstr))) {
			WObjectHolder OH;
			WUnknown Unk;

				THROW_FAILED_HRESULT(GetObjectHolder (bstr, OH.ppi()));
				THROW_FAILED_HRESULT(OH -> GetObject (Unk.ppi()));
				THROW_FAILED_HRESULT(LoadFileOrStream (Unk, bstr, STGM_CREATE, pIStg, FALSE));

			} else {
				THROW_FAILED_HRESULT(SetLoad (bstr));
				THROW_FAILED_HRESULT(SetMoniker(bstr, IMon));		// Moniker setzen
			}
		}

	} catch (_com_error &e) {
		hr = _COM_ERROR(e);
	} catch (bad_alloc) {
		hr = E_OUTOFMEMORY; 
	}
	DELETE_OBJ(lpBuf);
	return hr;
}

/*
 * CObjectManagement::Save
 *
 * Purpose:
 *  Saves the data for this object to an IStream.  Be sure not
 *  to change the position of the seek pointer on entry to this
 *  function: the caller will assume that you write from the
 *  current offset.  Leave the stream's seek pointer at the end
 *  of the data written on exit.
 */

STDMETHODIMP CObjectManagement::Save(LPSTREAM pIStream, BOOL fClearDirty )
{                     
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	ASSERT(pIStream);
	ASSERT(m_pEnumObjects);

HRESULT hr = NOERROR;

	USES_CONVERSION;
	try {
	// Erstmal truncating
	LARGE_INTEGER li;
		
		LISet32(li, 0);
		THROW_FAILED_HRESULT(pIStream -> SetSize((ULARGE_INTEGER &)li));
		THROW_FAILED_HRESULT(pIStream -> Seek (li, SEEK_SET, NULL));

	// #HK000620: Versions/Signaturinfo werden jetzt am Ende geschrieben
		THROW_FAILED_HRESULT(SaveData (pIStream, OBJECTMANAGEMENT_SIGNATURE));
		THROW_FAILED_HRESULT(SaveData (pIStream, m_dwVersion));		// Version beibehalten

	// ObjektCount ohne Neue und Temporaere geben lassen
	ULONG ulCount = 0;
	
		THROW_FAILED_HRESULT(ObjectCountToWrite(&ulCount));

	// 1. Anzahl der Items schreiben
		THROW_FAILED_HRESULT(SaveData (pIStream, ulCount));		// Count schreiben
		
		if (0 != ulCount) {
		ULONG cbWritten;
		WUnknown IUnkObjectHolder;
	
			while (S_OK == m_pEnumObjects -> Next(1, IUnkObjectHolder.ppi(), NULL)) {
			// Neue und temporäre nicht wegschreiben
			WObjectHolder IOH (IUnkObjectHolder);
			bool fTemp = false, fNew = false; 

				THROW_FAILED_HRESULT(IOH -> GetNew(&fNew));
				THROW_FAILED_HRESULT(IOH -> GetTemporaer(fTemp));

			// WEITER mit Naechstem
				if (fNew || fTemp) continue;

			// Monikerart des Objektes
			WMoniker IMon;

				THROW_FAILED_HRESULT(IOH -> GetMoniker(IMon.ppi()));
			
			// Name des Objektes
			CComBSTR bstr;

				THROW_FAILED_HRESULT(IOH -> GetName(&bstr));

			// 2. Moniker streamen
			WPersistStream IPS(IMon);
			
				THROW_FAILED_HRESULT(OleSaveToStream(IPS, pIStream));
				
			// 3. Grösse des Namens
			LPCSTR lpcstr = OLE2A(bstr);
			int iSize = strlen(lpcstr)+1; // wegen der '\0'
			
				THROW_FAILED_HRESULT(pIStream -> Write (&iSize, sizeof(int), &cbWritten));
				if ((int)cbWritten != sizeof(int)) _com_issue_error(E_FAIL);
				
			// 4. Name an sich
				THROW_FAILED_HRESULT(pIStream -> Write (lpcstr, iSize, &cbWritten));
				if ((int)cbWritten != iSize) _com_issue_error(E_FAIL);
			}
		}
		else
			hr = S_FALSE;
		
		if (fClearDirty)
			m_fIsDirty = false;
	}
	catch(_com_error& hres)
	{	
		hr = _COM_ERROR(hres);
	}

// Enumerator zurücksetzen
	m_pEnumObjects -> Reset();
	return hr;
}

HRESULT CObjectManagement::ObjectCountToWrite(ULONG *pul)
{
	ASSERT(pul);
	if (NULL == pul) return E_POINTER;
	*pul = 0;

	HRESULT hr = NOERROR; 		
	ULONG ul = 0;
	try
	{
		m_pEnumObjects -> Reset();
		
		WUnknown IU;
		while (S_OK == m_pEnumObjects -> Next(1, IU.ppi(), NULL))
		{
			WObjectHolder IOH = IU;
			bool fNew = false;
			bool fTemp = false;
			// Temporaere und Neue nicht wegschreiben
			hr = IOH -> GetNew(&fNew);
			if (FAILED(hr)) _com_issue_error(hr);
			hr = IOH -> GetTemporaer(fTemp);
			if (FAILED(hr)) _com_issue_error(hr);

			if (fNew || fTemp) continue;

			ul++;			
		}
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	m_pEnumObjects -> Reset();
	*pul = ul;			

	return hr;
}

/*
 * CObjectManagement::GetSizeMax
 *
 * Purpose:
 *  Returns the size of the data we would write if Save was
 *  called right now.
 *
 * Parameters:
 *  pcbSize         ULARGE_INTEGER FAR * in which to save the size
 *                  of the stream an immediate call to Save would
 *                  write.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CObjectManagement::GetSizeMax(ULARGE_INTEGER FAR
    * pcbSize)
{
	// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

return E_NOTIMPL;
}


