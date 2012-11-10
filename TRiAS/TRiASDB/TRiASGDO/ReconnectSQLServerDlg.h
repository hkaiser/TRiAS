// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 24.10.2002 21:43:20 
//
// @doc
// @module ReconnectSQLServerDlg.h | Declaration of the <c CReconnectSQLServerDlg> class

#if !defined(_RECONNECTSQLSERVERDLG_H__FA7228F8_EC71_4E15_AC2B_D5824AC35243__INCLUDED_)
#define _RECONNECTSQLSERVERDLG_H__FA7228F8_EC71_4E15_AC2B_D5824AC35243__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include "Separator.h"

/////////////////////////////////////////////////////////////////////////////
// CReconnectSQLServerDlg
class CReconnectSQLServerDlg : 
	public CDialogImpl<CReconnectSQLServerDlg>
{
public:
	CReconnectSQLServerDlg()
	{
		m_fTrusted = true;
		m_fReadWrite = false;
		m_fServersFilled = false;
		m_fDatabasesFilled = false;
	}

	~CReconnectSQLServerDlg()
	{
	}

	enum { IDD = IDD_RECONNECTSQLSERVERDLG };

	BEGIN_MSG_MAP_EX(CReconnectSQLServerDlg)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_HANDLER_EX(IDOK, BN_CLICKED, OnOK)
		COMMAND_HANDLER_EX(IDCANCEL, BN_CLICKED, OnCancel)
		COMMAND_HANDLER_EX(IDC_AUTHENTICATE_DOMANE, BN_CLICKED, OnAuthDomane)
		COMMAND_HANDLER_EX(IDC_AUTHENTICATE_SQLSERVER, BN_CLICKED, OnAuthSQLServer)
		COMMAND_HANDLER_EX(IDC_SQLSERVERNAME, CBN_DROPDOWN, OnDropDownServers)
		COMMAND_HANDLER_EX(IDC_USERNAME, EN_CHANGE, OnUsernameChanged)
		COMMAND_HANDLER_EX(IDC_DATABASENAME, CBN_DROPDOWN, OnDropDownDatabases)
		COMMAND_HANDLER_EX(IDC_DATABASENAME, CBN_SELCHANGE, OnSelectDatabases)
	END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(HWND hFocus, LPARAM lParam);
	void OnOK(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnCancel(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnAuthDomane(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnAuthSQLServer(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnDropDownServers(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnUsernameChanged(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnDropDownDatabases(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnSelectDatabases(UINT wNotifyCode, int iCtrlId, HWND hCtrl);

protected:
	HRESULT FillSQLServerNames();
	HRESULT FillDatabases();

	void AdjustAuthMode(BOOL fAuthMode);
	void AdjustControls();

public:
	CString m_strName;
	CString m_strPath;

	CString m_strServer;
	CString m_strUser;
	CString m_strPwd;
	CString m_strDatabaseName;
	bool m_fReadWrite;
	bool m_fTrusted;

private:
	CStatic	m_ftReconnectPrompt;
	CSeparator m_ftServer;
	CComboBox m_cbSQLServers;
	CSeparator m_ftAuthenticate;
	CButton m_bttnDomane;
	CButton m_bttnSQLServer;
	CEdit m_sleUserName;
	CEdit m_slePassword;
	CSeparator m_ftDatabase;
	CComboBox m_cbDatabases;

	bool m_fServersFilled;
	bool m_fDatabasesFilled;
};

#endif // !defined(_RECONNECTSQLSERVERDLG_H__FA7228F8_EC71_4E15_AC2B_D5824AC35243__INCLUDED_)
