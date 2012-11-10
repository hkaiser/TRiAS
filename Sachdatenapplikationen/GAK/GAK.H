// gak.h : main header file for the GAK application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGakApp:
// See gak.cpp for the implementation of this class
//

class CRPEJob; 


// JG Accessors für die Views hinzugefügt
class CAbfView;
class CGakView;

// JG BGSAbglForwards
class CDatabaseExt : public CDatabase
{      
//	Konstruktor/Destruktor
public:
	CDatabaseExt () {}
	~CDatabaseExt () { if (IsOpen ()) Close (); }
};

class CParameters;
class CDoAbgleich;
class CResultDialog;
class CAbgleichParameter
{
	public:
	CString m_strLastErzeuger;
	CString m_strLastAsn;
	CString m_strAbfallTable;
	CString m_strErzTable;
	BOOL m_bOnlyThisErzeuger;
	BOOL m_bLockTables;

	CAbgleichParameter(	const CString& strLastErzeuger,
						const CString& strLastAsn,
						const CString& strAbfallTable,
						const CString& strErzTable,
						const BOOL bOnlyThisErzeuger,
						const BOOL bLockTables);
	void ModifyParameters(CParameters* params);
};

class CGakApp : public CWinApp
{
private:
// BGSAbglMember
//	Attribute
	BOOL m_bError;
	CDatabaseExt *m_pdbMDB;
	CDatabaseExt *m_pdbFoxPro;
	CParameters *m_pParamDlg;
	CDoAbgleich *m_pAbgleichDlg;
	CResultDialog *m_pResDlg;

// end
	CMultiDocTemplate* m_pErzTemplate;
	CMultiDocTemplate* m_pAbfTemplate;

	CAbfView* m_pAbfView;
	CGakView* m_pErzView;

//	KK990714
	CWnd * m_pAbfWnd;
	CWnd * m_pErzWnd;

public:
	// void SetCaption();
	BOOL m_bResDlg;					// Ergebnisdialog einer Recherche aktiv ?

	CGakApp();
	~CGakApp();


//	KK990714
	void SetErzWindow ( CWnd *pWnd)
	{
		m_pErzWnd = pWnd;
	}

	void SetAbfWindow ( CWnd *pWnd)
	{
		m_pAbfWnd = pWnd;
	}

	void SetWindowStatus ( BOOL iFlag)
	{
		if ( m_pAbfWnd )
			m_pAbfWnd->EnableWindow(iFlag);
		if ( m_pErzWnd )
			m_pErzWnd->EnableWindow(iFlag);
	}

//-------------------------------------
	CAbfView* GetAbfallView()
	{	
		return m_pAbfView;
	}

	CGakView* GetErzeugerView()
	{
		return m_pErzView;
	}

	void ReleaseView(const CView* pView)
	{
		if (pView == (CView*) m_pAbfView)
		{
			m_pAbfView = NULL;
			return;
		}
		if (pView == (CView*) m_pErzView)
		{
			m_pErzView = NULL;
			return;
		}
		// Fehler was soll denn hier abgemeldet werden
		ASSERT(false);
	}

