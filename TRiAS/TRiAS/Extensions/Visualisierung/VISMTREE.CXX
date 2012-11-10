// Implementation der typspezifischen TreeKlasse ------------------------------
// File: VISMTREE.CXX
// Generiert aus TTREE.CTT

#include "visobjp.hxx"

#include <protos.h>
#include <icustom.hxx>
#include <vismguid.h>
#include <registrx.hxx>

#include "visobj.h"

#include "vismtree.hxx"	// KlassenDeklarationen
#include "vismtree.inl"	// Inline-Funktionen

///////////////////////////////////////////////////////////////////////////////
// Finden des ClsID's über den 'alten Name' des VisModules 
#if defined(WIN32)

#define GUID_CCH	39	// Characters in string form of guid, including '\0'

HRESULT CLSIDFromOldName (LPCSTR pOldName, CLSID *pclsID)
{
CRegKey regVMD;

	if (ERROR_SUCCESS != regVMD.Open (HKEY_CURRENT_USER, TEXT("Software")) ||
		ERROR_SUCCESS != regVMD.Open (regVMD, REG_COMPANY_KEY) ||
		ERROR_SUCCESS != regVMD.Open (regVMD, REG_PRODUCT_KEY) ||
		ERROR_SUCCESS != regVMD.Open (regVMD, TEXT("VisModules")))
	{
		return CO_E_OBJNOTREG;
	}

// alle registrierten Einträge durchgehen
DWORD i = 0;
char cbBuffer[_MAX_PATH];

	USES_CONVERSION;
	while (RegEnumKey (regVMD, i, cbBuffer, _MAX_PATH) == ERROR_SUCCESS) {
	CRegistry regProgID (regVMD, cbBuffer);
	LONG lLen = _MAX_PATH;

		i++;	// nächster RegistryEintrag

	// testen, ob der OldName gefunden wurde
		if (!regProgID.GetSZ (TEXT("OldName"), cbBuffer, lLen) ||
			_stricmp (cbBuffer, pOldName))
		{
			continue;
		}

	// ProgID lesen
		lLen = _MAX_PATH;
		if (!regProgID.GetSZ (TEXT("CLSID"), cbBuffer, lLen))
			return CO_E_OBJNOTREG;

	// CLSID konvertieren
		return CLSIDFromString (A2OLE(cbBuffer), pclsID);
	}

return CO_E_OBJNOTREG;
}
#endif // WIN32

// Initialisierung eines Elementes des Baumes ---------------------------------
bool CVisModule :: FInit (pChar pVisModuleName, char *pProject)
{
// Schlüssel kopieren
	m_Key = new char [strlen (pVisModuleName)+1];	// ModuleNamen merken
	if (m_Key == NULL) return false;

#if defined(WIN32)
// ClassID aus Registry besorgen
CLSID clsID;
HRESULT hr = CLSIDFromOldName (pVisModuleName, &clsID);

// Objekt instantiieren
	if (SUCCEEDED(hr))
		hr = CoCreateInstance (clsID, NULL, CLSCTX_INPROC_SERVER, 
							   IID_IVisModule, (LPVOID *)&m_pIVisModule);
	if (SUCCEEDED(hr)) {
		strcpy (m_Key, pVisModuleName);		// Key initialisieren

	// evtl. für ein Projekt initialisieren
		if (pProject) 
			m_pIVisModule -> OnProjectChange (__hWndM, PROJECTCHANGE_OPENED, pProject);
		return true;
	}
	return false;
#else
// Kompatibilität zu 'alten' VisModules halten
// ... (jetzt nicht mehr)
HRESULT hr = NOERROR;		// DLL binden, Erweiterung (*.VMD) anhängen
ResString rsExt (ResID (IDS_VMDEXTENSION, &g_pTE -> RF()), 5);
char *pcnDLLName = new char [_MAX_FNAME];
char *pcnDLLPath = new char [_MAX_PATH];
char *pcnDLLDrive = new char [_MAX_DRIVE];
char *pcnDLLExt = new char [_MAX_EXT];

	_splitpath (pVisModuleName, pcnDLLDrive, pcnDLLPath, m_Key, pcnDLLExt);
	strlwr (m_Key);
	if (pcnDLLExt == NULL || *pcnDLLExt == '\0')
		_makepath (pcnDLLName, pcnDLLDrive, pcnDLLPath, m_Key, (const char *)rsExt.Addr());
	else
		_makepath (pcnDLLName, pcnDLLDrive, pcnDLLPath, m_Key, pcnDLLExt);
	m_pVCSModule = CDllBindX :: CreateInstance (pcnDLLName);
	DELETE (pcnDLLName);
	DELETE (pcnDLLDrive);
	DELETE (pcnDLLPath);
	DELETE (pcnDLLExt);

	if (m_pVCSModule == NULL) return false;

// Interface besorgen
LPFNGETCLASSOBJECT pF = (LPFNGETCLASSOBJECT)m_pVCSModule -> GetProcAddress ("DLLGETCLASSOBJECT");

	if (pF == NULL) {
		DELETE (m_pVCSModule);
		return false;
	}

LPCLASSFACTORY pCF = NULL;

	hr = (*pF)(CLSID_VisModule, IID_IClassFactory, (LPVOID *)&pCF);
	if (SUCCEEDED(hr)) {
		hr = pCF -> CreateInstance (NULL, IID_IVisModule, 
					    (LPVOID *)&m_pIVisModule);
		pCF -> Release();
	}

	if (FAILED(hr)) {
		DELETE (m_pVCSModule);
		return false;
	}

// evtl. für ein Projekt initialisieren
	if (pProject) 
		m_pIVisModule -> OnProjectChange (__hWndM, PROJECTCHANGE_OPENED, pProject);
	
	return true;
#endif
}

