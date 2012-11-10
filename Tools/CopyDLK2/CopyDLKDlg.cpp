// $Header: $ 
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 10.12.2002 16:51:8
//
// @doc
// @module CopyDLKDlg.cpp | Implementation of the <c CCopyDLKDlg> class

#include "stdafx.h"

#include <WinVersion.h>
#include <Com/MemoryHelper.h>

#include <ospace/std/set>
#include <ospace/file/path.h>

#include "boost/directory.h"

#include "CopyDLK2.h"
#include "CopyDLKDlg.h"
#include "DlgProxy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWinVersion g_Version;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyDLKDlg dialog

IMPLEMENT_DYNAMIC(CCopyDLKDlg, CDialog);

CCopyDLKDlg::CCopyDLKDlg(CWnd* pParent /*=NULL*/) :
	CDialog(CCopyDLKDlg::IDD, pParent),
	m_threadCopy (this, reinterpret_cast<LPARAM>(&m_CopyData)),
	m_fSkipExisting(false)
{
	//{{AFX_DATA_INIT(CCopyDLKDlg)
	m_strSourcePath = _T("");
	m_strDestPath = _T("");
	m_strPrompt = _T("");
	m_strFilesToCopy = _T("");
	m_strInventarFile = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;

	m_iMinRange = 0;
	m_iMaxRange = 100;

// vorhergehende Daten aus Registry lesen
    ReadDataFromRegistry();
}

CCopyDLKDlg::~CCopyDLKDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
		
// Daten wieder in Registry verewigen
    WriteDataToRegistry();
}

void CCopyDLKDlg::ReadDataFromRegistry()
{
CRegKey regKey;

    if (ERROR_SUCCESS == regKey.Open(HKEY_CURRENT_USER, "Software", KEY_READ) &&
        ERROR_SUCCESS == regKey.Open(regKey, REG_COMPANY_KEY, KEY_READ) &&
        ERROR_SUCCESS == regKey.Open(regKey, "Tools", KEY_READ) &&
        ERROR_SUCCESS == regKey.Open(regKey, "CopyDLK2", KEY_READ) &&
        ERROR_SUCCESS == regKey.Open(regKey, "Config", KEY_READ))
    {
    char cbBuffer[_MAX_PATH];
    ULONG ulLen = sizeof(cbBuffer);
    DWORD dwValue = 0;
        
        if (ERROR_SUCCESS == regKey.QueryStringValue("SourcePath", cbBuffer, &ulLen))
            m_strSourcePath = cbBuffer;
            
        ulLen = sizeof(cbBuffer);
        if (ERROR_SUCCESS == regKey.QueryStringValue("DestPath", cbBuffer, &ulLen))
            m_strDestPath = cbBuffer;
            
        ulLen = sizeof(cbBuffer);
        if (ERROR_SUCCESS == regKey.QueryStringValue("DlkList", cbBuffer, &ulLen))
            m_strFilesToCopy = cbBuffer;

        ulLen = sizeof(cbBuffer);
        if (ERROR_SUCCESS == regKey.QueryStringValue("Inventory", cbBuffer, &ulLen))
            m_strInventarFile = cbBuffer;

        if (ERROR_SUCCESS == regKey.QueryDWORDValue("SkipExisting", dwValue))
            m_fSkipExisting = dwValue ? true : false;
    }
}

void CCopyDLKDlg::WriteDataToRegistry()
{
CRegKey regKey;

    if (ERROR_SUCCESS == regKey.Open(HKEY_CURRENT_USER, "Software", KEY_READ) &&
        ERROR_SUCCESS == regKey.Create(regKey, REG_COMPANY_KEY) &&
        ERROR_SUCCESS == regKey.Create(regKey, "Tools") &&
        ERROR_SUCCESS == regKey.Create(regKey, "CopyDLK2") &&
        ERROR_SUCCESS == regKey.Create(regKey, "Config"))
    {
        if (!m_strSourcePath.IsEmpty())
            regKey.SetStringValue("SourcePath", m_strSourcePath);
        if (!m_strDestPath.IsEmpty())
            regKey.SetStringValue("DestPath", m_strDestPath);
        if (!m_strFilesToCopy.IsEmpty())
            regKey.SetStringValue("DlkList", m_strFilesToCopy);
        if (!m_strInventarFile.IsEmpty())
            regKey.SetStringValue("Inventory", m_strInventarFile);
        regKey.SetDWORDValue("SkipExisting", m_fSkipExisting ? 1 : 0);
    }
}

