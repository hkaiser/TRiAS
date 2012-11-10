// Definitionen: Hilfslinien für den DesignMode
// File: RestrictLine.cpp
// W. Mörtl


#include "GeoEditP.h"

#include "ScreenGeometry.hxx"	// SegmentSegmentIntersection(), ...
#include "strecke.hxx"			// GeradenLotPunkt()

#include "RestrictLine.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern ResourceFile* pRF;



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
CRestrictLine::CRestrictLine (void)
			 : m_MyPen1 (Dotted, 0, BLACK),					// gepunktete Linie, schwarz 
//			   m_MyPen2 (Dotted, 0, Color(150,150,150)),	// gepunktete Linie, grau
			   m_MyBrush (ClearBrush)		// nur Kreisring (also KEINE gefüllte Kreisfläche)
{
    m_pVWnd = g_pTE->MVWind();	// TRiAS-ViewFenster
	m_bUnDraw = false;			// Konstruktionshilfslinie nicht nicht auf Bildschirm gelöscht
}


// --------------------------------------------------------------------------------------------
// Destruktor
CRestrictLine::~CRestrictLine (void)
{
	DELETE_OBJ (m_pKHL);
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Memberfunktionen
// Konstruktionshilfslinie bilden
STDMETHODIMP CRestrictLine::BuildRestrictLine (LONG lFixX, LONG lFixY, RestrType ResType,
									   double dAngle, double dLength, double dUFX, double dUFY)
{
	m_lFixX = lFixX;		// die unveränderlichen Parameter der Konstruktionshilfslinie
	m_lFixY = lFixY;		// retten, da sie benötigt werden, wenn sich der Sichtausschnitt
	m_dAngle = dAngle;		// verändert und damit die bildschirmbezogenen Parameter
	m_dLength = dLength;	// (m_EPt1, ...) neu berechnet werden müssen
	m_ResType = ResType;
	m_dUFX = dUFX;
	m_dUFY = dUFY;

	if (RESTRTYPE_STRECKE == m_ResType)
		BuildSegmentLine (lFixX, lFixY, dAngle, dLength);
	else if (RESTRTYPE_GERADE == m_ResType)
		BuildStraightLine (lFixX, lFixY, dAngle);
	else if (RESTRTYPE_KREIS == m_ResType)
		BuildCircleLine (lFixX, lFixY, dLength);
	else	//RESTRTYPE_UNKNOWN == m_ResType
	{
		_ASSERTE (RESTRTYPE_STRECKE == m_ResType || RESTRTYPE_GERADE == m_ResType ||
				   RESTRTYPE_KREIS == m_ResType);

		return E_INVALIDARG;
	}

	m_pVWnd->Draw (m_pKHL);	// Konstruktionshilfslinie
	m_pVWnd->Update();		// sofort zeichnen

    return S_OK;

} // BuildRestrictLine


// --------------------------------------------------------------------------------------------
// Bildung einer Konstruktionshilfslinie in Form einer Geraden
bool CRestrictLine::BuildStraightLine (KoOrd lFixX, KoOrd lFixY, double dAngle)
{
Window MWnd(__hWndM);					// TRiAS-Hauptfenster
Dimension dimMWin = MWnd.GetSize();		// Größe (im Point-Format) des Hauptfensters
Point FixPt = BSKoordinaten (lFixX, lFixY);

	// obwohl die Hilfslinie eine Gerade ist, braucht sie zum Zeichnen auf dem Bildschirm zwei
	// Endpunkte (m_EPt1, m_EPt2), welche sich aus der Bildschirmbegrenzung ergeben
	if (Pi/2. != dAngle)
	{
	CoOrd b = dimMWin.Width();		// Breite des TRiAS-Hauptfensters
	CoOrd h = dimMWin.Height();		// Höhe des TRiAS-Hauptfensters
	double dTanAngle = tan (dAngle);

		m_EPt1.X() = 0;
		m_EPt1.Y() = DtoL (-FixPt.X()*dTanAngle + FixPt.Y());

		// evtl. Clipping an der Bildschirmbegrenzung (ist für das Zeichnen der Gerade nicht
		// erforderlich; ich mache es aber trotzdem, damit das Rechteck für UnDraw() nicht
		// unnötig groß wird)
		// für m_EPt1.Y() < 0 || m_EPt1.Y() > h kann eigentlich dTanAngle nicht 0 werden (d.h.
		// eine waagerechte Gerade), sollte der Fall aber unerwartet doch eintreten, mache ich
		// eben kein Clipping (geht ja auch ohne)
		if ((m_EPt1.Y() < 0 || m_EPt1.Y() > h) && dTanAngle != 0)
		{
			(m_EPt1.Y() < 0) ? (m_EPt1.Y() = 0) : (m_EPt1.Y() = h);
			m_EPt1.X() = DtoL ((m_EPt1.Y()-FixPt.Y())/dTanAngle + FixPt.X());
		}

		m_EPt2.X() = b;
		m_EPt2.Y() = DtoL ((b-FixPt.X())*dTanAngle + FixPt.Y());

		if ((m_EPt2.Y() < 0 || m_EPt2.Y() > h) && dTanAngle != 0)
		{
			(m_EPt2.Y() < 0) ? (m_EPt2.Y() = 0) : (m_EPt2.Y() = h);
			m_EPt2.X() = DtoL ((m_EPt2.Y()-FixPt.Y())/dTanAngle + FixPt.X());
		}
	}
	else
	{
		m_EPt1.X() = FixPt.X();
		m_EPt1.Y() = 0;
		m_EPt2.X() = FixPt.X();
		m_EPt2.Y() = dimMWin.Height();
	}

	m_pKHL = new LineObject (m_EPt1, m_EPt2, &m_MyPen1);

	if (! m_pKHL)
    {
    	DEX_Error (RC_RestrictLine, EC_NOMEMORY);
    	return false;
    }
	return true;

} // BuildStraightLine


// --------------------------------------------------------------------------------------------
// Bildung einer Konstruktionshilfslinie in Form eines Kreises
bool CRestrictLine::BuildCircleLine (KoOrd lFixX, KoOrd lFixY, double dLength)
{
Point FixPt = BSKoordinaten (lFixX, lFixY);
Point EPt = BSKoordinaten (lFixX + m_dUFX*dLength, lFixY);

	_ASSERTE (EPt.X() - FixPt.X() > 0); 

	m_iRad = EPt.X() - FixPt.X();	// Radius und

CoOrd d = 2 * m_iRad;	// Durchmesser der kreisförmigen Hilfslinie

	m_RefPt.X() = FixPt.X() - m_iRad;
	m_RefPt.Y() = FixPt.Y() - m_iRad;
	m_pKHL = new EllipseObject (m_RefPt, Dimension(d, d), &m_MyPen1, &m_MyBrush);

	if (! m_pKHL)
    {
    	DEX_Error (RC_RestrictLine, EC_NOMEMORY);
    	return false;
    }
	return true;

} // BuildCircleLine


// --------------------------------------------------------------------------------------------
// Bildung einer Konstruktionshilfslinie in Form einer Strecke
bool CRestrictLine::BuildSegmentLine (KoOrd lFixX, KoOrd lFixY, double dAngle, double dLength)
{
KoOrd lKorr1 = DtoL (m_dUFX * dLength * cos (dAngle));
KoOrd lKorr2 = DtoL (m_dUFY * dLength * sin (dAngle));
KoOrd EPktX = lFixX + lKorr1;
KoOrd EPktY = lFixY + lKorr2;

	m_EPt1 = BSKoordinaten (EPktX, EPktY);

	EPktX = lFixX - lKorr1;
	EPktY = lFixY - lKorr2;
	m_EPt2 = BSKoordinaten (EPktX, EPktY);

	m_pKHL = new LineObject (m_EPt1, m_EPt2, &m_MyPen1);
	if (! m_pKHL)
    {
    	DEX_Error (RC_RestrictLine, EC_NOMEMORY);
    	return false;
    }
	return true;

} // BuildSegmentLine


// --------------------------------------------------------------------------------------------
// gibt die Parameter der this-Hilfslinien zurück
HRESULT CRestrictLine::GetParameters (RestrType* pResType, POINT* pEPT1, POINT* pEPT2,
						POINT* pRefPT, int* piRad, long* plFixX, long* plFixY, double* pdAngle)
{
	*pResType = m_ResType;
	*pEPT1 = (POINT&)m_EPt1;
	*pEPT2 = (POINT&)m_EPt2;
	*pRefPT = (POINT&)m_RefPt;
	*piRad = m_iRad;

	// die nachfolgenden Parameter sind eigentlich redundant; aber (vermtl.) durch
	// Rundungsfehler bei der Berechnung von m_EPt1 und m_EPt2 erscheinen 2 Geraden, die auf
	// der gleichen Bezugslinie mit dem gleichen Anstieg errichtet werden, nicht immer als
	// parallel sondern mit einem (allerdings weit drausen liegenden) Schnittpunkt
	*plFixX = m_lFixX;
	*plFixY = m_lFixY;
	*pdAngle = m_dAngle;

	return S_OK;
}


// --------------------------------------------------------------------------------------------
// den Cursor auf die this-Hilfslinie setzen
HRESULT CRestrictLine::CursorTo1RestrictLine (LPARAM lParam, POINT* pPTCur)
{
Point MSPt = BSPoint (lParam);	// BS-Punkt der Mausspitze

	if (RESTRTYPE_GERADE == m_ResType)
	{
	double dLotPX, dLotPY;

		GeradenLotPunkt (MSPt.X(), MSPt.Y(), m_EPt1.X(), m_EPt1.Y(), m_EPt2.X(), m_EPt2.Y(),
						 dLotPX, dLotPY);
		pPTCur->x = DtoL (dLotPX);
		pPTCur->y = DtoL (dLotPY);
	}

	else if (RESTRTYPE_KREIS == m_ResType)
	{
	// Abstand der Mausposition vom Mittelpunkt der kreisförmigen Hilfslinie
	double dx = MSPt.X() - m_RefPt.X() - m_iRad;
	double dy = MSPt.Y() - m_RefPt.Y() - m_iRad;
	double dAbst = sqrt (dx*dx + dy*dy);

		if (0. == dAbst) return S_FALSE;

		pPTCur->x = m_RefPt.X() + m_iRad + DtoL (m_iRad*dx/dAbst);
		pPTCur->y = m_RefPt.Y() + m_iRad + DtoL (m_iRad*dy/dAbst);
	}

	else if (RESTRTYPE_STRECKE == m_ResType)
	{
	double dLotPX, dLotPY;

		GeradenLotPunkt (MSPt.X(), MSPt.Y(), m_EPt1.X(), m_EPt1.Y(), m_EPt2.X(), m_EPt2.Y(),
						 dLotPX, dLotPY);
		CursorToStraight (MSPt, dLotPX, dLotPY, m_EPt1, m_EPt2, pPTCur);
	}

	return S_OK;

} // CursorTo1RestrictLine


// --------------------------------------------------------------------------------------------
// den Cursor auf einen der gemeinsamen Punkte der this- und der pRestrLine2-Hilfslinie setzen;
// return-Werte sind
//  S_OK:    es ließ sich eine Cursorposition bestimmen
//  S_FALSE: die beiden Hilfslinien sind zu löschen, weil sie sich z. B. nicht oder nur
//           außerhalb des Bildschirm schneiden oder sonst ein Fehler aufgetreten ist
HRESULT CRestrictLine::CursorTo2RestrictLines (LPARAM lParam, IRestrictLine* pRestrLine2,
											   POINT* pPTCur)
{
Point MSPt = BSPoint (lParam);	// BS-Punkt der Mausspitze

RestrType ResType2;		// Parameter der 2. Konstruktionshilfslinie
Point EPt12, EPt22, RefPt2;
int iRad2;
KoOrd lFixX, lFixY;
double dAngle;

	pRestrLine2->GetParameters (&ResType2, (POINT*)&EPt12, (POINT*)&EPt22, (POINT*)&RefPt2,
								&iRad2, &lFixX, &lFixY, &dAngle);

ResString rsCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);

	// dieser Vortest ist eigentlich redundant, aber (vermtl.) durch Rundungsfehler bei der
	// Berechnung von m_EPt1 und m_EPt2 erscheinen 2 Geraden, die auf der gleichen Bezugslinie
	// mit dem gleichen Anstieg errichtet werden, nicht immer als parallel sondern mit einem
	// (allerdings weit drausen liegenden) Schnittpunkt
	if (RESTRTYPE_KREIS != m_ResType && RESTRTYPE_KREIS != ResType2 &&
		m_dAngle == dAngle &&
		(m_lFixX != lFixX || m_lFixY != lFixY))
	{
	ResString rsText (ResID (IDS_NOSECTPOINT, pRF), 250);
    	
    	MessageBox (__hWndM, rsText.Addr(), rsCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
		pPTCur->x = -1;
		pPTCur->y = -1;
		return S_FALSE;
	}

	if (RESTRTYPE_STRECKE == m_ResType && RESTRTYPE_STRECKE == ResType2)
		return CursorToSegmentSegment (MSPt, m_EPt1, m_EPt2, EPt12, EPt22, pPTCur);

	if (RESTRTYPE_STRECKE == m_ResType && RESTRTYPE_GERADE == ResType2)
		return CursorToSegmentStraight (MSPt, m_EPt1, m_EPt2, EPt12, EPt22, pPTCur);

	if (RESTRTYPE_STRECKE == m_ResType && RESTRTYPE_KREIS == ResType2)
	{
	Point MPt2 = BSKoordinaten (lFixX, lFixY);

		return CursorToSegmentCircle (MSPt, m_EPt1, m_EPt2, MPt2, iRad2, pPTCur);
	}

	if (RESTRTYPE_GERADE == m_ResType && RESTRTYPE_STRECKE == ResType2)
		return CursorToSegmentStraight (MSPt, EPt12, EPt22, m_EPt1, m_EPt2, pPTCur);

	if (RESTRTYPE_GERADE == m_ResType && RESTRTYPE_GERADE == ResType2)
		return CursorToStraightStraight (lParam, m_EPt1, m_EPt2, EPt12, EPt22, pPTCur);

	if (RESTRTYPE_GERADE == m_ResType && RESTRTYPE_KREIS == ResType2)
	{
	Point MPt2 = BSKoordinaten (lFixX, lFixY);

		return CursorToStraightCircle (MSPt, m_EPt1, m_EPt2, MPt2, iRad2, pPTCur);
	}

	if (RESTRTYPE_KREIS == m_ResType && RESTRTYPE_STRECKE == ResType2)
	{
	Point MPt1 = BSKoordinaten (m_lFixX, m_lFixY);

		return CursorToSegmentCircle (MSPt, EPt12, EPt22, MPt1, m_iRad, pPTCur);
	}

	if (RESTRTYPE_KREIS == m_ResType && RESTRTYPE_GERADE == ResType2)
	{
	Point MPt1 = BSKoordinaten (m_lFixX, m_lFixY);

		return CursorToStraightCircle (MSPt, EPt12, EPt22, MPt1, m_iRad, pPTCur);
	}

	if (RESTRTYPE_KREIS == m_ResType && RESTRTYPE_KREIS == ResType2)
	{
	Point MPt1 = BSKoordinaten (m_lFixX, m_lFixY);
	Point MPt2 = BSKoordinaten (lFixX, lFixY);

		return CursorToCircleCircle (lParam, MSPt, MPt1, m_iRad, MPt2, iRad2, pPTCur);
	}

	_ASSERTE (false);	// hierhin dürfte keiner mehr kommen
	return E_UNEXPECTED;

} // CursorTo2RestrictLines


// --------------------------------------------------------------------------------------------
// Ermittlung der Cursorposition bei 2 Strecken
HRESULT CRestrictLine::CursorToSegmentSegment (Point MSPt, Point EPt11, Point EPt21,
											   Point EPt12, Point EPt22, POINT* pPTCur)
{
Point SectPt1, SectPt2;
SectScreen ssRet = SegmentSegmentIntersection (EPt11, EPt21, EPt12, EPt22, SectPt1, SectPt2);

	if (INSECT == ssRet)
	{
		*pPTCur = (POINT&)SectPt1;
		return S_OK;
	}

ResString rsCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);

	if (OUTSECT == ssRet)
	{
	ResString rsText (ResID (IDS_OUTSECTPOINT, pRF), 200);
    	
		if (IDYES == MessageBox (__hWndM, rsText.Addr(), rsCapt.Addr(),
								 MB_ICONQUESTION | MB_YESNO))
		{
			ExpandingSreenSection (SectPt1);
			pPTCur->x = 0;	// an dieser Stelle könnte mehr Aufwand getrieben werden, damit die NEUE Position
			pPTCur->y = 0;	// von SectPt nach der Vergrößerung des Sichtausschnittes ermittelt wird !!!!!!!
			return S_OK;
		}
		return S_FALSE;		// IDNO
	}

	if (INFISECT == ssRet)	// beide Strecken haben einen Überlappungsbereich
	{
	double dLotPX, dLotPY;

		GeradenLotPunkt (MSPt.X(), MSPt.Y(), m_EPt1.X(), m_EPt1.Y(), m_EPt2.X(), m_EPt2.Y(),
						 dLotPX, dLotPY);
		CursorToStraight (MSPt, dLotPX, dLotPY, SectPt1, SectPt2, pPTCur);
		return S_OK;
	}

	if (NOSECT == ssRet)
	{
	ResString rsText (ResID (IDS_NOSECTPOINT, pRF), 250);
    	
    	MessageBox (__hWndM, rsText.Addr(), rsCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
		pPTCur->x = -1;
		pPTCur->y = -1;
		return S_FALSE;
	}

	DEX_Error (RC_RestrictLine, EC_NOINTERSECTION);
	return E_FAIL;

} // CursorToSegmentSegment


// --------------------------------------------------------------------------------------------
// Ermittlung der Cursorposition bei 1 Strecke und 1 Gerade
HRESULT CRestrictLine::CursorToSegmentStraight (Point MSPt, Point EPt11, Point EPt21,
												Point EPt12, Point EPt22, POINT* pPTCur)
{
Point SectPt1, SectPt2;
SectScreen ssRet = SegmentStraightIntersection (EPt11, EPt21, EPt12, EPt22, SectPt1,
												SectPt2);

	if (INSECT == ssRet)
	{
		*pPTCur = (POINT&)SectPt1;
		return S_OK;
	}

ResString rsCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);

	if (OUTSECT == ssRet)
	{
	ResString rsText (ResID (IDS_OUTSECTPOINT, pRF), 200);
    	
		if (IDYES == MessageBox (__hWndM, rsText.Addr(), rsCapt.Addr(),
								 MB_ICONQUESTION | MB_YESNO))
		{
			ExpandingSreenSection (SectPt1);
			pPTCur->x = 0;	// an dieser Stelle könnte mehr Aufwand getrieben werden, damit die NEUE Position
			pPTCur->y = 0;	// von SectPt nach der Vergrößerung des Sichtausschnittes ermittelt wird !!!!!!!
			return S_OK;
		}
		return S_FALSE;		// IDNO
	}

	if (INFISECT == ssRet)	// Strecke liegt vollständig auf der Geraden
	{
	double dLotPX, dLotPY;

		GeradenLotPunkt (MSPt.X(), MSPt.Y(), m_EPt1.X(), m_EPt1.Y(), m_EPt2.X(), m_EPt2.Y(),
						 dLotPX, dLotPY);
		CursorToStraight (MSPt, dLotPX, dLotPY, SectPt1, SectPt2, pPTCur);
		return S_OK;
	}

	if (NOSECT == ssRet)
	{
	ResString rsText (ResID (IDS_NOSECTPOINT, pRF), 250);
    	
    	MessageBox (__hWndM, rsText.Addr(), rsCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
		pPTCur->x = -1;
		pPTCur->y = -1;
		return S_FALSE;
	}

	DEX_Error (RC_RestrictLine, EC_NOINTERSECTION);
	return E_FAIL;

} // CursorToSegmentStraight


// --------------------------------------------------------------------------------------------
// Ermittlung der Cursorposition bei 1 Strecke und 1 Kreis
HRESULT CRestrictLine::CursorToSegmentCircle (Point MSPt, Point EPt1, Point EPt2, Point MPt,
											  int iRad, POINT* pPTCur)
{
bool bTwice;	// 2 Schnittpunkte (true) bzw. 1 Berührungspunkt (false)
Point SectPt1, SectPt2;
SectScreen ssRet = SegmentCircleIntersection (EPt1, EPt2, MPt, iRad, bTwice, SectPt1, SectPt2);

	if (INSECT == ssRet)
	{
		if (bTwice)
			CursorToNearbyPoint (MSPt, SectPt1, SectPt2, pPTCur);
		else
			*pPTCur = (POINT&)SectPt1;
		return S_OK;
	}

ResString rsCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);

	if (OUTSECT == ssRet)
	{
	ResString rsText (ResID (IDS_OUTSECTPOINT, pRF), 200);
    	
		if (IDYES == MessageBox (__hWndM, rsText.Addr(), rsCapt.Addr(),
								 MB_ICONQUESTION | MB_YESNO))
		{
			if (bTwice)
				ExpandingSreenSection (SectPt1, SectPt2);
			else
				ExpandingSreenSection (SectPt1);
			pPTCur->x = 0;	// an dieser Stelle könnte mehr Aufwand getrieben werden, damit die NEUE Position
			pPTCur->y = 0;	// von SectPt nach der Vergrößerung des Sichtausschnittes ermittelt wird !!!!!!!
			return S_OK;
		}
		return S_FALSE;		// IDNO
	}

	if (INOUTSECT == ssRet)
	{
	ResString rsText (ResID (IDS_OUTSECTPOINT, pRF), 200);
    	
		if (IDYES == MessageBox (__hWndM, rsText.Addr(), rsCapt.Addr(),
								 MB_ICONQUESTION | MB_YESNO))
		{
			ExpandingSreenSection (SectPt1, SectPt2);
			CursorToNearbyPoint (MSPt, SectPt1, SectPt2, pPTCur);
			return S_OK;
		}

		CursorToNearbyPoint (MSPt, SectPt1, SectPt2, pPTCur);
		return S_FALSE;		// IDNO
	}

	if (NOSECT == ssRet)
	{
	ResString rsText (ResID (IDS_NOSECTPOINT, pRF), 250);
    	
    	MessageBox (__hWndM, rsText.Addr(), rsCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
		pPTCur->x = -1;
		pPTCur->y = -1;
		return S_FALSE;
	}

	DEX_Error (RC_RestrictLine, EC_NOINTERSECTION);
	return E_FAIL;

} // CursorToSegmentCircle


// --------------------------------------------------------------------------------------------
// Ermittlung der Cursorposition bei 2 Geraden
HRESULT CRestrictLine::CursorToStraightStraight (LPARAM lParam, Point EPt11, Point EPt21,
												 Point EPt12, Point EPt22, POINT* pPTCur)
{
Point SectPt;
SectScreen ssRet = StraightStraightIntersection (EPt11, EPt21, EPt12, EPt22, SectPt);

	if (INSECT == ssRet)
	{
		*pPTCur = (POINT&)SectPt;
		return S_OK;
	}

ResString rsCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);

	if (OUTSECT == ssRet)
	{
	ResString rsText (ResID (IDS_OUTSECTPOINT, pRF), 200);
    	
		if (IDYES == MessageBox (__hWndM, rsText.Addr(), rsCapt.Addr(),
								MB_ICONQUESTION | MB_YESNO))
		{
			ExpandingSreenSection (SectPt);
			pPTCur->x = 0;	// an dieser Stelle könnte mehr Aufwand getrieben werden, damit die NEUE Position
			pPTCur->y = 0;	// von SectPt nach der Vergrößerung des Sichtausschnittes ermittelt wird !!!!!!!
			return S_OK;
		}
		return S_FALSE;		// IDNO
	}

	if (INFISECT == ssRet)	// beide Geraden sind deckungsgleich
		return CursorTo1RestrictLine (lParam, pPTCur);

	if (NOSECT == ssRet)
	{
	ResString rsText (ResID (IDS_NOSECTPOINT, pRF), 250);
    	
    	MessageBox (__hWndM, rsText.Addr(), rsCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
		pPTCur->x = -1;
		pPTCur->y = -1;
		return S_FALSE;
	}

	DEX_Error (RC_RestrictLine, EC_NOINTERSECTION);
	return E_FAIL;

} // CursorToStraightStraight

// --------------------------------------------------------------------------------------------
// Ermittlung der Cursorposition bei 1 Geraden und 1 Kreis
HRESULT CRestrictLine::CursorToStraightCircle (Point MSPt, Point EPt1, Point EPt2, Point MPt,
											   int iRad, POINT* pPTCur)
{
bool bTwice;	// 2 Schnittpunkte (true) bzw. 1 Berührungspunkt (false)
Point SectPt1, SectPt2;
SectScreen ssRet = StraightCircleIntersection (EPt1, EPt2, MPt, iRad, bTwice, SectPt1, SectPt2);

	if (INSECT == ssRet)
	{
		if (bTwice)
			CursorToNearbyPoint (MSPt, SectPt1, SectPt2, pPTCur);
		else
			*pPTCur = (POINT&)SectPt1;
		return S_OK;
	}

ResString rsCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);

	if (OUTSECT == ssRet)
	{
	ResString rsText (ResID (IDS_OUTSECTPOINT, pRF), 200);
    	
		if (IDYES == MessageBox (__hWndM, rsText.Addr(), rsCapt.Addr(),
								 MB_ICONQUESTION | MB_YESNO))
		{
			if (bTwice)
				ExpandingSreenSection (SectPt1, SectPt2);
			else
				ExpandingSreenSection (SectPt1);
			pPTCur->x = 0;	// an dieser Stelle könnte mehr Aufwand getrieben werden, damit die NEUE Position
			pPTCur->y = 0;	// von SectPt nach der Vergrößerung des Sichtausschnittes ermittelt wird !!!!!!!
			return S_OK;
		}
		return S_FALSE;		// IDNO
	}

	if (INOUTSECT == ssRet)
	{
	ResString rsText (ResID (IDS_OUTSECTPOINT, pRF), 200);
    	
		if (IDYES == MessageBox (__hWndM, rsText.Addr(), rsCapt.Addr(),
								 MB_ICONQUESTION | MB_YESNO))
		{
			ExpandingSreenSection (SectPt1, SectPt2);
			CursorToNearbyPoint (MSPt, SectPt1, SectPt2, pPTCur);
			return S_OK;
		}

		CursorToNearbyPoint (MSPt, SectPt1, SectPt2, pPTCur);
		return S_FALSE;		// IDNO
	}

	if (NOSECT == ssRet)
	{
	ResString rsText (ResID (IDS_NOSECTPOINT, pRF), 250);
    	
    	MessageBox (__hWndM, rsText.Addr(), rsCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
		pPTCur->x = -1;
		pPTCur->y = -1;
		return S_FALSE;
	}

	DEX_Error (RC_RestrictLine, EC_NOINTERSECTION);
	return E_FAIL;

} // CursorToStraightCircle


// --------------------------------------------------------------------------------------------
// Ermittlung der Cursorposition bei 2 Kreisen
HRESULT CRestrictLine::CursorToCircleCircle (LPARAM lParam, Point MSPt, Point MPt1, int iRad1,
											 Point MPt2, int iRad2, POINT* pPTCur)
{
bool bTwice;	// 2 Schnittpunkte (true) bzw. 1 Berührungspunkt (false)
Point SectPt1, SectPt2;
SectScreen ssRet = CircleCircleIntersection (MPt1, iRad1, MPt2, iRad2, bTwice, SectPt1,
											 SectPt2);

	if (INSECT == ssRet)
	{
		if (bTwice)
			CursorToNearbyPoint (MSPt, SectPt1, SectPt2, pPTCur);
		else
			*pPTCur = (POINT&)SectPt1;
		return S_OK;
	}

ResString rsCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);

	if (OUTSECT == ssRet)
	{
	ResString rsText (ResID (IDS_OUTSECTPOINT, pRF), 200);
    	
		if (IDYES == MessageBox (__hWndM, rsText.Addr(), rsCapt.Addr(),
								 MB_ICONQUESTION | MB_YESNO))
		{
			if (bTwice)
				ExpandingSreenSection (SectPt1, SectPt2);
			else
				ExpandingSreenSection (SectPt1);
			pPTCur->x = 0;	// an dieser Stelle könnte mehr Aufwand getrieben werden, damit die NEUE Position
			pPTCur->y = 0;	// von SectPt nach der Vergrößerung des Sichtausschnittes ermittelt wird !!!!!!!
			return S_OK;
		}
		return S_FALSE;		// IDNO
	}

	if (INOUTSECT == ssRet)
	{
	ResString rsText (ResID (IDS_OUTSECTPOINT, pRF), 200);
    	
		if (IDYES == MessageBox (__hWndM, rsText.Addr(), rsCapt.Addr(),
								 MB_ICONQUESTION | MB_YESNO))
		{
			ExpandingSreenSection (SectPt1, SectPt2);
			CursorToNearbyPoint (MSPt, SectPt1, SectPt2, pPTCur);
			return S_OK;
		}

		CursorToNearbyPoint (MSPt, SectPt1, SectPt2, pPTCur);
		return S_FALSE;		// IDNO
	}

	if (INFISECT == ssRet)	// beide Kreise sind deckungsgleich
		return CursorTo1RestrictLine (lParam, pPTCur);

	if (NOSECT == ssRet)
	{
	ResString rsText (ResID (IDS_NOSECTPOINT, pRF), 250);
    	
    	MessageBox (__hWndM, rsText.Addr(), rsCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
		pPTCur->x = -1;
		pPTCur->y = -1;
		return S_FALSE;
	}

	DEX_Error (RC_RestrictLine, EC_NOINTERSECTION);
	return E_FAIL;

} // CursorToCircleCircle


// --------------------------------------------------------------------------------------------
// Cursor auf eine Strecke ziehen
void CRestrictLine::CursorToStraight (Point MSPt, double dLotPX, double dLotPY, Point EPt1,
									  Point EPt2, POINT* pPTCur)
{
CoOrd MinX = min (EPt1.X(), EPt2.X());
CoOrd MinY = min (EPt1.Y(), EPt2.Y());
CoOrd MaxX = max (EPt1.X(), EPt2.X());
CoOrd MaxY = max (EPt1.Y(), EPt2.Y());

bool b1 = (EPt1.X() == EPt2.X() &&			// senkrechte Strecke
		   MinY <= dLotPY && dLotPY <= MaxY);
bool b2 = (EPt1.Y() == EPt2.Y() &&			// waagrechte Strecke
		   MinX <= dLotPX && dLotPX <= MaxX);
bool b3 = (MinX <= dLotPX && dLotPX <= MaxX &&	// Normalfall (schräge Strecke)
		   MinY <= dLotPY && dLotPY <= MaxY);

	// Lotpunkt und damit Cursor INNERHALB der Strecke
	if (b1 || b2 || b3)
	{
		pPTCur->x = DtoL (dLotPX);
		pPTCur->y = DtoL (dLotPY);
	}
	// Lotpunkt AUßERHALB der Strecke; Cursor wird auf einen der beiden Streckenendpunkte
	// gesetzt
	else
		CursorToNearbyPoint (MSPt, EPt1, EPt2, pPTCur);

} // CursorToStraight


// --------------------------------------------------------------------------------------------
// Cursor auf den nähergelegenen der beiden Punkt Pt1 bzw. Pt2 ziehen
void CRestrictLine::CursorToNearbyPoint (Point MSPt, Point Pt1, Point Pt2, POINT* pPTCur)
{
double dx1 = MSPt.X() - Pt1.X();
double dy1 = MSPt.Y() - Pt1.Y();
double dx2 = MSPt.X() - Pt2.X();
double dy2 = MSPt.Y() - Pt2.Y();

	if (dx1*dx1+dy1*dy1 <= dx2*dx2+dy2*dy2)
	{
		pPTCur->x = Pt1.X();
		pPTCur->y = Pt1.Y();
	}
	else
	{
		pPTCur->x = Pt2.X();
		pPTCur->y = Pt2.Y();
	}
}


// --------------------------------------------------------------------------------------------
// Bildausschnitt vergrößern, so daß die BS-Punkte ExtPt1 und ExtPt2 mit enthalten sind
void CRestrictLine::ExpandingSreenSection (Point ExtPt1, Point ExtPt2)
{
Rectangle rcOldView = m_pVWnd->CanvasRect();	// derzeiteiges TRiAS-ViewFenster
Rectangle rcNewView;							// neues vergrößertes TRiAS-ViewFenster
CoOrd MinX = min (ExtPt1.X(), ExtPt2.X());
CoOrd MaxX = max (ExtPt1.X(), ExtPt2.X());
CoOrd MinY = min (ExtPt1.Y(), ExtPt2.Y());
CoOrd MaxY = max (ExtPt1.Y(), ExtPt2.Y());

	// Faktor 1.1 ist eine Zugabe, damit ExtPt1 bzw. ExtPt2 im neuen Bildausschnitt nicht genau
	// auf dem Rand sitzt
	if (MinY < rcOldView.Bottom()) rcNewView.Bottom() = 1.1 * MinY;
	else rcNewView.Bottom() = rcOldView.Bottom();

	if (MaxY > rcOldView.Top()) rcNewView.Top() = 1.1 * MaxY;
	else rcNewView.Top() = rcOldView.Top();

	if (MinX < rcOldView.Left()) rcNewView.Left() = 1.1 * MinX;
	else rcNewView.Left() = rcOldView.Left();

	if (MaxX > rcOldView.Right()) rcNewView.Right() = 1.1 * MaxX;
	else rcNewView.Right() = rcOldView.Right();

EPunkt PLU = DBKoordinaten (Point(rcNewView.Left(),rcNewView.Bottom()));
EPunkt PRO = DBKoordinaten (Point(rcNewView.Right(),rcNewView.Top()));
KoOrd lCO[4];	// Koordinaten des neuen Sichtausschnittes (lCO[0] = xmin, lCO[1] = xmax,
				// lCO[2] = ymin, lCO[3] = ymax)

	lCO[0] = PLU.X();
	lCO[1] = PRO.X();
	lCO[2] = PLU.Y();
	lCO[3] = PRO.Y();
	DEX_SetActiveSightContainer (lCO);
	DEX_RePaintRectWait (rcNewView);
	m_pVWnd->Update();

} // ExpandingSreenSection


// --------------------------------------------------------------------------------------------
// Konstruktionshilfslinie auf dem Bildschirm zeichnen
HRESULT CRestrictLine::Draw (void)
{
	if (m_bUnDraw) return S_FALSE;

	BuildRestrictLine (m_lFixX, m_lFixY, m_ResType, m_dAngle, m_dLength, m_dUFX, m_dUFY);
	m_pVWnd->Draw (m_pKHL);	// Konstruktionshilfslinie zeichnen
	m_pVWnd->Update();		// sofort zeichnen

	return S_OK;

} // Draw


// --------------------------------------------------------------------------------------------
// Konstruktionshilfslinie auf dem Bildschirm löschen
HRESULT CRestrictLine::UnDraw (void)
{
HRESULT hrRet = S_OK;
Rectangle rcUnDraw;	// Rechteck der zu löschenden Konstruktionshilfslinie

	if (RESTRTYPE_GERADE == m_ResType || RESTRTYPE_STRECKE == m_ResType)
	{
		rcUnDraw.Left() = min (m_EPt1.X(), m_EPt2.X()) - iZug;
		rcUnDraw.Right() = max (m_EPt1.X(), m_EPt2.X()) + iZug;
		rcUnDraw.Top() = max (m_EPt1.Y(), m_EPt2.Y()) + iZug;
		rcUnDraw.Bottom() = min (m_EPt1.Y(), m_EPt2.Y()) - iZug;
	}
	else if (RESTRTYPE_KREIS == m_ResType)
	{
		rcUnDraw.Left() = m_RefPt.X() - iZug;
		rcUnDraw.Right() = m_RefPt.X() + 2*m_iRad + iZug;
		rcUnDraw.Top() = m_RefPt.Y() + 2*m_iRad + iZug;
		rcUnDraw.Bottom() = m_RefPt.Y() - iZug;
	}
	else
	{
		if (RESTRTYPE_UNKNOWN != m_ResType)
			_ASSERTE (m_ResType == RESTRTYPE_GERADE || m_ResType == RESTRTYPE_KREIS ||
					   m_ResType == RESTRTYPE_STRECKE || m_ResType == RESTRTYPE_UNKNOWN);

	Window MWnd(__hWndM);					// TRiAS-Hauptfenster
	Dimension dimMWin = MWnd.GetSize();		// Größe (im Point-Format) des Hauptfensters

		rcUnDraw.Left() = 0;
		rcUnDraw.Right() = dimMWin.Width();
		rcUnDraw.Top() = dimMWin.Height();
		rcUnDraw.Bottom() = 0;

		hrRet = E_UNEXPECTED;
	}
	
	m_bUnDraw = true;	// Konstruktionshilfslinie wird auf dem Bildschirm gelöscht
	DEX_RePaintRectWait (rcUnDraw);
	m_pVWnd->Update();

	return hrRet;

} // UnDraw
