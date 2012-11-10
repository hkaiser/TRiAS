/*
File: NUMEDIT.HXX
reelisiert die Verwaltung eines SingleLineEdit, das die Eingabe
auf Ziffer beschränkt.

erarbeitet : J. Benkenstein                 Begonnen am 9. Juni 1993
*/

#ifndef _NUMEDIT_HXX
#define _NUMEDIT_HXX

class NumEdit : public ControlWindow {
private:
	short sBase;						// Zahlenbasis
protected:
    void __export KeyDown (KeyEvt KE);

public:
//  Konstruktor/Destruktor
    NumEdit (pDialogWindow pDW , ResID rID, 
    		 short sBase = 10);                 // Zahlenbasis
    ~NumEdit (void);

//  weitere Member
	//  Aktionen auf das enthaltene Control anwenden
    pchar GetText (pchar pText, short MaxLen);
    void SetText (pchar pText);
    void SetTextLimit (short Limit);
    Bool isModified (void);
};

#endif  // _NUMEDIT_HXX
