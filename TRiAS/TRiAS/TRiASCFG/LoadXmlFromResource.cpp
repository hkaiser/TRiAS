// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.12.2000 20:16:41 
//
// @doc
// @module LoadXmlFromResource.cpp | Definition of the LoadXmlFromResource function

#include "StdAfx.h"

#include <LoadXmlFromResource.h>

#include "Strings.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

namespace {
	CString ConvertToURL (CString str)
	{
	CString strRes;

		for (int i = 0; i < str.GetLength(); ++i) {
			if (iscntrl(str[i])) {
			CString strT;

				strT.Format ("%%%02x", str[i]);
				strRes += strT;
			}
			else
				strRes += str[i];
		}
		return str;
	}
}

HRESULT LoadXmlFromResource (HINSTANCE hInst, LPCSTR pcRsc, xml::IXMLDOMDocument **ppIXmlDoc)
{
	using namespace WTL;

	if (NULL == ppIXmlDoc)
		return E_POINTER;
	*ppIXmlDoc = NULL;

	if (NULL == hInst)
		hInst = _Module.GetResourceInstance();

	COM_TRY {
	__Interface<xml::IXMLDOMDocument> Doc;
	HRESULT hr = Doc.CreateInstance (CLSID_DOMDocument);

		if (FAILED(hr)) 
			return hr;		// kein XMLDOM-Parser installiert

	// resource-url zusammenbauen
	CString strResource (g_cbRes);
	char cbBuffer[_MAX_PATH];
		
		GetModuleFileName(hInst, cbBuffer, sizeof(cbBuffer));
		strResource += cbBuffer;
		strResource += "/";
		strResource += pcRsc;

	// XML-File laden
	VARIANT_BOOL fSuccess = VARIANT_FALSE;

		THROW_FAILED_HRESULT(Doc -> put_validateOnParse (VARIANT_TRUE));
		THROW_FAILED_HRESULT(Doc -> raw_load (CComVariant(ConvertToURL(strResource)), &fSuccess));

		*ppIXmlDoc = Doc.detach();

	} COM_CATCH;
	return S_OK;
}
