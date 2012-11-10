// Dialogfenster zur Einstellung eines neuen Bildausschnittes -----------------
// File: AUSSCHN.CXX

#include "triaspre.hxx"

#include <dblpair.hxx>

#include "ausschn.hxx"

long myatol (const char *lpStr);

// Konstruktor/Destruktor -----------------------------------------------------
#pragma warning (disable:4355)

CAusschnittsDlg :: CAusschnittsDlg (pWindow pParent, CoordTrans *pCTF,
				    Dimension DotsPerMM)
		 : DialogWindow (pParent, ResID (AUSSCHNITTDLG)),
	// allgemeine Member
		  m_pbOK (this, IDOK),
		  m_pbCancel (this, IDCANCEL),
#if !defined(WIN32)
		  m_pbHelp (this, IDB_AUSSCHNITTHELP),
#endif // WIN32
	// Member für Ausschnittseingabe
		  m_rbAusschnitt (this, IDR_AUSSCHNITT),
		  m_dneObenHochWert (this, IDE_OBENHOCHWERT),
		  m_dneObenRechtsWert (this, IDE_OBENRECHTSWERT),
		  m_dneUntenHochWert (this, IDE_UNTENHOCHWERT),
		  m_dneUntenRechtsWert (this, IDE_UNTENRECHTSWERT),
		  
	// Member für Masstabseingabe
		  m_rbMasstab (this, IDR_MASSTAB),
		  m_cbMasstab (this, IDC_NEWMASSTAB),
		  m_dneMittelHochWert  (this, IDE_MITTELHOCHWERT),
		  m_dneMittelRechtsWert (this, IDE_MITTELRECHTSWERT),

		  m_dimDotsPerMM (DotsPerMM),		  
		  m_pCT (pCTF)
{
// RechtecksPointer erstmal initialisieren
	m_pOC = NULL;

// NumEdits initialisieren
	m_dneObenHochWert.SetNumEditMode (NumEdit :: NEM_NoTest);
	m_dneObenRechtsWert.SetNumEditMode (NumEdit :: NEM_NoTest);
	m_dneUntenHochWert.SetNumEditMode (NumEdit :: NEM_NoTest);
	m_dneUntenRechtsWert.SetNumEditMode (NumEdit :: NEM_NoTest);

	m_dneMittelHochWert.SetNumEditMode (NumEdit :: NEM_NoTest);
	m_dneMittelRechtsWert.SetNumEditMode (NumEdit :: NEM_NoTest);

// MaßstabsComboBox füllen
	for (short i = 0; i < CNT_MASSTAB; i++) 
		m_cbMasstab.AddString (ResString (IDS_MASSTAB250+i, 10));

// Hilfe erstmal passivieren
#if !defined(WIN32)
	m_pbHelp.Disable();
#endif // WIN32

	m_pInBuff = NULL;
	m_pInBuffY = NULL;
}

#pragma warning (default:4355)

