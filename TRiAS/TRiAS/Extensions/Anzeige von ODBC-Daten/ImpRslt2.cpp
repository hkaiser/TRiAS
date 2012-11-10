// ImpRslt2.cpp : implementation file
//

#include "pheader.h"
#include "odbcext.hr"


#include <hpp/waitcur.hpp>				// CWaitCursor
#include <hpp/getodbci.hpp>				// COdbcInfos
#include "database.hpp"				// CDataBaseExtc
#include "importpa.hpp"				// CImportParams

#include "ImpRslt2.hpp"				// zugeh. Header

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	externe Variablen
extern CImportParams *g_pCParams;
extern CStdioFile *g_pFile;				// Protokoll-Datei
#ifndef WIN32
	extern CPropertySheetExt *g_pSheet;
	extern char ErrFileName [_MAX_PATH];
#endif


/////////////////////////////////////////////////////////////////////////////
// CImportResult2 property page

IMPLEMENT_DYNCREATE(CImportResult2, CPropertyPage)

CImportResult2::CImportResult2() : CPropertyPage(CImportResult2::IDD)
{
	//{{AFX_DATA_INIT(CImportResult2)
	//}}AFX_DATA_INIT
}

CImportResult2::~CImportResult2()
{
}

void CImportResult2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportResult2)
	DDX_Control(pDX, IDT_IMP_RES_DOPP_TABLE, m_stDoppTable);
	DDX_Control(pDX, IDT_IMP_RES_DOPP_TRIAS, m_stDoppTrias);
	DDX_Control(pDX, IDT_IMP_RES_VNEW, m_stValNew);
	DDX_Control(pDX, IDT_IMP_RES_VERR, m_stValError);
	DDX_Control(pDX, IDT_IMP_RES_VDOPP_TRIAS, m_stValDoppTrias);
	DDX_Control(pDX, IDT_IMP_RES_VDOPP_TABLE, m_stValDoppTable);
	DDX_Control(pDX, IDT_IMP_RES_VDEL, m_stValDelete);
	DDX_Control(pDX, IDT_IMP_RES_VABGL, m_stValAbgleich);
	DDX_Control(pDX, IDT_IMP_RES_NEW, m_stNew);
	DDX_Control(pDX, IDT_IMP_RES_ERR, m_stError);
	DDX_Control(pDX, IDT_IMP_RES_DEL, m_stDelete);
	DDX_Control(pDX, IDT_IMP_RES_ABGL, m_stAbgleich);
	//}}AFX_DATA_MAP
}

