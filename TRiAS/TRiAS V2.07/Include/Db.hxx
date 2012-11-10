// Headerdatei für C++ - Objekt DB (Datenbasis) -------------------------------
// File: DB.HXX

#ifdef sccs 
static char SccsId[] = "IRISWIN: %W%	%E%";
#endif

#ifndef _DB_HXX
#define _DB_HXX

#if !defined(TPPunkt)
#define TPCustomized	0x00		// nicht DefaultVisInfo
#define TPDefaultInfo	0x80		// DefaultVisInfo

#define TPUnknown	0x00

#define TPPunkt		0x01
#define TPLinie		0x02
#define TPFlaeche	0x04
#define TPText		0x08
#define TPAll		0x0f

#define TPKO		0x10
#define TPSO		0x20
#endif

// Zugriffsrechte für DB
// Der Zugriffs-Parameter für die Funktion z_access setzt sich aus 2 Teilen
// zusammen:	LOWORD - neue Zugriffsrechte (Z_NOACC, Z_RDONLY, Z_RDWR)
//		HIWORD - Z_ALL - alle Dateien oder Dateinummer
#define Z_ALL 		0x80000000 	// Alle Dateien
#define Z_NOACC 	-1		// Kein Zugriff
#define Z_RDONLY 	0		// nur Lesezugriff
#define Z_RDWR 		2		// Lese- und Schreibzugriff

#if !defined(EXPORT02)
#define EXPORT02 
#endif

#if !defined(_TRIAS02_ENTRY)
#define _TRIAS02_ENTRY 
#endif

#if !defined(NODBTEMPLATE)
class DBTemplate {
protected:
	char *_DBName;	// DB-Name
	char *_UserName;
	HPROJECT _DBDesc;	// DB-Deskriptor nach öffnen

private:
	bool _ReadOnlyFlag;	
	bool m_fTemp;		// temporäres Projekt, bei schließen löschen
	bool m_fIsDirty;	// wurde modifiziert
	bool m_fIsCopy;		// ist Kopie der OriginalDatei

// private Memberfunktionen
virtual DBTyp isA (void) = 0;	// pure virtual function

protected:
// Konstruktoren (können nicht direkt gerufen werden)
_TRIAS02_ENTRY EXPORT02 DBTemplate (void);
_TRIAS02_ENTRY EXPORT02 DBTemplate (const char *DBName);
_TRIAS02_ENTRY EXPORT02 DBTemplate (const DBTemplate &DB);

public:
// Memberfunktionen
	void operator =(const DBTemplate &);

// Datenbasis - Arbeit
_TRIAS02_ENTRY virtual ErrCode EXPORT02 Open (char *UserName, char *PassWord, DWORD dwMode);	// Eröffnen der DB
_TRIAS02_ENTRY virtual ErrCode EXPORT02 Open (LPSTORAGE);	// Eröffnen der DB
_TRIAS02_ENTRY virtual ErrCode EXPORT02 Close (bool fCommit = true);	// Schließen der DB
_TRIAS02_ENTRY virtual ErrCode EXPORT02 SetAccess (long);	// ZugriffsMode setzen
_TRIAS02_ENTRY virtual ErrCode EXPORT02 RestoreAccess (long);	// Zugriffsmode wieder rücksetzen

_TRIAS02_ENTRY virtual ErrCode EXPORT02 Flush (bool fCommit = true);		// alles wegschreiben

	ErrCode Restore (void);		// alles verwerfen

_TRIAS02_ENTRY ErrCode EXPORT02 BeginTransaction (void);	// Transaktion starten
	ErrCode EndTransaction (void) { return BeginTransaction(); }
		// Transaktion abschließen
_TRIAS02_ENTRY ErrCode EXPORT02 BreakTransaction (void);

_TRIAS02_ENTRY virtual DBTemplate * EXPORT02 Activate (void);	// DB aktivieren

inline HPROJECT EXPORT02 DBDesc (void);		// DB-Descriptor
_TRIAS02_ENTRY long EXPORT02 LastRec (short);		// letzter existierender Satz in Datei

inline	bool SetROMode (bool);		// ReadOnlyFlag setzen
inline	bool GetROMode (void);		// ReadOnlyFlag lesen
inline	bool isCopy (void) { return m_fIsCopy; }	// IsCopyFlag lesen

_TRIAS02_ENTRY void EXPORT02 SetDBName (char *);	// DBNamen setzen
_TRIAS02_ENTRY bool EXPORT02 GetTempDBName (char *);	// DBNamen setzen

