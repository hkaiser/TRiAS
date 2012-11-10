/*
File: NAMEEDIT.HXX
reelisiert die Verwaltung eines SingleLineEdit, die die Eingabe
auf alphanumerische Zeichen und den Unterstrich "_" beschränkt.

erarbeitet : J. Benkenstein		    Begonnen am 24. Mai 1993
*/

#ifndef _NAMEEDIT_HXX
#define _NAMEEDIT_HXX

class NameEdit : public ControlWindow {
protected:
    void KeyDown (KeyEvt KE);

public:
//  Konstruktor/Destruktor
    NameEdit (pDialogWindow pDW , ResID rID);
    ~NameEdit (void);

//  weitere Member
	//  Aktionen auf das enthaltene Control anwenden
    void SetTextLimit (short Limit);
    void SetText (pchar pText);
    void GetText (pchar pText, short MaxLen);
    Bool isModified (void);
};

#endif	// _NAMEEDIT_HXX
