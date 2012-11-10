// Methoden für Klasse ObjektGeometrie
// File: ObjGeom.cxx
// H. Kaiser, W. Mörtl

#include "GeometrP.hxx"

#include "datbank.hxx"	// FehlerhaftesObjekt()
#include "zeichnen.hxx"	// PointSymbolSize()

#include <initguid.h>	// wird für objgguid.h benötigt
#include "objgguid.h"	// IID_IInitObjektGeometrie, IID_IObjektGeometrie


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


// ------------------------------------------------------------------------------------------------
// IUnknown-Interface
// Reih-um-Abfrage der (derzeit 3) Interfaces
STDMETHODIMP ObjektGeometrie :: QueryInterface (REFIID riid, LPVOID* ppvObj)
{
	if (riid == IID_IUnknown)
		*ppvObj = this;
	else if (riid == IID_IInitObjektGeometrie)
		*ppvObj = m_pOGInit;
	else if (riid == IID_IObjektGeometrie)
		*ppvObj = m_pOGFunc;
	else
		return E_NOINTERFACE;

	LPUNKNOWN(*ppvObj)->AddRef();

	return NOERROR;
}


// ------------------------------------------------------------------------------------------------
STDMETHODIMP_ (ULONG) ObjektGeometrie :: AddRef (void)
{
//TX_TRACE1 ("AddRef zu %ld\n", m_dwRefCnt + 1);
	return ++m_dwRefCnt;
}


// ------------------------------------------------------------------------------------------------
STDMETHODIMP_ (ULONG) ObjektGeometrie :: Release (void)
{
//TX_TRACE1 ("Release zu %ld\n", m_dwRefCnt - 1);
	if (--m_dwRefCnt == 0)
	{
		if (m_pFEnd) m_pFEnd();
		delete this;
		return 0L;
	}

	return m_dwRefCnt;
}



//-------------------------------------------------------------------------------------------------
// Konstruktor
ObjektGeometrie :: ObjektGeometrie (long lNewONr, DESTROYNOTIFYPROC* pFcn)
{
//TX_TRACE ("Konstruktor\n");
	m_dwRefCnt = 0;
	m_pFEnd = pFcn;
	m_pOGInit = 0;
	m_pOGFunc = 0;
	
	dwSize = sizeof (OBJGEOMETRIE);
	lONr = lNewONr;	// Objektnummer
	lIdent = 0;		// Identifikator
	iObjTyp = 0;	// ObjektTyp (Punkt, Kante, Fläche, ...)
	iFlags = 0;		// Modi von ModGI
	lCnt = 0;		// Gesamtanzahl der Stützpunkte (Größe der Koordinatenfelder)
	iKCnt = 0;		// Größe des Konturfeldes
	pdblX = 0;		// Feld der x-Koordinaten (double* / KoOrd*)
	pdblY = 0;		// Feld der y-Koordinaten (double* / KoOrd*)
	plCnt = 0;		// Anzahl der Stützpunkte in Konturen
}


//-------------------------------------------------------------------------------------------------
// Destruktor
_GEOMETR_EXPORT ObjektGeometrie :: ~ObjektGeometrie (void)
{
//TX_TRACE ("Destruktor\n");
	DELETE_VEC (pdblX);
	DELETE_VEC (pdblY);
	DELETE_VEC (plCnt);

	DELETE_OBJ (m_pOGInit);
	DELETE_OBJ (m_pOGFunc);
}


//-------------------------------------------------------------------------------------------------
// leeres Objekt "ObjektGeometrie" anlegen
ObjektGeometrie* _GEOMETR_EXPORT ObjektGeometrie :: CreateInstance (LPUNKNOWN pIUnk,
																	DESTROYNOTIFYPROC* pFcn)
{
ObjektGeometrie* pOG = new ObjektGeometrie (0, pFcn);

	if (pOG == 0 || !pOG->FInit (pIUnk))
	{
		DEX_Error (RC_objgeom, EC_NOMEMORY);
		DELETE_OBJ (pOG);
		return 0;
	}

	pOG->AddRef();
	return pOG;
} // CreateInstance (LPUNKNOWN, DESTROYNOTIFYPROC*)


//-------------------------------------------------------------------------------------------------
// Objekt "ObjektGeometrie" anlegen
ObjektGeometrie* _GEOMETR_EXPORT ObjektGeometrie :: CreateInstance (long lONr)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

ObjektGeometrie* pOG = new ObjektGeometrie (lONr);

	if (pOG == 0 || !pOG->FInit() || !pOG->FInit(lONr))
	{
		DEX_Error (RC_objgeom, EC_NOMEMORY);
		DELETE_OBJ (pOG);
		return 0;
	}

	pOG->AddRef();
	return pOG;
} // CreateInstance (long)


//-------------------------------------------------------------------------------------------------
// Objekt "ObjektGeometrie" mit einem Koordinatenpaar (x,y) anlegen
ObjektGeometrie* _GEOMETR_EXPORT ObjektGeometrie :: CreateInstance (KoOrd x, KoOrd y, int iOT)
{
ObjektGeometrie* pOG = new ObjektGeometrie (0);

	if (pOG == 0 || !pOG->FInit() || !pOG->FInit(x, y, iOT))
	{
		DEX_Error (RC_objgeom, EC_NOMEMORY);
		DELETE_OBJ (pOG);
		return 0;
	}

	pOG->AddRef();
	return pOG;
} // CreateInstance (KoOrd, KoOrd, int)


//-------------------------------------------------------------------------------------------------
//
bool ObjektGeometrie :: FInit (LPUNKNOWN pIUnk)
{
	// Parameter von CreateInstance() dienen dazu, die Lebensdauer eines ObjektGeometrie-Objektes
	// von einer übergeordneten Ebene zu steuern
	m_pOGInit = CObjGeometrieInit::CreateInstance (pIUnk ? pIUnk : this, this);
	m_pOGFunc = CObjGeometrieFunkt::CreateInstance (pIUnk ? pIUnk : this, this);

	if (!m_pOGInit || !m_pOGFunc)
		return false;
	return true;
}


//---------------------------------------------------------------------------------------------
// Geometrie des lONr-Objektes bereitstellen
bool ObjektGeometrie :: FInit (long lNewONr)
{
	lONr = lNewONr;

// statistische Angaben von TRiAS holen
// da Struktur OBJGEOMETRIE am Anfang wie Struktur OBJSTATISTIK aufgebaut ist, können die
// statistischen Angaben gleich in die Struktur OBJGEOMETRIE eingetragen werden, wodurch das
// Umkopieren entfällt 
	dwSize = sizeof (OBJSTATISTIK);

	// Cast ist erforderlich, da ObjektGeometrie jetzt nicht nur mehr von tagOBJGEOMETRIE
	// sondern auch von IUnknown abgeleitet ist; DEX_GetObjGeometrie() verlangt als Parameter
	// tagOBJGEOMETRIE, am Beginn von ObjektGeometrie steht aber der IUnknown-Pointer
	if (! DEX_GetObjStatistik (*(OBJGEOMETRIE*)this))
	{
		dwSize = sizeof (OBJGEOMETRIE);
		return false;
	}

	dwSize = sizeof (OBJGEOMETRIE);

	// für wiederholten Zugriff
	DELETE_VEC (pdblX);
	DELETE_VEC (pdblY);
	DELETE_VEC (plCnt);

	if (iFlags & OGConverted)
	{
		pdblX = new double[lCnt];
		if (pdblX == 0) return false;
		pdblY = new double[lCnt];
		if (pdblY == 0) return false;
	}
	else
	{
		pdblX = new KoOrd[lCnt];
		if (pdblX == 0) return false;
		pdblY = new KoOrd[lCnt];
		if (pdblY == 0) return false;
	}

	if (iObjTyp == OT_FLAECHE)
	{
		plCnt = new long[iKCnt];
		if (plCnt == 0) return false;
	}

	if (! DEX_GetObjGeometrie (*(OBJGEOMETRIE*)this))	// Geometrie des Objektes von TRiAS holen
		return false;
	return true;

} // FInit (long lONr)


//-------------------------------------------------------------------------------------------------
// Geometrie eines neuen Objektes vom Objekttyp iOT mit dem Koordinatenpaar (x,y) anlegen
bool ObjektGeometrie :: FInit (KoOrd x, KoOrd y, int iOT)
{
	if (OT_PUNKT != iOT && OT_KANTE != iOT && OT_FLAECHE != iOT && OT_TEXT != iOT)
	{
		_ASSERTE (OT_PUNKT == iOT || OT_KANTE == iOT || OT_FLAECHE == iOT || OT_TEXT == iOT);
		return false;
	}

	iObjTyp = iOT;	// ObjektTyp
	lCnt = 1;		// Gesamtanzahl der Stützpunkte
	if (iObjTyp == OT_FLAECHE)
		iKCnt = 1;		// Größe des Konturfeldes

	// für wiederholten Zugriff
	DELETE_VEC (pdblX);
	DELETE_VEC (pdblY);
	DELETE_VEC (plCnt);

	pdblX = new KoOrd[lCnt];	// Feld der x-Koordinaten
	if (pdblX == 0) return false;
	((KoOrd*)pdblX)[0] = x;

	pdblY = new KoOrd[lCnt];	// Feld der y-Koordinaten
	if (pdblY == 0) return false;
	((KoOrd*)pdblY)[0] = y;

	if (iObjTyp == OT_FLAECHE)
	{
		plCnt = new long[iKCnt];
		if (plCnt == 0) return false;
		plCnt[0] = 1;		// Anzahl der Stützpunkte in Konturen
	}

	return true;
} // FInit (KoOrd x, KoOrd y, int iOT)


