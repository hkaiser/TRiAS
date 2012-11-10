// Geometrieobjekte (Punkt, Linie, Flaeche) -- Methoden -----------------------
// File: GEO_OBJ.CXX

#include "trias02p.hxx"

#if defined(_FORCE_LEGACY_CODE)

#include <limits.h>

// Methoden für Geometrieobjekt: KANTE ----------------------------------------
// Konstruktoren
Kante :: Kante (KoOrd x[], KoOrd y[], long size) 
{
	if (size == 0 || x == NULL || y == NULL) {
		_SPF = NULL;
		_Size = 0;
		_OCont = NULL;
		db_error (EC_ILLPARS, RC_ctKante);
	} else {
#if !defined(WIN32)
		if (size > HUGELIMIT) 
			_SPF = new __huge Punkt [_Size = size];	// ____huge
		else
#endif
			_SPF = new Punkt [_Size = size];	// normal
		if (_SPF == NULL) {
			_Size = 0;
			db_error (EC_NOMEMORY, RC_ctKante);
			return;
		}
#if !defined(WIN32)
		if (size > HUGELIMIT) {
			for (long i = 0; i < size; i++)
				((Punkt __huge *)_SPF)[i] = Punkt (((KoOrd __huge *)x)[i], ((KoOrd __huge *)y)[i]);
		} else 
#endif
		{
			for (long i = 0; i < size; i++)
				_SPF[i] = Punkt (x[i], y[i]);
		}
		_OCont = NULL;
	}
}

// Linie - Stützpunktfeld
// size  - Anzahl der Stützpunkte
Kante :: Kante (Punkt Linie[], long size) 
{
	if (size == 0 || Linie == (Punkt *)NULL) {
		_SPF = NULL;
		_Size = 0;
		_OCont = NULL;
		db_error (EC_ILLPARS, RC_ctKante);
	} else {
#if !defined(WIN32)
		if (size > HUGELIMIT) 
			_SPF = new __huge Punkt [_Size = size];	// ____huge
		else
#endif
			_SPF = new Punkt [_Size = size];	// normal

		if (_SPF == NULL) {
			_Size = 0;
			db_error (EC_NOMEMORY, RC_ctKante);
			return;
		}
#if !defined(WIN32)
		if (size > HUGELIMIT) {
			for (long i = 0; i < size; i++) 
				((Punkt __huge *)_SPF)[i] = ((Punkt __huge *)Linie)[i];	 // Kante umkopieren
		} else 
#endif
		{
			for (long i = 0; i < size; i++) 
				_SPF[i] = Linie[i];	 // Kante umkopieren
		}
		_OCont = NULL;
	}
}

Kante :: Kante (const Kante &newKante) 
{
	if (newKante._Size == 0 || newKante._SPF == NULL) {
		_SPF = NULL;
		_Size = 0;
		_OCont = NULL;
		db_error (EC_ILLPARS, RC_ctKante);
	} else {
#if !defined(WIN32)
		if (newKante._Size > HUGELIMIT) 
			_SPF = new __huge Punkt [_Size = newKante._Size];	// ____huge
		else
#endif
			_SPF = new Punkt [_Size = newKante._Size];	// normal

		if (_SPF == NULL) {
			_Size = 0;
			db_error (EC_NOMEMORY, RC_ctKante);
			return;
		}

#if !defined(WIN32)
		if (_Size > HUGELIMIT) {
			for (long i = 0; i < _Size; i++) 
				((Punkt __huge *)_SPF)[i] = ((Punkt __huge *)newKante._SPF)[i];	 // Kante umkopieren
		} else 
#endif
		{
			for (long i = 0; i < _Size; i++)
				_SPF[i] = newKante._SPF[i];
		}
		if (newKante._OCont) {
			_OCont = new ObjContainer (*newKante._OCont);
			if (_OCont == NULL) {
				db_error (EC_NOMEMORY, RC_ctKante);
				return;
			}
		} else
			_OCont = NULL;
	}
}

