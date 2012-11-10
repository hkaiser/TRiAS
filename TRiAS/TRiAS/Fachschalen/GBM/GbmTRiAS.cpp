///////////////////////////////////////////////////////////////////////
//      TRiAS - Erweiterung: GBM-Kopplung
///////////////////////////////////////////////////////////////////////
//      Datei:                  GbmTRiAS.cpp
//
//      Stand:                  07.04.1997
//      Beschreibung:   Extension-Objekt
//      Entwicklung:    07.04.94        Beginn der Kodierung
//////////////////////////////////////////////////////////////////////

#include "bool.h"
#include "stdafx.h"
#include <TRiASHelper.h>

#include <istatus.h>			// Interfacedeklaration
#include <IToolbar.h>

#include "GbmTRiAS.h"

#include <xtsnguid.h>

#include <initguid.h>
#include "gbmguid.h"			// CLSID_EDBSImport

#include "version.h"
#include "resource.h"
#include "statguid.h"
#include "toolguid.h"

#include "ResiWnd.h"
#include "OpProDlg.h"
#include "DLDlg.h"

#include "MyPropS.h"
#include "SPage1.h"
#include "SPage2.h"
#include "about.h"

#include "PrintAnlaDialog.h"
#include "DlgSelPrint.h"
#include <AfxPriv.h>

#include "PrintAnlage.h"
#include "PreviewDialog.h"
#include "PrintHandler.h"

#include "DlgTB.h"
#include "DlgVisu.h"

#include "InterDialog.h"
#include "ODBCInst.h"

#include "FlAbgleichDlg.h"
#include "EditIDEDlg.h"
#include "DlgZFkt.h"
#include "DlgEditVorlage.h"

#include "SetVorlagen.h"

#include <TRiASHelper_i.c>

#include "RegKey.h"

#include <itoolbar.h>
#include <triastlb.h>
#include <dirisole.h>
#include <xtsnguid.h>

extern CComModule _Module;

#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)
#include <ospace/std/map>		// STL related stuff
#include "AuxUIOwner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class CGbmTRiASExtension;
UINT g_iGSTeilenMsg = 0;

CDatabase* g_pDatabase;

CTriDBSet* g_pSetTriDB;
CStrasseSet* g_pSetStrasse;
COrteSet* g_pSetOrte;
CSetNF_PG1* g_pNF_PG1;

CSetNF_PG2H* g_pNF_PG2H;
CSetNF_PG2D* g_pNF_PG2D;
CSetNF_PG1GB* g_pNF_PG1GB;
CSetNF_PG4* g_pNF_PG4;

CGbmTRiASExtension	*g_pExt;

COPAngeschlGS*		g_pOPAngeschlGS;
COPBeitragsartGS*	g_pOPBeitragsartGS;
COPEigentumGS*		g_pOPEigentumGS;
COPGedrucktGS*		g_pOPGedrucktGS;
COPGedrucktGS*		g_pOPGedruck2GS;

COP_AGGS*			g_pOP_AGGS;
COP_FLG*			g_pOP_FLG;
COP_GEFS*			g_pOP_GEFS;
COP_TIEB*			g_pOP_TIEB;
COP_KAT*			g_pOP_KAT;
COP_FLN*			g_pOP_FLN;
COP_TIEF*			g_pOP_TIEF;

ULONG g_ulOPAngeschlGS = 0L;
ULONG g_ulOPBeitragsartGS = 0L;
ULONG g_ulOPEigentumGS = 0L;
ULONG g_ulOPGedrucktGS = 0L;
ULONG g_ulOPGedruck2GS = 0L;
ULONG g_ulOP_AGGS = 0L;
ULONG g_ulOP_FLG = 0L;
ULONG g_ulOP_GEFS = 0L;
ULONG g_ulOP_TIEB = 0L;
ULONG g_ulOP_KAT = 0L;
ULONG g_ulOP_FLN = 0L;
ULONG g_ulOP_TIEF = 0L;

int		g_iMessageStatus;
BOOL	g_bHandleGSTeilen;

extern CSetVorlagen *g_pSetVorlagen;

//
// Die folgende Funktion muß vom Nutzer bereitgestellt werden und lediglich
// ein Objekt vom konkreten ErweiterungTyp anlegen. Diese Funktion ist notwendig,
// da keine virtuellen Konstruktoren erlaubt sind.
//
CTriasExtension *NewExtension (void)            // NEU: ohne Parameter
{
	g_pExt = NULL;

	TRY
	{
		g_pExt = new CGbmTRiASExtension();
	}
	CATCH( CMemoryException, mce )
	{
		return NULL;
	}
	END_CATCH

	g_iGSTeilenMsg = ::RegisterWindowMessage( "GBM-TRiAS-GS-Teilen" );
	return g_pExt;
}

//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden.
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID
// dieser Erweiterung.
// Bitte beachten: JEDE Erweiterung muß ihren eigenen ClassID haben. Dieser ID
// kann mit dem Tool GENGUID.EXE generiert werden.
//
bool GetExtensionCLSID (CLSID &rClsID)  // Liefert CLSID
{
	memcpy (&rClsID, &CLSID_GBMKopplung, sizeof (GUID));
	return true;
}

//
// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung
// sich selbst in der RegDB registrieren soll (empfohlen!!).
// Der ProgID (hier 'TRiAS.Simple.1') ist eine ZeichenKette, die die Erweiterung
// in der RegDB repräsentiert. Das Format sollte beibehalten werden. Die '....1'
// steht für die VersionsNummer.
// Der KlassenName (hier die Stringresource hinter IDS_LONGCLASSNAME) ist eine
// normal-lesbare Zeichenkette, die lokalisiert wird (deshalb in der Resource) und
// die Bezeichnung der Erweiterung definiert.
//
bool UpdateRegistry (bool fRegister)    // RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister)
	{
	// RegDB initialisieren
		bool fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_GBMKopplung,
				TEXT("TRiAS.GBMKopplung.1"), IDS_LONGCLASSNAME,
				GBMKOPPLUNG_MAJORVERSION, GBMKOPPLUNG_MINORVERSION,
				EFPreLoad |		// soll automatische geladen werden
				EFUnLoadable |	// darf entladen werden
				EFVisible		// darf optional geladen werden
				);

		if (!fSuccess) return false;
	}
	else
	{
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_GBMKopplung,
				TEXT("TRiAS.GBMKopplung.1"));
	}

	return true;	// alles ok
}


/////////////////////////////////////////////////////////////////////////////
// CGbmTRiASExtension

#pragma warning (disable: 4355)

//      Konstruktion  -----------------------------------------------------
CGbmTRiASExtension :: CGbmTRiASExtension()
	: CTriasExtension( EXTENSIONMENU )
{
	m_bInitialisiert = false;

	m_bServerIsClosing = FALSE;
	m_bIntegratedProjekt = FALSE;
	m_bIntegrierbar = FALSE;
	m_iOISY = -1;

	m_pObjProp = NULL;
	g_pOPAngeschlGS = NULL;
	g_pOPBeitragsartGS = NULL;
	g_pOPEigentumGS = NULL;
	g_pOPGedrucktGS = NULL;
	g_pOPGedruck2GS = NULL;

	g_pOP_AGGS = NULL;
	g_pOP_FLG = NULL;
	g_pOP_GEFS = NULL;
	g_pOP_TIEB = NULL;
	g_pOP_KAT = NULL;
	g_pOP_FLN = NULL;
	g_pOP_TIEF = NULL;

	g_ulOPAngeschlGS = 0L;
	g_ulOPBeitragsartGS = 0L;
	g_ulOPEigentumGS = 0L;
	g_ulOPGedrucktGS = 0L;
	g_ulOPGedruck2GS = 0L;
	g_ulOP_AGGS = 0L;
	g_ulOP_FLG = 0L;
	g_ulOP_GEFS = 0L;
	g_ulOP_TIEB = 0L;
	g_ulOP_KAT = 0L;
	g_ulOP_FLN = 0L;
	g_ulOP_TIEF = 0L;

	g_pDatabase = NULL;
	m_pSetTriDB = NULL;
	m_pSetVerz = NULL;
	m_pSetOrte = NULL;
	m_pSetStrasse = NULL;

	g_pSetTriDB   = NULL;
	g_pSetOrte    = NULL;
	g_pSetStrasse = NULL;
	g_pNF_PG1     = NULL;

	g_pNF_PG2H    = NULL;
	g_pNF_PG2D    = NULL;
	g_pNF_PG1GB   = NULL;
	g_pNF_PG4     = NULL;

	g_iMessageStatus = 0;
	g_bHandleGSTeilen = FALSE;

//	m_pNF_PG1   = NULL;
	m_pNF_PG1FL = NULL;
//	m_pNF_PG1GB = NULL;
//	m_pNF_PG2D  = NULL;
//	m_pNF_PG2H  = NULL;
	m_pNF_PG3   = NULL;

	m_pDatenListeDlg = NULL;
	m_pScript = NULL;

//	m_pTestBar = NULL;
	m_bProcessPrinting = FALSE;
	m_bUseProjectManager = TRUE;
}	// CGbmTRiASExtension

#pragma warning (default: 4355)

// da wir ein zusätzliches Interface dazugenommen haben, muß ein modifiziertes
// QueryInterface gegeben sein
HRESULT CGbmTRiASExtension :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IObjectProps)
		*ppvObj = m_pObjProp;	// ObjectProperties liefern
	else
		return CTriasExtension :: QueryInterface (riid, ppvObj);

// AddRef nicht vergessen
	LPUNKNOWN(*ppvObj) -> AddRef();

	return S_OK;
}

//      Destruktion  ------------------------------------------------------
CGbmTRiASExtension :: ~CGbmTRiASExtension()
{
	if ( m_pDatenListeDlg )
	{
		m_pDatenListeDlg -> DestroyWindow();
		delete m_pDatenListeDlg;
		m_pDatenListeDlg = NULL;
	}

	if ( m_pObjProp != NULL )
		delete m_pObjProp;
	m_pObjProp = NULL;

	if ( m_pSetVerz )
	{
		m_pSetVerz -> Close();
		delete m_pSetVerz;
	}
	if ( m_pSetOrte )
	{
		m_pSetOrte -> Close();
		delete m_pSetOrte;
	}
	if ( m_pSetStrasse )
	{
		m_pSetStrasse -> Close();
		delete m_pSetStrasse;
	}
	if ( m_pSetTriDB )
	{
		m_pSetTriDB -> Close();
		delete m_pSetTriDB;
		g_pSetTriDB = NULL;
	}
	if ( g_pNF_PG1 )
	{
		if ( g_pNF_PG1 -> IsOpen())	g_pNF_PG1 -> Close();
		delete g_pNF_PG1;
		g_pNF_PG1 = NULL;
	}

	if ( g_pNF_PG2H )
	{
		if ( g_pNF_PG2H -> IsOpen())	g_pNF_PG2H -> Close();
		delete g_pNF_PG2H;
		g_pNF_PG2H = NULL;
	}
	if ( g_pNF_PG2D )
	{
		if ( g_pNF_PG2D -> IsOpen())	g_pNF_PG2D -> Close();
		delete g_pNF_PG2D;
		g_pNF_PG2D = NULL;
	}
	if ( g_pNF_PG1GB )
	{
		if ( g_pNF_PG1GB -> IsOpen())	g_pNF_PG1GB -> Close();
		delete g_pNF_PG1GB;
		g_pNF_PG1GB = NULL;
	}
	if ( g_pNF_PG4 )
	{
		if ( g_pNF_PG4 -> IsOpen())		g_pNF_PG4 -> Close();
		delete g_pNF_PG4;
		g_pNF_PG4 = NULL;
	}

	if ( m_pNF_PG1FL )
	{
		if ( m_pNF_PG1FL -> IsOpen())	m_pNF_PG1FL -> Close();
		delete m_pNF_PG1FL;
	}
/*	if ( m_pNF_PG1GB )
	{
		if ( m_pNF_PG1GB -> IsOpen())	m_pNF_PG1GB -> Close();
		delete m_pNF_PG1GB;
	}
	if ( m_pNF_PG2D )
	{
		if ( m_pNF_PG2D -> IsOpen())	m_pNF_PG2D -> Close();
		delete m_pNF_PG2D;
	}
	if ( m_pNF_PG2H )
	{
		if ( m_pNF_PG2H -> IsOpen())	m_pNF_PG2H -> Close();
		delete m_pNF_PG2H;
	}
*/
	if ( m_pNF_PG3 )
	{
		if ( m_pNF_PG3 -> IsOpen())		m_pNF_PG3 -> Close();
		delete m_pNF_PG3;
	}

	g_pDatabase = NULL;
	g_pSetTriDB = NULL;
	m_pSetTriDB = NULL;
	m_pSetVerz = NULL;
	m_pSetOrte = NULL;
	m_pSetStrasse = NULL;
//	m_pNF_PG1   = NULL;
	m_pNF_PG1FL = NULL;
//	m_pNF_PG1GB = NULL;
//	m_pNF_PG2D  = NULL;
//	m_pNF_PG2H  = NULL;
	m_pNF_PG3   = NULL;

//	if ( m_pTestBar )
//	{
//		delete m_pTestBar;
//		m_pTestBar = NULL;
//	}
}       // ~CGbmTRiASExtension


ULONG CGbmTRiASExtension :: m_RegNoti[] =
{
	0,
	DEX_PROJECTOPEN,			// Projekt öffnen
	DEX_PROJECTCLOSE,			// Projekt schließen
	DEX_N_PROJECTTOCLOSE,		// Projekt wird geschlossen
	DEX_INITIALIZEDSERVER,		// Server fertig initialisiert
	DEX_SERVERISCLOSING,		// TRIAS wird geschlossen
	DEX_SERVERCLOSED,			// TRIAS wurde geschlossen
	DEX_CREATEOBJEKTINFO,		// OR-Fenster wurde erzeugt
	DEX_OBJWNDCLOSED,			// OR-Fenster wurde geschlossen
	DEX_OBJECTSELECTED,			// Objekt wurde selektiert
	DEX_N_SHOWPROJECTWIZARD,	// zum Test
	DEX_ADDOBJECTTOLIST,		// Objekt in OR-Fenster aufnehmen
	DEX_REMOVEOBJECTFROMLIST,	// Objekt aus OR-Fenster entfernen
	DEX_SIGHTTOSELECT,			// Sicht soll gewechselt werden
	DEX_SIGHTSELECTED			// Sicht wurde aktiviert
};

ULONG CGbmTRiASExtension :: m_RegWinNoti[] =
{
	0,
};

//      InitExtension  ----------------------------------------------------
STDMETHODIMP_(bool) CGbmTRiASExtension :: InitExtension( short iMode )
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());

// den aktuellen Namen von TRiAS lesen
/*
CRegKey key;

	if (ERROR_SUCCESS == key.Open(HKEY_CURRENT_USER, TEXT("Software")) &&
		ERROR_SUCCESS == key.Open(key, TEXT("uve")) &&
		ERROR_SUCCESS == key.Open(key, TEXT("TRiAS")))
	{
	CRegKey cfgkey;

		if (ERROR_SUCCESS == cfgkey.Open(key, TEXT("Config")))
		{
//			DWORD dwCount = _countof(g_cbTRiAS);
			DWORD dwCount = _MAX_PATH;

			if (ERROR_SUCCESS != cfgkey.QueryValue (g_cbTRiAS, TEXT("TRiASName"), &dwCount))
				_tcscpy (g_cbTRiAS, g_cbTRiASDefaultName);	// Standard verwenden

		}
	}
	else
	{
	// Standard verwenden
		_tcscpy (g_cbTRiAS, g_cbTRiASDefaultName);
	}
*/
	HKEY	hKey0, hKey1, hKey2, hKey3;

	if (ERROR_SUCCESS == RegOpenKey(HKEY_CURRENT_USER, TEXT("Software"), &hKey0))
	{
		if (ERROR_SUCCESS == RegOpenKey( hKey0, TEXT("uve"), &hKey1 ))
		{
			if (ERROR_SUCCESS == RegOpenKey( hKey1, TEXT("TRiAS"), &hKey2 ))
			{
				if (ERROR_SUCCESS == RegOpenKey( hKey2, TEXT("Config"), &hKey3 ))
				{
					DWORD	dwCount = _MAX_PATH;
					DWORD	dwType = NULL;
					LONG	lRes = RegQueryValueEx( hKey3, TEXT("TRiASName"), NULL, &dwType,
											(LPBYTE)g_cbTRiAS, &dwCount );

					ASSERT((lRes!=ERROR_SUCCESS) || (dwType == REG_SZ) ||
						 (dwType == REG_MULTI_SZ) || (dwType == REG_EXPAND_SZ));

					if (ERROR_SUCCESS != lRes)
						_tcscpy (g_cbTRiAS, g_cbTRiASDefaultName);	// Standard verwenden

					RegCloseKey( hKey3 );
				}
				else
					_tcscpy (g_cbTRiAS, g_cbTRiASDefaultName);	// Standard verwenden

				RegCloseKey( hKey2 );
			}
			else
				_tcscpy (g_cbTRiAS, g_cbTRiASDefaultName);	// Standard verwenden

			RegCloseKey( hKey1 );
		}
		else
			_tcscpy (g_cbTRiAS, g_cbTRiASDefaultName);	// Standard verwenden

		RegCloseKey( hKey0 );
	}
	else
		_tcscpy (g_cbTRiAS, g_cbTRiASDefaultName);	// Standard verwenden

