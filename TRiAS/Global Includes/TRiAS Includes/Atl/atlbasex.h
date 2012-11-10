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
	explicit CComVariantEx(LCID lcid = LOCALE_NEUTRAL) : m_lcid(lcid) {}
	~CComVariantEx() {}
	
	CComVariantEx(const VARIANT& varSrc, LCID lcid = LOCALE_NEUTRAL)
		: CComVariant(varSrc), m_lcid(lcid) {}
	CComVariantEx(const CComVariant& varSrc, LCID lcid = LOCALE_NEUTRAL)
		: CComVariant(varSrc), m_lcid(lcid) {}
	CComVariantEx(const CComBSTR &bstrSrc, LCID lcid = LOCALE_NEUTRAL)
		: CComVariant(bstrSrc), m_lcid(lcid) {}
	CComVariantEx(BSTR bstrSrc, LCID lcid = LOCALE_NEUTRAL)
		: CComVariant(bstrSrc), m_lcid(lcid) {}
	CComVariantEx(LPCOLESTR lpszSrc, LCID lcid = LOCALE_NEUTRAL)
		: CComVariant(lpszSrc), m_lcid(lcid) {}

#ifndef OLE2ANSI
	CComVariantEx(LPCSTR lpszSrc, LCID lcid = LOCALE_NEUTRAL)
		: CComVariant(lpszSrc), m_lcid(lcid) {}
#endif

#if _MSC_VER > 1020
	CComVariantEx(bool bSrc, LCID lcid = LOCALE_NEUTRAL)
		: CComVariant(bSrc), m_lcid(lcid) {}
#endif
	CComVariantEx(int nSrc, LCID lcid = LOCALE_NEUTRAL)
		: CComVariant(nSrc), m_lcid(lcid) {}
	CComVariantEx(BYTE nSrc, LCID lcid = LOCALE_NEUTRAL)
		: CComVariant(nSrc), m_lcid(lcid) {}
	CComVariantEx(short nSrc, LCID lcid = LOCALE_NEUTRAL)
		: CComVariant(nSrc), m_lcid(lcid) {}
	CComVariantEx(long nSrc, VARTYPE vtSrc = VT_I4, LCID lcid = LOCALE_NEUTRAL)
		: CComVariant(nSrc, vtSrc), m_lcid(lcid) {}
	CComVariantEx(long nSrc, LCID lcid)
		: CComVariant(nSrc, VT_I4), m_lcid(lcid) {}
	CComVariantEx(float fltSrc, LCID lcid = LOCALE_NEUTRAL)
		: CComVariant(fltSrc), m_lcid(lcid) {}
	CComVariantEx(double dblSrc, LCID lcid = LOCALE_NEUTRAL)
		: CComVariant(dblSrc), m_lcid(lcid) {}
	CComVariantEx(CY cySrc, LCID lcid = LOCALE_NEUTRAL)
		: CComVariant(cySrc), m_lcid(lcid) {}
	CComVariantEx(IDispatch* pSrc, LCID lcid = LOCALE_NEUTRAL)
		: CComVariant(pSrc), m_lcid(lcid) {}
	CComVariantEx(IUnknown* pSrc, LCID lcid = LOCALE_NEUTRAL)
		: CComVariant(pSrc), m_lcid(lcid) {}

// operations
	HRESULT ChangeTypeEx(VARTYPE vtNew)
		{ return ChangeTypeEx (vtNew, NULL, m_lcid); }
	HRESULT ChangeTypeEx(VARTYPE vtNew, const VARIANT* pSrc, LCID lcid = LOCALE_NEUTRAL)
	{
		VARIANT* pVar = const_cast<VARIANT*>(pSrc);
		// Convert in place if pSrc is NULL
		if (pVar == NULL)
			pVar = this;
		// Do nothing if doing in place convert and vts not different
		return ::VariantChangeTypeEx(this, pVar, lcid, 0, vtNew);
	}

// type conversion operators
	operator VARIANT_BOOL() throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeTypeEx(VT_BOOL));
		return V_BOOL(this);
	}
	operator int () throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeTypeEx(VT_I4));
		return V_I4(this); 
	}
	operator long () throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeTypeEx(VT_I4));
		return V_I4(this); 
	}
	operator unsigned long () throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeTypeEx(VT_UI4));
		return V_UI4(this); 
	}
	operator BYTE () throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeTypeEx(VT_UI1));
		return V_UI1(this); 
	}
	operator float () throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeTypeEx(VT_R4));
		return V_R4(this); 
	}
	operator double () throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeTypeEx(VT_R8));
		return V_R8(this); 
	}
	operator CY () throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeTypeEx(VT_CY));
		return V_CY(this); 
	}
	operator IDispatch * () throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeTypeEx(VT_DISPATCH));

	IDispatch *pIDisp = V_DISPATCH(this);

		if (NULL != pIDisp) 
			pIDisp -> AddRef();
		return pIDisp; 
	}
	operator IUnknown * () throw(_com_error)
	{
		THROW_FAILED_HRESULT(ChangeTypeEx(VT_UNKNOWN));

	IUnknown *pIUnk = V_UNKNOWN(this);

		if (NULL != pIUnk)
			pIUnk -> AddRef();
		return pIUnk; 
	}
	operator CComBSTR ()
	{
		THROW_FAILED_HRESULT(ChangeTypeEx(VT_BSTR));
		return CComBSTR(V_BSTR(this)); 
	}

protected:
	LCID m_lcid;
};

///////////////////////////////////////////////////////////////////////////////
// SemaphoreSupport
template<class T>
class CComSemaphore
{
private:
	LONG &m_rlSem;

public:
	inline CComSemaphore (LONG &rlSem) : m_rlSem(rlSem)
	{
		T::Increment (&m_rlSem);
	}
	inline ~CComSemaphore ()
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
