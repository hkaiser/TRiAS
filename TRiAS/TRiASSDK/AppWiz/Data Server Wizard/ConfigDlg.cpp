// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"

#include "TRiASDBDS.h"
#include "TRiASDBDSAw.h"
#include "ConfigDlg.h"
#include "paint.h"
#include "options.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog

CConfigDlg::CConfigDlg()
	: CAppWizStepDlg(CConfigDlg::IDD)
{
	m_nSeqBitmap = IDB_READONLY;
	//{{AFX_DATA_INIT(CConfigDlg)
	m_Name = _T("");
	m_EditFileExt = _T("rit");
	m_AccessMode = 0;
	m_AccessType = ACCESSMODE_NOFILENODIR;
	m_fEmitSampleCode = TRUE;
	//}}AFX_DATA_INIT
	SetSeqBitmap();
}


void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	DDX_Control(pDX, IDC_FILEEXTENSION, m_FileExt);
	DDX_Text(pDX, IDC_DATASERVERNAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_FILEEXTENSION, m_EditFileExt);
	DDX_Radio(pDX, IDC_READONLY, m_AccessMode);
	DDX_Radio(pDX, IDC_FILEORIENTED, m_AccessType);
	DDX_Check(pDX, IDC_EMIT_SAMPLE_CODE, m_fEmitSampleCode);
	//}}AFX_DATA_MAP
}

// Base default title of custom AppWizard off of project name.  This is called
//  by CDialogChooser when the New Project dialog is dimissed with a
//  new project name.
void CConfigDlg::UpdateTitle(const CString& strRoot)
{
//	m_strTitle = _T("TRiASDB Dataserver Module ") + strRoot;
}


BEGIN_MESSAGE_MAP(CConfigDlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_COMMAND_EX(IDC_READONLY, OnClickedAccessMode)
	ON_WM_PAINT()
	ON_COMMAND_EX(IDC_READWRITE, OnClickedAccessMode)
	ON_WM_KILLFOCUS()
	ON_WM_CANCELMODE()
	ON_COMMAND_EX(IDC_FILEORIENTED, OnClickedAccessMode)
	ON_COMMAND_EX(IDC_FOLDERORIENTED, OnClickedAccessMode)
	ON_COMMAND_EX(IDC_NOFILEANDFOLDER, OnClickedAccessMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

#define STEPBMP_LEFT            8
#define STEPBMP_TOP             40
#define STEPBMP_WIDTH           179
#define STEPBMP_HEIGHT          235

// Set member variable to the bitmap ID corresponding to the currently
//  selected AppWizard sequence
void CConfigDlg::SetSeqBitmap()
{
	static UINT nBmps[] = { 
		IDB_READONLY_FILE, 
		IDB_READONLY_FOLDER, 
		IDB_READONLY, 
		IDB_READWRITE_FILE, 
		IDB_READWRITE_FOLDER, 
		IDB_READWRITE, 
	};

	ASSERT (ACCESSMODE_READONLY == m_AccessMode || ACCESSMODE_READWRITE == m_AccessMode);
	ASSERT (ACCESSTYPE_FILE == m_AccessType || ACCESSTYPE_DIRECTORY == m_AccessType || ACCESSMODE_NOFILENODIR == m_AccessType);
	m_nSeqBitmap = nBmps[m_AccessMode*3+m_AccessType];
}

// This handler allows us to dynamically change the bitmap as soon
//  as a new AppWizard sequence is selected.
void CConfigDlg::OnClickedAccessMode(UINT nID) 
{
	UpdateData(TRUE);

// Controls nachführen
	if (m_AccessType == ACCESSTYPE_FILE) {
		GetDlgItem(IDC_FILEEXTENSION) -> EnableWindow (TRUE);
		GetDlgItem(IDC_EDIT_FILEEXTENSION) -> EnableWindow (TRUE);
	} else {
		GetDlgItem(IDC_FILEEXTENSION) -> EnableWindow (FALSE);
		GetDlgItem(IDC_EDIT_FILEEXTENSION) -> EnableWindow (FALSE);
	}

// Invalidate the portion of this dialog on which we draw the picture
CRect rect(STEPBMP_LEFT, STEPBMP_TOP, STEPBMP_LEFT + STEPBMP_WIDTH, STEPBMP_TOP + STEPBMP_HEIGHT);

	SetSeqBitmap();
	RedrawWindow(&rect, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

void CConfigDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	PaintBackground(&dc, this);

	CDC dcMem;
	if (!dcMem.CreateCompatibleDC(&dc))
		return;

	// picture
	PaintBitmap(m_nSeqBitmap, STEPBMP_LEFT, STEPBMP_TOP, STEPBMP_WIDTH, STEPBMP_HEIGHT, &dc, &dcMem);
}


BOOL CConfigDlg::OnInitDialog() 
{
	CAppWizStepDlg::OnInitDialog();

	TRiASDBDSaw.m_Dictionary.Lookup(_T("root"), m_Name);
	_ASSERTE(m_Name.GetLength() > 0)	
	_toupper(m_Name[0]);

	GetDlgItem(IDC_FILEEXTENSION) -> EnableWindow (FALSE);
	GetDlgItem(IDC_EDIT_FILEEXTENSION) -> EnableWindow (FALSE);
	
	UpdateData (FALSE);
	return TRUE;  
}

// Set step-related template macros before dismissing
BOOL CConfigDlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;

	g_Options.m_AccessMode = m_AccessMode;
	g_Options.m_AccessType = m_AccessType;
	g_Options.m_FileExt = m_EditFileExt;
	_toupper(m_Name[0]);
	g_Options.m_Name = m_Name;
	g_Options.m_fEmitSampleCode = m_fEmitSampleCode;

	g_Options.DefineDlgMacros();
	return TRUE;
}
