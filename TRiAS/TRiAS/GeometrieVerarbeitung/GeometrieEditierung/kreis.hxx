// Deklaration für Routinen zur Kreisberechnung
// File: KREIS.HXX
// W. Mörtl


#ifndef _KREIS_HXX
#define _KREIS_HXX
     
     
bool KreisParameter (Punkt& P0, Punkt& P1, Punkt& P2, double& r, double& xm, double& ym);
bool Vollkreis (EObjekt* pEO, Punkt& P0, Punkt& P1, Punkt& P2, pWindow pW);
bool Kreisbogen (EObjekt* pEO, Punkt& P0, Punkt& P1, Punkt& P2, pWindow pW);

#endif // _KREIS_HXX
