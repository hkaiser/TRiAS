#include "stdafx.h"
#include "resource.h"

// globale Funktionen -- Ausgabe von Fehlermeldungen
void OutputInfo (const CString strInfo)
{
	:: MessageBox (NULL, strInfo, AfxGetAppName (), MB_ICONINFORMATION | MB_OK);	
}

void OutputError (const CString &strError)
{
	:: MessageBox (NULL, strError, AfxGetAppName (), MB_ICONHAND | MB_OK);
}          

void OutputMemoryError ()
{
	CString strNoMemory;
	VERIFY (strNoMemory.LoadString (IDS_NOMEMORY));
	OutputError (strNoMemory);
}

void OutputFileError (int iCause)
{
	UINT uiResID = 0;
		           
	switch (iCause)
	{                                  
		case CFileException::badPath:
		case CFileException::fileNotFound:
			uiResID = IDS_FILE_NOT_FOUND;			
		break;
		case CFileException::tooManyOpenFiles:
			uiResID = IDS_TOO_MANY_OPEN_FILES;
		break;
		case CFileException::accessDenied:
			uiResID = IDS_ASSESS_DENIED;
		break;
		case CFileException::removeCurrentDir:
			uiResID = IDS_REMOVE_CURRENT_DIR;
		break;                        
		case CFileException::diskFull:				
		case CFileException::directoryFull:
			uiResID = IDS_DIRECTORY_FULL;
		break;
		case CFileException::hardIO:
			uiResID = IDS_HARD_IO;
		break;
		case CFileException::sharingViolation:
		case CFileException::lockViolation:
			uiResID = IDS_LOCK_VIOLATION;
		break;
		case CFileException::none:
		case CFileException::generic:
		case CFileException::invalidFile:
		case CFileException::badSeek:				
		case CFileException::endOfFile:
		default:
			uiResID = IDS_FILE_ERROR;
		break;				         
	}
		
//	Fehlermeldung ausgeben		    
	ASSERT (uiResID > 0);
	CString strFileErr;
	VERIFY (strFileErr.LoadString (uiResID));		    
	OutputError (strFileErr);			
}
