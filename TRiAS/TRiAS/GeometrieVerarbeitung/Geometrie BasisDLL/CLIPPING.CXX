// Clipping für GeoKante und GeoFlaeche
// File: CLIPPING.CXX
// W. Mörtl


#include "GeometrP.hxx"

#include "cliplist.hxx"
#include "ErrorCorrection.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


///////////////////////////////////////////////////////////////////////////////////////////////
// Methoden für das GeoObjekt: GEOKANTE
// Clipping für GeoKante: pSO schneidet this-Kante und erzeugt dabei evtl. mehrere Teilkanten,
// die entspr. dem Auswahlkriterium ulLageAusw in CL eingetragen werden;
// Wird this-Kante geschnitten, wird true zurückgegeben, sonst false;
// bAbbr = true, wenn Schnittoperation durch Anwender abgebrochen wurde, sonst false
bool _GEOMETR_EXPORT GeoKante :: Clipping (EObjekt* pSO, int iOT, ulong ulLageAusw,
						   ClipListe& CL, int iSkip, Posit& posLage, bool& bAbbr, void* pPSt)
{
	_ASSERTE (NULL != pSO);	// pPSt kann 0 sein

	bAbbr = false;
	if (! pSO)
		return false;
	
	switch (iOT)
	{
		case OT_KANTE:
			return ClippingMitKante ((EKante*)pSO, CL, iSkip, bAbbr, pPSt);
		case OT_FLAECHE:
			return ClippingMitFlaeche ((EFlaeche*)pSO, ulLageAusw, CL, iSkip, posLage, bAbbr,
									   pPSt);
		default:
			_ASSERTE (false);
			return false;	// kein zulässiger Objekttyp
	}
} // GeoKante :: Clipping


// --------------------------------------------------------------------------------------------
// this-Kante wird durch pSKt-Kante geschnitten;
// Test, ob die Objektcontainer der this-Kante und der schneidenden pSKt-Kante
// durchschnittsleer sind, wird in Routine Aufbereitung0() durchgeführt und dabei außerdem der
// Prozentzähler weitergestellt
bool _GEOMETR_EXPORT GeoKante :: ClippingMitKante (EKante* pSKt, ClipListe& CL, int,
												   bool& bAbbr, void* pPSt)
{
	_ASSERTE (NULL != pSKt);	// pPSt kann 0 sein

bool bRet = false;		// return-Wert

// aus Stützpunktfolge der this-Kante wird Vektor pML1 mit markierten Punkten erzeugt;
// dieser Vektor wird in Routine Aufbereitung0() evtl. noch erweitert
bool bClosed1 = (SP(0) == SP(_Size-1));
MarkLine* pML1 = new MarkLine (_Size, -1, bClosed1);

	if (!pML1 || !pML1->Vektor())
	{
		DEX_Error (RC_clipping, EC_NOMEMORY);
		DELETE_OBJ(pML1);
		return false;
	}

	if (!Aufbereitung0 (pSKt, pML1, bAbbr, pPSt))
	{
		DELETE_OBJ (pML1);
		return false;
	}

	// Routine KanteZerlegt() ermittelt, ob die zu schneidende this-Kante pML1 überhaupt durch
	// die schneidende pSKt-EKante zerlegt wird (true) oder nicht
	if (KanteZerlegt (pML1))
		bRet = TeilKanten1 (pML1, ObjNr(), Id(), CL);

	DELETE_OBJ (pML1);
	return bRet;

} // GeoKante :: ClippingMitKante


// --------------------------------------------------------------------------------------------
// this-Kante wird durch pSFl-Fläche geschnitten;
// Test, ob die Objektcontainer der this-Kante und der schneidenden pSFl-Fläche
// durchschnittsleer sind, wird in Routine Aufbereitung2() durchgeführt und dabei außerdem der
// Prozentzähler weitergestellt
bool _GEOMETR_EXPORT GeoKante :: ClippingMitFlaeche (EFlaeche* pSFl, ulong ulLageAusw,
								 ClipListe& CL, int, Posit& posLage, bool& bAbbr, void* pPSt)
{
	_ASSERTE (NULL != pSFl);	// pPSt kann 0 sein

// aus Stützpunktfolge der this-Kante wird Vektor pML1 mit markierten Punkten erzeugt;
// dieser Vektor wird in Aufbereitung2() evtl. noch erweitert
bool bClosed = (SP(0) == SP(_Size-1));
MarkLine* pML1 = new MarkLine (_Size, -1, bClosed);
MarkLine* pML2 = new MarkLine (pSFl->KA(0).ASP(), 0);

	if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
	{
		DEX_Error (RC_clipping, EC_NOMEMORY);
		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		return false;
	}

bool bLeer;		// Parameter von Aufbereitung2(); wird hier nicht ausgewertet

	if (!Aufbereitung2 (&pSFl->KA(0), pML1, pML2, bLeer, bAbbr, pPSt))
	{
		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		return false;
	}

// Routine KantenPosit() ermittelt, ob this-Kante überhaupt durch pSFl zerlegt wird
// (posLage == INNAUSS) oder nicht, d.h. this-Kante liegt außerhalb (AUSSERH bzw. AUSSERHB),
// innerhalb (INNERH bzw. INNERHB) von pSFl bzw. auf dem pSFl-Rand (KONTUR)
bool bOverlap;	// this-Kante hat mit der pSFl-Außenkontur einen Überlappungsbereich
int iTouchOut;	// Parameter von KantenPosit(); wird hier nicht ausgewertet

	posLage = KantenPosit (&pSFl->KA(0), pML1, bOverlap, iTouchOut);

// keine Zerlegung
	if (AUSSERH == posLage || (AUSSERHB == posLage && !bOverlap) || KONTUR == posLage ||
		OFFEN == posLage || UNKLAR == posLage)
	{
		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		return false;
	}

bool bRet1 = false;		// es wurde geschnitten und damit Schnittergebnisse in CL eingetragen
bool bRet2 = false;		// (true), ansonsten false
bool bRet3 = false;		// war bis zum 02.07.98 auf "true" gesetzt

// Spezialfall: die zu schneidende this-Kante liegt innerhalb der Außenkontur der schneidenden
// pSFl-Fläche; es ist noch zu prüfen, ob this-Kante in eine pSFl-Insel hineinragt
	if (INNERH == posLage || (INNERHB == posLage && !bOverlap))
	{
		if (ulLageAusw & LINN)
			bRet1 = MesserInselnINN0 (pSFl, CL);
		if (ulLageAusw & LAUSS)
			bRet2 = MesserInselnAUSS (pSFl, CL);
		if (ulLageAusw & LKONT)
			bRet3 = MesserInselnKONT (pSFl, CL);

		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		return (bRet1 || bRet2 || bRet3);
	}

int iSkip = (int) CL.Count();	// die Teilkanten, die sich schon in CL befinden, können
								//  bei der Routine MesserInselnINN() übergangen werden
// Zerlegen in Teilkanten
bool bRet =	TeilKanten2 (pML1, pML2, ObjNr(), Id(), ulLageAusw, CL);

	DELETE_OBJ (pML1); DELETE_OBJ (pML2);

	// Inseln berücksichtigen
	if (pSFl->KantenAnz() > 1)	// pSFl-Fläche hat Inseln
	{
		if (bRet &&		// Teilkanten wurden erzeugt
			ulLageAusw & LINN)
			bRet1 = MesserInselnINN1 (pSFl, CL, iSkip);
		if (ulLageAusw & LAUSS)
			bRet2 = MesserInselnAUSS (pSFl, CL);
		if (ulLageAusw & LKONT)
			bRet3 = MesserInselnKONT (pSFl, CL);
	}

	return (bRet || bRet1 || bRet2 || bRet3);
	
} // GeoKante :: ClippingMitFlaeche


// --------------------------------------------------------------------------------------------
// Inseln bei Schnitt der this-Kante mit pSFl-Schnittfläche berücksichtigen
// (ulLageAusw == LINN); this-Kante liegt vollständig innerhalb der Außenkontur der
// pSFl-Schnittfläche;
// Rückgabe von true, wenn geschnitten wurde und damit Schnittergebnisse in CL eingetragen
// wurden, ansonsten false
bool GeoKante :: MesserInselnINN0 (EFlaeche* pSFl, ClipListe& CL)
{
	_ASSERTE (pSFl != 0);

	if (! pSFl) return false;

int iKAnz = pSFl->KantenAnz();

	if (1 == iKAnz) return false;	// keine Inseln

// this-Kante in CLZw eintragen; Test, ob this-Kante von einer pSFl-Insel geschnitten wird;
// wenn ja, dann die Teilabschnitte, die außerhalb dieser Insel liegen, in CLZw eintragen und
// die this-Kante aus CLZw löschen;
// danach alle CLZw-Einträge mit der nächsten Insel testen; Teilabschnitte, die außerhalb
// dieser Insel liegen, wieder in CLZw eintragen und den aktuellen CLZw-Eintrag löschen usw.
ClipListe CLZw;		// ClipListe für Zwischenergebnisse

	AddClipObjekt (CLZw);

bool bDelThis = false;	// this-Objekt wurde (noch nicht) aus CLZw gelöscht

	MesserInselnINN (pSFl, CLZw, bDelThis);

	// wenn in CLZw Zwischenergebnisse abgelegt wurden, dann diese jetzt nach CL übernehmen
	if (!bDelThis || 0 == CLZw.Count())
		return false;

CRing riz (CLZw);

	for (riz.First(); riz.Valid(); riz.Next())
	{
	GeoObjektLock mlz (riz);

		if (! mlz) continue;	// kein Zugriff möglich
		mlz->AddClipObjekt (CL);
	}

	CLZw.EveryDelete();

	return true;

} // MesserInselnINN0


// --------------------------------------------------------------------------------------------
// Inseln bei Schnitt der this-Kante mit pSFl-Schnittfläche berücksichtigen (ulLageAusw == LINN);
// die ersten iSkip Einträge in CL werden übergangen;
// Rückgabe von true, wenn geschnitten wurde und damit Schnittergebnisse in CL eingetragen
// wurden, ansonsten false
bool GeoKante :: MesserInselnINN1 (EFlaeche* pSFl, ClipListe& CL, int iSkip)
{
	_ASSERTE (pSFl != 0);

	if (! pSFl) return false;

int iKAnz = pSFl->KantenAnz();

	if (1 == iKAnz) return false;	// keine Inseln

// alle CL-Teilkanten überprüfen, ob sie eine pSFl-Insel schneiden; wenn ja, dann diese
// Teilkanten aus CL löschen und dafür die Teile eintragen, die außerhalb einer pSFl-Insel
// liegen
CRing ri (CL);		// Navigator für ListContainer ClipListe CL

	// do-Schleife für alle in CL befindlichen Schnittergebnisse (die ersten iSkip Einträge in
	// CL sind zu übergehen)
	ri.First();
	if (iSkip > 0)
		for (int ii = 1; ii <= iSkip; ii++)
			ri.Next();

ClipListe CLZw;		// ClipListe für Zwischenergebnisse

	// die nachfolgenden CL-Einträge nach CLZw übertragen und in CL löschen
	while (ri.Valid())
	{
		{
		GeoObjektLock mlz (ri);

			if (! mlz) continue;	// kein Zugriff möglich
			mlz->AddClipObjekt (CLZw);
		}
		ri.Delete();
	}

bool bDelThis;	// Parameter für MesserInselnINN(); wird hier nicht ausgewertet

	MesserInselnINN (pSFl, CLZw, bDelThis);

	// wenn in CLZw Zwischenergebnisse abgelegt wurden, dann diese jetzt nach CL übernehmen
	if (0 == CLZw.Count())
		return false;

CRing riz (CLZw);

	for (riz.First(); riz.Valid(); riz.Next())
	{
	GeoObjektLock mlz (riz);

		if (! mlz) continue;	// kein Zugriff möglich
		mlz->AddClipObjekt (CL);
	}

	CLZw.EveryDelete();

	return true;

} // MesserInselnINN1


