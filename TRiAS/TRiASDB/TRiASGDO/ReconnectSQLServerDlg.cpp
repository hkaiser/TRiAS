// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 24.10.2002 21:59:25 
//
// @doc
// @module ReconnectSQLServerDlg.cpp | Definition of the <c CReconnectSQLServerDlg> class

#include "stdafx.h"
#include "TRiASGDOImpl.h"

#include <sqldmo.h>
#include <sqldmoid.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "SQLServerUtils.h"
#include "ReconnectSQLServerDlg.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterfaceEx(SQLDMOApplication);
DefineSmartInterfaceEx(SQLDMODatabases);
DefineSmartInterfaceEx(SQLDMODatabase);
DefineSmartInterfaceEx(SQLDMONameList);

/////////////////////////////////////////////////////////////////////////////
// CReconnectSQLServerDlg

void CReconnectSQLServerDlg::AdjustAuthMode(BOOL fAuthMode)
{
	if (fAuthMode) {
	// NT Domänenanmeldung
		m_bttnDomane.SetCheck(1);
		m_bttnSQLServer.SetCheck(0);
		m_sleUserName.EnableWindow(FALSE);
		m_slePassword.EnableWindow(FALSE);
	}
	else {
	// SQLServeranmeldung
		m_bttnDomane.SetCheck(0);
		m_bttnSQLServer.SetCheck(1);
		m_sleUserName.EnableWindow(TRUE);
		m_slePassword.EnableWindow(TRUE);
	}
	m_fTrusted = fAuthMode;
}

// Implementation of AdjustControls
void CReconnectSQLServerDlg::AdjustControls()
{
int iServer = m_cbSQLServers.GetCurSel();
int iDatabase = -1;

	if (iServer >= 0) {
		m_cbDatabases.EnableWindow(TRUE);
		iDatabase = m_cbDatabases.GetCurSel();
	}
	else {
		m_cbDatabases.SetCurSel(-1);
		m_cbDatabases.EnableWindow(FALSE);
	}

CButton bttnOK(GetDlgItem(IDOK));

	if (iServer >= 0 && iDatabase >= 0 &&
		(m_bttnDomane.GetCheck() || 
			(m_bttnSQLServer.GetCheck() && m_sleUserName.GetWindowTextLength() > 0)
		)
	)
	{
		bttnOK.EnableWindow(TRUE);
	}
	else {
		bttnOK.EnableWindow(FALSE);
	}

}

HRESULT CReconnectSQLServerDlg::FillSQLServerNames()
{
	COM_TRY {
	int iLocalIndex = -1;
	int iOrigIndex = -1;

		for (int i = m_cbSQLServers.GetCount()-1; i >= 0; --i)
			m_cbSQLServers.DeleteString(i);

		{
		CWaitCursor wait;
		WSQLDMOApplication SQLDMOApp (CLSID_SQLDMOApplication);
		WSQLDMONameList SQLServers;

			THROW_FAILED_HRESULT(SQLDMOApp->ListAvailableSQLServers(SQLServers.ppi()));

		long lCount = 0;

			USES_CONVERSION;
			THROW_FAILED_HRESULT(SQLServers->GetCount(&lCount));
			for (long i = 0; i < lCount; ++i) {
			CComBSTR bstrName;

				if (FAILED(SQLServers->GetItemByOrd(i, CLEARED(bstrName))))
					continue;
			
			int iIndex = m_cbSQLServers.AddString(OLE2A(bstrName));
			
				if (bstrName[0] == L'(')	// '(local)'
					iLocalIndex = iIndex;
				else if (bstrName == m_strServer)
					iOrigIndex = iIndex;
			}
		}

		if (-1 != iOrigIndex)
			m_cbSQLServers.SetCurSel(iOrigIndex);
		else if (-1 != iLocalIndex)
			m_cbSQLServers.SetCurSel(iLocalIndex);
		else if (m_cbSQLServers.GetCount() > 0)
			m_cbSQLServers.SetCurSel(0);
		else {
		// keine SQL-Server verfügbar
		CString strMsg;
		CString strCap;

			strMsg.LoadString(m_fReadWrite ? IDS_SQLSERVER_RW : IDS_SQLSERVER_RO);
			strCap.Format("%s: %s", (LPCTSTR)strMsg, g_cbTRiAS);
			strMsg.LoadString(IDS_NOAVAIL_SQLSERVERS);
			MessageBox(strMsg, strCap, MB_OK|MB_ICONEXCLAMATION);
			return E_FAIL;
		}

	} 
	COM_CATCH_EX(e) {
	// ggf. Fehlermeldung ausgeben
		if (_COM_ERROR(e) == REGDB_E_CLASSNOTREG) {
		// SQLDMO nicht installiert
		CString strMsg;
		CString strCap;

			strMsg.Format(m_fReadWrite ? IDS_SQLSERVER_RW : IDS_SQLSERVER_RO);
			strCap.Format("%s: %s", (LPCTSTR)strMsg, g_cbTRiAS);
			strMsg.Format(IDS_SQLDMO_NOTINSTALLED, g_cbTRiAS);
			MessageBox(strMsg, strCap, MB_OK|MB_ICONEXCLAMATION);
			return E_FAIL;
		}
		COM_ASSERT_EX(e);
	}
	return S_OK;
}

