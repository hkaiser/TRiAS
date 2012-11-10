
#include "stdafx.h"

#include "cxstring.h"
/*
#include "windows.h"
#include "winver.h"
#include <time.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <commdlg.h>
#include <direct.h> 
#include <dos.h>
#include <shellapi.h>
#include <io.h>
#include <errno.h>
*/
#include "dunzdll.h"
#include "dunzerr.h"

#define MAX_BUFFERLEN		20000

FARPROC lpMinorStatus = (FARPROC)NULL;
FARPROC lpMajorStatus = (FARPROC)NULL;
FARPROC lpMsgDispProc = (FARPROC)NULL;
char MsgDispData[] = "DynaZIP Shell";

BOOL    gbCancel = FALSE;

void CreateTempDirName( CString& strTempDirName )
{
	char szTempDirName[_MAX_PATH];
	GetTempPath(_MAX_PATH, szTempDirName );
	strTempDirName = szTempDirName;
	strTempDirName += "ZEDBS\\";
}

void CreateTempFileName( CString& strTempFileName )
{
	char szTempDirName[_MAX_PATH];
	char szTempFileName[_MAX_PATH];
	GetTempPath(_MAX_PATH, szTempDirName );
	GetTempFileName(szTempDirName,"FJE",0,szTempFileName);
	strTempFileName = szTempFileName;
}
//------------------------------------------------------------------------
void ExtractWorkingDir(LPSTR szDir, LPSTR szFileSpec)
{
BOOL Found;
int  k;
char szTemp[_MAX_PATH], szDrv[_MAX_DRIVE], szPath[_MAX_PATH], szFname[_MAX_FNAME], szExt[_MAX_EXT];

  // get all of the components of the executable d:\path\filename
  lstrcpy((LPSTR)szTemp, (LPSTR)szFileSpec);
  Found = FALSE;
  k = 0;
  while(((BYTE)szTemp[k] != (BYTE)0) && !Found){
    if((BYTE)szTemp[k] == (BYTE)' '){
      // remainder of line is parameters
      // terminate on parameters boundary
      szTemp[k] = (char)0;
      Found = TRUE;
    }
    k++;
  }

  _splitpath(szTemp, szDrv, szPath, szFname, szExt);

  if((lstrlen((LPSTR)szDrv) == 0) && (lstrlen((LPSTR)szPath) == 0)){
    // if the user did not enter an explicit drive:, path and file
    // then do what Program Manager does.... default to windows dir
    GetWindowsDirectory((LPSTR)szTemp, sizeof(szTemp));
    lstrcat((LPSTR)szTemp, (LPSTR)"\\");
    lstrcat((LPSTR)szTemp, (LPSTR)szFname);
    lstrcat((LPSTR)szTemp, (LPSTR)szExt);
    _splitpath(szTemp, szDrv, szPath, szFname, szExt);
  }

  // set the current working directory on this new drive
  lstrcpy((LPSTR)szTemp, (LPSTR)szDrv);

  if(lstrlen((LPSTR)szPath) > 1){
    // don't copy the trailing backslash character!
    strncat(szTemp, szPath, lstrlen((LPSTR)szPath) - 1);
  }
  else{
    // there is only a backslash
    lstrcat((LPSTR)szTemp, (LPSTR)szPath);
  }
  lstrcpy((LPSTR)szDir, (LPSTR)szTemp);
}
//------------------------------------------------------------------------
void ExtractWorkingDir1(LPSTR szDir, LPSTR szFileSpec)
{
char szTemp[_MAX_PATH], szDrv[_MAX_DRIVE], szPath[_MAX_PATH], szFname[_MAX_FNAME], szExt[_MAX_EXT];

  // get all of the components of the executable d:\path\filename
  lstrcpy((LPSTR)szTemp, (LPSTR)szFileSpec);

  _splitpath(szTemp, szDrv, szPath, szFname, szExt);

  if((lstrlen((LPSTR)szDrv) == 0) && (lstrlen((LPSTR)szPath) == 0)){
    // if the user did not enter an explicit drive:, path and file
    // then do what Program Manager does.... default to windows dir
    GetWindowsDirectory((LPSTR)szTemp, sizeof(szTemp));
    lstrcat((LPSTR)szTemp, (LPSTR)"\\");
    lstrcat((LPSTR)szTemp, (LPSTR)szFname);
    lstrcat((LPSTR)szTemp, (LPSTR)szExt);
    _splitpath(szTemp, szDrv, szPath, szFname, szExt);
  }

  // set the current working directory on this new drive
  lstrcpy((LPSTR)szTemp, (LPSTR)szDrv);

  if(lstrlen((LPSTR)szPath) > 1){
    // don't copy the trailing backslash character!
    strncat(szTemp, szPath, lstrlen((LPSTR)szPath) - 1);
  }
  else{
    // there is only a backslash
    lstrcat((LPSTR)szTemp, (LPSTR)szPath);
  }
  lstrcpy((LPSTR)szDir, (LPSTR)szTemp);
}
//------------------------------------------------------------------------
void ExtractPath(LPSTR szDir, LPSTR szFileSpec)
{
char szDrv[_MAX_DRIVE], szPath[_MAX_PATH], szFname[_MAX_FNAME], szExt[_MAX_EXT];

  // get all of the components of the executable d:\path\filename
  _splitpath(szFileSpec, szDrv, szPath, szFname, szExt);

  lstrcpy((LPSTR)szDir, (LPSTR)szDrv);
	lstrcat((LPSTR)szDir, (LPSTR)szPath);

	if(szDir[lstrlen(szDir) - 1] == '\\'){
	  szDir[lstrlen(szDir) - 1] = 0;
	}

}
//------------------------------------------------------------------------
void ExtractFilename(LPSTR lpszFilename, LPSTR lpszPathSpec)
{
char szTemp[_MAX_PATH];
char szDrv[_MAX_DRIVE], szDir[_MAX_PATH], szFname[_MAX_FNAME], szExt[_MAX_EXT];

  lstrcpy((LPSTR)szTemp, lpszPathSpec);
  _splitpath(szTemp, szDrv, szDir, szFname, szExt);
  szFname[_MAX_FNAME - 1] = (char)0;
  lstrcpy(lpszFilename, (LPSTR)szFname);
  szExt[_MAX_EXT - 1] = (char)0;
  lstrcat(lpszFilename, (LPSTR)szExt);
}

// **************************************************************************************
//
//  Procedure:  initUNZIPCmdStruct()
//
//  Purpose:  make the inputted UNZIP command structure "plain vanilla"
//
// **************************************************************************************
void initUNZIPCmdStruct(UNZIPCMDSTRUCT FAR *ucs){
  ucs->unzipStructSize = sizeof(UNZIPCMDSTRUCT);
  ucs->function = 9;  // intentionally out of range
  ucs->lpszZIPFile = (LPSTR)NULL ;
  ucs->zInfo = (ZIPINFO FAR *)NULL;
  ucs->lpszFilespec = (LPSTR)NULL ;
  ucs->index = -1;
  ucs->lpszDestination = (LPSTR)NULL ;
  ucs->freshenFlag = (BOOL)FALSE;
  ucs->updateFlag = (BOOL)FALSE;
  ucs->overWriteFlag = (BOOL)FALSE;
  ucs->quietFlag = (BOOL)FALSE;
  ucs->testFlag = (BOOL)FALSE;
  ucs->noDirectoryNamesFlag = (BOOL)TRUE;
  ucs->recurseFlag = (BOOL)TRUE;
  ucs->noDirectoryItemsFlag = (BOOL)TRUE;
  ucs->lpMinorStatus = (FARPROC)NULL;
  ucs->lpMinorUserData = (void FAR *)NULL;
  ucs->lpMajorStatus = (FARPROC)NULL;
  ucs->lpMajorUserData = (void FAR *)NULL;
  ucs->returnCount = 0;
  ucs->lpszReturnString = (LPSTR)NULL;
  ucs->bDiagnostic = FALSE;
  ucs->bLF2CRLFFlag = (BOOL)FALSE;
  ucs->decryptFlag = FALSE;
  ucs->lpszDecryptCode = (LPSTR)NULL;
  // rev 2.00
  ucs->lpMessageDisplay = lpMsgDispProc;
  ucs->lpMessageDisplayData = (void FAR *)&MsgDispData;
  ucs->wUnzipSubOptions = 0;

  // added for rev 3.00
  ucs->lResv1 = 0L;
  ucs->lResv2 = 0L;
  ucs->lpRenameProc = (FARPROC)NULL;
  ucs->lpRenameUserData = (void FAR *)NULL;;
  ucs->lpszExtProgTitle = (LPSTR)NULL;
  ucs->lpMemBlock = (void FAR *)NULL;
  ucs->lMemBlockSize = 0L;
  ucs->lStartingOffset = 0L;
  
  // nothing cancelled yet
  gbCancel = FALSE;

}

HRESULT UnzipFileFromFile( CString strSourceFileName, CString& strDestinationFileName) {
 HRESULT hResult;
 ZIPINFO zi;
 UNZIPCMDSTRUCT ucs;
 int iNumFiles;;
 char szTemp[_MAX_PATH];
 char szFileName[_MAX_PATH];
 
	initUNZIPCmdStruct((UNZIPCMDSTRUCT FAR *)&ucs);
	ucs.lpszZIPFile = strSourceFileName.GetBuffer(_MAX_PATH);
    ucs.function = UNZIP_COUNTALLZIPMEMBERS;
    hResult = dunzip((UNZIPCMDSTRUCT FAR *) &ucs);
	strSourceFileName.ReleaseBuffer();
    if(hResult != UE_OK){
		wsprintf((LPSTR)szTemp,(LPSTR)"%s is an invalid ZIP file, operation aborted!",
          (LPSTR)	strSourceFileName.GetBuffer(_MAX_PATH));
		strSourceFileName.ReleaseBuffer();
		MessageBox(NULL, (LPSTR)szTemp, "Dynazip Alert", MB_ICONEXCLAMATION | MB_OK);
		hResult = -1;
    }
    iNumFiles = ucs.returnCount;
    if( hResult == 0 ) {
		initUNZIPCmdStruct((UNZIPCMDSTRUCT FAR *)&ucs);
		ucs.lpszZIPFile = strSourceFileName.GetBuffer(_MAX_PATH);
		ucs.function = UNZIP_GETNEXTZIPINFO;
		ucs.zInfo = (ZIPINFO FAR *)&zi;
        ucs.noDirectoryItemsFlag = true;
        ucs.noDirectoryNamesFlag = true;
		do {
			hResult = dunzip((UNZIPCMDSTRUCT FAR *)&ucs);
			if(hResult != UE_OK){
				wsprintf((LPSTR)szTemp,(LPSTR)"%s is an invalid ZIP file, operation aborted!",
				  (LPSTR)	strSourceFileName.GetBuffer(_MAX_PATH));
				strSourceFileName.ReleaseBuffer();
				MessageBox(NULL, (LPSTR)szTemp, "Dynazip Alert", MB_ICONEXCLAMATION | MB_OK);
				hResult = -1;
			}
        } while( (hResult == 0) && (0 == (zi.attr & 0x00000020) ) );
		strSourceFileName.ReleaseBuffer();

        if( hResult == 0 ) {
            ExtractFilename(szFileName, zi.szFileName);
			CreateTempDirName( strDestinationFileName );
        	initUNZIPCmdStruct((UNZIPCMDSTRUCT FAR *)&ucs);
			ucs.lpszZIPFile = strSourceFileName.GetBuffer(_MAX_PATH);
            ucs.function = UNZIP_EXTRACT;
            ucs.noDirectoryItemsFlag = true;
            ucs.noDirectoryNamesFlag = true;
            ucs.overWriteFlag = true;
            ucs.lpszFilespec = szFileName;
			ucs.lpszDestination = strDestinationFileName.GetBuffer(_MAX_PATH);

			hResult = dunzip((UNZIPCMDSTRUCT FAR *)&ucs);
			strSourceFileName.ReleaseBuffer();
			strDestinationFileName.ReleaseBuffer();
			strDestinationFileName += ucs.lpszFilespec;
        }
	}
    return hResult;
}

