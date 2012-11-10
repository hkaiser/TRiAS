// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 09.11.2000 21:26:54 
//
// @doc
// @module EsnecilExt.cpp | Definition of the <c CEsnecilExt> class

#include "StdAfx.h"

#include <time.h>

#if !defined(_NO_DELAYLOAD_CRP32DLL)
#include <DelayImp.h>
#endif // !defined(_NO_DELAYLOAD_CRP32DLL)

#include <d_lib/d_lib.h>

#undef FUNCTYPE
#include <CrypKey/CrypKey.h>

#include <Esnecil.h>
#include <EsnecilExt.h>

namespace wait {
	///////////////////////////////////////////////////////////////////////////////
	// CEierUhr
	class CWaitCursor
	{
	// Construction/Destruction
	public:
		CWaitCursor() : m_hCursor(::SetCursor(::LoadCursor(NULL, IDC_WAIT))) {}
		~CWaitCursor() { ::SetCursor(m_hCursor); }

	private:
		HCURSOR m_hCursor;
	};
}

///////////////////////////////////////////////////////////////////////////////
// Registrierkeys et.al. für TRiAS.exe
const unsigned short MASTER_KEY[] = { 0xACDB, 0x57C4, 0xB351, 0x8E02, 0xE453, 0x27F9, 0x05E3, 0x27B0, 0xDAE6, 0x90F5, 0x97EE, };
const unsigned short USER_KEY[] = { 0xD519, 0x52C3, 0xD185, 0x1513, 0xA827, 0xA361, 0x0A, };
const unsigned long COMPANY_NUM = 7956670UL;
const unsigned long PASS_NUM = 1625877072UL;

///////////////////////////////////////////////////////////////////////////////
// Konstruktor, Initialisierung
CEsnecilExt::CEsnecilExt() :
	m_ulOptions(0), m_fIsValid(false), m_iAuthOpt(0), m_iNumAllowed(0), 
	m_iNumUsed(0), m_iCopies(0), m_iLevel(0), m_ulStartDate(0)
{
	FInit(true);
}

CEsnecilExt::~CEsnecilExt()
{
	EndCrypkey();
#if !defined(_NO_DELAYLOAD_CRP32DLL)
	__FUnloadDelayLoadedDLL("crp32dll.dll");		// unload crypkey dll
#endif // !defined(_NO_DELAYLOAD_CRP32DLL)
}

///////////////////////////////////////////////////////////////////////////////
// Initialisierung
bool CEsnecilExt::FInit(bool fFullInit)
{
	m_fIsValid = false;
	
	try {
	wait::CWaitCursor wait;
	os_string strPath, strMasterKey, strUserKey;

		if (fFullInit) {
			if (GetLicensePath (strPath) && GetMasterKey(strMasterKey) && GetUserKey(strUserKey)) {
			int iReturn = InitCrypkey((char *)strPath.c_str(), (char *)strMasterKey.c_str(), (char *)strUserKey.c_str(), 0, 15*60);

				D_OUTF(3, "TRiAS: Lizenz: InitCrypkey returns: %ld", iReturn);
				if (0 != iReturn) {
					D_OUTF3(3, 
						"TRiAS: Lizenz: Initialization Failure %s", ExplainErr (EXP_INIT_ERR, iReturn),
						"(%d)", iReturn, " for %s", strPath.c_str());
					return false;
				}
			} 
			else {
				D_OUTF(3, "TRiAS: Lizenz: Could not retrieve path of license file: %s\n", "TRiAS.exe");
				return false;
			}
		}
		
	// Autorisierung
	int iReturn = ::GetAuthorization(&m_ulOptions, 0);		// check authorization, use up 0 run

		D_OUTF2(3, 
			"TRiAS: Lizenz: GetAuthorisation returned: %ld, ", iReturn, 
			"Options: %lx", m_ulOptions);

		m_fIsValid = (iReturn == 0 && CheckChallenge()) ? true : false;
		
	// SiteCode abfragen
		m_strSiteCode = ::GetSiteCode2();
		D_OUTF(3, "TRiAS: Lizenz: GetSiteCode returned: %s", m_strSiteCode.c_str());

	// sonstige Authorisierungen abfragen
		if (m_fIsValid) {
			if (GRI_OK != ::GetRestrictionInfo(&m_iAuthOpt, &m_ulStartDate, &m_iNumAllowed, &m_iNumUsed))
				m_fIsValid = false;
			m_iCopies = ::GetNumCopies();
			m_iLevel = ::GetLevel(CKIOPTION_MAXCOUNT);
		}
	} 
	catch (...) {
		D_OUTF(3, "TRiAS: Lizenz: Unexpected error in %s\n", "CEsencilExt::ctor");
		return false;
	}
	return m_fIsValid;
}

