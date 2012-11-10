// Dialogfenster fuer die Einstellung der DruckLayoutParameter 
// File PRNTLAYT.CXX

#include "triaspre.hxx"

#include "triasres.h"

#include <printer.hxx>
#include <owncombo.hxx>
#include <ActPrint.h>

#include "strings.h"

#include "extmain3.hxx"
#include "prlayout.hxx"
#include "prntlayt.hxx"
#include "prntprof.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define WM_SETFOCUSTOWINDOW		(WM_USER+1234)

// sonstige FunktionsprotoTypen -----------------------------------------------
ErrCode EvalKoeffs (double *, double *, double *, double *);

// Konstruktor ----------------------------------------------------------------
#pragma warning (disable:4355)

CPrintLayoutDlg :: CPrintLayoutDlg (
			const ObjContainer &actRect, CoordTrans *pCTF, PrinterPars &rPP) 
	: CPropertyPage (IDD_PRINTLAYOUT, ResString (IDS_LAYOUTPAGECAP, 32)),
		  m_isValid (false), m_rPP (rPP),
	// Kartenausschnitt
		  m_ObenHoch (this, IDE_PRINTOBENHOCH),
		  m_ObenRechts (this, IDE_PRINTOBENRECHTS),
		  m_UntenHoch (this, IDE_PRINTUNTENHOCH),
		  m_UntenRechts (this, IDE_PRINTUNTENRECHTS),
		  m_Masstab (this, IDC_MASSTAB),
		  m_RKoord (this, IDR_PRINTRECHTS),
		  m_RMasstab (this, IDR_PRINTMASSTAB),
	// Buttons
		  m_Default (this, IDB_STANDARDSETTINGS),
		  m_pbSelect (this, IDB_PRINTERSELECTION),
	// Kartenlayout
		  m_CBLegende (this, IDCB_PRINTLEGENDE),
		  m_CBLegendOnly (this, IDC_LEGENDONLY),
		  m_CBRahmen (this, IDCB_PRINTRAHMEN),
		  m_CBMasstab (this, IDCB_PRINTMASSTAB),
		  m_CBHeadLine (this, IDCB_PRINTHEADLINE),
		  m_HeadLine (this, IDE_HEADLINE),
	// Seitenränder
		  m_RandLinks (this, IDE_PRINTFORMATLINKS, IDMS_PRINTFORMATLINKS, Range (0, 1000)),
		  m_RandOben (this, IDE_PRINTFORMATOBEN, IDMS_PRINTFORMATOBEN, Range (0, 1000)),
		  m_RandRechts (this, IDE_PRINTFORMATRECHTS, IDMS_PRINTFORMATRECHTS, Range (0, 1000)), 
		  m_RandUnten (this, IDE_PRINTFORMATUNTEN, IDMS_PRINTFORMATUNTEN, Range (0, 1000)),
	// Format des Kartenausschnittes
		  m_SizeX (this, IDE_PRINTFORMATX, IDMS_PRINTFORMAT_X, Range (0, 3000)),
		  m_SizeY (this, IDE_PRINTFORMATY, IDMS_PRINTFORMAT_Y, Range (0, 3000)),
	// Koordinatentransformation
		  m_pCT (pCTF)
{
	m_ocActRect = actRect;
	m_pInBuff = NULL;

	m_fSysMode = (DEX_QueryMode() & QMSysAdmin) ? true : false;
}

#pragma warning (default:4355)

void CPrintLayoutDlg::WindowInit (Event)
{
CEierUhr Wait (this, CursorPath(g_cbCursorPrint));

// Kartenausschnitt
	m_ObenHoch.FInit();
	m_ObenRechts.FInit();
	m_UntenHoch.FInit();
	m_UntenRechts.FInit();
	m_Masstab.FInit();
	m_RKoord.FInit();
	m_RMasstab.FInit();
// Buttons
	m_Default.FInit();
	m_pbSelect.FInit();
// Kartenlayout
	m_CBLegende.FInit();
	m_CBLegendOnly.FInit();
	m_CBRahmen.FInit();
	m_CBMasstab.FInit();
	m_CBHeadLine.FInit();
	m_HeadLine.FInit();
// Seitenränder
	m_RandLinks.FInit();
	m_RandOben.FInit();
	m_RandRechts.FInit();
	m_RandUnten.FInit();
// Format des Kartenausschnittes
	m_SizeX.FInit();
	m_SizeY.FInit();

// Controls initialisieren
	m_ObenRechts.SetNumEditMode (NumEdit :: NEM_NoTest);
	m_ObenHoch.SetNumEditMode (NumEdit :: NEM_NoTest);
	m_UntenRechts.SetNumEditMode (NumEdit :: NEM_NoTest);
	m_UntenHoch.SetNumEditMode (NumEdit :: NEM_NoTest);

	m_HeadLine.SetTextLimit (HEADLINELENGTH);
	m_HeadLine.SetText ("");

// MaßstabsComboBox füllen
	for (short i = 0; i < CNT_MASSTAB; i++) 
		m_Masstab.AddString (ResString (IDS_MASSTAB250+i, 10));

	m_SizeX.HideSpin();		// für Neef
	m_SizeY.HideSpin();

	if (!m_fSysMode)
		m_CBLegendOnly.Hide();

// letzte Initialisierungen
	if (Init())		// jetzt ist der Dialog gültig
		m_isValid = true;
}

