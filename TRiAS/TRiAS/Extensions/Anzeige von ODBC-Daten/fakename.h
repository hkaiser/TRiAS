/////////////////////////////////////
// fakename.cpp
// Routinen zum ändern des angezeigten Programmnamens 

extern char g_cbTRiAS[];				// the cached AppName
//extern const char g_cbCopyrightName[];	// = TEXT("InterTRiAS");	// a defaultval
//extern const char g_cbTRiASName[];		// = TEXT("TRiASName");	// where i'll get the Name from
//extern const char g_cbRegConfig[];		//= TEXT("Software\\TRiAS\\InterTRiAS\\Config"); // c above

void InitFakeName();					// Reading the val
CString __cdecl FakeName (UINT resID);
CString __cdecl FakeName (LPCSTR pcTempl);
CString __cdecl FakeName (CWnd* pWnd);	// den WindowText ändern
