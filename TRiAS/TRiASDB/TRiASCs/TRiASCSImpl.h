// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.10.1999 11:50:58 
//
// @doc
// @module TRiASCSImpl.h | Helper definitions et.al.

#if !defined(_TRIASCSIMPL_H__74259339_8228_44BB_9336_7E1C42182F87__INCLUDED_)
#define _TRIASCSIMPL_H__74259339_8228_44BB_9336_7E1C42182F87__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TRiASCS.h"
#include "resource.h"

#include <Com/VariantHelpers.h>
#include <Com/BSTRHelpers.h>
#include <Com/GUIDHelpers.h>

#include <Com/DefSmartIf.h>
#include <Com/DefTRiASCS.h>

#include <Com/PersistFileHelper.h>
#include <Com/StreamHelpers.h>

#include <LocaleHelpers.h>

#include "InterfaceWrappers.h"

DefineSmartInterface2(IGMCoordSystem, IID_IGMCoordSystem)		// WIGMCoordSystem
DefineSmartInterface2(DGMDatumTransformation, IID_DGMDatumTransformation)
DefineSmartInterface2(DGMCoordSystemsMgr, DIID_DGMCoordSystemsMgr)	// WDGMCoordSystemsMgr

DefineSmartInterface2(RefSpaceMgr, DIID_RefSpaceMgr)			// WRefSpaceMgr
DefineSmartInterface2(ProjSpace, DIID_ProjSpace)				// WProjSpace
DefineSmartInterface2(GeogSpace, DIID_GeogSpace)				// WGeogSpace
DefineSmartInterface2(PaperSpace, DIID_PaperSpace)			// WPaperSpace

#if defined(_TRACE_CS)
#define	CSTRACE		ATLTRACE
#define	CSTRACE1	ATLTRACE
#define	CSTRACE2	ATLTRACE
#define	CSTRACE3	ATLTRACE
#define	CSTRACE4	ATLTRACE
#define	CSTRACE5	ATLTRACE
#else
#define	CSTRACE(x)
#define	CSTRACE1(x,y)
#define	CSTRACE2(x,y1,y2)
#define	CSTRACE3(x,y1,y2,y3)
#define	CSTRACE4(x,y1,y2,y3,y4)
#define	CSTRACE5(x,y1,y2,y3,y4,y5)
#endif

