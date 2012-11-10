// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/02/1998 08:04:13 PM
//
// @doc
// @module Main.cpp | Berechnung diverser SoldnerNetze

#include <stdio.h>

class CQuadrant {
private:
	int m_iQuadrant;
	double m_dOrigX;
	double m_dOrigY;
	double m_dDeltaX;
	double m_dDeltaY;
	double m_dMaxX;
	double m_dMaxY;

public:
		CQuadrant (int iQuadNum, double dOrigX, double dOrigY, 
				double dDeltaX, double dDeltaY, double dMaxX, double dMaxY)
			: m_iQuadrant(iQuadNum), m_dOrigX(dOrigX), m_dOrigY(dOrigY),
			  m_dDeltaX(dDeltaX), m_dDeltaY(dDeltaY), m_dMaxX(dMaxX), m_dMaxY(dMaxY)
		{
		}

	void Generate(long lStart);
};

void CQuadrant::Generate(long lStart)
{
long lCnt = lStart;		// Objektzähler
long iX = 1;
long iY = 0;

	for (double dX = m_dOrigX; m_dOrigX < m_dMaxX ? dX <= m_dMaxX : dX >= m_dMaxX; dX += m_dDeltaX, iX++) {
		iY = 0;
		for (double dY = m_dOrigY; m_dOrigY < m_dMaxY ? dY <= m_dMaxY : dY >= m_dMaxY; dY += m_dDeltaY, iY++) {
		// Nomenklatur generieren
			printf ("\"1\",\"%d%02d%02d\",\"SOLDNERNEU_%ld\",5\n", m_iQuadrant, iY, iX, lCnt++);

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
	CQuadrant(1, 40000, 10000, 800, 600, 50000, 40000).Generate(10000);
	CQuadrant(2, 40000, 10000, 800, -600, 50000, 600).Generate(20000);
	CQuadrant(3, 40000, 10000, -800, -600, 2000, 600).Generate(30000);
	CQuadrant(4, 40000, 10000, -800, 600, 2000, 40000).Generate(40000);
}

