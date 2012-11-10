// DialogBox zur Einstellung des Objekttypes eines neu erfassten Objektes -----
// File: OBJTYPE.HXX


#if !defined(_OBJTYPE_HXX)
#define _OBJTYPE_HXX

class ObjTypDlg : public DialogWindow {
private:
	RadioButton PunktObjekt;
	RadioButton LinienObjekt;
	RadioButton FlaechenObjekt;
	RadioButton TextObjekt;

	PushButton OKButton;
	PushButton CancelButton;
	PushButton HelpButton;

	FixedText CommentString;

protected:
	ObjTyp _OT;

	void ButtonClick (ControlEvt);

public:
// Konstruktor
		ObjTypDlg (pWindow, char *, VisType);

	ObjTyp GetNewObjTyp (void) { return _OT; }	// liefert Ergebnis
};




#endif // _OBJTYPE_HXX

