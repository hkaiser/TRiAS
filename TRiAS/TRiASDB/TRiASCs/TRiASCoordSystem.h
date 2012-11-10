// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 07.10.1999 12:49:07 
//
// @doc
// @module TRiASCoordSystem.h | Declaration of the <c CTRiASCoordSystem> class

#if !defined(_TRIASCOORDSYSTEM_H__E69F9BA2_A213_437D_B00E_786C2C69741D__INCLUDED_)
#define _TRIASCOORDSYSTEM_H__E69F9BA2_A213_437D_B00E_786C2C69741D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// 
#include <Esnecil.h>
#include <EsnecilExt.h>

extern bool g_fEsnecil;

#if defined(_DEBUG)
extern bool g_fGlobalLic;
#else
#define g_fGlobalLic false
#endif

inline
BOOL GetLicenseKey (LPWSTR pwKey, size_t iLen)
{
// Environment überprüfen
CEsnecilExt Lic;

	if (!Lic || Lic.GetLevel() < CKILEVEL_PLUS)
		return FALSE;

// Lizensierungsmodul überprüfen
LPCSTR pcSiteCode = Lic.GetSiteCode();

	if (NULL != pwKey && NULL != pcSiteCode) 		// Key kopieren
		mbstowcs (pwKey, pcSiteCode, min(iLen, strlen(pcSiteCode)));

	return (NULL != pcSiteCode) ? TRUE : FALSE;
}

inline
BOOL GetLicensed (void)
{
	if (g_fGlobalLic || g_fEsnecil || 
		NULL != GetProcAddress(GetModuleHandle(NULL), "DEXEXTENSIONPROC"))
	{
		return TRUE;	// unter TRiAS immer lizensiert
	}

// Environment überprüfen
CEsnecilExt Lic;

	if (!Lic || Lic.GetLevel() < CKILEVEL_PLUS)
		return FALSE;

	g_fEsnecil = true;
	return TRUE;
}

inline
BOOL SetLicensed (LPCSTR lpNewKey)		// Lizensierung ist erfolgt
{
CEsnecilExt Lic;

	return Lic.Authorize(lpNewKey);
}

///////////////////////////////////////////////////////////////////////////////
// LizensierungsKlasse
class CCoordSysLicense
{
protected:
	static 
	BOOL VerifyLicenseKey(BSTR bstr)
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

	static 
	BOOL GetLicenseKey (DWORD, BSTR *pBstr) 
	{
	CComBSTR bstrKey (_MAX_PATH, (LPCOLESTR)NULL);

		if (!::GetLicenseKey (bstrKey.m_str, _MAX_PATH))
			return FALSE;

		*pBstr = bstrKey.Detach(); 
		return TRUE;
	}

	static 
	BOOL IsLicenseValid() { return ::GetLicensed(); }
};

/////////////////////////////////////////////////////////////////////////////
// CTRiASCoordSystem

#include "CPTRiASCsEvents.h"
#include <Com/MemoryHelper.h>

const long CS_VERSION = 0x0100L;
const long CS_WITH_DESCRIPTION = 0x0101L;
const long CS_WITH_NAME = 0x0102L;
const long LASTKNOWN_CS_VERSION = CS_WITH_NAME;

class ATL_NO_VTABLE CTRiASCoordSystem :
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CTRiASCoordSystem, &CLSID_TRiASCS>,
	public CErrSupport<CTRiASCoordSystem, &IID_ITRiASCS>,
	public CPersistStreamInitImpl<CTRiASCoordSystem, &CLSID_TRiASCS>,
	public CPersistFileImpl<CTRiASCoordSystem, &CLSID_TRiASCS>,
	public CProxyITRiASCSEvents<CTRiASCoordSystem>,
	public IConnectionPointContainerImpl<CTRiASCoordSystem>,
	public IDispatchImpl<ITRiASCS, &IID_ITRiASCS, &LIBID_TRIASCS>,
	public IDispatchImpl<ITRiASCSUIHelper, &IID_ITRiASCSUIHelper, &LIBID_TRIASCS>,
	public ITRiASCSTransformData,
	public ITRiASCSValidate,
#if defined(_USE_OGC_COMPATIBILITY)
	public ISpatialReferenceInfo,
