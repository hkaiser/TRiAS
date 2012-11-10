// TriDBSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTriDBSet recordset

#ifndef _TRIDBSET_H_
#define _TRIDBSET_H_

class CTriDBSet : public CRecordset
{
public:
	void AddIDE( const char*, int );
	BOOL ModIDE( const char*, const char*, int );
	int GetProjectNr( const char* );
	BOOL Ortslage( const char*, CString&, CString& );
	BOOL RewriteIndex();
	short FindOISY( short );
	BOOL GetProjekte( const char* ide, CString& nr );
	BOOL InitListen( BOOL = FALSE );
	CTriDBSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTriDBSet)

// Field/Param Data
	//{{AFX_FIELD(CTriDBSet, CRecordset)
	CString	m_NFPG1_IDE;
	CString	m_TRIDB_NR;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTriDBSet)
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
private:
	CMapStringToString m_mapIDE;
	BOOL m_bInitialisiert;
	CMapStringToString m_mapStrassen;
	CMapStringToString m_mapOrte;

protected:
	void RegisterGS( const char*, const char* );
};

#endif // _TRIDBSET_H_
