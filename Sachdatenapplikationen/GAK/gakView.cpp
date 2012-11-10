// gakView.cpp : implementation of the CGakView class
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp

#include "gaksete.h"	// CDaoRecordsetExt
#include "gakSet.h"		// CGakSet
#include "abfset.h"		// CAbfSet
#include "documext.h"	// CDocumentExt
#include "gakDoc.h"		// CGakDocument
#include "childfrm.h"	// CChildFrame

#include "firmpage.h"	// CFirmaPage
#include "anfpage.h"	// CAnfallStelle
#include "EntsPage.h"	// CEntsPage
#include "branPage.h"	// CBranchPage
#include "PartPage.h"	// CPartnerPage
#include "erzsheet.h"	// CErzeugerSheet 		
#include "numedit.h"	// CErzNrEdit
#include "changenr.h"	// CChangeKeyDialog

// Crystal-Reports-Header
#include "peplus.h"
#include "crpe.h"

#include "recview.h"	// CDaoRecordViewExt	
#include "gakView.h"	// zugeh. Header

// JG
#include "AbfView.h"	// CAbfView

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	lokale Konstanten
// const short ErzPrintBufferSize = 4096;			// Puffergröße zum Drucken eines Formulars

//	externe Variablen
extern CAbfSet * g_pAbfSet;
extern CGakSet * g_pErzSet;

//	globale Funktionen
void StartErrorHelp ()
{
	try
	{
		CString strHelpFile;
		VERIFY (strHelpFile.LoadString (IDS_ERROR_HELP_FILE_NAME));
		::WinHelp(GetDesktopWindow(), strHelpFile, HELP_FINDER, 0);
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGakView

IMPLEMENT_DYNCREATE(CGakView, CDaoRecordViewExt)

BEGIN_MESSAGE_MAP(CGakView, CDaoRecordViewExt)
	//{{AFX_MSG_MAP(CGakView)
	ON_WM_CREATE()
	ON_COMMAND(IDM_DELETE_REKORD, OnDeleteRekord)
	ON_COMMAND(IDM_HELP_DATABSE_ERRORS, OnHelpDatabaseErrors)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Initialisierung
void CGakView::OnInitialUpdate()
{
	m_pSet = &GetDocument() -> m_gakSet;
	CDaoRecordViewExt::OnInitialUpdate();
}

#ifdef _DEBUG
CGakDoc* CGakView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGakDoc)));
	return (CGakDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGakView message handlers
int CGakView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDaoRecordViewExt::OnCreate (lpCreateStruct) == -1)
		return -1;
	
//	TODO: Add your specialized creation code here
	m_pSheet = new CErzeugerSheet (AFX_IDS_APP_TITLE, this);
	if (!m_pSheet->Create (this, WS_CHILD | WS_VISIBLE, 0))
	{
		DELETE_OBJ (m_pSheet);
		return -1;
	}

//	Fenster in AnfangsPosition bringen
	CRect rectClient;
	m_pSheet -> GetWindowRect (rectClient);
	m_pSheet -> SetWindowPos (NULL, 0, 0,
							  rectClient.Width(), rectClient.Height(),
							  SWP_NOZORDER | SWP_NOACTIVATE);
	return 0;
}

void CGakView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	return;
/*
//	TODO: Add your specialized code here and/or call the base class
	ASSERT (pDC != NULL);
	ASSERT_VALID (pDC);
	ASSERT (pInfo != NULL);

	try
	{
	//	Set prüfen
		ASSERT (m_pSet != NULL);
		ASSERT_VALID (m_pSet);
		CGakSet *pSet = (CGakSet *) m_pSet;
		ASSERT_VALID (pSet);

	//	Sheet prüfen
		ASSERT (m_pSheet != NULL);
		ASSERT_VALID (m_pSheet);
		CErzeugerSheet *pSheet = (CErzeugerSheet*) m_pSheet;
		ASSERT_VALID (pSheet);

	//	Formular erzeugen
		CGakApp *pApp = (CGakApp *) AfxGetApp ();
		ASSERT (pApp != NULL);
		ASSERT_VALID (pApp);
		CString strPage,
				strErstDat (m_pSet -> m_Erfassungsdatum.Format ((UINT) IDS_DATETIME_FORMAT)), 
			    strAendDat (m_pSet -> m_Aenderungsdatum.Format ((UINT) IDS_DATETIME_FORMAT));
		char *pPage = (char *) strPage.GetBuffer (ErzPrintBufferSize);
		/*
		strPage.Format (IDS_ERZEUGER_FORMULAR,pSet->m_Anfallstelle,pSet->m_Betriebsstaette,pSet->m_Strasse,
			pSet->m_Hausnummer,pSet->m_Ortsname,pSet->m_Gemeindekennzahl,pSet->m_Postleitzahl,
			pSet->m_Telefon,pSet->m_Telefax,(int)pSet->m_Beschaeftigtenanzahl,pSet->m_Firmenname,
			pSet->m_Firmenstrasse,pSet->m_Firmenhausnummer,pSet->m_Firmenortsname,pSet->m_Firmenpostleitzahl,
			pSet->m_Branchennummer,pSheet->GetBranchenName(),pSet->m_Ansprechpartner,pSet->m_Partnertelefon,pSet->m_Partnertelefax,
			pSet->m_Entsorgungsnummer,pSet->m_Entsorgungsart,strErstDat,strAendDat,pApp->UserName());
		CDaoRecordViewExt :: Print (pDC, pInfo, strPage);
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
*/
}

