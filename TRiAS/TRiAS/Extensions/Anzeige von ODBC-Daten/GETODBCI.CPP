//	FILE: GETODBCI.CPP
//
// 	Erarbeitet: J. Benkenstein			Stand vom 1.10.94

#include "pheader.h"			// vorübersetzter Header
#include "odbcext.hr"			// Resource-Konstanten    

#include <odbcinst.h>			// SQLValidDSN ()
#include <direct.h>				// _MAX_PATH
#include <io.h>    				//  _access ()
#include <hpp/odbcerr.hpp>			// OdbcError                                
#include <hpp/tableset.hpp>			// CTables
#include <hpp/columnst.hpp>			// CColumns
#include <hpp/waitcur.hpp>			// CWaitCursor
#include <hpp/getodbci.hpp>			// zugeh. Header
#include "database.hpp"			// CDataBaseEx                                

//	Konstanten
const int OdbcAdminVersion = 3;		//	ODBC-Version 3.0

// externe Variablen
extern "C" {
extern HINSTANCE g_hInstance;
}

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//	DSN ändern (Administrator rufen)
BOOL ChangeDataSource (HWND hWnd, const char *pInDSN, DataSourceType tType)
{
	ASSERT (pInDSN != NULL && AfxIsValidString (pInDSN));
	ASSERT (NULL != hWnd);
	ASSERT (UserDataSource == tType || FileDataSource == tType || SystemDataSource == tType);

	try
	{
	//	zuerst Treiber lesen
		CString strDriver (' ', _MAX_PATH);
		if (UserDataSource == tType || SystemDataSource == tType)
		{
			CString strFile, strSection;
			VERIFY (strFile.LoadString (IDS_ODBCINI));
			VERIFY (strSection.LoadString (IDS_DSNSECTION));
			if (! ::SQLGetPrivateProfileString (strSection, pInDSN, "",
												(char *)(const char *)strDriver, _MAX_PATH, strFile))
				return FALSE;
		}
		else		//	FileDataSource
		{
		/*		
			CString strSection, strKey;
			VERIFY (strSection.LoadString (IDS_ODBC));
			VERIFY (strKey.LoadString (IDS_DRIVER));
			if (! :: GetPrivateProfileString (strSection, strKey, "",
											  (char *)(const char *)strDriver, _MAX_PATH, pInDSN))
				return FALSE;
			läuft in ODBC nicht
		*/
			return ::SQLManageDataSources (hWnd);
		}

		CString strDsn;
		VERIFY (strDsn.LoadString (IDS_DSNGLEICH));	// Key --> DSN=
		strDsn += pInDSN;
		return SQLConfigDataSource (hWnd, 
								    tType == UserDataSource ? ODBC_CONFIG_DSN : ODBC_CONFIG_SYS_DSN, 
									strDriver, strDsn); 	// DSN konfigurieren
	}
	catch (CMemoryException *me)
	{
		me -> Delete ();
		DEX_Error (RC_CommonODBC, EC_NOMEMORY);			
	}

	return FALSE;
}

/*
	const short DSNBufferSize = 128;
	const short DriverBufferSize = 128;

	TRY
	{                
	//	Puffer für DSN anlegen
		CString strDSN;
		char *pDSN = strDSN.GetBuffer (DSNBufferSize);
		memset (pDSN, 0, DSNBufferSize);
		
	//	akt. DSN zusammenbauen
		if (:: LoadString (g_hInstance, IDS_DSNGLEICH, pDSN, DSNBufferSize))	// Kennung lesen: "DSN="
		{   
			lstrcat (pDSN, pInDSN);

		//	zugeh. Treiber bestimmen
			CString strDriver;
			char *pDriver = strDriver.GetBuffer (DriverBufferSize);		// Puffer anfordern
			
		//	Prpfile-Variablen init.			
			CString strFileName;
			strFileName.LoadString (IDS_ODBCINI);
			CString strSection;
			strSection.LoadString (IDS_DSNSECTION);
			
			if (SQLGetPrivateProfileString (strSection, strchr (pDSN, '=') + 1, "", pDriver, // Treiber lesen
						   				    DriverBufferSize, strFileName) &&
				SQLConfigDataSource (hWnd, ODBC_CONFIG_DSN, pDriver, pDSN)) 	// DSN konfigurieren
				return TRUE;
		}
	}
	CATCH (CMemoryException, cme)  
	{
		DEX_Error (RC_CommonODBC, EC_NOMEMORY);			
	}
	END_CATCH

	return FALSE;
*/

//	TRUE, wenn neuer DSN-erzeugt wurde, sonst False
BOOL CreateNewDataSource (HWND hWnd, DataSourceType tType)	// Administrator rufen
{
	ASSERT (NULL != hWnd);
	ASSERT (UserDataSource == tType || FileDataSource == tType || SystemDataSource == tType);

	try
	{
		CWaitCursor wc;
		CString strPath (' ', _MAX_PATH), strDsn (' ', _MAX_PATH);
		if (DEX_GetActiveProject ((const char *)strPath))
		{                                                               
		//	lese Projektnamen
			_splitpath (strPath, NULL, NULL, (char *)(const char *)strDsn, NULL);
			strDsn.MakeUpper ();		// in Großbuchstaben

			if (UserDataSource == tType || SystemDataSource == tType)
			{
			//	prüfe max. Länge
				if (strDsn.GetLength () > SQL_MAX_DSN_LENGTH)
					strDsn = strDsn.Left (SQL_MAX_DSN_LENGTH);
				
			//	prüfe min. Länge: Name muß für ODBC wenigstens 5 Zeichen haben		
				while (strDsn.GetLength () < 5)
					strDsn += "_";

			//	prüfe Datasourcenamen
				if (! ::SQLValidDSN (strDsn))
					strDsn.Empty ();
			}
			else		//	Spezialbehandlung für FileDataSource
			{
				CString strDir, strExt;
				GetFileDataSourceDir (strDir);
				VERIFY (strExt.LoadString (IDS_FILE_DSN_EXT));
				_makepath ((char *)(const char *)strPath, NULL, strDir, strDsn, strExt);
				strDsn = strPath;
			}			
		
		//	DataSource bereits vorhanden			
			if (ExistDataSource (strDsn, tType))
				strDsn.Empty ();						
		}		           
		else
			strDsn.Empty ();
	
		return SQLCreateDataSource (hWnd, strDsn);
	}
	catch (CMemoryException *m)
	{
		m -> Delete ();
		DEX_Error (RC_CommonODBC, EC_NOMEMORY);
	}

	return FALSE;
}

