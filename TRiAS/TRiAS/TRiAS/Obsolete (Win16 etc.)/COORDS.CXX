// Memberfunktionen für Koordinatenanzeige ------------------------------------
// File: COORDS.CXX

#include "triaspre.hxx"

#include "coords.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern bool CoordsCFlag;        // Fenster ist angezeigt

// Konstruktor ----------------------------------------------------------------
#pragma warning (disable: 4355)

CoordsDlg :: CoordsDlg (pWindow pW, CoordTrans *pCTF)
	   : ModeLessDialog (pW, ResID (KOORDINATEN)),
	     CoordX (this, IDT_KOORDX), CoordY (this, IDT_KOORDY),
	     DeltaX (this, IDT_DELTAX), DeltaY (this, IDT_DELTAY),
	     Delimiter (this, IDT_DELIMITER),
	     _pCT (pCTF), m_ptLast(0, 0)
{
// Fenster in linke untere Ecke Positionieren
	ChangePosition (Point (0, 0));
	dim = GetSize();

// Fenster im ersten Mode anzeigen (ein Koordinatenwert)
	_Mode = CM_Normal;              // mit nur einem Koordinatenpaar beginnen
	AdjustMode();
	_Delta = false;
	_Start = false;
}

#pragma warning (default: 4355)

inline double sqr(double X) { return X*X; }

// Anzeige der aktuellen Koordinaten
static short iSem = false;

void CoordsDlg :: SetCoords (Point &inPt) 
{
	m_ptLast = inPt;
	HandleDisplay (inPt);
}

void CoordsDlg :: RefreshCoords (void) 
{
	HandleDisplay (m_ptLast);
}

void CoordsDlg :: HandleDisplay (Point &inPt)
{
	if (iSem == true) return;
	iSem = true;

// wenn AnzeigeMode verändert wurde, dann diesen realisieren
	if (_ModeChanged == true) 
		AdjustMode();

// Koordinaten in DB-Koordinaten umsetzen
Punkt Pt = DCtoOC (inPt);       // Device --> Objekt

// Koordinaten transformieren (incl. rausrechnen der internen Skalierung)
double XOut, YOut;

	pCT() -> UnScale (Pt, &XOut, &YOut);

// temporäre Zeichenketten
char OutBuff[40];

	switch (_Mode) {
	case CM_Normal:         // erstes Koordinatenpaar
		{
		// Koordinaten korrigieren
			pCT() -> Transform (&XOut, &YOut);

		// Koordinaten ausgeben        
			pCT() -> CoordTransToStringEx (XOut, YOut, true, OutBuff, sizeof(OutBuff));
			CoordX.SetText (OutBuff);
			pCT() -> CoordTransToStringEx (XOut, YOut, false, OutBuff, sizeof(OutBuff));
			CoordY.SetText (OutBuff);
		}
		break;

	case CM_Measure:
		{
			if (_Start == true) {
			// erster Wert
				_XStart = XOut;
				_YStart = YOut;
				_Start = false;
			}

		DoublePair DP (XOut, YOut);
		DoublePair DStart (_XStart, _YStart);

			DtoA (OutBuff, "%8.3f", pCT() -> CoordTransDistance (&DP, &DStart)/1000.0);
			strcat (OutBuff, " ");
			strcat (OutBuff, ResString (IDS_KILOMETER, 10));
			CoordY.SetText (OutBuff);
		}
		break;

	case CM_Rectangle:
		if (!_Delta) {
		// Koordinaten korrigieren                      
			pCT() -> Transform (&XOut, &YOut);

		// zweites Paar als Punktwert anzeigen
			pCT() -> CoordTransToStringEx (XOut, YOut, true, OutBuff, sizeof(OutBuff));
			DeltaX.SetText (OutBuff);
			pCT() -> CoordTransToStringEx (XOut, YOut, false, OutBuff, sizeof(OutBuff));
			DeltaY.SetText (OutBuff);
		}
		break;

	default:
		TX_ASSERT(false);
	}
	iSem = false;
}

// Abfrage, ob Fenster geschlossen werden soll
bool CoordsDlg :: QueryClose (Event) {

	CoordsCFlag = false;

return true;            // auf jeden Fall raus
}

// neuen Mode einstellen
void CoordsDlg :: SetMode (CoordMode newMode) 
{
	if (newMode != _Mode) {
		_Mode = newMode;
		if (_Mode == CM_Normal || _Mode == CM_Measure) {
			if (_Mode == CM_Measure)
				_Start = true;
			if (_ModeChanged == false) {
				AdjustMode();   
					// wenn auf ein Koordinatenpaar
					// zurückgeschaltet werden soll
					// dann sofort ausführen
			} else 
				_ModeChanged = false;
				
		} else 
			_ModeChanged = true;    // ansonsten erst nach MouseMove
	}
}


// Anzeigeform anpassen
void CoordsDlg :: AdjustMode (void) 
{
Point Pt;       // aktuelle FensterPosition
Dimension Dim;  // aktuelle FensterGröße
long BaseUnits = GetDialogBaseUnits();

	if (_Mode == CM_Rectangle) {
	// zwei Koordinaten anzeigen 
	// neu Positionieren
		Pt = GetPosition();
		Dim = GetSize();
		ChangeSize (dim);
		ChangePosition (Pt);
	// Controls anzeigen
		DeltaX.Show();
		DeltaY.Show();
		Delimiter.Show();
		CoordY.Show();
	} else {
	// nur ein Koordinatenpaar anzeigen
	// Controls nicht mehr anzeigen
		DeltaX.Hide();
		DeltaY.Hide();
		Delimiter.Hide();
	// neu Positionieren
		Pt = GetPosition();
		ChangeSize (Dimension (dim.Width(), 
				       CoOrd(dim.Height()-(7*HIWORD(BaseUnits))/8)));
		ChangePosition (Pt);
		if (_Mode == CM_Measure)
			CoordX.SetText(ResString (IDS_ENTFERNUNG, 15));
		else
			CoordY.SetText("");
	}
	Update();		// sofort zeichnen
	_ModeChanged = false;   // Anzeige entspricht aktuellem Mode
}

