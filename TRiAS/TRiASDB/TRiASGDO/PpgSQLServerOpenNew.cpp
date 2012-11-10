// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 12.10.2002 21:54:18 
//
// @doc
// @module PpgSQLServerOpenNew.cpp | Definition of the <c CPpgSQLServerOpenNew> class

#include "stdafx.h"
#include "TRiASGDOImpl.h"

#include <sqldmo.h>
#include <sqldmoid.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "SQLServerUtils.h"
#include "PpgSQLServerOpenNew.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterfaceEx(SQLDMODatabases);
DefineSmartInterfaceEx(SQLDMODatabase);

/////////////////////////////////////////////////////////////////////////////
// CPpgSQLServer

CPpgSQLServerOpenNew::CPpgSQLServerOpenNew(LPCSTR pcTitle) :
	CPropertyPageImpl<CPpgSQLServerOpenNew>(),
	m_strCaption(pcTitle),
	m_fCreateMode(false)
{
	SetTitle((LPCSTR)m_strCaption);
	m_fReadWrite = false;
	m_fDatabasesFilled = false;
}

CPpgSQLServerOpenNew::~CPpgSQLServerOpenNew()
{
}

// Implementation of AdjustButtons
void CPpgSQLServerOpenNew::AdjustButtons()
{
DWORD dwFlags = PSWIZB_BACK;

	if (m_fCreateMode) {
	CEdit Database (GetDlgItem(IDC_DATABASENAME));

		if (Database.GetWindowTextLength() > 0 &&
			m_sleConnName.GetWindowTextLength() > 0)
		{
			dwFlags |= PSWIZB_FINISH;
		}
		else
			dwFlags |= PSWIZB_DISABLEDFINISH;
	}
	else {
	CComboBox Databases (GetDlgItem(IDC_DATABASENAME));

		if (Databases.GetCurSel() >= 0 &&
			m_sleConnName.GetWindowTextLength() > 0)
		{
			dwFlags |= PSWIZB_FINISH;
		}
		else
			dwFlags |= PSWIZB_DISABLEDFINISH;
	}
	GetPropertySheet().SetWizardButtons(dwFlags);
}

namespace {
// disconnect am Ende sicherstellen
	struct CDisconnectGuard :
		public WSQLDMOServer
	{
		~CDisconnectGuard() { static_cast<ISQLDMOServer *>(*this)->DisConnect(); }
	};
}

bool CPpgSQLServerOpenNew::DatabaseExistsAndWantsNotDelete(BSTR bstrDbName)
{
// SQL-Server -Instanz
CDisconnectGuard Server;

	COM_TRY {
	CWaitCursor wait;
	WParseStringPairs Pairs(m_Pairs);
	CComBSTR bstrServer, bstrAuthMode;
	CComBSTR bstrUser, bstrPwd;
	bool fTrusted = false;

		RETURN_FAILED_HRESULT(GetAuthParams(Pairs, CLEARED(bstrServer), 
			NULL, CLEARED(bstrUser), CLEARED(bstrPwd), &fTrusted));
		RETURN_FAILED_HRESULT(GetSQLServer(bstrServer, bstrUser, bstrPwd, 
			fTrusted, Server.ppi()));

	WSQLDMODatabases SQLServerDBs;
	WSQLDMODatabase SQLServerDB;

		RETURN_FAILED_HRESULT(Server->GetDatabases(SQLServerDBs.ppi()));
		if (SUCCEEDED(SQLServerDBs->GetItemByName(bstrDbName, SQLServerDB.ppi()))) {
		// diese Datenbank gibt es schon
		CString strCaption;
		CString strPrompt;
		CWindow Wnd(GetActiveWindow());

			strCaption.LoadString(m_fReadWrite ? IDS_SQLSERVER_RW : IDS_SQLSERVER_RO);
			strPrompt.Format(IDS_SQLSERVER_DBEXISTS, bstrDbName, bstrServer);
			if (IDNO == Wnd.MessageBox(strPrompt, strCaption, MB_YESNO))
				return true;		// nicht löschen

		// Datenbank löschen
			if (FAILED(SQLServerDBs->RemoveByName(bstrDbName))) {
			// kann nicht gelöscht werden
				strPrompt.Format(IDS_COULD_NOT_DELETE, bstrDbName, bstrServer);
				Wnd.MessageBox(strPrompt, strCaption, MB_OK);
				return true;
			}
		}

	} COM_CATCH_RETURN(true);
	return false;
}

