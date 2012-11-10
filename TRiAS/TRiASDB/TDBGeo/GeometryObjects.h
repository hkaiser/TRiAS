// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 18.01.2002 14:10:04 
//
// @doc
// @module GeometryObjects.h | Declaration of the <c CGeometryObjects> class

// WMObjRechteck und Elementarobjekte WMPunkt, WMKante, WMFlaeche
// Original: W. Mörtl

#if !defined(_GEOMETRYOBJECTS_H__4272BEC2_5135_4F70_A44C_DBA868DC886B__INCLUDED_)
#define _GEOMETRYOBJECTS_H__4272BEC2_5135_4F70_A44C_DBA868DC886B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <limits>
#include "GeometryObjectsFwd.h"

namespace trias_wmgeometry {

///////////////////////////////////////////////////////////////////////////////
// Konstantendefinitionen
const double Pi = 3.141592653589793238462643383279502884197169399;

// dGlEps ist die zulässige Abweichung bei EpsGleich() bzw. EpsUngleich().
// Eigentlich müßte sqrt(2)/2 = 0.7071 (die halbe Diagonale eines Quadrates mit der
// Kantenlänge 1) ausreichen.
// In mindestens einem Fall reicht dies aber nicht aus: So wurde eine Fläche mit Inseln
// geschnitten. Zwischen dem Schnitt der Außenkontur und den Innenkonturen wurden jeweils die
// double-Koordinaten auf KoOrd-Koordinaten gerundet, da die Ergebnisfläche ein
// GeoFlaeche-Objekt ist. Dadurch ragte die Ergebnisfläche mehr als sqrt(2)/2 über die
// schneidende Fläche hinaus. Ein erneuter Schnitt (nun aber mit dem WMSchnittErgebnis des ersten
// Schnittes) hätte noch einmal echte neue Teilflächen ergeben.
// Die bisher bekannte größte Abweischung beträgt 0.74275 (08.10.98)
// Die bisher bekannte größte Abweischung beträgt 1.51555 (13.10.98)
const double dGlEps = 1E-6; // was 1.52;		// zulässige Abweichung bei Test auf Gleichheit (in DB-Koordinaten)
const double dREps = 1E-6;		// zulässiges Rauschen bei double-Koordinaten
const short iKoEps = 6;			// zulässige Abweichung bei eps-Kollinearität dreier Punkte
const short iCoEps = 6;			// zulässige Abweichung bei Container-Durchschnitt
const short iBuEps = 6;			// zulässige Abweichung bei Bildung der Pufferelemente

const double dDopEps = 0.;		// zulässige Abweichung bei Bereinigung von DoppelPunkt'en (in
								// Meter)
const double dSpiEps = 0.5;		// Grenzwinkel für Spitze (in Gradmaß)

///////////////////////////////////////////////////////////////////////////////
// WMPosition eines Objektes zu einem Bezugsobjekt
enum WMPosit
{
	INNERH,		// vollständig innerhalb des Bezugsobjektes
	INNERHB,	// innerhalb des Bezugsobjektes ( = Fläche), aber mit Berührung
				// des Flächenrandes
	KONTUR,		// vollständig auf dem Rand des Bezugsobjektes
	AUSSERH,	// vollständig außerhalb des Bezugsobjektes
	AUSSERHB,	// außerhalb des Bezugsobjektes, aber mit Berührung des 
				// Bezugsobjektes
	INNAUSS,	// teilweise innerhalb, teilweise außerhalb des Bezugsobjektes
	UMSCHL,		// außerhalb des Bezugsobjektes, aber umschließt das Bezugsobjekt 
				// vollständig (nur für geschlossenes Bezugsobjekt möglich)
	UMSCHLB,	// außerhalb des Bezugsobjektes, aber mit Berührung des Bezugs-
				// objektes und umschließt das Bezugsobjekt vollständig (nur 
				// für geschlossenes Bezugsobjekt möglich)
	OFFEN,		// Rand des Bezugsobjektes ( = Fläche) nicht geschlossen
	UNKLAR,		// vorzeitiges Ende bei falschen Parametern, unzureichendem 
				// dynamischen Speicher oder Abbruch durch den Anwender
	GLEICH		// beide Objekte sind identisch
};

///////////////////////////////////////////////////////////////////////////////
// Position eines Objektes zu einem Bezugsobjekt (nach der OGC-Norm)
enum OGCWMPosit
{
	WITHIN,		// vollständig innerhalb des Bezugsobjektes
	CONTAIN,	// überdeckt das Bezugsobjekt vollständig
	OVERLAP,	// teilweise innerhalb, teilweise außerhalb des Bezugsobjektes 
				// (nur für die Kombinationen Linie/Linie und Fläche/Fläche; 
				// der Durchschnitt beider Objekte muß die gleiche Dimension 
				// wie die Vergleichsobjekte haben)
	ENTER,		// teilweise innerhalb, teilweise außerhalb des Bezugsobjektes 
				// (nur für die Kombinationen Linie/Linie, Linie/Fläche und 
				// Fläche/Linie; der Durchschnitt beider Objekte muß eine 
				// geringere Dimension als die größere der beiden Dimensionen 
				// der Vergleichsobjekte haben)
	TOUCH,		// berührt das Bezugsobjekt von außen
	EQUAL,		// vollständig identisch mit dem Bezugsobjekt
	DISJOINT,	// keinerlei Gemeinsamkeiten mit dem Bezugsobjekt
	INTERSECT,	// mindestens ein Punkt mit dem Bezugsobjekt gemeinsam 
				// (NOT DISJOINT)
	UNCLEAR		// vorzeitiges Ende bei falschen Parametern, unzureichendem 
				// dynamischen Speicher oder Abbruch durch den Anwender
};

///////////////////////////////////////////////////////////////////////////////
// mögliche Ergebnisse bei Test auf Überschneidung der Strecken zweier Kanten
enum WMSchnittErg
{
	KEINE,		// keine Überschneidung
	ECHT,		// Überschneidung, so daß Schnittpunkt jeweils im "Inneren" der beiden
				// Strecken liegt (echter Schnitt)
	RAND,		// Überschneidung, so daß Schnittpunkt bei beiden Strecken ein Randpunkt
				// ist, Seitenwechsel ist noch nicht geklärt (Randpunktberührung)
	RAND_MIT,	// Überschneidung, so daß Schnittpunkt bei beiden Strecken ein Randpunkt
				// ist und ein sofortiger Seitenwechsel erfolgt (Randpunktberührung)
	RAND_OHNE,	// Berührung in einem Punkt, der bei beiden Strecken ein Randpunkt ist, ein
				// Seitenwechsel erfolgt nicht (Randpunktberührung)
	INNEN,		// Berührung in einem Punkt, der bei einer Strecke ein Randpunkt ist, bei der
				// anderen in deren "Inneren" liegt, Seitenwechsel ist noch nicht geklärt
				// (Innenberührung)
	INNEN_MIT,	// Überschneidung, so daß Schnittpunkt bei einer Strecke ein Randpunkt ist,
				// bei der anderen in deren "Inneren" liegt und ein sofortiger Seitenwechsel
				// erfolgt (Innenberührung)
	INNEN_OHNE,	// Berührung in einem Punkt, der bei einer Strecke ein Randpunkt ist, bei der
				// anderen in deren "Inneren" liegt, ein Seitenwechsel erfolgt nicht
				// (Innenberührung)
	BERUE_OHNE,	// Randpunkt- oder Innenberührung ohne Seitenwechsel
	UEBERLAPP	// Überlappung beider Strecken
};

///////////////////////////////////////////////////////////////////////////////
// Objekttypen
enum WMObjTyp { 
	OT_PUNKT,	// Punkt
	OT_KANTE,	// Polylines
	OT_FLAECHE, // Polygones/PolyPolygones
	OT_KREIS,	// Kreis - not used here
	OT_KO,		// Komplexe Geometrie - not used here
	OT_TEXT,	// Text - not used here
	OT_UNKNOWN,	// Unbekannt
	OT_LABEL,	// Indirektes Textobjekt - not used here
};

///////////////////////////////////////////////////////////////////////////////
// auswählbare Lage für Lagebestimmung der Schnittergebnisse
#define LINN	0x01			// Objekt liegt innerhalb,
#define LAUSS	0x02			//  außerhalb,
#define LINAU	LINN | LAUSS	//	sowohl innerhalb als auch außerhalb,
#define LKONT	0x04			//  auf der Kontur des schneidenden Objektes

///////////////////////////////////////////////////////////////////////////////
// Hilfsfunktionen 
template <typename KoOrdT>
KoOrdT KoOrdAbs (KoOrdT x);

template <typename KoOrdT>
KoOrdT KoOrdMin (KoOrdT x, KoOrdT y);

template <typename KoOrdT>
KoOrdT KoOrdMax (KoOrdT x, KoOrdT y);

// Konvertierung von double nach long
template <typename KoOrdT>
KoOrdT DtoLH (double D);
template <>
double DtoLH (double D);

#define DtoL(d) DtoLH<KoOrdT>(d)

///////////////////////////////////////////////////////////////////////////////
// Gemeinsame Basisklasse für ElementarObjekte
template <typename KoOrdT>
class WMObjekt 
{
protected:
// Konstruktor
	WMObjekt();

public:
// Destruktor
	virtual ~WMObjekt();

// rein virtuelle Funktionen
	virtual WMObjTyp isA() const = 0;		// liefert Objekttyp
	virtual WMPosit EnthaltenIn (WMFlaeche<KoOrdT> *, void* pPSt = 0) = 0;

	virtual bool 
	Clipping (WMObjekt *pEO, int iOT, unsigned long ulLageAusw, 
		WMClipListe<KoOrdT> &CL, int iSkip, WMPosit &Lage, bool &bAbbr, 
		void *pPSt);
	virtual bool AddClipObjekt (WMClipListe<KoOrdT> &CL);
};

} // namespace trias_wmgeometry

///////////////////////////////////////////////////////////////////////////////
// sonstige Geometrien
#include "Geometries/BasicFunctions.h"
#include "Geometries/ErrorCorrection.h"

#include "Geometries/Rechteck.h"
#include "Geometries/Punkt.h"
#include "Geometries/Strecke.h"
#include "Geometries/MarkObjects.h"
#include "Geometries/Kante.h"
#include "Geometries/Flaeche.h"
#include "Geometries/Clipliste.h"

///////////////////////////////////////////////////////////////////////////////
// include inline definitions
#include "GeometryObjects.inl"

#endif // !defined(_GEOMETRYOBJECTS_H__4272BEC2_5135_4F70_A44C_DBA868DC886B__INCLUDED_)