// Konstruktor, der direkt eine fertige Kante übergibt ------------------------
Kante :: Kante (long Size, Punkt* SPF) 
{
	if (Size == 0 || SPF == NULL) {
		_SPF = NULL;
		_Size = 0;
		_OCont = NULL;
		db_error (EC_ILLPARS, RC_ctKante);
	} else {
		_SPF = SPF;
		_Size = Size;
		_OCont = NULL;
	}
}

void Kante :: operator =(const Kante &newKante) 
{
	if (this == &newKante) return;		// Vorsicht nicht s=s !

	if (newKante._Size == 0 || newKante._SPF == NULL)
		return;

#if !defined(WIN32)
	if (_Size > HUGELIMIT) {
		if (_SPF) {
			delete [_Size] (Punkt __huge *)_SPF;
			_SPF = NULL;
		}
	} else 
#endif
	{
		DELETE_VEC (_SPF/*, _Size*/);
	}
	DELETE_OBJ (_OCont);
	_Size = 0;

#if !defined(WIN32)
	if (newKante._Size > HUGELIMIT) 
		_SPF = new __huge Punkt [_Size = newKante._Size];	// ____huge
	else
#endif
		_SPF = new Punkt [_Size = newKante._Size];	// normal
		
	if (_SPF == NULL) {
		_Size = 0;
		db_error (EC_NOMEMORY, RC_asKante);
		return;
	}

#if !defined(WIN32)
	if (_Size > HUGELIMIT) {
		for (long i = 0; i < _Size; i++) 
			((Punkt __huge *)_SPF)[i] = ((Punkt __huge *)newKante._SPF)[i];	 // Kante umkopieren
	} else 
#endif
	{
		for (long i = 0; i < _Size; i++)
			_SPF[i] = newKante._SPF[i];
	}
	if (newKante._OCont) {
		_OCont = new ObjContainer (*newKante._OCont);
		if (_OCont == NULL) {
			db_error (EC_NOMEMORY, RC_asKante);
			return;
		}
	} else
		_OCont = NULL;
}

Kante :: ~Kante (void) 
{
#if !defined(WIN32)
	if (_Size > HUGELIMIT) {
		if (_SPF) {
			delete [_Size] (Punkt __huge *)_SPF;
			_SPF = NULL;
		}
	} else 
#endif
	{
		DELETE_VEC (_SPF/*, _Size*/);
	}
	DELETE_OBJ (_OCont);
	_Size = 0;
}


// Memberfunktionen
ObjContainer Kante :: maxCont (ObjContainer &ObjCont) 
{
#if !defined(WIN32)
	if (_Size > HUGELIMIT) {
	Punkt __huge *currP = _SPF;
	
		for (long i = 0; i < _Size; i++, currP++) {
			if (currP -> X() < ObjCont.XMin()) 
				ObjCont.XMin() = currP -> X();
			if (currP -> X() > ObjCont.XMax())
				ObjCont.XMax() = currP -> X();
		}
		for (i = 0, currP = _SPF; i < _Size; i++, currP++) {
			if (currP -> Y() < ObjCont.YMin()) 
				ObjCont.YMin() = currP -> Y();
			if (currP -> Y() > ObjCont.YMax())
				ObjCont.YMax() = currP -> Y();
		}
	} else 
#endif
	{
	Punkt *currP = _SPF;
	
		for (long i = 0; i < _Size; i++, currP++) {
			if (currP -> X() < ObjCont.XMin()) 
				ObjCont.XMin() = currP -> X();
			if (currP -> X() > ObjCont.XMax())
				ObjCont.XMax() = currP -> X();
		}
		for (i = 0, currP = _SPF; i < _Size; i++, currP++) {
			if (currP -> Y() < ObjCont.YMin()) 
				ObjCont.YMin() = currP -> Y();
			if (currP -> Y() > ObjCont.YMax())
				ObjCont.YMax() = currP -> Y();
		}
	}
	
return ObjCont;
}

