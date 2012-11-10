// Objektbezogene Visualiserung -----------------------------------------------
// File: VISOBJ.CXX

#include "visobjp.hxx"

#include <xtsnaux.hxx>

#define INITGUIDS

#include "visobj.h"	// ResourceKonstanten für dieses Beispiel
#include "defabout.h"
#include "resource.h"

#include "defabout.hxx"
#include "colcntrl.hxx"

#if defined(EXTVIS)
#include <icustom.hxx>
#include <vismguid.h>
#include "vismtree.hxx"
#endif

#include "yy1stype.hxx"
#include "VisInfoObj.h"

#define _TriasTLB_H_
#include <dirisole.h>
#include "version.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//EXTERN_C const IID IID_ITRiASServiceProvider = {0x4F76AC35,0x98EF,0x11D1,{0xBA,0x12,0x08,0x00,0x36,0xD6,0x38,0x03}};
EXTERN_C const IID IID_IRawVisInfo = {0x4BAB20A3,0xA922,0x11D1,{0x85,0x88,0x00,0x60,0x08,0x75,0x13,0x8A}};
//#if _MSC_VER >= 1100
//EXTERN_C const CLSID CLSID_TRiASCSRectangleGeometry = {0xCF648167,0x9E24,0x11D1,{0xBA,0x1C,0x08,0x00,0x36,0xD6,0x38,0x03}};
//EXTERN_C const CLSID CLSID_TRiASCSPointGeometry = {0x3327AD94,0xA2B1,0x11D1,{0xA0,0x51,0x00,0x60,0x97,0x55,0x66,0xB4}};
//#endif // _MSC_VER >= 1100

// 
// NEU: Die folgende Funktion KANN vom Nutzer bereitgestellt werden, wenn eine
// TypeLib registriert werden soll. Auch die TypeLib muß einen eigenen GUID
// besitzen !
//
BOOL GetTypeLibGUID (GUID &guidTLib)
{
	memcpy (&guidTLib, &LIBID_VisInfoLib, sizeof (GUID));
	return true;		// TypeLib registrieren/deregistrieren
}

// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll.
BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
	bool fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_ObjVisInfoExtension, 
				TEXT("TRiAS.ObjVisInfo.1"), IDS_LONGCLASSNAME,
				VISINFO_MAJORVERSION, VISINFO_MINORVERSION,
				EFUnLoadable|EFPreLoad|EFVisible);
		return fSuccess;
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_ObjVisInfoExtension, 
				TEXT("TRiAS.ObjVisInfo.1"));
	}

return true;	// alles ok
}

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muß von der Klasse 'TriasExtension'
// abgeleitet sein, welche wiederum als die beiden Parameter die ResID's der
// im Hauptfenster und im ObjektRechercheFenster einzuhängeneden Menu's 
// übergeben bekommt.
#pragma warning (disable: 4355)

CVisObjExtension::CVisObjExtension (void)
		  : CTriasExtension (EXTENSIONMENU, OBJEXTENSIONMENU)
#if _ATL_VER < 0x0200
		  , m_cp(this)
#endif // _ATL_VER
{
	m_pActProject = NULL;
	m_pActSight = NULL;

	m_lSichtVisMCode = -1L;
	m_lObjVisMCode = -1L;

	m_lSichtLegMCode = -1L;

	m_fAllVisErrIgnore = false;	// Visualisierungsfehler bearbeiten
	m_fModifyAllSelected = false;	// nur aktiviertes Objekt beeinflussen
	m_fFullVisInfo = false;		// nur Änderung in VisInfo speichern
	m_fShowHidden = false;		// versteckte Objekte nicht anzeigen
	m_fRebuildView = false;	
			
	m_lIdentHandled = -1L;		// keine Fehlerbehandlung aktiv
				
	m_pVIE = new CIgnoreVisErrorTree;

#if defined(EXTVIS)
	m_pVMT = new CVisModuleTree;
	m_hDC = 0;
	m_hTargetDC = 0;
	m_fOleInitialized = false;
	m_fForceShutdown = false;	// darf nicht entladen werden, wenn OLE initialisiert wurde
#endif	

	m_pMWert = new char [MWERTSIZE+1];

	m_CCDlg = NULL;	
}

#pragma warning (default: 4355)

// Destruktor -----------------------------------------------------------------
CVisObjExtension::~CVisObjExtension (void) 
{
	DELETE_OBJ (m_pActProject);
	DELETE_OBJ (m_pActSight);
	DELETE_OBJ (m_pVIE);
#if defined(EXTVIS)
	DELETE_OBJ (m_pVMT);
#endif
	DELETE_OBJ (m_pMWert);

	DELETE_OBJ (m_CCDlg);
}


// Im folgenden müssen alle durch diese Erweiterung überladenen virtuellen
// Funktionen definiert werden.

