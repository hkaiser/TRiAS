// Dialogfenster fuer die PunktobjektEditierung -------------------------------
// File: EDITPNT.HXX

#if !defined(_EDITPNT_HXX)
#define _EDITPNT_HXX

class IdentList;

class EditPointObjDlg : public DialogWindow {
private:
	ComboBox _IDList;
	DoubleNumEditX _X;
	DoubleNumEditX _Y;
	CoordTransX *_pCTFX;
	PushButton _HelpButton;
	
	IdentList &_IL;
	Punkt _Pkt;
	long _Ident;
	
protected:
	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void ListBoxClk (ControlEvt);

public:
		EditPointObjDlg (pWindow pW, ResourceFile *pRF, IdentList &IL,
				 long Ident, Punkt &Pkt);
		~EditPointObjDlg (void);

	Bool GetIdent (long &);		// ResultatsFunktionen
	Bool GetPunkt (Punkt &);
};

#endif // _EDITPNT_HXX
