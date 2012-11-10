// Prototypen der PBD-Zugriffsfunktionen
// File: MPROTOS.H

#if !defined(_MPROTOS_H)
#define _MPROTOS_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <pshpack1.h>

// Löschen eines Eintrages aus einer PBD --------------------------------------
long FUNCTYPE mdelkr (HPROJECT hPr, long rec);
long FUNCTYPE mdelki (HPROJECT hPr, long rec);
long FUNCTYPE mdelkm (HPROJECT hPr, long rec);

// Finden eines Eintrages in einer PBD ----------------------------------------
long FUNCTYPE mfind (HPROJECT hPr, short Typ, long Code, long *pSatz);
long FUNCTYPE mfindi (HPROJECT hPr, long Ident, long *pSatz);
long FUNCTYPE mfindm (HPROJECT hPr, long MCode, long *pSatz);
long FUNCTYPE mfindr (HPROJECT hPr, long RCode, long *pSatz);

// Schreiben eines Eintrages in eine PBD --------------------------------------
long FUNCTYPE mputki (HPROJECT hPr, long Ident, long *pRec);
long FUNCTYPE mputkm (HPROJECT hPr, long MCode, short MTyp, long WF, long *von, long *bis, long *pRec);
long FUNCTYPE mputkr (HPROJECT hPr, long RCode, short reltyp, long *pRec);

// Schreiben eines KurzTextes zu einem Beschreibungssatz ----------------------
long FUNCTYPE mputkt (HPROJECT hPr, short Typ, long Satz, char *pText);
long FUNCTYPE mputkti (HPROJECT hPr, long Rec, char *Text);
long FUNCTYPE mputktm (HPROJECT hPr, long Rec, char *Text);
long FUNCTYPE mputktr (HPROJECT hPr, long Rec, char *Text);
long FUNCTYPE mputktxt (struct db_addr *pDBA, char *Text);

// Schreiben eines LangTextes zu einem Beschreibungssatz ----------------------
long FUNCTYPE mputtx (HPROJECT hPr, short Typ, long Satz, char *pText);
long FUNCTYPE mputtxi (HPROJECT hPr, long Rec, char *Text);
long FUNCTYPE mputtxm (HPROJECT hPr, long Rec, char *Text);
long FUNCTYPE mputtxr (HPROJECT hPr, long Rec, char *Text);
long FUNCTYPE mputtxw (HPROJECT hPr, long Rec, char *Text);
long FUNCTYPE mputtxt (struct db_addr *pDBA, char *Text);

// Schreiben eines MerkmalsFolgeSatzes zu einem AufzählungsMerkmal ------------
long FUNCTYPE mputwm (HPROJECT hPr, long MCode, long MWert, long *pSatz);

// Einlesen der BeschreibungsInformationen ------------------------------------
long FUNCTYPE mgetkm (HPROJECT hPr, long Satz, long *pMCode, short *pMTyp, long *pWF, long *pVon, long *pBis, long *pNext);
long FUNCTYPE mgetkr (HPROJECT hPr, long Satz, long *pRCode, short *pRTyp);
long FUNCTYPE mgetwm (HPROJECT hPr, long Satz, long *pMWert, long *pNext);

long FUNCTYPE mgetkt (HPROJECT hPr, short Typ, long Satz, char *pText);
long FUNCTYPE mgetktall (HPROJECT hPr, long Satz, char *pText, short FileNo);

long FUNCTYPE mgetl (HPROJECT hPr, short Typ, long Satz, long *pLen);
long FUNCTYPE mgettx (HPROJECT hPr, short Typ, long Satz, char *pText);

// ----------------------------------------------------------------------------
long FUNCTYPE mfirst(HPROJECT hPr, char  *typ,long  *rec,long  *kod);
long FUNCTYPE mlast(HPROJECT hPr, char  *typ,long  *rec,long  *kod);
long FUNCTYPE mnext(HPROJECT hPr, char  *typ,long  *rec,long  *kod);
long FUNCTYPE mprev(HPROJECT hPr, char  *typ,long  *rec,long  *kod);

long FUNCTYPE mgetki(HPROJECT hPr, long  *rec,long  *kode);

long FUNCTYPE mrange(HPROJECT hPr, char  *typ,long  *kod1,long  *kod2);

long FUNCTYPE FreeText (HPROJECT hPr, short FileNo, long RecNo);

#include <poppack.h>

#if defined(__cplusplus)
}
#endif

#endif  // _MPROTOS_H
