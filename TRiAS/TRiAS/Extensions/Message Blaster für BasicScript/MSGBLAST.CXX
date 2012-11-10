// Messages für Basic abfangen und Weiterleiten
// File: MSGBLAST.CXX

#include "StdAfx.h"

#include "resource.h"		// ResourceKonstanten
#include "version.h"

#include <initguid.h>		// nur im einem Module notwendig
#include <bscrguid.h>
#include "Msgguid.h"

#include "MsgMap.h"
#include "MouseAction.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// NEU: An Stelle der Funktionen NewExtension und GetExtensionCLSID muß die 
// Erweiterung jetzt in der ATL ObjectMap eingetragen werden (zusammen 
// mit allen anderen ATL-Objekten)
BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_MsgBlaster, CMsgBlastExt)
	OBJECT_ENTRY(CLSID_MessageMap, CMessageMap)
	OBJECT_ENTRY(CLSID_MouseAction, CMouseAction)
END_OBJECT_MAP()

// mit der folgenden Funktion wird die ObjectMap in den ClassFactory-Mechanismus
// dieser Erweiterung eingebunden
_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// liefert ObjectMap
}

///////////////////////////////////////////////////////////////////////////////
// Registrierung/DeRegistrierung
BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
		return ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_MsgBlaster, 
				TEXT("TRiAS.MsgBlaster.1"), IDS_LONGCLASSNAME,
				MSGBLAST_MAJORVERSION, MSGBLAST_MINORVERSION,
				EFPreLoad);
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_MsgBlaster, 
					      TEXT("TRiAS.MsgBlaster.1"));
	}
	return true;	// alles ok
}


// Konstruktor der ExtensionKlasse --------------------------------------------
CMsgBlastExt::CMsgBlastExt (void)
{
}

STDMETHODIMP_(BOOL) CMsgBlastExt::InitExtension (short iMode) 
{
	if (!CTriasExtension::InitExtension(iMode))
		return false;

	ATLTRY(m_Mouse = WMouseAction(CLSID_MouseAction));
	RegisterBScriptExtension();
	return true;
}

STDMETHODIMP_(BOOL) CMsgBlastExt::UnLoadExtension (void)
{
	m_Mouse.Assign(NULL);
	m_Sink.Assign(NULL);
	return CTriasExtension::UnLoadExtension();
}

///////////////////////////////////////////////////////////////////////////////
//
bool CMsgBlastExt::RegisterBScriptExtension (void)
{
	COM_TRY {
	// diese Erweiterung als public BasicExtension registrieren
		m_Sink = WExtendBScript (CLSID_MacroScriptExtension);
		THROW_FAILED_HRESULT(m_Sink -> RegisterExtModule (g_pDLLName));

	} COM_CATCH_RETURN(false);
	return true;
}

