// Funktionen fuer ODBC-OPF's ------------------------------------------------
// File OPJPROPF.CPP

#include "pheader.h"				// vorübersetzter Header
#include "odbcext.hr"				// Resourcen-Konstanten

#include <xtsnpropatl.h>			// CObjectProperties
#include <xtsnaux.hxx>				// WideString

#include <hpp/odbcerr.hpp>        		// OdbcError 
#include <hpp/columnst.hpp>         	// CColumns
#include <hpp/collist.hpp>          	// CColumnObjArray
#include <hpp/waitcur.hpp>				// CWaitCursor
#include <hpp/strdup.hxx>				// StringDup
#include <hpp/getodbci.hpp>				// nur DataSourceType

#include "odbcguid.h"	

#include "recset.hpp"           	// CRecSet
#include "database.hpp"         	// CDataBaseEx
#include "profile.hpp"          	// DBaseProFile
#include "dispatch.hpp"         	// dBaseDispatch
#include "tablenam.hpp"				// CTableNameTree
#include "odbcext.hpp"         		// Klasse für diese Erweiterung

#include "myhelper.h"				// JG 

#if _TRiAS_VER >= 0x0400
#include "ODBCProperty.h"
#endif // _TRiAS_VER >= 0x0400

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(InitInnerObject);

///////////////////////////////////////////////////////////////////////////////
// externe Funktionen
void CallMessageQueue (void);		// Steuerung an Windows zum Nachzeichnen

// externe Varibalen
CODBCObjectProperties *g_pCOdbcProperties = NULL;
extern COdbcExtension *g_pCOdbcExtension;

#if _TRiAS_VER < 0x0400
// globale Variablen
CLastIdentInfo LastIdentInfo;		

// Freigeben des FeldNamens in der Beschreibung der OPF
extern "C"
void __export PASCAL FreeFieldName (DWORD eData)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	if (eData) 
		:: delete ((CFeldInfos *) eData);	
}                       
              
// Einlesen eines ODBC-Feldes über eine gegebene ObjektNummer -----------------
extern "C"
char * __export PASCAL RetrieveFieldInfo (long lONr, char *pBuffer, short iLen, DWORD eData)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

static long lCnt = 0L;			// akt. Feldnummer
static long lCntAll = 0L;		// Akkumulatorinhalt
static long lLastObjNr = -1L;	

	if (lONr == OBJPROP_RESET) {
		lCnt = 0L;
		lCntAll = 0L;
		lLastObjNr = -1L;         
		if (! g_pCOdbcExtension -> GetOptEnable())
			LastIdentInfo.RemoveAll ();		// alten Ident-Infos löschen
		return NULL;
	}
	if (pBuffer == NULL) 
		return NULL;
	
	if (lONr == OBJPROP_CUMULATION) 
	{	// kumulativen Index ausgeben
#ifdef WIN32
		ltoa (lCntAll, pBuffer, 10);
#else
	char HelpBuffer [20] = "";
	
		ltoa (lCntAll, HelpBuffer, 10);
		memcpy (pBuffer, HelpBuffer, lstrlen (HelpBuffer) + 1);
#endif		
		return pBuffer; 
	} 
	else {
		if (lONr == OBJPROP_GETHELPTEXT) 
		{	// HilfeText besorgen
			CString strHelp;
			AfxFormatString2 (strHelp, IDS_OBJPROPFUNC_HELP,
							 ((CFeldInfos *) eData) -> m_strTableName,
							 ((CFeldInfos *) eData) -> m_strFeldName);							 								
#ifdef WIN32
			lstrcpy (pBuffer, strHelp);
#else
			memcpy (pBuffer, (const char *) strHelp, strHelp.GetLength () + 1);
#endif		
			return pBuffer;
		} 
		else if (lONr == OBJPROP_COUNT) 
		{ 	// Gesamtanzahl ausgeben
			ltoa (lCnt, pBuffer, 10);
			return pBuffer;
		}
	}

