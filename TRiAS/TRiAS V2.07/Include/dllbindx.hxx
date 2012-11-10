// Klasse, der eine dynamisch angebundene DLL zugeordnet wird -----------------
// File: DLLBINDX.HXX

#if !defined(_DLLBINDX_HXX)
#define _DLLBINDX_HXX

class CDllBindX {
private:
	HMODULE _hLib;		// Handle der gebundenen DLL
	string m_strName;

public:
// Konstruktor
		CDllBindX (const char *DLLName);

// Memberfunktion
	HMODULE &hLib (void) const { return (HMODULE &)_hLib; }
	FARPROC GetProcAddress (const char *FcnName);
	
// Destruktor
		~CDllBindX (void);

// sicheres Anlegen einer Instanz
static CDllBindX * CreateInstance (const char *pDLLName);

	LPCSTR GetName (void) { return m_strName.c_str(); }
};

#endif // _DLLBINDX_HXX
