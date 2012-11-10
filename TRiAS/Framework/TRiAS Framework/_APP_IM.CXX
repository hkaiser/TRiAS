/* $Header:   G:/cv.win/pvcs/commonvu/src/_app_im.cxv   3.0.1.0   14 Jul 1992 11:48:12   RONAN  $
 *
 *	_ a p p . c x x
 *
 *  Copyright (c) 1992 Trischford Limited 
 *  ( A wholly owned subsidary of Computer Associates International, Inc)
 *  All Rights Reserved
 *
 *	Version 3.1			Nov 1992
 *
 *	Mods log:
 *	0.0	ferg	05oct88	-------- Milestone 2 Beta 2 .. shipped. --------
 *	0.1	ferg	02nov88	delete entry from dynalink registered task LIST.
 *	0.2 ferg	02nov88	App::App() moved here from app.cxx + minor change
 *						to get App pointer from DLL dataseg. App.cxx now 
 *						defunct.
 *	0.3	ferg	08nov88	initialize CVSflg and DlgDispatch in App.
 *	0.4 jk		29nov88	------ Milestone 2A. Beta 2A shipped. ------
 *	0.5 jk		02dec88	Fast Compile defines added.
 *  0.6 rs      22jan89 Extensions for accelerators
 *  0.7 rs      22feb89 Changes for PM compatible mapping modes
 *  1.0 rs		29mar89 -------Release 1.0 ship date ----------------
 *  1.1 rs		07jul89 -------Release 1.0a ship date ---------------
 *	1.2 rs		12jul89 Modifications for modeless dialog boxes
 *  1.3 rs		04oct89 Temporary fix for modeless dialog boxes. 
 *						In debugging versions of windows IsDialogMessage 
 *						causes a crash in certain circumstances. This
 *						fix disables the offending code in debugging versions.
 *	1.4	rs		10oct89	Idle support
 *	1.5 rs		15Nov89	Removed App:: CmdLine, App::sCmd and associated functions
 *	1.6 rs		02jan90	Provision of correct dereferencing and cleanup of
 *						strings used by CA-CommonView programs.
 *	1.7 rs		03Jan89	Flagging of windows to support correct style updating.
 *						Also WndFlags is now used to indicate whether window
 *						is a ModeLessDialog or a DeleteWindow.
 *	1.8 rs		19Jan89 Support for re-entrant App :: Exec.
 *						This is to support nested exec's such as used by 
 *						Dialog::Show.
 *	1.9 hl		08Feb90 Initialize WindowCount in the construstor
 *	1.10 rs		20Feb90 Initialise hModelessDlg for EVERY iteration of 
 *						message loop.
 *	1.11 rs		16May90 Setup ds for use in dispatcher
 *	2.0 rs		19Jun90 rs from nc Apr90 - Hiding
 *	2.1 rs		31Oct90 Allow Exec to be triggered to run until no messages
 *	2.2 rs		20Nov90 Handle help keys and accelerators
 *	2.3	sm		15May91 MDI support
 */

#include "tfrmpre.hxx"
#include	<_Link.hxx>
#include 	<_dsfix.hxx>

#ifdef NEWWAVE
#define MAXROOTFILENAMELENGTH	80	/* d: + (Path-null) + \ + 8.3 + null*/
#define MAXTITLE	32				/* 32 */
#endif

/*********************************************************************
 * The following code needs to be upgraded for MultiByte character sets
 *********************************************************************/

static char * SkipSpace(char * s)
{
	while ((*s == ' ') || (*s == '\t'))
			s++;
	return s;
}

static int LengthArg(char *s)
{
int len = 0;

	if ('\"' == *s || '\'' == *s) {		// Compound argument
	char cScope = *s++;

		len++;
		while (*s && (*s != cScope))
			s++, len++;
		if (cScope == *s)
			s++, len++;
	} else {
		while (*s && (*s != ' ') && (*s !='\t'))
			s++, len ++;
	}

return len;
}

