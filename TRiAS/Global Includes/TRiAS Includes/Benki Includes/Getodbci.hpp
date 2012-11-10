//	FILE: GETODBCI.HPP
//
// 	Erarbeitet: J. Benkenstein			Stand vom 1.10.94

#ifndef _GETODBCI_HPP
#define _GETODBCI_HPP

typedef enum { NoDataSource = 0,  UserDataSource, SystemDataSource, 
			   FileDataSource } DataSourceType;

typedef struct 
{
	DataSourceType tType;
	const char *pName;
}	DataSourceInfo;

#ifndef SQL_FETCH_FIRST_USER
#define SQL_FETCH_FIRST_USER				31
#endif
#ifndef SQL_FETCH_FIRST_SYSTEM
#define SQL_FETCH_FIRST_SYSTEM				32
#endif

//	True, wenn das unter "DefaultDir" angegebene Verzeichnis im DSN existiert                             
BOOL DSNParamOk (const char *pDSN, DataSourceType tType);

//	die verfügbaren Data-Source-Names aus der ODBC-INI lesen und in List/ComboBox ausgeben
BOOL GetDataSources (CWnd *pBox, DataSourceType tType);                                 

//	wenn Data-Source in ODBC-INI existiert, dann TRUE sonst FALSE
BOOL ExistDataSource (const char *pDSN, DataSourceType tType);

//	TRUE, wenn neuer DSN-erzeugt wurde
BOOL CreateNewDataSource (HWND hWnd, DataSourceType tType);	// Administrator rufen

//	TRUE, wenn DataSource geändert wurde, sonst FALSE
BOOL ChangeDataSource (HWND hWnd, const char *pDSN, DataSourceType tType);

//	FileSource über Dialog auswählen
BOOL SelectFileDataSource (CString &strDsn, CWnd *pParent = NULL);

//	lese Defaultverzeichnis für Filedatasources
void GetFileDataSourceDir (CString &strDir);

//	lese Version des Administrators
int GetOdbcAdminVersion ();

// Klasse zur Verwaltung von ODBC-Infos
class CDataBaseExt;
class CTables;
class CColumns;

class CODBCInfos
{   
protected:
//	prüfe und lese Beschreibungs-Info einer skalaren Funktion
	void GetScaleFunction (uint &uIndex, uint uResID,
						   UDWORD uwCheckFlag, UDWORD fFlag,
						   CWnd *pCWnd, UINT *pFunctArr);
public:
	CDataBaseExt *m_pDataBase;   	// Data-Source-Objekt
	CTables *m_pTables;				// Tabellen-Infos
	CColumns *m_pColumns;			// Spalten-Infos
	                        
//	Konstruktor/Destruktor              
	CODBCInfos (void);
	~ CODBCInfos (void);	
	
//	Zugriffs-Funktionen	
	BOOL CompleteImportInfo (void);

	BOOL CompleteInfo (void) { return ((m_pDataBase != NULL) && (m_pTables != NULL) &&
									   (m_pColumns != NULL)); } 
	
							// alten Objekte komplett löschen
							// Erzeugen und Öffnen eines Data-Source-Objektes
	CDataBaseExt *CreateDataBase (const char *pDataSourceName, DataSourceType tType);

							// geben Kommentar zum. aktuellen Data-Source-Objekt aus 
	BOOL OutputDataBaseInfo (CEdit &stDescription);
	                            
							// alten Table-Set löschen
							// neuen Tables-Set erzeugen und öffnen
                                                        // alle Tabellen-Namen in                                                                                                           
    BOOL OutputTableNames (CWnd *pBox);             // List/Combobox ausgeben
	                                                                 
							// gebe Kommentar zur angegebenen Tabelle in Beschr.-Feld aus	                                                                 
	BOOL OutputTableInfo (const char *pTableName, CEdit &stDescription);
	
							// gebe zur angegebenen Tabelle alle Koppelfelder in ListBox aus
							// erzeuge neues Columns-Objekt	
	BOOL OutputColumnNames (const char *pTableName, CComboBox &ColumnList,
							short sSQLType = -1); // für Typ-prüfung notwendig
	
							// gebe FeldInfo zum gegebenen Feld aus	                                    
	BOOL OutputColumnInfo (const char *pFieldName, CEdit &stDescription); 

	
//	weitere Member	
	void DeleteAll (void);				// alle zugeh. Objekte löschen	

	void DeleteAllNotDataSource (void);	// alles außer DataSource löschen

//	Funktionen des DataSources in ListBox/ComboBox ausgeben
	BOOL OutputFunctions (CWnd *pWnd, UINT *pFunctArray, UINT uiSize);
};

#endif	// _GETODBCI_HPP
