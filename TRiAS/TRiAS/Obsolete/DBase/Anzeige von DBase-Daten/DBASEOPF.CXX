// Funktionen fuer DBase-OPF's ------------------------------------------------
// File DBASEOPF.CXX

#include "pheader.h"

#include "dbaseopf.htp"
#include <commonvu.hxx>
#include <containr.hxx>

extern "C" {
	#include <resstrg.h> 		// Ressourcen-Defines
	#include "dbaseext.hr"
}

#include <ixtensn.hxx>			// ITriasXtension
#include <xtencunk.hxx>			// CTriasExtension			  
#include <xtsnprop.hxx>			// CObjectProperties
#include <dbtools.hxx>	  		// GetFulldBaseName ()
#include <objfeld.hxx>	 		// für Klasse ObjNummer
#include <dbliste.hxx>	  		// für Klasse DB_Filter

#include <dbaserel.hxx>	 		// DBaseRel
#include <dbasprof.hxx>			// DBaseProfile
#include "waitcur.hxx"         	// CWaitCursor     
#include "dbase.hxx"
#include "tablenam.hxx"			// CTableNameTree
#include "dbaseext.hxx"		 	// Klasse für diese Erweiterung

// ObjPropFuncs für das aktive Objekt des aktuellen ORFensters installieren ---
extern "C" {

// 	Freigeben des FeldNamens in der Beschreibung der OPF
void __export PASCAL FreeFieldName (DWORD eData)
{
	if (eData) 
		delete (CFeldInfos *)eData;
}
}
extern DBaseExtension *pDBExt;

// Objekteigenschaften --------------------------------------------------------
CdBaseObjectProperties :: CdBaseObjectProperties (LPUNKNOWN pIUnk, LPCSTR pcGroupName, DWORD dwFlags)
					    : CObjectProperties (pIUnk, pcGroupName, dwFlags)
{
}

CdBaseObjectProperties :: ~CdBaseObjectProperties (void)
{
}

CdBaseObjectProperties *CdBaseObjectProperties :: CreateInstance (LPUNKNOWN pIUnk, LPCSTR pcGroupName, 
												  			      DWORD dwFlags)
{
#ifdef WIN32
	ResourceFile RF (g_pDLLName);
        ResString strGroupName (ResID (IDS_GROUP_NAME, &RF), 50);
	CdBaseObjectProperties *pOPs = new CdBaseObjectProperties (pIUnk, strGroupName.Addr (), 
									   						   PROPCAPS_NONE);
#else
	CdBaseObjectProperties *pOPs = new CdBaseObjectProperties (pIUnk, NULL, PROPCAPS_NONE);	
#endif

	if (NULL == pOPs || !pOPs -> FInit()) 
	{
		DELETE_OBJ(pOPs);
		return NULL;
	}

	return pOPs;
}

STDMETHODIMP CdBaseObjectProperties :: OnNewReferenceObject (LONG lRefONr)
{
	if (InstallActPropertyFunctions (lRefONr) > 0)
		return ResultFromScode (S_OK);
	else
		return ResultFromScode (E_NOTIMPL);
}       

