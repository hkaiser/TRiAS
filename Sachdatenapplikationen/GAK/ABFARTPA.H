// abfartpa.h : header file
//

#include "SelNumberDlgUsage.h"

/////////////////////////////////////////////////////////////////////////////
// CAbfartParams dialog
class CEntsorgerSet;
class CTranspSet;
class CAbfArtSet;

class CAbfartParams : public CSelNumberDlgUsage
{
// Construction
public:
	CAbfartParams(CWnd* pParent, BOOL bReadOnly);
	virtual ~CAbfartParams();
// Dialog Data
	//{{AFX_DATA(CAbfartParams)
	enum { IDD = IDD_ABFART_PARAMS };
	CEditExt m_edEntsorger;
	CEditExt m_edTransp;
	CRealEdit m_edMenge;
	CButton	m_btOk;
	CString	m_strEntsorger;
	CString	m_strTransp;
	CString m_strAbfArt;
	CString	m_strMenge;
	CString m_strNachweis;
	CString m_strVerfahren;
	CString m_strPrioritaet;
	CString	m_strBefoerdName;
	CString	m_strEntsorgerBemerkung;
	CString	m_strTransportBemerkung;
	//}}AFX_DATA

	int m_iPosX;
	int m_iPosY;
	double m_dMinMengeRec;
	CString m_strCaption;
	
// Implementation
protected:
	CEntsorgerSet* m_pEntsorgerSet;
	CTranspSet* m_pTransSet;
	CAbfArtSet* m_pAbfallart;

	enum ChangeState{
		CHANGENOTHING, 
		CHANGEENTSORGER,
		CHANGETRANSPORT,
	};
	ChangeState enumState;

	CEdit * HasFocus () { return (CEdit *) GetFocus (); }

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CAbfartParams)
	virtual BOOL OnInitDialog();
	virtual void OnOK();         
	afx_msg void OnChangeMenge();
	afx_msg void OnCut();
	afx_msg void OnCopy();
	afx_msg void OnInsert();
	afx_msg void OnDelete();
	afx_msg void OnSelect();
	afx_msg void OnBack();
	afx_msg void OnSelectbefoerd();
	afx_msg void OnChangeEntsorger();
	afx_msg void OnChangeTransporteur();
	afx_msg void OnSelectentsorg();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL m_bReadOnly;

	void DoChangeName(CString& strName);
	void DoChangeNummer(CString& strNummer);
};

BOOL SearchNummer(CSelectSet* pSet, CString& strNummer);