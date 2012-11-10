// $Header: $
// Copyright© 1999-2004 Hartmut Kaiser, All rights reserved
// Created: 28.08.2001 22:25:48 
//
// @doc
// @module DialogView.h | Declaration of the <c CDialogView> class

#if !defined(_DIALOGVIEW_H__9259A1E3_88DE_4ECC_92FE_AE7CA9F0E710__INCLUDED_)
#define _DIALOGVIEW_H__9259A1E3_88DE_4ECC_92FE_AE7CA9F0E710__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// 
template<typename T, typename DlgT = CDialogImpl<T, TBase> >
class CDialogView : 
	public DlgT 
{
public:
	HWND m_hWndFocus;
	
	BEGIN_MSG_MAP_EX(CDialogView)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_KILLFOCUS(OnKillFocus)
		MSG_WM_SETFOCUS(OnSetFocus)
	END_MSG_MAP()
		
	LRESULT OnInitDialog(HWND /*hWnd*/, LPARAM /*lParam*/)
	{
		ATLASSERT(GetStyle() & WS_CHILD);
		ModifyStyle(WS_BORDER|WS_CAPTION, 0);
		ShowWindow(SW_NORMAL);
		SetMsgHandled(FALSE);
		return 0;
	}
	void OnKillFocus(HWND /*wParam*/)
	{
	HWND hWndFocus = ::GetFocus();
	
		if (NULL != hWndFocus && IsChild(hWndFocus)) 
			m_hWndFocus = hWndFocus;
	}
	void OnSetFocus(HWND /*wParam*/)
	{
	// Set focus to last known control
		if (!::IsWindow(m_hWndFocus) || !IsChild(m_hWndFocus)) 
			SetMsgHandled(FALSE);
		else
			::SetFocus(m_hWndFocus);
	}
	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
	HWND hWndFocus = ::GetFocus();
	
		if (NULL == hWndFocus || !IsChild(hWndFocus)) 
			return FALSE;
		if (NULL == GetWindow(GW_CHILD)) 
			return FALSE;      
		if (IsDialogMessage(pMsg)) 
			return TRUE;
		return FALSE;
	}
};

#endif // !defined(_DIALOGVIEW_H__9259A1E3_88DE_4ECC_92FE_AE7CA9F0E710__INCLUDED_)
