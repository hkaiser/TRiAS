// Typ- und Konstantendefinitionen für die ErweiterungsSchnittstelle von TRIAS
// File: XTENSION.H
// @doc
// @module XTENSION.H | Enthält die Definitionen aller Messages von und an <tr>
// die die eigentliche Programmierschnittstelle ausmachen.<nl>Ferner sind alle
// 'C'-Strukturen und Konstanten definiert, die für die Messages benötigt werden.
// @topic Die Programmierschnittstelle von TRiAS(R) | Die Programmier-Schnittstelle 
// von <tr> besteht im wesentlichen aus 
// zwei Typen von Messages. Zum einen welchen, die von Erweiterungen an das 
// Hauptfenster von <tr> geschickt werden um bestimmte Aktionen auszulösen. 
// Die Struktur aller dieser Messages ist identisch. Als wParam wird eine Konstante 
// übergeben, die festlegt, welche Aktion durch <tr> ausgeführt werden soll. 
// Der Inhalt von lParam ist spezifisch für die konkrete Message und ist zumeist ein 
// Pointer auf eine Datenstruktur, welche ihrerseits alle notwendigen Informationen 
// enthält.<nl>Zum anderen sind es Messages von <tr> an eine Erweiterung, die zur 
// richtigen Einbindung der Erweiterung in die Nutzeroberfläche dient <tpc Notifikationen>.

#if !defined(_XTENSION_H)
#define _XTENSION_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <basetsd.h>
#include <pshpack1.h>

///////////////////////////////////////////////////////////////////////////////
// ProjectHandle etc.
#include <DeclareHandles.h>

///////////////////////////////////////////////////////////////////////////////
// Infos über TRiAS

#if _TRiAS_VER < 0x0400
// Name des Hauptmodules 
#undef TRIASMODULE
#undef TRIAS_MODULENAME
#if _TRiAS_VER >= 0x0200
#if defined(_DEBUG)
#define TRIAS_MODULENAME	TEXT("TRIAS32D.EXE")
#else
#define TRIAS_MODULENAME	TEXT("TRIAS32.EXE")
#endif	// _DEBUG
#else	// _TRiAS_VER >= 0x0200
#define TRIAS_MODULENAME	TEXT("TRIAS.EXE")
#endif	// _TRiAS_VER >= 0x0200
#endif	// _TRiAS_VER < 0x0400

// MenuPositionen
#define PROJECT_MENU_POS	0
#define EDIT_MENU_POS		1
#define THEMA_MENU_POS		2
#define OBJCLASS_MENU_POS	3
#define STYLE_MENU_POS		4
#define VIEW_MENU_POS		5
#define EXTRA_MENU_POS		6
#define HELP_MENU_POS		7

// Menupositionen in RechereFenstern
#define OR_EDIT_MENU_POS	0
#define OR_OBJECT_MENU_POS	1
#define OR_STYLE_MENU_POS	2
#define OR_EXTRA_MENU_POS	3

// max. Länge eines Ansichtnamens
#define MAXVIEWNAMESIZE		_MAX_PATH

// Strukturen, die bei der Kommunikation mit der Nutzer-DLL verwendet werden --
#if defined(__cplusplus)
const short DEX_MENUNAMELEN 		= 40;
const short DEX_FIRSTMENUOFFSET 	= 10000;
const short DEX_MENUOFFSETDELTA 	= 110;
#else
#define DEX_MENUNAMELEN		40
#define DEX_FIRSTMENUOFFSET	10000
#define DEX_MENUOFFSETDELTA	110
#endif

///////////////////////////////////////////////////////////////////////////////
// Messages 

// @msg DEX_LOADEXTENSION | Diese Message wird von <tr> einmalig an eine 
// Erweiterung geschickt, wenn diese geladen wird. 
// @comm Diese Message muß von einer Erweiterung behandelt werden.
// Die Erweiterung muß an dieser Stelle initialisiert werden. Außerdem kann
// ein Handle auf die Menu's der Erweiterung, sowie im Hauptmenu und im Menu der
// Objektrecherchefenster anzuzeigende Menutexte zurück übergeben werden. An dieser
// Stelle ist es noch nicht möglich die programmierschnittstelle von <tr> zu 
// nutzen, da die Erweiterung noch nicht vollständig im System installiert ist. 
// Diese Message wird gefolgt von <m DEX_INITEXTENSION>, welche für die vollständige
// Initialisierung der Erweiterung genutzt werden kann.
// <nl>Die Implementation der Standard-Basisklasse <c CTriasExtension> behandelt 
// diese Message.
//
// @parm TRIASLOADEX *	| pTL | lParam enthält einen Pointer auf eine Struktur vom
// Typ <t TRIASLOADEX>, welche weitere Parameter und Felder für Rückkehrwerte enthält.
// @rdesc Liefert einen <t ErrCode> der folgenden Werte:
// @flag EC_OKAY	| Erweiterung wurde erfolgreich geladen
// @flag EC_NOMEMORY	| Hauptspeicher nicht ausreichend
// @flag EC_ILLPARS	| Parameterfehler (Übergebener Parameter ist NULL)
// @xref <c CTriasExtension>, <m DEX_INITEXTENSION>, <t TRIASLOADEX>, <t ErrCode>
const short DEX_LOADEXTENSION 		= 100;

// @msg DEX_UNLOADEXTENSION | Diese Message wird von <tr> einmalig an eine 
// Erweiterung geschickt, wenn diese freigegeben werden soll. 
// @comm Diese Message muß von einer Erweiterung behandelt werden.
// An dieser Stelle muß der gesamte von der Erweiterung angeforderte
// Speicher freigegeben, sowie sonstige Aufräumarbeiten durchgeführt werden.<nl>Die 
// Implementation der Standard-Basisklasse <c CTriasExtension> behandelt diese
// Message.
//
// @rdesc Liefert einen <t BOOL>- Wert:
// @flag true	| Erweiterung wurde erfolgreich entladen
// @flag false	| Es ist ein fehler bei der Freigabe der Erweiterung aufgetreten
// @xref <c CTriasExtension>
const short DEX_UNLOADEXTENSION 	= 101;

// @msg DEX_MENUINIT | Diese Message wird von <tr> an eine Erweiterung verschickt, 
// wenn für einen Menupunkt dieser Erweiterung die Windows-Message <m WM_INITMENUPOPUP>
// empfangen wurde.
// @comm An dieser Stelle können Befehle zur Menuinitialisierung des Menus der
// Erweiterung durchgeführt werden (ENABLE/DISABLE/GRAY etc.).
// <nl>Die Implementation der Standard-Basisklasse <c CTriasExtension> leitet diese
// Message an die Funktion <mf CTriasExtension::MenuInit> weiter.
//
// @rdesc Eine Erweiterung sollte <t true> liefern, wenn diese Message
// bearbeitet wird, ansonsten <t false>.
// @parm HMENU	| hMenu | wParam enthält das Handle des zu behandelnden Popupmenus.
// @parm HWND	| hWnd	| HIWORD(lParam) enthält das Handle des Recherche-Fensters
// in dem das Popupmenu initialisiert werden soll. Ist ein Popupmenu des Hauptfensters
// zu initialisieren, dann ist dieser Parameter NULL.
// @xref <c CTriasExtension>, <mf CTriasExtension::MenuInit>
const short DEX_MENUINIT 		= 102;

// @msg DEX_INITEXTENSION | Diese Message ist die eigentliche Fertigmeldung von 
// <tr> an eine Erweiterung, die ausgelöst wird, wenn die 
// Erweiterung erfolgreich im System installiert ist. 
// @comm An dieser Stelle sollte die gesamte Initialisierung der Erweiterung 
// erfolgen. So können beispielsweise Speicherressourcen angefordert werden oder
// Notifikationsanforderungen an <tr> abgesetzt werden. Alle an 
// dieser Stelle angeforderten Ressourcen bzw. Notifikationen sollten
// spätestens während der Bearbeitung der Meldung <m DEX_UNLOADEXTENSION>
// wieder freigegeben werden.
// <nl>Die Implementation der Standard-Basisklasse <c CTriasExtension> leitet diese
// Message an die Funktion <mf CTriasExtension::InitExtension> weiter.
//
// @parm short | iInitMode | wParam enthält den Mode in dem die Erweiterung
// geladen wird. Er kann folgende Werte annehmen:
// @flag LENoLoad	| Die Erweiterung soll nicht geladen werden
// @flag LEInitOnly	| Die Erweiterung soll lediglich initialisiert werden. Es
// darf kein Nutzerinterface installiert werden (z.B. zusätzliche Menupunkte).
// @flag LEFullLoad	| Die Erweiterung soll vollständig initialisiert werden. 
// Das Nutzerinterface darf installiert werden.
// @xref <c CTriasExtension>, <mf CTriasExtension::InitExtension>, <m DEX_UNLOADEXTENSION>
const short DEX_INITEXTENSION		= 103;

// @msg DEX_ENUMEXTENSIONPROP | Diese Message wird von <tr> an eine Erweiterung 
// geschickt, um Informationen über die von dieser Erweiterung installierten 
// Objekteigenschaften zu erhalten.
// <nl>Die Implementation der Standard-Basisklasse <c CObjectpropertyExtension> 
// bearbeitet diese Message vollständig.
// @parm ENUMOBJPROPDATA * | pEnumObjPropData | lParam enthält einen Pointer auf
// eine Struktur vom Typ <t ENUMOBJPROPDATA>.
// @rdesc Eine Erweiterung sollte <t true> liefern, wenn diese Message
// bearbeitet wird, ansonsten <t false>.
// @xref <c CObjectpropertyExtension>, <t ENUMOBJPROPDATA>
const short DEX_ENUMEXTENSIONPROP	= 104;	// ObjPropMessages

// @msg DEX_INVOKEOBJPROPFUNC | Diese Message wird von <tr> an eine Erweiterung 
// geschickt, um eine von dieser Erweiterung installierte Objekteigenschaft
// für ein vorgegebenes Objekt zu berechnen.
// <nl>Die Implementation der Standard-Basisklasse <c CObjectpropertyExtension> 
// leitet diese Message an die durch die Erweiterung für diese Objekteigenschaft
// installierte Funktion <mf ObjProp::InvokeFunc> weiter, die ihrerseits die 
// geforderte Funktion ausführen muß.
// @parm INVOKEOBJPROPDATA * | pInvokeObjPropData | lParam enthält einen Pointer auf
// eine Struktur vom Typ <t INVOKEOBJPROPDATA>.
// @rdesc Eine Erweiterung sollte <t true> liefern, wenn diese Message
// bearbeitet wird, ansonsten <t false>.
// @xref <c CObjectpropertyExtension>, <t INVOKEOBJPROPDATA>, <c ObjProp>, 
// <mf ObjProp::InvokeFunc> 
const short DEX_INVOKEOBJPROPFUNC	= 105;

const short DEX_MENUITEMINSTALL		= 106;	// MenuItem einhängen
const short DEX_MENUITEMREMOVE		= 107;
const short DEX_TOOLINSTALL		= 108;	// Werkzeug einhängen
const short DEX_TOOLREMOVE		= 109;

const short DEX_SHOWMAINWINDOW		= 110;	// Fenster anzeigen/nicht anzeigen
const short DEX_HIDEMAINWINDOW		= 111;

const short DEX_SERVERISCLOSING		= 112;	// TRIAS wird geschlossen
const short DEX_SERVERCLOSED		= 113;	// TRIAS wurde geschlossen
 
const short DEX_CAPABILITIES 		= 150;
const short DEXCAP_OBJPROPFUNCS		= 1;	// kann ObjPropFuncs
const short DEXCAP_NOTLOADED 		= 2;	// noch nicht geladen
const short DEXCAP_CLASSPROPFUNCS	= 3;	// kann ClassPropFuncs

const short DEX_OBJPROPGETHELPTEXT	= 113;

const short DEX_QUERYMAINWINDOWVISIBLE	= 114;	// Fenster angezeigt
const short DEX_QUITAPP			= 115;	// Trias schließen
const short DEX_QUERYDEFAULTDATAPATH	= 116;	// Setzen/Abfragen des aktuellen StandardProjektPfades
const short DEX_MODDEFAULTDATAPATH	= 117;

const short DEX_GETLASTIDENT		= 118;	// letzter verwendeter Ident bei neuen Objekten
const short DEX_SETLASTIDENT		= 119;

const short DEX_CHANGINGOBJECT		= 120;	// Notifikationen
const short DEX_OBJECTCHANGED		= 121;
const short DEX_QUERYINTERACTIVE	= 122;	// Interactive-Flag abfragen

// Messages der Extension an Diris --------------------------------------------
// allgemeine Anfragen (common Queries) ---------------------------------------
/* ok */const short DEX_QUERYACTIVEPROJECT	= 200;	// aktuelles Projekt
/* ok */const short DEX_QUERYMAINININAME	= 201;	// zentrale INI-Datei 
// 202 belegt
/* ok */const short DEX_QUERYACTIVESIGHT	= 203;	// aktuelle Sicht
/* ok */const short DEX_QUERYACTIVEDQLNAME	= 204;	// aktuellen DQL-ScriptFileNamen

// obsolete - nicht mehr verwenden
/* ok */const short DEX_QUERYACTIVEOBJECT	= 205;	// das selektierte Objekt
/* ok */const short DEX_QUERYCNTACTIVEOBJECTS	= 206;	// Anzahl der selektierten Objekte
/* ok */const short DEX_QUERYALLACTIVEOBJECTS	= 207;	// Alle Selektierten Objekte liefern
/* ok */const short DEX_QUERYCNTRECHERCHEDOBJECTS = 208;	// Anzahl der Recherchierten Objekte
/* ok */const short DEX_QUERYGEODBVERSION	= 209;	// GeoDBVersion anfordern

// Objektbezogene Anfragen (object oriented queries) --------------------------
/* ok */const short DEX_QUERYOBJIDENT		= 210;	// Identifikator eines Objektes
/* ok */const short DEX_QUERYOBJMERKMAL		= 211;	// ein bestimmtes Objektmerkmal
/* ok */const short DEX_QUERYOBJGEOMETRIE	= 212;	// ObjektGeometrie/ObjektListe bei KomplexObjekten
/* ok */const short DEX_QUERYIDENTVISINFO	= 213;	// VisualisierungsInfo 
/* ok */const short DEX_QUERYOBJTYPE		= 214;	// ObjektTyp
/* ok */const short DEX_QUERYOBJCONTAINER	= 215;	// ObjektContainer
/* ok */const short DEX_QUERYKOBJECTRCODE	= 216;	// RelationsCode in KObjekt
/* ok */const short DEX_QUERYOBJCOLOR		= 217;	// ObjektFarbe
/* ok */const short DEX_QUERYOBJSTATISTIK	= 218;	// diverse ObjektEigenschaften
/* intern */const short DEX_QUERYTEXTMERKMAL	= 219;

// Notifications an Diris -----------------------------------------------------
const short DEX_NOTIFYPROJINICHANGED	= 220;	// Projekt-INIDatei geändert
const short DEX_NOTIFYMAININICHANGED	= 221;	// zentrale INI-Datei geändert

// Modifikationsanforderungen an Diris ----------------------------------------
/* ok */const short DEX_MODOBJIDENT		= 230;	// Ident eines Objektes ändern
/* ok */const short DEX_MODIFYMERKMAL		= 231;	// Merkmal an Objekt/Ident/Sicht modifizieren
/* ok */const short DEX_MODIFYOBJGEOMETRIE	= 232;	// Objektgeometrie modifizieren
/* ok */const short DEX_MODIFYIDENTVISINFO	= 233;	// ObjektVisInfo moddifizieren
/* ok */const short DEX_MERGEKOBJECTS		= 234;	// KomplexObjekte zusammenfassen
/* ok */const short DEX_ADDNEWIDENT		= 235;	// Neuen Ident aufnehmen
/* ok */const short DEX_USEDIDENT		= 236;	// testen, ob Ident benutzt ist
/* ok */const short DEX_DELOBJECT		= 237;	// Objekt löschen
const short DEX_USEDIDENTSIGHT		= 238;	// Ident gehört zur Sicht
/* ok */const short DEX_DELETEOBJFROMKOBJECT	= 239;	// Objekt aus KO herauslösen

// Sonstige Befehle an Diris --------------------------------------------------
/* ok */const short DEX_REPAINTALL		= 240;	// gesamten Bildschirm neu zeichnen
/* ok */const short DEX_REPAINTRECT		= 241;	// Rechteck neu zeichnen
/* ok */const short DEX_REBUILDVIEW		= 248;	// Sicht neu generieren

/* ok */const short DEX_DQLQUERYFILE		= 242;	// DQLRecherche aus Datei ausführen
/* ok */const short DEX_DQLQUERYBUFFER		= 243;	// DQLRecherche aus Buffer ausführen
/* ok */const short DEX_DQLQUERYCLIPBOARD	= 244;	// DQLRecherche aus ClipBoard ausführen

/* ok */const short DEX_SELNEWSIGHT		= 245;	// Sicht wechseln
/* ok */const short DEX_SIGHTTOSELECT		= 246;	// Sicht soll gewechselt werden

/* ok */const short DEX_MODIFYVISINFODIALOG	= 247;	// VI über Dialog Einstellen

/* 248 belegt */
/* ok */const short DEX_CREATEOBJEKTINFO	= 249;	// ObjRechFenster aufmachen

// Enumeration-Anforderungen an Diris -----------------------------------------
/* ok */const short DEX_ENUMALLSIGHTS	= 250;	// alle Sichten liefern
/* ok */const short DEX_ENUMSIGHTOBJECTS = 251;	// alle (Einzel-)Objekte einer Sicht
/* ok */const short DEX_ENUMVIEWIDENTS	= 252;	// alle Identifikatoren einer Sicht
/* ok */const short DEX_ENUMMERKMALE	= 253;	// alle Merkmale eines Objektes
/* ok */const short DEX_ENUMSELECTEDOBJECTS = 254; // alle recherchierten Objekte
/* ok */const short DEX_ENUMKOMPLOBJECTS = 255;	// alle Teilobjekte eines Komplexobjektes
/* ok */const short DEX_ENUMIDENTOBJS	= 256;	// alle Objekte mit einem Identifikator
/* ok */const short DEX_RECHERCHEDOBJECTS 	= 257;	// alle Objekte in Recherchefenstern
/* ok */const short DEX_ENUMALLIDENTS	= 258;	// Enumeration aller Identifikatoren der DB
/* ok */const short DEX_ENUMALLMCODES	= 259;	// alle MCodes einer GeoDB

// Rechercheanforderungen/Enumeration -----------------------------------------
/* ok */const short DEX_ENUMTEXTMERKMALRECH	= 290;	// Objekte über TextMerkmal suchen
const short DEX_ENUMRECHGEOMETRIE	= 291;	// Objekte über Geometrie suchen

// Projektbezogenen Befehle ---------------------------------------------------
/* ok */const short DEX_PROJECTOPEN	= 260;	// Projekt eröffnen
const short DEX_OPENPROJECTRO		= 261;	// Projekt $RO eröffnen
/* ok */const short DEX_PROJECTCLOSE	= 262;	// Projekt schließen
/* ok */const short DEX_FLUSHALLMODIFICATIONS = 263;	// aktuellen Zustand speichern
const short DEX_ENUMOBJRECHWNDS		= 264;	// ORFenster enumerieren

// Befehle an den ObjektBaum --------------------------------------------------
/* intern */const short DEX_SETATTRIBUTES	= 270;	// Zeichenattribute setzen
/* intern */const short DEX_RESETATTRIBUTES	= 271;	// Zeichenattribute rücksetzen

/* ok */const short DEX_OBJECTTODELETE		= 272;	// Objekt soll gelöscht werden
/* ok */const short DEX_ENUMIDENTSSELECTED	= 273;	// Enumeration aller Identifikatoren der DB

// PBDVerwaltung --------------------------------------------------------------
/* ok */const short DEX_QUERYACTIVEPBD	= 202;	// aktuellen PBD-Namen liefern
/* ok */const short DEX_QUERYPBDDATA	= 280;	// PBDDaten abfragen
/* ok */const short DEX_MODPBDDATA	= 281;	// PBDDaten modifizieren
/* ok */const short DEX_DELPBDDATA	= 282;	// PBDSatz löschen
/* ok */const short DEX_MODIFYPBDNAME	= 283;	// neuen PBD-Namen setzen
/* ok */const short DEX_QUERYPBDVERSION	= 284;	// VersionsNummer der IDTDB.DBS

/* intern */const short DEX_BEGINPBDTRANSACTION	= 285;	// interne Transaktionsverwaltung
/* intern */const short DEX_BREAKPBDTRANSACTION	= 286;
/* intern */const short DEX_ENDPBDTRANSACTION	= 287;

/* ok */const short DEX_ENUMPBDDATA	= 288;

// SystemMeldungen ------------------------------------------------------------
/* ok */const short DEX_SETERROR		= 300;	// Fehler aufgetreten
/* ok */const short DEX_ERRORMESSAGE		= 301;	// Fehlermeldungen zuleiten/verschicken
/* ok */const short DEX_ERRINSTALL		= 302;	// FehlerBehandlung setzen
/* ok */const short DEX_EXTERRINSTALL		= 303;	// Erweiterte FehlerBehandlung setzen

const short DEX_OBJECTSELECTED		= 310;	// Objekt wurde selektiert
const short DEX_OBJECTUNSELECTED	= 311;	// Objekt wurde deselektiert

const short DEX_SIGHTSELECTED		= 312;	// Sicht wurde aktiviert

// @nfy DEX_DRAWIDENT | Wird verschickt, um zu erfragen, ob in der aktuellen Sicht
// Objekte des gegebenen Identifikators von einer Erweiterung in besonderer Form
// behandelt werden. 
// @parm long | lIdent | lParam enthält den zu behandelnden Identifikator.
// @rdesc Eine Erweiterung kann mit folgenden Werten antworten:
// @flag DT_Normal | Objekte dieses Identifikators sollen normal (von <tr>) gezeichnet
// werden. Die Erweiterung wird diese Objekte nicht beeinflussen.
// @flag DT_HasNewVI | Die Erweiterung wird einzelne oder alle Objekte dieses 
// Identifikators durch die Vorgabe einer neuen Visualisierungsinformation (Farbe, 
// Zeichentyp, Größe etc.) beeinflussen. Die eigentliche Darstellung wird auch für
// die beeinflußten Objekte durch <tr> vorgenommen.
// @flag DT_WillDrawComplete | Die Erweiterung übernimmt vollständig die Darstellung
// einzelner oder aller Objekte dieses Identifikators.
// @comm Diese Notifikation wird für jede Sicht genau einmal für jeden in dieser Sicht
// darzustellenden Identifikator gerufen. Die dabei gesammelte Information wird für
// alle nachfolgenden Darstellungsoperationen in dieser Sicht verwendet.
const short DEX_DRAWIDENT		= 313;		// Identifikator wird gezeichnet
const short DEX_DRAWIDENTEX		= 446;		// Identifikator wird gezeichnet (neu)

#if _TRiAS_VER >= 0x0200
const short DEX_GOTOBJWNDFOCUS		= 314;	// ORFenster-Fokus erhalten
const short DEX_LOSTOBJWNDFOCUS		= 337;	// ORFenster-Fokus verloren
#else	// _TRiAS_VER >= 0x0200
const short DEX_OBJWNDFOCUSCHANGED	= 314;	// ORFenster-FokusWechsel
#endif	// _TRiAS_VER >= 0x0200
const short DEX_OBJWNDCLOSED		= 315;	// Objektfenster geschlossen