//-------------------------------------------------------------------------------------------------
// Geometrie eines neuen Objektes vom Objekttyp iOT mit den x- bzw. y-Vektoren der Länge lAnz anlegen
bool ObjektGeometrie :: FInit (KoOrd* x, KoOrd* y, long lAnz, int iOT)
{
	if (OT_PUNKT != iOT && OT_KANTE != iOT && OT_FLAECHE != iOT && OT_TEXT != iOT)
	{
		_ASSERTE (OT_PUNKT == iOT || OT_KANTE == iOT || OT_FLAECHE == iOT || OT_TEXT == iOT);
		return false;
	}

	iObjTyp = iOT;	// ObjektTyp
	lCnt = lAnz;	// Gesamtanzahl der Stützpunkte

	// für wiederholten Zugriff
	DELETE_VEC (pdblX);
	DELETE_VEC (pdblY);
	DELETE_VEC (plCnt);

	pdblX = new KoOrd[lCnt];	// Feld der x-Koordinaten
	if (pdblX == 0) return false;
	pdblY = new KoOrd[lCnt];	// Feld der y-Koordinaten
	if (pdblY == 0) return false;
	for (long i = 0; i < lCnt; i++)
	{
		((KoOrd*)pdblX)[i] = x[i];
		((KoOrd*)pdblY)[i] = y[i];
	}

	if (iObjTyp == OT_FLAECHE)
	{
		iKCnt = 1;				// Größe des Konturfeldes
		plCnt = new long[iKCnt];
		if (plCnt == 0) return false;
		plCnt[0] = lAnz;		// Anzahl der Stützpunkte in Konturen
	}

	return true;

} // FInit (KoOrd* x, KoOrd* y, long lAnz, int iOT)


