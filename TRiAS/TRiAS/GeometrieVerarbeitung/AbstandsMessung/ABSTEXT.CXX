// Definition des Interface für die Erweiterung "Abstandsmessung"
// File: ABSTEXT.CXX


#include "abstandp.hxx"

#include <resstrg.h>			// IDS_UIFORMAT

#include "BasicFunctions.hxx"	// TurnDirection()
#include "geotrias.hxx"			// EFlaecheErzeugen()
#include "strecke.hxx"			// StreckenTeilung()
#include "datbank.hxx"			// WriteFeatureText()

#include "AbstandR.h"			// IDS_LONGCLASSNAME

#include "abstguid.h"			// CLSID_Abstand in abstand.hxx

#include "abstand.hxx"			// AbstandExtension

#include "SmartInterfaces.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;

extern int ErrHandler (int iWC, int iRoutine, ...);


///////////////////////////////////////////////////////////////////////////////////////////////
// Abstand des lONr-Objektes vom lBONr-Bezugsobjektes
BOOL _ABSTAND_EXPORT FAR PASCAL ObjektAbstand (long lONr, BOOL, void* pDat)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);
	_ASSERTE (pDat != NULL);

AbstandExtension* pAE = (AbstandExtension*) g_pTE;
double dZW;		// Zwischenwert
long lBONr = ((AbstDat*) pDat)->lBONr;
DistTyp dtTyp = ((AbstDat*) pDat)->dtTyp;
ExtrAbst exAbst = ((AbstDat*) pDat)->exAbst;

	if (lBONr == lONr)
		return true;	// keine Abstandsmessung mit "sich selbst"


	if (ABST_MAX == exAbst)	// größter Abstand gesucht
	{
		// durch Vortest wird ermittelt, ob der Abstand der beiden Objektcontainer
		// kleiner als das bisherige Maximum ist; in diesem Fall wird nichts weiter
		// berechnet; anderenfalls wird der Typ-gerechte Abstand ermittelt
		if (pAE->AbstandRechtecke (lBONr, lONr) < ((AbstDat*)pDat)->dAbst)	// Vortest
			return true;
		pAE->AbstandObjObj_ONr (lBONr, lONr, &dZW, dtTyp);		// exakter Abstand
		if (dZW > ((AbstDat*)pDat)->dAbst)
		{
			((AbstDat*)pDat)->dAbst = dZW;
			((AbstDat*)pDat)->lEONr = lONr;
		}
	}
	else		// kleinster Abstand gesucht
	{
		// durch Vortest wird ermittelt, ob der Abstand der beiden Objektcontainer
		// größer als das bisherige Minimum ist; in diesem Fall wird nichts weiter
		// berechnet; anderenfalls wird der Typ-gerechte Abstand ermittelt
		if (pAE->AbstandRechtecke (lBONr, lONr) > ((AbstDat*)pDat)->dAbst)	// Vortest
			return true;
		pAE->AbstandObjObj_ONr (lBONr, lONr, &dZW, dtTyp);		// exakter Abstand
		if (dZW >= 0 &&	// ist das Objekt kein Punkt-, Linien- oder Flächenobjekt bzw.
						// bei unzureichendem dynamischen Speicher wird -1 zurückgegeben
			dZW < ((AbstDat*)pDat)->dAbst)
		{
			((AbstDat*)pDat)->dAbst = dZW;
			((AbstDat*)pDat)->lEONr = lONr;
		}
		if (0. == dZW)			// 0 ist der kleinstmöglichste Abstand,
			return false;		//  kleiner kann's nicht werden
	}
	return true;
}



///////////////////////////////////////////////////////////////////////////////////////////////
// IExtendAbstand2-Methoden
// --------------------------------------------------------------------------------------------
// Abstand zwischen 2 Objekten
STDMETHODIMP_(HRESULT) AbstandExtension :: DistanceObjObj_ONr (LONG lONr1, LONG lONr2,
												double* pdAbst, DistTyp dtTyp, ExtrAbst exAbst)
{
	_ASSERTE (lONr1 != 0);
	_ASSERTE (lONr1 != -1);
	_ASSERTE (lONr2 != 0);
	_ASSERTE (lONr2 != -1);

ErrInstall EI (WC_MESSAGE_ABST);	// keine Anzeige der Fehlermeldung WC_MESSAGE_ABST

	if (! m_pCT)
	{
		m_pCT = new CoordTransX();	// Klasse für KoordinatenTransformation
		if (! m_pCT)
		{                                                                      
			DEX_Error (RC_abstext, EC_NOMEMORY);
			return E_OUTOFMEMORY;
		}
	}

// wenn eine Fehlerbehandlungsmethode registriert war, dann diese beibelassen
	if (ErrHandler != EI.OldMethod())
		EI.Revoke();

	return AbstandObjObj_ONr (lONr1, lONr2, pdAbst, dtTyp, exAbst);
}


// --------------------------------------------------------------------------------------------
// kleinster bzw. größter Abstand der Objekte einer ulIdent-Objektklasse zu einem
// lONr-Bezugsobjekt; in plONr wird die Objektnummer des Ergebnisobjektes zurückgegeben
STDMETHODIMP_(HRESULT) AbstandExtension :: DistanceObjOClass_ONr (LONG lONr, ULONG ulIdent,
								   double* pdAbst, DistTyp dtTyp, ExtrAbst exAbst, LONG* plONr)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);
	_ASSERTE (plONr != NULL);

ErrInstall EI (WC_MESSAGE_ABST);	// keine Anzeige der Fehlermeldung WC_MESSAGE_ABST

	if (! m_pCT)
	{
		m_pCT = new CoordTransX();	// Klasse für KoordinatenTransformation
		if (! m_pCT)
		{                                                                      
			DEX_Error (RC_abstext, EC_NOMEMORY);
			return E_OUTOFMEMORY;
		}
	}

