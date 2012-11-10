// ShowOKSDlg.cpp : implementation file
//

#include "stdafx.h"
#include <fstream.h>
#include <comdef.h>
#include <afxpriv2.h>

#include "ShowOKS.h"

#define OS_NO_STREAM_SUPPORT
#include "ShowOKSDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowOKSDlg dialog

CShowOKSDlg::CShowOKSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowOKSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowOKSDlg)
	m_strGenText = _T("");
	m_strGenCode = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CShowOKSDlg::~CShowOKSDlg()
{
}

void CShowOKSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowOKSDlg)
	DDX_Control(pDX, IDC_OKSTREE, m_OKSList);
	DDX_Text(pDX, IDC_GEN_TEXT, m_strGenText);
	DDX_Text(pDX, IDC_GEN_CODE, m_strGenCode);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShowOKSDlg, CDialog)
	//{{AFX_MSG_MAP(CShowOKSDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPENFILE, OnOpenfile)
	ON_NOTIFY(TVN_SELCHANGED, IDC_OKSTREE, OnSelchangedOkstree)
	ON_NOTIFY_EX(TVN_CHECKSTATECHANGED, IDC_OKSTREE, OnCheckStateChangedOkstree)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SAVECOMPILED, OnSavecompiled)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// CShowOKSDlg message handlers

BOOL CShowOKSDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	if (!m_OKSList.InitControl()) 
		TRACE("Couldn't initialise tree control.\n");

	m_OKSList.SetFocus();
	return false;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CShowOKSDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CShowOKSDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CShowOKSDlg::OnOpenfile() 
{
	TRY {
	CString strFilter; strFilter.LoadString (IDS_OPENFILTER);
	CString strDefExt; strDefExt.LoadString (IDS_DEFEXT);
	CString strOkcExt; strOkcExt.LoadString (IDS_COMPILEDEXT);

	CFileDialog Dlg (true, strDefExt, NULL, OFN_EXPLORER|OFN_HIDEREADONLY, 
					 strFilter, this);

		if (IDOK == Dlg.DoModal()) {
		CString str = Dlg.GetFileName();

			if (strOkcExt == Dlg.GetFileExt()) {
			// als persistente Daten lesen
			IStoragePtr pIStg;
			DWORD dwMode = STGM_READ | STGM_SHARE_DENY_WRITE | STGM_DIRECT;
			HRESULT hr = StgOpenStorage (AfxTaskStringA2W(str), NULL, dwMode, NULL, 0L, &pIStg);

				if (SUCCEEDED(hr)) {
				IStreamPtr pIStm;

					dwMode = STGM_SHARE_EXCLUSIVE | STGM_READ;
					hr = pIStg -> OpenStream (AfxTaskStringA2W("PersistentOKS"), NULL, dwMode, 0L, &pIStm);
					if (SUCCEEDED(hr))
						m_OKSList.Load (pIStm);
					else
						AfxMessageBox ("Couldn't open stream");
				} else
					AfxMessageBox ("Couldn't open storage");
				
			} else {
			// als Textdatei einlesen
				m_OKSList.OpenAndParseFile (str);
			}
		}
	
	} CATCH(CMemoryException, e) {
		AfxMessageBox ("Out of memory");
	} END_CATCH;
}

void CShowOKSDlg::OnSavecompiled() 
{
	TRY {
	CString strFilter; strFilter.LoadString (IDS_SAVEFILTER);
	CString strOkcExt; strOkcExt.LoadString (IDS_COMPILEDEXT);

	CFileDialog Dlg (false, strOkcExt, NULL, OFN_EXPLORER|OFN_HIDEREADONLY, 
					 strFilter, this);

		if (IDOK == Dlg.DoModal()) {
		CString str = Dlg.GetFileName();

		// als persistente Daten lesen
		IStoragePtr pIStg;
		DWORD dwMode = STGM_READWRITE | STGM_SHARE_DENY_WRITE | STGM_TRANSACTED;
		HRESULT hr = StgOpenStorage (AfxTaskStringA2W(str), NULL, dwMode, NULL, 0L, &pIStg);

			if (FAILED(hr)) {
				dwMode |= STGM_CREATE;
				hr = StgCreateDocfile(AfxTaskStringA2W(str), dwMode, 0L, &pIStg);
			}
			if (SUCCEEDED(hr)) {
			IStreamPtr pIStm;

				dwMode = STGM_SHARE_EXCLUSIVE | STGM_READWRITE | STGM_CREATE;
				hr = pIStg -> CreateStream (AfxTaskStringA2W("PersistentOKS"), dwMode, 0L, 0L, &pIStm);
				if (SUCCEEDED(hr)) {
					if (SUCCEEDED(m_OKSList.Save (pIStm, TRUE)))
						pIStg -> Commit (STGC_DEFAULT);
				} else
					AfxMessageBox ("Couldn't open stream");
			} else
				AfxMessageBox ("Couldn't open storage");
		}
	
	} CATCH(CMemoryException, e) {
		AfxMessageBox ("Out of memory");
	} END_CATCH;
}

void CShowOKSDlg::OnSelchangedOkstree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateText();
	*pResult = 0;
}

BOOL CShowOKSDlg::OnCheckStateChangedOkstree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateText();
	*pResult = 0;
	return FALSE;	// continue processing
}

void CShowOKSDlg::UpdateText (void)
{
HTREEITEM hItem = m_OKSList.GetSelectedItem();

	if (NULL != hItem) {
	os_string strText = m_OKSList.GetFullText();
	os_string strCode = m_OKSList.GetCodeConverted();

		m_strGenText = strText.c_str();		
		m_strGenCode = strCode.c_str();
		UpdateData (false);
	}
}
	
