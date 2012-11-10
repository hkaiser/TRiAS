// Cfg.cpp: Implementierung der Klasse CCfg.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "resource.h"
#include "CXSTRING.H"
#include "CfgDb.h"
#include "Cfg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BOOL UpdateEDBSRegistry(BOOL fRegister)
{
	CRegKey regTRiAS;
	CRegKey regEDBS;
	char  straConfig[MAX_PATH];
	DWORD cbConfig;
	CString strConfigPath;
	CString strRegKey(TRiAS_REGKEY);

	if( fRegister ) {
		regEDBS.Create(HKEY_CURRENT_USER, strRegKey + "Extensions\\TRiAS.EDBSALK.1\\ImportFormat");
		regEDBS.SetValue("{73645434-AED5-11D3-8E7B-00105AF354F9}","ConfigPage");
		regEDBS.Close();

		regEDBS.Create(HKEY_CURRENT_USER, strRegKey + "Extensions\\TRiAS.EDBSALK.1\\Config");
		cbConfig = MAX_PATH;
		if( ERROR_SUCCESS != regEDBS.QueryValue(straConfig, "ConfigPath", &cbConfig ) ) {
			regTRiAS.Open(HKEY_CURRENT_USER, strRegKey + "Directories");
			cbConfig = MAX_PATH;
			if( ERROR_SUCCESS == regTRiAS.QueryValue(straConfig, "Config", &cbConfig ) ) {
				strConfigPath = straConfig;
				strConfigPath += "\\EDBS\\";
				regTRiAS.Close();
			}
			else {
				regTRiAS.Close();
#if _TRiAS_VER < 0x300
				regTRiAS.Open(HKEY_CLASSES_ROOT,".ris\\ShellNew", KEY_READ);
#else
				regTRiAS.Open(HKEY_CLASSES_ROOT,".riw\\ShellNew", KEY_READ);
#endif
				cbConfig = MAX_PATH;
				if (ERROR_SUCCESS == regTRiAS.QueryValue(straConfig, "command", &cbConfig)) {
					strConfigPath = straConfig;
                    for (int i = 0; i < 1; ++i) {
					    while (strConfigPath.GetLength() > 0 && strConfigPath.Right(1) != "\\")
						    strConfigPath = strConfigPath.Left(strConfigPath.GetLength() - 1);
                    }
					strConfigPath = strConfigPath + "EDBS\\";
				}
				regTRiAS.Close();
			}
			regEDBS.SetValue(strConfigPath, "ConfigPath");
		}
		cbConfig = MAX_PATH;
		if( ERROR_SUCCESS != regEDBS.QueryValue(straConfig,"ConfigFile", &cbConfig ) ) {
			regEDBS.SetValue("Default","ConfigFile");
		}
		if( ERROR_SUCCESS != regEDBS.QueryValue(cbConfig,"ConfigBase") ) {
			regEDBS.SetValue(0xFFFFFFFD,"ConfigBase");
		}
		regEDBS.Close();

	}
	else {
		if( ERROR_SUCCESS == regEDBS.Open(HKEY_CURRENT_USER,strRegKey + "Extensions\\TRiAS.EDBSALK.1\\ImportFormat") ) {
			regEDBS.DeleteValue("ConfigPage");
			regEDBS.Close();
		}
	
//		if( ERROR_SUCCESS == regEDBS.Open(HKEY_CURRENT_USER,strRegKey + "Extensions") ) {
//			regEDBS.DeleteSubKey("TRiAS.EDBS");
//			regEDBS.Close();
//		}
	}

	return true;	// alles ok
}

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CCfg::CCfg()
{
	char  straConfig[MAX_PATH];
	DWORD cbConfig;

	m_tEnabled = false;
	CRegKey regODBC;

	regODBC.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\ODBC\\ODBCINST.INI\\ODBC Drivers");
	cbConfig = MAX_PATH;
	if( ERROR_SUCCESS == regODBC.QueryValue(straConfig,"Microsoft Access-Treiber (*.mdb)", &cbConfig ) ) {
		m_strAccessDriverName = ";DRIVER={Microsoft Access-Treiber (*.mdb)};DSN=''";
	}
	else if( ERROR_SUCCESS == regODBC.QueryValue(straConfig,"Microsoft Access Driver (*.mdb)", &cbConfig ) ) {
		m_strAccessDriverName = ";DRIVER={Microsoft Access Driver (*.mdb)};DSN=''";
	}
	else {
		m_strAccessDriverName.Empty();
	}
}

