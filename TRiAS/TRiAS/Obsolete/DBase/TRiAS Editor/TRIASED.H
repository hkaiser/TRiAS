#define MAXFILESIZE 0x7fff           /* maximum file size that can be loaded */
#define MAXFILENAME 256              /* maximum length of file pathname      */
#define MAXCUSTFILTER 40             /* maximum size of custom filter buffer */

/* Row/Coulumn */
#define cRowText  " Zeile: "
#define cColText  " Spalte: "
#define iMaxLineLength 128          /* max. Länge einer Edit-Zeile */
#define iTabSize 		 8			/* 8 Zeichen pro Tab */ 

/* Timer */
#define TIME            500        /* alle 0,5 Sekunden Zeilen/Spalte-Anzeige akt. */

/* Name der Edit-Klasse */
#define szMainClassName "TriasEDWClass"   /* verwendet in "FindWindow" */

/* Profile */
#define szSectionName       "TriasED"
#define szKeyName           "SizeOrg"
#define szInitFile32        "trias20.ini"
#define szInitFile16		"trias13.ini"
#define Separator           ','             /* Komma trennt Parameter */
#define ProfBuffSize        80
#define MainWinParSize      4

/* Find/Replace-text */
#define FindStrSize         30  

int PASCAL WinMain(HANDLE, HANDLE, LPSTR, int);
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
long FAR PASCAL MainWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL FAR PASCAL About (HWND, unsigned, WORD, LONG);
BOOL SaveFile (HWND);
BOOL QuerySaveFile (HWND);
void SetNewBuffer (HWND, HANDLE, LPSTR);
HDC GetPrinterDC (void);
int FAR PASCAL AbortProc (HDC, int);
int FAR PASCAL AbortDlg (HWND, unsigned, WORD, LONG);
void InitPrinter (DWORD);
BOOL Print (void);
/* void PrintSetup (void); */
HWND FindTextInit (HWND hWndOwner);
BOOL IsFindReplaceMsg (unsigned msg, LPARAM lParam);
char *GetSelectedText (char *, int);
char *GetFirstLine (char *);
char *CompareStrings (char *, char *);
BOOL SearchText (char *, POINT*);
void SetTextCursor (HWND, char *);
//  bilde "kurzen" Dateinamen
BOOL ShortFileName (char *pFullName, char *pShortName);
//  Text des Edit-Fenster ins Clipboard kopieren
BOOL CopyTextToClipBoard (HWND hMainWnd, HWND hEditWnd);
UINT FAR PASCAL Init3dHook (HWND, UINT, WPARAM, LPARAM);
void SetRowCol (void);        
void SetFixedFont (HWND hWnd);
void CheckColumn (int iRow, int *pCol);
BOOL CopyFileNameToClipBoard (HWND hMainWnd, char *FileName);
BOOL OutputErrorMessage (HWND hWnd, char *pErrText);
 