BOOL CCopyDLKDlg::LoadInventory(BOOL fUpdateData, CMapInventory &rmapInventory)
{
    if (!rmapInventory.LoadFromFile(m_strInventarFile)) {
    // Meldung anzeigen
    CString strCaption, strPrompt;
    
        strCaption.LoadString(IDS_CAPTION);
        strPrompt.Format(IDS_INVENTORYNOTLOADED, (char const *)m_strInventarFile);
        _ASSERTE(!strCaption.IsEmpty() && !strPrompt.IsEmpty());
        MessageBox(strPrompt, strCaption);
    
    // UI richten
        m_strInventarFile = "";
        if (fUpdateData)
            UpdateData(FALSE);
        return FALSE;
    }
    return TRUE;
}

BOOL CCopyDLKDlg::LoadDlkList(BOOL fUpdateData)
{
    if (!m_DlkList.LoadFromFile(m_strFilesToCopy)) {
    // Meldung anzeigen
    CString strCaption, strPrompt;
    
        strCaption.LoadString(IDS_CAPTION);
        strPrompt.Format(IDS_DLKLISTNOTLOADED, (char const *)m_strFilesToCopy);
        _ASSERTE(!strCaption.IsEmpty() && !strPrompt.IsEmpty());
        MessageBox(strPrompt, strCaption);
    
    // UI richten
        m_strFilesToCopy = "";
        if (fUpdateData)
            UpdateData(FALSE);
        return FALSE;
    }
    return TRUE;
}

BOOL CCopyDLKDlg::LoadDestDir(BOOL fUpdateData, CDestList &rmapDestList)
{
    if (m_fSkipExisting && !rmapDestList.LoadFromDir(m_strDestPath)) {
    // Meldung anzeigen
    CString strCaption, strPrompt;
    
        strCaption.LoadString(IDS_CAPTION);
        strPrompt.Format(IDS_DESTLISTNOTLOADED, (char const *)m_strDestPath);
        _ASSERTE(!strCaption.IsEmpty() && !strPrompt.IsEmpty());
        MessageBox(strPrompt, strCaption);
    
    // UI richten
        m_strDestPath = "";
        if (fUpdateData)
            UpdateData(FALSE);
        return FALSE;
    }
    return TRUE;
}

BOOL CCopyDLKDlg::FillFilesToCopy(BOOL fUpdateData, DWORD dwUpdate)
{
// Tree aufräumen
    m_FilesToCopy.ResetCds();
    
// Geduldsanzeige
CWaitCursor Wait;

// Inventardatei einlesen  
    if ((dwUpdate & UPDATE_INVENTORY) && !LoadInventory(fUpdateData, m_Inventory))
        return FALSE;
        
// DLK-Liste einlesen
    if ((dwUpdate & UPDATE_DLKLIST) && !LoadDlkList(fUpdateData))
        return FALSE;

// ggf. Zielverzeichnis abklappern
    if (m_fSkipExisting) {
        if ((dwUpdate & UPDATE_DESTLIST) && !LoadDestDir(fUpdateData, m_DestList))
            return FALSE;
    }
    else {
        m_DestList.Reset();
    }
    
// Dlks abklappern
    if (m_Inventory.IsLoaded() && m_DlkList.IsLoaded()) {
    CDlkList::const_iterator it = m_DlkList.begin();
    CDlkList::const_iterator end = m_DlkList.end();

        for (/**/; it != end; ++it) {
        CMapInventory::const_iterator itInv = m_Inventory.find(*it);
        
            if (itInv != m_Inventory.end()) {
            // DLK gefunden
            HTREEITEM hItem = m_FilesToCopy.AddCdNode((*itInv).second);

            // jetzt Dlk in Liste einfügen
            CDestList::const_iterator cit = m_DestList.find(*it);
            long lCopied = FILETYPE_UNKNOWN;
            
                if (cit != m_DestList.end())
                    lCopied = (*cit).second & m_DestList.GetFileTypes();
                    
                m_FilesToCopy.AddDlkNode(hItem, *it, lCopied);
            }
            else {
            // DLK nicht gefunden
                m_FilesToCopy.AddDlkNodeNotFound(*it);
            }
        }
    }
    return TRUE;
}

