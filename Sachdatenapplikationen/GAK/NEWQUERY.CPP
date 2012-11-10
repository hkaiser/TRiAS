// NewQuery.cpp : implementation file
//

#include "stdafx.h"			// prec. Header
#include "gak.h"			// CGakApp u. Ressourcen
#include "NewQuery.h"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const char TableQualifier [] = ".";
const char TempQueryName [] = "TempQuery";

typedef struct 
{
	const char *pContents;
	const char *pComment;
}	LISTE;

const LISTE OperatorList [] = {
//  Operatoren-Liste
	{   "+",			"Numerische Addition."},
	{   "-",			"Numerische Subtraktion."},
	{   "*",			"Numerische Multiplikation."},
	{   "/",			"Numerische Division."},
	{   "=",			"Werte sind gleich."},
	{   "<>",			"Werte sind verschieden."},
	{   "<",			"Wert ist kleiner."},
	{   ">",			"Wert ist größer."},
	{   "<=",			"Wert ist kleiner oder gleich."},
	{   ">=",			"Wert ist größer oder gleich."},
	{	"&",			"Verkettung von Zeichenfolgen."},
	{   "AND",			"Logisches UND."},
	{   "OR",			"Logisches ODER."},
	{   "NOT",			"Logische Verneinung."},
	{	"IS NULL",		"Wert ist nicht vorhanden."},
	{	"IS NOT NULL",	"Wert ist vorhanden."},
	{	"LIKE",			"Abfrage in angegebener Maske, z.B.: LIKE '12'."},
	{	"IN",			"Abfrage in vorgegener Menge, z.B.: IN (10, 20, 30)."},
	{	"BETWEEN AND",	"Abfrage im angegebenen Bereich, z.B.: BETWEEN 100 AND 200."},
	{	"DIV",			"Ganzzahlige Division."},
	{	"MOD",			"Rest einer ganzzahligen Division."}
};

