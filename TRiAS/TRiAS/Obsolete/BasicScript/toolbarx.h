// Toolbar mit einigen zusätzlichen Funktionen --------------------------------
// Datei: TOOLBARX.H

#if !defined(_TOOLBARX_H)
#define _TOOLBARX_H

#if defined(WIN32)

class CToolBarEx : public CToolBarCtrl {
public:
	CToolBarEx (void) : CToolBarCtrl () {}
	~CToolBarEx (void) {}

	void Disable (UINT nIndex) { EnableButton (nIndex, false); }
	void Enable (UINT nIndex) { EnableButton (nIndex, true); }
	void Repaint (void) {}	// do nothing
};

#else

class CToolBarEx : public CToolBar
{ 
public:					
	CToolBarEx (void) : CToolBar () {}
	~CToolBarEx (void) {}
	
	void Disable (UINT nIndex) 
		{ _SetButtonStyle (CommandToIndex (nIndex), TBBS_DISABLED); }	
	void Enable (UINT nIndex)  
		{ _SetButtonStyle (CommandToIndex (nIndex), TBBS_BUTTON); } 
	void Repaint (void) { Invalidate(); UpdateWindow(); }
};

#endif // WIN32

#endif 	// _TOOLBARX_H
                    
                    
