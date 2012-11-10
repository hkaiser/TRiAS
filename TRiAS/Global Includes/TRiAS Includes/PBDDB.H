///////////////////////////////////////////////////////////////////////////
// @doc 
// @module PBDDB.H | Deklaration der Datenbasisstruktur fuer idtdb

#if !defined(_PBDDB_H__8B724F05_9445_11D2_9F07_006008447800__INCLUDED_)
#define _PBDDB_H__8B724F05_9445_11D2_9F07_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <pshpack1.h>

#undef INITRECORD
#if !defined(_NO_INITRECORD) 
#define INITRECORD() memset(this, '\0', sizeof(*this))
#else
#define INITRECORD()
#endif // _NO_INITRECORD

// allgemeine Struktur der TextEinträge in den Beschreibungssätzen
struct desc {
	long Key;		// allg. Schlüsselwert
	char LText[76];		// LangText
	long Next;		// Verweis aauf evtl. FortsetzungsText
	char SText[16];		// KurzText

#if defined(__cplusplus)
		desc() { INITRECORD(); }
#endif // __cplusplus
};
struct fdesc {
	char FLText[120];	// Langtext - Fortsetzung
	char FNext;		// Verweis auf weiteren Satz

#if defined(__cplusplus)
		fdesc() { INITRECORD(); }
#endif // __cplusplus
};

struct mid {
	long ids;
	char texti[76];
	long zntxti;
	char ktexti[16];

#if defined(__cplusplus)
		mid() { INITRECORD(); }
#endif // __cplusplus
};
struct mif {
	char textif[120];
	long ztxtif;

#if defined(__cplusplus)
		mif() { INITRECORD(); }
#endif // __cplusplus
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

#if defined(__cplusplus)
		mmk() { INITRECORD(); }
#endif // __cplusplus
};
struct mkf {
	char textmf[120];
	long ztxtmf;

#if defined(__cplusplus)
		mkf() { INITRECORD(); }
#endif // __cplusplus
};
struct mmw {
	long wkode;
	char textw[76];
	long zntxtw;
	long znwert;

#if defined(__cplusplus)
		mmw() { INITRECORD(); }
#endif // __cplusplus
};
struct mmf {
	char textmw[120];
	long ztxtmw;

#if defined(__cplusplus)
		mmf() { INITRECORD(); }
#endif // __cplusplus
};
struct mrl {
	long prirel;
	char textr[76];
	long zntxtr;
	char ktextr[16];
	short reltyp;

#if defined(__cplusplus)
		mrl() { INITRECORD(); }
#endif // __cplusplus
};
struct mrf {
	char textrf[120];
	long ztxtrf;

#if defined(__cplusplus)
		mrf() { INITRECORD(); }
#endif // __cplusplus
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

#endif // !defined(_PBDDB_H__8B724F05_9445_11D2_9F07_006008447800__INCLUDED_)
