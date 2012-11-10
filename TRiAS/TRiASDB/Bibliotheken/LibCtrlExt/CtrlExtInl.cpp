#include "lmfcx/LafxCtrl.h"

#ifdef LAFX_CORE_SEG
#pragma code_seg(LAFX_CORE_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Inlines

#ifndef _AFX_ENABLE_INLINES			// _DEBUG is defined

#ifdef AFX_DBG1_SEG
#pragma code_seg(AFX_DBG1_SEG)
#endif

static char BASED_CODE _szAfxWinInl[] = "LafxCtrl.inl";
#undef THIS_FILE
#define THIS_FILE _szAfxWinInl
#define _AFXWIN_INLINE
#include "lmfcx/LafxCtrl.inl"

#endif //!_AFX_ENABLE_INLINES