#ifdef WIN32
BEGIN_MESSAGE_MAP(CImportResult2, CPropertyPage)
	//{{AFX_MSG_MAP(CImportResult2)
	ON_BN_CLICKED(IDB_IMP_RES_PROT, OnShowProtokoll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#else 
BEGIN_MESSAGE_MAP(CImportResult2, CPropertyPage)
	//{{AFX_MSG_MAP(CImportResult2)
	ON_BN_CLICKED(IDB_IMP_RES_PROT, OnShowProtokoll)
	ON_MESSAGE(IDM_SETFOCUS, OnSetFocusToControl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportResult2 message handlers
#ifdef WIN32
BOOL CImportResult2::OnSetActive() 
{
//	TODO: Add your specialized code here and/or call the base class
	GetResults ();

	return CPropertyPage::OnSetActive();
}	              
#endif
      
void CImportResult2::GetResults (void)
{      
	BOOL bRet = FALSE;
	TRY
	{		
		CString strHelp, strRes;
		if (!strHelp.LoadString (IDS_BEENDEN))
			AfxThrowUserException ();

#ifdef WIN32			
		GetParent () -> SetFinishText (strHelp);
#else 
		ASSERT (g_pSheet != NULL);
		g_pSheet -> SetFinishText (strHelp);
#endif		

		ASSERT (g_pCParams != NULL);

	//	Text in der Anzeige akt.
		if (!strHelp.LoadString (g_pCParams -> m_bAction ?
								 IDS_IMP_PUNKT_OBJEKTE : IDS_IMP_RECORDS))
			AfxThrowUserException ();
		AfxFormatString1 (strRes, IDS_IMP_RES_ABGL, strHelp);
		m_stAbgleich.SetWindowText (strRes);
		AfxFormatString1 (strRes, IDS_IMP_RES_NEW, strHelp);
		m_stNew.SetWindowText (strRes);

		if (g_pCParams -> m_bAction)
		{
			AfxFormatString1 (strRes, IDS_IMP_RES_DEL, strHelp);
			m_stDelete.SetWindowText (strRes);
		}
		AfxFormatString1 (strRes, IDS_IMP_RES_ERR, strHelp);
		m_stError.SetWindowText (strRes);

	//	Zähler ausgeben
		char Buffer [30] = "";
		m_stValDoppTable.SetWindowText (ltoa (g_pCParams -> m_lDoppTableCnt, Buffer, 10));
		m_stValDoppTrias.SetWindowText (ltoa (g_pCParams -> m_lDoppTriasCnt, Buffer, 10));
		m_stValNew.SetWindowText (ltoa (g_pCParams -> m_lNewCnt, Buffer, 10));
		if (g_pCParams -> m_bAction)
			m_stValDelete.SetWindowText (ltoa (g_pCParams -> m_lDelCnt, Buffer, 10));
		m_stValError.SetWindowText (ltoa (g_pCParams -> m_lErrImpCnt, Buffer, 10));
		m_stValAbgleich.SetWindowText (ltoa (g_pCParams -> m_lImpCnt, Buffer, 10));

	//	Fehler-Protokoll-Datei vervollst.
		ASSERT (g_pFile != NULL);

	//	Separator
		g_pFile -> WriteString ("\n");
		CString strOut;
	
	//	abgeglichene
		m_stAbgleich.GetWindowText (strOut);
		m_stValAbgleich.GetWindowText (strRes);
		g_pFile -> WriteString (strOut + strRes + "\n");

	//	neue
		m_stNew.GetWindowText (strOut);
		m_stValNew.GetWindowText (strRes);
		g_pFile -> WriteString (strOut + strRes + "\n");

	//	gelöschte
		if (g_pCParams -> m_bAction)
		{
			m_stDelete.GetWindowText (strOut);
			m_stValDelete.GetWindowText (strRes);
			g_pFile -> WriteString (strOut + strRes + "\n");
		}

	//	fehlerhafte
		m_stError.GetWindowText (strOut);
		m_stValError.GetWindowText (strRes);
		g_pFile -> WriteString (strOut + strRes + "\n");

	//	doppelte in Trias
		m_stDoppTrias.GetWindowText (strOut);
		m_stValDoppTrias.GetWindowText (strRes);
		g_pFile -> WriteString (strOut + strRes + "\n");

	//	doppelte in Tabelle
		m_stDoppTable.GetWindowText (strOut);
		m_stValDoppTable.GetWindowText (strRes);
		g_pFile -> WriteString (strOut + strRes + "\n");

		g_pFile -> Close ();

		bRet = TRUE;		// alles OK
	}
	CATCH (CMemoryException, me)
	{
		DEX_Error (RC_OdbcImport, EC_NOMEMORY);
	}
	AND_CATCH (CUserException, ue)
	{
		DEX_Error (RC_OdbcImport, EC_SYSERROR);
	}
	AND_CATCH (CFileException, fe)
	{
		// DEX_Error (RC_OdbcImport, EC_NOSPACE);
		fe -> ReportError ();
	}		
	END_CATCH

	if (!bRet)
		GetParent () -> EndDialog (IDCANCEL);
}

void CImportResult2::OnShowProtokoll() 
{
	// TODO: Add your control notification handler code here
	ASSERT (g_pFile != NULL);

	CString strCommand;
#ifdef WIN32	
	AfxFormatString1 (strCommand, IDS_EDIT_COMMAND, g_pFile -> GetFilePath ());
#else                                                                          
	AfxFormatString1 (strCommand, IDS_EDIT_COMMAND, ErrFileName);
#endif	
	:: WinExec (strCommand, SW_SHOWNORMAL);
}

BOOL CImportResult2::DestroyWindow() 
{
//	TODO: Add your specialized code here and/or call the base class
	DELETE_OBJ (g_pFile);
	
	return CPropertyPage::DestroyWindow();
}

#ifdef WIN32
BOOL CImportResult2::OnWizardFinish() 
{
	// TODO: Add your specialized code here and/or call the base class
	// DEX_PostRebuildSight();		// Sicht neu lesen

	return CPropertyPage::OnWizardFinish();
}           
#else		// WIN16
BOOL CImportResult2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetResults (); 
	
	PostMessage (IDM_SETFOCUS, 0, 0L);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}                     

LONG CImportResult2 :: OnSetFocusToControl (UINT, LONG)
{
	CWnd *pItemWnd = GetDlgItem (IDB_IMP_RES_PROT);
	if (pItemWnd)		
		GotoDlgCtrl (pItemWnd);
	return TRUE;		
}            
#endif		// WIN16