// Typen beim Objektzeichnen
const short DT_Normal 		= 0x00;
const short DT_HasNewVI 	= 0x01;
const short DT_WillDrawComplete = 0x02;
const short DT_NoDrawing	= 0x04;
const short DT_DrawingMask 	= 0x07;

const short DT_CustomVisualisation	= 0x10;	// Objektbezogene Visualisierung

// Reaktion einer Erweiterung auf DEX_DRAWOBJECT
const short DO_UnChanged	= 0x0000;		// nichts verändert
const short DO_StyleChanged	= 0x0100;
const short DO_PrimColorChanged = 0x0200;
const short DO_SecColorChanged	= 0x0400;
const short DO_ColorChanged	= 0x0600;
const short DO_SizeChanged	= 0x0800;
const short DO_NameChanged	= 0x1000;
const short DO_PriorityChanged	= 0x2000;
const short DO_OthersChanged	= 0x4000;		// sonstiges 
const short DO_VisInfoChanged	= 0x7F00;
const short DO_Tagged		= short(0x8000);	// Kennzeichen gesetzt

const short DF_Normal		= 0x00;
const short DF_Blinking		= 0x01;		// es wird geblinkt
const short DF_Analyze		= 0x02;
const short DF_Export		= 0x04;		// es wird exportiert
const short DF_ShowHidden	= 0x08;		// ausgeblendete Objekte anzeigen

const short DF_ForceImport	= 0x40;		// auf jeden Fall importieren
const short DF_HSBModel		= 0x80;		// HSB verwenden

// @nfy DEX_DRAWOBJECT | Wird für jedes Objekt verschickt, für dessen Identifikator
// eine Erweiterung einen anderen Wert als <t DT_Normal> geliefert hat. Die 
// betreffende Erweiterung kann während der Bearbeitung dieser Notifikation die 
// für dieses Objekt notwendigen Darstellungsoperationen durchführen (<n DEX_DRAWIDENT> 
// wurde mit <t DT_WillDrawComplete> beantwortet) bzw. die notwendigen Veränderungen
// der Darstellungsattribute vornehmen (<n DEX_DRAWIDENT> wurde mit <t DT_HasNewVI> 
// beantwortet).
// @parm DRAWOBJECT | pDrawObject | lParam enthält einen Pointer auf eine Struktur
// vom Typ <t DRAWOBJECT>.
// @rdesc Eine Erweiterung kann mit folgenden Werten bzw. deren Kombination antworten:
// @flag DO_UnChanged | Die Darstellungattribute für dieses Objekt wurden nicht modifiziert.
// @flag DO_StyleChanged | Der Darstellungstyp dieses Objektes wurde modifiziert.
// @flag DO_PrimColorChanged | Der primäre Farbwert dieses Objektes wurde modifiziert.
// @flag DO_SecColorChanged | Der sekundäre Farbwert dieses Objektes wurde modifiziert.
// @flag DO_SizeChanged | Die Darstellunggröße dieses Objektes wurde modifiziert.
// @flag DO_NameChanged | Der Darstellungsname dieses Objektes wurde modifiziert.
// @flag DO_OthersChanged | Es wurden andere Darstellungsattribute dieses Objektes modifiziert
// (z.B. Schriftattribute wie kursiv, Rahmen etc.).
// @flag DT_NoDrawing | Die Darstellung des Objektes wurde vollständig durch die 
// Erweiterung erledigt. Dieses Flag kann verwendet werden, wenn ein Objekt nicht
// dargestellt werden soll. Ist dieses Flag gesetzt, wird das betreffende Objekt von <tr> 
// nicht dargestellt.
// @comm Die Darstellungs-Priorität eines Objektes läßt sich nicht verändern.
// @xref <n DEX_DRAWIDENT>, <t DRAWOBJECT>, <t DT_Normal>, <t DT_HasNewVI>, <t DT_WillDrawComplete>
const short DEX_DRAWOBJECT		= 316;	// Objekt wird gezeichnet
const short DEX_OBJECTACTIVATED		= 317;	// Objekt aktivieren

const short DEX_PAINTTOPLAYER		= 318;	// TopLayer zeichnen

const short DEX_PROJECTCLOSEEX		= 319;	// bestimmte GeoDB schließen
const short DEX_QUERYOPENPROJECTS	= 320;	// Anzahl der geöffneten Projekte liefern

const short DEX_QUERYVIEWDESCRIPTION	= 321;	// SichtBeschreibung abfragen
const short DEX_MODVIEWDESCRIPTION	= 322;	// SichtBeschreibung setzen

const short DEX_OBJECTDEACTIVATED	= 323;	// Objekt wurde deaktiviert
const short DEX_CANCELMODE		= 324;	// Blinken abschalten/erlauben

const short DEX_QUERYPROJECTCONT	= 325;	// GeoDBContainer liefern
const short DEX_QUERYOBJECTNAME		= 326;	// Objektnamen abfragen
const short DEX_SETOBJECTNAME		= 327;	// ObjektNamen setzen/löschen

const short DEX_DIAGNOSTICSENABLE	= 328;	// Diagnostics ein-/ausschalten

const short DEX_ENUMMERKMALEEX		= 329;	// Merkmale enumerieren mit zusätzlichen Optionen
const short DEX_ENUMMERKMALEIDENTEX	= 330;
const short DEX_ENUMMERKMALESICHTEX	= 331;

const short DEX_ENUMIDENTOBJSEX		= 332;	// Objekte nach Ident/OTyp enumerieren

const short DEX_QUERYUNKNOWNIDENT	= 333;	// Identifikator für unbekannte ObjektKlasse besorgen
const short DEX_FINDOBJFROMNAME		= 334;	// Objektnummer über Objektnamen finden
const short DEX_QUERYOBJNAMEMCODE	= 335;	// Liefert Merkmalscode des Objektnamens für Ident.
const short DEX_QUERYUNIQUEIDENTMCODE	= 336;	// Liefert MCode für UniqueIdents.
//337 belegt

const short DEX_HEADERREREAD		= 338;	// Header neu einlesen

const short DEX_FINDIDENTFROMNAME	= 339;	// Ident über KlassenNamen suchen
const short DEX_DELETEIDENT		= 340;	// Alle Objekte eines Idents löschen
const short DEX_VIEWCREATE		= 341;	// Leere Sicht erzeugen
const short DEX_DELETEIDENTFROMVIEW	= 342;	// Ident/ObjektTyp aus Sicht löschen
const short DEX_VIEWRENAME		= 343;	// Sicht umbenennen
const short DEX_HASVIEWIDENT		= 344;	// gehört Ident/ObjektTyp zur Sicht ?
const short DEX_HASVIEWOBJECT		= 345;	// gehört Objekt zur Sicht ?
const short DEX_IDENTADDTOVIEW		= 346;	// Ident zu Sicht hinzufügen (mit defaultfarben)
const short DEX_VIEWCREATEOPT		= 347;	// Leere Sicht erzeugen, wenn noch nicht da
const short DEX_HASPROJECTVIEW		= 348;	// Testet, ob Sicht existiert

const short DEX_IDENTTODELETE		= 349;	// Ident soll gelöscht werden
const short DEX_VIEWCREATED		= 350;	// Sicht wurde erzeugt

const short DEX_QUERYADMINMODE		= 351;	// AdminModeFlag abfragen
const short DEX_SETADMINMODE		= 352;	// AdminModeFlag setzen

#if _TRiAS_VER >= 0x0200
const short DEX_ADDUNDOREDOITEM		= 353;	// LPUNDOREDO registrieren
const short DEX_UNDOLEVELBEGIN		= 354;	// komplexes Undo starten
const short DEX_UNDOLEVELEND		= 355;	// komplexes Undo beenden
const short DEX_UNDOLEVELCANCEL		= 356;	// komplexes Undo abbrechen
#endif // _TRiAS_VER >= 0x0200

const short DEX_INITIALIZEDSERVER	= 357;	// Server fertig initialisiert
const short DEX_HANDLEEMBEDDING		= 358;	// /Embedding behandeln ?
const short DEX_HANDLEAUTOMATION	= 359;	// /Automation behandeln ?

const short DEX_RECHOBJECTSTATUS	= 360;	// liefert ObjektStatus in ORFenster
const short DEX_DELOBJECTEX		= 361;	// Objekt löschen mit Undo
const short DEX_GETSELECTEDTYPES	= 362;	// liefert selektierte Objekttypen aus ORFenster

const short DEX_RCTOOC			= 363;	// RealKoordinaten zu DBKoords
const short DEX_OCTORC			= 364;	// DBKoords zu RealKoordinaten

const short DEX_ISOBJWINDOW		= 365;	// Test ob ORFenster
const short DEX_OBJECTREPAINT		= 366;	// Objekt draufmalen

const short DEX_ENUMIDENTVIEWSEX	= 367;	// alle Sichten, in denen Ident vertreten ist

const short DEX_MODIFYINGIDENT		= 368;	// Notification: Ident soll modifiziert werden
const short DEX_IDENTWASMODIFIED	= 369;	// Notification: Ident wurde modifiziert

const short DEX_ACTIVATEALLORWNDS	= 370;	// alle selektierten Objekte neu selektieren
const short DEX_ENUMALLMCODESEX		= 371;	// alle MCodes einer GeoDB mit Optionen
const short DEX_FINDFEATUREFROMNAME	= 372;	// MCode über MerkmalsKurztext suchen

const short DEX_COORDFORMATWASCHANGED	= 373;	// Coord-Format wurde geändert

const short DEX_SETGEODBDIRTY		= 374;	// GeoDB wurd emodifiziert

const short DEX_BEGINDIALOG		= 375;	// modaler Dialog wurde erzeugt
const short DEX_ENDDIALOG		= 376;	// modaler Dialog wurde zerlegt

const short DEX_ENUMALLPROJECTS		= 377;	// alle geöffneten Projekte enumerieren
const short DEX_PROJECTHANDLEFROMNAME	= 378;	// liefert für Project das HPROJECT-Handle
const short DEX_PROJECTMAKEACTIVE	= 379;	// macht das gegebene projekt zum aktiven

const short DEX_ENUMSELECTEDOBJECTSEX	= 380;	// alle recherchierten Objekte mit Objekttyp
const short DEX_QUERYIDENTOBJTYPESACTVIEW = 381;	// ObjektTypen für Ident in dieser Sicht liefern

const short DEX_N_SCROLLING_HORZ		= 382;	// es soll horizontal gescrollt werden
const short DEX_N_SCROLLING_VERT		= 383;	// es soll vertikal gescrollt werden

const short DEX_ATTACHPRETRANSLATEMSGPROC = 384;
const short DEX_ATTACHIDLEPROC			= 385;

const short DEX_CAPTIONREREAD			= 386;	// Caption neu generieren
const short DEX_QUERYACTIVEVIEWWINDOW	= 387;	// Liefert HWND des aktuellen Projektes

const short DEX_N_VIEWCREATED			= 388;	// View ist jetzt sichtbar
const short DEX_MODOBJIDENTEX			= 389;	// Ident eines Objektes ändern (mit Undo)
const short DEX_QUERYOBJECTPROPS		= 390;	// Liefert Interface der OPropListe

const short DEX_GETGEODBDIRTY			= 391;	// Abfrage, ob GeoDB gespeichert werden muß
const short DEX_QUERYCANUNDO			= 392;	// Undo ist möglich
const short DEX_QUERYCANREDO			= 393;	// Redo ist möglicn

const short DEX_MODACTVIEWCONTAINER		= 394;	// SichtContainer setzen
const short DEX_QUERYACTVIEWCONTAINER	= 395;	// SichtCOntainer abfragen

const short DEX_N_EXTENSIONSLOADED		= 396;	// Alle Erweiterungen fertig geladen
const short DEX_FINDIDENTFROMNAMECI		= 397;	// Ident über KlassenNamen suchen (case insensitive)
const short DEX_FINDFEATUREFROMNAMECI	= 398;	// MCode über MerkmalsKurztext suchen (case insensitive)
const short DEX_SETSTRINGMESSAGE		= 399;	// Text in Statusbar setzen

// Messages zur OLE-Unterstützung ---------------------------------------------
/* ok */const short DEX_QUERYPROJECTSTORAGE	= 400;
/* ok */const short DEX_QUERYACTIVEPALETTE	= 401;
const short DEX_N_SAVESAMESTORAGE		= 402;		// für IPersistStorage
const short DEX_N_SAVEOTHERSTORAGE		= 403;
const short DEX_N_SAVECOMPLETED			= 404;
const short DEX_N_HANDSOFFSTORAGE		= 405;
const short DEX_N_TIPOFTHEDAY			= 406;

const short DEX_N_PRINTINGPROJECT		= 407;
const short DEX_N_PROJECTPRINTED		= 408;
const short DEX_N_SCALINGCHANGED		= 409;
const short DEX_SETACTSCALING			= 410;
const short DEX_N_PROJECTTOCLOSE		= 411;
const short DEX_N_SHOWTOOLTIPS			= 412;
const short DEX_CANCTFCONFIG			= 413;
const short DEX_KICKIDLELOOP			= 414;		// IdleLoop rufen
const short DEX_ACTIVEPROJECTTEST		= 415;		// DEX_QUERYACTIVEPROJECT, aber nur testen
const short DEX_ERASEVIEWCANVAS			= 416;		// View löschen

const short DEX_QUERYOBJECTCOUNT		= 417;		// Statistikwerte abfragen
const short DEX_QUERYCLASSCOUNT			= 418;
const short DEX_QUERYVIEWCOUNT			= 419;
const short DEX_HOLDZOOMSET				= 420;		// HoldZoomStatus
const short DEX_QUERYHOLDZOOM			= 421;
const short DEX_QUERYCLIPOBJECT			= 422;
const short DEX_CLIPOBJECTSET			= 423;
const short DEX_QUERYACTIVEPROJECTHANDLE	= 424;
const short DEX_PROJECTNAMEFROMHANDLE	= 425;
const short DEX_SHOWOBJPROP				= 426;
const short DEX_PROJECTOPENEX			= 427;
const short DEX_PUTTEXTOBJECTTEXT		= 428;
const short DEX_N_RENAMINGFILE			= 429;
const short DEX_N_FILERENAMED			= 430;
const short DEX_IDENTFROMCLASS			= 431;
const short DEX_CLASSFROMIDENT			= 432;
const short DEX_MODOBJCLASSCODE			= 433;
const short DEX_GETSHOWOBJPROP			= 434;
const short DEX_REPLACEOBJECTINLIST		= 435;
const short DEX_SETTEXT					= 436;
const short DEX_N_ADDEDOBJECTPROPERTY	= 437;
const short DEX_N_ADDEDCLASSPROPERTY	= 438;
const short DEX_N_REMOVEDOBJECTPROPERTY	= 439;
const short DEX_N_REMOVEDCLASSPROPERTY	= 440;
const short DEX_QUERYTRIASVERSION		= 441;
const short DEX_QUERYTRIASCAPTION		= 442;
const short DEX_MODIFYTRIASCAPTION		= 443;
const short DEX_SETSTRINGMESSAGENOKICKIDLE		= 444;	// Text in Statusbar setzen
const short DEX_N_SHOWPROJECTWIZARD		= 445;
// 446 belegt (DEX_DRAWIDENTEX)
const short DEX_N_SCRIPTINGENGINEACTIVE	= 447;
const short DEX_N_UIREADY				= 448;
const short DEX_N_VIEWDELETED			= 449;
const short DEX_QUERYIDENTPRIORITY		= 450;
const short DEX_MODIFYIDENTPRIORITY		= 451;
const short DEX_QUERYACTOBJPROP			= 452;
const short DEX_QUERYOVERVIEWACTIVE		= 453;
const short DEX_QUERYCOMPATIBILITYMODE	= 454;
const short DEX_N_ENABLECOOLLOOK		= 455;
const short DEX_N_OBJECTSPLITTED		= 456;		// #WM970814
const short DEX_N_TODELETEOBJECT		= 457;		// Objekt wird jetzt (wirklich) gelöscht
const short DEX_N_OBJECTCREATED_EDIT	= 458;		// #WM970822
const short DEX_N_OBJECTCREATED			= 458;		// #WM970822
const short DEX_OVERVIEWSAVE			= 459;
const short DEX_QUERYIDENTOBJECTCOUNT	= 460;
const short DEX_QUERYOBJECTGUID			= 461;
const short DEX_FINDOBJECTGUID			= 462;
const short DEX_SETOBJECTGUID			= 463;
const short DEX_SETACTIVEORWINDOW		= 464;

const short DEX_QUERYSTARTVIEW			= 465;		// AnfangsAnsicht setzen/abfragen
const short DEX_MODIFYSTARTVIEW			= 466;

const short DEX_ADDOBJECTTOLISTEX		= 467;
const short DEX_REMOVEOBJECTFROMLISTEX	= 468;
const short DEX_REPLACEOBJECTINLISTEX	= 469;
const short DEX_QUERYPROJECTDESC		= 470;

const short DEX_N_REREADOBJPROPS		= 471;
const short DEX_QUERYMRUITEM			= 472;
const short DEX_DELETEMRUITEM			= 473;
const short DEX_ADDMRUITEM				= 474;

const short DEX_QUERYACTIVEPROJECTPTR	= 475;

const short DEX_ENUMEXTENSIONS			= 476;
const short DEX_QUERYEXTENSIONINFO		= 477;
const short DEX_QUERYEXTENSIONPTR		= 478;

const short DEX_N_MODIFYMERKMAL			= 479;	// Merkmal an Objekt modifiziert
const short DEX_QUERYPREVENTREPAINT		= 480;
const short DEX_PREVENTREPAINT			= 481;

const short DEX_QUERYACTASPECTRATIO		= 482;	// Isotropiekoeffizient

const short DEX_QUERYIDENTSCALEDATA		= 483;
const short DEX_MODIFYIDENTSCALEDATA	= 484;
const short DEX_TESTIDENTSCALETOPAINT	= 485;

const short DEX_QUERYOLDUNIQUEIDENTMCODE	= 486;	// Liefert MCode für ursprünglichen UniqueIdents.

const short DEX_SETHAVETOINITOPFS		= 487;
const short DEX_QUERYMUSTINITOPFS		= 488;

const short DEX_QUERYTRIASVERSIONLONG	= 489;

const short DEX_ENUMMERKMALECLASSEX		= 490;		// alle Merkmale der Objekte einer Objektklasse

const short DEX_N_HANDLEMENU			= 491;		// Rundruf zur Menubehandlungsabfrage
const short DEX_N_MENUCHANGED			= 492;		// Menu wurde modifiziert
const short DEX_N_CHANGINGMENU			= 493;		// Menu soll modifiziert werden

const short DEX_LOADEXTENSION2 			= 494;		// Erweiterung laden/entladen
const short DEX_UNLOADEXTENSION2 		= 495;

const short DEX_QUERYNAMEDVIEWPROPERTY 	= 496;		// ViewEigenschaften über globalen Bezeichner bearbeiten
const short DEX_MODNAMEDVIEWPROPERTY	= 497;

const short DEX_QUERYOBJECTPROJECT		= 498;
const short DEX_QUERYOBJECTSPROJECT		= 499;

// other stuff
/* ok */const short DEX_MODIFYHEADER		= 500;	// GeoDBHeader modifizieren
/* ok */const short DEX_READHEADER 		= 501;	// GeoDBHeader lesen
/* ok */const short DEX_DELETEHEADER		= 502;	// Eintrag in GeoDBHeader löschen
/* ok */const short DEX_GETUNIQUEICODE		= 503;	// UniqueICode liefern
/* ok */const short DEX_GETUNIQUEMCODE		= 504;	// UniqueMCode liefern
/* ok */const short DEX_GETUNIQUERCODE		= 505;	// UniqueRCode liefern

/* ok */const short DEX_QUERYACTSCALING		= 506;	// aktuellen Darstellungskoeffizienten liefern
/* ok */const short DEX_GETUNIQUETEMPON		= 507;	// UniqueTempObjNr liefern

/* ok */const short DEX_QUERYACTIVEORWINDOW	= 508;	// aktives ORFensterHandle liefern
/* ok */const short DEX_CHANGEACTIVECOLOR	= 509;	// SelektionsFarbe eines Objektes ändern

const short DEX_USEDMCODE		= 510;	// MCode verwendet
const short DEX_USEDRCODE		= 511;	// RCode verwendet

const short DEX_QUERYOBJSTATUS		= 512;	// ObjektStatus liefern
// gelieferter ObjektStatus
#define OSUnknown	-1
#define OSNormal	 0
#define OSTemp		 1
#define OSInvalid	 2
#define OSModified	 4

/* ok */const short DEX_QUERYACTSIGHTCONTAINER 	= 513;	// aktuellen Ausschnitt abfragen
/* ok */const short DEX_SETACTSIGHTCONTAINER	= 514;	// Ausschnitt einstellen

/* ok */const short DEX_TXICHANGED		= 515;	// PBD wurde modifiziert
/* ok */const short DEX_TXMCHANGED		= 516;	// PBD wurde modifiziert
/* ok */const short DEX_TXRCHANGED		= 517;	// PBD wurde modifiziert

/* ok */const short DEX_QUERYACTMASSTAB		= 518;	// Bezugs-/Darstellungmaástab
/* ok */const short DEX_QUERYDRAWINGSTATUS	= 519;	// Abfrage, ob derzeit gezeichnet wird
/* ok */const short DEX_SETNEWPALETTE		= 520;	// Palette zur Erweiterung rumreichen
/* ok */const short DEX_ERASEBKGND		= 521;	// Hintergrund zeichnen

/* ok */const short DEX_DCTOOC			= 522;	// DCtoOC
/* ok */const short DEX_OCTODC			= 523;	// OCtoDC

/* ok */const short DEX_QUERYACTIVETOOL		= 524;
/* ok */const short DEX_SETACTIVETOOL		= 525;

/* ok */const short DEX_FINDOBJECT		= 526;	// --> struct FINDOBJECT

/* ok */const short DEX_QUERYRECHOBJECT		= 527;	// --> struct RECHOBJECT
/* ok */const short DEX_ISCLOSEDPROJECT		= 528;	// Notifikation

/* ok */const short DEX_QUERYACTIVEUSER		= 529;	// aktuellen NutzerNamen holen
/* ok */const short DEX_QUERYACTIVESELECTION	= 530;	// evtl. SelktionsBereich liefern

/* ok */const short DEX_ENUMMERKMALEIDENT	= 531;	// alle Merkmale eines Idents enumerieren
/* ok */const short DEX_ENUMMERKMALESICHT	= 532;	// alle Merkmale einer Sicht enumerieren

// Relationen, Relationen, Relationen -----------------------------------------
/* ok */const short DEX_ENUMRELATIONS		= 533;	// alle RelationsCodes einer GeoDB
/* ok */const short DEX_ENUMRELATIONOBJS	= 534;	// alle ONrs, mit einer Relation zu einem Obj
/* ok */const short DEX_MODRELATION		= 535;	// Relation aufbauen/modifizieren
/* ok */const short DEX_DELRELATION		= 536;	// Relation löschen

/* ok */const short DEX_QUERYIDENTBASE		= 537;	// Zahlenbasis der Idents holen
/* ok */const short DEX_QUERYIDENTOBJTYPES	= 538;	// Objekttypen eines Idents feststellen
/* ok */const short DEX_LOADEXTENSIONEX 	= 539;
/* ok */const short DEX_UNLOADEXTENSIONEX 	= 540;

/* ok */const short DEX_QUERYROMODE		= 541;	// ROMode holen
/* ok */const short DEX_REMOVEORWND		= 542;	// Alle ORWnds löschen

// Verwalten der Objektliste in ORFenstern
/* ok */const short DEX_ADDOBJECTTOLIST		= 543;
/* ok */const short DEX_REMOVEOBJECTFROMLIST 	= 544;

