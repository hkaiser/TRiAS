// TSCrypt.cpp : Implementierung der DLL-Exporte.


// Hinweis: Proxy/Stub-Information
//		Zur Aufnahme des Proxy/Stub-Codes in die Objekt-DLL fügen Sie die Datei 
//		dlldatax.c dem Projekt hinzu.  Stellen Sie sicher, dass vorcompilierte Header
//		für diese Datei deaktiviert sind und fügen Sie _MERGE_PROXYSTUB zu 
//		den Projektdefinitionen hinzu.  
//
//		Wenn Sie WinNT4.0 oder Win95 nicht mit DCOM ausführen,
//		müssen Sie die folgende define-Anweisung aus dlldatax.c entfernen.
//		#define _WIN32_WINNT 0x0400
//
//		Wenn Sie darüber hinaus MIDL ohne den Schalter /Oicf ausführen, 
//		müssen Sie auch die folgende define-Anweisung aus dlldatax.c entfernen.
//		#define USE_STUBLESS_PROXY
//
//		Ändern Sie die benutzerspezifische Build-Regel für TSCrypt.idl durch Hinzufügen
//		folgender Dateien.
//			TSCrypt_p.c
//			dlldata.c
//		Um eine eigene Proxy/Stub-DLL zu erstellen, 
//		führen Sie nmake -f TSCryptps.mk im Projektverzeichnis aus.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "TSCrypt.h"
#include "dlldatax.h"

#define CSO_IMPORT __declspec( dllimport ) 
#include "CryptoSealObjects.h"

#include "TSCrypt_i.c"
#include "TSCryptSvr.h"

#ifdef _MERGE_PROXYSTUB
extern "C" HINSTANCE hProxyDll;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_TSCryptSvr, CTSCryptSvr)
END_OBJECT_MAP()

class CTSCryptApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
protected:
};


CTSCryptApp theApp;


BOOL CTSCryptApp::InitInstance()
{
#ifdef _MERGE_PROXYSTUB
	hProxyDll = m_hInstance;
#endif
	_Module.Init(ObjectMap, m_hInstance);
	return CWinApp::InitInstance();
}

int CTSCryptApp::ExitInstance()
{
	_Module.Term();
	return CWinApp::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// Verwendet, um zu entscheiden, ob die DLL von OLE aus dem Speicher entfernt werden kann

STDAPI DllCanUnloadNow(void)
{
#ifdef _MERGE_PROXYSTUB
	if (PrxDllCanUnloadNow() != S_OK)
		return S_FALSE;
#endif
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Liefert eine Klassenfabrik zurück, um ein Objekt des angeforderten Typs anzulegen

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
#ifdef _MERGE_PROXYSTUB
	if (PrxDllGetClassObject(rclsid, riid, ppv) == S_OK)
		return S_OK;
#endif
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Fügt der Systemregistrierung Einträge hinzu

STDAPI DllRegisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
	HRESULT hRes = PrxDllRegisterServer();
	if (FAILED(hRes))
		return hRes;
#endif
	// Registriert Objekt, Typelib und alle Schnittstellen in Typelib
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Entfernt Einträge aus der Systemregistrierung

STDAPI DllUnregisterServer(void)
{
#ifdef _MERGE_PROXYSTUB
	PrxDllUnregisterServer();
#endif
	_Module.UnregisterServer();
	return S_OK;
}