//	FileSource über Dialog auswählen
BOOL SelectFileDataSource (CString &strDsn, CWnd *pParent)
{
	try
	{
	//	lese Dafaultverzeichnis
		CString strPath;
		GetFileDataSourceDir (strPath);
			
	//	FileAuswahl-Dialog
		CString strExt, strFilter, strTitle;
		VERIFY (strExt.LoadString (IDS_FILE_DSN_EXT));
		VERIFY (strFilter.LoadString (IDS_FILE_DSN_FILTER));
		VERIFY (strTitle.LoadString (IDS_SELECT_FILE_DSN));
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
		CFileDialog Dlg (TRUE, strExt, NULL, dwFlags, strFilter, pParent);
		Dlg.m_ofn.lpstrInitialDir = strPath;
		Dlg.m_ofn.lpstrTitle = strTitle;
		if (IDOK == Dlg.DoModal ())
		{
			strDsn = Dlg.GetPathName ();
			strDsn.MakeUpper ();
			return TRUE;
		}
	}
	catch (CMemoryException *m)
	{
		m -> ReportError ();
		m -> Delete ();
	}

	return FALSE;
}

//	diese Funktion überprüft die Gültigkeit eines ODBC-Eintrages:
//	- existiert das bei "DefaultDir" oder "DBQ" angegebene Verzeichnis ?
BOOL DSNParamOk (const char *pDSN, DataSourceType tType)
{
	ASSERT (UserDataSource == tType || FileDataSource == tType || SystemDataSource == tType);

//	prüfe Parameter
	if (!pDSN || !*pDSN)
		return FALSE;	

//	lese Verzeichnis-Eintrag		
	try
	{
		if (FileDataSource == tType)
		{
			CString strSection, strEntry, strPath, strDBQ;
			VERIFY (strSection.LoadString (IDS_ODBC_SETUPSECTION));	// JG990314
			VERIFY (strEntry.LoadString (IDS_DEFAULT_DIR));
			VERIFY (strDBQ.LoadString (IDS_DBQ));
			char *pPath = strPath.GetBuffer (_MAX_PATH);
			if (GetPrivateProfileString (strSection, strEntry, "", pPath, _MAX_PATH, pDSN) || 
				GetPrivateProfileString (strSection, strDBQ, "", pPath, _MAX_PATH, pDSN))
				return (_access (pPath, 0) == 0) ? TRUE : FALSE;
			
			return TRUE;
		}

		CString strFileName, strEntry, strPath, strDBQ;
		VERIFY (strFileName.LoadString (IDS_ODBCINI));
		VERIFY (strEntry.LoadString (IDS_DEFAULT_DIR));
		VERIFY (strDBQ.LoadString (IDS_DBQ));
		char *pPath = strPath.GetBuffer (_MAX_PATH);			

		if (SQLGetPrivateProfileString (pDSN, strEntry, "", pPath, _MAX_PATH, strFileName) ||
			SQLGetPrivateProfileString (pDSN, strDBQ, "", pPath, _MAX_PATH, strFileName))
			return (_access (pPath, 0) == 0) ? TRUE : FALSE;

		return TRUE;
	}
	catch (CMemoryException *me)
	{        
		me -> Delete ();
		DEX_Error (RC_GetDataSources, EC_NOMEMORY);
	}
	
	return FALSE;
}           
	
