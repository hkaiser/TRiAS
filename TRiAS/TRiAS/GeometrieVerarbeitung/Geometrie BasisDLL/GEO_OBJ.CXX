// Methoden für ObjRechteck und Elementarobjekte EPunkt, EKante bzw. EFlaeche
// File: GEO_OBJ.CXX

#include "GeometrP.hxx"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



//=================================================================================================
// Methoden für OBJRECHTECK
// Konstruktoren
_GEOMETR_EXPORT ObjRechteck :: ObjRechteck (KoOrd XMin, KoOrd XMax, KoOrd YMin, KoOrd YMax)
{
	_XMin = XMin; _XMax = XMax;
	_YMin = YMin; _YMax = YMax;
}


//-------------------------------------------------------------------------------------------------
_GEOMETR_EXPORT ObjRechteck :: ObjRechteck (EPunkt Pt, Ausdehnung A)
{
	_XMin = Pt.X(); _YMin = Pt.Y();
	_XMax = Pt.X()+A.Breite();
	_YMax = Pt.Y()+A.Hoehe();
}


//-------------------------------------------------------------------------------------------------
_GEOMETR_EXPORT ObjRechteck :: ObjRechteck (EPunkt Pt1, EPunkt Pt2)
{
	_XMin = Pt1.X(); _XMax = Pt2.X();
	_YMin = Pt1.Y(); _YMax = Pt2.Y();
}


//-------------------------------------------------------------------------------------------------
_GEOMETR_EXPORT ObjRechteck :: ObjRechteck (const ObjRechteck &OC)
{
	_XMin = OC._XMin; _XMax = OC._XMax;
	_YMin = OC._YMin; _YMax = OC._YMax;
}


//-------------------------------------------------------------------------------------------------
// Memberfunktionen
// Werte, um die das umschreibende Rechteck vergrößert werden soll
ObjRechteck _GEOMETR_EXPORT ObjRechteck :: InflateCont (int Percent)
{
KoOrd dX = ((XMax()-XMin())*Percent)/200;
KoOrd dY = ((YMax()-YMin())*Percent)/200;

	return ObjRechteck (XMin()-dX, XMax()+dX, YMin()-dY, YMax()+dY);
}


//-------------------------------------------------------------------------------------------------
// umschreibendes Rechteck direkt verändern
ObjRechteck _GEOMETR_EXPORT &ObjRechteck :: ShiftCont (Ausdehnung &A)
{
	XMin() += A.Breite();
	XMax() += A.Breite();
	YMin() += A.Hoehe();
	YMax() += A.Hoehe();

	return *this;
}





//=================================================================================================
// Methoden für ElementarObjekt: EPUNKT
// Memberfunktionen
// true, wenn Punkt ungültig, d.h. beide Punktkoordinaten == LONG_MAX, sonst false
bool _GEOMETR_EXPORT EPunkt :: operator ! ()
{
	return ((_X == LONG_MAX) && (_Y == LONG_MAX));
}       


//-------------------------------------------------------------------------------------------------
// true, wenn Punkt gültig, d.h. wenigstens eine Punktkoordinate != LONG_MAX, sonst false
_GEOMETR_EXPORT EPunkt :: operator bool ()
{
	return ((_X != LONG_MAX) || (_Y != LONG_MAX));
}





