/* Deklaration der Datenbasisstruktur fuer idtdb */

#include <pshpack1.h>

// allgemeine Struktur der TextEinträge in den Beschreibungssätzen
struct desc {
	long Key;		// allg. Schlüsselwert
	char LText[76];		// LangText
	long Next;		// Verweis aauf evtl. FortsetzungsText
	char SText[16];		// KurzText
};
struct fdesc {
	char FLText[120];	// Langtext - Fortsetzung
	char FNext;		// Verweis auf weiteren Satz
};

struct mid {
	long ids;
	char texti[76];
	long zntxti;
	char ktexti[16];
};
struct mif {
	char textif[120];
	long ztxtif;
};
struct mmk {
	long mks;
	char textm[76];
	long zntxtm;
	char ktextm[16];
	char mtyp[4];
	long wfakm;
	union {
		double dwvon;
		long iwvon[2];
	} wvon;
	union {
		double dwbis;
		long iwbis[2];
	} wbis;
};
struct mkf {
	char textmf[120];
	long ztxtmf;
};
struct mmw {
	long wkode;
	char textw[76];
	long zntxtw;
	long znwert;
};
struct mmf {
	char textmw[120];
	long ztxtmw;
};
struct mrl {
	long prirel;
	char textr[76];
	long zntxtr;
	char ktextr[16];
	short reltyp;
};
struct mrf {
	char textrf[120];
	long ztxtrf;
};

/* Record- und Feld-Tabelleneintraege */

/* Konstanten fuer Recordnamen */
#define MID 0
#define MIF 1
#define MMK 2
#define MKF 3
#define MMW 4
#define MMF 5
#define MRL 6
#define MRF 7

/* Konstanten fuer Schluesselfelder */
#define IDS 0
#define MKS 1
#define PRIREL 2

#include <poppack.h>


