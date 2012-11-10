// bscripta.cpp : implementation file

#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#if defined(WIN32)
#include "afxcmn.h"
#include "registry.hxx"
#endif // WIN32

#include <direct.h>
#include <ctype.h>
#include <float.h>

#include <oleguid.h>
#include <dirisole.h>
#include <triastlb.h>
#include <itriasap.h>

#include "conststr.h"
#include "toolbarx.h"

#include "macrguid.h"

#include "imacro.h"
#include "imacorg.h"

#include "enumscpt.h"

#include "bscripta.h"
#include "scrptdlg.h"
#include "mru.h"
#include "dummypar.h"
#include "fndrpld.h"
#ifndef WIN32
#include "waitcur.h"
#endif

#include "runerr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(WIN32)
#define __huge
#endif // WIN32

#define MAXTEXT	0x0000FFEFL		// maximale ScriptGröße

enum tagKindOfProcess {	TRACEINTO, 
						TRACEOVER, 
						GO 
} KindOfProcess;

extern SummitModul g_SummitModuls[];

static UINT NEAR uiWM_Replace = ::RegisterWindowMessage(FINDMSGSTRING);
static UINT NEAR uiWM_EndScript = ::RegisterWindowMessage("End_Script");

/////////////////////////////////////////////////////////////////////////////
// globale Funktionsdeklarationen
bool LoadString(CString & str, int IDS);
bool GetParam (CebThread &rThread, int iIndex, ebPARAM &rParam, LPVOID pParam, bool fModsPar=false);
CString GetPathName (CString &rPath);
bool IsRemoteDir(LPCSTR cbPath);

extern "C"
UINT ebCALLBACK _XTENSN_EXPORT CallbackFontDlgProc(HWND hWnd, UINT msg,  
							UINT uiParam, long lParam)
{        
static CBScriptDebug *pSD;
	     
	switch (msg) {                        
	case WM_INITDIALOG:              
		pSD = (CBScriptDebug *)((CHOOSEFONT *)lParam) -> lCustData; 
		pSD -> m_bFDOpen = true;
		break;

	case IDCANCEL:
		pSD -> m_pMenu -> EnableMenuItem (ID_DEBUG_FONTS, MF_ENABLED);
		pSD -> m_bFDOpen = false;
		break;
	}

return 0;
}       

/////////////////////////////////////////////////////////////////////////////
//												   Idle, Run, Susp, Hilight
static Accelerator AccTable[] = {
        { 'n' - 'a' + 1,	VKCTRL, ID_DEBUG_NEW,  true, false, true, true }, 
        { 'o' - 'a' + 1,	VKCTRL, ID_DEBUG_OPEN, true, false, true, true }, 
        { 's' - 'a' + 1,	VKCTRL, ID_DEBUG_SAVE, true, true, true, true }, 
        { 'f' - 'a' + 1,	VKCTRL, ID_DEBUG_FIND, true, true, true, true }, 
        { 'g' - 'a' + 1,	VKCTRL, ID_DEBUG_GOTOLINE, true, true, true, true },
        { 'r' - 'a' + 1,	VKCTRL, ID_DEBUG_REPLACE, true, false, false, true }, 
        { 'w' - 'a' + 1,	VKCTRL, ID_DEBUG_ADDWATCH, true, true, true, true }, 
        { 'u' - 'a' + 1,	VKCTRL, ID_DEBUG_DELETEWATCH, true, true, true, true }, 
        { VK_F3,     		ANYKEY, ID_DEBUG_FINDNEXT, true, true, true, true }, 
        { VK_F8,     		ANYKEY, ID_DEBUG_TRACEIN, true, true, true, true }, 
        { VK_F9,     		ANYKEY, ID_DEBUG_BREAKPOINT, true, true, true, true }, 
        { VK_F5,    		ANYKEY, ID_DEBUG_GO, true, true, true, true }, 
        { VK_F12,    		ANYKEY, ID_DEBUG_TRACEOVER, true, true, true, true }, 
        { VK_F1,    		ANYKEY, ID_DEBUG_GETHELPON, true, false, true, true }, 
        { '\0',      		0, 0, false, false, false, false },
};             

extern "C"
ebBOOL ebCALLBACK _XTENSN_EXPORT KeyboardFilterProc(HWND hWnd, UINT message, 
						WPARAM wParam,LPARAM lParam)
{
CebDebugger *pDebug = (CebDebugger *)GetProp (hWnd, g_cbKeyboardFilterData);

	if (NULL == pDebug) return false;
	
return CustomTranslateAccelerator (pDebug, AccTable, GetParent(hWnd), message, wParam ,lParam);
/* OK for debugger control to process message */
}

//////////////////////////////////////////////////////////////////////////////////////////////
// Funktionen zum Keyboardfilter
/////////////////////////////////////////////////////////////////////////////////////////////
BOOL ActivateMenuItem (HWND hWnd, WORD wID, bool fHilight)
{
HMENU hMenu = ::GetMenu (hWnd);
	
	if (fHilight) HiliteMenuItem (hWnd, hMenu, wID, MF_BYCOMMAND | MF_HILITE);
	PostMessage (hWnd, WM_COMMAND, wID, 0L);
	if (fHilight) HiliteMenuItem (hWnd, hMenu, wID, MF_BYCOMMAND | MF_UNHILITE);

return true;  //key combination found and processed
}

bool CustomTranslateAccelerator (CebDebugger *pDebug, Accelerator  *pAcc,
			HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
bool bIdle = false;
bool bSuspended = false;
bool bRunning = false;

	switch (pDebug -> GetState()) {
	case TS_IDLE:
		bIdle  = true;
		break;

	case TS_SUSPENDED:
		bSuspended = true;
		break;

	case TS_RUNNING:
		bRunning = true;
		break;

	default:
		ASSERT(false);
		break;
	}

int cChar = wParam;
int i = 0;

	if (WM_CHAR == message) {
		if (isascii(cChar)) cChar = tolower (cChar);

		while (pAcc[i].cChar != '\0') {
			if (pAcc[i].cChar == cChar)	{
			// key is in table
				switch (pAcc[i].cVirtKey) {
	           	case VKCTRL:  //is CONTROL down?
					if (GetKeyState(VK_CONTROL) & 0x8000) {
						if (bRunning == pAcc[i].fRunning ||
						    bSuspended == pAcc[i].fSuspended ||							 
						    bIdle == pAcc[i].fIdle) 
						{
							ActivateMenuItem (hWnd, pAcc[i].wID, pAcc[i].fHilight);
							return true;	/* do not pass this message ON */
						}
					}               
					break;

				case VKSHFT:  //is SHIFT do
					if (GetKeyState(VK_SHIFT) & 0x8000) {
						if (bRunning == pAcc[i].fRunning ||
						    bSuspended == pAcc[i].fSuspended ||							 
						    bIdle == pAcc[i].fIdle) 
						{
							ActivateMenuItem (hWnd, pAcc[i].wID, pAcc[i].fHilight);
							return true;	/* do not pass this message ON */
						}
					}
					break;

	            case VKALT:  //is CONTROL down?
					if ( HIWORD(lParam) & 0x2000 ) {
						if (bRunning == pAcc[i].fRunning ||
						    bSuspended == pAcc[i].fSuspended ||							 
						    bIdle == pAcc[i].fIdle) 
						{
							ActivateMenuItem (hWnd, pAcc[i].wID, pAcc[i].fHilight);
							return true;	/* do not pass this message ON */
						}
					}
					break;

				default:
					return false;
				} //end switch          
			}
			i++;
		} //end while loop		          
	}
	else if (message == WM_KEYDOWN) {
		while (pAcc[i].cChar != '\0') {
			if (pAcc[i].cChar == cChar) {
			// key is in table
				switch (pAcc[i].cVirtKey) {
				case ANYKEY:  
					if (bRunning == pAcc[i].fRunning ||
					    bSuspended == pAcc[i].fSuspended ||							 
					    bIdle == pAcc[i].fIdle) 
					{
						ActivateMenuItem (hWnd, pAcc[i].wID, pAcc[i].fHilight);
						return true;	/* do not pass this message ON */
					}
		       		break;

				default:
					return false;
				}
			}
			i++;
		}
	}

return false;    // key combination not found in accelerator table
}

// toolbar buttons - IDs are command buttons
#if defined(WIN32)
const int iString = 0;
static TBBUTTON BASED_CODE buttons[] =
{	// same order as in the bitmap 'toolbar.bmp'
	{ 6, ID_SEPARATOR, 0, TBSTYLE_SEP, 0L, iString, },

	{ 0, ID_DEBUG_CUT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, iString, },
	{ 1, ID_DEBUG_COPY, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, iString, },
	{ 2, ID_DEBUG_PASTE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, iString, },
	
	{ 6, ID_SEPARATOR, 0, TBSTYLE_SEP, 0L, iString, },

	{ 3, ID_DEBUG_UNDO, 0, TBSTYLE_BUTTON, 0L, iString, },

	{ 6, ID_SEPARATOR, 0, TBSTYLE_SEP, 0L, iString, },

	{ 4, ID_DEBUG_GO, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, iString, },
	{ 5, ID_DEBUG_SUSPEND, 0, TBSTYLE_BUTTON, 0L, iString, },
	
	{ 6, ID_SEPARATOR, 0, TBSTYLE_SEP, 0L, iString, },
	
	{ 6, ID_DEBUG_BREAKPOINT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, iString, },
	{ 7, ID_DEBUG_ADDWATCH, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, iString, },
	{ 8, ID_DEBUG_CALLSTACK, 0, TBSTYLE_BUTTON, 0L, iString, },
	{ 9, ID_DEBUG_TRACEIN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, iString, },
	{ 10, ID_DEBUG_TRACEOVER, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0L, iString, },
};
#else
static UINT buttons[] = 
{
	ID_DEBUG_CUT,
	ID_DEBUG_COPY,
	ID_DEBUG_PASTE,
	ID_SEPARATOR,
	ID_DEBUG_UNDO,
	ID_SEPARATOR,
	ID_DEBUG_GO,
	ID_DEBUG_SUSPEND,
	ID_SEPARATOR,
	ID_DEBUG_BREAKPOINT,
	ID_DEBUG_ADDWATCH,
	ID_DEBUG_CALLSTACK, 
	ID_DEBUG_TRACEIN,
	ID_DEBUG_TRACEOVER, 
};
#endif

static UINT BASED_CODE indicators[] =
{
	ID_STATUSBAR_PANE1,	// Textbereich
	ID_STATUSBAR_PANE2,	// x-Achsenwert
	ID_STATUSBAR_PANE3,	// Wert an sich
	ID_STATUSBAR_PANE4,	// y-Achsenwert
	ID_STATUSBAR_PANE5,	// Wert an sich
};


bool CMacroScriptExtension :: OnCloseDebugDlg (bool fTRiASClose)
{ 
bool fResult = true;

	if (m_pDebugWnd) 
	{
		HRESULT hr = NOERROR;
	// wenn Projekt vor dem Debugger geschlossen werden soll
		if (fTRiASClose)	
		{
	// Debugger nur automatisch schliessen, wenn nicht projektbezogene Macros geladen sind
			hr = m_pDebugWnd -> Close();
			if (FAILED(hr)) return false;
		}
	// Debugger will closed, if Projectmacros loaded
		if (S_FALSE == hr) return true;

		if (NULL != GetProp (m_pDebugWnd -> GetWindow(), g_cbKeyboardFilterData))
			RemoveProp (m_pDebugWnd -> GetWindow(), g_cbKeyboardFilterData);
	// intern DestroyWindow()
		delete m_pDebugWnd;
		m_pDebugWnd = NULL;
	}
	
return fResult;
}

int CMacroScriptExtension :: OnDebugDlg (LPUNKNOWN pMacroScripts, LPSTR pcName)
{								   
CWaitCursor WC;

// Debugger-DLL nicht installiert	
	if (!g_SummitModuls[DEBUGGER].fIsInstalled) return false;

	if (m_pDebugWnd != NULL) {
		m_pDebugWnd -> SendMessage (WM_CLOSE); 
		return true;
	}
	
	m_pDebugWnd = new CBScriptDebug (ebInst(), MWind(), pMacroScripts); 
	if (m_pDebugWnd == NULL) {
		AfxMessageBox (IDS_NOMEMORY);
		return false;     
	}

	m_pDebugWnd -> ShowWindow (SW_SHOWNORMAL);
	m_pDebugWnd -> UpdateWindow();
	m_pDebugWnd -> SetFocus();

	RegisterNotification (WM_CLOSEDEBUGGERDIALOG, false);

	if (pMacroScripts == NULL || pcName == NULL) return true;

	// Einlesen des Scripts 
return m_pDebugWnd -> OpenStream (pcName);
}

/////////////////////////////////////////////////////////////////////////////
// lokale Funktionen
LONG CBScriptDebug::OutPutNoMatch (CString & strFind)
{
	TRY {
	CString str; str.LoadString (IDS_TEXTNOTFOUND);
	CString strCap; strCap.LoadString (IDS_LONGCLASSNAME);
	CString strOut;

		strOut.Format (str, (LPCSTR)strFind); 
		MessageBox (strOut, strCap, MB_OK | MB_ICONINFORMATION);

	} CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return 0;
	} END_CATCH;
	
return 1;
}


CString CorrectExtension (CString &rPath, UINT uiResIDExt)
{
CString strNew, strDrive, strPath, strName, strExt;
	
	TRY {                                       
	char *pNew = strNew.GetBuffer (_MAX_PATH);
	char *pDrive = strDrive.GetBuffer (_MAX_DRIVE);
	char *pPath = strPath.GetBuffer (_MAX_PATH);
	char *pName = strName.GetBuffer (_MAX_FNAME);

		if (!::LoadString (strExt, uiResIDExt)) return  '\0';
	
		_splitpath (rPath, pDrive, pPath, pName, NULL);
		_makepath (pNew, pDrive, pPath, pName, strExt);

   	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return  '\0';
	}                  
	END_CATCH

	strNew.ReleaseBuffer();

return strNew;
}

static CString GetFileName (CString &rPath, bool fExt)
{

CString strName, strExt;
	TRY {                                       
	char *pName = strName.GetBuffer (_MAX_PATH);
	char *pExt = strExt.GetBuffer(_MAX_EXT);

		if(pExt == NULL || pName == NULL) return  '\0';   	
		
		_splitpath (rPath, NULL, NULL, pName, pExt);
		_makepath (pName, g_cbNil, g_cbNil, pName, fExt ? pExt : g_cbNil);
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return  '\0';
	}                  
	END_CATCH
	

	strName.ReleaseBuffer();

return strName;
}

CString GetPathName (CString &rPath)
{
CString strDrive, strPath, strName;
	
	TRY {                                       
	char *pPath = strPath.GetBuffer (_MAX_PATH);
	char *pDrive = strDrive.GetBuffer (_MAX_DRIVE);
	char *pName = strName.GetBuffer (_MAX_PATH);
		
		if(pPath == NULL || pDrive == NULL || pName == NULL)
			return  '\0';

   		_splitpath (rPath, pDrive, pPath, NULL, NULL);
		_makepath (pName, pDrive, pPath, g_cbNil, g_cbNil);
		
		if (*pPath) 
			pName[strlen(pName)-1] = '\0';	// abschließendes '\\' entfernen
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return  '\0';
	}                  
	END_CATCH
		
	
	strName.ReleaseBuffer();

return strName;
}

bool SaveSettingsWindow(CBScriptDebug *pDeb)
{
#ifdef WIN32        
	if (!IsWin32s()) {
		if (!SaveRegSettingsWindow(pDeb))
			return false;
	}
	else 
#endif       
	if (!SaveIniSettingsWindow ())
		return false;

return true;
}

bool SaveRegSettingsLastOpenFile (LPCSTR pc)
{ 
#if defined(WIN32)
CCurrentUser regBS (g_cbCfgKey);
// save in reg file...
	
	if ( ! regBS.SetSubSZ (g_cbLastFile, pc) ) return false;
#endif
return true;
}                                         

