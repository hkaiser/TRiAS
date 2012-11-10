/****************************************************************************

	PROGRAM: TriasED.c

	PURPOSE: Loads, saves, prints and edits text files

	FUNCTIONS:

		WinMain() - calls initialization function, processes message loop
		InitApplication() - initializes window data and registers window
		InitInstance() - saves instance handle and creates main window
		MainWndProc() - processes messages
		About() - processes messages for "About" dialog box
		SaveFile() - Save current file
		QuerySaveFile() - Called when some action might lose current contents
		SetNewBuffer() - Set new buffer for edit window

Erweitert durch JB am 22.2.1992
Stand vom 4. 10. 1993
****************************************************************************/

#include "pheader.h"

/* new variables for common dialogs */
static char szFilterSpec [128] = "";	  /* filter string for dir. listings	 */
char szCustFilterSpec[MAXCUSTFILTER];	 /* custom filter buffer			  */
char szOpenDlgTitle[] = "Datei öffnen";   /* title of Datei open dialog		*/
char szSaveDlgTitle[] = "Datei sichern";		  /* title of Datei saveas dialog	   */
OPENFILENAME ofn;						 /* struct. passed to GetOpenFileName */

char PathName [_MAX_PATH] = "";
char FileName [_MAX_PATH] = "";
char szShortFileName [_MAX_FNAME] = "";
char Untitled[] =						 /* default window title	  */
	 "TriasED - (unbenannt)";

HANDLE hInst;
HANDLE hEditBuffer;					   /* handle to editing buffer	  */
HANDLE hOldBuffer;						/* old buffer handle		*/
HANDLE hHourGlass;						/* handle to hourglass cursor	  */
HANDLE hSaveCursor;					   /* current cursor handle	  */
HANDLE hAccTable;								/* handle to accelerator table */
HWND hEditWnd, hRow, hRowText, hCol, hColText;   /* handle to edit window */
HFILE hFile;								/* file handle			  */
int count;								/* number of chars read or written */
PSTR pBuffer;							 /* address of read/write buffer	*/
OFSTRUCT OfStruct;						/* information from OpenFile()	 */
struct stat FileStatus;				   /* information from fstat()	  */
BOOL bChanges = FALSE;					/* TRUE if the file is changed	 */
BOOL bSaveEnabled = FALSE;				/* TRUE if text in the edit buffer */
BOOL bVersion = FALSE;					// 1/0 --> 32/16 Bit-Version
PSTR pEditBuffer = NULL;				/* address of the edit buffer	  */
HWND hwnd = NULL;						/* handle to main window		   */
HWND hWndKR = NULL;					/* Handle zur Komplexrecherche */
char str [128] = "";

/* Variablen für die Zeilen-Spaltenanzeige */
BOOL bParam = FALSE;					  /* keine Parameter beim Programmau-
											 aufruf übergeben */
char szParam [MAXFILENAME];			   /* Parameter-String */
TEXTMETRIC tm;
int iRowWidth, iColWidth, iRowColHigh;

/* ProfString-Variablen */
int MainWinPar[MainWinParSize] = {CW_USEDEFAULT, CW_USEDEFAULT,/* xPos,yPos*/
					   CW_USEDEFAULT, CW_USEDEFAULT}; /* Weite, Höhe */
char  szProfBuff [ProfBuffSize] = "\0";
char  *pszProfBuff = szProfBuff;

/* Variablen für Find-Dialog */
HWND hFindDlg = NULL;
UINT FindReplaceMsg = 0;
UINT KomplexrMsg = 0;

