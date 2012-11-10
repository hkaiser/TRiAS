// VerzSet2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVerzSet2 recordset

#ifndef _VERZSET2_H_
#define _VERZSET2_H_

class CVerzSet2 : public CRecordset
{
public:
	CVerzSet2(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CVerzSet2)

// Field/Param Data
	//{{AFX_FIELD(CVerzSet2, CRecordset)
	CString	m_TRIDB_NR;
	CString	m_TRIDB_VZ;
	CString	m_TRIDB_BZ;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVerzSet2)
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

#endif	// _VERZSET2_H_
