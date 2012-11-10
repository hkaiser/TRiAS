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

#include "trias02r.h"

#include "pbdids.hxx"	// CPBDIdents

// globale Variablen
extern char g_pDLLName[];

// locale Variablen
static DBTemplate *actDB = NULL;	// derzeit aktivierte DB

// Konstruktoren
DBTemplate :: DBTemplate (void) 
{
	_DBDesc = (HPROJECT)0;
	_DBName = NULL;
	_UserName = NULL;
	_ReadOnlyFlag = true;

	m_fTemp = false;
	m_fIsDirty = false;
}


DBTemplate :: DBTemplate (const char *DBName) 
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
}

DBTemplate :: DBTemplate (const DBTemplate &DB) 
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
}

// Destruktor
DBTemplate :: ~DBTemplate (void) 
{
	if (actDB == this)
		actDB = NULL;
	DELETE_VEC (_UserName);
	DELETE_VEC (_DBName);
}

// Memberfunktionen
void DBTemplate :: operator =(const DBTemplate &DB) 
{
// alte DB freigeben
	DELETE_VEC (_DBName);
	DELETE_VEC (_UserName);
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
}

void DBTemplate :: SetDBName (char *DBName) 
{
	DELETE_VEC (_DBName);
	_DBName = new char [strlen (DBName) +1];
	if (_DBName == NULL) {
		db_error (EC_NOMEMORY, RC_SetDBName);
		return;
	}
	strcpy (_DBName, DBName);
}

bool DBTemplate :: GetTempDBName (char *pDBName) 
{
	if (!isOpened()) return false;	// DB nicht eröffnet

// wenn temporär und Com-Datei
	if (m_fTemp) {
	IStorage *pIStorage = NULL;
		
		if (SUCCEEDED(::GetProjectStorage (_DBDesc, &pIStorage))) {
		STATSTG st;

			pIStorage -> Stat (&st, STATFLAG_DEFAULT);
			strcpy (pDBName, AnsiString (st.pwcsName));
//			WideCharToMultiByte (CP_ACP, 0, st.pwcsName, 
//						-1, pDBName, _MAX_PATH, NULL, NULL);

		// aufräumen
			CoTaskMemFree (st.pwcsName);
			pIStorage -> Release();
			return true;
		}
	} 

// alle anderen Fälle liefern den richtigen Namen	
	strcpy (pDBName, _DBName);

return true;
}

#ifdef NOINLINES
// Inline-Funktionen ----------------------------------------------------------
// Liefert DB-Descriptor
short DBTemplate :: DBDesc (void) { return _DBDesc; }

// Setzen des OpenModes
bool DBTemplate :: SetROMode (bool newMode) 
{
register bool oldMode = _ReadOnlyFlag;

	_ReadOnlyFlag = newMode;

return oldMode;
}

// OpenMode lesen
bool DBTemplate :: GetROMode (void) { return _ReadOnlyFlag; }

#endif // NOINLINES

// Datenbasisarbeit -----------------------------------------------------------
// DB Eröffnen
ErrCode DBTemplate :: Open (char *UserName, char *PassWord, DWORD dwMode) 
{
	if (isOpened()) return (EC_OKAY);	// DB bereits eröffnet
	if (_DBName == NULL)			// DBName nicht gegeben
		return ((ErrCode)db_error (EC_NODBNAME, RC_OPEN));

	_DBDesc = (HPROJECT)z_open (_DBName, UserName, PassWord, _ReadOnlyFlag, dwMode);
	if (!isOpened()) {
	ErrCode EC = (ErrCode)(short)_DBDesc;
	
		if (EC == EC_OPENRO) {		// ReadOnly öffnen
			_ReadOnlyFlag = true;
			_DBDesc = (HPROJECT)z_open (_DBName, UserName, PassWord, true, dwMode);
		}
		if (!isOpened()) {
			_DBDesc = (HPROJECT)-2;		// erfolgloser Versuch
			return EC_NOOPEN;
		}
	}

	::GetCopyMode (_DBDesc, &m_fIsCopy);
	::GetROMode (_DBDesc, &_ReadOnlyFlag);

	actDB = this;				// aktivierte DB setzen
	if (_ReadOnlyFlag) 
		SetAccess (Z_ALL | Z_RDONLY); 	// DB ReadOnly

	DELETE_VEC (_UserName);
	if (UserName) {
		_UserName = new char [strlen (UserName) +1];
		if (_UserName == NULL)
			return ((ErrCode)db_error (EC_NOMEMORY, RC_OPEN));
		strcpy (_UserName, UserName);
	}

	SetDirty (false);

return (EC_OKAY);
}