// Anlegen einer neuen GeoDB/IdentsDB
/* ok */const short DEX_CREATENEWGEODB		= 545;
/* ok */const short DEX_CREATENEWIDENTSDB	= 546;

const short DEX_QUERYISPRINTING			= 547;

/* ok */const short DEX_ENUMHEADER		= 548;

/* ok */const short DEX_RESCALE			= 549;	// Notification: Scaling changed
/* ok */const short DEX_REREADIDENTS		= 550;
/* ok */const short DEX_REREADCONTAINER		= 551;

/* ok */const short DEX_REREADSIGHTS		= 552;	// Sichten neu lesen
/* ok */const short DEX_DELETEVIEW		= 553;	// Sicht löschen

/* ok */const short DEX_DCTOOCEX		= 554;	// DCtoOC ohne kippen
/* ok */const short DEX_OCTODCEX		= 555;	// OCtoDC ohne kippen

/* ok */const short DEX_RENDERGEODB		= 556;	// in hDC ausgeben
/* ok */const short DEX_QUERYEXPOSEDOC		= 557;	// zu zeichnender Bereich (GeoDB)
/* ok */const short DEX_QUERYEXPOSEDAREA	= 558;	// zu zeichnender Bereich (hDC)

/* ok */const short DEX_SIGHTDELETED		= 559;	// Sicht ist gelöscht

/* ok */const short DEX_ENUMVIEWIDENTSEX	= 560;	// Idents mit OTyp enumerieren
/* ok */const short DEX_ENUMALLIDENTSEX		= 561;

/* ok */const short DEX_QUERYMCODEBASE		= 562;	// Zahlenbasis der Idents holen

// LegendenVerwaltung ---------------------------------------------------------
/* ok */const short DEX_SAVELEGEND		= 563;	// Legende speichern
/* ok */const short DEX_RESETLEGEND		= 564;	// Legende rücksetzen
/* ok */const short DEX_REFRESHLEGEND		= 565;	// Legende neu generieren
/* ok */const short DEX_ADDOBJECTTOLEGEND	= 566;	// Objekt zu Legende hinzufügen
/* ok */const short DEX_REPAINTLEGEND 		= 567;	// Legende neu zeichnen
const short DEX_QUERYLEGENDACTIVE		= 572;	// Ist Legende angezeigt ?

/* ok */const short DEX_GETTEXTOBJECTTEXT	= 568;	// Text von Textobjekt holen
/* ok */const short DEX_OBJECTISVISIBLE		= 569;	// Objekt beim letzten mal gezeichnet ?

/* ok */const short DEX_ENUMIDENTSSELECTEDEX	= 570;	// Enumeration aller Identifikatoren des ORFensters
/* ok */const short DEX_ENUMTOPRELATIONS	= 571;	// Enumeration topologischer Relationen
// 572 belegt

const short DEX_MODIFYSHOWNCOORDS			= 573;	// anzuzeigende Koordinaten durchrufen
const short DEX_QUERYDATASOURCENAME			= 574;	// Namen der Connection liefern

const short DEX_QUERYDATASOURCECOUNT		= 575;	// Anzahl der Connections liefern
#define QDCAllOpen			0x00
#define QDCReadOnly			0x01
#define QDCWriteAble		0x02
#define QDCCountQueryDefs	0x04

const short DEX_DEFINENEWOBJECTS			= 576;	// Beschreibungsdaten für Objects definieren
const short DEX_ENUMPROJECTSFORCLASS		= 577;	// Connections/Projekt mit einem OKS enumerieren
const short DEX_GETHANDLEFROMMCODE			= 578;	// Handle über MCode erfragen (for compatibility)
const short DEX_QUERYFEATUREPROJECT			= 579;	// Datenquellenhandle für eine Objekteigenschaft liefern (wenn möglich)
const short DEX_QUERYTRIASDATASOURCE		= 580;	// Testet, ob Datenquelle eine TRiAS-GeoDB ist
const short DEX_QUERYDATASOURCEOPEN			= 581;	// Testet, ob Datenquelle derzeit geöffnet ist
const short DEX_QUERYROMODEIDENT			= 582;	// Testet, ob Objektklasse (Tabelle) beschreibbar ist
const short DEX_QUERYROMODEMCODE			= 583;	// Testet, ob Objekteigenschaft (nicht deren Wert!) beschreibbar ist
const short DEX_QUERYTABLENAME				= 584;	// Liefert evtl. Tabellennamen
const short DEX_QUERYOBJGUIDMCODE			= 585;	// Liefert MCode (Handle) für ObjektGuid für Ident
const short DEX_PROJECTHANDLEFROMSHORTNAME	= 586;	// HPROJECT von ShortName liefern
const short DEX_ENUMALLPROJECTHANDLES		= 587;	// HPROJECT's aller Datenquellen enumerieren
const short DEX_GETMCODEFROMHANDLE			= 588;	// Liefert MCode füt gegebene Objekteigenschaft (HFEATURE)
const short DEX_QUERYCONTEXTPROJECT			= 589;	// aktuellen hPr-Kontext dieser Message abfragen
const short DEX_MAPORCREATEHANDLEFROMMCODE	= 590;	// MCode zu Handle konvertieren
const short DEX_UPDATESTATUSBAR				= 591;	// StatusBar aktualisieren
const short DEX_MODIFYROMODEIDENT			= 592;	// Setzt, ob Objektklasse (Tabelle) beschreibbar ist
const short DEX_MODIFYROMODEMCODE			= 593;	// Setzt, ob Objekteigenschaft (nicht deren Wert!) beschreibbar ist
const short DEX_QUERYSCHEMAUPDATABLE		= 594;	// Fragt, ob ein DB-Schema modifizierbar ist

const short DEX_QUERYGDODATASOURCE			= 595;	// Fragt, ob eine Datenquelle aus GDO kommt

const short DEX_DELETEOBJECTUNDORECT		= 596;	// Objekt löschen mit ausführlichen Parametern

// #HK000301
const short DEX_ADDOBJECT2CLASS				= 597;	// Objekt zu Zuordnungsobjektklasse hinzufügen
const short DEX_DELETEOBJECTFROMCLASS		= 598;	// Objekt aus Zuordnungsobjektklasse herauslösen
const short DEX_OBJECTISINCLASS				= 599;	// Zugehörigkeit eines Objektes zu Zuordnungsobjektklasse feststellen
const short DEX_ENUMCLASSESFROMOBJECT		= 600;	// alle (Zuordnungs-)Objektklassen enumerieren, zu denen ein Objekt gehört

// #HK000313
const short DEX_UNLOADOBJECTFROMMEMORY		= 601;	// gegebenes Objekt aus Speicher entladen
const short DEX_QUERYNATIVEOBJECT			= 602;	// zu Pseudoobjekt passendes 'native' Objekt liefern

// #HK00408
const short DEX_CHANGEIMPORTMODE			= 603;	// TRiAS in/aus Importmode schalten

// #HK00412
const short DEX_CHANGENOTIFICATIONMODE		= 604;	// Notifikationen ein/ausschalten
const short DEX_MRUMENUMODE					= 605;	// MRU Menu anzeigen/nicht anzeigen

// #AD000425
const short DEX_OLEUPDATECLIENT				= 606;	// Aktualisierung des Client wurde angefordert
const short DEX_OLERETURN					= 607;	// Schließen und zurück zu Client wurde angefordert

// #HK000526
const short DEX_RELATEDDATASOURCENAME		= 608;	// liefert Ursprundsdatenquelle einer Ansicht

// #HK000705
const short DEX_QUERYFEATUREIDENT			= 609;	// liefert Ident zu dem MCode gehört

// #HK000713
const short DEX_UPDATEPRINTERSELECTION		= 610;	// Druckerdaten neu einlesen (FakeMFC)
const short DEX_SHOWPRINTLAYOUTDIALOG		= 611;	// DruckLayout-Dialog anzeigen
const short DEX_PREVIEWPRINT				= 612;	// Druckvorschau rendern
const short DEX_ENDPREVIEWPRINT				= 613;	// Druckvorschau beenden

// #HK000807
const short DEX_SHOWSTARTUPDIALOG			= 614;	// StartupDialog anzeigen (FakeMFC)

// #HK001022
const short DEX_CLONEOBJECT					= 615;	// Objekt doppeln (evtl. in andere Datenquelle)

// #HK001030
const short DEX_TOGGLEROLLUPSTATUS			= 616;	// ORWnd zusammenfalten/ausklappen
const short DEX_QUERYROLLUPSTATUS			= 617;	// ORWnd Faltstatus abfragen

// #HK001107
const short DEX_N_MODIFYMERKMALSET			= 618;	// FeatureSet eines Idents wurde modifiziert

// #HK001114
const short DEX_VERIFYLICLEVEL				= 619;	// LizensierungsLevel abgleichen
const short DEX_VERIFYLICOPTION				= 620;
const short DEX_SHOWDENYLICDLG				= 621;	// nur Dialog anzeigen
/*622 benutzt!*/
const short DEX_QUERYTEXTFEATURE			= 623;	// FeatureHandle für TextobjektText abfragen

const short DEX_N_HIDEORSHOWPROJECTWINDOW	= 624;	// Projektfenster angezeigt/ausgeblendet

// #HK010306
const short DEX_ZOOMIN2OBJECT				= 625;	// Objekt zeigen
const short DEX_QUERYOBJECTDESCSTRING		= 626;	// aktuellen Objektbeschreibungs-String liefern (wie im Recherchefenster)

// #HK010307
const short DEX_N_COPYVISINFO				= 627;	// Darstellungsparameter übernehmen
const short DEX_REFRESHENTRY				= 628;	// Objekteintrag eines/aller ORFenster neu einlesen

// #HK010315
const short WM_QUERYPROJECTBARACTIVE		= 629;	// ProjectBar ist angezeigt
const short WM_QUERYOVERVIEWBARACTIVE		= 630;	// OverviewBar ist angezeigt

// #HK010922
const short WM_QUERYMAYOPENLEGEND			= 631;	// Legende darf angezeigt werden
const short WM_QUERYMAYOPENOVERVIEW			= 632;	// Gesamtübersicht darf angezeigt werden

// #HK020306
const short DEX_QUERYOBJCONTAINEREX			= 633;	// ObjektContainer mit Koordinatensystem

// #HK020413
const short DEX_SHOWOBJPROPEX				= 634;	// anzuzeigende Objekteiegenschaft sichtbezogen setzen
const short DEX_QUERYOBJPROPEX				= 635;	// anzuzeigende Objekteiegenschaft sichtbezogen abfragen

// #HK020415
const short DEX_QUERYLIMITSEARCHES			= 636;	// Recherchen auf aktuellen Bildausschnitt begrenzen
const short DEX_SETLIMITSEARCHES			= 637;
const short DEX_QUERYWINDOWASDBCONTAINER	= 638;	// Liefert Fensterecken als DBKoords
const short DEX_QUERYIGNORESEARCHOPTIONS	= 639;	// Recherche-Einschränkungen (objektklassenbezogen) ignorieren
const short DEX_SETIGNORESEARCHOPTIONS		= 640;

// #HK020531
const short WM_QUERYSABiSBARACTIVE			= 641;

// #HK020628
const short WM_QUERYGENERICBARACTIVE		= 642;

// #HK020925
const short WM_QUERYMARKCOLOR				= 643;	// Blinkfarbe vom ORFenster abfragen
const short WM_CHANGEMARKCOLOR				= 644;	// Blinkfarbe für ORFenster setzen

// #HK020926
const short WM_QUERYDROPSOURCEORWND			= 645;	// liefert QuellORWnd des D&D

// #HK021209
const short DEX_QUERYOBJECTPTR				= 646;	// liefert ITRiASObject zu HOBJECT
const short DEX_QUERYOBJECTSPTR				= 647;	// liefert ITRiASObjects zu HOBJECTS
const short DEX_QUERYFEATUREPTR				= 648;	// liefert ITRiASFeature zu HFEATURE

// #HK021217
const short DEX_N_ADDINGOBJECT				= 649;	// Objekt soll hinzugefügt werden (Abfrage)
const short DEX_N_OBJECTTOADD				= 650;	// Objekt wird hinzugefügt werden (Mitteilung)
const short DEX_N_OBJECTADDED				= 651;	// Objekt wurde hinzugefügt

const short DEX_CREATECONNECTIONFILTER		= 652;	// Connectionfilter
const short DEX_DELETECONNECTIONFILTER		= 653;
const short DEX_ENUMCONNECTIONFILTERS		= 654;	// Enumeration aller Connectionfilter (ENUMNOKEY)
const short DEX_ATTACHCONNECTIONFILTER		= 655;
const short DEX_DETACHCONNECTIONFILTER		= 656;
const short DEX_QUERYATTACHEDCONNECTIONFILTER		= 657;

// #HK021219
const short DEX_CREATECONNECTIONFILTER_DLG	= 658;	// Dialog zum Erzeugen eines Connectionfilters anzeigen

const short DEX_QUERYWINDOWASCONTAINER		= 659;	// Liefert Fensterecken als Koords
const short DEX_QUERYACTIVESELECTIONEX		= 660;	// Liefert Selektion als Koords

// #HK030107
const short DEX_SHOWCONNECTFILTERS			= 661;	// ConnectFilter anzeigen
const short DEX_CONNECTFILTERSSHOWN			= 662;	// ConnectFilter angezeigt

// #HK030113
const short DEX_N_CLOSINGOBJWND				= 663;
const short DEX_N_OBJWNDTOCLOSE				= 664;

// #HK030117
const short DEX_QUERYCONNECTIONFILTER		= 665;	// Connectfilter-Params abfragen

// #HK041112
const short DEX_EXECUTECOMMANDSEQUENCE      = 666;  // Ladbaren befehl ausführen

// VisualisierungsTypen eines Identifikators/Objektes -------------------------
#define VTPunkt		0
#define VTLinie		1
#define VTFlaeche	2
#define VTText		4
#define VTDefault	3	// keine VisInfo gegeben

// ----------------------------------------------------------------------------
// DatenStrukturen, die bei der Kommunikation mit der Extension verwendet werden
DECLARE_HANDLE (HDEX);			// Handle der Extension

typedef DWORD (FAR PASCAL *DEXENTRY)(HWND, UINT, WPARAM, LPARAM);
typedef DWORD (FAR PASCAL *DEXCALLBACK)(HDEX, UINT, WPARAM, LPARAM);

#if defined(__XT) && defined(__DEXPROCS)
typedef LRESULT (CALLBACK * DEXEXTENSIONPROC)(WPARAM, LPARAM);
typedef LRESULT (CALLBACK * DEXEXTENSIONPROC2)(HPROJECT, WPARAM, LPARAM);
typedef LRESULT (CALLBACK * DEXNOTIFICATIONPROC)(WPARAM, LPARAM, BOOL);
typedef LRESULT (CALLBACK * DEXDISPATCHPROC)(HWND, UINT, WPARAM, LPARAM);
#endif // __XT && __DEXPROCS

// Struktur, die beim Laden einer Erweiterung benötigt wird -------------------
typedef struct tagTRIAS_LOAD {
	DWORD dwSize;				// Größe dieserStruktur
	char szMenuName[DEX_MENUNAMELEN];	// Text im HauptMenu
	HMENU hMenu;				// PopUpMenuHandle
	UINT wMenuDelta;			// MenuOffset
	DEXCALLBACK fcDef;			// DefaultCallBack in TRIAS(R)
	char szORMenuName[DEX_MENUNAMELEN];	// Text für ObjRechMenu
	HMENU hORMenu;				// Menu für Objektrecherche
} TRIAS_LOAD;

// @struct TRIASLOADEX | Diese Struktur wird verwendet, um eine Erweiterung 
// zu laden.
// @field DWORD	| m_dwSize | Größe dieser Struktur
// @field char | m_szMenuName[DEX_MENUNAMELEN] | Menutext, der im Menu des Hauptfensters
// angezeigt werden soll.
// @field HMENU	| m_hMenu | Menu für Hauptfenster. Wenn dieser Wert ungleich NULL ist,
// dann wird dieses Menu als Popupmenu im Hauptfenster eingehängt. Dieses Menu muß
// jedoch durch die Erweiterung während der Bearbeitung der Message <m DEX_UNLOADEXTENSION>
// freigegeben werden.
// @field UINT	| m_wMenuDelta | Offset, der durch <tr> zu jedem Menu-ID hinzuaddiert
// wird, um Konflikte mit Menupunkten anderer Erweiterungen zu verhindern. Dieser Offset 
// muß durch die Erweiterung berücksichtigt werden, wenn direkt auf einzelne Menupunkte
// zugegriffen werden soll. Dieser Wert ist für eine Erweiterung nicht konstant und
// kann sich von Start zu Start verändern.
// @field DEXCALLBACK | m_fcDef | DefaultCallBack in <tr>, derzeit nicht verwendet
// @field char | m_szORMenuName[DEX_MENUNAMELEN] | Menutext, der im Menu jedes 
// Objekt-Recherchefensters angezeigt werden soll.
// @field HMENU	| m_hORMenu | Menu für Objektrecherche-Fenster. Wenn dieser Wert ungleich NULL ist,
// dann wird dieses Menu als Popupmenu in jedem Objektrecherche-Fenster eingehängt. Dieses Menu muß
// jedoch durch die Erweiterung während der Bearbeitung der Message <m DEX_UNLOADEXTENSION>
// freigegeben werden.
// @field short | m_iMode | Aktivierungs-Mode der Erweiterung. Dieses Feld kann folgende
// Werte enthalten:
// @flag LENoLoad	| Die Erweiterung soll nicht geladen werden.
// @flag LEInitOnly	| Die Erweiterung soll lediglich initialisiert werden. Es
// darf kein Nutzerinterface installiert werden (z.B. zusätzliche Menupunkte).
// @flag LEFullLoad	| Die Erweiterung soll vollständig initialisiert werden. 
// Das Nutzerinterface darf installiert werden.
// @comm Durch <tr> werden vor Übergabe dieser Struktur die Felder 
// <e TRIASLOADEX.m_dwSize>, <e TRIASLOADEX.m_wMenuDelta> und <e TRIASLOADEX.m_iMode> ausgefüllt. 
// Die restlichen Datenfelder können durch die Erweiterung gefüllt werden.
typedef struct tagTRIASLOADEX {
	DWORD m_dwSize;				// Größe dieser Struktur
	char m_szMenuName[DEX_MENUNAMELEN];	// Menutext im Menu des Hauptfensters 
	HMENU m_hMenu;				// MenuHandle
	UINT m_wMenuDelta;			// MenuOffset
	DEXCALLBACK m_fcDef;			// DefaultCallBack in <tr>
	char m_szORMenuName[DEX_MENUNAMELEN];	// Menutext für Objekt-Recherchefenster
	HMENU m_hORMenu;			// Menu für Objektrecherche
	short m_iMode;				// AktivierungsMode
} TRIASLOADEX;

#define LENoLoad	0x00
#define LEInitOnly	0x01
#define LEFullLoad	0x02

// Struktur für das Eröffnen eines Projektes ----------------------------------
// @struct TRIAS_OPEN | Diese Struktur wird im Zusammenhang mit der Message 
// <m DEX_PROJECTOPEN> verwendet, um ein <tr>-Projekt zu eröffnen.
// @xref <m DEX_PROJECTOPEN>, <t TRIAS_OPENEX>
typedef struct tagTRIAS_OPEN {
	DWORD dwSize;	// @field Die Größe dieser Struktur.
	char *lpProject;// @field Der Name des zu eröffnenden Projektes.
		// Entweder wird der volle Dateiname der Steuerblockdatei (*.ris) 
		// angegeben, oder lediglich der Dateiname. Die Dateierweiterung wird 
		// als '.ris' ergänzt und das Projekt im aktuellen Standard-Datenpfad 
		// gesucht.
	char *lpUser;	// @field Der Name des Nutzers, für den das Projekt geöffnet 
		// werden soll. Damit werden die Zugriffsrechte festgelegt.
	char *lpPassWord;	// @field Dieses Feld muß genau dann belegt sein 
		// (<p lpPassWord> != NULL), wenn für den gewünschten Nutzernamen ein
		// Paßwort vorgegeben worden ist. Ansonsten wird dieser Wert ignoriert.
	short iMode;	// @field Dieser Wert enthält den Mode, in dem das Projekt
		// geöffnet werden soll. Er kann folgende Werte bzw. eine 
		// Kombination dieser Werte annehmen:
} TRIAS_OPEN;

// Werte für iMode ------------------------------------------------------------
#define OM_Normal	0x08	// @flag OM_Normal | Eröffnen im Normalmodus, d.h. 
				// mit Schreibzugriff und Aktivierung der Standardansicht,
				// vormerken als aktuelles Projekt und ein evtl. geöffnetes 
				// Projekt schließen.
#define OM_NormalNoActivate	0x00	// @flag OM_NormalNoActivate | Eröffnen im Normalmodus, d.h. 
				// mit Schreibzugriff und Aktivierung der Standardansicht,
				// NICHT vormerken als aktuelles Projekt und ein evtl. geöffnetes 
				// Projekt schließen.
#define OM_RO		0x01	// @flag OM_RO | Eröffnen mit Schreibschutz (readonly).
#define OM_NoStandard	0x02	// @flag OM_NoStandard | Nach Eröffnen Standardansicht nicht anzeigen.
#define OM_HideWindow	0x04	// @flag OM_HideWindow | Nach Eröffnen Projektfenster nicht anzeigen.
#define OM_ActivateDBO	0x08	// @flag OM_ActivateDBO | Nach Eröffnen, dieses Projekt als derzeit 
				// aktuelles Projekt vormerken.
#define OM_NotCloseOpen	0x10	// @flag OM_NotCloseOpen | Vor Eröffnen dieses Projektes ein evtl. 
				// geöffnetes Projekt nicht schließen.
#define OM_DeleteOnClose	0x20	// @flag OM_DeleteOnClose | Das Projekt wird beim schließen
				// automatisch gelöscht, wenn es eine Datei ist.
#define OM_16BitCompatible	0x40	// @flag OM_16BitCompatible | Das Projekt wird im 16Bit Kompatibilitätsmodus
				// erzeugt.
#define OM_ConvertRisOnTheFly	0x80	// @flag OM_ConvertRisOnTheFly | Die gegebene <tr> Datenbank soll
				// ohne weitere Rückfragen als Datenquelle in einen neu zu erzeugende <tr> Workspace
				// eingebunden werden.

// @struct TRIAS_OPENEX | Diese Struktur wird im Zusammenhang mit der Message 
// <m DEX_PROJECTOPENEX> verwendet, um ein <tr>-Projekt zu eröffnen.
// @xref <m DEX_PROJECTOPENEX>, <t TRIAS_OPEN>
typedef struct tagTRIAS_OPENEX {
	DWORD dwSize;		// @field Die Größe dieser Struktur.
	LPCSTR pcProject;	// @field Der Name des zu eröffnenden Projektes.
		// Entweder wird der volle Dateiname der Steuerblockdatei (*.ris) 
		// angegeben, oder lediglich der Dateiname. Die Dateierweiterung wird 
		// als '.ris' ergänzt und das Projekt im aktuellen Standard-Datenpfad 
		// gesucht.
	LPCSTR pcUser;		// @field Der Name des Nutzers, für den das Projekt geöffnet 
		// werden soll. Damit werden die Zugriffsrechte festgelegt. (hier zumeist NULL)
	LPCSTR pcPassWord;	// @field Dieses Feld muß genau dann belegt sein 
		// (<e TRIAS_OPENEX.lpPassWord> != NULL), wenn für den gewünschten Nutzernamen ein
		// Paßwort vorgegeben worden ist. Ansonsten wird dieser Wert ignoriert.
	short iMode;	// @field Dieser Wert enthält den Mode, in dem das Projekt
		// geöffnet werden soll (s. iMode von <t TRIAS_OPEN>)
	DWORD dwMode;	// @field Dieser Wert enthält den Mode, in dem das Projekt
		// geöffnet werden soll. Er kann beliebige Werte aus STGM_... enthalten
} TRIAS_OPENEX;

