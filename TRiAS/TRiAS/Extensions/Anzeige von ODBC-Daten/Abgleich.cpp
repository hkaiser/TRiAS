// Abgleich.cpp : implementation file
//

#include "pheader.h"
#include "odbcext.hr"


#include <hpp/waitcur.hpp>				// CWaitCursor
#include <hpp/helptext.hpp>				// CHelpText
#include <hpp/getodbci.hpp>				// COdbcInfos
#include "database.hpp"				// CDataBaseExt
#include <hpp/odbcerr.hpp>				// COdbcError
#include <hpp/collist.hpp>				// CColumnObjArray
#include "recset.hpp"				// CRecSet
#include <hpp/columnst.hpp>				// CColumns
#include "profile.hpp"				// DBaseProfile

#include "importpa.hpp"				// CImportParams
#include "tools.hpp"				// OutputGeometrie

#ifndef WIN32
#include <progress.hpp>				// CProgressCtrl
#endif                                               

#include "pktinfo.hpp"				// CPunktInfoTree

#include "Abgleich.hpp"				// zugeh. Header

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	Konstanten
const short MaxFileNameLength = 8;			// max. 8 Zeichen für DOS
const short sImpFieldCnt = 3;				// Anzahl der für den Import benötigten Felder
const short MaxValSize = 30;				// max. Zahlenpuffergröße
const char KoordFormat [] = "%.5f";			// für Tabellenwerte

#ifdef WIN32
// const char TimeFormat [] = "%d.%m.%Y um %H:%M:%S Uhr";
#else 
// const char TimeFormat [] = "%02d.%02d.%d um %02d:%02d:%02d Uhr";
const short TimeSize = 80;					// ZeitPuffer-Größe
#endif

//	globale Variablen 
CStdioFile *g_pFile = NULL;					// Fehler-Protokoll-Datei
CPunktInfoTree *g_pCPunktInfoTree = NULL;	// Punktobjektebaum

#ifndef WIN32
	char ErrFileName [_MAX_PATH] = "";		// Name der Protokolldatei
#endif

//	lokale Variablen
static CDoAbgleich *pAbgleichPage = NULL;	// Zeiger diser Page

//	externe Variablen
extern CImportParams *g_pCParams;
extern int g_sMkBase;						// und Merkmale
#ifndef WIN32
extern CPropertySheetExt *g_pSheet;
#endif

//	externe Funktionen
void CallMessageQueue (void);				// verarbeiten anh. Nachrichten
char *DtoA (double Wert, char *String, const char *Format = NULL); 

IMPLEMENT_DYNAMIC(CNoValuesFoundException, CException)
static CNoValuesFoundException _simpleNoValuesFoundException;

//	globale Funktionen
void AFXAPI AfxNoValuesFoundException (void)
{
	THROW ((CNoValuesFoundException *)&_simpleNoValuesFoundException);
}

	// Teste auf Nutzer-Abbruch	
void __export WasInterrupted (void)
{
	CallMessageQueue ();					// anhängige Messages abarbeiten
	if (pAbgleichPage && pAbgleichPage -> m_bBreak)
		AfxNoValuesFoundException ();
}

/////////////////////////////////////////////////////////////////////////////
// CDoAbgleich property page

IMPLEMENT_DYNCREATE(CDoAbgleich, CPropertyPage)

CDoAbgleich::CDoAbgleich() : CPropertyPage(CDoAbgleich::IDD)
{
	//{{AFX_DATA_INIT(CDoAbgleich)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bBreak = FALSE;
	pAbgleichPage = this;
	m_tDsnType = UserDataSource;
}

CDoAbgleich::~CDoAbgleich()
{
	pAbgleichPage = NULL;
}

void CDoAbgleich::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoAbgleich)
	DDX_Control(pDX, IDC_IMP_PROGRESS, m_ctProgress);
	DDX_Control(pDX, IDT_IMP_ABGLEICH_INFO, m_stInfo);
	//}}AFX_DATA_MAP
}

#ifdef WIN32
BEGIN_MESSAGE_MAP(CDoAbgleich, CPropertyPage)
	//{{AFX_MSG_MAP(CDoAbgleich)
	ON_MESSAGE (IDM_DOABGLEICH, OnDoAbgleich)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#else 
