///////////////////////////////////////////////////////////////////////////
// Headerdatei für C++ - Objekt DB (Datenbasis) 
// File: DB.HXX

#if !defined(_DB_HXX__0E7FBA34_4D26_11d1_96E7_00A024D6F582__INCLUDED_)
#define _DB_HXX__0E7FBA34_4D26_11d1_96E7_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef sccs 
static char SccsId[] = "IRISWIN: %W%	%E%";
#endif

#include <CSRectGeom.h>
#include <ospace/std/set>

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

/////////////////////////////////////////////////////////////////////////////
// Forward references
class CIdTree;

#if defined(_USE_LEGACY_CODE)
class PBD_Data;
class GeoObjekt;
class Punkt;
class ObjContainer;
class ObjFeld;
#endif // defined(_USE_LEGACY_CODE)

/////////////////////////////////////////////////////////////////////////////
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

class DBTemplate 
{
protected:
	char *_DBName;	// DB-Name
	char *_UserName;
	HPROJECT _DBDesc;	// DB-Deskriptor nach öffnen

	bool _ReadOnlyFlag;	
	bool m_fTemp;		// temporäres Projekt, bei schließen löschen
	bool m_fIsDirty;	// wurde modifiziert
	bool m_fIsCopy;		// ist Kopie der OriginalDatei

// private Memberfunktionen
virtual DBTyp isA (void) = 0;	// pure virtual function

protected:
// Konstruktoren (können nicht direkt gerufen werden)
_TRIAS02_ENTRY DBTemplate (void);
_TRIAS02_ENTRY DBTemplate (const char *DBName);
_TRIAS02_ENTRY DBTemplate (const DBTemplate &DB);

public:
// Memberfunktionen
	void operator =(const DBTemplate &);

#if defined(_USE_LEGACY_CODE)
// Datenbasis - Arbeit
_TRIAS02_ENTRY virtual ErrCode Open (char *UserName, char *PassWord, DWORD dwMode);	// Eröffnen der DB
_TRIAS02_ENTRY virtual ErrCode Open (LPSTORAGE);		// Eröffnen der DB
_TRIAS02_ENTRY virtual ErrCode SetAccess (long);		// ZugriffsMode setzen
_TRIAS02_ENTRY virtual ErrCode RestoreAccess (long);	// Zugriffsmode wieder rücksetzen
_TRIAS02_ENTRY long LastRec (short);					// letzter existierender Satz in Datei
_TRIAS02_ENTRY virtual ErrCode Flush (BOOL fCommit = true);		// alles wegschreiben

	ErrCode Restore (void);		// alles verwerfen
#endif // _USE_LEGACY_CODE

_TRIAS02_ENTRY virtual ErrCode Close (BOOL fCommit = true);	// Schließen der DB
_TRIAS02_ENTRY virtual DBTemplate * Activate (HPROJECT *phPr = NULL);	// DB aktivieren

_TRIAS02_ENTRY ErrCode BeginTransaction (void);			// Transaktion starten
_TRIAS02_ENTRY ErrCode BreakTransaction (void);			// Transaktion abbrechen
	ErrCode EndTransaction (void) { return BeginTransaction(); }	// Transaktion abschließen

_TRIAS02_ENTRY virtual void SetDirty (BOOL fDirty = true);
_TRIAS02_ENTRY virtual BOOL isDirty (void);
_TRIAS02_ENTRY virtual ~DBTemplate (void);

_TRIAS02_ENTRY void SetDBName (char *);				// DBNamen setzen
_TRIAS02_ENTRY virtual BOOL GetTempDBName (char *);
_TRIAS02_ENTRY char * GetDBPath (char *Buffer, short BuffLen);
_TRIAS02_ENTRY virtual long GetDBVersion (void);
_TRIAS02_ENTRY BOOL IsComDB (void);

	BOOL isOpened (void) { return ((long)_DBDesc > 0) ? TRUE : FALSE; }
_TRIAS02_ENTRY virtual HRESULT GetProjectStorage (LPSTORAGE *ppIStorage)
		{ return ::GetProjectStorage (DBDesc(), ppIStorage); }

	BOOL GetTempMode (void) { return m_fTemp; }
	void SetTempMode (BOOL fTemp) { m_fTemp = fTemp; }

