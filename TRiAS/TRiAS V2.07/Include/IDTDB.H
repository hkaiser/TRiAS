/* Deklaration der Datenbasisstruktur fuer idtdb */

#if !defined(_IDTDB_H)
#define _IDTDB_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <pshpack1.h>

#include <idtdb001.h>		// alte Version

#define PBD030000002	0x03000002L

// allgemeine Struktur der TextEinträge in den Beschreibungssätzen
struct desc {
	long Key;		// allg. Schlüsselwert
	char LText[76];		// LangText
	long Next;		// Verweis aauf evtl. FortsetzungsText
	char SText[32];		// KurzText
	char dummy[24];
};
struct fdesc {
	char FLText[136];	// Langtext - Fortsetzung
	long FNext;		// Verweis auf weiteren Satz
};

struct mid {
	long ids;
	char texti[76];
	long zntxti;
	char ktexti[32];
};
struct mif {
	char textif[136];
	long ztxtif;
};
struct mmk {
	long mks;
	char textm[76];
	long zntxtm;
	char ktextm[32];
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
	char textmf[136];
	long ztxtmf;
};
struct mmw {
	long wkode;
	char textw[76];
	long zntxtw;
	long znwert;
};
struct mmf {
	char textmw[136];
	long ztxtmw;
};
struct mrl {
	long prirel;
	char textr[76];
	long zntxtr;
	char ktextr[32];
	short reltyp;
};
struct mrf {
	char textrf[136];
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

#if defined(__cplusplus)
}
#endif

#endif // _IDTDB_H

