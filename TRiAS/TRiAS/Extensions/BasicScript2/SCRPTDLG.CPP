// CScriptDlg.cpp : implementation file
//
 
#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#include <iobjman.h>

#if defined(WIN32)
#include <afxcmn.h>
#include <registrx.hxx>
#endif // WIN32

#include <ctype.h>
#include <float.h>
#include <new>

#include <triastlb.h>

#include "macrguid.h"
#include "iscrprop.h"
                 
#include "conststr.h"
#include "projscr.h"
#include "macro.h"
#include "strinfo.h"
#include "scrptdlg.h"
#include "runscorg.h"
#include "relscrpt.h"
#include "runerr.h"
#include "runebobs.h"
#include "debfdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MAXTEXT	0x0000FFEFL		// maximale ScriptGröße

#define OS_NO_STREAM_SUPPORT

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

DefineEnumerator2(os_wstring, IID_IEnumos_wstring);
DefineSmartEnumerator2(os_wstring, IID_IEnumos_wstring);

extern CRunningObjectsHelper * GetRunningObjectsHelper(void);
extern SummitModul g_SummitModuls[];

////////////////////////////////////////////////////////////////////////////
// Deklaration externer globaler Funktionen
// global: wird mehrmals genutzt
UINT FileDialog (LPCSTR pcPath, CWnd *pParent, CString & strFileName, BOOL fOpen = true, LPCSTR lpcstr = NULL) ;
BOOL LoadString(CString & str, int IDS);
BOOL SetEntryInfoUnLoadScript(CebEntryInfo & EI);
CString GetFileName (CString &rPath, BOOL fExt);

HRESULT ReadIniAutoLoadScript (char *pcMacroName, int iLen);
HRESULT	WriteIniAutoLoadScript (LPCSTR pcMacroName);
BOOL	SaveRegSettingsAutoLoadFile (LPCSTR pc);
BOOL	ReadRegSettingsAutoLoadFile (LPSTR pc, DWORD dwL);
BOOL	ReadRegSettingsLastOpenFile(char *pc, DWORD dwL);
BOOL	SaveRegSettingsLastOpenFile (LPCSTR pc);
CString GetPathName (LPCSTR pcPath);

/////////////////////////////////////////////////////////////////////////////
// CScriptDlg dialog
CScriptDlg* CScriptDlg::CreateInstance(CWnd* pParent, IObjectManagement *pIOM, IStreamInfo *pISI)
{
	if (!g_SummitModuls[COMPILER].fIsInstalled || !g_SummitModuls[RUNTIME].fIsInstalled)
		return NULL;

	CScriptDlg* pSD = NULL;
	
	try {
		pSD = new CScriptDlg(pParent, pIOM, pISI);
	}
	catch (bad_alloc) {
		AfxMessageBox(IDS_NOMEMORY);
		return NULL;
	}

	return pSD; 
}

CScriptDlg::CScriptDlg(CWnd* pParent, IObjectManagement *pIObjManagement, IStreamInfo *pISI)
	: CDialog(CScriptDlg::IDD, pParent), m_strMacroName(' ', MAXSTRLENGTH),
		m_lbxMakroList()
{
	//{{AFX_DATA_INIT(CScriptDlg)
	//}}AFX_DATA_INIT
	
	m_fAutoStart = false;
	m_fEntf = false;
	m_fRun = false;
	m_fOpenFile = false;
	m_fRunFile = false;

	ASSERT(pIObjManagement);
	m_pIObjManagement = pIObjManagement;
	m_pIObjManagement -> AddRef();

	ASSERT(pISI);
	m_pIObjInfo = pISI;
	m_pIObjInfo -> AddRef();
}

CScriptDlg::~CScriptDlg()
{
	m_pIObjManagement -> Release();
	m_pIObjManagement = NULL;

	m_pIObjInfo -> Release();
	m_pIObjInfo = NULL;
}


