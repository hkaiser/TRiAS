// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 21.01.2002 14:46:30 
//
// @doc
// @module Flaeche.inl | Declaration of the <c CFlaeche> class

#if !defined(_FLAECHE_INL__3F1018D6_D59D_4202_8F7F_B18CBC8AF418__INCLUDED_)
#define _FLAECHE_INL__3F1018D6_D59D_4202_8F7F_B18CBC8AF418__INCLUDED_

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

// Spezielle Flächenvereinigung von this- und pFl-Fläche mit Berücksichtigung 
// sämtlicher Inseln, wobei vorausgesetzt wird, daß pFl vollständig innerhalb 
// der this-Außenkontur liegt. Es werden folgende Fälle unterschieden:
// - pFl liegt innerhalb einer this-Insel und berührt diese Innenkontur 
//	 höchstens an einzelnen Punkten, dann ist keine Flächenvereinigung möglich, 
//	 es wird 0 zurückgegeben
// - this-Fläche hat keine Inseln bzw. pFl liegt außerhalb aller this-Inseln, 
//   dann wird die this-Fläche unverändert zurückgegeben
// - In allen anderen Fällen wird die this-Fläche mit folgenden Inseln 
//	 zurückgegeben:
//   . Teile der this-Inseln, die außerhalb der pFl-Außenkontur liegen
//   . Flächen, die sich beim Durchschnitt jeder this-Insel mit jeder pFl-Insel 
//	   ergeben
template <typename KoOrdT>
inline WMFlaeche<KoOrdT> * 
WMFlaeche<KoOrdT>::FlaechenVereinigung1 (WMFlaeche* pFl)
{
	if (1 == _Size)	// this-Fläche hat keine Inseln
		return this;

	_ASSERTE(pFl != 0);

// Wenn this-Fläche auch Inseln hat, dann Lage der pFl-Außenkontur bez. dieser 
// this-Inseln bestimmen
bool bLeer;		// Container der beiden in Aufbereitung2() verglichenen Objekte 
				// sind durchschnittsleer (true)
bool bAbbr;		// Parameter von Aufbereitung2(); wird hier nicht ausgewertet
bool bOverlap;	// pFl-Außenkontur hat mit einer this-Insel einen Überlappungsbereich
int iTouchOut;	// Parameter von KantenPosit(); wird hier nicht ausgewertet

	for (int i = 1; i < _Size; i++) {
	WMMarkLine ML1 (pFl->KA(0).ASP(), 0);			// 09.06.98: von ...
	WMMarkLine ML2 (_KAF[i].ASP(), i, true);

		_ASSERTE(!(!ML1.Vektor() || !ML2.Vektor()));
		if (!pFl->KA(0).Aufbereitung2 (&_KAF[i], &ML1, &ML2, bLeer, bAbbr, 0))	// 27.07.98
		{
			if (bLeer) 
				continue;		// 11.11.98
			return 0;
		}																// ... bis

	WMPosit posLage = KantenPosit (&_KAF[i], &ML1, bOverlap, iTouchOut);

		if (INNERH == posLage ||				// pFl liegt innerhalb einer this-Insel
			(INNERHB == posLage && !bOverlap))	// pFl berührt this-Insel höchstens 
												// an einzelnen Punkten
			return 0;	// deshalb keine Flächenvereinigung möglich
							
	// Außenkontur der pFl-Fläche ist mit der i-ten Insel der this-Fläche völlig 
	// identisch (09.06.98)
		else if (KONTUR == posLage || GLEICH == posLage) {
		// i-te Insel der this-Fläche löschen und dafür Inseln der pFl-Fläche 
		// hinzunehmen
			AddInseln3 (pFl, i);
			return this;
		}

	// Außenkontur der pFl-Fläche umschließt (d.h. überdeckt) die i-te Insel der
	// this-Fläche (27.07.98)
		else if (UMSCHL == posLage ||	// 27.07.98
				 UMSCHLB == posLage)
		{
		// i-te Insel der this-Fläche löschen und dafür andere Inseln hinzunehmen
			AddInseln4 (pFl, i);
			return this;
		}
		else if (AUSSERH != posLage && AUSSERHB != posLage)
			break;	// pFl ragt in ein "Inselloch" hinein
	}

	if (i == _Size)	// pFl ist bez. aller this-Inseln AUSSERH bzw. AUSSERHB
		return this;

	AddInseln5 (pFl);	// Inseln (verschnitten) hinzufügen
	return this;		// evtl. mit Inseln ergänzt
}

// Innenkonturen der Flächen pFl1 und pFl2 werden unverändert als Innenkonturen 
// der this-Fläche hinzugefügt (bei Routine FlaechenVereinigung() benötigt)
template <typename KoOrdT>
inline void 
WMFlaeche<KoOrdT>::AddInseln1 (WMFlaeche* pFl1, WMFlaeche* pFl2)
{
	_ASSERTE(pFl1 != 0);
	_ASSERTE(pFl2 != 0);

int iKAnz1 = pFl1->KantenAnz();
int iKAnz2 = pFl2->KantenAnz();

	if (iKAnz1 > 1) {
		for (int i = 1; i < iKAnz1; i++)
			AddKante (WMFlaeche<KoOrdT>(&pFl1->KA(i), 1), 1, -1);
	}
	if (iKAnz2 > 1) {
		for (int i = 1; i < iKAnz2; i++)
			AddKante (WMFlaeche<KoOrdT>(&pFl2->KA(i), 1), 1, -1);
	}
}

// Innenkonturen der Flächen pFl1 und pFl2 werden unter Berücksichtung 
// möglicher Überlappungen als Innenkonturen der this-Fläche hinzugefügt (bei 
// Routinen FlaechenVereinigung() benötigt)
template <typename KoOrdT>
inline void 
WMFlaeche<KoOrdT>::AddInseln2 (WMFlaeche* pFl1, WMFlaeche* pFl2)
{
	_ASSERTE(pFl1 != 0);
	_ASSERTE(pFl2 != 0);
	if (!pFl1 || !pFl2)
		return;

WMClipListe<KoOrdT> CL;	// Liste für die Ergebnisse der Schnittoperation
int iKAnz1 = pFl1->KantenAnz();
int iKAnz2 = pFl2->KantenAnz();

// Erzeugen von Inseln für die Vereinigungsfläche
// Teile der pFl1-Inseln, die außerhalb der pFl2-Außenkontur liegen
	if (iKAnz1 > 1) {
		for (int i = 1; i < iKAnz1; i++)
			pFl1->KA(i).SchnittKonturMitKontur (&pFl2->KA(0), i, 0, LAUSS, CL);
	}

// Teile der pFl2-Inseln, die außerhalb der pFl1-Außenkontur liegen
	if (iKAnz2 > 1) {
		for (int ii = 1; ii < iKAnz2; ii++)
			pFl2->KA(ii).SchnittKonturMitKontur (&pFl1->KA(0), ii, 0, LAUSS, CL);
	}

// Flächen, die sich beim Durchschnitt jeder pFl1-Insel mit jeder pFl2-Insel ergeben
	if (iKAnz1 > 1 && iKAnz2 > 1) {
		for (int ii = 1; ii < iKAnz2; ii++)
			for (int i = 1; i < iKAnz1; i++)
				pFl1->KA(i).SchnittKonturMitKontur (&pFl2->KA(ii), i, ii, LINN, CL);
	}

	if (CL.size() > 0) {		// es hat sich wenigstens eine Insel ergeben
	WMClipListe<KoOrdT>::iterator end = CL.end();

		for (WMClipListe<KoOrdT>::iterator ri = CL.begin(); ri != end; ++ri) {
			_ASSERTE((*ri)->isA() == OT_FLAECHE);
			AddKante (*(WMFlaeche<KoOrdT> *)(*ri), 1, -1);
		}
	}
}

// i-te Insel der this-Fläche löschen und dafür Inseln der pFl-Fläche 
// hinzunehmen (bei Routine FlaechenVereinigung1() benötigt)
template <typename KoOrdT>
inline void 
WMFlaeche<KoOrdT>::AddInseln3 (WMFlaeche* pFl, int i)
{
	_ASSERTE(pFl != 0);
	_ASSERTE(i >= 1);

	SubKante (1, i);	// alte _KAF[i]-Insel herausnehmen

int iKAnz = pFl->KantenAnz();

	if (iKAnz > 1) {
		for (int j = 1; j < iKAnz; j++)
			AddKante (WMFlaeche<KoOrdT>(&pFl->KA(j), 1), 1, -1);	// pFl-Inseln hinzunehmen	
	}
}

// i-te Insel der this-Fläche löschen und dafür neue Inseln hinzunehmen, u. z.
// - die Bereiche, die innerhalb der i-ten Insel der this-Fläche und außerhalb 
//	 der Außenkontur der pFl-Fläche liegen sowie
// - die Inseln der pFl-Fläche bzw. deren Bereiche, die innerhalb der i-ten 
//   Insel der this-Fläche liegen
// (bei Routine FlaechenVereinigung1() benötigt)
template <typename KoOrdT>
inline void 
WMFlaeche<KoOrdT>::AddInseln4 (WMFlaeche* pFl, int i)
{
	_ASSERTE(pFl != 0);
	_ASSERTE(i >= 1);

WMClipListe<KoOrdT> CL;	// Liste für die Ergebnisse der Schnittoperation

// Teile der i-ten this-Insel, die außerhalb der pFl-Außenkontur liegen
	_KAF[i].SchnittKonturMitKontur (&pFl->KA(0), i, 0, LAUSS, CL);

int iKCnt = pFl->KantenAnz();

	if (iKCnt > 1) {	// pFl-Fläche hat Inseln
		// Teile der j-ten pFl-Insel, die innerhalb der i-ten this-Insel liegen
		for (int j = 1; j < iKCnt; j++)
			pFl->KA(j).SchnittKonturMitKontur (&_KAF[i], j, i, LINN, CL);
	}

	if (CL.size() > 0) {		// es hat sich wenigstens eine Insel ergeben
	WMClipListe<KoOrdT>::iterator end = CL.end();

		for (WMClipListe<KoOrdT>::iterator ri = CL.begin(); ri != end; ++ri) {
			_ASSERTE((*ri)->isA() == OT_FLAECHE);
			AddKante (*(WMFlaeche<KoOrdT> *)(*ri), 1, -1);
		}
	}
	SubKante (1, i);	// i-te Insel der this-Fläche löschen (06.07.99)
}

// Innenkonturen der this-Fläche und von pFl werden unter Berücksichtung möglicher
// Überlappungen als Innenkonturen der this-Fläche hinzugefügt (bei Routine
// FlaechenVereinigung1() benötigt)
template <typename KoOrdT>
inline void 
WMFlaeche<KoOrdT>::AddInseln5 (WMFlaeche* pFl)
{
	_ASSERTE(pFl != 0);

WMClipListe<KoOrdT> CL;	// Liste für die Ergebnisse der Schnittoperation
int iKAnz1 = _Size;
	
// Erzeugen von Inseln für die Vereinigungsfläche
	if (iKAnz1 > 1) {
	// Teile der this-Inseln, die außerhalb der pFl-Außenkontur liegen
		for (int i = 1; i < iKAnz1; i++)
			_KAF[i].SchnittKonturMitKontur (&pFl->KA(0), i, 0, LAUSS, CL);

	// Flächen, die sich beim Durchschnitt jeder this-Insel mit jeder pFl-Insel ergeben
	int iKAnz2 = pFl->KantenAnz();

		if (iKAnz2 > 1) {
			for (int ii = 1; ii < iKAnz2; ii++)
				for (int i = 1; i < iKAnz1; i++)
					_KAF[i].SchnittKonturMitKontur (&pFl->KA(ii), i, ii, LINN, CL);
		}
	}

// die bisherigen this-Inseln löschen
	SubKante (iKAnz1-1, 1);

	if (CL.size() > 0) {		// es hat sich wenigstens eine Insel ergeben
	WMClipListe<KoOrdT>::iterator end = CL.end();

		for (WMClipListe<KoOrdT>::iterator ri = CL.begin(); ri != end; ++ri) {
			_ASSERTE((*ri)->isA() == OT_FLAECHE);
			AddKante (*(WMFlaeche<KoOrdT> *)(*ri), 1, -1);
		}
	}
}

// pKVFl mit Punkten von pML2 ergänzen
// (siehe auch Routine SpezAddPunkt() in geo_obj3.cxx)
template <typename KoOrdT>
inline void 
WMFlaeche<KoOrdT>::ZweiteFlaeche (WMMarkLine* pML1, WMMarkLine* pML2, long& i)
{
	_ASSERTE(pML1 != 0);
	_ASSERTE(pML2 != 0);

long lVekL1 = pML1->ADP();   // Länge des Vektors pML1
long lVekL2 = pML2->ADP();   //  bzw. pML2

// Index des pML2-Punktes, der mit Punkt pML1[i] übereinstimmt
long ii = pML1->GetRefInd(i);

	_ASSERTE(ii >= 0);

long lAnfId2;	// Anfangsindex für den Teil der Kontur, der aus pML2 übernommen wird
WMMar1 mark;	// Markierung

int iKInd1 = pML1->GetKInd();		_ASSERTE(iKInd1 >= 0);
int iKInd2 = pML2->GetKInd();		_ASSERTE(iKInd2 >= 0);
bool bWechsel;	// bei BERUE_UMG ist bei pML1 fortzusetzen (true); wird durch
				// EckeMitBeruehrung() gesetzt
bool bMax;		// SEHR wichtiger Parameter von EckeMitBeruehrung()

	if (0 == iKInd1 && 0 == iKInd2)
		bMax = false;
	else if (0 == iKInd1 && iKInd2 > 0)
		bMax = true;
	else if (iKInd1 > 0 && 0 == iKInd2) {
		_ASSERTE(false);	// nur zu Testzwecken, da
		bMax = false;		// diesen Fall hatte ich noch nicht
	}
	else	// if (iKInd1 > 0 && iKInd2 > 0)
		bMax = true;	// 29.10.98

	lAnfId2 = (ii < lVekL2-2) ? ii + 1 : 0;
	do {
		ii = (ii < lVekL2-2) ? ii + 1 : 0;
		mark = pML2->GetMk1(ii);
		if (BERUE_UMG == mark)
			pML2->EckeMitBeruehrung (pML1, ii, MOVEDIR_UP, MOVEDIR_UP, bMax, bWechsel);
	}
	// Abbruch bei Schnitt- oder Endpunkten mit "Zuführung" in die pML2-Umgebung
	// und/oder nicht mit Berührungspunkt
	while (mark != SCHNITT && mark != RAND_UMG
		   && !(mark == BERUE_UMG && bWechsel));

// Teil der Kontur von pML2 an pKVFl anhängen
	_KAF[0].AddKonturTeil (pML2, lAnfId2, ii, -1);

// Index des pML1-Punktes, der mit dem letzten hinzugefügten Punkt pML2[ii] 
// übereinstimmt
	i = pML2->GetRefInd(ii);
	_ASSERTE(i >= 0);
}

