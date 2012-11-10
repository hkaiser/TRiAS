/* 
	File: ODBCEXT.CPP (Version für MFC 4.0 - ODBC)
	Anzeige von ODBC-Daten.

	Erarbeitet: J. Benkenstein						Stand vom 04.01.1996
*/

#include "pheader.h"                // vorübersetzte Header
#include "odbcext.hr"				// ResourceKonstanten

//	STL-Header
#include <ospace/com/smartif.h>

#include <odbcinst.h>				// SQLManageDataSources ()

#include <xtsnpropatl.h>			// CObjectProperties
#include <xtsnaux.hxx>				// ExtOleRegisterClass () u.a.
#include <registrx.hxx>

#include <hpp/relation.hpp>             // DBaseRel
#include <hpp/getodbci.hpp>
#include <hpp/columnst.hpp>             // CColumns 
#include <hpp/helptext.hpp>				// CHelpText                                                   
#include <hpp/actwind.hpp>				// CActivateWindow
#include <hpp/TabDlgs.hpp>				// CTabbedDialogs

#include "profile.hpp"             	// DBaseProfile
#include "database.hpp"             // CDataBase            
#include "dispatch.hpp"             // dBaseDispatch
#include "UserDlg.h"				// CUserDlg
#include "FileDlg.h"				// CFileDsnPage
#include "connect.hpp"				// CConnect

#include "importpa.hpp"				// CImportParams
#include "abglpge.hpp"				// CAbgleichPage                                                    
#include "dsnpage.hpp"				// CDsnPage
#include "filtrpge.hpp"				// CFilterPage
#include "rsltpge.hpp"				// CResultPage

#ifndef WIN32
#include <progress.hpp>				// CProgressCtrl
#endif                                               

#include "pktinfo.hpp"				// CPunktInfoTree
#include "Abgleich.hpp"				// CDoAgleich             
#include "ImpRslt2.hpp"				// Aktionsergebnis-Anzeige

#ifdef WIN32            
#include "triaspge.hpp"				// CTriasPage
#include "feldpage.hpp"				// CFeldPage
#else
#include "trs16pge.hpp"				// CTriasPage
#include "fld16pge.hpp"				// CFeldPage
#endif

#include "importsh.hpp"				// CImportSheet

//	GUID-Header
#include "whereprp.h"				// CLSID_WhereKlauselPropAct
#include <xtsnguid.h>
#include <initguid.h>           
#include "odbcguid.h"
#include "version.h"

#include <hpp/propactb.hpp>				// CPropertyAction
#include "whereprp.hpp"				// CWhereKlauselPropAct

#include "odbcext.hpp"             	// zugeh. Header

#include "fakename.h"				// var. AppName

#include <locale.h>					// loakales Datumsformat
#include "features.h"

//  Konstanten
const short MinParCnt = 2;      	// min. Anz. der Parameter in der INI-Datei
const int BeginExpr = '{';      	// Separatoren in dBase-Expressions
const int EndExpr = '}';

// globale Variablen
COdbcExtension *g_pCOdbcExtension = NULL;
CDataBaseExtTree *g_pDataBaseTree = NULL;
int g_sMkBase = 10;						// und Merkmale

// externe Variablen
#if _TRiAS_VER < 0x0400
extern CLastIdentInfo LastIdentInfo;		
#endif // _TRiAS_VER < 0x0400
extern CODBCObjectProperties *g_pCOdbcProperties;

const char g_cbRegOdbcConfig[] = TEXT("Software\\" REG_COMPANY_KEY "\\" 
	REG_PRODUCT_KEY "\\Extensions\\TRiAS.OdbcExtension.1\\Config"); 

// Variablen
#ifndef WIN32
CExtDLL NEAR MyExtension ("odbcext.ext");      		// für MFC-Anbindung benötigt
#endif

///////////////////////////////////////////////////////////////////////////////
// ClassFactory/registry support
BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_ODBCExtension, COdbcExtension)
	OBJECT_ENTRY(CLSID_WhereKlauselPropAct, CWhereKlauselPropAct)
END_OBJECT_MAP()

_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;
}

// globale Funktionen -------------------------------------------------------------
// Nachzeichnen des Parent-Windows
void CallMessageQueue (void)
{                         
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
	{
    	if (msg.message == WM_QUIT)
    		return;

    	TranslateMessage(&msg);
    	DispatchMessage(&msg);
	}
}	                            

/*
CTriasExtension *NewExtension (void)
{              
	g_pCOdbcExtension = NULL;         
	// g_pDataSourceTree = NULL;
		
	TRY 
	{
		g_pCOdbcExtension = new COdbcExtension ();
	}
	CATCH (CMemoryException, mce)
	{
		return NULL;
	}                           
	END_CATCH
	
	return g_pCOdbcExtension;
}

void DeleteExtension (CTriasExtension *pTE)
{
	DELETE_OBJ (pTE);
}

BOOL GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
    memcpy (&rClsID, &CLSID_ODBCExtension, sizeof (GUID));
	return TRUE;
}
*/

// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll.
BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
    char ExtName [] = "TRiAS.OdbcExtension.1";

	if (fRegister) 
	{// RegDB initialisieren
		BOOL fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
                                					  CLSID_ODBCExtension, 
                                					  TEXT(ExtName), IDS_LONGCLASSNAME,
                                					  ODBCEXT_MAJORVERSION, ODBCEXT_MINORVERSION, EFUnLoadable|EFVisible);
		if (!fSuccess) 
			return false;
	} 
	else 
	{// RegDB säubern
        return ExtOleUnregisterClass (CLSID_ODBCExtension, TEXT(ExtName));
	}

	return true;	// alles ok
}

// COdbcExtension -----------------------------------------------------------------
COdbcExtension::COdbcExtension (void)
				: CTriasExtension (/*IDM_ODBC*/)	// JG 990430 we didn't need a Menu in the root
{
	_hWndLast = NULL;       // FensterHandle des letzten ORFensters
	_lONr = -1;				// ObjektNummer
	_lIdent = 0;           	// Identifikator
	_Type = FeldName;       // Parameter-Typ

	_pAliasName = NULL;     // aktuell zu verwendende DBaseDatei
	_pFieldName = NULL;    	// aktuelles DBaseSchlüssel für die Anbindung
	_pKeyName = NULL;      	// aktueller Schlüssel
								
	_pDispatcher = NULL;	// akt. Dispatcher	
	g_pDataBaseTree = NULL;	// DataBase-Baum

//	Interface-Zeiger		
	// m_pIObjProp = NULL;		// ObjectEig.
	m_bShowInfo = TRUE;		// ODBC-Fenster erlaubt
#ifdef WIN32
	CCurrentUser regCfg(g_cbRegOdbcConfig, false, KEY_READ);
	DWORD dwData = 0;
	
	if (!regCfg.GetDWORD("Optimise", dwData) || 0 == dwData)
		m_bOptEnable = FALSE;	// Optimierung ausschalten
	else
		m_bOptEnable = TRUE;	// default is on
#else
	m_bOptEnable = FALSE;	// hier zu sehr mit Fehlern behaftet
#endif

	g_pCOdbcExtension = this;
	m_pPopupMenu	= NULL;
	_tsetlocale(LC_TIME, NULL);	// JG now we support the local Time-formats

	m_pErrMsgHdl = new CErrMessageHandler();	// default : ShowErrMsg
}

// Destruktor -----------------------------------------------------------------
COdbcExtension::~COdbcExtension (void)
{
//  Strings für die Anbindung der Dateien wieder freigeben
	DELETE_VEC (_pAliasName);           
	DELETE_VEC (_pKeyName);
	DELETE_VEC (_pFieldName);
	
	DELETE_OBJ (_pDispatcher);          // DBaseDispatcher wieder freigeben
	// DELETE_OBJ (m_pIObjProp);
                               
	DELETE_OBJ (g_pDataBaseTree);
	DELETE_OBJ (m_pErrMsgHdl);			
	g_pCOdbcExtension = NULL;
}

HRESULT COdbcExtension::FinalConstruct (void)
{
	HRESULT hr = NO_ERROR;

	try	{
		hr = CTriasExtension::FinalConstruct ();
		if (FAILED(hr))
			throw hr;

		hr = CObjectProperties::FinalConstruct ();
	}
	catch (HRESULT hrr)
	{
		hr = hrr;
	}

	return hr;
}

// da wir ein zusätzliches Interface dazugenommen haben, muß ein modifiziertes 
// QueryInterface gegeben sein
/*
HRESULT COdbcExtension::QueryInterface (THIS_ REFIID riid, LPVOID *ppvObj)
{                     
	if (riid == IID_IObjectProps)
		*ppvObj = m_pIObjProp;  		// Eigenschaften-Interface liefern 
	else
		return CTriasExtension::QueryInterface (riid, ppvObj);							

// 	AddRef nicht vergessen
	LPUNKNOWN(*ppvObj) -> AddRef();

	return NOERROR;
}
*/

// in Registry vermerken, daß der nächste RechercheDialog vollständig neu erzeugt werden muß
const char g_cbForceReload[] = "Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\TRiASEx\\TRiAS.Application.4\\SearchEngines";

BOOL ForceReloadSearchDlg()
{
CCurrentUser regSI (g_cbForceReload, true);

	return regSI.SetDWORD("ForceReload", 1);
}