ErrCode DBTemplate :: Open (LPSTORAGE pIStorage) 
{
	if (isOpened()) return (EC_OKAY);	// DB bereits eröffnet

	_DBDesc = (HPROJECT)z_open_storage (pIStorage, _ReadOnlyFlag, m_fTemp);
	if (!isOpened()) {
	ErrCode EC = (ErrCode)(short)_DBDesc;
	
		if (EC == EC_OPENRO) {		// ReadOnly öffnen
			_ReadOnlyFlag = true;
			_DBDesc = (HPROJECT)z_open_storage (pIStorage, true, false);
		}
		if (!isOpened()) {
			_DBDesc = (HPROJECT)-2;		// erfolgloser Versuch
			return EC_NOOPEN;
		}
	}

	::GetCopyMode (_DBDesc, &m_fIsCopy);
	::GetROMode (_DBDesc, &_ReadOnlyFlag);

	actDB = this;				// aktivierte DB setzen
	if (_ReadOnlyFlag) 
		SetAccess (Z_ALL | Z_RDONLY); 	// DB ReadOnly

	DELETE_VEC (_UserName);

	SetDirty (false);

return (EC_OKAY);
}

// DB Schließen ---------------------------------------------------------------
ErrCode DBTemplate :: Close (bool fCommit) 
{
	if (!isOpened()) {
		if ((short)_DBDesc == -2) _DBDesc = (HPROJECT)-1;
		return (EC_OKAY);	// DB bereits abgeschlossen
	}

CActDB ActDB (*this);
ErrCode RC;
	
	DBASSERT (z_close (_DBDesc, fCommit));
	_DBDesc = (HPROJECT)0;		// DB geschlossen
	DELETE_VEC (_DBName);
	DELETE_VEC (_UserName);

return EC_OKAY;
}

// Zugriffsmode für DB setzen -------------------------------------------------
ErrCode DBTemplate :: SetAccess (long Mode) 
{
CActDB ActDB (*this);

	return (ErrCode)z_access (DBDesc(), Mode);
}

ErrCode DBTemplate :: RestoreAccess (long Mode) 
{
CActDB ActDB (*this);

	return (ErrCode)z_raccess (DBDesc(), Mode);
}

// Nummer des letzten existierenden Satzes einer DB-Datei bestimmen -----------
long DBTemplate :: LastRec (short Datei) 
{ 
CActDB ActDB (*this);

	return (ladr_(DBDesc(), &Datei, true) +1); 
}

// neue DB aktivieren ---------------------------------------------------------
DBTemplate * DBTemplate :: Activate (void) 
{
	if (!isOpened()) return actDB;	// nicht mehr eröffnet

DBTemplate *oldDB = actDB;		// alte DB merken
HPROJECT oldnum = z_activate (DBDesc());

	if (actDB != NULL && oldnum != actDB -> DBDesc()) {
	// DAS sollte nicht passieren !
		z_activate (oldnum);		// zurückschalten
		db_error (EC_SYSERROR, RC_Activate);
		return NULL;
	}
	actDB = this;		// neue DB einstellen

return oldDB;
}

// als Dirty markieren --------------------------------------------------------
void EXPORT02 DBTemplate :: SetDirty (bool fDirty)
{ 
	m_fIsDirty = fDirty ? true : false; 
}

void EXPORT02 GeoDB :: SetDirty (bool fDirty)
{
CActDB ActDB (*this);
bool fNewDirty = fDirty ? true : false;

	if (isDirty() ^ fNewDirty) {
		DBTemplate :: SetDirty (fDirty);
		DEXN_GeoDBisDirty (fDirty);
	}
}

void EXPORT02 PBD_DB :: SetDirty (bool fDirty)
{
	DBTemplate :: SetDirty (fDirty);
	if (fDirty)		// zugehörige GeoDB ist in jedem Fall Dirty
		DEX_SetDirtyGeoDB (true);
}

