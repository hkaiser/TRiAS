// DialogBox fuer Buffering-ParameterEingabe
// File: SBUFFER.HXX

#if !defined(_SBUFFER_HXX)
#define _SBUFFER_HXX

#if !defined(NOBUFFERDLG)

const short NUMDISTS = 20;	// max. Anzahl der Buffer
const short BUFFERPARLEN = 200;	// max. L„nge der EingabeZeichenkette

class GeoDB;

class BufferParDlg : public DialogWindow {
// Controls
	PushButton OKButton, CancelButton, HelpButton;
	NumEdit SLEDistances;
	ComboBox Units;

	long *_Distances;	// eingelesene Abst„nde
	short _NumDists;	// Anzahl der eingelesenen Abst„nde

	GeoDB &_DB;

protected:
	void ButtonClick (ControlEvt);		// EventHandler

	long *ReadDistances (char *, short &);

public:
// Konstruktor
		BufferParDlg (pWindow pW, GeoDB &geoDB);

// Member 
	long *GetDistances (void) { return _Distances; }
	short GetNumDists (void) { return _NumDists; }
};

#endif // NOBUFFERDLG

#endif // _SBUFFER_HXX
