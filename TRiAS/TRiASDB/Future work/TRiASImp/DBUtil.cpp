// @doc
// @module DBUTIL.CPP | Allgemeine Makrodefinitionen et.al.

#include "StdAfx.h"

#include "Wrapper.h"	// SmartIF's

///////////////////////////////////////////////////////////////////////////////
// Öffnen/Erzeugen eines SubStorages
HRESULT GetSubStorage (
	IStorage *pIRootStg, LPCOLESTR poleName, REFCLSID rClsId,
	IStorage **ppIStg, bool fCreate)
{
	if (NULL == ppIStg) return E_POINTER;
	if (NULL == pIRootStg) return E_INVALIDARG;

WStorage IStg;
HRESULT hr = E_FAIL;
bool fSetDirty = false;

	{
	bool fRO = false;

		hr = pIRootStg -> OpenStorage (poleName, NULL, 
							STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
							NULL, 0L, IStg.ppi());
		if (FAILED(hr)) {
			if (STG_E_FILENOTFOUND == GetScode(hr) && fCreate) {
			// existiert nicht, evtl. neu erzeugen
				hr = pIRootStg -> CreateStorage (poleName, 
									STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED|STGM_CREATE, 
									0L, 0L, IStg.ppi());
				if (SUCCEEDED(hr))
					hr = ::WriteClassStg (IStg, rClsId);
				
				fSetDirty = true;

			} else if (STG_E_ACCESSDENIED == GetScode(hr)) {
			// mit Schreibschutz versuchen
				hr = pIRootStg -> OpenStorage (poleName, NULL, 
								STGM_READ|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
								NULL, 0L, IStg.ppi());
				fRO = true;
			} else
				return hr;
		} 

		if (SUCCEEDED(hr)) {
		CLSID clsId;

			hr = ::ReadClassStg (IStg, &clsId);
			if (FAILED(hr)) return hr;

			if (!IsEqualCLSID(clsId, rClsId) && !IsEqualCLSID(clsId, CLSID_NULL))
			{
				return E_FAIL;
			}

			if (IsEqualCLSID(clsId, CLSID_NULL) && !fRO) {
				hr = ::WriteClassStg (IStg, rClsId);
				fSetDirty = true;
			}
		}
	}
	if (FAILED(hr)) return hr;

	*ppIStg = IStg.detach();
	return fSetDirty ? S_FALSE : S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Öffnen/Erzeugen des SubStreames
HRESULT GetSubStream (
	IStorage *pIRootStg, LPCOLESTR poleName, IStream **ppIStm, bool fCreate)
{
	if (NULL == ppIStm) return E_POINTER;
	if (NULL == pIRootStg) return E_INVALIDARG;

WStream IStm;
HRESULT hr = S_OK;

	if (fCreate) {
		hr = pIRootStg -> CreateStream (poleName, 
						STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE, 
						0L, 0L, IStm.ppi());
	} else {
		hr = pIRootStg -> OpenStream (poleName, NULL, 
						STGM_READ|STGM_SHARE_EXCLUSIVE, 0L, IStm.ppi());
	}
	if (FAILED(hr)) return hr;

	*ppIStm = IStm.detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// FormatMessage aus MessageTyble in ein CString
void __cdecl FormatMessage(CString &rStr, UINT uiError, ...)
{
// format message into temporary buffer lpszTemp
DWORD dwFlags = FORMAT_MESSAGE_FROM_HMODULE|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER;
LPTSTR lpszTemp = NULL;
va_list argList;

	va_start(argList, uiError);
	if (::FormatMessage (dwFlags, _Module.GetResourceInstance(), uiError, 0, (LPTSTR)&lpszTemp, 0, &argList) == 0 ||
		lpszTemp == NULL)
	{
#if defined(_DEBUG)
		dwFlags = FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_IGNORE_INSERTS;

	DWORD dwError = GetLastError();

		::FormatMessage (dwFlags, NULL, dwError, 0, (LPTSTR)&lpszTemp, 0, NULL);
		rStr = lpszTemp;
#else
		rStr = g_cbNoMemory;
#endif // _DEBUG
	}
	else	// assign lpszTemp into the resulting string and free lpszTemp
		rStr = lpszTemp;

	if (lpszTemp) LocalFree(lpszTemp);
	va_end(argList);
}

///////////////////////////////////////////////////////////////////////////////
// Spezielle Messagebox mit Formatiermöglichkeiten
int __cdecl VMessageBox (UINT uiCaption, UINT uiType, UINT uiText, ...)
{
CString strCap, strText;

	VERIFY(strCap.LoadString (uiCaption));
	VERIFY(strText.LoadString (uiText));

CWnd Wnd;
CString strOut;
LPTSTR pcOut = NULL;

	ATLTRY(pcOut = strOut.GetBufferSetLength(_MAX_PATH*4));
	if (NULL != pcOut) {
	va_list params;

		va_start (params, uiText);
		wvsprintf (pcOut, strText, params);
		va_end (params);

		return Wnd.MessageBox (pcOut, strCap, uiType);
	}
	return Wnd.MessageBox (strText, strCap, uiType);
}

int __cdecl VMessageBox (LPCSTR pcCaption, UINT uiType, UINT uiText, ...)
{
CString strText;

	VERIFY(strText.LoadString (uiText));

CWnd Wnd;
CString strOut;
LPTSTR pcOut = NULL;

	ATLTRY(pcOut = strOut.GetBufferSetLength(_MAX_PATH*4));
	if (NULL != pcOut) {
	va_list params;

		va_start (params, uiText);
		wvsprintf (pcOut, strText, params);
		va_end (params);

		return Wnd.MessageBox (pcOut, pcCaption, uiType);
	}
	return Wnd.MessageBox (strText, pcCaption, uiType);
}

///////////////////////////////////////////////////////////////////////////////
// Formatierfunktionen
os_string __cdecl FakeTRiASName (UINT resID, ...)
{
CString strText;

	VERIFY(strText.LoadString (resID));

	try {
	CString strOut;
	LPTSTR pcOut = strOut.GetBufferSetLength(_MAX_PATH*4);
	va_list params;

		va_start (params, resID);
		wvsprintf (pcOut, strText, params);
		va_end (params);
		return os_string(pcOut);
	
	} catch (...) {
	// irgendein Fehler
		;
	}
	return os_string((LPCSTR)strText);
}

os_string __cdecl FakeTRiASName (LPCSTR pcTempl, ...)
{
	try {
	CString strOut;
	LPTSTR pcOut = strOut.GetBufferSetLength(_MAX_PATH*4);
	va_list params;

		va_start (params, pcTempl);
		wvsprintf (pcOut, pcTempl, params);
		va_end (params);
		return os_string(pcOut);
	
	} catch (...) {		// irgendein Fehler
		;
	}
	return os_string(pcTempl);
}