void CCopyDLKDlg::AdjustOK()
{
    if (!m_strSourcePath.IsEmpty() && !m_strDestPath.IsEmpty() && 
        !m_strFilesToCopy.IsEmpty() && !m_strInventarFile.IsEmpty())
    {
        GetDlgItem(IDC_COPY)->EnableWindow(TRUE);
        return;
    }
    GetDlgItem(IDC_COPY)->EnableWindow(FALSE);
}

void CCopyDLKDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CCopyDLKDlg)
    DDX_Control(pDX, IDC_COPYPROGRESS, m_Status);
    DDX_Control(pDX, IDC_PARAMETERS, m_Parameters);
    DDX_Control(pDX, IDC_SOURCEDATA, m_SourceData);
    DDX_Text(pDX, IDC_PROMPT, m_strPrompt);
    DDX_Text(pDX, IDC_SOURCEDIR, m_strSourcePath);
    DDX_Text(pDX, IDC_DESTINATIONDIR, m_strDestPath);
    DDX_Text(pDX, IDC_FILESTOCOPYLIST, m_strFilesToCopy);
    DDX_Text(pDX, IDC_INVENTAR_FILE, m_strInventarFile);
    DDX_Control(pDX, IDC_COPY, m_pbAction);
    DDX_Control(pDX, IDCANCEL, m_pbClose);
    DDX_Control(pDX, IDC_SKIPEXISTING, m_cbSkipExisting);
    //}}AFX_DATA_MAP

    // Dateiabfrage
    DWORD dwFlags = 0;
    CString strCaptionInventar;
    CString strCaptionFileList;

    VERIFY(strCaptionInventar.LoadString(IDS_SELECTINVENTAR));
    VERIFY(strCaptionFileList.LoadString(IDS_SELECTFILELIST));

    if (!g_Version.IsWin40())
        dwFlags |= GF_OLD_STYLE_DIALOG;
    dwFlags |= GF_HIDEREADONLY;

    CString strFilterInventar; 
    CString strDefExtInventar;
    CString strFilterFileList; 
    CString strDefExtFileList;

    VERIFY(strFilterInventar.LoadString(IDS_FILTERINVENTAR));
    VERIFY(strDefExtInventar.LoadString(IDS_DEFEXTINVENTAR));
    VERIFY(strFilterFileList.LoadString(IDS_FILTERFILELIST));
    VERIFY(strDefExtFileList.LoadString(IDS_DEFEXTFILELIST));

    DDX_GetFilenameControl(pDX, IDC_INVENTAR_FILE, 
        m_sleInventar, dwFlags, 
        strCaptionInventar, strFilterInventar,
        strDefExtInventar, m_strInventarFile);
    DDX_GetFilenameControl(pDX, IDC_FILESTOCOPYLIST, 
        m_sleFileList, dwFlags, 
        strCaptionFileList, strFilterFileList,
        strDefExtFileList, m_strFilesToCopy);

    // Verzeichnisabfrage
    CString strCaptionDest;
    CString strCaptionSrc;

    VERIFY(strCaptionSrc.LoadString(IDS_SELECTSOURCEDIR));
    VERIFY(strCaptionDest.LoadString(IDS_SELECTDESTINATIONDIR));

    dwFlags = 0;
    if (!g_Version.IsWin40())
        dwFlags |= GFLDR_OLD_STYLE_DIALOG;

    DDX_GetFolderControl(pDX, IDC_SOURCEDIR, m_sleSourcePath, dwFlags, 
        strCaptionSrc,	m_strSourcePath);

    if (g_Version.IsWin50())
        dwFlags |= GFLDR_SAVEASDIALOG;
    DDX_GetFolderControl(pDX, IDC_DESTINATIONDIR, m_sleDestPath, dwFlags, 
        strCaptionDest,	m_strDestPath);
}

