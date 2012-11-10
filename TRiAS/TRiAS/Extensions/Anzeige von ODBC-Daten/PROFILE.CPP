// Routinen, die aus einer INI-Datei die gewuenschten Info's rausholen
// File: PROFILE.CPP
// Stand vom 11.4.1993
							
#include "pheader.h"                                                                          
#include "odbcext.hr"		// Resourcen							

#include <string.h>			// strchr ()
#include <hpp/strdup.hxx>		// StringDup		   
#include <hpp/relation.hpp>     // DBaseRel
#include <hpp/getodbci.hpp>		// DataSourceType
#include "profile.hpp"     	// zugeh. Header
#include <errinstx.hxx> // ErrInstall
#include <hpp/objinfo.hpp>		// KurzTextLen
#include "myhelper.h"
#include "features.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// externe Variablen
extern "C" HINSTANCE g_hInstance;
extern int g_sMkBase;	

// Konstanten
const short dBaseSectSize = 128;	 // richtig Stoff geb. brauch Platz
const short dBaseIdSize = 5;
const short DSNameSize = _MAX_PATH;
const short TableNameLength = 100;
const char NotOper [] = ".NOT.";		// Operatoren, die aus Kompatibilitäsgründen
const char OrOper [] = ".OR.";			// zu dBASE ersetzt werden müssen
const char AndOper [] = ".AND.";
const char NotOperL [] = ".not.";		
const char OrOperL [] = ".or.";	
const char AndOperL [] = ".and.";
const short MaxValSize = MAX_OKS_LENX+1;			// Zahlenpuffergröße
const short MaxKonvertBuffer = 128;		// max. Konvertpuffergr.
const short ReadAllBufferSize = 4096;

const TCHAR g_cbStandard[] = _T("Standard");
const TCHAR g_cbId[] = _T("ID");
// const TCHAR g_cbODBC[] = _T("ODBC");	// Globaler String der Section für die Verbindungen



// Konstruktor --------------------

Profile::Profile (void) 
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

//  Dateinamen der ProfileDatei neu generieren
	_pFullName = NULL;
	TRY {
		CString strDrive ('\0', _MAX_DRIVE),
				strDir ('\0', _MAX_DIR),
				strFName ('\0', _MAX_FNAME),
				strProject ('\0', _MAX_PATH);

		_pFullName =  new char [_MAX_PATH];
		*_pFullName = '\0';
		if (DEX_GetActiveProject ((const char *)strProject))
		{
			_splitpath (strProject, (char *)(const char *)strDrive, 
									(char *)(const char *)strDir, 
									(char *)(const char *)strFName, NULL);
    
		//  vollen ProFileNamen zusammenbauen
		CString strExt;
		
			VERIFY (strExt.LoadString (IDS_INIEXT));
			_makepath (_pFullName, strDrive, strDir, strFName, strExt);
			m_hPr = DEX_GetDataSourceHandle();
		}
		else {
			DELETE_VEC (_pFullName);
		}
	}
	CATCH (CMemoryException, cme)
	{      
		DEX_Error (RC_Profile, EC_NOMEMORY);
	}
	END_CATCH        
}

#define DECLARE_CHAR(name, len) \
	char name[len];\
	name[0] = '\0';

// Konstruktor --------------------
Profile::Profile (HPROJECT hPr) 
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

//  Dateinamen der ProfileDatei neu generieren
	_pFullName = NULL;
	TRY {
		DECLARE_CHAR(strDrive, _MAX_DRIVE);
		DECLARE_CHAR(strDir , _MAX_DIR);
		DECLARE_CHAR(strFName , _MAX_FNAME);
		DECLARE_CHAR(strProject , _MAX_PATH);

/*		CString strDrive ('\0', _MAX_DRIVE),
				strDir ('\0', _MAX_DIR),
				strFName ('\0', _MAX_FNAME),
				strProject ('\0', _MAX_PATH);
*/
		_pFullName =  new char [_MAX_PATH];
		*_pFullName = '\0';
		if (DEX_GetDataSourceName(hPr, (const char *)strProject))
//		if (DEX_GetActiveProject ((const char *)strProject))
		{
			_splitpath (strProject, /*(char *)(const char *)*/strDrive, 
									/*(char *)(const char *)*/strDir, 
									/*(char *)(const char *)*/strFName, NULL);
    
		//  vollen ProFileNamen zusammenbauen
		CString strExt;
		
			VERIFY (strExt.LoadString (IDS_INIEXT));
			_makepath (_pFullName, strDrive, strDir, strFName, strExt);
			m_hPr = hPr;
		}
		else {
			DELETE_VEC (_pFullName);
		}
	}
	CATCH (CMemoryException, cme)
	{      
		DEX_Error (RC_Profile, EC_NOMEMORY);
	}
	END_CATCH        
}

// Destruktor
Profile::~Profile (void) 
{
	DELETE_VEC (_pFullName);
}

//	dBASE-Entry in ODBC-Entry konvertieren
BOOL Profile::KonvertDBaseToOdbc (ulong ulId, char *pBuffer, short BufferSize, int &iEntryCnt)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

