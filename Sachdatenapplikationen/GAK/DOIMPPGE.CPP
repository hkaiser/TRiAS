// DoImpPge.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp u. Ressourcen
#include "importty.h"	// CImportParams
#include "DoImpPge.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Konstanten
const char TableSep [] = "_";		// Tabellen-Begrenzer
const char ParamVal1 [] = "= '%s'";
const char ParamVal2 [] = "= '%s'";
const char AndOper [] = " AND ";
const char ExportFlag [] = "Exportiert";
const int  Importiert = 4;			//	bereits Importiert

/////////////////////////////////////////////////////////////////////////////
// CDoImportPage property page

IMPLEMENT_DYNCREATE(CDoImportPage, CPropertyPage)

CDoImportPage::CDoImportPage() : CPropertyPage(CDoImportPage::IDD)
{
	//{{AFX_DATA_INIT(CDoImportPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pParams = NULL;
	m_bBreak = FALSE;
}

CDoImportPage::~CDoImportPage()
{
}

void CDoImportPage::SetParams (CImportParams &Params)
{
	m_pParams = &Params;
}

void CDoImportPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoImportPage)
	DDX_Control(pDX, IDS_AKTION, m_stAction);
	DDX_Control(pDX, IDC_PROGRESS, m_ctProgress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoImportPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDoImportPage)
		// NOTE: the ClassWizard will add message map macros here
	ON_MESSAGE (IDM_DOABGLEICH, OnDoImport)
	ON_COMMAND(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoImportPage message handlers

BOOL CDoImportPage::OnSetActive() 
{
//	Protokolldatei Aufbauen
	ASSERT (NULL != m_pParams);
	ASSERT (m_pParams->m_SourceDatabase.IsOpen ());
	CString strPath, strDrive, strDir, strFileName, strExt;
	char *pPath = strPath.GetBuffer (_MAX_PATH);
	char *pDrive = strDrive.GetBuffer (_MAX_DRIVE);
	char *pDir = strDir.GetBuffer (_MAX_DIR);
	VERIFY (strExt.LoadString (IDS_ERR_EXT));
	_splitpath (m_pParams->m_DestDatabase.GetName(), pDrive, pDir, NULL, NULL);
	_makepath (pPath, pDrive, pDir, AfxGetAppName (), strExt);
	UINT uiMode = CFile::modeCreate | CFile::modeWrite | CFile::typeText;
	CFileException fe;
	m_pParams -> m_ReportFile.Open (pPath, uiMode, &fe);	// beenden bei Fehler	

//	Standard-Werte ausgeben: Datum, Uhrzeit, Definition
	ASSERT (!m_pParams -> m_strInputTableName.IsEmpty ());

//	Zeitstring bilden	
	COleDateTime OleDate (COleDateTime::GetCurrentTime());
	CString strDate (OleDate.Format ((UINT) IDS_DATETIME_FORMAT)), strHelp;
	
	AfxFormatString2 (strHelp, IDS_IMPORT_HEAD, m_pParams->m_strInputTableName, strDate);	 
	m_pParams -> m_ReportFile.WriteString (strHelp);		
	m_pParams -> m_ReportFile.WriteString ("\n");

	GetParent () -> SetWizardButtons (0);	
	PostMessage (IDM_DOABGLEICH, 0, 0);
	
	return CPropertyPage::OnSetActive();
}

void CDoImportPage::OnCancel() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_bBreak = TRUE;
	
	CPropertyPage::OnCancel();
}

	// Teste auf Nutzer-Abbruch	
void CDoImportPage::WasInterrupted (void)
{
	CallMessageQueue ();					// anhängige Messages abarbeiten
	if (m_bBreak)
		AfxThrowUserException ();
}

