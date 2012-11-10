// Routinen, die aus einer INI-Datei die gewuenschten Info's rausholen
// File: BILDPROF.CXX

#include "bilderp.hxx"

#include <ospace/file/path.h>
#include "bildprof.hxx"

DefineSmartInterface(TRiASConnection);
DefineSmartInterface(TRiASDatabase);
DefineSmartInterface(TRiASObjectHandleMap);
DefineSmartInterface(TRiASObjects);
DefineSmartInterface(TRiASFeature);

// Konstruktor ----------------------------------------------------------------
BildProFile::BildProFile (const char *pProject, ResourceFile *pResTarget) 
{
	_FullName = NULL;		// für alle Fälle
	if (NULL == pProject) return;

// Dateinamen der ProfileDatei neu generieren
os_path inipath = os_string(pProject);

	if (!inipath.file_path()) {	// Datenquelle ist verzeichnisorientiert
		inipath.filename (inipath.tail());
		if (!inipath.file_path())	// Targetverzeichnis ist Laufwerkswurzel (!?)
			inipath.filename ("root");
	}
	inipath.extension (ResString (ResID (IDS_EXTPROFILE, pResTarget), 5).Addr()+1);

	ATLTRY(_FullName = new char[_MAX_PATH]);
	if (_FullName != NULL) {
	// etvl. ResourceFile merken
		_pResTarget = pResTarget;

	// vollen ProFileNamen zusammenbauen
		
		strcpy (_FullName, os_string(inipath).c_str());
	} else
		_pResTarget = NULL;
}

// Destruktor
BildProFile::~BildProFile (void) 
{
	DELETE_OBJ (_FullName);
}

// MerkmalsKodes, die BildDateinamen enthalten --------------------------------
long BildProFile::ReadImageCode (long lIdent) 
{
// Wenn keine ProFileDatei definiert ist - Fehler
	if (_FullName == NULL || -1 == lIdent) 
		return 0L;

// für bestimmten Id liefern
char cbBuffer[_MAX_PATH];
ResString Images (ResID (IDS_IMAGES, _pResTarget), 13);
char IdKey[64];
char cbOKS[MAX_OKS_LENX+1];

	ClassFromIdentX (lIdent, cbOKS);
	strcpy (IdKey, "");
	strcat (IdKey, cbOKS);

	if (0 == GetPrivateProfileString (Images, IdKey, "", cbBuffer, sizeof(cbBuffer), _FullName)) 
		cbBuffer[0] = '\0';

// wenn nichts da, dann Standard liefern
	if ('\0' == cbBuffer[0])
		GetPrivateProfileString (Images, "Standard", "", cbBuffer, sizeof(cbBuffer), _FullName);

// wenn immer noch nichts da, dann 'ObjName' setzen und liefern
	if ('\0' == cbBuffer[0]) {
	ResString resBildInfo(ResID (IDS_BILDINFO, _pResTarget), 64);

		strcpy (cbBuffer, resBildInfo);
		WritePrivateProfileString (Images, "Standard", cbBuffer, _FullName);
	}

WTRiASFeature Feat;

	if (FAILED(GetFeature (lIdent, cbBuffer, Feat.ppi())))
		return 0L;

INT_PTR lHandle = NULL;

	if (FAILED(Feat -> get_Handle (&lHandle)))
		return 0L;
	return lHandle;
}

HRESULT BildProFile::GetFeature (INT_PTR lIdent, LPCSTR pcName, ITRiASFeature **ppIFeat)
{
WTRiASObjects Objs;
HRESULT hr = GetObjectsDef (lIdent, Objs.ppi());

	if (FAILED(hr))
		return hr;
			
	return Objs -> get_Feature (CComVariant(pcName), VARIANT_FALSE, CComBSTR(""), ppIFeat);
}

HRESULT BildProFile::GetObjectsDef (ULONG ulIdent, ITRiASObjects **ppIObjs)
{
	if (NULL == ppIObjs)
		return E_POINTER;
	*ppIObjs = NULL;

	COM_TRY {
	// aus Database-Tabelle rausfischen
	WTRiASObjectHandleMap Map (CLSID_TRiASObjectsHandleMap);
	WTRiASObjects Objs;
	
	// wiederauffinden des Objects-Objektes
		if (!Map || 0 == ulIdent || FAILED(Map -> GetObject (ulIdent, Objs.ppu()))) 
			return HRESULT_FROM_ERRCODE(WC_NOTFOUND);

		*ppIObjs = Objs.detach();

	} COM_CATCH;
	return S_OK;
}

