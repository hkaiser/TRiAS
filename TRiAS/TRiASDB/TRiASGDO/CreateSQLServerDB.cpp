// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 12.11.2002 13:15:43 
//
// @doc
// @module CreateSQLServerDB.cpp | Definition of the <c CCreateSQLServerDB> class

#include "stdafx.h"
#include "TRiASGDOImpl.h"

#include <sqldmo.h>
#include <sqldmoid.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "SQLServerUtils.h"
#include "CreateSQLServerDB.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterfaceEx(SQLDMOApplication);
DefineSmartInterfaceEx(SQLDMORegistry);
DefineSmartInterfaceEx(SQLDMODatabases);
DefineSmartInterfaceEx(SQLDMODatabase);
DefineSmartInterfaceEx(SQLDMODBFile);
DefineSmartInterfaceEx(SQLDMOFileGroups);
DefineSmartInterfaceEx(SQLDMOFileGroup);
DefineSmartInterfaceEx(SQLDMOLogFile);
DefineSmartInterfaceEx(SQLDMOTransactionLog);

///////////////////////////////////////////////////////////////////////////////
// 
#define DATAFILE_INITIALSIZE	2
#define DATAFILE_FILEGROWTH		1
#define LOGFILE_INITIALSIZE		2

/////////////////////////////////////////////////////////////////////////////
// CCreateSQLServerDB

