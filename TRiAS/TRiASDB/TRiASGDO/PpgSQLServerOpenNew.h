// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 12.10.2002 21:54:51 
//
// @doc
// @module PpgSQLServerOpenNew.h | Declaration of the <c CPpgSQLServerOpenNew> class

#if !defined(_PPGSQLSERVEROPENNEW_H__A97AC1D5_E0BF_4FD5_8CBC_E89E8B9C7834__INCLUDED_)
#define _PPGSQLSERVEROPENNEW_H__A97AC1D5_E0BF_4FD5_8CBC_E89E8B9C7834__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPpgSQLServerOpenNew
class CPpgSQLServerOpenNew :
	public CPropertyPageImpl<CPpgSQLServerOpenNew>
{
public:
	CPpgSQLServerOpenNew(LPCSTR pcTitle);
	~CPpgSQLServerOpenNew();

	enum { 
		IDD_OPEN = IDD_PPGSQLSERVER_OPEN,
		IDD_NEW = IDD_PPGSQLSERVER_NEW,		 
		IDD = IDD_NEW
	};

	BEGIN_MSG_MAP_EX(CPpgSQLServerOpenNew)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_HANDLER_EX(IDC_DATABASENAME, CBN_DROPDOWN, OnDropDownDatabases)
		COMMAND_HANDLER_EX(IDC_DATABASENAME, CBN_SELCHANGE, OnSelectDatabases)
		COMMAND_HANDLER_EX(IDC_DATABASENAME, EN_CHANGE, OnDatabaseChanged)
		COMMAND_HANDLER_EX(IDC_DATABASENAME, EN_KILLFOCUS, OnDatabaseKillFocus)
		COMMAND_HANDLER_EX(IDC_CONNECTION_NAME, EN_CHANGE, OnConnNameChanged)
		CHAIN_MSG_MAP(CPropertyPageImpl<CPpgSQLServerOpenNew>)
	END_MSG_MAP()

// Message handlers
	LRESULT OnInitDialog(HWND hFocus, LPARAM lParam);

	BOOL OnSetActive();
	int OnWizardBack();
	int OnWizardNext();
	int OnWizardFinish();

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	void OnDropDownDatabases(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnSelectDatabases(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnDatabaseChanged(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnDatabaseKillFocus(UINT wNotifyCode, int iCtrlId, HWND hCtrl);
	void OnConnNameChanged(UINT wNotifyCode, int iCtrlId, HWND hCtrl);

////////////////////////////////////////////////////////////////////////////
// hier: Dialog nur für CreateDataSource und neue TRiAS-DBs anzeigen
	HRESULT SetProgID(LPCSTR pcProgID) 
	{ 
		_ASSERTE(!strcmp(pcProgID, "SQLServerRO.GDatabase") || 
				 !strcmp(pcProgID, "SQLServerRW.GDatabase")); 

		if (strcmp (pcProgID, "SQLServerRO.GDatabase") &&
			strcmp (pcProgID, "SQLServerRW.GDatabase"))
			return E_FAIL;

		m_fReadWrite = strcmp(pcProgID, "SQLServerRW.GDatabase") ? false : true;
		m_strProgID = pcProgID;
		return S_OK; 
	}
	HRESULT SetCreateMode (BOOL fCreate) 
	{
		m_fCreateMode = fCreate ? true : false;
		m_psp.pszTemplate = MAKEINTRESOURCE(
			fCreate ? IDD_PPGSQLSERVER_NEW : IDD_PPGSQLSERVER_OPEN);	
		return S_OK;		// Seite immer anzeigen
	}
	HRESULT SetPairs (IComposeStringPairs *pIPairs) 
	{
		m_Pairs = pIPairs; 
		return S_OK; 
	}

protected:
	void AdjustButtons();
	HRESULT PrepareResults();
	bool DatabaseExistsAndWantsNotDelete(BSTR bstrDbName);

	HRESULT FillDatabases();

private:
	CString m_strProgID;
	CString m_strCaption;
	CString m_strLastServer;
	WComposeStringPairs m_Pairs;
	bool m_fCreateMode;
	bool m_fReadWrite;
	bool m_fDatabasesFilled;

	CEdit m_sleConnName;
	CEdit m_mleDescription;
};

#endif // !defined(_PPGSQLSERVEROPENNEW_H__A97AC1D5_E0BF_4FD5_8CBC_E89E8B9C7834__INCLUDED_)
