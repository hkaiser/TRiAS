// Dialogfenster um Selektion zu korrigieren ----------------------------------
// File: SELECTN.HXX

#include "triaspre.hxx"
#include "triasres.h"

#include <ctf.hxx>
#include "selectn.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#pragma warning (disable:4355)

CSelectRectDlg :: CSelectRectDlg (pWindow pW, CoordTrans *pCT, DragRectangleObject &rDRO)
		: DialogWindow (pW, IDD_SELECTRECT),
		  m_dneObenHochWert (this, IDE_OBENHOCHWERT),
		  m_dneObenRechtsWert (this, IDE_OBENRECHTSWERT),
		  m_dneUntenHochWert (this, IDE_UNTENHOCHWERT),
		  m_dneUntenRechtsWert (this, IDE_UNTENRECHTSWERT),
		  m_pCT(pCT), m_RC(0, 0, 0, 0), m_rDRO(rDRO),
		  m_fRemoveOnEnd(false)
{
	TX_ASSERT (m_pCT);

// NumEdits initialisieren
	m_dneObenHochWert.SetNumEditMode (NumEdit :: NEM_NoTest);
	m_dneObenRechtsWert.SetNumEditMode (NumEdit :: NEM_NoTest);
	m_dneUntenHochWert.SetNumEditMode (NumEdit :: NEM_NoTest);
	m_dneUntenRechtsWert.SetNumEditMode (NumEdit :: NEM_NoTest);

// Ausgangsbereich festlegen, Koordinaten kippen
Rectangle rc = m_rDRO.GetRect();
	
	rc.Bottom() = CoOrd(2*rc.Top() - rc.Bottom());

// Koordinaten in DB-Koordinaten umsetzen
Punkt PtMin = DCtoOC (rc.Left(), rc.Bottom());       // Device --> Objekt
Punkt PtMax = DCtoOC (rc.Right(), rc.Top());
double dXMin, dXMax, dYMin, dYMax;
		
// Koordinaten transformieren (incl. rausrechnen der internen Skalierung)
#if defined(WIN32)
LPVOID pData = NULL;

	m_pCT -> UnScale (PtMin, &dXMin, &dYMin);
//	m_pCT -> GetTransformParam (dXMin, dYMin, &pData);
	m_pCT -> TransformEx (&dXMin, &dYMin, pData);
	m_pCT -> UnScale (PtMax, &dXMax, &dYMax);
	m_pCT -> TransformEx (&dXMax, &dYMax, pData);
	if (NULL != pData) CoTaskMemFree (pData);
#else
	m_pCT -> UnScale (PtMin, &dXMin, &dYMin);
	m_pCT -> Transform (&dXMin, &dYMin);
	m_pCT -> UnScale (PtMax, &dXMax, &dYMax);
	m_pCT -> Transform (&dXMax, &dYMax);
#endif // WIN32

// Anfangswerte in Controls schreiben
char cbBuffer[64];

	m_pCT -> CoordTransToStringEx (dXMax, dYMax, false, cbBuffer, sizeof(cbBuffer));
	m_dneObenHochWert.SetText (cbBuffer);
	m_pCT -> CoordTransToStringEx (dXMin, dYMin, true, cbBuffer, sizeof(cbBuffer));
	m_dneObenRechtsWert.SetText (cbBuffer);
	m_pCT -> CoordTransToStringEx (dXMin, dYMin, false, cbBuffer, sizeof(cbBuffer));
	m_dneUntenHochWert.SetText (cbBuffer);
	m_pCT -> CoordTransToStringEx (dXMax, dYMax, true, cbBuffer, sizeof(cbBuffer));
	m_dneUntenRechtsWert.SetText (cbBuffer);

	ReadResults (m_RC);		// wieder einlesen

// Position dieses Fensters korrigieren
	CorrectPosition();
}

#pragma warning (default:4355)

CSelectRectDlg :: ~CSelectRectDlg (void)
{
}

void CSelectRectDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		if (ReadResults (m_RC)) {
			if (m_fRemoveOnEnd)
				GetParent() -> Draw (&m_rDRO);	// altes ausblenden
			m_rDRO.SetRect (GetPt(m_RC), GetDim(m_RC));
			EndDlg(1);
		}
		break;

	case IDCANCEL:
	// DRO rücksetzen
		GetParent() -> Draw (&m_rDRO);		// altes ausblenden
		m_rDRO.SetRect (GetPt(m_RC), GetDim(m_RC));
		EndDlg(0);
		break;
	}
}

