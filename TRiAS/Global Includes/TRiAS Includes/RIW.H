/* Deklaration der Datenbasisstruktur fuer riw */

struct prjhead {
	long prjhdidn[4];
	char text[64];
	long zntext;
};
struct prjfhead {
	char textf[80];
	long ztextf;
};

/* Record- und Feld-Tabelleneintraege */

/* Konstanten fuer Recordnamen */
#define PRJHEAD 0
#define PRJFHEAD 1

/* Konstanten fuer Schluesselfelder */
#define PRJHDIDN 0
