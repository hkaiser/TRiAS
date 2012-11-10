// listext.h : interface of the CListBoxExt class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _LIST_EXT_
#define _LIST_EXT_

class CListBoxExt : public CListBox
{
public:
//	Konstruktor/Destruktor
	CListBoxExt (void) {}

protected:	
	// Generated message map functions
	//{{AFX_MSG(CListBoxExt)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif		// _LIST_EXT_
