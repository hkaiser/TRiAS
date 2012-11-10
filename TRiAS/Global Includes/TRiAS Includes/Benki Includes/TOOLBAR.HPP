// Datei: TOOLBAR.HPP

#ifndef _TOOLBAR_HPP
#define _TOOLBAR_HPP

class CToolBarEx : public CToolBar
{ 
public:	
	CToolBarEx (void) : CToolBar () {}
	~ CToolBarEx (void) {}
	
	void Disable (uint nIndex);
	void Enable (uint nIndex); 

protected:
#ifdef WIN32
	afx_msg LONG OnDisable (UINT, LONG);
	DECLARE_MESSAGE_MAP()
#endif 
};

#endif 	// _TOOLBAR_HPP
                    
                    
