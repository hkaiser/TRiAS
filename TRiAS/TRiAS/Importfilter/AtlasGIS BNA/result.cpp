// ErgebnisDialog -------------------------------------------------------------
// File: RESULT.CPP

#include "bnaimpp.hpp"

#include "bnaimp.h"		// ResourceKonstanten
#include "relkey.hxx"
#include "result.hxx"		// DialogKlasse

#pragma warning (disable: 4355)

CResultDlg :: CResultDlg (pWindow pW)
	    : DialogWindow (pW, ResID (IDD_RESULTDLG, &g_pTE -> RF())),
	      m_ftTexts (this, IDT_TEXTS),
	      m_ftPoints (this, IDT_POINTS),
	      m_ftLines (this, IDT_LINES),
	      m_ftAreas (this, IDT_AREAS),
	      m_ftKomplex (this, IDT_KOMPLEX),
	      m_ftWithErrors (this, IDT_WITHERRORS),
	      m_ftImported (this, IDT_IMPORTED),
	      m_ftNotImported (this, IDT_NOTIMPORTED),
	      m_ftTime (this, IDT_TIME)
{
}

#pragma warning (default: 4355)

CResultDlg :: ~CResultDlg (void)
{
}

void CResultDlg :: ButtonClick (ControlEvt)
{
	EndDlg(1);	// immer raus
}

void CResultDlg :: SetTexts (long lCnt)
{
	SetFixedNumber (lCnt, m_ftTexts);
}

void CResultDlg :: SetPoints (long lCnt)
{
	SetFixedNumber (lCnt, m_ftPoints);
}

void CResultDlg :: SetLines (long lCnt)
{
	SetFixedNumber (lCnt, m_ftLines);
}

void CResultDlg :: SetAreas (long lCnt)
{
	SetFixedNumber (lCnt, m_ftAreas);
}

void CResultDlg :: SetKomplex (long lCnt)
{
	SetFixedNumber (lCnt, m_ftKomplex);
}

void CResultDlg :: SetWithErrors (long lCnt)
{
	SetFixedNumber (lCnt, m_ftWithErrors);
}

void CResultDlg :: SetImported (long lCnt)
{
	SetFixedNumber (lCnt, m_ftImported);
}

void CResultDlg :: SetNotImported (long lCnt)
{
	SetFixedNumber (lCnt, m_ftNotImported);
}

void CResultDlg :: SetFixedNumber (long lCnt, FixedText &ft)
{
char cbBuffer[64];

	ltoa (lCnt, cbBuffer, 10);
	ft.SetText (cbBuffer);
}


