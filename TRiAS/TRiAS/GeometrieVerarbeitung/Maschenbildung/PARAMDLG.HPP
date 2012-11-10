// ParamDialog.hpp : header file
//

#ifndef _PARAMDIAOLG_HPP
#define _PARAMDIAOLG_HPP

class CObjektKante;
class CParamDialog;
class CMaschenBildung;
class CLinVerPropAct;
class CVerschnittPage;


///////////////////////////////////////////////////////////////////////////////////////////////
//	CParameters 
class CParameters
{
//	Attribute
private:
	ULONG m_ulOldUnIdent,	// UniqueIdent-Merkmalskode der urspünglichen Objekte
		  m_ulNewUnIdent,	// OldUniqueIdentMCode für das Sammeln der UniqueIdents der
							// urspünglichen Objekte (!!! ???)
		  m_ulXFuzzy,		// interne Fuzzy-Toleranzen
		  m_ulYFuzzy,
		  m_ulDangleLen;
	HPROJECT m_hPr;			// Zieldatenquelle für neu erzeugte Objekte
	
public:
//	Konstruktor/Destruktor
	CParameters (void);
	~CParameters (void) {}

//	einfache Lesefunktionen
	ULONG GetOldUniqueIdent (void)	{ return m_ulOldUnIdent; }
	ULONG GetNewUniqueIdent (void)	{ return m_ulNewUnIdent; }
	ULONG GetXFuzzy (void) { return m_ulXFuzzy; }
	ULONG GetYFuzzy (void) { return m_ulYFuzzy; }
	ULONG GetDangleLen (void) { return m_ulDangleLen; }

//	von TRiAS Merkmalskode für UniqueIdent holen
	void ReadNewUnIdent (void);

//	weitere Memberfunktionen
	BOOL Init (void);
	BOOL Init (double &dUserFuzzy, double *pdDangleLen = NULL);		// Werte init.

//	Toleranzen in Datenbankeinheiten berechnen
	HRESULT CalculateTolerances (CObjektKante &OK,		//	Koordinate eines bel. Objektes
								 double dUserFuzzy, double *pdDangleLen = NULL);	//	vom Nutzer eingegebene Toleranzen
	HRESULT CalculateTolerances (long lX, long lY, double dUserFuzzy, double *pdDangleLen = NULL);

	friend class CParamDialog;
	friend class CVerschnittPage;
	friend class CMaschenBildung;
};



///////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _NO_PARAM_DIAOLOG
#define _NO_PARAM_DIAOLOG

// CParamDialog dialog
class CProgressIndicator;

//	Typdefinitionen
DefineSmartInterface(EnumObjectsByNumber);	
typedef list<CObjektKante> CObjektKantenListe;
typedef CObjektKantenListe::iterator CObjektKantenList_tit;
typedef list<WEnumObjectsByNumber> EnumListe;

class CParamDialog : public CPropertyPage
{
	DECLARE_DYNCREATE(CParamDialog)

private:
//	Attribute
	DWORD m_dwFlags;					//	Dialog-Flags
	CObjektKantenListe m_ObjektListe;	//	Liste der zu bildenden Maschen
	double m_dFuzzy;					//  Fangbereich zweier Stützpunkte
	BOOL m_bUnionLines,					//	restl. Linien vereinigen
		 m_bDeleteLines,				//	urspünglichen Objekte löschen
		 m_bOutputMerkmal,				//	UniqueIdent der Vereinigten ausgeben
		 m_bUnionMaschen,				//	Maschen vereinigen
		 m_bMarkObjects;				//	urspünglichen Objekte kennzeichnen (#HK971217)

	CParameters m_Params;				//	Parameter
	EnumListe m_OutNrListe;				//	Objektnummern-Ausgabe-Strom

public:
	CLinVerPropAct *m_pAction;
	
//	Konstruktor/Destruktor
	CParamDialog();
	~CParamDialog();

//	weitere Memberfunktionen
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	HRESULT SetEnumLONG (IEnumObjectsByNumber *pIEnum);		// übergibt Objektmenge
	HRESULT GetEnumLONG (WEnumObjectsByNumber &WEnum);
	HRESULT SetDataSource (HPROJECT hPr);

	static CParamDialog *CreateInstance (CLinVerPropAct *);	// Page erzeugen

//	Parameter setzen
	void SelectFuzzy (double);
	void SelectUnionMaschen (BOOL);
	void SelectUnionLines (BOOL);
	void SelectDeleteOldLines (BOOL);
	void SelectOutputMerkmal (BOOL);
	void SelectMarkObjects (BOOL);								// #HK971217

//	Parameter lesen
	double GetFuzzy (void) { return m_dFuzzy; }
	BOOL GetUnionMaschen (void) { return m_bUnionMaschen; }
	BOOL GetUnionLines (void) { return m_bUnionLines; }
	BOOL GetDeleteOldLines (void) { return m_bDeleteLines; }
	BOOL GetOutputMerkmal (void) { return m_bOutputMerkmal; }
	BOOL GetMarkObjects (void) { return m_bMarkObjects; }		// #HK971217

// Dialog Data
	//{{AFX_DATA(CParamDialog)
	enum { IDD = IDD_LINVERFOLGUNG };
	CButton	m_btMarkObjects;
	CButton	m_btOutputMerkmal;
	CStatic	m_stDescription;
	CButton	m_btUnionMaschen;
	CButton	m_btUnionLines;
	CButton	m_btDeleteLines;
	CEdit	m_edFuzzy;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CParamDialog)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
//	Beschreibungstext ausgeben
	void OutputDescription (UINT uiResID);

//	benutzte Kanten in TRIAS löschen/kennzeichnen
	BOOL DeleteLinesInTrias (CProgressIndicator *pIndicator, CString &strCaption);

// #HK971217
	BOOL MarkObjectsInTrias (CProgressIndicator *pIndicator, CString &strCaption);

//	benutzte Linien in Liste löschen
	void DeleteLinesInListe (void);

	void SetButtons (void);			// Button für den WIZZARD setzen
	CPropertySheet *GetPropertySheet (void) { return (CPropertySheet *)GetParent (); } 

	// Generated message map functions
	//{{AFX_MSG(CParamDialog)
	afx_msg void OnChangeFuzzy();
	virtual BOOL OnInitDialog();
	afx_msg void OnDeleteLines();
	afx_msg void OnLinesUnion();
	afx_msg void OnMaschenUnion();
	afx_msg void OnSetfocusFuzzy();
	afx_msg void OnDeltaposFuzzy(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutputMerkmal();
	afx_msg void OnMarkObjects();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif		// _NO_PARAM_DIAOLOG

#endif		//	_PARAMDIAOLG_HPP