//	wenn Data-Source in ODBC-INI existiert, dann TRUE sonst FALSE
BOOL ExistDataSource (const char *pDSN, DataSourceType tType)
{       
//	prüfe Parameter
	if (!pDSN || !*pDSN)
		return FALSE;					
	ASSERT (UserDataSource == tType || FileDataSource == tType || SystemDataSource == tType);

	try
	{
		if (FileDataSource == tType)
		{
			OFSTRUCT of;
			return (OpenFile (pDSN, &of, OF_EXIST) != HFILE_ERROR);
		}
		else
		{
		//	lese Nutzer- und System-DataSources
		//	EnvHandle besorgen
			HENV hEnv = NULL;
			RETCODE rc = :: SQLAllocEnv (&hEnv);
			if (SQL_SUCCESS != rc)
				return FALSE;

		//	lese Einträge
			BOOL bFound = FALSE;
			char BufferDSN [SQL_MAX_DSN_LENGTH+2] = "";
			SQLSMALLINT iReadCnt = 0;
			rc = :: SQLDataSources (hEnv, SQL_FETCH_FIRST, (UCHAR FAR *)BufferDSN, 
									sizeof(BufferDSN)-1, &iReadCnt, NULL, 0, NULL);
			while (SQL_SUCCESS == rc)
			{
				if (iReadCnt > 0)
				{
					if (0 == strcmpi (BufferDSN, pDSN))
					{
						bFound = TRUE;
						break;
					}
				}	

			//	lese nächsten Eintrag
				rc = :: SQLDataSources (hEnv, SQL_FETCH_NEXT, (UCHAR FAR *)BufferDSN, 
										sizeof(BufferDSN)-1, &iReadCnt, NULL, 0, NULL);
			}

		//	EnvHandle freigeben
			if (NULL != hEnv)
				:: SQLFreeEnv (hEnv);

			return bFound;

		/*  alte Variante
			if (UserDataSource == tType)
			{
				CString strFileName;
				strFileName.LoadString (IDS_ODBCINI);
				CString strSection;       
				strSection.LoadString (IDS_DSNSECTION);
				CString strBuffer;
				char *pBuffer = strBuffer.GetBuffer (BufferSize);
			
			//	alle Einträge lesen		
				if (SQLGetPrivateProfileString (strSection, NULL, "", pBuffer, 
					BufferSize, strFileName))
				{
				//	jetzt alle gelesenen Einträge prüfen
					for (; *pBuffer; pBuffer += lstrlen (pBuffer) + 1)			
					{
						if (strcmpi (pBuffer, pDSN) == 0)
							return TRUE;
					}
				}		                        
			else		//	System-DataSource
				return FALSE;
			*/
		}
	}
	catch (CMemoryException *me)
	{                   
		me -> Delete ();
		DEX_Error (RC_GetDataSources, EC_NOMEMORY);
	}
	
	return FALSE;		
}

//	lese Verzeichnis für FiledataSources
void GetFileDataSourceDir (CString &strDirIn)
{
	try
	{
	//	lese Default-Verzeichnis aus odbc.ini
		CString strFile, strSection, strKey, strPath (' ', _MAX_PATH);
		VERIFY (strFile.LoadString (IDS_ODBCINI));
		VERIFY (strSection.LoadString (IDS_ODBC_FILE_DSN));
		VERIFY (strKey.LoadString (IDS_ODBC_DEFAULT_DIR));
		if (! ::SQLGetPrivateProfileString (strSection, strKey, "", 
										   (char *)(const char *)strPath, _MAX_PATH, strFile) || 
		   (_access (strPath, 0) != 0))
		{
		//	wenn Eintrag nicht vorhanden, Projekt Verzeichnis besorgen
			if (DEX_GetActiveProject ((const char *)strPath))
			{
				CString strDir (' ', _MAX_DIR), strDrive (' ', _MAX_DRIVE);
				_splitpath (strPath, (char *)(const char *)strDrive, (char *)(const char *)strDir, NULL, NULL);
				_makepath ((char *)(const char *)strPath, strDrive, strDir, NULL, NULL);
				strDirIn = strPath;
			}
		}
		else
			strDirIn = strPath;
	}
	catch (CMemoryException *m)
	{
		m -> ReportError ();
		m -> Delete ();
	}
}	

//	die verfügbaren Data-SourceNames aus der ODBC-INI lesen und in Combo/ListBox ausgeben
BOOL GetDataSources (CWnd *pWnd, DataSourceType tType)
{       
	ASSERT (pWnd != NULL);
	ASSERT (UserDataSource == tType || SystemDataSource == tType);

	if (FileDataSource == tType)
		return TRUE;

	CWaitCursor wc;
	BOOL bType = TRUE;					// ComboBox
	if (pWnd -> IsKindOf (RUNTIME_CLASS(CListBox)))
		bType = FALSE;					// ListBox
	else
		ASSERT (pWnd -> IsKindOf (RUNTIME_CLASS(CComboBox)));

//	EnvHandle besorgen
	HENV hEnv = NULL;
	RETCODE rc = :: SQLAllocEnv (&hEnv);
	if (SQL_SUCCESS != rc)
		return FALSE;

	BOOL bOk = FALSE;					// Op-Flag
	try
	{
	//	alten Infos löschen
		if (bType)
			((CComboBox *) pWnd) -> ResetContent ();	
		else
			((CListBox *) pWnd) -> ResetContent ();	

		char BufferDSN [SQL_MAX_DSN_LENGTH+2] = "";
		SQLSMALLINT iReadCnt = 0;

//		lese Version des Administrators
		int iDir = UserDataSource == tType ? SQL_FETCH_FIRST_USER : SQL_FETCH_FIRST_SYSTEM;
		if (GetOdbcAdminVersion () < OdbcAdminVersion)
			iDir = SQL_FETCH_FIRST;
		RETCODE	rc = :: SQLDataSources (hEnv, iDir,
										(UCHAR FAR *)BufferDSN, sizeof(BufferDSN)-1, 
										&iReadCnt, NULL, 0, NULL);
		int iRes = 0;
		while (SQL_SUCCESS == rc)
		{
			if ((iReadCnt > 0) && SQLValidDSN (BufferDSN) && DSNParamOk (BufferDSN, tType))
			{					
				if (bType)	
					iRes = ((CComboBox *) pWnd) -> AddString (BufferDSN);
				else
					iRes = ((CListBox *) pWnd) -> AddString (BufferDSN);

				if (iRes < 0)
					AfxThrowMemoryException ();
			}

		//	lese nächsten Eintrag
			iReadCnt = 0;
			rc = :: SQLDataSources (hEnv, SQL_FETCH_NEXT, (UCHAR FAR *)BufferDSN,
									sizeof(BufferDSN)-1, &iReadCnt, NULL, 0, NULL);
		}

	//	Ergebnisflag setzen
		if (bType)	
			bOk = ((CComboBox *) pWnd) -> GetCount () > 0 ? TRUE : FALSE;
		else
			bOk = ((CListBox *) pWnd) -> GetCount () > 0 ? TRUE : FALSE;
	}
	catch (CMemoryException *me)
	{                   
		me -> Delete ();
		DEX_Error (RC_GetDataSources, EC_NOMEMORY);
	}

//	EnvHandle freigeben
	if (NULL != hEnv)
		:: SQLFreeEnv (hEnv);
	
	return bOk;		


/*	alte Variante
	const short BufferSize = 1024;		// Ini-Lese-Puffer
	BOOL bOk = TRUE;					// Op-Flag
	int iRes = 0;
	
	TRY
	{
		CString strFileName;
		strFileName.LoadString (IDS_ODBCINI);
		CString strSection;       
		strSection.LoadString (IDS_DSNSECTION);
		CString strBuffer;
		char *pBuffer = strBuffer.GetBuffer (BufferSize);
		
	//	alle Einträge lesen		
		if (SQLGetPrivateProfileString (strSection, NULL, "", pBuffer, 
			BufferSize, strFileName))
		{
		//	jetzt alle gelesenen Einträge in ListBox ausgeben
			if (bType)
				((CComboBox *) pWnd) -> ResetContent ();		// alten Infos löschen
			else
				((CListBox *) pWnd) -> ResetContent ();		// alten Infos löschen				
			for (; *pBuffer; pBuffer += lstrlen (pBuffer) + 1)			
			{
				if (! SQLValidDSN (strupr (pBuffer)))	// nur wenn gültiger Name
					continue;

				if (! DSNParamOk (pBuffer, FALSE))
					continue;					
				
				if (bType)	
					iRes = ((CComboBox *) pWnd) -> AddString (pBuffer);
				else
					iRes = ((CListBox *) pWnd) -> AddString (pBuffer);

				if (iRes < 0)
				{            
					bOk = FALSE;
					DEX_Error (RC_GetDataSources, EC_SYSERROR);  
					break;
				}
			}
		}		                        
		else
			bOk	= FALSE;					
	}
	CATCH (CMemoryException, cme);
	{                   
		bOk = FALSE;
		DEX_Error (RC_GetDataSources, EC_NOMEMORY);
	}
	END_CATCH
	return bOk;		
*/
}
     
 // CODBCInfos -----------------------------------------------------------------------------------------
