// Memberfunktionen fuer DoubleNumEdit ----------------------------------------
// File: DBLNUMED.CXX

#include "trias03p.hxx"

#include <funcs02.h>
#include <numedit.hxx>
#include <dblnumed.hxx>

// Konstruktoren ---------------------------------------------------------------
EXPORT03 
DoubleNumEdit :: DoubleNumEdit (pDialogWindow p, ResID r)
	       : NumEdit (p, r, 10)
{
	m_NEM = NEM_NoTest;
	m_dblMin = 0.0;
	m_dblMax = 0.0;
}

EXPORT03 
DoubleNumEdit :: DoubleNumEdit (pWindow pW, uint id, Point p, Dimension d)
	       : NumEdit (pW, id, p, d, 10)
{
	m_NEM = NEM_NoTest;
	m_dblMin = 0.0;
	m_dblMax = 0.0;
}

// neuer KeyEvent - Handler für DoubleEingabe ---------------------------------
void EXPORT03 DoubleNumEdit :: KeyDown (KeyEvt e) 
{
char c = e.ASCIIChar();

	if (c == '.' || c == '\'' || c == '\"' || c == '°') {
		Default ((Event &)e);	// DezimalPunkt oder Gradangabe
		return;
	}
	NumEdit :: KeyDown (e);		// ansonsten weiterleiten
}

EXPORT03 DoubleNumEdit :: ~DoubleNumEdit (void) 
{
	// nothing to do 
}

void EXPORT03 DoubleNumEdit :: FocusChange (FocusChangeEvt e)
{
	if (!e.gotFocus() && m_NEM == NEM_Test) {	// wenn Focus verloren geht
	// Prüfroutine rufen
	double dResult = 0.0;
	
		if (GetValue (dResult)) {	// eingegebenen Wert holen
		// kein Fehler
			if (dResult < m_dblMin || dResult > m_dblMax) {
				SetValue (m_dblMin);	// evtl. neuen Wert setzen
				MessageBeep (0);	// piepsen
			}
		} else {
			SetValue (0.0);		// fehlerhafte Eingabe 
			MessageBeep (0);
		}

	// Workaround der Win31-Hacke keinen EN_KILLFOCUS Event zu generieren
	// ------------------------------------------------------------------
		if (LOWORD(GetVersion()) >= 0x030a) {
			SendMessage (GetParent() -> Handle(), 
				    WM_COMMAND, GetID(), 
				    MAKELONG (Handle (), EN_KILLFOCUS));
		}
	// ------------------------------------------------------------------
	}
	ControlWindow :: FocusChange (e);	// und weiterleiten
}

bool EXPORT03 DoubleNumEdit :: GetValue (double &dbl) 
{
char inBuff[40];

	if (GetTextLen() > 0) {
		GetText (inBuff, sizeof(inBuff));
		dbl = atof (inBuff);
		return TRUE;
	}
	dbl = 0.0;

return FALSE;	// Default
}

void EXPORT03 DoubleNumEdit :: SetValue (double dbl)
{
char outBuff[40];

	SetText (DtoA (outBuff, "%10.3f", dbl));
}

void EXPORT03 DoubleNumEdit :: SetMargins (double dMin, double dMax)
{
	m_dblMin = dMin;
	m_dblMax = dMax;
}

bool EXPORT03 DoubleNumEdit :: GetMargins (double &rdMin, double &rdMax)
{
	if (NEM_NoTest == m_NEM) return false;
	rdMin = m_dblMin;
	rdMax = m_dblMax;

return true;
}
