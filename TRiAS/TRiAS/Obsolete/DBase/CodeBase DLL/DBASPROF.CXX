// Routinen, die aus einer INI-Datei die gewuenschten Info's rausholen
// File: DBASPROF.CXX
// Stand vom 29.6.1995

#include <d4all.h>

#include "dbasprof.htp"
#ifdef WIN32
#include <bool.h>
#endif
#include <commonvu.hxx>
#ifndef WIN32
#include <storage.h>		// LPSTORAGE
#endif
#include <xtension.h>	   	// für DEX_Error (), DEX_SetError ()
#include <xtensnx.h>
#include <protos.h>			// DELETE ()
#include <dbaserel.hxx>	 	// DBaseRel
#include <dbasprof.hxx>	 	// zugeh. Header
#include "dbasedll.hr"           // Resourcen-Defines
					
extern "C" {					
extern char pDLLName[_MAX_PATH];
} 

inline
HRESULT ClassFromIdentX (ULONG ulIdent, char *pBuffer, int iBuffLen)
{
CLASSFROMIDENT CFI;

        INITSTRUCT(CFI, CLASSFROMIDENT);
        CFI.ulIdent = ulIdent;
        CFI.pClass = pBuffer;
        CFI.iBuffLen = iBuffLen;
        if (NULL != pBuffer && iBuffLen > 0)
                pBuffer[0] = '\0';
        return DEX_GetClassFromIdent(CFI);
}

// Konstruktor --------------------
__export DBaseProFile :: DBaseProFile (void) {
	_FullName = NULL;		   // für alle Fälle
	ResourceFile RF (pDLLName);

	char *pProject = new char [_MAX_PATH];
	char *pDrive = new char [_MAX_DRIVE];
	char *pDir = new char [_MAX_DIR];
	char *pName = new char [_MAX_FNAME];
	
//	prüfe Speicher-Anforderung
	if (!pProject || !pDrive || !pDir || !pName)
	{
		DEX_Error (RC_ctDBaseProFile, EC_NOMEMORY);
		DELETE_VEC (pProject);
		DELETE_VEC (pDrive);
		DELETE_VEC (pDir);
		DELETE_VEC (pName);
		return;
	}	

//  Dateinamen der ProfileDatei neu generieren
	DEX_GetActiveProject (pProject);
	if (!*pProject)     
	{
		DELETE_VEC (pProject);
		DELETE_VEC (pDrive);
		DELETE_VEC (pDir);
		DELETE_VEC (pName);		
		return;
	}		
	_splitpath (pProject, pDrive, pDir, pName, NULL);
	_FullName = new char [_MAX_PATH];

	if (_FullName != NULL)
	// vollen ProFileNamen zusammenbauen
		_makepath (_FullName, pDrive, pDir, pName,
				   ResString (ResID (IDS_INIEXT, &RF), _MAX_EXT));

//  Speicher freigeben
	DELETE_VEC (pDrive);
	DELETE_VEC (pDir);
	DELETE_VEC (pName);
	DELETE_VEC (pProject);
}

// Destruktor
__export DBaseProFile :: ~DBaseProFile (void) {
	DELETE_VEC (_FullName);
}

// Einlesen der zu einem Ident gehörenden dBASE-Information ----------------
Bool __export DBaseProFile :: ReadDBaseEntry (long Ident, pchar pBuffer,
									 short BufferSize) {
//  prüfe Parameter
	if (_FullName == NULL || pBuffer == NULL)
		return False;

	ResourceFile RF (pDLLName);
	ResString DBaseInfo (ResID (IDS_DBASEKEY, &RF), 13);
	char IdKey [30] = "";

//  für bestimmten Id liefern
	if (Ident != -1) 
	{   
		char Buffer [30] = "";
		if (FAILED(ClassFromIdentX (Ident, Buffer, sizeof(Buffer))) || !*Buffer)
			return False;
		wsprintf (IdKey, "%s%s", (const char *)ResString (ResID (IDS_PROFID, &RF), 3), Buffer);
		return GetPrivateProfileString (DBaseInfo.Addr (), IdKey, "", pBuffer,
			   BufferSize, _FullName) != 0;
	}

	return False;
}