/****************************************************************************
	FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)
	PURPOSE: calls initialization function, processes message loop
****************************************************************************/
int PASCAL WinMain (hInstance, hPrevInstance, lpCmdLine, nCmdShow)
HANDLE hInstance;
HANDLE hPrevInstance;
LPSTR lpCmdLine;
int nCmdShow;
{
	LPSTR pCmdLine = NULL;
	HANDLE hCmdLine = NULL;
	MSG msg;
	BOOL bError = FALSE;
	HWND hOldWnd = FindWindow (szMainClassName, NULL); // suche nach ClassName

	if (hOldWnd) {	 /* nur eine Instance der Applikation zu lassen */
		if (lstrlen (lpCmdLine) > 0) {  // Par. bei Aufruf übergeben
			hCmdLine = GlobalAlloc (GMEM_MOVEABLE | GMEM_SHARE,
								   (DWORD) (lstrlen (lpCmdLine) + 1));
			if (hCmdLine) {
				if (pCmdLine = GlobalLock (hCmdLine)) {
					if (lstrcpy (pCmdLine, lpCmdLine)) {
						GlobalUnlock (hCmdLine);
						SendMessage (hOldWnd, WM_COMMAND,
									(WPARAM) IDM_NEWOPEN, (LPARAM) hCmdLine);
						ShowWindow (hOldWnd, SW_SHOWNORMAL);
					}
					else {
						bError = TRUE;
						GlobalUnlock (hCmdLine);
					}
				}
				else bError = TRUE;
			}
			else bError = TRUE;
		}
		if (hCmdLine)
			GlobalFree (hCmdLine);
		if (bError)
			MessageBox(hOldWnd, "Nicht genügend Speicher.",
								"TriasED", MB_OK | MB_ICONHAND);
		return (BringWindowToTop (hOldWnd));
	}
	else {   
		if (!InitApplication (hInstance))
			return (FALSE);
	}

	if (lstrlen (lpCmdLine) > 0)		/* wenn Parameter vorhanden */
	{
	   lstrcpy (szParam, lpCmdLine);
	   bParam = TRUE;				   /* Bearbeitungsflag setzen */
	}

	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);

	if (SetTimer(hwnd, ID_TIMER, TIME, NULL) == 0) {
		MessageBox(hwnd, "Kann Timer nicht erzeugen !", "TriasED",
						 MB_OK | MB_ICONSTOP);
		return (FALSE);
	}

//  3d-Effekte installieren
	if (Ctl3dRegister (hInstance))
	   Ctl3dAutoSubclass (hInstance);
    
//	ggf. TriasVersion abfragen u. Handle austauschen
	if (hWndKR == NULL)
	{
		PostMessage (HWND_BROADCAST, KomplexrMsg, KE_GET_HANDLE, (LPARAM) hwnd);	// eigenes Handle senden
		PostMessage (HWND_BROADCAST, KomplexrMsg, KE_SENT_HANDLE,  0L);	// Trias-Handle agfragen				    
		PostMessage (HWND_BROADCAST, KomplexrMsg, KE_SENT_VERSION, 0L);	// Trias-Version abfragen   	   
	}		
	   
	while (GetMessage(&msg, NULL, 0, 0)) {
		if ((!TranslateAccelerator (hwnd, hAccTable, &msg)) &&
			(hFindDlg==NULL || !IsDialogMessage (hFindDlg, &msg))) {
		   TranslateMessage(&msg);
		   DispatchMessage(&msg);
		}
	}

//  3d-Effekte freigeben
	if (Ctl3dEnabled())
		Ctl3dUnregister (hInstance);

	return (msg.wParam);
}

/****************************************************************************
	FUNCTION: InitApplication(HANDLE)
	PURPOSE: Initializes window data and registers window class
****************************************************************************/
BOOL InitApplication(hInstance)
HANDLE hInstance;
{
	WNDCLASS  wc;
	char MsgString [80] = "";

	FindReplaceMsg = RegisterWindowMessage (FINDMSGSTRING);

//  TRIAS-Nachricht registrieren
	LoadString (hInstance, KE_RECHERCHE, (LPSTR) MsgString, sizeof (MsgString));
	KomplexrMsg = RegisterWindowMessage ((LPSTR) MsgString);

	wc.style = 0;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, "TriasEdIcon");
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 
	wc.hbrBackground = GetStockObject(WHITE_BRUSH); 
	wc.lpszMenuName =  "TriasEDMenu";
	wc.lpszClassName = szMainClassName;

	return (RegisterClass(&wc));
}

/****************************************************************************
	FUNCTION:  InitInstance(HANDLE, int)
	PURPOSE:  Saves instance handle and creates main window
****************************************************************************/

