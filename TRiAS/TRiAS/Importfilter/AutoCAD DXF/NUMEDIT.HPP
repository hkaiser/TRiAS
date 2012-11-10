/*
File: NUMEDIT.HPP
reelisiert die Verwaltung eines SingleLineEdit, das die Eingabe
auf Ziffer beschränkt.

erarbeitet : J. Benkenstein                 Stand vom 1.9.1995
*/

#ifndef _NUMEDIT_HPP
#define _NUMEDIT_HPP

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

#endif  // _NUMEDIT_HPP
