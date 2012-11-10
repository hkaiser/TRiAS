// Klasse, der eine dynamisch angebundene DLL zugeordnet wird -----------------
// File: DLLBINDX.HXX

#if !defined(_DLLBINDX_HXX)
#define _DLLBINDX_HXX

class CDllBindX {
private:
	HMODULE _hLib;		// Handle der gebundenen DLL
	string m_strName;

protected:
	void Init (const char *pcDLLName, DWORD dwFlags = 0);

public:
// Konstruktor
	CDllBindX (const char *pcDLLName);
	CDllBindX (const char *pcDLLName, DWORD dwFlags);

// Memberfunktion
	HMODULE &hLib (void) const { return (HMODULE &)_hLib; }
	FARPROC GetProcAddress (const char *FcnName);
	
// Destruktor
		~CDllBindX (void);

// sicheres Anlegen einer Instanz
static CDllBindX *CreateInstance (const char *pDLLName);
static CDllBindX *CreateInstance (const char *pDLLName, DWORD dwFlags);

	LPCSTR GetName (void) { return m_strName.c_str(); }
};

#endif // _DLLBINDX_HXX
