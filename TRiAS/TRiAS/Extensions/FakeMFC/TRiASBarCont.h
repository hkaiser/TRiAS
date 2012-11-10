// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.03.2001 13:40:57 
//
// @doc
// @module TRiASBarCont.h | Declaration of the <c CTRiASBarCont> class

#if !defined(_TRIASBARCONT_H__3C4C4219_DFAD_4E5A_96C8_47898DC24948__INCLUDED_)
#define _TRIASBARCONT_H__3C4C4219_DFAD_4E5A_96C8_47898DC24948__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(_USE_DOCKEDTABWINDOW)
#include <ospace/std/map>
#include <SidManageTabs.h>
#include <Com/GuidHelpers.h>

#include "ManageTabWindow.h"

#define SERVICE_ENTRY_CHAIN_LOC(x) \
		if (SUCCEEDED(x.QueryService(guidService, riid, ppvObject))) \
			return S_OK;

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ManageTabWindows)

///////////////////////////////////////////////////////////////////////////////
// Klasse, die alle derzeit erzeugten TabWindows enthält und über QueryService
// die Aufrufe verteilt
class CMainFrame;
class CTRiASBarCont;

class CManageTabWindowsCont
{
public:
	CManageTabWindowsCont(CTRiASBarCont *pBack) : m_pBack(pBack) {}
	~CManageTabWindowsCont() {}

	HRESULT AddTabWindow(REFGUID guidSid, IManageTabWindows **ppINewTab = NULL);
	HRESULT QueryService (REFGUID guidSid, REFIID riid, void **ppvObject)
	{
		CManageTabWindowsMap::iterator it = m_TabWnds.find(guidSid);
		if (it != m_TabWnds.end())
			return (*it).second -> QueryInterface(riid, ppvObject);

		WManageTabWindows tab;
		RETURN_FAILED_HRESULT(AddTabWindow(guidSid, tab.ppi()));

		_ASSERTE(tab.IsValid());
		return tab -> QueryInterface(riid, ppvObject);
	}
	void ClearAll()
	{
		m_TabWnds.erase();
	}
	HRESULT SetFrame (CMainFrame *pFrame);

private:
	typedef map<GUID, WManageTabWindows, less<GUID> > CManageTabWindowsMap;
	CManageTabWindowsMap m_TabWnds;
	CTRiASBarCont *m_pBack;
};

#endif // defined(_USE_DOCKEDTABWINDOW)

///////////////////////////////////////////////////////////////////////////////
// CTRiASBarCont

class CTRiASBarCont : 
	public ITRiASBarContainer,
	public CComDualImpl<DControlToolBars, &IID_DControlToolBars, &LIBID_ToolBarLib, 
				TOOLBAR_TYPELIB_VERSION_MAJOR, TOOLBAR_TYPELIB_VERSION_MINOR>,
	public CComISupportErrorInfoImpl<&IID_DControlToolBars>,
#if defined(_USE_DOCKEDTABWINDOW)
	public IServiceProviderImpl<CTRiASBarCont>,
#endif // defined(_USE_DOCKEDTABWINDOW)
	public CComObjectRoot
{
public:
	CTRiASBarCont() 
#if defined(_USE_DOCKEDTABWINDOW)
		: m_TabWnds(this) 
#endif // defined(_USE_DOCKEDTABWINDOW)
	{
	}
	~CTRiASBarCont() {}

	BEGIN_COM_MAP(CTRiASBarCont)
		COM_INTERFACE_ENTRY(ITRiASBarContainer)
		COM_INTERFACE_ENTRY(DControlToolBars)
		COM_INTERFACE_ENTRY_IID(IID_DTRiASCollection, DControlToolBars)
		COM_INTERFACE_ENTRY_IID(IID_DTRiASBaseClass, DControlToolBars)
		COM_INTERFACE_ENTRY_IID(IID_IDispatch, DControlToolBars)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
#if defined(_USE_DOCKEDTABWINDOW)
		COM_INTERFACE_ENTRY(IServiceProvider)
#endif // defined(_USE_DOCKEDTABWINDOW)
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CTRiASBarCont)