#endif // defined(_USE_OGC_COMPATIBILITY)
	public CComControl<CTRiASCoordSystem>,
	public IPropertyNotifySinkCP<CTRiASCoordSystem>,
	public IOleObjectImpl<CTRiASCoordSystem>,
	public ISpecifyPropertyPagesImpl<CTRiASCoordSystem>
{
private:
	bool m_bDirty;
	TRIASCSTYPE m_csType;
	GUID m_guid;
	CComBSTR m_bstrName;
	CComBSTR m_strDescription;
	CComBSTR m_strCategory;

	WTRiASCSGCS	m_pGeographicCS;
	WTRiASCSPCS	m_pProjectedCS;
	WTRiASCSDatumTransformation	m_pDTrans;
#if defined(USE_GM_CS)
	WIGMCoordSystem	m_gmCS;
#endif // defined(USE_GM_CS)

	HRESULT InternalInitialize () 
	{
		m_strDescription = _T("");
		m_strCategory = _T("");
		ChangeGUID();
		return put_CoordSystemType (tcsCS_Projected); 
	}

	HRESULT FindTcfFile (BSTR bstrOrgFile, BSTR *pbstrLocation);
	HRESULT EnsureTcfPath (BSTR *pbstrTcfPath);
	HRESULT FindCoordSysResource (LPCSTR pcBaseName, HGLOBAL *phGbl);
	HRESULT LoadCoordSysFromResource (CGlobalMem &rMem);

public:
	CTRiASCoordSystem()
		: m_csType (tcsCS_Projected), m_guid (IID_NULL), m_bDirty(true)
	{
	}
	~CTRiASCoordSystem() 
	{
	}
	
	HRESULT	FinalConstruct();
	void FinalRelease();

	HRESULT UIDeactivate() { return S_OK; }
//	virtual BOOL ProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID) 
//	{
//		return 0;
//	}

	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASCoordSystem)
//	_ATLX_DEBUG_ADDREF_RELEASE_IMPL(CTRiASCoordSystem)
	
	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASCOORDSYSTEM)
	DECLARE_AGGREGATABLE(CTRiASCoordSystem)
	DECLARE_GET_CONTROLLING_UNKNOWN()
	DECLARE_CLASSFACTORY2(CCoordSysLicense)

	BEGIN_COM_MAP(CTRiASCoordSystem)
		COM_INTERFACE_ENTRY(ITRiASCSTransformData)	// meist gebrauchtes Interface
		COM_INTERFACE_ENTRY(ITRiASCS)
		COM_INTERFACE_ENTRY2(IDispatch, ITRiASCS)
		COM_INTERFACE_ENTRY(ITRiASCSValidate)
		COM_INTERFACE_ENTRY_CHAIN(CPersistStreamInitImpl_t)
		COM_INTERFACE_ENTRY_CHAIN(CPersistFileImpl_t)
		COM_INTERFACE_ENTRY_CHAIN(CErrSupport_t)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
		COM_INTERFACE_ENTRY_IMPL(IOleObject)
		COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
		COM_INTERFACE_ENTRY(ITRiASCSUIHelper)
#if defined(_USE_OGC_COMPATIBILITY)
		COM_INTERFACE_ENTRY(ISpatialReferenceInfo)
#endif // defined(_USE_OGC_COMPATIBILITY)
	END_COM_MAP()

	BEGIN_CONNECTION_POINT_MAP(CTRiASCoordSystem)
		CONNECTION_POINT_ENTRY(IID_ITRiASCSEvents)
		CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	END_CONNECTION_POINT_MAP()

	BEGIN_PROPERTY_MAP(CTRiASCoordSystem)
		PROP_PAGE(CLSID_TRiASCSPpg)
		PROP_PAGE(CLSID_TRiASGCSPpg)
		PROP_PAGE(CLSID_TRiASPCSPpg)
	END_PROPERTY_MAP()

public:
	STDMETHOD(get_Category)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Category)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Description)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);