// wenn eine Fehlerbehandlungsmethode registriert war, dann diese beibelassen
	if (ErrHandler != EI.OldMethod())
		EI.Revoke();

	return AbstandObjOKlasse (lONr, ulIdent, pdAbst, dtTyp, exAbst, plONr);
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_(HRESULT) AbstandExtension :: DistanceObjObj_Geom (IObjektGeometrie* pIOG1,
					   IObjektGeometrie* pIOG2, double* pdAbst, DistTyp dtTyp, ExtrAbst exAbst)
{
	_ASSERTE (pIOG1 != NULL);
	_ASSERTE (pIOG2 != NULL);

ErrInstall EI (WC_MESSAGE_ABST);	// keine Anzeige der Fehlermeldung WC_MESSAGE_ABST

	if (! m_pCT)
	{
		m_pCT = new CoordTransX();	// Klasse für KoordinatenTransformation
		if (! m_pCT)
		{                                                                      
			DEX_Error (RC_abstext, EC_NOMEMORY);
			return E_OUTOFMEMORY;
		}
	}

// wenn eine Fehlerbehandlungsmethode registriert war, dann diese beibelassen
	if (ErrHandler != EI.OldMethod())
		EI.Revoke();

	return AbstandObjObj_Geom (pIOG1, pIOG2, pdAbst, dtTyp, exAbst);
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_(HRESULT) AbstandExtension :: DistanceObjOClass_Geom (IObjektGeometrie* pIOG,
					ULONG ulIdent, double* pdAbst, DistTyp dtTyp, ExtrAbst exAbst, LONG* plONr)
{
	return E_NOTIMPL;
}


// --------------------------------------------------------------------------------------------
// Ausgehend von dem Startpunkt (lXA, lYA) wird auf dem pIOG-Linienobjekt in Richtung des
// Endpunktes (lXE, lYE) eine Kante der Länge dDistanz abgemessen; gilt ppIOGOut != NULL, wird
// in ppIOGOut diese Kante zurückgegeben; in (lXA, lYA) wird in jedem Fall der letzte Punkt
// zurückgegeben; für lXE == -1 oder lYE == -1 wird die Stützpunktfolge des pIOG-Objektes
// bez. des Index standardmäßig aufsteigend durchlaufen.
STDMETHODIMP_(HRESULT) AbstandExtension :: LinePart (IObjektGeometrie* pIOGIn, LONG lXA,
					   LONG lYA, LONG lXE, LONG lYE, double dDist, IObjektGeometrie** ppIOGOut)
{
	if (NULL == ppIOGOut) return E_POINTER;

	_ASSERTE (pIOGIn != NULL);

ErrInstall EI (WC_MESSAGE_ABST);	// keine Anzeige der Fehlermeldung WC_MESSAGE_ABST

	if (! m_pCT)
	{
		m_pCT = new CoordTransX();	// Klasse für KoordinatenTransformation
		if (! m_pCT)
		{                                                                      
			DEX_Error (RC_abstext, EC_NOMEMORY);
			return E_OUTOFMEMORY;
		}
	}

// wenn eine Fehlerbehandlungsmethode registriert war, dann diese beibelassen
	if (ErrHandler != EI.OldMethod())
		EI.Revoke();

	return TeilKante (pIOGIn, lXA, lYA, lXE, lYE, dDist, ppIOGOut);
}


// --------------------------------------------------------------------------------------------
// Entfernung des Punktes Punkt (lX,lY) von Stützpunkt 0 auf der pIOG-Kante
STDMETHODIMP_(HRESULT) AbstandExtension :: DistanceFromOrigin_Geom (IObjektGeometrie* pIOG,
														  LONG* plX, LONG* plY, double* pdAbst)
{
	_ASSERTE (pIOG != NULL);

ErrInstall EI (WC_MESSAGE_ABST);	// keine Anzeige der Fehlermeldung WC_MESSAGE_ABST

	if (! m_pCT)
	{
		m_pCT = new CoordTransX();	// Klasse für KoordinatenTransformation
		if (! m_pCT)
		{                                                                      
			DEX_Error (RC_abstext, EC_NOMEMORY);
			return E_OUTOFMEMORY;
		}
	}

// wenn eine Fehlerbehandlungsmethode registriert war, dann diese beibelassen
	if (ErrHandler != EI.OldMethod())
		EI.Revoke();

	return EntfernungVomAnfang_Geom (pIOG, plX, plY, pdAbst);
}


// --------------------------------------------------------------------------------------------
// Erzeugen eines nach links bzw. rechts (Seite == ABST_LEFT/ABST_RIGHT) verschobenen
// Teilabschnittes der pIOGIn-Ausgangslinie;
// (lXA,lYA): Koordinaten des Anfangspunktes
// dLaenge:   die Länge des Teilabschnittes auf der Ausgangslinie
// dAbst:     der Abstand (in Metern)
// ulIdent:   der Objektklassenschlüssel des Ergebnisobjektes, das in ppIOGOut zurückgegeben wird
STDMETHODIMP_(HRESULT) AbstandExtension :: ShiftedLinePart (IObjektGeometrie* pIOGIn, LONG lXA,
										  LONG lYA, double dLaenge, Side Seite, double* pdAbst,
										  ULONG ulIdent, IObjektGeometrie** ppIOGOut)
{
	_ASSERTE (pIOGIn != NULL);

ErrInstall EI (WC_MESSAGE_ABST);	// keine Anzeige der Fehlermeldung WC_MESSAGE_ABST

	if (! m_pCT)
	{
		m_pCT = new CoordTransX();	// Klasse für KoordinatenTransformation
		if (! m_pCT)
		{                                                                      
			DEX_Error (RC_abstext, EC_NOMEMORY);
			return E_OUTOFMEMORY;
		}
	}

// wenn eine Fehlerbehandlungsmethode registriert war, dann diese beibelassen
	if (ErrHandler != EI.OldMethod())
		EI.Revoke();

	return VerschobeneTeilKante (pIOGIn, lXA, lYA, dLaenge, Seite, pdAbst, ulIdent, ppIOGOut);
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Routinen für die IExtendAbstand2-Methoden
// --------------------------------------------------------------------------------------------
// Abstand zwischen 2 Objekten ermitteln
HRESULT AbstandExtension :: AbstandObjObj_ONr (long lONr1, long lONr2, double* pdAbst,
											   DistTyp dtTyp, ExtrAbst exAbst)
{
	if (ABST_MAX == exAbst || ABST_MINMAX == exAbst)
		return E_NOTIMPL;

	_ASSERTE (lONr1 != 0);
	_ASSERTE (lONr1 != -1);
	_ASSERTE (lONr2 != 0);
	_ASSERTE (lONr2 != -1);

	if (OT_TEXT == DEX_GetObjectType (lONr1) ||
		OT_TEXT == DEX_GetObjectType (lONr2) ||
		OT_LABEL == DEX_GetObjectType (lONr1) ||
		OT_LABEL == DEX_GetObjectType (lONr2))
		return E_UNEXPECTED;	// Abstand kann mit (indirektem) Textobjekt nicht gebildet werden

WObjektGeometrie wObj1;
WObjektGeometrie wObj2;
HRESULT hr = CreateInterfaceOG (wObj1.ppi(), lONr1);

	if (FAILED(hr))	return hr;
	hr = CreateInterfaceOG (wObj2.ppi(), lONr2);
	if (FAILED(hr))	return hr;

	return AbstandObjObj_Geom (wObj1, wObj2, pdAbst, dtTyp, exAbst); 

} // AbstandObjObj_ONr


// --------------------------------------------------------------------------------------------
// Abstand zwischen 2 Objekten ermitteln
HRESULT AbstandExtension :: AbstandObjObj_Geom (IObjektGeometrie* pIOG1,
					   IObjektGeometrie* pIOG2, double* pdAbst, DistTyp dtTyp, ExtrAbst exAbst)
{
	_ASSERTE (pIOG1 != NULL);
	_ASSERTE (pIOG2 != NULL);

// Parameter der beiden Objekte
long lONr1, lONr2;
short iOT1, iOT2;
long lCnt1, lCnt2;
KoOrd* plXK1; KoOrd* plYK1; KoOrd* plXK2; KoOrd* plYK2;

	pIOG1->GetONr (&lONr1);
	pIOG1->GetObjTyp (&iOT1);
	pIOG1->GetCnt (&lCnt1);
	pIOG1->GetX ((void**)&plXK1);
	pIOG1->GetY ((void**)&plYK1);
	pIOG2->GetONr (&lONr2);
	pIOG2->GetObjTyp (&iOT2);
	pIOG2->GetCnt (&lCnt2);
	pIOG2->GetX ((void**)&plXK2);
	pIOG2->GetY ((void**)&plYK2);

// EObjekte rekonstruieren
EPunkt* pP1 = NULL;
EPunkt* pP2 = NULL;
EKante* pK1 = NULL;
EKante* pK2 = NULL;
EFlaeche* pF1 = NULL;
EFlaeche* pF2 = NULL;

	switch (iOT1)
	{
		case OT_PUNKT:
			pP1 = new EPunkt (EPunkt (plXK1[0], plYK1[0]));
			break;

		case OT_KANTE:
			pK1 = new EKante (plXK1, plYK1, lCnt1);
			break;

		case OT_FLAECHE:
		{
		short iKCnt1;
		long* plCnt1;

			pIOG1->GetKCnt (&iKCnt1);
			pIOG1->GetLPCnt (&plCnt1);

			pF1 = EFlaecheErzeugen (iKCnt1, plXK1, plYK1, plCnt1);
			break;
		}

		default:	// z.B. Textobjekte
			break;
	}

	if ((OT_PUNKT == iOT1 && !pP1) ||
		(OT_KANTE == iOT1 && !pK1) || 
		(OT_FLAECHE == iOT1 && !pF1))
	{
		DEX_Error (RC_abstext, EC_NOMEMORY);
		return E_OUTOFMEMORY;
	}

	switch (iOT2)
	{
		case OT_PUNKT:
			pP2 = new EPunkt (EPunkt (plXK2[0], plYK2[0]));
			break;

		case OT_KANTE:
			pK2 = new EKante (plXK2, plYK2, lCnt2);
			break;

		case OT_FLAECHE:
		{
		short iKCnt2;
		long* plCnt2;

			pIOG2->GetKCnt (&iKCnt2);
			pIOG2->GetLPCnt (&plCnt2);

			pF2 = EFlaecheErzeugen (iKCnt2, plXK2, plYK2, plCnt2);
			break;
		}

		default:	// z. B. Textobjekte
			break;
	}

	if ((OT_PUNKT == iOT2 && !pP2) ||
		(OT_KANTE == iOT2 && !pK2) || 
		(OT_FLAECHE == iOT2 && !pF2))
	{
		DEX_Error (RC_abstext, EC_NOMEMORY);
		return E_OUTOFMEMORY;
	}

// Abstand ermitteln
HRESULT hrRet = S_OK;	// return-Wert

	if (iOT1 == OT_PUNKT && iOT2 == OT_PUNKT)					// Punkt - Punkt
		*pdAbst = AbstandPunktPunkt (pP1, pP2);

	else if (iOT1 == OT_PUNKT && iOT2 == OT_KANTE)				// Punkt - Linie
		*pdAbst = AbstandPunktLinie (lONr1, pP1, lONr2, pK2, dtTyp);

	else if (iOT1 == OT_KANTE && iOT2 == OT_PUNKT)
		*pdAbst = AbstandPunktLinie (lONr2, pP2, lONr1, pK1, dtTyp);

	else if (iOT1 == OT_PUNKT && iOT2 == OT_FLAECHE)			// Punkt - Fläche
	{
		if (pP1->EnthaltenIn(pF2) != AUSSERH)
			*pdAbst = 0.;
		else
		{
		int iKCnt2 = pF2->KantenAnz();
		double dMinAbst = DBL_MAX;

			for (int i = 0; i < iKCnt2; i++)
			{
			EKante* pKt2 = &pF2->KA(i);
			double dAbst = AbstandPunktLinie (lONr1, pP1, lONr2, pKt2, dtTyp);

				if (dAbst < dMinAbst)
					dMinAbst = dAbst;
			}
			*pdAbst = dMinAbst;
		}
	}

	else if (iOT1 == OT_FLAECHE && iOT2 == OT_PUNKT)
	{
		if (pP2->EnthaltenIn(pF1) != AUSSERH)
			*pdAbst = 0;
		else
		{
		int iKCnt1 = pF1->KantenAnz();
		double dMinAbst = DBL_MAX;

			for (int i = 0; i < iKCnt1; i++)
			{
			EKante* pKt1 = &pF1->KA(i);
			double dAbst = AbstandPunktLinie (lONr2, pP2, lONr1, pKt1, dtTyp);

				if (dAbst < dMinAbst)
					dMinAbst = dAbst;
			}
			*pdAbst = dMinAbst;
		}
	}

	else if (iOT1 == OT_KANTE && iOT2 == OT_KANTE)				// Linie - Linie
	{
		if (exAbst == ABST_MAXMIN)
			hrRet = E_NOTIMPL;
		else
			*pdAbst = AbstandLinieLinie (lONr1, pK1, lONr2, pK2, dtTyp);
	}

	else if (iOT1 == OT_KANTE && iOT2 == OT_FLAECHE)			// Linie - Fläche
	{
		if (exAbst == ABST_MIN)
		{
			if (pK1->EnthaltenIn(pF2) != AUSSERH)
				*pdAbst = 0;
			else			
			{
			int iKCnt2 = pF2->KantenAnz();
			double dMinAbst = DBL_MAX;

				for (int i = 0; i < iKCnt2; i++)
				{
				EKante* pKt2 = &pF2->KA(i);
				double dAbst = AbstandLinieLinie (lONr1, pK1, lONr2, pKt2, dtTyp);

					if (dAbst < dMinAbst)
						dMinAbst = dAbst;
				}
				*pdAbst = dMinAbst;
			}
		}

		else if (exAbst == ABST_MAXMIN)
		{
		EKante* pKt2 = &pF2->KA(0);		// nur Einbeziehung der pF2-Außenkontur !!!

			*pdAbst = MaxMinAbstandLinieLinie (pK1, pKt2, dtTyp);
		}
		else
			hrRet = E_UNEXPECTED;
	}

	else if (iOT1 == OT_FLAECHE && iOT2 == OT_KANTE)
	{
		if (exAbst == ABST_MIN)
		{
			if (pK2->EnthaltenIn(pF1) != AUSSERH)
				*pdAbst = 0;
			else
			{
			int iKCnt1 = pF1->KantenAnz();
			double dMinAbst = DBL_MAX;

				for (int i = 0; i < iKCnt1; i++)
				{
				EKante* pKt1 = &pF1->KA(i);
				double dAbst = AbstandLinieLinie (lONr2, pK2, lONr1, pKt1, dtTyp);

					if (dAbst < dMinAbst)
						dMinAbst = dAbst;
				}
				*pdAbst = dMinAbst;
			}
		}

		else if (exAbst == ABST_MAXMIN)
		{
		EKante* pKt1 = &pF1->KA(0);		// nur Einbeziehung der pF1-Außenkontur !!!

			*pdAbst = MaxMinAbstandLinieLinie (pKt1, pK2, dtTyp);
		}
		else
			hrRet = E_UNEXPECTED;
	}

	else if (iOT1 == OT_FLAECHE && iOT2 == OT_FLAECHE)			// Fläche - Fläche
	{
		if (exAbst == ABST_MIN)
		{
			if (pF1->EnthaltenIn(pF2) != AUSSERH)
				*pdAbst = 0;
			else
			{
			int iKCnt1 = pF1->KantenAnz();
			int iKCnt2 = pF2->KantenAnz();
			double dMinAbst = DBL_MAX;

				for (int i = 0; i < iKCnt1; i++)
				{
				EKante* pKt1 = &pF1->KA(i);

					for (int ii = 0; ii < iKCnt2; ii++)
					{
					EKante* pKt2 = &pF2->KA(ii);
					double dAbst = AbstandLinieLinie (lONr1, pKt1, lONr2, pKt2, dtTyp);

						if (dAbst < dMinAbst)
							dMinAbst = dAbst;
					}
				}
				*pdAbst = dMinAbst;
			}
		}

		else if (exAbst == ABST_MAXMIN)
		{
		EKante* pKt1 = &pF1->KA(0);		// nur Einbeziehung der pF1- und pF2-Außenkontur !!!
		EKante* pKt2 = &pF2->KA(0);

			*pdAbst = MaxMinAbstandLinieLinie (pKt1, pKt2, dtTyp);
		}
		else
			hrRet = E_UNEXPECTED;
	}

	else
		hrRet = E_UNEXPECTED;	// wenn Objekt weder Punkt, Linie noch Fläche

	DELETE_OBJ (pP1);
	DELETE_OBJ (pK1);
	DELETE_OBJ (pF1);
	DELETE_OBJ (pP2);
	DELETE_OBJ (pK2);
	DELETE_OBJ (pF2);					   

	if (FAILED(hrRet))
		*pdAbst = -1;

	return hrRet;

} // AbstandObjObj_Geom


// --------------------------------------------------------------------------------------------
// kleinster (exAbst == ABST_MIN) bzw. größter (exAbst == ABST_MAX) Abstand der Objekte einer
// ulIdent-Objektklasse zu einem lONr-Bezugsobjekt; in plONr wird die Objektnummer des
// Ergebnisobjektes zurückgegeben
// folgende Formen (Typ) der Abstandsbestimmung sind möglich
//	DISTTYP_AUTO	automatische Entscheidung über die Form der Abstandsbestimmung
//	DISTTYP_MIDDLE	Abstand zwischen den Containermittelpunken der beiden Objekte
//	DISTTYP_VERTEX	kürzeste Entfernung zwischen je einem Stützpunkt
//	DISTTYP_EXACT	kürzeste Entfernung bei Berücksichtigung der Punkte zwischen den
//                  Stützpunkten
HRESULT AbstandExtension :: AbstandObjOKlasse (long lONr, ulong ulIdent, double* pdAbst,
											   DistTyp dtTyp, ExtrAbst exAbst, long* plONr)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);
	_ASSERTE (ulIdent != 0);
	_ASSERTE ((ulong)-1 != ulIdent);

	if (0 == lONr || -1 == lONr || 0 == ulIdent || (ulong)-1 == ulIdent)
		return E_INVALIDARG;

	_ASSERTE (plONr != NULL);

struct AbstDat Dat;

	Dat.lBONr = lONr;		// Objektnummer des Bezugsobjektes
	Dat.dtTyp = dtTyp;		// Form der Abstandsbestimmung
	Dat.exAbst = exAbst;	// der kleinste / größte Abstand ist zu bestimmen
	if (exAbst == ABST_MAX)	// größter Abstand gesucht
		Dat.dAbst = -DBL_MAX;	// gesuchter Abstand
	else		// kleinster Abstand gesucht
		Dat.dAbst = DBL_MAX;

// Objektnummern aller Objekte des Identifikators ulIdent bereitstellen
ENUMLONGKEY ELK;

	if (0 != ulIdent && (ulong)-1 != ulIdent)
		ELK.eKey = ulIdent;
	ELK.eFcn = (ENUMLONGKEYPROC) ObjektAbstand;
	ELK.ePtr = (void*) &Dat;
	DEX_EnumIdentObjects (ELK);

	*plONr = Dat.lEONr;	// Nummer des Objektes mit dem kleinsten / größten Abstand
	*pdAbst = Dat.dAbst;
	return S_OK;

} // AbstandObjOKlasse