BEGIN_MESSAGE_MAP(CDoAbgleich, CPropertyPage)
	//{{AFX_MSG_MAP(CDoAbgleich)
	ON_MESSAGE (IDM_DOABGLEICH, OnDoAbgleich)
	ON_MESSAGE(IDM_SETFOCUS, OnSetFocusToControl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoAbgleich message handlers
void CDoAbgleich::OnCancel() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_bBreak = TRUE;
	
	CPropertyPage::OnCancel();
}
                  
#ifdef WIN32                  
BOOL CDoAbgleich::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	GetParent () -> SetWizardButtons (0);			// keine Buttons aktiv
	PostMessage (IDM_DOABGLEICH, 0, 0);
	return CPropertyPage::OnSetActive();
}           
#endif

//	Protokoll-Datei erzeugen: Kopf ausgeben
void CDoAbgleich::CreateProtokoll (void)
{
	CString strPath, strDrive, strDir, strFileName, strExt;
	char *pPath = strPath.GetBuffer (_MAX_PATH);
	char *pDrive = strDrive.GetBuffer (_MAX_DRIVE);
	char *pDir = strDir.GetBuffer (_MAX_DIR);
	// char *pFileName = strFileName.GetBuffer (_MAX_FNAME);
	if (!DEX_GetActiveProject (pPath))
		AfxThrowUserException ();

//	Filename zusammenbauen	
	_splitpath (pPath, pDrive, pDir, NULL, NULL);
	if (!strExt.LoadString (IDS_ERR_EXTENSION))
		AfxThrowResourceException ();

	// strcpy (pFileName, g_pCParams -> m_strDefinition);	// läuft unter Umständen nicht
	VERIFY (strFileName.LoadString (IDS_ERR_FILENAME));
	
	//if (strlen (pFileName) > MaxFileNameLength)
	//	pFileName [MaxFileNameLength] = '\0';
	_makepath (pPath, pDrive, pDir, strFileName/*pFileName*/, strExt);

	UINT uiMode = CFile::modeCreate | CFile::modeWrite | CFile::typeText;
	g_pFile = new CStdioFile (pPath, uiMode);
#ifndef WIN32
	strcpy (ErrFileName, pPath);
#endif	

//	Standard-Werte ausgeben: Datum, Uhrzeit, Definition
	CTime Time = CTime::GetCurrentTime();
#ifdef WIN32	
	CString strTime = Time.Format (IDS_DATE_TIME_FORMAT);
#else            
	char Buffer [TimeSize] = "";          
	CString strFormat;
	VERIFY (strFormat.LoadString (IDS_DATE_TIME_FORMAT));
	wsprintf (Buffer, strFormat, Time.GetDay(), Time.GetMonth(), Time.GetYear(),
								 Time.GetHour(), Time.GetMinute(),Time.GetSecond());
#endif	
	CString strHelp;
	AfxFormatString2 (strHelp, IDS_IMP_PROT_HEAD, g_pCParams -> m_strDefinition,
#ifdef WIN32	
							   strTime);	 
#else
							   Buffer);
#endif							   							   
	g_pFile -> WriteString (strHelp);		

//	Separator ausgeben
	g_pFile -> WriteString ("\n");
}

