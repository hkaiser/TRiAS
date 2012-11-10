///////////////////////////////////////////////////////////////////////////
// @doc 
// @module IDTDB.H | Deklaration der Datenbasisstruktur für idtdb

#if !defined(_IDTDB_H__7A24AC75_96F4_11D1_BA0E_080036D63803__INCLUDED_)
#define _IDTDB_H__7A24AC75_96F4_11D1_BA0E_080036D63803__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <pshpack1.h>
#include <risdb.h>
#include <idtdb001.h>		// alte Version

#if !defined(_RISDB_NO_STRUCTS)

// allgemeine Struktur der TextEinträge in den Beschreibungssätzen
struct desc :
	public db_access<desc>
{
	long Key;			// allg. Schlüsselwert
	char LText[76];		// LangText
	long Next;			// Verweis aauf evtl. FortsetzungsText
	char SText[32];		// KurzText
	char dummy[28];

	inline desc();		// defined later
};

struct fdesc :
	public db_access<fdesc>
{
	char FLText[136];	// Langtext - Fortsetzung
	long FNext;			// Verweis auf weiteren Satz

	fdesc() { INITRECORD(); }
};

struct mid :
	public db_access<mid>
{
	long ids;
	char texti[76];
	long zntxti;
	char ktexti[32];
	long ityp;			// ab V5.00.00.012: Typ des Identifikators

	mid() { INITRECORD(); _ASSERTE(sizeof(mid) <= sizeof(desc)); }
};

struct mif :
	public db_access<mif>
{
	char textif[136];
	long ztxtif;

	mif() { INITRECORD(); }
};

struct mmk :
	public db_access<mmk>
{
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
	long ident;

	mmk() {	INITRECORD(); _ASSERTE(sizeof(mmk) <= sizeof(desc)); }
};

struct mkf :
	public db_access<mkf>
{
	char textmf[136];
	long ztxtmf;

	mkf() { INITRECORD(); }
};

struct mmw :
	public db_access<mmw>
{
	long wkode;
	char textw[76];
	long zntxtw;
	long znwert;

	mmw() { INITRECORD(); }
};

struct mmf :
	public db_access<mmf>
{
	char textmw[136];
	long ztxtmw;

	mmf() { INITRECORD(); }
};

struct mrl :
	public db_access<mrl>
{
	long prirel;
	char textr[76];
	long zntxtr;
	char ktextr[32];
	short reltyp;

	mrl() { INITRECORD(); _ASSERTE(sizeof(mrl) <= sizeof(desc)); }
};

struct mrf :
	public db_access<mrf>
{
	char textrf[136];
	long ztxtrf;

	mrf() { INITRECORD(); }
};

///////////////////////////////////////////////////////////////////////////////
// resolve forward declarartion problem
inline desc::desc()
{ 
	INITRECORD(); 

// desc muß mindestens ebenso groß sein wie Id/Mk Beschreibungssatz

	_ASSERTE(sizeof(mid) <= sizeof(desc));
	_ASSERTE(sizeof(mmk) <= sizeof(desc));
	_ASSERTE(sizeof(mrl) <= sizeof(desc));
}
	
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

#include <poppack.h>

#endif // !defined(_IDTDB_H__7A24AC75_96F4_11D1_BA0E_080036D63803__INCLUDED_)
