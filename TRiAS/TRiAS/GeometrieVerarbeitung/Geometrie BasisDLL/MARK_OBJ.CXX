// Funktionen für markierten Stützpunkt (MarkVertex) und markierte Linie (MarkLine)
// File: MARK_OBJ.CXX
// W. Mörtl

#include "GeometrP.hxx"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif




class MarkLine;


// ============================================================================================
// Methoden für markierten Stützpunkt MARKVERTEX
// friend-Funktionen
// Ermittlung des Index lEInd des MarkLine-Vektors pML, VOR dem ein zusätzlicher Punkt ZP (der
// durch Schnitt, Überlappung bzw. Berührung zweier Kanten entstanden ist) einzufügen ist.
// APkt ist dabei der l-te, EPkt der (l+1)-te Stützpunkt der Kante, aus der pML gebildet wurde.
bool EinfIndex (EPunkt& APkt, EPunkt& EPkt, long l, MarkLine* pML, DoublePair ZP, long& lEInd)
{
	_ASSERTE (pML != 0);
	_ASSERTE (l >= 0);

	if (!pML || l < 0)
		return false;
		
long lVekL = pML->ADP();

// Die Ermittlung des gesuchten Index erfolgt i.a. in 2 Stufen, da zwischen 2 Stützpunkten der
// Originalkante bei Schnitt, Überlappung bzw. Berührung mit einer weiteren Kante mehrere
// zusätzliche Punkte liegen können. Deshalb zuerst Index ka mit pML->SP(ka) == APkt und Index
// ke mit pML->SP(ke) == EPkt suchen.
long ka = l - 1;
double xa = APkt.X();
double ya = APkt.Y();

	do
		ka++;          
	while ((pML->x(ka) != xa || pML->y(ka) != ya) && ka < lVekL);

long ke = ka;
double xe = EPkt.X();
double ye = EPkt.Y();

	do
		ke++;          
	while ((pML->x(ke) != xe || pML->y(ke) != ye) && ke < lVekL);

	if (ke == ka + 1)
	{
		lEInd = ke;
		return true;
	}

// Danach wird getestet, in welchem Teilabschnitt pML->Vt(k'),pML->Vt(k'+1) der
// Original-Strecke SP(l),SP(l+1) == APkt,EPkt die Einfügung erfolgen muß, d.h. auf welcher
// Teilstrecke pML->Vt(k'),pML->Vt(k'+1) der Punkt ZP liegt (mit ka <= k' und k' <= ke)
double dMinAbst = DBL_MAX;
long k = ka;
long ks = k + 1;	// k'

	// Die nachfolgende Berechnung mit AbstandPktStrecke() erscheint unnötig, da doch ZP schon
	// AUF der Strecke liegen müßte. Naheliegender erscheint der Test, INNERHALB welcher
	// Strecke liegt ZP. Dem steht die Epsilon-Gleichheit entgegen.
	do
	{
	double dAbst = DBL_MAX;

		if (AbstandPktStrecke (ZP, pML->DP(k), pML->DP(k+1), dAbst) &&
			dAbst >= 0. && dAbst < dMinAbst)
		{
			dMinAbst = dAbst;
			ks = k + 1;
		}
		k++;
	}
	while ((pML->x(k) != xa || pML->y(k) != ya) &&
		   dMinAbst > 0. && k < ke);

	lEInd = ks;

	_ASSERTE (ks <= ke);

	return true;

} // EinfIndex


// --------------------------------------------------------------------------------------------
// Punkt DP wird in einen MarkLine-Vektor pML VOR Vektorindex -1 <= lIndex <= Vektorlänge mit
// der Markierung Mark1 eingefügt; wenn lIndex == -1 bzw. Vektorlänge, dann wird Punkt am Ende
// angehangen
bool _GEOMETR_ENTRY AddMarkPunkt (MarkLine*& pML, long lIndex, DoublePair DP, Mar1 Mark)
{
	_ASSERTE (pML != 0);
	_ASSERTE (lIndex >= -1);

	if (! pML) return false;

long lVekL = pML->ADP();

	_ASSERTE (lIndex <= lVekL);
	
int iKInd = pML->GetKInd();
bool bClosed = pML->IsClosed();

// neues MarkLine-Objekt anlegen
MarkLine* pNewML = new MarkLine (lVekL+1, iKInd, bClosed/*, bPos*/);

	if (!pNewML || !pNewML->Vektor())
	{
		DEX_Error (RC_AddMarkPunkt, EC_NOMEMORY);
		return false;
	}

	if (lIndex == -1)        // ans Ende anhängen
		lIndex = lVekL;

	for (long l = 0; l < lIndex; l++)		// Beginn kopieren
		pNewML->Vt(l) = pML->Vt(l);
	pNewML->Vt(l) = MarkVertex (DP, Mark);	// Einfügen
	for (l = lIndex+1; l < lVekL+1; l++)	// Rest kopieren
		pNewML->Vt(l) = pML->Vt(l-1);
	DELETE_OBJ (pML);
	pML = pNewML;

	return true;

} // AddMarkPunkt


