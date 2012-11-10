// Memberfunktionen fuer die Klassen der DGeoObj - Hierarchie -----------------
// File: DGEOOBJ.CXX

#include <stdafx.h>

#include "gdb.h"
#include "dgeoobj.hxx"
#include "hashtabs.hxx"

#include "mcodes.h"

extern FILE *yyout;	// AusgabeStream
extern int MaxPunktStufe;	// maximal auszugebende Stufe
extern int MaxLinienStufe;
extern int MaxFlaechenStufe;
extern int MaxTextStufe;

extern int h_flag;
extern int s_flag;
extern int r_flag;
extern int b_flag;

extern GDBElementTab *pGDBElemente;	// bereits ausgegebene GDBElemente
extern long cntEl;					// Zähler der GDBElemente

// lokale Funktionsprototypen -------------------------------------------------
static void OutputMK (long, char *);
static void OutputMK (long, double);
static void OutputMK (long, long);
static void OutputGI (CRing &, long);
static void OutputTO (char *);

// Konstruktoren --------------------------------------------------------------
DGeoObj :: DGeoObj (DGeoTyp DGT, DParam *pDPar)
{
	_DGT = DGT;

	_pDPar = pDPar;

	_Code = NULL;

	_Text = NULL;
	_Name = NULL;

	_RelSatz = 0;	// kein Begleitobjekt
}

DGeoObj :: ~DGeoObj (void) 
{
	if (_pDPar) { delete _pDPar; _pDPar = NULL; }
	if (_Text) { delete _Text; _Text = NULL; }
	if (_Name) { delete _Name; _Name = NULL; }
}

DGeoObj :: DGeoObj (DGeoObj &DGO) {

	_DGT = DGO._DGT;

	_pDPar = DGO._pDPar;		// Pointer wird kopiert
	DGO._pDPar = NULL;		// alten Pointer NULL-Setzen

	_Code = DGO._Code;	// Code fr DB-Ankopplung
	DGO._Code = NULL;

	_Text = DGO._Text;
	DGO._Text = NULL;
	_Name = DGO._Name;
	DGO._Name = NULL;

	_RelSatz = DGO._RelSatz;	// Begleitobjekt kopieren
}

void DGeoObj :: SetParams (DParam *pDParam) {

	if (_pDPar) delete _pDPar;
	_pDPar = new DParam;
	if (_pDPar) 
		*_pDPar = *pDParam;	// echte Kopie machen
}

void DGeoObj :: SetCode (char *pCode) {

	if (_Code) delete _Code;
	_Code = pCode;
}

void DGeoObj :: SetText (char *Text) {

	if (_Text) delete _Text;
	_Text = Text;
}

void DGeoObj :: SetName (char *Name) {

	if (_Name) delete _Name;
	_Name = Name;
}


// ----------------------------------------------------------------------------
DPunkt :: DPunkt (void) 
	: DGeoObj (DGT_Punkt)
{
	_X = _Y = -1.0;
}

DPunkt :: DPunkt (DPunkt &DPt) 
	: DGeoObj ((DGeoObj &)DPt)
{
	_X = DPt.X(); _Y = DPt.Y();
}

DPunkt :: DPunkt (double X, double Y) 
	: DGeoObj (DGT_Punkt)
{
	_X = X; _Y = Y;
}

// macht eine echte Kopie (aber nur Geometrie) --------------------------------
DGeoObj *DPunkt :: Copy (void) {
DPunkt *pDPt = new DPunkt ();		// neuen DPunkt anlegen

	if (pDPt == NULL) return NULL;
	pDPt -> _X = _X;
	pDPt -> _Y = _Y;

return pDPt;
}

DGeoObj *DSymbol :: Copy (void) 
{
	return new DSymbol; 
}

void DPunkt :: SetPunktParams (char *PKZ, long PNR) {

	strncpy (_PunktKennzeichen, PKZ, 4);
	_PunktNummer = PNR;
}

// Vergleicht die Geometrien zweier Punkte
Bool DPunkt :: operator== (DPunkt &DPt) {

	return ((X() == DPt.X()) && (Y() == DPt.Y()));
}


// Linien/Polygone/Bogen/Kreise -----------------------------------------------
DLinie :: DLinie (void) 
	: DGeoObj (DGT_Linie)
{
	_pDPL = new DPunktListe();
	if (_pDPL == NULL) 
		yyerror ("Kein Speicherplatz.");
}

