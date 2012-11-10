// $Header: $
// Copyright© 1999 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 02/18/1999 09:38:41 PM
//
// @doc
// @module JumpTable.cpp | Sprungverteilertablle für TRiAS-DEX_... commands

#include "idntsdbp.hxx"

#include "identsdb.h"
#include "defident.h"

#include "Identsdb.hxx"
#include "JumpTable.h"
#include "defident.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define _countof(x)	(sizeof(x)/sizeof(x[0]))

///////////////////////////////////////////////////////////////////////////////
// alle möglichen Windows-Messages hier vorbeischicken
STDMETHODIMP_(LRESULT) CIdentsDBExtension::WindowsNotification (
	UINT wMsg, WPARAM wParam, LPARAM lParam)
{
	if (__DexCmd == wMsg)
		return FullFillWill (wParam, lParam);		// evtl. hier verarbeiten
	return FALSE;		// alles andere normalerweise weiterleiten
}

///////////////////////////////////////////////////////////////////////////////
// Sprungverteilertabelle initialisieren
bool CIdentsDBExtension::InitJumpTable()
{
// größten und kleinsten MessageID suchen
unsigned int iFirst = UINT_MAX;
unsigned int iLast = 0;
const DEXMESSAGEENTRY *pDME = DexMessageEntries;

	for (int i = 0; i < _countof(DexMessageEntries); i++, pDME++) {
	UINT uiMsg = pDME -> m_uiMsg;
	
		if (iFirst > uiMsg) iFirst = uiMsg;
		if (iLast < uiMsg) iLast = uiMsg;
	}
	if (iFirst == USHRT_MAX || iLast == 0)
		return false;
	
	m_iDexProcsNum = iLast-iFirst+1;
	m_i1stDexProc = iFirst;

	TX_ASSERT(m_iDexProcsNum >= 1);
					
// Tabelle anlegen und initialisieren
	ATLTRY(m_cbDexProcs = new DEXMESSAGEPROC [m_iDexProcsNum]);
	if (NULL == m_cbDexProcs) return false;

	for (unsigned short j = 0; j < m_iDexProcsNum; j++) 
		 m_cbDexProcs[j] = NULL;

// Funktionen eintragen
	pDME = DexMessageEntries;
	for (i = 0; i < _countof(DexMessageEntries); i++, pDME++) {
	// erste Zuweisung ?
		TX_ASSERT(NULL == m_cbDexProcs[(pDME -> m_uiMsg) - iFirst]);
		m_cbDexProcs[(pDME -> m_uiMsg) - iFirst] = pDME -> m_pProc;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Sprungverteilertabelle freigeben
void CIdentsDBExtension::FreeJumpTable()
{
	DELETE_OBJ(m_cbDexProcs);
}

///////////////////////////////////////////////////////////////////////////////
// DEX_Commands abarbeiten
LRESULT CIdentsDBExtension::FullFillWill (WPARAM wParam, LPARAM lParam)
{
	TX_ASSERT (NULL != m_cbDexProcs);	// über Sprungverteiler abwickeln

register unsigned int uiMsg = wParam-m_i1stDexProc;
	
	if (uiMsg >= 0 && uiMsg < m_iDexProcsNum && NULL != m_cbDexProcs[uiMsg])
		return (this ->* m_cbDexProcs[uiMsg])(NULL, lParam);

// alle, die nicht implementiert sind, weiterleiten
	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// DEX_... command handler

// DEX_PROJECTOPEN
LRESULT CIdentsDBExtension::OnDefineNewObjects (HPROJECT hPr, LPARAM lParam)
{
DEFINEIDENTDLG *pDlgData = reinterpret_cast<DEFINEIDENTDLG *>(lParam);

	TX_ASSERT_POINTER(pDlgData, DEFINEIDENTDLG);
	TX_ASSERT(pDlgData -> dwSize == sizeof(DEFINEIDENTDLG));
	TX_ASSERT(IsWindow(pDlgData -> hWnd));

Window Wnd (pDlgData -> hWnd);
DefineIdentDlg DIDlg (&Wnd, ResID (DEFINEIDENT, &RF()));

	if (0 != pDlgData -> lIdent) {
		if (!DIDlg.FInit (pDlgData -> lIdent))
			return 0;
	} else {
		if (!DIDlg.FInit ("", pDlgData -> hPr))		// neuen Ident erzeugen
			return 0;
	}
	DIDlg.Show (Centre);
	return DIDlg.GetIdent();	// liefert Ident
}