// --------------------------------------------------------------------------------------------
// Hilfsroutine für MesserInselnINN0() bzw. MesserInselnINN1()
bool GeoKante :: MesserInselnINN (EFlaeche* pSFl, ClipListe& CLZw, bool& bDelThis)
{
bool bOverlap;		// this-Kante hat mit einer pSFl-Insel einen Überlappungsbereich
int iTouchOut;		// Parameter von KantenPosit(); wird hier nicht ausgewertet
bool bLeer, bAbbr;	// Parameter von Aufbereitung2(); werden hier nicht ausgewertet
CRing riz (CLZw);
int iKAnz = pSFl->KantenAnz();

	for (int i = 1; i < iKAnz; i++)	// Abarbeitung aller pSFl-Inseln
	{
	ulong ul = CLZw.Count();	// Anzahl der aus CLZw zu bearbeitenden Einträge

		riz.First();

		for (ulong u = 0; u < ul; u++)
		{
		bool bDel = false;	// aktuelle Teilkante ist (noch nicht) aus CLZw zu löschen

			{ // Klammerung für riz.Delete() erforderlich
			GeoObjektLock mlz (riz);

				if (! mlz)		// kein Zugriff möglich
				{
					DEX_Error (RC_clipping, EC_NOLOCK);
					riz.Next();
					i++;
					continue;
				}

			GeoKante* pTK = (GeoKante*)(GeoObjekt*) mlz;		// Teilabschnitt aus CLZw
			bool bClosed = (pTK->SP(0) == pTK->SP(pTK->ASP()-1));

			MarkLine* pML1 = new MarkLine (pTK->ASP(), -1, bClosed);
			MarkLine* pML2 = new MarkLine (pSFl->KA(i).ASP(), i, true/*, false*/);

				if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
				{
					DEX_Error (RC_clipping, EC_NOMEMORY);
					DELETE_OBJ (pML1); DELETE_OBJ (pML2);
					return false;
				}

				if (!pTK->Aufbereitung2 (&pSFl->KA(i), pML1, pML2, bLeer, bAbbr, 0))
				{
					DELETE_OBJ (pML1); DELETE_OBJ (pML2);
					if (bLeer) continue;		// ??? (11.11.98)
					return false;
				}

			// Lage der Teilabschnitte aus CLZw bez. der pSFl-Insel bestimmen
			Posit posLage = KantenPosit (&pSFl->KA(i), pML1, bOverlap, iTouchOut);

				if ((INNAUSS == posLage || (AUSSERHB == posLage && bOverlap)) &&
					TeilKanten2 (pML1, pML2, ObjNr(), Id(), LAUSS, CLZw))
					bDel = true;	// aktuelle Teilkante ist aus CLZw zu löschen

				DELETE_OBJ (pML1); DELETE_OBJ (pML2);
			}

			if (bDel)
			{
				riz.Delete();	// aktuelle Teilkante aus CLZw löschen
				bDelThis = true;
			}
			else riz.Next();
		}
	}

	return true;

} // MesserInselnINN


// --------------------------------------------------------------------------------------------
// Inseln bei Schnitt der this-Kante mit pSFl-Schnittfläche berücksichtigen
// (ulLageAusw == LAUSS); die ersten iSkip Einträge in CL werden übergangen;
// Rückgabe von true, wenn geschnitten wurde und damit Schnittergebnisse in CL eingetragen
// wurden, ansonsten false
bool GeoKante :: MesserInselnAUSS (EFlaeche* pSFl, ClipListe& CL)
{
	_ASSERTE (pSFl != 0);

	if (! pSFl) return false;

int iKAnz = pSFl->KantenAnz();

	if (1 == iKAnz) return true;	// keine Inseln

// Teile der this-Kante erzeugen, die innerhalb der pSFl-Schnittfläche liegen, und diese Teile
// mit den pSFl-Inseln schneiden; alles was innerhalb einer pSFl-Insel liegt wird als Teilkante
// in CL eingetragen
bool bClosed = (SP(0) == SP(_Size-1));
MarkLine* pML1 = new MarkLine (_Size, -1, bClosed);
MarkLine* pML2 = new MarkLine (pSFl->KA(0).ASP(), 0);

	if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
	{
		DEX_Error (RC_clipping, EC_NOMEMORY);
		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		return false;
	}

bool bLeer, bAbbr;	// Parameter von Aufbereitung2(); werden hier nicht ausgewertet

	if (!Aufbereitung2 (&pSFl->KA(0), pML1, pML2, bLeer, bAbbr, 0))
	{
		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		return false;
	}

ClipListe CLZw;	// ClipListe für Zwischenergebnisse

	TeilKanten2 (pML1, pML2, ObjNr(), Id(), LINN, CLZw);

	DELETE_OBJ (pML1); DELETE_OBJ (pML2);

bool bOverlap;		// this-Kante hat mit einer pSFl-Insel einen Überlappungsbereich
int iTouchOut;		// Parameter von KantenPosit(); wird hier nicht ausgewertet
CRing riz (CLZw);
bool bRet = false;	// noch keine Schnittergebnisse in CL eingetragen 

	for (riz.First(); riz.Valid(); riz.Next())
	{
	GeoObjektLock ml (riz);

		if (! ml)	// kein Zugriff möglich
		{
			DEX_Error (RC_clipping, EC_NOLOCK);
			continue;
		}

	GeoKante* pTK = (GeoKante*)(GeoObjekt*) ml;	// Teilkante aus CLZw
	bool bClosed = (pTK->SP(0) == pTK->SP(pTK->ASP()-1));

		for (int i = 1; i < iKAnz; i++)	// Abarbeitung aller pSFl-Inseln
		{
		MarkLine* pML1 = new MarkLine (pTK->ASP(), -1, bClosed);
		MarkLine* pML2 = new MarkLine (pSFl->KA(i).ASP(), i, true/*, false*/);

			if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
			{
				DEX_Error (RC_clipping, EC_NOMEMORY);
				DELETE_OBJ (pML1); DELETE_OBJ (pML2);
				return false;
			}

			if (!pTK->Aufbereitung2 (&pSFl->KA(i), pML1, pML2, bLeer, bAbbr, 0))
			{
				DELETE_OBJ (pML1); DELETE_OBJ (pML2);
				if (bLeer) continue;		// ??? (11.11.98)
				return false;
			}

		// Lage der pTK-Teilkante aus CLZw bez. der pSFl-Insel bestimmen
		Posit PosLage = KantenPosit (&pSFl->KA(i), pML1, bOverlap, iTouchOut);

			if ((INNAUSS == PosLage || (INNERHB == PosLage && bOverlap)) &&
				TeilKanten2 (pML1, pML2, ObjNr(), Id(), LINN, CL))
				bRet = true;

			DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		}
	}

	return bRet;

} // MesserInselnAUSS


// --------------------------------------------------------------------------------------------
// Inseln bei Schnitt der this-Kante mit pSFl-Schnittfläche berücksichtigen
// (ulLageAusw == LKONT);  die ersten iSkip Einträge in CL werden übergangen;
// Rückgabe von true, wenn geschnitten wurde und damit Schnittergebnisse in CL eingetragen
// wurden, ansonsten false
bool GeoKante :: MesserInselnKONT (EFlaeche* pSFl, ClipListe& CL)
{
	_ASSERTE (pSFl != 0);

	if (! pSFl) return false;

int iKAnz = pSFl->KantenAnz();

	if (1 == iKAnz) return true;	// keine Inseln

// Teile der this-Kante erzeugen, die innerhalb der pSFl-Schnittfläche liegen, und diese Teile
// mit den pSFl-Inseln schneiden; alles was auf der Kontur einer pSFl-Insel liegt wird als
// Teilkante in CL eingetragen
bool bClosed = (SP(0) == SP(_Size-1));
MarkLine* pML1 = new MarkLine (_Size, -1, bClosed);
MarkLine* pML2 = new MarkLine (pSFl->KA(0).ASP(), 0);

	if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
	{
		DEX_Error (RC_clipping, EC_NOMEMORY);
		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		return false;
	}

bool bLeer, bAbbr;	// Parameter von Aufbereitung2(); werden hier nicht ausgewertet

	if (!Aufbereitung2 (&pSFl->KA(0), pML1, pML2, bLeer, bAbbr, 0))
	{
		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		return false;
	}

ClipListe CLZw;	// ClipListe für Zwischenergebnisse

	TeilKanten2 (pML1, pML2, ObjNr(), Id(), LINN, CLZw);

	DELETE_OBJ (pML1); DELETE_OBJ (pML2);

bool bOverlap;		// this-Kante hat mit einer pSFl-Insel einen Überlappungsbereich
int iTouchOut;		// Parameter von KantenPosit(); wird hier nicht ausgewertet
CRing riz (CLZw);
bool bRet = false;	// noch keine Schnittergebnisse in CL eingetragen 

	for (riz.First(); riz.Valid(); riz.Next())
	{
	GeoObjektLock ml (riz);

		if (! ml)	// kein Zugriff möglich
		{
			DEX_Error (RC_clipping, EC_NOLOCK);
			continue;
		}

	GeoKante* pTK = (GeoKante*)(GeoObjekt*) ml;	// Teilkante aus CLZw
	bool bClosed = (pTK->SP(0) == pTK->SP(pTK->ASP()-1));

		for (int i = 1; i < iKAnz; i++)	// Abarbeitung aller pSFl-Inseln
		{
		MarkLine* pML1 = new MarkLine (pTK->ASP(), -1, bClosed);
		MarkLine* pML2 = new MarkLine (pSFl->KA(i).ASP(), i, true);

			if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
			{
				DEX_Error (RC_clipping, EC_NOMEMORY);
				DELETE_OBJ (pML1); DELETE_OBJ (pML2);
				return false;
			}

			if (!pTK->Aufbereitung2 (&pSFl->KA(i), pML1, pML2, bLeer, bAbbr, 0))
			{
				DELETE_OBJ (pML1); DELETE_OBJ (pML2);
				if (bLeer) continue;		// ??? (11.11.98)
				return false;
			}

		// Lage der pTK-Teilkante aus CLZw bez. der pSFl-Insel bestimmen
		Posit posLage = KantenPosit (&pSFl->KA(i), pML1, bOverlap, iTouchOut);

			if ((INNAUSS == posLage ||
				((INNERHB == posLage || AUSSERHB == posLage) && bOverlap)) &&
				TeilKanten2 (pML1, pML2, ObjNr(), Id(), LKONT, CL))
				bRet = true;

			DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		}
	}

	return bRet;

} // MesserInselnKONT


// --------------------------------------------------------------------------------------------
// Eintrag einer (Teil)Kante in die ClipListe; liefert true zurück, wenn Eintrag
// möglich war, sonst false
bool _GEOMETR_EXPORT GeoKante :: AddClipObjekt (ClipListe& CL)
{
	_ASSERTE (_Size >= 2);

GeoObjektCreator GOC (CL);

	if (ContCreate (GOC, GeoKante) (*this))
		return true;

	DEX_Error (RC_clipping, EC_NOMEMORY);
	return false;

} // GeoKante :: AddClipObjekt




///////////////////////////////////////////////////////////////////////////////////////////////
// Methoden für das GeoObjekt: GEOFLAECHE
// Clipping für Fläche: pSO schneidet this-Fläche und erzeugt dabei evtl. mehrere Teilflächen,
// die in CL eingetragen werden;
// Wird this-Fläche geschnitten, wird true zurückgegeben, sonst false;
// bAbbr = true, wenn Schnittoperation abgebrochen wurde, sonst false
bool _GEOMETR_EXPORT GeoFlaeche :: Clipping (EObjekt* pSO, int iOT, ulong ulLageAusw,
						   ClipListe& CL, int iSkip, Posit& posLage, bool& bAbbr, void* pPSt)
{
	_ASSERTE (NULL != pSO);	// pPSt kann 0 sein

	bAbbr = false;
	if (! pSO) return false;

	switch (iOT)
	{
		case OT_KANTE:
			return ClippingMitKante ((EKante*)pSO, CL, iSkip, bAbbr, pPSt);
		case OT_FLAECHE:
			return ClippingMitFlaeche ((EFlaeche*)pSO, ulLageAusw, CL, iSkip, posLage, bAbbr,
									   pPSt);
		default:
			_ASSERTE (false);
			return false;	// kein zulässiger Objekttyp
	}

} // GeoFlaeche :: Clipping