OPENFILENAME  ofn;

HANDLE hInst;
HWND hwndMain, hDlg;

BOOL bOverwriteWarn = TRUE;
BOOL bDeleteWarn = FALSE;
BOOL bOverwriteRO = FALSE;
BOOL bSkipLockedFiles = FALSE;
BOOL bSavePaths = FALSE;
BOOL bAppendPaths = FALSE;
int iZIPCompLevel = 5;
BOOL bDeleteAfterZIP = FALSE;
BOOL bUseTempDir = FALSE;
BOOL bIncludeSysHide = FALSE;
BOOL bIgnoreLongNames = FALSE;
BOOL bMangleLongNames = FALSE;
BOOL bIgnoreLongNamesUnzip = FALSE;
BOOL bMangleLongNamesUnzip = FALSE;
BOOL bInProcess = FALSE;
BOOL bForceRemovableZIP = FALSE;
BOOL bForceRemovableUnzip = FALSE;
BOOL gbYesToAll = FALSE;

// Multi-Volume Settings
BOOL bFormatVolume  = FALSE;
BOOL bWipeVolume    = FALSE;
BOOL bWipeSubDirs   = FALSE;
BOOL bWipeSysHidden = FALSE;
BOOL bLowDensity    = FALSE;
BOOL bPlaceCDFirst  = FALSE;

int winPosUpLeftX, winPosUpLeftY;
char szStatus1[_MAX_PATH], szStatus2[_MAX_PATH];
char encryptCode[_MAX_PATH];
static HFONT hfontSmall;

// Globals related to retrieving Version Information
char *gszVerString[] = 
    {
		  "InternalName",
			"ProductVersion",
			"LegalCopyright",
			"SpecialBuild",
			NULL
		};

typedef struct tagDLGINIT
{
  char *szMsg;
  char *szTitle;

}DLGINIT;

typedef DLGINIT *LPDLGINIT;



