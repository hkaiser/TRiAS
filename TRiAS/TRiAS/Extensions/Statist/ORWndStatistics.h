// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 16.09.2001 21:31:50 
//
// @doc
// @module ORWndStatistics.h | Declaration of the <c CORWndStatistics> class

#if !defined(_ORWNDSTATISTICS_H__8807421D_169F_4166_808B_B7A06A460290__INCLUDED_)
#define _ORWNDSTATISTICS_H__8807421D_169F_4166_808B_B7A06A460290__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "WaitingTreeCtrl.h"
#include "StatisticsImageIds.h"

///////////////////////////////////////////////////////////////////////////////
// CORWndStatistics: objektklassenbezogene Statistiken im ProjektValueContainer
class CORWndStatistics :
	public CWaitingTreeCtrl
{
public:
	CORWndStatistics() 
	{
		ShowWaitMessage();
		SetWaitMessage(NULL, ::LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_HOURGLASS)));
	}
	~CORWndStatistics() {}

	BOOL CALLBACK EnumORWnds (HWND hWnd, BOOL, UINT_PTR *pData);

///////////////////////////////////////////////////////////////////////////////
// Objekte, die an verschiedenen Items hängen, sind alle von CItemCallBack abgeleitet
	class CItemCallback
	{
	public:
		CItemCallback(HTREEITEM hItem) : m_hItem(hItem) {}
		virtual ~CItemCallback() {}
		virtual BOOL PopulateItem (CORWndStatistics *pTarget, HTREEITEM hParent) = 0;
		virtual BOOL WantsRefresh(HTREEITEM hItem) { return FALSE; }

	protected:
		HTREEITEM m_hItem;
	};

// CORWndItemCallback: Items, die an RechercheFenster im Baum hängen
	class CORWndItemCallback :
		public CItemCallback
	{
	public:
		CORWndItemCallback(HWND hWnd, HTREEITEM hItem) : 
			CItemCallback(hItem), m_hWnd(hWnd)
		{
		}
		~CORWndItemCallback() 
		{
		}

		BOOL PopulateItem (CORWndStatistics *pTarget, HTREEITEM hParent);
		BOOL CALLBACK EnumClasses(HOBJECTS lIdent, BOOL, void *pData);

	private:
		HWND m_hWnd;
	};

// CORWndObjectClassItemCallback: Items, die an Objektklassen im Baum hängen
	class CORWndObjectClassItemCallback :
		public CItemCallback
	{
	public:
		CORWndObjectClassItemCallback(HWND hWnd, HOBJECTS lIdent, HTREEITEM hItem) : 
			CItemCallback(hItem), m_hWnd(hWnd), m_lIdent(lIdent) 
		{
		}
		~CORWndObjectClassItemCallback() 
		{
		}

		BOOL PopulateItem (CORWndStatistics *pTarget, HTREEITEM hParent);

	private:
		HWND m_hWnd;
		HOBJECTS m_lIdent; 
	};

// CValueProviderCallback: Items, die unter einer Objektklasse hängen
	class CValueProviderCallback :
		public CItemCallback,
		public IValueProviderCallback 
	{
	public:
		CValueProviderCallback(CORWndStatistics *pTarget, 
				IValueProvider *pIProvider, HTREEITEM hItem) :
			CItemCallback(hItem), m_pTarget(pTarget), m_Provider(pIProvider)
		{
		} 
		~CValueProviderCallback() 
		{
		}

		BOOL PopulateItem (CORWndStatistics *pTarget, HTREEITEM hParent)
		{
			return TRUE;		// nothing to populate
		}

	// IValueProviderCallback
		STDMETHOD_(ULONG, AddRef)() {_ASSERTE(FALSE); return 0;}
		STDMETHOD_(ULONG, Release)(){_ASSERTE(FALSE); return 0;}
		STDMETHOD(QueryInterface)(REFIID iid, void **ppvObject)
			{_ASSERTE(FALSE); return E_NOINTERFACE;}
		STDMETHODIMP NeedsRefresh();

	protected:
		WValueProvider m_Provider;
		CORWndStatistics *m_pTarget;
	};

	class CValueProviderCallbackORWndClass :
		public CValueProviderCallback
	{
	public:
		CValueProviderCallbackORWndClass(CORWndStatistics *pTarget, HWND hWnd,
                HOBJECTS lIdent, IValueProvider *pIProvider, HTREEITEM hItem) 
		:	CValueProviderCallback(pTarget, pIProvider, hItem), 
            m_hWnd(hWnd), m_lIdent(lIdent)
		{
		} 
		~CValueProviderCallbackORWndClass() 
		{
		}

	protected:
        HWND m_hWnd;
		HOBJECTS m_lIdent;
	};

	class CValueProviderCallbackORWnd :
		public CValueProviderCallback
	{
	public:
		CValueProviderCallbackORWnd(CORWndStatistics *pTarget, HWND hWnd, 
				IValueProvider *pIProvider, HTREEITEM hItem) 
		:	CValueProviderCallback(pTarget, pIProvider, hItem), m_hWnd(hWnd)
		{
		} 
		~CValueProviderCallbackORWnd() 
		{
		}

	protected:
		HWND m_hWnd;
	};

public:
	BOOL PopulateItem(HTREEITEM hParent);	// wird für jedes zu öffnende Item gerufen
	void DeletingItem(HTREEITEM hItem);		// wird für jedes zu löschende Item gerufen

private:
	BOOL InitRoot();
};

#endif // !defined(_ORWNDSTATISTICS_H__8807421D_169F_4166_808B_B7A06A460290__INCLUDED_)