bool SaveRegSettingsWindow(CBScriptDebug *pDeb)
{ 
#if defined(WIN32)
RECT Rect;	                     
char cBuffer[80];

	if (pDeb -> IsIconic()) {
		return true;
	} else {
		
		pDeb -> GetWindowRect (&Rect);

		if (Rect.top < 0) Rect.top = 0;
		if (Rect.left < 0) Rect.left = 0;

	// window information
		wsprintf(cBuffer, g_cbWindowFmt,
			 Rect.bottom, Rect.top, Rect.left, Rect.right);
	}

CCurrentUser regBS (g_cbCfgKey);

	if ( ! regBS.SetSubSZ (g_cbWindow, cBuffer ) )	// save in reg file...
		return false;
#endif
return true;
}                                         

bool SaveIniSettingsWindow()
{ 	
RECT Rect;	                     
char buf[80];                 
HWND hWnd = ::GetActiveWindow();
	
	::GetWindowRect (hWnd, &Rect);
	

// window information
	wsprintf(buf, g_cbWindowFmt,
		 Rect.bottom, Rect.top, Rect.left, Rect.right);

// save in INI file...
	if (!WritePrivateProfileString (g_cbEditor, g_cbWindow, buf, g_cbLocalINI))
		return false;

return true;
}                                         

bool SaveSettingsFont( CBScriptDebug *pDeb)
{
#ifdef WIN32        
	if (!IsWin32s()) {
		if (!SaveRegSettingsFont (pDeb))
			return false;
	}
	else 
#endif       
	if (!SaveIniSettingsFont (pDeb))
		return false;

return true;
}

bool SaveRegSettingsFont (CBScriptDebug *pDeb)
{
#if defined(WIN32)
LOGFONT LF;
	
	LF.lfFaceName[0] = 0;
	
//font information
int iSize = GetObject (pDeb -> m_Debug.GetFont(), sizeof (LOGFONT), &LF);
	
	if (LF.lfFaceName[0] == 0) return false;

CCurrentUser regBS (g_cbCfgKey);
char cBuffer[80];

	wsprintf(cBuffer, g_cbFontFmt,
		 LF.lfHeight, LF.lfWidth, LF.lfWeight, LF.lfItalic, 
		 LF.lfFaceName);

// save in reg file...
	if (!regBS.SetSubSZ (g_cbFont, cBuffer))
		return false;
#endif

return true;
}

bool SaveIniSettingsFont( CBScriptDebug *pDeb)
{
LOGFONT LF;
char buf[80];
	
//font information
	GetObject (pDeb -> m_Debug.GetFont(), sizeof (LOGFONT), &LF);
	wsprintf(buf, g_cbFontFmt,
		LF.lfHeight, LF.lfWidth, LF.lfWeight, LF.lfItalic, 
		LF.lfFaceName);

// save in INI file...
	if ( !WritePrivateProfileString(g_cbEditor, g_cbFont, buf, g_cbLocalINI) )
		return false;

return true;
}


bool ReadSettingsFont(LPLOGFONT pLF)
{
	ASSERT (NULL != pLF);

#ifdef WIN32        
	if (!IsWin32s()) {
		if (!ReadRegSettingsFont (pLF))
			return false;    
	} else 
#endif
	{
		if (!ReadIniSettingsFont (pLF))
			return false;
	}

return true;
}

static bool ParseFontInfo (LPSTR pBuffer, LPLOGFONT pLF)
{
	if (pBuffer == NULL || *pBuffer == '\0') return false;  
	if (pLF == NULL) return false;

char *pStr = strtok (pBuffer, g_cbFmtDel);

	if (NULL == pStr) return false;
	pLF -> lfHeight = atoi (pStr);
	
	pStr = strtok (NULL, g_cbFmtDel);
	if (NULL == pStr) return false;
	pLF -> lfWidth = atoi (pStr);

	pStr = strtok (NULL, g_cbFmtDel);
	if (NULL == pStr) return false;
	pLF -> lfWeight = atoi (pStr);

	pStr = strtok (NULL, g_cbFmtDel);
	if (NULL == pStr) return false;
	pLF -> lfItalic = atoi (pStr) ? true : false;

	pStr = strtok (NULL, g_cbFmtDel);
	if (NULL == pStr) return false;
	strncpy (pLF -> lfFaceName, pStr, LF_FACESIZE);
	pLF -> lfFaceName[LF_FACESIZE-1] = '\0';

return true;
}

bool ReadRegSettingsFont (LPLOGFONT pLF)
{
#if defined(WIN32)
CString strBuffer;
LPTSTR pcBuffer = NULL;

	TRY {                                       
		pcBuffer = strBuffer.GetBuffer( MAXSTRLENGTH ); 
		if (pcBuffer == NULL) return false;
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return false;
	}                  
	END_CATCH
	
DWORD dwL = MAXSTRLENGTH;
CCurrentUser regBS (g_cbCfgKey);

	if (!regBS.GetSubSZ (g_cbFont, pcBuffer, dwL)) 
		return false;

return ParseFontInfo (pcBuffer, pLF);
#else
return false;
#endif
}

bool ReadIniSettingsFont(LPLOGFONT pLF )
{
CString strBuffer;
LPTSTR pcBuffer  = NULL;

	TRY {                                       
		pcBuffer = strBuffer.GetBuffer (MAXSTRLENGTH);         
		if (NULL == pcBuffer) return false;
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return false;
	}                  
	END_CATCH

	if (!GetPrivateProfileString (g_cbEditor, g_cbFont , g_cbNil, pcBuffer, 
				      MAXSTRLENGTH, g_cbLocalINI))
		return false;

return ParseFontInfo (pcBuffer, pLF);
}

bool ReadSettingsWindow (RECT *pRect)
{
	ASSERT (NULL != pRect);

#ifdef WIN32        
	if ( ! IsWin32s() ) {
		if ( ! ReadRegSettingsWindow(pRect) )
			return false;            
	}
	else 
#endif       
	if ( ! ReadIniSettingsWindow (pRect) )
		return false;

return true;
}


static bool ParseRectangleInfo (LPSTR pInfo, RECT *pRect)
{
	if (pInfo == NULL || *pInfo == '\0') return false;
	if(pRect == NULL) return false;

char *pStr = strtok (pInfo, g_cbFmtDel);

	if (NULL == pStr) return false;
	pRect -> bottom = atoi (pStr);
	
	pStr = strtok (NULL, g_cbFmtDel);
	if (NULL == pStr) return false;
	pRect -> top = atoi (pStr);
	
	pStr = strtok (NULL, g_cbFmtDel);
	if (NULL == pStr) return false;
	pRect -> left = atoi (pStr);
	                                                  
	pStr = strtok (NULL, g_cbFmtDel);
	if (NULL == pStr) return false;
	pRect -> right = atoi (pStr);               

return true;
}

bool ReadRegSettingsWindow (RECT *pRect)
{
#if defined(WIN32)
CString strBuffer;
LPTSTR pcBuffer = NULL;

	TRY {
		pcBuffer = strBuffer.GetBuffer( MAXSTRLENGTH ); 	
		if (pcBuffer == NULL) return false;
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return false;
	}                  
	END_CATCH

DWORD dwL = MAXSTRLENGTH;
CCurrentUser regBS (g_cbCfgKey);

	if (!regBS.GetSubSZ (g_cbWindow, pcBuffer, dwL))
		return false;

return ParseRectangleInfo (pcBuffer, pRect);
#else
return false;
#endif
}

bool ReadRegSettingsLastOpenFile(char *pc, DWORD dwL)
{
#if defined(WIN32)
CCurrentUser regBS (g_cbCfgKey);

	return regBS.GetSubSZ (g_cbLastFile, pc, dwL); 
#endif
}

bool ReadIniSettingsWindow (RECT *pRect )
{     
CString strBuffer;
LPTSTR pcBuffer = NULL;

	TRY {
		pcBuffer = strBuffer.GetBuffer( MAXSTRLENGTH ); 
		if (pcBuffer == NULL) return false;
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return false;
	}                  
	END_CATCH

	if (!GetPrivateProfileString (g_cbEditor, g_cbWindow , g_cbNil, pcBuffer, 
				      MAXSTRLENGTH, g_cbLocalINI))
		return false;

return ParseRectangleInfo (pcBuffer, pRect);
}

/////////////////////////////////////////////////////////////////////////////
// *** CBScriptDebug Dialog ***
/////////////////////////////////////////////////////////////////////////////

CBScriptDebug::CBScriptDebug(CebInstance &rInst, CWnd* pParent /*=NULL*/, LPUNKNOWN pMacroScripts)
			: CDialog(), m_rInst (rInst)
{	
	//{{AFX_DATA_INIT(CBScriptDebug)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	if (pMacroScripts) {
		m_fStorageManagement = true;
		m_pMacroScripts = pMacroScripts;
		m_pMacroScripts -> AddRef();		//	Release() in ~
	}
	else {
		m_fStorageManagement = false;
		m_pMacroScripts = NULL;
	}

// Script nicht laufend ?
	m_fBreak = true;
	m_fBreakSet = true;
	m_fOtherFunction = false;

	m_fAskSave = false;

	m_fLoadIsRun = true;
	m_fUnLoadIsRun = false;
	m_fMainIsRun = false;

	m_fRunModal = false;
	m_fRunError = false;
	
	m_fEditOnly = false;

	m_fRMBMenu = false;
	m_fDisplayFormat = false;

	m_pParent = pParent;
	
	m_fInitNew = false;	
	m_fSaveCompiled = false;
	
	m_bMatchCase = false;
	m_bUpDown = true;
	m_bMatchWholeWord = false;

	m_pMenu = NULL;

	m_pcFindText = NULL;
	m_strFindText.Empty();
	m_pcReplaceWithText = NULL;

// eigene Member initialisieren
	m_sCX = 0;
	m_sCY = 0; 

	m_fSendClose = false;
	m_fClose = false;
	m_fIsDirty = false;
	m_fEnabled = true;

	m_hWndSaved = NULL;
	m_lpSavedCode = NULL;

	m_pFRD = NULL;
	m_bFDOpen = false;
	m_hCode = NULL;

	m_uiMruID = 0;		// MenuID
	ResetParams();

#if _MFC_VER >= 0400
// modeless erzeugen, da Menu zusätzlich geladen wird, muß der MFC
// das Handle mitgeteilt werden, wo selbiges zu finden ist
HINSTANCE hCurrInst = AfxGetInstanceHandle();

	afxCurrentInstanceHandle = g_hInstance;
	Create (CBScriptDebug::IDD, pParent);
	afxCurrentInstanceHandle = hCurrInst;
#else
	Create (CBScriptDebug::IDD, pParent);
#endif 

// jetzt explizit an allen Stellen, wo der Dialog benötigt wird
//	ShowWindow (SW_SHOWNORMAL);
//	UpdateWindow();	

// DummyParent erzeugen (bleibt unsichtbar)
	m_pDummyParent = new CDummyParent (pParent);
	m_hIcon = NULL;
}

CBScriptDebug :: ~CBScriptDebug (void)
{    
// Immer einmal rufen, bei Fremdabbruch oder virtuellen Script anhalten !!!
	m_Debug.ClearAllBreakpoints();
	RunUnLoadScript(GO); 

// muß vor Zerstörung des Fensters geschehen
	if (!SaveSettingsFont (this) || !SaveSettingsWindow(this)) 
		AfxMessageBox (IDS_SETTINGSNOTSAVED);
		
// löscht Timer 
	KillTimer (ID_TIMER1);

// Font der Statusbar wieder zuruecksetzen	
	if (m_pSBOldFont) 
		m_wndStatusBar.SetFont (m_pSBOldFont, true);
	m_pSBOldFont = NULL;

	// Font in Debugger zurücksetzen
	if (m_hFontOld) 
		m_Debug.SetFont (m_hFontOld);		
	m_hFontOld = NULL;

	// Fenstericon zurücksetzen
	if (m_hIcon)
		SetIcon(m_hIcon, true);
	m_hIcon = NULL;

	// Keyboardfilterpproc zurücksetzen
	m_Debug.SetKeyboardFilter (NULL);
	if (NULL != GetProp (m_Debug.GetWindow(), g_cbKeyboardFilterData))
		RemoveProp (m_Debug.GetWindow(), g_cbKeyboardFilterData);

	// ParentWindow wieder zurückstellen		
	m_rInst.SetWindow (((CMacroScriptExtension *)g_pTE) -> hWnd());	

	if (m_pDummyParent) {
		m_pDummyParent -> DestroyWindow();
		delete m_pDummyParent;
	}
	m_pDummyParent = NULL;
	
// Release() zum Konstruktor()
	if (m_fStorageManagement) {
		if (m_pMacroScripts) m_pMacroScripts -> Release();	
	}
	m_pMacroScripts  = NULL;
	
	if (m_hCode) CoTaskMemFree (m_hCode);     
	m_hCode = NULL;

	DeleteMruMenu (m_pMRUMenu);
	m_pMRUMenu = NULL;
	
	if (m_pFRD)  delete( m_pFRD );
	m_pFRD = NULL;

//
// ***Fenster an sich zerstören ***
//
	VERIFY(DestroyWindow());
}       


void CBScriptDebug::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBScriptDebug)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBScriptDebug, CDialog)
	//{{AFX_MSG_MAP(CBScriptDebug)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_COMMAND(IDM_CLOSE, OnExit)
	ON_COMMAND(ID_DEBUG_CUT, OnDebugCut)
	ON_COMMAND(ID_DEBUG_COPY, OnDebugCopy)
	ON_COMMAND(ID_DEBUG_BREAKPOINT, OnDebugBreakpoint)
	ON_COMMAND(ID_DEBUG_CALLSTACK, OnDebugCallstack)
	ON_COMMAND(ID_DEBUG_DELETE, OnDebugDelete)
	ON_COMMAND(ID_DEBUG_ADDWATCH, OnDebugAddwatch)
	ON_COMMAND(ID_DEBUG_DELETEWATCH, OnDebugDeletewatch)
	ON_COMMAND(ID_DEBUG_MODIFYDLG, OnDebugModifyDlg)
	ON_COMMAND(ID_DEBUG_HEX, OnDebugHex)
	ON_COMMAND(ID_DEBUG_EDITDIALOG, OnDebugEditdialog)
	ON_COMMAND(ID_DEBUG_FIND, OnDebugFind)
	ON_COMMAND(ID_DEBUG_FINDNEXT, OnDebugFindnext)
	ON_COMMAND(ID_DEBUG_FONTS, OnDebugFonts)
	ON_COMMAND(ID_DEBUG_GO, OnDebugGo)
	ON_COMMAND(ID_DEBUG_GOTOLINE, OnDebugGotoline)
	ON_COMMAND(ID_DEBUG_NEWDIALOG, OnDebugNewdialog)
	ON_COMMAND(ID_DEBUG_PASTE, OnDebugPaste)
	ON_COMMAND(ID_DEBUG_RECORDING, OnDebugRecording)
	ON_COMMAND(ID_DEBUG_REPLACE, OnDebugReplace)
	ON_COMMAND(ID_DEBUG_SUSPEND, OnDebugSuspend)
	ON_COMMAND(ID_DEBUG_SYNTAX, OnDebugSyntax)
	ON_COMMAND(ID_DEBUG_TRACEIN, OnDebugTracein)
	ON_COMMAND(ID_DEBUG_TRACEOVER, OnDebugTraceover)
	ON_COMMAND(ID_DEBUG_UNDO, OnDebugUndo)
	ON_WM_INITMENU()
	ON_WM_MENUSELECT()	
	ON_WM_SETFOCUS()                                      
	ON_COMMAND(ID_DEBUG_NEW, OnDebugNew)
	ON_COMMAND(ID_DEBUG_OPEN, OnDebugOpen)
	ON_COMMAND(ID_DEBUG_SAVE, OnDebugSave)
	ON_COMMAND(ID_DEBUG_SAVETEXT, OnDebugSaveText)
	ON_COMMAND(ID_DEBUG_SAVEAS, OnDebugSaveas)
	ON_COMMAND(ID_DEBUG_GETHELPON, OnDebugGetHelpOn)	
	ON_COMMAND(ID_DEBUG_EDITORHELP, OnDebugEditorHelp)	
	ON_COMMAND(ID_DEBUG_TRIASHELP, OnDebugTriasHelp)	
	ON_REGISTERED_MESSAGE(uiWM_Replace, OnCallbackFindReplace)
	ON_REGISTERED_MESSAGE(uiWM_EndScript, OnEndScript)
	ON_WM_TIMER()	
	ON_COMMAND(ID_DEBUG_IMPORT, OnDebugOpen)
	ON_COMMAND(ID_DEBUG_EXPORT, OnDebugSaveas)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CBScriptDebug message handlers
