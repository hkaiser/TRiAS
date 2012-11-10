// Registrieren und Unregistrieren einer TRiAS-Erweiterung --------------------
// File: CEXTREG.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <FormatString.h>
#include <cextreg.hxx>
#include <funcs03.h>

#if !defined(WIN16)
#define LOADLIBRARY_FAILED(x) (x == 0)
#else
#include <tchar.h>
#include <ver.h>

#define LOADLIBRARY_FAILED(x) (x <= HINSTANCE_ERROR)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char g_pDLLName[_MAX_PATH];

typedef HRESULT (STDAPICALLTYPE *CTLREGPROC)(void) ; //see COMPOBJ.H

CExtReg::CExtReg (CVersionBind &rVer, string &PathName, int fh)
	: m_rVer(rVer), m_fh(fh)
{
	m_strPathName = PathName;
}

CExtReg::~CExtReg (void)
{
}

namespace {
// unsere Fehlercodes für die Selbstregistrieren
	#define SELFREG_E_FIRST		MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x0200)
	#define SELFREG_E_LAST		MAKE_SCODE(SEVERITY_ERROR,   FACILITY_ITF, 0x020F)
	#define SELFREG_S_FIRST		MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_ITF, 0x0200)
	#define SELFREG_S_LAST		MAKE_SCODE(SEVERITY_SUCCESS, FACILITY_ITF, 0x020F)
	#define SELFREG_E_TYPELIB	(SELFREG_E_FIRST+0)		// failed to register/unregister type library
	#define SELFREG_E_CLASS		(SELFREG_E_FIRST+1)		// failed to register/unregister class

	BOOL ResultIsError(HRESULT regResult)
	{
		if (S_OK == regResult)
			return FALSE;

		if (!AmIAdministrator() && 
			(E_ACCESSDENIED == regResult || TYPE_E_REGISTRYACCESS == regResult || 
			 SELFREG_E_TYPELIB == regResult || SELFREG_E_CLASS == regResult)) 
		{
		// wenn man nicht Administrator ist, dann darf verschiedenstes fehlschlagen
			return FALSE;
		}
		return TRUE;
	}
}

bool CExtReg::Register (void)
{
bool bResult = false;
string strVersion (m_strFileVersion.size() > 0 ? m_strFileVersion.c_str() : "<?version?>");
string strOut;
ResourceFile RF (g_pDLLName);

	if (SupportsSelfRegister()) {  
	// #HK990614 work around WinNT4 LoadProcess bug
	char szModuleShort[_MAX_PATH];
	string strLong = string(m_strPathName).c_str();
	int cbShortName = GetShortPathName (strLong.c_str(), szModuleShort, _MAX_PATH);
	LPCSTR pcModule = NULL;

		if (cbShortName == _MAX_PATH)
			return false;
		pcModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? strLong.c_str() : szModuleShort;

	HINSTANCE hModule = ::LoadLibrary (pcModule);
	
		if (LOADLIBRARY_FAILED(hModule)) {
			if (HFILE_ERROR != m_fh) {
			DWORD dwError = GetLastError();
			char cbBuffer[_MAX_PATH];

				FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, 
					NULL, dwError, 0, cbBuffer, _MAX_PATH, NULL);

			ResString resLoadFailed (ResID (IDS_LOADLIBRARYFAILED, &RF), 64);

				Format (strOut, resLoadFailed, m_strPathName.filename().c_str(), strVersion.c_str(), dwError, cbBuffer);
				_lwrite (m_fh, strOut.c_str(), strOut.size());
			}
			return false;
		}
				
	CTLREGPROC DLLRegisterServer = (CTLREGPROC)::GetProcAddress (hModule, TEXT("DllRegisterServer"));
	
		if (DLLRegisterServer == NULL) 
			DLLRegisterServer = (CTLREGPROC)::GetProcAddress (hModule, TEXT("DLLREGISTERSERVER"));

	HRESULT regResult = E_FAIL;

		if (DLLRegisterServer != NULL) {
			try {
				regResult = DLLRegisterServer();
				bResult = !ResultIsError(regResult); 
			} catch (...) {
			// GP oä
				regResult = DISP_E_EXCEPTION;		// Exception occured
				bResult = FALSE;
			}

			if (HFILE_ERROR != m_fh) {
				if (bResult) {
				ResString resLoadFailed (ResID (IDS_SELFREGISTERSUCCEEDED, &RF), 64);

					Format (strOut, resLoadFailed, m_strPathName.filename().c_str(), strVersion.c_str());
					_lwrite (m_fh, strOut.c_str(), strOut.size());
				} else {
				ResString resLoadFailed (ResID (IDS_SELFREGISTERFAILED, &RF), 64);
				char cbBuffer[_MAX_PATH];

					FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, 
						NULL, regResult, 0, cbBuffer, _MAX_PATH, NULL);

					Format (strOut, resLoadFailed, m_strPathName.filename().c_str(), strVersion.c_str(), regResult, cbBuffer);
					_lwrite (m_fh, strOut.c_str(), strOut.size());
				}
			}
		} else {
		ResString resLoadFailed (ResID (IDS_ENTRYPOINTNOTFOUND, &RF), 64);

			Format (strOut, resLoadFailed, m_strPathName.filename().c_str(), strVersion.c_str());
			_lwrite (m_fh, strOut.c_str(), strOut.size());
		}
		::FreeLibrary (hModule);
	} 
	else if (HFILE_ERROR != m_fh) {
	ResString resLoadFailed (ResID (IDS_NOSELFREGISTER, &RF), 64);

		Format (strOut, resLoadFailed, m_strPathName.filename().c_str(), strVersion.c_str());
		_lwrite (m_fh, strOut.c_str(), strOut.size());
	}
	return bResult;	
}