bool CAusschnittsDlg :: Init (Rectangle *pRc)
{
// EingabePuffer initialisieren
	m_pInBuff = new char [INBUFFLEN+1];
	if (m_pInBuff == NULL) {
		db_error (EC_NOMEMORY, RC_ctAusschnittsDlg);
		return false;
	}
	m_pInBuffY = new char [INBUFFLEN+1];
	if (m_pInBuffY == NULL) {
		db_error (EC_NOMEMORY, RC_ctAusschnittsDlg);
		return false;
	}
	
// Rechteck initialisieren
bool fToDelete = false;

	if (pRc == NULL) {
		pRc = new Rectangle (0, 0, 0, 0);
		if (pRc == NULL) {
			db_error (EC_NOMEMORY, RC_ctAusschnittsDlg);
			return false;
		}
		*pRc = GetParent() -> CanvasRect();
		fToDelete = true;
	} else {
	// Koordinaten kippen
	CoOrd tmpC = CoOrd(pRc -> Bottom() - pRc -> Top());
	
		pRc -> Bottom() = CoOrd(pRc -> Top() - tmpC);
	}
		
	{
	// Koordinaten in DB-Koordinaten umsetzen
	Punkt PtMin = DCtoOC (pRc -> Left(), pRc -> Bottom());       // Device --> Objekt
	Punkt PtMax = DCtoOC (pRc -> Right(), pRc -> Top());
	double dXMin, dXMax, dYMin, dYMax;
		
	// Koordinaten transformieren (incl. rausrechnen der internen Skalierung)
		pCT() -> UnScale (PtMin, &dXMin, &dYMin);
		pCT() -> UnScale (PtMax, &dXMax, &dYMax);

	// MittelpunktsKoordinaten berechnen
	DoublePair DP1 (dXMin, dYMax);
	DoublePair DP2 (dXMax, dYMax);
	DoublePair DP3 (dXMin, dYMin);
	double dXDelta = 0.0;
	double dYDelta = 0.0;

		if (pCT() -> hasDistEx()) {
		DoublePair DP4 (dXMax, dYMin);

			pCT() -> CoordTransDistanceEx (&DP1, &DP4, dXDelta, dYDelta);
		} else {
			dXDelta = pCT() -> CoordTransDistance (&DP1, &DP2);
			dYDelta = pCT() -> CoordTransDistance (&DP1, &DP3);
		}

		DP1 = DoublePair (dXMin, dYMin);
		DP2 = DoublePair (dXDelta/2, dYDelta/2);
		pCT() -> CoordTransRectangle (&DP1, &DP2, &DP3);

	double dXCentre = DP3.Width();
	double dYCentre = DP3.Height();

#if defined(WIN32)
	LPVOID pData = NULL;

//		pCT() -> GetTransformParam (dXMin, dYMin, &pData);
		pCT() -> TransformEx (&dXMin, &dYMin, pData);
		pCT() -> TransformEx (&dXMax, &dYMax, pData);
#else
		pCT() -> Transform (&dXMin, &dYMin);
		pCT() -> Transform (&dXMax, &dYMax);
#endif // WIN32

	// ObjektContainer aufbauen
		m_pOC = new ObjContainer (PtMin, PtMax);
		if (m_pOC == NULL) {
			if (fToDelete) DELETE(pRc);
			db_error (EC_NOMEMORY, RC_ctAusschnittsDlg);
			return false;
		}

	// Anfangswerte in Controls schreiben
//		if (!fToDelete) {
			pCT() -> CoordTransToStringEx (dXMax, dYMax, false, m_pInBuff, INBUFFLEN);
			m_dneObenHochWert.SetText (m_pInBuff);
			pCT() -> CoordTransToStringEx (dXMin, dYMin, true, m_pInBuff, INBUFFLEN);
			m_dneObenRechtsWert.SetText (m_pInBuff);
			pCT() -> CoordTransToStringEx (dXMin, dYMin, false, m_pInBuff, INBUFFLEN);
			m_dneUntenHochWert.SetText (m_pInBuff);
			pCT() -> CoordTransToStringEx (dXMax, dYMax, true, m_pInBuff, INBUFFLEN);
			m_dneUntenRechtsWert.SetText (m_pInBuff);
//		}
		
#if defined(WIN32)
		pCT() -> TransformEx (&dXCentre, &dYCentre, pData);
		if (NULL != pData) CoTaskMemFree (pData);
#else
		pCT() -> Transform (&dXCentre, &dYCentre);
#endif // WIN32

		pCT() -> CoordTransToStringEx (dXCentre, dYCentre, true, m_pInBuff, INBUFFLEN);
		m_dneMittelRechtsWert.SetText (m_pInBuff);
		pCT() -> CoordTransToStringEx (dXCentre, dYCentre, false, m_pInBuff, INBUFFLEN);
		m_dneMittelHochWert.SetText (m_pInBuff);
		
		EvalMasstab (!fToDelete);	// berechnen des aktuellen Maßstabes
	}

// MasstabsAuswahl aktivieren
	SetStateMasstab();

	if (fToDelete) DELETE(pRc);
	
return true;
}

CAusschnittsDlg :: ~CAusschnittsDlg (void) 
{
	DELETE (m_pOC);
	DELETE (m_pInBuff);
	DELETE (m_pInBuffY);
}

inline void CondSwap (KoOrd &rlXMin, KoOrd &rlXMax)
{
	if (rlXMin > rlXMax) {
	KoOrd temp = rlXMax;

		rlXMax = rlXMin;
		rlXMin = temp;
	}
}

