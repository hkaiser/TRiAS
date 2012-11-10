/* Deklaration der Datenbasisstruktur fuer errdb */

#if !defined(_ERRDB_H)
#define _ERRDB_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <pshpack1.h>

struct error {
	long errcode;
	char eshort[7];
	char errtext[80];
};
struct routine {
	long srccode;
	char srcname[40];
};

/* Record- und Feld-Tabelleneintraege */

/* Konstanten fuer Recordnamen */
#define ERRORNR 0
#define ROUTINE 1

/* Konstanten fuer Schluesselfelder */
#define ERRCODE 0
#define SRCCODE 1

#include <poppack.h>

#if defined(__cplusplus)
}
#endif

#endif // _ERRDB_H
