/*
File: REALEDIT.HPP
reelisiert die Verwaltung eines SingleLineEdit, das die Eingabe
auf eine Real-Zahl beschränkt.

erarbeitet : J. Benkenstein                 Stand vom 1.9.1995
*/

#ifndef _REALEDIT_HPP
#define _REALEDIT_HPP

class RealEdit : public NumEdit {
protected:
    void __export KeyDown (KeyEvt KE);

public:
//  Konstruktor/Destruktor
    RealEdit (pDialogWindow pDW , ResID rID)
    		: NumEdit (pDW , rID) {}

    ~RealEdit (void) {}
};

#endif  // _REALEDIT_HPP
