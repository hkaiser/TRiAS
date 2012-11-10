// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 10/15/1998 11:08:08 AM
//
// @doc
// @module EditObjProps.h | Description goes here

#if !defined(_EDITOBJPROPS_H__3460D3EA_62C9_11D2_9EDE_006008447800__INCLUDED_)
#define _EDITOBJPROPS_H__3460D3EA_62C9_11D2_9EDE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#import "tlb/TRiASUI.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASOptionDlg);
DefineSmartInterface(TRiASLockFeatureEx);

///////////////////////////////////////////////////////////////////////////////
// Map wird benötigt, um Baumstruktur zu erzeugen
inline int operator< (const CComBSTR &r1, const CComBSTR &r2)
{
	return (wcscmp (r1, r2) < 0) ? true : false;
}
inline int operator== (const CComBSTR &r1, const CComBSTR &r2)
{
	return (wcscmp (r1, r2) == 0) ? true : false;
}
typedef map<CComBSTR, ULONG, less<CComBSTR> > CItemMap;

/////////////////////////////////////////////////////////////////////////////
// Map hält Pictures für einen Eintrag (optimization aid)
typedef map<os_string, WUnknown, less<os_string> > CMapStringObject;

/////////////////////////////////////////////////////////////////////////////
// {3460D3ED-62C9-11D2-9EDE-006008447800}
extern "C" const IID __declspec(selectany) CLSID_EditObjProps = 
	{0x3460d3ed,0x62c9,0x11d2,{0x9e,0xde,0x00,0x60,0x08,0x44,0x78,0x00}};

