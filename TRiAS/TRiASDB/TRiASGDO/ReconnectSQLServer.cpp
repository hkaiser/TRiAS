// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 24.10.2002 16:06:57 
//
// @doc
// @module ReconnectSQLServer.cpp | Definition of the <c CReconnectSQLServer> class

#include "stdafx.h"
#include "TRiASGDOImpl.h"

#include "ReconnectSQLServer.h"
#include "ReconnectSQLServerDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReconnectSQLServer

// Implementation of GetReconnectParams
STDMETHODIMP CReconnectSQLServer::GetReconnectParams(INT_PTR hWnd, BSTR bstrName, 
	BSTR bstrDesc, BSTR bstrConnectString, BSTR bstrPath, BSTR *pbstrNewName, 
	BSTR *pbstrNewConnectString, BSTR *pbstrNewPath)
{
	if (NULL == pbstrNewName || NULL == pbstrNewConnectString || NULL == pbstrNewPath)
		return E_POINTER;

	*pbstrNewName = NULL;
	*pbstrNewConnectString = NULL;
	*pbstrNewPath = NULL;

// Dialog initialisieren und anzeigen
CReconnectSQLServerDlg Dlg;

	Dlg.m_strName = bstrName;
	Dlg.m_strPath = bstrPath;

// Connectstring auswerten
WParseStringPairs Parse;

	COM_TRY {
	long lPairs = 0;

		THROW_FAILED_HRESULT(Parse.CreateInstance(CLSID_ParseStringPairs));
		THROW_FAILED_HRESULT(Parse -> put_Pattern(CComBSTR(g_cbCollatePattern)));
		THROW_FAILED_HRESULT(Parse -> Parse(bstrConnectString, &lPairs));

		USES_CONVERSION;
		if (0 < lPairs) {
		CComBSTR bstr;

		// Server/Datenbasis
			if (S_OK == Parse -> get_Value(CComBSTR(L"Server"), CLEARED(bstr)))
				Dlg.m_strServer = OLE2A(bstr);
			if (S_OK == Parse -> get_Value(CComBSTR(L"Database"), CLEARED(bstr)))
				Dlg.m_strDatabaseName = OLE2A(bstr);

		// Authentifikation
			if (S_OK == Parse -> get_Value(CComBSTR(L"Trusted_Connection"), CLEARED(bstr)) &&
				bstr == L"Yes")
			{
				Dlg.m_fTrusted = true;
			}
			else {
				Dlg.m_fTrusted = false;
				if (S_OK == Parse -> get_Value(CComBSTR(L"UID"), CLEARED(bstr)))
					Dlg.m_strUser = OLE2A(bstr);
				if (S_OK == Parse -> get_Value(CComBSTR(L"PWD"), CLEARED(bstr)))
					Dlg.m_strPwd = OLE2A(bstr);
			}

		// ProgId 
			if (S_OK == Parse -> get_Value(CComBSTR(L"PROGID"), CLEARED(bstr))) {
				if (bstr == L"SQLServerRW.GDatabase")
					Dlg.m_fReadWrite = true;
				else
					Dlg.m_fReadWrite = false;
			}
		}

	} COM_CATCH;

	if (IDOK == Dlg.DoModal(reinterpret_cast<HWND>(hWnd))) {
	// ok gedrückt, es müßte alles da sein
		COM_TRY {
		WComposeStringPairs Compose(Parse);

			THROW_FAILED_HRESULT(Compose -> SetValue(CComBSTR(L"Server"), 
				CComBSTR(Dlg.m_strServer), VARIANT_TRUE));
			THROW_FAILED_HRESULT(Compose -> SetValue(CComBSTR(L"Database"), 
				CComBSTR(Dlg.m_strDatabaseName), VARIANT_TRUE));
			if (Dlg.m_fTrusted) {
				THROW_FAILED_HRESULT(Compose -> SetValue(CComBSTR(L"Trusted_Connection"), 
					CComBSTR("Yes"), VARIANT_TRUE));
			}
			else {
				THROW_FAILED_HRESULT(Compose -> SetValue(CComBSTR(L"Trusted_Connection"), 
					CComBSTR("No"), VARIANT_TRUE));
				THROW_FAILED_HRESULT(Compose -> SetValue(CComBSTR(L"UID"), 
					CComBSTR(Dlg.m_strUser), VARIANT_TRUE));
				THROW_FAILED_HRESULT(Compose -> SetValue(CComBSTR(L"PWD"), 
					CComBSTR(Dlg.m_strPwd), VARIANT_TRUE));
			}

			THROW_FAILED_HRESULT(Compose -> get_ComposedData(CComBSTR(g_cbCollatePattern), 
				pbstrNewConnectString));

		} COM_CATCH;

		*pbstrNewName = CComBSTR(bstrName).Detach();
		*pbstrNewPath = CComBSTR(bstrPath).Detach();
		return S_OK;
	}

// Nutzer hat abgebrochen
	return E_FAIL;
}

