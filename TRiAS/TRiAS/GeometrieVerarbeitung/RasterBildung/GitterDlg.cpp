// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 06.12.2002 13:02:11 
//
// @doc    Konfigurationsdialog zu PropertyAction für Gitterbildung
// @module GitterDlg.cpp | Definition of the <c CGitterDlg> class

#include "RasterP.hxx"

#include <ospace/std/algorithm>	// swap()

#include "Koord.hxx"			// DBKoordInReal()

#include "RasterR.h"
#include "Gitter.hxx"			// RasterExtension

#include "GitterDlg.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//extern char g_pDLLName[_MAX_PATH];


///////////////////////////////////////////////////////////////////////////////////////////////
// CGitterDlg

CGitterDlg* CGitterDlg::CreateInstance (LPCSTR pcCaption)
{
CGitterDlg* pCfgDlg = NULL;

	COM_TRY
	{
	// Dialog erzeugen
	ResourceFile RF (g_pDLLName);

		pCfgDlg = new CGitterDlg (ResID(CGitterDlg::IDD, &RF), pcCaption);

		if (NULL == pCfgDlg || !pCfgDlg -> FInit())
		{
			DELETE_OBJ(pCfgDlg);
			return NULL;
		}

	}
	COM_CATCH_OP_RETURN(delete pCfgDlg, NULL);
	
	return pCfgDlg; 
}


// --------------------------------------------------------------------------------------------
CGitterDlg::CGitterDlg(ResID uiResID, LPCSTR pcCaption)
		  : CPropertyPage(uiResID, pcCaption),
			m_TopRightValue (this, IDE_RECHTSWERTOBEN),
			m_TopHightValue (this, IDE_HOCHWERTOBEN),
			m_BottomRightValue (this, IDE_RECHTSWERTUNTEN),
			m_BottomHighValue (this, IDE_HOCHWERTUNTEN),
			m_CBoxRound (this, IDC_ROUND),
			m_RoundValuesList (this, IDC_ROUNDVALUES),
			m_RBttnArea (this, IDR_FLAECHE),
			m_RBttnLine (this, IDR_LINIE),
			m_Horizontal (this, IDE_WAAGERECHT),
			m_Vertical (this, IDE_SENKRECHT),
			m_Angle (this, IDE_WINKEL)

{
	m_dwFlags = 0;
	m_bType = true;			// Gittertyp (Fläche)
	m_iRoundListIndex = -1;
	m_lRoundValue = 0;
	m_bDefXWidth = true;
	m_bDefYWidth = true;
	m_dTurnAngle = 0.;		// Drehwinkel
}


// --------------------------------------------------------------------------------------------
CGitterDlg::~CGitterDlg()
{
}


// --------------------------------------------------------------------------------------------
BOOL CGitterDlg::FInit()
{
	return TRUE;
}