//	ermittle Anzahl der Datensätze im SourceSet
long CDoImportPage :: GetAnzahl (void)
{
	CWaitCursor wc;
	CString strInfo, strSQL, strFieldName;
	VERIFY (strInfo.LoadString (IDS_GET_RECORD_COUNT));
	m_stAction.SetWindowText (strInfo);

//	SourceSet ggf. schließen
	ASSERT (NULL != m_pParams);
	if (m_pParams -> m_SourceSet.IsOpen ())
		m_pParams -> m_SourceSet.Close ();
	ASSERT (!m_pParams -> m_strInputTableName.IsEmpty ());
	AfxFormatString1 (strSQL, IDS_SELECT_COUNT, m_pParams -> m_strInputTableName);
	m_pParams -> m_SourceSet.Open (dbOpenSnapshot, strSQL, dbForwardOnly);
	
//	lese Anzahl der Datensätze vom Feld 'Anzahl'
	CDaoFieldInfo Info;
	m_pParams -> m_SourceSet.GetFieldInfo (0, Info);
	COleVariant var (m_pParams -> m_SourceSet.GetFieldValue (Info.m_strName));
	if (VT_NULL == var.vt)
		return 0;

	if (VT_I4 != var.vt)
		var.ChangeType (VT_I4);

	return var.lVal;
}

/*
//	Erstelle Link zwischen Eingabetabelle und Ausgabe-Datenbank
void CDoImportPage::CreateLink (void)
{
	ASSERT (NULL != m_pParams);
	ASSERT (m_pParams -> m_DestDatabase.IsOpen ());
	ASSERT (m_pParams -> m_SourceDatabase.IsOpen ());
	ASSERT (!m_pParams -> m_strInputTableName.IsEmpty ());

	if (MdbTable == m_pParams -> m_tImportType)
		return;

	CDaoTableDef TableLink (&m_pParams -> m_DestDatabase);
	CString strCon1, strCon2, strNewTableName;
	VERIFY (strCon1.LoadString (IDS_FOXPRO_CONNECT));
	AfxFormatString1 (strCon2, IDS_DATABASE_CONNECT, m_pParams -> m_SourceDatabase.GetName());
	strCon1 += strCon2;
	strNewTableName = TableSep + m_pParams -> m_strInputTableName + TableSep;
	TableLink.Create (strNewTableName, dbAttachExclusive, m_pParams -> m_strInputTableName, strCon1);
	TableLink.Append ();
	TableLink.Close ();
	m_pParams -> m_strInputTableName = strNewTableName;		// Namen speichern
	if (m_pParams -> m_SourceSet.IsOpen ())
		m_pParams -> m_SourceSet.Close ();		
	m_pParams -> m_SourceDatabase.Close ();		// wird nicht mehr gebraucht
	m_pParams -> m_SourceSet.m_pDatabase = m_pParams -> m_DestSet.m_pDatabase;
}	
*/

/*
void CDoImportPage::DestroyLink(void)
{
	ASSERT (NULL != m_pParams);
	ASSERT (m_pParams -> m_DestDatabase.IsOpen());
	ASSERT (!m_pParams -> m_strInputTableName.IsEmpty ());

	try
	{
		if (MdbTable == m_pParams -> m_tImportType)
			return;

		m_pParams -> m_DestDatabase.DeleteTableDef (m_pParams -> m_strInputTableName);
		DAO_CHECK(m_pParams -> m_DestDatabase.m_pDAOTableDefs -> Refresh ());
	}
	catch (CException *e)
	{
		e -> Delete ();		// nur auffangen
	}
}		
*/