CCfg::~CCfg()
{
	POSITION	pos;
	CString		key;
	CCfgDb		*pCfgDb;

	if( m_dbCfg.IsOpen() )
		m_dbCfg.Close();

	for ( pos = m_CfgDbs.GetStartPosition(); pos != NULL; ) {
		m_CfgDbs.GetNextAssoc( pos, key, (CObject*&)pCfgDb );
		delete pCfgDb;
	}
	m_CfgDbs.RemoveAll();

}

void CCfg::Load()
{
	CRegKey regEDBS;
	char  straConfig[MAX_PATH];
	DWORD cbConfig;
	CString strConfigPath;
	CString strBuffer;
	WIN32_FIND_DATA FileData;   // Data structure describes the file found
	HANDLE hSearch;             // Search handle returned by FindFirstFile
	CString strRegKey(TRiAS_REGKEY);

	regEDBS.Open(HKEY_CURRENT_USER,strRegKey + "Config");
	regEDBS.QueryValue( m_dwSystemAdministration,"SystemAdministration" );
	cbConfig = MAX_PATH;
	if( ERROR_SUCCESS == regEDBS.QueryValue(straConfig, "TRiASName", &cbConfig ) )
		m_strTRiASName = straConfig;
	else
		m_strTRiASName = "TRiAS®";
	regEDBS.Close();

	regEDBS.Open(HKEY_CURRENT_USER,strRegKey + "Extensions\\TRiAS.EDBSALK.1\\Config");

	if( ERROR_SUCCESS != regEDBS.QueryValue( m_dwReportBase, "ReportBase" ) )
		m_dwReportBase = 0;

	if( ERROR_SUCCESS != regEDBS.QueryValue( m_dwConfigBase, "ConfigBase" ) )
		m_dwConfigBase = 0xFFFFFFFD;

	m_tDefaultObjectMapping = (0 != (m_dwConfigBase & EDBSCFG_DEFAULTOBJECTMAPPING));
	m_tOverwriteRules = (0 != (m_dwConfigBase & EDBSCFG_OVERWRITERULES));

	m_tImportAreas = (0 != (m_dwConfigBase & EDBSCFG_IMPORTAREAS));
	m_tImportLines = (0 != (m_dwConfigBase & EDBSCFG_IMPORTLINES));
	m_tImportPoints = (0 != (m_dwConfigBase & EDBSCFG_IMPORTPOINTS));
	m_tImportText = (0 != (m_dwConfigBase & EDBSCFG_IMPORTTEXT));
	
	m_tCreateBIgeom = (0 != (m_dwConfigBase & EDBSCFG_CREATEBIGEOM));
	m_tCreateBItext = (0 != (m_dwConfigBase & EDBSCFG_CREATEBITEXT));

	m_tImportAttr = (0 != (m_dwConfigBase & EDBSCFG_IMPORTATTR));
	m_tCreateEDBSattr = (0 != (m_dwConfigBase & EDBSCFG_CREATEEDBSATTR));
	m_tCreateBIattr = (0 != (m_dwConfigBase & EDBSCFG_CREATEBIATTR));
	
	m_tImportKSIG = (0 != (m_dwConfigBase & EDBSCFG_IMPORTKSIG));
	m_tImportVPKT = (0 != (m_dwConfigBase & EDBSCFG_IMPORTVPKT));

	m_tCreateAttributeDateiname = (0 != (m_dwConfigBase & EDBSCFG_CREATEATTRDATEINAME));
	m_tCreateAttributeFolie = (0 != (m_dwConfigBase & EDBSCFG_CREATEATTRFOLIE));
	m_tCreateAttributeObjektart = (0 != (m_dwConfigBase & EDBSCFG_CREATEATTROBJEKTART));
	m_tCreateAttributeObjektnummer = (0 != (m_dwConfigBase & EDBSCFG_CREATEATTROBJEKTNUMMER));
	m_tCreateAttributeObjektteilnummer = (0 != (m_dwConfigBase & EDBSCFG_CREATEATTROBJEKTTEILNUMMER));
	m_tCreateAttributeObjektteilnummerK = (0 != (m_dwConfigBase & EDBSCFG_CREATEATTROBJEKTTEILNUMMERK));
	m_tCreateAttributeAktualitaet = (0 != (m_dwConfigBase & EDBSCFG_CREATEATTRAKTUALITAET));
	m_tCreateAttributeRegeln = (0 != (m_dwConfigBase & EDBSCFG_CREATEATTRREGELN));

	cbConfig = MAX_PATH;
	if( ERROR_SUCCESS == regEDBS.QueryValue(straConfig,"ConfigFile", &cbConfig ) ) {
		m_strConfigFile = straConfig;
		if( m_strConfigFile == "Default" ) 
			m_tDefaultObjectMapping = true;
		cbConfig = MAX_PATH;
		if( ERROR_SUCCESS == regEDBS.QueryValue(straConfig,"ConfigPath", &cbConfig ) )
			m_strConfigPath = straConfig;
	}

	cbConfig = MAX_PATH;
	if( ERROR_SUCCESS == regEDBS.QueryValue(straConfig,"ObjectClassesTRiAS", &cbConfig ) )
		m_strObjectClassesTRiAS = straConfig;
	else
		m_strObjectClassesTRiAS = "D";

	cbConfig = MAX_PATH;
	if( ERROR_SUCCESS == regEDBS.QueryValue(straConfig,"ObjectAttributesTRiAS", &cbConfig ) )
		m_strObjectAttributesTRiAS = straConfig;
	else
		m_strObjectAttributesTRiAS = "49";

	regEDBS.Close();

// ermitteln, ob Datenbanken im EDBS-Konfigurationsverteichnis vorhanden sind.

	hSearch = FindFirstFile (TEXT(m_strConfigPath + "*.mdb"), &FileData);
//	if( (hSearch != INVALID_HANDLE_VALUE) || (DEX_QueryMode() & QMSysAdmin) )
	if( (hSearch != INVALID_HANDLE_VALUE) || (m_dwSystemAdministration & QMSysAdmin) )
		m_tEnabled = true;
	FindClose (hSearch);
}

