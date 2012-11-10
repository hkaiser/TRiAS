/*
File: NUMEDIT.HXX
reelisiert die Verwaltung eines SingleLineEdit, die die Eingabe
auf Ziffer beschränkt.

erarbeitet : J. Benkenstein                 Begonnen am 9. Juni 1993
*/

#ifndef _NUMEDIT_HXX
#define _NUMEDIT_HXX

class NumEdit : public ControlWindow {
protected:
    void EXPORTFLT KeyDown (KeyEvt KE);

public:
//  Konstruktor/Destruktor
    NumEdit (pDialogWindow pDW , ResID rID);
    ~NumEdit (void);

//  weitere Member
	//  Aktionen auf das enthaltene Control anwenden
    void GetText (pchar pText, short MaxLen);
    void SetText (pchar pText);
    Bool isModified (void);
};

#endif  // _NUMEDIT_HXX
