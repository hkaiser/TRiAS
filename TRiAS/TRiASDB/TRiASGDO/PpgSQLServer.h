// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 11.10.2002 21:05:33 
//
// @doc
// @module PpgSQLServer.h | Declaration of the <c CPpgSQLServer> class

#if !defined(_PPGSQLSERVER_H__A44AA366_BB68_4725_967E_AFE92F3C9491__INCLUDED_)
#define _PPGSQLSERVER_H__A44AA366_BB68_4725_967E_AFE92F3C9491__INCLUDED_

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
// CPpgSQLServer
class CPpgSQLServer :
	public CPropertyPageImpl<CPpgSQLServer>
{
public:
	CPpgSQLServer(LPCSTR pcTitle);
	~CPpgSQLServer();

	enum { IDD = IDD_PPGSQLSERVER };

	BEGIN_MSG_MAP_EX(CPpgSQLServer)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_HANDLER_EX(IDC_AUTHENTICATE_DOMANE, BN_CLICKED, OnAuthDomane)
		COMMAND_HANDLER_EX(IDC_AUTHENTICATE_SQLSERVER, BN_CLICKED, OnAuthSQLServer)
		COMMAND_HANDLER_EX(IDC_SQLSERVERNAME, CBN_DROPDOWN, OnDropDownServers)
		COMMAND_HANDLER_EX(IDC_USERNAME, EN_CHANGE, OnUsernameChanged)
		CHAIN_MSG_MAP(CPropertyPageImpl<CPpgSQLServer>)
	END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// Message handlers
	LRESULT OnInitDialog(HWND hFocus, LPARAM lParam);
	void OnAuthDomane(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnAuthSQLServer(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnDropDownServers(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnUsernameChanged(UINT wNotifyCode, int iCtrlId, HWND hCtrl);

	int OnWizardNext();
	int OnWizardBack();
	BOOL OnSetActive();

////////////////////////////////////////////////////////////////////////////
// hier: Dialog nur für CreateDataSource und neue TRiAS-DBs anzeigen
	HRESULT SetProgID(LPCSTR pcProgID) 
	{ 
		_ASSERTE(!strcmp(pcProgID, _T("SQLServerRO.GDatabase")) || 
				 !strcmp(pcProgID, _T("SQLServerRW.GDatabase"))); 

		if (strcmp (pcProgID, _T("SQLServerRO.GDatabase")) &&
			strcmp (pcProgID, _T("SQLServerRW.GDatabase")))
			return E_FAIL;

		m_fReadWrite = strcmp(pcProgID, "SQLServerRW.GDatabase") ? false : true;
		m_strProgID = pcProgID;
		return S_OK; 
	}
	HRESULT SetCreateMode (BOOL fCreate) 
	{
		m_fCreateMode = fCreate ? true : false;
		return S_OK;		// Seite immer anzeigen
	}
	HRESULT SetPairs (IComposeStringPairs *pIPairs) 
	{
		m_Pairs = pIPairs; 
		return S_OK; 
	}

protected:
	void AdjustAuthMode(BOOL fAuthMode);
	HRESULT FillSQLServerNames();
	void AdjustButtons();
	HRESULT PrepareResults();

private:
	CString m_strProgID;
	CString m_strCaption;
	WComposeStringPairs m_Pairs;
	bool m_fCreateMode;
	bool m_fReadWrite;
	bool m_fServersFilled;

	CStatic	m_ftOpenNewPrompt;
	CSeparator m_ftAuthenticate;
	CButton m_bttnDomane;
	CButton m_bttnSQLServer;
	CEdit m_sleUserName;
	CEdit m_slePassword;
	CComboBox m_cbSQLServers;
};

#endif // !defined(_PPGSQLSERVER_H__A44AA366_BB68_4725_967E_AFE92F3C9491__INCLUDED_)