//	ermittle Tabellensätze
BOOL CDoAbgleich :: GetTableRecords (CDataBaseExt *pCDataBase, CColumnObjArray *&pCColArr, 
								     CRecSet *&pCRecSet, long &lMaxCnt, BOOL bForUpdate)
{
//	prüfe Parameter
	ASSERT (g_pCParams -> InfoComplete ());
	ASSERT (pCDataBase != NULL || pCDataBase -> IsOpen ());

	TRY
	{
	//	Zähler rücksetzen
		lMaxCnt = 0;

	//	Recordset zusammenbauen: zuerst SpaltenInfos lesen
		CColumns CCol ((CDatabase *) pCDataBase);
		CCol.m_strTableNameParam = g_pCParams -> m_strTableName;

	//	SpaltenInfos öffnen
		if (!CCol.Open ())
		{
			DEX_Error (RC_OdbcImport, EC_NOOPENDSN);	// Fehlermeldung ausgeben
			return FALSE;
		}

	//	Info aller Felder
		pCColArr = new CColumnObjArray;	
		
		if (!pCColArr -> FillColumnList (CCol))
			return FALSE;
		CCol.Close ();									// keinen 2. Cursor zulassen

	//	Indizes speichern
		g_pCParams -> m_sKoppelIndex = pCColArr -> GetIndex (g_pCParams -> m_strKoppelFeld);
		g_pCParams -> m_sRechtsWertIndex = pCColArr -> GetIndex (g_pCParams -> m_strRechtsWert);
		g_pCParams -> m_sHochWertIndex = pCColArr -> GetIndex (g_pCParams -> m_strHochWert);

	//	Fehlermeldung bereits ausgegeben
		if (g_pCParams -> m_sKoppelIndex == -1 ||
			g_pCParams -> m_sRechtsWertIndex == -1 ||
			g_pCParams -> m_sHochWertIndex == -1)
			return FALSE;

	//	SQL-Select-Anweisung erzeugen: "select * from %s"
		CString strSel;
		AfxFormatString1 (strSel, IDS_SQLSELECT, g_pCParams -> m_strTableName);

		// DWORD dwOptions = bForUpdate ? CRecordset::none : CRecordset::readOnly;
                                 
#ifdef WIN32                                  
		UINT nOpenType = AFX_DB_USE_DEFAULT_TYPE;                                    
#else		
		UINT nOpenType = CRecordset::snapshot;                                    
#endif		
		pCRecSet = new CRecSet (*(CDatabase *) pCDataBase
								, *pCColArr
								, g_pCParams -> m_strFilter
#ifdef __UseOGX__
								, strSel
#endif //__UseOGX__
								); 
		
		if (!pCRecSet -> Open (nOpenType, strSel/*, dwOptions*/))
		{
			DEX_Error (RC_OdbcImport, EC_NOOPENDSN);	// Fehlermeldung ausgeben
			return FALSE;
		}

	//	sind Sätze im Set vorhanden ?
		if (!pCRecSet -> IsBOF ())
			lMaxCnt = pCRecSet -> GetRecordCount () + 1; 

	}	// TRY
	CATCH (CDBException, dbe)   
	{
		OdbcError oe (dbe);
		oe.Show (RC_OdbcImport);                 
		AfxThrowNotSupportedException ();		// Fehler bereits ausgegeben
	}
	AND_CATCH_ALL (e)
	{
		THROW_LAST ();
	}
	END_CATCH_ALL

	return TRUE;
}

//	schreibe ODBC-Anbindungen
BOOL CDoAbgleich :: OutputConnections (void)
{
//	prüfe Parameter
	ASSERT (g_pCParams -> InfoComplete ());

//	ODBC-Anbindungen schreiben
	Profile ProFile;			

//	für alle IDs 
	for (ulong *pIds = g_pCParams -> m_pulObjektKlassen; pIds && *pIds; pIds++)
	{
		if (!ProFile.WriteOdbcEntry (*pIds, g_pCParams -> m_strTableName,
									 g_pCParams -> m_strKoppelFeld, 
									 g_pCParams -> m_ulObjektMKode))
			return FALSE;
	}		

//	Table/DataSource-Name ausgeben
	if (ProFile.WriteTableName (g_pCParams -> m_strTableName,
								g_pCParams -> m_strTableName) &&
		ProFile.WriteDataSourceName (g_pCParams -> m_strTableName,
								     g_pCParams -> m_strDataSource, m_tDsnType))
		return TRUE;

	return FALSE;
}

