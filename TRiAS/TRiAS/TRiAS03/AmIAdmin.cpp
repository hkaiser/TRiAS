// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.02.2001 10:11:17 
//
// @doc
// @module AmIAdmin.cpp | Definition of the AmIAdministrator function

#include "trias03p.hxx"
#include <funcs03.h>

BOOL AmIAdministrator (void)
{
// Plagerized from Microsoft Knowledge Base article Q118626
HANDLE access_token_handle = NULL;
BYTE buffer[1024];
PTOKEN_GROUPS token_groups_p = (PTOKEN_GROUPS) buffer;
DWORD buffer_size = 0;

	if (!OpenThreadToken (GetCurrentThread(), TOKEN_QUERY, TRUE, &access_token_handle)) {
		if (ERROR_NO_TOKEN != GetLastError())
			return FALSE;

	// retry against process token if no thread token exists
		if (!OpenProcessToken (GetCurrentProcess(), TOKEN_QUERY, &access_token_handle))
			return FALSE;
	}

BOOL success = GetTokenInformation (access_token_handle, TokenGroups, buffer, 1024, &buffer_size);

	CloseHandle (access_token_handle);
	access_token_handle = NULL;
	if (!success)
		return FALSE;

SID_IDENTIFIER_AUTHORITY nt_authority_sid = SECURITY_NT_AUTHORITY;
PSID administrators_sid_p = NULL;

	if (!AllocateAndInitializeSid (&nt_authority_sid, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &administrators_sid_p))
		return FALSE;

// assume that we don't find the admin SID.
	success = FALSE;
	for (UINT x = 0; x < token_groups_p->GroupCount; x++)
	{
		if (EqualSid (administrators_sid_p, token_groups_p->Groups[x].Sid)) {
			success = TRUE;
			break;
		}
	}
	FreeSid (administrators_sid_p);
	return success;
}

