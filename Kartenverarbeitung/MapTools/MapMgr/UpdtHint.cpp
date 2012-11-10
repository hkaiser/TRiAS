#include "stdafx.h"
#include "UpdtHint.h"

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: updthint.cpp 1.1 1996/07/12 10:50:04 andy Exp andy $";
/* $Log: updthint.cpp $
// Revision 1.1  1996/07/12  10:50:04  andy
// initial version
//
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CUpdateHint,CObject);

tagMAPINFO::tagMAPINFO()
{
	m_lpszMapIdent = NULL;
	m_lpszMapName = NULL;
	ptr.vPtr = NULL;
}

CUpdateHint::CUpdateHint(LPMAPINFO pI)
{
	m_wParam = 0;
	pInfo = pI;
}