//	Abgleich ausführen
LONG CDoAbgleich::OnDoAbgleich (UINT, LONG)
{   
	UpdateWindow ();
	CallMessageQueue ();

//	prüfe Parameter
	ASSERT (g_pCParams != NULL);	// prüfe Parameter

//	Daten init.
	BOOL bRet = FALSE;				// noch nichts getan
	g_pCParams -> m_COdbcInfos.DeleteAllNotDataSource ();		// alten ODBC-Infos löschen: außer DataSource
	CDataBaseExt *pCDataBase = NULL;		// DataSource-Objekt
	CColumnObjArray *pCColList = NULL;		// Container mit Spalten-Infos
	CRecSet *pCRecSet = NULL;				// Record-Container 
	CPunktInfoTree *pCPunktInfoTree = NULL;	// Tree mit TRiAS-Objekten

	TRY
	{
	//	erzeuge Protokoll-Datei
		CreateProtokoll ();

		WasInterrupted ();		// Nutzerabbruch ?

	//	Datensätze der Tabelle ermitteln: akt. Statusanzeige
		CString strInfo;
		m_ctProgress.SetRange (0, 1);
		m_ctProgress.SetPos (0);
		AfxFormatString1 (strInfo, IDS_IMP_SEL_REC, g_pCParams -> m_strTableName);
		m_stInfo.SetWindowText (strInfo);

	//	DataSource-Objekt ggf. erzeugen
		if (g_pCParams -> m_COdbcInfos.m_pDataBase)
		{
			pCDataBase = g_pCParams -> m_COdbcInfos.m_pDataBase;
			g_pCParams -> m_COdbcInfos.m_pDataBase = NULL;
		}
		else
			pCDataBase = new CDataBaseExt (g_pCParams -> m_strDataSource, m_tDsnType);
		if (! pCDataBase -> Open ())
		{
			DEX_Error (RC_OdbcImport, EC_NOOPENDSN);
			AfxThrowUserException ();
		}		

		WasInterrupted ();		// Nutzerabbruch ?

	//	DatenSätze aus Tabelle bestimmen
		long lMaxCnt = 0;				// Anzahl der Sätze
		if (!GetTableRecords (pCDataBase, pCColList, pCRecSet, lMaxCnt, 
			!g_pCParams -> m_bAction))
			AfxThrowNotSupportedException ();		// bereits ausgewerteter Fehler oder Nutzer-Abbruch

	//	Zähler auswerten
		if (lMaxCnt == 0) 							// wenn keine Sätze gefunden
		{
			if (g_pCParams -> m_bAction)			// TRIAS anpassen				
				AfxNoValuesFoundException ();		// kein Abgleich möglich	
			else									// Table anpassen
				if (g_pCParams -> m_bAddNotExist == FALSE)	// keine zus. Punkte imp.
					AfxNoValuesFoundException ();	// kein Abgleich möglich							
		}

		m_ctProgress.SetPos (1);	// 	Scrollbar akt.
		WasInterrupted ();			//	Nutzerabbruch ?

	//	lese Trias-Objekte: zuerst Anzeige akt.
		if (!strInfo.LoadString (IDS_IMP_SEL_OBJ))
			AfxThrowResourceException ();
		m_stInfo.SetWindowText (strInfo);
		m_ctProgress.SetPos (0);
										 
	//	Trias-Objekte ermitteln
		pCPunktInfoTree = new CPunktInfoTree (g_pCParams -> m_bAction ?
											  g_pCParams -> m_bDelNotExist : FALSE);
		g_pCPunktInfoTree = pCPunktInfoTree;
		if (! pCPunktInfoTree -> GetPunktInfos (g_pCParams -> m_pulObjektKlassen,
												g_pCParams -> m_ulObjektMKode))
			AfxThrowNotSupportedException ();	// bereits ausgewerteter Fehler

	//	Anzahl Punkte auswerten
		if (pCPunktInfoTree -> Count () == 0)
		{
			if (g_pCParams -> m_bAction == FALSE)			// Tabelle anpassen				
				AfxNoValuesFoundException ();				// kein Abgleich möglich	
			else											// TRIAS anpassen
				if (g_pCParams -> m_bAddNotExist == FALSE)	// keine zusätzl. Datens. imp.
					AfxNoValuesFoundException ();			// kein Abgleich möglich							
		}

		pCPunktInfoTree -> Optimize ();
		m_ctProgress.SetPos (1);	//	Fertig-Einstellung				

		WasInterrupted ();		// Nutzerabbruch ?

	//	Abgleichnachricht ausgeben
		if (!strInfo.LoadString (IDS_IMP_DOABGL))
			AfxThrowResourceException ();
		m_stInfo.SetWindowText (strInfo);

		m_ctProgress.SetRange (0, (int) lMaxCnt);
		m_ctProgress.SetPos (0);	//	Fertig-Einstellung				

	//	1. Zweig: TRiAS-Objekte abgleichen
		if (g_pCParams -> m_bAction)
		{
		//	TriasAgbleich durchführen
			if (!TriasAbgleich (lMaxCnt, pCPunktInfoTree, pCRecSet, pCColList, g_pCParams -> m_bAddNotExist))
				AfxThrowNotSupportedException ();	// bereits ausgewerteter Fehler
					
		//	lösche ggf. nicht existierende Objekte				
			if (g_pCParams -> m_bDelNotExist)
				pCPunktInfoTree -> DeleteNotRefObj (m_ctProgress, m_stInfo, 
													&WasInterrupted);
	
		//	Änderungen speichern
			IStorage *pISt = NULL;
			if (DEX_GetProjectStorage (pISt))
				pISt -> Release ();
			else
				DEX_FlushModifications();

		//	schreibe ODBC-Anbindungen
			if (!OutputConnections ())
				AfxThrowUserException ();	
		}	
		else	// Datensätze der Tabelle abgleichen		
		{
			if (! TableAbgleich (lMaxCnt, pCPunktInfoTree, pCRecSet, pCColList, 
								 g_pCParams -> m_bAddNotExist))
				AfxThrowNotSupportedException ();	// bereits ausgewerteter Fehler			
		}

		bRet = TRUE;
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
		//DEX_Error (RC_OdbcImport, EC_NOSPACE);
		fe -> ReportError ();
	}
	AND_CATCH (CNotSupportedException, ne)
	{
		//	Fehler bereits ausgegeben
	}
	AND_CATCH (CResourceException, re)
	{
		DEX_Error (RC_OdbcImport,  EC_NORESOURCE);
	}
	AND_CATCH (CNoValuesFoundException, nv)
	{
		bRet = TRUE;		// Ausgabe der Ergebnisse
	}
	END_CATCH

//	Speicher freigeben	
	DELETE_OBJ (pCColList);
	DELETE_OBJ (pCRecSet);
	DELETE_OBJ (pCDataBase);
	DELETE_OBJ (pCPunktInfoTree);
	g_pCPunktInfoTree = NULL;


//	Result-Flag Ok ?
	if (!bRet)
	{
		DELETE_OBJ (g_pFile);
		GetParent () -> EndDialog (IDCANCEL);
		return TRUE;
	}
	                
#ifdef WIN32	                
	GetParent () -> SetWizardButtons (PSWIZB_NEXT);
	GetParent () -> PressButton (PSBTN_NEXT);
#else 
	ASSERT (g_pSheet != NULL);
	g_pSheet -> SetWizardButtons (PSWIZB_NEXT);
	:: PostMessage (GetParent () -> m_hWnd, IDM_NEXT_PAGE, 0, 0);
#endif	
	:: MessageBeep (MB_OK);
	return TRUE;
}
        
