// Erweiterung fuer die Verwaltung und Anzeige der ObjektAblage ---------------
// File: OBJCLIP.CXX

#include "objclipp.hxx"

#include "objclip.h"
#include "objclipr.h"

#include <xtsnguid.h>

#include <initguid.h>		// nur im einem Module notwendig
#include <undoguid.h>
#include "oclpguid.h"

#include "version.h"

extern "C" int __cdecl db_error (int EC, int RC, ...);

CTriasExtension *NewExtension (void)
{
	return new ObjClipExtension();
}

//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
//
bool GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
	memcpy (&rClsID, &CLSID_ObjectClipBoard, sizeof (GUID));
	return true;
}

// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll.
bool UpdateRegistry (bool fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
	bool fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_ObjectClipBoard, 
				TEXT("TRiAS.ObjectClipBoard.1"), IDS_LONGCLASSNAME,
				OBJCLIP_MAJORVERSION, OBJCLIP_MINORVERSION,
				EFUnLoadable|EFVisible);
		return fSuccess;
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_ObjectClipBoard, 
				TEXT("TRiAS.ObjectClipBoard.1"));
	}

return true;	// alles ok
}

// Konstruktor der ExtensionKlasse --------------------------------------------
ObjClipExtension :: ObjClipExtension (void)
{
	_pViewer = NULL;
}

// Destruktor -----------------------------------------------------------------
ObjClipExtension :: ~ObjClipExtension (void) 
{
	DELETE (_pViewer);	// Fenster und Daten zerlegen
}


// Diese Funktion wird einmalig nach der erfolgreichen Installation der 
// Erweiterung durch TRIAS gerufen. Hier sollten alle notwendigen 
// Initialisierungen erfolgen.
STDMETHODIMP_(bool) ObjClipExtension :: InitExtension (short iMode)
{
// hier zusätzliche MenuPunkte anhängen
	InstallMenuItem (IDM_COPY, IDS_COPYMENUITEM, true, 1);
	InstallMenuItem (IDM_CUT, IDS_CUTMENUITEM, true, 1);
	InstallMenuItem (IDM_PASTE, IDS_PASTEMENUITEM, true, 1);
	InstallMenuItem (IDM_COPYANDPASTE, IDS_COPYANDPASTE, true, 1);

	InstallMenuItem (IDM_SHOWOBJCLIP, IDS_SHOWOBJCLIP, false, 2);
	InstallMenuItem (IDM_PASTEGLOBAL, IDS_PASTEGLOBAL, false, 1);

// Notifikationen anfordern
	RegisterNotification (DEX_PROJECTOPEN);
	RegisterNotification (DEX_PROJECTCLOSE);
	RegisterNotification (DEX_OBJWNDCLOSED);

	RegisterNotification (DEX_TXICHANGED);
	RegisterNotification (DEX_TXMCHANGED);
	RegisterNotification (DEX_TXRCHANGED);

	_pViewer = new ObjClipboardViewer (MWind(), &RF());
	if (_pViewer == NULL) {
		db_error (EC_NOMEMORY, RC_ctObjClip);
		return false;
	}

return true;
}

STDMETHODIMP_(bool) ObjClipExtension :: UnLoadExtension (void)
{
// MenuPunkt natürlich wieder ausbauen
	RemoveMenuItem (IDM_PASTEGLOBAL, false, 1);
	RemoveMenuItem (IDM_SHOWOBJCLIP, false, 2);

	RemoveMenuItem (IDM_COPYANDPASTE, true, 1);
	RemoveMenuItem (IDM_PASTE, true, 1);
	RemoveMenuItem (IDM_CUT, true, 1);
	RemoveMenuItem (IDM_COPY, true, 1);

// Notifikationen wieder abmelden
	UnRegisterNotification (DEX_TXRCHANGED);
	UnRegisterNotification (DEX_TXMCHANGED);
	UnRegisterNotification (DEX_TXICHANGED);

	UnRegisterNotification (DEX_OBJWNDCLOSED);
	UnRegisterNotification (DEX_PROJECTCLOSE);
	UnRegisterNotification (DEX_PROJECTOPEN);

return true;
}


