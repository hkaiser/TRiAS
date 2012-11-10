// Erweiterung für die Anzeige von Bildinformationen --------------------------
// File: BILDER.CXX

#include "bilderp.hxx"

#include <direct.h> 

#include <xtsnguid.h>

#include <initguid.h>		// nur im einem Module notwendig
#include "bildguid.h"

#include "version.h"

#include "bilderr.h"			// ResourceKonstanten für diese Erweiterung

#include "bilder.hxx"		// Klasse für diese Erweiterung
#include "bildprof.hxx"

#if _MSC_VER >= 1100
EXTERN_C const IID IID_ITRiASServiceProvider = {0x4F76AC35,0x98EF,0x11D1,{0xBA,0x12,0x08,0x00,0x36,0xD6,0x38,0x03}};
#endif // _MSC_VER >= 1100

//
// Die folgende Funktion muß vom Nutzer bereitgestellt werden und lediglich
// ein Objekt vom konkreten ErweiterungTyp anlegen. Diese Funktion ist notwendig,
// da keine virtuellen Konstruktoren erlaubt sind.
//
CTriasExtension *NewExtension (void)
{
	return new CBilderExtension ();
}

//
// NEU: Die folgende Funktion muß ebenfalls vom Nutzer bereitgestellt werden. 
// Sie liefert den (für jede Erweiterung neu zu generierenden) CLSID 
// dieser Erweiterung.
//
BOOL GetExtensionCLSID (CLSID &rClsID)	// Liefert CLSID
{
	memcpy (&rClsID, &CLSID_BilderExtension, sizeof (GUID));
	return true;
}

// NEU: Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung 
// sich selbst in der RegDB registrieren soll.
BOOL UpdateRegistry (BOOL fRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (fRegister) {
	// RegDB initialisieren
	bool fSuccess = ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_BilderExtension, 
				TEXT("TRiAS.BilderExtension.1"), IDS_LONGCLASSNAME,
				BILDER_MAJORVERSION, BILDER_MINORVERSION,
				EFUnLoadable|EFVisible);
		return fSuccess;
	} else {
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_BilderExtension, 
				TEXT("TRiAS.BilderExtension.1"));
	}

return true;	// alles ok
}

// Konstruktor der ExtensionKlasse --------------------------------------------
// Die nutzerdefinierte Erweiterung muá von der Klasse 'TriasExtension'
// abgeleitet sein, welche wiederum als einzigen Parameter den ResID des
// im Hauptfenster einzuhängeneden Menu's übergeben bekommt.
CBilderExtension::CBilderExtension (void)
	: CTriasExtension ()	// keine Menu's
{
	_pBDir = NULL;		// zentrales Bilderverzeichnis
	_pLocDir = NULL;	// lokales Projektverzeichnis
	_pBW = NULL;		// Daten initialisieren
	_hWnd = 0;		// FensterHandle des aktiven ORFennsters
	_lONr = -1;		// ObjektNummer
	_lIdent = -1;		// Identifikator
}

// Destruktor -----------------------------------------------------------------
CBilderExtension::~CBilderExtension (void) 
{
	DELETE_OBJ (_pBDir);
	DELETE_OBJ (_pLocDir);
	DELETE_OBJ (_pBW);		// evtl. Bild zerlegen
}


// Im folgenden müssen alle durch diese Erweiterung überladenen virtuellen
// Funktionen definiert werden. In diesem konkreten Fall ist es nur eine:

