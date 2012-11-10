// Funktionen für Erweiterungs-DLL "Topologische Relationen"
// File: TopoRel.cxx
// W. Mörtl


#include "TopoRelP.hxx"

#include <initguid.h>			// nur in einem Modul für Linken (*guid.h, CLSID_*) notwendig
#include "version.h"			// TOPOREL_MAJORVERSION, ...

#include <TriasTLB.h>			// IPropertySequenceService
#include <TRiASHelper_i.c>		// CLSID_PropertySequenceService
#include <selobwnd.h>

#include "GeomDLL.hxx"			// InitGeometrie()

#include "TopoRel.hxx"			// TopoRelatExtension
#include "TopoRelPropAct.h"


DefineSmartInterface(PropertySequenceService);	// WPropertySequenceService
DefineSmartInterface(TRiASDataObject);			// WTRiASDataObject


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
//extern UINT __DexNotify;
//extern UINT __DexCmd;
    


///////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_OBJECT_MAP(ObjectMap)		// Makro
	OBJECT_ENTRY(CLSID_Topologie, TopoRelatExtension)
	OBJECT_ENTRY(CLSID_TopoRelPropAct, CTopoRelPropAct)
END_OBJECT_MAP()

_ATL_OBJMAP_ENTRY* GetObjectMap (void)
{
	return ObjectMap;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung sich selbst in der
// RegDB registrieren soll (empfohlen!!).
// Der ProgID (hier 'TRiAS.Topologie.1') ist eine Zeichenkette, die die Erweiterung in der
// RegDB repräsentiert. Das Format sollte beibehalten werden. Die '... .1' steht für die
// VersionsNummer. Der KlassenName (hier die Stringresource hinter IDS_LONGCLASSNAME) ist eine
// normal-lesbare Zeichenkette, die lokalisiert wird (deshalb in der Ressource) und die
// Bezeichnung der Erweiterung definiert.
BOOL UpdateRegistry (BOOL bRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (bRegister)	// RegDB initialisieren
		return ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_Topologie, TEXT("TRiAS.Topologie.1"), IDS_LONGCLASSNAME,
				TOPOREL_MAJORVERSION, TOPOREL_MINORVERSION,
				EFUnLoadable|EFVisible);
	else			// RegDB säubern
		return ExtOleUnregisterClass (CLSID_Topologie, TEXT("TRiAS.Topologie.1"));

	return true;	// alles ok
}


///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
ResourceFile* pRF = NULL;



///////////////////////////////////////////////////////////////////////////////////////////////
int ErrHandler (int iWC, int iRoutine, ...);



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
// Die Erweiterung wird von der Klasse 'CTriasExtension' abgeleitet
TopoRelatExtension :: TopoRelatExtension (void)
					: CTriasExtension()
#if !defined(__ATL_20_USED__)
					  , m_PPI(this)
#endif // !defined(__ATL_20_USED__)
{
	// Member initialisieren
	m_bMenIt = false;	// MenuItem noch nicht installiert
	m_pTRF = NULL;
}


