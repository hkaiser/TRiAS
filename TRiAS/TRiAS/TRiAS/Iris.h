/* Konstantendefinitionen für Ressourcendatei                   */
/* File: IRIS.H                                                 */

#if !defined(_IRIS_H)
#define _IRIS_H

// wenn nicht anders definiert, dann für Windows 3.1 übersetzen
#if !defined(WINVER)
#define WINVER	0x030a
#endif

// extern "C" {	// Direkt gerufene C-Funktionen
//	char * _pascal InitScriptDlg (HANDLE, char *, short &, char *, char *);
//}

#if !defined(NOIRISPROTOS)
// diverse globale Funktionsprototypen ----------------------------------------
ErrCode doExport (HANDLE hWnd, ObjContainer *OC = NULL);

#if !defined(NOPROJEKTION)
void geowel (KoOrd *x, KoOrd *y);
#endif
#endif

// Ressourcen ----------------------------------------------------------------
#define DIRISICON1	49	// TRIAS13-Ikone
#define DIRISICON	50	// TRIAS13-Ikone
#define IRISICON        51      // Anwendungsikone
#define IRISMENU        52      // Hauptmenu
#define IRISACCELS      55      // Acceleratoren
#define STARTACCELS	72	// Acceleratoren in StartupFenster
#define CANCELACCELS    61      // AbbruchAcceleratoren
#define STARTMENU       66      // StartupMenu
#define	OBJMENU		76	// Menu für ObjektRechercheFenster

#if !defined(MARKER1)
#define MARKER1         170     // 1x1
#endif
#define MARKER2         171     // 3x3
#define MARKER3         172     // 5x5
#define MARKER4         173     // Kreuz 3x3
#define MARKER5         174     // Kreuz 5x5
#define MARKER6         175     // diag. Kreuz 3x3
#define MARKER7         176     // diag. Kreuz 5x5
#define MARKER8         177     // leeres Rhombus 5x5
#define MARKER9         178     // Rhombus 5x5
#define MARKER10        179     // Rahmen 5x5
#define MARKER11        180     // Kreis 
#define MARKER12        181     // Kleeblatt
#define MARKER13        182     // VollKreis
#define MARKER14	183
#define MARKER15	184
#define MARKER16	185
#define MARKER17	186
#define MARKER18	187

#define TEXTOBJMENU	300

#define ARROW           90      // Werkzeuge
#define ARROWON         91
#define LUPE            92
#define LUPEON          93
#define SCHERE          94
#define SCHEREON        95
#define STIFT           96
#define STIFTON         97
#define LINEAL          98
#define LINEALON        99
#define ZOOM		101
#define SCHRIFT		102
#define GRAYSCHRIFT	103

#define SIGNONBMP	104

#define PERSONALCODE    100     // PersonalisierungsKode - Resource

#include "resstrg.h"

// zusätzlicher ResourceType
#define PERSONALCODERES 256

// Kursoren ------------------------------------------------------------------
#define LUPECURSOR	502
#define MOVECURSOR	509

#define IDSND_STARTUP	1000
#define IDBMP_STARTUP	1001

// Menueinträge --------------------------------------------------------------
#include "menuitem.h"

// DialogBoxen ----------------------------------------------------------------
// #include "irisopen.h"           // Projekt eröffnen
#include "opendb.h"
// #include "relation.h"           // Objektbezogene Relations-Recherche
#include "identsel.h"           // Selektion der zu zeichneden Objekte
// #include "pwdialog.h"           // Passwordfenster
// #include "mkrech.h"             // MerkmalsrechercheFenster
// #include "coords.h"             // Koordinatenanzeige
// #include "nomenkl.h"            // Nomeklaturanzeige
#include "infodlg.h"            // AboutDlgBox
#include "prntabrt.h"           // Drucken abbrechen
// #include "prntsel.h"            // Druckereinrichtung
// #include "merkedit.h"           // Merkmalseditierung
// #include "edithead.h"           // DBHeader editieren
#include "objekte.h"            // Recherchefenster
// #include "schrank.h"		// SchrankSchnulli
#include "export.h"		// Datenexport
// #include "mbuffdlg.h"		// Objektpufferung
// #include "sbuffer.h"		// ObjektPufferParameter
#include "newid.h"
#include "palwind.h"
#include "visparam.h"
// #include "objtype.h"
#include "edittext.h"
// #include "masstab.h"
#include "ausschn.h"
// #include "expstat.h"
#include "priority.h"
#include "exptrans.h"
#include "prntlayt.h"
#include "extload.h"
#include "legende.h"
#include "objprop.h"
#include "rechres.h"
#include "delviews.h"
#include "saveopt.h"
// #include "import.h"
#include "signon.h"
#include "signon1.h"
#include "overview.h"
#include "rechres.h"
#include "selident.h"
// #include "modident.h"

// Größen verschiedener Textfelder
#define PATHLEN        _MAX_PATH	// FileNameLen
#define USERLEN         20			// Länge des UserNamens
#define PASSWDLEN       20			// Länge des Passwords

// Angenommene Skalierung der geometrischen Koordinaten in der Datenbasis
#define SCALE_X 1000000L
#define SCALE_Y 1000000L

// Position der OldDB-Liste in den Menues
#if !defined(WIN16)
#define IRISMENU_PROPERTYPOS	8
#define IRISMENUPOS				13
#define STARTMENUPOS			2
#else
#define IRISMENUPOS				13
#define STARTMENUPOS			5
#endif

// Konstantendefinitionen -----------------------------------------------------
// const long ID_BUFFEROFFSET = 1000000000L;	// Neuer Ident bei Pufferung
// const long ON_BUFFEROFFSET = 1000000L;		// Neue Objektnummer bei Pufferung

// Datenstruktur, die für Scrollen/Zeichnen benötigt wird ---------------------
typedef struct tagIDLEPAINT {
	HWND m_hWnd;
	HRGN m_hRgn;
} IDLEPAINT;

#endif  // _IRIS_H