DLinie :: DLinie (DLinie &DLi) 
	: DGeoObj ((DGeoObj &)DLi)
{
	_pDPL = DLi._pDPL;	// Pointer wird kopiert !!
	DLi._pDPL = NULL;	// doppeltes delete verhindern
}

DGeoObj *DLinie :: Copy (void) {	// kopiert Liniengeometrie
DLinie *pDLi = new DLinie();
	
	if (pDLi)
		pDLi -> _pDPL = _pDPL -> Copy();

return pDLi;
}


// Kreisbogen (Kreis) durch Polygon approximieren -----------------------------
static double Sinus[360];
static double Cosinus[360];
static Bool SinCosValid = FALSE;

Bool DLinie :: MakePolygon (double X, double Y, double X0, double Y0, double Winkel, int Delta) {

// WinkelTabellen aufbauen
	if (!SinCosValid) {
	double ArcPi = 2*asin(1.0)/180.0;

		for (int i = 0; i < 360; i++) {
			Sinus[i] = sin (i*ArcPi);
			Cosinus[i] = cos (i*ArcPi);
		}
		SinCosValid = TRUE;
	}

// wenn Winkel sehr klein ist, dann gar nichts machen
	if (Winkel < (double)Delta)
		return TRUE;

// Polygon berechnen
double DeltaX = X0 - X;
double DeltaY = Y0 - Y;

	for (int i = Delta; i < Winkel; i += Delta) {
	double XKoord, YKoord;
	int Arc360 = i % 360;

		XKoord = X + Cosinus[Arc360]*DeltaX - Sinus[Arc360]*DeltaY;
		YKoord = Y + Cosinus[Arc360]*DeltaY + Sinus[Arc360]*DeltaX;

	// DBContainer korrigieren
		SetXCont (XKoord);
		SetYCont (YKoord);

	DPunkt DPt (XKoord, YKoord);
		AddGeoObj (&DPt);	
	}

return TRUE;
}

DFlaeche :: DFlaeche (void) 
	  : DGeoObj (DGT_Flaeche)
{
	_pDLL = new DLinienListe ();
}

// Copy-Construktor
DFlaeche :: DFlaeche (DFlaeche &DF) 
	  : DGeoObj ((DGeoObj &)DF)
{
	_pDLL = DF._pDLL;	// LinienListe umh„ngen
	DF._pDLL = NULL;

	memcpy (_Pointer, DF._Pointer, PointerSize);
}

// kopiert Fl„chengeometrie ---------------------------------------------------
DGeoObj *DFlaeche :: Copy (void) {
DFlaeche *pDFl = new DFlaeche ();

	if (pDFl)
		pDFl -> _pDLL = _pDLL -> Copy();

return pDFl;
}


void DFlaeche :: SetPointer (char Pointer [PointerSize]) {

	memcpy (_Pointer, Pointer, PointerSize);
}

char *DFlaeche :: GetPointer (char Pointer [PointerSize]) {

	memcpy (Pointer, _Pointer, PointerSize);

return Pointer;
}

DPunkt *DFlaeche :: FirstDPunkt (void) {

	return _pDLL -> FirstDPunkt();
}

DPunkt *DFlaeche :: LastDPunkt (void) {

	return _pDLL -> LastDPunkt();
}

// Destruktoren ---------------------------------------------------------------
DPunkt :: ~DPunkt (void) 
{
	// nothing
}

DLinie :: ~DLinie (void) {

	if (_pDPL != NULL) {
		delete _pDPL;
		_pDPL = NULL;
	}
}

DFlaeche :: ~DFlaeche (void) {

	if (_pDLL) {
		delete _pDLL;
		_pDLL = NULL;
	}
}


// Erweiterung der Geometrie --------------------------------------------------
Bool DPunkt :: AddGeoObj (DGeoObj *pDGO, AppMode) {

	if (pDGO == NULL)
		return TRUE;	// falls leerer Punkt dazukommt

	switch (pDGO -> isA()) {
	case DGT_Punkt:
		{
		// evtl. Relation weitergeben
			if (RelSatz() == 0)
				_RelSatz = pDGO -> RelSatz();

		// Koordinaten austauschen
		DPunkt *pPt = (DPunkt *)pDGO;
		
			if (pPt -> X() == -1 && pPt -> Y() == -1)
			// wenn ungltiger Punkt einfach wieder raus
				return TRUE;
			_X = ((DPunkt *)pDGO) -> X();
			_Y = ((DPunkt *)pDGO) -> Y();

			return TRUE;
		}

	case DGT_Text:
		{
		// als Begleitobjekt an Punkt anh„ngen
			_RelSatz = pDGO -> Enum();
		}
		return TRUE;

	case DGT_Linie:
	case DGT_Flaeche:
	case DGT_Unknown:
	default:
	// Fehler, kann nicht Objekt h”herer Ordnung anh„ngen
		yyerror ("Fragwrdige Objektreihenfolge.");
		return FALSE;
	}
}