/****************************************************************************

    FUNCTION: DlgWndProc(HWND, UINT, UINT, LONG)

    PURPOSE:  Processes messages for Dialog Box

****************************************************************************/
/*
BOOL FAR PASCAL DlgWndProc(HWND hWnd,UINT message, UINT wParam,
                           LONG lParam)

{
  char szTemp[_MAX_PATH], szMsg[_MAX_PATH];
  int i, fileCount;
  HDC hdcStatic, hdcParent; / * handle of display context * /
  HWND hwndStatic;          / * handle of static control  * /
    
  switch(message){
    case WM_CTLCOLORDLG:
      return((long)GetStockObject(LTGRAY_BRUSH));
      break;

    case WM_CTLCOLORSTATIC: 
    case WM_CTLCOLORBTN:
      hdcStatic = (HDC) wParam;   / * handle of display context * /
      hwndStatic = (HWND) lParam; / * handle of static control  * /
      hdcParent = GetDC(hWnd);
      SetBkColor(hdcStatic,GetBkColor(hdcParent));
      ReleaseDC(hWnd, hdcParent); 
      SetBkMode(hdcStatic, TRANSPARENT);
      return((long)GetStockObject(LTGRAY_BRUSH));
      break;

    case WM_INITDIALOG:
      hDlg = hWnd;
      SendDlgItemMessage(hDlg, IDE_ZIPFILENAME, EM_SETREADONLY, TRUE, 0L);
      SetDlgItemText(hDlg, IDE_EXTRACTTO, (LPSTR)szInitialDir);
      SendDlgItemMessage(hDlg, IDC_STATUS2, WM_SETSTATUSPERCENT, 0, 0L);
      SendDlgItemMessage(hDlg, IDC_STATUS2, WM_SETSTATUSBASEMSG, 
              (WORD)0, (long)(LPSTR)"");
      if (fillInZIPInfo())
        EnableWindow(GetDlgItem(hDlg, IDB_ADDFILES), TRUE);
      else
        EnableWindow(GetDlgItem(hDlg, IDB_ADDFILES), FALSE);
      EnableWindow(GetDlgItem(hDlg, IDB_EXECUTE), FALSE);
      SendDlgItemMessage(hDlg, IDC_INCLUDEPATH, BM_SETCHECK,(bAppendPaths ? 1 : 0), 0L);
      EnableWindow(GetDlgItem(hDlg, IDC_CANCEL), FALSE);
      return TRUE;
      break;

    case WM_COMMAND:
      // only allow command processing if zip/unzip process is inactive
      if(!bInProcess) switch((int)LOWORD(wParam)){
        case IDC_FILELIST:
          switch(HIWORD(wParam)){
            case LBN_SELCHANGE: // the user changed the selection somehow
              i =  (int)SendDlgItemMessage(hDlg, IDC_FILELIST, LB_GETSELCOUNT, 0, 0L);
              wsprintf((LPSTR)szTemp, "%d Item(s) Selected", i);
                SendDlgItemMessage(hDlg, IDC_STATUS2, WM_SETSTATUSBASEMSG, 
                      (WORD)0, (long)(LPSTR)szTemp);
              if(i == 0){
                EnableWindow(GetDlgItem(hDlg, IDB_EXTRACTFILES), FALSE);
                EnableWindow(GetDlgItem(hDlg, IDB_DELETEFILES), FALSE);
              }
              else{
                EnableWindow(GetDlgItem(hDlg, IDB_EXTRACTFILES), TRUE);
                EnableWindow(GetDlgItem(hDlg, IDB_DELETEFILES), TRUE);
              }
              EnableWindow(GetDlgItem(hDlg, IDB_EXECUTE), 
                    (i == 1 ? TRUE : FALSE));
              fileCount = (int)SendDlgItemMessage(hDlg, IDC_FILELIST, LB_GETCOUNT, 0, 0L);
              EnableWindow(GetDlgItem(hDlg, IDC_SELECTALL), 
                    ((fileCount == i) && (fileCount != 0) ? FALSE : TRUE));
              break;
      
            case LBN_DBLCLK: // the user double clicked an item
              gbYesToAll = FALSE;
              executeFile();
              break;
          }
          break;

        case IDB_OPENEXIST:
          gbYesToAll = FALSE;
          ExtractFilename((LPSTR) szTemp, (LPSTR)szZIPFileName);
          getInputFileName(hDlg,(LPSTR)szTemp);
          if(szTemp[0] != '\0'){  // the user actually selected something
            if(validZIPFile((LPSTR)szTemp)){ // it's a real zip file
              lstrcpy((LPSTR)szZIPFileName, szTemp);
              AnsiUpper((LPSTR)szZIPFileName);
              if (fillInZIPInfo())
                EnableWindow(GetDlgItem(hDlg, IDB_ADDFILES), TRUE);
              else
                EnableWindow(GetDlgItem(hDlg, IDB_ADDFILES), FALSE);
            }
            else{
              wsprintf((LPSTR)szMsg,(LPSTR)"%s an empty or invalid ZIP file, operation aborted!",
                  (LPSTR)szTemp);
              MessageBox(hDlg, (LPSTR)szMsg, "Dynazip Alert", MB_ICONEXCLAMATION | MB_OK);
              szZIPFileName[0] = '\0';
              UpdateWindow(hDlg);
            }
          }
          break;

        case IDB_CREATENEW:
          gbYesToAll = FALSE;
          createNewZIP();
          break;

        case IDC_SELFEXTRACT:
          gbYesToAll = FALSE;
          if(strlen(szZIPFileName) == 0){
            if(MessageBox(hDlg, 
                    (LPSTR)"You do not currently have a ZIP file open, continue anyway?",
                    "Dynazip Alert", MB_ICONQUESTION | MB_OKCANCEL ) == IDCANCEL)
              break;        
          }
          if(ShellExecute(hDlg, (LPSTR)NULL, (LPSTR)"selfex.exe", 
                      (LPSTR)szZIPFileName, (LPSTR)szTempDir, SW_SHOW) <= (HINSTANCE)32) // we had an error
            MessageBox(hDlg, 
                    (LPSTR)"Could not run SELFEX.EXE.  Be sure this program "\
                    "is somewhere on your path, and retry the operation.",    
                    "Dynazip Alert", MB_ICONASTERISK | MB_OK );
          break;

        case IDB_BROWSE:
          GetDlgItemText(hDlg, IDE_EXTRACTTO, (LPSTR)szTemp, sizeof(szTemp));
          if(szTemp[strlen(szTemp)-1] != '\\')
            lstrcat((LPSTR)szTemp, "\\");
          lstrcat((LPSTR)szTemp, "*.*");
          GetDestDirectory(hDlg, (LPSTR)szTemp, (LPSTR)"Get Extract-to Directory");
          if(lstrlen((LPSTR)szTemp) != 0){
            SetDlgItemText(hDlg, IDE_EXTRACTTO, (LPSTR)szTemp);
            lstrcpy((LPSTR)szInitialDir, (LPSTR)szTemp);
          }
          break;

        case IDE_EXTRACTTO:
          if(HIWORD(wParam) == EN_CHANGE){
            GetDlgItemText(hDlg, IDE_EXTRACTTO, (LPSTR)szInitialDir, sizeof(szInitialDir));
          }
          break;

        case IDB_EXTRACTFILES:
          gbYesToAll = FALSE;
          extractSelectedFiles();
          break;

        case IDB_REFRESH:
          gbYesToAll = FALSE;
          if (fillInZIPInfo())
            EnableWindow(GetDlgItem(hDlg, IDB_ADDFILES), TRUE);
          else
            EnableWindow(GetDlgItem(hDlg, IDB_ADDFILES), FALSE);
          break;

        case IDB_ADDFILES:
          gbYesToAll = FALSE;
          addNewFiles();
          break;

        case IDC_SELECTALL:
          fileCount = (int)SendDlgItemMessage(hDlg, IDC_FILELIST, LB_GETCOUNT, 0, 0L);
          SendDlgItemMessage(hDlg, IDC_FILELIST, LB_SELITEMRANGE, (WORD)TRUE, 
              MAKELPARAM(0, fileCount-1));
          PostMessage(hWnd, WM_COMMAND, 
              MAKEWPARAM((WORD)IDC_FILELIST,(WORD)LBN_SELCHANGE), 0L);
          break;

        case IDB_DELETEFILES:
          gbYesToAll = FALSE;
          deleteSelectedFiles();
          break;

        case IDC_INCLUDEPATH:
          bAppendPaths = (BOOL)SendDlgItemMessage(hDlg, IDC_INCLUDEPATH, 
                        BM_GETCHECK, 0, 0L);
          break;

        case IDB_EXECUTE:
          gbYesToAll = FALSE;
          if(SendDlgItemMessage(hDlg, IDC_FILELIST, LB_GETSELCOUNT, 0, 0L) == 1)
            executeFile();
          break;
          
        default:
          break; 
      }
      else{
        switch((int)LOWORD(wParam)){
          // we're in a zip/unzip process now, only cancel allowed
          case IDC_CANCEL:
            gbCancel = TRUE;
            break;
       
          default:
            break; 
        }
      }
      return (long)TRUE;
      break;    

  }
  return (long)FALSE;
}
*/
//---------------------------------------------------------------------------
/*
void extractSelectedFiles(){                 
  int selcount, i, totalItems;
  char szMemberSpec[_MAX_PATH];
  char szNew1[_MAX_PATH],szNew2[_MAX_PATH];
  HGLOBAL hSelArray;
  int FAR * lpSelArray;
  ZIPINFO zi;
  int error;
  HCURSOR hOldCursor;
  UNZIPCMDSTRUCT ucs;
  BOOL bResponse;
     
  // initialize the UNZIP command structure
  initUNZIPCmdStruct((UNZIPCMDSTRUCT FAR *)&ucs);
  ucs.lpszZIPFile = (LPSTR)szZIPFileName;
  ucs.noDirectoryNamesFlag = !bAppendPaths;
  ucs.overWriteFlag = !bOverwriteWarn;
  ucs.bLF2CRLFFlag = IsDlgButtonChecked(hDlg, IDC_LF2CRLF);
  // retrieve the extract-to path
  GetDlgItemText(hDlg, IDE_EXTRACTTO, (LPSTR)&szMemberSpec[0], sizeof(szMemberSpec));
  ucs.lpszDestination = (LPSTR)szMemberSpec;

  selcount =  (int)SendDlgItemMessage(hDlg, IDC_FILELIST, LB_GETSELCOUNT, 0, 0L);
  totalItems =  (int)SendDlgItemMessage(hDlg, IDC_FILELIST, LB_GETCOUNT, 0, 0L);

  if ((selcount == 0) || (totalItems == 0)) return; // There's something amiss
  // make a buffer for the selection array
  hSelArray = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, selcount * sizeof(int));
  if (!hSelArray)
    // put some kind of error message here
    return;
  lpSelArray = (int FAR *)GlobalLock(hSelArray);
  if(!lpSelArray){
    // put some kind of error message here
    GlobalFree(hSelArray);
    return;
  }
  // fill in the selection array
  if((int)SendDlgItemMessage(hDlg, IDC_FILELIST, LB_GETSELITEMS, 
        selcount, (LPARAM)(int FAR*)lpSelArray) != selcount){
    // put some kind of error message here
    GlobalUnlock(hSelArray);
    GlobalFree(hSelArray);
    return;
  }
  preserveStatusBars();
  
  wsprintf((LPSTR)szNew2, (LPSTR)"Extracting %d item(s)", selcount);
  SendDlgItemMessage(hDlg, IDC_STATUS2, WM_SETSTATUSBASEMSG, 
        (WORD)0, (long)(LPSTR)szNew2);
  UpdateWindow(GetDlgItem(hDlg,IDC_STATUS2)); 
  EnableWindow(GetDlgItem(hDlg, IDC_CANCEL), TRUE);
  bInProcess = TRUE;
  for(i = 0 ; i < selcount ; i++){
    if(selcount > 1){
      wsprintf((LPSTR)szNew2, (LPSTR)"Item %d of %d", i+1, selcount);
      bResponse = MajorStatusCallback((LPSTR)szNew2, (100 * (i+1))/selcount, (void FAR *)&hDlg);
      if(bResponse){ // user said cancel operation
        MessageBox(hDlg, (LPSTR)"Operation cancelled by user", 
              "Dynazip Alert", MB_ICONEXCLAMATION | MB_OK);
        UpdateWindow(hDlg);
        break;        
      }
    }  
    ucs.function = UNZIP_GETINDEXEDZIPINFO;
    ucs.lpszZIPFile = (LPSTR)szZIPFileName;
    ucs.index = *(lpSelArray + i);
    ucs.zInfo = (ZIPINFO FAR *)&zi;
    if(dunzip((UNZIPCMDSTRUCT FAR *) &ucs) == UE_OK){ // check for valid item
  
      // finally ready to unzip something
      SendDlgItemMessage(hDlg, IDC_STATUS, WM_SETSTATUSPERCENT, 0, 0L);
      UpdateWindow(GetDlgItem(hDlg, IDC_STATUS));

      hOldCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
      ucs.index = zi.index;
        
      // inform us for each item extracted
      ucs.lpMinorStatus = (FARPROC)lpMinorStatus;
      ucs.lpMinorUserData = (void FAR *)&hDlg;

      // here's where the actual unzipping occurs
      ucs.function = UNZIP_EXTRACT;
      if(GetDlgItemText(hDlg, IDC_ENCRYPTCODE, (LPSTR)encryptCode, sizeof(encryptCode)-1) != 0){
        if(IsDlgButtonChecked(hDlg, IDC_ENCRYPT)){
          ucs.decryptFlag = TRUE;
          ucs.lpszDecryptCode = (LPSTR)encryptCode;
        }
      }
      error = dunzip((UNZIPCMDSTRUCT FAR *) &ucs);
      //
      if(error == UE_SKIP) 
        error = 0;
      else if((error == UE_CANCEL) || (error == UE_ABORT)){
        break;
      }
      SetCursor(hOldCursor);
      if(error != 0){
        wsprintf((LPSTR)szNew1, "UNZIP error: %s", (LPSTR)UNZIPerrors[error]);
        MessageBox(hDlg, (LPSTR)szNew1, "Dynazip Alert", MB_ICONEXCLAMATION | MB_OK);
        UpdateWindow(hDlg);
        break;
      }
    }
  }
  bInProcess = FALSE;
  EnableWindow(GetDlgItem(hDlg, IDC_CANCEL), FALSE);

  // Make sure the user sees 100%
  SendDlgItemMessage(hDlg, IDC_STATUS2, WM_SETSTATUSPERCENT, 100, 0L);
  UpdateWindow(GetDlgItem(hDlg,IDC_STATUS2)); 

  // restore the state of both status bars
  restoreStatusBars();
  GlobalUnlock(hSelArray);
  GlobalFree(hSelArray);
  return; 
}
*/
//---------------------------------------------------------------------------
/*
void deleteSelectedFiles(){
  LPSTR lpszLargeFileList;
  int selcount, i, totalItems;
  char szNew1[_MAX_PATH],szNew2[_MAX_PATH];
  HGLOBAL hSelArray, hFileList;
  int FAR * lpSelArray;
  ZIPINFO zi;
  int response, deletedCount;
  HCURSOR hOldCursor;
  OFSTRUCT ofs;
  ZIPCMDSTRUCT zcs;
  UNZIPCMDSTRUCT ucs;
  DWORD buffLen = 20000;
  char szTemp[_MAX_PATH];
     
  // initialize the ZIP and UNZIP command structures
  initZIPCmdStruct((ZIPCMDSTRUCT far *)&zcs);
  initUNZIPCmdStruct((UNZIPCMDSTRUCT far *)&ucs);
  
  // set up for the output file name
  zcs.lpszZIPFile = (LPSTR)szZIPFileName;

  selcount =  (int)SendDlgItemMessage(hDlg, IDC_FILELIST, LB_GETSELCOUNT, 0, 0L);
  totalItems =  (int)SendDlgItemMessage(hDlg, IDC_FILELIST, LB_GETCOUNT, 0, 0L);
  deletedCount = 0; // nothing's been deleted yet
  
  if ((selcount == 0) || (totalItems == 0)) return; // There's something amiss
  ucs.lpszZIPFile = (LPSTR) szZIPFileName;
  ucs.function = UNZIP_COUNTALLZIPMEMBERS;
  response = dunzip((UNZIPCMDSTRUCT FAR *)&ucs);
  if(response != ZE_OK){
    wsprintf((LPSTR)szTemp, "ZIP error: %s", (LPSTR)ZIPerrors[response]);
    MessageBox(hDlg, (LPSTR)szTemp, (LPSTR)"DynaZIP Alert", MB_OK | MB_ICONINFORMATION);
    UpdateWindow(hDlg);      
    return;
  }
  if(selcount == ucs.returnCount){
    wsprintf((LPSTR)szNew1,
        (LPSTR)"You have selected all of the items in ZIP File %s. Do you want to delete this ZIP file from your disk?",
          (LPSTR)szZIPFileName);
    if((response = MessageBox(hDlg, (LPSTR)szNew1, 
          "Dynazip Alert", MB_ICONQUESTION | MB_YESNOCANCEL )) == IDCANCEL)
      return;
    else if(response == IDYES){
      UpdateWindow(hDlg);
      if(OpenFile((LPSTR)szZIPFileName,(OFSTRUCT FAR *)&ofs, OF_DELETE) == HFILE_ERROR){
        wsprintf((LPSTR)szNew1,
          (LPSTR)"File %s could not be deleted!", (LPSTR)szZIPFileName);
        MessageBox(hDlg, (LPSTR)szNew1, "Dynazip Alert", MB_ICONASTERISK | MB_OK );
        return; 
      }
      szZIPFileName[0] = '\0';
      fillInZIPInfo();
      EnableWindow(GetDlgItem(hDlg, IDB_ADDFILES), FALSE);
      return; 
    }
  }
  UpdateWindow(hDlg);      
  // make a buffer for the file name array
  hFileList = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, buffLen); // probably big enough
  if (!hFileList)
    // put some kind of error message here
    return;
  lpszLargeFileList = (LPSTR)GlobalLock(hFileList);
  if(!lpszLargeFileList){
    // put some kind of error message here
    GlobalFree(hFileList);
    return;
  }
  // make a buffer for the selection array
  hSelArray = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, selcount * sizeof(int));
  if (!hSelArray){
    // put some kind of error message here
    GlobalUnlock(hFileList);
    GlobalFree(hFileList);
    return;
  }
  lpSelArray = (int FAR *)GlobalLock(hSelArray);
  if(!lpSelArray){
    // put some kind of error message here
    GlobalUnlock(hFileList);
    GlobalFree(hFileList);
    GlobalFree(hSelArray);
    return;
  }
  // fill in the selection array
  if((int)SendDlgItemMessage(hDlg, IDC_FILELIST, LB_GETSELITEMS, 
        selcount, (LPARAM)(int FAR*)lpSelArray) != selcount){
    // put some kind of error message here
    GlobalUnlock(hSelArray);
    GlobalFree(hSelArray);
    GlobalUnlock(hFileList);
    GlobalFree(hFileList);
    return;
  }
  preserveStatusBars();
  // build the string to be used for the delete operation
  for(i = 0 ; i < selcount ; i++){
    ucs.function = UNZIP_GETINDEXEDZIPINFO;
    ucs.lpszZIPFile = (LPSTR) szZIPFileName;
    ucs.index = *(lpSelArray + i);
    ucs.zInfo = (ZIPINFO FAR *) &zi;
    if(dunzip((UNZIPCMDSTRUCT FAR *)&ucs) == UE_OK){ // check for valid item
  
      if(bDeleteWarn){
        wsprintf((LPSTR)szNew1,
            (LPSTR)"You are about to delete %s from ZIP File %s. Is this what you want to do?",
              (LPSTR)zi.szFileName, (LPSTR)szZIPFileName);
        if((response = MessageBox(hDlg, (LPSTR)szNew1, 
              "Dynazip Alert", MB_ICONQUESTION | MB_YESNOCANCEL )) == IDCANCEL)
          break;
        else if(response == IDNO){
          UpdateWindow(hDlg);
          continue;
        }
        UpdateWindow(hDlg);
      }
      lstrcat((LPSTR)lpszLargeFileList, (LPSTR)"\"");
      lstrcat((LPSTR)lpszLargeFileList, (LPSTR)zi.szFileName);
      lstrcat((LPSTR)lpszLargeFileList, (LPSTR)"\" ");
      deletedCount++;
    }
  }
  UpdateWindow(hDlg);      
  if(deletedCount != 0){  // now we're ready to delete the group
    bInProcess = TRUE;
    // get rid of the ' ' at the end of the list (if any)
    lpszLargeFileList[lstrlen(lpszLargeFileList) - 1] = '\0';
    zcs.lpszItemList = (LPSTR)lpszLargeFileList;
    hOldCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
    wsprintf((LPSTR)szNew2, (LPSTR)"Deleting %d item(s)", deletedCount);
    SendDlgItemMessage(hDlg, IDC_STATUS2, WM_SETSTATUSBASEMSG, 
        (WORD)0, (long)(LPSTR)szNew2);
    UpdateWindow(GetDlgItem(hDlg,IDC_STATUS2)); 
    SetDlgItemText(hDlg, IDE_ZIPFILENAME, (LPSTR)szZIPFileName);
    UpdateWindow(GetDlgItem(hDlg,IDE_ZIPFILENAME)); 
    zcs.lpMajorStatus = lpMajorStatus;
    zcs.lpMajorUserData = (void FAR *)&hDlg;
    zcs.lpMinorStatus = lpMinorStatus;
    zcs.lpMinorUserData = (void FAR *)&hDlg;
    zcs.function = ZIP_DELETE;
    initZCSMultiVol((ZIPCMDSTRUCT FAR *)&zcs);
    // here's where the actual deleting takes place
    response =  dzip((ZIPCMDSTRUCT FAR *)&zcs); 
    //
    
    bInProcess = FALSE;
    SetCursor(hOldCursor);
  }
  if(response != ZE_OK){
    wsprintf((LPSTR)szTemp, "ZIP error: %s", (LPSTR)ZIPerrors[response]);
    MessageBox(hDlg, (LPSTR)szTemp, (LPSTR)"DynaZIP Alert", MB_OK | MB_ICONINFORMATION);
    UpdateWindow(hDlg);      
  }

  // Make sure the user sees 100%
  SendDlgItemMessage(hDlg, IDC_STATUS2, WM_SETSTATUSPERCENT, 100, 0L);
  UpdateWindow(GetDlgItem(hDlg,IDC_STATUS2)); 

  restoreStatusBars();
  GlobalUnlock(hFileList);
  GlobalFree(hFileList);
  GlobalUnlock(hSelArray);
  GlobalFree(hSelArray);
  if(deletedCount != 0) // something was deleted, we need to update the item list
    fillInZIPInfo();
  return; 
}
//---------------------------------------------------------------------------

BOOL validZIPFile(LPSTR szTestFile){
  UNZIPCMDSTRUCT ucs;

  initUNZIPCmdStruct((UNZIPCMDSTRUCT FAR *)&ucs);
  ucs.lpszZIPFile = szTestFile;
  ucs.function = UNZIP_COUNTALLZIPMEMBERS;
  if(dunzip((UNZIPCMDSTRUCT FAR *)&ucs) != UE_OK)
    return FALSE;
  return TRUE;
}
//---------------------------------------------------------------------------
// Returns TRUE if filled in OK, FALSE i there's some problem with the
// ZIP file as specified.

BOOL fillInZIPInfo(){
  int response, i, j;  
  ZIPINFO zi;
  char szTemp[_MAX_PATH], szMethod[50], szPerc[4], szTemp2[20], szTemp3[20];
  LPSTR lpSz2, lpSz3;
  long perc;
  HCURSOR hOldCursor;
  TEXTMETRIC tm;
  WORD wLongest = 0, wLBWidth;
  RECT rc1;
  HDC hDc;
  DWORD dwStringExt;
  long lBytesTotal;
  UNZIPCMDSTRUCT ucs;
  char szAttributes[9];
  SIZE size;
    
  initUNZIPCmdStruct((UNZIPCMDSTRUCT FAR *)&ucs);
  if(szZIPFileName[0] == '\0'){ // there is no name recorded (yet)
    SetDlgItemText(hDlg, IDE_ZIPFILENAME, (LPSTR)"No ZIP File Selected");
    SendDlgItemMessage(hDlg, IDC_FILELIST, LB_RESETCONTENT, 0, 0L);
    EnableWindow(GetDlgItem(hDlg, IDB_EXTRACTFILES), FALSE);
    EnableWindow(GetDlgItem(hDlg, IDB_DELETEFILES), FALSE);
    EnableWindow(GetDlgItem(hDlg, IDB_EXECUTE), FALSE);
    EnableWindow(GetDlgItem(hDlg, IDC_SELECTALL), FALSE);
    SendDlgItemMessage(hDlg, IDC_STATUS, WM_SETSTATUSBASEMSG, 
            (WORD)0, (long)(LPSTR)"");
    SendDlgItemMessage(hDlg, IDC_STATUS2, WM_SETSTATUSBASEMSG, 
            (WORD)0, (long)(LPSTR)"");
    UpdateWindow(hDlg);
    return FALSE;
  }
  else{ // there is a name, get the info
    ExtractFilename((LPSTR) szTemp, (LPSTR)szZIPFileName);
    ExtractWorkingDir((LPSTR)szDefaultZIPDir, (LPSTR)szZIPFileName);
    SetDlgItemText(hDlg, IDE_ZIPFILENAME, (LPSTR)szZIPFileName);
    ucs.function = UNZIP_COUNTALLZIPMEMBERS;
    ucs.lpszZIPFile = (LPSTR) szZIPFileName;
    response = dunzip((UNZIPCMDSTRUCT FAR *)&ucs);
    j = ucs.returnCount;
    if(response != UE_OK){
      wsprintf((LPSTR)szTemp,(LPSTR)"%s is an invalid ZIP file, operation aborted!",
          (LPSTR)szZIPFileName);
      MessageBox(hDlg, (LPSTR)szTemp, "Dynazip Alert", MB_ICONEXCLAMATION | MB_OK);
      szZIPFileName[0] = '\0';
      return FALSE;
    }
    SendDlgItemMessage(hDlg, IDC_FILELIST, LB_RESETCONTENT, 0, 0L);
    SendDlgItemMessage(hDlg, IDC_FILELIST, LB_SETHORIZONTALEXTENT,0, 0L);
    hOldCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
    GetClientRect(GetDlgItem(hDlg,IDC_FILELIST), (LPRECT)&rc1);
    hDc = GetDC(GetDlgItem(hDlg,IDC_FILELIST));
    DPtoLP(hDc, (LPPOINT) &rc1, 2);
    wLBWidth = (WORD)(rc1.right - rc1.left); 
    GetTextMetrics(hDc, (TEXTMETRIC FAR *) & tm);
    lBytesTotal = 0;
    wsprintf((LPSTR)szTemp, (LPSTR)"Reading %s", (LPSTR)szZIPFileName);
    SendDlgItemMessage(hDlg, IDC_STATUS, WM_SETSTATUSBASEMSG, 
            (WORD)0, (long)(LPSTR)szTemp);
    UpdateWindow(hDlg);
    for(i = 0 ; i < j ; i++){
      ucs.function = UNZIP_GETNEXTZIPINFO;
      ucs.zInfo = (ZIPINFO FAR *)&zi;
      ucs.lpszZIPFile = (LPSTR) szZIPFileName;
      if(dunzip((UNZIPCMDSTRUCT FAR *)&ucs) != UE_OK){
        SetCursor(hOldCursor);
        ReleaseDC(GetDlgItem(hDlg,IDC_FILELIST), hDc);
        SendDlgItemMessage(hDlg, IDC_STATUS, WM_SETSTATUSPERCENT, 0, 0L);
        SendDlgItemMessage(hDlg, IDC_STATUS, WM_SETSTATUSBASEMSG, 
              (WORD)0, (long)(LPSTR)"");
        return FALSE;
      }
      switch(zi.cMethod){
        case 0:
          lstrcpy((LPSTR)szMethod, (LPSTR)"Stored");
          break;
        case 1:
          lstrcpy((LPSTR)szMethod, (LPSTR)"Shrunk");
          break;
        case 2:
          lstrcpy((LPSTR)szMethod, (LPSTR)"Reduced1");
          break;
        case 3:
          lstrcpy((LPSTR)szMethod, (LPSTR)"Reduced2");
          break;
        case 4:
          lstrcpy((LPSTR)szMethod, (LPSTR)"Reduced3");
          break;
        case 5:
          lstrcpy((LPSTR)szMethod, (LPSTR)"Reduced4");
          break;
        case 6:
          lstrcpy((LPSTR)szMethod, (LPSTR)"Imploded");
          break;
        case 7:
          lstrcpy((LPSTR)szMethod, (LPSTR)"Tokenized");
          break;
        case 8:
          lstrcpy((LPSTR)szMethod, (LPSTR)"Deflated");
          break;
        default:
          lstrcpy((LPSTR)szMethod, (LPSTR)"Unknown");
          break;
      }          
      if(zi.oSize <= zi.cSize){
        perc = 0;
      }
      else{
        perc = max(0,(100L * (zi.oSize - zi.cSize)) / zi.oSize);
      }
      wsprintf((LPSTR)szPerc, "%s%ld%%",(perc < 10 ? (LPSTR)"0" : (LPSTR)""), perc);  
      wsprintf((LPSTR)szAttributes, "%c%c%c%c%c%c%c%c",
        zi.attr & ARCHIVE ? 'a' : '-',
        zi.attr & SUBDIR ? 'd' : '-',
        zi.attr & VOLUME ? 'v' : '-',
        zi.attr & SYSTEM ? 's' : '-',
        zi.attr & HIDDEN ? 'h' : '-',
        zi.attr & READONLY ? 'r' : '-',
        zi.attr & ENCRYPT ? '*' : ' ',
        zi.attr & LFNAME ? 'L' : ' ');
      wsprintf((LPSTR)szTemp, "%s\t%ld\t%ld\t%s    %s\t%s\t%s",
        (LPSTR)zi.szDateTime,
        (long)zi.cSize,
        (long)zi.oSize,
        (LPSTR)szPerc,
        (LPSTR)szMethod,
        (LPSTR)szAttributes,
        (LPSTR)zi.szFileName);

        GetTextExtentPoint32(hDc, (LPCSTR)szTemp, strlen(szTemp), &size); 
        dwStringExt = size.cx  + 12 * tm.tmAveCharWidth; // empirically figured 

//      dwStringExt = GetTextExtent(hDc, (LPSTR) szTemp, 
//            strlen(szTemp)) + 12 * tm.tmAveCharWidth; // empirically figured

      lBytesTotal += zi.oSize;
      if((LOWORD(dwStringExt) > wLongest) &&
          (LOWORD(dwStringExt) > wLBWidth)){
        wLongest = LOWORD(dwStringExt);
      }
      SendDlgItemMessage(hDlg, IDC_FILELIST, LB_ADDSTRING, 0, (LPARAM)(LPCSTR) szTemp);
      if(j > 20){
        SendDlgItemMessage(hDlg, IDC_STATUS, WM_SETSTATUSPERCENT, (WORD)(((long)i * 100L) / (long)j), 0L);
        UpdateWindow(GetDlgItem(hDlg, IDC_STATUS));
      }
    }
		if(j > 0){
      SendDlgItemMessage(hDlg, IDC_FILELIST, LB_SETHORIZONTALEXTENT, wLongest, 0L);
		}
    SendDlgItemMessage(hDlg, IDC_STATUS, WM_SETSTATUSPERCENT, 0, 0L);
    wsprintf((LPSTR)szTemp2, (LPSTR)"%ld", lBytesTotal);
    i = lstrlen((LPSTR)szTemp2) % 3;    // get ready to add some commas
    if (i == 0) i = 3;
    lpSz2 = (LPSTR) &szTemp2[0];  // the source string for the total size
    lpSz3 = (LPSTR) &szTemp3[0];  // the comma delimited output  
    while(*lpSz2 != '\0'){
      *(lpSz3++) = *(lpSz2++);
      if(--i == 0){
        *(lpSz3++) = ',';
        i = 3;
      }
    }
    *(--lpSz3) = '\0'; 
    wsprintf((LPSTR)szTemp, (LPSTR)"%d Total Items, %s bytes total", j, (LPSTR)szTemp3);
    SendDlgItemMessage(hDlg, IDC_STATUS, WM_SETSTATUSBASEMSG, 
            (WORD)0, (long)(LPSTR)szTemp);
    SendDlgItemMessage(hDlg, IDC_STATUS2, WM_SETSTATUSBASEMSG, 
              (WORD)0, (long)(LPSTR)"0 Item(s) Selected");
    EnableWindow(GetDlgItem(hDlg, IDB_EXTRACTFILES), FALSE);
    EnableWindow(GetDlgItem(hDlg, IDB_DELETEFILES), FALSE);
    EnableWindow(GetDlgItem(hDlg, IDB_EXECUTE), FALSE);
    if(j != 0)
      EnableWindow(GetDlgItem(hDlg, IDC_SELECTALL), TRUE);
    SetCursor(hOldCursor);
    ReleaseDC(GetDlgItem(hDlg,IDC_FILELIST), hDc);
    return TRUE;
  }
}
*/
/*
BOOL getInputFileName(HWND hwndOwner, LPSTR lpstrFile)
{
  char szExt[_MAX_EXT];
  static char szLastInputFileDir[_MAX_PATH] = "";
  char szFileName[_MAX_PATH] = "";
  char rFilter[_MAX_PATH] = "ZIP Files(*.ZIP)|*.ZIP|All Files|*.*||";
  int i;
  
  for(i = 0 ; rFilter[i] != '\0' ; i++){
    if(rFilter[i] == '|')
      rFilter[i] = '\0';
  }
  // Prompt user for name of file to use for input
  lstrcpy((LPSTR)szLastInputFileDir, (LPSTR) szDefaultZIPDir);
	memset(&ofn, 0, sizeof(OPENFILENAME));
  ofn.lpstrTitle        = (LPSTR)"DynaZIP - Open ZIP File";
  ofn.lpstrInitialDir   = (LPSTR)szLastInputFileDir;
  lstrcpy((LPSTR)szFileName, (LPSTR)lpstrFile);
  lstrcpy((LPSTR)szExt, (LPSTR)"");
  ofn.lStructSize       = sizeof(OPENFILENAME);
  ofn.hwndOwner         = hwndOwner;
//  ofn.hInstance         = hInst;
  ofn.lpstrFilter       = (LPSTR)rFilter;
  ofn.lpstrCustomFilter = (LPSTR)NULL;
  ofn.nMaxCustFilter    = 0L;
  ofn.nFilterIndex      = 1;
  ofn.lpstrFile         = (LPSTR)szFileName;
  ofn.nMaxFile          = sizeof(szFileName);
  ofn.lpstrFileTitle    = (LPSTR)NULL;
  ofn.nMaxFileTitle     = 0;
  ofn.Flags             = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
  ofn.nFileOffset       = 0;
  ofn.nFileExtension    = 0;
  ofn.lpstrDefExt       = (LPSTR)"ZIP";
  ofn.lCustData          = (DWORD)0L;

  if(GetOpenFileName(&ofn)){
    lstrcpy((LPSTR)lpstrFile, (LPSTR)ofn.lpstrFile);
    ExtractWorkingDir((LPSTR)szDefaultZIPDir, (LPSTR)ofn.lpstrFile);
  }
  else{
    lpstrFile[0] = '\0';
    return FALSE;
  }
  return TRUE;
}
*/
// ---------------------------------------------------------------------------
/* This is called when an input filename is needed
 *
 */