void CCfg::Save()
{
 CRegKey regEDBS;
 DWORD dwConfigBase;
 CString strRegKey(TRiAS_REGKEY);

	regEDBS.Open(HKEY_CURRENT_USER,strRegKey + "Extensions\\TRiAS.EDBSALK.1\\Config");

	regEDBS.SetValue( m_strConfigPath,"ConfigPath");
	regEDBS.SetValue( m_strConfigFile, "ConfigFile");

	regEDBS.QueryValue( dwConfigBase,"ConfigBase" );

	if( m_tDefaultObjectMapping )
		dwConfigBase |= EDBSCFG_DEFAULTOBJECTMAPPING;
	else
		dwConfigBase &= ~EDBSCFG_DEFAULTOBJECTMAPPING;
	if( m_tOverwriteRules )
		dwConfigBase |= EDBSCFG_OVERWRITERULES;
	else
		dwConfigBase &= ~EDBSCFG_OVERWRITERULES;
	if( m_tImportAreas )
		dwConfigBase |= EDBSCFG_IMPORTAREAS;
	else
		dwConfigBase &= ~EDBSCFG_IMPORTAREAS;
	if( m_tImportLines )
		dwConfigBase |= EDBSCFG_IMPORTLINES;
	else
		dwConfigBase &= ~EDBSCFG_IMPORTLINES;
	if( m_tImportPoints )
		dwConfigBase |= EDBSCFG_IMPORTPOINTS;
	else
		dwConfigBase &= ~EDBSCFG_IMPORTPOINTS;
	if( m_tImportText )
		dwConfigBase |= EDBSCFG_IMPORTTEXT;
	else
		dwConfigBase &= ~EDBSCFG_IMPORTTEXT;

	if( m_tCreateBIgeom )
		dwConfigBase |= EDBSCFG_CREATEBIGEOM;
	else
		dwConfigBase &= ~EDBSCFG_CREATEBIGEOM;
	if( m_tCreateBItext )
		dwConfigBase |= EDBSCFG_CREATEBITEXT;
	else
		dwConfigBase &= ~EDBSCFG_CREATEBITEXT;

	if( m_tImportKSIG )
		dwConfigBase |= EDBSCFG_IMPORTKSIG;
	else
		dwConfigBase &= ~EDBSCFG_IMPORTKSIG;
	if( m_tImportVPKT )
		dwConfigBase |= EDBSCFG_IMPORTVPKT;
	else
		dwConfigBase &= ~EDBSCFG_IMPORTVPKT;
	

	if( m_tImportAttr )
		dwConfigBase |= EDBSCFG_IMPORTATTR;
	else
		dwConfigBase &= ~EDBSCFG_IMPORTATTR;
	if( m_tCreateEDBSattr )
		dwConfigBase |= EDBSCFG_CREATEEDBSATTR;
	else
		dwConfigBase &= ~EDBSCFG_CREATEEDBSATTR;
	if( m_tCreateBIattr )
		dwConfigBase |= EDBSCFG_CREATEBIATTR;
	else
		dwConfigBase &= ~EDBSCFG_CREATEBIATTR;

	if( m_tCreateAttributeDateiname )
		dwConfigBase |= EDBSCFG_CREATEATTRDATEINAME;
	else
		dwConfigBase &= ~EDBSCFG_CREATEATTRDATEINAME;
	if( m_tCreateAttributeFolie )
		dwConfigBase |= EDBSCFG_CREATEATTRFOLIE;
	else
		dwConfigBase &= ~EDBSCFG_CREATEATTRFOLIE;
	if( m_tCreateAttributeObjektart )
		dwConfigBase |= EDBSCFG_CREATEATTROBJEKTART;
	else
		dwConfigBase &= ~EDBSCFG_CREATEATTROBJEKTART;
	if( m_tCreateAttributeObjektnummer )
		dwConfigBase |= EDBSCFG_CREATEATTROBJEKTNUMMER;
	else
		dwConfigBase &= ~EDBSCFG_CREATEATTROBJEKTNUMMER;
	if( m_tCreateAttributeObjektteilnummer )
		dwConfigBase |= EDBSCFG_CREATEATTROBJEKTTEILNUMMER;
	else
		dwConfigBase &= ~EDBSCFG_CREATEATTROBJEKTTEILNUMMER;
	if( m_tCreateAttributeObjektteilnummerK )
		dwConfigBase |= EDBSCFG_CREATEATTROBJEKTTEILNUMMERK;
	else
		dwConfigBase &= ~EDBSCFG_CREATEATTROBJEKTTEILNUMMERK;
	if( m_tCreateAttributeAktualitaet )
		dwConfigBase |= EDBSCFG_CREATEATTRAKTUALITAET;
	else
		dwConfigBase &= ~EDBSCFG_CREATEATTRAKTUALITAET;
	if( m_tCreateAttributeRegeln )
		dwConfigBase |= EDBSCFG_CREATEATTRREGELN;
	else
		dwConfigBase &= ~EDBSCFG_CREATEATTRREGELN;

	regEDBS.SetValue( dwConfigBase, "ConfigBase");

	regEDBS.Close();


}