	const char *GetDBName (void) { return _DBName; } // DBNamen liefern
	const char *GetUserName (void) { return _UserName ? _UserName : ""; }	// UserName liefern

_TRIAS02_ENTRY char * EXPORT02 GetDBPath (char *Buffer, short BuffLen);
_TRIAS02_ENTRY long EXPORT02 GetDBVersion (void);

	bool isOpened (void) { return (short)_DBDesc > 0; }
	HRESULT GetProjectStorage (LPSTORAGE *ppIStorage)
		{ return ::GetProjectStorage (DBDesc(), ppIStorage); }
	bool GetTempMode (void) { return m_fTemp; }
	void SetTempMode (bool fTemp) { m_fTemp = fTemp; }

	bool isDirty (void) { return m_fIsDirty; }

_TRIAS02_ENTRY virtual void SetDirty (bool fDirty = true);

// Destruktoren
_TRIAS02_ENTRY virtual EXPORT02 ~DBTemplate (void);
};

#if !defined(NOGEODB)

class DBDict;
class Protocol;
typedef struct tagENUMRELATIONOBJS ENUMRELATIONOBJS;

class GeoDB : public DBTemplate {
private:
	ObjContainer *_pDBCont;			// DBContainer
	ErrCode GetRigObj (long ONr, int *num, long **Feld);

	long _lTextObjMCode;

protected:
	long GetUniqueLong (unsigned int resID, long lFirstCode);

public:
// Konstruktoren
		GeoDB (void) { _pDBCont = NULL; _DBDesc = (HPROJECT)-2; }
		GeoDB (const char *DBName) 
			: DBTemplate (DBName) { _pDBCont = NULL; _DBDesc = (HPROJECT)-2; }

// Memberfunktionen
_TRIAS02_ENTRY ErrCode EXPORT02 Open (char *, char *, DWORD);
_TRIAS02_ENTRY ErrCode EXPORT02 Open (LPSTORAGE);	// Eröffnen der DB

// Geometriebehandlung
_TRIAS02_ENTRY ErrCode EXPORT02 GetGI (long ObjNr, GeoObjekt **, ObjContainer * = NULL);  
				// Geometrie aus DB lesen
_TRIAS02_ENTRY ErrCode EXPORT02 GIWindow (ObjContainer &, ObjFeld &, bool Flag);
				// Objekte in Window finden
_TRIAS02_ENTRY ErrCode EXPORT02 DelGI (long);			// Geometrie in DB löschen
_TRIAS02_ENTRY ErrCode EXPORT02 OverlayGI (long, GeoObjekt *);	// Geometrie überlagern
_TRIAS02_ENTRY ErrCode EXPORT02 PutGI (GeoObjekt *);		// Geometrie neu schreiben

_TRIAS02_ENTRY long EXPORT02 CreateObjTemplate (long lIdent, short iTyp);

_TRIAS02_ENTRY ErrCode EXPORT02 IdFilter (ObjFeld &, CIdTree &);		// Id's filtern
_TRIAS02_ENTRY ErrCode EXPORT02 IdFilter (ObjFeld &, char *);
_TRIAS02_ENTRY ErrCode EXPORT02 IdFilterNew (ObjFeld &, char *);
_TRIAS02_ENTRY ErrCode EXPORT02 IdFilterAll (ObjFeld &);

_TRIAS02_ENTRY ErrCode EXPORT02 RelInfo (long ONr, ObjFeld &);		// Relationen lesen
_TRIAS02_ENTRY ErrCode EXPORT02 RigInfo (long ONr, ObjFeld &);		// Topologie lesen
_TRIAS02_ENTRY ErrCode EXPORT02 FindText (long Code, int Mode, char *SText, ObjFeld &);

_TRIAS02_ENTRY ErrCode EXPORT02 FindId (long Id, long *FlexNum, short *pOTyp = NULL, long *plObjCnts = NULL);
_TRIAS02_ENTRY ErrCode EXPORT02 ReadText (long ONr, char * &pText, TextObjTyp &);// Text von OT_TEXT
_TRIAS02_ENTRY ErrCode EXPORT02 WriteText (long ONr, char *pText, BOOL fIndObjProp);
_TRIAS02_ENTRY ErrCode DelText (long ONr);

_TRIAS02_ENTRY ErrCode EXPORT02 ModGIPunkt (long ONr, Punkt &Pt);  	// neue PunktKoordinate

_TRIAS02_ENTRY ErrCode EXPORT02 Close (bool fCommit = true);
_TRIAS02_ENTRY ObjContainer EXPORT02 DBCont (bool fReRead = false);	// dbcodb

_TRIAS02_ENTRY bool EXPORT02 EnumIdents (bool (*pFcn)(long, bool, void *), void *pData);
_TRIAS02_ENTRY bool EXPORT02 EnumIdentsEx (bool (*pFcn)(long, DWORD, void *), void *pData, DWORD);
_TRIAS02_ENTRY bool EXPORT02 EnumIdentObjects (long, bool (*pFcn)(long, bool, void *), void *);
_TRIAS02_ENTRY bool EXPORT02 EnumIdentObjectsEx (long, bool (*pFcn)(long, DWORD, void *), void *, DWORD dwData);
_TRIAS02_ENTRY bool EXPORT02 EnumObjectsIdl (long lIdent, long lNext, bool (*pFcn)(long, bool, void *), void *pData);
_TRIAS02_ENTRY bool EXPORT02 EnumObjectsIdlEx (long lIdent, long lNext, bool fVerifyType, bool (*pFcn)(long, DWORD, void *), void *pData, DWORD dwData);
_TRIAS02_ENTRY bool EXPORT02 EnumHdrData (bool (*pFcn)(char *, bool, void *), void *pData);
_TRIAS02_ENTRY ErrCode EXPORT02 GetIdentObjectCounts (LONG lIdent, long *plObjCnts);
_TRIAS02_ENTRY ErrCode EXPORT02 GetObjectType (LONG lONr, int *piOTyp);

_TRIAS02_ENTRY bool EXPORT02 EnumRCodes (bool (*pFcn)(long, bool, void *), void *pData);
_TRIAS02_ENTRY bool EXPORT02 EnumRelationObjs (ENUMRELATIONOBJS *pERO);

_TRIAS02_ENTRY DBTyp EXPORT02 isA (void);

// Konsistenztest -------------------------------------------------------------
	ErrCode TestObjekt (DBDict &, Protocol &, long ONr, short toDo = 0);
	ErrCode DelObjekt (DBDict &, Protocol &, long ONr, short toDo = 0);
// ----------------------------------------------------------------------------