static int CountArgs(char *s)
{
	int result = 0;
	do {
	   s = SkipSpace(s);
	   if (*s)
	   		{
			result ++;
			s += LengthArg(s);
			}
	   }
	while (*s);
	return result;
}

void App_Imp:: ParseArgs ()
{
// Set up initial argument
char buffer[256];

	GetModuleFileName(hApp, buffer, 256);

int len = CV_strlen(buffer);
int argnum = 0;

	argc = CountArgs(Commandl) + 1;

// allocate space for args 
// Space is argcount + 1 * char *  - pointer storage
// len + 1 for argv[0] storage
// length of command line + 2 for argument storage

	argv = (char**) new char[ (argc+1) * sizeof(char*) + len + CV_strlen(Commandl) + 2];

// Set up argv[0] - application name
	argv[argnum] = ((char*)(&argv[argc+1])); 
	CV_strcpy(argv[argnum], buffer);

char * bptr = argv[argnum]+ len + 1;
char * cptr = Commandl;

// Get remaining arguments
	while((++argnum < argc) && *cptr) {
		argv[argnum] = bptr;

		cptr = SkipSpace(cptr);
	
	int lenarg = LengthArg(cptr);

	// Copy argument, update pointers and put in terminating NULL
	int fFoundScope = false;

		if ('\"' == *cptr || '\'' == *cptr) {
		char cScope = *cptr;

			cptr++;
			lenarg--;
			if (cScope == *(cptr+lenarg-1)) {
				lenarg--;
				fFoundScope = true;
			}
		}

		CV_strncpy (bptr, cptr, lenarg);
		cptr += lenarg;
		if (fFoundScope) cptr++;
		bptr += lenarg;
		*bptr = '\0';
		bptr++;
	}
	argv[argnum] = (char*)0;
}		
	
void App_Imp :: InitColors()
{
COLORREF newBackColor = (GetSysColor (COLOR_WINDOW)) & 0x00ffffffL;

	TextColor = (GetSysColor(COLOR_WINDOWTEXT)) & 0x00ffffffL;
	if (newBackColor != BackColor) {
		if (DefBackBrush)
			DeleteObject (DefBackBrush);
		DefBackBrush = CreateSolidBrush (BackColor = newBackColor);
	}
}
		  
App_Imp::  App_Imp (App * pReq, uint seg, HINSTANCE hInst, HINSTANCE hPrev, const char* CmdL, int scmd)
{
#if defined(WIN32)
	m_pPreTranslateMsgProc = NULL;
	m_pIdleProc = NULL;

	m_pCM = NULL;
	m_dwDataCM = 0L;
#endif // WIN32

	pRequestor = pReq;

DS_segment = seg; 	// * 1.11 *

	AppScreenSize = Dimension( GetSystemMetrics (  SM_CXSCREEN ),      // * 0.7 *
        GetSystemMetrics ( SM_CYSCREEN ));
	IdleStatus	= IdleFirstTime;	// Non - idling exec loop * 1.4 *
	WindowCount = 0;		// * 1.9 *
	MDIClientHandle = LastDlgHandle = 0;

	hApp		= hInst;
	hPrevInst	= hPrev;
	Commandl = CV_strdup(CmdL);
	ParseArgs();

	IdleFunc = 0;
	status = scmd;

	hHelpWnd = 0; 	// * 2.2  *
	hHelpAccel = 0;
	hWndAccel = 0;
	hAccelRecv = 0; 

	m_ptCursorLast.x = 0;			// #HK960229
	m_ptCursorLast.y = 0;
	m_nMsgLast = 0;

	DlgDispatch = (FARPROC)DialogDispatcher;
	EvtDispatch = (FARPROC)EventDispatcher;

	// Initialise colors for Color Management
	DefBackBrush = 0;
	BackColor = 0;
	TextColor = 0;
	InitColors();

	m_fQuitOnLast = true;

	ResourceList() -> LockOrder (true);	// Reihenfolge in ResourceListe ist fest

}	// End of "App_Ip" CONSTRUCTOR "(HANDLE,HANDLE,const char*,int)"