void CScriptDlg::DoDataExchange(CDataExchange* pDX)
{ 
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScriptDlg)
	DDX_Control(pDX, IDC_AUTOSTART, m_cckAutoStart);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Control(pDX, IDC_RUN, m_Run);
	DDX_Control(pDX, IDOK, m_Edit);
	DDX_Control(pDX, IDC_MAKROLIST, m_lbxMakroList);
	DDX_Control(pDX, IDC_MACRONAME, m_eMacroName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScriptDlg, CDialog)
	//{{AFX_MSG_MAP(CScriptDlg)
	ON_LBN_SELCHANGE(IDC_MAKROLIST, OnSelChangeMakrolist)
	ON_EN_CHANGE(IDC_MACRONAME, OnChangeMacroname)
	ON_BN_CLICKED(IDC_RUN, OnRun)
	ON_LBN_DBLCLK(IDC_MAKROLIST, OnDblclkMakrolist)
	ON_BN_CLICKED(IDC_AUTOSTART, OnAutoStart)
	ON_BN_CLICKED(IDC_OPENFILE, OnOpenfile)
	ON_BN_CLICKED(IDC_RUNFILE, OnRunfile)
	ON_BN_CLICKED(IDC_IMPORT, OnImport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CScriptDlg message handlers

BOOL CScriptDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
		
// Fuellen der Listbox		      
	HRESULT hr = FillListBox();
	if (FAILED(hr)) return false;
	m_eMacroName.SetFocus();
	SetButtons();

return TRUE;
}

BOOL CScriptDlg::GetName (LPSTR pc, int iLen)
{
	if (m_strMacroName.GetLength() > iLen) 
		return false;	
	strcpy (pc, m_strMacroName); 

int iLength = m_strMacroName.GetLength();

	pc[iLength] = '\0';
	return iLength > 0 ? true : false;
}
                 

void CScriptDlg::OnOK()
{
	m_eMacroName.GetWindowText(m_strMacroName);
// Nur Dialog verlassen , wenn Name angegeben
	if (m_strMacroName.IsEmpty()) return;                      

	char *pc = NULL;

	TRY {
		pc = m_strMacroName.GetBuffer(MAXSTRLENGTH);
	} CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return;
	} END_CATCH;
	 
	if (__isascii(*pc) && islower(*pc)) 
		*pc = toupper ((int)*pc); 
	                                            
	m_fEntf = false;
	m_fRun = false;
	
	CDialog::OnOK();
}

void CScriptDlg::OnSelChangeMakrolist()
{
	CString strMacroName;

	m_lbxMakroList.GetText (m_lbxMakroList.GetCurSel(), strMacroName);
	m_eMacroName.SetWindowText (strMacroName);	

	SetButtons();
}

void CScriptDlg::OnChangeMacroname()
{
	SetButtons();
}

void CScriptDlg::OnCancel()
{
	CDialog::OnCancel();
}


void CScriptDlg::OnAutoStart() 
{
	SetAutoStart();
}

HRESULT CScriptDlg::SetAutoStart()
{
	HRESULT hr = NOERROR;
	CString strMacroName;
	m_eMacroName.GetWindowText (strMacroName);	
	if (strMacroName.IsEmpty()) return E_FAIL;
	// Wenn schon Running
	char str[_MAX_PATH];
	ReadRegSettingsAutoLoadFile (str, _MAX_PATH);
	////////////////////////////////////////
	// Aus der REG Autoload-File lesen	
	if (1 == m_cckAutoStart.GetCheck() && SUCCEEDED(IsRunning(strMacroName))) 
	{// AutostartStorage gewählt und in INI oder REG schreiben
		// steht nicht in der Reg, REIN
		if (0 != stricmp(str, strMacroName) && !SaveRegSettingsAutoLoadFile (str))
			return E_FAIL;
	} 
	else if (SUCCEEDED(IsRunning(strMacroName)))
	{// AutostartStorage gewählt und aus INI oder REG entfernen
		// steht auch in der Reg, RAUS				
		if (0 == stricmp(str, strMacroName) && !SaveRegSettingsAutoLoadFile (g_cbNil))
			return E_FAIL;
	}
	if (FAILED(hr)) return hr;
	////////////////////////////////////////
	// Aus der INI Autoload-Projekt lesen	
	*str = '\0';
	hr = ReadIniAutoLoadScript (str, _MAX_PATH);
	// Autoload-intern	, RAUS aus INI						 steht in INI
	if (S_FALSE == hr && 0 == m_cckAutoStart.GetCheck() && 0 == stricmp(str, strMacroName))
		WriteIniAutoLoadScript (g_cbNil);
			// Soll in INI						// schon anderer in INI 
	else if (1 == m_cckAutoStart.GetCheck() && stricmp(str, strMacroName))
		WriteIniAutoLoadScript (strMacroName);
	// Schließen einstellen
	CString strClose; LoadString(strClose, IDS_CLOSE);
	m_Cancel.SetWindowText(strClose);
	return hr;
}