///////////////////////////////////////////////////////////////////////////////
//  
bool MustCopy (std::set<long> const &setDlkList, ospace::file::os_path &rName)
{
std::string base (rName.base());

	if (8 != base.size())
		return false;		// falsche Länge
	if (std::string::npos != base.find_first_not_of("0123456789"))
		return false;		// darf nur Zahlen im Namen haben

long lDlkName = strtoul(base.c_str(), NULL, 10);
std::set<long>::const_iterator it = setDlkList.find(lDlkName);

    return it != setDlkList.end();
}

void FindFilesFromPattern (std::set<long> const &setDlkList, 
    char const *pcPath, std::set<std::string> &rFiles, char const *pcPattern)
{
    using namespace boost::filesystem;

ospace::file::os_path filepath(pcPath);
dir_it end;

	for (dir_it it (string(filepath).c_str(), pcPattern); it != end; ++it) {
		if (get<is_directory>(it))
			continue;

	// Namenskonvention prüfen
	ospace::file::os_path file = *it;

        if (!MustCopy(setDlkList, file))
            continue;
            
	// Datei speichern
		if (filepath.has_directory())
			file.directory(std::string(filepath));
		else if (filepath.has_drive())
			file.drive(filepath.drive()[0]);
		else if (filepath.has_unc())
			file.unc(filepath.server(), filepath.share());

		rFiles.insert(std::string(file));
	}
}

///////////////////////////////////////////////////////////////////////////////
//  
const UINT WM_THREADCALLBACK = RegisterWindowMessage("WM_THREADCALLBACK");
const UINT WM_COPYDLKSTATUS = RegisterWindowMessage("WM_COPYDLKSTATUS");
const UINT WM_THREADERROR = RegisterWindowMessage("WM_THREADERROR");
const UINT WM_FILECOPIED = RegisterWindowMessage("WM_FILECOPIED");

BEGIN_MESSAGE_MAP(CCopyDLKDlg, CDialog)
	ON_MESSAGE(WM_DIRSELECTED, OnDirSelected)
	ON_MESSAGE(WM_FILESELECTED, OnFileSelected)
	//{{AFX_MSG_MAP(CCopyDLKDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_COPY, OnBnClickedCopy)
	ON_REGISTERED_MESSAGE(WM_THREADCALLBACK, OnThreadCallback)
	ON_REGISTERED_MESSAGE(WM_COPYDLKSTATUS, OnCopyDLKStatus)
	ON_REGISTERED_MESSAGE(WM_THREADERROR, OnCopyError)
	ON_REGISTERED_MESSAGE(WM_FILECOPIED, OnFileCopied)
	ON_BN_CLICKED(IDC_STOP, OnStop)
    ON_BN_CLICKED(IDC_CLIPBOARD, OnBnClickedClipboard)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_SKIPEXISTING, OnBnClickedSkipexisting)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyDLKDlg message handlers

BOOL CCopyDLKDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
    m_FilesToCopy.Init(this);
    m_cbSkipExisting.SetState(m_fSkipExisting ? 1 : 0);
    
// ListView mit allen Informationen füllen (if appropriate)
    FillFilesToCopy(FALSE);
    m_FilesToCopy.AdjustColumns();
            
	AdjustOK();	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCopyDLKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCopyDLKDlg::OnPaint() 
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
HCURSOR CCopyDLKDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CCopyDLKDlg::OnClose() 
{
	UpdateData(TRUE);
	if (!m_threadCopy.IsAlive()) {
	    if (CanExit())
		    CDialog::OnClose();
	}
	else
		OnStop();
}

