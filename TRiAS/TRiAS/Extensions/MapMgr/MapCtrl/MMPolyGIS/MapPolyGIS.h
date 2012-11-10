// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 16.03.2002 23:53:13 
//
// @doc
// @module MapPolyGIS.h | Declaration of the <c CMapPolyGIS> class

#if !defined(_MAPPOLYGIS_H__6F208672_2EE2_4803_8EFF_50BD26B8EA94__INCLUDED_)
#define _MAPPOLYGIS_H__6F208672_2EE2_4803_8EFF_50BD26B8EA94__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

///////////////////////////////////////////////////////////////////////////////
// LizensierungsKlasse
#if defined(_DEBUG)
extern "C" bool g_fGlobalLic;
#else
#define g_fGlobalLic false
#endif // defined(_DEBUG)

BOOL SetLicensed (LPCSTR lpwNewKey);
BOOL GetLicensed (void);
BOOL GetLicenseKey (LPWSTR, size_t iLen);

class CMyLicense
{
protected:
	static BOOL VerifyLicenseKey(BSTR bstr)
	{
	CComBSTR bstrKey;

		USES_CONVERSION;
		if ((GetLicenseKey (0, &bstrKey) && !wcscmp (bstrKey, bstr)) ||
			 ::SetLicensed (OLE2A(bstr)))
		{
			return TRUE;
		}
		return FALSE;
	}

	static BOOL GetLicenseKey (DWORD, BSTR *pBstr) 
	{
	CComBSTR bstrKey (_MAX_PATH, (LPCOLESTR)NULL);

		if (!::GetLicenseKey (bstrKey.m_str, _MAX_PATH))
			return FALSE;

		*pBstr = bstrKey.Detach(); 
		return TRUE;
	}

	static BOOL IsLicenseValid() { return g_fGlobalLic || ::GetLicensed(); }
};

/////////////////////////////////////////////////////////////////////////////
// CMapPolyGIS
class ATL_NO_VTABLE CMapPolyGIS :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMapPolyGIS, &CLSID_MapPolyGIS>,
	public IConnectionPointContainerImpl<CMapPolyGIS>,
	public IDispatchImpl<IMapPolyGIS, &IID_IMapPolyGIS, &LIBID_MMPOLYGISLib>,
	public ITopoMapImpl
{
public:
	CMapPolyGIS() {}
	~CMapPolyGIS() {}

	HRESULT FinalConstruct();
	void FinalRelease();

	DECLARE_REGISTRY_RESOURCEID(IDR_MAPPOLYGIS)
	DECLARE_CLASSFACTORY2(CMyLicense)

	BEGIN_COM_MAP(CMapPolyGIS)
		COM_INTERFACE_ENTRY(IMapPolyGIS)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ITopoMap)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CMapPolyGIS)
	END_CONNECTION_POINT_MAP()

public:
// IMapImport
	STDMETHOD(GetImageFileFilter)(BSTR* pFilter); 
	STDMETHOD(GetAltFileFilter)(/*[out]*/ BSTR* pFilter);
	STDMETHOD(GetDisplayName)(/*[out]*/ BSTR* strDisplay);
	STDMETHOD(CheckPictureFile)(ITopoPict* pServer, long* pValid);
	STDMETHOD(CheckAltFile)(BSTR strFileName, long* pValid);
	STDMETHOD(GetNameAndIdent)(BSTR bstrPathName, BSTR *pbstrName, BSTR *pbstrIdent);
	STDMETHOD(GetAltFileTyp)(/*[out]*/ BSTR* pTyp);
	STDMETHOD(HaveMultiMap)(/*[out]*/ long* pYesNo);

// #HK020318
	STDMETHOD(BitmapIndex)(/*[out, retval]*/ long *plIndex);
	STDMETHOD(CorrectName)(/*[in]*/ BSTR bstrDestDir, /*[in]*/ BSTR bstrName, /*[out, retval]*/ BSTR *pbstrToWrite);
//	STDMETHOD(CorrectDirectory)(/*[in]*/ BSTR bstrDestDir, /*[out, retval]*/ BSTR *pbstrToWrite);
	STDMETHOD(GetDescription)(/*[out, retval]*/ BSTR *prgFlags);
	STDMETHOD(CopyFlags)(/*[out, retval]*/ COPYFLAG *prgFlags);
	STDMETHOD(MakeFullName)(/*[in]*/ BSTR bstrBaseDir, /*[out, retval]*/ BSTR *pbstrFullName);

// #HK011018
	STDMETHOD(NeedsCoordSystem)(/*[out, retval]*/ VARIANT_BOOL *pfNeedsCoordSys);
	STDMETHOD(PutCoordSystem)(IUnknown *pICS);

private:
	CComBSTR m_bstrName;
};

#endif // !defined(_MAPPOLYGIS_H__6F208672_2EE2_4803_8EFF_50BD26B8EA94__INCLUDED_)