Bool DLinie :: AddGeoObj (DGeoObj *pDGO, AppMode AM) {

	if (pDGO == NULL) 
		return TRUE;	// falls leeres Objekt dazukommen soll

	switch (pDGO -> isA()) {
	case DGT_Punkt:
		{
		// erster bzw. letzter Punkt
		DPunkt *pPt = (DPunkt *)pDGO;
		
			if (pPt -> X() == -1 && pPt -> Y() == -1)
			// wenn ungltiger Punkt einfach wieder raus
				return TRUE;
			return _pDPL -> AddDPunkt (*(DPunkt *)pDGO);
		}

	case DGT_Linie:
	{
	if (Count() && ((DLinie *)pDGO) -> _pDPL -> Count()) {
		// wenn alte/neue Linien nicht leer sind

	// evtl. Relation weitergeben
		if (RelSatz() == 0) {
			_RelSatz = pDGO -> RelSatz();
		}

	// die Linie muá ggf. gedreht werden, um einen Anschluá zu
	// gew„hrleisten
	DPunkt *oldFirst = _pDPL -> FirstDPunkt();
	DPunkt *oldLast = _pDPL -> LastDPunkt();
	DPunkt *newFirst = ((DLinie *)pDGO) -> _pDPL -> FirstDPunkt();
	DPunkt *newLast = ((DLinie *)pDGO) -> _pDPL -> LastDPunkt();
	CRing newR(*(((DLinie *)pDGO) -> _pDPL)); 	// neue PunktListe
	Bool RetVal = FALSE;

		if (!oldFirst || !oldLast || !newFirst || !newLast) {
			yyerror ("Kein Speicherplatz.");
			RetVal = FALSE;
		} else switch (AM) {
		case AM_Reverse:
		// Zwischenpunkte eines Polygones gedreht anh„ngen
			RetVal = AppendReverse (*_pDPL, newR, FALSE);
			break;

		case AM_NoReverse:
		// Zwischenpunkte eines Polygones direkt anh„ngen
			RetVal = Append (*_pDPL, newR, FALSE);
			break;

		case AM_NoSense:
		// sonstige F„lle, erzeugen zusammenh„ngender Polygone
			if (*oldLast == *newFirst) {
			// Sttzpunktfolge in richtiger Reihenfolge anh„ngen
				RetVal = Append (*_pDPL, newR);
			} else if (*oldLast == *newLast) {
			// Sttzpunktfolge in umgekehrter Reihenfolge anh„ngen
				RetVal = AppendReverse (*_pDPL, newR);
			} else if (*oldFirst == *newFirst) {
			// 1. Linie umdrehen, dann 2. rankopieren
			DPunktListe *newpDPL = new DPunktListe();

				{
				CRing oldR (*_pDPL);	// alte PunktListe

					AppendReverse (*newpDPL, oldR, FALSE);
					RetVal = Append (*newpDPL, newR);
				}
				if (_pDPL) delete _pDPL;
				_pDPL = newpDPL;
			} else if (*oldFirst == *newLast) {
			// 1. Linie umdrehen, dann 2. umgedreht rankopieren
			DPunktListe *newpDPL = new DPunktListe ();

				{
				CRing oldR (*_pDPL);	// alte PunktListe

					AppendReverse (*newpDPL, oldR, FALSE);
					RetVal = AppendReverse (*newpDPL, newR);
				}
				if (_pDPL) delete _pDPL;
				_pDPL = newpDPL;
			} else {
			// es beginnt ein Loch: ersten Punkt noch mal anh„ngen,
			// dann einfach weitermachen
//				yyerror ("Kann keine geschlossene Linie bilden.");
				RetVal = FALSE;
			}
		}	 

	// Speicherbereiche wieder freigeben und raus
		if (oldFirst) delete oldFirst;
		if (oldLast) delete oldLast;
		if (newFirst) delete newFirst;
		if (newLast) delete newLast;
		return RetVal;
	} else if (Count() == 0) {
	// Linie umh„ngen, da alte Linie noch leer ist
		_pDPL = ((DLinie *)pDGO) -> _pDPL;
		((DLinie *)pDGO) -> _pDPL = NULL;
		return TRUE;
	}
	// wenn lediglich die neue Linie leer ist, dann nichts machen
	}

	case DGT_Text:
		{
		// als BegleitObjekt anhängen
			_RelSatz = pDGO -> Enum();
		}
		return TRUE;

	case DGT_Flaeche:
	case DGT_Unknown:
	default:
	// Fehler, kann nicht Objekt höherer Ordnung anhängen
		yyerror ("Fragwrdige Objektreihenfolge.");
		return FALSE;
	}
}

