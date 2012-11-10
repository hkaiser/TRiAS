// Control, welches zur Anzeige eines Hilfetextes in Dialogfenstern 
// eingesetzt werden kann
// File: HELPTEXT.HXX

#include "trias03p.hxx"

#include <stdarg.h>

#include "helptext.hxx"

// Initialisierung, Konstruktor/Destruktor ------------------------------------
EXPORT03 CHelpText :: CHelpText (pDialogWindow pW, ResID resID)
		    : FixedText (pW, resID)
{
	m_fFontChanged = false;
	m_pFont = NULL;
	m_pBuff = NULL;
}


EXPORT03 CHelpText :: ~CHelpText (void)
{
	DELETE (m_pBuff);
	if (m_fFontChanged) {
		m_pFont = ChangeFont (m_pFont);
		DELETE (m_pFont);
	}
}


bool EXPORT03 CHelpText :: FInit (bool fChangeFont)
{
// Bufferbereich anlegen
	m_pBuff = new char [_MAX_PATH];
	if (m_pBuff == NULL)
		return false;

	if (!fChangeFont) return true;

// Font für BeschreibungsBox generieren
ResString rsArial (IDS_ARIAL, 20);

	m_pFont = new Font (Swiss, Dimension (0, -12), rsArial);
	if (m_pFont) {
		m_pFont = ChangeFont (m_pFont);
		m_fFontChanged = true;
	}

return true;
}


CHelpText * EXPORT03 CHelpText :: CreateInstance (pDialogWindow pW, ResID resID, 
						  bool fChangeFont)
{
CHelpText *pHT = new CHelpText (pW, resID);

	if (pHT == NULL || !pHT -> FInit (fChangeFont)) {
		DELETE (pHT);
		return NULL;
	}
	
return pHT;
}


// Eigentliche Funktionalität -------------------------------------------------
// Setzt den BeschreibungsText entsprechend dem ResourceText ------------------
void EXPORT03 CHelpText :: SetHelpText (ResID uiRes)
{
ResString rsT (uiRes, _MAX_PATH);

	SetText (rsT.Addr());
}


void EXPORT03 CHelpText :: SetHelpTextV (ResID uiRes, ...)
{
	if (m_pBuff == NULL) {
		SetHelpText (uiRes);
		return;
	}
	
ResString rsT (uiRes, _MAX_PATH);
va_list vaArgs;

	va_start (vaArgs, uiRes);
	wvsprintf (m_pBuff, rsT.Addr(), vaArgs);	
	va_end (vaArgs);
	
	SetText (m_pBuff);
}


