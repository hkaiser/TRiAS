// StatDlg.h : header file
//

//	typedefs
typedef enum { NoType, DatabaseSel, TableCollectionSel, TableSel, FieldCollectionSel, FieldSel, 
			   IndexCollectionSel, IndexSel, QueryCollectionSel, QuerySel, RelationCollectionSel, 
			   RelationSel, IniInfoCollectionSel, IniInfoSel } SelectType;

/////////////////////////////////////////////////////////////////////////////
// CStatistikDialog dialog

class CStatistikDialog : public CDialog
{
// Construction
public:
	CStatistikDialog(CWnd* pParent = NULL);   // standard constructor
	~CStatistikDialog (void);

// Dialog Data
	//{{AFX_DATA(CStatistikDialog)
	enum { IDD = IDD_STATISTIK };
	CListCtrl	m_lcDatabase;
	CTreeCtrl	m_trDatabase;
	CStatic	m_stTransInfo;
	CStatic	m_stEntsorgerInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatistikDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList m_ctlImage;
	CDaoDatabase m_Database;
	HTREEITEM m_hActItem;						// akt. sel. Item
	SelectType m_tActSelType;					// akt. sel. Type

	void SetColumnNames (SelectType tType);		//	Spalten-Namen neu ausgeben
	BOOL IsObject (SelectType tType);			//	aktueller Selektions-Typ ein Object ?
	BOOL IsCollection (SelectType tType);		//	aktueller Selektions-Typ eine Collection ?	
	void OutputItemValues (SelectType tType);	//  Werte in Listview ausgeben

//	Werte für die einzelnen Objektarten ausgeben
	void OutputDatabaseInfo (BOOL bObjekt = TRUE);
	void OutputTableInfo (BOOL bObjekt = TRUE);
	void OutputQueryInfo (BOOL bObjekt = TRUE);
	void OutputRelationInfo (BOOL bObjekt = TRUE);
	void OutputIndexInfo (BOOL bObjekt = TRUE);
	void OutputFieldInfo (BOOL bObjekt = TRUE);
	void OutputIniInfo (BOOL bObjekt = TRUE);

	int OutputPropertyColumn (char **ppColNames);	//	"Eigenschaft"-Spalte füllen

	// Generated message map functions
	//{{AFX_MSG(CStatistikDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickTables(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTables(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysColorChange();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
