// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 21.01.2002 14:44:03 
//
// @doc
// @module Kante.h | Declaration of the <c CKante> class

#if !defined(_KANTE_H__85D7164B_066A_4E7A_815A_835EB41AACFD__INCLUDED_)
#define _KANTE_H__85D7164B_066A_4E7A_815A_835EB41AACFD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

namespace trias_wmgeometry {

///////////////////////////////////////////////////////////////////////////////
// Punktvektor  
template <typename KoOrdT>
class WMPunktVec
{
private:
	WMPunkt<KoOrdT> *m_pSPF;		// Punktvektor
	long m_lLen;					// Vektorlänge

public:
// Konstruktor/Destruktor
	WMPunktVec(long lLen);
	~WMPunktVec();

// Funktionen
	// Überladung des Index-Operators
	WMPunkt<KoOrdT> &operator[] (long lInd);
	WMPunkt<KoOrdT> const &operator[] (long lInd) const;

// Vektorlänge liefern
	long VekL() const;

// Pointer auf Punktfeld liefern
	WMPunkt<KoOrdT> *Vektor();
	WMPunkt<KoOrdT> const *Vektor() const;
};

///////////////////////////////////////////////////////////////////////////////
// WMKante 
template <typename KoOrdT>
class WMKante : 
	public WMObjekt<KoOrdT> 
{
private:
	void AddKantenStueck1 (WMPunktVec<KoOrdT> * pPt, long lAnfId, long lEndId, 
		WMMoveDir MD);

	bool OverlapTest (WMKante const* pKt, long jj, DoublePair GP) const;
	bool Seitenwechsel (WMKante const* pKt, long j, long jj, DoublePair GP, 
		WMSchnittErg &Fo) const;

	void AddKantenStueck2 (WMMarkLine* pML, long lAnfId, long lEndId, WMMoveDir MD);
	bool Aufbereitung (WMKante const* pSKt, WMMarkLine *pML1, WMMarkLine *pML2, 
		bool& bSonst, bool& bSchnitt, bool& bLeer, bool& bAbbr, void* pPSt);

// Memberfunktionen von GeoKante
	bool ClippingMitKante (WMKante const* pSKt, WMClipListe& CL, int iSkip, 
		bool& bAbbr, void* pPSt);
	bool ClippingMitFlaeche (WMFlaeche<KoOrdT> const* pSFl, unsigned long ulLageAusw, 
		WMClipListe& CL, int iSkip, WMPosit& Lage, bool& bAbbr, void* pPSt);

// Inseln bei Schnitt der this-WMKante mit pSFl-Schnittfläche berücksichtigen
// (ulLageAusw == LINN)
	bool MesserInselnINN0 (WMFlaeche<KoOrdT>* pSFl, WMClipListe& CL);
	bool MesserInselnINN1 (WMFlaeche<KoOrdT>* pSFl, WMClipListe& CL, int iSkip);
	bool MesserInselnINN (WMFlaeche<KoOrdT>* pSFl, WMClipListe& CLZw, bool& bDelThis);

// Inseln bei Schnitt der this-WMKante mit pSFl-Schnittfläche berücksichtigen
// (ulLageAusw == LAUSS) 
	bool MesserInselnAUSS (WMFlaeche<KoOrdT>* pSFl, WMClipListe& CL);

// Inseln bei Schnitt der this-WMKante mit pSFl-Schnittfläche berücksichtigen
// (ulLageAusw == LKONT) 
	bool MesserInselnKONT (WMFlaeche<KoOrdT>* pSFl, WMClipListe& CL);

protected:
	WMPunktVec<KoOrdT> *_SPF;		// Stützpunktfolge
	WMObjRechteck<KoOrdT> *_OCont;	// Container dieser Kante

// Konstruktoren
	WMKante (long Size, WMPunktVec<KoOrdT>* SPF);

public:
	WMKante();
	WMKante(KoOrdT x[], KoOrdT y[], long lSize);
	WMKante(KoOrdT *Points, long lSize);		// (X, Y, Z) Tripel
	WMKante(WMPunktVec<KoOrdT> Linie[], long lSize);
	WMKante(WMKante const &rhs);
	~WMKante();

// Memberfunktionen
	WMKante &operator= (const WMKante &);	// Zuweisung überladen

// interne Variablenwerte liefern
	WMPunktVec<KoOrdT> const *Vektor() const;	// Pointer auf Punktfeld liefern
	long ASP() const;					// Anzahl der Stützpunkte

	WMObjRechteck<KoOrdT> GetCont() const;
	WMObjRechteck<KoOrdT> &maxCont (WMObjRechteck<KoOrdT> &) const;		// umschließender Cont
	WMObjRechteck<KoOrdT> &minCont (WMObjRechteck<KoOrdT> &) const;		// k.g.Container
	WMPunkt<KoOrdT> &SPV (long n = 0);				// Stützpunkt n liefern		16.01.98
	WMPunkt<KoOrdT> const &SP (long n = 0) const;

	void GetKante (KoOrdT x[], KoOrdT y[], long &) const;	// Geometrie

// interne Werte modifizieren
// Punkt(e) hinzufügen
	void AddPunkt (const WMKante &K, long Anzahl, long Index);

// Len > 0 Punkte werden vor Stützpunktnummer -1 <= Index <= _Size eingefügt
	void AddPunkt (KoOrdT x[], KoOrdT y[], long Len, long Index);
	HRESULT AddPunkt (KoOrdT x[], KoOrdT y[], long lCnt, long lAnfId, 
		long lEndId, long lIndex);

// Len > 0 Punkte werden vor Stützpunktnummer -1 <= Index <= _Size eingefügt
	void AddPunkt (WMPunktVec<KoOrdT> * pPV, long Len, long Index);

// Die Punkte vom Anfangsindex lAnfId bis einschließlich zum Endindex lEndId der
// Kontur pML werden vor Stützpunktnummer -1 <= lIndex <= _Size eingefügt
	void AddKonturTeil (WMMarkLine* pML, long lAnfId, long lEndId, long lIndex);

// Punkt(e) löschen
// Len > 0 Punkte werden ab Stützpunktnummer 0 <= Index < _Size gelöscht
	void SubPunkt (long Len, long Index);

	void SetCont (KoOrdT Cont[]);          // OCont setzen

// Test auf Geometriefehler
// Doppelpunkt liegt vor (true), wenn der Abstand zum nachfolgenden Punkt höchstens
// dEps (in Meter) beträgt
	bool isDoppel (bool& bNull, double dEps, DoublePair dpUF, bool bMetric, 
		long i, long j = -1);

// 2 hintereinanderliegende Strecken einer Kante bzw. Flächenkontur bilden eine Spitze
	bool isSpitz (bool& bNull, double dSpEps, long i, long j = -1, long k = -1);

// Kollinearität zwischen 3 aufeinanderfolgenden Punkten (true), sonst false
	bool isKoll (long i, long j = -1, long k = -1);

// Selbstüberschneidung liegt vor (true), sonst false
	bool isSelbInz (WMStrecke<KoOrdT>& S1, WMPunkt<KoOrdT>& AP, WMPunkt<KoOrdT>& EP, 
		long j, long jj, WMPunkt<KoOrdT>& GP1, WMPunkt<KoOrdT>& GP2, WMSchnittErg& Fo);

// Umlaufsinn einer geschlossenen Kante ermitteln
	bool GetTurning (void);

// Richtung einer Kante umorientieren
	void OrientDreh (void);

// Punkt einer Stützpunktfolge mit der kleinsten x-Koordinate unter allen 
// Punkten mit der kleinsten y-Koordinate bestimmen
	long IndTiefsterPunkt (void);

// Umordnen der Stützpunktfolge einer geschlossenen Kante bzw. Flächenkontur
	bool Umordnen (void);

// berechnet den vorzeichenbehafteten Inhalt einer geschlossenen Kante
	double PolygonArea();

// Aufbereitung einer Kante, die (evtl.) von einer WMKante pSKt geschnitten wird
	bool Aufbereitung0 (WMKante* pSKt, WMMarkLine* pML, bool& bAbbr, void* pPSt);
	
// Aufbereitung einer Flächenkontur, die (evtl.) von einer WMKante pSKt 
// geschnitten wird
	bool Aufbereitung1 (WMKante* pSKt, WMMarkLine* pML1, WMMarkLine* pML2, 
		bool& bAbbr, void* pPSt);

// Aufbereitung einer Kante bzw. Flächenkontur, die (evtl.) von einer Fläche 
// (geschlossenen WMKante) pFS geschnitten werden
	bool Aufbereitung2 (WMKante* pFS, WMMarkLine* pML1, WMMarkLine* pML2, 
		bool& bLeer, bool& bAbbr, void* pPSt);

// Kante mit weiteren Punkten aus einem offenen MarkVertex-Vektor pML2 ergänzen
	void SpezAddPunkt1 (WMMarkLine* pML1, WMMarkLine* pML2, long& i, WMMar1 mark);

// Kante mit weiteren Punkten aus einem geschlossenen MarkVertex-Vektor pML2 
// ergänzen
	void SpezAddPunkt2 (WMMarkLine* pML1, WMMarkLine* pML2, long& i, WMMoveDir MD,
						unsigned long ulLageAusw);

// Lage der this- und der pKt-Kontur zueinander
	WMPosit LageKonturZuKontur (WMKante* pKt, WMMarkLine *pML1, WMMarkLine *pML2, 
		bool& bOverlap, int& iTouchOut);

// Punkte der this-Kante, die mit einem pKt-Punkt eps-gleich sind, auf diesen 
// pKt-Punkt setzen
	void DblPointTestBetween2Lines (WMKante const* pKt);
	
// Enthaltensein eines real-Punktes in der Fläche
	WMPosit Position_real (double x, double y) const;

// Punkt (dInX, dInY) zurückgeben, der garantiert innerhalb der geschlossenen 
// this-WMKante liegt
	bool InneliegenderPunkt (double& dInX, double& dInY);

// Lage der this-WMKante und der pKt-WMKante zueinander
	WMPosit KantenLage (WMKante* pKt);
	OGCWMPosit LinesLocation (WMKante* pKt);
	
// Definition der virtuellen Funktionen der Basisklasse WMObjekt
	WMObjTyp isA() const;		// liefert ObjektTyp
	WMPosit EnthaltenIn (WMFlaeche<KoOrdT>* pFS, void* pPSt = 0);

// Verbindung zweier Kanten
	bool LinienVereinigung (WMKante* pKt, unsigned long ulFill = 0);
	bool LinienVereinigung2 (WMKante* pKt, unsigned long ulFillX = 0, 
		unsigned long ulFillY = 0);

// Test auf Überschneidung der Strecken zweier Kanten
	WMSchnittErg KantenSchnitt (WMKante const* pKt, long j, long jj, DoublePair& GP1, 
		DoublePair& GP2) const;

// this-Kontur wird durch pKont-Kontur geschnitten und dabei evtl. neue Flächen 
// erzeugt
	bool SchnittKonturMitKontur (WMKante* pKont, int iKI1, int iKI2, 
		unsigned long ulLageAusw, WMClipListe& CL);

	bool GeometricalSameLines (WMKante* pKt);

// Memberfunktionen von GeoKante
	bool Clipping (WMObjekt<KoOrdT>* pEO, int iOT, unsigned long ulLageAusw, 
		WMClipListe& CL, int iSkip, WMPosit& Lage, bool& bAbbr, void* pPSt);
	bool AddClipObjekt (WMClipListe& CL);
};

} // namespace trias_wmgeometry

#endif // !defined(_KANTE_H__85D7164B_066A_4E7A_815A_835EB41AACFD__INCLUDED_)