//	ggf. RecordSet aufbauen                                     
BOOL bOpFlag = TRUE;

	if (lLastObjNr != lONr) {
	INT_PTR ulIdent = DEX_GetObjIdent (lONr);

		lLastObjNr = lONr;											// neue Objekt-Nummer speichern

	//	aktuellen Merkmalswerte müssen für jedes neue Onjekt neu gelesen werden
		if (g_pCOdbcExtension -> ReadDBaseCodes (lONr, ulIdent) < 2) 	// INI lesen
			return NULL;                    	// keine ODBC-Anbindung vorh.

	//	sind wir hier in der richtigen Tabelle ?
	HPROJECT hPr = DEX_GetObjectsProject(ulIdent);
	Profile ProFile(hPr);
	StringDup strTableName (ProFile.GetTableName (g_pCOdbcExtension -> _pAliasName), FALSE);

		if (! strTableName)
			return NULL;
		if (((CFeldInfos *) eData) -> m_strTableName.CompareNoCase (strTableName) != 0) 
			return NULL;	

		if (!LastIdentInfo.Refresh (strTableName, lONr, ulIdent))		// bei Init. ist Fehler aufgetreten
			return NULL;

	//	neuen RecordSet aufbauen
	BOOL bHardError = FALSE;

		TRY	{                      
		//	zuerst Where-Klausel
		CString strWhere;                                       
		
			if (bOpFlag = LastIdentInfo.m_pCA -> BuildWhereKlausel (strWhere, 
														 			g_pCOdbcExtension -> _pFieldName, 
														 			g_pCOdbcExtension -> _pKeyName, FALSE))
			{
				LastIdentInfo.m_pCRecSet -> m_strFilter = strWhere;	// neue Klausel speichern	
				if (LastIdentInfo.m_pCRecSet -> IsOpen ())
					bOpFlag = LastIdentInfo.m_pCRecSet -> Requery ();
				else
					bOpFlag = LastIdentInfo.m_pCRecSet -> Open (CRecordset::snapshot, LastIdentInfo.m_strSQL,
																CRecordset::readOnly);
			}           
		}                   
		CATCH (CDBException, dbe)
		{   
			bHardError = TRUE;
			OdbcError oe (dbe);
			oe.Show (RC_RetrieveFieldInfo);                                     
		}
		AND_CATCH (CMemoryException, mce)
		{                     
			bHardError = TRUE;      
			DEX_Error (RC_RetrieveFieldInfo, EC_NOMEMORY);
		}
		AND_CATCH (CFileException, fe)
		{
			bHardError = TRUE;
			// DEX_Error (RC_RetrieveFieldInfo, EC_SYSERROR);
			fe -> ReportError ();
		}
		END_CATCH          
		                        
	//	bei Fehler              
		if (bHardError)
			LastIdentInfo.CleanUp (FALSE);		
	}	// end_if // lese neue ODBC-Infos		
		
//	wenn Infos gefunden
int sMinLen = 0;

	if (bOpFlag && LastIdentInfo.HasInfo()) {
	//	FeldInhalt lesen
	CString strVal;
	
		if (LastIdentInfo.m_pCA -> GetFieldInfo (LastIdentInfo.m_pCRecSet, 
												 strVal, ((CFeldInfos *) eData) -> m_sIndex))
		{           
			sMinLen = min (iLen - 1, strVal.GetLength ()); 		
			if (sMinLen)						// mehr als Ende-Zeichen
			{				
				memcpy (pBuffer, strVal, sMinLen);
				pBuffer [sMinLen] = '\0';
				lCntAll += atol (pBuffer);      // Versuch zu addieren

			// 	Zähler aktualisieren
				lCnt++;             
			}				
		}			
	}
	return sMinLen ? pBuffer : NULL;
}
#endif // _TRiAS_VER < 0x0400

// CLastIdentInfo ------------------------------------------------------------------------
CLastIdentInfo::CLastIdentInfo (void)
{
	m_pCDataBase = NULL;
	m_pCRecSet = NULL;
	m_pCA = NULL;

	m_bRefreshed = FALSE;
	m_ulIdent = (ulong) -1L;
}                

CLastIdentInfo::~CLastIdentInfo (void)
{
	CleanUp ();
}              

void CLastIdentInfo::CleanUp (BOOL bEraseIdent)
{       
	if (bEraseIdent)				// Id ggf. beibehalten: Info, daß für diese
		m_ulIdent = (ulong) -1L;	// Klasse keine Anbindung existiert

	m_bRefreshed = FALSE;

	m_strSQL.Empty ();
	m_strTableName.Empty ();

	DELETE_OBJ (m_pCA);
	DELETE_OBJ (m_pCRecSet);                    
	DELETE_OBJ (m_pCDataBase);
}   

