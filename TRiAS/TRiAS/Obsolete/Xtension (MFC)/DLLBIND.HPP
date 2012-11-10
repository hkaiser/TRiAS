// Klasse, der eine dynamisch angebundene DLL zugeordnet wird -----------------
// File: DLLBIND.HXX


#if !defined(_DLLBIND_HXX)
#define _DLLBIND_HXX


class DLLBind {
private:
	HANDLE _hLib;		// Handle der gebundenen DLL

public:
// Konstruktor
		DLLBind (const char *DLLName);

// Memberfunktion
	HANDLE &hLib (void) const { return _hLib; }
	FARPROC GetProcAddress (const char *FcnName);
	
// Destruktor
		~DLLBind (void);
};

#endif // _DLLBIND_HXX