	BOOL SetCopy (BOOL fIsCopy)
		{ BOOL fOldMode = m_fIsCopy; m_fIsCopy = fIsCopy; return fOldMode; }
	BOOL isCopy (void) { return m_fIsCopy; }

	BOOL SetROMode (BOOL fMode) 
		{ BOOL fOldMode = _ReadOnlyFlag; _ReadOnlyFlag = fMode; return fOldMode; }
	BOOL GetROMode (void) { return _ReadOnlyFlag; }

	LPCSTR GetDBName (void) { return _DBName; }						// DBNamen liefern
	LPCSTR GetUserName (void) { return _UserName ? _UserName : ""; } // UserName liefern

	HPROJECT DBDesc (void) { return _DBDesc; }				// DB-Descriptor
//	virtual BOOL IsTRiASDBBased() { return FALSE; }
	BOOL IsTRiASDBBased() { return TRUE; }
};

#if defined(_DEBUG)
class DBDict;
class Protocol;
#endif // _DEBUG

typedef struct tagENUMRELATIONOBJS ENUMRELATIONOBJS;

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASConnection);

class GeoDB : 
	public DBTemplate 
{
private:
	WTRiASConnection m_Conn;	// Connection zu einer TRiASDB - Database
	W_DGMRectangleGeometry m_DBCont;	// Datenbank-Container

	bool m_fInz;				// DB ist vollständig verschnitten
	bool m_fPosTextAtBaseLine;	// Texte an Basisline positionieren
	bool m_fIsCompatible16;		// 16-Bit Kompatibilität gewährleisten
	bool m_fCanTexts;			// Textobjekte werden unterstützt

	INT_PTR _lTextObjMCode;		// MerkmalsCode an dem Texte der Textobjekte hängen
	int m_iIdentBase;			// IdentifikatorZahlenbasis

#if defined(_USE_LEGACY_CODE)
	ObjContainer *_pDBCont;		// DBContainer
	int m_iMkBase;				// Zahlenbasis der MerkmalsCodes
#endif // _USE_LEGACY_CODE

protected:
	ErrCode GetRigObj (long ONr, int *num, long **Feld);
	long GetUniqueLong (unsigned int resID, long lFirstCode);

public:
// Konstruktoren
	GeoDB (void) 
		{
			_DBDesc = (HPROJECT)-2; 
			m_fInz = false;
			m_fPosTextAtBaseLine = false;
			m_fIsCompatible16 = false;
			m_fCanTexts = true;
			_lTextObjMCode = 0L;
			m_iIdentBase = 16;
#if defined(_USE_LEGACY_CODE)
			_pDBCont = NULL; 
			m_iMkBase = 10;
#endif // _USE_LEGACY_CODE
		}
	GeoDB (LPCSTR pcDBName) 
		: DBTemplate (pcDBName) 
		{
			_DBDesc = (HPROJECT)-2; 
			m_fInz = false;
			m_fPosTextAtBaseLine = false;
			m_fIsCompatible16 = false;
			m_fCanTexts = true;
			_lTextObjMCode = 0L;
			m_iIdentBase = 16;
#if defined(_USE_LEGACY_CODE)
			_pDBCont = NULL; 
			m_iMkBase = 10;
#endif // _USE_LEGACY_CODE
		}

// Memberfunktionen
#if defined(_USE_LEGACY_CODE)
_TRIAS02_ENTRY ErrCode Open (char *, char *, DWORD);
_TRIAS02_ENTRY ErrCode Open (LPSTORAGE);	// Eröffnen der DB
_TRIAS02_ENTRY ErrCode Flush (BOOL fCommit = true);		// alles wegschreiben

_TRIAS02_ENTRY ErrCode IdFilter (ObjFeld &, CIdTree &);		// Id's filtern
_TRIAS02_ENTRY ErrCode IdFilter (ObjFeld &, char *);
_TRIAS02_ENTRY ErrCode IdFilterNew (ObjFeld &, char *);
_TRIAS02_ENTRY ErrCode IdFilterAll (ObjFeld &);

// Geometriebehandlung
_TRIAS02_ENTRY HRESULT GetGI (long ObjNr, GeoObjekt **, ObjContainer * = NULL);  // Geometrie aus DB lesen
_TRIAS02_ENTRY ErrCode GIWindow (ObjContainer &, ObjFeld &, BOOL Flag);	// Objekte in Window finden
_TRIAS02_ENTRY HRESULT DelGI (long);			// Geometrie in DB löschen
_TRIAS02_ENTRY HRESULT PutGI (GeoObjekt *);		// Geometrie neu schreiben
_TRIAS02_ENTRY HRESULT OverlayGI (long, GeoObjekt *);	// Geometrie überlagern
_TRIAS02_ENTRY ErrCode ModGIPunkt (long ONr, Punkt &Pt);  	// neue PunktKoordinate

_TRIAS02_ENTRY ErrCode RelInfo (long ONr, ObjFeld &);		// Relationen lesen
_TRIAS02_ENTRY ErrCode RigInfo (long ONr, ObjFeld &);		// Topologie lesen
_TRIAS02_ENTRY ErrCode FindText (long Code, int Mode, char *SText, ObjFeld &);
#endif // _USE_LEGACY_CODE

_TRIAS02_ENTRY ErrCode Close (BOOL fCommit = true);
_TRIAS02_ENTRY long CreateObjTemplate (long lIdent, short iTyp);

_TRIAS02_ENTRY ErrCode FindId (long Id, long *FlexNum, short *pOTyp = NULL, long *plObjCnts = NULL);

#if defined(_USE_LEGACY_CODE)
_TRIAS02_ENTRY ErrCode ReadText (long ONr, char * &pText, TextObjTyp &);// Text von OT_TEXT
_TRIAS02_ENTRY ErrCode WriteText (long ONr, char *pText, BOOL fIndObjProp);
_TRIAS02_ENTRY ErrCode DelText (long ONr);
#endif // defined(_USE_LEGACY_CODE)

_TRIAS02_ENTRY HRESULT SearchObjects (BSTR bstrCommand, ITRiASObjects *pIObjs, SAFEARRAY *pParams);
_TRIAS02_ENTRY HRESULT SearchObjectsSeparate (BSTR bstrCommand, ITRiASObjects *pIObjs, SAFEARRAY *pParams);

_TRIAS02_ENTRY BOOL EnumIdents (BOOL (*pFcn)(long, BOOL, void *), void *pData);
_TRIAS02_ENTRY BOOL EnumIdentsEx (BOOL (*pFcn)(long, DWORD, void *), void *pData, DWORD);
_TRIAS02_ENTRY BOOL EnumIdentObjects (long, BOOL (*pFcn)(long, BOOL, void *), void *);
_TRIAS02_ENTRY BOOL EnumIdentObjectsEx (long, BOOL (*pFcn)(long, DWORD, void *), void *, DWORD dwData);
_TRIAS02_ENTRY HRESULT GetObjectType (LONG lONr, int *piOTyp);

_TRIAS02_ENTRY HRESULT GetFeature (INT_PTR hObjs, LPCSTR pcName, ITRiASFeature **ppIFeat);
_TRIAS02_ENTRY HRESULT CreateFeature (INT_PTR hObjs, VARIANT vMCodeOrName, INT_PTR *plMCode, ITRiASFeature **ppIFeat = NULL, ITRiASDatabase *pIDB = NULL);
_TRIAS02_ENTRY BOOL EnumAllFeatures (ENUMNOKEYLONGPROC pFcn, void *pData);
_TRIAS02_ENTRY BOOL EnumAllFeaturesEx (ENUMNOKEYLONGEXPROC pFcn, FEATURETYPE rgTypeToEnum, void *pData, bool fListAllClasses = false);
_TRIAS02_ENTRY BOOL EnumAllFeaturesObjsEx (ITRiASObjects *pIObjs, ENUMNOKEYLONGEXPROC pFcn, FEATURETYPE rgTypeToEnum, void *pData, set<HFEATURE, less<HFEATURE> > *pMCodes = NULL);
_TRIAS02_ENTRY INT_PTR MapMCodeToHandle (INT_PTR lMCode, BOOL fCreate = FALSE, BOOL *pfCreated = NULL, INT_PTR lIdent = NULL);
_TRIAS02_ENTRY INT_PTR MapHandleToMCode (INT_PTR lHandle);

_TRIAS02_ENTRY BOOL EnumRCodes (BOOL (*pFcn)(long, BOOL, void *), void *pData);
_TRIAS02_ENTRY BOOL EnumRelationObjs (ENUMRELATIONOBJS *pERO);

_TRIAS02_ENTRY DBTyp isA (void);
_TRIAS02_ENTRY BOOL ReReadHeader (void);

_TRIAS02_ENTRY HRESULT DeleteObject (INT_PTR lONr);
_TRIAS02_ENTRY HRESULT ForceReLoad (RELOADDATABASE rgWhat = RELOADDATABASE_All);

// sonstige Member
_TRIAS02_ENTRY long GetUniqueICode (BOOL fSystem = FALSE);
_TRIAS02_ENTRY long GetUniqueMCode (BOOL fSystem = FALSE);
_TRIAS02_ENTRY long GetUniqueRCode (void);
_TRIAS02_ENTRY long GetUniqueTempONr (void);
#if defined(_USE_LEGACY_CODE)
_TRIAS02_ENTRY ObjContainer DBCont (BOOL fReRead = false);	// dbcodb
_TRIAS02_ENTRY BOOL EnumHdrData (BOOL (*pFcn)(char *, BOOL, void *), void *pData);
_TRIAS02_ENTRY ErrCode GetIdentObjectCounts (LONG lIdent, long *plObjCnts);
_TRIAS02_ENTRY BOOL EnumObjectsIdl (long lIdent, long lNext, BOOL (*pFcn)(long, BOOL, void *), void *pData);
_TRIAS02_ENTRY BOOL EnumObjectsIdlEx (long lIdent, long lNext, BOOL fVerifyType, BOOL (*pFcn)(long, DWORD, void *), void *pData, DWORD dwData);
#endif // _USE_LEGACY_CODE
_TRIAS02_ENTRY HRESULT DBCont (_DGMRectangleGeometry **ppIRect, BOOL fReRead = false);	// dbcodb
_TRIAS02_ENTRY HRESULT DBMaxCont (_DGMRectangleGeometry **ppIRect);	// max. mögliches KoordinatenRechteck

_TRIAS02_ENTRY BOOL VerifyGI (GeoObjekt *pGO);
_TRIAS02_ENTRY void SetDirty (BOOL fDirty = true);
_TRIAS02_ENTRY HRESULT GetProjectStorage (LPSTORAGE *);
_TRIAS02_ENTRY HRESULT GetDataSourceDescription (char *pDesc, int iLen = _MAX_PATH);
_TRIAS02_ENTRY HRESULT GetDataSourceName (char *pName, int iLen = _MAX_PATH);

///////////////////////////////////////////////////////////////////////////////
// ProjektHeaderFunktionen
_TRIAS02_ENTRY ErrCode GetHeaderEntry (GEODBHDRENTRY *pHE);
_TRIAS02_ENTRY ErrCode SetHeaderEntry (GEODBHDRENTRY *pHE);
_TRIAS02_ENTRY ErrCode DeleteHeaderEntry (GEODBHDRENTRY *pHE);
_TRIAS02_ENTRY BOOL EnumHeaderData (ENUMNOKEYCALLBACK pFcn, void *pData);

///////////////////////////////////////////////////////////////////////////////
// MetaDatenZugriff
_TRIAS02_ENTRY ErrCode ModPBDDataIdent (PBDDATA *pData);
_TRIAS02_ENTRY ErrCode DelPBDDataIdent (PBDDATA *pData);
_TRIAS02_ENTRY BOOL EnumPBDDataIdent (ENUMLONGKEYPROC pFcn, void *pData);
_TRIAS02_ENTRY ErrCode ModPBDDataMerkmal (PBDDATA *pData);
_TRIAS02_ENTRY ErrCode DelPBDDataMerkmal (PBDDATA *pData);
_TRIAS02_ENTRY BOOL EnumPBDDataMerkmal (ENUMLONGKEYPROC pFcn, void *pData);

// Statistische Funktionen
_TRIAS02_ENTRY LONG CountObjects (void);
_TRIAS02_ENTRY LONG CountClasses (void);
#if defined(_USE_LEGACY_CODE)
_TRIAS02_ENTRY LONG CountViews (void);
#endif // _USE_LEGACY_CODE

_TRIAS02_ENTRY HRESULT GetObjectGUID (LONG lONr, struct _GUID *pGuid);
_TRIAS02_ENTRY HRESULT SetObjectGUID (LONG lONr, const _GUID &rGuid);
_TRIAS02_ENTRY HRESULT FindObjectFromGUID (const _GUID &rGuid, LONG *plONr);
#if defined(_FORCE_LEGACY_CODE)
_TRIAS02_ENTRY HRESULT GetObjectGUIDFeature (LONG lONr, LONG lMCode, _GUID *pGuid);
_TRIAS02_ENTRY HRESULT SetObjectGUIDFeature (LONG lONr, const _GUID &rGuid, LONG lMCode);
_TRIAS02_ENTRY HRESULT FindObjectFromGUIDFeature (const _GUID &rGuid, LONG lMCode, LONG *plONr);
#endif // _FORCE_LEGACY_CODE

#if defined(_DEBUG)
///////////////////////////////////////////////////////////////////////////////
// Konsistenztest 
	ErrCode TestObjekt (DBDict &, Protocol &, long ONr, short toDo = 0);
	ErrCode DelObjekt (DBDict &, Protocol &, long ONr, short toDo = 0);
#endif // _DEBUG

	INT_PTR TOMCode (void) { return _lTextObjMCode; }
	int GetIdentBase() { return m_iIdentBase; }
#if defined(_USE_LEGACY_CODE)
	int GetMkBase() { return m_iMkBase; }
#endif // _USE_LEGACY_CODE

	BOOL GetPosAtBaseLine() { return m_fPosTextAtBaseLine; }
	BOOL GetCompatibleMode() { return m_fIsCompatible16; }
	BOOL GetInzMode() { return m_fInz; }
	BOOL GetCanTexts() { return m_fCanTexts; }

_TRIAS02_ENTRY HRESULT GetObjectsDef (ULONG ulIdent, VARIANT vItem, VARIANT_BOOL fCreate, BSTR bstrType, ITRiASObjects **ppIObjs);

///////////////////////////////////////////////////////////////////////////////
// TRiASDB Spezifika
_TRIAS02_ENTRY HRESULT AttachConnection (ITRiASConnection *pIConn, ITRiASConnection **ppIConn = NULL);
_TRIAS02_ENTRY HRESULT GetConnection (ITRiASConnection **ppIConn);
	HRESULT DetachConnection (ITRiASConnection **ppIConn = NULL)
		{ return AttachConnection (NULL, ppIConn); }

//	BOOL IsTRiASDBBased() { return !!m_Conn ? TRUE : FALSE; }

_TRIAS02_ENTRY BOOL GetTempDBName (char *);
_TRIAS02_ENTRY BOOL isDirty (void);
_TRIAS02_ENTRY BOOL IsTRiASDataSource (void);
_TRIAS02_ENTRY BOOL IsGDODataSource (void);
_TRIAS02_ENTRY long GetDBVersion (void);
_TRIAS02_ENTRY BOOL GetSchemaUpdatable();

// Destruktor
		~GeoDB (void) 
		{ 
#if defined(_USE_LEGACY_CODE)
			DELETE_OBJ(_pDBCont); 
#endif // _USE_LEGACY_CODE
			m_DBCont.Assign(NULL);
		}
};

