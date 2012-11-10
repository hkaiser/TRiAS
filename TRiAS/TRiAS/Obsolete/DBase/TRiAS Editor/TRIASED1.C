/****************************************************************************

	PROGRAM: TriasED1.c

	PURPOSE: Beinhaltet in TriasED.c benötigte Funktionen

erstellt durch JB am 4. März 1992
Stand vom 11. Jan. 1993
****************************************************************************/

#include "pheader.h"

/* new variables for common dialogs */
extern OPENFILENAME ofn;		/* struct. passed to GetOpenFileName */

PRINTDLG pd;			/* Common print dialog structure */

/* Find/Replace-Text */
FINDREPLACE fr;		 /* Common find/replace structure */
static char szFindWhat [FindStrSize] = "\0";
extern DWORD dwFindFlag;
extern UINT FindReplaceMsg;

extern char FileName [];
extern char szSaveDlgTitle [];

extern HANDLE hEditBuffer;	  /* handle to editing buffer		 */
extern HANDLE hOldBuffer;	   /* old buffer handle		  */
extern HANDLE hHourGlass;	   /* handle to hourglass cursor	   */
extern HANDLE hSaveCursor;	  /* current cursor handle		*/
extern HWND hEditWnd;		   /* handle to edit window */
extern int hFile;			   /* file handle		 */
extern OFSTRUCT OfStruct;	   /* information from OpenFile()	 */
extern BOOL bChanges;		   /* TRUE if the file is changed	 */
extern PSTR pEditBuffer;		/* address of the edit buffer	   */
extern HWND hwnd;			   /* handle to main window			 */
extern char str [];
extern HANDLE hInst;
extern TEXTMETRIC tm;
extern HWND hFindDlg;
			 
/* Printer variables  */
HDC hPr;							/* handle for printer device context	 */
int LineSpace;					  /* spacing between lines		  */
int LinesPerPage;				   /* lines per page				 */
int CurrentLine;					/* current line				   */
int LineLength;					 /* line length					*/
WORD wLines;						/* number of lines to print	   */
WORD wIndex;						/* index into lines to print	  */
char szPrLine[128];				 /* buffer to store lines before printing */
BOOL bAbort;						/* FALSE if user cancels printing	  */
HWND hAbortDlgWnd;
FARPROC lpAbortDlg, lpAbortProc;

/****************************************************************************
	FUNCTION: SaveFile(HWND)
	PURPOSE: Save current file
	COMMENTS:

		This saves the current contents of the Edit buffer, and changes
		bChanges to indicate that the buffer has not been changed since the
		last save.

		Before the edit buffer is sent, you must get its handle and lock it
		to get its address.  Once the file is written, you must unlock the
		buffer.  This allows Windows to move the buffer when not in immediate
		use.
****************************************************************************/
BOOL SaveFile(hWnd)
HWND hWnd;
{
	BOOL bSuccess;
	int IOStatus;								  /* result of a file write */

	if ((hFile = OpenFile(FileName, &OfStruct,
		OF_PROMPT | OF_CANCEL | OF_CREATE)) < 0) {

		/* If the file can't be saved */
                
		lstrcpy (str, "Fehler beim Schreiben in ");
		lstrcat (str, FileName);                
		lstrcat (str, " !");
		// wsprintf(str, "Fehler beim Schreiben in \"%s\" !", FileName);
		MessageBox(hWnd, str, "TriasED", MB_OK | MB_ICONEXCLAMATION);
		return (FALSE);
	}

	hEditBuffer = (HANDLE) SendMessage(hEditWnd, EM_GETHANDLE, 0, 0L);
	pEditBuffer = LocalLock(hEditBuffer);

	/* Set the cursor to an hourglass during the file transfer */

	hSaveCursor = SetCursor(hHourGlass);
	IOStatus = _lwrite(hFile, pEditBuffer, lstrlen(pEditBuffer));
	_lclose(hFile);
	SetCursor(hSaveCursor);
	if (IOStatus != lstrlen(pEditBuffer)) {
		lstrcpy (str, "Fehler beim Schreiben in ");
		lstrcat (str, FileName);                
		lstrcat (str, " !");
		// wsprintf(str, "Fehler beim Schreiben in \"%s\" !", FileName);
		MessageBox(hWnd, str,
			"TriasED", MB_OK | MB_ICONEXCLAMATION);
		bSuccess = FALSE;
	}
	else {
		bSuccess = TRUE;				/* Indicates the file was saved	  */
		bChanges = FALSE;			   /* Indicates changes have been saved */
	}

	LocalUnlock(hEditBuffer);
	return (bSuccess);
}