ObjContainer Kante :: minCont (ObjContainer &ObjCont) 
{
#if !defined(WIN32)
	if (_Size > HUGELIMIT) {
	Punkt __huge *currP = _SPF;

		for (long i = 0; i < _Size; i++, currP++) {
			if (currP -> X() > ObjCont.XMin()) 
				ObjCont.XMin() = currP -> X();
			if (currP -> X() < ObjCont.XMax())
				ObjCont.XMax() = currP -> X();
		}
		for (i = 0, currP = _SPF; i < _Size; i++, currP++) {
			if (currP -> Y() > ObjCont.YMin()) 
				ObjCont.YMin() = currP -> Y();
			if (currP -> Y() < ObjCont.YMax())
				ObjCont.YMax() = currP -> Y();
		}
	} else 
#endif
	{
	Punkt *currP = _SPF;

		for (long i = 0; i < _Size; i++, currP++) {
			if (currP -> X() > ObjCont.XMin()) 
				ObjCont.XMin() = currP -> X();
			if (currP -> X() < ObjCont.XMax())
				ObjCont.XMax() = currP -> X();
		}
		for (i = 0, currP = _SPF; i < _Size; i++, currP++) {
			if (currP -> Y() > ObjCont.YMin()) 
				ObjCont.YMin() = currP -> Y();
			if (currP -> Y() < ObjCont.YMax())
				ObjCont.YMax() = currP -> Y();
		}
	}
	
return ObjCont;
}

// XFeld, YFeld - Koordinatenfelder für X- und Y-Koordinaten
// size         - enthält max. zu liefernde Koordinatenanzahl
void Kante :: GetKante (KoOrd XFeld[], KoOrd YFeld[], long & size) 
{
long toCopy = longMin (size, _Size);
long i;

#if !defined(WIN32)
	if (_Size > HUGELIMIT) {
		for (i = 0; i < toCopy; i++) {
			((KoOrd __huge *)XFeld)[i] = ((Punkt __huge *)_SPF)[i].X();
			((KoOrd __huge *)YFeld)[i] = ((Punkt __huge *)_SPF)[i].Y();
		}
	} else 
#endif
	{
		for (i = 0; i < toCopy; i++) {
			XFeld[i] = _SPF[i].X();
			YFeld[i] = _SPF[i].Y();
		}
	}
	size = i;
}


// Punkt(e) hinzufügen
void Kante :: AddPunkt (const Kante &K, long Anzahl, long Index) 
{
	if (Index == -1)
	// ans Ende anhängen
		Index = _Size;
	if (Anzahl == 0 || 			// nichts einfügen
	    K._SPF == NULL ||	 		// keine Koordinaten gegeben
	    Index < 0 || Index > _Size) {	// ungültiger Wert
		return;		// do nothing
	} else {
	long i, j;
	Punkt *newSPF = NULL;

#if !defined(WIN32)
		if (_Size+Anzahl > HUGELIMIT) {
		Punkt __huge *pSPF = new __huge Punkt [_Size+Anzahl];	// ____huge
		
			if (pSPF == NULL) {
				db_error (EC_NOMEMORY, RC_AddPunkt);
				return;
			}
			--Index;	// besser in Schleifen zu verwenden
			for (i = 0; i <= Index; i++)
				pSPF[i] = ((Punkt __huge *)_SPF)[i];	// Beginn kopieren
			for (j = 0; j < Anzahl; i++, j++)
				pSPF[i] = ((Punkt __huge *)K._SPF)[j];	// Einfügen
			for (j = Index +1; i < _Size + Anzahl; i++, j++)
				pSPF[i] = ((Punkt __huge *)_SPF)[j];
			newSPF = pSPF;
		} else 
#endif
		{
		Punkt *pSPF = new Punkt [_Size+Anzahl];	// normal

			if (pSPF == NULL) {
				db_error (EC_NOMEMORY, RC_AddPunkt);
				return;
			}
			--Index;	// besser in Schleifen zu verwenden
			for (i = 0; i <= Index; i++)
				pSPF[i] = _SPF[i];	// Beginn kopieren
			for (j = 0; j < Anzahl; i++, j++)
				pSPF[i] = K._SPF[j];	// Einfügen
			for (j = Index +1; i < _Size + Anzahl; i++, j++)
				pSPF[i] = _SPF[j];
			newSPF = pSPF;
		}
#if !defined(WIN32)
		if (_Size > HUGELIMIT) {
			if (_SPF) {
				delete [_Size] (Punkt __huge *)_SPF;
				_SPF = NULL;
			}
		} else 
#endif
		{
			DELETE_VEC (_SPF/*, _Size*/);
		}
		_SPF = newSPF;
		_Size += Anzahl;
	}
}

