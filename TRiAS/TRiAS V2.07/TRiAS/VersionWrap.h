///////////////////////////////////////////////////////////////////////////////
// Version.Dll Wrapper 

#if !defined(_VERSIONWRAP_H)
#define _VERSIONWRAP_H

#include <dllbind.hxx>

class CVersionBind :
	public DLLBind 
{
private:
	typedef DWORD (WINAPI *GETFILEVERSIONINFOSIZEPROC)(LPSTR lptstrFilename, LPDWORD lpdwHandle);
	typedef DWORD (WINAPI *GETFILEVERSIONINFOPROC)(LPSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData);
	typedef DWORD (WINAPI *VERQUERYVALUEPROC)(const LPVOID pBlock, LPSTR lpSubBlock, LPVOID *lplpBuffer, PUINT puLen);

	GETFILEVERSIONINFOSIZEPROC m_pGetFileVersionInfoSize;
	GETFILEVERSIONINFOPROC m_pGetFileVersionInfo;
	VERQUERYVALUEPROC m_pVerQueryValue;

	bool m_fIsValid;

public:
		CVersionBind (void);

	DWORD GetFileVersionInfoSize (LPSTR lptstrFilename, LPDWORD lpdwHandle);
	BOOL GetFileVersionInfo (LPSTR lptstrFilename, DWORD dwHandle, DWORD dwLen, LPVOID lpData);
	BOOL VerQueryValue (const LPVOID pBlock, LPSTR lpSubBlock, LPVOID *lplpBuffer, PUINT puLen);

	bool IsValid (void) { return m_fIsValid; }
};

#endif // _VERSIONWRAP_H