// --------------------------------------------------------------------------------------------
// Punkt Pkt VOR der fortlaufenden Indexposition lIndGes (d.h. ohne Berücksichtigung von
// Konturen bei Flächenobjekten) hinzufügen; ist lIndGes == -1, wird Pkt an das Ende
// angehangen (d. h. an das Ende der letzten Kontur);
// für Flächenobjekte muß noch der Index iKontInd der Kontur angegeben werden, zu der der neue
// Punkt gehören soll, da die Angabe von lIndGes alleine dann nicht ausreichend ist, wenn
// lIndGes der 1. Index einer Kontur ist; in diesem Fall wäre nicht klar, ob Pkt der 1. Punkt
// dieser Kontur oder der letzte der vorhergehenden sein soll
bool _GEOMETR_EXPORT ObjektGeometrie :: AddPunkt (EPunkt& Pkt, long lIndGes, int iKontInd)
{
	_ASSERTE (iObjTyp == OT_KANTE || iObjTyp == OT_FLAECHE);
	_ASSERTE (lIndGes >= -1);
	_ASSERTE (lIndGes < lCnt);

	if (lIndGes < -1 || lIndGes >= lCnt ||
		(iObjTyp != OT_KANTE && iObjTyp != OT_FLAECHE))
	{
		DEX_Error (RC_AddPunkt_OG, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine ObjektGeometrie::AddPunkt(EPunkt& Pkt,...)/I", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

IndPos IP;		// nur für Flächenobjekte: Position des Index lIndGes innerhalb der betreffenden Kontur
short iKInd;	// nur für Flächenobjekte: Index der Kontur, zu der der Punkt mit dem Index lIndGes gehört

	if (iObjTyp == OT_FLAECHE &&	// Flächenobjekt und
		lIndGes >= 0)				//  nicht hinten anhängen
	{
	long lIndex;	// für Routine IndexTest(); wird hier nicht ausgewertet

		IP = IndexTest (lIndGes, iKInd, lIndex);
		if (IP == NICHTS)
		{
			DEX_Error (RC_AddPunkt_OG, EC_ILLPARS);
			MessageBox (__hWndM, "Fehlerhafter Parameter in Routine ObjektGeometrie::AddPunkt(EPunkt& Pkt,...)/II", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}
		if (IP == ERSTER)
		{								// lIndGes ist der 1. Index einer Kontur, dann müssen
			if (iKontInd != iKInd &&	//  entweder iKontInd und iKInd übereinstimmen (d.h. Pkt wird
										//   als neuer 1. Punkt der iKontInd-Kontur eingefügt)
				iKontInd != iKInd-1)	//  oder iKontInd ist um eins kleiner als iKInd (d.h. Pkt wird
										//   als letzter Punkt der iKontInd-Kontur eingefügt)
			{
				DEX_Error (RC_AddPunkt_OG, EC_ILLPARS);
				MessageBox (__hWndM, "Fehlerhafter Parameter in Routine ObjektGeometrie::AddPunkt(EPunkt& Pkt,...)/III", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
				return false;
			}
		}
		else		// IP == LETZTER oder MITTE
		{
			if (iKontInd != iKInd)		// iKontInd und iKInd müssen übereinstimmen
			{
				DEX_Error (RC_AddPunkt_OG, EC_ILLPARS);
				MessageBox (__hWndM, "Fehlerhafter Parameter in Routine ObjektGeometrie::AddPunkt(EPunkt& Pkt,...)/IV", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
				return false;
			}
		}
	}


	if (-1 == lIndGes)	// Pkt ans Ende anhängen
	{
		lIndGes = lCnt;
		IP = LETZTER;
	}

// Punkt Pkt einfügen (gilt für Linien- und Flächenobjekt)
double* pdblNewX = 0;
double* pdblNewY = 0;
KoOrd* plNewX = 0;
KoOrd* plNewY = 0;

	if (iFlags & OGConverted)	// Koordinaten im double-Format
	{
		pdblNewX = new double[lCnt+1];
		if (pdblNewX == 0) return false;
		pdblNewY = new double[lCnt+1];
		if (pdblNewY == 0) return false;

		for (long i = 0; i < lIndGes; i++)
		{
			pdblNewX[i] = ((double*)pdblX)[i];	// Beginn kopieren
			pdblNewY[i] = ((double*)pdblY)[i];
		}

		pdblNewX[lIndGes] = Pkt.X();			// Pkt einfügen
		pdblNewY[lIndGes] = Pkt.Y();
		i++;

		for (long j = lIndGes; i < lCnt+1; i++, j++)
		{
			pdblNewX[i] = ((double*)pdblX)[j];	// Rest kopieren
			pdblNewY[i] = ((double*)pdblY)[j];
		}

		DELETE_VEC (pdblX);
		DELETE_VEC (pdblY);
		pdblX = pdblNewX;
		pdblY = pdblNewY;
	}

	else						// Koordinaten im KoOrd-Format
	{
		plNewX = new KoOrd[lCnt+1];
		if (plNewX == 0) return false;
		plNewY = new KoOrd[lCnt+1];
		if (plNewY == 0) return false;

		for (long i = 0; i < lIndGes; i++)
		{
			plNewX[i] = ((KoOrd*)pdblX)[i];	// Beginn kopieren
			plNewY[i] = ((KoOrd*)pdblY)[i];
		}

		plNewX[lIndGes] = Pkt.X();			// Pkt einfügen
		plNewY[lIndGes] = Pkt.Y();
		i++;

		for (long j = lIndGes; i < lCnt+1; i++, j++)
		{
			plNewX[i] = ((KoOrd*)pdblX)[j];	// Rest kopieren
			plNewY[i] = ((KoOrd*)pdblY)[j];
		}

		DELETE_VEC (pdblX);
		DELETE_VEC (pdblY);
		pdblX = plNewX;
		pdblY = plNewY;
	}

	lCnt++;		// (Gesamt-)Anzahl der Stützpunkte


	// bei einem Flächenobjekt ist noch zusätzlich die Stützpunktanzahl und evtl. der Anfangs/Endpunkt
	// der betreffenden Kontur zu ändern
	if (iObjTyp == OT_FLAECHE)
	{
		_ASSERTE (iKontInd >= 0);

		plCnt[iKontInd]++;	// Stützpunktanzahl der betreffenden Kontur

		// wenn der neue Punkt vor dem 1. Punkt einer Kontur eingefügt werden sollte (IP == ERSTER),
		// dann kann der neue Punkt jetzt der 1. Punkt dieser Kontur (iKontInd == iKInd) oder der
		// letzte der vorhergehenden Kontur (iKontInd == iKInd-1) sein
		if (IP == ERSTER)
		{
		long lIndz;	// zusätzlicher Index

			// der neue Punkt ist jetzt der 1. Punkt dieser Kontur; deshalb den letzten Punkt dieser
			// Kontur durch den neuen 1. Punkt ersetzen
			if (iKontInd == iKInd)
				lIndz = lIndGes + plCnt[iKontInd] - 1;	// letzter Index besagter Kontur

			// der neue Punkt ist jetzt der letzte der vorhergehenden Kontur; deshalb den 1. Punkt
			// dieser Kontur durch den neuen letzten Punkt ersetzen
			else
				lIndz = lIndGes - plCnt[iKontInd] + 1;	// 1. Index besagter Kontur

			if (iFlags & OGConverted)	// Koordinaten im double-Format
			{
				((double*)pdblX)[lIndz] = ((double*)pdblX)[lIndGes];
				((double*)pdblY)[lIndz] = ((double*)pdblY)[lIndGes];
			}
			else						// Koordinaten im KoOrd-Format
			{
				((KoOrd*)pdblX)[lIndz] = ((KoOrd*)pdblX)[lIndGes];
				((KoOrd*)pdblY)[lIndz] = ((KoOrd*)pdblY)[lIndGes];
			}
		}
	}
	return true;
} // AddPunkt


// ------------------------------------------------------------------------------------------------
// lAnzahl Koordinatenpaare (x,y) vor der fortlaufenden Indexposition lIndGes (d.h. ohne Berück-
// sichtigung von Konturen bei Flächenobjekten) einfügen; ist lIndGes == -1, werden die beiden
// Vektoren x[] und y[] an das Ende angehangen; für Flächenobjekte muß noch der Index iKontInd der
// Kontur angegeben werden, zu der die neuen Punkte (x,y) gehören sollen, da die Angabe von lIndGes
// alleine dann nicht ausreichend ist, wenn lIndGes der 1. Index einer Kontur ist; in diesem Fall
// wäre nicht klar, ob die Punkte der neue Anfang dieser Kontur oder das Ende der vorhergehenden
// sein sollen
bool _GEOMETR_EXPORT ObjektGeometrie :: AddPunkt (KoOrd* x, KoOrd* y, long lAnzahl, long lIndGes,
												  int iKontInd)
{
	_ASSERTE (x != 0);
	_ASSERTE (y != 0);
	_ASSERTE (lAnzahl > 0);
	_ASSERTE (iObjTyp == OT_KANTE || iObjTyp == OT_FLAECHE);
	_ASSERTE (lIndGes >= -1);
	_ASSERTE (lIndGes < lCnt);

	if (lAnzahl <= 0 || lIndGes < -1 || lIndGes >= lCnt ||
		(iObjTyp != OT_KANTE && iObjTyp != OT_FLAECHE))
	{
		DEX_Error (RC_AddPunkt_OG, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine ObjektGeometrie::AddPunkt(KoOrd x[],...)/I", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	if (lIndGes == -1)	// x,y ans Ende anhängen	
		lIndGes = lCnt;

IndPos IP;		// nur für Flächenobjekte: Position des Index lIndGes innerhalb der betreffenden Kontur
short iKInd;	// nur für Flächenobjekte: Index der Kontur, zu der der Punkt mit dem Index lIndGes gehört

	if (iObjTyp == OT_FLAECHE)	// Flächenobjekt
	{
	long lIndex;	// für Routine IndexTest(); wird hier nicht ausgewertet

		IP = IndexTest (lIndGes, iKInd, lIndex);
		if (IP == NICHTS)
		{
			DEX_Error (RC_AddPunkt_OG, EC_ILLPARS);
			MessageBox (__hWndM, "Fehlerhafter Parameter in Routine ObjektGeometrie::AddPunkt(KoOrd x[],...)/II", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}
		if (IP == ERSTER)
		{								// lIndGes ist der 1. Index einer Kontur, dann müssen entweder
			if (iKontInd != iKInd &&	//  iKontInd und iKInd übereinstimmen (d.h. die Vektoren x,y
										//  werden als neuer Anfang der iKontInd-Kontur eingefügt) oder
				iKontInd != iKInd-1)	//  iKontInd ist um eins kleiner als iKInd (d.h. die Vektoren
										//  x,y werden am Ende der iKontInd-Kontur eingefügt)
			{
				DEX_Error (RC_AddPunkt_OG, EC_ILLPARS);
				MessageBox (__hWndM, "Fehlerhafter Parameter in Routine ObjektGeometrie::AddPunkt(KoOrd x[],...)/III", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
				return false;
			}
		}
		else		// IP == LETZTER oder MITTE
		{
			if (iKontInd != iKInd)		// iKontInd und iKInd müssen übereinstimmen
			{
				DEX_Error (RC_AddPunkt_OG, EC_ILLPARS);
				MessageBox (__hWndM, "Fehlerhafter Parameter in Routine ObjektGeometrie::AddPunkt(KoOrd x[],...)/IV", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
				return false;
			}
		}
	}


// Vektoren x[] und y[] einfügen (gilt für Linien- und Flächenobjekt)
double* pdblNewX = 0;
double* pdblNewY = 0;
KoOrd* plNewX = 0;
KoOrd* plNewY = 0;

	if (iFlags & OGConverted)	// Koordinaten im double-Format
	{
		pdblNewX = new double[lCnt+lAnzahl];
		if (pdblNewX == 0) return false;
		pdblNewY = new double[lCnt+lAnzahl];
		if (pdblNewY == 0) return false;

		for (long i = 0; i < lIndGes; i++)				// Beginn kopieren
		{
			pdblNewX[i] = ((double*)pdblX)[i];
			pdblNewY[i] = ((double*)pdblY)[i];
		}

		for (long j = 0; j < lAnzahl; i++, j++)			// Einfügen
		{
			pdblNewX[i] = x[j];
			pdblNewY[i] = y[j];
		}

		for (j = lIndGes; i < lCnt+lAnzahl; i++, j++)	// Rest kopieren
		{
			pdblNewX[i] = ((double*)pdblX)[j];
			pdblNewY[i] = ((double*)pdblY)[j];
		}

		DELETE_VEC (pdblX);
		DELETE_VEC (pdblY);
		pdblX = pdblNewX;
		pdblY = pdblNewY;
	}

	else						// Koordinaten im KoOrd-Format
	{
		plNewX = new KoOrd[lCnt+lAnzahl];
		if (plNewX == 0) return false;
		plNewY = new KoOrd[lCnt+lAnzahl];
		if (plNewY == 0) return false;

		for (long i = 0; i < lIndGes; i++)				// Beginn kopieren
		{
			plNewX[i] = ((KoOrd*)pdblX)[i];
			plNewY[i] = ((KoOrd*)pdblY)[i];
		}

		for (long j = 0; j < lAnzahl; i++, j++)			// Einfügen
		{
			plNewX[i] = x[j];
			plNewY[i] = y[j];
		}

		for (j = lIndGes; i < lCnt+lAnzahl; i++, j++)	// Rest kopieren
		{
			plNewX[i] = ((KoOrd*)pdblX)[j];
			plNewY[i] = ((KoOrd*)pdblY)[j];
		}

		DELETE_VEC (pdblX);
		DELETE_VEC (pdblY);
		pdblX = plNewX;
		pdblY = plNewY;
	}

	lCnt += lAnzahl;		// (Gesamt-)Anzahl der Stützpunkte


	// bei einem Flächenobjekt ist noch zusätzlich die Stützpunktanzahl und evtl. der Anfangs/Endpunkt
	// der betreffenden Kontur zu ändern
	if (iObjTyp == OT_FLAECHE)
	{
		plCnt[iKontInd] += lAnzahl;	// Stützpunktanzahl der betreffenden Kontur

		// wenn die neuen Punkte vor dem 1. Punkt einer Kontur eingefügt werden sollten (IP == ERSTER),
		// dann können diese neuen Punkte jetzt der neue Anfang dieser Kontur (iKontInd == iKInd) oder
		// das Ende der vorhergehenden Kontur (iKontInd == iKInd-1) sein
		if (IP == ERSTER)
		{
		long lIndz;	// zusätzlicher Index

			// die neuen Punkte sind jetzt der neue Anfang dieser Kontur; deshalb den letzten Punkt
			// dieser Kontur durch den neuen 1. Punkt ersetzen
			if (iKontInd == iKInd)
				lIndz = lIndGes + plCnt[iKontInd] - 1;	// letzter Index besagter Kontur

			// die neuen Punkte sind jetzt das Ende der vorhergehenden Kontur; deshalb den 1. Punkt
			// dieser Kontur durch den neuen letzten Punkt ersetzen
			else
				lIndz = lIndGes - plCnt[iKontInd] + 1;	// 1. Index besagter Kontur

			if (iFlags & OGConverted)	// Koordinaten im double-Format
			{
				((double*)pdblX)[lIndz] = ((double*)pdblX)[lIndGes];
				((double*)pdblY)[lIndz] = ((double*)pdblY)[lIndGes];
			}
			else						// Koordinaten im KoOrd-Format
			{
				((KoOrd*)pdblX)[lIndz] = ((KoOrd*)pdblX)[lIndGes];
				((KoOrd*)pdblY)[lIndz] = ((KoOrd*)pdblY)[lIndGes];
			}
		}
	}

	return true;

} // AddPunkt


// ------------------------------------------------------------------------------------------------
// die Vektoren x, y der Länge lSize als iKontInd-te Innenkontur einfügen (der KonturIndex für
// Innenkonturen beginnt bei 1, die Außenkontur hat den KonturIndex 0); gilt iKontInd == -1 bzw.
// iKontInd > iKCnt, wird die neue Innenkontur hinten angehangen
bool _GEOMETR_EXPORT ObjektGeometrie :: AddKante (KoOrd* x, KoOrd* y, long lSize, int iKontInd)
{
	_ASSERTE (OT_FLAECHE == iObjTyp);
	_ASSERTE (x != 0);
	_ASSERTE (y != 0);
	_ASSERTE (iKontInd >= -1);
	_ASSERTE (iKontInd != 0);

	if (-1 == iKontInd || iKontInd > iKCnt)	// als letzte Innenkontur anhängen
		iKontInd = iKCnt;

	if (0 >= lSize || 0 > iKontInd)
	{
		DEX_Error (RC_objgeom, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine ObjektGeometrie::AddKante", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

long lSPAvor = 0;	// Anzahl der Stützpunkte vor der Einfügestelle

	if (iKontInd == iKCnt)
		lSPAvor = lCnt;
	else
		for (int i = 0; i < iKontInd; i++)
			lSPAvor += plCnt[i];

// Innenkontur einfügen
double* pdblNewX = 0;
double* pdblNewY = 0;
KoOrd* plNewX = 0;
KoOrd* plNewY = 0;

	if (iFlags & OGConverted)	// Koordinaten im double-Format
	{
		pdblNewX = new double[lCnt+lSize];
		if (0 == pdblNewX) return false;
		pdblNewY = new double[lCnt+lSize];
		if (0 == pdblNewY) return false;

		for (long l1 = 0; l1 < lSPAvor; l1++)
		{
			pdblNewX[l1] = ((double*)pdblX)[l1];	// Beginn kopieren
			pdblNewY[l1] = ((double*)pdblY)[l1];
		}

		for (long l2 = 0; l2 < lSize; l1++, l2++)	// Innenkontur einfügen
		{
			pdblNewX[l1] = x[l1];
			pdblNewY[l1] = y[l1];
		}

		for (long l3 = lSPAvor; l3 < lCnt; l1++, l3++)
		{
			pdblNewX[l1] = ((double*)pdblX)[l3];	// Rest kopieren
			pdblNewY[l1] = ((double*)pdblY)[l3];
		}

		DELETE_VEC (pdblX);
		DELETE_VEC (pdblY);
		pdblX = pdblNewX;
		pdblY = pdblNewY;
	}

	else						// Koordinaten im KoOrd-Format
	{
		plNewX = new KoOrd[lCnt+lSize];
		if (0 == plNewX) return false;
		plNewY = new KoOrd[lCnt+lSize];
		if (0 == plNewY) return false;

		for (long l1 = 0; l1 < lSPAvor; l1++)
		{
			plNewX[l1] = ((KoOrd*)pdblX)[l1];		// Beginn kopieren
			plNewY[l1] = ((KoOrd*)pdblY)[l1];
		}

		for (long l2 = 0; l2 < lSize; l1++, l2++)	// Innenkontur einfügen
		{
			plNewX[l1] = x[l2];
			plNewY[l1] = y[l2];
		}

		for (long l3 = lSPAvor; l3 < lCnt; l1++, l3++)
		{
			plNewX[l1] = ((KoOrd*)pdblX)[l3];		// Rest kopieren
			plNewY[l1] = ((KoOrd*)pdblY)[l3];
		}

		DELETE_VEC (pdblX);
		DELETE_VEC (pdblY);
		pdblX = plNewX;
		pdblY = plNewY;
	}


// Stützpunktanzahl der einzelnen Konturen korrigieren
long* plCntNew = 0;

	plCntNew = new long[iKCnt+1];
	if (0 == plCntNew) return false;

	for (int i = iKCnt; i > iKontInd; i--)
		plCntNew[i] = plCnt[i-1];

	plCntNew[iKontInd] = lSize;

	for (i = iKontInd-1; i >= 0; i--)
		plCntNew[i] = plCnt[i];

	DELETE_VEC (plCnt);
	plCnt = plCntNew;

	iKCnt++;					// Anzahl der Konturen korrigieren
	lCnt += lSize;				// Gesamtanzahl der Stützpunkte korrigieren

	return true;

} // AddKante


// --------------------------------------------------------------------------------------------
// Die Punkte vom Anfangsindex lAnfId bis einschließlich zum Endindex lEndId aus der
// ObjektGeometrie pIOG werden an das Ende der this-ObjektGeometrie (d. h. nach der letzten
// Kontur!) angehangen;
// für MD == MOVEDIR_UP wird die zu übernehmende Punktefolge aufsteigend, sonst absteigend
// durchlaufen; ist pIOG eine Fläche, kann bei der Übernahme u.U. das "Konturschloß" passiert
// werden (analoges gilt, wenn pIOG eine geschlossene Linie ist)
bool _GEOMETR_EXPORT ObjektGeometrie :: AddKantenTeil (IObjektGeometrie* pIOG, long lAnfId,
													   long lEndId, MoveDir MD)
{
	_ASSERTE (iObjTyp == OT_KANTE || iObjTyp == OT_FLAECHE);
	_ASSERTE (pIOG != 0);

bool bFormat1 = iFlags & OGConverted;		// this-Koordinaten liegen im double- (true) bzw. 
											// KoOrd-Format (false) vor
short iFlags2;				// Parameter von
void* pdblX2; void* pdblY2;	//  pIOG

	pIOG->GetFlags (&iFlags2);
	pIOG->GetX (&pdblX2);
	pIOG->GetY (&pdblY2);

bool bFormat2 = iFlags2 & OGConverted;	// pIOG-Koordinaten liegen im double- (true) bzw. 
										// KoOrd-Format (false) vor

	if (0 == pIOG ||
		(!bFormat1 && bFormat2))	// this-Koordinaten imKoOrd-Format und pIOG-Koordinaten im
	{								// double-Format
		DEX_Error (RC_AddKantenTeil, EC_ILLPARS);
		MessageBox (__hWndM, "Fehlerhafter Parameter in Routine ObjektGeometrie::AddKantenTeil", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

long lAnzahl = labs (lEndId - lAnfId) + 1;		// Anzahl der anzuhängenden Punkte

// nachfolgend wird der Fall berücksichtigt, daß pIOG eine Fläche ist und die übergebenden
// Parameter so stehen, daß das "Konturschloß" passiert werden muß
short iOT2;			// Objekttyp von pIOG
long lFirstInd = 0;	// wenn pIOG eine Linie ist: erster Index der Linie
					// wenn pIOG eine Fläche ist: erster Index der Kontur, zu der lAnfId gehört
long lAnz;			// wenn pIOG eine Linie ist: Gesamtstützpunktanzhl
					// wenn pIOG eine Fläche ist: Stützpunktanzahl der Kontur, zu der lAnfId
					// gehört
					
	pIOG->GetCnt (&lAnz);
	pIOG->GetObjTyp (&iOT2);

	if (OT_KANTE == iOT2)
	{
	bool bOpen = true;	// pIOG ist eine offene (true) bzw. geschlossene (false) Linie

		if (bFormat2)
		{
			if (((double*)pdblX2)[0] == ((double*)pdblX2)[lAnz-1] &&
				((double*)pdblY2)[0] == ((double*)pdblY2)[lAnz-1])
				bOpen = false;
		}
		else
		{
			if (((KoOrd*)pdblX2)[0] == ((KoOrd*)pdblX2)[lAnz-1] &&
				((KoOrd*)pdblY2)[0] == ((KoOrd*)pdblY2)[lAnz-1])
				bOpen = false;
		}

		if (!bOpen &&									// geschlossene Linie
			((MOVEDIR_UP == MD && lAnfId > lEndId) ||
			(MOVEDIR_DOWN == MD && lAnfId < lEndId)))	// Anfangs-/Endpunkt wird bei einer
			lAnzahl = lAnz - labs (lEndId - lAnfId);	// geschlossenen Linie durchlaufen
	}

	else if (OT_FLAECHE == iOT2 &&
		((MOVEDIR_UP == MD && lAnfId > lEndId) ||
		(MOVEDIR_DOWN == MD && lAnfId < lEndId)))	// "Konturschloß"
	{
	// zuerst muß geklärt werden, zu welcher pIOG-Kontur der Anfangsindex lAnfId gehört
	short iKInd;	// Index der Kontur, zu der der Punkt mit dem Index lAnfId gehört
	long lIndex;	// für Routine IndexTest(); wird hier nicht ausgewertet
	IndPos IP;		// für Routine IndexTest(); wird hier nicht ausgewertet

		pIOG->IndexTest (lAnfId, &iKInd, &lIndex, &IP);

	long* plK2;	// Anzahl der Stützpunkte in den einzelnen Konturen

		pIOG->GetLPCnt (&plK2);
		lAnzahl = plK2[iKInd] - labs (lEndId - lAnfId);
		lAnz = plK2[iKInd];
		for (int i = 0; i < iKInd; i++) 
			lFirstInd += plK2[i]; 
	}

double* pdblNewX = 0;
double* pdblNewY = 0;
KoOrd* plNewX = 0;
KoOrd* plNewY = 0;

	if (bFormat1)				// this-Koordinaten im double-Format
	{
		pdblNewX = new double[lCnt+lAnzahl];
		if (pdblNewX == 0) return false;
		pdblNewY = new double[lCnt+lAnzahl];
		if (pdblNewY == 0) return false;

		for (long i = 0; i < lCnt; i++)			// this-ObjektGeometrie kopieren
		{
			pdblNewX[i] = ((double*)pdblX)[i];
			pdblNewY[i] = ((double*)pdblY)[i];
		}

	long j = lAnfId;

		if (MOVEDIR_UP == MD)					// Anhängen
			for (; i < lCnt + lAnzahl; i++)			// vorwärts übernehmen
			{
				if (bFormat2)
				{
					pdblNewX[i] = ((double*)pdblX2)[j];
					pdblNewY[i] = ((double*)pdblY2)[j];
				}
				else
				{
					pdblNewX[i] = ((KoOrd*)pdblX2)[j];
					pdblNewY[i] = ((KoOrd*)pdblY2)[j];
				}
				(j < lAnz-1) ? (j++) : (j = lFirstInd + 1);
			}
		else
			for (; i < lCnt + lAnzahl; i++)			// rückwärts übernehmen
			{
				if (bFormat2)
				{
					pdblNewX[i] = ((double*)pdblX2)[j];
					pdblNewY[i] = ((double*)pdblY2)[j];
				}
				else
				{
					pdblNewX[i] = ((KoOrd*)pdblX2)[j];
					pdblNewY[i] = ((KoOrd*)pdblY2)[j];
				}
				(j > lFirstInd) ? (j--) : (j = lFirstInd + lAnz - 2);
			}

		DELETE_VEC (pdblX);
		DELETE_VEC (pdblY);
		pdblX = pdblNewX;
		pdblY = pdblNewY;
	}

	else						// this-Koordinaten im KoOrd-Format
	{
		plNewX = new KoOrd[lCnt+lAnzahl];
		if (plNewX == 0) return false;
		plNewY = new KoOrd[lCnt+lAnzahl];
		if (plNewY == 0) return false;

		for (long i = 0; i < lCnt; i++)			// this-ObjektGeometrie kopieren
		{
			plNewX[i] = ((KoOrd*)pdblX)[i];
			plNewY[i] = ((KoOrd*)pdblY)[i];
		}

	long j = lAnfId;

		if (MOVEDIR_UP == MD)					// Anhängen
			for (; i < lCnt + lAnzahl; i++)			// vorwärts übernehmen
			{
				plNewX[i] = ((KoOrd*)pdblX2)[j];
				plNewY[i] = ((KoOrd*)pdblY2)[j];
				(j < lAnz-1) ? (j++) : (j = lFirstInd+1);
			}
		else
			for (; i < lCnt + lAnzahl; i++)			// rückwärts übernehmen
			{
				plNewX[i] = ((KoOrd*)pdblX2)[j];
				plNewY[i] = ((KoOrd*)pdblY2)[j];
				(j > lFirstInd) ? (j--) : (j = lFirstInd + lAnz - 2);
			}

		DELETE_VEC (pdblX);
		DELETE_VEC (pdblY);
		pdblX = plNewX;
		pdblY = plNewY;
	}

	lCnt += lAnzahl;		// (Gesamt-)Anzahl der Stützpunkte
	if (OT_FLAECHE == iObjTyp)
	{
		_ASSERTE (plCnt != 0);

		plCnt[iKCnt-1] += lAnzahl;	// Stützpunktanzahl der letzten Kontur
	}

	return true;

} // AddKantenTeil


//---------------------------------------------------------------------------------------------
// Punkt mit der fortlaufenden Indexposition lIndGes (d.h. ohne Berücksichtigung von Konturen
// bei Flächenobjekten) löschen; für bEqVertDel = true/false wird der koordinatengleiche
// Stützpunkt des "Konturschlosses" bei Flächenobjekten ebenfalls/nicht gelöscht;
// in iKontInd wird der Index der Kontur zurückgegeben, aus der der Punkt gelöscht wurde (bei
// Linienobjekten wird -1 zurückgegeben)
bool _GEOMETR_EXPORT ObjektGeometrie :: SubPunkt (long lIndGes, bool bEqVertDel,
												  short& iKontInd)
{
	_ASSERTE (iObjTyp == OT_KANTE || iObjTyp == OT_FLAECHE);
	_ASSERTE (lIndGes >= 0);
	_ASSERTE (lIndGes < lCnt);

	if (lIndGes < 0 || lIndGes >= lCnt ||
		(iObjTyp != OT_KANTE && iObjTyp != OT_FLAECHE))
		return false;

IndPos IP;			// nur für Flächenobjekt: Position des Index lIndGes innerhalb der
					//  betreffenden Kontur

	iKontInd = -1;	// nur für Flächenobjekt: Index der Kontur, zu der der Punkt mit dem Index
					//  lIndGes gehört

	if (OT_FLAECHE == iObjTyp)	// Flächenobjekt
	{
	long lIndex;	// für Routine IndexTest(); wird hier nicht ausgewertet

		IP = IndexTest (lIndGes, iKontInd, lIndex);
		if (NICHTS == IP) return false;
	}


// Punkt löschen (durch Auslassen beim Umkopieren)
double* pdblNewX = 0;
double* pdblNewY = 0;
KoOrd* plNewX = 0;
KoOrd* plNewY = 0;

	if (iFlags & OGConverted)	// Koordinaten im double-Format
	{
		pdblNewX = new double[lCnt-1];
		if (pdblNewX == 0) return false;
		pdblNewY = new double[lCnt-1];
		if (pdblNewY == 0) return false;

		for (long i = 0; i < lIndGes; i++)
		{
			pdblNewX[i] = ((double*)pdblX)[i];		// Beginn kopieren
			pdblNewY[i] = ((double*)pdblY)[i];
		}

		for (; i < lCnt-1; i++)
		{
			pdblNewX[i] = ((double*)pdblX)[i+1];	// Rest kopieren
			pdblNewY[i] = ((double*)pdblY)[i+1];
		}

		DELETE_VEC (pdblX);
		DELETE_VEC (pdblY);
		pdblX = pdblNewX;
		pdblY = pdblNewY;
	}

	else						// Koordinaten im KoOrd-Format
	{
		plNewX = new KoOrd[lCnt-1];
		if (plNewX == 0) return false;
		plNewY = new KoOrd[lCnt-1];
		if (plNewY == 0) return false;

		for (long i = 0; i < lIndGes; i++)
		{
			plNewX[i] = ((KoOrd*)pdblX)[i];		// Beginn kopieren
			plNewY[i] = ((KoOrd*)pdblY)[i];
		}

		for (; i < lCnt-1; i++)
		{
			plNewX[i] = ((KoOrd*)pdblX)[i+1];	// Rest kopieren
			plNewY[i] = ((KoOrd*)pdblY)[i+1];
		}

		DELETE_VEC (pdblX);
		DELETE_VEC (pdblY);
		pdblX = plNewX;
		pdblY = plNewY;
	}

	_ASSERTE (lCnt > 0);

	if (lCnt > 0)
		lCnt--;		// (Gesamt-)Anzahl der Stützpunkte


	// bei einem Flächenobjekt ist noch zusätzlich die Stützpunktanzahl und evtl. der Anfangs/Endpunkt
	// der betreffenden Kontur zu ändern
	if (iObjTyp == OT_FLAECHE)
	{
		_ASSERTE (plCnt[iKontInd] > 0);

		if (plCnt[iKontInd] > 0)
			plCnt[iKontInd]--;	// Stützpunktanzahl der betreffenden Kontur

		// wenn Kontur nicht mehr existiert (Stützpunktanzahl == 0), braucht der 1. und letzte
		// Stützpunkt nicht mehr in Übereinstimmung gebracht zu werden
		if (plCnt[iKontInd] == 0)
		{
			_ASSERTE (iKCnt > 0);

			if (iKCnt > 0)
				iKCnt--;
			return true;
		}

		if ((ERSTER == IP || LETZTER == IP) && bEqVertDel &&
			plCnt[iKontInd] >= 4)		// 02.11.98
		{
		long lIndz;	// zusätzlicher Index

			// wenn lIndGes der 1. Index einer Kontur ist, dann den letzten Punkt dieser Kontur
			// durch den neuen 1. Punkt ersetzen
			if (IP == ERSTER)
				lIndz = lIndGes + plCnt[iKontInd] - 1;	// letzter Index besagter Kontur

			// wenn lIndGes der letzte Index einer Kontur ist, dann den 1. Punkt dieser Kontur
			// durch den neuen letzten Punkt ersetzen
			else
			{
				lIndz = lIndGes - plCnt[iKontInd];		// 1. Index besagter Kontur
				lIndGes--;	// pdblX[lIndGes] bzw. pdblY[lIndGes] gibt es inzwischen nicht mehr
			}
		
			if (iFlags & OGConverted)	// Koordinaten im double-Format
			{
				((double*)pdblX)[lIndz] = ((double*)pdblX)[lIndGes];
				((double*)pdblY)[lIndz] = ((double*)pdblY)[lIndGes];
			}
			else						// Koordinaten im KoOrd-Format
			{
				((KoOrd*)pdblX)[lIndz] = ((KoOrd*)pdblX)[lIndGes];
				((KoOrd*)pdblY)[lIndz] = ((KoOrd*)pdblY)[lIndGes];
			}
		}
	}

	return true;

} // SubPunkt


// ------------------------------------------------------------------------------------------------
// Innenkontur(en) einer Fläche löschen
// 1 <= iAnzahl < iKCnt Innenkonturen werden ab Konturindex 1 <= iKontInd < iKCnt gelöscht;
// für iKontInd == -1 wird letzte Innenkontur gelöscht; sollen mehr Innenkonturen gelöscht
// werden als vorhanden sind, werden die Innenkonturen ab iKontInd bis zur letzten gelöscht
bool _GEOMETR_EXPORT ObjektGeometrie :: SubKante (int iAnzahl, int iKontInd)
{
	if (1 >= iKCnt) return false;	// keine Innenkontur vorhanden

	_ASSERTE (OT_FLAECHE == iObjTyp);
	_ASSERTE (iAnzahl >= 1);
	_ASSERTE (iAnzahl < iKCnt);
	_ASSERTE (iKontInd >= -1);
	_ASSERTE (iKontInd != 0);
	_ASSERTE (iKontInd < iKCnt);

	if (iKontInd == -1)				   // letzte Innenkontur löschen
		iKontInd = iKCnt - 1;
	if (iKCnt - iKontInd < iAnzahl)		// es sollen mehr Innenkonturen gelöscht werden
		iAnzahl = iKCnt - iKontInd;		//  als ab iKontInd noch vorhanden sind
	if (iAnzahl < 1 || iAnzahl > iKCnt - 1 ||
	    iKontInd < 1 || iKontInd > iKCnt - 1)
		return false;

long lSPAvor = 0;	// Anzahl der Stützpunkte vor dem zu löschenden Bereich und
long lSPAim = 0;	//  innerhalb des zu löschenden Bereiches

	for (int i = 0; i < iKontInd; i++)
		lSPAvor += plCnt[i];
	for (; i < iKontInd+iAnzahl; i++)
		lSPAim += plCnt[i];

// Innenkontur(en) löschen (durch Auslassen beim Umkopieren)
double* pdblNewX = 0;
double* pdblNewY = 0;
KoOrd* plNewX = 0;
KoOrd* plNewY = 0;

	if (iFlags & OGConverted)	// Koordinaten im double-Format
	{
		pdblNewX = new double[lCnt-lSPAim];
		if (0 == pdblNewX) return false;
		pdblNewY = new double[lCnt-lSPAim];
		if (0 == pdblNewY) return false;

		for (long l = 0; l < lSPAvor; l++)
		{
			pdblNewX[l] = ((double*)pdblX)[l];			// Beginn kopieren
			pdblNewY[l] = ((double*)pdblY)[l];
		}

		for (; l < lCnt - lSPAim; l++)
		{
			pdblNewX[l] = ((double*)pdblX)[l+lSPAim];	// Rest kopieren
			pdblNewY[l] = ((double*)pdblY)[i+lSPAim];
		}

		DELETE_VEC (pdblX);
		DELETE_VEC (pdblY);
		pdblX = pdblNewX;
		pdblY = pdblNewY;
	}

	else						// Koordinaten im KoOrd-Format
	{
		plNewX = new KoOrd[lCnt-lSPAim];
		if (0 == plNewX) return false;
		plNewY = new KoOrd[lCnt-lSPAim];
		if (0 == plNewY) return false;

		for (long l = 0; l < lSPAvor; l++)
		{
			plNewX[l] = ((KoOrd*)pdblX)[l];			// Beginn kopieren
			plNewY[l] = ((KoOrd*)pdblY)[l];
		}

		for (; l < lCnt - lSPAim; l++)
		{
			plNewX[l] = ((KoOrd*)pdblX)[l+lSPAim];	// Rest kopieren
			plNewY[l] = ((KoOrd*)pdblY)[l+lSPAim];
		}

		DELETE_VEC (pdblX);
		DELETE_VEC (pdblY);
		pdblX = plNewX;
		pdblY = plNewY;
	}

	for (i = iKontInd; i < iKCnt-iAnzahl; i++)
		plCnt[i] = plCnt[i+iAnzahl];	// Stützpunktanzahl der einzelnen Konturen korrigieren

	iKCnt -= iAnzahl;					// Anzahl der Konturen korrigieren
	_ASSERTE (iKCnt >= 1);				// Fläche muß mindestens die Außenkontur besitzen

	lCnt -= lSPAim;						// Gesamtanzahl der Stützpunkte korrigieren
	_ASSERTE (lCnt >= 3);				// Fläche muß mindestens 4 Stützpunkte besitzen
	
	return true;

} // SubKante


// ------------------------------------------------------------------------------------------------
// Punkt mit Index lIndGes durch Pkt ersetzen
bool _GEOMETR_EXPORT ObjektGeometrie :: ModPunkt (EPunkt& Pkt, long lIndGes)
{
	_ASSERTE (lIndGes >= 0);
	_ASSERTE (lIndGes < lCnt);

	if (lIndGes < 0 || lIndGes >= lCnt)
		return false;

	if (iFlags & OGConverted)	// Koordinaten im double-Format
	{
		((double*)pdblX)[lIndGes] = Pkt.X();
		((double*)pdblY)[lIndGes] = Pkt.Y();
	}
	else						// Koordinaten im KoOrd-Format
	{
		((KoOrd*)pdblX)[lIndGes] = Pkt.X();
		((KoOrd*)pdblY)[lIndGes] = Pkt.Y();
	}
	                                                        
	// wenn der Schloßpunkt einer Flächenkontur geändert wurde, dann noch den "anderen"
	// koordinatengleichen Punkt ändern
	if (iObjTyp == OT_FLAECHE)
	{
	short iKontNr;		// Nummer der Kontur, zu der der geänderte Punkt gehört
	long lInd;			// wird hier nicht ausgewertet
	IndPos IP = IndexTest (lIndGes, iKontNr, lInd);
	long lIndz = -1;	// Index für zusätzliche Modifikation
	
		if (IP == ERSTER || IP == LETZTER)
		{
			if (IP == ERSTER)
				lIndz = lIndGes + plCnt[iKontNr] - 1;	// letzter Index der aktuellen Kontur
			else
				lIndz = lIndGes - plCnt[iKontNr] + 1;	// erster Index der aktuellen Kontur

			if (iFlags & OGConverted)	// Koordinaten im double-Format
			{
				((double*)pdblX)[lIndz] = Pkt.X();
				((double*)pdblY)[lIndz] = Pkt.Y();
			}
			else
			{
				((KoOrd*)pdblX)[lIndz] = Pkt.X();
				((KoOrd*)pdblY)[lIndz] = Pkt.Y();
			}
		}
	}

	return true;

} // ModPunkt


// --------------------------------------------------------------------------------------------
// Index lInd des Stützpunktes (lX, lY) innerhalb des this-Objektes bestimmen; gehört der Punkt
// zum this-Objekt, wird true zurückgegeben, sonst false
bool _GEOMETR_EXPORT ObjektGeometrie :: GetVertexIndex (KoOrd lX, KoOrd lY, long& lInd)
{
	_ASSERTE ((KoOrd*)pdblX != 0);
	_ASSERTE ((KoOrd*)pdblY != 0);
	_ASSERTE (lCnt > 0);

	for (long i = 0; i < lCnt; i++)
		if (((KoOrd*)pdblX)[i] == lX && ((KoOrd*)pdblY)[i] == lY)
		{
			lInd = i;
			return true;
		}

	return false;

} // GetVertexIndex


// --------------------------------------------------------------------------------------------
// Testen, ob Punkt (lX, lY) einer Strecke des this-Objektes näher als lEps liegt; wenn ja,
// dann Rückgabe von true, sonst false;
// in lInd wird der Index des End-Stützpunktes der betreffenden this-Strecke zurückgegeben
bool _GEOMETR_EXPORT ObjektGeometrie :: GetLineIndex (KoOrd lX, KoOrd lY, long lEps,
													  long& lInd)
{
KoOrd lDist;	// Abstand des Punktes (lX, lY) von Strecke (x1, y1, x2, y2) in Maximum-Norm

	for (long i = 0; i < lCnt-1; i++)
	{
	KoOrd x0 = ((KoOrd*)pdblX)[i];
	KoOrd y0 = ((KoOrd*)pdblY)[i];
	KoOrd x1 = ((KoOrd*)pdblX)[i+1];
	KoOrd y1 = ((KoOrd*)pdblY)[i+1];
	bool bLot = PunktAnStrecke (lX, lY, x0, y0, x1, y1, lDist);

//		if (bLot && lDist < lEps)	// #WM030505
		if (bLot)
		{
			if (lDist <= lEps)	// "<=" wurde jetzt bewusst verwendet
			{
				lInd = i + 1;	// Index zurückgeben
				return true;
			}
		}
		else
		{
			KoOrd k0 = AbstandPktPktM (lX, lY, x0, y0);
			KoOrd k1 = AbstandPktPktM (lX, lY, x1, y1);
			if (AbstandPktPktM (lX, lY, x0, y0) <= lEps ||
				AbstandPktPktM (lX, lY, x1, y1) <= lEps)
			{
				lInd = i + 1;	// Index zurückgeben
				return true;
			}
		}
	}

	return false;

} // GetLineIndex


// --------------------------------------------------------------------------------------------
// Testen, ob der Index lIndGes eines pdblX- bzw. pdblY-Vektors einer Fläche der erste, letzte
// Index bez. einer der Konturen ist bzw. innerhalb einer Kontur liegt; dann Rückgabe von
// ERSTER, LETZTER bzw. MITTE; außerdem Rückgabe des Indexes lInd innerhalb der entsprechenden
// Kontur und den Konturindex iKontInd selbst
IndPos _GEOMETR_EXPORT ObjektGeometrie :: IndexTest (long lIndGes, short& iKontInd, long& lInd)
{
	_ASSERTE (lIndGes >= 0);
	_ASSERTE (lIndGes < lCnt);
	_ASSERTE (iObjTyp == OT_FLAECHE);

	if (lIndGes < 0 || lIndGes >= lCnt || iObjTyp != OT_FLAECHE)
		return NICHTS;

long lSumm = 0;		// Anfangswert für Teilsummenbildung
		
	iKontInd = 0;	// Index der Kontur, zu der der lIndGes-Stützpunkt gehört
	if (iKCnt > 1)	// wenigstens 1 Innenkontur
		// Index der Kontur ermitteln, zu der der lIndGes-Stützpunkt gehört
		for (int i = 0; i < iKCnt; i++)
		{
			if (lIndGes >= lSumm && lIndGes < lSumm + plCnt[i]) break;
			lSumm += plCnt[i];
			iKontInd++;
		}

	lInd = lIndGes - lSumm;
		
	if (lInd == 0)
		return ERSTER;
	if (lInd == plCnt[iKontInd]-1)
		return LETZTER;
	return MITTE;

} // IndexTest


// ------------------------------------------------------------------------------------------------
// Index des vorhergehenden und nachfolgenden Stützpunktes einer Flächenkontur zu dem
// übergebenen Index lIndGes ermitteln;
// die Indizes sind auch bei mehreren Konturen fortlaufend, d.h. unabhängig von der Kontur;
// es muß jedoch beachtet werden, daß der Vorgänger des ersten Stützpunktes einer Kontur der
// vorletzte Punkt und der Nachfolger des letzten Punktes einer Kontur der zweite Punkt ist
bool _GEOMETR_EXPORT ObjektGeometrie :: IndexVorNach (long lIndGes, long& lIndv, long& lIndn)
{
	_ASSERTE (lIndGes >= 0);
	_ASSERTE (lIndGes < lCnt);
	_ASSERTE (iObjTyp == OT_FLAECHE);

	if (lIndGes < 0 || lIndGes >= lCnt || iObjTyp != OT_FLAECHE)
		return false;
		
short iKontInd;	// Index der Kontur, zu der der Punkt mit dem Index lIndGes gehört
long lIndex;	// wird hier nicht ausgewertet
IndPos IP = IndexTest (lIndGes, iKontInd, lIndex);
			
	if (IP != ERSTER)
		lIndv = lIndGes - 1;	// "echt" vorhergehender Index
	else
		lIndv = lIndGes + plCnt[iKontInd] - 2;	// Index des vorletzten Stützpunktes der Kontur
		
	if (IP != LETZTER)
		lIndn = lIndGes + 1;	// "echt" nachfolgender Index
	else
		lIndn = lIndGes - plCnt[iKontInd] + 2;	// Index des nachfolgenden Stützpunktes
	return true;

} // IndexVorNach


// --------------------------------------------------------------------------------------------
// Index des vorhergehenden Stützpunktes einer Flächenkontur zu dem übergebenen Index lIndGes
// ermitteln; die Indizes sind auch bei mehreren Konturen fortlaufend, d.h. unabhängig von der
// Kontur; es muß jedoch beachtet werden, daß der Vorgänger des ersten Stützpunktes einer
// Kontur der vorletzte Punkt und der Nachfolger des letzten Punktes einer Kontur der zweite
// Punkt ist
bool _GEOMETR_EXPORT ObjektGeometrie :: IndexVor (long lIndGes, long& lIndv)
{
	_ASSERTE (lIndGes >= 0);
	_ASSERTE (lIndGes < lCnt);
	_ASSERTE (iObjTyp == OT_FLAECHE);

	if (lIndGes < 0 || lIndGes >= lCnt || iObjTyp != OT_FLAECHE)
		return false;
		
short iKontInd;	// Index der Kontur, zu der der Punkt mit dem Index lIndGes gehört
long lIndex;	// wird hier nicht ausgewertet
IndPos IP = IndexTest (lIndGes, iKontInd, lIndex);
			
	if (IP != ERSTER)
		lIndv = lIndGes - 1;	// "echt" vorhergehender Index
	else
		lIndv = lIndGes + plCnt[iKontInd] - 2;	// Index des vorletzten Stützpunktes der Kontur
	return true;

} // IndexVor


// ------------------------------------------------------------------------------------------------
// ObjektContainer von this-ObjektGeometrie; dabei müssen die Koordinaten im KoOrd-Format vorliegen
ObjRechteck _GEOMETR_EXPORT ObjektGeometrie :: GetCont (void)
{
	if (iFlags & OGConverted)	// für Koordinaten mit double-Format ist ObjRechteck nicht bildbar
		return ObjRechteck (-1, -1, -1, -1);

KoOrd xmin = MAXKOORD;
KoOrd xmax = -1;
KoOrd ymin = MAXKOORD;
KoOrd ymax = -1;

	switch (iObjTyp)
	{
		case OT_PUNKT:
			xmin = xmax = ((KoOrd*)pdblX)[0];
			ymin = ymax = ((KoOrd*)pdblY)[0];
			break;

		case OT_KANTE:
		case OT_FLAECHE:
			{
			long lSPAnz;	// Anzahl der zu testenden Stützpunkte

			// wenn OTyp geändert wurde, ist plCnt ggf. nicht gegeben
				if (iObjTyp == OT_KANTE || NULL == plCnt)
					lSPAnz = lCnt;
				else
					lSPAnz = plCnt[0];

				for (long i = 0; i < lSPAnz; i++)
				{
					if (((KoOrd*)pdblX)[i] < xmin) xmin = ((KoOrd*)pdblX)[i];
					if (((KoOrd*)pdblX)[i] > xmax) xmax = ((KoOrd*)pdblX)[i];
					if (((KoOrd*)pdblY)[i] < ymin) ymin = ((KoOrd*)pdblY)[i];
					if (((KoOrd*)pdblY)[i] > ymax) ymax = ((KoOrd*)pdblY)[i];
				}
			}
			break;
	}
	return ObjRechteck (xmin, xmax, ymin, ymax);
} // GetCont


//-------------------------------------------------------------------------------------------------
// Richtung einer Kante bzw. Flächenkontur umorientieren; iKInd ist (nur bei Flächenobjekten) der
// Konturindex
bool _GEOMETR_EXPORT ObjektGeometrie :: OrientDreh (int iKInd)
{
	if (iObjTyp != OT_KANTE && iObjTyp != OT_FLAECHE)
		return false;

long lAnfInd = 0;	// Anfangsindex bzw.
long lAnz; 			//  Stützpunktanzahl der zu drehenden Kante bzw. Flächenkontur

	if (iObjTyp == OT_KANTE)
		lAnz = lCnt;

	else	// OT_FLAECHE
	{
		_ASSERTE (iKInd < iKCnt);

		if (iKInd >= iKCnt)
		{
			DEX_Error (RC_objgeom, EC_ILLPARS);
			MessageBox (__hWndM, "Fehlerhafter Parameter in Routine ObjektGeometrie::OrientDreh", "Achtung:", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}

		// Anfangsindex der iKInd-ten Kontur ermitteln
		if (iKInd > 0)		// eine Innenkontur
			for (int i = 0; i < iKInd; i++)
				lAnfInd += plCnt[i];

		lAnz = plCnt[iKInd];	// Stützpunktanzahl der iKInd-ten Kontur
	}

	// Kante bzw. Flächenkontur drehen
	if (iFlags & OGConverted)	// Koordinaten im double-Format
	{
		for (long k = lAnfInd; k < lAnz/2; k++)
		{
		long lInd = lAnz-k-1;
		double dX = ((double*)pdblX)[lInd];
		double dY = ((double*)pdblY)[lInd];

			((double*)pdblX)[lInd] = ((double*)pdblX)[k];
			((double*)pdblY)[lInd] = ((double*)pdblY)[k];
			((double*)pdblX)[k] = dX;
			((double*)pdblY)[k] = dY;
		}
	}
	else						// Koordinaten im KoOrd-Format
	{
		for (long k = lAnfInd; k < lAnz/2; k++)
		{
		long lInd = lAnz-k-1;
		KoOrd lX = ((KoOrd*)pdblX)[lInd];
		KoOrd lY = ((KoOrd*)pdblY)[lInd];

			((KoOrd*)pdblX)[lInd] = ((KoOrd*)pdblX)[k];
			((KoOrd*)pdblY)[lInd] = ((KoOrd*)pdblY)[k];
			((KoOrd*)pdblX)[k] = lX;
			((KoOrd*)pdblY)[k] = lY;
		}
	}

	return true;

} // OrientDreh


// --------------------------------------------------------------------------------------------
// Testen, ob für das this-Objekt das Merkmal "Geometriefehler" existiert, das einen Eintrag
// mit der Teilzeichenkette "F..: " besitzt (S_FALSE) oder nicht (S_OK)
HRESULT _GEOMETR_EXPORT ObjektGeometrie :: IsClear (void)
{
HRESULT hr = FehlerhaftesObjekt (NULL, lONr);

	if (S_FALSE == hr) hr = S_OK;		// Merkmal "Geometriefehler" existiert entweder nicht
										//  oder ist unbelegt, d.h. das Objekt ist fehlerfrei
	else if (S_OK == hr) hr = S_FALSE;	// Objekt hat einen Geometriefehler

	return hr;

} // IsClear


// --------------------------------------------------------------------------------------------
// Ermittlung der Cursorposition des Punktes (xLM, yLM) (in DB-Koordinaten) bez. des
// this-Objektes
CursPos _GEOMETR_EXPORT ObjektGeometrie :: CursorPositionAtObject (KoOrd xLM, KoOrd yLM,
												  long lEpsX, long lEpsY, long lEpsStr,
												  bool bInBorder, KoOrd& lGrabX, KoOrd& lGrabY)
{
	switch (iObjTyp)
	{
		case OT_PUNKT:
			return CursorPositionAtPoint (xLM, yLM, lEpsX, lEpsY, lGrabX, lGrabY);

		case OT_KANTE:
			return CursorPositionAtLine (xLM, yLM, lEpsX, lEpsY, lEpsStr, lGrabX, lGrabY);

		case OT_FLAECHE:
			return CursorPositionAtArea (xLM, yLM, lEpsX, lEpsY, lEpsStr, bInBorder, lGrabX,
										 lGrabY);
		default:
			break;	// alle anderen Typen (OT_TEXT, ...)
	}

	return CURSPOS_OUTSIDE;

} // CursorPositionAtObject


// --------------------------------------------------------------------------------------------
// Hilfsroutine für CursorPositionAtObject()
CursPos ObjektGeometrie :: CursorPositionAtPoint (KoOrd xLM, KoOrd yLM, long lEpsX, long lEpsY,
												  KoOrd& lGrabX, KoOrd& lGrabY)
{
KoOrd x0 = ((KoOrd*)pdblX)[0];
KoOrd y0 = ((KoOrd*)pdblY)[0];

	if (PunktInMarker (xLM, yLM, x0, y0, lEpsX, lEpsY))
	{
		lGrabX = x0;
		lGrabY = y0;

		return CURSPOS_VERTEX;
	}

	return CURSPOS_OUTSIDE;

} // CursorPositionAtPoint


// --------------------------------------------------------------------------------------------
// Hilfsroutine für CursorPositionAtObject()
CursPos ObjektGeometrie :: CursorPositionAtLine (KoOrd xLM, KoOrd yLM, long lEpsX, long lEpsY,
												 long lEpsStr, KoOrd& lGrabX, KoOrd& lGrabY)
{
	for (long i = 0; i < lCnt; i++)
	{
	KoOrd x0 = ((KoOrd*)pdblX)[i];
	KoOrd y0 = ((KoOrd*)pdblY)[i];

		if (PunktInMarker (xLM, yLM, x0, y0, lEpsX, lEpsY))
		{
			lGrabX = x0;
			lGrabY = y0;

			if (0 == i) return CURSPOS_FIRST_VERTEX;
			else if (i == lCnt-1) return CURSPOS_LAST_VERTEX;
			return CURSPOS_VERTEX;
		}

		if (0 == i)		// es müssen erst BEIDE Endpunkte einer Strecke getestet werden, bevor
			continue;	// die Strecke selbst getestet werden kann (05.03.98)

	KoOrd x1 = ((KoOrd*)pdblX)[i-1];
	KoOrd y1 = ((KoOrd*)pdblY)[i-1];
	KoOrd lDist;	// Abstand des Punktes Pkt von Strecke (x1, y1, x2, y2) in Maximum-Norm

		if (PunktAnStrecke (xLM, yLM, x0, y0, x1, y1, lDist) && lDist < lEpsStr)
		{
			lGrabX = xLM;
			lGrabY = yLM;
			return CURSPOS_LINE;
		}
	}

	return CURSPOS_OUTSIDE;

} // CursorPositionAtLine


// --------------------------------------------------------------------------------------------
// Hilfsroutine für CursorPositionAtObject();
// für bInBorder == true werden auch die Innenkonturen berücksichtigt (d.h. liegt der Cursor
// innerhalb einer Innenkontur, liegt er bez. des this-Objektes außerhalb dieses Objektes)
CursPos ObjektGeometrie :: CursorPositionAtArea (KoOrd xLM, KoOrd yLM, long lEpsX, long lEpsY,
									long lEpsStr, bool bInBorder, KoOrd& lGrabX, KoOrd& lGrabY)
{
int j = 0;		// Konturindex
long lSumm = 0;	// Teilsumme der Stützpunktanzahlen der Konturen

	for (long i = 0; i < lCnt; i++)
	{			
	KoOrd x0 = ((KoOrd*)pdblX)[i];
	KoOrd y0 = ((KoOrd*)pdblY)[i];

		if (PunktInMarker (xLM, yLM, x0, y0, lEpsX, lEpsY))
		{
			lGrabX = x0;
			lGrabY = y0;

			if (i < plCnt[0]) return CURSPOS_OUTBORDER_VERTEX;
			return CURSPOS_INBORDER_VERTEX;
		}

		if (i == lSumm)	// Abfrage erforderlich, damit erst BEIDE Stützpunkte einer Strecke
			continue;	// getestet werden, bevor die Nähe zur Strecke selbst getestet wird

		// wenn nur getestet werden soll, ob sich Cursor "in der Nähe" der Außenkontur
		// befindet, dann hier Ende
		if (!bInBorder && i >= plCnt[0])
			return CURSPOS_OUTSIDE;

		// Strecke zwischen dem letzten Stützpunkt einer Kontur und dem 1. der nächsten Kontur
		// natürlich nicht testen
		if (i == lSumm + plCnt[j])	// i steht am Anfang einer Kontur
		{
			lSumm += plCnt[j];
			j++;
			continue;		// nächstes i in der for-Schleife
		}

	KoOrd x1 = ((KoOrd*)pdblX)[i-1];
	KoOrd y1 = ((KoOrd*)pdblY)[i-1];
	KoOrd lDist;	// Abstand des Punktes Pkt von Strecke (x0, y0, x1, y1) in Maximum-Norm

		if (PunktAnStrecke (xLM, yLM, x0, y0, x1, y1, lDist) && lDist < lEpsStr)
		{
			lGrabX = xLM;
			lGrabY = yLM;
			if (i < plCnt[0]) return CURSPOS_OUTBORDER;
			return CURSPOS_INBORDER;
		}
	}

	return CURSPOS_OUTSIDE;

} // CursorPositionAtArea


// --------------------------------------------------------------------------------------------
// der Punkt(xLM, yLM) (in DB-Koordinaten), auf den die linke Maustaste zeigt, liegt in einem
// Markierungsquadrat (Kantenlänge in x- bzw. y-Richtung von m_lMBX bzw. m_lMBY) um den
// Punkt(XK, YK) einschließlich dessen Rand (true), sonst false
bool ObjektGeometrie :: PunktInMarker (KoOrd xLM, KoOrd yLM, KoOrd XK, KoOrd YK, long lEpsX,
									   long lEpsY)
{
KoOrd xmin = XK - lEpsX;
KoOrd xmax = XK + lEpsX;
KoOrd ymin = YK - lEpsY;
KoOrd ymax = YK + lEpsY;

	return (xmin <= xLM && xLM <= xmax && ymin <= yLM && yLM <= ymax);

} // PunktInMarker


// --------------------------------------------------------------------------------------------
// Test, wo sich der Punkt (xLM, yLM) (in DB-Koordinaten), auf den die linke Maustaste zeigt,
// bez. der Strecke (P1, P2) liegt; in lAbst wird der Abstand nach Maximum-Norm zurückgegeben;
// läßt sich von Pkt auf die Strecke das Lot fällen, wird true zurückgegeben, sonst false
bool ObjektGeometrie :: PunktAnStrecke (KoOrd xLM, KoOrd yLM, KoOrd x1, KoOrd y1, KoOrd x2,
										KoOrd y2, KoOrd& lAbst)
{
EPunkt LPkt;	// für Routine LotPktStrecke(): wird hier aber nicht ausgewertet

	return Strecke(x1, y1, x2, y2).LotPktStrecke (EPunkt(xLM, yLM), lAbst, LPkt);

} // PunktAnStrecke


// --------------------------------------------------------------------------------------------
// Test, ob Cursor (gegeben durch xLM und yLM) innerhalb (return-Wert: true) oder außerhalb
// (false) eines Markers des this-Objektes liegt
bool _GEOMETR_EXPORT ObjektGeometrie :: CursorInMarker (KoOrd xLM, KoOrd yLM, long lEpsX,
													  long lEpsY, KoOrd& lGrabX, KoOrd& lGrabY)
{
	for (long i = 0; i < lCnt; i++)
	{
	KoOrd x = ((KoOrd*)pdblX)[i];
	KoOrd y = ((KoOrd*)pdblY)[i];

		if (PunktInMarker (xLM, yLM, x, y, lEpsX, lEpsY))
		{
			lGrabX = x;
			lGrabY = y;
			return true;
		}
	}

	return false;

} // CursorInMarker


// --------------------------------------------------------------------------------------------
// Test, ob Cursor (gegeben durch xLM und yLM) innerhalb (return-Wert: CURSPOS_OBJECT) oder
// außerhalb (return-Wert: CURSPOS_OUTSIDE) des this-Objektes liegt
CursPos _GEOMETR_EXPORT ObjektGeometrie :: CursorInObject (KoOrd xLM, KoOrd yLM, long lEpsX,
													 long lEpsY, long lEpsLine, bool bInBorder)
{
	switch (iObjTyp)
	{
		case OT_PUNKT:
			return CursorInPoint (xLM, yLM, lEpsX, lEpsY);

		case OT_KANTE:
			return CursorInLine (xLM, yLM, lEpsLine);

		case OT_FLAECHE:
			return CursorInArea (xLM, yLM, bInBorder);	// hier muss auch lEpsLine berücksichtigt werden (#WM030206)

		case OT_TEXT:
   		case OT_LABEL:		// indirektes Textobjekt
			return CursorInText (xLM, yLM);

		default:
			break;	// alle anderen Typen
	}

	return CURSPOS_OUTSIDE;

} // CursorInObject


// --------------------------------------------------------------------------------------------
// Hilfsroutine für CursorInObject()
CursPos ObjektGeometrie :: CursorInPoint (KoOrd xLM, KoOrd yLM, long lEpsX, long lEpsY)
{
KoOrd x0 = ((KoOrd*)pdblX)[0];
KoOrd y0 = ((KoOrd*)pdblY)[0];
int iPixX, iPixY;	// Größe des Punktsymbols des this-Punktobjektes in BS-Pixel

    PointSymbolSize (DEX_GetObjIdentEx (lONr), iPixX, iPixY);

Point PtPO = BSKoordinaten (x0, y0);	// BS-Koordinaten des Punktobjektes
Point PtLM = BSKoordinaten (xLM, yLM);	// BS-Koordinaten der Maus bei Druck auf linke Maustaste

// zuerst Test, ob Cursor innerhalb des Rechteckes liegt, das durch die Größe des PunktSYMBOLs
// gebildet wird
	if (PtPO.X()-iPixX/2 <= PtLM.X() && PtLM.X() <= PtPO.X()+iPixX/2 &&
		PtPO.Y()-iPixY/2 <= PtLM.Y() && PtLM.Y() <= PtPO.Y()+iPixY/2)
		return CURSPOS_OBJECT;

// ist dies nicht der Fall, dann noch Test, ob Cursor innerhalb des Rechteckes liegt, das um
// den DB-Punkt (x0,y0) mit den EPSILON-Schranken lEpsX und lEpsY gebildet wird
	if (x0 - lEpsX/2 <= xLM && xLM <= x0 + lEpsX/2 &&
		y0 - lEpsY/2 <= yLM && yLM <= y0 + lEpsY/2)
		return CURSPOS_OBJECT;
	return CURSPOS_OUTSIDE;

} // CursorInPoint


// --------------------------------------------------------------------------------------------
// Hilfsroutine für CursorInObject()
CursPos ObjektGeometrie :: CursorInLine (KoOrd xLM, KoOrd yLM, long lEpsLine)
{
	for (long i = 0; i < lCnt-1; i++)
	{
	KoOrd x0 = ((KoOrd*)pdblX)[i];
	KoOrd y0 = ((KoOrd*)pdblY)[i];
	KoOrd x1 = ((KoOrd*)pdblX)[i+1];
	KoOrd y1 = ((KoOrd*)pdblY)[i+1];
	KoOrd lAbst;	// Abstand des Punktes Pkt von Strecke (x1, y1, x2, y2) in Maximum-Norm

		if (PunktAnStrecke (xLM, yLM, x0, y0, x1, y1, lAbst) && lAbst <= lEpsLine)
			return CURSPOS_OBJECT;
	}

	return CURSPOS_OUTSIDE;

} // CursorInLine


// --------------------------------------------------------------------------------------------
// Hilfsroutine für CursorInObject();
// für bInBorder == true werden auch die Innenkonturen berücksichtigt (d.h. liegt der Cursor
// innerhalb einer Innenkontur, liegt er bez. des this-Objektes außerhab dieses Objektes)
CursPos ObjektGeometrie :: CursorInArea (KoOrd xLM, KoOrd yLM, bool bInBorder)
{
EFlaeche* pObj = 0;

	if (bInBorder)	// alle Konturen berücksichtigen
		pObj = EFlaecheErzeugen (iKCnt, (KoOrd*)pdblX, (KoOrd*)pdblY, plCnt);
	else			// nur Außenkontur
		pObj = new EFlaeche ((KoOrd*)pdblX, (KoOrd*)pdblY, plCnt[0]);

	if (! pObj)
	{
		DEX_Error (RC_objgeom, EC_NOMEMORY);
		return CURSPOS_OUTSIDE;
	}

Posit posLage = EPunkt(xLM,yLM).EnthaltenIn (pObj);

	DELETE_OBJ (pObj);

	if (INNERH == posLage)
		return CURSPOS_OBJECT;
	return CURSPOS_OUTSIDE;

} // CursorInArea


// --------------------------------------------------------------------------------------------
// Hilfsroutine für CursorInObject();
CursPos ObjektGeometrie :: CursorInText (KoOrd xLM, KoOrd yLM)
{
long lCO[4];	// Containerkoordinaten des this-Textobjektes
    			// lCO[0] = xmin, lCO[1] = xmax, lCO[2] = ymin, lCO[3] = ymax

    DEX_GetObjContainer (lONr, lCO);	// Container des Textfeldes

	if (lCO[0] <= xLM && xLM <= lCO[1] &&
		lCO[2] <= yLM && yLM <= lCO[3])
		return CURSPOS_OBJECT;
	return CURSPOS_OUTSIDE;

} // CursorInText
