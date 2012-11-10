/*
File: TEXTCONN.CXX

Realisiert die Ausgabe aller Informationen in der aktuellen Projekt-INI-Datei 
und den ODBC-Dateien, die zur Anbindung von Texdateien über ODBC notwendig sind.

Erarbeitet: J. Benkenstein				Stand vom: 10. Mai 1995
*/              

#include "pheader.h"

#include <odbcinst.h>				// SQLConfigDataSource ()
#include "arctrias.hr"               // Resourcen-Konstanten

#include "textconn.hxx"			// zugeh. Header	

// Konstanten     
const short OdbcParSize = 6;
const char *ppOdbcStandPar [OdbcParSize] = 						// ODBC-Standard-Parameter	
{ 
	"Description=Text-Dateien",
	"FileType=Text",
	"ColNameHeader=True",		
	"Format=CSVDelimited",
	"MaxScanRows=2",	
	"CharacterSet=ANSI",
};

// CTextDatInfo ----------------------------------------------------------------------------------------------
CTextDatInfo :: CTextDatInfo (char *pNewName)
{              
//	alles rücksetzen                             
	m_bOpFlag = False;
	m_pName = NULL;	  
	                
//	Parameter prüfen	                
	if (!pNewName || !*pNewName)
		return;     
		
	m_pName = new char [lstrlen (pNewName) + 1];		
	if (!m_pName)
	{          
		DEX_Error (RC_ctCTextDatInfo, EC_NOMEMORY);
		return;
	}                                
	lstrcpy (m_pName, pNewName);
	
	m_bOpFlag = True;
}

CTextDatInfo :: ~CTextDatInfo (void)
{
        DELETE_VEC (m_pName);
}
                    
// CTextDatInfoList -------------------------------------------------------------------------------
CTextDatInfoList :: CTextDatInfoList (ResourceFile *pRF)
			      : CListContainer ()					
{
	m_pRF = pRF;
	m_pMaster = m_pKoppelFeld = NULL;
	m_lMKode = m_lIdent = 0;	
	m_TextDatLength = 0;
}
                    
CTextDatInfoList :: ~CTextDatInfoList (void)
{                       
        DELETE_VEC (m_pKoppelFeld);
        DELETE_VEC (m_pMaster);
	EveryDelete ();
}

void __export CTextDatInfoList :: UserDelete (void *pObj)
{                    
	((CTextDatInfo *) pObj) -> ~CTextDatInfo ();
}

BOOL CTextDatInfoList :: SetMaster (char *pMaster)
{
//	prüfe Parameter
	if (!pMaster || !*pMaster)
	{
		DEX_Error (RC_CTextDatListSetMaster, EC_ILLPARS);
		return FALSE;
	}	                    
	
	if (m_pMaster == NULL)	// wenn noch nicht gespeichert
	{
		m_pMaster = new char [lstrlen (pMaster) + 1];
		if (!m_pMaster)
		{
			DEX_Error (RC_CTextDatListSetMaster, EC_NOMEMORY);
			return FALSE;						
		}
		lstrcpy (m_pMaster, pMaster);			
		return TRUE;
	}                                
	else		// ein neuer 'Slave' ist gekommen
	{                                                          
		CTextDatInfoCreator TDI (*this);
		CTextDatInfo *pTD = ContCreate (TDI, CTextDatInfo) (pMaster);
		if (pTD && pTD -> OpFlag ())
		{
			m_TextDatLength += lstrlen (pMaster);
			return TRUE;
		}			    
		else
			return FALSE;
	}
}

BOOL CTextDatInfoList :: SetKoppelFeld (char *pFeld)
{
	if (m_pKoppelFeld)		// Feld bereits gesetzt
		return TRUE;                               
		               
//	prüfe Parameter
	if (!pFeld || !*pFeld)
	{                	
		DEX_Error (RC_CTextDatListSetKopp, EC_ILLPARS);
		return FALSE;
	}		               
	
//	ansonsten Feldnamen speichern                  
	m_pKoppelFeld = new char [lstrlen (pFeld) + 1];
	if (!m_pKoppelFeld)
	{
		DEX_Error (RC_CTextDatListSetKopp, EC_NOMEMORY);
		return FALSE;		
	}
	lstrcpy (m_pKoppelFeld, pFeld);				
				
	return TRUE;		
}

void CTextDatInfoList :: SetIdent (ulong lNewIdent)
{
	if (m_lIdent <= 0)        	// wenn noch keiner gesetzt
		m_lIdent = lNewIdent;
}

void CTextDatInfoList :: SetMKode (ulong lNewMKode)
{
	if (m_lMKode <= 0)
		m_lMKode = lNewMKode;
}
                                                  
