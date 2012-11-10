#include "stdafx.h"

#ifdef LAFX_CORE_SEG
#pragma code_seg(LAFX_CORE_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
/*{{RCS
initial version
RCS}}*/
static char* pszRCS = "$Id: lafxinl1.cpp 1.1 1996/07/12 17:16:16 andy Exp $";
/* $Log: lafxinl1.cpp $
// Revision 1.1  1996/07/12  17:16:16  andy
// initial version
//
*/
/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

#ifndef _AFX_ENABLE_INLINES			// _DEBUG is defined

#ifdef AFX_DBG1_SEG
#pragma code_seg(AFX_DBG1_SEG)
#endif

static char BASED_CODE _szAfxInl[] = "lafx.inl";
#undef THIS_FILE
#define THIS_FILE _szAfxInl
#define _AFX_INLINE
#include "lmfcx/lafx.inl"

static char BASED_CODE _szAfxCollInl[] = "lafxcoll.inl";
#undef THIS_FILE
#define THIS_FILE _szAfxCollInl
#define _AFXCOLL_INLINE
#include "lmfcx/lafxcoll.inl"

#endif //!_AFX_ENABLE_INLINES