	long TOMCode (void) { return _lTextObjMCode; }
_TRIAS02_ENTRY void ReReadHeader (void);

// sonstige Member
_TRIAS02_ENTRY long EXPORT02 GetUniqueICode (bool fSystem = false);
_TRIAS02_ENTRY long EXPORT02 GetUniqueMCode (bool fSystem = false);
_TRIAS02_ENTRY long EXPORT02 GetUniqueRCode (void);
_TRIAS02_ENTRY long EXPORT02 GetUniqueTempONr (void);

	ErrCode doImport (pWindow pW);
	
_TRIAS02_ENTRY bool EXPORT02 VerifyGI (GeoObjekt *pGO);
_TRIAS02_ENTRY void SetDirty (bool fDirty = true);
_TRIAS02_ENTRY bool GetProjectStorage (LPSTORAGE *);
_TRIAS02_ENTRY ErrCode EXPORT02 Flush (bool fCommit = true);		// alles wegschreiben

#if defined(WIN32)
// Statistische Funktionen
_TRIAS02_ENTRY LONG CountObjects (void);
_TRIAS02_ENTRY LONG CountClasses (void);
_TRIAS02_ENTRY LONG CountViews (void);

_TRIAS02_ENTRY HRESULT GetObjectGUID (LONG lONr, struct _GUID *pGuid);
_TRIAS02_ENTRY HRESULT SetObjectGUID (LONG lONr, const _GUID &rGuid);
_TRIAS02_ENTRY HRESULT FindObjectFromGUID (const _GUID &rGuid, LONG *plONr);
_TRIAS02_ENTRY HRESULT GetObjectGUIDFeature (LONG lONr, LONG lMCode, _GUID *pGuid);
_TRIAS02_ENTRY HRESULT SetObjectGUIDFeature (LONG lONr, const _GUID &rGuid, LONG lMCode);
_TRIAS02_ENTRY HRESULT FindObjectFromGUIDFeature (const _GUID &rGuid, LONG lMCode, LONG *plONr);
#endif // WIN32

// Destruktor
		~GeoDB (void) { DELETE (_pDBCont); }
};
#endif // NOGEODB

#if !defined(NOPBDDB)

typedef struct tagPBDDATA PBDDATA;
class CPBDIdents;
class CPBDMCodes;
class CPBDRCodes;

class PBD_DB : public DBTemplate {
private:
	class CPBDIdents *m_pIdents;		// Baum aller IdentEntries der PBD
	class CPBDMCodes *m_pMCodes;		// Baum aller MCodeEntries der PBD
	class CPBDRCodes *m_pRCodes;		// Baum aller RCodeEntries der PBD

