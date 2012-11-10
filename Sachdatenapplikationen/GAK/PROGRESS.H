// progress.h : header file
//

#ifndef _PROGRESS_H
#define _PROGRESS_H

#ifndef WIN32
class CProgressCtrl : public CStatic
{ 
private:
	UINT m_iStart, m_iEnd, m_iPos, m_iDrawPos;
	CRect rc;     
	double m_dFaktor;
	
protected:
	void DrawPosition (UINT iPos);
		
public:
	CProgressCtrl (void);
	~CProgressCtrl (void) {}			
			
	void SetRange (UINT iStart, UINT iEnd);
	void SetPos (UINT iNewPos);
};    
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgress dialog
class CProgress : public CDialog
{   
private:           
	BOOL m_bWasInterrupted;

// Construction
public:
	CProgress(CWnd* pParent = NULL);	// standard constructor
	~CProgress ();

// Dialog Data
	//{{AFX_DATA(CProgress)
	enum { IDD = IDD_RECHERCHESTATUS };
	CStatic	m_stAction;
	CProgressCtrl m_ctlProgress;
	//}}AFX_DATA
	
	BOOL Break (void);		//	wurde unterbrochen ?
	void SetParams (UINT uiStart, UINT uiEnd, const char *pCaption);
	void SetPos (UINT uiNewPos);
	void SetActionText (const char *pText);

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CProgress)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif 		// _PROGRESS_H