//=================================================================================================
// Methoden für ElementarObjekt: EKANTE
// Konstruktoren
// Konstruktor, der direkt eine fertige Kante übergibt
_GEOMETR_EXPORT EKante :: EKante (long Size, PunktVec* SPF)
{
	_ASSERTE (Size > 0);
	_ASSERTE (SPF != 0);

	_SPF = 0;		// Stützpunktfolge
	_Size = 0;		// Anzahl der Stützpunkte
	_OCont = 0;		// Container dieser Kante
	if (Size == 0 || SPF == 0)
	{
		DEX_Error (RC_ctKante, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EKante::EKante(long Size,...)", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
	}
	else
	{
		_SPF = SPF;
		_Size = Size;
	}
}


//-------------------------------------------------------------------------------------------------
_GEOMETR_EXPORT EKante :: EKante (KoOrd x[], KoOrd y[], long size)
{
	_ASSERTE (size > 0);
	_ASSERTE (x != 0);
	_ASSERTE (y != 0);

	_SPF = 0;	// Stützpunktfolge
	_Size = 0;		// Anzahl der Stützpunkte
	_OCont = 0;	// Container dieser Kante
	if (size == 0 || x == 0 || y == 0)
	{
		DEX_Error (RC_ctKante, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EKante::EKante(KoOrd x[],...)", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
	}
	else
	{
		_SPF = new PunktVec (_Size = size);
		if (0 == _SPF)
		{
			_Size = 0;
			DEX_Error (RC_ctKante, EC_NOMEMORY);
			return;
		}
		if (0 == _SPF->VekL())	// PunktVec-Konstruktor arbeitet nicht zufriedenstellend
		{
			_SPF = 0;
			_Size = 0;
			return;				// Fehlerausschrift kam schon bei PunktVec-Konstruktor
		}
		for (long i = 0; i < size; i++)
		{
			SP(i).X() = x[i];
			SP(i).Y() = y[i];
		}
	}
}


//-------------------------------------------------------------------------------------------------
// Linie - Stützpunktfeld
// size  - Anzahl der Stützpunkte
_GEOMETR_EXPORT EKante :: EKante (PunktVec Linie[], long size)
{
	_ASSERTE (size > 0);
	_ASSERTE (Linie != 0);

	_SPF = 0;	// Stützpunktfolge
	_Size = 0;		// Anzahl der Stützpunkte
	_OCont = 0;	// Container dieser Kante
	if (size == 0 || Linie == (PunktVec *)0)
	{
		DEX_Error (RC_ctKante, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EKante::EKante(PunktVec Linie[],...)", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
	}
	else
	{
		_SPF = new PunktVec (_Size = size); // neue Kante anfordern
		if (_SPF == 0)
		{
			_Size = 0;
			DEX_Error (RC_ctKante, EC_NOMEMORY);
			return;      
		}
		if (_SPF->VekL() == 0)	// PunktVec-Konstruktor arbeitet nicht zufriedenstellend
		{
			_SPF = 0;
			_Size = 0;
			return;				// Fehlerausschrift kam schon bei PunktVec-Konstruktor
		}
		for (long i = 0; i < size; i++)
			SP(i) = (*Linie)[i];	 // Kante umkopieren
	}
}


//-------------------------------------------------------------------------------------------------
_GEOMETR_EXPORT EKante :: EKante (const EKante &newKante)
{
	_SPF = 0;	// Stützpunktfolge
	_Size = 0;		// Anzahl der Stützpunkte
	_OCont = 0;	// Container dieser Kante
	if (newKante._Size == 0 || newKante._SPF == 0)
	{
		DEX_Error (RC_ctKante, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EKante::EKante(const EKante &newKante)", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
	}
	else
	{
		_SPF = new PunktVec (_Size = newKante._Size); // Punktfeld anlegen
		if (_SPF == 0)
		{
			_Size = 0;
			DEX_Error (RC_ctKante, EC_NOMEMORY);
			return;      
		}
		if (_SPF->VekL() == 0)	// PunktVec-Konstruktor arbeitet nicht zufriedenstellend
		{
			_SPF = 0;
			_Size = 0;
			return;				// Fehlerausschrift kam schon bei PunktVec-Konstruktor
		}
		for (long i = 0; i < newKante._Size; i++)
			SP(i) = newKante.SP(i);
		if (newKante._OCont)
		{
			_OCont = new ObjRechteck (*newKante._OCont);
			if (_OCont == 0)
			{
				_SPF = 0;
				_Size = 0;
				DEX_Error (RC_ctKante, EC_NOMEMORY);
				return;      
			}
		}
	}
}


//-------------------------------------------------------------------------------------------------
// Memberfunktionen
void _GEOMETR_EXPORT EKante :: operator = (const EKante &newKante)
{
	if (this == &newKante) return;	  // Vorsicht nicht s=s !
	DELETE_OBJ (_SPF);
	_Size = 0;
	DELETE_OBJ (_OCont);
	if (newKante._Size == 0 || newKante._SPF == 0)
	{
		DEX_Error (RC_asKante, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EKante::operator =", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	_SPF = new PunktVec (_Size = newKante._Size);   // Punktfeld anlegen
	if (0 == _SPF)
	{
		_Size = 0;
		DEX_Error (RC_asKante, EC_NOMEMORY);
		return;      
	}
	if (0 == _SPF->VekL())	// PunktVec-Konstruktor arbeitet nicht zufriedenstellend
		return;

	for (long i = 0; i < newKante._Size; i++)
		SP(i) = newKante.SP(i);

	if (newKante._OCont)
	{
		_OCont = new ObjRechteck (*newKante._OCont);
		if (0 == _OCont)
		{
			DEX_Error (RC_asKante, EC_NOMEMORY);
			return;      
		}
	}
	else
		_OCont = 0;
}


//-------------------------------------------------------------------------------------------------
ObjRechteck _GEOMETR_EXPORT EKante :: GetCont (void)
{
	if (_OCont) 
		return *_OCont;
	else {
	ObjRechteck OC (MAXKOORD, 0, MAXKOORD, 0);

		return maxCont (OC);
	}
}


//-------------------------------------------------------------------------------------------------
ObjRechteck _GEOMETR_EXPORT EKante :: maxCont (ObjRechteck &ObjCont) {
register SpecPunkt *currP = _SPF->Vektor();

	_ASSERTE (currP != 0);

	for (long i = 0; i < _Size; i++, currP++) {
		if (currP->X() < ObjCont.XMin()) 
			ObjCont.XMin() = currP->X();
		if (currP->X() > ObjCont.XMax())
			ObjCont.XMax() = currP->X();
	}
	for (i = 0, currP = _SPF->Vektor(); i < _Size; i++, currP++) {
		if (currP->Y() < ObjCont.YMin()) 
			ObjCont.YMin() = currP->Y();
		if (currP->Y() > ObjCont.YMax())
			ObjCont.YMax() = currP->Y();
	}

return ObjCont;
}


//-------------------------------------------------------------------------------------------------
ObjRechteck _GEOMETR_EXPORT EKante :: minCont (ObjRechteck &ObjCont) {
register SpecPunkt *currP = _SPF->Vektor();

	for (long i = 0; i < _Size; i++, currP++) {
		if (currP->X() > ObjCont.XMin()) 
			ObjCont.XMin() = currP->X();
		if (currP->X() < ObjCont.XMax())
			ObjCont.XMax() = currP->X();
	}
	for (i = 0, currP = _SPF->Vektor(); i < _Size; i++, currP++) {
		if (currP->Y() > ObjCont.YMin()) 
			ObjCont.YMin() = currP->Y();
		if (currP->Y() < ObjCont.YMax())
			ObjCont.YMax() = currP->Y();
	}

return ObjCont;
}


//-------------------------------------------------------------------------------------------------
// XFeld, YFeld - Koordinatenfelder für X- und Y-Koordinaten
// size	 - enthält max. zu liefernde Koordinatenanzahl
void _GEOMETR_EXPORT EKante :: GetKante (KoOrd XFeld[], KoOrd YFeld[], long & size)
{
	_ASSERTE (XFeld != 0);
	_ASSERTE (YFeld != 0);
	_ASSERTE (size > 0);

long toCopy = longMin (size, _Size);

	for (long i = 0; i < toCopy; i++) {
		XFeld[i] = SP(i).X();
		YFeld[i] = SP(i).Y();
	}
	size = i;
}


//-------------------------------------------------------------------------------------------------
// Punkt(e) hinzufügen
void _GEOMETR_EXPORT EKante :: AddPunkt (const EKante &K, long Anzahl, long Index) {

	if (Index == -1)
	// ans Ende anhängen
		Index = _Size;
	if (Anzahl == 0 ||					// nichts einfügen
	    K._SPF == 0 ||				// keine Koordinaten gegeben
	    Index < 0 || Index > _Size) {	// ungültiger Wert
		return;							// do nothing
	} else {
	long i, j;
	PunktVec *newSPF = new PunktVec (_Size+Anzahl);

		if (newSPF == 0) {
			DEX_Error (RC_AddPunkt, EC_NOMEMORY);
			return;      
		}
		--Index;	// besser in Schleifen zu verwenden
		for (i = 0; i <= Index; i++)
			(*newSPF)[i] = SP(i);   // Beginn kopieren
		for (j = 0; j < Anzahl; i++, j++)
			(*newSPF)[i] = K.SP(j);  // Einfügen
		for (j = Index +1; i < _Size + Anzahl; i++, j++)
			(*newSPF)[i] = SP(j);
		DELETE_OBJ (_SPF);
		_Size += Anzahl;
		_SPF = newSPF;
	}
}


//-------------------------------------------------------------------------------------------------
// Aus den Vektoren x[] bzw. y[] werden die ersten Len Koordinaten in die this-Kante vor
// Stützpunktnummer -1 <= lIndex <= _Size eingefügt; wenn lIndex == -1 bzw. _Size, dann werden die
// Koordinaten am Ende angehangen
void _GEOMETR_EXPORT EKante :: AddPunkt (KoOrd x[], KoOrd y[], long Len, long Index) {

	_ASSERTE (x != 0);
	_ASSERTE (y != 0);

	if (Index == -1)
	// ans Ende anhängen
		Index = _Size;
	if (Len == 0 ||						// nichts einfügen
		Index < 0 || Index > _Size) {	// ungültiger Wert
		return;							// do nothing
	} else {
	long i, j;
	PunktVec *newSPF = new PunktVec (_Size+Len);

		if (newSPF == 0) {
			DEX_Error (RC_AddPunkt, EC_NOMEMORY);
			return;      
		}
		--Index;	// besser in Schleifen zu verwenden
		for (i = 0; i <= Index; i++)
			(*newSPF)[i] = SP(i);				// Beginn kopieren
		for (j = 0; j < Len; i++, j++)
			(*newSPF)[i] = EPunkt (x[j], y[j]);	// Einfügen
		for (j = Index +1; i < _Size + Len; i++, j++)
			(*newSPF)[i] = SP(j);
		DELETE_OBJ (_SPF);
		_Size += Len;
		_SPF = newSPF;
	}
}


//-------------------------------------------------------------------------------------------------
void _GEOMETR_EXPORT EKante :: SetCont (long Cont[])
{
	_ASSERTE (Cont != 0);

	DELETE_OBJ (_OCont);
	_OCont = new ObjRechteck (Cont[0], Cont[1], Cont[2], Cont[3]);
	if (_OCont == 0)
	{
		DEX_Error (RC_SetContKante, EC_NOMEMORY);
		return;      
	}
}


//-------------------------------------------------------------------------------------------------
// Destruktor
_GEOMETR_EXPORT EKante :: ~EKante (void) {

	DELETE_OBJ (_SPF);
	_Size = 0;
	DELETE_OBJ (_OCont);
}




//=================================================================================================
// Methoden für das ElementarObjekt: EFLAECHE
// Konstruktoren
// EFlaeche generieren, die nur aus einer Kante besteht
_GEOMETR_EXPORT EFlaeche :: EFlaeche (PunktVec* SPF, long Size)
{
	_ASSERTE (SPF != 0);

	_OCont = 0;
	if (Size <= 0) {
		_KAF = 0;
		_Size = 0;
	} else {
		_KAF = new EKante [1];   // Kantenfolge immer als Array anlegen !!
		if (_KAF == 0) {
			_Size = 0;
			DEX_Error (RC_ctMasche, EC_NOMEMORY);
			return;      
		}
		_Size = 1;
		_KAF[0].AddPunkt (SPF, Size, -1);
	}
}


//-------------------------------------------------------------------------------------------------
// EFlaeche generieren, die nur aus einer Kante besteht
_GEOMETR_EXPORT EFlaeche :: EFlaeche (KoOrd x[], KoOrd y[], long Len)
{
	_ASSERTE (x != 0);
	_ASSERTE (y != 0);

	_OCont = 0;
	if (Len <= 0) {
		_KAF = 0;
		_Size = 0;
	} else {
		_KAF = new EKante [1];   // Kantenfolge immer als Array anlegen !!
		if (_KAF == 0) {
			_Size = 0;
			DEX_Error (RC_ctMasche, EC_NOMEMORY);
			return;      
		}
		_Size = 1;
		_KAF[0].AddPunkt (x, y, Len, -1);
	}
}
	

//-------------------------------------------------------------------------------------------------
// Flaeche - Konturfeld der this-EFlaeche
// size    - Anzahl der Konturen dieser Fläche
_GEOMETR_EXPORT EFlaeche :: EFlaeche (EKante *Flaeche, int size)
{
	_OCont = 0;
	if (size == 0 || Flaeche == 0) {
		_KAF = 0;
		_Size = 0;
	} else {
		_KAF = new EKante [size];       // Konturfeld anfordern
		if (_KAF == 0) {
			_Size = 0;
			DEX_Error (RC_ctMasche, EC_NOMEMORY);
			return;      
		}
		_Size = size;
		for (int i = 0; i < size; i++)
		// Kopieren der einzelnen Konturen
			_KAF[i] = Flaeche[i];
	}
}


//-------------------------------------------------------------------------------------------------
// Kontur - Feld von Pointern auf die Konturen der this-EFlaeche
// size   - Anzahl der Konturen dieser Fläche
_GEOMETR_EXPORT EFlaeche :: EFlaeche (EKante** Kontur, int size)
{
	_OCont = 0;
	if (size == 0 || Kontur == 0)
	{
		_KAF = 0;
		_Size = 0;
	}
	else
	{
		_KAF = new EKante [size];       // Konturfeld anfordern
		if (_KAF == 0)
		{
			_Size = 0;
			DEX_Error (RC_ctMasche, EC_NOMEMORY);
			return;      
		}
		_Size = size;
		for (int i = 0; i < size; i++)
		// Kopieren der einzelnen Konturen
			_KAF[i] = *(Kontur[i]);
	}
}


//-------------------------------------------------------------------------------------------------
_GEOMETR_EXPORT EFlaeche :: EFlaeche (const EFlaeche &newFlaeche)
{
	if (newFlaeche._Size == 0 || newFlaeche._KAF == 0) {
		_KAF = 0;
		_Size = 0;
		_OCont = 0;
	} else {
		_KAF = new EKante [newFlaeche._Size]; // Konturenfeld anlegen
		if (_KAF == 0) {
			_Size = 0;
			DEX_Error (RC_ctMasche, EC_NOMEMORY);
			return;      
		}
		_Size = newFlaeche._Size;
		for (int i = 0; i < newFlaeche._Size; i++)
			_KAF[i] = newFlaeche._KAF[i];
		if (newFlaeche._OCont) {
			_OCont = new ObjRechteck (*newFlaeche._OCont);
			if (_OCont == 0) {
				DEX_Error (RC_ctMasche, EC_NOMEMORY);
				return;      
			}
		} else 
			_OCont = 0;
	}
}


//-------------------------------------------------------------------------------------------------
// Memberfunktionen
void _GEOMETR_EXPORT EFlaeche :: operator = (const EFlaeche &newFlaeche)
{
	if (this == &newFlaeche) return;	 // Vorsicht nicht s=s !
	if (_KAF) {
		DELETE_VEC (_KAF);
		_Size = 0;
		_KAF = 0;
	}
	DELETE_OBJ (_OCont);
	if (newFlaeche._Size == 0 || newFlaeche._KAF == (EKante *)0)
		return;

	_KAF = new EKante [newFlaeche._Size];     // Konturenfeld anlegen
	if (_KAF == 0) {
		_Size = 0;
		DEX_Error (RC_opMasche, EC_NOMEMORY);
		return;      
	}
	_Size = newFlaeche._Size;
	for (int i = 0; i < newFlaeche._Size; i++)
		_KAF[i] = newFlaeche._KAF[i];
	if (newFlaeche._OCont) {
		_OCont = new ObjRechteck (*newFlaeche._OCont);
		if (_OCont == 0) {
			DEX_Error (RC_opMasche, EC_NOMEMORY);
			return;      
		}
	} else 
		_OCont = 0;
}


//-------------------------------------------------------------------------------------------------
// liefert Gesamtanzahl der Stützpunkte
long _GEOMETR_EXPORT EFlaeche :: ASP (void) {
long cnt = 0;

	for (int i = 0; i < KantenAnz(); i++)
		cnt += KA(i).ASP();

return cnt;
}


//-------------------------------------------------------------------------------------------------
ObjRechteck _GEOMETR_EXPORT EFlaeche :: GetCont (void)
{
	if (_OCont) 
		return *_OCont;
	else {
	ObjRechteck OC (MAXKOORD, 0, MAXKOORD, 0);

		return maxCont (OC);
	}
}


//-------------------------------------------------------------------------------------------------
ObjRechteck _GEOMETR_EXPORT EFlaeche :: maxCont (ObjRechteck & OC) {

	for (int i = 0; i < _Size; i++)
		_KAF[i].maxCont (OC);

return OC;
}


//-------------------------------------------------------------------------------------------------
ObjRechteck _GEOMETR_EXPORT EFlaeche :: minCont (ObjRechteck & OC) {

	for (int i = 0; i < _Size; i++)
		_KAF[i].minCont (OC);

return OC;
}


//-------------------------------------------------------------------------------------------------
// Hinzufügen einer EFlaeche (z.B. inneres Loch in Fläche)
// Flaeche - Kantenfeld der this-EFlaeche
void _GEOMETR_EXPORT EFlaeche :: AddKante (const EFlaeche &Flaeche, int Anzahl, int Index)
{
	if (Index == -1)
	// ans Ende anhängen
		Index = _Size;
	if (Anzahl == 0 || Flaeche._KAF == 0 ||
	    Index < 0 || Index > _Size) {
		DEX_Error (RC_AddKante, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EFlaeche::AddKante(const EFlaeche &Flaeche,...)", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return;
	} else {
	int i, j;
	EKante *newKAF = new EKante [_Size + Anzahl];

		if (newKAF == 0) {
			DEX_Error (RC_AddKante, EC_NOMEMORY);
			return;      
		}
		--Index;	// besser zu verwenden
		for (i = 0; i <= Index; i++)
			newKAF[i] = _KAF[i];			// Beginn kopieren
		for (j = 0; j < Anzahl; i++, j++)
			newKAF[i] = Flaeche._KAF[j];    // Einfügen
		for (j = Index +1; i < _Size + Anzahl; i++, j++)
			newKAF[i] = _KAF[j];			// Rest kopieren
		DELETE_VEC (_KAF);
		_Size += Anzahl;
		_KAF = newKAF;
	}
}


//-------------------------------------------------------------------------------------------------
void _GEOMETR_EXPORT EFlaeche :: AddKante (KoOrd x[], KoOrd y[], long Len, int Index) {
// nur eine Kante in EFlaeche einfügen

	if (Index == -1)
	// ans Ende anhängen
		Index = _Size;
	if (Len == 0 || Index < 0 || Index > _Size) {
		DEX_Error (RC_AddKante, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EFlaeche::AddKante(KoOrd x[],...)", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return;
	} else {
	int i, j;
	EKante *newKAF = new EKante [_Size + 1];

		if (newKAF == 0) {
			DEX_Error (RC_AddKante, EC_NOMEMORY);
			return;      
		}
		--Index;	// besser zu verwenden
		for (i = 0; i <= Index; i++)
			newKAF[i] = _KAF[i];	  		// Beginn kopieren
		newKAF[i++] = EKante (x, y, Len);	// Einfügen
		for (j = Index +1; i <= _Size; i++, j++)
			newKAF[i] = _KAF[j];			// Rest kopieren
		DELETE_VEC (_KAF);
		_Size++;
		_KAF = newKAF;
	}
}


//-------------------------------------------------------------------------------------------------
// Zu einer der Kanten einer Fläche Punkt(e) hinzufügen
void _GEOMETR_EXPORT EFlaeche :: AddPunkt (const EKante &K, long KAnz, long KIndex, int MIndex) {

	if (MIndex == -1)
	// ans Ende anhängen
		MIndex = _Size;
	if (MIndex < 1 || MIndex > _Size) {
		DEX_Error (RC_AddPunkt_K, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EFlaeche::AddPunkt(const EKante &K,...)", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return;
	}
	_KAF[MIndex-1].EKante :: AddPunkt (K, KAnz, KIndex);
}


//-------------------------------------------------------------------------------------------------
// wie oben, jedoch Kante als Koordinaten gegeben
void _GEOMETR_EXPORT EFlaeche :: AddPunkt (KoOrd x[], KoOrd y[], long Len, long KIndex, int MIndex) {

	if (MIndex == -1)
	// ans Ende anhängen
		MIndex = _Size;
	if (MIndex < 1 || MIndex > _Size) {
		DEX_Error (RC_AddPunkt_K, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine EFlaeche::AddPunkt(KoOrd x[],...)", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return;
	}
	_KAF[MIndex-1].EKante :: AddPunkt (x, y, Len, KIndex);
}


//-------------------------------------------------------------------------------------------------
void _GEOMETR_EXPORT EFlaeche :: SetCont (long Cont[]) {

	_ASSERTE (Cont != 0);

	DELETE_OBJ (_OCont);
	_OCont = new ObjRechteck (Cont[0], Cont[1], Cont[2], Cont[3]);
	if (_OCont == 0)
	{
		DEX_Error (RC_SetContMasche, EC_NOMEMORY);
		return;      
	}
}


//-------------------------------------------------------------------------------------------------
// Destruktor
_GEOMETR_EXPORT EFlaeche :: ~EFlaeche (void) {

	if (_KAF) {
		DELETE_VEC (_KAF);
		_KAF = 0;
		_Size = 0;
	}
	DELETE_OBJ (_OCont);
}





//=================================================================================================
// Konstruktor der Basisklasse GEOOBJEKT
_GEOMETR_EXPORT GeoObjekt :: GeoObjekt (long ON, ulong Id) {

	_ObjNr = ON; _Id = Id;
}
