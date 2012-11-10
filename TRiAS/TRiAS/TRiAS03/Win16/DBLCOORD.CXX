// Zwei EditControls für ein Koordinatenpaar ----------------------------------
// File: DBLCOORD.CXX

#include "trias03p.hxx"

#include <dblcoord.hxx>

CCoordPairEdit ::
CCoordEdit :: CCoordEdit (pDialogWindow pW, ResID resID, CCoordPairEdit *pCPE)
	    : DoubleNumEdit (pW, resID)
{
	m_pCPE = pCPE;
}

CCoordPairEdit :: CCoordEdit :: ~CCoordEdit (void)
{
	// nothing else to do
}

void CCoordPairEdit :: CCoordEdit :: FocusChange (FocusChangeEvt e)
{
	if (!e.gotFocus() && m_NEM == NEM_Test) {	// wenn Focus verloren geht
		if (!m_pCPE -> Validate()) {
			MessageBeep (MB_ICONEXCLAMATION);
			SetFocus();
		}
/*
	// ------------------------------------------------------------------
		if (LOWORD(GetVersion()) >= 0x030a) {
			SendMessage (GetParent() -> Handle(), 
				    WM_COMMAND, GetID(), 
				    MAKELONG (Handle (), EN_KILLFOCUS));
		}
	// ------------------------------------------------------------------
*/
	}
	ControlWindow :: FocusChange (e);	// und weiterleiten
}

#pragma warning(disable: 4355)

EXPORT03
CCoordPairEdit :: CCoordPairEdit (pDialogWindow pW, CoordTrans &rCTF, 
				  ResID resX, ResID resY) 
		: m_EditX (pW, resX, this), m_EditY (pW, resY, this),
		  m_rCTF(rCTF)
{
	m_dX = 0.0;
	m_dY = 0.0;
}

#pragma warning(default: 4355)

EXPORT03 CCoordPairEdit :: ~CCoordPairEdit (void)
{
	// nothing else to do
}

bool EXPORT03 CCoordPairEdit :: Validate (void)
{
double X, Y;

	return GetValues (X, Y, true);
}

bool EXPORT03 CCoordPairEdit :: GetValues (double &rX, double &rY, bool fCorrect)
{
	if (m_EditX.GetTextLen() > 0 && m_EditY.GetTextLen() > 0) {
	char cbBufferX[_MAX_PATH+1];
	char cbBufferY[_MAX_PATH+1];

		m_EditX.GetText (cbBufferX, _MAX_PATH);
		m_EditY.GetText (cbBufferY, _MAX_PATH);
		if (m_rCTF.CoordTransToValueEx (cbBufferX, cbBufferY, rX, rY)) {
			m_dX = rX;
			m_dY = rY;
			return true;
		}
	} 
// Fehler, alte Werte wieder einstellen
	rX = m_dX;
	rY = m_dY;
	if (fCorrect) SetValues (rX, rY);

return false;
}

bool EXPORT03 CCoordPairEdit :: SetValues (double dX, double dY)
{
char cbBuffer[_MAX_PATH+1];

	m_rCTF.CoordTransToStringEx (dX, dY, true, cbBuffer, _MAX_PATH);
	m_EditX.SetText (cbBuffer);
	m_rCTF.CoordTransToStringEx (dX, dY, false, cbBuffer, _MAX_PATH);
	m_EditY.SetText (cbBuffer);

	m_dX = dX;
	m_dY = dY;

return true;
}

