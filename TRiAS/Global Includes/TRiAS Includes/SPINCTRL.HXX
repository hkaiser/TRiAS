// Definition eines kombinierten FixedText/SpinButton/EditControl -------------
// File SPINCTRL.HXX

#if !defined(_SPINCTRL_HXX)
#define _SPINCTRL_HXX

class _TRIAS03_ENTRY SpinEdit : public NumEdit {
protected:
	Range _R;	// Grenzwerte für die Eingabe

public:
// Konstruktoren
	EXPORT03 SpinEdit (pDialogWindow, ResID, Range);

// sonstige Member
	Range EXPORT03 SetRange (Range R);
	int EXPORT03 PostValidate (long);
	bool isModified (void) { return GetEditControl() -> isModified(); }
};


class _TRIAS03_ENTRY SpinControl {
protected:
	SpinEdit SpinControlEdit;
	VertMicroScroll SpinButton;

public:
// Konstruktor
	EXPORT03 SpinControl (pDialogWindow, uint, uint, Range);

// Memberfunktionen
	long EXPORT03 SetValue (long);
	long GetValue (void) { return short(SpinButton.GetCurrPos()); }

// Wert aus Spin -> Edit
	void CopyToEdit (void) { SpinControlEdit.SetValue (SpinButton.GetCurrPos()); }

// Wert aus Edit -> Spin
	void CopyToSpin (void) { SpinButton.SetCurrPos (SpinControlEdit.GetValue()); }
	Range SetRange (Range R) { 
		SpinControlEdit.SetRange (R);
		return SpinButton.SetScrollRange (R);
	}

// überprüfen, ob Edit verändert wurde
	bool isModified (void) { return SpinControlEdit.isModified(); }

// SpinButton verschwinden lassen/anzeigen
	void HideSpin (void) { SpinButton.Hide(); }
	void ShowSpin (void) { SpinButton.Show(); }

// SpinControl aktivieren/Deaktivieren
	void Disable (void) { SpinControlEdit.Disable(); SpinButton.Disable(); }
	void Enable (void) { SpinControlEdit.Enable(); SpinButton.Enable(); }
};


#endif // _SPINCTRL_HXX