/////////////////////////////////////////////////////////////////////////////
// CGakView diagnostics
#ifdef _DEBUG
void CGakView::AssertValid() const
{
	CDaoRecordViewExt::AssertValid();
}

void CGakView::Dump(CDumpContext& dc) const
{
	CDaoRecordViewExt::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGakView database support
CDaoRecordset* CGakView::OnGetRecordset()
{
	ASSERT (NULL != m_pSet);
	ASSERT_VALID (m_pSet);
	return m_pSet;
}

/*
void CGakView::OnActivateView(BOOL bActivate, CView* pActView, CView* pDeactView) 
{
//	TODO: Add your specialized code here and/or call the base class

	if (bActivate && g_pAbfSet && !((CGakApp *) AfxGetApp ()) -> m_bResDlg &&
	   (m_pSet -> m_Nummer != g_pAbfSet -> m_Nummer) && IsWindowVisible () && !m_bOnSearch)
	{
		CBoolSema Sema(m_bOnSearch);
		SearchNummer (g_pAbfSet -> m_Nummer, TRUE);
	}

	CDaoRecordView::OnActivateView(bActivate, pActView, pDeactView);
}
*/

//	Erzeuger und zugeh. Abfälle löschen
void CGakView :: OnDeleteRekord()
{
	CString strDelText;
	AfxFormatString1 (strDelText, IDS_DELETE_ERZ, 
					((CDaoRecordsetExt *) OnGetRecordset())->m_Nummer);
	if (IDYES == MessageBox (strDelText, AfxGetAppName(), MB_ICONQUESTION | MB_YESNO))
		CDaoRecordViewExt::OnDeleteRekord(); 
}

void CGakView::OnHelpDatabaseErrors() 
{
	// TODO: Add your command handler code here
	StartErrorHelp ();
}

void CGakView::OnFilePrint() 
{
	// TODO: Add your command handler code here
	Print (FALSE);
}

void CGakView::OnFilePrintPreview() 
{
	// TODO: Add your command handler code here
	Print (TRUE);
}

void CGakView::Print (BOOL bToWindow)
{
	try
	{
		CString strReport;
		VERIFY (strReport.LoadString (IDS_ERZ_TABLE_NAME));
		CDaoRecordViewExt::Print (strReport, bToWindow);
	}
	catch (CMemoryException *me)
	{
		me -> ReportError ();
		me -> Delete ();
	}
}
// JG 981028
BOOL CGakView::OnMoveExt(UINT nIDMoveCommand)
{
	BOOL retval = CDaoRecordViewExt::OnMoveExt(nIDMoveCommand);
	Sync();
	return retval;
}

// JG 981028
void CGakView::Sync()
{
	ExtSync();
}

void CGakView::ExtSync()
{
	// Updaten des zugehörigen Abfallviews
	CGakApp * pApp = (CGakApp *) AfxGetApp();
	CAbfView * pAbfView = NULL;
	if (NULL != pApp)
		pAbfView = pApp->GetAbfallView();

	if (NULL == pAbfView)
	{
#ifdef _DEBUG
//		AfxMessageBox("Kann den Abfalldatensatz nicht aktualisieren");
		TRACE("Kann den Abfalldatensatz nicht aktualisieren");
#endif
		return;
	}

//	KK990714
	if ( g_pAbfSet)
//-----------------
// den Abfalldatensatz nachführen
	pAbfView->SearchNummer();
	return;
}
