// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.01.2000 21:54:53 
//
// @doc
// @module QueryDefExt.h | Declaration of the <c CQueryDefExtension> class

#if !defined(_QUERYDEF_H__1BF01AF5_33CF_11D3_94FA_0080C786297B__INCLUDED_)
#define _QUERYDEF_H__1BF01AF5_33CF_11D3_94FA_0080C786297B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASObjectHandleMap);
DefineSmartInterface(TRiASObjects);
DefineSmartInterface(TRiASObject);

/////////////////////////////////////////////////////////////////////////////
// CQueryDefExtension
class ATL_NO_VTABLE CQueryDefExtension : 
	public CComCoClass<CQueryDefExtension, &CLSID_QueryDefExt>,
	public CTriasExtension 
{
public:
	CQueryDefExtension()
	{
	}

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE_SINGLE(CQueryDefExtension, g_pTE)

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	BEGIN_COM_MAP(CQueryDefExtension)
		COM_INTERFACE_ENTRY(IUnknown)
		COM_INTERFACE_ENTRY_CHAIN(CTriasExtension)
	END_COM_MAP()

// ITriasXtension
public:
	STDMETHOD_(BOOL, InitExtension) (short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (void);
	STDMETHODIMP_(BOOL) MenuInit (HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHODIMP_(BOOL) MenuSelect (UINT uiMenuID, HMENU hMenu, HWND hWnd);
	STDMETHODIMP_(BOOL) MenuCommand (UINT uiMenuID, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);
	STDMETHOD_(LRESULT, WindowsNotification) (THIS_ UINT wMsg, WPARAM wParam, LPARAM lParam);

	ITRiASObjectHandleMap *GetObjectsMap(bool fAddRef = false) 
	{ 
		_ASSERTE(m_ObjsMap.IsValid());
		if (fAddRef)
			m_ObjsMap -> AddRef();
		return m_ObjsMap; 
	}
	ITRiASObjectHandleMap *GetObjectMap(bool fAddRef = false) 
	{ 
		_ASSERTE(m_ObjMap.IsValid());
		if (fAddRef)
			m_ObjMap -> AddRef();
		return m_ObjMap; 
	}

// Funktion für den Zugriff auf die ObjectMap von TRiASDB
	HRESULT GetObjectFromMap (long lTarget, WTRiASObject &rif)
	{
	WUnknown Unk;
	HRESULT hr = m_ObjMap -> GetObject (lTarget, Unk.ppi());

		if (SUCCEEDED(hr))
			rif = Unk;
		return hr;
	}

// Funktion für den Zugriff auf die ObjectsMap von TRiASDB
	HRESULT GetObjectsFromMap (long lTarget, WTRiASObjects &rif)
	{
	WUnknown Unk;
	HRESULT hr = m_ObjsMap -> GetObject (lTarget, Unk.ppi());

		if (SUCCEEDED(hr))
			rif = Unk;
		return hr;
	}

protected:
	bool FindMenuItem (HMENU hMenu, UINT uiID);

	HRESULT MakeObjectClass (HWND hWnd); 
	HRESULT DeleteFromClass (HWND hWnd); 
	bool HasPseudoObjects (HWND hWnd);

public:
#include "DexCommands.h"

	typedef LRESULT (CQueryDefExtension::*DEXMESSAGEPROC)(HPROJECT, LPARAM);

protected:
// DEX_... commandsupport
	bool InitJumpTable();
	void FreeJumpTable();

	DEXMESSAGEPROC *m_cbDexProcs;	// Sprungverteiler (DEX_...)

	unsigned int m_i1stDexProc;		// erste Funktion
	unsigned int m_iDexProcsNum;	// Anzahl der Funktionen in Tabelle

// Notification support
	BOOL OnObjectChanged (INT_PTR lONr);

public:
	BOOL IsObjectInClass (INT_PTR lIdent, INT_PTR lONr, INT_PTR *plONrMapped = NULL);
	LRESULT DeleteObjectFromClass (INT_PTR lIdent, INT_PTR lONr, BOOL fEnableUndo = FALSE);
	LRESULT GetObjectIdent (INT_PTR lONr);

private:
	WTRiASObjectHandleMap m_ObjsMap;
	WTRiASObjectHandleMap m_ObjMap;
};

#endif // !defined(_QUERYDEF_H__1BF01AF5_33CF_11D3_94FA_0080C786297B__INCLUDED_)