//	prüfe Parameter
	ASSERT (_pFullName != NULL && AfxIsValidString (_pFullName));
	ASSERT (pBuffer != NULL && AfxIsValidString (pBuffer));
	ASSERT (!InvalidIdent(ulId) && BufferSize > 0);

	TRY {
	//	existiert Eintrag in der Section [DBASE] ?
	char IdKey [30] = "";
	char Buffer [30] = "";

//		if (FAILED(ClassFromIdentX (ulId, Buffer, sizeof(Buffer))) || (!*Buffer))
// KK000608
		if (FAILED(ClassFromIdentX (m_hPr,ulId, Buffer, sizeof(Buffer))) || (!*Buffer))
			return FALSE;

		strcpy (IdKey, g_cbId);
		strcat (IdKey, Buffer);

	CString strSection;
	
		if (!strSection.LoadString (IDS_DBASE))
			AfxThrowUserException ();

	iEntryCnt = GetPrivateProfileInt (strSection, IdKey, 0, _pFullName);
	
		if (iEntryCnt != 2 && iEntryCnt != 3)		// nur gültige Einträge konvert.
			return FALSE;
		
		if (GetPrivateProfileString (strSection, IdKey, "", pBuffer, BufferSize, _pFullName) <= 0)
			return FALSE;

	//	existiert hier auch ein ODBC-Tabelleneintrag: extrahiere Name der Tabelle
	char *pFirst = strchr (pBuffer, ',');		// suche 1. Separator
	
		if (!pFirst || !*++pFirst)
			return FALSE;
		if (*pFirst == '"')						// suche Begrenzer
			pFirst++;
		if (!*pFirst)
			return FALSE;

	char *pEnd = strchr (pFirst, ',');			// suche 2. Separator
		
		if (!pEnd || (--pEnd == pFirst))
			return FALSE;

	//	extrahiere Name
	CString strTableName;
	int iCnt = pEnd - pFirst;
	char *pTableName = strTableName.GetBuffer (iCnt + 2);
	
		memcpy (pTableName, pFirst, iCnt);
		pTableName [iCnt] = '\0';

	//	versuche Tabellen-Namen zu lesen
	char szBuff [5] = "";			// Check-Puffer

		if (!strSection.LoadString (IDS_TABLENAME))
			AfxThrowUserException ();
		if (!GetPrivateProfileString (strSection, pTableName, "", szBuff, sizeof (szBuff), _pFullName))
			return FALSE;
		
	//	wurde Anbindung über Ausdruck verwendet ?
		if (!strSection.LoadString (IDS_DBASE))		// Section wieder lesen
			AfxThrowUserException ();

		if (iEntryCnt == 3)	// normale Anbindung
		{
		//	"säubere" Feldname: "<" und ">" filtern 
			pFirst = strchr (pBuffer, '<');
			if (pFirst)
				*pFirst = '"';
			pFirst = strchr (pBuffer, '>');
			if (pFirst)
				*pFirst = '"';													
		} else {		// Anbindung über Ausdruck
		char *pBeg = strchr (pBuffer, ',');	// 1. Komma

			if (!pBeg || !*++pBeg)
				return FALSE;
			pBeg = strchr (pBeg, ',');			// 2. Komma
			if (!pBeg || !*++pBeg)
				return FALSE;

		//	Separatoren ersetzen
		char *pF = strchr (pBeg, '\'');

			if (pF)
				*pF = ' ';
			pF = strchr (pBeg, '`');
			if (pF)
				*pF = ' ';

		CString strWhere = pBeg;		// Expression umkopieren

		//	nur noch evtl. "krumme" Zeichen (""") ersetzen
			for (register short i = strWhere.Find ('\"'); i != -1;	
				 i = strWhere.Find ('\"'))
				strWhere.SetAt (i, '\'');	          
		
		//	DBASE-Operatoren ggf. ersetzen (.AND.; .OR.; .NOT.)
			short iFind = -1; 

		//	DBASE-Operatoren ggf. ersetzen (.AND.; .OR.; .NOT.)
		//	NotOperator		
			if (((iFind = strWhere.Find (NotOper)) >= 0) ||
				((iFind = strWhere.Find (NotOperL)) >= 0)) 			
			{
				strWhere.SetAt (iFind, ' ');	// Punkte durch Leerzeichen ersetzen			
				iFind += lstrlen (NotOper) - 1;
				strWhere.SetAt (iFind, ' ');			
			}	       
		
		//	OrOperator
			if (((iFind = strWhere.Find (OrOper)) >= 0) ||
				((iFind = strWhere.Find (OrOperL)) >= 0)) 			
			{
				strWhere.SetAt (iFind, ' ');	// Punkte durch Leerzeichen ersetzen			
				iFind += lstrlen (OrOper) - 1;
				strWhere.SetAt (iFind, ' ');			
			}	       
		           
		//	And-Operator		           
			if (((iFind = strWhere.Find (AndOper)) >= 0) ||
				((iFind = strWhere.Find (AndOperL)) >= 0)) 			
			{
				strWhere.SetAt (iFind, ' ');	// Punkte durch Leerzeichen ersetzen			
				iFind += lstrlen (AndOper) - 1;
				strWhere.SetAt (iFind, ' ');			
			}	          
			
			strcpy (pBeg, strWhere);			// String wieder umkopieren
			pBeg [0] = '"';						// Separatoren setzen
			pBeg [strlen (pBeg) - 1] = '"';					
		}

	//	neue Anbindung schreiben
		if (!strSection.LoadString (IDS_ODBC_SECTION))
			AfxThrowUserException ();

		return WritePrivateProfileString (strSection, IdKey, pBuffer, _pFullName);
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_Profile, EC_NOMEMORY);
	}
	AND_CATCH (CUserException, ue)
	{
		DEX_Error (RC_Profile, EC_SYSERROR);
	}
	END_CATCH 

	return FALSE;
}

//	Schreiben der normalen ODBC-Anbindung: 3 Parameter
BOOL Profile::WriteOdbcEntry (ulong ulId, const char *pAliasName, 
	const char *pFeldName, char const *pMName)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

//	püfe Parameter
	ASSERT (_pFullName != NULL && AfxIsValidString (_pFullName));
	ASSERT (pAliasName != NULL && AfxIsValidString (pAliasName));
	ASSERT (pFeldName != NULL && AfxIsValidString (pFeldName));

	if (!*pAliasName || !*pFeldName)
		return FALSE;

	TRY {
	//	Entry zusammenbauen
	CString strEntry;
	char Buffer[ReadAllBufferSize] = "";
		
		AfxFormatString2 (strEntry, IDS_MERKM_CONN_FORM, pAliasName, pFeldName);
		strncpy(Buffer, pMName, sizeof(Buffer)-1);
		Buffer[ReadAllBufferSize-1] = '\0';

	// JG alter Code schreibt MerkmalsCodes raus, jetzt nehmen wir hier die Namen
		strEntry += '\"';
		strEntry += Buffer;
		strEntry += '\"';

	//	Key zusammenbauen
	CString strId;

		if (0 != ulId) {
		char tBuffer [MAX_OKS_LENX+1] = "";
	
			if (!strId.LoadString (IDS_PROFID))
				return FALSE;
			if (FAILED(ClassFromIdentX (m_hPr,ulId, tBuffer, sizeof(tBuffer))) || (!*tBuffer))
				return FALSE;

			strcpy (Buffer, g_cbId);
			strcat (Buffer, tBuffer);
		} else
			strcpy (Buffer, g_cbStandard);

		CString strSection;
		VERIFY (strSection.LoadString(IDS_ODBC_SECTION));
		return WritePrivateProfileString (strSection, Buffer, strEntry, _pFullName);
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_Profile, EC_NOMEMORY);
	}
	END_CATCH
	return FALSE;
}