bool CPrintLayoutDlg::Init (void)
{
char cbUser[_MAX_PATH];		// NutzerName für ProjektINI
PrintProfile PPF (DEX_GetActiveUser (cbUser));

// Legende und Rahmen standardmäßig nicht drucken
	if (m_pInBuff == NULL) {
		m_pInBuff = new char [HEADLINELENGTH+1];
		if (m_pInBuff == NULL) return false;
		*m_pInBuff = '\0';
	}	

// Überschrift des Fensters generieren
	MakeCaption();

// ist eine Drucklegende
	if (!m_PrLayout.FInit (Pars())) return false;	// DruckLegende

// Controls Initialisieren
	*m_pInBuff = '\0';
	m_CBLegende.SetChecked (PPF.GetLegende());	// Legende
	if (m_fSysMode) {
		if (m_CBLegende.isChecked()) {
			m_CBLegendOnly.Enable();
			m_CBLegendOnly.SetChecked (PPF.GetLegendOnly());
		} else {
			m_CBLegendOnly.SetChecked (false);
			m_CBLegendOnly.Disable();
		}
	}
	m_CBRahmen.SetChecked (PPF.GetRahmen());	// Rahmen
	m_CBMasstab.SetChecked (PPF.GetMasstab());	// Maßstab
	m_CBHeadLine.SetChecked (PPF.GetHeadLine (m_pInBuff, HEADLINELENGTH));	// Überschrift
	m_HeadLine.SetText (m_pInBuff);
	
// Papierformat einstellen
	m_PageSize = Pars().GetPageSize();
	m_DotsPerMM = Pars().GetDotsPerMM();

Rectangle RandRc (10, 10, 10, 10);

	PPF.GetRand (RandRc);
	m_RandLinks.SetValue (short(RandRc.Left()));		// 10 mm Rand Links und Oben
	m_RandOben.SetValue (short(RandRc.Top()));
	m_RandRechts.SetValue (short(RandRc.Right()));
	m_RandUnten.SetValue (short(RandRc.Bottom()));

// entsprechend Seitengröße einstellen
	m_SizeX.SetValue (short(m_PageSize.Width()-RandRc.Left()-RandRc.Right()));
	m_SizeY.SetValue (short(m_PageSize.Height()-RandRc.Top()-RandRc.Bottom()));

// linke obere Ecke und Maßstab setzen
// echte Koordinaten der Ecken berechnen
ObjContainer ocR = m_ocActRect;	// aktueller Bildschrimausschnitt

	m_actMasstab = 10000L;

double X, Y;
short iTyp = PPF.GetAusschnitt (ocR.XMin(), ocR.YMax(), ocR.XMax(), ocR.YMin(), m_actMasstab);

	pCT() -> UnScale (ocR.XMin(), ocR.YMax(), &X, &Y);

LPVOID pData = NULL;

//	pCT() -> GetTransformParam (X, Y, &pData);
	pCT() -> TransformEx (&X, &Y, pData);

	pCT() -> CoordTransToStringEx (X, Y, true, m_pInBuff, INBUFFLEN);
	m_ObenRechts.SetText (m_pInBuff);
	pCT() -> CoordTransToStringEx (X, Y, false, m_pInBuff, INBUFFLEN);
	m_ObenHoch.SetText (m_pInBuff);

	switch (iTyp) {
	case 0:		// kein Ausschnitt gegeben
	case 1:		// LiObReUn
		{
			m_RKoord.SetState (true);	// RadioButtons
			m_RMasstab.SetState (false);	// default: Masstabseingabe

			pCT() -> UnScale (ocR.XMax(), ocR.YMin(), &X, &Y);
			pCT() -> TransformEx (&X, &Y, pData);

			pCT() -> CoordTransToStringEx (X, Y, true, m_pInBuff, INBUFFLEN);
			m_UntenRechts.SetText (m_pInBuff);
			pCT() -> CoordTransToStringEx (X, Y, false, m_pInBuff, INBUFFLEN);
			m_UntenHoch.SetText (m_pInBuff);
			
			EvalMasstab();
		}
		break;
		
	case 2:		// LiObMasstab
		{
			m_RKoord.SetState (false);	// RadioButtons
			m_RMasstab.SetState (true);	// default: Koordinateneingabe
			m_Masstab.ChangeCurrentIndex(-1);
			m_Masstab.SetText (ltoa (m_actMasstab, m_pInBuff, 10));
			EvalRechtsUnten();
		}
		break;
	}

	if (NULL != pData) CoTaskMemFree (pData);

// BlattGröße entsprechend berechnen
	EvalSizeX (false);
	EvalSizeY();

return true;
}

CPrintLayoutDlg :: ~CPrintLayoutDlg (void) 
{
	DELETE (m_pInBuff);
}

void CPrintLayoutDlg::SaveEntries (void)
{
// Einstellungen wieder wegschreiben
	if (m_pInBuff) {
	char cbUser[_MAX_PATH];
	PrintProfile PPF (DEX_GetActiveUser (cbUser));

	// PapierRänder merken
		Rectangle locRc (m_RandOben.GetValue(), 
				 m_RandLinks.GetValue(),
				 m_RandUnten.GetValue(), 
				 m_RandRechts.GetValue()
				);
		PPF.SetRand (locRc);

	// Überschrift merken
		m_HeadLine.GetText (m_pInBuff, INBUFFLEN);
		PPF.SetHeadLine (m_CBHeadLine.isChecked(), m_pInBuff); 

	// Ausschnitt/Maßstab merken
	double lx, ly, rx, ry;

		if (GetValue (m_ObenRechts, lx, m_ObenHoch, ly) &&
		    GetValue (m_UntenRechts, rx, m_UntenHoch, ry)) 
		{
		LPVOID pData = NULL;

//			pCT() -> GetInvTransformParam (lx, ly, &pData);
			pCT() -> InvTransformEx (&lx, &ly, pData);
			pCT() -> InvTransformEx (&rx, &ry, pData);
			if (NULL != pData) CoTaskMemFree (pData);

			pCT() -> Scale (lx, ly, &m_ocActRect.XMin(), &m_ocActRect.YMax());
			pCT() -> Scale (rx, ry, &m_ocActRect.XMax(), &m_ocActRect.YMin());

			if (m_RKoord.GetState()) {	// LiOb/ReUn
				PPF.SetAusschnitt (m_ocActRect.XMin(), m_ocActRect.YMax(), 
						   m_ocActRect.XMax(), m_ocActRect.YMin());
			} else {			// LiOb/Maßstab
				PPF.SetAusschnitt (m_ocActRect.XMin(), m_ocActRect.YMax(), 
						   m_actMasstab);
			}
		}

	// sonstiges merken				       
		PPF.SetRahmen (m_CBRahmen.isChecked());
		PPF.SetLegende (m_CBLegende.isChecked());
		if (m_fSysMode)	PPF.SetLegendOnly (m_CBLegendOnly.isChecked());
		PPF.SetMasstab (m_CBMasstab.isChecked());                     
	}
}

long myatol (const char *);

