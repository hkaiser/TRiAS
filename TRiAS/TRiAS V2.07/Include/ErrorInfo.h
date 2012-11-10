///////////////////////////////////////////////////////////////////////////
// @doc
// @module ErrorInfo.h | Auswerten einer evtl. existierenden ErrorInfo

#if !defined(_ERRORINFO_H__C6FF3BE4_5CCD_11D1_B9E3_080036D63803__INCLUDED_)
#define _ERRORINFO_H__C6FF3BE4_5CCD_11D1_B9E3_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

inline HRESULT GetErrorDescription (IUnknown *pUnk, BSTR *pbstrDesc)
{
CComQIPtr<ISupportErrorInfo, &IID_ISupportErrorInfo> spSupportErrorInfo(pUnk);

	if (NULL == spSupportErrorInfo)
		return E_FAIL;

HRESULT hr = spSupportErrorInfo->InterfaceSupportsErrorInfo(iid);

	if (FAILED(hr))	return hr;

CComPtr<IErrorInfo> spErrorInfo;

	hr = ::GetErrorInfo(0, &spErrorInfo);
	if (hr == S_FALSE) return hr;

	return spErrorInfo -> GetDescription (*pbstrDesc);
}

#endif // !defined(_ERRORINFO_H__C6FF3BE4_5CCD_11D1_B9E3_080036D63803__INCLUDED_)