BOOL CLastIdentInfo::HasInfo (void) 
{
	return m_bRefreshed && (m_pCA != NULL) && 
		  (m_pCRecSet != NULL) && m_pCRecSet -> IsOpen () && 
		  (m_pCRecSet -> IsBOF () == FALSE);
}

void CLastIdentInfo::RemoveAll (void)
{
	CleanUp (TRUE);
}

BOOL CLastIdentInfo::Refresh (StringDup &strTableName, long lONr, ulong ulIdent)
{
BOOL bOldRefresh = m_bRefreshed;			// was war mit altem ID

	m_bRefreshed = FALSE;					// internes Flag rücksetzen

//	prüfe Parameter
	if (InvalidIdent(ulIdent))
		return FALSE;

	if (g_pCOdbcExtension -> GetOptEnable()) {
		if (m_ulIdent == ulIdent) {				// aktueller ID ist gleich altem ID
		//	"Requery" wird nicht von allen ODBC-Treibern unterstützt
			if (!bOldRefresh || !m_pCRecSet || !m_pCA)
				return FALSE;						// für diesen ID gibt es offensichtlich keine Anbindg.

		//	Kann Requery gemacht werde ?
			if (m_pCRecSet -> CanRestart ())
				return (m_bRefreshed = TRUE);		// alles andere bleibt beim alten
		}
	}

//	ein neuer ID ist gekommen, Anbindung muß komplett neu gelesen werden		
CColumns *pCColumns = NULL;

	m_ulIdent = ulIdent;			// Id auf jeden Fall speichern

//	anderen nicht mehr gebrauchten Objekte löschen
	DELETE_OBJ (m_pCA);					// Spalten Infos		
	DELETE_OBJ (m_pCRecSet);			// Recordset

//	Tabellen-Namen lesen
	TRY	{
	//	Tabellen-Name gegeben ?
		if (!strTableName) 
			return FALSE;
		else
			m_strTableName = strTableName;

	//	neuen DSN-lesen	
	HPROJECT hPr = DEX_GetObjectsProject(ulIdent);
	Profile ProFile(hPr);
	DataSourceType tType = NoDataSource;
	StringDup strNewDSN (ProFile.GetDataSourceName (g_pCOdbcExtension -> _pAliasName, tType), FALSE);

		if (! strNewDSN)
			return FALSE;

	//	Data-Source-Objekt ggf. neu generieren	
		if (!g_pCOdbcExtension -> GetOptEnable() ||	// Optimierung ist nicht erlaubt
		    NULL == m_pCDataBase || 0 != strcmpi (m_pCDataBase -> DataSourceName (), strNewDSN))
		{
			DELETE_OBJ(m_pCDataBase);
			m_pCDataBase = new CDataBaseExt (strNewDSN, tType);
		}

	//	DSN-Objekt öffnen, Abfrage-Klausel gen. usw.
		if (m_pCDataBase -> Open()) {
		//	Info für ein Feld
			pCColumns = new CColumns ((CDatabase *) m_pCDataBase);  
			pCColumns -> m_strTableNameParam = m_strTableName;        

		//	Info aller Felder
			m_pCA = new CColumnObjArray();			

		//	Klausel erzeugen
			if (pCColumns -> Open () && m_pCA -> FillColumnList (*pCColumns)) {	
				pCColumns -> Close ();					// keinen 2. Cursor zulassen

			//	SQL-Select-Anweisung erzeugen: "SELECT * FROM <tablename> 
			CString strWhere;						// dummy-String

				AfxFormatString1 (m_strSQL, IDS_SQLSELECT, m_strTableName);
				m_pCRecSet = new CRecSet(*(CDatabase *)m_pCDataBase
											, *m_pCA
											, strWhere
#ifdef __UseOGX__
											, strWhere	// eh nur'n dummy
#endif //__UseOGX__
										); 
				if (m_pCRecSet -> IsOpen())
					m_pCRecSet -> Close();
				m_bRefreshed = TRUE;
			}
		}
	}
	CATCH (CDBException, dbe)
	{               
		OdbcError oe (dbe);
		oe.Show (RC_RetrieveFieldInfo);                                     
	}
	AND_CATCH (CMemoryException, mce)
	{                           
		DEX_Error (RC_RetrieveFieldInfo, EC_NOMEMORY);
	}
	END_CATCH          
		
//	Speicher freigeben
	DELETE_OBJ(pCColumns);

	return m_bRefreshed;					
}