void CCopyDLKDlg::OnOK() 
{
	UpdateData(TRUE);
	if (CanExit())
		CDialog::OnOK();
}

void CCopyDLKDlg::OnCancel() 
{
	UpdateData(TRUE);
	if (!m_threadCopy.IsAlive()) {
	    if (CanExit())
		    CDialog::OnCancel();
	}
	else
		OnStop();
}

void CCopyDLKDlg::OnStop() 
{
	if (IDYES == AfxMessageBox(IDS_ASKTOCANCEL, MB_YESNO)) {
		try {
			m_pbAction.EnableWindow(FALSE);
			m_threadCopy.Stop();
		}
		catch (CThreadException *pe) {
			if (!pe->GetErrorMsg().IsEmpty())
				pe->ReportError();
			pe->Delete();
		}
	}
}

BOOL CCopyDLKDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//  
LRESULT CCopyDLKDlg::OnDirSelected(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);
	AdjustOK();
	if (IDC_DESTINATIONDIR == wParam)
	    FillFilesToCopy(TRUE, UPDATE_DESTLIST);
    return TRUE;
}

LRESULT CCopyDLKDlg::OnFileSelected(WPARAM wParam, LPARAM lParam)
{
	UpdateData(TRUE);
	if (IDC_INVENTAR_FILE == wParam) {
        m_strFilesToCopy = "";
        UpdateData(FALSE);
        FillFilesToCopy(TRUE, UPDATE_INVENTORY);
	}
	else {
        FillFilesToCopy(TRUE, UPDATE_DLKLIST);
	}
	
	AdjustOK();
    return TRUE;
}

void CCopyDLKDlg::OnBnClickedCopy()
{
	try {
	CWaitCursor wait;
	
		m_pbClose.EnableWindow(FALSE);		// während Initialisierung

		UpdateData(TRUE);
		m_CopyData.m_strSourcePath = m_strSourcePath;
		m_CopyData.m_strDestPath = m_strDestPath;

    // zu kopierende Dateien bestimmen
        m_CopyData.m_setFilesToCopy.clear();
    
	    FindFilesFromPattern(m_DlkList, m_strSourcePath, m_CopyData.m_setFilesToCopy, "*.tif");
	    FindFilesFromPattern(m_DlkList, m_strSourcePath, m_CopyData.m_setFilesToCopy, "*.tfw");
	    FindFilesFromPattern(m_DlkList, m_strSourcePath, m_CopyData.m_setFilesToCopy, "*.x");

    // jetzt solls losgehen		
		m_threadCopy.Start();
	}
	catch (CThreadException *pe) {
		if (!pe->GetErrorMsg().IsEmpty())
			pe->ReportError();
		pe->Delete();
	}
}

LRESULT CCopyDLKDlg::OnThreadCallback(WPARAM wParam, LPARAM lParam)
{
	switch (wParam) {
	case CThread::CMD_INITIALIZE:
		if (!lParam) {
		// vorher
		    m_pbAction.EnableWindow(FALSE);
			m_sleSourcePath.EnableWindow(FALSE);
			m_sleDestPath.EnableWindow(FALSE);
			m_sleInventar.EnableWindow(FALSE);
			m_sleFileList.EnableWindow(FALSE);
		}
		break;

	case CThread::CMD_RUN:
		if (!lParam) {
		// vorher
		CString strCancel;

			VERIFY(strCancel.LoadString(IDS_CANCEL));
			m_pbAction.SetDlgCtrlID(IDC_STOP);
			m_pbAction.SetWindowText(strCancel);
			m_pbAction.EnableWindow(TRUE);
		}
		break;

	case CThread::CMD_STOP:
		if (lParam) {
		// nachher
		CString strCopy;

			VERIFY(strCopy.LoadString(IDS_COPY));
			m_pbAction.SetDlgCtrlID(IDC_COPY);
			m_pbAction.SetWindowText(strCopy);
			m_pbAction.EnableWindow(TRUE);

			m_sleSourcePath.EnableWindow(TRUE);
			m_sleDestPath.EnableWindow(TRUE);
			m_sleInventar.EnableWindow(TRUE);
			m_sleFileList.EnableWindow(TRUE);
			m_pbClose.EnableWindow(TRUE);

			m_Status.SetPos(m_iMinRange);
			m_strPrompt = "";
			UpdateData(FALSE);
		}
		break;
	}
	return TRUE;
}

