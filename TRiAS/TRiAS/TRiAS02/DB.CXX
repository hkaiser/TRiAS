// Methoden fuer die Datenbankarbeit ------------------------------------------
// File: DB.CXX

#include "trias02p.hxx"
#include "trias02.h"

#if !defined(WIN32)
#include <storage.h>
#include <ole16.h>
#endif // !WIN32

#include <hdrentry.hxx>
#include <pbd.hxx>
#include <ErrInst.hxx>
#include <Com/PropertyHelper.h>

#include "Strings.h"
#include "pbdids.hxx"	// CPBDIdents

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// globale Variablen
extern char g_pDLLName[];

///////////////////////////////////////////////////////////////////////////////
// locale Variablen
DBTemplate *actDB = NULL;	// derzeit aktivierte DB

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASDatabase);
DefineSmartInterface(TRiASAccessDatabase);
DefineSmartInterface(TRiASProperty);
DefineSmartInterface(TRiASPropertyBase);
DefineSmartInterface(TRiASProperties);
DefineSmartInterface(TRiASObjectsCollection);
DefineSmartInterface(TRiASViews);
DefineSmartInterface(Dispatch);
DefineSmartInterface(TRiASPropertyCallback);

///////////////////////////////////////////////////////////////////////////////
// Konstruktoren
DBTemplate::DBTemplate (void) 
{
	_DBDesc = (HPROJECT)0;
	_DBName = NULL;
	_UserName = NULL;
	_ReadOnlyFlag = true;

	m_fTemp = false;
	m_fIsDirty = false;
	m_fIsCopy = false;
}

DBTemplate::DBTemplate (const char *DBName) 
{
	_DBDesc = (HPROJECT)0;
	_DBName = new char [strlen (DBName) +1];
	if (_DBName == NULL) {
		db_error (EC_NOMEMORY, RC_CDatenBasis);
		return;
	}
	strcpy (_DBName, DBName);
	_UserName = NULL;
	_ReadOnlyFlag = true;

	m_fTemp = false;
	m_fIsDirty = false;
	m_fIsCopy = false;
}

DBTemplate::DBTemplate (const DBTemplate &DB) 
{
	_DBDesc = DB._DBDesc;
	_DBName = new char [strlen (DB._DBName) +1];
	if (_DBName == NULL) {
		db_error (EC_NOMEMORY, RC_CDatenBasis);
		return;
	}
	strcpy (_DBName, DB._DBName);
	if (DB._UserName != NULL) {
		_UserName = new char [strlen (DB._UserName) +1];
		if (_UserName == NULL) {
			db_error (EC_NOMEMORY, RC_CDatenBasis);
			return;
		}
		strcpy (_UserName, DB._UserName);
	} else
		_UserName = NULL;
	_ReadOnlyFlag = DB._ReadOnlyFlag;

	m_fTemp = DB.m_fTemp;
	m_fIsDirty = DB.m_fIsDirty;
	m_fIsCopy = DB.m_fIsCopy;
}

// Destruktor
DBTemplate::~DBTemplate (void) 
{
	if (actDB == this)
		actDB = NULL;
	DELETE_OBJ (_UserName);
	DELETE_OBJ (_DBName);
}

// Memberfunktionen
void DBTemplate::operator =(const DBTemplate &DB) 
{
// alte DB freigeben
	DELETE_OBJ (_DBName);
	DELETE_OBJ (_UserName);
// DB kopieren
// DB-Deskriptor
	_DBDesc = DB._DBDesc;
// DB-Namen
	_DBName = new char [strlen (DB._DBName) +1];
	if (_DBName == NULL) {
		db_error (EC_NOMEMORY, RC_CDatenBasis);
		return;
	}
	strcpy (_DBName, DB._DBName);
// Nutzernamen
	if (DB._UserName != NULL) {
		_UserName = new char [strlen (DB._UserName) +1];
		if (_UserName == NULL) {
			db_error (EC_NOMEMORY, RC_opDatenBasis);
			return;
		}
		strcpy (_UserName, DB._UserName);
	} else
		_UserName = NULL;
// ReadOnlyFlag
	_ReadOnlyFlag = DB._ReadOnlyFlag;

	m_fTemp = DB.m_fTemp;
	m_fIsDirty = DB.m_fIsDirty;
	m_fIsCopy = DB.m_fIsCopy;
}

void DBTemplate::SetDBName (char *DBName) 
{
	DELETE_OBJ (_DBName);
	_DBName = new char [strlen (DBName) +1];
	if (_DBName == NULL) {
		db_error (EC_NOMEMORY, RC_SetDBName);
		return;
	}
	strcpy (_DBName, DBName);
}

BOOL DBTemplate::GetTempDBName (char *pDBName) 
{
	if (!isOpened()) return false;	// DB nicht eröffnet

	USES_CONVERSION;

#if defined(_USE_LEGACY_CODE)
	TX_ASSERT(!IsTRiASDBBased());

// wenn temporär und Com-Datei
	if (m_fTemp) {
	IStorage *pIStorage = NULL;
		
		if (SUCCEEDED(::GetProjectStorage (_DBDesc, &pIStorage))) {
		STATSTG st;

			pIStorage -> Stat (&st, STATFLAG_DEFAULT);
			strcpy (pDBName, OLE2A(st.pwcsName));

		// aufräumen
			CoTaskMemFree (st.pwcsName);
			pIStorage -> Release();
			return true;
		}
	} 
#endif // _USE_LEGACY_CODE

// alle anderen Fälle liefern den richtigen Namen	
	strcpy (pDBName, _DBName);
	return true;
}

BOOL GeoDB::GetTempDBName (char *pDBName) 
{
	if (!isOpened()) return false;	// DB nicht eröffnet

	USES_CONVERSION;

#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	// wenn temporär und Com-Datei
		return DBTemplate::GetTempDBName (pDBName);
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		if (m_fTemp) {
			COM_TRY {
			WTRiASDatabase DBase;
			CComBSTR bstrName;

				THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));
				THROW_FAILED_HRESULT(DBase -> get_TemporaryName (CLEARED(&bstrName)));
				strcpy (pDBName, OLE2A(bstrName));

			} COM_CATCH_RETURN(false);
		}
	}

// alle anderen Fälle liefern den richtigen Namen	
	strcpy (pDBName, _DBName);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Datenbasisarbeit 