//	Schreiben der normalen ODBC-Anbindung: 3 Parameter
BOOL Profile::WriteOdbcEntry (ulong ulId, const char *pAliasName, 
	const char *pFeldName, ulong ulMKode)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

//	püfe Parameter
	ASSERT (_pFullName != NULL && AfxIsValidString (_pFullName));
	ASSERT (pAliasName != NULL && AfxIsValidString (pAliasName));
	ASSERT (pFeldName != NULL && AfxIsValidString (pFeldName));

	if (!*pAliasName || !*pFeldName)
		return FALSE;

	TRY {
	//	Entry zusammenbauen
	CString strEntry;
	char Buffer [ReadAllBufferSize] = "";
		
		AfxFormatString2 (strEntry, IDS_MERKM_CONN_FORM, pAliasName, pFeldName);
		if FAILED(GetFeatureName(ulMKode, Buffer, ReadAllBufferSize))
			return FALSE;
		
	// JG alter Code schreibt MerkmalsCodes raus, jetzt nehmen wir hier die Namen
		strEntry += '\"';
		strEntry += Buffer;
		strEntry += '\"';

	//	Key zusammenbauen
	CString strId;

		if (0 != ulId) {
		char tBuffer [MAX_OKS_LENX+1] = "";
	
			if (!strId.LoadString (IDS_PROFID))
				return FALSE;
			if (FAILED(ClassFromIdentX (m_hPr,ulId, tBuffer, sizeof(tBuffer))) || (!*tBuffer))
				return FALSE;

			strcpy (Buffer, g_cbId);
			strcat (Buffer, tBuffer);
		} else
			strcpy (Buffer, g_cbStandard);

		CString strSection;
		VERIFY (strSection.LoadString(IDS_ODBC_SECTION));
		return WritePrivateProfileString (strSection, Buffer, strEntry, _pFullName);
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_Profile, EC_NOMEMORY);
	}
	END_CATCH
	return FALSE;
}

//	schreibe Klausel-Anbindung in ODBC-Section
BOOL Profile::WriteOdbcKlausel (ulong ulId, const char *pAliasName, 
								  const char *pKlausel)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

//	püfe Parameter
	ASSERT (_pFullName != NULL && AfxIsValidString (_pFullName));
	ASSERT (pAliasName != NULL && AfxIsValidString (pAliasName));
	ASSERT (pKlausel != NULL && AfxIsValidString (pKlausel));

	if (!*pAliasName || !*pKlausel)
		return FALSE;			

	TRY	{
	//	Entry zusammenbauen
		CString strEntry;
		AfxFormatString2 (strEntry, IDS_KLAUSEL_CONN_FORM, pAliasName, pKlausel);

	//	Key zusammenbauen
	char Buffer [MaxValSize] = "";
	char tBuffer [MAX_OKS_LENX+1] = "";

//		if (FAILED(ClassFromIdentX (ulId, tBuffer, sizeof(tBuffer))) || (!*tBuffer))
// KK000608
		if (FAILED(ClassFromIdentX (m_hPr,ulId, tBuffer, sizeof(tBuffer))) || (!*tBuffer))
			return FALSE;
		strcpy (Buffer, g_cbId);
		strcat (Buffer, tBuffer);

		CString strSection;
		VERIFY (strSection.LoadString(IDS_ODBC_SECTION));
		return WritePrivateProfileString (strSection, Buffer, strEntry, _pFullName);
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_Profile, EC_NOMEMORY);
	}
	END_CATCH

	return FALSE;
}

// Schreiben des vollständigen dBase-Dateinamens (Section dBase-AliasNames)
BOOL Profile::WritedBaseAliasName (const char *pAliasName) 
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

//  prüfe Parameter
    if (!_pFullName || !*_pFullName || !pAliasName || !*pAliasName)
		return FALSE;

	StringDup strFullName (GetFulldBaseName (pAliasName), FALSE);		
	if (! strFullName)
		return False;
		             
//	existiert Datei ?
	Bool bRet = False;			// noch nichts getan
	OFSTRUCT of;
	if (OpenFile (strFullName.Upper (), &of, OF_EXIST) != HFILE_ERROR)
	{							   
		char AliasSection [30]= "";
		if (LoadString (g_hInstance, IDS_ALIASNAMES, AliasSection, sizeof (AliasSection))
			&& WritePrivateProfileString (AliasSection, pAliasName, strFullName, _pFullName))
			bRet = True;
	}
	
	return bRet;
}	
	

// Einlesen der zu einem Objekt gehörenden ODBC MerkmalsCodes ----------------
// Analysiert folgendes Format
//
// für den StandardFall:
// [dBaseRelations]
//      MasterDB:MasterField = n,SlaveDB1:SlaveField1, ... ,SlaveDBn:SlaveFieldn
int Profile::ReadOdbcRelations (DBaseRel &Master, DBaseRel ***pppDR) 
{                               
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	if (! _pFullName) 
		return 0;
	TRY {               
		char IdKey [dBaseSectSize] = "";
		char *PString = NULL;
		BOOL PStringAllocated = FALSE;
		short Cnt = 0;          // Anzahl der Relationen

	//  Namen der Section generieren
	char Section [30] = "";
	
		VERIFY(LoadString (g_hInstance, IDS_ODBC_RELATION, Section, sizeof (Section)) > 0);

		/*
		char ID [dBaseIdSize] = "";
		if (! LoadString (g_hInstance, IDS_PROFID, ID, dBaseIdSize))
			return 0;

		char Buffer [30] = "";
		if (FAILED(ClassFromIdentX (Ident, Buffer, sizeof(Buffer))) || (!*Buffer))
			return 0;
		strcpy (IdKey, ID);
		strcat (IdKey, Buffer);
		*/

	//  Anzahl der Relationen lesen
		CString strMasterEntry;
		AfxFormatString2 (strMasterEntry, IDS_MASTER_REL, Master.GetDBName (), 
														  Master.GetFieldName ());		
		Cnt = GetPrivateProfileInt (Section, strMasterEntry, 0, _pFullName);
		if (Cnt > 0) {
		//      Feld für ProfileString anfordern
			PString = new char [(Cnt+1)*80+1];
			*PString = '\0';
			if (PString == NULL) {          // kein Speicher mehr
				*pppDR = NULL;
				return 0;
			}
			PStringAllocated = TRUE;

		//  MerkmalsCodes selbst lesen
			GetPrivateProfileString (Section, strMasterEntry, "", PString, 
									 (Cnt+1)*80, _pFullName);
		}

	//  wenn nicht gegeben ist, wieder raus
		if (Cnt == 0) { 
			if (PStringAllocated) 
				DELETE_VEC (PString);
			*pppDR = NULL;
			return 0; 
		}

	//  RelationsFeld anfordern
		*pppDR = new DBaseRel* [Cnt];
		if (*pppDR == NULL) {
			if (PStringAllocated) 
				DELETE_VEC (PString);
			return 0;
		}

	// Relationen konvertieren
		register char *cptr = strchr (PString, ',');          // 1. Komma suchen
		int i = 0;

		while (i < Cnt) {
			if (cptr == NULL) {
				(*pppDR)[i] = NULL;     // Default
				break;  // abbrechen
			}

		char *pDBName = cptr+1;
		char *pField = strchr (pDBName, ':');

			if (pField) {
				*pField = '\0';
				pField++;

			//  nächster Eintrag
				cptr = strchr (pField, ',');
				if (cptr) 
					*cptr = '\0';
				(*pppDR)[i] = new DBaseRel (pDBName, pField);
				if ((*pppDR)[i] == NULL) 
					break;          // Fehler und raus
			}
			i++;
		}

	//  Speicher wieder freigeben
		if (PStringAllocated) 
			DELETE_VEC (PString);

		return i;       // real gelesene Werte
	}
	CATCH (CMemoryException, cme)
	{
		DEX_Error (RC_Profile, EC_NOMEMORY);
	}            
	END_CATCH
	
	return 0;
}

