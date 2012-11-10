// Definitionen: Bibliothek für Erweiterung "Geometrie-Editierung"
// File: GeoEditLib.cpp
// W. Mörtl


#include "GeoEditP.h"

#include "SmartInterfaces.h"

#include "objgguid.h"	// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif




///////////////////////////////////////////////////////////////////////////////////////////////
// Reaktion auf die Scroll-Tasten
void ScrollTest (HWND hWnd, WPARAM wParam)
{
    switch (wParam)
    {
    	case VK_LEFT:	// Pfeil links
    		break;

    	case VK_RIGHT:	// Pfeil rechts
    		break;

    	case VK_UP:		// Pfeil hoch
    		break;

    	case VK_DOWN:	// Pfeil runter
    		break;

    	case VK_PRIOR:	// Bild hoch
    		break;

    	case VK_NEXT:	// Bild runter
    		break;

    	case VK_HOME:	// Pos 1
    		break;

    	case VK_END:	// Ende
    		break;

    	case VK_SCROLL:	// Rollen hohler Pfeil runter
    		break;
    }
} // ScrollTest



///////////////////////////////////////////////////////////////////////////////////////////////
// Test, ob CommonBorder erlaubt ist; return-Werte sind
// S_OK:      CommonBorder ist erlaubt
// S_FALSE:   CommonBorder ist noch nicht erlaubt
// E_PENDING: Entscheidung kann nicht getroffen werden, weil mehrere Objekte die angegrabten
//            Punkte besitzen, wodurch möglicherweise (jedoch nicht immer) mehrere Pfade
//            denkbar sind
HRESULT IsCommonBorderAllowable (int& iGrabCnt, IEnumObjektGeometrie* pActGrabObjs,
    							 IEnumObjektGeometrie* pGrabObjs, long& lComONr)
{
    _ASSERTE (iGrabCnt >= 0);
    _ASSERTE (pActGrabObjs != NULL);

WUnknown Unk;
WObjektGeometrie wObj;	// das Objekt, vom bisher die Objektnummer lONr verwendet wurde
						// (inhaltlichr Bedeutung momentan unklar !!!!!)
short iOT;				// Objekttyp des wObj-Objektes

    // 1. GrabPunkt
    if (0 == iGrabCnt)
    {
    	pGrabObjs->Clear();
    	for (pActGrabObjs->Reset(); S_OK == pActGrabObjs->Next (1, Unk.ppi(), NULL); )
		{
			wObj = Unk;
    		pGrabObjs->AddItem (wObj);
		}
    	iGrabCnt++;
    	return S_FALSE;		// noch nicht
    }


// Anzahl der Objekte, die sowohl in pActGrabObjs als auch in pGrabObjs enthalten sind
ulong ulAndCnt;

    // 2. GrabPunkt
    if (1 == iGrabCnt)
    {
    	ANDforEnumObjektGeometrie (pGrabObjs, pActGrabObjs, wObj.ppi());

    	pGrabObjs->GetCount (&ulAndCnt);

    	if (0 == ulAndCnt)	// kein Objekt besitzt beide Stützpunkte, deshalb Neubeginn mit dem
    	{					// Aufbau des Gerüstes für CommonBorder
    		pGrabObjs->Clear();
    		for (pActGrabObjs->Reset(); S_OK == pActGrabObjs->Next (1, Unk.ppi(), NULL); )
			{
				wObj = Unk;
    			pGrabObjs->AddItem (wObj);
			}
    		return S_FALSE;
    	}

    	iGrabCnt++;

    	if (1 == ulAndCnt)	// genau EIN Objekt besitzt beide Stützpunkte
    	{
			wObj->GetObjTyp (&iOT);
    		if (OT_KANTE == iOT)
    		{
				if (S_FALSE == IsClosedLine (wObj, iOT))
				{
					wObj->GetONr (&lComONr);
					return S_OK;	// dieses Objekt ist eine offene Kante
				}
    		}
    		return S_FALSE;		// dieses Objekt ist eine Fläche oder eine geschlossene Kante
    	}

    	// mehrere Objekte besitzen beide Stützpunkte
    	for (pGrabObjs->Reset(); S_OK == pGrabObjs->Next (1, Unk.ppi(), NULL); )
		{
			wObj = Unk;
			wObj->GetObjTyp (&iOT);
    		if (OT_FLAECHE == iOT) return S_FALSE;	// es sind auch Flächen dabei
		}
    	return E_PENDING;			// mehrere Kanten
    }


    // 3. GrabPunkt (26.08.98)
    ANDforEnumObjektGeometrie (pGrabObjs, pActGrabObjs, wObj.ppi());

    pGrabObjs->GetCount (&ulAndCnt);

    if (0 == ulAndCnt)	// kein Objekt besitzt alle Stützpunkte, deshalb Neubeginn
    {
    	pGrabObjs->Clear();
    	for (pActGrabObjs->Reset(); S_OK == pActGrabObjs->Next (1, Unk.ppi(), NULL); )
		{
			wObj = Unk;
    		pGrabObjs->AddItem (wObj);
		}
    	iGrabCnt = 1;
    	return S_FALSE;
    }

	if (iGrabCnt <= iComCnt)		// 26.08.98
	    iGrabCnt++;

    if (1 == ulAndCnt)	// genau EIN Objekt besitzt alle Stützpunkte
    {
    	wObj->GetONr (&lComONr);
    	return S_OK;
    }

    return E_PENDING;	// mehrere Objekte besitzen alle Stützpunkte

} // IsCommonBorderAllowable


