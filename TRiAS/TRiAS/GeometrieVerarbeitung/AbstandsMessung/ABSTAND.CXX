// Funktionen für Erweiterungs-DLL "Abstandsmessung"
// File: ABSTAND.CXX
// W. Mörtl


#include "abstandp.hxx"


// Voraussetzungen für Arbeit mit Toolbars
#include <initguid.h>	// für Linken von toolguid.h und abstguid.h (s.u.) erforderlich
#include <toolguid.h>	// CLSID_TRiASUIOwner in uiowner.h
#include "uiowner.h"	// CUIOwner

DefineSmartInterface(TRiASBarContainer);	// WTRiASBarContainer
DefineSmartInterface(TRiASBar);				// WTRiASBar

#define BMPSIZE			1		// Anzahl der Buttons in der Bitmap
#define NUMBUTTONS		1		// Anzahl der zu installierenden Buttons
#define ID_ALTLINEAL	22053	// ID des alten "Lineal"-Buttons


#include <resstrg.h>    // IDS_UIFORMAT

#include <hdrentrx.hxx>	// HeaderEntryX

#include "AbstandR.h"	// IDS_LONGCLASSNAME

#include "GeomDLL.hxx"	// InitGeometrie
#include "zeichnen.hxx"	// PointSymbolSize()
#include "datbank.hxx"	// WriteFeatureText()
#include "strecke.hxx"	// LotPunkt()

#include "abstguid.h"	// CLSID_Abstand
#include "version.h"	// ABSTAND_MAJORVERSION, ...

#include "kilometr.hxx"	// KilometrDlg
#include "abstand.hxx"	// AbstandExtension



#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern UINT __DexNotify;
extern UINT __DexCmd;



///////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_OBJECT_MAP(ObjectMap)		// Makro
	OBJECT_ENTRY(CLSID_Abstand, AbstandExtension)
END_OBJECT_MAP()

_ATL_OBJMAP_ENTRY* GetObjectMap (void)
{
	return ObjectMap;
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung sich selbst in der
// RegDB registrieren soll (empfohlen!!).
// Der ProgID (hier 'TRiAS.Abstand.1') ist eine Zeichenkette, die die Erweiterung in der RegDB
// repräsentiert. Das Format sollte beibehalten werden. Die '... .1' steht für die
// VersionsNummer.
// Der KlassenName (hier die Stringresource hinter IDS_LONGCLASSNAME) ist eine
// normal-lesbare Zeichenkette, die lokalisiert wird (deshalb in der Ressource) und die
// Bezeichnung der Erweiterung definiert.
BOOL UpdateRegistry (BOOL bRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (bRegister)	// RegDB initialisieren
		return ExtOleRegisterExtensionClass (g_hInstance, CLSID_Abstand,
							TEXT("TRiAS.Abstand.1"), IDS_LONGCLASSNAME, ABSTAND_MAJORVERSION,
							ABSTAND_MINORVERSION, EFUnLoadable|EFVisible);
	else			// RegDB säubern
		return ExtOleUnregisterClass (CLSID_Abstand, TEXT("TRiAS.Abstand.1"));

	return true;	// alles ok
}



///////////////////////////////////////////////////////////////////////////////////////////////
ResourceFile* pRF = NULL;
bool Mess;		// Flag für Ausgabe im DebugWindow (wird in InitExtension gesetzt)



///////////////////////////////////////////////////////////////////////////////////////////////
// Zählen von Objekten in den geöffneten Recherchefenstern und Rückgabe von
//   iAnz[0]  Anzahl der selektierten (markierten) Objekte außer dem aktivierten
//            (blinkenden) Objekt
//   iAnz[1]  Anzahl der selektierten Flächen (evtl. einschl. einer aktiv. Fläche)
//   iAnz[2]  Anzahl der selektierten Kanten (evtl. einschl. einer aktiv. Kante)
BOOL _ABSTAND_EXPORT FAR PASCAL AktObjekteZaehlen (long lONr, BOOL, void* iAnz)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

	if (((AbstandExtension*) g_pTE)->ONrAO() != lONr)
		((long*)iAnz)[0]++;
	if (DEX_GetObjectType(lONr) == OT_FLAECHE)
		((long*)iAnz)[1]++;
	if (DEX_GetObjectType(lONr) == OT_KANTE)
		((long*)iAnz)[2]++;

	return true;
}



///////////////////////////////////////////////////////////////////////////////////////////////
int ErrHandler (int iWC, int iRoutine, ...);



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
// Die Erweiterung wird von der Klasse 'CTriasExtension' abgeleitet, welche wiederum als
// einzigen Parameter den ResID des im Hauptfenster einzuhängenden Menüs übergeben bekommt.
AbstandExtension :: AbstandExtension (void)
				  : CTriasExtension (0, IDM_KILOMETRMENU)
{
// Member initialisieren
char cSichtName[MAXVIEWNAMESIZE+1] = { '\0' };     // Name der Sicht (NICHT mit "string")

	if (DEX_TestActiveProject() &&    // ein Projekt ist schon geöffnet
		0 != DEX_GetActiveSight (cSichtName))
		m_bSight = true;	// eine Sicht ist schon ausgewählt
	else
		m_bSight = false;	// noch keine Sicht ausgewählt

	_iAbstTool = -1;        // neues Werkzeug ist noch nicht installiert
	_isActive = false;      // Erweiterung ist noch nicht aktiviert
	_bProj = false;         // kein Projekt geöffnet

	_LeftButtonSem = false; // Semaphore für Maustasten (linke Maustaste wurde noch nicht
							// gedrückt)
	_RightButtonSem = false;// rechte Maustaste wurde noch nicht gedrückt
	_LeftButtonUp = false;	// linke Maustaste wurde noch nicht losgelassen

	m_pAWDlg = NULL;		// Dialogbox für die Ergebnisse der Abstandsmessung
	_bWinOn = false;        // Dialogbox m_pAWDlg noch nicht angelegt
	_bWinAnz = false;       // Dialogbox m_pAWDlg kann noch nicht angezeigt werden
//	m_bMenIt = false;		// MenuItem noch nicht installiert

	m_pCT = NULL;			// Klasse für KoordinatenTransformation
	m_pIL = NULL;
	_AP = DoublePair();		// Anfangs- bzw.
	_EP = DoublePair();		//  Endpunkt für Abstandsmessung (im ASC-Format)
	_DRO = NULL;

	m_NrKPunkte = NULL;		// Baum für Objektnummern der Kilometrierungspunkte
	m_NrTeile = NULL;		// Baum für Objektnummern der Teilkanten
	m_MenPktLoe = false;	// Menüpunkt für Löschen der Kilometrierungspunkte noch nicht
							// aktiviert
	m_MenTeilLoe = false;	// Menüpunkt für Löschen der Teilkanten noch nicht aktiviert
	m_iOT = OT_UNKNOWN;		// Objekttyp des zu kilometrierenden Objektes
	m_bMenuDelP = false;
	m_bMenuDelT = false;

	m_pIUIOwner = NULL;
}