#if defined(_USE_LEGACY_CODE)
// DB Eröffnen
ErrCode DBTemplate::Open (char *UserName, char *PassWord, DWORD dwMode) 
{
	TX_ASSERT(!IsTRiASDBBased());		// ist eine alte Funktion

	if (isOpened()) return (EC_OKAY);	// DB bereits eröffnet
	if (_DBName == NULL)			// DBName nicht gegeben
		return ((ErrCode)db_error (EC_NODBNAME, RC_OPEN));

	_DBDesc = (HPROJECT)z_open (_DBName, UserName, PassWord, _ReadOnlyFlag, dwMode);
	if (!isOpened()) {
	ErrCode EC = ERRCODE_FROM_HRESULT(::GetLastError());
	
		if (EC == EC_OPENRO) {		// ReadOnly öffnen
			_ReadOnlyFlag = true;
			_DBDesc = (HPROJECT)z_open (_DBName, UserName, PassWord, true, dwMode);
		}
		if (!isOpened()) {
			_DBDesc = (HPROJECT)-2;		// erfolgloser Versuch
			return EC_NOOPEN;
		}
	}

BOOL fFlag;

	::GetCopyMode (_DBDesc, &fFlag); 
	m_fIsCopy = fFlag ? true : false;
	
	::GetROMode (_DBDesc, &fFlag);
	_ReadOnlyFlag = fFlag ? true : false;

	actDB = this;				// aktivierte DB setzen
	if (_ReadOnlyFlag) 
		SetAccess (Z_ALL | Z_RDONLY); 	// DB ReadOnly

	DELETE_OBJ (_UserName);
	if (UserName) {
		_UserName = new char [strlen (UserName) +1];
		if (_UserName == NULL)
			return ((ErrCode)db_error (EC_NOMEMORY, RC_OPEN));
		strcpy (_UserName, UserName);
	}

	SetDirty (false);
	return (EC_OKAY);
}

ErrCode DBTemplate::Open (LPSTORAGE pIStorage) 
{
	TX_ASSERT(!IsTRiASDBBased());		// ist eine alte Funktion

	if (isOpened()) return (EC_OKAY);	// DB bereits eröffnet

	_DBDesc = (HPROJECT)z_open_storage (pIStorage, _ReadOnlyFlag, m_fTemp);
	if (!isOpened()) {
	ErrCode EC = ERRCODE_FROM_HRESULT(::GetLastError());
	
		if (EC == EC_OPENRO) {		// ReadOnly öffnen
			_ReadOnlyFlag = true;
			_DBDesc = (HPROJECT)z_open_storage (pIStorage, true, false);
		}
		if (!isOpened()) {
			_DBDesc = (HPROJECT)-2;		// erfolgloser Versuch
			return EC_NOOPEN;
		}
	}

BOOL fFlag;

	::GetCopyMode (_DBDesc, &fFlag); 
	m_fIsCopy = fFlag ? true : false;
	
	::GetROMode (_DBDesc, &fFlag);
	_ReadOnlyFlag = fFlag ? true : false;

	actDB = this;				// aktivierte DB setzen
	if (_ReadOnlyFlag) 
		SetAccess (Z_ALL | Z_RDONLY); 	// DB ReadOnly

	DELETE_OBJ (_UserName);

	SetDirty (false);

return (EC_OKAY);
}
#endif // defined(_USE_LEGACY_CODE)

// DB Schließen ---------------------------------------------------------------
ErrCode DBTemplate::Close (BOOL fCommit) 
{
	TX_ASSERT(!IsTRiASDBBased());		// ist eine alte Funktion

	if (!isOpened()) {
		if ((short)_DBDesc == -2) _DBDesc = (HPROJECT)-1;
		return (EC_OKAY);	// DB bereits abgeschlossen
	}

#if defined(_USE_LEGACY_CODE)
ErrInstall EI ((ErrCode)S_ACTIV);	// ~CActDB greift ins leere
ErrInstall EI1 (EC_SYSERROR);
ErrCode RC;

	{
	CActDB ActDB (*this);
	
		DBASSERT (z_close (_DBDesc, fCommit));
	}
#endif // defined(_USE_LEGACY_CODE)

	_DBDesc = (HPROJECT)0;		// DB geschlossen
	DELETE_OBJ (_DBName);
	DELETE_OBJ (_UserName);
	return EC_OKAY;
}

#if defined(_USE_LEGACY_CODE)
// Zugriffsmode für DB setzen -------------------------------------------------
ErrCode DBTemplate::SetAccess (long Mode) 
{
	TX_ASSERT(!IsTRiASDBBased());		// ist eine alte Funktion

CActDB ActDB (*this);

	return (ErrCode)z_access (DBDesc(), Mode);
}

ErrCode DBTemplate::RestoreAccess (long Mode) 
{
	TX_ASSERT(!IsTRiASDBBased());		// ist eine alte Funktion

CActDB ActDB (*this);

	return (ErrCode)z_raccess (DBDesc(), Mode);
}

// Nummer des letzten existierenden Satzes einer DB-Datei bestimmen -----------
long DBTemplate::LastRec (short Datei) 
{ 
	TX_ASSERT(!IsTRiASDBBased());		// ist eine alte Funktion

CActDB ActDB (*this);

	return (ladr_(DBDesc(), &Datei, true) +1); 
}
#endif // _USE_LEGACY_CODE

// neue DB aktivieren ---------------------------------------------------------
DBTemplate * DBTemplate::Activate (HPROJECT *phPr) 
{
DBTemplate *oldDB = actDB;		// alte DB merken

	if (!isOpened()) {
		TX_ASSERT(!isOpened());		// snh !!
		if (NULL != phPr)
			*phPr = NULL;
		return actDB;	// nicht mehr eröffnet
	}

#if defined(_USE_LEGACY_CODE)
	if (IsValidTRiASProjectHandle(DBDesc())) {
	HPROJECT oldnum = z_activate (DBDesc());

		if (NULL != phPr)
			*phPr = oldnum;

		if (actDB != NULL && oldnum != actDB -> DBDesc()) {
		// DAS sollte nicht passieren !
			z_activate (oldnum);		// zurückschalten
			db_error (EC_SYSERROR, RC_Activate);
			return NULL;
		}
	} else
#endif // _USE_LEGACY_CODE
	{
		if (NULL != phPr)
			*phPr = DBDesc();
	}
	actDB = this;					// neue DB einstellen
	return oldDB;
}

///////////////////////////////////////////////////////////////////////////////
// #HK980111: Datenbank verwaltet DirtyFlag jetzt selbst
// als Dirty markieren 
void EXPORT02 DBTemplate::SetDirty (BOOL fDirty)
{ 
	m_fIsDirty = fDirty ? true : false; 

	TX_ASSERT(!IsTRiASDBBased());
	::SetDirty (DBDesc(), m_fIsDirty);
}

// DirtyFlag abfragen
BOOL EXPORT02 DBTemplate::isDirty (void)
{
	TX_ASSERT(!IsTRiASDBBased());

CActDB ActDB (*this);
BOOL fIsDirty = m_fIsDirty ? TRUE : FALSE;

	::IsDirty (DBDesc(), &fIsDirty);
	m_fIsDirty = fIsDirty ? true : false;
	
	return fIsDirty;
} 

