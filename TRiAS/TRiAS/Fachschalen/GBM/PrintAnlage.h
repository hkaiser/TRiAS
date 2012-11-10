//	Print Anlage

#include "dibapi.h"

class CPrintAnlageArray : public CPtrArray
{
public:
	CPrintAnlageArray()		{}
	~CPrintAnlageArray();
};

class CPrintAnlage : public CObject
{
public:
	void SelectTRiASProject( const char* );
	void SelectTRiASView( const char* );
	void ResetObjColor( long, BOOL );
	void PrepareObjColor( long, BOOL );
	CString m_strViewName;
	void SetTopLeftOffset( CSize* );
	void DeleteStaticMembers();
	void CreateStaticMembers( CDC*, const char* );
	static CFont*			m_pFntNormal;
	static CFont*			m_pFntUeberschrift;
	static CFont*			m_pFntFett;
	static CFont*			m_pFntAnschrift;
	static CFont*			m_pFntAnschrFett;
	static CFont*			m_pFntBeitrag;
	static CFont*			m_pFntBeitragFett;
	static CSetNF_PG1*		m_pNF_PG1;
	static CSetNF_PG1GB*	m_pNF_PG1GB;
	static CSetNF_PG2D*		m_pNF_PG2D;
	static CSetNF_PG2H*		m_pNF_PG2H;
	static CSetNF_OG1*		m_pNF_OG1;
	static CSetNF_PG3*		m_pNF_PG3;
	static CStrasseSet*		m_pStrassen;
	static COrteSet*		m_pOrte;
	static CVerzSet*		m_pVerz;
	static CTriDBSet*		m_pTRiDB;

	char			m_cKennung;

public:
	CPrintAnlage()				{	m_lONr = -1L;
									m_hMetaFile = NULL;	}
	virtual ~CPrintAnlage()		{}
	virtual void	Print( CDC* ) = NULL;
protected:
	int PrintLogo( CDC*, int, int, int, const char*, const char* );
	CString m_strColor;
	CString GetAnsichtName( const char* );
	CMapStringToPtr m_mapObj2Project;
	CString GetProjectName( const char* );
	BOOL m_bNeuerOffset;
	CSize m_sizeTopLeftOffset;
	HENHMETAFILE m_hMetaFile;
	long m_lONr;
	void RenderTRiASAusschnitt( CDC*, const char*, long, RECTL&, CRect* );
	long GetObjNr( const char* );
	long GetTriasObjColor( long );
	BOOL GetTriasObjContainer( long, long* );
	short OrtNr( const char* );
	double TB( const char* );
	void PrintCheckBox( CDC *pDC, int x, int y, int dx, BOOL flag );
	void PrintTextF3( CDC *pDC, CFont *fnt, int x, int y, double r );
	void PrintTextF2( CDC *pDC, CFont *fnt, int x, int y, double r );
	void PrintTextF0( CDC *pDC, CFont *fnt, int x, int y, double r );
	void PrintTextR( CDC *pDC, CFont *fnt, int x, int y, const char *txt );
	void PrintExtText( CDC *pDC, CFont *fnt, int x, int y, int x1, int y1, const char* txt );
	void PrintText( CDC *pDC, CFont *fnt, int x, int y, const char *txt );
};

class CPrintAnlage1 : public CPrintAnlage
{
protected:
	CString m_strTIEF;
	double m_rAGGS;
	struct GEBAEUDE
	{
		double	m_rNr;
		double	m_rFl;
		double	m_rVz;
		double	m_rGh;
		BOOL	m_bVa;
	};

	CString		m_strPRO;
	CString		m_strIDE;
	CString		m_strStrasse;
	CString		m_strENA;
	CString		m_strEAN;
	CString		m_strEPL;
	CString		m_strEOR;
	CString		m_strORT;
	CString		m_strFLU;
	CString		m_strFST;
	CPtrArray	m_arrGebaeude;
	int			m_iBAR;
	double		m_rGFZ;
	double		m_rBMZ;
	double		m_rVGZ;
	double		m_rGUZ;
	double		m_rGEF;
	double		m_rKAT;
	double		m_rAGG;
	double		m_rTB;
	CString		m_strANDAT;
	CString		m_strANNWL;
	RECTL		m_lrTRiAS;

	BOOL		m_bInitialisiert;
	BOOL		Init();

public:
	long m_lENR;
	double m_rGEFS;
	CPrintAnlage1( const char*, long );
	~CPrintAnlage1();

	void	Print( CDC* );
};

class CPrintAnlage2 : public CPrintAnlage
{
protected:
	CString m_strOrt;
	CString m_strStrasse;
	struct FLAECHE
	{
		CString	m_strNr;
		double	m_rFl;
		double	m_rAbf;
		BOOL	m_bAns;
	};

	CString		m_strPRO;
	CString		m_strIDE;
	CString		m_strENA;
	CString		m_strEAN;
	CString		m_strEPL;
	CString		m_strEOR;
	CPtrArray	m_arrDFlaeche;
	CPtrArray	m_arrHFlaeche;
	RECTL		m_lrTRiAS;

	BOOL		m_bInitialisiert;
	BOOL		Init();

public:
	long m_lENR;
	CPrintAnlage2( const char*, long );
	~CPrintAnlage2();

	void	Print( CDC* );
};