void Kante :: AddPunkt (KoOrd x[], KoOrd y[], long Len, long Index) {

	if (Index == -1)	// ans Ende anhängen
		Index = _Size;
	if (Len == 0 || 			// nichts einfügen
	        Index < 0 || Index > _Size) {	// ungültiger Wert
		return;		// do nothing
	} else {
	long i, j;
	Punkt *newSPF = NULL;
	
#if !defined(WIN32)
		if (_Size+Len > HUGELIMIT) {
		Punkt __huge *pSPF = new __huge Punkt [_Size+Len];	// ____huge
		
			if (pSPF == NULL) {
				db_error (EC_NOMEMORY, RC_AddPunkt);
				return;
			}
			--Index;	// besser in Schleifen zu verwenden
			for (i = 0; i <= Index; i++)
				pSPF[i] = ((Punkt __huge *)_SPF)[i];	// Beginn kopieren
			for (j = 0; j < Len; i++, j++)
				pSPF[i] = Punkt (((KoOrd __huge *)x)[j], ((KoOrd __huge *)y)[j]);	// Einfügen
			for (j = Index +1; i < _Size + Len; i++, j++)
				pSPF[i] = ((Punkt __huge *)_SPF)[j];
			newSPF = pSPF;
		} else 
#endif
		{
		Punkt *pSPF = new Punkt [_Size+Len];
	
			if (pSPF == NULL) {
				db_error (EC_NOMEMORY, RC_AddPunkt);
				return;
			}
			--Index;	// besser in Schleifen zu verwenden
			for (i = 0; i <= Index; i++)
				pSPF[i] = _SPF[i];	// Beginn kopieren
			for (j = 0; j < Len; i++, j++)
				pSPF[i] = Punkt (x[j], y[j]);	// Einfügen
			for (j = Index +1; i < _Size + Len; i++, j++)
				pSPF[i] = _SPF[j];
			newSPF = pSPF;
		}
#if !defined(WIN32)
		if (_Size > HUGELIMIT) {
			if (_SPF) {
				delete [_Size] (Punkt __huge *)_SPF;
				_SPF = NULL;
			}
		} else 
#endif
		{
			DELETE_VEC (_SPF/*, _Size*/);
		}
		_SPF = newSPF;
		_Size += Len;
	}
}

// Methoden für das Geometrieobjekt: MASCHE -----------------------------------
// Konstruktoren
Masche :: Masche (KoOrd x[], KoOrd y[], long Len) 
{
// Masche generieren, die nur aus einer Kante besteht

	_OCont = NULL;
	if (Len <= 0) {
		_KAF = NULL;
		_Size = 0;
	} else {
		_KAF = new Kante [1];
		if (_KAF == NULL) {
			_Size = 0;
			db_error (EC_NOMEMORY, RC_ctMasche);
			return;
		}
		*_KAF = Kante (x, y, Len);
		_Size = 1;
	}
}
	
Masche :: Masche (Kante *Flaeche, short size) 
{
// Flaeche - Kantenfeld dieser Flaeche (Maschen)
// size    - Anzahl der Maschen dieser Fläche

	_OCont = NULL;
	if (size == 0 || Flaeche == NULL) {
		_KAF = NULL;
		_Size = 0;
	} else {
		_KAF = new Kante [size];       // Maschenfeld anfordern
		if (_KAF == NULL) {
			_Size = 0;
			db_error (EC_NOMEMORY, RC_ctMasche);
			return;
		}
		_Size = size;
		for (register short i = 0; i < size; i++)
		// Kopieren der einzelnen Maschen
			_KAF[i] = Flaeche[i];
	}
}

