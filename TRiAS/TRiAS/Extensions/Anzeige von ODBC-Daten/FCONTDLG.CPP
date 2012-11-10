// FContDlg.cpp : implementation file
//

#include "pheader.h"
#include "odbcext.hr"				//	Resource-Konstanten

#include <hpp/FContDlg.h>				//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFieldContentsDlg dialog


CFieldContentsDlg::CFieldContentsDlg(CWnd* pParent, CDatabase *pDatabase,
	const char *pTable, const char *pField)
: CDialog(CFieldContentsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFieldContentsDlg)
	m_strFieldName = _T("");
	m_strFieldType = _T("");
	//}}AFX_DATA_INIT
	m_pDatabase = NULL;
	m_uiResID = 0;

	ASSERT (NULL != pDatabase && pDatabase -> IsOpen ());
	m_pDatabase = pDatabase;
	ASSERT (NULL != pTable && AfxIsValidString (pTable));
	ASSERT (NULL != pField && AfxIsValidString (pField));
	m_strTable = pTable;
	m_strField = pField;
}

void CFieldContentsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFieldContentsDlg)
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDL_FELD_CONTENTS, m_lbFields);
	DDX_Text(pDX, IDT_FELDNAME, m_strFieldName);
	DDX_Text(pDX, IDT_FELD_TYP, m_strFieldType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFieldContentsDlg, CDialog)
	//{{AFX_MSG_MAP(CFieldContentsDlg)
	ON_LBN_SELCHANGE(IDL_FELD_CONTENTS, OnSelchangeFeldContents)
	ON_LBN_DBLCLK(IDL_FELD_CONTENTS, OnDblclkFeldContents)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFieldContentsDlg message handlers

BOOL CFieldContentsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	try
	{		
	//	prüfe Parameter
		ASSERT (NULL != m_pDatabase && m_pDatabase -> IsOpen ());
		ASSERT (!m_strField.IsEmpty ());
		ASSERT (!m_strTable.IsEmpty ());

	//	Listbox füllen
		CWaitCursor wc;

	//	zuerst SelectString zusammenbauen
		CString strSelect;
		AfxFormatString2 (strSelect, IDS_SELECT_FIELD, m_strField, m_strTable);
		CRecordset rs (m_pDatabase);
		VERIFY (rs.Open (CRecordset::forwardOnly, strSelect, CRecordset::readOnly));
		CString strVal;
		int iMax = 0;
		while (!rs.IsEOF ())
		{
			rs.GetFieldValue (m_strField, strVal);
			if (!strVal.IsEmpty ())
			{
				if (m_lbFields.AddString (strVal) < 0)
					AfxThrowMemoryException ();
				iMax = max (iMax, strVal.GetLength ());
			}
			rs.MoveNext ();
		}

	//	HorizontalExtent setzen
		if (iMax > 0)
		{
			WORD wUnits = LOWORD (:: GetDialogBaseUnits ());
			m_lbFields.SetHorizontalExtent (wUnits * iMax);
		}

	//	TypInfo ausgeben
		CODBCFieldInfo FieldInfo;
		rs.GetODBCFieldInfo (m_strField, FieldInfo);
		switch (FieldInfo.m_nSQLType)
		{
			case SQL_DATE:		//	Zeitformate
			case SQL_TIME:
			case SQL_TIMESTAMP:		
			{
				m_uiResID = IDS_DATETIME_FORMAT;
				VERIFY (m_strFieldType.LoadString (IDS_DATE_TIME));
			}
			break;
			case SQL_DECIMAL:   
			case SQL_NUMERIC:   
			case SQL_BIGINT: 
			case SQL_CHAR:
			case SQL_VARCHAR:
			{
				m_uiResID = IDS_STRING_FORMAT;
				VERIFY (m_strFieldType.LoadString (IDS_TEXT));
			}
			break;
			default:			//	 alle Zahlenformate
				VERIFY (m_strFieldType.LoadString (IDS_ZAHL));
			break;
		}
	
	//	Caption setzen
		CString strFormat;
		GetWindowText (strFormat);
		strVal.Format (strFormat, m_strTable);
		SetWindowText (strVal);

	//	Feldname setzen
		m_strFieldName = FieldInfo.m_strName;

	//	Controls setzen
		m_lbFields.EnableWindow (m_lbFields.GetCount () > 0);	
		m_btOk.EnableWindow (FALSE);

		rs.Close ();

		UpdateData (FALSE);
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFieldContentsDlg::OnSelchangeFeldContents() 
{
	// TODO: Add your control notification handler code here
	m_btOk.EnableWindow (TRUE);
}
void CFieldContentsDlg::OnDblclkFeldContents() 
{
	// TODO: Add your control notification handler code here
	OnOK ();
}

void CFieldContentsDlg::OnOK() 
{
	// TODO: Add extra validation here
	CString strSel;
	m_lbFields.GetText (m_lbFields.GetCurSel (), strSel);		

	if (m_uiResID > 0)
		m_strSelection.Format (m_uiResID, strSel);
	else
		m_strSelection = strSel;
	
	CDialog::OnOK();
}
