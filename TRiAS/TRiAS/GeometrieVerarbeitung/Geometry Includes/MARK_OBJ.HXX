// Markierter Stützpunkt (MarkVertex) und markierte Linie (MarkLine)
// File: MARK_OBJ.HXX
// W. Mörtl


#ifndef _MARK_OBJ_HXX
#define _MARK_OBJ_HXX


// --------------------------------------------------------------------------------------------
#if !defined(NOMARKVERTEX)
// markierter Stützpunkt MARKVERTEX
class MarkVertex
{
// friend-Funktionen
// Ermittlung des Index lEInd des MarkLine-Vektors pML, VOR dem ein zusätzlicher Punkt ZP
// einzufügen ist
	friend bool EinfIndex (EPunkt& APkt, EPunkt& EPkt, long l, MarkLine* pML, DoublePair ZP,
						   long& lEInd);

// Punkt DP wird in pML vor Index -1 <= lIndex <= Vektorlänge mit der Markierung Mark1 eingefügt
_GEOMETR_ENTRY friend bool AddMarkPunkt (MarkLine*& pML, long lIndex, DoublePair DP,
										 Mar1 Mark);

// Punkt DP wird in pML vor Index -1 <= lIndex <= Vektorlänge mit der Markierung Mark1 eingefügt,
// wenn kein koordinatengleicher Punkt existiert
	friend bool EinfMarkPunkt (MarkLine*& pML, long& lIndex, DoublePair DP, Mar1 Mark,
							   bool& bAdd);

// Modifizierung von Markierungen der pML1- und pML2-Punkte
	friend void MarkierungModify0 (MarkLine*& pML);
	friend void MarkierungModify1 (MarkLine*& pML1, MarkLine*& pML2);
	friend void MarkierungModify2 (MarkLine*& pML1, MarkLine*& pML2);
	friend bool MarkINNERHALB (MarkLine*& pML1, MarkLine* pML2, int iKInd1, long lVekL1,
							   long i, bool& bKont, Mar1& Mark, Mar1& newM, bool& bMody);
	friend bool MarkBERUEHR (MarkLine*& pML1, MarkLine* pML2, long lVekL1, long i, Mar1& newM,
							 bool& bMody);
	friend void SpezMarkierungModify (EKante* pMK, MarkLine*& pML1, MarkLine*& pML2);

// Position eines MarkLine-Vektors pML bez. einer Fläche pFS
	friend Posit KantenPosit (EKante* pFS, MarkLine* pML, bool& bOverlap, int& iTouchOut);

// Test, ob pML-Kante zerlegt wird (true), sonst false
	friend bool KanteZerlegt (MarkLine* pML);
	
// Test, ob pML-Fläche durch pSKt-EKante zerlegt wird (true), sonst false
	friend bool FlaecheZerlegt (EKante* pSKt, MarkLine* pML);

// Zerlegen von pML in Teilkanten
	friend bool TeilKanten1 (MarkLine* pML, long lONr, ulong ulIdent, ClipListe& CL);
	friend bool TeilKanten2 (MarkLine* pML1, MarkLine* pML2, long ONr, ulong uIdent,
							 ulong ulLageAusw, ClipListe& CL);

// Zerlegen von pML1 durch die EKante pSKt in Teilflächen
	friend bool TeilFlaechen1 (MarkLine* pML1, MarkLine* pML2, long lONr, ulong ulIdent,
							   ClipListe& CL);

// Zerlegen von pML1 durch die Flächenkontur pKont in Teilflächen
	friend bool TeilFlaechen2 (MarkLine* pML1, MarkLine* pML2, long lONr, ulong ulIdent,
							   ulong ulLageAusw, ClipListe& CL);


private:
	DoublePair m_dpVtx;	// Stützpunkt
	Mar1 m_Mark1;		// 1. Markierungsmöglichkeit (NORMAL, SCHNITT, ...)
	Mar2 m_Mark2;		// 2. Markierungsmöglichkeit (UNVERBR, VERBR)
	long m_lRInd;		// Referenzindex zu einem Stützpunkt in einem anderen MarkLine-Vektor

public:
// Konstruktoren/Destruktor
		MarkVertex (void)			// default-Konstruktor
					{ m_Mark1 = NORMAL; m_Mark2 = UNVERBR; m_lRInd = -1; };
		MarkVertex (EPunkt Pkt)
					{ m_dpVtx.X() = Pkt.X(); m_dpVtx.Y() = Pkt.Y(); m_Mark1 = NORMAL;
					  m_Mark2 = UNVERBR; m_lRInd = -1; };
		MarkVertex (DoublePair DP, Mar1 Mk1 = NORMAL, Mar2 Mk2 = UNVERBR, long lRInd = -1)
					: m_dpVtx (DP), m_Mark1 (Mk1), m_Mark2 (Mk2), m_lRInd (lRInd) {};
		MarkVertex (MarkVertex& MV)	// Copy-Konstruktor
					: m_dpVtx (MV.X(), MV.Y()), m_Mark1 (MV.m_Mark1),
					  m_Mark2 (MV.m_Mark2), m_lRInd (MV.m_lRInd) {};
		~MarkVertex (void)/* {}*/;

// Elementfunktion
	void SetX (double x) { m_dpVtx.X() = x; }
	void SetY (double y) { m_dpVtx.Y() = y; }
	void ModMk1 (Mar1 Mk1) { m_Mark1 = Mk1; }		// 1. Markierung modifizieren
	void ModMk2 (Mar2 Mk2) { m_Mark2 = Mk2; }		// 2. Markierung modifizieren
	void SetRInd (long lRInd) { m_lRInd = lRInd; }	// Referenzindex setzen
	void IncRInd (void) { m_lRInd++; }				// Referenzindex inkrementieren
	DoublePair Vtx (void) const { return m_dpVtx; }
	double X (void) { return m_dpVtx.X(); }
	double Y (void) { return m_dpVtx.Y(); }
	Mar1 Mark1 (void) const { return m_Mark1; }
	Mar2 Mark2 (void) const { return m_Mark2; }
	long GetRInd (void) const { return m_lRInd; }