Masche :: Masche (const Masche &newMasche) 
{
	if (newMasche._Size == 0 || newMasche._KAF == NULL) {
		_KAF = NULL;
		_Size = 0;
		_OCont = NULL;
	} else {
		_KAF = new Kante [newMasche._Size]; // Maschenfeld anlegen
		if (_KAF == NULL) {
			_Size = 0;
			db_error (EC_NOMEMORY, RC_ctMasche);
			return;
		}
		_Size = newMasche._Size;

	// Kanten kopieren
		for (register short i = 0; i < newMasche._Size; i++)
			_KAF[i] = newMasche._KAF[i];

	// evtl. Container kopieren
		if (newMasche._OCont) {
			_OCont = new ObjContainer (*newMasche._OCont);
			if (_OCont == NULL) {
				db_error (EC_NOMEMORY, RC_ctMasche);
				return;
			}
		} else 
			_OCont = NULL;
	}
}

// Masche generieren, die nur aus einer Kante besteht -------------------------
Masche :: Masche (Punkt* SPF, long Size) 
{
	_OCont = NULL;
	if (Size <= 0) {
		_KAF = NULL;
		_Size = 0;
	} else {
		_KAF = new Kante[1];
		if (_KAF == NULL) {
			_Size = 0;
			db_error (EC_NOMEMORY, RC_ctMasche);
			return;
		}
		*_KAF = Kante (SPF, Size);
		_Size = 1;
	}
}

void Masche :: operator =(const Masche &newMasche) 
{
	if (this == &newMasche) return;		// Vorsicht nicht s=s !

//		for (register short i = 0; i < _Size; i++)
//		// Kanten freigeben
//			_KAF[i].Kante :: ~Kante ();

	DELETE_VEC (_KAF/*, _Size*/);
	DELETE_OBJ (_OCont);
	_Size = 0;

	if (newMasche._Size == 0 || newMasche._KAF == (Kante *)NULL)
		return;

	_KAF = new Kante [newMasche._Size];	// Maschenfeld anlegen
	if (_KAF == NULL) {
		_Size = 0;
		db_error (EC_NOMEMORY, RC_opMasche);
		return;
	}
	_Size = newMasche._Size;

	for (register int i = 0; i < newMasche._Size; i++)
		_KAF[i] = newMasche._KAF[i];
	if (newMasche._OCont) {
		_OCont = new ObjContainer (*newMasche._OCont);
		if (_OCont == NULL) {
			db_error (EC_NOMEMORY, RC_opMasche);
			return;
		}
	} else 
		_OCont = NULL;
}

// Destruktor -----------------------------------------------------------------
Masche :: ~Masche (void) 
{
	DELETE_VEC (_KAF/*, _Size*/);		// Fläche freigeben
	DELETE_OBJ (_OCont);
	_Size = 0;
}


// Memberfunktionen
ObjContainer Masche :: maxCont (ObjContainer & OC) 
{
	for (register int i = 0; i < _Size; i++)
		_KAF[i].maxCont (OC);

return OC;
}


ObjContainer Masche :: minCont (ObjContainer & OC) 
{
	for (register int i = 0; i < _Size; i++)
		_KAF[i].minCont (OC);

return OC;
}


// Hinzufügen einer Masche (z.B. inneres Loch in Fläche) ----------------------
// Flaeche - Kantenfeld dieser Flaeche (Maschen)
// size    - Anzahl der Maschen dieser Fläche
void Masche :: AddKante (const Masche &Flaeche, short Anzahl, short Index) 
{
	if (Index == -1)	// ans Ende anhängen
		Index = _Size;

	if (Anzahl == 0 || Flaeche._KAF == NULL ||
	    Index < 0 || Index > _Size) {
		db_error (EC_ILLPARS, RC_AddKante);
		return;
	} else {
	register int i, j;
	Kante *newKAF = new Kante [_Size + Anzahl];

		if (newKAF == NULL) {
			db_error (EC_NOMEMORY, RC_AddKante);
			return;
		}
		--Index;	// besser zu verwenden
		for (i = 0; i <= Index; i++)
			newKAF[i] = _KAF[i];		// Beginn kopieren
		for (j = 0; j < Anzahl; i++, j++)
			newKAF[i] = Flaeche._KAF[j];	// Einfügen
		for (j = Index +1; i < _Size + Anzahl; i++, j++)
			newKAF[i] = _KAF[j];		// Rest kopieren
		DELETE_VEC (_KAF/*, _Size*/);
		_Size += Anzahl;
		_KAF = newKAF;
	}
}