//	Fehlermeldung ins Prorokoll ausgeben
void CDoAbgleich :: OutputError (uint uiResID, long lObjNr, long lX, long lY,
								 const char *pMerkmal)
{
//	prüfe Paremeter
	ASSERT (g_pFile != NULL);
	ASSERT (uiResID > 0 && lObjNr > 0);
	ASSERT (pMerkmal != NULL && AfxIsValidString (pMerkmal));

	CString strFormat, strBuffer;
	if (!strFormat.LoadString (uiResID))
		AfxThrowResourceException ();
	char *pBuffer = strBuffer.GetBuffer (strFormat.GetLength () + strlen (pMerkmal) +
										(3 * MaxValSize));
	wsprintf (pBuffer, (const char *) strFormat, lObjNr, pMerkmal, lX, lY);
	g_pFile -> WriteString (pBuffer);
}

//	Triasabgleich durchführen
BOOL CDoAbgleich :: TriasAbgleich (long lMax, CPunktInfoTree *pTree, CRecSet *pSet, 
								   CColumnObjArray *pCol, BOOL bAddNotExist)
{
	ASSERT (g_pCParams != NULL);
	return TriasTableAbgleich (lMax, pTree, pSet, pCol, bAddNotExist, g_pCParams -> m_bAction);
}

