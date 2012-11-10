///////////////////////////////////////////////////////////////////////
//	TRiAS - Erweiterung: EDBS - Import
///////////////////////////////////////////////////////////////////////
//	Datei:			edbs.cpp
//
//	Stand:			15.11.1994
//	Beschreibung:	Extension-Objekt
//	Entwicklung:	15.11.94	Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <TRiASHelper.h>

#include <istatus.h>		// Interfacedeklaration

#include "edbs.hpp"                  // zugeh. Header

#include "import.hpp"
//#include "trif.hpp"					// CTriasInterface
#include "objpool.hpp"

#include <xtsnguid.h>

#include <initguid.h>
#include "edbsguid.h"		// CLSID_EDBSImport

#include "version.h"
#include "resource.h"
#include "statguid.h"

#include "cxstring.h"
#include "trif.hpp"

#include <TRiASHelper_i.c>

DEFINE_GUID(IID_ITRiASServiceProvider, 0x4F76AC35L, 0x98EF, 0x11D1, 0xBA, 0x12, 0x08, 0x00, 0x36, 0xD6, 0x38, 0x03);

class CEDBSExtension;
BOOL	g_bKurzeIdents;
short	g_iKoordFormat;
BOOL	g_bKoordTauschen;

extern class CTriasInterface*	g_pTriasInterface;

// Variablen  ::wichtig für MFC-Anbindung !!!
/*
CEDBSExtension*		g_pCEDBSExtension;
CTriasInterface*	g_pTriasInterface;
CObjektPool*		g_pObjektPool;

extern CTriasExtension* g_pTE;
*/

#ifdef	WIN16
static CExtDLL NEAR MyExtension( "edbsimp.ext" );       // für MFC-Anbindung benötigt
														// als Argument den Namen der DLL angeben
#endif

//
// Die folgende Funktion muß vom Nutzer bereitgestellt werden und lediglich
// ein Objekt vom konkreten ErweiterungTyp anlegen. Diese Funktion ist notwendig,
// da keine virtuellen Konstruktoren erlaubt sind.
//
CTriasExtension *NewExtension (void)		// NEU: ohne Parameter
{
	CEDBSExtension	*g_pExt = NULL;
	CString			GeoReinName;
	
	TRY
	{	g_pExt = new CEDBSExtension();	}
	CATCH( CMemoryException, mce )
	{	return NULL;	}
	END_CATCH

//		GeoReinName.LoadString( IDS_GEOREINEXT );
//		if ( !GeoReinName.IsEmpty())
//			DEX_ExternalLoadExtension( (long)((const char*)GeoReinName));
	
	return g_pExt;
}

//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
// Bitte beachten: JEDE Erweiterung muß ihren eigenen ClassID haben. Dieser ID
// kann mit dem Tool GENGUID.EXE generiert werden. 
//
BOOL GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
	memcpy (&rClsID, &CLSID_EDBSImport, sizeof (GUID));
	return true;
}


//
// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll (empfohlen!!).
// Der ProgID (hier 'TRiAS.Simple.1') ist eine ZeichenKette, die die Erweiterung
// in der RegDB repräsentiert. Das Format sollte beibehalten werden. Die '... .1'
// steht für die VersionsNummer.
// Der KlassenName (hier die Stringresource hinter IDS_LONGCLASSNAME) ist eine 
// normal-lesbare Zeichenkette, die lokalisiert wird (deshalb in der Resource) und
// die Bezeichnung der Erweiterung definiert.
//
BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
		BOOL fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_EDBSImport, 
				TEXT("TRiAS.EDBSImport.1"), IDS_LONGCLASSNAME,
				EDBSIMPORT_MAJORVERSION, EDBSIMPORT_MINORVERSION,
				EFUnLoadable|EFCanImport);
		if (!fSuccess) return false;

		return ExtOleRegisterImportClass (g_hInstance,
				CLSID_EDBSImport, TEXT("TRiAS.EDBSImport.1"),
				IDS_FORMATDESCRIPTION, IDS_DEFAULTEXTENSION);
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_EDBSImport, 
					      TEXT("TRiAS.EDBSImport.1"));
	}
	return true;	// alles ok
}


// NEU: Die Funktion void DeleteExtension (CTriasExtension *pTE) muß nicht mehr
// zur Verfügung gestellt werden. Die Destruktoren sind 'virtual', so daß auch so
// alles sauber aufgeräumt werden kann.
//void DeleteExtension( CTriasExtension *pTE )
//{
//	ASSERT( pTE != NULL );
//	delete (CEDBSExtension*)pTE;
//}

/**********************************************************************
 *	CEDBSExtension
 *********************************************************************/
#pragma warning (disable: 4355)

//	Konstruktion  -----------------------------------------------------
CEDBSExtension::CEDBSExtension()
	: CTriasExtension()
{
	m_pImport = NULL;
	g_bKurzeIdents = TRUE;
	g_iKoordFormat = 0;
	g_bKoordTauschen = FALSE;
}	// CEDBSExtension
#pragma warning (default: 4355)