// Initialisierung
STDMETHODIMP_(BOOL) COdbcExtension::InitExtension (short iMode)
{            
	if (!CTriasExtension::InitExtension (iMode))
		return false;

// Initialisierung der Grid-Klassen
	GXInit();
	GXInitODBC();	

#ifndef WIN32
	MyExtension.m_pMainWnd = MWind();             // für MFC setzen
#endif

	g_sMkBase = DEX_GetMkBase ();						

	TRY {
		_pDispatcher = new DBaseDispatchTree;        // Dispatcher der DBaseFenster
#ifdef WIN32
		g_pDataBaseTree = new CDataBaseExtTree;
#endif	

		InitFakeName();		// variablen App_Name initialisieren
		InstallMainMenu();	// Menü ins ExtraMenü inhängen
	}
	CATCH (CMemoryException, cme)
	{            
		return FALSE;
	}
	END_CATCH       

//  hier zusätzlichen MenüPunkt anhängen
	InstallMenuItem (IDM_SHOWDBASE, IDS_DBASEMENUITEM, TRUE, 0);

//  Notifikationen anfordern
	RegisterNotification (DEX_CREATEOBJEKTINFO);
	RegisterNotification (DEX_OBJWNDCLOSED);
	RegisterNotification (DEX_OBJECTUNSELECTED);
	RegisterNotification (DEX_OBJECTSELECTED);
	
#ifdef WIN32	      
	RegisterNotification (DEX_GOTOBJWNDFOCUS);
#else
	RegisterNotification (DEX_OBJWNDFOCUSCHANGED);
#endif
	RegisterNotification (DEX_PROJECTOPEN);
	RegisterNotification (DEX_PROJECTCLOSE);

	ForceReloadSearchDlg();
	return TRUE;
}

STDMETHODIMP_(BOOL) COdbcExtension::UnLoadExtension (void)
{
//  Alle installierrten Funktionen hier wieder abmelden
/*
	if (m_pIObjProp)
		m_pIObjProp -> RemoveAllPropertyFunctions ();
*/
	RemoveAllPropertyFunctions ();
	m_LastIdentInfo.RemoveAll();			// alle zugeh. Objekte freigeben
	if (g_pDataBaseTree)
		g_pDataBaseTree -> RemoveAllDataSources ();
	
//  MenüPunkt natürlich wieder ausbauen
	RemoveMenuItem (IDM_SHOWDBASE, TRUE, 0);
	RemoveMainMenu();

//  Notifikationen wieder abmelden
	UnRegisterNotification (DEX_PROJECTCLOSE);
	UnRegisterNotification (DEX_PROJECTOPEN);
#ifdef WIN32
	UnRegisterNotification (DEX_GOTOBJWNDFOCUS);
#else
	UnRegisterNotification (DEX_OBJWNDFOCUSCHANGED);
#endif
	UnRegisterNotification (DEX_OBJECTSELECTED);
	UnRegisterNotification (DEX_OBJECTUNSELECTED);
	UnRegisterNotification (DEX_OBJWNDCLOSED);
	UnRegisterNotification (DEX_CREATEOBJEKTINFO);

	ForceReloadSearchDlg();

	return CTriasExtension::UnLoadExtension();
}

// Diese Funktion dient der Behandlung der MenuKommandos vom nutzereigenen
// Menu der Erweiterung
STDMETHODIMP_(BOOL) COdbcExtension::MenuCommand (UINT MenuItemID, HWND hWnd)
{
	TRY {
		switch (MenuItemID) {   
		case IDM_CALL_ADMIN:				// Administrator rufen
			{
			CSyncThread syn (this);	

				if (g_pCOdbcProperties)			// Optimierung der Eigenschaften rücksetzen
					g_pCOdbcProperties -> ResetOptInfo();

				m_bShowInfo = FALSE;
				m_LastIdentInfo.RemoveAll();		// noch evtl. vorh. DSN freigeben
				if (g_pDataBaseTree)
					g_pDataBaseTree -> RemoveAllDataSources ();

				::SQLManageDataSources (g_pCOdbcExtension -> hWnd());
				m_bShowInfo = TRUE;
			}
			return TRUE;
		
		case IDM_SHOWDBASE:
			{
				if (m_bShowInfo && (hWnd != 0) && _pDispatcher)
				   ShowDBaseInfo (); 	
			}
			return TRUE;			
		
		case IDM_ODBCENTRY:
			{      
			CSyncThread syn (this);	

				if (g_pCOdbcProperties)			// Optimierung der Eigenschaften rücksetzen
					g_pCOdbcProperties -> ResetOptInfo();

				m_bShowInfo = FALSE;
				m_LastIdentInfo.RemoveAll ();			// noch evtl. vorh. DSN freigeben
				if (g_pDataBaseTree)
					g_pDataBaseTree -> RemoveAllDataSources ();
				CConnect Connect (NULL, DEX_GetActiveObject (hWnd));
				if (Connect.Result ())
					Connect.DoModal ();
				m_bShowInfo = TRUE;
			}
			return TRUE;        
		
		case IDM_IMPORT_PARAM:
			{
				CSyncThread syn (this);	

				if (g_pCOdbcProperties)			// Optimierung der Eigenschaften rücksetzen
					g_pCOdbcProperties -> ResetOptInfo ();

				m_bShowInfo = FALSE;
				m_LastIdentInfo.RemoveAll ();		// noch evtl. vorh. DSN freigeben
				CActivateWindow aw (g_pCOdbcExtension -> hWnd ());		//	Parent-Fenster deakt.
				CImportSheet Sheet (IDS_IMP_CAPTION);
				if (Sheet.m_bResult)
				{
	#ifdef WIN32				
					Sheet.SetWizardMode ();
	#endif					
					Sheet.DoModal ();
				}
				m_bShowInfo = TRUE;
			}
			return TRUE;

	#ifdef WIN32										
		case IDM_OPTIMIZE:				// Optimierung ein/ausschalten
			{
			CSyncThread syn (this);	

				if (g_pCOdbcProperties)			// Optimierung der Eigenschaften rücksetzen
					g_pCOdbcProperties -> ResetOptInfo ();

				if (m_bOptEnable)
				{
					m_bOptEnable = FALSE;
					DELETE_OBJ (g_pDataBaseTree);
				}
				else
				{
					m_bOptEnable = TRUE;
					if (!g_pDataBaseTree)		// wenn Baum noch nicht ex.
						g_pDataBaseTree = new CDataBaseExtTree;
				}

				:: CheckMenuItem (MenuHandle (), IDM_OPTIMIZE+MenuOffset(), 
				   MF_BYCOMMAND | (m_bOptEnable ? MF_CHECKED : MF_UNCHECKED));
			}
			return TRUE;
	#endif			
		}				
	}
	CATCH (CMemoryException, me)	
	{
		DEX_Error (RC_MenuCommandCOdbcExtension, EC_NOMEMORY);                             				
	}			
	END_CATCH
	
	return FALSE;								// Nachricht nicht behandelt
}

