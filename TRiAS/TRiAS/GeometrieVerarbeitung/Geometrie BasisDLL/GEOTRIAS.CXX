// Funktionen für Übertragung der Objektgeometrien von und nach TRiAS
// File: GeoTrias.cxx
// W. Mörtl


#include "GeometrP.hxx"

#include "geotrias.hxx"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
    
        
extern HWND __hWndM;
extern UINT __DexxCmd;
extern UINT __DexCmd;
	


// --------------------------------------------------------------------------------------------
// Anzahl der selektierten (markierten) Objekte in allen geöffneten Recherchefenstern
BOOL _GEOMETR_EXPORT FAR PASCAL AnzSelektObjekte (long, BOOL, void* plAnz)
{
	(*((long*)plAnz))++;
	return true;
}


// --------------------------------------------------------------------------------------------
// Anzahl der Objekte eines Identifikators, deren Container mit der aktuellen Sicht bzw.
// Ausschnitt mindestens 1 Punkt gemeinsam haben
BOOL FAR PASCAL IdentObjekteZaehlen (long lONr, BOOL, void* plAnz)
{
	if (ObjektInAusschnitt (lONr))  // Objektcontainer liegt im Ausschnitt
		(*((long*) plAnz))++;
	return true;
}


// --------------------------------------------------------------------------------------------
// Anzahl der Objekte in der aktuellen Sicht bzw. Ausschnitt, deren Container hiermit
// mindestens 1 Punkt gemeinsam haben
bool FAR PASCAL SichtObjekteZaehlen (ulong ulIdent, bool, void* plAnz)
{
// Objektnummern aller Objekte des Identifikators ulIdent bereitstellen
ENUMLONGKEY ELK;	// Enumeration aller Objekte eines Identifikators

	_ASSERTE (0 != ulIdent);
	_ASSERTE ((ulong)-1 != ulIdent);

	ELK.eKey = ulIdent;
	ELK.eFcn = (ENUMLONGKEYPROC) IdentObjekteZaehlen;
	ELK.ePtr = plAnz;
	DEX_EnumIdentObjects (ELK);

	return true;
}




// ============================================================================================
// Fläche erzeugen;
// dabei wird vorausgesetzt, daß die Koordinaten im KoOrd-Format übergeben werden
EFlaeche* _GEOMETR_EXPORT EFlaecheErzeugen (int iKCnt, KoOrd* pdblX, KoOrd* pdblY,
											long* plCnt)
{
EKante** ppKt = new EKante*[iKCnt];	// Feld der Konturen

	if (! ppKt)
	{
		DEX_Error (RC_geotrias, EC_NOMEMORY);
		return 0;
	}

long lOs = 0;
				
	for (int i = 0; i < iKCnt; i++)
	{
		if (i > 0) lOs += plCnt[i-1];

		ppKt[i] = new EKante ((KoOrd*)pdblX+lOs, (KoOrd*)pdblY+lOs, plCnt[i]);
		if (! ppKt[i])
		{
			DEX_Error (RC_geotrias, EC_NOMEMORY);
			DELETE_VEC (ppKt);
			return 0;
		}
		if ((ppKt[i])->ASP() == 0 || (ppKt[i])->Vektor() == 0)
		{
			for (int ii = 0; ii <= i; ii++)
				if (ppKt[ii]) delete (ppKt[ii]);
			DELETE_VEC (ppKt);
			return 0;	// Kanten- oder PunktVec-Konstruktor haben nicht mitgespielt
		}
	}
			
EFlaeche* pFl = new EFlaeche (ppKt, iKCnt);

	if (! pFl)
		DEX_Error (RC_geotrias, EC_NOMEMORY);

	if (pFl && 0 == pFl->KantenAnz())	// pFl konnte im Konstruktor nicht initialisiert werden
		DELETE_OBJ (pFl);

	for (i = 0; i < iKCnt; i++)
		if (ppKt[i])
			delete (ppKt[i]);
	DELETE_VEC (ppKt);

	return pFl;

} // EFlaecheErzeugen
          