class CSaveCursor
{
private:
	HCURSOR m_hCursor;

public:
	CSaveCursor() { m_hCursor = ::GetCursor(); }
	~CSaveCursor() { ::SetCursor (m_hCursor); }
};

int	App_Imp::Exec (BOOL **ppac, ExecType et, CONTINUEMODALPROC pCM, DWORD dwDataCM)	// * 2.1 *
{
volatile BOOL		active = TRUE;		// wird von außen rückgesetzt !!
BOOL			nested;
MSG				msg;
int 			retval = 0;
CSaveCursor Save;

// Set up nested context information

	if (ppac) {
		(*ppac) = (BOOL *)&active;	// über diesen Pointer wird's rückgesetzt
		nested = TRUE; 
	}
	else
		nested = FALSE;

// hier den evtl. aktiven ContinueModalStatus ablegen
CONTINUEMODALPROC pCMOld = m_pCM;
DWORD dwDataCMOld = m_dwDataCM;

	if (NULL != pCM) {
		m_pCM = pCM;
		m_dwDataCM = dwDataCM;
	}

// Determine if this is one of three combinations 
// 1) ExecNormal with IDLE
// 2) ExecNormal without IDLE
// 3) ExecWhileEvent

	if (ExecNormal == et) {
	// if first normal Exec call
	// Check for presence of idle function

		if (IdleStatus == IdleFirstTime) {
		DS_fixup newds(DS_segment);

 			(pRequestor ->* IdleFunc)(TRUE);
			if (NULL != m_pIdleProc)
				(*m_pIdleProc)(-1L);
		}
		if (IdleStatus == IdleFirstTime) 		// Could n't call built in Idle
			IdleStatus = IdlePresent;
	}

	if (!List_of_EventContexts.First())
		return	0;

bool fIdle = true;
long lCnt = 0L;

	while (active && (NULL == pCM || pCM(dwDataCM))) {		// #HK961014: pCM: PropertySheets, die 2.
		if (ExecNormal == et || ExecNormalNoQuitOnHide == et) {
		// ContinueModal der äüßeren Schleife rufen
			if (pCMOld) pCMOld(dwDataCMOld);

		// normale Messageverarbeitung
			if (IdleStatus == IdlePresent) {
			// phase1: check to see if we can do idle work
				while (fIdle && !PeekMessage (&msg, NULL, NULL, NULL, PM_NOREMOVE)) 
				{
				DS_fixup newds(DS_segment);
				
					(pRequestor ->* IdleFunc)(FALSE);

				// external idleprocessing
					if (NULL != m_pIdleProc && !(*m_pIdleProc)(lCnt++))	
						fIdle = false;		// no more Idle processing
				}

			// phase2: pump messages while available
				do {
					if (!PumpMessage (ExecNormal, &msg))
						goto labelWmQuit;		// WM_QUIT received, break outer loop

				// reset "no idle" state after pumping "normal" message
					if (IsIdleMessage(&msg)) {
						fIdle = true;
						lCnt = 0L;
					}
				} while (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE));

			} else if (!PumpMessage (et, &msg))
				break;			// received WM_QUIT

		} else if (et == ExecWhileEvent) {
		// ExecWhileEvent
			if (!PeekMessage (&msg, 0, 0, 0, PM_NOREMOVE)) {
				retval = 1;
				break;
			}
		  	if (msg.message == WM_QUIT)
				break;    // * 2.1 end *

			PumpMessage (et, &msg);

		} else if (et == ExecWhileEventWithIdle) {
		// ExecWhileEvent with Idle processing

		// phase1: check to see if we can do idle work
			while (fIdle) {		
			// internal idleprocessing
			DS_fixup newds(DS_segment);
			
				(pRequestor ->* IdleFunc)(FALSE);
			
			// external idleprocessing 
				if (NULL == m_pIdleProc || !(*m_pIdleProc)(lCnt++))	
					fIdle = false;		// no more Idle processing
			}

		// phase2: pump one message if available
			if (!PeekMessage (&msg, 0, 0, 0, PM_NOREMOVE)) {
				retval = 1;		// no more messages avalable
				break;
			}
			if (!PumpMessage (ExecNormal, &msg))
				break;		// WM_QUIT received, break outer loop

		// phase3: reset "no idle" state after pumping "normal" message
			if (IsIdleMessage(&msg)) {
				fIdle = true;
				lCnt = 0L;
			}
		} else if (et == ExecIdleOnly) {
		// ExecWhileEvent only with Idle processing

		// phase1: check to see if we can do idle work
			while (fIdle) {		
			// internal idleprocessing
			DS_fixup newds(DS_segment);
			
				(pRequestor ->* IdleFunc)(FALSE);
			
			// external idleprocessing 
				if (NULL == m_pIdleProc || !(*m_pIdleProc)(lCnt++))	
					fIdle = false;		// no more Idle processing
			}

		// phase2: pump one message if available
			if (!PeekMessage (&msg, 0, 0, 0, PM_NOREMOVE)) {
				retval = 1;		// no more messages avalable
				break;
			}

			PumpMessage (ExecNormal, &msg);
			retval = 0;		// more messages avalable 
			break;
		}
	}	// End of WHILE