int CBScriptDebug::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;		
	
// DebuggerControl erzeugen
HRESULT hr = CreateDebuggerControl();

	if (FAILED(hr)) {
		ASSERT(0); return -1;
	}

// StatusBar erzeugen
	hr = StatusBar();
	if (FAILED(hr)) {
		ASSERT(0); return -1;
	}

// ToolBar erzeugen
	hr = ToolBar();
	if (FAILED(hr)) {
		ASSERT(0); return -1;
	}

// MRU-List initialisieren
	hr = MRU();
	if(FAILED(hr)) {
		ASSERT(0); return -1;
	}

return 0;
}

// *** Hilfsfunktionen Create ***
//
HRESULT CBScriptDebug::ToolBar()
{
// CToolbar erzeugen
#if !defined(WIN32)

	if (!m_wndToolBar.Create (this) ||
	    !m_wndToolBar.LoadBitmap (IDR_DEBUGFRAME) ||
	    !m_wndToolBar.SetButtons (buttons, sizeof(buttons)/sizeof(UINT)))
	{
		TRACE("Failed to create toolbar\n");
		return ResultFromScode(E_FAIL);      // fail to create
	}

// Toolbar initialisieren
	m_wndToolBar.Disable (ID_DEBUG_SUSPEND);
	m_wndToolBar.Disable (ID_DEBUG_CALLSTACK);
	
#else

CRect rc (10, 10, 100, 100);
DWORD dwStyle = WS_CHILD | WS_VISIBLE | TBSTYLE_TOOLTIPS | CCS_ADJUSTABLE;

	if (!m_wndToolBar.Create (dwStyle, rc, this, 1)) {
		TRACE("Failed to create toolbar\n");
		return ResultFromScode(E_FAIL);      // fail to create
	}

	m_wndToolBar.AddBitmap (11, IDR_DEBUGFRAME);
	m_wndToolBar.AddButtons (sizeof(buttons)/sizeof(TBBUTTON), buttons);
	m_wndToolBar.AutoSize();

	if (!g_SummitModuls[RUNTIME].fIsInstalled) {
		m_wndToolBar.Disable (ID_DEBUG_SUSPEND);
		m_wndToolBar.Disable (ID_DEBUG_TRACEIN);
		m_wndToolBar.Disable (ID_DEBUG_TRACEOVER);
		m_wndToolBar.Disable (ID_DEBUG_GO);
		m_wndToolBar.Disable (ID_DEBUG_ADDWATCH);
		m_wndToolBar.Disable (ID_DEBUG_CALLSTACK);
		m_wndToolBar.Disable (ID_DEBUG_BREAKPOINT);
	}


#endif // !WIN32

#if defined(WIN32)

CRect rcTB;

	m_wndToolBar.GetWindowRect (rcTB);

CRect rcExtra (0, rcTB.Height()-1, 0, 0);		// ltrb

	RepositionBars (0, 0xffff, CBScriptDebug::ID_DEBUG, 
			CWnd::reposExtra, rcExtra);
#else

	RepositionBars (0, 0xffff, CBScriptDebug::ID_DEBUG);

#endif

return NOERROR;
}

HRESULT CBScriptDebug::StatusBar()
{
	if (!m_wndStatusBar.Create(this) ||
	    !m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return ResultFromScode(E_FAIL);      // fail to create
	}

	m_pSBOldFont = m_wndStatusBar.GetFont();

return NOERROR;
}

HRESULT CBScriptDebug::CreateDebuggerControl (void)
{
ebDWORD dwStyle = WS_CHILD|WS_VISIBLE|WS_BORDER;

	if (!g_SummitModuls[RUNTIME].fIsInstalled)
		dwStyle |= DS_NOWATCHWINDOW;

	m_Debug.SetParent (m_hWnd);
	m_Debug.SetStyle (dwStyle);
	m_Debug.SetId (CBScriptDebug::ID_DEBUG);
	m_Debug.SetInstance (g_hInstance);

	if (!m_Debug.Create()) {
		TRACE("Failed to create debugger control\n");
		return ResultFromScode(E_FAIL);      // fail to create
	}

	m_Debug.SetAutoCase	(true);
	m_Debug.SetAutoIndent(true);

// Extrabuffer für Threadbytes (z.B. ebThread_SetLong() für BREAK ?) 
	m_Debug.SetThreadExtra(sizeof(long));

// Entry "LoadScript()" setzen
// Scripttext laden
	if (false == m_fStorageManagement)
		if (!InitNewScript(false)) return E_FAIL;
	
	m_Debug.SetInstance (&m_rInst);
	m_Debug.EnableTextColors();
	m_Debug.EnableCtrlBreak();

	m_rInst.SetWindow (m_hWnd);		// ParentWindow setzen
			
// Timer fuer Events setzen:		
	m_Debug.SetKeyboardFilter (KeyboardFilterProc);
	m_Debug.SetNotificationProc(HandleDebuggerNotification);
	m_Debug.SetNotificationData((long)this);

// Daten für KeyboardFilterProc merken
	SetProp (m_Debug.GetWindow(), g_cbKeyboardFilterData, (HANDLE)&m_Debug);

return NOERROR;
}

HRESULT CBScriptDebug::MRU (void)
{
	if (m_fStorageManagement)
		m_uiMruID = ID_MRU_STORAGE-1;
	else
		m_uiMruID = ID_MRU_FILE-1;

	m_pMRUMenu = CreateMruMenu (NBMRUMENUSHOW, NBMRUMENU, MAXSIZEMRUITEM, m_uiMruID);
	if (m_pMRUMenu == NULL) return ResultFromScode(E_OUTOFMEMORY);
	
#if defined(WIN32)
	if (GetWin32Kind() == WIN32S)
		LoadMruInIni (m_pMRUMenu, g_cbOpenMRU, g_cbLocalINI);
	else
		LoadMruInReg (m_pMRUMenu, g_cbOpenMRUKey);
#else
	LoadMruInIni (m_pMRUMenu, g_cbOpenMRU, g_cbLocalINI);
#endif
	PlaceMenuMRUItem (m_pMRUMenu, ::GetSubMenu (::GetMenu(m_hWnd), 0), IDM_CLOSE); 

return NOERROR;
}

BOOL CBScriptDebug::OnInitDialog (void)
{
	CDialog::OnInitDialog();
	
CFont f;

#ifdef WIN32
	if (IsWin40())
		f.Attach ((HFONT)GetStockObject (DEFAULT_GUI_FONT));
	else 
#endif // WIN32
		f.Attach ((HFONT)GetStockObject (ANSI_VAR_FONT));

	m_wndStatusBar.SetFont (&f, true);
	f.Detach();

// StatusBar initialisieren
	m_wndStatusBar.SetPaneInfo (0, ID_STATUSBAR_PANE1, SBPS_STRETCH, 0);

// Font aus Registry/INI lesen
	{
	LOGFONT LF;

		memset (&LF, 0, sizeof(LOGFONT));
		if (ReadSettingsFont (&LF) ) {
			m_hFontOld = m_Debug.GetFont(); 
			m_Debug.SetFont (::CreateFontIndirect (&LF));
		} else 
			m_hFontOld = NULL;		
	}

RECT Rect;

	if (ReadSettingsWindow (&Rect)) {
		SetWindowPos (NULL, Rect.left, Rect.top, 
			Rect.right-Rect.left, -Rect.top+Rect.bottom, 
			SWP_NOZORDER|SWP_NOACTIVATE);
//		InvalidateRect (NULL, true);
//		UpdateWindow ();
	}
	
	m_hIcon = GetIcon(true);
	SetIcon(AfxGetApp() -> LoadIcon(IDR_MACRO), true);	

//	::SetFocus(m_Debug.GetWindow());

	SetTimer (ID_TIMER1, 100, NULL);

return false;  // return true  unless you set the focus to a control
}

void CBScriptDebug::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	m_sCX = cx;
	m_sCY = cy; 

#if defined(WIN32)
CRect rcTB;

	m_wndToolBar.AutoSize();
	m_wndToolBar.GetWindowRect (rcTB);

CRect rcExtra (0, rcTB.Height()-1, 0, 0);		// ltrb

	RepositionBars (0, 0xffff, CBScriptDebug::ID_DEBUG, 
			CWnd::reposExtra, rcExtra);
#else
	RepositionBars (0, 0xffff, CBScriptDebug::ID_DEBUG);
#endif
}

void CBScriptDebug::OnTimer( UINT nIDEvent )
{                                            
DWORD dwCursorPos = m_Debug.GetCursorPos();
CString str;

	str.Format (g_cbDezFmt, LOWORD(dwCursorPos) +1);
	m_wndStatusBar.SetPaneText (4, str, true);

	str.Format (g_cbDezFmt, HIWORD(dwCursorPos) +1);
	m_wndStatusBar.SetPaneText (2, str, true);

	if (m_fUnLoadIsRun)
		ebDebugger_SetReadOnly(m_Debug.GetWindow(), true);
	else
		ebDebugger_SetReadOnly(m_Debug.GetWindow(), false);
}

void CBScriptDebug::OnMenuSelect (UINT nItemID, UINT nFlags, HMENU hSysMenu)
{
	if (0xffff != nFlags && nFlags & MF_SYSMENU) 
		return;	// nicht unser Bier

// text fuer StatusBar 
CString str;

	TRY {                                       
		if (0xffff == nFlags && NULL == hSysMenu) {
			str.LoadString (ID_STATUSBAR_PANE1);	// Menu ausgeblendet
		} else if (nFlags & MF_POPUP) {
			str.LoadString (nItemID + IDS_POPUP0);
		} else if (nItemID > 0)
			str.LoadString (nItemID);
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return;
	}                  
	END_CATCH

	m_wndStatusBar.SetPaneText (0, str, true);

// und weiterreichen	
	CDialog::OnMenuSelect (nItemID, nFlags, hSysMenu);
}                                   

void CBScriptDebug::OnInitMenu(CMenu* pMenu) 
{
	CDialog::OnInitMenu(pMenu);

	m_wndStatusBar.SetPaneText (0, g_cbNil, true);
	
int iState = m_Debug.GetState();

// *** Undo ***
UINT uiEnabled = (iState == ES_IDLE && m_Debug.CanUndo() && (m_fBreakSet || m_fOtherFunction)) ? MF_ENABLED : MF_GRAYED;

	pMenu -> EnableMenuItem (ID_DEBUG_UNDO, uiEnabled);

// *** Find, Replace *** disabled if there allready is a Find/Replace-dialog
	uiEnabled = (m_pFRD == NULL) ? MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_FINDNEXT, uiEnabled);
	pMenu -> EnableMenuItem (ID_DEBUG_FIND, uiEnabled);

	uiEnabled = (m_pFRD == NULL && (m_fBreakSet || m_fOtherFunction)) ? MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_REPLACE, uiEnabled);

	uiEnabled = (m_bFDOpen == false) ? MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_FONTS, uiEnabled);

// *** Copy, Cut, Del *** enabled if there is a selection in the debugger control and if
// we are not executing
	uiEnabled = (iState == ES_IDLE && m_Debug.HasSelection()) ? MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_COPY, uiEnabled);

	uiEnabled = (iState == ES_IDLE && m_Debug.HasSelection() && (m_fBreakSet || m_fOtherFunction)) ? MF_ENABLED : MF_GRAYED;	
	pMenu -> EnableMenuItem (ID_DEBUG_CUT, uiEnabled);
	pMenu -> EnableMenuItem (ID_DEBUG_DELETE, uiEnabled);

	uiEnabled = (iState == ES_IDLE && ::IsClipboardFormatAvailable (CF_TEXT) && (m_fBreakSet || m_fOtherFunction)) ? MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_PASTE, uiEnabled);

// *** DialogEditor ***
	uiEnabled = (iState == ES_IDLE && m_Debug.IsDialogSelected() && g_SummitModuls[DLGEDIT].fIsInstalled) ? MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_EDITDIALOG, uiEnabled);
	
	uiEnabled = (iState == ES_IDLE && g_SummitModuls[DLGEDIT].fIsInstalled && (m_fBreakSet || m_fOtherFunction)) ? MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_NEWDIALOG, uiEnabled);
	
// *** Modifizierung des Menüs für Storage-verwaltung ***
// *** Datei öffnen, neu ... ***
CString strMenuText;
	
	if (!m_fRMBMenu && m_fStorageManagement && NULL == m_pMenu) 
	{
		if (!::LoadString (strMenuText, IDS_EXPORT)) return;
		pMenu -> ModifyMenu (ID_DEBUG_SAVEAS, MF_BYCOMMAND | MF_STRING,	
	 				ID_DEBUG_EXPORT, strMenuText);

		if (!::LoadString (strMenuText, IDS_IMPORT)) return;
	 	pMenu -> ModifyMenu (ID_DEBUG_OPEN, MF_BYCOMMAND | MF_STRING,	
	 				ID_DEBUG_IMPORT, strMenuText);
		
		if (!::LoadString (strMenuText, IDS_NEUESMACRO)) return;
	 	pMenu -> ModifyMenu (ID_DEBUG_NEW, MF_BYCOMMAND | MF_STRING,	
	 				ID_DEBUG_NEW, strMenuText);		

		if (!::LoadString (strMenuText, IDS_SAVETEXT)) return;
	 	(pMenu -> GetSubMenu(0)) -> InsertMenu (2, MF_BYPOSITION | MF_STRING,	
	 				ID_DEBUG_SAVETEXT, strMenuText);

	} 

	m_fRMBMenu = false;
	m_pMenu = pMenu;	// für Callback

	if (false == (m_fBreakSet || m_fOtherFunction)) {
		pMenu -> EnableMenuItem (ID_DEBUG_NEW, MF_GRAYED);
		pMenu -> EnableMenuItem (ID_DEBUG_IMPORT, MF_GRAYED);
		pMenu -> EnableMenuItem (ID_DEBUG_OPEN, MF_GRAYED);
	} else {
		pMenu -> EnableMenuItem (ID_DEBUG_NEW, MF_ENABLED);
		pMenu -> EnableMenuItem (ID_DEBUG_IMPORT, MF_ENABLED);
		pMenu -> EnableMenuItem (ID_DEBUG_OPEN, MF_ENABLED);
	}

	pMenu -> EnableMenuItem (ID_DEBUG_SAVE, m_fIsDirty ? MF_ENABLED : MF_GRAYED);
	if (m_fStorageManagement) 
		pMenu -> EnableMenuItem (ID_DEBUG_SAVETEXT, m_fIsDirty ? MF_ENABLED : MF_GRAYED);
	
// *** Compile ***
	uiEnabled = (iState == ES_IDLE && g_SummitModuls[COMPILER].fIsInstalled && m_fBreakSet) ? MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_SYNTAX, uiEnabled);