void CAusschnittsDlg :: ButtonClick (ControlEvt e) 
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		{	
		// Eingabewerte holen
		double dXMin, dXMax, dYMin, dYMax;
		
			if (!GetValue (m_dneObenRechtsWert, dXMin, m_dneObenHochWert, dYMax) ||
			    !GetValue (m_dneUntenRechtsWert, dXMax, m_dneUntenHochWert, dYMin))
			{
			// einer der Numedits hat keine Eingabe
				EndDlg();	// abbrechen
				break;
			}

		// Werte aus  NumEdits einlesen und konvertieren
#if defined(WIN32)
		LPVOID pData = NULL;

//			pCT() -> GetInvTransformParam (dXMin, dYMin, &pData);
			pCT() -> InvTransformEx (&dXMin, &dYMin, pData);
			pCT() -> InvTransformEx (&dXMax, &dYMax, pData);
			if (NULL != pData) CoTaskMemFree (pData);
#else
			pCT() -> InvTransform (&dXMin, &dYMin);
			pCT() -> InvTransform (&dXMax, &dYMax);
#endif // WIN32

			pCT() -> Scale (dXMin, dYMin, &m_pOC -> XMin(), &m_pOC -> YMin());
			pCT() -> Scale (dXMax, dYMax, &m_pOC -> XMax(), &m_pOC -> YMax());

		// Korrektur des neues Ausschnittes (kippen)
			CondSwap (m_pOC -> XMin(), m_pOC -> XMax());
			CondSwap (m_pOC -> YMin(), m_pOC -> YMax());
		}
		EndDlg (1);
		break;

	case IDCANCEL:
		EndDlg ();
		break;

	case IDR_MASSTAB:
		SetStateMasstab();
		break;
		
	case IDR_AUSSCHNITT:
		SetStateAusschnitt();
		break;
		
	case IDB_AUSSCHNITTHELP:
		break;
	}
}


// EditControl hat Focus verloren ---------------------------------------------
void CAusschnittsDlg :: EditFocusChg (EditFocusChgEvt e)
{
	if (e.gotFocus()) {
		switch ((uint)e.GetControlID()) {
		case IDE_OBENHOCHWERT:
		case IDE_OBENRECHTSWERT:
		case IDE_UNTENHOCHWERT:
		case IDE_UNTENRECHTSWERT:
			SetStateAusschnitt();
			break;
		
		case IDC_NEWMASSTAB:
		case IDE_MITTELHOCHWERT:
		case IDE_MITTELRECHTSWERT:
			SetStateMasstab();
			break;
		}
	} else {
		switch ((uint)e.GetControlID()) {
		case IDE_OBENHOCHWERT:
		case IDE_OBENRECHTSWERT:
		case IDE_UNTENHOCHWERT:
		case IDE_UNTENRECHTSWERT:
			EvalMasstab();
			break;
		
		case IDC_NEWMASSTAB:
		case IDE_MITTELHOCHWERT:
		case IDE_MITTELRECHTSWERT:
			EvalCoords();
			break;
		}
	}
}


// Maßstabsauswahl aus ComboBox -----------------------------------------------
void CAusschnittsDlg :: ListBoxSel (ControlEvt)
{
	EvalCoords();
}


// Umschalten zwischen den beiden EingabeModi ---------------------------------
void CAusschnittsDlg :: SetStateMasstab (void)
{
// RadioButtons setzen
	m_rbMasstab.SetState (true);
	m_rbAusschnitt.SetState (false);
}


void CAusschnittsDlg :: SetStateAusschnitt (void)
{
// RadioButtons setzen
	m_rbMasstab.SetState (false);
	m_rbAusschnitt.SetState (true);
}