void CScriptDlg::OnRun()
{	
	HRESULT hr = Stop ();
	// Script angehalten ODER (angehalten UND kein UnLoad-Entry)
	if (S_OK == hr || (hr != BS_E_NOTFOUND && hr == BS_E_NOENTRY)) return;
	
	m_fRun = false;
	// Nicht anzuhalten, da nicht Running
	if (hr == BS_E_NOTFOUND)
		m_fRun = true;

	CDialog::OnOK();	
}

/*
void CScriptDlg::OnEntfernen()
{
// Entfernt Eintrag in Liste und schliesst Fenster                    

	CString strMacroName;
	
	m_eMacroName.GetWindowText (strMacroName);	
	ASSERT(!strMacroName.IsEmpty());
	if (strMacroName.IsEmpty()) return;

	USES_CONVERSION;

	HRESULT hr = m_pIObjManagement -> DelObject (A2OLE(strMacroName));
	if (FAILED(hr)) return;
		
	hr = m_pIObjInfo -> Set (A2OLE(strMacroName), 0);
	if (FAILED(hr)) return;

	m_fRun = false;
	m_fEntf = true;

	DEX_SetDirtyGeoDB(1);

	CDialog::OnOK();	
}
*/
void CScriptDlg::OnDblclkMakrolist() 
{
	CString str;

	m_eMacroName.GetWindowText(str);
	ASSERT(!str.IsEmpty());
	if (str.IsEmpty()) return;               

// Prüfe, ob derzeitiges Script läuft
	HRESULT hr = IsRunning(str);
	if (S_OK == hr || FAILED(hr)) return;
	
	m_fEntf = false;
	m_fRun = false;
		
	m_strMacroName = str;

	char *pc = NULL;
	try {
		pc = m_strMacroName.GetBuffer(MAXSTRLENGTH);
	} catch (bad_alloc) {
		AfxMessageBox (IDS_NOMEMORY);
		return;
	} 

	if (__isascii(*pc) && islower(*pc)) 
		*pc = toupper ((int)*pc); 
	                                            
	CDialog::OnOK();	
}

HRESULT CScriptDlg::FillListBox()
{
	ASSERT(m_pIObjManagement);
	ASSERT(m_pIObjInfo);

HRESULT hr = S_OK;

	USES_CONVERSION;
	try
	{
	WUnknown IU;

		THROW_FAILED_HRESULT(m_pIObjManagement -> EnumStrings(IU.ppi()));

	WEnumos_wstring IE(IU);
	os_wstring oswstr;
	CString str, strOld;

		if (!::LoadString (str, IDS_NEWSTREAMINFO)) _com_issue_error(E_OUTOFMEMORY);
		if (!::LoadString (strOld, IDS_STREAMINFOS)) _com_issue_error(E_OUTOFMEMORY);

		while (S_OK == IE -> Next(1, &oswstr, NULL)) 
		{
		LPSTR lpstr = OLE2A(oswstr.c_str());
		
			if (0 == _stricmp(str, lpstr) || 0 == _stricmp(strOld, lpstr)) 
				continue;

		DWORD dwInfo = 0;				
		
			hr = m_pIObjInfo -> Get(A2OLE(lpstr), &dwInfo);
			if (FAILED(hr)) continue;
		
		// nur Dateinamen und nicht gesamten Pfad in ListBox ???
			if (dwInfo & SUPERITEM)
				m_lbxMakroList.AddString(lpstr);
		}
	
	// RunningFiles zum Anhalten in ListBox füllen
	WRunningObject IRO;
	char cbBuffer[_MAX_PATH];
	
		while (S_OK == GetRunningObjectsHelper() -> FindNext(cbBuffer, _MAX_PATH, IRO.ppi())) 
		{
			if (S_OK == IRO -> CanAddString())
				m_lbxMakroList.AddString(cbBuffer);
		}
	}
	catch (_com_error &e)
	{
		return _COM_ERROR(e);
	}

	return S_OK;
}