void CSelectRectDlg :: EditFocusChg (EditFocusChgEvt e)
{
	if (e.gotFocus()) return;	// nur LostFocus bearbeiten

Rectangle rc;

	if (!ReadResults(rc)) return;

// neue Werte in DragRectangle setzen und zeichnen
	GetParent() -> Draw (&m_rDRO);		// altes ausblenden
	m_rDRO.SetRect (GetPt(rc), GetDim(rc));
	GetParent() -> Draw (&m_rDRO);		// neues zeichnen
}


// Eingabewerte holen ---------------------------------------------------------
inline void CondSwap (KoOrd &rlXMin, KoOrd &rlXMax)
{
	if (rlXMin > rlXMax) {
	KoOrd temp = rlXMax;

		rlXMax = rlXMin;
		rlXMin = temp;
	}
}


bool CSelectRectDlg :: ReadResults (Rectangle &rRC)
{
double dXMin, dXMax, dYMin, dYMax;

	if (!GetValue (m_dneObenRechtsWert, dXMin, m_dneObenHochWert, dYMax) ||
	    !GetValue (m_dneUntenRechtsWert, dXMax, m_dneUntenHochWert, dYMin))
	{
		MessageBeep (MB_ICONEXCLAMATION);
		return false;
	}

// Werte aus  NumEdits einlesen und konvertieren
KoOrd lXMin, lXMax, lYMin, lYMax;

#if defined(WIN32)
LPVOID pData = NULL;

//	m_pCT -> GetInvTransformParam (dXMin, dYMin, &pData);
	m_pCT -> InvTransformEx (&dXMin, &dYMin, pData);
	m_pCT -> InvTransformEx (&dXMax, &dYMax, pData);
	if (NULL != pData) CoTaskMemFree (pData);
#else
	m_pCT -> InvTransform (&dXMin, &dYMin);
	m_pCT -> InvTransform (&dXMax, &dYMax);
#endif // WIN32

	m_pCT -> Scale (dXMin, dYMin, &lXMin, &lYMin);
	m_pCT -> Scale (dXMax, dYMax, &lXMax, &lYMax);

// Korrektur des neues Ausschnittes (kippen)
	CondSwap (lXMin, lXMax);
	CondSwap (lYMin, lYMax);

// in Bildschrimkoordinaten umrechnen
Point Pt1 = OCtoDC (lXMin, lYMax);
Point Pt2 = OCtoDC (lXMax, lYMin);

	rRC = Rectangle (Pt1, Pt2);

return true;
}

#define BOUND(x,min,max) ((x)<(min)?(min):((x)>(max)?(max):(x)))

void CSelectRectDlg::CorrectPosition (void)
{
Rectangle rc = WindowRect();
Rectangle rcP = GetParent() -> CanvasRect();
Point pt;
int dX = GetSystemMetrics (SM_CXSCREEN);
int dY = GetSystemMetrics (SM_CYSCREEN);

	pt.X() = min(m_RC.Right(), rcP.Right() - (rc.Right()-rc.Left()));
	pt.Y() = max(m_RC.Bottom() - (rc.Top()-rc.Bottom()), rcP.Bottom());
	pt.X() = BOUND(pt.X(), 0, dX);
	pt.Y() = BOUND(pt.Y(), rc.Top()-rc.Bottom(), dY);

	ChangePosition (pt);
}

// Einlesen und Transformieren in eine Zahlendarstellung einer Koordinate -----
bool CSelectRectDlg :: GetValue (DoubleNumEdit &dblNEDX, double &dblX, 
				 DoubleNumEdit &dblNEDY, double &dblY)
{
char cbBuffer1[64];
char cbBuffer2[64];

	if (dblNEDX.GetTextLen() > 0 && dblNEDY.GetTextLen() > 0) {
		dblNEDX.GetText (cbBuffer1, sizeof(cbBuffer1));
		dblNEDY.GetText (cbBuffer2, sizeof(cbBuffer2));
		return m_pCT -> CoordTransToValueEx (cbBuffer1, cbBuffer2, dblX, dblY);
	}
	dblX = 0.0;
	dblY = 0.0;

return false;
}


