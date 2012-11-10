// UIOwner.cpp : Implementation of ToolBarOwner for MainToolbar/EditPntButton

#include "editobjp.hxx"
#include "editobjr.h"

#include <toolguid.h>
#include <itoolbar.h>

#include "UIOwner.h"

/////////////////////////////////////////////////////////////////////////////
// *** ITRiASUIOwner specific functions ***

// 'OnUpdateUI' wird immer dann gerufen, wenn der Status unseres Knopfes 
// aktualisiert werden soll (Enable/Disable, Checked/Unchecked etc).
//
// Solange kein Projekt geöffnet ist, bleibt der Knopf passiv ('Enable(false)').
// Danach wird der Knopf gedrückt ('SetChecked(1)', wenn unser ButtonID als
// aktives Tool gemeldet wird, ansonsten bleibt der Button ungedrückt
// ('SetChecked(0)').
HRESULT CUIOwner::OnUpdateUI (ITRiASBar *pIBar, ITRiASCmdUI *pICmdUI)
{
	if (NULL == pIBar) return E_POINTER;

// Testen, ob überhaupt ein Projekt geöffnet ist
char cbBuffer[_MAX_PATH];

	if (!DEX_GetActiveProject(cbBuffer)) {
		pICmdUI -> Enable (false);
		return NOERROR;
	}

// Projekt ist geöffnet, aktives Werkzeug abfragen
int uiID = 0;

	pICmdUI -> Enable(true);
	pICmdUI -> GetID (&uiID);		// ID des Buttons besorgen

return pICmdUI -> SetCheck (uiID == (int)DEX_GetActiveTool() ? 1 : 0);
}

// 'OnSelect' wird gerufen, wenn ein beschreibender Text für unseren Button
// benötigt wird (ToolTip oder Statuszeile)
// 
// Dabei muß in pBuffer eine Zeichenkette geliefert werden, die zuerst den
// in der Statuszeile anzuzeigenden Text enthält. Wenn ein ToolTip angezeigt
// werden soll, dann muß dieser Text anschließend nach einem '\n' in 'pBuffer'
// geliefert werden:
//		"StatuszeilenText\nToolTipText"
// Wenn 'pulWritten != NULL' ist, dann hier die Anzahl der in 'pBuffer'
// abgelegten Zeichen liefern. ACHTUNG: Nicht mehr als 'ulLen' Zeichen 
// schreiben.
HRESULT CUIOwner::OnSelect (ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (NULL == pIBar || NULL == pBuffer || 0 == ulLen) 
		return E_POINTER;

	try {
	ResString str (ResID (IDS_STATUSTEXT, &g_pTE -> RF()), 128);
	ULONG ulToWrite = min (ulLen-1, ULONG(str.Len()));

		strncpy (pBuffer, str, ulToWrite);
		pBuffer[ulToWrite] = '\0';

		if (pulWritten)
			*pulWritten = ulToWrite;

	} catch (...) {
		return E_OUTOFMEMORY;
	} 

return NOERROR;
}

// 'OnCommand' wird gerufen, wenn unser Button durch den Nutzer gedrückt wurde.
//
// Dieses herrliche Ereignis muß TRiAS mitgeteilt werden, damit unser Button
// das aktuelle Werkzeug ist (aktuelles Werkzeug == ButtonID)
HRESULT CUIOwner::OnCommand (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (nCode != 0) return S_FALSE;
	if (NULL == pIBar) return E_POINTER;

	DEX_ChangeActiveTool(uiID);

return NOERROR;
}