// Schreiben der zu einem Ident gehörenden dBASE-Information ----------------
Bool __export DBaseProFile :: WriteDBaseEntry (long Ident, pchar pBuffer) {
//  prüfe Parameter
	if (_FullName == NULL || pBuffer == NULL)
		return False;

	ResourceFile RF (pDLLName);
	ResString DBaseInfo (ResID (IDS_DBASEKEY, &RF), 13);
	char IdKey [30] = "";

//  für bestimmten Id liefern
	if (Ident != -1) 
	{
		char Buffer [30] = "";
		if (FAILED(ClassFromIdentX (Ident, Buffer, sizeof(Buffer))) || (!*Buffer))
			return False;
		wsprintf (IdKey, "%s%s", (const char *)ResString (ResID (IDS_PROFID, &RF), 3), Buffer);
		return WritePrivateProfileString (DBaseInfo.Addr (), IdKey, pBuffer, _FullName);
	}

	return False;
}


// Einlesen der zu einem Objekt gehörenden DBase MerkmalsCodes ----------------
int __export DBaseProFile :: ReadDBaseCodes (long **MKs, char ***MStrs, long Ident) {

	if (_FullName == NULL) 
		return 0;

	ResourceFile RF (pDLLName);

	ResString DBaseInfo (ResID (IDS_DBASEKEY, &RF), 13);
	char IdKey[30];
	char *PString = "";
	Bool PStringAllocated = FALSE;
	short Cnt = 0;		  // Anzahl der MerkmalsCodes

// 	für bestimmten Id liefern
	if (Ident != -1) 
	{
		char Buffer [30] = "";
		if (FAILED(ClassFromIdentX (Ident, Buffer, sizeof(Buffer))) || (!*Buffer))
			return 0;
		wsprintf (IdKey, "%s%s", (const char *)ResString (ResID (IDS_PROFID, &RF), 3), Buffer); 
		
	// 	Anzahl der MerkmalsCodes lesen
		ResString Dir (ResID (IDS_DBASESUBDIR, &RF), 10);
		Cnt = GetPrivateProfileInt (Dir.Addr (), IdKey, 0, _FullName);
		if (Cnt > 0) 
		{
		// Feld für ProfileString anfordern
			PString = new char [(Cnt+1)*80+1];
			if (PString == NULL) 		  // kein Speicher mehr
			{
				*MKs = NULL;
				*MStrs = NULL;
				return 0;
			}
			PStringAllocated = TRUE;

		// 	MerkmalsCodes selbst lesen
			GetPrivateProfileString (DBaseInfo, IdKey, "", PString, (Cnt+1)*80, _FullName);
		}
	} 

// 	wenn nichts da, dann Standard liefern
	if (!lstrcmp (PString, "")) 
	{
		ResString Standard (ResID (IDS_STANDARD, &RF), 20);

	// 	Anzahl der MerkmalsCodes lesen
		Cnt = GetPrivateProfileInt (DBaseInfo, Standard, 0, _FullName);
		if (Cnt > 0) 
		{
		// 	Feld für ProfileString anfordern
			PString = new char [(Cnt+1)*80+1];
			if (PString == NULL) 		  // kein Speicher mehr
			{
				*MKs = NULL;
				*MStrs = NULL;
				return 0;
			}
			PStringAllocated = TRUE;

		// 	MerkmalsCodes selbst lesen
			GetPrivateProfileString (DBaseInfo, Standard, "", PString, (Cnt+1)*80, _FullName);
		}
	}

// 	wenn nicht gegeben ist, wieder raus
	if (Cnt == 0) 
	{ 
		if (PStringAllocated) 
			DELETE_VEC (PString);
		*MKs = NULL; 
		*MStrs = NULL;
		return 0; 
	}

// 	MKFeld anfordern
	*MKs = new long [Cnt];
	*MStrs = new char * [Cnt];
	if (*MKs == NULL || *MStrs == NULL) 
	{
		if (PStringAllocated)
			DELETE_VEC (PString);
		DELETE_VEC (*MKs);
		*MKs = NULL;
		*MStrs = NULL;
		return 0;
	}

// 	MerkmalsCodes konvertieren
	register char *cptr = strchr (PString, ',');		  // 1. Komma suchen
	int i = 0;

	while (i < Cnt) 
	{
		if (cptr == NULL) 
		{
			(*MKs)[i] = -1L;		// Default
			(*MStrs)[i] = NULL;
			break;  // abbrechen
		}

	// 	entweder MerkmalsCode, Tag oder direkt Merkmalswert
		char Quote = *(cptr+1);
		if (Quote == '\"' || Quote == 39 /*'''*/ || Quote == 96 /*'\`'*/ || Quote == '<') 
		{
		// bereits Wert/Tag gegeben
			if (Quote == 96 /*'\`'*/) 
			{
				Quote = '\'';
				(*MKs)[i] = -2L;		// DBaseExpr gegeben
			} else 
				if (Quote == '<') 
				{
					Quote = '>';
					(*MKs)[i] = -3L;		// Tag gegeben
				} else
					(*MKs)[i] = -1L;		// MerkmalsWert gegeben
					
			(*MStrs)[i] = new char [lstrlen (cptr+2)+1];
			if ((*MStrs)[i] == NULL) 
				break;		  // Fehler und raus
			lstrcpy ((*MStrs)[i], cptr+2);  // Merkmalswert

		// 	QuoteChar am Ende rausnehmen
			char *tmpPtr;

			if ((tmpPtr = strchr ((*MStrs)[i], Quote)) != NULL)
				*tmpPtr = '\0';
			// 	Zeichensatz konvertieren
			OemToAnsi ((*MStrs)[i], (*MStrs)[i]);
		} 
		else 
		{
		// 	nur MerkmalsCode gegeben
			(*MKs)[i] = strtoul (cptr+1, NULL, DEX_GetMkBase ());	  // MK konvertieren
			(*MStrs)[i] = NULL;			 // kein Merkmalswert
		}
		cptr = strchr (cptr+1, ',');	// nächsten MK suchen
		i++;
	}		// while

// 	Speicher wieder freigeben
	if (PStringAllocated) 
		DELETE_VEC (PString);

	return i;	   // real gelesene Werte
}