//	CDBException*	e;

	if (!CTriasExtension :: InitExtension (iMode))
		return false;

	m_pObjProp = CObjectProperties::CreateInstance( m_pUnk ? m_pUnk : this );

	if ( NULL == m_pObjProp )
		return false;

	g_pOPAngeschlGS = new COPAngeschlGS;
	if ( NULL != g_pOPAngeschlGS )
		g_pOPAngeschlGS -> AddRef();
	g_pOPBeitragsartGS = new COPBeitragsartGS;
	if ( NULL != g_pOPBeitragsartGS )
		g_pOPBeitragsartGS -> AddRef();
	g_pOPEigentumGS = new COPEigentumGS;
	if ( NULL != g_pOPEigentumGS )
		g_pOPEigentumGS -> AddRef();
	g_pOPGedrucktGS = new COPGedrucktGS;
	if ( NULL != g_pOPGedrucktGS )
	{
		g_pOPGedrucktGS -> AddRef();
		g_pOPGedrucktGS -> m_uiInfo = IDS_OPNAME02;
		g_pOPGedrucktGS -> m_uiHelp = IDS_OPINFO02;
	}
	g_pOPGedruck2GS = new COPGedrucktGS;
	if ( NULL != g_pOPGedruck2GS )
	{
		g_pOPGedruck2GS -> AddRef();
		g_pOPGedruck2GS -> m_uiInfo = IDS_OPNAME12;
		g_pOPGedruck2GS -> m_uiHelp = IDS_OPINFO12;
	}

	g_pOP_AGGS = new COP_AGGS;
	if ( NULL != g_pOP_AGGS )
		g_pOP_AGGS -> AddRef();
	g_pOP_FLG  = new COP_FLG;
	if ( NULL != g_pOP_FLG )
		g_pOP_FLG -> AddRef();
	g_pOP_GEFS = new COP_GEFS;
	if ( NULL != g_pOP_GEFS )
		g_pOP_GEFS -> AddRef();
	g_pOP_TIEB = new COP_TIEB;
	if ( NULL != g_pOP_TIEB )
		g_pOP_TIEB -> AddRef();
	g_pOP_KAT  = new COP_KAT;
	if ( NULL != g_pOP_KAT )
		g_pOP_KAT -> AddRef();
	g_pOP_FLN  = new COP_FLN;
	if ( NULL != g_pOP_FLN )
		g_pOP_FLN -> AddRef();
	g_pOP_TIEF = new COP_TIEF;
	if ( NULL != g_pOP_TIEF )
		g_pOP_TIEF -> AddRef();

//	((CFrameWnd*)MWind()) -> m_bAutoMenuEnable = FALSE;

//// MenuPunkte in TRiAS installieren und wieder entfernen
//	UINT InstallMenuItem (UINT iMenuID, UINT iMenuStr, bool iORMenu, 
//			      short iPopupNum, short iMenuPos = -1);
//	void RemoveMenuItem (UINT iMenuID, bool iORMenu, short iPopupNum);

	WritePrivateProfileString( "Aktiv", "ODBC", "Ja", "GBM.INI" );

	CxString	strFlag;

	strFlag.GetPrivateProfileString( "ProjectManager", "Verwenden", "GBM.INI" );
	if ( !strFlag.IsEmpty() && ( strFlag == "Nein" ))
		m_bUseProjectManager = FALSE;
	else
		m_bUseProjectManager = TRUE;

	InitZusatzFunktionen( FALSE );

	m_pSetTriDB = new CTriDBSet;
	if ( m_pSetTriDB == NULL )	return false;

	g_pDatabase = NULL;
	g_pSetTriDB = m_pSetTriDB;
	try
	{
		m_pSetTriDB -> Open();
		g_pDatabase = m_pSetTriDB -> m_pDatabase;
	}
	catch( CDBException* e )
	{
		AfxMessageBox( e->m_strError, MB_ICONEXCLAMATION );
		// Delete the incomplete recordset object
		delete m_pSetTriDB;
		m_pSetTriDB = NULL;
		e -> Delete();
		return false;
    }

	m_pSetVerz = new CVerzSet( g_pDatabase );
	try
	{
		m_pSetVerz -> Open();
	}
	catch( CDBException* e )
	{
		AfxMessageBox( e->m_strError, MB_ICONEXCLAMATION );
		// Delete the incomplete recordset object
		delete m_pSetVerz;
		m_pSetVerz = NULL;
		e -> Delete();
		return false;
    }

	m_pSetOrte = new COrteSet( g_pDatabase );
	try
	{
		m_pSetOrte -> Open();
	}
	catch( CDBException* e )
	{
		AfxMessageBox( e->m_strError, MB_ICONEXCLAMATION );
		// Delete the incomplete recordset object
		delete m_pSetOrte;
		m_pSetOrte = NULL;
		e -> Delete();
		return false;
    }
	g_pSetOrte = m_pSetOrte;

	m_pSetStrasse = new CStrasseSet( g_pDatabase );
	try
	{
		m_pSetStrasse -> Open();
	}
	catch( CDBException* e )
	{
		AfxMessageBox( e->m_strError, MB_ICONEXCLAMATION );
		// Delete the incomplete recordset object
		delete m_pSetStrasse;
		m_pSetStrasse = NULL;
		e -> Delete();
		return false;
    }
	g_pSetStrasse = m_pSetStrasse;

	m_pSetTriDB -> InitListen();
	g_pSetStrasse -> InitListen();
	m_pSetOrte -> InitListen();

	InstallMenuItem( IDM_OPEN_TR_PROJEKT, IDS_OPENMENUITEM, IMINormalMenu, 0, 1 );
	InstallMenuItem( IDM_OPEN_TR_PROJEKT, IDS_OPENMENUITEM, IMIStartUpMenu, 0, 1 );
	RemoveMenuItem( 101, IMINormalMenu|IMIOrigMenuItem, 0 );
	RemoveMenuItem( 101, IMIStartUpMenu|IMIOrigMenuItem, 0 );

	RegisterNotifications();
	CreateGBMToolBar();

	// Für den Fall, daß die Kopplung bei geöffnetem Projekt geladen wird!
	OnProjektOpen();

	m_bInitialisiert = true;

	return true;
}       // InitExtension

//      UnLoadExtension  --------------------------------------------------
STDMETHODIMP_(bool) CGbmTRiASExtension :: UnLoadExtension()
{
	m_bInitialisiert = false;

	UnregisterNotifications();
	RemoveGBMToolBar();

	g_pOPAngeschlGS -> Release();
	g_pOPBeitragsartGS -> Release();
	g_pOPEigentumGS -> Release();
	g_pOPGedrucktGS -> Release();
	g_pOPGedruck2GS -> Release();

	g_pOP_AGGS -> Release();
	g_pOP_FLG -> Release();
	g_pOP_GEFS -> Release();
	g_pOP_TIEB -> Release();
	g_pOP_KAT -> Release();
	g_pOP_FLN -> Release();
	g_pOP_TIEF -> Release();
	m_pObjProp -> Release();

	g_pOP_AGGS = NULL;
	g_pOP_FLG = NULL;
	g_pOP_GEFS = NULL;
	g_pOP_TIEB = NULL;
	g_pOP_KAT = NULL;
	g_pOP_FLN = NULL;
	g_pOP_TIEF = NULL;

	if ( NULL != m_pScript )
		m_pScript -> Release();

	CPrintAnlage1	*pPA;
	pPA = new CPrintAnlage1( "XX", 0L );
	pPA -> DeleteStaticMembers();
	delete pPA;

	if ( m_pDatenListeDlg )
	{
		m_pDatenListeDlg -> DestroyWindow();
		delete m_pDatenListeDlg;
		m_pDatenListeDlg = NULL;
	}

	InstallMenuItem( 101, 0, 1, IDS_OPEN, IMINormalMenu|IMIOrigMenuItem );
	InstallMenuItem( 101, 0, 1, IDS_OPEN, IMIStartUpMenu|IMIOrigMenuItem );
// Ist leider wirkungslos!
/*
	CMenu	*pMenu = MWind() -> GetMenu();
	CMenu	*pSubMenu = NULL;
	CString	strMenuText;

	if ( NULL != pMenu )
	{
		pSubMenu = pMenu -> GetSubMenu( 0 );
		if ( NULL != pSubMenu )
		{
			strMenuText.LoadString( IDS_OPEN );
			pSubMenu -> InsertMenu( 1, MF_BYPOSITION, 101, strMenuText );
		}
	}
*/
	RemoveMenuItem( IDM_OPEN_TR_PROJEKT, IMINormalMenu, 0 );
	RemoveMenuItem( IDM_OPEN_TR_PROJEKT, IMIStartUpMenu, 0 );

	WritePrivateProfileString( "Aktiv", "ODBC", "Nein", "GBM.INI" );
	if ( m_bUseProjectManager )
		WritePrivateProfileString( "ProjectManager", "Verwenden", "Ja", "GBM.INI" );
	else
		WritePrivateProfileString( "ProjectManager", "Verwenden", "Nein", "GBM.INI" );

	return CTriasExtension :: UnLoadExtension();
}	// UnLoadExtension

void CGbmTRiASExtension::RegisterNotifications()
{
	short	i, n = sizeof( m_RegNoti ) / sizeof( ULONG );

	for ( i = 1; i < n; RegisterNotification( m_RegNoti[i++]));
	n = sizeof( m_RegWinNoti ) / sizeof( ULONG );
	for ( i = 1; i < n; RegisterNotification( m_RegWinNoti[i++]), FALSE );
	RegisterNotification( g_iGSTeilenMsg, FALSE );
}

void CGbmTRiASExtension::UnregisterNotifications()
{
	short	i, n = sizeof( m_RegNoti ) / sizeof( ULONG );

	for ( i = 1; i < n; UnRegisterNotification( m_RegNoti[i++]));
	n = sizeof( m_RegWinNoti ) / sizeof( ULONG );
	for ( i = 1; i < n; UnRegisterNotification( m_RegWinNoti[i++]), FALSE );
	UnRegisterNotification( g_iGSTeilenMsg, FALSE );
}

bool CGbmTRiASExtension::CommandToEnable( UINT uiID )
{
	bool	result = false;

	if ( !m_bInitialisiert )	return result;

	switch ( uiID )
	{
	case IDM_OPENPROJEKT:
	case IDM_EDIT:
	case IDM_ABOUT:
		result = true;
		break;

	case IDM_STATISTIK:
		result = false;
		break;

	case IDM_DATEN:				// + MenuOffset();		// id1
	case IDM_FLAECHEN:			// + MenuOffset();		// id4
	case IDM_TIEFENBEGR:		// + MenuOffset();		// id5
	case IDM_SUCHEN:			// + MenuOffset();		// id7
	case IDM_EXTRAS:			// + MenuOffset();		// idA
	case IDM_VISU:				// + MenuOffset();		// idB
		result = m_bIntegratedProjekt && ( m_iOISY > 0 );
		break;

	case IDM_PRINT:				// + MenuOffset();		// id2
	case IDM_PRINT_PREVIEW:		// + MenuOffset();		// id3
	case IDM_BEITRAG:			// + MenuOffset();		// id8
		result = ( NULL != m_pDatenListeDlg ) && m_bIntegratedProjekt &&
				 ( m_pDatenListeDlg -> AnzahlSelectedGS() > 0 );
		break;

	case IDM_BEARBEITEN:		// + MenuOffset();		// id6
	case IDM_EDITIDE:			// + MenuOffset();		// id0
		result = m_bIntegratedProjekt && ( NULL != m_pDatenListeDlg ) &&
			(( m_pDatenListeDlg -> AnzahlMarkedGS() == 1 ) ||
			(( m_pDatenListeDlg -> AnzahlMarkedGS() == 0 ) &&
			 ( m_pDatenListeDlg -> GSohneIDE() != 0 )));
		break;

	case IDM_INCLUDEPROJECT:	// + MenuOffset();		// id9
		result = !m_bIntegratedProjekt && m_bIntegrierbar;
		break;
	}

	return result;
}

int CGbmTRiASExtension::CommandToCheck( UINT uiID )
{
	int		result = 0;

	if ( !m_bInitialisiert )	return result;

	switch ( uiID )
	{
	case IDM_DATEN:				// + MenuOffset();		// id1
		if ( m_pDatenListeDlg )
			if ( m_pDatenListeDlg -> IsWindowVisible())
				result = 1;
		break;

	case IDM_OPENPROJEKT:
	case IDM_EDIT:
	case IDM_ABOUT:
	case IDM_STATISTIK:
	case IDM_FLAECHEN:			// + MenuOffset();		// id4
	case IDM_TIEFENBEGR:		// + MenuOffset();		// id5
	case IDM_SUCHEN:			// + MenuOffset();		// id7
	case IDM_EXTRAS:			// + MenuOffset();		// idA
	case IDM_VISU:				// + MenuOffset();		// idB
	case IDM_PRINT:				// + MenuOffset();		// id2
	case IDM_PRINT_PREVIEW:		// + MenuOffset();		// id3
	case IDM_BEITRAG:			// + MenuOffset();		// id8
	case IDM_BEARBEITEN:		// + MenuOffset();		// id6
	case IDM_EDITIDE:			// + MenuOffset();		// id0
	case IDM_INCLUDEPROJECT:	// + MenuOffset();		// id9
		break;
	}

	return result;
}

