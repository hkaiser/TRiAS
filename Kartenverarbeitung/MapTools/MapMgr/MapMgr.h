#include "resource.h"

#define WM_INIT_STATUSBAR	(WM_USER+200)

#define	DOC_ADDMAP	(WM_USER+201)
#define	DOC_DELMAP	(WM_USER+202)
#define	DOC_CHGMAP	(WM_USER+203)

#define ON_ADD_MAP( ) \
	{ DOC_ADDMAP, 0, 0, 0, AfxSig_vs, \
	(AFX_PMSG)(AFX_PMSGW)(void (AFX_MSG_CALL CWnd::*)(LPCTSTR))&OnAddMap },

#define ON_DEL_MAP( ) \
	{ DOC_DELMAP, 0, 0, 0, AfxSig_vs, \
	(AFX_PMSG)(AFX_PMSGW)(void (AFX_MSG_CALL CWnd::*)(LPCTSTR))&OnDelMap },

#define ON_CHANGE_MAP( ) \
	{ DOC_CHGMAP, 0, 0, 0, AfxSig_vs, \
	(AFX_PMSG)(AFX_PMSGW)(void (AFX_MSG_CALL CWnd::*)(LPCTSTR))&OnChangeMap },

#define ON_WM_INITSTATUSBAR() \
	{ WM_INIT_STATUSBAR, 0, 0, 0, AfxSig_vs, (AFX_PMSG) (AFX_PMSGW) \
		(void (CWnd::*) (CFrameStatus*) ) OnInitStatusBar },