/****************************************************************************
	FUNCTION: QuerySaveFile(HWND);
	PURPOSE: Called when some action might lose current contents
	COMMENTS:
		This function is called whenever we are about to take an action that
		would lose the current contents of the edit buffer.
****************************************************************************/
BOOL QuerySaveFile(hWnd)
HWND hWnd;
{
	int Response;

	if (bChanges) {

		ofn.lpstrTitle = (LPSTR)szSaveDlgTitle;
		if (!FileName[0])
			lstrcpy (str, "Änderungen speichern ?");
		else        
		{
			// wsprintf(str, "Änderungen speichern in \"%s\" ?", FileName);
			lstrcpy (str, "Änderungen speichern in "); 
			lstrcat (str, FileName);                
			lstrcat (str, " ?");
		}			


		Response = MessageBox(hWnd, str,
			"TriasED",  MB_YESNOCANCEL | MB_ICONQUESTION);
		if (Response == IDYES) {

			/* Make sure there is a filename to save to */
			while (!FileName[0]) {

				/* fill in pertinent field of OPENFILENAME struct. and show
				 * dialog box
				 */
				if (!GetSaveFileName ((LPOPENFILENAME)&ofn))
					return FALSE;		   /* User canceled */
			}
			return SaveFile (hWnd);
		}
		else
			if (Response == IDCANCEL)
				return (FALSE);
	}
	else
		return (TRUE);
}

/****************************************************************************
	FUNCTION: SetNewBuffer(HWND, HANDLE, PSTR)
	PURPOSE: Set new buffer for edit window
	COMMENTS:
		Point the edit window to the new buffer, update the window title, and
		redraw the edit window.  If hNewBuffer is NULL, then create an empty
		1K buffer, and return its handle.
****************************************************************************/
void SetNewBuffer(hWnd, hNewBuffer, Title)
HWND hWnd;
HANDLE hNewBuffer;
LPSTR Title;
{
	HANDLE hOldBuffer;

	hOldBuffer = (HANDLE) SendMessage(hEditWnd, EM_GETHANDLE, 0, 0L);
	LocalFree(hOldBuffer);
	if (!hNewBuffer)					/* Allocates a buffer if none exists */
		hNewBuffer = LocalAlloc(LMEM_MOVEABLE | LMEM_ZEROINIT, 1);

	/* Updates the buffer and displays new buffer */
	SendMessage(hEditWnd, (UINT) EM_SETHANDLE, (WPARAM) hNewBuffer, 0L);

	SetWindowText(hWnd, Title);
	SetFocus(hEditWnd);
	bChanges = FALSE;
}

/****************************************************************************
	FUNCTION: About(HWND, unsigned, WORD, LONG)
	PURPOSE:  Processes messages for "About" dialog box
	MESSAGES:
		WM_INITDIALOG - initialize dialog box
		WM_COMMAND	- Input received
****************************************************************************/
BOOL FAR PASCAL About(hDlg, message, wParam, lParam)
HWND hDlg;
unsigned message;
WORD wParam;
LONG lParam;
{
	switch (message) {
		case WM_INITDIALOG:
			return (TRUE);

		case WM_COMMAND:
			if (wParam == IDOK
				|| wParam == IDCANCEL) {
				EndDialog(hDlg, TRUE);
				return (TRUE);
			}
			break;
	}
	return (FALSE);
}

/****************************************************************************
	FUNCTION: GetPrinterDC()
	PURPOSE:  Get hDc for current device on current output port according to
			  info in WIN.INI.
	COMMENTS:
		Searches WIN.INI for information about what printer is connected, and
		if found, creates a DC for the printer.
		returns
			hDC > 0 if success
			hDC = 0 if failure
****************************************************************************/
HDC GetPrinterDC(void)
{
	HDC		 hDC;
	LPDEVMODE   lpDevMode = NULL;
	LPDEVNAMES  lpDevNames;
	LPSTR	   lpszDriverName;
	LPSTR	   lpszDeviceName;
	LPSTR	   lpszPortName;

	InitPrinter (PD_NOPAGENUMS | PD_RETURNDC | PD_NOSELECTION);
	if (!PrintDlg((LPPRINTDLG)&pd))
		return (NULL);
	if (pd.hDC)
	  {
		hDC = pd.hDC;
	  }
	else
	  {
		if (!pd.hDevNames)
			return(NULL);
		lpDevNames = (LPDEVNAMES)GlobalLock(pd.hDevNames);
		lpszDriverName = (LPSTR)lpDevNames + lpDevNames->wDriverOffset;
		lpszDeviceName = (LPSTR)lpDevNames + lpDevNames->wDeviceOffset;
		lpszPortName   = (LPSTR)lpDevNames + lpDevNames->wOutputOffset;
		GlobalUnlock(pd.hDevNames);

		if (pd.hDevMode)
			lpDevMode = (LPDEVMODE)GlobalLock(pd.hDevMode);
#ifdef WIN32
		hDC = CreateDC(lpszDriverName, lpszDeviceName, lpszPortName, lpDevMode);
#else
		hDC = CreateDC(lpszDriverName, lpszDeviceName, lpszPortName, (LPSTR)lpDevMode);
#endif
		if (pd.hDevMode && lpDevMode)
			GlobalUnlock(pd.hDevMode);
	  }

	if (pd.hDevNames)
		GlobalFree(pd.hDevNames);
	if (pd.hDevMode)
		GlobalFree(pd.hDevMode);
	return(hDC);
}