// ObjPropFuncs für das aktive Objekt des aktuellen ORFensters installieren ---
short CdBaseObjectProperties :: InstallActPropertyFunctions (long lONr)
{
	const short BufferSize = 2048;

//	prüfe Parameter 
	if (!pDBExt || lONr < 0)
		return 0;

	CWaitCursor wc;				// Sanduhr einschalten

// 	als erstes alle alten OPFs vergessen
	RemoveAllPropertyFunctions ();

	if (lONr > 0)
	{//	dBASE-Anbindung vorhanden
		ulong ulIdent = DEX_GetObjIdent (lONr);
		if (pDBExt -> ReadDBaseCodes (lONr, ulIdent) < 2)  // INI lesen
			return 0;	   
		return InstallIdentPropertyFunctions (ulIdent);				
	}

//	Anbindung für alle Objektklassen
	short sCnt = 0;			

//	Ini-Dateinamen lesen	
	DBaseProFile ProFile;				    
	CTableNameTree * pTableNameTree = new CTableNameTree;
	char *pBuffer = new char [BufferSize];
	if (!pTableNameTree || !pBuffer)
	{
		DEX_Error (RC_InstPropFunction, EC_NOMEMORY);
		return 0;
	}
                        
//	Puffer init.                        
	*pBuffer = '\0';
		
//	alle gültigen Strings lesen		
	ResString strSection (ResID (IDS_DBASEKEY, &pDBExt -> RF ()), 10);
	if (GetPrivateProfileString (strSection.Addr (), NULL, "", pBuffer, 
		BufferSize, ProFile.GetProFileName ()))
	{
		ulong ulIdent = 0;		// akt. ID
		long *pMKs = NULL;
		char **ppMStrs = NULL;
		short sActParams = 0;

	//	für alle IDs die Objekteigenschaften lesen			
		for (char *pBuff = pBuffer; *pBuff; pBuff += lstrlen (pBuff) + 1)
		{                
		//	aktuellen ID bestimmen                                         
			if (FAILED(IdentFromClassX (pBuff + 2, &ulIdent, FALSE)))	// wenn kein gültiger ID
				continue;		// weiter

			sActParams = ProFile.ReadDBaseCodes (&pMKs, &ppMStrs, (long) ulIdent);

		//	alle Objekteigenschaften dieser Objektklasse install.					
			if ((sActParams > 1) 
				&& (pMKs [0] == -1) && (ppMStrs [0] != NULL) && (*ppMStrs [0])	// AliasName OK
				&& (pMKs [1] == -1) && (ppMStrs [1] != NULL) && (*ppMStrs [1]))	// FeldName OK	
				sCnt += InstallIdentPropertyFunctions (ulIdent, pTableNameTree, ppMStrs [0]);

		//	MKodes und MStr-Speicher freigeben
			for (short i = 0; i < sActParams; i++)
				DELETE_VEC (ppMStrs [i]);
			DELETE_VEC (ppMStrs);
			DELETE_VEC (pMKs);
		}	// end_for
	}

//	Speicher freigeben
	DELETE_OBJ (pTableNameTree);    
	DELETE_VEC (pBuffer);
	
	return sCnt;	
}

//	Objekt-Eigenschaften für eine bestimmte Klasse installieren
short CdBaseObjectProperties :: InstallIdentPropertyFunctions (ulong lIdent, 
															   CTableNameTree *pTableNameTree,
										 					   char *pAliasName)
{
//	prüfe interne Parameter
	if (!pDBExt)
		return 0;	

//	lese vollst. Dateinamen
	char *pFullName = GetFulldBaseName (pAliasName ? pAliasName : pDBExt -> _pDBaseFile);
	if (pFullName == NULL) 
		return 0;		// Datei existiert evtl. nicht

//	Tabelle bereits gespeichert ?
	char TableName [_MAX_FNAME] = "";
	_splitpath (pFullName, NULL, NULL, TableName, NULL);		
	strupr (TableName);
	if (pDBExt -> m_bOemToAnsi)		// WINDOWS-Zeichensatz erz.
		OemToAnsi (TableName, TableName);
	if (pTableNameTree && pTableNameTree -> Exist (TableName))
	{
		DELETE_VEC (pFullName);		// mögliche Funktionen bereits installiert
		return 0;		   			// zurück
	}	

//	Infos lesen
	CodeBase *pCB = CreateCodeBaseObj (g_hInstance);
	if (pCB == NULL) 
	{
		DELETE_OBJ (pFullName);
		return 0;
	}
	Data *pData = new Data (pCB, pFullName); 	// zu diesem Objekt gehörende DBaseDatei
	short iNumFields = pData && (!pCB -> error ()) ? pData -> num_fields() : 0;

	if (iNumFields <= 0) 		  // Fehler, oder keine Anbindung
	{
		DELETE_VEC (pFullName);
		DELETE_VEC (pData);
		DeleteCodeBaseObj();
		return 0;
	}

// 	Funktionen installieren
	ResString rstrFunctFormat (ResID (IDS_DBASEOPF, &pDBExt -> RF()), 20);
	CFeldInfos *pFieldInfo = NULL;
	char *pFuncName = NULL;
	short sInstCnt = 0;			// real installierte Funtkionen
	for (short iCnt = 1; iCnt <= iNumFields; iCnt++) 
	{// für alle Felder (außer Memo)
		if ((pData -> field (iCnt) -> type ()) == 'M')		
			continue;

	//	Neues FeldInfo erzeugen
		pFieldInfo = new CFeldInfos;
		pFieldInfo -> m_pFieldName = new char [pData -> field (iCnt) -> name.len () + 1];
		pFieldInfo -> m_pTableName = new char [lstrlen (TableName) + 1];
		pFuncName = new char [lstrlen (TableName) + pData -> field (iCnt) -> name.len () + 
							  rstrFunctFormat.Len ()];
		if (!pFieldInfo || !pFieldInfo -> m_pFieldName || !pFieldInfo -> m_pTableName || !pFuncName)
		{
			DELETE_OBJ (pFieldInfo);
			DELETE_VEC (pFuncName);
			break;
		}

	//	Feldnamen speichern
		lstrcpy (pFieldInfo -> m_pFieldName, pData -> field (iCnt) -> name.ptr ());
		if (pDBExt -> m_bOemToAnsi)
			OemToAnsi (pFieldInfo -> m_pFieldName, pFieldInfo -> m_pFieldName);
		strupr (pFieldInfo -> m_pFieldName);

	//	Tabellennamen speichern
		lstrcpy (pFieldInfo -> m_pTableName, TableName);	

	//	Funktion zusammenbauen
		wsprintf (pFuncName, rstrFunctFormat.Addr (), pFieldInfo -> m_pTableName, pFieldInfo -> m_pFieldName);

		if (AddPropertyFunctionEx (pFuncName, RetrieveFieldInfo, (DWORD) pFieldInfo, 
								   FreeFieldName) == 0)
		{
			DELETE_VEC (pFuncName);
			break;								   	
		}

		sInstCnt++;		// Zähler erhöhen

		DELETE_VEC (pFuncName);
	}	// end_for

//	ggf. Tabellennamen speichern
	if (pTableNameTree)
		pTableNameTree -> AddTable (TableName);

// 	Speicher freigeben
	DELETE_OBJ (pData);
	DELETE_VEC (pFullName);
	DeleteCodeBaseObj();

	return sInstCnt;
}

