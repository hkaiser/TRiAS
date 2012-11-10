// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/02/1998 08:04:13 PM
//
// @doc
// @module Main.cpp | Berechnung diverser SoldnerNetze

#include <stdio.h>

class CQuadrant {
private:
	double m_dOrigX;
	double m_dOrigY;
	double m_dDeltaX;
	double m_dDeltaY;
	double m_dMaxX;
	double m_dMaxY;

public:
		CQuadrant (double dOrigX, double dOrigY, 
				double dDeltaX, double dDeltaY, double dMaxX, double dMaxY)
			: m_dOrigX(dOrigX), m_dOrigY(dOrigY),
			  m_dDeltaX(dDeltaX), m_dDeltaY(dDeltaY), m_dMaxX(dMaxX), m_dMaxY(dMaxY)
		{
		}

	void Generate(long lStart);
};

void CQuadrant::Generate(long lStart)
{
long lCnt = lStart;		// Objektzähler
bool fNegX = m_dOrigX < m_dMaxX ? false : true;
bool fNegY = m_dOrigY < m_dMaxY ? false : true;

	for (double dX = m_dOrigX; m_dOrigX < m_dMaxX ? dX <= m_dMaxX : dX >= m_dMaxX; dX += m_dDeltaX) {
		for (double dY = m_dOrigY; m_dOrigY < m_dMaxY ? dY <= m_dMaxY : dY >= m_dMaxY; dY += m_dDeltaY) {
		// Nomenklatur generieren
		long lX = long(dX/1000);
		long lY = long(dY/1000);

			if (fNegX) lX--;
			if (fNegY) lY--;

			printf ("\"2\",\"+%03d+%03d\",\"ALK_%ld\",5\n", lX, lY, lCnt++);

		// Kartenrahmen ausgeben
			printf ("%lf,%lf\n", dX, dY);
			printf ("%lf,%lf\n", dX, dY+m_dDeltaY);
			printf ("%lf,%lf\n", dX+m_dDeltaX, dY+m_dDeltaY);
			printf ("%lf,%lf\n", dX+m_dDeltaX, dY);
			printf ("%lf,%lf\n", dX, dY);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// 
void main (void)
{
	CQuadrant(40000, 10000, 1000, 1000, 50000, 40000).Generate(10000);
	CQuadrant(40000, 10000, 1000, -1000, 50000, 1000).Generate(20000);
	CQuadrant(40000, 10000, -1000, -1000, 2000, 1000).Generate(30000);
	CQuadrant(40000, 10000, -1000, 1000, 2000, 40000).Generate(40000);
}