// *** DebugSession ***
	uiEnabled = (	iState == ES_EXECUTING					|| 
					!g_SummitModuls[RUNTIME].fIsInstalled	|| 
					(!m_fBreakSet && !m_fOtherFunction		||
					m_fEditOnly)/*Script läuft noch*/)		?	MF_GRAYED : MF_ENABLED; 
	pMenu -> EnableMenuItem (ID_DEBUG_GO, uiEnabled);
	pMenu -> EnableMenuItem (ID_DEBUG_TRACEIN, uiEnabled);
	pMenu -> EnableMenuItem (ID_DEBUG_TRACEOVER, uiEnabled);

	uiEnabled = (	(iState == ES_IDLE	&& (m_fBreakSet || m_fOtherFunction))	|| 
					!g_SummitModuls[RUNTIME].fIsInstalled	||
					m_fEditOnly)							?	MF_GRAYED : MF_ENABLED;
	pMenu -> EnableMenuItem (ID_DEBUG_SUSPEND, uiEnabled);

// *** hexadezimale Anzeige ***
	if (m_fDisplayFormat == true) { // alt == hex
		if (!::LoadString (strMenuText, IDS_DEZ)) return;
	} else {
		if (!::LoadString (strMenuText, IDS_HEX)) return;
	}
 	pMenu -> ModifyMenu (ID_DEBUG_HEX, MF_BYCOMMAND | MF_STRING,	
 				ID_DEBUG_HEX, strMenuText);	
	
	uiEnabled = (iState != ES_IDLE || !g_SummitModuls[RUNTIME].fIsInstalled) ? MF_GRAYED : MF_ENABLED;
	pMenu -> EnableMenuItem (ID_DEBUG_HEX, uiEnabled);

// *** Watches ***
	uiEnabled = (	m_Debug.CanDeleteWatch()				&& 
					g_SummitModuls[RUNTIME].fIsInstalled	&&
					(m_fBreakSet || m_fOtherFunction))							?	MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_DELETEWATCH, uiEnabled);

	uiEnabled = (g_SummitModuls[RUNTIME].fIsInstalled && (m_fBreakSet || m_fOtherFunction)) ? MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_ADDWATCH, uiEnabled);

	uiEnabled = (	iState == ES_SUSPENDED					&& 
					IsWatch() && g_SummitModuls[RUNTIME].fIsInstalled	&&
					(m_fBreakSet || m_fOtherFunction))							? MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_MODIFYDLG, uiEnabled);

// *** CallStack ***
	uiEnabled = (	iState == ES_SUSPENDED	&& 
					g_SummitModuls[RUNTIME].fIsInstalled &&
					(m_fBreakSet || m_fOtherFunction))			? MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_CALLSTACK, uiEnabled);

// *** Breakpoint ***
	uiEnabled = (g_SummitModuls[RUNTIME].fIsInstalled) ? MF_ENABLED : MF_GRAYED;
	pMenu -> EnableMenuItem (ID_DEBUG_BREAKPOINT, uiEnabled);

// *** Hilfe A-Z ***
char KeyWord[MAXSTRLENGTH];
	
	uiEnabled = (m_Debug.GetCaretWord(KeyWord, MAXSTRLENGTH)) ? MF_ENABLED : MF_GRAYED; 
	pMenu -> EnableMenuItem (ID_DEBUG_GETHELPON, uiEnabled);	
}

bool CBScriptDebug::IsWatch()
{
char Name[MAXSTRLENGTH];
	if (m_Debug.GetFirstWatch(Name, MAXSTRLENGTH))
		return true;
return false;
}

void CBScriptDebug::OnSetFocus(CWnd* pOldWnd) 
{
	CDialog::OnSetFocus(pOldWnd);
	
	::SetFocus(m_Debug.GetWindow());	
}

void CBScriptDebug::EndMRUHandling (void)
{
#if defined(WIN32)
/*	m_wndToolBar.SaveState (HKEY_CURRENT_USER, 
		"Software\\uve\\TRiAS\\Extensions\\TRiAS.MacroScript.1",
		"MainToolBar");
*/
	if (GetWin32Kind() == WIN32S)
		SaveMruInIni (m_pMRUMenu, g_cbOpenMRU, g_cbLocalINI);
	else
		SaveMruInReg (m_pMRUMenu, g_cbOpenMRUKey);
#else
	SaveMruInIni (m_pMRUMenu, g_cbOpenMRU, g_cbLocalINI);
#endif
	DeleteMruMenu (m_pMRUMenu);
	m_pMRUMenu = NULL;
}

bool CBScriptDebug::DebuggerEnd(void)
{
	if (AskSave(m_fInitNew)) return false;
	
// end execution, if something is currently executing
// Message "end" an den Debugger, warten in ExeEnd(), dann entgültig schliessen	
	if (m_Debug.GetState() == ES_EXECUTING) {
		m_Debug.EndScript();
	// script currently executing, set state to resend CLOSE later on
		m_fSendClose = true; return false; // Script erst nach Notification ExeEnd() schliessen
	} else if (m_Debug.GetState() == ES_SUSPENDED) { // für FilterDebugger bei zwischendurch schliessen
		m_Debug.EndScript();
		m_fClose = true; 
	} 

// MRUList behandeln
	EndMRUHandling();

return true;
}

// kommt bei Projekt schliessen
HRESULT CBScriptDebug::Close()
{
// Debugger nur automatisch schliessen, wenn nicht projektbezogene Macros geladen sind
	if (false == m_fStorageManagement) return S_FALSE;
	
	if (m_fRunModal == false) 
	{
		CString str;
		if (!LoadString(str, IDS_DEBISOPENYET)) return ResultFromScode(E_FAIL); 
		// IDOK == nicht Debugger schliessen
		AfxMessageBox (str);
	}

	if (DebuggerEnd() == false) return S_FALSE;

	CDialog::OnClose();
// Schliessen o.k.
return NOERROR;
}

void CBScriptDebug::OnClose()
{                        
	if (DebuggerEnd() == false) return;

//	if (OkToExit()), DestroyDebugger() nach Message
	GetParent() -> PostMessage (WM_CLOSEDEBUGGERDIALOG);

	CDialog::OnClose();
}

////////////////////////////////////////////////////////////////////////////
// MenuCommands
void CBScriptDebug::OnExit()
{	
	if (DebuggerEnd() == false) return;

	GetParent() -> PostMessage (WM_CLOSEDEBUGGERDIALOG);
}

void CBScriptDebug::OnDebugCut() 
{
	if (m_Debug.GetState() != TS_RUNNING && m_Debug.HasSelection()) {
		m_Debug.EditCut();
		if(m_Debug.CanUndo()) {
			// Toolbarknöpfe einstellen
			m_wndToolBar.Enable (ID_DEBUG_UNDO);
			m_wndToolBar.Repaint();
		}
	}
}

void CBScriptDebug::OnDebugCopy() 
{
	if (m_Debug.HasSelection()) {
		m_Debug.EditCopy();
		if(m_Debug.CanUndo()) {
			// Toolbarknöpfe einstellen
			m_wndToolBar.Enable (ID_DEBUG_UNDO);
			m_wndToolBar.Repaint();
		}
	}
}

void CBScriptDebug::OnDebugAddwatch() 
{
	if (m_fBreakSet || m_fOtherFunction)
		m_Debug.AddWatch (NULL);	
}

void CBScriptDebug::OnDebugModifyDlg() 
{
	if (m_fBreakSet || m_fOtherFunction)
		ebDebugger_ModifyDialog(m_Debug.GetWindow(), true);
}

void CBScriptDebug::OnDebugDeletewatch() 
{
	if (m_Debug.CanDeleteWatch() && (m_fBreakSet || m_fOtherFunction))
		m_Debug.DeleteWatch (NULL);	
}

void CBScriptDebug::OnDebugHex() 
{
	if (m_Debug.GetState() != TS_IDLE) return;

	if (m_fDisplayFormat == false) {
		ebDebugger_SetDisplayFormat(m_Debug.GetWindow(), DF_HEX);
		m_fDisplayFormat = true;
	} else {
		ebDebugger_SetDisplayFormat(m_Debug.GetWindow(), DF_DECIMAL);
		m_fDisplayFormat = false;
	}
}

void CBScriptDebug::OnDebugBreakpoint() 
{
	m_Debug.ToggleBreakpoint (0);	
}

void CBScriptDebug::OnDebugCallstack() 
{
	if ((m_fBreakSet || m_fOtherFunction))
		m_Debug.InvokeCallsDialogBox();	
}

void CBScriptDebug::OnDebugDelete() 
{
	if (m_Debug.GetState() != TS_RUNNING && m_Debug.HasSelection())	
		m_Debug.EditClear();	
}

void CBScriptDebug::OnDebugEditdialog() 
{
	if (m_Debug.GetState() != TS_RUNNING && m_Debug.IsDialogSelected())	
		m_Debug.EditDialog();	
}

void CBScriptDebug::OutputReachedEOF(void)
{
CString str;

	if (!::LoadString (str, IDS_REACHEDEOF)) return;
	m_wndStatusBar.SetPaneText (0, str, true );
	m_Debug.SetCaretPos ( 0, 0, false);	
}

void CBScriptDebug::OutputReachedBOF(void)
{
CString str;

	if (!::LoadString (str, IDS_REACHEDBOF)) return;
	m_wndStatusBar.SetPaneText (0, str, true );
	m_Debug.SetCaretPos ( 0, 0, false);	
}

void CBScriptDebug::OnDebugNewdialog() 
{                        
ebBOOL bErr = false;
	// Initialize the ebDLGINFO structure
	if (m_Debug.GetState() != TS_RUNNING)	
		m_Debug.InsertDialog();
                              
}
                              
// Aufruf von Menü 
void CBScriptDebug::OnDebugFindnext() 
{                                 
	m_wndStatusBar.SetPaneText ( 0, g_cbNil, true );

	TRY {                                       		
		if(m_strFindText.IsEmpty()) return;						
		FindNext();
	} CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
	} END_CATCH;
}

// Aufruf von Menü 
void CBScriptDebug::OnDebugFind() 
{
	m_pcFindText = new char[MAXSTRLENGTH];
	if (NULL == m_pcFindText) AfxMessageBox (IDS_NOMEMORY);
	
	m_wndStatusBar.SetPaneText ( 0, g_cbNil, true );

	if ( NULL == m_pFRD ) {

		if (1 == m_Debug.GetSelection (m_pcFindText, MAXSTRLENGTH) )
			m_Debug.GetCaretWord (m_pcFindText, MAXSTRLENGTH);
		
		m_pFRD = CFindReplaceDlg :: CreateInstance();			
		if (NULL == m_pFRD) {
			AfxMessageBox (IDS_NOMEMORY);
			return;
		}		
		m_pFRD -> m_fr.lStructSize = sizeof ( FINDREPLACE );
		m_pFRD -> m_fr.lpstrFindWhat = m_pcFindText;
		m_pFRD -> m_fr.wFindWhatLen = MAXSTRLENGTH;                                      	
		m_pFRD -> Create ( true, NULL, NULL,
				FR_DOWN,  
				this);
	}
}

void CBScriptDebug::OnDebugReplace() 
{
	m_pcFindText = new char[MAXSTRLENGTH];
	if (NULL == m_pcFindText) AfxMessageBox (IDS_NOMEMORY);

	m_pcReplaceWithText = new char[MAXSTRLENGTH];
	if (NULL == m_pcReplaceWithText) AfxMessageBox (IDS_NOMEMORY);
		
	m_wndStatusBar.SetPaneText (0, g_cbNil, true);

	if ( NULL == m_pFRD ) {
		if (1 == m_Debug.GetSelection( m_pcFindText, MAXSTRLENGTH ) )
			m_Debug.GetCaretWord ( m_pcFindText, MAXSTRLENGTH);		
		
		m_pFRD = CFindReplaceDlg :: CreateInstance();			
		if (NULL == m_pFRD) {
			AfxMessageBox (IDS_NOMEMORY);
			return;
		}		
		m_pFRD -> m_fr.lStructSize = sizeof (FINDREPLACE);
		m_pFRD -> m_fr.lpstrFindWhat = m_pcFindText;
		m_pFRD -> m_fr.lpstrReplaceWith = m_pcReplaceWithText;
		m_pFRD -> m_fr.wFindWhatLen = MAXSTRLENGTH;                                      	
		m_pFRD -> m_fr.wReplaceWithLen = MAXSTRLENGTH;                                      	
		m_pFRD -> Create ( false, NULL, NULL,
				FR_DOWN,
				this);
	}
}

LRESULT CBScriptDebug :: FindNext()
{
	if (-1 == m_Debug.FindText(m_strFindText,m_bUpDown,m_bMatchCase, m_bMatchWholeWord) ) {		
		if (m_bUpDown==true) {
			OutputReachedEOF();
			m_Debug.SetCaretPos (0, 0, false);

			if (-1 == m_Debug.FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord) )
				OutPutNoMatch(m_strFindText);
		}
		else {
			OutputReachedBOF();
			m_Debug.SetCaretPos (0, m_Debug.GetNumLines()+1, false);

			if (-1 == m_Debug.FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord) )
				OutPutNoMatch(m_strFindText);
		}
	}

return 1;
}
LRESULT CBScriptDebug :: ReplaceAll(const CString &str)
{
	m_Debug.SetCaretPos (0, 0, false);

	if (-1 == m_Debug.FindText (m_strFindText, true, m_bMatchCase, m_bMatchWholeWord) ) { 
		OutPutNoMatch(m_strFindText); return 1; 
	} 
	m_Debug.ReplaceSelection (str, 0);			
	
	while (-1 != m_Debug.FindText (m_strFindText, true, m_bMatchCase, m_bMatchWholeWord) ) 
		m_Debug.ReplaceSelection (str, 0);

	OutputReachedEOF();

return 1;
}
LRESULT	CBScriptDebug :: ReplaceCurrent(const CString &str)
{
DWORD dwCursorPos = m_Debug.GetCursorPos ();			
int ix = LOWORD (dwCursorPos), iy = HIWORD (dwCursorPos), iLength = m_strFindText.GetLength()+1;
	
	if (ix - iLength < 0) ix = 0;
	else ix = ix-iLength;
	m_Debug.SetCaretPos (ix, iy);
	
	if (-1 !=  m_Debug.FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord) ) {
		m_Debug.ReplaceSelection (str, 0);
		if (-1 == m_Debug.FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord) ) {
			if (m_bUpDown) {
				OutputReachedEOF();
				m_Debug.SetCaretPos (0, 0, false);
				m_Debug.FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord);
			}
			else {
				OutputReachedBOF();
				m_Debug.SetCaretPos (0, m_Debug.GetNumLines()+1, false);
				m_Debug.FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord);
			}
		}
	}
	else {		
		if (m_bUpDown==true) {
			OutputReachedEOF();
			m_Debug.SetCaretPos (0, 0, false);

			if (-1 != m_Debug.FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord) ) {
				m_Debug.ReplaceSelection (str, 0);
				if (-1 == m_Debug.FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord) )
					OutputReachedEOF();
			}
			else
				OutPutNoMatch(m_strFindText);
		}		
		else {
			OutputReachedBOF();
			m_Debug.SetCaretPos (0, m_Debug.GetNumLines()+1, false);

			if (-1 != m_Debug.FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord) ) {
				m_Debug.ReplaceSelection (str, 0);
				if (-1 == m_Debug.FindText (m_strFindText, m_bUpDown, m_bMatchCase, m_bMatchWholeWord) )
					OutputReachedBOF();
			}
			else
				OutPutNoMatch(m_strFindText);
		}
	}
	
return 1;
}