// @struct TRIAS_OPENEX | Diese Struktur wird im Zusammenhang mit der Message 
// <m DEX_PROJECTOPENEX> verwendet, um ein <tr>-Projekt zu eröffnen.
// @xref <m DEX_PROJECTOPENEX>, <t TRIAS_OPEN>
typedef struct tagTRIAS_OPENSTG {
	DWORD dwSize;		// @field Die Größe dieser Struktur.
	LPCSTR pcProject;	// @field Der Name des zu eröffnenden Projektes.
		// Entweder wird der volle Dateiname der Steuerblockdatei (*.ris) 
		// angegeben, oder lediglich der Dateiname. Die Dateierweiterung wird 
		// als '.ris' ergänzt und das Projekt im aktuellen Standard-Datenpfad 
		// gesucht.
	int iMode;		// @field Dieser Wert enthält den Mode, in dem das Projekt
		// geöffnet werden soll (s. iMode von <t TRIAS_OPEN>)
	LPSTORAGE m_pIStorage;	// @field Dieser Wert enthält ein Ole-Storage, in welchem
		// ein Projekt gespeichert ist, welches hier geöffnet werden soll
} TRIAS_OPENSTG;

// Struktur für EnumRechObjMerkmale -------------------------------------------
// @func BOOL | RECHTEXTMERKMALCALLBACK | Rückruf-Funktion, die durch eine Erweiterung
// installiert werden muß, wenn eine Enumeration aller Objekte, die ein gegebenes Merkmal
// besitzen, durchgeführt werden soll.
// @rdesc Eine Erweiterung sollte <t true> liefern, wenn die Enumeration fortgesetzt
// werden soll. Im Fehlerfall oder wenn die Enumeration abgebrochen werden soll, 
// muß diese Funktion <t false> liefern.
// @parm long | lValue | Die Objektnummer eines Objektes, welches den Suchkriterien entspricht.
// @parm BOOL | fNotLast | Dieser Wert gibt an, ob der aktuelle Aufruf der Funktion 
// nicht der letzte in dieser Enumeration ist.
// @parm void * | pData | Durchzureichende Daten.
// @xref <m DEX_ENUMTEXTMERKMALRECH>
typedef BOOL (CALLBACK *RECHTEXTMERKMALCALLBACK)(HOBJECT ONr, BOOL iNotLast, void *pData);
// typedef RECHTEXTMERKMALCALLBACK RECHTEXTMERKMALPROC;
typedef BOOL (*RECHTEXTMERKMALPROC)(HOBJECT ONr, BOOL iNotLast, void *pData);

// @struct ENUMRECHTEXTMERKMAL | Diese Datenstruktur wird verwendet, um eine Enumeration 
// aller Objekte mit einem gegebenen Merkmal durchzuführen.
// @comm Die im Feld <e ENUMRECHTEXTMERKMAL.pData> vorgegebenen Daten werden ohne Veränderung als 
// 3. Parameter (<p pData>) an die zu rufende Funktion <e ENUMRECHTEXTMERKMAL.eFcn> übergeben 
// und können durch die Erweiterung frei belegt werden.
// @xref <m DEX_ENUMTEXTMERKMALRECH>
typedef struct tagENUMRECHTEXTMERKMAL {
	DWORD dwSize;	// @field Die Größe dieser Struktur.
	char *pView;	// @field Wenn ungleich NULL, dann wird die Recherche auf 
		// die Sicht beschränkt, deren Namen durch <e ENUMRECHTEXTMERKMAL.pView> gegeben ist.
	long lMCode;	// @field Gibt den zu untersuchenden Merkmalscode vor.
	char *pMWert;	// @field Gesuchtes Textmerkmal.
	short iMode;	// @field SuchMode, hier können folgende Werte gegeben sein:
		// @flag SMExactMatch | Es werden alle Objekte geliefert, die exakt das gesuchte
		// Textmerkmal besitzen.
		// @flag SMInexactMatch | Es werden alle Objekte geliefert, die ein 
		// ähnliches Textmerkmal besitzen. Dieser Mode ist verwendbar, um evtl. 
		// Tippfehler zu berücksichtigen.
		// @flag SMSubstringMatch | Es werden alle Objekte geliefert, deren Merkmal
		// den Suchstring enthalten.
		// @flag SMSubstringStartMatch | Es werden alle Objekte geliefert, deren Merkmal
		// mit dem gegebenen Suchstring beginnt.
		// @flag SMExistanceOnly | Es werden alle Objekte geliefert, die dieses Merkmal 
		// besitzen (entspricht pMText == NULL)
		// @flag SMActViewOnly | Diese Flag kann mit den anderen kombiniert werden
		// und beschränkt die Suche auf die aktuelle Sicht. <e ENUMRECHTEXTMERKMAL.pView>
		// wird in diesem Fall ignoriert.
	RECHTEXTMERKMALCALLBACK eFcn;	// @field Durch die Enumeration zu rufende Funktion 
		// <f RECHTEXTMERKMALCALLBACK>.
	void *pData;	// @field An die gerufene Funktion durchgereichte Daten.
} ENUMRECHTEXTMERKMAL;

// @struct ENUMRECHTEXTMERKMALEX | Diese Datenstruktur wird verwendet, um eine Enumeration 
// aller Objekte mit einem gegebenen Merkmal durchzuführen.
// @comm Die im Feld <e ENUMRECHTEXTMERKMALEX.pData> vorgegebenen Daten werden ohne Veränderung als 
// 3. Parameter (<p pData>) an die zu rufende Funktion <e ENUMRECHTEXTMERKMALEX.eFcn> übergeben 
// und können durch die Erweiterung frei belegt werden.
// @xref <m DEX_ENUMTEXTMERKMALRECHEX>
typedef struct tagENUMRECHTEXTMERKMALEX {
	DWORD dwSize;	// @field Die Größe dieser Struktur.
	char *pView;	// @field Wenn ungleich NULL, dann wird die Recherche auf 
		// die Sicht beschränkt, deren Namen durch <e ENUMRECHTEXTMERKMALEX.pView> gegeben ist.
	long lMCode;	// @field Gibt den zu untersuchenden Merkmalscode vor.
	char *pMWert;	// @field Gesuchtes Textmerkmal.
	short iMode;	// @field SuchMode, hier können folgende Werte gegeben sein:
		// @flag SMExactMatch | Es werden alle Objekte geliefert, die exakt das gesuchte
		// Textmerkmal besitzen.
		// @flag SMInexactMatch | Es werden alle Objekte geliefert, die ein 
		// ähnliches Textmerkmal besitzen. Dieser Mode ist verwendbar, um evtl. 
		// Tippfehler zu berücksichtigen.
		// @flag SMSubstringMatch | Es werden alle Objekte geliefert, deren Merkmal
		// den Suchstring enthalten.
		// @flag SMSubstringStartMatch | Es werden alle Objekte geliefert, deren Merkmal
		// mit dem gegebenen Suchstring beginnt.
		// @flag SMExistanceOnly | Es werden alle Objekte geliefert, die dieses Merkmal 
		// besitzen (entspricht pMText == NULL)
		// @flag SMActViewOnly | Diese Flag kann mit den anderen kombiniert werden
		// und beschränkt die Suche auf die aktuelle Sicht. <e ENUMRECHTEXTMERKMALEX.pView>
		// wird in diesem Fall ignoriert.
	RECHTEXTMERKMALCALLBACK eFcn;	// @field Durch die Enumeration zu rufende Funktion 
		// <f RECHTEXTMERKMALCALLBACK>.
	void *pData;	// @field An die gerufene Funktion durchgereichte Daten.
	BOOL fFilteredColl;	// @field Spezialflag für GDO und andere exotische Datenquellen,
		// welche die Recherche über die einzelnen Objektklassen durchführen. Einfach
		// auf FALSE setzen und wenn's TRUE wird, die Recherche erfolgreich abbrechen :-)
} ENUMRECHTEXTMERKMALEX;

#define SMExactMatch			1		// zulässige Werte für iMode, default: 1
#define SMInexactMatch			2
#define SMSubstringMatch		3
#define SMSubStringStartMatch	4
#define SMRegularExpression		5
#define SMExistanceOnly			6		// äquivalent zu pMText == NULL
#define SMSubRegularExpression	7		// RegExpr, aber substring
#define SMActionFlag		 0x7F		// Flag für eigentliche Aktion

#define SMActViewOnly		 0x80		// nur in aktueller Sicht
#define SMNegateResult		0x100		// Resultat negieren (not supported (yet))
#define SMIgnoreCase		0x200		// Resultat negieren (not supported (yet))

// Struktur für EnumRechGeometrie ---------------------------------------------
typedef BOOL (CALLBACK *RECHGEOMETRIECALLBACK)(HOBJECT ONr, BOOL iNotLast, void *pData);
// typedef RECHGEOMETRIECALLBACK RECHGEOMETRIEPROC;
typedef BOOL (*RECHGEOMETRIEPROC)(HOBJECT ONr, BOOL iNotLast, void *pData);

typedef struct tagENUMRECHGEOMETRIE {
	DWORD dwSize;
	void *lCont;			// SuchBereich (ObjContainer !!/double *)
	short iMode;			// SuchMode
	RECHGEOMETRIEPROC eFcn;		// gerufene Funktion
	void *pData;			// an Funktion übergebener DatenBereich
} ENUMRECHGEOMETRIE;

#define ERGExact		0x01	// Geometrie exakt prüfen
#define ERGActSight		0x02	// nur aktuelle Sicht auswerten
#define ERGConverted	0x04	// Suchbereich enthält double Koordinaten

typedef struct tagENUMRECHGEOMETRIEEX {
	DWORD dwSize;
	void *lCont;			// SuchBereich (ObjContainer !!/double *)
	short iMode;			// SuchMode
	RECHGEOMETRIEPROC eFcn;		// gerufene Funktion
	void *pData;			// an Funktion übergebener DatenBereich
	const char *m_pView;	// zu untersuchende Ansicht (NULL: aktuelle Ansicht)
} ENUMRECHGEOMETRIEEX;

// Struktur für Enumeration mit einem long-Key --------------------------------
// @func BOOL | ENUMLONGKEYCALLBACK | Rückruf-Funktion, die durch eine Erweiterung
// installiert werden muß, wenn eine Enumeration über einen long -Schlüssel
// durchgeführt werden soll.
// @rdesc Eine Erweiterung sollte <t true> liefern, wenn die Enumertaion fortgesetzt
// werden soll. Im Fehlerfall oder wenn die Enumeration abgebrochen werden soll, 
// muß diese Funktion <t false> liefern.
// @parm long | lValue | Der aktuelle Wert der zu enumerierenden Eigenschaft 
// (Objektnummer, Merkmalscode o.ä.).
// @parm BOOL | fNotLast | Dieser Wert gibt an, ob der aktuelle Aufruf der Funktion 
// nicht der letzte in dieser Enumeration ist.
// @parm void * | pData | Durchzureichende Daten.
// @xref <m DEX_ENUMMERKMALE>, <m DEX_ENUMMERKMALEIDENT>, <m DEX_ENUMVIEWIDENTS>
// <m DEX_ENUMIDENTOBJS>
typedef BOOL (CALLBACK *ENUMLONGKEYCALLBACK)(HGENERIC Key, BOOL iNotLast, void *pData);
// typedef ENUMLONGKEYCALLBACK ENUMLONGKEYPROC;
typedef BOOL (*ENUMLONGKEYPROC)(HGENERIC Key, BOOL iNotLast, void *pData);

// @struct ENUMLONGKEY | Diese Datenstruktur wird verwendet, um eine Enumeration über 
// einen long -Schlüssel durchzuführen.
// @comm Die im Feld <e ENUMLONGKEY.ePtr> vorgegebenen Daten werden ohne Veränderung als 
// 3. Parameter (<p pData>) an die zu rufende Funktion <e ENUMLONGKEY.eFcn> übergeben 
// und können durch die Erweiterung frei belegt werden.
// @xref <m DEX_ENUMMERKMALE>, <m DEX_ENUMMERKMALEIDENT>, <m DEX_ENUMVIEWIDENTS>
// <f ENUMLONGKEYCALLBACK>
typedef struct tagENUMLONGKEY {
	HGENERIC eKey;		// @field Suchschlüssel, über den zu enumerieren ist.
	ENUMLONGKEYPROC eFcn;	// @field Durch die Enumeration zu rufende Funktion <f ENUMLONGKEYCALLBACK>.
	void *ePtr;		// @field An die gerufene Funktion durchgereichte Daten.
} ENUMLONGKEY;

// @func BOOL | ENUMLONGKEYEXCALLBACK | Rückruf-Funktion, die durch eine Erweiterung
// installiert werden muß, wenn eine Enumeration über einen long -Schlüssel mit 
// erweiterter Parametervorgabe durchgeführt werden soll (<m DEX_ENUMMERKMALEEX>, 
// <m DEX_ENUMMERKMALEIDENTEX>).
// @rdesc Eine Erweiterung sollte <t true> liefern, wenn die Enumertaion fortgesetzt
// werden soll. Im Fehlerfall oder wenn die Enumeration abgebrochen werden soll, 
// muß diese Funktion <t false> liefern.
// @parm long | lValue | Der aktuelle Wert der zu enumerierenden Eigenschaft 
// (Objektnummer, Merkmalscode o.ä.).
// @parm DWORD | dwData | Die an dieser Stelle übergebenen Daten sind spezifisch für 
// jede konkrete Message und jeweils dort beschrieben.
// @parm void * | pData | Durchzureichende Daten.
// @xref <m DEX_ENUMMERKMALEEX>, <m DEX_ENUMMERKMALEIDENTEX>, <m DEX_ENUMIDENTOBJSEX>
typedef BOOL (CALLBACK *ENUMLONGKEYEXCALLBACK)(HGENERIC Key, DWORD dwData, void *pData);
// typedef ENUMLONGKEYEXCALLBACK ENUMLONGKEYEXPROC;
typedef BOOL (*ENUMLONGKEYEXPROC)(HGENERIC Key, DWORD dwData, void *pData);

// @struct ENUMLONGKEYEX | Diese Datenstruktur wird verwendet, um eine Enumeration über 
// einen long -Schlüssel durchzuführen (Message <m DEX_ENUMMERKMALEEX>, 
// <m DEX_ENUMMERKMALEIDENTEX>).
// @comm Die im Feld <e ENUMLONGKEYEX.ePtr> vorgegebenen Daten werden ohne Veränderung als 
// 3. Parameter (<p pData>) an die zu rufende Funktion <e ENUMLONGKEYEX.eFcn> übergeben 
// und können durch die Erweiterung frei belegt werden.
// @xref <m DEX_ENUMMERKMALEEX>, <m DEX_ENUMMERKMALEIDENTEX>, <f ENUMLONGKEYCALLBACK>
typedef struct tagENUMLONGKEYEX {
	HGENERIC eKey;		// @field Suchschlüssel, über den zu enumerieren ist.
	ENUMLONGKEYEXPROC eFcn;	// @field Durch die Enumeration zu rufende Funktion <f ENUMLONGKEYCALLBACK>.
	void *ePtr;			// @field An die gerufene Funktion durchgereichte Daten.
	DWORD eData;		// @field Zusätzliche Parameter für die Enumeration. 
		// Die Bedeutung dieser Parameter ist abhängig von der konkreten
		// Enumeration und jeweils dort beschrieben.
} ENUMLONGKEYEX;

#define MPObjectFeature		'a'		// Objektattribut
#define MPViewFeature		'b'		// Ansichtsattribut
#define MPIdentFeature		'c'		// Objektklassenattribut
#define MPDoubleFeature		'f'
#define MPIntegerFeature	'i'
#define MPUnknownFeature	'u'
#define MPSystemFeatures	0x0100	// Systeminterne Attribute
#define MPAllFeatures		0x0200	// Alle Attribute (auch Ansichts- und Objektklassenattribute)
#define MPReadOnlyFeatures	0x0400	// Schreibgeschützte Attribute
#define MPTextFeature		0x0800
#define MPPbdOnly			0x1000	// Merkmale, die nur in Pbd definiert sind
#define MPForceForTRiASDBs	0x2000	// nur für TRiAS Datenquellen: Nur Merkmalstyp setzen
#define MPListAllClasses	0x4000	// Für DEX_EnumMCodesEx: wenn keine durchzureichenden Daten 
	// gegeben sind (ePtr), dann nicht nur aktuellen Identifikator übergeben, sondern Liste 
	// aller Identifikatoren (vector<HOBJECTS> *), für die ein Attribut (MCode) existiert 
	// (nur für TRiAS Datenquellen, ansonsten genau ein Identifikator)

// Struktur für Enumeration mit TextSchlüssel ---------------------------------
// @func BOOL | ENUMTEXTKEYCALLBACK | Rückruf-Funktion, die durch eine Erweiterung
// installiert werden muß, wenn eine Enumeration über einen Text-Schlüssel
// durchgeführt werden soll (<m DEX_ENUMMERKMALESICHT>).
// @rdesc Eine Erweiterung sollte <t true> liefern, wenn die Enumertaion fortgesetzt
// werden soll. Im Fehlerfall oder wenn die Enumeration abgebrochen werden soll, 
// muß diese Funktion <t false> liefern.
// @parm long | lValue | Der aktuelle Wert der zu enumerierenden Eigenschaft 
// (Objektnummer, Merkmalscode o.ä.).
// @parm BOOL | fNotLast | Dieser Wert gibt an, ob der aktuelle Aufruf der Funktion 
// nicht der letzte in dieser Enumeration ist.
// @parm void * | pData | Durchzureichende Daten.
// @xref <m DEX_ENUMMERKMALESICHT>
typedef BOOL (CALLBACK *ENUMTEXTKEYCALLBACK)(HGENERIC Key, BOOL iNotLast, void *pData);
// typedef ENUMTEXTKEYCALLBACK ENUMTEXTKEYPROC;
typedef BOOL (*ENUMTEXTKEYPROC)(HGENERIC Key, BOOL iNotLast, void *pData);

// @struct ENUMTEXTKEY | Diese Datenstruktur wird verwendet, um eine Enumeration über 
// einen Text-Schlüssel durchzuführen (Message <m DEX_ENUMMERKMALESICHT>).
// @comm Die im Feld <e ENUMTEXTKEY.ePtr> vorgegebenen Daten werden ohne Veränderung 
// als 3. Parameter (<p pData>) an die zu rufende Funktion <e ENUMTEXTKEY.eFcn> übergeben 
// und können durch die Erweiterung frei belegt werden.
// @xref <m DEX_ENUMMERKMALESICHT>, <f ENUMTEXTKEYCALLBACK>
typedef struct tagENUMTEXTKEY {
	char *eKey;		// @field Suchschlüssel, über den zu enumerieren ist.
	ENUMLONGKEYPROC eFcn;	// @field Durch die Enumeration zu rufende Funktion <f ENUMLONGKEYCALLBACK>.
	void *ePtr;		// @field An die gerufene Funktion durchgereichte Daten.
} ENUMTEXTKEY;

// @func BOOL | ENUMTEXTKEYEXCALLBACK | Rückruf-Funktion, die durch eine Erweiterung
// installiert werden muß, wenn eine Enumeration über einen Text-Schlüssel
// durchgeführt werden soll (<m DEX_ENUMMERKMALESICHTEX>).
// @rdesc Eine Erweiterung sollte <t true> liefern, wenn die Enumertaion fortgesetzt
// werden soll. Im Fehlerfall oder wenn die Enumeration abgebrochen werden soll, 
// muß diese Funktion <t false> liefern.
// @parm long | lValue | Der aktuelle Wert der zu enumerierenden Eigenschaft 
// (Objektnummer, Merkmalscode o.ä.).
// @parm DWORD | dwData | Die an dieser Stelle übergebenen Daten sind spezifisch für 
// jede konkrete Message und jeweils dort beschrieben.
// @parm void * | pData | Durchzureichende Daten.
// @xref <m DEX_ENUMMERKMALESICHTEX>
typedef BOOL (CALLBACK *ENUMTEXTKEYEXCALLBACK)(HGENERIC Key, DWORD dwData, void *pData);
// typedef ENUMTEXTKEYEXCALLBACK ENUMTEXTKEYEXPROC;
typedef BOOL (*ENUMTEXTKEYEXPROC)(HGENERIC Key, DWORD dwData, void *pData);

// @struct ENUMTEXTKEYEX | Diese Datenstruktur wird verwendet, um eine Enumeration über 
// einen Text-Schlüssel durchzuführen (Message <m DEX_ENUMMERKMALESICHTEX>).
// @comm Die im Feld <e ENUMTEXTKEYEX.ePtr> vorgegebenen Daten werden ohne Veränderung als 
// 3. Parameter (<p pData>) an die zu rufende Funktion <e ENUMTEXTKEYEX.eFcn> übergeben 
// und können durch die Erweiterung frei belegt werden.
// @xref <m DEX_ENUMMERKMALESICHTEX>, <f ENUMTEXTKEYEXCALLBACK>
typedef struct tagENUMTEXTKEYEX {
	char *eKey;		// @field Suchschlüssel, über den zu enumerieren ist.
	ENUMLONGKEYEXPROC eFcn;	// @field Durch die Enumeration zu rufende Funktion <f ENUMLONGKEYCALLBACK>.
	void *ePtr;		// @field An die gerufene Funktion durchgereichte Daten.
	DWORD eData;		// @field Zusätzliche Parameter für die Enumeration. 
		// Die Bedeutung dieser Parameter ist abhängig von der konkreten
		// Enumeration und jeweils dort beschrieben.
} ENUMTEXTKEYEX;

// Struktur für Enumeration ohne Schlüssel ------------------------------------
// @func BOOL | ENUMNOKEYCALLBACK | Rückruf-Funktion, die durch eine Erweiterung
// installiert werden muß, wenn eine Enumeration über das gesamte Projekt 
// durchgeführt werden soll (<m DEX_ENUMALLSIGHTS>).
// @rdesc Eine Erweiterung sollte <t true> liefern, wenn die Enumertaion fortgesetzt
// werden soll. Im Fehlerfall oder wenn die Enumeration abgebrochen werden soll, 
// muß diese Funktion <t false> liefern.
// @parm char * | pValue | Der aktuelle Wert der zu enumerierenden Eigenschaft 
// (Sichtname).
// @parm BOOL | fNotLast | Dieser Wert gibt an, ob der aktuelle Aufruf der Funktion 
// nicht der letzte in dieser Enumeration ist.
// @parm void * | pData | Durchzureichende Daten.
// @xref <m DEX_ENUMALLSIGHTS>
typedef BOOL (CALLBACK *ENUMNOKEYCALLBACK)(char *pPtr, BOOL fNotLast, void *pData);
typedef BOOL (*ENUMNOKEYPROC)(char *pPtr, BOOL fNotLast, void *pData);

