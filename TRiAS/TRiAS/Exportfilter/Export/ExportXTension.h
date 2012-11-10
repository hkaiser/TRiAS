// @doc 
// @module Export.h | Declaration of the <c CExportXtension> class

#if !defined(_EXPORT_H__BD1B0ED5_FFAF_11D2_94C3_0080C786297B__INCLUDED_)
#define _EXPORT_H__BD1B0ED5_FFAF_11D2_94C3_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#pragma HDR_ON()

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CExportXtension
class ATL_NO_VTABLE CExportXtension
	: public CComCoClass<CExportXtension, &CLSID_ExportXTension>
	, public IDispatchImpl<ITRiASExportXTension, &IID_ITRiASExportXTension, &LIBID_ExportXTension>
	, public CTriasExtension 
	, public CErrSupport<CExportXtension, &IID_ITRiASExportXTension>
{
	UINT	m_iMainMenu;
	UINT	m_iORMenu;
	BOOL	m_bHaveXML;
	BOOL	m_bHaveEngines;
public:
	CExportXtension() 
		: m_iMainMenu(0)
		, m_iORMenu(0)
		, m_bHaveXML(TRUE)
		, m_bHaveEngines(TRUE)
	{
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_EXPORTXTENSION)
	DECLARE_NOT_AGGREGATABLE_SINGLE(CExportXtension, g_pTE)
#if _TRiAS_VER < 0x0400
	DECLARE_CLASSFACTORY2(CVerifyExportLicense)
#endif // _TRiAS_VER < 0x0400

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CExportXtension)
		COM_INTERFACE_ENTRY(ITRiASExportXTension)
		COM_INTERFACE_ENTRY_CHAIN(CTriasExtension)
	END_COM_MAP()

// ITriasXtension
public:
	STDMETHOD_(BOOL, InitExtension) (short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (void);

// Menuhandling
	STDMETHOD_(BOOL, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuSelect) (THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd);

	HRESULT OnExportData( bool bMainData );
};

#pragma HDR_OFF()

#endif // !defined(_EXPORT_H__BD1B0ED5_FFAF_11D2_94C3_0080C786297B__INCLUDED_)