bool CPrintLayoutDlg::OnOK (NotifyEvt e)
{
	if (m_SizeX.isModified()) m_SizeX.CopyToSpin();
	if (m_SizeY.isModified()) m_SizeY.CopyToSpin();
	if (m_RandOben.isModified()) m_RandOben.CopyToSpin();
	if (m_RandUnten.isModified()) m_RandUnten.CopyToSpin();
	if (m_RandLinks.isModified()) m_RandLinks.CopyToSpin();
	if (m_RandRechts.isModified()) m_RandRechts.CopyToSpin();

	return false;		// false allows operation
}

void CPrintLayoutDlg::OnCancel (NotifyEvt e)
{
}

void CPrintLayoutDlg :: ButtonClick (ControlEvt e) 
{
bool fFullReset = true;

	switch ((unsigned int)e.GetControlID()) {
/*	case IDOK:
	// alle Spins aktualisieren
		if (m_SizeX.isModified()) m_SizeX.CopyToSpin();
		if (m_SizeY.isModified()) m_SizeY.CopyToSpin();
		if (m_RandOben.isModified()) m_RandOben.CopyToSpin();
		if (m_RandUnten.isModified()) m_RandUnten.CopyToSpin();
		if (m_RandLinks.isModified()) m_RandLinks.CopyToSpin();
		if (m_RandRechts.isModified()) m_RandRechts.CopyToSpin();
		EndDlg (1);
		break;

	case IDCANCEL:
		EndDlg (0);	// abbrechen und raus
		break;
*/
	case IDR_PRINTRECHTS:
		{
			m_Masstab.GetText (m_pInBuff, INBUFFLEN);
			m_actMasstab = myatol (m_pInBuff);
//			m_Masstab.ChangeCurrentIndex (-1);
			m_RKoord.SetState (true);
			m_RMasstab.SetState (false);
		}
		break;

	case IDR_PRINTMASSTAB:
		m_Masstab.ChangeCurrentIndex(-1);
		m_Masstab.SetText (ltoa (m_actMasstab, m_pInBuff, 10));
		m_RKoord.SetState (false);
		m_RMasstab.SetState (true);
		m_Masstab.SetFocus();
		break;

	case IDB_PRINTFORMATHELP:
		break;

	case IDB_PRINTERSELECTION:	// neuen Drucker aussuchen
		{
			if (!Pars().SetUp())
				break;		// abgebrochen
			
		HRESULT hr = SetNewPrinterData();

			if (FAILED(hr) && E_FAIL != hr)
				break;		// fatal error
			if (!m_PrLayout.Refresh())
				break;
			m_PageSize = Pars().GetPageSize();
			m_DotsPerMM = Pars().GetDotsPerMM();
			MakeCaption();
			fFullReset = false;
		}
	// durchfallen ...

	case IDB_STANDARDSETTINGS:	// Voreinstellungen setzen
		{
			if (fFullReset) {
				m_CBLegende.SetChecked (false);		// Legende
				if (m_fSysMode) {
					m_CBLegendOnly.SetChecked(false);
					m_CBLegendOnly.Disable();
				}
				m_CBRahmen.SetChecked (false);		// Rahmen
				m_CBMasstab.SetChecked (false);		// Maßstab
				m_CBHeadLine.SetChecked (false);	// Überschrift
//				m_HeadLine.SetText ("");
			}

			m_RandLinks.SetValue (10);		// 10 mm Rand Links und Oben
			m_RandOben.SetValue (10);
			m_RandRechts.SetValue (10);
			m_RandUnten.SetValue (10);

			m_SizeX.SetValue (m_PageSize.Width()-20);
			m_SizeY.SetValue (m_PageSize.Height()-20);

			m_actMasstab = 10000L;
			m_Masstab.ChangeCurrentIndex (6);
			
		double X, Y;

			pCT() -> UnScale (m_ocActRect.XMin(), m_ocActRect.YMin(), &X, &Y);

		LPVOID pData = NULL;

//			pCT() -> GetTransformParam (X, Y, &pData);
			pCT() -> TransformEx (&X, &Y, pData);

			pCT() -> CoordTransToStringEx (X, Y, true, m_pInBuff, INBUFFLEN);
			m_ObenRechts.SetText (m_pInBuff);
			pCT() -> CoordTransToStringEx (X, Y, false, m_pInBuff, INBUFFLEN);
			m_UntenHoch.SetText (m_pInBuff);

			m_RKoord.SetState (true);	// RadioButtons
			m_RMasstab.SetState (false);	// default: Masstabseingabe

			pCT() -> UnScale (m_ocActRect.XMax(), m_ocActRect.YMax(), &X, &Y);
			pCT() -> TransformEx (&X, &Y, pData);

			if (NULL != pData) CoTaskMemFree (pData);

			pCT() -> CoordTransToStringEx (X, Y, true, m_pInBuff, INBUFFLEN);
			m_UntenRechts.SetText (m_pInBuff);
			pCT() -> CoordTransToStringEx (X, Y, false, m_pInBuff, INBUFFLEN);
			m_ObenHoch.SetText (m_pInBuff);
			
			EvalMasstab();
			EvalSizeX (false);
			EvalSizeY();
		}
		break;
		
	case IDCB_PRINTLEGENDE:
		EvalSizeX();
		if (m_fSysMode) {
			if (m_CBLegende.isChecked())
				m_CBLegendOnly.Enable();
			else
				m_CBLegendOnly.Disable();
			m_CBLegendOnly.SetChecked (false);
		}
		break;

	case IDCB_PRINTRAHMEN:
		break;

	case IDCB_PRINTHEADLINE:
		EvalSizeY();
		break;
	}	
}

void CPrintLayoutDlg :: ListBoxSel (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {
	case IDC_MASSTAB:
		{
		// Masstab ausgewählt
		short iIndex = m_Masstab.GetCurrentIndex();

			if (iIndex >= 0 && iIndex < CNT_MASSTAB) {
				m_Masstab.SetText (
					ltoa (m_actMasstab = GetMasstab (iIndex), 
					      m_pInBuff, 10
					     )
				);
			} else {
				m_Masstab.ChangeCurrentIndex(-1);
				m_Masstab.SetText (ltoa (m_actMasstab, m_pInBuff, 10));
			}

		// RadioButton umsetzen
			m_RMasstab.SetState (true);
			m_RKoord.SetState (false);

		// Rechte untere Koordinate ändern
			EvalRechtsUnten();
		}
		break;
	}
}

