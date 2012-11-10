// $Header: $
// Copyright© 2003 Hartmut Kaiser, All rights reserved
// Created: 19.05.2003 12:32:08 
//
// @doc
// @module ConvertAscCoords.cpp | Definition of the <c CConvertAscCoords> class

#include "stdafx.h"

#include <ospace/std/vector>
#include <ospace/string/tokenize.h>

#include "CvrtAsc.h"
#include "ConvertAscCoords.h"

/////////////////////////////////////////////////////////////////////////////
// CConvertAscCoords

STDMETHODIMP CConvertAscCoords::InterfaceSupportsErrorInfo(REFIID riid)
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
STDMETHODIMP CConvertAscCoords::get_Version(BSTR *pVal)
{
	ATLTRACE(_T("CConvertAscCoords::get_Version\n"));

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
STDMETHODIMP CConvertAscCoords::put_Callback(ITransformLineOfTextCallback *pVal)
{
	ATLTRACE(_T("CConvertAscCoords::put_Callback\n"));
	m_Callback = pVal;
	return S_OK;
}

// Implementation of TransformLineOfText
STDMETHODIMP CConvertAscCoords::TransformLineOfText(BSTR bstrIn, BSTR *pbstrOut)
{
	ATLTRACE(_T("CConvertAscCoords::TransformLineOfText\n"));

	if (!pbstrOut) return E_POINTER;
	*pbstrOut = NULL;

	USES_CONVERSION;

	COM_TRY {
	string strIn (OLE2A(bstrIn));
	CComBSTR bstrOut (bstrIn);

		if ('G' == strIn[0]) {
		// Koordinatenzeile
		double dX[3] ={ 0.0, 0.0, 0.0 };
		double dY[3] ={ 0.0, 0.0, 0.0 };

		size_t iNL = strIn.find_last_of('\n');

			if (os_npos != iNL)
				strIn.resize(iNL);

		// aial 3 Koordinatenpaare sind auf einer Geoetriezeile
		int iCount = sscanf (strIn.c_str(), "G %lf%lf%lf%lf%lf%lf", 
			&dX[0], &dY[0], &dX[1], &dY[1], &dX[2], &dY[2]);

			if (2 == iCount || 4 == iCount || 6 == iCount) {
			
				bstrOut = L"G ";
				for (int iIndex = 0; iIndex < iCount/2; ++iIndex) {
					RETURN_FAILED_HRESULT(m_Callback->TransformCoords(
						&dX[iIndex], &dY[iIndex]));

				char cbBuffer[_MAX_PATH];

					sprintf(cbBuffer, "%lf %lf ", dX[iIndex], dY[iIndex]);
					bstrOut += cbBuffer;
				}

				bstrOut += L"\n";
			}
		}
		*pbstrOut = bstrOut.Detach();

	} COM_CATCH;
	return S_OK;
}

