#include "stdafx.h"
#include "LPictImpl.h"

#ifdef LAFX_PICT_SEG
#pragma code_seg(LAFX_PICT_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

#define	new	DEBUG_NEW

#ifndef _AFX_ENABLE_INLINES			// _DEBUG is defined

#ifdef AFX_DBG1_SEG
#pragma code_seg(AFX_DBG1_SEG)
#endif

static char BASED_CODE _szAfxInl[] = __FILE__;
#undef THIS_FILE
#define THIS_FILE _szAfxInl
#define _AFX_INLINE
#include "lpict/PictCod.inl"

#endif //!_AFX_ENABLE_INLINES