// Berechnen der Eckkoordinaten und des Maßstabes des Bildausschnitts --------
bool CAusschnittsDlg :: EvalCoords (void) 
{
// MittelPunktsKoordinate holen
double lx, ly;

	if (!GetValue (m_dneMittelRechtsWert, lx, m_dneMittelHochWert, ly))
	{
		return false;
	}
	pCT() -> InvTransform (&lx, &ly);

short iIndex = short(m_cbMasstab.GetCurrentIndex());
long lMasstab = 0L;

	if (iIndex == -1) {	// nutzerdefinierter Maßstab
		m_cbMasstab.GetText (m_pInBuff, INBUFFLEN);
		lMasstab = myatol (m_pInBuff);
	} else 			// vorgebener Maßstab
		lMasstab = GetMasstab (iIndex);

	if (lMasstab == 0L) {		// Blödsinn abfangen
		MessageBeep (MB_ICONEXCLAMATION);
		ltoa (m_lMasstab, m_pInBuff, 10);
		m_cbMasstab.SetText (m_pInBuff);
		m_cbMasstab.SetFocus();
		return false;
	}

	m_lMasstab = lMasstab;			// Maßstab merken
	
// Größe des FensterAusschnittes besorgen
Rectangle CRc = GetParent() -> CanvasRect();
CoOrd iSizeX = CoOrd(CRc.Right()-CRc.Left());		// FensterGröße als Bezug
CoOrd iSizeY = CoOrd(CRc.Top()-CRc.Bottom());
// halbe Größe des Ausschnitts
DoublePair mDelta (-((double)lMasstab * iSizeX)/(m_dimDotsPerMM.Width()*2000.0),
		   ((double)lMasstab * iSizeY)/(m_dimDotsPerMM.Height()*2000.0));
DoublePair PIn (lx, ly);
DoublePair PLiO, PReU;

// linke obere Ecke berechnen
	pCT() -> CoordTransRectangle (&PIn, &mDelta, &PLiO);
// rechte untere Ecke berechnen
DoublePair Delta (((double)lMasstab * iSizeX)/(m_dimDotsPerMM.Width()*1000.0),
		  -((double)lMasstab * iSizeY)/(m_dimDotsPerMM.Height()*1000.0));

	pCT() -> CoordTransRectangle (&PLiO, &Delta, &PReU);

#if defined(WIN32)
LPVOID pData = NULL;

//	pCT() -> GetTransformParam (PIn.X(), PIn.Y(), &pData);
	pCT() -> TransformEx (&PLiO, 1, pData);			// zurückschreiben
	pCT() -> CoordTransToStringEx (PLiO.X(), PLiO.Y(), true, m_pInBuff, INBUFFLEN);
	m_dneObenRechtsWert.SetText (m_pInBuff);
	pCT() -> CoordTransToStringEx (PLiO.X(), PLiO.Y(), false, m_pInBuff, INBUFFLEN);
	m_dneObenHochWert.SetText (m_pInBuff);
	
	pCT() -> TransformEx (&PReU, 1, pData);			// zurückschreiben
	pCT() -> CoordTransToStringEx (PReU.X(), PReU.Y(), true, m_pInBuff, INBUFFLEN);
	m_dneUntenRechtsWert.SetText (m_pInBuff);
	pCT() -> CoordTransToStringEx (PReU.X(), PReU.Y(), false, m_pInBuff, INBUFFLEN);
	m_dneUntenHochWert.SetText (m_pInBuff);

	if (NULL != pData) CoTaskMemFree (pData);
#else
	pCT() -> Transform (&PLiO, 1);			// zurückschreiben
	pCT() -> CoordTransToStringEx (PLiO.X(), PLiO.Y(), true, m_pInBuff, INBUFFLEN);
	m_dneObenRechtsWert.SetText (m_pInBuff);
	pCT() -> CoordTransToStringEx (PLiO.X(), PLiO.Y(), false, m_pInBuff, INBUFFLEN);
	m_dneObenHochWert.SetText (m_pInBuff);
	
	pCT() -> Transform (&PReU, 1);			// zurückschreiben
	pCT() -> CoordTransToStringEx (PReU.X(), PReU.Y(), true, m_pInBuff, INBUFFLEN);
	m_dneUntenRechtsWert.SetText (m_pInBuff);
	pCT() -> CoordTransToStringEx (PReU.X(), PReU.Y(), false, m_pInBuff, INBUFFLEN);
	m_dneUntenHochWert.SetText (m_pInBuff);
#endif // WIN32

return true;
}


