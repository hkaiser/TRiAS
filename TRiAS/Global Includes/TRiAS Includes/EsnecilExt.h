// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 09.11.2000 20:40:03 
//
// @doc
// @module EsnecilExt.h | Declaration of the <c CEsnecilExt> class

#if !defined(_ESNECILEXT_H__1D8C6BD3_C88C_472A_8136_4D34E3C7A8B9__INCLUDED_)
#define _ESNECILEXT_H__1D8C6BD3_C88C_472A_8136_4D34E3C7A8B9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Klasse für Zugriff auf Crypkey SDK Funktionen
class CEsnecilExt
{
public:
	CEsnecilExt();
	~CEsnecilExt();

	int GetAuthOpt() { return m_fIsValid ? m_iAuthOpt : -1; }
	int GetNumAllowed() { return m_fIsValid ? m_iNumAllowed : 0; }
	int GetNumUsed() { return m_fIsValid ? m_iNumUsed : 0; }
	int GetNumCopies() { return m_fIsValid ? m_iCopies : 0; }
	int GetLevel() { return m_fIsValid ? m_iLevel : 0; }
	const char *GetSiteCode() { return m_strSiteCode.c_str(); }
	ULONG GetFullOptions() { return m_ulOptions; }
	const char *GetInstallDate();
	
	bool Authorize(LPCSTR pcNewKey);
	
	bool operator! () { return !m_fIsValid; }
	operator bool () { return !!(*this); }
	bool IsValid() { return bool(*this); }
	
protected:
	bool FInit(bool fFullInit = false);

	bool GetLicensePath (os_string &rstr);
	bool GetMasterKey (os_string &rstr);
	bool GetUserKey (os_string &rstr);

	bool CheckChallenge();

private:
	ULONG m_ulOptions;
	os_string m_strSiteCode;
	os_string m_strInstallDate;
	bool m_fIsValid;

	int m_iAuthOpt;
	int m_iNumAllowed;
	int m_iNumUsed;
	int m_iCopies;
	int m_iLevel;
	ULONG m_ulStartDate;
};

///////////////////////////////////////////////////////////////////////////////
// Libraries einbinden
#if defined(_DEBUG)
#pragma comment(lib, "esnecild.lib")
#else
#pragma comment(lib, "esnecil.lib")
#endif // defined(_DEBUG)

#pragma comment(lib, "crp32dll.lib")

#endif // !defined(_ESNECILEXT_H__1D8C6BD3_C88C_472A_8136_4D34E3C7A8B9__INCLUDED_)