labelWmQuit:	// raus hier
	if (nested && (msg.message == WM_QUIT) && !(ExecNormalNoQuitOnHide == et))
		PostQuitMessage (0);

// ContinueModalStatus wieder herstellen
	if (NULL != pCM) {
		m_pCM = pCMOld;
		m_dwDataCM = dwDataCMOld;
	}

return	retval;
}	// End of "App" FUNCTION "Exec"
  
inline 
BOOL App_Imp::PreTranslateMsgExt (MSG *pMsg)
{
	if (NULL != m_pPreTranslateMsgProc && (*m_pPreTranslateMsgProc)(pMsg))
		return TRUE;
	return FALSE;
}

BOOL App_Imp::IsIdleMessage (MSG* pMsg)
{
// Return 'false' if the message just dispatched should _not_
// cause OnIdle to be run.  Messages which do not usually
// affect the state of the user interface and happen very
// often are checked for.

// redundant WM_MOUSEMOVE and WM_NCMOUSEMOVE
	if (pMsg->message == WM_MOUSEMOVE || pMsg->message == WM_NCMOUSEMOVE)
	{
		// mouse move at same position as last mouse move?
		if (m_ptCursorLast.x == pMsg->pt.x && m_ptCursorLast.x == pMsg->pt.x &&
			pMsg->message == m_nMsgLast)
		{
			return false;
		}

		m_ptCursorLast = pMsg->pt;  // remember for next time
		m_nMsgLast = pMsg->message;
		return true;
	}

// WM_PAINT and WM_SYSTIMER (caret blink)
	return pMsg->message != WM_PAINT && pMsg->message != 0x0118;
}

BOOL App_Imp::PumpMessage (ExecType, MSG *pMsg)
{
	if (!::GetMessage(pMsg, NULL, NULL, NULL))
		return false;		// received WM_QUIT

// #HK960214: PreTranslateMessage
// first route the message to external clients if required
	if (!PreTranslateMsgExt(pMsg) && !PreTranslateMessage (pMsg))
	{
		if (!hHelpAccel || !TranslateAccelerator (hHelpWnd, hHelpAccel, pMsg)) 
		{
			if ((!MDIClientHandle || !TranslateMDISysAccel (MDIClientHandle, pMsg))
				&& (!hWndAccel || !TranslateAccelerator (hAccelRecv, hWndAccel, pMsg))) 
			{
				::TranslateMessage (pMsg);
				::DispatchMessage (pMsg);
			}	// End of IF
		}
	}	// PreTranslateMessage

return true;
}