// Masstab nachführen, wenn rechte untere Koordinate verändert wird -----------
bool CAusschnittsDlg :: EvalMasstab (bool /*fShow*/)
{
// Seitenverhältnis von Bild und Bildausschnitt berechnen
double lx, ly, rx, ry;

	if (!GetValue (m_dneObenRechtsWert, lx, m_dneObenHochWert, ly) ||
	    !GetValue (m_dneUntenRechtsWert, rx, m_dneUntenHochWert, ry))
	{
		return false;
	}

#if defined(WIN32)
LPVOID pData = NULL;

//	pCT() -> GetInvTransformParam (lx, ly, &pData);
	pCT() -> InvTransformEx (&lx, &ly, pData);
	pCT() -> InvTransformEx (&rx, &ry, pData);
	if (NULL != pData) CoTaskMemFree (pData);
#else
	pCT() -> InvTransform (&lx, &ly);
	pCT() -> InvTransform (&rx, &ry);
#endif // WIN32

DoublePair LO (lx, ly);
double dX = 0.0;
double dY = 0.0;

	if (pCT() -> hasDistEx()) {
	DoublePair RU (rx, ry);

		pCT() -> CoordTransDistanceEx (&LO, &RU, dX, dY);
	} else {
	DoublePair RO (rx, ly);
	DoublePair LU (lx, ry);

		dX = pCT() -> CoordTransDistance (&LO, &RO);
		dY = pCT() -> CoordTransDistance (&LO, &LU);
	}

double kBild = dX != 0.0 ? fabs (dY / dX) : 1.0;
Rectangle CRc = GetParent() -> CanvasRect();
CoOrd iSizeX = CoOrd(CRc.Right()-CRc.Left());		// FensterGröße als Bezug
CoOrd iSizeY = CoOrd(CRc.Top()-CRc.Bottom());
double kBAus = iSizeX != 0 ? fabs (double (iSizeY)/double (iSizeX)) : 1.0;

// Maßstab ausrechnen
long lMasstab = 0L;

	if (kBild > kBAus) {
	// Maßstab aus Y-Koordinate ausrechnen
		if (iSizeY != 0)
			lMasstab = long ((fabs (dY) * m_dimDotsPerMM.Height()*1000.0) / 
					 double (iSizeY));
	} else {
	// Maßstab aus X-Koordinate ausrechnen
		if (iSizeX != 0)
			lMasstab = long ((fabs (dX) * m_dimDotsPerMM.Width()*1000.0) / 
					 double (iSizeX));
	}

// Maßstab anzeigen
	if (lMasstab != 0) 
		m_lMasstab = lMasstab;
//	if (fShow) 
		m_cbMasstab.SetText (ltoa (m_lMasstab, m_pInBuff, 10));

// Mittelpunktskoordinate anzeigen
DoublePair DP1 (lx, ly);
DoublePair DP2 (rx, ly);
DoublePair DP3 (lx, ry);
double dXDelta = 0.0;
double dYDelta = 0.0;

	if (pCT() -> hasDistEx()) {
	DoublePair DP4 (rx, ry);

		pCT() -> CoordTransDistanceEx (&DP1, &DP4, dXDelta, dYDelta);
	} else {
		dXDelta = pCT() -> CoordTransDistance (&DP1, &DP2);
		dYDelta = pCT() -> CoordTransDistance (&DP1, &DP3);
	}

	DP1 = DoublePair (lx, ry);
	DP2 = DoublePair (dXDelta/2, dYDelta/2);
	pCT() -> CoordTransRectangle (&DP1, &DP2, &DP3);

double dXCentre = DP3.Width();
double dYCentre = DP3.Height();

#if defined(WIN32)
//	pCT() -> GetTransformParam (lx, ly, &pData);
	pCT() -> TransformEx (&dXCentre, &dYCentre, pData);
	if (NULL != pData) CoTaskMemFree (pData);
#else
	pCT() -> Transform (&dXCentre, &dYCentre);
#endif // WIN32

	pCT() -> CoordTransToStringEx (dXCentre, dYCentre, true, m_pInBuff, INBUFFLEN);
	m_dneMittelRechtsWert.SetText (m_pInBuff);
	pCT() -> CoordTransToStringEx (dXCentre, dYCentre, false, m_pInBuff, INBUFFLEN);
	m_dneMittelHochWert.SetText (m_pInBuff);

return true;
}


// Einlesen und Transformieren in eine Zahlendarstellung einer Koordinate -----
bool CAusschnittsDlg :: GetValue (DoubleNumEdit &dblNEDX, double &dblX, 
				  DoubleNumEdit &dblNEDY, double &dblY)
{
	if (dblNEDX.GetTextLen() > 0 && dblNEDY.GetTextLen() > 0) {
		dblNEDX.GetText (m_pInBuff, INBUFFLEN);
		dblNEDY.GetText (m_pInBuffY, INBUFFLEN);
		return pCT() -> CoordTransToValueEx (m_pInBuff, m_pInBuffY, dblX, dblY);
	}
	dblX = 0.0;
	dblY = 0.0;

return false;
}


// GetMasstab rechnet den ComboBoxIndex in einen Maßstab um -------------------
long CAusschnittsDlg :: GetMasstab (short iIndex) 
{
	switch (iIndex) {
	case 0:		return 250L;
	case 1:		return 500L;
	case 2:		return 1000L;
	case 3:		return 2000L;
	case 4:		return 4000L;
	case 5:		return 5000L;
	case 6:		return 10000L;
	case 7:		return 25000L;
	case 8:		return 50000L;
	case 9:		return 100000L;
	case 10:	return 200000L;
	case 11:	return 500000L;
	case 12:	return 750000L;
	case 13:	return 1000000L;
	case 14:	return 2000000L;
	case 15:	return 5000000L;
	}

return 0L;
}


