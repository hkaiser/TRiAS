// resdlg.cpp : implementation file
//

#include "stdafx.h"  		//	prec. Header
#include "res.h"			//	Resource-Konstanten
#include "recset.h"			// 	CRecordsetExt
#include "erzliste.h"		// 	CErzListeSet
#include "reptable.h"		//	CReportTable
#include "getodbci.hpp"
#include "resdlg.h"			//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResultDialog dialog
CResultDialog::CResultDialog(CWnd* pParent,BOOL bAbgleich)
	: CDialog(CResultDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResultDialog)
	m_strErzListe = "";
	m_pDatabase = NULL;
	m_strAbglCnt = _T("");
	m_strEscCnt = _T("");
	m_strInListeCnt = _T("");
	m_strOutputCnt = _T("");
	//}}AFX_DATA_INIT

	m_bAbgleich = bAbgleich;
}

void CResultDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResultDialog)
	DDX_Control(pDX, IDT_DELETED_REC, m_stDeletedRec);
	DDX_Control(pDX, IDB_OUTPUT_ERZLISTE, m_btErzListe);
	DDX_Text(pDX, IDT_ABGL_CNT, m_strAbglCnt);
	DDX_Text(pDX, IDT_ESC_CNT, m_strEscCnt);
	DDX_Text(pDX, IDT_INLISTE_DEL_CNT, m_strInListeCnt);
	DDX_Text(pDX, IDT_UEBERN_CNT, m_strOutputCnt);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CResultDialog, CDialog)
	//{{AFX_MSG_MAP(CResultDialog)
	ON_BN_CLICKED(IDB_OUTPUT_ERZLISTE, OnOutputErzliste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//	Ausgabe der Erzeugerliste        
void CResultDialog::OnOutputErzliste()
{   
	m_btErzListe.EnableWindow (FALSE);               
	m_btErzListe.EnableWindow (OutputErzeugerListe ());
}                          

BOOL CResultDialog::OutputErzeugerListe ()
{
	try
	{   
		CWaitCursor wc;                                  
		
	//	prüfe Parameter
		ASSERT (!m_strErzListe.IsEmpty ());
		ASSERT (NULL != m_pDatabase && m_pDatabase -> IsOpen ());
		
	//	Datei erzeugen
		CErzListeSet Set (m_pDatabase);
		CString strSQL;
		AfxFormatString1 (strSQL, IDS_ERZLISTE_SELECT, m_strErzListe);
		Set.Open (CRecordset::forwardOnly, strSQL, CRecordset::readOnly);				
		if (Set.IsEOF ())
		{
			CString strInfo;
			AfxFormatString1 (strInfo, IDS_NO_LIST_RECORDS, m_strErzListe);
			OutputInfo (strInfo);
			return FALSE;						
		}

		CReportTable Dlg (this, &Set, m_strErzListe);		
		Dlg.DoModal ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
		return FALSE;
	}
	
	return TRUE;
}

BOOL CResultDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	CString strInfo, strFormat, strCaption;
	VERIFY (strInfo.LoadString (m_bAbgleich ? IDS_DATEN_ABGLEICH : IDS_DATEN_KONTROLLE));
	GetWindowText (strFormat);
	strCaption.Format (strFormat, (const char *)strInfo);
	SetWindowText (strCaption);

	if (!m_bAbgleich)
	{
		VERIFY (strInfo.LoadString (IDS_DELETE_RECS));
		m_stDeletedRec.SetWindowText (strInfo);
	}

	m_btErzListe.EnableWindow (!m_strErzListe.IsEmpty ());
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