// Suchstring-Format aufbauen
void CDoImportPage::GetFindString (CString &strFind)
{
	ASSERT (NULL != m_pParams);
	ASSERT (NULL != m_pParams -> m_pTableInfo);
	ASSERT (!m_pParams -> m_strOutputTableName.IsEmpty ());

//	Werte init.
	strFind.Empty ();

	if (m_pParams->m_pTableInfo->KeyInpName1().IsEmpty () && m_pParams->m_pTableInfo->KeyInpName2().IsEmpty () &&
		m_pParams->m_pTableInfo->KeyOutName1().IsEmpty () && m_pParams->m_pTableInfo->KeyOutName2().IsEmpty ())
		return;

	ASSERT (!m_pParams->m_pTableInfo->KeyInpName1().IsEmpty ());
	ASSERT (!m_pParams->m_pTableInfo->KeyOutName1().IsEmpty ());
	AfxFormatString2 (strFind, IDS_SEARCH_FIELD, m_pParams->m_strOutputTableName,
												 m_pParams->m_pTableInfo->KeyOutName1());
	strFind += ParamVal1;		// LTRIM([TableName].[FieldName]) = '%1'

//	ggf. 2. Vergleich anfügen
	if (m_pParams->m_pTableInfo->KeyInpName2().IsEmpty () ||
		m_pParams->m_pTableInfo->KeyOutName2().IsEmpty ())
		return;

	CString strSecFind;
	AfxFormatString2 (strSecFind, IDS_SEARCH_FIELD, m_pParams->m_strOutputTableName,
												    m_pParams->m_pTableInfo->KeyOutName2());
	strFind += AndOper + strSecFind + ParamVal2;   // AND LTRIM([TableName].[FieldName]) = '%2'
}		

// Ausgabe-Satz suchen
BOOL CDoImportPage::FindOutputRecord (const char *pFindString)
{
	ASSERT (NULL != m_pParams);
	ASSERT (m_pParams -> m_DestSet.IsOpen ());
	COleVariant var1, var2;
	const char *pVal1 = NULL;
	const char *pVal2 = NULL;

//	1. Wert lesen
	if (!m_pParams->m_pTableInfo->KeyInpName1().IsEmpty ())
	{
		var1 = m_pParams->m_SourceSet.GetFieldValue (m_pParams->m_pTableInfo->KeyInpName1());
		if (VT_NULL == var1.vt)
			return FALSE;
		ASSERT (VT_BSTR == var1.vt);		// nur diesen Typ zulassen
		pVal1 = (const char *) var1.pbVal;
		if (!pVal1 || !*pVal1)
			return FALSE;

	//	Left trim durchführen
		while (*pVal1 && (*pVal1 == ' '))
			pVal1++;

		if (!*pVal1)		// nur Leerzeichen
			return FALSE;
	}
	
//	ggf. 2. Wert lesen
	if (!m_pParams->m_pTableInfo->KeyInpName2().IsEmpty ())
	{
		var2 = m_pParams->m_SourceSet.GetFieldValue (m_pParams->m_pTableInfo->KeyInpName2());
		if (VT_NULL == var2.vt)
			return FALSE;
		ASSERT (VT_BSTR == var2.vt);		// nur diesen Typ zulassen
		pVal2 = (const char *) var2.pbVal;
		if (!pVal2 || !*pVal2)
			return FALSE;

	//	Left trim durchführen
		while (*pVal2 && (*pVal2 == ' '))
			pVal2++;

		if (!*pVal2)		// nur Leerzeichen
			return FALSE;
	}

	if (pFindString && *pFindString)
	{
	//	fertige Anweisung zusammenbauen
		int iLen = pVal1 ? strlen (pVal1) : 0;
		iLen += pVal2 ? strlen (pVal2) : 0;
		iLen += strlen (pFindString);

		CString strFind;
		char *pFindBuffer = strFind.GetBuffer (iLen + 10);
		if (pVal2) 
			wsprintf (pFindBuffer, pFindString, pVal1, pVal2);
		else
			wsprintf (pFindBuffer, pFindString, pVal1);
		
		return m_pParams -> m_DestSet.FindFirst (pFindBuffer);
	}
	else
	{
		if (pVal2)
			return m_pParams -> m_DestSet.Seek ("=", &var1, &var2);		
		else
			return m_pParams -> m_DestSet.Seek ("=", &var1);		
	}
}

