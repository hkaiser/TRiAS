// Verwaltung von Objektmerkmalen ---------------------------------------------
// File: FEATMENU.CXX

#include "featurep.hxx"
#include "feature.h"		// ResourceKonstanten

#include "selidlst.hxx"
#include "selident.hxx"

bool CFeatureExtension :: FindDupFeatures (void) 
{
// Dialogfenster anzeigen
CSelectIdentDlg *pDlg = CSelectIdentDlg :: CreateInstance (MWind(), 
				ResID (SELECTIDENTSDLG, &g_pTE -> RF()));
				
	if (pDlg == NULL) return false;

	pDlg -> Show();
	if (!pDlg -> Result()) return false;	// abgebrochen
	
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
CREATEOBJEKTINFOEX COI;
ResString resCaption (ResID (IDS_DUPCAPTION, &RF()), 64);
POINT pt;

	pt.x = 0, pt.y = 0;
	
	INITSTRUCT (COI, CREATEOBJEKTINFOEX);
	COI.lpCaption = (char *)resCaption.Addr();
        COI.plObjs = pObjs;
        COI.iNumObjs = short(lCount);
        COI.cMColor = RGB(255, 0, 0);
        COI.pntPos = pt;
	COI.m_iFlags = ROSortText;
	
// anstelle des IdentKurztextes soll das doppelte Merkmal angezeigt werden
	m_lMCode = lMCode;		// untersuchter MerkmalsCode
	RegisterNotification (DEX_QUERYRECHOBJECT);
        DEX_CreateObjektInfo (COI);	// ORFenster erzeugen
	UnRegisterNotification (DEX_QUERYRECHOBJECT);
	m_lMCode = 0L;
		        
	DELETE (pObjs);
		
return true;
}

// Doppelte Objekte in m_DupObjs finden und löschen ---------------------------
bool CFeatureExtension :: ScanTreeForDupObjects (bool &fError)
{
CTable t(m_DupObjs);
string strFeat = "";
ULONG lONr = 0L;
bool fObjDeleted = false;	// doppelte Objekte gefunden

	for (t.First(); t.Valid(); ) {
	bool fDelete = false;

		{
		CObjUIdentLock l(t);

			if (!l) continue;

		// RechercheStaus abfragen
		RECHOBJECT ro;

		        INITSTRUCT (ro, RECHOBJECT);
		        ro.lONr = l -> ObjNr();
		        DEXOR_QueryRechercheStatus (m_hORWnd, ro);

		        if (!(ro.iFlags & RSListed)) continue;      // nicht in ORFenster

		// RechercheStaus merken
		        if (!(ro.iFlags & RSSelected))
				continue;		// nicht selektiert
			
			if (lONr == 0L || strFeat != l -> Text()) {
			// erstes oder nächstes Merkmal
				lONr = l -> ObjNr();
				strFeat = l -> Text();
			} else {
			// Merkmale identisch, gesamte Objekte vergleichen
				if (CompareObjs (lONr, l -> ObjNr())) {
				// beide Objekte sind identisch
					if (!DEX_DeleteObjectEx (l -> ObjNr())) {
						fError = true;
						return false;
					}
					fDelete = true;
				}
			}
		}

	// auf nächstes Element stellen
		if (fDelete) {
			t.Delete();	// stellt auf nächstes Element
			fObjDeleted = true;
		} else
			t.Next();

	// MessageSchleife
		App :: Exec (ExecWhileEvent);
	}

return fObjDeleted;
}

// Vergleich zweier Objekte auf Identität -------------------------------------
bool CompareObjs (ULONG lONr1, ULONG lONr2)
{
// ObjektStatistik besorgen
OBJGEOMETRIE OG1;
OBJGEOMETRIE OG2;

	INITSTRUCT (OG1, OBJGEOMETRIE);
	INITSTRUCT (OG2, OBJGEOMETRIE);
	OG1.lONr = long(lONr1);
	OG2.lONr = long(lONr2);
	
	if (!DEX_GetObjStatistik (OG1) || !DEX_GetObjStatistik (OG2))
		return false;	// Fehler heißt nicht identisch

	if (OG1.lIdent != OG2.lIdent) return false;	// Idents ungleich
	if (OG1.iObjTyp != OG2.iObjTyp) return false;	// ObjektTyp ungleich
	if (OG1.lCnt != OG2.lCnt) return false;		// ungleiche Stützpunktanzahl
	if (OG1.iKCnt != OG2.iKCnt) return false;	// ungleiche KonturAnzahl

// so weit, so gut, jetzt Geometrie selbst vergleichen
bool fResult = false;

	if (GetObjectGeometrie (OG1) && GetObjectGeometrie (OG2)) {
		fResult = !memcmp (OG1.pdblX, OG2.pdblX, sizeof(long)*OG1.lCnt);
		if (fResult) fResult = !memcmp (OG1.pdblY, OG2.pdblY, sizeof(long)*OG1.lCnt);
		if (fResult) {
			switch (OG1.iObjTyp) {
			case OGFlaeche:
				fResult = !memcmp (OG1.plCnt, OG2.plCnt, sizeof(long)*OG1.iKCnt);
				break;

			case OGText:
				fResult = !strncmp (((TEXTGEOMETRIE &)OG1).pText,
						    ((TEXTGEOMETRIE &)OG2).pText,
						    OG1.iKCnt);
				break;

			default:
				break;
			}
		}
	}

	FreeObjGeometrie (OG1);
	FreeObjGeometrie (OG1);

return fResult;
}


// Objektgeometrie besorgen ---------------------------------------------------
bool GetObjectGeometrie (OBJGEOMETRIE &rOG)
{
// Felder anfordern
	rOG.pdblX = new long [rOG.lCnt];
	rOG.pdblY = new long [rOG.lCnt];
	if (rOG.pdblX == NULL || rOG.pdblY == NULL) 
		return NULL;
		
	if (rOG.iKCnt > 0) {
		if (rOG.iObjTyp == OGFlaeche) {
			rOG.plCnt = new long [rOG.iKCnt];
			if (rOG.plCnt == NULL) 
				return NULL;
		} else if (rOG.iObjTyp == OGText) {
			((TEXTGEOMETRIE &)rOG).pText = new char [rOG.iKCnt+1];
			if (((TEXTGEOMETRIE &)rOG).pText == NULL) 
				return false;
		}
	}

return DEX_GetObjGeometrie (rOG);
}

void FreeObjGeometrie (OBJGEOMETRIE &rOG)
{
	DELETE (rOG.pdblX);
	DELETE (rOG.pdblY);
	DELETE (rOG.plCnt);
}