DBTemplate *PBD_DB :: ActivateCOMPbd (void) 
{
DBTemplate *oldDB = NULL;
IStorage *pIStorage = NULL;
GeoDB *pDB = GetGeoDB();

	if (NULL == pDB) return NULL;

	if (!pDB -> GetProjectStorage (&pIStorage))
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
			if (db_error (EC_INVPBDNAME, RC_Activate) == EC_OKAY) {
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
				if (db_error (EC_INVPBDNAME, RC_Activate) == EC_OKAY) {
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

DBTemplate *PBD_DB :: Activate (void) 
{
DBTemplate *oldDB = NULL;

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
					if (db_error (EC_INVPBDNAME, RC_Activate) == EC_OKAY) {
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
		return DBTemplate :: Activate();
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
ErrCode DBTemplate :: Flush (bool fCommit) 
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
ErrCode DBTemplate :: Restore (void)
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

// Version dieser DB liefern --------------------------------------------------
long DBTemplate :: GetDBVersion (void) 
{
CActDB ActDB (*this);

	return ::GetDBVersion(DBDesc());
}

// Pfad zu DB liefern ---------------------------------------------------------
char *DBTemplate :: GetDBPath (char *Buff, short BuffLen) 
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


// Memberfunktionen GeoDB -----------------------------------------------------
ObjContainer GeoDB :: DBCont (bool fReRead) 
{
long Cont[4];
register ErrCode EC;

// DB Container bestimmen
	if (!isOpened()) {			// Keine DB eröffnet
		db_error ((int)EC_NOOPEN, (int)RC_DBCont);
		return ObjContainer (0, 0, 0, 0);
	}

// DB aktivieren
CActDB ActDB (*this);

	if (fReRead) {
		DELETE (_pDBCont);
	}

	if (_pDBCont != NULL)
	// Container bereits bestimmt
		return *_pDBCont;

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

ErrCode GeoDB :: Open (char *pUser, char *pPasswd, DWORD dwMode)
{
ErrCode RC;

	DBASSERT (DBTemplate :: Open (pUser, pPasswd, dwMode));

	ReReadHeader();

return EC_OKAY;
}

void EXPORT02 GeoDB :: ReReadHeader (void)
{
// dazu ResourceFile generieren
ResourceFile RF (g_pDLLName);
HeaderEntry HE (*this, ResID (IDS_TEXTOBJMCODE, &RF));

	_lTextObjMCode = HE.EntryLong (0L);	// MerkmalsCode für TextObjekte holen
}

ErrCode GeoDB :: Open (LPSTORAGE pIStorage)
{
ErrCode RC;

	DBASSERT (DBTemplate :: Open (pIStorage));

	ReReadHeader();

return EC_OKAY;
}

ErrCode GeoDB :: Close (bool fCommit) 
{
// DBContainer freigeben

	DELETE (_pDBCont);	// Container freigeben

return DBTemplate :: Close (fCommit);
}


// Funktionen für PBD-DatenbankHandling ---------------------------------------
EXPORT02 PBD_DB :: PBD_DB (void)
{
	m_pIdents = NULL;
	m_pMCodes = NULL;
	m_pRCodes = NULL;
	m_pPbdTemp = NULL;

	m_fCOMPbd = false;
}


EXPORT02 PBD_DB :: ~PBD_DB (void)
{
	if (isOpened()) {
		Close (false);	// wenn noch geöffnet, schließen
		SetGeoDB (NULL);
	}

	DELETE (m_pIdents);
	DELETE (m_pMCodes);
	DELETE (m_pRCodes);
	ReleasePBDTempTree();
}


EXPORT02 PBD_DB :: PBD_DB (const char *pDBName)
		 : DBTemplate (pDBName)
{
	m_pIdents = NULL;
	m_pMCodes = NULL;
	m_pRCodes = NULL;
	m_pPbdTemp = NULL;

	m_fCOMPbd = false;
}

ErrCode EXPORT02 PBD_DB :: Open (LPSTORAGE pIStorage)
{
	if (isOpened()) return (EC_OKAY);	// DB bereits eröffnet

	_DBDesc = (HPROJECT)z_open_storage_pbd (pIStorage, GetROMode());
	if (!isOpened()) {
	ErrCode EC = (ErrCode)(short)_DBDesc;
	
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

	DELETE_VEC (_UserName);
	SetDirty (false);

return (EC_OKAY);
}

// jemand hat PBD geändert, also neue Einträge lesen
bool EXPORT02 PBD_DB :: UpdateIdents (long lIdent)	// CPBDIdents aktualisieren
{
	if (lIdent == 0) {	// alles neu einlesen
		DELETE (m_pIdents);
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

bool EXPORT02 PBD_DB :: UpdateMCodes (long lMCode)
{
	if (lMCode == 0) {	// alles neu einlesen
		DELETE (m_pMCodes);
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

bool EXPORT02 PBD_DB :: UpdateRCodes (long lRCode)
{
	if (lRCode == 0) {	// alles neu einlesen
		DELETE (m_pRCodes);
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
bool PBD_DB :: FillFromTree (PBD_Data *pDataToFill)
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
bool PBD_DB :: AddToTree (PBD_Data *pNewData)
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
void EXPORT02 PBD_DB :: EveryDelete (void)
{
	DELETE (m_pIdents);
	DELETE (m_pMCodes);
	DELETE (m_pRCodes);
	ReleasePBDTempTree();
}

// PBD - Initialisierung ------------------------------------------------------
bool PBD_DB :: InitPBD (GeoDB &geoDB, char *PbdDBDir, bool iUseName) 
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

	if (geoDB.GetProjectStorage (&pIStorage)) {
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
		db_error (EC_NOPBDNAME, RC_InitPBD);
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

bool PBD_DB :: InitComPbd (GeoDB &rDB)
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

ErrCode EXPORT02 PBD_DB :: Flush (bool fCommit)		// alles wegschreiben
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

// Virtuelle Funktionen -------------------------------------------------------
DBTyp GeoDB :: isA (void) { return O_GEODB; }
DBTyp PBD_DB :: isA (void) { return  O_PBDDB; }

// Transaktionsverwaltung -----------------------------------------------------
ErrCode DBTemplate :: BeginTransaction (void)
{
// wenn DB nicht eröffnet ist
	if (!isOpened()) 			// Keine DB eröffnet
		return (ErrCode)db_error ((int)EC_NOOPEN, (int)RC_BeginTrans);

CActDB ActDB (*this);
ErrCode RC;

	DBASSERT (SetAccess (Z_ALL | Z_RDWR));
	DBASSERT (Flush());
	DBASSERT (z_touch (DBDesc()));
	DBASSERT (RestoreAccess (Z_ALL));

return EC_OKAY;
}


ErrCode DBTemplate :: BreakTransaction (void)
{
// wenn DB nicht eröffnet ist
	if (!isOpened()) 			// Keine DB eröffnet
		return (ErrCode)db_error ((int)EC_NOOPEN, (int)RC_BreakTrans);

CActDB ActDB (*this);
ErrCode RC;

	DBASSERT (SetAccess (Z_ALL | Z_RDWR));
	DBASSERT (Restore());
	DBASSERT (z_restore (DBDesc()));
	DBASSERT (RestoreAccess (Z_ALL));

return EC_OKAY;
}

// FriendFunktionen -----------------------------------------------------------
// Liefern Unique- Identifikator, MerkmalsCode und RelationsCode --------------
long GeoDB :: GetUniqueICode (bool fSystem)
{
//	if (fSystem)
//		return GetUniqueLong (IDS_HDRUNIQUESYSICODE, FIRSTUNIQUESYSICODE);

long lFirstCode = DEX_GetIdBase() == 10 ? FIRSTUNIQUEICODE : FIRSTUNIQUEICODEX;

	return GetUniqueLong (IDS_HDRUNIQUEICODE, lFirstCode);
}

long GeoDB :: GetUniqueMCode (bool fSystem)
{
	if (fSystem)
		return GetUniqueLong (IDS_HDRUNIQUESYSMCODE, FIRSTUNIQUESYSMCODE);

return GetUniqueLong (IDS_HDRUNIQUEMCODE, FIRSTUNIQUEMCODE);
}

long GeoDB :: GetUniqueRCode (void)
{
	return GetUniqueLong (IDS_HDRUNIQUERCODE, FIRSTUNIQUERCODE);
}

long GeoDB :: GetUniqueTempONr (void)
{
	return GetUniqueLong (IDS_HDRUNIQUETEMPON, FIRSTUNIQUETEMPON);
}

long GeoDB :: GetUniqueLong (unsigned int resID, long lFirstCode)
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

// Liefert den LPSTORAGE für ein Projekt, wenn es ein CompoundFile ist --------
bool EXPORT02 GeoDB :: GetProjectStorage (LPSTORAGE *ppIStorage)
{
// wenn DB nicht eröffnet ist
	if (!isOpened()) return false;	// Keine DB eröffnet
	if (NULL == ppIStorage) return false;

	*ppIStorage = NULL;

return SUCCEEDED(::GetProjectStorage (_DBDesc, ppIStorage));
}

ErrCode EXPORT02 GeoDB :: Flush (bool fCommit) 
{
	return DBTemplate :: Flush (fCommit);
}

#if defined(WIN32)
LONG GeoDB::CountObjects (void)
{
CActDB ActDB (*this);
short iFNr = OBL_OLD;

	return ladr_ (DBDesc(), &iFNr, false);
}

LONG GeoDB::CountClasses (void)
{
CActDB ActDB (*this);
short iFNr = IDL;

	return ladr_ (DBDesc(), &iFNr, false);
}

LONG GeoDB::CountViews (void)
{
CActDB ActDB (*this);
short iFNr = SICHT;
LONG lCnt = ladr_ (DBDesc(), &iFNr, false);

	return (lCnt > 0) ? lCnt-1 : 0L;	// __DefaultVisInfo__
}
#endif // WIN32
