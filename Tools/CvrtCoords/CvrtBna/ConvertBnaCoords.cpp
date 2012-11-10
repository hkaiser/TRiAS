// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 05.09.2002 12:45:43 
//
// @doc
// @module ConvertBnaCoords.cpp | Definition of the <c CConvertBnaCoords> class

#include "stdafx.h"

#include <ospace/std/vector>
#include <ospace/string/tokenize.h>

#include "CvrtBna.h"
#include "ConvertBnaCoords.h"

/////////////////////////////////////////////////////////////////////////////
// CConvertBnaCoords

STDMETHODIMP CConvertBnaCoords::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITransformLineOfText
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

// Implementation of get_Version
STDMETHODIMP CConvertBnaCoords::get_Version(BSTR *pVal)
{
	ATLTRACE(_T("CConvertBnaCoords::get_Version\n"));

	if (!pVal) return E_POINTER;
	*pVal = NULL;

CComBSTR bstrName;
CComBSTR bstrVersion;
CComBSTR bstrCopyright;

	if (!bstrName.LoadString(IDS_FORMATNAME) ||
		!bstrVersion.LoadString(IDS_VERSION) || 
		!bstrCopyright.LoadString(IDS_COPYRIGHT))
	{
		return E_UNEXPECTED;
	}

	bstrName.Append(L", ");
	bstrName.AppendBSTR(bstrVersion);
	bstrName.Append(L", ");
	bstrName.AppendBSTR(bstrCopyright);

	*pVal = bstrName.Detach();
	return S_OK;
}

// Implementation of put_Callback
STDMETHODIMP CConvertBnaCoords::put_Callback(ITransformLineOfTextCallback *pVal)
{
	ATLTRACE(_T("CConvertBnaCoords::put_Callback\n"));
	m_Callback = pVal;
	return S_OK;
}

// Implementation of TransformLineOfText
STDMETHODIMP CConvertBnaCoords::TransformLineOfText(BSTR bstrIn, BSTR *pbstrOut)
{
	ATLTRACE(_T("CConvertBnaCoords::TransformLineOfText\n"));

	if (!pbstrOut) return E_POINTER;
	*pbstrOut = NULL;

	USES_CONVERSION;

	COM_TRY {
	string strIn (OLE2A(bstrIn));
	CComBSTR bstrOut (bstrIn);

		if ('\"' != strIn[0]) {
		// Koordinaten
		double dX = 0;
		double dY = 0;

		size_t iNL = strIn.find_last_of('\n');

			if (os_npos != iNL)
				strIn.resize(iNL);

			if (2 == sscanf (strIn.c_str(), "%lf,%lf", &dX, &dY)) {
			// ein bischen Fehlertoleranz muß sein, alles, was nicht aus
			// 2 Zahlen an Zeilenanfang besteht, wird ignoriert

			// versuchen das Zahlenformat der Ausgangskoordinaten festzustellen
			char cbFormat[256];
			
			int iLenX = strIn.find_first_of(',');
			int iLenY = strIn.size() - iLenX -1;
			int iDecX = strIn.find_first_of('.');
			int iDecY = strIn.find_last_of('.');

			int iLen = max(iLenX, iLenY);

				if (os_npos == iDecX || os_npos == iDecY) {
					wsprintf(cbFormat, "%%%d.0f,%%%d.0f\n", iLen, iLen);
				}
				else {
					iDecX = iLenX - iDecX -1;
					iDecY = strIn.size() - iDecY -1;

				int iDec = max(iDecX, iDecY);

					wsprintf(cbFormat, "%%%d.%df,%%%d.%df\n", iLen, iDec, iLen, iDec);
				}

				RETURN_FAILED_HRESULT(m_Callback->TransformCoords(&dX, &dY));

			char cbBuffer[_MAX_PATH];

				sprintf(cbBuffer, cbFormat, dX, dY);
				bstrOut = cbBuffer;
			}
		}
		*pbstrOut = bstrOut.Detach();

	} COM_CATCH;
	return S_OK;
}