void CPrintLayoutDlg::PostFocus (Control *pCtrl, Control *pCtrlAct)
{
Event e;

	e.Msg() = WM_SETFOCUSTOWINDOW;
	e.WParam() = (WPARAM)pCtrl;
	e.LParam() = (LPARAM)pCtrlAct;
	PostEvent (e);
}

LRESULT CPrintLayoutDlg::Dispatch (Event e)
{
	switch (e.Msg()) {
	case WM_SETFOCUSTOWINDOW:
		((Control *)e.WParam()) -> SetFocus();
		break;
	}

return CPropertyPage::Dispatch(e);
}

void CPrintLayoutDlg::EditFocusChg (EditFocusChgEvt e) 
{
	if (e.gotFocus()) {		
	// EditControl hat Focus erhalten
		switch ((unsigned int)e.GetControlID()) {
		case IDE_HEADLINE:
			m_CBHeadLine.SetChecked (true);
			EvalSizeY();
			break;

		case IDE_PRINTUNTENHOCH:
		case IDE_PRINTUNTENRECHTS:
			m_RMasstab.SetState (false);
			m_RKoord.SetState (true);
			break;

		default:
			break;
		}
		return;
	} else if (((ComboFocusChgEvt &)e).gotFocus()) {	
	// ComboBox hat Focus erhalten
		if (IDC_MASSTAB == (uint)e.GetControlID()) {
			m_RMasstab.SetState (true);
			m_RKoord.SetState (false);
		}
		return;
	}

// Focus verloren
	switch ((unsigned int)e.GetControlID()) {
	case IDE_PRINTFORMATX:
		if (m_SizeX.isModified()) m_SizeX.CopyToSpin();
		break;

	case IDE_PRINTFORMATY:
		if (m_SizeY.isModified()) m_SizeY.CopyToSpin();
		break;

	case IDE_PRINTFORMATLINKS:
		if (m_RandLinks.isModified()) {
			m_RandLinks.CopyToSpin();
			EvalSizeX();
		}
		break;

	case IDE_PRINTFORMATRECHTS:
		if (m_RandRechts.isModified()) {
			m_RandRechts.CopyToSpin();
			EvalSizeX();
		}
		break;

	case IDE_PRINTFORMATUNTEN:
		if (m_RandUnten.isModified()) {
			m_RandUnten.CopyToSpin();
			EvalSizeY();
		}
		break;

	case IDE_PRINTFORMATOBEN:
		if (m_RandOben.isModified()) {
			m_RandOben.CopyToSpin();
			EvalSizeY();
		}
		break;

	case IDE_PRINTUNTENHOCH:
	case IDE_PRINTUNTENRECHTS:
		EvalMasstab();
		break;

	case IDC_MASSTAB:	// MastabsComboBox
		{
			if (0 == m_Masstab.GetTextLen()) {
				PostFocus (&m_Masstab);
				m_Masstab.SetText (ltoa (m_actMasstab, m_pInBuff, 10));
				MessageBeep (MB_ICONASTERISK);
			} else {
				m_Masstab.GetText (m_pInBuff, INBUFFLEN);

			long lNewMasstab = myatol (m_pInBuff);

				if (0 >= lNewMasstab) {
					PostFocus (&m_Masstab);
					m_Masstab.SetText (ltoa (m_actMasstab, m_pInBuff, 10));
					MessageBeep (MB_ICONASTERISK);
				} else {
					m_actMasstab = lNewMasstab;
					EvalSizeX (false);
					EvalSizeY();
				}
			}
		}
		break;
	}
}

void CPrintLayoutDlg :: VertScroll (ScrollEvt e) 
{
	switch ((unsigned int)e.GetScrollBar() -> GetID()) {
	case IDMS_PRINTFORMATX:		// SpinControl betätigt
		m_SizeX.CopyToEdit ();
		break;

	case IDMS_PRINTFORMATY:		// SpinControl betätigt
		m_SizeY.CopyToEdit ();
		break;

	case IDMS_PRINTFORMATLINKS:	// SpinControl betätigt
		m_RandLinks.CopyToEdit ();
		EvalSizeX();
		break;

	case IDMS_PRINTFORMATOBEN:	// SpinControl betätigt
		m_RandOben.CopyToEdit ();
		EvalSizeY();
		break;

	case IDMS_PRINTFORMATRECHTS:	// SpinControl betätigt
		m_RandRechts.CopyToEdit ();
		EvalSizeX();
		break;

	case IDMS_PRINTFORMATUNTEN:	// SpinControl betätigt
		m_RandUnten.CopyToEdit ();
		EvalSizeY();
		break;
	}
}


// sonstige Memberfunktionen --------------------------------------------------
// GetPaperCanvas liefert den Bereich des KartenSpiegels ----------------------
Rectangle *CPrintLayoutDlg :: GetPaperCanvas (void) 
{
// Plausibilitätsprüfung
	if (m_SizeX.GetValue() < 0 || m_SizeY.GetValue() < 0) return NULL;

// Blattränder berücksichtigen
CoOrd iLinks = m_RandLinks.GetValue();
CoOrd iUnten = m_RandUnten.GetValue();

	if (iLinks < 0 || iUnten < 0) return NULL;

CoOrd l = (CoOrd)(iLinks * m_DotsPerMM.Width());
CoOrd r = (CoOrd)((m_SizeX.GetValue()+iLinks) * m_DotsPerMM.Width());
CoOrd b = (CoOrd)(iUnten * m_DotsPerMM.Height());
CoOrd t = (CoOrd)((m_SizeY.GetValue()+iUnten) * m_DotsPerMM.Height());

return new Rectangle (t, l, b, r);
}