HRESULT CScriptDlg::FindFileName(const CString & strLBName, CString & strPathName)
{	// Namen in der Listbox konvertieren, da nur Dateiname 
	// und nicht ganzer Pfad in der ListBox erscheint
	ASSERT(m_pIObjManagement);
	ASSERT(m_pIObjInfo);

	USES_CONVERSION;

	WUnknown IU;
	HRESULT hr = m_pIObjManagement -> EnumStrings(IU.ppi());

	if (SUCCEEDED(hr)) 
	{
		WEnumos_wstring IE(IU);
		os_wstring oswstr;

		while (S_OK == IE -> Next(1, &oswstr, NULL)) 
		{
			CString strFileName = OLE2A(oswstr.c_str());
			// nur Filenamen für Vergleich geben lassen
			CString str = GetFileName(strFileName, false);
			ASSERT(!str.IsEmpty());

			if (str == strLBName)
			{ // richtigen Namen gefunden, Kopieren
				strPathName = strFileName;
			}
		}
	}

	return hr;
}

HRESULT CScriptDlg::IsRunning(LPCSTR lpcstr)
{
	return GetRunningObjectsHelper() -> IsRunning(lpcstr);
}

HRESULT CScriptDlg::LinkScript()
{
	CString str; m_eMacroName.GetWindowText (str);	
	if (str.IsEmpty()) return E_FAIL;
	return GetRunningObjectsHelper() -> LinkScript(str, NULL, m_pIObjManagement);
}

HRESULT  CScriptDlg::SetButtons()
{
	USES_CONVERSION;

CString strMacroName;
CString strRunning; 
	
	VERIFY(::LoadString(strRunning, IDS_RUNNING));

	m_eMacroName.GetWindowText (strMacroName);	
	if (strMacroName.IsEmpty()) {
		m_Edit.EnableWindow (false);		
		
		m_Run.SetWindowText(strRunning); 
		m_Run.EnableWindow (false);

		return S_OK;
	}

	try	{
	///////////////////////////////////////
	// VorInitialisieren
		m_Run.EnableWindow (true);
	
		m_Run.SetWindowText(strRunning); 
		m_Edit.EnableWindow (true);		
		m_cckAutoStart.EnableWindow(true);
		m_cckAutoStart.SetCheck(0);			

	// Running ?, dann "Anhalten" einstellen, RAUS
		if (S_OK == GetRunningObjectsHelper() -> IsRunning(strMacroName)) {
		CString strStop; 
		
			VERIFY(::LoadString(strStop, IDS_STOP));
			m_Run.SetWindowText(strStop); 
			m_Run.EnableWindow (true);			// Anhalten erlauben
			m_Edit.EnableWindow (false);		// Editieren verbieten
		
		DWORD dw = 0;
		
			if (S_OK == GetRunningObjectsHelper() -> GetAutoStart(strMacroName, &dw) && 0 != dw)
				m_cckAutoStart.SetCheck(1);		// Autostart kenntlich machen
			else
				m_cckAutoStart.SetCheck(0);
		}
		else {
		// oder Objekt vorhanden ?
		WUnknown IU;

			HRESULT hr = m_pIObjManagement -> GetObject(A2OLE(strMacroName), IU.ppi());
			if (FAILED(hr))
			{// kein Object mit diesem Namen, Neues kreieren
				m_Run.EnableWindow (false);		// Running verbieten
				m_cckAutoStart.EnableWindow(false);
				return S_FALSE;	
			}
		
		DWORD dwInfo = 0;
		
			THROW_FAILED_HRESULT(m_pIObjInfo -> Get(A2OLE(strMacroName), &dwInfo)); 

		//////////////////////////////////
		// CODE ?
			if (!(dwInfo & CC_CODE)) {
				m_Run.EnableWindow (false);		// Running verbieten
			}

		//////////////////////////////////
		// TEXT ?
			if (!(dwInfo & CC_SCRIPT)) {
				m_Edit.EnableWindow (false);	// Editieren verbieten
			}

		char str[_MAX_PATH];

			if (S_FALSE == ReadIniAutoLoadScript (str, _MAX_PATH) && 0 == stricmp (str, strMacroName)) 
				m_cckAutoStart.SetCheck(1);		// Autostart kenntlich machen
			else
				m_cckAutoStart.SetCheck(0);
		}
	}
	catch (_com_error &e)
	{
		m_Run.EnableWindow (false);
		m_Edit.EnableWindow (false);		
		m_cckAutoStart.EnableWindow(false);
		m_cckAutoStart.SetCheck(0);			
		return _COM_ERROR(e);
	}

	return S_OK;
}