// Alle Infos zur Anbindung ausgeben                                                     
// In Projekt-INI-Datei: Master-und Slave-Connections und ODBC-Infos
// OBDC-Section erzeugen
ErrCode CTextDatInfoList ::  OutputConnectInfos (void)
{   
	ErrCode EC = EC_OKAY;	
            
//	prüfe Parameter
	if (!m_pMaster || !m_pKoppelFeld || !m_lMKode || !m_lIdent)
		return EC;		// keine Anbindung definert
		
	if (!m_pRF)
	{
		DEX_Error (RC_CTextDatListOutCon, (EC = EC_ILLPARS));
		return EC;					       
	}		                             
	                                         
//	bilde INI-Projekt-Ini-Dateinamen	                                         
	char *pPath  = new char [_MAX_PATH];
	char *pDrive = new char [_MAX_DRIVE];
	char *pDir   = new char [_MAX_DIR];
	char *pFName = new char [_MAX_FNAME];
	char *pBuffer80 = new char [80];
	
	if (!pPath || !pDrive || !pDir || !pFName || !pBuffer80)
		EC = EC_NOMEMORY;
		
	if (EC == EC_OKAY)
	{             
		*pPath = '\0';
		DEX_GetActiveProject (pPath);		// Projekt-Namen lesen
		if (!*pPath)
			EC = EC_ILLPARS;
		else
		{                                           
			ResString IniExt (ResID (IDS_INIEXT, m_pRF), _MAX_EXT);
			_splitpath (pPath, pDrive, pDir, pFName, NULL);
			_makepath (pPath, pDrive, pDir, pFName, IniExt.Addr ());
			
		//	Speicher nicht mehr benötigt			
                        DELETE_VEC (pFName);
		}
	}
	                                         
//	Ident-Ankopplung ausgeben: dBase-Section schreiben
	if (EC == EC_OKAY)
	{                       
		short sMkBase = DEX_GetMkBase ();
	
	// 	Eintrag erzeugen	
		ResString IDFormat (ResID (IDS_IDFORMAT_IDENT, m_pRF), 10);		
		char Entry [30] = "";
		char tBuffer [30] = "";
		ClassFromIdentX (m_lIdent, tBuffer, sizeof(tBuffer));
		wsprintf (Entry, IDFormat.Addr (), tBuffer);
		
	//	Eintragswert erzeugen	
		ResString IdFormatVal (ResID (sMkBase == 10 ? IDS_FORMATVAL : IDS_FORMATVALX, m_pRF), 20);	
		wsprintf (pBuffer80, (pchar) IdFormatVal.Addr (), m_pMaster, m_pKoppelFeld, m_lMKode);		
		                                  
	//	Eintrag in INI-Datei ausgeben		                                  
		ResString dBaseSect (ResID (IDS_DBASESECTION, m_pRF), 10);	// Section lesen
		if (! WritePrivateProfileString (dBaseSect.Addr (), Entry, pBuffer80, pPath))
			EC = EC_SYSERROR;
	}
	
// 	ggf. weitere Relationen ausgeben: dBase-Relations
	if ((EC == EC_OKAY) && Count ())		// und Slave-Einträge vorhanden
	{                        
	//	EntryVal aufbauen                
		short Len = ((lstrlen (m_pKoppelFeld) + 2) * (short) Count ()) + 10 + m_TextDatLength;
		char *pRelEntryVal = new char [Len];
		if (!pRelEntryVal)
			EC = EC_NOMEMORY;
		else
		//	Anzahl der Slave-Einträge schreiben
			ltoa (Count (), pRelEntryVal, 10);
	                                
	//	alle Slavenamen lesen    
		CRing ri (*this);
		for (ri.First (); (EC == EC_OKAY) && ri.Valid (); ri.Next ())
		{   
			CTextDatInfoLock pTD (ri);
			if (!pTD) 
			{
				EC = EC_LOCKERROR;
				break;
			}				
			lstrcat (pRelEntryVal, ",");				
			lstrcat (pRelEntryVal, pTD -> GetName ());
			lstrcat (pRelEntryVal, ":");
			lstrcat (pRelEntryVal, m_pKoppelFeld);
		}

		if (EC == EC_OKAY)
		{
		//	Entry aufbauen
			ResString RelFormat (ResID (IDS_RELFORMAT, m_pRF), 10);
			wsprintf (pBuffer80, RelFormat.Addr (), m_pMaster, m_pKoppelFeld);				
		
		//	Section lesen
			ResString RelSec (ResID (IDS_RELATIONSECTION, m_pRF), 20);		

		//	Eintrag in INI-Datei schreiben
			if (! WritePrivateProfileString (RelSec.Addr (), pBuffer80, pRelEntryVal, pPath))
				EC = EC_SYSERROR;
		} 	
		
                DELETE_VEC (pRelEntryVal);          // Speicher freigeben                       
	}
    
// 	ODBC-Section erzeugen
	if (EC == EC_OKAY)
	{       
		const short ParamSize = _MAX_PATH * 3;                                       
		char *pNewDir = new char [_MAX_DIR + 30];
		char *pParams = new char [ParamSize];     
		
		if (pNewDir && pParams)
		{	
		//	variablen Parameter zusammenstellen: DSN
			ResString TextDriverDSN (ResID (IDS_TEXTDRDSN, m_pRF), 10);				
			wsprintf (pBuffer80, TextDriverDSN.Addr (), m_pMaster);
			
		//	DatenVerzeichnis		
			ResString TextDriverDir (ResID (IDS_TEXTDRDATADIR, m_pRF), 30);				
			wsprintf (pNewDir, TextDriverDir.Addr (), pDrive, pDir);
			if (pNewDir [lstrlen (pNewDir) - 1] == '\\')	// letzten Backslash abschneiden
				pNewDir [lstrlen (pNewDir) - 1] = '\0';
			
			ResString FileTyp (ResID (IDS_FILTYP, m_pRF), 20); 		// 	Typ lesen
			ResString DriverId (ResID (IDS_DRIVERID, m_pRF), 20);	// 	TreiberID lesen			

		//	alle Parameter summieren: Zuerst Standard-Parameter  
			memset (pParams, 0, ParamSize);
			short Pos = 0;
			short ActLen = Pos;
			ActLen = lstrlen (pBuffer80);		
			memcpy (pParams, pBuffer80, ActLen);
			Pos += ++ActLen;
			ActLen = lstrlen (pNewDir);
			memcpy (pParams + Pos, pNewDir, ActLen);
			Pos += ++ActLen;
			ActLen = lstrlen (FileTyp);
			memcpy (pParams + Pos, FileTyp, ActLen);
			Pos += ++ActLen;		
			ActLen = lstrlen (DriverId);
			memcpy (pParams + Pos, DriverId, ActLen);
			Pos += ++ActLen;		
			
		//	jetzt variable Parameter               
			for (short i = 0; i < OdbcParSize; i++)
			{                                          
				ActLen = lstrlen (ppOdbcStandPar [i]);
				memcpy (pParams + Pos, ppOdbcStandPar [i], ActLen);						
				Pos += ++ActLen;						
			}
			                                       
		//	Treiberkennung	
#ifdef WIN32						                                       
			ResString TextDriver (ResID (IDS_TEXTDRKENNUNG32, m_pRF), 50);
#else
			ResString TextDriver (ResID (IDS_TEXTDRKENNUNG, m_pRF), 50);
#endif	
				
		//	Section ausgeben
			SQLConfigDataSource (NULL, ODBC_ADD_DSN, TextDriver.Addr (), pParams);
		}
		else
			EC = EC_NOMEMORY;
			
                DELETE_VEC (pParams);
                DELETE_VEC (pNewDir);
	}

//	Data-Source-Names ausgeben
	if (EC == EC_OKAY)
	{                                                           
	//	Section lesen
		ResString ODBCSec (ResID (IDS_DATASOURCENAME, m_pRF), 30);        
		                                    
	//	Master-Anbindung als erstes schreiben		                                    
		if (! WritePrivateProfileString (ODBCSec.Addr (), m_pMaster, 
										 m_pMaster, pPath))	
			EC = EC_SYSERROR;										 				
		
		CRing rid (*this);
		for (rid.First (); (EC == EC_OKAY) && rid.Valid (); rid.Next ())
		{   
			CTextDatInfoLock pTDI (rid);
			if (!pTDI ||
				!WritePrivateProfileString (ODBCSec.Addr (), pTDI -> GetName (), 
											m_pMaster, pPath))					
			{
				EC = EC_LOCKERROR;
				break;
			}		
		}
		
	}
	             
//	Speicher freigeben
        DELETE_VEC (pPath);         
        DELETE_VEC (pDrive);
        DELETE_VEC (pFName);
        DELETE_VEC (pDir);
        DELETE_VEC (pBuffer80);
	
//	Fehlermeldung ggf. ausgeben	
	if (EC != EC_OKAY)                        
	{
		DEX_Error (RC_CTextDatListOutCon, EC);
	}             
	
	return EC;
}   