// Diese Funktion wird (einmalig) gerufen, wenn die Erweiterung vollständig
// installiert ist
STDMETHODIMP_(BOOL) CVisObjExtension::InitExtension (short iMode)
{
	if (!CTriasExtension::InitExtension (iMode))
		return false;

// Menupunkt im Hauptfenster installieren
	if (iMode == LEFullLoad)
		InstallMenuItem (IDM_IGNOREALLERRORS, IDS_IGNOREALLERRORS, false, 1);

	if (iMode != LoadState()) return true;

// FehlerNotifikation
	RegisterNotification (DEX_ERRORMESSAGE);

// Notifikationen bei ProjektWechsel
	RegisterNotification (DEX_PROJECTOPEN);
	RegisterNotification (DEX_N_PROJECTTOCLOSE);

// Notifikationen bei SichtWechsel/Sicht löschen/Sicht erzeugen
	RegisterNotification (DEX_SIGHTTOSELECT);
	RegisterNotification (DEX_DELETEVIEW);
	RegisterNotification (DEX_VIEWCREATED);

// Notifikation bei Objekt löschen
	RegisterNotification (DEX_OBJECTTODELETE);
	
// Notifikation aus RechercheFenster
	RegisterNotification (DEX_QUERYRECHOBJECT);

// Notifikation beim laden eines Identifikators/Objektes um zu entscheiden, 
// ob eine Einmischung in den Prozeß des Zeichnens notwendig ist.
	RegisterNotification (DEX_DRAWIDENT);
	RegisterNotification (DEX_DRAWIDENTEX);
	RegisterNotification (DEX_DRAWOBJECT);
#if defined(EXTVIS)
	RegisterNotification (DEX_ERASEBKGND);
	RegisterNotification (DEX_SIGHTSELECTED);
	RegisterNotification (DEX_SERVERCLOSED);	// Informieren lassen, wenn TRiAS geschlossen wird
#endif
// Palette zuleiten
	RegisterNotification (DEX_SETNEWPALETTE);

// evtl. bereits offenes Projekt/VisObjMCode holen
	if (InitMCodes ()) DEX_RebuildSight();

#if defined(EXTVIS)
#if defined(WIN32)
	if (OleInitialize (NULL) == NOERROR)
		m_fOleInitialized = true;
	else
		m_fOleInitialized = false;
#else
/*
 * Check if our host did CoInitialize by trying CoGetMalloc.
 * If it doesn't work, then we'll CoInitialize ourselves.
 */
LPMALLOC pIMalloc = NULL;
HRESULT hr = CoGetMalloc(MEMCTX_TASK, &pIMalloc);

	if (SUCCEEDED(hr))
		pIMalloc -> Release();
	else {
		hr = OleInitialize (NULL);
		if (FAILED(hr)) return false;
		m_fOleInitialized = true;
	}
#endif // WIN32
#endif // EXTVIS

// ObjektParser initialisieren
	if (!InitYY1Parse()) return false;
	
return true;
}

// Diese Funktion wird gerufen, bevor die Erweiterung freigeben werden soll
STDMETHODIMP_(BOOL) CVisObjExtension::UnLoadExtension (void)
{
#if defined(EXTVIS)
// wenn OLE initialisiert wurde, dann nur ganz am Ende wirklich entladen
	if (m_fOleInitialized && !m_fForceShutdown)
		return false;
#endif	// EXTVIS
		
// Menupunkt rausnehmen
	if (LoadState() == LEFullLoad)
		RemoveMenuItem (IDM_IGNOREALLERRORS, false, 1);

// Notifikationen freigeben
	UnRegisterNotification (DEX_SETNEWPALETTE);	// Palette abmelden
	UnRegisterNotification (DEX_QUERYRECHOBJECT);
	UnRegisterNotification (DEX_PROJECTOPEN);
	UnRegisterNotification (DEX_N_PROJECTTOCLOSE);
	UnRegisterNotification (DEX_OBJECTTODELETE);
	UnRegisterNotification (DEX_VIEWCREATED);
	UnRegisterNotification (DEX_DELETEVIEW);
	UnRegisterNotification (DEX_SIGHTTOSELECT);
	UnRegisterNotification (DEX_DRAWIDENTEX);
	UnRegisterNotification (DEX_DRAWIDENT);
	UnRegisterNotification (DEX_DRAWOBJECT);
#if defined(EXTVIS)
	UnRegisterNotification (DEX_SERVERCLOSED);
	UnRegisterNotification (DEX_SIGHTSELECTED);
	UnRegisterNotification (DEX_ERASEBKGND);
#endif
	UnRegisterNotification (DEX_ERRORMESSAGE);	// FehlerNotifikation
	if (m_fRebuildView)	// wenn notwendig, dann auch diese Message abmelden
		UnRegisterNotification (DEX_PAINTTOPLAYER);

// Sicht ohne uns neu aufbauen
	if (m_pActProject)	// wenn Projekt geöffnet ist
		DEX_PostRebuildSight();

	EndYY1Parse();		// ObjektParser wieder deinitialisieren
	
#if defined(EXTVIS)
	if (m_fOleInitialized)
		OleUninitialize();
#endif

return CTriasExtension::UnLoadExtension();
}


