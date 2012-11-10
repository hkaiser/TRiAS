// Klassendefintion fuer numerisches SingleLineEdit ---------------------------
// File: NUMEDITX.HXX

#if !defined(_NUMEDITX_HXX)
#define _NUMEDITX_HXX

#if !defined(NONUMERICEDITX)

// Klasse für numerische Eingaben ---------------------------------------------
class NumEditX : public ControlWindow {
private:
	short m_iBase;

public:
	enum NumEditMode {
		NEM_Test,
		NEM_NoTest,
	};
	NumEditMode m_NEM;

protected:
	void KeyDown (KeyEvt);
	void FocusChange (FocusChangeEvt);

virtual int PostValidate (int);	// Validierung nach Abschluß
	
public:
// Konstruktoren
		NumEditX (pDialogWindow p, ResID r, short iBase = 10);
		NumEditX (pWindow parent, uint id, Point p, Dimension d, short iBase = 10);

// MemberFunktionen
	SingleLineEdit *GetEditControl (void) { 
		return (SingleLineEdit *)GetControl(); 
	}

	void GetText (char *, uint);
	void SetText (const char *);
	int GetTextLen (void);
	void SetTextLimit (uint);

	int GetValue (BOOL * = NULL);
	void SetValue (int newVal);

	BOOL isModified() { return GetEditControl() -> isModified(); }
	void SetModified (BOOL fModified = true) { GetEditControl() -> SetModified (fModified); }

	void SetStyle (ulong);

	NumEditMode SetNumEditMode (NumEditMode);

// Destruktor
		~NumEditX (void);
};
#endif // NONUMERICEDIT

#endif // _NUMEDITX_HXX



