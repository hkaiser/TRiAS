// Prototypen aller ZIPEDB - Funktionen
// File: PROTOS.H

#if !defined(_PROTOS_H)
#define _PROTOS_H

#include <pshpack1.h>

#if defined(__cplusplus)
extern "C" {
#endif

#if !(defined(MSWIND) || defined(_WINDOWS)) && !defined(__386__)

#if !defined(FAR)
#define FAR __far
#endif

#elif (defined(__WATCOMC__) && defined(__386__)) || defined(WIN32)

// alle Speichermodellspezifika herausnehmen
#undef FAR
#undef __near
#undef __far
#undef _far
#undef far

#define FAR
#define __near
#define __far
#define _far
#define far

#endif

#include <trias01m.hxx>		// Manifestkonstanten

#if defined(WIN32)
#define __huge
#endif

#if !defined(NEWDBVERSION)
#define BASICRELEASENUM	0x05000000L
#define NEWDBVERSION	0x05000003L
#define VERSION05000004 0x05000004L
#define VERSION05000005 0x05000005L
#define VERSION05000006 0x05000006L
#define VERSION05000007 0x05000007L
#define VERSION05000008 0x05000008L
#define VERSION05000009 0x05000009L
#define VERSION0500000A 0x0500000AL
#define VERSION0500000B 0x0500000BL
#define VERSION05000100 0x05000100L
#define LASTDBVERSION	VERSION0500000B

#define PBDVERSION03000001	0x03000001L
#define PBDVERSION03000002	0x03000002L
#define PBDVERSION03000003	0x03000003L
#define PBDVERSION0500000A	0x0500000AL

#endif

// ProjectHandle
#if defined(MSWIND) || defined(_WINDOWS)
#if !defined(_DEFINED_HPROJECT)
#define _DEFINED_HPROJECT
DECLARE_HANDLE(HPROJECT);
#endif
#else
#define HPROJECT int
#endif

#if !defined(DELETE)
	#define DELETE(x) {if(x){delete (x); (x)=NULL;}}
	#if defined(MSCC8) || _MSC_VER >= 800
		#define DELETE_VEC(x)	{if(x){delete [] (x); (x)=NULL;}}
	#else
		#define DELETE_VEC(x,s)	{if(x){delete [(s)] (x); (x)=NULL;}}
	#endif
#endif

#define DELETE_VEC(x)   {if(x){delete [] (x); (x)=NULL;}}
#define DELETE_OBJ(x)   {if(x){delete (x); (x)=NULL;}} 

// Modi des Speicherns einer/aller Datenbasis(en) -----------------------------
#define FLUSH_NODATA	0
#define FLUSH_ACTDB	1
#define FLUSH_ALLDATA	2

#if defined(__WATCOMC__)
#pragma warning 583 4;
#pragma warning 594 4;
#endif

typedef struct IStream * LPSTREAM;	// nur deklarieren
typedef struct IStorage *LPSTORAGE;

// Strukturen deklarieren, damit __WATCOMC__ beruhigt ist
struct tagDBASE;
union hypercube;
struct container;
struct db_addr;
struct pg_entry;
struct file_entry;
struct key_entry;
struct rec_entry;
struct htslot;
struct qtslot;
struct key_slot;
struct pg_zero;
struct dbpasswd;
struct window;
struct node;
union quadrant;
struct point;

struct tagDBASE * FUNCTYPE activate (struct tagDBASE *new_db);
int FUNCTYPE asm_buf(long left, long right, void *key, short *nkeys, short slot, short level);
void * FUNCTYPE binary(char __far *key, char __far *base, unsigned short *nelp, unsigned short width, short (FUNCTYPE *compar)(void __far *, void __far *), int todo_flag);
_TRIAS01_ENTRY int FUNCTYPE bit(unsigned long x, short bitnr);
_TRIAS01_ENTRY unsigned long FUNCTYPE bis(unsigned long x, short bitnr);
_TRIAS01_ENTRY short FUNCTYPE bitcnt(unsigned long x);
int FUNCTYPE combine(long left, long right, short slot, short level);
_TRIAS01_ENTRY char * FUNCTYPE EXPORT01 crypt(char *pw, char *salt);
short FUNCTYPE cube(union hypercube *hc, struct container *w, short flag);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 z_close(HPROJECT db_slot);
#if defined(MSWIND) || defined(_WINDOWS)
_TRIAS01_ENTRY HPROJECT FUNCTYPE EXPORT01 z_open(char __far *dbfile, char __far *uname, char __far *passwd, BOOL fRO);
_TRIAS01_ENTRY HPROJECT FUNCTYPE EXPORT01 OpenStorageProject (LPSTORAGE, struct tagDBASE *, const char *, const char *, const char *, BOOL);
#if defined(WIN32)
_TRIAS01_ENTRY HPROJECT FUNCTYPE z_open_storage (LPSTORAGE pIStorage, bool fRO);
_TRIAS01_ENTRY HPROJECT FUNCTYPE CreateTempStorageProject (struct tagDBASE *);
_TRIAS01_ENTRY HRESULT FUNCTYPE RenameStorageProject (HPROJECT hPr, LPCTSTR pszFile);
#endif // WIN32
_TRIAS01_ENTRY HRESULT FUNCTYPE GetProjectStorage (HPROJECT hPr, LPSTORAGE *ppIStorage);
short FUNCTYPE InitSharedAccess (HFILE *pfhShared, char *pDBName, char *pUsername);
HFILE FUNCTYPE AskToOpenRO (void);
#else
int FUNCTYPE z_open(char *dbfile, char *uname, char *passwd, char *pExt);
#endif
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 z_access (long);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 z_raccess (long);
int FUNCTYPE db_read(struct db_addr *dba, void * *recptr);
int FUNCTYPE db_write(struct db_addr *dba, void *recptr);
int FUNCTYPE tdb_read(struct db_addr *dbkey, void __far * *recptr);
int FUNCTYPE tdb_write(struct db_addr *dbkey, void __far *recptr);
int FUNCTYPE replace_page(struct pg_entry __far **pPage, struct tagDBASE __far *pDB, short filenum, long pageno);
_TRIAS01_ENTRY int FUNCTYPE db_flush(int, struct tagDBASE *pDB = 0);
void FUNCTYPE db_free(void);
int FUNCTYPE kdel(long nod, void *key, short level);
int FUNCTYPE dio_init(struct tagDBASE *pDB = 0);
int FUNCTYPE dio_pzinit (void);
short FUNCTYPE InitPageZeroTable (struct tagDBASE *pDB);
_TRIAS01_ENTRY int __cdecl einvaddr (int errcode, int routine, ...);
_TRIAS01_ENTRY int __cdecl enomem (int errcode, int routine, ...);
_TRIAS01_ENTRY int __cdecl EXPORT01 ReportVisError (int err_code, int r_code, ...);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 err_install(long err_code, int (*error_func)(int, int, ...), int (* *old_errfunc)(int, int, ...));
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 ExtErrInstall(long err_code, int (*error_func)(int, int, ...), int (* *old_errfunc)(int, int, ...), void *pData);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 ReleaseErrorTree(void);
_TRIAS01_ENTRY long FUNCTYPE err_type(long errcode);
_TRIAS01_ENTRY int (*err_func(long errcode))(int, int, ...);
_TRIAS01_ENTRY void * FUNCTYPE err_data (long err_code);
int FUNCTYPE file_close(struct file_entry __far *ft_p, int fForceClosing = 0);
int FUNCTYPE file_open(struct file_entry __far *ft_p);
_TRIAS01_ENTRY int FUNCTYPE gen_backup(struct file_entry __far *bf_p, struct pg_zero __far *pz_p, char *copyright, unsigned long	time_val);
void FUNCTYPE setdwent(char __far *dwdfile);
void FUNCTYPE enddwent(void);
struct dbpasswd * FUNCTYPE getdwent(void);
struct dbpasswd * FUNCTYPE getdwnam(char __far *name, char __far *dbname);
struct dbpasswd * FUNCTYPE getdwuid(int dbuid, char __far *dbname);
struct dbpasswd * FUNCTYPE GetPWDName (LPSTORAGE pIStorage, const char *pUser);
struct dbpasswd * FUNCTYPE GetNextPWDEntry (LPSTREAM pIStream);

char * FUNCTYPE getpath(char *buff, char __far *name, int size);
_TRIAS01_ENTRY int FUNCTYPE htcont(struct container *cont, short keyindex);
int FUNCTYPE ht_del(long node, union hypercube *hc, struct htslot __far *data, short level);
int FUNCTYPE ht_ins(long node, union hypercube *hc, struct htslot __far *data, short level);
int FUNCTYPE ht_insert(struct container __far *w_key, struct db_addr *db_addr);
int FUNCTYPE ht_delete(struct container __far *w_key, struct db_addr *db_addr);
int FUNCTYPE htprep(struct container __far *w_key, struct db_addr *db_addr);
int FUNCTYPE htsearch(long node, union hypercube *hcube, short level);
int FUNCTYPE ht_shrink(struct htslot __far *data, short level);
int FUNCTYPE ht_split(union hypercube *hc, short level);
#if defined(_MSC_VER)
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 hwindow(struct window *window, long (__cdecl *action)(struct db_addr *, ...), short keyindex);
#else
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 hwindow(struct window *window, long __cdecl (*action)(struct db_addr *, ...), short keyindex);
#endif
int FUNCTYPE htwalk(struct htslot *node, union hypercube *hc, short level, short comp);
int FUNCTYPE inittab(char *dbname, struct dbpasswd *dwd, int dbf, int fRO);
short FUNCTYPE InitTables (LPSTORAGE pIStorage, struct tagDBASE *pDB, const char *pName, 
			   unsigned long dwAccess, int fRO);
int FUNCTYPE ins(long nod, void *key, short level);
void FUNCTYPE key_cat(void __far *key_val, long *db_ad);
int FUNCTYPE key_cmp(void *keyval, void	__far *buffer, short filled, short __far *sln);
int FUNCTYPE key_del(int keyindex, long *key_val, struct db_addr *db_ad);
int FUNCTYPE key_first(short keyindex, struct db_addr *dba);
int FUNCTYPE key_init(struct key_entry __far *key_ptr);
int FUNCTYPE key_ins(int keyindex, void	*key_val, struct db_addr *db_ad);
int FUNCTYPE key_last(short keyindex, struct db_addr *dba);
int FUNCTYPE key_loc(void *keyval, int keyindex,struct	db_addr *dba);
int FUNCTYPE key_next(int keyindex, struct db_addr *dba);
int FUNCTYPE key_prev(int keyindex, struct db_addr *dba);
int FUNCTYPE key_read(void *keyval);
int FUNCTYPE insert_key(struct db_addr *dba, void __far *ptr);
int FUNCTYPE delete_key(struct db_addr *dba, void __far *ptr);
int FUNCTYPE dio_get(long page_no, struct node	__far * *pg_ptr);
int FUNCTYPE dio_touch(long page_no);
int FUNCTYPE locate(void *keyval, struct db_addr *dba);
int FUNCTYPE locate_first(struct db_addr *dba);
int FUNCTYPE locate_last(struct db_addr *dba);
int FUNCTYPE locate_slot(void __far *key, void __far *buffer, short n, short *slot);
_TRIAS01_ENTRY unsigned short FUNCTYPE EXPORT01 mycrypt (unsigned char *ptr, short n);
int FUNCTYPE NodeExpand(long nod, void *key, short level);
int FUNCTYPE fill_nodes(long ch1, long ch2, long ch3, short m, short n, short level);
int FUNCTYPE split_nodes(long left, long right, void *key, short slot, short level);
int FUNCTYPE nullcmp(void __far *cptr, int len);
int FUNCTYPE overflow(long left, long right, void *key, short slot, short level);
int FUNCTYPE parent_slot(short level, long nod, long *next, long *prev);
_TRIAS01_ENTRY int FUNCTYPE db_pzflush(int, struct tagDBASE *pDB = 0);
_TRIAS01_ENTRY int FUNCTYPE db_pzalloc(short fno, long *loc);
int FUNCTYPE db_pzfree(short fno, long loc);
void FUNCTYPE put_inline(void __far *key, void __far *buffer, short n, short u_gr);
_TRIAS01_ENTRY int FUNCTYPE qtcont(struct container *cont, short keyindex);
int FUNCTYPE qt_page(struct container *c_p, char filled);
int FUNCTYPE qt_del(long node, union quadrant *qd, struct qtslot *data, short level);
int FUNCTYPE qt_ins(long node, union quadrant *qd, struct qtslot *data, short level);
int FUNCTYPE qt_insert(struct point __far *w_key, struct db_addr *db_addr);
int FUNCTYPE qt_delete(struct point __far *w_key, struct db_addr *db_addr);
int FUNCTYPE qtprep(struct point __far *w_key,struct db_addr *db_addr);
int FUNCTYPE qtsearch(long node, union quadrant *quadleaf,short level);
int FUNCTYPE qt_shrink(struct qtslot *data, short level);
int FUNCTYPE qt_split(union quadrant *qd, short level);
#if defined(_MSC_VER)
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 qwindow(struct window *window, long (__cdecl *action)(struct db_addr *, ...), short keyindex);
#else
int FUNCTYPE qwindow(struct window *window, long __cdecl (*action)(struct db_addr *, ...), short keyindex);
#endif
int FUNCTYPE qtwalk(struct qtslot *node,union quadrant *qd, short level, short comp);
short FUNCTYPE quad(union quadrant *qd, struct point *w, short flag);
int FUNCTYPE split_root(struct node __far *nd, struct key_slot *key, short level);
_TRIAS01_ENTRY int __cdecl EXPORT01 db_error (int errcode, int routine, ...);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 default_db_error (int, int);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 set_db_status (int errcode);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 GetDBStatus (void);
_TRIAS01_ENTRY int FUNCTYPE act_meta(struct tagDBASE * *olddb);
_TRIAS01_ENTRY int __cdecl error_message(struct tagDBASE * *olddb, int errcode, int routine, char *pExtraText);
_TRIAS01_ENTRY void FUNCTYPE store_error(int *errcode, int routine);
int FUNCTYPE shrink(long nod, short i, short level);
_TRIAS01_ENTRY char * FUNCTYPE EXPORT01 strnchr(char __far *ptr, char z, int len);
_TRIAS01_ENTRY char * FUNCTYPE EXPORT01 strrlchr(char __far *ptr, char z);
int FUNCTYPE t_locate_slot (void *lockey, void *buffer, short n, short *slot);
void FUNCTYPE t_put_inline(void __far *key, void __far *buffer, short n, short u_gr);
int FUNCTYPE t_zap_slot(void __far *buffer, short slot, short n);
_TRIAS01_ENTRY HPROJECT FUNCTYPE EXPORT01 z_activate(HPROJECT num);
int FUNCTYPE zap_slot(void __far *buffer, short slot, short n);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 z_dispose(struct db_addr *dba);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 z_fillnew(struct db_addr *dba, void *ptr);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 z_keyfind(struct db_addr *dba, int	keyno, void *keyptr);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 z_keyfirst(struct db_addr *dba, int keyno);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 z_keylast(struct db_addr *dba, int	keyno);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 z_keynext(struct db_addr *dba, int	keyno);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 z_keyprev(struct db_addr *dba, int	keyno);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 z_keyread(void __far *keyptr);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 z_readrec(struct db_addr *dba, void __far *ptr);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 z_restore(HPROJECT  db_slot);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 z_setfiles(int num);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 z_setpages(int num);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 z_touch(HPROJECT db_slot);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 z_writerec(struct db_addr *dba, void __far *ptr);
void FUNCTYPE myqsort(void __far *baseP, unsigned int nElem, unsigned int width, long (__cdecl *compar)(const long __far *, const long __far *));
_TRIAS01_ENTRY int FUNCTYPE ReIndexFile (short iFile, short iRecord, short iKeyFile, short (EXPORT01 *pProc)(void *));
_TRIAS01_ENTRY int FUNCTYPE db_pzreread (struct tagDBASE *pDB = 0);

_TRIAS01_ENTRY short FUNCTYPE EXPORT01 CreateDataFile (char *pFName, const char *pCopyRight, long TimeVal, short iPageSize);
_TRIAS01_ENTRY short FUNCTYPE EXPORT01 CreateKeyFile (char *pFName, const char *pCopyRight, long TimeVal, short iPageSize);
_TRIAS01_ENTRY short FUNCTYPE EXPORT01 CreateGeoTreeFile (char *pFName, const char *pCopyRight, long TimeVal, short iPageSize);
_TRIAS01_ENTRY short FUNCTYPE EXPORT01 CreateTreeKeyFile (char *pFName, const char *pCopyRight, long TimeVal, short iPageSize);
_TRIAS01_ENTRY short FUNCTYPE EXPORT01 CreateBackupFile (char *pFName, const char *pCopyright, long TimeVal, struct pg_zero __far *pPZTable, short iFiles, short iPageSize);

_TRIAS01_ENTRY short FUNCTYPE EXPORT01 CreateDataStream (LPSTREAM pIStream, const char *pCopyRight, long TimeVal, short iPageSize);
_TRIAS01_ENTRY short FUNCTYPE EXPORT01 CreateKeyStream (LPSTREAM pIStream, const char *pCopyRight, long TimeVal, short iPageSize);
_TRIAS01_ENTRY short FUNCTYPE EXPORT01 CreateGeoTreeStream (LPSTREAM pIStream, const char *pCopyRight, long TimeVal, short iPageSize);
_TRIAS01_ENTRY short FUNCTYPE EXPORT01 CreateTreeKeyStream (LPSTREAM pIStream, const char *pCopyRight, long TimeVal, short iPageSize);
_TRIAS01_ENTRY short FUNCTYPE EXPORT01 CreateBackupStream (LPSTREAM pIStream, const char *pCopyright, long TimeVal, struct pg_zero __far *pPZTable, short iFiles, short iPageSize);

_TRIAS01_ENTRY long FUNCTYPE EXPORT01 delhd_(long *key);
int FUNCTYPE delete_head(char *key,struct db_addr *dba);
_TRIAS01_ENTRY long FUNCTYPE EXPORT01 gethd_(char *text,int l_text,long *len,long *key);
#if defined(DLL)
_TRIAS01_ENTRY long FUNCTYPE EXPORT01 puthd_(char *s_text,int l_text,long *len,long *key);
#else
long FUNCTYPE puthd_(char *s_text,int l_text,long *len,long *key,short iNew);
#endif
int FUNCTYPE store_head(long *key,long len,char *text);
_TRIAS01_ENTRY int FUNCTYPE EXPORT01 gethdlen (long *key, short *len);

_TRIAS01_ENTRY void __cdecl EXPORT01 ErrorWindow (struct tagDBASE * *, const char __far *, const char __far *, ...);
void FUNCTYPE replace_ext (char *, char *);
_TRIAS01_ENTRY void FUNCTYPE EXPORT01 SetErrorDBEnv (char *);
_TRIAS01_ENTRY short FUNCTYPE EXPORT01 SetCopyrightFlag (short);

_TRIAS01_ENTRY long FUNCTYPE EXPORT01 GetDBVersion (HPROJECT = 0);

int FUNCTYPE prim (int);

_TRIAS01_ENTRY void FUNCTYPE EXPORT01 InitTrias01 (HWND, UINT, UINT, UINT);
_TRIAS01_ENTRY void FUNCTYPE EXPORT01 CleanUpTrias01 (void);
_TRIAS01_ENTRY struct rec_entry *FUNCTYPE EXPORT01 RecordTable (short iIndex);


#if defined(__cplusplus)
}
#endif

#if defined(WIN32)
#if !defined(OLE2ANSI)
_TRIAS01_ENTRY LPWSTR ConvertStrAtoW (const char *strIn, LPCWSTR buf, UINT size);
// _TRIAS01_ENTRY LPWSTR WideString (const char *strIn);
// _TRIAS01_ENTRY char *ConvertStrWtoA (LPCWSTR strIn, char *buf, UINT size);	
// _TRIAS01_ENTRY char *AnsiString (LPCWSTR strIn);
#else
#define ConvertStrAtoW(strIn,buf,size)	((const char *)(strIn))
#define WideString(strIn) 		((const char *)(strIn))
#define ConvertStrWtoA(strIn,buf,size)	((const char *)(strIn))
#define AnsiString(strIn) 		((const char *)(strIn))
#endif // OLE2ANSI
#else
#define ConvertStrAtoW(strIn,buf,size)	((const char *)(strIn))
// #define WideString(strIn) 		((const char *)(strIn))
// #define ConvertStrWtoA(strIn,buf,size)	((const char *)(strIn))
// #define AnsiString(strIn) 		((const char *)(strIn))
#endif // WIN32

#include <poppack.h>

#endif // _PROTOS_H
