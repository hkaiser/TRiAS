// Fortran(C)-Schnittstelle
// File: FPROTOS.H

#ifndef _FPROTOS_H
#define _FPROTOS_H

#if defined(__cplusplus)
extern "C" {
#endif

#include <trias01m.hxx>		// Manifestkonstanten

struct db_addr;

// _TRIAS01_ENTRY long  FUNCTYPE EXPORT01 zact_(long *dblun);
// _TRIAS01_ENTRY long  FUNCTYPE EXPORT01 zclose_(long  *db_slot);
// _TRIAS01_ENTRY long  FUNCTYPE EXPORT01 zdestr_(char  *dbname,int  *p_flag);
// _TRIAS01_ENTRY long  FUNCTYPE EXPORT01 zdisp_(long *dba);
// _TRIAS01_ENTRY long  FUNCTYPE EXPORT01 zfiles_(int  num);
// _TRIAS01_ENTRY long  FUNCTYPE EXPORT01 zfind_(long *dba, long *keyno, void *keyptr);
// _TRIAS01_ENTRY long  FUNCTYPE EXPORT01 zfirst_(long *dba,long	*keyno);
// _TRIAS01_ENTRY long  FUNCTYPE EXPORT01 zinit_(char  *dbspec, char *dbname,int *p_flag);
// _TRIAS01_ENTRY long  FUNCTYPE EXPORT01 zkread_(void *keyptr);
// _TRIAS01_ENTRY long  FUNCTYPE EXPORT01 zlast_(long *dba,long	*keyno);
// _TRIAS01_ENTRY long  FUNCTYPE EXPORT01 znew_(long *dba,void	*ptr);
// _TRIAS01_ENTRY long  FUNCTYPE EXPORT01 znext_(long *dba,long	*keyno);
// _TRIAS01_ENTRY long  FUNCTYPE EXPORT01 zopen_(char  *s_dbfile,int  l_dbfile,char  *s_uname,int  l_uname,char  *s_passwd,int  l_passwd);
// _TRIAS01_ENTRY long  FUNCTYPE EXPORT01 zpages_(int  num);
// _TRIAS01_ENTRY long  FUNCTYPE EXPORT01 zprev_(long *dba,long	*keyno);
// _TRIAS01_ENTRY long  FUNCTYPE EXPORT01 zread_(long *dba, void *ptr);
// _TRIAS01_ENTRY long  FUNCTYPE EXPORT01 zwrite_(long *dba, void *ptr);
#if defined(_MSC_VER) || defined(__WATCOMC__)
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 htwind_(HPROJECT hPr, long  *cont, long (* fkt)(struct db_addr *, long *), long *keyno);
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 qtwind_(HPROJECT hPr, long  *cont, long (* fkt)(struct db_addr *, ...), long *keyno);
#else
long  FUNCTYPE htwind_(long  *cont,long __cdecl (*fkt)(long *, long *), long	*keyno);
long  FUNCTYPE qtwind_(long  *cont,long __cdecl (*fkt)(long *), long *keyno);
#endif
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 dbcodb_(HPROJECT hPr, long *cont);
_TRIAS01_ENTRY void  FUNCTYPE dbinit_(void);
// _TRIAS01_ENTRY long  FUNCTYPE errfkt_(long *errcode, long *errmode, int (*errfunc)(int, int, ...));
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 feini_(long *num);
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 ferel_(long *num);
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 feput_(long *num, long *new_elem);
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 feget_(long *num, long *index, long *elem);
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 felen_(long *num, long *len);
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 feread_(long *num, long *begin, long *len, long *feld);
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 fewrit_(long *num, long *begin, long *len, long *feld);
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 flqsrt_(long *num);
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 flredn_(long *num, long *len);
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 FlexAdr (short num, long **ptr);
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 FlexShrink (short num, short iFlag);
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 ladr_(HPROJECT hPr, short *lon, bool fLast);
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 lrec_(short *lon);
_TRIAS01_ENTRY void  __cdecl EXPORT01 reslis_(void);
struct db_addr;
_TRIAS01_ENTRY long  __cdecl EXPORT01 putlis_(struct db_addr *dba, ...);
_TRIAS01_ENTRY int  __cdecl EXPORT01 getlis_(short *lon, long *rec_no);
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 ngmini_(HPROJECT hpr, long *recno, long *ist, long *w);
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 ngmc_(long *recno, long *ist);
// _TRIAS01_ENTRY long  FUNCTYPE EXPORT01 seterr_(long *errcode, long *routine, void *D);
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 emessg_(long *new_flag);
struct error_list;
_TRIAS01_ENTRY long  FUNCTYPE EXPORT01 setvec_(struct error_list *errtab, long *len);

#if defined(__cplusplus)
}
#endif

#endif // _FPROTOS_H
