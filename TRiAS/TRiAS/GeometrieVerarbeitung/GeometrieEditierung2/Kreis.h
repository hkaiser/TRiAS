// Deklarationen: Routinen zur Kreisberechnung
// File: Kreis.h
// W. Mörtl


#ifndef _KREIS_H
#define _KREIS_H
     
     
bool KreisParameter (EPunkt& P0, EPunkt& P1, EPunkt& P2, double& r, double& xm, double& ym);
bool Vollkreis (IObjektGeometrie* pIOG, EPunkt& P0, EPunkt& P1, EPunkt& P2, pWindow pW);
bool Kreisbogen (IObjektGeometrie* pIOG, EPunkt& P0, EPunkt& P1, EPunkt& P2, pWindow pW);

#endif // _KREIS_H
