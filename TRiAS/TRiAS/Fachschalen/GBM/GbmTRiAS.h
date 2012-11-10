// GbmTRiAS.h : main header file for the GBMTRIAS DLL
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <bool.h>
#include "resource.h"		// main symbols
//#include <triastlb.h>

/////////////////////////////////////////////////////////////////////////////
// CGbmTRiASExtension
// See GbmTRiAS.cpp for the implementation of this class
//

class CDatenListeDlg;
class CTestDialogBar;
//class CGbmControlBar;

class CGbmTRiASExtension : public CTriasExtension
{
	static ULONG	m_RegNoti[];
	static ULONG	m_RegWinNoti[];
	BOOL			m_bServerIsClosing;
	BOOL			m_bIntegratedProjekt;
	short			m_iOISY;

//	CDatabase*		m_pDatabase;
	CTriDBSet*		m_pSetTriDB;
	CVerzSet*		m_pSetVerz;
	COrteSet*		m_pSetOrte;
	CStrasseSet*	m_pSetStrasse;

//-----------Basic-----------------------------
	IExtendBScript	*m_pScript;
//-------------------------------------------
//	_DDocument		*m_pDoc;
	CObjectProperties*	m_pObjProp;

protected:
	void EditVorlagen();
	HRESULT RemoveGBMToolBar();
	HRESULT CreateGBMToolBar();
	BOOL m_bUseProjectManager;
	void ExecuteBasicScriptLoc( const char*, const char* );
	void ExecuteBasicScript( const char*, const char* );
	void ExecuteBasicScriptRes( UINT, const char* );
	void ExecuteBasicScript( int );
	void Visualisierung();
	CStringArray m_strarrZusatzFktPro;
	void InitZusatzFunktionen( BOOL );
	void ZusatzFkt();
	CStringArray m_strarrZusatzFkt;
	int m_iVerzNr;
	void NeueIDE();
	void EditIDE();
	BOOL m_bProcessPrinting;
	void OnBeitragBerechnen();
	void OnTiefenbegrenzung();
	void OnFlaechenberechnung();
	BOOL PreparePrintAnlage( BOOL = TRUE );
	void OnPrint();
	CStringArray m_arrPrintList;
	void PreparePrintListe( CStringArray*, const char*, int, int, BOOL );
	void OnPrintPreview();
	short IstProjektIntegriert( const char* );
	void OnProjektOpen();
	void OnAbout();
	LRESULT OpenProjektWiz();
//	CSetNF_PG1* m_pSetNF_PG1;
	LRESULT IncludeProjekt();
	void CloseProjektCleanup();
	void ObjectSelected( long onr );
	void AddObject( long onr );
	void UpdateORWnd( HWND wnd, BOOL add );
	bool SwitchDatenListeDlg( bool zwang = false, bool visible = true );
	CDatenListeDlg *m_pDatenListeDlg;
	void UnregisterNotifications();
	void RegisterNotifications();
	// überladene Funktionen der Basisklasse

	STDMETHOD (QueryInterface)(THIS_ REFIID riid, LPVOID *ppvObj );

	STDMETHOD_(bool, InitExtension) (THIS_ short iMode);
	STDMETHOD_(bool, UnLoadExtension) (THIS);
	STDMETHOD_(bool, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(bool, MenuSelect) (THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd);
	STDMETHOD_(bool, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);
	STDMETHOD_(LRESULT, WindowsNotification) (THIS_ UINT wMsg, WPARAM wParam, 
						  LPARAM lParam);
	STDMETHOD_(LRESULT, GetCapabilities) (THIS_ UINT uiCap);

public:
	void RewriteModifications();
	int CommandToCheck( UINT );
	bool m_bInitialisiert;
	void ExecCommand( UINT );
	bool CommandToEnable( UINT );
	void PrepareVisu( const char*, const char*, const char*, COLORREF );
	void ExecBasicScriptParam( UINT, const char*, const char* );
	CString GetTRiASPfad();
	CString GetDefaultDBName();
	CMapStringToString* m_pmapStrassen;
	CStringArray m_arrOrte;
	CString OrtVonIDE( const char* );
	CString StrasseVonIDE( const char* );
	LRESULT StartupProc( WPARAM wParam, LPARAM lParam );
	CGbmTRiASExtension();
	~CGbmTRiASExtension();
private:
//	CGbmControlBar* m_pTestBar;
	BOOL m_bIntegrierbar;
	CSetNF_PG3* m_pNF_PG3;
//	CSetNF_PG2H* m_pNF_PG2H;
//	CSetNF_PG2D* m_pNF_PG2D;
//	CSetNF_PG1GB* m_pNF_PG1GB;
	CSetNF_PG1FL* m_pNF_PG1FL;
//	CSetNF_PG1* m_pNF_PG1;
};

/////////////////////////////////////////////////////////////////////////////
//	TRiAS - Funktionen
/////////////////////////////////////////////////////////////////////////////

void GetActiveProject( CString &name );
void OISY2String( double oisy, CString &strOISY );
void ISY2String( double oisy, double isy, CString &strISY );
short String2OISY( const char* );
short String2ISY( short, const char* );
void OISY2String2( double oisy, CString &strOISY );

BOOL IDEfromONr( long onr, CString& ide );
BOOL IstGrundstueck( long onr );
BOOL IstGebaeude( long onr );
BOOL IstDachteilflaeche( long onr );
BOOL IstHofflaeche( long onr );

CString GetVorlageFileName( char c );

/////////////////////////////////////////////////////////////////////////////
