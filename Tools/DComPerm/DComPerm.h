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

#define GUIDSTR_MAX 38

#ifndef STR2UNI

#define STR2UNI(unistr, regstr) \
        mbstowcs (unistr, regstr, strlen (regstr)+1);

#define UNI2STR(regstr, unistr) \
        wcstombs (regstr, unistr, wcslen (unistr)+1);

#endif


//
// Wrappers
//

DWORD
ListDefaultAccessACL();

DWORD
ListDefaultLaunchACL();

DWORD
ListAppIDAccessACL (
    LPTSTR AppID
    );

DWORD
ListAppIDLaunchACL (
    LPTSTR AppID
    );

DWORD
ChangeDefaultAccessACL (
    LPTSTR Principal,
    BOOL SetPrincipal,
    BOOL Permit
    );

DWORD
ChangeDefaultLaunchACL (
    LPTSTR Principal,
    BOOL SetPrincipal,
    BOOL Permit
    );

DWORD
ChangeAppIDAccessACL (
    LPTSTR AppID,
    LPTSTR Principal,
    BOOL SetPrincipal,
    BOOL Permit
    );

DWORD
ChangeAppIDLaunchACL (
    LPTSTR AppID,
    LPTSTR Principal,
    BOOL SetPrincipal,
    BOOL Permit
    );

DWORD GetRunAsPassword (
    LPTSTR AppID,
    LPTSTR Password
    );

DWORD SetRunAsPassword (
    LPTSTR AppID,
    LPTSTR Principal,
    LPTSTR Password
    );

DWORD GetRunAsPassword (
    LPTSTR AppID,
    LPTSTR Password
    );

DWORD SetRunAsPassword (
    LPTSTR AppID,
    LPTSTR Password
    );

//
// Internal functions
//

DWORD
CreateNewSD (
    SECURITY_DESCRIPTOR **SD
    );

DWORD
MakeSDAbsolute (
    PSECURITY_DESCRIPTOR OldSD,
    PSECURITY_DESCRIPTOR *NewSD
    );

DWORD
SetNamedValueSD (
    HKEY RootKey,
    LPTSTR KeyName,
    LPTSTR ValueName,
    SECURITY_DESCRIPTOR *SD
    );

DWORD
GetNamedValueSD (
    HKEY RootKey,
    LPTSTR KeyName,
    LPTSTR ValueName,
    SECURITY_DESCRIPTOR **SD,
    BOOL *NewSD
    );

DWORD
ListNamedValueSD (
    HKEY RootKey,
    LPTSTR KeyName,
    LPTSTR ValueName
    );

DWORD
AddPrincipalToNamedValueSD (
    HKEY RootKey,
    LPTSTR KeyName,
    LPTSTR ValueName,
    LPTSTR Principal,
    BOOL Permit
    );

DWORD
RemovePrincipalFromNamedValueSD (
    HKEY RootKey,
    LPTSTR KeyName,
    LPTSTR ValueName,
    LPTSTR Principal
    );

DWORD
GetCurrentUserSID (
    PSID *Sid
    );

DWORD
GetPrincipalSID (
    LPTSTR Principal,
    PSID *Sid
    );

DWORD
CopyACL (
    PACL OldACL,
    PACL NewACL
    );

DWORD
AddAccessDeniedACEToACL (
    PACL *Acl,
    DWORD PermissionMask,
    LPTSTR Principal
    );

DWORD
AddAccessAllowedACEToACL (
    PACL *Acl,
    DWORD PermissionMask,
    LPTSTR Principal
    );

DWORD
RemovePrincipalFromACL (
    PACL Acl,
    LPTSTR Principal
    );

void
ListACL (
    PACL Acl
    );

DWORD
SetAccountRights (
    LPTSTR User,
    LPTSTR Privilege
    );

//
// Utility Functions
//

LPTSTR
SystemMessage (
    LPTSTR szBuffer,
    HRESULT hr
    );