// Diese Funktion dient der Behandlung der MenuKommandos vom nutzereigenen
// Menu der Erweiterung
STDMETHODIMP_(bool) ObjClipExtension :: MenuCommand (UINT MenuItemID, HWND hWnd)
{
	if (_pViewer == NULL) return false;

	switch (MenuItemID) {	
	case IDM_COPY:
		return _pViewer -> InsertObject (DEX_GetActiveObject (hWnd));

	case IDM_CUT:
		{
		long lONr = DEX_GetActiveObject (hWnd);

			_pViewer -> InsertObject (lONr, IMDelete);
			DEXOR_DeleteObject (hWnd, lONr);
			DEX_RePaint();			// neu zeichnen
		}
		break;

	case IDM_PASTE:
	// alle selektierten Objekte des auslösenden Fensters bearbeiten
		return _pViewer -> PasteObjectLocal (hWnd);

	case IDM_COPYANDPASTE:
	// das aktivierte Objekt kopieren und anschließen auf alle selektierten 
	// zurückspeichern
		_pViewer -> InsertObject (DEX_GetActiveObject (hWnd));
		return _pViewer -> PasteObjectLocal (hWnd);
	
	case IDM_PASTEGLOBAL:
	// Inhalt der Zwischenablage als neues Objekt zurückspeichern
		return _pViewer -> PasteObjectGlobal();

	case IDM_SHOWOBJCLIP:	// HauptMenuPunkt
	// Fenster anzeigen/ausblenden
		_pViewer -> ToggleStatus();
		break;
	}

return false;
}

STDMETHODIMP_(bool) ObjClipExtension :: MenuInit (HMENU hMenu, LPARAM, HWND hWnd)
{
	if (hWnd == 0) {
	UINT iMenuID = IDM_SHOWOBJCLIP+MenuOffset();

		if (_pViewer && _pViewer -> isViewerShown()) {
			ModifyMenu (hMenu, iMenuID, MF_BYCOMMAND|MF_STRING, 
				    iMenuID, 
				    ResString (ResID (IDS_HIDEOBJCLIP, &RF()), 30));
		} else {
			ModifyMenu (hMenu, iMenuID, MF_BYCOMMAND|MF_STRING, 
				    iMenuID, 
				    ResString (ResID (IDS_SHOWOBJCLIP, &RF()), 30));
		}

		if (_pViewer && _pViewer -> Status() == OCVObjectValid)
			EnableMenuItem (hMenu, IDM_PASTEGLOBAL+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
		else		
			EnableMenuItem (hMenu, IDM_PASTEGLOBAL+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		return true;
	}

// ObjektRechercheMenu bearbeiten
	if (_pViewer == NULL || _pViewer -> Status() == OCVInValid) {
		EnableMenuItem (hMenu, IDM_CUT+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		EnableMenuItem (hMenu, IDM_COPY+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		EnableMenuItem (hMenu, IDM_PASTE+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

		return true;
	}		
	EnableMenuItem (hMenu, IDM_CUT+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
	EnableMenuItem (hMenu, IDM_COPY+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
	if ((_pViewer -> Status() == OCVObjectValid || 
	     _pViewer -> Status() == OCVInfoValid)
	/* && wenigstens ein Objekt selektiert */) 
		EnableMenuItem (hMenu, IDM_PASTE+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
	else		
		EnableMenuItem (hMenu, IDM_PASTE+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

return true;
}

// Diese Funktion wird bei Systemereignissen diverser Natur gerufen -----------
STDMETHODIMP_(LRESULT) ObjClipExtension :: Notification (WPARAM iMsg, LPARAM p)
{
	if (_pViewer == NULL) return false;

	switch (iMsg) {
	case DEX_PROJECTOPEN:		// neues Projekt wurde eröffnet
		_pViewer -> OpenedProject();
		break;

	case DEX_PROJECTCLOSE:		// project is to be closed
		_pViewer -> ClosingProject();
		break;

	case DEX_OBJWNDCLOSED:
		_pViewer -> ResetUndoHandle((HWND)p);
		break;

	case DEX_TXICHANGED:
		_pViewer -> ReReadIdents (p);
		break;

	case DEX_TXMCHANGED:
		_pViewer -> ReReadMCodes (p);
		break;

	case DEX_TXRCHANGED:
		break;
	}

return false;	// alles andere ignorieren
}


