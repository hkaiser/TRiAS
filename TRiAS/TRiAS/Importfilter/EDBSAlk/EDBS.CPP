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
//#include <TRiASHelper.h>

#include <istatus.h>		// Interfacedeklaration

#include "edbs.hpp"                  // zugeh. Header

#include "EDBS_Cfg.h"
#include "EDBS_CfgImp.h"

#include "import.hpp"
#include "trif.hpp"					// CTriasInterface
#include "objpool.hpp"

#include <xtsnguid.h>

#include <initguid.h>
#include "edbsguid.h"		// CLSID_EDBSImport

#include "version.h"
#include "resource.h"
#include "statguid.h"

#include "cxstring.h"
#include "MetaData.h"

#include <TRiASHelper_i.c>
#include "EDBS_Cfg_i.c"

//DEFINE_GUID(IID_ITRiASServiceProvider, 0x4F76AC35L, 0x98EF, 0x11D1, 0xBA, 0x12, 0x08, 0x00, 0x36, 0xD6, 0x38, 0x03);

class CEDBSExtension;

CObjektPool		*g_pObjektPool;
CTriasInterface	*g_pTriasInterface;
CMetaData		*g_pMetaData;

//#fje980727//=====================================================================
//#include "W:\Projekte\GeoCvt\GeometryConversionService.h"
//IArcConversion *g_pIArcConversion = NULL;
//BOOL m_fCOMinitialized = FALSE;	

// Variablen   :: wichtig für MFC-Anbindung !!!
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
//CTriasExtension *NewExtension (void)		// NEU: ohne Parameter
//{
//	CEDBSExtension	*g_pExt = NULL;
//	CString			GeoReinName;
//	
////	IID		dummy = IID_ITRiASServiceProvider;
//
//	TRY
//	{	g_pExt = new CEDBSExtension();	}
//	CATCH( CMemoryException, mce )
//	{	return NULL;	}
//	END_CATCH
//
////		GeoReinName.LoadString( IDS_GEOREINEXT );
////		if ( !GeoReinName.IsEmpty())
////			DEX_ExternalLoadExtension( (long)((const char*)GeoReinName));
//	
//	return g_pExt;
//}

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_EDBSImport, CEDBSExtension)
	OBJECT_ENTRY(CLSID_EDBS_CfgImp, CEDBS_CfgImp)
END_OBJECT_MAP()