const LISTE FunctionList [] = {
//  Liste der benutzten Funktionen
//	mathematische Funktionen
	{	"ABS()", "Berechnet den Absolutwert einer Zahl."},
	{	"ATN()", "Berechnet den Arkustangens einer Zahl."},
	{	"COS()", "Berechnet den Kosinus eines Winkels."},
	{	"EXP()", "Gibt e (die Basis des natürlichen Logarithmus) potenziert mit einer Zahl zurück."},
	{	"FIX()", "Gibt den ganzzahligen Anteil einer Zahl zurück, die bei negativem Wert größer oder gleich diesem ist."},
	{	"INT()", "Gibt den ganzzahligen Anteil einer Zahl zurück, die bei negativem Wert kleiner oder gleich diesem ist."},
	{	"LOG()", "Berechnet den natürlichen Logarithmus einer Zahl."},
	{	"RND()", "Gibt eine Zufallszahl zurück, die im Bereich von 0 (eingeschlossen) bis 1 (nicht eingeschlossen) liegt."},
	{	"SGN()", "Gibt einen ganzzahligen Wert zurück, der das Vorzeichen einer Zahl darstellt: -1 kleiner 0, 1 größer 0 und 0 wenn Zahl gleich 0 ist."},
	{	"SIN()", "Berechnet den Sinus eines Winkels."},
	{	"SQR()", "Gibt die Quadratwurzel einer Zahl zurück."},
	{	"TAN()", "Berechnet den Tangens eines Winkels."},
//	Stringfunktionen
	{	"ASC()",	"Gibt den Zeichencode zurück, der dem ersten Buchstaben in einer Zeichenfolge entspricht."},	
	{	"CHR()",	"Gibt das Zeichen für den angegebenen Zeichencode zurück."},
	{	"INSTR()",	"Gibt die Position des ersten Auftretens einer Zeichenfolge innerhalb einer anderen Zeichenfolge zurück, Syntax: InStr([Startposition,]ZK1, ZK2[, Vergleich])."},
	{	"LCASE()",	"Gibt eine Zeichenfolge zurück, in der alle Buchstaben in Kleinbuchstaben umgewandelt worden sind."},
	{	"LTRIM()",	"Gibt eine Kopie einer Zeichenfolge zurück, die keine führenden Leerzeichen enthält."},
	{	"LEFT()",	"Gibt eine bestimmte Anzahl von Zeichen ab dem ersten (linken) Zeichen einer Zeichenfolge zurück, Syntax: Left(Zeichenkette,Länge)."},
	{	"LEN()",	"Gibt die Anzahl der Zeichen in einer Zeichenfolge zurück."},
	{	"MID()",	"Gibt eine bestimmte Anzahl von Zeichen aus einer Zeichenfolge zurück, Syntax: Mid(Zeichenkette,Startposition[, Länge])."},
	{	"RTRIM()",	"Gibt eine Kopie einer Zeichenfolge zurück, die keine nachgestellten Leerzeichen enthält."},
	{	"RIGHT()",	"Gibt eine bestimmte Anzahl von Zeichen vom rechten Teil (dem Ende) einer Zeichenfolge zurück, Syntax: Right(Zeichenkette,Länge)."},
	{	"SPACE()",	"Gibt eine Zeichenfolge mit einer bestimmten Anzahl an Leerzeichen zurück, Syntax: Space(Zahl)"},
	{	"STR()",	"Gibt die Zeichenfolgendarstellung einer Zahl zurück, Syntax: Str(Zahl)."},
	{	"STRING()",	"Gibt eine Zeichenfolge in der angegebenen Länge mit einem sich wiederholenden Zeichen zurück, Syntax: String(Zahl,Zeichen)."},
	{	"TRIM()",	"Gibt eine Kopie einer Zeichenfolge zurück, die weder führende noch nachgestellte Leerzeichen enthält."},
	{	"UCASE()",	"Gibt eine Zeichenfolge zurück, die in Großbuchstaben umgewandelt wurde."},
//	Aggregatefunktionen
	{	"AVG()",	"Berechnet den arithmetischen Mittelwert einer Menge von Werten in einem bestimmten Feld einer Abfrage."},
	{	"COUNT()",	"Berechnet die Anzahl der von einer Abfrage zurückgegebenen Datensätze."},
	{	"FIRST()",	"Gibt den ersten Wert aus einer Reihe von Werten zurück, der in einem bestimmten Feld einer Abfrage enthalten ist."},
	{	"LAST()",	"Gibt den letzten Wert aus einer Reihe von Werten zurück, der in einem bestimmten Feld einer Abfrage enthalten ist."},
	{	"MIN()",	"Gibt den kleinsten Wert aus einer Reihe von Werten zurück, der in einem bestimmten Feld einer Abfrage enthalten ist."},
	{	"MAX()",	"Gibt den kleinsten Wert aus einer Reihe von Werten zurück, der in einem bestimmten Feld einer Abfrage enthalten ist."},
	{	"SUM()",	"Gibt die Summe einer Reihe von Werten zurück, die in einem bestimmten Feld einer Abfrage enthalten ist."},
//	Konvertierungsfunktionen
	{	"CCur()",	"Wandelt einen Ausdruck in den Typ Currency um."},
	{	"CDbl()",	"Wandelt einen Ausdruck in den Typ Double um."},
	{	"CInt()",	"Wandelt einen Ausdruck in den Typ Integer um."},
	{	"CLng()",	"Wandelt einen Ausdruck in den Typ Long um."},
	{	"CSng()",	"Wandelt einen Ausdruck in den Typ Single um."},
	{	"CStr()",	"Wandelt einen Ausdruck in den Typ String um."},
	{	"CDate()",	"Wandelt einen Ausdruck in den Typ Date um."},
//	Datumsfunktionen
	{	"DATE()",	"Gibt das aktuelle Systemdatum zurück."},
	{	"DAY()",	"Gibt den Tag des Monats als ganze Zahl im Bereich von 1 bis 31 zurück."},
	{	"HOUR()",	"Gibt eine ganze Zahl im Bereich von 0 bis 23 zurück, die die Stunde des Tages darstellt."},
	{	"MINUTE()",	"Gibt eine ganze Zahl im Bereich von 0 bis 59 zurück, die die Minute in der Stunde darstellt."},
	{	"MONTH()",	"Gibt eine ganze Zahl im Bereich von 0 bis 59 zurück, die die Minute in der Stunde darstellt."},
	{	"NOW()",	"Gibt das aktuelle Datum und die aktuelle Zeit aus den Einstellungen für das Systemdatum und die Systemzeit auf Ihrem Computer zurück."},
	{	"SECOND()",	"Gibt eine ganze Zahl im Bereich von 0 bis 59 zurück, die die Sekunde in der Minute darstellt."},
	{	"TIME()",	"Gibt einen Wert vom Typ Date zurück, der die aktuelle Systemzeit angibt."},
	{	"WEEKDAY()","Gibt den Wochentag als ganze Zahl zurück, Syntax: Weekday(Datum, [1. Tag der Woche])."},	
	{	"YEAR()",	"Gibt das Jahr als ganze Zahl zurück."},
};