// --------------------------------------------------------------------------------------------
// Destruktor
AbstandExtension :: ~AbstandExtension (void)
{
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Im folgenden werden alle durch diese Erweiterung überladenen virtuellen Funktionen definiert

// Folgende Funktion wird einmalig nach der erfolgreichen Installation der Erweiterung durch
// TRiAS gerufen. Hier erfolgen alle notwendigen Initialisierungen.
STDMETHODIMP_(BOOL) AbstandExtension :: InitExtension (short iMode)
{
	if (!CTriasExtension :: InitExtension (iMode))
		return false;

	InitGeometrie (hWnd(), __DexNotify, __DexCmd);
	pRF = &RF();
	
	_ASSERTE (NULL != pRF);

ErrCode rcDummy;

	DEX_ErrInstall (rcDummy, WC_MESSAGE_ABST, ErrHandler, &m_oldEH);
	
	m_iMode = iMode;
	if (iMode != LoadState())	// Erweiterung war schon teilweise geladen gewesen
		return true;			// jetzt ist sie voll zu sehen

// TRiAS-Messages anfordern (nur 1 Parameter)
	RegisterNotification (DEX_PROJECTOPEN);
	RegisterNotification (DEX_PROJECTCLOSE);
	RegisterNotification (DEX_SETACTIVETOOL);
	RegisterNotification (DEX_TXICHANGED);		// Veränderungen in der Identifikator-Datenbank
	RegisterNotification (DEX_OBJECTTODELETE);
	RegisterNotification (DEX_SIGHTSELECTED);	// eine Sicht wurde ausgewählt
	RegisterNotification (DEX_HEADERREREAD);	// ein DB-Header-Eintrag wurde verändert
	RegisterNotification (DEX_N_SAVECOMPLETED);

	InitAndOPEN (iMode);
// neues Werkzeug installieren
	if (_iAbstTool == -1)
	{
		InstallToolbarButton();
		_iAbstTool = ID_TOOL_ABSTAND;
	}

// georein.ext automatisch nachladen
ResString GeoRein (ResID (IDS_GEOREIN, pRF), 20);
	
	DEX_ExternalLoadExtension (GeoRein.Addr());

	Mess = _GetDebugOutputFlag();	// Ausgabe im DebugWindow (true), sonst false	

	return true;

} // InitExtension


// --------------------------------------------------------------------------------------------
// alle Interface-Geschichten müssen in UnLoadExtension aufgelöst werden
STDMETHODIMP_(BOOL) AbstandExtension :: UnLoadExtension (void)
{
// Erweiterung passivieren
	if (_isActive)
	{
		// Windows-Messages wieder abmelden (2 Parameter)
		UnRegisterNotification (WM_LBUTTONDOWN, false);
		UnRegisterNotification (WM_RBUTTONDOWN, false);
		_isActive = false;
	}

// TRiAS-Messages wieder abmelden
	UnRegisterNotification (DEX_N_SAVECOMPLETED);		// ein DB-Header-Eintrag wurde verändert
	UnRegisterNotification (DEX_HEADERREREAD);		// ein DB-Header-Eintrag wurde verändert
	UnRegisterNotification (DEX_SIGHTSELECTED);		// eine Sicht wurde ausgewählt
	UnRegisterNotification (DEX_OBJECTTODELETE);
	UnRegisterNotification (DEX_TXICHANGED);
	UnRegisterNotification (DEX_SETACTIVETOOL);
	UnRegisterNotification (DEX_PROJECTCLOSE);
	UnRegisterNotification (DEX_PROJECTOPEN);

ErrCode rcDummy;

	DEX_ErrInstall (rcDummy, WC_MESSAGE_ABST, m_oldEH, NULL);

// restliche Abmeldungen
	UnLoadAndCLOSE();

// Werkzeug wieder entfernen
	if (_iAbstTool != -1)
	{
		RemoveToolbarButton();
		if (m_pIUIOwner) m_pIUIOwner->Release();
		_iAbstTool = -1;
	}

	return CTriasExtension :: UnLoadExtension();

} // UnLoadExtension


// --------------------------------------------------------------------------------------------
// Diese Funktion dient der Behandlung der MenüKommandos der Erweiterung
STDMETHODIMP_(BOOL) AbstandExtension :: MenuCommand (UINT MenuItemID, HWND hWnd)
{
	_hWnd = hWnd;

	switch (MenuItemID)
	{
		case IDM_ABSTAND:       // Zeile im Menü "Anzeige"
		{
			if (_bWinAnz)		// DialogBox wurde bis eben angezeigt
			{
				m_pAWDlg->Hide();			// DialogBox verdecken
				DEX_ChangeActiveTool (0);	// "Pfeil"-ToolButton aktivieren
				_bWinAnz = false;
			}
			else				// DialogBox war bis eben verdeckt
			{
				m_pAWDlg->Show();					// DialogBox wieder anzeigen
				DEX_ChangeActiveTool (_iAbstTool);	// "Abstand"-ToolButton wieder aktivieren
				_bWinAnz = true;
			}
			m_pAWDlg->SetSichtbarkeit (_bWinAnz);

			return true;
		}


		case IDM_KILOMETR:		// Menüpunkt: Kilometrierung vornehmen
		{
// nachfolgende Message gilt nur vorübergehend !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			if (m_iOT != OT_KANTE)
			{
			ResString Titel (ResID (IDS_KILOMETRIERUNG, pRF), 50);
			ResString Text (ResID (IDS_NOKANTE, pRF), 80);
			
				MessageBox (hWnd, Text.Addr(), Titel.Addr(), MB_ICONEXCLAMATION | MB_OK);
				return false;
			}

		WObjektGeometrie wObj;	// (Interface auf) Objektgeometrie des zu kilometrierenden Objektes

			if (FAILED(CreateInterfaceOG (wObj.ppi(), m_lONrAO)))
				return false;

		// als Anfangspunkt für die Kilometrierung den 1. Stützpunkt, als Endpunkt den letzten
		// Stützpunkt von wObj vorgeben
		KoOrd* plXK; KoOrd* plYK;
		long lCnt;

			wObj->GetX ((void**)&plXK);
			wObj->GetY ((void**)&plYK);
			wObj->GetCnt (&lCnt);

		KoOrd lXA = plXK[0];
		KoOrd lYA = plYK[0];
		KoOrd lXE = plXK[lCnt-1];
		KoOrd lYE = plYK[lCnt-1];
		pWindow pW;

			// ORWind() liefert pWindow-Zeiger auf ObjektRechercheFenster; damit können alle
			// weiteren Fenster auf das ObjektRechercheFenster bezogen werden
			if (hWnd && ORWind (hWnd))
				pW = ORWind (hWnd);

			else
				pW = MWind();	// MWind() liefert pWindow-Zeiger auf HauptFenster

		KilometrDlg KMDlg (pW, ResID (IDD_KILOMETR, pRF), *m_pIL, lXA, lYA, lXE, lYE);

			KMDlg.Show();  // DialogBox anzeigen

			if (KMDlg.Result())		// Click auf OK-Button
			{
			CEierUhr Wait (MVWind());

				if (m_NrKPunkte) m_NrKPunkte->EveryDelete();
				if (m_NrTeile) m_NrTeile->EveryDelete();
				m_MenPktLoe = false;
				m_MenTeilLoe = false;

			double dDistanz = KMDlg.GetDistanz();	// Schrittweite für Kilometrierung
			double dTextStartWert = KMDlg.GetTextStartWert();	// Startwert für Text
			bool bTeil = KMDlg.GetTeilabschnitt();	// Teilabschnitte erzeugen ja/nein

				m_bText = KMDlg.GetKilometrText();	// Text anhängen ja/nein
				m_ulKMIdent = KMDlg.GetIdent();		// Identifikator für Kilometrierungspunkte
				lXA = KMDlg.GetXA();				// x-Koordinate bzw.
				lYA = KMDlg.GetYA();				//  y-Koordinate des Anfangspunktes
				lXE = KMDlg.GetXE();				// x-Koordinate bzw.
				lYE = KMDlg.GetYE();				//  y-Koordinate des Endpunktes

				if (OT_KANTE == m_iOT)
					LinienKilometrierung (wObj, lXA, lYA, lXE, lYE, dDistanz, dTextStartWert,
										  bTeil);
				else
					FlaechenKilometrierung (wObj, lXA, lYA, lXE, lYE, dDistanz, dTextStartWert,
											bTeil);

				wObj->GetCont (&m_KC.XMin(), &m_KC.XMax(), &m_KC.YMin(), &m_KC.YMax());

				BereichZeichnen();	// Kilometrierungs-Bereich neu zeichnen
			}

			return true;     // bei Abbruch-Button ist KMDlg.Result() == 0: keine Reaktion
		}


		case IDM_KPUNKTLOESCHEN:	// Menüpunkt: Kilometrierungspunkte löschen
		{
		CEierUhr Wait (MVWind());

			m_MenPktLoe = false;

		CTable tab (*m_NrKPunkte);

			m_bMenuDelP = true;		// Kilometrierungspunkte werden über Menüpunkt
									//  "Kilometrierungspunkte löschen" gelöscht

			for (tab.First(); tab.Valid(); tab.Next())
			{
			ObjNrKnotenLock kl (tab);

				if (kl)
					DEX_DeleteObjectEx (kl->GetONr());
				else
				{
	    			DEX_Error (RC_abstand, EC_SYSERROR);
					continue;
				}
			}

			m_bMenuDelP = false;

			BereichZeichnen();	// Kilometrierungs-Bereich neu zeichnen

			if (m_NrKPunkte) m_NrKPunkte->EveryDelete();
			return true;
		}


		case IDM_TEILLOESCHEN:		// Menüpunkt: Teilkanten löschen
		{
		CEierUhr Wait (MVWind());

			m_MenTeilLoe = false;

		CTable tab (*m_NrTeile);

			m_bMenuDelT = true;		// Teilkanten werden über Menüpunkt "Teilabschnitte löschen" gelöscht

			for (tab.First(); tab.Valid(); tab.Next())
			{
			ObjNrKnotenLock kl (tab);

				if (kl)
					DEX_DeleteObjectEx (kl->GetONr());
				else
				{
	    			DEX_Error (RC_abstand, EC_SYSERROR);
					continue;
				}
			}

			m_bMenuDelT = false;

			BereichZeichnen();	// Kilometrierungs-Bereich neu zeichnen

			if (m_NrTeile) m_NrTeile->EveryDelete();
			return true;
		}


		default:
			_ASSERTE (false);
			break;
	}

	DEX_Error (RC_MenuCommandAbstand, EC_ERRMENUITEMID);   // Fehlermeldung
	return false;

} // MenuCommand
 
 

// --------------------------------------------------------------------------------------------
// Diese Funktion initialisiert das Menü
STDMETHODIMP_(BOOL) AbstandExtension :: MenuInit (HMENU hMenu, LPARAM, HWND hWnd)
{
	// DialogBox kann durch Betätigung des Systemmenüfeldes verdeckt werden
	if (m_pAWDlg)
		_bWinAnz = m_pAWDlg->GetSichtbarkeit();

	if (_bWinAnz)   // DialogBox wird angezeigt, deshalb Häkchen setzen
		CheckMenuItem (hMenu, IDM_ABSTAND+MenuOffset(), MF_BYCOMMAND|MF_CHECKED);
	else			// DialogBox ist verdeckt, deshalb Häkchen löschen
		CheckMenuItem (hMenu, IDM_ABSTAND+MenuOffset(), MF_BYCOMMAND|MF_UNCHECKED);

	if (m_MenPktLoe) // Menüpunkt für Löschen der Kilometrierungspunkte
		EnableMenuItem (hMenu, IDM_KPUNKTLOESCHEN+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
	else
		EnableMenuItem (hMenu, IDM_KPUNKTLOESCHEN+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

	if (m_MenTeilLoe) // Menüpunkt für Löschen der Teilabschnitte
		EnableMenuItem (hMenu, IDM_TEILLOESCHEN+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
	else
		EnableMenuItem (hMenu, IDM_TEILLOESCHEN+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

	m_lONrAO = DEX_GetActiveObject (hWnd);	// Objektnummer und

	if (0 != m_lONrAO && -1 != m_lONrAO)
		m_iOT = DEX_GetObjectType (m_lONrAO);	//  Typ des aktivierten (blinkenden) Objektes

	if (m_iOT == OT_KANTE || m_iOT == OT_FLAECHE) // Menüpunkt für Kilometrierung
		EnableMenuItem (hMenu, IDM_KILOMETR+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
	else
		EnableMenuItem (hMenu, IDM_KILOMETR+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

	return true;
} // MenuInit


// --------------------------------------------------------------------------------------------
// Diese Funktion wird bei Systemereignissen diverser Natur gerufen, z.B. bei
// Anklicken sowohl der neuen als auch der anderen Iconen
STDMETHODIMP_(LRESULT) AbstandExtension :: Notification (WPARAM iMsg, LPARAM lPar)
{
	switch (iMsg)
	{
		case DEX_SETACTIVETOOL:
		{
			if ((int)lPar == _iAbstTool)
			{
			// Erweiterung aktivieren (Windows-Messages anmelden)
				RegisterNotification (WM_LBUTTONDOWN, false);
				RegisterNotification (WM_RBUTTONDOWN, false);
				_isActive = true;

				if (!_bWinOn)   // Dialogbox noch nicht angelegt
				{
				int iOT = OT_KANTE;
				
					m_piAnz[0] = 1;	// Anzahl der selektierten (markierten) Objekte außer dem
									// aktivierten (blinkenden) Objekt
					m_piAnz[1] = 0;	// Anzahl der selektierten Flächen (evtl. einschl. einer
									// aktivierten Fläche)
					m_piAnz[2] = 2;	// Anzahl der selektierten Kanten (evtl. einschl. einer
									// aktivierten Kante)

					m_pAWDlg = new AbstandsWerte (MVWind(), ResID (IDD_ABSTAND, pRF), iOT,
												  m_piAnz, m_cGenau);
					if (! m_pAWDlg)
					{
						DEX_Error (RC_abstand, EC_NOMEMORY);
						return false;
					}

					_bWinOn = true;  // DialogBox ist angelegt
					_bWinAnz = true; //  und wird angezeigt
					m_pAWDlg->SetSichtbarkeit (_bWinAnz);

					// zusätzliche Menüpunkte im Hauptmenü (false) "Extras" anhängen
					InstallMenuItem (ResID (IDM_ABSTAND, pRF), IDS_BOXANZEIGEN, false, EXTRA_MENU_POS);
				}
				else	// Dialogbox schon angelegt aber versteckt
				{
					m_pAWDlg->Show();		// DialogBox wieder anzeigen
					_bWinAnz = true;
				}
				m_pAWDlg->SetSichtbarkeit (_bWinAnz);

			}

			// bis eben war Abstandserweiterung aktiv, jetzt wurde ein anderer ToolButton gedrückt
			else if (_isActive)
			{
				// Erweiterung passivieren
				UnRegisterNotification (WM_LBUTTONDOWN, false);
				UnRegisterNotification (WM_RBUTTONDOWN, false);
				_isActive = false;

				if (_bWinOn)   // Dialogbox ist schon angelegt gewesen
				{
					m_pAWDlg->Hide();		// DialogBox verdecken
					_bWinAnz = false;
					m_pAWDlg->SetSichtbarkeit (_bWinAnz);
				}
			}
		}
			break;

		case DEX_PROJECTOPEN:		// Projekt wird geöffnet
			InitAndOPEN (m_iMode);

			break;

		case DEX_PROJECTCLOSE:		// Projekt wird geschlossen
			_bWinAnz = false;
			_bProj = false;
			UnLoadAndCLOSE();
			break;


		case DEX_TXICHANGED:		// IdentListe aktualisieren
			if (m_pIL)
			{
				if (lPar == 0)
				{
				CEierUhr Wait (MVWind());
				
					// alles neu einlesen
					DELETE_OBJ (m_pIL);
					m_pIL = new IdentList();
					if (! m_pIL)
					{                                                                      
						DEX_Error (RC_abstand, EC_NOMEMORY);
						return false;
					}
				}
				else
					m_pIL->UpdateEntry (lPar);
			}
			break;


		case DEX_OBJECTTODELETE:	// Objekt mit Objektnummer lPar wird gleich gelöscht
			// diese Message interessiert nur unter bestimmten Voraussetzungen
			if (m_bMenuDelP == false &&		// die zuletzt erzeugten Kilometrierungspunkte werden
											//  nicht über den Menüpunkt "Kilometrierungspunkte löschen"
											//  gelöscht
				m_NrKPunkte != NULL &&
				m_NrKPunkte->Count() > 0 &&	// es wurden überhaupt Kilometrierungspunkte erzeugt
				DEX_GetObjectType(lPar) == OT_PUNKT)
			{
				m_NrKPunkte->DeleteK (lPar);
				if (m_NrKPunkte->Count() == 0)
					m_MenPktLoe = false;	// Lösch-Menüpunkt inaktivieren
			}

			if (m_bMenuDelT == false &&		// die zuletzt erzeugten Teilkanten werden nicht über den
											//  Menüpunkt "Teilabschnitte löschen" gelöscht
				m_NrTeile != NULL &&
				m_NrTeile->Count() > 0 &&		// es wurden überhaupt Teilkanten erzeugt
				DEX_GetObjectType(lPar) == OT_KANTE)
			{
				m_NrTeile->DeleteK (lPar);
				if (m_NrTeile->Count() == 0)
					m_MenTeilLoe = false;	// Lösch-Menüpunkt inaktivieren
			}
			break;


		case DEX_SIGHTSELECTED:
			if (lPar != 0)
				m_bSight = true;
			else
				m_bSight = false;
			break;


		case DEX_HEADERREREAD:
			ReadCoordPrecision();
			break;

		case DEX_N_SAVECOMPLETED:
			DELETE_OBJ (m_pCT);
			m_pCT = new CoordTransX();
			if (! m_pCT) 
				DEX_Error (RC_abstand, EC_NOMEMORY);
			break;

		default:	// Notifikationen der Basisklasse
			break;
	}

	return CTriasExtension :: Notification (iMsg, lPar);

} // Notification


// --------------------------------------------------------------------------------------------
STDMETHODIMP_(LRESULT) AbstandExtension :: WindowsNotification (UINT wMsg, WPARAM, LPARAM lPar)
{
// EPunkt in Bildschirmkoordinaten, auf den Maus zeigt
//Point Pt (LOWORD(lPar), HIWORD(lPar));
CoOrd x = LOWORD (lPar);	// beide Werte sind (04.08.98)
CoOrd y = HIWORD (lPar);	// vorzeichenbehaftet

	if (x >= 0x8000)
		x -= 0x10000;
	if (y >= 0x8000)
		y -= 0x10000;

Point Pt (x, y);
Rectangle CRc = MVWind()->CanvasRect();
int iBH = CRc.Top() - CRc.Bottom();

	Pt.Y() = iBH - Pt.Y();	// y-Koordinate drehen

	switch (wMsg)
	{
	case WM_LBUTTONDOWN:        // linke MausTaste gedrückt
		if (DEX_GetActiveTool() == _iAbstTool)
		{

			MVWind()->MouseTrap (TRUE);		// Maus einfangen
			_AP = BSInASCKoord (Pt, m_pCT);	// Anfangspunkt für Abstandsmessung
			_LeftButtonSem = true;			// linke Maustaste wurde gedrückt

			LMouseButtonDn (Pt);

			RegisterNotification (WM_LBUTTONUP, false);
			RegisterNotification (WM_MOUSEMOVE, false);
			return true;
		}
		break;
		
	case WM_LBUTTONUP:          // linke MausTaste losgelasssen
		if (_LeftButtonSem)
		{
			_EP = BSInASCKoord (Pt, m_pCT);	// Endpunkt für Abstandsmessung
			AbstandAnzeigen();

			LMouseButtonUp();

			UnRegisterNotification (WM_MOUSEMOVE, false);
			UnRegisterNotification (WM_LBUTTONUP, false);

			_LeftButtonSem = false; // Down kam von hier (linke Maustaste wurde losgelassen)
			_LeftButtonUp = true;	// linke Maustaste wurde gedrückt und wieder losgelassen
			MVWind()->MouseTrap (FALSE);

			return true;
		}
		break;
		
	case WM_RBUTTONDOWN:        // rechte MausTaste gedrückt
		if (DEX_GetActiveTool() == _iAbstTool &&
		    _LeftButtonUp)		// rechte Maustaste reagiert nur, wenn vorher linke gedrückt
								// und losgelassen wurde
		{
		// Maustaste zum ersten mal gedrückt
			_RightButtonSem = true;

			m_pAWDlg->ErgebnisEintragen (_AP, _EP, m_pCT);

			RMouseButtonDn();

			if (_RightButtonSem)
				_RightButtonSem = false;	// RBUTTONUP wurde geschluckt
			_LeftButtonUp = false;			// linke Maustaste muß erst wieder gedrückt und
											// losgelassen werden
			return true;
		}
		break;    // interessiert hier nicht
		
	case WM_MOUSEMOVE:
		if (_RightButtonSem) return false;	// nur abfangen
		_EP = BSInASCKoord (Pt, m_pCT);		// Endpunkt für Abstandsmessung
		AbstandAnzeigen();
		LMouseDrag (Pt);
		break;

	default:
		_ASSERTE (false);
		break;
	}
	
	return false;
} // WindowsNotification


// --------------------------------------------------------------------------------------------
// Aktionen, die bei InitExtension und DEX_PROJECTOPEN gleich sind
bool AbstandExtension :: InitAndOPEN (int iMode)
{
// IdentList und CoordTransX anlegen
	if (DEX_TestActiveProject())    // ein Projekt ist schon geöffnet
	{
		DELETE_OBJ (m_pIL);			// vorsichtshalber löschen
		DELETE_OBJ (m_pCT);
		m_pIL = new IdentList();	// IdentList nur anlegen, wenn ein Projekt geöffnet ist !!!
		m_pCT = new CoordTransX();	// Klasse für KoordinatenTransformation
		if (! m_pIL || ! m_pCT)
		{                                                                      
			DEX_Error (RC_abstand, EC_NOMEMORY);
			DELETE_OBJ (m_pIL)
			return false;
		}
		_bProj = true;

/* Erfolgt jetzt über " : CTriasExtension (0L, IDM_KILOMETRMENU)" in "Extras"
		// zusätzliche Menüpunkte im Recherchemenü (true) "Aktionen" (1) anhängen
		if (iMode == LEFullLoad && m_bMenIt == false)
		{
			InstallMenuItem (IDM_KILOMETR, IDS_KILOMETRIERUNG, true, 1);
			InstallMenuItem (IDM_KPUNKTLOESCHEN, IDS_KPUNKTLOESCHEN, true, 1);
			InstallMenuItem (IDM_TEILLOESCHEN, IDS_TEILLOESCHEN, true, 1);
			m_bMenIt = true;
		}
*/
	}


// Bäume für Objektnummern der Kilometrierungspunkte und der Teilkanten anlegen
	DELETE_OBJ (m_NrKPunkte);		// vorsichtshalber löschen
	DELETE_OBJ (m_NrTeile);
	m_NrKPunkte = new ObjNrBaum;	// Baum für Objektnummern der Kilometrierungspunkte
	m_NrTeile = new ObjNrBaum;		// Baum für Objektnummern der Teilkanten

	if (!m_NrKPunkte || !m_NrTeile)
	{
		DEX_Error (RC_abstand, EC_NOMEMORY);
		DELETE_OBJ (m_NrKPunkte);
		return false;
	}

	ReadCoordPrecision();	// Genauigkeit der Anzeige feststellen

	return true;
} // InitAndOPEN


// --------------------------------------------------------------------------------------------
// Aktionen, die bei UnLoadExtension und DEX_PROJECTCLOSE gleich sind
void AbstandExtension :: UnLoadAndCLOSE (void)
{
// restliche Daten abspeichern
	RestSpeichern();

 // Menüpunkte wieder entfernen
	if (_bWinOn)
	{
		RemoveMenuItem (ResID (IDM_ABSTAND, pRF), false, EXTRA_MENU_POS);
		_bWinOn = false;
	}
/*
	if (m_bMenIt)
	{
		RemoveMenuItem (IDM_KILOMETR, true, 1);
		RemoveMenuItem (IDM_KPUNKTLOESCHEN, true, 1);
		RemoveMenuItem (IDM_TEILLOESCHEN, true, 1);
		m_bMenIt = false;
	}
*/
	m_MenPktLoe = false;
	m_MenTeilLoe = false;

// dynamische Felder freigeben
	DELETE_OBJ (m_NrKPunkte);
	DELETE_OBJ (m_NrTeile);
	DELETE_OBJ (m_pAWDlg);			// Dialogbox für die Ergebnisse der Abstandsmessung
	DELETE_OBJ (m_pCT);
	DELETE_OBJ (m_pIL);

} // UnLoadAndCLOSE


// --------------------------------------------------------------------------------------------
// Hinzufügen des Knopfes zur WerkzeugLeiste 
 
// Dazu wird über TRiAS der Container aller Toolbars besorgt (QueryInterface), danach die
// gewünschte ToolBar (hier: "Werkzeuge") gesucht und gefunden. Mit AddBitmap wird dieser
// ToolBar die Bitmap (Streifen) mit allen ButtonBmps übergeben und anschließend werden die
// Buttons selbst installiert (hier einer).

// Der UIOwner ist so eine Art Feld von CallBack-Funktionen, die durch die ToolBar in
// verschiedenen Situationen gerufen werden, um diverse Informationen zu bekommen bzw.
// bestimmte Aktionen auszulösen.
bool AbstandExtension :: InstallToolbarButton (void)
{
// Finden der ToolBar "Werkzeuge"
WTRiASBarContainer ToolBars;
HRESULT hr = m_pXtnSite->QueryInterface (IID_ITRiASBarContainer, ToolBars.ppv());

	if (FAILED(hr)) return false;

WTRiASBar Bar;
ResString resTools (ResID (IDS_TOOLBARWERKZEUG, pRF), 32);	// "Werkzeuge" ist der Name der Toolbar

	hr = ToolBars->FindTRiASBar (resTools, Bar.ppi());
	if (S_OK != hr) return false;

ITRiASUIOwner* pIUIOwner = NULL;

	try
	{
	// alten "Lineal"-Button und dessen Parameter geben lassen und danach Button aus Toolbar löschen
	WTRiASToolBar ToolBar = Bar;		// throws_com_error

		m_iButtonIndex = -1;
		memset (&m_tb, '\0', sizeof (TBBUTTON));
		m_pIUIOwner = NULL;

		// bisherigen Index m_iButtonIndex für Rekonstruktion geben lassen; ID_ALTLINEAL ist der
		// ID des alten "Lineal"-Buttons
		hr = ToolBar->CommandToIndex (ID_ALTLINEAL, &m_iButtonIndex);
		if (FAILED(hr)) _com_issue_error (hr);

		// bisherige Struktur m_tb und bisherigen Pointer m_pIUIOwner für Rekonstruktion geben lassen
		hr = ToolBar->GetButton (m_iButtonIndex, &m_tb, &m_pIUIOwner);
		if (FAILED(hr)) _com_issue_error (hr);

		hr = ToolBar->DeleteItem (m_iButtonIndex);
		if (FAILED(hr)) _com_issue_error (hr);
		
	// Hinzufügen des neuen "Lineal"-Buttons
	int iOffset = 0;

		hr = ToolBar->AddBitmap (g_hInstance, ResID (IDB_TOOLBARABSTAND, pRF), BMPSIZE, &iOffset);
		if (FAILED(hr)) _com_issue_error (hr);

		hr = CUIOwner::_CreatorClass::CreateInstance (NULL, IID_ITRiASUIOwner, (LPVOID*)&pIUIOwner);
		if (FAILED(hr)) _com_issue_error (hr);

	// für den zu installierenden Button diese Struktur bereitstellen
	//              BitmapNr CmdID		 ButtonState ButtonStyle
	TBBUTTON tb = { iOffset, ID_TOOL_ABSTAND, 0, TBSTYLE_CHECKGROUP, 0L, 0 };

		hr = ToolBar->InsertButton (m_iButtonIndex, &tb, pIUIOwner);
		if (FAILED(hr)) _com_issue_error (hr);
		if (pIUIOwner) pIUIOwner->Release();
		pIUIOwner = NULL;
	}
	catch (...)
	{
		if (pIUIOwner) pIUIOwner->Release();
		pIUIOwner = NULL;
		TX_TRACE1 ("Can't add button to toolbar: %s\n", resTools.Addr());
		return false;
	}

	return true;
} // InstallToolbarButton


// --------------------------------------------------------------------------------------------
// Entfernen des installierten Knopfes aus der Toolbar
//
// Im Prinzip das gleiche, wie das Installieren, nur das die Funktion DeleteItem() gerufen wird.
// CommandToIndex() liefert die aktuelle Position unseres Buttons über seinen CmdID.
bool AbstandExtension :: RemoveToolbarButton (void)
{
// Finden der ToolBar "Werkzeuge"
WTRiASBarContainer ToolBars;
HRESULT hr = m_pXtnSite->QueryInterface (IID_ITRiASBarContainer, ToolBars.ppv());

	if (FAILED(hr)) return false;

WTRiASBar Bar;
ResString resTools (ResID (IDS_TOOLBARWERKZEUG, pRF), 32);	// "Werkzeuge" ist der Name der Toolbar

	hr = ToolBars->FindTRiASBar (resTools, Bar.ppi());
	if (S_OK != hr) return false;

	try
	{
	// Entfernen des neuen "Lineal"-Buttons
	WTRiASToolBar ToolBar = Bar;		// throws_com_error

		hr = ToolBar->DeleteItem (m_iButtonIndex);
		if (FAILED(hr)) _com_issue_error (hr);

	// alten "Lineal"-Button wieder hinzufügen
		hr = ToolBar->InsertButton (m_iButtonIndex, &m_tb, m_pIUIOwner);
		if (FAILED(hr)) _com_issue_error (hr);
		if (m_pIUIOwner) m_pIUIOwner->Release();
		m_pIUIOwner = NULL;
	}
	catch (...)
	{
		TX_TRACE1 ("Can't remove button from toolbar %s\n", resTools.Addr());
		return false;
	}

	return true;

} // RemoveToolbarButton


// --------------------------------------------------------------------------------------------
// Abstand zwischen Anfangspunkt _AP und Endpunkt _EP ermitteln und in DialogBox anzeigen
void AbstandExtension :: AbstandAnzeigen (void)
{
double dAbst = m_pCT->CoordTransDistance (&_AP, &_EP); // Abstand ermitteln

	m_pAWDlg->AbstandEintragen (dAbst);       // Abstand in DialogBox eintragen
} // AbstandAnzeigen


// --------------------------------------------------------------------------------------------
// evtl. Rest aus DialogBox abspeichern, wenn Projekt geschlossen bzw. TRiAS beendet wird
void AbstandExtension :: RestSpeichern (void)
{
	// DialogBox ist schon gelöscht, ein evtl. Datenrest wurde schon gespeichert
	if (m_pAWDlg == NULL) return;

MultiLineEdit* pMLE = m_pAWDlg->GetErgebnis();
int iTexLen = pMLE->GetTextLen() + 1;

	if (iTexLen <= 1) return;	// kein Text zum Abspeichern vorhanden

ResString Capt (ResID (IDS_BOXCAPTION1, pRF), 30);
ResString Inhalt (ResID (IDS_BOXTEXT1, pRF), 80);
MessBox mb (Capt.Addr(), Inhalt.Addr(), m_pAWDlg);

	mb.SetType (QuestionMarkIcon | YesNoButtons);
	if (mb.Show() == YesReply)
	{
	FILE* fAbst = m_pAWDlg->GetDatei();

		if (fAbst == NULL)	// keine Datei geöffnet
		{
		char* pFileName = m_pAWDlg->DateiAuswaehlen (MWind());
		
			if (pFileName)
			{
				if (m_pAWDlg->GetSpForm())
					remove (pFileName);		// evtl. alte Datei löschen
				fAbst = fopen (pFileName, "ab");
			}
			else return;	// keine Datei ausgewählt
		}

	char* pcBuffer = new char[iTexLen];
	
		if (! pcBuffer)
		{
			DEX_Error (RC_abstand, EC_NOMEMORY);
			return;
		}

		pMLE->GetText (pcBuffer, iTexLen);
		fprintf (fAbst, "%s", pcBuffer);
		fclose (fAbst);
		DELETE_VEC (pcBuffer);
	}
} // RestSpeichern


// --------------------------------------------------------------------------------------------
// Auslesen des HeaderEintrags "CoordPrecision"
bool AbstandExtension :: ReadCoordPrecision (void)
{
	m_cGenau = '0';

// Anzahl der Nachkommastellen für Anzeige aus Datenbank-Header ermitteln
HeaderEntryX HE (ResString (ResID (IDS_COORDPRECISION, pRF), 20));

	if (HE.Status() != HE_INVALID)	// HaederEintrag "CoordPrecision" existiert im DB-Header
	{
	char pcCP[5] = "0";

		strcpy (pcCP, HE.EntryText());
		if (0 == strlen(pcCP))		// HeaderEntry-Eintrag ist leer, dann (15.03.99)
			return true;			// m_cGenau = '0'

		if (1 == strlen(pcCP))
		{
			m_cGenau = pcCP[0];
			return true;
		}

		_ASSERTE (false);			// mehr als 9 Kommastellen
		m_cGenau = '9';
	}

	return false;	// HaederEintrag "CoordPrecision" existiert gar nicht im DB-Header

} // ReadCoordPrecision


// --------------------------------------------------------------------------------------------
// Kilometrierung durch Setzen von Punkten im Abstand "dDistanz" entlang des
// pIOG-Linienobjektes beginnend beim Anfangspunkt (lXA,lYA) bis zum Endpunkt (lXE,lYE)
bool AbstandExtension :: LinienKilometrierung (IObjektGeometrie* pIOG, KoOrd lXA, KoOrd lYA,
					  KoOrd lXE, KoOrd lYE, double dDistanz, double dTextStartWert, bool bTeil)
{
	_ASSERTE (pIOG != NULL);

	if (!pIOG || (lXA == lXE && lYA == lYE) || dDistanz <= 0.)
	{
		DEX_Error (RC_abstand, EC_ILLPARS);
		return false;
	}

double dTextWert = dTextStartWert;	// Wert für Textobjekt der Kilometrierungspunkte
ulong ulIdent;

	if (bTeil)
		pIOG->GetIdent (&ulIdent);

	_ASSERTE (0 != ulIdent);
	_ASSERTE ((ulong)-1 != ulIdent);


// wenn Startpunkt (lXA,lYA) bzw. Endpunkt (lXE,lYE) - so dieser überhaupt vorgegeben ist, d.h.
// lXE >= 0 und lYE >= 0 - nicht auf der Kante liegt, dann den nächstgelegen Punkt auf der
// Kante suchen
long lIndA, lIndE;	// Parameter von GetPointOnObject();
BOOL bPA, bPE;		// werden hier niht weiter ausgewertet

	pIOG->GetPointOnObject (&lXA, &lYA, &lIndA, &bPA);
	if (lXE >= 0 && lYE >= 0)
		pIOG->GetPointOnObject (&lXE, &lYE, &lIndE, &bPE);

HPROJECT hPr = DEX_GetObjectsProject (ulIdent);

	if (!KilometrPunktSetzen (hPr, lXA, lYA, dTextWert))
		return false;

HRESULT hrRet;		// return-Wert von Routine TeilKante()
KoOrd lXANeu = lXA;	// Koordinaten des Startpunktes
KoOrd lYANeu = lYA;	//  für TeilKante()
WObjektGeometrie wTKante;

	do
	{
		if (bTeil)	// mit Teilkanten
		{
			if (FAILED(CreateInterfaceOG (wTKante.ppi(), lXANeu, lYANeu, OT_KANTE)))
				return false;
			hrRet = TeilKante (pIOG, lXANeu, lYANeu, lXE, lYE, dDistanz, wTKante.ppi());
		}
		else		// ohne Teilkanten
			hrRet = TeilKante (pIOG, lXANeu, lYANeu, lXE, lYE, dDistanz, NULL);

		if (wTKante.IsValid())
			TeilkanteAnTRiAS (hPr, wTKante, ulIdent);

		dTextWert += dDistanz;
		if (!KilometrPunktSetzen (hPr, lXANeu, lYANeu, dTextWert))
			return false;
	}
	while ((lXANeu != lXE || lYANeu != lYE) &&	// Startpunkt != Endpunkt
		   S_OK == hrRet);						// der Rest reicht immer noch zu einem
												//  vollständigen Kantenabschnitt
	return true;

} // LinienKilometrierung


// --------------------------------------------------------------------------------------------
// Kilometrierung durch Setzen von Punkten im Abstand von dDistanz entlang einer zu
// konstruierenden Mittellinie des lONr-Flächenobjektes
bool AbstandExtension :: FlaechenKilometrierung (IObjektGeometrie* pIOG, KoOrd lXA, KoOrd lYA,
					  KoOrd lXE, KoOrd lYE, double dDistanz, double dTextStartWert, bool bTeil)
{
	return true;

} // FlaechenKilometrierung


// --------------------------------------------------------------------------------------------
// Kilometrierungspunkte mit angebundenen Textobjekten versehen
bool AbstandExtension :: AppendTextObject (long lKMONr, KoOrd x, KoOrd y, double dTextWert)
{
char pcText[20] = { '\0' };		// Text des Textobjektes
char pcFormat[10] = "%-10.0f";	// Format für Anzeige

	DtoA (pcText, pcFormat, dTextWert);
	strcat (pcText, " m");			// Maßeinheit "Meter" anfügen

int iTextLen = strlen (pcText) + 1;	// "+1" für "\0"
long lCnt = 1;						// Gesamtanzahl der Stützpunkte (Größe der KoordFelder)

TEXTGEOMETRIE TG;

	INITSTRUCT (TG, TEXTGEOMETRIE);
	TG.dwSize = sizeof (TEXTGEOMETRIE);
	TG.pdblX = new KoOrd[lCnt];
	if (TG.pdblX == NULL) return false;
	TG.pdblY = new KoOrd[lCnt];
	if (TG.pdblY == NULL) return false;
	TG.pText = new char[iTextLen];
	if (TG.pText == NULL) return false;

	TG.lIdent = m_ulKMIdent;
	TG.iObjTyp = OT_TEXT;
	TG.iFlags |= OGNewObject;			// Geometrie des Objektes nicht ersetzen sondern neu in
										// DB ablegen
	TG.iFlags |= OGForceGeometry;		// kein Test, ob neues Objekt innerhalb des
										// Projekt-Containers liegt
	TG.iFlags |= OGGeometryIsChecked;	// georein nicht anwerfen
	TG.lCnt = lCnt;						// Gesamtanzahl der Stützpunkte (Größe der KoordFelder)
	TG.iKCnt = iTextLen;				// (max.) Textlänge

Point p = BSKoordinaten (x, y);

	p.X() += iOff;		// Textobjekt etwas von Kilometrierungspunkt abrücken
	p.Y() += iOff;		// iOff ist in abskonst.hxx definiert

EPunkt P = DBKoordinaten (p);

	((KoOrd*)TG.pdblX)[0] = P.X();		// Koordinaten
	((KoOrd*)TG.pdblY)[0] = P.Y();
	strcpy (TG.pText, pcText);			// Text des Textobjektes 

bool bRet = DEX_ModObjGeometrie (TG);

	DELETE_OBJ (TG.pdblX);
	DELETE_OBJ (TG.pdblY);
	DELETE_OBJ (TG.pText);

	_ASSERTE (bRet == true);
	_ASSERTE (TG.lONr != 0);
	_ASSERTE (TG.lONr != -1);

// erzeugtes Textobjekt soll von dem dazugehörigen Kilometrierungspunkt abhängig sein
MODRELATION MREL;		// Struktur für Veränderung von Abhängigkeiten

	INITSTRUCT (MREL, MODRELATION);
	MREL.iRTyp = RTBegleitO;		// RelationsTyp "Begleitrelation"
	// durch INITSTRUCT() wird MREL.lRCode = 0 gesetzt, was auch ausreicht, da es bei
	// Begleitrelationen nur EINE Verbindung geben kann (im Gegensatz zur Komplexrelation, wo
	// MEHRERE Verbindungen bestehen können)

	MREL.lPONr = lKMONr;			// PrimärObjekt, d.h. Geometrieobjekt
	MREL.lSONr = TG.lONr;			// SekundärObjekt, d.h. Textobjekt
	DEX_ModifyRelation (MREL);		// ohne Funktion MREL.eFcn

	return bRet;

} // AppendTextObject


// --------------------------------------------------------------------------------------------
// Teilkante wird in die TRiAS-Datenbank eingetragen
bool AbstandExtension :: TeilkanteAnTRiAS (HPROJECT hPr, IObjektGeometrie* pITK, ulong ulIdent)
{
	_ASSERTE (pITK != NULL);

	if (! pITK) return false;

	if (0 != ulIdent && (ulong)-1 != ulIdent)
		pITK->SetIdent (ulIdent);
	else	// ulIdent == 0 || ulIdent = -1 
		pITK->SetIdent (DEX_GetUnknownIdentEx (hPr));
	// OGNewObject:     permanentes Objekt in Datenbank aufnehmen
	// OGAddToView:     Identifikator zur Sicht hinzufügen
	// OGForceGeoError: Objekt wird bei Geometriefehler von GEOREIN abgewiesen
	pITK->SetFlags (OGNewObject | OGAddToView | OGForceGeoError);

#if _TRiAS_VER < 0x0300
	// 1. Parameter von GeometrieAnTRiAS() besagt, daß Undo nicht vorgesehen ist
	// 2. Parameter wird in diesem Fall nicht ausgewertet
	if (S_OK != pITK->GeometrieAnTRiAS (false, NULL))
#else
//INT_PTR hPr = reinterpret_cast<INT_PTR>(DEX_GetObjectsProject (ulIdent));

	// 2. Parameter von GeometrieAnTRiASEx() besagt, daß Undo nicht vorgesehen ist
	// 3. Parameter wird in diesem Fall nicht ausgewertet
	if (S_OK != pITK->GeometrieAnTRiASEx (reinterpret_cast<INT_PTR>(hPr), false, NULL))
#endif // _TRiAS_VER < 0x0300
		return false;

long lNeuONr;	// Objektnummer des eben neu eingespeicherten pITK-Objektes

	pITK->GetONr (&lNeuONr);
	m_NrTeile->InsertK (lNeuONr);
	m_MenTeilLoe = true;

// Merkmale kopieren (sollen hier noch die Merkmale kopiert werden ??????????????????????)
	
	if (0 != lNeuONr && -1 != lNeuONr)	// Unique Ident verpassen
	{
	string sUIText;
	ResString resText (ResID (IDS_UIFORMAT, pRF), 20);

		Format (sUIText, (char*)resText.Addr(), lNeuONr);
#if _TRiAS_VER < 0x0300
		WriteFeatureText (lNeuONr, DEX_GetUniqueIdentMCode(), TT_Objekt, sUIText);
#else
		WriteFeatureText (lNeuONr, DEX_GetUniqueIdentMCodeEx (DEX_GetObjectProject(lNeuONr)), TT_Objekt, sUIText);
#endif // _TRiAS_VER < 0x0300
	}

	return true;

} // TeilkanteAnTRiAS


// --------------------------------------------------------------------------------------------
// Kilometrierungspunkt setzen
bool AbstandExtension :: KilometrPunktSetzen (HPROJECT hPr, KoOrd x, KoOrd y, double dTextWert)
{
	_ASSERTE (x >= 0);
	_ASSERTE (y >= 0);

	if (x < 0 || y < 0)
	{
		DEX_Error (RC_abstand, EC_ILLPARS);
		return false;
	}

// ObjektGeometrie für Eintrag in die TRiAS-Datenbank
WObjektGeometrie wKPunkt;

	if (FAILED(CreateInterfaceOG (wKPunkt.ppi(), x, y, OT_PUNKT)))
		return false;

	if (0 == m_ulKMIdent || -1 == m_ulKMIdent)
		m_ulKMIdent = DEX_GetUnknownIdentEx (hPr);
	wKPunkt->SetIdent (m_ulKMIdent);

	// OGNewObject: permanentes Objekt in Datenbank aufnehmen
	// OGAddToView: Identifikator zur Sicht hinzufügen
	wKPunkt->SetFlags (OGNewObject | OGAddToView);
	wKPunkt->SetKCnt (-1);				// Größe des Konturfeldes

#if _TRiAS_VER < 0x0300
	// 1. Parameter besagt, daß Undo nicht vorgesehen ist
	// 2. Parameter wird in diesem Fall nicht ausgewertet
	if (S_OK != wKPunkt->GeometrieAnTRiAS (false, NULL))
#else
	// 2. Parameter besagt, daß Undo nicht vorgesehen ist
	// 3. Parameter wird in diesem Fall nicht ausgewertet
	if (S_OK != wKPunkt->GeometrieAnTRiASEx (reinterpret_cast<INT_PTR>(hPr), false, NULL))
#endif // _TRiAS_VER < 0x0300
		return false;

long lNeuONr;	// Objektnummer des eben neu eingespeicherten wKPunkt-Objektes

	wKPunkt->GetONr (&lNeuONr);
	m_NrKPunkte->InsertK (lNeuONr);
	m_MenPktLoe = true;

	if (0 != lNeuONr && -1 != lNeuONr)	// Unique Ident verpassen
	{
	string sUIText;
	ResString resText (ResID (IDS_UIFORMAT, pRF), 20);

		Format (sUIText, (char*)resText.Addr(), lNeuONr);
#if _TRiAS_VER < 0x0300
		WriteFeatureText (lNeuONr, DEX_GetUniqueIdentMCode(), TT_Objekt, sUIText);
#else
		WriteFeatureText (lNeuONr, DEX_GetUniqueIdentMCodeEx (DEX_GetObjectProject(lNeuONr)), TT_Objekt, sUIText);
#endif // _TRiAS_VER < 0x0300

		// evtl. dazugehöriges Textobjekt bilden
		if (m_bText)
			AppendTextObject (lNeuONr, x, y, dTextWert);
	}

	return true;

} // KilometrPunktSetzen


// --------------------------------------------------------------------------------------------
// Bereich, in dem die Kilometrierung vorgenommen wurde, neu zeichnen
void AbstandExtension :: BereichZeichnen (void)
{
Point PLO = BSKoordinaten (m_KC.XMin(), m_KC.YMax());
Point PRU = BSKoordinaten (m_KC.XMax(), m_KC.YMin());

int iPixPX, iPixPY;	// Größe des Punktsymbols eines Kilometrierungspunktes in BS-Pixel

	PointSymbolSize (m_ulKMIdent, iPixPX, iPixPY);

	PLO.X() -= iPixPX;
	PRU.Y() -= iPixPY;

	if (m_bText)
	{
		PLO.Y() += 20 * iPixPY;	// in der Hoffnung, daß der Text nicht höher als die 20-fache
								// Punktsymbolhöhe ist
		// da es etwas aufwendig ist, die Breite des Textes zu ermitteln, der am weitesten nach
		// rechts ragt, zeichne ich ganz einfach bis zum rechten Bildschirmrand
		PRU.X() = MVWind()->CanvasRect().Right();
	}
	else
	{
		PLO.Y() += iPixPY;
		PRU.X() += iPixPX;
	}

Rectangle Rec (PLO, PRU);
	 
	DEX_RePaintRectWait (Rec);
	MVWind()->Update();		// sofort zeichnen

} // BereichZeichnen


// --------------------------------------------------------------------------------------------
// Abstand zwischen Punkt und Punkt
double AbstandExtension :: AbstandPunktPunkt (EPunkt* pP1, EPunkt* pP2)
{
	_ASSERTE (pP1 != NULL);
	_ASSERTE (pP2 != NULL);

	if (pP1->X() == pP2->X() && pP1->Y() == pP2->Y())
		return 0.;

double XOut1, YOut1, XOut2, YOut2;	// Real-Koordinaten

	m_pCT->UnScale (*pP1, &XOut1, &YOut1);	// DB-Koordinaten in ASC-Format transformieren
	m_pCT->UnScale (*pP2, &XOut2, &YOut2);	//  (incl. rausrechnen der internen Skalierung)

DoublePair P1 (XOut1, YOut1);
DoublePair P2 (XOut2, YOut2);

	return m_pCT->CoordTransDistance (&P1, &P2); // Abstand ermitteln

} // AbstandPunktPunkt


// --------------------------------------------------------------------------------------------
// Abstand zwischen Punkt und Linie
double AbstandExtension :: AbstandPunktLinie (long lONr1, EPunkt* pP, long lONr2, EKante* pK,
											  DistTyp dtTyp)
{
	_ASSERTE (lONr1 != 0);
	_ASSERTE (lONr1 != -1);
	_ASSERTE (pP != NULL);
	_ASSERTE (lONr2 != 0);
	_ASSERTE (lONr2 != -1);
	_ASSERTE (pK != NULL);

// Test, ob Punktobjekt auf Linienobjekt liegt
Posit posLage = pP->PunktAufKante (pK);

	if (INNERH == posLage || AUSSERHB == posLage)
		return 0;		// wenn ja, dann Abstand = 0

	// Abstand ermitteln
	switch (dtTyp)
	{
		case DISTTYP_AUTO:
			return AbstandPunktKanteAuto (pP, lONr2, pK);

		case DISTTYP_MIDDLE:
			return AbstandMitte (lONr1, lONr2);

		case DISTTYP_VERTEX:
			return AbstandPunktKanteStuetz (pP, pK);

		case DISTTYP_EXACT:
//			return AbstandPunktKanteStuetz (pP, pK);	// z. Zt. noch mit DISTTYP_VERTEX identisch !!!!!
			return AbstandPunktKanteExakt (pP, pK);	// 05.02.98

		default:
			_ASSERTE (false);
			break;
	}

	return -1.;
} // AbstandPunktLinie


// --------------------------------------------------------------------------------------------
// Abstand zwischen Linie und Linie
double AbstandExtension :: AbstandLinieLinie (long lONr1, EKante* pK1, long lONr2, EKante* pK2,
											  DistTyp dtTyp)
{
	_ASSERTE (lONr1 != 0);
	_ASSERTE (lONr1 != -1);
	_ASSERTE (pK1 != NULL);
	_ASSERTE (lONr2 != 0);
	_ASSERTE (lONr2 != -1);
	_ASSERTE (pK2 != NULL);

// Test, ob sich beide Linienobjekte schneiden; wenn ja, dann Abstand = 0
Posit posLage = pK1->KantenLage (pK2);

	if (posLage == UNKLAR)
	{
		_ASSERTE (false);
		return -1.;			// Fehler
	}
	if (posLage != AUSSERH)	// Linienobjekte haben mindestens einen Punkt gemeinsam
		return 0.;			// dann Abstand = 0

	// Abstand ermitteln
	switch (dtTyp)
	{
		case DISTTYP_AUTO:
			return AbstandKanteKanteAuto (lONr1, pK1, lONr2, pK2);

		case DISTTYP_MIDDLE:
			return AbstandMitte (lONr1, lONr2);

		case DISTTYP_VERTEX:
		{
		double dAbst = DBL_MAX;
		double dZW;					// Zwischenwert
		long lKL1 = pK1->ASP();	// Kantenlänge des 1. Linienobjektes

			// den kürzesten Abstand zwischen den Stützpunkten des ersten und den Stützpunkten
			// des zweiten Linienobjektes ermitteln
			for (long i = 0; i < lKL1; i++)
			{
				dZW = AbstandPunktKanteStuetz (&pK1->SP(i), pK2);
				if (dZW < dAbst) dAbst = dZW;
			}
			return dAbst;
		}

		case DISTTYP_EXACT:
		{
		double dAbst = DBL_MAX;
		double dZW;					// Zwischenwert
		long lKL1 = pK1->ASP();	// Kantenlänge des 1. Linienobjektes

			// den kürzesten Abstand zwischen den Stützpunkten des ersten und den Stützpunkten
			// des zweiten Linienobjektes ermitteln
			for (long i = 0; i < lKL1; i++)
			{
				dZW = AbstandPunktKanteExakt (&pK1->SP(i), pK2);
				if (dZW < dAbst) dAbst = dZW;
			}
			return dAbst;
		}

		default:
			_ASSERTE (false);
			break;
	}

	return -1.;
} // AbstandLinieLinie


// --------------------------------------------------------------------------------------------
// Abstand (Min) des Stützpunktes des pK1-Linienobjektes ermitteln, der am weitesten (Max) vom
// pK2-Linienobjekt entfernt ist;
// ACHTUNG: Die umgekehrte Frage (welcher pK2-Stützpunkt ist am weitesten von pK1 entfernt)
//          bringt i.d.R. ein anderes Ergebnis
double AbstandExtension :: MaxMinAbstandLinieLinie (EKante* pK1, EKante* pK2, DistTyp dtTyp)
{
	_ASSERTE (pK1 != NULL);
	_ASSERTE (pK2 != NULL);
	_ASSERTE (dtTyp == DISTTYP_VERTEX || dtTyp == DISTTYP_EXACT);

	if (!pK1 || !pK2 || 
		(dtTyp != DISTTYP_VERTEX && dtTyp != DISTTYP_EXACT))
		return -1.;			// Fehler

double dMaxAbst = -1;
double dZW;					// Zwischenwert
long lKL1 = pK1->ASP();	// Kantenlänge des 1. Linienobjektes

	if (dtTyp == DISTTYP_VERTEX)
	{
		for (long i = 0; i < lKL1; i++)
		{
			dZW = AbstandPunktKanteStuetz (&pK1->SP(i), pK2);
			if (dZW > dMaxAbst) dMaxAbst = dZW;
		}
		return dMaxAbst;
	}


	// DISTTYP_EXACT
	for (long i = 0; i < lKL1; i++)
	{
		dZW = AbstandPunktKanteExakt (&pK1->SP(i), pK2);
		if (dZW > dMaxAbst) dMaxAbst = dZW;
	}
	return dMaxAbst;

} // MaxMinAbstandLinieLinie


// --------------------------------------------------------------------------------------------
// Abstand zwischen den umschließenden Rechtecken zweier Objekte ermitteln
double AbstandExtension :: AbstandRechtecke (long lONr1, long lONr2)
{
	_ASSERTE (lONr1 != 0);
	_ASSERTE (lONr1 != -1);
	_ASSERTE (lONr2 != 0);
	_ASSERTE (lONr2 != -1);

long lCO1[4], lCO2[4];	// Koordinaten des umschließenden Rechtecks
						// lCO[0] = xmin, lCO[1] = xmax, lCO[2] = ymin, lCO[3] = ymax

	DEX_GetObjContainer (lONr1, lCO1);	// Koordinaten des umschließenden Rechtecks ermitteln
	DEX_GetObjContainer (lONr2, lCO2);

// der Abstand zwischen den umschließenden Rechtecken wird als der größere der beiden Abstände
// lAbstX und lAbstY in x- bzw. y-Richtung definiert;
// dessen Berechnung erfolgt mit den Datenbank-Koordinaten x1, y1, x2, y2;
// für den Fall, daß der Abstand zwischen den umschließenden Rechtecken in x-Richtung ermittelt
// wird, müssen die beiden y-Koordinaten y1 und y2 beliebige, aber gleiche Werte besitzen; für
// den Fall, daß der Abstand in y-Richtung ermittelt wird, müssen die beiden x-Koordinaten x1
// und x2 beliebige, aber gleiche Werte besitzen
long lAbstX = 0;	// Abstand der beiden umschließenden Rechtecke in x-Richtung
long lAbstY = 0;	// Abstand der beiden umschließenden Rechtecke in y-Richtung
KoOrd x1 = lCO1[0];	// evtl. werden für x1 und x2 werden 2 beliebige, aber
KoOrd x2 = lCO1[0];	//  gleiche Werte benötigt
KoOrd y1 = lCO1[2];	// evtl. werden für y1 und y2 werden 2 beliebige, aber
KoOrd y2 = lCO1[2];	//  gleiche Werte benötigt

	if (lCO2[0] - lCO1[1] > 0)
	{
		lAbstX = lCO2[0] - lCO1[1];
		x1 = lCO2[0];
		x2 = lCO1[1];
	}
	else		// es gilt niemals gleichzeitig lCO2[0]-lCO1[1]>0 und lCO1[0]-lCO2[1]>0
	{			// allerhöchstens beide gleichzeitig = 0
		if (lCO1[0] - lCO2[1] > 0)
		{
			lAbstX = lCO1[0] - lCO2[1];
			x1 = lCO1[0];
			x2 = lCO2[1];
		}
	}

	if (lCO2[2] - lCO1[3] > 0)
	{
		lAbstY = lCO2[2] - lCO1[3];
		y1 = lCO2[2];
		y2 = lCO1[3];
	}
	else
	{
		if (lCO1[2] - lCO2[3] > 0)
		{
			lAbstY = lCO1[2] - lCO2[3];
			y1 = lCO1[2];
			y2 = lCO2[3];
		}
	}

	if (lAbstX == 0 && lAbstY == 0)
		return 0.;

double XOut1, YOut1, XOut2, YOut2;	// Real-Koordinaten

	m_pCT->UnScale (x1, y1, &XOut1, &YOut1);	// DB-Koordinaten in ASC-Format transformieren
	m_pCT->UnScale (x2, y2, &XOut2, &YOut2);	//  (incl. rausrechnen der internen Skalierung)

DoublePair MP1 (XOut1, YOut1);	// Real-Koordinaten für CoordTransDistance()
DoublePair MP2 (XOut2, YOut2);

	return m_pCT->CoordTransDistance (&MP1, &MP2); // Abstand ermitteln

} // AbstandRechtecke


// --------------------------------------------------------------------------------------------
// Abstand zwischen 2 Objekten als Abstand zwischen den Mittelpunkten der umschließenden
// Rechtecke ermitteln
double AbstandExtension :: AbstandMitte (long lONr1, long lONr2)
{
	_ASSERTE (lONr1 != 0);
	_ASSERTE (lONr1 != -1);
	_ASSERTE (lONr2 != 0);
	_ASSERTE (lONr2 != -1);

long lCO1[4], lCO2[4];	// Koordinaten des umschließenden Rechtecks
						// lCO[0] = xmin, lCO[1] = xmax, lCO[2] = ymin, lCO[3] = ymax

	DEX_GetObjContainer (lONr1, lCO1);	// Koordinaten des umschließenden Rechtecks ermitteln
	DEX_GetObjContainer (lONr2, lCO2);

KoOrd x1 = DtoL (((double)lCO1[0]+lCO1[1]) / 2.);	// Datenbank-Koordinaten der Container-
KoOrd y1 = DtoL (((double)lCO1[2]+lCO1[3]) / 2.);	//  Mittelpunkte beider Objekte
KoOrd x2 = DtoL (((double)lCO2[0]+lCO2[1]) / 2.);
KoOrd y2 = DtoL (((double)lCO2[2]+lCO2[3]) / 2.);
double XOut1, YOut1, XOut2, YOut2;	// Real-Koordinaten

	m_pCT->UnScale (x1, y1, &XOut1, &YOut1);	// DB-Koordinaten in ASC-Format transformieren
	m_pCT->UnScale (x2, y2, &XOut2, &YOut2);	//  (incl. rausrechnen der internen Skalierung)

DoublePair MP1 (XOut1, YOut1);	// Container-Mittelpunkte in Real-Koordinaten
DoublePair MP2 (XOut2, YOut2);

	return m_pCT->CoordTransDistance (&MP1, &MP2); // Abstand ermitteln
} // AbstandMitte


// --------------------------------------------------------------------------------------------
// kleinster Abstand zwischen einem einzelnen (Stütz-)Punkt und den Stützpunkten der
// lONr-Kante, wobei evtl. von der Kante nur der Containermittelpunkt genommen wird, wenn der
// Kanten-Container im Vergleich zum Abstand "klein" ist
double AbstandExtension :: AbstandPunktKanteAuto (EPunkt* pP, long lONr, EKante* pK)
{
	_ASSERTE (pP != NULL);
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);
	_ASSERTE (pK != NULL);

long lCO[4];	// Containerkoordinaten (lCO[0] = xmin, lCO[1] = xmax, lCO[2] = ymin, lCO[3] = ymax)

	DEX_GetObjContainer (lONr, lCO);	// Containerkoordinaten ermitteln

KoOrd xm = DtoL (((double)lCO[0]+lCO[1]) / 2.);	// Datenbank-Koordinaten des Container-
KoOrd ym = DtoL (((double)lCO[2]+lCO[3]) / 2.);	//  Mittelpunktes der Kante
EPunkt* pMP = new EPunkt (EPunkt (xm, ym));

	if (! pMP)
	{
		DEX_Error (RC_abstand, EC_NOMEMORY);
		return -1.;
	}

// Abstand zwischen Punkt pP und Containermittelpunkt der Kante (in Datenbank-Koordinaten)
double dAbstGrob = AbstandPunktPunkt (pP, pMP);
                  
	DELETE_OBJ (pMP);
	
EPunkt PLU (lCO[0], lCO[2]);	// Container-Ecke links unten
EPunkt PRU (lCO[1], lCO[2]);	// rechts unten
EPunkt PRO (lCO[1], lCO[3]);	// rechts oben
double dCS1 = AbstandPunktPunkt (&PLU, &PRU);	// Seitenlängen des Kanten-Containers
double dCS2 = AbstandPunktPunkt (&PRU, &PRO);
double dMaxCS;						// größte der beiden Container-Seiten

	(dCS1 > dCS2) ? (dMaxCS = dCS1) : (dMaxCS = dCS2);
	if (dAbstGrob > dVer * dMaxCS)	// Kanten-Container	ist im Vergleich zum Abstand "klein",
		return dAbstGrob;			// dann keine genauere Berechnung mit den Stützpunkten der Kante
	return AbstandPunktKanteStuetz (pP, pK);	// sonst genauere Berechnung

} // AbstandPunktKanteAuto


// --------------------------------------------------------------------------------------------
// kleinster Abstand zwischen zwei Kanten wobei evtl. von den Kanten nur der
// Containermittelpunkt genommen wird, wenn der jeweilige Kanten-Container im Vergleich zum
// Abstand "klein" ist
double AbstandExtension :: AbstandKanteKanteAuto (long lONr1, EKante* pK1,
												  long lONr2, EKante* pK2)
{
	_ASSERTE (lONr1 != 0);
	_ASSERTE (lONr1 != -1);
	_ASSERTE (pK1 != NULL);
	_ASSERTE (lONr2 != 0);
	_ASSERTE (lONr2 != -1);
	_ASSERTE (pK2 != NULL);

long lCO1[4], lCO2[4];	// Containerkoordinaten
						// lCO[0] = xmin, lCO[1] = xmax, lCO[2] = ymin, lCO[3] = ymax

	DEX_GetObjContainer (lONr1, lCO1);	// Containerkoordinaten ermitteln
	DEX_GetObjContainer (lONr2, lCO2);

KoOrd x1 = DtoL (((double)lCO1[0]+lCO1[1]) / 2.);	// Datenbank-Koordinaten der Container-
KoOrd y1 = DtoL (((double)lCO1[2]+lCO1[3]) / 2.);	//  Mittelpunkte beider Kanten
KoOrd x2 = DtoL (((double)lCO2[0]+lCO2[1]) / 2.);
KoOrd y2 = DtoL (((double)lCO2[2]+lCO2[3]) / 2.);
EPunkt* pMP1 = new EPunkt (EPunkt (x1, y1));
EPunkt* pMP2 = new EPunkt (EPunkt (x2, y2));

	if (!pMP1 || !pMP2)
	{
		DEX_Error (RC_abstand, EC_NOMEMORY);
		DELETE_OBJ (pMP1);
		return -1.;
	}

// Abstand zwischen den Container-Mittelpunkten (in Datenbank-Koordinaten)
double dAbstGrob = AbstandPunktPunkt (pMP1, pMP2);

EPunkt PLU1 (lCO1[0], lCO1[2]);	// Ecke des 1. Containers links unten
EPunkt PRU1 (lCO1[1], lCO1[2]);	// rechts unten
EPunkt PRO1 (lCO1[1], lCO1[3]);	// rechts oben
double dCS11 = AbstandPunktPunkt (&PLU1, &PRU1);	// Seitenlängen des 1. Containers
double dCS12 = AbstandPunktPunkt (&PRU1, &PRO1);
EPunkt PLU2 (lCO2[0], lCO2[2]);	// Ecke des 2. Containers links unten
EPunkt PRU2 (lCO2[1], lCO2[2]);	// rechts unten
EPunkt PRO2 (lCO2[1], lCO2[3]);	// rechts oben
double dCS21 = AbstandPunktPunkt (&PLU2, &PRU2);	// Seitenlängen des 2. Containers
double dCS22 = AbstandPunktPunkt (&PRU2, &PRO2);
double dMaxCS1, dMaxCS2;		// die größten Container-Seiten

	(dCS11 > dCS12) ? (dMaxCS1 = dCS11) : (dMaxCS1 = dCS12);
	(dCS21 > dCS22) ? (dMaxCS2 = dCS21) : (dMaxCS2 = dCS22);

double dAbst = DBL_MAX;		// return-Wert

	if (dAbstGrob > dVer * dMaxCS1)
	{
		if (dAbstGrob > dVer * dMaxCS2)	// beide Kanten-Container sind im Vergleich zum Abstand "klein",
			dAbst = dAbstGrob;			// dann keine genauere Berechnung mit den Stützpunkten der Kanten
		else
			dAbst = AbstandPunktKanteStuetz (pMP1, pK2);	// nur Kante pK2 genauer
	}
	else
	{
		if (dAbstGrob > dVer * dMaxCS2)
			dAbst = AbstandPunktKanteStuetz (pMP2, pK1);	// nur Kante pK1 genauer
		else			// genaue Berechnnung unter Einbeziehung der Stützpunkte beider Kanten
		{
		double dZW;				// Zwischenwert
		long lKL1 = pK1->ASP();	// Kantenlänge des 1. Linienobjektes

			// den kürzesten Abstand zwischen den Stützpunkten des ersten und den Stützpunkten
			// des zweiten Linienobjektes ermitteln
			for (long i = 0; i < lKL1; i++)
			{
				dZW = AbstandPunktKanteStuetz (&pK1->SP(i), pK2);
				if (dZW < dAbst) dAbst = dZW;
			}
		}
	}

	DELETE_OBJ (pMP1);
	DELETE_OBJ (pMP2);

	return dAbst;
} // AbstandKanteKanteAuto


// --------------------------------------------------------------------------------------------
// kleinster Abstand zwischen einem einzelnen (Stütz-)Punkt und den Stützpunkten einer Kante
double AbstandExtension :: AbstandPunktKanteStuetz (EPunkt* pP, EKante* pK)
{
	_ASSERTE (pP != NULL);
	_ASSERTE (pK != NULL);

DoublePair OB1 = DoublePair();	// Real-Koordinaten
DoublePair OB2 = DoublePair();

	m_pCT->UnScale (*pP, &OB1.X(), &OB1.Y());	// DB-Koordinaten in ASC-Format transformieren

double dAbst = DBL_MAX;
double dZW;				// Zwischenwert
long lKL = pK->ASP();	// Kantenlänge

	// den kürzesten Abstand ermitteln
	for (long i = 0; i < lKL; i++)
	{
		m_pCT->UnScale (pK->SP(i), &OB2.X(), &OB2.Y());
		dZW = m_pCT->CoordTransDistance (&OB1, &OB2);
		if (dZW < dAbst) dAbst = dZW;
	}
	return dAbst;
} // AbstandPunktKanteStuetz


// --------------------------------------------------------------------------------------------
// exakten Abstand zwischen einem einzelnen (Stütz-)Punkt und einer Kante durch Ermittlung der
// kleinsten Entfernung von allen pK-Stützpunkten UND allen (möglichen) Lotpunkten auf die
// pK-Strecken
double AbstandExtension :: AbstandPunktKanteExakt (EPunkt* pP, EKante* pK)
{
	_ASSERTE (pP != NULL);
	_ASSERTE (pK != NULL);

DoublePair OB1 = DoublePair();	// Real-Koordinaten
DoublePair OB2 = DoublePair();

	m_pCT->UnScale (*pP, &OB1.X(), &OB1.Y());	// DB-Koordinaten in ASC-Format transformieren

double dAbst1 = DBL_MAX;	// kleinster Abstand von allen (möglichen) Lotpunkten auf die pK-Strecken bzw.
//double dAbst2 = DBL_MAX;	//  von allen pK-Stützpunkten (ab 05.02.98 nur noch dAbst1)
double dZW;					// Zwischenwert
long lKL = pK->ASP();	// Kantenlänge
EPunkt LPkt;				// Lotpunkt

	// die kürzeste Entfernung (Abstand) ermitteln
	for (long i = 0; i < lKL-1; i++)
	{
		if (LotPunkt (*pP, pK->SP(i), pK->SP(i+1), LPkt))	// Lotpunkt von pP auf Strecke (SP(i), SP(i+1))
		{
			m_pCT->UnScale (LPkt, &OB2.X(), &OB2.Y());
			dZW = m_pCT->CoordTransDistance (&OB1, &OB2);
			if (dZW < dAbst1) dAbst1 = dZW;
		}
		else	// "else" erst ab 05.02.98, bis dahin wurden die 3 nachfolgenden Zeilen IMMER abgearbeitet
		{
			m_pCT->UnScale (pK->SP(i), &OB2.X(), &OB2.Y());
			dZW = m_pCT->CoordTransDistance (&OB1, &OB2);
//			if (dZW < dAbst2) dAbst2 = dZW;
			if (dZW < dAbst1) dAbst1 = dZW;
		}
	}

	// Einbeziehung des letzten pK-Stützpunktes
	m_pCT->UnScale (pK->SP(lKL-1), &OB2.X(), &OB2.Y());
	dZW = m_pCT->CoordTransDistance (&OB1, &OB2);
//	if (dZW < dAbst2) dAbst2 = dZW;
	if (dZW < dAbst1) dAbst1 = dZW;

//	if (dAbst1 < dAbst2) 
		return dAbst1;
//	return dAbst2;

} // AbstandPunktKanteExakt


// --------------------------------------------------------------------------------------------
//	DebugSection-Eintrag aus win.ini lesen
bool AbstandExtension :: _GetDebugOutputFlag (void)
{
ResString Section (ResID (IDS_DEBUGSECTION, pRF), 30);
ResString Entry (ResID (IDS_DEBUGENTRY, pRF), 30);	
char pcBuffer[5] = "";
	
	return  GetProfileString (Section.Addr(), Entry.Addr(), "0", pcBuffer, sizeof (pcBuffer)) 
			&& (atoi (pcBuffer) > 0) ? true : false;
} // _GetDebugOutputFlag


// --------------------------------------------------------------------------------------------
// Reaktion auf Fehlercode iWC
int ErrHandler (int iWC, int iRoutine, ...)
{
va_list vaArgs;		// Liste der unbenannten Argumente

	va_start (vaArgs, iRoutine);

void* pvData = va_arg (vaArgs, void*);	// Makro, um die unbenannten Argumente herauszuholen

	va_end (vaArgs);

ResString Titel (ResID (IDS_LONGCLASSNAME, pRF), 50);
				
	MessageBox (__hWndM, (char*)pvData, Titel.Addr(), MB_ICONEXCLAMATION | MB_OK);

	return iWC;

} // ErrHandler