CODBCInfos :: CODBCInfos (void)
{
	m_pDataBase = NULL;
	m_pTables = NULL;
	m_pColumns = NULL;
}                     

CODBCInfos :: ~CODBCInfos (void)
{
	DeleteAll ();
}

void CODBCInfos :: DeleteAllNotDataSource (void)
{
//	Spalten-Infos löschen
	DELETE_OBJ (m_pColumns);
	
//	Tabellen-Infos löschen
	DELETE_OBJ (m_pTables);
}

void CODBCInfos :: DeleteAll (void)
{       
//	Spalten-Infos löschen
	DELETE_OBJ (m_pColumns);
	
//	Tabellen-Infos löschen
	DELETE_OBJ (m_pTables);
	
//	Data-Source-Objekt			
	DELETE_OBJ (m_pDataBase);
}                               

// alten Objekte komplett löschen
// Erzeugen und Öffnen eines Data-Source-Objektes
CDataBaseExt *CODBCInfos :: CreateDataBase (const char *pDSN, DataSourceType tType)
{
	ASSERT (UserDataSource == tType || FileDataSource == tType || SystemDataSource == tType);

	if (!pDSN)
	{                
		DEX_Error (RC_CreateDataBaseCODBCInfos, EC_ILLPARS);
		return NULL;
	}				
	
CWaitCursor wc; 		// Sanduhr einschalten
	                         
//	Data-Source-Objekt bereits geladen ?	                         
	if (m_pDataBase && (strcmpi (m_pDataBase -> DataSourceName (), pDSN) == 0))
		return m_pDataBase;
		
//	neues Objekt erzeugen
	TRY {                   
		DeleteAll ();									// alten Infos löschen				
		m_pDataBase = new CDataBaseExt (pDSN, tType);	// neues Objekt erzeugen
		if (m_pDataBase -> Open () == FALSE)			// DataSource-Objekt öffnen
		{
			DELETE_OBJ (m_pDataBase);
			return NULL;
		}
	}		
	CATCH (CMemoryException, me)
	{   
		DEX_Error (RC_CreateDataBaseCODBCInfos, EC_NOMEMORY);
		return NULL;
	}
	END_CATCH       
	
	return m_pDataBase;
}
                                                         
