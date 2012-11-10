// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 20.12.2000 12:18:05 
//
// @doc
// @module Strings.h | Stringkonstanten

#if !defined(_STRINGS_H__7F2949FA_567E_408C_A240_20244FEB2E6D__INCLUDED_)
#define _STRINGS_H__7F2949FA_567E_408C_A240_20244FEB2E6D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Variable Strings (werden bei Startup)
extern char g_cbTRiAS[];

extern const TCHAR g_cbCopyrightName[];	// TEXT("TRiAS®");

///////////////////////////////////////////////////////////////////////////////
// 
extern const TCHAR g_cbAppKey[];	// TEXT("TRiAS.Application.4");
extern const TCHAR g_cbDocKey[];	// TEXT("TRiAS.Document.2");
extern const TCHAR g_cbShowSysFeatures[];	// TEXT("ShowSysFeatures");
extern const TCHAR g_cbSysAdmin[];	// TEXT("SystemAdministration");

extern const TCHAR g_cbNil[];		// TEXT("");
extern const TCHAR g_cbSpace[];		// TEXT(" ");
extern const TCHAR g_cbDel[];		// TEXT("\\");

extern const TCHAR g_cbRegConfig[];		// TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config");
extern const TCHAR g_cbRegVersion[];	// TEXT("SOFTWARE\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY) TEXT("\\5.0");
extern const TCHAR g_cbUninstall[];		// TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" REG_PRODUCT_KEY);

extern const TCHAR g_cbUninstallString[];	// TEXT("UninstallString");
#if _TRiAS_VER < 0x0400
extern const TCHAR g_cbOrigUninstallString[];	// TEXT("OrigUninstallString");
#endif // _TRiAS_VER < 0x0400
extern const TCHAR g_cbUnregFull[];		// TEXT(" /unregserver:full");
extern const TCHAR g_cbDisplayName[];	// TEXT("DisplayName");
extern const TCHAR g_cbSerial[];		// TEXT("Serial");

extern const TCHAR g_cbAppID[];		// TEXT("AppID");
extern const TCHAR g_cbClsId[];		// TEXT("CLSID");
extern const TCHAR g_cbToolboxBitmap[];	// TEXT("ToolboxBitmap32");

#endif // !defined(_STRINGS_H__7F2949FA_567E_408C_A240_20244FEB2E6D__INCLUDED_)
