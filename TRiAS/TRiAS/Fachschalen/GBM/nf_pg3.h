// nf_pg3.h : header file
//

class CDetailSatz;

/////////////////////////////////////////////////////////////////////////////
// CSetNF_PG3 recordset

class CSetNF_PG3 : public CRecordset
{
	CMapStringToPtr		m_mapMOB;

public:
	BOOL ModIDE( const char*, const char* );
	void RewriteIDE( const char*, CDetailSatz* );
	void TestPrintIDE( CStringArray* );
	BOOL IstMOB( const char* );

	CSetNF_PG3(CDatabase* pDatabase = NULL);
	~CSetNF_PG3();

	virtual BOOL Open( UINT nOpenType = AFX_DB_USE_DEFAULT_TYPE, LPCTSTR lpszSQL = NULL,
		DWORD dwOptions = none );

// Field/Param Data
	//{{AFX_FIELD(CSetNF_PG3, CRecordset)
	CString	m_NFP3_IDE;
	double	m_NFP3_AWE;
	double	m_NFP3_AEW;
	double	m_NFP3_GW;
	CString	m_NFP3_MOB;
	CString	m_NFP3_SAM;
	double	m_NFP3_SAG;
	CString	m_NFP3_SAT;
	CString	m_NFP3_KK;
	double	m_NFP3_KKG;
	CString	m_NFP3_KKT;
	CString	m_NFP3_KKV;
	CString	m_NFP3_KKK;
	double	m_NFP3_FV;
	CString	m_NFP3_BEM;
	//}}AFX_FIELD

	BOOL	Find( const char* );
	BOOL	IDE( const char* );
	BOOL	AWE( double );
	BOOL	AEW( double );
	BOOL	GW( double );
	BOOL	MOB( BOOL );
	BOOL	SAM( BOOL );
	BOOL	SAG( double );
	BOOL	SAT( BOOL );
	BOOL	KK( BOOL );
	BOOL	KKG( double );
	BOOL	KKT( BOOL );
	BOOL	KKV( BOOL );
	BOOL	KKK( BOOL );
	BOOL	BEM( const char* );

	void	InitListen( const char* );
	CDetailSatz	*FindIDE( const char* );

// Implementation
protected:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
	DECLARE_DYNAMIC(CSetNF_PG3)

	BOOL	SetSaveText( CString&, const char*, short );
	BOOL	SetSaveDoublePositive( double&, double, double );
};

class CDetailSatz
{
public:
	CDetailSatz();

protected:
	CString	m_NFP3_IDE;
	double	m_NFP3_AWE;
	double	m_NFP3_AEW;
	double	m_NFP3_GW;
	BOOL	m_NFP3_MOB;
	BOOL	m_NFP3_SAM;
	double	m_NFP3_SAG;
	BOOL	m_NFP3_SAT;
	BOOL	m_NFP3_KK;
	double	m_NFP3_KKG;
	BOOL	m_NFP3_KKT;
	BOOL	m_NFP3_KKV;
	BOOL	m_NFP3_KKK;
	double	m_NFP3_FV;
	CString	m_NFP3_BEM;
	BOOL	m_NFP3_FE;
	BOOL	m_NFP3_FZ;
	BOOL	m_NFP3_FZE;
	CString	m_strSonst;

public:
	CString&	IDE()	{ return m_NFP3_IDE; }
	double&		AWE()	{ return m_NFP3_AWE; }
	double&		AEW()	{ return m_NFP3_AEW; }
	double&		GW()	{ return m_NFP3_GW; }
	BOOL&		MOB()	{ return m_NFP3_MOB; }
	BOOL&		SAM()	{ return m_NFP3_SAM; }
	double&		SAG()	{ return m_NFP3_SAG; }
	BOOL&		SAT()	{ return m_NFP3_SAT; }
	BOOL&		KK()	{ return m_NFP3_KK; }
	double&		KKG()	{ return m_NFP3_KKG; }
	BOOL&		KKT()	{ return m_NFP3_KKT; }
	BOOL&		KKV()	{ return m_NFP3_KKV; }
	BOOL&		KKK()	{ return m_NFP3_KKK; }
	double&		FV()	{ return m_NFP3_FV; }
	CString&	Bem()	{ return m_NFP3_BEM; }
	BOOL&		FE()	{ return m_NFP3_FE; }
	BOOL&		FZ()	{ return m_NFP3_FZ; }
	BOOL&		FZE()	{ return m_NFP3_FZE; }
	CString&	Sonst()	{ return m_strSonst; }
	CDetailSatz& operator = ( CDetailSatz& );
};

typedef float (WINAPI *BER_AGG_PROC)( float, float, float, float, float, int, float );
typedef float (WINAPI *BER_BDM_PROC)( float, float, float, float, float, float );
typedef float (WINAPI *BER_BFL_PROC)( float, float, float, float, float );
typedef float (WINAPI *BER_BSA_PROC)( float );
typedef float (WINAPI *BER_GEF_PROC)( float, float, int, float );
typedef float (WINAPI *BER_VOLP_PROC)( float, float, float );
typedef float (WINAPI *BER_VOLT_PROC)( float );

class CCalculator
{
public:
	CSetNF_PG3*		m_pNF_PG3;
//	CSetNF_PG2H*	m_pNF_PG2H;
//	CSetNF_PG2D*	m_pNF_PG2D;
//	CSetNF_PG1GB*	m_pNF_PG1GB;
//	CSetNF_PG1*		m_pNF_PG1;
	CString			m_strIDE;
	CStringArray	m_arrIDE;

				CCalculator()		{}
				~CCalculator()		{}
	void		StartDialog();
	void		Calculate();
};