// --------------------------------------------------------------------------------------------
// this-Fläche wird durch pSKt-EKante geschnitten
// Test, ob die Objektcontainer der this-Fläche und der schneidenden pSKt-EKante
// durchschnittsleer sind, wird in Routine Aufbereitung1() durchgeführt und dabei außerdem der
// Prozentzähler weitergestellt
bool _GEOMETR_EXPORT GeoFlaeche :: ClippingMitKante (EKante* pSKt, ClipListe& CL, int iSkip,
													 bool& bAbbr, void* pPSt)
{
	_ASSERTE (pSKt != 0);	// pPSt kann 0 sein

// #HK030327
	PartialCleaningForLines(&_KAF[0]);
	PartialCleaningForLines(pSKt);

bool bRet = false;	// return-Wert

// aus Stützpunktfolge der this-Flächenkontur wird Vektor pML1, aus Stützpunktfolge der
// pSKt-EKante wird Vektor pML2 mit markierten Punkten erzeugt; diese Vektoren werden in
// Aufbereitung1() evtl. noch erweitert
bool bClosed = (pSKt->SP(0) == pSKt->SP(pSKt->ASP()-1));
MarkLine* pML1 = new MarkLine (_KAF[0].ASP(), 0);
MarkLine* pML2 = new MarkLine (pSKt->ASP(), -1, bClosed);

	if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
	{
		DEX_Error (RC_clipping, EC_NOMEMORY);
		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		return false;
	}

	// pML1 und pML2 werden evtl. durch Routine Aufbereitung1() modifiziert; zurückgegeben
	// werden die um die Schnittpunkte erweiterten Vektoren pML1 und pML2
	if (!_KAF[0].Aufbereitung1 (pSKt, pML1, pML2, bAbbr, pPSt))
	{
		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		return false;
	}

	// Routine FlaecheZerlegt() ermittelt, ob die zu schneidende this-Fläche (pML1) überhaupt
	// durch die schneidende pSKt-EKante (pML2) zerlegt wird (true) oder nicht
	if (FlaecheZerlegt (pSKt, pML1))
		bRet = TeilFlaechen1 (pML1, pML2, ObjNr(), Id(), CL);

	DELETE_OBJ (pML1); DELETE_OBJ (pML2);

	// Inseln der this-Fläche (evtl.) berücksichtigen
	if (bRet &&		// Teilflächen wurden erzeugt
		_Size > 1)	// this-Fläche hat Inseln
		InselnBeiSchnittMitKante (CL, iSkip);

	return bRet;
	
} // GeoFlaeche :: ClippingMitKante


// --------------------------------------------------------------------------------------------
// this-Fläche wird durch pSFl-Fläche geschnitten
// Test, ob die Objektcontainer der this-Fläche und der schneidenden pSFl-Fläche
// durchschnittsleer sind, wird in Routine Aufbereitung2() durchgeführt und dabei außerdem der
// Prozentzähler weitergestellt
bool _GEOMETR_EXPORT GeoFlaeche :: ClippingMitFlaeche (EFlaeche* pSFl, ulong ulLageAusw,
						   ClipListe& CL, int iSkip, Posit& posLage, bool& bAbbr, void* pPSt)
{
	_ASSERTE (pSFl != 0); 	// pPSt != 0 wird weiter unten gestestet

// #HK030307
	PartialCleaningForLines(&_KAF[0]);
	PartialCleaningForLines(&pSFl->KA(0));

// aus Stützpunktfolge der this-Flächenkontur wird Vektor pML1, aus Stützpunktfolge der
// pSFl-Fläche wird Vektor pML2 mit markierten Punkten erzeugt; diese Vektoren werden in
// Aufbereitung2() evtl. noch erweitert
MarkLine* pML1 = new MarkLine (_KAF[0].ASP(), 0);
MarkLine* pML2 = new MarkLine (pSFl->KA(0).ASP(), 0);

	if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
	{
		DEX_Error (RC_clipping, EC_NOMEMORY);
		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		return false;
	}

// pML1 und pML2 werden evtl. durch Routine Aufbereitung2() modifiziert; zurückgegeben
// werden die um die Schnittpunkte erweiterten Vektoren pML1 und pML2
bool bLeer;		// Container der beiden mit Aufbereitung2() verglichenen Objekte sind
				//  durchschnittsleer (true)

	if (!_KAF[0].Aufbereitung2 (&pSFl->KA(0), pML1, pML2, bLeer, bAbbr, pPSt))
	{
		if (bLeer)	// beide Container sind durchschnittsleer
			posLage = AUSSERH;
		else posLage = UNKLAR;
		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		return false;
	}

// Routine KantenPosit() ermittelt, ob die Außenkontur der zu schneidenden this-Fläche pML1
// überhaupt durch die Außenkontur der pSFl-Fläche zerlegt wird (posLage == INNAUSS) oder
// nicht; in letzterem Fall liegt this-Fläche außerhalb (AUSSERH bzw. AUSSERHB) bzw. innerhalb
// (INNERH bzw. INNERHB) von pSFl;
// für posLage == UMSCHL bzw. UMSCHLB liegt pSFl vollständig innerhalb der this-Fläche, d.h.
// die this-Fläche umschließt pSFl
bool bOverlap;	// this-Fläche hat mit der pSFl-Außenkontur einen Überlappungsbereich
int iTouchOut;	// iTouchOut Berührungspunkte mit "Zuführung" aus der Umgebung der
				// pSFl-Außenkontur gemeinsam

	posLage = KantenPosit (&pSFl->KA(0), pML1, bOverlap, iTouchOut);

// keine Zerlegung
	if (posLage == AUSSERH || posLage == AUSSERHB)
	{
		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		return false;
	}

// Spezialfall: die zu schneidende this-Fläche liegt innerhalb der Außenkontur der schneidenden
// pSFl-Fläche; es ist noch zu prüfen, ob this-Fläche in eine pSFl-Insel hineinragt
	if (INNERH == posLage || INNERHB == posLage || KONTUR == posLage || GLEICH == posLage)
	{
	bool bRet =	MesserAusserhalb (pSFl, ulLageAusw, CL, iSkip);

		DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		return bRet;
	}

// Spezialfall: schneidende pSFl-Fläche liegt innerhalb der Außenkontur der zu schneidenden
// this-Fläche
	if (posLage == UMSCHL || posLage == UMSCHLB)
	{
	bool bEnde;	// true, wenn durch Routine MesserInnerhalb() alles erledigt wurde
	bool bRet =	MesserInnerhalb (pSFl, ulLageAusw, CL, iSkip, bOverlap, iTouchOut, bEnde);

		if (bEnde)
		{
			DELETE_OBJ (pML1); DELETE_OBJ (pML2);
			return bRet;
		}
	}

// Zerlegen in Teilflächen
bool bRet =	TeilFlaechen2 (pML1, pML2, ObjNr(), Id(), ulLageAusw, CL);

	DELETE_OBJ (pML1); DELETE_OBJ (pML2);

	// Inseln berücksichtigen
	if (bRet &&									// Teilflächen wurden erzeugt
		(_Size > 1 || pSFl->KantenAnz() > 1))	// wenigstens eine Fläche hat Inseln
	{
		if (ulLageAusw & LINN)
			InselnBeiSchnittMitFlaeche (pSFl, CL, iSkip);
		if (ulLageAusw & LAUSS)
			InselnBeiSchnittMitFlaecheAUSS (pSFl, CL, iSkip);
	}

	return bRet;

} // GeoFlaeche :: ClippingMitFlaeche


// --------------------------------------------------------------------------------------------
// Hilfsroutine für GeoFlaeche::ClippingMitFlaeche() für den Fall, daß schneidende pSFl-Fläche
// innerhalb der Außenkontur der zu schneidenden this-Fläche liegt;
// werden Teilflächen in CL eingetragen, wird true zurückgegeben, sonst false
bool GeoFlaeche :: MesserInnerhalb (EFlaeche* pSFl, ulong ulLageAusw, ClipListe& CL,
									int iSkip, bool bOverlap , int iTouchOut, bool& bEnde)
{
	_ASSERTE (pSFl != 0);

	bEnde = true;

// Test, ob pSFl-Außenkontur nicht vielleicht innerhalb einer this-Insel liegt, dann wäre kein
// Schnitt möglich
bool bOver;	// Parameter von LageKonturZuKontur(); werden
int iTouch;	// hier nicht ausgewertet

	for (int i = 1; i < _Size; i++)		// this-Inseln
	{
	MarkLine* pML1 = new MarkLine (pSFl->KA(0).ASP(), 0);
	MarkLine* pML2 = new MarkLine (_KAF[i].ASP(), i, true/*, false*/);

		if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
		{
			DEX_Error (RC_clipping, EC_NOMEMORY);
			DELETE_OBJ (pML1); DELETE_OBJ (pML2);
			return false;
		}

	Posit posLage = pSFl->KA(0).LageKonturZuKontur (&_KAF[i], pML1, pML2, bOver, iTouch);

		DELETE_OBJ (pML1); DELETE_OBJ (pML2);

		if (INNERH == posLage || INNERHB == posLage || KONTUR == posLage ||
			GLEICH == posLage || OFFEN == posLage || UNKLAR == posLage)
			return false;	// kein Schnitt möglich

		if (INNAUSS == posLage || UMSCHL == posLage || UMSCHLB == posLage)	// 28.10.98
			break;
	} // for

int iKAnz = pSFl->KantenAnz();
bool bRet = false;	// return-Wert dieser Routine

	// Wenn "innerhalb" gewählt wurde, dann ist die Außenkontur der Ergebnisfläche der Teil der
	// this-Fläche, der innerhalb von pSFl liegt, d.h. pSFl-Außenkontur mit Identifikator der
	// this-Fläche
	if (ulLageAusw & LINN)
	{
	EFlaeche* pNewArea = new EFlaeche (&pSFl->KA(0), 1);

		if (! pNewArea)
		{
			DEX_Error (RC_clipping, EC_NOMEMORY);
			return false;
		}

		GeoFlaeche(ObjNr(), Id(), *pNewArea).AddClipObjekt (CL);
		DELETE_OBJ (pNewArea);

		// Inseln berücksichtigen
		if (_Size > 1 || iKAnz > 1)	// wenigstens eine Fläche hat Inseln
			InselnBeiSchnittMitFlaeche (pSFl, CL, iSkip);
		bRet = true;
	}
			
	// Wenn "außerhalb" gewählt wurde und beide Außenkonturen sich höchstens in einem Punkt
	// berühren, dann entstehen als Ergebnisflächen die this-Außenkontur mit der
	// pSFl-Außenkontur als Insel sowie die pSFl-Innenkonturen als separate Flächen, zu denen
	// dann noch die this- bzw. pSFl-Inseln hinzuzunehmen sind.
	if (ulLageAusw & LAUSS)
	{
		if (iTouchOut <= 1 && !bOverlap)	// beide Außenkonturen berühren sich höchstens in einem
		{								// Punkt
		EFlaeche* pNewArea = new EFlaeche (&pSFl->KA(0), 1);
		EFlaeche* pNewAus = new EFlaeche (&_KAF[0], 1);

			if (!pNewArea || !pNewAus)
			{
				DELETE_OBJ (pNewArea);
				DEX_Error (RC_clipping, EC_NOMEMORY);
				return false;
			}

		GeoFlaeche* pGF = new GeoFlaeche (ObjNr(), Id(), *pNewAus);

			DELETE_OBJ (pNewAus);

			if (! pGF)
			{
				DEX_Error (RC_clipping, EC_NOMEMORY);
				return false;
			}

			// eine Außenkontur wird zur Innenkontur, deshalb Orientierung drehen
			pNewArea->OrientDreh (0);
			pGF->AddKante (*pNewArea, 1, -1);	// als Insel hinzufügen
			DELETE_OBJ (pNewArea);
			pGF->AddClipObjekt (CL);
			DELETE_OBJ (pGF);

			// Inseln berücksichtigen
			if (_Size > 1 || iKAnz > 1)	// wenigstens eine Fläche hat Inseln
				InselnBeiSchnittMitFlaecheAUSS (pSFl, CL, iSkip);
			bRet = true;
		}
		else
			bEnde = false;	// Weiterbearbeitung mit Routine TeilFlaechen2() erforderlich
	}

	return bRet;

} // MesserInnerhalb