// Herausfinden, ob das aktive Objekt DBaseDaten hat, Menu --------------------
// entsprechend richten 
STDMETHODIMP_(BOOL) COdbcExtension::MenuInit (HMENU hMenu, LPARAM, HWND hWnd)
{
	if (hWnd == 0) {		// MenuInit aus HauptMenu
	//  aktive DSNames dürfen nicht geändert werden !
		if (g_pDataBaseTree && g_pDataBaseTree -> HasReferences ())		
		{
			EnableMenuItem (hMenu, IDM_ODBCENTRY+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
			EnableMenuItem (hMenu, IDM_CALL_ADMIN+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);                        
//			EnableMenuItem (hMenu, IDM_IMPORT_PARAM+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);		 				
		#ifdef WIN32
			EnableMenuItem (hMenu, IDM_OPTIMIZE+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);			
		#endif
		}
		else
		{
			EnableMenuItem (hMenu, IDM_ODBCENTRY+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);		    
			EnableMenuItem (hMenu, IDM_CALL_ADMIN+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);			
//			EnableMenuItem (hMenu, IDM_IMPORT_PARAM+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);	 		
		#ifdef WIN32
			EnableMenuItem (hMenu, IDM_OPTIMIZE+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);			    
		#endif
		}

		return TRUE;		// Menüpunkt wurde behandelt
	}

//	Recherche momentan möglich ?
	if (!m_bShowInfo)
	{
		EnableMenuItem (hMenu, IDM_SHOWDBASE+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);	
		return TRUE;
	}

	_lONr = DEX_GetActiveObject (hWnd);     // 1. ObjektNummer besorgen
	if (_lONr == -1L) 
	{
		EnableMenuItem (hMenu, IDM_SHOWDBASE+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		return TRUE;
	}

short Status = DEX_GetObjectStatus (_lONr);

	if (Status != OSNormal && Status != OSModified) {
	// Objekt existiert nicht
		_lONr = -1L;
		EnableMenuItem (hMenu, IDM_SHOWDBASE+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		return TRUE;
	}

	_lIdent = (ulong) DEX_GetObjIdent (_lONr);      // 2. Identifikator besorgen            
			
//  3. in INI-Datei des Projektes nach DBaseEinträgen (MCodes) suchen
	if (ReadDBaseCodes (_lONr, _lIdent) >= MinParCnt) 
		EnableMenuItem (hMenu, IDM_SHOWDBASE+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
	else
		EnableMenuItem (hMenu, IDM_SHOWDBASE+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

	return TRUE;
}

// Diese Funktion wird bei Systemereignissen diverser Natur gerufen -----------
LRESULT COdbcExtension::Notification (WPARAM iMsg, LPARAM p)
{
	switch (iMsg) {
	case DEX_CREATEOBJEKTINFO:
		_hWndLast = (HWND) p;
		break;

	case DEX_OBJWNDCLOSED:
		{                                  
			if (_pDispatcher != NULL) 
				_pDispatcher -> AllDelete ((HWND) p);       // DBaseFenster freigeben
		}       
		break;
								
	case DEX_OBJECTSELECTED:                               
		{   
			if (_pDispatcher == NULL) 
				break;
	
		long lLastObj = _pDispatcher -> ActObj (_hWndLast);
		
			if (lLastObj != -1L && DEX_GetActiveObject (_hWndLast) != lLastObj)
			// innerhalb eines ORFenster wurde Objekt gewechselt
				_pDispatcher -> AllDelete (_hWndLast);       // DBaseFenster freigeben
		}     
		break;
	
	case DEX_OBJECTUNSELECTED:
		break;          // andere wollen diese Meldungen auch noch haben

#ifdef WIN32
	case DEX_GOTOBJWNDFOCUS:		
#else
	case DEX_OBJWNDFOCUSCHANGED:
#endif
		{   
		//  wenn ein anderes ORFenster den Focus erhalten hat, Dispatcher
		//  für dieses Fenster anlegen
#ifdef WIN32
			_hWndLast = (HWND) p;
#else
			if (LOWORD(p) && (uint) _hWndLast != HIWORD(p)) 
				_hWndLast = (HWND) HIWORD(p);      // ORFensterHandle merken
#endif
			break;
		}                       

	case DEX_HEADERREREAD:					// Header neu lesen
		g_sMkBase = DEX_GetMkBase();						
		break;

	case DEX_PROJECTOPEN:                   // neues Projekt wurde eröffnet
		{   
			g_sMkBase = DEX_GetMkBase ();			

			TRY {
			// DBaseFensterDispatcher initialisieren
				DELETE_OBJ (_pDispatcher);
				_pDispatcher = new DBaseDispatchTree (); 
				_hWndLast = NULL;
			}
			CATCH (CMemoryException, mce)
			{
				DEX_Error (RC_NotifydBaseExt, EC_NOMEMORY);                                             
			}
			END_CATCH
		}
		break;

	case DEX_PROJECTCLOSE:          // project is to be closed
		{                           
			DELETE_OBJ (_pDispatcher);                          
			_hWndLast = NULL;

		// Objekteigenschaften freigeben
			RemoveAllPropertyFunctions();
#if _TRiAS_VER >= 0x0400
			ResetObjProps();
#endif // _TRiAS_VER >= 0x0400
		}
		break;
	}                       // end_switch
	return FALSE;   // alles andere ignorieren
}

// Testet, ob ein vorgegebener MerkmalsWert existiert -------------------------
BOOL COdbcExtension::ExistsMValue (long lONr, ulong lMCode)
{
	return GetMerkmalsValue (lONr, lMCode);
}

// Liefert einen vorgegebenen MerkmalsWert ------------------------------------
BOOL COdbcExtension::GetMerkmalsValue (long lONr, ulong lMCode, char *pBuffer, short iLen)
{
	if (lMCode != 0) {
	// MerkmalsWert holen
	TARGETMERKMAL tm;

		tm.dwSize = sizeof(TARGETMERKMAL);
		tm.lTarget = lONr;              // ObjektNummer
		tm.lMCode = lMCode;             // MerkmalsCode
		tm.imaxLen = iLen;
		tm.pMText = pBuffer;            // kein Buffer: nur Test
		tm.iTTyp = TT_Objekt;
		DEX_GetTextMerkmal (tm);
		return tm.imaxLen > 0;
	}
	return FALSE;
}

// Anzeigen der DBaseInfo für das aktive Objekt dieses ORFensters -------------
BOOL COdbcExtension::ShowDBaseInfo (void) 
{
BOOL iResult = FALSE;

//  Überpüfen, ob schon Dispatcher für dieses Fenster existiert
CTable t (*_pDispatcher);

    if (_hWndLast != NULL) {
		if (!t.Find ((void *)&_hWndLast)) {
		//  noch kein dBaseDispatch für dieses Fenster angelegt
		long lActObj = DEX_GetActiveObject (_hWndLast);
		dBaseDispatchCreator DBCr (*_pDispatcher);                       

			TRY	{        
				::ContCreate (DBCr, dBaseDispatch)(_hWndLast, lActObj);
			}
			CATCH (CMemoryException, cme)           
			{
				DEX_Error (RC_ShowDBaseInfoCDBaseExt, EC_NOMEMORY);                             
				return FALSE;
			}    
			END_CATCH
		}

	//  DBaseFenster zum Dispatcher hinzufügen und anzeigen
		_pDispatcher -> ShowDBaseWindowField (_hWndLast, _pAliasName, _pFieldName, _pKeyName);
		iResult = TRUE;
    }
    return iResult;
}       
                                         
//	gültiger MerkmalsCode ?                                         
BOOL COdbcExtension::ValidMK (long MK)    
{                          
	return MK > 0 || MK < -3L ? True : False;
}	

// Lesen der INI-Datei für ein Objekt nach DBaseInformationen -----------------
short COdbcExtension::ReadDBaseCodes (long lONr, ulong lIdent)
{   
//JG 990311
HPROJECT hPr = DEX_GetObjectsProject(lIdent);
Profile ProFile(hPr);          // ProjektINI
long *pMKs = NULL;
char **ppMStrs = NULL;                                             
int iCnt = ProFile.ReadOdbcCodes (&pMKs, &ppMStrs, (long) lIdent);
short iMCnt = 0;				// Anzahl der real gelesenen Parameter

	DELETE_VEC (_pAliasName);           // alten Infos freigeben
	DELETE_VEC (_pKeyName);
	DELETE_VEC (_pFieldName);

	_Type = FeldName;               // Typ setzen

	TRY {
	// 	wenn Merkmale existieren, dann hat Objekt DBaseDaten
		if (pMKs != NULL && ppMStrs != NULL && iCnt >= MinParCnt) {
		// 	1. Parameter immer dBase-File-Name
			if (ValidMK (pMKs[0]) && ExistsMValue (lONr, pMKs[0])) {
				_pAliasName = new char [_MAX_PATH];
				if (GetMerkmalsValue (lONr, pMKs[0], _pAliasName, _MAX_PATH))
					iMCnt++;
			} 
			else if (ppMStrs[0] != NULL) {
				_pAliasName = ppMStrs[0];
				ppMStrs[0] = NULL;              // delete verhindern
				iMCnt++;
			}

		// 	2. Parameter Feld-, Tagname oder dBase-Expression
			if (ValidMK (pMKs [1]) && ExistsMValue (lONr, pMKs[1])) {
				_pFieldName = new char [_MAX_PATH];
				if (GetMerkmalsValue (lONr, pMKs[1], _pFieldName, _MAX_PATH))
					iMCnt++;
			} 
			else {
				if (pMKs[1] == -1L && ppMStrs[1] != NULL) {
					_pFieldName = ppMStrs[1];
					ppMStrs[1] = NULL;       // doppeltes delete verhindern
					iMCnt++;
				} else {
					if (pMKs[1] == -3L && ppMStrs[1] != NULL) { // Tag gegeben
						_Type = TagName;
						if (ExistsMValue (lONr, strtoul (ppMStrs[1], NULL, g_sMkBase))) {
							_pFieldName = new char [_MAX_PATH];
							if (GetMerkmalsValue (lONr, strtoul (ppMStrs[1], NULL, g_sMkBase), _pFieldName, _MAX_PATH))
								iMCnt++;
						} 
						else {        // Tagname direkt gegeben
							_pFieldName = ppMStrs[1];
							ppMStrs[1] = NULL;      // dopp. löschen verh.
							iMCnt++;
						}
					} else {
						if (pMKs[1] == -2L && ppMStrs[1] != NULL) { // dBase-Express.
							_Type = dBaseExpr;
							if (_pFieldName = _ExpandDBaseExpression (lONr, ppMStrs[1]))
								iMCnt++;
						}
					}
				}
			}

		// optionaler 3. Parameter Feldinhalt oder Schlüssel
			if (iCnt > MinParCnt) {
				if (ValidMK (pMKs[2]) && ExistsMValue (lONr, pMKs[2])) {
					_pKeyName = new char [_MAX_PATH];
					if (GetMerkmalsValue (lONr, pMKs[2], _pKeyName, _MAX_PATH))
						iMCnt++;
				} else if (ppMStrs[2] != NULL) {
					_pKeyName = ppMStrs[2];
					ppMStrs[2] = NULL;       // doppeltes delete verhindern
					iMCnt++;
				}
			}
		}
		
	//	Typ ggf. ändern
	//	if (iMCnt == MinParCnt)         // bei nur 2 Parametern ist keine
	//		_Type = dBaseExpr;			// andere Abfragart möglich
			
	//	prüfe gelesene Parameter        
		switch (_Type)
		{
			case TagName:									// aus Kompatbilitätsgründen (Index)
			case FeldName:    								// Feldname	
			{
				if ((iMCnt < 3) ||		// Anbindung nur über wenigstens 3 Parameter				
					(!_pAliasName) || (!*_pAliasName) ||	// gültigen AliasNamen
					(!_pFieldName) || (!*_pFieldName)  ||	// gültigen Feld/Tagnamen
					(!_pKeyName) || (!*_pKeyName))			// und gültigen Schlüssel
					iMCnt = 0;					
			}			
			break;
			case dBaseExpr:									// WHERE-Klausel
			{
				if ((iMCnt < MinParCnt) ||		// Anbindung nur über wenigstens 2 Parameter				
					(!_pAliasName) || (!*_pAliasName) ||	// gültigen AliasNamen
					(!_pFieldName) || (!*_pFieldName)) 		// gültige Klausel
					iMCnt = 0;					
			}   
			break;                                                      
			default:
				iMCnt = 0;
		}

	// 	Speicher wieder freigeben
		DELETE_VEC (pMKs);  
		if (ppMStrs != NULL) {
			for (short iLoop = 0; iLoop < iCnt; iLoop++) {
				if (ppMStrs[iLoop]) 
					DELETE_VEC (ppMStrs[iLoop]);
			}
			DELETE_VEC (ppMStrs);
		}

		return iMCnt;
		
	}
	CATCH (CMemoryException, mce)
	{            
		DEX_Error (RC_ReadCodesdBaseExt, EC_NOMEMORY);
	}
	END_CATCH

	return 0;       
}

// dBase-Expression expandieren
pchar COdbcExtension::_ExpandDBaseExpression (long ONr, pchar pExpr) 
{
//  prüfe Parameter
    if (!pExpr || !*pExpr)
		return NULL;

//  Variablen init.
pchar pAct = pExpr;         // akt. Zeichen
pchar pBegin = pExpr;       // Beginn des öffnenden Separators
pchar pResult = NULL;       // Zeiger auf Ergebnis
pchar pTemp = NULL;         // Puffer-Zeiger
char Merkmal [_MAX_PATH] = "";  // akt. Merkmalswert
short ActLen = 0;           // Textlängen
short OldLen = 0;
    
	TRY {    
	//  Expression expandieren
    	for (;;) {
    	//  Beginn des 1. weiteren Parameters suchen
			pBegin = pAct;
			while (*pBegin && (*pBegin != BeginExpr))
				pBegin++;
			if (!*pBegin)           // Textende erreicht
				break;

    	//  kopiere alle Zeichen bis zum Parameterbeginn
			ActLen = pBegin - pAct;
			pTemp = new char [(pResult ? lstrlen (pResult) : 0) + ActLen + sizeof (Merkmal) + 1];
			*pTemp = '\0';
			if (pResult)
				lstrcpy (pTemp, pResult);       		// alten Text kopieren
			DELETE_VEC (pResult);                       	// und löschen
			pResult = pTemp;
			OldLen = pResult ? lstrlen (pResult) : 0;   // alte Länge merken
			memcpy (pResult + OldLen, pAct, ActLen);    // neuen Text ans akt. Ende kop.
			*(pResult + OldLen + ActLen) = '\0';        // Textende setzen

    	//  lese und speichere Merkmalswert

// KK000414
		// MerkmalsName gegeben
		long lIdent = DEX_GetObjIdent(ONr);
		ulong MKode = 0;
		char *cptr = strchr (pBegin,  EndExpr);

			if (cptr)
				*cptr = '\0';

			if (FAILED(GetFeatureHandle (lIdent,++pBegin, (INT_PTR *)& MKode)))
				MKode = strtoul (pBegin, NULL, g_sMkBase);

			if ( cptr)
				*cptr = EndExpr;

			if (MKode == 0) {		// scalare Funktion kann folgen { fn substring (...
			char *pT = pResult + lstrlen (pResult);
				
				*pT++ = BeginExpr;				
				while (*pBegin && (*pBegin != BeginExpr) && (*pBegin != EndExpr))
					*pT++ = *pBegin++;
				
				if (!*pBegin) {
					DEX_Error (RC_ExpdBaseExpr, EC_SYNTAX);
					DELETE_VEC (pResult);
					return NULL;					
				}					
				else {                                       
					if (*pBegin == EndExpr)
						*pT++ = *pBegin++;				// Separator speichern
					*pT = '\0';
				}
				pAct = pBegin;
				continue;									// und weiter
			}
				
			if (GetMerkmalsValue (ONr, MKode, Merkmal, sizeof (Merkmal)))
				lstrcat (pResult, Merkmal);

    	//  akt. Zeiger neu setzen
			while (*pAct && (*pAct != EndExpr))
				pAct++;
			
			if (*pAct)              // wenn noch kein Textende erreicht,
				pAct++;             // auf 1. Zeichen nach Separator
			else {                 	// Syntax-Fehler
				DEX_Error (RC_ExpdBaseExpr, EC_SYNTAX);
				DELETE_VEC (pResult);
				return NULL;
			}
    	}   //  end_for

	//  ggf. letzten Zeichen kopieren
    	ActLen = pBegin - pAct;
    	if (ActLen > 0) 
    	{
			pTemp = new char [(pResult ? lstrlen (pResult) : 0) + ActLen + 1];
			*pTemp = '\0';
			if (pResult) 
				lstrcpy (pTemp, pResult);                       // alten Text kopieren
			DELETE_VEC (pResult);                                       // und löschen
			pResult = pTemp;
			OldLen = pResult ? lstrlen (pResult) : 0;

		// KK000417 - fehlerhafte Länge der Query
			lstrcat ( pResult,pAct);

//			memcpy (pResult + OldLen, pAct, ActLen);        // Rest kopieren
//			*(pResult + OldLen + ActLen) = '\0';    // Ende-Kennung setzen
    	}

    	return pResult;
    
	}
	CATCH (CMemoryException, mce)
	{                                                                   
		DELETE_VEC (pResult);
		DEX_Error  (RC_ExpandExprdBaseExt, EC_NOMEMORY);                
	}    
	END_CATCH

	return NULL;
}

///////////////////////////////////////////////////////////
// Einbau der Menüpunkte in das Extras-Menü
//
BOOL COdbcExtension::InstallMainMenu()
{
// erst Separator einfügen
//	InstallMenuItem((UINT)-1, 0, IMINormalMenu, EXTRA_MENU_POS);

// PopupMenu einbauen
	if (NULL == m_pPopupMenu) {
		ATLTRY(m_pPopupMenu = new CMenu());
		if (NULL == m_pPopupMenu || !m_pPopupMenu -> LoadMenu (IDM_ODBC))
			return FALSE;
	}

INSTALLMENUITEMEX imi;

	INITSTRUCT(imi, INSTALLMENUITEMEX);
	imi.hDex = hDex();
	imi.iMenuID = -1;
	imi.iFlag = IMINormalMenu;
	imi.iMenuNum = EXTRA_MENU_POS;
	imi.iMenuPos = -1;

// PopUpMenu und MenuText holen
char cbBuffer[64];

	imi.hMenu = GetSubMenu (m_pPopupMenu -> m_hMenu, 0);
	ASSERT(NULL != imi.hMenu);
	GetMenuString (m_pPopupMenu -> m_hMenu, 0, cbBuffer, sizeof(cbBuffer), MF_BYPOSITION);

//  JG cut'n paste error
//	if (!(DEX_QueryMode() & QMSysAdmin)) {
//	int iCnt = GetMenuItemCount (imi.hMenu);

//		RemoveMenu (imi.hMenu, iCnt-2, MF_BYPOSITION);		// Separator entfernen
//		RemoveMenu (imi.hMenu, iCnt-2, MF_BYPOSITION);		// "FilterScript" entfernen
//	}

	imi.pMenuText = cbBuffer;
	return (NULL != DEX_InstallMenuItem (imi)) ? TRUE : FALSE;
}

void COdbcExtension::RemoveMainMenu()
{
REMOVEMENUITEMEX rmi;

	INITSTRUCT(rmi, REMOVEMENUITEMEX);
	rmi.hDex = hDex();
	rmi.iMenuID = -1;
	rmi.iMenuNum = EXTRA_MENU_POS;
	rmi.iFlag = IMINormalMenu;
	rmi.iMenuPos = -1;
	DEX_RemoveMenuItem (rmi);

//	RemoveMenuItem ((UINT)-1, IMINormalMenu, EXTRA_MENU_POS);
}

CErrMessageHandler* COdbcExtension::SetErrMessageHandler(CErrMessageHandler* pShower)
{
	CErrMessageHandler* tmp = m_pErrMsgHdl;
	m_pErrMsgHdl = pShower;
	return tmp;
}

// CErrMessageHandler
void CErrMessageHandler::Show(CString& strMsg)
{
CString Caption;

	VERIFY(Caption.LoadString (IDS_ODBCERROR));
	:: MessageBox (g_pCOdbcExtension -> hWnd (), strMsg, Caption, MB_OK | MB_ICONSTOP);
}

// CErrMessageBlocker
CErrMessageBlocker::CErrMessageBlocker()
{
	pOldHandler = g_pCOdbcExtension->SetErrMessageHandler(NULL);
}

CErrMessageBlocker::~CErrMessageBlocker()
{
	g_pCOdbcExtension->SetErrMessageHandler(pOldHandler);
}

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
BOOL FillMapWithClasses (HPROJECT hPr, CObjClassMap_t &rMap, CString &rstrClasses)
{
char *pEnd = NULL;
char *pBeg = (char *)(const char *)rstrClasses; 
char Buffer20 [20] = "";
ULONG ulVal = 0;

	while (pBeg && *pBeg) {
		ulVal = strtoul (pBeg, &pEnd, 10);
		if (ulVal != 0) {
			ultoa (ulVal, Buffer20, 10);
			if (FAILED(IdentFromClassX(hPr, Buffer20, &ulVal, FALSE)))	// JG hier das Project mitgeben
				continue;
		} else 
			pEnd = strchr (pBeg, ',');	// nächstes Trennzeichen suchen

	// Standard: fügt Ident==0 zur Map hinzu
#if defined(_DEBUG)
		if (0 == ulVal) {
		// Standard bzw. Ident==0 darf nur einmal vorkommen
		CObjClassMap_t_tit map_it = rMap.find (0);

			ASSERT(map_it == rMap.end());
		}
#endif // _DEBUG
		rMap.insert (ulVal);

		if (pEnd && *pEnd)
			pBeg = ++pEnd;
		else
			break;
	}
	return rMap.empty() ? FALSE : TRUE;
}