// ------------------------------------------------------------------------------------------------
// Elementarobjekt aus Punkt-, Linien-, Flächen- oder Textobjekt erzeugen
bool _GEOMETR_EXPORT EObjektErzeugen (long lONr, EObjekt*& pEO, CoordTransX* pCT)
{
	_ASSERTE (lONr != 0);	// pEO wird weiter unten getestet
	_ASSERTE (lONr != -1);
	_ASSERTE (pCT != 0);

	if (NULL == pCT || 0 == lONr || -1 == lONr)	return false;

int iObjTyp = DEX_GetObjectType (lONr);	// Objekttyp (Punkt, Linie, Fläche, Text, ...)
bool bRet = true;	// return-Wert

	if (iObjTyp != OT_PUNKT && iObjTyp != OT_KANTE &&
		iObjTyp != OT_FLAECHE && iObjTyp != OT_TEXT && iObjTyp != OT_LABEL)
		return false;

ObjektGeometrie* pOG = ObjektGeometrie :: CreateInstance (lONr);

	if (NULL == pOG ||
		(pOG && !OBJGEOMETRIEinEObj (pOG, pEO, pCT)))
		bRet = false;
//	DELETE_OBJ (pOG);
	pOG->Release();
	return bRet;
	
} // EObjektErzeugen


//-------------------------------------------------------------------------------------------------
// Aus IObjektGeometrie ein Elementarobjekt (EPunkt, EKante, EFlaeche) rekonstruieren;
// aus der Geometrie eines Textobjektes wird ein Punkt rekonstruiert
bool _GEOMETR_EXPORT IObjGeometrieInEObj (IObjektGeometrie* pIOG, EObjekt*& pEO, CoordTransX* pCT)
{
	_ASSERTE (pIOG != 0);
	_ASSERTE (pCT != 0);

short iOTyp;	// Objekttyp
short iFlags;	// Modi von ModGI
long lCnt;		// Gesamtanzahl der Stützpunkte
short iKCnt;	// Größe des Konturfeldes
void* pdblX;	// Pointer auf den x-Vektor
void* pdblY;	// Pointer auf den y-Vektor
long* plCnt;	// Anzahl der Stützpunkte in Konturen

	pIOG->GetObjTyp (&iOTyp);
	pIOG->GetFlags (&iFlags);
	pIOG->GetCnt (&lCnt);
	pIOG->GetKCnt (&iKCnt);
	pIOG->GetX (&pdblX);
	pIOG->GetY (&pdblY);
	pIOG->GetLPCnt (&plCnt);

bool bRet = KonvertierungInEObj (iOTyp, iFlags, lCnt, iKCnt, pdblX, pdblY, plCnt, pEO, pCT);

	pIOG->SetFlags (iFlags);
	return bRet;
} // IObjGeometrieInEObj


//-------------------------------------------------------------------------------------------------
// Aus OBJGEOMETRIE ein Elementarobjekt (EPunkt, EKante, EFlaeche) rekonstruieren;
// aus der Geometrie eines Textobjektes wird ein Punkt rekonstruiert
bool _GEOMETR_EXPORT OBJGEOMETRIEinEObj (OBJGEOMETRIE* pOG, EObjekt*& pEO, CoordTransX* pCT, IUnknown *pICS)
{
	_ASSERTE (pOG != 0);
	_ASSERTE (pCT != 0);

short iOTyp = pOG->iObjTyp;	// ObjektTyp (EPunkt, EKante, EFlaeche)
short iFlags = pOG->iFlags;	// Modi von ModGI
long lCnt = pOG->lCnt;		// Gesamtanzahl der Stützpunkte (Größe der KoordFelder)
short iKCnt = pOG->iKCnt;	// Größe des KonturFeldes
void* pdblX = pOG->pdblX;	// KoordinatenFelder (double* / KoOrd*)
void* pdblY = pOG->pdblY;
long* plCnt = pOG->plCnt;	// Anzahl der Stützpunkte in Konturen

bool bRet = KonvertierungInEObj (iOTyp, iFlags, lCnt, iKCnt, pdblX, pdblY, plCnt, pEO, pCT, pICS);

	pOG->iFlags = iFlags;
	return bRet;
} // OBJGEOMETRIEinEObj