// --------------------------------------------------------------------------------------------
// Hilfsroutine für InselZweiteFlaecheAUSS() für den Fall, daß schneidende pSFl-Insel pKont
// innerhalb der this-Außenkontur liegt; dann noch Test, wie pKont zu den this-Innenkonturen
// liegt. Rückgabe von true, wenn in CL weitere Schnittergebnisse eingetragen werden.
bool GeoFlaeche :: MesserinselInnerhalb (EKante* pKont, int iKInd, ClipListe& CL,
										 int iSkip)
{
	_ASSERTE (pKont != 0);

//	if (1 == _Size) return false;	// 11.09.98

/* 29.10.98
// die pSFl-Insel pKont ist auf jeden Fall in CL abzulegen, egal ob die zu schneidende
// this-Fläche Inseln hat oder nicht
EFlaeche* pNewArea = new EFlaeche (&pKont, 1);

	if (! pNewArea)
	{
		DEX_Error (RC_clipping, EC_NOMEMORY);
		return false;
	}

	pNewArea->OrientDreh (0);	// Insel wird zur Außenkontur, deshalb drehen
	GeoFlaeche(ObjNr(), Id(), *pNewArea).AddClipObjekt (CL);
	DELETE_OBJ (pNewArea);

	if (1 == _Size)
		return true;
*/

bool bOverlap;	// Parameter von LageKonturZuKontur(); werden
int iTouchOut;	// hier nicht ausgewertet

	// Test, ob pSFl-Insel pKont nicht vielleicht innerhalb einer this-Insel liegt, dann
	// wäre kein Schnitt möglich
	for (int i = 1; i < _Size; i++)	// this-Inseln
	{
	MarkLine* pML1 = new MarkLine (pKont->ASP(), iKInd, true/*, false*/);
	MarkLine* pML2 = new MarkLine (_KAF[i].ASP(), i, true/*, false*/);

		if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
		{
			DEX_Error (RC_clipping, EC_NOMEMORY);
			DELETE_OBJ (pML1); DELETE_OBJ (pML2);
			return false;
		}

	Posit posLage = pKont->LageKonturZuKontur (&_KAF[i], pML1, pML2, bOverlap, iTouchOut);

		DELETE_OBJ (pML1); DELETE_OBJ (pML2);

		if (INNERH == posLage || INNERHB == posLage || KONTUR == posLage || GLEICH == posLage)
			return false;	// kein Schnitt möglich
	} // for

EFlaeche* pNewArea = new EFlaeche (&pKont, 1);

	if (! pNewArea)
	{
		DEX_Error (RC_clipping, EC_NOMEMORY);
		return false;
	}

	pNewArea->OrientDreh (0);			// Insel wird zur Außenkontur, deshalb drehen
	GeoFlaeche(ObjNr(), Id(), *pNewArea).AddClipObjekt (CL);
	DELETE_OBJ (pNewArea);

	if (_Size > 1)
		InselnBeiSchnittMitKante (CL, iSkip);	// this-Inseln berücksichtigen

	return true;

} // MesserinselInnerhalb


// --------------------------------------------------------------------------------------------
// Hilfsroutine für GeoFlaeche::ClippingMitFlaeche() für den Fall, daß zu schneidende
// this-Fläche innerhalb der Außenkontur der schneidende pSFl-Fläche liegt;
// Rückgabe von true, wenn geschnitten wurde und damit Schnittergebnisse in CL eingetragen
// wurden, ansonsten false
bool GeoFlaeche :: MesserAusserhalb (EFlaeche* pSFl, ulong ulLageAusw, ClipListe& CL,
									 int iSkip)
{
	_ASSERTE (pSFl != 0);

int iKAnz = pSFl->KantenAnz();

	if (iKAnz == 1) return false;
	
// Feld für die Indizes der pSFl-Inseln, die noch mit den this-Inseln zu vergleichen sind
int k = 0;	// Laufindex für piInsel
int* piInsel = new int[iKAnz];	

	if (! piInsel)
	{
		DEX_Error (RC_clipping, EC_NOMEMORY);
		return false;
	}

	memset (piInsel, 0 , iKAnz*sizeof(int));

bool bOverlap;	// Parameter von LageKonturZuKontur(); werden
int iTouchOut;	// hier nicht ausgewertet

	// Lage der pSFl-Inseln zu der this-Außenkontur
	for (int i = 1; i < iKAnz; i++)			// pSFl-Inseln
	{
	MarkLine* pML1 = new MarkLine (pSFl->KA(i).ASP(), i, true/*, false*/);
	MarkLine* pML2 = new MarkLine (_KAF[0].ASP(), 0);

		if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
		{
			DEX_Error (RC_clipping, EC_NOMEMORY);
			DELETE_OBJ (pML1); DELETE_OBJ (pML2);
			DELETE_VEC (piInsel);
			return false;
		}

	Posit posLage = pSFl->KA(i).LageKonturZuKontur (&_KAF[0], pML1, pML2, bOverlap, iTouchOut);

		DELETE_OBJ (pML1); DELETE_OBJ (pML2);

		if (posLage == INNAUSS)
		{
			if (ulLageAusw & LINN)	// Schnittergebnis "innerhalb"
			{
				DELETE_VEC (piInsel);

			EFlaeche* pNewArea = new EFlaeche (&_KAF[0], 1);

				if (! pNewArea)
				{
					DEX_Error (RC_clipping, EC_NOMEMORY);
					return false;
				}

				// this-Außenkontur nach CL
				GeoFlaeche(ObjNr(), Id(), *pNewArea).AddClipObjekt (CL);
				DELETE_OBJ (pNewArea);

				InselnBeiSchnittMitFlaeche (pSFl, CL, iSkip);
				return true;
			}
			else				// Schnittergebnis "außerhalb"
			{
				InselnBeiSchnittMitFlaecheAUSS (pSFl, CL, iSkip);	// erst ab 11.09.98
				return true;
			}
		}

		// eine pSFl-Insel liegt innerhalb der this-Außenkontur, deshalb sind die this-Inseln
		// noch zu Rate zu ziehen
		if (posLage == INNERH || posLage == INNERHB)
		{
			piInsel[k] = i;
			k++;
			continue;
		}

		// eine pSFl-Insel umschließt die this-Außenkontur
		if (UMSCHL == posLage || UMSCHLB == posLage || KONTUR == posLage ||
			GLEICH == posLage || OFFEN == posLage || UNKLAR == posLage)
		{
			DELETE_VEC (piInsel);
			return false;	// kein Schnitt möglich
		}
	} // for

	// noch weitere Tests mit den this-Innenkonturen (so sie vorhanden sind)
	if (0 != piInsel[0])
		MesserAusserhalbWeiter (pSFl, ulLageAusw, CL, iSkip, piInsel);

	DELETE_VEC (piInsel);

	return true;	// 11.09.98 ("true", weil sonst die Originalobjekte nicht angezeigt werden)

} // MesserAusserhalb


// --------------------------------------------------------------------------------------------
// Hilfsroutine für MesserAusserhalb() für den Fall, daß mindestens eine pSFl-Insel innerhalb
// der this-Außenkontur liegt; wenn für mindestens eine dieser pSFl-Inseln gilt, daß sie nicht
// innerhalb einer this-Insel liegen, kann geschnitten werden;
// Rückgabe von true, wenn geschnitten wurde und damit Schnittergebnisse in CL eingetragen
// wurden, ansonsten false
bool GeoFlaeche :: MesserAusserhalbWeiter (EFlaeche* pSFl, ulong ulLageAusw, ClipListe& CL,
										   int iSkip, int* piInsel)
{
	_ASSERTE (pSFl != 0);
	_ASSERTE (piInsel != 0);

	if (0 == piInsel[0]) return false;

bool bAbbr = false;	// true: Abbruch der while-Schleife
int k = 0;			// Laufindex für piInsel
bool bOverlap;		// Parameter von LageKonturZuKontur(); werden hier
int iTouchOut;		// nicht ausgewertet

	// Lage der pSFl-Inseln, die innerhalb der this-Außenkontur liegen, zu den this-Inseln
	while (0 != piInsel[k])	// pSFl-Inseln
	{
	int i = piInsel[k];	// Index für die pSFl-Inseln, die innerhalb der this-Außenkontur liegen 

		for (int ii = 1; ii < _Size; ii++)	// this-Inseln
		{
		MarkLine* pML1 = new MarkLine (pSFl->KA(i).ASP(), i, true/*, false*/);
		MarkLine* pML2 = new MarkLine (_KAF[ii].ASP(), ii, true/*, false*/);

			if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
			{
				DEX_Error (RC_clipping, EC_NOMEMORY);
				DELETE_OBJ (pML1); DELETE_OBJ (pML2);
				return false;
			}

		Posit posLage = pSFl->KA(i).LageKonturZuKontur (&_KAF[ii], pML1, pML2, bOverlap, iTouchOut);

			DELETE_OBJ (pML1); DELETE_OBJ (pML2);

			if (INNERH == posLage || INNERHB == posLage || KONTUR == posLage ||
				GLEICH == posLage || OFFEN == posLage || UNKLAR == posLage)
			{
				bAbbr = true;
				// for-Schleife abbrechen, da getestete pSFl-Insel innerhalb einer this-Insel
				// liegt; es muß aber einer pSFl-Insel gefunden werden, die außerhalb von allen
				// this-Inseln liegt
				break;
			}

			if (posLage == INNAUSS)	// 15.03.99
			{
				bAbbr = false;
				break;
			}
		} // for

		if (bAbbr) k++;
		else
			// wenn for-Schleife nicht abgebrochen wurde, gibt es mindestens eine pSFl-Insel,
			// die nicht innerhalb einer this-Insel liegt, d.h. es kann geschnitten werden und
			// deshalb gleich while-Schleife abbrechen
			break;

	} // while

	if (bAbbr) return false;	// kein Schnitt möglich

bool bRet1 = false;	// return-Werte
bool bRet2 = false;

	if (ulLageAusw & LINN)	// Schnittergebnis "innerhalb"
	{
		GeoFlaeche(ObjNr(), Id(), *this).AddClipObjekt (CL);	// this-Fläche nach CL
//		InselnAmRand (CL, iSkip, piVbInsel, bModify);		????????
		pSFl->InselnInnerhalb (CL, iSkip);		// pSFl-Inseln noch berückichtigen
		bRet1 = true;
	}

	if (ulLageAusw & LAUSS)	// Schnittergebnis "außerhalb" (29.10.98)
		bRet2 = InselZweiteFlaecheAUSS (pSFl, CL);

	return bRet1 || bRet2;

} // MesserAusserhalbWeiter


// --------------------------------------------------------------------------------------------
// Eintrag einer (Teil)Fläche in die ClipListe; liefert true zurück, wenn Eintrag möglich war,
// sonst false
bool _GEOMETR_EXPORT GeoFlaeche :: AddClipObjekt (ClipListe& CL)
{
	for (int i = 0; i < _Size; i++)
		_ASSERTE (_KAF[i].ASP() >= 4);

GeoObjektCreator GOC (CL);

	if (ContCreate (GOC, GeoFlaeche) (*this))
		return true;

	DEX_Error (RC_clipping, EC_NOMEMORY);
	return false;

} // GeoFlaeche :: AddClipObjekt


