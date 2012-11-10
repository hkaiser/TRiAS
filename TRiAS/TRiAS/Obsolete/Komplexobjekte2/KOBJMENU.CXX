// Verwaltung von Objektmerkmalen ---------------------------------------------
// File: FEATMENU.CXX

#include "featurep.hxx"
#include "feature.h"		// ResourceKonstanten

#include "selidlst.hxx"
#include "selident.hxx"

#include "classdlg.hxx"

#include "cgobject.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

bool CFeatureExtension :: FindDupFeatures (void) 
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
CUIdentObjects AllObjs;		// Baum für alle Objekte (HilfsTree)

	m_DupObjs.EveryDelete();	// für alle Fälle noch mal

// für alle markierten Ident/OTyp-Kombinationen
	if (pDlg -> GetFirstIdent (lIdent, iOTyp)) {
		do {
			FillTrees (lIdent, iOTyp, lMCode, AllObjs, m_DupObjs);
		} while (pDlg -> GetNextIdent (lIdent, iOTyp));
	}
        DELETE (pDlg);

long lCount = m_DupObjs.Count();

	if (lCount == 0) {
		MessageBeep (MB_OK);
		return false;
	}
	
// Objektfeld zusammenstellen
long *pObjs = new long [lCount];

	if (pObjs == NULL) return false;

CTable t(m_DupObjs);
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

// Doppelte Objekte in m_DupObjs finden und Funktion rufen --------------------
bool CFeatureExtension :: ScanTreeForDupObjects (DUPOBJPROC pDupProc, DWORD dwData)
{
CTable t1(m_DupObjs);
bool fDupObjs = false;	// doppelte Objekte gefunden

	for (t1.First(); t1.Valid(); t1.Next()) {
	CObjUIdentLock l(t1);
		
		TX_ASSERT(NULL != (CObjUIdent *)l);
		if (!isSelected (m_hORWnd, l -> ObjNr())) continue;
			
	CGObject O1 (l -> ObjNr());	// erstes Objekt
	CTable t2(t1);

//		DEXOR_ActivateObject (m_hORWnd, O1.lONr());	// ORWnd laufend halten
		for (t2.Next(); t2.Valid(); ) {
		LONG lONr2 = -1L;

			{
			CObjUIdentLock l2(t2);

				TX_ASSERT(NULL != (CObjUIdent *)l2);
				if (strcmp (l2 -> Text(), l -> Text()))
					break;	// Merkmale nicht mehr gleich
				lONr2 = l2 -> ObjNr();
			} // Lock aufheben, damit gelöscht werden kann

		CGObject O2 (lONr2);
		bool fDelete = false;

			if (O1.isEqual (O2/*, default:CMP_ALL*/)) {
			// Objekte sind identisch
				fDelete = pDupProc (O1, O2, dwData);
				fDupObjs = true;
			}

		// auf nächstes Element stellen
			if (fDelete) t2.Delete();	// stellt auf nächstes Element
			else	     t2.Next();

		// MessageSchleife
			App :: Exec (ExecWhileEvent);
		}
	}

return fDupObjs;
}

// Klassifikation der Merkmalswerte eines MerkmalsCodes -----------------------
bool CFeatureExtension :: ClassifyFeatures (void) 
{
// Dialogfenster anzeigen
CSelectIdentDlg *pDlg = CSelectIdentDlg :: CreateInstance (MWind(), 
				ResID (SELECTIDENTSDLG, &g_pTE -> RF()));
				
	if (pDlg == NULL) return false;
	pDlg -> SetCaption (ResString (ResID (IDS_CLASSIFYCAPTION, &g_pTE -> RF()), 64).Addr());
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
CUIdentObjects AllObjs;		// Baum für alle Objekte (HilfsTree)
CUIdentObjects DupObjs;		// Baum für doppelte Objekte

// für alle markierten Ident/OTyp-Kombinationen
	if (pDlg -> GetFirstIdent (lIdent, iOTyp)) {
		do {
			FillTrees (lIdent, iOTyp, lMCode, AllObjs, DupObjs);
		} while (pDlg -> GetNextIdent (lIdent, iOTyp));
	}
        DELETE (pDlg);

long lCount = AllObjs.Count();

	if (lCount == 0) {
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

