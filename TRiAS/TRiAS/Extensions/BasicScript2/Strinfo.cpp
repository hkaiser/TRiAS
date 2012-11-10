
#include "bscriptp.hxx"
#include "bscript.h"

#include <ospace/source.h>
#include <ospace/olestrea.h>

#include "macrguid.h"
#include "iscrprop.h"

extern CComModule _Module;

#include "strinfo.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAXTEXT	0x0000FFEFL		// maximale ScriptGröße

#if defined(WIN32)
#define __huge
#endif // WIN32


///////////////////////////////////////////////////////////////////////////////
// algemeine globale Funktionen

//////////////////////////////////////////////////////////////////////////////
//	Methods: CStreamInfoScript


CStreamInfo::CStreamInfo()
{
	m_fIsDirty = false;
	m_uiManID = 0;
}


CStreamInfo::~CStreamInfo()
{
	TRACE("StreamInfo Released\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////
// *** IPersistStream / IPersistStreamInit ***


STDMETHODIMP_(UINT) CStreamInfo::GetManID() 
{
	return m_uiManID;
}
STDMETHODIMP_(void) CStreamInfo::SetManID(UINT ui) 
{
	m_uiManID = ui;
}

STDMETHODIMP CStreamInfo::GetClassID(LPCLSID pClsID)
{
	*pClsID = CLSID_StreamInfo;
	
return NOERROR;
}


STDMETHODIMP CStreamInfo::IsDirty(void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}


STDMETHODIMP CStreamInfo::Load(LPSTREAM pIStream)
{
	ASSERT(pIStream);

	int iCount = 0;
	ULONG cbRead;

	// Anzahl aller Entries lesen
	HRESULT hr = pIStream -> Read (&iCount, sizeof(int), &cbRead);
	// NICHT wundern: Stream kann z.B. in SaveAs(), obwohl er leer ist, noch vorhanden sein
	// Load dieses Streams würde sonst fehlschlagen
	if (cbRead != (ULONG)sizeof(int)) return S_FALSE;
	if (FAILED(hr)) return hr; 

	if (0 != iCount)
	{
		int i;

		for (i=0; i<iCount;i++)
		{		
			DWORD dw = 0;

			// Streaminfo lesen
			hr = pIStream -> Read (&dw, sizeof(DWORD), &cbRead);	
			if ((int)cbRead != sizeof(DWORD)) return E_FAIL;
			if (FAILED(hr)) return hr;

			int iSize = 0;

			// Size von String lesen
			hr = pIStream -> Read (&iSize, sizeof(int), &cbRead);	
			if ((int)cbRead != sizeof(int)) return E_FAIL;
			if (FAILED(hr)) return hr;

			char str[MAXSTRLENGTH];

			// String von Size lesen
			hr = pIStream -> Read(str, iSize, &cbRead);	
			if ((int)cbRead != iSize) return E_FAIL;
			if (FAILED(hr)) return hr;

			str[iSize] = '\0';

			os_string oss(str);

			// Map füllen
			map_StreamInfo.insert(oss, dw);
		}
	}

return NOERROR;
}

STDMETHODIMP CStreamInfo::Save(LPSTREAM pIStream, BOOL fClearDirty)
{
	ASSERT(pIStream);

	// Erstmal truncating
	ULARGE_INTEGER libNewSize;
	ULISet32(libNewSize, 0);
	HRESULT hr = pIStream -> SetSize(libNewSize);
	if (FAILED(hr)) return hr;

	int iCount = StreamMapCount();
	ULONG cbWritten;
	hr = pIStream -> Write (&iCount, sizeof(int), &cbWritten);	// Count schreiben
	if ((int)cbWritten != sizeof(int)) return E_FAIL;
	if (FAILED(hr)) return hr;

	if (0 != iCount)
	{
		StreamMap::iterator it = map_StreamInfo.begin();

	// mehrere Entries für einen Script 
		while(it != map_StreamInfo.end()) 
		{		
			DWORD dw = (*it).second;
			os_string oss = (*it).first;

			hr = pIStream -> Write (&dw, sizeof(DWORD), &cbWritten);	// Count schreiben
			if ((int)cbWritten != sizeof(DWORD)) return E_FAIL;
			if (FAILED(hr)) return hr;

			LPCSTR lpcstr = oss.c_str();
			int iSize = strlen(lpcstr)+1;

			hr = pIStream -> Write (&iSize, sizeof(int), &cbWritten);	// Count schreiben
			if ((int)cbWritten != sizeof(int)) return E_FAIL;
			if (FAILED(hr)) return hr;

			hr = pIStream -> Write (lpcstr, iSize, &cbWritten);	// Count schreiben
			if ((int)cbWritten != iSize) return E_FAIL;
			if (FAILED(hr)) return hr;

			it++;
		}
	}
	// Speichern erfolgreich
	if (fClearDirty)
		m_fIsDirty = false;

	return NOERROR;
}


STDMETHODIMP CStreamInfo::GetSizeMax (ULARGE_INTEGER FAR *)
{
return E_NOTIMPL;
}


STDMETHODIMP CStreamInfo::Rename(BSTR bstr, BSTR bstrNew)
{			// Streaminfo umbenennen
	DWORD dw = 0;
	HRESULT hr = Get(bstr, &dw);	
	if (SUCCEEDED(hr))
	{
		hr = Set(bstr, 0);
		if (SUCCEEDED(hr))
		{
			hr = Set(bstrNew, dw);
		}
	}

	return hr;
}

STDMETHODIMP_(UINT) CStreamInfo::Count()
{
	return StreamMapCount();
}

STDMETHODIMP CStreamInfo::Get(BSTR bstr, DWORD *pdw)
{
	USES_CONVERSION;
	os_string osstr(OLE2A(bstr));
	StreamMap::iterator it = map_StreamInfo.find(osstr); 
	if (it == map_StreamInfo.end()) return E_FAIL;

	*pdw = (*it).second;

return NOERROR;
}


STDMETHODIMP CStreamInfo::Set(BSTR bstr, DWORD dw)
{
	USES_CONVERSION;
	os_string osstr(OLE2A(bstr));

	// 0 heisst löschen
	if (0 == dw) 
	{
		StreamMap::iterator it = map_StreamInfo.find(osstr); 
		if (it == map_StreamInfo.end()) return S_FALSE;
		// Nur löschen und Dirty setzen, wenn auch eines vorhanden ist.
		map_StreamInfo.erase(osstr);
	} 
	else 
	{// wenn schon in der Liste, nochmaliges Einfügen nicht möglich
		map_StreamInfo.erase(osstr);
		map_StreamInfo.insert(osstr, dw); 
	}
	m_fIsDirty = true;

return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// *** Hilfsfunktionen

int CStreamInfo::StreamMapCount()
{
	int i = 0;
	StreamMap::iterator it = map_StreamInfo.begin();

	while(it != map_StreamInfo.end()) {
		it++; i++;
	}

return i;
}