bool CExtReg::Unregister (void)
{
bool bResult = false;

	if (SupportsSelfRegister()) {                                    
	// #HK990614 work around WinNT4 LoadProcess bug
	char szModuleShort[_MAX_PATH];
	string strLong = string(m_strPathName).c_str();
	int cbShortName = GetShortPathName (strLong.c_str(), szModuleShort, _MAX_PATH);
	LPCSTR pcModule = NULL;

		if (cbShortName == _MAX_PATH)
			return false;
		pcModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? strLong.c_str() : szModuleShort;

	HINSTANCE hModule = ::LoadLibrary (pcModule);

		if (LOADLIBRARY_FAILED(hModule)) return false;
				
	CTLREGPROC DllUnregisterServer = (CTLREGPROC)::GetProcAddress (hModule, TEXT("DllUnregisterServer"));
		
		if (DllUnregisterServer == NULL) 
			DllUnregisterServer = (CTLREGPROC)::GetProcAddress (hModule, TEXT("DLLUNREGISTERSERVER"));

		if (DllUnregisterServer != NULL) {
		HRESULT regResult = S_OK;
		
			try {
				regResult = DllUnregisterServer();
				bResult = !ResultIsError(regResult); 
			} catch (...) {
				bResult = FALSE;
			}
		}		
		FreeLibrary (hModule);
	}                                     
	return bResult;	
} 

bool CExtReg::SupportsSelfRegister (void)
{
bool bResult = false;
DWORD  handle;
DWORD  uiInfoSize;
UINT  uiVerSize;
UINT  uiSize;
DWORD *lpBuffer;
char szName[128];

// #HK990614 work around WinNT4 LoadProcess bug
char szModuleShort[_MAX_PATH];
string strLong = string(m_strPathName).c_str();
int cbShortName = GetShortPathName (strLong.c_str(), szModuleShort, _MAX_PATH);
LPCSTR pcModule = NULL;

	if (cbShortName == _MAX_PATH)
		return false;
	pcModule = (cbShortName == 0 || cbShortName == ERROR_INVALID_PARAMETER) ? strLong.c_str() : szModuleShort;

// Get the size of the version information.
	uiInfoSize = m_rVer.GetFileVersionInfoSize ((LPSTR)pcModule, &handle);
	if (uiInfoSize == 0) return false;

// Allocate a buffer for the version information.
char *pbData = NULL;

	ATLTRY(pbData = new char[uiInfoSize]);
	if (NULL == pbData) return false;

// Fill the buffer with the version information.
	bResult = m_rVer.GetFileVersionInfo ((LPSTR)pcModule, handle, uiInfoSize, pbData);
	if (!bResult) goto NastyGoto;

// Get the translation information.
	strcpy (szName, TEXT("\\VarFileInfo\\Translation"));
	bResult = m_rVer.VerQueryValue (pbData, szName, (void **)&lpBuffer, &uiVerSize);
	if (!bResult || uiVerSize == 0) goto NastyGoto;

// Build the path to the key OLESelfRegister using the translation information.
	wsprintf (szName, TEXT("\\StringFileInfo\\%04hX%04hX\\TRiASSelfRegister"), LOWORD(*lpBuffer), HIWORD(*lpBuffer));

// Search for the key.
DWORD *lpSelfReg;

	bResult = m_rVer.VerQueryValue (pbData, szName, (void **)&lpSelfReg, &uiSize);

// Search for the FileVersion key
DWORD *lpFileVer;

	wsprintf (szName, TEXT("\\StringFileInfo\\%04hX%04hX\\FileVersion"), LOWORD(*lpBuffer), HIWORD(*lpBuffer));
	if (m_rVer.VerQueryValue (pbData, szName, (void **)&lpFileVer, &uiSize))
		m_strFileVersion = reinterpret_cast<char *>(lpFileVer);

NastyGoto:
	delete [] pbData;
	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
// Versio.DLL binden
CVersionBind::CVersionBind (void)
	: DLLBind (TEXT("VERSION.DLL")), m_fIsValid(false)
{
	if (NULL == hLib()) return;		// Initialisierungs-Fehler

	m_pGetFileVersionInfoSize = (GETFILEVERSIONINFOSIZEPROC)GetProcAddress (TEXT("GetFileVersionInfoSizeA"));;
	m_pGetFileVersionInfo = (GETFILEVERSIONINFOPROC)GetProcAddress (TEXT("GetFileVersionInfoA"));;
	m_pVerQueryValue = (VERQUERYVALUEPROC)GetProcAddress (TEXT("VerQueryValueA"));;

	if (NULL != m_pGetFileVersionInfoSize &&
		NULL != m_pGetFileVersionInfo &&
		NULL != m_pVerQueryValue)
	{
		m_fIsValid = true;
	}
}

DWORD CVersionBind::GetFileVersionInfoSize (LPSTR lptstrFilename, LPDWORD lpdwHandle)
{
	TX_ASSERT(NULL != m_pGetFileVersionInfoSize);
	return m_pGetFileVersionInfoSize (lptstrFilename, lpdwHandle);
}

BOOL CVersionBind::GetFileVersionInfo (LPSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData)
{
	TX_ASSERT(NULL != m_pGetFileVersionInfo);
	return m_pGetFileVersionInfo (lptstrFilename, dwHandle, dwLen, lpData);
}

BOOL CVersionBind::VerQueryValue (const LPVOID pBlock, LPSTR lpSubBlock, LPVOID *lplpBuffer, PUINT puLen)
{
	TX_ASSERT(NULL != m_pVerQueryValue);
	return m_pVerQueryValue (pBlock, lpSubBlock, lplpBuffer, puLen);
}