// lese zu einem Alias-Namen den zugehörigen Tabellen-Namen -    
// wenn kein Eintrag gefunden wird:
// 1. lese aus dem zugeh. vollst. Dateinamen den Filenamen
// 2. wenn auch dieser nicht existiert, liefere den AliasNamen  
// Return: der übergebene Zeiger ist explizit freizugeben
char *Profile::GetTableName (const char *pAliasName)
{                  
	AFX_MANAGE_STATE(AfxGetAppModuleState());

//      prüfe Parameter
	if (!_pFullName | !pAliasName || !*pAliasName)
		return NULL;
		
	TRY {               
	char Section [30] = "";
	
		VERIFY(LoadString (g_hInstance, IDS_TABLENAME, Section, sizeof (Section)) > 0);
			 
	char *pTableName = new char [_MAX_FNAME];               
	char *pFullName = NULL;                                       

		*pTableName = '\0';
		if (0 == GetPrivateProfileString (Section, pAliasName, "", pTableName, _MAX_FNAME, _pFullName))	{                             
		// lesen den vollst. DateiNamen
		StringDup strFullName (GetFulldBaseName (pAliasName), FALSE);

			if (strFullName) 
				_splitpath (strFullName.Ptr (), NULL, NULL, pTableName, NULL);
			else // letzte Variante: liefere den AliasNamen zurück
				lstrcpy (pTableName, pAliasName);
		}                                                            
		return pTableName;

	} CATCH (CMemoryException, cme)	{
		DEX_Error (RC_Profile, EC_NOMEMORY);
	} END_CATCH    

	return NULL;                                                            
}

// Zeiger ist explizit freizugeben                                    
char *Profile::GetDataSourceName (const char *pAliasName, DataSourceType &tType) 
{   
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	char *pDSN = NULL;              
	try	{
	//	prüfe Parameter
		if (!_pFullName)
			return NULL;  
		
	//	Odbc-Section lesen
		CString strSection;
		VERIFY (strSection.LoadString (IDS_DSN));
		pDSN = new char [DSNameSize];
		*pDSN = '\0';
		tType = NoDataSource;

	//	DataSourceName lesen         
		int iReadCnt = 0;
		if (pAliasName && *pAliasName)
			iReadCnt = GetPrivateProfileString (strSection, pAliasName, "", pDSN, DSNameSize, _pFullName);

	//	wenn keine zugeh. Eintrag gefunden, Standard-DataSourceName lesen
		if (0 == iReadCnt)
		{
			iReadCnt = GetPrivateProfileString (strSection, g_cbStandard, "", pDSN, DSNameSize, _pFullName);
		}

	//	jetzt Type auswerten
		if (iReadCnt > 2)
		{
		//	Zuerst Typ auswerten
			if (pDSN [1] != ',')	//	wenn kein Typ gegeben, alte Extension
			{
				tType = UserDataSource;
				return pDSN;
			}
	
		//	Typ lesen
			tType = (DataSourceType) atoi (pDSN);
			if ((tType != UserDataSource) && (tType != SystemDataSource) && (tType != FileDataSource))
				tType = UserDataSource;

		//	Namen verschieben
			memmove (pDSN, pDSN+2, strlen (pDSN) - 1);
			return pDSN;
		}
	}
	catch (CMemoryException *m)
	{
		m -> Delete ();
		DEX_Error (RC_Profile, EC_NOMEMORY);
	}
	
	DELETE_VEC (pDSN);                           
	return NULL;
}                       

