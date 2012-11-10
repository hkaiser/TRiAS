// Klassendefinition fuer SingleLineEdit ---------------------------
// File: TXTEDIT.HXX

#if !defined(_TXTEDIT_HXX)
#define _TXTEDIT_HXX

// Klasse für definierte Eingaben ---------------------------------------------
class TxtEdit : public ControlWindow {

private:
	char *m_pKey;	
	char *m_pFirstKey;
// KK010813
	bool *m_iStatus;
	bool m_iFirstStatus;

	PushButton * m_pPush;
	PushButton * m_pDelete;
	FixedText * m_pProject;

protected:
	void KeyDown (KeyEvt);

public:
// Konstruktoren
		TxtEdit (pDialogWindow p, ResID r);
		TxtEdit (pWindow parent, uint id, Point p, Dimension d);

// MemberFunktionen
	SingleLineEdit *GetEditControl (void) { 
		return (SingleLineEdit *)GetControl(); 
	};
	void GetText (char *, uint);
	void SetText (const char *);
	void SetButton ( PushButton *);
	void SetDelete ( PushButton *);
	void SetProject ( FixedText *);
	void SetKey ( char *);
	int GetTextLen (void);
	void SetTextLimit (uint);
	void SetStatus(bool *);

// Destruktor
		~TxtEdit (void);
};

#endif // _TXTEDIT_HXX

