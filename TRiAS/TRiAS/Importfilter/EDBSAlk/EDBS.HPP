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

// Lizensierung
#if defined(_DEBUG)
extern "C" bool g_fGlobalLic;
#else
#define g_fGlobalLic false
#endif // defined(_DEBUG)

class CMyLicense
{
protected:
	static BOOL VerifyLicenseKey(BSTR bstr)
	{
	CComBSTR bstrKey;

		USES_CONVERSION;
		if ((GetLicenseKey (0, &bstrKey) && !wcscmp (bstrKey, bstr)) || ::SetLicensed (OLE2A(bstr)))
		{
			return TRUE;
		}
		return FALSE;
	}

	static BOOL GetLicenseKey (DWORD, BSTR *pBstr) 
	{
	CComBSTR bstrKey (_MAX_PATH, (LPCOLESTR)NULL);

		if (!::GetLicenseKey (bstrKey.m_str, _MAX_PATH))
			return FALSE;

		*pBstr = bstrKey.Detach(); 
		return TRUE;
	}

	static BOOL IsLicenseValid() { return g_fGlobalLic || ::GetLicensed(); }
};

// #include	<xtsnmfc.hpp>
//#include	"edbsfo.hpp"
//#include	"aboutdlg.hpp"
//#include	"setupdlg.hpp"
#include "import.hpp"
#include <xtsnguid.h>
#include "Cfg.h"

enum nArtObjektIdent	{
	_Gerade = 11,
	_Geradenschar = 12,
	_Polygonzug = 15,
	_Kreisbogen_rechts = 21,
	_Kreisbogen_links = 22,
	_Kurve = 41,
	_EinzelpunktInStandardausrichtung  = 51,
	_PunkthaufenRepraesentant = 52,
	_EinzelpunktInBesondererAusrichtung = 53,
	_Flaechendefinition = 91,
	_Liniendefinition = 92
};

EXTERN_C const GUID CLSID_EDBSImport;

///////////////////////////////////////////////////////////////////////////////
// Eigentliche Erweiterung
class	CEDBSExtension : 
	public CTriasExtension,
	public CImportEDBS,
	public CComCoClass<CEDBSExtension, &CLSID_EDBSImport>
{
private:
//	CImportEDBS		*m_pImport;
	LPPROGRESSINDICATOR	m_pIStatus;
	CString			m_strStatDatei;
	CString			m_strStatDateiName;
	CString			m_strStatusText1;
	CString			m_strStatusText2;

protected:
//	void CreateIniFile();
	// überladene Funktionen der Basisklasse

//	STDMETHOD (QueryInterface)(THIS_ REFIID riid, LPVOID *ppvObj );
	
	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);

public:
	CEDBSExtension();
	~CEDBSExtension();
	
	BEGIN_COM_MAP(CEDBSExtension)
		COM_INTERFACE_ENTRY(IImportGeoData)				// aus CImportGeoData
		COM_INTERFACE_ENTRY(IImportGeoDataSelectCS)		// aus CImportGeoData
		COM_INTERFACE_ENTRY_CHAIN(CTriasExtension)
	END_COM_MAP()

	DECLARE_NO_REGISTRY()
	DECLARE_NOT_AGGREGATABLE_SINGLE(CEDBSExtension, g_pTE)
	DECLARE_CLASSFACTORY2(CMyLicense)

	CCfg	Configuration;

// SetDefaultStatusTexte 
	void	SetDefaultStatusTexte( const char* = NULL, const char* = NULL,
					const char* = NULL, const char* = NULL );
// CreateStatusDialog
	LPPROGRESSINDICATOR CreateStatusDialog();
// InitStatusDialog 
	HRESULT InitStatusDialog( const char*, ULONG, const char* );
// ChangeStatusText
	void ChangeStatusText( const char*, const char* );
// SetupStatus 
	int SetupStatus( ULONG );
// ReleaseStatusDialog  
	void	ReleaseStatusDialog();
// NutzerAbbruch  
	bool	NutzerAbbruch();
// ResetAbbruch  
	void	ResetAbbruch();
};

#endif	// _EDBS_HPP
