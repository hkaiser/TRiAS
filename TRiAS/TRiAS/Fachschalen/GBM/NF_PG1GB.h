// NF_PG1GB.h : header file
//

class CPG1GBArray;

/////////////////////////////////////////////////////////////////////////////
// CSetNF_PG1GB recordset

class CSetNF_PG1GB : public CRecordset
{
public:
	long GetCount();
	BOOL IstAngeschlossen( const char*, const char* );
	void DeleteIDE( const char* );
	BOOL ModIDE( const char*, const char* );
	void RewriteArray( const char*, CPG1GBArray* );
	CSetNF_PG1GB(CDatabase* pDatabase = NULL);
	~CSetNF_PG1GB();
	DECLARE_DYNAMIC(CSetNF_PG1GB)

// Field/Param Data
	//{{AFX_FIELD(CSetNF_PG1GB, CRecordset)
	CString	m_NFP1_IDE;
	double	m_NFP1_GNR;
	double	m_NFP1_GFL;
	double	m_NFP1_VOL;
	double	m_NFP1_HOH;
	CString	m_NFP1_ANL;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetNF_PG1GB)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL
	void	InitListen( const char* );
	void	InitArray( const char*, CPG1GBArray* );

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

// Datensatzklasse für 1:n - Beziehung Gebäude

class CPG1GBSatz : public CObject
{
public:
			CPG1GBSatz()    {}
			CPG1GBSatz( CPG1GBSatz* );
	CString	m_NFP1_IDE;
	double	m_NFP1_GNR;
	double	m_NFP1_GFL;
	double	m_NFP1_VOL;
	double	m_NFP1_HOH;
	CString	m_NFP1_ANL;
};

class CPG1GBArray : public CObArray
{
public:
	double VOL();
	double GFL();
			CPG1GBArray()   {}
			~CPG1GBArray()  { Clear(); }
	BOOL	Add( CPG1GBSatz* );
	void	Remove( const char* );
	void	Clear();
	const	CPG1GBArray& operator = ( const CPG1GBArray& );
};


// Datensatzklasse für 1:n - Beziehung Dach-/Hofflächen

class CPG2DSatz : public CObject
{
public:
			CPG2DSatz()     {}
			CPG2DSatz( CPG2DSatz* );
	CString	m_NFP2_IDE;
	CString	m_NFP2_FLN;
	double	m_NFP2_FLG;
	double	m_NFP2_ABF;
	CString	m_NFP2_ANS;
};

class CPG2DArray : public CObArray
{
public:
			CPG2DArray()    {}
			~CPG2DArray()   { Clear(); }
	BOOL	Add( CPG2DSatz* );
	void	Remove( const char* );
	void	Clear();
	const CPG2DArray& operator = ( const CPG2DArray& );
};
