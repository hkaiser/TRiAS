/*
Datei WAITCUR.HXX

Scoping-class für Standard-WAIT-CURSOR (Hourglas).

Erarbeitet:	J. Benkenstein 				Stand vom 26. Mai 1996
*/

#ifndef _WAITCUR_HXX
#define _WAITCUR_HXX

class CWaitCursor
{
private:	
	HCURSOR m_hSaveCur;

public:
	CWaitCursor (void) { m_hSaveCur = :: SetCursor (:: LoadCursor (NULL, IDC_WAIT)); }
	~ CWaitCursor (void) { :: SetCursor (m_hSaveCur); }	
};

#endif // _WAITCUR_HXX
