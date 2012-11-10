// objstat.hpp : header file
//

/////////////////////////////////////////////////////////////////////////////
// CObjStatDlg dialog

class CObjStatDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CObjStatDlg)
private:
	DWORD m_dwFlags;					//	Dialog-Flags
	IEnumObjectsByNumber *m_pIEnumObjs;			//	Objektnummern-Ausgabe-Strom
	long m_lGeoErrCnt;
	long m_lTexteCnt;
	long m_lPointCnt;
	long m_lLineCnt;
	long m_lAreaCnt;

// Construction
public:
	CObjStatDlg();
	~CObjStatDlg();

//	weitere Member
	HRESULT SetEnumLONG (IEnumObjectsByNumber *pIEnum);		// übergibt Objektmenge
	HRESULT GetEnumLONG (IEnumObjectsByNumber **ppIEnum);	// liest Objektmenge
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CObjStatDlg * CreateInstance (void);

// Dialog Data
	//{{AFX_DATA(CObjStatDlg)
	enum { IDD = IDD_OBJEKT_STATISTIK };
	CStatic	m_stTexteCnt;
	CStatic	m_stSumCnt;
	CStatic	m_stPointCnt;
	CStatic	m_stLineCnt;
	CStatic	m_stGeoErrCnt;
	CStatic	m_stAreaCnt;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CObjStatDlg)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetButtons (void);
	CPropertySheet *GetPropertySheet (void) { return (CPropertySheet *)GetParent (); } 
	// Generated message map functions
	//{{AFX_MSG(CObjStatDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
