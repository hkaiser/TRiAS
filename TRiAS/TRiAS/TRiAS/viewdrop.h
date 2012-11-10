// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 23.09.2000 22:19:40 
//
// @doc
// @module viewdrop.h | Declaration of the <c CViewDropTarget> class

#if !defined(_VIEWDROP_H__22AF2A1E_9E6A_4DA5_9BCF_A06590308005__INCLUDED_)
#define _VIEWDROP_H__22AF2A1E_9E6A_4DA5_9BCF_A06590308005__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "DragDropCallback.h"

///////////////////////////////////////////////////////////////////////////////
// Scroll-Parameter
extern DWORD g_dwScrollInset;
extern DWORD g_dwScrollDelay;

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(DataObject);

class CViewDropTarget :
	public IDropTarget,
	public CComObjectRoot
{
private:
	CDragDropCallback *m_pBack;
	Window *m_pWnd;
	WDataObject m_DataSource;

	UINT m_uiLastTest;

	UINT m_uiVertScroll;
	UINT m_uiHorzScroll;
	DWORD m_dwLastTime;

public:
	BEGIN_COM_MAP(CViewDropTarget)
		COM_INTERFACE_ENTRY(IDropTarget)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CViewDropTarget)		// class factory

		CViewDropTarget(void);
		~CViewDropTarget(void);

	bool FInit (CDragDropCallback *pBack, Window *pWnd);

// *** IDropTarget interface members
	STDMETHODIMP DragEnter (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffekt);
	STDMETHODIMP DragOver (DWORD grfKeyState, POINTL pt, DWORD *pdwEffekt);
	STDMETHODIMP DragLeave (void);
	STDMETHODIMP Drop (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffekt);

// sonstige ZugriffsFunktionen
	void SetHorzScrollCode (UINT uiCode) { m_uiHorzScroll = uiCode; }
	void SetVertScrollCode (UINT uiCode) { m_uiVertScroll = uiCode; }
	UINT GetHorzScrollCode (void) { return m_uiHorzScroll; }
	UINT GetVertScrollCode (void) { return m_uiVertScroll; }

	void SetLastTest (UINT uiTest) { m_uiLastTest = uiTest; }
	UINT GetLastTest (void) { return m_uiLastTest; }

	void SetLastTime (DWORD dwTime) { m_dwLastTime = dwTime; }
	void ResetLastTime (void) { m_dwLastTime = 0L; }
	DWORD GetLastTime (void) { return m_dwLastTime; }

	DWORD GetScrollDelay (void) { return g_dwScrollDelay; }
};

#endif // !defined(_VIEWDROP_H__22AF2A1E_9E6A_4DA5_9BCF_A06590308005__INCLUDED_)