//---------------------------------------------------------------------------------------------
// Destruktor
TopoRelatExtension :: ~TopoRelatExtension (void)
{
	DELETE_OBJ(m_pTRF);
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Im folgenden werden alle durch diese Erweiterung überladenen virtuellen Funktionen definiert

//---------------------------------------------------------------------------------------------
// Folgende Funktion wird einmalig nach der erfolgreichen Installation der Erweiterung durch
// TRiAS gerufen. Hier erfolgen alle notwendigen Initialisierungen.
STDMETHODIMP_(BOOL) TopoRelatExtension :: InitExtension (short iMode)
{
	if (!CTriasExtension :: InitExtension (iMode))
		return false;

	InitGeometrie (hWnd(), __DexNotify, __DexCmd);
	pRF = &RF();
	
	_ASSERTE (pRF != 0);

ErrCode rcDummy;

	DEX_ErrInstall (rcDummy, WC_MESSAGE_TOPO, ErrHandler, &m_oldEH);

	m_iMode = iMode;
	if (iMode != LoadState())	// Erweiterung war schon teilweise geladen gewesen
		return true;			// jetzt ist sie voll zu sehen

	// TRiAS-Messages anfordern (nur 1 Parameter)
	// ich interessiere mich für die von TRiAS verschickten Meldungen:
	RegisterNotification (DEX_PROJECTOPEN);		// Schließen eines Projektes
	RegisterNotification (DEX_PROJECTCLOSE);	// Öffnen eines Projektes
	RegisterNotification (DEX_N_SAVECOMPLETED);

	m_pTRF = new TopoRelFunc();
	if (! m_pTRF)
	{                                                                      
		DEX_Error (RC_TopoRel, EC_NOMEMORY);
		return E_OUTOFMEMORY;
	}

	InitAndOPEN (iMode);

	return true;
} // InitExtension


//--------------------------------------------------------------------------------------------
STDMETHODIMP_(BOOL) TopoRelatExtension :: UnLoadExtension (void)
{
	// TRiAS-Messages wieder abmelden
	// ich interessiere mich nicht mehr für die von TRiAS verschickten Meldungen:
	UnRegisterNotification (DEX_N_SAVECOMPLETED);
	UnRegisterNotification (DEX_PROJECTCLOSE);		// Schließen eines Projektes
	UnRegisterNotification (DEX_PROJECTOPEN);		// Öffnen eines Projektes

ErrCode rcDummy;

	DEX_ErrInstall (rcDummy, WC_MESSAGE_TOPO, m_oldEH, 0);
	
	// restliche Abmeldungen
	UnLoadAndCLOSE();
	
	return CTriasExtension :: UnLoadExtension();
}


//--------------------------------------------------------------------------------------------
// Diese Funktion dient der Behandlung der MenüKommandos der Erweiterung
STDMETHODIMP_(BOOL) TopoRelatExtension :: MenuCommand (UINT MenuItemID, HWND hWnd)
{
WPropertySequenceService Service (CLSID_PropertySequenceService);
WProgressIndicator Status (CLSID_ProgressIndicator);

	Status -> InitNew (hWnd, PIFLAG_RESULT);

	Service -> put_ResourceModule(CComBSTR(g_pDLLName));

	switch (MenuItemID)
	{
		case IDM_MAINMENU:	// Menüpunkt im Hauptmennü
		{
		HRESULT hr = Service -> RunActionSequence(
					reinterpret_cast<INT_PTR>(hWnd), 
					CComBSTR("TopologicalAnalysisMain.xml"), 
					CComBSTR(""), CComBSTR("TopoRelMain"), 
					WProgressIndicator2(Status), NULL, VARIANT_FALSE, NULL);
		
			if (SUCCEEDED(hr))
				return true;
			return false;
		}
 
		case IDM_ORMENU:	// Menüpunkt im Recherchefenster: Lage bez. der Bezugsobjekte bestimmen
		{
			if (0 == hWnd)	// kein Recherchefenster geöffnet
				return false;

			COM_TRY {
			// das eigene Fenster nicht mit anzeigen
			WDataObject DataCtx(CLSID_DataTransferObject);

				THROW_FAILED_HRESULT(PropActBase::SetHWND(hWnd, DataCtx, 
					&c_feIgnoreWindow));
		
				THROW_FAILED_HRESULT(Service -> putref_ContextData(
					WTRiASDataObject(DataCtx)));
				THROW_FAILED_HRESULT(Service -> RunActionSequence(
					reinterpret_cast<INT_PTR>(hWnd), 
					CComBSTR("TopologicalAnalysisORWin.xml"), 
					CComBSTR(""), CComBSTR("TopoRelORWin"), 
					WProgressIndicator2(Status), NULL, VARIANT_FALSE, NULL));

			} COM_CATCH_NOASSERT_ON_RETURN(E_ABORT, false);
			return true;
		}

		default:
			_ASSERTE (false);
			break;
	} // switch

	DEX_Error (RC_MenuCommandTopo, EC_ERRMENUITEMID);   // Fehlermeldung
	return false;

} // MenuCommand
 

//-------------------------------------------------------------------------------------------------
// Diese Funktion initialisiert das Menü
STDMETHODIMP_(BOOL) TopoRelatExtension :: MenuInit (HMENU hMenu, LPARAM, HWND hWnd)
{
	if (hWnd)		// Recherchefenster geöffnet
		EnableMenuItem (hMenu, IDM_ORMENU+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
	else
		EnableMenuItem (hMenu, IDM_ORMENU+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);
		
	return true;
}


// -----------------------------------------------------------------------------------------------
// Diese Funktion wird bei Systemereignissen diverser Natur gerufen, z.B. Projekt öffnen
STDMETHODIMP_(LRESULT) TopoRelatExtension :: Notification (WPARAM iMsg, LPARAM p)
{
	switch (iMsg)
	{
		case DEX_PROJECTOPEN:		// Projekt wird geöffnet
			InitAndOPEN (m_iMode);
			break;
	
	
		case DEX_PROJECTCLOSE:		// Projekt wird geschlossen
			UnLoadAndCLOSE();
			break;
			
		case DEX_N_SAVECOMPLETED:
			break;

		default:	// Notifikationen der Basisklasse
			break;
	}

	return CTriasExtension :: Notification (iMsg, p);

} // Notification


// ------------------------------------------------------------------------------------------------
// Aktionen, die bei InitExtension und DEX_PROJECTOPEN gleich sind
bool TopoRelatExtension :: InitAndOPEN (int iMode)
{
	if (DEX_TestActiveProject())    // ein Projekt ist schon geöffnet
	{
		if (iMode == LEFullLoad && m_bMenIt == false)
		{
			// zusätzliche Menüpunkte im Hauptmenü (false) "Extras" anhängen
			InstallMenuItem (IDM_MAINMENU, IDS_LAGEBEST, false, EXTRA_MENU_POS);
			
			// zusätzlichen Menüpunkt im Recherchemenü (true) "Extras" (2) anhängen
			InstallMenuItem (IDM_ORMENU, IDS_LAGEBEST, true, OR_EXTRA_MENU_POS);

			m_bMenIt = true;
		}
	}

	return true;
}


// ------------------------------------------------------------------------------------------------
// Aktionen, die bei UnLoadExtension und DEX_PROJECTCLOSE gleich sind
void TopoRelatExtension :: UnLoadAndCLOSE (void)
{
	// Menüpunkte entfernen ...
	if (m_bMenIt)
	{
		RemoveMenuItem (IDM_MAINMENU, false, EXTRA_MENU_POS);	// ... im Hauptmenü
		RemoveMenuItem (IDM_ORMENU, true, OR_EXTRA_MENU_POS);	// ... im Recherchefenster
		m_bMenIt = false;
	}
}


// --------------------------------------------------------------------------------------------
// Reaktion auf Fehlercode iWC
int ErrHandler (int iWC, int iRoutine, ...)
{
va_list vaArgs;		// Liste der unbenannten Argumente

	va_start (vaArgs, iRoutine);

void* pvData = va_arg (vaArgs, void*);	// Makro, um die unbenannten Argumente herauszuholen
ResString resTitel (ResID (IDS_LONGCLASSNAME, pRF), 50);
				
	MessageBox (__hWndM, (char*)pvData, resTitel.Addr(), MB_ICONEXCLAMATION | MB_OK);
	va_end (vaArgs);

	return iWC;

} // ErrHandler