// Hilfsroutine für EFlaeche :: EnthaltenIn()
template <typename KoOrdT>
inline WMPosit 
WMFlaeche<KoOrdT>::BeideAussenkonturenIdentisch (WMFlaeche* pFl, int iKAnz) const
{
	_ASSERTE(pFl != 0);	// pPSt kann 0 sein
	if (1 == _Size && 1 == iKAnz)	// this- und pFl-Fläche haben keine Innenkonturen
		return GLEICH;

	if (_Size > 1 && 1 == iKAnz)
		return INNERHB;

	if (1 == _Size && iKAnz > 1)
		return INNAUSS;

// es bleibt:   iKAnz > 1 && _Size > 1
// dafür sind immer noch INNAUSS, INNERHB, KONTUR und GLEICH möglich
bool bLeer, bAbbr;	// Parameter von Aufbereitung2(); werden hier nicht ausgewertet
bool bOverlap;		// Parameter von KantenPosit(); werden
int iTouchOut;		// hier nicht ausgewertet

// piKennz ist ein 2-dimensionales Feld (Vektor von Vektoren) mit
//   1. Index: Indizes der this-Insel   } jeweils von 0 ... KantenAnz()-2;
//   2. Index: Indizes der pFl-Insel    }  deswegen überall i-1 bzw. ii-1
// die Belegung von piKennz hat folgende Bedeutung:
//   -1  noch unklar (Initialisierung)
//    0  zur i-ten bzw. ii-ten Insel gibt es eine Insel der "anderen" Fläche, die haarscharf
//       auf dieser Insel liegt (Inseln, zu der es eine deckungsgleiche Insel der "anderen"
//       Fläche gibt, werden aus der weiteren Betrachtung heraus gelassen)
//    1  die i-te Insel liegt außerhalb der ii-ten Insel
//    2  die i-te Insel umschließt die ii-te Insel
vector<vector<int> > piKennz;

	piKennz.resize (_Size-1);	// Größe des Feldes anlegen
	for (size_t i = 0; i < piKennz.size(); i++)
		piKennz[i].resize (iKAnz-1);

	for (i = 1; i < _Size; i++)	// Initialisierung
		for (int ii = 1; ii < iKAnz; ii++)
			piKennz[i-1][ii-1] = -1;

	for (i = 1; i < _Size; i++)
		for (int ii = 1; ii < iKAnz; ii++) {
			if (0 == piKennz[i-1][ii-1])
				continue;

		WMMarkLine ML1 (_KAF[i].ASP(), i, true);
		WMMarkLine ML2 (pFl->KA(ii).ASP(), ii, true);

			_ASSERTE(!(!ML1.Vektor() || !ML2.Vektor()));
			if (!_KAF[i].Aufbereitung2 (&pFl->KA(ii), &ML1, &ML2, bLeer, bAbbr, 0))
			{
				if (bLeer) {
				// Container beider Konturen sind durchschnittsleer
					piKennz[i-1][ii-1] = 1;
					continue;
				}
				else
					return UNKLAR;
			}

		WMPosit posLage = KantenPosit (&pFl->KA(ii), &ML1, bOverlap, iTouchOut);

			if (INNAUSS == posLage || INNERH == posLage || INNERHB == posLage)
				return INNAUSS;

			if (UNKLAR == posLage)
				return UNKLAR;

			if (KONTUR == posLage) {
				for (int jj = 1; jj < iKAnz; jj++)
					piKennz[i-1][jj-1] = 0;

				for (int j = 1; j < _Size; j++)
					piKennz[j-1][ii-1] = 0;
				break;	// nächste KA(i)-Insel
			}

			_ASSERTE(piKennz[i-1][ii-1] == -1);

			if (AUSSERH == posLage || AUSSERHB == posLage)
				piKennz[i-1][ii-1] = 1;
			else	// UMSCHL == posLage || UMSCHLB == posLage
				piKennz[i-1][ii-1] = 2;
		}

// nachfolgender Test kann NICHT gleich mit der vorangegangenen for-Schleife 
// abgefangen werden, da die Kennzeichnungen "1" bzw. "2" nachträglich noch 
// auf "0" gesetzt werden können, da sich erst SPÄTER herausstellen kann, 
// daß es zu einer Insel eine deckungsgleiche Insel der "anderen" Fläche gibt
bool bAusser = false;	// das Kennzeichen piKennz[][] == 1 tritt auf, d.h. 
						// mindestens einmal war posLage == AUSSERH bzw. 
						// posLage == AUSSERHB (true)
bool bUmschl = false;	// das Kennzeichen piKennz[][] == 2 tritt auf, d.h. 
						// mindestens einmal war posLage == UMSCHL bzw. 
						// posLage == UMSCHLB (true)

	for (i = 1; i < _Size; i++)
		for (int ii = 1; ii < iKAnz; ii++) {
		int iKZ = piKennz[i-1][ii-1];

			if (1 == iKZ)
				bAusser = true;
			else if (2 == iKZ)
				bUmschl = true;
		}

	if (!bAusser) {
		if (bUmschl)
			return INNERHB;

	// bAusser == false && bUmschl == false
		if (_Size == iKAnz)
			return GLEICH;

		if (_Size > iKAnz)
			return INNERHB;

		if (_Size < iKAnz)
			return INNAUSS;
	}

// bAusser == true, d.h. es bleibt immer noch INNAUSS und INNERHB
// Wenn es mindestens eine KA(ii)-Insel der pFl-Bezugsfläche gibt, für die für 
// ALLE KA(i)-Inseln piKennz[i][.] == 1 gilt, dann INNAUSS, sonst INNERHB
	for (int ii = 1; ii < iKAnz; ii++) {
	bool bAllNull = true;	// es gilt piKennz[.][ii] == 0 für alle i

		for (int i = 1; i < _Size; i++) {
		int iKZ = piKennz[i-1][ii-1];

			if (0 == iKZ) 
				continue;
			bAllNull = false;
			if (1 != iKZ) 
				break;
		}

		if (i == _Size && !bAllNull)
			return INNAUSS;
	}
	return INNERHB;
}

// 19.10.98: Hilfsroutine zu EFlaeche::EnthaltenIn() für folgenden Fall:
// this-Fläche liegt innerhalb der pFl-Außenkontur und und bez. der pFl-
// Innenkonturen gilt mindestens einmal UMSCHL bzw. UMSCHLB (diese 
// pFl-Innenkonturen sind in piInsel aufgelistet); für das Verhältnis der 
// this-Fläche bez. der pFl-Fläche gilt dann
//   INNERH,  wenn zu allen diese pFl-Innenkonturen auch this-Innenkonturen mit UMSCHL
//            existieren
//   INNERHB, wenn zu allen diese pFl-Innenkonturen auch this-Innenkonturen mit UMSCHLB bzw.
//            KONTUR existieren
//   INNAUSS  in allen übrigen Fällen
template <typename KoOrdT>
inline WMPosit 
WMFlaeche<KoOrdT>::EnthaltenInWeiter (WMFlaeche* pFl, int* piInsel) const
{
	_ASSERTE(pFl != 0);
	_ASSERTE(piInsel != 0);

	if (0 == piInsel[0] || 1 == _Size) 
		return UNKLAR;

bool bAbbr = false;		// true: Abbruch der while-Schleife
int k = 0;				// Laufindex für piInsel
bool bOverlap;			// Parameter von LageKonturZuKontur(); werden hier
int iTouchOut;			// nicht ausgewertet
bool bInnerhB = false;	// this-Fläche liegt bez. der pFl-Fläche INNERHB (true)

// Lage der pFl-Inseln, die innerhalb der this-Außenkontur liegen, zu den this-Inseln
	while (0 != piInsel[k])	{	// pFl-Inseln
	bool bInn = false;	// this-Insel liegt bez. einer pFl-Insel INNERH (true)
	bool bInnB = false;	// this-Insel liegt bez. einer pFl-Insel INNERHB (true)
	int i = piInsel[k];	// Index für die pFl-Inseln, die innerhalb der this-Außenkontur liegen 

		for (int ii = 1; ii < _Size; ii++) {	// this-Inseln
		WMMarkLine ML1 (pFl->KA(i).ASP(), i, true);
		WMMarkLine ML2 (_KAF[ii].ASP(), ii, true);

			_ASSERTE(!(!ML1.Vektor() || !ML2.Vektor()));

		WMPosit posLage = pFl->KA(i).LageKonturZuKontur (&_KAF[ii], &ML1, &ML2, 
			bOverlap, iTouchOut);

			if (INNERH == posLage) {
				bInn = true;
				break;
			}
			else if (INNERHB == posLage || KONTUR == posLage || GLEICH == posLage) {
				bInnB = true;
				bInnerhB = true;
				break;
			}
			else if (OFFEN == posLage || UNKLAR == posLage)	{
				_ASSERTE(posLage != OFFEN);
				_ASSERTE(posLage != UNKLAR);
				return UNKLAR;
			}
		} // for

		if (!bInn && !bInnB)
			return INNAUSS;

		k++;
	} // while

	if (bInnerhB)
		return INNERHB;
	return INNERH;
}

// Memberfunktionen von GeoFlaeche

// this-Fläche wird durch pSKt-EKante geschnitten
// Test, ob die Objektcontainer der this-Fläche und der schneidenden pSKt-EKante
// durchschnittsleer sind, wird in Routine Aufbereitung1() durchgeführt und dabei 
// außerdem der Prozentzähler weitergestellt
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::ClippingMitKante (WMKante<KoOrdT>* pSKt, 
	WMClipListe<KoOrdT>& CL, int iSkip, bool& bAbbr, void* pPSt)
{
	_ASSERTE(pSKt != 0);	// pPSt kann 0 sein

bool bRet = false;	// return-Wert

// aus Stützpunktfolge der this-Flächenkontur wird Vektor pML1, aus 
// Stützpunktfolge der pSKt-EKante wird Vektor pML2 mit markierten Punkten 
// erzeugt; diese Vektoren werden in Aufbereitung1() evtl. noch erweitert
bool bClosed = (pSKt->SP(0) == pSKt->SP(pSKt->ASP()-1));
WMMarkLine ML1 (_KAF[0].ASP(), 0);
WMMarkLine ML2 (pSKt->ASP(), -1, bClosed);

	_ASSERTE(!(!ML1.Vektor() || !ML2.Vektor()));

// pML1 und pML2 werden evtl. durch Routine Aufbereitung1() modifiziert; 
// zurückgegeben werden die um die Schnittpunkte erweiterten Vektoren pML1 
// und pML2
	if (!_KAF[0].Aufbereitung1 (pSKt, &ML1, &ML2, bAbbr, pPSt)) 
		return false;

// Routine FlaecheZerlegt() ermittelt, ob die zu schneidende this-Fläche (pML1) 
// überhaupt durch die schneidende pSKt-EKante (pML2) zerlegt wird (true) oder 
// nicht
	if (FlaecheZerlegt (pSKt, &ML1))
		bRet = TeilFlaechen1 (&ML1, &ML2, CL);

// Inseln der this-Fläche (evtl.) berücksichtigen
	if (bRet &&		// Teilflächen wurden erzeugt
		_Size > 1)	// this-Fläche hat Inseln
		InselnBeiSchnittMitKante (CL, iSkip);

	return bRet;
}

// this-Fläche wird durch pSFl-Fläche geschnitten
// Test, ob die Objektcontainer der this-Fläche und der schneidenden pSFl-Fläche
// durchschnittsleer sind, wird in Routine Aufbereitung2() durchgeführt und 
// dabei außerdem der Prozentzähler weitergestellt
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::ClippingMitFlaeche (WMFlaeche* pSFl, unsigned long ulLageAusw, 
	WMClipListe<KoOrdT>& CL, int iSkip, WMPosit& posLage, bool& bAbbr, void* pPSt)
{
	_ASSERTE(pSFl != 0); 	// pPSt != 0 wird weiter unten gestestet

// aus Stützpunktfolge der this-Flächenkontur wird Vektor pML1, aus Stützpunkt-
// folge der pSFl-Fläche wird Vektor pML2 mit markierten Punkten erzeugt; diese 
// Vektoren werden in Aufbereitung2() evtl. noch erweitert
WMMarkLine ML1 (_KAF[0].ASP(), 0);
WMMarkLine ML2 (pSFl->KA(0).ASP(), 0);

	_ASSERTE(!(!ML1.Vektor() || !ML2.Vektor()));

// pML1 und pML2 werden evtl. durch Routine Aufbereitung2() modifiziert; 
// zurückgegeben werden die um die Schnittpunkte erweiterten Vektoren pML1 
// und pML2
bool bLeer;		// Container der beiden mit Aufbereitung2() verglichenen 
				//  Objekte sind durchschnittsleer (true)

	if (!_KAF[0].Aufbereitung2 (&pSFl->KA(0), &ML1, &ML2, bLeer, bAbbr, pPSt)) {
		if (bLeer)	// beide Container sind durchschnittsleer
			posLage = AUSSERH;
		else 
			posLage = UNKLAR;
		return false;
	}

// Routine KantenPosit() ermittelt, ob die Außenkontur der zu schneidenden 
// this-Fläche pML1 überhaupt durch die Außenkontur der pSFl-Fläche zerlegt 
// wird (posLage == INNAUSS) oder nicht; in letzterem Fall liegt this-Fläche 
// außerhalb (AUSSERH bzw. AUSSERHB) bzw. innerhalb (INNERH bzw. INNERHB) 
// von pSFl; für posLage == UMSCHL bzw. UMSCHLB liegt pSFl vollständig 
// innerhalb der this-Fläche, d.h. die this-Fläche umschließt pSFl
bool bOverlap;	// this-Fläche hat mit der pSFl-Außenkontur einen 
				// Überlappungsbereich
int iTouchOut;	// iTouchOut Berührungspunkte mit "Zuführung" aus der Umgebung 
				// der pSFl-Außenkontur gemeinsam

	posLage = KantenPosit (&pSFl->KA(0), &ML1, bOverlap, iTouchOut);

// keine Zerlegung
	if (posLage == AUSSERH || posLage == AUSSERHB)
		return false;

// Spezialfall: die zu schneidende this-Fläche liegt innerhalb der Außenkontur 
// der schneidenden pSFl-Fläche; es ist noch zu prüfen, ob this-Fläche in eine 
// pSFl-Insel hineinragt
	if (INNERH == posLage || INNERHB == posLage || KONTUR == posLage || 
		GLEICH == posLage)
	{
		return MesserAusserhalb (pSFl, ulLageAusw, CL, iSkip);
	}

// Spezialfall: schneidende pSFl-Fläche liegt innerhalb der Außenkontur der 
// zu schneidenden this-Fläche
	if (posLage == UMSCHL || posLage == UMSCHLB) {
	bool bEnde;	// true, wenn durch Routine MesserInnerhalb() alles erledigt wurde
	bool bRet =	MesserInnerhalb (pSFl, ulLageAusw, CL, iSkip, bOverlap, iTouchOut, bEnde);

		if (bEnde)
			return bRet;
	}

// Zerlegen in Teilflächen
bool bRet =	TeilFlaechen2 (&ML1, &ML2, ulLageAusw, CL);

// Inseln berücksichtigen
	if (bRet &&									// Teilflächen wurden erzeugt
		(_Size > 1 || pSFl->KantenAnz() > 1))	// wenigstens eine Fläche hat Inseln
	{
		if (ulLageAusw & LINN)
			InselnBeiSchnittMitFlaeche (pSFl, CL, iSkip);
		if (ulLageAusw & LAUSS)
			InselnBeiSchnittMitFlaecheAUSS (pSFl, CL, iSkip);
	}
	return bRet;
}

// Hilfsroutine für GeoFlaeche::ClippingMitFlaeche() für den Fall, daß 
// schneidende pSFl-Fläche innerhalb der Außenkontur der zu schneidenden 
// this-Fläche liegt; werden Teilflächen in CL eingetragen, wird true 
// zurückgegeben, sonst false
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::MesserInnerhalb (WMFlaeche* pSFl, unsigned long ulLageAusw, 
	WMClipListe<KoOrdT>& CL, int iSkip, bool bOverlap, int iTouchOut, bool& bEnde)
{
	_ASSERTE(pSFl != 0);

	bEnde = true;

// Test, ob pSFl-Außenkontur nicht vielleicht innerhalb einer this-Insel liegt, 
// dann wäre kein Schnitt möglich
bool bOver;	// Parameter von LageKonturZuKontur(); werden
int iTouch;	// hier nicht ausgewertet

	for (int i = 1; i < _Size; i++) {		// this-Inseln
	WMMarkLine ML1 (pSFl->KA(0).ASP(), 0);
	WMMarkLine ML2 (_KAF[i].ASP(), i, true/*, false*/);

		_ASSERTE(!(!ML1.Vektor() || !ML2.Vektor()));

	WMPosit posLage = pSFl->KA(0).LageKonturZuKontur (&_KAF[i], &ML1, &ML2, bOver, iTouch);

		if (INNERH == posLage || INNERHB == posLage || KONTUR == posLage ||
			GLEICH == posLage || OFFEN == posLage || UNKLAR == posLage)
		{
			return false;	// kein Schnitt möglich
		}
		if (INNAUSS == posLage || UMSCHL == posLage || UMSCHLB == posLage)	// 28.10.98
			break;
	} // for

int iKAnz = pSFl->KantenAnz();
bool bRet = false;	// return-Wert dieser Routine

// Wenn "innerhalb" gewählt wurde, dann ist die Außenkontur der Ergebnisfläche 
// der Teil der this-Fläche, der innerhalb von pSFl liegt, d.h. pSFl-
// Außenkontur mit Identifikator der this-Fläche
	if (ulLageAusw & LINN) {
	WMFlaeche<KoOrdT> NewArea (&pSFl->KA(0), 1);

		NewArea.AddClipObjekt (CL);

	// Inseln berücksichtigen
		if (_Size > 1 || iKAnz > 1)	// wenigstens eine Fläche hat Inseln
			InselnBeiSchnittMitFlaeche (pSFl, CL, iSkip);
		bRet = true;
	}
			
// Wenn "außerhalb" gewählt wurde und beide Außenkonturen sich höchstens in 
// einem Punkt berühren, dann entstehen als Ergebnisflächen die this-Außenkontur 
// mit der pSFl-Außenkontur als Insel sowie die pSFl-Innenkonturen als separate 
// Flächen, zu denen dann noch die this- bzw. pSFl-Inseln hinzuzunehmen sind.
	if (ulLageAusw & LAUSS) {
		if (iTouchOut <= 1 && !bOverlap) {	
		// beide Außenkonturen berühren sich höchstens in einem Punkt
		WMFlaeche<KoOrdT> NewArea (&pSFl->KA(0), 1);
		WMFlaeche<KoOrdT> GF (&_KAF[0], 1);		// 02.06.99

		// eine Außenkontur wird zur Innenkontur, deshalb Orientierung drehen
			NewArea.OrientDreh (0);
			GF.AddKante (NewArea, 1, -1);	// als Insel hinzufügen
			GF.AddClipObjekt (CL);

		// Inseln berücksichtigen
			if (_Size > 1 || iKAnz > 1)	// wenigstens eine Fläche hat Inseln
				InselnBeiSchnittMitFlaecheAUSS (pSFl, CL, iSkip);
			bRet = true;
		}
		else
			bEnde = false;	// Weiterbearbeitung mit Routine TeilFlaechen2() 
							// erforderlich
	}
	return bRet;
}

