// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 16.09.99 18:18:44 
//
// @doc
// @module KoppelTemplate.h | Declaration of the <c CKoppelTemplate> class

#if !defined(_KOPPELTEMPLATE_H__B24C2B87_E1C4_4B6A_A53B_523CDD20313C__INCLUDED_)
#define _KOPPELTEMPLATE_H__B24C2B87_E1C4_4B6A_A53B_523CDD20313C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

///////////////////////////////////////////////////////////////////////////////
// für SABIS-Kopplung notwendige Interfacedefinitionen
#import "tlb/SABIS_typelib.tlb" no_implementation raw_interfaces_only raw_dispinterfaces named_guids no_namespace \
	exclude("EnumFormTypes", "EnumGroupTypes", "EnumRegHKeyRoots", "ControlListStyles") \
	exclude("DataProjectOpenModes", "EnumUserRights", "EnumSystemMetrics", "CommonConstants") \
	exclude("EnumShowWindow", "TabbedDialogStyles", "EnumRegErrorReturn")
#import "tlb/AppLink.dll" no_implementation raw_interfaces_only raw_dispinterfaces named_guids no_namespace 


/////////////////////////////////////////////////////////////////////////////
// CMainApplication
class ATL_NO_VTABLE CMainApplication : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CMainApplication, &CLSID_KoppelTemplate>,
	public ISupportErrorInfo,
	public IDispatchImpl<IMainApplication, &IID_IMainApplication, &LIBID_SabisTemplate>,
	public IDispatchImpl<MainApplicationLink, &IID_MainApplicationLink, &LIBID_SABIS_CLASSES>,
	public IDispatchImpl<__DLLApplicationLinkTarget, &DIID___DLLApplicationLinkTarget, &LIBID_APPLink>
{
public:
	CMainApplication() :
		m_dwCookie(0L)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_KOPPELTEMPLATE)
	DECLARE_GET_CONTROLLING_UNKNOWN()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CMainApplication)
		COM_INTERFACE_ENTRY(IMainApplication)
		COM_INTERFACE_ENTRY2(IDispatch, MainApplicationLink)
		COM_INTERFACE_ENTRY(MainApplicationLink)
		COM_INTERFACE_ENTRY(__DLLApplicationLinkTarget)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

public:
// MainApplicationLink
	STDMETHOD(OpenProject)(implUserInfo * Info, BSTR ProjectFilename, GISLinkTarget * LinkClient, ApplicationLinkTarget **ppTarget);
	STDMETHOD(CloseProject)(VARIANT_BOOL DoAsk, VARIANT_BOOL CleanUp, VARIANT_BOOL *pfOk);

// __DLLApplicationLinkTarget
	STDMETHODIMP_(void) GetVisible(VARIANT_BOOL* Status);
	STDMETHODIMP_(void) LetVisible(VARIANT_BOOL DoShow);
	STDMETHODIMP_(void) ShowStatusText(BSTR AText);
	STDMETHODIMP_(void) OpenDataProject(implUserInfo* Info, BSTR ProjectFilename, VARIANT_BOOL* Done);
	STDMETHODIMP_(void) CloseDataProject(VARIANT_BOOL DoAsk, VARIANT_BOOL CleanUp, VARIANT_BOOL* Done);
	STDMETHODIMP_(void) ShowProjectInfo();
	STDMETHODIMP_(void) BreakGetData();
	STDMETHODIMP_(void) BreakSendData(BSTR Linkgroup);
	STDMETHODIMP_(void) GetMaxDataCount(BSTR Linkgroup, long* Selected);
	STDMETHODIMP_(void) GetData(BSTR Linkgroup, BSTR* AName, VARIANT_BOOL* Done);
	STDMETHODIMP_(void) AddToSendData(implUserInfo* Info, BSTR Linkgroup, BSTR LinkItem, VARIANT_BOOL* Done);
	STDMETHODIMP_(void) DoSendData(implUserInfo* Info, BSTR Linkgroup, BSTR Source);
	STDMETHODIMP_(void) OpenForm(implUserInfo* Info, BSTR Linkgroup, BSTR LinkItem, VARIANT OpenID, VARIANT_BOOL* Done);
	STDMETHODIMP_(void) CloseChilds(VARIANT Art, VARIANT_BOOL* Done);
	STDMETHODIMP_(void) OpenFormCount(VARIANT GrpArt, long* Anzahl);
	STDMETHODIMP_(void) RefreshForm(implUserInfo* Info, BSTR Linkgroup, BSTR LinkItem);
	STDMETHODIMP_(void) TestCurrentgroup(BSTR Linkgroup, VARIANT_BOOL* Ok);
	STDMETHODIMP_(void) GetCurrentLinkgroup(BSTR* Gruppe);
	STDMETHODIMP_(void) GetCurrentLinkgroupName(BSTR* Name);

protected:
	HRESULT Connect (_DLLApplicationLinkTarget *pTarget);
	HRESULT Disconnect (_DLLApplicationLinkTarget *pTarget);

	BOOL OpenData (BSTR ProjektName);

private:
	_DLLApplicationLinkTargetPtr m_SabisLink;
	DWORD m_dwCookie;
};

#endif // !defined(_KOPPELTEMPLATE_H__B24C2B87_E1C4_4B6A_A53B_523CDD20313C__INCLUDED_)