// --------------------------------------------------------------------------------------------
// Inseln bei Schnittoperationen der zu schneidenden this-Fläche mit der schneidenden
// pSFl-Fläche berücksichtigen, für den Fall, daß für Schnittergebnis "außerhalb" gewählt wurde
bool GeoFlaeche :: InselnBeiSchnittMitFlaecheAUSS (EFlaeche* pSFl, ClipListe& CL, int iSkip)
{
	_ASSERTE (pSFl != 0);

bool bRet1 = true;
bool bRet2 = true;

	if (_Size > 1)		// zu schneidende this-Fläche hat Inseln
	{
	bool bModify1 = false;	// an mindestens einer CL-Fläche wurden durch die this-Inseln
							// Veränderungen vorgenommen (true)
	int* piVbInsel1 = new int[_Size];

		if (! piVbInsel1)
		{
			DEX_Error (RC_clipping, EC_NOMEMORY);
			return false;
		}

		memset (piVbInsel1, 0 , _Size*sizeof(int));

		if (!InselnAmRand (CL, iSkip, piVbInsel1, bModify1))
			bRet1 = false;

		// letzter Parameter "false", da schon Inseln vorhanden sein können (für den Fall, daß
		// schneidende Fläche innerhalb der zu schneidenden liegt)
		if (!InselnInnerhalb (CL, iSkip))
			bRet1 = false;
	}

	if (pSFl->KantenAnz() > 1)	// schneidende pSFl-Fläche hat Inseln
		// Test, wie die pSFl-Inseln zu der zu this-Fläche liegen
		bRet2 = InselZweiteFlaecheAUSS (pSFl, CL);

	return bRet1 && bRet2;

} // InselnBeiSchnittMitFlaecheAUSS


// --------------------------------------------------------------------------------------------
// Wenn bei Schnitt der this-Fläche durch die pSFl-Fläche die Schnittergebnisse außerhalb der
// schneidenden Fläche liegen sollen, wird hier geprüft, wie die pSFl-Inseln zur this-Fläche
// (NICHT zu den CL-Flächen) liegen.
// Wenn weitere Schnittergebnisse in CL eingetragen werden, dann wird true zurückgegeben, sonst
// false.
// Ich hoffe, daß durch folgende kühne Überlegung alle denkbaren Fälle abgefangen werden:
// Aus jeder SFl-Insel wird eine neue schneidende Fläche (ohne Inseln !) gebildet, die die
// this-Fläche (i.a. mit Inseln) mit "innerhalb" schneidet. Die Ergebnisse werden erst in einer
// Zwischenliste CLZw abgelegt und dann nach CL übertragen !!!!!
bool GeoFlaeche :: InselZweiteFlaecheAUSS (EFlaeche* pSFl, ClipListe& CL)
{
	_ASSERTE (pSFl != 0);

int iKAnz = pSFl->KantenAnz();

	if (iKAnz == 1) return false;

bool bOverlap;		// Parameter von LageKonturZuKontur(); werden
int iTouchOut;		// hier nicht ausgewertet
bool bRet = false;	// return-Wert dieser Routine
ClipListe CLZw;		// ClipListe für Zwischenergebnisse

	// Test, ob sich eine pSFl-Insel mit der this-Außenkontur schneidet
	for (int i = 1; i < iKAnz; i++)
	{
	MarkLine* pML1 = new MarkLine (_KAF[0].ASP(), 0);
	MarkLine* pML2 = new MarkLine (pSFl->KA(i).ASP(), i, true);

		if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
		{
			DEX_Error (RC_clipping, EC_NOMEMORY);
			DELETE_OBJ (pML1); DELETE_OBJ (pML2);
			return false;
		}

	Posit posLage = _KAF[0].LageKonturZuKontur (&pSFl->KA(i), pML1, pML2, bOverlap, iTouchOut);

		// keine weiteren Schnittergebnisse, wenn die zu schneidende this-Fläche innerhalb der
		// schneidenden pSFl-Insel liegt
		if (INNERH == posLage || INNERHB == posLage || KONTUR == posLage ||
			GLEICH == posLage || UNKLAR == posLage || OFFEN == posLage)
		{
			DELETE_OBJ (pML1); DELETE_OBJ (pML2);
			return false;
		}

// wenn die beiden nachfolgenden Zeilen drin blieben, müßte DELETE_OBJ (pML1); DELETE_OBJ (pML2);
// hinzugefügt werden (29.10.98)
//		if (posLage == AUSSERH || posLage == AUSSERHB)
//			continue;

		// schneidende pSFl-Insel liegt innerhalb der Außenkontur der zu schneidenden
		// this-Fläche; dann Test mit den this-Innenkonturen
		if (posLage == UMSCHL || posLage == UMSCHLB)
			MesserinselInnerhalb (&pSFl->KA(i), i, CLZw, 0);

		// pSFl-Insel schneidet die Außenkontur der this-Fläche;
		// dann Schnitt mit der this-Außenkontur pML1 und Test mit den this-Innenkonturen
		if (posLage == INNAUSS)
		{
			TeilFlaechen2 (pML1, pML2, ObjNr(), Id(), LINN, CLZw);
			InselnBeiSchnittMitKante (CLZw, 0);	// in CLZw braucht nichts übergangen zu werden
		}

		DELETE_OBJ (pML1); DELETE_OBJ (pML2);

		// wenn in CLZw Zwischenergebnisse abgelegt wurden, dann diese jetzt nach CL übernehmen
		if (CLZw.Count() > 0)
		{
		CRing riz (CLZw);

			for (riz.First(); riz.Valid(); riz.Next())
			{
			GeoObjektLock mlz (riz);

				if (! mlz) continue;	// kein Zugriff möglich
				mlz->AddClipObjekt (CL);
			}

			CLZw.EveryDelete();
			bRet = true;
		}
	} // for

	return bRet;

} // InselZweiteFlaecheAUSS


// --------------------------------------------------------------------------------------------
// Hilfsroutine für InselnInnerhalb(); zu der this-Fläche mit Inseln wird als zusätzliche Insel
// pKont hinzugenommen, dabei sind evtl. Überschneidungen mit den this-Inseln zu
// berücksichtigen
bool GeoFlaeche :: InselZweiteFlaeche (ClipListe& CL, EKante* pKont, int iKInd)
{
	_ASSERTE (pKont != 0);

// Insel nach möglicherweise mehreren Vereinigungen
EFlaeche* pNewIsland = new EFlaeche (pKont, 1);

	if (! pNewIsland)
	{
		DEX_Error (RC_clipping, EC_NOMEMORY);
		return false;
	}

	if (1 == _Size)	// this-Fläche hat keine Inseln
	{
		AddKante (*pNewIsland, 1, -1);	// neue Insel einfach so hinzufügen
		DELETE_OBJ (pNewIsland);
		return true;
	}

// Abarbeitung aller this-Inseln, d.h. aller Inseln der 1. Fläche, die innerhalb der Teilfläche
// liegen und dieser schon zugeordnet sind
bool bOverlap;	// pNewIsland hat mit dem Rand einer this-Insel einen Überlappungsbereich
int iTouchOut;	// Parameter von LageKonturZuKontur(); wird hier nicht ausgewertet

	for (int i = 1; i < _Size; i++)
	{
//	MarkLine* pML1 = new MarkLine (pKont->ASP(), iKInd, true, false);
	MarkLine* pML1 = new MarkLine (pNewIsland->KA(0).ASP(), iKInd, true/*, false*/);	// 16.03.99
	MarkLine* pML2 = new MarkLine (_KAF[i].ASP(), i, true/*, false*/);

		if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
		{
			DEX_Error (RC_clipping, EC_NOMEMORY);
			DELETE_OBJ (pML1); DELETE_OBJ (pML2);
			DELETE_OBJ (pNewIsland);
			return false;
		}

	// Lage der (vereinigten) Insel pNewIsland zur this-Insel _KAF[i]
//	Posit posLage = pKont->LageKonturZuKontur (&_KAF[i], pML1, pML2, bOverlap, iTouchOut);
	Posit posLage = pNewIsland->KA(0).LageKonturZuKontur (&_KAF[i], pML1, pML2, bOverlap, iTouchOut);	// 16.03.99

		if (INNAUSS != posLage && AUSSERHB != posLage)
		{
			DELETE_OBJ (pML1); DELETE_OBJ (pML2);
		}

		switch (posLage)
		{
			case INNERH:
			case INNERHB:
			case KONTUR:
			case GLEICH:
				DELETE_OBJ (pNewIsland);
				return true;	// hier brauche ich nichts zu machen

			case INNAUSS:	// beide Inseln vereinigen
				ZweiInselnVereinigen (CL, pNewIsland, pML1, pML2);	// 29.10.98
				DELETE_OBJ (pML1); DELETE_OBJ (pML2);
				SubKante (1, i);	// alte _KAF[i]-Insel herausnehmen

				// da jetzt eine Insel gelöscht wurde, hat jetzt die nächste den gleichen
				// Index, wie die soeben gelöschte; deshalb muß das "i++" in der for-Anweisung
				// neutralisiert werden
				i--;
				break;

// überflüssig (28.10.98)
//			case AUSSERH:		// hier kann ich noch nichts endgültiges entscheiden
//				break;

			case AUSSERHB:
				// wenn pNewIsland mit dem Rand der this-Insel keinen Überlappungsbereich hat,
				// kann ich noch nichts endgültiges entscheiden, ansonsten beide Inseln
				// vereinigen
				if (bOverlap)
				{
					ZweiInselnVereinigen (CL, pNewIsland, pML1, pML2);	// 29.10.98
					DELETE_OBJ (pML1); DELETE_OBJ (pML2);
					SubKante (1, i);	// alte _KAF[i]-Insel herausnehmen
					i--;
				}
				break;

			case UMSCHL:		// hier kann ich noch nichts endgültiges entscheiden
			case UMSCHLB:
				SubKante (1, i);	// alte _KAF[i]-Insel herausnehmen
				i--;
				break;

			case OFFEN:			// hier kann ich nichts machen
			case UNKLAR:
				DELETE_OBJ (pNewIsland);
				return false;

		} // switch
	} // for

	AddKante (*pNewIsland, 1, -1);	// neue (vereinigte) Insel hinzufügen

	DELETE_OBJ (pNewIsland);

	return true;

} // InselZweiteFlaeche


// --------------------------------------------------------------------------------------------
// Hilfsroutine für InselZweiteFlaeche()
bool GeoFlaeche :: ZweiInselnVereinigen (ClipListe& CL, EFlaeche*& pNewIsland, MarkLine* pML1,
										 MarkLine* pML2)
{
	_ASSERTE (pML1 != 0);
	_ASSERTE (pML2 != 0);

EFlaeche* pUniIsland = new EFlaeche();

	if (! pUniIsland)
	{
		DEX_Error (RC_clipping, EC_NOMEMORY);
		return false;
	}

//	ContourUnion (pML1, pML2, pUniIsland, true);
	ContourUnion (pML1, pML2, pUniIsland, false);	// sonst könnte "Insel in Insel" entstehen (28.05.99)

int iKCnt = pUniIsland->KantenAnz();

	for (int i = 0; i < iKCnt; i++)
	{
	EFlaeche* pNewArea = new EFlaeche (&pUniIsland->KA(i), 1);

		if (! pNewArea)
		{
			DELETE_OBJ (pUniIsland);
			DEX_Error (RC_clipping, EC_NOMEMORY);
			return false;
		}

		if (0 == i)
		{
			DELETE_OBJ (pNewIsland);
			pNewIsland = pNewArea;
		}

		// Innenkonturen von pUniIsland werden zu separaten Ergebnisflächen
		else
		{
			pNewArea->OrientDreh (0);			// Insel wird zur Außenkontur, deshalb drehen
			GeoFlaeche(ObjNr(), Id(), *pNewArea).AddClipObjekt (CL);
			DELETE_OBJ (pNewArea);
		}
	}

	DELETE_OBJ (pUniIsland);

	return true;

} // ZweiInselnVereinigen


