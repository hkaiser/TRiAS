// CScriptDlg.cpp : implementation file
//
 
#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#if defined(WIN32)
#include "afxcmn.h"
#include "registry.hxx"
#endif // WIN32

#include <ctype.h>
#include <float.h>

#include <triastlb.h>

#include <ospace/std/string>

#include "macrguid.h"
#include "imacro.h" 
#include "imacorg.h"
                 
#include "conststr.h"

#include "enumscpt.h"
#include "strmimp.h"
#include "perstimp.h"
#include "macroimp.h"
#include "macro.h"
#include "scrptdlg.h"
#include "runscorg.h"

#include "runerr.h"

#ifndef WIN32
#include "waitcur.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define MAXTEXT	0x0000FFEFL		// maximale ScriptGröße

#define OS_NO_STREAM_SUPPORT

extern CRunScriptsOrg * GetRunningScripts();

extern SummitModul g_SummitModuls[];

HRESULT	OpenFile (bool fAutoStart, const CString & strFileName, LPSTR *ppText, ebHCODE *phCode);
bool ReadRegSettingsMacrosDirectory (char *pc, DWORD dwL);
HRESULT MakePathName (LPCSTR pPathName, LPSTR pNameToUse);
CString GetPathName (CString &rPath);
bool LoadString (CString & str, int IDS);
HRESULT LoadCode (int fh, ebFILEHEADER &rHead, ebHCODE *phCode, LPSTR *ppText);

extern HRESULT RunThread(CebThread & Thread, ebHSCRIPT hScript);

HRESULT		Fill(CWnd *pWnd, bool fCB, IScriptContainer * pISC);
HRESULT		RunThread(	IScriptContainer *pIScriptContainer, 
						CebInstance *pebInstance, 
						const CString& strMacroName,
						bool fAutoSt);
bool ResetEntryInfo(CebEntryInfo & EI);
bool SetEntryInfoLoadScript(CebEntryInfo & EI);
bool SetEntryInfoUnLoadScript(CebEntryInfo & EI);
HRESULT RunScript(CebEntryInfo & EI, ebHSCRIPT hScript, CRunErr *pRunErr, bool & fE, bool & fBreak, bool fAuto);

HRESULT ReadIniAutoLoadScript (char *pcMacroName, int iLen);
HRESULT	WriteIniAutoLoadScript (LPCSTR pcMacroName);

/////////////////////////////////////////////////////////////////////////////
// CScriptDlg dialog


CScriptDlg::CScriptDlg(	CWnd* pParent,          
						LPUNKNOWN pMacroScripts)
	: CDialog(CScriptDlg::IDD, pParent), m_strMacroName(' ', MAXSTRLENGTH),
		m_lbxMakroList()
{
	//{{AFX_DATA_INIT(CScriptDlg)
	//}}AFX_DATA_INIT
	ASSERT (pMacroScripts);
	
	CWaitCursor WC;

	m_pMacroScripts = pMacroScripts;
	m_pMacroScripts -> AddRef();
	
	m_pIScriptContainer = NULL;

	m_fEntf = false;
	m_fRun = false;
}

CScriptDlg::~CScriptDlg()
{
// Release() zum Konstruktor()
	m_pIScriptContainer  -> Release();
	m_pMacroScripts -> Release();
}


void CScriptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScriptDlg)
	DDX_Control(pDX, IDC_AUTOSTART, m_cckAutoStart);
	DDX_Control(pDX, IDC_ENTFERNEN, m_Entfernen);
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
	ON_BN_CLICKED(IDC_ENTFERNEN, OnEntfernen)
	ON_LBN_DBLCLK(IDC_MAKROLIST, OnDblclkMakrolist)
	ON_BN_CLICKED(IDC_AUTOSTART, OnAutoStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CScriptDlg message handlers

BOOL CScriptDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
HRESULT hr = m_pMacroScripts -> QueryInterface (IID_IScriptContainer, 
												(LPVOID *)&m_pIScriptContainer);
	if (FAILED(hr)) return false;  
	
	ASSERT(m_pIScriptContainer);

// Fuellen der Listbox		      
	if ( !FillList (m_pIScriptContainer)) return false;
		
	m_Edit.EnableWindow(FALSE);
	m_Cancel.EnableWindow(TRUE);
	m_Run.EnableWindow(FALSE);      
	m_Entfernen.EnableWindow (FALSE);

	m_eMacroName.SetFocus();

char AutoScript[_MAX_PATH]; 

	hr = ReadIniAutoLoadScript (AutoScript, _MAX_PATH);
	// AutoStartPath gesetzt
	if (S_OK == hr) {
		m_cckAutoStart.EnableWindow(false);
	}

return TRUE;
}

bool CScriptDlg::GetName(char *pc, int iLen)
{
	if (m_strMacroName.GetLength() > iLen) return false;	
	strcpy (pc, m_strMacroName); 
int iLength = m_strMacroName.GetLength();
	pc[iLength+1] = '\0';

return true;
}
                 
bool CScriptDlg::FillList (IScriptContainer *pIScriptContainer)
{
LPUNKNOWN pUnk = NULL;                                                
		
HRESULT hr = Fill((CWnd *)&m_lbxMakroList, 0, pIScriptContainer);
	if (FAILED(hr)) return false;  

return true;
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
CString strMacroName;

	m_eMacroName.GetWindowText (strMacroName);	

	if (!strMacroName.IsEmpty()) {
		if (1 == m_cckAutoStart.GetCheck()) {
			WriteIniAutoLoadScript (strMacroName);
		} else {
			WriteIniAutoLoadScript (g_cbNil);
		}
		m_Cancel.SetWindowText("&Schliessen");
	}
}

