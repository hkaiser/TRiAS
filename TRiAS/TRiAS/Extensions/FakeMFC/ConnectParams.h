// ConnectParams.h : header file
//

#if !defined(_CONNECTPARAMS_H)
#define _CONNECTPARAMS_H

/////////////////////////////////////////////////////////////////////////////
// Modi für Open/New PropertySheet
enum PROJECTOPENMODE {
	PROJECTOPENMODE_Unknown = 0,
	PROJECTOPENMODE_OpenExistend = 1,
	PROJECTOPENMODE_OpenMRU = 2,
	PROJECTOPENMODE_CreateNew = 3,
};

// Modi für letzte Page (What to do else)
enum CREATEMODE {
	CREATEMODE_Unknown = 0,
	CREATEMODE_ImportData = 1,
	CREATEMODE_EditData = 2,
};

// Modi für DatasourceOpen/New
enum DATASOURCEMODE {
	DATASOURCEMODE_Unknown = 0,
	DATASOURCEMODE_OpenExistend = 1,
	DATASOURCEMODE_CreateNew = 2,
};

///////////////////////////////////////////////////////////////////////////////
// Parameter der einzustellenden Connection
class CDataServerItem;

class CConnectParams
{
public:
	BOOL m_fIsReadWrite;
	BOOL m_fNameIsFile;
	BOOL m_fNameIsDir;
	BOOL m_fNameIsSubStorage;
	BOOL m_fMultipleFiles;
	BOOL m_fNeedsCoordSysWizExisting;
	BOOL m_fNeedsCoordSysWizNew;

	CString m_strProgID;	// ProgID der DataBaseClass im OriginalSystem
	CString m_strExtProgID;	// ProgID eines OpenWizPages Objektes
	CString m_strConnect;	// evtl. zusätzliche Info's für ConnectString
	CString m_strFilter;	// FilterString für 'Datei öffnen'
	CString m_strDefExt;	// Standard Dateierweiterung
	CString m_strLongName;	// Langbezeichner des DatenServers
	CString m_strShortName;	// Kurzbezeichner des DatenServers
	CString m_strFileDesc;	// Bezeichner des Dateiformates
	CString m_strTempName;	// Temporäre Datenquelle möglich, das ist der DefaultName
	CString m_strLastDirUsed;	// beim letzten mal benutztes Verzeichnis
	CString m_strCoordsKey;	// RegKey des zu initialisierenden Koordinatensystems (optional)
	CString m_strTcfName;	// Name der zu verwendenden Koordinatensystem-Datei (optional)
		
	CLSID m_ClsId;			// ClsId der TRiASDataBaseClass

	LONG m_lInstances;		// Anzahl der gleichzeitig instantiierbaren Datenquellen

	CConnectParams &operator= (CDataServerItem const &rhs);

	bool GetDbmsMode() { return !m_fNameIsFile && !m_fNameIsDir; }
	bool GetNeedsCoordSys(DATASOURCEMODE rgMode)
	{
		return (DATASOURCEMODE_CreateNew == rgMode) ?
			m_fNeedsCoordSysWizNew : m_fNeedsCoordSysWizExisting;
	}
	bool GetNeedsCoordSysExisting()
	{
		return m_fNeedsCoordSysWizExisting;
	}
};

// Inizies für Bitmapstrip IDB_DATASERVER
//#define IMG_GEOMEDIA	2
//#define IMG_TRIAS130	3
//#define IMG_TRIAS200	4
#define IMG_GENERAL		5
//#define IMG_UNKNOWN		6

// in diesem Set werden die Dateinamen aus einem MultiSelDlg gespeichert
typedef set<os_string, less<os_string> > CFiles;

/////////////////////////////////////////////////////////////////////////////
// DataItem, welches in Tree hängt

class CDataServerItem
	: public CConnectParams
{
public:
	CDataServerItem() {}
	~CDataServerItem() {}

	CString GetDesc() { return m_strLongName; }
};

inline
CConnectParams &CConnectParams::operator= (CDataServerItem const &rhs)
{
	m_ClsId = rhs.m_ClsId;

	m_fIsReadWrite = rhs.m_fIsReadWrite;
	m_fNameIsFile = rhs.m_fNameIsFile;
	m_fNameIsDir = rhs.m_fNameIsDir;
	m_fNameIsSubStorage = rhs.m_fNameIsSubStorage;
	m_fMultipleFiles = rhs.m_fMultipleFiles;
	m_fNeedsCoordSysWizNew = rhs.m_fNeedsCoordSysWizNew;
	m_fNeedsCoordSysWizExisting = rhs.m_fNeedsCoordSysWizExisting;

	m_strProgID = rhs.m_strProgID;
	m_strExtProgID = rhs.m_strExtProgID;
	m_strConnect = rhs.m_strConnect;
	m_strFilter = rhs.m_strFilter;
	m_strDefExt = rhs.m_strDefExt;
	m_strLongName = rhs.m_strLongName;
	m_strShortName = rhs.m_strShortName;
	m_strFileDesc = rhs.m_strFileDesc;
	m_strTempName = rhs.m_strTempName;
	m_strLastDirUsed = rhs.m_strLastDirUsed;
//		m_strCoordsKey = rhs.m_strCoordsKey;		// nicht kopieren!
//		m_strTcfName = rhs.m_strTcfName;

	m_lInstances = rhs.m_lInstances;

	return *this;
}

#endif // _CONNECTPARAMS_H
