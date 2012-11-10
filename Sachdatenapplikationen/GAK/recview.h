// RecView.h : interface of the CDaoRecordViewExt class
//
/////////////////////////////////////////////////////////////////////////////

class CRPEJob; 
class CDaoRecordsetExt;

#ifndef _REC_VIEW
#define _REC_VIEW

/*
class CBoolSema
{
private:
	BOOL &m_bVal;

public:
	CBoolSema (BOOL &bVal) : m_bVal (bVal) { m_bVal = TRUE; }
	~CBoolSema () { m_bVal = FALSE; }
};
*/

class CDaoRecordViewExt : public CDaoRecordView
{
private:
	CRPEJob *m_pPrintJob; 
	
protected: 
	//BOOL m_bOnSearch;
	void SetBookMarks (void);
	//int m_iTextHoehe;				// akt. Texthöhe
	CDaoRecordsetExt * m_pSet;		// Datenset
	CPropertySheet *m_pSheet;		// Dialogspeicher
	COleVariant m_varBookmark;		// Satzmarke

	// BOOL PrintPageHeader (CDC* pDC, CPrintInfo *pInfo, CString& strHeader); // Kopf drucken
	BOOL HasRecords (void);			// Datensätze im Set
	long RecordCount (void);		// Anzahl Datensätze

	virtual BOOL ChangeKey (BOOL bSelect = FALSE);		// Erzeugernummer ändern

public:
	DECLARE_DYNCREATE(CDaoRecordViewExt)
	CDaoRecordViewExt();
	enum { IDD = IDD_GAK_FORM };

//	kann eine bestimmte Aktion durchgeführt werden ?
	virtual BOOL CanChangeKey (void);			// Schlüssel ändern
	virtual BOOL CanDeleteRecord (void);		// akt. Satz löschen
	virtual BOOL CanAddNewRecord (void);		// neuen Satz anhängen
	virtual BOOL CanGotoBookmark (void);		// Buchmarke anspringen
	virtual BOOL CanSetBookmark (void);			// Buchmarke gesetzt werden
	virtual void Sync();						// Synchronsisation anderer Ansichten

//	Erzeuger suchen	
	virtual BOOL SearchNummer (const char *pNummer, BOOL bOutErrMsg = TRUE);	
	void SetCaption ();							// Caption setzen	
	CPropertySheet *GetSheet (void);

protected:
//	Attributes
	CDocument* GetDocument();

//	Seite drucken
	// BOOL Print (CDC* pDC, CPrintInfo* pInfo, const CString &strPage);
	void Print (CString &strReportFile, BOOL bToWindow);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDaoRecordViewExt)
	public:
	virtual CDaoRecordset* OnGetRecordset();
	virtual BOOL OnMove(UINT nIDMoveCommand);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDaoRecordViewExt();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnMoveExt(UINT nIDMoveCommand);
	void SetScrollValues (void);
	CGakApp* GetApp() const
	{
		return static_cast <CGakApp*> (AfxGetApp());
	}

// Generated message map functions
	//{{AFX_MSG(CDaoRecordViewExt)
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnUpdateChangeKey(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDeleteRekord(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGotoBookmark(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNewRekord(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSetBookmark(CCmdUI* pCmdUI);
	afx_msg void OnChangeKey();
	afx_msg void OnDeleteRekord();
	afx_msg void OnGotoBookmark();
	afx_msg void OnNewRekord();
	afx_msg void OnSetBookmark();
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLookNr(CCmdUI* pCmdUI);
	afx_msg void OnAktbilanz();
	afx_msg void OnUpdateAktbilanz(CCmdUI* pCmdUI);
	afx_msg void OnAbgleichAkt();
	afx_msg void OnAbgleich();
	afx_msg void OnAbgleichAktnew();
	afx_msg void OnUpdateAbgleichAkt(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAbgleichAktnew(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAbgleich(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in gakView.cpp
inline CDocument* CDaoRecordViewExt::GetDocument()
   { return m_pDocument; }
#endif

#endif	// _REC_VIEW