// --------------------------------------------------------------------------------------------
// Ausgehend von dem Startpunkt (lXA, lYA) wird auf dem pIOG-Linienobjekt in Richtung des
// Endpunktes (lXE, lYE) eine Kante der Länge dDistanz abgemessen; gilt ppIOGOut != NULL, wird
// in ppIOGOut diese Kante zurückgegeben; in (lXA, lYA) wird in jedem Fall der letzte Punkt
// zurückgegeben; für lXE == -1 oder lYE == -1 wird die Stützpunktfolge des pIOG-Objektes
// bez. des Index standardmäßig aufsteigend durchlaufen.
// return-Wert sind
//   keine Fehler:
//     S_OK:          Punkt wurde exakt berechnet und in plXK[0] bzw. plYK[0] zurückgegeben
//     S_FALSE:       die Länge vom Startpunkt (lXA, lYA) bis zum Ende des lONr-Linienobjektes
//                    ist < dDistanz; deshalb können in plXK[0] bzw. plYK[0] nur die
//                    Koordinaten des Endpunktes zurückgegeben werden
//   Fehler:
//     E_UNEXPECTED:  unerlaubte Parameter bzw. kein Punkt bei Streckenteilung bildbar
//     E_POINTER:     plXK == NULL oder plYK == NULL
//     E_OUTOFMEMORY: dynamischer Speicher nicht ausreichend
// Liegt der Endpunkt (lXE, lYE) nicht exakt auf dem pIOG-Linienobjekt, wird er auf das
// Linienobjekt gezogen. Die korrigierten Koordinaten werden zurückgegeben, um diese Prozedur
// für den nächsten Aufruf von TeilKante() zu verkürzen.
HRESULT AbstandExtension :: TeilKante (IObjektGeometrie* pIOGIn, KoOrd& lXA, KoOrd& lYA,
						 KoOrd& lXE, KoOrd& lYE, double& dDistanz, IObjektGeometrie** ppIOGOut)
{
	_ASSERTE (pIOGIn != NULL);

	if (! pIOGIn)
	{
		DEX_Error (RC_TeilKante, EC_ILLPARS);
		return E_POINTER;
	}

// nachfolgende Message gilt nur vorübergehend !
short iOT;

	pIOGIn->GetObjTyp (&iOT);

	if (iOT != OT_KANTE)
	{
	ResString Text (ResID (IDS_NOKANTE, pRF), 80);
	ErrCode rcDummy;

		DEX_SetError (rcDummy, 0, WC_MESSAGE_ABST, (void*)Text.Addr());
		return E_UNEXPECTED;
	}

	if (!pIOGIn || dDistanz <= 0 ||
		lXA < 0 || lYA < 0 || lXE < -1 || lYE < -1 ||
		(lXA == lXE && lYA == lYE))		// Startpunkt == Endpunkt
	{
		DEX_Error (RC_TeilKante, EC_ILLPARS);
		return E_UNEXPECTED;
	}

// wenn Startpunkt (lXA,lYA) nicht auf der Kante liegt, dann den nächstgelegen Punkt auf der
// Kante suchen (dabei wird sich i.d.R. ein Punkt zwischen 2 Stützpunkten ergeben)
long lIndA = -1;	// Index für kleinsten Abstand von Punkt (lXA,lYA) bzw.
long lIndE = -1;	//  von Punkt (lXE,lYE) zu den Strecken der pIOGIn-Kante
BOOL bPA, bPE;		// Anfangspunkt (lXA,lYA) bzw. Endpunkt (lXE,lYE) ist mit einem Stützpunkt
					// identisch (true)

	pIOGIn->GetPointOnObject (&lXA, &lYA, &lIndA, &bPA);

	if (ppIOGOut != NULL && *ppIOGOut == NULL)
	{
	HRESULT hr = CreateInterfaceOG (ppIOGOut, lXA, lYA, OT_KANTE);

		if (FAILED(hr)) return hr;
	}

KoOrd* plXK; KoOrd* plYK;

	pIOGIn->GetX ((void**)&plXK);
	pIOGIn->GetY ((void**)&plYK);

	if (lXE >= 0 && lYE >= 0)
		pIOGIn->GetPointOnObject (&lXE, &lYE, &lIndE, &bPE);

	// kein Endpunkt vorgegeben; deshalb wird als Richtung "aufsteigende Stützpunktindizes"
	// standardmäßig festgelegt
	else
	{
		pIOGIn->GetCnt (&lIndE);
		lIndE--;		// höchster Stützpunktindex
		bPE = true;		// Punkt(lXE,lYE) ist mit dem letzten Stützpunkt identisch

		lXE = plXK [lIndE];
		lYE = plYK [lIndE];
	}

	// Kante bzgl. der Stützpunktindizes umorientieren, wenn Anfangsindex > Endindex
	if (lIndA > lIndE)
	{
	long lSAnz;

		pIOGIn->GetCnt (&lSAnz);
		pIOGIn->OrientDreh (-1);

		if (bPA)	// Startpunkt ist mit einem Stützpunkt identisch
			lIndA = lSAnz - lIndA - 1;
		else		// Startpunkt liegt zwischen 2 Stützpunkten
			lIndA = lSAnz - lIndA - 2;
		if (bPE)	// Endpunkt ist mit einem Stützpunkt identisch
			lIndE = lSAnz - lIndE - 1;
		else
			lIndE = lSAnz - lIndE - 2;
	}

	// wenn Endpunkt (lXE,lYE) nicht mit einem Stützpunkt identisch ist, dann wird (lXE,lYE)
	// als "temporärer" Stützpunkt in pIOGIn eingefügt
	if (!bPE)
	{
		pIOGIn->AddPunkt (lXE, lYE, lIndE+1, -1);
		lIndE++;
		pIOGIn->GetX ((void**)&plXK);
		pIOGIn->GetY ((void**)&plYK);
	}

EPunkt P1, P2;	// P1 und P2 sind pIOGIn-Stützpunkte, zwischen denen der Abstand ermittelt wird


// ................................................................................................
// Beginn der eigentlichen Messung des Abstandes dDistanz
HRESULT hrRet = S_OK;	// return-Wert dieser Routine

long i = lIndA + 1;	// Index des 1. zu betrachtenden pIOGIn-Stützpunktes

	P2.X() = plXK [i];	// Koordinaten des 1. zu betrachtenden
	P2.Y() = plYK [i];	//  Stützpunktes

EPunkt TPkt ;			// Zwischenpunkt, der gebildet werden muß, wenn eine pIOGIn-Teilstrecke
						// länger als "dDistanz" ist
EPunkt AP (lXA,lYA);	// Startpunkt
double dUFak;			// Umrechnungsfaktor von Meter-Angaben in DB-Verhältnisse
double dAktLaenge = 0;	// (iterativ aufgebaute) aktuelle Gesamtlänge
double dStrLaenge = AbstandPunktPunkt (&AP, &P2);	// Teillänge zwischen 2 Punkten

	if (dStrLaenge < dDistanz)		// vorgegebene Länge "dDistanz" im 1. Anlauf noch nicht erreicht
	{
		dAktLaenge = dStrLaenge;
		for (; i < lIndE; i++)		// for-Schleife zur Abfrage weiterer Stützpunkte
		{
			P1.X() = plXK [i];
			P1.Y() = plYK [i];
			P2.X() = plXK [i+1];
			P2.Y() = plYK [i+1];
			if ((dStrLaenge = AbstandPunktPunkt (&P1, &P2)) == 0)	// 2 identische Punkte
				continue;	// for-Schleife weiter abarbeiten

			if (ppIOGOut)
				(*ppIOGOut)->AddPunkt (P1.X(), P1.Y(), -1, -1);

			// vorgegebene Länge "dDistanz" jetzt exakt erreicht
			if (dAktLaenge + dStrLaenge == dDistanz)
			{
				if (ppIOGOut)
					(*ppIOGOut)->AddPunkt (P2.X(), P2.Y(), -1, -1);
				lXA = P2.X();
				lYA = P2.Y();
				break;	// for-Schleife verlassen
			}

			// vorgegebene Länge "dDistanz" würde jetzt überschritten werden
			if (dAktLaenge + dStrLaenge > dDistanz)
			{
				_ASSERTE (dStrLaenge != 0);

				// dStrLaenge == 0 wird durch die Überprüfung von dDistanz am Beginn dieser Routine
				// ausgeschlossen
				dUFak = AbstandPktPktE (P1, P2) / dStrLaenge;
				if (StreckenTeilung (P1, P2, (dDistanz-dAktLaenge)*dUFak, TPkt))
				{
					if (ppIOGOut)
						(*ppIOGOut)->AddPunkt (TPkt.X(), TPkt.Y(), -1, -1);
					lXA = TPkt.X();
					lYA = TPkt.Y();
					break;	// for-Schleife verlassen
				}

				// kein Teilungspunkt bildbar; dürfte eigentlich nicht passieren
				_ASSERTE (false);
				DEX_Error (RC_TeilKante, EC_NOKILOMETRIERUNG);
				hrRet = E_UNEXPECTED;
				break;	// for-Schleife verlassen
			}

			// vorgegebene Länge "dDistanz" immer noch nicht erreicht
			dAktLaenge += dStrLaenge;
		} // for

		// i == lIndE bedeutet, daß alle pIOGIn-Stützpunkte abgearbeitet sind, aber nicht die
		// Länge "dDistanz" erreicht wurde
		if (i == lIndE)
		{
			if (ppIOGOut)
				(*ppIOGOut)->AddPunkt (lXE, lYE, -1, -1);

//			dDistanz = AbstandPunktPunkt (&AP, &P2);	// Restlänge (16.09.99)
			dDistanz = dAktLaenge;	// Restlänge
			lXA = lXE;		// lXE bzw. lYE wurden korrigiert, wenn der Endpunkt
			lYA = lYE;		//  auf die Kante gezogen wurde
			hrRet = S_FALSE;
		}
	}

	// dStrLaenge >= dDistanz schon im 1. Anlauf
	else
	{
		// vorgegebene Länge "dDistanz" schon im 1. Anlauf exakt erreicht
		if (dStrLaenge == dDistanz)
		{
			if (ppIOGOut)
				(*ppIOGOut)->AddPunkt (P2.X(), P2.Y(), -1, -1);
			lXA = P2.X();
			lYA = P2.Y();
		}

		// vorgegebene Länge "dDistanz" würde schon im 1. Anlauf überschritten
		else	// dStrLaenge > dDistanz
		{
			dUFak = AbstandPktPktE (AP, P2) / dStrLaenge;
			if (StreckenTeilung (AP, P2, dDistanz*dUFak, TPkt))
			{
				if (ppIOGOut)
					(*ppIOGOut)->AddPunkt (TPkt.X(), TPkt.Y(), -1, -1);
				lXA = TPkt.X();
				lYA = TPkt.Y();
			}

			// kein Teilungspunkt bildbar; dürfte eigentlich nicht passieren
			else
			{
				_ASSERTE (false);
				DEX_Error (RC_TeilKante, EC_NOKILOMETRIERUNG);
				hrRet = E_UNEXPECTED;
			}
		}
	}

	return hrRet;

} // TeilKante


