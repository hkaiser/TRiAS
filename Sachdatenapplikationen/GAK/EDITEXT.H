// editext.h : interface of the CEditExt class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _EDIT_EXT_
#define _EDIT_EXT_

#ifdef WIN32
#define CEditExt	CEdit
#else
class CEditExt : public CEdit
{
public:           
//	Konstruktor/Destruktor
	CEditExt () {}
	
protected:	
	// Generated message map functions
	//{{AFX_MSG(CEditExt)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};   
#endif

#endif		// _EDIT_EXT_