class CPrintAnlage3 : public CPrintAnlage
{
protected:
	CString m_strBem;
	BOOL m_bFZE;
	BOOL m_bFZ;
	BOOL m_bFE;
	BOOL m_bKKK;
	BOOL m_bKKV;
	BOOL m_bKKT;
	double m_rKKG;
	BOOL m_bKK;
	BOOL m_bSAT;
	double m_rSAG;
	BOOL m_bSAM;
	BOOL m_bMOB;
	double m_rEW;
	double m_rAEW;
	double m_rAWE;
	CString		m_strPRO;
	CString		m_strIDE;

	BOOL		m_bInitialisiert;
	BOOL		Init();

public:
	long m_lENR;
	CPrintAnlage3( const char*, long );
	~CPrintAnlage3();

	void	Print( CDC* );
};

class CPrintAnlage4 : public CPrintAnlage
{
protected:
	RECTL m_lrTRiAS;
	CString m_strEPL;
	int m_iBAR;
	double m_rVGZ;
	double m_rTB;
	double m_rAGG;
	double m_rGEF;
	double m_rKAT;
	CString m_strFST;
	CString m_strFLU;
	CString m_strStrasse;
	CString m_strEOR;
	CString m_strEAN;
	CString m_strENA;
	double m_rBFL;
	CString m_strTIEF;
	CString m_strOrt;
	CString		m_strPRO;
	CString		m_strIDE;

	BOOL		m_bInitialisiert;
	BOOL		Init();

public:
	long m_lENR;
	CPrintAnlage4( const char*, long );
	~CPrintAnlage4();

	void	Print( CDC* );
};

class CPrintAnlage5 : public CPrintAnlage
{
protected:
	COLORREF GetLegendColor( short, const char* );
	short GetLegendHatch( short, const char* );
	RECTL m_lrTRiAS;
	struct FLAECHE
	{
		CString	m_strNr;
		double	m_rFl;
		double	m_rAbf;
		BOOL	m_bAns;
	};

	CPtrArray	m_arrDFlaeche;
	CPtrArray	m_arrHFlaeche;

	double m_rVFlGes;
	double m_rDFlGes;
	CString m_strEOR;
	CString m_strEPL;
	CString m_strEAN;
	CString m_strENA;
	CString		m_strPRO;
	CString		m_strIDE;

	BOOL		m_bInitialisiert;
	BOOL		Init();

public:
	long m_lENR;
	CPrintAnlage5( const char*, long );
	~CPrintAnlage5();

	void	Print( CDC* );
};

class CPrintAnlage6 : public CPrintAnlage
{
protected:
	CString m_strStrasse;
	CString m_strFST;
	CString m_strFLU;
	CString m_strORT;
	CString m_strBEM;
	CString m_strAFU;
	CString m_strAFA;
	double m_rPGR;
	double m_rPFU;
	double m_rPFA;
	double m_rVFL;
	double m_rFLG;
	int m_iBLT;
	int m_iART;
	CString m_strIDE;
	CString		m_strPRO;

	BOOL		m_bInitialisiert;
	BOOL		Init();

public:
	long m_lENR;
	CPrintAnlage6( const char*, long );
	~CPrintAnlage6();

	void	Print( CDC* );
};

class CPrintAnlage7 : public CPrintAnlage
{
public:
	CString m_strLogoFileName;
	CString m_strLogoPosition;
	long m_lENR;
	CString m_strRW_DM_QA;
	CString m_strRW_DM_JA;
	CString m_strRW_FL_RU;
	CString m_strRW_FL_GE;
	CString m_strVOLLGESCH;
	CStringArray m_arrInfo;
	CStringArray m_arrText;
	CString	m_strIDE;
	CString	m_strFileName;

	CString	m_strNFP1_ENA;
	CString	m_strNFP1_EAN;
	CString	m_strNFP1_EPL;
	CString	m_strNFP1_EOR;
	CString	m_strNFP1_KASS;

	CString	m_strNFP1_ORT;
	CString	m_strSTR_DECO;
	CString	m_strNFP1_FLU;
	CString	m_strNFP1_FST;
	CString	m_strNFP1_GFZ;

	CString	m_strNFP1_AGG;
	CString	m_strVOLLIE2;
	CString	m_strVOLLIE3;
	CString	m_strNFP1_BDM;
	CString	m_strNFP1_VGZ;

	CString	m_strAddr1;
	CString	m_strAddr2;
	CString	m_strAddr3;
	CString	m_strAddr4;
	CString	m_strAddr5;
	BOOL	m_bDatum;

	BOOL m_bB_PLAN;

	BOOL		m_bInitialisiert;
	BOOL		Init();

public:
	CPrintAnlage7( const char*, long );
	~CPrintAnlage7();

	void	Print( CDC* );
protected:
	void SetupDataString( CString& );
};

class CPrintAnlage8 : public CPrintAnlage
{
public:
	CString		m_strIDE;
	CString		m_strFileName;
	long		m_lMasstab;
	RECTL		m_lrTRiAS;

	BOOL		m_bInitialisiert;
	BOOL		Init();

public:
	CPrintAnlage8( const char*, long );
	~CPrintAnlage8();

	void	Print( CDC* );

protected:
	void RenderTRiASAusschnittDirekt( CDC*, const char*, long, RECTL&, CRect* );
	void	BerechneMasstab( CDC*, long, RECTL&, CRect* );
};

class CFileBitmap
{
	CString		m_strFileName;
	HDIB		m_hDIB;
	CPalette*	m_palDIB;
	CSize		m_sizeDoc;

public:
				CFileBitmap( const char* );
				~CFileBitmap();
	HDIB		GetHDIB();
	CPalette*	GetDocPalette() const { return m_palDIB; }

protected:
	void		InitDIBData();
};