// ITRiASCS
	STDMETHOD(get_CoordSystemType)(/*[out, retval]*/ TRIASCSTYPE *pVal);
	STDMETHOD(put_CoordSystemType)(/*[in]*/ TRIASCSTYPE newVal);
	STDMETHOD(get_GUID)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_GUID)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_GeographicCS)(/*[out, retval]*/ ITRiASCSGCS **GCS);
	STDMETHOD(get_ProjectedCS)(/*[out, retval]*/ ITRiASCSPCS **PCS);
	STDMETHOD(get_DatumTransformation)(/*[out, retval]*/ ITRiASCSDatumTransformation **pVal);
	STDMETHOD(ChangeGUID)();
	STDMETHOD(Recompute)();
	STDMETHOD(LoadFromRegistry)(/*[in]*/ TCS_REGISTRYROOT root, /*[in]*/ BSTR strRegKey, /*[in, optional]*/ VARIANT strComputername);
	STDMETHOD(SaveToRegistry)(/*[in]*/ TCS_REGISTRYROOT root, /*[in]*/ BSTR strRegKey, /*[in, optional]*/ VARIANT strComputername);
	STDMETHOD(LoadFromFile)(/*[in]*/ BSTR strFileName);
	STDMETHOD(SaveToFile)(/*[in]*/ BSTR strFile);
	STDMETHOD(IsEqual)(/*[in]*/ ITRiASCS *pIOther, /*[out, retval]*/ VARIANT_BOOL *pfIsEqual);

// ITRiASCSValidate
	STDMETHOD(IsValid) ();
	STDMETHOD(RecomputeTransformation)(/*[in,defaultvalue(NULL)]*/ ITRiASCSGCS *pGCS);

// ITRiASCSTransformData
	STDMETHOD(Transform)(/*[in]*/ long nCoords, /*[in,out,size_is(nCoords)]*/ CSCOORD* pCoords); 
	STDMETHOD(TransformInverse)(/*[in]*/ long nCoords, /*[in,out,size_is(nCoords)]*/ CSCOORD* pCoords); 

// ITRiASCSTransformInfo
	STDMETHOD(CanTransform)(/*[in]*/ LONG typeOfTransformation);

// ITRiASCSUIHelper
	STDMETHOD(get_InputMask) (/*[in]*/ COORDELEMENT rgElement, /*[out, retval]*/ BSTR *UIMask);
	STDMETHOD(get_Precision) (/*[out, retval]*/ long *pPrec);
	STDMETHOD(put_Precision) (/*[in]*/ long lPrec);
	STDMETHOD(Format) (/*[in]*/ COORDELEMENT rgElement, /*[in]*/ double dValue, /*[out, retval]*/ BSTR *pbstrFormattedElement);
	STDMETHOD(Convert) (/*[in]*/ COORDELEMENT rgElement, /*[in]*/ BSTR bstrFormatted, /*[out, retval]*/ double *pdValue);

#if defined(_USE_OGC_COMPATIBILITY)
// ISpatialReferenceInfo
	STDMETHODIMP get_Name(BSTR *pbstrName);
	STDMETHODIMP put_Name(BSTR bstrName);
	STDMETHODIMP get_Authority(BSTR *pbstrAuth);
	STDMETHODIMP put_Authority(BSTR bstrAuth);
	STDMETHODIMP get_Code(long *plCode);
	STDMETHODIMP put_Code(long lCode);
	STDMETHODIMP get_Alias(BSTR *pbstrAlias);
	STDMETHODIMP put_Alias(BSTR bstrAlias);
	STDMETHODIMP get_Abbreviation(BSTR *pbstrAbbrev);
	STDMETHODIMP put_Abbreviation(BSTR bstrAbbrev);
	STDMETHODIMP get_Remarks(BSTR *pbstrRemarks);
	STDMETHODIMP put_Remarks(BSTR bstrRemarks);
	STDMETHODIMP get_WellKnownText(BSTR *pbstrWkt);
#endif // defined(_USE_OGC_COMPATIBILITY)

// CPersistStreamInit
	HRESULT	OnInitNew ();
	HRESULT LoadData (LPSTREAM pStm, DWORD dwVersion); 
	HRESULT SaveData (LPSTREAM pStm, BOOL bClearDirty); 
	LONGLONG GetDataSize ();

	DWORD GetSignature () { char *s = "CSCS"; return *((DWORD *)s); }
	DWORD GetVersion () { return LASTKNOWN_CS_VERSION;  }

	static CLIPFORMAT GetClipFormat() { return RegisterClipboardFormat("TRiAS.CS.1"); }
	static LPWSTR GetUserType() { return L"TRiASCoordSystem"; }
	static LPCWSTR GetSubStreamName() { return L"TRiAS_CoordSystem"; }
	static LPCWSTR GetFileExt() { return L"*.tcs"; }

	HRESULT SavePropertySet(IStorage *pIStg, DWORD rgMode);
};

#endif // !defined(_TRIASCOORDSYSTEM_H__E69F9BA2_A213_437D_B00E_786C2C69741D__INCLUDED_)