// Objekteigenschaften --------------------------------------------------------
CODBCObjectProperties::CODBCObjectProperties ()
	: CObjectProperties ()
{
	m_ulIdent = 0;			// letzter ID, für den Objekeigenschaft implementiert wurde
	m_sCnt = 0;				// Anzahl der inst. Objekteigenschaften

	try {
	CString strGroupName;
		
		strGroupName.LoadString (IDS_GROUP_NAME);
		m_strGroup = strGroupName; 
		m_dwFlags = PROPCAPS_NONE;
	}
	catch (CMemoryException *me)
	{
		me -> Delete ();		
		throw E_OUTOFMEMORY;
	}
	g_pCOdbcProperties = this;
}

CODBCObjectProperties::~CODBCObjectProperties (void)
{
	g_pCOdbcProperties = NULL;
}                     

// KK000413
// Korrektur der Parm OnNewReference ... von LONG in INT_PTR
STDMETHODIMP CODBCObjectProperties::OnNewReferenceObjects(INT_PTR lIdent)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (InstallActPropertyFunctions (0, lIdent) > 0)
		return S_OK;
	else
		return E_NOTIMPL;
}

STDMETHODIMP CODBCObjectProperties::OnNewReferenceObject (INT_PTR lRefONr)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (InstallActPropertyFunctions (lRefONr) > 0)
		return S_OK;
	else
		return E_NOTIMPL;
}       

STDMETHODIMP CODBCObjectProperties::OnNewReferenceObjects (INT_PTR lRefObjs, INT_PTR lRefObj)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (InstallActPropertyFunctions (lRefObj, lRefObjs) > 0)
		return S_OK;
	else
		return E_NOTIMPL;
}       

