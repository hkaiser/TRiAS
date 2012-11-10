// Menukommandos --------------------------------------------------------------
// File: BSCRMENU.CXX

#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

bool CMacroScriptExtension :: OnInvokeScript (void)
{
CebDebugDlgInfo DlgInfo;
CebEntryInfo EntryInfo;
CebDebuggerDlg DebugDlg (&DlgInfo, ebInst(), EntryInfo, hWnd());

// nStatus (return code) will be one of the following values
// DRC_OUTOFMEMORY	: Insufficient memory to create the debugger dialog
// DRC_CANTCREATEWINDOW	: Unable to create window
// DRC_CANTFINDLIBRARY	: Unable to locate the debugger control library
// DRC_CANCEL		: Script was not saved on exit
// DRC_SAVED		: Script was saved on exit
int nStatus = DebugDlg.Invoke();
char *pszError = NULL;
	
	switch (nStatus) {
	case DRC_CANCEL:	// Only need to free debug.ei.lpWatchesOut
		break;
		
	case DRC_SAVED:		// Free all output information
		break;
			
	case DRC_OUTOFMEMORY:
		pszError = "Insufficient memory to create the Debugger Dialog!";
		break;
			
	case DRC_CANTCREATEWINDOW:
		pszError = "Unable to create window!";
		break;
			
	case DRC_CANTFINDLIBRARY:
		pszError = "Unable to locate the Debugger Control Library!";
		break;
	}
	
	if (pszError) {		// Display error condition
		::AfxMessageBox (pszError);
		return false;
	}
	
return true;
}

