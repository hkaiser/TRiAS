///////////////////////////////////////////////////////////////////////////
// @doc 
// @module CPCTFTransformEvents.h | Description goes here

#if !defined(_CPCTFTRANSFORMEVENTS_H__764CA445_DFF6_11D1_8608_00600875138A__INCLUDED_)
#define _CPCTFTRANSFORMEVENTS_H__764CA445_DFF6_11D1_8608_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////////////
// CProxyICoordTransformEvents
template <class T>
class CProxyICoordTransformEvents : public IConnectionPointImpl<T, &IID_ICoordTransformEvents, CComDynamicUnkArray>
{
public:

//ICoordTransformEvents : IDispatch
public:
	HRESULT Fire_CoordParamsToChange(
		IDispatch * pICoordSys,
		VARIANT_BOOL * pVal)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ICoordTransformEvents* pICoordTransformEvents = reinterpret_cast<ICoordTransformEvents*>(*pp);
				ret = pICoordTransformEvents->CoordParamsToChange(pICoordSys, pVal);
				if (VARIANT_TRUE == *pVal) break;
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ChangingCoordParams(
		IDispatch * pICoordSys)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ICoordTransformEvents* pICoordTransformEvents = reinterpret_cast<ICoordTransformEvents*>(*pp);
				ret = pICoordTransformEvents->ChangingCoordParams(pICoordSys);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
	HRESULT Fire_ChangedCoordParams(
		IDispatch * pICoordSys)
	{
		T* pT = (T*)this;
		pT->Lock();
		HRESULT ret = S_OK;
		IUnknown** pp = m_vec.begin();
		while (pp < m_vec.end())
		{
			if (*pp != NULL)
			{
				ICoordTransformEvents* pICoordTransformEvents = reinterpret_cast<ICoordTransformEvents*>(*pp);
				ret = pICoordTransformEvents->ChangedCoordParams(pICoordSys);
			}
			pp++;
		}
		pT->Unlock();
		return ret;
	}
};

#endif // !defined(_CPCTFTRANSFORMEVENTS_H__764CA445_DFF6_11D1_8608_00600875138A__INCLUDED_)