// Diese Funktion wird einmalig nach der erfolgreichen Installation der 
// Erweiterung durch TRIAS gerufen. Hier sollten alle notwendigen 
// Initialisierungen erfolgen.
STDMETHODIMP_(BOOL) CBilderExtension::InitExtension (short iMode)
{
// hier zusätzlichen MenuPunkt anhängen
	if (iMode == LEFullLoad)
		InstallMenuItem (IDM_SHOWBILD, IDS_BILDMENUITEM, true, 0);

	if (iMode != LoadState()) 
		return true;		// jetzt voll zu sehen

// Notifikationen anfordern
	RegisterNotification (DEX_OBJECTUNSELECTED);
	RegisterNotification (DEX_OBJECTSELECTED);	
	RegisterNotification (DEX_LOSTOBJWNDFOCUS);
	RegisterNotification (DEX_GOTOBJWNDFOCUS);	
	RegisterNotification (DEX_PROJECTOPEN);
	RegisterNotification (DEX_PROJECTCLOSE);

// zentrales Bildverzeichnis besorgen
	_pBDir = new char [_MAX_PATH];

	if (_pBDir) {
	ResString Bilder (IDS_BILDER, 13);
	ResString Dirs (ResID (IDS_IRISDIRS , &RF()), 13);
	char *pProfile = new char [_MAX_PATH];

		pProfile = DEX_GetMainIniName (pProfile);
		if (pProfile) {
			GetPrivateProfileString (Dirs, Bilder, "", _pBDir, _MAX_PATH, pProfile);
			if (!strcmp (_pBDir, "")) {
				_getdcwd (_getdrive(), _pBDir, _MAX_PATH);
				if (_pBDir[strlen (_pBDir)-1] != '\\')
					strcat (_pBDir, "\\");
				WritePrivateProfileString (Dirs, Bilder, _pBDir, pProfile);
			}
			delete pProfile;
		} else
			*_pBDir = '\0';
	}

// aktuelles Projektverzeichnis besorgen
	_pLocDir = new char [_MAX_PATH];
	return true;
}

STDMETHODIMP_(BOOL) CBilderExtension::UnLoadExtension (void)
{
// MenuPunkt natürlich wieder ausbauen
	RemoveMenuItem (IDM_SHOWBILD, true, 0);

// Notifikationen wieder abmelden
	UnRegisterNotification (DEX_PROJECTCLOSE);
	UnRegisterNotification (DEX_PROJECTOPEN);
	UnRegisterNotification (DEX_GOTOBJWNDFOCUS);
	UnRegisterNotification (DEX_LOSTOBJWNDFOCUS);
	UnRegisterNotification (DEX_OBJECTSELECTED);
	UnRegisterNotification (DEX_OBJECTUNSELECTED);

	return true;
}


// Diese Funktion dient der Behandlung der MenuKommandos vom nutzereigenen
// Menu der Erweiterung
STDMETHODIMP_(BOOL) CBilderExtension::MenuCommand (UINT uiMenuID, HWND hWnd)
{
	switch (uiMenuID) {	
	case IDM_SHOWBILD:
		if (hWnd != 0) {
		char *pImageName = GetImageName();
		char *pImageCaption = GetImageCaption();

		// Bild anzeigen und raus
		bool iResult = ShowImage (pImageName, pImageCaption);

			DELETE_OBJ (pImageName);
			DELETE_OBJ (pImageCaption);
			return iResult;
		}
		break;

	default:
		break;
	}
	return false;
}

