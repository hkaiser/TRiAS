// Memberfunktionen f¸r Maﬂtabsanzeige
// File: MASSTAB2.CXX

#include "triaspre.hxx"

#include "overview.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern COverView *pOverView;	// ‹bersichtsfenster
extern bool OverViewCFlag;	
extern bool LegendToRepaint;

Dimension GetDotsPerMM (HDC);

// Anzeige des aktuellen Maﬂstabes --------------------------------------------
bool IrisWind :: SetMasstab (Rectangle R) 
{
// wenn Rechteck entartet ist, dann nichts ‰ndern
	if (R.Right() == R.Left()) return false;

Rectangle CRc = CanvasRect();

	if (CRc.Left() == CRc.Right()) return false;		// Icon

// Koordinaten in DB-Koordinaten umsetzen
CoordTrans *pCT = DBO().pCT();

	TX_ASSERT(NULL != pCT);

Point ptLO = R.UpperLeft();
Punkt LO = DCtoOC (ptLO);       // Device --> Objekt
Point ptRU = R.LowerRight();
Punkt RU = DCtoOC (ptRU);
double XLO, YLO, XRU, YRU;

	pCT -> UnScale (LO, &XLO, &YLO);
	pCT -> UnScale (RU, &XRU, &YRU);

DoublePair P1 (XLO, YLO);
DoublePair P2 (XRU, YLO);	// ¸ber X-Koordinate berechnen

double dX = 1.0;

	if (pCT -> hasDistEx()) {
	double dY = 1.0;

		pCT -> CoordTransDistanceEx (&P1, &P2, dX, dY);
	} else
		dX = pCT -> CoordTransDistance (&P1, &P2);

Dimension DotsPerMM = GetDotsPerMM (NULL);
long M = (long)((dX * 1000.0 * DotsPerMM.Width()) / ((double)(CRc.Right()-CRc.Left())));

// Maﬂstab muﬂ positiv sein
	if (M < 0L) M = -M;
	DEXN_ScalingChanged (M);

return true;
}

///////////////////////////////////////////////////////////////////////////////
// Einstellen eines neuen Darstellungsmaﬂstabes
// Die Berechnung muﬂ evtl. zweimal vorgenommen werden, da durch ein Auftauchen/
// Verschwinden eines Scrollbars der Maﬂstab verf‰lscht werden kann

bool IrisWind::SetActiveScaling (long lZoom)
{
ObjContainer OC (0, 0, 0, 0);
ObjContainer oldOC = DBO().GetExtend();		// alten Ausschnitt merken
bool fResult = false;
Rectangle rcC (0, 0, 0, 0);

	for (int i = 0; i < 2; i++) {
		rcC = CanvasRect();

	Rectangle rc;
	
		if (NULL != DRO) {
			rc = ((DragRectangleObject *)DRO) -> GetRect();

		// Koordinaten kippen
		CoOrd tmpC = CoOrd(rc.Bottom() - rc.Top());
		
			rc.Bottom() = CoOrd(rc.Top() - tmpC);
		} else
			rc = rcC;
				
		fResult = DBO().SetActiveScaling (lZoom, rc, rcC, OC);
		if (!fResult) break;
	
	// neuen Ausschnitt einstellen
		DBO().SetExtend (this, OC, AspectRatio);

	// bei Bedarf ScrollBars einblenden und initialisieren
		if (!InitWndScrollBars())
			break;		// einmal reicht, wenn Scrollbars nicht ge‰ndert wurden
	}

// wenn Erfolgreich, dann alles neu einstellen
	if (fResult) {
		DELETE (DRO);

	// ‹bersichtsfenster bedienen
		if (OverViewCFlag && pOverView) {
		Rectangle rcC = CanvasRect();
		ObjContainer OC (rcC);
		
			pOverView -> SetActVP (OC);
		}

		actClip.Push (oldOC);

	// neu zeichnen
		LegendToRepaint = true;
		m_fRePaintFlag = true;
		RePaint();
	}

return fResult;
}