// ------------------------------------------------------------------------------------------------
// Entfernung des Punktes Punkt (*plX,*plY) von Stützpunkt 0 auf der pIOG-Kante
HRESULT AbstandExtension :: EntfernungVomAnfang_Geom (IObjektGeometrie* pIOG, KoOrd* plX,
													  KoOrd* plY, double* pdAbst)
{
	_ASSERTE (pIOG != NULL);

	if (! pIOG) return E_POINTER;

short iOT;

	pIOG->GetObjTyp (&iOT);

	if (iOT != OT_KANTE || *plX < 0 || *plY < 0)
		return E_UNEXPECTED;

// wenn Punkt (*plX,*plY) nicht auf der Kante liegt, dann den nächstgelegen Punkt auf der Kante
// suchen (dabei wird sich i.d.R. ein Punkt zwischen 2 Stützpunkten ergeben)
long lInd = -1;	// Index für kleinsten Abstand von Punkt (*plX,*plY) zu den Strecken der pIOG-Kante
BOOL bVertex;

	pIOG->GetPointOnObject (plX, plY, &lInd, &bVertex);

KoOrd* plXK; KoOrd* plYK;

	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);

EPunkt P1;						// pIOG-Stützpunkte, zwischen denen der
EPunkt P2 (plXK[0], plYK[0]);	//  Abstand ermittelt wird

	*pdAbst = 0;	// Startwert für die iterativ errechnete Länge

	for (long j = 0; j < lInd; j++)
	{
		P1.X() = P2.X();
		P1.Y() = P2.Y();
		P2.X() = plXK[j+1];
		P2.Y() = plYK[j+1];
		*pdAbst += AbstandPunktPunkt (&P1, &P2);	// Teillänge zwischen 2 Punkten
	}

	if (! bVertex)	// (*plX,*plY) ist kein pIOG-Stützpunkt
	{
		P1.X() = P2.X();
		P1.Y() = P2.Y();
		P2.X() = *plX;
		P2.Y() = *plY;
		*pdAbst += AbstandPunktPunkt (&P1, &P2);
	}

	return S_OK;

} // EntfernungVomAnfang_Geom