STDMETHODIMP_(bool) CGbmTRiASExtension :: MenuInit( HMENU hMenu, LPARAM lParam, HWND hWnd)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CMenu*	pMenu;
	UINT	id1 = IDM_DATEN + MenuOffset();
	UINT	id2 = IDM_PRINT + MenuOffset();
	UINT	id3 = IDM_PRINT_PREVIEW + MenuOffset();
	UINT	id4 = IDM_FLAECHEN + MenuOffset();
	UINT	id5 = IDM_TIEFENBEGR + MenuOffset();
	UINT	id6 = IDM_BEARBEITEN + MenuOffset();
	UINT	id7 = IDM_SUCHEN + MenuOffset();
	UINT	id8 = IDM_BEITRAG + MenuOffset();
	UINT	id9 = IDM_INCLUDEPROJECT + MenuOffset();
	UINT	id0 = IDM_EDITIDE + MenuOffset();
	UINT	idA = IDM_EXTRAS + MenuOffset();
	UINT	idB = IDM_VISU + MenuOffset();

	if ( !hWnd )
	{
		pMenu = CMenu::FromHandle( hMenu );
		ASSERT( pMenu );

		if ( m_strarrZusatzFkt.GetSize() == 0 )
			if ( pExtMenu() -> DeleteMenu( idA, MF_BYCOMMAND ))
				MWind() -> DrawMenuBar();

		if ( m_bIntegratedProjekt && ( m_iOISY > 0 ))
		{
			pMenu -> EnableMenuItem( id1, MF_ENABLED | MF_BYCOMMAND );
			pMenu -> EnableMenuItem( id4, MF_ENABLED | MF_BYCOMMAND );
			pMenu -> EnableMenuItem( id5, MF_ENABLED | MF_BYCOMMAND );
//			pMenu -> EnableMenuItem( id5, MF_GRAYED | MF_BYCOMMAND );
			pMenu -> EnableMenuItem( id7, MF_ENABLED | MF_BYCOMMAND );
			pMenu -> EnableMenuItem( id8, MF_ENABLED | MF_BYCOMMAND );
			pMenu -> EnableMenuItem( idA, MF_ENABLED | MF_BYCOMMAND );
			pMenu -> EnableMenuItem( idB, MF_ENABLED | MF_BYCOMMAND );
		}
		else
		{
			pMenu -> EnableMenuItem( id1, MF_GRAYED | MF_BYCOMMAND );
			pMenu -> EnableMenuItem( id4, MF_GRAYED | MF_BYCOMMAND );
			pMenu -> EnableMenuItem( id5, MF_GRAYED | MF_BYCOMMAND );
			pMenu -> EnableMenuItem( id7, MF_GRAYED | MF_BYCOMMAND );
			pMenu -> EnableMenuItem( id8, MF_GRAYED | MF_BYCOMMAND );
			pMenu -> EnableMenuItem( idA, MF_GRAYED | MF_BYCOMMAND );
			pMenu -> EnableMenuItem( idB, MF_GRAYED | MF_BYCOMMAND );
		}

		if ( !m_bIntegratedProjekt && m_bIntegrierbar )
			pMenu -> EnableMenuItem( id9, MF_ENABLED | MF_BYCOMMAND );
		else
			pMenu -> EnableMenuItem( id9, MF_GRAYED | MF_BYCOMMAND );

		if ( m_pDatenListeDlg )
		{
			if ( m_pDatenListeDlg -> IsWindowVisible())
				pMenu -> CheckMenuItem( id1, MF_CHECKED | MF_BYCOMMAND );
			else
				pMenu -> CheckMenuItem( id1, MF_UNCHECKED | MF_BYCOMMAND );

			if ( m_bIntegratedProjekt && ( m_pDatenListeDlg -> AnzahlSelectedGS() > 0 ))
			{
				pMenu -> EnableMenuItem( id2, MF_ENABLED | MF_BYCOMMAND );
				pMenu -> EnableMenuItem( id3, MF_ENABLED | MF_BYCOMMAND );
			}
			else
			{
//				pMenu -> EnableMenuItem( id2, MF_ENABLED | MF_BYCOMMAND );	// nur zum Test!!!
//				pMenu -> EnableMenuItem( id3, MF_ENABLED | MF_BYCOMMAND );	// nur zum Test!!!
				pMenu -> EnableMenuItem( id2, MF_GRAYED | MF_BYCOMMAND );
				pMenu -> EnableMenuItem( id3, MF_GRAYED | MF_BYCOMMAND );
			}

//			if ( m_bIntegratedProjekt &&
//				( m_pDatenListeDlg -> AnzahlSelectedGS() > 0 ) &&
//				( m_pDatenListeDlg -> AnzahlMarkedGS() == 1 ))
//				pMenu -> EnableMenuItem( id6, MF_ENABLED | MF_BYCOMMAND );
//			else
//				pMenu -> EnableMenuItem( id6, MF_GRAYED | MF_BYCOMMAND );
		}
		else
		{
			pMenu -> CheckMenuItem( id1, MF_UNCHECKED | MF_BYCOMMAND );
//			pMenu -> EnableMenuItem( id2, MF_ENABLED | MF_BYCOMMAND );	// nur zum Test!!!
//			pMenu -> EnableMenuItem( id3, MF_ENABLED | MF_BYCOMMAND );	// nur zum Test!!!
			pMenu -> EnableMenuItem( id2, MF_GRAYED | MF_BYCOMMAND );
			pMenu -> EnableMenuItem( id3, MF_GRAYED | MF_BYCOMMAND );
//			pMenu -> EnableMenuItem( id6, MF_GRAYED | MF_BYCOMMAND );
		}

		if ( m_bIntegratedProjekt &&
			(( m_pDatenListeDlg -> AnzahlMarkedGS() == 1 ) ||
			 (( m_pDatenListeDlg -> AnzahlMarkedGS() == 0 ) &&
			  ( m_pDatenListeDlg -> GSohneIDE() != 0 ))))
		{
			pMenu -> EnableMenuItem( id0, MF_ENABLED | MF_BYCOMMAND );
			pMenu -> EnableMenuItem( id6, MF_ENABLED | MF_BYCOMMAND );
		}
		else
		{
			pMenu -> EnableMenuItem( id0, MF_GRAYED | MF_BYCOMMAND );
			pMenu -> EnableMenuItem( id6, MF_GRAYED | MF_BYCOMMAND );
		}
	}
	else
	{
/*
		pMenu = CMenu::FromHandle( hMenu );
		ASSERT( pMenu );

		if ( TRUE )
			pMenu -> EnableMenuItem( id0, MF_GRAYED | MF_BYCOMMAND );
		else
			pMenu -> EnableMenuItem( id0, MF_GRAYED | MF_BYCOMMAND );
*/
	}

	return CTriasExtension :: MenuInit( hMenu, lParam, hWnd );
}	// MenuInit

STDMETHODIMP_(bool) CGbmTRiASExtension :: MenuSelect( UINT uiMenuID, HMENU hMenu, HWND hWnd)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString	text;
	bool	result = true;

	switch ( uiMenuID )
	{
	case IDM_OPENPROJEKT:
		break;

	case IDM_INCLUDEPROJECT:
		break;

	case IDM_DATEN:
		break;

	case IDM_OPEN_TR_PROJEKT:
//		text.LoadString( IDM_OPEN_TR_PROJEKT );
		break;

	default:
		result = CTriasExtension :: MenuSelect( uiMenuID, hMenu, hWnd );
	}

	if ( !text.IsEmpty())
		DEX_SetMessageString((const char*)text );

	return result;
//	return CTriasExtension :: MenuSelect( uiMenuID, hMenu, hWnd );
}	// MenuSelect

STDMETHODIMP_(bool) CGbmTRiASExtension :: MenuCommand( WPARAM wParam, HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	bool	result = true;

	if ( hWnd )
	{
		switch ( wParam )
		{
		case IDM_EDITIDE:
			EditIDE();
			break;

		default:
			result = CTriasExtension :: MenuCommand( wParam, hWnd );
		}
	}
	else
	{
		switch ( wParam )
		{
		case IDM_EDITIDE:
			EditIDE();
			break;

		case IDM_OPENPROJEKT:
//			result = ( StartupProc( 0, 0L ) == 0L );
			result = ( OpenProjektWiz() == 0L );
			break;

		case IDM_INCLUDEPROJECT:
			result = ( IncludeProjekt() == 0L );
			break;

		case IDM_DATEN:
			if ( m_bIntegratedProjekt )	result = SwitchDatenListeDlg();
			break;

		case IDM_OPEN_TR_PROJEKT:
			if ( m_bUseProjectManager )
				result = ( OpenProjektWiz() == 0L );
			else
				AfxGetMainWnd() -> PostMessage( WM_COMMAND, 101, 0L );
			break;

		case IDM_ABOUT:
			OnAbout();
			break;

		case IDM_PRINT:
			OnPrint();
			break;

		case IDM_PRINT_PREVIEW:
			OnPrintPreview();
			break;

		case IDM_FLAECHEN:
			OnFlaechenberechnung();
			break;

		case IDM_TIEFENBEGR:
			OnTiefenbegrenzung();
			break;

		case IDM_BEITRAG:
			OnBeitragBerechnen();
			break;

		case IDM_SUCHEN:
			if ( m_pDatenListeDlg ) m_pDatenListeDlg -> OnSuchen();
			break;

		case IDM_BEARBEITEN:
			if ( m_pDatenListeDlg )
			{
				if ( m_pDatenListeDlg -> AnzahlMarkedGS() == 1 )	m_pDatenListeDlg -> OnDetails();
			}
			else		NeueIDE();
			break;

		case IDM_EXTRAS:
			ZusatzFkt();
			break;

		case IDM_VISU:
			Visualisierung();
			break;

		case IDM_EDIT:
			EditVorlagen();
			break;

		default:
			result = CTriasExtension :: MenuCommand( wParam, hWnd );
		}
	}

	return result;
}	// MenuCommand

STDMETHODIMP_(LRESULT) CGbmTRiASExtension :: Notification( WPARAM wParam, LPARAM lParam)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CxString	text;
	LRESULT		result = 0L;

	switch (wParam )
	{
	case DEX_PROJECTOPEN:			// Projekt öffnen
		OnProjektOpen();
		break;

	case DEX_INITIALIZEDSERVER:		// Server fertig initialisiert
		break;

	case DEX_PROJECTCLOSE:			// Projekt schließen
		RewriteModifications();
		break;

	case DEX_N_PROJECTTOCLOSE:		// Projekt wird geschlossen
//		DEX_FlushModifications();	// um die Rückfrage zu unterdrücken und die
//									// ObjektVisInfo zu speichern!
		CloseProjektCleanup();
		break;

	case DEX_SERVERISCLOSING:		// TRIAS wird geschlossen
		m_bServerIsClosing = TRUE;
		break;

	case DEX_CREATEOBJEKTINFO:		// OR-Fenster wurde erzeugt
		if ( !m_bProcessPrinting )
			UpdateORWnd( (HWND)lParam, TRUE );
		break;

	case DEX_OBJWNDCLOSED:			// OR-Fenster wurde geschlossen
		if ( !m_bProcessPrinting )
			UpdateORWnd( (HWND)lParam, FALSE );
		break;

	case DEX_OBJECTSELECTED:		// Objekt wurde selektiert
		ObjectSelected( lParam );
		break;

	case DEX_N_SHOWPROJECTWIZARD:
//		if ( AfxGetApp())	text = AfxGetApp() -> m_lpCmdLine;
//		if ( AfxGetApp() && text.IsEmpty())
		if ( lParam == 2L )
		{
			if ( m_bUseProjectManager )
			{
				OpenProjektWiz();
				result = true;
			}
			else
				result = CTriasExtension :: Notification( wParam, lParam );
		}
		break;

	case DEX_ADDOBJECTTOLIST:		// Objekt wurde zu einem OR-Fenster hinzugefügt
									// wParam ???
									// lParam = ObjektNr
		AddObject( (long)lParam );
		break;

	default:
		result = CTriasExtension :: Notification( wParam, lParam );
	}

	return result;
}	// Notification

STDMETHODIMP_(LRESULT) CGbmTRiASExtension :: WindowsNotification( UINT wMsg, WPARAM wParam, LPARAM lParam)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if ( wMsg == g_iGSTeilenMsg )
		if ( m_pDatenListeDlg )
	{
		// Behandlung durch INI-Eintrag außer Betrieb?
		// [GS-Teilen]
		// Behandlung=Ja
		//
		if ( g_bHandleGSTeilen )
			m_pDatenListeDlg -> HandleGSTeilen();
		return 0L;
	}

	return CTriasExtension::WindowsNotification( wMsg, wParam, lParam );
}	// WindowsNotification

STDMETHODIMP_(LRESULT) CGbmTRiASExtension :: GetCapabilities( UINT uiCap )
{
	return CTriasExtension :: GetCapabilities( uiCap );
}	// GetCapabilities

LRESULT CGbmTRiASExtension::StartupProc( WPARAM wParam, LPARAM lParam )
{
	LRESULT			result = 0L;
	CString			name;
	COpenProjektDlg	dlg( MWind());

	if ( wParam == 1 )
	{
		GetActiveProject( name );
		if ( !name.IsEmpty())	return 1L;
	}

	dlg.m_pSetTriDB = m_pSetTriDB;
	dlg.m_pSetVerz = m_pSetVerz;
	dlg.m_pSetOrte = m_pSetOrte;
	dlg.m_pSetStrasse = m_pSetStrasse;

	if ( dlg.DoModal() == IDOK )
	{
		m_bIntegratedProjekt = FALSE;

		if ( !dlg.m_strPfad.IsEmpty())
		{
			name = dlg.m_strPfad;
			m_iOISY = dlg.m_iCurrOISY;

			TRIAS_OPEN	tos;
			char		*pProjekt, *pUser, *pPassWord;

			pProjekt = name.GetBuffer( 0 );
			pUser = pProjekt;

			while ( *pUser ) pUser++;
			pPassWord = pUser;

			tos.dwSize     = sizeof( TRIAS_OPEN );
			tos.lpProject  = pProjekt;
			tos.lpUser     = pUser;
			tos.lpPassWord = pPassWord;
			tos.iMode      = 0;     // Standardsicht zeigen!

			DEX_OpenProject( tos );

			if (( DEX_GetIdentFromClassName( "Grundstück" ) != 0L ) &&
				( DEX_GetMCodeFromFeatureName( "Identifikationsnummer" ) != 0L ))
				m_bIntegratedProjekt = TRUE;
			else
				m_iOISY = -1;
		}
	}

	return result;
}

void GetActiveProject( CString &name )
{
	char	*buffer;

	buffer = name.GetBuffer( 1024 );
	buffer[0] = '\0';
	DEX_GetActiveProject( buffer );
	name.ReleaseBuffer();
}	// GetActiveProject

#include "sectlf.h"

bool CGbmTRiASExtension::SwitchDatenListeDlg( bool zwang, bool visible )
{
	bool	result = true;
	CRect	rect, rect1;
	SECToplevelFrame *pWnd = (SECToplevelFrame*)AfxGetMainWnd();

	if ( m_pDatenListeDlg == NULL )
	{
		if ( g_pNF_PG1 == NULL )	g_pNF_PG1 = new CSetNF_PG1( g_pDatabase );
//		if ( g_pNF_PG1 == NULL )	g_pNF_PG1 = new CSetNF_PG1;
		ASSERT( g_pNF_PG1 );
		m_pDatenListeDlg = new CDatenListeDlg( MWind(), m_iOISY, g_pNF_PG1 );
		if ( m_pDatenListeDlg )
		{
			AfxGetMainWnd() -> GetClientRect( &rect );
			m_pDatenListeDlg -> GetWindowRect( &rect1 );
			rect.left = rect.right - rect1.Width();
			m_pDatenListeDlg -> EnableDocking( CBRS_ALIGN_ANY );

//			((SECToplevelFrame*)AfxGetMainWnd()) -> DockControlBar( m_pDatenListeDlg,
//				AFX_IDW_DOCKBAR_RIGHT, &rect );

			if ( pWnd -> IsKindOf( RUNTIME_CLASS( SECToplevelFrame )))
				pWnd -> DockControlBar( m_pDatenListeDlg, AFX_IDW_DOCKBAR_RIGHT, &rect );

//			((SECToplevelFrame*)AfxGetMainWnd()) -> DockControlBarEx( m_pDatenListeDlg,
//				AFX_IDW_DOCKBAR_RIGHT, 1, 0, (float)0.40, 130);
			m_pDatenListeDlg -> m_pSetStrasse = m_pSetStrasse;
			m_pDatenListeDlg -> m_pSetOrte = m_pSetOrte;

			if ( g_pNF_PG2D == NULL )	g_pNF_PG2D = new CSetNF_PG2D( g_pDatabase );
			ASSERT( g_pNF_PG2D );
			if ( g_pNF_PG2H == NULL )	g_pNF_PG2H = new CSetNF_PG2H( g_pDatabase );
			ASSERT( g_pNF_PG2H );
			if ( g_pNF_PG1GB == NULL )	g_pNF_PG1GB = new CSetNF_PG1GB( g_pDatabase );
			ASSERT( g_pNF_PG1GB );
			if ( g_pNF_PG4 == NULL )	g_pNF_PG4 = new CSetNF_PG4( g_pDatabase );
			ASSERT( g_pNF_PG4 );
		}
		else
			return false;
	}

	if ( pWnd -> IsKindOf( RUNTIME_CLASS( SECToplevelFrame )))
	{
		if ( zwang )
			pWnd -> ShowControlBar( m_pDatenListeDlg, visible, TRUE );
		else
			pWnd -> ShowControlBar( m_pDatenListeDlg, 
					!m_pDatenListeDlg -> IsWindowVisible(), TRUE );
	}
	else
	{
		if ( zwang )
			m_pDatenListeDlg -> ShowWindow( visible ? SW_SHOW : SW_HIDE );
		else
		{
			if ( m_pDatenListeDlg -> IsWindowVisible())
				m_pDatenListeDlg -> ShowWindow( SW_HIDE );
			else
				m_pDatenListeDlg -> ShowWindow( SW_SHOW );
		}
	}

//	if ( pWnd -> IsKindOf( RUNTIME_CLASS( SECToplevelFrame )))
//		((SECToplevelFrame*)pWnd) -> RecalcLayout();
//	else
		((CFrameWnd*)pWnd) -> RecalcLayout();

//	CWnd *pWnd = AfxGetMainWnd();
//	if ( pWnd -> IsKindOf( RUNTIME_CLASS( CFrameWnd )))
//			((CFrameWnd*)pWnd) -> RecalcLayout();

//	if ( pWnd -> IsKindOf( RUNTIME_CLASS( SECFrameWnd )))
//			((SECFrameWnd*)pWnd) -> RecalcLayout();

//	if ( pWnd -> IsKindOf( RUNTIME_CLASS( SECToplevelFrame )))
//			((SECToplevelFrame*)pWnd) -> RecalcLayout();

	return result;
}