// Die folgende Funktion wird gerufen, wenn eine der angeforderten 
// Notifikationen ankommt.
STDMETHODIMP_(LRESULT) CVisObjExtension::Notification (WPARAM iMsg, LPARAM p)
{
	switch (iMsg) {
	case DEX_PROJECTOPEN:
		{
		short iDesc = (short)p;

			DELETE_OBJ (m_pActProject);
			m_pActProject = new char [_MAX_PATH +1];
			if (DEX_GetActiveProject (m_pActProject) == NULL) {
				DELETE_OBJ (m_pActProject);
				break;
			} 
		// MerkmalsCodes initialisieren
			m_lSichtVisMCode = GetViewMCode();
			m_lObjVisMCode = GetObjMCode();
			m_lSichtLegMCode = GetViewLegMCode();

#if defined(EXTVIS)
		// Visualisierungsmodule bedienen
			if (m_pVMT) {
				m_pVMT -> OnProjectChange (__hWndM, 
							   PROJECTCHANGE_OPENED,
							   m_pActProject);
			}
#endif
		}
		break;

	case DEX_SIGHTTOSELECT:
		{
		char *cptr = (char *)p;

			DELETE_OBJ (m_pActSight);
			if (cptr != NULL) {
				m_pActSight = new char [_MAX_PATH +1];
				if (m_pActSight) {
					strcpy (m_pActSight, cptr);
					m_lSichtVisMCode = GetViewMCode();
					m_lObjVisMCode = GetObjMCode();
					m_lSichtLegMCode = GetViewLegMCode();
				}
			}
		}
		break;

#if defined(EXTVIS)
	case DEX_SIGHTSELECTED:
		if (m_pVMT) m_pVMT -> OnViewChange (__hWndM, VIEWCHANGE_SELECTED, (char *)p);
		break;

	case DEX_ERASEBKGND:
		m_hDC = ((HDC *)p)[0];		// to draw on
		m_hTargetDC = ((HDC *)p)[1];	// drawtarget
		break;
		
	case DEX_SERVERCLOSED:
		m_fForceShutdown = true;
		break;		// jetzt darf dieser Erweiterung entladen werden, selbst, wenn
				// OLE initialisert wurde
#endif
		
	case DEX_DELETEVIEW:
#if defined(EXTVIS)
		if (m_pVMT) {
			m_pVMT -> OnViewChange (__hWndM, VIEWCHANGE_DELETED, 
						(char *)p);
		}
#endif
		return HandleDeleteSight ((char *)p);
		
	case DEX_VIEWCREATED:
		return HandleViewCreated ((VIEWCREATED *)p);

	case DEX_N_PROJECTTOCLOSE:
#if defined(EXTVIS)
		if (m_pVMT) {
			m_pVMT -> OnProjectChange (__hWndM, PROJECTCHANGE_CLOSED,
						   m_pActProject);
		}
		if (m_pVMT) m_pVMT -> EveryDelete();	// VMD's freigeben
#endif
		DELETE_OBJ (m_pActProject);
		m_fAllVisErrIgnore = false;
		if (m_pVIE) m_pVIE -> EveryDelete();
		DeInitMCodes();
		break;

	case DEX_DRAWIDENT:
		return (LRESULT)GetIDMode ((long)p);

	case DEX_DRAWIDENTEX:
		{
		DRAWIDENTEX *pDI = (DRAWIDENTEX *)p;

			pDI -> m_lResult |= (LRESULT)GetIDMode (pDI -> m_lIdent);
			return false;		// unbedingt weiterreichen
		}

	case DEX_DRAWOBJECT:
		{
		DRAWOBJECT *pDO = (DRAWOBJECT *)p;

			if (pDO -> dwSize == sizeof(DRAWOBJECT)) {
			// behandeln, wie bisher
				return (LRESULT)GetNewVI (pDO -> lObjNr, pDO -> pNewVI, 
						  false, -1L,
						  pDO -> m_fFlags);
			} else {
				TX_ASSERT(pDO -> dwSize == sizeof(DRAWOBJECTEX));

			// Resultate zu bereits existierenden hinzufügen
				((DRAWOBJECTEX *)pDO) -> m_lResult |= (LRESULT)GetNewVI (
							pDO -> lObjNr, pDO -> pNewVI, 
							false, -1L, pDO -> m_fFlags);
				return false;		// unbedingt weiterreichen
			}
		}
		
	case DEX_ERRORMESSAGE:
		return (LRESULT)HandleErrorMessage ((ERRORMESSAGE *)p);
		
	case DEX_QUERYRECHOBJECT:	// Strings in ORFenster beeinflussen
		return HandleQueryRechObject ((RECHOBJECT *)p);
		
	case DEX_SETNEWPALETTE:		// PaletteHandling in ColorControlDlg
		if (m_CCDlg) m_CCDlg -> SetNewPalette (*(HPALETTE *)p);
		if (m_pVMT) m_pVMT -> OnPaletteChange (__hWndM, *(HPALETTE *)p);
		break;

	case DEX_PAINTTOPLAYER:		// zeichnen beendet
		if (m_fRebuildView) {
			DEX_PostRebuildSight();	// noch mal abschicken, aber als Post
			UnRegisterNotification (DEX_PAINTTOPLAYER);	// nur einmal
			m_fRebuildView = false;
		}
		break;

	default:
		break;		// alle anderen interessieren nicht
	}

return CTriasExtension::Notification(iMsg, p);	// Notifikationen weiterreichen 
}