	void operator = (/*const */MarkVertex&);	// Zuweisung überladen
};
#endif // NOMARKVERTEX
											   
											   


//  ---------------------------------------------------------------------------------------
#if !defined(NOMARKLINE)
// Vektor von markierten Stützpunkten MARKLINE
class _GEOMETR_ENTRY MarkLine
{
private:
	MarkVertex* m_pML;	// Vektor von markierten Stützpunkten
	long m_lSize;		// Vektorlänge
	int m_iKInd;		// Index der Flächenkontur, aus der m_pML gebildet wurde
						//  (für Kante gilt m_iKInd = -1)
	bool m_bClosed;		// m_pML geschlossen (true) oder offen (false)
	bool m_bPos;		// Umlaufsinn ist mathematisch positiv (true) oder negativ (false)
						//  (für Kante unbestimmt)

public:
// Konstruktor/Destruktor
	MarkLine (long lLen, int iKInd, bool bClosed = true
			  /*, bool bPos = true*/);	// wird nirgends genutzt (27.07.99)
	~MarkLine (void);


// MemberFunktionen
	MarkVertex* Vektor (void) { return m_pML; }
	long ADP (void) const { return m_lSize; }	// Anzahl der DoublePair-Punkte
	int GetKInd (void) const { return m_iKInd; }
	bool IsClosed (void) const { return m_bClosed; }
//	bool IsPositiv (void) const { return m_bPos; }	wird nirgends genutzt (27.07.99)

	void SetX (long lInd, double x) { m_pML[lInd].SetX (x); }
	void SetY (long lInd, double y) { m_pML[lInd].SetY (y); }
	void ModMark1 (long lInd, Mar1 Mark1) { m_pML[lInd].ModMk1 (Mark1); } // 1. Markierung modifizieren
	void ModMark2 (long lInd, Mar2 Mark2) { m_pML[lInd].ModMk2 (Mark2); } // 2. Markierung modifizieren

	MarkVertex& Vt (long lInd) const { return m_pML[lInd]; }
	DoublePair DP (long lInd) const { return m_pML[lInd].Vtx(); }
	EPunkt SP (long lInd) const
		{ return EPunkt (DtoL(m_pML[lInd].X()), DtoL(m_pML[lInd].Y())); }
	double x (long lInd) const { return m_pML[lInd].X(); }
	double y (long lInd) const { return m_pML[lInd].Y(); }
	Mar1 GetMk1 (long lInd) const { return m_pML[lInd].Mark1(); }
	Mar2 GetMk2 (long lInd) const { return m_pML[lInd].Mark2(); }
	long GetRefInd (long lInd) const { return m_pML[lInd].GetRInd(); }

// weitere Funktionen
	void RefIndexSetzen (long lInd, long lRInd);
	void RefIndexInkrementieren (long lInd);
	void RefIndexModifizieren (MarkLine* pML2, bool bAdd1, bool bAdd2, long& lRInd1,
							   long& lRInd2);
	Posit Position_real (double x, double y, double dEps = dREps);
	Posit Position (MarkLine* pML, long lInd, bool bCont = true, MoveDir MD = MOVEDIR_UP);
	bool EckeMitBeruehrung (MarkLine* pML, long lInd, MoveDir MD, MoveDir MD2,
							bool bMax, bool& bWechsel);
};

#endif // NOMARKLINE

#endif // _MARK_OBJ_HXX