// Hilfsroutine für InselZweiteFlaecheAUSS() für den Fall, daß schneidende 
// pSFl-Insel pKont innerhalb der this-Außenkontur liegt; dann noch Test, wie 
// pKont zu den this-Innenkonturen liegt. Rückgabe von true, wenn in CL weitere 
// Schnittergebnisse eingetragen werden.
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::MesserinselInnerhalb (WMKante<KoOrdT>* pKont, int iKInd, 
	WMClipListe<KoOrdT>& CL, int iSkip)
{
	_ASSERTE(pKont != 0);

bool bOverlap;	// Parameter von LageKonturZuKontur(); werden
int iTouchOut;	// hier nicht ausgewertet

// Test, ob pSFl-Insel pKont nicht vielleicht innerhalb einer this-Insel liegt, 
// dann wäre kein Schnitt möglich
	for (int i = 1; i < _Size; i++)	{
	// this-Inseln
	WMMarkLine ML1 (pKont->ASP(), iKInd, true);
	WMMarkLine ML2 (_KAF[i].ASP(), i, true);

		_ASSERTE(!(!ML1.Vektor() || !ML2.Vektor()));

	WMPosit posLage = pKont->LageKonturZuKontur (&_KAF[i], &ML1, &ML2, bOverlap, iTouchOut);

		if (INNERH == posLage || INNERHB == posLage || KONTUR == posLage || 
			GLEICH == posLage)
		{
			return false;	// kein Schnitt möglich
		}
	} // for

WMFlaeche<KoOrdT> NewArea (&pKont, 1);

	NewArea.OrientDreh (0);			// Insel wird zur Außenkontur, deshalb drehen
	NewArea.AddClipObjekt (CL);

	if (_Size > 1)
		InselnBeiSchnittMitKante (CL, iSkip);	// this-Inseln berücksichtigen

	return true;
}

// Hilfsroutine für GeoFlaeche::ClippingMitFlaeche() für den Fall, daß zu 
// schneidende this-Fläche innerhalb der Außenkontur der schneidende pSFl-Fläche 
// liegt; Rückgabe von true, wenn geschnitten wurde und damit Schnittergebnisse 
// in CL eingetragen wurden, ansonsten false
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::MesserAusserhalb (WMFlaeche* pSFl, unsigned long ulLageAusw, 
		WMClipListe<KoOrdT>& CL, int iSkip)
{
	_ASSERTE(pSFl != 0);

int iKAnz = pSFl->KantenAnz();

	if (iKAnz == 1) return false;
	
// Feld für die Indizes der pSFl-Inseln, die noch mit den this-Inseln zu 
// vergleichen sind
int k = 0;		// Laufindex für piInsel
vector<int> piInsel(iKAnz, 0);	
bool bOverlap;	// Parameter von LageKonturZuKontur(); werden
int iTouchOut;	// hier nicht ausgewertet

// Lage der pSFl-Inseln zu der this-Außenkontur
	for (int i = 1; i < iKAnz; i++)	{		// pSFl-Inseln
	WMMarkLine ML1 (pSFl->KA(i).ASP(), i, true);
	WMMarkLine ML2 (_KAF[0].ASP(), 0);

		_ASSERTE(!(!ML1.Vektor() || !ML2.Vektor()));

	WMPosit posLage = pSFl->KA(i).LageKonturZuKontur (&_KAF[0], &ML1, &ML2, 
		bOverlap, iTouchOut);

		if (posLage == INNAUSS)	{
			if (ulLageAusw & LINN) {	// Schnittergebnis "innerhalb"
			WMFlaeche<KoOrdT> NewArea (&_KAF[0], 1);

			// this-Außenkontur nach CL
				NewArea.AddClipObjekt (CL);
				InselnBeiSchnittMitFlaeche (pSFl, CL, iSkip);
				return true;
			}
			else {
			// Schnittergebnis "außerhalb"
				InselnBeiSchnittMitFlaecheAUSS (pSFl, CL, iSkip);	// erst ab 11.09.98
				return true;
			}
		}

	// eine pSFl-Insel liegt innerhalb der this-Außenkontur, deshalb sind die 
	// this-Inseln noch zu Rate zu ziehen
		if (posLage == INNERH || posLage == INNERHB) {
			piInsel[k] = i;
			k++;
			continue;
		}

		// eine pSFl-Insel umschließt die this-Außenkontur
		if (UMSCHL == posLage || UMSCHLB == posLage || KONTUR == posLage ||
			GLEICH == posLage || OFFEN == posLage || UNKLAR == posLage)
		{
			return false;	// kein Schnitt möglich
		}
	} // for

// noch weitere Tests mit den this-Innenkonturen (so sie vorhanden sind)
	if (0 != piInsel[0])	// 29.10.98
		MesserAusserhalbWeiter (pSFl, ulLageAusw, CL, iSkip, piInsel.begin());

	return true;	// 11.09.98 ("true", weil sonst die Originalobjekte nicht angezeigt werden)
}

// Hilfsroutine für MesserAusserhalb() für den Fall, daß mindestens eine 
// pSFl-Insel innerhalb der this-Außenkontur liegt; wenn für mindestens eine 
// dieser pSFl-Inseln gilt, daß sie nicht innerhalb einer this-Insel liegen, 
// kann geschnitten werden;
// Rückgabe von true, wenn geschnitten wurde und damit Schnittergebnisse in CL 
// eingetragen wurden, ansonsten false
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::MesserAusserhalbWeiter (WMFlaeche* pSFl, 
	unsigned long ulLageAusw, WMClipListe<KoOrdT>& CL, int iSkip, int* piInsel) 
{
	_ASSERTE(pSFl != 0);
	_ASSERTE(piInsel != 0);

	if (0 == piInsel[0]) 
		return false;	// 29.10.98

bool bAbbr = false;	// true: Abbruch der while-Schleife
int k = 0;			// Laufindex für piInsel
bool bOverlap;		// Parameter von LageKonturZuKontur(); werden hier
int iTouchOut;		// nicht ausgewertet

// Lage der pSFl-Inseln, die innerhalb der this-Außenkontur liegen, zu den this-Inseln
	while (0 != piInsel[k])	{	// pSFl-Inseln
	int i = piInsel[k];			// Index für die pSFl-Inseln, die innerhalb der 
								// this-Außenkontur liegen 

		for (int ii = 1; ii < _Size; ii++) {	// this-Inseln
		WMMarkLine ML1 (pSFl->KA(i).ASP(), i, true);
		WMMarkLine ML2 (_KAF[ii].ASP(), ii, true);

			_ASSERTE(!(!ML1.Vektor() || !ML2.Vektor()));

		WMPosit posLage = pSFl->KA(i).LageKonturZuKontur (&_KAF[ii], &ML1, &ML2, 
			bOverlap, iTouchOut);

			if (INNERH == posLage || INNERHB == posLage || KONTUR == posLage ||
				GLEICH == posLage || OFFEN == posLage || UNKLAR == posLage)
			{
			// for-Schleife abbrechen, da getestete pSFl-Insel innerhalb einer 
			// this-Insel liegt; es muß aber einer pSFl-Insel gefunden werden, 
			// die außerhalb von allen this-Inseln liegt
				bAbbr = true;
				break;
			}

			if (posLage == INNAUSS)	{	// 15.03.99
				bAbbr = false;
				break;
			}
		} // for

		if (bAbbr) 
			k++;
		else {
		// wenn for-Schleife nicht abgebrochen wurde, gibt es mindestens eine 
		// pSFl-Insel, die nicht innerhalb einer this-Insel liegt, d.h. es kann 
		// geschnitten werden und deshalb gleich while-Schleife abbrechen
			break;
		}
	} // while

	if (bAbbr) 
		return false;	// kein Schnitt möglich

bool bRet1 = false;	// return-Werte
bool bRet2 = false;

	if (ulLageAusw & LINN) {	// Schnittergebnis "innerhalb"
		AddClipObjekt (CL);					// this-Fläche nach CL
		pSFl->InselnInnerhalb (CL, iSkip);	// pSFl-Inseln noch berückichtigen
		bRet1 = true;
	}

	if (ulLageAusw & LAUSS)		// Schnittergebnis "außerhalb" (29.10.98)
		bRet2 = InselZweiteFlaecheAUSS (pSFl, CL);

	return bRet1 || bRet2;
}

// Wenn bei Schnitt der this-Fläche durch die pSFl-Fläche die Schnittergebnisse 
// außerhalb der schneidenden Fläche liegen sollen, wird hier geprüft, wie die 
// pSFl-Inseln zur this-Fläche (NICHT zu den CL-Flächen) liegen.
// Wenn weitere Schnittergebnisse in CL eingetragen werden, dann wird true 
// zurückgegeben, sonst false.
// Ich hoffe, daß durch folgende kühne Überlegung alle denkbaren Fälle 
// abgefangen werden:
// Aus jeder SFl-Insel wird eine neue schneidende Fläche (ohne Inseln !) 
// gebildet, die die this-Fläche (i.a. mit Inseln) mit "innerhalb" schneidet. 
// Die Ergebnisse werden erst in einer Zwischenliste CLZw abgelegt und dann 
// nach CL übertragen !!!!!
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::InselZweiteFlaecheAUSS (WMFlaeche* pSFl, 
	WMClipListe<KoOrdT>& CL)
{
	_ASSERTE(pSFl != 0);

int iKAnz = pSFl->KantenAnz();

	if (iKAnz == 1) 
		return false;

bool bOverlap;		// Parameter von LageKonturZuKontur(); werden
int iTouchOut;		// hier nicht ausgewertet
bool bRet = false;	// return-Wert dieser Routine
WMClipListe<KoOrdT> CLZw;		// ClipListe für Zwischenergebnisse

// Test, ob sich eine pSFl-Insel mit der this-Außenkontur schneidet
	for (int i = 1; i < iKAnz; i++) {
	WMMarkLine ML1 (_KAF[0].ASP(), 0);
	WMMarkLine ML2 (pSFl->KA(i).ASP(), i, true);

		_ASSERTE(!(!ML1.Vektor() || !ML2.Vektor()));

	WMPosit posLage = _KAF[0].LageKonturZuKontur (&pSFl->KA(i), &ML1, &ML2, 
		bOverlap, iTouchOut);

	// keine weiteren Schnittergebnisse, wenn die zu schneidende this-Fläche 
	// innerhalb der schneidenden pSFl-Insel liegt
		if (INNERH == posLage || INNERHB == posLage || KONTUR == posLage ||
			GLEICH == posLage || UNKLAR == posLage || OFFEN == posLage)
		{
			return false;
		}

// wenn die beiden nachfolgenden Zeilen drin blieben, müßte DELETE_OBJ (pML1); 
// DELETE_OBJ (pML2); hinzugefügt werden (29.10.98)
//		if (posLage == AUSSERH || posLage == AUSSERHB)
//			continue;

	// schneidende pSFl-Insel liegt innerhalb der Außenkontur der zu schneidenden
	// this-Fläche; dann Test mit den this-Innenkonturen
		if (posLage == UMSCHL || posLage == UMSCHLB)
			MesserinselInnerhalb (&pSFl->KA(i), i, CLZw, 0);

	// pSFl-Insel schneidet die Außenkontur der this-Fläche;
	// dann Schnitt mit der this-Außenkontur pML1 und Test mit den this-Innenkonturen
		if (posLage == INNAUSS) {
			TeilFlaechen2 (&ML1, &ML2, LINN, CLZw);
			InselnBeiSchnittMitKante (CLZw, 0);	// in CLZw braucht nichts übergangen zu werden
		}

	// wenn in CLZw Zwischenergebnisse abgelegt wurden, dann diese jetzt nach CL übernehmen
		if (CLZw.size() > 0) {
		WMClipListe<KoOrdT>::iterator end = CLZw.end();

			for (WMClipListe<KoOrdT>::iterator riz = CLZw.begin(); riz != end; ++riz)
			{
				(*riz)->AddClipObjekt (CL);
			}
			CLZw.clear();
			bRet = true;
		}
	} // for
	return bRet;
}

// Hilfsroutine für InselZweiteFlaeche()
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::ZweiInselnVereinigen (WMClipListe<KoOrdT>& CL, 
	WMFlaeche*& pNewIsland, WMMarkLine* pML1, WMMarkLine* pML2)
{
	_ASSERTE(pML1 != 0);
	_ASSERTE(pML2 != 0);

WMFlaeche<KoOrdT> UniIsland;

	ContourUnion (pML1, pML2, &UniIsland, false);	// sonst könnte "Insel in Insel" entstehen (28.05.99)

int iKCnt = UniIsland.KantenAnz();

	for (int i = 0; i < iKCnt; i++) {
		if (0 == i)	{
			DELETE_OBJ (pNewIsland);
			pNewIsland = new WMFlaeche<KoOrdT>(&UniIsland.KA(i), 1);
		}
		else {
		// Innenkonturen von pUniIsland werden zu separaten Ergebnisflächen
		WMFlaeche<KoOrdT> NewArea (&UniIsland.KA(i), 1);

			NewArea.OrientDreh (0);			// Insel wird zur Außenkontur, deshalb drehen
			NewArea.AddClipObjekt (CL);
		}
	}
	return true;
}

// Memberfunktionen

// Inseln der this-Fläche bei Schnittoperationen mit Schnittkante 
// berücksichtigen; die ersten iSkip Einträge in CL sind dabei zu übergehen
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::InselnBeiSchnittMitKante (WMClipListe<KoOrdT>& CL, 
	int iSkip)
{
bool bModify;	// wird hier nicht ausgewertet

// Feld für die Indizes der Inseln, die schon "verbraucht" wurden
vector<int> piVbInsel(_Size, 0);

bool bRet1 = InselnAmRand (CL, iSkip, piVbInsel.begin(), bModify);
bool bRet2 = InselnInnerhalb (CL, iSkip, piVbInsel.begin());

	return bRet1 && bRet2; 
}