/////////////////////////////////////////////////////////////////////////////
// CNewQueryDef dialog
CNewQueryDef::CNewQueryDef(CWnd* pParent, CDaoDatabase *pDatabase)
	: CDialog(CNewQueryDef::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewQueryDef)
	//}}AFX_DATA_INIT

	m_pDatabase = NULL;

	ASSERT (NULL != pDatabase);
	ASSERT_VALID (pDatabase);
	ASSERT (pDatabase -> IsOpen ());

	m_pDatabase = pDatabase;
}

CNewQueryDef:: ~CNewQueryDef (void)
{
	
}

void CNewQueryDef::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewQueryDef)
	DDX_Control(pDX, IDB_QUERY_ART, m_btAbfrageArt);
	DDX_Control(pDX, IDC_TABLES, m_stTables);
	DDX_Control(pDX, IDC_OPERATORS, m_stOperators);
	DDX_Control(pDX, IDC_FUNCTIONS, m_stFunctions);
	DDX_Control(pDX, IDC_FIELDS, m_stFields);
	DDX_Control(pDX, IDB_CHECK, m_btCheck);
	DDX_Control(pDX, IDE_DESCRPITION, m_edDescription);
	DDX_Control(pDX, IDB_ED_BACK, m_btBack);
	DDX_Control(pDX, IDL_TABLES, m_lbTables);
	DDX_Control(pDX, IDL_OPERATORS, m_lbOperators);
	DDX_Control(pDX, IDL_FUNCTIONS, m_lbFunctions);
	DDX_Control(pDX, IDL_FIELDS, m_lbFields);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDE_SQL, m_edSQL);
	DDX_Control(pDX, IDE_NAME, m_edName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewQueryDef, CDialog)
	//{{AFX_MSG_MAP(CNewQueryDef)
	ON_EN_CHANGE(IDE_NAME, OnChangeName)
	ON_EN_CHANGE(IDE_SQL, OnChangeSql)
	ON_LBN_SELCHANGE(IDL_FIELDS, OnSelchangeFields)
	ON_LBN_DBLCLK(IDL_FIELDS, OnDblclkFields)
	ON_LBN_DBLCLK(IDL_TABLES, OnDblclkTables)
	ON_LBN_SELCHANGE(IDL_TABLES, OnSelchangeTables)
	ON_LBN_SELCHANGE(IDL_OPERATORS, OnSelchangeOperators)
	ON_LBN_DBLCLK(IDL_OPERATORS, OnDblclkOperators)
	ON_LBN_DBLCLK(IDL_FUNCTIONS, OnDblclkFunctions)
	ON_LBN_SELCHANGE(IDL_FUNCTIONS, OnSelchangeFunctions)
	ON_BN_CLICKED(IDB_ED_BACK, OnEdBack)
	ON_BN_CLICKED(IDB_CHECK, OnCheck)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDB_QUERY_ART, OnQueryArt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewQueryDef message handlers

