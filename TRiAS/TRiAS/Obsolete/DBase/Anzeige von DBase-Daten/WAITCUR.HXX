/*
Datei WAITCUR.HPP

Scoping-class für Standard-WAIT-CURSOR (Hourglas).

Erarbeitet:	J. Benkenstein 				Stand vom 26. Mai 1996
*/

#ifndef _WAITCUR_HPP
#define _WAITCUR_HPP

class CWaitCursor
{
private:	
	HCURSOR m_hSaveCur;

public:
	CWaitCursor (void) { m_hSaveCur = :: SetCursor (:: LoadCursor (NULL, IDC_WAIT)); }
	~ CWaitCursor (void) { :: SetCursor (m_hSaveCur); }	
};

#endif // _WAITCUR_HPP