// ----------------------------------------------------------------------------
// 
// This file is part of the Microsoft COM+ Samples.
// 
// Copyright (C) 1995-2000 Microsoft Corporation. All rights reserved.
// 
// This source code is intended only as a supplement to Microsoft
// Development Tools and/or on-line documentation. See these other
// materials for detailed information regarding Microsoft code samples.
// 
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
// 
// ----------------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include "ntsecapi.h"
#include "dcomperm.h"

DWORD
ListDefaultAccessACL()
{
    return ListNamedValueSD (HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Ole"), TEXT("DefaultAccessPermission"));
}

DWORD
ListDefaultLaunchACL()
{
    return ListNamedValueSD (HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Ole"), TEXT("DefaultLaunchPermission"));
}

DWORD
ListAppIDAccessACL (
    LPTSTR AppID
    )
{
    TCHAR   keyName [256];

    if (AppID [0] == '{')
        wsprintf (keyName, TEXT("APPID\\%s"), AppID); else
        wsprintf (keyName, TEXT("APPID\\{%s}"), AppID);

    return ListNamedValueSD (HKEY_CLASSES_ROOT, keyName, TEXT("AccessPermission"));
}

DWORD
ListAppIDLaunchACL (
    LPTSTR AppID
    )
{
    TCHAR   keyName [256];

    if (AppID [0] == '{')
        wsprintf (keyName, TEXT("APPID\\%s"), AppID); else
        wsprintf (keyName, TEXT("APPID\\{%s}"), AppID);

    return ListNamedValueSD (HKEY_CLASSES_ROOT, keyName, TEXT("LaunchPermission"));
}

DWORD
ChangeDefaultAccessACL (
    LPTSTR Principal,
    BOOL SetPrincipal,
    BOOL Permit
    )
{
    if (SetPrincipal)
    {
        RemovePrincipalFromNamedValueSD (HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Ole"), TEXT("DefaultAccessPermission"), Principal);
        return AddPrincipalToNamedValueSD (HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Ole"), TEXT("DefaultAccessPermission"), Principal, Permit);
    } else
        return RemovePrincipalFromNamedValueSD (HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Ole"), TEXT("DefaultAccessPermission"), Principal);
}

DWORD
ChangeDefaultLaunchACL (
    LPTSTR Principal,
    BOOL SetPrincipal,
    BOOL Permit
    )
{
    if (SetPrincipal)
    {
        RemovePrincipalFromNamedValueSD (HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Ole"), TEXT("DefaultLaunchPermission"), Principal);
        return AddPrincipalToNamedValueSD (HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Ole"), TEXT("DefaultLaunchPermission"), Principal, Permit);
    } else
        return RemovePrincipalFromNamedValueSD (HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\Ole"), TEXT("DefaultLaunchPermission"), Principal);
}

DWORD
ChangeAppIDAccessACL (
    LPTSTR AppID,
    LPTSTR Principal,
    BOOL SetPrincipal,
    BOOL Permit
    )
{
    TCHAR   keyName [256];

    if (AppID [0] == '{')
        wsprintf (keyName, TEXT("APPID\\%s"), AppID); else
        wsprintf (keyName, TEXT("APPID\\{%s}"), AppID);

    if (SetPrincipal)
    {
        RemovePrincipalFromNamedValueSD (HKEY_CLASSES_ROOT, keyName, TEXT("AccessPermission"), Principal);
        return AddPrincipalToNamedValueSD (HKEY_CLASSES_ROOT, keyName, TEXT("AccessPermission"), Principal, Permit);
    } else
        return RemovePrincipalFromNamedValueSD (HKEY_CLASSES_ROOT, keyName, TEXT("AccessPermission"), Principal);
}

DWORD
ChangeAppIDLaunchACL (
    LPTSTR AppID,
    LPTSTR Principal,
    BOOL SetPrincipal,
    BOOL Permit
    )
{
    TCHAR   keyName [256];

    if (AppID [0] == '{')
        wsprintf (keyName, TEXT("APPID\\%s"), AppID); else
        wsprintf (keyName, TEXT("APPID\\{%s}"), AppID);

    if (SetPrincipal)
    {
        RemovePrincipalFromNamedValueSD (HKEY_CLASSES_ROOT, keyName, TEXT("LaunchPermission"), Principal);
        return AddPrincipalToNamedValueSD (HKEY_CLASSES_ROOT, keyName, TEXT("LaunchPermission"), Principal, Permit);
    } else
        return RemovePrincipalFromNamedValueSD (HKEY_CLASSES_ROOT, keyName, TEXT("LaunchPermission"), Principal);
}