BOOL InitInstance(hInstance, nCmdShow)
	HANDLE		  	  hInstance;
	int			 	  nCmdShow;
{
	int iIndex;
	UINT cbString;
	char chReplace;
	HDC hDC;
	RECT Rect;				  /* dimension of the client window */
	hInst = hInstance;

	hAccTable = LoadAccelerators(hInst, "TriasEDAcc");

	hSaveCursor = SetCursor(hHourGlass);

/* ProfileString lesen */
	pszProfBuff = szProfBuff;
	if (GetPrivateProfileString (szSectionName, szKeyName, "",
		pszProfBuff, sizeof (szProfBuff), bVersion ? szInitFile32 : szInitFile16)) {
		for (iIndex = 0; iIndex < MainWinParSize; iIndex++) {
			MainWinPar [iIndex] = atoi (pszProfBuff);
			if (!MainWinPar [iIndex])
			   MainWinPar [iIndex] = CW_USEDEFAULT;
			   while ((*++pszProfBuff) && (*pszProfBuff != Separator));
			   if (*pszProfBuff)
				   pszProfBuff++; 
				else	
				   break;	   /* Parameter fehlt  */
		}
	}


	SetCursor (hSaveCursor);

	hwnd = CreateWindow(
		szMainClassName,
		"TriasED",
		WS_OVERLAPPEDWINDOW,
		MainWinPar [0],
		MainWinPar [1],
		MainWinPar [2],
		MainWinPar [3],
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hwnd)
		return (FALSE);
  
	GetClientRect(hwnd, (LPRECT) &Rect);

	/* ber. Werte für Static-Fenster */

	hDC = GetDC (hwnd);
	GetTextMetrics (hDC, &tm);
	iRowWidth = tm.tmAveCharWidth * strlen (cRowText);
	iColWidth = tm.tmAveCharWidth * strlen (cColText);
	iRowColHigh = tm.tmHeight + tm.tmExternalLeading + 2;
	ReleaseDC (hwnd, hDC);

	/* Create a child window */

	hEditWnd = CreateWindow("Edit",
		"",
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | WS_VSCROLL | WS_HSCROLL | 
		ES_AUTOHSCROLL | ES_AUTOVSCROLL,
		0,
		0,
		(Rect.right-Rect.left),
		(Rect.bottom-Rect.top-iRowColHigh),
		hwnd,
		(HMENU) IDC_EDIT,						  /* Child control i.d. */
		hInst,
		NULL);      
		
	if (hEditWnd) 
		SetFixedFont (hEditWnd);
	else
	{
		DestroyWindow(hwnd);
		return FALSE;
	}

	/* Create a static text for row/column */

	hRowText = CreateWindow ("Static",
		cRowText,
		WS_CHILD | WS_VISIBLE,
		0,
		(Rect.bottom-Rect.top-iRowColHigh),
		iRowWidth,
		iRowColHigh,
		hwnd,
		NULL,
		hInst,
		NULL);

	if (hRowText)     
		SetFixedFont (hRowText);
	else		
	{
		DestroyWindow(hwnd);
		return FALSE;
	}

	hRow = CreateWindow ("Static",
		"",
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		iRowWidth,
		(Rect.bottom-Rect.top-iRowColHigh),
		iRowWidth,
		iRowColHigh,
		hwnd,
		NULL,
		hInst,
		NULL);

	if (hRow) 
		SetFixedFont (hRow);
	else		
	{
		DestroyWindow(hwnd);
		return FALSE;
	}

	hColText = CreateWindow ("Static",
		cColText,
		WS_CHILD | WS_VISIBLE,
		iRowWidth + iColWidth,
		(Rect.bottom-Rect.top-iRowColHigh),
		iColWidth,
		iRowColHigh,
		hwnd,
		NULL,
		hInst,
		NULL);

	if (hColText) 
		SetFixedFont (hColText);
	else
	{
		DestroyWindow(hwnd);
		return FALSE;
	}

	hCol = CreateWindow ("Static",
		"",
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		(iRowWidth * 2) + iColWidth,
		(Rect.bottom-Rect.top-iRowColHigh),
		iColWidth,
		iRowColHigh,
		hwnd,
		NULL,
		hInst,
		NULL);

	if (hCol) 
		SetFixedFont (hCol);
	else
	{
		DestroyWindow(hwnd);
		return FALSE;
	}

	/* Get an hourglass cursor to use during file transfers */

	hHourGlass = LoadCursor(NULL, IDC_WAIT);

	/* fill in non-variant fields of OPENFILENAME struct. */
	cbString = LoadString (hInst, IDS_FILTERSTRING, szFilterSpec,
						   sizeof (szFilterSpec) - 1);
	chReplace = szFilterSpec [cbString - 1];		// wildcard merken
	for (iIndex = 0; szFilterSpec [iIndex] != '\0'; iIndex++) { // wildcards ersetzen
		if (szFilterSpec [iIndex] == chReplace)
			szFilterSpec [iIndex] = '\0';
	}

	memset (&ofn, 0, sizeof (OPENFILENAME));	// alle 0 setzen

	ofn.lStructSize	   = sizeof(OPENFILENAME);
	ofn.hwndOwner		 = hwnd;
	ofn.lpstrFilter	   = szFilterSpec;
	ofn.lpstrCustomFilter = szCustFilterSpec;
	ofn.nMaxCustFilter	= MAXCUSTFILTER;
	ofn.nFilterIndex	  = 1;
	ofn.lpstrFile		 = FileName;
	ofn.nMaxFile		  = MAXFILENAME;
	ofn.lpstrInitialDir   = PathName;
	ofn.Flags			 = OFN_HIDEREADONLY | OFN_ENABLEHOOK;
	ofn.lpfnHook		  = Init3dHook;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd); 
	
	return (TRUE);
}