//	Import durchführen
LONG CDoImportPage::OnDoImport (UINT, LONG)
{   
	UpdateWindow ();
	CallMessageQueue ();

	ASSERT (NULL != m_pParams);
	CDaoWorkspace *pWSpace = NULL;
	if (m_pParams -> m_DestSet.CanTransact ())
		pWSpace = m_pParams -> m_DestSet.m_pDatabase -> m_pWorkspace;
	BOOL bRet = FALSE;
	try
	{
		CMutex mt;
		WasInterrupted ();		// Nutzerabbruch ?

	//	Link erstellen
		// CreateLink ();

	//	ermittle Anzahl Datensätze
		long lMaxPos = GetAnzahl ();
		lMaxPos = min(0x7FFF, lMaxPos);				// will truncate if there are more than 32k Entries	
		m_ctProgress.SetRange (0, (short)lMaxPos);	// JG typecasting to short (more then 64k Entries is invalid)
		m_ctProgress.SetPos (0);	

	//	Eingabe-Set vorbereiten
		ASSERT (!m_pParams -> m_strInputTableName.IsEmpty ());
		CString strTemp;
		AfxFormatString1 (strTemp, IDS_SELECT_ALL, m_pParams -> m_strInputTableName);
		if (m_pParams -> m_SourceSet.IsOpen ())	
			m_pParams -> m_SourceSet.Close ();	

		if (m_pParams -> m_pTableInfo -> SelectFlag () & CheckImportFlag)
			m_pParams -> m_SourceSet.Open (dbOpenDynaset, strTemp);
		else
			m_pParams -> m_SourceSet.Open (dbOpenSnapshot, strTemp, dbForwardOnly);

	//	ggf. spezielle Begin-Import-Funktion rufen
		if (m_pParams -> m_pTableInfo -> BeginImport ())
		{
			KonvertFunctionPtr pBegin = m_pParams -> m_pTableInfo -> BeginImport ();
			if (!pBegin (m_pParams))
				AfxThrowUserException ();
		}

	//	FindString zusammenbauen, bzw. Index setzen
		CString strFind;
		
	//	Ausgabeset ggf. im richtigen Modus öffnen
		if ((Index == m_pParams -> m_pTableInfo -> m_tActual) ||
		   ((Never == m_pParams -> m_pTableInfo -> m_tActual) && 
		    !m_pParams -> m_pTableInfo -> PrimaryKey().IsEmpty()))	
		{
			if (m_pParams -> m_DestSet.IsOpen ())
				m_pParams -> m_DestSet.Close ();

			ASSERT (!m_pParams -> m_strOutputTableName.IsEmpty ());
			m_pParams -> m_DestSet.Open (dbOpenTable, m_pParams -> m_strOutputTableName);

		//	Index setzen
			ASSERT (!m_pParams -> m_pTableInfo -> PrimaryKey().IsEmpty());
			m_pParams -> m_DestSet.SetCurrentIndex (m_pParams -> m_pTableInfo -> PrimaryKey ());
		}
		else
			GetFindString (strFind);

	//	Import durchführen
		VERIFY (strTemp.LoadString (IDS_DO_IMPORT));
		m_stAction.SetWindowText (strTemp);		// Nutzer informieren
		BOOL bUpdate = TRUE;					// Operation mit Datensatz
		COleVariant vars;						// akt. FeldInhalt
		VERIFY (strTemp.LoadString (IDS_REPORT_ERR_FORMAT));

		if (pWSpace)
			pWSpace -> BeginTrans ();

	//	während des Imports das Importflag prüfen ?
		BOOL bCheckImportFlag = m_pParams -> m_pTableInfo -> SelectFlag () & CheckImportFlag;
		COleVariant varImport;

		for (long lPos = 0; !m_pParams -> m_SourceSet.IsEOF (); lPos++, m_ctProgress.SetPos (lPos),
			 m_pParams -> m_SourceSet.MoveNext (), WasInterrupted ())
		{

		//	prüfe ggf. Importflag
			if (bCheckImportFlag)
			{
				m_pParams -> m_SourceSet.GetFieldValue (ExportFlag, varImport);
				if ((VT_NULL != varImport.vt) && (VT_BSTR	== varImport.vt))
				{
					char *pExportVal = (char *) varImport.pbVal;
					if (pExportVal && *pExportVal)
					{
					//	jetzt Flag prüfen
						if (atoi (pExportVal) & Importiert)	//	wenn gesetzt
							continue;						//	diesen Satz nicht noch mal imp.
					}
				}
			}

			switch (m_pParams -> m_pTableInfo -> m_tMenge)
			{
				case AllRecords:
				{
				//	automatische Aktualisierung ?						
					if (((Always == m_pParams -> m_pTableInfo -> m_tActual) && FindOutputRecord (strFind)) ||
						((Index == m_pParams -> m_pTableInfo -> m_tActual) && FindOutputRecord (NULL)))
						bUpdate = TRUE;
					else
						bUpdate = FALSE;				// Datensatz append
				}
				break;
				case OnlyRefRecords:
				{
					if (((Always == m_pParams -> m_pTableInfo -> m_tActual) && FindOutputRecord (strFind)) ||
						((Index == m_pParams -> m_pTableInfo -> m_tActual) && FindOutputRecord (NULL)))
						bUpdate = TRUE;
					else
						continue;						// keine Referenz vorhanden: nächster Datensatz
				}
				break;
				case OnlyNotRefRecords:
				{
#pragma MSG("JG")
					const char* pcTmp = NULL;
					if (!strFind.IsEmpty())
						pcTmp = strFind;

					if (FindOutputRecord (pcTmp))
//					if (FindOutputRecord (strFind.IsEmpty () ? strFind : NULL))
						continue;						// nur Datensätze ohne Referenz
					bUpdate = FALSE;					// Datensatz append
				}
				break;
				default:
				ASSERT (FALSE);
			}

		//	Art der Änderung einstellen
			if (bUpdate)
				m_pParams -> m_DestSet.Edit (); 
			else
				m_pParams -> m_DestSet.AddNew ();

		//	alle Felder der Eingabetabelle in Ausgabetabelle kopieren
			FieldKonvert *pOutputTable = m_pParams -> m_pTableInfo -> OutputTable ();
			for (FieldKonvert *pInputTable = m_pParams -> m_pTableInfo -> InputTable ();
				 pInputTable->pFieldName && *pInputTable->pFieldName; pInputTable++, pOutputTable++)
			{
			//	spezielle Konvertierung gewünscht ?
				if (pInputTable -> pfFieldKonvert)
					pInputTable -> pfFieldKonvert (m_pParams);					
				else
				{//	"normale" Konvertierung
					vars = m_pParams -> m_SourceSet.GetFieldValue (pInputTable -> pFieldName);
					if (VT_NULL == vars.vt)
						m_pParams -> m_DestSet.SetFieldValueNull (pOutputTable -> pFieldName);
					else
					{
						if (VT_BSTR == vars.vt)
						{
						//	left trim durchführen
							char *pVal = (char *) vars.pbVal;
							while (pVal && *pVal && *pVal == ' ')
								pVal++;
							if (!pVal || !*pVal)
								m_pParams -> m_DestSet.SetFieldValueNull (pOutputTable -> pFieldName);								
							else
							{
								if (pVal != (char *)vars.pbVal)
								{
									COleVariant vard (pVal, VT_BSTRT);
									m_pParams -> m_DestSet.SetFieldValue (pOutputTable -> pFieldName, vard);
								}
								else
									m_pParams -> m_DestSet.SetFieldValue (pOutputTable -> pFieldName, vars);							
							}
						}
						else
							m_pParams -> m_DestSet.SetFieldValue (pOutputTable -> pFieldName, vars);							
					}
				}
			}	// für alle Felder

		//	Werte in neuen Tabelle speichern
			try
			{
				m_pParams -> m_DestSet.Update ();
				if (bUpdate)
					m_pParams -> m_lUpdateCnt++;
				else
					m_pParams -> m_lAppendCnt++;

			//	ggf. Importflag in Eingabetabelle setzen
				if (bCheckImportFlag)
				{
					char Buffer5 [5] = "";
					itoa (Importiert, Buffer5, 10);		//	voreingestellter Wert

					if ((VT_NULL != varImport.vt) && (VT_BSTR == varImport.vt))
					{
						char *pExportVal = (char *) varImport.pbVal;
						if (pExportVal && *pExportVal)
							itoa (atoi (pExportVal) | Importiert, Buffer5, 10);	
					}
						
					m_pParams -> m_SourceSet.Edit ();
					m_pParams -> m_SourceSet.SetFieldValue (ExportFlag, Buffer5);
					m_pParams -> m_SourceSet.Update ();
				}
			}
			catch (CDaoException *de)	// bei CMemoryException alles beenden
			{
			//	Fehlermeldung in Datei ausgeben
				char Buffer [80];
				wsprintf (Buffer, strTemp, de->m_pErrorInfo->m_lErrorCode, lPos+1);
				m_pParams -> m_ReportFile.WriteString (Buffer);
				m_pParams -> m_ReportFile.WriteString (de->m_pErrorInfo->m_strDescription);
				m_pParams -> m_ReportFile.WriteString ("\n");

			//	Name der Fehler-Hilfe-Datei merken
				if (m_pParams -> m_strHelpFileName.IsEmpty () && de -> m_pErrorInfo)
					m_pParams -> m_strHelpFileName = de -> m_pErrorInfo -> m_strHelpFile;

				if (bUpdate)
					m_pParams -> m_lUpdateErrCnt++;
				else
					m_pParams -> m_lAppendErrCnt++;
				de -> Delete ();
			}
		}	// für alle Datensätze	

	//	100% fertig
		m_ctProgress.SetPos (lMaxPos);	

	//	spez. End-Import-Funktion rufen
		if (m_pParams -> m_pTableInfo -> EndImport ())
		{
			KonvertFunctionPtr pEnd = m_pParams -> m_pTableInfo -> EndImport ();
			if (!pEnd (m_pParams))
				AfxThrowUserException ();
		}

		if (pWSpace)
			pWSpace -> CommitTrans ();			// Ende der Transaktion

	//	Ini-Datei ggf. akt.
		if (m_pParams -> m_bAsNewTable)
			SetIniEntry ();

		bRet = TRUE;
	}
	catch (CUserException *e)
	{
		e -> Delete ();			// hier Abbruch durch Nutzer
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}

//	Link zur Eingabe-Tabelle wieder auflösen
	// DestroyLink ();

//	Ergebnis des Imports auswerten
	if (!bRet)
	{
		if (pWSpace)
			pWSpace -> Rollback ();
		GetParent () -> EndDialog (IDCANCEL);
		return TRUE;
	}

//	auf nächste Seite gehen
	GetParent () -> SetWizardButtons (PSWIZB_NEXT);
	GetParent () -> PressButton (PSBTN_NEXT);
	:: MessageBeep (MB_OK);
	return TRUE;
}

//	die Ausgabetabelle in INI-Datei schreiben
void CDoImportPage::SetIniEntry(void)
{
	ASSERT (NULL != m_pParams);
	ASSERT (NULL != m_pParams -> m_pTableInfo);
	ASSERT (!m_pParams -> m_strOutputTableName.IsEmpty ());
	ASSERT (!m_pParams -> m_pTableInfo -> TableName ().IsEmpty ());

	CString strEntry, strSection, strTableName;
	AfxFormatString1 (strEntry, IDS_TABLE_ENTRY, m_pParams -> m_pTableInfo -> TableName ());
	AfxFormatString1 (strTableName, IDS_ENTRY_FORMAT, m_pParams -> m_strOutputTableName); 	
	VERIFY (strSection.LoadString (IDS_CONFIG_SECTION));
	AfxGetApp () -> WriteProfileString (strSection, strEntry, strTableName);
	((CGakApp *) AfxGetApp ()) -> ReadTablesFromIni ();
}

void CDoImportPage :: OnHelp ()
{
	AfxGetApp () -> WinHelp (IDD+HelpDialogOffset);
}