//	Tabellenabgleich durchführen
BOOL CDoAbgleich :: TableAbgleich (long lMax, CPunktInfoTree *pTree, CRecSet *pSet, 
								   CColumnObjArray *pCol, BOOL bAddNotExist)
{
//	prüfe Parameter
	ASSERT ((pTree != NULL) && (pSet != NULL) && (pCol != NULL));
	ASSERT (pSet -> m_pDatabase -> IsOpen ());
	ASSERT ((g_pCParams != NULL) && g_pCParams -> InfoComplete ());
	ASSERT (g_pFile != NULL);

	BOOL bRet = FALSE;				// noch nichts getan

	TRY
	{
	//	prüfe Transaktions-Fähigkeit
		if (pSet -> CanTransact ())
			pSet -> m_pDatabase -> BeginTrans ();

		if (!pSet -> CanUpdate ())
		{
			DEX_Error (RC_OdbcImport, EC_NOTABLEUPDATE);
			return FALSE;
		}

		pSet -> SetLockingMode (CRecordset::LockMode::optimistic);				// Locking-Modus setzen

	//	führe Abgleich ohne "append" neuer Sätze durch
		if (TriasTableAbgleich (lMax, pTree, pSet, pCol, FALSE, g_pCParams -> m_bAction))
		{
		//	ggf. Objekte ohne Referenz hinzufügen								
			if (bAddNotExist)
			{
			//	können Sätze angehangen werden ?
				if (!pSet -> CanAppend ())
				{
					DEX_Error (RC_OdbcImport, EC_NOTABLEAPPEND);
					return TRUE;
				}					

			//	NutzerInfo akt.
				CString strInfo;
				if (!strInfo.LoadString (IDS_IMP_ADD_NOT_EXIST))
					AfxThrowResourceException ();
				m_stInfo.SetWindowText (strInfo);

			//	Progress-Balken akt.
				m_ctProgress.SetRange (0, (int) pTree -> Count ());
				m_ctProgress.SetPos (0);
				ulong ulActCnt = 1;					// akt. Satz-Nummer

			//	Variablen init.
				short sRetKopp = OkSet;				// Return-Werte
				short sRetY = OkSet;
				short sRetX = OkSet;
				BOOL bOut = FALSE;					// Ausgabeflag
				CString strX, strY;					// Koordinaten
				char KoordBuffer [MaxValSize] = "";	// Zahlenpuffer

				CTable tb (*pTree);					// Punkt-Navigator
				for (tb.First (); tb.Valid (); tb.Next (), ulActCnt++)
				{
					WasInterrupted ();				// Nutzerabbruch ?
					m_ctProgress.SetPos ((int) ulActCnt);	// Scrollbalken akt.											

					CPunktInfoLock pL (tb);		
					if (! pL)						// interner Fehler
					{
						DEX_Error (RC_OdbcImport, EC_LOCKERROR);
						AfxThrowNotSupportedException ();
					}
					else
					{//	wenn Objekt nicht modifiziert wurde --> appenden
						if (pL -> m_sIsModified == NotModified)
						{
							pL -> m_sIsModified = IsModified;		// Flag setzen

							pSet -> AddNew ();						// neuen Satz dazu
						//	Koordinaten konvertieren und speichern
							strX = DtoA (pL -> m_dX, KoordBuffer, KoordFormat); 
							strY = DtoA (pL -> m_dY, KoordBuffer, KoordFormat); 
							bOut = FALSE;

							sRetKopp = OkSet;				// Return-Werte
							sRetY = OkSet;
							sRetX = OkSet;

							if ((sRetKopp = pCol -> SetFieldInfo (pL -> m_strMerkmal, g_pCParams -> m_sKoppelIndex)) && 
								(sRetY = pCol -> SetFieldInfo (strY, g_pCParams -> m_sHochWertIndex)) &&
								(sRetX = pCol -> SetFieldInfo (strX, g_pCParams -> m_sRechtsWertIndex)) &&
								 pSet -> Update ())		// Ergebnisse speichern
							{
								bOut = TRUE;			// keine Fehlermeldung gen.
								g_pCParams -> m_lNewCnt++;

							//	prüfe Längen-Info
								if ((sRetKopp == InfoTruncated) || 
									(sRetX == InfoTruncated) || (sRetY == InfoTruncated))
									OutputError (IDS_IMP_ERR_INFOTRUNC, ulActCnt, (long) pL -> m_dX, (long) pL -> m_dX, 
																				  pL -> m_strMerkmal);
							}
							else
								g_pCParams -> m_lErrImpCnt++;

						//	Fehlermeldung ggf. ausgeben
							if (!bOut)
								OutputError (IDS_IMP_ERR_ADDREC, ulActCnt, (long) pL -> m_dX, (long) pL -> m_dX, 
																	       pL -> m_strMerkmal);
						}
					}		// else
				}			// for
			}				// AddNotExist
		}					// TriasTableAbgleich

		if (pSet -> CanTransact ())
			bRet = pSet -> m_pDatabase -> CommitTrans ();	// alle Änderungen speichern
		else
			bRet = TRUE;
		pSet -> Close ();
	}
	CATCH (CDBException, dbe)   
	{
		OdbcError oe (dbe);
		oe.Show (RC_OdbcImport);                 
		RollBack (pSet);
		AfxThrowNotSupportedException ();		// Fehler bereits ausgegeben
	}
	AND_CATCH_ALL (e)
	{
		RollBack (pSet);
		THROW_LAST ();				
	}
	END_CATCH_ALL

	return bRet;
}