BOOL EXPORT02 GeoDB::isDirty()
{
#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		return DBTemplate::isDirty();
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

		COM_TRY {
		WTRiASDatabase DBase;
		VARIANT_BOOL fIsDirty = m_fIsDirty ? VARIANT_TRUE : VARIANT_FALSE;

			THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));
			THROW_FAILED_HRESULT(DBase -> get_IsDirty (&fIsDirty));
			m_fIsDirty = fIsDirty ? true : false;
			
			return fIsDirty;

		} COM_CATCH_RETURN(m_fIsDirty);
	}
}

BOOL EXPORT02 DBTemplate::IsComDB (void)
{
IStorage *pIStg = NULL;

	if (S_OK == GetProjectStorage (&pIStg)) {
		pIStg -> Release();
		return TRUE;
	}
	return FALSE;
}

BOOL EXPORT02 GeoDB::IsTRiASDataSource (void)
{
	TX_ASSERT(IsTRiASDBBased());
	COM_TRY {
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));
		return GetPropertyFrom (DBase, g_cbTRiASDataSource, VARIANT_FALSE) ? TRUE : FALSE;

	} COM_CATCH_RETURN(FALSE);
}

BOOL EXPORT02 GeoDB::IsGDODataSource (void)
{
	TX_ASSERT(IsTRiASDBBased());
	COM_TRY {
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));
		return GetPropertyFrom (DBase, g_cbGDODataSource, VARIANT_FALSE) ? TRUE : FALSE;

	} COM_CATCH_RETURN(FALSE);
}

void EXPORT02 GeoDB::SetDirty (BOOL fDirty)
{
CActDB ActDB (*this);
BOOL fNewDirty = fDirty ? true : false;

	if (isDirty() ^ fNewDirty) {
#if defined(_USE_LEGACY_CODE)
		if (!IsTRiASDBBased()) {
			DBTemplate::SetDirty (fDirty);
		} else
#endif // _USE_LEGACY_CODE
		{
			TX_ASSERT(IsTRiASDBBased());
			COM_TRY {
			WTRiASDatabase DBase;

				THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));
				THROW_FAILED_HRESULT(DBase -> put_IsDirty (fDirty ? VARIANT_TRUE : VARIANT_FALSE));

			} COM_CATCH_IGNORE;
		}
		DEXN_GeoDBisDirty (fDirty);
	}
}

#if defined(_USE_LEGACY_CODE)
void EXPORT02 PBD_DB::SetDirty (BOOL fDirty)
{
CActDB ActDB (*this);

	DBTemplate::SetDirty (fDirty);
	if (fDirty)		// zugehörige GeoDB ist in jedem Fall Dirty
		DEX_SetDirtyGeoDB (true);
}

DBTemplate *PBD_DB::ActivateCOMPbd (void) 
{
DBTemplate *oldDB = NULL;
IStorage *pIStorage = NULL;
GeoDB *pDB = GetGeoDB();

	if (NULL == pDB) return NULL;

	if (FAILED(pDB -> GetProjectStorage (&pIStorage)))
		return NULL;
	oldDB = actDB;			// alte DB merken

IStorage *pIPbdStorage = NULL;
DWORD dwMode = STGM_TRANSACTED;
ErrCode EC = WC_RETURN;
int iCnt = 0;

	if (GetROMode()) 
		dwMode |= (STGM_READ | STGM_SHARE_EXCLUSIVE);
	else
		dwMode |= (STGM_READWRITE | STGM_SHARE_EXCLUSIVE);

	while (++iCnt < 3 && EC != EC_OKAY) {
	HRESULT hr = pIStorage -> OpenStorage (
			WideString (GetDBName()), NULL, dwMode, NULL, 0L, &pIPbdStorage);

		if (FAILED(hr)) {
			if (db_error (EC_INVPBDNAME, RC_Activate, pDB -> DBDesc()) == EC_OKAY) {
				EC = WC_RETURN;
				continue;		// nochmal versuchen
			}
			_DBDesc = (HPROJECT)-2;
			pIStorage -> Release();
			actDB = oldDB;		// wiederherstellen
			return NULL;
		}		
		
		if ((EC = Open (pIPbdStorage)) != EC_OKAY) {
			pIPbdStorage -> Release();

			if (EC == EC_INVDBNAME || EC == EC_NOOPEN) {
			// DB nicht gefunden: Fehlerbehandlung hat
			// die Möglichkeit neuen DBNamen vorzugeben
				if (db_error (EC_INVPBDNAME, RC_Activate, pDB -> DBDesc()) == EC_OKAY) {
					EC = WC_RETURN;
					continue;	// nochmal versuchen
				}
			}
			actDB = oldDB;		// wiederherstellen
			pIStorage -> Release();
			return NULL;
		} 

	// Open aktiviert neu eröffnete DatenBasis
		pIPbdStorage -> Release();
		pIStorage -> Release();
		actDB = this;		// neue DB einstellen
		return oldDB;
	}

	if (NULL != pIPbdStorage) 
		pIPbdStorage -> Release();
	pIStorage -> Release();

return oldDB;
}

DBTemplate *PBD_DB::Activate (HPROJECT *phPr) 
{
DBTemplate *oldDB = NULL;

	if (NULL != phPr)
		*phPr = (NULL != actDB) ? actDB -> DBDesc() : NULL;

// überprüfen, ob DB bereits geöffnet ist
	if (!isOpened()) {
		if ((short)DBDesc() == -2) return NULL;   // bereits erfolglos versucht

	// DB noch nicht eröffnet --> ReadOnly mit Standard-User öffnen
		if (GetDBName() == NULL) return NULL;

	ErrInstall EI (EC_INVDBNAME);	// ungültige DB abfangen

		if (GetCOMFlag()) return ActivateCOMPbd();

		SetROMode (true);			// $ro eröffnen

	// alte PBD, als externe DB eröffnen
	char *pFile = new char[_MAX_FNAME];
	ErrCode EC = WC_RETURN;
	short iCnt = 0;
		
		oldDB = actDB;			// alte DB merken

		while (++iCnt < 3 && EC != EC_OKAY) {
			_splitpath (GetDBName(), NULL, NULL, pFile, NULL);
			_strlwr (pFile);

			if ((EC = DBTemplate::Open (pFile, "", 0L)) != EC_OKAY) {
				if (EC == EC_INVDBNAME || EC == EC_NOOPEN) {
				// DB nicht gefunden: Fehlerbehandlung hat
				// die Möglichkeit neuen DBNamen vorzugeben
				GeoDB *pDB = GetGeoDB();
				HPROJECT hPr = pDB ? pDB -> DBDesc() : NULL;

					if (db_error (EC_INVPBDNAME, RC_Activate, hPr) == EC_OKAY) {
						EC = WC_RETURN;
						continue;	// nochmal versuchen
					}
				}
				
				DELETE_VEC (pFile);
				actDB = oldDB;		// wiederherstellen
				return NULL;
			} else {
			// Open aktiviert neu eröffnete DatenBasis
				actDB = this;		// neue DB einstellen
				DELETE_VEC (pFile);
				return oldDB;
			}
		}
		DELETE_VEC (pFile);
		actDB = oldDB;		// wiederherstellen
		return NULL;		// Fehler
	} else 		// PBD bereits geöffnet
		return DBTemplate::Activate(phPr);
/*
	// nur umschalten
	int oldnum = z_activate (DBDesc());

		if (actDB != NULL && oldnum != actDB -> DBDesc()) {
		// DAS sollte nicht passieren !
			z_activate (oldnum);		// zurückschalten
			db_error (EC_SYSERROR, RC_Activate);
			return NULL;
		}
		oldDB = actDB;		// alte DB merken
	}
	actDB = this;			// neue DB einstellen

return oldDB;
*/
}