// Einlesen der zu einem Objekt gehörenden ODBC MerkmalsCodes ----------------
int Profile::ReadOdbcCodes (long **MKs, char ***MStrs, long Ident) 
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	TRY {
	//  prüfe Parameter
		if (! _pFullName)
			return 0;
		
	CString strBuffer;
	char DBaseInfo [dBaseSectSize] = "";

		VERIFY(LoadString (g_hInstance, IDS_ODBC_SECTION, DBaseInfo, dBaseSectSize) > 0);
		
		char IdKey[30];
		char *PString = "";
		BOOL PStringAllocated = FALSE;
		int Cnt = 0;          // Anzahl der MerkmalsCodes

	//  für bestimmten Id liefern
		if (!InvalidIdent(Ident)/*Ident != -1*/) {      
		char Buffer [MAX_OKS_LENX+1] = "";

//			if (FAILED(ClassFromIdentX (Ident, Buffer, sizeof(Buffer))) || (!*Buffer))

// KK000608
			if (FAILED(ClassFromIdentX (m_hPr,Ident, Buffer, sizeof(Buffer))) || (!*Buffer))
				return 0;

			strcpy (IdKey, g_cbId);
			strcat (IdKey, Buffer);
			
		//  Anzahl der MerkmalsCodes lesen
			Cnt =::GetPrivateProfileInt (DBaseInfo, IdKey, 0, _pFullName);

		// wenn es (noch) keine  neuen Einträge gibt, dann die alten versuchen zu lesen (andere ini-Section)
			bool iFlag = false;	// Keine Umstellung auf OE !!
			if (0 == Cnt)
			{
				VERIFY(LoadString (g_hInstance, IDS_ODBC_SECTION_OLD, DBaseInfo, dBaseSectSize) > 0);
				Cnt = ::GetPrivateProfileInt (DBaseInfo, IdKey, 0, _pFullName);
// KK000414
				iFlag = true;	// in INI Umstellung auf OE abspeichern
			}

			if (Cnt > 0) {
			// Feld für ProfileString anfordern
				PString = new char [(Cnt+1)*80+1];
				*PString = '\0';
				if (PString == NULL) {          // kein Speicher mehr
					*MKs = NULL;
					*MStrs = NULL;
					return 0;
				}
				PStringAllocated = TRUE;

			// MerkmalsCodes selbst lesen
			   GetPrivateProfileString (DBaseInfo, IdKey, "", PString, (Cnt+1)*80, _pFullName);
// KK000414
			   if (iFlag) {
				   if ( 3 == Cnt ) {
						VERIFY(LoadString (g_hInstance, IDS_ODBC_SECTION, DBaseInfo, dBaseSectSize) > 0);
						ModeString (PString,Ident);
						WritePrivateProfileString (DBaseInfo, IdKey, PString, _pFullName);
				   }

			   }
			}
		} 

	//	wenn nichts da, dann Standard liefern
		if (!strcmp (PString, "")) {
		char Standard [20] = "";
		
			VERIFY(LoadString (g_hInstance, IDS_STANDARD, Standard, sizeof (Standard)) > 0);

		//	Anzahl der MerkmalsCodes lesen
			Cnt = GetPrivateProfileInt (DBaseInfo, Standard, 0, _pFullName);
			if (Cnt > 0) {
			// Feld für ProfileString anfordern
				PString = new char [(Cnt+1)*80+1];
				*PString = '\0';
				if (PString == NULL) {          // kein Speicher mehr
					*MKs = NULL;
					*MStrs = NULL;
					return 0;
				}
				PStringAllocated = TRUE;

			// MerkmalsCodes selbst lesen
			   GetPrivateProfileString (DBaseInfo, Standard, "", PString, (Cnt+1)*80, _pFullName);
			}
		}

	//	wenn nicht gegeben ist, wieder raus
		if (Cnt == 0) { 
			if (PStringAllocated) 
				DELETE_VEC(PString);
			*MKs = NULL; 
			*MStrs = NULL;

		//	ggf. Konvertierung vornehmen
			PString = strBuffer.GetBuffer (MaxKonvertBuffer);
			if (!KonvertDBaseToOdbc (Ident, PString, MaxKonvertBuffer, Cnt))
				return 0;
		}

	//	MKFeld anfordern
		*MKs = new long [Cnt];
		*MStrs = new char * [Cnt];
		if (*MKs == NULL || *MStrs == NULL) {
			if (PStringAllocated)
				DELETE_VEC (PString);
			if (*MKs != NULL) 
				DELETE_VEC (*MKs);
			*MKs = NULL;
			*MStrs = NULL;
			return 0;
		}

	//	MerkmalsCodes konvertieren
		register char *cptr = strchr (PString, ',');          // 1. Komma suchen
		int i = 0;

		while (i < Cnt) 
		{
			if (cptr == NULL) 
			{
				(*MKs)[i] = -1L;        // Default
				(*MStrs)[i] = NULL;
				break;  // abbrechen
			}
			// String zu lesen
			if (*(cptr+1) == '\"')
			{
				if (Cnt == 2 && i == 1)		
					(*MKs)[i] = -2L;			// Klausel gegeben
				else
					(*MKs)[i] = -1L;			// normaler String gegeben
				
				//	String kopieren
				(*MStrs)[i] = new char [lstrlen (cptr+2)+1];
				lstrcpy ((*MStrs)[i], cptr+2);  // Merkmalswert
				
				//	QuoteChar am Ende rausnehmen
				char *pPtr = strchr ((*MStrs)[i], '\"'); 
				if (pPtr)
					*pPtr = '\0';

			//  JG der 3. normale String bei Tabellenkopplung ist ein Merkmalsname
//				if ((2 == i) && (Cnt = 2))
// KK000413
				if ((2 == i) && (Cnt == 3))	// 3.Wert = OE
				{
					// MerkmalsName gegeben
					if (!FAILED(GetFeatureHandle (Ident,(*MStrs)[i], (INT_PTR *)&((*MKs)[i]))))
						(*MStrs)[i] = NULL;     // kein Merkmalswert
				}
			} 
			else						
			{
				// alte Version (Merkmalscodes in der *.ini)
				(*MKs)[i] = -1L;        // MerkmalsWert gegeben
				(*MKs)[i] = strtoul (cptr+1, NULL, g_sMkBase);   // MK konvertieren
				(*MStrs)[i] = NULL;     // kein Merkmalswert
			}

			cptr = strchr (cptr+1, ',');    // nächsten MK suchen
			i++;
		}		// end_while

	//  Speicher wieder freigeben
		if (PStringAllocated) 
			DELETE_VEC (PString);

		return i;       // real gelesene Werte
		
	} 
	CATCH (CMemoryException, cme) 
	{    
		DEX_Error (RC_Profile, EC_NOMEMORY);
	}         
	END_CATCH

	return 0;    
}

// MK in OE
void Profile :: ModeString (char * pString, long lIdent)
{
	if ( !pString || *pString == '\0')
		return;

	if ( 0 == lIdent)
		return;

	char * cptr = strrchr (pString,',');
	if (!cptr)
		return;

	long lMCode = atol (cptr+1);
	if ( 0 == lMCode ) 
		return;

	char KText[KurzTextLen] = "";

	ErrInstall E1 ( WC_NOMERKMAL);
	char outBuff[KurzTextLen + 20] = "";

	ErrCode EC;

	PBDMERKMALEX pbdData;            
	INITSTRUCT(pbdData, PBDMERKMALEX);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = KurzTextLen - 1;
	pbdData.lIdent = lIdent;
	HPROJECT hPr = DEX_GetObjectsProject(lIdent);
	EC = DEX_GetPBDDataEx (hPr,pbdData);

	if ( EC != EC_OKAY ) // Nur definierte OE !!
		return;

	wsprintf (outBuff, "\"%s\"", pbdData.pbdKText);
	*(cptr+1) = '\0';
	strcat (pString ,outBuff);

	return;
}