// da wir ein zusõtzliches Interface dazugenommen haben, mu_ ein modifiziertes
// QueryInterface gegeben sein
HRESULT CEDBSExtension::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IImportGeoData)
		*ppvObj = (IImportGeoData *)m_pImport;	// ImportInterface liefern
	else if (riid == IID_IImportGeoDataSelectCS)
		*ppvObj = (IImportGeoDataSelectCS *)m_pImport;
	else
// alles andere überlassen wir der BasisKlassse
		return CTriasExtension::QueryInterface (riid, ppvObj);

// AddRef nicht vergessen
	LPUNKNOWN(*ppvObj) -> AddRef();

	return NOERROR;
}


//	Destruktion  ------------------------------------------------------
CEDBSExtension::~CEDBSExtension()
{
	if (NULL != m_pImport) {
		delete m_pImport;
		m_pImport = NULL;
	}
}	// ~CEDBSExtension


//	InitExtension  ----------------------------------------------------
STDMETHODIMP_(BOOL) CEDBSExtension::InitExtension( short iMode )
{
	if (!CTriasExtension::InitExtension (iMode))
		return false;

	m_pImport = CImportEDBS::CreateInstance(m_pUnk ? m_pUnk : this);
	if (NULL == m_pImport)
		return FALSE;

	_ASSERTE(NULL != g_pTriasInterface);
	
CxString text;

	text.GetPrivateProfileString( "Report", "Level", "", 255, g_pTriasInterface->GetIniFileName());
	if ( text.IsEmpty())
		CreateIniFile();

	return TRUE;
}	// InitExtension


//	UnLoadExtension  --------------------------------------------------
STDMETHODIMP_(BOOL) CEDBSExtension::UnLoadExtension()
{	
	return CTriasExtension::UnLoadExtension();
}	// UnLoadExtension

//	SetDefaultStatusTexte  --------------------------------------------
void CEDBSExtension::SetDefaultStatusTexte( const char *status1,
		const char *status2, const char *filename, const char *file )
{
	if ( file )	m_strStatDatei = file;
	else		m_strStatDatei.Empty();
	if ( filename )	m_strStatDateiName = filename;
	else		m_strStatDateiName.Empty();
	if ( status1 )	m_strStatusText1 = status1;
	else		m_strStatusText1.Empty();
	if ( status2 )	m_strStatusText2 = status2;
	else		m_strStatusText2.Empty();
}	// SetDefaultStatusTexte

//	CreateStatusDialog  -----------------------------------------------
LPPROGRESSINDICATOR CEDBSExtension::CreateStatusDialog()
{
	m_pIStatus = NULL;
	HRESULT hr = m_pXtnSite -> CreateInstance (NULL, CLSID_ProgressIndicator, 
					IID_IProgressIndicator, (LPVOID*)&m_pIStatus);

	if (FAILED(hr)) return NULL;

	HWND	hNewWnd = m_pIStatus -> InitNew (__hWndM, 0L);

        if (NULL == hNewWnd)
        {
		m_pIStatus -> Release();
		m_pIStatus = NULL;
        	return NULL;
	}

	return m_pIStatus;
}	// CreateStatusDialog

//	InitStatusDialog  -------------------------------------------------
HRESULT CEDBSExtension::InitStatusDialog( const char *filename, ULONG filesize, const char *text )
{	HRESULT		hr = NOERROR;
	CString		txt;

	if ( m_pIStatus != NULL )
	{	
		hr = m_pIStatus -> Restart (0L, filesize, PIFLAG_FILE|PIFLAG_FILENAME|
					PIFLAG_STATUS|PIFLAG_RESULT|
					PIFLAG_ADJUSTPERCENT|PIFLAG_INIT_SHOWWINDOW );
//					PIFLAG_ALL|PIFLAG_INIT_SHOWWINDOW);
		if (FAILED(hr)) return hr;

// diverse Text initialisieren
		txt = "Status des aktuellen Imports";
		m_pIStatus -> ChangeText (PIFLAG_CAPTION, txt );
		if ( !m_strStatDatei.IsEmpty())
			m_pIStatus -> ChangeText (PIFLAG_FILE, m_strStatDatei );

		if ( filename )
			m_pIStatus -> ChangeText (PIFLAG_FILENAME, filename );
		else
			if ( !m_strStatDateiName.IsEmpty())
				m_pIStatus -> ChangeText (PIFLAG_FILENAME, m_strStatDateiName );

		if ( text )
			m_pIStatus -> ChangeText (PIFLAG_ADJUSTPERCENT, text );
		else
			if ( !m_strStatusText1.IsEmpty())
				m_pIStatus -> ChangeText (PIFLAG_ADJUSTPERCENT, m_strStatusText1 );

		if ( !m_strStatusText2.IsEmpty())
			m_pIStatus -> ChangeText (PIFLAG_RESULT, m_strStatusText2 );

	}
	return hr;
}	// InitStatusDialog