// --------------------------------------------------------------------------------------------
// Hilfsroutine für OBJGEOMETRIEinEObj() und IObjGeometrieInEObj()
bool KonvertierungInEObj (short iOTyp, short& iFlags, long lCnt, short iKCnt, void* pdblX,
						  void* pdblY, long* plCnt, EObjekt*& pEO, CoordTransX* pCT,
						  IUnknown *pICS)
{
	// wenn Koordinaten noch im double-Format, dann Umwandlung in KoOrd-Format
	if (iFlags & OGConverted)
	{
		_ASSERTE (pCT != 0);

		if (! pCT ) return false;

// ACHTUNG: Die nachfolgende InPlace-Lösung funktioniert nur dann richtig, wenn
//          sizeof(KoOrd) <= sizeof(double)  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		_ASSERTE (sizeof(KoOrd) <= sizeof(double));

		for (long i = 0; i < lCnt; i++)
		{
			// Umwandlung der Real-Koordinaten pdblX und pdblY in ASC-Format sowie
			// des ASC-Format in DB-Koordinaten (unter Berücksichtigung der internen Skalierung)
			RealInDBKoord (((double*)pdblX)[i], ((double*)pdblY)[i], ((KoOrd*)pdblX)[i],
						   ((KoOrd*)pdblY)[i], pCT, pICS);
		}

		iFlags &= ~OGConverted;	// Flags werden hier sofort modifizieren
	}

	
	switch (iOTyp)
	{
		case OT_PUNKT:
		case OT_TEXT:
		case OT_LABEL:		// indirektes Textobjekt
			pEO = new EPunkt (((KoOrd*)pdblX)[0], ((KoOrd*)pdblY)[0]);
			if (! pEO)
			{
				DEX_Error (RC_geotrias, EC_NOMEMORY);
				return false;
			}
			return true;
			
		case OT_KANTE:
			pEO = new EKante ((KoOrd*)pdblX, (KoOrd*)pdblY, lCnt);
			if (! pEO)
			{
				DEX_Error (RC_geotrias, EC_NOMEMORY);
				return false;
			}
			return true;
			
		case OT_FLAECHE:
			pEO = EFlaecheErzeugen (iKCnt, (KoOrd*)pdblX, (KoOrd*)pdblY, plCnt);
			if (! pEO)
			{
				DELETE_OBJ (pEO);	// trotzdem
				return false;
			}
			return true;
			
		default:
			_ASSERTE (false);
			return false;	// weder EPunkt, EKante noch EFlaeche
	}
} // KonvertierungInEObj


//---------------------------------------------------------------------------------------------
// Geometrie eines Elementarobjektes pEO (EPunkt, EKante, EFlaeche) in das Interface
// IObjektGeometrie pIOG einer ObjektGeometrie einspeichern;
// !!! Es wird vorausgesetzt, daß die Gesamtanzahl der Stützpunkte und (bei Flächen) die
//     Konturanzahl von pEO den Platz in pIOG nicht übersteigt !!!
bool _GEOMETR_EXPORT EObjInIObjGeometrie (EObjekt* pEO, IObjektGeometrie* pIOG)
{
	_ASSERTE (pEO != 0);
	_ASSERTE (pIOG != 0);

	if (!pEO || !pIOG) return false;

long lCnt;					// Parameter des pIOG-Zielobjektes
short iKCnt;
KoOrd* plXK; KoOrd* plYK;
long* plCnt;

	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);
	pIOG->GetLPCnt (&plCnt);

	switch (pEO->isA())
	{
		case OT_PUNKT:
			plXK[0] = ((EPunkt*)pEO)->X();
			plYK[0] = ((EPunkt*)pEO)->Y();

			pIOG->SetCnt (1);			// Gesamtanzahl der Stützpunkte
			pIOG->SetKCnt (-1);			// Größe des Konturfeldes
			pIOG->SetLPCnt (0, -1);		// Anzahl der Stützpunkte in Konturen
			pIOG->SetObjTyp (OT_PUNKT);	// 02.11.98
			return true;

		case OT_KANTE:
		{
		long lCntEO = ((EKante*)pEO)->ASP();	// Gesamtanzahl der Stützpunkte

			pIOG->GetCnt (&lCnt);

			_ASSERTE (lCntEO <= lCnt);

			if (lCntEO > lCnt)
				return false;	// Quellparameter zu groß; hier müßte mehr Aufwand getrieben werden !!!

			((EKante*)pEO)->GetKante (plXK, plYK, lCntEO);

			pIOG->SetCnt (lCntEO);
			pIOG->SetKCnt (0);			// Größe des Konturfeldes
			pIOG->SetLPCnt (0, 0);		// Anzahl der Stützpunkte in Konturen
			pIOG->SetObjTyp (OT_KANTE);	// 02.11.98
			return true;
		}

		case OT_FLAECHE:
		{
		long lCntEO = ((EFlaeche*)pEO)->ASP();		// Gesamtanzahl der Stützpunkte und
		int iKCntEO = ((EFlaeche*)pEO)->KantenAnz();// Größe des Konturfeldes des Quellobjektes

			pIOG->GetCnt (&lCnt);
			pIOG->GetKCnt (&iKCnt);

			_ASSERTE (lCntEO <= lCnt);
			_ASSERTE (iKCntEO <= iKCnt);

			if (lCntEO > lCnt || iKCntEO > iKCnt)
				return false;	// Quellparameter zu groß; hier müßte mehr Aufwand getrieben werden !!!

		long lOs = 0;

			for (int i = 0; i < iKCntEO; i++)
			{
			long lKL = ((EFlaeche*)pEO)->KA(i).ASP();		// Länge der i-ten Kontur

				((EFlaeche*)pEO)->KA(i).GetKante (plXK+lOs, plYK+lOs, lKL);
				lOs += lKL;

				plCnt[i] = lKL;
			}

			pIOG->SetCnt (lCntEO);
			pIOG->SetKCnt (iKCntEO);
			pIOG->SetObjTyp (OT_FLAECHE);	// 02.11.98

			return true;
		}

		default:		// weder EPunkt, Text, EKante noch EFlaeche
			_ASSERTE (false);
			return false;
	}

	return true;

} // EObjInIObjGeometrie