//  lese zu einem geg. Alias-Namen den zugehörigen Eintrag:
//  1. Alternative: suche im zur DB lokalen dBase-Verzeichnis
//  2. Alternative: suche im den in der TRIAS-INI angeg. dBase-Verzeichnis
//  der übergebene Zeiger ist explizit freizugeben
char *Profile::GetFulldBaseName (const char *pAliasName) 
{                              
	AFX_MANAGE_STATE(AfxGetAppModuleState());

//  prüfe Parameter
    if (!_pFullName || !pAliasName || !*pAliasName) 
		return NULL;
				 
TRY {
	char *pFoundName = new char [_MAX_PATH];
	if (! pFoundName)
		return NULL;
					 
//  zugeh. Eintrag lesen
char Section [20] = "";

	VERIFY(LoadString (g_hInstance, IDS_ALIASNAMES, Section, sizeof (Section)) > 0);
    if (GetPrivateProfileString (Section, pAliasName, "", pFoundName, _MAX_PATH, _pFullName))
		return pFoundName;

//  wenn kein Alias-Eintrag gefunden, suche Datei im lokalen dBASE-Verzeichnis 
	char Drive [_MAX_DRIVE] = "";
	char Dir [_MAX_DIR] = "";
	char dBaseExt [_MAX_EXT] = "";                                            
	
//  aktuelle Extension lesen
char ExtKey [15] = "";

	VERIFY(LoadString (g_hInstance, IDS_ACTEXTENSION, ExtKey, sizeof (ExtKey)) > 0);
	VERIFY(LoadString (g_hInstance, IDS_ODBC_SECTION, Section, sizeof (Section)) > 0);

	if (! GetPrivateProfileString (Section, ExtKey, "", dBaseExt, sizeof (dBaseExt), 
								   _pFullName)) 
	{
		// in der neuen Sektion nichts gefunden? ´noch mal alte Section probieren
		VERIFY(LoadString (g_hInstance, IDS_ODBC_SECTION_OLD, Section, sizeof (Section)) > 0);
		if (! GetPrivateProfileString (Section, ExtKey, "", dBaseExt, sizeof (dBaseExt), 
									   _pFullName)) 
		{       // wenn kein Nutzer-Eintrag in Projekt-Ini: Standard-Extension lesen (.dbf)                                                                             
			VERIFY(LoadString (g_hInstance, IDS_DBASEEXT, dBaseExt, sizeof (dBaseExt)) > 0);
		}                       
    }
    _splitpath (_pFullName, Drive, Dir, NULL, NULL);
    _makepath (pFoundName, Drive, Dir, NULL, NULL);
    char dBaseSubDir [10] = "";
    if (! LoadString (g_hInstance, IDS_DBASESUBDIR, dBaseSubDir, sizeof (dBaseSubDir)))
		return NULL;
    lstrcat (pFoundName, dBaseSubDir);
    lstrcat (pFoundName, "\\");
    lstrcat (pFoundName, pAliasName);
    lstrcat (pFoundName, dBaseExt);

//  Dateiname OK ?
    OFSTRUCT of;
    if (OpenFile (pFoundName, &of, OF_EXIST | OF_READ) < 0) {
    //  Datei steht nicht lokal zu dieser DatenBasis: zentralen Namen
    //  generieren               
    	char IniPath [_MAX_PATH] = "";
		DEX_GetMainIniName (IniPath);

	char Key [10] = "";

		VERIFY(LoadString (g_hInstance, IDS_ODBC_SECTION, Key, sizeof (Key)) > 0);
		VERIFY(LoadString (g_hInstance, IDS_PFADSECTION, Section, sizeof (Section)) > 0);
		if (GetPrivateProfileString (Section, Key, "",
								 	 pFoundName, _MAX_PATH, IniPath) == 0) 
		{
			// Notnagel, auch hier nochmal in der alten Section nachschauen
			VERIFY(LoadString (g_hInstance, IDS_ODBC_SECTION_OLD, Key, sizeof (Key)) > 0);
			if (GetPrivateProfileString (Section, Key, "",
								 	 pFoundName, _MAX_PATH, IniPath) == 0) 
			{		
				// immer noch nichts gefunden
				DELETE_VEC (pFoundName);
				return NULL;
			}
		}
		lstrcat (pFoundName, pAliasName);
		lstrcat (pFoundName, dBaseExt); 
    }

    return pFoundName;
    
}
CATCH (CMemoryException, cme)
{    
	DEX_Error (RC_Profile, EC_NOMEMORY);
}
END_CATCH

	return NULL;    
}

//	TRUE, wenn dieser Relations-Eintrag in der akt. Projekt-Ini existiert, sonst FALSE                
BOOL Profile::RelationEntryExist (CString &strMaster)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

//  prüfe interne Parameter
	if (!_pFullName)
		return FALSE;

//  Namen der Section generieren
char Section [30] = "";

	VERIFY(LoadString (g_hInstance, IDS_ODBC_RELATION, Section, sizeof (Section)) > 0);
    
//  Eintrag prüfen
char DummyBuffer [10] = "";    		

	return GetPrivateProfileString (Section, strMaster, "", DummyBuffer, 
								 	sizeof (DummyBuffer), _pFullName) > 0 ? TRUE : FALSE;
}

//	schreibe normale Anbindung in DBASE-Section
BOOL Profile::WriteDBaseEntry (ulong ulId, const char *pAliasName,
	const char *pFeldName, char const *pMName)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	ASSERT (_pFullName != NULL && AfxIsValidString (_pFullName));
	ASSERT (pAliasName != NULL && AfxIsValidString (pAliasName));
	ASSERT (pFeldName != NULL && AfxIsValidString (pFeldName));

	if (!*pAliasName || !*pFeldName)
		return FALSE;

	TRY
	{
	//	Entry zusammenbauen
	CString strEntry;
	char Buffer [ReadAllBufferSize] = "";

		AfxFormatString2 (strEntry, IDS_DBASE_CONNECTION, pAliasName, pFeldName);
		
		strncpy(Buffer, pMName, sizeof(Buffer)-1);
		Buffer[ReadAllBufferSize-1] = '\0';

		strEntry += '\"';
		strEntry += Buffer;
		strEntry += '\"';

	//	Key zusammenbauen
	CString strId;

		VERIFY(strId.LoadString (IDS_PROFID));

		char tBuffer [MAX_OKS_LENX+1] = "";
		if (FAILED(ClassFromIdentX (m_hPr, ulId, tBuffer, sizeof(tBuffer))) || (!*tBuffer))
			return FALSE;

		strcpy (Buffer, strId);
		strcat (Buffer, tBuffer);
	
	CString strSection;

		VERIFY(strSection.LoadString (IDS_DBASE));
		return WritePrivateProfileString (strSection, Buffer, strEntry, _pFullName);
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_Profile, EC_NOMEMORY);
	}
	END_CATCH
	return FALSE;
}

