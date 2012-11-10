// Klasse, der eine dynamisch angebundene DLL zugeordnet wird -----------------
// File: DLLBIND.HXX

#if !defined(_DLLBIND_HXX)
#define _DLLBIND_HXX

class DLLBind {
private:
	HMODULE _hLib;		// Handle der gebundenen DLL
	string m_strName;

public:
// Konstruktor
	_TRIAS02_ENTRY DLLBind (const char *DLLName, DWORD dwFlags = 0);

// Memberfunktion
	HMODULE &hLib (void) const { return (HMODULE &)_hLib; }
	_TRIAS02_ENTRY FARPROC GetProcAddress (const char *FcnName);
	
// Destruktor
	_TRIAS02_ENTRY ~DLLBind (void);

// sicheres Anlegen einer Instanz
_TRIAS02_ENTRY static DLLBind * CreateInstance (const char *pDLLName, DWORD dwFlags = 0);

	_TRIAS02_ENTRY LPCSTR GetName (void);
};

#endif // _DLLBIND_HXX
