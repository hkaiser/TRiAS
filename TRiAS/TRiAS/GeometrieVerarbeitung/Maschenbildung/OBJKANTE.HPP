/*
Datei: OBJKANTE.HPP

Das Modul stellt elementare Datenstrukturen und Methoden zur Realisierung
der Linienverfolgung bereit.

Erarbeitet: J.Benkenstein		Stand vom: 15. Oktober 1996
*/

#ifndef _OBJKANTE_HPP
#define _OBJKANTE_HPP

//	Konstanten
const short KonturSize = 1;				// Konturfeld speichert nur Anzahl der Stützpunkte der 
										// äußeren Masche	
const short sGeoOutputFlags = (short)(OGNoMemoryObject |	// nicht im Speicher halten
									  OGForceGeoError |		// Objekt wird bei Geometriefehler von GEOREIN abgewiesen
									  OGIgnoreIdent |		// Identifikator ignorieren
									  OGNewObject);			// neues Objekt erzeugen 

const short sLineOutputFlags = (short)(OGNoMemoryObject |	// nicht im Speicher halten
									   //OGForceGeoError |	// Objekt wird bei Geometriefehler von GEOREIN abgewiesen
									   OGIgnoreIdent |		// Identifikator ignorieren
									   OGNewObject);		// neues Objekt erzeugen 

DefineSmartInterface (ObjektGeometrie);

//	CObjektKante ----------------------------------------------
class CObjektKante
{
//	Konstruktor/Destruktor
public:
	CObjektKante ();						// default Konstruktor	
	CObjektKante (const CObjektKante &);	// Copy-Konstruktor
	CObjektKante (long lObjNr);				// Interface erzeugen
	
	WObjektGeometrie m_wIObjGeo;	// Interface-Wrapper
	double m_dWi;					// größter/kleinster Winkel zur X-Achse in Größeneinheiten (0..360)
	short m_sBuildCnt;				// Anzahl, wie oft Linie in Masche eingebaut wurde
	short m_sAppendType;			// Vereinigungstyp bei Linien
		  
	BOOL m_bIsInUnion,				// wird Linie gerade vereinigt
		 m_bAussenKante,			// Außenkante ?	
		 m_bIsDirChanged,			// Richtung gewechselt ?
		 m_bIsDirChangedArea;		// wie war Richtung beim Erzeugen der Fläche
	int m_iChangeCounter;			// Anzahl, wie oft die Richtung einer inneren Kante nach
									// dem 1. Einbau noch geändert wurde (#WM990701)

//	allgemeine Funktionen
	HRESULT GetInterface (IObjektGeometrie **ppIOG);
	
//	Geometrie-Infos lesen
	void GetGeometrie (long **pplX, long **pplY,					// Punkte/Texte
					   long *plCnt = NULL,							// Linien/Flächen
					   short *pKCnt = NULL, long **pplLPCnt = NULL);// Flächen
	
//	durch STL geforderte Operatoren
	BOOL operator < (const CObjektKante &OK) const { return FALSE; }

//	durch STL benutzte Operatoren
	BOOL operator = (const CObjektKante &OK);
	BOOL operator == (const CObjektKante &OK) const { return FALSE; }

//	berechne Drehwinkel des 1. Segments der Kante zur x-Achse
	double GetDrehWinkel (void);

//	lese Objektnummer der Kante
	long GetObjNummer (void);

//	Setze Winkelminimum in Abhängigkeit von der Suchrichtung
	void SetWinkelMin (/*BOOL bDir*/void); 

//	Geometrie der übergebenen Kante kopieren
	void InitObjectGeometrie (CObjektKante &Kante);

//	Geometrie-Vektor tauschen
	void ChangeDirection (void);

//	Geometrie des Objektes löschen
	BOOL DeleteGeometrie (BOOL fUndo = TRUE);

// #HK971217
//	Objekt als benutzt kennzeichnen
	BOOL MarkObject (ULONG ulMCode);

//	Geometrie an TRiAS ausgeben: liefert Objektnummer zurück
	long Output (HPROJECT hPr, BOOL& bRO, int iFlags = sGeoOutputFlags, BOOL fUndo = TRUE);

//	Geometrie als Fläche an TRiAS ausgeben:  liefert Objektnummer zurück
	long OutputFlaeche (HPROJECT hPr, BOOL& bRO);

//	vergleiche Objektnummern
	BOOL IsEqual (CObjektKante &OK) { return OK.GetObjNummer () == GetObjNummer (); }

//	lese Anzahl Stützpunkte
	long GetASP (void);

//	lese ObjektContainer
	CObjContainer GetCont (void);

//	lese Objekttyp
	short GetType (void);

	friend class CInitAllKanten;
};

//	CInitAllKanten ------------------------------------------------------------
class CInitAllKanten
{
public:
//	Attribute
	BOOL m_bDirection,				//	math. Richtung
		 m_bIncBuildCnt,			//	UnionFlag in BuildCnt umwandeln
		 m_bResetIsInUnion,			//	setze Flag IsInUnion zurück
		 m_bSetAussenKante,			//	markiere Kante als Außenkante
		 m_bSetWinkelMin;			//	setze Winkelminimum
	
//	Konstruktor/Destruktor
	CInitAllKanten (void) { m_bSetWinkelMin = m_bResetIsInUnion = m_bDirection = TRUE; 
							m_bSetAussenKante = m_bIncBuildCnt = FALSE; }
	
//	operatoren
	void operator ()(CObjektKante &OK);	// führt eigentliche Aktion aus
};

#endif // _OBJKANTE_HPP

