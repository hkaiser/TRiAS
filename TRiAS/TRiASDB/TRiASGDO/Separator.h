/////////////////////////////////////////////////////////////////////////////
// Separator.h : header file for CSeparator.
//
// Written by Michael Dunn (mdunn at inreach dot com).  Copyright and all
// that stuff.  Use however you like but give me credit where it's due.  I'll
// know if you don't. bwa ha ha ha ha!
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEPARATOR_H__90B023A4_6E4F_11D2_96F6_00C04FAC114C__INCLUDED_)
#define AFX_SEPARATOR_H__90B023A4_6E4F_11D2_96F6_00C04FAC114C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CSeparator window

class CSeparator : 
	public CWindowImpl<CSeparator, CStatic>
{
// Construction
public:
	typedef CWindowImpl<CSeparator, CStatic> base_t;

	CSeparator();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeparator)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSeparator();

	// Generated message map functions
protected:
	BEGIN_MSG_MAP_EX(CSeparator)
		MSG_WM_PAINT(OnPaint)
	END_MSG_MAP()

	LRESULT OnPaint(HDC hDC);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEPARATOR_H__90B023A4_6E4F_11D2_96F6_00C04FAC114C__INCLUDED_)