// ObjPropFuncs für das aktive Objekt des aktuellen ORFensters installieren ---
short CODBCObjectProperties::InstallActPropertyFunctions (long lONr, ulong ident)
{   
//	prüfe Parameter
	if (!g_pCOdbcExtension)
		return 0;

CWaitCursor wc;

	CallMessageQueue();	// Nachzeichnen des OR-Fensters
	if (-1 == lONr || -1 == ident)
	{
		RemoveAllPropertyFunctions();
		m_ulIdent = 0;
		return 1;
	}

	if (lONr != 0 && ident == 0) {
	//	prüfe ob sich Objektklasse geändert hat
	ulong ulIdent = DEX_GetObjIdent (lONr);

		if (g_pCOdbcExtension -> GetOptEnable() && (ulIdent == m_ulIdent))	// nur wenn Opt. erlaubt
			return m_sCnt;				// nein, zurück mit gespeichertem Zähler

		m_ulIdent = ulIdent;			// neuen Id speichern
		m_sCnt = 0;						// Anzahl Eigenschaften rücksetzen
		RemoveAllPropertyFunctions();	// alle Eigenschaften löschen

		if (g_pCOdbcExtension -> ReadDBaseCodes (lONr, ulIdent) < 2)	// INI lesen
			return 0;                    								// keine ODBC-Anbindung
		return (m_sCnt = InstallIdentPropertyFunctions (ulIdent));				
	}
	RemoveAllPropertyFunctions();

list<HPROJECT> ProjectList;	// hier werden die zu durchforstenden Projekte gespeichert

//	Anbindung für alle Objektklassen
	if (InvalidIdent (ident)) {
	// JG hier Schleife über alle DQ's
		if (FAILED(EnumAllProjects(ProjectList)))
			return 0;
		m_ulIdent = 0;				// Id löschen
	}
	else {
	// Anbindung nur für die angegebene Objektklasse
	HPROJECT hPr = DEX_GetObjectsProject(ident);

		ProjectList.push_back(hPr);
		m_ulIdent = ident;	// merken
	}
	m_sCnt = 0;						// Anzahl Eigenschaften rücksetzen

short sCnt = 0;			
CTableNameTree * pTableNameTree = NULL;
	
	for (list<HPROJECT>::iterator it = ProjectList.begin();it!= ProjectList.end(); ++it)	{
	HPROJECT actProject = (*it);

		TRY	{                   
		//	Ini-Dateinamen lesen	
		Profile ProFile(actProject);				    

			if (!ProFile.GetProFileName())
				return 0;

			pTableNameTree = new CTableNameTree;
                        
		//	Puffer init.                        
		const short BufferSize = 2048;
		CString strBuffer;
		char *pBuffer = strBuffer.GetBuffer (BufferSize);

			*pBuffer = '\0';

		// JG Diesen Weg um Kontext zu erhalten, das ist ein Kandidat für 'ne Funktion(Macro)
		// wollt ich mir aber sparen (Es ist schließlich März ;-))
		const short SECTIONCOUNT = 2;
		CString strSections[SECTIONCOUNT];

			VERIFY(strSections[0].LoadString (IDS_ODBC_SECTION_OLD));
			VERIFY(strSections[1].LoadString (IDS_ODBC_SECTION));

			for (int i = 0; i < SECTIONCOUNT; i++) {
			//	alle gültigen Strings lesen		
			CString strSection (strSections[i]);

				if (GetPrivateProfileString (strSection, NULL, "", pBuffer, BufferSize, ProFile.GetProFileName ()))
				{
				ulong ulIdent = 0;		// akt. ID
				long *pMKs = NULL;
				char **ppMStrs = NULL;
				short sActParams = 0;

				//	für alle IDs die Objekteigenschaften lesen			
					for (char *pBuff = pBuffer; *pBuff; pBuff += lstrlen (pBuff) + 1) {                
					//	aktuellen ID bestimmen  
					HRESULT HRO = IdentFromClassX (actProject,pBuff + 2, &ulIdent, FALSE);

						if (S_OK != HRO)
							continue;			// weiter

					//  JG geht es um nur eine Objektklasse ?
						if (!InvalidIdent(ident) && ident != ulIdent) 
						// ja, dann raus wenn es nicht diese Objektklasse ist 
							continue;

						sActParams = ProFile.ReadOdbcCodes (&pMKs, &ppMStrs, (long) ulIdent);

					//	alle Objekteigenschaften dieser Objektklasse install.					
						if ((sActParams > 1) &&
							(pMKs[0] == -1) && (ppMStrs[0] != NULL) && (*ppMStrs[0]) &&	// AliasName OK
							((pMKs[1] == -1) || (pMKs[1] == -2)) &&
							(ppMStrs[1] != NULL) && (*ppMStrs [1]))	// FeldName OK	
						{
							sCnt += InstallIdentPropertyFunctions (ulIdent, pTableNameTree, ppMStrs [0]);
						}

					//	MKodes und MStr-Speicher freigeben
						for (short i = 0; i < sActParams; i++)
							DELETE_VEC (ppMStrs [i]);
						DELETE_VEC (ppMStrs);
						DELETE_VEC (pMKs);
					}	// end_for
				}
			}
		}		
		CATCH (CMemoryException, cme) 
		{
			DEX_Error (RC_InstPropFunction, EC_NOMEMORY);
		}	  
		END_CATCH   

	//	Speicher freigeben
		DELETE_OBJ (pTableNameTree);    
	}	
	return sCnt;	
}
                                         
