// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 16.09.2001 21:31:50 
//
// @doc
// @module ObjectClassStatistics.h | Declaration of the <c CObjectClassStatistics> class

#if !defined(_OBJECTCLASSSTATISTICS_H__8807421D_169F_4166_808B_B7A06A460290__INCLUDED_)
#define _OBJECTCLASSSTATISTICS_H__8807421D_169F_4166_808B_B7A06A460290__INCLUDED_

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
// CObjectClassStatistics: objektklassenbezogene Statistiken im ProjektValueContainer
class CObjectClassStatistics :
	public CWaitingTreeCtrl
{
public:
	CObjectClassStatistics() 
	{
		ShowWaitMessage();
		SetWaitMessage(NULL, ::LoadIcon(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDI_HOURGLASS)));
	}
	~CObjectClassStatistics() {}

	BOOL CALLBACK EnumDataSources (HPROJECT hPr, BOOL, UINT_PTR *pData);

///////////////////////////////////////////////////////////////////////////////
// Objekte, die an verschiedenen Items hängen, sind alle von CItemCallBack abgeleitet
	class CItemCallback
	{
	public:
		CItemCallback(HTREEITEM hItem) : m_hItem(hItem) {}
		virtual ~CItemCallback() {}
		virtual BOOL PopulateItem (CObjectClassStatistics *pTarget, HTREEITEM hParent) = 0;
		virtual BOOL WantsRefresh(HTREEITEM hItem) { return FALSE; }

	protected:
		HTREEITEM m_hItem;
	};

// CDataSourceItemCallback: Items, die an DataSourceItem im Baum hängen
	class CDataSourceItemCallback :
		public CItemCallback
	{
	public:
		CDataSourceItemCallback(HPROJECT hPr, HTREEITEM hItem) : 
			CItemCallback(hItem), m_hPr(hPr) 
		{
		}
		~CDataSourceItemCallback() 
		{
		}

		BOOL PopulateItem (CObjectClassStatistics *pTarget, HTREEITEM hParent);
		BOOL CALLBACK EnumClasses(HOBJECTS lIdent, BOOL, void *pData);

	private:
		HPROJECT m_hPr; 
	};

// CObjectClassItemCallback: Items, die an Objektklassen im Baum hängen
	class CObjectClassItemCallback :
		public CItemCallback
	{
	public:
		CObjectClassItemCallback(HPROJECT hPr, HOBJECTS lIdent, HTREEITEM hItem) : 
			CItemCallback(hItem), m_hPr(hPr), m_lIdent(lIdent) 
		{
		}
		~CObjectClassItemCallback() 
		{
		}

		BOOL PopulateItem (CObjectClassStatistics *pTarget, HTREEITEM hParent);

	private:
		HPROJECT m_hPr;
		HOBJECTS m_lIdent; 
	};

// CValueProviderCallback: Items, die unter einer Objektklasse hängen
	class CValueProviderCallback :
		public CItemCallback,
		public IValueProviderCallback 
	{
	public:
		CValueProviderCallback(CObjectClassStatistics *pTarget, 
				IValueProvider *pIProvider, HTREEITEM hItem) :
			CItemCallback(hItem), m_pTarget(pTarget), m_Provider(pIProvider)
		{
		} 
		~CValueProviderCallback() 
		{
		}

		BOOL PopulateItem (CObjectClassStatistics *pTarget, HTREEITEM hParent)
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
		CObjectClassStatistics *m_pTarget;
	};

	class CValueProviderCallbackClass :
		public CValueProviderCallback
	{
	public:
		CValueProviderCallbackClass(CObjectClassStatistics *pTarget, HOBJECTS lIdent, 
				IValueProvider *pIProvider, HTREEITEM hItem) :
			CValueProviderCallback(pTarget, pIProvider, hItem), m_lIdent(lIdent)
		{
		} 
		~CValueProviderCallbackClass() 
		{
		}

	protected:
		HOBJECTS m_lIdent;
	};

	class CValueProviderCallbackDatasource :
		public CValueProviderCallback
	{
	public:
		CValueProviderCallbackDatasource(CObjectClassStatistics *pTarget, HPROJECT hPr, 
				IValueProvider *pIProvider, HTREEITEM hItem) :
			CValueProviderCallback(pTarget, pIProvider, hItem), m_hPr(hPr)
		{
		} 
		~CValueProviderCallbackDatasource() 
		{
		}

	protected:
		HPROJECT m_hPr;
	};

public:
	BOOL PopulateItem(HTREEITEM hParent);	// wird für jedes zu öffnende Item gerufen
	void DeletingItem(HTREEITEM hItem);		// wird für jedes zu löschende Item gerufen

private:
	BOOL InitRoot();
};

///////////////////////////////////////////////////////////////////////////////
// ItemIds in Imagelist
#define OVL_PUBLISH							1		// publish overlay

#define IMG_NOICON							0
#define IMG_PUBLISH							1

#define IMG_DATASOURCE						18		// allgemeine Datenquelle
#define IMG_DATASOURCE_TRiAS1				19		// .stb
#define IMG_DATASOURCE_TRiAS2				20		// V2.0 .ris
#define IMG_DATASOURCE_TRiAS3				21		// V3.0 .ris
#define IMG_DATASOURCE_TRiAS_EMBEDDED		22		// V3.0 embedded in .riw
#define IMG_DATASOURCE_ARCVIEW				23		// ArcView
#define IMG_DATASOURCE_MAPINFO				24		// MapInfo
#define IMG_DATASOURCE_OLEDB				25		// OleDb
#define IMG_DATASOURCE_POLYGIS				26		// PolyGIS
#define IMG_DATASOURCE_GDO					27		// Geomedia GDO
#define IMG_DATASOURCE_MEMDB				28		// FastDB

#define IMG_WORKSPACE						29		// Workspace

#define IMG_STATFUNC_TAB					30
#define IMG_STATFUNC						31
#define IMG_STATFUNC_CLASS					32		// StatFunc für Objektklassen
#define IMG_STATFUNC_CUM					33		// kumulative StatFunc
#define IMG_STATFUNC_CLASS_CUM				34		// kumulative StatFunc für Objektklassen

#define IMG_STATFUNC_ORWND					35		// StatFunc für Objektrecherchfenster

#define IMG_STATFUNC_OBJECT					36		// StatFunc für Objekte
#define IMG_STATFUNC_OBJECT_CUM				37		// kumulative StatFunc für Objekte
#define IMG_STATFUNC_POINT					38		// StatFunc für Punkte
#define IMG_STATFUNC_LINE					39		// StatFunc für Linien
#define IMG_STATFUNC_AREA					40		// StatFunc für Flächen
#define IMG_STATFUNC_TEXT					41		// StatFunc für Texte

///////////////////////////////////////////////////////////////////////////////
// Column numbers
#define NAME_COLUMN							0
#define VALUE_COLUMN						1

#endif // !defined(_OBJECTCLASSSTATISTICS_H__8807421D_169F_4166_808B_B7A06A460290__INCLUDED_)
