///////////////////////////////////////////////////////////////////////////////
// WinMM für PlaySound binden

#if !defined(_WINMMWRAP_H)
#define _WINMMWRAP_H

#include <dllbind.hxx>

class CWinMMBind :
	public DLLBind 
{
private:
	typedef BOOL (WINAPI *PLAYSOUNDPROC)(LPCSTR pszSound, HMODULE hmod, DWORD fdwSound);

	PLAYSOUNDPROC m_pPlaySound;
	bool m_fIsValid;

public:
		CWinMMBind (void);

	BOOL PlaySound (LPCSTR pszSound, HMODULE hmod, DWORD fdwSound);
	bool IsValid (void) { return m_fIsValid; }
};

#endif // _WINMMWRAP_H