void CNewQueryDef::OnOK() 
{
	m_btCheck.EnableWindow (FALSE);

	CString strSQL;
	m_edSQL.GetWindowText (strSQL);
	if (!CheckSQL (strSQL))
	{
		m_btOk.EnableWindow (FALSE);
		return;
	}

//	SQL-String ist Ok
	m_edName.GetWindowText (m_strName);
	m_edSQL.GetWindowText (m_strSQL);
	
	CDialog::OnOK();
}

BOOL CNewQueryDef::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CWaitCursor wc;
	CMutex mt;

//	TODO: Add extra initialization here
	m_edName.LimitText (MaxQueryDefNameLen);

//	Werte in Controls setzen
	m_edName.SetWindowText (m_strName);
	m_edSQL.SetWindowText (m_strSQL);

//	Caption setzen
	CString strCaption;
	VERIFY (strCaption.LoadString (m_strName.IsEmpty () ? 
							       IDS_NEW_QUERY : IDS_MODIFY_QUERY));
	SetWindowText (strCaption);

//	Tabellen in Listbox ausgeben
	ASSERT (NULL != m_pDatabase);
	ASSERT_VALID (m_pDatabase);
	ASSERT (m_pDatabase -> IsOpen ());

	short sTableCnt = m_pDatabase -> GetTableDefCount ();
	CDaoTableDefInfo Info;
	int iMaxLen = 0;
	for (short iIndex = 0; iIndex < sTableCnt; iIndex++)
	{
		m_pDatabase -> GetTableDefInfo (iIndex, Info);		//  only primary info
		if (dbSystemObject & Info.m_lAttributes)			//	keine Systemtabelle
			continue;

		if (m_lbTables.AddString (Info.m_strName) < 0)
			AfxThrowMemoryException ();
		iMaxLen = max (iMaxLen, Info.m_strName.GetLength ());
	}

//	Scrollbalken setzen
	WORD wUnits = LOWORD (:: GetDialogBaseUnits ());
	m_lbTables.SetHorizontalExtent (iMaxLen*wUnits);

//	Anzahl ausgeben
	char Buffer10 [] = "";
	CString strCnt;
	itoa (m_lbTables.GetCount (), Buffer10, 10);
	AfxFormatString1 (strCnt, IDS_TABLE_COUNT, Buffer10);
	m_stTables.SetWindowText (strCnt);

//  Operator-Liste füllen
	short Entries = sizeof (OperatorList) / sizeof (LISTE);
	short i = 0;
	iMaxLen = 0;
	for (; i < Entries; i++) 
	{
		if (m_lbOperators.AddString (OperatorList[i].pContents) < 0) 
			AfxThrowMemoryException ();
		iMaxLen = max (iMaxLen, static_cast<int> (strlen (OperatorList[i].pContents))); // JG cast
	}
//	Scrollbalken setzen
	m_lbOperators.SetHorizontalExtent (iMaxLen*wUnits);;

//	Anzahl ausgeben
	itoa (Entries, Buffer10, 10);
	AfxFormatString1 (strCnt, IDS_OPERA_COUNT, Buffer10);
	m_stOperators.SetWindowText (strCnt);

//  Funktionen-Liste füllen
	Entries = sizeof (FunctionList) / sizeof (LISTE);
	iMaxLen = 0;
	for (i = 0; i < Entries; i++) 
	{
		if (m_lbFunctions.AddString (FunctionList [i].pContents) < 0)
			AfxThrowMemoryException ();
		iMaxLen = max (iMaxLen, static_cast<int> (strlen (FunctionList [i].pContents)));// JG cast
	}

//	Scrollbalken setzen
	m_lbFunctions.SetHorizontalExtent (iMaxLen*wUnits);

//	Anzahl ausgeben
	itoa (Entries, Buffer10, 10);
	AfxFormatString1 (strCnt, IDS_FUNCTION_COUNT, Buffer10);
	m_stFunctions.SetWindowText (strCnt);