// GetExtend liefert den Bereich der auszugebenden Karte in KartenKoordinaten
ObjContainer *CPrintLayoutDlg :: GetExtend (void) 
{
// Werte einlesen und in Eckpunkte umwandeln
double lx, ly, rx, ry;
	
	if (!GetValue (m_ObenRechts, lx, m_ObenHoch, ly))
		return NULL;

// RealKoordinaten in DB-Koordinaten umrechnen
LPVOID pData = NULL;

//	pCT() -> GetInvTransformParam (lx, ly, &pData);
	pCT() -> InvTransformEx (&lx, &ly, pData);

	if (m_RMasstab.GetState()) {
	// Maßtabsbezogene Formatbestimmung
	short iIndex = m_Masstab.GetCurrentIndex();
	long lMasstab = 0L;

		if (iIndex == -1) {
		// nutzerdefinierter Maßstab

			m_Masstab.GetText (m_pInBuff, INBUFFLEN);
			lMasstab = myatol (m_pInBuff);
		} else {
		// vorgebener Maßstab
			lMasstab = GetMasstab (iIndex);
		}
		if (lMasstab == 0L) return NULL;

	// Plausibilitätsprüfung
		if (m_SizeX.GetValue() < 0 || m_SizeY.GetValue() < 0) return NULL;

	// Größe des Kartenspiegels besorgen
	DoublePair Delta (((double)lMasstab * m_SizeX.GetValue())/1000.0,
			  -((double)lMasstab * m_SizeY.GetValue())/1000.0);
	DoublePair PIn (lx, ly);
	DoublePair POut;

	// zweiten Eckpunkt berechnen
		pCT() -> CoordTransRectangle (&PIn, &Delta, &POut);

		rx = POut.X();
		ry = POut.Y();
	} else {
	// rechte untere Ecke gegeben
		if (!GetValue (m_UntenRechts, rx, m_UntenHoch, ry))
			return NULL;	// Eingabe unvollständig

		pCT() -> InvTransformEx (&rx, &ry, pData);
	}

	if (NULL != pData) CoTaskMemFree (pData);

// Eckpunkte umrechnen
ObjContainer *pOC = new ObjContainer;

	if (pOC) {
	// Eckpunkte umrechnen
		pCT() -> Scale (lx, ry, &(pOC -> XMin()), &(pOC -> YMin()));
		pCT() -> Scale (rx, ly, &(pOC -> XMax()), &(pOC -> YMax()));

	// Rechteck evtl. kippen
		if (pOC -> XMin() > pOC -> XMax()) {
		KoOrd tmp = pOC -> XMin();

			pOC -> XMin() = pOC -> XMax();
			pOC -> XMax() = tmp;
		}
		if (pOC -> YMin() > pOC -> YMax()) {
		KoOrd tmp = pOC -> YMin();

			pOC -> YMin() = pOC -> YMax();
			pOC -> YMax() = tmp;
		}
	}

return pOC;
}

// GetMasstab rechnet den ComboBoxIndex in einen Maßstab um -------------------
long CPrintLayoutDlg :: GetMasstab (short iIndex) 
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

// Berechnung der Grööße des KartenSpiegels in Abhängigkeit der anderen Bereiche
void CPrintLayoutDlg :: EvalSizeX (bool fRecalc) 
{
	if (!m_isValid) return;

CoOrd lSizeX = m_PageSize.Width() - m_RandLinks.GetValue()
				  - m_RandRechts.GetValue();

	if (m_CBLegende.isChecked()) {
	long lLegSizeX = m_PrLayout.LegendeBreite(lSizeX/5, lSizeX);

		lSizeX -= CoOrd(lLegSizeX);	// LegendenGröße ist gegeben (Default1/5)
	}
	m_SizeX.SetValue (short(lSizeX));

	if (fRecalc) {
		if (m_RMasstab.GetState()) EvalRechtsUnten();
		if (m_RKoord.GetState()) EvalMasstab();
	}
}

void CPrintLayoutDlg :: EvalSizeY (void) 
{
	if (!m_isValid) return;

CoOrd SizeY = m_PageSize.Height() - m_RandOben.GetValue()
				  - m_RandUnten.GetValue();

long iHL = m_CBLegende.isChecked() ? m_PrLayout.UeberschriftTyp(0) : 0;

	if (m_CBHeadLine.isChecked() && (0 == iHL))
		SizeY = (CoOrd)((SizeY*97L)/100L);	// Überschrift 3% der Höhe

	m_SizeY.SetValue (short(SizeY));
	
	if (m_RMasstab.GetState()) EvalRechtsUnten();
	if (m_RKoord.GetState()) EvalMasstab();
}

void CPrintLayoutDlg :: EvalRechtsUnten (void) 
{
// Linke obere Koordinate holen
double lx, ly;

	if (!GetValue (m_ObenRechts, lx, m_ObenHoch, ly))
		return;

	pCT() -> InvTransform (&lx, &ly);

short iIndex = m_Masstab.GetCurrentIndex();
long lMasstab = 0L;

	if (iIndex == -1) {
	// nutzerdefinierter Maßstab

		m_Masstab.GetText (m_pInBuff, INBUFFLEN);
		lMasstab = myatol (m_pInBuff);
	} else {
	// vorgebener Maßstab
		lMasstab = GetMasstab (iIndex);
	}
	if (lMasstab == 0L) return;
	m_actMasstab = lMasstab;
	
// Plausibilitätsprüfung
	if (m_SizeX.GetValue() < 0 || m_SizeY.GetValue() < 0) return;

// Größe des Kartenspiegels besorgen
DoublePair Delta (((double)lMasstab * m_SizeX.GetValue())/1000.0,
				  -((double)lMasstab * m_SizeY.GetValue())/1000.0);
DoublePair PIn (lx, ly);
DoublePair POut;

// zweiten Eckpunkt berechnen
	pCT() -> CoordTransRectangle (&PIn, &Delta, &POut);

// zurückschreiben
LPVOID pData = NULL;

//	pCT() -> GetTransformParam (PIn.X(), PIn.Y(), &pData);
	pCT() -> TransformEx (&POut, 1, pData);
	if (NULL != pData) CoTaskMemFree (pData);

	pCT() -> CoordTransToStringEx (POut.X(), POut.Y(), true, m_pInBuff, INBUFFLEN);
	m_UntenRechts.SetText (m_pInBuff);
	pCT() -> CoordTransToStringEx (POut.X(), POut.Y(), false, m_pInBuff, INBUFFLEN);
	m_UntenHoch.SetText (m_pInBuff);
}


