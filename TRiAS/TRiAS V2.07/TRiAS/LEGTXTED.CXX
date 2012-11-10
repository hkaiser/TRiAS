// LegendenText editieren -----------------------------------------------------
// File: LEGTXTED.CXX

#include "triaspre.hxx"

#include "legtxted.hxx"

#include "triasres.h"

// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable:4355)

CEditLegTextDlg :: CEditLegTextDlg (pWindow pW)
		 : DialogWindow (pW, LEGENTRYTEXTDLG),
		   m_mleText (this, IDE_LEGENTRYEDITTEXT),
#if !defined(WIN32)
		   m_pbHelp (this, IDHELP),
#endif // WIN32
		   m_pbOK (this, IDOK)
{
	m_pBuffer = NULL;
#if !defined(WIN32)
	m_pbHelp.Disable();
#endif // WIN32
	m_pbOK.Disable();
}

#pragma warning (default:4355)

CEditLegTextDlg :: ~CEditLegTextDlg (void)
{
	DELETE (m_pBuffer);
}

CEditLegTextDlg *CEditLegTextDlg :: CreateInstance (pWindow pW, char *pText)
{
CEditLegTextDlg *pDlg = new CEditLegTextDlg (pW);

	if (pDlg == NULL || !pDlg -> FInit (pText)) {
		DELETE (pDlg);
		return NULL;
	}
	
return pDlg;
}

BOOL CEditLegTextDlg :: FInit (char *pText)
{
char *pT = ConvertToEscape (pText, '"');

	m_pBuffer = new char [_MAX_PATH*4];
	if (m_pBuffer == NULL) return FALSE;
	
	if (pT) {
		strcpy (m_pBuffer, pT);
		DELETE (pT);
	} else
		strcpy (m_pBuffer, pText);
	
	m_mleText.SetText (m_pBuffer);
	if (m_mleText.GetTextLen() > 0)
		m_pbOK.Enable();
	
return TRUE;
}

// EventHandler ---------------------------------------------------------------
void CEditLegTextDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		{
		char *pText = NULL;
		
			m_mleText.GetText (m_pBuffer, _MAX_PATH*4);
			pText = ConvertFromEscape (m_pBuffer, '"');
			if (pText) {
				strcpy (m_pBuffer, pText);
				delete pText;
			}
			EndDlg(1);
		}
		break;
		
	case IDCANCEL:
		EndDlg(0);
		break;
		
	case IDHELP:
		break;
	}
}

void CEditLegTextDlg :: EditChange (ControlEvt)
{
	if (m_mleText.GetTextLen() > 0)
		m_pbOK.Enable();
	else 
		m_pbOK.Disable();
}