#if defined(_USE_LEGACY_CODE)
///////////////////////////////////////////////////////////////////////////////
// Pbd
typedef struct tagPBDDATA PBDDATA;
class CPBDIdents;
class CPBDMCodes;
class CPBDRCodes;

class PBD_DB : 
	public DBTemplate 
{
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
_TRIAS02_ENTRY DBTyp isA (void);
_TRIAS02_ENTRY BOOL InitPBD (GeoDB &, char *, BOOL = false);	// Initialisieren anhand der GeoDB
_TRIAS02_ENTRY BOOL InitComPbd (GeoDB &);	// Initialisieren anhand der GeoDB
_TRIAS02_ENTRY void EveryDelete (void);		// Bäume freigeben
	
_TRIAS02_ENTRY ErrCode GetPBDData (PBDDATA *);
_TRIAS02_ENTRY ErrCode ModPBDData (PBDDATA *);
_TRIAS02_ENTRY ErrCode DelPBDData (PBDDATA *);

_TRIAS02_ENTRY BOOL EnumPBDData (long, BOOL (*)(long, BOOL, void *), void *);

_TRIAS02_ENTRY ErrCode Open (LPSTORAGE);	// Eröffnen der DB
_TRIAS02_ENTRY DBTemplate * Activate (HPROJECT *phPr = NULL);	// PBD aktivieren
_TRIAS02_ENTRY DBTemplate * ActivateCOMPbd (void);	// COM-PBD aktivieren
_TRIAS02_ENTRY ErrCode Flush (BOOL fCommit = true);		// alles wegschreiben
	
_TRIAS02_ENTRY BOOL UpdateIdents (long lIdent = -1);	// CPBDIdents aktualisieren
_TRIAS02_ENTRY BOOL UpdateMCodes (long lIdent = -1);	// CPBDMCodes aktualisieren
_TRIAS02_ENTRY BOOL UpdateRCodes (long lIdent = -1);	// CPBDRCodes aktualisieren

	BOOL FillFromTree (PBD_Data *pDataToFill);
	BOOL AddToTree (PBD_Data *pNewData);

_TRIAS02_ENTRY BOOL AddToTempTree (PBD_Data &rData);
_TRIAS02_ENTRY BOOL RemoveFromTempTree (PBD_Data &rData);
_TRIAS02_ENTRY BOOL FillFromTempTree (PBD_Data &rData);
_TRIAS02_ENTRY void ReleasePBDTempTree (void);

_TRIAS02_ENTRY void SetDirty (BOOL fDirty = true);

	void SetCOMFlag (BOOL fFlag) { m_fCOMPbd = fFlag ? true : false; }
	BOOL GetCOMFlag (void) { return m_fCOMPbd; }

// Zugriff auf rückverweis auf zugehörige GeoDB
	void SetGeoDB (GeoDB *pDB) { m_pGeoDB = pDB; }
	GeoDB *GetGeoDB (void) { return m_pGeoDB; }
};
#endif // _USE_LEGACY_CODE