// @struct ENUMNOKEY | Diese Datenstruktur wird verwendet, um eine Enumeration ohne 
// Schlüssel (über das gesamte aktuelle Projekt) durchzuführen (Message <m DEX_ENUMALLSIGHTS>).
// @comm Die im Feld <e ENUMNOKEY.ePtr> vorgegebenen Daten werden ohne Veränderung 
// als 3. Parameter (<p pData>) an die zu rufende Funktion <e ENUMNOKEY.eFcn> übergeben und können
// durch die Erweiterung frei belegt werden.<par>Diese Datenstruktur unterscheidet 
// sich von der Struktur <t ENUMNOKEYLONG> lediglich
// durch den Typ der vorzugebenden Rückruffunktion. <t ENUMNOKEY> wird verwendet,
// wenn der Typ der zu enumerierenden Eigenschaft 'char *' ist.
// @xref <m DEX_ENUMALLSIGHTS>, <f ENUMNOKEYCALLBACK>, <t ENUMNOKEYLONG>
typedef struct tagENUMNOKEY {
	ENUMNOKEYPROC eFcn;	// @field Zu registrierende Rückruffunktion.
	void *ePtr;		// @field An die Rückruffunktion als 3. Parameter
		// durchzureichende Daten.
} ENUMNOKEY;

// @func BOOL | ENUMNOKEYLONGCALLBACK | Rückruf-Funktion, die durch eine Erweiterung
// installiert werden muß, wenn eine Enumeration über das gesamte Projekt 
// durchgeführt werden soll (<m DEX_ENUMALLIDENTS>).
// @rdesc Eine Erweiterung sollte <t true> liefern, wenn die Enumertaion fortgesetzt
// werden soll. Im Fehlerfall oder wenn die Enumeration abgebrochen werden soll, 
// muß diese Funktion <t false> liefern.
// @parm long | lValue | Der aktuelle Wert der zu enumerierenden Eigenschaft 
// (Identifikator).
// @parm void * | pData | Durchzureichende Daten.
// @xref <m DEX_ENUMALLIDENTS>
typedef BOOL (CALLBACK *ENUMNOKEYLONGCALLBACK)(long Key, BOOL iNotLast, void *pData);
typedef BOOL (*ENUMNOKEYLONGPROC)(long Key, BOOL iNotLast, void *pData);

// @struct ENUMNOKEYLONG | Diese Datenstruktur wird verwendet, um eine Enumeration ohne 
// Schlüssel (über das gesamte aktuelle Projekt) durchzuführen (Message <m DEX_ENUMALLIDENTS>).
// @comm Die im Feld <e ENUMNOKEYLONG.ePtr> vorgegebenen Daten werden ohne Veränderung 
// als 3. Parameter (<p pData>) an die zu rufende Funktion <e ENUMNOKEYLONG.eFcn> übergeben und können 
// durch die Erweiterung frei belegt werden.<par>Diese Datenstruktur unterscheidet 
// sich von der Struktur <t ENUMNOKEY> lediglich
// durch den Typ der vorzugebenden Rückruffunktion. <t ENUMNOKEYLONG> wird verwendet,
// wenn der Typ der zu enumerierenden Eigenschaft 'long' ist.
// @xref <m DEX_ENUMALLIDENTS>, <f ENUMNOKEYLONGCALLBACK>, <t ENUMNOKEY>
typedef struct tagENUMNOKEYLONG {
	ENUMNOKEYLONGPROC eFcn;	// @field Zu registrierende Rückruffunktion.
	void *ePtr;		// @field An die Rückruffunktion als 3. Parameter
		// durchzureichende Daten.
} ENUMNOKEYLONG;

typedef BOOL (CALLBACK *ENUMNOKEYEXCALLBACK)(char *pPtr, DWORD dwData, void *pData);
typedef BOOL (*ENUMNOKEYEXPROC)(char *pPtr, DWORD dwData, void *pData);
typedef BOOL (CALLBACK *ENUMNOKEYLONGEXCALLBACK)(HGENERIC hKey, DWORD dwData, void *pData);
typedef BOOL (*ENUMNOKEYLONGEXPROC)(HGENERIC hKey, DWORD dwData, void *pData);

typedef struct tagENUMNOKEYEX {
	ENUMNOKEYEXPROC eFcn;	// zu rufende Funktion
	void *ePtr;		// durchzureichende Daten
	DWORD eData;	// zusätzliche Parameter
} ENUMNOKEYEX;

typedef struct tagENUMNOKEYLONGEX {
	ENUMNOKEYLONGEXPROC eFcn;	// zu rufende Funktion
	void *ePtr;		// durchzureichende Daten
	DWORD eData;	// zusätzliche Parameter
} ENUMNOKEYLONGEX;

// Zusammenfassen zweier Objekte zu einem Komplexobjekt -----------------------
typedef struct tagMERGEKOBJECT {
	HOBJECT mObj1;		// BezugsObjekt
	HOBJECT mObj2;		// hinzuzufügendes Objekt
	HOBJECTS mIdent;	// neuer Identifikator
	HRELATION mRCode;	// zu verwendender RelationsCode
	BOOL mMerge;	// Objekte vereinigen oder neues KObjekt bilden
} MERGEKOBJECT;

// Herauslöschen eines Objektes aus einem Komplexobjekt -----------------------
typedef struct tagDELETEKOBJECT {
	HOBJECT doKObj;		// KomplexObjekt, aus dem herausgelöst werden soll
	HOBJECT doObj;		// herauszulösendes Objekt
} DELETEKOBJECT;

// Einfügen eines neuen Identifikators in die SpeicherListe -------------------
typedef struct tagADDNEWIDENT {	
	HOBJECTS newIdent;		// neuer Identifikator
	short iFlags;		// Identifikator ist temporär
	short iTyp;			// ObjTyp für diesen Ident
} ADDNEWIDENT;

#define ANI_Temp			0x01	// @flag Temporär zu Objektklasse hinzufügen
#define ANI_AddToView		0x02	// @flag Neue Objektklasse zu aktueller Ansicht hinzufügen
#define ANI_CountObjects	0x04	// @flag Objekttypen in Objektklasse zählen
#define ANI_UnloadComplete	0x08	// @flag Objekte Objektklasse komplett neu laden
#define ANI_Unload			0x10	// @flag neue Objekte dieser Objektklasse nachladen

// Fehlermeldungen systemweit verteilen ---------------------------------------
typedef struct tagERRORMESSAGE {
	short emiErrCode;	// FehlerCode
	short emiRoutine;	// RoutinenCode
	void *empData;		// zusätzliche Daten
} ERRORMESSAGE;

typedef int (*ERRHANDLER)(int,int,...);
typedef struct tagERRINSTALL {
	short eiRC;		// FehlerCode
	ERRHANDLER eiEH;	// neue Fehlerbehandlungsart
	ERRHANDLER *eioEH;	// alte Fehlerbehandlungsart
} ERRINSTALL;

typedef struct tagEXTERRINSTALL {
	short eiRC;		// FehlerCode
	ERRHANDLER eiEH;	// neue Fehlerbehandlungsart
	ERRHANDLER *eioEH;	// alte Fehlerbehandlungsart
	DWORD dwData;		// durchzureichende Daten
} EXTERRINSTALL;

// Struktur für das Liefern eines MerkmalsWertes ------------------------------
#define	TT_Objekt		6
#define TT_Identifikator 	8
#define	TT_Sicht		25

// @struct TARGETMERKMAL | Diese Struktur wird im Zusammenhang mit den Messages
// <m DEX_QUERYTEXTMERKMAL> und <m DEX_MODIFYMERKMAL> verwendet, um ein Merkmal eines
// Objektes, eines Identifikators oder einer Ansicht zu lesen, zu schreiben oder zu 
// löschen.
// @comm Ein Merkmal wird dann gelöscht, wenn beim Schreiben die Felder
// <mf TARGETMERKMAL.pMText> und <mf TARGETMERKMAL.imaxLen> ausgenullt sind.
// @xref <m DEX_QUERYTEXTMERKMAL>, <m DEX_MODIFYMERKMAL>, <t TARGETMERKMALEX>
typedef struct tagTARGETMERKMAL {
	DWORD dwSize;	// @field Die Größe dieser Struktur.
	HGENERIC lTarget;	// @field Dieses Feld muß die Objektnummer, den
		// Identifikator oder einen Zeiger auf den Ansichtnamen enthalten,
		// für den/die das Merkmal behandelt werden soll. Dieses Feld wird in 
		// Abhängigkeit vom Feld <mf TARGETMERKMAL.iTTyp> interpretiert.
	HFEATURE lMCode;	// @field Enthält den Merkmalscode des zu behandelnden Merkmales.
	short imaxLen;	// @field Enthält beim Lesen eines Merkmales (Message <m DEX_QUERYTEXTMERKMAL>)
		// die Größe des Textpuffers sowie nach dem Aufruf die Länge des
		// gelesenen Textes. Beim Schreiben (Message <m DEX_MODIFYMERKMAL>) enthält 
		// dieses Feld die Länge der zu schreibenden Zeichenkette.
	char *pMText;	// @field Enthält beim Lesen einen Zeiger auf den Pufferbereich,
		// in dem das gelesene Merkmal abgelegt werden soll, beim Schreiben den
		// neuen Merkmalstext.
	short iTTyp;	// @field Enthält die Information, ob 
		// es sich um ein Merkmal eines Objektes, eines Identifikators oder
		// einer Ansicht handelt. Es kann folgende Werte enthalten
		// @flag TT_Objekt | Es handelt sich um ein Objektmerkmal.
		// @flag TT_Identifikator | Es handelt sich um ein identifikatormerkmal.
		// @flag TT_Sicht | Es handelt sich um ein Ansichtmerkmal.
} TARGETMERKMAL;

// @struct TARGETMERKMALEX | Diese Struktur wird im Zusammenhang mit den Messages
// <m DEX_QUERYTEXTMERKMAL> und <m DEX_MODIFYMERKMAL> verwendet, um ein Merkmal eines
// Objektes, eines Identifikators oder einer Ansicht zu lesen, zu schreiben oder zu 
// löschen.
// @comm Das Verhalten der Messages mit dieser Struktur ist im wesentlichen identisch
// mit dem Verhalten bei der Verwendung der Struktur <m TARGETMERKMAL>. Lediglich 
// Feinheiten können mit Hilfe der Flags im Feld <mf TARGETMERKMALEX.iFlags> beeinflußt
// werden.
// @xref <m DEX_QUERYTEXTMERKMAL>, <m DEX_MODIFYMERKMAL>, <t TARGETMERKMAL>
typedef struct tagTARGETMERKMALEX {
	DWORD dwSize;	// @field Die Größe dieser Struktur.
	HGENERIC lTarget;	// @field Dieses Feld muß die Objektnummer, den
		// Identifikator oder einen Zeiger auf den Ansichtnamen enthalten,
		// für den/die das Merkmal behandelt werden soll. Dieses Feld wird in 
		// Abhängigkeit vom Feld <mf TARGETMERKMAL.iTTyp> interpretiert.
	HFEATURE lMCode;	// @field Enthält den Merkmalscode des zu behandelnden Merkmales.
	short imaxLen;	// @field Enthält beim Lesen eines Merkmales (Message <m DEX_QUERYTEXTMERKMAL>)
		// die Größe des Textpuffers sowie nach dem Aufruf die Länge des
		// gelesenen Textes. Beim Schreiben (Message <m DEX_MODIFYMERKMAL>) enthält 
		// dieses Feld die Länge der zu schreibenden Zeichenkette.
	char *pMText;	// @field Enthält beim Lesen einen Zeiger auf den Pufferbereich,
		// in dem das gelesene Merkmal abgelegt werden soll, beim Schreiben den
		// neuen Merkmalstext.
	short iTTyp;	// @field Enthält die Information, ob 
		// es sich um ein Merkmal eines Objektes, eines Identifikators oder
		// einer Ansicht handelt. Es kann folgende Werte enthalten
		// @flag TT_Objekt | Es handelt sich um ein Objektmerkmal.
		// @flag TT_Identifikator | Es handelt sich um ein identifikatormerkmal.
		// @flag TT_Sicht | Es handelt sich um ein Ansichtmerkmal.
	short iFlags;	// @field Enthält zusätzliche Informationen über spezielle
		// Modi der Funktion. Es kann eine Kombination der folgenden Werte enthalten:
		// @flag TMNoCaching | Nur beim Schreiben: Verhindert, daß der neue 
		// Merkmalswert im Merkmals-Cache von <tr> abgelegt wird.
		// @flag TMCreateNewTarget | Nur beim Schreiben und 'TT_Identifikator':
		// Identifikatorsatz anlegen, wenn nicht existent.
	const char *pcView;	// @field Nur bei 'TT_Identifikator': Enthält die Ansicht, für die dieses
		// Merkmal an der Objektklasse abgelegt/gelesen werden soll. (NULL --> aktuelle Ansicht)
} TARGETMERKMALEX;

#define TMNoCaching	0x01
#define TMCreateNewTarget 0x02

// @struct OBJECTFEATURE | Diese Struktur dient zum Lesen, Schreiben und Löschen
// von speziellen Objektmerkmalen, wie z.B. Objektname oder Unique Ident. Sie ist 
// zur Vereinfachung der Merkmals-Schnittstelle vorgesehen. 
// @xref <m DEX_QUERYOBJECTNAME>, <m DEX_SETOBJECTNAME>
typedef struct tagOBJECTFEATURE {	
	DWORD m_dwSize;	// @field Die Größe dieser Struktur.
	HOBJECT m_lONr;	// @field Objektnummer des zu behandelnden Objektes.
	char *m_pMText;	// @field Der Zeichenkettenpuffer, der zur Übertragung
		// des Merkmalstextes dient. Beim Schreiben (Message <m DEX_SETOBJECTNAME>)
		// muß hier der neue Text vorgegeben werden.<nl>Beim Lesen (Message 
		// <m DEX_QUERYOBJECTNAME>) wird hier der Text geliefert.<nl>Um ein spezielles
		// Merkmal zu löschen, muß <p m_pMText> gleich NULL sein.
	short m_iLen;	// @field Beim Lesen (Message <m DEX_QUERYOBJECTNAME>) wird hier die Größe des 
		// Zeichenkettenpuffers vorgegeben. Nach Aufruf enthält dieser Wert die
		// Anzahl der real eingelesenen Zeichen. Beim Schreiben (Message 
		// <m DEX_SETOBJECTNAME>) muß dieser Wert auf die Länge der zu 
		// schreibenden Zeichenkette gesetzt sein.
} OBJECTFEATURE;

// Struktur für PBD_Data Abfrage und Modifikation -----------------------------
typedef struct tagPBDDATA {
	DWORD dwSize;		// Größe dieser Struktur
	short pbdTyp;		// Typ: 'i' - Identifikator, 'm' - Merkmal, 'r' - Relation
	HGENERIC pbdCode;	// interner Code
	char *pbdKText;		// KurzText
	char *pbdLText;		// LangText
	short pbdTemp;		// Flag, ob temporär oder permanent (nur 'i')
	short pbdKTextLen;	// max. Länge der Texte
	short pbdLTextLen;
} PBDDATA;

// Struktur für PBD_Merkmal (erweiterte PBDDATA)
typedef struct tagPBDMERKMAL {
	DWORD dwSize;		// Größe dieser Struktur
	short pbdTyp;		// 'm' - Merkmal
	HFEATURE pbdCode;	// interner Code
	char *pbdKText;		// KurzText
	char *pbdLText;		// LangText
	short pbdReserved;	// unused
	short pbdKTextLen;	// max. Länge der Texte
	short pbdLTextLen;
	short ipbdMTyp;		// MerkmalsTyp
	short ipbdMLen;		// max. Länge des Merkmales
} PBDMERKMAL;

// Struktur für PBD_Merkmal (erweiterte PBDMERKMAL)
typedef struct tagPBDMERKMALEX {
	DWORD dwSize;		// Größe dieser Struktur
	short pbdTyp;		// 'm' - Merkmal
	HFEATURE pbdCode;	// interner Code
	char *pbdKText;		// KurzText
	char *pbdLText;		// LangText
	short pbdReserved;	// unused
	short pbdKTextLen;	// max. Länge der Texte
	short pbdLTextLen;
	short ipbdMTyp;		// MerkmalsTyp
	short ipbdMLen;		// max. Länge des Merkmales
	HOBJECTS lIdent;	// Objektklasse, zu der dieses Merkmal gehört
} PBDMERKMALEX;

// Struktur für PBD_Relation (erweiterte PBDDATA)
typedef struct tagPBDRELATION {
	DWORD dwSize;		// Größe dieser Struktur
	short pbdTyp;		// Typ: 'r' - Relation
	HRELATION pbdCode;	// interner Code
	char *pbdKText;		// KurzText
	char *pbdLText;		// LangText
	short pbdReserved;	// unused
	short pbdKTextLen;	// max. Länge der Texte
	short pbdLTextLen;
	short ipbdRTyp;		// RelationsTyp
} PBDRELATION;

#if !defined(PBDMERKMAL_SYSTEMFLAG)
#define PBDMERKMAL_SYSTEMFLAG		0x80
#define PBDMERKMAL_READONLY		0x100
#endif

// Strutur für die Verwaltung der GeoDBHeaderEntries --------------------------
typedef struct tagGEODBHDRENTRY {
	DWORD dwSize;
	char hdrKey[16];	// Schlüssel (mit ' ' auffüllen !)
	char *lphdrText;	// gesuchter/gefundener Text
	short hdrTextLen;	// BufferGröße
} GEODBHDRENTRY;

typedef struct tagGEODBHDRENTRYEX {
	DWORD dwSize;
	char hdrKey[16];	// Schlüssel (mit ' ' auffüllen !)
	char *lphdrText;	// gesuchter/gefundener Text
	short hdrTextLen;	// BufferGröße
	DWORD dwFlags;		// Flags s.u.
} GEODBHDRENTRYEX;

// Flags für GEODBHDRENTRYEX.dwFlags 
#define HEADER_NORMAL	0x00
#define HEADER_SYSTEM	0x01
#define HEADER_READONLY	0x02
#define HEADER_SYSTEMRO	0x03
#define HEADER_DYNAMIC	0x04

// Struktur, welche für DEX_QUERYOBJSTATISTIK verwendet wird ------------------
typedef struct tagOBJSTATISTIK {
	DWORD dwSize;		// Größe dieser Struktur
	HOBJECT lONr;		// ObjektNummer
	HOBJECTS lIdent;		// Identifikator
	short iObjTyp;		// ObjektTyp
	short iFlags;		// Modi von QueryObjStatistik (unused)
	long lCnt;		// Anzahl der Stützpunkte
	short iKCnt;		// Flächen: Anzahl der Konturen
} OBJSTATISTIK;

// Struktur für das Anlegen eines ObjektTemplates -----------------------------
// @struct OBJCREATE | Diese Struktur wird im Zusammenhang mit der Message
// <m DEX_MODIFYOBJGEOMETRIE> verwendet, um ein Objekt neu zu erzeugen.
// @comm Diese Struktur ist identisch mit dem Kopf aller verwandten Strukturen,
// mit deren Hilfe Objektgeometrien modifiziert (<t OBJCREATE>, <t COPYGEOMETRIE>
// oder <t TEXTGEOMETRIE>), bzw. Informationen über ein Objekt (<t OBJSTATISTIK>)
// abgefragt werden können.
// @xref <m DEX_MODIFYOBJGEOMETRIE>, <f DEX_QueryUnknownIdent>
typedef struct tagOBJCREATE {
	DWORD dwSize;	// @field Die Größe dieser Struktur.
	HOBJECT lONr;	// @field Enthält nach erfolgreichem Ausführen der Funktion
		// die Objektnummer des neu erzeugten Objektes. Enthält dieses Feld 
		// bei Funktionsaufruf eine gültige Objektnummer, so wird dieses Objekt 
		// zuerst gelöscht und an seiner Stelle ein neues Objekt erzeugt.
	HOBJECTS lIdent;	// @field Enthält den Identifikator des neu zu erzeugenden 
		// Objektes. Ist dieses Feld Null, so erhält das neue Objekt den
		// projektspezifischen Identifikator 'Unbekannte Objektklasse' 
		// (Funktion <f DEX_QueryUnknownIdent>).
	short iObjTyp;	// @field (unused)
	short iFlags;	// @field Enthält Modi von ObjCreate. Es kann folgende Werte
		// enthalten:
		// @flag OGNewObject | Es wird ein neues Objekt erzeugt (default).
		// @flag OGTempObject | Es wird ein temporäres Objekt erzeugt.
} OBJCREATE;

// Strukturen für die Abfrage/Modifikation der Objektgeometrie ----------------
typedef struct tagOBJGEOMETRIE {
	DWORD dwSize;
	HOBJECT lONr;		// ObjektNummer
	HOBJECTS lIdent;	// Identifikator
	short iObjTyp;		// ObjektTyp (Punkt, Kante, Fläche, ...)
	short iFlags;		// Modi von ModGI
//
// dieser Teil ist spezifisch für den Fall einer neuen Geometrie
	long lCnt;			// Gesamtanzahl der Stützpunkte (Größe der KoordFelder)
	short iKCnt;		// Größe des KonturFeldes
	void *pdblX;		// KoordinatenFelder (double */long *)
	void *pdblY;
	long *plCnt;		// Anzahl der Stützpunkte in Konturen
} OBJGEOMETRIE;

typedef struct tagCOPYGEOMETRIE {
	DWORD dwSize;
	HOBJECT lONr;		// ObjektNummer
	HOBJECTS lIdent;	// Identifikator
	short iObjTyp;		// ObjektTyp (Punkt, Kante, Fläche, ...)
	short iFlags;		// Modi von ModGI
//
// dieser Teil ist spezifisch für den Fall GeometrieOverlay
	HOBJECT lTargetONr;	// ObjektNummer der BezugsGeometrie
} COPYGEOMETRIE;

typedef struct tagTEXTGEOMETRIE {
	DWORD dwSize;
	HOBJECT lONr;		// ObjektNummer
	HOBJECTS lIdent;	// Identifikator
	short iObjTyp;		// ObjektTyp (Punkt, Kante, Fläche, ...)
	short iFlags;		// Modi von ModGI
//
// dieser Teil ist spezifisch für den Fall Textobjekt
	long lCnt;			// Gesamtanzahl der Stützpunkte (Größe der KoordFelder)
	short iKCnt;		// hier: (max.) Textlänge
	void *pdblX;		// KoordinatenFelder (double */long *)
	void *pdblY;
	char *pText;		// Text des Textobjektes
} TEXTGEOMETRIE;

typedef struct tagTEXTGEOMETRIEEX {
	DWORD dwSize;
	HOBJECT lONr;		// ObjektNummer
	HOBJECTS lIdent;	// Identifikator
	short iObjTyp;		// ObjektTyp (Punkt, Kante, Fläche, ...)
	short iFlags;		// Modi von ModGI
//
// dieser Teil ist spezifisch für den Fall Textobjekt
	long lCnt;			// Gesamtanzahl der Stützpunkte (Größe der KoordFelder)
	short iKCnt;		// hier: (max.) Textlänge
	void *pdblX;		// KoordinatenFelder (double */long *)
	void *pdblY;
	char *pText;		// Text des Textobjektes
	BOOL fIndObjProp;	// Text ist evtl. IndirektLabel
} TEXTGEOMETRIEEX;

// Die folgende Struktur kann anstelle einer OBJGEOMETRIE verwendet werden,
// wenn zusätzlich ein passendes Koordinatensystem benötigt wird
// Die Geometrien müssen OGConverted (double *) sein.
typedef struct tagGEOMETRIEWITHCS {
	DWORD dwSize;
	OBJGEOMETRIE *pOG;	// OBJGEOMETRIE oder TEXTGEOMETRIE[EX]
	IUnknown *pICS;		// ITRiASCS
} GEOMETRIEWITHCS;

// Werte, die in iFlags die Modi von Query/ModObjGeometrie bestimmen
#define OGConverted			0x01	// Koordinaten konvertiert/!konvertiert