HRESULT GetDatabase (ISQLDMOServer *pIServer, BSTR bstrDatabaseName, 
	ISQLDMODatabase **ppIDatabase)
{
	COM_TRY {
	WSQLDMODatabase Database (CLSID_SQLDMODatabase);

		RETURN_FAILED_HRESULT(Database->SetName(bstrDatabaseName));

	// Wurzelverzeichnis besorgen
	WSQLDMORegistry Registry;
	CComBSTR bstrRoot;

		RETURN_FAILED_HRESULT(pIServer->GetRegistry(Registry.ppi()));
		RETURN_FAILED_HRESULT(Registry->GetSQLDataRoot(CLEARED(bstrRoot)));

	// primary data file
	WSQLDMODBFile DataFile (CLSID_SQLDMODBFile);
	CComBSTR bstrMdfName (bstrRoot);
	CComBSTR bstrDbFileName(bstrDatabaseName);

		bstrDbFileName.Append(L"_Data");
		bstrMdfName.Append(L"\\Data\\");
		bstrMdfName.AppendBSTR(bstrDbFileName);
		bstrMdfName.Append(L".mdf");

		RETURN_FAILED_HRESULT(DataFile->SetName(bstrDbFileName));
		RETURN_FAILED_HRESULT(DataFile->SetPhysicalName(bstrMdfName));
		RETURN_FAILED_HRESULT(DataFile->SetPrimaryFile(TRUE));

	// specify initail size ans file growth in chunks of fixed size for all data files.
		RETURN_FAILED_HRESULT(DataFile->SetSize(DATAFILE_INITIALSIZE));
		RETURN_FAILED_HRESULT(DataFile->SetFileGrowthType(SQLDMOGrowth_MB));
		RETURN_FAILED_HRESULT(DataFile->SetFileGrowth(DATAFILE_FILEGROWTH));

	// add the new datafile
	WSQLDMOFileGroups FileGroups;
	WSQLDMOFileGroup FileGroup;

		RETURN_FAILED_HRESULT(Database->GetFileGroups(FileGroups.ppi()));
		RETURN_FAILED_HRESULT(FileGroups->GetItemByName(CComBSTR(L"PRIMARY"), 
			FileGroup.ppi()));
		RETURN_FAILED_HRESULT(FileGroup->AddDBFile(DataFile));

	// log file
	WSQLDMOLogFile LogFile (CLSID_SQLDMOLogFile);
	CComBSTR bstrLogFileName (bstrRoot);
	CComBSTR bstrLogName (bstrDatabaseName);

		bstrLogName.Append(L"_Log");
		bstrLogFileName.Append(L"\\Data\\");
		bstrLogFileName.AppendBSTR(bstrLogName);
		bstrLogFileName.Append(L".ldf");

		RETURN_FAILED_HRESULT(LogFile->SetName(bstrLogName));
		RETURN_FAILED_HRESULT(LogFile->SetPhysicalName(bstrLogFileName));
		RETURN_FAILED_HRESULT(LogFile->SetSize(LOGFILE_INITIALSIZE));

	// add new logfile
	WSQLDMOTransactionLog TransLog;

		RETURN_FAILED_HRESULT(Database->GetTransactionLog(TransLog.ppi()));
		RETURN_FAILED_HRESULT(TransLog->AddLogFile(LogFile));

	// jetzt passierts
	WSQLDMODatabases Databases;

		RETURN_FAILED_HRESULT(pIServer->GetDatabases(Databases.ppi()));
		RETURN_FAILED_HRESULT(Databases->Add(Database));

		*ppIDatabase = Database.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP LoadSQLCommand (UINT uiId, BSTR *pbstrCommand)
{
	_ASSERTE(NULL != pbstrCommand);
	*pbstrCommand = NULL;

HRSRC hRsc = ::FindResource(_Module.GetResourceInstance(), MAKEINTRESOURCE(uiId), "SQLSCRIPT");

	if (NULL == hRsc)
		return E_INVALIDARG;	// resource not found

HGLOBAL hGlb = ::LoadResource(_Module.GetModuleInstance(), hRsc);

	if (NULL == hGlb) 
		return E_INVALIDARG;

LPVOID pData = ::LockResource(hGlb);

	if (NULL == pData) 
		return E_INVALIDARG;

	COM_TRY {
	DWORD dwSize = ::SizeofResource(_Module.GetModuleInstance(), hRsc);
	CComBSTR bstr (dwSize, (char const *)pData);

		*pbstrCommand = bstr.Detach();

	} COM_CATCH;
	return S_OK;
}

HRESULT InitMetaData(ISQLDMOServer *pIServer, BSTR bstrDbName)
{
	COM_TRY {
	CComBSTR bstrUseCommand (L"USE ");

		bstrUseCommand.AppendBSTR(bstrDbName);
		bstrUseCommand.Append(L"\nGO\n");

	CComBSTR bstrCommand;

		RETURN_FAILED_HRESULT(LoadSQLCommand(IDR_SQLSERVER_CREATE_METADATA, CLEARED(bstrCommand)));
		bstrUseCommand.AppendBSTR(bstrCommand);
		RETURN_FAILED_HRESULT(pIServer -> ExecuteImmediate(bstrUseCommand));

	} COM_CATCH;
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

// Implementation of CreateDatabase
STDMETHODIMP CCreateSQLServerDB::CreateDatabase(BSTR bstrName, BSTR bstrLocale, 
	BSTR bstrSource)
{
	ATLTRACE(_T("CCreateSQLServerDB::CreateDatabase\n"));
	COM_TRY {
	CWaitCursor wait;
	CComBSTR bstrServer, bstrDbName, bstrUser, bstrPwd;
	bool fTrusted = false;

		RETURN_FAILED_HRESULT(GetAuthParams(bstrSource, CLEARED(bstrServer), 
			CLEARED(bstrDbName), CLEARED(bstrUser), CLEARED(bstrPwd), &fTrusted));

	// Datenbank erzeugen
	CDisconnectGuard Server;
	WSQLDMODatabase Database;

		RETURN_FAILED_HRESULT(GetSQLServer(bstrServer, bstrUser, bstrPwd, 
			fTrusted, Server.ppi()));
		RETURN_FAILED_HRESULT(GetDatabase(Server, bstrDbName, Database.ppi()));
		RETURN_FAILED_HRESULT(InitMetaData(Server, bstrDbName));

	} COM_CATCH;
	return S_OK;
}

