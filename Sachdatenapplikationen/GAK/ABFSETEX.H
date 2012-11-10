// AbfSetEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAbfSetExport DAO recordset

class CAbfSetExport : public CDaoRecordset
{
public:
	CAbfSetExport(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CAbfSetExport)

// Field/Param Data
	//{{AFX_FIELD(CAbfSetExport, CDaoRecordset)
	CString	m_Nummer;
	CString	m_Abfallnummer;
	CString	m_Transporteurnummer;
	CString	m_Entsorgernummer;
	CString	m_Vorbehandlung;
	double	m_Menge_t;
	CString	m_Verbringungscode;
	CString	m_Abfallbezeichnung;
	CString	m_Betreibernummer;
	BOOL	m_Eigentransport;
	CString	m_Entsorgungsverfahren;
	BOOL	m_Eigenentsorgung;
	CString	m_Entsorgungspartner;
	CString	m_Entsorgungstelefon;
	CString	m_Entsorgungstelefax;
	BOOL	m_Entsorgungsfreistellung;
	CString	m_Freistellungsnummer;
	CString	m_Betreiberbemerkungen;
	CString	m_Transporteurbemerkungen;
	CString	m_Entsorgerbemerkungen;
	CString	m_Bemerkungen;
	COleDateTime	m_Erfassungsdatum;
	COleDateTime	m_Aenderungsdatum;
	BOOL	m_ro;
	CString	m_user;
	CString	m_EAKNummer;
	CString	m_Nachweisnummer;
	CString	m_Exportiert;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAbfSetExport)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

	BOOL operator = (const CAbfSetExport&);

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