//-------------------------------------------------------------------------------------------------
// Geometrie eines Elementarobjektes (EPunkt, EKante, EFlaeche) in eine schon vorhandene Struktur
// OBJGEOMETRIE einspeichern;
// gilt auch für Punkte, die aus einem Textobjekt entstanden sind; deshalb ist Parameter iObjTyp
// erforderlich, da ansonsten nicht unterschieden werden könnte, ob ein Punkt- oder Textobjekt
// entstehen soll
bool _GEOMETR_EXPORT EObjInOBJGEOMETRIE (EObjekt* pEO, int iObjTyp, OBJGEOMETRIE* pOG, bool bDblCoord)
{
	_ASSERTE (pEO != 0);
	_ASSERTE (pOG != 0);

	if (!pEO || !pOG) return false;

	pOG->iObjTyp = iObjTyp;	

	switch (iObjTyp)	// neuer Objekttyp (Typumwandlung ist möglich)
	{
		case OT_PUNKT:	// hier kein break bzw. return !
			pOG->iKCnt = 0;	// Größe des Konturfeldes
			pOG->plCnt = 0;	// Anzahl der Stützpunkte in Konturen


		case OT_TEXT:
		case OT_LABEL:		// indirektes Textobjekt
			switch (pEO->isA())	// bisheriger Objekttyp
			{
				case OT_KANTE:
					((KoOrd*)pOG->pdblX)[0] = ((EKante*)pEO)->SP(0).X();
					((KoOrd*)pOG->pdblY)[0] = ((EKante*)pEO)->SP(0).Y();
					break;
				case OT_FLAECHE:
					((KoOrd*)pOG->pdblX)[0] = ((EFlaeche*)pEO)->KA(0).SP(0).X();
					((KoOrd*)pOG->pdblY)[0] = ((EFlaeche*)pEO)->KA(0).SP(0).Y();
					break;
				default:	// Normalfall (keine Typumwandlung)
					((KoOrd*)pOG->pdblX)[0] = ((EPunkt*)pEO)->X();
					((KoOrd*)pOG->pdblY)[0] = ((EPunkt*)pEO)->Y();
			}

			// wegen einer evtl. Typumwandlung ist noch nachfolgendes erforderlich:
			pOG->lCnt = 1;		// Gesamtanzahl der Stützpunkte
			return true;


		case OT_KANTE:
		{
		long lCnt;	// neue Kantenlänge

			switch (pEO->isA())	// bisheriger Objekttyp
			{
				case OT_FLAECHE:
					lCnt = ((EFlaeche*)pEO)->KA(0).ASP();

					_ASSERTE (pOG->lCnt >= lCnt);

					// Außenkontur der bisherigen Fläche pEO wird zur EKante
					pOG->lCnt = lCnt;
					((EFlaeche*)pEO)->KA(0).GetKante ((KoOrd*)pOG->pdblX, (KoOrd*)pOG->pdblY,
													pOG->lCnt);
					break;

				default:	// Normalfall (keine Typumwandlung)
					lCnt = ((EKante*)pEO)->ASP();

					_ASSERTE (pOG->lCnt >= lCnt);

					pOG->lCnt = lCnt;
					((EKante*)pEO)->GetKante ((KoOrd*)pOG->pdblX, (KoOrd*)pOG->pdblY,
											 pOG->lCnt);
			}

			pOG->iKCnt = 0;	// Größe des Konturfeldes
			pOG->plCnt = 0;	// Anzahl der Stützpunkte in Konturen
			return true;
		}


		case OT_FLAECHE:
		{
		long lCnt = ((EFlaeche*)pEO)->ASP();		// Gesamtanzahl der Stützpunkte
		int iKCnt = ((EFlaeche*)pEO)->KantenAnz();	// Größe des Konturfeldes

		// Die Felder pOG->pdblX bzw. pOG->pdblY dürfen auf KEINEN Fall vergrößert werden, da
		// sie außerhalb von meinen Routinen angelegt wurden und auch dort wieder freigegeben
		// werden. Wird dort mit einer anderen als meiner Speicherverwaltung gearbeitet,
		// knallt's ganz schlicht. (02.07.98)
		// Waren aber die Koordinaten des an GeoRein übergebenen Objektes im double-Format
		// (bDblCoord == true), ist durch die Konvertierung in das KoOrd-Format genug Platz da,
		// um einen weiteren Stützpunkt aufzunehmen, da KoOrd-Koordinaten weniger Platz
		// benötigen als double-Koordinaten. Trotzdem bleibt die Forderung bestehen: Der
		// Speicherplatz für pOG->pdblX bzw. pOG->pdblY darf nicht größer werden. (22.09.98)
#if defined(_DEBUG)
			if (pOG->lCnt < lCnt && !bDblCoord)
				_ASSERTE (pOG->lCnt >= lCnt);
			_ASSERTE (pOG->iKCnt >= iKCnt);	// diesen Fall kenne ich nicht
#endif // defined(_DEBUG)

			pOG->lCnt = lCnt;
			pOG->iKCnt = iKCnt;
			
		long lOs = 0;
				
			for (int i = 0; i < iKCnt; i++)
			{
				if (i > 0) lOs += pOG->plCnt[i-1];

				// definierte Belegung von plCnt[i] ist wegen des Minimum-Befehls in
				// GetKante() notwendig
				pOG->plCnt[i] = lCnt;
				((EFlaeche*)pEO)->KA(i).GetKante ((KoOrd*)pOG->pdblX+lOs, (KoOrd*)pOG->pdblY+lOs,
												  pOG->plCnt[i]);
			}
			return true;
		}

		
		default:		// weder EPunkt, Text, EKante noch EFlaeche
			_ASSERTE (false);
			return false;
	}
} // EObjInOBJGEOMETRIE


