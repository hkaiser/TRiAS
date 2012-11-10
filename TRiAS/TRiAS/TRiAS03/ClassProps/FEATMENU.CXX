// Verwaltung von Objektmerkmalen ---------------------------------------------
// File: FEATMENU.CXX

#include "featurep.hxx"
#include "feature.h"		// ResourceKonstanten

#include "selidlst.hxx"
#include "selident.hxx"

#include "classdlg.hxx"

#include "cgobject.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


// Anzeige der Objekte in einem Baum (der doppelten Objekte) in einem ORWnd ---
bool CFeatureExtension :: ShowDupsInORWnd (CUIdentObjects &rDupObjs, long lMCode)
{
long lCount = rDupObjs.Count();

	if (lCount == 0) {
		MessageBeep (MB_OK);
		return false;
	}
	
// Objektfeld zusammenstellen
long *pObjs = new long [lCount];

	if (pObjs == NULL) return false;

CTable t(rDupObjs);
long lIndex = 0;

	for (t.First(); t.Valid() && lIndex < lCount; t.Next()) {
	CObjUIdentLock l(t);
	
		if (!l) continue;
		pObjs[lIndex++] = l -> ObjNr();
	}
	
// ORFenster mit Result aufbauen
	GenerateObjWnd (lMCode, pObjs, lCount, IDS_DUPCAPTION);
	DELETE (pObjs);
		
return true;
}


// Doppelte Objekte in rDupObjs finden und Aktion auslösen --------------------
bool CFeatureExtension :: ScanTreeForDupObjects (
	CUIdentObjects &rDupObjs, LPPROPERTYACTION pIAction)
{
CTable t1(rDupObjs);
bool fDupObjs = false;		// doppelte Objekte gefunden
CEnumObjectsByNumber *pEnum = NULL;

// Baum durchgehen und Objekte mit jeweils gleichem Merkmal zusammenfassen
	for (t1.First(); t1.Valid(); t1.Next()) {
	CObjUIdentLock l(t1);
		
		TX_ASSERT(NULL != (CObjUIdent *)l);

	// Enumerator, der alle Objekte mit identischem Merkmal enthält
		pEnum = CEnumObjectsByNumber::CreateInstance();
		if (NULL == pEnum) break;	// Abbrechen, da Fehler

		if (!pEnum -> AddObject (l -> ObjNr()))	// erstes Objekt immer dazu
			break;			// Abbrechen, da Fehler

	// innere Schleife geht vom nächsten Objekt bis zum ersten mit 
	// ungleichem Merkmal
	CTable t2(t1);

		for (t2.Next(); t1.Valid() && t2.Valid(); ) {
			{
			CObjUIdentLock l2(t2);

				TX_ASSERT(NULL != (CObjUIdent *)l2);
				if (strcmp (l2 -> Text(), l -> Text()))
					break;	// Merkmale nicht mehr gleich
				
				if (!pEnum -> AddObject (l2 -> ObjNr()))
					break;	// Abbrechen, da Fehler
				fDupObjs = true;
			} // Lock aufheben

		// auf nächstes Element stellen
			t2.Next();
			t1.Next();

		// MessageSchleife
			App :: Exec (ExecWhileEvent);	// ???
		}

	// eigentliche Aktion ausführen, was auch immer
		if (FAILED(pIAction -> DoAction (pEnum, 0L)))
			break;

		pEnum -> Release();
		pEnum = NULL;
	}
	if (pEnum) pEnum -> Release();

return fDupObjs;
}


CGObject O1 (lONr1);
CGObject O2 (lONr2);
bool fDelete = false;

	if (O1.isEqual (O2/*, default:CMP_ALL*/)) {
	// Objekte sind identisch
		fDelete = pDupProc (O1, O2, dwData);
		fDupObjs = true;
	}



// Klassifikation der Merkmalswerte eines MerkmalsCodes -----------------------
// der MerkmalsCode wird für die Anzeige im ORFenster benötigt
bool CFeatureExtension :: ClassifyFeatures (
	CUIdentObjects &rAllObjs, CUIdentObjects &rDupObjs, long lMCode)
{
// --> AnalyzeIdentObjects
	if (0 == AllObjs.Count()) {
		MessageBeep (MB_OK);
		return false;
	}
	
// Fenster mit MerkmalsKlassen anzeigen
CClassifiedDlg *pCDlg = CClassifiedDlg :: CreateInstance (
		MWind(), ResID (IDD_CLASSIFIED_FEATURES, &g_pTE -> RF()),
		AllObjs, DupObjs, lMCode);
		
	if (pCDlg == NULL) return false;

	pCDlg -> Show();

bool fResult = pCDlg -> Result();	// abgebrochen ?

        DELETE (pCDlg);

return fResult;
}