// alle Pages, die zu dieser DB gehören, wegschreiben -------------------------
ErrCode DBTemplate::Flush (BOOL fCommit) 
{
CActDB ActDB (*this);		// evtl. wird Pbd hier eröffnet

// wenn DB nicht eröffnet ist
	if (!isOpened()) 			// Keine DB eröffnet
		return (ErrCode)db_error ((int)EC_NOOPEN, (int)RC_FlushDB);
	if (!isDirty()) return EC_OKAY;

// DB aktivieren
ErrCode RC;

	DBASSERT(DBFlush(DBDesc(), FLUSH_ACTDB));	// alles wegschreiben
	DBASSERT(DBPageZeroFlush(DBDesc(), FLUSH_ACTDB));	// PageZero's auch wegschreiben

IStorage *pIStorage = NULL;

	if (fCommit && SUCCEEDED(GetProjectStorage (&pIStorage))) 
	{
		pIStorage -> Commit (STGC_DEFAULT);
		pIStorage -> Release();
	}
	SetDirty (false);
	return EC_OKAY;
}

// Zustand aus BackupDatei wieder herstellen ----------------------------------
ErrCode DBTemplate::Restore (void)
{
// wenn DB nicht eröffnet ist
	if (!isOpened()) 			// Keine DB eröffnet
		return (ErrCode)db_error ((int)EC_NOOPEN, (int)RC_RestoreDB);

// DB aktivieren
ErrCode RC;
CActDB ActDB (*this);

	DBASSERT(DBFlush(DBDesc(), FLUSH_NODATA));		// alles verwerfen
	DBASSERT(DBPageZeroFlush(DBDesc(), FLUSH_NODATA));	// PageZero's auch verwerfen

IStorage *pIStorage = NULL;

	if (SUCCEEDED(GetProjectStorage (&pIStorage))) 
	{
	HRESULT hr = pIStorage -> Revert();

		if (SUCCEEDED(hr)) {
			Close (false);		// schließen, kein commit
			Open (pIStorage);	// reopen
		}
		pIStorage -> Release();
	}
	SetDirty (false);

return EC_OKAY;
}
#endif // _USE_LEGACY_CODE

///////////////////////////////////////////////////////////////////////////////
// Version dieser DB liefern 
long DBTemplate::GetDBVersion (void) 
{
	TX_ASSERT(!IsTRiASDBBased());

CActDB ActDB (*this);

	return ::GetDBVersion(DBDesc());
}

long GeoDB::GetDBVersion (void)
{
#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		return DBTemplate::GetDBVersion();
	} else
#endif // _USE_LEGACY_CODE
	{
	long lVersion = -1L;

		COM_TRY {
		WTRiASDatabase DBase;

			THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));
			THROW_FAILED_HRESULT(DBase -> get_VersionLong (&lVersion));

		} COM_CATCH_RETURN(-1L);
		return lVersion;
	}
}

// Pfad zu DB liefern ---------------------------------------------------------
char *DBTemplate::GetDBPath (char *Buff, short BuffLen) 
{
char Drive[_MAX_DRIVE];
char Dir[_MAX_DIR];
char Result[_MAX_PATH];

	_splitpath (_DBName, Drive, Dir, NULL, NULL);
	_makepath (Result, Drive, Dir, "", "");
	strncpy (Buff, Result, BuffLen);	
	Buff[BuffLen-1] = '\0';
	return Buff;
}

///////////////////////////////////////////////////////////////////////////////
// Memberfunktionen GeoDB 
#if defined(_USE_LEGACY_CODE)
ObjContainer GeoDB::DBCont (BOOL fReRead) 
{
	TX_ASSERT(!IsTRiASDBBased());

// DB Container bestimmen
	if (!isOpened()) {			// Keine DB eröffnet
		db_error ((int)EC_NOOPEN, (int)RC_DBCont);
		return ObjContainer (0, 0, 0, 0);
	}

	if (fReRead) {
		DELETE_OBJ (_pDBCont);
	}
	if (_pDBCont != NULL)	// Container bereits bestimmt
		return *_pDBCont;

long Cont[4];
register ErrCode EC;

// DB aktivieren
CActDB ActDB (*this);

	if ((EC = (ErrCode)dbcodb_ (DBDesc(), Cont)) != EC_OKAY)  
	// Fehler beim Cont bestimmen
		return ObjContainer (0, 0, 0, 0);

// DBContainer setzen
	_pDBCont = new ObjContainer (Cont[0], Cont[1], Cont[2], Cont[3]);
	if (_pDBCont == NULL) {
		db_error ((int)EC_NOMEMORY, (int)RC_DBCont);
		return ObjContainer (0, 0, 0, 0);
	}
	return *_pDBCont;
}
#endif // _USE_LEGACY_CODE