_ATL_OBJMAP_ENTRY *GetObjectMap (void)
{
	return ObjectMap;		// ObjectMap liefern
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

BOOL GetTypeLibGUID (GUID &guidTLib)
{
	memcpy (&guidTLib, &LIBID_EDBS_CFGLib, sizeof (GUID));
	return true;		// TypeLib registrieren/deregistrieren
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
		bool fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_EDBSImport, 
				TEXT("TRiAS.EDBSALK.1"), IDS_LONGCLASSNAME,
				EDBSALKIMPORT_MAJORVERSION, EDBSALKIMPORT_MINORVERSION,
				EFUnLoadable|EFCanImport);

		if (!fSuccess)
			return false;

		UpdateEDBSRegistry( fRegister );

		return ExtOleRegisterImportClass (g_hInstance,
				CLSID_EDBSImport, TEXT("TRiAS.EDBSALK.1"),
				IDS_FORMATDESCRIPTION, IDS_DEFAULTEXTENSION);
	} else {
	// RegDB säubern

		UpdateEDBSRegistry( fRegister );
		
		return ExtOleUnregisterClass (CLSID_EDBSImport, 
					      TEXT("TRiAS.EDBSALK.1"));
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
CEDBSExtension :: CEDBSExtension()
				: CTriasExtension(), CImportEDBS()
{
//	m_pImport = NULL;
	UpdateEDBSRegistry(true);
	Configuration.Load();
	g_pMetaData = NULL;
//	g_pMetaData = new CMetaData;
//	g_pMetaData->pConfiguration = &this->Configuration;

}	// CEDBSExtension
#pragma warning (default: 4355)

// da wir ein zusõtzliches Interface dazugenommen haben, mu_ ein modifiziertes
// QueryInterface gegeben sein
//HRESULT CEDBSExtension :: QueryInterface (REFIID riid, LPVOID *ppvObj)
//{
//	if (riid == IID_IImportGeoData)
//		*ppvObj = m_pImport;	// ImportInterface liefern
//	else
//// alles andere überlassen wir der BasisKlassse
//		return CTriasExtension :: QueryInterface (riid, ppvObj);
//
//// AddRef nicht vergessen
//	LPUNKNOWN(*ppvObj) -> AddRef();
//
//	return NOERROR;
//}


//	Destruktion  ------------------------------------------------------
CEDBSExtension :: ~CEDBSExtension()
{
//	if( m_pImport ) {
//		delete m_pImport;
//		m_pImport = NULL;
//	}
	if( g_pMetaData ) {
		delete g_pMetaData;
		g_pMetaData = NULL;
	}

}	// ~CEDBSExtension


//	InitExtension  ----------------------------------------------------
STDMETHODIMP_(BOOL) CEDBSExtension :: InitExtension( short iMode )
{
	if (!CTriasExtension :: InitExtension (iMode))
		return false;

//	CxString	text;
//	text.GetPrivateProfileString( "Report", "Level", "", 255, "ALK.INI" );
//	if ( text.IsEmpty())
//		CreateIniFile();
//	m_pImport = new CImportEDBS (m_pUnk ? m_pUnk : this);

//#fje980727
//	m_fCOMinitialized = SUCCEEDED(CoInitialize(NULL));
//	if (!m_fCOMinitialized)
//		return FALSE;
//	return (NULL != m_pImport);
	return TRUE;
}	// InitExtension


//	UnLoadExtension  --------------------------------------------------
STDMETHODIMP_(BOOL) CEDBSExtension :: UnLoadExtension()
{
//#fje980727
//	if (NULL != g_pIArcConversion) {
//		g_pIArcConversion -> Release();
//		g_pIArcConversion = NULL;
//	}
//	if (m_fCOMinitialized)
//		CoUninitialize();
	return CTriasExtension :: UnLoadExtension();
}	// UnLoadExtension

//	SetDefaultStatusTexte  --------------------------------------------
void CEDBSExtension :: SetDefaultStatusTexte( const char *status1,
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
LPPROGRESSINDICATOR CEDBSExtension :: CreateStatusDialog()
{
 	m_pIStatus = NULL;
	HRESULT hr;

	if( NULL == m_pXtnSite )
		hr = CoCreateInstance(
			CLSID_ProgressIndicator,    //Class identifier (CLSID) of the object
			NULL,						//Pointer to controlling IUnknown
			CLSCTX_ALL ,		//Context for running executable code
			IID_IProgressIndicator,     //Reference to the identifier of the interface
			(LPVOID*)&m_pIStatus        //Address of output variable that receives 
										// the interface pointer requested in riid
			);
	else
		hr = m_pXtnSite -> CreateInstance (NULL, CLSID_ProgressIndicator, 
					IID_IProgressIndicator, (LPVOID*)&m_pIStatus);

	if( NULL != m_pIStatus ) {
		HWND	hNewWnd = m_pIStatus -> InitNew (__hWndM, 0L);

		if (NULL == hNewWnd) {
			m_pIStatus -> Release();
			m_pIStatus = NULL;
		}
	}
	return m_pIStatus;
}	// CreateStatusDialog

//	InitStatusDialog  -------------------------------------------------
HRESULT CEDBSExtension :: InitStatusDialog( const char *filename, ULONG filesize, const char *text )
{	HRESULT		hr = NOERROR;
	CString		txt;

	if ( m_pIStatus != NULL ) {	
		hr = m_pIStatus -> Restart (0L, filesize, PIFLAG_FILE|PIFLAG_FILENAME|
					PIFLAG_STATUS|PIFLAG_RESULT|
					PIFLAG_ADJUSTPERCENT|PIFLAG_INIT_SHOWWINDOW );
//					PIFLAG_ALL|PIFLAG_INIT_SHOWWINDOW);
		if (FAILED(hr))
			return hr;

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
void CEDBSExtension :: ChangeStatusText( const char *txt1, const char *txt2 )
{
	if (( txt1 != NULL ) && ( m_pIStatus != NULL ))
		m_pIStatus -> ChangeText (PIFLAG_ADJUSTPERCENT, txt1 );
	
	if (( txt2 != NULL ) && ( m_pIStatus != NULL ))
		m_pIStatus -> ChangeText (PIFLAG_RESULT, txt2 );
}	// ChangeStatusText

//	SetupStatus  ------------------------------------------------------
int CEDBSExtension :: SetupStatus( ULONG pos )
{	if( m_pIStatus != NULL )
		return m_pIStatus -> SetPosition( pos );
	else
		return 0;
}	// SetupStatus

//	ReleaseStatusDialog  ----------------------------------------------
void CEDBSExtension :: ReleaseStatusDialog()
{	
	if( m_pIStatus != NULL )
		m_pIStatus -> Release();
}	// ReleaseStatusDialog

//	NutzerAbbruch  ----------------------------------------------------
bool CEDBSExtension :: NutzerAbbruch()
{
	bool result = false;
	if ( m_pIStatus != NULL )
		result = m_pIStatus -> WasCanceled();
	return result;
}	// NutzerAbbruch

//	ResetAbbruch  -----------------------------------------------------
void CEDBSExtension :: ResetAbbruch()
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
		name += "EDBSALK.INI";

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

//void CEDBSExtension::CreateIniFile()
//{
//	CFile	file;
//	CFileException  e;
//	HRSRC	hRes; // resource handle to INI-file
//	HGLOBAL hData;
//	HINSTANCE	hInst;
//	DWORD   size;
//	CString name;
//	char	*txt;
//	UINT	len;
//	void    *ptr;
//	BOOL    bOk = FALSE;
//	BOOL    bOpen = FALSE;
//
//	if ( hInst = AfxFindResourceHandle( "IDR_INIFILE2", "INIFILE" ))
//		if (( hRes = ::FindResource( hInst, "IDR_INIFILE2", "INIFILE" )) != NULL &&
//			( hData = ::LoadResource( hInst, hRes)) != NULL)
//	{
//		// Ermitteln Dateiname
//		txt = name.GetBuffer( 1024 );
//		len = ::GetWindowsDirectory( txt, 1023 );
//		txt[len] = '\0';
//		name.ReleaseBuffer();
//		if (( name[name.GetLength() - 1] != '/' ) &&
//			( name[name.GetLength() - 1] != '\\' ))
//			name += '/';
//		name += "EDBSALK.INI";
//
//		if ( !name.IsEmpty())
//		{
//			ptr  = ::LockResource( hData );
//			size = ::SizeofResource( AfxGetResourceHandle(), hRes );
//			if ( !file.Open( name, CFile::modeWrite|CFile::modeCreate|CFile::shareExclusive, &e ))
//			{
//				#ifdef _DEBUG
//				afxDump << "Datei " << name << " kann nicht geöffnet werden. " << e.m_cause << "\n";
//				#endif
//			}
//			else
//			{
//				file.WriteHuge( ptr, size );
//				file.Close();
//			}
//			FreeResource(hData);
//
//	}	}
//}
