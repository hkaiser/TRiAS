// Control, welches zur Anzeige eines Hilfetextes in Dialogfenstern 
// eingesetzt werden kann
// File: HELPTEXT.CPP

#include "pheader.hpp"

extern "C" {
	#include <stdarg.h>
}

#include "helptext.hpp"

// Initialisierung, Konstruktor/Destruktor ------------------------------------
__export CHelpText :: CHelpText (pDialogWindow pW, ResID resID, ResourceFile *pRF)
		    		: FixedText (pW, resID)
{
	m_fFontChanged = FALSE;
	m_pFont = NULL;
	m_pBuff = NULL; 
	m_pRF = pRF;
}

__export CHelpText :: ~CHelpText (void)
{
	DELETE_VEC (m_pBuff);
	if (m_fFontChanged) {
		m_pFont = ChangeFont (m_pFont);
		DELETE_OBJ (m_pFont);
	}
}

BOOL __export CHelpText :: FInit (void)
{
// Bufferbereich anlegen
	m_pBuff = new char [_MAX_PATH];
	if (m_pBuff == NULL)
		return FALSE;

#ifdef WIN32
	if (IsWin40()) 
		return true;
#endif // WIN32

// 	Font für BeschreibungsBox generieren
	ResString rsArial (ResID (IDS_ARIALTEXT, m_pRF), 10);
#if !defined(_TRIAS_OLDIMPLEMENTATION2)
	m_pFont = new CVFont (Swiss, Dimension (0, -12), rsArial);
#else
	m_pFont = new Font (Swiss, Dimension (0, -12), rsArial);
#endif //!defined(_TRIAS_OLDIMPLEMENTATION2)
	if (m_pFont) {
		m_pFont = ChangeFont (m_pFont);
		m_fFontChanged = TRUE;
	}

return TRUE;
}

                                  
/*                                  
CHelpText * __export CHelpText :: CreateInstance (pDialogWindow pW, ResID resID)
{
CHelpText *pHT = new CHelpText (pW, resID);

	if (pHT == NULL || !pHT -> FInit()) {
		DELETE (pHT);
		return NULL;
	}
	
return pHT;
}
*/


// Eigentliche Funktionalität -------------------------------------------------
// Setzt den BeschreibungsText entsprechend dem ResourceText ------------------
void __export CHelpText :: SetHelpText (uint ID)
{
ResString rsT (ResID (ID, m_pRF), _MAX_PATH);

	SetText (rsT.Addr());
}


void __export CHelpText :: SetHelpTextV (ResID uiRes, ...)
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