// --------------------------------------------------------------------------------------------
// Erzeugen eines nach links bzw. rechts (Seite == ABST_LEFT/ABST_RIGHT) verschobenen
// Teilabschnittes der pIOGIn-Ausgangslinie; (lXA,lYA) und (lXE,lYE) sind die Koordinaten des
// Anfangs- und Endpunktes, pdAbst der Abstand (in Metern) und ulIdent der
// Objektklassenschlüssel des Ergebnisobjektes, das in ppIOGOut zurückgegeben wird
HRESULT AbstandExtension :: VerschobeneTeilKante (IObjektGeometrie* pIOGIn, KoOrd lXA,
										 KoOrd lYA, double dLaenge, Side Seite, double* pdAbst,
										 ulong ulIdent, IObjektGeometrie** ppIOGOut)
{
// Teilkante wTK ab Punkt (lXA,lYA) der Länge "dLaenge" AUF dem pIOGIn-Linienobjekt erzeugen
WObjektGeometrie wTK; 
KoOrd lXE = -1;		// die von TeilKante() zurückgegebenen
KoOrd lYE = -1;		// Koordinaten des letzten wTK-Punktes

HRESULT hr = TeilKante (pIOGIn, lXA, lYA, lXE, lYE, dLaenge, wTK.ppi());

	if (FAILED(hr)) return hr;

	hr = SmallestDistance (wTK, Seite, pdAbst);
	if (FAILED(hr)) return hr;

	if (! m_wBuffer.IsValid())	// (wenn noch nicht, dann) IExtendBuffer-Interface für
	{							//  WorkingBuffer_Geom() zuschalten
	WUnknown wBuffer;

		BufferInterface (wBuffer.ppi());
		m_wBuffer = wBuffer;
	}

// Puffer der Breite pdAbst um die Teilkante wTK bilden
WObjektGeometrie wPuffFl;	// Pufferfläche

	if (m_wBuffer.IsValid())
	{
	// Vorgabe für die Kantenlänge des n-Ecks, das an einer konvexen Ecke anstatt eines
	// Kreisbogens gebildet wird (in Meter)
	double dKonvex = *pdAbst/4.;

		if (dKonvex < 1.) dKonvex = 1.;

		m_wBuffer->WorkingBuffer_Geom (wTK, *pdAbst, PBAU_VOLL, BUFF_BOTH, BUFF_ARC, dKonvex,
									   wPuffFl.ppi());
	}
	else return E_POINTER;

// den 1. (lXAv,lYAv) und letzten Punkt (lXEvlYEv) der VERSCHOBENEN Teilkante ermitteln
KoOrd lXAv, lYAv, lXEv, lYEv;
DoublePair dUF = UmrechnungsFaktor (lXA, lYA, lXE, lYE, m_pCT);

	hr = GetStartStopCoords (wTK, Seite, *pdAbst, dUF, lXAv, lYAv, lXEv, lYEv);

	if (FAILED(hr)) return hr;

// die Indizes lAInd bzw. lEInd der wPuffFl-Punkte ermitteln, welche den beiden Punkten
// (lXAv,lYAv) bzw. (lXEv,lYEv) am nächsten liegen
long lAInd, lEInd;

	GetStartStopIndexes (wPuffFl, lXAv, lYAv, lXEv, lYEv, lAInd, lEInd);

// die verschobene Teilkante aufbauen, mit ulIdent versehen und nach TRiAS speichern
	return CreateShiftedLinePart (wPuffFl, lAInd, lEInd, Seite, ulIdent, ppIOGOut);

} // VerschobeneTeilKante