//	eigentlichen Abgleich durchführen
BOOL CDoAbgleich :: TriasTableAbgleich (long lMax, CPunktInfoTree *pTree, CRecSet *pSet, 
								        CColumnObjArray *pCol, BOOL bAddNotExist, BOOL bAction)
{
//	prüfe Parameter
	ASSERT ((pTree != NULL) && (pSet != NULL) && (pCol != NULL));
	ASSERT (pSet -> m_pDatabase -> IsOpen ());
	ASSERT ((g_pCParams != NULL) && g_pCParams -> InfoComplete ());
	ASSERT (g_pFile != NULL);

	BOOL bRet = FALSE;				// noch nichts getan

	TRY
	{
	//	Variablen init.
		CString strKoppel, strX, strY;
		long lObjNr = -1;						// akt. Obj.-Nr
		BOOL bOut = FALSE;						// Ausgabe-Flag
		double dX, dY;							// akt. Koord.
		dX = dY = 0.0;
		long lActCnt = 1;						// akt. Satznummer
		char KoordBuffer [MaxValSize] = "";		// Zahlenpuffer
		for (pSet -> MoveFirst (); !pSet -> IsEOF (); pSet -> MoveNext (), lActCnt++)
		{
			WasInterrupted ();				// Nutzerabbruch ?
			m_ctProgress.SetPos ((int) lActCnt);	// Scrollbalken akt.

		//	lese Inhalt des akt. Satz
			strKoppel.Empty ();
			strX.Empty ();
			strY.Empty ();
			if (!pCol -> GetFieldInfo (pSet, strKoppel, g_pCParams -> m_sKoppelIndex) ||
				 strKoppel.IsEmpty () ||
				!pCol -> GetFieldInfo (pSet, strY, g_pCParams -> m_sHochWertIndex) ||
				strY.IsEmpty () ||
				!pCol -> GetFieldInfo (pSet, strX, g_pCParams -> m_sRechtsWertIndex) ||
				strX.IsEmpty ())
			{
			//	Fehlermeldung ausgeben
				OutputError (IDS_IMP_UNV_RECINFO, lActCnt, 0, 0, 
							 strKoppel.IsEmpty () ? "" : strKoppel);
				continue;	// und zum nächsten Satz
			}

		//	Koordinaten erzeugen
			dX = atof (strX);
			dY = atof (strY);

		//	suche Satz im Trias-Baum
			CTable tb (*pTree);
			if (tb.Find ((void *)(const char *)strKoppel))
			{	
			//	Satz bereits vorhanden, ggf. Geometrie modifizieren 
				CPunktInfoLock pL (tb);		
				if (! pL)					// interner Fehler
				{
					DEX_Error (RC_OdbcImport, EC_LOCKERROR);
					AfxThrowNotSupportedException ();			// und raus
				}

			//	Geometrie nur ändern, wenn Objekt noch nicht modifiziert 
				if (pL -> m_sIsModified != NotModified)
				{
				//	hier nur Fehlermeldung ausgeben: dopp. vorh. Datensatz								
					OutputError (IDS_IMP_ERR_DOPPREC, lActCnt, (long) dX, (long) dY, strKoppel);
					g_pCParams -> m_lDoppTableCnt++;					// Zähler erhöhen
					continue;
				}

				pL -> m_sIsModified = IsModified;		// Flag immer setzen

			//	nur Modifikation, wenn Geoemtrie sich geändert hat
				if (pL -> m_dX != dX || pL -> m_dY != dY)
				{
				//	jetzt erst Geometrie modifizieren
					if (bAction)				// TRIAS mod.
					{
						pL -> m_dX = dX;		// Geometrie im Punkt-Baum speichern
						pL -> m_dY = dY;
						bOut = ModPunktGeometrie (pL -> m_lObjNr, dX, dY);
					}
					else
					{								//	Tabelle modif.
						pSet -> Edit ();			//	Editierung beginnen
						
					//	Koordinaten konvertieren und speichern
						strX = DtoA (pL -> m_dX, KoordBuffer, KoordFormat); 
						strY = DtoA (pL -> m_dY, KoordBuffer, KoordFormat); 
						bOut = FALSE;
						
						if (pCol -> SetFieldInfo (strY, g_pCParams -> m_sHochWertIndex) &&
							pCol -> SetFieldInfo (strX, g_pCParams -> m_sRechtsWertIndex) &&
						    pSet -> Update ())		// Ergebnisse speichern
						{
							bOut = TRUE;			// keine Fehlermeldung gen.
							g_pCParams -> m_lImpCnt++;
						}
						else
							g_pCParams -> m_lErrImpCnt++;
					}

				//	Fehlermeldung ggf. ausgeben
					if (!bOut)
						OutputError (IDS_IMP_ERR_ABGREC, lActCnt, (long) dX, (long) dY, strKoppel);
				}
			}			
			else	//	Satz nicht gefunden, ggf. neu importieren
			{
				if (bAddNotExist)
				{
					bOut = FALSE;				// Ausgabe-Flag rücksetzen

				//	Satz ausgeben: Geometrie akt. Zähler
					lObjNr = OutputPunkt (dX, dY, g_pCParams -> m_pulObjektKlassen [0]);
					if ((lObjNr > 0) &&
						(OutputMerkmal (lObjNr, g_pCParams -> m_ulObjektMKode, strKoppel) == EC_OKAY) &&
						pTree -> StoreRecordInfo (lObjNr, strKoppel, dX, dY, IsModified))
						bOut = TRUE;

				//	ggf. Fehlermeldung ins Protokoll
					if (!bOut)
						OutputError (IDS_IMP_ERR_IMP, lActCnt, (long) dX, (long) dY, strKoppel);
				}				
			}			// else
		}				// for
		bRet = TRUE;
	}					// TRY
	CATCH (CDBException, dbe)   
	{
		OdbcError oe (dbe);
		oe.Show (RC_OdbcImport);                 
		AfxThrowNotSupportedException ();		// Fehler bereits ausgegeben
	}
	AND_CATCH_ALL (e)
	{
		THROW_LAST ();
	}
	END_CATCH_ALL

	return bRet;
}

//	alle Änderungen in der Tabelle werden ungültig
void CDoAbgleich :: RollBack (CRecSet *pSet)
{
//	prüfe Parameter
	ASSERT (pSet != NULL && pSet -> IsOpen ());
	ASSERT (g_pCParams != NULL);

	if (pSet -> CanTransact ())
	{
		g_pCParams -> m_lImpCnt = 0;				// Zähler rücksetzen
		g_pCParams -> m_lDelCnt = 0;
		g_pCParams -> m_lNewCnt = 0;

		pSet -> m_pDatabase -> Rollback ();			// alle Änderungen werden ungültig		
	}
	pSet -> Close ();
}

#ifndef WIN32
BOOL CDoAbgleich::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	ASSERT (g_pSheet != NULL);
	g_pSheet -> SetWizardButtons (0);			// keine Buttons aktiv
	PostMessage (IDM_SETFOCUS, 0, 0L);
	PostMessage (IDM_DOABGLEICH, 0, 0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LONG CDoAbgleich :: OnSetFocusToControl (UINT, LONG)
{
	GotoDlgCtrl (&m_ctProgress);
	return TRUE;		
}            
#endif

