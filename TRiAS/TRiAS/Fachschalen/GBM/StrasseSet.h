// StrasseSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStrasseSet recordset

#ifndef _STRASSESET_H_
#define _STRASSESET_H_

class CStrasseSet : public CRecordset
{
public:
	CString Strasse( const char* );
	void InitListen( BOOL = FALSE );
	CStrasseSet(CDatabase* pDatabase = NULL);
	~CStrasseSet();
	DECLARE_DYNAMIC(CStrasseSet)

	short	GetZahlStrassen( short );
	CMapStringToString	*GetStrassen( short );
	// Field/Param Data
	//{{AFX_FIELD(CStrasseSet, CRecordset)
	CString	m_STR_NAM;
	double	m_STR_ISY;
	double	m_STR_OISY;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStrasseSet)
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
	void RegisterStrasse( double, double, const char* );
	void CleanupListen();
	CMapStringToPtr m_mapOrtListen;
	CMapStringToString m_mapListe;
	BOOL m_bInitialisiert;
};

#endif	// _STRASSESET_H_