//  RechIDProc  ------------------------------------------------------
//////////////////////////////////////////////////////////////////////
BOOL PASCAL FAR RechIDProc( long ONr, BOOL iNotLast, void *pData )
{
	long	*l_ONr = (long*)pData;
	if ( l_ONr[0] < 2L )		l_ONr[0] = 2L;
	if ( l_ONr[0] < l_ONr[1] )	l_ONr[l_ONr[0]++] = ONr;
	else						l_ONr[0]++;
	return TRUE;
}

void CGbmTRiASExtension::UpdateORWnd( HWND hwnd, BOOL add )
{
	if ( m_pDatenListeDlg )
	{
		if ( !add )		m_pDatenListeDlg -> m_hWndRemove = (HWND)hwnd;
		else			m_pDatenListeDlg -> m_hWndRemove = (HWND)NULL;

		m_pDatenListeDlg -> SyncListen( FALSE );
	}
}

void CGbmTRiASExtension::ObjectSelected( long onr )
{
	if ( m_pDatenListeDlg )
//		m_pDatenListeDlg -> SyncListen( FALSE );
		m_pDatenListeDlg -> SelectObject( onr );
}

void CGbmTRiASExtension::AddObject( long onr )
{
	if ( m_pDatenListeDlg )
		m_pDatenListeDlg -> AddGS( onr );
}

