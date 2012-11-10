typedef CList<CMapInfo*,CMapInfo*&>	CInfoList;

typedef enum { 
	HDRVER_OLD = 0, 
	HDRVER_5 = 1
} HDRVERSION;

class MMGR_ASC_HEADER {
public:
	int		m_nIdentBase;
	int		m_nMcodeBase;
	HDRVERSION		m_nVersion;
	DWORD	m_dwTKIdent;
	DWORD	m_dwTKIcode;
	DWORD	m_dwTKMcode;
	DWORD	m_dwTKVcode;
	TOPOMAPTYPE	m_mapType;
	CString	m_strSearchMask;

	void Init();
	MMGR_ASC_HEADER operator=( const MMGR_ASC_HEADER& hdr );
};

class CAscParser;

class CMapMgrDoc : public CDocument {
protected: // create from serialization only
	void CheckDocument();
	POSITION m_posEnumItems;
	CMapMgrDoc();
	void DeleteContents();
	DECLARE_DYNCREATE(CMapMgrDoc)
	friend class CAscParser;

	BOOL				m_bStartup;
	CMapStringToOb		m_listOfFilters;		// Liste aller verfügbaren Filter

	ASC_HEADER			m_ascHdrGlob;
	MMGR_ASC_HEADER		m_ascHdrMmgr;

	CObList				m_listOfEmptyMapInfos;
	CMapInfo			*GetNewMapInfo();

	CInfoList			m_listOfMapInfos;
	CMapInfo			*m_pCurrMapInfo;

	CStringArray		m_strPictDirs;
	CMapStringToString	m_mapOfPictPaths;

// Attributes
public:
	BOOL NextItem( LPCTSTR *ppszItem );
	void ResetItems();
	///////////////////////////////////////////////////////////////////////
	// Bearbeitungsoptionen
	CSize				m_szJump;				// Standardoffset für neuen Referenzpunkt

// Operations
public:
	void ChangeMapIdent( LPCTSTR lpszMapIdent );
	void ResetStartState();

// Implementation
public:
	virtual ~CMapMgrDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	BOOL LoadFromDialog( CDialog* pDlg );

protected:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	void	ReadAscFile( CArchive& ar );
	void	WriteAscFile( CArchive& ar );
	void	WriteAscRecord( iostream& os, int nRec, CMapInfo *pMapInfo );
	void	RecalcGeometry();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMapMgrDoc)
	afx_msg void OnAddMap();
	afx_msg void OnDelMap();
	afx_msg void OnUpdateDelMap(CCmdUI* pCmdUI);
	afx_msg void OnMapModifyIdent();
	afx_msg void OnUpdateMapModifyIdent(CCmdUI* pCmdUI);
	afx_msg void OnMapModifyFilename();
	afx_msg void OnUpdateMapModifyFilename(CCmdUI* pCmdUI);
	afx_msg void OnFileProperties();
	afx_msg void OnUpdateFileProperties(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAddMap(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMapProperties(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