// DataSourcename schreiben
BOOL Profile::WriteDataSourceName (const char *pAliasName, const char *pDSN, 
									 DataSourceType tType)
{         
	AFX_MANAGE_STATE(AfxGetAppModuleState());

//  prüfe Parameter                                          
	ASSERT (_pFullName != NULL && AfxIsValidString (_pFullName));
	ASSERT (pDSN != NULL && AfxIsValidString (pDSN));
	ASSERT (pAliasName != NULL && AfxIsValidString (pAliasName));
	ASSERT (tType == UserDataSource || tType == FileDataSource || tType == SystemDataSource);

	TRY	{
		CString strSection, strValue;
		VERIFY (strSection.LoadString (IDS_DSN));
		strValue.Format (IDS_DSN_FORMAT, tType, pDSN);
		return WritePrivateProfileString (strSection, pAliasName, strValue, _pFullName);
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_Profile, EC_NOMEMORY);
	}
	END_CATCH
	return FALSE;
}

// Tablename schreiben
BOOL Profile::WriteTableName (const char *pAliasName, const char *pTableName)
{         
	AFX_MANAGE_STATE(AfxGetAppModuleState());

//  prüfe Parameter                                          
	ASSERT (_pFullName != NULL && AfxIsValidString (_pFullName));
	ASSERT (pTableName != NULL && AfxIsValidString (pTableName));
	ASSERT (pAliasName != NULL && AfxIsValidString (pAliasName));

	TRY	{
	CString strSection, strValue;
	
		VERIFY(strSection.LoadString (IDS_TABLENAME));
		AfxFormatString1 (strValue, IDS_ENTRY_FORMAT, pTableName);
		return WritePrivateProfileString (strSection, pAliasName, strValue, _pFullName);
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_Profile, EC_NOMEMORY);
	}
	END_CATCH
	return FALSE;
}

// Standard-DataSourcename schreiben
BOOL Profile::WriteStandardDataSourceName (const char *pDSN, DataSourceType tType)
{         
	AFX_MANAGE_STATE(AfxGetAppModuleState());

//  prüfe Parameter                                          
	ASSERT (_pFullName != NULL && AfxIsValidString (_pFullName));
	ASSERT (pDSN != NULL && AfxIsValidString (pDSN));
	ASSERT (tType == UserDataSource || tType == FileDataSource || tType == SystemDataSource);

	TRY	{
		CString strSection, strValue, strStandard;
		VERIFY (strSection.LoadString (IDS_DSN));
		VERIFY (strStandard.LoadString (IDS_STANDARD));
		strValue.Format(IDS_DSN_FORMAT, tType, pDSN);
		return WritePrivateProfileString (strSection, strStandard, strValue, _pFullName);
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_Profile, EC_NOMEMORY);
	}
	END_CATCH
	return FALSE;
}

//	lese zum DataSource den AliasNamen
CString Profile::GetAliasName (const char *pDsn, DataSourceType tType, const char *pTableName)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

//	prüfe Parameter
	ASSERT (NULL != _pFullName && AfxIsValidString (_pFullName));
	ASSERT (NULL != pDsn && AfxIsValidString (pDsn));
	ASSERT (NULL != pTableName && AfxIsValidString (pTableName));
	if (!*pDsn || !*pTableName)
		return "";
	if ((tType != UserDataSource) && (tType != FileDataSource) && (tType != SystemDataSource))
		return "";

//	Suchstring zusammenbauen
CString strSection, strResult;

	VERIFY (strSection.LoadString (IDS_DSN));

CString strBuffer;
char *pBuffer = strBuffer.GetBuffer (ReadAllBufferSize);

	if (GetPrivateProfileString (strSection, NULL, "", pBuffer, ReadAllBufferSize, _pFullName))	{
	//	jetzt alle gelesenen Einträge prüfen
		char *pResult = NULL;
		char *pTable = NULL;
		DataSourceType tFountType;
		for (; *pBuffer; pBuffer += lstrlen (pBuffer) + 1)			
		{
			DELETE_VEC (pResult);
			pResult = GetDataSourceName (pBuffer, tFountType);
			if (pResult && *pResult)
			{
				if ((strcmpi (pResult, pDsn) == 0) && (tType == tFountType))
				{
				//	richtige Tabelle ?
					DELETE_VEC (pTable);
					pTable = GetTableName (pBuffer);
					if (pTable && (strcmpi (pTableName, pTable) == 0))
					{
						strResult = pBuffer;
						break;
					}
				}
			}
		}
		DELETE_VEC (pResult);
		DELETE_VEC (pTable);
	}

	return strResult;
}

//	lese Koppelfeld über zugeh. Aliasnamen
//	d.h., für eine beliebige Objektklasse muß eine 3er Anbindung über
//	den Aliasnamen erfolgen
CString Profile::GetKoppelFeld (const char *pAliasName)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

//	prüfe Parameter
	ASSERT (NULL != _pFullName && AfxIsValidString (_pFullName));

	if (!pAliasName || !*pAliasName)
		return "";

//	lese alle Objektklassen	
	CString strSection, strResult;
	VERIFY (strSection.LoadString (IDS_ODBC_SECTION));
	CString strBuffer;
	char *pBuffer = strBuffer.GetBuffer (ReadAllBufferSize);

	if (!GetPrivateProfileString (strSection, NULL, "", pBuffer, ReadAllBufferSize, _pFullName))
	{
		// in der neuen section nichts gefunden, also nochmal in der alten nachschlagen
		VERIFY (strSection.LoadString (IDS_ODBC_SECTION_OLD));
		if (!GetPrivateProfileString (strSection, NULL, "", pBuffer, ReadAllBufferSize, _pFullName))
		{
			return strResult;	// also nichts
		}
	}
	

