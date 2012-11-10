// Import aus dem AutoCAD DXF-Format der Version 12.0 ------------------------------------
// File: DXFIMP.CPP

#include "pheader.hpp"          // vorübersetzter Header
#include <xtsnguid.h>
// #include <registry.hxx>			// CCurrentUser

#include <initguid.h>			// nur im einem Module notwendig
#include "dxfguids.h"

#include "version.h"

#if _MSC_VER >= 1100
EXTERN_C const IID IID_ITRiASServiceProvider = {0x4F76AC35,0x98EF,0x11D1,{0xBA,0x12,0x08,0x00,0x36,0xD6,0x38,0x03}};
#endif // _MSC_VER

//	Konstanten
// const short EbenenSize = 512;

//	externe Variablen
extern char g_pDLLName [_MAX_PATH];

//
// Die folgende Funktion muß vom Nutzer bereitgestellt werden und lediglich
// ein Objekt vom konkreten ErweiterungTyp anlegen. Diese Funktion ist notwendig,
// da keine virtuellen Konstruktoren erlaubt sind.
//
CTriasExtension *NewExtension (void)		// NEU: ohne Parameter
{
	return new CImpDxfExtension();
}

//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
//
BOOL GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
    memcpy (&rClsID, &CLSID_ImpDxfExtension, sizeof (GUID));
	return TRUE;
}

// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll.
BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	char ImportName [] = "TRiAS.AutoCadImport.1";

	if (fRegister) 
	{// RegDB initialisieren
		bool fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
                                CLSID_ImpDxfExtension, 
                                TEXT(ImportName), IDS_LONGCLASSNAME,
                                DXFIMP_MAJORVERSION, DXFIMP_MINORVERSION,
								EFUnLoadable|EFCanImport);
		if (!fSuccess) 
			return False;

/*
	//	Flags für diese Erweiterung lesen/schreiben
		DELETE_VEC (g_pEbenen);
		DWORD Size = EbenenSize;
		g_pEbenen = new char [Size+1];
		if (!g_pEbenen)
			return False;
		*g_pEbenen = '\0';

		ResourceFile RF (g_pDLLName);
		ResString RegistryPfad (ResID (IDS_REGPFAD, &RF), 100);	
		ResString Schluessel (ResID (IDS_DXFIMP_LAYERS, &RF), 30);	
		CCurrentUser cuConfig (RegistryPfad.Addr());	// Software\\uve\\TRiAS\\Config
		
		if (cuConfig.GetSubSZ (Schluessel.Addr(), g_pEbenen, Size) == False)
		{
			ResString strValue (ResID (IDS_STANDANRD_LAYER, &RF), 10);
			cuConfig.SetSubSZ (Schluessel.Addr(), strValue.Addr ());
			strcpy (g_pEbenen, strValue.Addr ());
		}
*/

		return ExtOleRegisterImportClass (g_hInstance,
                                CLSID_ImpDxfExtension, TEXT(ImportName), 
                                IDS_FORMATDESCRIPTION, IDS_DEFAULTEXTENSION);
	} 
	else 
	{// RegDB säubern
        return ExtOleUnregisterClass (CLSID_ImpDxfExtension, TEXT(ImportName));
	}

	return true;	// alles ok
}

// NEU: Die Funktion void DeleteExtension (CTriasExtension *pTE) muß nicht mehr
// zur Verfügung gestellt werden.

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muß von der Klasse 'CTriasExtension'
// abgeleitet sein, welche wiederum als einzige Parameter die ResID's der
// im Hauptfenster und ORFenster einzuhängeneden Menu's übergeben bekommt.
CImpDxfExtension :: CImpDxfExtension (void)
		  		  : CTriasExtension ()
{
	m_pIImport = NULL;
}

// da wir ein zusätzliches Interface dazugenommen haben, muß ein modifiziertes 
// QueryInterface gegeben sein
HRESULT CImpDxfExtension :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
	if (riid == IID_IImportGeoData)
		*ppvObj = (IImportGeoData *)m_pIImport;	// ImportInterface liefern
	else if (riid == IID_IImportGeoDataSelectCS)
		*ppvObj = (IImportGeoDataSelectCS *)m_pIImport;
	else
	// 	alles andere überlassen wir der BasisKlassse
		return CTriasExtension :: QueryInterface (riid, ppvObj);

// 	AddRef nicht vergessen
	LPUNKNOWN(*ppvObj) -> AddRef();

	return NOERROR;
}

// Destruktor -----------------------------------------------------------------
CImpDxfExtension :: ~CImpDxfExtension (void) 
{
	DELETE_OBJ (m_pIImport);
}

// Diese Funktion wird einmalig nach der erfolgreichen Installation der 
// Erweiterung durch TRIAS gerufen. Hier sollten alle notwendigen 
// Initialisierungen erfolgen.
STDMETHODIMP_(BOOL) CImpDxfExtension :: InitExtension (short iMode)
{
//  InitCommonControls();
	if (! CTriasExtension :: InitExtension (iMode))
		return FALSE;

	 m_pIImport = new CImportAutoCadDxf (m_pUnk ? m_pUnk : this);
	 return m_pIImport != NULL;
}

STDMETHODIMP_(BOOL) CImpDxfExtension :: UnLoadExtension (void)
{
	return CTriasExtension :: UnLoadExtension();
}

