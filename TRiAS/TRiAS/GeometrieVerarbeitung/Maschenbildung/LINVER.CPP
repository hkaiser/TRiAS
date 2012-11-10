/* 
	File: LINVER.CPP (Version für MFC 4.2)
	Allgemeine Schnittstelle zu TRiAS.

	Erarbeitet: J. Benkenstein						Stand vom 12.09.1996
*/

#include "pheader.h"		// vorübersetzte Header
#include "resource.h"		// RessourceKonstanten

#include <xtsnaux.hxx>		// ExtOleRegisterClass () u.a.
#include <registrx.hxx>		// CClassesRoot	

//	GUID-Header
#include <xtsnguid.h>
#include <triashelper.h>
#include "linaguid.h"
#include "rsltguid.h"		// CLSID_ResultPropAction
#include "doppguid.h"		// CLSID_FindDoubledObjects
#include "verguid.h"
#include "linvguid.h"
#include "version.h"

#include "linver.hpp"		// zugeh. Header	


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
EXTERN_C const IID IID_ICoordTransformInit = {0x0BDC3C1B,0x503F,0x11d1,{0x96,0xF0,0x00,0xA0,0x24,0xD6,0xF5,0x82}};

// globale Variablen
extern const char ExtensionName [] = "TRiAS.LinVerExtension.1";
//char const RegistryDir [] = "TRiAS.Application.2\\TRiASEx\\PropertyActions\\";



///////////////////////////////////////////////////////////////////////////////////////////////
// NEU: Die folgende Funktion KANN vom Nutzer bereitgestellt werden, wenn eine TypeLib
// registriert werden soll. Auch die TypeLib muß einen eigenen GUID besitzen !
BOOL GetTypeLibGUID (GUID &guidTLib)
{
	memcpy (&guidTLib, &LIBID_LinienVerfolgung, sizeof (GUID));
	return true;		// TypeLib registrieren/deregistrieren
}


// --------------------------------------------------------------------------------------------
// NEU: Die folgende Funktion KANN vom Nutzer bereitgestellt werden, wenn die TypeLib nicht als
// Ressource an dieser Extension gespeichert ist. Diese Funktion muß in diesem Fall den Namen
// der zu registrierenden TypeLib liefern
BOOL GetTypeLibName (OLECHAR *cbBuffer)
{
	return FALSE;	// hier nicht der Fall (Funktion könnte weggelassen werden)
}


// --------------------------------------------------------------------------------------------
// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung sich selbst in
// der RegDB registrieren soll.
BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
//	CClassesRoot Root (RegistryDir, fRegister);

	// RegDB initialisieren
    if (fRegister) 
	{
		/*bool fSuccess = */
		return ExtOleRegisterExtensionClass (g_hInstance, CLSID_LinienVerfolgung,
								TEXT(ExtensionName), IDS_LONGCLASSNAME, LINVEREXT_MAJORVERSION,
								LINVEREXT_MINORVERSION, EFUnLoadable/*|EFVisible*/);
/*
		if (!fSuccess) 
			return FALSE;

	//	Key für einzelnen Pages setzen	
		if (!Root.SetSZ (LinienVerfolgung, LinienVerfolgungsPropActText))
			return FALSE;
		if (!Root.SetSZ (Objektstatistik, ResultPropActionText))
			return FALSE;
		if (!Root.SetSZ (DoppelteGeometrie, FindDoubledObjectsText))
			return FALSE;
		if (!Root.SetSZ (VerschnittGeometrie, VerschnittPropActionText))
			return FALSE;
*/
	} 

	// RegDB säubern
	else 
	{
		return ExtOleUnregisterClass (CLSID_LinienVerfolgung, TEXT(ExtensionName));
/*		
        if (!ExtOleUnregisterClass (CLSID_LinienVerfolgung, TEXT(ExtensionName)))
			return FALSE;

	//	Pages-Eintragungen löschen
		Root.DeleteKey (LinienVerfolgungsPropActText);
		Root.DeleteKey (ResultPropActionText);
		Root.DeleteKey (FindDoubledObjectsText);
		Root.DeleteKey (VerschnittPropActionText);
*/
	}

	return TRUE;	// alles ok
}



///////////////////////////////////////////////////////////////////////////////////////////////
// CLinVerExtension
CLinVerExtension :: CLinVerExtension (void)
				  : CTriasExtension ()
//				  : CTriasExtension (0, IDM_UNITINGMENU)	// #WM990624 (noch nicht!)
{
}


// --------------------------------------------------------------------------------------------
// Destruktor
CLinVerExtension :: ~CLinVerExtension (void)
{
}


// --------------------------------------------------------------------------------------------
// Initialisierung
STDMETHODIMP_(BOOL) CLinVerExtension :: InitExtension (short iMode)
{            
	if (!CTriasExtension :: InitExtension (iMode))
		return FALSE;

	return TRUE;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_(BOOL) CLinVerExtension :: UnLoadExtension (void)
{
	return CTriasExtension :: UnLoadExtension();
}


// --------------------------------------------------------------------------------------------
// Diese Funktion dient der Behandlung der MenüKommandos der Erweiterung
STDMETHODIMP_(BOOL) CLinVerExtension :: MenuCommand (UINT MenuItemID, HWND hWnd)
{
	switch (MenuItemID)
	{
		case IDM_LINESPLITTING:
		{
			return TRUE;
		}

		case IDM_LINEUNITING:
		{
			return TRUE;
		}

		case IDM_AREAFORMING:
		{
			return TRUE;
		}

		default:
			ASSERT (FALSE);
			break;
	}

	return FALSE;
}

/*
// --------------------------------------------------------------------------------------------
HRESULT CLinVerExtension :: FinalConstruct (void)
{
	HRESULT hr = S_OK;       

	try 
	{
	//	Erweiterung laden
		if (!isLoaded ())
		{
			LOADEXTENSIONEX le;
			memset (&le, 0, sizeof (LOADEXTENSIONEX));
			le.m_pDesc = NULL;
			le.m_pName = ExtensionName;
			le.m_iMode = LEFullLoad;
			le.m_fGlobal = TRUE;		
			hr = DEX_ExternalLoadExtensionEx (le) ? S_OK : E_FAIL;
		}
	} 
	catch (CException *e)
	{
		hr = E_OUTOFMEMORY;
		e -> Delete ();
	}
	return hr;
}


// --------------------------------------------------------------------------------------------
void CLinVerExtension :: FinalRelease (void) 
{
	if (isLoaded ())
	{
	//	Erweiterung entladen
		LOADEXTENSIONEX le;
		memset (&le, 0, sizeof (LOADEXTENSIONEX));
		le.m_pDesc = NULL;
		le.m_pName = ExtensionName;
		le.m_iMode = LENoLoad;
		le.m_fGlobal = TRUE;		
		DEX_ExternalUnLoadExtensionEx (le);
	}
}
*/
