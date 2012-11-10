///////////////////////////////////////////////////////////////////////////
// atlbasex.h

#if !defined(_ATLBASEX_H__99F636F5_5C50_11D1_9717_00A024D6F582__INCLUDED_)
#define _ATLBASEX_H__99F636F5_5C50_11D1_9717_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __cplusplus
	#error ATL requires C++ compilation (use a .cpp suffix)
#endif

#ifndef __ATLBASE_H__
	#error atlcom.h requires atlbase.h to be included first
#endif

#pragma pack(push, _ATL_PACKING)

#ifndef ATL_NO_NAMESPACE
namespace ATL
{
#endif

/////////////////////////////////////////////////////////////////////////////
// CComVariantEx

class CComVariantEx : public CComVariant
{
// Constructors
public:
	CComVariantEx() {}
	~CComVariantEx() {}
	
	CComVariantEx(const VARIANT& varSrc)
		: CComVariant(varSrc) {}
	CComVariantEx(const CComVariant& varSrc)
		: CComVariant(varSrc) {}
	CComVariantEx(BSTR bstrSrc)
		: CComVariant(bstrSrc) {}
	CComVariantEx(LPCOLESTR lpszSrc)
		: CComVariant(lpszSrc) {}

#ifndef OLE2ANSI
	CComVariantEx(LPCSTR lpszSrc)
		: CComVariant(lpszSrc) {}
#endif

#if _MSC_VER>1020
	CComVariantEx(bool bSrc)
		: CComVariant(bSrc) {}
#endif
	CComVariantEx(int nSrc)
		: CComVariant(nSrc) {}
	CComVariantEx(BYTE nSrc)
		: CComVariant(nSrc) {}
	CComVariantEx(short nSrc)
		: CComVariant(nSrc) {}
	CComVariantEx(long nSrc, VARTYPE vtSrc = VT_I4)
		: CComVariant(nSrc, vtSrc) {}
	CComVariantEx(float fltSrc)
		: CComVariant(fltSrc) {}
	CComVariantEx(double dblSrc)
		: CComVariant(dblSrc) {}
	CComVariantEx(CY cySrc)
		: CComVariant(cySrc) {}
	CComVariantEx(IDispatch* pSrc)
		: CComVariant(pSrc) {}
	CComVariantEx(IUnknown* pSrc)
		: CComVariant(pSrc) {}

// type conversion operators
	operator VARIANT_BOOL() throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeType(VT_BOOL));
		return V_BOOL(this);
	}
	operator int () throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeType(VT_I4));
		return V_I4(this); 
	}
	operator long () throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeType(VT_I4));
		return V_I4(this); 
	}
	operator BYTE () throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeType(VT_UI1));
		return V_UI1(this); 
	}
	operator float () throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeType(VT_R4));
		return V_R4(this); 
	}
	operator double () throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeType(VT_R8));
		return V_R8(this); 
	}
	operator CY () throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeType(VT_CY));
		return V_CY(this); 
	}
	operator IDispatch * () throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeType(VT_DISPATCH));

	IDispatch *pIDisp = V_DISPATCH(this);

		if (NULL != pIDisp) 
			pIDisp -> AddRef();
		return pIDisp; 
	}
	operator IUnknown * () throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeType(VT_UNKNOWN));

	IUnknown *pIUnk = V_UNKNOWN(this);

		if (NULL != pIUnk)
			pIUnk -> AddRef();
		return pIUnk; 
	}
	operator BSTR ()
	{
		THROW_FAILED_HRESULT(ChangeType(VT_BSTR));
		return V_BSTR(this); 
	}
};

///////////////////////////////////////////////////////////////////////////////
// SemaphoreSupport
template<class T>
class CSemaphore
{
private:
	LONG &m_rlSem;

public:
	inline CSemaphore (LONG &rlSem) : m_rlSem(rlSem)
	{
		T::Increment (&m_rlSem);
	}
	inline ~CSemaphore ()
	{
		T::Decrement (&m_rlSem);
	}
};

template<class T>
inline bool IsSemaphoreSignaled (LONG &rlSem, T &rTarget) 
{ 
	rTarget.Lock(); 
	bool fSignaled = (rlSem != 0) ? true : false; 
	rTarget.Unlock(); 
	return fSignaled; 
}

#pragma pack(pop)

#ifndef ATL_NO_NAMESPACE
}; //namespace ATL
#endif

#endif // !defined(_ATLBASEX_H__99F636F5_5C50_11D1_9717_00A024D6F582__INCLUDED_)