Bool Append (DPunktListe &DPL, CRing &R, Bool iSecond) {

	R.First();
	if (iSecond)
		R.Next();	// evtl erst beim 2. beginnen
	for ( ; R.Valid(); R.Next()) {
	DPunktLock l(R);

		if (!l || !DPL.AddDPunkt (*(DPunkt *)l)) 
			return FALSE;
	}

return TRUE;
}

Bool AppendReverse (DPunktListe &DPL, CRing &R, Bool iSecond) {

	R.Last();
	if (iSecond) 
		R.Prev();	// evtl. beim 2. von hinten beginnen
	for ( ; R.Valid(); R.Prev()) {
	DPunktLock l(R);

		if (!l || !DPL.AddDPunkt (*(DPunkt *)l)) 
			return FALSE;
	}

return TRUE;
}


Bool DFlaeche :: AddGeoObj (DGeoObj *pDGO, AppMode) {

	switch (pDGO -> isA()) {
	case DGT_Punkt:
	case DGT_Linie:
	// evtl. Relation weitergeben
		if (RelSatz() == 0)
			_RelSatz = pDGO -> RelSatz();
		return _pDLL -> AddGeoObj (pDGO);

	case DGT_Text:
		{
		// als BegleitObjekt anh„ngen
			_RelSatz = pDGO -> Enum();
		}
		return TRUE;

	case DGT_Flaeche:
	case DGT_Unknown:
	default:
	// Fehler, kann nicht Objekt h”herer Ordnung anh„ngen
		yyerror ("Fragwrdige Objektreihenfolge.");
		return FALSE;
	}
}

void DFlaeche :: SetFlaechenParams (double X, double Y, double SWinkel, double SAbstand) {

	_XKoord = X;
	_YKoord = Y;
	_SWinkel = SWinkel;
	_SAbstand = SAbstand;
}

// diese Routine fgt eine neue Kontur an die Flaeche an
Bool DFlaeche :: AddDLinie (DLinie &DL) {

// bei Bedarf Fl„chenkontur schlieáen
DPunkt *pFirst = _pDLL -> FirstDPunkt();
DPunkt *pLast = _pDLL -> LastDPunkt();

	if (pFirst && pLast) {
	// wenn nicht die erste Linie dieser Fl„che
		if (!(*pFirst == *pLast))
			AddGeoObj (pFirst);	// Kontur schlieáen
	}
// Speicher wieder freigeben
	if (pFirst) delete pFirst;
	if (pLast) delete pLast;

// neue Kontur anfordern
return _pDLL -> AddDLinie (DL);
}

// Liefert die Anzahl der Stützpunkte eines/aller Polygone einer Fläche
long DFlaeche :: Count (int i) {
CRing rF (*_pDLL);

	if (i == -1) {
	// Gesamtanzahl der Stützpunkte liefern
	long Val = 0L;

		for (rF.First(); rF.Valid(); rF.Next()) {
		DLinieLock l(rF);

			if (l)
				Val += l -> Count();
		}
		return Val;
	} else if (i >= 0 && i < (int)_pDLL -> Count()) {
	// Stützpunktanzahl einer einzelnen DPunktListe liefern
	int j;

		for (j = 0, rF.First(); j < i && rF.Valid(); j++, rF.Next()) 
			;
		if (rF.Valid() && j == i) {
		DLinieLock l(rF);

			if (l) 
				return l -> Count();
		}
	} 

return 0L;
}

// ListenStrukturen - Memberfunktionen ----------------------------------------
DPunktListe :: DPunktListe (void) 
	     : CListContainer ()
{
	// nothing to do
}