// Konstruktor der typspezifischen TreeKlasse ---------------------------------
CVisModuleTree :: CVisModuleTree (void)
: CTree ((TTREEGETKEYFCN)FTTreeGetpChar, (TTREECMPKEYFCN)FTTreeCmppChar)
{
	// nothing else to do
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CVisModuleTree :: ~CVisModuleTree (void)
{
	EveryDelete();
}

// Funktion, die ein neues Element in den Baum einhängt -----------------------
bool CVisModuleTree :: FAddItem (pChar pVisModuleName, char *pProject)
{
CVisModuleCreator Cr (*this);
CVisModule *pVM = new CVisModule();

	if (pVM == NULL || !pVM -> FInit (pVisModuleName, pProject)) {
		DELETE_OBJ(pVM);
		return false;
	}

return NULL != Cr.InsertPtr (pVM);
}

// Funktion, die ein Element aus dem Baum löscht -----------------------------
bool CVisModuleTree :: FDeleteItem (pChar &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) return t.Delete();

return false;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CVisModule *CVisModuleTree :: FFindItem (pChar &rKT)
{
CTable t(*this);

	if (!t.Find ((void *)&rKT)) {
	char cbKey[_MAX_PATH];
	char *pPtr = cbKey;

		_splitpath (rKT, NULL, NULL, cbKey, NULL);
		if (!t.Find ((void *)&pPtr))
			return NULL;
	}

	{
	CVisModuleLock l(t);

		if (l) return l;
	}

return NULL;	// nicht gefunden
}

CVisModule *CVisModuleTree :: FFindOrAdd (pChar &rKT, pChar pProject)
{
CVisModule *pVM = FFindItem (rKT);

	if (pVM == NULL) {
		if (!FAddItem (rKT, pProject)) return NULL;
		pVM = FFindItem (rKT);
	} 
	if (pVM && !pVM -> isValid())
		return NULL;
		
return pVM;
}

// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void CVisModuleTree :: UserDelete (void *pObj)
{
	((CVisModule *)pObj) -> ~CVisModule();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
pChar *FTTreeGetpChar (CVisModule *pObj)
{
	return & ((CVisModule *)pObj) -> FGetpChar();
}

void CVisModuleTree :: OnProjectChange (HWND hWndM, PROJECTCHANGE rgPC, char *pPrName)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CVisModuleLock l(t);

		if (l && l -> isValid()) 
			l -> m_pIVisModule -> OnProjectChange (hWndM, rgPC, pPrName);
	}
}


void CVisModuleTree :: OnViewChange (HWND hWndM, VIEWCHANGE rgVC, char *pView)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CVisModuleLock l(t);

		if (l && l -> isValid()) 
			l -> m_pIVisModule -> OnViewChange (hWndM, rgVC, pView);
	}
}


void CVisModuleTree :: OnPaletteChange (HWND hWndM, HPALETTE hPal)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CVisModuleLock l(t);

		if (l && l -> isValid()) 
			l -> m_pIVisModule -> OnPaletteChange (hWndM, hPal);
	}
}