LRESULT CBScriptDebug :: OnCallbackFindReplace(WPARAM wParam, LPARAM lParam)
{	
	ASSERT(m_pFRD);

	m_wndStatusBar.SetPaneText (0, g_cbNil, true );

CString strReplaceWithText;

	if (m_pFRD -> IsTerminating()) {
		m_pFRD -> DestroyWindow(); m_pFRD = NULL; 		
		if (m_pcFindText) delete m_pcFindText;	
		m_pcFindText = NULL;		
		if (m_pcReplaceWithText) delete	m_pcReplaceWithText; 
		m_pcReplaceWithText = NULL;

	CString str;
		if (!::LoadString (str, ID_STATUSBAR_PANE1)) return 0;
		m_wndStatusBar.SetPaneText (0, str, true);		
	return 1;
	}
	else {		
		m_pFRD -> UpdateWindow();		
		m_bMatchCase = m_pFRD -> MatchCase();			
		m_bUpDown = m_pFRD -> SearchDown();
		m_bMatchWholeWord = m_pFRD -> MatchWholeWord();
		
		m_strFindText = m_pFRD -> GetFindString();
		if(m_strFindText.IsEmpty()) return 0;

		strReplaceWithText = m_pFRD -> GetReplaceString();		
	}
 
	TRY {
		if (m_pFRD->FindNext())
			FindNext();
		else if (m_pFRD -> ReplaceAll()) 
			ReplaceAll(strReplaceWithText);
		else if (m_pFRD -> ReplaceCurrent())
			ReplaceCurrent(strReplaceWithText);		
		else ASSERT (0);

	} CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return 0;
	} END_CATCH;

return 1;
}

void CBScriptDebug::OnDebugFonts() 
{
LOGFONT LF;
HFONT hFont = m_Debug.GetFont();
int iSize = GetObject (hFont, sizeof(LOGFONT), &LF);
	
	ASSERT (iSize != 0);

	if (iSize != 0) {
	DWORD dwFlags = CF_ENABLEHOOK | CF_SCREENFONTS | CF_ANSIONLY | 
			CF_INITTOLOGFONTSTRUCT | CF_FIXEDPITCHONLY;
	CFontDialog FD (&LF, dwFlags, NULL, this);

		FD.m_cf.lpfnHook = &CallbackFontDlgProc;	 
		FD.m_cf.lCustData = (LONG) this;
	
		if (FD.DoModal() == IDOK) {    
		// alle selbst kreierten Fonts auch wieder freigeben
			m_Debug.SetFont (::CreateFontIndirect (&LF));
			if (NULL == m_hFontOld) // erster neuer Font
				m_hFontOld = hFont;
			else if (hFont)		// nicht erster, m_hFontOld beibehalten
				::DeleteObject (hFont);
		
		// neuen Font auch anzeigen
			::InvalidateRect (m_Debug.GetWindow(), NULL, true);
			::UpdateWindow (m_Debug.GetWindow());
		}                                               
	}
}

void CBScriptDebug::OnDebugGotoline() 
{
	m_Debug.InvokeGotoLineDialogBox();	
}

void CBScriptDebug::OnDebugPaste() 
{

	if (m_Debug.GetState() != TS_RUNNING &&
		::IsClipboardFormatAvailable (CF_TEXT))
	{
		m_Debug.EditPaste();
		if(m_Debug.CanUndo()) {
			// Toolbarknöpfe einstellen
			m_wndToolBar.Enable (ID_DEBUG_UNDO);
			m_wndToolBar.Repaint();
		}
	}
}

void CBScriptDebug::OnDebugRecording() 
{
	// TODO: Add your command handler code here
	
}

void CBScriptDebug::OnDebugSuspend() 
{
	if (m_Debug.GetState() == TS_RUNNING ||
		m_Debug.GetState() == TS_SUSPENDED)	
	{
		m_Debug.EndScript();
	}

	m_fBreakSet  = true;
	PostMessage(uiWM_EndScript, 0, GO);
}

void CBScriptDebug::OnDebugSyntax() 
{
	if (g_SummitModuls[COMPILER].fIsInstalled && m_Debug.GetState() != TS_RUNNING && m_Debug.Compile())
		AfxMessageBox (IDS_NOERRORSFOUND);
}

void CBScriptDebug::OnDebugGo() 
{
	if (m_Debug.GetState() != ES_EXECUTING && 
		g_SummitModuls[RUNTIME].fIsInstalled)
	{
		if (!(m_fBreakSet || m_fOtherFunction)) return;
		
		// nur einmal für alle nach Speichern fragen
		if (false == m_fAskSave) {
			if (AskSave(false))
				return;// Cancel
			m_fAskSave = true;
		}

		if (m_fRunModal || m_fOtherFunction) {
			m_Debug.StartScript();
			return;
		}

		if (NULL == m_Debug.GetCode(false) ||
			true == m_fIsDirty) {	
			if (!m_Debug.Compile()) return;
		}
		
		if (FAILED(RunScript(GO))) return;
	}
}

void CBScriptDebug::OnDebugTracein() 
{
	if (g_SummitModuls[RUNTIME].fIsInstalled && (m_fBreakSet || m_fOtherFunction)) {

		if (false == m_fAskSave) {
			if (AskSave(false))
				return;// Cancel
			m_fAskSave = true;
		}

		if (m_fRunModal || m_fOtherFunction) {
			m_Debug.TraceInto();
			return;
		}

		if (NULL == m_Debug.GetCode(false) ||
			true == m_fIsDirty) {	
			if (!m_Debug.Compile()) return;
		}

		if (FAILED(RunScript(TRACEINTO))) return;
	}
}

void CBScriptDebug::OnDebugTraceover() 
{
	if (g_SummitModuls[RUNTIME].fIsInstalled && (m_fBreakSet || m_fOtherFunction)) {

		if (false == m_fAskSave) {
			if (AskSave(false))
				return;// Cancel
			m_fAskSave = true;
		}

		if (m_fRunModal || m_fOtherFunction) {
			m_Debug.StepOver();
			return;
		}

		if (NULL == m_Debug.GetCode(false) ||
			true == m_fIsDirty) {	
			if (!m_Debug.Compile()) return;
		}

		if (FAILED(RunScript(TRACEOVER))) return;
	}
}

void CBScriptDebug::OnDebugUndo() 
{
	if (m_Debug.GetState() != TS_RUNNING && m_Debug.CanUndo())
		m_Debug.EditUndo();
}

//
// *** Speicheroperationen ***
//

void CBScriptDebug::OnDebugNew()
{    
	if (m_Debug.GetState() == TS_RUNNING) return;
	
// bei Storage wird altes Script überschrieben, 
// vorher bei Änderung oder Import Speichern erfragen
	if (AskSave(false)) return;	

	InitNewScript(m_fStorageManagement ? true : false);// Dirty
}

void CBScriptDebug::OnDebugOpen()
{
	if (m_Debug.GetState() == TS_RUNNING) return;

// bei Storage wird altes Script überschrieben, vorher bei Änderung gespeichert
	if (AskSave(false)) return;

	if (m_fStorageManagement) { 
		if (!OpenNew_DB()) { 
			FileErrorMessage (IDS_CANTOPENFILE, m_strFileName); 
			return; 
		}
	}
	else { 
		if(!OpenNew()) { 
			FileErrorMessage (IDS_CANTOPENFILE, m_strFileName); 
			return; 
		}
	}
}

void CBScriptDebug::OnDebugSave()
{
	if ( ! m_fIsDirty) return;

	if (m_fStorageManagement == true) {
		SaveScript_InDB(false);
		m_fInitNew = false;
	}
	else SaveScript();	

CString str;
	if (!::LoadString (str, ID_STATUSBAR_PANE1)) return;
	m_wndStatusBar.SetPaneText (0, str, true);		
}

void CBScriptDebug::OnDebugSaveText()
{
	if ( ! m_fIsDirty) return;

	if (m_fStorageManagement == true) {
		SaveScript_InDB(true);
		m_fInitNew = false;
	}

CString str;
	if (!::LoadString (str, ID_STATUSBAR_PANE1)) return;
	m_wndStatusBar.SetPaneText (0, str, true);		
}

void CBScriptDebug::OnDebugSaveas()
{
	SaveAs();

CString str;
	if (!::LoadString (str, ID_STATUSBAR_PANE1)) return;
	m_wndStatusBar.SetPaneText (0, str, true);		
}

void CBScriptDebug::OnDebugGetHelpOn()
{
char KeyWord[MAXSTRLENGTH];

	if (m_Debug.GetCaretWord(KeyWord, MAXSTRLENGTH)) {
		VERIFY(SUCCEEDED(KeywordHelp(KeyWord)));
	}
}

void CBScriptDebug::OnDebugEditorHelp()
{
	VERIFY(SUCCEEDED(DebuggerHelp()));
}

void CBScriptDebug::OnDebugTriasHelp()
{
	VERIFY(SUCCEEDED(TriasHelp()));
}

void ebCALLBACK EXPORT LineNumberProc(long lParam, ebWORD wLineNo)
{
TCHAR buf[64];
CBScriptDebug *pSD = (CBScriptDebug *)lParam;
int numlines = pSD -> m_Debug.GetNumLines();

	if (numlines && (wLineNo % 20 == 0)) {
	CString strFmt;

		if (LoadString (strFmt, IDS_COMPILEFORMAT)) {
			wsprintf(buf, strFmt, (wLineNo * 100L) / numlines);
			pSD -> m_wndStatusBar.SetPaneText (0, buf, true);		
			pSD -> m_wndStatusBar.UpdateWindow();
		}
	}
}

long CBScriptDebug::Compile(ebLPCOMPILESTRUCT lpcs)
{
	// add a line number procedure
	lpcs -> wFlags |= CF_USELINENUMBERPROC;
	lpcs -> lpfnLineNum = LineNumberProc;
	lpcs -> LineNumData = (long)this;

CString str;

	if (!LoadString (str, IDS_COMPILESTART)) return 1;
	m_wndStatusBar.SetPaneText (0, str, true);		
	
return 0;
}

long CBScriptDebug::CompileEnd()
{
CString str;

	if (!LoadString (str, ID_STATUSBAR_PANE1)) return 1;
	m_wndStatusBar.SetPaneText (0, str, true);		

return 0;
}

long CBScriptDebug::Changed()
{
	m_fIsDirty = true;
	m_fAskSave = false;

	GenerateCaption ();	// beim ersten mal

	if(m_Debug.CanUndo()) {
		// Toolbarknöpfe einstellen
		m_wndToolBar.Enable (ID_DEBUG_UNDO);
		m_wndToolBar.Repaint();
	}

return 0;
}

long CBScriptDebug::ExeEnd(ebPARAM1 np1)
{
CString str;

	if (LoadString (str, IDS_SCRIPTEXECUTEEND))
		m_wndStatusBar.SetPaneText (0, str, true);		

	// Knöpfchen richten			
	m_wndToolBar.Disable (ID_DEBUG_CALLSTACK);
	m_wndToolBar.Disable (ID_DEBUG_SUSPEND);
	if (m_Debug.CanUndo()) m_wndToolBar.Enable (ID_DEBUG_UNDO);
	m_wndToolBar.Enable (ID_DEBUG_PASTE);
	m_wndToolBar.Enable (ID_DEBUG_CUT);
	m_wndToolBar.Repaint();

// Soll abgebrochen werden ?
	if (GetBreakFlag())
		m_fBreakSet = true;
	else 
		m_fBreakSet = false;
		
// evtl. Parameter rausholen
	{
	CebThread Thread (ebDebugger_GetScript (m_Debug.GetWindow(), false));	

		Thread.Attach (ebDebugger_GetThread (m_Debug.GetWindow(), false));
		
	// evtl. Rückgabewert abfragen
		if (NULL != m_pPars) {
			if (m_pPars -> pTypes[0].wType != 0) 
				GetParam (Thread, 0, m_pPars -> pTypes[0], m_pPars -> pValues[0], true);		

		// evtl. Parameter zurückschreiben
			for (int iOut = 0; iOut <= m_iNumParams; iOut++) {
				if (iOut > 0 && m_pPars -> pTypes[iOut].wType & TYP_MODSPARM)
					GetParam (Thread, iOut, m_pPars -> pTypes[iOut], m_pPars -> pValues[iOut], true);

			// Parameter ausnullen, damit eventuelle AppObjektpointer nicht released werden: 
				if (TYP_APPOBJECT == m_pPars -> pTypes[iOut].wType) 
				{
					DWORD dw = 0L;
					SetParam (Thread, iOut, m_pPars -> pTypes[iOut], &dw);
				}
			}
		}

		Thread.Detach();
	}


// Debuggerfenster sollte bereits geschlossen werden
	if (m_fSendClose) {
		if (AskSave(m_fInitNew)) return 0;
		
		EndMRUHandling();
		GetParent() -> PostMessage (WM_CLOSEDEBUGGERDIALOG);

		return 0;
	}

	if (::LoadString (str, ID_STATUSBAR_PANE1)) 
		m_wndStatusBar.SetPaneText (0, str, true);		

// setzt globale Variablen zur Steuerung des Script-Running (welche Entries ?)	
	GetWhichEntryMayRun();

	BreakReset();
		
	if (m_fRunModal) {

	ebHTHREAD hThread = (ebHTHREAD) np1;
		// möglicherweise Laufzeitfehler
		if (ebThread_GetErrorNumber(hThread))
			m_fRunError = true;
		ShowWindow(SW_HIDE);
		EndModalLoop(IDOK);
	}

return 0;
}

long CBScriptDebug::Stop()
{
	if (IsIconic() && ES_SUSPENDED == m_Debug.GetState()) 
	{
		ShowWindow(SW_RESTORE);
		BringWindowToTop();
	}

	m_rInst.SetWindow (m_hWnd);		// ParentWindow setzen

CString str;

	if (!::LoadString (str, IDS_SUSPENDED)) return 1;
	m_wndStatusBar.SetPaneText (0, str, true);		

// Knöpfchen richten
	m_wndToolBar.Enable (ID_DEBUG_GO);
	m_wndToolBar.Enable (ID_DEBUG_SUSPEND);
	m_wndToolBar.Enable (ID_DEBUG_CALLSTACK);
	m_wndToolBar.Enable (ID_DEBUG_TRACEIN);
	m_wndToolBar.Enable (ID_DEBUG_TRACEOVER);
	m_wndToolBar.Repaint();
	
	m_hWndSaved = ::GetFocus();
	m_fEnabled = IsWindowEnabled() ? true : false;
	EnableWindow (true);
	SetFocus();

return 0;
}

long CBScriptDebug::Go()
{
CString str;
	if (!::LoadString (str, IDS_SCRIPTEXECUTESTART)) return 1;
	m_wndStatusBar.SetPaneText (0, str, true);		

	if (m_hWndSaved && IsWindow(m_hWndSaved))
		::SetFocus (m_hWndSaved);
	EnableWindow (m_fEnabled ? true : false);

// ParentWindow setzen (zur Laufzeit ist CDummy der Parent)
	m_rInst.SetWindow (m_pDummyParent -> m_hWnd);
	m_rInst.SetViewportParent(m_pDummyParent -> m_hWnd);

return 0;
}