/****************************************************************************
	FUNCTION: MainWndProc(HWND, UINT, WPARAM, LPARAM)
	PURPOSE:  Processes messages
	MESSAGES:
		WM_INITMENU   - initialize menu
		WM_COMMAND	- application menu (About dialog box)
		WM_DESTROY	- destroy window
		WM_QUERYENDSESSION - willing to end session?
		WM_ENDSESSION - end Windows session
		WM_CLOSE	  - close the window
		WM_SIZE	   - window resized, neue Größe in "trias.ini" speichern
		WM_TIMER	  - Anzeige der Zeilen/Spalten-Nr. alle 0,5 s akt.
		WM_MOVE	   - neue Position in "trias.ini" speichern
	COMMENTS:
		WM_COMMAND processing:
			IDM_NEW - query to save current file if there is one and it has
					  been changed, clear buffer and start new file.

			IDM_OPEN - query to save current file if there is one and it
					   has been changed, open a new file.

			IDM_NEWOPEN - eine weitere Task übergibt Parameter

			IDM_SAVE - save current file, prompt for name if none exists.

			IDM_SAVEAS - prompt for new filename to save to, save file.

			IDC_EDIT - change "bChanges" flag to indicate if edit buffer has
					  been modified.  Affects actions of IDM_NEW and
					  IDM_OPEN.  Reset when file is saved.

			IDM_EXIT - query to save current file if there is one and it
					   has been changed, then exit.

			IDM_ABOUT - display "About" box.

		When more then one string needs to be sent to a message box,
		sprintf() is used to combine the strings into str[], and then str[]
		is passed to the MessageBox() function.  A message box string cannot
		exceed 255 characters, but may contain \n to generate separate
		lines.

		After the size of the file is determined, only enough memory to store
		the file is allocated for the Edit buffer.  The edit control will
		automatically expand this memory as needed.  Once the file has been
		read into the edit buffer, unlock the memory.  Use whatever was
		obtained from the read() function, even if an error occured.  This
		allows partial salvage of a file with a bad sector.

		Before the printing operation begins, a modeless dialog box is
		created to allow the user to abort the printing operation.  This
		dialog box remains active until the print job is completed, or the
		user cancels the print operation.
****************************************************************************/
long FAR PASCAL MainWndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	FARPROC lpProcAbout;

	UINT IOStatus;						   /* result of file i/o	  */

/* Variablen für Anzeige der Zeilen-Nummer */
	// int iColMax;
	static iActRow = 0;
	static iNewRow = 1;
	static iActCol = 0;
	static iNewCol = 1;
	static BOOL bRech = FALSE;		
	char szLine [iMaxLineLength] = "\0";
	DWORD dwSel;

/* Variablen für Profile-Arbeit */
	RECT Rect;

