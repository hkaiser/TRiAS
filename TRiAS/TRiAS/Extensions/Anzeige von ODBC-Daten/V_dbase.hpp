/*------------------------------------------------------------------------
File: V_DBASE.HPP

View_dBase -
gibt den Inhalt eines dBase-Files satzweise in eine Listbox aus.

Erarbeitet: J. Benkenstein				 	am: 19. Dez. 1991
					          		 Stand vom: 12. März 1994
---------------------------------------------------------------------------*/

#ifndef V_DBASE_HPP
#define V_DBASE_HPP       
                            
                          
// V_DBASE_HPP/////////////////////////////////////////////////////////////////////////////
// ShowFile dialog

class dBaseDispatch;
class CColumns;
class CRecSet;  
class CToolBarEx;
class CDataBaseExt;

// Die Klasse "ShowFile" stellt Funktionen für die Darstellung des
// Inhalts einer ODBC-Tabelle bereit

#include "derivedgrid.h"

class ShowFile : public CDialog
{
private:                                                
    short m_sRelCnt;				// Anz. d. Relationen
    DBaseRel **m_ppdBaseRel;		// Zeiger auf Slave-DB/Feld
    CMenu *m_pRelMenu;				// Zeiger auf Relations-Menü

	short m_sActRec, m_sMaxRec,		// Satz-Zähler
		  m_sCX, m_sCY;				// X-Y-Offset (BS-Position)	
    BOOL m_bToDelete;				// Lösch-Flag
    ErrCode m_sRC;					// Konstruktor-Flag
    CString m_strAliasName;			// AliasName

#ifndef __UseOGX__
		CToolBarEx m_WndButtons;		// ToolBar
#endif //__UseOGX__

	CColumnObjArray m_CColList;		// Container mit Spalten-Infos
	CColumns *m_pCColumns;			// liest alle Spalten-Infos

	CRecSet *m_pCRecSet;			// Record-Container 

#ifdef __UseOGX__
//		long m_nTicksSinceResize;		// speichert die Timeraufrufe seit dem letzten OnSize handling
//		UINT m_nTimer;					// Timernummer

		CString m_strFieldName;			// hier werden jetzt die entsprechenden Werte gespeichert
		CString m_strFieldVal;
#endif //__UseOGX__

	dBaseDispatch *m_pCDispatcher;	// zugeh. Dispatcher
	CDataBaseExt *m_pCDataBase;		// DataSource-Objekt
	HPROJECT m_hProject;			// das Projekt des aktuellen Objektes (JG990312)
	
public:                             
       // ListBox u.a. Parameter init.
   ShowFile (CWnd * pParent,	    // Zeiger auf Elternfenster     
   			 dBaseDispatch *pDisp,  // Zeiger auf rufenden dBase-Dispatcher
	     	 CPoint &TransLation,   // x,y-Verschiebung des Fensters
	     	 char * pAliasName,	    // Alias-Name der Datei
	     	 char * pFieldName,	    // akt. Feld-Name
	     	 char * pFieldVal = NULL); // akt. Feld-Inhalt, bei Expression NULL
	     	 
   ~ShowFile (void);				// Fenster löschen
   
	 	// Tabelleninhalt ausgeben
    void Darstellen (void);	
                                    
		// Inhalt der ListBox ins Clipboard kopieren                                    
    void ListToClip (void);			
		
		// Tabelleninhalt in Textdatei anspeichern
    void Save (void);			

		// Löschflag lesen
    BOOL ToDelete (void) { return m_bToDelete; }	
        
        // Konstruktor-Flag abfragen
    ErrCode Result (void) { return m_sRC; }
                               
		// Selektion ändern 	                               
    void SelchangeRowList (void);
         
protected:
	// Dialog Data
	//{{AFX_DATA(ShowFile)
	enum { IDD = IDD_VIEW_FRAME };
	//}}AFX_DATA

// Control je nach Funktion
#ifndef __UseOGX__
		CListBox	m_lbRowList;	
#else
		CGXRecordInfoWnd m_lbRowList;
		CSortedGrid	 m_wndRecord;
#endif //__UseOGX__

		// RecordSet init.         
    BOOL InitRecordSet (const char *pAliasName, const char *pFieldName, const char *pFieldVal, HPROJECT hProject);
    
    	// Spalten-Infos ausgeben
	BOOL OutputList (void);   	

		// Relations-Funktionen	
	BOOL ReadRelations (CString &strFieldName, 
					    short sColIndex);		// Relationen lesen
    void DeleteRelations (void);	    		// und löschen
    BOOL CreateRelMenu (void); 	    			// Relations-Menü aufbauen
    BOOL DeleteRelMenu (void); 	    			// und löschen

		// menu commands message map	                          
	void OnFirstField (void);
	void OnLastField (void);
	void OnFirstRecord (void);	
	void OnNextRecord (void);	
	void OnLastRecord (void);	
	void OnPrevRecord (void);	

		// Generated message map functions
		//{{AFX_MSG(ShowFile)
	// afx_msg void OnClose(void);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog(void);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeRowList(void);
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnDblclkRowlist(void);
	afx_msg void OnFieldinfo(void);
	afx_msg LONG OnRecord (UINT, LONG);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnUpdateAnySort(CCmdUI* pCmdUI);
	afx_msg void OnSortGridAsc();
	afx_msg void OnSortGridDesc();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditClear(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnEditClear();
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_MSG
//	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()
	
		// behandelt nur Relations-Menüpunkte 
	virtual LRESULT DefWindowProc( UINT message, WPARAM wParam, LPARAM lParam );
	
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	void DeleteDataBase (void);
	void SetGridStyle();
};
        
#endif          
        
	