// alten Table-Set löschen
// neuen Tables-Set erzeugen und öffnen
// alle Tabellen-Namen in Combo/Listbox ausgeben
BOOL CODBCInfos :: OutputTableNames (CWnd *pWnd)
{                    
	ASSERT (pWnd != NULL);
	BOOL bType = TRUE;			// ComboBox
	if (pWnd -> IsKindOf (RUNTIME_CLASS(CListBox)))
		bType = FALSE;			// ListBox
	else
		ASSERT (pWnd -> IsKindOf (RUNTIME_CLASS(CComboBox)));

//	prüfe interne Parameter
	if (! m_pDataBase)     
	{
		DEX_Error (RC_OutputTableNamesCODBCInfos, EC_ILLPARS);
		return FALSE;
	}		                      
	               
CWaitCursor wc;
		               
//	alten Tabellen-Set ggf. löschen
	DELETE_OBJ (m_pTables);
		
	TRY {                
		m_pTables = new CTables ((CDatabase *) m_pDataBase);
		m_pTables -> m_strTypeParam = "'TABLE'";				// Tabellen-Namen lesen
		if (m_pTables -> Open (CRecordset::snapshot, NULL, CRecordset::readOnly) == FALSE)
		{
			DELETE_OBJ (m_pTables);
			return FALSE;
		}
	
	// 	Flush pending results for drivers that don't support multiple hstmt's
		m_pTables -> MoveLast ();
		m_pTables -> MoveFirst ();
		
	//	alle alten Tabellen aus ComboBox löschen	             
		if (bType)
			((CComboBox *) pWnd) -> ResetContent ();
		else
			((CListBox *) pWnd) -> ResetContent ();			
		
	//	Tabellen-Namen ausgeben		
		int iRes = 0;
		while (! m_pTables -> IsEOF ())
		{                         
			// m_pTables -> m_strName.MakeUpper ();			// nur Großbuchstaben
			if (bType)
				iRes = ((CComboBox *) pWnd) -> AddString (m_pTables -> m_strName);
			else
				iRes = ((CListBox *) pWnd) -> AddString (m_pTables -> m_strName);								
			if (iRes < 0)
			{
				DEX_Error (RC_OutputTableNamesCODBCInfos, EC_NOMEMORY);
				return FALSE;
			}    
			m_pTables -> MoveNext ();	// zur nächsten Tabelle
		}		
	}        
	CATCH (CDBException, dbe)
	{		 
		OdbcError Err (dbe);
		Err.Show (RC_OutputTableNamesCODBCInfos);
		return FALSE;
	}		
	AND_CATCH (CMemoryException, me)
	{                                                     
		DEX_Error (RC_OutputTableNamesCODBCInfos, EC_NOMEMORY);
		return FALSE;
	}                     
	AND_CATCH (CFileException, me)
	{                                                       
		// DEX_Error (RC_OutputTableNamesCODBCInfos, EC_SYSERROR);
		me -> ReportError ();
		return FALSE;
	}
	END_CATCH	                 
	                                 
	return TRUE;                                 
}                            
 
// gebe zur angegebenen Tabelle alle möglichen Koppelfelder in ListBox aus
// erzeuge neues Columns-Objekt	
BOOL CODBCInfos :: OutputColumnNames (const char *pTableName, 
								      CComboBox &cbColumnsList, short sType)
{
//	prüfe interne Parameter
	if (!m_pDataBase || !m_pTables || !pTableName)
	{
		DEX_Error (RC_OutputColumnNamesCODBCInfos, EC_ILLPARS);
		return FALSE;
	}	        
	                        
	CWaitCursor wc;	                        
	BOOL bOk = FALSE;					// noch nichts getan
	TRY
	{                
		m_pTables -> MoveFirst ();		// zur 1. Tabelle

	//	Tabelle suchen		
		while (! m_pTables -> IsEOF ())
		{                                            
		//	wenn Tabelle gefunden
			if (m_pTables -> m_strName.CompareNoCase (pTableName) == 0)
			{   
				DELETE_OBJ (m_pColumns);	// alten Spalten-Infos löschen							
				m_pColumns = new CColumns ((CDatabase *) m_pDataBase);
				m_pColumns -> m_strTableNameParam = pTableName;        // Namen für ODBC speichern		
				if (m_pColumns -> Open () == TRUE)						 // Set öffnen
				{   
				//	jetzt alle Feld-Bezeichnungen ausgeben
					cbColumnsList.ResetContent ();					// alten Feldnamen löschen
					while (! m_pColumns -> IsEOF ())
					{                          
					//	nur "ausgesuchte" Felder für Kopplung
						switch (m_pColumns -> m_nDataType)
						{                                 
							case SQL_SMALLINT:
							case SQL_INTEGER:
							case SQL_REAL:
							case SQL_FLOAT:
							case SQL_DOUBLE:
							case SQL_DATE:
							case SQL_TIME:
							case SQL_TIMESTAMP:
							case SQL_DECIMAL:  
							case SQL_NUMERIC:  
							case SQL_CHAR:
							case SQL_VARCHAR:
							{
								if ((sType != -1) &&		// Typ-Prüfung wird verlangt
								    (!SQLTypesCompatible (sType, m_pColumns -> m_nDataType)))
								    break;					// Typen sind nicht kompatibel
								// m_pColumns -> m_strColumnName.MakeUpper ();				// nur Großbuchstaben			
								if (cbColumnsList.AddString (m_pColumns -> m_strColumnName) < 0)
								{
									DEX_Error (RC_OutputColumnNamesCODBCInfos, EC_NOMEMORY);
									DELETE_OBJ (m_pColumns);  	
									return FALSE;           
								}                           
							}								
						}
						m_pColumns -> MoveNext ();		// zum nächsten Feld
					}						
					bOk = TRUE;				// alles ausgegeben 
				}
				else
					DELETE_OBJ (m_pColumns);  	// Fehler beim Öffnen										
				break;	                	// keine weiteren Tabellen mehr
			}								// end_if 		(wenn Tabelle gefunden)
			m_pTables -> MoveNext ();		// zur nächsten Tabelle			
		}									// end_while	(Tabellensuche)
	}        
	CATCH (CDBException, dbe)
	{		 
		OdbcError Err (dbe);
		Err.Show (RC_OutputColumnNamesCODBCInfos);
		return FALSE;
	}		
	AND_CATCH (CMemoryException, me)
	{                                                     
		DEX_Error (RC_OutputColumnNamesCODBCInfos, EC_NOMEMORY);
		return FALSE;
	}                     
	AND_CATCH (CFileException, me)
	{                                                       
		// DEX_Error (RC_OutputColumnNamesCODBCInfos, EC_SYSERROR);
		me -> ReportError ();
		return FALSE;
	}
	END_CATCH	                 

	return bOk;				
}
            
