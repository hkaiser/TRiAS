// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/27/1998 12:13:04 PM
//
// @doc ERROR MACRO TRiASDB
// @module ErrorMacros2Impl.cpp | Fehlermakros

inline DWORD __cdecl FormatMessageLine( CComBSTR& strMsg, HRESULT hr, va_list* pArgs ) {
	int	nChar = 0;
	LPTSTR lptMsg = NULL;
	HINSTANCE	hRes = _Module.GetResourceInstance();
	/////////////////////////////////////////////////////////////////
	// zuerst versuchen, den Fehler lokal aufzulösen...
	nChar = ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE, hRes, hr, 0, (LPTSTR) &lptMsg, 1024, pArgs );
	DWORD	dwErr = 0;
	if( 0 == nChar ) {
		/////////////////////////////////////////////////////////////////
		// hat nicht geklappt; Fehler erst mal merken
		dwErr = GetLastError();
		/////////////////////////////////////////////////////////////////
		// und jetzt im System versuchen
		nChar = ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, hr, 1024, (LPTSTR) &lptMsg, 0, pArgs );
	}
	if( nChar ) {
		strMsg = lptMsg;
		::LocalFree( lptMsg );
		dwErr = 0;
	}
	return dwErr;
}

#if defined(_DEBUG)
HRESULT GenerateError (LPCTSTR strExpr, LPCTSTR strFile, int line, REFCLSID rClsId, REFIID riid, LPCOLESTR pcHelpFile, HRESULT hRes) {
#else
HRESULT GenerateError (REFCLSID rClsId, REFIID riid, LPCOLESTR pcHelpFile, HRESULT hRes) {
#endif
	CComBSTR	strMsgLine;
	DWORD dwErr = FormatMessageLine( strMsgLine, hRes, NULL );
#if defined(_DEBUG)
	USES_CONVERSION;
	if( dwErr ) {
		LPTSTR lptMsg = NULL;
		CComBSTR	strMsg(L"\n---------------------- Fehler beim Erzeugen der Fehlermeldung ----------------------\n");
		if( ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, dwErr, 1024, (LPTSTR) &lptMsg, 0, NULL ) ) {
			USES_CONVERSION;
			strMsg.Append( A2W(lptMsg) );
			::LocalFree(lptMsg);
			if( 0x716 == dwErr ) {
				strMsg.Append(L"\n----------------------------------------------------------------------------------------");
				strMsg.Append( L"\nHat die Message-Ressource den Wert 1? ;-)" );
			}
			strMsg.Append(L"\n----------------------------------------------------------------------------------------");
			_CrtDbgReport(_CRT_ASSERT, strFile, line, NULL, W2A(strMsg) );
			return E_FAIL;
		}
	}
	CComBSTR	strDbgLine;
	FormatDebuggerLine( strDbgLine, hRes, strFile, line, strExpr );
	strDbgLine.Append( _T("\t") );
	strDbgLine.Append( strMsgLine );
	strDbgLine.Append( _T("\n") );
	{ ATLTRACE( W2A(strDbgLine) ); }
#endif
	DWORD	dwHelpID = hRes;
	return AtlReportError(rClsId, strMsgLine, dwHelpID, pcHelpFile, riid, hRes);
}

#if defined(_DEBUG)
HRESULT GenerateErrorV (LPCTSTR strExpr, LPCTSTR strFile, int line, REFCLSID rClsId, REFIID riid, LPCOLESTR pcHelpFile, HRESULT hRes, va_list argList) {
#else
HRESULT GenerateErrorV (REFCLSID rClsId, REFIID riid, LPCOLESTR pcHelpFile, HRESULT hRes, va_list argList) {
#endif
	CComBSTR	strMsgLine;
	DWORD dwErr = FormatMessageLine( strMsgLine, hRes, &argList );
#if defined(_DEBUG)
	USES_CONVERSION;
	if( dwErr ) {
		LPTSTR lptMsg = NULL;
		if( ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, dwErr, 1024, (LPTSTR) &lptMsg, 0, NULL ) ) {
			_CrtDbgReport(_CRT_ASSERT, strFile, line, NULL, lptMsg );
			::LocalFree(lptMsg);
			return E_FAIL;
		}
	}
	CComBSTR	strDbgLine;
	FormatDebuggerLine( strDbgLine, hRes, strFile, line, strExpr );
	strDbgLine.Append( _T("\t") );
	strDbgLine.Append( strMsgLine );
	strDbgLine.Append( _T("\n") );
	{ ATLTRACE( W2A(strDbgLine) ); }
#endif
	DWORD	dwHelpID = hRes;
	return AtlReportError(rClsId, strMsgLine, dwHelpID, pcHelpFile, riid, hRes);
}

