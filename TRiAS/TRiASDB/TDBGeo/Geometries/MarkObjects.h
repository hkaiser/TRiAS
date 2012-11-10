// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 25.01.2002 21:41:04 
//
// @doc
// @module MarkObjects.h | Declaration of the <c CMarkObjects> class

#if !defined(_MARKOBJECTS_H__F1712058_457A_430B_A5DE_FD6D2B6A6856__INCLUDED_)
#define _MARKOBJECTS_H__F1712058_457A_430B_A5DE_FD6D2B6A6856__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

namespace trias_wmgeometry {

///////////////////////////////////////////////////////////////////////////////
// mögliche 1. Markierung bei markierbaren Punkten
enum WMMar1
{
	NORMAL,		// normaler Punkt
	INNERHALB,	// Punkt innerhalb eines Überlappungsbereiches
	RANDP,		// Randpunkt eines Überlappungsbereiches
	RAND_INN,	// Randpunkt eines Überlappungsbereiches mit Zuführung aus dem
				// Inneren der Bezugsfläche
	RAND_UMG,	// Randpunkt eines Überlappungsbereiches mit Zuführung aus der
				// Umgebung der Bezugsfläche
	BERUEHR,	// Punkt mit Randpunkt- bzw. Innenberührung ohne Seitenwechsel
	BERUE_INN,	// Punkt mit Randpunkt- bzw. Innenberührung ohne Seitenwechsel, wobei die
				// beteiligten Strecken aus dem Inneren der Bezugsfläche kommen
	BERUE_UMG,	// Punkt mit Randpunkt- bzw. Innenberührung ohne Seitenwechsel, wobei die
				// beteiligten Strecken aus der Umgebung der Bezugsfläche kommen
	BERUE_ER,	// erster Punkt einer offenen Kante mit Randpunkt- bzw. Innenberührung ohne
				// Seitenwechsel, wobei die beteiligten Strecken aus dem Inneren der
				// Bezugsfläche kommen und der Anfangspunkt der Kante im Inneren der
				// Bezugsfläche liegt
	BERUE_LE,	// letzter Punkt einer offenen Kante mit Randpunkt- bzw. Innenberührung ohne
				// Seitenwechsel, wobei die beteiligten Strecken aus dem Inneren der
				// Bezugsfläche kommen und der Endpunkt der Kante im Inneren der Bezugsfläche
				// liegt
	SCHNITT,	// Schnittpunkt
	GEMEINSAM	// Punkt, an dem 2 Linien eine Gemeinsamkeit haben (Schnitt, Berührung,
				// Überlappung) 
};

///////////////////////////////////////////////////////////////////////////////
// mögliche 2. Markierung bei markierbaren Punkten
enum WMMar2
{
	UNVERBR,	// "unverbrauchte" Strecke
	VERBR		// "verbrauchte" Strecke
};

///////////////////////////////////////////////////////////////////////////////
// Durchlaufrichtung bei Übernahme einer Teilkante
enum WMMoveDir
{
	MOVEDIR_UP,		// mit aufsteigenden Stützpunkt-Indizes
	MOVEDIR_DOWN	// mit absteigenden Stützpunkt-Indizes
};

///////////////////////////////////////////////////////////////////////////////
// markierter Stützpunkt MARKVERTEX
class WMMarkVertex
{
private:
	DoublePair m_dpVtx;	// Stützpunkt
	WMMar1 m_Mark1;		// 1. Markierungsmöglichkeit (NORMAL, SCHNITT, ...)
	WMMar2 m_Mark2;		// 2. Markierungsmöglichkeit (UNVERBR, VERBR)
	long m_lRInd;		// Referenzindex zu einem Stützpunkt in einem anderen MarkLine-Vektor

public:
// Konstruktoren/Destruktor
	WMMarkVertex();			// default-Konstruktor
	template <typename KoOrdT>
	WMMarkVertex (WMPunkt<KoOrdT> const &Pkt);
	WMMarkVertex (DoublePair const &DP, WMMar1 Mk1 = NORMAL, 
		WMMar2 Mk2 = UNVERBR, long lRInd = -1);
	WMMarkVertex (WMMarkVertex const& MV);	// Copy-Konstruktor
	~WMMarkVertex();

// Elementfunktion
	void SetX (double x);
	void SetY (double y);
	void ModMk1 (WMMar1 Mk1);		// 1. Markierung modifizieren
	void ModMk2 (WMMar2 Mk2);		// 2. Markierung modifizieren
	void SetRInd (long lRInd);		// Referenzindex setzen
	void IncRInd (void);			// Referenzindex inkrementieren
	DoublePair Vtx (void) const;
	double X (void) const;
	double Y (void) const;
	WMMar1 Mark1 (void) const;
	WMMar2 Mark2 (void) const;
	long GetRInd (void) const;

