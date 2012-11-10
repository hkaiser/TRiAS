#if !defined(AFX_TESTRS_H__E7311AA5_E735_11D2_8D1C_006097A8F384__INCLUDED_)
#define AFX_TESTRS_H__E7311AA5_E735_11D2_8D1C_006097A8F384__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestRS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestRS recordset

class CTestRS : public CRecordset
{
public:
	CTestRS(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CTestRS)

// Field/Param Data
	//{{AFX_FIELD(CTestRS, CRecordset)
	CString	m_Prioritaet;
	BOOL	m_Bearbeitet;
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
	CTime	m_Erfassungsdatum;
	CTime	m_Aenderungsdatum;
	BOOL	m_ro;
	CString	m_user;
	CString	m_EAKNummer;
	CString	m_Nachweisnummer;
	CString	m_Exportiert;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestRS)
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

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTRS_H__E7311AA5_E735_11D2_8D1C_006097A8F384__INCLUDED_)