HRESULT GeoDB::DBCont (_DGMRectangleGeometry **ppIRect, BOOL fReRead) 
{
	TX_ASSERT(IsTRiASDBBased());

// DB Container bestimmen
HRESULT hr = E_FAIL;

	if (!isOpened()) {			// Keine DB eröffnet
		db_error ((int)EC_NOOPEN, (int)RC_DBCont);
		return HRESULT_FROM_ERRCODE(EC_NOOPEN);
	}

	if (fReRead)		// neu einlesen
		m_DBCont.Assign(NULL);

	if (!m_DBCont) {		// Container muß bestimmt werden
		COM_TRY {
		WTRiASDatabase DBase;
		WDispatch disp;

			THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));
			if (fReRead) 
				DBase -> ReLoad (RELOADDATABASE_Envelope);

			if (SUCCEEDED(WTRiASAccessDatabase(DBase) -> get_Envelope (ENVELOPETYPE_AllGeometries, disp.ppi()))) {
			// Werte besorgen
				m_DBCont = disp;
				hr = S_OK;
			}
			else {
			WTRiASProperties Props;

				THROW_FAILED_HRESULT(GetProperties (DBase, Props.ppi()));
			
			// GetProperty liefert mit AddRef ab !
			WCoordTransform CTF (GetProperty (Props, g_cbCTFService, (IDispatch *)NULL), false);

				if (SUCCEEDED(CTF -> get_Envelope (disp.ppi()))) {
					m_DBCont = disp;
					hr = S_FALSE;
				}
			}

		} COM_CATCH;
	} else
		hr = S_OK;

	*ppIRect = m_DBCont;
	if (*ppIRect) {
		(*ppIRect) -> AddRef();
		return hr;
	}
	return E_FAIL;
}

HRESULT GeoDB::DBMaxCont (_DGMRectangleGeometry **ppIRect) 
{
	TX_ASSERT(IsTRiASDBBased());

// DB Container bestimmen
	if (!isOpened()) {			// Keine DB eröffnet
		db_error ((int)EC_NOOPEN, (int)RC_DBCont);
		return HRESULT_FROM_ERRCODE(EC_NOOPEN);
	}

	COM_TRY {
	WTRiASDatabase DBase;
	WDispatch disp;

		THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));
		THROW_FAILED_HRESULT(WTRiASAccessDatabase(DBase) -> get_Envelope (ENVELOPETYPE_MaxPossible, disp.ppi()));
		THROW_FAILED_HRESULT(disp -> QueryInterface (IID__DGMRectangleGeometry, (LPVOID *)ppIRect));

	} COM_CATCH;
	return S_OK;
}

#if defined(_USE_LEGACY_CODE)
ErrCode GeoDB::Open (char *pUser, char *pPasswd, DWORD dwMode)
{
ErrCode RC;

	DBASSERT (DBTemplate::Open (pUser, pPasswd, dwMode));

// eigenschaften dieser DB einlesen
	ReReadHeader();
	m_fCanTexts = GetDBVersion() >= NEWDBVERSION ? true : false;

	return EC_OKAY;
}
#endif // defined(_USE_LEGACY_CODE)

BOOL EXPORT02 GeoDB::ReReadHeader (void)
{
ResourceFile RF (g_pDLLName);

#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	// dazu ResourceFile generieren
	HeaderEntry HE (*this, ResID (IDS_TEXTOBJMCODE, &RF));

		_lTextObjMCode = HE.EntryLong (0L);	// MerkmalsCode für TextObjekte holen

	// Verschnitt der DB feststellen
		{
		HeaderEntry Inz (*this, IDS_INZIDENZ);

			if (Inz.Status() != HE_INVALID)
				m_fInz = !strcmp (Inz.EntryText(), ResString (IDS_YES, 3));
		}

	// Zahlenbasis der Idents holen
	BOOL fStorage = IsComDB();

		{
		HeaderEntry IdBase (*this, IDS_IDENTBASE);
		int sBase = (int)IdBase.EntryLong (fStorage ? 16 : 10);

			if (sBase != 10 && sBase != 16) 
				sBase = 16;
			m_iIdentBase = sBase;
		}

	// Zahlenbasis der MCodes holen (default: 10)
		{
		HeaderEntry MkBase (*this, IDS_MCODEBASE);
		int sBase = (int)MkBase.EntryLong (10);

			if (sBase != 10 && sBase != 16) 
				sBase = 10;
			m_iMkBase = sBase;
		}

	// Positionierung von Textobjekten (default: untere Kante)
		{
		HeaderEntry PosTxt (*this, ResID(IDS_POSTEXTATBASELINE, &RF));
		
			m_fPosTextAtBaseLine = PosTxt.EntryLong(0) ? true : false;
		}

	// 16Bit Kompatibilität gewährleisten ? (OKS <--> Ident)
		{
		HeaderEntry Comp16 (*this, ResID(IDS_COMPATIBILITY_16BIT, &RF));
		
			m_fIsCompatible16 = Comp16.EntryLong(0) ? true : false;
		}
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	// alle notwendigen Properties der Database abfragen
	WTRiASDatabase DBase;
	WTRiASProperties Props;

		THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));
		if (SUCCEEDED(WTRiASPropertyBase(DBase) -> get_Properties (Props.ppi()))) {
			THROW_FAILED_HRESULT(Props -> Refresh());

		// nicht alle Datenquellen unterstützen das
		WTRiASPropertyCallback CB;
		
			if (SUCCEEDED(DBase -> QueryInterface (CB.ppi())))
			{
				THROW_FAILED_HRESULT(CB -> Refresh(CComBSTR(g_cbNil)));
			}

		// PosTextOnBaseLine
			m_fPosTextAtBaseLine = GetPropertyResID (Props, ResID (IDS_POSTEXTATBASELINE, &RF), VARIANT_FALSE) ? true : false;
			m_fIsCompatible16 = GetPropertyResID (Props, ResID (IDS_COMPATIBILITY_16BIT, &RF), VARIANT_FALSE) ? true : false;
			m_fInz = GetPropertyResID (Props, IDS_INZIDENZ, VARIANT_FALSE) ? true : false;
			m_iIdentBase = GetPropertyResID (Props, IDS_IDENTBASE, 16, LOCALE_ENGLISH);
			if (10 != m_iIdentBase && 16 != m_iIdentBase)
				m_iIdentBase = 16;
#if defined(_USE_LEGACY_CODE)
			m_iMkBase = GetPropertyResID (Props, IDS_MCODEBASE, 10, LOCALE_ENGLISH);
			if (10 != m_iMkBase && 16 != m_iMkBase)
				m_iMkBase = 10;
#endif // defined(_USE_LEGACY_CODE)
			_lTextObjMCode = GetPropertyResID (Props, ResID (IDS_TEXTOBJMCODE, &RF), 0L, LOCALE_ENGLISH);
		}

		if (0 != _lTextObjMCode && IsTRiASDataSource()) 
			_lTextObjMCode = MapMCodeToHandle (_lTextObjMCode);
	}
	return TRUE;
}

#if defined(_USE_LEGACY_CODE)
ErrCode GeoDB::Open (LPSTORAGE pIStorage)
{
ErrCode RC;

	DBASSERT (DBTemplate::Open (pIStorage));

	ReReadHeader();
	return EC_OKAY;
}
#endif // defined(_USE_LEGACY_CODE)

ErrCode GeoDB::Close (BOOL fCommit) 
{
#if defined(_USE_LEGACY_CODE)
	DELETE_OBJ (_pDBCont);		// DBContainer freigeben
#endif // defined(_USE_LEGACY_CODE)
	return DBTemplate::Close (fCommit);
}

