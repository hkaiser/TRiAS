// Klassendefintion fuer Dialogfenster zur Eingabe der SkalierungsParameter ---
// File: EXPTRANS.HXX

#if !defined(_EXPTRANS_HXX)
#define _EXPTRANS_HXX

class ExportTransDlg : public DialogWindow {
private:
	DoubleNumEdit _LX, _LY, _RX, _RY;
	double _KX, _KY, _OX, _OY;
	double xMin, xMax, yMin, yMax;

	CoordTrans *_pCT;

protected:
	void ButtonClick (ControlEvt);

public:
		ExportTransDlg (pWindow, ObjContainer &, CoordTrans *);
		~ExportTransDlg (void) {}

	double KX (void) { return _KX; }
	double KY (void) { return _KY; }
	double OX (void) { return _OX; }
	double OY (void) { return _OY; }

	Bool ExportTransParams (void);

	CoordTrans *& pCT (void) { return _pCT; }
};

#endif // _EXPTRANS_HXX

