// Abgleich.hpp : header file
//

#ifndef _ABGLEICH_HPP
#define _ABGLEICH_HPP

class CDataBaseExt;
class CColumnObjArray;
class CRecSet;
class CPunktInfoTree;

//	Exception-Handling erweitern
class CNoValuesFoundException : public CException 
{
	DECLARE_DYNAMIC (CNoValuesFoundException);
public:                                   
#ifdef WIN32
	CNoValuesFoundException (void) : CException (FALSE) {}
#else
	CNoValuesFoundException (void) : CException () {}
#endif
	~CNoValuesFoundException (void) {}
};
void AFXAPI AfxNoValuesFoundException (void);

/////////////////////////////////////////////////////////////////////////////
// CDoAbgleich dialog
class CDoAbgleich : public CPropertyPage
{
	DECLARE_DYNCREATE(CDoAbgleich)

// Construction
public:
	CDoAbgleich();
	~CDoAbgleich();

// Dialog Data
	//{{AFX_DATA(CDoAbgleich)
	enum { IDD = IDD_IMP_DOABGLEICH };
	CProgressCtrl	m_ctProgress;
	CStatic	m_stInfo;
	//}}AFX_DATA

#ifdef WIN32
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDoAbgleich)
	public:
	virtual BOOL OnSetActive();
	virtual void OnCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
#else		// WIN16
	// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDoAbgleich)
	public:
	virtual void OnCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDoAbgleich)
	virtual BOOL OnInitDialog();
	afx_msg LONG OnSetFocusToControl (UINT, LONG);
	//}}AFX_MSG
#endif	    // WIN16
	DECLARE_MESSAGE_MAP()
	
	void RollBack (CRecSet *pSet);
	BOOL m_bBreak;
	DataSourceType m_tDsnType;
	
	afx_msg LONG OnDoAbgleich (UINT, LONG);

	CPropertySheet *GetParent (void) { return (CPropertySheet *) 
											   CWnd :: GetParent (); }
		//	erzeuge Protokoll-Datei
	void CreateProtokoll (void);
		//	lese Tabellensätze
	BOOL GetTableRecords (CDataBaseExt *pCDataBase, CColumnObjArray *&pCColArr, 
						  CRecSet *&pCRecSet, long &lMaxCnt, BOOL bForUpdate);
		//	schreibe ODBC-Anbindungen
	BOOL OutputConnections (void);

		// Triasabgleich durchführen
	BOOL TriasAbgleich (long lCnt, CPunktInfoTree *pTree, CRecSet *pSet, CColumnObjArray *pList, 
						BOOL bAddNotExist);

		//	Fehlermeldung ins Prorokoll ausgeben
	void OutputError (uint uiResID, long lObjNr, long lX, long lY, 
					  const char *pMerkmal);

		//	Tabellenabgleich durchführen
	BOOL TableAbgleich (long lMax, CPunktInfoTree *pTree, CRecSet *pSet, CColumnObjArray *pCol,
						BOOL bAddNotExist);

		//	eigentlichen Abgleich durchführen
	BOOL TriasTableAbgleich (long lMax, CPunktInfoTree *pTree, CRecSet *pSet, CColumnObjArray *pCol,
							 BOOL bAddNotExist, BOOL bAction);

		// Abbruch-Test
	friend void WasInterrupted (void);	
};

#endif		// _ABGLEICH_HPP