// --------------------------------------------------------------------------------------------
// Test, ob das lONr-Objekt eine geschlossene Kante ist; return-Werte sind
//   S_OK			geschlossene Kante
//   S_FALSE		offene Kante
//   E_UNEXPECTED	temporäres Objekt oder keine Kante
HRESULT IsClosedLine (long lONr)
{
	if (0 == lONr || -1 == lONr || OT_KANTE != DEX_GetObjectType (lONr))
		return E_UNEXPECTED;

WObjektGeometrie wObj;	// ObjektGeometrie des lONr-Objektes
long lCnt;
KoOrd* plXK; KoOrd* plYK;

	try
	{
	WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);

    	THROW_FAILED_HRESULT (wIObj->InitObjGeometry (lONr));
    	wObj = wIObj;

    	wObj->GetCnt (&lCnt);
    	wObj->GetX ((void**)&plXK);
    	wObj->GetY ((void**)&plYK);

		if (plXK[0] != plXK[lCnt-1] || plYK[0] != plYK[lCnt-1])
			return S_FALSE;
	}

	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

    return S_OK;

} // IsClosedLine


// --------------------------------------------------------------------------------------------
// Test, ob das pIOG-Objekt eine geschlossene Kante ist; return-Werte sind
//   S_OK			geschlossene Kante
//   S_FALSE		offene Kante
//   E_UNEXPECTED	keine Kante
HRESULT IsClosedLine (IObjektGeometrie* pIOG, short iOT)
{
	if (OT_KANTE != iOT)
		return E_UNEXPECTED;

long lCnt;
KoOrd* plXK; KoOrd* plYK;

	pIOG->GetCnt (&lCnt);
	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);

	if (plXK[0] != plXK[lCnt-1] || plYK[0] != plYK[lCnt-1])
		return S_FALSE;
    return S_OK;

} // IsClosedLine