// --------------------------------------------------------------------------------------------
// OBJGEOMETRIE eines GeoObjektes an TRiAS zurückgeben, wenn nicht möglich, dann false;
// neue Objektnummer wird zurückgegeben
bool _GEOMETR_EXPORT GeometrieAnTRIAS (GeoObjekt* pGObj, SpForm sfSForm, long& lNeuONr, CoordTransX* pCT)
{
#if _TRiAS_VER >= 0x0300
	_ASSERTE (_TRiAS_VER >= 0x0300);
#endif // _TRiAS_VER >= 0x0300
	return GeometrieAnTRIASEx (HPROJECT(NULL), pGObj, sfSForm, lNeuONr, pCT);
}


// --------------------------------------------------------------------------------------------
// OBJGEOMETRIE eines GeoObjektes an TRiAS zurückgeben, wenn nicht möglich, dann false;
// neue Objektnummer wird zurückgegeben
bool _GEOMETR_EXPORT GeometrieAnTRIASEx (HPROJECT hPr, GeoObjekt* pGObj, SpForm sfSForm,
										 long& lNeuONr, CoordTransX* pCT)
{
	lNeuONr = -1;	// für den Fall, daß Datenquelle schreibgeschützt ist

ulong ulIdent = pGObj->Id();

#if _TRiAS_VER >= 0x0300
	if (0 != ulIdent && (ulong)-1 != ulIdent)
	{
		if (DEX_GetROModeIdent (ulIdent))	// Objektklasse schreibgeschützt (R/O-Modus)
		{
			DEX_Error (RC_GeometrieAnTRIAS, WC_CLASS_ISRO);
			return false;
		}
	}
	else
#endif // _TRiAS_VER >= 0x0300
	if (0 != DEX_GetROModeEx (hPr))	// Datenquelle schreibgeschützt (R/O-Modus)
	{
		DEX_Error (RC_GeometrieAnTRIAS, WC_DATASOURCE_ISRO);
		return false;
	}

	_ASSERTE (pGObj != 0);	// pCT kann 0 sein, da er nicht immer benötigt wird

OBJGEOMETRIE OG;

	INITSTRUCT (OG, OBJGEOMETRIE);
	OG.lIdent = ulIdent;

	switch (pGObj->isA())
	{
		case OT_PUNKT:
		{
			OG.iObjTyp = OT_PUNKT;
			OG.lCnt = 1L;
			OG.pdblX = &((EPunkt*)(GeoPunkt*)pGObj)->X();
			OG.pdblY = &((EPunkt*)(GeoPunkt*)pGObj)->Y();
		}
			break;

		case OT_KANTE:
		{
			OG.iObjTyp = OT_KANTE;
			OG.lCnt = ((EKante*)(GeoKante*)pGObj)->ASP();
			OG.pdblX = new KoOrd[OG.lCnt];
			OG.pdblY = new KoOrd[OG.lCnt];
			if (!OG.pdblX || !OG.pdblY)
			{
				DEX_Error (RC_GeometrieAnTRIAS, EC_NOMEMORY);
				DELETE_VEC (OG.pdblX);
				return false;
			}
			((EKante*)(GeoKante*)pGObj)->GetKante ((KoOrd*) OG.pdblX, (KoOrd*) OG.pdblY, OG.lCnt);
		}
			break;

		case OT_FLAECHE:
		{
			OG.iObjTyp = OT_FLAECHE;
			OG.lCnt = ((EFlaeche*)(GeoFlaeche*)pGObj)->ASP();			// Gesamtanzahl der Stützpunkte
			OG.iKCnt = ((EFlaeche*)(GeoFlaeche*)pGObj)->KantenAnz();	// Größe des Konturfeldes
			OG.pdblX = new KoOrd[OG.lCnt];
			OG.pdblY = new KoOrd[OG.lCnt];
			OG.plCnt = new long[OG.iKCnt]; // Anzahl der Stützpunkte in Konturen
			if (!OG.pdblX || !OG.pdblY || !OG.plCnt)
			{
				DEX_Error (RC_GeometrieAnTRIAS, EC_NOMEMORY);
				DELETE_VEC (OG.pdblX);
				DELETE_VEC (OG.pdblY);
				return false;
			}

		long lOs = 0;
				
			for (int i = 0; i < OG.iKCnt; i++)
			{
				if (i > 0) lOs += OG.plCnt[i-1];

				OG.plCnt[i] = OG.lCnt; // definierte Belegung wegen des Minimum-Befehls in GetKante
				((EFlaeche*)(GeoFlaeche*)pGObj)->KA(i).GetKante ((KoOrd*)OG.pdblX+lOs,
															(KoOrd*)OG.pdblY+lOs, OG.plCnt[i]);
			}
		}
			break;

		case OT_KREIS:
		{
		EPunkt M = ((GeoKreis*) pGObj)->MP();	// Mittelpunkt
		long r = ((GeoKreis*) pGObj)->Radius(); // Radius

			if (SFORM_TEMP == sfSForm)	// temporärer Kreis
			{
				OG.iObjTyp = OT_KREIS;
				OG.lCnt = 2;
			}
			else		// permanenter Kreis
			{
				OG.iObjTyp = OT_FLAECHE;
				OG.lCnt = 181;
			}
			OG.iKCnt = 1;
			OG.pdblX = new KoOrd[OG.lCnt];
			OG.pdblY = new KoOrd[OG.lCnt];
			OG.plCnt = new long[1]; 		// Anzahl der Stützpunkte in Konturen
			if (!OG.pdblX || !OG.pdblY || !OG.plCnt)
			{
				DEX_Error (RC_GeometrieAnTRIAS, EC_NOMEMORY);
				DELETE_VEC (OG.pdblX);
				DELETE_VEC (OG.pdblY);
				return false;
			}
			OG.plCnt[0] = OG.lCnt;

			if (SFORM_TEMP == sfSForm)	// temporäres Objekt
			{
				((KoOrd*) OG.pdblX)[0] = M.X();
				((KoOrd*) OG.pdblY)[0] = M.Y();
				((KoOrd*) OG.pdblX)[1] = M.X() + r;
				((KoOrd*) OG.pdblY)[1] = M.Y();
			}
			else		// permanentes Objekt
			{
			double dFak = 1;

				if (pCT && pCT->isMetric() == false)
					dFak = pCT->CoordTransAspectRatio (ObjRechteck (M.X()-r, M.X()+r, M.Y()-r,
																	 M.Y()+r));

				// 180-Eck, d.h. aller 2°
				for (int i = 0; i <= 180; i++)
				{
				double wi = Pi/90*i;	// Pi ist in geokonst.hxx definiert

					((KoOrd*) OG.pdblX)[i] = DtoL (M.X() + r*cos(wi)/dFak);
					((KoOrd*) OG.pdblY)[i] = DtoL (M.Y() + r*sin(wi));
				}
			}
		}
			break;

		default:        // Objekt weder EPunkt, EKante, EFlaeche noch Kreis
			_ASSERTE (false);
			DEX_Error (RC_GeometrieAnTRIAS, EC_NOGEOOBJEKT);
			return false;

	} // switch

	OG.iFlags &= ~OGConverted;		// KoOrd-Koordinaten
	if (SFORM_TEMP == sfSForm)
		OG.iFlags |= OGTempObject;	// temporäres Objekt
	else
	{
		OG.iFlags |= OGNewObject;		// permanentes Objekt in Datenbank aufnehmen
		OG.iFlags |= OGAddToView;		// Identifikator zur Sicht hinzufügen
		OG.iFlags |= OGForceGeometry;	// kein Test, ob neues Objekt innerhalb des Projekt-Containers liegt
										// (für Buffering eines am Container-Rand liegenden Objektes notwendig)
		OG.iFlags |= OGForceGeoError;	// Objekt wird bei Geometriefehler von GEOREIN abgewiesen
	}
    
bool bRet = true;	// return-Wert dieser Routine

	if (OT_KANTE == pGObj->isA())
		OG.iFlags |= OGNoExtendedErrorCheck;	// das Teilen von Kanten wird erst einmal unterbunden (#WM021217)

// Objektgeometrie von Erweiterung an TRiAS übergeben, danach wird von TRiAS die neue
// Objektnummer zurückgegeben
bool bResult = DEX_ModObjGeometrieEx (hPr, OG);

	// es gibt 3 Fälle:
	// bResult == true, OG.lONr > 0:   fehlerfreies Objekt, wurde gespeichert
	// bResult == false, OG.lONr > 0:  Objekt mit Fehlerkennzeichnung, wurde gespeichert
	// bResult == false, OG.lONr == 0: fehlerhaftes Objekt, wurde nicht gespeichert
	if (0 != OG.lONr && -1 != OG.lONr)
		lNeuONr = OG.lONr;
	else
		bRet = false;

	if (OT_PUNKT != pGObj->isA())
	{
		DELETE_VEC (OG.pdblX);
		DELETE_VEC (OG.pdblY);
		DELETE_VEC (OG.plCnt);
	}

	return bRet;

} // GeometrieAnTRIASEx


//-------------------------------------------------------------------------------------------------
// Test, ob Container des lONr-Objektes mit dem Container der aktuellen Sicht
// bzw. des Ausschnitts mindestens einen Punkt gemeinsam hat (true), sonst false
bool ObjektInAusschnitt (long lONr)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

long CO[4];    // Containerkoordinaten des lONr-Objektes

	DEX_GetObjContainer (lONr, CO);

ObjRechteck OC1 (CO[0], CO[1], CO[2], CO[3]);
ObjRechteck* pOC2 = new ObjRechteck (0L, 0L, 0L, 0L); // Container von Sicht bzw. Ausschnitt

	if (! pOC2)
	{
		DEX_Error (RC_geotrias, EC_NOMEMORY);
		return false;
	}
	DEX_GetActiveSelection (pOC2);
	//  Ymin, Ymax ggf. tauschen
	if (pOC2->YMin() > pOC2->YMax())
	{
	long Y = pOC2->YMin();

		pOC2->YMin() = pOC2->YMax();
		pOC2->YMax() = Y;
	}

bool bRueck = pOC2->Durchschnitt (OC1);

	DELETE_OBJ (pOC2);

	return bRueck;
} // ObjektInAusschnitt
