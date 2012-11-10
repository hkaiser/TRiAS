// Import aus dem unkomprimierten E00-Format
// File: ARCIMP.CPP

#include "pheader.h"          	// vorübersetzter Header
#include <xtsnguid.h>

#include <initguid.h>			// nur im einem Module notwendig
#include "arcguid.h"

#include "version.h"
#include "arctrias.hr"          // Resourcen-Konstanten
#include <hpp/filebuff.hxx>         // CFileBuffer
#include "numedit.hxx"          // NumEdit
#include "realedit.hxx"         // RealEdit
#include "helptext.hxx"         // CHelpText
#include "optparam.hxx"         // Params, OptParams
#include "arcimpif.hxx"			// Interface-Klasse
#include "arcimp.hxx"			// zugeh. Header

#if _TRiAS_VER >= 0x0300
EXTERN_C const IID IID_ITRiASServiceProvider = {0x4F76AC35,0x98EF,0x11D1,{0xBA,0x12,0x08,0x00,0x36,0xD6,0x38,0x03}};
#endif // _TRiAS_VER >= 0x0300

//
// Die folgende Funktion muß vom Nutzer bereitgestellt werden und lediglich
// ein Objekt vom konkreten ErweiterungTyp anlegen. Diese Funktion ist notwendig,
// da keine virtuellen Konstruktoren erlaubt sind.
//
CTriasExtension *NewExtension (void)		// NEU: ohne Parameter
{
        return new CImpArcExtension;
}

//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
//
BOOL GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
    memcpy (&rClsID, &CLSID_ImpArcExtension, sizeof (GUID));
	return TRUE;
}

// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll.
BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	char ImportName [] = "TRiAS.ArcInfoImport.1";
	if (fRegister) 
	{// RegDB initialisieren
		bool fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
                                CLSID_ImpArcExtension, 
                                TEXT(ImportName), IDS_LONGCLASSNAME,
                                ARCINFO_IMP_MAJORVERSION, ARCINFO_IMP_MINORVERSION,
								EFUnLoadable|EFCanImport);
		if (!fSuccess) 
			return false;

		return ExtOleRegisterImportClass (g_hInstance,
                                CLSID_ImpArcExtension, TEXT(ImportName), 
								IDS_FORMATDESCRIPTION, IDS_DEFAULTEXTENSION);
	} 
	else 
	{// RegDB säubern
        return ExtOleUnregisterClass (CLSID_ImpArcExtension, TEXT(ImportName));
	}

	return true;	// alles ok
}

// NEU: Die Funktion void DeleteExtension (CTriasExtension *pTE) muß nicht mehr
// zur Verfügung gestellt werden.

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muß von der Klasse 'CTriasExtension'
// abgeleitet sein, welche wiederum als einzige Parameter die ResID's der
// im Hauptfenster und ORFenster einzuhängeneden Menu's übergeben bekommt.
CImpArcExtension :: CImpArcExtension (void)
		  		  : CTriasExtension ()
{
	m_pIImport = NULL;
}

// da wir ein zusätzliches Interface dazugenommen haben, muß ein modifiziertes 
// QueryInterface gegeben sein
HRESULT CImpArcExtension :: QueryInterface (REFIID riid, LPVOID *ppvObj)
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
CImpArcExtension :: ~CImpArcExtension (void) 
{
	DELETE_OBJ (m_pIImport);
}

// Diese Funktion wird einmalig nach der erfolgreichen Installation der 
// Erweiterung durch TRIAS gerufen. Hier sollten alle notwendigen 
// Initialisierungen erfolgen.
STDMETHODIMP_(BOOL) CImpArcExtension :: InitExtension (short iMode)
{
//        InitCommonControls();
	if (! CTriasExtension :: InitExtension (iMode))
		return FALSE;

	m_pIImport = new CImportArcInfo (m_pUnk ? m_pUnk : this);
	return m_pIImport != NULL;
}

STDMETHODIMP_(BOOL) CImpArcExtension :: UnLoadExtension (void)
{
	return CTriasExtension :: UnLoadExtension();
}

