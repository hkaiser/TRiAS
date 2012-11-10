//	FILE: GETODBCI.H
//
// 	Erarbeitet: J. Benkenstein			Stand vom 28.6.1997

#ifndef _GETODBCI_H
#define _GETODBCI_H

                             
//	True, wenn das unter "DBQ" angegebene Verzeichnis im DSN existiert                             
BOOL DSNParamOk (const char *pDSN);

//	wenn Data-Source in ODBC-INI existiert, dann TRUE sonst FALSE
BOOL ExistDataSource (const char *pDSN);

//	TRUE, wenn neuer DSN-erzeugt wurde
BOOL CreateNewDataSource (HWND hWnd);	// Administrator rufen

//	TRUE, wenn DataSource geändert wurde, sonst FALSE
BOOL ChangeDataSource (HWND hWnd, const char *pDSN);

//	Datenverzeichnis lesen
BOOL GetDataPath (CString &strDir);

//	schreibe ODBC-Path
BOOL WriteOdbcPath (const char *pPath);

#endif	// _GETODBCI_H