// --------------------------------------------------------------------------------------------
// Abstand, d. h die kürzeste Entfernung (in Meter) ermitteln, den der Linienverlauf des
// pTK-Objektes auf der "Seite" mit sich selbst hat, da der pdAbst-Abstand kleiner als die
// Hälfte eben dieses Abstandes sein muß
HRESULT AbstandExtension :: SmallestDistance (IObjektGeometrie* pTK, Side Seite,
											  double* pdAbst)
{
	_ASSERTE (pTK != NULL);

double dMinAbst = DBL_MAX;
double dMinjAbst;				// errechneter Abstand für den Stützpunkt SP(j)
DoublePair OB1 = DoublePair();	// Real-Koordinaten
DoublePair OB2 = DoublePair();
EPunkt LPkt;						// Lotpunkt
int iBR;						// Bewegungsrichtung für Ausnutzung der "Seite"-Information 
long lCnt;						// Länge der pTK-Teilkante
KoOrd* plXK; KoOrd* plYK;

	pTK->GetCnt (&lCnt);
	pTK->GetX ((void**)&plXK);
	pTK->GetY ((void**)&plYK);
	
EPunkt Pj, Pj1, Pjj, Pjj1/*, Pcnt*/;

	for (long j = 0; j < lCnt-2; j++)
	{
		// DB-Koordinaten in ASC-Format transformieren
		m_pCT->UnScale (plXK[j], plYK[j], &OB1.X(), &OB1.Y());

		for (long jj = j+2; jj < lCnt-1; jj++)
		{
			Pj.X() = plXK[j];
			Pj.Y() = plYK[j];
			Pj1.X() = plXK[j+1];
			Pj1.Y() = plYK[j+1];
			Pjj.X() = plXK[jj];
			Pjj.Y() = plYK[jj];
			iBR = TurnDirection (Pj.X(), Pj.Y(), Pj1.X(), Pj1.Y(), Pjj.X(), Pjj.Y());

			if ((ABST_RIGHT == Seite && -1 == iBR) ||
				(ABST_LEFT == Seite && +1 == iBR))
			{
				// Lotpunkt LPkt von SP(j) auf Strecke (SP(j+2), SP(j+3))
				Pjj1.X() = plXK[jj+1];
				Pjj1.Y() = plYK[jj+1];
				if (LotPunkt (Pj, Pjj, Pjj1, LPkt))
				{
					m_pCT->UnScale (LPkt, &OB2.X(), &OB2.Y());
					dMinjAbst = m_pCT->CoordTransDistance (&OB1, &OB2);
					if (dMinjAbst < dMinAbst) dMinAbst = dMinjAbst;
				}
				else
				{
					m_pCT->UnScale (plXK[jj], plYK[jj], &OB2.X(), &OB2.Y());
					dMinjAbst = m_pCT->CoordTransDistance (&OB1, &OB2);
					if (dMinjAbst < dMinAbst) dMinAbst = dMinjAbst;
				}
			}
		}
		
		// Einbeziehung des letzten pTK-Stützpunktes
//		Pcnt.X() = plXK[lCnt-1];
//		Pcnt.Y() = plYK[lCnt-1];
//		iBR = TurnDirection (Pj.X(), Pj.Y(), Pj1.X(), Pj1.Y(), Pcnt.X(), Pcnt.Y());
		iBR = TurnDirection (Pj.X(), Pj.Y(), Pj1.X(), Pj1.Y(), plXK[lCnt-1], plYK[lCnt-1]);

		if ((ABST_RIGHT == Seite && -1 == iBR) ||
			(ABST_LEFT == Seite && +1 == iBR))
		{
			m_pCT->UnScale (plXK[lCnt-1], plYK[lCnt-1], &OB2.X(), &OB2.Y());
			dMinjAbst = m_pCT->CoordTransDistance (&OB1, &OB2);
			if (dMinjAbst < dMinAbst) dMinAbst = dMinjAbst;
		}
	}


	// Test, ob der pdAbst-Abstand kleiner als die Hälfte des eben errechneten
	// dMinAbst-Abstandes ist; wenn nicht, dann Korrektur und Warnung
	if (dMinAbst <= 2.*(*pdAbst))
	{
	ResString Text (ResID (IDS_DISTTOGREAT, pRF), 150);
	ErrCode rcDummy;

		DEX_SetError (rcDummy, 0, WC_MESSAGE_ABST, (void*)Text.Addr())
		if (EC_OKAY != rcDummy)
		{
		// die nachfolgende Korrektur mit "1." soll bewirken, daß 
		// *pdAbst < dMinAbst/2. gilt (jetzt mit .1 korrigiert - #HK040608)
		// wenn dMinAbst/2 < 1, dann wird mit .01 korrigiert usw. #HK040608
			if (dMinAbst > 2) 
				*pdAbst = dMinAbst / 2. - .1;
			else if (dMinAbst > 1)
				*pdAbst = dMinAbst / 2. - .01;
			else if (dMinAbst > .1)
				*pdAbst = dMinAbst / 2. - .001;
			else if (dMinAbst > .01)
				*pdAbst = dMinAbst / 2. - .0001;
			else if (dMinAbst > .001)
				*pdAbst = dMinAbst / 2. - .00001;

			if (*pdAbst < 0)
				*pdAbst = -*pdAbst;
		}
	}

	return S_OK;

} // SmallestDistance