// gebe Kommentar zur angegebenen Tabelle in Beschr.-Feld aus	                                                                 
BOOL CODBCInfos :: OutputTableInfo (const char *pTableName, CEdit &stDescription)
{
//	prüfe interne Parameter
	if (!m_pTables ||!pTableName)
	{
		DEX_Error (RC_OutputTableInfoCODBCInfos, EC_ILLPARS);
		return FALSE;
	}	        

	CWaitCursor wc;	
	BOOL bOk = FALSE;					// noch nichts getan
	TRY
	{                
		m_pTables -> MoveFirst ();		// zur 1. Tabelle

	//	Tabelle suchen		
		while (! m_pTables -> IsEOF ())
		{                                            
		//	wenn Tabelle gefunden
			if (m_pTables -> m_strName.CompareNoCase (pTableName) == 0)
			{   
				stDescription.SetWindowText (m_pTables -> m_strRemarks);
				bOk = TRUE;			// alles OK
				break;				// und Suche beenden
			}	
			m_pTables -> MoveNext ();			
		}	
	}        
	CATCH (CDBException, dbe)
	{		 
		OdbcError Err (dbe);
		Err.Show (RC_OutputTableInfoCODBCInfos);
		return FALSE;
	}		
	AND_CATCH (CMemoryException, me)
	{                                                     
		DEX_Error (RC_OutputTableInfoCODBCInfos, EC_NOMEMORY);
		return FALSE;
	}                     
	AND_CATCH (CFileException, me)
	{                                                       
		// DEX_Error (RC_OutputTableInfoCODBCInfos, EC_SYSERROR);
		me -> ReportError ();
		return FALSE;
	}
	END_CATCH	                 

	return bOk;				
}

// gebe FeldInfo zum gegebenen Feld aus
BOOL CODBCInfos :: OutputColumnInfo (const char *pFieldName, CEdit &stDescription)
{
//	prüfe interne Parameter
	if (!m_pColumns || !pFieldName)
	{
		DEX_Error (RC_OutputColumnInfoCODBCInfos, EC_ILLPARS);
		return FALSE;
	}	        

	CWaitCursor wc;	
	BOOL bOk = FALSE;					// noch nichts getan
	TRY
	{                
		m_pColumns -> MoveFirst ();		// zum 1. Feld

	//	Feld suchen		
		while (! m_pColumns -> IsEOF ())
		{                                            
		//	wenn Feld gefunden
			if (m_pColumns -> m_strColumnName.CompareNoCase (pFieldName) == 0)
			{                   
			//	Kommentar bilden
				CString strFormat;    
				strFormat.LoadString (IDS_FIELDESCRIPTIONFORMAT);
				char Buffer [80] = "";                              
				char LenBuffer [20] = "";
				ltoa (m_pColumns -> m_lLength, LenBuffer, 10);   
				wsprintf (Buffer, strFormat, m_pColumns -> m_strTypeName);
				lstrcat (Buffer, LenBuffer);
				stDescription.SetWindowText (Buffer);
				bOk = TRUE;			// alles OK
				break;				// und Suche beenden
			}	
			m_pColumns -> MoveNext ();
		}	
	}        
	CATCH (CDBException, dbe)
	{		 
		OdbcError Err (dbe);
		Err.Show (RC_OutputColumnInfoCODBCInfos);
		return FALSE;
	}		
	AND_CATCH (CMemoryException, me)
	{                                                     
		DEX_Error (RC_OutputColumnInfoCODBCInfos, EC_NOMEMORY);
		return FALSE;
	}                     
	AND_CATCH (CFileException, me)
	{                                                       
		// DEX_Error (RC_OutputColumnInfoCODBCInfos, EC_SYSERROR);
		me -> ReportError ();
		return FALSE;
	}
	END_CATCH	                 

	return bOk;				
}
	                        
// gebe Kommentar zum aktuellen Data-Source-Objekt aus 
BOOL CODBCInfos :: OutputDataBaseInfo (CEdit &stDescription)
{    
	if (!m_pDataBase)
		return FALSE;

	TRY
	{
		CString strFileName;
		strFileName.LoadString (IDS_ODBCINI);
		CString strEntry;       
		strEntry.LoadString (IDS_DESCRIPTION);
		char Buffer [100] = "";
		
	//	alle Einträge lesen		
		if (SQLGetPrivateProfileString (m_pDataBase -> DataSourceName (), strEntry, "", 
										Buffer, sizeof (Buffer), strFileName))
			stDescription.SetWindowText (Buffer);		
		else
			stDescription.SetWindowText ("");		// keine Beschreibung gefunden
	}
	CATCH (CMemoryException, cme);
	{                   
		DEX_Error (RC_GetDataSources, EC_NOMEMORY);
		return FALSE;		
	}
	END_CATCH
	
	return TRUE;		
}

BOOL CODBCInfos :: CompleteImportInfo (void)
{
	return m_pDataBase && m_pDataBase -> IsOpen () ? TRUE : FALSE;
}	                        
	                        