// Inseln der this-Fläche, die am Rand der in CL enthaltenen Schnittergebnisse 
// liegen, bei Schnittoperationen mit Schnittkante berücksichtigen; die ersten 
// iSkip Einträge in CL sind dabei zu übergehen;
// in bModify wird zurückgegeben, ob an mindestens einer CL-Fläche eine 
// Veränderung durch "Anknabbern" der Außenkontur vorgenommen wurde (true), 
// sonst false
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::InselnAmRand (WMClipListe<KoOrdT>& CL, int iSkip, 
	int* piVbInsel, bool& bModify)
{
	bModify = false;
	if (0 == CL.size() || 1 == _Size) 
		return true;	// keine Inseln

	_ASSERTE(piVbInsel != 0);

WMClipListe<KoOrdT> CLZw;	// ClipListe für Zwischenergebnisse
bool bOverlap;  // Teilfläche hat mit dem Rand einer this-Insel einen Überlappungsbereich bzw.
int iTouchOut;	// iTouchOut Berührungspunkte mit "Zuführung" aus der _KAF[i]-Umgebung gemeinsam

	for (int i = 1; i < _Size; i++)	{
	// alle Inseln, die noch nicht verbraucht sind
	bool bVerbr = false;	// Insel noch nicht verbraucht

		for (int j = 0; j < _Size-1; j++) {
			if (piVbInsel[j] == i)
			{
				bVerbr = true;	// diese Insel wurde schon verarbeitet
				break;
			}
			if (piVbInsel[j] == 0) 
				break;
		}
		if (bVerbr) 
			continue;

	// do-Schleife für alle in CL befindlichen Schnittergebnisse (die ersten 
	// iSkip Einträge in CL sind zu übergehen)
	WMClipListe<KoOrdT>::iterator ri = CL.begin();
	WMClipListe<KoOrdT>::iterator end = CL.end();

		_ASSERTE(iSkip >= 0 && iSkip < CL.size());	// wenigstens einer muß noch da sein
		advance(ri, iSkip);
		do {
		bool bDel = false;	// im Zugriff befindliches Teilobjekt (kann Fläche 
				// aber auch Kante sein) ist aus CL (noch) nicht zu löschen

			if (OT_KANTE == (*ri)->isA()) {
				++ri;
				continue;
			}

		WMFlaeche<KoOrdT> *pTF = (WMFlaeche<KoOrdT> *)(*ri);

			PartialCleaningForLines (&pTF->KA(0), -1);	// 09.02.99

		// aus Stützpunktfolge der Außenkontur der ml-Teilfläche wird Vektor 
		// pML1, aus _KAF[i]-Insel wird Vektor pML2 mit markierten Punkten 
		// erzeugt; diese Vektoren werden in Aufbereitung2() evtl. noch erweitert
		// Bildung von pML2 muß innerhalb der do-Schleife erfolgen, da diese 
		// Variable in LageKonturZuKontur() durch Aufbereitung2() verändert wird
		WMMarkLine ML1 (pTF->KA(0).ASP(), 0);
		WMMarkLine ML2 (_KAF[i].ASP(), i, true);

			_ASSERTE(!(!ML1.Vektor() || !ML2.Vektor()));
			
		// Lage der this-Inseln bez. der Teilflächen aus CL bestimmen
		WMPosit posLage = pTF->KA(0).LageKonturZuKontur (&_KAF[i], &ML1, &ML2, 
			bOverlap, iTouchOut);

		// gleich schneiden;  es können dabei mehrere Teilflächen entstehen
		// (UMSCHLB statt INNERHB, da Inseln math.neg. orientiert sind)
			if (INNAUSS == posLage ||
				(UMSCHLB == posLage && (bOverlap || iTouchOut > 1)))
			{
				TeilFlaechen2 (&ML1, &ML2, LAUSS, CLZw);
				bDel = true;	// im Zugriff befindliche Teilfläche soll aus CL gelöscht werden
				bModify = true;	// eine CL-Fläche wurde modifiziert

			// Insel als verbraucht registrieren
				for (int j = 0; j < _Size-1; j++) {
					if (piVbInsel[j] == i) 
						break;	// Insel ist schon als verbraucht registriert
					if (piVbInsel[j] == 0) {
						piVbInsel[j] = i;
						break;
					}
				}
				_ASSERTE(j < _Size-1);
			}

			if (bDel) {
				ri = CL.erase(ri);	// aktuelle Teilfläche in CL löschen (diese wurde durch	die
									//  "angeknabberte" Unter-Teilflächen ersetzt)
			} else 
				++ri;
		} while (ri != end);

	// wenn in CLZw Zwischenergebnisse abgelegt wurden, dann diese jetzt nach CL übernehmen
		if (0 == CLZw.size()) 
			continue;

	WMClipListe<KoOrdT>::iterator endr = CLZw.end();

		for (WMClipListe<KoOrdT>::iterator riz = CLZw.begin(); riz != endr; ++riz)
		{
			(*riz)->AddClipObjekt (CL);
		}
		CLZw.clear();
	} // for
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Konstruktoren

// nur eine Kante
template <typename KoOrdT>
inline 
WMFlaeche<KoOrdT>::WMFlaeche (WMPunktVec<KoOrdT>* SPF, long Size) :
	_KAF(NULL), _Size(0), _OCont(NULL) 
{
	_ASSERTE(SPF != 0);
	if (Size > 0) {
		_KAF = new WMKante<KoOrdT>[1];   // Kantenfolge immer als Array anlegen !!
		_Size = 1;
		_KAF[0].AddPunkt (SPF, Size, -1);
	}
}

template <typename KoOrdT>
inline 
WMFlaeche<KoOrdT>::WMFlaeche() :
	_KAF(NULL), _Size(0), _OCont(NULL)
{ 
}

// EFlaeche generieren, die nur aus einer Kante besteht
template <typename KoOrdT>
inline 
WMFlaeche<KoOrdT>::WMFlaeche (KoOrdT x[], KoOrdT y[], long Len) :
	_KAF(NULL), _Size(0), _OCont(NULL)
{
	_ASSERTE(x != 0);
	_ASSERTE(y != 0);

	if (Len > 0) {
		_KAF = new WMKante<KoOrdT>[1];   // Kantenfolge immer als Array anlegen !!
		_Size = 1;
		_KAF[0].AddPunkt (x, y, Len, -1);
	}
}

// mehrere Kanten
// Flaeche - Konturfeld der this-EFlaeche
// size    - Anzahl der Konturen dieser Fläche
template <typename KoOrdT>
inline 
WMFlaeche<KoOrdT>::WMFlaeche (WMKante<KoOrdT> *Flaeche, int size) :
	_KAF(NULL), _Size(0), _OCont(NULL)
{
	if (size != 0 && Flaeche != 0) {
		_KAF = new WMKante<KoOrdT>[size];	// Konturfeld anfordern
		_Size = size;
		for (int i = 0; i < size; i++)		// Kopieren der einzelnen Konturen
			_KAF[i] = Flaeche[i];
	}
}

// Kontur - Feld von Pointern auf die Konturen der this-EFlaeche
// size   - Anzahl der Konturen dieser Fläche
template <typename KoOrdT>
inline 
WMFlaeche<KoOrdT>::WMFlaeche (WMKante<KoOrdT> ** Kontur, int size) :
	_KAF(NULL), _Size(0), _OCont(NULL)
{
	if (size != 0 && Kontur != 0) {
		_KAF = new WMKante<KoOrdT>[size];	// Konturfeld anfordern
		_Size = size;
		for (int i = 0; i < size; i++)		// Kopieren der einzelnen Konturen
			_KAF[i] = *(Kontur[i]);
	}
}

// Copy-Konstruktor
template <typename KoOrdT>
inline 
WMFlaeche<KoOrdT>::WMFlaeche (const WMFlaeche &newFlaeche) :
	_KAF(NULL), _Size(0), _OCont(NULL)
{
	if (newFlaeche._Size != 0 || newFlaeche._KAF != 0) {
		_KAF = new WMKante<KoOrdT>[newFlaeche._Size];	// Konturenfeld anlegen
		_Size = newFlaeche._Size;

		for (int i = 0; i < newFlaeche._Size; i++)
			_KAF[i] = newFlaeche._KAF[i];
		if (newFlaeche._OCont) 
			_OCont = new WMObjRechteck<KoOrdT>(*newFlaeche._OCont);
	}
}

template <typename KoOrdT>
inline 
WMFlaeche<KoOrdT>::~WMFlaeche (void)
{
	_Size = 0;
	DELETE_VEC (_KAF);
	DELETE_OBJ (_OCont);
}

// Memberfunktionen
template <typename KoOrdT>
inline WMFlaeche<KoOrdT> &
WMFlaeche<KoOrdT>::operator= (const WMFlaeche &newFlaeche)
{
	if (this == &newFlaeche) 
		return;	 // Vorsicht nicht s=s !

	_Size = 0;
	DELETE_VEC (_KAF);
	DELETE_OBJ (_OCont);
	if (newFlaeche._Size == 0 || NULL == newFlaeche._KAF)
		return;

	_KAF = new WMKante<KoOrdT>[newFlaeche._Size];     // Konturenfeld anlegen
	_Size = newFlaeche._Size;
	for (int i = 0; i < newFlaeche._Size; i++)
		_KAF[i] = newFlaeche._KAF[i];

	if (newFlaeche._OCont) 
		_OCont = new WMObjRechteck<KoOrdT>(*newFlaeche._OCont);
}

// liefert Kantenanzahl
template <typename KoOrdT>
inline int 
WMFlaeche<KoOrdT>::KantenAnz (void) const 
{ 
	return _Size;
}

template <typename KoOrdT>
inline long
WMFlaeche<KoOrdT>::ASP() const       // liefert Gesamtanzahl der Stützpunkte
{
long cnt = 0;

	for (int i = 0; i < KantenAnz(); i++)
		cnt += KA(i).ASP();
	return cnt;
}

template <typename KoOrdT>
inline WMObjRechteck<KoOrdT> 
WMFlaeche<KoOrdT>::GetCont() const
{
	if (_OCont) 
		return *_OCont;
	else {
	WMObjRechteck<KoOrdT> OC (std::numeric_limits<KoOrdT>::max(), 0, 
		std::numeric_limits<KoOrdT>::max(), 0);

		return maxCont(OC);
	}
}

// Berechnung des Flächeninhalt einer Flächen unter Berücksichtigung von 
// Innenkonturen, der bei einem Fehler gleich 0 ist
template <typename KoOrdT>
inline double 
WMFlaeche<KoOrdT>::AreaSize() const
{
// berechne Inhalt der äußeren Fläche
double dInhalt = fabs (_KAF[0].PolygonArea());

    if (0 == dInhalt)	// wenn Inhalt nicht berechnet werden konnte,
		return 0;		// mit 0 zurück

	if (_Size > 1) {	// Fläche hat Inseln
		for (int i = 1; i < _Size; i++)					// subtrahiere den Inhalt
			dInhalt -= fabs (_KAF[i].PolygonArea());	// aller Inseln
	}
	return dInhalt;		// mit Differenz zurück
}
	
// berechnet den vorzeichenbehafteten Flächeninhalt und Schwerpunkt der äußeren
// Kontur (ohne Löcher) einer Fläche. Fehler wenn Flächeninhalt == 0.0.
template <typename KoOrdT>
inline double 
WMFlaeche<KoOrdT>::SchwerPunkt (WMPunkt<KoOrdT> &Pt) const        
{
// teste Parameter der Fläche
WMKante<KoOrdT> &Ka = _KAF [0];	   // Referenz auf äußere Kante
long Size = Ka.ASP();	   // Anzahl Stützpunkte

	if ((Ka.SP(0) != Ka.SP(Size - 1)) ||    // wenn AnfPkt versch. EnPkt
			(Size <= 3))	// oder zuwenig Punkte
	{
		return 0.0;			// mit ungültigem Wert zurück
	}

// kleinste X/Y-Koordinate bestimmen
WMObjRechteck<KoOrdT> OC (Ka.GetCont()); // Koordinaten bestimmen und
KoOrdT Xmin = OC.XMin();	 // lesen
KoOrdT Ymin = OC.YMin();

// Schwerpunkt u. Flächeninhalt berechnen
double Xs, Ys, Xsi, Ysi, Inh;   // Schwerpunkt-Koordinaten, Flächeninhalt
double FlI;						// Flächeninhalt

	Xs = Ys = FlI = 0.0;	    // Werte definiert initialisieren
	for (long i = 0; i < (Size - 1); i++) { // für alle Punkte der Folge
	// akt. Koordinaten lesen
	double X1 = double (Ka.SP(i).X()   - Xmin),
	       Y1 = double (Ka.SP(i).Y()   - Ymin),
	       X2 = double (Ka.SP(i+1).X() - Xmin),
	       Y2 = double (Ka.SP(i+1).Y() - Ymin);

	// Zwischenwerte berechnen
		if ((Y1 + Y2) != 0) {      // wenn Berechnung möglich
			Xsi = X1 + ((X2 - X1) * ((2.0 * Y2) + Y1)) / (3.0 * (Y1 + Y2));
			Ysi = ((Y1 * Y1) + (Y1 * Y2) + (Y2 * Y2)) / (3.0 * (Y1 + Y2));
			Inh = (X1 - X2) * (Y1 + Y2) * 0.5;

		} else 
			Xsi = Ysi = Inh = 0.0;      // alle Werte 0 setzen

	// Zwischenwerte aktualisieren
		Xs += Xsi * Inh;	// Schwerpunkt
		Ys += Ysi * Inh;
		FlI += Inh;			// Inhalt der Fläche
	}

// Endkoordinaten berechnen
	if (FlI == 0.0) {	     // wenn Fl.-Inhalt ungültig
//		DEX_Error (RC_SchwPktMasche, EC_NOSCHWERPUNKT);	// Fehlermeldung ausg.
		_ASSERTE(FlI != 0.0);
		return 0.0;
	} 
	else {
		Pt = WMPunkt<KoOrdT> (KoOrdT((Xs / FlI) + Xmin + 0.5),	// Koordinaten
					 KoOrdT((Ys / FlI) + Ymin + 0.5));	// runden u. zurück
		return FlI;
	}
}

// umschließendes Rechteck
template <typename KoOrdT>
inline WMObjRechteck<KoOrdT> &
WMFlaeche<KoOrdT>::maxCont (WMObjRechteck<KoOrdT> &OC) const 
{
	for (int i = 0; i < _Size; i++)
		_KAF[i].maxCont(OC);

	return OC;
}

// k.g. Rechteck (Schnitt)
template <typename KoOrdT>
inline WMObjRechteck<KoOrdT> &
WMFlaeche<KoOrdT>::minCont (WMObjRechteck<KoOrdT> &OC) const 
{
	for (int i = 0; i < _Size; i++)
		_KAF[i].minCont(OC);

	return OC;
}

// WMKante n liefern
template <typename KoOrdT>
inline WMKante<KoOrdT> &
WMFlaeche<KoOrdT>::KA (int n) const 
{  
	_ASSERTE(n >= 0 && n < _Size); 
	return _KAF[n];
}

// interne Werte modifizieren

// Hinzufügen einer EFlaeche (z.B. inneres Loch in Fläche)
// Flaeche - Kantenfeld der this-EFlaeche
template <typename KoOrdT>
inline void 
WMFlaeche<KoOrdT>::AddKante (WMFlaeche const &Flaeche, int Anzahl, int Index)
{
	if (Index == -1)	// ans Ende anhängen
		Index = _Size;

	_ASSERTE(!(Anzahl == 0 || Flaeche._KAF == 0 || Index < 0 || Index > _Size));

int i, j;
WMKante<KoOrdT> *newKAF = new WMKante<KoOrdT>[_Size + Anzahl];

	--Index;	// besser zu verwenden
	for (i = 0; i <= Index; i++)
		newKAF[i] = _KAF[i];			// Beginn kopieren
	for (j = 0; j < Anzahl; i++, j++)
		newKAF[i] = Flaeche._KAF[j];    // Einfügen
	for (j = Index +1; i < _Size + Anzahl; i++, j++)
		newKAF[i] = _KAF[j];			// Rest kopieren

	DELETE_VEC(_KAF);
	_Size += Anzahl;
	_KAF = newKAF;
}

// nur eine Kante in EFlaeche einfügen
template <typename KoOrdT>
inline void 
WMFlaeche<KoOrdT>::AddKante (KoOrdT x[], KoOrdT y[], long Len, int Index)
{
	if (Index == -1)	// ans Ende anhängen
		Index = _Size;

	_ASSERTE(!(Len == 0 || Index < 0 || Index > _Size));

int i, j;
WMKante<KoOrdT> *newKAF = new WMKante<KoOrdT>[_Size + 1];

	--Index;	// besser zu verwenden
	for (i = 0; i <= Index; i++)
		newKAF[i] = _KAF[i];	  				// Beginn kopieren
	newKAF[i++] = WMKante<KoOrdT>(x, y, Len);	// Einfügen
	for (j = Index +1; i <= _Size; i++, j++)
		newKAF[i] = _KAF[j];					// Rest kopieren

	DELETE_VEC (_KAF);
	_Size++;
	_KAF = newKAF;
}

// Innenkontur(en) einer Fläche löschen
// 1 <= iAnzahl < _Size Innenkonturen werden ab Konturindex 1 <= iIndex < _Size 
// gelöscht; für iIndex == -1 wird letzte Innenkontur gelöscht sollen mehr 
// Innenkonturen gelöscht werden als vorhanden sind, werden die Innenkonturen 
// ab iIndex bis zur letzten gelöscht
template <typename KoOrdT>
inline void 
WMFlaeche<KoOrdT>::SubKante (int iAnzahl, int iIndex)
{
	if (iIndex == -1 && _Size > 1)   // letzte Innenkontur löschen
		iIndex = _Size-1;

	if (_Size - iIndex < iAnzahl)		// es sollen mehr Innenkonturen gelöscht werden
		iAnzahl = _Size - iIndex;		// als ab iIndex noch vorhanden sind

	_ASSERTE(iAnzahl >= 1);
	_ASSERTE(iAnzahl < _Size);
	_ASSERTE(iIndex >= -1);
	_ASSERTE(iIndex != 0);
	_ASSERTE(iIndex < _Size);
	_ASSERTE(1 != _Size);				// muß Innenkonturen haben

	for (int i = iIndex; i < _Size-iAnzahl; i++)
		_KAF[i] = _KAF[i+iAnzahl];

	_Size -= iAnzahl;
}

// Punkt(e) zu einer der Kanten hinzufügen
template <typename KoOrdT>
inline void 
WMFlaeche<KoOrdT>::AddPunkt (const WMKante<KoOrdT> &K, long KAnz, long KIndex, 
	int MIndex)
{
	if (MIndex == -1)	// ans Ende anhängen
		MIndex = _Size;
	_ASSERTE(!(MIndex < 1 || MIndex > _Size));
	_KAF[MIndex-1].AddPunkt (K, KAnz, KIndex);
}

// Len > 0 Punkte werden vor Stützpunktnummer -1 <= KIndex <= Konturlänge 
//eingefügt
template <typename KoOrdT>
inline void 
WMFlaeche<KoOrdT>::AddPunkt (KoOrdT x[], KoOrdT y[], long Len, long KIndex, 
	int MIndex)
{
	if (MIndex == -1)	// ans Ende anhängen
		MIndex = _Size;

	_ASSERTE(!(MIndex < 1 || MIndex > _Size));
	_KAF[MIndex-1].AddPunkt (x, y, Len, KIndex);
}

// Punkt(e) in einer der Flächenkonturen löschen
// Len > 0 Punkte werden ab Stützpunktnummer 0 <= KIndex < _KAF[MIndex-1].ASP() 
// gelöscht; 1 <= MIndex <= _Size ist der Konturindex
template <typename KoOrdT>
inline void 
WMFlaeche<KoOrdT>::SubPunkt (long Len, long KIndex, int MIndex)
{
	_ASSERTE(Len > 0);
	_ASSERTE(KIndex >= 0);
	_ASSERTE(MIndex >= 1);
	_ASSERTE(MIndex <= _Size);

	if (MIndex == 1) {	// Außenkontur
		_ASSERTE(!(_KAF[0].ASP() <= Len));		// es müßte die komplette Außenkontur gelöscht werden
		_KAF[MIndex-1].SubPunkt (Len, KIndex);
	}
	else {
	// Innenkontur
		if (_KAF[MIndex-1].ASP() <= Len)		// es wird eine komplette Innenkontur gelöscht
			SubKante (1, MIndex-1);
		else
			_KAF[MIndex-1].SubPunkt (Len, KIndex);
	}
}

// Außenkontur und i-te Innenkontur werden getauscht, d.h. die i-te Innenkontur 
// wird zur Außenkontur; wenn der Tausch erfolgreich war, wird true 
// zurückgegeben, sonst false
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::TauschKante (int i)
{
	_ASSERTE(i >= 0);
	_ASSERTE(i < _Size);

WMFlaeche<KoOrdT> NewOut (&_KAF[i], 1);	// neue Außenkontur
WMFlaeche<KoOrdT> NewIn (&_KAF[0], 1);	// neue Innenkontur

	SubKante (1, i);			// i-te Innenkontur löschen
	AddKante (NewOut, 1, 0);	// neue Außenkontur hinzufügen
	SubKante (1, 1);			// alte Außenkontur löschen
	AddKante (NewIn, 1, -1);	// neue Innenkontur hinzufügen

	return true;
}

// Container setzen
template <typename KoOrdT>
inline void 
WMFlaeche<KoOrdT>::SetCont (KoOrdT Cont[])
{
	_ASSERTE(Cont != 0);

WMObjRechteck<KoOrdT> newCont = new WMObjRechteck<KoOrdT>(Cont[0], Cont[1], 
	Cont[2], Cont[3]);

	DELETE_OBJ(_OCont);
	_OCont = newCont;
}

///////////////////////////////////////////////////////////////////////////////
// Test auf Geometriefehler

// Kontur einer Fläche ist offen (true), d.h. 1. und letzter Punkt sind 
// verschieden, sonst false; 0 <= i < _Size ist Konturindex
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::isOffen (int i) const
{
	_ASSERTE(i >= 0);
	_ASSERTE(i < _Size);

long lKCnti = _KAF[i].ASP();  // Länge der i-ten Kontur

	if (lKCnti <= 2)	// eine entartete Kontur wird an anderer Stelle angemeckert 
		return false;	// und ist durch Schließen nicht mehr zu retten (08.09.98)

double hw = AbstandPktPktE (_KAF[i].SP(0), _KAF[i].SP(lKCnti-1));

	return hw > 0;	// 08.09.98
}

// Umlaufsinn einer Kontur fehlerhaft (true), sonst false;
// Außenkontur muß mathematisch positiv, Innenkonturen müssen mathematisch 
// negativ orientiert sein (durch Berechnung des vorzeichenbehafteten 
// Flächeninhaltes FlInh eines geschlossenen Polygonzuges); 
// 0 <= i < _Size ist der Konturindex
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::isWrongTurning (int i) const
{
	_ASSERTE(i >= 0);
	_ASSERTE(i < _Size);

double dFlInh = _KAF[i].PolygonArea();

	return ((i == 0 && dFlInh <= 0.0) ||	// Außenkontur
			(i > 0 && dFlInh >= 0.0));		// Innenkontur(en)
}

// Umlaufsinn einer Kontur umorientieren (0 <= i < _Size ist der Konturindex)
template <typename KoOrdT>
inline void 
WMFlaeche<KoOrdT>::OrientDreh (int i)
{
	_ASSERTE(i >= 0);
	_ASSERTE(i < _Size);

long lKCnti = _KAF[i].ASP();

	for (long k = 0; k < lKCnti/2; k++)	{
	KoOrdT x = _KAF[i].SP(lKCnti-k-1).X();
	KoOrdT y = _KAF[i].SP(lKCnti-k-1).Y();

		_KAF[i].SPV(lKCnti-k-1).X() = _KAF[i].SP(k).X();
		_KAF[i].SPV(lKCnti-k-1).Y() = _KAF[i].SP(k).Y();
		_KAF[i].SPV(k).X() = x;
		_KAF[i].SPV(k).Y() = y;
	}
}

// Umlaufsinn aller Konturen einer Fläche prüfen und ggf. richtig drehen,
// falls der Flächeninhalt der Fläche bzw. einer Insel 0 ist, Rückgabe von 
// false 
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::Umlaufsinn()
{
	for (int i = 0; i < _Size; i++) {
	double dFlInh = _KAF[i].PolygonArea();	// vorzeichenbehafteter Flächeninhalt

		if (0 == dFlInh)   // entartete oder fehlerhafte Fläche
			return false;

		if ((i == 0 && dFlInh < 0) ||	// Außenkontur math. negativ bzw.
			(i > 0 && dFlInh > 0))		// Innenkontur math. positiv orientiert
		{
			OrientDreh (i);				// Konturumlaufsinn umdrehen
		}
	}
	return true;

}
	
// Test auf Überschneidung zwischen den Konturen (return-Wert: true), sonst 
// false mit Rückgabewert Fo
//   KEINE      keine Überschneidung, GP1 und GP2 unbestimmt
//   ECHT       Überschneidung, so daß Schnittpunkt GP1 jeweils im "Inneren" 
//              der beiden betr. Konturstrecken liegt, GP2 unbestimmt
//   RAND_MIT   Überschneidung, so daß Schnittpunkt GP1 bei beiden betr. 
//              Konturen ein Stützpunkt ist (Stützpunktgleichheit mit 
//				Seitenwechsel), GP2 unbestimmt
//   INNEN_MIT  Überschneidung, so daß Schnittpunkt GP1 bei einer Kontur ein 
//              Stützpunkt, bei der anderen im "Inneren" einer Konturstrecke 
//              liegt (Berührungspunkt mit Seitenwechsel), GP2 unbestimmt
//   UEBERLAPP  Überlappung von Strecken beider Konturen, GP1 und GP2 sind die 
//              beiden Endpunkte des gemeinsamen Bereiches
//   BERUE_OHNE Konturinzidenz (Stützpunktgleichheit bzw. Berührung) ohne 
//              Seitenwechsel, betreffender Punkt in GP1, GP2 ist unbestimmt
// i, ii sind Indizes der zu vergleichenden Konturen, j, jj die Indizes der
// Stützpunkte, KonInzOS ist Zähler für Stützpunktwiederholung bzw. Berührung 
// ohne Seitenwechsel
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::isKontInz (WMPunkt<KoOrdT>& AP1, WMPunkt<KoOrdT>& EP1, 
		WMPunkt<KoOrdT>& AP2, WMPunkt<KoOrdT>& EP2, int i, int ii, 
		long j, long jj, long& KonInzOS, 
		WMPunkt<KoOrdT>& GP1, WMPunkt<KoOrdT>& GP2, WMSchnittErg& Fo) const
{
	_ASSERTE(i >= 0);
	_ASSERTE(ii >= 0);
	_ASSERTE(j >= 0);
	_ASSERTE(jj >= 0);

// warum ich am 02.10.98 nachfolgende Routine nehmen wollte, weiß ich nicht 
// mehr; aber heute am 17.11.98 merke ich, daß dies nicht geht; wenn ich bei 
// der Erzeugung von Objekten (z. B. in ObjOper.ext) und den dazugehörigen 
// Tests mit Aufbereitung2 / Aufbereitung / KantenSchnitt / GemeinsamePunkte 
// (...,DoublePair,DoublePair) arbeite, muß ich es hier auch tun, d. h. auch 
// Epsilon-Toleranzen zulassen

//	Fo = GemeinsamePunkte (AP1, EP1, AP2, EP2, GP1, GP2);

DoublePair DP1, DP2;

	Fo = GemeinsamePunkte (AP1, EP1, AP2, EP2, DP1, DP2);     // Fo == KEINE ... UEBERLAPP

	GP1.X() = DtoL(DP1.X());
	GP1.Y() = DtoL(DP1.Y());
	GP2.X() = DtoL(DP2.X());
	GP2.Y() = DtoL(DP2.Y());

// Stützpunktwiederholungen werden immer 4-mal, Berührungspunkte immer doppelt 
// erkannt, wobei nur der Fall GP1 == EP1 && GP1 == EP2 als der einzig 
// relevante angesehen wird
	if ((Fo == RAND || Fo == INNEN) && (GP1 == AP1 || GP1 == AP2)) {
	// nun wohl doch wieder (02.10.98)
		Fo = KEINE;
		return false;
	}

bool ksw = false;	// kein Seitenwechsel (true), sonst false

// Vorarbeiten für Test auf Stützpunktwiederholung bzw. Berührungspunkt
	if (Fo == RAND || Fo == INNEN) {
	WMPunkt<KoOrdT> Pj2, Pjj2;
	double qwj1, qwj2, qwjj1, qwjj2;	// Quasi-Winkel von Strecken mit der Waagrechten

		if (j < _KAF[i].ASP()-2)
			Pj2 = _KAF[i].SP(j+2);
		else
			Pj2 = _KAF[i].SP(1);
		if (jj < _KAF[ii].ASP()-2)
			Pjj2 = _KAF[ii].SP(jj+2);
		else
			Pjj2 = _KAF[ii].SP(1);
			
		qwj1 = QuasiWinkel (GP1.X(), GP1.Y(), AP1.X(), AP1.Y());
		qwjj1 = QuasiWinkel (GP1.X(), GP1.Y(), AP2.X(), AP2.Y());

		if (Fo == RAND) {
		// Stützpunktwiederholung
			qwj2 = QuasiWinkel (GP1.X(), GP1.Y(), Pj2.X(), Pj2.Y());
			qwjj2 = QuasiWinkel (GP1.X(), GP1.Y(), Pjj2.X(), Pjj2.Y());
		}
		else {
		// Bei Berührung muß unterschieden werden, ob Endpunkt von i-Strecke 
		// innerhalb der ii-Strecke liegt (GP1 == SP(j+1) oder Endpunkt von 
		// ii-Strecke innerhalb der i-Strecke (GP1 == SP(jj+1)
			if (EP1.EpsGleich(DP1))	{
				qwj2 = QuasiWinkel (GP1.X(), GP1.Y(), Pj2.X(), Pj2.Y());
				qwjj2 = QuasiWinkel (GP1.X(), GP1.Y(), EP2.X(), EP2.Y());
			}
			else {
				qwj2 = QuasiWinkel (GP1.X(), GP1.Y(), EP1.X(), EP1.Y());
				qwjj2 = QuasiWinkel (GP1.X(), GP1.Y(), Pjj2.X(), Pjj2.Y());
			}
		}

	// Sind zwei Quasi-Winkel gleich, dann ist die diagnostizierte Stützpunkt-
	// wiederholung bzw. Berührung nicht echt, sondern nur ein Endpunkt einer 
	// Konturüberlappung
		if (qwj1 == qwjj1 || qwj1 == qwjj2 || qwj2 == qwjj1 || qwj2 == qwjj2) {
			Fo = KEINE;
			return false;
		}

	double kj, kjj, gj, gjj;	// die kleineren bzw. größeren der beiden j- bzw. jj-Winkel

	// Ermittlung der jeweils kleineren bzw. größeren der beiden j- bzw. jj-Winkel
		if (qwj1 < qwj2) { 
			kj = qwj1; 
			gj = qwj2; 
		}
		else { 
			kj = qwj2; 
			gj =qwj1; 
		}
		if (qwjj1 < qwjj2) { 
			kjj = qwjj1; 
			gjj = qwjj2; 
		}
		else { 
			kjj = qwjj2; 
			gjj =qwjj1; 
		}

	// kein Seitenwechsel (true)
		ksw = (gj < kjj || (kj < kjj && gjj < gj) ||
		       gjj < kj || (kjj < kj && gj < gjj));
	}

// Stützpunktwiederholungen (Fo == RAND) bzw. Berührung (Fo == INNEN) mit 
// Seitenwechsel werden immer als Fehler gemeldet (bleibt Fo = RAND bzw. 
// Fo = INNEN), ohne Seitenwechsel erst dann, wenn dieser Fall wenigstens 
// zweimal aufgetreten ist; dabei wird nicht mehr zwischen Stützpunkt-
// wiederholung und Berührung unterschieden (Fo == BERUE_OHNE). Ist die
// geordnete Folge der Quasi-Winkel zwischen j und jj nicht alternierend, 
// dann liegt Seitenwechsel vor
	if ((Fo == RAND || Fo == INNEN) && ksw) {
		KonInzOS++;
		Fo = BERUE_OHNE;
	}

// eine einzige Konturinzidenz (Stützpunktwiederholung bzw. Berührung ohne 
// Seitenwechsel) ist noch kein Fehler, erst das mehrmalige Auftreten
	if (Fo == KEINE || (Fo == BERUE_OHNE && KonInzOS == 1))
		return false;
	return true;
}

// Test, ob Innenkontur i, die die Außenkontur nicht echt schneidet, außerhalb 
// der Außenkontur liegt (true), sonst false
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::isAussen (int i) const
{
	_ASSERTE(i >= 1);			// Index einer Innenkontur
	_ASSERTE(i < _Size);

	if (_KAF[0].ASP() < 4)		// Außenkontur hat zu wenig Stützpunkte
		return false;

long lCntKi = _KAF[i].ASP();	// Länge der i-ten Kontur

	for (long j = 0; j < lCntKi; j++) {
	WMPosit posLage = _KAF[i].SP(j).Position (&_KAF[0], dGlEps);

		if (INNERH == posLage)
			return false;
		if (AUSSERH == posLage)
			return true;
		if (OFFEN == posLage)	// Außenkontur nicht geschlossen
			return false;
	}

// dieser Progammteil dürfte nur erreicht werden, wenn alle _KAF[i]-Stützpunkte 
// auf der _KAF[0]-Außenkontur liegen; diese Konturinzidenz wurde aber von 
// vornherein ausgeschlossen; mit der Assertion wird der Fall abgefangen, daß 
// die _KAF[i]-Kontur nur aus einem Stützpunkt besteht (entartete Kontur), 
// der genau auf der _KAF[0]-Außenkontur liegt
	_ASSERTE(lCntKi <= 1);
	return false;
}

// Test, ob Kontur i1 (kann auch die Außenkontur sein), die die Innenkontur i2 
// nicht echt schneidet, innerhalb von i2 liegt (true), sonst false
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::isInnen (int i1, int i2) const
{
	_ASSERTE(i1 >= 0);		// Index einer Kontur
	_ASSERTE(i1 < _Size);
	_ASSERTE(i2 >= 1);		// Index einer Innenkontur
	_ASSERTE(i2 < _Size);

	if (_KAF[i2].ASP() < 4)		// i2-Innenkontur hat zu wenig Stützpunkte
		return false;

long lCntKi1 = _KAF[i1].ASP();	// Länge der i1-ten Kontur

	for (long j = 0; j < lCntKi1; j++) {
	WMPosit posLage = _KAF[i1].SP(j).Position (&_KAF[i2]);

		if (INNERH == posLage)
			return true;
		if (AUSSERH == posLage)
			return false;
		if (OFFEN == posLage)	// i2-Innenkontur nicht geschlossen
			return false;
	}

// dieser Progammteil dürfte nur erreicht werden, wenn alle _KAF[i1]-Stützpunkte 
// auf der _KAF[i2]-Kontur liegen; diese Konturinzidenz wurde aber von 
// vornherein ausgeschlossen; mit der Assertion wird der Fall abgefangen, daß 
// die _KAF[i1]-Kontur nur aus einem Stützpunkt besteht (entartete Kontur), 
// der genau auf der _KAF[i2]-Außenkontur liegt
	_ASSERTE(lCntKi1 <= 1);
	return false;
}

// Vereinigung zweier Flächen (this- und pFl-Fläche) mit (bInsel == true) bzw. 
// ohne (bInsel == false) Berücksichtigung der Innenkonturen; wenn
// - beide Flächen keinen oder nur endlich viele Punkte gemeinsam haben
// - sich kein Anfangspunkt für die Außenkontur der vereinigten Fläche finden 
//	 läßt
// - nicht genügend dynamischer Speicher verfügbar ist,
// dann keine Vereinigung möglich (Rückgabe von 0)
template <typename KoOrdT>
inline WMFlaeche<KoOrdT> * 
WMFlaeche<KoOrdT>::FlaechenVereinigung (WMFlaeche* pFl, bool& bAbbr, void* pPSt, 
		bool bInsel)
{
	_ASSERTE(pFl != 0);	// pPSt wird weiter unten getestet

WMObjRechteck<KoOrdT> OC1 (GetCont());		// Container der this-Fläche
WMObjRechteck<KoOrdT> OC2 (pFl->GetCont());	// Container von pFl

// Test, ob beide Container genau 1 Punkt gemeinsam haben. (Der Fall, daß 
// Container völlig durchschnittsleer sind, wird in Aufbereitung2() abgefangen.)
	if (WMPunkt<KoOrdT>(OC1.XMin(), OC1.YMin()) == 
			WMPunkt<KoOrdT>(OC2.XMax(), OC2.YMax()) ||
		WMPunkt<KoOrdT>(OC1.XMax(), OC1.YMin()) == 
			WMPunkt<KoOrdT>(OC2.XMin(), OC2.YMax()) ||
	    WMPunkt<KoOrdT>(OC1.XMin(), OC1.YMax()) == 
			WMPunkt<KoOrdT>(OC2.XMax(), OC2.YMin()) ||
		WMPunkt<KoOrdT>(OC1.XMax(), OC1.YMax()) == 
			WMPunkt<KoOrdT>(OC2.XMin(), OC2.YMin()))
	{
		return 0;
	}

// aus Stützpunktfolge der this-Außenkontur wird Vektor pML1, aus Außenkontur 
// der pFl-Fläche wird Vektor pML2 mit markierten Punkten erzeugt; diese 
// Vektoren werden in Aufbereitung2() evtl. noch erweitert
WMMarkLine<KoOrdT> ML1 (_KAF[0].ASP(), 0);
WMMarkLine<KoOrdT> ML2 (pFl->KA(0).ASP(), 0);

	_ASSERTE(!(!ML1.Vektor() || !ML2.Vektor()));

// Die beiden nachfolgenden Zeilen könnten an vielen Stellen anstatt der 
// new-Definition geschrieben werden. Dann muß aber nach Aufbereitung() noch 
// als Parameter durchgereicht werden, ob es sich um eine echte Kante 
// (pML2 bleibt 0) oder eine Flächenkontur (pML2 wird gesetzt) handelt.
//MarkLine* pML1 = 0;
//MarkLine* pML2 = 0;

bool bLeer;		// Parameter von Aufbereitung2(); wird hier nicht ausgewertet

	if (!_KAF[0].Aufbereitung2 (&pFl->KA(0), &ML1, &ML2, bLeer, bAbbr, pPSt))
		return 0;

// KantenPosit() ermittelt die Position "posLage" der beiden Außenkonturen der 
// this-Fläche und pFl zueinander
bool bOverlap;	// this-Fläche hat mit pFl-Außenkontur einen Überlappungsbereich
int iTouchOut;	// Parameter von KantenPosit(); wird hier nicht ausgewertet
WMPosit posLage = KantenPosit (&pFl->KA(0), &ML1, bOverlap, iTouchOut);
WMFlaeche<KoOrdT> *pVFl = 0;		// Vereinigungsfläche
bool bNew = false;		// pVFl wurde (noch nicht) mit new dynamisch angelegt

	switch (posLage) {
	case INNERH:	// this-Fläche innerhalb von pFl
	case INNERHB:
		if (bInsel)	{	
		// mit Inseln
		WMFlaeche<KoOrdT> *pHF = pFl->FlaechenVereinigung1 (this);

			if (pHF) {
			// FlaechenVereinigung1() hat nicht 0 zurückgeliefert
				pVFl = new WMFlaeche<KoOrdT>(*pHF);
				bNew = true;
			}
		} else		// ohne Inseln
			pVFl = new WMFlaeche<KoOrdT>(*pFl);
		break;

	case UMSCHL:	// pFl innerhalb der this-Fläche
	case UMSCHLB:
	case KONTUR:	// Außenkonturen der this-Fläche und pFl liegen genau übereinander
	case GLEICH:	// Außenkonturen der this-Fläche und pFl liegen genau übereinander
		if (bInsel)	{
		WMFlaeche<KoOrdT> *pHF = FlaechenVereinigung1 (pFl);

			if (pHF) {
			// FlaechenVereinigung1() hat nicht 0 zurückgeliefert
				pVFl = new WMFlaeche<KoOrdT>(*pHF);
				bNew = true;
			}
		} else
			pVFl = new WMFlaeche<KoOrdT>(*this);
		break;

	case AUSSERHB:	// pFl außerhalb der this-Fläche mit Berührung
		if (bOverlap) {
			pVFl = new WMFlaeche<KoOrdT>();
			bNew = true;

			if (!ContourUnion (pML1, pML2, pVFl, bInsel) &&	
				0 == pVFl->KantenAnz())
			{
				DELETE_OBJ (pVFl);
				break;
			}
			if (bInsel)			// blankes Hinzufügen der Innenkonturen
				pVFl->AddInseln1 (this, pFl);
		}
		break;	// anderenfalls ist keine Vereinigung möglich, d. h. pVFl == 0

	case INNAUSS:
	// Aufbau der Außenkontur (und evtl. einiger Innenkonturen) der 
	// Vereinigungsfläche
		pVFl = new WMFlaeche<KoOrdT>();

		if (!ContourUnion (pML1, pML2, pVFl, bInsel) &&
			0 == pVFl->KantenAnz())
		{
			DELETE_OBJ (pVFl);
			break;
		}
		if (bInsel &&		// Inseln (verschnitten) hinzufügen
			(KantenAnz() > 1 || pFl->KantenAnz() > 1))
		{
			pVFl->AddInseln2 (this, pFl);
		}
		break;
	} // switch

// für posLage == AUSSERH bzw. UNKLAR ist keine Vereinigung möglich, d. h. 
// pVFl == 0
	_ASSERTE(!(bNew && !pVFl));
	return pVFl;
}
	
///////////////////////////////////////////////////////////////////////////////
// Definition der virtuellen Funktionen der Basisklasse WMObjekt

// liefert ObjektTyp
template <typename KoOrdT>
inline WMObjTyp 
WMFlaeche<KoOrdT>::isA (void) const
{ 
	return OT_FLAECHE; 
}

// Lage der this-Fläche bezüglich der Fläche pFl; es werden sowohl von der 
// this-Fläche als auch von pFl Inseln mit berücksichtigt, d.h. liegt this-
// Fläche innerhalb einer pFl-Insel, dann liegt this-Fläche außerhalb von pFl 
// sowie umgekehrt
template <typename KoOrdT>
inline WMPosit 
WMFlaeche<KoOrdT>::EnthaltenIn (WMFlaeche* pFl, void* pPSt)
{
	_ASSERTE(pFl != 0);	// pPSt kann 0 sein
	if (!pFl) 
		return UNKLAR;

WMObjRechteck<KoOrdT> OC1 (GetCont());
WMObjRechteck<KoOrdT> OC2 (pFl->GetCont());

	if (!OC1.Durchschnitt (OC2))
		return AUSSERH;		// Container haben keinen Punkt gemeinsam

int iKAnz = pFl->KantenAnz();		// Anzahl der Konturen von pFl
bool bOverlap;		// Parameter von KantenPosit(); werden
int iTouchOut;		// hier nicht ausgewertet
WMPosit posLage;	// Ergebnis der Routine KantenPosit
bool bInnenB = false;	// this-Fläche liegt zur pFl-Außenkontur INNERHB (true) oder nicht
						// (false)
bool bAussenB = false;	// this-Fläche liegt zu mindestens einer pFl-Innenkontur AUSSERHB
						// (true)
bool bLeer;				// Container der beiden in Aufbereitung2() verglichenen Objekte sind
						// durchschnittsleer (true)
bool bAbbr;				// Parameter von Routine Aufbereitung2(); wird hier nicht ausgewertet

// Feld für die Indizes der pFl-Inseln, die noch mit den this-Inseln zu vergleichen sind
int k = 0;	// Laufindex für piInsel
vector<int> piInsel(iKAnz, 0);	

   	for (int i = 0; i < iKAnz; i++)	{	// Test mit allen pFl-Konturen
										// (Außen- und Innenkontur)
	// pML1 muß in die for-Schleife, da dieses Variable in Aufbereitung2() verändert wird
	WMMarkLine ML1 (_KAF[0].ASP(), 0);
	WMMarkLine ML2 (pFl->KA(i).ASP(), i, true);

		_ASSERTE(!(!ML1.Vektor() || !ML2.Vektor()));

		if (!_KAF[0].Aufbereitung2 (&pFl->KA(i), &ML1, &ML2, bLeer, bAbbr, pPSt)) {
		// bLeer == true bedeutet, daß der Container der i-ten pFl-Kontur und 
		// Container der Außenkontur der this-Fläche durchschnittsleer sind. 
		// Für Außenkontur (i == 0) wurde dies schon oben abgefangen. Hier kann 
		// der Fall nur noch bei Innenkonturen auftreten (i > 0). Dabei ist die 
		// Lage noch nicht klärbar.
			if (bLeer) 
				continue;

		// false-Rückgabe von Aufbereitung2() bedeutet Abbruch durch den 
		// Anwender, falsche Parameter oder unzureichender dynamischer Speicher
			return UNKLAR;
		}

		posLage = KantenPosit (&pFl->KA(i), &ML1, bOverlap, iTouchOut);
		if (0 == i) {			// pFl-Außenkontur
		// wird pFl-Außenkontur von this-Außenkontur umschlossen bzw. wenn beide
		// Außenkonturen identisch sind, muß (wenn vorhanden) noch Test mit
		// this-Innenkonturen durchgeführt werden
			if (UMSCHL == posLage || UMSCHLB == posLage ||
				KONTUR == posLage ||		// 16.06.98
				GLEICH == posLage)			// 15.04.99
			{
				break;
			}	

		// Test mit pFl-Innenkonturen (i > 0) nur erforderlich, wenn der Test 
		// mit der pFl-Außenkontur posLage == INNERH oder posLage == INNERHB 
		// ergeben hat
			if (INNERH != posLage && INNERHB != posLage) 
				return posLage;

			if (INNERHB == posLage)
				bInnenB = true;
		}
			
		if (i > 0) {		// pFl-Innenkonturen wurden noch mit herangezogen
		// für INNERH, INNERHB, INNAUSS, KONTUR, GLEICH und UNKLAR ist alles klar
			if (INNERH == posLage || INNERHB == posLage || INNAUSS == posLage ||
				KONTUR == posLage || GLEICH == posLage || UNKLAR == posLage)
			{
				if (INNERH == posLage)	// vollständig innerhalb einer pFl-Insel 
					return AUSSERH;		//  heißt außerhalb der pFl-Fläche
				if (INNERHB == posLage)	// innerhalb der pFl-Außenkontur, aber bez. einer
					return AUSSERHB;	//  pFl-Insel INNERHB bedeutet AUSSERHB
				if (KONTUR == posLage)	// vollständig auf einer pFl-Insel heißt 
					return AUSSERHB;	//  AUSSERHB bez. der pFl-Fläche (16.07.98)
				return posLage;
			}
				
		// für AUSSERH, AUSSERHB, UMSCHL bzw. UMSCHLB der this-Außenkontur bez. 
		// einer pFl-Insel ist posLage noch nicht eindeutig klärbar
			if (AUSSERHB == posLage)
				bAussenB = true;

			if (UMSCHL == posLage || UMSCHLB == posLage) {	// 16.10.98
				piInsel[k] = i;
				k++;
			}
		}
	} // for
	
// dieser Programmteil wird nur erreicht, wenn
// 1. this- und pFl-Außenkontur identisch sind
// 2. this-Fläche innerhalb der pFl-Außenkontur liegt
//    a) und bez. aller pFl-Innenkonturen AUSSERH bzw. AUSSERHB gilt;
//       dann gilt bez. der pFl-Außenkontur INNERHB (bInnenB == true) oder bez. 
//       der pFl-Innenkonturen mindestens einmal AUSSERHB (bAussenB == true), 
//       dann gilt bez. der gesamten pFl-Fläche INNERHB, sonst INNERH
//    b) und bez. der pFl-Innenkonturen mindestens einmal UMSCHL bzw. UMSCHLB 
//       gilt; dann gilt
//       INNERH,  wenn zu allen diesen pFl-Innenkonturen mit UMSCHL auch this-
//                Innenkonturen mit UMSCHL existieren
//       INNERHB, wenn UMSCHLB bzw. KONTUR
//       INNAUSS  in allen übrigen Fällen
// 3. pFl-Fläche innerhalb der this-Außenkontur liegt (i == 0 und posLage == 
//    UMSCHL oder UMSCHLB); dann ist die gleiche Prozedur zwischen pFl->KA(0) 
//    und allen Innenkonturen der this-Fläche durchzuführen (so die this-Fläche 
//    überhaupt Innenkonturen besitzt), innerhalb derer ja die pFl-Fläche 
//	  liegen könnte
	
// >>>>> 1. Fall: this- und pFl-Außenkontur sind identisch
	if (0 == i && (KONTUR == posLage || GLEICH == posLage))	
		return BeideAussenkonturenIdentisch (pFl, iKAnz);
	
// >>>>> 2. Fall: this-Fläche innerhalb der pFl-Außenkontur
	if (i > 0 || (UMSCHL != posLage && UMSCHLB != posLage)) {
		if (0 == piInsel[0]) {	// 19.10.98
			if (bAussenB || bInnenB)
				return INNERHB;
			return INNERH;
		}

	// noch weitere Tests mit den this-Innenkonturen (so sie vorhanden sind)
		if (_Size > 1)
			posLage = EnthaltenInWeiter (pFl, piInsel.begin());
		return posLage;
	}

// >>>>> 3. Fall: pFl-Fläche innerhalb der this-Außenkontur
	if (1 == _Size)		// this-Fläche hat keine Innenkonturen
		return posLage;
		
	if (UMSCHL == posLage)
		bInnenB = false;
	else	// posLage == UMSCHLB
		bInnenB = true;

// da die this-Außenkontur die pFl-Fläche umschließt, gibt es für die Lage der 
// this-Fläche bezüglich der pFl-Fläche nur noch die beiden Möglichkeiten:
// - AUSSERH bzw. AUSSERHB, wenn die pFl-Fläche vollständig innerhalb einer 
//	 this-Insel liegt
// - INNAUSS ansonsten
   	for (i = 1; i < _Size; i++)	{	// Test mit allen this-Innenkonturen reicht 
									// aus, da schon klar ist, daß pFl-Fläche 
									// innerhalb der this-Außenkontur liegt
	WMMarkLine ML1 (pFl->KA(0).ASP(), 0);
	WMMarkLine ML2 (_KAF[i].ASP(), i, true);

		_ASSERTE(!(!ML1.Vektor() || !ML2.Vektor()));
		if (!pFl->KA(0).Aufbereitung2 (&_KAF[i], &ML1, &ML2, bLeer, bAbbr, 0)) {
		// bLeer == true bedeutet, daß der Container der i-ten this-Kontur und 
		// Container der pFl-Außenkontur durchschnittsleer sind. Bei den hier 
		// nur noch herangezogenen Innenkonturen (i > 0) ist die Lage noch 
		// nicht klärbar.
			if (bLeer) 
				continue;

		// false-Rückgabe von Aufbereitung2() bedeutet Abbruch durch den 
		// Anwender, falsche Parameter oder unzureichender dynamischer Speicher
			return UNKLAR;
		}

		posLage = KantenPosit (&_KAF[i], &ML1, bOverlap, iTouchOut);

	// für INNERH, INNERHB, INNAUSS, KONTUR, GLEICH, UMSCHL, UMSCHLB und UNKLAR 
	// ist alles klar
		if (INNERH == posLage || INNERHB == posLage || INNAUSS == posLage || 
			KONTUR == posLage || GLEICH == posLage || UMSCHL == posLage || 
			UMSCHLB == posLage || UNKLAR == posLage)
		{
		// vollständig innerhalb einer this-Insel heißt außerhalb der this-Fläche
			if (INNERH == posLage)
				return AUSSERH;

		// innerhalb der this-Außenkontur, aber bez. einer this-Innenkontur INNERHB bzw.
		// mit dieser vollständig deckungsgleich (KONTUR oder GLEICH) bedeutet AUSSERHB
			if (INNERHB == posLage ||
				KONTUR == posLage ||		// 16.06.98
				GLEICH == posLage)			// 15.04.99
			{
				return AUSSERHB;
			}

		// eine this-Innenkontur umschließen heißt INNAUSS bez. der this-Fläche
			if (UMSCHL == posLage || UMSCHLB == posLage)
				return INNAUSS;
			return posLage;
		}
	}
	return INNAUSS;
}

// Inseln bei Schnittoperationen der this-Fläche mit pSFl-Schnittfläche 
// berücksichtigen 
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::InselnBeiSchnittMitFlaeche (WMFlaeche* pSFl, 
	WMClipListe<KoOrdT>& CL, int iSkip)
{
	_ASSERTE(pSFl != 0);

bool bRet;
int iKAnz = pSFl->KantenAnz();	// Anzahl der pSFl-Konturen

	if (_Size > 1) {			// this-Fläche hat Inseln
		if (iKAnz == 1)			// nur this-Fläche hat Inseln
			bRet = InselnBeiSchnittMitKante (CL, iSkip);	// this-Inseln berücksichtigen
		else {				// beide Flächen mit Inseln
		bool bModify1 = true;	// an mindestens einer CL-Fläche wurden durch die this-Inseln
		bool bModify2 = true;	//  bzw. die pSFl-Inseln Veränderungen vorgenommen (true)
		bool bRet1 = true;
		bool bRet2 = true;

		// Felder für die Indizes der Inseln, die schon "verbraucht" wurden
		int iKAnz2 = pSFl->KantenAnz();
		vector<int> piVbInsel1(_Size, 0);
		vector<int> piVbInsel2(iKAnz2, 0);

			if (!InselnAmRand (CL, iSkip, piVbInsel1.begin(), bModify1))
				bRet1 = false;
			if (!pSFl->InselnAmRand (CL, iSkip, piVbInsel2.begin(), bModify2))
				bRet2 = false;

		// durch das "Ankabbern" mit den pSFl-Inseln können wieder this-Inseln 
		// die Außenkontur der CL-Fläche "anknabbern" wollen, usw.
			while (bModify2) {
				if (!InselnAmRand (CL, iSkip, piVbInsel1.begin(), bModify1))
					bRet1 = false;
				if (bModify1) {
					if (!pSFl->InselnAmRand (CL, iSkip, piVbInsel2.begin(), bModify2))
						bRet2 = false;
				} else
					bModify2 = false;
			}

		bool bRet3 = InselnInnerhalb (CL, iSkip, piVbInsel1.begin());
		bool bRet4 = pSFl->InselnInnerhalb (CL, iSkip, piVbInsel2.begin());

			bRet = bRet1 && bRet2 && bRet3 && bRet4;
		}
	}
	else {	// this-Fläche hat keine Inseln
		if (iKAnz == 1) 
			return true;	// beide Flächen ohne Inseln

		bRet = pSFl->InselnBeiSchnittMitKante (CL, iSkip);	// pSFl-Inseln berücksichtigen
	}
	return bRet;
}

// Inseln der this-Fläche, die innerhalb EINER (!) in CL enthaltenen 
// Schnittfläche liegen, bei Schnittoperationen mit Schnittkante berücksichtigen; 
// die ersten iSkip Einträge in CL sind dabei zu übergehen
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::InselnInnerhalb (WMClipListe<KoOrdT>& CL, int iSkip, 
	int* piVbInsel)
{
// piVbInsel kann 0 sein (bei Schnittergebnis "außerhalb")
	if (1 == _Size) 
		return true;	// keine Inseln vorhanden

// in CL sind jetzt die durch am Rand liegende Inseln "angeknabberten" 
// Teilflächen enthalten; diese sind noch mit den echten Inseln zu 
// komplettieren (die ersten iSkip Einträge aus CL wieder übergehen)
WMClipListe<KoOrdT>::iterator ri = CL.begin();

	_ASSERTE(iSkip >= 0 && iSkip < CL.size());	// wenigstens einer muß noch da sein
	advance(ri, iSkip);

bool bOverlap;	// Teilfläche hat mit dem Rand einer this-Insel einen Überlappungsbereich bzw.
int iTouchOut;	// iTouchOut Berührungspunkte mit "Zuführung" aus der _KAF[i]-Umgebung gemeinsam
WMClipListe<KoOrdT>::iterator end = CL.end();

	for (/**/; ri != end; ++ri) {
	// alle Teilflächen aus CL
		if (OT_KANTE == (*ri)->isA())
			continue;

	WMFlaeche<KoOrdT> *pTF = (WMFlaeche<KoOrdT> *)(*ri);

		PartialCleaningForLines (&pTF->KA(0), -1);	// 09.02.99
		for (int i = 1; i < _Size; i++)	{
		// alle Inseln, die noch nicht verbraucht sind 
		bool bVerbr = false;	// Insel noch nicht verbraucht

			if (piVbInsel) {	// piVbInsel == 0 bei Schnittergebnis "außerhalb"
				for (int j = 0; j < _Size-1; j++) {
					if (piVbInsel[j] == i) {
						bVerbr = true;	// diese Insel wurde schon verarbeitet
						break;
					}
					if (piVbInsel[j] == 0) 
						break;
				}
				if (bVerbr) 
					continue;
			}

		// aus Stützpunktfolge der Außenkontur der ml-Teilfläche wird Vektor 
		// pML1, aus _KAF[i]-Insel wird Vektor pML2 mit markierten Punkten 
		// erzeugt; diese Vektoren werden in LageKonturZuKontur() durch 
		// Aufbereitung2() evtl. noch erweitert
		WMMarkLine ML1 (pTF->KA(0).ASP(), 0);
		WMMarkLine ML2 (_KAF[i].ASP(), i, true);

			_ASSERTE(!(!ML1.Vektor() || !ML2.Vektor()));

		// Lage der this-Inseln bez. der Außenkontur der Teilflächen aus CL bestimmen
		WMPosit posLage = pTF->KA(0).LageKonturZuKontur (&_KAF[i], &ML1, &ML2, 
			bOverlap, iTouchOut);

			if (UMSCHL == posLage ||	// UMSCHL statt INNERH, da Inseln math.neg. orientiert sind
				(UMSCHLB == posLage && !bOverlap && iTouchOut <= 1))
			{
				if (1 == pTF->KantenAnz())	// 1. Insel hinzufügen (08.02.99)
					pTF->AddKante (WMFlaeche<KoOrdT>(&_KAF[i], 1), 1, -1);
				else				// weitere Inseln mit den schon vorhandenen Inseln abtesten
					pTF->InselZweiteFlaeche (CL, &_KAF[i], i);
			}
		}
	} // for
	return true;
}

// Aufbau der Außenkontur der Vereinigungsfläche pVFl (und für bInsel == true 
// Innenkonturen, die durch konkave Stellen bei pML1 bzw. pML2 enstehen können) 
// bei Vereinigung zweier geschlossener Konturen, die durch die Vektoren pML1 
// und pML2 gegeben sind; schon vorhandene Innenkonturen der Ausgangsflächen 
// werden hier nicht berücksichtigt
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::ContourUnion (WMMarkLine* pML1, WMMarkLine* pML2, 
	WMFlaeche* pVFl, bool bInsel)
{
	_ASSERTE(pML1 != 0);
	_ASSERTE(pML2 != 0);
	_ASSERTE(pVFl != 0);

//double dUmlauf;		// Umlaufsinn einer Kontur der vereinigten Fläche
long lAI = 0;			// Anfangsindex für Suche nach Anfangspunkt einer Kontur
WMMar1 mark;			// Markierung
long lNewSize1 = pML1->ADP();
long lNewSize2 = pML2->ADP();
bool bRest;				// nach Verlassen der do-Schleife ist die soeben aufgebaute Kontur noch
						//  durch einen restlichen Teil zu ergänzen

int iKInd1 = pML1->GetKInd();		_ASSERTE(iKInd1 >= 0);
int iKInd2 = pML2->GetKInd();		_ASSERTE(iKInd2 >= 0);
bool bMax;		// SEHR wichtiger Parameter von EckeMitBeruehrung()

	if (0 == iKInd1 && 0 == iKInd2)
		bMax = false;
	else if (0 == iKInd1 && iKInd2 > 0)
		bMax = true;
	else if (iKInd1 > 0 && 0 == iKInd2) {
		_ASSERTE(false);	// nur zu Testzwecken, da
		bMax = false;	// diesen Fall hatte ich noch nicht
	} else	// if (iKInd1 > 0 && iKInd2 > 0)
		bMax = true;	// 29.10.98

bool bWechsel;	// bei BERUE_UMG ist bei pML2 fortzusetzen (true); wird durch
				// EckeMitBeruehrung() gesetzt
bool bAussen;	// pML1 und pML2 sind beide aus Außen- (true) bzw. Innenkonturen (false)
				// entstanden

	if (0 == iKInd1 && 0 == iKInd2)
		bAussen = true;
	else if (iKInd1 > 0 && iKInd2 > 0) {
		bAussen = false;
		_ASSERTE(!bInsel);	// sonst könnte "Insel in Insel" entstehen (28.05.99)
	} else {
		_ASSERTE(false);
	}

// for-Schleife wird mehrfach durchlaufen, wenn bei der Vereinigung durch 
// konkave Stellen auch Innenkonturen entstehen
	for (;;) {
	// Suche nach einem Punkt der pML1-Kontur, so daß die folgende Strecke noch
	// "unverbraucht" ist und der anschließende Teil der pML1-Kontur außerhalb 
	// der pML2-Kontur liegt, um dort mit dem Aufbau einer Kontur der 
	// vereinigten Fläche zu beginnen, da es sein kann, daß der bisherige 
	// Anfangspunkt der pML1-Kontur durch die Vereinigung innerhalb der 
	// vereinigten Fläche liegt und somit nicht mehr verwendbar ist; dazu wird 
	// getestet, wo der Mittelpunkt (!) der einzelnen Strecken der pML1-Kontur 
	// bez. der um die Schnittpunkte erweiterten pML2-Kontur liegt.
		for (long i = lAI; i < lNewSize1-1; i++) {
			if (UNVERBR == pML1->GetMk2(i) &&		// noch "unverbrauchte" Strecke
				AUSSERH == pML2->Position (pML1, i))
				break;  // geeigneter Punkt gefunden
		}

		if (i == lNewSize1-1) {	
		// alle this-Strecken abgearbeitet
			_ASSERTE(0 != pVFl->KantenAnz());	// kein geeigneter Anfangspunkt gefunden
			return false;
		}

		lAI = (i < lNewSize1-2) ? i + 1 : 0;

	// punktweiser Aufbau einer Kontur pKVFl der vereinigten Fläche, zuerst mit 
	// Punkten der this-Außenkontur
	KoOrdT x = DtoL (pML1->x(i));
	KoOrdT y = DtoL (pML1->y(i));
	WMFlaeche<KoOrdT> KVFl (&x, &y, 1); // Anfang einer Kontur der Vereinigungsfläche
	WMPunkt<KoOrdT> PA (x, y);			// Anfangspunkt einer Kontur der Vereinigungsfläche
	long lAnfId1 = lAI;	// Anfangsindex für den Teil der Kontur, der aus pML1 übernommen wird

		do {      // weiterer Aufbau einer Kontur der vereinigten Fläche
			bRest = true;
			pML1->ModMark2 (i, VERBR);       // Strecke (pML1[i], pML1[i+1] "verbraucht"
			i = (i < lNewSize1-2) ? i + 1 : 0;

		// aktueller Punkt pML1[i] ist Schnittpunkt (SCHNITT) oder Endpunkt mit
		// "Zuführung" aus der Umgebung der pML2-Fläche (RAND_UMG), dann pKVFl 
		// mit Punkten von pFl ergänzen
			mark = pML1->GetMk1(i);
			if (BERUE_UMG == mark)
				pML1->EckeMitBeruehrung (pML2, i, MOVEDIR_UP, MOVEDIR_UP, 
					bMax, bWechsel);

			if (PA != pML1->DP(i) &&
				(SCHNITT == mark || RAND_UMG == mark ||
				 (BERUE_UMG == mark && bWechsel)))
			{
			// Teil der Kontur von pML1 an pKVFl anhängen
				KVFl.KA(0).AddKonturTeil (pML1, lAnfId1, i, -1);
				if (PA == pML1->DP(i))
					break;	// 13.10.98
				KVFl.ZweiteFlaeche (pML1, pML2, i);	// pKVFl mit Punkten von pML2 ergänzen

				lAnfId1 = (i < lNewSize1-2) ? i + 1 : 0;
				bRest = false;
			}
		} while (PA != pML1->DP(i));		// Abbruch, wenn Kontur geschlossen

	// restlichen Teil an pKVFl anhängen, wenn in der do-Schleife noch 
	// Stützpunkte gesammelt wurden, die jedoch mit AddKonturTeil noch nicht 
	// an die Kontur angefügt wurden; bRest == false, wenn unmittelbar nach 
	// dem Aufruf der Routine SpezAddPunkt() die do-Schleife mit geschlossener 
	// Kontur beendet wurde
		if (bRest)
			KVFl.KA(0).AddKonturTeil (pML1, lAnfId1, i, -1);

	// Da es möglich ist, daß durch die Eps-Arithmetik der Anfangs- und 
	// Endpunkt nur eps-gleich sind, werden beide Punkte vorsichtshalber völlig 
	// identisch gemacht.
	long lSPAnz = KVFl.KA(0).ASP();
		
		KVFl.KA(0).SPV(lSPAnz-1) = PA;

	// 28.05.99
	// Vereinigung zweier Außenkonturen
		if (bAussen) {
		// Ermittlung des Umlaufsinns der neu erzeugten Kontur
		double dUmlauf = KVFl.KA(0).PolygonArea();

		// es wurde eine Außenkontur erzeugt, die "vorn" anzufügen ist
			if (dUmlauf > 0.) {
				pVFl->AddKante (KVFl, 1, 0);

			// wenn keine Inseln gefordert sind, kann nach Aufbau der 
			// Außenkontur die Suche nach weiteren "unverbrauchten" Strecken 
			// abgebrochen werden
				if (!bInsel)	
					lAI = lNewSize1-1;
			}
			else if (dUmlauf < 0.) {
			// es wurde eine Innenkontur erzeugt, die "hinten" anzufügen ist
				pVFl->AddKante (KVFl, 1, -1);
			}
			_ASSERTE(dUmlauf != 0.);	// es wurde "etwas" erzeugt
		}
		else {
		// Vereinigung zweier Innenkonturen (hier kann das Ergebnis nur die 
		// Außenkontur von pKVFl sein
			pVFl->AddKante (KVFl, 1, 0);
		}
	} // for
	return true;
}

// Es wird ein Punkt zurückgegeben, der garantiert innerhalb der this-EFlaeche 
// liegt.
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::InneliegenderPunkt (double& dInX, double& dInY)
{
// zuerst wird getestet, ob der Mittelpunkt des umschließenden Rechtecks innerhalb der
// this-EFlaeche liegt
WMObjRechteck<KoOrdT> OC (GetCont());

	dInX = (OC.XMax() + OC.XMin()) / 2.;	// Mittelpunkt des umschließenden
	dInY = (OC.YMax() + OC.YMin()) / 2.;	// Rechtecks

WMPunkt<KoOrdT> MP (DtoL(dInX), DtoL(dInY));

	if (INNERH == MP.EnthaltenIn (this))
		return true;	// liegt innerhalb

// klappt das noch nicht, wird durch den Mittelpunkt (dInX, dInY) eine 
// waagerechte Testkante TKt gelegt, welche mit den Flächenkonturen geschnitten 
// wird; von den ECHTEN Schnittpunkten werden die beiden mit den kleinsten 
// x-Koordinaten gesucht; der Mittelpunkt zwischen diesen beiden Schnittpunkten 
// muß mit Wahrscheinlichkeit 1 innerhalb der this-EFlaeche liegen
double dTestY = dInY;
double dSchrittY = OC.YMax() - OC.YMin();
KoOrdT x[2] = { -std::numeric_limits<double>::max, std::numeric_limits<double>::max };
KoOrdT y[2] = { DtoL(dTestY), DtoL(dTestY) };
WMKante<KoOrdT> TKt (x, y, 2);	// waagrechte Testkante (aus 1 Strecke bestehend) durch den
						// Mittelpunkt des umschließenden Rechtecks
DoublePair ZPA, ZPE;	// evtl. gemeinsame Punkte der Testkante mit den Strecken der
						// Flächenkonturen
double xs1 = std::numeric_limits<double>::max,	// die beiden kleinsten x-Koordinaten von allen
	   xs2 = std::numeric_limits<double>::max;	// Schnittpunkten der Flächenkonturen mit der waagrechten Testkante

int iKAnz = KantenAnz();
int i = 0;
long j = -1;

	do {
	long lCSize = _KAF[i].ASP();

		do {
			j++;

			if (!Intersection (_KAF[i].SP(j).X(), _KAF[i].SP(j).Y(),
					_KAF[i].SP(j+1).X(), _KAF[i].SP(j+1).Y(), TKt.SP(0).X(),
					TKt.SP(0).Y(), TKt.SP(1).X(), TKt.SP(1).Y()))
			{
				continue;       // die beiden Strecken haben keinen Punkt gemeinsam
			}

		WMSchnittErg Fo = _KAF[i].KantenSchnitt (&TKt, j, 0, ZPA, ZPE);

		// Überlappungen und die Berührung einer Innenkontur mit der Außenkontur 
		// machen an dieser Stelle Probleme, deshalb wird die waagrechte 
		// Testkante etwas parallel verschoben
			if (UEBERLAPP == Fo ||
				((ECHT == Fo || INNEN_MIT == Fo || RAND_MIT == Fo) && i > 0 && 
				xs1 == ZPA.X()))
			{
				if (dTestY + dSchrittY < OC.YMax())
					dTestY += dSchrittY;
				else {
					dTestY = (dTestY + OC.YMin()) / 2.;
					dSchrittY /= 2.;
				}

				TKt.SP(0).Y() = TKt.SP(1).Y() = DtoL(dTestY);
				xs1 = xs2 = std::numeric_limits<double>::max;
				i = -1;
				break;
			}
			else if (ECHT == Fo || INNEN_MIT == Fo || RAND_MIT == Fo) {
				if (ZPA.X() < xs1) {
					xs2 = xs1;
					xs1 = ZPA.X();
				}
				else if (ZPA.X() < xs2) 
					xs2 = ZPA.X();
			}
		} while (j < lCSize - 2);
		i++;
		j = -1;
	} while (i < iKAnz);

	_ASSERTE(xs1 < std::numeric_limits<double>::max);
	_ASSERTE(xs2 < std::numeric_limits<double>::max);

	dInX = (xs2 + xs1) / 2.;
	dInY = dTestY;

	MP.X() = DtoL (dInX);
	MP.Y() = DtoL (dInY);

	if (INNERH == MP.EnthaltenIn (this))
		return true;

	_ASSERTE(false);
	return false;
}

// Memberfunktionen von GeoFlaeche

// Clipping für Fläche: pSO schneidet this-Fläche und erzeugt dabei evtl. 
// mehrere Teilflächen, die in CL eingetragen werden;
// Wird this-Fläche geschnitten, wird true zurückgegeben, sonst false;
// bAbbr = true, wenn Schnittoperation abgebrochen wurde, sonst false
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::Clipping (WMObjekt<KoOrdT> *pSO, int iOT, 
	unsigned long ulLageAusw, WMClipListe<KoOrdT>& CL, int iSkip, 
	WMPosit& posLage, bool& bAbbr, void* pPSt)
{
	_ASSERTE(pSO != 0);	// pPSt kann 0 sein

	bAbbr = false;
	if (!pSO) 
		return false;

	switch (iOT) {
	case OT_KANTE:
		return ClippingMitKante ((WMKante<KoOrdT> *)pSO, CL, iSkip, bAbbr, pPSt);

	case OT_FLAECHE:
		return ClippingMitFlaeche ((WMFlaeche<KoOrdT> *)pSO, ulLageAusw, CL, 
			iSkip, posLage, bAbbr, pPSt);

	default:
		_ASSERTE(false);
		return false;	// kein zulässiger Objekttyp
	}
}

// Eintrag einer (Teil)Fläche in die ClipListe; liefert true zurück, wenn 
// Eintrag möglich war, sonst false
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::AddClipObjekt (WMClipListe<KoOrdT>& CL)
{
#if defined(_DEBUG)
	for (int i = 0; i < _Size; i++) {
		_ASSERTE(_KAF[i].ASP() >= 4);
	}
#endif // defined(_DEBUG)

	_ASSERTE(_Size >= 2);
	CL.insert(*this);
	return true;
}

// Inseln bei Schnittoperationen der zu schneidenden this-Fläche mit der 
// schneidenden pSFl-Fläche berücksichtigen, für den Fall, daß für 
// Schnittergebnis "außerhalb" gewählt wurde
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::InselnBeiSchnittMitFlaecheAUSS (WMFlaeche* pSFl, 
	WMClipListe<KoOrdT>& CL, int iSkip)
{
	_ASSERTE(pSFl != 0);

bool bRet1 = true;
bool bRet2 = true;

	if (_Size > 1) {		// zu schneidende this-Fläche hat Inseln
	bool bModify1 = false;	// an mindestens einer CL-Fläche wurden durch die this-Inseln
							// Veränderungen vorgenommen (true)
	vector<int> piVbInsel1(_Size, 0);

		if (!InselnAmRand (CL, iSkip, piVbInsel1.begin(), bModify1))
			bRet1 = false;

	// letzter Parameter "false", da schon Inseln vorhanden sein können (für 
	// den Fall, daß schneidende Fläche innerhalb der zu schneidenden liegt)
		if (!InselnInnerhalb (CL, iSkip))
			bRet1 = false;
	}

	if (pSFl->KantenAnz() > 1) {	// schneidende pSFl-Fläche hat Inseln
	// Test, wie die pSFl-Inseln zu der zu this-Fläche liegen
		bRet2 = InselZweiteFlaecheAUSS (pSFl, CL);
	}
	return bRet1 && bRet2;
}

// gemeinsame Konturabschnitte zweier Flächen werden in CL als Kanten 
// bereitgestellt (true); in posLage wird die Lage der beiden Flächen 
// zueinander angezeigt; gibt es keine gemeinsamen Konturabschnitte bzw. bei 
// unzureichendem dynamischen Speicher, wird false zurückgegeben
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::KonturGemeinsamkeiten (WMFlaeche* pFl, 
	unsigned long ulLageAusw, WMClipListe<KoOrdT>& CL, bool& bAbbr, void* pPSt)
{
	_ASSERTE(pFl != 0);	// pPSt kann 0 sein

WMPosit posLage = EnthaltenIn (pFl);

// keine Berührung bzw. nicht erfüllte Auswahlbedingung
bool b1 = (INNERHB == posLage || KONTUR == posLage || GLEICH == posLage) && (ulLageAusw & LINN);
bool b2 = (AUSSERHB == posLage) && (ulLageAusw & LAUSS);
bool b3 = (UMSCHLB == posLage || INNAUSS == posLage) && (ulLageAusw & LINAU);

	if (!b1 && !b2 && !b3)
		return false;

bool bRet = false;		// return-Wert dieser Routine
int iKontAnz = pFl->KantenAnz();
bool bOverlap;	// this-Fläche hat mit einer pFl-Kontur einen Überlappungsbereich bzw.
int iTouchOut;	// Parameter von KantenPosit(); wird hier nicht ausgewertet
bool bLeer;		// Parameter von Aufbereitung2(); wird hier nicht ausgewertet
long lNInd;		// der auf einen Anfangsindex folgende Index eines Konturabschnittes

	for (int i = 0; i < _Size; i++) {				// jede Kontur der this-Fläche mit
		for (int ii = 0; ii < iKontAnz; ii++) {	//  jeder Kontur der pFl-Fläche vergleichen
		// aus Stützpunktfolge einer this-Kontur wird Vektor pML1 mit markierten Punkten
		// erzeugt; dieser Vektor wird in Routine Aufbereitung2() evtl. noch erweitert
		WMMarkLine ML1 (_KAF[i].ASP(), i);
		WMMarkLine ML2 (pFl->KA(ii).ASP(), ii);

			_ASSERTE(!(!ML1.Vektor() || !ML2.Vektor()));
			if (!_KAF[i].Aufbereitung2 (&pFl->KA(ii), &ML1, &ML2, bLeer, bAbbr, pPSt))
				continue;

		// Routine KantenPosit() ermittelt, ob die beiden Konturen einen
		// Überlappungsbereich haben
			posLage = KantenPosit (&pFl->KA(ii), &ML1, bOverlap, iTouchOut);
			if (!bOverlap) 
				continue;	// kein Überlappungsbereich
														  
		// Bilden der gemeinsamen Konturabschnitte														  
		long lVekL1 = ML1.ADP();

			// zuerst wird der Spezialfall getestet, ob es nur INNERHALB-Punkte gibt
			for (long j = 0; j < lVekL1; j++) {
				if (ML1.GetMk1(j) != INNERHALB) 
					break;
			}

			if (j == lVekL1) {	// alle Punkte tragen Markierung INNERHALB
			KoOrdT x = DtoL (ML1.x(0));
			KoOrdT y = DtoL (ML1.y(0));
			WMKante<KoOrdT> GK (&x, &y, 1);	// gemeinsamer Konturabschnitt
			
				GK.AddKonturTeil (&ML1, 1, lVekL1-1, -1);	// Rest von pML1 an pGK anhängen
				GK.AddClipObjekt (CL);					// Konturabschnitt in CL speichern
				continue;
			}

		// sonst den Normalfall abhandeln
		long lAInd1 = -1;		// 1. Anfangsindex eines Konturabschnittes
		bool bAufbau = false;	// Konturabschnitt ist aktuell (nicht) im Aufbau (true/false)
		WMKante<KoOrdT> GK;		// gemeinsamer Konturabschnitt

			j = 0;	// Laufindex von pML1
			do {
			WMMar1 mark11 = ML1.GetMk1(j);
		
				if (!bAufbau) {	// kein Konturabschnitt aktuell im Aufbau
					if (mark11 == RAND_INN || mark11 == RAND_UMG) {
					long k;			// der auf j folgende Index

						if (j < lVekL1-2) 
							k = j + 1;
						else 
							k = 0;
						mark11 = ML1.GetMk1(k);

					// bei nachfolgender Bedingung wurde das Ende eines Konturabschnitts erwischt
						if (mark11 != INNERHALB && mark11 != RAND_INN && mark11 != RAND_UMG) {
							do {
								j = (j > 0) ? j - 1 : lVekL1-2;	// 31.12.98
								mark11 = ML1.GetMk1(j);
							} while (mark11 != RAND_INN && mark11 != RAND_UMG);
						}

					// Anfang eines Konturabschnitts
					KoOrdT x = DtoL (ML1.x(j));
					KoOrdT y = DtoL (ML1.y(j));

						GK = WMKante<KoOrdT>(&x, &y, 1);
						lNInd = (j < lVekL1-2) ? j + 1 : 0;
						if (lAInd1 == -1) 
							lAInd1 = j;				// 1. Anfangsindex merken
						bAufbau = true;
					}
				}
				else {
				// Konturabschnitt aktuell im Aufbau
					if (mark11 == RAND_INN || mark11 == RAND_UMG) {
						GK.AddKonturTeil (&ML1, lNInd, j, -1);	// Teil von pML1 an pGK anhängen
						GK.AddClipObjekt (CL);					// Konturabschnitt in CL speichern
						bAufbau = false;
					}
				}
				j = (j < lVekL1-2) ? j + 1 : 0;
			} while (j != lAInd1);
		} // for/for
	}
	return true;
}

// Hilfsroutine für InselnInnerhalb(); zu der this-Fläche mit Inseln wird als 
// zusätzliche Insel pKont hinzugenommen, dabei sind evtl. Überschneidungen mit 
// den this-Inseln zu berücksichtigen
template <typename KoOrdT>
inline bool 
WMFlaeche<KoOrdT>::InselZweiteFlaeche (WMClipListe<KoOrdT>& CL, 
	WMKante<KoOrdT> * pKont, int iKInd)
{
	_ASSERTE(pKont != 0);

// Insel nach möglicherweise mehreren Vereinigungen
WMFlaeche<KoOrdT> *pNewIsland = new WMFlaeche<KoOrdT>(pKont, 1);

	if (1 == _Size)	{
	// this-Fläche hat keine Inseln
		AddKante (*pNewIsland, 1, -1);	// neue Insel einfach so hinzufügen
		DELETE_OBJ (pNewIsland);
		return true;
	}

// Abarbeitung aller this-Inseln, d.h. aller Inseln der 1. Fläche, die 
// innerhalb der Teilfläche liegen und dieser schon zugeordnet sind
bool bOverlap;	// pNewIsland hat mit dem Rand einer this-Insel einen 
				// Überlappungsbereich
int iTouchOut;	// Parameter von LageKonturZuKontur(); wird hier nicht 
				// ausgewertet

	for (int i = 1; i < _Size; i++) {
	WMMarkLine ML1 (pNewIsland->KA(0).ASP(), iKInd, true);	// 16.03.99
	WMMarkLine ML2 (_KAF[i].ASP(), i, true);

		_ASSERTE(!(!ML1.Vektor() || !ML2.Vektor()));

	// Lage der (vereinigten) Insel pNewIsland zur this-Insel _KAF[i]
	WMPosit posLage = pNewIsland->KA(0).LageKonturZuKontur (&_KAF[i], &ML1, 
		&ML2, bOverlap, iTouchOut);	// 16.03.99

//		if (INNAUSS != posLage && AUSSERHB != posLage) {
//			DELETE_OBJ (pML1); DELETE_OBJ (pML2);
//		}

		switch (posLage) {
		case INNERH:
		case INNERHB:
		case KONTUR:
		case GLEICH:
			DELETE_OBJ (pNewIsland);
			return true;	// hier brauche ich nichts zu machen

		case INNAUSS:	// beide Inseln vereinigen
			ZweiInselnVereinigen (CL, pNewIsland, &ML1, &ML2);	// 29.10.98
			SubKante (1, i);	// alte _KAF[i]-Insel herausnehmen

		// da jetzt eine Insel gelöscht wurde, hat jetzt die nächste den gleichen
		// Index, wie die soeben gelöschte; deshalb muß das "i++" in der for-Anweisung
		// neutralisiert werden
			i--;
			break;

// überflüssig (28.10.98)
//			case AUSSERH:		// hier kann ich noch nichts endgültiges entscheiden
//				break;

		case AUSSERHB:
		// wenn pNewIsland mit dem Rand der this-Insel keinen Überlappungsbereich hat,
		// kann ich noch nichts endgültiges entscheiden, ansonsten beide Inseln
		// vereinigen
			if (bOverlap) {
				ZweiInselnVereinigen (CL, pNewIsland, &ML1, &ML2);	// 29.10.98
				SubKante (1, i);	// alte _KAF[i]-Insel herausnehmen
				i--;
			}
			break;

		case UMSCHL:		// hier kann ich noch nichts endgültiges entscheiden
		case UMSCHLB:
			SubKante (1, i);	// alte _KAF[i]-Insel herausnehmen
			i--;
			break;

		case OFFEN:			// hier kann ich nichts machen
		case UNKLAR:
			DELETE_OBJ (pNewIsland);
			return false;
		} // switch
	} // for

	AddKante (*pNewIsland, 1, -1);	// neue (vereinigte) Insel hinzufügen
	DELETE_OBJ (pNewIsland);
	return true;
}

} // namespace trias_wmgeometry

#endif // !defined(_FLAECHE_INL__3F1018D6_D59D_4202_8F7F_B18CBC8AF418__INCLUDED_)
