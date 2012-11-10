// ImportInterface-Implementation für den Import von ODBC-Daten -----------
// File: ODBCIMP.CPP

#include "pheader.h"
#include "odbcext.hr"				// Ressourcen

#include <xtsnpropatl.h>			// CObjectProperties
#include <helptext.hpp>				// CHelpText
#include "database.hpp"				// CDataBaseExt
#include <waitcur.hpp>				// CWaitCursor
#include <getodbci.hpp>				// COdbcInfos
#include <actwind.hpp>				// CActivateWindow
#include <odbcerr.hpp>				// OdbcError
#include <hpp/collist.hpp>				// CColumnObjArray
#include "recset.hpp"				// CRecSet
#include <columnst.hpp>				// CColumns

#ifdef WIN32
#include <initguid.h>
#include <istatus.h>
#include <statguid.h>
#endif

#include "tools.hpp"				// OutputPunkt ()
#include "importpa.hpp"				// CImportParams
#include "triaspge.hpp"				// CTriasPage
#include "abglpge.hpp"				// CAbgleichPage
#include "dsnpage.hpp"				// CDsnPage
#include "feldpage.hpp"				// CFeldPage
#include "filtrpge.hpp"				// CFilterPage
#include "importsh.hpp"				// CImportSheet
#include "odbcimp.hpp"				// zugeh. Header
#include "odbcext.hpp"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// 	Konstanten
const short sImpFieldCnt = 3;						// Anzahl der für den Import benötigten Felder

// globale Variablen
CImportParams *g_pCParams = NULL;	

// externe Variablen
extern COdbcExtension *g_pCOdbcExtension;
                
// Konstruktor/Destruktor -----------------------------------------------------
CImportOdbcData :: CImportOdbcData (void)
{
	m_pCImportParams = NULL;
	m_pCConfigDialog = NULL;
}

CImportOdbcData :: ~CImportOdbcData (void)
{
	DELETE_OBJ (m_pCImportParams);
	DELETE_OBJ (m_pCConfigDialog);
}

BOOL  CImportOdbcData :: Configure (void)
{
//	zuerst alten Objekte löschen
	DELETE_OBJ (m_pCImportParams);
	DELETE_OBJ (m_pCConfigDialog);
	TRY
	{
		m_pCImportParams = new CImportParams;
		g_pCParams = m_pCImportParams;		// Zeiger speichern		
		m_pCConfigDialog = new CImportSheet (IDS_IMP_CAPTION/*, g_pCOdbcExtension -> MWind ()*/);
	} 
	CATCH (CMemoryException, me)
	{
		return FALSE;
	}
	END_CATCH

	if (m_pCConfigDialog -> m_bResult)
		m_pCConfigDialog -> DoModal ();
		// m_pCConfigDialog -> Create (g_pCOdbcExtension -> MWind ());

	BOOL bRet =  m_pCImportParams -> InfoComplete ();
	if (!bRet)
		m_pCImportParams -> CleanUp ();		

	return bRet;
}

//	kann Importiert werden ?
BOOL CImportOdbcData :: CanImport (void)
{
	if (m_pCImportParams != NULL && m_pCImportParams -> InfoComplete ())
		return TRUE;
	else
		return FALSE;
}