	const CString& GetAbfallTable()
	{
		return m_strAbfallTable;
	}
	const CString& GetErzTable()
	{
		return m_strErzTable;
	}
	void CreateAbfaelle (const char *pNummer = NULL, BOOL bSetFocus = TRUE);	// AbfallView erzeugen
	void CreateStammdaten (const char *pNummer = NULL, BOOL bSetFocus = TRUE);	// StammdatenView
	void OutputMessage (int iMessageCode);		// beliebige Nachricht an Nutzer ausgeben
	void OutputMessage (const char *pText);		// beliebige Nachricht an Nutzer ausgeben	
	void OutputBarMessage (const char *pText);	// beliebige Nachricht in Statusbar ausgeben
	const char *UserName (void) { return m_strUserName; }
	const char *DatabaseName (void) { return m_strDatabaseName; }
	CRPEJob *Print (const char *ReportFile, const char *pTitle=NULL, const char *pSubst=NULL, 
					BOOL btoWindow = TRUE, CWnd* pWnd = NULL);

//	Tabellennamen lesen
	CString ErzeugerDefaultSQL (void) { return m_strErzTable; }
	CString AbfallDefaultSQL (void) { return m_strAbfallTable; }
	CString GemeindenDefaultSQL (void) { return m_strGemeindenTable; }
	CString BranchenDefaultSQL (void) { return m_strBranchenTable; }
	CString AbfallArtenDefaultSQL (void) { return m_strAbfallArtenTable; }
	CString EntsorgerDefaultSQL (void) { return m_strEntsorgerTable; }
	CString TransporteureDefaultSQL (void) { return m_strTransporteureTable; }
	CString VerbringungsDefaultSQL (void) { return m_strVerbringungsTable; }
	CString KreisDefaultSQL (void) { return m_strKreisTable; }
	CString VerfahrenDefaultSQL (void) { return m_strVerfahrenTable; }

//	eine der obigen Tabellen in Verwendung ?
	BOOL TableInUse (const CString &strTableName);

//	lese Infos über Hintergrund-Tabellen
	BOOL OnlyValidEntsorger (void);
	BOOL OnlyValidTransporteure (void);

	void ReadTablesFromIni (void);	// alle Tabellennamen aus Ini-Datei lesen

	BOOL CheckOdbcConnection (BOOL bOutputUserInfo = TRUE);
	
//	neuen Datenbasis-Namen setzen
	void SetNewDatabase (const char *pNewDatabaseName);

// Abgl merge
	CString GetAbgleichParameter(const CString& strSection, const CString& strKey, const CString& strDefault = "");
	int GetAbgleichParameterInt(const CString& strSection, const CString& strKey, const int nDefault = 0);
	BOOL SetAbgleichParameter(const CString& strSection, const CString& strKey, const CString& value);
	BOOL SetAbgleichParameter(const CString& strSection, const CString& strKey, const int& value);
	CString GetAbgleichIniFileName();
// JG BgsAbgl
	void DoAbgleich (BOOL bLast,CAbgleichParameter * pAbglParas = NULL);

protected:
	CString m_strUserName;			// vom Nutzer eingegbener Name
	CString m_strDatabaseName;		// Name der Datenbasis
	CString m_strAbfallTable;		// Name der akt. Abfalltabelle
	CString m_strErzTable;			// Name der akt. Erzeugertabelle

//	Namen der Hintergrund-Tabellen
	CString m_strGemeindenTable,	
			m_strBranchenTable, 
			m_strAbfallArtenTable,
			m_strEntsorgerTable,
			m_strTransporteureTable,
			m_strVerbringungsTable,
			m_strKreisTable,
			m_strVerfahrenTable;

	CView* CreateDaten (CMultiDocTemplate *pDoc, const char *pNummer = NULL, BOOL bSetFocus = TRUE);
	BOOL CheckAllTables (void);		// existieren alle Tabellen
	void LookGKZ (const CString &strGKZ);
// JG BgsAbgl
	void DeleteAllDatas ();
	void ReadParams (CParameters *m_pParams);
	void ReadTables (CParameters *pParams);

// Overrides
	virtual LRESULT ProcessWndProcException (CException* e, const MSG* pMsg);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGakApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGakApp)
	afx_msg void OnAppAbout();
	afx_msg void OnCreateStammdaten();
	afx_msg void OnCreateAbfaelle();
	afx_msg void OnLookNr();
	afx_msg void OnUpdateLookNr(CCmdUI* pCmdUI);
	afx_msg void OnCompactDatabase();
	afx_msg void OnRepairDatabase();
	afx_msg void OnRecherche();
	afx_msg void OnUpdateRecherche(CCmdUI* pCmdUI);
	afx_msg void OnAbgleich ();
	afx_msg void OnDruckErzliste();
	afx_msg void OnLastAbgleich();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