// --------------------------------------------------------------------------------------------
// gemeinsame Konturabschnitte zweier Flächen werden in CL als Kanten bereitgestellt (true);
// in posLage wird die Lage der beiden Flächen zueinander angezeigt; gibt es keine gemeinsamen
// Konturabschnitte bzw. bei unzureichendem dynamischen Speicher, wird false zurückgegeben
bool _GEOMETR_EXPORT GeoFlaeche :: KonturGemeinsamkeiten (EFlaeche* pFl, ulong ulLageAusw,
														ClipListe& CL, bool& bAbbr, void* pPSt)
{
	_ASSERTE (pFl != 0);	// pPSt kann 0 sein

Posit posLage = EnthaltenIn (pFl);

// keine Berührung bzw. nicht erfüllte Auswahlbedingung
bool b1 = (INNERHB == posLage || KONTUR == posLage || GLEICH == posLage) && (ulLageAusw & LINN);
bool b2 = (AUSSERHB == posLage) && (ulLageAusw & LAUSS);
bool b3 = (UMSCHLB == posLage || INNAUSS == posLage) && (ulLageAusw & LINAU);

	if (!b1 && !b2 && !b3)
		return false;

bool bRet = false;		// return-Wert dieser Routine
int iKontAnz = pFl->KantenAnz();
bool bOverlap;	// this-Fläche hat mit einer pFl-Kontur einen Überlappungsbereich bzw.
int iTouchOut;	// Parameter von KantenPosit(); wird hier nicht ausgewertet
bool bLeer;		// Parameter von Aufbereitung2(); wird hier nicht ausgewertet
long lNInd;		// der auf einen Anfangsindex folgende Index eines Konturabschnittes
MarkLine* pML1 = 0;
MarkLine* pML2 = 0;

	for (int i = 0; i < _Size; i++)				// jede Kontur der this-Fläche mit
		for (int ii = 0; ii < iKontAnz; ii++)	//  jeder Kontur der pFl-Fläche vergleichen
		{
			// aus Stützpunktfolge einer this-Kontur wird Vektor pML1 mit markierten Punkten
			// erzeugt; dieser Vektor wird in Routine Aufbereitung2() evtl. noch erweitert
			DELETE_OBJ (pML1); DELETE_OBJ (pML2);

			pML1 = new MarkLine (_KAF[i].ASP(), i);
			pML2 = new MarkLine (pFl->KA(ii).ASP(), ii);

			if (!pML1 || !pML1->Vektor() || !pML2 || !pML2->Vektor())
			{
				DEX_Error (RC_clipping, EC_NOMEMORY);
				DELETE_OBJ (pML1); DELETE_OBJ (pML2);
				return false;
			}

			if (!_KAF[i].Aufbereitung2 (&pFl->KA(ii), pML1, pML2, bLeer, bAbbr, pPSt))
				continue;

			DELETE_OBJ (pML2);

			// Routine KantenPosit() ermittelt, ob die beiden Konturen einen
			// Überlappungsbereich haben
			posLage = KantenPosit (&pFl->KA(ii), pML1, bOverlap, iTouchOut);

			if (!bOverlap) continue;	// kein Überlappungsbereich
														  
		// Bilden der gemeinsamen Konturabschnitte														  
		long lVekL1 = pML1->ADP();
		GeoKante* pGK = 0;	// gemeinsamer Konturabschnitt

			// zuerst wird der Spezialfall getestet, ob es nur INNERHALB-Punkte gibt
			for (long j = 0; j < lVekL1; j++)
				if (pML1->GetMk1(j) != INNERHALB) break;

			if (j == lVekL1)	// alle Punkte tragen Markierung INNERHALB
			{
			KoOrd x = DtoL (pML1->x(0));
			KoOrd y = DtoL (pML1->y(0));

				pGK = new GeoKante (0, 0, &x, &y, 1);
				if (! pGK)
				{
					DEX_Error (RC_clipping, EC_NOMEMORY);
					DELETE_OBJ (pML1);
					return false;
				}
				pGK->AddKonturTeil (pML1, 1, lVekL1-1, -1);	// Rest von pML1 an pGK anhängen
				pGK->AddClipObjekt (CL);					// Konturabschnitt in CL speichern
				DELETE_OBJ (pGK);
				continue;
			}

		// sonst den Normalfall abhandeln
		long lAInd1 = -1;		// 1. Anfangsindex eines Konturabschnittes
		bool bAufbau = false;	// Konturabschnitt ist aktuell (nicht) im Aufbau (true/false)

			j = 0;	// Laufindex von pML1

			do
			{
			Mar1 mark11 = pML1->GetMk1(j);
		
				if (! bAufbau)	// kein Konturabschnitt aktuell im Aufbau
				{
					if (mark11 == RAND_INN || mark11 == RAND_UMG)
					{
					long k;		// der auf j folgende Index

						if (j < lVekL1-2) k = j + 1;
						else k = 0;
						mark11 = pML1->GetMk1(k);

						// bei nachfolgender Bedingung wurde das Ende eines Konturabschnitts erwischt
						if (mark11 != INNERHALB && mark11 != RAND_INN && mark11 != RAND_UMG)
							do
							{
//								if (j == 0) j = lVekL1-2;
//								else j--;
								(j > 0) ? (j--) : (j = lVekL1-2);	// 31.12.98
								mark11 = pML1->GetMk1(j);
							}
							while (mark11 != RAND_INN && mark11 != RAND_UMG);

					// Anfang eines Konturabschnitts
					KoOrd x = DtoL (pML1->x(j));
					KoOrd y = DtoL (pML1->y(j));

						DELETE_OBJ (pGK);
						pGK = new GeoKante (0, 0, &x, &y, 1);
						if (! pGK)
						{
							DEX_Error (RC_clipping, EC_NOMEMORY);
							DELETE_OBJ (pML1);
							return false;
						}
						(j < lVekL1-2) ? (lNInd = j + 1) : (lNInd = 0);
						if (lAInd1 == -1) lAInd1 = j;	// 1. Anfangsindex merken
						bAufbau = true;
					}
				}
				else			// Konturabschnitt aktuell im Aufbau
				{
					if (mark11 == RAND_INN || mark11 == RAND_UMG)
					{
						pGK->AddKonturTeil (pML1, lNInd, j, -1);	// Teil von pML1 an pGK anhängen
						pGK->AddClipObjekt (CL);					// Konturabschnitt in CL speichern
						DELETE_OBJ (pGK);
						bAufbau = false;
					}
				}
				(j < lVekL1-2) ? (j++) : (j = 0);
			}
			while (j != lAInd1);

			DELETE_OBJ (pGK);

		} // for/for

	DELETE_OBJ (pML1);
	return true;

} // KonturGemeinsamkeiten




///////////////////////////////////////////////////////////////////////////////////////////////
// Methoden für markiertes ElementarGeoObjekt MARKPUNKT 
// Zerlegen von pML durch eine Kante in Teilkanten, die in CL eingetragen werden;
// return-Wert ist "true", wenn Teilkanten in CL eingetragen werden, sonst "false"
bool TeilKanten1 (MarkLine* pML, long lONr, ulong ulIdent, ClipListe& CL)
{
	_ASSERTE (pML != 0);
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);
	_ASSERTE (ulIdent != 0);
	_ASSERTE ((ulong)-1 != ulIdent);

	if (! pML) return false;

GeoKante* pGK = 0;	// Teilkante
long lVekL = pML->ADP();
long l = 0;			// Index für pML-Punkte
long lAInd = l;		// Anfangsindex für den Teil der Kante, der aus pML übernommen wird
Mar1 mark1 = pML->GetMk1(l);
bool bClosed = pML->IsClosed();

	// bei geschlossenen Kanten kann der Beginn einer Teilkante (SCHNITT-, BERUEHR- oder
	// RANDP-Punkt) vor dem Anfangs/Endpunkt der Kante liegen, deshalb so einen Beginn suchen
	if (bClosed && SCHNITT != mark1/* && BERUEHR != mark1*/ && RANDP != mark1)
	{
		l = lVekL - 1;
		do
		{
			l--;
			mark1 = pML->GetMk1(l);
		}
		while (SCHNITT != mark1/* && BERUEHR != mark1*/ && RANDP != mark1 && l > 0);

		lAInd = l;
	}

long lAnfInd1 = lAInd;		// der Anfangspunkt der 1. Teilkante

	// Aufbau der Teilkanten
	for (;;)
	{
		if (bClosed)
		{
			(l < lVekL-2) ? (l++) : (l = 0);
			if (l == lAnfInd1) return true;
		}
		else
		{
			if (l == lVekL-1) break;
			l++;
		}

		mark1 = pML->GetMk1(l);
	
		// wenn aktueller Punkt pML[l] Schnitt-, Berührungs- oder Randpunkt eines
		// Überlappungsbereiches ist, dann aktuelle Teilkante schließen und neue Teilkante mit
		// dem aktuellen pML[l] beginnen
		if ((SCHNITT == mark1/* || BERUEHR == mark1*/ || RAND == mark1) &&
			lAInd != l)	// es wird mindestens noch ein zweiter Punkt angehangen			
		{
			if (labs (l - lAInd) == lVekL - 1)
				return true;	// die ungeteilte Kante nicht noch einmal erzeugen

		KoOrd x = DtoL (pML->x(lAInd));		// Anfang einer Teilkante
		KoOrd y = DtoL (pML->y(lAInd));

			pGK = new GeoKante (lONr, ulIdent, &x, &y, 1);
			if (! pGK)
			{
				DEX_Error (RC_clipping, EC_NOMEMORY);
				return false;
			}

			pGK->AddKonturTeil (pML, lAInd+1, l, -1);	// Teil der pML-Kante an pGK anhängen
			pGK->AddClipObjekt (CL);
			DELETE_OBJ (pGK);

			lAInd = l;
		}
	}

	// bei offenen Kanten kann es noch einen Rest geben
	_ASSERTE (!bClosed);

	if (lAInd != l)
	{
	KoOrd x = DtoL (pML->x(lAInd));
	KoOrd y = DtoL (pML->y(lAInd));

		pGK = new GeoKante (lONr, ulIdent, &x, &y, 1);
		if (! pGK)
		{
			DEX_Error (RC_clipping, EC_NOMEMORY);
			return false;
		}

		pGK->AddKonturTeil (pML, lAInd+1, l, -1);
		pGK->AddClipObjekt (CL);
		DELETE_OBJ (pGK);
	}

	return true;

} // TeilKanten1


