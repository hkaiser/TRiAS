// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/02/1998 08:04:13 PM
//
// @doc
// @module Main.cpp | Berechnung des Tk25 Netzes

#include "stdafx.h"

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

	void Generate(const char *pcName, const char *pcPrefix = "");
	void GenerateSub(const char *pcName);
};

void CQuadrant::Generate(const char *pcName, const char *pcPrefix)
{
	for (double dX = m_dOrigX; m_dOrigX < m_dMaxX ? dX <= m_dMaxX : dX >= m_dMaxX; dX += m_dDeltaX) {
		for (double dY = m_dOrigY; m_dOrigY < m_dMaxY ? dY <= m_dMaxY : dY >= m_dMaxY; dY += m_dDeltaY) {
		// Nomenklatur generieren (Bezugskoordinate ist 5°40'/55°54')
		int iNomenX = int((dX-20400)/600);
		int iNomenY = int((201240-dY)/360);
		int iNomen = 100*iNomenY + iNomenX;

			printf ("\"1\",\"%s%04d\",\"%s_%s%ld\",5\n", pcPrefix, iNomen, pcName, pcPrefix, iNomen);

		// Kartenrahmen ausgeben
			printf ("%lf,%lf\n", dX, dY);
			printf ("%lf,%lf\n", dX, dY+m_dDeltaY);
			printf ("%lf,%lf\n", dX+m_dDeltaX, dY+m_dDeltaY);
			printf ("%lf,%lf\n", dX+m_dDeltaX, dY);
			printf ("%lf,%lf\n", dX, dY);
		}
	}
}

void CQuadrant::GenerateSub(const char *pcName)
{
	for (double dX = m_dOrigX; m_dOrigX < m_dMaxX ? dX <= m_dMaxX : dX >= m_dMaxX; dX += m_dDeltaX) {
		for (double dY = m_dOrigY; m_dOrigY < m_dMaxY ? dY <= m_dMaxY : dY >= m_dMaxY; dY += m_dDeltaY) {
		// Nomenklatur generieren (Bezugskoordinate ist 5°40'/55°54')
		int iNomenX = int((dX-20400)/600);
		int iNomenY = int((201240-dY)/360);
		int iNomen = 100*iNomenY + iNomenX;

		double dX2 = m_dDeltaX/2;
		double dY2 = m_dDeltaY/2;

		// Kartenrahmen ausgeben (sw)
			printf ("\"1\",\"%04d-SW\",\"%s_%ld_SW\",5\n", iNomen, pcName, iNomen);
			printf ("%lf,%lf\n", dX, dY);
			printf ("%lf,%lf\n", dX, dY+dY2);
			printf ("%lf,%lf\n", dX+dX2, dY+dY2);
			printf ("%lf,%lf\n", dX+dX2, dY);
			printf ("%lf,%lf\n", dX, dY);

		// Kartenrahmen ausgeben (so)
			printf ("\"1\",\"%04d-SO\",\"%s_%ld_SO\",5\n", iNomen, pcName, iNomen);
			printf ("%lf,%lf\n", dX+dX2, dY);
			printf ("%lf,%lf\n", dX+dX2, dY+dY2);
			printf ("%lf,%lf\n", dX+m_dDeltaX, dY+dY2);
			printf ("%lf,%lf\n", dX+m_dDeltaX, dY);
			printf ("%lf,%lf\n", dX+dX2, dY);

		// Kartenrahmen ausgeben (nw)
			printf ("\"1\",\"%04d-NW\",\"%s_%ld_NW\",5\n", iNomen, pcName, iNomen);
			printf ("%lf,%lf\n", dX, dY+dY2);
			printf ("%lf,%lf\n", dX, dY+m_dDeltaY);
			printf ("%lf,%lf\n", dX+dX2, dY+m_dDeltaY);
			printf ("%lf,%lf\n", dX+dX2, dY+dY2);
			printf ("%lf,%lf\n", dX, dY+dY2);

		// Kartenrahmen ausgeben (no)
			printf ("\"1\",\"%04d-NO\",\"%s_%ld_NO\",5\n", iNomen, pcName, iNomen);
			printf ("%lf,%lf\n", dX+dX2, dY+dY2);
			printf ("%lf,%lf\n", dX+dX2, dY+m_dDeltaY);
			printf ("%lf,%lf\n", dX+m_dDeltaX, dY+m_dDeltaY);
			printf ("%lf,%lf\n", dX+m_dDeltaX, dY+dY2);
			printf ("%lf,%lf\n", dX+dX2, dY+dY2);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// 
void main (void)
{
// Sachsen-Anhalt
	CQuadrant(37800, 183240, 600, 360, 47400, 190800).GenerateSub("TK10");	
//	CQuadrant(37800, 183240, 600, 360, 47400, 190800).Generate("TK25");	
//	CQuadrant(37200, 182880, 1200, 720, 47400, 190800).Generate("TK50", "L");	
//	CQuadrant(36000, 182880, 2400, 1440, 47400, 190800).Generate("TK100", "C");	
// Sachsen
//	CQuadrant(42600, 180360, 600, 360, 53400, 185760).Generate("TK25");	
//	CQuadrant(42000, 180000, 1200, 720, 53400, 185760).Generate("TK50", "L");	
//	CQuadrant(40800, 180000, 2400, 1440, 53400, 185760).Generate("TK100", "C");	
// Brandenburg
//	CQuadrant(41400, 185040, 600, 360, 52800, 192240).Generate("TK25");	
//	CQuadrant(40800, 185040, 1200, 720, 52800, 192240).Generate("TK50", "L");	
//	CQuadrant(40800, 184320, 2400, 1440, 52800, 192240).Generate("TK100", "C");	
// gesamtes D
//	CQuadrant(20400, 170100, 600, 360, 53400, 201240).Generate("TK25");	
//	CQuadrant(20400, 168900, 1200, 720, 53400, 201240).Generate("TK50", "L");
//	CQuadrant(19200, 167040, 2400, 1440, 53400, 201240).Generate("TK100", "C");	
}

