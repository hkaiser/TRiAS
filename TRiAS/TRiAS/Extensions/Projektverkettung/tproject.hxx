// Projektverwaltung (objektbezogenes Umschalten zu anderen Projekten)
// File: TPROJECT.HXX

#if !defined(_TPROJECT_HXX)
#define _TPROJECT_HXX


//-----------------------------------------------------------
class CProjectExtension : public CTriasExtension {
private:

	short m_iActive;

	UINT m_wMsg1;
	UINT m_wMsg2;
	UINT m_wMsg3;

//---------HauptProjekt----------------------------------------
	char *m_pMainProject;		// MainProjektName
	char *m_pMainUser;			// MainUserName
	char *m_pMainSight;			// MainSichtName

	short m_iLevel;
	short m_iLowLevel;
	short m_iHighLevel;

	UINT m_MenuID1;
	UINT m_MenuID2;
//----------------------------------------------------------------

	long m_lMainSightContainer[4];		// MainSichtContainer
	int m_NumMenuPoints;
	int m_iActMenuPoint;
	char *m_pLocDir;	// lokales ProjektVerzeichnis
	char *m_pPrevDir;	// vorheriges lokales ProjektVerzeichnis
	char *m_pMainDir;	// globales ProjektVerzeichnis
	char *m_pProjectName;	// neues Projekt
	char *m_pProjectKey;	// neuer Projektschlüssel
	char *m_pOwnerCheck;	// Owner ProjectName
	HWND m_hWnd;		// ORFenster mit Fokus
	HMENU m_hMenu;		// Menu der Erweiterung
	long m_lONr;		// selektiertes Objekt
	long m_lIdent;		// zugehöriger Ident
	long m_lHeadMCode;	// MCode TP in DB-Header
	short m_iMenu;
	short m_iMain;
	short m_isSwitchTP;
	short m_iObjCount;
	short m_iSetCont;	// Container setzen
	short m_isSearch;

// KK010115
	char *_pTRiNam;		// TRiASName aus Registry
	HPROJECT m_hPr;		// aktuelle Datenquelle


	class PROJTree * m_pPROJ;
	class TPRJTree * m_pTPRJ;
	class MMenuTree *m_pMenu;


// KK 010521 - trick
	char * _pIniOriginal;
	char * _pIniTemp;
	bool m_bTPUndef;
	bool m_isTempINI;

protected:
// überladene virtuelle Funktion(en)

	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);
	STDMETHOD_(BOOL, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (THIS_ UINT uiMenuID, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);
	STDMETHOD_(LRESULT, WindowsNotification) (THIS_ UINT wMsg, WPARAM wParam, LPARAM lParam);

public:
// Konstruktor / Destruktor
		CProjectExtension (void);
		~CProjectExtension (void);


//------------Member
		void DefinitionAusschnitt(void);
		void DefineStartParameter ( void);
		void CreateTPMenu ( HMENU);
		void CreateTPPartMenu ( HMENU);
		void DeleteTPMenu ( HMENU);
		void ModifyProjectProFile ( void );
		void StoreProjectProFile ( short, char *, char *, char *, char *);
		void ModifyMenu ( HMENU);
		void StoreMainProject ( void );
		BOOL SwitchToProject ( char *, char *, char *);
		void GoToPreviousProject ( bool );
		void FindFirstLevel( void );
		void FindSecondLevel( UINT );
		void GetHeaderMCode ( void);
		void GetHeaderMCodeEx ( void);
		void SetHeaderMCode (HPROJECT, char *);
		void SetPBDMCode ( long,long);
		void ZeigeProject(void);
		void CreateORWindow ( short, short, short, long *, char *, short, short, short );
		long NumberTProjects ( void );
		TPRJTree *GetTPAktuell ( char *);

		void SetSightInformation ( void );
		int ReadProjectProFile ( void );

	// KK010115
		char * TRiASName(void) { return _pTRiNam; }
		BOOL	SetDQ(void );


	// KK 010521
		char * GetTempIni(void) { return _pIniTemp; };

		char * GetOriginalIni(void) { return _pIniOriginal; };
		void SetTempIniFile(char * pPath);
		bool GetTPUndef(void) { return 	m_bTPUndef;};
		void SetTPUndef(void) { m_bTPUndef = true;};
		bool isTempINI(void) { return 	m_isTempINI;};
		bool DuplicatTempIni(char *);


};

#endif 	// _TPROJECT_HXX
