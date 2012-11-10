// Registrieren und Unregistrieren einer TRiAS-Erweiterung --------------------
// File: CEXTREG.CXX

#include "trias03p.hxx"

#include <cextreg.hxx>

#if defined(WIN32)
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

typedef HRESULT (STDAPICALLTYPE *CTLREGPROC)(void) ; //see COMPOBJ.H

CExtReg::CExtReg (CVersionBind &rVer, string &PathName)
	: m_rVer(rVer)
{
	m_strPathName = PathName;
}

CExtReg::~CExtReg (void)
{
}

bool CExtReg::Register (void)
{
bool bResult = false;

	if (SupportsSelfRegister()) {  
	HINSTANCE hModule = ::LoadLibrary (m_strPathName.c_str());
	
		if (LOADLIBRARY_FAILED(hModule)) {
#if defined(_DEBUG)
		DWORD dwError = GetLastError();
		char cbBuffer[_MAX_PATH];

			FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS, 
				NULL, dwError, 0, cbBuffer, _MAX_PATH, NULL);
#endif // _DEBUG
			return false;
		}
				
	CTLREGPROC DLLRegisterServer = (CTLREGPROC)::GetProcAddress (hModule, TEXT("DllRegisterServer"));
	
		if (DLLRegisterServer == NULL) 
			DLLRegisterServer = (CTLREGPROC)::GetProcAddress (hModule, TEXT("DLLREGISTERSERVER"));

		if (DLLRegisterServer != NULL) {
		HRESULT regResult = DLLRegisterServer();

			bResult = (regResult == NOERROR); 
		}		
		::FreeLibrary (hModule);
	}

return bResult;	
}

bool CExtReg::Unregister (void)
{
bool bResult = false;

	if (SupportsSelfRegister()) {                                    
	HMODULE hModule = ::LoadLibrary (m_strPathName.c_str());

		if (LOADLIBRARY_FAILED(hModule)) return false;
				
	CTLREGPROC DllUnregisterServer = (CTLREGPROC)::GetProcAddress (hModule, TEXT("DllUnregisterServer"));
		
		if (DllUnregisterServer == NULL) 
			DllUnregisterServer = (CTLREGPROC)::GetProcAddress (hModule, TEXT("DLLUNREGISTERSERVER"));

		if (DllUnregisterServer != NULL) {
		HRESULT regResult = DllUnregisterServer();

			bResult = (regResult == NOERROR); 
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

// Get the size of the version information.
	uiInfoSize = m_rVer.GetFileVersionInfoSize ((LPTSTR)m_strPathName.c_str(), &handle);
	if (uiInfoSize == 0) return false;

// Allocate a buffer for the version information.
char *pbData = NULL;

	ATLTRY(pbData = new char[uiInfoSize]);
	if (NULL == pbData) return false;

// Fill the buffer with the version information.
	bResult = m_rVer.GetFileVersionInfo ((LPTSTR)m_strPathName.c_str(), handle, uiInfoSize, pbData);
	if (!bResult) goto NastyGoto;

// Get the translation information.
	strcpy (szName, TEXT("\\VarFileInfo\\Translation"));
	bResult = m_rVer.VerQueryValue (pbData, szName, (void **)&lpBuffer, &uiVerSize);
	if (!bResult || uiVerSize == 0) goto NastyGoto;

// Build the path to the key OLESelfRegister using the translation information.
	wsprintf (szName, TEXT("\\StringFileInfo\\%04hX%04hX\\TRiASSelfRegister"), LOWORD(*lpBuffer), HIWORD(*lpBuffer));

// Search for the key.
	bResult = m_rVer.VerQueryValue (pbData, szName, (void **)&lpBuffer, &uiSize);

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
