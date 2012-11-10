// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 14.11.2002 15:53:29 
//
// @doc
// @module SQLServerUtils.h | Declaration of the <c CSQLServerUtils> class

#if !defined(_SQLSERVERUTILS_H__C3818288_EB0E_499A_9F5B_822F2C8A019F__INCLUDED_)
#define _SQLSERVERUTILS_H__C3818288_EB0E_499A_9F5B_822F2C8A019F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterfaceEx(SQLDMOServer);

///////////////////////////////////////////////////////////////////////////////
// 
inline
HRESULT GetAuthParams (IParseStringPairs *pIPairs, BSTR *pbstrServer, BSTR *pbstrDbName,
	BSTR *pbstrUser, BSTR *pbstrPwd, bool *pfTrusted)
{
	_ASSERTE(NULL != pbstrServer && NULL != pbstrUser && NULL != pbstrPwd &&
		NULL != pfTrusted);

	*pbstrServer = NULL;
	if (NULL != pbstrDbName)
		*pbstrDbName = NULL;
	*pbstrUser = NULL;
	*pbstrPwd = NULL;
	*pfTrusted = false;

	COM_TRY {
	CComBSTR bstr;
	CComBSTR bstrServer, bstrDatabaseName;

		if (S_OK != pIPairs -> get_Value(CComBSTR(L"Server"), CLEARED(bstr)))
		{
			THROW_FAILED_HRESULT(E_UNEXPECTED);
		}
		*pbstrServer = bstr.Detach();
		
		if (NULL != pbstrDbName) {
			if (S_OK != pIPairs -> get_Value(CComBSTR(L"Database"), CLEARED(bstr)))
			{
				THROW_FAILED_HRESULT(E_UNEXPECTED);
			}
			*pbstrDbName = bstr.Detach();
		}

	bool fTrusted = false;
	CComBSTR bstrUser, bstrPwd;

		if (S_OK == pIPairs -> get_Value(CComBSTR(L"Trusted_Connection"), CLEARED(bstr)) &&
			bstr == L"Yes")
		{
			*pfTrusted = true;
		}
		else {
			*pfTrusted = false;
			if (S_OK != pIPairs -> get_Value(CComBSTR(L"UID"), CLEARED(bstr)))
			{
				THROW_FAILED_HRESULT(E_UNEXPECTED);
			}
			*pbstrUser = bstr.Detach();

			if (S_OK == pIPairs -> get_Value(CComBSTR(L"PWD"), CLEARED(bstr)))
				*pbstrPwd = bstr.Detach();
		}

	} COM_CATCH;
	return S_OK;
}

inline
HRESULT GetAuthParams (BSTR bstrSource, BSTR *pbstrServer, BSTR *pbstrDbName,
	BSTR *pbstrUser, BSTR *pbstrPwd, bool *pfTrusted)
{
	_ASSERTE(NULL != pbstrServer && NULL != pbstrUser && NULL != pbstrPwd &&
		NULL != pfTrusted);

	*pbstrServer = NULL;
	if (NULL != pbstrDbName)
		*pbstrDbName = NULL;
	*pbstrUser = NULL;
	*pbstrPwd = NULL;
	*pfTrusted = false;

	COM_TRY {
	WParseStringPairs Parse (CLSID_ParseStringPairs);
	long lPairs = 0;

		RETURN_FAILED_HRESULT(Parse -> put_Pattern(CComBSTR(g_cbCollatePattern)));
		RETURN_FAILED_HRESULT(Parse -> Parse(bstrSource, &lPairs));

		RETURN_FAILED_HRESULT(GetAuthParams(Parse, pbstrServer, pbstrDbName, 
			pbstrUser, pbstrPwd, pfTrusted));

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// 
inline
HRESULT GetSQLServer (BSTR bstrServer, BSTR bstrUser, BSTR bstrPwd, 
	bool fTrusted, ISQLDMOServer **ppIServer)
{
	_ASSERTE(NULL != ppIServer);

WSQLDMOServer Server;

	RETURN_FAILED_HRESULT(Server.CreateInstance(CLSID_SQLDMOServer));
	RETURN_FAILED_HRESULT(Server->SetLoginTimeout(-1));	// -1 is the ODBC default (60) seconds

	if (fTrusted) {
	// Domane Authentifizierung
		RETURN_FAILED_HRESULT(Server->SetLoginSecure(TRUE));
		RETURN_FAILED_HRESULT(Server->SetAutoReConnect(FALSE));
		RETURN_FAILED_HRESULT(Server->Connect(bstrServer, NULL, NULL));
	}
	else {
	// SQL_Server Authentifizierung
		RETURN_FAILED_HRESULT(Server->SetLoginSecure(FALSE));
		RETURN_FAILED_HRESULT(Server->SetAutoReConnect(FALSE));
		RETURN_FAILED_HRESULT(Server->Connect(bstrServer, bstrUser, bstrPwd));
	}
	*ppIServer = Server.detach();
	return S_OK;
}

#endif // !defined(_SQLSERVERUTILS_H__C3818288_EB0E_499A_9F5B_822F2C8A019F__INCLUDED_)
