// Klassendefinition fÅr Koordinatenanzeige
// File: COORDS.HXX

#if !defined(_COORDS_HXX)
#define _COORDS_HXX

#if !defined(NOCOORDS)
class CoordsDlg : public ModeLessDialog {
private:
// Controls
	FixedText CoordX;       // Anzeige der X-Koordinate
	FixedText CoordY;       // Anzeige der Y-Koordinate
	FixedText DeltaX;       // zweites Koordinatenpaar
	FixedText DeltaY;       // entweder Delta oder zweiter Punkt
	FixedText Delimiter;

	double _XStart, _YStart;        // Anfangspunkt der Messung

// Anzeigemode
	Bool _Mode;             // FALSE: ein Koordinatenpaar
				// TRUE:  zwei Koordinatenpaare
	Bool _ModeChanged;      // Mode ist umzuschalten
	Bool _Delta;            // zweites Koordinatenpaar als Deltawerte
	Bool _Start;            // Begin der Messung
	Dimension dim;
	Point m_ptLast;		// letzte angezeigte Koordinate

	CoordTrans *_pCT;	// nur Kopie, darf nicht freigegeben werden !


// Eingestellten Mode wirksam machen
	void AdjustMode (void);
	void HandleDisplay (Point &rPt);

protected:
	Bool QueryClose (Event);

public:
// enums
	enum CoordMode { CM_Normal, CM_Rectangle, CM_Measure, };

// Konstruktor
		CoordsDlg (pWindow pW, CoordTrans *);

// Memberfuntkionen
	void SetCoords (Point &);
	void RefreshCoords (void);
	void SetMode (CoordMode Mode);

	CoordTrans *&pCT (void) const { return (CoordTrans *&)_pCT; }
};
#endif // NOCOORDS

#endif // _COORDS_HXX
