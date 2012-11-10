// Wrapper für CTL3D-Funktionen -----------------------------------------------
// CTL3DW.CPP

#include "tfrmpre.hxx"
#include <ctl3d.h>

HINSTANCE s_hInstCtl3d = NULL;

#if !defined(WIN32)
#define CTL3D_MODULENAME	TEXT("CTL3DV2.DLL")
#define LOADLIBRARY_FAILED(x) (x <= HINSTANCE_ERROR)
#else
#define CTL3D_MODULENAME	TEXT("CTL3D32.DLL")
#define LOADLIBRARY_FAILED(x) (x == 0)
#endif // WIN32

///////////////////////////////////////////////////////////////////////////////
// Ctl3dSubclassDlg
typedef BOOL WINAPI CTL3DSUBCLASSDLGPROC (HWND, WORD);
typedef CTL3DSUBCLASSDLGPROC * CTL3DSUBCLASSDLGPTR;

extern "C"
BOOL WINAPI Ctl3dSubclassDlg(HWND hWnd, WORD wMode)
{
	if (NULL == s_hInstCtl3d) return false;

static CTL3DSUBCLASSDLGPTR F = NULL;

	if (NULL == F) {
		F = (CTL3DSUBCLASSDLGPTR)GetProcAddress (s_hInstCtl3d, "Ctl3dSubclassDlg");
		if (NULL == F) return false;
	}

return F(hWnd, wMode);
}

///////////////////////////////////////////////////////////////////////////////
// Ctl3dEnabled
typedef BOOL WINAPI CTL3DENABLEDPROC (void);
typedef CTL3DENABLEDPROC * CTL3DENABLEDPTR;

extern "C"
BOOL WINAPI Ctl3dEnabled(void)
{
	if (NULL == s_hInstCtl3d) return false;

static CTL3DENABLEDPTR F = NULL;

	if (NULL == F) {
		F = (CTL3DENABLEDPTR)GetProcAddress (s_hInstCtl3d, "Ctl3dEnabled");
		if (NULL == F) return false;
	}

return F();
}

///////////////////////////////////////////////////////////////////////////////
// Ctl3dColorChange
typedef BOOL WINAPI CTL3DCOLORCHANGEPROC (void);
typedef CTL3DCOLORCHANGEPROC * CTL3DCOLORCHANGEPTR;

extern "C"
BOOL WINAPI Ctl3dColorChange(void)
{
	if (NULL == s_hInstCtl3d) return false;

static CTL3DCOLORCHANGEPTR F = NULL;

	if (NULL == F) {
		F = (CTL3DCOLORCHANGEPTR)GetProcAddress (s_hInstCtl3d, "Ctl3dColorChange");
		if (NULL == F) return false;
	}

return F();
}

///////////////////////////////////////////////////////////////////////////////
// Ctl3dAutoSubclass
typedef BOOL WINAPI CTL3DAUTOSUBCLASSPROC (HINSTANCE);
typedef CTL3DAUTOSUBCLASSPROC * CTL3DAUTOSUBCLASSPTR;

extern "C"
BOOL WINAPI Ctl3dAutoSubclass(HINSTANCE hInst)
{
	if (NULL == s_hInstCtl3d) return false;

static CTL3DAUTOSUBCLASSPTR F = NULL;

	if (NULL == F) {
		F = (CTL3DAUTOSUBCLASSPTR)GetProcAddress (s_hInstCtl3d, "Ctl3dAutoSubclass");
		if (NULL == F) return false;
	}

return F(hInst);
}

///////////////////////////////////////////////////////////////////////////////
// Ctl3dRegister
typedef BOOL WINAPI CTL3DREGISTERPROC (HINSTANCE);
typedef CTL3DREGISTERPROC * CTL3DREGISTERPTR;

extern "C"
BOOL WINAPI Ctl3dRegister(HINSTANCE hInst)
{
	if (IsWin40()) return false;

// zuerst DLL laden
	if (NULL == s_hInstCtl3d) {
		s_hInstCtl3d = LoadLibrary (CTL3D_MODULENAME);
		if (LOADLIBRARY_FAILED(s_hInstCtl3d))
			s_hInstCtl3d = NULL;
	}

	if (NULL == s_hInstCtl3d) return false;

// eigentliche Funktion rufen
static CTL3DREGISTERPTR F = NULL;

	if (NULL == F) {
		F = (CTL3DREGISTERPTR)GetProcAddress (s_hInstCtl3d, "Ctl3dRegister");
		if (NULL == F) return false;
	}

return F(hInst);
}

///////////////////////////////////////////////////////////////////////////////
// Ctl3dUnregister
typedef BOOL WINAPI CTL3DUNREGISTERPROC (HINSTANCE);
typedef CTL3DUNREGISTERPROC * CTL3DUNREGISTERPTR;

extern "C"
BOOL WINAPI Ctl3dUnregister(HINSTANCE hInst)
{
	if (NULL == s_hInstCtl3d) return false;

// eigentliche Funktion rufen
static CTL3DUNREGISTERPTR F = NULL;

	if (NULL == F) {
		F = (CTL3DUNREGISTERPTR)GetProcAddress (s_hInstCtl3d, "Ctl3dUnregister");
		if (NULL == F) return false;
	}

BOOL fResult = F(hInst);

// wieder alles abmelden und entladen
	FreeLibrary (s_hInstCtl3d);
	s_hInstCtl3d = NULL;

return fResult;
}

