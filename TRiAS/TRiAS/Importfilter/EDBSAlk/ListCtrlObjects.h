#if !defined(AFX_LISTCTRLOBJECTS_H__398558D6_4B2F_11D4_9378_004F4E05A09F__INCLUDED_)
#define AFX_LISTCTRLOBJECTS_H__398558D6_4B2F_11D4_9378_004F4E05A09F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrlObjects.h : Header-Datei
//
#include <afxcmn.h>	// CListCtrl

/////////////////////////////////////////////////////////////////////////////
// Fenster CListCtrlObjects 

class CListCtrlObjects : public CListCtrl
{
// Konstruktion
public:
	CListCtrlObjects();

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CListCtrlObjects)
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CListCtrlObjects();

private:
	bool tLButtonDownCatched;
	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CListCtrlObjects)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_LISTCTRLOBJECTS_H__398558D6_4B2F_11D4_9378_004F4E05A09F__INCLUDED_
