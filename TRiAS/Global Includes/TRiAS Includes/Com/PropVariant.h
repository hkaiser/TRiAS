// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/19/1998 09:26:11 AM
//
// @doc
// @module PropVariant.h | Description goes here

#if !defined(_PROPVARIANT_H__7CD5571A_6427_11D2_9EDE_006008447800__INCLUDED_)
#define _PROPVARIANT_H__7CD5571A_6427_11D2_9EDE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CPropVariant
class CPropVariant : public tagPROPVARIANT
{
// Constructors
public:
	CPropVariant()
	{
		::PropVariantInit(this);
	}
	~CPropVariant()
	{
		Clear();
	}

	CPropVariant(const PROPVARIANT& varSrc)
	{
		::PropVariantInit(this);
		InternalCopy(&varSrc);
	}
	CPropVariant(const VARIANT& varSrc)
	{
		::PropVariantInit(this);
		InternalCopy((PROPVARIANT *)&varSrc);
	}
	CPropVariant(const CPropVariant& varSrc)
	{
		::PropVariantInit(this);
		InternalCopy(&varSrc);
	}

// Assignment Operators
public:
	CPropVariant& operator=(const CPropVariant& varSrc)
	{
		InternalCopy(&varSrc);
		return *this;
	}
	CPropVariant& operator=(const PROPVARIANT& varSrc)
	{
		InternalCopy(&varSrc);
		return *this;
	}

// Operations
public:
	HRESULT Clear() { return ::PropVariantClear(this); }
	HRESULT Copy(const PROPVARIANT* pSrc) { return ::PropVariantCopy(this, const_cast<PROPVARIANT *>(pSrc)); }
	operator VARIANT *() { return reinterpret_cast<VARIANT *>(this); }

	HRESULT CPropVariant::Attach(VARIANT *pSrc) { return Attach (reinterpret_cast<PROPVARIANT *>(pSrc)); }
	HRESULT CPropVariant::Attach(PROPVARIANT *pSrc)
	{
		// Clear out the variant
		HRESULT hr = Clear();
		if (!FAILED(hr))
		{
			// Copy the contents and give control to CPropVariant
			memcpy(this, pSrc, sizeof(PROPVARIANT));
			PropVariantInit(pSrc);
			hr = S_OK;
		}
		return hr;
	}
	HRESULT CPropVariant::Detach(VARIANT *pDest) { return Detach(reinterpret_cast<PROPVARIANT *>(pDest)); }
	HRESULT CPropVariant::Detach(PROPVARIANT *pDest)
	{
		// Clear out the variant
		HRESULT hr = ::PropVariantClear(pDest);
		if (!FAILED(hr))
		{
			// Copy the contents and remove control from CPropVariant
			memcpy(pDest, this, sizeof(PROPVARIANT));
			vt = VT_EMPTY;
			hr = S_OK;
		}
		return hr;
	}
	HRESULT WriteToPropertyStorage(IPropertyStorage *pIProps, LPCOLESTR pcoleName, ULONG ulPropId)
	{
		enum { DEFAULT_PROPID = 0x40000000,	};

		_ASSERTE(NULL != pIProps);

	PROPSPEC spec;

		spec.ulKind = PRSPEC_PROPID;
		spec.propid = ulPropId;
		RETURN_FAILED_HRESULT(pIProps -> WriteMultiple (1, &spec, this, DEFAULT_PROPID));
		if (NULL != pcoleName)
		{
			RETURN_FAILED_HRESULT(pIProps -> WritePropertyNames (1, &ulPropId, const_cast<LPWSTR *>(&pcoleName)));
		}
		return S_OK;
	}
	HRESULT ReadFromPropertyStorage(IPropertyStorage *pIProps, LPCOLESTR pcoleName)
	{
		RETURN_FAILED_HRESULT(Clear());		// clear out this PROPVARIANT

	PROPSPEC spec;

		spec.ulKind = PRSPEC_LPWSTR;
		spec.lpwstr = const_cast<LPWSTR>(pcoleName);
		return pIProps -> ReadMultiple (1, &spec, this);
	}

// Implementation
public:
	HRESULT CPropVariant::InternalClear()
	{
		HRESULT hr = Clear();
		_ASSERTE(SUCCEEDED(hr));
		if (FAILED(hr))
		{
			vt = VT_ERROR;
			scode = hr;
		}
		return hr;
	}
	void CPropVariant::InternalCopy(const PROPVARIANT* pSrc)
	{
		HRESULT hr = Copy(pSrc);
		if (FAILED(hr))
		{
			vt = VT_ERROR;
			scode = hr;
		}
	}
};

inline PROPVARIANT *CLEARED (CPropVariant *pv)
{
	_ASSERTE(NULL != pv);
	pv -> Clear();
	return pv;
}

#endif // !defined(_PROPVARIANT_H__7CD5571A_6427_11D2_9EDE_006008447800__INCLUDED_)
