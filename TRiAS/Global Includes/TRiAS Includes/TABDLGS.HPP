// TabDlgs.hpp : header file
//
//	Der Modul realisert im Wesentlichen die Funktionalität einer CPropersheet.
//	Im Vergleich zur Sheet gibt es im CTabbedDialogs keine Buttons (Übernehmen usw.).
//
//	Hinweise zur Anwendung:
//	Innerhalb des MainDialogs wird im ClassWizard ein TabControl mit seiner zu
//	zeichnenden (wahren) Größe dargestellt. Die in den Tab zu ladenden Dialoge sind
//	entsprechend kleiner als WS_CHILD und ohne TitleBar (besser auch ohne Rahmen) 
//	zu entwerfen. Im ClassWizard wird dann innerhalb des MainDialogs eine Variable
//	des Typs CTabbedDialogs erzeugt. Dem Konstruktor ist bei Aufruf die max. Anzahl
//	der in ihm enthaltenen Dialoge anzugeben. In der Funktion OnInitDialog des MainDialogs
//	werden dann die einzelnen Dialoge mit der Funktion AddDialog in das TabControl ein-
//	gefügt:
//		m_Tab.AddDialog (&m_UserDlg, CUserDlg::IDD, "UserDSN");
//		m_Tab.AddDialog (&m_FileDlg, CFileDlg::IDD, "FileDSN");
//		m_Tab.SetActiveDialog (0);
//	Hinweis: Der Dialogkonstruktor darf das Objekt nicht erzeugen,
//		CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
//				 :CDialog()
//	dies wird innerhalb der Funktion AddDialog durchgeführt.
//	#JB970804

#ifndef _TABDLGS_HPP
#define _TABDLGS_HPP

/////////////////////////////////////////////////////////////////////////////
// CTabbedDialogs window

class CTabbedDialogs : public CTabCtrl
{
// Construction
public:
	CTabbedDialogs(int iDialogCnt);

// Attributes
private:
	int m_iMaxCnt;			//	max. Anzahl der Dialoge
	int m_iActInd;			//	akt. Einfügeindex
	int m_iActSel;			//	akt. SelektionsIndex
	CDialog **m_ppDialog;

// Operations
public:
	int GetDialogCount (void) { return m_iMaxCnt; }
	int GetActiveIndex (void) { return m_iActSel; }
	
//	sollte im OnInitDialog des MainDialogs gerufen werden
	int AddDialog (CDialog *pDlg,		//	Modeless-Dialog-ID (WS_CHILD) ohne Caption,
										//  zurück: 0 basierte Index des Dialogs
				   UINT uiResID,		//	Resource-ID
				   const char *pTitle);	//	Text in Tabcontrol
	CDialog *GetDialog (int iSel);		//	lese zum 0 basierten Index zugeh. Dialog
	CDialog *GetActiveDialog (void);	//	lese selektierten Dialog
	void SetActiveDialog (int iSel);	//	übergebenen Dialog
	BOOL SetActiveDialog (CDialog *pDlg);//	als aktuellen setzen
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabbedDialogs)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTabbedDialogs();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTabbedDialogs)
	afx_msg void OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif		//	_TABDLGS_HPP
