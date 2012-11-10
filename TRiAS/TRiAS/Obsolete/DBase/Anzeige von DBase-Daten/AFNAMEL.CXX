/*
File: AFNAMEL.CXX

Das Mudul verwaltet Einträge einer Text-Datei in der Section
	<FeldName>=<AliasFeldName>    
die einer dBASE-Datei in der Projekt-INI über den Eintrag
	[dBASE-AliasFiles]
	<AliasName>=<AliasDateiName>
zugeordnet werden können.

Erarbeitet: J. Benkenstein						Stand vom 11.9.1995		
*/             

#include "pheader.h"

#include <dbasprof.hxx>	 			// DBaseProFile
#include <containr.hxx>
#include "afnamel.hxx"				// zugeh. Header

// Konstanten                     
const char ProFileSep = '=';		// Profile-Separator 
const short MaxRowLen = 126;		// max. Länge in Profile-Datei
    
// globale Funktionen -------------------------------------------------------------
void* GetFieldName (void *pObj) 
{
	return ((CAliasFieldName *) pObj) -> FieldName ();
}           
	             
// 	CAliasFieldName ---------------------------------------------------------------
CAliasFieldName :: ~CAliasFieldName (void)
{
	DELETE_VEC (m_pFieldName);
	DELETE_VEC (m_pAliasName);
}                         

Bool CAliasFieldName :: Init (char *pFieldName, char *pAliasName)
{               
	if (!pFieldName || !pAliasName || !*pFieldName || !*pAliasName)
		return True;
		
	m_pFieldName = new char [lstrlen (pFieldName) + 1];
	m_pAliasName = new char [lstrlen (pAliasName) + 1];
	if (!m_pFieldName || !m_pAliasName)
	{
		DEX_Error (RC_InitCAliasFieldName, EC_NOMEMORY);
		return False;
	}		         
	
//	Namen speichern
	lstrcpy (m_pFieldName, pFieldName);
	strupr (m_pFieldName);					// Suchschlüssel nur in Großbuchstaben
	lstrcpy (m_pAliasName, pAliasName);

	return True;
}

// CAliasFieldNameTree ------------------------------------------------------------
CAliasFieldNameTree :: CAliasFieldNameTree (void)
					 : CTree (GetFieldName)
{
	m_sMaxAlCnt = 0;			// max. Zeichenlänge rücksetzen	
}					 

CAliasFieldNameTree :: ~CAliasFieldNameTree (void)
{
	EveryDelete ();
}					 		          
		        
void __export CAliasFieldNameTree :: UserDelete (void *pObj)
{
	((CAliasFieldName *) pObj) -> ~CAliasFieldName ();	
}	

//	lese zugeh. AliasNamen über Feldnamen	                                      
char* CAliasFieldNameTree :: GetAliasName (char *pFieldName)
{
//	prüfe Parameter
	if (!pFieldName || !*pFieldName)
		return NULL;
	                         
	ErrCode EC = EC_OKAY;
	CTable tb (*this);
	if (tb.Find (pFieldName))
	{
		if (tb.Valid ())
		{
			CAliasFieldNameLock pA (tb);		
			if (pA)
				return pA -> AliasName ();
			else
				EC = EC_LOCKERROR;
		}
		else
			EC = EC_SYSERROR;
	}                        
	
//	ggf. Fehlermeldung ausgeben
	if (EC != EC_OKAY)
	{
		DEX_Error (RC_GetAliasNameCAliasFieldNameTree, EC);
	}		
	                                               
	return NULL;	                                               
}               
    
//	alle Einträge aus der zugeh. INI-Datei lesen
//	max. Text-Länge eines Eintrages ermitteln
Bool CAliasFieldNameTree :: Init (char *pAliasName)
{
//	prüfe Parameter
	if (!pAliasName || !*pAliasName)
		return False;
                     
//	lese Profile-Datei-Namen aus der Projekt-Ini                     
	DBaseProFile ProFile;
	char *pFileName = ProFile.GetAliasFileName (pAliasName);
	if (!pFileName)
		return False;

//	Datei öffnen 
    FILE *pFile; 
    if ((pFile = fopen (pFileName, "rt")) == NULL)
    {           
    	DELETE_VEC (pFileName);
    	return False;
    }
				
//	ProfileBuffer anlegen
	char *pBuffer = new char [MaxRowLen];
	if (!pBuffer)
	{
		DELETE_VEC (pFileName);
		DEX_Error (RC_InitCAliasFieldNameTree, EC_NOMEMORY);
		return False;
	}                       
	
//	alle Einträge lesen	
	char *pAName = NULL;
	Bool bRet = True;
	while (fgets (pBuffer, MaxRowLen, pFile))
	{                                                
	//	Zeile-Ende setzen
		pBuffer [lstrlen (pBuffer) - 1] = '\0';		
	   
	//	eine mögliche Zeile lesen                       
		if ((pAName = strchr (pBuffer, ProFileSep)) && *++pAName)
		{                                                 
			pAName [-1] = '\0';			// Trennungs-Zeichen setzen
			CAliasFieldNameCreator AFN (*this);
			CAliasFieldName *pAFN = Create (AFN, CAliasFieldName);
			if (pAFN && pAFN -> Init (pBuffer, pAName))
				m_sMaxAlCnt = max (m_sMaxAlCnt, lstrlen (pAName));
			else
			{//	bei Fehler abbrechen
				bRet = False;
				break;
			}				
		}			
	}		
	fclose (pFile);
	
	if (bRet && m_sMaxAlCnt && Count ())	            
		Optimize ();			// Baum optimieren
	else
		m_sMaxAlCnt = 0;		// alle Einträge ungültig
	
//	Speicher freigeben                     
    DELETE_VEC (pBuffer);
	DELETE_VEC (pFileName);
	return bRet;				
}	    