#define OGNewObject			0x02	// neues Objekt generieren
#define OGModObject			0x04	// Geometrie des Objektes ersetzen
#define OGTempObject		0x08	// temporäres Objekt generieren
#define OGOverlay			0x10	// Geometrie überlagern

#define OGForceGeometry		0x20	// auch außerhalb des aktuellen DBConts importieren
#define OGAddToView			0x40	// zur aktuellen Sicht hinzufügen
#define OGForceGeoError		0x80	// Objekt wird bei Geometriefehler von GEOREIN abgewiesen

#define OGIgnoreGeometry	0x0100	// Geometrie ignorieren (nicht verändern)
#define OGIgnoreIdent		0x0200	// Identifikator ignorieren
#define OGNoExtendedErrorCheck	0x0400	// weitergehende Analysen in Georein nicht ausführen

#define OGObjectHasGeometryErrors	0x1000		// Objekt hat Geometriefehler, wurde jedoch importiert
#define OGAskWhenError		0x2000	// GeoRein soll bei fehlerhafter Geometrie nochmal nachfragen
#define OGGeometryIsChecked	0x4000	// Geometrie ist bereits getestet
#define OGNoMemoryObject	0x8000	// debugging purposes

#define OGPunkt		0
#define OGLinie		1
#define OGFlaeche	2
#define OGKreis		3
#define OGKO		4
#define OGText		5
#define OGUnknown	6
#define OGLabel		7
#define OGSachObjekt	0x80	// zusätzliches Flag (BLOB - Flag)

#define OTPunkt		0x01
#define OTLinie		0x02
#define OTFlaeche	0x04
#define OTText		0x08
#define OTKO		0x10
#define OTSachObjekt	0x20	// zusätzliches Flag (BLOB - Flag)
#define OTAll			(OTPunkt|OTLinie|OTFlaeche|OTText)

///////////////////////////////////////////////////////////////////////////////
// Virtuelle Objekte/Objektklassen in Enumeration einschließen
#define EnumVirtualData		0x80000000L

// ----------------------------------------------------------------------------
typedef struct tagRESETATTRDATA {
	HOBJECT lONr;
	void *pVI;
} RESETATTRDATA;

// Struktur, die beim Generieren eines ObjRechercheFensters benötigt wird -----
typedef struct tagCREATEOBJEKTINFO {
	DWORD dwSize;
	char *lpCaption;	// FensterCaption
	HOBJECT *plObjs;	// ObjektNummern, die angezeigt werden sollen
	short iNumObjs;		// Anzahl der ObjektNummern
	COLORREF cMColor;	// Markierungsfarbe
	POINT pntPos;		// AnfangsPosition im Hauptfenster
} CREATEOBJEKTINFO;

typedef short (CALLBACK *CMPONRPROC)(HOBJECT lONr1, HOBJECT lONr2, UINT_PTR dwData);

typedef struct tagCREATEOBJEKTINFOEX {
	DWORD dwSize;
	char *lpCaption;	// FensterCaption
	HOBJECT *plObjs;	// ObjektNummern, die angezeigt werden sollen
	short iNumObjs;		// Anzahl der ObjektNummern
	COLORREF cMColor;	// Markierungsfarbe
	POINT pntPos;		// AnfangsPosition im Hauptfenster
// zusätzliche Member #HK940920
	short m_iFlags;		// Bitmuster für die Abfrage
	HWND m_hWnd;		// evtl. FensterHandle für Target-ORFenster
	CMPONRPROC m_pCmpProc;	// evtl. Vergleichsfunktion für Reihenfolge
	UINT_PTR m_dwData;		// evtl. Daten für SortierFunktion
} CREATEOBJEKTINFOEX;

#if _TRiAS_VER >= 0x0200

typedef struct tagCREATEOBJEKTINFOEX2 {
	DWORD dwSize;
	char *lpCaption;	// FensterCaption
	HOBJECT *plObjs;	// ObjektNummern, die angezeigt werden sollen
	short iNumObjs;		// Anzahl der ObjektNummern
	COLORREF cMColor;	// Markierungsfarbe
	POINT pntPos;		// AnfangsPosition im Hauptfenster
// zusätzliche Member #HK940920
	short m_iFlags;		// Bitmuster für die Abfrage
	HWND m_hWnd;		// evtl. FensterHandle für Target-ORFenster
	CMPONRPROC m_pCmpProc;	// evtl. Vergleichsfunktion für Reihenfolge
	UINT_PTR m_dwData;		// evtl. Daten für SortierFunktion
// #HK951116
	LPUNKNOWN m_pIObjProp;	// anzuzeigende Objekteigenschaft
} CREATEOBJEKTINFOEX2;

// #HK001127
typedef struct tagCREATEOBJEKTINFOEX3 {
	DWORD dwSize;
	char *lpCaption;	// FensterCaption
	HOBJECT *plObjs;	// ObjektNummern, die angezeigt werden sollen
	short iNumObjs;		// Anzahl der ObjektNummern
	COLORREF cMColor;	// Markierungsfarbe
	POINT pntPos;		// AnfangsPosition im Hauptfenster
	short m_iFlags;		// Bitmuster für die Abfrage
	HWND m_hWnd;		// evtl. FensterHandle für Target-ORFenster
	CMPONRPROC m_pCmpProc;	// evtl. Vergleichsfunktion für Reihenfolge
	UINT_PTR m_dwData;		// evtl. Daten für SortierFunktion
	LPUNKNOWN m_pIObjProp;	// anzuzeigende Objekteigenschaft
	long lNumObjs;		// mehr Objekte möglich (iNumObjs == 0), sizeof(iNumObjs) == 2!
} CREATEOBJEKTINFOEX3;

#endif // _TRiAS_VER >= 0x0200

// Datenstrukturen für ObjPropFunc's ------------------------------------------
// @func BOOL | ENUMOBJPROPCALLBACK | Rückruf-Funktion, die durch <tr> installiert ist,
// um von einer Erweiterung für jede installierte Objekteigenschaft gerufen zu werden.
// Auf diesem Wege kann eine Erweiterung ihre derzeit aktiven Objekteigenschaften
// registrieren.<nl>Diese Funktion wird bei der Message <m DEX_ENUMEXTENSIONPROP> 
// verwendet.
// @rdesc Eine Erweiterung sollte <t true> liefern, wenn diese Message bearbeitet
// wurde, ansonsten <t false>
// @parm const char * | pFName | Der Name der zu installierenden Objekteigenschaft.
// @parm short | iFuncID | Der ID der Funktion, über den diese angesprochen werden kann.
// @parm BOOL | iNotLast | Dieser Wert gibt an, ob der aktuelle Aufruf der Funktion
// @parm void * | pData | An <tr> durchzureichende Daten.
// @xref <t ENUMOBJPROPDATA>, <m DEX_ENUMEXTENSIONPROP>
typedef BOOL (CALLBACK *ENUMOBJPROPCALLBACK)(const char *pFName, short iFuncID, BOOL iNotLast, void *pData);
typedef ENUMOBJPROPCALLBACK ENUMOBJPROPPROC;
//typedef BOOL (*ENUMOBJPROPPROC)(const char *pFName, short iFuncID, BOOL iNotLast, void *pData); // obsolete

// @struct ENUMOBJPROPDATA | Diese Datenstruktur wird verwendet, um eine Erweiterung
// aufzufordern, ihre Objekteigenschaften zu installieren (Message <m DEX_ENUMEXTENSIONPROP>).
// <nl>Die Implementation der Standard-Basisklasse <c CObjectpropertyExtension> 
// bearbeitet diese Message vollständig.
// @comm Der Wert im Feld <p pPtr> muß unverändert beim Aufruf der Enumerationsfunktion 
// (<p pFunc>) als 4. Parameter an <tr> übergeben werden.
// @xref <c CObjectpropertyExtension>, <m DEX_ENUMEXTENSIONPROP>, <f ENUMOBJPROPCALLBACK>
typedef struct tagENUMOBJPROPDATA {
	ENUMOBJPROPCALLBACK pFunc;	// @field Funktion, die durch die Erweiterung für jede 
	// zu installierende Objekteigenschaft gerufen werden soll.
	void *pPtr;			// @field An <tr> durchzureichende Daten.
} ENUMOBJPROPDATA;

typedef char * (CALLBACK *INTOBJPROPCALLBACK)(HOBJECT lONr, char *pBuffer, short iLen);
typedef INTOBJPROPCALLBACK INTOBJPROPPROC;
//typedef char * (*INTOBJPROPPROC)(long lONr, char *pBuffer, short iLen);	// obsolete

// @struct INVOKEOBJPROPDATA | Diese Datenstruktur wird verwendet, um eine Erweiterung
// aufzufordern, für ein vorgegebenes Objekt eine Objekteigenschaft zu berechnen
// (Message <m DEX_INVOKEOBJPROPFUNC>).
// @xref <m DEX_INVOKEOBJPROPFUNC>
typedef struct tagINVOKEOBJPROPDATA {
	DWORD dwSize;	// @field Die Größe dieser Struktur.
	short iFuncID;	// @field ID der zu berechnenden Objekteigenschaft. 
		// Dieser ID wurde bei der Installation der Objekteigenschaft durch 
		// die Erweiterung vorgegeben.
	HOBJECT lONr;	// @field Objektnummer des Objektes, für welches die 
		// Objekteigenschaft berechnet werden soll.
	short iBuffLen;	// @field Maximal mögliche Anzahl der in den 
		// Ergebnispuffer <p pBuff> kopierbaren Zeichen.
	char *pBuff;	// @field Ergebnispuffer, wo die Erweiterung die 
		// berechnete Objekteigenschaft ablegen muß.
} INVOKEOBJPROPDATA;

typedef struct tagINVOKEOBJPROPDATAEX {
	DWORD dwSize;
	short iFuncID;
	HOBJECT lONr;
	short iBuffLen;
	char *pBuff;
	char *pFName;
} INVOKEOBJPROPDATAEX;

typedef struct tagGETHELPTEXTDATA {
	DWORD dwSize;
	short iFuncID;		// zu rufende Funktion
	short iBuffLen;
	char *pBuff;
} GETHELPTEXTDATA;

typedef struct tagGETHELPTEXTDATAEX {
	DWORD dwSize;
	short iFuncID;		// zu rufende Funktion
	short iBuffLen;
	char *pBuff;
	char *pFName;		// FunktionsName
	char *pHelpFile;	// evtl. HelpFile
	ULONG ulHelpCtx;	// mit HelpContext
} GETHELPTEXTDATAEX;

// mögliche Sonderwerte des FunktionsParameters (sonst ObjektNummer > 0) ------
#if defined(__cplusplus)
typedef enum tagOBJPROPTYPE {
	OBJPROP_EVAL		= 1,
	OBJPROP_RESET		= 0,
	OBJPROP_CUMULATION	= -1,
	OBJPROP_COUNT		= -2,
	OBJPROP_GETHELPTEXT	= -3,
} OBJPROPTYPE;
#else
#define OBJPROP_RESET		 0L
#define OBJPROP_CUMULATION	-1L
#define OBJPROP_COUNT		-2L
#define OBJPROP_GETHELPTEXT	-3L
#endif // __cplusplus

// ----------------------------------------------------------------------------
// @struct INSTALLMENUITEM | Diese Struktur wird verwendet, um einen zusätzlichen
// Menupunkt in <tr> zu installieren.
// @xref <m DEX_MENUITEMINSTALL>, <f DEX_InstallMenuItem>
typedef struct tagINSTALLMENUITEM {
	DWORD dwSize;	// @field Größe dieser Struktur
	HDEX hDex;	// @field Erweiterung, die Behandlung vornimmt
	short iFlag;	// @field Enthält Modi von fürs Menueinhängen, 
					// kann folgende Flags enthalten:
		// @flag IMIObjWnd | Der Menupunkt wird in allen Objektrecherchefenstern
		// erzeugt. Die anderen Parameter in dieser Struktur beziehen
		// sich daher auf dieses Menu.
		// @flag IMIStartUpMenu | Der Menupunkt wird im Startmenu von <tr>
		// erzeugt.
		// @flag IMINormalMenu | Der Menupunkt wird im Projektmenu von <tr>
		// erzeugt.
	short iMenuNum;	// @field Nummer des PopupMenus, wo's hinsoll (0 ..)
	short iMenuID;	// @field MenuID dieses Punktes, 
			// <tr> addiert selbst den Menuoffset
	char *pMenuText;// @field Einzuhängender MenuText
	short iMenuPos;	// @field Stelle an der es eingehängt werden soll 
			// (-1: ans Ende des Popupmenus)
} INSTALLMENUITEM;

#define IMINormalMenu	0x00
#define IMIObjWnd		0x01
#define IMIStartUpMenu	0x02
#define IMITopLevel		0x04
#define IMIOrigMenuItem	0x80

// @struct INSTALLMENUITEM | Diese Struktur wird verwendet, um einen zusätzlichen
// Menupunkt in <tr> zu installieren.
// @xref <m DEX_MENUITEMINSTALL>, <f DEX_InstallMenuItem>
typedef struct tagINSTALLMENUITEMEX :
	public INSTALLMENUITEM
{
	HMENU hMenu;	// @field Handle eines einzuhängenden PopupMenues,
		// in diesem Fall ist iMenuID gleich 0, die Erweiterung bleibt owner 
		// dieses Handles (muß am Ende gelöscht werden)
} INSTALLMENUITEMEX;


// @struct REMOVEMENUITEM | Diese Struktur wird verwendet, um einen zusätzlich
// installierten Menupunkt wieder in <tr> zu entfernen.
// @xref <m DEX_REMOVEMENUITEM>
typedef struct tagREMOVEMENUITEM {
	DWORD dwSize;	// @field Größe dieser Struktur
	HDEX hDex;	// @field Erweiterung, die Eigner dieses Menupunktes ist
	short iFlag;	// @field false: HauptMenu, 
			// true: Objektrecherche-Menu's
	short iMenuNum;	// @field Nummer des PopupMenus, in dem sich der
			// Menupunkt befindet (0 ..)
	short iMenuID;	// @field MenuID des herauszulösende Menuitems ohne 
			// Berücksichtigung des Menuoffsets
} REMOVEMENUITEM;

// @struct REMOVEMENUITEMEX | Diese Struktur wird verwendet, um einen zusätzlich
// installierten Menupunkt wieder in <tr> zu entfernen.
// @xref <m DEX_REMOVEMENUITEM>
typedef struct tagREMOVEMENUITEMEX : 
	public REMOVEMENUITEM 
{
	short iMenuPos;	// @field Stelle an der es eingehängt werden soll 
			// (-1: ans Ende des Popupmenus)
} REMOVEMENUITEMEX;

// Strukturen zum Einhängen/Rausnehmen eines Werkzeuges -----------------------
// @struct INSTALLTOOL | Diese Struktur wird verwendet, um ein zusätzliches 
// Werkzeug in <tr> zu installieren (mit der Message <m DEX_TOOLINSTALL>).
// @xref <m DEX_TOOLINSTALL>, <m DEX_TOOLREMOVE>
typedef struct tagINSTALLTOOL {
	DWORD dwSize;	// @field Die Größe dieser Struktur.
	char *pDesc;	// @field Zeichenkette, die im Werkzeug-Menu von <tr>
			// eingehängt wird, um ein Tastatur-Interface für die
			// Werkzeugauswahl zu gewährleisten
	HBITMAP hBmp;	// @field Handle der Bitmap, welche in der Werkzeugleiste
			// angezeigt wird. Diese Bitmap wird durch <tr> freigegeben.
} INSTALLTOOL;

// SelektionsFarbe eines Objektes in einem ORFenster ändern -------------------
typedef struct tagCHANGEACTIVECOLOR {
	DWORD dwSize;
	HWND hWnd;		// FensterHandle des ORFensters
	long lONr;		// ObjektNummer des betreffenden Objektes
	COLORREF newC;		// neue/alte Farbe
} CHANGEACTIVECOLOR;	

// Identifikator modifizieren ------------------------------------------------
typedef struct tagMODOBJIDENT {
	DWORD dwSize;
	HOBJECT lONr;
	HOBJECTS lNewIdent;
	short iMode;
} MODOBJIDENT;                                                                

// Werte von iMode 
#define MODIDENT_PUNKT		0x01	// GeoTyp umklassifizieren
#define MODIDENT_LINIE 		0x02
#define MODIDENT_FLAECHE	0x04
#define MODIDENT_TEXT		0x08
#define MODIDENT_KOMPLEX	0x10
#define MODODENT_SACH		0x20

#define MODIDENT_TYP		0x3f

#define MODIDENT_TEMP		0x100	// temporär umklassifizieren
#define MODIDENT_ADDTOVIEW	0x200	// zur Sicht hinzufügen

///////////////////////////////////////////////////////////////////////////////
// Zuordnungsobjektklassen (#HK000301)
typedef struct tagOBJECTCLASSPAIR {
	DWORD dwSize;
	HOBJECT lONr;		// [in] Objektnummer 
	HOBJECTS lIdent;	// [in] Zuordnungsobjektklasse
} OBJECTCLASSPAIR;

// Objekt zu Zuordnungsobjektklasse hinzufügen, DEX_ADDOBJECT2CLASS
typedef struct tagADDOBJECTTOCLASS {
	DWORD dwSize;
	HOBJECT lONr;		// [in] Objektnummer 
	HOBJECTS lIdent;	// [in] Zuordnungsobjektklasse
	int iMode;			// [in] Modi 'MODIDENT_...'
	HOBJECT *plNewONr;	// [out] Objektnummer des neu erzeugten Zuordnungsobjektes
	BOOL fUndoRedo;		// [in] UndoRedo verwenden
} ADDOBJECTTOCLASS;

// Objekt aus Zuordnungsobjektklasse herauslösen, DEX_DELETEOBJECTFROMCLASS
typedef struct tagDELOBJECTFROMCLASS {
	DWORD dwSize;
	HOBJECT lONr;		// [in] Objektnummer 
	HOBJECTS lIdent;		// [in] Zuordnungsobjektklasse
	BOOL fUndoRedo;		// [in] UndoRedo verwenden
} DELOBJECTFROMCLASS;

// Zugehörigkeit eines Objektes zu Zuordnungsobjektklasse feststellen, DEX_OBJECTISINCLASS
typedef struct tagISOBJECTINCLASS {
	DWORD dwSize;
	HOBJECT lONr;		// [in] Objektnummer 
	HOBJECTS lIdent;		// [in] Zuordnungsobjektklasse
	HOBJECT *plONrMapped;	// [out, retval] Objektnummer des gegebenen Objektes innerhalb der Objektklasse
	BOOL fUndoRedo;		// [in] UndoRedo verwenden
} ISOBJECTINCLASS;

///////////////////////////////////////////////////////////////////////////////
// DEX_RELATEDDATASOURCENAME
typedef struct tagRELATEDDATASOURCENAME {
	DWORD dwSize;
	const char *pcTargetName;	// [in] Bezugsansicht
	char *pDataSourceName;		// [out] Buffer enthält hinterher evtl. Ursprungsdatenquellennamen
	size_t iLen;				// [in] sizeof(pDataSourceName)
} RELATEDDATASOURCENAME;

// Flags für <e ENUMLONGKEYEX.eData> bei DEX_ENUMCLASSESFROMOBJECT
#define CFO_ActViewOnly		0x01	// lediglich Objektklassen der aktuellen Ansicht enumerieren
#define CFO_QueryDefsOnly	0x02	// lediglich Zuordnungsobjektklassen enumerieren
#define CFO_NativeDefsOnly	0x04	// lediglich Originalobjektklasse enumerieren

///////////////////////////////////////////////////////////////////////////////
// KoordinatenTransformation (DCtoOC und OCtoDC) 
typedef struct tagCOORDCONVERT {
	POINT *lpPt;	// POINT
	long *lpPkt;	// Punkt !!
} COORDCONVERT;

// KoordinatentransformationsStruktur -----------------------------------------
typedef struct tagCOORDTRANSFORM {	// RCtoOC oder OCtoRC
	DWORD dwSize;
	long *m_Pts;		// DatenbasisKoordinaten (Punkt!)
	double *m_rcPts;	// RealKoordinaten
} COORDTRANSFORM;

typedef struct tagCOORDTRANSFORMEX {	// RCtoOC oder OCtoRC
	DWORD dwSize;
	long *m_Pts;		// DatenbasisKoordinaten (Punkt!)
	double *m_rcPts;	// RealKoordinaten
	IUnknown *m_pICS;		// Koordinatensystem für RealKoordinaten
} COORDTRANSFORMEX;

// Enumeration aller Objekte der aktuellen Sicht, die einen BildSchirmPunkt
// überdecken
typedef BOOL (*FINDOBJECTPROC)(HOBJECT Key, RECT Rc, void *pData);
typedef BOOL (CALLBACK *FINDOBJECTCALLBACK)(HOBJECT Key, RECT Rc, void *pData);

typedef struct tagFINDOBJECT {
	DWORD dwSize;
	POINT Pt;			// gegebener BildschirmPunkt
	short iFOMode;		// gesuchte Objekttypen
	FINDOBJECTPROC eFcn;	// zu rufende Funktion
	void *pData;		// durchgereichte Daten
} FINDOBJECT;

// gesuchte Objekttypen (in iFOMode)
#define FOPunkt		0x01
#define FOKante		0x02
#define FOFlaeche	0x04
#define FOText		0x08

// Nachfrage bzw. Beeinflussen der Anzeige recherierter Objekte in einem
// Objektrecherchefenster
typedef struct tagRECHOBJECT {
	DWORD dwSize;
	HOBJECT lONr;		// ObjektNummer
	HOBJECTS lIdent;		// Identifikator
	char *lpText;		// anzuzeigender Text
	short iTextLen;		// Größe des TextBuffers
	short iOTyp;		// ObjektTyp
	short iFlags;		// anzuzeigende Informationen
} RECHOBJECT;

//////////////////////////////////////////////////////////////////////////////
// Ersetzen eines Eintrages in einem ObjRechWnd durch ein anderes Objekt
typedef struct tagREPLACEOBJECT {
	DWORD dwSize;
	HOBJECT lONr;
	HOBJECT lNewONr;
} REPLACEOBJECT;

// Flags, die in iFlags gesetzt werden können --------------------------------
#define ROHideObjNr	0x0001	// _jetzt_: Datasource nicht anzeigen
#define ROHideDatasource	ROHideObjNr
#define ROHideIdent	0x0002	// Identifikator nicht anzeigen
#define ROHideObjTyp	0x0004	// ObjTyp nicht anzeigen
#define ROHideText	0x0008	// Text nicht anzeigen
#define ROHideFlags 	0x000f

#define ROSortObjNr	0x0010	// _jetzt_: sortieren nach Datasource
#define ROSortDatasource	ROSortObjNr
#define ROSortIdent	0x0020	// Identifikator
#define ROSortObjTyp	0x0040	// ObjektTyp
#define ROSortText	0x0080	// angezeigtem Text
#define ROSortFlags	0x00f0

#define ROShowHidden	0x0100	// ausgeblendete Objekte mit anzeigen
#define ROCreateHidden	0x0200	// Fenster erzeugen aber nicht anzeigen
#define ROAddPureObjects	0x0400	// lediglich angegebene Objekte hinzufügen (evtl. zugehörige Zuordnungsobjekte nicht)
#define ROForceNoCallback	0x0800	// Texte der Einträge sofort generieren (nicht optimiert erst bei Bedarf)

#define RODefaultFlags	ROSortIdent

// Flags für DEX_RECHOBJECTSTATUS --------------------------------------------
#define RSNothing 	0x0000	// nicht in ORFenster enthalten
#define RSListed	0x0100	// in ORFenster enthalten
#define RSSelected	0x0200	// in ORFenster selektiert
#define RSActivated	0x0400	// in ORFenster aktiviert

