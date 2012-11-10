
#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#if defined(WIN32)
#include "afxcmn.h"
#endif // WIN32

#include <direct.h>

#include "fndrpld.h"

CFindReplaceDlg :: CFindReplaceDlg (void)
{
}


bool CFindReplaceDlg :: FInit ()
{
return true;
}


CFindReplaceDlg :: ~CFindReplaceDlg (void)
{
}


CFindReplaceDlg *CFindReplaceDlg :: CreateInstance ()
{
CFindReplaceDlg *pCFindReplaceDlg = new CFindReplaceDlg();
	if(pCFindReplaceDlg == NULL || !pCFindReplaceDlg -> FInit () ) {
		if (pCFindReplaceDlg) delete pCFindReplaceDlg;
		return NULL;
	}
return pCFindReplaceDlg;
}