DPunktListe :: ~DPunktListe (void) {

	EveryDelete ();
}

Bool DPunktListe :: AddDPunkt (DPunkt &DPt) {
DPunktCreator DPC (*this);

	return Create (DPC, DPunkt) (DPt) != NULL;
}

// Liefert Kopie des ersten Punktes einer Linie
DPunkt *DPunktListe :: FirstDPunkt (void) {
CRing r(*this);

	if (r.First()) {
	DPunktLock l(r);

		if (l) return (DPunkt *)l -> Copy();
	} 

return NULL;
}

// Liefert Kopie ds letzten Punktes einer Linie
DPunkt *DPunktListe :: LastDPunkt (void) {
CRing r(*this);

	if (r.Last()) {
	DPunktLock l(r);

		if (l) return (DPunkt *)l -> Copy();
	}

return NULL;
}


void DPunktListe :: UserDelete (void *pObj) {

	((DPunkt *)pObj) -> DPunkt :: ~DPunkt ();
}

// kopieren der LinienGeometrie -----------------------------------------------
DPunktListe *DPunktListe :: Copy (void) {
DPunktListe *pDPL = new DPunktListe ();

	if (pDPL) {
	CRing r(*this);
	DPunktCreator Cr (*pDPL);
	
		for (r.First(); r.Valid(); r.Next()) {
		DPunktLock l(r);	// zu kopierender Punkt

			if (!l) continue;

		DPunkt *pDPt = (DPunkt *)l -> Copy();

			if (pDPt) {
				if (Create (Cr, DPunkt) (*pDPt) == NULL) {
					delete pDPt;
					return NULL;	// neu generieren
				}
				delete pDPt;
			} else 
				return NULL;	// Speicherfehler
		}
	} 

return pDPL;
}

// ----------------------------------------------------------------------------
DLinienListe :: DLinienListe (void) 
	      : CListContainer ()
{
	// nothing to do
}

DLinienListe :: ~DLinienListe (void) {

	EveryDelete ();
}

Bool DLinienListe :: AddDLinie (DLinie &DLi) {
DLinieCreator DLC (*this);

	return Create (DLC, DLinie) (DLi) != NULL;
}

Bool DLinienListe :: AddDLinie (void) {
DLinieCreator DLC (*this);

	return Create (DLC, DLinie)() != NULL;
}

void DLinienListe :: UserDelete (void *pObj) {

	((DLinie *)pObj) -> DLinie :: ~DLinie ();
}

// liefert den ersten bzw. letzten Punkt der letzte Linie dieser Fl„che
DPunkt *DLinienListe :: FirstDPunkt (void) {
CRing r(*this);

	if (r.First()) {
	DLinieLock l(r);

		if (l) return l -> _pDPL -> FirstDPunkt();
	}

return NULL;
}

DPunkt *DLinienListe :: LastDPunkt (void) {
CRing r(*this);

	if (r.Last()) {
	DLinieLock l(r);

		if (l) return l -> _pDPL -> LastDPunkt();
	}

return NULL;
}

Bool DLinienListe :: AddGeoObj (DGeoObj *pDGO) {
CRing r(*this);

	if (Count () == 0) 
	// erste Linie dieser Fl„che
		AddDLinie ();

	if (r.Last()) {
	DLinieLock l(r);

		if (l) return l -> AddGeoObj (pDGO);
	}

return FALSE;
}


// kopieren der FlächenGeometrie ----------------------------------------------
DLinienListe *DLinienListe :: Copy (void) {
DLinienListe *pDLL = new DLinienListe ();

	if (pDLL) {
	CRing r(*this);
	DLinieCreator Cr (*pDLL);
	
		for (r.First(); r.Valid(); r.Next()) {
		DLinieLock l(r);	// zu kopierende TeilKontur

			if (!l) continue;

		DLinie *pDLi = (DLinie *)l -> Copy();

			if (pDLi) {
				if (Create (Cr, DLinie) (*pDLi) == NULL) {
					delete pDLi;
					return NULL;	// neu generieren
				}
				delete pDLi;
			} else 
				return NULL;	// Speicherfehler
		}
	} 

return pDLL;
}

// TextElement ----------------------------------------------------------------
DText :: DText (void) 
       : DPunkt ()
{
	_DGT = DGT_Text;	// DPunkt ist TextObjekt
}

