// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 20.12.2000 12:17:30 
//
// @doc
// @module Strings.cpp | Stringkonstanten

#include "StdAfx.h"
#include "Strings.h"

///////////////////////////////////////////////////////////////////////////////
// Variable Strings (werden bei Startup)
char g_cbTRiAS[_MAX_PATH];

const TCHAR g_cbCopyrightName[] = TEXT("TRiAS®");

///////////////////////////////////////////////////////////////////////////////
// 
const TCHAR g_cbAppKey[] = TEXT("TRiAS.Application.4");
const TCHAR g_cbDocKey[] = TEXT("TRiAS.Document.2");
const TCHAR g_cbShowSysFeatures[] = TEXT("ShowSysFeatures");
const TCHAR g_cbSysAdmin[] = TEXT("SystemAdministration");

const TCHAR g_cbNil[] = TEXT("");
const TCHAR g_cbSpace[] = TEXT(" ");
const TCHAR g_cbDel[] = TEXT("\\");

const TCHAR g_cbRegConfig[] = TEXT("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config");
const TCHAR g_cbRegVersion[] = TEXT("SOFTWARE\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY) TEXT("\\5.0");
const TCHAR g_cbUninstall[] = TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" REG_PRODUCT_KEY);

const TCHAR g_cbUninstallString[] = TEXT("UninstallString");
#if _TRiAS_VER < 0x0400
const TCHAR g_cbOrigUninstallString[] = TEXT("OrigUninstallString");
#endif // _TRiAS_VER < 0x0400
const TCHAR g_cbUnregFull[] = TEXT(" /unregserver:full");
const TCHAR g_cbDisplayName[] = TEXT("DisplayName");
const TCHAR g_cbSerial[] = TEXT("Serial");

const TCHAR g_cbAppID[] = TEXT("AppID");
const TCHAR g_cbClsId[] = TEXT("CLSID");
const TCHAR g_cbToolboxBitmap[] = TEXT("ToolboxBitmap32");
