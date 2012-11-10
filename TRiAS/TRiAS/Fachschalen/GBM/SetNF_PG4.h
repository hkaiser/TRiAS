// SetNF_PG4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetNF_PG4 recordset

#ifndef _SETNF_PG4_H_
#define _SETNF_PG4_H_

class CEigentuemerArray;
class CEigentuemer;

class CSetNF_PG4 : public CRecordset
{
public:
	CEigentuemer* FindEigentuemer( const char*, long );
	void TestPrintIDE( CStringArray* );
	bool Find( const char* );
	BOOL ModIDE( const char*, const char* );
	void RewriteArray( const char* ide, CEigentuemerArray* array );
	void InitArray( const char*, CEigentuemerArray* );
	CSetNF_PG4(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetNF_PG4)

// Field/Param Data
	//{{AFX_FIELD(CSetNF_PG4, CRecordset)
	double	m_NFP4_BDM;
	CString	m_NFP4_EAN;
	CString	m_NFP4_ENA;
	CString	m_NFP4_EOR;
	CString	m_NFP4_EPL;
	CString	m_NFP4_HER;
	CString	m_NFP4_IDE;
	double	m_NFP4_TFL;
	double	m_NFP4_PN;
	double	m_NFP4_PZ;
	long	m_NFP4_NR;
	CString	m_NFP4_KASS;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetNF_PG4)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};


class CEigentuemer : public CObject
{
public:
	CString m_NFP4_KASS;
	long m_NFP4_NR;
	CEigentuemer();
	CEigentuemer( CEigentuemer* );
	~CEigentuemer()	{}

	double	m_NFP4_BDM;
	CString	m_NFP4_EAN;
	CString	m_NFP4_ENA;
	CString	m_NFP4_EOR;
	CString	m_NFP4_EPL;
	CString	m_NFP4_HER;
	CString	m_NFP4_IDE;
	double	m_NFP4_TFL;
	long	m_NFP4_PN;
	long	m_NFP4_PZ;
};

class CEigentuemerArray : public CObArray
{
public:
			CEigentuemerArray()   {}
			~CEigentuemerArray()  { Clear(); }
	BOOL	Add( CEigentuemer* );
	void	Remove( const char* );
	void	Clear();
	const	CEigentuemerArray& operator = ( const CEigentuemerArray& );
};

#endif //_SETNF_PG4_H_
