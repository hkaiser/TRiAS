// LegendenText editieren -----------------------------------------------------
// File: LEGTXTED.CXX

#include "triaspre.hxx"

#include "strings.h"
#include "legtxted.hxx"

#include "triasres.h"

// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable:4355)

CEditLegTextDlg::CEditLegTextDlg (pWindow pW, UINT uiResCap, UINT uiResPrompt)
		 : DialogWindow (pW, LEGENTRYTEXTDLG),
		   m_mleText (this, IDE_LEGENTRYEDITTEXT),
#if defined(WIN16)
		   m_pbHelp (this, IDHELP),
#endif // WIN16
		   m_ftPrompt (this, uiResPrompt),
		   m_pbOK (this, IDOK)
{
	m_pBuffer = NULL;
#if defined(WIN16)
	m_pbHelp.Disable();
#endif // WIN16
	m_pbOK.Disable();

ResString resCap (uiResCap, 128);

	SetCaption (resCap);
}

#pragma warning (default:4355)

CEditLegTextDlg::~CEditLegTextDlg (void)
{
	DELETE_OBJ (m_pBuffer);
}

CEditLegTextDlg *CEditLegTextDlg::CreateInstance (
	pWindow pW, LPCSTR pText, UINT uiResCap, UINT uiResPrompt)
{
CEditLegTextDlg *pDlg = new CEditLegTextDlg (pW, uiResCap, uiResPrompt);

	if (pDlg == NULL || !pDlg -> FInit (pText)) {
		DELETE_OBJ (pDlg);
		return NULL;
	}
	return pDlg;
}

BOOL CEditLegTextDlg::FInit (LPCSTR pText)
{
char *pT = ConvertToEscape (pText, "\"\'");

	m_pBuffer = new char [_MAX_PATH*4];
	if (m_pBuffer == NULL) return FALSE;
	
	if (pT) {
		strcpy (m_pBuffer, pT);
		DELETE_OBJ (pT);
	} else
		strcpy (m_pBuffer, (NULL != pText) ? pText : g_cbNil);
	
	m_mleText.SetText (m_pBuffer);
	if (m_mleText.GetTextLen() > 0)
		m_pbOK.Enable();
	
	return TRUE;
}

// EventHandler ---------------------------------------------------------------
void CEditLegTextDlg::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		{
		char *pText = NULL;
		
			m_mleText.GetText (m_pBuffer, _MAX_PATH*4);
			pText = ConvertFromEscape (m_pBuffer, "\"\'");
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

void CEditLegTextDlg::EditChange (ControlEvt)
{
	if (m_mleText.GetTextLen() > 0)
		m_pbOK.Enable();
	else 
		m_pbOK.Disable();
}


