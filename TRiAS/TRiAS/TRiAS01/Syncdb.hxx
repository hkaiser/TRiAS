// Klasse, die gewährleistet, daß jeweils nur ein Thread die DB-Funktionen
// benutzt
// File: SYNCDB.HXX

#if !defined(_SYNCDB_HXX)
#define _SYNCDB_HXX

class CDbAccess : 
	public CSyncMonitor 
{
public:
	CDbAccess(bool fUseMtx = true) : CSyncMonitor(fUseMtx) {}

// functions, that should be able to use CDbAccess 
friend int FUNCTYPE z_setfiles (int);
friend int FUNCTYPE z_setpages (int);

friend HPROJECT FUNCTYPE z_open (LPSTR, LPSTR, LPSTR, BOOL, DWORD);
friend HPROJECT FUNCTYPE z_open_ex (LPSTR, LPSTR, LPSTR, BOOL, DWORD, BOOL);
friend int FUNCTYPE z_close (HPROJECT, BOOL);
friend long FUNCTYPE GetDBVersion (HPROJECT);
friend HPROJECT FUNCTYPE z_activate (HPROJECT);
friend int FUNCTYPE z_access (HPROJECT, long); 
friend int FUNCTYPE z_raccess (HPROJECT, long);

friend BOOL FUNCTYPE GetCopyMode (HPROJECT hPr, BOOL *pfRO);
friend BOOL FUNCTYPE GetROMode (HPROJECT hPr, BOOL *pfRO);
friend BOOL FUNCTYPE CouldOpenTarget (HPROJECT hPr, BOOL *pfCouldOpen);
friend BOOL FUNCTYPE IsDirty (HPROJECT hPr, BOOL *pfDirty);
friend BOOL FUNCTYPE SetDirty (HPROJECT hPr, BOOL fDirty);
friend BOOL FUNCTYPE IsOpened (HPROJECT hPr, BOOL *pfOpened);
friend BOOL FUNCTYPE GetRelatedProject (HPROJECT hPr, HPROJECT *phPr);
friend BOOL FUNCTYPE SetRelatedProject (HPROJECT hPr, HPROJECT hPrRel);
friend HRESULT FUNCTYPE GetGeometryGuid (HPROJECT hPr, long lIdent, LPCSTR pcName, _GUID *pGuid);
friend HRESULT FUNCTYPE GetGeometryGuids (HPROJECT hPr, long *pCnt, _GUID **pGuids);

friend int FUNCTYPE z_keyfind (DB_ADDR *, int, void *);
friend int FUNCTYPE z_keyread (HPROJECT hPr, void *);
friend int FUNCTYPE z_keyprev (DB_ADDR *, int);
friend int FUNCTYPE z_keynext (DB_ADDR *, int);
friend int FUNCTYPE z_keyfirst (DB_ADDR *, int);
friend int FUNCTYPE z_keylast (DB_ADDR *, int);
friend void FUNCTYPE SetKeyContext (struct tagKEYCONTEXT *); 
friend void FUNCTYPE GetKeyContext (struct tagKEYCONTEXT *);
friend int FUNCTYPE qwindow (HPROJECT hpr, struct window *, long (*)(DB_ADDR *, ...), short);
friend int FUNCTYPE hwindow (HPROJECT hpr, struct window *, long (*)(DB_ADDR *, ...), short);
friend int FUNCTYPE qtcont (HPROJECT hpr, struct container *, short);
friend int FUNCTYPE htcont (HPROJECT hpr, struct container *, short);

friend int FUNCTYPE z_touch (HPROJECT);
friend int FUNCTYPE z_restore (HPROJECT);

friend int FUNCTYPE z_fillnew (DB_ADDR *, void *);
friend int FUNCTYPE z_dispose (DB_ADDR *);
friend int FUNCTYPE z_readrec (DB_ADDR *, void *);
friend int FUNCTYPE z_writerec (DB_ADDR *, void *);

friend int FUNCTYPE DBPageZeroReRead (HPROJECT hPr);
friend int FUNCTYPE DBPageZeroFlush(HPROJECT hPr, int);
friend int FUNCTYPE DBPageZeroAlloc(HPROJECT hPr, short fno, long *loc);
friend int FUNCTYPE DBPageZeroFree(HPROJECT hPr, short fno, long loc);
friend int FUNCTYPE EXPORT01 DBFlush(HPROJECT hPr, int iFlush);

friend int db_error (int, int, ...);
friend int FUNCTYPE ExtErrInstall (long, int (*)(int,int,...), int (**)(int,int,...), void *);

friend int FUNCTYPE ReIndexFile (HPROJECT hpr, short, short, short, short (*)(void *));
friend int FUNCTYPE gen_backup (FILE_ENTRY *, PGZERO *, char *, time_t);

friend HPROJECT FUNCTYPE z_open_storage (LPSTORAGE pIStorage, BOOL fRO, BOOL fTemp);
friend HPROJECT FUNCTYPE z_open_storage_ex (LPSTORAGE pIStorage, BOOL fRO, BOOL fTemp, const CLSID *pClsID, BOOL fHandleErrors);
friend HPROJECT FUNCTYPE z_open_storage_pbd (LPSTORAGE pIStorage, BOOL fRO);
#if defined(WIN32)
friend HPROJECT FUNCTYPE CreateTempStorageProject (DBASE *pDB);
friend HRESULT FUNCTYPE RenameStorageProject (HPROJECT hPr, LPCTSTR pszFile);
friend HRESULT FUNCTYPE CopyToStorageProject (HPROJECT hPr, LPCTSTR pszFile, IStorage **ppIStgDest, const CLSID *pClsID, LPCSTR pCF);
#endif
friend HRESULT FUNCTYPE GetProjectStorage (HPROJECT hPr, LPSTORAGE *ppIStorage);
friend HPROJECT FUNCTYPE OpenStorageProject (LPSTORAGE, DBASE *, LPCSTR, LPCSTR, LPCSTR, BOOL, BOOL, DWORD);
friend HPROJECT FUNCTYPE OpenStorageProjectEx (LPSTORAGE, DBASE *, LPCSTR, LPCSTR, LPCSTR, BOOL, BOOL, DWORD, const CLSID *, BOOL);
friend HPROJECT FUNCTYPE OpenStoragePbd (LPSTORAGE pIStg, DBASE *pDB, LPCSTR pcName, BOOL fRO);

// obsolete functions
friend void FUNCTYPE dbinit_ (void);
friend long FUNCTYPE dbcodb_ (HPROJECT hPr, long *);
// friend long FUNCTYPE zact_ (long *);
friend long FUNCTYPE ngmini_ (HPROJECT hPr, REC_NO *, long *, long *);
friend long FUNCTYPE ngmc_ (REC_NO *, long *);
friend long FUNCTYPE ladr_ (HPROJECT hPr, short *lon, BOOL fLast);
friend long FUNCTYPE lrec_ (short *lon);
// friend long FUNCTYPE zopen_ (LPSTR, int, LPSTR, int, LPSTR, int);

#if defined(_USE_TRIASDB)
///////////////////////////////////////////////////////////////////////////////
// TRiASDB
friend class CHeaderEntry;
friend class CDBHeader;
friend class CPrjHeader;

friend class CNativeObject;
friend class CNativeView;
friend class CNativeIdent;
friend class CNativeMerkmal;
friend class CNativePbd;
friend class CNativePbdIdent;
friend class CNativePbdMerkmal;
friend class CNativePbdRelation;

friend class CKeyContext;

friend long GetTextFromDBT (HPROJECT hPr, long lAdr, char *pMText, long lLen, BOOL fText); 

friend long FUNCTYPE puthd_ (HPROJECT hpr, char *, int, long *, long *, long);
friend int FUNCTYPE gethdlen (HPROJECT hpr, long *, short *);
friend long FUNCTYPE gethd_ (HPROJECT hpr, char *, int, long *, long *, long*);
friend long FUNCTYPE delhd_ (HPROJECT hpr, long *);

#else
friend long FUNCTYPE puthd_ (HPROJECT hpr, char *, int, long *, long *, long);
friend int FUNCTYPE gethdlen (HPROJECT hpr, long *, short *);
friend long FUNCTYPE gethd_ (HPROJECT hpr, char *, int, long *, long *, long*);
friend long FUNCTYPE delhd_ (HPROJECT hpr, long *);
#endif // _USE_TRIASDB

///////////////////////////////////////////////////////////////////////////////
// Zugehöriger MutexVerwalter
	friend class CSyncDbAccess;
};

