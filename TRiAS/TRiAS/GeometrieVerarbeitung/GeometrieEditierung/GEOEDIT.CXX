// Funktionen für Erweiterungs-DLL "Geometrie-Editierung"
// File: GEOEDIT.CXX
// W. Mörtl

#include "geoeditp.hxx"

#include <xtensnn.h>	// DEXN_ObjectCreated

#include <math.h>		// fabs()
#include <stdio.h>		// sprintf() für OutputDebugString
#include <resstrg.h>    // IDS_UIFORMAT
#include <defattr.h>	// StandardAttribute für Punkte, Linien etc. (DEF_SIZE_PUNKT_X, ...)

#include "geoeditr.h"	// IDS_LONGCLASSNAME

#include <geomdll.hxx>	// InitGeometrie

#include "version.h"	// GEOEDIT_MAJORVERSION, ...

#if defined(WIN32)		// nur für 32-Bit-Variante
#include <undoguid.h>
#include <iunredo.hxx>
#endif // WIN32

#include <TRiASHelper_i.c>// IID_IProgressIndicator2
#include "SmartInterfaces.h"
#include <initguid.h>	// zum Linken von IID_* und CLSID_* erforderlich
#include "editguid.h"	// CLSID_GeometrieEditierung

// Voraussetzungen für Arbeit mit Toolbars
#if defined(WIN32)
#include <toolguid.h>	// CLSID_TRiASUIOwner in uiowner.h
#include <itoolbar.h>	// ITRiASUIOwner in uiowner.h

#include "uiowner.h"	// CUIOwner

DefineSmartInterface(TRiASBarContainer);	// WTRiASBarContainer
DefineSmartInterface(TRiASBar);				// WTRiASBar
#endif // WIN32

#define BMPSIZE		5	// Anzahl der Buttons in der Bitmap
#define NUMBUTTONS	4	// Anzahl der zu installierenden Buttons
// Ende der Toolbar-Voraussetzungen

#include "geoedit.hxx"




#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


extern "C"
{
	extern UINT __DexNotify;
	extern UINT __DexCmd;		// globale Variable, die MessageWert enthält
}
    

/*
#ifdef WIN32
#define _DEBUG_HEAP
#if defined(_DEBUG_HEAP)
//debughilfe
#include <malloc.h>
bool HEAPCHECK (void)
{
int iStatus = _heapchk();

	if (iStatus != _HEAPOK) 
	{
		TX_ASSERT (iStatus == _HEAPOK);
		return false;	// hierauf den Breakpoint setzen; bei Fehler wird hier angehalten !!!!!!
	}

return true;
}
#else
#define HEAPCHECK()
#endif
#else
#define HEAPCHECK()
#endif
*/



    
// --------------------------------------------------------------------------------------------
BEGIN_OBJECT_MAP(ObjectMap)		// Makro
	OBJECT_ENTRY(CLSID_GeometrieEditierung, GeoEditExtension)
END_OBJECT_MAP()

_ATL_OBJMAP_ENTRY* GetObjectMap (void)
{
	return ObjectMap;
}

/*
//---------------------------------------------------------------------------------------------
// Die folgende Funktion muß vom Nutzer bereitgestellt werden. Sie liefert den (für jede
// Erweiterung neu zu generierenden) CLSID dieser Erweiterung.
// JEDE Erweiterung muß ihren eigenen ClassID haben. Dieser ID kann mit dem Tool GENGUID.EXE
// generiert werden. 

bool GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
	memcpy (&rClsID, &CLSID_GeometrieEditierung, sizeof (GUID));
	return true;
}
*/

// Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung sich selbst in der
// der RegDB registrieren soll (empfohlen!!).
// Der ProgID (hier 'TRiAS.Editierung.1') ist eine ZeichenKette, die die Erweiterung in der RegDB
// repräsentiert. Das Format sollte beibehalten werden. Die '... .1' steht für die VersionsNummer.
// Der KlassenName (hier die Stringresource hinter IDS_LONGCLASSNAME) ist eine normal-lesbare Zeichenkette,
// die lokalisiert wird (deshalb in der Ressource) und die Bezeichnung der Erweiterung definiert.

bool UpdateRegistry (bool bRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (bRegister)
	{
	// RegDB initialisieren ...
	bool bRet = ExtOleRegisterExtensionClass (g_hInstance, CLSID_GeometrieEditierung,
											  TEXT("TRiAS.Editierung.1"), IDS_LONGCLASSNAME,
											  GEOEDIT_MAJORVERSION, GEOEDIT_MINORVERSION,
											  EFPreLoad|EFUnLoadable|EFVisible);

	// durch Eintrag der Schlüssel "MinMarkGroesse" bzw. "MaxMarkGroesse", mit dessen Hilfe die Unter-
	// bzw. Obergrenze der Pixelgröße der Markierungsquadrate eingestellt werden kann
	ResourceFile RF (g_pDLLName);
	ResString RegistryExtPfad (ResID (IDS_REGEXTPFAD, &RF), 100);
	ResString UMarkGroesse (ResID (IDS_UMARKGROESSE, &RF), 30);
	ResString OMarkGroesse (ResID (IDS_OMARKGROESSE, &RF), 30);
	CCurrentUser cuExtConfig (RegistryExtPfad.Addr());	// Software\\uve\\TRiAS\\Extensions\\TRiAS.Editierung.1\\Config
	DWORD dwUWert = iUGr;	// default-Wert des Schlüssels "MinMarkGroesse"
	DWORD dwOWert = iOGr;	//  bzw. des Schlüssels "MaxMarkGroesse" (in edikonst.hxx definiert)

		// wenn Schlüssel "MinMarkGroesse" bzw. "MaxMarkGroesse" bisher noch nicht in der RegDB
		// existieren, dann jetzt anlegen
		if (false == cuExtConfig.GetDWORD (UMarkGroesse.Addr(), dwUWert))
			cuExtConfig.SetDWORD (UMarkGroesse.Addr(), dwUWert);

		if (false == cuExtConfig.GetDWORD (OMarkGroesse.Addr(), dwOWert))
			cuExtConfig.SetDWORD (OMarkGroesse.Addr(), dwOWert);

	// alte Schlüsselbezeichnungen in Software\\uve\\TRiAS\\Config löschen
	ResString RegistryPfad (ResID (IDS_REGPFAD, &RF), 100);
	ResString MarkGroesse (ResID (IDS_MARKGROESSE, &RF), 30);
	CCurrentUser cuConfig (RegistryPfad.Addr());	// Software\\uve\\TRiAS\\Config

		cuConfig.DeleteValue (MarkGroesse.Addr());
		cuConfig.DeleteValue (UMarkGroesse.Addr());
		cuConfig.DeleteValue (OMarkGroesse.Addr());

		return bRet;
	}
	else
	{
		// RegDB säubern
		// die eigenen Einträge müßten hier wieder gelöscht werden !!!
		return ExtOleUnregisterClass (CLSID_GeometrieEditierung, TEXT("TRiAS.Editierung.1"));
	}

	return true;	// alles ok
}

    

//-------------------------------------------------------------------------------------------------
// globale Konstanten
ResourceFile* pRF = NULL;
bool Mess;				// Flag für Ausgabe im DebugWindow (wird in InitExtension gesetzt)


/*
//-------------------------------------------------------------------------------------------------
// Die folgende Funktion muß bereitgestellt werden und lediglich ein Objekt von diesem ErweiterungTyp
// anlegen. Diese Funktion ist notwendig, da keine virtuellen Konstruktoren erlaubt sind.

CTriasExtension* NewExtension (void)
{
	return new GeoEditExtension ();
}
*/

//-------------------------------------------------------------------------------------------------
// Konstruktor
// Die Erweiterung wird von der Klasse 'CTriasExtension' abgeleitet, welche wiederum als
// einzigen Parameter den ResID des im Hauptfenster einzuhängenden Menüs übergeben bekommt.
GeoEditExtension :: GeoEditExtension (void)
				  : CTriasExtension (),		// keine separaten Menü's
					m_PPI(this)
{
	// Member initialisieren
char pcSichtname [iSichtL] = { '\0' };

	DEX_GetActiveSight (pcSichtname);
	if (DEX_TestActiveProject() &&    // ein Projekt ist schon geöffnet
		pcSichtname[0] != '\0')
		m_bSight = true;	// eine Sicht ist schon ausgewählt
	else
		m_bSight = false;	// noch keine Sicht ausgewählt

	m_dwCookie = 0L;		// Nummer des ConnectionPoint

//	m_pEDropTarget = NULL;
	m_pIGeoRein = NULL;	// für Ankopplung von georein.ext	
	m_bGeoRein = false;	// Ankopplung von georein.ext über Interface noch nicht erfolgt
	m_pIObjOper = NULL;	// für Ankopplung von objoper.ext
	m_bObjOper = false;	// Ankopplung von objoper.ext noch nicht erfolgt

	m_bHgrZeichnen1 = false;	// Hintergrund (durch DEX_ERASEBKGND ausgelöst) wird augenblicklich
								//  nicht gezeichnet
	m_bHgrZeichnen2 = false;	// Hintergrund (durch Update() ausgelöst) wird augenblicklich
								//  nicht gezeichnet

	m_pIL = NULL;		// Identifikatorliste
	m_pCT = NULL;		// Klasse für Zugriff auf Header-Informationen

	_isActive = false;	// noch keine der 4 Editier-Iconen ausgewählt
	_iNeuTool1 = -1;	// neues Werkzeug "Punkteditierung" noch nicht installiert
	_iNeuTool2 = -1;	// neues Werkzeug "Linieneditierung" noch nicht installiert
	_iNeuTool3 = -1;	// neues Werkzeug "Flächeneditierung" noch nicht installiert
	_iNeuTool4 = -1;	// neues Werkzeug "Geometrieveränderung" noch nicht installiert
	_bProj = false;		// kein Projekt geöffnet

	_RightButtonSem = false;	// rechte Maustaste wurde noch nicht gedrückt
	_LeftButtonSem = false;		// linke Maustaste wurde noch nicht gedrückt
	_KD = false;		// noch nicht RegisterNotification (WM_KEYDOWN, false)
	_KU = false;		// noch nicht RegisterNotification (WM_KEYUP, false)
	_LD = false;		// noch nicht RegisterNotification (WM_LBUTTONDOWN, false)
	_LU = false;		// noch nicht RegisterNotification (WM_LBUTTONUP, false)
	_RD = false;		// noch nicht RegisterNotification (WM_RBUTTONDOWN, false)
	_RU = false;		// noch nicht RegisterNotification (WM_RBUTTONUP, false)
	_MM = false;		// noch nicht RegisterNotification (WM_MOUSEMOVE, false)

	_pEO = NULL;		// neu zu erfassendes EObjekt
	_OTyp = OT_UNKNOWN;	// Objekttyp und
	_pcONText = NULL;	//  Objektname
	_bIns = false;		// der nächste editierte Punkt ist nicht Beginn einer neuen Insel
	
	m_hSubMenu = 0;		// MenuHandle nach Druck der rechten Maustaste bei Modifizieren von Objekten
	_DRO = NULL;		// zu zeichnende Linie (in dragline.cxx)
	_DRO1 = NULL;		// zu zeichnende Linie
	_DRO2 = NULL;		//   für Banding (in dragline.cxx)

	m_pGB = NULL;		// Baum für Geometrien der selektierten (markierten) Objekte
	m_pIOG = NULL;		// ObjektGeometrie des Objektes, auf das Cursor zeigt
	m_pMk = NULL;		// Markierunsquadrat, das verschoben oder gelöscht werden soll
	m_pMarkObj = NULL;	// Objekt, in dem sich Cursur befindet
	m_pVerlLin = NULL;	// Linie, die verlängert werden soll

	m_pFT = NULL;		// Fläche, die geteilt werden soll (entspricht dem über das Interface geholten m_pIOG)
	m_pMesser = NULL;	// Objekt (Kante) für Teilung von Flächenobjekten

	m_CurForm = PFEIL;
	m_SternCursor = NULL;	// eigener Cursor, wenn Cursor auf Stützpunkt (Geometrie-Modifizierung)
	m_TrennCursor = NULL;	// eigener Cursor, wenn Cursor auf Strecke
	m_KreuzCursor = NULL;	// eigener Cursor, wenn Cursor auf Stützpunkt und CTRL-Taste gedrückt
	m_InnerhCursor = NULL;	// eigener Cursor, wenn Cursor innerhalb eines markierten Objektes
	m_FangCursor = NULL;	// eigener Cursor, wenn Cursor auf Stützpunkt (Stützpunkt-Angraben)
	m_OldCursor = NULL;		// vorhergehender eigener Cursor

	m_bIsDropSource = false;	// DragDrop (noch) nicht von mir ausgelöst
	m_iVerz = GetProfileInt ("windows", "DragMinDist", DD_DEFDRAGMINDIST);
	m_plObjNrVO = NULL;
	m_pPolyPoly = NULL;
	m_piPolyCounts = NULL;

	m_dimDots = GetDotsPerMM (NULL);	// Pixel pro Millimeter für den Bildschirm

// Pixelanzahl für Markierungsquadrat aus der RegDB entnehmen
ResourceFile RF (g_pDLLName);
ResString RegistryExtPfad (ResID (IDS_REGEXTPFAD, &RF), 100);	
ResString UMarkGroesse (ResID (IDS_UMARKGROESSE, &RF), 30);	
ResString OMarkGroesse (ResID (IDS_OMARKGROESSE, &RF), 30);	
CCurrentUser cuExtConfig (RegistryExtPfad.Addr());
DWORD dwUWert, dwOWert;

	if (cuExtConfig.GetDWORD (UMarkGroesse.Addr(), dwUWert))
		m_iUMarkGr = (short)dwUWert;
	else
		m_iUMarkGr = iUGr;

	if (cuExtConfig.GetDWORD (OMarkGroesse.Addr(), dwOWert))
		m_iOMarkGr = (short)dwOWert;
	else
		m_iOMarkGr = iOGr;

	m_AktGesLaenge = 0.0;	// aktuelle Gesamtlänge einer editierten Linie
	m_AktGesFlaeche = 0.0;	// aktueller Gesamtflächeninhalt einer editierten Fläche
}


