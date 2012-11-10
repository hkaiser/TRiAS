// Implementation of CEnumUnknown
#include "stdafx.h"
#include "EnumUnknown.h"

HRESULT MyEnumWUnknown::Add(LPDISPATCH pIDisp)
{
    WUnknown IU = pIDisp;
    m_data.push_back(IU);
    return S_OK;
}

STDMETHODIMP CEnumUnknown::Next(ULONG celt, IUnknown ** rgelt, ULONG * pceltFetched)
{
    if (NULL == rgelt) return E_POINTER;

    WUnknown IU;
    HRESULT hr =myEnum.Next(celt,&IU,pceltFetched);
    *rgelt=IU.detach();
    return hr;
}

STDMETHODIMP CEnumUnknown::Skip(ULONG celt)
{
    return myEnum.Skip(celt);
}

STDMETHODIMP CEnumUnknown::Reset(void)
{
    return myEnum.Reset();
}

// DefineSmartInterface(EnumWUnknown);

STDMETHODIMP CEnumUnknown::Clone(IEnumUnknown ** ppenum)
{
//  TEST_E_POINTER("CEnumUnknown::Clone", ppenum);
/*    if (NULL == ppenum) return E_POINTER;

    *ppenum = NULL;

    CComObject<CEnumUnknown> *pEnum = NULL;
    HRESULT hr = CComObject<CEnumUnknown>::CreateInstance(&pEnum);

    if (FAILED(hr)) 
        return hr;

    try {
        WEnumWUnknown ICloned = NULL;

        THROW_FAILED_HRESULT(myEnum.Clone (&pICloned)); 

        WUnknown UI;

        for (ICloned -> Reset(); S_OK == ICloned -> Next (1, &UI, NULL); /**///)
/*        {
            THROW_FAILED_HRESULT(pEnum -> myEnum.AddItem(UI));
        }
    
    } catch (_com_error &e) {
        if (NULL != pEnum)
            delete pEnum;
        return _COM_ERROR(e);
    }

    *ppenum = pEnum;
    (*ppenum) -> AddRef();  // CreateInstance setzt RefCnt = 0
    return S_OK;*/
    return E_NOTIMPL;
}

HRESULT   CEnumUnknown::Add(IDispatch* pIDisp)
{
    return myEnum.Add(pIDisp);
}
// ATLTRACENOTINMPL("");