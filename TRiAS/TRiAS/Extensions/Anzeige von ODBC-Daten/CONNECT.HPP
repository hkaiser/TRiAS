//	CONNECT.HPP:	Projektbezogene ODBC-Anbindung definieren.
//
//	Erarbeitet: J. Benkenstein					Stand vom: 28.09.94


#ifndef _CONNECT_HPP
#define _CONNECT_HPP           

#include "AutoListComboBox.h"
                    
/////////////////////////////////////////////////////////////////////////////
// CConnect dialog

class CConnect : public CDialog
{                    
private:
	BOOL m_bResult, m_bInfosStored;
	CODBCInfos m_OdbcInfos;
	long m_lObjNr;
	CString m_strActObjKlasse;			// aktuelle Objekt-Klasse	//JG wir benutzen jetzt nur noch den Identifikator (weils eindeutig ist)
	CString m_strOldObjKlasse;			// alte Objekt-Klasse
	ulong m_nActObjIdent;				// dito, aber als Nummer (nihct vergessen nachzuführen)
	ulong m_nOldObjIdent;
	
	DataSourceType m_tDsn;
	CString m_strDsn;

// Construction
public:
	CConnect (CWnd* pParent, long lActObjNr = 0);

// Dialog Data
	//{{AFX_DATA(CConnect)
	enum { IDD = IDD_CONNECTIONS };
	CFileDlg m_dlgFileDsn;
	CUserDlg m_dlgUserDsn;
	CUserDlg m_dlgSystemDsn;
	CTabbedDialogs m_tbDsn;
	CButton	m_btLastEntry;
	CAutoListComboBox m_cbObjKlassen;
	CAutoListComboBox m_cbMerkmalsKodes;
	CAutoListComboBox m_cbTables;
	CAutoListComboBox m_cbKoppelFields;
	CButton m_btMermkalsKodes; 
	CButton m_btWhereKlausel; 
	CButton m_btRelations;
	CButton m_btBeenden;
	CButton m_btStoreConnection;
	CButton m_btCreateWhereKlausel;
	CButton m_btStandard;
	CEdit m_edAliasName;
	CEdit m_edWhereKlausel;			
	CHelpText m_stDescription;
	//}}AFX_DATA
	
	BOOL Result (void) { return m_bResult; }

// Implementation
protected:        
	void SetControlState (void);		// Control-Status setzen
	void SetStoreButton (void);			// Store-Button akt.
	void SetCreateRelations (void);		// Create-Relations-Button setzen
	void SetCreateWhereKlausel (void);	// erzeuge Where-Klausel-Button prüfen
	void SetKoppelFields (void); 		// Koppelfeld-ComboBox aktivieren/deaktivieren
	void SetTables (void);				// Table-Box
	void ResetODBCInfos (void); 		// alle über ODBC gelesenen Infos löschen 
           
	BOOL ReadActConnections (const char *pObjKlasse = NULL, ulong nObjIdent = 0); // Infos der gew. Obj-Klasse lesen und ausgeben // JG added default Parameter
	BOOL StoreActConnection (void);		// aktuellen Anbindungen speichern 
	BOOL QueryStore (void);				// speichern über vorige Abfrage                 
	
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CConnect)
	afx_msg void OnSelChangeObjKlasse (void);		// neue Objektklasse
	afx_msg void OnSelChangeMerkmal (void);			// neues Merkmal
	afx_msg void OnSelChangeTable (void);			// neue Tabelle
	afx_msg void OnSelChangeKoppelField (void);		// neues Koppelfeld
	afx_msg void CreateRelations (void);			// Relationen erzeugen
	afx_msg void OnChangeWhereKlausel (void);		// Klausel wurde geändert
	afx_msg void OnChangeAliasName (void);			// AliasName wurde geändert
	afx_msg void WantMerkmalsKodes (void);			// Merkmals-Selektion gewünscht
	afx_msg void WantWhereKlausel (void); 			// Klausel-Eingabe gewünscht
	afx_msg void CreateWhereKlausel (void);			// Where-Klausel erzeugen	
	afx_msg void StoreConnection (void);			// Infos speichern
	afx_msg void OuputKlauselDescription (void); 	// BeschreibungsText für Klausel ausgeben
	afx_msg void OutputAliasDescription (void);		// BeschreibungsText für AliasName ausgeben
	afx_msg void StandardDataSource (void); 		// akt. DSN für alle Objekt-Klassen nehmen 
	afx_msg void Beenden (void);					// Dialog beenden
	virtual BOOL OnInitDialog(void);
	afx_msg void OnLastentry();
	afx_msg OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif  // _CONNECT_HPP
