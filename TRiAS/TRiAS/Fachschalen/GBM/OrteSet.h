// OrteSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COrteSet recordset

#ifndef _ORTESET_H_
#define _ORTESET_H_

class COrteSet : public CRecordset
{
public:
	CString Ort( const char* );
	double TB( short );
	void InitListen( BOOL = FALSE );
	COrteSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(COrteSet)

// Field/Param Data
	//{{AFX_FIELD(COrteSet, CRecordset)
	CString	m_ORT_NAM;
	double	m_ORT_ISY;
	double	m_ORT_TB;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrteSet)
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
	void RegisterOrt( double, const char* );
	CMapStringToString m_mapListe;
	BOOL m_bInitialisiert;
};

#endif	// _ORTESET_H_