// Masstab nachführen, wenn rechte untere Koordinate verändert wird -----------
void CPrintLayoutDlg :: EvalMasstab (void)
{
// Seitenverhältnis von Bild und Bildausschnitt berechnen
double lx, ly, rx, ry;

	if (!GetValue (m_ObenRechts, lx, m_ObenHoch, ly) ||
	    !GetValue (m_UntenRechts, rx, m_UntenHoch, ry))
		return;

LPVOID pData = NULL;

//	pCT() -> GetInvTransformParam (lx, ly, &pData);
	pCT() -> InvTransformEx (&lx, &ly, pData);
	pCT() -> InvTransformEx (&rx, &ry, pData);
	if (NULL != pData) CoTaskMemFree (pData);

DoublePair LO (lx, ly);
double dX = 0.0;
double dY = 0.0;

	if (pCT() -> hasDistEx()) {// z.B. bei geodätischen Koord Besonderheiten
	DoublePair RU (rx, ry);

		pCT() -> CoordTransDistanceEx (&LO, &RU, dX, dY);
	} else {
	DoublePair RO (rx, ly);
	DoublePair LU (lx, ry);

		dX = pCT() -> CoordTransDistance (&LO, &RO);
		dY = pCT() -> CoordTransDistance (&LO, &LU);
	}

double kBild = dX != 0.0 ? fabs (dY / dX) : 1.0;
short sizeX = m_SizeX.GetValue();
short sizeY = m_SizeY.GetValue();
double kBAus = sizeX != 0 ? fabs (double (sizeY)/double (sizeX)) : 1.0;

// Maástab ausrechnen
long lMasstab = m_actMasstab;

	if (kBild > kBAus) {
	// Maßstab aus Y-Koordinate ausrechnen
		if (sizeY != 0)
			lMasstab = long((fabs (dY) * 1000.0) / double (sizeY));
	} else {
	// Maßstab aus X-Koordinate ausrechnen
		if (sizeX != 0)
			lMasstab = long((fabs (dX) * 1000.0) / double (sizeX));
	}

// Maßstab anzeigen
	if (lMasstab != m_actMasstab) {
		m_actMasstab = lMasstab;
 		m_Masstab.ChangeCurrentIndex(-1);
		m_Masstab.SetText (ltoa (m_actMasstab, m_pInBuff, 10));
	}
}


// Layout der Druckseite in einer Struktur zusammenstellen --------------------
PrintLayout *CPrintLayoutDlg :: GetLayout (void) 
{
PrintLayout *lpPL = new PrintLayout();

	if (lpPL == NULL) return NULL;

// Struktur füllen
	lpPL -> m_plRcSpiegel = GetPaperCanvas();
	lpPL -> m_plOCSpiegel = GetExtend();
	lpPL -> m_plFullRect = GetFullRect();
	lpPL -> m_plfsRahmen = GetFrameType();
	lpPL -> m_pllsLegende = GetLegendType();
	lpPL -> m_plRcLegende = GetLegendeRect();
	lpPL -> m_pliHeadLine = GetHeadLineFlag();
	lpPL -> m_pllpHeadLine = GetHeadLine();
	lpPL -> m_plRcHeadLine = GetHeadLineRect();
	lpPL -> m_plmsMasstab = GetMasstabType();
	lpPL -> m_plRcMasstab = GetMasstabRect();
	lpPL -> m_lMasstab = m_actMasstab;
	lpPL -> m_plrcPageSize = GetPageSize();
	lpPL -> m_plrcPageBase = GetPageBase();
	lpPL -> m_plRcLogo = GetLogoRect();

	for (int i = 0; i < MAX_LOGOFELD; i++)
		lpPL -> m_plRcFirmLogo[i] = GetFirmLogoRect(i+1);

	lpPL -> m_fLegendOnly = m_fSysMode ? m_CBLegendOnly.isChecked() : false;

return lpPL;
}

// Destruktor für PrintLayoutStruktur -----------------------------------------
PrintLayout :: ~PrintLayout (void) 
{
	DELETE (m_plRcSpiegel);
	DELETE (m_plOCSpiegel);
	DELETE (m_plFullRect);
	DELETE (m_plRcLegende);
	DELETE (m_pllpHeadLine);
	DELETE (m_plRcHeadLine);
	DELETE (m_plRcMasstab);
	DELETE (m_plrcPageSize);
	DELETE (m_plrcPageBase);
	DELETE (m_plRcLogo);
	for (int i = 0; i < MAX_LOGOFELD; i++)
		DELETE (m_plRcFirmLogo[i]);
}

// Private Member des Dialogfensters zur Berechnung der Größen der einzelnen
// Bereiche
char *CPrintLayoutDlg :: GetHeadLine (void)  
{
	if (!m_CBHeadLine.isChecked())
		return NULL;

	if (m_HeadLine.GetTextLen() == 0)
		return NULL;

	m_HeadLine.GetText (m_pInBuff, HEADLINELENGTH);
	return StrDup (m_pInBuff, RC_GetHeadLine);
}

Rectangle *CPrintLayoutDlg :: GetHeadLineRect (void)
{
	if (!m_CBHeadLine.isChecked())
		return NULL;

long iHL = m_CBLegende.isChecked() ? m_PrLayout.UeberschriftTyp(0) : 0;

	if (0 == iHL) {
	// Überschrift über gesamte Breite
	long lPageWidth = m_PageSize.Width();

		if (m_fSysMode && m_CBLegendOnly.isChecked())
			lPageWidth -= m_SizeX.GetValue();

		return new Rectangle (
			(CoOrd)((m_PageSize.Height() - m_RandOben.GetValue()) * m_DotsPerMM.Height()),
			(CoOrd)(m_RandLinks.GetValue() * m_DotsPerMM.Width()),
			(CoOrd)((m_RandUnten.GetValue() + m_SizeY.GetValue()) * m_DotsPerMM.Height()),
			(CoOrd)((lPageWidth - m_RandRechts.GetValue()) * m_DotsPerMM.Width())
		);
	} else if (m_CBLegende.isChecked()) {
	long lHeight = m_PageSize.Height() - m_RandOben.GetValue() - m_RandUnten.GetValue();
	long lWidth = m_PageSize.Width() - m_RandRechts.GetValue() - m_RandLinks.GetValue();
	long lHeightHL = m_PrLayout.UeberschriftHoehe (20, lHeight);
	long lWidthHL = m_PrLayout.UeberschriftBreite (20, lWidth);
	long lLinks = (m_fSysMode && m_CBLegendOnly.isChecked()) ? 0 : m_SizeX.GetValue();

		return new Rectangle (
			(CoOrd)((m_PageSize.Height() - m_RandOben.GetValue()) * m_DotsPerMM.Height()),
			(CoOrd)((m_RandLinks.GetValue() + lLinks) * m_DotsPerMM.Width()),
			(CoOrd)((m_PageSize.Height() - m_RandOben.GetValue() - lHeightHL) * m_DotsPerMM.Height()),
			(CoOrd)((m_RandLinks.GetValue() + lLinks + lWidthHL) * m_DotsPerMM.Width())
		);
	}

return NULL;	// kein Logo
}