#define RSFillIdent	0x1000	// Identifikator liefern
#define RSFillText	0x2000	// Text liefern
#define RSFillOTyp	0x4000	// OTyp liefern

// Relationen ----------------------------------------------------------------
// DEX_MODRELATION
typedef struct tagMODRELATION {
	DWORD dwSize;
	HOBJECT lPONr;		// PrimärObjekt
	HOBJECT lSONr;		// SekundärObjekt
	HRELATION lRCode;	// RelationsCode
	short iRTyp;		// RelationsTyp
} MODRELATION;

typedef struct tagMODRELATIONEX {
	DWORD dwSize;
	HOBJECT lPONr;		// PrimärObjekt
	HOBJECT lSONr;		// SekundärObjekt
	HRELATION lRCode;	// RelationsCode
	short iRTyp;		// RelationsTyp
	BOOL fUndo;			// Undo durchführen
} MODRELATIONEX;

// DEX_DELRELATION
typedef struct tagDELRELATION {
	DWORD dwSize;
	HOBJECT lPONr;		// PrimärObjekt
	HOBJECT lSONr;		// SekundärObjekt
	HRELATION lRCode;	// RelationsCode
	short iRTyp;		// RelationsTyp
} DELRELATION;

typedef struct tagDELRELATIONEX {
	DWORD dwSize;
	HOBJECT lPONr;		// PrimärObjekt
	HOBJECT lSONr;		// SekundärObjekt
	HRELATION lRCode;	// RelationsCode
	short iRTyp;		// RelationsTyp
	BOOL fUndo;			// Undo durchführen
} DELRELATIONEX;

// Enumeration aller Relationen eines Objektes --------------------------------
// DEX_ENUMRELATIONOBJS -------------------------------------------------------
typedef BOOL (*ENUMRELOBJPROC)(HOBJECT lONr, HRELATION lRCode, short iRTyp, void *pData);
typedef BOOL (CALLBACK *ENUMRELOBJCALLBACK)(HOBJECT lONr, HRELATION lRCode, short iRTyp, void *pData);

typedef struct tagENUMRELATIONOBJS {
	DWORD dwSize;
	HOBJECT lONr;		// Bezugsobjekt, für das Relationen geliefert werden
	HRELATION lRCode;		// zu untersuchende Relation (-1: alle)
	short iRTyp;		// zu untersuchende RelationsTypen
	ENUMRELOBJPROC eFcn;	// zu rufende Funktion
	void *pData;		// durchgereichte Daten
} ENUMRELATIONOBJS;

// RelationsTypen ------------------------------------------------------------
#define RTKomplexO	0x01	// Komplexrelation lPONr -> lSONr
#define RTKomplexU	0x02	// inv. Komplexrelation lPONr <- lSONr
#define RTGleich	0x04	// Gleichrangige Relation
#define RTBegleitO	0x08	// BegleitRelation (hat BegleitObjekt)
#define RTBegleitU	0x10	// BegleitRelation (ist Begleitobjekt)


// Strukturen für das Modifizieren/Abfragen von VisInfo's --------------------
#if !defined(VISNAMESIZE)
#define VISNAMESIZE	32
#endif

typedef struct tagVISINFO {
#if _TRiAS_VER >= 0x0300
	DWORD dwSize;
#endif // _TRiAS_VER >= 0x0300

	short m_Priority;	// Priorität
	short m_Style;		// DarstellungsStyle
	char m_VisName[VISNAMESIZE];		// evtl. Typname (ohne '\0')
	COLORREF m_C;		// Primärfarbe
//
#if _TRiAS_VER >= 0x0300
	char m_fLocatable;	// recherchierbar
	char m_fVisible;	// sichtbar
	char m_GeomName[VISNAMESIZE];		// evtl. GeometrieFeldName (ohne '\0')
#if defined(__cplusplus)
	tagVISINFO() { memset(this, '\0', sizeof(tagVISINFO)); dwSize = sizeof(tagVISINFO); }
#endif // __cplusplus
#endif // _TRiAS_VER >= 0x0300
} VISINFO;

typedef struct tagDVISINFO {
	VISINFO m_VI;		// allgemeine VisInfo
	short m_iDefTypes;	// sonstige IdentGeoTypen
#if defined(__cplusplus) && _TRiAS_VER >= 0x0300
	tagDVISINFO() { m_VI.dwSize = sizeof(tagDVISINFO); }
#endif // defined(__cplusplus) && _TRiAS_VER >= 0x0300
} DVISINFO;

typedef struct tagPVISINFO {
	VISINFO m_VI;		// allgemeine VisInfo
	SIZE m_Size;		// Punktgröße
	short m_iRot;		// Drehwinkel (#HK951015)
	COLORREF m_SecC;	// zweite Farbe (#HK951102)
#if defined(__cplusplus) && _TRiAS_VER >= 0x0300
	tagPVISINFO() { m_VI.dwSize = sizeof(tagPVISINFO); }
#endif // defined(__cplusplus) && _TRiAS_VER >= 0x0300
} PVISINFO;

typedef struct tagLVISINFO {
	VISINFO m_VI;		// allgemeine VisInfo
	short m_Width;		// LinienBreite
#if defined(__cplusplus) && _TRiAS_VER >= 0x0300
	tagLVISINFO() { m_VI.dwSize = sizeof(tagLVISINFO); }
#endif // defined(__cplusplus) && _TRiAS_VER >= 0x0300
} LVISINFO;

typedef struct tagFVISINFO {
	VISINFO m_VI;		// allgemeine VisInfo
	COLORREF m_FC;		// Füllfarbe
	short m_iWidth;		// Konturdicke (#HK931218)
	short m_iAttrEx;	// (zusätzliche) Attribute
#if defined(__cplusplus) && _TRiAS_VER >= 0x0300
	tagFVISINFO() { m_VI.dwSize = sizeof(tagFVISINFO); }
#endif // defined(__cplusplus) && _TRiAS_VER >= 0x0300
} FVISINFO;

typedef struct tagTVISINFO {
	VISINFO m_VI;		// allgemeine VisInfo
	SIZE m_Size;		// TextGröße
	short m_Type;		// FontArt
	short m_Rot;		// Drehwinkel
	short m_Orient;		// BuchstabenNeigung
#if defined(__cplusplus) && _TRiAS_VER >= 0x0300
	tagTVISINFO() { m_VI.dwSize = sizeof(tagTVISINFO); }
#endif // defined(__cplusplus) && _TRiAS_VER >= 0x0300
} TVISINFO;

// DatenStruktur, die zum Datentransfer bezüglich einer VisInfo verwendet wird 
typedef struct tagHANDLEVISINFO {	// Abfrage/Modifikation 
	DWORD dwSize;
	HOBJECT m_lONr;		// Target (ObjektNummer)
	HOBJECTS m_lIdent;		// Identifikator
	short m_iVTyp;		// VisInfoTyp
	short m_fFlags;		// zu ändern bzw. geändert
	char *m_pDesc;		// beschreibender Text
	char *m_pView;		// evtl. SichtName (aktuelle Sicht: NULL)
	VISINFO *m_pVI;		// generischer Pointer auf VisInfo
	HWND m_hWnd;		// als ParentWindow verwenden	
} HANDLEVISINFO;

///////////////////////////////////////////////////////////////////////////////
// erweiterte HANDLEVISINFO, die zusätzlich ExtendedObjVisInfo's enthält
typedef struct tagHANDLEVISINFOEX {
	DWORD dwSize;
	HOBJECT m_lONr;		// Target (ObjektNummer)
	HOBJECTS m_lIdent;		// Identifikator
	short m_iVTyp;		// VisInfoTyp
	short m_fFlags;		// zu ändern bzw. geändert
	char *m_pDesc;		// beschreibender Text
	char *m_pView;		// evtl. SichtName (aktuelle Sicht: NULL)
	VISINFO *m_pVI;		// generischer Pointer auf VisInfo
	HWND m_hWnd;		// als ParentWindow verwenden	
	char *m_pModule;	// (alter) Modulname des VisModules
	char *m_pInfo;		// VisModul-spezifische VisInfo
} HANDLEVISINFOEX;

// Laden/Entladen einer Erweiterung von außen --------------------------------
typedef struct tagLOADEXTENSIONEX {
	const char *m_pDesc;
	const char *m_pName;
	short m_iMode;
	BOOL m_fGlobal;
} LOADEXTENSIONEX;
// die Modi in m_iMode entsprechen denen von TRIASLOADEX

// @xref <m DEX_LOADEXTENSION2>, <m DEX_UNLOADEXTENSION2>
typedef struct tagLOADEXTENSION2 {
	DWORD dwSize;
	const char *m_pDesc;
	const char *m_pName;
	int m_iMode;
	BOOL m_fGlobal;			// die Modi in m_iMode entsprechen denen von TRIASLOADEX
	IUnknown *m_pIUnk;		// evtl. vorinstantiierte Erweiterung
} LOADEXTENSION2;

// Neu anlegen einer GeoDB/IdentsDB ------------------------------------------
typedef struct tagCREATEDB {
	DWORD dwSize;
	char *m_pName;
	char *m_pUser;
	char *m_pPassWd;
	short m_iMode;		// OpenMode (OM_...) | DBV...
} CREATEDB;

typedef struct tagCREATEDBEX {
	DWORD dwSize;
	char *m_pName;
	char *m_pUser;
	char *m_pPassWd;
	short m_iMode;		// OpenMode (OM_...) | DBV...
	LPSTORAGE m_pIStorage;
	const CLSID *m_pClsID;	// ClassID, (NULL für CLSID_DirisProject)
	LPCSTR m_pCFStr;	// ClipboardFormat (NULL für TRiAS.Document.2)
} CREATEDBEX;

#define DBVNormal	0x0000		// Trias1.20 Projekt
#define DBVCompFile	0x1000		// Trias1.30 Projekt
#define DBVCompatible	0x2000	// TRiAS1.30 16 Bit kompatibel
#define DBVFlags	0xf000		// Flags für VersionsKennung

// Rendering der GeoDB in einen vorgegeben DeviceContext ---------------------
#if !(defined(_OLE2_H_) || _TRiAS_VER >= 0x0200)
typedef struct tagPOINTL {
	long x;
	long y;
} POINTL;

typedef struct tagRECTL {
	long left;
	long top;
	long right;
	long bottom;
} RECTL;
#endif // !(defined(_OLE2_H_) || _TRiAS_VER >= 0x0200)

typedef struct tagRENDERGEODB {
	DWORD dwSize;
	HDC m_hDC;			// AusgabeDC
	HDC m_hTargetDC;	// TargetDC
	RECTL m_rclFrame;	// Ausgabebereich
	RECTL m_rclGeoDB;	// Ausgabeausschnitt
	RECTL m_rclClipBox;	// ClippingRechteck
} RENDERGEODB;

typedef struct tagRENDERGEODB2 {
	DWORD dwSize;
	HDC m_hDC;			// AusgabeDC
	HDC m_hTargetDC;	// TargetDC
	RECTL m_rclFrame;	// Ausgabebereich
	RECTL m_rclGeoDB;	// Ausgabeausschnitt
	RECTL m_rclClipBox;	// ClippingRechteck
	int m_iFlags;		// zusätzliche Flags
} RENDERGEODB2;

#define RDB_CoordsScaled 1	// Koordinaten sind skaliert (interne DB-Koords)

// Besorgen des Textes eines Textobjektes ------------------------------------
typedef struct tagGETTEXTDATA {
	DWORD dwSize;
	HOBJECT m_lONr;
	char *m_pText;
	short m_iLen;
} GETTEXTDATA;

// Wegschreiben eines neuen Textes für ein Textobjekt (DEX_PUTTEXTOBJECTTEXT)
typedef struct tagPUTTEXTDATA {
	DWORD dwSize;
	HOBJECT m_lONr;
	const char *m_pcText;
} PUTTEXTDATA;

typedef struct tagPUTTEXTDATAEX {
	DWORD dwSize;
	HOBJECT m_lONr;
	const char *m_pcText;
	BOOL m_fIndObjProp;		// Textobjekt ist Labelobjekt
} PUTTEXTDATAEX;

// BeschreibungsInfo für Sicht -----------------------------------------------
// Messages: DEX_MODVIEWDESCRIPTION, DEX_QUERYVIEWDESCRIPTION
typedef struct tagVIEWDESC {
	DWORD m_dwSize;
	char *m_pView;
	char *m_pDesc;
	short m_iLen;
} VIEWDESC;

#if _TRiAS_VER < 0x0300
// Enumeration der topologischen Relationen ----------------------------------
// Message: DEX_ENUMTOPRELATIONS
typedef struct tagENUMTOPRELS {
	DWORD m_dwSize;
	HOBJECT m_lONr;		// zu untersuchendes Objekt
	ENUMLONGKEYPROC m_eFcn;	// zu rufende Funktion
	DWORD m_dwData;		// durchgereichte Daten
	short m_iMode;		// weitere Flags
	char *m_pView;		// NULL: aktuelle Sicht verwenden
} ENUMTOPRELS;

#define ETRAnalyzeView	0x01	// zusätzlich über Sicht filtern
#endif // _TRiAS_VER < 0x0300

// @struct VIEWIDENTOBJECT | Diese Struktur wird in Funktionen verwendet, die
// als Parameter eine Ansicht, einen Identifikator/ ein Objekt und/oder einen
// Objekttyp verlangen.
// @comm Es sind im allgemeinen nicht alle Felder dieser Struktur zu belegen.
// Meist sind je nach Funktion nur die Felder <p m_plIdent> und <p m_iOTyp> oder 
// das Feld <p m_lONr> belegt. Die jeweils nicht benutzten Felder sollten 
// ausgenullt sein.
// @xref <m DEX_IDENTADDTOVIEW>, <m DEX_DELETEIDENTFROMVIEW>, <m DEX_HASVIEWIDENT>, <m DEX_HASVIEWOBJECT>
typedef struct tagVIEWIDENTOBJECT {
	DWORD dwSize;	// @field Die Größe dieser Struktur.
	char *m_pView;	// @field Der Sichtname der Ansicht, auf die 
		// sich der Funktionsaufruf bezieht. NULL bedeutet, daß die 
		// aktuelle Ansicht verwendet werden soll.
	HOBJECTS m_lIdent;	// @field Der Identifikator, für den die
		// Funktion ausgeführt werden soll.
	HOBJECT m_lONr;	// @field Die Objektnummer des Objektes, für 
		// welches die Funktion ausgeführt werden soll.
	short m_iOTyp;	// @field Die Objekttypen, für die die Funktion
		// ausgeführt werden soll. Dieses Feld kann folgende Flags oder
		// eine ihrer Kombinationen enthalten:
} VIEWIDENTOBJECT;
// @flag OTPunkt	| Punktobjekte behandeln.
// @flag OTLinie	| Linienobjekte behandeln.
// @flag OTFlaeche	| Flächenobjekte behandeln.
// @flag OTText		| Textobjekte behandeln.
// @flag OTKO		| Komplexobjekte behandeln (not implemented yet, soory).
// @flag OTSachObjekt	| Sachobjekte behandeln (not implemented yet, soory).

// @struct RENAMEVIEW | Diese Struktur wird verwendet, um eine Ansicht umzubenennen.
// @comm Wenn der Name der umzubenennenden Ansicht nicht vorgegeben wird, so wird
// die aktuelle Ansicht umbenannt.
// @xref <m DEX_VIEWRENAME>
typedef struct tagRENAMEVIEW {
	DWORD dwSize;		// @field Die Größe dieser Struktur.
	const char *m_pOldName;	// @field Der Name der umzubenennenden Ansicht.
	const char *m_pNewName;	// @field Der neue Name, den die Ansicht erhalten soll.
} RENAMEVIEW;

// @struct VIEWCREATED | Diese Sruktur wird als Parameter der Notifikation 
// <m DEX_VIEWCREATED> verschickt.
// @comm Diese Notifikation getattet es einer Erweiterung zusätzliche Aktionen
// vorzunehmen, die die neu angelegte Sicht betreffen.
// @xref <m DEX_VIEWCREATED>
typedef struct tagVIEWCREATED {
	DWORD dwSize;		// @field Die Größe dieser Struktur.
	const char *m_pTarget;	// @field Der Name der Sicht, die als Bezugssicht verwendet wird.
	const char *m_pNewName;	// @field Der Name der neu angelegten Sicht.
	short m_iMode;		// @field Enthält die Modi, die beim Anlegen der neuen
		// Sicht verwendet wurden. Dieses Feld kann folgende Werte bzw. ihre
		// Kombination annehmen:
} VIEWCREATED; 
// @flag VCUseTargetView | Es soll die Visualisierungs-Information der Bezugssicht
// verwendet werden.
// @flag VCDeleteTarget | Die Bezugssicht soll gelöscht werden.
// @flag VCFeaturesMoved | Die neue Sicht hat bereits die Eigenschaften (Merkmale und Relationen)
// de Bezugssicht übernommen.
#define VCUseTargetView	0x01
#define VCDeleteTarget	0x02
#define VCFeaturesMoved	0x04

// @struct COPYVISINFO | Diese Struktur wird als Parameter der Notifikation
// <m DEX_N_COPYVISINFO> verschickt.
// @comm Diese Notifikation wird verschickt, wenn die Darstellungsparameter einer
// Objektklasse aus einer Ansicht in eine andere übernommen wurden und ermöglicht
// z.B. die gleichzeitige Übernahme der Objektbezogenen Darstellungsparameter.
typedef struct tagCOPYVISINFO :
	public tagVIEWCREATED
{
	HOBJECTS lIdent;	// @field Objektklasse, für die die Darstellungsparameter kopiert wurden
	int iOTyp;			// @field zu behandelnde Objekttypen
} COPYVISINFO;

// Flags (Returnkonstanten) für DEX_VIEWCREATEOPT ----------------------------
#define CVError		0
#define CVCreated	1
#define CVExists	2

//////////////////////////////////////////////////////////////////////////////
// Struktur für DEX_CLIPOBJECTSET
// @struct CLIPOBJECTSET | Diese Struktur wird als Parameter der Message
// <m DEX_CLIPOBJECTSET> verschickt.
// @comm Diese Message getattet es einer Erweiterung das Clipping Objekt für 
// eine Ansicht zu modifizieren.
// @xref <m DEX_CLIPOBJECTSET>
typedef struct tagCLIPOBJECTSET {
	DWORD dwSize;			// @field Die Größe dieser Struktur.
	const char *m_pcView;	// @field Der Name der Anicht, die bearbeitet 
		// werden soll (wenn NULL, dann aktuelle Ansicht verwenden)
	HOBJECT m_lONr;			// @field Objektnummer des als Clipping Objekt 
		// zu verwendeneden Objektes
} CLIPOBJECTSET;

//////////////////////////////////////////////////////////////////////////////
// Struktur für DEX_SHOWOBJPROP
// @struct SHOWOBJPROP | Diese Sruktur wird als Parameter der Message
// <m DEX_SHOWOBJPROP> verschickt (bei setzen im ORFenster).
// @comm Diese Message getattet es einer Erweiterung die aktuell in einem 
// Recherchefenster angezeigte Objekteigenschaft zu modifizieren.
// @xref <m DEX_SHOWOBJPROP>
typedef struct tagSHOWOBJPROP {
	DWORD dwSize;			// @field Die Größe dieser Struktur.
	IUnknown *m_pIObjProp;	// @field Die anzuzeigende Objekteigenschaft
	int m_iFlags;			// @field Zusätzliche Flags, die weiter Optionen
		// vorgeben können.
} SHOWOBJPROP;
#define SOPLeaveOldProps	0x00	// @flag SOPLeaveOldProps | Objekteigenschaft nur für neu hinzukommende Objekte verwenden.
#define SOPReloadProps		0x01	// @flag SOPReloadProps | Objekteigenschaften für alle Objekte neu lesen.

///////////////////////////////////////////////////////////////////////////////
// DEX_SHOWOBJEPROPEX, DEX_QUERYOBJPROPEX
// @struct SHOWOBJPROPEX | Diese Struktur wird verwendet, um ansichtsbezogen die
// anzuzeigende Objekteigsnchaft zu setzen bzw. abzufragen
// @xref <m DEX_SHOWOBJPROPEX>, <m DEX_QUERYOBJPROPEX>
typedef struct tagSHOWOBJPROPEX {
	DWORD dwSize;
	LPCSTR pcView;			// @field Ansicht, für die die anzuzeigende 
		// Objekteigenschaft gesetzt bzw. abgefragt werden soll [in]
	LPSTR pObjProp;			// @field Die anzuzeigenden Objekteigenschaft ([in] 
		// oder [out] je nach Kontext)
	int iLen;				// @field Die Bufferlänge für pObjProp (bei 
		// <m DEX_QUERYOBJPROPEX>)
	int iFlags;				// @field Bei Recherchen anzuzeigende Informationen
		// @xref ROHideObjNr etc.
} SHOWOBJPROPEX;

//////////////////////////////////////////////////////////////////////////////
// DEX_IDENTFROMCLASS
typedef struct tagIDENTFROMCLASS {
	DWORD dwSize;
	LPCSTR pcClass;		/*[in]*/
	HOBJECTS ulIdent;	/*[out]*/
	BOOL fCreateNew;	/*[in]*/
} IDENTFROMCLASS;

//////////////////////////////////////////////////////////////////////////////
// DEX_CLASSFROMIDENT
typedef struct tagCLASSFROMIDENT {
	DWORD dwSize;
	HOBJECTS ulIdent;	/*[in]*/
	LPSTR pClass;		/*[out]*/
	int iBuffLen;		/*[in,out]*/
} CLASSFROMIDENT;

//////////////////////////////////////////////////////////////////////////////
// DEX_MODOBJCLASSCODE
typedef struct tagMODOBJCLASSCODE {
	DWORD dwSize;
	HOBJECTS ulIdent;	/*[in]*/
	LPCSTR pcClass;		/*[in]*/
	BOOL fOverWrite;	/*[in]*/
} MODOBJCLASSCODE;

///////////////////////////////////////////////////////////////////////////////
// Flags für QueryMode/SetMode 
#define QMSysAdmin			0x01	// SysAdminMode aktiv
#define QMAutomation		0x02	// /Automation auf CmdLine
#define QMEmbedding			0x04	// /Embedding auf CmdLine
#define QMTipOfTheDay		0x08	// -t auf CmdLine
#define QMShowSysFeatures	0x10	// Systeminterne Merkmale anzeigen
#define QMShowDataTips		0x20	// DataTips anzeigen

///////////////////////////////////////////////////////////////////////////////
// Konstanten für die Verwaltung des TipOfTheDay 
#define TOTD_LookAtRegistry	0x00	// Voreinstellungen verwenden
#define TOTD_ForceNoTips	0x01	// auf keinen Fall Tips anzeigen
#define TOTD_ForceTips		0x02	// auf jeden Fall Tips anzeigen
#define TOTD_ForceNoWizard	0x04	// auf keinen Fall Wizard anzeigen

///////////////////////////////////////////////////////////////////////////////
// Priority abfragen/einstellen
// @xref <m DEX_QUERYIDENTPRIORITY>, <m DEX_MODIFYIDENTPRIORITY>
typedef struct tagIDENTPRIORITY {
	DWORD dwSize;
	HOBJECTS ulIdent;	/*[in]*/
	int iVisType;		/*[optional,in]*/
	HOBJECT lONr;		/*[optional,in]*/
	LPCSTR pcView;		/*[optional,in]*/
	int iPriority;		/*[in] (Set) or [out] (Get)*/
} IDENTPRIORITY;