// Diese Funktion initialisiert das Menu --------------------------------------
STDMETHODIMP_(BOOL) CVisObjExtension::MenuInit (HMENU hMenu, LPARAM, HWND hWnd)
{
	if (hWnd == 0 && hMenu == MenuHandle()) {
	// Hauptmenu der Erweiterung auszuklappen
		CheckMenuItem (hMenu, IDM_SHOWHIDDEN+MenuOffset(), 
			MF_BYCOMMAND | (m_fShowHidden ? MF_CHECKED : MF_UNCHECKED)); 	
		CheckMenuItem (hMenu, IDM_SAVECOMPLETE+MenuOffset(), 
			MF_BYCOMMAND | (m_fFullVisInfo ? MF_CHECKED : MF_UNCHECKED)); 

	uint uiHide = IDM_VISOBJREMOVE + MenuOffset();
	
		if (m_lObjVisMCode == -1) 
			EnableMenuItem (hMenu, uiHide, MF_BYCOMMAND|MF_GRAYED);
		else
			EnableMenuItem (hMenu, uiHide, MF_BYCOMMAND|MF_ENABLED);
		return true;
	}

	if (hWnd != 0 && hMenu == ORMenuHandle()) {
	uint uiHide = IDM_HIDEOBJECTS+MenuOffset();
	short iCnt = 0;

		DEXOR_SelectedObjectsCount (hWnd, &iCnt);

		if (iCnt == 0) {
			EnableMenuItem (hMenu, uiHide, MF_BYCOMMAND|MF_GRAYED);
			return true;
		}

		EnableMenuItem (hMenu, uiHide, MF_BYCOMMAND|MF_ENABLED);
		if (iCnt > 1) {
		// nicht nur ein Objekt selektiert
			ModifyMenu (hMenu, uiHide, MF_BYCOMMAND|MF_STRING, uiHide, 
				    ResString (ResID (IDS_HIDESELECTEDOBJECTS, &RF()), 30));
		} else {
		// genau ein Objekt aktiviert/selektiert
			ModifyMenu (hMenu, uiHide, MF_BYCOMMAND|MF_STRING, uiHide, 
				    ResString (ResID (IDS_HIDEACTIVATEDOBJECT, &RF()), 30));
		}
		return true;
	}

	if (m_pActProject) {	// nur im ProjektMenu
		CheckMenuItem (hMenu, IDM_IGNOREALLERRORS+MenuOffset(), 
		MF_BYCOMMAND | (m_fAllVisErrIgnore ? MF_CHECKED : MF_UNCHECKED));
	}
	
return false;
}