Rectangle *CPrintLayoutDlg :: GetMasstabRect (void)
{
	if (!m_CBMasstab.isChecked())
		return NULL;

long lHeight = m_PageSize.Height() - m_RandOben.GetValue() - m_RandUnten.GetValue();
short iMRect = (short)m_PrLayout.MasstabHoehe(20, lHeight);

long lLinks = m_SizeX.GetValue();
long lPageWidth = m_PageSize.Width();
CoOrd lSizeX = CoOrd(lPageWidth - m_RandLinks.GetValue() - m_RandRechts.GetValue());
long lLegSizeX = m_PrLayout.LegendeBreite (lSizeX/5, lSizeX);
long lBottom = GetFirmLogoHeight (lHeight);

	if (m_fSysMode && m_CBLegendOnly.isChecked())	{
		lPageWidth -= lLinks;
		lLinks = 0;
	}

	return new Rectangle (
			(CoOrd)((lBottom + iMRect) * m_DotsPerMM.Height()),
//			(CoOrd)((m_RandLinks.GetValue() + lLinks) * m_DotsPerMM.Width()),
			(CoOrd)((lPageWidth - m_RandRechts.GetValue() - lLegSizeX) * m_DotsPerMM.Width()),
			(CoOrd)(lBottom * m_DotsPerMM.Height()),
			(CoOrd)((lPageWidth - m_RandRechts.GetValue()) * m_DotsPerMM.Width())
		   );
}

Rectangle *CPrintLayoutDlg :: GetLegendeRect (void)
{
	if (!m_CBLegende.isChecked())
		return NULL;

long lHeight = m_PageSize.Height() - m_RandOben.GetValue() - m_RandUnten.GetValue();
long lHeightHL = (m_CBHeadLine.isChecked() && m_PrLayout.UeberschriftTyp(0)) ? 
			m_PrLayout.UeberschriftHoehe (20, lHeight) : 0;
short iMRect = m_CBMasstab.isChecked() ? 
			(short)m_PrLayout.MasstabHoehe(20, lHeight) : 0;
long lLinks = m_SizeX.GetValue();
long lPageWidth = m_PageSize.Width();

	if (m_fSysMode && m_CBLegendOnly.isChecked())	{
		lLinks = 0;
		lPageWidth -= m_SizeX.GetValue();
	}

long lBottom = GetFirmLogoHeight (lHeight);

	return new Rectangle (
			(CoOrd)((m_RandUnten.GetValue() + m_SizeY.GetValue() - lHeightHL) * m_DotsPerMM.Height()),
			(CoOrd)((m_RandLinks.GetValue() + lLinks) * m_DotsPerMM.Width()),
			(CoOrd)((lBottom + iMRect) * m_DotsPerMM.Height()),
			(CoOrd)((lPageWidth - m_RandRechts.GetValue()) * m_DotsPerMM.Width())
		   );
}


Rectangle *CPrintLayoutDlg :: GetLogoRect (void)
{
	if (!m_CBHeadLine.isChecked())
		return NULL;

long iHL = m_CBLegende.isChecked() ? m_PrLayout.UeberschriftTyp(0) : 0;

	if (0 == iHL) {
		return NULL;
	} else if (m_CBLegende.isChecked()) {
	long lHeight = m_PageSize.Height() - m_RandOben.GetValue() - m_RandUnten.GetValue();
	long lWidth = m_PageSize.Width() - m_RandRechts.GetValue() - m_RandLinks.GetValue();
	long lHeightHL = m_PrLayout.UeberschriftHoehe (20, lHeight);
	long lWidthHL = m_PrLayout.UeberschriftBreite (20, lWidth);

	long lLeft = m_RandLinks.GetValue() + ((m_fSysMode && m_CBLegendOnly.isChecked()) ? 0 : m_SizeX.GetValue()) + lWidthHL;
	long lRight = m_PageSize.Width() - m_RandRechts.GetValue() - ((m_fSysMode && m_CBLegendOnly.isChecked()) ? m_SizeX.GetValue() : 0);

		if (lRight <= lLeft) return NULL; 	// kein LogoBereich gegeben

		return new Rectangle (
			(CoOrd)((m_PageSize.Height() - m_RandOben.GetValue()) * m_DotsPerMM.Height()),
			(CoOrd)(lLeft * m_DotsPerMM.Width()),
			(CoOrd)((m_PageSize.Height() - m_RandOben.GetValue() - lHeightHL) * m_DotsPerMM.Height()),
			(CoOrd)(lRight * m_DotsPerMM.Width())
		);
	}

return NULL;	// keine Überschrift
}


Rectangle *CPrintLayoutDlg :: GetFullRect (void)
{
long lPageWidth = m_PageSize.Width();

	if (m_fSysMode && m_CBLegendOnly.isChecked())	
		lPageWidth -= m_SizeX.GetValue();

	return new Rectangle (
			(CoOrd)((m_PageSize.Height() - m_RandOben.GetValue()) * m_DotsPerMM.Height()),
			(CoOrd)(m_RandLinks.GetValue() * m_DotsPerMM.Width()),
			(CoOrd)(m_RandUnten.GetValue() * m_DotsPerMM.Height()),
			(CoOrd)((lPageWidth - m_RandRechts.GetValue()) * m_DotsPerMM.Width())
		   );
}


Rectangle *CPrintLayoutDlg :: GetPageSize (void)
{
long lPageWidth = m_PageSize.Width();

	if (m_fSysMode && m_CBLegendOnly.isChecked())	
		lPageWidth -= m_SizeX.GetValue();

	return new Rectangle (
			(CoOrd)(m_PageSize.Height() * m_DotsPerMM.Height()), 
			0, 
			0,
			(CoOrd)(lPageWidth * m_DotsPerMM.Width())
		   );
}


