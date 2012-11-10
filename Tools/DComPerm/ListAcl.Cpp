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

void
ListACL (
    PACL Acl
    )
{
    ACL_SIZE_INFORMATION     aclSizeInfo;
    ACL_REVISION_INFORMATION aclRevInfo;
    ULONG                    i;
    LPVOID                   ace;
    ACE_HEADER               *aceHeader;
    ACCESS_ALLOWED_ACE       *paaace;
    ACCESS_DENIED_ACE        *padace;
    TCHAR                    domainName [256];
    TCHAR                    userName [256];
    DWORD                    nameLength;
    SID_NAME_USE             snu;

    if (!GetAclInformation (Acl,
                            &aclSizeInfo,
                            sizeof (ACL_SIZE_INFORMATION),
                            AclSizeInformation))
    {
        _tprintf (TEXT("Could not get AclSizeInformation"));
        return;
    }

    if (!GetAclInformation (Acl,
                            &aclRevInfo,
                            sizeof (ACL_REVISION_INFORMATION),
                            AclRevisionInformation))
    {
        _tprintf (TEXT("Could not get AclRevisionInformation"));
        return;
    }

    for (i = 0; i < aclSizeInfo.AceCount; i++)
    {
        if (!GetAce (Acl, i, &ace))
            return;

        aceHeader = (ACE_HEADER *) ace;

        if (aceHeader->AceType == ACCESS_ALLOWED_ACE_TYPE)
        {
            paaace = (ACCESS_ALLOWED_ACE *) ace;
            nameLength = 255;
            LookupAccountSid (NULL,
                              &paaace->SidStart,
                              userName,
                              &nameLength,
                              domainName,
                              &nameLength,
                              &snu);

            _tprintf (TEXT("Access permitted to %s\\%s.\n"), domainName, userName);
        } else
        if (aceHeader->AceType == ACCESS_DENIED_ACE_TYPE)
        {
            padace = (ACCESS_DENIED_ACE *) ace;
            nameLength = 255;
            LookupAccountSid (NULL,
                              &padace->SidStart,
                              userName,
                              &nameLength,
                              domainName,
                              &nameLength,
                              &snu);

            _tprintf (TEXT("Access denied to %s\\%s.\n"), domainName, userName);

        }
   }
}