// Diese Funktion dient der Behandlung der MenuKommandos vom nutzereigenen
// Menu der Erweiterung
STDMETHODIMP_(BOOL) CVisObjExtension::MenuCommand (UINT MenuItemID, HWND hORWnd)
{
	switch (MenuItemID) {	
	// Hauptmenupunkte
#if !defined(WIN32)
	case IDM_EXTABOUT:		// InfoBox anzeigen		
		{
		AboutBox AB (MWind(), ResID (DEFIDABOUT, &RF()));
		
			AB.Show (Centre);
		} 
		return true;
#endif // !WIN32

	case IDM_SAVECOMPLETE:		// gesamte VisInfo speichern
		m_fFullVisInfo = !m_fFullVisInfo;
		break;
		
	case IDM_VISOBJREMOVE:		// VisInfoMerkmale löschen
		if (RemoveVisInfo()) 
			DEX_RePaintWait();
		break;
		
	case IDM_SHOWHIDDEN:		// versteckte Objekte anzeigen
		m_fShowHidden = !m_fShowHidden;
		DEX_RePaintWait();
		break;
		
	case IDM_REVOKEHIDE:		// Ausblenden rückgängig
		if (RemoveShowInfo()) 
			DEX_RePaintWait();
		break;

	case IDM_VISINFOEXPORT:		// Erzeugen der VisAsc
		ExportVisInfo();
		break;
		
	case IDM_VISINFOIMPORT:
		ImportVisInfo();	// Einlesen einer VisAsc
		break;
		
	// ObjektRechercheFensterMenu
	case IDM_CHANGEVISINFO:
	// neue VisInfo für dieses Objekt einstellen
		if (hORWnd) 
			return ChangeVisInfo (hORWnd, GetKeyState (VK_CONTROL) < 0);
		break;
		
#if defined(EXTVIS)
	case IDM_CHANGESYMBOLINFO:
		if (hORWnd) return DefineSymbol (hORWnd);
		break;
#endif

	case IDM_RESETVISINFO:
		if (hORWnd) return ResetVisInfo (hORWnd);
		break;

	case IDM_HIDEOBJECTS:
		if (hORWnd) return ShowObjects (hORWnd);
		break;

	case IDM_SHOWOBJECTS:
		if (hORWnd) return ShowObjects (hORWnd, true);
		break;

	case IDM_COLORCONTROL:
		ControlColors();
		break;
		
	// zusätzlicher MenuPunkt
	case IDM_IGNOREALLERRORS:
		if (m_fAllVisErrIgnore || (m_pVIE && m_pVIE -> Count())) {
			m_fAllVisErrIgnore = false;
			if (m_pVIE) m_pVIE -> EveryDelete();
		} else
			m_fAllVisErrIgnore = true;
		break;
	}

return false;
}

// Initialisieren der internen Strukturen für objektbezogene Visualisierung ---
bool CVisObjExtension::InitMCodes (void)
{
	DELETE_OBJ (m_pActProject);
	m_pActProject = new char [_MAX_PATH +1];

	if (DEX_GetActiveProject (m_pActProject) != NULL) {
		DELETE_OBJ (m_pActSight);
		m_pActSight = new char [_MAX_PATH +1];
		m_pActSight = DEX_GetActiveSight (m_pActSight);

		m_lSichtVisMCode = GetViewMCode ();	// VisObjMCode holen
		m_lObjVisMCode = GetObjMCode ();

		m_lSichtLegMCode = GetViewLegMCode();	// LegObjMCode holen
	} else {
		DELETE_OBJ (m_pActProject);
		m_lSichtVisMCode = -1L;
		m_lObjVisMCode = -1L;
		m_lSichtLegMCode = -1L;
	}

return m_lSichtVisMCode != -1L && m_lObjVisMCode != -1L;
}

void CVisObjExtension::DeInitMCodes (void)
{
	DELETE_OBJ (m_pActProject);
	DELETE_OBJ (m_pActSight);

	m_lSichtVisMCode = -1L;
	m_lObjVisMCode = -1L;
	m_lSichtLegMCode = -1L;
}

// Holen des MCodes, unter dem an einer Sicht der MCode für die Visualisierung
// hängt
long CVisObjExtension::GetViewMCode (bool fGenerate)
{
	if (m_pActProject == NULL || *m_pActProject == '\0') {
	// in StartupAnsicht kommt ProjektOpened erst nach SightToSelect
		DELETE_OBJ (m_pActProject);
		m_pActProject = new char [_MAX_PATH +1];
		if (DEX_GetActiveProject (m_pActProject) == NULL) 
		{
			DELETE_OBJ (m_pActProject);
			return -1L;		// wirklich kein Projekt
		} 
	}

return GetHeaderMCode (fGenerate, IDS_OBJVISINFO, 
					   IDS_OBJVISINFOKTEXT, IDS_OBJVISINFOLTEXT);
}


// Holen des MCodes, unter dem an einer Sicht der MCode für die Legende hängt
long CVisObjExtension::GetViewLegMCode (void)
{
	if (m_pActProject == NULL || *m_pActProject == '\0') {
		DELETE_OBJ (m_pActProject);
		m_pActProject = new char [_MAX_PATH +1];
		if (DEX_GetActiveProject (m_pActProject) == NULL) 
		{
			DELETE_OBJ (m_pActProject);
			return -1L;		// wirklich kein Projekt
		} 
	}

	return GetHeaderMCode (false, IDS_LEGENDINFOMCODE,
					   IDS_LEGENDINFOKTEXT, IDS_LEGENDINFOLTEXT);
}