/*
BOOL getExeFileName(HWND hwndOwner, LPSTR lpstrFile)
{
  char szExt[_MAX_EXT];
  static char szLastInputFileDir[_MAX_PATH] = "";
  char szFileName[_MAX_PATH] = "";
  char rFilter[_MAX_PATH] = "Programs etc.|*.EXE;*.PIF;*.BAT;*.COM|All Files|*.*||";
  int i;
  
  for(i = 0 ; rFilter[i] != '\0' ; i++){
    if(rFilter[i] == '|')
      rFilter[i] = '\0';
  }
  // Prompt user for name of file to use for input
  lstrcpy((LPSTR)szLastInputFileDir, (LPSTR) szDefaultZIPDir);
	memset(&ofn, 0, sizeof(OPENFILENAME));
  ofn.lpstrTitle        = (LPSTR)"Get Program Name";
  ofn.lpstrInitialDir   = (LPSTR)szLastInputFileDir;
  lstrcpy((LPSTR)szFileName, (LPSTR)lpstrFile);
  lstrcpy((LPSTR)szExt, (LPSTR)"");
  ofn.lStructSize       = sizeof(OPENFILENAME);
  ofn.hwndOwner         = hwndOwner;
//  ofn.hInstance         = hInst;
  ofn.lpstrFilter       = (LPSTR)rFilter;
  ofn.lpstrCustomFilter = (LPSTR)NULL;
  ofn.nMaxCustFilter    = 0L;
  ofn.nFilterIndex      = 1;
  ofn.lpstrFile         = (LPSTR)szFileName;
  ofn.nMaxFile          = sizeof(szFileName);
  ofn.lpstrFileTitle    = (LPSTR)NULL;
  ofn.nMaxFileTitle     = 0L;
  ofn.Flags             = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
  ofn.nFileOffset       = 0;
  ofn.nFileExtension    = 0;
  ofn.lpstrDefExt       = (LPSTR)"EXE";
  ofn.lCustData          = (DWORD)0L;

  if(GetOpenFileName(&ofn)){
    lstrcpy((LPSTR)lpstrFile, (LPSTR)ofn.lpstrFile);
    ExtractWorkingDir((LPSTR)szDefaultZIPDir, (LPSTR)ofn.lpstrFile);
  }
  else{
    lpstrFile[0] = '\0';
    return FALSE;
  }
  return TRUE;
}
*/
// ---------------------------------------------------------------------------
/* This is called when an output filename is needed
 *
 */