///////////////////////////////////////////////////////////////////////////////
// Visualles Aktivieren/Deaktivieren eines Objektes
// @xref <m DEX_OBJECTSELECTED>, <m DEX_OBJECTUNSELECTED>
typedef struct tagACTIVATEOBJECT {
	DWORD dwSize;
	HOBJECT lONr;			/*[in]*/
	COLORREF crAct;		/*[in]*/
} ACTIVATEOBJECT;

typedef struct tagACTIVATEOBJECTEX {
	DWORD dwSize;
	HOBJECT lONr;			/*[in]*/
	COLORREF crAct;		/*[in]*/
	BOOL fAssoc;		/*[in], true: evtl. abhängige Objekte ebenfalls kennzeichnen */
} ACTIVATEOBJECTEX;

///////////////////////////////////////////////////////////////////////////////
// #WM970814
typedef struct tagOBJECTSPLITTED {
	DWORD dwSize;
	HOBJECT m_lONrOrig;	// Ursprungsobjekt
	HOBJECT m_lONrNew1;	// neues Objekt 1
	HOBJECT m_lONrNew2;	// neues Objekt 2
} OBJECTSPLITTED;

///////////////////////////////////////////////////////////////////////////////
// Struktur, um ein Objektanzahl abzufragen 
// @xref <m DEX_QUERYIDENTOBJECTCOUNT>
typedef struct tagIDENTOBJECTCOUNT {
	DWORD dwSize;
	HOBJECTS ulIdent;	// Identifikator
	int iOTypes;		// Objekttypen (OTPunkt| ...)
} IDENTOBJECTCOUNT;

///////////////////////////////////////////////////////////////////////////////
// Struktur, um ein Objektanzahl abzufragen 
// @xref <m DEX_QUERYIDENTOBJECTCOUNT>
typedef struct tagIDENTOBJECTCOUNTEX {
	DWORD dwSize;
	HOBJECTS ulIdent;	// Identifikator
	int iOTypes;		// Objekttypen (OTPunkt| ...)
	long lPoints;		// [out] Anzahl der Punktobjekte
	long lLines;		// [out] Anzahl der Linienobjekte
	long lAreas;		// [out] Anzahl der Flächenobjekte
	long lTexts;		// [out] Anzahl der Textobjekte
	long lComplex;		// [out] Anzahl der Objekte mit Komplexgeometrien
} IDENTOBJECTCOUNTEX;

///////////////////////////////////////////////////////////////////////////////
// Verwaltung des ObjectGUID's
// @xref <m DEX_QUERYOBJECTGUID>, <m DEX_FINDOBJECTGUID>, <m DEX_SETOBJECTGUID>
typedef struct tagOBJECTGUID {
	DWORD dwSize;
	HOBJECT lONr;		// ObjektNummer
	struct _GUID guid;	// zugehöriger Guid
} OBJECTGUID;

///////////////////////////////////////////////////////////////////////////////
// Verwaltung der MRUItems
// @xref <m DEX_QUERYMRUITEM>, <m DEX_DELETEMRUITEM>, <m DEX_ADDMRUITEM>
typedef struct tagADDMRUITEM {
	DWORD dwSize;
	LPCSTR pcName;		// ProjektName
	BOOL fRO;			// RO geöffnet
	BOOL fStartup;		// StartUp oder ProjektMenu
} ADDMRUITEM;

typedef struct tagGETMRUITEM {
	DWORD dwSize;
	UINT uiMenuID;		// MenuID
	LPSTR pName;		// ProjektName
	int iLen;			// sizeof(pName)
	BOOL fRO;			// RO geöffnet
	BOOL fStartup;		// StartUp oder ProjektMenu
} GETMRUITEM;

typedef struct tagDELMRUITEM {
	DWORD dwSize;
	UINT uiMenuID;		// MenuID
	BOOL fStartup;		// StartUp oder ProjektMenu
} DELMRUITEM;

/////////////////////////////////////////////////////////////////////////////
// Abfrage von Info's über eine Extension
// @xref <m DEX_QUERYEXTENSIONINFO>
typedef struct tagEXTENSIONINFO {
	DWORD dwSize;
	LPSTR pcDLLName;	// [in] ProgID der zu untersuchenden Erweiterung
	HDEX hDex;			// [out] InstanceHandle der Erweiterung
	LPSTR pName;		// [out] Name der Erweiterung
	int iLen;			// [in, out] sizeof(pName)
	DWORD rgFlags;		// [out] Flags dieser Erweiterung (EXTENSIONFLAGS)
	int iLoadState;		// [out] LadeStatus
} EXTENSIONINFO;

// @xref <m DEX_QUERYEXTENSIONPTR>
typedef struct tagEXTENSIONPTR {
	DWORD dwSize;
	LPCSTR pcDLLName;	// [in] ProgID der zu untersuchenden Erweiterung
	IUnknown **ppIUnk;	// [out] ITriasExtension **
} EXTENSIONPTR;

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaft wurde modifiziert
typedef struct tagFEATUREMODIFIED {
	DWORD dwSize;
	LONG lONr;			// [in] Objektnummer des modifizierten Objektes
	LPCSTR pcName;		// [in] Name der modifizierten Objekteigenschaft
} FEATUREMODIFIED;

///////////////////////////////////////////////////////////////////////////////
// Objektklassen maßstabsbezogen ein/ausblenden
typedef struct tagIDENTSCALEDATA {
	DWORD dwSize;
	LPCSTR pcView;		// [in] Ansicht (NULL entspricht aktueller Ansicht)
	HOBJECTS lIdent;	// [in] untersuchter Identifikator
	int iVTyp;			// [in] interessierender Visualisierungstyp (VisInfoTyp)
	LONG lUpperScale;	// [in/out] obere Maßstabsgrenze (0 --> löschen)
	LONG lLowerScale;	// [in/out] untere Maßstabsgrenze (0 --> löschen)
} IDENTSCALEDATA;

// Menuänderungen verfolgen
// @xref <m DEXN_ChangingMenu>, <m DEXN_MenuChanged>
typedef struct tagMENUCHANGED {
	DWORD dwSize;
	HWND hWnd;			// [in] Fensterhandle, dessen Menu modifiziert wurde
	HMENU hMenu;		// [in] Menuhande des neuen Menus
	BOOL fPopupMenu;	// [in] FALSE: oberstes menulevel modifiziert, TRUE: Popupmenu modifiziert
} MENUCHANGED;

// Flags für Antwort auf 'DEXN_HandleMenu()'
#define HANDLEMENU_MainMenu	0x01
#define HANDLEMENU_ORMenu	0x02

///////////////////////////////////////////////////////////////////////////////
// Strukturen für NamedProperties
// DEX_MODNAMEDVIEWPROPERTY, DEX_QUERYNAMEDVIEWPROPERTY
typedef struct tagNAMEDVIEWPROPERTY {
	DWORD dwSize;
	LPCSTR pcView;		// [in, optional] Name der Ansicht (NULL --> aktuelle Ansicht)
	LPCSTR pcName;		// [in] eindeutiger Bezeichner der AnsichtsEigenschaft (Len <= 16!)
	LPSTR pBuffer;		// [in, out] Pufferbereich für Property selbst (NULL + DEX_MOD... --> löschen)
	int iLen;			// [in, out] Länge des Pufferbereiches/Länge des Wertes
// die folgenden Member brauchen nur bei DEX_MODNAMEDVIEWPROPERTY belegt zu sein
	LPCSTR pcShort;		// [in, optional] Kurze Beschreibung der Eigenschaft (Len <= 32!), NULL --> pcName
	LPCSTR pcDesc;		// [in, optional] Beliebig lange Beschreibung der Eigenschaft
} NAMEDVIEWPROPERTY;

///////////////////////////////////////////////////////////////////////////////
// Struktur für DEX_DEFINENEWOBJECTS
typedef struct tagDEFINEIDENTDLG {
	DWORD dwSize;
	HWND hWnd;			// [in] als parent zu verwendendes Fenster
	HOBJECTS lIdent;	// [in, out] zu bearbeitender Ident (0L --> neuer Beschreibungssatz)
	HPROJECT hPr;		// [in] Datenquelle, in der der Ident erzeugt werden soll
} DEFINEIDENTDLG;

///////////////////////////////////////////////////////////////////////////////
// Struktur für DEX_QUERYTABLENAME
typedef struct tagTABLENAME {
	DWORD dwSize;
	INT_PTR lIdent;		// [in] Bezugsobjektmenge
	LPSTR pBuffer;		// [in, out] Zeichenkettenpuffer für Tabellennamen
	int iLen;			// [in] Länge des übergebenen Puffers (mind 64 Zeichen!)
} TABLENAME;

///////////////////////////////////////////////////////////////////////////////
// Struktur für MapOrCreateMCodeToHandle (DEX_MAPORCREATEHANDLEFROMMCODE)
typedef struct tagMAPMCODETOHANDLE {
	DWORD dwSize;
	HOBJECTS lIdent;	// [in, optional] Objektklasse, auf die sich der MCode bezieht
	HFEATURE lMCode;	// [in] zu mappender MCode
	HFEATURE *plHandle;	// [out] evtl. erfolgreich gemappter MCode
	BOOL fCreate;		// [in] Handle evtl. neu erzeugen
	BOOL *pfCreated;	// [out] Handle wurde neu erzeugt
} MAPMCODETOHANDLE;

///////////////////////////////////////////////////////////////////////////////
// Struktur für ModifyROMode{Ident,Feature} (DEX_MODIFYROMODEIDENT, DEX_MODIFYROMODEMCODE)
typedef struct tagMODIFYROMODE {
	DWORD dwSize;
	HGENERIC lTarget;	// [in] lIdent oder lMCode, je nach Message
	BOOL fROMode;		// [in] TRUE: wird schreibgeschützt
} MODIFYROMODE;

///////////////////////////////////////////////////////////////////////////////
// Struktur für Objektlöschen mit ausführlichen Parametern
typedef struct tagDELETEOBJECTRECT {
	DWORD dwSize;
	HOBJECT lONr;			// [in] Objektnummer des zu löschenden Objektes
	bool fUndo;				// [in] mit Undo löschen
	bool fWithParentUndo;	// [in] (nur bei fUndo == true sinnvoll): übergeordnetes Undo existiert bereits
	bool fWithRect;			// [in] Parameter rcObj ist gültig
	RECT rcObj;				// [in, optional] Rechteck in BS Koordinaten (für Undo)
} DELETEOBJECTRECT;

///////////////////////////////////////////////////////////////////////////////
// Drucklayout einstellen lassen
// (DEX_SHOWPRINTLAYOUTDIALOG, DEX_PREVIEWPRINT)
#define MAX_LOGOFELD	4		// Anzahl der FirmenLogoBereiche

typedef struct tagPRINTLAYOUT {
	DWORD dwSize;

// Optionen
	bool m_fLegendOnly;		// nur Legende ausgeben
	bool m_fHasHeadline;	// Überschrift ausgeben

	DWORD m_rgLegendStyle;	// LegendenStyle
	DWORD m_rgRahmen;		// RahmenStyle
	DWORD m_rgMasstab;		// MaßstabsStyle

// sonstige Werte
	long m_lMasstab;		// AusgabeMaßstab
	LPSTR m_pHeadline;		// ÜberschriftsText
	int m_lHeadlineLen;		// Puffergröße für ÜberschriftsText
	
// welche Rechtecke sind gültig
	unsigned int m_fPageSize : 1;
	unsigned int m_fPageBase : 1;
	unsigned int m_fFullRect : 1;
	unsigned int m_fLegende : 1;
	unsigned int m_fHeadline : 1;
	unsigned int m_fMasstab : 1;
	unsigned int m_fSpiegel : 1;
	unsigned int m_fLogo : 1;
	unsigned int m_fFirmLogo : MAX_LOGOFELD;

// Druckbereiche auf Papier
	RECTL m_rcPageSize;		// Papiergröße
	RECTL m_rcPageBase;		// bedruckbarer Bereich

// Bereiche auf Ausgabepapier
	RECTL m_rcFullRect;		// Blattgrenzen
	RECTL m_rcLegende;		// Legendenbereich
	RECTL m_rcHeadline;		// Überschriftsbereich
	RECTL m_rcMasstab;		// Maßstabsbereich
	RECTL m_rcSpiegel;		// Kartenbereich

// auszugebender Bereich
	double m_dXMin;			// Datenbank-Container
	double m_dXMax;
	double m_dYMin;
	double m_dYMax;

// Logobereiche
	RECTL m_rcLogo;			// Logobereich (Überschrift)
	RECTL m_rcFirmLogo[MAX_LOGOFELD];	// Logobereiche (unten)
} PRINTLAYOUT;

// Printlayout-Dialog anzeigen (DEX_SHOWPRINTLAYOUTDIALOG)
typedef struct tagPRINTLAYOUTDIALOG {
	DWORD dwSize;
	HWND m_hWndParent;		// als Parent verwenden
	LPCSTR m_pcCaption;		// als Caption verwenden
	PRINTLAYOUT *m_pLayout;	// wird mit eingestelltem Layout gefüllt
} PRINTLAYOUTDIALOG; 

// Druckvorschau erzeugen
typedef struct tagPRINTPREVIEW {
	DWORD dwSize;
	RENDERGEODB *pRenderDb;	// Informationen zum Rendern
	PRINTLAYOUT *pLayout;	// Informationen zum Layout

// Daten für die Optimierung der Vorschau-Aufbereitung
	PVOID m_pData;			// vom Server verwaltete Daten
	POINT m_ptRatio;		// ScreenDC/PrinterDC * 10000
} PRINTPREVIEW;

///////////////////////////////////////////////////////////////////////////////
// DEX_CLONEOBJECT: Objekt doppeln
typedef struct tagCLONEOBJECT {
	DWORD dwSize;
	HOBJECT lONrToCopy;		// zu kopierendes Objekt
	HOBJECTS lNewIdent;		// wenn != NULL dann neue Objektklasse, ansonsten 'Unbekannte Objektklasse')
	HOBJECT lNewONr;		// neu erzeugtes Objekt
} CLONEOBJECT;

///////////////////////////////////////////////////////////////////////////////
// DEX_VERIFYLICLEVEL, DEX_VERIFYLICOPTION
typedef struct tagVERIFYLICENSE {
	DWORD dwSize;
	ULONG lLevelOrOption;	// zu testendes Level/Option(s)
	int iMode;				// was soll getestet werden (s. VERIFYMODE_...), nur bei DEX_VERIFYLICLEVEL
	HWND hWndParent;		// als Parent zu verwendendes Fenster
	LPCSTR pcCaption;		// ggf. anzuzeigendes Caption
} VERIFYLICENSE;

///////////////////////////////////////////////////////////////////////////////
// DEX_VERIFYLICLEVEL, DEX_VERIFYLICOPTION
typedef struct tagVERIFYLICENSEEX {
	DWORD dwSize;
	ULONG lLevelOrOption;	// zu testendes Level/Option(s)
	int iMode;				// was soll getestet werden (s. VERIFYMODE_...), nur bei DEX_VERIFYLICLEVEL
	HWND hWndParent;		// als Parent zu verwendendes Fenster
	LPCSTR pcCaption;		// anzuzeigendes Caption
	LPCSTR pcLicText;		// anzuzeigender Text
} VERIFYLICENSEEX;

// ACHTUNG: unterschiedliche Bedeutungen des Rückkehrwertes:
// VERIFYMODE_Equal liefert TRUE, wenn der Wert gleich ist
// VERIFYMODE_LessOrEqual liefet TRUE, wenn Lizensierung im Sinne des Levels vorliegt
#define VERIFYMODE_Equal			0		// Testet, ob lLevelOrOption den tatsächlichen Wert entspricht
#define VERIFYMODE_LessOrEqual		1		// Testet, ob mindestens lLevelOrOption als LizensierungsLevel vorliegt
#define VERIFYMODE_DontShowDialog	0x0080	// zeigt Lizensierungdialog _nicht_ an
#define VERIFYMODE_ShowDialogSync	0x0100	// zeigt Lizensierungdialog sofort (synchron)

///////////////////////////////////////////////////////////////////////////////
// DEX_QUERYOBJECTPTR, DEX_QUERYOBJECTSPTR, DEX_QUERYFEATUREPTR
typedef struct tagQUERYCOMOBJECT {
	DWORD dwSize;
	HGENERIC hObject;
	IID const *piid;
	IUnknown **ppIUnk;
} QUERYCOMOBJECT;

///////////////////////////////////////////////////////////////////////////////
// Objektcontainer in vorgegebenen Koordinatensystem abfragen (DEX_QUERYOBJCONTAINEREX)
typedef struct tagOBJECTCONTAINER {
	DWORD dwSize;
	HOBJECT lONr;			// [in] zu untersuchendes Objekt
	IUnknown *pICS;			// [in] gewünschtes Koordinatensystem
	double dXMin;			// [out] umschließendes Rechteck
	double dYMin;
	double dXMax;
	double dYMax;
} OBJECTCONTAINER;

///////////////////////////////////////////////////////////////////////////////
// Generischer Container in einem bestimmten Koordinatensystem
// DEX_QUERYACTIVESELECTIONEX, DEX_QUERYWINDOWASCONTAINER
typedef struct tagGENERICCONTAINER {
	DWORD dwSize;
	IUnknown *pICS;			// [in] gewünschtes Koordinatensystem
	double dXMin;			// [out] umschließendes Rechteck
	double dYMin;
	double dXMax;
	double dYMax;
} GENERICCONTAINER;

///////////////////////////////////////////////////////////////////////////////
// Abfrage von Infos zu einem TabFenster (WM_QUERYGENERICBARACTIVE)
typedef struct tagGENERICBARINFO {
	DWORD dwSize;
	GUID guidSid;			// [in] SID der abzufragenden Bar
	BOOL fVisible;			// [out] ist derzeit angezeigt
} GENERICBARINFO;

///////////////////////////////////////////////////////////////////////////////
// ExtensionFunc's 
#if defined(__cplusplus)
typedef LRESULT (*EXTPROC)(...);
// typedef LRESULT (CALLBACK *EXTCALLBACK)(...);
#else
typedef LRESULT (*EXTPROC)();
typedef LRESULT (CALLBACK *EXTCALLBACK)();
#endif

///////////////////////////////////////////////////////////////////////////////
// Connectionfilter
// DEX_CREATECONNECTIONFILTER, DEX_DELETECONNECTIONFILTER, DEX_QUERYCONNECTIONFILTER
// ACHTUNG: bei DEX_QUERYCONNECTIONFILTER ist der gelieferte IUnknown-Pointer 
//			pIGeometry AddRef'd, muß also freigegeben werden
typedef struct tagCONNECTIONFILTER {
	DWORD dwSize;
	char const *pcName;		// [in] Name des Connectionfilters
	IUnknown *pICS;			// [in, optional] Koordinatensystem, in dem die Filtergeometrie vorliegt
//
// die folgenden Felder sind [out] bei DEX_QUERYCONNECTIONFILTER
	IUnknown *pIGeometry;	// [in] Filtergeometrie (NULL für delete)
	int iMode;				// [in] Filtertyp (CF_Unknown für delete)
} CONNECTIONFILTER;

// Typen der Verbindungsfilter
#define CF_Unknown					0

// Bezugsgeometrie ist Rechteck
#define CF_Rectangle_OverlappedContainers	0x1		// Objektcontainer überlappt Filterbereich (Rechteck)
#define CF_Rectangle_ContainedContainers	0x2		// Objektcontainer ist in Filterbereich enthalten (Rechteck)
#define CF_Rectangle_OverlappedPoints		0x3		// Objektpunkte überlappt Filterbereich (Rechteck)
#define CF_Rectangle_ContainedPoints		0x4		// Objektpunkte ist in Filterbereich enthalten (Rechteck)
#define CF_Rectangle_OverlappedObjects		0x5		// Objekt überlappt Filterbereich (Rechteck)
#define CF_Rectangle_ContainedObjects		0x6		// Objekt ist in Filterbereich enthalten (Rechteck)

// Bezugsgeometrie ist ein Polygon
#define CF_Polygon_OverlappedContainers		0x11	// Objektcontainer überlappt Filterbereich (Polygon)
#define CF_Polygon_ContainedContainers		0x12	// Objektcontainer ist in Filterbereich enthalten (Polygon)
#define CF_Polygon_OverlappedPoints			0x13	// Objektpunkte überlappt Filterbereich (Polygon)
#define CF_Polygon_ContainedPoints		    0x14	// Objektpunkte ist in Filterbereich enthalten (Polygon)
#define CF_Polygon_OverlappedObjects		0x15	// Objekt überlappt Filterbereich (Polygon)
#define CF_Polygon_ContainedObjects			0x16	// Objekt ist in Filterbereich enthalten (Polygon)

#define CF_Polygon_Flag						0x10

// DEX_ATTACHCONNECTIONFILTER, DEX_DETACHCONNECTIONFILTER, 
typedef struct tagATTACHCONNECTIONFILTER {
	DWORD dwSize;
	char const *pcName;		// [in] Name des Connectionfilters (NULL für detach)
	char const *pcConnName;	// [in] Name der Connection, auf die Bezug genommen wird
} ATTACHCONNECTIONFILTER;

// DEX_QUERYATTACHEDCONNECTIONFILTER
typedef struct tagGETATTACHEDCONNECTIONFILTER {
	DWORD dwSize;
	char const *pcConnName;	// [in] Name der Connection, auf die Bezug genommen wird
	int iLen;				// [in, out] Puffergröße, wenn gleich NULL, dann 
							// lediglich Abfrage ob Filter attached ist
	char *pName;			// [in, out] Puffer
} GETATTACHEDCONNECTIONFILTER;

// #HK021219
// DEX_CREATECONNECTIONFILTER_DLG
typedef struct tagCREATECONNECTIONFILTER {
	DWORD dwSize;
	HWND hWndParent;		// [in] zu verwendendes Parentfenster
	char *pName;			// [in, out] Name des Verbindungsfilters
	int iLen;				// [in, out] Puffergröße von 'pName'
	int iMode;				// [in, out] Filtertyp
	bool fApplyAllConnections;		// [in, out] 'Auf alle Datenquellen anwenden'
	bool fNameIsNew;		// [out] der ausgewählte Name wurde neu vergeben
	bool fShowApplyAllConnections;	// [in] 'Auf alle Datenquellen anwenden' anzeigen
	bool fApplySettings;	// [in] false: Dialog nur anzeigen und Resultate liefern
							//		true:  Resultate auch durchsetzen
	bool fShowPropertiesOnly;	// [in] Name ist nicht editierbar (Name muß im 
								//      Feld pName gegeben sein
	HOBJECT hTargetONr;		// [in] bei iMode & CF_Polygon_Flag Objektnummer des
							//		Objektes, von dem Geometrie genommen werden soll
	int iRetVal;			// [out] Rückgabewert vom Dialog
} CREATECONNECTIONFILTER;

///////////////////////////////////////////////////////////////////////////////
// eigentliche Schnittstellenfunktion 
#include <xtensnm.hxx>		// Manifestkonstanten

extern "C" _XTENSN_ENTRY LRESULT WINAPI TriasExtensionProc (HWND, UINT, WPARAM, LPARAM);

// nützliche Makros
#if !defined(DELETE)
#define DELETE(x) {if(x) { delete(x); (x)=NULL; }}
#if defined(MSCC8) || _MSC_VER >= 800
#define DELETE_VEC(x)	{if(x){delete [] (x); (x)=NULL;}}
#else
#define DELETE_VEC(x,s)	{if(x){delete [(s)] (x); (x)=NULL;}}
#endif
#endif

#define INITSTRUCT(v,t)			\
	memset(&(v),'\0',sizeof(t));	\
	(v).dwSize=sizeof(t);

#include <poppack.h>

#if defined(__cplusplus)
}	// extern "C"
#endif

#endif // _XTENSION_H