HRESULT CPpgSQLServerOpenNew::PrepareResults()
{
// Datenbasisnamen zu Location umbauen
	COM_TRY {
	WParseStringPairs Pairs(m_Pairs);
	CComBSTR bstrServer, bstrUser, bstrPwd;
	CComBSTR bstrDbName;
	bool fTrusted = false;

		RETURN_FAILED_HRESULT(Pairs->get_Value(CComBSTR(L"Server"), 
			CLEARED(bstrServer)));

		if (m_fCreateMode) {
		CEdit Database (GetDlgItem(IDC_DATABASENAME));

			_ASSERTE(Database.GetWindowTextLength() > 0 &&
				m_sleConnName.GetWindowTextLength() > 0);
			Database.GetWindowText(&bstrDbName);
			if (DatabaseExistsAndWantsNotDelete(bstrDbName))
				return E_ABORT;
		}
		else {
		CComboBox Databases (GetDlgItem(IDC_DATABASENAME));

			_ASSERTE(Databases.GetCurSel() >= 0 &&
				m_sleConnName.GetWindowTextLength() > 0);
			Databases.GetWindowText(&bstrDbName);
		}

		THROW_FAILED_HRESULT(m_Pairs -> SetValue(CComBSTR(L"Database"), 
			bstrDbName, VARIANT_TRUE));

	CComBSTR bstrLocation (bstrDbName);

		bstrLocation.Append(L"@");
		bstrLocation.AppendBSTR(bstrServer);
		THROW_FAILED_HRESULT(m_Pairs -> SetValue(CComBSTR(L"Location"), 
			bstrLocation, VARIANT_TRUE));

	// ConnName und ConnDesc für FakeMFC setzen
	CComBSTR bstrConnName, bstrConnDesc;

		m_sleConnName.GetWindowText(&bstrConnName);
		m_mleDescription.GetWindowText(&bstrConnDesc);
		RETURN_FAILED_HRESULT(m_Pairs -> SetValue(CComBSTR(L"ConnName"), 
			bstrConnName, VARIANT_TRUE));
		RETURN_FAILED_HRESULT(m_Pairs -> SetValue(CComBSTR(L"ConnDesc"), 
			bstrConnDesc, VARIANT_TRUE));

	// TRiASDB mitteilen, daß besondere ConnectInfo vorliegt
		RETURN_FAILED_HRESULT(m_Pairs -> SetValue(CComBSTR(L"CustomConnInfo"), 
			CComBSTR(L"1"), VARIANT_TRUE));

	} COM_CATCH;
	return S_OK;
}

// Implementation of FillDatabases
HRESULT CPpgSQLServerOpenNew::FillDatabases()
{
	_ASSERTE(!m_fCreateMode);

// SQL-Server -Instanz
CDisconnectGuard Server;

	COM_TRY {
	// Servernamen von vorhergehender Seite holen
	CWaitCursor wait;
	WParseStringPairs Pairs(m_Pairs);
	CComBSTR bstrServer, bstrAuthMode;
	CComBSTR bstrUser, bstrPwd;
	bool fTrusted = false;

		RETURN_FAILED_HRESULT(GetAuthParams(Pairs, CLEARED(bstrServer), 
			NULL, CLEARED(bstrUser), CLEARED(bstrPwd), &fTrusted));
		RETURN_FAILED_HRESULT(GetSQLServer(bstrServer, bstrUser, bstrPwd, 
			fTrusted, Server.ppi()));

	CComboBox Databases (GetDlgItem(IDC_DATABASENAME));
	WSQLDMODatabases SQLServerDBs;
	long lCount = 0;

		RETURN_FAILED_HRESULT(Server->GetDatabases(SQLServerDBs.ppi()));
		RETURN_FAILED_HRESULT(SQLServerDBs->GetCount(&lCount));
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

			RETURN_FAILED_HRESULT(SQLServerDB->GetName(CLEARED(bstrName)));
			Databases.AddString(CString(bstrName));
		}

		if (Databases.GetCount() >= 0)
			Databases.SetCurSel(0);

	} COM_CATCH;
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// MessageHandlers
LRESULT CPpgSQLServerOpenNew::OnInitDialog(HWND hFocus, LPARAM lParam)
{
	m_sleConnName.Attach(GetDlgItem(IDC_CONNECTION_NAME));
	m_mleDescription.Attach(GetDlgItem(IDC_CONNECT_DESCRIPTION));

CStatic ftPrompt (GetDlgItem(IDC_DESCTEXT));
CString strType;
TCHAR cbBuffer[_MAX_PATH];

	strType.LoadString(m_fReadWrite ? IDS_SQLSERVER_RW : IDS_SQLSERVER_RO);
	ftPrompt.GetWindowText(cbBuffer, sizeof(cbBuffer));
	wsprintf (cbBuffer, CString(cbBuffer), (LPCTSTR)strType);
	ftPrompt.SetWindowText(cbBuffer);

	AdjustButtons();
	return TRUE;
}