#if defined(_USE_DOCKEDTABWINDOW)
	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct()
	{
		VERIFY(SUCCEEDED(m_TabWnds.AddTabWindow(SID_ManageProjectTabs)));
		VERIFY(SUCCEEDED(m_TabWnds.AddTabWindow(SID_ManageOverviewTabs)));
		return CComObjectRootEx<_ThreadModel>::FinalConstruct();
	}
	void FinalRelease()
	{
		m_TabWnds.ClearAll();
	}

	BEGIN_SERVICE_MAP(CTRiASBarCont)
		SERVICE_ENTRY_CHAIN_LOC(m_TabWnds)
		SERVICE_ENTRY_CHAIN(g_pTE -> m_pXtnSite)
	END_SERVICE_MAP()
#endif // defined(_USE_DOCKEDTABWINDOW)

public:
// *** ITRiASBarContainer specific functions ***
	STDMETHOD(EnumTRiASBars) (THIS_ IEnumITRiASBar **ppEnum);
	STDMETHOD(FindTRiASBar) (THIS_ LPCSTR pcName, ITRiASBar **pIBar);
	STDMETHOD(AddTRiASBar) (THIS_ LPCSTR pcName, DWORD dwStyle, DWORD dwStyleEx, ITRiASBar **ppITools);
	STDMETHOD(DeleteTRiASBar) (THIS_ LPCSTR pcName);

// *** DControlToolBars specific functions
	STDMETHOD(get_isA)(THIS_ LONG *plRTTI);					// ObjektTyp (RTTI)
	STDMETHOD(get_Parent)(THIS_ IDispatch **ppIBase);		// übergeordnetes Objekt
	STDMETHOD(put_Parent)(THIS_ IDispatch *pIBase);
	STDMETHOD(get_Application)(THIS_ IDispatch **ppIApp);	// Anwendung
	STDMETHOD(put_Application)(THIS_ IDispatch *pIApp);

	STDMETHOD(get_Count)(THIS_ LONG *plCnt);
	STDMETHOD(Item)(THIS_ VARIANT vItem, IDispatch **ppIDisp);
	STDMETHOD(_NewEnum)(THIS_ IUnknown **pvEnum);
	STDMETHOD(Add)(THIS_ VARIANT vAdd, IDispatch **ppIDisp);
	STDMETHOD(Remove)(THIS_ VARIANT vRemove);
	STDMETHOD(Refresh)(THIS);

	STDMETHOD(SaveState)(THIS_ VARIANT vKey, VARIANT vProject);
	STDMETHOD(LoadState)(THIS_ VARIANT vKey, VARIANT vProject);

private:
	class CMainFrame *m_pFrame;

#if defined(_USE_DOCKEDTABWINDOW)
	friend CManageTabWindowsCont;
	CManageTabWindowsCont m_TabWnds;

	HRESULT InitDockingTab (IManageTabWindows *pIManage, CDockingTabFrame *pDockingTab);
#endif // defined(_USE_DOCKEDTABWINDOW)

protected:
	CComPtr<IDispatch> m_Parent;	// für Einbindung in OleAutomation
	CComPtr<IDispatch> m_App;

public:
	HRESULT SetFrame (CMainFrame *pFrame); 
};

///////////////////////////////////////////////////////////////////////////////
// _NewEnum-Enumerator

class CToolBarNewEnum :
	public IEnumVARIANT,
	public CComObjectRoot
{
public:
	CToolBarNewEnum() {}
	~CToolBarNewEnum() {}

	BEGIN_COM_MAP(CToolBarNewEnum)
		COM_INTERFACE_ENTRY(IEnumVARIANT)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CToolBarNewEnum)

// *** IEnumVARIANT methods
	STDMETHOD(Next)(ULONG celt, VARIANT *rgvar, ULONG *pceltFetched);
	STDMETHOD(Skip)(ULONG celt);
	STDMETHOD(Reset)(void);
	STDMETHOD(Clone)(LPENUMVARIANT *ppenum);

// zusätzliche Member
	HRESULT FInit (CMainFrame *pFrame);		// Initialisierung
	HRESULT FInit (IEnumITRiASBar *pIEnum)
		{ m_Enum = pIEnum; return S_OK; }

private:
	WEnumITRiASBar m_Enum;
};

#endif // !defined(_TRIASBARCONT_H__3C4C4219_DFAD_4E5A_96C8_47898DC24948__INCLUDED_)
