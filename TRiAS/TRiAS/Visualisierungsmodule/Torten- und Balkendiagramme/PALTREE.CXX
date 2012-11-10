// Implementation der typspezifischen TreeKlasse ------------------------------
// Generiert aus CTTREE.CTT
// File: PALTREE.CXX

#include "tortenp.hxx"

#include <protos.h>
#include <icustom.hxx>

#include "tortenid.h"

#include "impcustm.hxx"
#include "paltree.hxx"	// KlassenDeklarationen
#include "paltree.inl"	// Inline-Funktionen

#if !defined(WIN32)
#include <tchar.h>
#endif // !WIN32

OLECHAR *VMDWideString (const char *strIn);
char *VMDAnsiString (const OLECHAR *strIn);

// Konstruktor der typspezifischen TrreKlasse ---------------------------------
CVisPaletteTree :: CVisPaletteTree (void)
: CTree ((CTTREEGETKEYFCN)FCTTreeGetpChar, (CTTREECMPKEYFCN)FCTTreeCmppChar)
{
}

// Destruktor, zerlegt alle Elemente des Baumes -------------------------------
CVisPaletteTree :: ~CVisPaletteTree (void)
{
	EveryDelete();
}

// Funktionen, die ein neues Element in den Baum einhängt ---------------------
BOOL CVisPaletteTree :: FAddItem (pChar pPName, LPSTORAGE pIStorage)
{
BOOL fDelete = false;

	{
	CVisPaletteCreator Cr (*this);
	CVisPalette *pVP = Create (Cr, CVisPalette);
		
		if (pVP == NULL || !pVP -> FInit (pPName, pIStorage))
			fDelete = true;
	}
	if (fDelete) 	// bei Fehler wieder rauslöschen
		FDeleteItem (pPName);
		
	return TRUE;
}


BOOL CVisPaletteTree :: FAddItem (CVisPalette &rVP)
{
bool fDelete = false;

	{
	CVisPaletteCreator Cr (*this);
	CVisPalette *pVP = Create (Cr, CVisPalette);
		
		if (pVP == NULL || !pVP -> FInit (rVP))
			fDelete = true;
	}
	if (fDelete) 	// bei Fehler wieder rauslöschen
		FDeleteItem (rVP.FGetpChar());
		
return true;
}

// Funktion, die ein Element aus dem Baum löscht -----------------------------
BOOL CVisPaletteTree :: FDeleteItem (pChar &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) return t.Delete();

return false;
}

// Funktion, die Pointer auf ein gesuchtes Item liefert ---------------------
CVisPalette *CVisPaletteTree :: FFindItem (pChar &rKT)
{
CTable t(*this);

	if (t.Find (&rKT)) {
	CVisPaletteLock l(t);

		if (l) return l;
	}

return NULL;	// nicht gefunden
}

CVisPalette *CVisPaletteTree :: DefinitelyGetPalette (
					pChar &rKT, 
					const char *pDefPal, BOOL &fTemp)
{
CVisPalette *pVP = FFindItem (rKT);

	fTemp = false;
	if (pVP == NULL) {	// diese Palette kenn ich nicht
	// StandardPalette finden bzw. generieren
	char *& rDefKey = (char *&)pDefPal;
	
		pVP = FFindItem (rDefKey);
		if (pVP == NULL) {		// Fehler
			pVP = CVisPalette :: GetDefaultVisPalette();
			if (pVP == NULL) return NULL;
			FAddItem (*pVP);
			DELETE_OBJ (pVP);
			pVP = FFindItem (rDefKey);
			fTemp = true;
		}
	}
	
return pVP;
}


// Diese Funktion zerlegt ein Element des Baumes ------------------------------
void _VMD_EXPORT CVisPaletteTree :: UserDelete (void *pObj)
{
	((CVisPalette *)pObj) -> ~CVisPalette();
}

// Funktion, die Pointer auf den Suchschlüssel liefert ------------------------
pChar * _VMD_EXPORT FCTTreeGetpChar (CVisPalette *pObj)
{
	return & ((CVisPalette *)pObj) -> FGetpChar();
}

// Funktion, die zwei SuchSchlüssel miteinander vergleicht --------------------
int _VMD_EXPORT FCTTreeCmppChar (pChar *pObj1, pChar *pObj2)
{
	return FCmppChar (*pObj1, *pObj2);
}