// ObjPropFuncs für das aktive Objekt des aktuellen ORFensters installieren ---
short CODBCObjectProperties::InstallIdentPropertyFunctions (
	ulong ulIdent, CTableNameTree *pTableNameTree, char *pAliasName)
{
	if 	(!g_pCOdbcExtension)
		return 0;
		
//  Table-Namen lesen
	// JG 990311
HPROJECT hPr = DEX_GetObjectsProject(ulIdent);
Profile ProFile(hPr);

	if (!ProFile.GetProFileName())
		return 0;
	
StringDup strTableName (ProFile.GetTableName (pAliasName ? pAliasName : g_pCOdbcExtension -> _pAliasName), FALSE);

	if (!strTableName)
	{               
		DEX_Error (RC_InstPropFunction, EC_NOTABLENAME);
		return 0;
	}                                           

//	ggf. Test, ob Tabelle schon installiert ?
	if (pTableNameTree && pTableNameTree -> Exist (strTableName))
		return 0;

CErrMessageBlocker Block;	// keine Messages
CDataBaseEx *pCDataBase = NULL;
CColumns *pCColumns = NULL;        
int sCnt = 0;							// Anzahl der installierten Funktionen	

	TRY {                                                        
		pCDataBase = new CDataBaseEx;
		if (pCDataBase -> OpenAlias (pAliasName ? pAliasName : g_pCOdbcExtension -> _pAliasName, hPr))
		{
			pCColumns = new CColumns ((CDatabase *) pCDataBase);  
		
		//	Tabellen-Namen speichern				
			pCColumns -> m_strTableNameParam = strTableName;

			if (pCColumns -> Open ()) {
			// 	lese alle Feldnamen         
			CString strFctName;				// akt. Funktion
			short sIndex = -1;					// Index mitzählen

				while (!pCColumns -> IsEOF()) {                               
					sIndex++;					// Index erhöhen
					if (pCColumns -> IsPropField())	{
					//	neue FieldInfo erzeugen
					CFeldInfos *pFieldInfo = new CFeldInfos;

						pFieldInfo -> m_hPr = hPr;
						pFieldInfo -> m_strAlias = pAliasName ? pAliasName : g_pCOdbcExtension -> _pAliasName;
						pFieldInfo -> m_strTableName = strTableName;			// Tabellennamen speichern
						pFieldInfo -> m_iDataType = pCColumns -> m_nDataType;	// FeldTyp speichern
						pFieldInfo -> m_sIndex = sIndex;						// Index speichern
						pFieldInfo -> m_strFeldName = pCColumns -> m_strColumnName;	// Feldnamen speichern

					//	Functionname erzeugen
						AfxFormatString2 (strFctName, IDS_OBJPROPFUNC, pFieldInfo -> m_strTableName, pFieldInfo -> m_strFeldName);

#if _TRiAS_VER < 0x0400
						AddPropertyFunctionEx ((const char *)strFctName, RetrieveFieldInfo, (DWORD)pFieldInfo, FreeFieldName);
#else
					CObjProps::iterator it = m_mapObjProps.find(os_string(strFctName));

						if (it == m_mapObjProps.end()) {
						CComObject<CODBCProperty> *pProp = NULL;

							if (FAILED(CComObject<CODBCProperty>::CreateInstance(&pProp)))
								AfxThrowMemoryException();
							pProp -> AddRef();			// RefCnt jetzt 1

							pProp -> SetName(strFctName);
							pProp -> SetFieldInfo(pFieldInfo);
							pFieldInfo = NULL;			// pProp hat pFieldInfo übernommen

						// mit allem sontigen Nötigen versehen (ITRiASLockFeature)
						WObjectProperty ObjProp;
						WInitInnerObject FakeLock (CLSID_FakeTRiASLockFeature);

							FakeLock -> SetInnerObject (pProp -> GetUnknown(), (GUID *)&ObjProp.GetIID(), ObjProp.ppu());
							if (!ObjProp.IsValid())
								ObjProp = pProp;

							AddPropertyFunction(ObjProp);		// bei TRiAS anmelden
							m_mapObjProps.insert(CObjProps::value_type(os_string(strFctName), ObjProp));
						}
						else
							AddPropertyFunction((*it).second);
#endif // _TRiAS_VER < 0x0400
						sCnt++;						// Feldzähler erhöhen
					}	// property field
		
				// 	lese nächste Feld-Info       
					pCColumns -> MoveNext();                      
				}
			}			
		}		// Database not open

	//	ggf. Tabellennamen speichern
		if (pTableNameTree)
			pTableNameTree -> AddTable (strTableName);
	}                       
	CATCH (CMemoryException, e)	
	{   
		DEX_Error (RC_InstPropFunction, EC_NOMEMORY);               
	}                
	AND_CATCH (CDBException, dbe)   
	{                   
		OdbcError oe (dbe);
		oe.Show (RC_InstPropFunction);                 
	}
	AND_CATCH (CFileException, fe)
	{
		// DEX_Error (RC_InstPropFunction, EC_SYSERROR);               	
		fe -> ReportError ();
	}
	END_CATCH                                               
	
// 	Speicher freigeben
	DELETE_OBJ (pCColumns);					
	DELETE_OBJ (pCDataBase);

	return sCnt;	
}