/* Variablen für die Analyse der Kommando-Zeilen-Parameter */
	char szParamBuff [MAXFILENAME];		 /* Parameter-String */
	char *pStrBeg;						  /* Zeiger auf Parameter-String */
	char *pStrEnd;
	int Index;   

	/* für Aufruf weiterer Task */
	LPSTR pCmdLine = NULL;
	BOOL bErr = FALSE;
	WORD wBeg, wEnd;
	int iColMax;
	
	switch (message) {
		case WM_INITMENU:
		/* Check "Undo" */
			if (Edit_CanUndo (hEditWnd)) {
				EnableMenuItem ((HMENU) wParam, IDM_UNDO, MF_ENABLED);
			}
			else {
			   EnableMenuItem ((HMENU) wParam, IDM_UNDO, MF_GRAYED);
			   Edit_EmptyUndoBuffer (hEditWnd);
			}

		/* Check "Paste" */
			if (OpenClipboard (hwnd)) {
			   if (IsClipboardFormatAvailable (CF_TEXT)
				   || IsClipboardFormatAvailable (CF_OEMTEXT))
						EnableMenuItem (GetMenu(hwnd), IDM_PASTE, MF_ENABLED);
					else
						EnableMenuItem (GetMenu(hwnd), IDM_PASTE, MF_GRAYED);
			}
			CloseClipboard ();

		/* Check "copy", "cut" and "del" */
			dwSel = Edit_GetSel (hEditWnd);
			if (LOWORD (dwSel) != HIWORD (dwSel)) { /* wenn Text selektiert */
				EnableMenuItem (GetMenu(hwnd), IDM_COPY, MF_ENABLED);
				EnableMenuItem (GetMenu(hwnd), IDM_CUT, MF_ENABLED);
				EnableMenuItem (GetMenu(hwnd), IDM_CLEAR, MF_ENABLED);
			}
			else {
				EnableMenuItem (GetMenu(hwnd), IDM_COPY, MF_GRAYED);
				EnableMenuItem (GetMenu(hwnd), IDM_CUT, MF_GRAYED);
				EnableMenuItem (GetMenu(hwnd), IDM_CLEAR, MF_GRAYED);
			}

		/*  Recherche-Menüs ggf. aktivieren */
			bRech = FALSE;
		/*  Komplex-Recherche bereit ? */
			if (hWndKR)
				SendMessage (hWndKR, KomplexrMsg, KE_READY, 0L);
												              
			EnableMenuItem (GetMenu(hwnd), IDM_PARSE, bRech ? MF_ENABLED : MF_GRAYED);															              
			if (bRech && *FileName) {  /* gültiger Dateiname */
				EnableMenuItem (GetMenu(hwnd), IDM_START, MF_ENABLED);
				EnableMenuItem (GetMenu(hwnd), IDM_PARAM, MF_ENABLED);
			} else {
				EnableMenuItem (GetMenu(hwnd), IDM_START, MF_GRAYED);
				EnableMenuItem (GetMenu(hwnd), IDM_PARAM, MF_GRAYED);
			}

			return (TRUE);

		case WM_TIMER:		 /* alle 0,5 s */
		//	SetRowCol ();
		/* Werte lesen */
			dwSel = Edit_GetSel (hEditWnd);
			wBeg = LOWORD (dwSel);
			wEnd = HIWORD (dwSel);

		/* Zeilenzähler akt. */
			if (wBeg == wEnd)
				iNewRow = Edit_LineFromChar (hEditWnd, -1);
			else
				iNewRow = Edit_LineFromChar (hEditWnd, wEnd);
			if (iActRow != ++iNewRow) {
				iActRow = iNewRow;
				Static_SetText (hRow, itoa (iActRow ,szLine, 10));
			}

		/* Spalten-Zähler akt. */
			if (wBeg == wEnd)
				iColMax = Edit_LineLength (hEditWnd, -1);
			else
				iColMax = Edit_LineLength (hEditWnd, iActRow - 1);
			iNewCol = wEnd - Edit_LineIndex (hEditWnd, -1) + 1;
			if (iNewCol > ++iColMax)
				iNewCol = iColMax;     
			CheckColumn (iNewRow, &iNewCol);				
			if (iActCol != iNewCol) {
				iActCol = iNewCol;
				Static_SetText (hCol, itoa (iActCol, szLine, 10));
			}
			break;
			
			case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDM_PARAM:				 // Script in Komplex-Recherche setzen
					if (bRech && *FileName) {
						if (CopyFileNameToClipBoard (hWnd, FileName))	
							PostMessage (hWndKR, (UINT) KomplexrMsg, (WPARAM) KE_PARAM, 0L);												
					}						
					break;
				case IDM_START:				 // Komplex-Recherche starten
					if (bRech && *FileName && QuerySaveFile (hWnd)) {
						ShowWindow (hWnd, SW_MINIMIZE);
						if (CopyFileNameToClipBoard (hWnd, FileName))	                            
						{
							PostMessage (hWndKR, (UINT) KomplexrMsg, (WPARAM) KE_PARAM, 0L);	
							PostMessage (hWndKR, (UINT) KomplexrMsg, (WPARAM) KE_START, 0L);
						}							
													
					}
					break;
				case IDM_PARSE:		 // Script prüfen
					if (bRech) {
						if (CopyTextToClipBoard (hWnd, hEditWnd))
							PostMessage (hWndKR, KomplexrMsg, KE_PARSE, 0L);
					}
					break;

				case IDM_ABOUT:
					lpProcAbout = MakeProcInstance(About, hInst);
					DialogBox(hInst, "AboutBox", hWnd, lpProcAbout);
					FreeProcInstance(lpProcAbout);
					break;

				case IDM_CLOSE:
				case IDM_NEW:
					/* If current file has been modified, query user about
					 * saving it.
					 */

					if (!QuerySaveFile(hWnd))
						return FALSE;

					/* bChanges is set to FALSE to indicate there have been
					 * no changes since the last file save.
					 */

					bChanges = FALSE;
					FileName[0] = 0;

					/* Update the edit buffer */

					SetNewBuffer(hWnd, NULL, Untitled);
					break;

				case IDM_NEWOPEN:
					if ((HANDLE) lParam) {
						if (pCmdLine = GlobalLock ((HANDLE) lParam)) {
							if (lstrcpy (szParam, pCmdLine)) {
								GlobalUnlock ((HANDLE) lParam);
								bParam = TRUE;  /* Bearbeitungsflag setzen */
								SendMessage (hWnd, WM_COMMAND, IDM_OPEN, 0L);
								bParam = FALSE;
							}
							else {
								bErr = TRUE;
								GlobalUnlock ((HANDLE) lParam);
							}
						}
						else bErr = TRUE;
					}
					if (bErr)
						MessageBox(hWnd, "Nicht genügend Speicher.",
								"TriasED", MB_OK | MB_ICONHAND);
					break;

				case IDM_OPEN:
					if (bParam && strstr (szParam, "-e"))		// immer als Erstes auswerten
						OutputErrorMessage (hWnd, szParam);		// Fehlermeldung ausgeben
				
					if (bParam && strstr (szParam, "-k")) { // Daten bereits im Puffer
						SetTextCursor (hEditWnd, szParam);  // Cursor setzen
						break;
					}

					if (!QuerySaveFile(hWnd))	   // alte Datei ggf. sichern
							return FALSE;

					if (bParam && strstr (szParam, "-c")) { /*  Daten aus Clipboard holen ? */
						FileName [0] = 0;
						SetNewBuffer(hWnd, NULL, Untitled);
						SendMessage (hEditWnd, WM_PASTE, 0, 0L);
						SetTextCursor (hEditWnd, szParam); // Cursor setzen
						break;
					}

					if (bParam) {   /* andere Paramter in Kommandozeile übergeben */
					/* ggf. Filenamen aus Commando-Zeile */
						pStrBeg = szParam;
						while (*pStrBeg && *pStrBeg == '-') { // keine Option
							while (*pStrBeg && *pStrBeg != ' ')
								pStrBeg++;
							if (!*pStrBeg)
								return FALSE;
							if (*++pStrBeg != '-')
								break;
						}
						if (!*pStrBeg)
							return FALSE;
						pStrEnd = pStrBeg;
						while (*pStrEnd &&	   /* solange kein Textende oder */
							(*pStrEnd != ' ')) /* kein Separator gef. */
							pStrEnd++;
						for (Index = 0, pStrBeg; pStrBeg < pStrEnd;
							pStrBeg++, Index++)
							szParamBuff [Index] = *pStrBeg;
						szParamBuff [Index] = '\0';	 /* Endekennzeichen setzen */
						if (!strlen (szParamBuff))	  /* wenn keine Zeichen kopiert */
							break;
						lstrcpy (FileName, szParamBuff);
					} else {	 /* normales Öffnen aus dem Menü */
						ofn.lpstrTitle	= (LPSTR)szOpenDlgTitle;
						if (!GetOpenFileName ((LPOPENFILENAME)&ofn))
						   return FALSE;
					}

					/* Open the file and get its handle */
					hFile = OpenFile (FileName, (LPOFSTRUCT)&OfStruct,
												 OF_READ);
					if (!hFile)
						return FALSE;

					/* Allocate edit buffer to the size of the file + 1 */
						fstat(hFile, &FileStatus);
						hEditBuffer =
							LocalAlloc(LMEM_MOVEABLE | LMEM_ZEROINIT,
							(WORD)(FileStatus.st_size+1));

					if (!hEditBuffer) {
						MessageBox(hWnd, "Nicht genügend Speicher.",
							"TriasED", MB_OK | MB_ICONHAND);
						return FALSE;
					}
					hSaveCursor = SetCursor(hHourGlass);
					pEditBuffer = LocalLock(hEditBuffer);

					IOStatus = _lread(hFile, pEditBuffer, (UINT) FileStatus.st_size);
					_lclose(hFile);

					/* # bytes read must equal file size */

					if (IOStatus != (UINT) FileStatus.st_size) 
					{
                    	lstrcpy (str, "Fehler beim Lesen von ");
                    	lstrcat (str, FileName);
                    	lstrcat (str, ".");              
						// wsprintf(str, "Fehler beim Lesen von \"%s\".", FileName);
						SetCursor(hSaveCursor);	  /* Remove the hourglass */
						MessageBox(hWnd, str, "TriasED", MB_OK | MB_ICONEXCLAMATION);
					}
					LocalUnlock(hEditBuffer);

					/* Set up a new buffer and window title */ 
					if (ShortFileName (FileName, szShortFileName))
					{           
						lstrcpy (str, "TriasED - ");
						lstrcat (str, szShortFileName);
						// wsprintf (str, "TriasED %s", szShortFileName);
						SetNewBuffer(hWnd, hEditBuffer, str);
					}						
					SetCursor(hSaveCursor);			/* restore the cursor */

					if (bParam)	/* Paramter in Kommandozeile übergeben */
						SetTextCursor (hEditWnd, szParam); // Cursor setzen
					break;

				case IDM_SAVE:
					/* If there is no filename, use the saveas command to get
					 * one.  Otherwise, save the file using the current
					 * filename.
					 */
					if (FileName[0]){
						if (bChanges)
							SaveFile(hWnd);
						break;
					}
					/* else fall thro' for Saveas processing */

				case IDM_SAVEAS:

					/* fill in title field of OPENFILENAME struct. and show
					 * dialog box
					 */
					ofn.lpstrTitle = (LPSTR)szSaveDlgTitle;
					if (!GetSaveFileName ((LPOPENFILENAME)&ofn))
						return FALSE;		   /* User canceled */

					/* If successful, update the window title, save the file */
					if (ShortFileName (FileName, szShortFileName))
					{           
						lstrcpy (str, "TriasED - ");
						lstrcat (str, szShortFileName);
						// wsprintf (str, "TriasED: %s", szShortFileName);
						SetWindowText(hWnd, str);
					}						
					SaveFile(hWnd);
					break;

				case IDM_PRINT:
					Print ();
					break;

				/* läuft nicht im Zusammenhang mit dem Drucken
				case IDM_PRINTSETUP:
					PrintSetup ();
					break;
				*/

				case IDM_FIND:
					if (!(hFindDlg = FindTextInit (hWnd)))
						MessageBox(hWnd, "Ein interner Fehler ist aufgetreten !",
								   "TriasED", MB_OK | MB_ICONEXCLAMATION);
					break;

				/*  kommt Zeit, kommt Realisierung
				case IDM_CHANGE:
					break;
				*/

				case IDM_CUT:
					SendMessage (hEditWnd, WM_CUT, 0, 0L);
					break;

				case IDM_COPY:
					SendMessage (hEditWnd, WM_COPY, 0, 0L);
					break;

				case IDM_CLEAR:
					SendMessage (hEditWnd, WM_CLEAR, 0, 0L);
					break;

				case IDM_PASTE:
					SendMessage (hEditWnd, WM_PASTE, 0, 0L);
					break;

				case IDM_UNDO:
					if (!Edit_Undo (hEditWnd))
						Edit_EmptyUndoBuffer (hEditWnd);
					break;

				case IDM_EXIT:
					QuerySaveFile(hWnd);
					DestroyWindow(hWnd);
					break;

				case IDC_EDIT:
					switch (HIWORD (lParam)){
						case EN_ERRSPACE:
							MessageBox(GetFocus (), "Nicht genügend Speicher.",
								"TriasED", MB_OK | MB_ICONHAND);
							break;

						case EN_CHANGE:
							/* contents of edit control buffer have changed */
							if (!bChanges)
								bChanges = TRUE;
							break;

						default:
							break;
					}
					break;
			} 
			break;

		case WM_SETFOCUS:
			SetFocus (hEditWnd);
			break;

		case WM_SIZE:
			MoveWindow(hEditWnd, 0, 0, LOWORD(lParam), HIWORD(lParam)-iRowColHigh,
					   TRUE);
			MoveWindow(hRowText, 0, HIWORD(lParam)-iRowColHigh, iRowWidth,
					   iRowColHigh, TRUE);
			MoveWindow(hRow, iRowWidth, HIWORD(lParam)-iRowColHigh, iRowWidth,
					   iRowColHigh, TRUE);
			MoveWindow(hColText, iRowWidth*2, HIWORD(lParam)-iRowColHigh,
					   iColWidth, iRowColHigh, TRUE);
			MoveWindow(hCol, iRowWidth*2+iColWidth, HIWORD(lParam)-iRowColHigh,
					   iColWidth, iRowColHigh, TRUE);

			if (bParam)	  /* wenn Parameter bei Aufruf übergeben */
			{
				SendMessage (hwnd, WM_COMMAND, IDM_OPEN, 0L);
				bParam = FALSE;	  /* Flag rücksetzen */
			}
			if (wParam == SIZENORMAL) {
				GetWindowRect (hwnd, &Rect);
				MainWinPar [2] =Rect.right - Rect.left;  /* neue Weite */
				MainWinPar [3] = Rect.bottom - Rect.top; /* neue Höhe */
				wsprintf (szProfBuff, "%i%c%i%c%i%c%i",
					MainWinPar[0], Separator, MainWinPar[1], Separator,
					MainWinPar[2], Separator, MainWinPar[3], Separator);
				hSaveCursor = SetCursor(hHourGlass);
				WritePrivateProfileString (szSectionName, szKeyName,
										   szProfBuff, bVersion ? szInitFile32 : szInitFile16);
				SetCursor (hSaveCursor);	  /* restore the cursor */
			}
		break;

		case WM_MOVE:
			if ((!IsZoomed (hWnd)) &&
				(!IsIconic (hWnd))) {
				GetWindowRect (hWnd, &Rect);
				if (Rect.left > 0)
					MainWinPar [0] = Rect.left;  /* neue xPos */
				else
					MainWinPar [0] = CW_USEDEFAULT;
				if (Rect.top > 0)
					MainWinPar [1] = Rect.top;   /* neue yPos */
				else
					MainWinPar [1] = CW_USEDEFAULT;
				wsprintf (szProfBuff, "%i%c%i%c%i%c%i",
						  MainWinPar[0], Separator, MainWinPar[1], Separator,
						  MainWinPar[2], Separator, MainWinPar[3], Separator);
				hSaveCursor = SetCursor(hHourGlass);
				WritePrivateProfileString (szSectionName, szKeyName,
										   szProfBuff, bVersion ? szInitFile32 : szInitFile16);
				SetCursor(hSaveCursor); /* restore the cursor */
			}
			break;
		case WM_QUERYENDSESSION:			 /* message: to end the session? */
			return (QuerySaveFile(hWnd));

		case WM_CLOSE:					   /* message: close the window	*/
		{
			if (QuerySaveFile(hWnd))
				DestroyWindow(hWnd);        
		}			
			break;

		case WM_DESTROY:
			KillTimer (hwnd, ID_TIMER);
			PostQuitMessage(0);
			break;

		case WM_SYSCOLORCHANGE:
			if (Ctl3dEnabled())
				Ctl3dColorChange();
			break;

		default:
			if (IsFindReplaceMsg (message, lParam))
				return FALSE;
				
			if (message == KomplexrMsg)
			{               
				switch (wParam)
				{
					case EDIT_CAN:
						bRech = TRUE;							// Recherche kann durchgef. werden
					return TRUE;											
					case EDIT_CLOSE:
						PostMessage (hWnd, WM_CLOSE, 0, 0L); 	//	TRIAS verlangt schließen des Editors
					return TRUE;																	
					case EDIT_GET_VERSION:
						bVersion = (BOOL) lParam;
					return TRUE;						
					case EDIT_GET_HANDLE:
						hWndKR = (HWND) lParam;
					return TRUE;
				}					
			}					
			
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return FALSE;
}
              
