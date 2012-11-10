// Erweiterung fuer die GeometrieEditierung ------------------------------------
// File: EDITOBJ.CXX

#include "editobjp.hxx"

#include "editobjr.h"	// ResourceKonstanten für dieses Beispiel

#include <xtensnxx.h>
#include <xtsnguid.h>

#include <initguid.h>		// nur im einem Module notwendig

#if defined(WIN32)
#include <undoguid.h>
#include <toolguid.h>
#include <itoolbar.h>
#include "UIOwner.h"
#endif // WIN32

#include "edptguid.h"

#include "version.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CTriasExtension *NewExtension (void)
{
	return new EditObjExtension();
}

//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
//
bool GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
	memcpy (&rClsID, &CLSID_EditPoints, sizeof (GUID));
	return true;
}

// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll.
bool UpdateRegistry (bool fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
	bool fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_EditPoints, 
				TEXT("TRiAS.EditPointObjects.1"), IDS_LONGCLASSNAME,
				EDITPOINT_MAJORVERSION, EDITPOINT_MINORVERSION,
				EFUnLoadable|EFVisible);
		return fSuccess;
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_EditPoints, 
				TEXT("TRiAS.EditPointObjects.1"));
	}

return true;	// alles ok
}

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muá von der Klasse 'TriasExtension'
// abgeleitet sein, welche wiederum als einzigen Parameter den ResID des
// im Hauptfenster einzuhängeneden Menu's übergeben bekommt.
EditObjExtension :: EditObjExtension (void)
{
// Variablen initialisieren   
	_isActive = false;
	_pIL = NULL;
	_iPktTool = -1;
	_pSRO = NULL;		// ShiftRectangleObject

	_ShowPointSem = 0;	// Semaphore für PunktMenu
	_LeftButtonSem = 0;	// Semaphore für Maustasten
	_RightButtonSem = 0;

	_lLastId = -1L;
}

// Destruktor -----------------------------------------------------------------
EditObjExtension :: ~EditObjExtension (void) 
{
	DELETE (_pSRO);
	DELETE (_pIL);
}


// Diese Funktion wird einmalig nach der erfolgreichen Installation der 
// Erweiterung durch TRIAS gerufen. Hier sollten alle notwendigen 
// Initialisierungen erfolgen.
STDMETHODIMP_(bool) EditObjExtension :: InitExtension (short iMode)
{                   
// neues Werkzeug einhängen
#if !defined(WIN32)
	_iPktTool = InstallTool (ResID (STIFTP, &RF()), ResString (ResID (IDS_EDITPKT, &RF()), 20));
#else
	_iPktTool = InstallToolbarButton();
#endif // !WIN32

	if (_iPktTool != -1)		// DB eröffnet
		_pIL = new IdentList();

// MenuItem in ObjrechFenstern installieren
	InstallMenuItem (IDM_EDITPOINTOBJORWND, IDS_EDITPOINTOBJ, true, 0);

// Messages anfordern
	RegisterNotification (DEX_PROJECTOPEN);
	RegisterNotification (DEX_PROJECTCLOSE);
	RegisterNotification (DEX_SETACTIVETOOL);
	RegisterNotification (DEX_TXICHANGED);
	
return true;
}

STDMETHODIMP_(bool) EditObjExtension :: UnLoadExtension (void)
{
// Messages wieder abmelden
	UnRegisterNotification (DEX_TXICHANGED);
	UnRegisterNotification (DEX_SETACTIVETOOL);
	UnRegisterNotification (DEX_PROJECTCLOSE);
	UnRegisterNotification (DEX_PROJECTOPEN);

	if (_isActive) {		// Erweiterung passivieren
		UnRegisterNotification (WM_LBUTTONDOWN, false);
		UnRegisterNotification (WM_RBUTTONDOWN, false);
		_isActive = false;
	}

// Werkzeug wieder ausbauen
	if (_iPktTool != -1) {
#if !defined(WIN32)
		RemoveTool (_iPktTool);
#else
		RemoveToolbarButton();
#endif // !WIN32
		_iPktTool = -1;
	}

	RemoveMenuItem (IDM_EDITPOINTOBJORWND, true, 0);

// IdentListe löschen
	DELETE (_pIL);

return true;
}


// Diese Funktion dient der Behandlung der MenuKommandos vom nutzereigenen
// Menu der Erweiterung
STDMETHODIMP_(bool) EditObjExtension :: MenuCommand (UINT uiMenuID, HWND hWnd)
{
	switch (uiMenuID) {	
	case IDM_CREATEPOINTOBJ:
		return CreatePointObj ();

	case IDM_DELETEPOINTOBJ:
		return DeletePointObj ();

	case IDM_EDITPOINTOBJ:
		return EditPointObj ();

	case IDM_EDITPOINTOBJORWND:
		{
		Punkt Pkt (0, 0);

			if (EditPointObj (DEX_GetActiveObject (hWnd), Pkt, hWnd)) {
				DEX_RePaint();		// neu zeichnen
				return true;
			}
		}

	default:
		break;
	}

return false;
}

