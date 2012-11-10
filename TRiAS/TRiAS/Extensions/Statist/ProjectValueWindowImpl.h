// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 28.08.2001 22:19:15 
//
// @doc
// @module ProjectValueWindowImpl.h | Declaration of the <c CProjectValueWindowImpl> class

#if !defined(_PROJECTVALUEWINDOWIMPL_H__63407741_4530_4F77_831A_7EA0D7D59E10__INCLUDED_)
#define _PROJECTVALUEWINDOWIMPL_H__63407741_4530_4F77_831A_7EA0D7D59E10__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__)
#endif

#if defined(_USE_PROJECTVALUES)

#include <Atl/Ciid.h>
#include "DialogView.h"
#include "Categories.h"

///////////////////////////////////////////////////////////////////////////////
// CProjectValueWindowImpl
class CStatist;		// forward decl only 

class CProjectValueWindowImpl :
	public CDialogView<CProjectValueWindowImpl, CAxDialogImpl<CProjectValueWindowImpl> >,
	public CDialogResize<CProjectValueWindowImpl>
{
public:
	enum { IDD = IDD_PROJECTVALUES };

	CProjectValueWindowImpl() :
		m_hIcon(NULL), m_iCurrItem(CB_ERR)
	{
	}
	~CProjectValueWindowImpl() 
	{
	}

	static HRESULT RegisterTabWindow(CStatist *pXtsn);

	static CProjectValueWindowImpl *CreateInstance(CStatist *pXtsn);
	bool ReShow(CStatist *pXtsn);
	static void DeleteInstance(CStatist *pXtsn, CProjectValueWindowImpl *& pValues);

	typedef CDialogView<CProjectValueWindowImpl, CAxDialogImpl<CProjectValueWindowImpl> > dialogbase_t;

	BEGIN_MSG_MAP_EX(CProjectValueWindowImpl)
		CHAIN_MSG_MAP(dialogbase_t)
		CHAIN_MSG_MAP(CDialogResize<CProjectValueWindowImpl>)
		MSG_WM_INITDIALOG(OnInitDialog)
		NOTIFY_HANDLER_EX(IDC_CATEGORIES, CBEN_DELETEITEM, OnItemDeleted)
		COMMAND_HANDLER_EX(IDC_CATEGORIES, CBN_SELCHANGE, OnItemSelected)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	BEGIN_DLGRESIZE_MAP(CProjectValueWindowImpl)
		DLGRESIZE_CONTROL(IDC_CATEGORIES, DLSZ_SIZE_X)
		DLGRESIZE_CONTROL(IDC_VALUES, DLSZ_SIZE_X|DLSZ_SIZE_Y)
		DLGRESIZE_CONTROL(IDC_NOMODULES, DLSZ_SIZE_X)
	END_DLGRESIZE_MAP()

	LRESULT OnInitDialog(HWND /*hWnd*/, LPARAM /*lParam*/);
	LRESULT OnItemDeleted(LPNMHDR pNmHdr);
	void OnItemSelected(UINT uiCode, int iItemId, HWND hCtrl);

	CComVariant GetIcon() 
	{ 
		EnsureIcon();
		return CComVariant(reinterpret_cast<INT_PTR>(m_hIcon), VT_I4); 
	}

// globaler (gecachter) enumerator für GUID's der Container für Statistische Kenngrößen
	class CEnumGuids
		: public NEnumGUID
	{
	public:
		CEnumGuids() : m_fIsInitialized(false) {}
		~CEnumGuids() {}

		HRESULT InitGuids (REFGUID rGuid, bool fForce = false);
		bool IsValid() { return m_fIsInitialized; }

		void RemoveActiveItem()
		{
		iterator itprev = m_itcur;

			--itprev;
			m_data.erase(itprev);		// aktuelles Item nicht mehr enumerieren
		}
		
	private:
		bool m_fIsInitialized;
	};
	static CEnumGuids s_StatValueContGUIDs;

// Elemente, die in der der eingebundenen ComboBoxEx hängen
	class CProjectCategory
	{
	public:
		CProjectCategory(REFGUID rGuid, LPCSTR pcName, UINT uiBmp, UINT uiId) :
			m_Guid(rGuid), m_strName(pcName), m_uiBmp(uiBmp), 
			m_hWnd(NULL), m_uiOrgId(uiId)
		{
		}
		~CProjectCategory() 
		{
			DestroyControl();
		}

		UINT GetImageId() { return m_uiBmp; }
		UINT GetSelectedImageId() { return m_uiBmp; }
		LPCSTR GetText() { return m_strName.c_str(); }

		HRESULT ShowControl(HWND hWndParent, CRect rcPos);
		HRESULT HideControl();

	protected:
		void DestroyControl()
		{
			if (NULL != m_hWnd) {
				_ASSERTE(::IsWindow(m_hWnd));
				::DestroyWindow(m_hWnd);
				m_hWnd = NULL;
			}
		}

	private:
		os_string m_strName;
		UINT m_uiBmp;
		CIID m_Guid;
		HWND m_hWnd;		// Wrapperfenster des Controls
		UINT m_uiOrgId;		// ursprünglicher ChildId dieses Fensters
	};

protected:
	bool EnsureIcon();

private:
	HICON m_hIcon;
	CCategories m_ValueConts;
	int m_iCurrItem;
	CImageList m_ValueContBmps;
};

///////////////////////////////////////////////////////////////////////////////
// Index in ImageList
#define PROJECTVALUE_DEFAULT	27

#endif // defined(_USE_PROJECTVALUES)

#endif // !defined(_PROJECTVALUEWINDOWIMPL_H__63407741_4530_4F77_831A_7EA0D7D59E10__INCLUDED_)