/*
BOOL getOutputFileName(HWND hwndOwner, LPSTR lpstrFile)
{
  char szExt[_MAX_EXT];
  static char szLastInputFileDir[_MAX_PATH] = "";
  char szFileName[_MAX_PATH] = "";
  char sFilter[_MAX_PATH] = "ZIP Files(*.ZIP)|*.ZIP|All Files|*.*||";
  int i;
  
  for(i = 0 ; sFilter[i] != '\0' ; i++){
    if(sFilter[i] == '|')
      sFilter[i] = '\0';
  }
  lstrcpy((LPSTR)szLastInputFileDir, (LPSTR) szDefaultZIPDir);
  // Prompt user for name of file to use for input
	memset(&ofn, 0, sizeof(OPENFILENAME));
  ofn.lpstrTitle        = (LPSTR)"DynaZIP - Create ZIP File";
  ofn.lpstrInitialDir   = (LPSTR)szLastInputFileDir;
  lstrcpy((LPSTR)szFileName, (LPSTR)lpstrFile);
  lstrcpy((LPSTR)szExt, (LPSTR)"");
  ofn.lStructSize       = sizeof(OPENFILENAME);
  ofn.hwndOwner         = hwndOwner;
//  ofn.hInstance         = hInst;
  ofn.lpstrFilter       = (LPSTR)sFilter;
  ofn.lpstrCustomFilter = (LPSTR)NULL;
  ofn.nMaxCustFilter    = 0L;
  ofn.nFilterIndex      = 1;
  ofn.lpstrFile         = (LPSTR)szFileName;
  ofn.nMaxFile          = sizeof(szFileName);
  ofn.lpstrFileTitle    = (LPSTR)NULL;
  ofn.nMaxFileTitle     = 0L;
//  if(IsDlgButtonChecked(hDlg, IDC_USEMULTIVOLUME) && (bFormatVolume || bWipeVolume)){
    // path does not have to exist for Multi Volume with Formatting or Wiping turned on
    ofn.Flags  = OFN_HIDEREADONLY;
//  }
//  else{
//    ofn.Flags  = OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
//  }
  ofn.nFileOffset       = 0;
  ofn.nFileExtension    = 0;
  ofn.lpstrDefExt       = (LPSTR)"ZIP";
  ofn.lCustData          = (DWORD)0L;

  if(GetSaveFileName(&ofn)){
    lstrcpy((LPSTR)lpstrFile, (LPSTR)ofn.lpstrFile);
    ExtractWorkingDir((LPSTR)szDefaultZIPDir, (LPSTR)ofn.lpstrFile);
  }
  else{
    lpstrFile[0] = '\0';
    return FALSE;
  }
  return TRUE;
}
*/
// ---------------------------------------------------------------------------
/* This is called when (possibly) more than one input filenames are needed
 *
 */
