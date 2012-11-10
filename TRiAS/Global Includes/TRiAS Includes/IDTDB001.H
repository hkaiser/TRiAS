/* Deklaration der Datenbasisstruktur fuer idtdb */

#include <risdb.h>

#define PBD030000001	0x03000001L

#if !defined(_RISDB_NO_STRUCTS)

// allgemeine Struktur der TextEinträge in den Beschreibungssätzen
struct desc_001 :
	public db_access<desc_001>
{
	long Key;			// allg. Schlüsselwert
	char LText[76];		// LangText
	long Next;			// Verweis aauf evtl. FortsetzungsText
	char SText[16];		// KurzText
	char dummy[24];

	desc_001() { INITRECORD(); }
};

struct fdesc_001 :
	public db_access<fdesc_001>
{
	char FLText[120];	// Langtext - Fortsetzung
	long FNext;			// Verweis auf weiteren Satz

	fdesc_001() { INITRECORD(); }
};

struct mid_001 :
	public db_access<mid_001>
{
	long ids;
	char texti[76];
	long zntxti;
	char ktexti[16];

	mid_001() { INITRECORD(); }
};

struct mif_001 :
	public db_access<mif_001>
{
	char textif[120];
	long ztxtif;

	mif_001() { INITRECORD(); }
};

struct mmk_001 :
	public db_access<mmk_001>
{
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

struct mkf_001 :
	public db_access<mkf_001>
{
	char textmf[120];
	long ztxtmf;

	mkf_001() { INITRECORD(); }
};

struct mmw_001 :
	public db_access<mmw_001>
{
	long wkode;
	char textw[76];
	long zntxtw;
	long znwert;

	mmw_001() { INITRECORD(); }
};

struct mmf_001 :
	public db_access<mmf_001>
{
	char textmw[120];
	long ztxtmw;

	mmf_001() { INITRECORD(); }
};

struct mrl_001 :
	public db_access<mrl_001>
{
	long prirel;
	char textr[76];
	long zntxtr;
	char ktextr[16];
	short reltyp;

	mrl_001() { INITRECORD(); }
};

struct mrf_001 :
	public db_access<mrf_001>
{
	char textrf[120];
	long ztxtrf;

	mrf_001() { INITRECORD(); }
};
#endif // !defined(_RISDB_NO_STRUCTS)

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