// --------------------------------------------------------------------------------------------
// Zerlegen von pML1-Kante durch pML2-Flächenkontur in Teilkanten, die in CL eingetragen
// werden; dabei wird der in ulLageAusw vorgegebene Lagewunsch mit berücksichtigt;
// return-Wert ist "true", wenn Teilkanten in CL eingetragen werden, sonst "false"
bool TeilKanten2 (MarkLine* pML1, MarkLine* pML2, long lONr, ulong ulIdent, ulong ulLageAusw,
				  ClipListe& CL)
{
	_ASSERTE (pML1 != 0);
	_ASSERTE (pML2 != 0);
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

	if (!pML1 || !pML2) return false;

bool bRet = false;	// return-Wert
GeoKante* pGK = 0;	// Teilkante
long lVekL = pML1->ADP();
long i = 0;			// Index für pML1-Punkte
long lAInd = i;		// Anfangsindex für den Teil der Kante, der aus pML1 übernommen wird
Posit posLage;		// Lage eines pML1-Punktes bez. der pML2-Fläche

	// Lage des 1. Teils der Kante bez. pML2 bestimmen
	if (pML1->GetMk1(0) != INNERHALB)	// Anfangspunkt einer Kante kann nicht die Markierung
	{                                   //  RAND_INN bzw. RAND_UMG haben
		posLage = pML2->Position (pML1, 0);

		if (posLage == OFFEN) // Außenkontur der schneidenden Fläche pML2 ist nicht geschlossen
		{
			DEX_Error (RC_TeilKanten2, WC_FLAECHEOFFEN);
			return false;
		}
	}
	else
		posLage = KONTUR;

	// Aufbau der Teilkanten
	do
	{
		i++;

	// wenn aktueller Punkt pML1[i] Schnittpunkt oder Endpunkt eines Überlappungsbereiches ist,
	// dann akt. Teilkante schließen und neue Teilkante mit dem akt. pML1[i] beginnen
	Mar1 mark11 = pML1->GetMk1(i);
	
		if (mark11 == RAND_INN || mark11 == RAND_UMG || mark11 == SCHNITT)
		{
			// die aktuell zu bildende Teilkante entspricht mit ihrer posLage dem vorgegebenen
			// Lagewunsch
			if ((posLage == INNERH && (ulLageAusw & LINN)) ||	// innerhalb
	    		(posLage == KONTUR && (ulLageAusw & LKONT)) ||	// auf der Kontur
	    		(posLage == AUSSERH && (ulLageAusw & LAUSS)))	// außerhalb
			{
			// Anfang einer Teilkante
			KoOrd x = DtoL (pML1->x(lAInd));
			KoOrd y = DtoL (pML1->y(lAInd));

				pGK = new GeoKante (lONr, ulIdent, &x, &y, 1);
				if (! pGK)
				{
					DEX_Error (RC_clipping, EC_NOMEMORY);
					return bRet;
				}
				if (lAInd+1 <= i)	// es wird mindestens noch ein zweiter Punkt angehangen
				{
					pGK->AddKonturTeil (pML1, lAInd+1, i, -1);	// Teil der pML1-Kante an pGK anhängen
					pGK->AddClipObjekt (CL);
				}
				DELETE_OBJ (pGK);
				bRet = true;
			}

			// Lage der nächsten Teilkante bestimmen
			if (mark11 == SCHNITT)		// Schnittpunkt
			{
				if (posLage == INNERH)
					posLage = AUSSERH;
				else if (posLage == AUSSERH) posLage = INNERH;
			}
			else if (posLage != KONTUR) posLage = KONTUR;   // Randpunkt erreicht
			else if (mark11 == RAND_INN) posLage = INNERH;
			else posLage = AUSSERH;

			lAInd = i;	// Anfangsindex für den nächsten Teil der Kante, der aus pML1 übernommen wird
		}
	}
	while (i < lVekL-1);

	if ((posLage == INNERH && (ulLageAusw & LINN)) ||	// innerhalb
	    (posLage == KONTUR && (ulLageAusw & LKONT)) ||	// auf der Kontur
	    (posLage == AUSSERH && (ulLageAusw & LAUSS)))	// außerhalb
	{
	// akt. Punkt ist Anfangspunkt einer neuen Teilkante mit neuem "posLage"
	KoOrd x = DtoL (pML1->x(lAInd));
	KoOrd y = DtoL (pML1->y(lAInd));

		pGK = new GeoKante (lONr, ulIdent, &x, &y, 1);
		if (! pGK)
		{
			DEX_Error (RC_clipping, EC_NOMEMORY);
			return bRet;
		}
		if (lAInd+1 <= i)	// es wird mindestens noch ein zweiter Punkt angehangen
		{
			pGK->AddKonturTeil (pML1, lAInd+1, i, -1);	// Teil der pML1-Kante an pGK anhängen
			pGK->AddClipObjekt (CL);
		}
		DELETE_OBJ (pGK);
		bRet = true;
	}                        

	return bRet;

} // TeilKanten2


// --------------------------------------------------------------------------------------------
// Zerlegen von pML1-Flächenkontur durch pML2-Kante in Teilflächen, die in CL eingetragen
// werden.
// Die MarkPunkte des Vektors pML1[] werden nicht kontinuierlich mit aufsteigendem Index
// abgearbeitet. Dies hätte zur Folge, daß u.U. mehrerer Teilflächen gleichzeitig im Aufbau
// sein könnten. Wird ein Schnittpunkt, der Endpunkt eines Überlappungsbereiches (deren zu-
// bzw. abführende pML2-Strecke innerhalb der pML1-Fläche liegt) oder ein Punkt mit Randpunkt-
// bzw. Innenberührung ohne Seitenwechsel (deren beteiligte pML2-Strecken aus dem Inneren der
// pML1-Fläche kommen) erreicht, wird die bis dahin kontinuierliche Folge der pML1[i]-Punkte
// verlassen und der Aufbau der aktuellen Teilfläche mit Punkten der schneidenden pML2-Kante 
// fortgesetzt.
// Damit wird erreicht, daß sich immer nur EINE Teilfläche im Aufbau befindet. Wurde ein
// Strecke (pML1[i], pML1[i+1]) "verbraucht", wird die Markierung _Mark2 des Anfangspunktes
// pML1[i] von UNVERBR auf VERBR gesetzt. Nach Abschluß der aktuell bearbeiteten Teilfläche
// wird im pML1[]-Vektor an der ersten "unverbrauchten" Strecke fortgesetzt.
// return-Wert ist "true", wenn Teilflächen in CL eingetragen werden, sonst "false".
// Die Objektnummer	lONr des Originalobjektes wird an die Teilobjekte weitergereicht, damit
// beim Kopieren der Merkmale das Quell-Objekt klar ist.
bool TeilFlaechen1 (MarkLine* pML1, MarkLine* pML2, long lONr, ulong ulIdent, ClipListe& CL)
{
	_ASSERTE (pML1 != 0);
	_ASSERTE (pML2 != 0);
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

	if (!pML1 || !pML2) return false;

bool bRet = false;	// return-Wert
long lVekL1 = pML1->ADP();
long i = 0;			// Index für pML1-Punkte
GeoFlaeche* pGF = 0;	// Teilfläche
long lUnverbr = 0;	// Index der ersten noch unverbrauchten Strecke
bool bRest;			// nach Verlassen der 2. do-Schleife ist die soeben aufgebaute Teilfläche
					// noch durch einen restlichen Teil zu ergänzen (true)
long lAInd;			// Anfangsindex für den Teil der Flächenkontur, der aus pML1 übernommen
					// wird

	for (;;)
	{
	// Anfang der Außenkontur einer Teilfläche
	KoOrd x = DtoL (pML1->x(i));
	KoOrd y = DtoL (pML1->y(i));

		pGF = new GeoFlaeche (lONr, ulIdent, &x, &y, 1);
		if (! pGF)
		{
			DEX_Error (RC_clipping, EC_NOMEMORY);
			return bRet;
		}

	EPunkt PA (x, y);		// Anfangspunkt von pGF

		(i < lVekL1-2) ? (lAInd = i + 1) : (lAInd = 0);

		
		// Aufbau einer Teilfläche
		do
		{
			bRest = true;
			
			pML1->ModMark2 (i, VERBR);	// Strecke (pML1[i], pML1[i+1]) als "verbraucht" markieren
			(i < lVekL1-2) ? (i++) : (i = 0);

		// aktueller Punkt pML1[i] ist Schnittpunkt (SCHNITT), Endpunkt eines
		// Überlappungsbereiches (RAND_INN) oder Punkt mit Randpunkt- bzw. Innenberührung ohne
		// Seitenwechsel (BERUE_INN, BERUE_ER, BERUE_LE)
 		Mar1 mark11 = pML1->GetMk1(i);

			if (mark11 == SCHNITT || mark11 == RAND_INN || mark11 == BERUE_INN ||
				mark11 == BERUE_ER || mark11 == BERUE_LE)
			{
				// Teil der Kontur von pML1 an pGF anhängen
				pGF->KA(0).AddKonturTeil (pML1, lAInd, i, -1);
				if (PA == pML1->SP(i))
					break;
				// pGF mit Punkten von pML2 ergänzen
				pGF->KA(0).SpezAddPunkt1 (pML1, pML2, i, mark11);
				
				(i < lVekL1-2) ? (lAInd = i + 1) : (lAInd = 0);
				bRest = false;
			}
		}       // Abbruch, wenn akt. Teilfläche geschlossen
		while (PA != pML1->SP(i));
		
		// restlichen Teil an pGF anhängen, wenn in der do-Schleife noch Stützpunkte gesammelt
		// wurden, die jedoch mit AddKonturTeil noch nicht an die Teilfläche angefügt wurden;
		// bRest == false, wenn unmittelbar nach dem Aufruf von Routine SpezAddPunkt() die
		// do-Schleife mit geschlossener Teilfläche beendet wurde
		if (bRest)
			pGF->KA(0).AddKonturTeil (pML1, lAInd, i, -1);
			
	// Da es möglich ist, daß durch die Eps-Arithmetik der Anfangs- und Endpunkt nur eps-gleich
	// sind, werden beide Punkte vorsichtshalber völlig identisch gemacht.
	long lSPAnz = pGF->KA(0).ASP();
		
		pGF->KA(0).SP(lSPAnz-1) = PA;

		pGF->AddClipObjekt (CL);
		bRet = true;
		DELETE_OBJ (pGF);
			
		// nächste noch "unverbrauchte" Strecke suchen; wird keine mehr gefunden, ist i == lVekL1-1
		for (i = lUnverbr; i < lVekL1-1; i++ )
			if (UNVERBR == pML1->GetMk2(i))
				break;
		lUnverbr = i;

		if (i == lVekL1-1)	// keine "unverbrauchte" Strecke mehr gefunden
			return bRet;
	}
} // TeilFlaechen1


