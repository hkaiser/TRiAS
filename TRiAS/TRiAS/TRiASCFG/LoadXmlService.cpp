// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.12.2000 22:22:05 
//
// @doc
// @module LoadXmlService.cpp | Definition of the <c CLoadXmlService> class

#include "stdafx.h"

#include <shlwapi.h>
#include <shfolder.h>

#include <ospace/file/path.h>
#include <Com/MemoryHelper.h>

#include "TRiASCFG.h"
#include "LoadXmlService.h"

#include "Strings.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLoadXmlService

STDMETHODIMP CLoadXmlService::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ILoadXmlService
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// laden einer XML-Datei
namespace {
	CString ConvertToURL (CString str)
	{
	CString strRes;

		for (int i = 0; i < str.GetLength(); ++i) {
			if (iscntrl(str[i]) || str[i] == '\\') {
			CString strT;

				strT.Format ("%%%02x", str[i]);
				strRes += strT;
			}
			else
				strRes += str[i];
		}
		return strRes;
	}
}

STDMETHODIMP CLoadXmlService::LoadXmlFromResource (BSTR bstrRsc, IDispatch **ppIXmlDoc)
{
	using namespace WTL;

	CHECKOUTPOINTER(ppIXmlDoc);
	USES_CONVERSION;

	COM_TRY {
	__Interface<IXMLDOMDocument> Doc;
	HRESULT hr = Doc.CreateInstance (CLSID_DOMDocument);

		if (FAILED(hr)) 
			return hr;		// kein XMLDOM-Parser installiert

	// zuerst versuchen, diese Datei aus dem zentralen XML-Verzeichnis zu laden
	CComBSTR bstrXMLPath;

		THROW_FAILED_HRESULT(EnsureXmlPath (&bstrXMLPath));
		if (SUCCEEDED(LoadXml (bstrXMLPath, bstrRsc, Doc))) 
			*ppIXmlDoc = Doc.detach();
		else {
		// Resource-url zusammenbauen (ggf. aus lokaler Resource laden)
		CComBSTR bstrResource (g_cbRes);
		char cbBuffer[_MAX_PATH];
			
			if (0 == m_bstrModule.Length()) {
				GetModuleFileName(_Module.GetResourceInstance(), cbBuffer, sizeof(cbBuffer));
				bstrResource += cbBuffer;
			} else
				bstrResource += m_bstrModule;

			THROW_FAILED_HRESULT(LoadXml (bstrResource, bstrRsc, Doc));
			*ppIXmlDoc = Doc.detach();
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Finden und ggf. laden einer HTML-Resource
namespace {
	HRESULT FindHtmlResource(LPCSTR pcBaseName, HGLOBAL *phGbl)
	{
		_ASSERTE(NULL != phGbl);
		*phGbl = NULL;

	HRSRC hRsc = ::FindResource(_Module.GetResourceInstance(), pcBaseName, RT_HTML);

		if (NULL == hRsc)
			return E_INVALIDARG;	// resource not found

	HGLOBAL hGlb = ::LoadResource(_Module.GetModuleInstance(), hRsc);

		if (NULL == hGlb) 
			return E_INVALIDARG;

	LPVOID pData = ::LockResource(hGlb);

		if (NULL == pData) 
			return E_INVALIDARG;

		COM_TRY {
		DWORD dwSize = ::SizeofResource(_Module.GetModuleInstance(), hRsc);
		CGlobalMem hMem (dwSize);	// throws E_OUTOFMEMORY

			{
			CGlobalMem::Lock<BYTE> lock(hMem);

				memcpy(lock, pData, dwSize);
			}
			*phGbl = hMem.Detach();

		} COM_CATCH;
		return S_OK;
	}
}

STDMETHODIMP CLoadXmlService::LoadXmlFromFile (BSTR bstrFile, IDispatch **ppIXmlDoc)
{
	using namespace WTL;

	CHECKOUTPOINTER(ppIXmlDoc);
	USES_CONVERSION;

// GeoComponentSequence.dtd sicherstellen
os_path pathXML (OLE2A(bstrFile));
bool fCreatedDtd = false;

	pathXML.base("GeoComponentSequence");
	pathXML.extension("dtd");

	if ((DWORD)(-1) == GetFileAttributes(pathXML)) {
	CGlobalMem hMem;
	HRESULT hr = FindHtmlResource("GeoComponentSequence.dtd", &hMem);

		if (SUCCEEDED(hr)) {
		CGlobalMem::Lock<BYTE> lock(hMem);
		FILE *fpDtd = fopen(pathXML, "wb");

			if (NULL != fpDtd) {
				ATLTRY(fwrite(lock, lock.GetSize(), 1, fpDtd));
				fclose(fpDtd);
				fCreatedDtd = true;
			}
		}
	}

// jetzt laden
__Interface<IXMLDOMDocument> Doc;
HRESULT hr = Doc.CreateInstance (CLSID_DOMDocument);

	if (FAILED(hr)) 
		return hr;		// kein XMLDOM-Parser installiert

// zuerst versuchen, Datei direkt zu laden
	if (FAILED(LoadXml(bstrFile, NULL, Doc)))
		return hr;
	
// ggf. *.dtd wieder weglöschen
	if (fCreatedDtd) 
		::DeleteFile(pathXML);

	*ppIXmlDoc = Doc.detach();
	return S_OK;
}

HRESULT CLoadXmlService::LoadXml (BSTR bstrPath, BSTR bstrRsc, IXMLDOMDocument *pIXmlDoc)
{
	USES_CONVERSION;

VARIANT_BOOL fSuccess = VARIANT_FALSE;

	COM_TRY {
	// url zusammenbauen
	CString strResource (OLE2A(bstrPath));

		if (NULL != bstrRsc && SysStringLen(bstrRsc) > 0) {
			strResource += "/";
			strResource += OLE2A(bstrRsc);
		}

	// XML-File laden
		THROW_FAILED_HRESULT(pIXmlDoc -> put_validateOnParse (VARIANT_TRUE));
		THROW_FAILED_HRESULT(pIXmlDoc -> load (CComVariant(ConvertToURL(strResource)), &fSuccess));

#if defined(_DEBUG)
	CComBSTR bstrReason;
	CComBSTR bstrUrl;
	CComBSTR bstrSrc;
	long lError = S_OK;
	long lLine = 0;
	long lLinePos = 0;

		if (!fSuccess) {
		__Interface<IXMLDOMParseError> ParseError;

			THROW_FAILED_HRESULT(pIXmlDoc->get_parseError(ParseError.ppi()));
			THROW_FAILED_HRESULT(ParseError->get_errorCode(&lError));
			THROW_FAILED_HRESULT(ParseError->get_reason(&bstrReason));
			THROW_FAILED_HRESULT(ParseError->get_url(&bstrUrl));
			THROW_FAILED_HRESULT(ParseError->get_srcText(&bstrSrc));
			THROW_FAILED_HRESULT(ParseError->get_line(&lLine));
			THROW_FAILED_HRESULT(ParseError->get_linepos(&lLinePos));
		}
#endif // defined(_DEBUG)

	} COM_CATCH;
	return fSuccess ? S_OK : E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////
// Xml-Config Verzeichnis aus Registry einlesen
HRESULT EnsureXmlPath (BSTR *pbstrXmlPath)
{
CRegKey regKey;

	if (ERROR_SUCCESS == regKey.Open (HKEY_CURRENT_USER, "Software", KEY_READ) &&
		ERROR_SUCCESS == regKey.Open (regKey, REG_COMPANY_KEY, KEY_READ) &&
		ERROR_SUCCESS == regKey.Open (regKey, REG_PRODUCT_KEY, KEY_READ) &&
		ERROR_SUCCESS == regKey.Open (regKey, g_cbDirectories))
	{
	char cbBuffer[_MAX_PATH];
	DWORD dwLen = sizeof(cbBuffer);

		if (ERROR_SUCCESS == regKey.QueryValue (cbBuffer, g_cbXmlConfigDir, &dwLen)) {
		CComBSTR bstr (cbBuffer);

			*pbstrXmlPath = bstr.Detach();
			return S_OK;
		}
		else {
		// VerzeichnisPfad neu erzeugen und anlegen
			if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA|CSIDL_FLAG_CREATE, NULL, 0, cbBuffer))) {
				PathAppend(cbBuffer, REG_COMPANY_KEY);
				CreateDirectory (cbBuffer, NULL);
				PathAppend(cbBuffer, REG_PRODUCT_KEY);
				CreateDirectory (cbBuffer, NULL);
				PathAppend(cbBuffer, g_cbXmlConfigDir);
				CreateDirectory (cbBuffer, NULL);

				if (ERROR_SUCCESS == regKey.SetValue(cbBuffer, g_cbXmlConfigDir)) {
				CComBSTR bstr (cbBuffer);

					*pbstrXmlPath = bstr.Detach();
					return S_OK;
				}
			}
		}
	}
	return E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CLoadXmlService::get_ResourceModule (BSTR *pbstrModule)
{
	CHECKOUTPOINTER(pbstrModule);

CComBSTR bstr (m_bstrModule);

	*pbstrModule = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CLoadXmlService::put_ResourceModule (BSTR bstrModule)
{
	m_bstrModule = bstrModule;
	return S_OK;
}