// Herausfinden, ob das aktive Objekt ein Bild hat, Menu entsprechend richten -
STDMETHODIMP_(bool) EditObjExtension :: MenuInit (HMENU hMenu, LPARAM, HWND hWnd)
{
// PopupMenu im ORFenster behandeln
	if (hWnd != 0) {
	long lActObj= DEX_GetActiveObject (hWnd);
	short Status = DEX_GetObjectStatus (lActObj);

		if (Status != OSNormal && Status != OSModified) {
			EnableMenuItem (hMenu, IDM_EDITPOINTOBJORWND+MenuOffset(), 
					MF_BYCOMMAND|MF_GRAYED);
			return true;
		}
		
		if (DEX_GetObjectType (lActObj) == OGPunkt) {
			EnableMenuItem (hMenu, IDM_EDITPOINTOBJORWND+MenuOffset(), 
					MF_BYCOMMAND|MF_ENABLED);
		} else {
			EnableMenuItem (hMenu, IDM_EDITPOINTOBJORWND+MenuOffset(), 
					MF_BYCOMMAND|MF_GRAYED);
		}
	}
	
	if (!_ShowPointSem || !_pSRO) return false;	// nicht für uns

	hMenu = _pSRO -> hMenu();
	if (_pSRO -> ONr() != -1L) {		// Objekt getroffen
		EnableMenuItem (hMenu, IDM_DELETEPOINTOBJ+MenuOffset(), 
						MF_BYCOMMAND|MF_ENABLED);
		EnableMenuItem (hMenu, IDM_EDITPOINTOBJ+MenuOffset(), 
						MF_BYCOMMAND|MF_ENABLED);
#if defined(WIN32)
		if (IsWin40()) {
			SetMenuDefaultItem (hMenu, IDM_EDITPOINTOBJ+MenuOffset(), 
							    false);
		}
#endif // WIN32
	} else {
		EnableMenuItem (hMenu, IDM_DELETEPOINTOBJ+MenuOffset(), 
						MF_BYCOMMAND|MF_GRAYED);
		EnableMenuItem (hMenu, IDM_EDITPOINTOBJ+MenuOffset(), 
						MF_BYCOMMAND|MF_GRAYED);
	}

return true;
}

// Diese Funktion wird bei Systemereignissen diverser Natur gerufen -----------
STDMETHODIMP_(LRESULT) EditObjExtension :: Notification (WPARAM iMsg, LPARAM p)
{
	switch (iMsg) {
	case DEX_SETACTIVETOOL:
		{
			if ((short)p == _iPktTool) {
			// Erweiterung scharf machen
				RegisterNotification (WM_LBUTTONDOWN, false);
				RegisterNotification (WM_RBUTTONDOWN, false);
				_isActive = true;
			} else if (_isActive) {
			// Erweiterung passivieren
				UnRegisterNotification (WM_LBUTTONDOWN, false);
				UnRegisterNotification (WM_RBUTTONDOWN, false);
				_isActive = false;
			}
		}
		break;

	case DEX_PROJECTOPEN:
		{
			if (_iPktTool == -1) {
			// Werkzeug installieren
#if !defined(WIN32)
				_iPktTool = InstallTool (ResID (STIFTP, &RF()), 
							 ResString (ResID (IDS_EDITPKT, &RF()), 20));
#else
				_iPktTool = InstallToolbarButton();
#endif // !WIN32
			}
			_pIL = new IdentList();
			_lLastId = -1L;			// letzten Ident vergessen
		}
		break;

	case DEX_PROJECTCLOSE:
		DELETE (_pIL);
#if !defined(WIN32)
		if (_iPktTool != -1) {
			RemoveTool (_iPktTool);
			_iPktTool = -1;
		}
#endif // !WIN32
		break;

	case DEX_TXICHANGED:		// IdentListe aktualisieren
		if (_pIL) {
			if (p == 0) {
			// alles neu einlesen
				DELETE (_pIL);
				_pIL = new IdentList();
				_lLastId = -1L;
			} else
				_pIL -> UpdateEntry (p);
		}
		break;
		
	default:
		break;
	}

return CTriasExtension::Notification (iMsg, p);	// alles weiterleiten
}