extern CDbAccess *g_pDbMutex;	// globale ZugriffsKontrolle

//#define SYNC_DBACCESS(pMtx)	CDbAccess::CSyncThread __Sync((CSyncMonitor *)pMtx)

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
#define THIS_FILE	SYNC_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

class CSyncDbAccess : 
	public CDbAccess::CSyncThread 
{
private:
	DBASE *m_pOldDB;

// declare only, not to be used
	CSyncDbAccess();		//lint !e1704

public:
	CSyncDbAccess (CSyncMonitor *pMtx, HPROJECT hPr) 
		: CSyncThread (pMtx), m_pOldDB(NULL) 
	{
		AquireDbAccess(hPr);
	}
	~CSyncDbAccess () 
	{
		ReleaseDbAccess();
	}
	
// worker functions
	void AquireDbAccess (HPROJECT hPr, bool fPropagate = false)
	{
		if (fPropagate)
			CSyncThread::AquireLock();

		_ASSERTE(NULL != hPr);
		m_pOldDB = act_db;
		act_db = &db_table[(INT_PTR)hPr -1];	//lint !e676
	}
	void ReleaseDbAccess(bool fPropagate = false)
	{
		if (fPropagate)
			ReleaseLock();
		act_db = m_pOldDB;
		m_pOldDB = NULL;
	}
	
	friend class CDbAccess;
};

///////////////////////////////////////////////////////////////////////////////
// zeitweiliges freigeben des Locks
class CUnlockDbAccess
{
public:
	CUnlockDbAccess(CSyncDbAccess *pSync, HPROJECT hPr) :
		m_pSync(pSync), m_hPr(hPr)
	{
		m_pSync -> ReleaseDbAccess(true);
	}
	~CUnlockDbAccess()
	{
		m_pSync -> AquireDbAccess(m_hPr, true);
	}

private:
	CSyncDbAccess *m_pSync;
	HPROJECT m_hPr;
};

#define SYNC_DBACCESS(pMtx,hPr)	CSyncDbAccess __Sync(static_cast<CSyncMonitor *>(pMtx), hPr)
#define SYNC_DBACCESS_EX(pMtx)	CDbAccess::CSyncThread __Sync(static_cast<CSyncMonitor *>(pMtx))

#define UNLOCK_DBACCESS(pSync, hPr)	CUnlockDbAccess __Unlock(pSync, hPr)

#endif // _SYNCDB_HXX
