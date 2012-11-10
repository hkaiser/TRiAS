// Memberfunktionen fuer Masstabsanzeige
// File: MASSTAB.CXX

#include "triaspre.hxx"

#include "masstab.hxx"

extern Bool MasstabCFlag; 
extern MasstabDlg *pMasstab;

Dimension GetDotsPerMM (HDC);

// MenuSelectBearbeitungen ----------------------------------------------------
bool IrisWind :: MenuSelectMasstab (void) 
{
	if (MasstabCFlag) {             // Anzeige ganz ausschalten
		if (pMasstab) {
			pMasstab -> Hide();
			delete pMasstab;
			pMasstab = NULL;
		}
	} else {
		if (!pMasstab)
			pMasstab = new MasstabDlg (this, DBO().pCT());
		if (!pMasstab) 
			return false;		// Fehler
		pMasstab -> SetMasstab (CanvasRect());
		pMasstab -> Show();     // neu anzeigen
		SetFocus();
		ValidateWindow();       // kein RePaint()
	}
	MasstabCFlag = !MasstabCFlag;

return true;
}


// Konstruktor ----------------------------------------------------------------
#pragma warning (disable:4355)

MasstabDlg :: MasstabDlg (pWindow pW, CoordTrans *pCTF)
	    : ModeLessDialog (pW, ResID (MASSTABDLG)),
	      Masstab (this, ResID (IDT_MASSTAB)),
	      _pCT (pCTF)
{
// Fenster in linke untere Ecke Positionieren
	ChangePosition (Point (0, 54));

// aktuelle Bildschirmauflˆsung holen
	_DotsPerMM = GetDotsPerMM (NULL);

// Bezugsfenster merken
	_pW = pW;
}

#pragma warning (default:4355)

// Anzeige des aktuellen Maﬂstabes --------------------------------------------
void MasstabDlg :: SetMasstab (Rectangle R) 
{
// wenn Rechteck entartet ist, dann nichts ‰ndern
	if (R.Right() == R.Left()) return;

Rectangle CRc = _pW -> CanvasRect();

	if (CRc.Left() == CRc.Right()) return;		// Icon

// Koordinaten in DB-Koordinaten umsetzen
Point ptLO = R.UpperLeft();
Punkt LO = DCtoOC (ptLO);       // Device --> Objekt
Point ptRU = R.LowerRight();
Punkt RU = DCtoOC (ptRU);
double XLO, YLO, XRU, YRU;

	pCT() -> UnScale (LO, &XLO, &YLO);
	pCT() -> UnScale (RU, &XRU, &YRU);

DoublePair P1 (XLO, YLO);
DoublePair P2 (XRU, YLO);	// ¸ber X-Koordinate berechnen

double dX = 1.0;

	if (pCT() -> hasDistEx()) {
	double dY = 1.0;

		pCT() -> CoordTransDistanceEx (&P1, &P2, dX, dY);
	} else
		dX = pCT() -> CoordTransDistance (&P1, &P2);

char OutBuff[40];		// tempor‰re Zeichenkette
long M = (long)((dX * 1000.0 * _DotsPerMM.Width()) / ((double)(CRc.Right()-CRc.Left())));

// Maﬂstab anzeigen
	if (M < 0L) M = -M;

	if (M >= 1000000L) {
	short iMill = (short)(M / 1000000L);
	short iTaus = (short)((M % 1000000L) / 1000L);
	short iEin = (short)(M % 1000L);

		wsprintf (OutBuff, "1 : %d.%03d.%03d", iMill, iTaus, iEin);
	} else if (M >= 1000L) {
	short iTaus = (short)(M / 1000L);
	short iEin = (short)(M % 1000L);

		wsprintf (OutBuff, "1 : %d.%03d", iTaus, iEin);
	} else {
		wsprintf (OutBuff, "1 : %ld", M);
	}
	Masstab.SetText (OutBuff);
}

// Abfrage, ob Fenster geschlossen werden soll --------------------------------
Bool MasstabDlg :: QueryClose (Event) 
{
	MasstabCFlag = FALSE;

return TRUE;            // auf jeden Fall raus
}

// Eventhandler f¸r FocusChangeEvt --------------------------------------------
void MasstabDlg :: FocusChange (FocusChangeEvt) {}
/*
	if (!e.gotFocus()) 	// hat Focus abgegeben
		_pW -> SetFocus();
}
*/