BOOL App_Imp::PreTranslateMessage (MSG *pMsg)
{
pWind_Imp pWI = NULL;

// dann versuchen, ob's ein CV-Fenster ist
	if (NULL != ContextList() -> First()) {
	// Message für Fenster
		pWI = (pWind_Imp)(ContextList()->Find ((HANDLE)pMsg->hwnd));
		if (NULL == pWI) {
		// evtl. ist's ein Control, dann alles beim Parent vorbeischicken
		HWND hWnd = (NULL != pMsg->hwnd) ? ::GetParent(pMsg->hwnd) : NULL;

			if (NULL != hWnd) 
				pWI = (pWind_Imp)(ContextList()->Find ((HANDLE)hWnd));
		}
	}

// jetzt Fenster-Hierarchie hochwandern, wenn ein Fenster gefunden wurde
	for (/**/; NULL != pWI; pWI = CV_RunTime::Window_Parent(pWI)) 
	{
		if (pWI -> PreTranslateMsg (pMsg))
			return true;		// abgearbeitet
	}

//	return (NULL != LastDlgHandle && ::IsDialogMessage(LastDlgHandle, pMsg));
	return false;		// keiner wollte diese Msg haben
}

void	App_Imp::  Quit	()
{
	PostQuitMessage ( 0 );
}	// End of "App_Imp" FUNCTION "Quit"

// * 1.5 * start
App_Imp ::  ~App_Imp()
{
	FreeProcInstance((FARPROC)DlgDispatch);
	if (Commandl)
		delete Commandl;
	if (argv)
		delete argv;
	if (DefBackBrush)
		DeleteObject(DefBackBrush);

// Assertions to ensure all memory from object lists has been freed.

	CV_ASSERT(!List_of_EventContexts.First());
	CV_ASSERT(!List_of_Menus.First());
	CV_ASSERT(!List_of_Controls.First());
	CV_ASSERT(!List_of_Printers.First());
	CV_ASSERT(!List_of_Resources.First());
#if defined(WIN32)
	CV_ASSERT(!List_of_ImageLists.First());
#endif
}
// * 1.5 * end


void App_Imp:: Idle(InvokeStatus)
{
	   IdleStatus = IdleNotPresent;
}	

HINSTANCE	App_Imp:: Handle (Service s_ID)
{
	switch( s_ID ) {
	case API_APP_HMQ:
	case API_APP_HHEAP:
		return 0;

	case API_APP_HAPP:
		return hApp;

	case API_APP_HPREV:
		return hPrevInst;

//	case API_APP_COMMANDL:
//		return (HINSTANCE) Commandl;
	}

return 0;
}

void	App_Imp:: SetHelpWind (HWND hw, uint mode)
{
	hHelpWnd = hw;
	switch (mode) {
	case HM_GENERAL:
		hHelpAccel = LoadAccelerators (CV_LibHandle(), "GeneralHelp");
		break;
	
	case HM_MOUSE:
		hHelpAccel = LoadAccelerators (CV_LibHandle(), "CursorHelp");
		break;

	default:
		hHelpAccel = 0;
	}
}

void	App_Imp:: SetAccelWind(HACCEL hacc, HWND receiver)
{
	hWndAccel = hacc;
	hAccelRecv = receiver; 
}


HINSTANCE App_Imp :: FindResourceModule (ResID &r, LPCSTR lpszType)
{
	for (CVLink *pLink = ResourceList() -> First(); 
	     pLink; pLink = ResourceList() -> Next()) 
	{
	ResourceFile *pRF = (ResourceFile *)pLink -> Item();
	HINSTANCE hInst = CV_RunTime :: pResFile_to_pImp (pRF) -> Handle();

		if (FindResource (hInst, MAKEINTRESOURCE(uint(r)), lpszType))
			return hInst;
	}

return hApp;	// eigenes Handle liefern
}
