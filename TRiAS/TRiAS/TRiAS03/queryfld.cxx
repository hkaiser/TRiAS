// Fenster zur Eingabe eines Textes als Objekteigenschaft ---------------------
// File: QUERYFLD.CXX

#include "trias03p.hxx"

#include "trias03.h"

#include "queryfld.hxx"

#pragma warning (disable: 4355)

CQueryFieldDlg::CQueryFieldDlg (pWindow pW, short iCnt)
		: DialogWindow (pW, QUERYFIELDDLG),
		  m_sleFieldText (this, IDE_FIELDTEXT),
		  m_cbUseForAll (this, IDCB_USEFORALL),
		  m_pbOk (this, IDOK)
{
	m_pInBuff = NULL;
	m_iCnt = iCnt;
	m_pbOk.Disable();
}

#pragma warning (default: 4355)

bool CQueryFieldDlg::FInit (long lONr, bool fUseForAll, LPCSTR pText, bool fEnableUseForAll)
{
// Buffer anlegen
	ATLTRY(m_pInBuff = new char [_MAX_PATH]);
	if (m_pInBuff == NULL) return false;

// Caption modifizieren
char cbTemp[_MAX_PATH];

	if (NULL == GetCaption (m_pInBuff, _MAX_PATH))
		ltoa (lONr, m_pInBuff, 10);
	else
		wsprintf (cbTemp, m_pInBuff, m_iCnt);

	SetCaption (cbTemp);

	if (fEnableUseForAll) 
		m_cbUseForAll.SetChecked (fUseForAll);
	else
		m_cbUseForAll.Hide();

	if (NULL != pText)
		m_sleFieldText.SetText (pText);

	return true;
}

void CQueryFieldDlg::EditChange (ControlEvt e)
{
	if (IDE_FIELDTEXT == (uint)e.GetControlID()) {
		if (m_sleFieldText.GetTextLen() > 0)
			m_pbOk.Enable();
		else
			m_pbOk.Disable();
	}
}

void CQueryFieldDlg::ButtonClick (ControlEvt e)
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


char *CQueryFieldDlg::GetFieldText (char *pBuffer, ULONG)
{
	if (!pBuffer || !m_pInBuff) 
		return NULL; 
	return strcpy (pBuffer, m_pInBuff);
}

CQueryFieldDlg::~CQueryFieldDlg (void)
{
	DELETE_OBJ (m_pInBuff);
}
