// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 21.01.2002 14:45:22 
//
// @doc
// @module Flaeche.h | Declaration of the <c CFlaeche> class

#if !defined(_FLAECHE_H__7EBFC871_9CF5_4C57_A14F_9DA32B6EE30F__INCLUDED_)
#define _FLAECHE_H__7EBFC871_9CF5_4C57_A14F_9DA32B6EE30F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

namespace trias_wmgeometry {

///////////////////////////////////////////////////////////////////////////////
// Fläche 
template <typename KoOrdT>
class WMFlaeche : 
	public WMObjekt<KoOrdT>
{
private:
	WMFlaeche* FlaechenVereinigung1 (WMFlaeche* pFl);
	void AddInseln1 (WMFlaeche* pFl1, WMFlaeche* pFl2);
	void AddInseln2 (WMFlaeche* pFl1, WMFlaeche* pFl2);
	void AddInseln3 (WMFlaeche* pFl, int i);
	void AddInseln4 (WMFlaeche* pFl, int i);
	void AddInseln5 (WMFlaeche* pFl);

	WMPosit BeideAussenkonturenIdentisch (WMFlaeche* pFl, int iKAnz) const;
	WMPosit EnthaltenInWeiter (WMFlaeche* pFl, int* piInsel) const;

// Memberfunktionen von GeoFlaeche
	bool ClippingMitKante (WMKante<KoOrdT>* pSKt, WMClipListe<KoOrdT>& CL, 
		int iSkip, bool& bAbbr, void* pPSt);
	bool ClippingMitFlaeche (WMFlaeche* pSFl, unsigned long ulLageAusw, 
		WMClipListe<KoOrdT>& CL, int iSkip,
		WMPosit& Lage, bool& bAbbr, void* pPSt);
	bool MesserInnerhalb (WMFlaeche* pSFl, unsigned long ulLageAusw, 
		WMClipListe<KoOrdT>& CL, int iSkip, bool bOverlap, int iTouchOut, 
			bool& bEnde);
	bool MesserinselInnerhalb (WMKante<KoOrdT>* pKont, int iKInd, 
		WMClipListe<KoOrdT>& CL, int iSkip);
	bool MesserAusserhalb (WMFlaeche* pSFl, unsigned long ulLageAusw, 
		WMClipListe<KoOrdT>& CL, int iSkip);
	bool MesserAusserhalbWeiter (WMFlaeche* pSFl, unsigned long ulLageAusw, 
		WMClipListe<KoOrdT>& CL, int iSkip, int* piInsel);
	void ZweiteFlaeche (WMMarkLine* pML1, WMMarkLine* pML2, long& i);
	bool InselZweiteFlaecheAUSS (WMFlaeche* pSFl, WMClipListe<KoOrdT>& CL);
	bool ZweiInselnVereinigen (WMClipListe<KoOrdT>& CL, WMFlaeche*& pNewInsel, 
		WMMarkLine* pML1, WMMarkLine* pML2);

protected:
	WMKante<KoOrdT> *_KAF;			// Kantenfolge
	int _Size;						// Anzahl der Kanten
	WMObjRechteck<KoOrdT> *_OCont;	// Container dieser Fläche

// Konstruktoren
	WMFlaeche (WMPunktVec<KoOrdT>* SPF, long Size); // nur eine Kante

// Memberfunktionen
	bool InselnBeiSchnittMitKante (WMClipListe<KoOrdT>& CL, int iSkip);
	bool InselnAmRand (WMClipListe<KoOrdT>& CL, int iSkip, int* piVbInsel, bool& bModify);

public:
// weitere Konstruktoren
	WMFlaeche();
	WMFlaeche(KoOrdT x[], KoOrdT y[], long Len);	// nur eine Kante
	WMFlaeche(WMKante<KoOrdT> *Flaeche, int);		// mehrere Kanten
	WMFlaeche(WMKante<KoOrdT> ** Kontur, int);		// mehrere Kanten
	WMFlaeche(const WMFlaeche &);					// Copy-Konstruktor
	~WMFlaeche();

// Memberfunktionen
	WMFlaeche &operator= (const WMFlaeche &);	// Zuweisung überladen

	int KantenAnz() const;		// liefert Kantenanzahl
	long ASP() const;				// Gesamtanzahl der Stützpunkte
	WMObjRechteck<KoOrdT> GetCont() const;

// Berechnung des Flächeninhalt einer Flächen unter Berücksichtigung von 
// Innenkonturen
	double AreaSize() const; 
	
// berechnet Schwerpunkt der Außenkontur (ohne Innenkonturen) und 
// (vorzeichenbehafteten) Flächeninhalt einer Fläche
	double SchwerPunkt (WMPunkt<KoOrdT> &Pt) const;         
	
	WMObjRechteck<KoOrdT> &maxCont (WMObjRechteck<KoOrdT> &) const;  // umschließendes Rechteck
	WMObjRechteck<KoOrdT> &minCont (WMObjRechteck<KoOrdT> &) const;  // k.g. Rechteck (Schnitt)
	WMKante<KoOrdT> &KA (int n = 0) const;		// WMKante n liefern

// interne Werte modifizieren
// Kante(n) hinzufügen
	void AddKante (WMFlaeche const &, int Anzahl, int Index);
	void AddKante (KoOrdT x[], KoOrdT y[], long Len, int Index);

// Innenkontur(en) einer Fläche löschen
	void SubKante (int Anzahl, int Index);

// Punkt(e) zu einer der Kanten hinzufügen
	void AddPunkt (const WMKante<KoOrdT> &K, long KAnz, long KIndex, int MIndex);

// Len > 0 Punkte werden vor Stützpunktnummer -1 <= KIndex <= Konturlänge eingefügt
	void AddPunkt (KoOrdT x[], KoOrdT y[], long Len, long KIndex, int MIndex);

// Punkt(e) in einer der Flächenkonturen löschen
	void SubPunkt (long Len, long KIndex, int MIndex);

// Außenkontur und i-te Innenkontur werden getauscht
	bool TauschKante (int i);

	void SetCont (KoOrdT Cont[]);     // Container setzen

// Test auf Geometriefehler
// Kontur einer Fläche ist offen (true), sonst false, 0 <= i < _Size ist 
// der Konturindex
	bool isOffen (int i) const;

// Umlaufsinn einer Kontur fehlerhaft (true), sonst false
	bool isWrongTurning (int i) const;

// Umlaufsinn einer Kontur umorientieren (0 <= i < _Size ist der Konturindex)
	void OrientDreh (int i);

// Umlaufsinn aller Konturen einer Fläche prüfen und ggf. richtig drehen
	bool Umlaufsinn();
	
// Test auf Überschneidung zwischen den Konturen (true), sonst false
	bool isKontInz (WMPunkt<KoOrdT>& AP1, WMPunkt<KoOrdT>& EP1, 
		WMPunkt<KoOrdT>& AP2, WMPunkt<KoOrdT>& EP2, int i, int ii, 
		long j, long jj, long& KonInzOS, 
		WMPunkt<KoOrdT>& GP1, WMPunkt<KoOrdT>& GP2, WMSchnittErg& Fo) const;

// Test, ob Innenkontur i, die die Außenkontur nicht echt schneidet, außerhalb 
// der Außenkontur liegt (true), sonst false
	bool isAussen (int i) const;

// Test, ob Innenkontur i1, die die Innenkontur i2 nicht echt schneidet, 
// innerhalb von i2 liegt (true), sonst false
	bool isInnen (int i1, int i2) const;

// Vereinigung zweier Flächen (this- und pFl-Fläche) mit (bInsel == true) bzw. 
// ohne (bInsel == false) Berücksichtigung von Innenkonturen; wenn keine 
// Vereinigung möglich, dann Rückgabe von 0
	WMFlaeche* FlaechenVereinigung (WMFlaeche* pFl, bool& bAbbr, void* pPSt, 
		bool bInsel = true);
	
// Definition der virtuellen Funktionen der Basisklasse WMObjekt
	WMObjTyp isA() const;		// liefert ObjektTyp
	WMPosit EnthaltenIn (WMFlaeche* pFS, void* pPSt = 0);

	bool InneliegenderPunkt (double& dInX, double& dInY);

	bool InselnBeiSchnittMitFlaeche (WMFlaeche* pFl, WMClipListe<KoOrdT>& CL, int iSkip);
	bool InselnInnerhalb (WMClipListe<KoOrdT>& CL, int iSkip, int* piVbInsel = 0);
	bool ContourUnion (WMMarkLine* pML1, WMMarkLine* pML2, WMFlaeche* pVFl, bool bInsel);

// Memberfunktionen von GeoFlaeche
	bool Clipping (WMObjekt<KoOrdT>* pEO, int iOT, unsigned long ulLageAusw, 
		WMClipListe<KoOrdT>& CL, int iSkip, WMPosit& Lage, bool& bAbbr, void* pPSt);
	bool AddClipObjekt (WMClipListe<KoOrdT>& CL);
	bool InselnBeiSchnittMitFlaecheAUSS (WMFlaeche* pFl, WMClipListe<KoOrdT>& CL, 
		int iSkip);
	bool KonturGemeinsamkeiten (WMFlaeche* pFl, unsigned long ulLageAusw, 
		WMClipListe<KoOrdT>& CL, bool& bAbbr, void* pPSt);
	bool InselZweiteFlaeche (WMClipListe<KoOrdT>& CL, WMKante<KoOrdT> *pKont, 
		int iKInd);
};

} // namespace trias_wmgeometry

#endif // !defined(_FLAECHE_H__7EBFC871_9CF5_4C57_A14F_9DA32B6EE30F__INCLUDED_)