extern "C" {
                                
#pragma function (memcpy)                                
// Einlesen eines DBaseFeldes über eine gegebene ObjektNummer -----------------
char * __export PASCAL RetrieveFieldInfo (long lONr, char *pBuffer, 
										  short iLen, DWORD eData)
{
	static long lCnt = 0;		   // Idents mit KurzText
	static long lCntAll = 0;	   // GesamtIdents
	static long lLastRecNo = -1L;
	static long lLastONr = -1L;               

#ifndef WIN32
	char HelpBuffer [100] = "";
#endif	

	if (lONr == OBJPROP_RESET) 
	{
		lCnt = 0L;
		lCntAll = 0L;
		lLastRecNo = -1L;
		lLastONr = -1L;
		return NULL;
	}
	if (pBuffer == NULL) 
		return NULL;
		
	if (lONr == OBJPROP_CUMULATION) {
		// kumulativen Index ausgeben
#ifndef WIN32		                                                    
		ltoa (lCntAll, HelpBuffer, 10);
		memcpy (pBuffer, HelpBuffer, lstrlen (HelpBuffer) + 1);
#else                                       
		ltoa (lCntAll, pBuffer, 10);
#endif				
		return pBuffer; 
	} 
	else 
		if (lONr == OBJPROP_GETHELPTEXT) 
		{ 	// HilfeText besorgen
			ResString strFormat (ResID (IDS_DBASEOPFHELP, &pDBExt -> RF()), 80);
#ifndef WIN32		
			wsprintf (HelpBuffer, strFormat.Addr (), 
					 ((CFeldInfos *)eData) -> m_pFieldName, ((CFeldInfos *)eData) -> m_pTableName);
			memcpy (pBuffer, HelpBuffer, lstrlen (HelpBuffer) + 1);
#else 
			wsprintf (pBuffer, strFormat.Addr (),
					 ((CFeldInfos *)eData) -> m_pFieldName, ((CFeldInfos *)eData) -> m_pTableName);
#endif				
			return pBuffer;
		} else 
		if (lONr == OBJPROP_COUNT) 
		{// 	Gesamtanzahl ausgeben
#ifndef WIN32		
			ltoa (lCnt, HelpBuffer, 10);
			memcpy (pBuffer, HelpBuffer, lstrlen (HelpBuffer) + 1);
#else                                    
			ltoa (lCnt, pBuffer, 10);				
#endif				
			return pBuffer;
		}

//	FeldInfo lesen
	ulong lIdent = DEX_GetObjIdent (lONr);		   			// Identifkator lesen
	if (pDBExt -> ReadDBaseCodes (lONr, lIdent) < 2)		// INI-Datei lesen
		return NULL;										// keine DBaseAnbindung

// 	vollen DBaseDateiPfad generieren
	char *pFullName = GetFulldBaseName (pDBExt -> _pDBaseFile);
	if (pFullName == NULL) 
		return NULL;	 // Datei existiert evtl. nicht

	CWaitCursor wc;		 // Sanduhr einschalten

// 	CodeBaseObjekt anfordern
	CodeBase *pCB = CreateCodeBaseObj (g_hInstance);
	if (pCB == NULL) 
	{
		DELETE_VEC (pFullName);
		return NULL;
	}

// 	DBaseDatei öffnen, die zu diesem Objekt gehört
	int iAutoOpen = pCB -> auto_open;				// Index-Datei-Öffnen-Flag speichern
	if (pDBExt -> _Type == TagName)
		pCB -> auto_open = True;		
	DataIndex *pDI = new DataIndex (pCB, pFullName);
	pCB -> auto_open = iAutoOpen;					// Flag wieder rücksetzen
	DBaseObjNummer *pDO = new DBaseObjNummer (lONr);
	DELETE_VEC (pFullName);	 // wird nicht mehr gebraucht

	if (pDI == NULL || pCB -> error() || pDO == NULL || 		// Objekte nicht erzeugt ?
		(lstrcmpi (pDI -> alias.ptr (), ((CFeldInfos *) eData) -> m_pTableName) != 0) || // falsche Tabelle
		(pDI -> jfield (((CFeldInfos *) eData) -> m_pFieldName) < 0))  
	{
		DELETE_OBJ (pDI);
		DELETE_OBJ (pDO);
		DeleteCodeBaseObj();
		return NULL;
	}

	if (lLastONr != lONr)
	{// zum Objekt gehörenden DBaseSatz suchen (nur den ersten)
		lLastONr = lONr;		// akt. Obj-Nr. speichern
		DB_Filter *pDBF = NULL;
		switch (pDBExt -> _Type) 
		{
		case TagName: 
			pDBF = new DB_Filter (pCB, *pDI, *pDO, pDBExt -> _pDBaseField, pDBExt -> _pDBaseKey);
		break;
		case dBaseExpr: 
			pDBF = new DB_Filter (pCB, *pDI, *pDO, NULL, NULL, pDBExt -> _pDBaseField);
		break;
		case FeldName:
		default:
			pDBF = new DB_Filter (pCB, *pDI, pDBExt -> _pDBaseField, pDBExt -> _pDBaseKey, *pDO);
		break;
		}
				
		if (pDBF && (pDBF -> Result() == EC_OKAY) && 
			(pDBF -> Check (FALSE, TRUE) == EC_OKAY)) // Unique
			lLastRecNo = pDO -> RA(). GetRecordNr (0);
		else 
			lLastRecNo = -1L;	   // nichts gefunden
		DELETE_OBJ (pDBF);
	}

	if (lLastRecNo > 0) 
	{
	// 	Gesuchtes Feld lokalisieren und umkopieren
		pDI -> go (lLastRecNo); // Satz positionieren
		if (pCB -> error () == r4success)
		{
			Field *pF = pDI -> field (((CFeldInfos *)(eData)) -> m_pFieldName);
			if (pCB -> error () == r4success)
			{
				short minLen = min ((short) pF -> len(), iLen-1);
				memcpy (pBuffer, pF -> ptr(), minLen); // Feld umkopieren
				pBuffer[minLen] = '\0';
				if (pDBExt -> m_bOemToAnsi)		
					OemToAnsi (pBuffer, pBuffer);

			// 	Zähler aktualisieren
				lCnt++;
				lCntAll += atol (pBuffer);	  // Versuch zu addieren
			}
		}
	}

// 	Speicher freigeben
	DELETE_OBJ (pDI);
	DELETE_OBJ (pDO);
	DeleteCodeBaseObj();

	return lLastRecNo > -1 ? pBuffer : NULL;
}

}	   // extern "C"

// CFeldInfos ------------------------------------------------------------------------------------------
CFeldInfos :: CFeldInfos (void)
{
	m_pFieldName = m_pTableName = NULL;
}

CFeldInfos :: ~CFeldInfos (void)
{
	DELETE_VEC (m_pFieldName);
	DELETE_VEC (m_pTableName);
}