LRESULT CCopyDLKDlg::OnCopyDLKStatus(WPARAM wParam, LPARAM lParam)
{
	switch (wParam) {
	case PBM_SETRANGE:
		m_iMinRange = LOWORD(lParam);
		m_iMaxRange = HIWORD(lParam);
		if (m_iMaxRange == m_iMinRange)
			m_iMaxRange = m_iMinRange+1;		// avoid division with zero
		m_Status.SetRange(m_iMinRange, m_iMaxRange);
		break;

	case PBM_SETPOS:
		_ASSERTE(m_iMaxRange-m_iMinRange != 0);
		m_strPrompt.Format(IDS_STATUSPROMPT, ((lParam-m_iMinRange)*100)/(m_iMaxRange-m_iMinRange));
		m_Status.SetPos(lParam);
		UpdateData(FALSE);
		break;
	}
	return TRUE;
}

LRESULT CCopyDLKDlg::OnCopyError(WPARAM wParam, LPARAM lParam)
{
    COM_TRY {
    // Fehlerdaten besorgen und in Fehlerliste löschen
    CCopyError err (m_CopyData.m_Errors.GetErrorEntry(wParam));     // throws hr

        m_CopyData.m_Errors.RemoveErrorEntry(wParam);
 
    // Fehlertext erzeugen       
    CString strError;
    LPVOID lpMsgBuf = NULL;

	    ::FormatMessage( 
		    FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		    FORMAT_MESSAGE_FROM_SYSTEM | 
		    FORMAT_MESSAGE_IGNORE_INSERTS,
		    NULL,
		    err.GetErrorCode(),
		    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		    (LPTSTR) &lpMsgBuf,
		    0,
		    NULL);

    CString strReason((LPCSTR)lpMsgBuf);

	    LocalFree(lpMsgBuf);
	    strReason.Replace('\n', ' ');

	    strError.Format (IDS_COPYERROR, err.GetFileName(), (LPCSTR)strReason, err.GetErrorCode());

    // Fehler am DlkNode anzeigen
        m_FilesToCopy.SetError(err.GetDlkName(), strError);
    
    } COM_CATCH_RETURN(FALSE);
	return TRUE;
}

LRESULT CCopyDLKDlg::OnFileCopied(WPARAM wParam, LPARAM lParam)
{
    COM_TRY {
        m_FilesToCopy.SetCopied(wParam, lParam);
    } COM_CATCH_RETURN(FALSE);
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//  Tree in Zwischenablage kopieren
void CCopyDLKDlg::OnBnClickedClipboard()
{
CWaitCursor wait;
std::string strResult = m_FilesToCopy.GetCdsAndDlks();

    if (OpenClipboard() && ::EmptyClipboard()) {
        COM_TRY {
        CGlobalMem Mem(strResult.size()+1);
        
            {
            CGlobalMem::Lock<char> lock (Mem);
            
                strcpy(lock, strResult.c_str());
            }
            ::SetClipboardData(CF_TEXT, Mem.Handle());
            
        } COM_CATCH_IGNORE;
        ::CloseClipboard();
    }
}

void CCopyDLKDlg::OnBnClickedSkipexisting()
{
    m_fSkipExisting = !m_fSkipExisting;
    FillFilesToCopy(TRUE, UPDATE_DESTLIST);
}