STDMETHODIMP_(LRESULT) EditObjExtension ::  WindowsNotification (UINT wMsg, WPARAM, LPARAM p)
{
	switch (wMsg) {
	case WM_LBUTTONDOWN:		// linke MausTaste gedrückt
		if (DEX_GetActiveTool() == _iPktTool) {
		Point Pt (LOWORD(p), HIWORD(p));
		
			if (!FindPointObjFromPoint (Pt, false)) 
				return false;	// keinen Punkt getroffen

			MVWind() -> MouseTrap (On);	// Maus einfangen
			MovePointObj (Pt, false);	// erste Position
			
			_LeftButtonSem++;
			
			RegisterNotification (WM_LBUTTONUP, false);
			RegisterNotification (WM_MOUSEMOVE, false);
			return true;
		}
		break;
		
	case WM_LBUTTONUP:
		if (_LeftButtonSem) {
			UnRegisterNotification (WM_MOUSEMOVE, false);
			UnRegisterNotification (WM_LBUTTONUP, false);

			_LeftButtonSem--;		// Down kam von hier
			MVWind() -> MouseTrap (Off);

		// Objekt an neuer Stelle wegspeichern
			MovePointObj (Point (LOWORD(p), HIWORD(p)));
			SavePointObj ();

			return true;
		}
		break;
		
	case WM_RBUTTONDOWN:		// rechte MausTaste gedrückt
		{
		if (DEX_GetActiveTool() == _iPktTool && !_ShowPointSem) {           
		// Maustaste zum ersten mal gedrückt
			_RightButtonSem++;
			_ShowPointSem++;

			RegisterNotification (WM_RBUTTONUP, false);
			RegisterNotification (WM_MOUSEMOVE, false);

		Point Pt (LOWORD(p), HIWORD(p));
		
			FindPointObjFromPoint (Pt);
			ShowPointMenu (Pt);

			UnRegisterNotification (WM_MOUSEMOVE, false);
			UnRegisterNotification (WM_RBUTTONUP, false);

			_ShowPointSem--;
			if (_RightButtonSem) 
				_RightButtonSem--; // RBUTTONUP wurde geschluckt 
			return true;
		}
		}
		break;		// interessiert uns nicht
		
	case WM_RBUTTONUP:  
		if (!_ShowPointSem && _RightButtonSem) {
		// wenn kein Menu mehr aktiv ist        
			_RightButtonSem--;		// Down kam von hier
			return true;
		}
		break;		// interressiert uns nicht

	case WM_MOUSEMOVE:
		if (_RightButtonSem) return false;		// nur abfangen
		if (_LeftButtonSem) 
		// da Objekt getroffen wurde, dieses verschieben    
			MovePointObj (Point (LOWORD(p), HIWORD(p)));
		break;
		
	default:
		break;
	}
	
return false;
}

#if defined(WIN32)

DefineSmartInterface(TRiASBarContainer);
DefineSmartInterface(TRiASBar);
DefineSmartInterface(TRiASToolBar);
DefineSmartInterface(TRiASUIOwner);

///////////////////////////////////////////////////////////////////////////////
// Hinzufügen des Knopfes zur WerkzeugLeiste 
int EditObjExtension::InstallToolbarButton (void)
{
// Finden der ToolBar "Werkzeuge"
WTRiASBarContainer ToolBars;
HRESULT hr = m_pXtnSite -> QueryInterface (IID_ITRiASBarContainer, ToolBars.ppv());

	if (FAILED(hr)) return -1;

WTRiASBar Bar;
ResString resTools (ResID (IDS_TOOLBARNAME, &RF()), 32);

	hr = ToolBars -> FindTRiASBar (resTools, Bar.ppi());
	if (FAILED(hr)) return -1;

	try {
	// Hinzufügen des Buttons
	WTRiASToolBar ToolBar = Bar;		// throws HRESULT
	WTRiASUIOwner IUIOwner;
	int iOffset = 0;

		hr = ToolBar -> AddBitmap (g_hInstance, IDR_EDITOBJ, 5, &iOffset);
		if (FAILED(hr)) throw hr;

		hr = CUIOwner::_CreatorClass::CreateInstance (NULL, IID_ITRiASUIOwner, IUIOwner.ppv());
		if (FAILED(hr)) throw hr;

	TBBUTTON tb = { iOffset, ID_TOOL_EDITPNT, TBSTATE_ENABLED, TBSTYLE_CHECKGROUP, 0L, 0, };

		hr = ToolBar -> AddButtons (&tb, 1, IUIOwner);
		if (FAILED(hr)) throw hr;

	} catch (...) {
		TX_TRACE1("Can't add button to toolbar\n", resTools.Addr());
		return -1;
	}

	return ID_TOOL_EDITPNT;
}

bool EditObjExtension::RemoveToolbarButton (void)
{
// Finden der ToolBar "Werkzeuge"
WTRiASBarContainer ToolBars;
HRESULT hr = m_pXtnSite -> QueryInterface (IID_ITRiASBarContainer, ToolBars.ppv());

	if (FAILED(hr)) return false;

WTRiASBar Bar;
ResString resTools (ResID (IDS_TOOLBARNAME, &RF()), 32);

	hr = ToolBars -> FindTRiASBar (resTools, Bar.ppi());
	if (FAILED(hr)) return false;

	try {
	// Entfernen des Buttons
	WTRiASToolBar ToolBar = Bar;		// throws HRESULT
	int iIndex = -1;

		hr = ToolBar -> CommandToIndex (ID_TOOL_EDITPNT, &iIndex);
		if (FAILED(hr)) throw hr;

		hr = ToolBar -> DeleteItem (iIndex);
		if (FAILED(hr)) throw hr;

	} catch (...) {
		TX_TRACE1("Can't remove button from toolbar %s\n", resTools.Addr());
		return false;
	}

return true;
}

#endif // WIN32