//	ChangeStatusText  -------------------------------------------------
void CEDBSExtension::ChangeStatusText( const char *txt1, const char *txt2 )
{
	if (( txt1 != NULL ) && ( m_pIStatus != NULL ))
	{
		m_pIStatus -> ChangeText (PIFLAG_ADJUSTPERCENT, txt1 );
	}
	if (( txt2 != NULL ) && ( m_pIStatus != NULL ))
		m_pIStatus -> ChangeText (PIFLAG_RESULT, txt2 );
}	// ChangeStatusText

//	SetupStatus  ------------------------------------------------------
int CEDBSExtension::SetupStatus( ULONG pos )
{	
	if ( m_pIStatus != NULL ) 
		return m_pIStatus -> SetPosition( pos );
	return 0;
}	// SetupStatus

//	ReleaseStatusDialog  ----------------------------------------------
void CEDBSExtension::ReleaseStatusDialog()
{	if ( m_pIStatus != NULL )
		m_pIStatus -> Release();
}	// ReleaseStatusDialog

//	NutzerAbbruch  ----------------------------------------------------
BOOL CEDBSExtension::NutzerAbbruch(UINT uiResId)
{
BOOL result = FALSE;

	if (m_pIStatus != NULL)
		result = m_pIStatus -> WasCanceled();

	if (result) {
		if (0 != uiResId && AfxMessageBox(uiResId, MB_ICONQUESTION | MB_YESNO) != IDYES) {
			result = FALSE;		// doch nicht abbrechen
			ResetAbbruch();
		}
	}
	return result;
}	// NutzerAbbruch

//	ResetAbbruch  -----------------------------------------------------
void CEDBSExtension::ResetAbbruch()
{
	if ( m_pIStatus != NULL )
		m_pIStatus -> Restart (0L, 0L, PIFLAG_RESETCANCEL );
}	// ResetAbbruch

/*
	CFile	file;
	CFileException  e;
	HRSRC	hRes; // resource handle to INI-file
	HGLOBAL hData;
	DWORD   size;
	CString name;
	char	*txt;
	UINT	len;
	void    *ptr;
	BOOL    bOk = FALSE;
	BOOL    bOpen = FALSE;

	if (( hRes = ::FindResource( AfxGetResourceHandle(), (LPCSTR)IDR_INIFILE2, "INIFILE" )) != NULL &&
		( hData = ::LoadResource( AfxGetResourceHandle(), hRes)) != NULL)
	{
		// Ermitteln Dateiname
		txt = name.GetBuffer( 1024 );
		len = ::GetWindowsDirectory( txt, 1023 );
		txt[len] = '\0';
		name.ReleaseBuffer();
		if (( name[name.GetLength() - 1] != '/' ) &&
			( name[name.GetLength() - 1] != '\' ))
			name += '//';
		name += "EDBS.INI";

		if ( !name.IsEmpty())
		{
			ptr  = ::LockResource( hData );
			size = ::SizeofResource( AfxGetResourceHandle(), hRes );
			if ( !file.Open( name, CFile::modeWrite|CFile::modeCreate|CFile::shareExclusive, &e ))
			{
				#ifdef _DEBUG
				afxDump << "Datei " << name << " kann nicht geöffnet werden. " << e.m_cause << "\n";
				#endif
			}
			else
			{
				file.WriteHuge( ptr, size );
				file.Close();
			}
			FreeResource(hData);

	}	}


*/

void CEDBSExtension::CreateIniFile()
{
	CFile	file;
	CFileException  e;
	HRSRC	hRes; // resource handle to INI-file
	HGLOBAL hData;
	HINSTANCE	hInst;
	DWORD   size;
	CString name;
	char	*txt;
	UINT	len;
	void    *ptr;
	BOOL    bOk = FALSE;
	BOOL    bOpen = FALSE;

	if ( hInst = AfxFindResourceHandle( "IDR_INIFILE2", "INIFILE" ))
		if (( hRes = ::FindResource( hInst, "IDR_INIFILE2", "INIFILE" )) != NULL &&
			( hData = ::LoadResource( hInst, hRes)) != NULL)
	{
		// Ermitteln Dateiname
		txt = name.GetBuffer( 1024 );
		len = ::GetWindowsDirectory( txt, 1023 );
		txt[len] = '\0';
		name.ReleaseBuffer();
		if (( name[name.GetLength() - 1] != '/' ) &&
			( name[name.GetLength() - 1] != '\\' ))
			name += '/';
		name += "EDBS.INI";

		if ( !name.IsEmpty())
		{
			ptr  = ::LockResource( hData );
			size = ::SizeofResource( hInst, hRes );
			if ( !file.Open( name, CFile::modeWrite|CFile::modeCreate|CFile::shareExclusive, &e ))
			{
				#ifdef _DEBUG
				afxDump << "Datei " << name << " kann nicht geöffnet werden. " << e.m_cause << "\n";
				#endif
			}
			else
			{
				file.WriteHuge( ptr, size );
				file.Close();
			}
			FreeResource(hData);

	}	}
}
