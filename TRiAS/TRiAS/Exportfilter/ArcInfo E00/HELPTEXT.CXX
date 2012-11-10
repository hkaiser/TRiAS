// Control, welches zur Anzeige eines Hilfetextes in Dialogfenstern 
// eingesetzt werden kann
// File: HELPTEXT.CXX

#include "stdafx.h"               
/*XX*/ #include "TRiASArcImpl.h"

extern "C" {
	#include <stdarg.h>
}

//XX#include "triasarc.hr"			// Ressourcen
#include "helptext.hxx"

// Initialisierung, Konstruktor/Destruktor ------------------------------------
EXPORTFLT CHelpText :: CHelpText (pDialogWindow pW, ResID resID, ResourceFile *pRF)
		    		: FixedText (pW, resID)
{
	m_fFontChanged = FALSE;
	m_pFont = NULL;
	m_pBuff = NULL; 
	m_pRF = pRF;
}

EXPORTFLT CHelpText :: ~CHelpText (void)
{
	DELETE_VEC (m_pBuff);
	if (m_fFontChanged) {
		m_pFont = ChangeFont (m_pFont);
		DELETE_OBJ (m_pFont);
	}
}

BOOL EXPORTFLT CHelpText :: FInit (void)
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
	ResString ArialStr (ResID (IDS_ARIALTEXT, m_pRF), 10);
//XX	m_pFont = new Font (Swiss, Dimension (0, -12), ArialStr.Addr ());
/*XX*/	m_pFont = new CVFont (Swiss, Dimension (0, -12), ArialStr.Addr ());
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
void EXPORTFLT CHelpText :: SetHelpText (uint ID)
{
ResString rsT (ResID (ID, m_pRF), _MAX_PATH);

	SetText (rsT.Addr());
}


void EXPORTFLT CHelpText :: SetHelpTextV (ResID uiRes, ...)
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