void CGbmTRiASExtension::CloseProjektCleanup()
{
	CxString	strIniFile;
	CxString	strFkt;

	m_bIntegratedProjekt = FALSE;

	if ( NULL != m_pObjProp )
		m_pObjProp -> RemoveAllPropertyFunctions();

	if ( m_pDatenListeDlg )
	{
		m_pDatenListeDlg -> DestroyWindow();
		delete m_pDatenListeDlg;
		m_pDatenListeDlg = NULL;
	}

	if ( NULL != m_pObjProp )
	{
		m_pObjProp -> RemovePropertyFunction( g_ulOPAngeschlGS );
		m_pObjProp -> RemovePropertyFunction( g_ulOPBeitragsartGS );
		m_pObjProp -> RemovePropertyFunction( g_ulOPEigentumGS );
		m_pObjProp -> RemovePropertyFunction( g_ulOPGedrucktGS );
		m_pObjProp -> RemovePropertyFunction( g_ulOPGedruck2GS );

		m_pObjProp -> RemovePropertyFunction( g_ulOP_AGGS );
		m_pObjProp -> RemovePropertyFunction( g_ulOP_FLG );
		m_pObjProp -> RemovePropertyFunction( g_ulOP_GEFS );
		m_pObjProp -> RemovePropertyFunction( g_ulOP_TIEB );
		m_pObjProp -> RemovePropertyFunction( g_ulOP_KAT );
		m_pObjProp -> RemovePropertyFunction( g_ulOP_FLN );
		m_pObjProp -> RemovePropertyFunction( g_ulOP_TIEF );

		g_ulOPAngeschlGS = 0L;
		g_ulOPBeitragsartGS = 0L;
		g_ulOPEigentumGS = 0L;
		g_ulOPGedrucktGS = 0L;
		g_ulOPGedruck2GS = 0L;
		g_ulOP_AGGS = 0L;
		g_ulOP_FLG = 0L;
		g_ulOP_GEFS = 0L;
		g_ulOP_TIEB = 0L;
		g_ulOP_KAT = 0L;
		g_ulOP_FLN = 0L;
		g_ulOP_TIEF = 0L;
	}

	if ( g_pNF_PG1GB )
	{
		if ( g_pNF_PG1GB -> IsOpen())	g_pNF_PG1GB -> Close();
		delete g_pNF_PG1GB;
		g_pNF_PG1GB = NULL;
	}
	if ( g_pNF_PG2D )
	{
		if ( g_pNF_PG2D -> IsOpen())	g_pNF_PG2D -> Close();
		delete g_pNF_PG2D;
		g_pNF_PG2D = NULL;
	}
	if ( g_pNF_PG2H )
	{
		if ( g_pNF_PG2H -> IsOpen())	g_pNF_PG2H -> Close();
		delete g_pNF_PG2H;
		g_pNF_PG2H = NULL;
	}
	if ( g_pNF_PG4 )
	{
		if ( g_pNF_PG4 -> IsOpen())		g_pNF_PG4 -> Close();
		delete g_pNF_PG4;
		g_pNF_PG4 = NULL;
	}

	GetActiveProject( strIniFile );
	if ( strIniFile.GetLength() > 4 )
		strIniFile = strIniFile.Left( strIniFile.GetLength() - 3 );
	else
		strIniFile.Empty();

	if ( !strIniFile.IsEmpty())
	{
		strIniFile += "INI";
		strFkt.WritePrivateProfileString( "BasicScript", "AutoStart", strIniFile );
	}
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

void OISY2String2( double oisy, CString &strOISY )
{
	CString		temp;
	short		id = short( oisy );

	switch ( id )
	{
	case 1:		temp = "I";	break;
	case 2:		temp = "E";	break;
	case 3:		temp = "B";	break;
	case 4:		temp = "J";	break;
	case 5:		temp = "P";	break;
	case 6:		temp = "G";	break;
	case 7:		temp = "M";	break;
	case 8:		temp = "L";	break;
	case 9:		temp = "N";	break;
	case 10:	temp = "H";	break;
	case 11:	temp = "C";	break;
	case 12:	temp = "A";	break;
	case 13:	temp = "D";	break;
	case 14:	temp = "F";	break;
	case 15:	temp = "K";	break;
	case 16:	temp = "O";	break;
	}

	if ( temp.GetLength() == 1 )	temp += "0";
	strOISY = temp;
}	// OISY2String	2 Alternativen!!

void OISY2String( double oisy, CString &strOISY )
{
	CxString	temp, result;
	short		id = short( oisy );

	result.AppendF( id, -1 );
	while ( result.GetLength() < 2 )
	{
		temp = "0";
		temp += result;
		result = temp;
	}

	strOISY = result;
}	// OISY2String	2 Alternativen!!

short String2OISY( const char* oisy )
{
	ASSERT( AfxIsValidString( oisy ));
	ASSERT( oisy[0]);
	ASSERT( oisy[1]);

	short		result = -1;
	char		id = *oisy;
	CString		text;

	text = oisy;
	if ( oisy[1] == '0' )
	{
		switch ( id )
		{
		case 'I':	result = 1;		break;
		case 'E':	result = 2;		break;
		case 'B':	result = 3;		break;
		case 'J':	result = 4;		break;
		case 'P':	result = 5;		break;
		case 'G':	result = 6;		break;
		case 'M':	result = 7;		break;
		case 'L':	result = 8;		break;
		case 'N':	result = 9;		break;
		case 'H':	result = 10;	break;
		case 'C':	result = 11;	break;
		case 'A':	result = 12;	break;
		case 'D':	result = 13;	break;
		case 'F':	result = 14;	break;
		case 'K':	result = 15;	break;
		case 'O':	result = 16;	break;
		case '1':	result = 10;	break;
		}
	}
	else
	{
		text = text.Left( 2 );
		result = atoi( text );
	}
	return result;
}	// OISY2String

void ISY2String( double oisy, double isy, CString &strISY )
{
	CxString	temp, result;
	short		id = short( isy );

	result.AppendF( id, -1 );
	while ( result.GetLength() < 3 )
	{
		temp = "0";
		temp += result;
		result = temp;
	}

	strISY = result;
}	// ISY2String

short String2ISY( short oisy, const char* isy )
{
	CString		text;
	short		result;

	ASSERT( AfxIsValidString( isy ));
	text = isy;
	result = atoi( text );
	return result;
}	// ISY2String

LRESULT CGbmTRiASExtension::IncludeProjekt()
{
	LRESULT			result = 0L;
	CInterDialog	dlg( AfxGetMainWnd());
	CString			name, pfad;
	char			*txt;

	// Namen für Projekt erfragen (und Optionen einstellen)
	txt = pfad.GetBuffer( 1024 );
	DEX_GetActiveProject( txt );
	pfad.ReleaseBuffer();
	dlg.m_strPfad = pfad;
	if ( dlg.DoModal() != IDOK )	return 1L;
	name = dlg.m_strBez;
	if ( name.IsEmpty())		return 1L;

	CWaitCursor		wc;

	// Eintrag in Tabelle 'Verz' erstellen
	ASSERT( m_pSetVerz != NULL );
	m_iVerzNr = m_pSetVerz -> RegisterProjekt( name, pfad );
	if ( m_iVerzNr <= 0 )			return 1L;

	// Alle IDE auflisten
	OnProjektOpen();

	// Tabelle 'TRIDB' ergänzen
	ASSERT( m_pDatenListeDlg != NULL );
	m_pDatenListeDlg -> SaveTRiDBNr( m_iVerzNr );

	// Indextabellen für Orte und Strassen neu erstellen
	m_pSetTriDB -> RewriteIndex();

	// Initialisierung GBM-Datenbank abgeschlossen
	m_iOISY = m_pSetTriDB -> FindOISY( m_iVerzNr );

	return result;
}

LRESULT CGbmTRiASExtension::OpenProjektWiz()
{
	LRESULT			result = 0L;
	CMyPropSheet	sheet( "GBM-Projekt auswählen" );
	CStartPage1		*page1;
	CStartPage2		*page2;
	CString			name, ide, text, ide2;
	CxString		project;

	MWind() -> BeginWaitCursor();

	page1 = new CStartPage1;
	page2 = new CStartPage2;

	page2 -> m_pSetTriDB = m_pSetTriDB;
	page2 -> m_pSetVerz = m_pSetVerz;
	page2 -> m_pSetOrte = m_pSetOrte;
	page2 -> m_pSetStrasse = m_pSetStrasse;

	m_pSetTriDB -> InitListen();
	m_pSetOrte -> InitListen();

	sheet.AddPage( page1 );
	sheet.AddPage( page2 );
	sheet.SetWizardMode();
	if ( sheet.DoModal() == ID_WIZFINISH )
	{
		switch ( page1 -> m_iSelect )
		{
		case 0:		// Auswahl
			m_bIntegratedProjekt = FALSE;
			name = page2 -> m_strPfad;
			if ( !name.IsEmpty())
			{
				project = name;
				if ( !project.FileExist())
				{
					project = "Datei '";
					project += name;
					project += "' wurde nicht gefunden!";
					AfxMessageBox( project );
				}
				else
				{
					m_iOISY = page2 -> m_iCurrOISY;

					TRIAS_OPEN	tos;
					char		*pProjekt, *pUser, *pPassWord;

					pProjekt = name.GetBuffer( 0 );
					pUser = pProjekt;

					while ( *pUser ) pUser++;
					pPassWord = pUser;

					tos.dwSize     = sizeof( TRIAS_OPEN );
					tos.lpProject  = pProjekt;
					tos.lpUser     = pUser;
					tos.lpPassWord = pPassWord;
					tos.iMode      = 0;     // Standardsicht zeigen!

					DEX_OpenProject( tos );
/*
				if (( DEX_GetIdentFromClassName( "Grundstück" ) != 0L ) &&
					( DEX_GetMCodeFromFeatureName( "Identifikationsnummer" ) != 0L ))
					m_bIntegratedProjekt = TRUE;
				else
					m_iOISY = -1;
*/
					ide = page2 -> m_strIDE;
					ide2 = page2 -> m_strIDE2;
					if ( m_bIntegratedProjekt )
					{
						MWind() -> BeginWaitCursor();

						if ( g_iMessageStatus >= 1 )
						{
							text = "Ausführen Recherche";
							DEX_SetMessageString((const char*)text );
						}
						SwitchDatenListeDlg( true, false );

//					m_pDatenListeDlg -> RegisterProjekt();

						if ( ide.GetLength() > 4 )
							SwitchDatenListeDlg( true, true );

//					m_pDatenListeDlg -> AddGS( ide );
//					m_pDatenListeDlg -> AddGS( ide2 );
						m_pDatenListeDlg -> AddGS( ide, ide2 );
						MWind() -> EndWaitCursor();
						text.LoadString( IDS_BEREIT );
						DEX_SetMessageString((const char*)text );
					}
				}
			}
			break;
		case 1:		// MRU öffnen
			if (( page1 -> m_iMRU >= 0 ) && ( page1 -> m_iMRU < 4 ))
				AfxGetMainWnd() -> PostMessage( WM_COMMAND,
							8001 + page1 -> m_iMRU, 0L );
			break;
		case 2:
			AfxGetMainWnd() -> PostMessage( WM_COMMAND, 101, 0L );
			break;
		}
	}

	delete page1;
	delete page2;
	return result;
}

void CGbmTRiASExtension::OnAbout()
{
	CAbout	dlg( MWind());

	dlg.m_bManagerFlag = m_bUseProjectManager;
	if ( dlg.DoModal() == IDOK )
		m_bUseProjectManager = dlg.m_bManagerFlag;
}

void CGbmTRiASExtension::OnProjektOpen()
{
	CString		text;
	char		*txt;

	txt = text.GetBuffer( 1024 );
	DEX_GetActiveProject( txt );
	text.ReleaseBuffer();
	text.MakeUpper();

	if ( text.IsEmpty())	return;

	m_bInitialisiert = false;

	m_bIntegratedProjekt = (( m_iVerzNr = IstProjektIntegriert( text )) >= 0 );

	m_bIntegrierbar = FALSE;
	if ( m_bIntegratedProjekt )
	{
		MWind() -> BeginWaitCursor();

		m_iOISY = m_pSetTriDB -> FindOISY( m_iVerzNr );

		text = "Initialisiere GBM-Datenbank";
		DEX_SetMessageString((const char*)text );
		SwitchDatenListeDlg( true, false );

		m_pDatenListeDlg -> RegisterProjekt();

		InitZusatzFunktionen( TRUE );

		MWind() -> EndWaitCursor();
		text.LoadString( IDS_BEREIT );
		DEX_SetMessageString((const char*)text );

		if ( NULL != m_pObjProp )
		{
			g_ulOPAngeschlGS = m_pObjProp -> AddPropertyFunction( g_pOPAngeschlGS );
			g_ulOPBeitragsartGS = m_pObjProp -> AddPropertyFunction( g_pOPBeitragsartGS );
			g_ulOPEigentumGS = m_pObjProp -> AddPropertyFunction( g_pOPEigentumGS );
			g_ulOPGedrucktGS = m_pObjProp -> AddPropertyFunction( g_pOPGedrucktGS );
			g_ulOPGedruck2GS = m_pObjProp -> AddPropertyFunction( g_pOPGedruck2GS );

			g_ulOP_AGGS = m_pObjProp -> AddPropertyFunction( g_pOP_AGGS );
			g_ulOP_FLG = m_pObjProp -> AddPropertyFunction( g_pOP_FLG );
			g_ulOP_GEFS = m_pObjProp -> AddPropertyFunction( g_pOP_GEFS );
			g_ulOP_TIEB = m_pObjProp -> AddPropertyFunction( g_pOP_TIEB );
			g_ulOP_KAT = m_pObjProp -> AddPropertyFunction( g_pOP_KAT );
			g_ulOP_FLN = m_pObjProp -> AddPropertyFunction( g_pOP_FLN );
			g_ulOP_TIEF = m_pObjProp -> AddPropertyFunction( g_pOP_TIEF );
		}

		g_pOPAngeschlGS -> InitData();
	}
	else
	{
		if (( DEX_GetIdentFromClassName( "Grundstück" ) != 0L ) &&
			( DEX_GetMCodeFromFeatureName( "Identifikationsnummer" ) != 0L ))
				m_bIntegrierbar = TRUE;
		else
				m_iOISY = -1;
	}

	m_bInitialisiert = true;
}

short CGbmTRiASExtension::IstProjektIntegriert( const char *name )
{
	return m_pSetVerz -> IstProjektIntegriert( name );
}

void CGbmTRiASExtension::OnPrint()
{
	if ( !PreparePrintAnlage( FALSE ))	return;

	CPrintHandler	han;

	m_bProcessPrinting = TRUE;
	han.m_pPrintListe = &m_arrPrintList;
	han.Print();
	m_bProcessPrinting = FALSE;

	if ( DEX_IsGeoDBDirty())
		DEX_FlushModifications();	// um die Rückfrage zu unterdrücken und die
									// ObjektVisInfo zu speichern!
	DEX_RePaint();
}

void CGbmTRiASExtension::OnPrintPreview()
{
	if ( !PreparePrintAnlage())	return;

	CPreviewDialog	dlg( AfxGetMainWnd());

	m_bProcessPrinting = TRUE;
	dlg.m_pPrintListe = &m_arrPrintList;
	if ( m_pDatenListeDlg == NULL )	dlg.m_bWithOptionDialog = TRUE;

	dlg.DoModal();
	m_bProcessPrinting = FALSE;

	if ( m_pDatenListeDlg )		// OR-Wnd Wiederherstellen
		m_pDatenListeDlg -> SyncListen( TRUE );

	if ( DEX_IsGeoDBDirty())
		DEX_FlushModifications();	// um die Rückfrage zu unterdrücken und die
									// ObjektVisInfo zu speichern!
}

CString CGbmTRiASExtension::OrtVonIDE( const char* ide )
{
	ASSERT( AfxIsValidString( ide ));
	CString		result, strIDE;
	int			i;

	if ( m_arrOrte.GetSize() == 0 )
	{
		if ( m_pSetOrte != NULL )
		{
			m_pSetOrte -> InitListen();
			m_pSetOrte -> MoveFirst();
			while ( !m_pSetOrte -> IsEOF())
			{
				m_arrOrte.SetAtGrow((int)m_pSetOrte -> m_ORT_ISY, m_pSetOrte -> m_ORT_NAM );
				m_pSetOrte -> MoveNext();
			}
		}
		else
			return result;
	}

	strIDE = ide;
	if ( strIDE.GetLength() < 2 )	return result;

	if ( strIDE.GetLength() > 2 )	strIDE = strIDE.Left( 2 );

	i = String2OISY( strIDE );
	if (( i >= 0 ) && ( i < m_arrOrte.GetSize()))	result = m_arrOrte[i];

	return result;
}	// OrtVonIDE

CString CGbmTRiASExtension::StrasseVonIDE( const char* ide )
{
	ASSERT( AfxIsValidString( ide ));
	CString		result, strIDE;
	int			i, n;

	if ( m_pSetStrasse )
	{
		m_pSetStrasse -> InitListen();
		strIDE = ide;
		if ( strIDE.GetLength() > 2 )	strIDE = strIDE.Left( 2 );
		i = String2OISY( strIDE );
		n = m_pSetStrasse -> GetZahlStrassen( i );
		if ( n > 0 )
			m_pmapStrassen = m_pSetStrasse -> GetStrassen( i );
		else
			m_pmapStrassen = NULL;
	}
	else
		return result;

	strIDE = ide;
	if ( strIDE.GetLength() < 5 )	return result;

	if ( strIDE.GetLength() > 5 )	strIDE = strIDE.Left( 5 );
	if ( strIDE.GetLength() == 5 )	strIDE = strIDE.Right( 3 );

	if ( m_pmapStrassen )	m_pmapStrassen -> Lookup( strIDE, result );

	return result;
}	// StrasseVonIDE



//=======================================================
//	Hilfsroutinen für PreparePrintList
//=======================================================
void CopyListe1( CStringArray *a1, CStringArray *a2, char a )
{
	CString		text;

	for ( short i = 0; i < a1 -> GetSize(); i++ )
	{
		text = a;
		text += a1 -> GetAt( i );
		a2 -> Add( text );
	}
}	// CopyListe1

void CopyListe2( CStringArray *a1, CStringArray *a2, char a, char b )
{
	CString		text;

	for ( short i = 0; i < a1 -> GetSize(); i++ )
	{
		text = a;
		text += a1 -> GetAt( i );
		a2 -> Add( text );

		text = b;
		text += a1 -> GetAt( i );
		a2 -> Add( text );
	}
}	// CopyListe2

void CopyListe3( CStringArray *a1, CStringArray *a2, char a, char b, char c )
{
	CString		text;

	for ( short i = 0; i < a1 -> GetSize(); i++ )
	{
		text = a;
		text += a1 -> GetAt( i );
		a2 -> Add( text );

		text = b;
		text += a1 -> GetAt( i );
		a2 -> Add( text );

		if ( c != '\0' )
		{
		text = c;
		text += a1 -> GetAt( i );
		a2 -> Add( text );
		}
	}
}	// CopyListe3

//	Erstellt eine Liste der zu druckenden Dokumente
//	1.Param:	Array mit den zu verwendenden IDE's (kann NULL sein)
//	2.Param:	Ident für einzelnes Grundstück (kann NULL sein)
//	( sind 1. und 2.Param NULL, so werden die gewählten Anlagen für 
//	  alle GS der Datenbank gedruckt!)
//	3.Param:	== 0	==> Einzelgrundstück
//				== 1	==> Straße
//				== 2	==> Ortslage
//				== 3	==> Gesamt
//				== 4	==> Selektiere GS
//				== 5	==> Markierte GS
//	4.Param:	== 1	==> Anlage 1
//				== 2	==> Anlage 2
//				== 3	==> Anlage 3
//				== 4	==> Anlage 1 bis 3
//				== 5	==> Anlage 4
//				== 6	==> Anlage 5
//				== 7	==> Anlage 4 und 5
//				== 8	==> Anlage -öff. Flächen-
//	5.Param:	TRUE	sortiert nach Anlagen
//				FALSE	sortiert nach Grundstücken
//
// ist im großen und ganzen Geschichte!!
//	4.Param:	Bit   1   ==> Anlage 1
//	            Bit   2   ==> Anlage 2
//				Bit   4   ==> Anlage 3
//	            Bit   8   ==> Geb.bescheid 1
//	            Bit  16   ==> Infobrief 1
//	            Bit  32   ==> Anlage
//	            Bit  64   ==> Geb.bescheid 2
//	            Bit 128   ==> Infobrief 2
//	            Bit 256   ==> Anlage
void CGbmTRiASExtension::PreparePrintListe( CStringArray* pArrayID, const char* ide,
										    int mode, int anla, BOOL sort )
{
	CStringArray	idents;
	CStringArray	identsB;
	CSetNF_PG1		NFPG1;
//	CSetNF_PG3		NFPG3;
	CSetNF_OG1		NFOG1;
	CString			strID;
	int				i;
	int				a1, a2, a3, a4;

	a1 = anla & 07;
	a2 = anla & 070;
	a3 = anla & 0700;
	a4 = anla & 07000;
	a2 /= 8;
	a3 /= 64;
	a4 /= 512;

//	NFPG1.Open();
//	NFPG3.Open();
	AfxGetMainWnd() -> BeginWaitCursor();
	m_arrPrintList.RemoveAll();
	switch ( mode )
	{
		case 0:	//	==> Einzelgrundstück
			ASSERT( AfxIsValidString( ide ));
			idents.Add( ide );
			break;
		case 1:	//	==> Straße
		case 2:	//	==> Ortslage
		case 4:	//	==> Liste
		case 5:	//	==> Selektion
			for ( i = 0; i < pArrayID -> GetSize(); i++ )
				idents.Add( pArrayID -> GetAt( i ));
			break;
		case 3:	//	==> Gesamt
			NFPG1.Open();
			NFPG1.MoveFirst();
			while ( !NFPG1.IsEOF())
			{
				idents.Add( NFPG1.m_NFP1_IDE );
				NFPG1.MoveNext();
			}
			NFPG1.Close();
			break;
	}

	for ( i = 0; i < idents.GetSize(); i++ )
		identsB.Add( idents[i]);

	if ( idents.GetSize() > 0 )
	{
		strID = idents[0];
		g_pNF_PG1 -> InitListen( strID );
	}

	if ( a2 != 0 )
	{
		g_pNF_PG1 -> TestPrintBB( &identsB );
//		g_pNF_PG1 -> TestPrintGB( &identsB );
		if ( m_pNF_PG3 == NULL )	m_pNF_PG3 = new CSetNF_PG3( g_pDatabase );
		ASSERT( m_pNF_PG3 );
		if ( !m_pNF_PG3 -> IsOpen())	m_pNF_PG3 -> Open();
		else							m_pNF_PG3 -> Requery();
		m_pNF_PG3 -> TestPrintIDE( &identsB );
	}
	g_pNF_PG4 -> TestPrintIDE( &idents );
	g_pNF_PG4 -> TestPrintIDE( &identsB );
//	NFPG1.TestPrintIDE( &identsB );
//	NFPG3.TestPrintIDE( &identsB );

//	NFPG1.Close();
//	NFPG3.Close();
	switch ( a1 )
	{
		case 1:		// Anlage 1
			CopyListe1( &idents, &m_arrPrintList, '1' );
			break;
		case 2:		// Anlage 2
			CopyListe1( &idents, &m_arrPrintList, '2' );
			break;
		case 3:		// Anlage 1 + 2
			CopyListe3( &idents, &m_arrPrintList, '1', '2', '\0' );
			break;
		case 4:		// Anlage 3
			CopyListe1( &idents, &m_arrPrintList, '3' );
			break;
		case 5:		// Anlage 1 + 3
			CopyListe3( &idents, &m_arrPrintList, '1', '3', '\0' );
			break;
		case 6:		// Anlage 2 + 3
			CopyListe3( &idents, &m_arrPrintList, '2', '3', '\0' );
			break;
		case 7:		// Anlage 1 + 2 + 3
			CopyListe3( &idents, &m_arrPrintList, '1', '2', '3' );
			break;
	}
	switch ( a2 )
	{
		case 1:		// Bescheid 1
			CopyListe1( &identsB, &m_arrPrintList, '4' );
			break;
		case 2:		// InfoBrief 1
			CopyListe1( &identsB, &m_arrPrintList, '5' );
			break;
		case 3:		// Bescheid + InfoBrief 1
			CopyListe3( &identsB, &m_arrPrintList, '4', '5', '\0' );
			break;
		case 4:		// Anlage zu Bescheid 1
			CopyListe1( &identsB, &m_arrPrintList, '6' );
			break;
		case 5:		// Bescheid + Anlage zu 1
			CopyListe3( &identsB, &m_arrPrintList, '4', '6', '\0' );
			break;
		case 6:		// InfoBrief + Anlage zu 1
			CopyListe3( &identsB, &m_arrPrintList, '5', '6', '\0' );
			break;
		case 7:		// Bescheid + InfoBrief + Anlage zu 1
			CopyListe3( &identsB, &m_arrPrintList, '4', '5', '6' );
			break;
	}
	switch ( a3 )
	{
		case 1:		// Bescheid 2
			CopyListe1( &idents, &m_arrPrintList, '7' );
			break;
		case 2:		// InfoBrief 2
			CopyListe1( &idents, &m_arrPrintList, '8' );
			break;
		case 3:		// Bescheid + InfoBrief 2
			CopyListe3( &idents, &m_arrPrintList, '7', '8', '\0' );
			break;
		case 4:		// Anlage zu Bescheid 2
			CopyListe1( &idents, &m_arrPrintList, '9' );
			break;
		case 5:		// Bescheid + Anlage zu 2
			CopyListe3( &idents, &m_arrPrintList, '7', '9', '\0' );
			break;
		case 6:		// InfoBrief + Anlage zu 2
			CopyListe3( &idents, &m_arrPrintList, '8', '9', '\0' );
			break;
		case 7:		// Bescheid + InfoBrief + Anlage zu 2
			CopyListe3( &idents, &m_arrPrintList, '7', '8', '9' );
			break;
	}

	if ( 1 == a4 )
	{		// Massstabsgerechte Lageskizze -
		CopyListe1( &idents, &m_arrPrintList, 'B' );
	}

	AfxGetMainWnd() -> EndWaitCursor();

if ( TRUE )	return;

	AfxGetMainWnd() -> BeginWaitCursor();
	m_arrPrintList.RemoveAll();
	if ( anla == 8 )
	{
		if ( ide == NULL )
		{
			strID = ide;
			if ( strID.GetLength() < 2 )	return;
		}

		NFOG1.Open();
		switch ( mode )
		{
			case 0:	//	==> Einzelgrundstück (nicht sinnvoll)
			case 4:	//	==> willk. Selektion (nicht sinnvoll)
			case 5:	//
				break;
			case 1:	//	==> Straße
				strID = strID.Left( 5 );
				NFOG1.MoveFirst();
				while ( !NFOG1.IsEOF())
				{
					if (( NFOG1.m_NFO1_IDE == strID ))
						idents.Add( NFOG1.m_NFO1_IDE );
					NFOG1.MoveNext();
				}
				break;
			case 2:	//	==> Ortslage
				strID = strID.Left( 2 );
				NFOG1.MoveFirst();
				while ( !NFOG1.IsEOF())
				{
					if ( NFOG1.m_NFO1_IDE.Left( 2 ) == strID )
						idents.Add( NFOG1.m_NFO1_IDE );
					NFOG1.MoveNext();
				}
				break;
			case 3:	//	==> Gesamt
				NFOG1.MoveFirst();
				while ( !NFOG1.IsEOF())
				{
					idents.Add( NFOG1.m_NFO1_IDE );
					NFOG1.MoveNext();
				}
				break;
		}
		NFOG1.Close();
	}
	else
	{
		switch ( mode )
		{
			case 0:	//	==> Einzelgrundstück
				ASSERT( AfxIsValidString( ide ));
				idents.Add( ide );
				break;
			case 1:	//	==> Straße
			case 2:	//	==> Ortslage
			case 4:	//	==> Liste
			case 5:	//	==> Selektion
				for ( i = 0; i < pArrayID -> GetSize(); i++ )
					idents.Add( pArrayID -> GetAt( i ));
				break;
			case 3:	//	==> Gesamt
				NFPG1.Open();
				NFPG1.MoveFirst();
				while ( !NFPG1.IsEOF())
				{
					idents.Add( NFPG1.m_NFP1_IDE );
					NFPG1.MoveNext();
				}
				NFPG1.Close();
				break;
		}
	}

	if ( sort )
	{
		switch ( anla )
		{
			case 1:		// Anlage 1
				CopyListe1( &idents, &m_arrPrintList, '1' );
				break;
			case 2:		// Anlage 2
				CopyListe1( &idents, &m_arrPrintList, '2' );
				break;
			case 3:		// Anlage 3
				CopyListe1( &idents, &m_arrPrintList, '3' );
				break;
			case 4:		// Anlage 1 bis 3
				CopyListe1( &idents, &m_arrPrintList, '1' );
				CopyListe1( &idents, &m_arrPrintList, '2' );
				CopyListe1( &idents, &m_arrPrintList, '3' );
				break;
			case 5:		// Anlage 4
				CopyListe1( &idents, &m_arrPrintList, '4' );
				break;
			case 6:		// Anlage 5
				CopyListe1( &idents, &m_arrPrintList, '5' );
				break;
			case 7:		// Anlage 4 & 5
				CopyListe1( &idents, &m_arrPrintList, '4' );
				CopyListe1( &idents, &m_arrPrintList, '5' );
				break;
			case 8:		// Anlage - öff.Flächen -
				CopyListe1( &idents, &m_arrPrintList, '6' );
				break;
			case 9:		// Massstabsgerechte Lageskizze -
				CopyListe1( &idents, &m_arrPrintList, 'B' );
				break;
		}
	}
	else
	{
		switch ( anla )
		{
			case 1:		// Anlage 1
				CopyListe1( &idents, &m_arrPrintList, '1' );
				break;
			case 2:		// Anlage 2
				CopyListe1( &idents, &m_arrPrintList, '2' );
				break;
			case 3:		// Anlage 3
				CopyListe1( &idents, &m_arrPrintList, '3' );
				break;
			case 4:		// Anlage 1 bis 3
				CopyListe3( &idents, &m_arrPrintList, '1', '2', '3' );
				break;
			case 5:		// Anlage 4
				CopyListe1( &idents, &m_arrPrintList, '4' );
				break;
			case 6:		// Anlage 5
				CopyListe1( &idents, &m_arrPrintList, '5' );
				break;
			case 7:		// Anlage 4 & 5
				CopyListe3( &idents, &m_arrPrintList, '4', '5', '\0' );
				break;
			case 8:		// Anlage - öff.Flächen -
				CopyListe1( &idents, &m_arrPrintList, '6' );
				break;
			case 9:		// Massstabsgerechte Lageskizze -
				CopyListe1( &idents, &m_arrPrintList, 'B' );
				break;
		}
	}

	AfxGetMainWnd() -> EndWaitCursor();
}

BOOL CGbmTRiASExtension::PreparePrintAnlage( BOOL bPreview )
{
//	CPrintAnlaDialog	padlg;
	CDlgSelPrint		padlg;

	CxString			txt, ide, strID;
	CStringArray		arrID1;		// Straße
	CStringArray		arrID2;		// Ort
	CStringArray		arrID3;		// Selektion
	CStringArray		arrID4;		// Markierung

	if ( bPreview )
		txt.LoadString( IDS_PREVIEWCAPTION );
	else
		txt.LoadString( IDS_PRINTCAPTION );

	if ( !txt.IsEmpty())
		padlg.m_strCaption = txt;

	if ( g_pNF_PG1 == NULL )	g_pNF_PG1 = new CSetNF_PG1( g_pDatabase );
	ASSERT( g_pNF_PG1 );

	if ( m_pDatenListeDlg == NULL )	return TRUE;	// nichts zu drucken!!

	AfxGetMainWnd() -> BeginWaitCursor();

	ide = m_pDatenListeDlg -> AktIDE();
	strID = ide;
	if ( strID.GetLength() > 2 )	strID = strID.Left( 2 );
	g_pNF_PG1 -> InitListen( strID );

	strID = ide;
	if ( strID.GetLength() > 5 )	strID = strID.Left( 5 );
	if ( strID.GetLength() > 4 )	g_pNF_PG1 -> Add2Array( strID, &arrID1 );

	strID = ide;
	if ( strID.GetLength() > 2 )	strID = strID.Left( 2 );
	if ( strID.GetLength() > 1 )	g_pNF_PG1 -> Add2Array( strID, &arrID2 );

	m_pDatenListeDlg -> CopyArrayID( arrID3 );
	m_pDatenListeDlg -> CopyArraySelID( arrID4 );

	padlg.m_strIDE = ide;
	txt = "Grundstück: ";
	txt += padlg.m_strIDE;
	padlg.m_strGrund = txt;
	txt = "Straße: ";
	txt += StrasseVonIDE( ide );
	padlg.m_strStr = txt;
	txt = "Gemeinde: ";
	txt += OrtVonIDE( ide );
	padlg.m_strOrt = txt;
	padlg.m_strOrte = "Gesamtprojekt";
	padlg.m_strSelected = "Ausgewählte Grundstücke";
	padlg.m_strMarked = "Markierte Grundstücke";
	padlg.m_iA1 = arrID1.GetSize();
	padlg.m_iA2 = arrID2.GetSize();
	padlg.m_iA3 = 2500;
	padlg.m_iA4 = m_pDatenListeDlg -> AnzahlSelectedGS();
	padlg.m_iA5 = m_pDatenListeDlg -> AnzahlMarkedGS();

	AfxGetMainWnd() -> EndWaitCursor();
	
	if ( padlg.DoModal() != IDOK )	return FALSE;

	switch ( padlg.m_iUmfang )
	{
	case 0:		// Einzelgrundstück
		PreparePrintListe( NULL, ide, 0, padlg.m_iSelAnlaMode, padlg.m_bSort );
		break;
	case 1:		// Strasse
		PreparePrintListe( &arrID1, ide, 1, padlg.m_iSelAnlaMode, padlg.m_bSort );
		break;
	case 2:		// Ortslage
		PreparePrintListe( &arrID2, ide, 2, padlg.m_iSelAnlaMode, padlg.m_bSort );
		break;
	case 3:		// Gesamtprojekt
		PreparePrintListe( NULL, NULL, 3, padlg.m_iSelAnlaMode, padlg.m_bSort );
		break;
	case 4:		// Ausgewählte GS
		PreparePrintListe( &arrID3, NULL, 4, padlg.m_iSelAnlaMode, padlg.m_bSort );
		break;
	case 5:		// Markierte GS
		PreparePrintListe( &arrID4, NULL, 5, padlg.m_iSelAnlaMode, padlg.m_bSort );
		break;
	}

	if ( m_arrPrintList.GetSize() == 0 )
	{
		AfxMessageBox( IDS_NOANLAGETOPRINT, MB_OK|MB_ICONINFORMATION );
		return FALSE;
	}

	return TRUE;
}	// PreparePrintAnlage

void CGbmTRiASExtension::OnFlaechenberechnung()
{
	ExecuteBasicScript( IDR_MACRO1 );

	CFlAbgleichDlg		dlg;
	short				n;

	if ( m_pDatenListeDlg )
		n = m_pDatenListeDlg -> AnzahlMarkedGS();

	dlg.m_iAnzahlGS = n;
	if ( dlg.DoModal() == IDOK )
		if ( m_pDatenListeDlg )
	{
		m_pDatenListeDlg -> RefreshNFPG1();
		m_pDatenListeDlg -> RefreshGebDB();
		m_pDatenListeDlg -> RefreshDTDB();
		m_pDatenListeDlg -> RefreshVFDB();
	}
	UpdateORWnd((HWND)NULL, TRUE );
}

void CGbmTRiASExtension::OnTiefenbegrenzung()
{
	CDlgTB	dlg;

	if ( dlg.DoModal() == IDOK )
	{
		ExecuteBasicScript( IDR_MACRO2 );
		if ( m_pDatenListeDlg )
			m_pDatenListeDlg -> RefreshNFPG1();
	}
	UpdateORWnd((HWND)NULL, TRUE );
}

void CGbmTRiASExtension::OnBeitragBerechnen()
{
	CCalculator		calc;
	CString			ide;

	ide = m_pDatenListeDlg -> AktIDE();
	if ( ide.IsEmpty())		return;

	if ( g_pNF_PG1 == NULL )
	{
		g_pNF_PG1 = new CSetNF_PG1( g_pDatabase );
		ASSERT( g_pNF_PG1 );
		g_pNF_PG1 -> InitListen( ide );
	}
	if ( g_pNF_PG2H == NULL )	g_pNF_PG2H = new CSetNF_PG2H( g_pDatabase );
	ASSERT( g_pNF_PG2H );
	if ( g_pNF_PG2D == NULL )	g_pNF_PG2D = new CSetNF_PG2D( g_pDatabase );
	ASSERT( g_pNF_PG2D );
	if ( g_pNF_PG1GB == NULL )	g_pNF_PG1GB = new CSetNF_PG1GB( g_pDatabase );
	ASSERT( g_pNF_PG1GB );
	if ( g_pNF_PG4 == NULL )	g_pNF_PG4 = new CSetNF_PG4( g_pDatabase );
	ASSERT( g_pNF_PG4 );
	if ( m_pNF_PG3 == NULL )
	{
		m_pNF_PG3 = new CSetNF_PG3( g_pDatabase );
		ASSERT( m_pNF_PG3 );
		m_pNF_PG3 -> InitListen( ide );
	}

//	calc.m_pNF_PG1   = g_pNF_PG1;
//	calc.m_pNF_PG2H  = g_pNF_PG2H;
//	calc.m_pNF_PG2D  = g_pNF_PG2D;
//	calc.m_pNF_PG1GB = g_pNF_PG1GB;
	calc.m_pNF_PG3   = m_pNF_PG3;

	if ( m_pDatenListeDlg -> AnzahlMarkedGS() == 1 )
	{
		CxString	strKontrolle;

		strKontrolle.GetPrivateProfileString( "BeitragKontrolle", "Dialog", "GBM.INI" );
		strKontrolle.MakeUpper();
		if ( "JA" == strKontrolle )
		{
			calc.m_strIDE    = ide;
			calc.StartDialog();
		}
		else
		{
			m_pDatenListeDlg -> CopyArraySelID( calc.m_arrIDE );
			calc.Calculate();
		}
	}
	else
	{
		m_pDatenListeDlg -> CopyArraySelID( calc.m_arrIDE );
		calc.Calculate();
	}

	m_pDatenListeDlg -> RefreshNFPG1();

}	// OnBeitragBerechnen

extern "C" const GUID __based(__segname("_CODE")) CLSID_MacroScriptExtension \
                    = { 0xED9655CFL, 0x3122, 0x101C, { 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C } };

extern "C" const GUID __based(__segname("_CODE")) IID_IExtendBScript \
                    = { 0x0796380AL, 0x3123, 0x101C, { 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C } };

void CGbmTRiASExtension::ExecuteBasicScript( int id )
{
	CString	strDBName;
	CString	strTRiASPfad;
	char	*txt1, *txt2;

	if ( !m_pScript)
	{
		HRESULT hr = 0;

		if ( g_pTE -> m_pXtnSite )
			hr = g_pTE -> m_pXtnSite -> GetXtension( CLSID_MacroScriptExtension, IID_IExtendBScript, (LPVOID*)&m_pScript);

		if ( FAILED( hr ) ||	// Fehler
			!g_pTE -> m_pXtnSite )
			return;
	}

	ebPARAM PA[3];

	PA[0].wType = 0;
	PA[0].szExtType[0] = '\0';
	PA[1].wType = TYP_STRING;
	PA[1].szExtType[0] = '\0';
	PA[2].wType = TYP_STRING;
	PA[2].szExtType[0] = '\0';

//	PA[1].wType = TYP_APPOBJECT;
//	strcpy (PA[1].szExtType, "GeoObject");

	LPVOID pTyp = NULL;

	strDBName = GetDefaultDBName();
	strTRiASPfad = GetTRiASPfad();

//CxString	test;
//test = strDBName;
//test = strTRiASPfad;
//test += "Macro\\Logo.BMP";
//if ( !test.FileExist())
//	AfxMessageBox( test );

	txt1 = strTRiASPfad.GetBuffer( 128 );
	txt2 = strDBName.GetBuffer( 128 );
	LPVOID pVals[3] = { NULL, txt1, txt2 };

	BSPARAM BS;
	BS.pTypes = PA;
	BS.pValues = pVals;

	if ( m_pScript)
		m_pScript -> RunCode( g_hInstance, id, "Start", 2, &BS );
	else
		AfxMessageBox( "MacroScript-Erweiterung ist nicht verfügbar!" );

	strDBName.ReleaseBuffer();
}

void CGbmTRiASExtension::ExecuteBasicScriptRes( UINT resid, const char* param )
{
	ASSERT( AfxIsValidString( param ));
	if ( !AfxIsValidString( param ))	return;

	CxString	result, strFktName;
	int			intResult;

	strFktName = param;
	strFktName.Teilen( result, strFktName, ' ' );
	if ( strFktName.IsEmpty())
		strFktName = "Main";

	if ( !m_pScript)
	{
		HRESULT hr = 0;

		if ( g_pTE -> m_pXtnSite )
			hr = g_pTE -> m_pXtnSite -> GetXtension( CLSID_MacroScriptExtension, IID_IExtendBScript, (LPVOID*)&m_pScript);

		if ( FAILED( hr ) ||	// Fehler
			!g_pTE -> m_pXtnSite )
			return;
	}

	ebPARAM PA[3];

	PA[0].wType = 0;
	PA[0].szExtType[0] = '\0';
	PA[1].wType = TYP_STRING;
	PA[1].szExtType[0] = '\0';
	PA[2].wType = TYP_STRING;
	PA[2].szExtType[0] = '\0';

	LPVOID pTyp = NULL;

//	strDBName = GetDefaultDBName();
//	strTRiASPfad = GetTRiASPfad();

//	txt1 = strTRiASPfad.GetBuffer( 128 );
//	txt2 = strDBName.GetBuffer( 128 );
//	LPVOID pVals[3] = { NULL, txt1, txt2 };
	LPVOID pVals[3] = { NULL, NULL, NULL };
	if ( *param == 'F' )
	{
		pVals[0] = &intResult;
		PA[0].wType = TYP_INTEGER;
	}

	BSPARAM BS;
	BS.pTypes = PA;
	BS.pValues = pVals;

	if ( m_pScript)
//		m_pScript -> RunCode( g_hInstance, id, "Start", 2, &BS );
		m_pScript -> RunCode( g_hInstance, resid, strFktName, 0, &BS );
	else
		AfxMessageBox( "MacroScript-Erweiterung ist nicht verfügbar!" );
}

void CGbmTRiASExtension::ExecuteBasicScript( const char* filename, const char* param )
{
	ASSERT( AfxIsValidString( filename ));
	ASSERT( AfxIsValidString( param ));
	if ( !AfxIsValidString( filename ))	return;
	if ( !AfxIsValidString( param ))	return;

	CxString	name( filename );
	CxString	result, strFktName;
	int			intResult;
	char		*resTxt;

	if ( !name.FileExist())		return;

	strFktName = param;
	strFktName.Teilen( result, strFktName, ' ' );
	if ( strFktName.IsEmpty())
		strFktName = "Main";

	try {
	CFile	datei( filename, CFile::modeRead );
	DWORD	laenge;
	HRESULT	hRes;
	char	*txt;

		laenge = datei.GetLength();
		if ( laenge < 62000 )
		{
			txt = new char[laenge+2];

			if ( txt != NULL )
			{
				datei.Read((void*)txt, laenge );
				txt[laenge] = '\0';

				if ( !m_pScript)
				{
					HRESULT hr = 0;

					if ( g_pTE -> m_pXtnSite )
						hr = g_pTE -> m_pXtnSite -> GetXtension( CLSID_MacroScriptExtension, IID_IExtendBScript, (LPVOID*)&m_pScript);

					if ( FAILED( hr ) ||	// Fehler
						!g_pTE -> m_pXtnSite )
						return;
				}

				ebPARAM PA[3];

				PA[0].wType = 0;
				PA[0].szExtType[0] = '\0';
				PA[1].wType = TYP_STRING;
				PA[1].szExtType[0] = '\0';
				PA[2].wType = TYP_STRING;
				PA[2].szExtType[0] = '\0';

				LPVOID pTyp = NULL;

//				strDBName = GetDefaultDBName();
//				strTRiASPfad = GetTRiASPfad();

//				txt1 = strTRiASPfad.GetBuffer( 128 );
//				txt2 = strDBName.GetBuffer( 128 );
//				LPVOID pVals[3] = { NULL, txt1, txt2 };
				resTxt = result.GetBuffer( 128 );
				LPVOID pVals[3] = { NULL, NULL, NULL };
				if ( *param == 'F' )
				{
					pVals[0] = &intResult;
					PA[0].wType = TYP_INTEGER;
				}

				BSPARAM BS;
				BS.pTypes = PA;
				BS.pValues = pVals;

				if ( m_pScript)
				{
					hRes = m_pScript -> RunText( txt, strFktName, 0, &BS );
					if ( FAILED( hRes ))
						AfxMessageBox( "Fehler bei Ausführung eines Makros!" );
				}
				else
					AfxMessageBox( "MacroScript-Erweiterung ist nicht verfügbar!" );

				result.ReleaseBuffer();
				delete [] txt;
			}
			else
				AfxMessageBox( "Zu wenig Speicher!" );
		}
		else
			AfxMessageBox( "Makro-Datei ist zu groß!" );
	}
	catch (...) {

		AfxMessageBox( "Nicht ausreichend Speicher verfügbar!" );
	}
}

void CGbmTRiASExtension::ExecuteBasicScriptLoc( const char* script, const char* param )
{
	ASSERT( AfxIsValidString( script ));
	if ( !AfxIsValidString( script ))	return;

	CString		strParam;

	if ( AfxIsValidString( param ))
		strParam = param;
	else
		strParam = "RUN";

	strParam.MakeUpper();

	if ( !m_pScript)
	{
		HRESULT hr = 0;

		if ( g_pTE -> m_pXtnSite )
			hr = g_pTE -> m_pXtnSite -> GetXtension( CLSID_MacroScriptExtension, IID_IExtendBScript, (LPVOID*)&m_pScript);

		if ( FAILED( hr ) ||	// Fehler
			!g_pTE -> m_pXtnSite )
			return;
	}

	if ( m_pScript)
	{
		if ( strParam == "STOP" )
			m_pScript -> StopScript( script );
		else
			m_pScript -> RunScript( script );
	}
	else
		AfxMessageBox( "MacroScript-Erweiterung ist nicht verfügbar!" );
}

//	Startet ein Visualisierungsmakro und übergibt folgende Parameter:
//	  klasse:	Objektklasse deren Objekte eine Visualisierung erhalten sollen
//	  prop:		ObjektEigenschaft, deren Wert die Visualisierung steuern soll
//	  wert:		gesuchter Wert von prop
//	  col:		einzustellende Farbe
void CGbmTRiASExtension::PrepareVisu( const char* klasse, const char* prop,
									  const char* wert, COLORREF col )
{
	if ( !m_pScript)
	{
		HRESULT hr = 0;

		if ( g_pTE -> m_pXtnSite )
			hr = g_pTE -> m_pXtnSite -> GetXtension( CLSID_MacroScriptExtension, IID_IExtendBScript, (LPVOID*)&m_pScript);

		if ( FAILED( hr ) ||	// Fehler
			!g_pTE -> m_pXtnSite )
			return;
	}

	ebPARAM PA[5];

	PA[0].wType = 0;
	PA[0].szExtType[0] = '\0';
	PA[1].wType = TYP_STRING;
	PA[1].szExtType[0] = '\0';
	PA[2].wType = TYP_STRING;
	PA[2].szExtType[0] = '\0';
	PA[3].wType = TYP_STRING;
	PA[3].szExtType[0] = '\0';
	PA[4].wType = TYP_LONG;
	PA[4].szExtType[0] = '\0';

	LPVOID pTyp = NULL;

	LPVOID pVals[5] = { NULL, (void*)klasse, (void*)prop, (void*)wert, (void*)&col };

	BSPARAM BS;
	BS.pTypes = PA;
	BS.pValues = pVals;

	if ( m_pScript)
		m_pScript -> RunCode( g_hInstance, IDR_VISU, "StartVisu", 4, &BS );
	else
		AfxMessageBox( "MacroScript-Erweiterung ist nicht verfügbar!" );
}

CString CGbmTRiASExtension::GetDefaultDBName()
{
	CString		result;
	CString		db_name;
	BOOL		bOpened = FALSE;
	char		*txt;

	if ( bOpened = ( m_pSetVerz == NULL ))	m_pSetVerz = new CVerzSet( g_pDatabase );

	db_name = m_pSetVerz -> GetDefaultConnect();
	if ( db_name.Left( 4 ) == "ODBC" )
	{
		txt = result.GetBuffer( 128 );
		db_name = db_name.Mid( 9 );
		SQLGetPrivateProfileString( db_name, "DBQ", "", txt, 127, "ODBC.INI" );
		result.ReleaseBuffer();
	}

	if ( bOpened )
	{
		delete m_pSetVerz;
		m_pSetVerz = NULL;
	}
	return result;
}

CString CGbmTRiASExtension::GetTRiASPfad()
{
	CString		result;
	int			i;

	result = AfxGetApp() -> m_pszHelpFilePath;
	if ( result.GetLength() > 2 )
	{
		i = result.GetLength() - 2;
		while (( i > 0 ) && ( result.GetAt( i ) != '\\' ))	i--;
		if ( i > 0 )	i--;
		while (( i > 0 ) && ( result.GetAt( i ) != '\\' ))	i--;
		if ( i > 0 )	result = result.Left( i + 1 );
	}
	
	return result;
}

void CGbmTRiASExtension::ExecBasicScriptParam( UINT id, const char* p1, const char* p2 )
{
//	char	*txt1, *txt2;

	if ( !m_pScript)
	{
		HRESULT hr = 0;

		if ( g_pTE -> m_pXtnSite )
			hr = g_pTE -> m_pXtnSite -> GetXtension( CLSID_MacroScriptExtension, IID_IExtendBScript, (LPVOID*)&m_pScript);

		if ( FAILED( hr ) ||	// Fehler
			!g_pTE -> m_pXtnSite )
			return;
	}

	ebPARAM PA[3];

	PA[0].wType = 0;
	PA[0].szExtType[0] = '\0';
	PA[1].wType = TYP_STRING;
	PA[1].szExtType[0] = '\0';
	PA[2].wType = TYP_STRING;
	PA[2].szExtType[0] = '\0';

	LPVOID pTyp = NULL;

//	txt1 = p1;
//	txt2 = p2;
	LPVOID pVals[3] = { NULL, (void*)p1, (void*)p2 };

	BSPARAM BS;
	BS.pTypes = PA;
	BS.pValues = pVals;

	if ( m_pScript)
		m_pScript -> RunCode( g_hInstance, id, "Start", 2, &BS );
	else
		AfxMessageBox( "MacroScript-Erweiterung ist nicht verfügbar!" );
}

BOOL FileExist( const char* n )
{
	BOOL			result = TRUE;
	CFileException	e;
	CString			name;
	CFile			file;

	ASSERT( AfxIsValidString( n ));
	name = n;
	ASSERT( name.GetLength());

	file.Open( name, CFile::modeRead|CFile::shareDenyWrite, &e );

	if ( e.m_cause != CFileException::none )
		result = FALSE;
	else
		file.Close();

	return result;
}	// FileExist

BOOL TestYES( const char* text )
{
	CString		wert;
	BOOL		result = FALSE;

	ASSERT( AfxIsValidString( text ));
	if ( AfxIsValidString( text ))
	{
		wert = text;
		wert.MakeUpper();
		result = (( wert == "Y" ) || ( wert == "J" ));
	}

	return result;
}

BOOL IsDoubleOK( double w )
{
	return (( w >= -1.0e10 ) && ( w <= 1.0e10 ));
}

void Fehler( UINT id, const char* str )
{
	CString		text;

	AfxFormatString1( text, id, str );
	AfxMessageBox( text, MB_ICONHAND|MB_OK );
}

void CGbmTRiASExtension::NeueIDE()
{
	long	onr;
	CString	ide;

	onr = m_pDatenListeDlg -> GSohneIDE();
	ide = m_pDatenListeDlg -> GetIdentNummer( onr );
	m_pDatenListeDlg -> Bearbeiten( ide );
}

void CGbmTRiASExtension::EditIDE()
{
	CEditIDEDlg		dlg;
	CString			strOldIDE;
	BOOL			bInDB;
	long			onr = 0L;

	if ( m_pDatenListeDlg -> AnzahlMarkedGS() == 1 )
	{
		strOldIDE = m_pDatenListeDlg -> AktIDE();
		onr = m_pDatenListeDlg -> FindONr( strOldIDE );
		bInDB = TRUE;
	}
	else
	{
		onr = m_pDatenListeDlg -> GSohneIDE();
		strOldIDE = m_pDatenListeDlg -> GetIdentNummer( onr );
		bInDB = FALSE;
	}

	if ( onr == 0L )	return;

	dlg.m_strOldIDE = strOldIDE;
	dlg.m_strNeueIDE = strOldIDE;
	dlg.m_lONr = onr;
	dlg.m_bInDB = bInDB;
	if ( dlg.DoModal() == IDOK )
	{
		if ( dlg.m_bModDB )
		{
			if ( g_pNF_PG1 == NULL )	g_pNF_PG1 = new CSetNF_PG1( g_pDatabase );
			ASSERT( g_pNF_PG1 );
			if ( g_pNF_PG2H == NULL )	g_pNF_PG2H = new CSetNF_PG2H( g_pDatabase );
			ASSERT( g_pNF_PG2H );
			if ( g_pNF_PG2D == NULL )	g_pNF_PG2D = new CSetNF_PG2D( g_pDatabase );
			ASSERT( g_pNF_PG2D );
			if ( g_pNF_PG1GB == NULL )	g_pNF_PG1GB = new CSetNF_PG1GB( g_pDatabase );
			ASSERT( g_pNF_PG1GB );
			if ( g_pNF_PG4 == NULL )	g_pNF_PG4 = new CSetNF_PG4( g_pDatabase );
			ASSERT( g_pNF_PG4 );
			if ( m_pNF_PG1FL == NULL )	m_pNF_PG1FL = new CSetNF_PG1FL( g_pDatabase );
			ASSERT( m_pNF_PG1FL );
			if ( m_pNF_PG3 == NULL )	m_pNF_PG3 = new CSetNF_PG3( g_pDatabase );
			ASSERT( m_pNF_PG3 );

			if ( !g_pNF_PG1 -> ModIDE( strOldIDE, dlg.m_strNeueIDE ))
				return;		// Abgebrochen!
			m_pNF_PG1FL -> ModIDE( strOldIDE, dlg.m_strNeueIDE );
			g_pNF_PG1GB -> ModIDE( strOldIDE, dlg.m_strNeueIDE );
			g_pNF_PG2D -> ModIDE( strOldIDE, dlg.m_strNeueIDE );
			g_pNF_PG2H -> ModIDE( strOldIDE, dlg.m_strNeueIDE );
			g_pNF_PG4 -> ModIDE( strOldIDE, dlg.m_strNeueIDE );
			m_pNF_PG3 -> ModIDE( strOldIDE, dlg.m_strNeueIDE );
			m_pSetTriDB -> ModIDE( strOldIDE, dlg.m_strNeueIDE, m_iVerzNr );
		}

		if ( dlg.m_bModGS )
			m_pDatenListeDlg -> SetIdentNummer( onr, dlg.m_strNeueIDE );
	}
}

void CGbmTRiASExtension::ZusatzFkt()
{
	CDlgZusatzFkt	dlg(MWind());

	dlg.m_arrZF = &m_strarrZusatzFkt;
	dlg.m_arrIM = &m_strarrZusatzFktPro;
	if ( dlg.DoModal() == IDOK )
	{
		if ( !dlg.m_strScriptFileName.IsEmpty())
			ExecuteBasicScript( dlg.m_strScriptFileName, dlg.m_strParameter );
		else if ( dlg.m_uiResID != 0 )
			ExecuteBasicScriptRes( dlg.m_uiResID, dlg.m_strParameter );
		else if ( !dlg.m_strScriptResName.IsEmpty())
			ExecuteBasicScriptLoc( dlg.m_strScriptResName, dlg.m_strParameter );
	}
}

// Callback-Funktion zur Enumeration aller benannten Resourcen
// lParam ist der Zeiger auf ein CStringArray!
BOOL CALLBACK EnumResNameProc( HANDLE hModule, LPCTSTR lpszType,
							   LPTSTR lpszName, LONG lParam )
{
	CStringArray	*pArr = (CStringArray*)lParam;

	ASSERT_VALID( pArr );
	if ( AfxIsValidString( lpszName ))
		pArr -> Add( lpszName );
	return TRUE;
}

void CGbmTRiASExtension::InitZusatzFunktionen( BOOL bOpenPro )
{
	CString		strItemBase( "F" );
	CString		strIniFile;
	CxString	strItem;
	CxString	strFkt;
	short		iNr = 1;

	m_strarrZusatzFkt.RemoveAll();
	m_strarrZusatzFktPro.RemoveAll();

	// Globale externe und interne Zusatzfunktionen:
	// In der GBM.INI stehen die externen Makros ('ebs'-Dateien, die in allen
	// GBM-Projekten in der aktuellen Installation verfügbar sein sollen) in
	// der Form:
	// Fx=[DateiNameMitPfad];[Bezeichnung]
	// sowie ggf. die aktivierbaren internen Makros (in der Resource gebundene,
	// compilierte Scripts) in der Form:
	// Fx=[ResourceID];[Bezeichnung]
	strItem = strItemBase;
	strItem.AppendF( iNr, -1 );
	strFkt.GetPrivateProfileString( "ZusatzFunktionen", strItem, "GBM.INI" );
	while ( !strFkt.IsEmpty())
	{
		m_strarrZusatzFkt.Add( strFkt );
		iNr++;
		strItem = strItemBase;
		strItem.AppendF( iNr, -1 );
		strFkt.Empty();
		strFkt.GetPrivateProfileString( "ZusatzFunktionen", strItem, "GBM.INI" );
	}

	// Lokale externe und interne Zusatzfunktionen:
	// In der [projekt].INI stehen die externen Makros ('ebs'-Dateien, die im
	// aktuell geladenen GBM-Projekt verfügbar sein sollen) in der Form:
	// Fx=[DateiNameMitPfad];[Bezeichnung]
	// sowie ggf. die aktivierbaren internen Makros (in der Resource gebundene,
	// compilierte Scripts) in der Form:
	// Fx=[ResourceID];[Bezeichnung]
	if ( bOpenPro )
	{
		GetActiveProject( strIniFile );
		if ( strIniFile.GetLength() > 4 )
			strIniFile = strIniFile.Left( strIniFile.GetLength() - 3 );
		else
			strIniFile.Empty();

		if ( !strIniFile.IsEmpty())
		{
			strIniFile += "INI";
			iNr = 1;
			strItem = strItemBase;
			strItem.AppendF( iNr, -1 );
			strFkt.GetPrivateProfileString( "ZusatzFunktionen", strItem, strIniFile );
			while ( !strFkt.IsEmpty())
			{
				m_strarrZusatzFkt.Add( strFkt );
				iNr++;
				strItem = strItemBase;
				strItem.AppendF( iNr, -1 );
				strFkt.Empty();
				strFkt.GetPrivateProfileString( "ZusatzFunktionen", strItem, strIniFile );
			}
		}
	}

	// Globale interne Zusatzfunktionen:
	// Abschließend werden alle internen Makros mit globaler Gültigkeit gesucht.
	// Dazu werden alle benannten Script-Resourcen enumeriert und die String-
	// Resourcen nach einer korrespondierenden Bezeichnung durchsucht.
	/*BOOL*/::EnumResourceNames( g_hInstance, TEXT("SCRIPT"),
					(ENUMRESNAMEPROC)EnumResNameProc,
					long((void*)&m_strarrZusatzFktPro ));

	UINT	idA = IDM_EXTRAS + MenuOffset();
	UINT	idB = IDM_VISU + MenuOffset();

	if ( m_strarrZusatzFkt.GetSize() > 0 )
	{
		pExtMenu() -> DeleteMenu( idA, MF_BYCOMMAND );
		if ( pExtMenu() -> InsertMenu( idB, MF_BYCOMMAND|MF_STRING, idA, "Zusätzliche Funktionen ..." ))
			MWind() -> DrawMenuBar();
	}

	strFkt.Empty();
	strFkt.GetPrivateProfileString( "StatusMessage", "Mode", "GBM.INI" );
	if ( !strFkt.IsEmpty())		g_iMessageStatus = strFkt.Short();

	// [GS-Teilen]
	// Behandlung=Ja
	strFkt.Empty();
	strFkt.GetPrivateProfileString( "GS-Teilen", "Behandlung", "GBM.INI" );
	g_bHandleGSTeilen = FALSE;
	if ( !strFkt.IsEmpty())
	{
		strFkt.MakeUpper();
		if ( "JA" == strFkt )
			g_bHandleGSTeilen = TRUE;
	}

}	// InitZusatzFunktionen

COLORREF MakeRGB( const char* txt )
{
	COLORREF	result = RGB( 255, 255, 255 );	// im Fehlerfall Weiß!
	BYTE		rot, gruen, blau;
	const char* ptr = txt;

	rot = gruen = blau = 0;
	if ( *ptr )		ptr++;
	if ( isdigit( *ptr ))	{	rot += *ptr - '0';	*ptr++;	}
	if ( isdigit( *ptr ))	{	rot *= 10;			rot += *ptr - '0';	*ptr++;	}
	if ( isdigit( *ptr ))	{	rot *= 10;			rot += *ptr - '0';	*ptr++;	}
	if ( isdigit( *ptr ))	{	gruen += *ptr - '0';	*ptr++;	}
	if ( isdigit( *ptr ))	{	gruen *= 10;		gruen += *ptr - '0';	*ptr++;	}
	if ( isdigit( *ptr ))	{	gruen *= 10;		gruen += *ptr - '0';	*ptr++;	}
	if ( isdigit( *ptr ))	{	blau += *ptr - '0';	*ptr++;	}
	if ( isdigit( *ptr ))	{	blau *= 10;			blau += *ptr - '0';	*ptr++;	}
	if ( isdigit( *ptr ))	{	blau *= 10;			blau += *ptr - '0';	}
	if ( isdigit( *ptr ))	result = RGB( rot, gruen, blau );
	return result;
}	// MakeRGB

void CGbmTRiASExtension::Visualisierung()
{
	CDlgVisu		dlg( MWind());
	CStringArray	strarrID;
	CxString		text, klasse, eigensch, wert;
	long			rgbCol1, rgbCol2, rgbCol3, rgbCol4, rgbCol5, rgbCol6;
//	long			i, onr;

	if ( dlg.DoModal() == IDOK )
	{
		switch ( dlg.m_iArtVisu )
		{
		case 1:
			text.GetPrivateProfileString( "Visualisierung", "Color01", "GBM.INI" );
			rgbCol1 = MakeRGB( text );		// Bescheid gedruckt
			text.GetPrivateProfileString( "Visualisierung", "Color02", "GBM.INI" );
			rgbCol2 = MakeRGB( text );		// nicht gedruckt
			klasse.LoadString( IDS_GS_CLASSNAME );	// Grundstück
			eigensch.LoadString( IDS_OPNAME02 );	// Bescheid gedruckt
			wert = "1";
			PrepareVisu( klasse, eigensch, wert, rgbCol1 );
			wert = "0";
			PrepareVisu( klasse, eigensch, wert, rgbCol2 );
//			DEX_RePaint();
			DEX_PostRebuildSight();
			break;
		case 2:
			text.GetPrivateProfileString( "Visualisierung", "Color11", "GBM.INI" );
			rgbCol1 = MakeRGB( text );		// Angeschlossene Dachteilflächen
			text.GetPrivateProfileString( "Visualisierung", "Color12", "GBM.INI" );
			rgbCol2 = MakeRGB( text );		// nicht angeschlossen
			klasse.LoadString( IDS_DACH_CLASSNAME );	// Dachteilfläche
			eigensch.LoadString( IDS_OPNAME01 );	// Fläche angeschlossen
			wert = "1";
			PrepareVisu( klasse, eigensch, wert, rgbCol1 );
			wert = "0";
			PrepareVisu( klasse, eigensch, wert, rgbCol2 );
//			DEX_RePaint();
			DEX_PostRebuildSight();
			break;
		case 3:
			text.GetPrivateProfileString( "Visualisierung", "Color21", "GBM.INI" );
			rgbCol1 = MakeRGB( text );		// Herstellungsbeitrag
			text.GetPrivateProfileString( "Visualisierung", "Color22", "GBM.INI" );
			rgbCol2 = MakeRGB( text );		// Erneuerungsbeitrag
			text.GetPrivateProfileString( "Visualisierung", "Color23", "GBM.INI" );
			rgbCol3 = MakeRGB( text );		// Verbesserungsbeitrag 1
			text.GetPrivateProfileString( "Visualisierung", "Color24", "GBM.INI" );
			rgbCol4 = MakeRGB( text );		// Verbesserungsbeitrag 2
			text.GetPrivateProfileString( "Visualisierung", "Color25", "GBM.INI" );
			rgbCol5 = MakeRGB( text );		// Erweiterungsbeitrag
			text.GetPrivateProfileString( "Visualisierung", "Color26", "GBM.INI" );
			rgbCol6 = MakeRGB( text );		// sonst
			klasse.LoadString( IDS_GS_CLASSNAME );	// Grundstück
			eigensch.LoadString( IDS_OPNAME03 );	// Beitragsart
			wert.LoadString( IDS_BEITRAGSART01 );
			PrepareVisu( klasse, eigensch, wert, rgbCol1 );
			wert.LoadString( IDS_BEITRAGSART02 );
			PrepareVisu( klasse, eigensch, wert, rgbCol2 );
			wert.LoadString( IDS_BEITRAGSART03 );
			PrepareVisu( klasse, eigensch, wert, rgbCol3 );
			wert.LoadString( IDS_BEITRAGSART04 );
			PrepareVisu( klasse, eigensch, wert, rgbCol4 );
			wert.LoadString( IDS_BEITRAGSART05 );
			PrepareVisu( klasse, eigensch, wert, rgbCol5 );
			wert.LoadString( IDS_BEITRAGSART06 );
			PrepareVisu( klasse, eigensch, wert, rgbCol6 );
//			DEX_RePaint();
			DEX_PostRebuildSight();
			break;
		case 4:
			text.GetPrivateProfileString( "Visualisierung", "Color31", "GBM.INI" );
			rgbCol1 = MakeRGB( text );		// Angeschlossene Grundstücke
			text.GetPrivateProfileString( "Visualisierung", "Color32", "GBM.INI" );
			rgbCol2 = MakeRGB( text );		// nicht angeschlossen
			klasse.LoadString( IDS_GS_CLASSNAME );	// Grundstück
			eigensch.LoadString( IDS_OPNAME01 );	// Fläche angeschlossen
			wert = "1";
			PrepareVisu( klasse, eigensch, wert, rgbCol1 );
			wert = "0";
			PrepareVisu( klasse, eigensch, wert, rgbCol2 );
//			DEX_RePaint();
			DEX_PostRebuildSight();
			break;
		case 5:
			text.GetPrivateProfileString( "Visualisierung", "Color41", "GBM.INI" );
			rgbCol1 = MakeRGB( text );		// privates Eigentum
			text.GetPrivateProfileString( "Visualisierung", "Color42", "GBM.INI" );
			rgbCol2 = MakeRGB( text );		// komunales Eigentum
			klasse.LoadString( IDS_GS_CLASSNAME );	// Grundstück
			eigensch.LoadString( IDS_OPNAME04 );	// Eigentumsverhältnisse
			wert.LoadString( IDS_EIGENTUM01 );
			PrepareVisu( klasse, eigensch, wert, rgbCol1 );
			wert.LoadString( IDS_EIGENTUM02 );
			PrepareVisu( klasse, eigensch, wert, rgbCol2 );
//			DEX_RePaint();
			DEX_PostRebuildSight();
			break;
		case 6:
			text.GetPrivateProfileString( "Visualisierung", "Color51", "GBM.INI" );
			rgbCol1 = MakeRGB( text );		// Angeschlossene Hoffläche
			text.GetPrivateProfileString( "Visualisierung", "Color52", "GBM.INI" );
			rgbCol2 = MakeRGB( text );		// Nicht angeschlossene Hoffläche
			klasse.LoadString( IDS_HOF_CLASSNAME );	// versiegelte Fläche
			eigensch.LoadString( IDS_OPNAME01 );	// Fläche angeschlossen
			wert = "1";
			PrepareVisu( klasse, eigensch, wert, rgbCol1 );
			wert = "0";
			PrepareVisu( klasse, eigensch, wert, rgbCol2 );
//			DEX_RePaint();
			DEX_PostRebuildSight();
			break;
		}
	}
}

DefineSmartInterface(TRiASBar);
//DefineSmartInterface(TRiASToolBar);
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(TRiASBarContainer);
DefineSmartInterface(TRiASUIOwner);

// Toolbar instatiieren -------------------------------------------------------
const int NOSTRING = 0;
const TBBUTTON buttonsMeta[] =
{	
	//  IDM_INCLUDEPROJECT              13
	//  IDM_OPENPROJEKT                 10
	//  IDM_DATEN                       11
	//  IDM_BEARBEITEN                  21
	//  IDM_SUCHEN                      20
	//  IDM_PRINT                       12
	//  IDM_PRINT_PREVIEW               14
	//  IDM_TIEFENBEGR                  16
	//  IDM_FLAECHEN                    18
	//  IDM_EDITIDE                     22
	// IDM_OBJEKTZEIGEN                31
	//  IDM_BEITRAG                     32
	//  IDM_EXTRAS                      33
	//  IDM_VISU                        34
	//  IDM_ABOUT                       99
	{  0, IDM_INCLUDEPROJECT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{  1, IDM_OPENPROJEKT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{  2, IDM_DATEN, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{  0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{  3, IDM_BEARBEITEN, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{  4, IDM_EDIT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{  5, IDM_EDITIDE, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{  6, IDM_SUCHEN, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{  0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{  7, IDM_PRINT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{  8, IDM_PRINT_PREVIEW, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{  0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{  9, IDM_TIEFENBEGR, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 10, IDM_FLAECHEN, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 11, IDM_BEITRAG, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{  0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 12, IDM_EXTRAS, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 13, IDM_VISU, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{ 14, IDM_STATISTIK, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
	{  0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, 0L, NOSTRING, },
	{ 15, IDM_ABOUT, 0, TBSTYLE_BUTTON, 0L, NOSTRING, },
};
#define NUMBUTTONS_META (sizeof(buttonsMeta)/sizeof(buttonsMeta[0]))

TBBUTTON *CopyButtons (const TBBUTTON *pBttns, int iCnt)
{
	try {
	TBBUTTON *pBtnCopy = new TBBUTTON [iCnt];

		for (int i = 0; i < iCnt; i++) 
			pBtnCopy[i] = pBttns[i];

		return pBtnCopy;
	} catch (...) {
		return NULL;
	} 
}

HRESULT CGbmTRiASExtension::CreateGBMToolBar()
{
TBBUTTON *pBtnCopy = NULL;

	try {
	WTRiASBarContainer BarCont (m_pXtnSite);
	WTRiASBar Bar;

//	ResString strCap (ResID (IDS_METATOOLCAPTION, &RF()), 128);
	CString	strCap;
		strCap.LoadString( IDS_GBMTOOLCAPTION );

	DWORD dwStyle = CBRS_ALIGN_TOP|CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|
					CBRS_BORDER_ANY|CBRS_FLYBY|CBRS_FLOATING|WS_VISIBLE;
//	DWORD dwStyle = CBRS_ALIGN_BOTTOM|CBRS_SIZE_DYNAMIC|CBRS_TOOLTIPS|
//					CBRS_BORDER_ANY|CBRS_FLYBY|CBRS_FLOATING;

		if (IsWin40()) dwStyle |= CBRS_BORDER_3D;

	// ToolBar erzeugen
	HRESULT hr = BarCont -> AddTRiASBar (strCap, dwStyle, TRIASTOOLBAR_PREDEFINED, Bar.ppi());

	// Bitmaps hinzufügen
	WTRiASToolBar Tools (Bar);		// throws HRESULT
	int iOffset = -1;

//		hr = Tools -> AddBitmap (g_hInstance, IDB_GBMTOOLBMP, 6, &iOffset);
		hr = Tools -> AddBitmap (g_hInstance, IDB_GBMTOOLBMP, 16, &iOffset);
		if (FAILED(hr)) return hr;

		pBtnCopy = CopyButtons (buttonsMeta, NUMBUTTONS_META);
		if (NULL == pBtnCopy) throw E_OUTOFMEMORY;

	TBBUTTON *pCurr = pBtnCopy;

		for (int i = 0; i < NUMBUTTONS_META; i++, pCurr++) {
			if (!(TBSTYLE_SEP & pCurr -> fsStyle))
				pCurr -> iBitmap += iOffset;
//			pBtnCopy -> idCommand += MenuOffset();
		}
	
	// UIOwner erzeugen
	WTRiASUIOwner UIOwner;
	
		try {
		CComObject<CAuxUIOwner> *pOwner = NULL;
		HRESULT hr = CComObject<CAuxUIOwner>::CreateInstance(&pOwner);

			if (FAILED(hr)) throw hr;
			UIOwner = (ITRiASUIOwner *)pOwner;		// AddRef !
		
			hr = pOwner -> SetExtension (this);
			if (FAILED(hr)) throw hr;
		
		} catch (HRESULT hr) {
			return hr;
		} catch (...) {
			throw E_OUTOFMEMORY;
		}			
	
	// Buttons hinzufügen
		hr = Tools -> AddButtons (pBtnCopy, NUMBUTTONS_META, UIOwner);
		if (FAILED(hr)) throw hr;

	// Toolbar jetzt floaten
//	Point pt (50, 50);
	CPoint pt(50, 50);

//		ClientToScreen (MWind() -> Handle(), (POINT *)&pt);
		ClientToScreen ( MWind() -> m_hWnd, &pt);
//		hr = Tools -> FloatBar ((POINT &)pt, dwStyle);
		hr = Tools -> DockBar ( AFX_IDW_DOCKBAR_BOTTOM, NULL );
		if (FAILED(hr)) throw hr;

		DELETE_OBJ(pBtnCopy);

	} catch (HRESULT hr) {

		DELETE_OBJ(pBtnCopy);
		return hr;
	}

return NOERROR;
}

HRESULT CGbmTRiASExtension::RemoveGBMToolBar()
{
	try {
	WTRiASBarContainer BarCont (m_pXtnSite);
//	ResString strCap (ResID (IDS_METATOOLCAPTION, &RF()), 128);
	CString strCap;
		
		strCap.LoadString( IDS_GBMTOOLCAPTION );

	// ToolBar beseitigen
		return BarCont -> DeleteTRiASBar (strCap);

	} catch (HRESULT hr) {
		return hr;
	}
}

void CGbmTRiASExtension::ExecCommand( UINT uiID )
{
	MenuCommand((WPARAM)uiID, NULL );
}

void CGbmTRiASExtension::EditVorlagen()
{
	CDlgEditVorlage		dlg( MWind());

	dlg.DoModal();
}


extern CDatenListeDlg	*g_pDatenListeDlg;

BOOL IDEfromONr( long onr, CString& ide )
{
	BOOL	result = FALSE;

	if ( NULL != g_pDatenListeDlg )
	{
//		ide = g_pDatenListeDlg -> FindID( onr );
		ide = g_pDatenListeDlg -> GetIdentNummer( onr );
		result = !ide.IsEmpty();
	}

	return result;
}

CString GetVorlageFileName( char c )
{
	CString		result;

	if ( NULL == g_pSetVorlagen )	g_pSetVorlagen = new CSetVorlagen;

	if ( g_pSetVorlagen -> SelectVorlage( c ))
		result = g_pSetVorlagen -> m_Pfad;

	return result;
}

BOOL IstGrundstueck( long onr )
{
	BOOL	result = FALSE;

	if ( NULL != g_pDatenListeDlg )
		result = g_pDatenListeDlg -> IstGrundstueck( onr );

	return result;
}

BOOL IstGebaeude( long onr )
{
	BOOL	result = FALSE;

	if ( NULL != g_pDatenListeDlg )
		result = g_pDatenListeDlg -> IstGebaeude( onr );

	return result;
}

BOOL IstDachteilflaeche( long onr )
{
	BOOL	result = FALSE;

	if ( NULL != g_pDatenListeDlg )
		result = g_pDatenListeDlg -> IstDachteilflaeche( onr );

	return result;
}

BOOL IstHofflaeche( long onr )
{
	BOOL	result = FALSE;

	if ( NULL != g_pDatenListeDlg )
		result = g_pDatenListeDlg -> IstHofflaeche( onr );

	return result;
}

void CGbmTRiASExtension::RewriteModifications()
{

	if ( NULL != m_pObjProp )
	{
//		g_pOPAngeschlGS -> RewriteModi();
//		g_pOPBeitragsartGS -> RewriteModi();
//		g_pOPEigentumGS -> RewriteModi();
//		g_pOPGedrucktGS -> RewriteModi();
//		g_pOPGedruck2GS -> RewriteModi();
		g_pOP_AGGS -> RewriteModi();
		g_pOP_FLG -> RewriteModi();
		g_pOP_GEFS -> RewriteModi();
		g_pOP_TIEB -> RewriteModi();
		g_pOP_KAT -> RewriteModi();
		g_pOP_FLN -> RewriteModi();
		g_pOP_TIEF -> RewriteModi();
	}
}