DText :: DText (double X, double Y) 
       : DPunkt (X, Y)
{
	_DGT = DGT_Text;	// DPunkt ist TextObjekt
}

DText :: DText (DText &DTxt) 
{
	_Text = DTxt._Text;		// Pointer wird kopiert
	DTxt._Text = NULL;		// NULL - setzen
	_DGT = DTxt._DGT;
}

DText :: ~DText (void) 
{
	// nothing to do
}

void DText :: SetTextParams (int R, double W, double H, double L, double M, double SWI) {

	_Winkel = W;
	_THoehe = H;
	_TLaenge = L;
	_TRicht = R;
	_TModus = M;
	_TSWinkel = SWI;
}


// Ausgabefunktionen ----------------------------------------------------------
Bool DPunkt :: OutPut (void) {

long locEnum = Enum();
long locEnum2 = Enum2();
long locEbene = Ebene() + PUNKTEBENE0;
DGeoObj *plocDGO = r_flag ? this : NULL;

	if (h_flag && pGDBElemente -> FindOrEnter (locEnum, locEnum2, plocDGO)) 
		return FALSE;		// bereits ausgegeben

// nur alles bis zu einer vorgegebenen Stufe ausgeben
	if (Stufe() > MaxPunktStufe) 
		return FALSE;

	if (!s_flag) {
		fprintf (stderr, "GDB-Element(PG): %7ld/%ld     \r", cntEl++, locEnum);
		fflush (stderr);
	}

// IdentifikatorSatz ausgeben
	fprintf (yyout, "P %10ld  %08ld      1\n", locEnum, locEbene);

// Merkmale ausgeben
	if (strcmp (_PunktKennzeichen, "T0") && *_PunktKennzeichen != '\0') 
		OutputMK (MKPKZ, _PunktKennzeichen);
	if (_PunktNummer > 0) 
		OutputMK (MKPNR, _PunktNummer);
	if (_Text) 
		OutputMK (MKPTEXT, _Text);
	if (_Name)
		OutputMK (MKPNAME, _Name);
	if (_Code)
		OutputMK (MKPCODE, _Code);	// DB-AnkopplungsCode

// auf evtl. Begleitobjekt beziehen
	if (_RelSatz) {
		fprintf (yyout, "R B %08ld\n", _RelSatz);
		_RelSatz = 0;
	}

// PunktGeoemtrie ausgeben
	fprintf (yyout, "G %10.4lf %10.4lf\n", X(), Y());
//	fflush (yyout);

return TRUE;
}


Bool DLinie :: OutPut (void) {

long locEnum = Enum();
long locEnum2 = Enum2();
long Cnt = Count();
long locEbene = Ebene() + LINIENEBENE0;
DGeoObj *plocDGO = r_flag ? this : NULL;

	if (h_flag && pGDBElemente -> FindOrEnter (locEnum, locEnum2, plocDGO)) 
		return FALSE;		// bereits ausgegeben

// nur alles bis zu einer vorgebebenen Stufe ausgeben
	if (Stufe() > MaxLinienStufe)
		return FALSE;

	if (!s_flag) {
		fprintf (stderr, "GDB-Element(LI): %7ld/%ld     \r", cntEl++, locEnum);
		fflush (stderr);
	}

// IdentifikatorSatz ausgeben
	fprintf (yyout, "L %10ld  %08ld  %5ld\n", locEnum, locEbene, Cnt);

	if (_Name)
		OutputMK (MKLNAME, _Name);
	if (_Code)
		OutputMK (MKLCODE, _Code);	// DB-AnkopplungsCode
	if (_Text) 
		OutputMK (MKLTEXT, _Text);	// eigentlicher Text

// auf evtl. Begleitobjekt beziehen
	if (_RelSatz) {
		fprintf (yyout, "R B %08ld\n", _RelSatz);
		_RelSatz = 0;
	}

// Geometrie ausgeben
CRing r (*_pDPL);

	OutputGI (r, Cnt);

return TRUE;
}