/////////////////////////////////////////////////////////////////////////////
// CEditObjProps
class ATL_NO_VTABLE CEditObjProps : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CEditObjProps, &CLSID_EditObjProps>,
	public ISupportErrorInfo,
	public IDispatchImpl<ITRiASOptionDlgCallback, &IID_ITRiASOptionDlgCallback, &LIBID_TRIASUI,
		TRIASUI_TYPELIB_VERSION_MAJOR, TRIASUI_TYPELIB_VERSION_MINOR>
{
public:
	CEditObjProps() :
		m_pWnd(NULL), m_dwCookie(0L), m_lONr(0L)
	{
	}
	~CEditObjProps()
	{
		_ASSERTE(0L == m_dwCookie);
	}

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE(CEditObjProps)

	BEGIN_COM_MAP(CEditObjProps)
		COM_INTERFACE_ENTRY(ITRiASOptionDlgCallback)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASOptionDlgCallback
public:
	STDMETHOD(OnInitDialog)(ITRiASOptionDlg *pIDlg);
	STDMETHOD(OnGetDispInfoChildren)(ITRiASOptionDlg *pIDlg, ULONG ulItem, int *piChildren);
	STDMETHOD(OnGetDispInfoImage)(ITRiASOptionDlg *pIDlg, ULONG ulItem, IDispatch **ppIPict);
	STDMETHOD(OnGetDispInfoExpandedImage)(ITRiASOptionDlg *pIDlg, ULONG ulItem, IDispatch **ppIPict);
	STDMETHOD(OnGetDispInfoText)(ITRiASOptionDlg *pIDlg, ULONG ulItem, BSTR *pbstrText);
	STDMETHOD(OnQueryContextMenu)(ITRiASOptionDlg *pIDlg, ULONG ulItem, INT_PTR hMenu, UINT uiFirst, UINT uiLast, UINT *puiLastID);
	STDMETHOD(OnGetCommandString)(ITRiASOptionDlg *pIDlg, ULONG ulItem, UINT uiCmd, DWORD dwFlags, BSTR *pbstrDesc);
	STDMETHOD(OnInvokeCommand)(ITRiASOptionDlg *pIDlg, ULONG ulItem, INT_PTR hWnd, UINT uiCmd);
	STDMETHOD(OnOk)(ITRiASOptionDlg *pIDlg);
	STDMETHOD(OnCancel)(ITRiASOptionDlg *pIDlg);

// Initialisierung
	HRESULT Init (Window *pWnd, ITRiASOptionDlg *pIDlg, INT_PTR lONr)
	{
		if (!m_ilList.CreateList (IDB_HEADERSTRIP, 16, 5, RGB(255, 0, 255)))
			return E_UNEXPECTED;

		m_pWnd = pWnd;
		m_Dlg = pIDlg;
		m_lONr = lONr;

		_ASSERTE(m_Dlg.IsValid());
		_ASSERTE(0 == m_dwCookie);
		return pIDlg -> Advise (GetUnknown(), &m_dwCookie);
	}
	void ShutDown(VARIANT_BOOL fCommit)
	{
		OnResetReferenceObject(fCommit);		// Bezugsobjekt rücksetzen

		_ASSERTE(0 != m_dwCookie);
		m_Dlg -> Unadvise (m_dwCookie);
		m_dwCookie = 0L;
	}

// Properties
	Window *GetParentWnd() { return m_pWnd; }

// Helperklasse für Init/Shutdown
	class CDlgWrapper 
	{
	public:
		CDlgWrapper (CEditObjProps *pDlg, Window *pWnd, ITRiASOptionDlg *pIDlg, INT_PTR lONr)
			: m_pDlg(pDlg), m_fCommit(VARIANT_FALSE)
		{
			if (NULL != m_pDlg) 
				m_pDlg -> Init (pWnd, pIDlg, lONr);
		}
		~CDlgWrapper()
		{
			if (NULL != m_pDlg) 
				m_pDlg -> ShutDown(m_fCommit);
		}

		void SetCommit (VARIANT_BOOL fCommit) { m_fCommit = fCommit; }

	private:
		CEditObjProps *m_pDlg;
		VARIANT_BOOL m_fCommit;
	};

protected:
	HRESULT InsertItems(ITRiASOptionDlg *pIDlg);
	ULONG CalcSubGroupItem (ITRiASOptionDlg *pIDlg, ULONG hParent, const CComBSTR &bstrSubGroup);
	ULONG CalcParentItem (ITRiASOptionDlg *pIDlg, const CComBSTR &bstrGroup, CItemMap &rItems);

/////////////////////////////////////////////////////////////////////////////
// spezielle Funktionen für setzen/rücksetzen des Bezugsobjektes
	class CSetReference 
	{
	public:
		CSetReference (LONG lONr) : m_hObj(INT_PTR(lONr))
		{
		}
		bool operator() (CMapStringObject::value_type cur)
		{
			_ASSERTE(NULL != m_hObj);
			return SUCCEEDED(WTRiASLockFeatureEx(cur.second) -> LockFeature(m_hObj));
		}

	private:
		INT_PTR m_hObj;
	};

	HRESULT OnNewReferenceObject()
	{
		COM_TRY {
			for_each (m_Entries.begin(), m_Entries.end(), CSetReference(m_lONr)); 
		} COM_CATCH;
		return S_OK;
	}

	class CResetReference 
	{
	public:
		CResetReference (LONG lONr, VARIANT_BOOL fCommit) : 
			m_fCommit(fCommit), m_hObj(INT_PTR(lONr)) 
		{
		}

		bool operator() (CMapStringObject::value_type cur)
		{
			return SUCCEEDED(WTRiASLockFeatureEx(cur.second) -> UnlockFeature(m_hObj, m_fCommit));
		}

	private:
		VARIANT_BOOL m_fCommit;
		INT_PTR m_hObj;
	};

	HRESULT OnResetReferenceObject(VARIANT_BOOL fCommit)
	{
		COM_TRY {
			for_each (m_Entries.begin(), m_Entries.end(), CResetReference(m_lONr, fCommit)); 
		} COM_CATCH;
		return S_OK;
	}

public:
	void SetLastName(LPCSTR pcLastName) { m_strLastName = pcLastName; }
	LPCSTR GetLastName() { return m_strLastName.c_str(); }
	HRESULT GetObjPropName(ITRiASOptionDlg *pIDlg, ULONG ulItem, os_string &rStrFull);

protected:
/////////////////////////////////////////////////////////////////////////////
// Map hält Zuordnung von MenuCmd's zu Items und Funktionen
	typedef HRESULT (CEditObjProps::*EDITOBJPROPACTION)(HWND hWnd, ITRiASOptionDlg *pIDlg, ULONG ulItem);
	typedef map<UINT, EDITOBJPROPACTION, less<UINT> > CMapCmdAction;

// MenuBefehle abarbeiten
	HRESULT AddObjProp (HWND hWnd, ITRiASOptionDlg *pIDlg, ULONG ulItem);
	HRESULT DeleteObjProp (HWND hWnd, ITRiASOptionDlg *pIDlg, ULONG ulItem);

private:
	CImageList m_ilList;

// Zuordnung des Bildchens zu einem Eintrag
//	CMapStringObject m_PropMap;		// nicht expandierter Zustand
//	CMapStringObject m_PropMapExp;	// expandierter Zustand

	CMapStringObject m_Entries;		// Liste aller Einträge 
	CMapCmdAction m_Actions;		// Liste der Zuordnungen der MenuID's zu den zugehörigen Funktionen

	Window *m_pWnd;
	WTRiASOptionDlg m_Dlg;
	DWORD m_dwCookie;
	INT_PTR m_lONr;

	os_string m_strLastName;
};

#endif // !defined(_EDITOBJPROPS_H__3460D3EA_62C9_11D2_9EDE_006008447800__INCLUDED_)
