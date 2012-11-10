// ImpResPg.cpp : implementation file
//

#include "stdafx.h"			// prec. Header
#include "gak.h"			// CGakApp u. Ressourcen
#include "importty.h"		// CImportParams
#include "ImpResPg.h"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportResultPage property page

IMPLEMENT_DYNCREATE(CImportResultPage, CPropertyPage)

CImportResultPage::CImportResultPage() : CPropertyPage(CImportResultPage::IDD)
{
	//{{AFX_DATA_INIT(CImportResultPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pParams = NULL;
}

CImportResultPage::~CImportResultPage()
{
}

void CImportResultPage::SetParams (CImportParams &Params)
{
	m_pParams = &Params;
}

void CImportResultPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportResultPage)
	DDX_Control(pDX, IDB_ERROR_HELP, m_btErrorHelp);
	DDX_Control(pDX, IDS_SUM_ERR_CNT, m_stSumErrCnt);
	DDX_Control(pDX, IDS_SUM_CNT, m_stSumCnt);
	DDX_Control(pDX, IDS_NEW_ERR_CNT, m_stNewErrCnt);
	DDX_Control(pDX, IDS_NEW_CNT, m_stNewCnt);
	DDX_Control(pDX, IDS_ACT_ERR_CNT, m_stActErrCnt);
	DDX_Control(pDX, IDS_ACT_CNT, m_stActCnt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportResultPage, CPropertyPage)
	//{{AFX_MSG_MAP(CImportResultPage)
	ON_BN_CLICKED(IDB_SHOW_PROTOKOLL, OnShowProtokoll)
	ON_BN_CLICKED(IDB_ERROR_HELP, OnErrorHelp)
	ON_COMMAND(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportResultPage message handlers

BOOL CImportResultPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT (NULL != m_pParams);

//	Ergebnisse ausgeben
	CString strBeenden;
	VERIFY (strBeenden.LoadString (IDS_BEENDEN));
	GetParent () -> SetFinishText (strBeenden);

//	Ergebnisse auch in Protokoll-Datei ausgeben
	m_pParams -> m_ReportFile.WriteString ("\n");

//	Import-Ergebnisse ausgeben
	char Buffer [30] = "";
	CString strTemp;

//	Anzahl geänderten Datensätze
	m_stActCnt.SetWindowText (ltoa (m_pParams->m_lUpdateCnt, Buffer, 10));
	AfxFormatString1 (strTemp, IDS_UPDATE_IMPORT_CNT, Buffer);
	m_pParams -> m_ReportFile.WriteString (strTemp);

//	Anzahl der neu importierten Datensätze
	m_stNewCnt.SetWindowText (ltoa (m_pParams->m_lAppendCnt, Buffer, 10));
	AfxFormatString1 (strTemp, IDS_NEW_IMPORT_CNT, Buffer);
	m_pParams -> m_ReportFile.WriteString (strTemp);

//	Anzahl der Fehler beim Ändern
	m_stActErrCnt.SetWindowText (ltoa (m_pParams->m_lUpdateErrCnt, Buffer, 10));
	AfxFormatString1 (strTemp, IDS_UPDATE_IMPORT_ERRCNT, Buffer);
	m_pParams -> m_ReportFile.WriteString (strTemp);

//	Anzahl der Fehler beim Anhängen	
	m_stNewErrCnt.SetWindowText (ltoa (m_pParams->m_lAppendErrCnt, Buffer, 10));
	AfxFormatString1 (strTemp, IDS_APPEND_IMPORT_ERRCNT, Buffer);
	m_pParams -> m_ReportFile.WriteString (strTemp);

//	Summe der fehlerfrei Importierten
	m_stSumCnt.SetWindowText (ltoa (m_pParams->m_lUpdateCnt+m_pParams->m_lAppendCnt, Buffer, 10));
	AfxFormatString1 (strTemp, IDS_SUMME_IMPORT_CNT, Buffer);
	m_pParams -> m_ReportFile.WriteString (strTemp);

//	Summe der Fehlerhaften
	m_stSumErrCnt.SetWindowText (ltoa (m_pParams->m_lUpdateErrCnt+m_pParams->m_lAppendErrCnt, Buffer, 10));
	AfxFormatString1 (strTemp, IDS_SUMME_IMPORT_ERRCNT, Buffer);
	m_pParams -> m_ReportFile.WriteString (strTemp);
	m_pParams -> m_ReportFile.Close ();

	m_btErrorHelp.EnableWindow (!m_pParams -> m_strHelpFileName.IsEmpty ());

	BOOL retval = CPropertyPage::OnSetActive();

	// JG 981007
	// hier können die Änderungen nicht mehr rückgängig gemacht werden
	// die Transaktion ist bereits committed
#pragma MSG("JG hier noch einmal nachschlagen")
//	CPropertySheet * pParent = dynamic_cast<CPropertySheet*> (GetParent());
	CPropertySheet * pParent = (CPropertySheet*) (GetParent());
	ASSERT(pParent);

	if (NULL != pParent)
	{
		// Abbrechen Button disablen
		CWnd* pBtnCancel = pParent -> GetDlgItem(IDCANCEL);
		if (NULL != pBtnCancel)
			pBtnCancel-> EnableWindow(false);

		pParent -> SetWizardButtons(PSWIZB_NEXT | PSWIZB_FINISH);
	}

	return retval;
}

void CImportResultPage::OnShowProtokoll() 
{
	// TODO: Add your control notification handler code here
	ASSERT (NULL != m_pParams);
	CString strCommand;
	AfxFormatString1 (strCommand, IDS_EDIT_COMMAND, m_pParams->m_ReportFile.GetFilePath ());
	:: WinExec (strCommand, SW_SHOWNORMAL);	
}

void CImportResultPage::OnErrorHelp() 
{
	// TODO: Add your control notification handler code here
	ASSERT (NULL != m_pParams);
	ASSERT (!m_pParams -> m_strHelpFileName.IsEmpty ());

	::WinHelp(m_hWnd, m_pParams -> m_strHelpFileName, HELP_FINDER, 0);
}

void CImportResultPage :: OnHelp ()
{
	AfxGetApp () -> WinHelp (IDD+HelpDialogOffset);
}