// Einlesen der zu einem Objekt gehörenden DBase MerkmalsCodes ----------------
// Analysiert folgendes Format
//
// für den StandardFall:
// [DBaseRelations]
//	  MasterDB:MasterField = n,SlaveDB1:SlaveField1, ... ,SlaveDBn:SlaveFieldn
//
// für einen bestimmten Ident:
// [DBaseRelations Id12345678]
//	  MasterDB:MasterFiled = n,SlaveDB1:SlaveField1, ... ,SlaveDBn:SlaveFieldn
//
int __export DBaseProFile :: ReadDBaseRelations (DBaseRel &Master, DBaseRel ***pppDR, long Ident) 
{
	if (_FullName == NULL) 
		return 0;

	ResourceFile RF (pDLLName);

	char IdKey[40];
	char *PString = "";
	Bool PStringAllocated = FALSE;
	short Cnt = 0;		  // Anzahl der Relationen

// 	Namen der Sektion generieren
	lstrcpy (IdKey, ResString (ResID (IDS_DBASERELINFO, &RF), 20));

	if (Ident != -1L) 
	{		
		char Buffer [30] = "";
		if (FAILED(ClassFromIdentX (Ident, Buffer, sizeof(Buffer))) || (!*Buffer))
			return 0;
		wsprintf (IdKey, " %s%s", (const char *)ResString (ResID (IDS_PROFID, &RF), 3), Buffer);
	}			   

// 	Anzahl der Relationen lesen
	char MasterEntry[25];

	lstrcpy (MasterEntry, Master.GetDBName());
	lstrcat (MasterEntry, ":");
	lstrcat (MasterEntry, Master.GetFieldName());
	Cnt = GetPrivateProfileInt (IdKey, MasterEntry, 0, _FullName);

	if (Cnt > 0) 
	{
	// 	Feld für ProfileString anfordern
		PString = new char [(Cnt+1)*80+1];
		if (PString == NULL) 		  // kein Speicher mehr
		{
			*pppDR = NULL;
			return 0;
		}
		PStringAllocated = TRUE;

	// 	MerkmalsCodes selbst lesen
		GetPrivateProfileString (IdKey, MasterEntry, "", 
								 PString, (Cnt+1)*80, _FullName);
	}

// 	wenn nicht gegeben ist, wieder raus
	if (Cnt == 0) 
	{ 
		if (PStringAllocated) DELETE_VEC (PString);
			*pppDR = NULL;
		return 0; 
	}

// 	RelationsFeld anfordern
	*pppDR = new DBaseRel* [Cnt];
	if (*pppDR == NULL) 
	{
		if (PStringAllocated) DELETE_VEC (PString);
			return 0;
	}

// 	Relationen konvertieren
	register char *cptr = strchr (PString, ',');		  // 1. Komma suchen
	int i = 0;
	while (i < Cnt) 
	{
		if (cptr == NULL) 
		{
			(*pppDR)[i] = NULL;	 // Default
			break;  // abbrechen
		}

		char *pDBName = cptr+1;
		char *pField = strchr (pDBName, ':');
	
		if (pField) 
		{
			*pField = '\0';
			pField++;

		// 	nächster Eintrag
			cptr = strchr (pField, ',');
			if (cptr) 
				*cptr = '\0';
			(*pppDR)[i] = new DBaseRel (pDBName, pField);
			if ((*pppDR)[i] == NULL) 
				break;		  // Fehler und raus

		// 	Zeichensatz konvertieren
			(*pppDR)[i] -> OemToAnsi();
		}
		i++;
	}

// 	Speicher wieder freigeben
	if (PStringAllocated) 
		DELETE_VEC (PString);

	return i;	   // real gelesene Werte
}                     

