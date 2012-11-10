// Definitionen: Verschieben eines Stützpunktes
// File: VertexMove.cpp
// W. Mörtl


#include "GeoEditP.h"

#include "VertexMove.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
CVertexMove::CVertexMove (void)
{
	m_pVWnd = g_pTE->MVWind();	// TRiAS-ViewFenster
	m_NewCP = CURSPOS_UNKNOWN;
	m_OldCP = CURSPOS_UNKNOWN;
	m_pMk = NULL;
}


// --------------------------------------------------------------------------------------------
// Destruktor
CVertexMove::~CVertexMove (void)
{
	DELETE_OBJ (m_pMk);
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Verbindung zur CObjectModify-Klasse über das Interface IModifyClassSite herstellen;
// es wird KEINE (!!) Verbindung zu TRiAS über Interface ITriasExtension hergestellt, die
// WindowsMessages werden vom CObjectModify-Objekt heruntergereicht
STDMETHODIMP CVertexMove::SetModifyClassSite (IEditExtensionSite* pIEdExSite,
											  IModifyClassSite* pIModClSite)
{
	try
	{
		if (pIEdExSite != NULL)
		{
			THROW_FAILED_HRESULT (pIEdExSite->CreateInterfaceTO (m_wTopObjs.ppi()));
			m_wEdExSite = pIEdExSite;
		}
		else
		{
			m_wTopObjs.Assign (NULL);	// freigeben
			m_wEdExSite.Assign (NULL);	// freigeben
		}
		m_wModClSite = pIModClSite;
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

	return S_OK;

} // SetModifyClassSite


// --------------------------------------------------------------------------------------------
STDMETHODIMP CVertexMove::LineElongation (IEnumObjektGeometrie*, long, long)
{
    ATLTRACENOTIMPL("CVertexMove::LineElongation");
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CVertexMove::AreaPartition (long, POINT)
{
    ATLTRACENOTIMPL("CVertexMove::AreaPartition");
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CVertexMove::IslandAddition (IEnumObjektGeometrie*)
{
    ATLTRACENOTIMPL("CVertexMove::IslandAddition");
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CVertexMove::Rectangularity (long, int, long, double, double, double,
										  IEnumObjectsByNumber**)
{
    ATLTRACENOTIMPL("CVertexMove::Rectangularity");
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CVertexMove::MakeCommonBorder (IEnumObjektGeometrie*, long, long)
{
    ATLTRACENOTIMPL("CVertexMove::MakeCommonBorder");
}


// --------------------------------------------------------------------------------------------
// Interface ITRiASNotificationSink: TRiAS-Notification's abfangen
STDMETHODIMP CVertexMove::ServerEvent (SERVEREVT se)
{
    ATLTRACE("CVertexMove::ServerEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CVertexMove::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT vProj)
{
    ATLTRACE("CVertexMove::ProjectEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// TRiAS-Notification's abfangen, die für die aktuelle Sicht verschickt werden
STDMETHODIMP CVertexMove::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT vData)
{
    switch (ve)
    {
		case GEOVIEWEVT_ScrollingHorz:
			if (m_wDragObj.IsValid() &&	// es befindet sich ein DragLineObject im Aufbau
				SUCCEEDED (VariantChangeType (&vData, &vData, NULL, VT_I4)))
			{
			long lOffset = V_I4 (&vData);

				m_wDragObj->EditWithScrolling (lOffset, true);

				// Position des Markierungsquadrates ebenfalls verschieben
				m_pVWnd->Draw (m_pMk);		// bisherige Position löschen
				m_ptMSp.X() += lOffset;		// neue Position
				m_pMk->Process (m_ptMSp);	//  einstellen
			}
    		break;

		case GEOVIEWEVT_ScrollingVert:
			if (m_wDragObj.IsValid() &&
				SUCCEEDED (VariantChangeType (&vData, &vData, NULL, VT_I4)))
			{
			long lOffset = V_I4 (&vData);

				m_wDragObj->EditWithScrolling (lOffset, false);

				// Position des Markierungsquadrates ebenfalls verschieben
				m_pVWnd->Draw (m_pMk);		// bisherige Position löschen
				m_ptMSp.Y() -= lOffset;		// neue Position
				m_pMk->Process (m_ptMSp);	//  einstellen
			}
			break;
    }

    return S_OK;	// immer weiterleiten

} // GeoViewEvent


// --------------------------------------------------------------------------------------------
STDMETHODIMP CVertexMove::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
    ATLTRACE("CVertexMove::GeoClassEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CVertexMove::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
    ATLTRACE("CVertexMove::GeoObjectEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CVertexMove::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
    ATLTRACE("CVertexMove::GeoFeatureEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CVertexMove::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
    ATLTRACE("CVertexMove::GeoRelationEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CVertexMove::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
    ATLTRACE("CVertexMove::ObjectWindowEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Interface ITRiASSysNotificationSink: WindowsNotification's abfangen
STDMETHODIMP CVertexMove::WindowsMessage (long hWnd, long uiMsg, long wParam, long lParam)
{
	switch (uiMsg)
	{
		case WM_KEYDOWN:
			KeyDown ((HWND)hWnd, wParam);
			break;
		
		case WM_KEYUP:
			KeyUp (wParam);
			break;

		case WM_MOUSEMOVE:
			MouseMove (lParam);
			break;

		case WM_LBUTTONDOWN:
			LeftMouseDown();
			break;

		case WM_LBUTTONUP:
			LeftMouseUp (lParam);
//			break;

//		default:		ist das hier auch richtig ??? (21.01.99)
//			return S_FALSE;
	}

    return S_OK;	// immer weiterleiten

} // WindowsMessage


// --------------------------------------------------------------------------------------------
// eine Taste der Tastatur wurde gedrückt
HRESULT CVertexMove::KeyDown (HWND hWnd, WPARAM wParam)
{
	if (VK_SHIFT == wParam)		// SHIFT-Taste gedrückt (um Grab-Funktion auszuschalten)
		return m_wEdExSite->SetCursor (CURSFORM_STERN, TRUE);	// dann STERN-Form
	else
		ScrollTest (hWnd, wParam);

	return S_OK;

} // KeyDown


// --------------------------------------------------------------------------------------------
// eine Taste der Tastatur wurde losgelassen
HRESULT CVertexMove::KeyUp (WPARAM wParam)
{
	if (VK_SHIFT == wParam)			// SHIFT-Taste losgelassen
	{
	CursForm CF;	// aktuelle CursorForm

		m_wEdExSite->GetCursor (&CF);

		if (CURSFORM_STERN == CF &&			// Cursor hat noch STERN-Form
			CURSPOS_VERTEX == m_NewCP &&	// Cursor in einer Stützpunktmarkierung
			m_wBelowObjs &&
			m_wActBelowObjs &&
			S_OK == m_wTopObjs->IsGrabAllowable (m_ModPkt.X(), m_ModPkt.Y(), m_lMSpX, m_lMSpY,
												 m_wBelowObjs, m_wActBelowObjs, -1L))
			return m_wEdExSite->SetCursor (CURSFORM_FANGEN, TRUE);
	}

	return S_OK;

} // KeyUp


// --------------------------------------------------------------------------------------------
// Stützpunkte verschieben
HRESULT CVertexMove::MouseMove (LPARAM lParam)
{
	if (! m_wDragObj.IsValid())	// StützpunktVerschieben schon beendet
		return S_OK;

	m_ptMSp = BSPoint (lParam);	// BS-Punkt der Mausspitze

	// bisherige Position des Markierungsquadrates löschen (das allererste Mal wurde die
	// Markierung durch Routine MarkerVisibility() gezeichnet
	m_pVWnd->Draw (m_pMk);
	m_pMk->Process (m_ptMSp);	// neue Position einstellen
	m_pVWnd->Draw (m_pMk);		// neue Position zeichnen

	// angrenzende Strecken als "Gummiband" mitziehen
	m_wDragObj->SetEndPoint ((POINT&)m_ptMSp, FALSE, TRUE);

HRESULT hr = m_wTopObjs->CursorAtTopicalObjects (&m_NewCP, NULL, &m_lMSpX, &m_lMSpY,
												 m_wActBelowObjs.ppi());
	if (FAILED(hr)) return hr;

	if (m_NewCP == m_OldCP) return S_OK;

	m_OldCP = m_NewCP;	// bisherige CursorPosition retten

	if (CURSPOS_VERTEX == m_NewCP &&		// Cursor im Marker eines Stützpunktes und
		(GetKeyState (VK_SHIFT) >= 0) &&	//  SHIFT-Taste nicht gedrückt, d.h. Grabben
		S_OK == m_wTopObjs->IsGrabAllowable (m_ModPkt.X(), m_ModPkt.Y(), m_lMSpX, m_lMSpY,
											 m_wBelowObjs, m_wActBelowObjs, -1L))
		return m_wEdExSite->SetCursor (CURSFORM_FANGEN, TRUE);	// CursorForm für Grabben

	return m_wEdExSite->SetCursor (CURSFORM_STERN, TRUE);

} // MouseMove


// --------------------------------------------------------------------------------------------
// Verschieben der Stützpunkte beim Drücken der linken Maustaste vorbereiten
HRESULT CVertexMove::LeftMouseDown (void)
{
	// Parameter von der CObjectModify-Klasse holen, die für das Verschieben des Stützpunktes
	// noch benötigt werden
	m_wModClSite->GetParameter (&m_ModPkt.X(), &m_ModPkt.Y(), m_wBelowObjs.ppi());

ulong ulBelowCnt;	// Anzahl der Objekte, die zu Beginn der Stützpunkt-Verschiebe-Aktion unter
					// der Mausspitze lagen
	m_wBelowObjs->GetCount(&ulBelowCnt);

	// das es unerklärlicherweise vorkommen kann, daß zu Beginn der Stützpunkt-Verschiebe-Aktion
	// kein Objekt unter der Mausspitze lag, nachfolgende Abfrage
	if (ulBelowCnt < 1)
		return S_FALSE;

Point BSPt = BSKoordinaten (m_ModPkt.X(), m_ModPkt.Y());
int iMarkGr;

	m_wTopObjs->GetMarkerSizeBS (&iMarkGr);
	DELETE_OBJ (m_pMk);
	m_pMk = new Marker (BSPt, iMarkGr, ulGW0);

	m_pMk->ChangeRop (ROP_Invert);	// das von m_pMk überzeichnete Gebiet wird invertiert

	m_wDragObj.Assign (NULL);

long lInd = 0;	//  Stützpunktindex eines der Objekte, von denen ein Stützpunkt verschoben
				//  werden soll
WObjektGeometrie wObj;	// ObjektGeometrie des lONr-Objektes
short iOT;				// Parameter des lONr-Objektes
long lCnt;
KoOrd* plXK; KoOrd* plYK;
long i = 0;			// laufender Index von m_wBelowObjs

	try
	{
	// Verbindung zum CDragMultiLine-Objekt über dessen Interface IDragObject herstellen
	WDragObject wDragObj (CLSID_DragMultiLine);		// throws_com_error

		m_wDragObj = wDragObj;

	WUnknown Unk;

    	for (m_wBelowObjs->Reset(); S_OK == m_wBelowObjs->Next (1, Unk.ppi(), NULL); )
    	{
		WObjektGeometrie wObj (Unk);

			wObj->GetObjTyp (&iOT);
			if (iOT != OT_KANTE && iOT != OT_FLAECHE) 
				continue;	// Banding nur bei Linien- bzw. Flächenobjekt

			// Index lInd des zu verschiebenden Stützpunktes m_ModPkt innerhalb des x- bzw.
			// y-Vektors bestimmen
			if (FAILED (wObj->GetVertexIndex (m_ModPkt.X(), m_ModPkt.Y(), &lInd)))
			// Nachfolgende Änderung wurde vorgenommen, da es den Fall gibt, daß unter dem
			// Mausklick wenigstens 2 Objekte liegen, deren Stützpunkte nur "fast" gleich sind,
			// deren Marker dadurch aber auch nur "fast" gleich sind. Es wird dann nur der
			// Stützpunkt verschoben, der exakt mit m_ModPkt übereinstimmt (29.03.99).
				continue;

		// Indizes des vorhergehenden bzw. nachfolgenden Stützpunktes vom zu verschiebenden
		// Stützpunkt ermitteln
		long lIndv = lInd - 1;	// führt bei Kante zu einem
		long lIndn = lInd + 1;	//  einkalkulierten Indexfehler

			// ist wObj eine Fläche, wird hier evtl. noch eine Korrektur an lIndv oder lIndn
			// vorgenommen
			if (OT_FLAECHE == iOT)
			{
				if (FAILED (wObj->IndexVorNach (lInd, &lIndv, &lIndn)))
					_ASSERTE (false);
			}

			// DB-Koordinaten des vorhergehenden bzw. nachfolgenden Punktes zum verschobenen
			// Punkt
			wObj->GetX ((void**)&plXK);
			wObj->GetY ((void**)&plYK);

		// BS-Koordinaten des vorhergehenden bzw. nachfolgenden Punktes
		Point PV = BSKoordinaten (plXK [lIndv], plYK [lIndv]);
		Point PN = BSKoordinaten (plXK [lIndn], plYK [lIndn]);

		bool bVor = true;		// es gibt einen vorhergehenden Punkt
		bool bNach = true;		// es gibt einen nachfolgenden Punkt

			if (OT_KANTE == iOT)	// Sonderfall am Kantenende
			{
				wObj->GetCnt (&lCnt);

				// beim 1. bzw. letzten Stützpunkt einer Kante nur "halbes" Banding
				if (0 == lInd) bVor = false;
				if (lInd == lCnt-1) bNach = false;
			}

			if (bVor && bNach)
			{
				m_wDragObj->AddStartPoint ((POINT&)PV);
				m_wDragObj->AddStartPoint ((POINT&)PN);
			}
			else
			{
				if (! bVor)
					m_wDragObj->AddStartPoint ((POINT&)PN);
				if (! bNach)
					m_wDragObj->AddStartPoint ((POINT&)PV);
			}

			i++;
		} // for
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

	m_wDragObj->ConstructDragLines();

	// Maus einfangen, damit die Maus-Messages auch dann weiterhin empfangen werden können,
	// wenn sich der Cursor außerhalb des Anwendungsbereiches (d.h. über einem anderen Fenster)
	// befindet
	m_pVWnd->MouseTrap (TRUE);

	return S_OK;

} // LeftMouseDown


// --------------------------------------------------------------------------------------------
// Verschieben der Stützpunkte beim Loslassen der linken Maustaste abschließen
bool CVertexMove::LeftMouseUp (LPARAM lParam)
{
	// Maus freigeben, wodurch die Maus-Messages nicht empfangen werden, wenn sich der Cursor
	// außerhalb des Anwendungsbereiches (d.h. über einem anderen Fenster) befindet
	m_pVWnd->MouseTrap (FALSE);

CEierUhr Wait (m_pVWnd);	// Verschieben, Test, Zeichnen ... kann länger dauern

Point newPt = BSPoint (lParam);			// BS-Punkt der Mausspitze = neuer Stützpunkt
EPunkt NewPkt = DBKoordinaten (newPt);	// DB-Koordinaten des neuen Stützpunktes
HRESULT hrRet = m_wTopObjs->NewVertexWithGrab ((POINT*)&newPt, NULL, &NewPkt.X(), &NewPkt.Y(),
											   NULL);

	// die nachfolgenden 2 Befehle müssen VOR ModObjSpeicherung() stehen, da dort
	// überraschenderweise noch ein MouseMove() dazwischen schlägt
	if (m_wDragObj.IsValid())
	{
		m_wDragObj->DragTerminate();
		m_wDragObj.Assign (NULL);
	}

Rectangle AllRec, Rec;		// Bereiche für das Neuzeichnen nach dem Verschieben
bool bAllRecInit = false;	// AllRec (noch) nicht initialisiert

long lInd;				//  Stützpunktindex eines der Objekte, von denen ein Stützpunkt
						//  verschoben werden soll
WObjektGeometrie wObj;	// ObjektGeometrie des lONr-Objektes

bool bMod = true;		// beim Stützpunkt-Verschieben keine Probleme (true)
ResString resText (ResID (IDS_UNDOVERTICESMOVE, pRF), 50);

	DEX_BeginUndoLevel (resText.Addr());

	try
	{
	WUnknown Unk;

    	for (m_wBelowObjs->Reset(); S_OK == m_wBelowObjs->Next (1, Unk.ppi(), NULL); )
    	{
		WObjektGeometrie wObj (Unk);

		// Index lInd des zu verschiebenden Stützpunktes m_ModPkt innerhalb des x- bzw.
		// y-Vektors bestimmen
		HRESULT hr = wObj->GetVertexIndex (m_ModPkt.X(), m_ModPkt.Y(), &lInd);

			if (S_OK != hr)
			// Nachfolgende Änderung wurde vorgenommen, da es den Fall gibt, daß unter dem
			// Mausklick wenigstens 2 Objekte liegen, deren Stützpunkte nur "fast" gleich sind,
			// deren Marker dadurch aber auch nur "fast" gleich sind. Es wird dann nur der
			// Stützpunkt verschoben, der exakt mit m_ModPkt übereinstimmt (29.03.99).
				continue;

			// Stützpunkt in wObj modifizieren
			hr = wObj->ModPunkt (NewPkt.X(), NewPkt.Y(), lInd);

			if (hr != S_OK)
			{
				bMod = false;
				continue;
			}

			hr = m_wModClSite->ModObjSpeicherung (wObj, m_ModPkt.X(), m_ModPkt.Y(), lInd,
												  false, VORRUECK, (RECT*)&Rec);

			// wenn modifiziertes Objekt nicht nach TRiAS gespeichert wird, dann Verschieben
			// rückgängig machen (der 5. Parameter von ModObjSpeicherung() besagt, daß der
			// modifizierte Stützpunkt nicht gelöscht wurde)
			if (S_OK != hr)
			{
				wObj->ModPunkt (m_ModPkt.X(), m_ModPkt.Y(), lInd);
				bMod = false;
			}
			else
				// Rückgabe des neuen Punktes als aktuellen GrabPunkt ist für den Fall
				// notwendig, daß nach dem LeftMouseDown() OHNE ein zwischenzeitliches
				// MouseMove() gleich das nächste LeftMouseUp() kommt
				m_wModClSite->SetGrabPoint (NewPkt.X(), NewPkt.Y());

			if (!bAllRecInit)
			{
				AllRec = Rec;
				bAllRecInit = true;
			}
			else
				AllRec = AllRec.Union (Rec);
		} // for
	}
	catch (_com_error&)
	{
		bMod = false;
	}
	
	if (bMod)	// Verschieben ohne Probleme verlaufen
		DEX_EndUndoLevel();
	else
		DEX_CancelUndoLevel (true);

	// Ausschnitt nach Geometrie-Modifikation neu zeichnen
	DEX_RePaintRectWait (AllRec);
	m_pVWnd->Update();		// sofort zeichnen

	Wait.Hide();	// ein vorgezogener Quasi-Destruktor für CEierUhr Wait
	m_wModClSite->RefreshCursorForm();

	return bMod;

} // LeftMouseUp