// Herausfinden, ob das aktive Objekt ein Bild hat, Menu entsprechend richten -
STDMETHODIMP_(BOOL) CBilderExtension::MenuInit (HMENU hMenu, LPARAM, HWND hWnd)
{
	if (NULL == hWnd) return true;

UINT iMenuID = IDM_SHOWBILD + MenuOffset();

	_lONr = DEX_GetActiveObject (hWnd);	// 1. ObjektNummer besorgen
	if (_lONr == -1L) {
		EnableMenuItem (hMenu, iMenuID, MF_BYCOMMAND|MF_GRAYED);
		return true;
	}

short Status = DEX_GetObjectStatus (_lONr);

	if (Status != OSNormal && Status != OSModified) {
	// Objekt existiert nicht
		_lONr = -1L;
		EnableMenuItem (hMenu, iMenuID, MF_BYCOMMAND|MF_GRAYED);
		return true;
	}

	_lIdent = DEX_GetObjIdent (_lONr);	// 2. Identifikator besorgen

// 3. in INI-Datei des Projektes nach Bildeintrag (MCode) suchen
HPROJECT hPr = DEX_GetObjectProject(_lONr);

	_ASSERTE(NULL != hPr);
	if (NULL == DEX_GetDataSourceName (hPr, _pLocDir))
		return TRUE;

BildProFile PF (_pLocDir, &RF());		// ProjektINI
long lMCode = PF.ReadImageCode (_lIdent);

// 4. wenn Merkmal existiert, dann hat Objekt ein Bild 
	if (lMCode != 0) {
	// MerkmalsWert holen
	TARGETMERKMAL tm;

		tm.dwSize = sizeof(TARGETMERKMAL);
		tm.lTarget = _lONr;		// ObjektNummer
		tm.lMCode = lMCode;		// MerkmalsCode
		tm.imaxLen = 0;
		tm.pMText = NULL;		// kein Buffer: nur Test
		tm.iTTyp = TT_Objekt;
		DEX_GetTextMerkmal (tm);

		if (tm.imaxLen > 0)
			EnableMenuItem (hMenu, iMenuID, MF_BYCOMMAND|MF_ENABLED);
		else
			EnableMenuItem (hMenu, iMenuID, MF_BYCOMMAND|MF_GRAYED);
	} else
		EnableMenuItem (hMenu, iMenuID, MF_BYCOMMAND|MF_GRAYED);

return true;
}

// Diese Funktion wird bei Systemereignissen diverser Natur gerufen -----------
STDMETHODIMP_(LRESULT) CBilderExtension::Notification (WPARAM iMsg, LPARAM p)
{
	switch (iMsg) {
	case DEX_OBJECTSELECTED:
	case DEX_OBJECTUNSELECTED:
		HideImage();		// evtl. Bildobjekt zerlegen
		break;			// andere wollen diese Meldungen auch noch haben

	case DEX_GOTOBJWNDFOCUS:
		_hWnd = (HWND)p;
		break;

	case DEX_PROJECTOPEN:		// neues Projekt wurde eröffnet
		{			// Projektverzeichnis merken
			if (NULL == _pLocDir)
				_pLocDir = new char [_MAX_PATH];
		}
		break;

	case DEX_PROJECTCLOSE:		// dieses Project wurde abgeschlossen
		{
			HideImage ();
			DELETE_OBJ (_pLocDir);
		}
		break;
	}

return false;	// alles andere ignorieren
}


// versuchen, ein Bild für dieses Objekt anzuzeigen ---------------------------
BOOL CBilderExtension::ShowImage (char *pImageName, char *pImageCaption)
{
	if (pImageName == NULL) return false;

Pointer waitPointer (HourGlass);        // EierUhr
Pointer *oldPointer = MWind() -> ChangePointer (&waitPointer);

	waitPointer.Show();

// vollständigen Bilddateinamen generieren
ResString ImageExt (ResID (IDS_IMGEXT, &RF()), 5);
char *pBildName = new char [_MAX_PATH];
char *pDrive = new char [_MAX_DRIVE];
char *pPath = new char [_MAX_PATH];
bool iResult = false;

	if (pBildName != NULL) {
		_splitpath (_pLocDir, pDrive, pPath, NULL, NULL);
		_makepath (pBildName, pDrive, pPath, "", "");
		strcat (pBildName, ResString (ResID (IDS_BILDERSUBDIR, &RF()), 13));
		strcat (pBildName, pImageName);
		strcat (pBildName, ImageExt);

	OFSTRUCT of;

		if (OpenFile (pBildName, &of, OF_EXIST | OF_READ) < 0) {
		// Datei steht nicht lokal zu dieser DatenBasis: zentralen Namen 
		// generieren

			if (_pBDir)
				strcpy (pBildName, _pBDir);
			strcat (pBildName, pImageName);
			strcat (pBildName, ImageExt);
		}

	// Bild generieren
		HideImage();		// evtl. altes Bild zerlegen
		_pBW = new BildWindow (MVWind(), pImageCaption, Point (0, 0), pBildName);

	// wenn alles ok ist, dann Bild anzeigen
		if (_pBW && _pBW -> OK()) {	// Bildgröße evtl. korrigieren
		Rectangle RB = _pBW -> WindowRect();
		Rectangle RC = MWind() -> CanvasRect();
		CoOrd dY = min (RB.Top()-RB.Bottom(), RC.Top()-RC.Bottom() -
					      2*GetSystemMetrics (SM_CYFRAME));
		CoOrd dX = min (RB.Right()-RB.Left(), RC.Right()-RC.Left() -
					      2*GetSystemMetrics (SM_CXFRAME));

			_pBW -> ChangeSize (Dimension (dX, dY));

		// Bild anzeigen
			_pBW -> Show();
		} else {
			DELETE_OBJ (_pBW);
		}	
		DELETE_OBJ (pBildName);
		DELETE_OBJ (pDrive);
		DELETE_OBJ (pPath);

	// alten Pointer wieder einschalten
		MWind() -> ChangePointer (oldPointer);     // wieder alter Kursor
		if (oldPointer) 
			oldPointer -> Show();

		iResult = true;
	}

return iResult;
}

