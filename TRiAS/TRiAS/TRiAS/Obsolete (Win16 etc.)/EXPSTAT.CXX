// Fenster, welchesden ExportStatus anzeigt (in Prozent)
// File: EXPSTATUS.CXX

#include "triaspre.hxx"

#include "expstat.h"
#include "expstat.hxx"

#pragma warning (disable: 4355)

ExportStatus :: ExportStatus (pWindow pW, long AllCnt, LPCSTR)
	      : ModeLessDialog (pW, EXPORTSTATUS),
		CancelButton (this, IDCANCEL),
		m_gStatus (this, IDG_EXPORTSTATUS)
{
// Variablen initialisieren
	m_lAllCnt = AllCnt;
	m_fWasInterrupted = FALSE;
	SetValue (0L);

	m_gStatus.SetRange (1000);

// initialisierung des Bufferbereiches
	m_pOutString = new char [64];
}

#pragma warning (default: 4355)

ExportStatus :: ~ExportStatus (void) 
{
	if (m_pOutString) delete m_pOutString;
}

void ExportStatus :: SetValue (long CurrCnt, long ON) 
{
short CurrVal = (short)((CurrCnt * 1000)/m_lAllCnt);

	if (ON != -1) {
		wsprintf (m_pOutString, "%ld (%ld) - %%3d%%%%", CurrCnt, ON); 
		m_gStatus.SetText (m_pOutString);
	}
	m_gStatus.SetPosition (CurrVal);
}

void ExportStatus :: ButtonClick (ControlEvt) 
{
	m_fWasInterrupted = TRUE;		// Export abbrechen
}