//	Funktionen des DataSources in ListBox/ComboBox ausgeben
BOOL CODBCInfos :: OutputFunctions (CWnd *pCWnd, UINT *pFunctField, UINT uiSize)
{                    
//	prüfe Parameter
	ASSERT (NULL != pCWnd);
	ASSERT (NULL != pFunctField);
	ASSERT (uiSize > 0);

	BOOL bType = TRUE;			// ComboBox
	if (pCWnd -> IsKindOf (RUNTIME_CLASS(CListBox)))
		bType = FALSE;			// ListBox
	else
		ASSERT (pCWnd -> IsKindOf (RUNTIME_CLASS(CComboBox)));

//	prüfe interne Parameter
	if (! m_pDataBase || !m_pDataBase -> IsOpen ())     
	{
		DEX_Error (RC_OutputTableNamesCODBCInfos, EC_ILLPARS);
		return FALSE;
	}		                      
	               
	CWaitCursor wc;
	TRY
	{                
	//	alten Funktionsnamen löschen	             
		if (bType)
			((CComboBox *) pCWnd) -> ResetContent ();
		else
			((CListBox *) pCWnd) -> ResetContent ();			
		
	//	Functionfeld init.      
		memset (pFunctField, 0, uiSize);

	//	Funktions-Namen ausgeben		
	//	lese String-Funktionen-Flag
		UDWORD	fFuncs = 0;            
		RETCODE nRetCode;		
		AFX_SQL_ASYNC (m_pDataBase, :: SQLGetInfo (m_pDataBase -> m_hdbc, 
					   SQL_STRING_FUNCTIONS, &fFuncs, sizeof (fFuncs), NULL));
		
	//	prüfe Ret-Kode									  
		if (nRetCode != SQL_SUCCESS)                                 
		{
			DEX_Error (RC_CCreateWhereKlDlg, EC_SYSERROR);
			return FALSE;
		}						
		    
	//	gebe zugeh. String-Funktionen in ListBox aus und speichere 
	//	deren Beschreibungs-ResID
		uint uIndex = 0;				// Beschreibungs-Array-Index init.
		GetScaleFunction (uIndex, IDS_STRING_ACII, SQL_FN_STR_ASCII, fFuncs, pCWnd,pFunctField);
		GetScaleFunction (uIndex, IDS_STRING_CHAR, SQL_FN_STR_CHAR, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_STRING_CONCAT, SQL_FN_STR_CONCAT, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_STRING_INSERT, SQL_FN_STR_INSERT, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_STRING_LCASE, SQL_FN_STR_LCASE, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_STRING_LEFT, SQL_FN_STR_LEFT, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_STRING_LENGTH, SQL_FN_STR_LENGTH, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_STRING_LOCATE, SQL_FN_STR_LOCATE, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_STRING_LTRIM, SQL_FN_STR_LTRIM, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_STRING_REPEAT, SQL_FN_STR_REPEAT, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_STRING_REPLACE, SQL_FN_STR_REPLACE, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_STRING_RIGHT, SQL_FN_STR_RIGHT, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_STRING_RTRIM, SQL_FN_STR_RTRIM, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_STRING_SUBSTRING, SQL_FN_STR_SUBSTRING, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_STRING_UCASE, SQL_FN_STR_UCASE, fFuncs, pCWnd, pFunctField);				
		
	//	lese Konvertierungs-Funktionen 
		fFuncs = 0;            
		AFX_SQL_ASYNC (m_pDataBase, :: SQLGetInfo (m_pDataBase -> m_hdbc, 
					   SQL_CONVERT_FUNCTIONS, &fFuncs, sizeof (fFuncs), NULL));
		
	//	prüfe Ret-Kode									  
		if (nRetCode != SQL_SUCCESS)                                 
		{
			DEX_Error (RC_OutputTableNamesCODBCInfos, EC_SYSERROR);
			return FALSE;
		}								
		GetScaleFunction (uIndex, IDS_CVT_CONVERT, SQL_FN_CVT_CONVERT, fFuncs, pCWnd, pFunctField);
		
	//	lese numerische Funktionen
		fFuncs= 0;            
		AFX_SQL_ASYNC (m_pDataBase, :: SQLGetInfo (m_pDataBase -> m_hdbc, 
					   SQL_NUMERIC_FUNCTIONS, &fFuncs, sizeof (fFuncs), NULL));					
					   
		if (nRetCode != SQL_SUCCESS)                                 
		{
			DEX_Error (RC_OutputTableNamesCODBCInfos, EC_SYSERROR);
			return FALSE;
		}													   
		GetScaleFunction (uIndex, IDS_NUM_ABS, SQL_FN_NUM_ABS, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_NUM_ACOS, SQL_FN_NUM_ACOS, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_NUM_ASIN, SQL_FN_NUM_ASIN, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_NUM_ATAN, SQL_FN_NUM_ATAN, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_NUM_ATAN2, SQL_FN_NUM_ATAN2, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_NUM_CEILING, SQL_FN_NUM_CEILING, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_NUM_COS, SQL_FN_NUM_COS, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_NUM_COT, SQL_FN_NUM_COT, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_NUM_EXP, SQL_FN_NUM_EXP, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_NUM_FLOOR, SQL_FN_NUM_FLOOR, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_NUM_LOG, SQL_FN_NUM_LOG, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_NUM_MOD, SQL_FN_NUM_MOD, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_NUM_PI, SQL_FN_NUM_PI, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_NUM_RAND, SQL_FN_NUM_RAND, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_NUM_SIGN, SQL_FN_NUM_SIGN, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_NUM_SIN, SQL_FN_NUM_SIN, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_NUM_SQRT, SQL_FN_NUM_SQRT, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_NUM_TAN, SQL_FN_NUM_TAN, fFuncs, pCWnd, pFunctField);				
		
	//	lese Datums-Funktionen
		fFuncs = 0;            
		AFX_SQL_ASYNC (m_pDataBase, :: SQLGetInfo (m_pDataBase -> m_hdbc, 
					   SQL_TIMEDATE_FUNCTIONS, &fFuncs, sizeof (fFuncs), NULL));					
					   
		if (nRetCode != SQL_SUCCESS)                                 
		{
			DEX_Error (RC_OutputTableNamesCODBCInfos, EC_SYSERROR);
			return FALSE;
		}													   				
		GetScaleFunction (uIndex, IDS_TD_NOW, SQL_FN_TD_NOW, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_TD_CURDATE, SQL_FN_TD_CURDATE, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_TD_DAYOFMONTH, SQL_FN_TD_DAYOFMONTH, fFuncs, pCWnd, pFunctField);		
		GetScaleFunction (uIndex, IDS_TD_DAYOFWEEK, SQL_FN_TD_DAYOFWEEK, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_TD_DAYOFYEAR, SQL_FN_TD_DAYOFYEAR, fFuncs, pCWnd, pFunctField);		
		GetScaleFunction (uIndex, IDS_TD_MONTH, SQL_FN_TD_MONTH, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_TD_QUARTER, SQL_FN_TD_QUARTER, fFuncs, pCWnd, pFunctField);		
		GetScaleFunction (uIndex, IDS_TD_WEEK, SQL_FN_TD_WEEK, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_TD_YEAR, SQL_FN_TD_YEAR, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_TD_CURTIME, SQL_FN_TD_CURTIME, fFuncs, pCWnd, pFunctField);		
		GetScaleFunction (uIndex, IDS_TD_HOUR, SQL_FN_TD_HOUR, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_TD_MINUTE, SQL_FN_TD_MINUTE, fFuncs, pCWnd, pFunctField);
		GetScaleFunction (uIndex, IDS_TD_SECOND, SQL_FN_TD_SECOND, fFuncs, pCWnd, pFunctField);					
	}        
	CATCH (CDBException, dbe)
	{		 
		OdbcError Err (dbe);
		Err.Show (RC_OutputTableNamesCODBCInfos);
		return FALSE;
	}		
	AND_CATCH (CMemoryException, me)
	{                                                     
		DEX_Error (RC_OutputTableNamesCODBCInfos, EC_NOMEMORY);
		return FALSE;
	}                     
	AND_CATCH (CFileException, me)
	{                                                       
		// DEX_Error (RC_OutputTableNamesCODBCInfos, EC_SYSERROR);
		me -> ReportError ();
		return FALSE;
	}
	END_CATCH	                 
	                                 
	return TRUE;                                 
}                            

