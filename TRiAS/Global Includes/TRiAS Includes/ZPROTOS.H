// File: ZPROTOS.H
// ZIPEDB: %W%	%E"

#ifndef _ZPROTOS_H
#define _ZPROTOS_H

#if defined(_FORCE_LEGACY_CODE)

#if defined(__cplusplus)
extern "C" {
#endif

#include <pshpack1.h>
#include <trias02m.hxx>		// Manifestkonstanten

// Versionskontrolle ----------------------------------------------------------
#include <versions.h>

#if !defined(DELETE_OBJ)
#define DELETE_OBJ(x) 	{if(x){delete (x);(x)=NULL;}}
#if defined(MSCC8) || _MSC_VER >= 800
#define DELETE_VEC(x)	{if(x){delete [] (x); (x)=NULL;}}
#else
#define DELETE_VEC(x,s)	{if(x){delete [(s)] (x); (x)=NULL;}}
#endif
#endif

// ProjectHandle
#if defined(MSWIND) || defined(_WINDOWS)
#if !defined(_DEFINED_HPROJECT)
#define _DEFINED_HPROJECT
DECLARE_HANDLE(HPROJECT);
#define HACTPROJECT		((HPROJECT)(-1))		// bezieht sich auf Projekt
#define HACTCONNECTION	((HPROJECT)(NULL))		// bezieht sich auf aktuelle Datenquelle
#endif
#else
#define HPROJECT int
#endif

// Fortranschnittstelle
#include <fprotos.h>
#include <mprotos.h>

// Makrodefinitionen ----------------------------------------------------------
#if defined(__cplusplus)

#define DBASSERT(f)	if((RC=(ErrCode)(f))!=0)return RC
#define DBASSERTM(f)	if(long(f)<0L)return(RC=(ErrCode)(f));
#define DBASSERTHR(f)	if((RC=(ErrCode)(f))!=0)return HRESULT_FROM_ERRCODE(RC)
#define THROW_FAILED_ERRCODE(f)	{ErrCode RC=(ErrCode)(f); if(0!=RC) _com_issue_error(HRESULT_FROM_ERRCODE(RC));}

#if !defined(NODBIO)

#define __Read(dba,Satz)	DBASSERT(z_readrec((DB_ADDR *)&(dba),(char *)&(Satz)))
#define __Write(dba,Satz)	DBASSERT(z_writerec((DB_ADDR *)&(dba),(char *)&(Satz)))
#define __Dispose(dba)		DBASSERT(z_dispose((DB_ADDR *)&(dba)))
#define __New(dba,Satz) 	DBASSERT(z_fillnew((DB_ADDR *)&(dba),(char *)&(Satz)))

#define __ReadHR(dba,Satz)	DBASSERTHR(z_readrec((DB_ADDR *)&(dba),(char *)&(Satz)))
#define __WriteHR(dba,Satz)	DBASSERTHR(z_writerec((DB_ADDR *)&(dba),(char *)&(Satz)))
#define __DisposeHR(dba)	DBASSERTHR(z_dispose((DB_ADDR *)&(dba)))
#define __NewHR(dba,Satz) 	DBASSERTHR(z_fillnew((DB_ADDR *)&(dba),(char *)&(Satz)))

#endif // NODBIO

#else

#define DBASSERT(f)	if((RC=(f))!=0)return RC
#define DBASSERTM(f)	if((RC=(f))<0)return RC
#define __Read(dba,Satz)	DBASSERT(z_readrec(&dba,(char *)&Satz))
#define __Write(dba,Satz)	DBASSERT(z_writerec(&dba,(char *)&Satz))
#define __Dispose(dba)		DBASSERT(z_dispose(&dba))
#define __New(dba,Satz)		DBASSERT(z_fillnew(&dba,(char *)&Satz))

#define __ReadHR(dba,Satz)	DBASSERTHR(z_readrec(&(dba),(char *)&(Satz)))
#define __WriteHR(dba,Satz)	DBASSERTHR(z_writerec(&(dba),(char *)&(Satz)))
#define __DisposeHR(dba)	DBASSERTHR(z_dispose(&(dba)))
#define __NewHR(dba,Satz) 	DBASSERTHR(z_fillnew(&(dba),(char *)&(Satz)))

#endif

// Makros für RelationsTypen --------------------------------------------------
#define UREL	0x01		// Relation von Unten
#define OREL	0x02		// Relation von Oben (ist KomplexObjekt)
#define OUREL	(OREL|UREL)	// beides

#define GREL	0x04		// gleichrangige Relation existiert

#define BRELA	0x08		// hat BegleitObjekt
#define BRELP	0x10		// ist BegleitObjekt
#define BRELAP	(BRELA|BRELP)	// beides

#define HREL(x)		((x)&GREL)	// Zugriffsfunktionen
#define VREL(x)		((x)&OUREL)
#define VRELO(x)		((x)&OREL)
#define VRELU(x)		((x)&UREL)
#define KREL(x)		((x)&(OUREL|GREL))	// Komplexrelationen
#define BREL(x)		((x)&BRELAP)		// Begleitrelationen

// StatusBits im ObjektSatz ---------------------------------------------------
#define SB_TEXTOBJ		0x01
#define SB_TEXTOBJIND	0x02
#define SB_SACHOBJ		0x04

// Bits, die Typ der MerkmalsVerbindung characterisiert -----------------------
#define OBL_MERKMAL		0x0L
#define IDL_MERKMAL		0x40000000L
#define SICHT_MERKMAL	0x80000000L

#if !defined(EXPORT02)
#define EXPORT02
#endif

// DBN-Routinen
long FUNCTYPE dbopen(long  *flag,char  *stdnam,int  stdnam_s);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 fndgi(HPROJECT hPr, long  *nl,long  *cont,long  *on);
long FUNCTYPE fndka(HPROJECT hPr, long  *ltest,struct db_addr  *dbakal,long  *cont);
long FUNCTYPE fndli(HPROJECT hPr, long  *ltest,long  *zvog,long  *cont);
long FUNCTYPE fndma(HPROJECT hPr, long  *ltest,struct db_addr  *dbamal,long  *cont);
long FUNCTYPE fndpu(HPROJECT hPr, long  *ltest,long  *zvog,long  *cont,long  *x1,long  *y1);
long FUNCTYPE getapu(HPROJECT hPr, long  *on,long  *staf,long  *xp,long  *yp);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 getgi(HPROJECT hPr, long  *nl,long  *on,long  *id,long  *staf,long  *lmx,long  *lgi,long  *x,long  *y, long *cont, long *window);
long FUNCTYPE getgif(HPROJECT hPr, long  *nl,long  *zvgi,long  *fex,long  *fey,long  *zkfn, long *cont, long *window);
long FUNCTYPE getgil(HPROJECT hPr, long  *zvgi,long  *fex,long  *fey, long *cont, long *window);
long FUNCTYPE getgip(HPROJECT hPr, long  *zvgi,long  *fex,long  *fey, long *cont, long *window);
long FUNCTYPE getkan(HPROJECT hPr, long  *zkl,long  *wdh,long  *fex,long  *fey, long *cont);
long FUNCTYPE getrif(HPROJECT hPr, long  *nl,long  *on,long  *zmal,long  *ferig,long  *x,long  *y);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 getrig(HPROJECT hPr, long  *nl,long  *on,long  *x,long  *y,long  *rig);
long FUNCTYPE getril(HPROJECT hPr, long  *nl,long  *on,long  *zvol,long  *ferig,long  *x,long  *y);
long FUNCTYPE getrip(HPROJECT hPr, long  *on,long  *zpol,long  *ferig,long  *x,long  *y);
long FUNCTYPE getri(long *nlp, long *on, long *rel);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 gifnd(long  *nl,long  *on,long  *id,long  *staf,long  *lmx,long  *lgi,long  *x,long  *y);
double FUNCTYPE ginhe(long  *eox,long  *eoy,long  *l1,long  *l2);
long FUNCTYPE girig(long  *nl,long  *on,long  *id,long  *staf,long  *lmx,long  *lgi,long  *x,long  *y);
_TRIAS02_ENTRY long __cdecl htfunc(struct db_addr  *dba,long  *cont);
_TRIAS02_ENTRY long __cdecl htmanr(struct db_addr  *dba,long  *cont);

long FUNCTYPE ick(long  *ipx,long  *ipy,long  *iqx,long  *iqy);
void FUNCTYPE ida(long  *idp,long  *ax,long  *ay,long  *ex,long  *ey,long  *px,long  *py);
void FUNCTYPE idam(long  *id,long  *px,long  *py,long  *p1x,long  *p1y,long  *qx,long  *qy,long  *q1x,long  *q1y);
void FUNCTYPE iel(long	*istat,long  *eox,long	*eoy,long  *znp, long *la, long *le, long *leo, long *lleo, long (*ktab)[7],long *lktab,long *llktab,long  *eps);
void FUNCTYPE ielk(long  *istat,long  *eox,long  *eoy,long  *znp, long *la, long *le, long *leo, long *lleo, long (*ktab)[7],long *lktab,long *llktab,long  *eps);
void FUNCTYPE ielp(long  *istat,long  *eox,long  *eoy,long  *znp, long *la, long *le, long *leo, long *lleo, long (*ktab)[7],long *lktab,long *llktab,long  *eps);
long FUNCTYPE iep(long  *istat,long  *eox,long  *eoy,long  *znp,long  (*ktab)[7],long  *eps);
long FUNCTYPE igbpt(long  *ax,long  *ay,long  *ex,long  *ey,long  *px,long  *py,long  *eps);
long FUNCTYPE iglage(long  *px,long  *py,long  *ax,long  *ay,long  *ex,long  *ey);
long FUNCTYPE igppte(long  *xp,long  *yp,long  *x,long  *y,long  *l1,long  *l2);
long FUNCTYPE igptnl(long  *xp,long  *yp,long  *x,long  *y,long  *l,long  *ist);
void FUNCTYPE igsic(long  *irc,long  *x,long  *y,long  *ab,long  *ia,long  *ie,long  *cxmin,long  *cxmax,long  *cymin,long  *cymax,long  *eps);
void FUNCTYPE igsil(long  *irc,long  *x,long  *y,long  *ia,long  *ie,long  *eps);
void FUNCTYPE igsinz(long  *irc,long  *x,long  *y,long  *ia,long  *ie,long  *eps);
long FUNCTYPE igspt(long  *px,long  *py,long  *p1x,long  *p1y,long  *qx,long  *qy,long  *q1x,long  *q1y);
void FUNCTYPE igtesf(long  *irc,long  *x,long  *y,long  *leo,long  *eps);
void FUNCTYPE igumoe(long  *eox,long  *eoy,long  *l1,long  *l2);
void FUNCTYPE inz(long	*lrc,long  *maxgi,long	*lgi,long  *gxi,long  *gyi,long  *jgeo,long  (*ktab)[7],long  *lmktab,long  *eps,long  *zfl, long *sta);
long FUNCTYPE mitest(long  *mi);
void FUNCTYPE ngm(void);
void FUNCTYPE nket(long  *krc,long  *ioc,long  *datnr,long  *zdatnr,long  *sizdat,long  *recnr,long  *zpos,long  *zol);
long FUNCTYPE puinfl(HPROJECT hPr, long  *pktla,long  *xp,long  *yp,long  *onr);
long FUNCTYPE put(long  *on,long  *id,long  *sta,long  *mi,long  *maxgi,long  *lgi,long  *gxi,long  *gyi,long  *eps);
void FUNCTYPE putco(long  *krc,long  *datnr,long  *keynr,long  *sizdat,long  *posnr,long  *vdatnr,long  *stc,long  *ico,long  *zol,long  *iz);
void FUNCTYPE putgi(long  *lrc,long  *gxi,long  *gyi,long  *jgeo,long  (*ktab)[7],long  *sta,long  *zol,long  *zvog,long  *oc,long  *zfl);
void FUNCTYPE putkan(long  *krc,long  *gxi,long  *gyi,long  *jgeo,long  *mast,long  *mzst,long  *pap,long  *pep,long  *cont,long  *zkl);
void FUNCTYPE putkfk(long  *krc,long  *nkno,long  *x2,long  *y2,long  *kn,long  *wix);
void FUNCTYPE putkfo(long  *krc,long  *maak,long  *cont,long  *zol,long  *zkl,long  *zvog,long  *oc,long  *mein);
void FUNCTYPE putkli(long  *krc,long  *zol,long  *zkl,long  *zvog,long  *oc);
void FUNCTYPE putkn(long  *krc,long  *izktab,long  (*ktab)[7],long  *x,long  *y,long  *zol,long  *zkpl);
#if defined(PUT)
void FUNCTYPE putmi(long  *krc, long *sta, long  *mif,long  *zol,long  *zvmi);
#else
void FUNCTYPE putmi(long  *krc,long  *mif,long  *zol,long  *zvmi);
#endif
void FUNCTYPE putozl(long  *krc,long  *ioc,long  *datnr,long  *zdatnr,long  *sizdat,long  *recnr,long  *zpos,long  *zol,long  *ezel);
long FUNCTYPE puttxt_(long  *mi,long  *wfpar,long  *madr);
void FUNCTYPE putvsp(long  *krc,long  (*ktab)[7],long  *izktab,long  *nk,long  *zape,long  *zepe,long  *ezesp,long  *zlsp,long  *cont,long  *zspn,long  *easp);
long __cdecl qtfunc(struct db_addr  *dbapol, ...);
long FUNCTYPE ralset(long  *rel,long  *zrel,long  *zrat,long  *rart);
long FUNCTYPE relset(long  *o1,long  *o2,long  *rart);
long FUNCTYPE rigin(HPROJECT hPr, long  *on,long  *ferig);
long FUNCTYPE rigkp(HPROJECT hPr, long  *on,long  *zkpla,long  *ferig,long  *x,long  *y);
void FUNCTYPE snkn(long  *krc,long  *zkpl,long  *izktab,long  (*ktab)[7],long  *zkl2);
long FUNCTYPE Spl(long  *i,long  *j);
long FUNCTYPE Kl(long  *i,long  *j);
long FUNCTYPE Kpl(long  *i,long  *j);
long FUNCTYPE stinfl(long  *ix1,long  *iy1,long  *ix2,long  *iy2,long  *ixc1,long  *iyc1,long  *ixc3,long  *iyc3);
long FUNCTYPE win(long  *lrc,long  *x1,long  *y1,long  *x2,long  *y2);
long FUNCTYPE profil(long  *nl,long  *xa,long  *ya,long  *xe,long  *ye,long  *xs,long  *ys,long  *on);

// Merkmale
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 fndmi(HPROJECT hPr, long  *whlg,long  *mko,char  *tkz1,double  *wi1,char  *tkz2,double  *wi2,long  *on);
long FUNCTYPE fndmw(HPROJECT hPr, long  *mko,long  *zmkl,long  *ty,char  * *tkz,double  *wie,long  *on);
long FUNCTYPE gettxt_(HPROJECT hPr, long  *kod,long  *madr,long  *lt,long  *mi);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 FindPattern (HPROJECT hPr, long Code, char *Text, short iMode, long *Obj);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 TextFind (HPROJECT hPr, long lMCode, char *pText, short iMode, short iTarget, long *pflObj);

// das neue DEL ---------------------------------------------------------------
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 del (HPROJECT hPr, long);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 delgi (HPROJECT hPr, long);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 delgip (HPROJECT hPr, long);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 delgil (HPROJECT hPr, long);
long FUNCTYPE delkan (HPROJECT hPr, long, long);
long FUNCTYPE DeletePoints (HPROJECT hPr, long);
long FUNCTYPE DeleteNode (HPROJECT hPr, long, long);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 delgif (HPROJECT hPr, long);
long FUNCTYPE delkanf (HPROJECT hPr, long, long);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 delmi (HPROJECT hPr, long, long, short);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 delid (HPROJECT hPr, long lONr, int *piOType);
_TRIAS02_ENTRY long FUNCTYPE DelLink (HPROJECT hPr, long, long *, long);
_TRIAS02_ENTRY long FUNCTYPE DelLinkVMO (HPROJECT hPr, long *Begin, long Wert, long lMCode);
_TRIAS02_ENTRY long FUNCTYPE DelLinkVIO (HPROJECT hPr, long *Begin, long Wert, long lIdent, enum tagLINKTYPE);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 DelRelation (HPROJECT hPr, long ON1, long ON2, long RelCode, short RelTyp);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 DelAllRelations (HPROJECT hPr, long ONr);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 DelText (HPROJECT hPr, long First, BOOL fText = false);

long FUNCTYPE TestLink (HPROJECT hPr, long, long, long);
long FUNCTYPE TestLinkVIO (HPROJECT hPr, long lFirst, long lValue, long lIdent, enum tagLINKTYPE, enum tagLINKTYPE *prgLink);

// das neue PUT ---------------------------------------------------------------
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 PutMiText (HPROJECT hPr, long, long, short, char *, BOOL fTextMCode);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 PutText (HPROJECT hPr, const char *, short, long *);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 PutTextEx (HPROJECT hPr, const char *, short, long *, long, int fText = false);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 PutLink (HPROJECT hPr, long, long *, long);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 PutLinkVMO (HPROJECT hPr, long *, long, long);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 PutLinkVIO (HPROJECT hPr, long *, long, long, enum tagLINKTYPE);
long FUNCTYPE PutChainEnd (HPROJECT hPr, long, long *, long);
_TRIAS02_ENTRY long FUNCTYPE PutRelation (HPROJECT hPr, long ON1, long ON2, long RelCode, short RelTyp);

long FUNCTYPE PutObject (HPROJECT hPr, long *pONr, long Ident, long *pX, long *pY);

struct idl;
_TRIAS02_ENTRY BOOL IsEmptyIDL (HPROJECT hPr, struct idl *pIdl);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 PutObjTemplate (HPROJECT hPr, long *pOBL, long lIdent);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 PutIdent (HPROJECT hPr, long ONr, long Ident, int iOTyp, long *pIDL);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 VerifyIdent (HPROJECT hPr, long ONr, long lIDL, int iOTyp);
long FUNCTYPE PutPunkt (HPROJECT hPr, long ONr, long X, long Y, long *pPOL);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 PutTextObject (HPROJECT hPr, long *pOBL, long Ident, long MCode, long X, long Y, char *pText, BOOL fIndObjProp);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 PutPunktObject (HPROJECT hPr, long *pOBL, long Ident, long X, long Y);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 PutLineObject (HPROJECT hPr, long *pOBL, long Ident, long *pX, long *pY, long iNum);
struct kcont;
long FUNCTYPE PutKante (HPROJECT hPr, long *pX, long *pY, long iNum, long *pKPL, struct kcont *kcont);
long FUNCTYPE LinkKante (HPROJECT hPr, long lONr, long lKante, long *povol);
long FUNCTYPE PutKnoten (HPROJECT hPr, long x, long y, long zkpl, long *pkal);
long FUNCTYPE ChainKnoten (HPROJECT hPr, long lKPL, long lKante);
long FUNCTYPE PutPoints (HPROJECT hPr, long *pX, long *pY, long iNum, long *pkal, struct kcont *pkcont);
long FUNCTYPE PutPoint (HPROJECT hPr, long x, long y, long *pspl);

_TRIAS02_ENTRY long FUNCTYPE EXPORT02 PutAreaObject (HPROJECT hPr, long *pOBL, long Ident, long *pX, long *pY, long *pK, long lCnt, short iKCnt);
long FUNCTYPE PutMasche (HPROJECT hPr, long *pX, long *pY, long *pK, long lCnt, short iKCnt, long *pKFL);
long FUNCTYPE LinkMasche (HPROJECT hPr, long lONr, long lMasche);
long FUNCTYPE LinkKanteM (HPROJECT hPr, long lONr, long lKFM);

_TRIAS02_ENTRY long FUNCTYPE EXPORT02 PutKomplexObject (HPROJECT hPr, long *pOBL, long Ident, long RCode, short iRTyp, short iCnt, long *pObjs);

short FUNCTYPE FindRelation (HPROJECT hPr, long, long, long, short, long *);

_TRIAS02_ENTRY long FUNCTYPE EXPORT02 CreateTarget (HPROJECT hPr, short iTTyp, long lTarget, long *pulNewTarget);

// das neue GET ---------------------------------------------------------------
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 GetMiText (HPROJECT hPr, long, long, short, char **);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 GetTarget (HPROJECT hPr, void *, short);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 GetText (HPROJECT hPr, long, char *, long, int fText = false);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 GetTextOld (HPROJECT hPr, long madr, char *mi, long Len);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 GetTextLen (HPROJECT hPr, long, long *);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 GetMerkLen (HPROJECT hPr, long, long *);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 GetMerkLong (HPROJECT hPr, long, long *, long);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 GetMerkDouble (HPROJECT hPr, long, double *, long);
long FUNCTYPE GetVOMMI (HPROJECT hPr, long *, long);

// das neue MOD ---------------------------------------------------------------
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 modid (HPROJECT hPr, long, long);

// das neue OVL ---------------------------------------------------------------
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 OvlPunktObject (HPROJECT hPr, long *pOBL, long Ident, long TONr);
long FUNCTYPE OvlPunkt (HPROJECT hPr, long ONr, long PolNr);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 OvlLineObject (HPROJECT hPr, long *pOBL, long Ident, long TONr);
long FUNCTYPE OvlLinie (HPROJECT hPr, long ONr, long *pNewChain, long lVolNr);
long FUNCTYPE OvlKante (HPROJECT hPr, long ONr, long lKalNr);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 OvlAreaObject (HPROJECT hPr, long *pOBL, long Ident, long TONr);
long FUNCTYPE OvlArea (HPROJECT hPr, long ONr, long *pNewChain, long lVomaNr);
long FUNCTYPE OvlMasche (HPROJECT hPr, long ONr, long lKalNr);

// sonstige Funktionen --------------------------------------------------------
_TRIAS02_ENTRY int FUNCTYPE EXPORT02 isalike (char *, char *);
_TRIAS02_ENTRY char * FUNCTYPE EXPORT02 FormatDate (char *, int);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 GeoDBVersion (HPROJECT hPr);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 AssociatedObjekt (INT_PTR lONr, bool *pfRelated);
_TRIAS02_ENTRY long FUNCTYPE EXPORT02 AssociatedTextObjekt (INT_PTR);

_TRIAS02_ENTRY long FUNCTYPE EXPORT02 GetKomplexObjects (HPROJECT hPr, long, long);

void FUNCTYPE UpdateContainer (struct kcont *pCont, long x, long y);
long FUNCTYPE Winkel (long, long, long, long);

_TRIAS02_ENTRY bool WINAPI DrawRectangle (HDC hDC, int x1, int y1, int x2, int y2);
_TRIAS02_ENTRY long EXPORT02 FindLong (long *, long, long);
_TRIAS02_ENTRY BOOL EXPORT02 ExpandPalette (HPALETTE hPal, class VisInfo *pVI);
_TRIAS02_ENTRY BOOL EXPORT02 ExpandPaletteColor (HPALETTE hPal, COLORREF C);
_TRIAS02_ENTRY class VisInfo * EXPORT02 MakeNewVI (enum VisType iVTyp);
_TRIAS02_ENTRY short EXPORT02 MakeCompleteNewVisInfo (VisInfo **ppVI, short iBits, BOOL fSpecial);

// String-Utilities
_TRIAS02_ENTRY char *WINAPI DtoA (char *, char *, double);

#include <poppack.h>

#if defined(__cplusplus)
}
#endif

#endif // defined(_FORCE_LEGACY_CODE)

#endif  // _ZRPOTOS_H