void CCfg::LoadCfgDbs()
{
	POSITION	pos;
	CString		key;
	CCfgDb		*pCfgDb;
	CString	strConfigDescription;

	WIN32_FIND_DATA FileData;   // Data structure describes the file found
	HANDLE hSearch;             // Search handle returned by FindFirstFile
	BOOL bFinished = FALSE;
	
	if( m_dbCfg.IsOpen() )
		m_dbCfg.Close();

	for ( pos = m_CfgDbs.GetStartPosition(); pos != NULL; ) {
		m_CfgDbs.GetNextAssoc( pos, key, (CObject*&)pCfgDb );
		delete pCfgDb;
	}
	m_CfgDbs.RemoveAll();

	pCfgDb = new CCfgDb( "Default" );
	pCfgDb->m_strConfigName.LoadString(IDS_CFGDEFAULTNAME);
	pCfgDb->m_strConfigDescription.LoadString(IDS_CFGDEFAULTDESCRIPTION);
	m_CfgDbs.SetAt( "Default", pCfgDb );

// Alle Datenbanken im EDBS-Konfigurationsverteichnis ermitteln.

	hSearch = FindFirstFile (TEXT(m_strConfigPath + "*.mdb"), &FileData);
	if (hSearch == INVALID_HANDLE_VALUE)
		bFinished = TRUE;

	while( !bFinished ) {
		try {
//			m_dbCfg.OpenEx("UID=admin;DBQ=" + m_strConfigPath  + FileData.cFileName + ";DRIVER={Microsoft Access-Treiber (*.mdb)};DSN=''",CDatabase::openReadOnly );
			m_dbCfg.OpenEx("UID=admin;DBQ=" + m_strConfigPath  + FileData.cFileName + m_strAccessDriverName, CDatabase::openReadOnly );
			if( !m_dbCfg.IsOpen( ) )
				AfxMessageBox("Die Konfigurationsdatenbank konnte nicht geöffnet werden!");
			else {
				pCfgDb = new CCfgDb( FileData.cFileName );
				pCfgDb->m_strConfigName = GetCfgDbEntry("CFGNAME");
				pCfgDb->m_strConfigDescription = GetCfgDbEntry("CFGDESCRIPTION");
				pCfgDb->m_strShowCfgPage = GetCfgDbEntry("CFGSHOWCFGPAGE");
				m_CfgDbs.SetAt( FileData.cFileName, pCfgDb );
/*
				CRecordset rsCfg( &m_dbCfg );
				rsCfg.Open(CRecordset::forwardOnly,
				"SELECT [Einstellung] FROM [Einstellungen] WHERE [IDEinstellung] = 'CFGNAME'",
				CRecordset::readOnly );
				if( !rsCfg.IsEOF() ) {
					pCfgDb = new CCfgDb( FileData.cFileName );
					rsCfg.GetFieldValue( "Einstellung", pCfgDb->m_strConfigName );
				}
				else
					pCfgDb = NULL;
				rsCfg.Close();

				if( pCfgDb ) {
					rsCfg.Open(CRecordset::forwardOnly,
						"SELECT [Einstellung] FROM [Einstellungen] WHERE [IDEinstellung] = 'CFGDESCRIPTION' ORDER BY [IDXEinstellung]",
						CRecordset::readOnly );
					while( !rsCfg.IsEOF() ) {
						rsCfg.GetFieldValue( "Einstellung", strConfigDescription );
						pCfgDb->m_strConfigDescription += strConfigDescription;
						rsCfg.MoveNext();
					}
					rsCfg.Close();
					m_CfgDbs.SetAt( FileData.cFileName, pCfgDb );
				}
*/
				m_dbCfg.Close();
			}
		}

		catch( CDBException* e )
		{
			e->ReportError(MB_ICONEXCLAMATION);
			if( m_dbCfg.IsOpen() )
				m_dbCfg.Close();
		}
		if (!FindNextFile (hSearch, &FileData)) {
			bFinished = TRUE;
//			if (GetLastError () == ERROR_NO_MORE_FILES)
		}
	}
	

// Close the search handle.
	FindClose (hSearch);
	
		

}