// Bild wieder ausblenden -----------------------------------------------------
void CBilderExtension::HideImage (void)
{
	DELETE_OBJ (_pBW);
}


// Den Namen einer Bilddatei aus der ProjektIni/Objektmerkmal rauskriegen -----
char *CBilderExtension::GetImageName (void)
{
HPROJECT hPr = DEX_GetObjectProject(_lONr);

	_ASSERTE(NULL != hPr);
	if (NULL == DEX_GetDataSourceName (hPr, _pLocDir))
		return NULL;

BildProFile PF (_pLocDir, &RF());		// ProjektINI
long lMCode = PF.ReadImageCode (_lIdent);

	if (lMCode != 0) {
	// MerkmalsWert holen
	TARGETMERKMAL tm;

		tm.dwSize = sizeof(TARGETMERKMAL);
		tm.lTarget = _lONr;		// ObjektNummer
		tm.lMCode = lMCode;		// MerkmalsCode
		tm.imaxLen = _MAX_PATH;
		tm.pMText = new char [_MAX_PATH];	// Buffer
		tm.iTTyp = TT_Objekt;
		if (DEX_GetTextMerkmal (tm) != NULL)
			return tm.pMText;	// Merkmal existiert
		else 
			DELETE_OBJ (tm.pMText);	// kein Merkmal da
	}
	return NULL;
}


// Die Bildüberschrift aus Projektini/Objektmerkmal rauskriegen ---------------
char *CBilderExtension::GetImageCaption (void)
{
long lMCode = DEX_GetObjNameMCode (_lIdent);

	if (lMCode != 0) {
	// MerkmalsWert holen
	TARGETMERKMAL tm;

		tm.dwSize = sizeof(TARGETMERKMAL);
		tm.lTarget = _lONr;		// ObjektNummer
		tm.lMCode = lMCode;		// MerkmalsCode
		tm.imaxLen = _MAX_PATH;
		tm.pMText = new char [_MAX_PATH];	// Buffer
		tm.iTTyp = TT_Objekt;
		if (DEX_GetTextMerkmal (tm) != NULL)
			return tm.pMText;	// Merkmal existiert
		else 
			DELETE_OBJ (tm.pMText);	// kein Merkmal da
	}
	return NULL;
}


// SchnittstellenFunktionen ---------------------------------------------------
extern "C" 
BOOL _XTENSN_EXPORT PASCAL SHOWIMAGE (char *pImageName, char *pCaption)
{
	if (g_pTE == NULL) return false;

// Bild anzeigen
	return ((CBilderExtension *)g_pTE) -> ShowImage (pImageName, pCaption);
}

extern "C" 
void _XTENSN_EXPORT PASCAL HIDEIMAGE (void)
{
	if (g_pTE == NULL) return;

// Bild aufblenden
	((CBilderExtension *)g_pTE) -> HideImage ();
}
