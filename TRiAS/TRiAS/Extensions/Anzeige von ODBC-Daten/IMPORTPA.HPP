// importpa.hpp : header file
//

#ifndef _IMPORT_HPP
#define _IMPORT_HPP         
    
#ifdef WIN32
	#define CPropertySheetExt CPropertySheet
#else
	const int PSWIZB_NEXT = 1;
	const int PSWIZB_BACK = 2;
	const int PSWIZB_FINISH = 4;

	class CPropertySheetExt : public CPropertySheet
	{
	public:
		CPropertySheetExt (UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
		~CPropertySheetExt (void);
		
		void SetWizardButtons (int iButtons);           
		void SetFinishText (const char *pText);
		
	protected:		
		HWND m_hWndEsc;                 	// Handle des Abbrechen-Button
		CButton m_btNext, m_btBack;			// "Wizard"-Buttons
		int m_iActPage;						// aktuelle Page
	};	
#endif

//	speichere alle über Config-Dialog gemachten Einstellungen
class CImportParams
{
public:
//	Attribute:
	CODBCInfos m_COdbcInfos;
	CString m_strTableName, m_strDataSource, m_strKoppelFeld, m_strHochWert, m_strRechtsWert,
			m_strFilter, m_strDefinition;
	ulong m_ulUnIdMKode, m_ulObjektMKode, m_ulPointCnt, m_ulNotImported;
	ulong * m_pulObjektKlassen;		// letztes Feld hat Wert 0 (also n-1 Kodes)
	BOOL m_bAction;					// 1/0 -> TRIAS/Tabelle abgleichen
	BOOL m_bDelNotExist;			// existierende Objekte löschen
	BOOL m_bAddNotExist;			// existierende Objekte hinzufügen	
	DataSourceType m_tDsn;			// Datenquellen Typ	

//	Zählervariablen
	long m_lImpCnt, m_lErrImpCnt, m_lDelCnt, m_lDoppTableCnt,
		 m_lDoppTriasCnt, m_lNewCnt;

//	Indizes in ArrayContainer
	short m_sKoppelIndex, m_sRechtsWertIndex, m_sHochWertIndex;

//	Konstruktor/Destruktor
	CImportParams (void);
	~CImportParams (void);	

	BOOL InfoComplete (void);		// Parameter vollst. ?
	void CleanUp (void);			// alle internen Infos löschen
};
#endif 	// 	_IMPORT_HPP