/*
BOOL getMultiFileName(HWND hwndOwner, LPSTR lpstrFile, DWORD buffLen)
{
  char szExt[_MAX_EXT];
  static char szLastInputFileDir[_MAX_PATH] = "";
  char rFilter[_MAX_PATH] = "All Files|*.*||";
  int i;
  BOOL bMulti;
  
  for(i = 0 ; rFilter[i] != '\0' ; i++){
    if(rFilter[i] == '|')
      rFilter[i] = '\0';
  }
  lstrcpy((LPSTR)szLastInputFileDir, (LPSTR) szDefaultSourceDir);
	memset(&ofn, 0, sizeof(OPENFILENAME));
	memset(lpstrFile, ' ', buffLen - 1);
	lpstrFile[buffLen - 1] = 0;
  // Prompt user for name of file to use for input
  ofn.lpstrTitle        = (LPSTR)"DynaZIP - Select Items To Add";
  ofn.lpstrInitialDir   = (LPSTR)szLastInputFileDir;
  lstrcpy((LPSTR)szExt, (LPSTR)"");
  ofn.lStructSize       = sizeof(OPENFILENAME);
  ofn.hwndOwner         = hwndOwner;
//  ofn.hInstance         = hInst;
  ofn.lpstrFilter       = (LPSTR)rFilter;
  ofn.lpstrCustomFilter = (LPSTR)NULL;
  ofn.nMaxCustFilter    = 0L;
  ofn.nFilterIndex      = 1;
  ofn.lpstrFile         = (LPSTR)lpstrFile;
  ofn.nMaxFile          = (DWORD)buffLen;
  ofn.lpstrFileTitle    = (LPSTR)NULL;
  ofn.nMaxFileTitle     = 0L;
  ofn.Flags             = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT;
  ofn.nFileOffset       = 0;
  ofn.nFileExtension    = 0;
  ofn.lpstrDefExt       = (LPSTR)"ZIP";
  ofn.lCustData          = (DWORD)0L;

  bMulti = FALSE;
  if(GetOpenFileName(&ofn)){
	  // The return buffer (ofn.lpstrFile) has the following format for multiple selections
		// <dir>0<file1>0<file2>0...<fileN>00
		// <dir> = root path of selections and will end in a backslash  such as "c:\temp\"
		// <file1 thru N> the filenames
		//  0 = single zero terminator character
		// 00 = double zero terminator character pair
		lstrcpy(szDefaultSourceDir, ofn.lpstrFile);
		if(ofn.lpstrFile[lstrlen(szDefaultSourceDir) + 1] != 0){
		  // multiple files have been selected
		  bMulti = TRUE;
		}
		else{
		  // a single file was seleted
		  ExtractPath((LPSTR)szDefaultSourceDir, (LPSTR)ofn.lpstrFile);
		}
	}
  else{
    lpstrFile[0] = '\0';
    return FALSE;
  }
  return TRUE;
}
*/
/*
//-------------------------------------------------------------------------------
LONG FAR PASCAL StatusWndProc(HWND hwnd, WORD msg, WORD wParam, long lParam)
// handles the status bar window
{
PAINTSTRUCT ps;
HBRUSH      hOldBrush;
HPEN        hOldPen, hNewPen;
static HFONT hOldFont;
HDC         hDC, hDCPerc;
RECT        rc1, rc2;
int         OldBkMode, rightEdge;
int         percent;
char        szMessage[129];
char        szPercent[10];

  switch(msg){

    case WM_CREATE:
      SetWindowWord(hwnd, WW_STATPERCENT, (WORD)0);
      SetWindowWord(hwnd, WW_STATPERCENT_OLD, (WORD)0);
      SetWindowText(hwnd, (LPSTR)"");
      break;

    case WM_PAINT:
      // force clearing of area behind percent text display
      hDCPerc = GetDC(hwnd);
      GetClientRect(hwnd, &rc1);
      CopyRect((LPRECT)&rc2, (LPRECT)&rc1);
      rc2.right = rc2.left + 33;
      InflateRect((LPRECT)&rc2, -1, -1);
      hOldPen = SelectObject(hDCPerc, GetStockObject(NULL_PEN));
      hOldBrush = SelectObject(hDCPerc, GetStockObject(LTGRAY_BRUSH));
      Rectangle(hDCPerc, rc2.left, rc2.top, rc2.right, rc2.bottom);

      // draw the percent text, if not null
      percent = (int)GetWindowWord(hwnd, WW_STATPERCENT);
      if(percent != 0){
        hOldFont = SelectObject(hDCPerc, hfontSmall);
        OldBkMode = SetBkMode(hDCPerc, TRANSPARENT);
        wsprintf((LPSTR)szPercent, (LPSTR)"%d%%", percent);
        DrawText(hDCPerc, szPercent, -1, &rc2, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
        SetBkMode(hDCPerc, OldBkMode);
        SelectObject(hDCPerc, hOldFont);
      }
      // put the DC back the way you found it
      SelectObject(hDCPerc, hOldPen);
      SelectObject(hDCPerc, hOldBrush);
      ReleaseDC(hwnd, hDCPerc);

      // now ready to do the area that has been invalidated
      hDC = BeginPaint(hwnd, &ps);
      hOldBrush = SelectObject(hDC, GetStockObject(LTGRAY_BRUSH));
      hOldFont = SelectObject(hDC, hfontSmall);
      OldBkMode = SetBkMode(hDC, TRANSPARENT);

      // first draw the border, upper/left = dark gray line
      hNewPen = CreatePen(PS_SOLID, 1, RGB(65,65,65));  // make a dark gray pen
      hOldPen = SelectObject(hDC, hNewPen);
      MoveToEx(hDC, rc1.left, rc1.bottom - 1, (LPPOINT)NULL);
      LineTo(hDC, rc1.left, rc1.top);
      LineTo(hDC, rc1.right, rc1.top);

      // ...lower/right = white line
      SelectObject(hDC, GetStockObject(WHITE_PEN));
      MoveToEx(hDC, rc1.left, rc1.bottom - 1, (LPPOINT)NULL);
      LineTo(hDC, rc1.right - 1, rc1.bottom - 1);
      LineTo(hDC, rc1.right - 1, rc1.top);

      // shrink down a pixel and draw the uniform gray background
      InflateRect((LPRECT)&rc1, -1, -1);
      rc1.left += 32;       // avoid the percent text area
      if(rc1.right < rc1.left){
        rc1.right = rc1.left;
      }
      if(rc1.bottom < rc1.top){
        rc1.bottom = rc1.top;
      }
      SelectObject(hDC, GetStockObject(NULL_PEN));
      Rectangle(hDC, rc1.left, rc1.top, rc1.right-1, rc1.bottom);
      
      // if percent is other than 0, we have to draw the bar
      if(percent != 0){
        // draw the status bar
        rightEdge = rc1.left + (int)((long)((long)percent * 
                        (long)(rc1.right - rc1.left)) / 100L);
        SelectObject(hDC, GetStockObject(WHITE_BRUSH));
        SetWindowWord(hwnd, WW_STATPERCENT_OLD, (WORD)(rightEdge - 1));
        Rectangle(hDC, rc1.left, rc1.top, rightEdge, rc1.bottom + 1);
      }
      GetWindowText(hwnd, (LPSTR)szMessage, sizeof(szMessage) - 1);
      if(lstrlen((LPSTR)szMessage) != 0){
        rc1.left = 42;
        DrawText(hDC, szMessage, -1, &rc1, DT_VCENTER | DT_SINGLELINE);
      }
      SetBkMode(hDC, OldBkMode);
      SelectObject(hDC, hOldFont);
      SelectObject(hDC, hOldBrush);
      SelectObject(hDC, hOldPen);
      DeleteObject(hNewPen);
      EndPaint(hwnd, &ps);
      break;

    case WM_SETSTATUSBASEMSG:
      if(lParam){
        SetWindowText(hwnd, (LPSTR)lParam);
        GetClientRect(hwnd, &rc1);
        rc1.left += 32;
        InvalidateRect(hwnd, (LPRECT)&rc1, FALSE);
      }
      return(0L);

    case WM_GETSTATUSBASEMSG:
      GetWindowText(hwnd, (LPSTR)lParam, _MAX_PATH);
      return(0L);

    case WM_SETSTATUSPERCENT:
      percent = wParam;
      if(percent < 0){
        percent = 0;
      }
      if(percent > 100){
        percent = 100;
      }
      if((percent == 0) && (percent != GetWindowWord(hwnd, WW_STATPERCENT))){
        InvalidateRect(hwnd, (LPRECT)NULL, TRUE);
      }
      if(((int)GetWindowWord(hwnd, WW_STATPERCENT) != percent) || (percent == 0)){
        SetWindowWord(hwnd, WW_STATPERCENT, (WORD)percent);
        if(percent == 0){
          SetWindowWord(hwnd, WW_STATPERCENT_OLD, (WORD)0);
        }
        else{
          GetClientRect(hwnd, &rc1);
          rc1.left = GetWindowWord(hwnd, WW_STATPERCENT_OLD);
          rc1.right = 32 + (int)((long)((long)percent * 
                        (long)(rc1.right - 32)) / 100L);
          InvalidateRect(hwnd, (LPRECT)&rc1, FALSE);
        }
      }
      return(0L);

    case WM_GETSTATUSPERCENT:
      return((long)GetWindowWord(hwnd, WW_STATPERCENT));

    case WM_SHOWSTATUSWINDOW:
      ShowWindow(hwnd, SW_SHOW);
      BringWindowToTop(hwnd);
      return(0L);

    case WM_HIDESTATUSWINDOW:
      ShowWindow(hwnd, SW_HIDE);
      return(0L);

    case WM_DESTROY:
      return (0L);
    default:
      return(DefWindowProc(hwnd, msg, wParam, lParam));

  }

  return(DefWindowProc(hwnd, msg, wParam, lParam));
}
*/
//---------------------------------------------------------------------------
/*
#ifdef USE_MINORCANCEL
BOOL FAR PASCAL MinorStatusCallback(LPSTR szItem, long percent, void FAR *lpUserData)
#else
void FAR PASCAL MinorStatusCallback(LPSTR szItem, long percent, void FAR *lpUserData)
#endif
{
  WORD iPercent;
  HWND hWnd;
  char szTemp[_MAX_PATH];
  MSG msg;
  
  hWnd = *(HWND FAR *)lpUserData;

  // simple message pump that Cancels if WM_QUIT is received
  while(PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE)){
    if(msg.message == WM_QUIT){
      gbCancel = TRUE;
    }
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  if((LPSTR)szItem != (LPSTR)NULL){
    SendDlgItemMessage(hWnd, IDC_STATUS, WM_GETSTATUSBASEMSG, 
            (WORD)0, (long)(LPSTR)szTemp);
    if((lstrcmp((LPSTR)szTemp, (LPSTR)szItem) != 0)  || (percent == 0)){
      SendDlgItemMessage(hWnd, IDC_STATUS, WM_SETSTATUSBASEMSG, 
            (WORD)0, (long)(LPSTR)szItem);
    }
  }
  else
    SendDlgItemMessage(hWnd, IDC_STATUS, WM_SETSTATUSBASEMSG, 
            (WORD)0, (long)(LPSTR)"");
  
  iPercent = (int)percent;
  SendDlgItemMessage(hWnd, IDC_STATUS, WM_SETSTATUSPERCENT, (WORD)iPercent, 0L);
  UpdateWindow(GetDlgItem(hWnd,IDC_STATUS));
#ifdef USE_MINORCANCEL
  return(gbCancel);
#else
  return
#endif
}
//---------------------------------------------------------------------------
BOOL FAR PASCAL MajorStatusCallback(LPSTR szItem, long percent, void FAR *lpUserData)
{                                       
  WORD iPercent;
  HWND hWnd;
  char szTemp[_MAX_PATH];
  MSG msg;
    
  hWnd = *(HWND FAR *)lpUserData; 
  
  // simple message pump that Cancels if WM_QUIT is received
  while(PeekMessage(&msg, (HWND)NULL, 0, 0, PM_REMOVE)){
    if(msg.message == WM_QUIT){
      gbCancel = TRUE;
    }
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  SendDlgItemMessage(hWnd, IDC_STATUS2, WM_GETSTATUSBASEMSG, 
            (WORD)0, (long)(LPSTR)szTemp);
  if(lstrcmp((LPSTR)szTemp, (LPSTR)szItem) != 0){
    SendDlgItemMessage(hWnd, IDC_STATUS2, WM_SETSTATUSBASEMSG, 
            (WORD)0, (long)(LPSTR)szItem);
  }

  iPercent = (int)percent;
  SendDlgItemMessage(hWnd, IDC_STATUS2, WM_SETSTATUSPERCENT, (WORD)iPercent, 0L);
  UpdateWindow(GetDlgItem(hWnd,IDC_STATUS2));
  return gbCancel;
}
//---------------------------------------------------------------------------
int FAR PASCAL MessageDisplay(UINT MsgID, UINT mbType, int p1, int p2, LPSTR lpsz1, LPSTR lpsz2, void FAR *lpMessageDisplayData)
{                                       
int response;
  // assume the DLL will have to handle this message
  response = -1;
  
  switch(MsgID){
    case MSGID_DISK:
    case MSGID_DISKOFDISK:
      // Let DLL handle these messages
      lstrcpy(lpsz2, "DynaZIP Shell Request!");
      break;

    case MSGID_NOREMOVE:
    case MSGID_ZFORMAT:
    case MSGID_SAMEVOL:
    case MSGID_ERROR:
    case MSGID_ZOPEN:
    case MSGID_ZREAD:
    case MSGID_ZWRITE:
    case MSGID_MVBADFIRSTDISK:
      // Let DLL handle these messages
      lstrcpy(lpsz2, "DynaZIP Shell Error!");
      break;


    case MSGID_WARN:
      // We handle the Warnings in the shell 
      lstrcpy(lpsz2, "DynaZIP Shell Warning!");
      response = MessageBox((HWND)NULL, lpsz1, lpsz2, MB_TASKMODAL | mbType);
      break;

    case MSGID_OVERWRT:
      // Let DLL handle this with RENAME Capability
      // Use p1 value to determine if the file is Read Only or NOT.
      // p1 = 0 if Read / Write
      // p1 = 1 if Read Only
      if(!gbYesToAll){
        response = OverWriteRename(lpsz1, lpsz2);
        if(response == IDIGNORE){
          gbYesToAll = TRUE;
        }
      }
      else{
        response = IDIGNORE;
      }
      break;

    case MSGID_CODEERR:
      // We handle the encryption code error in the shell
      lstrcpy(lpsz2, "DynaZIP Shell Error!");
      response = MessageBox((HWND)NULL, lpsz1, lpsz2, MB_TASKMODAL | mbType);
      break;

    case MSGID_CHANGE:
	  // Add code here to change any Native DynaZIP Messages
	  break;

    default:
      // Let DLL handle these messages
      lstrcpy(lpsz2, "DynaZIP Shell Alert!");
      break;
      

  }
  return(response);
}
//----------------------------------------------------------------------------------
void GetDestDirectory(HWND hwndOwner, LPSTR lpFilename, LPSTR lpTitle)
{
  char     szFileNameOnly[_MAX_FNAME];
  char     szDir[_MAX_PATH];
  char     szExt[_MAX_EXT];
  FARPROC  lpHookProc;
  char rFilter[_MAX_PATH] = "ZIP Files(*.ZIP)|*.ZIP|All Files|*.*||";
  int i;
  
  for(i = 0 ; rFilter[i] != '\0' ; i++){
    if(rFilter[i] == '|')
      rFilter[i] = '\0';
  }
  lstrcpy((LPSTR)szGlobalDest, (LPSTR)lpFilename);
  // make a local copy of the incoming path/file
  ExtractFilename((LPSTR)szFileNameOnly, lpFilename);
  ExtractWorkingDir((LPSTR)szDir, lpFilename);
  AdjustPathForFileOpenDlgs((LPSTR)szDir);

  lstrcpy((LPSTR)szExt, (LPSTR)"");

  lpHookProc = (FARPROC)MakeProcInstance((FARPROC)GetDestHookProc, hInst);
	memset(&ofn, 0, sizeof(OPENFILENAME));

  ofn.lStructSize       = sizeof(OPENFILENAME);
  ofn.hwndOwner         = (HWND)hwndOwner;
  ofn.hInstance         = (HANDLE)hInst;
  ofn.lpstrFilter       = (LPSTR)rFilter;
  ofn.lpstrCustomFilter = (LPSTR)NULL;
  ofn.nMaxCustFilter    = 0L;
  ofn.nFilterIndex      = 1;
  ofn.lpstrFile         = (LPSTR)szFileNameOnly;
  ofn.nMaxFile          = sizeof(szFileNameOnly);
  ofn.lpstrFileTitle    = (LPSTR)NULL;
  ofn.nMaxFileTitle     = 0L;
  ofn.lpstrInitialDir   = (LPSTR)szDir;
  ofn.lpstrTitle        = (LPSTR)lpTitle;
  ofn.Flags             = OFN_HIDEREADONLY |OFN_PATHMUSTEXIST |
                          OFN_ENABLETEMPLATE  | OFN_ENABLEHOOK;
  ofn.nFileOffset       = 0;
  ofn.nFileExtension    = 0;
  ofn.lpstrDefExt       = (LPSTR)szExt;
  ofn.lCustData          = 0L;
  ofn.lpfnHook          = (UINT (CALLBACK *)(HWND, UINT, WPARAM, LPARAM))lpHookProc;
  ofn.lpTemplateName    = (LPSTR)MAKEINTRESOURCE(IDD_DIALOG2);

  if(GetSaveFileName(&ofn)){
    lstrcpy((LPSTR)szDir, (LPSTR)ofn.lpstrFile);
    ExtractWorkingDir1(lpFilename, (LPSTR)szDir);
    FreeProcInstance(lpHookProc);
  }
  else{
    lstrcpy((LPSTR)lpFilename, (LPSTR)"");
    FreeProcInstance(lpHookProc);
  }
  return;
}
// **************************************************************************************
//
//  Procedure:  GetDestHookProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
//
//  Purpose:  callback function for the customized Get Extract-to Path
//
// **************************************************************************************
BOOL FAR PASCAL  GetDestHookProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
char szDir[_MAX_PATH];
HWND hwndFocus;

  switch(msg){
    case WM_INITDIALOG:
      ExtractWorkingDir((LPSTR)szDir, (LPSTR)szGlobalDest);
      SetDlgItemText(hDlg, ID_FROMSPEC, (LPSTR)szDir);
      updateSaveAsDir(hDlg);
      // start a watchdog on the directory spec
      SetTimer(hDlg, 1, 250, NULL);
      return TRUE;
      break;

    case WM_DESTROY:
      KillTimer(hDlg, 1);
      break;
    case WM_TIMER:
      updateSaveAsDir(hDlg);
      break;
    case WM_COMMAND:
      switch((int)LOWORD(wParam)){

        case IDOK:
          hwndFocus = GetFocus();
          if(hwndFocus == GetDlgItem(hDlg, ID_TOSPEC)){
            GetDlgItemText(hDlg, ID_TOSPEC, (LPSTR)szDir, sizeof(szDir));
            if((lstrlen((LPSTR)szDir) > 2) &&
               (szDir[lstrlen((LPSTR)szDir) - 1] != '\\')){
              lstrcat((LPSTR)szDir, (LPSTR)"\\");
            }
            lstrcat((LPSTR)szDir, (LPSTR)"*.*");
            SetDlgItemText(hDlg, edt1, (LPSTR)szDir);
            return(FALSE);
          }
          else{
            GetDlgItemText(hDlg, ID_TOSPEC, (LPSTR)szDir, sizeof(szDir));
            if((lstrlen((LPSTR)szDir) > 2) &&
               (szDir[lstrlen((LPSTR)szDir) - 1] != '\\')){
              lstrcat((LPSTR)szDir, (LPSTR)"\\");
            }
            lstrcat((LPSTR)szDir, (LPSTR)"abc.abc");
            if(IsValidPath((LPSTR)szDir)){
              SetDlgItemText(hDlg, edt1, (LPSTR)szDir);
              return(FALSE);
            }
            else{
              return(TRUE);
            }
          }
          break;

        default:
          return FALSE;
      }
      break;
  }
  return FALSE;
}
*/
//------------------------------------------------------------------------------------
/*
void AdjustPathForFileOpenDlgs(LPSTR lpPath)
{
char far *lpc;
int       len;
char      szDir[_MAX_PATH];

  len = lstrlen(lpPath);
  if(len < 2){
    getcwd(szDir, sizeof(szDir) - 1);
    lstrcpy(lpPath, (LPSTR)szDir);
    len = lstrlen(lpPath);
  }
  if(*(lpPath + (len - 1)) != '\\'){
    if(lstrlen(lpPath) <= 2){
      // The path is probably a drive letter followed by a colon.
      // This means that the trailing backslash needs to be present
      // after the colon.
      lpc = strrchr(lpPath, ':');
      if(lpc){
        // add trailing backslash for root
        *++lpc = '\\';
        *++lpc = 0;
      }
    }
  }
  else{
    // There is a backslash in the path
    if(len > 3){
      // Remove trailing backslash from paths that are not at root.
      // Be sure to preserve the subdirectory information.
      lpc = strrchr(lpPath, '\\');
      if(lpc){
        // Trailing backslash was found... get rid of it for
        // path that is not at root
        *lpc = 0;
      }
    }
  }
}
*/