//	Daten importieren
void CImportOdbcData :: ImportData (void)
{               
//	prüfe externe Parameter
	ASSERT (g_pCOdbcExtension != NULL);

//	prüfe Import-Parameter
	if (!CanImport ())
	{								
		DEX_Error (RC_OdbcImport, EC_ILLPARS);
		return;
	}

//	Voreinstellungen machen
	CActivateWindow aw (g_pCOdbcExtension -> hWnd ());		//	Parent-Fenster deakt.

//	ODBC-Infos
	CDataBaseExt *pCDataBase = NULL;		// DataSource-Objekt
	CColumnObjArray *pCColList = NULL;		// Container mit Spalten-Infos
	CRecSet *pCRecSet = NULL;				// Record-Container 

	#ifdef WIN32
	IProgressIndicator *pIStatus = NULL;
	TRY
	{
	//	Status-Fenster erzeugen
		HRESULT hr = g_pCOdbcExtension -> m_pXtnSite -> CreateInstance (NULL, CLSID_ProgressIndicator,
                                            	    		IID_IProgressIndicator, (LPVOID*)&pIStatus);
		if (FAILED (hr)) 
			AfxThrowUserException ();
		HWND hNewWnd = pIStatus -> InitNew (g_pCOdbcExtension -> hWnd (), 0L);
    	if (NULL == hNewWnd) 
			AfxThrowUserException ();						

		hr = pIStatus -> Restart (0L, 1L, PIFLAG_CAPTION | PIFLAG_FILENAME | PIFLAG_FILE | PIFLAG_STATUS);

	//	1. Tabellen-Objekte Recherche durchführen
		CString strInfo;
		strInfo.LoadString (IDS_IMP_SEL_REC);			
		pIStatus -> ChangeText (PIFLAG_CAPTION, strInfo);			

	//	Tabellen-Namen
		strInfo.LoadString (IDS_IMP_TABLE);		
		pIStatus -> ChangeText (PIFLAG_FILE, strInfo);
		pIStatus -> ChangeText (PIFLAG_FILENAME, m_pCImportParams -> m_strTableName);

	//	Anzeige akt. 
		pIStatus -> SetPosition (1);					

	//	DataSource-Objekt erzeugen
		pCDataBase = new CDataBaseExt (m_pCImportParams -> m_strDataSource);
		if (! pCDataBase -> Open ())
		{
			DEX_Error (RC_OdbcImport, EC_NOOPENDSN);
			AfxThrowNotSupportedException ();
		}		
		
	//	DatenSätze aus Tabelle lesen
		long lMaxCnt = 0;				// Anzahl der Sätze oder Trias-Objekte
		if (!GetTableRecords (pCDataBase, pCColList, pCRecSet, lMaxCnt) || pIStatus -> WasCanceled ())
			AfxThrowNotSupportedException ();		// bereits ausgewerteter Fehler oder Nutzer-Abbruch

	// hr = pIStatus -> Restart (0L, 20, PIFLAG_CAPTION | PIFLAG_STATUS | PIFLAG_FILENAME | PIFLAG_RESULT | 
	//								      PIFLAG_TIME | PIFLAG_ADJUSTPERCENT | PIFLAG_FILE);
	// 	strInfo.LoadString (IDS_IMP_STAT_PERCENT);					// Prozent-Anzeige
	// 	pIStatus -> ChangeText (PIFLAG_ADJUSTPERCENT, strInfo);	

	//	lese Trias-Objekte

	//	führe Abgleich durch

	//	lösche ggf. nicht existierende Objekte/Datensätze

	//	schreibe ODBC-Anbindungen

	//	zeige ImportErgebnis

	//	Definition-Page
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);
	}
	AND_CATCH (CDBException, dbe)   
	{
		OdbcError oe (dbe);
		oe.Show (RC_OdbcImport);                 
	}
	AND_CATCH (CUserException, ue)
	{
		DEX_Error (RC_OdbcImport, EC_SYSERROR);
	}
	AND_CATCH (CFileException, fe)
	{
		// DEX_Error (RC_OdbcImport, EC_SYSERROR);
		fe -> ReportError ();
	}
	AND_CATCH (CNotSupportedException, ne)
	{
		// hier Nutzer-Abbruch !
	}
	END_CATCH

	if (pIStatus)
   		pIStatus -> Release();  
#endif

//	Speicher freigeben	
	DELETE_OBJ (pCColList);
	DELETE_OBJ (pCRecSet);
	DELETE_OBJ (pCDataBase);