void CScriptDlg::OnRun()
{	                
HRESULT hr = NOERROR;

	m_eMacroName.GetWindowText (m_strMacroName);	
	if (m_strMacroName.IsEmpty()) return;

	hr = Stop (m_strMacroName);
	if (FAILED(hr)) return;

// Script angehalten, Dialog nicht verlassen	
	if (GetScode(hr) == S_OK) return;
	
	m_fRun = true;
	m_fEntf = false;

	CDialog::OnOK();	
}


void CScriptDlg::OnEntfernen()
{
// Entfernt Eintrag in Liste und schliesst Fenster                    

CString strMacroName;
	
	m_eMacroName.GetWindowText (strMacroName);	
	ASSERT(!strMacroName.IsEmpty());
	if (strMacroName.IsEmpty()) return;

HRESULT hr = m_pIScriptContainer -> DelScript (strMacroName);
	if (FAILED(hr)) return;
		
	m_fRun = false;
	m_fEntf = true;

	CDialog::OnOK();	
}

void CScriptDlg::OnDblclkMakrolist() 
{
	m_fEntf = false;
	m_fRun = false;

	m_eMacroName.GetWindowText(m_strMacroName);
	ASSERT(!m_strMacroName.IsEmpty());
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
	                                            
	CDialog::OnOK();	
}

HRESULT CScriptDlg::IsRunning(const CString & str)
{
ebHSCRIPT hScript = NULL;
return GetRunningScripts() -> Find(str, &hScript);
}

bool CScriptDlg::SetButtons()
{
CString strMacroName;

	m_eMacroName.GetWindowText (strMacroName);	

	if (strMacroName.GetLength() != 0) {
		m_Run.EnableWindow (true);
		m_Edit.EnableWindow (true);		
		m_Entfernen.EnableWindow (true); 
		m_cckAutoStart.EnableWindow(true);
	} else {
		m_Run.EnableWindow (false);
		m_Edit.EnableWindow (false);		
		m_Entfernen.EnableWindow (false); 
		m_cckAutoStart.EnableWindow(false);
	} 

// Prüfe, ob derzeitiges Script läuft
HRESULT hr = IsRunning(strMacroName);
	if (FAILED(hr)) return false;	
	
// Script läuft schon, nicht noch einmal ausführen
	if (S_OK == hr) {
		m_Run.SetWindowText("An&halten"); 
		m_Entfernen.EnableWindow (false);
		m_Edit.EnableWindow (false);
	} else {
		m_Run.SetWindowText("&Ausführen");
	}

DWORD dwInfo = 0;

// ausführbarer Code vorhanden ?
	hr = m_pIScriptContainer -> GetScriptInfo (strMacroName, &dwInfo);

	if (FAILED(hr) || S_FALSE == hr) {
		m_Run.EnableWindow (false);
		m_Entfernen.EnableWindow (false);
		m_cckAutoStart.EnableWindow(false);
	}
	
	if (!g_SummitModuls[RUNTIME].fIsInstalled || !(dwInfo & CC_CODE)) {
		m_Run.EnableWindow (false);
		m_cckAutoStart.EnableWindow(false);
	}

char AutoScript[_MAX_PATH]; 

	hr = ReadIniAutoLoadScript (AutoScript, _MAX_PATH);
	// AutoStartPath gesetzt
	if (S_OK == hr) {
		m_cckAutoStart.EnableWindow(false);
		return true;
	}
// kein Eintrag in INI,		wenn in INI, dann selektiert ?, Code vorhanden ?
	if (FAILED(hr) || (0 != strcmp (strMacroName, AutoScript)) || !(dwInfo & CC_CODE)) {
		m_cckAutoStart.SetCheck(0);
	} else {
		m_cckAutoStart.SetCheck(1);
	}

return true;
}

HRESULT CScriptDlg::Stop (const CString & str)
{
ebHSCRIPT hScript = NULL;
CebEntryInfo EI;
HRESULT hr = GetRunningScripts() -> Find(str, &hScript);

	if (GetScode(hr) != S_OK) return hr;

	hr = SetEntryInfoUnLoadScript(EI);		
	if (FAILED(hr)) return hr;

bool fRunTimeError = false, fBreak = true, fAuto = false;

	if (GetRunningScripts() -> GetAutoStart() == hScript)
		fAuto = true;		

	// UnLoadScript
	hr = RunScript(EI, hScript, NULL, fRunTimeError, fBreak, fAuto);
	if (FAILED(hr)) return hr;

	hr = GetRunningScripts() -> EndThreadRunning(hScript);
	if (FAILED(hr)) return hr;

	hr = GetRunningScripts() -> Delete(hScript);
	if (FAILED(hr)) return hr;
	
	m_Run.SetWindowText("&Ausführen"); 
	m_Entfernen.EnableWindow (true); 
	m_Edit.EnableWindow (true); 

return hr;
}

extern "C" void ebCALLBACK _XTENSN_EXPORT OnRuntimeError (	long lParam, 
															ebLPCTSTR lpMsg, 
															ebDWORD dwErrNum,
															ebWORD wLinNr, 
															ebWORD wCharPos, 
															ebLPCTSTR lpSource,
															ebLPCTSTR lpHelpFile, 
															ebDWORD dwHelpContext);

