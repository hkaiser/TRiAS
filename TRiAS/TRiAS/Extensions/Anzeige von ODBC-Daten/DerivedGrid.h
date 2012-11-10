#if !defined(AFX_DERIVEDGRID_H__26F96555_FC81_11D2_8D2D_000000000000__INCLUDED_)
#define AFX_DERIVEDGRID_H__26F96555_FC81_11D2_8D2D_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DerivedGrid.h : header file
//

#include "headctrl.h"	// Button für den Kopf

/////////////////////////////////////////////////////////////////////////////
// CSortedGrid window

class CSortedGrid : public CGXRecordWnd
{
// Construction
public:
	CSortedGrid();
	
// Attributes
public:
	CWnd* m_wndParent;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSortedGrid)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSortedGrid();

	// Parameter : direction 
	// Funktion : Angabe der Sortierreihenfolge
	// Werte	:	1	steigend sortieren
	//				0	Auswahl der SOrtierung
	//				-1	fallend sortieren (default)
	void DoSort(ROWCOL nCol, UINT direction = 0);		// nach einer angegebenen Spalte sortieren

	// Generated message map functions
protected:
	//{{AFX_MSG(CSortedGrid)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Overrides
	virtual void OnClickedButtonRowCol(ROWCOL nRow, ROWCOL nCol);
	virtual BOOL OnRButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);
	virtual void OnInitialUpdate();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DERIVEDGRID_H__26F96555_FC81_11D2_8D2D_000000000000__INCLUDED_)