namespace {
// disconnect am Ende sicherstellen
	struct CDisconnectGuard :
		public WSQLDMOServer
	{
		~CDisconnectGuard() { static_cast<ISQLDMOServer *>(*this)->DisConnect(); }
	};
}

HRESULT CReconnectSQLServerDlg::FillDatabases()
{
// SQL-Server -Instanz
CDisconnectGuard Server;

	COM_TRY {
	CWaitCursor wait;

		THROW_FAILED_HRESULT(GetSQLServer(CComBSTR(m_strServer), 
			CComBSTR(m_strUser), CComBSTR(m_strPwd), 0 != m_bttnDomane.GetState(),
			Server.ppi()));

	// ComboBox füllen
	WSQLDMODatabases SQLServerDBs;
	long lCount = 0;

		for (int k = m_cbDatabases.GetCount()-1; k >= 0; --k)
			m_cbDatabases.DeleteString(k);

		THROW_FAILED_HRESULT(Server->GetDatabases(SQLServerDBs.ppi()));
		THROW_FAILED_HRESULT(SQLServerDBs->GetCount(&lCount));
		for (long i = 0; i < lCount; ++i) {
		WSQLDMODatabase SQLServerDB;

			if (FAILED(SQLServerDBs->GetItemByOrd(i, SQLServerDB.ppi())))
				continue;

		SQLDMO_DBUSERPROFILE_TYPE rgRights = SQLDMODbUserProf_None;

			if (FAILED(SQLServerDB -> GetUserProfile(&rgRights)) ||
				SQLDMODbUserProf_InvalidLogin & rgRights)
			{
				continue;	// Fehler oder keine Rechte
			}

		CComBSTR bstrName;

			THROW_FAILED_HRESULT(SQLServerDB->GetName(CLEARED(bstrName)));
			m_cbDatabases.AddString(CString(bstrName));
		}

		if (m_cbDatabases.GetCount() >= 0)
			m_cbDatabases.SetCurSel(0);

	} COM_CATCH;
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// Messagehandler

LRESULT CReconnectSQLServerDlg::OnInitDialog(HWND hFocus, LPARAM lParam)
{
// Fenster im Parent zentrieren
	CenterWindow(GetParent());

// Controls initialisieren
	m_ftReconnectPrompt.Attach(GetDlgItem(IDC_RECONNECTPROMPT));
	m_ftServer.SubclassWindow(GetDlgItem(IDC_STATIC_SERVER));
	m_cbSQLServers.Attach(GetDlgItem(IDC_SQLSERVERNAME));
	m_ftAuthenticate.SubclassWindow(GetDlgItem(IDC_AUTHENTICATE));
	m_bttnDomane.Attach(GetDlgItem(IDC_AUTHENTICATE_DOMANE));
	m_bttnSQLServer.Attach(GetDlgItem(IDC_AUTHENTICATE_SQLSERVER));
	m_sleUserName.Attach(GetDlgItem(IDC_USERNAME));
	m_slePassword.Attach(GetDlgItem(IDC_PASSWORD));
	m_ftDatabase.SubclassWindow(GetDlgItem(IDC_STATIC_DATABASE));
	m_cbDatabases.Attach(GetDlgItem(IDC_DATABASENAME));

// Caption setzen
CString strText;

	strText.Format(IDS_OPENPROJECTCAP, g_cbTRiAS);
	_ASSERTE(strText.GetLength() > 0);
	SetWindowText(strText);

// Prompt setzen
	strText.Format(IDS_RECONNECTPROMPT, m_strName, m_strPath);
	_ASSERTE(strText.GetLength() > 0);
	m_ftReconnectPrompt.SetWindowText(strText);

// Knöpfchen richten
	AdjustAuthMode(m_fTrusted);
	if (!m_fTrusted && !m_strUser.IsEmpty()) {
		m_sleUserName.SetWindowText(m_strUser);
		if (!m_strPwd.IsEmpty())
			m_slePassword.SetWindowText(m_strPwd);
	}
	AdjustControls();

	return TRUE;	// Let the system set the focus
}

// Implementation of OnOK
void CReconnectSQLServerDlg::OnOK(UINT wNotifyCode, int iCtrlId, HWND hCtrl)
{
// prepare results
char cbBuffer[_MAX_PATH];

	_ASSERTE(m_cbSQLServers.GetCurSel() >= 0 && m_cbSQLServers.GetWindowTextLength() > 0);
	m_cbSQLServers.GetWindowText(cbBuffer, sizeof(cbBuffer));
	m_strServer = cbBuffer;

	if (!m_fTrusted) {
		m_sleUserName.GetWindowText(cbBuffer, sizeof(cbBuffer));
		m_strUser = cbBuffer;
		m_slePassword.GetWindowText(cbBuffer, sizeof(cbBuffer));
		m_strPwd = cbBuffer;
	}
	else {
		m_strUser.Empty();
		m_strPwd.Empty();
	}

	_ASSERTE(m_cbDatabases.GetCurSel() >= 0 && m_cbDatabases.GetWindowTextLength() > 0);
	m_cbDatabases.GetWindowText(cbBuffer, sizeof(cbBuffer));
	m_strDatabaseName = cbBuffer;

	EndDialog(IDOK);
}

// Implementation of OnCancel
void CReconnectSQLServerDlg::OnCancel(UINT wNotifyCode, int iCtrlId, HWND hCtrl)
{
	EndDialog(IDCANCEL);
}

// Implementation of OnAuthDomane
void CReconnectSQLServerDlg::OnAuthDomane(UINT wNotifyCode, int iCtrlId, HWND hCtrl)
{
	AdjustAuthMode(TRUE);
	AdjustControls();
}

// Implementation of OnAuthSQLServer
void CReconnectSQLServerDlg::OnAuthSQLServer(UINT wNotifyCode, int iCtrlId, HWND hCtrl)
{
	AdjustAuthMode(FALSE);
	AdjustControls();
}

// Implementation of OnDropDownServers
void CReconnectSQLServerDlg::OnDropDownServers(UINT wNotifyCode, int iCtrlId, HWND hCtrl)
{
	if (!m_fServersFilled && SUCCEEDED(FillSQLServerNames())) 
		m_fServersFilled = true;
	AdjustControls();
}

// Implementation of OnUsernameChanged
void CReconnectSQLServerDlg::OnUsernameChanged(UINT wNotifyCode, int iCtrlId, HWND hCtrl)
{
	AdjustControls();
}

// Implementation of OnDropDownDatabases
void CReconnectSQLServerDlg::OnDropDownDatabases(UINT wNotifyCode, int iCtrlId, HWND hCtrl)
{
	if (!m_fDatabasesFilled && SUCCEEDED(FillDatabases())) 
		m_fDatabasesFilled = true;

	AdjustControls();
}

void CReconnectSQLServerDlg::OnSelectDatabases(UINT wNotifyCode, int iCtrlId, HWND hCtrl)
{
	AdjustControls();
}