// --------------------------------------------------------------------------------------------
void CGitterDlg::AdjustSheetButtons()
{
CPropertySheet *pSheet = GetPropertySheet();

	_ASSERTE(NULL != pSheet);	

DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns = PSWIZB_BACK;			// nicht erste Seite

	if (!GetDisableNextPage()) {
		if (m_dwFlags & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte Seite
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	pSheet -> SetWizardButtons(dwBttns);
}


// --------------------------------------------------------------------------------------------
// Den "Fertig stellen"-Button aktivieren (bFinish == true) bzw. deaktivieren (false)
void CGitterDlg::FinishButton (bool bFinish)
{
CPropertySheet *pSheet = GetPropertySheet();

	_ASSERTE(NULL != pSheet);	

DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns = PSWIZB_BACK;			// nicht erste Seite

	if (bFinish)
	{
		if (m_dwFlags & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte Seite
	}
	else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	pSheet -> SetWizardButtons(dwBttns);
}


// --------------------------------------------------------------------------------------------
BOOL CGitterDlg::GetDisableNextPage()
{
	return FALSE;
}


//-------------------------------------------------------------------------------------------------
// Überprüfung der editierbaren Eingaben
// Routine wird bei manuellen Eingaben in eines der Editierfelder, aber auch z.B. bei
// SetText() gerufen
void CGitterDlg::EditChange (ControlEvt e)
{
	FinishButton (false);

	switch ((uint) e.GetControlID())
	{
		case IDE_WAAGERECHT:
			if (m_bDefXWidth &&								// der default-Wert der x-Gitterbreite
				InputWidth (&m_Horizontal) != m_lXWidth)	//  wurde editiert
				m_bDefXWidth = false;
			break;

		case IDE_SENKRECHT:
			if (m_bDefYWidth &&								// der default-Wert der y-Gitterbreite
				InputWidth (&m_Vertical) != m_lYWidth)		//  wurde editiert
				m_bDefYWidth = false;
	}

char szBufferX[40], szBufferY[40];	// Konvertierungspuffer für x- bzw. y-Koordinate
double dRWo, dHWo, dRWu, dHWu;		// Zwischenwerte für Test auf Sinnfälligkeit

	m_TopRightValue.GetText (szBufferX, sizeof (szBufferX));
	m_TopHightValue.GetText (szBufferY, sizeof (szBufferY));
	if (m_CTX.CoordTransToValueEx (szBufferX, szBufferY, dRWo, dHWo) == false)
		return;
	
	m_BottomRightValue.GetText (szBufferX, sizeof (szBufferX));
	m_BottomHighValue.GetText (szBufferY, sizeof (szBufferY));
	if (m_CTX.CoordTransToValueEx (szBufferX, szBufferY, dRWu, dHWu) == false)
		return;

	if (dRWo > 0 && dRWu > 0 &&	//  dRWo <= dRWu und dHWo >= dHWu können wegen möglicher
	    dHWo > 0 && dHWu > 0 &&	//  Rundungseffekte verletzt werden
//		dRWu <= dRWo &&			//  neuerdings werden die Werte "Rechts-oben" und
		dRWo <= dRWu &&
		dHWu <= dHWo &&
		InputWidth (&m_Horizontal) > 0. &&	// Gitterbreite
		InputWidth (&m_Vertical) > 0.)		// Gitterhöhe
		FinishButton (true);	// "Fertig stellen"-Button nur bei sinnvoller Eingabe freigeben

} // EditChange



///////////////////////////////////////////////////////////////////////////////////////////////
// CGitterDlg message handlers

// Call-Back-Funktion für die Initialisierung der Controls
void CGitterDlg::WindowInit(Event e) 
{
    // explizite Initialisierung der Controls
	m_TopRightValue.FInit();
	m_TopHightValue.FInit();
	m_BottomRightValue.FInit();
	m_BottomHighValue.FInit();
	m_CBoxRound.FInit();
	m_RoundValuesList.FInit();
	m_RBttnArea.FInit();
	m_RBttnLine.FInit();
	m_Horizontal.FInit();
	m_Vertical.FInit();
	m_Angle.FInit();

	// NumEditX initialiseren
	m_TopRightValue.SetNumEditMode (NumEditX :: NEM_NoTest);
	m_TopHightValue.SetNumEditMode (NumEditX :: NEM_NoTest);
	m_BottomRightValue.SetNumEditMode (NumEditX :: NEM_NoTest);
	m_BottomHighValue.SetNumEditMode (NumEditX :: NEM_NoTest);
	m_Horizontal.SetNumEditMode (NumEditX :: NEM_NoTest);
	m_Vertical.SetNumEditMode (NumEditX :: NEM_NoTest);
	m_Angle.SetNumEditMode (NumEditX :: NEM_NoTest);

	m_TopRightValue.SetFocus();     // 1. Eingabestelle soll bei "Rechtswert oben" sein

	// Controls initialisieren
	m_CBoxRound.SetChecked (m_bRound);
	m_RBttnArea.SetState (m_bType);
	m_RBttnLine.SetState (!m_bType);

	FillComboBox();

	m_RoundValuesList.ChangeCurrentIndex (m_iRoundListIndex);

	// Member initialisieren
	if (m_hWnd)		// Gitterbildung für ein konkretes Objekt
	{
		m_lONr = DEX_GetActiveObject (m_hWnd);	// Objektnummer und
		DEX_GetObjContainer (m_lONr, m_lCO);	//  Container-Koordinaten des aktivierten (blinkenden) Objektes
	}
	
	else			// Gitterbildung für einen allgemeinen Bereich
	{
		m_lONr = -1;

	ObjRechteck OC = ObjRechteck (0L, 0L, 0L, 0L);

		DEX_GetActiveSelection (&OC);

		if (OC.YMin() > OC.YMax())	// YMin, YMax ggf. tauschen
			swap (OC.YMin(), OC.YMax());

		m_lCO[0] = OC.XMin();
		m_lCO[1] = OC.XMax();
		m_lCO[2] = OC.YMin();
		m_lCO[3] = OC.YMax();
	}

	GridPresetting();	// Gitter-Koordinaten, -breite und -drehwinkel
} // WindowInit


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn der Button "Weiter" gedrückt wurde
// Rückgabe von
//    0: für OK
//   -1: für cancel
int CGitterDlg::OnWizNext (NotifyEvt)
{
char szBufferX[40], szBufferY[40];

	// nur Rückrechnung aus den Editierfenstern, wenn dort auch editiert wurde
	if (m_TopRightValue.isModified() || m_TopHightValue.isModified())
	{
		m_TopRightValue.GetText (szBufferX, sizeof (szBufferX));
		m_TopHightValue.GetText (szBufferY, sizeof (szBufferY));
		if (m_CTX.CoordTransToValueEx (szBufferX, szBufferY, m_dTRV, m_dTHV) == false)
			return TRUE;

		m_TopRightValue.SetModified (false);
		m_TopHightValue.SetModified (false);
	}

	if (m_BottomRightValue.isModified() || m_BottomHighValue.isModified())
	{
		m_BottomRightValue.GetText (szBufferX, sizeof (szBufferX));
		m_BottomHighValue.GetText (szBufferY, sizeof (szBufferY));
		if (m_CTX.CoordTransToValueEx (szBufferX, szBufferY, m_dBRV, m_dBHV) == false)
			return TRUE;

		m_BottomRightValue.SetModified (false);
		m_BottomHighValue.SetModified (false);
	}

	m_lXWidth = InputWidth (&m_Horizontal);
	if (-1 == m_lXWidth)		// wird keine x-Breite eingegeben, dann
		m_lXWidth = XBREITE;	//  Standardwert

	m_lYWidth = InputWidth (&m_Vertical);
	if (-1 == m_lYWidth)		// wird keine y-Breite eingegeben, dann
		m_lYWidth = m_lXWidth;	// wird die x-Breite verwendet

	m_Angle.GetValue (m_dTurnAngle);

	if (m_dTurnAngle)			// bei echter Drehung,
		ContainerRotation();	//  Container von gedrehtem Bereich bestimmen

	m_bType = m_RBttnArea.GetState();

/*
// aus den Punkten "Rechts-oben" und "Links-unten" des Dialogs werden für die Bearbeitung die
// Punkte "Links-oben" und "Rechts-unten" errechnet
EPunkt PRO, PLU;	// rechter oberer und linker unterer Punkt des Bereiches in DB-Koordinaten

	RealInDBKoord (m_dBRV, m_dTHV, m_PLO.X(), m_PLO.Y(), &m_CTX);
	RealInDBKoord (m_dTRV, m_dBHV, m_PRU.X(), m_PRU.Y(), &m_CTX);
*/
//	RealInDBKoord (m_dTRV, m_dTHV, m_PRO.X(), m_PRO.Y(), &m_CTX);
//	RealInDBKoord (m_dBRV, m_dBHV, m_PLU.X(), m_PLU.Y(), &m_CTX);
	RealInDBKoord (m_dTRV, m_dTHV, m_PLO.X(), m_PLO.Y(), &m_CTX);
	RealInDBKoord (m_dBRV, m_dBHV, m_PRU.X(), m_PRU.Y(), &m_CTX);

	return 0;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn Button "Fertig stellen" gedrückt wurde
//    FALSE: für OK
//    TRUE:  für cancel
BOOL CGitterDlg::OnWizFinish (NotifyEvt)
{
	return FALSE;
}


// --------------------------------------------------------------------------------------------
int CGitterDlg::OnSetActive (NotifyEvt e)
{
	AdjustSheetButtons();
	return 0;
}


// --------------------------------------------------------------------------------------------
void CGitterDlg::ButtonClick(ControlEvt e)
{
	switch ((uint) e.GetControlID())
	{
		case IDC_ROUND:
			if (m_CBoxRound.isChecked())
			{
				m_bRound = true;
				m_RoundValuesList.SetFocus();
			}
			else
			{
				m_bRound = false;

				m_RoundValuesList.ChangeCurrentIndex(-1);
				m_lRoundValue = 0;

				m_dTRV = m_dOrigTRV;
				m_dTHV = m_dOrigTHV;
				m_dBRV = m_dOrigBRV;
				m_dBHV = m_dOrigBHV;
				OutputCoords();

				if (m_bDefXWidth)
				{
					m_lXWidth = m_lOrigWidth;
					m_Horizontal.SetValue (m_lXWidth);
				}
	
				if (m_bDefYWidth)
				{
					m_lYWidth = m_lOrigWidth;
					m_Vertical.SetValue (m_lYWidth);
				}

				m_TopRightValue.SetFocus();
			}
	}

	AdjustSheetButtons();
}


// --------------------------------------------------------------------------------------------
// Reaktion bei Click in die ComboBox
void CGitterDlg::ListBoxSel (ControlEvt)
{
	m_CBoxRound.SetChecked (true);

	switch (m_RoundValuesList.GetCurrentIndex())
	{
		case 0:
			m_lRoundValue = 1;
			break;

		case 1:
			m_lRoundValue = 10;
			break;

		case 2:
			m_lRoundValue = 100;
			break;

		case 3:
			m_lRoundValue = 1000;
			break;

		case 4:
			m_lRoundValue = 10000;
	}

	m_iRoundListIndex = m_RoundValuesList.GetCurrentIndex();

	if (0 == m_lRoundValue) return;

//	m_dTRV = ceil(m_dOrigTRV / m_lRoundValue) * m_lRoundValue;
//	m_dTHV = ceil(m_dOrigTHV / m_lRoundValue) * m_lRoundValue;
//	m_dBRV = floor(m_dOrigBRV / m_lRoundValue) * m_lRoundValue;
//	m_dBHV = floor(m_dOrigBHV / m_lRoundValue) * m_lRoundValue;
	m_dTRV = floor(m_dOrigTRV / m_lRoundValue) * m_lRoundValue;
	m_dTHV = ceil(m_dOrigTHV / m_lRoundValue) * m_lRoundValue;
	m_dBRV = ceil(m_dOrigBRV / m_lRoundValue) * m_lRoundValue;
	m_dBHV = floor(m_dOrigBHV / m_lRoundValue) * m_lRoundValue;

	OutputCoords();

	// wenn die Gitterbreiten in x- und y-Richtung noch nicht durch den Anwender editiert
	// wurden, wird der automatische erzeugte default-Wert vergrößert, wenn er kleiner als
	// der Rundungswert ist
	if (m_bDefXWidth && m_lXWidth != m_lRoundValue)
	{
		if (m_lRoundValue >= m_lOrigWidth)
			m_lXWidth = m_lRoundValue;
		else
			m_lXWidth = m_lOrigWidth;
		m_Horizontal.SetValue (m_lXWidth);
	}
	
	if (m_bDefYWidth && m_lYWidth != m_lRoundValue)
	{
		if (m_lRoundValue >= m_lOrigWidth)
			m_lYWidth = m_lRoundValue;
		else
			m_lYWidth = m_lOrigWidth;
		m_Vertical.SetValue (m_lYWidth);
	}
} // ListBoxSel


// --------------------------------------------------------------------------------------------
// ComboBox füllen
void CGitterDlg::FillComboBox (void)
{
	m_RoundValuesList.AddString (sRound1, 0);
	m_RoundValuesList.AddString (sRound10, 1);
	m_RoundValuesList.AddString (sRound100, 2);
	m_RoundValuesList.AddString (sRound1000, 3);
	m_RoundValuesList.AddString (sRound10000, 4);
}


// -------------------------------------------------------------------------------------------
// Voreinstellung von Werten, bei Gitterbildung für
// - einen allgemeinen rechteckigen Bereich (m_hWnd == 0) Koordinaten der akt. Sicht und
//   Gitterbreite in beiden Richtungen von XBREITE
// - ein konkretes Objekt (m_hWnd > 0) Koordinaten des Objektcontainers und Gitterbreite so,
//   dass in Richtung der kleineren Containerbreite RANZAHL Gitter gebildet werden,
//   Gitterbreite wird auf RGENAU Genauigkeit gerundet
void CGitterDlg::GridPresetting (void)
{
/*
	// Konvertierung des rechten oberen bzw. linken unteren Punktes des Containers in
	// Real-Koordinaten
	DBKoordInReal (m_lCO[1], m_lCO[3], m_dTRV, m_dTHV, &m_CTX);
	DBKoordInReal (m_lCO[0], m_lCO[2], m_dBRV, m_dBHV, &m_CTX);
*/
	// Konvertierung des linken oberen bzw. rechten unteren Punktes des Containers in Real-Koordinaten
	DBKoordInReal (m_lCO[0], m_lCO[3], m_dTRV, m_dTHV, &m_CTX);
	DBKoordInReal (m_lCO[1], m_lCO[2], m_dBRV, m_dBHV, &m_CTX);

	// Gitterbildung für ein konkretes Objekt
	if (m_hWnd)
	{
		// Punktobjekt
		if (m_lCO[0] == m_lCO[1] && m_lCO[2] == m_lCO[3])
			m_lXWidth = RQUADRAT;

		// Linien- oder Flächenobjekt
		else
		{
		// kleinste Containerbreite bestimmen und daraus die Gitterbreite, so dass in dieser
		// Richtung RANZAHL Gitter entstehen
		DoublePair DPRU (m_dTRV, m_dBHV);	// Container-Eckpunkt rechts unten
		DoublePair DPLU (m_dBRV, m_dBHV);	// links unten
		DoublePair DPLO (m_dBRV, m_dTHV);	// links oben
		double dBr = m_CTX.CoordTransDistance (&DPLU, &DPRU);	// Breite
		double dHoe = m_CTX.CoordTransDistance (&DPLU, &DPLO);	// Höhe des Containers
		double dMinBr;		// kleinere der beiden Container-Seiten

			(dBr < dHoe) ? (dMinBr = dBr) : (dMinBr = dHoe);

			m_lXWidth = (KoOrd) (dMinBr / RANZAHL);
			if (m_lXWidth > RGENAU10)	// auf ganzzahliges Vielfaches von RGENAU10 abrunden
				m_lXWidth = m_lXWidth / RGENAU10 * RGENAU10;
			if (m_lXWidth > RGENAU100)	// auf ganzzahliges Vielfaches von RGENAU100 abrunden
				m_lXWidth = m_lXWidth / RGENAU100 * RGENAU100;
			if (m_lXWidth == 0)
				m_lXWidth = RQUADRAT;
			if (m_lXWidth > BREITEOG)
				m_lXWidth = BREITEOG;
		}
	}

	else	// Gitterbildung für einen allgemeinen rechteckigen Bereich
		m_lXWidth = XBREITE;

	if (m_bRound && m_lXWidth < m_lRoundValue)
		m_lXWidth = m_lRoundValue;

	m_lYWidth = m_lXWidth;

	m_dOrigTRV = m_dTRV;	// die ursprünglichen Werte für eine evtl. Änderung auf eine
	m_dOrigTHV = m_dTHV;	//   höhere Rundungsgenauigkeit retten
	m_dOrigBRV = m_dBRV;
	m_dOrigBHV = m_dBHV;

	m_lOrigWidth = m_lXWidth;

//	m_dTRV = ceil(m_dTRV);	// die anzuzeigenden Koordinaten gleich auf 1-m-Genauigkeit runden
//	m_dTHV = ceil(m_dTHV);
//	m_dBRV = floor(m_dBRV);
//	m_dBHV = floor(m_dBHV);

	OutputCoords();

	m_Horizontal.SetValue (m_lXWidth);
	m_Vertical.SetValue (m_lYWidth);
	m_Angle.SetValue (m_dTurnAngle);

} // GridPresetting


//----------------------------------------------------------------------------------------
// Rückgabe der Koordinaten für die Anzeige an den Dialog
void CGitterDlg::OutputCoords (void)
{
char szBuffer[40];	// Konvertierungspuffer

	m_CTX.CoordTransToStringEx (m_dTRV, m_dTHV, true, szBuffer, sizeof (szBuffer));
	m_TopRightValue.SetText (szBuffer);
	m_CTX.CoordTransToStringEx (m_dTRV, m_dTHV, false, szBuffer, sizeof (szBuffer));
	m_TopHightValue.SetText (szBuffer);
	m_CTX.CoordTransToStringEx (m_dBRV, m_dBHV, true, szBuffer, sizeof (szBuffer));
	m_BottomRightValue.SetText (szBuffer);
	m_CTX.CoordTransToStringEx (m_dBRV, m_dBHV, false, szBuffer, sizeof (szBuffer));
	m_BottomHighValue.SetText (szBuffer);

	m_TopRightValue.SetModified (false);	// keine Modifizerung durch den Anwender
	m_TopHightValue.SetModified (false);
	m_BottomRightValue.SetModified (false);
	m_BottomHighValue.SetModified (false);
}


//----------------------------------------------------------------------------------------
// Eingabe der waagerechten bzw. senkrechten Gitterbreite
int CGitterDlg::InputWidth (NumEditX* pEingWert)
{
	_ASSERTE (NULL != pEingWert);

int iRet = -1;

	if (pEingWert -> GetTextLen() > 0)
	{
	char szInBuffer[20];

		pEingWert -> GetText (szInBuffer, sizeof(szInBuffer));
		iRet = atoi (szInBuffer);
		if (0 == iRet)
			iRet = -1;
	}

	return iRet;

} // InputWidth


//-------------------------------------------------------------------------------------------------
// Wenn Drehwinkel != 0, wird der Container des um den negativen (!) m_dTurnAngle gedrehten
// Objektes bestimmt; für ein Punktobjekt wird in dieser Routine nichts gemacht
void CGitterDlg::ContainerRotation (void)
{
int iOT;

	if (0 != m_lONr && -1 != m_lONr)	// Gitterbildung für ein konkretes Objekt
	{
		iOT = DEX_GetObjectType (m_lONr);
		if (OT_KANTE != iOT && OT_FLAECHE != iOT)	// nur für Gitter um Linie oder Fläche
			return;
	}

// Hilfswerte für for-Schleife
double dSin = sin (-m_dTurnAngle*Pi/180.);		// Drehung um negativen (!) m_dTurnAngle (Pi
double dCos = cos (-m_dTurnAngle*Pi/180.);		//   ist inGeoKonst.hxx definiert)
double xm = ((double)m_lCO[0] + m_lCO[1]) / 2.; // Mittelpunkt des
double ym = ((double)m_lCO[2] + m_lCO[3]) / 2.; //  achsenparallelen Containers (in DB-Koordinaten)
double dFak = 1.;	// Faktor für den Fall, dass x- und y-Achse nicht die gleiche
					// Maßeinteilung besitzen (geodätische Koordinaten)

	if (!m_CTX.isMetric())
	{
		if (m_lCO[0] != m_lCO[1] && m_lCO[2] != m_lCO[3])	// beide Containerseiten > 0
			dFak = m_CTX.CoordTransAspectRatio (ObjRechteck (m_lCO[0], m_lCO[1], m_lCO[2],
															 m_lCO[3]));
		else			// mindestens eine Containerseite == 0
		{
		KoOrd hw;	// Hilfswert

			if (m_lCO[0] == m_lCO[1] && m_lCO[2] != m_lCO[3])	// waagerechte Seite == 0
			{
				hw = m_lCO[0] + m_lCO[3] - m_lCO[2];
				dFak = m_CTX.CoordTransAspectRatio (ObjRechteck (m_lCO[0], hw, m_lCO[2],
																 m_lCO[3]));
			}
			if (m_lCO[2] == m_lCO[3] && m_lCO[0] != m_lCO[1])	// senkrechte Seite == 0
			{
				hw = m_lCO[2] + m_lCO[1] - m_lCO[0];
				dFak = m_CTX.CoordTransAspectRatio (ObjRechteck (m_lCO[0], m_lCO[1],
																 m_lCO[2], hw));
			}
			else	// beide Seien == 0
			{
			KoOrd lCO[4];

				DEX_GetActiveSightContainer (lCO);
				dFak = m_CTX.CoordTransAspectRatio (ObjRechteck (lCO[0], lCO[1], lCO[2],
																 lCO[3]));
			}
		}
	}

// Startwerte für den Container des gedrehten Objektes bzw. Bereiches
double xmin = DBL_MAX;
double ymin = DBL_MAX;
double xmax = -1.;
double ymax = -1.;
double x, y;

	if (m_hWnd)		// Gitterbildung für ein konkretes Objekt
	{
	IObjektGeometrie* pIOG = NULL;

		if (FAILED(CreateInterfaceOG (&pIOG, m_lONr)))
			return;

	// Parameter des aktivierten (blinkenden) Objektes
	long lSPAnz;
	KoOrd* plXK; KoOrd* plYK;
	long* plK;

		pIOG -> GetCnt (&lSPAnz);
		pIOG -> GetX ((void**)&plXK);
		pIOG -> GetY ((void**)&plYK);
		pIOG -> GetLPCnt (&plK);

		if (OT_FLAECHE == iOT)
			lSPAnz = plK [0];

		for (long i = 0; i < lSPAnz; ++i)	// Stützpunkte drehen
		{
			x = xm - (xm-plXK[i])*dCos + (ym-plYK[i])*dSin/dFak;
			y = ym - dFak*(xm-plXK[i])*dSin - (ym-plYK[i])*dCos;

			if (xmin > x) xmin = x;
			if (xmax < x) xmax = x;
			if (ymin > y) ymin = y;
			if (ymax < y) ymax = y;
		}
		pIOG -> Release ();
	}

	else			// Gitterbildung für einen allgemeinen Bereich
	{
	KoOrd plXK[4], plYK[4];

		plXK[0] = m_lCO[0];   plYK[0] = m_lCO[2];
		plXK[1] = m_lCO[1];   plYK[1] = m_lCO[2];
		plXK[2] = m_lCO[1];   plYK[2] = m_lCO[3];
		plXK[3] = m_lCO[0];   plYK[3] = m_lCO[3];

		for (long i = 0; i < 4; ++i)	// Eckpunkte des allgemeinen Bereiches drehen
		{
			x = xm - (xm-plXK[i])*dCos + (ym-plYK[i])*dSin/dFak;
			y = ym - dFak*(xm-plXK[i])*dSin - (ym-plYK[i])*dCos;

			if (xmin > x) xmin = x;
			if (xmax < x) xmax = x;
			if (ymin > y) ymin = y;
			if (ymax < y) ymax = y;
		}
	}

/*	// Konvertierung des rechten oberen bzw. linken unteren Punktes des Containers in
	// Real-Koordinaten
	DBKoordInReal (DtoL(xmax), DtoL(ymax), m_dTRV, m_dTHV, &m_CTX);
	DBKoordInReal (DtoL(xmin), DtoL(ymin), m_dBRV, m_dBHV, &m_CTX);
*/
	// Koordinaten des Containers des gedrehten Objektes bzw. Bereiches in Real-Koordinaten
	// bestimmen
	DBKoordInReal (DtoL(xmin), DtoL(ymax), m_dTRV, m_dTHV, &m_CTX);
	DBKoordInReal (DtoL(xmax), DtoL(ymin), m_dBRV, m_dBHV, &m_CTX);

} // ContainerRotation


// --------------------------------------------------------------------------------------------
// Initialisierungsdaten für den Dialog aus pSelInfo übernehmen
HRESULT CGitterDlg::SetSelectedInfo (GRIDDATA* pSelInfo, bool bNoShow)
{
	if (NULL == pSelInfo) return E_POINTER;

	m_bType = pSelInfo->bType;
//	m_dTRV = pSelInfo->dTRV;
//	m_dTHV = pSelInfo->dTHV;
//	m_dBRV = pSelInfo->dBRV;
//	m_dBHV = pSelInfo->dBHV;
	m_bRound = pSelInfo->bRound;
	m_iRoundListIndex = pSelInfo->iRoundListIndex;
	m_lRoundValue = pSelInfo->lRoundValue;
//	m_lXWidth = pSelInfo->lXWidth;
//	m_lYWidth = pSelInfo->lYWidth;
	m_dTurnAngle = pSelInfo->dTurnAngle;

	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Zustand des Dialogs für evtl. Save() zwischenspeichern
HRESULT CGitterDlg::GetSelectedInfo (GRIDDATA* pSelInfo, bool& bIsDirty)
{
	if (NULL == pSelInfo) return E_POINTER;

	if (pSelInfo->bType != m_bType ||
//		pSelInfo->dTRV != m_dTRV ||
//		pSelInfo->dTHV != m_dTHV ||
//		pSelInfo->dBRV != m_dBRV ||
//		pSelInfo->dBHV != m_dBHV ||
		pSelInfo->bRound != m_bRound ||
		pSelInfo->iRoundListIndex != m_iRoundListIndex ||
		pSelInfo->lRoundValue != m_lRoundValue ||
//		pSelInfo->lXWidth != m_lXWidth ||
//		pSelInfo->lYWidth != m_lYWidth ||
		pSelInfo->dTurnAngle != m_dTurnAngle)
	{
		pSelInfo->bType = m_bType;
//		pSelInfo->dTRV = m_dTRV;
//		pSelInfo->dTHV = m_dTHV;
//		pSelInfo->dBRV = m_dBRV;
//		pSelInfo->dBHV = m_dBHV;
		pSelInfo->bRound = m_bRound;
		pSelInfo->iRoundListIndex = m_iRoundListIndex;
		pSelInfo->lRoundValue = m_lRoundValue;
//		pSelInfo->lXWidth = m_lXWidth;
//		pSelInfo->lYWidth = m_lYWidth;
		pSelInfo->dTurnAngle = m_dTurnAngle;

		bIsDirty = true;	// Änderungen im Dialog
	}
	else
		bIsDirty = false;	// keine Änderungen

	return S_OK;
}
