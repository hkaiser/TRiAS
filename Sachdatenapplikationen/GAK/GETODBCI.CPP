//	FILE: GETODBCI.CPP
//
// 	Erarbeitet: J. Benkenstein			Stand vom 28.6.1997

#include "stdafx.h" 			//	prec. Header
#include "gak.h"				//	Resource-Konstanten

#include <odbcinst.h>			// SQLValidDSN ()
// #include <io.h>    				//  _access ()

#include "getodbci.h"			// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//	DSN ändern (Administrator rufen)
BOOL ChangeDataSource (HWND hWnd, const char *pInDSN)
{
	ASSERT (pInDSN != NULL && AfxIsValidString (pInDSN));
	ASSERT (NULL != hWnd);

	const short DSNBufferSize = 128;
	const short DriverBufferSize = 128;

	try
	{                
	//	Puffer für DSN anlegen
		CString strDSN;
		char *pDSN = strDSN.GetBuffer (DSNBufferSize);
		memset (pDSN, 0, DSNBufferSize);
		
	//	akt. DSN zusammenbauen                 
		CString strKennung;
		VERIFY (strKennung.LoadString (IDS_DSNGLEICH));	// Kennung lesen: "DSN="
		if (:: LoadString (AfxGetInstanceHandle (), IDS_DSNGLEICH, pDSN, DSNBufferSize))	
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
						   				    DriverBufferSize, strFileName))
				SQLConfigDataSource (hWnd, ODBC_CONFIG_DSN, pDriver, pDSN); 	// DSN konfigurieren
			else
				SQLCreateDataSource (hWnd, pInDSN);				
			return TRUE;
		}
	}
	catch (CMemoryException *me)  
	{   
		me -> ReportError ();
		me -> Delete ();
	}
	
	return FALSE;
}	

//	schreibe ODBC-Path
BOOL WriteOdbcPath (const char *pPath)
{
	ASSERT (NULL != pPath && AfxIsValidString (pPath));

	try
	{
		CString strFileName, strSection, strEntry;
		VERIFY (strFileName.LoadString (IDS_ODBCINI));
		VERIFY (strSection.LoadString (IDS_DSN_GAK));
		VERIFY (strEntry.LoadString (IDS_DEFAULT_DIR));

		return SQLWritePrivateProfileString (strSection, strEntry, pPath, strFileName);
	}
	catch (CMemoryException *me)  
	{   
		me -> ReportError ();
		me -> Delete ();
	}

	return FALSE;
}

//	lese ODBC-Path
BOOL GetDataPath (CString &strDir)
{
	try
	{
		char Buffer [_MAX_PATH] = "";
		CString strFileName, strSection, strEntry;
		VERIFY (strFileName.LoadString (IDS_ODBCINI));
		VERIFY (strSection.LoadString (IDS_DSN_GAK));
		VERIFY (strEntry.LoadString (IDS_DEFAULT_DIR));
		if (SQLGetPrivateProfileString (strSection, strEntry, "", Buffer, 
						   				_MAX_PATH, strFileName))
		{
			strDir = Buffer;
			return TRUE;
		}			
		else
			strDir.Empty ();
	}
	catch (CMemoryException *me)  
	{   
		me -> ReportError ();
		me -> Delete ();
	}

	return FALSE;
}	

/*
//	diese Funktion überprüft die Gültigkeit eines ODBC-Eintrages:
//	- existiert das bei "DBQ" angegebene Datenbank ?
BOOL DSNParamOk (const char *pDSN)
{
//	prüfe Parameter
	if (!pDSN || !*pDSN)
		return FALSE;	

	BOOL bRet = FALSE;

//	lese Verzeichnis-Eintrag		
	try
	{
		CString strFileName, strEntry, strPath;
		strFileName.LoadString (IDS_ODBCINI);
		strEntry.LoadString (IDS_DEFAULT_DIR);
		char *pPath = strPath.GetBuffer (_MAX_PATH);			

		return SQLGetPrivateProfileString (pDSN, strEntry, "", pPath, _MAX_PATH, strFileName) && 
			   (_access (pPath, 0) == 0) ? TRUE : FALSE;
	}
	catch (CMemoryException *me)
	{                  
		me -> ReportError ();
		me -> Delete ();
	}
	
	return bRet;
}           
*/
	
//	wenn Data-Source in ODBC-INI existiert, dann TRUE sonst FALSE
BOOL ExistDataSource (const char *pDSN)
{       
//	prüfe Parameter
	if (!pDSN || !*pDSN)
		return FALSE;					

	const short BufferSize = 1024;		// Ini-Lese-Puffer
	
	try
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
	}
	catch (CMemoryException *me)  
	{   
		me -> ReportError ();
		me -> Delete ();
	}
	
	return FALSE;		
}



