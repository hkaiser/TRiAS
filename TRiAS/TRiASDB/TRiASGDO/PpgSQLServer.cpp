// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 11.10.2002 21:07:58 
//
// @doc
// @module PpgSQLServer.cpp | Definition of the <c CPpgSQLServer> class

#include "stdafx.h"
#include "TRiASGDOImpl.h"

#include <sqldmo.h>
#include "initguid.h"
#include <sqldmoid.h>

#include "PpgSQLServer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterfaceEx(SQLDMOApplication);
DefineSmartInterfaceEx(SQLDMONameList);

/////////////////////////////////////////////////////////////////////////////
// CPpgSQLServer

CPpgSQLServer::CPpgSQLServer(LPCSTR pcTitle) :
	CPropertyPageImpl<CPpgSQLServer>(),
	m_strCaption(pcTitle),
	m_fCreateMode(false)
{
	SetTitle((LPCSTR)m_strCaption);
	m_fReadWrite = false;
	m_fServersFilled = false;
}

CPpgSQLServer::~CPpgSQLServer()
{
	::CoFreeUnusedLibraries();		// SQLDMO freigeben
}

///////////////////////////////////////////////////////////////////////////////
// 
void CPpgSQLServer::AdjustAuthMode(BOOL fAuthMode)
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
}

// Implementation of AdjustButtons
void CPpgSQLServer::AdjustButtons()
{
DWORD dwFlags = PSWIZB_BACK;

	if (m_cbSQLServers.GetCurSel() >= 0 &&
		(m_bttnDomane.GetCheck() || 
			(m_bttnSQLServer.GetCheck() && m_sleUserName.GetWindowTextLength() > 0)
		)
	)
	{
		dwFlags |= PSWIZB_NEXT;
	}
	GetPropertySheet().SetWizardButtons(dwFlags);
}

HRESULT CPpgSQLServer::PrepareResults()
{
	if (!m_Pairs) 
		return E_UNEXPECTED;

// Servernamen speichern
CComBSTR bstrServer;

	_ASSERTE(-1 != m_cbSQLServers.GetCurSel());
	m_cbSQLServers.GetWindowText(CLEARED(bstrServer));
	RETURN_FAILED_HRESULT(m_Pairs -> SetValue(CComBSTR(L"Server"), bstrServer, 
		VARIANT_TRUE));

// AuthMode speichern
	if (m_bttnDomane.GetCheck()) {
	// Domänenanmeldung verwenden
		RETURN_FAILED_HRESULT(m_Pairs -> SetValue(CComBSTR(L"Trusted_Connection"), 
			CComBSTR("Yes"), VARIANT_TRUE));
	}
	else {
	// SQL-Server Anmeldung verwenden
		_ASSERTE(m_sleUserName.GetWindowTextLength() > 0);

	CComBSTR bstrUser, bstrPwd;

		m_sleUserName.GetWindowText(CLEARED(bstrUser));
		m_slePassword.GetWindowText(CLEARED(bstrPwd));

		RETURN_FAILED_HRESULT(m_Pairs -> SetValue(CComBSTR(L"Trusted_Connection"), 
			CComBSTR(L"No"), VARIANT_TRUE));
		RETURN_FAILED_HRESULT(m_Pairs -> SetValue(CComBSTR(L"UID"), 
			bstrUser, VARIANT_TRUE));
		if (bstrPwd.Length() > 0) {
			RETURN_FAILED_HRESULT(m_Pairs -> SetValue(CComBSTR(L"PWD"), 
				bstrPwd, VARIANT_TRUE));
		}
	}
	return S_OK;
}

// Implementation of FillSQLServerNames
HRESULT CPpgSQLServer::FillSQLServerNames()
{
	COM_TRY {
	int iFirstIndex = -1;

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
					iFirstIndex = iIndex;
			}
		}

		if (-1 != iFirstIndex)
			m_cbSQLServers.SetCurSel(iFirstIndex);
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

///////////////////////////////////////////////////////////////////////////////
// Messagehandlers
LRESULT CPpgSQLServer::OnInitDialog(HWND hFocus, LPARAM lParam)
{
	m_ftAuthenticate.SubclassWindow(GetDlgItem(IDC_AUTHENTICATE));
	m_ftOpenNewPrompt.Attach(GetDlgItem(IDC_DESCTEXT));
	m_bttnDomane.Attach(GetDlgItem(IDC_AUTHENTICATE_DOMANE));
	m_bttnSQLServer.Attach(GetDlgItem(IDC_AUTHENTICATE_SQLSERVER));
	m_sleUserName.Attach(GetDlgItem(IDC_USERNAME));
	m_slePassword.Attach(GetDlgItem(IDC_PASSWORD));
	m_cbSQLServers.Attach(GetDlgItem(IDC_SQLSERVERNAME));

CString strOpenNewPrompt;

	strOpenNewPrompt.LoadString(m_fCreateMode ? IDS_PROMPT_NEW_SQLSERVER :
		IDS_PROMPT_OPEN_SQLSERVER);
	m_ftOpenNewPrompt.SetWindowText(strOpenNewPrompt);

	AdjustAuthMode(TRUE);
	AdjustButtons();

	return TRUE;
}

// Implementation of OnAuthDomane
void CPpgSQLServer::OnAuthDomane(UINT wNotifyCode, int iCtrlId, HWND hCtrl)
{
	AdjustAuthMode(TRUE);
	AdjustButtons();
}

// Implementation of OnAuthSQLServer
void CPpgSQLServer::OnAuthSQLServer(UINT wNotifyCode, int iCtrlId, HWND hCtrl)
{
	AdjustAuthMode(FALSE);
	AdjustButtons();
}

// Implementation of OnDropDownServers
void CPpgSQLServer::OnDropDownServers(UINT wNotifyCode, int iCtrlId, HWND hCtrl)
{
	if (!m_fServersFilled && SUCCEEDED(FillSQLServerNames())) 
		m_fServersFilled = true;
	AdjustButtons();
}

// Implementation of OnUsernameChanged
void CPpgSQLServer::OnUsernameChanged(UINT wNotifyCode, int iCtrlId, HWND hCtrl)
{
	AdjustButtons();
}

// Implementation of OnWizardNext
int CPpgSQLServer::OnWizardNext()
{
	PrepareResults();
	return 0;
}

// Implementation of OnWizardBack
int CPpgSQLServer::OnWizardBack()
{
	m_fServersFilled = false;
	return 0;
}

BOOL CPpgSQLServer::OnSetActive()
{
	AdjustButtons();
	return TRUE;
}