Bool DFlaeche :: OutPut (void) {

long locEnum = Enum();
long locEnum2 = Enum2();
long Cnt = Count();
long locEbene = Ebene() + FLAECHENEBENE0;
DGeoObj *plocDGO = r_flag ? this : NULL;

	if (h_flag && pGDBElemente -> FindOrEnter (locEnum, locEnum2, plocDGO)) 
		return FALSE;		// bereits ausgegeben

// nur alles bis zu einer vorgegebenen Stufe ausgeben
	if (Stufe() > MaxFlaechenStufe) 
		return FALSE;

	if (!s_flag) {
		fprintf (stderr, "GDB-Element(FL): %7ld/%ld     \r", cntEl++, locEnum);
		fflush (stderr);
	}

#if defined(EWU)
// spezialFall fr EWU
	if (_Pointer[0] != '\0') {
	long Ident = atol (_Pointer);

		fprintf (yyout, "F %10ld 00910%3ld  %5ld\n", locEnum, Ident/1000, Cnt);
	} else
#endif
// IdentifikatorSatz ausgeben
	fprintf (yyout, "F %10ld  %08ld  %5ld\n", locEnum, locEbene, Cnt);

// Merkmale Ausgeben
	if (_Text) 
		OutputMK (MKFTEXT, _Text);	// eigentlicher Text
	if (_XKoord != -1.0 || _YKoord != -1.0) { 
	// Bezugspunkt der F„che ausgeben
		OutputMK (MKFXKOORD, _XKoord);
		OutputMK (MKFYKOORD, _YKoord);
	}
	if (_SWinkel != -1.0 && _SWinkel != 0.0)
		OutputMK (MKFSWINKEL, _SWinkel);	// Schraffurwinkel
	if (_SAbstand != -1.0 && _SAbstand != 0.0)
		OutputMK (MKFSABSTAND, _SAbstand);	// Schraffurabstand
	if (_Code)
		OutputMK (MKFCODE, _Code);	// DB-AnkopplungsCode
	if (_Pointer[0] != '\0')		// #JB921506
		OutputMK (MKFPOINTER, _Pointer);// dBase-AnkopplungsCode
	if (_Name)
		OutputMK (MKFNAME, _Name);

// auf evtl. Begleitobjekt beziehen
	if (_RelSatz) {
		fprintf (yyout, "R B %08ld\n", _RelSatz);
		_RelSatz = 0;
	}

// Geometrie ausgeben
CRing rF (*_pDLL);
int i = 0;

	for (i = 0, rF.First(); rF.Valid(); i++, rF.Next()) {
	DLinieLock l(rF);

		if (l) {
		CRing r(*(l -> _pDPL));

			OutputGI (r, l -> _pDPL -> Count());
			fprintf (yyout, "T\n");		//TrennSatz einfügen
		} else
			break;
	}

return TRUE;
}