long GetHeaderMCode (bool fGenerate, ResID resID, ResID resKT, ResID resLT)
{
GEODBHDRENTRY hdrEntry;
long result = -1L;

	hdrEntry.dwSize = sizeof(GEODBHDRENTRY);
	strncpy (hdrEntry.hdrKey, ResString (resID, 17), 16);
	hdrEntry.lphdrText = new char [MCODESIZE +1];
	hdrEntry.hdrTextLen = MCODESIZE;

	if (DEX_ReadGeoDBHdrEntry (hdrEntry) == EC_OKAY) {
	// HeaderEintrag existiert
		result = atol (hdrEntry.lphdrText);
	} else if (fGenerate) {
	// bei Bedarf neu generieren
	long lMCode = DEX_GetUniqueSysMCode();	// neuen MCode besorgen
	
		if (lMCode != -1) {		// und wegschreiben
			hdrEntry.hdrTextLen = MCODESIZE;
			ltoa (lMCode, hdrEntry.lphdrText, 10);

			if (DEX_WriteGeoDBHdrEntry (hdrEntry) == EC_OKAY) {
				result = lMCode;

			// neuen Eintrag in PBD generieren
			ResString KFormat (resKT, 33);
			ResString LFormat (resLT, 256);

				SaveMCodeInPbd (result, NULL, KFormat, LFormat, true);
			}
		}
	}
	DELETE_OBJ (hdrEntry.lphdrText);

return result;
}

// Abfragen des Merkmals der aktuellen Sicht, das MCode fuer die objektbezogene
// Visualisierung enthält
long CVisObjExtension::GetObjMCode (bool fGenerate, char *pView, LONG lIdent) 
{
	if (m_lSichtVisMCode == -1L) {
		m_lSichtVisMCode = GetViewMCode (false);
		if (m_lSichtVisMCode == -1L)
			return -1L;
	}
	if (pView == NULL && (m_pActSight == NULL || *m_pActSight == '\0'))
		return -1L;

	return GetObjMCodeView (pView ? pView : m_pActSight, m_lSichtVisMCode, 
			ResID (IDS_PBDKURZTEXT, &RF()), ResID (IDS_PBDLANGTEXT, &RF()), 
			fGenerate, lIdent);
}


// Für eine bestimmte Sicht MCode für Objekte besorgen ------------------------
long GetObjMCodeView (
	char *pView, long lSichtMCode, ResID resKT, ResID resLT, 
	bool fGenerate, LONG lIdent)
{
	if (lSichtMCode == -1L) return -1L;
	
TARGETMERKMAL gm;
long result = -1L;

	INITSTRUCT(gm, TARGETMERKMAL);
	gm.lTarget = (LPARAM)pView;
	gm.lMCode = lSichtMCode;
	gm.imaxLen = MCODESIZE;
	gm.pMText = new char [MCODESIZE+1];
	gm.iTTyp = TT_Sicht;

	if (DEX_GetTextMerkmal (gm) != NULL) {
		if (gm.pMText)
			result = atol (gm.pMText);
	} else if (fGenerate) {
	// neu generieren
	long lMCode = DEX_GetUniqueSysMCode();
	
		if (lMCode != -1 && gm.pMText) {	// und wegschreiben
			gm.imaxLen = MCODESIZE;
			ltoa (lMCode, gm.pMText, 10);

			if (DEX_ModTextMerkmal (gm) == EC_OKAY) {
				result = lMCode;

			// neuen Eintrag in PBD generieren
			ResString KFormat (resKT, 33);
			ResString LFormat (resLT, 256);

				SaveMCodeInPbd (result, pView, KFormat, LFormat, true, lIdent);
			}
		}
	}
	DELETE_OBJ (gm.pMText);
	return result;
}

// Heranholen und Merken des Modes für diesen Identifikator -------------------
DWORD CVisObjExtension::GetIDMode (long lIdent, char *pView)
{
// externe Behandlung
IDENTVISMODE rgVisMode = IDENTVISMODE_NoAction;

	USES_CONVERSION;
#if _ATL_VER >= 0x200
	{
	CComBSTR bstrView;

		if (NULL != pView)
			bstrView = A2OLE(pView);
		else 
			bstrView = A2OLE(m_pActSight);

		if (S_OK == Fire_GetIdentMode (lIdent, bstrView, &rgVisMode))
			return rgVisMode;
	}
#else
	if (!m_cp.empty()) {
	CComBSTR bstrView;

		if (NULL != pView)
			bstrView = A2OLE(pView);
		else 
			bstrView = A2OLE(m_pActSight);

		if (S_OK == m_cp.Fire_GetIdentMode (lIdent, bstrView, &rgVisMode))
			return rgVisMode;
	}
#endif // _ATL_VER

// eigene Behandlung
DWORD result = rgVisMode;
long lObjMCode = -1L;

	if (pView == NULL) {
		if (m_pActSight == NULL || *m_pActSight == '\0' || m_lObjVisMCode == -1L)
			return result;
		lObjMCode = m_lObjVisMCode;
	} else 
		lObjMCode = GetObjMCode (false, pView);

// permanente Sicht ausgewählt
	if (lObjMCode == -1L || 0 == lObjMCode) 
		return result;
	
	if (ReadTextMerkmal (TT_Identifikator, lIdent, lObjMCode, m_pMWert)) 
		result = StringToIdMode (m_pMWert, lIdent);

	return result;
}