// **************************************************************************************
//
//  Procedure:  updateSaveAsDir(HWND hDlg)
//
//  Purpose:  Displays the current directory
//
// **************************************************************************************
/*
void updateSaveAsDir(HWND hDlg)
{
  char szDir[_MAX_PATH];
  char szTemp[_MAX_PATH];

  getcwd((char *)&szDir[0], sizeof(szDir) - 1);
#if 0
  if((lstrlen((LPSTR)szDir) > 2) &&
     (szDir[lstrlen((LPSTR)szDir) - 1] != '\\')){
    lstrcat((LPSTR)szDir, (LPSTR)"\\");
  }
#endif
  GetDlgItemText(hDlg, ID_TOSPEC, (LPSTR)szTemp, sizeof(szTemp));
  AnsiLower((LPSTR)szTemp);
  AnsiLower((LPSTR)szDir);
  if(strcmp(szDir, szTemp))
    SetDlgItemText(hDlg, ID_TOSPEC, (LPSTR)szDir);
}
*/
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
/*
BOOL IsValidPath(LPSTR lpPath)
{
char     szPath[_MAX_PATH];
BOOL     bRet;


  bRet = FALSE;
  // check for double backslash occurence in path
  if(strstr(lpPath, (LPSTR)"\\\\")){
    return(bRet);
  }
  ExtractWorkingDir((LPSTR)szPath, lpPath);

  if((lstrlen((LPSTR)szPath) > 3) &&
     (szPath[lstrlen((LPSTR)szPath) - 1] == '\\')){
    szPath[lstrlen((LPSTR)szPath) - 1] = 0;
  }
  if(_access(szPath, 0) == 0){
    bRet = TRUE;
  }

  return(bRet);
}
*/
//-------------------------------------------------------------------------------
/*
void readIniFile(){
  int response;

  response = GetProfileString((LPSTR)"DynaZIP", (LPSTR)"Initial Save Directory",
              (LPSTR)"C:\\",(LPSTR)szInitialDir, sizeof(szInitialDir));
  if(response == 0)
    getcwd(szInitialDir, sizeof(szInitialDir));

  response = GetProfileString((LPSTR)"DynaZIP", (LPSTR)"Default ZIP Directory",
              (LPSTR)"C:\\",(LPSTR)szDefaultZIPDir, sizeof(szDefaultZIPDir));
  if(response == 0)
    getcwd(szDefaultZIPDir, sizeof(szDefaultZIPDir));

  response = GetProfileString((LPSTR)"DynaZIP", (LPSTR)"Default Source Directory",
              (LPSTR)"C:\\",(LPSTR)szDefaultSourceDir, sizeof(szDefaultSourceDir));
  if(response == 0)
    getcwd(szDefaultSourceDir, sizeof(szDefaultSourceDir));
    
  response = GetProfileString((LPSTR)"DynaZIP", (LPSTR)"Default Viewer",
              (LPSTR)"Notepad.exe",(LPSTR)szDefaultViewer, sizeof(szDefaultViewer));
  response = GetProfileString((LPSTR)"DynaZIP", (LPSTR)"Temporary Directory",
              (LPSTR)"C:\\tempdir",(LPSTR)szTempDir, sizeof(szTempDir));

  bOverwriteWarn   = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Overwrite Warn",(BOOL)TRUE);
  bDeleteWarn      = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Delete Warn",(BOOL)FALSE);
  bOverwriteRO     = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Overwrite Read Only",(BOOL)FALSE);
  bSkipLockedFiles = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Skip Locked Files",(BOOL)FALSE);

  bFormatVolume   = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Format Volume", (BOOL)FALSE);
  bLowDensity     = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Use Low Density", (BOOL)FALSE);
  bPlaceCDFirst   = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Place CD First", (BOOL)FALSE);
  bWipeVolume     = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Wipe Volume", (BOOL)FALSE);
  bWipeSubDirs    = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Wipe Sub Directories", (BOOL)FALSE);
  bWipeSysHidden  = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Wipe Sys Hidden", (BOOL)FALSE);


  bSavePaths            = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Save With Path",(BOOL)FALSE);
  bAppendPaths          = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Restore With Path",(BOOL)FALSE);
  bDeleteAfterZIP       = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Delete After ZIP",(BOOL)FALSE);
  bIncludeSysHide       = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Include Sys and Hidden",(BOOL)FALSE);
  bIgnoreLongNames      = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Ignore Long Filenames",(BOOL)FALSE);
  bMangleLongNames      = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Mangle Long Filenames",(BOOL)FALSE);
  bIgnoreLongNamesUnzip = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Ignore Long Filenames UNZIP",(BOOL)FALSE);
  bMangleLongNamesUnzip = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Mangle Long Filenames UNZIP",(BOOL)FALSE);
  bForceRemovableZIP    = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Force Removable Media ZIP",   (BOOL)FALSE);
  bForceRemovableUnzip  = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Force Removable Media UNZIP", (BOOL)FALSE);
  iZIPCompLevel         = GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"ZIP Compression Level",5);
  winPosUpLeftX         = GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Window Upper Left X",10);
  winPosUpLeftY         = GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Window Upper Left Y",10);
  bUseTempDir           = (BOOL)GetProfileInt((LPSTR)"DynaZIP", (LPSTR)"Use Temp Dir",(BOOL)FALSE);
  return;
}
//-------------------------------------------------------------------------------
void saveIniFile(){

  WriteProfileString((LPSTR)"DynaZIP", (LPSTR)"Initial Save Directory", (LPSTR)szInitialDir);
  WriteProfileString((LPSTR)"DynaZIP", (LPSTR)"Default ZIP Directory", (LPSTR)szDefaultZIPDir);
  WriteProfileString((LPSTR)"DynaZIP", (LPSTR)"Default Source Directory", (LPSTR)szDefaultSourceDir);
  WriteProfileString((LPSTR)"DynaZIP", (LPSTR)"Default Viewer", (LPSTR)szDefaultViewer);
  WriteProfileString((LPSTR)"DynaZIP", (LPSTR)"Temporary Directory", (LPSTR)szTempDir);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Overwrite Warn",(int)bOverwriteWarn);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Delete Warn",(int)bDeleteWarn);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Overwrite Read Only",(int)bOverwriteRO);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Skip Locked Files",(int)bSkipLockedFiles);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Format Volume",(int)bFormatVolume);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Use Low Density",(int)bLowDensity);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Place CD First",(int)bPlaceCDFirst);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Wipe Volume",(int)bWipeVolume);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Wipe Sub Directories",(int)bWipeSubDirs);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Wipe Sys Hidden",(int)bWipeSysHidden);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Save With Path",(int)bSavePaths);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Restore With Path",(int)bAppendPaths);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Delete After ZIP",(int)bDeleteAfterZIP);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Include Sys and Hidden",(int)bIncludeSysHide);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Ignore Long Filenames",(int)bIgnoreLongNames);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Mangle Long Filenames",(int)bMangleLongNames);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Ignore Long Filenames UNZIP",(int)bIgnoreLongNamesUnzip);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Mangle Long Filenames UNZIP",(int)bMangleLongNamesUnzip);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Force Removable Media ZIP",(int)bForceRemovableZIP);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Force Removable Media UNZIP",(int)bForceRemovableUnzip);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"ZIP Compression Level",iZIPCompLevel);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Window Upper Left X",winPosUpLeftX);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Window Upper Left Y",winPosUpLeftY);
  WriteProfileInt((LPSTR)"DynaZIP", (LPSTR)"Use Temp Dir",(int)bUseTempDir);
  return;
}
*/
// **************************************************************************************
//
//  Procedure:  WriteProfileInt(LPSTR, LPSTR, int, LPSTR)
//
//  Purpose:  this function should have been part of the API
//
// **************************************************************************************
BOOL WriteProfileInt(LPSTR szHeading,LPSTR szSubCat,int value){
  char szIntAsString[15];

  wsprintf((LPSTR)szIntAsString, "%d", value);
  return WriteProfileString(szHeading, szSubCat, (LPSTR)szIntAsString);
}