// --------------------------------------------------------------------------------------------
// den 1. (lXAv,lYAv) und letzten Punkt (lXEvlYEv) der VERSCHOBENEN Teilkante in Abhängigkeit
// von "Seite" mit den Algorithmen der BufferElemente ermitteln
HRESULT AbstandExtension :: GetStartStopCoords (IObjektGeometrie* pGK, Side Seite,
			  double dAbst, DoublePair dUF, KoOrd& lXAv, KoOrd& lYAv, KoOrd& lXEv, KoOrd& lYEv)
{
	_ASSERTE (pGK != NULL);

double dFak = dUF.Y() / dUF.X();	// Relation bei geodätischen Koordinaten
long lCnt;
KoOrd* plXK; KoOrd* plYK;

	pGK->GetCnt (&lCnt);
	pGK->GetX ((void**)&plXK);
	pGK->GetY ((void**)&plYK);

// Ermittlung des 1. Punktes PA
double x1 = plXK[0] * dFak;
double y1 = plYK[0];
double x2, y2, dLength;
long j = 1;

	do
	{
		x2 = plXK[j] * dFak;
		y2 = plYK[j];
		dLength = sqrt ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
		j++;
	}
	while (0. == dLength && j < lCnt);

	if (0. == dLength && j == lCnt)
		return E_UNEXPECTED;

double k0 = dAbst / dLength;	// Hilfswerte
double k1 = k0 * (x2 - x1);
double k2 = k0 * (y2 - y1);

	if (ABST_RIGHT == Seite)
	{
		lXAv = DtoL (plXK[0] + k2*dUF.X());
		lYAv = DtoL (y1 - k1*dUF.Y());
	}
	else	// ABST_LEFT
	{
		lXAv = DtoL (plXK[0] - k2*dUF.X());
		lYAv = DtoL (y1 + k1*dUF.Y());
	}


// Ermittlung des letzten Punktes PE
	x2 = plXK[lCnt-1] * dFak;
	y2 = plYK[lCnt-1];
	j = lCnt - 2;

	do
	{
		x1 = plXK[j] * dFak;
		y1 = plYK[j];
		dLength = sqrt ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
		j--;
	}
	while (0. == dLength && j >= 0);

	if (0. == dLength && j < 0)
		return E_UNEXPECTED;

	k0 = dAbst / dLength;
	k1 = k0 * (x2 - x1);
	k2 = k0 * (y2 - y1);

	if (ABST_RIGHT == Seite)
	{
		lXEv = DtoL (plXK[lCnt-1] + k2*dUF.X());
		lYEv = DtoL (y2 - k1*dUF.Y());
	}
	else	// ABST_LEFT
	{
		lXEv = DtoL (plXK[lCnt-1] - k2*dUF.X());
		lYEv = DtoL (y2 + k1*dUF.Y());
	}

	return S_OK;

} // GetStartStopCoords


