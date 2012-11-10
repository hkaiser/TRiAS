// Fenster zur Eingabe eines Textes als Objekteigenschaft ---------------------
// File: QUERYFLD.CXX

#include "trias03p.hxx"

#include "trias03.h"

#include "queryfld.hxx"

#pragma warning (disable: 4355)

CQueryFieldDlg :: CQueryFieldDlg (pWindow pW, short iCnt)
		: DialogWindow (pW, QUERYFIELDDLG),
		  m_sleFieldText (this, IDE_FIELDTEXT),
		  m_cbUseForAll (this, IDCB_USEFORALL)
{
	m_pInBuff = NULL;
	m_iCnt = iCnt;
}

#pragma warning (default: 4355)

bool CQueryFieldDlg :: 	FInit (long lONr, bool fUseForAll, LPCSTR pText)
{
// Buffer anlegen
	m_pInBuff = new char [_MAX_PATH];
	if (m_pInBuff == NULL) return false;

// Caption modifizieren
char *pTemp = new char [_MAX_PATH];

	if (pTemp == NULL) return false; 

	if (GetCaption (m_pInBuff, _MAX_PATH) == NULL)
		ltoa (lONr, m_pInBuff, 10);
	else
		wsprintf (pTemp, m_pInBuff, m_iCnt, lONr);
	SetCaption (pTemp);
	DELETE (pTemp);

	m_cbUseForAll.SetChecked (fUseForAll);
	if (NULL != pText)
		m_sleFieldText.SetText (pText);

return true;
}

void CQueryFieldDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		m_sleFieldText.GetText (m_pInBuff, _MAX_PATH);
		EndDlg (1);
		break;
		
	case IDCANCEL:
		EndDlg();
		break;
		
	case IDCB_USEFORALL:
		break;
	}
}


char *CQueryFieldDlg :: GetFieldText (char *pBuffer, ULONG)
{
	if (!pBuffer || !m_pInBuff) return NULL; 
	
return strcpy (pBuffer, m_pInBuff);
}

CQueryFieldDlg :: ~CQueryFieldDlg (void)
{
	DELETE (m_pInBuff);
}
