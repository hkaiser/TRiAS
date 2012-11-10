// VerzSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVerzSet recordset

#ifndef _VERZSET_H_
#define _VERZSET_H_

class CVerzSet : public CRecordset
{
public:
	int RegisterProjekt( const char*, const char* );
	CString GetProjectName( int );
	BOOL InitListen( BOOL = FALSE );
	short IstProjektIntegriert( const char* );
	CVerzSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CVerzSet)

// Field/Param Data
	//{{AFX_FIELD(CVerzSet, CRecordset)
	CString	m_TRIDB_NR;
	CString	m_TRIDB_VZ;
	CString	m_TRIDB_BZ;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVerzSet)
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
protected:
	CStringArray m_arrVerz;
};

#endif	// _VERZSET_H_