HRESULT CScriptDlg::Stop ()
{
	m_eMacroName.GetWindowText (m_strMacroName);	
	if (m_strMacroName.IsEmpty()) return E_FAIL;
	// Hier wird ein externes File ausgeführt
	if (S_OK == GetRunningObjectsHelper() -> CanAddString(m_strMacroName))
	{
		CString strSel;
		m_lbxMakroList.GetText(m_lbxMakroList.GetCurSel(), strSel);
		// Selektierter gleich EditBoxString
		if (m_strMacroName == strSel)
		{
			m_lbxMakroList.DeleteString(m_lbxMakroList.GetCurSel());
			m_eMacroName.SetWindowText ("");	
		}
	}
	HRESULT hr = GetRunningObjectsHelper() -> StopScript(m_strMacroName);	
	SetButtons();
	return hr;
}

void CScriptDlg::OnOpenfile() 
{
CString strMacroName;
char cbPath[_MAX_PATH];

	cbPath[0] = '\0';
	ReadRegSettingsLastOpenFile (cbPath, _MAX_PATH);

	if (0 == FileDialog (cbPath, this, strMacroName))
		return;// Cancel
	if (strMacroName.IsEmpty()) 
		return;
	
	SaveRegSettingsLastOpenFile(GetPathName (strMacroName));
	m_strMacroName = strMacroName;
	m_fOpenFile = true;
	
	CDialog::OnOK();	
}


void CScriptDlg::OnRunfile() 
{
CString strMacroName;
BOOL fAuto = false;
CString strRunning; 

	::LoadString(strRunning, IDS_RUNNINGWITHOUTUNDERSCORE);
	if (0 == OpenFileDialog (strMacroName, fAuto, strRunning))
		return ;// Cancel
	if (strMacroName.IsEmpty()) return;
	
	m_strMacroName = strMacroName;
	m_fRunFile = true;
	m_fAutoStart = fAuto;

	CDialog::OnOK();	
}

UINT CScriptDlg::OpenFileDialog (CString & strFileName, BOOL & fAuto, LPCSTR lpcstrCaption) 
{
CString strFilters; ::LoadString(strFilters, IDS_SAVEASFILTERS); 
CString strExt; ::LoadString(strExt, IDS_SCRIPTEXT); 

// Zusätzlichen Linkbutton einfügen
LPSTR lpTemplateName = MAKEINTRESOURCE(IDD_FILEAUTOSTART);
HINSTANCE hInst = AfxFindResourceHandle(lpTemplateName, RT_DIALOG);

	if (hInst == NULL) return 0;

DWORD dwFlags = OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_ENABLETEMPLATE|OFN_EXPLORER|OFN_LONGNAMES;

#if defined(OFN_ENABLESIZING)
	if (IsWin41() || (IsWin50() && IsWinNT())) {
		dwFlags |= OFN_ENABLESIZING;
#if defined(OFN_DONTADDTORECENT)
		dwFlags |= OFN_DONTADDTORECENT;
#endif // defined(OFN_DONTADDTORECENT)
	}
#endif // defined(OFN_ENABLESIZING)

CDebFileDialog SDlg (true, strExt, NULL, dwFlags, strFilters, this, lpcstrCaption);
char cbPath[_MAX_PATH];

	cbPath[0] = '\0';
	ReadRegSettingsLastOpenFile (cbPath, _MAX_PATH);
	if ('\0' != cbPath[0])
		SDlg.m_ofn.lpstrInitialDir = cbPath;
	else
		SDlg.m_ofn.lpstrInitialDir = NULL;

// ChildTemplate setzen
	SDlg.m_ofn.hInstance = hInst;
	SDlg.m_ofn.lpTemplateName = lpTemplateName;

	if (SDlg.DoModal() == IDOK) {
		strFileName = SDlg.GetPathName();
		fAuto = SDlg.GetAutoStart();
		SaveRegSettingsLastOpenFile(GetPathName (strFileName));
		return 1;
	}
	return 0;
}