// Laden aller Paletten aus dem angegebenen Storage ---------------------------
BOOL CVisPaletteTree :: LoadPalettes (LPSTORAGE pIStorage, const char *pPals)
{
	if (pIStorage == NULL) return false;
	
// pIStorage zeigt auf übergeordnetes Storage
LPSTORAGE pIStoragePal = NULL;
LPENUMSTATSTG pIEnumSTATSTG = NULL;
DWORD dwMode = STGM_TRANSACTED | STGM_READWRITE | STGM_SHARE_EXCLUSIVE;
HRESULT hr = pIStorage -> OpenStorage (VMDWideString(pPals), NULL, dwMode, NULL, 0, &pIStoragePal);

	if (FAILED(hr)) {
		if (GetScode(hr) != STG_E_FILENOTFOUND) 
			return false;	// Fehler
	
	// keine Paletten da: StandardPalette erzeugen
	CVisPalette *pDefVPal = CVisPalette :: GetDefaultVisPalette();
	
		dwMode |= STGM_CREATE;
		hr = pIStorage -> CreateStorage (VMDWideString(pPals), dwMode, 0, 0, &pIStoragePal);
		if (FAILED(hr)) return false;

	// GUID reinschreiben (Kontrollmöglichkeit)
		hr = WriteClassStg (pIStoragePal, CLSID_TortenPalette);
		if (FAILED(hr)) {
			pIStoragePal -> Release();
			return hr;
		}

	// DefaultPalette wegschreiben
		if (pDefVPal != NULL) 
			hr = pDefVPal -> Save (pIStoragePal);
		else
			hr = E_OUTOFMEMORY;

		if (FAILED(hr)) {
			pIStoragePal -> Release();
			return false;
		}
		pIStoragePal -> Commit (STGC_DEFAULT);	// wegschreiben
	}

// überprüfen, ob dieses Storage zu uns gehört
CLSID clsid;
	
	hr = ReadClassStg (pIStoragePal, &clsid);
	if (FAILED(hr) || !IsEqualCLSID (clsid, CLSID_TortenPalette)) {
		pIStoragePal -> Release();
		return hr;
	}

	hr = pIStoragePal -> EnumElements (0, NULL, 0, &pIEnumSTATSTG);
	if (FAILED(hr)) {
		pIStoragePal -> Release();
		return false;
	}
	
STATSTG stgT;

	while (pIEnumSTATSTG -> Next (1, &stgT, NULL) == S_OK) {
	// alle Elemente sind Streams und werden eingelesen
	bool fBreak = (stgT.type == STGTY_STREAM && 
		       !FAddItem ((char *)VMDAnsiString(stgT.pwcsName), pIStoragePal)); 

		CoTaskMemFree (stgT.pwcsName);
		if (fBreak) break;
	}

// Interface's freigeben
	pIEnumSTATSTG -> Release();
	pIStoragePal -> Release();
	return true;
}


// Speichern aller Paletten aus dem angegebenen Storage -----------------------
BOOL CVisPaletteTree :: SavePalettes (LPSTORAGE pIStorage, const char *pPals)
{
	if (pIStorage == NULL) return false;
	
// pIStorage zeigt auf übergeordnetes Storage
LPSTORAGE pIStoragePal;
DWORD dwMode = STGM_TRANSACTED | STGM_READWRITE | STGM_SHARE_EXCLUSIVE;
HRESULT hr = pIStorage -> OpenStorage (VMDWideString(pPals), NULL, dwMode, NULL, 0, &pIStoragePal);

	if (FAILED(hr) && GetScode(hr) == STG_E_FILENOTFOUND) {
		dwMode |= STGM_CREATE;
		hr = pIStorage -> CreateStorage (VMDWideString(pPals), dwMode, 0, 0, &pIStoragePal);
		if (FAILED(hr)) return false;
	}
	
// Alle Elemente des Baumes wegschreiben
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CVisPaletteLock l(t);
	
		if (l) {
			hr = l -> Save (pIStoragePal);
			if (FAILED(hr)) break;
		}
	}

// Interface's freigeben
	if (SUCCEEDED(hr))	// wegschreiben der Streams
		pIStoragePal -> Commit (STGC_DEFAULT);
	pIStoragePal -> Release();
	
return true;
}


BOOL CVisPaletteTree :: RetrievePalette (HPALETTE &hPal)
{
CTable t (*this);
bool fChanged = false;

	for (t.First(); t.Valid(); t.Next()) {
	CVisPaletteLock l(t);

		if (!l) continue;
		if (l -> RetrievePalette (hPal))
			fChanged = true;	// Palette wurde geändert
	}

return fChanged;
}

// Enumeration aller Items in dem Baum ----------------------------------------
BOOL CVisPaletteTree :: FEnumAllItems (CVisPaletteEnumFunc pFcn, void *pEData)
{
CTable t(*this);

	for (t.First(); t.Valid(); t.Next()) {
	CVisPaletteLock l(t);

		if (l && pFcn (*(CVisPalette *)l, pEData) == false)
			return false;
	}

return true;
}

// Enumeration aller Objekte mit einem bestimmten SuchSchlüssel ---------------
BOOL CVisPaletteTree  :: FEnumItems (pChar &rKey, CVisPaletteEnumFunc pFcn, void *pEData)
{
CTable t(*this);

	for (t.FindFirst (&rKey); t.Valid(); t.FindNext (&rKey)) {
	CVisPaletteLock l(t);

		if (l && pFcn (*(CVisPalette *)l, pEData) == false)
			return false;
	}

return true;
}

BOOL CVisPaletteTree  :: FReInsert (pChar &roldKey, pChar &rnewKey)
{
CTable t(*this);

	if (t.Find (&roldKey)) 
		return t.ReInsert (&rnewKey, sizeof (rnewKey));

return false;
}