//////////////////////////////////////////////////////////////////
// die Transformatoren der LIBCTF müssen immer S_OK liefern...
#if defined(_DEBUG)
#define ERROR_RCT_NOTOK(expr,hr)	\
	{ HRESULT __hr=(expr); if(S_OK != __hr)	{					\
			this->GenerateError(#expr, __FILE__, __LINE__, __hr);		\
			PushError();												\
			do { if (1 == _FailHRReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, #expr))   _CrtDbgBreak(); } while (0); \
			this->GenerateError(#expr, __FILE__, __LINE__, hr);			\
			PushError();												\
			return hr;													\
	} }
#else
#define ERROR_RCT_NOTOK(expr,hr)	\
	{ HRESULT __hr=(expr); if(S_OK != __hr)	{							\
			this->GenerateError(__hr);									\
			PushError();												\
			this->GenerateError(hr);									\
			PushError();												\
			return hr;													\
	} }
#endif

//////////////////////////////////////////////////////////////////
// Iteratoren...

#include <ospace/com/Iterenum.h>
#define ASSERT(expr)	_ASSERTE(expr)
#include <MakeEnumVariant.h>

// {24D48020-69AD-11d2-9842-0060085FC1CE}
extern "C" const IID __declspec(selectany) IID_IEnumTRiASCS =
	{ 0x24d48020, 0x69ad, 0x11d2, { 0x98, 0x42, 0x0, 0x60, 0x8, 0x5f, 0xc1, 0xce } };
DefineEnumerator2(WTRiASCS, IID_IEnumTRiASCS) 
DefineSmartEnumerator2(WTRiASCS, IID_IEnumTRiASCS)

//////////////////////////////////////////////////////////////////
// Füllzeichen für memset(...)

#if defined(_FILL_WITH_PADCHAR) 
#define PADCHAR 0xcd
#else
#define PADCHAR '\0'
#endif

class DISPENTRY 
{
public:
	DISPENTRY (WTRiASCS pCS, DWORD dwCookie, BOOL fMustTransform, BOOL fMustTransformDatum) :
		m_pCS(pCS), m_dwCookie(dwCookie), m_fMustTransform(fMustTransform), 
		m_fMustTransformDatum(fMustTransformDatum)
	{
	}
	DISPENTRY (const DISPENTRY &rhs)
	{
		m_pCS = rhs.GetTRiASCS();
		m_dwCookie = rhs.GetCookie();
		m_fMustTransform = rhs.MustTransform();
		m_fMustTransformDatum = rhs.MustTransformDatum();
	}

	DISPENTRY & operator= (const DISPENTRY &rhs)
	{
		if (&rhs != this) {
			m_pCS = rhs.GetTRiASCS();
			m_dwCookie = rhs.GetCookie();
			m_fMustTransform = rhs.MustTransform();
			m_fMustTransformDatum = rhs.MustTransformDatum();
		}
		return *this;
	}

// Helper
	DWORD GetCookie() const { return m_dwCookie; }
	WTRiASCS &GetTRiASCS() const { return const_cast<WTRiASCS &>(m_pCS); }
	BOOL MustTransform() const { return m_fMustTransform; }
	void MustTransform (BOOL fFlag) { m_fMustTransform = fFlag; }
	BOOL MustTransformDatum() const { return m_fMustTransformDatum; }
	void MustTransformDatum (BOOL fFlag) { m_fMustTransformDatum = fFlag; }

private:
	DWORD m_dwCookie;
	WTRiASCS m_pCS;
	BOOL m_fMustTransform;
	BOOL m_fMustTransformDatum;
};

typedef map<GUID, DISPENTRY> LPDispatchMap;

/////////////////////////////////////////////////////////////////////////////
// Registrierungsschlüssel

class CTRiASExtensionRegKey 
{
	UINT m_nTRiASVerMajor;
	UINT m_nTRiASVerMinor;
	UINT m_nHKLMResrcID;
	CComBSTR m_strKeyRoot;

	void GetHKLMRoot (CComBSTR& strRootKey)  
	{
		USES_CONVERSION;
		TCHAR	szKey[_MAX_PATH];
		wsprintf (szKey, _T("SOFTWARE\\") REG_COMPANY_KEY _T("\\") REG_PRODUCT_KEY TEXT("\\%d.%d\\%s"), m_nTRiASVerMajor, m_nTRiASVerMinor, OLE2A(m_strKeyRoot)); 
		strRootKey = szKey;
	}
	void GetHKCURoot (CComBSTR& strRootKey)  
	{
		USES_CONVERSION;
		TCHAR	szKey[_MAX_PATH];
		wsprintf (szKey, _T("Software\\") REG_COMPANY_KEY _T("\\") REG_PRODUCT_KEY TEXT("\\%s"), OLE2A(m_strKeyRoot)); 
		strRootKey = szKey;
	}

protected:
/////////////////////////////////////////////////////////////////////////////
// Konstruktor ist protected, d.h. Klasse überladen, z.B.:
// class CMyKey : public CTRiASExtensionRegKey {
//	public:
//		CMyKey (TRIAS_MAJOR, TRIAS_MINOR, IDR_HKLM, IDR_HKCU); 
	CTRiASExtensionRegKey (LPCOLESTR strKeyRoot, UINT nHKLMResrcID, UINT nTRiASVerMajor = 0, UINT nTRiASVerMinor = 0) 
		: m_nTRiASVerMajor (nTRiASVerMajor), m_nTRiASVerMinor (nTRiASVerMinor),
		  m_nHKLMResrcID (nHKLMResrcID), m_strKeyRoot (strKeyRoot) 
	{
	}

	HRESULT DoRegister (bool bRegister)  
	{
	TCHAR szCurrVer[_MAX_PATH];
	
		wsprintf (szCurrVer, _T("%d.%d"), m_nTRiASVerMajor, m_nTRiASVerMinor); 
	
	CComBSTR strCurrVer(szCurrVer);
	HRESULT hr = S_OK;
	
		_ATL_REGMAP_ENTRY regMap[] = {
			{ L"TRIASVER", strCurrVer },
			{ NULL, NULL },
		};
	
		if (0 != m_nHKLMResrcID && !SUCCEEDED (_Module.UpdateRegistryFromResource (m_nHKLMResrcID, bRegister, regMap)))   
			hr = E_FAIL;
//		if (0 != m_nHKCUResrcID && !SUCCEEDED (_Module.UpdateRegistryFromResource (m_nHKCUResrcID, bRegister, regMap)))   
//			hr = E_FAIL;
		return CopyHKLM2HKCU();
	}

	HRESULT CopyRecursive (CRegKey &keySrc, CRegKey &keyDst)  
	{
	DWORD	dwIndex;
	TCHAR	strName[_MAX_PATH];
	DWORD	dwNameSize = _MAX_PATH;
	TCHAR	strClass[_MAX_PATH];
	DWORD	dwClassSize = _MAX_PATH;
	FILETIME	lastWritten;
	CRegKey	src;
	CRegKey	dst;

		for (dwIndex = 0; ERROR_SUCCESS == ::RegEnumKeyEx (keySrc.m_hKey, dwIndex, strName, &dwNameSize, NULL, strClass, &dwClassSize, &lastWritten);  ++dwIndex)  {
			if (ERROR_SUCCESS != src.Open (keySrc.m_hKey, strName, KEY_READ))  
				continue;
			if (ERROR_SUCCESS != dst.Create (keyDst.m_hKey, strName))  
				continue;
			CopyRecursive (src, dst); 
			dwNameSize = _MAX_PATH;
			dwClassSize = _MAX_PATH;
		}

	DWORD	dwType;
	BYTE	data[2048];
	DWORD	dwDataSize = 2048;

		for (dwIndex = 0; ERROR_SUCCESS == ::RegEnumValue (keySrc.m_hKey, dwIndex, strName, &dwNameSize, NULL, &dwType, data, &dwDataSize);  ++dwIndex)  {
			::RegSetValueEx (keyDst.m_hKey, strName, NULL, dwType, data, dwDataSize); 
			dwNameSize = _MAX_PATH;
			dwDataSize = 2048;
		}
		return S_OK;
	}

public:
	HRESULT	put_TRiASMajor  (/*[in]*/ long l)  
	{
		_ASSERTE (l > 2); 	// alles erst ab Version 3.0
		m_nTRiASVerMajor = l;
		return S_OK;
	}
	HRESULT put_TRiASMinor  (/*[in]*/ long l)  
	{
		m_nTRiASVerMinor = l;
		return S_OK;
	}
	HRESULT	Register () 
	{
		return DoRegister (true); 
	}
	HRESULT	Unregister () 
	{
		return DoRegister (false);
	}
	HRESULT	CopyHKLM2HKCU () 
	{
	CComBSTR	strSrcKeyRoot, strDstKeyRoot;
	
		USES_CONVERSION;
		GetHKLMRoot (strSrcKeyRoot); 
		GetHKCURoot (strDstKeyRoot); 
	
	CRegKey	keySrc, keyDst;
	
		if (ERROR_SUCCESS != keySrc.Open (HKEY_LOCAL_MACHINE, OLE2A (strSrcKeyRoot), KEY_READ))   
			return E_FAIL;
		if (ERROR_SUCCESS != keyDst.Create (HKEY_CURRENT_USER, OLE2A (strDstKeyRoot)))   
			return E_FAIL;
		return CopyRecursive (keySrc, keyDst); 
	}
	HRESULT QueryValue (CComBSTR& strValue, LPCOLESTR lpcoleValue)  
	{
		USES_CONVERSION;
	
	CComBSTR strKeyName;
	
		GetHKCURoot (strKeyName); 

	CRegKey	rKey;
	LONG	res;

		if (ERROR_SUCCESS != (res = rKey.Open (HKEY_CURRENT_USER, OLE2A (strKeyName), KEY_READ)))    
			return MAKE_HRESULT (SEVERITY_ERROR, FACILITY_WINDOWS, res); 

	TCHAR	szValue[_MAX_PATH];
	DWORD	dwCount = _MAX_PATH;

		*szValue = _T('\0');
		if (ERROR_SUCCESS != (res = rKey.QueryValue (szValue, OLE2A (lpcoleValue) , &dwCount)))   
			return MAKE_HRESULT (SEVERITY_ERROR, FACILITY_WINDOWS, res); 
		strValue = szValue;
		return S_OK;
	}
	HRESULT QueryValue (DWORD& dwValue, LPCOLESTR lpcoleValue)  
	{
		USES_CONVERSION;

	CComBSTR	strKeyName;

		GetHKCURoot (strKeyName); 

	CRegKey	rKey;
	LONG	res;

		if (ERROR_SUCCESS != (res = rKey.Open (HKEY_CURRENT_USER, OLE2A (strKeyName), KEY_READ)))    
			return MAKE_HRESULT (SEVERITY_ERROR, FACILITY_WINDOWS, res); 
		if (ERROR_SUCCESS != (res = rKey.QueryValue (dwValue, OLE2A (lpcoleValue))))    
			return MAKE_HRESULT (SEVERITY_ERROR, FACILITY_WINDOWS, res); 
		return S_OK;
	}
};

class CTRiASCCSKeys : 
	public CTRiASExtensionRegKey 
{
public:
	CTRiASCCSKeys (LPCOLESTR strRoot); 
};

#endif // !defined(_TRIASCSIMPL_H__74259339_8228_44BB_9336_7E1C42182F87__INCLUDED_)