void CCfg::ConnectCfgDb()
{
 bool tResult = false;

	if( m_dbCfg.IsOpen( ) )
		m_dbCfg.Close();
	
	try {
//		m_dbCfg.OpenEx("UID=admin;DBQ=" + m_strConfigPath + m_strConfigFile + ";DRIVER={Microsoft Access-Treiber (*.mdb)};DSN=''", CDatabase::openReadOnly );
		m_dbCfg.OpenEx("UID=admin;DBQ=" + m_strConfigPath + m_strConfigFile + m_strAccessDriverName, CDatabase::openReadOnly );
		if( !m_dbCfg.IsOpen( ) )
			AfxMessageBox("Die Konfigurationsdatenbank konnte nicht geöffnet werden!");
	}
	catch( CDBException* e ) {
		e->ReportError(MB_ICONEXCLAMATION);
	}
}

CString CCfg::GetCfgDbEntry(CString strKey)
{
	CxString		strVal("");

	if( m_dbCfg.IsOpen() ) {
		CRecordset  rsCfg( &m_dbCfg );
		CString		strSQL;
		CString		strTmp;

		strSQL = "SELECT [Einstellung] FROM [Einstellungen] WHERE [IDEinstellung] = '";
		strSQL += strKey + "' ORDER BY [IDXEinstellung]";

		rsCfg.Open(CRecordset::forwardOnly, strSQL,	CRecordset::readOnly );
		while( !rsCfg.IsEOF() ) {
			rsCfg.GetFieldValue( "Einstellung", strTmp );
			strTmp.Replace("\\n","\n");
			strVal += strTmp;
			rsCfg.MoveNext();
		}
		rsCfg.Close();
	}
	return strVal;
}