/*
		// Satz ausgeben
		long lObjNr = OutputPunkt (4519380, 5730100, m_pCImportParams -> m_pulObjektKlassen [0]);
		if (lObjNr > 0)
		{
			if (OutputMerkmal (lObjNr, 	m_pCImportParams -> m_ulObjektMKode, "Satz1") == EC_OKAY)
		}
*/
}

//	lese alle Tabellensätze
BOOL CImportOdbcData :: GetTableRecords (CDataBaseExt *pCDataBase, CColumnObjArray *&pCColArr, 
										 CRecSet *&pCRecSet, long &lMaxCnt)
{
//	prüfe Parameter
	ASSERT (CanImport ());
	ASSERT (pCDataBase != NULL || pCDataBase -> IsOpen ());

	TRY
	{
	//	Recordset zusammenbauen: zuerst SpaltenInfos lesen
		CColumns CCol ((CDatabase *) pCDataBase);
		CCol.m_strTableNameParam = m_pCImportParams -> m_strTableName;

	//	SpaltenInfos öffnen
		if (!CCol.Open ())
		{
			DEX_Error (RC_OdbcImport, EC_NOOPENDSN);	// Fehlermeldung ausgeben
			AfxThrowNotSupportedException ();			// und raus
		}

	//	Info aller Felder
		pCColArr = new CColumnObjArray (sImpFieldCnt);	
		
	//	SpaltenInfos laden	
		const char *pvImpFields [sImpFieldCnt];		// Feldvektor
		pvImpFields [0] =  m_pCImportParams -> m_strKoppelFeld;
		pvImpFields [1] =  m_pCImportParams -> m_strRechtsWert;
		pvImpFields [2] =  m_pCImportParams -> m_strHochWert;

		if (!pCColArr -> FillColumnList (CCol, sImpFieldCnt, pvImpFields))
			AfxThrowNotSupportedException ();			// Fehler wurde bereits ausgegeben			
		CCol.Close ();									// keinen 2. Cursor zulassen

	//	SQL-Select-Anweisung erzeugen
		CString strFormat, strSel;
		strFormat.LoadString (IDS_IMP_SELECT);			// "select %s,%s,%s from %s"
		char *pSel = strSel.GetBuffer (strFormat.GetLength () + m_pCImportParams -> m_strKoppelFeld.GetLength () +
									   m_pCImportParams -> m_strRechtsWert.GetLength () +
									   m_pCImportParams -> m_strHochWert.GetLength () +
									   m_pCImportParams -> m_strTableName.GetLength () + 10);

		wsprintf (pSel, strFormat, (const char *) m_pCImportParams -> m_strKoppelFeld, 
								   (const char *) m_pCImportParams -> m_strRechtsWert,
								   (const char *) m_pCImportParams -> m_strHochWert, 
								   (const char *) m_pCImportParams -> m_strTableName);									   

		pCRecSet = new CRecSet (*(CDatabase *) pCDataBase, *pCColArr, m_pCImportParams -> m_strFilter); 
		if (!pCRecSet -> Open (CRecordset :: snapshot, pSel))
		{
			DEX_Error (RC_OdbcImport, EC_NOOPENDSN);	// Fehlermeldung ausgeben
			AfxThrowNotSupportedException ();			// und raus				
		}

	//	sind Sätze im Set vorhanden ?
		if (pCRecSet -> IsBOF () || 
			(m_pCImportParams -> m_bAction && 					// wenn TRiAS angepaßt wird				
		    ((lMaxCnt = pCRecSet -> GetRecordCount ()) == -1)))	// müssen setze gezählt werden
		{                                                    
			DEX_Error (RC_OdbcImport, WC_NOTFOUND);              
			AfxThrowNotSupportedException ();			// und raus				
		}

		return TRUE;
	}
	CATCH_ALL (e)
	{
		THROW_LAST ();
	}
	END_CATCH_ALL

	return FALSE;
}