//	lese über AliasNamen den zugehör. AliasFileNamen
// 	Speicher ist freizugeben
char* __export DBaseProFile :: GetAliasFileName (char *pAliasName)
{       
//	prüfe Parameter                                            
	if (!_FullName || !*_FullName || !pAliasName || !*pAliasName) 
		return NULL;             
		           
//	lade Section Name		           
	ResourceFile RF (pDLLName);
	ResString Section (ResID (IDS_ALIAS_FILES, &RF), 20);	
	char *pFileName = new char [_MAX_PATH];
	if (!pFileName)
		return NULL;
		
	if (GetPrivateProfileString (Section.Addr (), pAliasName, "",pFileName, 
								 _MAX_PATH, _FullName))
	{								 
	//	existiert Datei ?
		OFSTRUCT of;
		if (OpenFile (pFileName, &of, OF_EXIST) != HFILE_ERROR)
			return pFileName;
	}		
	
	DELETE_VEC (pFileName);
	return NULL;												 	
}

//	schreibe über AliasNamen den zugehör. AliasFileNamen
Bool __export DBaseProFile :: WriteAliasFileName (char *pAliasName, char *pFileName)
{       
//	prüfe Parameter                                            
	if (!_FullName || !*_FullName || !pAliasName || !*pAliasName 
		|| !pFileName || !*pFileName) 
		return False;             

//	existiert diese Datei ?		
	OFSTRUCT of;
	if (OpenFile (pFileName, &of, OF_EXIST) == HFILE_ERROR)
		return False;
		           
//	lade Section Name		           
	ResourceFile RF (pDLLName);
	ResString Section (ResID (IDS_ALIAS_FILES, &RF), 20);	
	return WritePrivateProfileString (Section.Addr (), pAliasName, 
		   pFileName, _FullName);
}

                
/*                
// CAliasFieldProFile --------------------------------------------
__export CAliasFieldProFile :: CAliasFieldProFile (void)
{
	m_pFileName = NULL;
	m_sMaxCnt = 0;
}

__export CAliasFieldProFile :: ~CAliasFieldProFile (void)
{
	DELETE (m_pFileName);
}
    
//	Profile-Namen aus der akt. Projekt-Ini lesen    
Bool __export CAliasFieldProFile :: Init (char *pAliasName) 
{
//	prüfe Parameter
	if (!pAliasName)
	{
		DEX_Error (RC_InitCAliasFieldPF, EC_ILLPARS);
		return False;
	}			    
	
//	prüfe Wert
	if (!*pAliasName)
		return False;	 
	
//	alten Parameter löschen
	DELETE (m_pFileName);
	m_sMaxCnt = 0;			

//	Namen der Projekt-Ini lesen
	ResourceFile RF (pDLLName);
	char *pProject = new char [_MAX_PATH];
	char *pDrive = new char [_MAX_DRIVE];
	char *pDir = new char [_MAX_DIR];
	char *pName = new char [_MAX_FNAME];
	m_pFileName = new char [_MAX_PATH];

//	prüfe Speicher-Anforderung
	if (!pProject || !pDrive || !pDir || !pName || !m_pFileName)
	{
		DEX_Error (RC_InitCAliasFieldPF, EC_NOMEMORY);
		DELETE (pProject);
		DELETE (pDrive);
		DELETE (pDir);
		DELETE (pName);
		DELETE (m_pFileName);
		return False;
	}	
	
//  Dateinamen der ProfileDatei neu generieren
	DEX_GetActiveProject (pProject);
	if (!*pProject) 
	{
		DELETE (pProject);
		DELETE (pDrive);
		DELETE (pDir);
		DELETE (pName);
		DELETE (m_pFileName);		
		return False;
	}		
	_splitpath (pProject, pDrive, pDir, pName, NULL);
	_makepath (pProject, pDrive, pDir, pName, ResString (ResID (IDS_INIEXT, &RF), _MAX_EXT));
	DELETE (pDrive);
	DELETE (pDir);
	DELETE (pName);

//	jetzt ProFile-Datei-Namen lesen
	ResString Section (ResID (IDS_AL_FIELD_FILES, &RF), 30);
	*m_pFileName = '\0';
	GetPrivateProfileString (Section.Addr (), pAliasName, "", m_pFileName, _MAX_PATH,
							 pProject);
	
//	FileName vorhanden ?
	if (!*m_pFileName)
	{               
		DELETE (pProject);
		DELETE (m_pFileName)
		return False;
	}		
	
//	Datei öffnen
    OFSTRUCT of;
    HFILE hFile;
    if ((hFile = OpenFile (m_pFileName, &of, OF_READ)) ==  HFILE_ERROR)
    {   
    	DELETE (pProject);
    	DELETE (m_pFileName);
    	return False;
    }
				
//	jetzt MaxCnt ermitteln					 
	char *pF = NULL;
	while (_lread (hFile, pProject, _MAX_PATH) > 0)
	{
		if ((pF = strchr (pProject, '=')) && *++pF)
			m_sMaxCnt = max (m_sMaxCnt, lstrlen (pF));
	}		

	DELETE (pProject);	
	_lclose (hFile);
	return True;					 
}

// lesen zugeh. Aliasnamen, Speicher ist explizit freizugeben
char* __export CAliasFieldProFile :: GetAliasName (char *pFieldName)
{                                                                   
//	prüfe Parameter
	if (!pFieldName || !*pFieldName || !m_pFileName || !*m_pFileName || !m_sMaxCnt)
		return NULL;
        
	ResourceFile RF (pDLLName);	        
	ResString Section (ResID (IDS_FA_NAMES, &RF), 30);	
			                                       
	char *pAliasName =	new char [m_sMaxCnt + 1];
	if (!pAliasName)
	{
		DEX_Error (RC_GetAilasNameCAliasFieldPF, EC_NOMEMORY);		
		return NULL;
	}
	
	if (GetPrivateProfileString (Section.Addr (), pFieldName, "", pAliasName, 
								 m_sMaxCnt, m_pFileName))
		return pAliasName;
	else
		DELETE (pAliasName);
		
	return NULL;
}
*/