//	Standard-Abfrage setzen
	m_btAbfrageArt.SetCheck (1);
	CString strTemp;
	VERIFY (strTemp.LoadString (IDS_STANDARD_QUEYRY));
	m_btAbfrageArt.SetWindowText (strTemp);

	SetControlState ();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewQueryDef::OnChangeName() 
{
	// TODO: Add your control notification handler code here
	SetControlState ();	
}

void CNewQueryDef::OnChangeSql() 
{
	// TODO: Add your control notification handler code here
	SetControlState ();	
}

void CNewQueryDef::SetControlState (void)
{
	if ((m_edName.LineLength () > 0) && (m_edSQL.LineLength () > 0))
	{
		m_btOk.EnableWindow (TRUE);
		m_btCheck.EnableWindow (TRUE);
	}
	else
	{
		m_btOk.EnableWindow (FALSE);
		m_btCheck.EnableWindow (FALSE);
	}

	if (m_lbFields.GetCount () > 0)
		m_lbFields.EnableWindow (TRUE);
	else
		m_lbFields.EnableWindow (FALSE);

	if (m_edSQL.CanUndo ())
		m_btBack.EnableWindow (TRUE);
	else
		m_btBack.EnableWindow (FALSE);
}

//	Felder löschen
void CNewQueryDef::DeleteFieldInfos (void)
{
 	int iCnt = m_lbFields.GetCount ();		
	if (iCnt <= 0)
		return;

	CString *pStrInfo = NULL;
	for (int i = 0; i < iCnt; i++)
	{
		pStrInfo = (CString *) m_lbFields.GetItemData (i);
		ASSERT (NULL != pStrInfo);
		DELETE_OBJ (pStrInfo);
	}

	m_lbFields.ResetContent ();		// alten Info löschen
}	