//--------------------------------------------------------------------------------------------
// Removes Double Quotes from szSrc and places converted string into szDst
// szSrc remains unaffected
// pointer to converted string is returned
// NULL pointer is returned if szSrc or szDst is a NULL pointer
char *RemoveDoubleQuotes(char *szDst, char *szSrc)
{
char *p1, *p2;
int cnt;

  // Remove any double quotes from possible long filenames
  p1 = szSrc;
  p2 = szDst;
  if(p1 && p2){
    cnt = 0;
    while(*p1 && (cnt < _MAX_PATH)){
      if(*p1 != '"'){
        *p2++ = *p1;
        cnt++;
      }
      p1++;
    }
    *p2 = (char)0;
    return(szDst);
  }
  return((char *)NULL);
}

/*
//--------------------------------------------------------------------------------------------
#ifndef WIN32
BOOL FAR PASCAL __export OverWriteRenameDlgProc(HWND hDlg, UINT message , UINT wParam, LONG lParam)
#else
BOOL FAR PASCAL OverWriteRenameDlgProc(HWND hDlg, UINT message , UINT wParam, LONG lParam)
#endif
{
HDC hdcStatic, hdcParent; / * handle of display context * /
HWND hwndStatic;          / * handle of static control  * /
LPDLGINIT lpdlgInit;
    
  if(lParam); // avoid compiler error
  switch(message){
#ifndef WIN32
// Compiling for 16-bit Windows
    case WM_CTLCOLOR:
      switch(HIWORD(lParam)){
        case CTLCOLOR_DLG:
         hdcStatic = (HDC)wParam;   / * handle of display context * /
         SetBkColor(hdcStatic, RGB(192, 192, 192));
         break;
         
        case CTLCOLOR_STATIC: 
        case CTLCOLOR_BTN:
          hdcStatic = (HDC)wParam;   / * handle of display context * /
          hwndStatic = (HWND)(LOWORD(lParam)); / * handle of static control  * /
          hdcParent = GetDC(hDlg);
          SetBkColor(hdcStatic,GetBkColor(hdcParent));
          ReleaseDC(hDlg, hdcParent); 
          SetBkMode(hdcStatic, TRANSPARENT);
          break;
      }
      break;

#else
// Compiling for 32-bit Windows
    case WM_CTLCOLORDLG:
      return((long)GetStockObject(LTGRAY_BRUSH));
      break;

    case WM_CTLCOLORSTATIC: 
    case WM_CTLCOLORBTN:
      hdcStatic = (HDC)wParam;   / * handle of display context * /
      hwndStatic = (HWND)lParam; / * handle of static control  * /
      hdcParent = GetDC(hDlg);
      SetBkColor(hdcStatic,GetBkColor(hdcParent));
      ReleaseDC(hDlg, hdcParent); 
      SetBkMode(hdcStatic, TRANSPARENT);
      return((long)GetStockObject(LTGRAY_BRUSH));
      break;
#endif

    case WM_INITDIALOG:
      lpdlgInit = (LPDLGINIT)lParam;
      SetDlgItemText(hDlg, IDC_MESSAGE, lpdlgInit->szMsg);
      SetWindowText(hDlg, lpdlgInit->szTitle);
#ifdef WIN32
      SetForegroundWindow(hDlg);
#endif
      return(TRUE);
      break;

    case WM_COMMAND:
      switch(LOWORD(wParam)){
        case IDC_YESBUTTON:
          EndDialog(hDlg, IDYES);
          return(TRUE);
          break;
        case IDC_NOBUTTON:
          EndDialog(hDlg, IDNO);
          return(TRUE);
          break;
        case IDC_CANCELBUTTON:
          EndDialog(hDlg, IDCANCEL);
          return(TRUE);
          break;
        case IDC_YESTOALLBUTTON:
          EndDialog(hDlg, IDIGNORE);
          return(TRUE);
          break;

      }
      break;
  }
  return(FALSE);
}
*/