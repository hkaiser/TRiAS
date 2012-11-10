#include "RecView.h"	

// AbfView.h : header file
//

class CAbfDoc;

/////////////////////////////////////////////////////////////////////////////
// CAbfView DAO record view
class CAbfView : public CDaoRecordViewExt
{
protected:
	void Print (BOOL bToWindow);
	virtual BOOL CanGotoBookmark (void);
	virtual BOOL ChangeKey (BOOL bSelect = FALSE);	// Erzeugernummer ändern
	CString m_strBookmark;				// akt. Buchmarke

	CAbfView() {}
	DECLARE_DYNCREATE(CAbfView)

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAbfView)
	protected:
	virtual CDaoRecordset* OnGetRecordset();
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL
//	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// Implementation
protected:
	virtual ~CAbfView() {}
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	CAbfDoc* GetDocument();
#endif

	// Generated message map functions
	//{{AFX_MSG(CAbfView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDeleteRekord();
	afx_msg void OnGotoBookmark();
	afx_msg void OnUpdateGotoBookmark(CCmdUI* pCmdUI);
	afx_msg void OnSetBookmark();
	afx_msg void OnNewRekord();
	afx_msg void OnUpdateNewRekord(CCmdUI* pCmdUI);
	afx_msg void OnDeleteAbfallGruppe();
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

#ifndef _DEBUG  // debug version in gakView.cpp
inline CAbfDoc* CAbfView::GetDocument()
   { return (CAbfDoc*)m_pDocument; }
#endif
private:


public:
	void DeleteAbfallGruppe();

#pragma MSG("JG Added DefaultParameter") 
	virtual BOOL SearchNummer (const char *pNummer = NULL, BOOL bOutErrMsg = TRUE);
// JG added functions
/*
	//	Druckfunktionen
	void PrintPageHead (CPrintInfo *pInfo);
	void PrintTableHead (CPrintInfo *pInfo);	
	void PrintTableLines (CPrintInfo *pInfo);	

//	aktuelle Zeile berechnen bzw. ausgeben
//	FALSE, wenn Platz nicht mehr ausreicht
	BOOL PrintRow (int iGridIndex, CPrintInfo *pInfo, BOOL bOutput);
*/
};