BOOL CPpgSQLServerOpenNew::OnSetActive()
{
// Servernamen abgleichen
	COM_TRY {
	// Servernamen von vorhergehender Seite holen
	WParseStringPairs Pairs(m_Pairs);
	CComBSTR bstrServer;

		RETURN_FAILED_HRESULT(Pairs->get_Value(CComBSTR(L"Server"), 
			CLEARED(bstrServer)));

	CString strServer(bstrServer);

		if (m_strLastServer != strServer) {
		// Controls rückstzen
			m_fDatabasesFilled = false;
		
			if (m_fCreateMode) {
			CEdit Database (GetDlgItem(IDC_DATABASENAME));

				Database.SetWindowText("");
				Database.SetFocus();
			}
			else {
			CComboBox Databases (GetDlgItem(IDC_DATABASENAME));

				for (int i = Databases.GetCount()-1; i >= 0; --i)
					Databases.DeleteString(i);

				Databases.SetCurSel(-1);
				Databases.SetFocus();
			}
			m_sleConnName.SetWindowText("");
			m_mleDescription.SetWindowText("");

			m_strLastServer = strServer;
		}

	} COM_CATCH_RETURN(FALSE);
	AdjustButtons();
	return TRUE;
}

int CPpgSQLServerOpenNew::OnWizardNext()
{
	return SUCCEEDED(PrepareResults()) ? 0 : -1;
}

int CPpgSQLServerOpenNew::OnWizardFinish()
{
	return SUCCEEDED(PrepareResults());
}

int CPpgSQLServerOpenNew::OnWizardBack()
{
	m_fDatabasesFilled = false;
	return 0;
}

// Implementation of OnDropDownDatabases
void CPpgSQLServerOpenNew::OnDropDownDatabases(UINT wNotifyCode, int iCtrlId, HWND hCtrl)
{
	_ASSERTE(!m_fCreateMode);
	if (!m_fDatabasesFilled && SUCCEEDED(FillDatabases())) 
		m_fDatabasesFilled = true;

	AdjustButtons();
}

void CPpgSQLServerOpenNew::OnSelectDatabases(UINT wNotifyCode, int iCtrlId, HWND hCtrl)
{
	_ASSERTE(!m_fCreateMode);
CComboBox Databases (GetDlgItem(IDC_DATABASENAME));
TCHAR cbBuffer[_MAX_PATH];

	if (Databases.GetCurSel() >= 0 && Databases.GetWindowTextLength() > 0) {
		Databases.GetWindowText(cbBuffer, sizeof(cbBuffer));
			
	CString strConnDesc;
	CString strType;

		strType.Format(m_fReadWrite ? IDS_SQLSERVER_RW : IDS_SQLSERVER_RO); 
		strConnDesc.Format(IDS_CONNECTDESCRIPTION, cbBuffer, LPCTSTR(strType));
		m_mleDescription.SetWindowText(strConnDesc);
		m_sleConnName.SetWindowText(cbBuffer);
	}
	AdjustButtons();
}

// Implementation of OnDatabaseChanged
void CPpgSQLServerOpenNew::OnDatabaseChanged(UINT wNotifyCode, int iCtrlId, HWND hCtrl)
{
	_ASSERTE(m_fCreateMode);
	AdjustButtons();
}

// Implementation of OnDatabaseKillFocus
void CPpgSQLServerOpenNew::OnDatabaseKillFocus(UINT wNotifyCode, int iCtrlId, HWND hCtrl)
{
	_ASSERTE(m_fCreateMode);

CEdit Database (GetDlgItem(IDC_DATABASENAME));
char cbBuffer[_MAX_PATH];

	if (0 != Database.GetWindowText(cbBuffer, sizeof(cbBuffer))) {
	CString strConnDesc;
	CString strType;

		strType.Format(m_fReadWrite ? IDS_SQLSERVER_RW : IDS_SQLSERVER_RO); 
		strConnDesc.Format(IDS_CONNECTDESCRIPTION, cbBuffer, LPCTSTR(strType));
		m_mleDescription.SetWindowText(strConnDesc);
		m_sleConnName.SetWindowText(cbBuffer);
	}
	AdjustButtons();
}

// Implementation of OnConnNameChanged
void CPpgSQLServerOpenNew::OnConnNameChanged(UINT wNotifyCode, int iCtrlId, HWND hCtrl)
{
	AdjustButtons();
}