//-------------------------------------------------------------------------------------------------
// Destruktor
GeoEditExtension :: ~GeoEditExtension (void)
{
//	DELETE (m_pEDropTarget);
	DELETE_VEC (m_plObjNrVO);
	DELETE_VEC (m_pPolyPoly);
	DELETE_VEC (m_piPolyCounts);
}



//=================================================================================================
// Im folgenden werden alle durch diese Erweiterung überladenen virtuellen Funktionen definiert.

//-------------------------------------------------------------------------------------------------
// Folgende Funktion wird einmalig nach der erfolgreichen Installation der Erweiterung durch
// TRiAS gerufen. Hier erfolgen alle notwendigen Initialisierungen.
STDMETHODIMP_(bool) GeoEditExtension :: InitExtension (short iMode)
{
	if (!CTriasExtension :: InitExtension (iMode))
		return false;

	InitGeometrie (hWnd(), __DexNotify, __DexCmd);
	pRF = &RF();

	TX_ASSERT (pRF != NULL);

	if (iMode != LoadState())	// Erweiterung war schon teilweise geladen gewesen
		return true;			// jetzt ist sie voll zu sehen

	// TRiAS-Messages anfordern (nur 1 Parameter)
	// ich interessiere mich für die von TRiAS verschickten Meldungen, für
	RegisterNotification (DEX_PROJECTOPEN);			// Projekt öffnen
	RegisterNotification (DEX_PROJECTCLOSE);		// Projekt schließen
	RegisterNotification (DEX_SETACTIVETOOL);		// neues Werkzeug selektiert
	RegisterNotification (DEX_ERASEBKGND);			// Beginn des Hintergrundzeichnens
	RegisterNotification (DEX_PAINTTOPLAYER);		// Ende des Hintergrundzeichnens
	RegisterNotification (DEX_OBJECTACTIVATED);		// Objekt selektiert (markiert)
	RegisterNotification (DEX_OBJECTDEACTIVATED);	// Objekt deselektiert
	RegisterNotification (DEX_TXICHANGED);			// Veränderungen in der Identifikator-Datenbank
	RegisterNotification (DEX_DELOBJECT);			// Löschen eines Objektes
	RegisterNotification (DEX_N_SCROLLING_HORZ);	// horizontales Scrollen
	RegisterNotification (DEX_N_SCROLLING_VERT);	// vertikales Scrollen
	RegisterNotification (DEX_OBJECTCHANGED);		// Objektgeometrie wurde verändert
	RegisterNotification (DEX_SIGHTSELECTED);		// eine Sicht wurde ausgewählt

	InitAndOPEN ();

// neue Werkzeuge installieren
	if (_iNeuTool1 == -1)	// alle Werkzeug-Iconen werden immer gemeinsam installiert
	{
#if defined(WIN32)
		InstallToolbarButtons ();
		_iNeuTool1 = ID_TOOL_PUNKTEDIT;
		_iNeuTool2 = ID_TOOL_LINIENEDIT;
		_iNeuTool3 = ID_TOOL_FLAECHENEDIT;
		_iNeuTool4 = ID_TOOL_MODIFYOBJ;
#else
		_iNeuTool1 = InstallTool (ResID (NEUEDITP, pRF), ResString (ResID (IDS_NEUEDITPKT, pRF), 20));
		_iNeuTool2 = InstallTool (ResID (NEUEDITL, pRF), ResString (ResID (IDS_NEUEDITLIN, pRF), 20));
		_iNeuTool3 = InstallTool (ResID (NEUEDITF, pRF), ResString (ResID (IDS_NEUEDITFLA, pRF), 20));
		_iNeuTool4 = InstallTool (ResID (MODEDIT, pRF), ResString (ResID (IDS_MODGEOMETRIE, pRF), 20));
#endif
	}

// georein.ext automatisch nachladen
	ResString GeoRein (ResID (IDS_GEOREIN, pRF), 20);
	
	DEX_ExternalLoadExtension (GeoRein.Addr());

	Mess = _GetDebugOutputFlag ();	// Ausgabe im DebugWindow (true), sonst false
	
	return true;
} // InitExtension


//-------------------------------------------------------------------------------------------------
// alle Interface-Geschichten müssen in UnLoadExtension aufgelöst werden
STDMETHODIMP_(bool) GeoEditExtension :: UnLoadExtension (void)
{
// Erweiterung passivieren, d.h. keine der 4 Editier-Iconen ist mehr ausgewählt
// (bis jetzt war aber eine ausgewählt)
	if (_isActive)
	{
		// Ich habe augenblicklich kein Interesse an den von Windows verschickten Meldungen zu
		// KEYDOWN, KEYUP, ... Deshalb die Windows-Messages (2 Parameter) wieder abmelden.
		UnRegisterNotificationM (WM_KEYDOWN, false, _KD);
		UnRegisterNotificationM (WM_KEYUP, false, _KU);
		UnRegisterNotificationM (WM_LBUTTONDOWN, false, _LD);
		UnRegisterNotificationM (WM_LBUTTONUP, false, _LU);
		UnRegisterNotificationM (WM_RBUTTONDOWN, false, _RD);
		UnRegisterNotificationM (WM_RBUTTONUP, false, _RU);
		UnRegisterNotificationM (WM_MOUSEMOVE, false, _MM);

		// die 2 nachfolgenden Zeilen sind für den Fall erforderlich, wenn die Erweiterung zwar
		// herausgenommen, das Projekt aber noch nicht geschlossen wird
		if (DEX_ActiveObjectsCount() > 0)	// mindestens 1 Recherchefenster geöffnet
			StuetzpunkteDeMarkieren ();	// Markierungen aller selektierten Objekte löschen

		_isActive = false;
	}

// TRiAS-Messages wieder abmelden
// ich interessiere mich nicht mehr für die von TRiAS verschickten Meldungen
	UnRegisterNotification (DEX_SIGHTSELECTED);		// eine Sicht wurde ausgewählt
	UnRegisterNotification (DEX_DELOBJECT);			// Objekt wurde gelöscht
	UnRegisterNotification (DEX_TXICHANGED);
	UnRegisterNotification (DEX_OBJECTDEACTIVATED);	// Objekt wurde deselektiert
	UnRegisterNotification (DEX_OBJECTACTIVATED);	// Objekt wurde selektiert
	UnRegisterNotification (DEX_ERASEBKGND);		// Beginn des Hintergrundzeichnens
	UnRegisterNotification (DEX_PAINTTOPLAYER);		// Ende des Hintergrundzeichnens
	UnRegisterNotification (DEX_SETACTIVETOOL);		// Auswahl einer Editier-Icone
	UnRegisterNotification (DEX_PROJECTCLOSE);		// Schließen eines Projektes
	UnRegisterNotification (DEX_PROJECTOPEN);		// Öffnen eines Projektes
	UnRegisterNotification (DEX_N_SCROLLING_HORZ);	// horizontales Scrollen
	UnRegisterNotification (DEX_N_SCROLLING_VERT);	// vertikales Scrollen
	UnRegisterNotification (DEX_OBJECTCHANGED);		// Objektgeometrie wurde verändert

// restliche Abmeldungen
	UnLoadAndCLOSE ();

// Werkzeuge wieder entfernen
	if (_iNeuTool1 != -1)   // alle 4 Werkzeug-Iconen werden immer gemeinsam installiert
	{
#if defined(WIN32)
		RemoveToolbarButton ();
#else
		RemoveTool (_iNeuTool1);
		RemoveTool (_iNeuTool2);
		RemoveTool (_iNeuTool3);
		RemoveTool (_iNeuTool4);
#endif
		_iNeuTool1 = -1;
		_iNeuTool2 = -1;
		_iNeuTool3 = -1;
		_iNeuTool4 = -1;
	}

	DELETE (m_pGB);	// siehe Kommentar in UnLoadAndCLOSE()

// Bezug zum Interface der Erweiterung "GeometrieBereinigung" lösen
	if (m_pIGeoRein)
	{
		m_pIGeoRein -> Release ();
		m_pIGeoRein = NULL;
	}

// Bezug zur Erweiterung "Objektoperationen" lösen
	if (m_pIObjOper)
	{
		m_pIObjOper -> Release ();
		m_pIObjOper = NULL;
	}

// Standard-Cursor wieder einstellen
	DELETE (m_SternCursor);
	DELETE (m_TrennCursor);
	DELETE (m_KreuzCursor);
	DELETE (m_InnerhCursor);
	DELETE (m_FangCursor);
	if (m_CurForm != PFEIL)		// doch nicht 27.02.97
		NeuerCursor ();

	return CTriasExtension :: UnLoadExtension();
} // UnLoadExtension


//-------------------------------------------------------------------------------------------------
// Diese Funktion dient der Behandlung der MenüKommandos der Erweiterung
STDMETHODIMP_(bool) GeoEditExtension :: MenuCommand (UINT MenuItemID, HWND)
{
	switch (MenuItemID)
	{
		case IDM_KOORDMOD:
//		{
//		Point Pnt = m_pMk -> MPoint();
//		Punkt Pkt = DBKoordinaten (Pnt);

			EditVertex (m_pIOG, m_lInd);
//		}
			break;

		case IDM_VERTDELETE:
			StuetzpunktLoeschen();
			break;

		case IDM_VERTEX:
			break;

		case IDM_LINIEVERL:
			LinienobjektVerlaengern();
			break;

		case IDM_OBJDREHEN:
			break;

		case IDM_OBJPART:		// Schnittlinie für Flächenteilung bilden
			SchnittlinieBilden();	// beginnend mit Punkt, bei dem rechte MTaste gedrückt wurde
			break;

		case IDM_ADDINSEL:
			break;

		case IDM_SUBINSEL:
			InselLoeschen ();
			break;

		case IDM_RECHTWINKL:	// Rechtwinkligkeit bezogen auf die angeklickte Strecke erzeugen
			break;

		case IDM_OBJDELETE:		// Objekt löschen
			ObjektLoeschen ();
			break;

		case IDM_ABBRUCH:
			break;

		default:
			TX_ASSERT (false);
	}

	return true;
} // MenuCommand
 