// --------------------------------------------------------------------------------------------
// die Indizes lAInd bzw. lEInd der pGF-Punkte ermitteln, welche den beiden Punkten (lXAv,lYAv)
// bzw. (lXEv,lYEv) am nächsten liegen (eigentlich müßte die pGF-Pufferfläche die Punkte
// (lXAv,lYAv) und (lXEv,lYEv) ganz genau als Stützpunkte besitzen)
void AbstandExtension :: GetStartStopIndexes (IObjektGeometrie* pGF, KoOrd lXAv, KoOrd lYAv,
											  KoOrd lXEv, KoOrd lYEv, long& lAInd, long& lEInd)
{
	_ASSERTE (pGF != NULL);

KoOrd lAbstA = MAXKOORD;
KoOrd lAbstE = MAXKOORD;
short iOT;
KoOrd* plXK; KoOrd* plYK;
long* plCnt;

	pGF->GetObjTyp (&iOT);

	_ASSERTE (iOT == OT_FLAECHE);

	pGF->GetX ((void**)&plXK);
	pGF->GetY ((void**)&plYK);
	pGF->GetLPCnt (&plCnt);

	for (long j = 0; j < plCnt[0]-1; j++)
	{
	KoOrd lAA = AbstandPktPktM (plXK[j], plYK[j], lXAv, lYAv);
	KoOrd lAE = AbstandPktPktM (plXK[j], plYK[j], lXEv, lYEv);

		if (lAbstA > 0 && lAA < lAbstA)
		{
			lAbstA = lAA;
			lAInd = j;
		}

		if (lAbstE > 0 && lAE < lAbstE)
		{
			lAbstE = lAE;
			lEInd = j;
		}

		if (0 == lAbstA && 0 == lAbstE)
			return;		// näher ran geht's nicht
	}
} // GetStartStopIndexes


// --------------------------------------------------------------------------------------------
// die verschobene Teilkante aus dem Teil der pGF-Pufferfläche aufbauen, der vom Index lAInd
// bis zum Index lEInd geht; das neue Objekt mit ulIdent versehen und nach TRiAS speichern
HRESULT AbstandExtension :: CreateShiftedLinePart (IObjektGeometrie* pGF, long lAInd,
							long lEInd, Side Seite, ulong ulIdent, IObjektGeometrie** ppIOGOut)
{
	_ASSERTE (pGF != NULL);

short iOT;
KoOrd* plXK; KoOrd* plYK;
long* plCnt;

	pGF->GetObjTyp (&iOT);

	_ASSERTE (iOT == OT_FLAECHE);

	pGF->GetX ((void**)&plXK);
	pGF->GetY ((void**)&plYK);
	pGF->GetLPCnt (&plCnt);

	if (ppIOGOut && NULL == *ppIOGOut)
	{
	HRESULT hr = CreateInterfaceOG (ppIOGOut, plXK[lAInd], plYK[lAInd], OT_KANTE);

		if (FAILED(hr)) return hr;
	}
	else
		return E_UNEXPECTED;

long j = lAInd;

	do
	{
		if (ABST_RIGHT == Seite)
			(j < plCnt[0]-2) ? (j++) : (j = 0);
		else	// Seite == ABST_LEFT
			(j > 0) ? (j--) : (j = plCnt[0]-2);
		(*ppIOGOut)->AddPunkt (plXK[j], plYK[j], -1, -1);
	}
	while (j != lEInd);

	// OGNewObject:     permanentes Objekt in Datenbank aufnehmen
	// OGForceGeometry: auch außerhalb des aktuellen Projekt-Containers speichern
	// OGForceGeoError: Objekt wird bei Geometriefehler von GEOREIN abgewiesen
	(*ppIOGOut)->SetFlags (OGNewObject | OGForceGeometry | OGForceGeoError);
	(*ppIOGOut)->SetIdent (ulIdent);
	
#if _TRiAS_VER < 0x0300
HRESULT hr = (*ppIOGOut)->GeometrieAnTRiAS (true, NULL);
#else
INT_PTR hPr = reinterpret_cast<INT_PTR>(DEX_GetObjectsProject (ulIdent));
HRESULT hr = (*ppIOGOut)->GeometrieAnTRiASEx (hPr, true, NULL);
#endif // _TRiAS_VER < 0x0300

	// verschobene Teilkante wurde erfolgreich nach TRiAS gespeichert, deshalb noch UniqueIdent
	// verpassen
	if (SUCCEEDED(hr))
	{
	long lNeuONr;	// Objektnummer des eben neu eingespeicherten ppIOGOut-Objektes

		(*ppIOGOut)->GetONr (&lNeuONr);

		if (0 != lNeuONr && -1 != lNeuONr)
		{
		string sUIText;
		ResString resText (ResID (IDS_UIFORMAT, pRF), 20);

			Format (sUIText, (char*)resText.Addr(), lNeuONr);
#if _TRiAS_VER < 0x0300
			WriteFeatureText (lNeuONr, DEX_GetUniqueIdentMCode(), TT_Objekt, sUIText);
#else
			WriteFeatureText (lNeuONr, DEX_GetUniqueIdentMCodeEx (DEX_GetObjectProject(lNeuONr)), TT_Objekt, sUIText);
#endif // _TRiAS_VER < 0x0300
		}

		_ASSERTE (lNeuONr != 0);
		_ASSERTE (lNeuONr != -1);
	}

	return hr;

} // CreateShiftedLinePart


// --------------------------------------------------------------------------------------------
// Bezug zur Erweiterung "Pufferung" herstellen
HRESULT AbstandExtension :: BufferInterface (IUnknown** ppIBuffer)
{
HRESULT hr = S_OK;
WExtendBuffer wBuffer;		// Interface für Ankopplung von Buffer.ext

	if (m_pXtnSite)
	{
		hr = m_pXtnSite->GetXtension (CLSID_BufferExtension, IID_IExtendBuffer,
									  (LPVOID*)wBuffer.ppi());

		// "detach": Weiterreichen des Pointers ohne Release() und erneutes AddRef()
		*ppIBuffer = wBuffer.detach();
	}
	else hr = E_UNEXPECTED;

	if (FAILED (hr) ||	// Fehler, z.B. Buffer.ext nicht verfügbar
		! m_pXtnSite)
	{
	ResString resText1 (ResID (IDS_NOBUFFER, pRF), 250);
	ResString resText2 (ResID (IDS_LONGCLASSNAME, pRF), 50);
		
		MessageBox (__hWndM, resText1.Addr(), resText2.Addr(), MB_ICONEXCLAMATION | MB_OK);
		return hr;
	}

	return hr;

} // BufferInterface   
