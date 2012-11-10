// Fenster, welches den ExportStatus anzeigt (Sichtnamen) ---------------------
// File: VEXPSTAT.CXX

#include "visobjp.hxx"
	
#include <protos.h>

#include "vstatus.h"
#include "vstatus.hxx"

#pragma warning (disable: 4355)

CStatus :: CStatus (pWindow pW, short iRange, ResourceFile *pRF, short iIdBase)
	 : ModeLessDialog (pW, ResID (IMPEXPORTSTATUS, pRF)),
	   m_gStatusGauge (this, IDG_STATUSGAUGE),
	   m_ftComment (this, IDT_COMMENT),
	   m_iIdBase (iIdBase)
{
// Variablen initialisieren
	m_fWasInterrupted = false;
	
	m_gStatusGauge.SetRange (iRange);
	
	m_pView = new char [_MAX_PATH];
}

#pragma warning (default: 4355)

CStatus :: ~CStatus (void) 
{
	DELETE_OBJ (m_pView);
}

void _XTENSN_EXPORT CStatus :: ButtonClick (ControlEvt) 
{
	m_fWasInterrupted = true;		// Import abbrechen
}

static char s_pTmp[_MAX_PATH];

void CStatus :: SetViewName (char *pView)
{
char *pLocView = NULL;

	if (pView == NULL) 
		pLocView = (char *)m_pView;
	else
		pLocView = pView;
		
	if (pLocView == NULL) return;
	
	wsprintf (s_pTmp, "%%3d%%%% - %s", pLocView);
	m_gStatusGauge.SetText (s_pTmp);
		
	if (m_pView) strcpy (m_pView, pLocView);
}


void CStatus :: SetHandledItem (long lIdent, bool fRePaint)
{
char cbBuffer[MAX_OKS_LENX];

	ClassFromIdentX (lIdent, cbBuffer);
	if (m_pView)
		wsprintf (s_pTmp, "%%3d%%%% - %s (%s)", m_pView, cbBuffer);
	else 
		wsprintf (s_pTmp, "%%3d%%%% - (%s)", cbBuffer);

	m_gStatusGauge.SetText (s_pTmp);
	if (fRePaint) m_gStatusGauge.SetDeltaPos (0);		// force repaint
}


void CStatus :: SetHandledItem (char *pUIdent, bool fRePaint)
{
	if (m_pView) {
		wsprintf (s_pTmp, "%%3d%%%% - %s (%s)", 
			  m_pView, pUIdent);
	} else {
		wsprintf (s_pTmp, "%%3d%%%% - (%s)", pUIdent);
	}
	m_gStatusGauge.SetText (s_pTmp);
	if (fRePaint) m_gStatusGauge.SetDeltaPos (0);		// force repaint
}