// Heranholen einer VisInfo für ein bestimmtes Objekt -------------------------
short CVisObjExtension::GetNewVI (
	HANDLEVISINFO *pHVI, long lMCode, short fFlags, char **cbModuleInfo)
{
	if (lMCode == -1) 
		lMCode = m_lObjVisMCode;
	
	if (lMCode == -1) return DO_UnChanged;

VisInfo *pVI = VisInfoFromC (*pHVI -> m_pVI, (VisType)pHVI -> m_iVTyp);
short iResult = 0;

	if ((iResult = GetNewVI (pHVI -> m_lONr, pVI, false, 
				 lMCode, fFlags, cbModuleInfo)) != 0) 
	{
		DELETE_OBJ (pHVI -> m_pVI);
		pHVI -> m_pVI = VISINFOFromCPP (pVI);
		pHVI -> m_fFlags = iResult;
	}
	DELETE_OBJ (pVI);

return iResult;
}

// Lesen und interpretieren eines VisualisierungsStrings ----------------------
HRESULT CreateVisInfo (VisInfo *pVis, CVisInfoInterfaceBase **ppIVis)
{
	if (NULL == pVis) return E_FAIL;
	TEST_E_POINTER("CreateVisInfo", ppIVis);

CVisInfoInterfaceBase *pBase = NULL;

	try {
		switch (pVis -> isA()) {
		case VT_Punkt:
			{
			CComObject<CPVisInfoObject> *pNewVis = NULL;

				THROW_FAILED_HRESULT(CComObject<CPVisInfoObject>::CreateInstance(&pNewVis));
				pBase = pNewVis;
			}
			break;

		case VT_Linie:
			{
			CComObject<CLVisInfoObject> *pNewVis = NULL;

				THROW_FAILED_HRESULT(CComObject<CLVisInfoObject>::CreateInstance(&pNewVis));
				pBase = pNewVis;
			}
			break;

		case VT_Flaeche:
			{
			CComObject<CFVisInfoObject> *pNewVis = NULL;

				THROW_FAILED_HRESULT(CComObject<CFVisInfoObject>::CreateInstance(&pNewVis));
				pBase = pNewVis;
			}
			break;

		case VT_Text:
			{
			CComObject<CTVisInfoObject> *pNewVis = NULL;

				THROW_FAILED_HRESULT(CComObject<CTVisInfoObject>::CreateInstance(&pNewVis));
				pBase = pNewVis;
			}
			break;

		default:
			return E_UNEXPECTED;
		}

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}

	pBase -> SetVisInfo (pVis);
	*ppIVis = pBase;
	return S_OK;
}

short CVisObjExtension::GetNewVI (long lONr, VisInfo * & rpVI, 
	bool fHidden, long lMCode, short fFlags, char **cbModuleInfo)
{
// externe Behandlung
#if _ATL_VER >= 0x200
	{
	CVisInfoInterfaceBase *pBase = NULL;

		if (SUCCEEDED(CreateVisInfo (rpVI, &pBase))) {
		WDVisInfo Vis;

			if (SUCCEEDED(pBase -> GetDVisInfo (Vis.ppi())) &&
				S_OK == Fire_GetObjectVis (lONr, &Vis.p)) 
			{
			// zurück kopieren ...
				DELETE_OBJ(rpVI);
				rpVI = (VisInfo *)pBase -> GetVisInfo() -> Copy();

			int iResult = DO_UnChanged;

				Vis -> get_Changed (&iResult);
				return iResult;
			}
		}
	}
#else
	if (!m_cp.empty()) {
	CVisInfoInterfaceBase *pBase = NULL;

		if (SUCCEEDED(CreateVisInfo (rpVI, &pBase))) {
		WDVisInfo Vis;

			if (SUCCEEDED(pBase -> GetDVisInfo (Vis.ppi())) &&
				S_OK == m_cp.Fire_GetObjectVis (lONr, &Vis.p)) 
			{
			// zurück kopieren ...
				DELETE_OBJ(rpVI);
				rpVI = (VisInfo *)pBase -> GetVisInfo() -> Copy();

			int iResult = DO_UnChanged;

				Vis -> get_Changed (&iResult);
				return iResult;
			}
		}
	}
#endif // _ATL_VER

// eigene Behandlung 
	if (lMCode == -1) lMCode = m_lObjVisMCode;
	
	if (lMCode == -1 || m_pMWert == NULL) 
		return DO_UnChanged;

// MWert vom aktuellen Objekt holen
short iResult = DO_UnChanged;

	if (ReadTextMerkmal (TT_Objekt, lONr, lMCode, m_pMWert)) {
		pActChar = m_pMWert;
		pBuffEnd = pActChar + strlen (pActChar);

	// MWert als VI interpretieren
		if (m_fShowHidden)
			fFlags |= DF_ShowHidden;
		else
			fFlags &= ~DF_ShowHidden;

		iResult = ParseVisString (lONr, rpVI, fFlags, cbModuleInfo);
		if ((fHidden || !m_fShowHidden) && 
		    (iResult & (DO_Tagged|DT_WillDrawComplete)))
			iResult |= DT_NoDrawing;
		if (fFlags & DF_Analyze && !(fFlags & DF_Export)) 
			iResult &= ~DO_Tagged;	// nur Analyse, nicht zeichnen
	}

	return iResult;		// ÄnderungsStatus liefern
}