// --------------------------------------------------------------------------------------------
// Punkt DP soll in MarkLine-Vektor pML VOR Index -1 <= lIndex <= Vektorlänge mit der
// Markierung Mark eingefügt werden; existiert schon ein koordinatengleicher Punkt, wird jedoch
// (evtl.) nur die Markierung des schon vorhandenen Punktes modifiziert mit folgender fallender
// Priorität: Überlappungspunkt (INNERHALB) > Berührungspunkt ohne Seitenwechsel (BERUEHR) >
//   Schnittpunkt (SCHNITT) > normaler Punkt (NORMAL).
// Wenn lIndex == -1 bzw. lVekL, dann wird Punkt am Ende angehangen.
// Wurde der Punkt echt eingefügt, wird bAdd = true zurückgegeben; wurde nur die Markierung
// modifiziert, wird bAdd = false zurückgegeben.
// Da die Modifizierung der Markierung entweder am lIndex-Punkt bzw. am (lIndex-1)-Punkt
// erfolgt, wird der wirkliche Index in lIndex zurückgegeben.
bool EinfMarkPunkt (MarkLine*& pML, long& lIndex, DoublePair DP, Mar1 Mark, bool& bAdd)
{
	bAdd = false;

	_ASSERTE (pML != 0);

	if (! pML)
		return false;
	
long lVekL = pML->ADP();

	_ASSERTE (lIndex >= -1);
	_ASSERTE (lIndex <= lVekL);

	if (lIndex < -1 || lIndex > lVekL) // unerlaubter Index
	{
		DEX_Error (RC_EpsEinfMarkPunkt, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EinfMarkPunkt", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}
	if (-1 == lIndex)        // ans Ende anhängen
		lIndex = lVekL;

// DP wird nur eingefügt, wenn kein koordinatengleicher Punkt existiert, anderenfalls wird
// evtl. nur die Markierung modifiziert; Koordinatengleichheit kann sowohl mit dem lIndex-ten
// als auch mit dem (lIndex-1)-ten pML-Punkt bestehen
bool b0 = (DP.X() != pML->x(lIndex) || DP.Y() != pML->y(lIndex));
bool b1 = (lIndex < lVekL && b0 &&
		   lIndex > 0 && (DP.X() != pML->x(lIndex-1) || DP.Y() != pML->y(lIndex-1)));
bool b2 = (lIndex == 0 && (DP.X() != pML->x(0) || DP.Y() != pML->y(0)));
bool b3 = (lIndex == lVekL && (DP.X() != pML->x(lVekL-1) || DP.Y() != pML->y(lVekL-1)));

	if (b1 || b2 || b3)
	{
	bool bRet = AddMarkPunkt (pML, lIndex, DP, Mark);

		if (bRet) bAdd = true;
		return bRet;
	}
	
	// DP nicht einfügen (Koordinatengleichheit)
	if (b0)
	{
		if (lIndex > 0) lIndex--;
		else	// lIndex == 0
		{
			if (pML->IsClosed()) lIndex = lVekL - 2;
			else _ASSERTE (false);	// es gibt keinen vorhergehenden Index
		}
	}

Mar1 ma = pML->GetMk1 (lIndex);

	// Markierung modifizieren
	if (ma == NORMAL || Mark == INNERHALB ||
	   (ma == SCHNITT && Mark == BERUEHR))
	{
		pML->ModMark1 (lIndex, Mark);

		// bei geschlossener Kante die Markierungen von Anfangs- und Endpunkt ggf. in
		// Übereinstimmung bringen
		if (pML->IsClosed())
		{
			if (0 == lIndex)		// Markierung des Anfangspunktes wurde modifiziert
			{
				pML->ModMark1 (lVekL-1, pML->GetMk1 (0));
				return true;
			}
			if (lIndex == lVekL-1)	// Markierung des Endpunktes wurde modifiziert
				pML->ModMark1 (0, pML->GetMk1 (lVekL-1));
		}
	}

	return true;

} // EinfMarkPunkt


// --------------------------------------------------------------------------------------------
// Bei den Punkten des Vektors pML, die am Rand eines Überlappungsbereiches liegen, wird die
// Markierung INNERHALB evtl. in RANDP geändert (seit 21.05.99)
void MarkierungModify0 (MarkLine*& pML)
{
	_ASSERTE (pML != 0);

	if (! pML) return;

long lVekL = pML->ADP();
long l = 0;		// Laufindex des pML-Vektors

	// offene Kante
	if (!pML->IsClosed())
	{
		if (INNERHALB == pML->GetMk1(0))	// der 1. Punkt hat keinen Vorgänger
			pML->ModMark1 (0, RANDP);

		for (l = 1; l < lVekL-1; l++)
		{
		Mar1 mv = pML->GetMk1(l-1);
		Mar1 mn = pML->GetMk1(l+1);

			if (INNERHALB == pML->GetMk1(l) &&
				((INNERHALB != mv && RANDP != mv) || INNERHALB != mn))
				pML->ModMark1 (l, RANDP);
		}

		if (INNERHALB == pML->GetMk1(lVekL-1))	// der letzte Punkt hat keinen Nachfolger
			pML->ModMark1 (lVekL-1, RANDP);

		return;
	}


	// bei geschlossenen Kanten kann ein Überlappungsbereich über den gemeinsamen
	// Anfangs/Endpunkt der Kante hinausgehen, deshalb den Anfangspunkt des
	// Überlappungsbereiches suchen
	if (INNERHALB == pML->GetMk1(0))
	{
		l = lVekL - 2;
		while (INNERHALB == pML->GetMk1(l) && l > 0)
			l--;

		if (0 == l)
			return;		// es gibt nur INNERHALB-Punkte, d.h.2 identische geschlossene Kanten

		(l < lVekL-2) ? (l++) : (l = 0);
		pML->ModMark1 (l, RANDP);
	}

long lv, ln;		// der bez. l vorhergehende bzw. nachfolgende Index
long lAnfInd = l;	// Index, bei dem der Test auf INNERHALB wirklich beginnt

	for (;;)
	{
		lv = l;
		(l < lVekL-2) ? (l++) : (l = 0);
		if (l == lAnfInd) break;
		(l < lVekL-2) ? (ln = l+1) : (ln = 0);

	Mar1 mv = pML->GetMk1(lv);
	Mar1 mn = pML->GetMk1(ln);

		if (INNERHALB == pML->GetMk1(l) &&
			((INNERHALB != mv && RANDP != mv) || INNERHALB != mn))
			pML->ModMark1 (l, RANDP);
	}

	// den Anfangs/Endpunkt der Kante noch gleichschalten
	if (RANDP == pML->GetMk1(0))
		pML->ModMark1 (lVekL-1, RANDP);
	else if (RANDP == pML->GetMk1(lVekL-1))
		pML->ModMark1 (0, RANDP);

} // MarkierungModify0


// --------------------------------------------------------------------------------------------
// Bei den Punkten der Vektoren pML1 (aus einer Flächenkontur gebildet) bzw. pML2 (aus einer
// Kante gebildet), die am Rand eines Überlappungsbereiches liegen, wird die allgemeine
// Markierung INNERHALB evtl. in RAND_INN ("Zuführung" kommt aus dem Inneren der Flächenkontur
// pML2) geändert. Für Punkte mit einer Randpunkt- bzw. Innenberührung ohne Seitenwechsel wir
// die allgemeine Markierung BERUEHR evtl. in BERUE_INN geändert. Die Modifizierung wird nicht
// vorgenommen, wenn die entsprechenden Punkte Anfangs- bzw. Endpunkt der schneidenden
// pML2-Kante sind.
void MarkierungModify1 (MarkLine*& pML1, MarkLine*& pML2)
{
	_ASSERTE (pML1 != 0);
	_ASSERTE (pML2 != 0);

	if (!pML1 || !pML2) return;

long i = 0;			// Laufindex des Vektors pML1
Mar1 Mark, newM;	// Markierungen
long lVekL1 = pML1->ADP();
long lVekL2 = pML2->ADP();
	
bool bKont = false;	// Mittelpunkt der bez. ii vorhergehenden Strecke (pML2[ii], pML2[ii-1])
					//  liegt/nicht (true/false) auf pML1

	for (long ii = 0; ii < lVekL2-1; ii++)
	{
	bool bMody = false;	// in pML2 wurde Markierung nicht/modifiziert (false/true)

		Mark = pML2->GetMk1 (ii);

		if (Mark == INNERHALB)
		{
		// Test, ob der Mittelpunkt der bez. ii nachfolgenden Strecke (pML2[ii], pML2[ii+1])
		// innerhalb von oder auf pML1 liegt
		Posit posLage = pML1->Position (pML2, ii);

			switch (posLage)
			{
				case INNERH:
					// den Fall, daß der Anfangspunkt einer Kante mit RAND_INN markiert werden
					// müßte, kann es nicht geben
					_ASSERTE (ii > 0);

					if (ii == 0) break;

					// wenn der Mittelpunkt der Strecke (pML2[ii], pML2[ii+1]) innerhalb von
					// pML1 liegt, dann muß die Strecke (pML2[ii-1], pML2[ii]) AUF pML1 liegen
					// (bKont == true), da pML2[ii] mit INNERHALB markiert ist
					_ASSERTE (bKont == true);	// 21.07.98;   siehe MarkierungModify2()

					newM = RAND_INN;	// "Zuführung" aus dem Inneren von pML1
					pML2->ModMark1 (ii, newM);
					bMody = true;
					bKont = false;
					break;

				case AUSSERH:
					// wenn der Mittelpunkt der Strecke (pML2[ii], pML2[ii+1]) außerhalb von
					// pML1 liegt, dann muß die Strecke (pML2[ii-1], pML2[ii]) AUF pML1 liegen
					// (bKont == true), da pML2[ii] mit INNERHALB markiert ist
					_ASSERTE (bKont == true);	// 21.07.98;   siehe MarkierungModify2()

					bKont = false;
					break;

				case KONTUR:
					if (! bKont &&
						ii > 0)	// hiermit wird ausgeschlossen, daß bei der Kante pML2 die
								//  Strecke vor dem Anfangspunkt untersucht wird
					{
						// Test, ob der Mittelpunkt der bez. ii vorhergehenden Strecke
						// (pML2[ii], pML2[ii-1]) innerhalb von pML1 liegt
						if (INNERH == pML1->Position (pML2, ii, true, MOVEDIR_DOWN))	// 03.03.99
						{
							newM = RAND_INN;
							pML2->ModMark1 (ii, newM);
							bMody = true;
						}
					}

					bKont = true;
					break;

				case OFFEN:
					_ASSERTE (posLage != OFFEN);
					return;
			}
		}

		if (Mark == BERUEHR)
		{
			// Test, ob der Mittelpunkt der bez. ii nachfolgenden Strecke
			// (pML2[ii], pML2[ii+1]) innerhalb von, außerhalb von oder auf pML1 liegt
			if (INNERH == pML1->Position (pML2, ii))
			{
				newM = BERUE_INN;	// "Zuführung" aus Inneren von pML1
				pML2->ModMark1 (ii, newM);
				bMody = true;
			}
		}

		// die gleiche Modifizierung der Markierungen in pML1
  		if (bMody)
  		{
			i = pML2->GetRefInd(ii);
			_ASSERTE (i >= 0);
			pML1->ModMark1 (i, newM);
		}
	} // for


	// Behandlung des letzten Stützpunktes
	Mark = pML2->GetMk1 (lVekL2-1);
	if (Mark == BERUEHR)
	{
		// Test, ob der Mittelpunkt der letzten Strecke (pML2[lVekL2-2], pML2[lVekL2-1])
		// innerhalb von pML1 liegt
		if (INNERH == pML1->Position (pML2, lVekL2-2))
		{
			pML2->ModMark1 (lVekL2-1, BERUE_INN);

			// Modifizierung der Markierungen auch in pML1
			i = pML2->GetRefInd(lVekL2-1);
			_ASSERTE (i >= 0);
			pML1->ModMark1 (i, BERUE_INN);
		}
	}

	// "Schloß" der Flächenkontur pML1 modifizieren
	Mark = pML1->GetMk1 (0);
	if (Mark == RAND_INN || Mark == RAND_UMG || Mark == BERUE_INN)
		pML1->ModMark1 (lVekL1-1, Mark);
	else
	{
		Mark = pML1->GetMk1 (lVekL1-1);
		if (Mark == RAND_INN || Mark == RAND_UMG || Mark == BERUE_INN)
			pML1->ModMark1 (0, Mark);
	}
} // MarkierungModify1


// --------------------------------------------------------------------------------------------
// Bei den Punkten der Vektoren pML1 bzw. pML2, die am Rand eines Überlappungsbereiches liegen,
// wird die allgemeine Markierung INNERHALB in RAND_INN ("Zuführung" kommt aus dem Inneren der
// Flächenkontur pML2) bzw. RAND_UMG ("Zuführung" kommt aus der Umgebung von pML2) geändert.
// Für Punkte mit einer Randpunkt- bzw. Innenberührung ohne Seitenwechsel wird die allgemeine
// Markierung BERUEHR in BERUE_INN bzw. BERUE_UMG geändert.
// OT == OT_FLAECHE bzw. OT_KANTE, wenn pML1 aus einer Flächenkontur bzw. einer echten Kante
// gebildet wurde; pML2 muß immer aus einer Flächenkontur gebildet worden sein
void MarkierungModify2 (MarkLine*& pML1, MarkLine*& pML2)
{
	_ASSERTE (pML1 != 0);
	_ASSERTE (pML2 != 0);

	if (!pML1 || !pML2) return;

long ii = 0;		// Laufindex des Vektors pML2[]
Mar1 Mark, newM;	// Markierungen
long lVekL1 = pML1->ADP();
bool bKont = false;	// Mittelpunkt der bez. i vorhergehenden Strecke (pML1[i], pML1[i-1])
					// liegt auf pML2 (true)
long lVekL2;
int iKInd1 = pML1->GetKInd();	// Konturindex von pML1 (wurde pML1 aus einer echten Kante
								//  gebildet, gilt iKInd1 == -1)

	if (iKInd1 >= 0)	// pML1 ist aus einer Flächenkontur gebildet worden
	{
		lVekL2 = pML2->ADP();

		// für den Fall, daß Überlappungsbereich von hinten bis an das "KonturSchloß" heran
		// bzw. über dieses hinaus reicht
		if (INNERHALB == pML1->GetMk1 (0) &&
			KONTUR == pML2->Position (pML1, 0, true, MOVEDIR_DOWN))		// 03.03.99
			bKont = true;
	}

	for (long i = 0; i < lVekL1-1; i++)
	{
	bool bMody = false;	// in pML1 wurde Markierung modifiziert (true)

		Mark = pML1->GetMk1 (i);

		if (INNERHALB == Mark)
			MarkINNERHALB (pML1, pML2, iKInd1, lVekL1, i, bKont, Mark, newM, bMody);

		if (BERUEHR == Mark)
			MarkBERUEHR (pML1, pML2, lVekL1, i, newM, bMody);

		// wenn pML1 eine Fläche ist, dann die gleiche Modifizierung der Markierungen in pML2
		if (bMody && iKInd1 >= 0)
  		{
			ii = pML1->GetRefInd (i);
			_ASSERTE (ii >= 0);
			pML2->ModMark1 (ii, newM);
		}
	} // for


	// Behandlung des letzten Stützpunktes
	if (iKInd1 >= 0)	// pML1 ist aus einer Flächenkontur gebildet worden
	{
		// "Schlösser" der beiden Vektoren modifizieren
		Mark = pML1->GetMk1 (0);
		if (Mark == RAND_INN || Mark == RAND_UMG || Mark == BERUE_INN || Mark == BERUE_UMG)
			pML1->ModMark1 (lVekL1-1, Mark);
		else
		{
			Mark = pML1->GetMk1 (lVekL1-1);
			if (Mark == RAND_INN || Mark == RAND_UMG || Mark == BERUE_INN || Mark == BERUE_UMG)
				pML1->ModMark1 (0, Mark);
		}
		Mark = pML2->GetMk1 (0);
		if (Mark == RAND_INN || Mark == RAND_UMG || Mark == BERUE_INN || Mark == BERUE_UMG)
			pML2->ModMark1 (lVekL2-1, Mark);
		else
		{
			Mark = pML2->GetMk1 (lVekL2-1);
			if (Mark == RAND_INN || Mark == RAND_UMG || Mark == BERUE_INN || Mark == BERUE_UMG)
				pML2->ModMark1 (0, Mark);
		}
	}
	else					// pML1 ist aus einer echten Kante gebildet worden
	{
		Mark = pML1->GetMk1 (lVekL1-1);
		if (Mark == BERUEHR)
		{
		// Test, ob der Mittelpunkt der letzten Strecke (pML1[lVekL1-2], pML1[lVekL1-1])
		// innerhalb oder außerhalb von pML2 liegt
		Posit posLage = pML2->Position (pML1, lVekL1-2);

			if (INNERH == posLage) newM = BERUE_INN;	// "Zuführung" aus Inneren
			else newM = BERUE_UMG;						//  bzw. aus Umgebung von pML2
			pML1->ModMark1 (i, newM);
		}
	}

} // MarkierungModify2


// --------------------------------------------------------------------------------------------
// Hilfsroutine für MarkierungModify2() für Mark == INNERHALB
// pML2 wird in dieser Routine NICHT modifiziert, höchstens pML1
bool MarkINNERHALB (MarkLine*& pML1, MarkLine* pML2, int iKInd1, long lVekL1, long i,
					bool& bKont, Mar1& Mark, Mar1& newM, bool& bMody)
{
// Test, ob der Mittelpunkt der bez. i nachfolgenden Strecke (pML1[i], pML1[i+1]) innerhalb
// von, außerhalb von oder auf pML2 liegt; dabei darf bei pML1->GetMk1 (i+1) != INNERHALB weder
// posLage == INNERH noch posLage == AUSSERH eintreten
bool bCont = (INNERHALB == pML1->GetMk1 (i+1));		// es gilt i < lVekL1 - 1
Posit posLage = pML2->Position (pML1, i, bCont);

	switch (posLage)
	{
		case INNERH:
		case AUSSERH:
			// den Fall, daß der Anfangspunkt einer offenen Kante mit RAND_INN bzw. RAND_UMG
			// markiert werden müßte, kann es nicht geben
			if (0 == i &&
				!pML1->IsClosed())	// 15.04.99
			{
				_ASSERTE (i > 0 || pML1->IsClosed());

				return false;
			}

			// wenn der Mittelpunkt der Strecke (pML1[i], pML1[i+1]) innerhalb oder außerhalb
			// von pML2 liegt, dann muß die Strecke (pML1[i-1], pML1[i]) AUF pML2 liegen
			// (bKont == true), da pML1[i] mit INNERHALB markiert ist
			if (bKont)
			{
				if (INNERH == posLage) newM = RAND_INN;	// "Zuführung" aus dem Inneren bzw.
				else newM = RAND_UMG;					//  der Umgebung von pML2
				pML1->ModMark1 (i, newM);
				bKont = false;
			}

			// (posLage == INNERH oder posLage == AUSSERH) und bKont == false widerspricht sich
			// mit Mark == INNERHALB, kann aber entstanden sein, wenn in einen
			// Überlappungsbereich, dessen Randpunkte schon mit INNERHALB markiert worden
			// waren, nachträglich noch ein Punkt eingefügt wurde; in diesem Fall ist
			// newM = SCHNITT oder Mark = BERUEHR zu setzen (29.07.98)
			else
			{
				// Mittelpunkte der bez. i vor- bzw. nachfolgenden Strecke liegen beide
				// entweder außerhalb oder beide innerhalb von pML2
				if (posLage == pML2->Position (pML1, i, true, MOVEDIR_DOWN))	// 03.03.99
					Mark = BERUEHR;
				// beide Mittelpunkte liegen auf verschiedenen "Seiten" von pML2
				else
				{
					newM = SCHNITT;
					pML1->ModMark1 (i, newM);
				}
			}

			bMody = true;
			break;

		case KONTUR:
			if (! bKont &&
				// mit nachfolgender Bedingung wird ausgeschlossen, daß bei einer echten Kante
				// die Strecke VOR dem Anfangspunkt untersucht wird
				(i > 0 || iKInd1 >= 0))
			{
				// Test, ob der Mittelpunkt der bez. i vorhergehenden Strecke
				// (pML1[i], pML1[i-1]) innerhalb oder außerhalb von pML2 liegt
				posLage = pML2->Position (pML1, i, false, MOVEDIR_DOWN);	// 03.03.99

				if (INNERH == posLage) newM = RAND_INN;
				else newM = RAND_UMG;
				pML1->ModMark1 (i, newM);
				bMody = true;
			}

			bKont = true;
			break;

		case OFFEN:
			_ASSERTE (posLage != OFFEN);
			return false;

	} // switch

	return true;

} // MarkINNERHALB


// --------------------------------------------------------------------------------------------
// Hilfsroutine für MarkierungModify2() für Mark == BERUEHR
// pML2 wird in dieser Routine NICHT modifiziert, höchstens pML1
bool MarkBERUEHR (MarkLine*& pML1, MarkLine* pML2, long lVekL1, long i, Mar1& newM,
				  bool& bMody)
{
// Test, ob der Mittelpunkt der bez. i nachfolgenden Strecke (pML1[i], pML1[i+1]) innerhalb
// oder außerhalb von pML2 liegt
Posit posLage = pML2->Position (pML1, i, false);

	if (INNERH == posLage) newM = BERUE_INN;	// "Zuführung" aus Inneren
	else newM = BERUE_UMG;						//  bzw. aus Umgebung von pML2
	pML1->ModMark1 (i, newM);
	bMody = true;
	return true;

} // MarkBERUEHR


// --------------------------------------------------------------------------------------------
// Wenn der Anfangs- bzw. Endpunkt der pML2-Kante innerhalb der Flächenkontur pKont liegt, dann
// hat der erste bzw. letzte Schnittpunkt (oder Endpunkt eines Überlappungsbereiches oder
// Berührungspunkt) für die Zerlegung von pML1-Fläche keine Bedeutung. Deren Markierung wird
// wie folgt modifiziert:
// - bei Schnittpunkt: zurücksetzen auf NORMAL
// - bei Endpunkt eines Überlappungsbereiches: zurücksetzen auf INNERHALB
// - bei Berührungspunkt: Markierung auf BERUE_ER bzw. BERUE_LE setzen
void SpezMarkierungModify (EKante* pKont, MarkLine*& pML1, MarkLine*& pML2)
{
	_ASSERTE (pKont != 0);
	_ASSERTE (pML1 != 0);
	_ASSERTE (pML2 != 0);

	if (!pKont || !pML1 || !pML2) return;

long lVekL1 = pML1->ADP();
long lVekL2 = pML2->ADP();
bool bErstIn = false;	// erster pML2-Punkt liegt innerhalb von pKont
bool bLetzIn = false;	// letzter pML2-Punkt liegt innerhalb von pKont

	if (INNERH == pKont->Position_real (pML2->x(0), pML2->y(0)))
		bErstIn = true;
	if (INNERH == pKont->Position_real (pML2->x(lVekL2-1), pML2->y(lVekL2-1)))
		bLetzIn = true;
	if (!bErstIn && !bLetzIn)
		return;		// weder erster noch letzter pML2-Punkt innerhalb von pKont

long i = 0;		// Laufindex des Vektors pML1
long ii;		// Laufindex des Vektors pML2
Mar1 ma, newM;	// Markierungen

	if (bErstIn)
	{
		for (ii = 0; ii < lVekL2; ii++)
		{
			ma = pML2->GetMk1 (ii);
			if (ma == SCHNITT || ma == RAND_INN || ma == BERUE_INN) break;
		}
		if (ii < lVekL2)	// einen der genannten Punkte gefunden
		{
			if (ma == SCHNITT)
				newM = NORMAL;
			else if (ma == RAND_INN)
				newM = INNERHALB;
			else	// ma == BERUE_INN
				newM = BERUE_ER;
			pML2->ModMark1 (ii, newM);

			// die gleiche Modifizierung der Markierungen in pML1
			i = pML2->GetRefInd(ii);
			_ASSERTE (i >= 0);
			pML1->ModMark1 (i, newM);
			if (0 == i)		// evtl. Schloß modifizieren
				pML1->ModMark1 (lVekL1-1, newM);
		}
	}
	
	if (bLetzIn)
	{
		for (ii = lVekL2-1; ii >= 0; ii--)
		{
			ma = pML2->GetMk1 (ii);
			if (ma == SCHNITT || ma == RAND_INN || ma == BERUE_INN) break;
		}
		if (ii >= 0)	// einen der genannten Punkte gefunden
		{
			if (ma == SCHNITT)
				newM = NORMAL;
			else if (ma == RAND_INN)
				newM = INNERHALB;
			else	// ma == BERUE_INN
				newM = BERUE_LE;
			pML2->ModMark1 (ii, newM);

			// die gleiche Modifizierung der Markierungen in pML1
			i = pML2->GetRefInd(ii);
			_ASSERTE (i >= 0);
			pML1->ModMark1 (i, newM);
			if (0 == i)		// evtl. Schloß modifizieren
				pML1->ModMark1 (lVekL1-1, newM);
		}
	}
} // SpezMarkierungModify


// --------------------------------------------------------------------------------------------
// Position eines Vektors pML aus markierten Stützpunkten bez. einer Flächenkontur pKont;
// pML-Vektor liegt mit folgenden return-Wert
//   INNERH   vollständig innerhalb von pKont
//   INNERHB  innerhalb von pKont mit Berührung von pKont
//   AUSSERH  vollständig außerhalb von pKont
//   AUSSERHB außerhalb von pKont mit Berührung von pKont
//   INNAUSS  teilweise innerhalb, teilweise außerhalb von pKont
//   KONTUR   vollständig auf pKont
//   UMSCHL   vollständig außerhalb von pKont, wobei pKont völlig umschlossen wird
//            (nur für geschlossenen pML-Vektor möglich)
//   UMSCHLB  außerhalb von pKont mit Berührung von pKont, wobei pKont völlig umschlossen wird
//            (nur für geschlossenen pML-Vektor möglich)
//   UNKLAR   falscher Parameter
// In bOverlap wird angezeigt, ob ein Überlappungsbereich vorliegt (true) oder nicht (false),
// in iTouchOut wird noch die Anzahl der Berührungspunkte mit "Zuführung" aus der Umgebung von
// pKont zurückgegeben.
Posit KantenPosit (EKante* pKont, MarkLine* pML, bool& bOverlap, int& iTouchOut)
{
	_ASSERTE (pKont != 0);
	_ASSERTE (pML != 0);

	if (!pKont || !pML) return UNKLAR;
	
long lVekL = pML->ADP();
bool bSchnittPt = false;// (noch) keine Schnittpunkte gefunden
bool bRichtInn = false;	// (noch) keine Endpunkte von Überlappungsbereichen mit
						// Richtungsmarkierung RAND_INN gefunden
bool bRichtUmg = false;	// (noch) keine Endpunkte von Überlappungsbereichen mit
						// Richtungsmarkierung RAND_UMG gefunden
bool bRand = false;		// (noch) keine Punkte aus dem Inneren eines Überlappungsbereiches
						// gefunden
int iBerInn = 0;		// Anzahl der Berührungspunkte mit Richtungsmarkierung BERUE_INN
bool bGeschl = pML->IsClosed();	// Kante geschlossen (true) oder offen (false)
Mar1 Mar;				// Markierung des akt. Punktes
long lLastIndex = lVekL;	// letzter Index für nachfolgende for-Schleife

	if (bGeschl) lLastIndex = lVekL - 1;	// bei geschlossener Kontur ist der letzte
											//  Stützpunkt nicht mehr zu prüfen

	iTouchOut = 0;	// Anzahl der Berührungspunkte mit Richtungsmarkierung BERUE_UMG

	for (long i = 0; i < lLastIndex; i++)
	{
		Mar = pML->GetMk1 (i);	// Markierung des akt. Punktes

		if (Mar == INNERHALB)		// innerer Punkt einer Überlappung
		{
			bRand = true; continue;
		}
		if (Mar == RAND_INN)		// Endpunkt einer Überlappung mit "Zuführung"
		{							// aus dem Inneren von pKont
			bRichtInn = true; continue;
		}
		if (Mar == RAND_UMG)		// Endpunkt einer Überlappung mit "Zuführung"
		{							// aus der Umgebung von pKont
			bRichtUmg = true; continue;
		}
		if (Mar == BERUE_INN)		// Berührungspunkt mit "Zuführung"
		{							// aus dem Inneren von pKont
			iBerInn++; continue;
		}
		if (Mar == BERUE_UMG)		// Berührungspunkt mit "Zuführung"
		{							// aus der Umgebung von pKont
			iTouchOut++; continue;
		}
		if (Mar == SCHNITT)			// Schnittpunkt
			bSchnittPt = true;
	}
	                        
	// Auswertung der Markierungssituation
	// pML-Vektor und pKon haben einen/keinen gemeinsamen Bereich (bOverlap == true/false)
	(bRand || bRichtInn || bRichtUmg) ? (bOverlap = true) : (bOverlap = false);

	if ((bRichtInn && bRichtUmg) || bSchnittPt)	// teilweise innerhalb, teilweise außerhalb von
		return INNAUSS;							// pKont

	if (!bRichtInn && !bRichtUmg && bRand)	// pML-Objekt liegt vollständig auf pKont
		return KONTUR;

	if (bRichtInn || iBerInn > 0)	// pML-Objekt innerhalb von pKont mit Randberührung
		return INNERHB;

	if (bRichtUmg || iTouchOut > 0)	// pML-Objekt außerhalb von pKont mit Randberührung
	{
		if (! bGeschl)				// pML-Objekt offen
			return AUSSERHB;

	// pML-Objekt geschlossen
	// Es ist zu klären, ob das pML-Objekt pKont umschließt oder "daneben" liegt. Dazu wird ein
	// Punkt (lInX, lInY) gesucht, der garantiert innerhalb von pKont liegt. Liegt (lInX, lInY)
	// dann auch innerhalb des geschlossenen pML-Objektes, so bedeutet dies, daß pKont
	// vollständig vom pML-Objekt umschlossen wird. Anderenfalls liegt pKont "neben" dem
	// pML-Objekt.
	double dInX, dInY;
	
		pKont->InneliegenderPunkt (dInX, dInY);

	Posit posLage = pML->Position_real (dInX, dInY);

		if (INNERH == posLage)
			return UMSCHLB;

		_ASSERTE (posLage != KONTUR);
		_ASSERTE (posLage != OFFEN);
		_ASSERTE (posLage != UNKLAR);

		return AUSSERHB;	// pKont außerhalb des pML-Objektes mit Berührung des pML-Randes
	}

	// Es bleibt noch der Fall (!bRichtInn && !bRichtUmg && !bRand && iBerInn == 0 &&
	// iTouchOut == 0) übrig, d.h. pML vollständig innerhalb bzw. außerhalb von pKont ohne
	// Berührung
	if (INNERH == pKont->Position_real (pML->x(0), pML->y(0)))	// Anfangspunkt und damit
		return INNERH;						//  gesamtes pML-Objekt vollständig innerhalb pKont
		
	// pML-Objekt vollständig außerhalb von pKont
	if (! bGeschl)        // pML-Objekt offen
		return AUSSERH;
		
// pML-Objekt geschlossen und vollständig außerhalb pKont
double dInX, dInY;

	pKont->InneliegenderPunkt (dInX, dInY);

Posit posLage = pML->Position_real (dInX, dInY);

	if (INNERH == posLage)	// (dInX, dInY) und damit alle pKont-Punkte
		return UMSCHL;		//  liegen innerhalb des pML-Objektes

	_ASSERTE (posLage != KONTUR);
	_ASSERTE (posLage != OFFEN);
	_ASSERTE (posLage != UNKLAR);

	return AUSSERH;		// pKont außerhalb des pML-Objektes
	
} // KantenPosit


// --------------------------------------------------------------------------------------------
// Test, ob pML-Kante durch pSKt-EKante zerlegt wird (true), sonst false;
// Eine Zerlegung erfolgt dann, wenn mindestens 1 echter Schnittpunkt oder 2 Überlappungspunkte
// vorliegen, aber nicht alles Überlappungspunkte sind
bool KanteZerlegt (MarkLine* pML)
{
	_ASSERTE (pML != 0);

	if (! pML) return false;
	
long lVekL = pML->ADP();
int iAnz = 0;				// Anzahl der Überlappungspunkte
Mar1 Mar;					// Markierung des akt. Punktes
bool bNoOverlap = false;	// mindestens 1 Punkt, der kein Überlappungspunkt ist (true)

	for (long i = 0; i < lVekL; i++)
	{
		Mar = pML->GetMk1 (i);		// Markierung des akt. Punktes

		if (SCHNITT == Mar)			// echter Schnittpunkt
			return true;
		if (BERUEHR == Mar &&		// Rand- oder Innenberührung
			(i > 0 && i < lVekL-1))	//  jedoch nicht am Anfang/Ende der Kante
			return true;
		if (INNERHALB == Mar)		// Überlappungspunkt
		{
			iAnz++;
			if (iAnz >= 2 && bNoOverlap)
				return true;
		}
		else bNoOverlap = true;
	}
	return false;
	
} // KanteZerlegt


// --------------------------------------------------------------------------------------------
// Test, ob pML-Fläche durch pSKt-EKante zerlegt wird (true), sonst false;
// Eine Zerlegung erfolgt dann, wenn die Anzahl aus
// - echten Schnittpunkten,
// - Punkten, bei den die pSKt-EKante die pML-Fläche innen berührt, und
// - Endpunkten von Überlappungsbereichen, bei denen die Zuführung aus dem Inneren der
//   pML-Fläche kommt,
// mindestens 2 beträgt.
bool FlaecheZerlegt (EKante* pSKt, MarkLine* pML)
{
	_ASSERTE (pSKt != 0);
	_ASSERTE (pML != 0);

	if (!pSKt || !pML) return false;
	
long lVekL = pML->ADP();
int iAnz = 0;	// Anzahl der Schnitt-, Berührungs- bzw. Endpunkte
Mar1 Mar;		// Markierung des akt. Punktes

	for (long i = 0; i < lVekL; i++)
	{
		Mar = pML->GetMk1 (i);	// Markierung des akt. Punktes

		if (Mar == SCHNITT ||	// echter Schnittpunkt
			Mar == BERUE_INN ||	// Punkt, bei den die pSKt-EKante die pML-Fläche innen berührt
			Mar == BERUE_ER ||	// erster Punkt, bei den die pSKt-EKante die pML-Fläche innen
								// berührt und pSKt-Anfangspunkt liegt innerhalb der pML-Fläche
			Mar == BERUE_LE ||	// letzter Punkt, bei den die pSKt-EKante die pML-Fläche innen
								// berührt und pSKt-Endpunkt liegt innerhalb der pML-Fläche
			Mar == RAND_INN)	// Endpunkt von Überlappungsbereich, bei dem die Zuführung
								// aus dem Inneren der pML-Fläche kommt
			iAnz++;
			if (iAnz >= 2)
				return true;
	}
	return false;
	
} // FlaecheZerlegt


// --------------------------------------------------------------------------------------------
// Destruktor (nur zu Testzwecken)
MarkVertex :: ~MarkVertex (void)
{
	m_lRInd = -2;
}


// --------------------------------------------------------------------------------------------
// Memberfunktionen
void MarkVertex :: operator = (/*const */MarkVertex& newMV)
{
	if (this == &newMV) return;       // Vorsicht nicht s = s !
	m_dpVtx.X() = newMV.X();
	m_dpVtx.Y() = newMV.Y();
	m_Mark1 = newMV.m_Mark1;
	m_Mark2 = newMV.m_Mark2;
	m_lRInd = newMV.m_lRInd;
}





// ============================================================================================
// Methoden für Vektor aus markierten Stützpunkten MARKLINE
// Konstruktor
_GEOMETR_ENTRY MarkLine :: MarkLine (long lLen, int iKInd, bool bClosed
									 /*, bool bPos*/)	// wird nirgends genutzt (27.07.99)
{
	m_lSize = 0;
	m_pML = 0;	// für alle Fälle
	if (lLen <= 0)
	{
		DEX_Error (RC_mark_obj, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine MarkLine::MarkLine", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	m_pML = new MarkVertex [lLen];
	if (! m_pML)
	{
		DEX_Error (RC_mark_obj, EC_NOMEMORY);
		return;
	}

	m_lSize = lLen;
	m_iKInd = iKInd;
	m_bClosed = bClosed;
} // MarkLine
	

// --------------------------------------------------------------------------------------------
// Destruktor
_GEOMETR_ENTRY MarkLine :: ~MarkLine (void)
{
	DELETE_VEC (m_pML);
	m_lSize = 0;
}


// --------------------------------------------------------------------------------------------
// Enthaltensein eines real-Punktes (x,y) in der Fläche, die durch einen geschlossenen
// MarkLine-Vektor gebildet wird; bez. der Lage AUF dem this-Vektor wird mit einer
// dEps-Genauigkeit gearbeitet; return-Wert ist
//   INNERH   Punkt liegt innerhalb der Fläche
//   KONTUR   Punkt liegt mit dEps-Genauigkeit AUF Flächenrand
//   AUSSERH  Punkt liegt außerhalb der Fläche
//   OFFEN    Flächenrand nicht geschlossen
//   UNKLAR   irgend etwas stimmt hier nicht
// Der real-Punkt (x,y) ist der Anfangspunkt einer waagrechten Testlinie, deren Endpunkt
// "unendlich" weit rechts liegt.
Posit MarkLine :: Position_real (double x, double y, double dEps)
{
	_ASSERTE (m_lSize >= 2);

	if (! m_bClosed)    // this-Vektor nicht geschlossen
		return OFFEN;

long AnzSchn = 0;	// Zähler für echte Schnitte der Testlinie mit this-Vektor
long j = m_lSize-2;	// Index des letzten Konturpunktes, von dem bekannt ist, daß er nicht auf
					// der Testlinie liegt

	while (TurnDirection (x, y, LONG_MAX, y, m_pML[j].X(), m_pML[j].Y()) == 0)
	{
		j--;
		if (j < 0)
			return OFFEN;	// entartete Fläche, d.h. alle Punkte liegen auf einer Geraden,
							// die mit der Trägergeraden der TLinie identsch ist
	}

int r1, r2, r3, r4;	// Hilfswerte für Bewegungsrichtung
double dAbst;		// absoluter Abstand von Punkt Pkt zur Strecke Str

	for (long i = 0; i < m_lSize-1; i++)
	{
		// Test, ob Punkt (x,y) mit dEps-Genauigkeit AUF this-Vektor liegt
		AbstandPktStrecke (DoublePair(x,y), m_pML[i].Vtx(), m_pML[i+1].Vtx(), dAbst);
		if (dAbst < 0)
			return UNKLAR;
		if (dAbst <= dEps)	// beim Runden double -> KoOrd auftreten (20.10.98)
			return KONTUR;	// Punkt (x,y) liegt mit dEps-Genauigkeit AUF this-Vektor

		// Im if-Zweig der nachfolgenden Anweisung wird der Fall behandelt, daß der Stützpunkt
		// m_pML[i] nicht auf der waagrechten Testlinie liegt.
		// Liegt m_pML[i] auf der Testlinie (else-Zweig), wird m_pML[i] i.a. ignoriert.
		// Liegt jedoch der zu testende Punkt (x,y) im Dreieck m_pML[i-1],m_pML[i],m_pML[i+1],
		// ergibt sich durch das Weglassen von m_pML[i] eine Fehlinterpretation. Deshalb ist
		// dieser Fall gesondert abzutesten.
		if (TurnDirection (x, y, LONG_MAX, y, m_pML[i].X(), m_pML[i].Y()) != 0)
		{
			r1 = TurnDirection (m_pML[i].X(), m_pML[i].Y(), m_pML[j].X(), m_pML[j].Y(),
								  x, y);
			r2 = TurnDirection (m_pML[i].X(), m_pML[i].Y(), m_pML[j].X(), m_pML[j].Y(),
								  LONG_MAX, y);
			r3 = TurnDirection (x, y, LONG_MAX, y, m_pML[i].X(), m_pML[i].Y());
			r4 = TurnDirection (x, y, LONG_MAX, y, m_pML[j].X(), m_pML[j].Y());
			j = i;
			// Zähler inkrementieren, wenn echter Schnitt zwischen Strecke
			// (m_pML[i], m_pML[j]) und Teststrecke vorliegt
			if ((r1 * r2 <= 0) && (r3 * r4 <= 0))
				AnzSchn++;
		}
		else    // m_pML[i] liegt auf der Teststrecke
		{
		long iv = i - 1;

			if (0 == i) iv = m_lSize-2;
			
			// liegt (x,y) mit einer dEps-Genauigkeit AUF der Strecke m_pML[i-1],m_pML[i], ist
			// alles klar
			AbstandPktStrecke (DoublePair(x,y), m_pML[iv].Vtx(), m_pML[i].Vtx(), dAbst);
			if (dAbst <= dEps)	// beim Runden double -> KoOrd auftreten (20.10.98)
				return KONTUR;

			// ansonsten wird getestet, ob (x,y) IM Dreieck m_pML[i-1], m_pML[i], m_pML[i+1]
			// liegt; wenn ja, wird überprüft, ob die Ecke bei m_pML[i] konvex oder konkav ist
			r1 = TurnDirection (m_pML[iv].X(), m_pML[iv].Y(), m_pML[i].X(), m_pML[i].Y(),
								  x, y);
			r2 = TurnDirection (m_pML[i].X(), m_pML[i].Y(), m_pML[i+1].X(), m_pML[i+1].Y(),
								  x, y);
			r3 = TurnDirection (m_pML[i+1].X(), m_pML[i+1].Y(), m_pML[iv].X(), m_pML[iv].Y(),
								  x, y);
			if (r1 >= 0 && r2 >= 0 && r3 >= 0)	// konvexe Ecke der this-Fläche:
				return INNERH;					//  Punkt liegt innerhalb
			if (r1 <= 0 && r2 <= 0 && r3 <= 0)	// konkave Ecke der this-Fläche:
				return AUSSERH;					//  Punkt liegt außerhalb
			// (x,y) liegt nicht im Dreieck m_pML[i-1], m_pML[i], m_pML[i+1]
		}
	}
	if (AnzSchn & 1)	// ungerader Zähler bedeutet Enthaltensein
		return INNERH;
	return AUSSERH;

} // Position_real


// --------------------------------------------------------------------------------------------
// Referenzindex des lInd-ten this-Punktes auf lRInd setzen
void MarkLine :: RefIndexSetzen (long lInd, long lRInd)
{
	_ASSERTE (lInd >= 0);
	_ASSERTE (lInd < m_lSize);
	_ASSERTE (lRInd >= 0);

	if ((0 == lInd || lInd == m_lSize-1) &&	// Referenzindex am Anfangs/Endpunkt
		m_bClosed)							//  einer geschlossenen Kontur
	{										//  in Übereinstimmung bringen
		m_pML[0].SetRInd (lRInd);			// ein Befehl ist umsonst, aber so spare
		m_pML[m_lSize-1].SetRInd (lRInd);	//  ich mir eine Abfrage
	}
	else
		m_pML[lInd].SetRInd (lRInd);
}


// --------------------------------------------------------------------------------------------
// die Referenzindizes aller this-Punkte, die größer/gleich lInd sind, inkrementieren
void MarkLine :: RefIndexInkrementieren (long lInd)
{
	for (long i = 0; i < m_lSize; i++)
		if (m_pML[i].GetRInd() >= lInd)
			m_pML[i].IncRInd();
}


// --------------------------------------------------------------------------------------------
// Referenzindizes im this- und pML2-MarkLine modifizieren;
// bAdd1 und lRInd1 gehören zu this-MarkLine, bAdd2 und lRInd2 zu pML2-MarkLine
// (lRInd1 und lRInd2 werden referenziert, da sie verändert werden können)
void MarkLine :: RefIndexModifizieren (MarkLine* pML2, bool bAdd1, bool bAdd2, long& lRInd1,
									   long& lRInd2)
{
	_ASSERTE (pML2 != 0);

	if (bAdd2)
		RefIndexInkrementieren (lRInd2);	// muß vor RefIndexSetzen() kommen

	if (lRInd2 == pML2->ADP()-1 &&	// lRInd2 ist der letzte pML2-Index
		pML2->IsClosed())			//  einer geschlossenen Kante
		lRInd2 = 0;
	RefIndexSetzen (lRInd1, lRInd2);

	if (bAdd1)
		pML2->RefIndexInkrementieren (lRInd1);

	if (lRInd1 == m_lSize-1 &&		// lRInd1 ist der letzte pML1-Index
		IsClosed())					//  einer geschlossenen Kante
		lRInd1 = 0;
	pML2->RefIndexSetzen (lRInd2, lRInd1);

} // RefIndexModifizieren


// --------------------------------------------------------------------------------------------
// Prüfen, wo der Mittelpunkt der von lInd nachfolgenden (MD == MOVEDIR_UP) bzw. vorhergehenden
// (MD == MOVEDIR_DOWN) Strecke (pML[lInd], pML[lInd1]) bez. des this-MarkLine liegt;
// HINWEIS: in GemeinsamePunkte() wird mit den ursprünglichen Stützpunkten gearbeitet, hier
//          u. U. auch mit den eingefügten Punkten, wodurch (wegen der Rundung double -> KoOrd)
//          nicht die gleichen Bedingungen bestehen (deswegen Einführung des Parameters bCont)
// in bCont wird angegeben, ob als return-Wert KONTUR kommen dürfte (true) oder nicht (false)
Posit MarkLine :: Position (MarkLine* pML, long lInd, bool bCont, MoveDir MD)
{
	_ASSERTE (pML != 0);

	if (! pML) return UNKLAR;

long lLaeng = pML->ADP();

	_ASSERTE (lInd >= 0);
	_ASSERTE (lInd < lLaeng);

long lInd1 = lInd;	// Index des von pML->DP(lInd) benachbarten Punktes
long lCount = 0;	// Zähler für Durchläufe der do-while-Schleife

	do	// do-while-Schleife wegen evtl. durch Rundung entstandener DoppelPunkte
	{
		if (pML->GetKInd() < 0)	// Kante
		{	
			if (MOVEDIR_UP == MD)	// Arbeit mit dem auf lInd folgenden Index
			{
				if (lInd < lLaeng-1) lInd1++;	// = lInd + 1;
				else return UNKLAR;	// lInd ist schon der lezte Index der pML-Kante
			}
			else		// Arbeit mit dem zu lInd vorangehenden Index
			{
				if (lInd > 0) lInd1--;			// = lInd - 1;
				else return UNKLAR;	// lInd ist schon der erste Index der pML-Kante
			}
		}
		else	// OT == OT_FLAECHE
		{
			if (MOVEDIR_UP == MD)
//				(lInd < lLaeng-1) ? (lInd1++) : (lInd1 = 0);	// = lInd + 1;
				(lInd < lLaeng-2) ? (lInd1++) : (lInd1 = 0);	// = lInd + 1;	(03.11.98)
			else
				(lInd > 0) ? (lInd1--) : (lInd1 = lLaeng-2);	// = lInd - 1;
		}
		lCount++;
	}
	while ((pML->x(lInd) == pML->x(lInd1) &&	// Ausschluß von DoppelPunkten, die durch Rundung
			pML->y(lInd) == pML->y(lInd1)) &&	// von double -> KoOrd entstehen können
			lCount < lLaeng);

	if (lCount == lLaeng)
	{
		_ASSERTE (lCount < lLaeng);
		return UNKLAR;		// nur DoppelPunkte !?
	}

// 06.10.98
// Abwehrstrategie gegen Dreckeffekte, die durch Rundung von double -> KoOrd entstehen können
long lRI0 = pML->GetRefInd (lInd);
long lRI1 = pML->GetRefInd (lInd1);

	// lRI0 bzw. lRI1 können negativ (-1) sein, wenn es zum dem pML-Punkt keinen entsprechenden
	// this-Punkt gibt
	if (lRI0 >= 0 && lRI1 >= 0)
	{
		_ASSERTE (lRI0 != lRI1);

	long lMinInd, lMaxInd;	// der kleinere bzw. größere der beiden Indizes	lRI0 bzw. lRI1

		if (lRI0 < lRI1)
		{
			lMinInd = lRI0;
			lMaxInd = lRI1;
		}
		else
		{
			lMinInd = lRI1;
			lMaxInd = lRI0;
		}

		if (lMinInd == lMaxInd - 1 ||
			(m_bClosed && 0 == lMinInd && lMaxInd == m_lSize-2))
			return KONTUR;

	double dAbst;			// aktueller Abstand
	double dMaxAbst = -1.;	// größter Abstand der this-Punkte zwischen lMinInd und lMaxInd von
							// der Strecke	pML->SP(lInd), pML->SP(lInd1)

		for (long j = lMinInd + 1; j < lMaxInd; j++)
		{
			LotStrecke (DP(j), pML->DP(lInd), pML->DP(lInd1), dAbst);
			if (dAbst > dMaxAbst) dMaxAbst = dAbst;
		}

		if (dMaxAbst < dGlEps)	// hier NOCH nicht die Halbierung des eps-Parameters (03.03.99)
			return KONTUR;
	}

DoublePair DPT;

	DPT.X() = (pML->x(lInd) + pML->x(lInd1)) / 2.;
	DPT.Y() = (pML->y(lInd) + pML->y(lInd1)) / 2.;

	if (bCont)
		return Position_real (DPT.X(), DPT.Y(), dGlEps/2.);

// 03.03.99
// Als return-Wert MUß bei bCont == false INNERH oder AUSSERH ermittelt werden. Tritt dies wegen
// der bekannten Dreckeffekte nicht ein, wird das benutzte Epsilon ggf. so lange halbiert, bis
// eine Klärung bez. INNERH/AUSSERH fällt.
double dEps = dGlEps;

	for (;;)
	{
	Posit posLage = Position_real (DPT.X(), DPT.Y(), dEps/2.);

		if (INNERH == posLage || AUSSERH == posLage)
			return posLage;

		if (KONTUR == posLage)
			dEps /= 2.;
		else
		{
			_ASSERTE (INNERH != posLage);
			_ASSERTE (AUSSERH != posLage);
			_ASSERTE (KONTUR != posLage);
			return posLage;
		}

		if (dEps < 1E-10)
		{
			_ASSERTE (dEps >= 1E-10);
			return UNKLAR;
		}
	}

	_ASSERTE (false);	// hierhin dürfte keiner mehr kommen
	return UNKLAR;

} // Position


// --------------------------------------------------------------------------------------------
// Test, wie an dem BERUEH-Punkt (this-Vektor hat hier den Index lInd) weiterzugehen ist;
// für MD/MD2 == MOVEDIR_UP ist die Punktefolge von this/pML mit aufsteigendem Index, für
// MD/MD2 == MOVEDIR_DOWN mit absteigendem Index zu durchlaufen; dabei ist der größte/kleinste
// (bMax = true/false) Winkel bez. der Bezugsstrecke entscheidend;
// wenn vom this-Vektor zum pML-Vektor zu wechseln ist, dann bWechsel = true, sonst false
bool MarkLine :: EckeMitBeruehrung (MarkLine* pML, long lInd, MoveDir MD, MoveDir MD2,
									bool bMax, bool& bWechsel)
{
	_ASSERTE (pML != 0);

	if (! pML) return false;

long lVL = pML->ADP();	// Länge des pML-Vektors

	_ASSERTE (lInd >= 0);
	_ASSERTE (lInd < m_lSize);

	if (m_lSize < 3 || lVL < 3)
	{
		_ASSERTE (m_lSize >= 3 && lVL >= 3);
		return false;	// nicht genügend Punkte
	}

bool bGeschl1 = m_bClosed;

	if (! bGeschl1)
	{
		_ASSERTE (bGeschl1 == true);
		return false;	// this-Vektor offen
	}

bool bGeschl2 = pML->IsClosed();

	if (! bGeschl2)
	{
		_ASSERTE (bGeschl2 == true);
		return false;	// pML-Vektor offen
	}

long lIndv = lInd - 1;	// der bez. lInd vorhergehende bzw.
long lIndn = lInd + 1;	//  nachfolgende Index des this-Vektors

	if (lInd == 0) lIndv = m_lSize - 2;
	if (lInd == m_lSize-1) lIndn = 1;

// Index des pML-Punktes, der mit Punkt pML[lInd] übereinstimmt
long lInd2 = GetRefInd(lInd);

	_ASSERTE (lInd2 >= 0);

long lInd2v = lInd2 - 1;	// der bez. lInd2 vorhergehende bzw.
long lInd2n = lInd2 + 1;	//  nachfolgende Index des pML-Vektors

	if (lInd2 == 0) lInd2v = lVL - 2;
	if (lInd2 == lVL-1) lInd2n = 1;

// von den 2 Strecken mit Winkel w1 bzw. w2 ist diejenige zu suchen, die den größten
// (bMax == true) bzw. kleinsten Winkel (bMax == false) mit der Bezugsstrecke (mit Winkel w0)
// bildet; auf dieser ist nach dem BERUE-Punkt weiter zu gehen
double w0, w1, w2;	// Quasiwinkel (w0: Winkel der Bezugsstrecke)

	if (MOVEDIR_UP == MD)
	{
		w0 = QuasiWinkel (m_pML[lInd].X(), m_pML[lInd].Y(), m_pML[lIndv].X(), m_pML[lIndv].Y());
		w1 = QuasiWinkel (m_pML[lInd].X(), m_pML[lInd].Y(), m_pML[lIndn].X(), m_pML[lIndn].Y());	
	}
	else
	{
		w0 = QuasiWinkel (m_pML[lInd].X(), m_pML[lInd].Y(), m_pML[lIndn].X(), m_pML[lIndn].Y());
		w1 = QuasiWinkel (m_pML[lInd].X(), m_pML[lInd].Y(), m_pML[lIndv].X(), m_pML[lIndv].Y());
	}

	if (MOVEDIR_UP == MD2)
		w2 = QuasiWinkel (pML->x(lInd2), pML->y(lInd2), pML->x(lInd2n), pML->y(lInd2n));
	else
		w2 = QuasiWinkel (pML->x(lInd2), pML->y(lInd2), pML->x(lInd2v), pML->y(lInd2v));

	if (w0 == w1)
	{
		_ASSERTE (w0 != w1);
		return false;	// kein Berührungspunkt
	}
	if (w0 == w2)
	{
		_ASSERTE (w0 != w2);
		return false;	// kein Berührungspunkt
	}
	if (w1 == w2)
	{
		_ASSERTE (w1 != w2);
		return false;	// kein Berührungspunkt
	}

	if ((w0 < w1 && w0 < w2) ||	// w0 ist der kleinste Winkel
		(w0 > w1 && w0 > w2))	// w0 ist der größte Winkel, dann
	{
		if (bMax)
		{
			if (w1 < w2) bWechsel = true;
			else bWechsel = false;
		}
		else
		{
			if (w1 < w2) bWechsel = false;	// w0 und w1 gehören zum gleichen Objekt
			else bWechsel = true;			// w0 und w2 gehören zu dem jeweils anderen Objekt
		}
		return true;
	}

	// w0 ist der mittlere der 3 Winkel, dann
	if (bMax)
	{
		if (w1 < w2) bWechsel = false;
		else bWechsel = true;
	}
	else
	{
		if (w1 < w2) bWechsel = true;
		else bWechsel = false;
	}
	return true;

} // EckeMitBeruehrung