//-------------------------------------------------------------------------------------------------
// Diese Funktion wird gerufen, wenn ein Menü auf dem Bildschirm erscheinen soll
STDMETHODIMP_(bool) GeoEditExtension :: MenuInit (HMENU hMenu, LPARAM, HWND)
{
	if (hMenu == m_hSubMenu && m_pIOG)	// Menü nach Betätigung der rechten Maustaste bei Modifizierung
										//  eines Objektes
	{
	short iOT;		// Typ des Objektes, auf dem aktuell der Cursor steht

		m_pIOG -> GetObjTyp (&iOT);

		if (m_CurForm == TRENNER)		// Cursor auf Strecke
		{
			TX_ASSERT (iOT != OT_PUNKT);

		ResString Text (ResID (IDS_VERTEX, pRF), 50);

			// Menü-Eintrag "Koordinaten verändern" durch "Stützpunkt hinzufügen" ersetzen
			ModifyMenu (hMenu, IDM_KOORDMOD+MenuOffset(), MF_BYCOMMAND|MF_STRING,
						IDM_VERTEX+MenuOffset(), Text.Addr());

			EnableMenuItem (hMenu, IDM_VERTEX+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		}

		if (OT_KANTE == iOT)		// Objekt ist eine Linie
		{
		long lSPAnz;

			m_pIOG -> GetCnt (&lSPAnz);
//			if (m_lInd == 0 ||								// 1. oder    (17.1.97) 
//				(m_lInd == lSPAnz-1 && m_CurForm == STERN))	//  letzter Stützpunkt eines Linienobjektes
			if ((m_lInd == 0 || m_lInd == lSPAnz-1) &&		// 1. oder letzter Stützpunkt eines Linienobjektes
				m_CurForm == STERN)							//  und STERN-Cursor
				EnableMenuItem (hMenu, IDM_LINIEVERL+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
			else
				EnableMenuItem (hMenu, IDM_LINIEVERL+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		}

		if (OT_FLAECHE == iOT)		// Objekt ist eine Fläche
		{
		short iKontInd = -1;	// Index der Kontur, auf der sich der Cursor befindet
		long lInd; 				// wird  hier nicht ausgewertet
		IndPos IP;				// wird  hier nicht ausgewertet

			m_pIOG -> IndexTest (m_lInd, &iKontInd, &lInd, &IP);
			if (1 <= iKontInd)	// Cursor auf Innenkontur
				EnableMenuItem (hMenu, IDM_SUBINSEL+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
			else				// Cursor auf Außenkontur
				EnableMenuItem (hMenu, IDM_SUBINSEL+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		}
	}
	return true;
} // MenuInit


// ------------------------------------------------------------------------------------------------
// Diese Funktion wird bei Systemereignissen diverser Natur gerufen, z.B. bei Anklicken sowohl
// der neuen als auch der anderen Iconen
STDMETHODIMP_(LRESULT) GeoEditExtension :: Notification (WPARAM iMsg, LPARAM lPar)
{	
	switch (iMsg)
	{
		case DEX_SETACTIVETOOL:
		{
			UnRegisterNotificationM (WM_MOUSEMOVE, false, _MM);	// kein Interesse an Mausbewegung

			// eine der 4 Editier-Iconen wurde ausgewählt (GeoEditierung ist damit aktiviert)
			if ((short)lPar == _iNeuTool1 || (short)lPar == _iNeuTool2 || (short)lPar == _iNeuTool3 ||
				(short)lPar == _iNeuTool4)
			{
				_isActive = true;

//			// Bildschirmhöhe des aktuellen Ausschnittes für Kippen der y-Koordinate bestimmen
//			Rectangle CRc = MVWind() -> CanvasRect();

				// Die nachfolgende Subtraktion von 1 ist Kosmetik, um mit Hartmuts Koordinatenanzeige
				// konform zu gehen !!!!!!!!!!!!
//				_iBH = CRc.Top() - CRc.Bottom() - 1;
				
				UnRegisterNotificationM (WM_KEYDOWN, false, _KD);	// kein Interesse an Tastatur-down
				UnRegisterNotificationM (WM_KEYUP, false, _KU);		// kein Interesse an Tastatur-up
				UnRegisterNotificationM (WM_LBUTTONUP, false, _LU);	// kein Interesse an l.M-up
				UnRegisterNotificationM (WM_RBUTTONUP, false, _RU);	// kein Interesse an r.M-down

				// ein Werkzeug für Neuerfassung von Objekten wurde ausgewählt
				if ((short)lPar == _iNeuTool1 || (short)lPar == _iNeuTool2 || (short)lPar == _iNeuTool3)
				{
					// ich interessiere mich für die von Windows verschickten Meldungen beim Drücken
					// der linken und rechten Maustaste
					RegisterNotificationM (WM_LBUTTONDOWN, false, _LD);	// sage mir, ob l.M-down?
					RegisterNotificationM (WM_RBUTTONDOWN, false, _RD);	// sage mir, ob r.M-down?
					
					// Objekttyp des neu zu editierenden Objektes entsprechend dem ausgewählten
					// Werkzeug festlegen
					if ((short)lPar == _iNeuTool1)
						_OTyp = OT_PUNKT;
					else if ((short)lPar == _iNeuTool2)
						_OTyp = OT_KANTE;
					else
						_OTyp = OT_FLAECHE;
				}

				// Werkzeug "Geometrie modifizieren" wurde ausgewählt
				else
				{
					UnRegisterNotificationM (WM_LBUTTONDOWN, false, _LD);	// kein Interesse an l.M-down
					UnRegisterNotificationM (WM_RBUTTONDOWN, false, _RD);	// kein Interesse an r.M-down
				}

				if (DEX_ActiveObjectsCount() > 0)	// wenn Objekte selektiert (markiert) sind, dann ...
				{
					AnzRuecksetzen ();			// m_iAnz im GeometrieBaum rücksetzen
					GeometrienErgaenzen ();		// evtl. weitere ObjektGeometrien in GeometrieBaum einfügen
					StuetzpunkteMarkieren ();	// Stützpunkte markieren
					RegisterNotificationM (WM_MOUSEMOVE, false, _MM);	// sage mir, ob Maus bewegt wurde?
				}
			}

			// keine der 4 Editier-Iconen wurde ausgewählt (GeoEditierung ist damit passiviert)
			else if (_isActive)
			{
//				if (m_CurForm != PFEIL)		27.02.97
					NeuerCursor ();	// wieder Standard-Cursor einstellen

				// Erweiterung wurde passiviert, d.h. keine der 4 Editier-Iconen ist mehr ausgewählt
				// (bis jetzt war aber eine ausgewählt)
				// Ich habe augenblicklich kein Interesse an den von Windows verschickten Meldungen zu
				// KEYDOWN, KEYUP, ... Deshalb die Windows-Messages (2 Parameter) wieder abmelden.
				UnRegisterNotificationM (WM_KEYDOWN, false, _KD);
				UnRegisterNotificationM (WM_KEYUP, false, _KU);
				UnRegisterNotificationM (WM_LBUTTONDOWN, false, _LD);
				UnRegisterNotificationM (WM_LBUTTONUP, false, _LU);
				UnRegisterNotificationM (WM_RBUTTONDOWN, false, _RD);
				UnRegisterNotificationM (WM_RBUTTONUP, false, _RU);
				UnRegisterNotificationM (WM_MOUSEMOVE, false, _MM);
		
				if (DEX_ActiveObjectsCount() > 0)	// mindestens 1 Recherchefenster geöffnet
					StuetzpunkteDeMarkieren ();	// Markierungen aller selektierten Objekte löschen

				_isActive = false;
			}
		}
			break;


		case DEX_PROJECTOPEN:			// Projekt wird geöffnet
			InitAndOPEN ();
			if ((DEX_QueryMode() & QMSysAdmin) == 0 &&	// Anzeige "Speicherform" versteckt und
				DEX_GetROMode() == 1)					// Datenbank schreibgeschützt
				DEX_Error (RC_geoedit, WC_TEMPORAER);	// Warnung: Speicherung nur temporär möglich
			break;


		case DEX_PROJECTCLOSE:			// Projekt wird geschlossen
			UnLoadAndCLOSE ();
			DELETE (m_pGB);		// 8.4.97
			_bProj = false;
			break;
	

		case DEX_ERASEBKGND:			// kommt vor dem Zeichnen des Hintergrundes
			m_bHgrZeichnen1 = true;	// Hintergrund wird gezeichnet

			// kein Interesse an Mausbewegung bis Hintergrundzeichnen nach Löschen des Menüs beendet ist
			UnRegisterNotificationM (WM_MOUSEMOVE, false, _MM);

			if (_LeftButtonSem && m_pMk)
				MVWind() -> Draw (m_pMk);
			break;


		case DEX_PAINTTOPLAYER:			// kommt nach dem Zeichnen des Hintergrundes
		{
			// Reaktion auf Bewegung der Maus wurde bis zum Ende des Hintergrundzeichnens gesperrt
			// nachdem eine Dialog oder Menü gelöscht wurde
			RegisterNotificationM (WM_MOUSEMOVE, false, _MM);	// sage mir, ob Maus bewegt wurde?

			if (_LeftButtonSem && m_pMk)
				MVWind() -> Draw (m_pMk);

		short iAT = DEX_GetActiveTool();
	
			if (iAT == _iNeuTool1 || iAT == _iNeuTool2 || iAT == _iNeuTool3 || iAT == _iNeuTool4)
			{
				if (DEX_ActiveObjectsCount() > 0)	// mindestens 1 Recherchefenster geöffnet
				{
					DEX_GetExposedArea (m_rcHintergrund);	// Hintergrundbereich bestimmen
					StuetzpunkteMarkieren ();	// Markierungen erneut zeichnen
				}

				if (_DRO && _pEO)	// es befindet sich ein DragLineObject im Aufbau
				{
				// Pt ist der Anfangspunkt des Linienobjektes und wird aus dem letzten Punkt des
				// bis dahin neu editierten Objektes gebildet
				Point Pt = BSKoordinaten (m_LastPunkt.X(), m_LastPunkt.Y());

					if (Pt.X() > 0) Pt.X()--;	// wegen Fehler bei Hartmut notwendig
					if (Pt.Y() > 0) Pt.Y()--;	// eine Korrektur bei ihm hätte zu große Folgen an anderen Stellen

					LRMouseButtonDn (Pt);
				}
				m_bHgrZeichnen1 = false;	// Hintergrund wurde gezeichnet (darf nicht vor
											//  StuetzpunkteMarkieren() gesetzt werden)
				break;
			}
				
			m_bHgrZeichnen1 = false;	// Hintergrund wurde gezeichnet
			
			if (_pEO == NULL)
				break;
			
			switch (_pEO -> isA())
			{
				case OT_PUNKT:
					break;
			
				case OT_KANTE:
					KanteNeuZeichnen ((Kante*)_pEO, MVWind());
					break;
	
				case OT_FLAECHE:
				{
				short iKA = ((Masche*)_pEO) -> KantenAnz ();	// Anzahl der bis jetzt editierten Konturen
		
					for (register short i = iKA-1; i >= 0; i--)
						KanteNeuZeichnen (&((Masche*)_pEO)->KA(i), MVWind());	// Neuzeichnen aller Konturen
				}
					break;

				default:
					TX_ASSERT (false);
					break;
			}
		}
			break;
									   
	
		case DEX_OBJECTACTIVATED:	// Objekt wurde selektiert (markiert)
		{
		short iAT = DEX_GetActiveTool();

			if (iAT == _iNeuTool1 || iAT == _iNeuTool2 ||
				iAT == _iNeuTool3 || iAT == _iNeuTool4)
			{
				GeometrieInBaum (lPar);

				TX_ASSERT (m_pGB != NULL);

			CTable tab (*m_pGB);

				if (tab.Find (&lPar))
				{
				GeometrieKnotenLock kl (tab);

					if (kl)
					{
					IObjektGeometrie* pIOG = NULL;
					HRESULT hr = kl -> GetIOG (&pIOG);

						if (SUCCEEDED(hr))
						{
							MarkierungenBearbeiten (pIOG);	// Markierungen setzen
							if (pIOG) pIOG -> Release();	// AddRef() in GetIOG()
						}
					}
					else
    					DEX_Error (RC_geoedit, EC_SYSERROR);
				}
			}
		}
			break;

					
		case DEX_OBJECTDEACTIVATED:	// Objekt wurde deselektiert
		case DEX_DELOBJECT:			// Objekt wurde aus DB gelöscht
		{
			if (! m_pGB) break;		// m_pGB wird bei DEX_PROJECTCLOSE gelöscht

		bool bFind = false;	// Objekt nicht im GeometrieBaum m_pGB gefunden
		short iAT = DEX_GetActiveTool();
		CTable tab (*m_pGB);

			if (tab.Find (&lPar))
			{
			GeometrieKnotenLock kl (tab);

				if (kl)
				{
					if (iAT == _iNeuTool1 || iAT == _iNeuTool2 ||
						iAT == _iNeuTool3 || iAT == _iNeuTool4)
					{
					IObjektGeometrie* pIOG = NULL;
					HRESULT hr = kl -> GetIOG (&pIOG);

						if (SUCCEEDED(hr))
						{
							MarkierungenBearbeiten (pIOG, false);	// Markierungen löschen
							if (pIOG) pIOG -> Release();	// AddRef() in GetIOG()
						}
					}
					bFind = true;
				}
				else
    				DEX_Error (RC_geoedit, EC_SYSERROR);
			}

			// Geometrie muß außerhalb der Find()-Schleife aus Baum gelöscht werden, weil sie dann
			// nicht mehr gelockt ist
			if (bFind)
				GeometrieAusBaum (lPar);
		}
			break;


		case DEX_TXICHANGED:		// IdentListe aktualisieren
			if (m_pIL)
			{
				if (lPar == 0)
				{
				CEierUhr Wait (MVWind());
				
					// alles neu einlesen
					DELETE (m_pIL);
					m_pIL = new IdentList();
					if (! m_pIL)
					{                                                                      
						DEX_Error (RC_geoedit, EC_NOMEMORY);
						return false;
					}
				}
				else
					m_pIL -> UpdateEntry (lPar);
			}
			break;


		case DEX_N_SCROLLING_HORZ:			// horizontales Scrollen
		case DEX_N_SCROLLING_VERT:			// vertikales Scrollen
		{
		int iActTool = DEX_GetActiveTool();

			// es wurde kein Werkzeug für Neueditierung ausgewählt
			if ((iActTool != _iNeuTool1 && iActTool != _iNeuTool2 && iActTool != _iNeuTool3) ||
				! _DRO)	// es befindet sich kein DragLineObject im Aufbau 
				break;

			MVWind() -> Draw (_DRO);	// alte Lage der aktuellen Strecke löschen durch
			break;						// invertiertes Neuzeichnen
		}


		case DEX_OBJECTCHANGED:	// Objektgeometrie wurde verändert
								// (z.B. nach Wegspeichern an TRiAS oder nach Undo bzw. Redo)
		{
			if (!m_pGB)	// m_pGB wird bei DEX_PROJECTCLOSE gelöscht
				break;

		bool bFind = false;	// Objekt nicht im GeometrieBaum m_pGB gefunden
		short iAnz = 0;		// Anzahl, wie oft lPar-Objekt (durch möglicherweise mehrere Recherchefenster)
							// im GeometrieBaum eingetragen ist
		CTable tab (*m_pGB);

			if (tab.Find (&lPar))
			{
			GeometrieKnotenLock kl (tab);

				if (kl)
				{
					iAnz = kl -> GetAnz();
					bFind = true;	// Objekt wurde im GeometrieBaum m_pGB gefunden
					kl -> SetAnz (1);
				}
				else DEX_Error (RC_geoedit, EC_SYSERROR);
			}
			if (bFind)						// wenn lPar-Objekt im GeometrieBaum enthalten ist,
			{
				GeometrieAusBaum (lPar);	//  dann zuerst löschen und
				for (register short i = 1; i <= iAnz; i++)
					GeometrieInBaum (lPar);	//  danach die veränderte Geometrie eintragen
			}
		}
			break;


		case DEX_SIGHTSELECTED:
			if (lPar != 0)
				m_bSight = true;
			else
				m_bSight = false;
			break;


		default:	// Notifikationen der Basisklasse
			break;
	}

	return CTriasExtension :: Notification (iMsg, lPar);

} // Notification



// -----------------------------------------------------------------------------------------------
// Bearbeitung von Windows-Meldungen
STDMETHODIMP_(LRESULT) GeoEditExtension :: WindowsNotification (UINT wMsg, WPARAM wPar, LPARAM lPar)
{
#if defined(WIN32)
	if (NULL == MVWind()) return false;		// kein Projekt geöffnet
#endif // WIN32

Point Pt (LOWORD (lPar), HIWORD (lPar));	// Punkt in Bildschirmkoordinaten, auf den die Maus zeigt
Rectangle CRc = MVWind() -> CanvasRect();

// Die nachfolgende Subtraktion von 1 ist Kosmetik, um mit Hartmuts Koordinatenanzeige
// konform zu gehen !!!!!!!!!!!!
int iBH = CRc.Top() - CRc.Bottom() - 1;	// Höhe des TRiAS-Fensters

	Pt.Y() = iBH - Pt.Y();			// y-Koordinate drehen


	switch (wMsg)
	{
		case WM_KEYDOWN:			// eine Taste wurde gedrückt
			return KeyDown (wPar);
		
		case WM_KEYUP:				// eine Taste wurde losgelassen
			return KeyUp (wPar);

		case WM_LBUTTONDOWN:		// linke Maustaste gedrückt
//{
//char Buff [100] = { '\0' };
//sprintf (Buff, "BH = %lu; y = %lu\n", _iBH, Pt.Y());			          
//OutputDebugString (Buff);
			if (iBH > 0)
				return LeftMouseDown (Pt);
			else break;
//}			      
		case WM_LBUTTONUP:			// linke Maustaste losgelasssen
			if (iBH > 0)
				return LeftMouseUp (Pt);
			else break;
		
		case WM_MOUSEMOVE:			// Maus wird bewegt
			if ((m_PtOld.X() != Pt.X() || m_PtOld.Y() != Pt.Y()) &&	// echt neue Position der Maus
				iBH > 0)
			{
				UnRegisterNotificationM (WM_MOUSEMOVE, false, _MM);	// kein Interesse an verschachtelten Mausbewegungen
				MouseMove (Pt);
				m_PtOld = Pt;	// Position retten
				RegisterNotificationM (WM_MOUSEMOVE, false, _MM);	// sage mir wieder, ob Maus bewegt wurde?
				return false;	// dadurch wird WM_MOUSEMOVE an TRiAS weitergereicht und kann z.B.
								// auch für mitlaufende Koordinaten genutzt werden
			}
			else break;

		case WM_RBUTTONDOWN:		// rechte Maustaste gedrückt
			if (iBH > 0)
				return RightMouseDown (Pt);
			else break;
		
		case WM_RBUTTONUP:			// rechte Maustaste losgelassen
			return RightMouseUp ();

		default:
			TX_ASSERT (false);
			break;
	}
	
	return false;
} // WindowsNotification


// ------------------------------------------------------------------------------------------------
// Aktionen, die bei InitExtension und DEX_PROJECTOPEN gleich sind
bool GeoEditExtension :: InitAndOPEN (void)
{
// IdentList und CoordTransX anlegen
	if (DEX_TestActiveProject ())    // ein Projekt ist schon geöffnet
	{
		DELETE (m_pIL);		// vorsichtshalber löschen
		DELETE (m_pCT);
		m_pIL = new IdentList();	// IdentList nur anlegen, wenn ein Projekt geöffnet ist !!!
		m_pCT = new CoordTransX();	// Klasse für Zugriff auf Header-Informationen
		if (! m_pIL || ! m_pCT)
		{                                                                      
			DEX_Error (RC_geoedit, EC_NOMEMORY);
			DELETE (m_pIL)
			return false;
		}

	// Cursoren anlegen
		DELETE (m_SternCursor);
		DELETE (m_TrennCursor);
		DELETE (m_KreuzCursor);
		DELETE (m_InnerhCursor);
		DELETE (m_FangCursor);
		m_SternCursor = new Pointer (ResID (IDC_CURSTERN, pRF));	// Cursor auf Stützpunkt(Modifizierung)
		m_TrennCursor = new Pointer (ResID (IDC_CURTRENN, pRF));	// Cursor auf Strecke
		m_KreuzCursor = new Pointer (ResID (IDC_CURKREUZ, pRF));	// Cursor auf Stützpunkt mit Löschmöglichkeit
		m_InnerhCursor = new Pointer (ResID (IDC_CURINNERHALB, pRF));// Cursor innerhalb Objekt (ohne CRTL-Taste)
		m_FangCursor = new Pointer (ResID (IDC_CURPALETTE, pRF));	// Cursor auf Stützpunkt (Angraben)
		if (!m_SternCursor || !m_TrennCursor || !m_KreuzCursor ||
			!m_InnerhCursor || !m_FangCursor)
		{
			DELETE (m_SternCursor);
			DELETE (m_TrennCursor);
			DELETE (m_KreuzCursor);
			DELETE (m_InnerhCursor);
			DEX_Error (RC_geoedit, EC_NOMEMORY);
			return false;
		}


	// Puffer für Objektname und Baum für Geometrien der selektierten (markierten) Objekte anlegen
		DELETE_VEC (_pcONText);
		DELETE (m_pGB);
		_pcONText = new char [maxTextLaenge+1];	// Objektname (maxTextLaenge in geokonst.hxx definiert)
		m_pGB = new GeometrieBaum;				// Baum für Geometrien der selektierten Objekte
		if (!_pcONText || !m_pGB)
		{                                                                      
			DELETE_VEC (_pcONText);
			DEX_Error (RC_geoedit, EC_NOMEMORY);
			return false;
		}
		_pcONText [0] = '\0';

		_bProj = true;
	}

	return true;
} // InitAndOPEN


// ------------------------------------------------------------------------------------------------
// Aktionen, die bei UnLoadExtension und DEX_PROJECTCLOSE gleich sind
void GeoEditExtension :: UnLoadAndCLOSE (void)
{
// dynamische Felder freigeben
	DELETE (_pcONText);	// Objektname des neu zu erfassenden Objektes
	DELETE (_pEO);  	// neu zu erfassendes ElementarObjekt
	DELETE (m_pMk);		// Markierunsquadrat, auf das Maus zuletzt gezeigt hat
	DELETE (m_pMarkObj);
	DELETE (m_pCT);
	DELETE (m_pIL);
// !!!!! m_pGB kann an dieser Stelle noch nicht freigegeben werden, da bei DEX_SETACTIVETOOL
// noch StuetzpunkteDeMarkieren() gerufen wird
	if (m_pIOG) m_pIOG -> Release();
	m_pIOG = NULL;

// die Cursoren NUR bei UnLoadExtension und NICHT bei DEX_PROJECTCLOSE freigeben

} // UnLoadAndCLOSE


#if defined(WIN32)		// nur für 32-Bit-Variante
//-------------------------------------------------------------------------------------------------
// Hinzufügen der Knöpfe zur WerkzeugLeiste 
 
// Dazu wird über TRiAS der Container aller Toolbars besorgt (QueryInterface), danach die gewünschte
// ToolBar (hier: "Werkzeuge") gesucht und gefunden. Mit AddBitmap wird dieser ToolBar die Bitmap
// (Streifen) mit allen ButtonBmps übergeben und anschließend werden die Buttons selbst installiert
// (hier 4).

// Der UIOwner ist so eine Art Feld von CallBack-Funktionen, die durch die ToolBar in verschiedenen
// Situationen gerufen werden, um diverse Informationen zu bekommen bzw. bestimmte Aktionen
// auszulösen.
bool GeoEditExtension :: InstallToolbarButtons (void)
{
// Finden der ToolBar "Werkzeuge"
WTRiASBarContainer ToolBars;
HRESULT hr = m_pXtnSite -> QueryInterface (IID_ITRiASBarContainer, ToolBars.ppv());

	if (FAILED(hr)) return false;

WTRiASBar Bar;
ResString resTools (ResID (IDS_TOOLBARWERKZEUG, pRF), 32);	// "Werkzeuge" ist der Name der Toolbar

	hr = ToolBars -> FindTRiASBar (resTools, Bar.ppi());
	if (S_OK != hr) return false;

ITRiASUIOwner* pIUIOwner = NULL;

	try
	{
	// Hinzufügen der Buttons
	WTRiASToolBar ToolBar = Bar;		// throws_com_error
	int iOffset = 0;

		hr = ToolBar -> AddBitmap (g_hInstance, IDB_TOOLBAREDIT, BMPSIZE, &iOffset);
		if (FAILED(hr)) _com_issue_error (hr);

		hr = CUIOwner::_CreatorClass::CreateInstance (NULL, IID_ITRiASUIOwner, (LPVOID*)&pIUIOwner);
		if (FAILED(hr)) _com_issue_error (hr);

	// für jeden zu installierenden Button diese Struktur bereitstellen
	//				  BitmapNr     CmdID		         ButtonState ButtonStyle
	TBBUTTON tb[] = { { iOffset,   ID_TOOL_PUNKTEDIT,    0,          TBSTYLE_CHECKGROUP, 0L, 0, },
					  { iOffset+1, ID_TOOL_LINIENEDIT,   0,          TBSTYLE_CHECKGROUP, 0L, 0, },
					  { iOffset+2, ID_TOOL_FLAECHENEDIT, 0,          TBSTYLE_CHECKGROUP, 0L, 0, },
					  { iOffset+3, ID_TOOL_MODIFYOBJ,    0,          TBSTYLE_CHECKGROUP, 0L, 0 }};

		hr = ToolBar -> AddButtons (tb, NUMBUTTONS, pIUIOwner);
		if (FAILED(hr)) _com_issue_error (hr);
		pIUIOwner -> Release ();

	}
	catch (...)
	{
		if (pIUIOwner) 	pIUIOwner -> Release();
		TX_TRACE1 ("Button kann nicht zur Toolbar hinzugefügt werden: %s\n", resTools.Addr());
		return false;
	}

	return true;
} // InstallToolbarButtons


//-------------------------------------------------------------------------------------------------
// Entfernen der installierten Knöpfe aus der Toolbar

// Im Prinzip das gleiche, wie das Installieren, nur das die Funktion DeleteItem() gerufen wird.
// CommandToIndex() liefert die aktuelle Position unseres Buttons über seinen CmdID.
bool GeoEditExtension :: RemoveToolbarButton (void)
{
// Finden der ToolBar "Werkzeuge"
WTRiASBarContainer ToolBars;
HRESULT hr = m_pXtnSite -> QueryInterface (IID_ITRiASBarContainer, ToolBars.ppv());

	if (FAILED(hr)) return false;

WTRiASBar Bar;
ResString resTools (ResID (IDS_TOOLBARWERKZEUG, pRF), 32);	// "Werkzeuge" ist der Name der Toolbar

	hr = ToolBars -> FindTRiASBar (resTools, Bar.ppi());
	if (S_OK != hr) return false;

	try
	{
	// Entfernen der Buttons
	WTRiASToolBar ToolBar = Bar;		// throws_com_error
	int iIndex = -1;

		hr = ToolBar -> CommandToIndex (ID_TOOL_PUNKTEDIT, &iIndex);
		if (FAILED(hr)) _com_issue_error (hr);
		hr = ToolBar -> DeleteItem (iIndex);
		if (FAILED(hr)) _com_issue_error (hr);
		hr = ToolBar -> CommandToIndex (ID_TOOL_LINIENEDIT, &iIndex);
		if (FAILED(hr)) _com_issue_error (hr);
		hr = ToolBar -> DeleteItem (iIndex);
		if (FAILED(hr)) _com_issue_error (hr);
		hr = ToolBar -> CommandToIndex (ID_TOOL_FLAECHENEDIT, &iIndex);
		if (FAILED(hr)) _com_issue_error (hr);
		hr = ToolBar -> DeleteItem (iIndex);
		if (FAILED(hr)) _com_issue_error (hr);
		hr = ToolBar -> CommandToIndex (ID_TOOL_MODIFYOBJ, &iIndex);
		if (FAILED(hr)) _com_issue_error (hr);
		hr = ToolBar -> DeleteItem (iIndex);
		if (FAILED(hr)) _com_issue_error (hr);


	}
	catch (...)
	{
		TX_TRACE1 ("Button kann nicht aus der Toolbar entfernt werden: %s\n", resTools.Addr());
		return false;
	}

	return true;
} // RemoveToolbarButton
#endif // WIN32


// -----------------------------------------------------------------------------------------------
// eine Taste der Tastatur wurde gedrückt
bool GeoEditExtension :: KeyDown (WPARAM wPar)
{
	if (! _isActive)		// Erweiterung ist nicht aktiviert, d.h. es ist keine der
		return false;		//   4 Editier-Iconen ausgewählt

	switch (m_CurForm)
	{
		// Beeinflussung der Cursorform durch CTRL-Taste (bei Modifizierung)
		case STERN:		// Cursor hat STERN-Form,
		{
		short iOT;

			m_pIOG -> GetObjTyp (&iOT);

			if (VK_CONTROL == wPar/* &&	//  CTRL-Taste gedrückt und
				OT_PUNKT != iOT*/)		//  kein Punktobjekt
			{
				NeuerCursor (KREUZ, m_KreuzCursor);
				UnRegisterNotificationM (WM_RBUTTONDOWN, false, _RD);	// kein Interesse an r.M-down
			}
		}
			break;

		// Beeinflussung der Cursorform durch SHIFT-Taste (bei Angraben)
		case FANGEN:	// Cursor hat FANGEN-Form und
			if (wPar == VK_SHIFT)		//  SHIFT-Taste gedrückt
				NeuerCursor (m_CurFormOld, m_OldCursor);
			break;
	}

	UnRegisterNotificationM (WM_KEYDOWN, false, _KD);			// kein Interesse an Tastatur-down
	RegisterNotificationM (WM_KEYUP, false, _KU);				// sage mir, ob Tastatur-up?
	return false;
} // KeyDown


// -----------------------------------------------------------------------------------------------
// eine Taste der Tastatur wurde losgelassen
bool GeoEditExtension :: KeyUp (WPARAM wPar)
{
	if (! _isActive)		// Erweiterung ist nicht aktiviert
		return false;
	
	switch (m_CurForm)
	{
		// Beeinflussung der Cursorform durch CTRL-Taste
		case KREUZ:			// Cursor hat noch KREUZ-Form und
			if (VK_CONTROL == wPar &&	//  CTRL-Taste losgelassen
			!m_bHgrZeichnen1)
			{
				NeuerCursor (STERN, m_SternCursor);
				RegisterNotificationM (WM_RBUTTONDOWN, false, _RD);		// sage mir, ob r.M-down?
			}
			break;

		// Beeinflussung der Cursorform durch SHIFT-Taste (bei Angraben)
		case PFEIL:			// Cursor hat noch PFEIL-Form und
			if (VK_SHIFT == wPar &&		//  SHIFT-Taste losgelassen	und
				_LeftButtonSem &&		//  linke Maus-Taste ist gedrückt, um Stützpunkt zu verschieben
				StuetzpunkteTesten (_ptMS, &m_pIOG, m_lInd) &&
				!m_bHgrZeichnen1)
				NeuerCursor (FANGEN, m_FangCursor);
			break;

		case STERN:			// Cursor hat noch STERN- oder TRENNER-Form und
		case TRENNER:
			if (VK_SHIFT == wPar &&		//  SHIFT-Taste losgelassen	und
				_LeftButtonSem &&		//	linke Maus-Taste ist gedrückt
				StuetzpunkteTestenGrab (_ptMS) &&
				!m_bHgrZeichnen1)
				NeuerCursor (FANGEN, m_FangCursor);
			break;
	}

	UnRegisterNotificationM (WM_KEYUP, false, _KU);		// kein Interesse an Tastatur-up
	RegisterNotificationM (WM_KEYDOWN, false, _KD);		// was macht Tastatur-down?
	return false;
} // KeyUp


// -----------------------------------------------------------------------------------------------
// linke Maustaste wurde gedrückt
bool GeoEditExtension :: LeftMouseDown (Point Pt)
{
	if (! _isActive)		// Erweiterung ist nicht aktiviert
		return false;

bool bRet = true;	// Rückkehrwert

	_LeftButtonSem = true;		// linke Maustaste wurde gedrückt

int iActTool = DEX_GetActiveTool();

// Editierung einer neuen Geometrie
	if (iActTool != _iNeuTool4)
	{
		if (iActTool != _iNeuTool1)		// Editierung eines neuen Linien- oder Flächenobjektes
			bRet =  LeftMouseDownNew (Pt);
		else							// Editierung eines neuen Punktobjektes
		{								// linke MTaste hat bei Punktobjekt keine Bedeutung, deshalb
			_LeftButtonSem = false;		// gilt dies wie "linke Maustaste nicht gedrückt"
			bRet = false;
		}
	}

// Modifizierung einer vorhandenen Geometrie
	else
		bRet = LeftMouseDownModify (Pt);

	if (_LeftButtonSem)
	{
		RegisterNotificationM (WM_LBUTTONUP, false, _LU);		// sage mir, ob l.M-up?
		UnRegisterNotificationM (WM_LBUTTONDOWN, false, _LD);	// kein Interesse an l.M-down
	}

	return bRet;
} // LeftMouseDown


// -----------------------------------------------------------------------------------------------
// linke Maustaste wurde losgelassen
bool GeoEditExtension :: LeftMouseUp (Point Pt)
{
	if (! _isActive ||		// Erweiterung ist nicht aktiviert
		! _LeftButtonSem)	// linke Maustaste wurde nicht gedrückt
		return false;

	_LeftButtonSem = false;	// linke Maustaste wurde losgelassen

// Editierung einer neuen Geometrie
	if (DEX_GetActiveTool() != _iNeuTool4)
		LMouseButtonUp ();

// Modifizierung einer vorhandenen Geometrie
	else
	{
		if (!m_pMesser &&	// keine "Messer"-Bildung und
			!m_pVerlLin)	//  keine Linienverlängerung
			LeftMouseUpModify (Pt);
	}

	RegisterNotificationM (WM_LBUTTONDOWN, false, _LD);	// sage mir, ob l.M-down?
	UnRegisterNotificationM (WM_LBUTTONUP, false, _LU);	// kein Interesse an l.M-up
		
	return true;
} // LeftMouseUp


// -----------------------------------------------------------------------------------------------
// Maus wurde bewegt
// Rückgabe von true, wenn etwas vernünftiges gemacht wurde, sonst false
bool GeoEditExtension :: MouseMove (Point Pt)
{
	_ptMS = Pt;		// aktuelle Mausspitze

	if (! _isActive)		// Erweiterung ist nicht aktiviert
		return false;

// Editierung einer neuen Geometrie
	if (DEX_GetActiveTool() != _iNeuTool4 &&
		_RightButtonSem == false)		// abfangen: rechte Maustaste wurde gedrückt
	{				
		LMouseDrag (Pt);

		// Cursorform evtl. modifizieren:
		// wenn Cursor noch FANGEN-Form hat, dann nur Testung, ob sich Cursor noch in dem Marker
		// befindet, der diese Form ausgelöst hat; wenn ja, dann passiert erst einmal gar nichts,
		// bei nein sofort erst einmal Umwandlung in PFEIL; erst danach Testung aller Stützpunkte
		if (m_CurForm == FANGEN)	// Cursor FANGEN-Form
		{
			if (PointInMarker (Pt, m_pMk) == false)	// Cursor nicht mehr im auslösenden Marker
				NeuerCursor ();
		}
		else						// Cursor keine FANGEN-Form
			CursorWechselNewGrab (Pt);

		AktuelleWerteAnzeigen (Pt);	// aktuelle Länge bzw. Flächeninhalt in Statuszeile anzeigen

		return true;
	}

// Modifizierung einer vorhandenen Geometrie
	if (0 == DEX_ActiveObjectsCount())	// keine selektierten (markierten) Objekte vorhanden
		return false;

	// evtl. mittels gedrückter linker MTaste Stützpunkt verschieben
	if (_LeftButtonSem &&			// linke Maustaste wurde gedrückt
		INOBJEKT != m_CurForm &&	// aber nicht Cursor innerhalb des Objektes
		!m_bHgrZeichnen1)
	{
		if (STERN == m_CurForm ||
			(FANGEN == m_CurForm && STERN == m_CurFormOld))
		{
			MoveMarker (Pt);	// schon vorhandenen Stützpunkt verschieben
			CursorWechselModGrab (Pt, STERN, m_SternCursor);
			return true;
		}
		if (TRENNER == m_CurForm ||
			(FANGEN == m_CurForm && TRENNER == m_CurFormOld))
		{
			Banding (Pt);		// neu gesetzten Stützpunkt verschieben
			CursorWechselModGrab (Pt, TRENNER, m_TrennCursor);
		}
		return true;
	}

	
	if (m_pVerlLin/* &&	// ein Linienobjekt wird verlängert	   27.03.97
		!m_bHgrZeichnen1 && !m_bHgrZeichnen2*/)
		if (!m_bHgrZeichnen1 && !m_bHgrZeichnen2)
		{
			LMouseDrag (Pt);
			AktuelleWerteAnzeigen (Pt);	// aktuelle Länge in Statuszeile anzeigen
			CursorWechselNewGrab (Pt);
			return true;
		}
		else
			return false;

	if (m_pMesser/* &&	// die Editierung eines "Messers" zur Flächenteilung wurde angefangen
		!m_bHgrZeichnen1 && !m_bHgrZeichnen2*/)			// 27.03.97
		if (!m_bHgrZeichnen1 && !m_bHgrZeichnen2)
		{
			LMouseDrag (Pt);
			CursorWechselMod();
			return true;
		}
		else
			return false;

	// ansonsten nur Cursorform modifizieren:
	switch (m_CurForm)
	{
		// wenn Cursor noch STERN- oder KREUZ-Form hat, dann nur Testung, ob sich Cursor noch
		// in dem Marker befindet, der diese Form ausgelöst hat; wenn ja, dann passiert erst
		// einmal gar nichts, bei nein sofort erst einmal Umwandlung in PFEIL; erst danach
		// Testung aller Stützpunkte
		case STERN:
		case KREUZ:
			if (false == PointInMarker (Pt, m_pMk))	// Cursor nicht mehr im auslösenden Marker
//			{
//				NeuerCursor ();
//				if (!m_pMesser && !m_bLinVerl)
//					UnRegisterNotificationM (WM_RBUTTONDOWN, false, _RD);	// kein Interesse an r.M-down
//			}
				CursorWechselMod();		// 24.1.97
			return true;

		// wenn Cursor noch INOBJEKT-Form hat, dann Testung, ob DragDrop zu starten ist (d.h.
		// ob linke MausTaste gedrückt ist, mindestens m_iVerz Pixel bewegt wurden und kein
		// "Messer" für Flächenschnitt im Aufbau), ansonsten gleich vollständige Testung
		case INOBJEKT:
#if defined(_DRAGDROP)
			if (_LeftButtonSem &&			// linke MTaste wurde gedrückt
				(abs(Pt.X() - m_StartPt.X()) >= m_iVerz ||
				 abs(Pt.Y() - m_StartPt.Y()) >= m_iVerz) &&
				 NULL == m_pMesser)			// kein "Schnittmesser" im Aufbau
			{
				DoDragDropAction (MK_LBUTTON);		// "Drag" starten

				// nachfolgende Befehle sind erforderlich, um WM_LBUTTONUP nachzubilden, das
				// in OLE untergeht
				_LeftButtonSem = false;
				MVWind() -> MouseTrap (Off);
				RegisterNotificationM (WM_LBUTTONDOWN, false, _LD);	// sage mir, ob l.M-down?
				UnRegisterNotificationM (WM_LBUTTONUP, false, _LU);	// kein Interesse an l.M-up
				return true;
			}
			// bei nicht-if gleich weiter zum default-Zweig
#endif // _DRAGDROP

		default:		// u.a. auch TRENNER-Form
			CursorWechselMod();
			return true;
	} // switch
} // MouseMove


// -----------------------------------------------------------------------------------------------
// rechte Maustaste wurde gedrückt
bool GeoEditExtension :: RightMouseDown (Point Pt)
{
	if (! _isActive ||		// Erweiterung ist nicht aktiviert
		(DEX_GetActiveTool() == _iNeuTool4 &&	// Modifizierung einer vorhandenen Geometrie aber
		// Cursor nicht auf Marker bzw. Strecke	eines Linien- bzw. Flächenobjektes und
		(STERN != m_CurForm && TRENNER != m_CurForm &&
		// Cursor nicht auf einem Punktobjekt und
		(OT_PUNKT != m_iOT || INOBJEKT != m_CurForm) &&
		// Cursur nicht PFEIL-Form oder "Messer" für Flächenteilung wird nicht gebildet und keine
		// Verlängerung eines Linienobjektes
		(PFEIL != m_CurForm || (!m_pMesser && !m_pVerlLin)))))
		return false;

	_RightButtonSem = true;	// rechte Maustaste wurde gedrückt
	_ptRM = Pt;				// Punkt, bei dem rechte Maustaste gedrückt wurde

	// Modifizierung einer vorhandenen Geometrie (hier wird getestet, ob bei Aufbau eines "Messers" für
	// Flächenteilung der gesetzte Punkt innerhalb der zu teilenden Fläche liegt; trifft diese nicht zu,
	// gilt dies wie "rechte MTaste nicht gedrückt"
	if (DEX_GetActiveTool() == _iNeuTool4)
		RightMouseDownModify ();	// modifiziert evtl. _RightButtonSem

	if (_RightButtonSem)
	{
		RMouseButtonDn ();			// DrawObject für Nachziehen der letzten Strecke löschen
		RegisterNotificationM (WM_RBUTTONUP, false, _RU);		// sage mir, ob r.M-up?
		UnRegisterNotificationM (WM_RBUTTONDOWN, false, _RD);	// kein Interesse an r.M-down
		UnRegisterNotificationM (WM_MOUSEMOVE, false, _MM);		// kein Interesse an Mausbewegung
	}

	return true;
} // RightMouseDown


// -----------------------------------------------------------------------------------------------
// rechte Maustaste wurde losgelassen
bool GeoEditExtension :: RightMouseUp (void)
{
	if (! _isActive ||		// Erweiterung ist nicht aktiviert
		! _RightButtonSem)	// rechte Maustaste wurde nicht gedrückt
		return false;

	_RightButtonSem = false;		// rechte Maustaste wurde losgelassen

	RegisterNotificationM (WM_RBUTTONDOWN, false, _RD);	// sage mir, ob r.M-down?
	RegisterNotificationM (WM_MOUSEMOVE, false, _MM);	// sage mir, ob Maus bewegt wurde?
	UnRegisterNotificationM (WM_RBUTTONUP, false, _RU);	// kein Interesse an r.M-up

// Editierung einer neuen Geometrie
	if (DEX_GetActiveTool() != _iNeuTool4)
		return RightMouseUpNew (_ptRM);	// mit Punkt, bei dem rechte Maustaste gedrückt wurde

// Modifizierung einer vorhandenen Geometrie
	else
		return RightMouseUpModify (_ptRM);
} // RightMouseUp


// -----------------------------------------------------------------------------------------------
// linke Maustaste wurde bei Neueditierung gedrückt
bool GeoEditExtension :: LeftMouseDownNew (Point Pt)
{
	if (_pEO == NULL)       // der 1. Punkt wurde editiert
	{
		// Maus einfangen, damit die Maus-Messages auch dann weiterhin empfangen werden können, wenn
		// sich der Cursor außerhalb des Anwendungsbereiches (d.h. über einem anderen Fenster) befindet
		MVWind() -> MouseTrap (On);

		RegisterNotificationM (WM_MOUSEMOVE, false, _MM);	// sage mir, ob Maus bewegt wurde?
	}

	m_LastPunkt = NeuerPunktMitGrab (Pt);	// aktuell editierter Punkt (evtl. mit Grab-Funktion)
		
	if (_OTyp == OT_KANTE)		// Linienobjekt
	{
		if (NeueKante () == false)
			return false;
	}
			
	if (_OTyp == OT_FLAECHE)	// Flächenobjekt
	{
		if (NeueFlaeche () == false)
			return false;
	}

	LRMouseButtonDn (Pt);

	return true;
} // LeftMouseDownNew


// -----------------------------------------------------------------------------------------------
// rechte Maustaste wurde bei Neueditierung losgelassen
bool GeoEditExtension :: RightMouseUpNew (Point Pt)
{
	m_LastPunkt = NeuerPunktMitGrab (Pt);	// aktuell editierter Punkt (evtl. mit Grab-Funktion)
		
	switch (_OTyp)
	{
		case OT_PUNKT:
			_pEO = new Punkt (m_LastPunkt);
			if (! _pEO)
			{                                                                      
				DEX_Error (RC_geoedit, EC_NOMEMORY);
				return false;
			}
			break;
			
		case OT_KANTE:
			if (NeueKante () == false)
				return false;
			break;
			
		case OT_FLAECHE:
			if (NeueFlaeche () == false)
				return false;
			break;
					
		default:        // weder Punkt, Linie bzw. Fläche, was dann ?
			TX_ASSERT (false);
			return false;
	}
			
	MVWind() -> MouseTrap (Off);	// Maus wieder freigeben
	
NeuEditDlg* pNED = NULL;

	if (! m_pVerlLin)	// echte Neueditierung
		pNED = new NeuEditDlg (MVWind(), *m_pIL, _pEO, _pcONText);
	else				// Linienverlängerung
	{
	Punkt LePkt;	// der andere Endpunkt der zu verlängernden Kante
	KoOrd* plXK; KoOrd* plYK;

		m_pIOG -> GetX ((void**)&plXK);
		m_pIOG -> GetY ((void**)&plYK);

		if (m_bAnf)
		{
		long lSPAnz;

			m_pIOG -> GetCnt (&lSPAnz);
			LePkt.X() = plXK[lSPAnz-1];
			LePkt.Y() = plYK[lSPAnz-1];
		}
		else
		{
			LePkt.X() = plXK[0];
			LePkt.Y() = plYK[0];
		}

		pNED = new NeuEditDlg (MVWind(), *m_pIL, _pEO, _pcONText, &LePkt);
	}

	if (! pNED)
	{                                                                      
		DEX_Error (RC_geoedit, EC_NOMEMORY);
		return false;
	}

ObjContainer OC = EObjContainer (_pEO);
Point p = DialogPosit (&OC, pNED->GetSize());

	// kein Interesse an Mausbewegung, da andererseits sonst z.B. vor idb_Speichern() noch eine
	// weitere ungebetene SendMessage käme
	UnRegisterNotificationM (WM_MOUSEMOVE, false, _MM);	// kein Interesse an Mausbewegung

	pNED -> ChangePosition (p);
	if (m_pVerlLin)
	{
	ResString rsCapt (ResID (IDS_LINIEVERL, pRF), 30);

		pNED -> SetCaption (rsCapt.Addr());
	}
	pNED -> Show ();

AktNeu Erg = (AktNeu) pNED -> Result (); // Rückgabewert der Aktion im pNED-Fenster

	switch (Erg)
	{                                                                                     
		case BEENDEN:
			if (! m_pVerlLin)
				idb_Speichern (pNED);			// echte Neueditierung
			else
				idb_SpeichernLinienVerl (pNED);	// Linienverlängerung
			DEX_SetMessageString ("");	// Anzeige in Statuszeile löschen
			break;
			
		case VERWERFEN:
			DELETE (_pEO);				// Objekt wird gelöscht
			if (m_pVerlLin)
			{
				m_pVerlLin -> Release();
				m_pVerlLin = NULL;
			}
			DEX_SetMessageString ("");	// Anzeige in Statuszeile löschen
			break;
				
		case FORTSETZEN:	// entspr. inhaltlich dem "linke Maustaste gedrückt"
			DELETE (pNED);   // Dialog-Fenster vor MouseTrap (On) wieder zerlegen
			Pt = idb_Fortsetzen ();
			LRMouseButtonDn (Pt);
			_ptRM = Pt;
			MVWind() -> MouseTrap (On);	// Maus einfangen (Erläuterung s. o.)
			break;
			
		case INSEL:
			DELETE (pNED);	// Dialog-Fenster vor MouseTrap (On) wieder zerlegen
			_bIns = true;	// der nächste editierte Punkt ist Beginn einer Insel
			MVWind() -> MouseTrap (On);	// Maus einfangen (Erläuterung s. o.)
			break;

		default:
			TX_ASSERT (false);
			break;
	}
							   
	DELETE (pNED);
	RegisterNotificationM (WM_MOUSEMOVE, false, _MM);	// sage mir, ob Maus bewegt wurde?
			
	return true;
} // RightMouseUpNew


// -----------------------------------------------------------------------------------------------
// neue Kante editieren
bool GeoEditExtension :: NeueKante (void)
{
	if (_pEO == NULL)       // aus dem 1. editierten Punkt Kantenanfang aufbauen
	{						
		m_AktGesLaenge = 0.0;
		if (m_pVerlLin)	// bei Linienverlängerung noch die bisherige Länge hinzurechnen
		{
		DoublePair DAP, DEP;	// Stützpunkte im ASC-Format
		long lSPA;
		KoOrd* plXK; KoOrd* plYK;

			m_pIOG -> GetCnt (&lSPA);
			m_pIOG -> GetX ((void**)&plXK);
			m_pIOG -> GetY ((void**)&plYK);

			for (long i = 0; i < lSPA-1; i++)
			{
				m_pCT -> UnScale (plXK[i], plYK[i], &DAP.X(), &DAP.Y());
				m_pCT -> UnScale (plXK[i+1], plYK[i+1], &DEP.X(), &DEP.Y());
				m_AktGesLaenge += m_pCT -> CoordTransDistance (&DAP, &DEP);
			}
		}


		_pEO = new Kante (&m_LastPunkt.X(), &m_LastPunkt.Y(), 1);
		if (! _pEO)
		{                                                                      
			DEX_Error (RC_geoedit, EC_NOMEMORY);
			return false;
		}
	}
	else					// weitere Punkte wurden editiert
	{
		((Kante*)_pEO) -> AddPunkt (&m_LastPunkt.X(), &m_LastPunkt.Y(), 1, -1);
		m_AktGesLaenge += m_AktLaenge;
	}
	return true;
} // NeueKante


// -----------------------------------------------------------------------------------------------
// neue Fläche editieren
bool GeoEditExtension :: NeueFlaeche (void)
{
	if (_pEO == NULL)       // 1. Punkt
	{
		m_AktGesFlaeche = 0.0;
		m_AktInsel = 0.0;
		_pEO = new Masche (&m_LastPunkt.X(), &m_LastPunkt.Y(), 1);
		if (! _pEO)
		{                                                                      
			DEX_Error (RC_geoedit, EC_NOMEMORY);
			return false;
		}
	}
	else						// weitere Punkte
	{
		if (!_bIns)             // keine neue Insel
		{
			((Masche*)_pEO) -> AddPunkt (&m_LastPunkt.X(), &m_LastPunkt.Y(), 1, -1, -1);
			if (((Masche*)_pEO) -> KantenAnz() == 1)
				m_AktGesFlaeche += m_AktDreieck;
			else
				m_AktInsel += m_AktDreieck;
		}
		else                    // neue Insel aufbauen
		{
			((Masche*)_pEO) -> AddKante (&m_LastPunkt.X(), &m_LastPunkt.Y(), 1, -1);
			_bIns = false;
			m_AktGesFlaeche = fabs(m_AktGesFlaeche) - fabs(m_AktInsel);
			m_AktInsel = 0.0;
		}
	}
	return true;
} // NeueFlaeche


// -----------------------------------------------------------------------------------------------
// neuen Cursor einstellen und Anzeige in Statuszeile entsprechend der Cursorform modifizieren
void GeoEditExtension :: NeuerCursor (Curs CurForm, Pointer* pCursor)
{
	if (PFEIL == CurForm)	// Cursor soll auf Standardform "Pfeil" zurückgestellt werden
	{
		m_OldCursor = MVWind() -> ChangePointer (NULL);

	char pcLeer [5] = "";

		SendMessage (__hWndM, 0x362, 0, (LPARAM)pcLeer);
	}
	else					// Cursor soll Sonderform bekommen
	{
		TX_ASSERT (pCursor);

		if (KREUZ == CurForm && false == DeleteAllow())
			return;	// Stützpunkt löschen ist nicht möglich

		m_OldCursor = MVWind() -> ChangePointer (pCursor);
		if (pCursor)
		{
			pCursor -> Show();
			StatuszeileModifizieren (CurForm);
		}
	}
	m_CurFormOld = m_CurForm;	// bisherige Cursorform retten
	m_CurForm = CurForm;
} // NeuerCursor


// -----------------------------------------------------------------------------------------------
// Testen, ob das Löschen eines Stützpunktes möglich ist; dann Rückgabe von true, sonst false
bool GeoEditExtension :: DeleteAllow (void)
{
short iOT;

	m_pIOG -> GetObjTyp (&iOT);

	// der Stützpunkt eines Punktobjekte ist an dieser Stelle nicht löschbar
	if (iOT != OT_KANTE && iOT != OT_FLAECHE)
		return false;

long lSPAnz;

	m_pIOG -> GetCnt (&lSPAnz);

	// Kante mit höchstens 2 Stützpunkten
	if (OT_KANTE == iOT)
	{
		if (lSPAnz <= 2)
			return false;
		return true;
	}

	// Kontur einer Fläche mit höchstens 4 Stützpunkten
	if (OT_FLAECHE == iOT)
	{
	short iKontInd = -1;	// Index der Kontur, in der ein Punkt gelöscht werden soll
	long lInd; 	// wird  hier nicht ausgewertet
	IndPos IP;	// wird  hier nicht ausgewertet

		m_pIOG -> IndexTest (m_lInd, &iKontInd, &lInd, &IP);
		
	long* plK;

		m_pIOG -> GetLPCnt (&plK);
		
		if (plK[iKontInd] <= 4)
			return false;
	}
	
	return true;

} // DeleteAllow


// -----------------------------------------------------------------------------------------------
// Text in der Statuszeile entsprechend der Cursorform modifizieren
void GeoEditExtension :: StatuszeileModifizieren (Curs CurForm)
{
	switch (CurForm)
	{
		case STERN:
		{
		ResString rsText (ResID (IDS_VERTEXMOVE, pRF), 100);

			SendMessage (__hWndM, 0x362, 0, (LPARAM)rsText.Addr());
			return;
		}

		case TRENNER:
		{
		ResString rsText (ResID (IDS_VERTEXADD, pRF), 100);

			SendMessage (__hWndM, 0x362, 0, (LPARAM)rsText.Addr());
			return;
		}

		case KREUZ:
		{
		ResString rsText (ResID (IDS_VERTEXDELETE, pRF), 100);

			SendMessage (__hWndM, 0x362, 0, (LPARAM)rsText.Addr());
			return;
		}

		case INOBJEKT:
		{
		ResString rsText (ResID (IDS_OBJECTCOPY, pRF), 100);

			SendMessage (__hWndM, 0x362, 0, (LPARAM)rsText.Addr());
			return;
		}

		case FANGEN:
		{
		ResString rsText (ResID (IDS_INMARKER, pRF), 100);

			SendMessage (__hWndM, 0x362, 0, (LPARAM)rsText.Addr());
			return;
		}
	}
} // StatuszeileModifizieren


// -----------------------------------------------------------------------------------------------
// Cursor bei Mausbewegung zum Angraben entsprechend der Bildschirmposition wechseln.
// Steht der Cursor auf einem markierten Stützpunkt, muß er die FANGEN-Form haben, ansonsten
// hat er die PFEIL-Form.
void GeoEditExtension :: CursorWechselNewGrab (Point Pt)
{
	if (0 == DEX_ActiveObjectsCount())	// kein Recherchefenster geöffnet
		return;

	if (StuetzpunkteTesten (Pt, &m_pIOG, m_lInd))	// Cursor in einem Marker
	{
	bool bShift = GetKeyState (VK_SHIFT) < 0;	// SHIFT-Taste nicht/gedrückt (false/true)

		RegisterNotificationM (WM_KEYDOWN, false, _KD);		// sage mir, ob Tastatur-down?

		if (m_CurForm != FANGEN &&	// noch nicht FANGEN-Form	doch nicht 27.02.97
			bShift == false)		// SHIFT-Taste nicht gedrückt
		{
			NeuerCursor (FANGEN, m_FangCursor);
			return;
		}
		if (m_CurForm == FANGEN &&	// schon FANGEN-Form		doch nicht 27.02.97
			bShift)					// SHIFT-Taste gedrückt
		{
			NeuerCursor ();
			return;
		}
	}

	// Cursor nicht in einem Marker
//	if (m_CurForm != PFEIL)			// noch nicht PFEIL-Form		27.02.97
		NeuerCursor ();
} // CursorWechselNewGrab


// -----------------------------------------------------------------------------------------------
// Rechteck, in dem das editierte Objekt _pEO liegt, neu zeichnen
void GeoEditExtension :: ObjektZeichnen (void)
{
double dQuot;   // Quotient von Bezugsmaßstab und Darstellungsmaßstab

	// Quotient aus Bezugs- und Darstellungsmaßstab ermitteln
	DEX_GetActiveScaling (dQuot);
	if (dQuot > 0) dQuot *= 100.;
	else
	{
		TX_ASSERT (dQuot > 0);
		dQuot = 1.;   // um Division durch Null vorzubeugen
	}
	
ObjContainer OC;	// Container um editiertes Objekt
Point PLO, PRU;		// linker oberer (PLO) bzw. rechter unterer Eckpunkt (PRU) von OC im Point-Format
HANDLEVISINFO HVI;

	INITSTRUCT(HVI, HANDLEVISINFO);	// Initialisierung
	HVI.m_lIdent = DEX_GetLastIdent (); // Identifikator
	HVI.m_pDesc = NULL;			// beschreibender Text
	HVI.m_pView = NULL;			// SichtName (aktuelle Sicht: NULL)

	switch (_pEO -> isA())
	{
		case OT_PUNKT:
		{
		PVISINFO PVI;
		SIZE sizePG;
		
			HVI.m_iVTyp = VTPunkt;				// VisInfoTyp
			HVI.m_pVI = &(PVI.m_VI);			// generischer Pointer auf VisInfo
			if (! DEX_GetIdentVisInfo (HVI))	// RückkehrCode ausgewertet
			{
				sizePG.cx = DEF_SIZE_PUNKT_X;
				sizePG.cy = DEF_SIZE_PUNKT_Y;
			}
			else
				sizePG = PVI.m_Size;   // Punktgröße (Eintrag aus der VisInfo)
			
		int ixpix = (int) (sizePG.cx * m_dimDots.Width() / dQuot);    // Größe des Punktsymbols in BS-Pixel (x-Richtung)
		int iypix = (int) (sizePG.cy * m_dimDots.Height() / dQuot);   //  bzw. y-Richtung
		Point PEO = BSKoordinaten (((Punkt*)_pEO) -> X(), ((Punkt*)_pEO) -> Y());
					    
			PLO = Point (PEO.X() - ixpix/2 - zug, PEO.Y() + iypix/2 + zug);
			PRU = Point (PEO.X() + ixpix/2 + zug, PEO.Y() - iypix/2 - zug);
		}

			break;
			
		case OT_KANTE:
		{
		LVISINFO LVI;
		short iLinBr;
		
			HVI.m_iVTyp = VTLinie;				// VisInfoTyp
			HVI.m_pVI = &(LVI.m_VI);        	// generischer Pointer auf VisInfo
			if (! DEX_GetIdentVisInfo (HVI))	// RückkehrCode ausgewertet
				iLinBr = DEF_WIDTH_LINIE;
			else
				iLinBr = LVI.m_Width;		// LinienBreite (Eintrag aus der Visualisierungsinformation)
			
			OC = ((Kante*)_pEO) -> GetCont ();
			PLO = BSKoordinaten (OC.XMin(), OC.YMax());
			PLO.X() -= (int) (iLinBr * m_dimDots.Width() / dQuot) + zug;  // zu bildendes Rechteck noch um Linienbreite
			PLO.Y() += (int) (iLinBr * m_dimDots.Height() / dQuot) + zug; //   bzw. Sicherheitszugabe vergrößern
			PRU = BSKoordinaten (OC.XMax(), OC.YMin());
			PRU.X() += (int) (iLinBr * m_dimDots.Width() / dQuot) + zug;
			PRU.Y() -= (int) (iLinBr * m_dimDots.Height() / dQuot)+ zug;
		}
			break;
			
		case OT_FLAECHE:
		{
		FVISINFO FVI;
		short iKontBr;
				
			HVI.m_iVTyp = VTFlaeche;			// VisInfoTyp
			HVI.m_pVI = &(FVI.m_VI);			// generischer Pointer auf VisInfo
			if (! DEX_GetIdentVisInfo (HVI))	// RückkehrCode ausgewertet
				iKontBr = DEF_WIDTH_FRAME;
			else {
			// m_Style ist ein 16-Bit-Wort mit mehreren Informationen; wenn das 16. Bit ausgeblendet
			// und der Rest durch 100 dividiert wird, liefert das ganzzahligen Divisionsergebnis
			// die Konturbreite in 0.01 mm, d.h. den Eintrag aus der Visualisierungsinformation
				iKontBr = ((FVI.m_VI.m_Style) & 0x7FFF) / 100;
			}
		
			OC = ((Masche*)_pEO) -> GetCont ();
			PLO = BSKoordinaten (OC.XMin(), OC.YMax());
			PLO.X() -= (int) (iKontBr * m_dimDots.Width() / dQuot) + zug;		// zu bildendes Rechteck noch um Linienbreite
			PLO.Y() += (int) (iKontBr * m_dimDots.Height() / dQuot) + zug;	//   bzw. Sicherheitszugabe vergrößern
			PRU = BSKoordinaten (OC.XMax(), OC.YMin());
			PRU.X() += (int) (iKontBr * m_dimDots.Width() / dQuot) + zug;
			PRU.Y() -= (int) (iKontBr * m_dimDots.Height() / dQuot)+ zug;
		}
			break;

		default:
			TX_ASSERT (false);
			break;
	}
	 
Rectangle Rec (PLO, PRU);
	 
	DEX_RePaintRectWait (Rec);
} // ObjektZeichnen


// -----------------------------------------------------------------------------------------------
// Position für Dialog-Fenster aus dem Containers bestimmen
// zuerst wird versucht, den Dialog unter das editierte Objekte zu positionieren; ist der Dialog nicht
// vollständig auf dem Bildschirm zu sehen, wird versucht, ihn oberhalb, dann rechts daneben und
// schließlich links daneben zu positionieren;
// läßt sich der Dialog nirgends außerhalb des Objektcontainers positionieren, ohne dabei über den
// Bildschirmrand hinauszuragen, wird er in die linke untere Bildschirmecke (0, 0) gestellt;
// dim ist die Dimension des Dialog-Fensters
Point GeoEditExtension :: DialogPosit (ObjContainer* pOC, Dimension dimDlgGr)
{
	TX_ASSERT (pOC);

Point PLU = BSKoordinaten (pOC->XMin(), pOC->YMin());	// linke untere Container-Ecke
CoOrd br = dimDlgGr.Width();	// Breite des Dialogs
CoOrd hoe = dimDlgGr.Height();	// Höhe des Dialogs
Dimension MWDim = MVWind() -> GetSize();	// Größe (im Point-Format) des Hauptfensters
CoOrd x, y;			// Koordinaten des linken unteren Punktes des Dialog-Fensters (Rückgabewert)
	    
	// Versuch, den Dialog unterhalb des editierten Objektes zu positionieren
	x = PLU.X();
	y = PLU.Y()-hoe;
	if (y >= 0)
	{
		if (x + br > MWDim.Width())     // Dialog ragt rechts aus dem Bildschirm heraus
			x = MWDim.Width() - br - 10;    // deshalb nach links verschieben
					// Subtraktion von 10 wegen des Rollbalkens am rechten Bildschirmrand
		return Point (x, y);
	}
	
Point PRO = BSKoordinaten (pOC->XMax(), pOC->YMax());	// rechte obere Container-Ecke

	// Versuch, den Dialog oberhalb des editierten Objektes zu positionieren
	x = PLU.X();
	y = PRO.Y();
	if (y + hoe <= MWDim.Height() - 50)     // Subtraktion von 50 wegen der beiden Kopfzeilen des Hauptfensters
	{
		if (x + br > MWDim.Width())     // Dialog ragt rechts aus dem Bildschirm heraus
			x = MWDim.Width() - br - 10;    // deshalb nach links verschieben
		return Point (x, y);
	}
	
	// Versuch, den Dialog rechts neben dem editierten Objekt zu positionieren
	x = PRO.X();
	y = PLU.Y();
	if (x + br <= MWDim.Width())
		return Point (x, y);
	
	// Versuch, den Dialog links neben dem editierten Objekt zu positionieren
	x = PLU.X() - br;
	y = PLU.Y();
	if (x >= 0)
		return Point (x, y);
	
	// Dialog ragt immer über den Bildschirmrand hinaus, wenn versucht wird, ihn außerhalb des
	// Objektcontainers zu positionieren; deshalb wird Dialog in die linke untere Bildschirmecke
	// (0, 0) gestellt
	return Point (0, 0);
} // DialogPosit


// -----------------------------------------------------------------------------------------------
// Container eines Elementarobjektes
ObjContainer GeoEditExtension :: EObjContainer (EObjekt* pEO)
{
	TX_ASSERT (pEO);

	switch (pEO -> isA())
	{
		case OT_PUNKT:
		{
		ObjContainer OC = ((Punkt*)pEO) -> GetCont ();
			
// !!!!!!!!!!!! da Fehler bei Container-Berechnung für Punkt, ist nachfolgende Modifizierung erforderlich
			OC.XMax() = OC.XMin();
			OC.YMin() = OC.YMax();
			return OC;
		}
			
		case OT_KANTE:
			return ((Kante*)_pEO) -> GetCont ();
			
		case OT_FLAECHE:
			return ((Masche*)_pEO) -> GetCont ();

		default:
			TX_ASSERT (false);
			return ObjContainer ();
	}
} // EObjContainer


// -----------------------------------------------------------------------------------------------
// Speichern-Button im Dialog gedrückt (bei echter Neueditierung)
void GeoEditExtension :: idb_Speichern (NeuEditDlg* pNED)
{
	TX_ASSERT (pNED);

CEierUhr Wait (MVWind());

long lNeuON;    // neue Objektnummer (von TRiAS bei Einspeicherung vergeben)
ulong ulIdent = pNED -> GetIdent ();// Identifikator und
SpForm sfSForm = pNED -> GetForm ();	//  Speicherform abfragen
bool bEinsp;    // Objekt wurde eingespeichert (true), sonst false
			
	if (_OTyp == OT_PUNKT)
	{
	GeoPunkt* pGP = new GeoPunkt (0, ulIdent, *((Punkt*)_pEO));
					    
		if (! pGP)
		{                                                                      
			DEX_Error (RC_geoedit, EC_NOMEMORY);
			return;
		}
		bEinsp = GeometrieAnTRIAS (pGP, sfSForm, lNeuON);
		DELETE (pGP)
	}
	else if (_OTyp == OT_KANTE)
	{
	GeoKante* pGK = new GeoKante (0, ulIdent, *((Kante*)_pEO));
					
		if (! pGK)
		{                                                                      
			DEX_Error (RC_geoedit, EC_NOMEMORY);
			return;
		}
		bEinsp = GeometrieAnTRIAS (pGK, sfSForm, lNeuON);
		DELETE (pGK);
	}
	else
	{
	GeoFlaeche* pGF = new GeoFlaeche (0, ulIdent, *((Masche*)_pEO));

		if (! pGF)
		{                                                                      
			DEX_Error (RC_geoedit, EC_NOMEMORY);
			return;
		}
		bEinsp = GeometrieAnTRIAS (pGF, sfSForm, lNeuON);
		DELETE (pGF);
	}
	
	// wenn Objekt in DB eingespeichert wurde, dann auch Objektname und Merkmale wegschreiben
	if (bEinsp)
	{
		// Objektname eintragen
		MerkmalSchreiben (TT_Objekt, lNeuON, DEX_GetObjNameMCode(ulIdent), _pcONText);	// Objektname wegschreiben
		DELETE (_pcONText);
		_pcONText = new char [maxTextLaenge+1];      // maxTextLaenge in geohilfe.hxx definiert
		if (! _pcONText)
		{                                                                      
			DEX_Error (RC_geoedit, EC_NOMEMORY);
			return;
		}
		_pcONText [0] = '\0';
			
	// UniqueIdent ergänzen
	char* pcUIText = new char [maxTextLaenge+1]; // maxTextLaenge in geokonst.hxx definiert
	
		if (pcUIText)
			wsprintf (pcUIText, ResString (ResID (IDS_UIFORMAT, pRF), 20), lNeuON);
		else
		{
			DEX_Error (RC_geoedit, EC_NOMEMORY);
			return;
		}

		// UniqueIdent wegschreiben
		MerkmalSchreiben (TT_Objekt, lNeuON, DEX_GetUniqueIdentMCode (), pcUIText);
		DELETE (pcUIText);

		DEXN_ObjectCreated (lNeuON);	// Mitteilung, daß NeuEditierung beendet
	}

	// wenn Geometrie fehlerhaft, dann keine Einspeicherung in DB;
	// da dies eigentlich nur bei Linie oder Fläche auftreten kann, werden für das nachfolgende
	// Löschen des editierten Objektes auf dem Bildschirm nur diese beiden Fälle unterschieden
	else
	{
	ResString rsText2 (ResID (IDS_LONGCLASSNAME, pRF), 100);
	ResString rsText1 (ResID (IDS_GEOFEHLERNEU, pRF), 100);

		MessageBox (hWnd(), rsText1.Addr(), rsText2.Addr(), MB_ICONEXCLAMATION | MB_OK);
	}

	// Bereich, in dem das editierte Objekt liegt, neu zeichnen; wurde es nicht abgespeichert,
	// wird es damit vom Bildschirm gelöscht
	ObjektZeichnen ();
				
	DELETE (_pEO);  // Objekt wird gelöscht (_pEO wurde noch in ObjektZeichnen() benötigt)
} // idb_Speichern


// -----------------------------------------------------------------------------------------------
// Forsetzen-Button im Dialog gedrückt
Point GeoEditExtension :: idb_Fortsetzen (void)
{
// Da zwischendurch der Löschen-Button gedrückt worden sein konnte, sind der Punkt, an dem
// fortgesetz werden soll, sowie m_AktGesLaenge neu zu berechnen

	TX_ASSERT (_pEO);

	if (! _pEO) return Point();

	if (_OTyp == OT_KANTE)
	{
	long lSPA = ((Kante*)_pEO) -> ASP ();
	
		m_LastPunkt = ((Kante*)_pEO) -> SP(lSPA-1);

	DoublePair DAP, DEP;	// Stützpunkte im ASC-Format

		m_AktGesLaenge = 0.0;		// m_AktGesLaenge neu berechnen
		for (long i = 0; i < lSPA-1; i++)
		{
			m_pCT -> UnScale (((Kante*)_pEO) -> SP(i), &DAP.X(), &DAP.Y());
			m_pCT -> UnScale (((Kante*)_pEO) -> SP(i+1), &DEP.X(), &DEP.Y());
			m_AktGesLaenge += m_pCT -> CoordTransDistance (&DAP, &DEP);
		}

		if (m_pVerlLin)	// bei Linienverlängerung noch die bisherige Länge hinzurechnen
		{
		KoOrd* plXK; KoOrd* plYK;

			m_pIOG -> GetCnt (&lSPA);
			m_pIOG -> GetX ((void**)&plXK);
			m_pIOG -> GetY ((void**)&plYK);

			for (long i = 0; i < lSPA-1; i++)
			{
				m_pCT -> UnScale (plXK[i], plYK[i], &DAP.X(), &DAP.Y());
				m_pCT -> UnScale (plXK[i+1], plYK[i+1], &DEP.X(), &DEP.Y());
				m_AktGesLaenge += m_pCT -> CoordTransDistance (&DAP, &DEP);
			}
		}
	}

	else    // Fläche
	{
	short iKAnz = ((Masche*)_pEO) -> KantenAnz ();		// Anzahl der bis jetzt editierten Konturen 
	long lSPA = ((Masche*)_pEO) -> KA(iKAnz-1).ASP ();	// Anzahl der Stützpunkte der letzten Kontur
					
		m_LastPunkt = ((Masche*)_pEO) -> KA(iKAnz-1).SP(lSPA-1);
	}

Point Pt = BSKoordinaten (m_LastPunkt.X(), m_LastPunkt.Y());

	if (Pt.X() > 0) Pt.X()--;	// wegen Fehler bei Hartmut notwendig
	if (Pt.Y() > 0) Pt.Y()--;	// eine Korrektur bei ihm hätte zu große Folgen an anderen Stellen

	return Pt;
} // idb_Fortsetzen


// -----------------------------------------------------------------------------------------------
// BS-Punkt Pt in Datenbank-Koordinaten umrechnen und dabei evtl. auf einen schon vorhandenen
// Stützpunkt ziehen; dazu
// - darf die SHIFT-Taste nicht gedrückt sein,
// - müssen mindestens iAnz Objekte selektiert sein, deren Stützpunkte damit markiert worden sind und
// - muß Pt innerhalb eines dieser Markierungen liegen
Punkt GeoEditExtension :: NeuerPunktMitGrab (Point& Pt, short iAnz)
{
Punkt NeuPkt;

// Test, ob Pt auf einen schon vorhandenen Stützpunkt gezogen werden soll
bool bShift = GetKeyState (VK_SHIFT) < 0;	// SHIFT-Taste nicht/gedrückt (false/true)

	if (bShift == false &&				// SHIFT-Taste nicht gedrückt
		(short)m_pGB->Count() >= iAnz)	// mindestens iAnz Objekte selektiert (markiert)
	{
		// Wenn Pt in einem Markierungsquadrat liegt, d.h. wenn Cursor die FANGEN-Form hat,
		// dann Pt auf diesen Stützpunkt ziehen
		if (m_CurForm == FANGEN)
		{
			NeuPkt = m_GrabPkt;
			LMouseDrag (Pt);	// Strecke mit ungegrabtem Pt löschen
			Pt = BSKoordinaten (m_GrabPkt.X(), m_GrabPkt.Y());
			LMouseDrag (Pt);	// Strecke mit gegrabtem Pt neu zeichnen
		}
		else	// kein Grab, da nicht in einem Markierungsquadrat
			NeuPkt = DBKoordinaten (Pt);	// aktuell editierter Punkt
	}
	else	// kein Grab, da SHIFT gedrückt oder kein Objekt markiert
		NeuPkt = DBKoordinaten (Pt);		// aktuell editierter Punkt

	return NeuPkt;
} // NeuerPunktMitGrab


// -----------------------------------------------------------------------------------------------
// Bereich des Objektes pIOG neu zeichnen
void GeoEditExtension :: BereichZeichnen (IObjektGeometrie* pIOG)
{
	TX_ASSERT (pIOG);

	if (! pIOG) return;

KoOrd lXmin, lXmax, lYmin, lYmax;	// Koordinaten des Containers von pIOG

	pIOG -> GetCont (&lXmin, &lXmax, &lYmin, &lYmax);

Point PLO = BSKoordinaten (lXmin, lYmax);
Point PRU = BSKoordinaten (lXmax, lYmin);

	PLO.X() -= iZeiZug;		// iZeiZug ist in geokonst.hxx definiert
	PLO.Y() += iZeiZug;
	PRU.X() += iZeiZug;
	PRU.Y() -= iZeiZug;

Rectangle Rec (PLO, PRU);
	 
	DEX_RePaintRectWait (Rec);
	MVWind() -> Update();		// sofort zeichnen
} // BereichZeichnen


// -----------------------------------------------------------------------------------------------
// bei Neueditierung aktuelle Länge und evtl. Fläche in Statuszeile anzeigen
void GeoEditExtension :: AktuelleWerteAnzeigen (Point Pt)
{
	if (! _pEO ||			// der 1. Punkt des zu editierenden Objektes ist noch nicht gesetzt
		_bIns ||			// Beginn einer neuen Insel wurde soeben angezeigt
		_OTyp == OT_PUNKT)	// bei Punkt keine Statusanzeige
		return;			// keine aktuellen Werte anzeigen

char pcKonvBuff [40] = { '\0' };	// Konvertierungspuffer
char pcOutBuff [200] = { '\0' };	// Ausgabepuffer
DoublePair DAP;			// Anfangspunkt der aktuell editierten Strecke (im ASC-Format)
DoublePair DEP = BSInASCKoord (Pt, m_pCT);	// aktueller Punkt an der Mausspitze

	m_pCT -> UnScale (m_LastPunkt, &DAP.X(), &DAP.Y());

	// Länge der aktuell editierten Strecke ermitteln
	m_AktLaenge = m_pCT -> CoordTransDistance (&DAP, &DEP);

	wsprintf (pcOutBuff, ResString (ResID (IDS_AKTSTRECKE, pRF), 40));
	DtoA (pcKonvBuff, "%1.0f", m_AktLaenge);
	strcat (pcOutBuff, pcKonvBuff);
	strcat (pcOutBuff, " m;  ");		// "Meter" anfügen

	if (_OTyp == OT_KANTE)
	{
	ResString Text (ResID (IDS_GESAMTLAENGE, pRF), 40);

		strcat (pcOutBuff, Text.Addr());
		DtoA (pcKonvBuff, "%1.0f", m_AktGesLaenge + m_AktLaenge);
		strcat (pcOutBuff, pcKonvBuff);
		strcat (pcOutBuff, " m");		// "Meter" anfügen
	}
	else		// Neueditierung einer Fläche
	{
	ResString Text (ResID (IDS_FLAECHENINHALT, pRF), 40);

		strcat (pcOutBuff, Text.Addr());

		(DreieckInhalt (Pt));

	double dZwFlInh;		// aktueller Zwischenstand des Flächeninhalts

		if (((Masche*)_pEO) -> KantenAnz() == 1)	// Neueditierung der Außenkontur
			dZwFlInh = fabs(m_AktGesFlaeche + m_AktDreieck);
		else										// Neueditierung einer Innenkontur
			dZwFlInh = m_AktGesFlaeche - fabs(m_AktInsel + m_AktDreieck);

		if (dZwFlInh > 1000000.)
		{
			DtoA (pcKonvBuff, "%5.3f", dZwFlInh/1000000.);
			strcat (pcOutBuff, pcKonvBuff);					// Ausgabe in km²
			strcat (pcOutBuff, " km²");
		}
		else
		{
			if (dZwFlInh > 10000.)
			{
				DtoA (pcKonvBuff, "%5.3f", dZwFlInh/10000.);
				strcat (pcOutBuff, pcKonvBuff);				// Ausgabe in ha
				strcat (pcOutBuff, " ha");
			}
			else
			{
				DtoA (pcKonvBuff, "%1.0f", dZwFlInh);
				strcat (pcOutBuff, pcKonvBuff);				// Ausgabe in m²
				strcat (pcOutBuff, " m²");
			}
		}
	}

	// __hWndM ist eine globale Variable, die das HauptfensterHandle enthält
	SendMessage (__hWndM, 0x362, 0, (LPARAM)pcOutBuff);
} // AktuelleWerteAnzeigen


// -----------------------------------------------------------------------------------------------
// vorzeichenbehafteten Flächeninhalt der neuesten hinzugekommenen Dreiecksfläche in m², wenn die
// zu editerende Fläche zum aktuellen Zeitpunkt zugezogen würde
bool GeoEditExtension :: DreieckInhalt (Point Pt)
{
	m_AktDreieck = 0.0;		// für return false;

	TX_ASSERT (_pEO);

	if (!_pEO || _OTyp != OT_FLAECHE)
		return false;		// kein Flächenobjekt

short iKAnz = ((Masche*)_pEO) -> KantenAnz();	// aktuelle Anzahl der Inseln

	if (((Masche*)_pEO) -> KA(iKAnz-1).ASP() < 2)
		return false;		// aktuelle Kontur hat bisher zu wenig Stützpunkte

Punkt AktPkt = DBKoordinaten (Pt);	// Punkt der aktuellen Mausspitze
Punkt AP = ((Masche*)_pEO) -> KA(iKAnz-1).SP(0);	// Anfangspunkt der letzten Insel
Masche* pFl = new Masche (&m_LastPunkt.X(), &m_LastPunkt.Y(), 1);

	if (! pFl)
	{
		DEX_Error (RC_geoedit, EC_NOMEMORY);
		return false;
	}

	pFl -> AddPunkt (&AktPkt.X(), &AktPkt.Y(), 1, -1, -1);
	pFl -> AddPunkt (&AP.X(), &AP.Y(), 1, -1, -1);
	pFl -> AddPunkt (&m_LastPunkt.X(), &m_LastPunkt.Y(), 1, -1, -1);
	
	m_AktDreieck = pFl -> FlInhalt (pFl->KA(0), m_pCT);	// vorzeichenbehafteten Flächeninhalt

	DELETE (pFl);

	return true;

} // DreieckInhalt


// -----------------------------------------------------------------------------------------------
// Vor Setzen von RegisterNotification () testen, ob diese Anforderung evtl. schon gestellt wurde
void GeoEditExtension :: RegisterNotificationM (UINT wMsg, bool isLocal, bool& bRN)
{
	if (! bRN)
	{
		RegisterNotification (wMsg, isLocal);
		bRN = true;
	}
	return;
} // RegisterNotificationM


// -----------------------------------------------------------------------------------------------
// Vor Setzen von UnRegisterNotification () testen, ob diese Anforderung evtl. schon gestellt wurde
void GeoEditExtension :: UnRegisterNotificationM (UINT wMsg, bool isLocal, bool& bURN)
{
	if (bURN)
	{
		UnRegisterNotification (wMsg, isLocal);
		bURN = false;
	}
	return;
} // UnRegisterNotificationM


// -----------------------------------------------------------------------------------------------
//	DebugSection-Eintrag aus win.ini lesen
bool GeoEditExtension :: _GetDebugOutputFlag (void)
{
ResString Section (ResID (IDS_DEBUGSECTION, pRF), 30);
ResString Entry (ResID (IDS_DEBUGENTRY, pRF), 30);	
char Buffer [5] = "";
	
	return  GetProfileString (Section.Addr (), Entry.Addr (), "0", Buffer, sizeof (Buffer)) 
			&& (atoi (Buffer) > 0) ? true : false;
} // _GetDebugOutputFlag