///////////////////////////////////////////////////////////////////////////////
// WrapperKlasse für das Aktivieren einer Datenbasis 

inline
bool IsValidTRiASProjectHandle(HPROJECT hPr)
{
	return (0 < (long)hPr && (long)hPr <= MAXDB) ? true : false;
}

#if defined(_FORCE_LEGACY_CODE)
extern _TRIAS02_ENTRY DBTemplate *actDB;	// derzeit aktivierte DB

class CActDB {
private:
	DBTemplate *m_pDB;	// alte DB
	DBTemplate &m_rDB;	// aktuelle DB
	HPROJECT m_hPrOld;

public:
		CActDB (DBTemplate &rDB) 
			: m_rDB(rDB), m_pDB(rDB.Activate (&m_hPrOld)) 
		{}

		~CActDB (void) 
		{
			if (NULL != m_pDB) 
				m_pDB -> Activate(); 
			else { 
				if (NULL != m_hPrOld && IsValidTRiASProjectHandle(m_hPrOld)) 
					z_activate (m_hPrOld); 
				actDB = NULL; 
			}
		}

	void ReActivate (void) 
	{
		m_rDB.Activate(); 
	}
	DBTemplate &GetOldDB (void) { return *m_pDB; }
	BOOL operator! (void)
	{
		return NULL == m_pDB && NULL == m_hPrOld; 
	}
};
#else
class CActDB {
private:
	DBTemplate &m_rDB;

public:
		CActDB (DBTemplate &rDB) : m_rDB(rDB) {}
		~CActDB (void) {}

	void ReActivate (void) {}
	BOOL operator! (void) { return FALSE; }
	DBTemplate &GetOldDB (void) { return m_rDB; }
};
#endif // _FORCE_LEGACY_CODE

#endif // !defined(_DB_HXX__0E7FBA34_4D26_11d1_96E7_00A024D6F582__INCLUDED_)