void CNewQueryDef::OnSelchangeTables() 
{
	// TODO: Add your control notification handler code here
	try
	{
		int iSel = m_lbTables.GetCurSel ();	
		if (iSel < 0)
			return;

		CString strNewTableName;
		m_lbTables.GetText (iSel, strNewTableName);
		if (strNewTableName == m_strTableName)
			return;

		CWaitCursor wc;
		CMutex;
		m_strTableName = strNewTableName;		// Tabellennamen speichern
		CString strTableInfo;
		AfxFormatString1 (strTableInfo, IDS_TABLE_INFO, m_strTableName);
		m_edDescription.SetWindowText (strTableInfo);		// Beschreibung ausgeben

	//	alle Feldinfos ausgeben
		DeleteFieldInfos ();					// alten Felder löschen
		ASSERT (NULL != m_pDatabase);
		ASSERT (m_pDatabase -> IsOpen ());
		CDaoTableDef TableDef (m_pDatabase);
		TableDef.Open (m_strTableName);

		short sFieldCnt = TableDef.GetFieldCount ();
		CDaoFieldInfo Info;
		CString strTypeName, strLen, strInfo;
		char Buffer30 [] = "";
		int iIndex = -1;
		int iMaxLen = 0;
		for (short sIndex = 0; sIndex < sFieldCnt; sIndex++)
		{
			TableDef.GetFieldInfo (sIndex, Info); // only primary info: type, name, len
			switch (Info.m_nType)
			{
				case dbLongBinary:		// diese Typen nicht in Listbox ausgeben
				case dbGUID:
					continue;
				default:
					strTypeName = GetFieldType (Info.m_nType);
			}				
				
			ltoa (Info.m_lSize, Buffer30, 10);
			strLen = Buffer30;
			AfxFormatString2 (strInfo, IDS_FIELD_INFO, strTypeName, strLen);

		//	Feldnamen in Listbox ausgeben
			iIndex = m_lbFields.AddString (Info.m_strName);
			iMaxLen = max (iMaxLen, Info.m_strName.GetLength ());
			if (iIndex < 0)
				AfxThrowMemoryException ();	

		//	Feldbeschreibung speichern
			CString *pDescription = new CString (strInfo);
			if (m_lbFields.SetItemData (iIndex, (DWORD) pDescription) < 0)
				AfxThrowMemoryException ();	
		}

	//	Srcollbalken stezen
		WORD wUnits = LOWORD (:: GetDialogBaseUnits ());
		m_lbFields.SetHorizontalExtent (iMaxLen*wUnits);

	//	Tabelle schließen
		if (TableDef.IsOpen ())
			TableDef.Close ();

	//	Anzahl ausgeben
		char Buffer10 [] = "";
		CString strCnt;
		itoa (m_lbFields.GetCount (), Buffer10, 10);
		AfxFormatString1 (strCnt, IDS_FIELD_COUNT, Buffer10);
		m_stFields.SetWindowText (strCnt);

		SetControlState ();
	}
	catch (CDaoException *e)
	{
		DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
}

void CNewQueryDef::OnDblclkTables() 
{
	// TODO: Add your control notification handler code here
	try
	{
		int iSel = m_lbTables.GetCurSel ();
		if (iSel < 0)
			return;

		CString strSel, strNewSel;
		m_lbTables.GetText (iSel, strSel);

	//	ggf. Namen klammmern
		if (strSel.Find (" ") >= 0)
			AfxFormatString1 (strNewSel, IDS_BRACKETS, strSel);
		else
			strNewSel = strSel;

		m_edSQL.ReplaceSel (strNewSel);
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
}

void CNewQueryDef::OnSelchangeFields() 
{
	int iSel = m_lbFields.GetCurSel ();
	if (iSel < 0)
		return;

	CString *pStrInfo = (CString *) m_lbFields.GetItemData (iSel);
	ASSERT (NULL != pStrInfo);
	m_edDescription.SetWindowText (pStrInfo -> operator LPCTSTR ());
}

void CNewQueryDef::OnDblclkFields() 
{
	try
	{
		int iSel = m_lbFields.GetCurSel ();
		if (iSel < 0)
			return;

		CString strSel, strNewSel;
		m_lbFields.GetText (iSel, strSel);

	//	ggf. Namen klammmern
		if (strSel.Find (" ") >= 0)
			AfxFormatString1 (strNewSel, IDS_BRACKETS, strSel);
		else
			strNewSel = strSel;

	//	mit vorangestellter Tabelle;
		iSel = m_lbTables.GetCurSel ();
		ASSERT (iSel >= 0);
		CString strTable, strNewTable;
		m_lbTables.GetText (iSel, strTable);

	//	ggf. Namen klammmern
		if (strTable.Find (" ") >= 0)
			AfxFormatString1 (strNewTable, IDS_BRACKETS, strTable);
		else
			strNewTable = strTable;

	//	Qualifier zusammenbauen
		strNewTable += TableQualifier + strNewSel;		
		m_edSQL.ReplaceSel (strNewTable);
	}
	catch (CMemoryException *e)
	{
		e -> ReportError (),
		e -> Delete ();
	}
}

void CNewQueryDef::OnDblclkOperators() 
{
	int iSel = m_lbOperators.GetCurSel ();
	if (iSel < 0)
		return;	

	CString strSel;
	m_lbOperators.GetText (iSel, strSel);
	m_edSQL.ReplaceSel (strSel);
}

void CNewQueryDef::OnDblclkFunctions() 
{
	int iSel = m_lbFunctions.GetCurSel ();
	if (iSel < 0)
		return;	

	CString strSel;
	m_lbFunctions.GetText (iSel, strSel);
	m_edSQL.ReplaceSel (strSel);
	
}

void CNewQueryDef::OnEdBack() 
{
	if (m_edSQL.CanUndo ())
		m_edSQL.Undo ();
}

BOOL CNewQueryDef::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	DeleteFieldInfos ();
	
	return CDialog::DestroyWindow();
}

void CNewQueryDef::OnSelchangeFunctions() 
{
	int iSel = m_lbFunctions.GetCurSel ();
	if (iSel < 0)
		return;

#ifdef _DEBUG
	short sMaxIndex = sizeof (FunctionList) / sizeof (LISTE);
	ASSERT (iSel < sMaxIndex); 
#endif
	m_edDescription.SetWindowText (FunctionList [iSel].pComment);
}

void CNewQueryDef::OnSelchangeOperators() 
{
	int iSel = m_lbOperators.GetCurSel ();
	if (iSel < 0)
		return;

#ifdef _DEBUG
	short sMaxIndex = sizeof (OperatorList) / sizeof (LISTE);
	ASSERT (iSel < sMaxIndex); 
#endif
	m_edDescription.SetWindowText (OperatorList [iSel].pComment);
}

//	Expression prüfen
void CNewQueryDef::OnCheck() 
{
	m_btCheck.EnableWindow (FALSE);

	CString strSQL;
	m_edSQL.GetWindowText (strSQL);
	if (CheckSQL (strSQL))
		m_btOk.EnableWindow (TRUE);
	else
		m_btOk.EnableWindow (FALSE);
}

BOOL CNewQueryDef::CheckSQL (const CString &strSQL)
{
	try
	{
		ASSERT (NULL != m_pDatabase);
		ASSERT (m_pDatabase -> IsOpen ());
		CWaitCursor wc;
		CMutex mt;
		CDaoQueryDef NewDef (m_pDatabase);
		try
		{
			NewDef.Create (TempQueryName, strSQL);	// Abfrage erzeugen			
			NewDef.Append ();						// Parsen des SQL-Ausdrucks
			NewDef.Close ();
			m_pDatabase -> DeleteQueryDef (TempQueryName); // wieder löschen

		//	Nutzer informieren
			CString strInfo;
			VERIFY (strInfo.LoadString (IDS_QUERY_OK));
			m_edDescription.SetWindowText (strInfo);
			return TRUE;
		}
		catch (CDaoException *e)
		{
			DisplayDaoException (e);
			e -> Delete ();
		}
		catch (CException *e)					// Fehler
		{
			e -> ReportError ();
			e -> Delete ();
		}
	}
	catch (CDaoException *e)
	{
		DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}		

	return FALSE;
}

BOOL CNewQueryDef::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	// return CDialog::OnHelpInfo(pHelpInfo);
	ASSERT (pHelpInfo != NULL);

	if (pHelpInfo -> dwContextId)
		WinHelp (pHelpInfo -> dwContextId, HELP_CONTEXTPOPUP);

	return TRUE;
}

