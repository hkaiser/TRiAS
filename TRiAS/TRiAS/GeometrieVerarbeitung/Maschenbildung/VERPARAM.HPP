// Verparam.hpp : header file
//

#ifndef _VERPARAM_HPP
#define _VERPARAM_HPP

/////////////////////////////////////////////////////////////////////////////
// CVerschnittPage dialog
DefineSmartInterface (EnumObjectsByNumber);
typedef list<WEnumObjectsByNumber> EnumListe;

class CVerschnittPropAct;
class CVerschnittPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CVerschnittPage)

private:
	DWORD m_dwFlags;					//	Dialog-Flags
	double m_dFuzzy,					//  Fangbereich zweier Stützpunkte
		   m_dDangleLen;				//	Länge überstehender Strecken	
	BOOL   m_bDeleteLines;				//	Ursprungslinien löschen		
	BOOL   m_bMarkLines;				//	Ursprungslinien markieren	
	
	CParameters m_Params;				//	Parameter
	EnumListe m_OutNrListe;				//	Objektnummern-Ausgabe-Strom	
	
// Construction
public:
	CVerschnittPropAct *m_pAction;
	CVerschnittPage();

//	Beschreibungstext ausgeben
	void OutputDescription (UINT uiResID);

//	weitere Memberfunktionen
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	HRESULT SetEnumLONG (IEnumObjectsByNumber *pIEnum);		// übergibt Objektmenge
	HRESULT GetEnumLONG (WEnumObjectsByNumber &WEnum);		// liest Objektmenge
	static CVerschnittPage *CreateInstance (CVerschnittPropAct *);		// Page erzeugen

//	Parameter setzen
	void SelectFuzzy (double);
	void SelectDangleLen (double);
	void SelectDeleteOldLines (BOOL bFlag);
	void SelectMarkOldLines (BOOL bFlag);
	
//	Parameter lesen
	double GetFuzzy (void) { return m_dFuzzy; }
	double GetDangleLen (void) { return m_dDangleLen; }
	BOOL GetDeleteOldLines (void) { return m_bDeleteLines; }
	BOOL GetMarkOldLines (void) { return m_bMarkLines; }
	
// Dialog Data
	//{{AFX_DATA(CVerschnittPage)
	enum { IDD = IDD_VERSCHNITT_PAGE };
	CButton	m_btMarkObjects;
	CButton	m_btDeleteLines;
	CEdit	m_edDangleLen;
	CStatic	m_stDescription;
	CEdit	m_edFuzzy;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CVerschnittPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetButtons (void);			// Button für den WIZZARD setzen
	CPropertySheet *GetPropertySheet (void) { return (CPropertySheet *)GetParent (); } 

	// Generated message map functions
	//{{AFX_MSG(CVerschnittPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposFuzzy(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeFuzzy();
	afx_msg void OnSetfocusFuzzy();
	afx_msg void OnChangeDangleLen();
	afx_msg void OnSetfocusDangleLen();
	afx_msg void OnDeltaposDangleLen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteLines();
	afx_msg void OnMarkObjects();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif		//	_VERPARAM_HPP
