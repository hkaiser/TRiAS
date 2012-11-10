// NF_PG1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetNF_PG1 recordset

class CBasisSatz
{
protected:
	double m_dVOL;
	double m_dGFL;
	CString m_strNA_B_PLAN;
	double m_dVOLU;
	double m_dTIEB;
	BOOL m_bTIEF;
	double m_rBFL;
	double m_rAGG;
	double m_rAGGS;
	double m_rGEF;
	double m_rGEFS;
	double m_dRW_DM_QA;
	double m_dRW_DM_JA;
	double m_dRW_FL_RU;
	double m_dRW_FL_GE;
	BOOL m_bAnDatGueltig;
	CString		m_strPLZ;
	CString		m_strIDE;
	CString		m_strOrt;
	CString		m_strStr;
	CString		m_strHausnr;
	CString		m_strFlur;
	CString		m_strFlurstk;
	CString		m_strBesitzer;
	BOOL		m_bGueltig;
	double		m_dBFlaeche;
	double		m_dBeitrag;
	double		m_dBAR;
	double		m_rGFZ;
	double		m_rBMZ;
	double		m_rVGZ;
	double		m_rGUZ;
	double		m_rKAT;
	CTime		m_strANDAT;
	CString		m_strKASS;
	CString		m_strANNWL;
	double		m_dVOLLIE2;
	double		m_dVOLLIE3;
	double		m_dBDM;
	CString		m_strNEIG;

public:
	BOOL		m_bBBGedr;
	BOOL		m_bGBGedr;

	CString& NA_B_PLAN();
	double& VOLU();
	double& TIEB();
	BOOL&	TIEF()			{	return m_bTIEF;	}
	double& BFL()			{	return m_rBFL;	}
	double& AGG()			{	return m_rAGG;	}
	double& AGGS()			{	return m_rAGGS;	}
	double& GEF()			{	return m_rGEF;	}
	double& GEFS()			{	return m_rGEFS;	}
	BOOL& AnDatGueltig()	{	return m_bAnDatGueltig;	}
	CString AnDatum();
				CBasisSatz( const char* );
	BOOL		Gueltig()	{	return m_bGueltig;	}
	const char*	IDE()		{	return m_strIDE;	}
	CString&	Ort()		{	return m_strOrt;	}
	CString&	PLZ()		{	return m_strPLZ;	}
	CString&	Strasse()	{	return m_strStr;	}
	CString&	Hausnr()	{	return m_strHausnr;	}
	CString&	Flur()		{	return m_strFlur;	}
	CString&	Flurstk()	{	return m_strFlurstk; }
	CString&	Besitzer()	{	return m_strBesitzer; }
	double&		GSFlaeche()	{	return m_rKAT; }
	double&		BFlaeche()	{	return m_dBFlaeche; }
	double&		Beitrag()	{	return m_dBeitrag; }
	double&		BAR()		{	return m_dBAR; }
	double&		GFZ()		{	return m_rGFZ; }
	double&		BMZ()		{	return m_rBMZ; }
	double&		VGZ()		{	return m_rVGZ; }
	double&		GUZ()		{	return m_rGUZ; }
	double&		KAT()		{	return m_rKAT; }
	CTime&		ANDAT()		{	return m_strANDAT; }
	CString&	AnNWL()		{	return m_strANNWL;	}
	CString&	KASS()		{	return m_strKASS;	}
	double&		VOLLIE2()	{	return m_dVOLLIE2;	}
	double&		VOLLIE3()	{	return m_dVOLLIE3;	}
	double&		BDM()		{	return m_dBDM;	}
	double&		RW_DM_QA()	{	return m_dRW_DM_QA;	}
	double&		RW_DM_JA()	{	return m_dRW_DM_JA;	}
	double&		RW_FL_RU()	{	return m_dRW_FL_RU;	}
	double&		RW_FL_GE()	{	return m_dRW_FL_GE;	}
	CString&	NEIG()		{	return m_strNEIG;	}
};

class CBasisArray : public CPtrArray
{
	CMapStringToPtr	m_mapIndex;

public:
	void Add( CBasisSatz* );
					CBasisArray();
					~CBasisArray();
	void			Clear();
	CBasisSatz*		Add( const char* );
	CBasisSatz*		Find( const char* );
};

class CSetNF_PG1 : public CRecordset
{
public:
	long GetCount();
	void UpdateListen( CStringArray* );
	BOOL ModIDE( const char*, const char* );
	void RewriteIDE( CBasisSatz* );
	void	ResetIDE( const char* );
	CString Projekt()	{	return m_strProjekt;	}
	void CopyGS( const char* quelle, const char* neu );
	void Add2ArrayByFlur( const char*, const char*, CStringArray* );
	void Add2ArrayByEigner( const char*, CStringArray* );
	CBasisSatz* FindIDE( const char* ide );
	short	GetSize();
	void	Refresh();
	void	InitListen( const char* );
	void	Reset()		{ m_bInitialisiert = FALSE; }
	void	Add2Array( const char*, CStringArray* );

	void	TestPrintBB( CStringArray* );
	void	TestPrintGB( CStringArray* );

	CSetNF_PG1(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSetNF_PG1)

//	CString	m_NFP1_ENA;
//	CString	m_NFP1_EAN;
//	CString	m_NFP1_EPL;
//	CString	m_NFP1_EOR;
// Field/Param Data
	//{{AFX_FIELD(CSetNF_PG1, CRecordset)
	CString	m_NFP1_PRO;
	CString	m_NFP1_IDE;
	CString	m_NFP1_ORT;
	CString	m_NFP1_FLU;
	double	m_NFP1_KAT;
	CString	m_NFP1_FST;
	double	m_NFP1_GFZ;
	double	m_NFP1_BMZ;
	double	m_NFP1_VGZ;
	double	m_NFP1_GUZ;
	CString	m_NFP1_TIEF;
	double	m_NFP1_GEF;
	double	m_NFP1_AGG;
	double	m_NFP1_BFL;
	CString	m_NFP1_AST;
	CString	m_NFP1_STC;
	double	m_NFP1_BAR;
	CTime	m_NFP1_ANDAT;
	double	m_NFP1_TIEB;
	double	m_NFP1_BDM;
	CString	m_NFP1_KASS;
	double	m_NFP1_AGGS;
	double	m_NFP1_GEFS;
	double	m_NFP1_FLGG;
	CString	m_B_GEDR;
	CString	m_B_GE_D;
	CString	m_B_GE_Z;
	CString	m_NA_B_PLAN;
	double	m_NFP1_VOLU;
	double  m_VOLLIE2;
	double  m_VOLLIE3;
	CString	m_NFP1_ANNWL;
	double	m_RW_DM_JA;
	double	m_RW_DM_QA;
	double	m_RW_FL_GE;
	double	m_RW_FL_RU;
	CString	m_NFP1_NEIG;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetNF_PG1)
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
	CString m_strLastInitID;
	void WriteBack( CBasisSatz* );
	BOOL			m_bInitialisiert;
	CBasisArray		m_arrBasis;
	CString			m_strProjekt;
};