#if defined(_USE_LEGACY_CODE)
// Funktionen für PBD-DatenbankHandling ---------------------------------------
EXPORT02 PBD_DB::PBD_DB (void)
{
	m_pIdents = NULL;
	m_pMCodes = NULL;
	m_pRCodes = NULL;
	m_pPbdTemp = NULL;

	m_fCOMPbd = false;
}


EXPORT02 PBD_DB::~PBD_DB (void)
{
	if (isOpened()) {
		Close (false);	// wenn noch geöffnet, schließen
		SetGeoDB (NULL);
	}

	DELETE_OBJ (m_pIdents);
	DELETE_OBJ (m_pMCodes);
	DELETE_OBJ (m_pRCodes);
	ReleasePBDTempTree();
}


EXPORT02 PBD_DB::PBD_DB (const char *pDBName)
		 : DBTemplate (pDBName)
{
	m_pIdents = NULL;
	m_pMCodes = NULL;
	m_pRCodes = NULL;
	m_pPbdTemp = NULL;

	m_fCOMPbd = false;
}

ErrCode EXPORT02 PBD_DB::Open (LPSTORAGE pIStorage)
{
	if (isOpened()) return (EC_OKAY);	// DB bereits eröffnet

	_DBDesc = (HPROJECT)z_open_storage_pbd (pIStorage, GetROMode());
	if (!isOpened()) {
	ErrCode EC = ERRCODE_FROM_HRESULT(::GetLastError());
	
		if (EC == EC_OPENRO) {		// ReadOnly öffnen
			SetROMode (true);
			_DBDesc = (HPROJECT)z_open_storage_pbd (pIStorage, true);
		}
		if (!isOpened()) {
			_DBDesc = (HPROJECT)-2;		// erfolgloser Versuch
			return EC_NOOPEN;
		}
	}
	actDB = this;				// aktivierte DB setzen

	if (GetROMode()) 
		SetAccess (Z_ALL | Z_RDONLY); 	// DB ReadOnly

	DELETE_OBJ (_UserName);
	SetDirty (false);

return (EC_OKAY);
}

// jemand hat PBD geändert, also neue Einträge lesen
BOOL EXPORT02 PBD_DB::UpdateIdents (long lIdent)	// CPBDIdents aktualisieren
{
	if (lIdent == 0) {	// alles neu einlesen
		DELETE_OBJ (m_pIdents);
		return true;
	}
	
// nur einen Eintrag erneuern
	if (!m_pIdents) return true;		// kein Baum da
	
CTable t (*m_pIdents);

// alten Eintrag löschen
	if (t.Find (&lIdent)) t.Delete();

	{
	// neuen Eintrag einlesen
	ErrInstall EI (WC_NOIDENT);
	PBD_Ident pbdID (this, lIdent);		// fügt neu en

		pbdID.GetCode();		// dummy
	}

return true;
}

BOOL EXPORT02 PBD_DB::UpdateMCodes (long lMCode)
{
	if (lMCode == 0) {	// alles neu einlesen
		DELETE_OBJ (m_pMCodes);
		return true;
	}
	
// nur einen Eintrag erneuern
	if (!m_pMCodes) return true;		// kein Baum da
	
CTable t (*m_pMCodes);

// alten Eintrag löschen
	if (t.Find (&lMCode)) t.Delete();

	{
	// neuen Eintrag einlesen
	ErrInstall EI (WC_NOMERKMAL);
	PBD_Merkmal pbdM (this, lMCode);		// fügt neu en

		pbdM.GetCode();		// dummy
	}

return true;
}

BOOL EXPORT02 PBD_DB::UpdateRCodes (long lRCode)
{
	if (lRCode == 0) {	// alles neu einlesen
		DELETE_OBJ (m_pRCodes);
		return true;
	}
	
// nur einen Eintrag erneuern
	if (!m_pRCodes) return true;		// kein Baum da
	
CTable t (*m_pRCodes);

// alten Eintrag löschen
	if (t.Find (&lRCode)) t.Delete();

	{
	// neuen Eintrag einlesen
	ErrInstall EI (WC_NORELATION);
	PBD_Relation pbdRel (this, lRCode);		// fügt neu en

		pbdRel.GetCode();		// dummy
	}

return true;
}


// füllt die DatenStruktur pDataToFill mit einem Eintrag aus dem Baum ---------
BOOL PBD_DB::FillFromTree (PBD_Data *pDataToFill)
{
	switch (pDataToFill -> GetDataType()) {
	case PBD_IDENT:
		if (m_pIdents)
			return m_pIdents -> FillFromTree (pDataToFill);
		break;
		
	case PBD_MERKMAL:
		if (m_pMCodes)
			return m_pMCodes -> FillFromTree (pDataToFill);
		break;
		
	case PBD_RELATION:
		if (m_pRCodes)
			return m_pRCodes -> FillFromTree (pDataToFill);
		break;

	default:
		break;
	}

return false;
}


// Die Daten aus pNewData im Baum speichern -----------------------------------
BOOL PBD_DB::AddToTree (PBD_Data *pNewData)
{
	switch (pNewData -> GetDataType()) {
	case PBD_IDENT:
		if (!m_pIdents) m_pIdents = new CPBDIdents;
		if (m_pIdents)
			return m_pIdents -> AddToTree (pNewData);
		break;
		
	case PBD_MERKMAL:
		if (!m_pMCodes) m_pMCodes = new CPBDMCodes;
		if (m_pMCodes)
			return m_pMCodes -> AddToTree (pNewData);
		break;
		
	case PBD_RELATION:
		if (!m_pRCodes) m_pRCodes = new CPBDRCodes;
		if (m_pRCodes)
			return m_pRCodes -> AddToTree (pNewData);
		break;

	default:
		break;
	}

return false;
}


// Bäume freigeben ------------------------------------------------------------
void EXPORT02 PBD_DB::EveryDelete (void)
{
	DELETE_OBJ (m_pIdents);
	DELETE_OBJ (m_pMCodes);
	DELETE_OBJ (m_pRCodes);
	ReleasePBDTempTree();
}