// nur eine Kante in Masche einfügen ------------------------------------------
void Masche :: AddKante (KoOrd x[], KoOrd y[], long Len, short Index) 
{
	if (Index == -1)	// ans Ende anhängen
		Index = _Size;
		
	if (Len == 0 || Index < 0 || Index > _Size) {
		db_error (EC_ILLPARS, RC_AddKante);
		return;
	} else {
	register int i, j;
	Kante *newKAF = new Kante [_Size + 1];

		if (newKAF == NULL) {
			db_error (EC_NOMEMORY, RC_AddKante);
			return;
		}
		--Index;	// besser zu verwenden
		for (i = 0; i <= Index; i++)
			newKAF[i] = _KAF[i];		// Beginn kopieren
		newKAF[i++] = Kante (x, y, Len);	// Einfgen
		for (j = Index +1; i <= _Size; i++, j++)
			newKAF[i] = _KAF[j];		// Rest kopieren
		DELETE_VEC (_KAF/*, _Size*/);
		_Size++;
		_KAF = newKAF;
	}
}

// Zu einer der Kanten (Maschen) einer Flaeche Punkt(e) hinzufügen ------------
void Masche :: AddPunkt (const Kante &K, long KAnz, long KIndex, short MIndex) 
{
	if (MIndex == -1)
	// ans Ende anh„ngen
		MIndex = _Size;
	if (MIndex < 1 || MIndex > _Size) {
		db_error (EC_ILLPARS, RC_AddPunkt_K);
		return;
	}
	_KAF[MIndex-1].Kante :: AddPunkt (K, KAnz, KIndex);
}

// wie oben, jedoch Kante als Koordinaten gegeben -----------------------------
void Masche :: AddPunkt (KoOrd x[], KoOrd y[], long Len, long KIndex, short MIndex) 
{
	if (MIndex == -1)	// ans Ende anhängen
		MIndex = _Size;
		
	if (MIndex < 1 || MIndex > _Size) {
		db_error (EC_ILLPARS, RC_AddPunkt_K);
		return;
	}
	_KAF[MIndex-1].Kante :: AddPunkt (x, y, Len, KIndex);
}

// liefert Gesamtanzahl der Stützpunkte ---------------------------------------
long Masche :: ASP (void) 
{
long cnt = 0;

	for (short i = 0; i < KantenAnz(); i++)
		cnt += KA(i).ASP();

return cnt;
}


// Methoden für OBJECTCONTAINER -----------------------------------------------
// Konstruktoren --------------------------------------------------------------
inline void Swap (long x1, long x2)
{
long t = x1;

	x1 = x2;
	x2 = t;
}

ObjContainer :: ObjContainer (KoOrd XMin, KoOrd XMax, KoOrd YMin, KoOrd YMax) 
{
	_XMin = XMin; _XMax = XMax;
	_YMin = YMin; _YMax = YMax;
	if (_XMin > _XMax) Swap (_XMin, _XMax);
	if (_YMin > _YMax) Swap (_YMin, _YMax);
}

ObjContainer :: ObjContainer (Punkt Pt, Ausdehnung A) 
{
	_XMin = Pt.X(); _YMin = Pt.Y();
	_XMax = Pt.X() + A.Breite();
	_YMax = Pt.Y() + A.Hoehe();

	if (_XMin > _XMax) Swap (_XMin, _XMax);
	if (_YMin > _YMax) Swap (_YMin, _YMax);
}

ObjContainer :: ObjContainer (Punkt Pt1, Punkt Pt2) 
{
	_XMin = Pt1.X(); _XMax = Pt2.X();
	_YMin = Pt1.Y(); _YMax = Pt2.Y();

	if (_XMin > _XMax) Swap (_XMin, _XMax);
	if (_YMin > _YMax) Swap (_YMin, _YMax);
}

ObjContainer :: ObjContainer (const ObjContainer &OC) 
{
	_XMin = OC._XMin; _XMax = OC._XMax;
	_YMin = OC._YMin; _YMax = OC._YMax;
}