//	prüfe und lese Beschreibungs-Info einer skalaren Funktion
void CODBCInfos :: GetScaleFunction (uint &uIndex, uint uResID,
									 UDWORD uwCheckFlag, UDWORD fFlag,
									 CWnd *pCWnd, UINT *pFunctArr)
{
//	prüfe Parameter
	ASSERT (NULL != pCWnd);
	ASSERT (uIndex >= 0);
	ASSERT (uResID > 0);
	ASSERT (NULL != pFunctArr);
	
	if (uwCheckFlag & fFlag)
	{                            
		CString strText;
		TRY 
		{
			BOOL bType = TRUE;					// ComboBox
			if (pCWnd -> IsKindOf (RUNTIME_CLASS(CListBox)))
				bType = FALSE;					// ListBox
			else
				ASSERT (pCWnd -> IsKindOf (RUNTIME_CLASS(CComboBox)));

		//	String laden und ausgeben
			VERIFY (strText.LoadString (uResID));
			int iRes = 0;
			if (bType)
				iRes = ((CComboBox *) pCWnd) -> AddString (strText);
			else
				iRes = ((CListBox *) pCWnd) -> AddString (strText);								
			if (iRes < 0)
			{
				DEX_Error (RC_OutputTableNamesCODBCInfos, EC_NOMEMORY);
			}
			else
			{
				pFunctArr [uIndex] = ++uResID;							
				uIndex++;    
			}
		}
		CATCH (CMemoryException, me)
		{        
			THROW_LAST ();		// diese Exception zum nächsten Handler
		}
		END_CATCH			
	}
}	 	

//	lese Version des Administrators
int GetOdbcAdminVersion ()
{
	int iRet = OdbcAdminVersion;		//	Returnwert 
	BYTE *pInfo = NULL;
	
	try
	{
		CString strFileName;
		VERIFY (strFileName.LoadString (IDS_ADMIN_EXE));
		
	//	lese Größe der zu erwartenden Info
		DWORD dwHandle = 0;
		DWORD dwLen = GetFileVersionInfoSize ((char*)(const char*)strFileName, &dwHandle);
		if (0 == dwLen)
			AfxThrowUserException ();

	//	Feld für diese Info anlegen
		pInfo = new BYTE [dwLen];
		memset (pInfo, 0, dwLen * sizeof (BYTE));		//	Feld init.

	//	lese FileVersion
		if (!GetFileVersionInfo ((char *)(const char *)strFileName, dwHandle, dwLen, pInfo))
			AfxThrowUserException ();

	//	lese FileInfo
		VS_FIXEDFILEINFO *pFixedFileInfo = NULL;
		UINT uiLen = 0;
		if (!VerQueryValue (pInfo, "\\", (LPVOID*) &pFixedFileInfo, &uiLen))
			AfxThrowUserException ();
		ASSERT (NULL != pFixedFileInfo);

		iRet = HIWORD (pFixedFileInfo->dwFileVersionMS);
	}
	catch (CMemoryException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
	catch (CUserException *u)
	{
		u -> Delete ();			//	nur auffangen
	}

//	Speicher ggf. freigeben
	DELETE_VEC (pInfo);

	return iRet;
}

		    
