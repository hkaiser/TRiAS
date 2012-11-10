// Klassendefintion fuer numerisches SingleLineEdit ---------------------------
// File: NUMEDIT.HXX

#if !defined(_NUMEDIT_HXX)
#define _NUMEDIT_HXX

#if !defined(NONUMERICEDIT)

// Klasse für numerische Eingaben ---------------------------------------------
class _TRIAS03_ENTRY NumEdit : public ControlWindow {
private:
	short m_iBase;

public:
	enum NumEditMode {
		NEM_Test,
		NEM_NoTest,
	};
	NumEditMode m_NEM;

protected:
	void EXPORT03 KeyDown (KeyEvt);
	void EXPORT03 FocusChange (FocusChangeEvt);

virtual int PostValidate (int);	// Validierung nach Abschluß
	
public:
// Konstruktoren
		EXPORT03 NumEdit (pDialogWindow p, ResID r, short iBase = 10);
		EXPORT03 NumEdit (pWindow parent, uint id, Point p, Dimension d, short iBase = 10);

// MemberFunktionen
	SingleLineEdit *GetEditControl (void) { 
		return (SingleLineEdit *)GetControl(); 
	}

	void EXPORT03 GetText (char *, uint);
	void EXPORT03 SetText (const char *);
	int EXPORT03 GetTextLen (void);
	void EXPORT03 SetTextLimit (uint);

	int EXPORT03 GetValue (Bool * = NULL);
	void EXPORT03 SetValue (int newVal);

	void EXPORT03 SetStyle (ulong);

	NumEditMode EXPORT03 SetNumEditMode (NumEditMode);

	bool EXPORT03 isModified (void);
	void EXPORT03 SetModified (bool fModified = true);

// Destruktor
		EXPORT03 ~NumEdit (void);
};
#endif // NONUMERICEDIT

#endif // _NUMEDIT_HXX