// --------------------------------------------------------------------------------------------
// Zerlegen der Kontur pML1 durch die Flächenkontur pML2 in Teilflächen, die in CL eingetragen
// werden.
// Die MarkPunkte des Vektors pML1[] werden nicht kontinuierlich mit aufsteigendem Index
// abgearbeitet. Dies hätte zur Folge, daß u.U. mehrerer Teilflächen gleichzeitig im Aufbau
// sein könnten. Wird ein Schnitt- bzw. der Endpunkt eines Überlappungsbereiches mit
// Seitenwechsel erreicht, wird die bis dahin kontinuierliche Folge der pML1[i]-Punkte
// verlassen und der Aufbau der aktuellen Teilfläche mit Punkten aus pML2 fortgesetzt.
// Damit wird erreicht, daß sich immer nur EINE Teilfläche im Aufbau befindet.
// Wurde ein Strecke (pML1[i], pML1[i+1]) "verbraucht", wird die Markierung _Mark2 des
// Anfangspunktes pML1[i] von UNVERBR auf VERBR gesetzt. Nach Abschluß der aktuell bearbeiteten
// Teilfläche wird im pML1[]-Vektor an der ersten "unverbrauchten" Strecke fortgesetzt.
// ulLageAusw gibt an, ob die Ergebnis-Teilfläche gewünscht werden, die innerhalb und/oder
// außerhalb der schneidenden Kontur pML2 liegen;
// return-Wert ist "true", wenn Teilflächen in CL eingetragen werden, sonst "false".
// Die Objektnummer lONr des Originalobjektes wird an die Teilobjekte weitergereicht, damit
// beim Kopieren der Merkmale das Quell-Objekt klar ist.
bool TeilFlaechen2 (MarkLine* pML1, MarkLine* pML2, long lONr, ulong ulIdent, ulong ulLageAusw,
					ClipListe& CL)
{
	_ASSERTE (pML1 != 0);

	if (! pML1) return false;

long lVekL1 = pML1->ADP();

	for (long i = 0; i < lVekL1; i++)
	{
	Mar1 marM = pML1->GetMk1(i);

		if (marM == SCHNITT || marM == RAND_INN || marM == RAND_UMG ||
			marM == BERUE_INN || marM == BERUE_UMG)
			break;
	}
	if (i == lVekL1)	// keine Teilfläche bildbar
		return false;

	_ASSERTE (pML2 != 0);	// lONr == 0 kann sein, z.B. bei Aufruf aus SchnittKonturMitKontur()

	if (! pML2) return false;

bool bRet = false;	// return-Wert
Posit posLage;		// Lage der zu erzeugenden Teilfläche bez. pML2

	// Suche nach einem pML1-Punkt, so daß der anschließende Teil des pML1-Vektors nicht in
	// einem Überlappungsbereich liegt, um dort mit dem Konturaufbau einer Teilfläche zu
	// beginnen
	for (i = 0; i < lVekL1-1; i++)
	{
	Mar1 ma10 = pML1->GetMk1(i);
	Mar1 ma11 = pML1->GetMk1(i+1);

		if (ma10 == INNERHALB || ma11 == INNERHALB ||	// außerhalb eines Überlappungsbereiches ?
		   ((ma10 == RAND_INN || ma10 == RAND_UMG) &&
			 KONTUR == pML2->Position (pML1, i)))
			pML1->ModMark2 (i, VERBR);	// Strecke (pML1[i], pML1[i+1] als "verbraucht" markieren
		else
			break;  // geeigneter Punkt gefunden
	}
	
	if (i == lVekL1-1)	// beide Flächen liegen haargenau übereinander
		return false;	// kein Eintrag in ClipListe, da auf Kontur pML2 keine andere Fläche
						// liegen kann

    
// Abarbeitung aller pML1-Punkte ..............................................................
GeoFlaeche* pGF = 0;	// Teilfläche
Mar1 mark11;		// Markierung
long lUnverbr = 0;	// Index der ersten noch unverbrauchten Strecke
bool bRest;			// nach Verlassen der 2. do-Schleife ist die soeben aufgebaute Teilfläche
					// noch durch einen restlichen Teil zu ergänzen (true)
long lAInd;			// Anfangsindex für den Teil der Flächenkontur, der aus pML1 übernommen
					// wird
MoveDir MD;			// wenn Punkte aus pML2 übernommen werden, ist der Index aufsteigend zu
					// durchlaufen (true)

int iKInd1 = pML1->GetKInd();		_ASSERTE (iKInd1 >= 0);
int iKInd2 = pML2->GetKInd();		_ASSERTE (iKInd2 >= 0);
bool bWechsel;	// bei BERUE_INN bzw. BERUE_UMG ist bei pML2 fortzusetzen (true); wird durch
				// EckeMitBeruehrung() gesetzt
bool bMax;		// SEHR wichtiger Parameter für EckeMitBeruehrung()

	if (0 == iKInd1 && 0 == iKInd2)
		bMax = true;
	else if (0 == iKInd1 && iKInd2 > 0)
		bMax = true;
	else if (iKInd1 > 0 && 0 == iKInd2)
		bMax = false;
	else	// if (iKInd1 > 0 && iKInd2 > 0)
		bMax = true;	// seit 10.06.99

bool bGlKont;	// die beiden Konturen haben den gleichen Umlaufsinn (bGlKont = true)

	if ((0 == iKInd1 && 0 == iKInd2) || (iKInd1 > 0 && iKInd2 > 0))
		bGlKont = true;
	else bGlKont = false;

	for (;;)
	{
		// Test, ob die evtl. aufzubauende Teilfläche pGF innerhalb (posLage == INNERH) oder
		// außerhalb (posLage == AUSSERH) der schneidenden Kontur pML2 liegt
		posLage = pML2->Position (pML1, i, false);

/* 03.03.99
		// posLage == KONTUR kann eigentlich nicht auftreten, da i so gewählt wurde, daß die
		// nachfolgende Strecke nicht in einem Überlappungsbereich liegt; kann aber durch die
		// sattsam bekannten Rundungsprobleme bei der Digitalgeometrie auftreten
		if (INNERH != posLage && AUSSERH != posLage)
		{
			for (i = lUnverbr; i < lVekL1-1; i++ )	// 19.10.98
			{
				if (UNVERBR == pML1->GetMk2(i))	// Strecke "unverbraucht"
				{
					posLage = pML2->Position (pML1, i);
					if (KONTUR == posLage)
						// Strecke (pML1[i], pML1[i+1] als "verbraucht" markieren
						pML1->ModMark2 (i, VERBR);
					else
						break;  // geeigneten Punkt gefunden
				}
			}

			if (i == lVekL1-1)
				return bRet;
			lUnverbr = i;
		}
*/
		// Wenn Lage der Teilfläche, die nachfolgend aufgebaut werden könnte, mit dem
		// vorgegebenen Auswahlkriterium übereinstimmt, dann wird die Teilfläche wirklich
		// aufgebaut (true), anderenfalls werden die Strecken nur als "verbraucht" markiert;
		// (Das Auswahlkriterium "Auf dem Rand" wird nicht berücksichtigt, da auf dem Rand
		// einer Fläche keine andere Fläche liegen kann.)
		if ((posLage == INNERH && (ulLageAusw & LINN)) ||	// innerhalb
			(posLage == AUSSERH && (ulLageAusw & LAUSS)))	// außerhalb
		{ // Teilfläche wird tatsächlich aufgebaut
		ulong ulLageAuswAkt;	// Lageauswahl, mit der aktuell gearbeitet wird

			if (posLage == INNERH && (ulLageAusw & LINN))
				ulLageAuswAkt = LINN;
			else
				ulLageAuswAkt = LAUSS;

		// Anfang der Außenkontur einer Teilfläche
		KoOrd x = DtoL (pML1->x(i));
		KoOrd y = DtoL (pML1->y(i));

			pGF = new GeoFlaeche (lONr, ulIdent, &x, &y, 1);
			if (! pGF)
			{
				DEX_Error (RC_clipping, EC_NOMEMORY);
				return bRet;
			}

		EPunkt PA (x, y);	// Anfangspunkt von pGF 

			if ((posLage == INNERH && bGlKont) ||
				(posLage == AUSSERH && !bGlKont))
				MD = MOVEDIR_UP;	// pML2-Punkte mit aufsteigendem bzw.
			else
				MD = MOVEDIR_DOWN;	//  absteigendem Index bearbeiten

			(i < lVekL1-2) ? (lAInd = i + 1) : (lAInd = 0);

			// Aufbau einer Teilfläche
			do {
				bRest = true;
				// Strecke (pML1[i], pML1[i+1]) als "verbraucht" markieren
				pML1->ModMark2 (i, VERBR);
				(i < lVekL1-2) ? (i++) : (i = 0);

				// aktueller Punkt pML1[i] ist Endpunkt eines Überlappungsbereiches
				// (_Mark1 == RAND_UMG bzw. RAND_INN), Schnittpunkt (SCHNITT) oder, wenn
				// Teilfläche außerhalb von pML2 aufgebaut werden soll, Punkt mit Randpunkt-
				// bzw. Innenberührung ohne Seitenwechsel (BERUE_UMG)
				mark11 = pML1->GetMk1(i);

				if ((mark11 == BERUE_INN && (ulLageAuswAkt & LINN)) ||
					(mark11 == BERUE_UMG && (ulLageAuswAkt & LAUSS)))
					pML1->EckeMitBeruehrung (pML2, i, MOVEDIR_UP, MD, bMax, bWechsel);

				if (mark11 == SCHNITT || mark11 == RAND_INN || mark11 == RAND_UMG ||
					(mark11 == BERUE_INN && (ulLageAuswAkt & LINN) && bWechsel) ||
					(mark11 == BERUE_UMG && (ulLageAuswAkt & LAUSS) && bWechsel))
				{
					bRest = false;
					// Teil der Kontur von pML1 an pGF anhängen
					pGF->KA(0).AddKonturTeil (pML1, lAInd, i, -1);

					// das langjährige unendeckte Fehlen der nachfolgenden if-Anweisung ist
					// eine der unerklärlichsten Phänomene meiner Programmierpraxis (13.10.98)
					if (PA == pML1->SP(i)) break;

				// pGF mit Punkten von pML2 ergänzen
					pGF->KA(0).SpezAddPunkt2 (pML1, pML2, i, MD, ulLageAuswAkt);

// Wann der Fall auftreten kann, dass man nach SpezAddPunkt2() auf einen "verbrauchten"
// pML1-Punkt stoßen kann, ist mir derzeit noch völlig unklar. Deshalb die Assertion (#WM030325).
_ASSERTE(UNVERBR == pML1->GetMk2(i));

				// #HK021111: den nächsten unverbrauchten Punkt suchen, an dem geht es 
				// dann weiter
					while (VERBR == pML1->GetMk2(i)) {
						if (PA == pML1->SP(i)) 
							break;		// äußere Schleife wird dann auch abgebrochen
						(i < lVekL1-2) ? (i++) : (i = 0);
					}

					(i < lVekL1-2) ? (lAInd = i + 1) : (lAInd = 0);
				}
			}       // Abbruch, wenn akt. Teilfläche geschlossen
			while (PA != pML1->SP(i));
		
			// restlichen Teil an pGF anhängen, wenn in der do-Schleife noch Stützpunkte
			// gesammelt wurden, die jedoch mit AddKonturTeil noch nicht an die Teilfläche
			// angefügt wurden; bRest == false, wenn unmittelbar nach dem Aufruf von Routine
			// SpezAddPunkt() die do-Schleife mit geschlossener Teilfläche beendet wurde
			if (bRest)
				pGF->KA(0).AddKonturTeil (pML1, lAInd, i, -1);
			
		// Da es möglich ist, daß durch die Eps-Arithmetik der Anfangs- und Endpunkt nur
		// eps-gleich sind, werden beide Punkte vorsichtshalber völlig identisch gemacht.
		long lSPAnz = pGF->KA(0).ASP();
		
			pGF->KA(0).SP(lSPAnz-1) = PA;

		// ggf. Digitalgeometrie-bedingte Entartungen übergehen (#HK021104)
			if (lSPAnz > 3)
				pGF->AddClipObjekt (CL);

			bRet = true;
			DELETE_OBJ (pGF);
		}

		// Teilfläche wird nicht aufgebaut, die Strecken werden nur als "verbraucht" markiert
		else
		{
		long lSZ = lVekL1 - 1;	// Zähler für spätesten Abbruch der do-Schleife, wenn while-Bedingung
								// überhaupt nicht erfüllt wird (für den Fall aller Fälle !!)
			do
			{
				pML1->ModMark2 (i, VERBR);	// Strecke (pML1[i], pML1[i+1]) als "verbraucht" markieren
				(i < lVekL1-2) ? (i++) : (i = 0);

				// aktueller Punkt pML1[i] ist Endpunkt eines Überlappungsbereiches
				// (_Mark1 == RAND_UMG bzw. RAND_INN), Schnittpunkt (SCHNITT) oder, wenn
				// Teilfläche außerhalb von pML2 aufgebaut werden soll, Punkt mit Randpunkt-
				// bzw. Innenberührung ohne Seitenwechsel (BERUE_UMG)
				mark11 = pML1->GetMk1(i);

				lSZ--;
				if (lSZ == 0) break;
			}
			while (mark11 != RAND_INN && mark11 != RAND_UMG  && mark11 != SCHNITT &&
				  (mark11 != BERUE_UMG || !(ulLageAusw & LAUSS)));
		}

	
		// nächste noch "unverbrauchte" Strecke, die nicht in einem Überlappungsbereich liegt,
		// suchen; wird keine mehr gefunden, ist i == lVekL1-1
		for (i = lUnverbr; i < lVekL1-1; i++ )
			if (UNVERBR == pML1->GetMk2(i))	// Strecke "unverbraucht"
			{
			Mar1 ma10 = pML1->GetMk1(i);
			Mar1 ma11 = pML1->GetMk1(i+1);

				if (ma10 == INNERHALB || ma11 == INNERHALB ||	// außerhalb eines Überlappungsbereiches ?
				   ((ma10 == RAND_INN || ma10 == RAND_UMG) &&
					 KONTUR == pML2->Position (pML1, i)))
					pML1->ModMark2 (i, VERBR);	// Strecke (pML1[i], pML1[i+1] als "verbraucht" markieren
				else
					break;  // geeigneten Punkt gefunden
			}

		lUnverbr = i;

		if (i == lVekL1-1)	// keine "unverbrauchte" Strecke mehr gefunden
			return bRet;
	} // for

} // TeilFlaechen2