// Memberfunktionen -----------------------------------------------------------
ObjContainer ObjContainer :: InflateCont (short Percent) 
{
// Werte, um die Container vergrößert werden soll 
	KoOrd dX = ((XMax()-XMin())*Percent)/200;
	KoOrd dY = ((YMax()-YMin())*Percent)/200;

return ObjContainer (XMin()-dX, XMax()+dX, YMin()-dY, YMax()+dY);
}

// ObjContainer direkt verändern ----------------------------------------------
ObjContainer & EXPORT02 ObjContainer :: ShiftCont (Ausdehnung &A) 
{
	XMin() += A.Breite();
	XMax() += A.Breite();
	YMin() += A.Hoehe();
	YMax() += A.Hoehe();

return *this;
}

// Verschnitt zweier ObjContainer testen --------------------------------------
bool EXPORT02 ObjContainer :: operator ^ (ObjContainer &OC) 
{
	if (XMin() > OC.XMax() || XMax() < OC.XMin() ||
	    YMin() > OC.YMax() || YMax() < OC.YMin()) 
	// ObjContainer überschneiden sich nicht
		return false;

return true;
}

// Gemeinsamen Container berechnen --------------------------------------------
ObjContainer & EXPORT02 ObjContainer :: operator + (ObjContainer &OC) 
{
	if (XMin() > OC.XMin()) XMin() = OC.XMin();
	if (XMax() < OC.XMax()) XMax() = OC.XMax();
	if (YMin() > OC.YMin()) YMin() = OC.YMin();
	if (YMax() < OC.YMax()) YMax() = OC.YMax();

return *this;
}

void EXPORT02 ObjContainer :: operator += (ObjContainer &OC) 
{
	if (XMin() > OC.XMin()) XMin() = OC.XMin();
	if (XMax() < OC.XMax()) XMax() = OC.XMax();
	if (YMin() > OC.YMin()) YMin() = OC.YMin();
	if (YMax() < OC.YMax()) YMax() = OC.YMax();
}

// Container miteinander verschneiden und gemeinsame Fläche liefern -----------
ObjContainer & EXPORT02 ObjContainer :: operator & (ObjContainer &OC) 
{
	if (XMin() < OC.XMin()) XMin() = OC.XMin();
	if (XMax() > OC.XMax()) XMax() = OC.XMax();
	if (YMin() < OC.YMin()) YMin() = OC.YMin();
	if (YMax() > OC.YMax()) YMax() = OC.YMax();

return *this;
}


void EXPORT02 ObjContainer :: operator &= (ObjContainer &OC) 
{
	if (XMin() < OC.XMin()) XMin() = OC.XMin();
	if (XMax() > OC.XMax()) XMax() = OC.XMax();
	if (YMin() < OC.YMin()) YMin() = OC.YMin();
	if (YMax() > OC.YMax()) YMax() = OC.YMax();
}


// Liefert, ob der erste der ObjContainer vollständig innerhalb des 
// Zweiten liegt
bool EXPORT02 operator < (ObjContainer &O1, ObjContainer &O2)
{
	return (O1.XMin() > O2.XMin() && O1.XMax() < O2.XMax() &&
		O1.YMin() > O2.YMin() && O1.YMax() < O2.YMax());
}

// Liefert, ob der erste der ObjContainer vollständig außerhalb des 
// Zweiten liegt
bool EXPORT02 operator > (ObjContainer &O1, ObjContainer &O2)
{
	return (O1.XMin() < O2.XMin() && O1.XMax() > O2.XMax() &&
		O1.YMin() < O2.YMin() && O1.YMax() > O2.YMax());
}

// Liefert, ob der erste der ObjContainer vollständig innerhalb des 
// Zweiten liegt (oder Gleichheit)
bool EXPORT02 operator <= (ObjContainer &O1, ObjContainer &O2)
{
	return (O1.XMin() >= O2.XMin() && O1.XMax() <= O2.XMax() &&
		O1.YMin() >= O2.YMin() && O1.YMax() <= O2.YMax());
}

// Liefert, ob der erste der ObjContainer vollständig außerhalb des 
// Zweiten liegt (oder Gleichheit)
bool EXPORT02 operator >= (ObjContainer &O1, ObjContainer &O2)
{
	return (O1.XMin() <= O2.XMin() && O1.XMax() >= O2.XMax() &&
		O1.YMin() <= O2.YMin() && O1.YMax() >= O2.YMax());
}

