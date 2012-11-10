// Toolbarzugriff aus Erweiterungen heraus
// File: TOOLBTTN.CXX
// H. Kaiser


#include "abstandp.hxx"

#include <toolguid.h>		// CLSID_TRiASUIOwner in uiowner.h
#include "uiowner.h"		// CUIOwner
#include "abstguid.h"		// CLSID_Abstand für abstand.hxx
#include "abstand.hxx"		// AbstandExtension




///////////////////////////////////////////////////////////////////////////////////////////////////
// UIOwner-Member

///////////////////////////////////////////////////////////////////////////////////////////////////
// *** ITRiASUIOwner specific functions ***

// ------------------------------------------------------------------------------------------------
// 'OnUpdateUI' wird unaufgefordert gerufen, wenn TRiAS nichts zu tun hat, und aktualisiert
// z.B. den Status eines ToolButtons (Enable/Disable, Checked/Unchecked etc).
// Solange kein Projekt geöffnet ist, bleibt der Knopf passiv ('Enable(false)'). Danach wird der
// Knopf gedrückt ('SetCheck(1)', wenn unser ButtonID als aktives Tool gemeldet wird, ansonsten
// bleibt der Button ungedrückt ('SetCheck(0)').
HRESULT CUIOwner :: OnUpdateUI (ITRiASBar* pIBar, ITRiASCmdUI* pICmdUI)
{
	if (NULL == pIBar)
		return E_POINTER;

bool b1 = DEX_TestActiveProject();
int i1 = DEX_GetObjectCount();
AbstandExtension* pAE = (AbstandExtension*)g_pTE;
bool b2 = ((AbstandExtension*)g_pTE)->IsSightSelected();

	if (! DEX_TestActiveProject() ||						// kein Projekt geöffnet
		0 == DEX_GetObjectCount() ||						// Projekt enthält keine Objekte
		NULL == (AbstandExtension*)g_pTE ||
		! ((AbstandExtension*)g_pTE)->IsSightSelected())	// keine Sicht ausgewählt
	{
		pICmdUI -> put_IsEnabled (false);	// ToolButton passivieren
		pICmdUI -> put_CheckState (0);		// ToolButton ungedrückt machen
		return NOERROR;
	}

// Projekt ist geöffnet und nicht leer, dann aktives Werkzeug abfragen
int uiID = 0;

	pICmdUI -> put_IsEnabled (true);	// ToolButton aktivieren
	pICmdUI -> get_CmdID (&uiID);		// ID des Buttons besorgen

	return pICmdUI -> put_CheckState (uiID == (int)DEX_GetActiveTool() ? 1 : 0);
}


// ------------------------------------------------------------------------------------------------
// 'OnSelect' wird gerufen, wenn ein beschreibender Text für unseren Button benötigt wird
// (ToolTip oder Statuszeile)
 
// Dabei muß in pBuffer eine Zeichenkette geliefert werden, die zuerst den in der Statuszeile
// anzuzeigenden Text enthält. Wenn ein ToolTip angezeigt werden soll, dann muß dieser Text
// anschließend nach einem '\n' in 'pBuffer' geliefert werden:
//		"StatuszeilenText\nToolTipText"
// Wenn 'pulWritten != NULL' ist, dann hier die Anzahl der in 'pBuffer' abgelegten Zeichen liefern.
// ACHTUNG: Nicht mehr als 'ulLen' Zeichen schreiben.
HRESULT CUIOwner :: OnSelect (ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG ulLen, ULONG* pulWritten)
{
	if (NULL == pIBar || NULL == pBuffer || 0 == ulLen) 
		return E_POINTER;

	try
	{
	ResString str (ResID (uiID, &g_pTE -> RF()), 128);
	ULONG ulToWrite = min (ulLen-1, ULONG(str.Len()));

		strncpy (pBuffer, str, ulToWrite);
		pBuffer[ulToWrite] = '\0';

		if (pulWritten)
			*pulWritten = ulToWrite;

	}
	catch (...)
	{
		return E_OUTOFMEMORY;
	} 

	return NOERROR;
}


// ------------------------------------------------------------------------------------------------
// 'OnCommand' wird gerufen, wenn unser Button durch den Nutzer gedrückt wurde.

// Dieses herrliche Ereignis muß TRiAS mitgeteilt werden, damit unser Button das aktuelle Werkzeug
// ist (aktuelles Werkzeug == ButtonID)
HRESULT CUIOwner :: OnCommand (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (NULL == pIBar) return E_POINTER;

	if (0 != nCode) return S_FALSE;

	DEX_ChangeActiveTool(uiID);

	return NOERROR;
}