/****************************************************************************
	FUNCTION: AbortProc()
	PURPOSE:  Processes messages for the Abort Dialog box
****************************************************************************/
int FAR PASCAL AbortProc(hPr, Code)
HDC hPr;							/* for multiple printer display contexts */
int Code;						   /* printing status				*/
{
	MSG msg;

	if (!hAbortDlgWnd)			  /* If the abort dialog isn't up yet */
		return(TRUE);

	/* Process messages intended for the abort dialog box */

#ifdef WIN32
	while (!bAbort && PeekMessage(&msg, NULL, 0, 0, TRUE))
#else
	while (!bAbort && PeekMessage(&msg, NULL, NULL, NULL, TRUE))
#endif
		if (!IsDialogMessage(hAbortDlgWnd, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	/* bAbort is TRUE (return is FALSE) if the user has aborted */
	return (!bAbort);
}

/****************************************************************************
	FUNCTION: AbortDlg(HWND, unsigned, WORD, LONG)
	PURPOSE:  Processes messages for printer abort dialog box
	MESSAGES:
		WM_INITDIALOG - initialize dialog box
		WM_COMMAND	- Input received
	COMMENTS
		This dialog box is created while the program is printing, and allows
		the user to cancel the printing process.
****************************************************************************/
int FAR PASCAL AbortDlg(hDlg, msg, wParam, lParam)
HWND hDlg;
unsigned msg;
WORD wParam;
LONG lParam;
{
	char szDrive [_MAX_DRIVE];
	char szDir   [_MAX_DIR];
	char szFName [_MAX_FNAME];
	char szExt   [_MAX_EXT];

	switch(msg) {
		/* Watch for Cancel button, RETURN key, ESCAPE key, or SPACE BAR */
		case WM_COMMAND:
			return (bAbort = TRUE);
		case WM_INITDIALOG:
			/* Set the focus to the Cancel box of the dialog */
			SetFocus(GetDlgItem(hDlg, IDCANCEL));
			_splitpath (FileName, szDrive, szDir, szFName, szExt);
			SetDlgItemText(hDlg, IDC_FILENAME, strcat (szFName, szExt));
			return (TRUE);
		}
	return (FALSE);
}

/* Drucke akt. File */
BOOL Print (void) {
	int Status;
	int nPageSize;			  /* vert. resolution of printer device */

	hSaveCursor = SetCursor(hHourGlass);
	hPr = GetPrinterDC();
	if (!hPr) 
	{
		// wsprintf(str, "Kann %s nicht drucken oder Druckabbruch.", FileName);
		lstrcpy (str, "Kann Datei nicht drucken oder Druckabbruch !"); 
		MessageBox(hwnd, str, "TriasED", MB_OK | MB_ICONHAND);
		return (FALSE);
	}
	lpAbortDlg = MakeProcInstance(AbortDlg, hInst);
	lpAbortProc = MakeProcInstance(AbortProc, hInst);

/*  Define the abort function */
#ifdef WIN32
	Escape(hPr, SETABORTPROC, 0, (LPSTR) (long) lpAbortProc,(LPVOID) NULL);
#else
	Escape(hPr, SETABORTPROC, NULL, (LPSTR) (long) lpAbortProc,(LPSTR) NULL);
#endif

	if (Escape(hPr, STARTDOC, 14, "Datei drucken", (LPSTR) NULL) < 0) {
		MessageBox(hwnd, "Drucken kann nicht begonnen werden.",
				   "TriasED", MB_OK | MB_ICONHAND);
		FreeProcInstance(lpAbortDlg);
		FreeProcInstance(lpAbortProc);
		DeleteDC(hPr);
	 }
	 bAbort = FALSE; /* Clears the abort flag  */

/*  Create the Abort dialog box (modeless) */
	  hAbortDlgWnd = CreateDialog(hInst, "AbortDlg", hwnd, lpAbortDlg);

	  if (!hAbortDlgWnd) {
		SetCursor(hSaveCursor);	 /* Remove the hourglass */
		MessageBox(hwnd, "Ein Systemfehler ist aufgetreten.",
				   "TriasED", MB_OK | MB_ICONHAND);
		return (FALSE);
	  }
					
/* Now show Abort dialog */
	  ShowWindow (hAbortDlgWnd, SW_NORMAL);

/* Disable the main window to avoid reentrancy problems */
	  EnableWindow(hwnd, FALSE);
	  SetCursor(hSaveCursor);   /* Remove the hourglass */

	  GetTextMetrics(hPr, &tm);
	  LineSpace = tm.tmHeight + tm.tmExternalLeading;

	  nPageSize = GetDeviceCaps (hPr, VERTRES);
	  LinesPerPage = nPageSize / LineSpace - 1;

	  wLines = (WORD)SendMessage(hEditWnd, EM_GETLINECOUNT, 0, 0L);

/* Keep track of the current line on the current page */
	  CurrentLine = 1;

	  for (wIndex = Status = 0; wIndex < wLines; wIndex++) {
		szPrLine[0] = 127;			  /* Maximum buffer size */
		szPrLine[1] = 0;
		LineLength = (int)SendMessage(hEditWnd, EM_GETLINE,
		wIndex, (DWORD)(LPSTR)szPrLine);
		TextOut(hPr, 0, CurrentLine*LineSpace,
		(LPSTR)szPrLine, LineLength);
		if (++CurrentLine > LinesPerPage ) {
			CurrentLine = 1;
			Status = Escape(hPr, NEWFRAME, 0, 0L, 0L);
			if (Status < 0 || bAbort)
				break;
		}
	  }

	  if (Status >= 0 && !bAbort) {
		  Escape(hPr, NEWFRAME, 0, 0L, 0L);
		  Escape(hPr, ENDDOC, 0, 0L, 0L);
	  }
	  EnableWindow(hwnd, TRUE);

/* Destroy the Abort dialog box */
	  DestroyWindow(hAbortDlgWnd);
	  FreeProcInstance(lpAbortDlg);
	  FreeProcInstance(lpAbortProc);
	  DeleteDC(hPr);
}

/*
void PrintSetup (void) {
	InitPrinter (PD_PRINTSETUP);
	PrintDlg ((LPPRINTDLG) &pd);
}
*/

/* fill in non-variant fields of PRINTDLG struct. */
void InitPrinter (DWORD dwFlag) {

	pd.lStructSize	= sizeof (PRINTDLG);
	pd.hwndOwner	  = hwnd;
	pd.hDevMode	   = (HANDLE) NULL;
	pd.hDevNames	  = (HANDLE) NULL;
	pd.Flags		  = dwFlag;
	pd.hInstance = (HANDLE) NULL;
	if (dwFlag != PD_PRINTSETUP)
	   pd.nCopies	 = 1;
	else
	   pd.nCopies	 = 0;
}

/* Finde Text init. */
HWND FindTextInit (HWND hWndOwner) {

//  Struktur init.
	fr.lStructSize = sizeof(FINDREPLACE);
	fr.hwndOwner = hWndOwner;
	fr.hInstance = NULL;
	fr.Flags = FR_FINDNEXT | FR_HIDEMATCHCASE |
			   FR_HIDEWHOLEWORD | FR_HIDEUPDOWN ;
	fr.lpstrFindWhat = GetSelectedText (szFindWhat, sizeof (szFindWhat)-1);
	fr.lpstrReplaceWith = (LPSTR)NULL;
	fr.wFindWhatLen = sizeof(szFindWhat);
	fr.wReplaceWithLen = 0;
	fr.lCustData = 0L;
	fr.lpfnHook = NULL;
	fr.lpTemplateName = (LPSTR)NULL;

	return (FindText (&fr));
}

/* Handle the special findreplace message (FindReplaceMsg) which
   was registered at initialization time. */
BOOL IsFindReplaceMsg (unsigned msg, LPARAM lParam) {

	POINT Pt;
	LPFINDREPLACE lpFR;
	int iResponse;
	char szText [] =
	"Keinen Text gefunden.\nSuche am Dateinfang fortsetzen ?";
	BOOL Ret = FALSE;

	if (msg == FindReplaceMsg) {
		lpFR = (LPFINDREPLACE) lParam;
		lstrcpy (szFindWhat, lpFR->lpstrFindWhat);
		if (!(lpFR->Flags & FR_DIALOGTERM)) { // not terminate
			if (!SearchText (szFindWhat, &Pt)) { // wenn kein Eintrag gefunden
				iResponse = MessageBox (hwnd, szText,
							"TriasED", MB_YESNO | MB_ICONQUESTION);
				if (iResponse == IDYES) {
					Edit_SetSel (hEditWnd, 0, 0); /* Cursor auf Dateianfang */
					if (SearchText (szFindWhat, &Pt)) {
						SetFocus (hEditWnd);
						Edit_SetSel (hEditWnd, Pt.x, Pt.y);
						Ret = TRUE;
					}								   
				}
			} else {
				SetFocus (hEditWnd);
				Edit_SetSel (hEditWnd, Pt.x, Pt.y);
				Ret = TRUE;
			}
		} else
			hFindDlg = NULL;
	}

	return Ret;
}