	class PBDTempTree *m_pPbdTemp;		// baum aller temporären Idents

	unsigned int m_fCOMPbd : 1;
	GeoDB *m_pGeoDB;					// zugehörige GeoDB
			
public:
// Konstruktor
	_TRIAS02_ENTRY PBD_DB (void);
	_TRIAS02_ENTRY PBD_DB (const char *DBName);
	_TRIAS02_ENTRY ~PBD_DB (void);

// Memberfunktionen
_TRIAS02_ENTRY DBTyp EXPORT02 isA (void);
_TRIAS02_ENTRY bool EXPORT02 InitPBD (GeoDB &, char *, bool = false);	// Initialisieren anhand der GeoDB
_TRIAS02_ENTRY bool EXPORT02 InitComPbd (GeoDB &);	// Initialisieren anhand der GeoDB
_TRIAS02_ENTRY void EveryDelete (void);		// Bäume freigeben
	
_TRIAS02_ENTRY ErrCode EXPORT02 GetPBDData (PBDDATA *);
_TRIAS02_ENTRY ErrCode EXPORT02 ModPBDData (PBDDATA *);
_TRIAS02_ENTRY ErrCode EXPORT02 DelPBDData (PBDDATA *);

_TRIAS02_ENTRY bool EXPORT02 EnumPBDData (long, bool (*)(long, bool, void *), void *);

_TRIAS02_ENTRY ErrCode EXPORT02 Open (LPSTORAGE);	// Eröffnen der DB
_TRIAS02_ENTRY DBTemplate * EXPORT02 Activate (void);	// PBD aktivieren
_TRIAS02_ENTRY DBTemplate * EXPORT02 ActivateCOMPbd (void);	// COM-PBD aktivieren
_TRIAS02_ENTRY ErrCode EXPORT02 Flush (bool fCommit = true);		// alles wegschreiben
	
_TRIAS02_ENTRY bool UpdateIdents (long lIdent = -1);	// CPBDIdents aktualisieren
_TRIAS02_ENTRY bool UpdateMCodes (long lIdent = -1);	// CPBDMCodes aktualisieren
_TRIAS02_ENTRY bool UpdateRCodes (long lIdent = -1);	// CPBDRCodes aktualisieren

	bool FillFromTree (PBD_Data *pDataToFill);
	bool AddToTree (PBD_Data *pNewData);

_TRIAS02_ENTRY bool AddToTempTree (PBD_Data &rData);
_TRIAS02_ENTRY bool RemoveFromTempTree (PBD_Data &rData);
_TRIAS02_ENTRY bool FillFromTempTree (PBD_Data &rData);
_TRIAS02_ENTRY void EXPORT02 ReleasePBDTempTree (void);

_TRIAS02_ENTRY void SetDirty (bool fDirty = true);

	void SetCOMFlag (bool fFlag) { m_fCOMPbd = fFlag ? true : false; }
	bool GetCOMFlag (void) { return m_fCOMPbd; }

// Zugriff auf rückverweis auf zugehörige GeoDB
	void SetGeoDB (GeoDB *pDB) { m_pGeoDB = pDB; }
	GeoDB *GetGeoDB (void) { return m_pGeoDB; }
};
#endif // NOPBDDB

// WrapperKlasse für das Aktivieren einer Datenbasis --------------------------
class CActDB {
private:
	DBTemplate *m_pDB;	// alte DB
	DBTemplate &m_rDB;	// aktuelle DB

public:
		CActDB (DBTemplate &rDB) : m_rDB (rDB), m_pDB (rDB.Activate()) {}
		~CActDB (void) { if (m_pDB) m_pDB -> Activate(); }

	void ReActivate (void) { m_rDB.Activate(); }
	DBTemplate &GetOldDB (void) { return *m_pDB; }
	bool operator ! (void) { return m_pDB == NULL; }
};


#ifndef NOINLINES
// Inline-Funktionen ----------------------------------------------------------
// Liefert DB-Descriptor
inline HPROJECT DBTemplate :: DBDesc (void) { return _DBDesc; }

// Setzen des OpenModes
inline bool DBTemplate :: SetROMode (bool newMode) 
{
register bool oldMode = _ReadOnlyFlag;

	_ReadOnlyFlag = newMode;

return oldMode;
}

// OpenMode lesen
inline bool DBTemplate :: GetROMode (void) { return _ReadOnlyFlag; }

#endif // NOINLINES

#endif // NODBTEMPLATE

#endif // _DB_HXX
