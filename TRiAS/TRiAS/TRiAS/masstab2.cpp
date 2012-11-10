// Memberfunktionen f¸r Maﬂtabsanzeige
// File: MASSTAB2.CXX

#include "triaspre.hxx"

#include "overview.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern COverViewClientWindow *pOverView;	// ‹bersichtsfenster
extern bool OverViewCFlag;	
extern bool LegendToRepaint;

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
	if (NULL == pCT) return false;

Point ptLO = R.UpperLeft();
Punkt LO = DCtoOC (ptLO);       // Device --> Objekt
Point ptRU = R.LowerRight();
Punkt RU = DCtoOC (ptRU);

#if defined(_KOORD_ISDOUBLE)
DoublePair P1 (LO.GetX(), LO.GetY());
DoublePair P2 (RU.GetX(), LO.GetY());	// ¸ber X-Koordinate berechnen
#else
double XLO, XRU, YLO, YRU;

	pCT() -> UnScale (LO, &XLO, &YLO);
	pCT() -> UnScale (RU, &XRU, &YRU);

DoublePair P1 (XLO, YLO);
DoublePair P2 (XRU, YLO);	// ¸ber X-Koordinate berechnen
#endif // _KOORD_ISDOUBLE

double dX = 1.0;

	if (pCT -> hasDistEx()) {
	double dY = 1.0;

		pCT -> CoordTransDistanceEx (&P1, &P2, dX, dY);
	} else
		dX = pCT -> CoordTransDistance (&P1, &P2);

DoublePair dimD;
Dimension DotsPerMM (GetDotsPerMM (NULL, &dimD));
long M = (long)((fabs(dX) * 1000.0 * dimD.Width()) / ((double)(CRc.Right()-CRc.Left())));

// Maﬂstab muﬂ positiv sein
	if (M < 0L) 
		M = -M;

	if (0 != m_lFakeZoom)
		DEXN_ScalingChanged (m_lFakeZoom);
	else
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
	
		if (NULL != m_pDRO) {
			rc = ((DragRectangleObject *)m_pDRO) -> GetRect();

		// Koordinaten kippen
		CoOrd tmpC = CoOrd(rc.Bottom() - rc.Top());
		
			rc.Bottom() = CoOrd(rc.Top() - tmpC);
		} else
			rc = rcC;
				
		fResult = DBO().SetActiveScaling (lZoom, rc, rcC, OC);
		if (!fResult) break;
	
	// neuen Ausschnitt einstellen
		SetExtend (OC, lZoom);

	// bei Bedarf ScrollBars einblenden und initialisieren
		if (!InitWndScrollBars())
			break;		// einmal reicht, wenn Scrollbars nicht ge‰ndert wurden
	}

// wenn Erfolgreich, dann alles neu einstellen
	if (fResult) {
		DELETE_OBJ (m_pDRO);

	// ‹bersichtsfenster bedienen
		if (OverViewCFlag && pOverView) 
			pOverView -> SetActVP (CanvasRect());
		actClip.Push (oldOC);

	// neu zeichnen
		LegendToRepaint = true;
		m_fRePaintFlag = true;
		RePaint();
	}

return fResult;
}