Ausdehnung EXPORT02 ObjContainer :: operator - (ObjContainer &OC)
{
	return Ausdehnung (((XMax()+XMin()) - (OC.XMax()+OC.XMin()))/2,
			   ((YMax()+YMin()) - (OC.YMax()+OC.YMin()))/2);
}


// ----------------------------------------------------------------------------
ObjContainer Kante :: GetCont (void) 
{
	if (_OCont) 
		return *_OCont;
	else {
	ObjContainer OC (MAXKOORD, 0, MAXKOORD, 0);

		_OCont = new ObjContainer (maxCont (OC));
		if (_OCont != NULL) 
			return *_OCont;		// für nächstes mal setzen
		return OC;
	}
}

void Kante :: SetCont (long Cont[]) 
{
	DELETE_OBJ (_OCont);
	_OCont = new ObjContainer (Cont[0], Cont[1], Cont[2], Cont[3]);
	if (_OCont == NULL) 
		db_error (EC_NOMEMORY, RC_SetContKante);
}

ObjContainer Masche :: GetCont (void) 
{
	if (_OCont) 
		return *_OCont;
	else {
	ObjContainer OC (MAXKOORD, 0, MAXKOORD, 0);

		_OCont = new ObjContainer (maxCont (OC));
		if (_OCont != NULL)
			return *_OCont;		// für nächstes mal gesetzt
		return OC;
	}
}

void Masche :: SetCont (long Cont[]) 
{
	DELETE_OBJ (_OCont);
	_OCont = new ObjContainer (Cont[0], Cont[1], Cont[2], Cont[3]);
	if (_OCont == NULL) 
		db_error (EC_NOMEMORY, RC_SetContMasche);
}


// true, wenn Punkt ungültig, sonst false -------------------------------------
/*inline*/ bool Punkt :: operator ! ()
{
	return ((_X == LONG_MAX) && (_Y == LONG_MAX));
}	

// true, wenn Punkt gültig, sonst false ---------------------------------------
/*inline*/ Punkt :: operator bool ()
{
	return ((_X != LONG_MAX) || (_Y != LONG_MAX));
}

// Virtuelle Funktionen -------------------------------------------------------
ObjTyp EXPORT02 GeoPunkt :: isA (void) { return OT_PUNKT; }
ObjTyp EXPORT02 GeoKante :: isA (void) { return OT_KANTE; }
ObjTyp EXPORT02 GeoFlaeche :: isA (void) { return OT_FLAECHE; }
ObjTyp EXPORT02 GeoKreis :: isA (void) { return OT_KREIS; }


// Konstruktor der BasisKlasse -----------------------------------------------
GeoObjekt :: GeoObjekt (GeoDB &rDB, long ON, long Id) 
		   : m_rDB(rDB)
{
	_ObjNr = ON; _Id = Id;
}


// Berechnen des Containers eines GeometrieObjektes --------------------------
// Diese Funktion müßte eigendlich als Virtuelle Funktion in der BasisKlasse
// aller GeoObjs stehen, aber da es (noch) keine BasisKlasse gibt, machen
// wir eben einen kleinen Handstand
bool GetObjContainer (GeoObjekt *pGO, ObjContainer &OC) 
{
	switch (pGO -> isA()) {
	case OT_PUNKT:
	case OT_LABEL:
	case OT_TEXT:		// #HK960116
		OC = ((GeoPunkt *)pGO) -> GetCont();
		return true;

	case OT_KANTE:
		OC = ((GeoKante *)pGO) -> GetCont();
		return true;

	case OT_FLAECHE:
		OC = ((GeoFlaeche *)pGO) -> GetCont();
		return true;

	case OT_KO:
		OC = ((KomplexObjekt *)pGO) -> GetCont();
		return true;

	case OT_KREIS:
		OC = ((GeoKreis *)pGO) -> GetCont();
		return true;
		
	case OT_UNKNOWN:
	default:        
		return false;
	}
}

#endif // defined(_FORCE_LEGACY_CODE)