// PBD - Initialisierung ------------------------------------------------------
BOOL PBD_DB::InitPBD (GeoDB &geoDB, char *PbdDBDir, BOOL iUseName) 
{
// wenn schon eine PBD existiert, dann diese zumachen
	Close();
	SetGeoDB (NULL);

// wenn GeoDB nicht eröffnet ist --> Fehler
	if (!geoDB.isOpened()) {
		db_error (EC_NOOPEN, RC_InitPBD);
		return false;
	}

// DatenBasis aktivieren
CActDB ActDB (geoDB);

	SetGeoDB (&geoDB);

// wenn GeoDB eine COM Datei ist, dann interne Pbd laden, wenn nicht 
// explizit ExternPbd gefordert wird
ResourceFile RF (g_pDLLName);
IStorage *pIStorage = NULL;

	if (SUCCEEDED(geoDB.GetProjectStorage (&pIStorage))) {
	HeaderEntry HE (geoDB, ResID (IDS_PBDCOMENTRY, &RF));

		pIStorage -> Release();
		if (0 == HE.EntryLong (0))		// not 'ForceExternPbd'
			return InitComPbd (geoDB);
	}

// aus GeoDB - Header PBDNamen bestimmen
	SetCOMFlag (false);

// dazu ResourceFile generieren
HeaderEntry HE (geoDB, ResID (IDS_PBDENTRY, &RF));

	if (!iUseName && HE.EntryText () == NULL) {
	// HeaderEntry fehlt
		_DBDesc = (HPROJECT)-2;	// gar nicht erst versuchen, PBD zu eröffnen
		db_error (EC_NOPBDNAME, RC_InitPBD, geoDB.DBDesc());
		return false;
	}

// PBD erst in Unterverzeichnis suchen
char *locPBDName = new char [_MAX_PATH];
char *pDrive = new char [_MAX_DRIVE];
char *pPath = new char [_MAX_DIR];
char *pName = new char [_MAX_FNAME];
char *pExt = new char [_MAX_EXT];

	if (!pDrive || !pPath || !locPBDName) {
		DELETE_VEC (locPBDName);
		DELETE_VEC (pDrive);
		DELETE_VEC (pPath);
		DELETE_VEC (pName);
		DELETE_VEC (pExt);
		db_error (EC_NOMEMORY, RC_InitPBD);
		return false;
	}

ResString Ext (ResID (IDS_STBEXT, &RF), 6);
OFSTRUCT of;

	_splitpath (PbdDBDir, NULL, NULL, pName, pExt);		// evtl. Namen benutzen
	_splitpath (geoDB.GetDBName(), pDrive, pPath, NULL, NULL);

// lokalen PBD-Pfad zusammenbauen
	_makepath (locPBDName, "", pPath, "", "");	// nur Pfad richten
	strcpy (pPath, locPBDName);
	strcat (pPath, ResString (ResID (IDS_PBDSUBDIR, &RF), 20));
	_makepath (locPBDName, pDrive, pPath, 
			iUseName ? pName : HE.EntryText(), 
			*pExt ? pExt : Ext+1); 

	if (OpenFile (locPBDName, &of, OF_EXIST | OF_READ) < 0)	{
	// mit neuer Erweiterung versuchen
	ResString NewExt (ResID (IDS_PBDEXT, &RF), 6);

		_makepath (locPBDName, pDrive, pPath, 
			   iUseName ? pName : HE.EntryText(), 
			   NewExt +1);

		if (OpenFile (locPBDName, &of, OF_EXIST | OF_READ) < 0)	{
		// PBD steht nicht lokal, default zentral suchen
			_splitpath (PbdDBDir, pDrive, pPath, pName, NULL);
			_makepath (locPBDName, pDrive, pPath, 
				   iUseName ? pName : HE.EntryText(), 
				   *pExt ? pExt : Ext+1);

			if (OpenFile (locPBDName, &of, OF_EXIST | OF_READ) < 0)	{
			// auch hier neue Erweiterung annehmen
				_makepath (locPBDName, pDrive, pPath, 
					   iUseName ? pName : HE.EntryText(), 
					   NewExt+1);
			}
		}
	}
	SetDBName (locPBDName);

// Speicher wieder freigeben
	DELETE_VEC (locPBDName);
	DELETE_VEC (pDrive);
	DELETE_VEC (pPath);
	DELETE_VEC (pName);
	DELETE_VEC (pExt);

// ReadOnlyFlag setzen
	SetROMode (true);		// PBD wird nur gelesen
	SetDirty (false);

return true;
}

BOOL PBD_DB::InitComPbd (GeoDB &rDB)
{
// Namen der Internen PBD setzen
ResourceFile RF (g_pDLLName);

	SetDBName ((char *)ResString (ResID (IDS_COMPBDNAME, &RF), 32).Addr());
	SetCOMFlag (true);

// ReadOnlyFlag setzen
	SetROMode (rDB.GetROMode());
	SetDirty (false);

return true;
}

ErrCode EXPORT02 PBD_DB::Flush (BOOL fCommit)		// alles wegschreiben
{
	if (!isOpened())
		return (ErrCode)db_error ((int)EC_NOOPEN, (int)RC_FlushDB);

ErrCode RC;

	DBASSERT (SetAccess (Z_ALL | Z_RDWR));
	DBASSERT (DBTemplate::Flush (fCommit));
	DBASSERT (RestoreAccess (Z_ALL));

	if (GetCOMFlag() && NULL != GetGeoDB())
		GetGeoDB() -> SetDirty (true);

return EC_OKAY;
}
#endif // defined(_USE_LEGACY_CODE)

// Virtuelle Funktionen -------------------------------------------------------
DBTyp GeoDB::isA (void) { return O_GEODB; }
#if defined(_USE_LEGACY_CODE)
DBTyp PBD_DB::isA (void) { return  O_PBDDB; }
#endif // defined(_USE_LEGACY_CODE)

// Transaktionsverwaltung -----------------------------------------------------
ErrCode DBTemplate::BeginTransaction (void)
{
// wenn DB nicht eröffnet ist
	if (!isOpened()) 			// Keine DB eröffnet
		return (ErrCode)db_error ((int)EC_NOOPEN, (int)RC_BeginTrans);

#if defined(_USE_LEGACY_CODE)
CActDB ActDB (*this);
ErrCode RC;

	DBASSERT (SetAccess (Z_ALL | Z_RDWR));
	DBASSERT (Flush());
	DBASSERT (z_touch (DBDesc()));
	DBASSERT (RestoreAccess (Z_ALL));
#endif // defined(_USE_LEGACY_CODE)
	return EC_OKAY;
}


ErrCode DBTemplate::BreakTransaction (void)
{
// wenn DB nicht eröffnet ist
	if (!isOpened()) 			// Keine DB eröffnet
		return (ErrCode)db_error ((int)EC_NOOPEN, (int)RC_BreakTrans);

#if defined(_USE_LEGACY_CODE)
CActDB ActDB (*this);
ErrCode RC;

	DBASSERT (SetAccess (Z_ALL | Z_RDWR));
	DBASSERT (Restore());
	DBASSERT (z_restore (DBDesc()));
	DBASSERT (RestoreAccess (Z_ALL));
#endif // defined(_USE_LEGACY_CODE)
	return EC_OKAY;
}

