// Wrapperklassen für COMMDLG.H / FileOpen, FileSaveAs
// File: STDDLG.CXX

#include "tfrmpre.hxx"

#include <commdlg.h>

#include "win31imp.hxx"
#include <stddlg.hxx>

// --------------- Dialog Boxes -----------------------------
CStdDialog :: CStdDialog (void) 
{ 
	implementor = 0; 
}

BOOL _DLLENTRY CStdDialog :: Show (void)
{
	if (implementor) 
		return (((CStdDialog_Win31*)implementor) -> Show()); 

return false;
}

CStdDialog :: ~CStdDialog (void) 
{ 
	implementor = 0; 
}

_DLLENTRY CStdColorDlg :: CStdColorDlg (void)
{ 
}

Color _DLLENTRY CStdColorDlg :: GetColor (void)
{
Color retval ((ColorVal)0, (ColorVal)0, (ColorVal)0);

	if (implementor) 
		((CStdColorDlg_Win31*)implementor) -> GetColor(&retval); 

return retval;
}

_DLLENTRY CStdColorDlg :: ~CStdColorDlg (void)
{
}


CStdFileDlg :: CStdFileDlg (void)
{ 
}

CStdFileDlg :: ~CStdFileDlg (void)
{ 
}

void _DLLENTRY CStdFileDlg :: GetFileName (char *buff, int len)
{
	if (implementor) 
		((CStdFileDlg_Win31*)implementor) -> GetFileName(buff, len); 
}

int _DLLENTRY CStdFileDlg :: GetFileNameLen (void)
{
int retval = 0;

	if (implementor) 
		retval = ((CStdFileDlg_Win31*)implementor) -> GetFileNameLen(); 

return retval;
}


long _DLLENTRY CStdFileDlg :: Flags (void)
{
	if (implementor) 
		return ((CStdFileDlg_Win31 *)implementor) -> Flags();

return 0; 
}


void _DLLENTRY CStdFileDlg :: SetFlags (long lNewFlags)
{
	if (implementor) 
		((CStdFileDlg_Win31 *)implementor) -> SetFlags (lNewFlags);
}


void _DLLENTRY CStdFileDlg :: AddFlags (long lNewFlags)
{
	if (implementor) 
		((CStdFileDlg_Win31 *)implementor) -> AddFlags (lNewFlags);
}


void _DLLENTRY CStdFileDlg :: SetHookFcn (HOOKFCN pF)
{
	if (implementor) 
		((CStdFileDlg_Win31 *)implementor) -> SetHookFcn (pF);
}


void _DLLENTRY CStdFileDlg :: SetFilterIndex (int iFilterIndex)
{
	if (implementor) 
		((CStdFileDlg_Win31 *)implementor) -> SetFilterIndex (iFilterIndex);
}


int _DLLENTRY CStdFileDlg :: GetFilterIndex (void)
{
	if (implementor) 
		return ((CStdFileDlg_Win31 *)implementor) -> GetFilterIndex();

return 0;
}


void _DLLENTRY CStdFileDlg :: SetTemplate (HGLOBAL hDlgRes)
{
	if (implementor) 
		((CStdFileDlg_Win31 *)implementor) -> SetTemplate (hDlgRes);
}


void _DLLENTRY CStdFileDlg :: SetTemplate (HINSTANCE hInst, const char *pRcs)
{
	if (implementor) 
		((CStdFileDlg_Win31 *)implementor) -> SetTemplate (hInst, pRcs);
}

void _DLLENTRY CStdFileDlg :: SetCustomData (DWORD lData)
{
	if (implementor) 
		((CStdFileDlg_Win31 *)implementor) -> SetCustomData (lData);
}


BOOL _DLLENTRY CStdFileDlg :: Result (void)
{
	if (implementor) 
		return ((CStdFileDlg_Win31 *)implementor) -> Result();

return false;
}

void _DLLENTRY CStdFileDlg :: SetCaption (const char *lpCaption)
{
	if (implementor)
		((CStdFileDlg_Win31 *)implementor) -> SetCaption (lpCaption);
}


void _DLLENTRY CStdFileDlg :: SetFileName (const char *pName)
{
	if (implementor)
		((CStdFileDlg_Win31 *)implementor) -> SetFileName (pName);
}


void _DLLENTRY CStdFileDlg :: SetInitialDir (const char *pPath)
{
	if (implementor)
		((CStdFileDlg_Win31 *)implementor) -> SetInitialDir (pPath);
}



_DLLENTRY COpenDialog :: COpenDialog (pWindow Parent, char *TheFileSpec) 
{
	implementor = (void *)new OpenDlg_Win31 (Parent -> Handle(), TheFileSpec);
}

_DLLENTRY COpenDialog :: ~COpenDialog (void)
{
// delete implementor
	if (implementor) 
		delete (OpenDlg_Win31*)implementor; 
}


_DLLENTRY CSaveAsDialog :: CSaveAsDialog (pWindow Parent, char *SaveDirectory) 
{
	implementor = (void *)new SaveAsDlg_Win31 (Parent -> Handle(), SaveDirectory);
}


_DLLENTRY CSaveAsDialog :: ~CSaveAsDialog (void)
{
	if (implementor) 
		delete (SaveAsDlg_Win31*)implementor; 
}