///////////////////////////////////////////////////////////////////////////////
// Methoden und Helper
bool CEsnecilExt::GetLicensePath(os_string &rstr)
{
CRegKey key;
char cbBuffer[_MAX_PATH];
DWORD dwLen = sizeof(cbBuffer);

	if (ERROR_SUCCESS == key.Open (HKEY_LOCAL_MACHINE, "SOFTWARE") &&
		ERROR_SUCCESS == key.Open (key, REG_COMPANY_KEY) &&
		ERROR_SUCCESS == key.QueryValue(cbBuffer, "License", &dwLen))
	{
		D_OUTF(3, "TRiAS: Lizenz: LizencePath: %s", cbBuffer);
		rstr = cbBuffer;
		return true;
	}

	D_OUTF(3, "TRiAS: Lizenz: LizencePath not defined", cbBuffer);
	return false;
}

bool CEsnecilExt::GetMasterKey(os_string &rstr)
{
char cbBuffer[64] = { '\0' };

	for (int i = 0; i < 11; ++i) {
	char cbVal[8];

		wsprintf (cbVal, "%04lX", MASTER_KEY[i]);
		strcat (cbBuffer, cbVal);
		if (i < 10)
			strcat (cbBuffer, " ");
	}

	D_OUTF(3, "TRiAS: Lizenz: MasterKey: %s", cbBuffer);
	rstr = cbBuffer;
	return true;
}

bool CEsnecilExt::GetUserKey(os_string &rstr)
{
char cbBuffer[64] = { '\0' };
char cbVal[8];

	for (int i = 0; i < 6; ++i) {
		wsprintf (cbVal, "%04lX", USER_KEY[i]);
		strcat (cbBuffer, cbVal);
		strcat (cbBuffer, " ");
	}
	wsprintf (cbVal, "%02lX", USER_KEY[6]);
	strcat (cbBuffer, cbVal);

	D_OUTF(3, "TRiAS: Lizenz: UserKey: %s", cbBuffer);
	rstr = cbBuffer;
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Integritaät der Lizensierung prüfen
namespace {
	long Challenge32(long companyNum, long passNumDiv2, long random1, long random2)
	{
	long ret = 1;

		for(int i = 2; i < 11; ++i)
		{
			ret = ret%32769 * ( (random1/i)%32769 + (companyNum/i)%32769);
			ret = ret%32769 * ( (random2/i)%32769 + (passNumDiv2/i)%32769);
		}
		return ret;
	}
}

bool CEsnecilExt::CheckChallenge()
{
// generate some random numbers - this can be done any way you like
ULONG random1 = time(NULL);
ULONG random2 = random1 * time(NULL);
ULONG result1 = Challenge32 (COMPANY_NUM, PASS_NUM/2, random1, random2);
ULONG result2 = CKChallenge32 (random1, random2);

	return (result1 == result2) ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
// Installations-Datum
const char *CEsnecilExt::GetInstallDate() 
{
time_t ulTime = m_ulStartDate-2209075200;
struct tm *ptm = gmtime (&ulTime);

	if (NULL != ptm) 
		m_strInstallDate = asctime(ptm);
	else 
		m_strInstallDate = _T("Predates 01-01-70 00:00:00");	// vor 1970!

	return m_strInstallDate.c_str(); 
}

///////////////////////////////////////////////////////////////////////////////
// neu authorisieren
bool CEsnecilExt::Authorize(LPCSTR pcNewKey)
{
int iResult = SaveSiteKey (const_cast<char *>(pcNewKey));

	if (SITE_KEY_OK != iResult) 
		return false;
	return FInit();		// neu initialisieren
}