// Behandeln der FehlerNotifikationen -----------------------------------------
short CVisObjExtension::HandleErrorMessage (ERRORMESSAGE *pEM) 
{
	switch (pEM -> emiErrCode) {
	case WC_NOVISINFOPUNKT:
	case WC_NOVISINFOLINIE:
	case WC_NOVISINFOFLAECHE:
	case WC_NOVISINFOTEXT:
		{
		Pointer *pOldPointer = MWind() -> GetPointer();	// aktuellen Pointer merken
		short RC = HandleVisInfoError ((CVisError *)pEM -> empData);

			MWind() -> ChangePointer (pOldPointer);
			return RC;
		}

	case WC_SYMBOLNOTFOUND:
		if (m_fAllVisErrIgnore) return 2;
		break;
	}
	return 0;
}


// Eintrag für ObjMCode in PBD generieren -------------------------------------
bool SaveMCodeInPbd (
	long lMCode, char *pView, const char *KFormat, const char *LFormat, 
	bool fView, LONG lIdent)
{
// PBDEintrag zusammenstellen
char *pKText = new char [64];
char *pLText = new char [256];

	if (pKText == NULL || pLText == NULL) {
		DELETE_OBJ (pKText);
		return false;
	}

// Kurztext zusammenbauen
	wsprintf (pKText, KFormat ? KFormat : "%s", pView);
	if (strlen (pKText) > 31) {	// länger als max. KurzText
		pKText[31] = ')';	// SichtNamen abschneiden
		pKText[32] = '\0';
	}
		
	wsprintf (pLText, LFormat, pView);

PBDMERKMALEX TM;
bool iResult = true;

	if (0 != lIdent) {
		INITSTRUCT(TM, PBDMERKMALEX);
	} else {
		INITSTRUCT(TM, PBDMERKMAL);
	}

	TM.pbdTyp = 'm';
	TM.pbdCode = lMCode;
	TM.pbdKText = pKText;
	TM.pbdLText = pLText;	
	TM.pbdKTextLen = strlen (pKText);
	TM.pbdLTextLen = strlen (pLText);
	TM.ipbdMTyp = (fView ? 'b' : 'a') | PBDMERKMAL_SYSTEMFLAG;	// so tun, als ob's nur für Objekte wär
	TM.ipbdMLen = 256;
	TM.lIdent = lIdent;
	{
	ErrInstall EI (WC_NOMERKMAL);

		if (DEX_ModPBDData (TM) != EC_OKAY)
			iResult = false;
		else
			DEXN_PBDMCodeChanged (lMCode);
	}
	
// Speicher freigeben
	delete pKText;
	delete pLText;
	return iResult; 
}

#if defined(EXTVIS)
// Zeichnen eines Objektes entsprechend Vorgaben ------------------------------
DWORD CVisObjExtension::DrawCustom (long lONr, char *pVisModule, short &fFlags,
				      VisInfo *pVI, char *pVisInfoString)
{
	if (m_pVMT == NULL || m_hDC == 0) 
		return (DWORD)ResultFromScode (VISMODULE_E_GENERALERROR);

// sicherstellen, daß dieser VisModule geladen ist
CVisModule *pVM = m_pVMT -> FFindOrAdd (pVisModule, m_pActProject);

	if (pVM == NULL)
		return (DWORD)ResultFromScode (VISMODULE_E_GENERALERROR);
	
// VisModule auffordern, das Objekt zu behandeln
return (DWORD)pVM -> m_pIVisModule -> DrawObject (
			hWnd(), m_hDC, m_hTargetDC, lONr, 
			fFlags, pVI, pVisInfoString
	      );
}
#endif
