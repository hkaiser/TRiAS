// Private Strukturen und Messages --------------------------------------------
// File: TRIASPRV.H

#if !defined(_TRIASPRV_H)
#define _TRIASPRV_H

#define WM_SIZEPARENT	0x0361			// lParam = &AFX_SIZEPARENTPARAMS

// special struct for WM_SIZEPARENT -------------------------------------------
struct SIZEPARENTPARAMS {
	HDWP hDWP;			// handle for DeferWindowPos
	RECT rect;			// parent client rectangle (trim as appropriate)
	SIZE sizeTotal;		// total size on each side as layout proceeds
	BOOL bStretch;		// should stretch to fill all space
};

// Values for RepositionBars (nFlag-parameter) --------------------------------
enum RepositionFlags {
	reposDefault = 0, 
	reposQuery = 1, 
	reposExtra = 2 
};

void WINAPI RepositionWindow (SIZEPARENTPARAMS *lpLayout, HWND hWnd, LPCRECT lpRect);

#endif // _TRIASPRV_H
