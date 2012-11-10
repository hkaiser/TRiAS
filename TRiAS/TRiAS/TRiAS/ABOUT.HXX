// Klasse für AboutBox --------------------------------------------------------
// File: ABOUT.HXX

#if !defined(_ABOUT_HXX)
#define _ABOUT_HXX

#if !defined(NOABOUT)

#pragma warning (disable: 4355)

class AboutDialogBox : public DialogWindow {
private:
	Bitmap BM;
	Brush B;
	FixedText PersonName, PersonAddress;

protected:
	void ButtonClick (ControlEvt) { EndDlg (); }
	void Expose (ExposeEvt) {
	BitmapObject BMO (Point (40, 20), BM.GetSize(), &BM);
		Draw (&BMO);
	}

public:
	AboutDialogBox (pWindow parentW, ResID res)
			: DialogWindow (parentW, res),
			  BM (ResID (UVELOGO)),
			  PersonName (this, IDB_INFOPNAME),
			  PersonAddress (this, IDB_INFOPADDRESS) 
	{
		PersonName.SetText(ResString(IDS_PERSONALNAME, 50));
		PersonAddress.SetText(ResString(IDS_PERSONALADDRESS,50));
	}
};

#pragma warning (default: 4355)

#endif // NOABOUT

#endif // _ABOUT_HXX