Rectangle *CPrintLayoutDlg :: GetPageBase (void)
{
	return new Rectangle (
			(CoOrd)(m_PageSize.Height() * m_DotsPerMM.Height()), 
			0, 
			0,
			(CoOrd)(m_PageSize.Width() * m_DotsPerMM.Width())
		   );
}

Rectangle *CPrintLayoutDlg :: GetFirmLogoRect (int iCnt)
{
	TX_ASSERT (0 < iCnt && MAX_LOGOFELD >= iCnt);

long lHeight = m_PageSize.Height() - m_RandOben.GetValue() - m_RandUnten.GetValue();
long lHoehe = m_PrLayout.LogoHoehe (0, lHeight, iCnt);

	if (0 == lHoehe) return NULL;	// nicht gegeben

long lBottom = m_RandUnten.GetValue();

	for (int i = 1; i < iCnt; i++)
		lBottom += m_PrLayout.LogoHoehe (0, lHeight, i);

long lLinks = m_SizeX.GetValue();
long lPageWidth = m_PageSize.Width();

CoOrd lSizeX = CoOrd(lPageWidth - m_RandLinks.GetValue() - m_RandRechts.GetValue());
long lLegSizeX = m_PrLayout.LegendeBreite(lSizeX/5, lSizeX);

	if (m_fSysMode && m_CBLegendOnly.isChecked())	{
		lLinks = 0;
		lPageWidth -= m_SizeX.GetValue();
	}

	return new Rectangle (
		(CoOrd)((lBottom + lHoehe) * m_DotsPerMM.Height()),
//		(CoOrd)((m_RandLinks.GetValue() + lLinks) * m_DotsPerMM.Width()),
		(CoOrd)((lPageWidth - m_RandRechts.GetValue() - lLegSizeX) * m_DotsPerMM.Width()),
		(CoOrd)(lBottom * m_DotsPerMM.Height()),
		(CoOrd)((lPageWidth - m_RandRechts.GetValue()) * m_DotsPerMM.Width())
	);
}


long CPrintLayoutDlg :: GetFirmLogoHeight (long lHeight)
{
long lBottom = m_RandUnten.GetValue();

	for (int i = 1; i < 10; i++) {
	long lH = m_PrLayout.LogoHoehe (0, lHeight, i);

		if (0 == lH) break;
		lBottom += lH;
	}

return lBottom;
}

// Einlesen und Transformieren in eine Zahlendarstellung einer Koordinate -----
bool CPrintLayoutDlg :: GetValue (DoubleNumEdit &dblNEDX, double &dblX, 
				 DoubleNumEdit &dblNEDY, double &dblY)
{
	if (dblNEDX.GetTextLen() > 0 && dblNEDY.GetTextLen() > 0) {
	char cbBuffer[INBUFFLEN+1];

		dblNEDX.GetText (m_pInBuff, INBUFFLEN);
		dblNEDY.GetText (cbBuffer, INBUFFLEN);
		return pCT() -> CoordTransToValueEx (m_pInBuff, cbBuffer, dblX, dblY);
	}
	dblX = 0.0;
	dblY = 0.0;

return false;
}

long myatol (const char *lpStr) 
{
long lRes = 0L;

	while (*lpStr) {
		if (isdigit (*lpStr)) 
			lRes = 10*lRes + *lpStr - '0';
		lpStr++;
	}

return lRes;
}

// Caption für dieses Fenster generieren --------------------------------------
void CPrintLayoutDlg :: MakeCaption (void)
{
LPCSTR pcPort = Pars().PortName();
LPCSTR pcDevice = Pars().DeviceName();

	if (NULL != pcPort && NULL != pcDevice) {
	ResString resCaption (IDS_PRNTLAYOUTCAPTION, 64);
	
		wsprintf (m_pInBuff, resCaption, pcDevice, pcPort);
		GetParent() -> SetCaption (m_pInBuff);
	} else {
	ResString resCaption (IDS_PRNTLAYOUTCAPTION_NOPRINTER, 64);

		GetParent() -> SetCaption (resCaption);
	}
}

///////////////////////////////////////////////////////////////////////////////
// DataObject abliefern, welches DVTARGETDEVICE enthält 
HRESULT CPrintLayoutDlg::GetDataObject (IDataObject **ppIDO)
{
	if (NULL == ppIDO) return E_POINTER;

// beim ersten mal evtl. neu anlegen und füllen
	if (NULL == (IDataObject *)m_DataObj) { 
		try {
			m_DataObj = WDataObject (CLSID_DataTransferObject);		// throws hr
			THROW_FAILED_HRESULT(SetNewPrinterData());

		} catch (_com_error& hr) {
			return _COM_ERROR(hr);
		}
	}

// aber immer DataObject liefern
	if (NULL != (IDataObject *)m_DataObj) {
		*ppIDO = (IDataObject *)m_DataObj;
		(*ppIDO) -> AddRef();
		return S_OK;
	}

	return E_FAIL;
}

HRESULT CPrintLayoutDlg::SetNewPrinterData (void)
{
	if (NULL == (IDataObject *)m_DataObj)
		return E_UNEXPECTED;

HGLOBAL hTD = NULL;
DVTARGETDEVICE *ptdNew = NULL;

	try {
	DVTARGETDEVICE *ptd = m_rPP.GetTargetDevice();

		if (NULL == ptd) _com_issue_error(E_FAIL);		// Drucker existiert nicht

		hTD = GlobalAlloc (GHND, ptd->tdSize);
		if (NULL == hTD) _com_issue_error(E_OUTOFMEMORY);
		ptdNew = (DVTARGETDEVICE *)GlobalLock (hTD);
		if (NULL == ptdNew) _com_issue_error(E_OUTOFMEMORY);

		memcpy (ptdNew, ptd, ptd->tdSize);
		GlobalUnlock (hTD);
		ptdNew = NULL;

	STGMEDIUM stg;

		stg.tymed = TYMED_HGLOBAL;
		stg.hGlobal = hTD;
		stg.pUnkForRelease = NULL;
		THROW_FAILED_HRESULT(m_DataObj -> SetData ((FORMATETC *)&g_cfeActPrinter, &stg, true));

	} catch (_com_error& hr) {
		if (NULL != ptdNew) 
			GlobalUnlock(hTD);
		if (NULL != hTD) 
			GlobalFree (hTD);
		return _COM_ERROR(hr);
	}

return S_OK;
}