long CBScriptDebug::ExeStart()
{
CString str;

	if (!::LoadString (str, IDS_COMPILEEND)) return 1;

	m_wndStatusBar.SetPaneText (0, str, true);		

	if (m_fStorageManagement) {
	
	CString strBuf;
	char * pBuf = NULL;
	
		TRY {
			pBuf = strBuf.GetBuffer(_MAX_PATH);
			if (pBuf == NULL) return 1;
		}
		CATCH (CMemoryException, e) {
			AfxMessageBox (IDS_NOMEMORY);
			return 1;
		}                  
		END_CATCH

		DEX_GetActiveProject(pBuf);
		strBuf.ReleaseBuffer();
		m_rInst.SetHomeDir(GetPathName(strBuf));
	}
	else
		m_rInst.SetHomeDir(GetPathName(m_strFileName));

// Knöpfchen richten			
	m_wndToolBar.Enable (ID_DEBUG_SUSPEND);
	m_wndToolBar.Disable (ID_DEBUG_GO);
	m_wndToolBar.Disable (ID_DEBUG_CALLSTACK);
	m_wndToolBar.Disable (ID_DEBUG_TRACEIN);
	m_wndToolBar.Disable (ID_DEBUG_TRACEOVER);
	m_wndToolBar.Disable (ID_DEBUG_UNDO);
	m_wndToolBar.Disable (ID_DEBUG_PASTE);
	m_wndToolBar.Disable (ID_DEBUG_CUT);
	m_wndToolBar.Repaint();
				
// evtl. müssen Parameter gesetzt werden
	{
	CebThread Thread (ebDebugger_GetScript (m_Debug.GetWindow(), false));	
		
		Thread.Attach (ebDebugger_GetThread (m_Debug.GetWindow(), false));
		Thread.SetStackSize (8192);				

		if (m_iNumParams) {				// evtl. Parameter setzen
			for (int i = 1; i <= m_iNumParams; i++) 
				SetParam (Thread, i, m_pPars -> pTypes[i], m_pPars -> pValues[i]);
		}

		Thread.SetLong (0, m_fBreakSet);		// BreakFlag voreinstellen
		Thread.Detach();
	}
	
	m_hWndSaved = NULL;
	m_fEnabled = true;

return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Fenster nur als Editor verwenden
void CBScriptDebug::EditOnly (void)
{
	// GO etc. blockieren
	m_fEditOnly = true;

	m_wndToolBar.Disable (ID_DEBUG_SUSPEND);
	m_wndToolBar.Disable (ID_DEBUG_GO);
	m_wndToolBar.Disable (ID_DEBUG_CALLSTACK);
	m_wndToolBar.Disable (ID_DEBUG_TRACEIN);
	m_wndToolBar.Disable (ID_DEBUG_TRACEOVER);
	m_wndToolBar.Repaint();
}


long CBScriptDebug::RightButtonUp (ebPARAM1 np1)
{
CMenu Menu;

	if (!Menu.LoadMenu(IDR_RBUTTONDEBUGGER)) 
	{
		ASSERT(0); 
		return 1;
	}

POINT pt;

	GetCursorPos (&pt);
	::SetFocus(m_Debug.GetWindow());
	
int iPos = (1 == np1) ? 0 : 1;

	m_fRMBMenu = true;
	return !(Menu.GetSubMenu (iPos)) -> TrackPopupMenu (0, pt.x, pt.y, this);
}

long ebCALLBACK EXPORT HandleDebuggerNotification(HWND hWnd,int code,ebPARAM1 np1,ebPARAM2 np2,long lPassThrough)
{
	switch (code) {
	case DN_ERRSPACE:	// Sent, when memory-error occured
		return AfxMessageBox(IDS_NOMEMORY);
		break;
	case DN_COMPILE:	// Sent immediately before compilation
		return ((CBScriptDebug *)lPassThrough) -> Compile((ebLPCOMPILESTRUCT)np2);
		break;
	case DN_COMPILEEND:
		return ((CBScriptDebug *)lPassThrough) -> CompileEnd();
		break;

	case DN_CHANGED:	// script saving is required
		return ((CBScriptDebug *)lPassThrough) -> Changed();
		break;
		
	case DN_EXECUTESTART:// sent before begin of execution
		return ((CBScriptDebug *)lPassThrough) -> ExeStart();
		break;

	case DN_EXECUTEEND:	// sent if script execution has terminated
		return ((CBScriptDebug *)lPassThrough) -> ExeEnd(np1);
		break;

	case DN_GO:			// sent immediately before execution begins
		return ((CBScriptDebug *)lPassThrough) -> Go();
		break;

	case DN_STOP:		// sent when execution is suspended
		return ((CBScriptDebug *)lPassThrough) -> Stop();
		break;

	case DN_CLOSE:		// ESC was pressed
		break;

	case DN_SWITCH:		// sent when the script needs to be changed
		break;

	case DN_DIALOGSTART:// sent before a dialog in the debugger is invoked
		break;

	case DN_DIALOGEND:	// sent after a dialog in the debugger was closed
		break;

    case DN_RIGHTBUTTONUP:
		return ((CBScriptDebug *)lPassThrough) -> RightButtonUp(np1);
		break;

	default:
		break;
	}

return 0;
}

BOOL CBScriptDebug::OnCommand(WPARAM wParam, LPARAM lParam)
{
UINT uiID = GET_WM_COMMAND_ID (wParam, lParam);
UINT uiNotifCode = GET_WM_COMMAND_CMD (wParam, lParam);

	if (uiNotifCode == 0 && uiID >= m_uiMruID && uiID < m_uiMruID+9) {
		if (AskSave(false)) return false;
		
// MRUMenuCommand
		return OpenFromMRU (uiID);
	}

return CDialog::OnCommand (wParam, lParam);
}

#if defined(WIN32)
BOOL CBScriptDebug::OnNotify (WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	switch (((LPNMHDR)lParam) -> code) {
	case TTN_NEEDTEXT:    // Display tool tip text.
		{
		LPTOOLTIPTEXT lpToolTipText = (LPTOOLTIPTEXT)lParam;

			lpToolTipText -> hinst = g_hInstance;
			lpToolTipText -> lpszText = MAKEINTRESOURCE(lpToolTipText->hdr.idFrom+1000);

			*pResult = true;
			return true;
		}

	case TTN_SHOW:	// ToolTip wird eingeblendet
		{
		// StatusZeile richten
		CString str;

			if (!::LoadString (str, ((LPTOOLTIPTEXT)lParam)->hdr.idFrom)) return false;
			m_wndStatusBar.SetPaneText (0, str, true);

			*pResult = true;
			return true;
		}
		break;

	case TTN_POP:	// ToolTip wird ausgebelendet
		{
		// StatusZeile richten
		CString str;

			if (!::LoadString (str, ID_STATUSBAR_PANE1)) return false;
			m_wndStatusBar.SetPaneText (0, str, true);

			*pResult = true;
			return true;
		}
		break;

	case TBN_QUERYDELETE:	// Toolbar customization -- can we delete this button?
		*pResult = true;
		return true;

	case TBN_GETBUTTONINFO:	// The toolbar needs information about a button.
		*pResult = false;
		return true;

	case TBN_QUERYINSERT:	// Can this button be inserted? Just say yo.
		*pResult = true;
		return true;

	case TBN_CUSTHELP:	// Need to display custom help.
		MessageBox ("This help is custom.");
		return true;

	case TBN_TOOLBARCHANGE:	// Done dragging a bitmap to the toolbar.
		m_wndToolBar.AutoSize();
		return true;

	default:
		break;
	}

return CWnd::OnNotify (wParam, lParam, pResult);
}
#endif

BOOL CBScriptDebug::OnCmdMsg(UINT nID, int nCode, void* pExtra,
				AFX_CMDHANDLERINFO* pHandlerInfo)
{
#if defined(WIN32)
// Toolbar bedienen
//	m_wndToolBar.OnCmdMsg (nID, nCode, pExtra, pHandlerInfo);
#endif

return CDialog:: OnCmdMsg (nID, nCode, pExtra, pHandlerInfo);
}


bool CBScriptDebug::DeleteWatchVariables (void)		// alle Watches entfernen
{
char cbVarName[VARNAMESZ];

// delete the first watch variable until there aren't any more
	while (m_Debug.GetFirstWatch (cbVarName, VARNAMESZ)) {
		if (!m_Debug.DeleteWatch (cbVarName))
			break;
	}
	m_Debug.SetWatchWindowHeight (0);

return true;
}

void CBScriptDebug::GenerateCaption ()
{
CString strCaption, strAppName, strName;
char *pCaption = NULL;

	TRY {
		pCaption = strCaption.GetBuffer (_MAX_PATH);
		if (pCaption == NULL) return;
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return;
	}                  
	END_CATCH

	if(m_strMacroName.IsEmpty()) {
		if (m_strFileName.IsEmpty()) {
			if (!::LoadString (strName, IDS_UNTITLED)) return;
		}
		else 
			strName = GetFileName (m_strFileName, false);
	}
	else strName = m_strMacroName;

	if (!::LoadString (strAppName, IDS_LONGCLASSNAME)) return;
	
	wsprintf (pCaption, "%s - [%s]%s", (const char *)strAppName, 
			(const char *)strName, m_fIsDirty ? "*" : g_cbNil);
	SetWindowText (pCaption);
}

bool CBScriptDebug::SaveScript (void)	// Script speichern
{
	if (m_strFileName.IsEmpty()) 
		return SaveAs();	// erst Namen abfragen, dann sichern

return Save();		// in gegebenem Dateinamen sichern
}

// Script speichern (nur den eigentlichen Text) -------------------------------
bool CBScriptDebug::Save (void)
{
UINT iLen = m_Debug.GetTextLength() + 1; // zur Sicherheit
	if (iLen == 1) return false;

CString strText;
char *pText = NULL;

	TRY {
		pText = strText.GetBuffer (iLen);
		if (pText == NULL) return false;
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return false;
	}                  
	END_CATCH

	if (iLen != m_Debug.GetText (pText, iLen)) return false;		// aktuellen Text besorgen
	pText[iLen-1] = '\0';

// Datei erzeugen und ggf. Fehler auswerten
int fh = _lcreat (m_strFileName, 0);

	if (fh <= 0) return FileErrorMessage (IDS_CANTCREATEFILE, m_strFileName);

// Text wegschreiben, ggf. Fehler auswerten
	if (_lwrite (fh, pText, iLen) != iLen) {
		_lclose (fh);
		return FileErrorMessage (IDS_CANTWRITEFILE, m_strFileName);
	}
	_lclose (fh);
// gespeichert, dann
	m_fIsDirty = false;
	::SetFocus(m_Debug.GetWindow());	
	GenerateCaption();	// Caption richten

return true;
}

// Nur Compilierten Script speichern ----------------------------------------------
bool CBScriptDebug::SaveCodeOnly (bool fCorrectExt)
{
// Script für alle Fälle noch mal kompilieren
	if (!m_Debug.Compile())	return false;

	ebHCODE hCode = m_Debug.GetCode (false);	
	if(hCode == NULL) return false; 	

// DateiErweiterung richten
	CString strScript = fCorrectExt ? CorrectExtension (m_strFileName, IDS_COMPLIEDSCRIPTEXT)
				: m_strFileName;

	int fh = _lcreat (strScript, 0);
	if (fh <= 0) return FileErrorMessage (IDS_CANTCREATEFILE, m_strFileName);

// Header initialisieren und wegschreiben
	ebFILEHEADER Head;

	memset(&Head, 0, sizeof(Head));

	Head.wVersion = FH_VERSION;
	Head.id = FH_ID;
	Head.dwCodeSz = ebCode_GetSize(hCode);
	
	_lwrite (fh, (LPCSTR)&Head, sizeof(Head));	// Header schreiben
	
	Head.dwCode = _llseek (fh, 0L, SEEK_CUR);	// Code schreiben
	_hwrite (fh, (LPCSTR)ebCode_GetPointer(hCode), Head.dwCodeSz);
		
	_llseek (fh, 0L, SEEK_SET);
	_lwrite (fh, (LPCSTR)&Head, sizeof(Head));	// Header nochmal schreiben
	
	_lclose (fh);

return true;		
}

// Compilierten Script speichern ----------------------------------------------
bool CBScriptDebug::SaveCode (bool fCorrectExt)
{
// Script für alle Fälle noch mal kompilieren
	if (!m_Debug.Compile())	return false;

// Code vom Debugger geben lassen, dabei den Eigentümer nicht wechseln
// auf jeden Fall den Code verwenden, der keine BreakPoints enthält
ebHCODE hCode = m_Debug.GetCode (false);
	if(hCode == NULL) return false; 	

// DateiErweiterung richten
CString strScript = fCorrectExt ? CorrectExtension (m_strFileName, IDS_COMPLIEDSCRIPTEXT)
				: m_strFileName;
int fh = _lcreat (strScript, 0);

	if (fh <= 0) return FileErrorMessage (IDS_CANTCREATEFILE, m_strFileName);

int iLen = m_Debug.GetTextLength() + 5;
	if (iLen == 5) return false;

CString strText;
char *pText = NULL;

	TRY {
		pText = strText.GetBuffer (iLen);
		if (pText== NULL) return false;
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return false;
	}                  
	END_CATCH

	if (0 == m_Debug.GetText (pText, iLen)) return false;

// Header initialisieren und wegschreiben
ebFILEHEADER Head;

	Head.wVersion = FH_VERSION;
	Head.id = FH_ID;
	Head.dwCodeSz = ebCode_GetSize(hCode);
	Head.dwScriptSz = iLen;
	
	_lwrite (fh, (LPCSTR)&Head, sizeof(Head));	// Header schreiben
	
	Head.dwCode = _llseek (fh, 0L, SEEK_CUR);	// Code schreiben
	_hwrite (fh, (LPCSTR)ebCode_GetPointer(hCode), Head.dwCodeSz);
	
	Head.dwScript = _llseek (fh, 0L, SEEK_CUR);	// Script schreiben
	_hwrite (fh, pText, Head.dwScriptSz);
	
	_llseek (fh, 0L, SEEK_SET);
	_lwrite (fh, (LPCSTR)&Head, sizeof(Head));	// Header nochmal schreiben
	
	_lclose (fh);
return true;		
}

bool CBScriptDebug::SaveAs (void)	// Script unter neuem Namen speichern
{
CString strFilters; 
	if (!::LoadString (strFilters, IDS_SAVEASFILTERS)) return false;

CString strExt; 
	if (!::LoadString (strExt, IDS_SCRIPTEXT)) return false;

CFileDialog SADlg (false, strExt, GetFileName (m_strFileName, true), 
		   OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST, 
		   strFilters, this);

// Savezustand merken, SaveScript() setzt bei Export() m_fIsDirty false, 
// obwohl Storagescripte noch im Storage gespeichert werden müßten
 bool fIsDirty = m_fIsDirty;

	if (SADlg.DoModal() == IDOK) {
	CString strFile = m_strFileName;	// bisherigen Namen merken
	bool fResult = false;
		
		m_strFileName = SADlg.GetPathName();

		if (SADlg.m_ofn.nFilterIndex == 2) 
		{
			fResult = SaveCode (false);	// kompletten Script speichern (compiled)
			if (fResult) 
			{
				AddNewItem (m_pMRUMenu, m_strFileName);
				m_strFileName = CorrectExtension (m_strFileName, IDS_SCRIPTEXT);
			}
		} 
		if (SADlg.m_ofn.nFilterIndex == 3) 
		{
			fResult = SaveCodeOnly (false);	// nur Code speichern (compiled)
			if (fResult) 
			{
				AddNewItem (m_pMRUMenu, m_strFileName);
				m_strFileName = CorrectExtension (m_strFileName, IDS_COMPLIEDSCRIPTEXT);
			}
		} 
		else if (fResult = SaveScript()) 	// lediglich Text speichern
			AddNewItem (m_pMRUMenu, m_strFileName);
		
		if (fResult) {
			
			if (!m_fStorageManagement) {
				m_Debug.SetModified (false);
				m_fIsDirty = false;
			}
		// wenn Storagescripte noch nicht gespeichert wurden				
			else if (fIsDirty) 
				m_fIsDirty = true;			
		
		// MRUList behandeln
			PlaceMenuMRUItem (m_pMRUMenu, ::GetSubMenu(::GetMenu(m_hWnd), 0), IDM_CLOSE);
			
			::SetFocus(m_Debug.GetWindow());	
			GenerateCaption();	// Caption richten
		
		// set current directory
		if (!IsRemoteDir(GetPathName (m_strFileName)))
			SetCurrentDirectory (GetPathName (m_strFileName));
		
			return true;
		}
		m_strFileName = strFile;
	}
	
return false;
}

// einen neuen Script laden ---------------------------------------------------
bool CBScriptDebug::OpenNew_DB (void)
{
	TRY {
	CString strFilters; strFilters.LoadString (IDS_SAVEASFILTERS);
	CString strExt; strExt.LoadString (IDS_SCRIPTEXT);
	CFileDialog ODlg (true, strExt, NULL, 
			  OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST, 
			  strFilters, this);
	
	char cbPath[_MAX_PATH]; 
	
		if (ReadRegSettingsLastOpenFile(cbPath, _MAX_PATH)) {
			if (!IsRemoteDir(cbPath))
				SetCurrentDirectory (cbPath);
		}
	
	UINT ui = ODlg.DoModal();

		if (ui == IDOK) {
		CString strName = m_strFileName;	// nur zwischenspeichern

			m_strFileName = ODlg.GetPathName();
			if (Open()) {
			// MRUList behandeln
				AddNewItem (m_pMRUMenu, m_strFileName);
				PlaceMenuMRUItem (m_pMRUMenu, ::GetSubMenu(::GetMenu(m_hWnd), 0), IDM_CLOSE);	
				SaveRegSettingsLastOpenFile(GetPathName (m_strFileName));
			
				m_fIsDirty = true;
				m_Debug.SetModified (true);
				DeleteWatchVariables();
				GenerateCaption ();		// Caption richten		
				m_Debug.SetCaretPos (4, 3);
				::SetFocus(m_Debug.GetWindow());	
		
				return true;
			}
			m_strFileName = strName;
		}
		else if(ui == IDCANCEL)
			return true;
	} CATCH (CMemoryException, e) {
		;
	} END_CATCH;
	
return false;
}

// einen neuen Script laden ---------------------------------------------------
bool CBScriptDebug::OpenNew (void)
{
	TRY {
	CString strFilters; strFilters.LoadString (IDS_SAVEASFILTERS);
	CString strExt; strExt.LoadString (IDS_SCRIPTEXT);
	CFileDialog ODlg (true, strExt, NULL, 
			  OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST, 
			  strFilters, this);
	
	char cbPath[_MAX_PATH]; 
	
		if (ReadRegSettingsLastOpenFile (cbPath, _MAX_PATH)) {
			if (!IsRemoteDir(cbPath))
				SetCurrentDirectory (cbPath);
		}

	UINT ui = ODlg.DoModal();

		if (ui == IDOK) {
		CString strName = m_strFileName;	// nur zwischenspeichern

			m_strFileName = ODlg.GetPathName();
//			m_strFileName.MakeUpper();

			if (Open()) {
			// MRUList behandeln
				AddNewItem (m_pMRUMenu, m_strFileName);
				PlaceMenuMRUItem (m_pMRUMenu, ::GetSubMenu(::GetMenu(m_hWnd), 0), IDM_CLOSE);
				SaveRegSettingsLastOpenFile(GetPathName (m_strFileName));
	
				m_fIsDirty = false;
				m_Debug.SetModified (false);
				DeleteWatchVariables();
				GenerateCaption ();		// Caption richten		
				m_Debug.SetCaretPos (4, 3);
				::SetFocus(m_Debug.GetWindow());	

				return true;
			}
			m_strFileName = strName;
		}
		else if(ui == IDCANCEL)
			return true;
	} CATCH (CMemoryException, e) {
		;
	} END_CATCH;
		
return false;
}

// Datei aus MRUListe laden ---------------------------------------------------
bool CBScriptDebug::OpenFromMRU (UINT uiID)
{
CString strName = m_strFileName;	// nur zwischenspeichern
char *pFileName = NULL;

	TRY {
		pFileName = m_strFileName.GetBuffer (_MAX_PATH);
		if(pFileName == NULL) return false; 
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return false;
	}                  
	END_CATCH

	GetMenuItem (m_pMRUMenu, uiID, true, pFileName, _MAX_PATH);
	m_strFileName.ReleaseBuffer();

	if (!Open()) {		// nicht erfolgreich geladen
		DelMenuItem (m_pMRUMenu, uiID, true);
		m_strFileName = strName;
		return false;
	}

// refresh MRUMenu
	PlaceMenuMRUItem (m_pMRUMenu, ::GetSubMenu(::GetMenu(m_hWnd), 0), IDM_CLOSE);
	
	if (m_fStorageManagement) {
		m_fIsDirty = true;
		m_Debug.SetModified (true);
	} else {
		m_fIsDirty = false;
		m_Debug.SetModified (false);
	}

	DeleteWatchVariables();
	GenerateCaption ();		// Caption richten		
	m_Debug.SetCaretPos (4, 3);
	::SetFocus(m_Debug.GetWindow());	
	
return true;
}

// Datei laden ----------------------------------------------------------------
bool CBScriptDebug::Open (void)
{
int fh = _lopen (m_strFileName, OF_READ);

	if (fh <= 0) return FileErrorMessage (IDS_CANTOPENFILE, m_strFileName);

ebFILEHEADER Head; 
int iBytes = _lread (fh, (LPSTR)&Head, sizeof(Head));
bool fResult = false;

	if(m_hCode) CoTaskMemFree (m_hCode);
	m_hCode = NULL;
	
	if (iBytes == sizeof(Head) && 
	    Head.id == FH_ID && Head.wVersion == FH_VERSION)
		fResult = LoadCode (fh, Head);
	else
		fResult = LoadScript (fh);
		
	_lclose (fh);
	
// set current directory
	if (!IsRemoteDir(GetPathName (m_strFileName)))
		SetCurrentDirectory (GetPathName (m_strFileName));

return fResult;
}

// Script als Textdatei einlesen ----------------------------------------------
bool CBScriptDebug::LoadScript (int fh)
{
	ASSERT(m_hCode==NULL);

LONG lBytes = _llseek (fh, 0L, SEEK_END);	// DateiGröße feststellen

	if (lBytes > MAXTEXT) {
		FileErrorMessage (IDS_FILETOLARGE, m_strFileName);
		lBytes = MAXTEXT;
	}

UINT iLen = (UINT)lBytes;
CString strText;
char *pText = NULL;

	TRY {
		pText = strText.GetBuffer (iLen);
   		if (pText == NULL) return false; 
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return  false;
	}                  
	END_CATCH

	_llseek (fh, 0L, SEEK_SET);		// an  Anfang positionieren
	if (iLen != _lread (fh, pText, iLen)) return false;
	pText[iLen-1] = '\0';
		
	m_Debug.SetText (pText);
	m_Debug.SetCode (NULL);

	AddNewItem (m_pMRUMenu, m_strFileName);
	
return true;
}

// Compilierten Script laden --------------------------------------------------
bool CBScriptDebug::LoadCode (int fh, ebFILEHEADER &rHead)
{
	ASSERT(m_hCode == NULL);

LPVOID lpCode = CoTaskMemAlloc(rHead.dwCodeSz);
	if(lpCode == NULL) { AfxMessageBox(IDS_NOMEMORY); return false; }

CString strText;
char *pText = NULL;

	TRY {
		pText = strText.GetBuffer ((int)rHead.dwScriptSz);
		if (pText == NULL) return false; 
   	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return false;
	}                  
	END_CATCH
	
	_llseek (fh, rHead.dwCode, SEEK_SET);
	if (_hread (fh, lpCode, rHead.dwCodeSz) != (LONG)rHead.dwCodeSz) {
		CoTaskMemFree(lpCode); lpCode = NULL;
		return FileErrorMessage (IDS_CANTREADFILE, m_strFileName);
	}
	
	_llseek (fh, rHead.dwScript, SEEK_SET);
	if (_lread (fh, pText, (UINT)rHead.dwScriptSz) != (UINT)rHead.dwScriptSz) {
		CoTaskMemFree(lpCode); lpCode = NULL; 
		return FileErrorMessage (IDS_CANTREADFILE, m_strFileName);
	}
	
	m_hCode = ebCode_Create(lpCode);
	
	m_Debug.SetText (pText);
	m_Debug.SetCode (m_hCode);
	
	AddNewItem (m_pMRUMenu, m_strFileName);
	
	m_strFileName = CorrectExtension (m_strFileName, IDS_SCRIPTEXT);

return true;
}                                                                               

bool FileErrorMessage (UINT uiResID, CString &rstrFileName)
{
CString strPrompt;
CString strOut;
char *pOut = NULL;

	TRY {
		pOut = strOut.GetBuffer (_MAX_PATH);
   		if (pOut == NULL) return false;
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return  false;
	}                  
	END_CATCH

	if (!::LoadString (strPrompt, uiResID)) return false;

	wsprintf (pOut, strPrompt, rstrFileName);
	AfxMessageBox (pOut, MB_OK|MB_ICONEXCLAMATION);
	strOut.ReleaseBuffer();

return false;		// liefert immer false
}

bool CBScriptDebug::SetParams (int iNumParams, BSPARAM *pPars)
{
	if (m_iNumParams) return false;		// nur einmal zulassen
	m_iNumParams = iNumParams;
	m_pPars = pPars;

return true;
}

void CBScriptDebug::ResetParams (void)
{
	m_iNumParams = 0;
	m_pPars = NULL;
}

// Script speichern  -------------------------------
bool CBScriptDebug::SaveScript_InDB (bool fTextOnly)
{
	ASSERT(m_strMacroName.GetLength()>0);

DWORD dwSaveFlag = CC_SCRIPT;
ebHCODE hCode = NULL;

// Script für alle Fälle noch mal kompilieren, Laufzeitfehler ?	
	if (fTextOnly) {
		dwSaveFlag = CC_SCRIPT;
	}
	else if (m_Debug.Compile()) {
		hCode = m_Debug.GetCode (false); 
		if (NULL == hCode) return false;
		dwSaveFlag = CC_ALL;
	}

	try {
	// aktuellen Text besorgen
	WScriptContainer IScriptContainer (m_pMacroScripts);	// throws hr
	UINT iLen = m_Debug.GetTextLength() + 1;
		
		if (iLen == 1) return false;

	LPSTR pText = (LPSTR) CoTaskMemAlloc(iLen);
		
		if  (pText == NULL)	return false;

		iLen = m_Debug.GetText (pText, iLen);
		if (0 == iLen) return false;

	// in  STREAM speichern	
	HRESULT hr = IScriptContainer -> SetScript (m_strMacroName, pText, hCode, dwSaveFlag);
	
		if (pText) CoTaskMemFree (pText); pText = NULL; 
		if (FAILED(hr)) return false; 

	} catch (HRESULT) {
		return false;
	}

	m_fIsDirty = false;
	m_Debug.SetModified(false);
	GenerateCaption();

// Speichern beendet, aber noch COMMIT()
	DEX_SetDirtyGeoDB(true);

return true;
}

bool CBScriptDebug::OpenStream (LPSTR pcMacroName)
{
/*** nur einmal !!! ***/
	ASSERT (NULL != pcMacroName);
	if (NULL == pcMacroName) return false;		   
	
	m_strMacroName = pcMacroName;

IScriptContainer *pIScriptContainer = NULL;
HRESULT hr = m_pMacroScripts -> QueryInterface (IID_IScriptContainer, (LPVOID *)&pIScriptContainer);
	
	if (FAILED(hr)) return false;  

// Text aus geöffnetem STREAM lesen oder neuen STREAM anlegen, *** m_hCode später SELBST freigeben !!! ***
char *pMakroText = NULL;
	
	hr = pIScriptContainer -> GetScript (m_strMacroName, &pMakroText, &m_hCode);
	pIScriptContainer -> Release();	
	if (FAILED(hr)) return false;  
	
	if (GetScode(hr) == S_FALSE) {
		if(!InitNewScript(false)) return false; 
		m_fInitNew = true;
// soll heißen: Neues Script, wenn nicht verändert, dann nicht speichern
	}
	else {
		InitScript (pMakroText);
		if (pMakroText) CoTaskMemFree (pMakroText);
		pMakroText = NULL;
		m_fInitNew = false;
	}

	m_fIsDirty = false;

return true;
}
	
void CBScriptDebug::InitScript (char *pc)
{	
	ASSERT(pc);
	ASSERT(!m_strMacroName.IsEmpty());

	if (m_Debug.SetText (pc) == false) return; 
	m_Debug.SetCode (m_hCode);

	m_fIsDirty = false;
	m_Debug.SetModified (false);
	m_Debug.SetCaretPos (0, 0);
	DeleteWatchVariables();
	GenerateCaption ();
	::SetFocus(m_Debug.GetWindow());	
}	

bool CBScriptDebug::InitNewScript(bool fIsDirty)
{
CString strDefaultScr; 
	if (!::LoadString (strDefaultScr, IDS_DEFAULTSCRIPT)) return false;
	
	m_Debug.SetText (strDefaultScr);
	m_Debug.SetCode (NULL);	// alten Code löschen
	
	m_fIsDirty = fIsDirty;
	m_Debug.SetModified (fIsDirty);
	m_Debug.SetCaretPos (4, 3);
	DeleteWatchVariables();
	m_strFileName.Empty();
	GenerateCaption ();		// Caption richten		
	
	::SetFocus(m_Debug.GetWindow());	

return SetEntryPointLoadScript();
}

HRESULT CBScriptDebug::DeleteFromEnum ()
{
IScriptContainer *pIScriptContainer = NULL;
HRESULT hr = m_pMacroScripts -> QueryInterface (IID_IScriptContainer, (LPVOID *)&pIScriptContainer);	
	if (FAILED(hr)) return hr;

	hr = pIScriptContainer -> DelScript (m_strMacroName);
	pIScriptContainer -> Release();	

return hr;
}

bool CBScriptDebug::AskSave(bool fInitNew)
{
	if (m_fIsDirty) {

		if (m_fStorageManagement) {
			switch (AskSaveChanges_DB()) {
			case IDYES:
			// noch geöffnetes Script speichern , noch nicht COMMIT()
				if ( !SaveScript_InDB(false) ) return true;
				m_fInitNew = false;
				fInitNew = false;
				break;		
			case IDCANCEL:
				return true;
				break;
			case IDNO:
				break;// weiter bis return false
			default:
				break;
			}
		} else {
			switch (AskSaveChanges()) {
			case IDYES:
				SaveScript();
				return false;
				break;				
			case IDCANCEL:
				return true;
			}
		}
// nicht dirty, aber neu
	}
	
	if (fInitNew) {
	
	HRESULT hr = DeleteFromEnum();
		if (FAILED(hr)) return true;
	}

return false;
}

int CBScriptDebug::AskSaveChanges (void)
{
CString strPrompt, strTemplate;
char *pPrompt = NULL;

	TRY {
		pPrompt = strPrompt.GetBuffer (_MAX_PATH);
		if (pPrompt == NULL) return 0;
   	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return  0;
	}                  
	END_CATCH

	if (m_strFileName.IsEmpty()) {
		if (!::LoadString (strTemplate, IDS_SAVEPROMPTUNTITLED)) return 0;
		strcpy (pPrompt, strTemplate);
	int iLen = strTemplate.GetLength();
		pPrompt[iLen+1] = '\0';					   
	} else {
		if (!::LoadString (strTemplate, IDS_SAVEPROMPT)) return 0;
		wsprintf (pPrompt, strTemplate, m_strFileName);
	}
	
return AfxMessageBox (pPrompt, MB_YESNOCANCEL | MB_TASKMODAL);
}

int CBScriptDebug::AskSaveChanges_DB (void)
{
CString strPrompt, strTemplate;
char *pPrompt = NULL;
	
	TRY {
		pPrompt = strPrompt.GetBuffer (_MAX_PATH);
		if (pPrompt == NULL) return 0;
   	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return  0;
	}                  
	END_CATCH

	if (m_strMacroName.IsEmpty()) {
		strTemplate.LoadString (IDS_SAVEPROMPTUNTITLED);
		strcpy (pPrompt, strTemplate);
	int iLen = strTemplate.GetLength();
		pPrompt[iLen+1] = '\0';					   
	} else {
		strTemplate.LoadString (IDS_SAVEPROMPTSTORAGE);
		wsprintf (pPrompt, strTemplate, m_strMacroName);
	}
	
return AfxMessageBox (pPrompt, MB_YESNOCANCEL | MB_TASKMODAL);
}

//
// *** Hilfe ***
//
HRESULT CBScriptDebug::LookupKeyword(LPCSTR lpKeyWord, int & id)
{
LPSTR lpszTemplateName = MAKEINTRESOURCE(AZ_KEYWORDS);
HANDLE hMem = NULL;
HINSTANCE hInst = NULL;
HRSRC hResource = NULL;

	// find the resrouce in my EXE
	hInst = AfxFindResourceHandle(lpszTemplateName, RT_RCDATA);
	if (hInst == NULL) return ResultFromScode(E_HANDLE);

	hResource = ::FindResource(hInst, lpszTemplateName, RT_RCDATA);

DWORD dwE = GetLastError();

	if (hResource == NULL) return ResultFromScode(E_HANDLE);
	
	// allocate memory for it and load it in
	hMem = LoadResource(hInst, hResource);
	if (hMem == NULL) return ResultFromScode(E_HANDLE);

BYTE FAR *lpMem;
char buf[80];

	// lock it
	lpMem = (BYTE FAR *)LockResource(hMem);

	id = -1;

	// get the default ID, in the case that the keyword isn't found
	id = *lpMem++;			// watch out for alignment!
	id |= *lpMem++ << 8;

	while (*lpMem) {
	
		strcpy(buf,(LPCSTR)lpMem);

		while (*lpMem) lpMem++;
		lpMem++;	// skip to ID

		if (!strcmpi(lpKeyWord, buf)) {
			// save the id for returning to caller
			id = *lpMem++;			// watch out for alignment!
			id |= *lpMem << 8;
			break;
		}
		else {
			// skip the id
			lpMem += sizeof(WORD);
		}
	}

	// get rid of the resource (it may hang around a while)
	UnlockResource(hMem);
	FreeResource(hMem);

return NOERROR;	// return id to caller
}

HRESULT CBScriptDebug::KeywordHelp(LPCSTR lpKeyWord)
{
CString strPath;
HRESULT hr = GetHelpFile(strPath, g_cbAZHelp);
	if (FAILED(hr)) return hr;

int id = -1;
	hr = LookupKeyword(lpKeyWord, id);
	if (SUCCEEDED(hr)) {
		if (!::WinHelp(m_hWnd, strPath, HELP_CONTEXT, id)) {
			ASSERT(0); return ResultFromScode(E_FAIL);
		}
	}
	else {
		if (!::WinHelp(m_hWnd, strPath, HELP_CONTENTS, 0L)) {
			ASSERT(0); return ResultFromScode(E_FAIL);
		}
	}

return NOERROR;
}

HRESULT CBScriptDebug::DebuggerHelp()
{
CString strPath;
HRESULT hr = GetHelpFile(strPath, g_cbDDHelp);
	if (FAILED(hr)) return hr;

	if (!::WinHelp(m_hWnd, strPath, HELP_CONTENTS, 0L)) {
			ASSERT(0); return ResultFromScode(E_FAIL);
	}

return NOERROR;
}

HRESULT CBScriptDebug::TriasHelp()
{
CString strPath;
HRESULT hr = GetHelpFile(strPath, g_cbMPHelp);
	if (FAILED(hr)) return hr;

	if (!::WinHelp(m_hWnd, strPath, HELP_CONTENTS, 0L)) {
			ASSERT(0); return ResultFromScode(E_FAIL);
	}

return NOERROR;
}

HRESULT CBScriptDebug::GetHelpFile(CString & strPath, LPCSTR pcFileName)
{
CString strName;
LPSTR pcStartupDir = strName.GetBuffer(MAXSTRLENGTH); 

	GetModuleFileName(NULL, pcStartupDir, MAXSTRLENGTH);	
	strPath = GetPathName(strName) + g_cbDel + pcFileName;

return NOERROR;
}

//
// *** BreakFlag abfragen ***
//

LONG CBScriptDebug::GetBreakFlag()
{
	if (m_fRunModal) return 1;

HWND hWnd = m_Debug.GetWindow();
	ASSERT(hWnd);
	if (hWnd == NULL) return -1;

ebHTHREAD hThread =	ebDebugger_GetThread(hWnd, false);
	ASSERT(hThread);
	if (hThread == NULL) return -1;

return ebThread_GetLong(hThread, 0);
}

HRESULT CBScriptDebug::RunModal ()
{
// jetzt, wo alles fertig ist, anzeigen
	Stop();		// UI richten, so tun, als ob angehalten wäre (stimmt ja auch)

	ShowWindow (SW_SHOWNORMAL);
	UpdateWindow();

DWORD dwFlags = MLF_SHOWONIDLE;
	
	if (GetStyle() & DS_NOIDLEMSG)
		dwFlags |= MLF_NOIDLEMSG;

	m_fRunModal = true;
	RunModalLoop(dwFlags);

// Zum endgültigen Schliessen des Debuggers während Running	
	if (m_fClose) {
		return E_ABORT;
	}
// Zum Schliessen des Debuggers bei RunTimeError 
	else if (m_fRunError) {
		return E_UNEXPECTED;
	}

return NOERROR;
}

HRESULT CBScriptDebug::RunMain(int iKindOfProcess)
{
	if (false == m_fMainIsRun) return S_FALSE;

	// "Main()" als Entry setzen, ausnullen
	ResetEntryInfo();

ebHCODE hCode = NULL;
	
	hCode = m_Debug.GetCode(false);	
	ASSERT(NULL != hCode);

	if (ebCheckEntry(hCode, m_EInfo.GetEntryInfo())) {
		m_fLoadIsRun = false;
		m_fMainIsRun = false;
		m_fUnLoadIsRun = true;
		return S_FALSE;
	}


	if (TRACEINTO == iKindOfProcess) {
		m_Debug.TraceInto();
	} else if (TRACEOVER == iKindOfProcess) {
		m_Debug.StepOver();
	} else if (GO == iKindOfProcess) {
		m_Debug.StartScript();
	}

return NOERROR;
}

HRESULT CBScriptDebug::RunScript(int iKindOfProcess)
{
HRESULT hr = NOERROR;

	hr = RunLoadScript(iKindOfProcess);
	if (FAILED(hr)) return hr;
	hr = RunMain(iKindOfProcess);
	if (FAILED(hr)) return hr;

// "m_fBreakSet" vorher schon in entweder StartScript() oder Main() gemerkt !!!
	OnEndScript(0,iKindOfProcess);

return NOERROR;
}

HRESULT CBScriptDebug::RunLoadScript(int iKindOfProcess)
{
	if (false == m_fLoadIsRun) return S_FALSE;

	if (!SetEntryPointLoadScript()) 
		return E_FAIL;
	
ebHCODE hCode = NULL;
	
	hCode = m_Debug.GetCode(false);	
	ASSERT(NULL != hCode);

	if (ebCheckEntry(hCode, m_EInfo.GetEntryInfo())) {
		m_fLoadIsRun = false;
		m_fMainIsRun = true;
		m_fUnLoadIsRun = false;
		return S_FALSE;
	}

	if (TRACEINTO == iKindOfProcess) {
		m_Debug.TraceInto();
	} else if (TRACEOVER == iKindOfProcess) {
		m_Debug.StepOver();
	} else if (GO == iKindOfProcess) {
		m_Debug.StartScript();
	}

return NOERROR;
}

HRESULT CBScriptDebug::RunUnLoadScript(int iKindOfProcess)
{	
	if (false == m_fUnLoadIsRun) return S_FALSE;

	if (!SetEntryPointUnLoadScript()) return E_FAIL;

ebHCODE hCode = NULL;
	
	hCode = m_Debug.GetCode(false);	
	ASSERT(NULL != hCode);

	if (ebCheckEntry(hCode, m_EInfo.GetEntryInfo()) ||
		false == m_fUnLoadIsRun ||
		FAILED(GetMethodType())) { 
		m_fLoadIsRun = true;
		m_fMainIsRun = false;
		m_fUnLoadIsRun = false;
		return S_FALSE;
	}
	
	if (TRACEINTO == iKindOfProcess) {
		m_Debug.TraceInto();
	} else if (TRACEOVER == iKindOfProcess) {
		m_Debug.StepOver();
	} else if (GO == iKindOfProcess) {
		m_Debug.StartScript();
	}


	return NOERROR;
}

bool CBScriptDebug::ResetEntryInfo()
{
CString str;

	if (!LoadString(str, IDS_MAIN)) return false;

	m_EInfo.SetEntryName(str); // "Main()"
	m_EInfo.GetEntryInfo() -> dwEntry = 0;
	m_EInfo.GetEntryInfo() -> wParms = 0;
	m_EInfo.GetEntryInfo() -> lpParms = NULL;
	m_EInfo.GetEntryInfo() -> RetParm.wType = 0;
	m_EInfo.GetEntryInfo() -> isFunc = 0;	// Sub and not a Function
	
	m_Debug.SetEntryPoint (m_EInfo.GetEntryInfo());	

return true;
}

bool CBScriptDebug::SetEntryPointLoadScript()
{
HRESULT hr = NOERROR;
CString str;

	if (!ResetEntryInfo()) return false;
	if (!LoadString(str, IDS_LOADSCRIPT)) return false;

	m_EInfo.SetEntryName(str);	
	m_Debug.SetEntryPoint (m_EInfo.GetEntryInfo());	

return true;
}

bool CBScriptDebug::SetEntryPointUnLoadScript()
{
HRESULT hr = NOERROR;
CString str;

	if (!ResetEntryInfo()) return false;
	if (!LoadString(str, IDS_UNLOADSCRIPT)) return false;

	m_EInfo.SetEntryName(str);
	m_Debug.SetEntryPoint (m_EInfo.GetEntryInfo());	

return true;
}

bool CBScriptDebug::FilterMessageBox(int iIDS1)
{
CString str, strClN;
	if (!LoadString(str, iIDS1) ||
		!LoadString(strClN, IDS_LONGCLASSNAMEFILTERSCRIPT)) 
	{
		return false;
	}
	MessageBox(str, strClN, MB_ICONEXCLAMATION);
return true;
}

bool CBScriptDebug::GetWhichEntryMayRun()
{
	if (m_fRunModal) 
		return true;

char EntryName[MAXSTRLENGTH];
CString strLoad, strUnload, strMain;
	if (!LoadString(strLoad, IDS_LOADSCRIPT) ||
		!LoadString(strUnload, IDS_UNLOADSCRIPT) ||
		!LoadString(strMain, IDS_MAIN)) {
		return false;
	}

	m_EInfo.GetEntryName(EntryName);

	if (0 == strcmp(EntryName, strLoad)) {
		m_fLoadIsRun = false;
		m_fMainIsRun = true;
		m_fUnLoadIsRun = false;
	} else if (0 == strcmp(EntryName, strMain)) {
		m_fLoadIsRun = false;
		m_fMainIsRun = false;
		m_fUnLoadIsRun = true;
		// nur einmal für alle nach Speichern fragen
		m_fAskSave = false;
	} else if (0 == strcmp(EntryName, strUnload)) {
		m_fLoadIsRun = true;
		m_fMainIsRun = false;
		m_fUnLoadIsRun = false;
	}

return true;
}

void CBScriptDebug::DisableToolbarVirtualRun()
{	
	if (true == m_fBreakSet) return;

	m_wndToolBar.Disable (ID_DEBUG_GO);
	m_wndToolBar.Disable (ID_DEBUG_CALLSTACK);
	m_wndToolBar.Disable (ID_DEBUG_TRACEIN);
	m_wndToolBar.Disable (ID_DEBUG_TRACEOVER);	
	m_wndToolBar.Disable (ID_DEBUG_OPEN);
	m_wndToolBar.Disable (ID_DEBUG_IMPORT);
	m_wndToolBar.Disable (ID_DEBUG_CUT);
	m_wndToolBar.Disable (ID_DEBUG_PASTE);
	m_wndToolBar.Disable (ID_DEBUG_UNDO);
	m_wndToolBar.Disable (ID_DEBUG_REPLACE);
	m_wndToolBar.Disable (ID_DEBUG_DELETE);
	m_wndToolBar.Disable (ID_DEBUG_ADDWATCH);
	m_wndToolBar.Disable (ID_DEBUG_SYNTAX);

	m_wndToolBar.Enable (ID_DEBUG_SUSPEND);

	m_wndToolBar.Repaint();
} 

void CBScriptDebug::EnableToolbarVirtualRun()
{	
	m_wndToolBar.Enable (ID_DEBUG_GO);
	m_wndToolBar.Enable (ID_DEBUG_CALLSTACK);
	m_wndToolBar.Enable (ID_DEBUG_TRACEIN);
	m_wndToolBar.Enable (ID_DEBUG_TRACEOVER);	
	m_wndToolBar.Enable (ID_DEBUG_OPEN);
	m_wndToolBar.Enable (ID_DEBUG_IMPORT);
	m_wndToolBar.Enable (ID_DEBUG_CUT);
	m_wndToolBar.Enable (ID_DEBUG_PASTE);
	m_wndToolBar.Enable (ID_DEBUG_UNDO);
	m_wndToolBar.Enable (ID_DEBUG_REPLACE);
	m_wndToolBar.Enable (ID_DEBUG_DELETE);
	m_wndToolBar.Enable (ID_DEBUG_ADDWATCH);
	m_wndToolBar.Enable (ID_DEBUG_SYNTAX);

	if (m_Debug.GetState() == ES_SUSPENDED)
		m_wndToolBar.Enable (ID_DEBUG_SUSPEND);
	else 
		m_wndToolBar.Disable (ID_DEBUG_SUSPEND);

	m_wndToolBar.Repaint();
}

bool CBScriptDebug::BreakSet(LPCSTR pEntryName)
{
	if (m_fRunModal) 
		return true;

CString strLoad, strUnload, strMain;
	if (!LoadString(strLoad, IDS_LOADSCRIPT) ||
		!LoadString(strMain, IDS_MAIN)) {
		return false;
	}

	if (!m_fBreakSet && 
		(0 == strcmp(pEntryName, strLoad) || 0 == strcmp(pEntryName, strMain))) {
		DisableToolbarVirtualRun();
		return true;
	} else {
		m_fOtherFunction = true;
		EnableToolbarVirtualRun();
		return true;
	}
 
return true; 
}

bool CBScriptDebug::BreakReset()
{
	if (m_fRunModal) 
		return true;
	
	// Main() und StartScript() schon glaufen ?, 
	// dann "m_fBreakSet" setzen und OnEndScript() rufen
	if (m_fUnLoadIsRun) {
		if (false == m_fOtherFunction)
			return true;
		PostMessage(uiWM_EndScript, 0, GO);
	}
	m_fOtherFunction = false;

return true; 
}

LRESULT CBScriptDebug::OnEndScript(WPARAM wParam, LPARAM lParam)
{
HRESULT hr = NOERROR;

	if (!m_fBreakSet) {
		DisableToolbarVirtualRun();
	} else {
		hr = RunUnLoadScript(lParam);
		ASSERT(E_FAIL != hr);
		if (FAILED(hr)) return 0;

		EnableToolbarVirtualRun();
	}

return 1;
}

// darf NUR bei Unload() gerufen werden !!!
HRESULT CBScriptDebug::GetMethodType()
{
ebHCODE hCode = m_Debug.GetCode();
	ASSERT(NULL != hCode);

ebPROCINFO PI;
ebBOOL fNext = true;

ebHENUM hEnum = ebGetFirstProc(hCode, &PI);
	
	if (hEnum == NULL) return E_FAIL;

CString strUnLoad;
		
	if (!LoadString(strUnLoad, IDS_UNLOADSCRIPT))
		return E_FAIL;

	while (fNext) {
		if (0 == strcmp (strUnLoad, PI.szName)) {
			if (1 == PI.wType) {
				ebEnumClose(hEnum);
				return E_FAIL;
			}
		}
		fNext = ebGetNextProc(hEnum, &PI);
	}		
	
	ebEnumClose(hEnum);

return NOERROR;
}

bool IsRemoteDir(LPCSTR cbPath)
{
LPSTR lpstr = (LPSTR)cbPath;
	if (*lpstr == '\\') {
		if (*(++lpstr) == '\\')
			return true;
	}

return false;
}