// FriendFunktionen -----------------------------------------------------------

// Liefern Unique- Identifikator, MerkmalsCode und RelationsCode --------------
long GeoDB::GetUniqueICode (BOOL fSystem)
{
//	if (fSystem)
//		return GetUniqueLong (IDS_HDRUNIQUESYSICODE, FIRSTUNIQUESYSICODE);

long lFirstCode = DEX_GetIdBase() == 10 ? FIRSTUNIQUEICODE : FIRSTUNIQUEICODEX;

	return GetUniqueLong (IDS_HDRUNIQUEICODE, lFirstCode);
}

long GeoDB::GetUniqueMCode (BOOL fSystem)
{
	if (fSystem)
		return GetUniqueLong (IDS_HDRUNIQUESYSMCODE, FIRSTUNIQUESYSMCODE);

return GetUniqueLong (IDS_HDRUNIQUEMCODE, FIRSTUNIQUEMCODE);
}

long GeoDB::GetUniqueRCode (void)
{
	return GetUniqueLong (IDS_HDRUNIQUERCODE, FIRSTUNIQUERCODE);
}

long GeoDB::GetUniqueTempONr (void)
{
	return GetUniqueLong (IDS_HDRUNIQUETEMPON, FIRSTUNIQUETEMPON);
}

long GeoDB::GetUniqueLong (unsigned int resID, long lFirstCode)
{
ResourceFile RF (g_pDLLName);
ErrInstall EI (WC_NOTFOUND);
HeaderEntry HE (*this, ResID (resID, &RF));
long lEntry;
char lText[20];

	if ((lEntry = HE.EntryLong (-1)) == -1) 
	// Entry existiert noch nicht
		lEntry = lFirstCode;

// Eintrag wegschreiben
	_ltoa (lEntry +1, lText, 10);
	HE.SetEntryText (lText);
	HE.Flags() = HEADER_SYSTEMRO;

	if (HE.WriteBack() != EC_OKAY) 
		lEntry = -1L;

	SetDirty (true);
	return lEntry;		// Unique Wert liefern
} 

///////////////////////////////////////////////////////////////////////////////
// Liefert den LPSTORAGE für ein Projekt, wenn es ein CompoundFile ist 
HRESULT EXPORT02 GeoDB::GetProjectStorage (LPSTORAGE *ppIStorage)
{
#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	// wenn DB nicht eröffnet ist
		if (!isOpened()) return E_FAIL;	// Keine DB eröffnet
		if (NULL == ppIStorage) return E_FAIL;

		*ppIStorage = NULL;
		return ::GetProjectStorage (_DBDesc, ppIStorage);
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

		if (NULL == ppIStorage) 
			return E_POINTER;
		*ppIStorage = NULL;
		COM_TRY {
		// Storage-Property der Database abfragen
		WTRiASDatabase DBase;
		WTRiASProperties Props;

			THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));
			THROW_FAILED_HRESULT(WTRiASPropertyBase(DBase) -> get_Properties (Props.ppi()));

			*ppIStorage = (IStorage *)GetProperty (Props, g_cbStgService, (IUnknown *)NULL);

		} COM_CATCH;
		return (NULL != *ppIStorage) ? S_OK : E_FAIL;
	}
}

HRESULT GeoDB::GetDataSourceDescription (char *pDesc, int iLen)
{
#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) 
		return E_FAIL;
#endif // _USE_LEGACY_CODE
	TX_ASSERT(IsTRiASDBBased());

	COM_TRY {
	// Description der Connection liefern
	CComBSTR bstrDesc;

		THROW_FAILED_HRESULT(m_Conn -> get_Description (CLEARED(&bstrDesc)));
		USES_CONVERSION;

		if (bstrDesc.Length() > iLen) {
			strncpy (pDesc, OLE2A(bstrDesc), iLen);
			pDesc[iLen-1] = '\0';
			return S_FALSE;
		} else
			strcpy (pDesc, OLE2A(bstrDesc));
	} COM_CATCH;
	return S_OK;
}

HRESULT GeoDB::GetDataSourceName (char *pDesc, int iLen)
{
#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) 
		return E_FAIL;
#endif // _USE_LEGACY_CODE
	TX_ASSERT(IsTRiASDBBased());

	COM_TRY {
	// Description der Connection liefern
	CComBSTR bstrDesc;

		THROW_FAILED_HRESULT(m_Conn -> get_Name (CLEARED(&bstrDesc)));
		USES_CONVERSION;

		if (bstrDesc.Length() > iLen) {
			strncpy (pDesc, OLE2A(bstrDesc), iLen);
			pDesc[iLen-1] = '\0';
			return S_FALSE;
		} else
			strcpy (pDesc, OLE2A(bstrDesc));
	} COM_CATCH;
	return S_OK;
}

#if defined(_USE_LEGACY_CODE)
ErrCode EXPORT02 GeoDB::Flush (BOOL fCommit) 
{
	return DBTemplate::Flush (fCommit);
}
#endif // defined(_USE_LEGACY_CODE)

#if defined(WIN32)
LONG GeoDB::CountObjects (void)
{
#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (*this);
	short iFNr = (VERSION0500000E <= GetDBVersion()) ? OBL_NEW : OBL_OLD;

		return ladr_ (DBDesc(), &iFNr, false);
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		WTRiASDatabase DBase;
		long lCount = 0L;

			THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));
			THROW_FAILED_HRESULT(WTRiASAccessDatabase(DBase) -> get_ObjectCount (&lCount));
			return lCount;
					
		} COM_CATCH_RETURN(0L);
	}
}

LONG GeoDB::CountClasses (void)
{
#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (*this);
	short iFNr = IDL;

		return ladr_ (DBDesc(), &iFNr, false);
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		WTRiASDatabase DBase;
		WTRiASObjectsCollection ObjsColl;
		long lCount = 0L;

			THROW_FAILED_HRESULT(m_Conn -> get_Database (DBase.ppi()));
			THROW_FAILED_HRESULT(WTRiASAccessDatabase(DBase) -> get_ObjectsDefs (ObjsColl.ppi()));
			THROW_FAILED_HRESULT(ObjsColl -> get_Count (&lCount));
			return lCount;
					
		} COM_CATCH_RETURN(0L);
	}
}

#if defined(_USE_LEGACY_CODE)	// Ansichten nicht mehr in der GeoDB
LONG GeoDB::CountViews (void)
{
	TX_ASSERT(!IsTRiASDBBased());

CActDB ActDB (*this);
short iFNr = SICHT;
LONG lCnt = ladr_ (DBDesc(), &iFNr, false);

	return (lCnt > 0) ? lCnt-1 : 0L;	// __DefaultVisInfo__
}
#endif // _USE_LEGACY_CODE

#endif // WIN32