UINT CScriptDlg::ImportFileDialog (CString & strFileName, LPCSTR lpcstrCaption) 
{
CString strFilters; ::LoadString(strFilters, IDS_SAVEASFILTERS); 
CString strExt; ::LoadString(strExt, IDS_SCRIPTEXT); 
DWORD dwFlags = OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_EXPLORER|OFN_LONGNAMES;

#if defined(OFN_ENABLESIZING)
	if (IsWin41() || (IsWin50() && IsWinNT())) {
		dwFlags |= OFN_ENABLESIZING;
#if defined(OFN_DONTADDTORECENT)
		dwFlags |= OFN_DONTADDTORECENT;
#endif // defined(OFN_DONTADDTORECENT)
	}
#endif // defined(OFN_ENABLESIZING)

CDebFileDialog SDlg (true, strExt, NULL, dwFlags, strFilters, this, lpcstrCaption);
char cbPath[_MAX_PATH];

	cbPath[0] = '\0';
	ReadRegSettingsLastOpenFile (cbPath, _MAX_PATH);
	if ('\0' != cbPath[0])
		SDlg.m_ofn.lpstrInitialDir = cbPath;
	else
		SDlg.m_ofn.lpstrInitialDir = NULL;

	if (SDlg.DoModal() == IDOK) {
		strFileName = SDlg.GetPathName();
		return 1;
	}
	return 0;
}

HRESULT CScriptDlg::ImportFileToStorage()
{
LPSTR *lplpstrRel = NULL;
LPSTR lpstrText = NULL;
ebHCODE hCode = NULL;
UINT uiCnt = 0;

LPSTR *lplpstrRelStream = NULL;
LPSTR lpstrTextStream = NULL;
ebHCODE hCodeStream = NULL;
UINT uiCntStream = 0;

HRESULT hr = NOERROR;

CComObject<CExternProjectScript> *pFile = NULL;
CComObject<CProjectScript> *pProjectScript = NULL;
		
// Welches File eigentlich ?
CString strMacroName;
CString strRunning; 

	LoadString(strRunning, IDS_IMPORT);
	if (0 == ImportFileDialog (strMacroName, strRunning))
		return S_FALSE;// Cancel

	try {
		if (strMacroName.IsEmpty()) _com_issue_error(E_FAIL);

	///////////////////////////////////////////////////////////////////////////////////////
	// FileObjektManager erzeugen
		pFile = new CComObject<CExternProjectScript>;
		if (NULL == pFile) _com_issue_error(E_POINTER);
		pFile -> AddRef();
		pFile -> Init(m_pIObjManagement, m_pIObjInfo, CLSID_FileScript);
		
		THROW_FAILED_HRESULT(pFile -> SetScriptName(strMacroName));		// Namen setzen
		THROW_FAILED_HRESULT(pFile -> Open(&lpstrText, &hCode, &lplpstrRel, uiCnt)); // File öffnen

	///////////////////////////////////////////////////////////////////////////////////////
	// StreamObjektManager erzeugen
		pProjectScript = new CComObject<CProjectScript>;
		if (NULL == pProjectScript) _com_issue_error(E_POINTER);
		pProjectScript -> AddRef();
		pProjectScript -> Init(m_pIObjManagement, m_pIObjInfo, CLSID_Script);
	
	// Streamnamen generieren
		strMacroName = GetFileName(strMacroName, false);
		ASSERT(!strMacroName.IsEmpty());
		if (strMacroName.IsEmpty()) _com_issue_error(E_FAIL);

		THROW_FAILED_HRESULT(pProjectScript -> SetScriptName(strMacroName));
		HRESULT hr = pProjectScript -> Open(&lpstrTextStream, &hCodeStream, &lplpstrRelStream, uiCntStream);// Stream erzeugen							
		if (FAILED(hr) || S_FALSE == hr) _com_issue_error(hr);// Stream schon vorhanden ?		

	///////////////////////////////////////////////////////////////////////////////////////
	// Alles OK, Wegspeichern
		THROW_FAILED_HRESULT(pProjectScript -> Save(lpstrText, hCode, NULL, 0, 0));

	// In Combo eintragen		
		m_lbxMakroList.AddString(strMacroName);
	} catch(_com_error& e) {
		hr = _COM_ERROR(e);
	} catch(bad_alloc) {
		hr = E_OUTOFMEMORY;
	}

	COTASKMEMFREE(lpstrText);
	COTASKMEMFREE(hCode);
	MEMFREE(lplpstrRel, uiCnt);

	COTASKMEMFREE(lpstrTextStream);
	COTASKMEMFREE(hCodeStream);
	MEMFREE(lplpstrRelStream, uiCntStream);

	if (pFile) { pFile -> Delete(); pFile = NULL; }
	if (pProjectScript) { pProjectScript -> Delete(); pProjectScript = NULL; }

	return hr;
}

void CScriptDlg::OnImport() 
{	
	ImportFileToStorage();
}
