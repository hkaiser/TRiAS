/* Deklaration der Datenbasisstruktur fuer idtdb */

#if defined(__cplusplus)
extern "C" {
#endif

#define PBD030000001	0x03000001L

// allgemeine Struktur der TextEintrÑge in den BeschreibungssÑtzen
struct desc_001 {
	long Key;		// allg. SchlÅsselwert
	char LText[76];		// LangText
	long Next;		// Verweis aauf evtl. FortsetzungsText
	char SText[16];		// KurzText
	char dummy[24];
};
struct fdesc_001 {
	char FLText[120];	// Langtext - Fortsetzung
	long FNext;		// Verweis auf weiteren Satz
};

struct mid_001 {
	long ids;
	char texti[76];
	long zntxti;
	char ktexti[16];
};
struct mif_001 {
	char textif[120];
	long ztxtif;
};
struct mmk_001 {
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
struct mkf_001 {
	char textmf[120];
	long ztxtmf;
};
struct mmw_001 {
	long wkode;
	char textw[76];
	long zntxtw;
	long znwert;
};
struct mmf_001 {
	char textmw[120];
	long ztxtmw;
};
struct mrl_001 {
	long prirel;
	char textr[76];
	long zntxtr;
	char ktextr[16];
	short reltyp;
};
struct mrf_001 {
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

#if defined(__cplusplus)
}
#endif

