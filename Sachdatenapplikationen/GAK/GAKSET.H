// gakSet.h : interface of the CGakSet class
//
/////////////////////////////////////////////////////////////////////////////
class CGakSet : public CDaoRecordsetExt
{
public:
	CGakSet(CDaoDatabase* pDatabase = NULL);
	~CGakSet (void);
	DECLARE_DYNAMIC(CGakSet)

// Field/Param Data
	//{{AFX_FIELD(CGakSet, CDaoRecordset)
	CString	m_Anfallstelle;
	CString	m_Ansprechpartner;
	CString	m_Antragsnummer;
	BOOL	m_Anzeigenachweisverordnung;
	CString	m_Bemerkungen;
	CString	m_Betreibernummer;
	long	m_Betriebsbeauftragtennummer;
	CString	m_Betriebsbeauftragtentelefax;
	CString	m_Betriebsbeauftragtentelefon;
	CString	m_Betriebsbeauftragter;
	CString	m_Betriebsstaette;
	CString	m_Bilanznummer;
	CString	m_Bimschgenehmigungsnummer;
	CString	m_Bimschnummer;
	CString	m_Bimschspalte;
	CString	m_Branchennummer;
	CString	m_Firmenansprechpartner;
	CString	m_Partnerfunktion;
	CString	m_Firmenhausnummer;
	CString	m_Firmenname;
	CString	m_Firmenortsname;
	CString	m_Firmenpostleitzahl;
	CString	m_Firmenstrasse;
	CString	m_Firmentelefax;
	CString	m_Firmentelefon;
	CString	m_Gemeindekennzahl;
	CString	m_Hausnummer;
	CString	m_Ortsname;
	CString	m_Partnertelefax;
	CString	m_Partnertelefon;
	CString	m_Postleitzahl;
	CString	m_Strasse;
	CString	m_Exportiert;
	CString m_EDV;
	CString m_EDVSonstige;
	BOOL	m_Unterschrift;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGakSet)
	public:
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);	// RFX support
	//}}AFX_VIRTUAL

	BOOL operator = (const CGakSet&);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
/////////////////////////////////////////////////////////////////////////////
// CGakSetRed DAO recordset

class CGakSetRed : public CDaoRecordset
{
public:
	CGakSetRed(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CGakSetRed)

// Field/Param Data
	//{{AFX_FIELD(CGakSetRed, CDaoRecordset)
	COleDateTime	m_Aenderungsdatum;
	CString	m_Anfallstelle;
	CString	m_Ansprechpartner;
	CString	m_Antragsnummer;
	BOOL	m_Anzeigenachweisverordnung;
	CString	m_Bemerkungen;
	CString	m_Betreibernummer;
	long	m_Betriebsbeauftragtennummer;
	CString	m_Betriebsbeauftragtentelefax;
	CString	m_Betriebsbeauftragtentelefon;
	CString	m_Betriebsbeauftragter;
	CString	m_Betriebsstaette;
	CString	m_Bilanznummer;
	CString	m_Bimschgenehmigungsnummer;
	CString	m_Bimschnummer;
	CString	m_Bimschspalte;
	CString	m_Branchennummer;
	CString	m_EDV;
	CString	m_EDVsonstige;
	COleDateTime	m_Erfassungsdatum;
	CString	m_Exportiert;
	CString	m_Firmenansprechpartner;
	CString	m_Firmenhausnummer;
	CString	m_Firmenname;
	CString	m_Firmenortsname;
	CString	m_Firmenpostleitzahl;
	CString	m_Firmenstrasse;
	CString	m_Firmentelefax;
	CString	m_Firmentelefon;
	CString	m_Gemeindekennzahl;
	CString	m_Hausnummer;
	CString	m_Nummer;
	CString	m_Ortsname;
	CString	m_Partnerfunktion;
	CString	m_Partnertelefax;
	CString	m_Partnertelefon;
	CString	m_Postleitzahl;
	BOOL	m_ro;
	CString	m_Strasse;
	BOOL	m_Unterschrift;
	CString	m_user;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGakSetRed)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