Bool DText :: OutPut (void) {

long locEnum = Enum();
long locEnum2 = Enum2();
long locEbene = Ebene() + TEXTEBENE0;
DGeoObj *plocDGO = r_flag ? this : NULL;

	if (h_flag && pGDBElemente -> FindOrEnter (locEnum, locEnum2, plocDGO)) 
		return FALSE;		// bereits ausgegeben

// nur alles bis zu einer vorgegebenen Stufe ausgeben
	if (Stufe() > MaxTextStufe) 
		return FALSE;

	if (!s_flag) {
		fprintf (stderr, "GDB-Element(TX): %7ld/%ld     \r", cntEl++, locEnum);
		fflush (stderr);
	}

char outBuff[80];
int iTHoehe, iTBreite;

	if (!b_flag) {
	// IdentifikatorSatz ausgeben
		fprintf (yyout, "P %10ld  %08ld      1\n", locEnum, locEbene);

	// Merkmale Ausgeben
		if (_Text) 
			OutputMK (MKTTEXT, _Text);	// eigentlicher Text
		if (_THoehe != -1.0 && _THoehe != 0.0) 
			OutputMK (MKTHOEHE, _THoehe);	// TextHöhe
		if (_TLaenge != -1.0 && _TLaenge != 0.0)
			OutputMK (MKTLAENGE, _TLaenge);	// TextLänge
		if (_TModus != -1.0)
			OutputMK (MKTMODUS, _TModus);	// TextModus
		if (_Code)
			OutputMK (MKTCODE, _Code);	// DB-AnkopplungsCode
		OutputMK (MKTSWINKEL, _TSWinkel);	// TORIENT
		OutputMK (MKTWINKEL, _Winkel);	// TextWinkel

	char Richt[2];

		Richt[0] = (char)_TRicht;
		Richt[1] = '\0';
		OutputMK (MKTRICHT, Richt);	// TextAusrichtung

	// VisInfo als Merkmal ausgeben
	int iTTyp = 0x0;

		switch (_TRicht) {
		default:
		case 'L':
			break;

		case 'M':
			iTTyp |= TV_CentreAlign;
			break;

		case 'R':
			iTTyp |= TV_RightAlign;
			break;
		}
		

		if (_THoehe != -1 && _TModus != -1) {
			iTHoehe = int(_THoehe / 0.3176);
			iTBreite = int((_THoehe * _TModus) / 0.3176);
			sprintf (outBuff, "x { r=%d; o=%d; s=%d,%d; y=0x%x; }", -(int)_Winkel, -(int)_TSWinkel, -iTHoehe, iTBreite, iTTyp);
		} else {
			sprintf (outBuff, "x { r=%d; o=%d; y=0x%x; }", -(int)_Winkel, -(int)_TSWinkel, iTTyp);
		}
		OutputMK (MKTVISINFO, outBuff);

	// Geoemtrie des Bezugspunktes ausgeben
		fprintf (yyout, "G %12.5lf %12.5lf\n;\n", X(), Y());
//		fflush (yyout);
	} else if (_Text) {
	// Texte als Begleitobjekte ausgeben
		fprintf (yyout, "B %10ld  %08ld      1\n", locEnum, locEbene);

	// eigentlichen Text ausgeben
		OutputTO (_Text);

	// VisInfo als Merkmal ausgeben
	int iTTyp = 0x0;

		switch (_TRicht) {
		default:
		case 'L':
			break;

		case 'M':
			iTTyp |= TV_CentreAlign;
			break;

		case 'R':
			iTTyp |= TV_RightAlign;
			break;
		}
		
		if (_THoehe != -1 && _TModus != -1) {
			iTHoehe = int(_THoehe / 0.3176);
			iTBreite = int((_THoehe * _TModus) / 0.3176);
			sprintf (outBuff, "x { r=%d; o=%d; s=%d,%d; y=0x%x; }", -(int)_Winkel, -(int)_TSWinkel+(int)_Winkel, -iTHoehe, iTBreite, iTTyp);
		} else {
			sprintf (outBuff, "x { r=%d; o=%d; y=0x%x; }", -(int)_Winkel, -(int)_TSWinkel+(int)_Winkel, iTTyp);
		}
		OutputMK (MKTVISINFO, outBuff);

	// Geoemtrie des Bezugspunktes ausgeben
		fprintf (yyout, "G %10.4lf %10.4lf\n;\n", X(), Y());
//		fflush (yyout);
	}

return TRUE;
}


// Ausgabe der MerkmalsInformationen ------------------------------------------
static void OutputMK (long MCode, char *StringM) {

	if (*StringM == '\0') return;

	fprintf (yyout, "M %08ld 1 A %4d\n", MCode, strlen (StringM));

char ScopeChar;

	if (strchr (StringM, '\"')) ScopeChar = '\'';
	else ScopeChar = '\"';

	fprintf (yyout, "W %c%s%c\n", ScopeChar, StringM, ScopeChar);
//	fflush (yyout);
}

static void OutputTO (char *StringM) {
char ScopeChar;

	if (strchr (StringM, '\"')) ScopeChar = '\'';
	else ScopeChar = '\"';

	fprintf (yyout, "I %c%s%c\n", ScopeChar, StringM, ScopeChar);
//	fflush (yyout);
}

static void OutputMK (long MCode, double DoubleM) {
char OutBuff[40];

	sprintf (OutBuff, "%12.5lf", DoubleM);
	OutputMK (MCode, OutBuff);
}

static void OutputMK (long MCode, long LongM) {
char OutBuff[40];

	sprintf (OutBuff, "%ld", LongM);
	OutputMK (MCode, OutBuff);
}

static void OutputGI (CRing &r, long Cnt) {
long i;

	if (Cnt > 0)
		fprintf (yyout, "G ");
	for (i = 0, r.First(); i < Cnt && r.Valid(); i++, r.Next()) {
	double dX = -1.0, dY = -1.0;

		{
		DPunktLock l(r);

			if (l) {
				dX = l -> X();
				dY = l -> Y();
			}
		}	
		fprintf (yyout, "%12.5lf %12.5lf ", dX, dY);
		if ((i + 1) % 3 == 0) {
			fprintf (yyout, "\n");
			if (i + 1 < Cnt)
				fprintf (yyout, "G ");
		}
	}
	if (i % 3 != 0)
		fprintf (yyout, "\n");
//	fflush (yyout);
}

