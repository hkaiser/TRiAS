/*
File: REALEDIT.HXX
reelisiert die Verwaltung eines SingleLineEdit, das die Eingabe
auf eine Real-Zahl beschränkt.

erarbeitet : J. Benkenstein                 Begonnen am 9. Juni 1993
*/

#ifndef _REALEDIT_HXX
#define _REALEDIT_HXX

class RealEdit : public NumEdit {
protected:
    void __export KeyDown (KeyEvt KE);

public:
//  Konstruktor/Destruktor
    RealEdit (pDialogWindow pDW , ResID rID)
    		: NumEdit (pDW , rID) {}

    ~RealEdit (void) {}
};

#endif	// _REALEDIT_HXX