//	jetzt alle gelesenen Einträge prüfen
	char *pResult = NULL;
	int iCnt = 0;
	//char Buffer20 [20] = "";
	long *pMKs = NULL;
	char **ppMStrs = NULL;
	ulong lIdent = 0;
	for (; *pBuffer; pBuffer += lstrlen (pBuffer) + 1)			
	{
		if (strlen (pBuffer) <= 2)
			continue;
	/*						
		lIdent = atol (pBuffer+2);
		if ((lIdent == 0) || (lIdent == -1))
			continue;
	*/
		if (FAILED(IdentFromClassX (m_hPr, pBuffer+2, &lIdent, FALSE)))
			continue;

		iCnt = ReadOdbcCodes (&pMKs, &ppMStrs, lIdent);
		if ((iCnt > 2) && (pMKs [0] == -1) && (ppMStrs [0] != NULL) && (*ppMStrs [0]) &&
			(strcmpi (pAliasName, ppMStrs [0]) == 0) &&
			(pMKs [1] == -1) && (ppMStrs [1]) && (*ppMStrs [1]))
			strResult = ppMStrs [1];
	
	//	MKodes und MStr-Speicher freigeben
		for (short i = 0; i < iCnt; i++)
			DELETE_VEC (ppMStrs [i]);
		DELETE_VEC (ppMStrs);
		DELETE_VEC (pMKs);		

	//	ggf. Abbruch
		if (!strResult.IsEmpty ())
			break;
	}

	return strResult;
}

//	lese Merkmalskode über zugeh. Aliasnamen
//	d.h., für eine beliebige Objektklasse muß eine 3er Anbindung über
//	den Aliasnamen erfolgen
ULONG Profile::GetMerkmalsKode (const char *pAliasName)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

//	prüfe Parameter
	ASSERT (NULL != _pFullName && AfxIsValidString (_pFullName));

	if (!pAliasName || !*pAliasName)
		return 0;

//	lese alle Objektklassen	
	ULONG ulRet = 0;
	CString strSection;
	VERIFY (strSection.LoadString (IDS_ODBC_SECTION));
	CString strBuffer;
	char *pBuffer = strBuffer.GetBuffer (ReadAllBufferSize);
	if (!GetPrivateProfileString (strSection, NULL, "", pBuffer, ReadAllBufferSize, _pFullName))
	{
		VERIFY (strSection.LoadString (IDS_ODBC_SECTION_OLD));
		if (!GetPrivateProfileString (strSection, NULL, "", pBuffer, ReadAllBufferSize, _pFullName))
		{
			return ulRet;
		}		
	}

//	jetzt alle gelesenen Einträge prüfen
	char *pResult = NULL;
	int iCnt = 0;
	// char Buffer20 [20] = "";
	long *pMKs = NULL;
	char **ppMStrs = NULL;
	ulong lIdent = 0;
	for (; *pBuffer; pBuffer += lstrlen (pBuffer) + 1)			
	{
		if (strlen (pBuffer) <= 2)
			continue;
	/*						
		lIdent = atol (pBuffer+2);
		if ((lIdent == 0) || (lIdent == -1))
			continue;
	*/
		if (FAILED(IdentFromClassX (m_hPr, pBuffer+2, &lIdent, FALSE)))
			continue;

		iCnt = ReadOdbcCodes (&pMKs, &ppMStrs, lIdent);
		if ((iCnt > 2) && (pMKs [0] == -1) && (ppMStrs [0] != NULL) && (*ppMStrs [0]) &&
			(strcmpi (pAliasName, ppMStrs [0]) == 0) &&
			(pMKs [2] != -1))
			ulRet = pMKs [2];
	
	//	MKodes und MStr-Speicher freigeben
		for (short i = 0; i < iCnt; i++)
			DELETE_VEC (ppMStrs [i]);
		DELETE_VEC (ppMStrs);
		DELETE_VEC (pMKs);		

	//	ggf. Abbruch
		if (ulRet != 0)
			break;
	}


	return ulRet;
}

//	lese durch Komma getrennt alle Objklassen, die die gegebene anbindung erfüllen
CString Profile::GetObjClasses (const char *pAliasName, const char *pKoppelField, ULONG ulMK)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

//	prüfe Parameter
	ASSERT (NULL != _pFullName && AfxIsValidString (_pFullName));
	ASSERT (pAliasName && AfxIsValidString (pAliasName));
	ASSERT (pKoppelField && AfxIsValidString (pKoppelField));
	ASSERT (ulMK > 0);
	if (!*pAliasName || !*pKoppelField)
		return "";

//	lese alle Objektklassen	
	CString strSection, strResult;
	VERIFY (strSection.LoadString (IDS_ODBC_SECTION));
	CString strBuffer;
	char *pBuffer = strBuffer.GetBuffer (ReadAllBufferSize);
	if (!GetPrivateProfileString (strSection, NULL, "", pBuffer, ReadAllBufferSize, _pFullName))
	{
		VERIFY (strSection.LoadString (IDS_ODBC_SECTION_OLD));
		if (!GetPrivateProfileString (strSection, NULL, "", pBuffer, ReadAllBufferSize, _pFullName))
		{
			return strResult;
		}		
	}

//	jetzt alle gelesenen Einträge prüfen
	char *pResult = NULL;
	int iCnt = 0;
	// char Buffer20 [20] = "";
	long *pMKs = NULL;
	char **ppMStrs = NULL;
	ulong lIdent = 0;
	for (; *pBuffer; pBuffer += lstrlen (pBuffer) + 1)			
	{
		if (strlen (pBuffer) <= 2)
			continue;
	/*						
		lIdent = atol (pBuffer+2);
		if ((lIdent == 0) || (lIdent == -1))
			continue;
	*/
		if (FAILED(IdentFromClassX (m_hPr, pBuffer+2, &lIdent, FALSE)))
			continue;

		iCnt = ReadOdbcCodes (&pMKs, &ppMStrs, lIdent);
		if ((iCnt > 2) && (pMKs [0] == -1) && (ppMStrs [0] != NULL) && (*ppMStrs [0]) &&
			(strcmpi (pAliasName, ppMStrs [0]) == 0) &&
			(pMKs [1] == -1) && (ppMStrs [1]) && (*ppMStrs [1]) &&
			(strcmpi (pKoppelField, ppMStrs [1]) == 0) &&
			(pMKs [2] != -1) && (pMKs [2] == (long)ulMK))
		{
			if (strResult.IsEmpty ())
				strResult = (pBuffer + 2);
			else
			{					
				strResult += ",";
				strResult += (pBuffer + 2);
			}
		}
	
	//	MKodes und MStr-Speicher freigeben
		for (short i = 0; i < iCnt; i++)
			DELETE_VEC (ppMStrs [i]);
		DELETE_VEC (ppMStrs);
		DELETE_VEC (pMKs);		
	}

	return strResult;
}