/*              
//	Zeile/Spalte aktualisieren
void SetRowCol (void)        
{                 
	BOOL bInit = FALSE;
	TEXTMETRIC tm;     
	HDC hdc = NULL;
	POINT pt;           
	double iXp = 1.0; 
	double iYp = 1.0;                     
	char szLine [10] = "";  
	
	if (bInit == FALSE)
	{                     
		if (hdc = GetDC (hEditWnd))
		{
			if (GetTextMetrics (hdc , &tm))
			{
				GetCaretPos (&pt);      
				bInit = TRUE;		// Init ok !
			}	
			ReleaseDC (hEditWnd, hdc);							
		}			
	}
	
//	Zeile/Spalte berechnen			
	if (bInit)
	{                    
		if (tm.tmAveCharWidth)
			iXp = (pt.x / tm.tmAveCharWidth) + 1.5;	
		Static_SetText (hCol, itoa ((int)iXp, szLine, 10));		
		if (tm.tmHeight)	ist falsch !
			iYp = (pt.y / tm.tmHeight) + 1.5;
		Static_SetText (hRow, itoa ((int)iYp, szLine, 10));							
	}		
}                    
*/
                  
//	Raster-Font einstellen            
void SetFixedFont (HWND hWnd)
{
	LOGFONT lf;
	HDC hDC = NULL;
	HFONT hFont = NULL;
	
	memset (&lf, 0, sizeof (LOGFONT));
	lf.lfPitchAndFamily = FIXED_PITCH;
	lf.lfHeight = -15;
	lf.lfWidth = 0;		// 8
	if (hFont = CreateFontIndirect (&lf))
	{
		if (hDC = GetDC (hWnd));
		{
			SendMessage (hWnd, WM_SETFONT, (WPARAM) hFont, 
						(LPARAM) MAKELONG((WORD) 0, 0));
			ReleaseDC (hWnd, hDC);
		}					
	}    
}	
                          
// prüfe aktuelle Spalte                          
void CheckColumn (int iRow, int *pCol)
{
	unsigned char szBuffer [iMaxLineLength] = "";
	WORD cbText = 0;
	register short i = 0;    
	register short iCnt = 0;
	register short sMax = pCol[0] - 1;
    
//	lese aktuelle Zeile
	if ((cbText = Edit_GetLine (hEditWnd, --iRow, szBuffer, sizeof (szBuffer))) == 0)
		return;
		
//	szBuffer[cbText] = '\0';    	// Nullendung sichern
//	suche Tabulatoren im Text
	sMax = min ((short) cbText, sMax);	                   	
	
	for (i = 0;	i < sMax; i++)
	{
		if (szBuffer [i] == '\t')
			iCnt += (iTabSize - (iCnt % iTabSize));			
		else			
			iCnt++; 		
	}
	
	*pCol = ++iCnt;
}