	WMMarkVertex &operator= (WMMarkVertex const &rhs);	// Zuweisung überladen
};

// Ermittlung des Index lEInd des MarkLine-Vektors pML, VOR dem ein zusätzlicher 
template <typename KoOrdT>
bool EinfIndex (WMPunkt<KoOrdT> const &APkt, WMPunkt<KoOrdT> const &EPkt, long l, 
	WMMarkLine* pML, DoublePair const &ZP, long& lEInd);

// Punkt DP wird in pML vor Index -1 <= lIndex <= Vektorlänge mit der Markierung 
// Mark1 eingefügt
bool AddMarkPunkt (WMMarkLine *pML, long lIndex, DoublePair const &DP, 
	WMMar1 Mark);

// Punkt DP wird in pML vor Index -1 <= lIndex <= Vektorlänge mit der Markierung 
// Mark1 eingefügt, wenn kein koordinatengleicher Punkt existiert
bool EinfMarkPunkt (WMMarkLine *pML, long &lIndex, DoublePair const &DP, 
	WMMar1 Mark, bool& bAdd);

// Modifizierung von Markierungen der pML1- und pML2-Punkte
void MarkierungModify0 (WMMarkLine *pML);
void MarkierungModify1 (WMMarkLine *pML1, WMMarkLine *pML2);
void MarkierungModify2 (WMMarkLine *pML1, WMMarkLine *pML2);
bool MarkINNERHALB (WMMarkLine* pML1, WMMarkLine *pML2, int iKInd1, long lVekL1,
	long i, bool& bKont, WMMar1 &Mark, WMMar1 &newM, bool& bMody);
bool MarkBERUEHR (WMMarkLine *pML1, WMMarkLine *pML2, long lVekL1, long i, 
	WMMar1& newM, bool& bMody);

template <typename KoOrdT>
void SpezMarkierungModify (WMKante<KoOrdT> const *pMK, WMMarkLine *pML1, WMMarkLine *pML2);

// Position eines MarkLine-Vektors pML bez. einer Fläche pFS
template <typename KoOrdT>
WMPosit KantenPosit (WMKante<KoOrdT> *pFS, WMMarkLine* pML, bool& bOverlap, int& iTouchOut);

// Test, ob pML-Kante zerlegt wird (true), sonst false
bool KanteZerlegt (WMMarkLine* pML);

// Test, ob pML-Fläche durch pSKt-EKante zerlegt wird (true), sonst false
template <typename KoOrdT>
bool FlaecheZerlegt (WMKante<KoOrdT> *pSKt, WMMarkLine* pML);

// Zerlegen von pML durch eine Kante in Teilkanten, die in CL eingetragen werden;
// return-Wert ist "true", wenn Teilkanten in CL eingetragen werden, sonst "false"
template <typename KoOrdT>
bool TeilKanten1 (WMMarkLine* pML, WMClipListe<KoOrdT> &CL);

template <typename KoOrdT>
bool TeilKanten2 (WMMarkLine* pML1, WMMarkLine* pML2, unsigned long ulLageAusw, 
	WMClipListe<KoOrdT> &CL);

// Zerlegen von pML1 durch die EKante pSKt in Teilflächen
template <typename KoOrdT>
bool TeilFlaechen1 (WMMarkLine* pML1, WMMarkLine* pML2, WMClipListe<KoOrdT> &CL);

// Zerlegen von pML1 durch die Flächenkontur pKont in Teilflächen
template <typename KoOrdT>
bool TeilFlaechen2 (WMMarkLine* pML1, WMMarkLine* pML2, unsigned long ulLageAusw, 
	WMClipListe<KoOrdT> &CL);

///////////////////////////////////////////////////////////////////////////////
// Vektor von markierten Stützpunkten MARKLINE
class WMMarkLine
{
private:
	WMMarkVertex *m_pML;	// Vektor von markierten Stützpunkten
	long m_lSize;			// Vektorlänge
	int m_iKInd;			// Index der Flächenkontur, aus der m_pML gebildet 
							// wurde (für Kante gilt m_iKInd = -1)
	bool m_bClosed;			// m_pML geschlossen (true) oder offen (false)
	bool m_bPos;			// Umlaufsinn ist mathematisch positiv (true) oder 
							// negativ (false) (für Kante unbestimmt)
public:
// Konstruktor/Destruktor
	WMMarkLine (long lLen, int iKInd, bool bClosed = true);
	~WMMarkLine();

// MemberFunktionen
	WMMarkVertex *Vektor();
	long ADP (void) const;	// Anzahl der DoublePair-Punkte
	int GetKInd (void) const;
	bool IsClosed (void) const;

	void SetX (long lInd, double x);
	void SetY (long lInd, double y);
	void ModMark1 (long lInd, WMMar1 Mark1); // 1. Markierung modifizieren
	void ModMark2 (long lInd, WMMar2 Mark2); // 2. Markierung modifizieren

	WMMarkVertex& Vt (long lInd) const;
	DoublePair DP (long lInd) const;

	template <typename KoOrdT>
	WMPunkt<KoOrdT> SP (long lInd) const;

	double x (long lInd) const;
	double y (long lInd) const;
	WMMar1 GetMk1 (long lInd) const;
	WMMar2 GetMk2 (long lInd) const;
	long GetRefInd (long lInd) const;

// weitere Funktionen
	void RefIndexSetzen (long lInd, long lRInd);
	void RefIndexInkrementieren (long lInd);
	void RefIndexModifizieren (WMMarkLine* pML2, bool bAdd1, bool bAdd2, 
		long& lRInd1, long& lRInd2);
	WMPosit Position_real (double x, double y, double dEps = dREps);
	WMPosit Position (WMMarkLine* pML, long lInd, bool bCont = true, 
		WMMoveDir MD = MOVEDIR_UP);
	bool EckeMitBeruehrung (WMMarkLine* pML, long lInd, WMMoveDir MD, 
		WMMoveDir MD2, bool bMax, bool& bWechsel);
};

} // namespace trias_wmgeometry

#endif // !defined(_MARKOBJECTS_H__F1712058_457A_430B_A5DE_FD6D2B6A6856__INCLUDED_)
