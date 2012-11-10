///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			edbs.hpp
//
//	Stand:			15.11.1994
//	Beschreibung:	Extension-Objekt
//	Entwicklung:	15.11.94	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#ifndef	_EDBS_HPP
#define	_EDBS_HPP

// #include	<xtsnmfc.hpp>
//#include	"edbsfo.hpp"
//#include	"aboutdlg.hpp"
//#include	"setupdlg.hpp"
#include "import.hpp"

class	CEDBSExtension : public CTriasExtension
{
private:
	CImportEDBS		*m_pImport;
	LPPROGRESSINDICATOR	m_pIStatus;
	CString			m_strStatDatei;
	CString			m_strStatDateiName;
	CString			m_strStatusText1;
	CString			m_strStatusText2;

protected:
	void CreateIniFile();
	// überladene Funktionen der Basisklasse

	STDMETHOD (QueryInterface)(THIS_ REFIID riid, LPVOID *ppvObj );
	
	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);

public:
	IUnknown *get_CS() const { return m_pImport->get_CS(); }

public:
				CEDBSExtension();
				~CEDBSExtension();
//	SetDefaultStatusTexte  --------------------------------------------
void	SetDefaultStatusTexte( const char* = NULL, const char* = NULL,
				const char* = NULL, const char* = NULL );
//	CreateStatusDialog  -----------------------------------------------
LPPROGRESSINDICATOR CreateStatusDialog();
//	InitStatusDialog  -------------------------------------------------
HRESULT InitStatusDialog( const char*, ULONG, const char* );
//	ChangeStatusText  -------------------------------------------------
void ChangeStatusText( const char*, const char* );
//	SetupStatus  ------------------------------------------------------
int SetupStatus( ULONG );
//	ReleaseStatusDialog  ----------------------------------------------
void	ReleaseStatusDialog();
//	NutzerAbbruch  ----------------------------------------------------
BOOL	NutzerAbbruch(UINT uiResId = 0);
//	ResetAbbruch  -----------------------------------------------------
void	ResetAbbruch();
};

#endif	// _EDBS_HPP