// --------------------------------------------------------------------------------------------
// in pEnumONr1 werden die Objektnummern zurück gegeben, die sowohl in pEnumONr1 als auch in
// pEnumONr2 enthalten sind (Durchschnitt)
HRESULT ANDforEnumObjektGeometrie (IEnumObjektGeometrie* pEnumONr1,
    							   IEnumObjektGeometrie* pEnumONr2, IObjektGeometrie** ppIOG)
{
long lONr1, lONr2;

    try
    {
    WEnumObjektGeometrie wAnd (CLSID_EnumObjektGeometrie);
	WUnknown Unk;

    	for (pEnumONr1->Reset(); S_OK == pEnumONr1->Next (1, Unk.ppi(), NULL); )
    	{
		WObjektGeometrie wObj (Unk);

			wObj->GetONr (&lONr1);

	    	for (pEnumONr2->Reset(); S_OK == pEnumONr2->Next (1, Unk.ppi(), NULL); )
			{
			WObjektGeometrie wObj (Unk);

				wObj->GetONr (&lONr2);

    			if (lONr1 == lONr2)
    			{
    				wAnd->AddItem (wObj);
    				*ppIOG = wObj.detach();
    			}
			}
		}

    ulong ul1, ulAnd;

    	pEnumONr1->GetCount(&ul1);
    	wAnd->GetCount(&ulAnd);

    	if (ul1 > ulAnd)
    	{
    		pEnumONr1->Clear();
    		for (wAnd->Reset(); S_OK == wAnd->Next (1, Unk.ppi(), NULL); )
			{
			WObjektGeometrie wObj (Unk);

    			pEnumONr1->AddItem (wObj);
			}
    	}
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // ANDforEnumObjektGeometrie



///////////////////////////////////////////////////////////////////////////////////////////////
// Position für Dialog bestimmen, der einem GeometrieObjekt zugeordnet werden soll;
// zuerst wird versucht, den Dialog unter das GeometrieObjekt zu positionieren; ist der
// Dialog nicht vollständig auf dem Bildschirm zu sehen, wird versucht, ihn oberhalb, dann
// rechts daneben und schließlich links daneben zu positionieren;
// läßt sich der Dialog nirgends außerhalb des Objektcontainers positionieren, ohne dabei über
// den Bildschirmrand hinauszuragen, wird er in die linke untere Bildschirmecke (0, 0)
// gestellt;
// PLU:        linke untere Ecke des Containers um das Geometrieobjekt, dem der Dialog
//             zugeordnet werden soll
// PRO:        rechte obere Ecke
// dimDlgSize: Größe des Dialogs
Point DialogPosition (Point PLU, Point PRO, Dimension dimDlgSize)
{
Window MWnd(__hWndM);				// TRiAS-Hauptfenster
Dimension dimMWin = MWnd.GetSize();	// Größe (im Point-Format) des Hauptfensters
CoOrd DlgW = dimDlgSize.Width();	// Breite und
CoOrd DlgH = dimDlgSize.Height();	//  Höhe des Dialogs
CoOrd x, y;	// Koordinaten des linken unteren Punktes des Dialog-Fensters (return-Wert)

int iXBord = GetSystemMetrics (SM_CXBORDER);	// Rahmenbreite um ein Window	
int iYBord = GetSystemMetrics (SM_CYBORDER);

int iHScroll = 0;	// Höhe des horizontale Scrollbalkens einschließlich des Rahmens
DWORD dwWndStyle = GetWindowStyle (g_pTE->MVWind()->Handle());

	if (dwWndStyle & WS_HSCROLL)
		iHScroll = GetSystemMetrics (SM_CYHSCROLL) + 2*iYBord;

Point PtLUV = g_pTE->MVWind()->GetPosition();	// linke untere Ecke des TRiAS-ViewFensters im
												// TRiAS-Hauptfenster
	PtLUV.X() += 8 * iXBord;
	PtLUV.Y() += 8 * iYBord;

    // Versuch, den Dialog unterhalb des editierten Objektes zu positionieren
    x = PLU.X();
    y = PLU.Y() - DlgH - iAway;	// Subtraktion von iAway, damit Dialog nicht am Objekt klebt

	// nachfolgend wird PtLUV.X() bzw. PtLUV.Y() addiert, um die Differenz zwischen dem
	// TRiAS-Haupt- und TRiAS-ViewFenster am LINKEN bzw. UNTEREN Rand zu berücksichtigen
    if (PtLUV.Y() + iHScroll + y >= 0)
	{
    	if (PtLUV.X() + x + DlgW > dimMWin.Width())	// Dialog ragt rechts aus dem Bildschirm
    		x = dimMWin.Width() - DlgW - PtLUV.X();	// heraus, deshalb nach links verschieben
    	return Point (x, y);
    }

    // Versuch, den Dialog oberhalb des editierten Objektes zu positionieren
    x = PLU.X();
    y = PRO.Y() + iAway;

    if (PtLUV.Y() + iHScroll + y + DlgH <= dimMWin.Height())
    {
    	if (PtLUV.X() + x + DlgW > dimMWin.Width())
    		x = dimMWin.Width() - DlgW - PtLUV.X();
    	return Point (x, y);
    }
    
    // Versuch, den Dialog rechts neben dem editierten Objekt zu positionieren; selbst wenn das
	// gänge, dürfte der Dialog nicht oben über das TRiAS-Hauptfenster hinaus ragen
    x = PRO.X() + iAway;
    y = PLU.Y();
    if (PtLUV.X() + x + DlgW <= dimMWin.Width() &&				// rechts wäre möglich
		PtLUV.Y() + iHScroll + y + DlgH <= dimMWin.Height())	// nach oben auch kein Problem
    	return Point (x, y);
    
    // Versuch, den Dialog links neben dem editierten Objekt zu positionieren; selbst wenn das
	// gänge, dürfte der Dialog nicht oben über das TRiAS-Hauptfenster hinaus ragen
    x = PLU.X() - DlgW - iAway;
    y = PLU.Y();
    if (PtLUV.X() + x >= 0 &&									// links wäre möglich
		PtLUV.Y() + iHScroll + y + DlgH <= dimMWin.Height())	// nach oben auch kein Problem
    	return Point (x, y);
    
    // Dialog ragt immer über das TRiAS-Hauptfenster hinaus, wenn versucht wird, ihn außerhalb
    // des Objektcontainers zu positionieren; deshalb wird Dialog in die linke untere
    // Ecke (0, 0) des TRiAS-ViewFenster gestellt bzw. noch tiefer
	if (PtLUV.Y() + iHScroll + DlgH <= dimMWin.Height())	// nach oben kein Problem
		return Point (0, 0);

    y = dimMWin.Height() - (PtLUV.Y() + iHScroll + DlgH);
	return Point (0, y);

} // DialogPosition


// --------------------------------------------------------------------------------------------
// Position für Dialog aus dem Container des pIOG-Objektes bestimmen
Point DialogPosition (IObjektGeometrie* pIOG, Dimension dimDlgSize)
{
    _ASSERTE (pIOG != NULL);

KoOrd lCXmin, lCXmax, lCYmin, lCYmax;	// Koordinaten des Containers von pIOG

    pIOG->GetCont (&lCXmin, &lCXmax, &lCYmin, &lCYmax);

Point PLU = BSKoordinaten (lCXmin, lCYmin);	// linke untere Container-Ecke
Point PRO = BSKoordinaten (lCXmax, lCYmax);	// rechte obere Container-Ecke

	return DialogPosition (PLU, PRO, dimDlgSize);

} // DialogPosition



///////////////////////////////////////////////////////////////////////////////////////////////
// Objektklassenschlüssel definiert setzen
HRESULT SetObjectClassKey (IEnumObjektGeometrie* pIEnumOG, ulong& ulIdent)
{
    _ASSERTE (pIEnumOG != NULL);

    pIEnumOG->Reset();

ulong ulObjIdent;
WUnknown Unk;
HRESULT hrRet = pIEnumOG->Next (1, Unk.ppi(), NULL);

	try
	{
		if (S_OK == hrRet)
		{
		WObjektGeometrie wObj (Unk);

			wObj->GetIdent (&ulIdent);
		}

		for (; S_OK == pIEnumOG->Next (1, Unk.ppi(), NULL); )
		{
		WObjektGeometrie wObj (Unk);

			// wenn alle pIEnumOG-Objekte den gleichen Objektklassenschlüssel besitzen, dann
			// eben diesen in der PropertyPage anzeigen, sonst den UnknownIdent abfragen,
			// wodurch dann in der PropertyPage keiner angezeigt wird
			wObj->GetIdent (&ulObjIdent);
			if (ulObjIdent != ulIdent)
			{
			HPROJECT hPr = DEX_GetObjectsProject (ulIdent);

    			ulIdent = DEX_GetUnknownIdentEx (hPr);
    			break;
			}
		}
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

    DEX_SetLastIdent (ulIdent);	//  Objektklassenschlüssel definiert setzen

    return hrRet;

} // SetObjectClassKey


// --------------------------------------------------------------------------------------------
// vorzeichenbehafteter Flächeninhalt der neuesten hinzugekommenen Dreiecksfläche in m²
// berechnen
double DreieckInhalt (Point Pt, EPunkt& FirstPkt, EPunkt& LastPkt, CoordTransX* pCT)
{
    // pCT kann NULL sein

EPunkt AktPkt = DBKoordinaten (Pt);	// Punkt der Mausspitze
KoOrd plXK[3], plYK[3];

    plXK[0] = LastPkt.X();
    plYK[0] = LastPkt.Y();
    plXK[1] = AktPkt.X();
    plYK[1] = AktPkt.Y();
    plXK[2] = FirstPkt.X();
    plYK[2] = FirstPkt.Y();

double dFlInhalt;

    AreaSize (plXK, plYK, 0, 2, pCT, &dFlInhalt);	// vorzeichenbehafteter Flächeninhalt

    return dFlInhalt;

} // DreieckInhalt


// --------------------------------------------------------------------------------------------
// Normierung des Flächeninhaltes dFlInhalt auf km², ha oder m²	und Eintrag in sOutBuff
void FlInhaltNormieren (double dFlInhalt, string& sOutBuff)
{
char pcKonvBuff [40] = { '\0' };	// Konvertierungspuffer

    if (dFlInhalt > 1000000.)
    {
    	DtoA (pcKonvBuff, "%5.3f", dFlInhalt/1000000.);
    	sOutBuff += pcKonvBuff;				// Ausgabe in km²
    	sOutBuff += " km²";
    }
    else if (dFlInhalt > 10000.)
    {
    	DtoA (pcKonvBuff, "%5.3f", dFlInhalt/10000.);
    	sOutBuff += pcKonvBuff;				// Ausgabe in ha
    	sOutBuff += " ha";
    }
    else
    {
    	DtoA (pcKonvBuff, "%1.0f", dFlInhalt);
    	sOutBuff += pcKonvBuff;				// Ausgabe in m²
    	sOutBuff += " m²";
    }

} // FlInhaltNormieren


// --------------------------------------------------------------------------------------------
// Position CurPt des Cursor (in BS-Koordinaten) in Abhängigkeit von den
// Konstruktionshilfslinien pIRL1 bzw. pIRL2 berechnen (ohne Grabben !);
// der return-Wert ist "S_OK", wenn sich die Cursorposition berechnen ließ, sonst S_FALSE 
HRESULT EPunktAtCursor (LPARAM lParam, IRestrictLine* pIRL1, IRestrictLine* pIRL2,
						Point& CurPt, EPunkt& CurPkt)
{
	// keine Konstruktionshilfslinien vorgegeben
	if (!pIRL1 && !pIRL2)
		CurPt = BSPoint (lParam);

	// Konstruktionshilfslinien sind vorgegeben
	else
	{
		if (!pIRL1 || !pIRL2)	// genau 1 Konstruktionshilfslinie
		{
			// wenn sich die Mausspitze genau im Mittelpunkt einer kreisförmigen Hilfslinie
			// befindet, wird keine neue Position berechnet (weil's eben nicht geht), sondern
			// die bisherige wird zurückgegeben
			if (pIRL1) pIRL1->CursorTo1RestrictLine (lParam, &(POINT&)CurPt);
			if (pIRL2) pIRL2->CursorTo1RestrictLine (lParam, &(POINT&)CurPt);
		}
		else					// 2 Konstruktionshilfslinien
			// wenn der return-Wert von CursorTo2RestrictLines() "S_FALSE" ist, wurde eine
			// MessageBox angezeigt
			if (//false == m_bMessBox &&		// keine MessageBox angezeigt
				S_FALSE == pIRL1->CursorTo2RestrictLines (lParam, pIRL2, &(POINT&)CurPt))
				return S_FALSE;
	}

	CurPkt = DBKoordinaten (CurPt);
	return S_OK;

} // PointAtCursor


// --------------------------------------------------------------------------------------------
// rechteckigen Bereich bestimmen, der sich aus dem umschließenden Rechteck des pIObj-Objektes
// ergibt, das noch um das Maximum aus Markergröße und Ausdehnung des Cursors vergrößert wird;
// außerdem muß der Punkt PtAdd in dem Ergebnisrechteck liegen
Rectangle GetDeleteRectangle (IObjektGeometrie* pIObj, ITopicalObjects* pITopObjs,
							  IRestrictCursor* pIRestrCursor, Point PtAdd)
{
	_ASSERTE (pIObj != NULL);	// pITopObjs und pIRestrCursor können NULL sein !

int iMarkGr = 0;				// Markergröße
long lWidth = 0, lHeight = 0;	// Ausdehnung des Cursors
long lMax;						// Maximum aus iMarkGr, lWidth und lHeight
Rectangle Rec;					// umschließendes Rechteck des pIObj-Objektes

	if (pITopObjs) pITopObjs->GetMarkerSizeBS (&iMarkGr);
	if (pIRestrCursor) pIRestrCursor->GetDimension (&lWidth, &lHeight);
	lMax = max (lWidth, lHeight);
	lMax = max (lMax, (long)iMarkGr);
	pIObj->RectangleToDraw2 ((RECT*)&Rec, lMax);
	
	Rec.Left()   = min (Rec.Left(), PtAdd.X()) - iZug;
	Rec.Right()  = max (Rec.Right(), PtAdd.X()) + iZug;
	Rec.Top()    = max (Rec.Top(), PtAdd.Y()) + iZug;
	Rec.Bottom() = min (Rec.Bottom(), PtAdd.Y()) - iZug;

	return Rec;

} // DrawObjBackground


// --------------------------------------------------------------------------------------------
// Recherchefenster für neu erzeugte Objekte generieren
void RechWindowForNewObjects (LPCSTR pszCaption, POINT PT, long* plNeuObjNr, int iAnzNeuObj)
{
CREATEOBJEKTINFOEX3 COI;	// Struktur für Recherchefenster
    
    INITSTRUCT (COI, CREATEOBJEKTINFOEX3);
    COI.lpCaption = (char*)pszCaption;	// Fensterüberschrift
    COI.plObjs = plNeuObjNr;			// Objektnummern, die angezeigt werden sollen
    COI.lNumObjs = iAnzNeuObj;			// Anzahl der Objektnummern
    COI.cMColor = RGB (160,60,180);		// Markierungsfarbe (rot, grün, blau)
    COI.pntPos = PT;					// Position des Recherchefensters im Hauptfenster

    DEX_CreateObjektInfo (COI);			// Recherchefenster anzeigen

} // RechWindowForNewObjects


// --------------------------------------------------------------------------------------------
// Berechnung der Koeffizienten für die Transformation der Digitizer- in die Realkoordinaten
//	iCnt		Anzahl der Koordinaten
//	pdXD, pdYD	Digitizerkoordinaten 
//	pdXR, pdYR	Realkoordinaten
// Rückgabewerte sind:
//	dT[2]		Translationsvektor
//	dM[2][2]	Rotationsmatrix
//	pdErr		Fehler zwischen abgetasteten und rückgerechneten Digitizerkoordinaten
bool TransformCoeffsDigitToReal (int iCnt, double* pdXD, double* pdYD, double* pdXR,
								 double* pdYR, double dT[2], double dM[2][2], double* pdErr)
{
long double sx = 0., sy = 0., sxx = 0., syy = 0., sxy = 0.;	// Zwischensummen
long double sxr = 0., syr = 0.;
long double sxrx = 0., sxry = 0., syrx = 0., syry = 0.;

	for (int i = 0; i < iCnt; i++)
	{
		sx += pdXD[i];
		sy += pdYD[i];
		sxx += pdXD[i] * pdXD[i];
		syy += pdYD[i] * pdYD[i];
		sxy += pdXD[i] * pdYD[i];
		sxr += pdXR[i];
		syr += pdYR[i];
		sxrx += pdXR[i] * pdXD[i];
		sxry += pdXR[i] * pdYD[i];
		syrx += pdYR[i] * pdXD[i];
		syry += pdYR[i] * pdYD[i];
	}

long double a = sxx - sx*sx/iCnt;	// Hilfsgrößen
long double g = syy - sy*sy/iCnt;
long double c = sxy - sx*sy/iCnt;
long double b = sxrx - sxr*sx/iCnt;
long double h = sxry - sxr*sy/iCnt;
long double e = syrx - syr*sx/iCnt;
long double k = syry - syr*sy/iCnt;

long double dNen = c*c - a*g;

	if (0. == dNen || 0. == c)
	{
		MessageBox (__hWndM, "Die Transformationskoeffizienten lassen sich nicht berechnen!",
    				"Koordinatentransformation:", MB_ICONERROR | MB_OK);
		return false;
	}

long double c1 = (c*h-b*g) / dNen;
long double c2 = b/c - a/c*c1;
long double d1 = (c*k-e*g) / dNen;
long double d2 = e/c - a/c*d1;

	dM[0][0] = c1;
	dM[0][1] = c2;
	dM[1][0] = d1;
	dM[1][1] = d2;
	dT[0] = (sxr - c1*sx - c2*sy)/iCnt;
	dT[1] = (syr - d1*sx - d2*sy)/iCnt;


// Fehlerberechnung
long double dDet = c1*d2 - c2*d1;	// Determinante für inverse Matrix

	if (0. == dDet)
	{
		MessageBox (__hWndM, "Die Abweichungen lassen sich nicht ermitteln!",
    				"Koordinatentransformation:", MB_ICONERROR | MB_OK);
		return false;
	}

long double c1i = d2 / dDet;	// Elemente der inversen Matrix
long double c2i = -c2 / dDet;
long double d1i = -d1 / dDet;
long double d2i = c1 / dDet;
double sf = 0.;

	for (i = 0; i < iCnt; i++)
	{
	long double d0 = pdXR[i] - dT[0];
	long double d1 = pdYR[i] - dT[1];
	long double dx = c1i*d0 + c2i*d1 - pdXD[i];
	long double dy = d1i*d0 + d2i*d1 - pdYD[i];

		pdErr[i] = sqrt (dx*dx + dy*dy);
		sf += pdErr[i];
	}

	return true;

} // TransformCoeffsDigitToReal
