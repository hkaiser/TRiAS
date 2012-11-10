/* Datenbank - I/O Funktionen unterste Ebene                    */
/* Fehlercode                                                   */
/* File: ERRDEF.H               last update: 26. September 1989 */

/* ZIPEDB: @(#)errdef.h 2.6  90/05/02"
 */

#ifndef _ERRDEF_H
#define _ERRDEF_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <pshpack1.h>

#include "routines.h"
#include "errtypes.h"
 
extern int db_status;

enum ErrCode;
 
#define dberr db_error
 
#define TRUE 1
#define FALSE 0
 
#define FOREGRND 0
#define BACKGRND 1
 
#define S_OKAY          0       /* kein Fehler */
#define S_DUMMY         700     /* kein Fehler, aber Ret-Value != 0 */
#define S_NOTFOUND      701     /* Schluessel nicht gefunden */
#define S_DUPLICATE     702     /* Schluessel doppelt */
#define S_NOFILES	703	/* DB enthaelt keine Dateien */
#define S_NOFIT		704	/* Container auáerhalb des vorgegebenen Fensters */

#define S_BADMKTYP	730	/* MerkmalsTyp stimmt nicht überein */
#define S_TEXTTOLONG	731	/* MerkmalsText zu lang */
#define S_MKODEEXISTS	732	/* MerkmalsKode existiert bereits für dieses Objekt */
#define W_BADRELTYP	733	/* Falscher RelationsTyp */
#define W_DUPLBREL	734	/* Doppeltes Begleitobjekt */
#define S_DUPLREL	735	/* Doppelte Relation */
#define W_NOTEXTOBJ	1706	/* Kein TextObjekt */
#define S_BADCOORD	750	/* Koordinaten auáerhalb des gültigen Bereiches */
 
#define S_NOON		-10

#define S_INVDB         -700    /* ungueltige(r) Datenbasis(name) */
#define S_DBOPEN        -701    /* Datenbasis nicht geoeffnet */
#define S_INVADDR       -702    /* ungueltige Datenbankadresse */
#define S_VERSION       -703    /* falsche Versionsnummer */
#define S_NOKEY         -704    /* kein gueltiger Schluessel */
#define S_HTLEVEL       -705    /* HTree zu tief verschachtelt */
#define S_QTLEVEL       -706    /* QTree zu tief verschachtelt */
#define S_CTLEVEL       -707    /* CubicTree zu tief verschachtelt */
#define S_KEYSEQ        -708    /* Fragwuerdige Schluesselnummer */
#define S_ACTIV         -709    /* Fehler beim Aktivieren einer DB */
#define S_CLOSE         -710    /* Kann DB nicht abschliessen */
 
#define S_NOSPACE       -711    /* File kann nicht vergroessert werden */
#define S_SYSERR        -712    /* Systemfehler */
#define S_FAULT         -713    /* Page waehrend der Nutzung veraendert */
#define S_NOWORK        -714    /* kein default working-file gegeben */
#define S_NOMEMORY      -715    /* Hauptspeicher nicht ausreichend */
#define S_NOFILE        -716    /* File nicht gefunden */
#define S_HOLDERR       -717    /* Fehler beim binden einer Seite an File */
#define S_RELEASERR     -718    /* Fehler beim loesen einer Seite von File */
#define S_NOREAD        -719    /* Lesefehler */
#define S_ACCESS        -720    /* Zugriffsueberschreitung */
#define S_SPAWN         -721    /* Kann Subprozesz nicht starten */
#define S_BACKUP        -722    /* Fehler im Prozesz des Backup */
#define S_OVERFL        -723    /* Ueberlauf der Hashtabelle */
#define S_MAXDB         -724    /* Bereits MAXDB Datenbasen eroeffnet */
#define S_ERROVL        -725    /* Ueberlauf der Fehlerliste NEGATIV !! */
#define S_NOERRVEC      -726    /* Fehlervektor nicht definierbar */
#define S_BADLEN	-727	/* DB-Header: Textfeld zu klein */
#define S_DELRECORD	-728	/* Satz ist gelöscht */

#define S_BADOBJTYP	-729	/* ObjektTyp stimmt nicht überein */

#define S_OPENRO	-731	// DB RO eröffnen
#define S_COMPOUNDFILE	-732	// DB ist CompoundFile
#define S_NOTAPROJECT	-733	// kein DirisProjekt
#define S_STG_CLOSEERROR 	-734	// Fehler bei IStorage::Commit
#define S_STG_READERROR 	-735	// Fehler beim Read
#define S_STG_WRITEERROR 	-736	// Fehler beim Write
#define S_STG_SEEKERROR 	-737	// Fehler beim Seek
#define S_STG_FLUSHERROR 	-738	// Fehler bei IStream::Commit

#define E_VERSION	704	// Warnung: Falsche Versionsnummer

/* Konsistenztest */
#define S_BADFNO	-750	/* ungueltige Dateinummer */
#define S_INVCHAIN	-751	/* ungueltiger Ruckverkettungszeiger */
#define S_DELREC	-752	/* Satz ist nicht in Rueckverkettung enthalten */
#define S_RECDEL	-753	/* Satz ist nur in Rueckverkettung enthalten */

/* Fehlercodes in FLEX.C */
#define S_BADFLEX       -790	/* fragwürdige FLEX-Nummer */
#define S_BADINDEX      -791	/* fragwürdiger FLEX-Index */
#define S_FLEXINI       -792	/* FLEX ist nicht initialisiert */
#define S_NOFLEX        -793	/* Kein FLEX mehr verfügbar */

/* KonsistenzFehler */
#define S_BADPOLVGO	-1501	/* Ungültiger Verweis aus POL in VGO */

/* Fehler in PBDRoutinen */
#define S_BADRECID	-1601	/* IDSatz nicht vorhanden */
#define S_BADRECMK	-1602	/* MKSatz nicht vorhanden */
#define S_BADRECREL	-1603	/* RELSatz nicht vorhanden */
#define S_BADRECWM	-1604	/* MerkmalsWert nicht vorhanden */
#define S_BADRECNO	-1605	/* PBDSatz nicht vorhanden */
#define S_BADTYP	-1606	/* Falscher SatzTyp */
#define S_BADPRIMOBJ	-1607	/* ungültiges PrimärObjekt */

#define E_BADDIRISVERSION	-1620	/* zu altes DIRIS */
#define W_NORELATION		1600	/* Relation nicht vorhanden */

///////////////////////////////////////////////////////////////////////////////
// alle Fehler/Warnungen ignorieren (überschreibt alle anderen Handler)
#define E_IGNOREALL	-12345
#define W_IGNOREALL	12345

#include <poppack.h>

#if defined(__cplusplus)
}
#endif

#endif // _ERRDEF_H
