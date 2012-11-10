/*
DATEI: NUMEDIT.H

Realisiert die Ziffereingaben in einem Editfeld.

Erarbeitet: 	J. Benkenstein				Stand vom: 22.08.1997
*/

#ifndef _NUM_EDIT_H
#define _NUM_EDIT_H

class CNumEdit : public CEdit
{
public:
	CNumEdit () {}
	
protected:  
	// Generated message map functions
	//{{AFX_MSG(CNumEdit)
		afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);		
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CRealEdit : public CNumEdit
{ 
public:
	CRealEdit () {}
	
protected:     
	//{{AFX_MSG(CRealEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);		
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CRealEditBegrenzt : public CRealEdit
{ 
public:
	CRealEditBegrenzt () {}
	
protected:     
	//{{AFX_MSG(CRealEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);		
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CErzNrEdit : public CNumEdit
{ 
public:
	CErzNrEdit () {}
	
protected:     
	//{{AFX_MSG(CErzNrEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);		
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif	// _NUM_EDIT_H
