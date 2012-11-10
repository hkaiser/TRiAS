// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 01.03.2001 10:48:49 
//
// @doc
// @module DockingTabFrame.h | Declaration of the <c CDockingTabFrame> class

#if !defined(_DOCKINGTABFRAME_H__EF691C46_92E4_43F8_AC41_B65014828590__INCLUDED_)
#define _DOCKINGTABFRAME_H__EF691C46_92E4_43F8_AC41_B65014828590__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ot_dockingwindows.h>		// Objective Toolkit docking windows
#include <ot_tabwnd.h>				// Objective Toolkit tab windows
#include <ot_toolbar.h>				// Objective Toolkit toolbar/menubar

#include "Docking3dTab.h"

#if defined(_USE_PROJECTVALUES)
#include "ProjectValues.h"
#endif // defined(_USE_PROJECTVALUES)

/////////////////////////////////////////////////////////////////////////////
// CDockingTabFrame window

const UINT WM_ADDTAB = RegisterWindowMessage("WM_ADDTAB");
const UINT WM_REMOVETAB = RegisterWindowMessage("WM_REMOVETAB");

class CDockingTabFrame : public SECControlBar
{
    DECLARE_DYNCREATE(CDockingTabFrame)

// Construction
public:
	CDockingTabFrame();

// Attributes
public:

// Operations
public:
	HRESULT get_Visible (VARIANT_BOOL *pfVisible);
	HRESULT put_Visible (VARIANT_BOOL fVisible);
	HRESULT get_Count (int *pfCount);
	HRESULT get_ActiveTabWindow (INT_PTR *phHandle);
	HRESULT get_ParentWindow (INT_PTR *phHandle);
	HRESULT FindTabWindow (BSTR Name, INT_PTR *phHandle);
	HRESULT AddTabWindow (INT_PTR hWnd, BSTR Name, VARIANT vPict, INT_PTR *phHandle);
	HRESULT DeleteTabWindow (INT_PTR hHandle, BOOL fRemoveCallback);
	HRESULT ActivateTabWindow (INT_PTR hHandle);
	HRESULT AddTabWindowDelayed (BSTR bstrName, ITabWindowCallback *pICallback);
	HRESULT RenameTabWindow(BSTR bstrOldName, BSTR bstrNewName);
	HRESULT SetTabIcon (INT_PTR hHandle, VARIANT vIcon);

	virtual void OnBarFloat();
	virtual void OnBarDock();

	int GetCount() { return ::IsWindow(m_wndTab.GetSafeHwnd()) ? m_wndTab.GetTabCount() : 0; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockingTabFrame)
	//}}AFX_VIRTUAL
	virtual void OnExtendContextMenu(CMenu* pMenu);

	virtual BOOL OnProjectOpened() { return TRUE; }
	virtual BOOL OnProjectClosed() { return TRUE; }

protected:
	DECLARE_INTERFACE_MAP()
	BEGIN_INTERFACE_PART(ManageTabWindows, IManageTabWindows)
		STDMETHOD(GetTypeInfoCount)(UINT* pctinfo);
		STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo** pptinfo);
		STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgdispid);
		STDMETHOD(Invoke)(DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult, EXCEPINFO* pexcepinfo, UINT* puArgErr);

		STDMETHOD(get_Visible)(THIS_ VARIANT_BOOL *pfVisible);
		STDMETHOD(put_Visible)(THIS_ VARIANT_BOOL fVisible);
		STDMETHOD(get_Count)(THIS_ int *pfCount);
		STDMETHOD(get_ActiveTabWindow)(THIS_ INT_PTR *phHandle);
		STDMETHOD(get_ParentWindow)(THIS_ INT_PTR *phHandle);
		STDMETHOD(FindTabWindow) (THIS_ BSTR Name, INT_PTR *Handle);
		STDMETHOD(AddTabWindow) (THIS_ INT_PTR Wnd, BSTR Name, VARIANT vPict, INT_PTR *Handle);
		STDMETHOD(DeleteTabWindow) (THIS_ INT_PTR Handle);
		STDMETHOD(ActivateTabWindow) (THIS_ INT_PTR Handle);
		STDMETHOD(AddTabWindowDelayed) (THIS_ BSTR bstrName, ITabWindowCallback *pICallback);
		STDMETHOD(RenameTabWindow) (THIS_ BSTR bstrOldName, BSTR bstrNewName);
		STDMETHOD(SetTabIcon) (THIS_ INT_PTR hHandle, VARIANT vIcon);
		STDMETHOD(DeleteTabWindowDelayed) (THIS_ INT_PTR Handle);
	END_INTERFACE_PART(ManageTabWindows)

protected:
	CDocking3DTab m_wndTab;

// Implementation
public:
	virtual ~CDockingTabFrame();

	UINT GetNextTabID();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDockingTabFrame)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnAddTab (WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRemoveTab (WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	afx_msg void OnTabCommand(UINT nID);
};

#if !defined(_USE_PROJECTVALUES)
#define CDockingProjectTabFrame CDockingTabFrame
#else
/////////////////////////////////////////////////////////////////////////////
// DockingFrame für Legende/Projektstatistiken etc.
class CDockingProjectTabFrame :
	public CDockingTabFrame
{
public:
	CDockingProjectTabFrame();
	~CDockingProjectTabFrame();

public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockingProjectTabFrame)
	//}}AFX_VIRTUAL

	virtual BOOL OnProjectOpened();
	virtual BOOL OnProjectClosed();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDockingProjectTabFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CProjectValues *m_pPrjValues;
};
#endif // defined(_USE_PROJECTVALUES)

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_DOCKINGTABFRAME_H__EF691C46_92E4_43F8_AC41_B65014828590__INCLUDED_)
