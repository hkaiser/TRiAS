// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 28.11.2002 12:26:17 
//
// @doc
// @module GeoObj.cpp | Definition of the <c CGeoObj> class

#include "pheader.h"

#pragma warning(disable: 4284)
#include <ospace/utility/autoptr.h>
#include <ospace/com/comerrormacros.h>

#include <ospace/std/vector>	// vector
#include <ospace/std/algorithm>	// swap()

#include <math.h>

#include "resource.h"
#include "GeoObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// inline Funktionen
namespace {
	inline 
	void SwapKoord(double &rd1, double &rd2)
	{
		double dT = rd1;
		rd1 = rd2;
		rd2 = dT;
	}
	inline
	long HashKoords(void *pData, long lLen)
	{
	long lHash = 0;

		for (long i = 0; i < lLen/sizeof(long); ++i)
			lHash += reinterpret_cast<long *>(pData)[i];
		
		return lHash;
	}
	inline 
	long HashKoordsTolerance(double *pData, long lCnt, double dKoeff)
	{
	long lHash = 0;

		for (long i = 0; i < lCnt; ++i)
			lHash += (long)(reinterpret_cast<double *>(pData)[i] * dKoeff);
		return lHash;
	}
	inline 
	int CompareWithTolerance (double const *pdlhs, double const *pdrhs, long lCnt, double dTolerance)
	{
		for (long i = 0; i < lCnt; ++i) {
		double dCmp = pdlhs[i] - pdrhs[i];

			_ASSERTE(dTolerance >= 0.0);
			if (dCmp != 0.0 && fabs(dCmp) > dTolerance)
				return (dCmp > 0.0) ? 1 : -1;
		}
		return 0;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Objektgeometrie besorgen 
bool CObjGeometrie::FInit (bool fStatisticsOnly)
{
// Statistik anfordern
	if (!DEX_GetObjStatistik (*this))
		return false;

	if (fStatisticsOnly)
		return true;

// Felder anfordern
	ATLTRY(pdblX = new double [lCnt]);
	ATLTRY(pdblY = new double [lCnt]);
	if (pdblX == NULL || pdblY == NULL) 
		return false;
		
	if (iKCnt > 0) {
		if (iObjTyp == OGFlaeche) {
			ATLTRY(plCnt = new long [iKCnt]);
			if (plCnt == NULL) 
				return false;
		} 
		else if (iObjTyp == OGText) {
			((TEXTGEOMETRIE &)*this).pText = new char [iKCnt+1];
			if (((TEXTGEOMETRIE &)*this).pText == NULL) 
				return false;
		}
	}

// Geometrie holen
	iFlags |= OGConverted;
	if (!DEX_GetObjGeometrie (*this)) 
		return false;

// bei Linien/Flächen vergleichbare Position herstellen
bool fResult = true;

	if (OGFlaeche == iObjTyp)
	{
		fResult = AdjustAreaGeometry();
		fResult &= AdjustIslands();	// Inseln sortieren
	}
	else if (OGLinie == iObjTyp)
		fResult = AdjustLineGeometry();

// Hashwerte berechnen
	if (1.0 == m_dKoeff) {
		m_lXHash = HashKoords(&X(0), lCnt*sizeof(double));
		m_lYHash = HashKoords(&Y(0), lCnt*sizeof(double));
	}
	else {
		m_lXHash = HashKoordsTolerance(&X(0), lCnt, m_dKoeff);
		m_lYHash = HashKoordsTolerance(&Y(0), lCnt, m_dKoeff);
	}
	return fResult;
}

/*static*/
double CObjGeometrie::CalcKoeff(double dTolerance)
{
double dKoeff = 1.0;

	if (0 == dTolerance)
		return 1.0;
	if (dTolerance < 0)
		dTolerance = -dTolerance;

	if (dTolerance < 1.0) {
		do {
			dTolerance *= 10;
			dKoeff *= 10;
		} while (dTolerance < 1.0);
	}
	else if (dTolerance > 1.0) {
		do {
			dTolerance /= 10;
			dKoeff /= 10;
		} while (dTolerance > 1.0);
	}
	return dKoeff;
}

///////////////////////////////////////////////////////////////////////////////
// Linien fangen bei der Koordinate an, die weiter links unten liegt
inline
void CObjGeometrie::SwapKoords(long lIndex1, long lIndex2)
{
	SwapKoord (X(lIndex1), X(lIndex2));
	SwapKoord (Y(lIndex1), Y(lIndex2));

}

bool CObjGeometrie::AdjustLineGeometry()
{
double dX1 = X(0);
double dY1 = Y(0);
double dX2 = X(lCnt-1);
double dY2 = Y(lCnt-1);

	if (dX1 < dX2)
		return true;
	if (dX1 == dX2 && dY1 < dY2)
		return true;

// Linie muß umgedreht werden
long lMid = lCnt/2;						// KK021203

	for (long i = 0; i < lMid; ++i) 
		SwapKoords(i, lCnt-i - 1);		// KK021202 - lCnt - 1!

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Flächen fangen bei der Koordinate an, die am weitesten links unten liegt 

bool CObjGeometrie::AdjustAreaGeometry()
{
// alle Konturen drehen
	for (int i = 0; i < GetKCnt(); ++i) {
		if (!AdjustAreaGeometryKontur(i))
			return false;
	}
	return true;
}

bool CObjGeometrie::AdjustAreaGeometryKontur(int iKontur)
{
// Anfangsindex der zu untersuchenden Kontur bestimmen
	_ASSERTE(iKontur < GetKCnt());

long l1st = 0;

	for (int iCont = 0; iCont < iKontur; ++iCont)
		l1st += GetplCnt(iCont);

// die Koordinate bestimmen, die der Schloßpunkt der neuen Kontur werden soll
double dXStart = X(l1st);
double dYStart = Y(l1st);
long lStart = l1st;

	for (long i = l1st+1; i < l1st+GetplCnt(iKontur); ++i) {
		if (dXStart < X(i))
			continue;
		if (dXStart == X(i) && dYStart < Y(i))
			continue;
		dXStart = X(i);
		dYStart = Y(i);
		lStart = i;
	}
	if (l1st == lStart)
		return true;

// jetzt die Kontur der Fläche so drehen, das sie mit dem gefundenen
// Schloßpunkt anfängt
	COM_TRY {
	// Kontur muß geschlossen sein
	long lCnt = lStart-l1st;
	long lLast = l1st+GetplCnt(iKontur)-1;

		_ASSERTE(X(l1st) == X(lLast));
		_ASSERTE(Y(l1st) == Y(lLast));

	auto_ptr<double> pdX (new double[lCnt]);
	auto_ptr<double> pdY (new double[lCnt]);
	long lDelta = lLast-lStart;				// Keine doppelte Koordinate !

		memcpy (pdX.get(), &X(l1st), lCnt*sizeof(double));
		memcpy (pdY.get(), &Y(l1st), lCnt*sizeof(double));

		memmove (&X(l1st), &X(lStart), lDelta*sizeof(double));
		memmove (&Y(l1st), &Y(lStart), lDelta*sizeof(double));

		memcpy (&X(l1st+lDelta), pdX.get(), lCnt*sizeof(double));
		memcpy (&Y(l1st+lDelta), pdY.get(), lCnt*sizeof(double));

		X(lLast) = X(l1st);		// Fläche wieder schließen
		Y(lLast) = Y(l1st);

	} COM_CATCH_RETURN(false);
	return true;
}

// Inseln sortieren nach dem Schlosspunkt der am weitesten links unten liegt;
// bei Übereinstimmung in den Schloßpunkten wird der nächste Stützpunkt zum Vergleich
// herangezogen.
// Voraussetzung: Die Insel sind so gedreht, dass der Schlosspunkt links unten liegt
// (#WM021218)
bool CObjGeometrie::AdjustIslands()
{
short iKCnt = GetKCnt();

	if (iKCnt <= 2) return true;

long l1st = 0;	// erster Stützpunktindex einer Insel

	COM_TRY
	{
	vector <int> piKCnt;	// Feld für die Reihenfolge der Inselindizes
	vector <long> pl1st;	// Feld für die ersten Stützpunktindizes der betreffenden Inseln

		piKCnt.resize (iKCnt-1);	// Größe der Felder anlegen
		pl1st.resize (iKCnt-1);

		// die Felder piKCnt[] und pl1st[] füllen
		for (int i = 0; i < iKCnt-1; ++i)
		{
			l1st += GetplCnt(i);
			piKCnt.at(i) = i + 1;
			pl1st.at(i) = l1st;
		}

		// die Felder piKCnt[] und pl1st[] sortieren
		for (i = 0; i < iKCnt-1; ++i)
			for (int ii = i+1; ii < iKCnt-1; ++ii)
			{
				// zuerst Vergleich der ersten Stützpunkte zweier Inseln
				if (X(pl1st.at(i)) < X(pl1st.at(ii)))
					continue;
				if (X(pl1st.at(i)) == X(pl1st.at(ii)) &&
					Y(pl1st.at(i)) <  Y(pl1st.at(ii)))
					continue;
				// sind diese gleich, dann Vergleich der jeweils zweiten Stützpunkte
				if (X(pl1st.at(i))  == X(pl1st.at(ii)) &&
					Y(pl1st.at(i))  == Y(pl1st.at(ii)) &&
					X(pl1st.at(i)+1) < X(pl1st.at(ii)+1))
					continue;
				if (X(pl1st.at(i))   == X(pl1st.at(ii))   &&
					Y(pl1st.at(i))   == Y(pl1st.at(ii))   &&
					X(pl1st.at(i)+1) == X(pl1st.at(ii)+1) &&
					Y(pl1st.at(i)+1)  < Y(pl1st.at(ii)+1))
					continue;		

				swap (piKCnt.at(i), piKCnt.at(ii));
				swap (pl1st.at(i), pl1st.at(ii));
			}

	long lACCnt = GetlCnt() - GetplCnt(0);	// Gesamtanzahl der Stützpunkte aller Inseln

		auto_ptr<double> pdX (new double[lACCnt]);
		auto_ptr<double> pdY (new double[lACCnt]);

		l1st = 0;	// Index des erstern Stützpunktes für die neue Inselreihenfolge

		// die Inseln sortieren
		for (i = 0; i < iKCnt-1; ++i)
		{
		long lInd = pl1st.at(i);
		long lKCnt = GetplCnt(piKCnt.at(i));	// Anzahl der Stützpunkte einer Insel

			memcpy (pdX.get()+l1st, &X(lInd), lKCnt*sizeof(double));
			memcpy (pdY.get()+l1st, &Y(lInd), lKCnt*sizeof(double));

			l1st += lKCnt;
		}

		// Stützpunkte der sortierten Inseln zurückschreiben
		memcpy (&X(GetplCnt(0)), pdX.get(), lACCnt*sizeof(double));
		memcpy (&Y(GetplCnt(0)), pdY.get(), lACCnt*sizeof(double));
	}
	COM_CATCH_RETURN(false);

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor
CGObject::CGObject (LONG lONr, double dTolerance) :
	m_fInitialized(false),
	m_ogObj(new CObjGeometrie(lONr, dTolerance)),
	m_dTolerance(fabs(dTolerance))
{
}

///////////////////////////////////////////////////////////////////////////////
// Vergleichen zweier Geometrien, liefert true, wenn das linke Objekt "kleiner"
// als das rechte Objekt ist
bool operator< (CGObject const &lhs, CGObject const &rhs)
{
// Objekttyp vergleichen
	if (lhs.iObjTyp() < rhs.iObjTyp())
		return true;
	else if (lhs.iObjTyp() == rhs.iObjTyp()) {
	// Hashwerte vergleichen
		if (lhs.GetXHash() < rhs.GetXHash())
			return true;
		else if (lhs.GetXHash() == rhs.GetXHash()) {
			if (lhs.GetYHash() < rhs.GetYHash())
				return true;
			else if (lhs.GetYHash() == rhs.GetYHash()) {
			// Hashwerte identisch also Geometrien selbst vergleichen
				if (lhs.lCnt() < rhs.lCnt())
					return true;
				else if (lhs.lCnt() == rhs.lCnt()) {
					if (lhs.UseTolerance()) {
					int iCmp = CompareWithTolerance(lhs.X(), rhs.X(), lhs.lCnt(), lhs.GetTolerance());

						if (iCmp < 0)
							return true;
						else if (0 == iCmp &&
							CompareWithTolerance(lhs.Y(), rhs.Y(), lhs.lCnt(), lhs.GetTolerance()) < 0)
						{
							return true;
						}
					}
					else {
					int iCmp = memcmp(lhs.X(), rhs.X(), lhs.lCnt()*sizeof(double));

						if (iCmp < 0)
							return true;
						else if (0 == iCmp &&
							memcmp(lhs.Y(), rhs.Y(), lhs.lCnt()*sizeof(double)) < 0)
						{
							return true;
						}
					}
				}		
			}
		}
	}
	return false;
}