void CNewQueryDef::DisplayDaoException (CDaoException *de)
{
	ASSERT (NULL != de);
	ASSERT (de -> IsKindOf (RUNTIME_CLASS (CDaoException)));

	try
	{
		CString strInfo;
		::MessageBeep (MB_OK);
		strInfo.Format (IDS_DABASE_ERROR_FORMAT, de->m_pErrorInfo->m_lErrorCode, 
					   (LPCTSTR)de->m_pErrorInfo->m_strDescription);
		m_edDescription.SetWindowText (strInfo);
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
}

void CNewQueryDef::OnQueryArt() 
{
	CString strTemp, strNewName;
	VERIFY (strTemp.LoadString (m_btAbfrageArt.GetCheck () == 1 ?
								IDS_STANDARD_QUEYRY : IDS_BILANZ_QUERY));
	m_btAbfrageArt.SetWindowText (strTemp);

	m_edName.GetWindowText (strTemp);		
	const char *pBilanz = strstr (strTemp, BilanzKennung);
	if (m_btAbfrageArt.GetCheck () == 1)	// Bei Standard
	{
		if (pBilanz && (pBilanz == strTemp))
		{
			strNewName = strTemp.Mid (strlen (BilanzKennung)); //	Kennung entfernen
			m_edName.SetWindowText (strNewName);
		}
	}
	else	// Bilanz
	{
		if (!pBilanz || (pBilanz != strTemp))
		{
			strNewName = BilanzKennung + strTemp;		// Kennung dazu
			m_edName.SetWindowText (strNewName);
		}
	}
}