///////////////////////////////////////////////////////////////////////////////
// Objekte ausgewählter Objektklassen analysieren und nach einem identischem 
// Merkmal zusammenstellen
bool CFeatureExtension :: AnalyzeIdentObjects (
	CUIdentObjects &rAllObjs, CUIdentObjects &rDupObjs, long *plMCode)
{
// Dialogfenster anzeigen
CSelectIdentDlg *pDlg = CSelectIdentDlg :: CreateInstance (MWind(), 
				ResID (SELECTIDENTSDLG, &g_pTE -> RF()));
				
	if (pDlg == NULL) return false;
	pDlg -> Show();
	if (!pDlg -> Result()) {
		DELETE(pDlg);
		return false;	// abgebrochen
	}
	
// abarbeiten des Geforderten
CEierUhr Wait (MWind());	// EierUhr anzeigen

long lIdent = -1L;
short iOTyp = 0;
long lMCode = pDlg -> GetMCode();

// für alle markierten Ident/OTyp-Kombinationen
	if (pDlg -> GetFirstIdent (lIdent, iOTyp)) {
		do {
			FillTrees (lIdent, iOTyp, lMCode, rAllObjs, rDupObjs);
		} while (pDlg -> GetNextIdent (lIdent, iOTyp));
	}
        DELETE (pDlg);
	if (plMCode) *plMCode = lMCode;

return true;
}

///////////////////////////////////////////////////////////////////////////////
// CallBackfuntkionen für Analyse der Objekte ---------------------------------
typedef struct tagENUMDOCDATA {
	CUIdentObjects *m_pUIObjs;
	CUIdentObjects *m_pDupObjs;
	ULONG m_lMCode;
	char *m_pMWert;
} ENUMDOCDATA;

extern "C" 
bool PASCAL _XTENSN_EXPORT GetObjectsFromEnumEx (
				long lONr, DWORD dwOTyp, void *pData)
{
ENUMDOCDATA *pEOD = (ENUMDOCDATA *)pData;
	
// Merkmal abfragen
	if (!ReadTextMerkmal (TT_Objekt, lONr, pEOD -> m_lMCode, pEOD -> m_pMWert, _MAX_PATH))
		return true;	//  hat keine UIdent, weitermachen

// wenn dieser UIdent bereits im Baum ist, dann beide Objekte speichern
CObjUIdent *pObj = pEOD -> m_pUIObjs -> FFindItem (pEOD -> m_pMWert);

	if (pObj != NULL) {
		pObj -> Increment();	// hochzählen

	// UIdent ist nicht zum ersten mal da
		if (!pEOD -> m_pDupObjs -> FFindItem (pEOD -> m_pMWert)) 
		// gefundenes Objekt in doppelte Liste einhängen, da erstes doppeltes
			pEOD -> m_pDupObjs -> FAddItem (pEOD -> m_pMWert, pObj -> ObjNr(), pObj -> OTyp());

	// jetzt noch neues Objekt in doppelte Liste reinhängen
		return pEOD -> m_pDupObjs -> FAddItem (pEOD -> m_pMWert, lONr, short(dwOTyp));
	}

// lediglich in Baum reinhängen
return pEOD -> m_pUIObjs -> FAddItem (pEOD -> m_pMWert, lONr, short(dwOTyp));
}


///////////////////////////////////////////////////////////////////////////////
// Objekte aus einem ORFenster analysieren und zusammenstellen ----------------
bool FillTreesFromORWindow (HWND hORWnd, short iOTyp, long lMCode, 
		CUIdentObjects &rAllObjs, CUIdentObjects &rDupObjs)
{
	TX_ASSERT(NULL != hORWnd);

// alle selektierten Objekte des Fensters analysieren
ENUMDOCDATA EDD;

	EDD.m_lMCode = lMCode;
	EDD.m_pUIObjs = &rAllObjs;
	EDD.m_pDupObjs = &rDupObjs;
	EDD.m_pMWert = new char [_MAX_PATH];

ENUMLONGKEYEX ELK;

	ELK.eKey = LONG(hORWnd);
	ELK.eFcn = (ENUMLONGKEYPROC)GetObjectsFromEnumEx;
	ELK.ePtr = &EDD;
	ELK.eData (DWORD)iOTyp;

bool fResult = DEX_EnumSelectedObjectsEx (ELK);

	DELETE (EDD.m_pMWert);

return fResult;
}

// doppelte Merkmale für eine Ident/OTyp-Kombination suchen -------------------
bool FillTreesFromIdent (long lIdent, short iOTyp, long lMCode, 
		CUIdentObjects &rAllObjs, CUIdentObjects &rDupObjs)
{
// Bäume füllen
ENUMDOCDATA EDD;

	EDD.m_lMCode = lMCode;
	EDD.m_pUIObjs = &rAllObjs;
	EDD.m_pDupObjs = &rDupObjs;
	EDD.m_pMWert = new char [_MAX_PATH];

ENUMLONGKEYEX ELK;

	ELK.eKey = lIdent;
	ELK.eFcn = (ENUMLONGKEYEXPROC)GetObjectsFromEnumEx;
	ELK.ePtr = &EDD;
	ELK.eData = (DWORD)iOTyp;
	
bool fResult = DEX_EnumIdentObjectsEx (ELK);

	DELETE(EDD.m_pMWert);

return fResult;
}


