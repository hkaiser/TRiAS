// Definitionen: Toolbarzugriff aus Erweiterungen heraus
// File: UIOwnerFunc.cpp
// H. Kaiser


#include "GeoEditP.h"

//#include <stdio.h>		// sprintf() für OutputDebugString

#include <toolguid.h>		// CLSID_TRiASUIOwner in uiowner.h
#include <itoolbar.h>		// ITRiASUIOwner in uiowner.h
#include "uiowner.h"		// CUIOwner

#include "geoedit.h"		// CGeoEditExtension



#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// UIOwner-Member

// Der UIOwner ist so eine Art Feld von CallBack-Funktionen, die durch die ToolBar in
// verschiedenen Situationen gerufen werden, um diverse Informationen zu bekommen bzw.
// bestimmte Aktionen auszulösen.



///////////////////////////////////////////////////////////////////////////////////////////////
// *** ITRiASUIOwner specific functions ***

// --------------------------------------------------------------------------------------------
// 'OnUpdateUI' wird unaufgefordert gerufen, wenn TRiAS nichts zu tun hat, und aktualisiert
// den Status des pICmdUI-ToolButtons (Enable/Disable, Checked/UnChecked).
// Solange kein Projekt geöffnet ist, bleibt der ToolButton passiv ('IsEnabled(false)').
// Wenn der aktuell überprüfte pICmdUI-ToolButton als aktives Tool gemeldet wird (d.h. der
// zuletzt gedrückte ToolButton ist), wird er in den Zustand 'CheckState(1)' versetzt;
// ansonsten bleibt der Button ungedrückt ('CheckState(0)').
// (pIBar kann NULL sein.)
HRESULT CUIOwner::OnUpdateUI (ITRiASBar* pIBar, ITRiASCmdUI* pICmdUI)
{
	if (! DEX_TestActiveProject() ||						// kein Projekt geöffnet
		0 == DEX_GetObjectCount() ||						// Projekt enthält keine Objekte
		NULL == (CGeoEditExtension*)g_pTE ||
		! ((CGeoEditExtension*)g_pTE)->IsSightSelected())	// keine Sicht ausgewählt

	{
		pICmdUI->put_IsEnabled (false);	// ToolButton passivieren
		pICmdUI->put_CheckState (0);	// ToolButton ungedrückt lassen oder machen
		return NOERROR;
	}

// Projekt ist geöffnet und nicht leer
int iPressID = DEX_GetActiveTool();	// ID des zuletzt gedrückten ToolButtons
int iInspectID = 0;			// ID des ToolButtons, der gerade bei der Reih-um-Abfrage dran ist

	pICmdUI->get_CmdID (&iInspectID);	// ID dieses aktuell überprüften ToolButtons besorgen

// Anzahl der selektierten Objekte
long lSelObjCnt = ((CGeoEditExtension*)g_pTE)->TopicalObjsCount();
// mindestens eine Konstruktionshilfslinie existiert (true)
bool bRLExist = ((CGeoEditExtension*)g_pTE)->IsRestrictLineExist();


// Aktualisierung des Enable/Disable-Status
	switch (iInspectID)
	{
		case ID_TOOL_MODIFYOBJ:	// Modify- bzw.
		case ID_TOOL_MOVEOBJ:	// Kopier/Verschiebe-Button werden abgefragt
			if (lSelObjCnt > 0)	// mindestens 1 selektiertes Objekt
				pICmdUI->put_IsEnabled (true);	//  dann ToolButton aktivieren
			else				// keine Objekt selektiert 
			{
				if (ID_TOOL_MODIFYOBJ == iPressID ||
					ID_TOOL_MOVEOBJ == iPressID)
					DEX_ChangeActiveTool (0);	// "Pfeil"-ToolButton ist jetzt gedrückt

				// Modify- bzw. Kopier/Verschiebe-Button passivieren, wenn kein Objekt
				// selektiert wurde
				pICmdUI->put_IsEnabled (false);
			}
			break;


		case ID_TOOL_DESIGN:	// Design-Button wird abgefragt
			if (lSelObjCnt > 0)	// mindestens 1 selektiertes Objekt und
			{
				// Design-, DesignStop-Button oder Punkt-, Linien bzw. FlächenNeueditierung
				// wurde gedrückt
				if (ID_TOOL_DESIGN == iPressID ||
					ID_TOOL_DESIGNSTOP == iPressID ||
					ID_TOOL_PUNKTEDIT == iPressID ||
					ID_TOOL_LINIENEDIT == iPressID ||
					ID_TOOL_FLAECHENEDIT == iPressID)
					pICmdUI->put_IsEnabled (true);	// dann auch Design-Button aktivieren
				else
					pICmdUI->put_IsEnabled (false);	// ansonsten Design-Button pasivieren
			}
			else	// kein Objekt selektiert, deshalb Design-Button passivieren
				pICmdUI->put_IsEnabled (false);
			break;


		case ID_TOOL_DESIGNSTOP:	// DesignStop-Button wird abgefragt
			// der 2. Teil der nachfolgenden if-Bedingung erscheint redundant, kann aber
			// eintreten, wenn während des Design-Zustandes selektierte Objekte deselektiert
			// bzw. gelöscht werden
			if (ID_TOOL_DESIGN == iPressID &&	// Design-Button wurde gedrückt
				bRLExist)						// und wenigstens 1 Hilfslinie existiert
				pICmdUI->put_IsEnabled (true);	// dann auch DesignStop-Button aktivieren
			else
				pICmdUI->put_IsEnabled (false);	// ansonsten DesignStop-Button pasivieren
			break;


		default:					// alle anderen Button
			pICmdUI->put_IsEnabled (true);	// Button aktvieren

	} // switch


// Aktualisierung des Checked/UnChecked-Status
	switch (iInspectID)
	{
		case ID_TOOL_PUNKTEDIT:
		case ID_TOOL_LINIENEDIT:
		case ID_TOOL_FLAECHENEDIT:
			if (ID_TOOL_DESIGN == iPressID || ID_TOOL_DESIGNSTOP == iPressID)
				return NOERROR;
			return pICmdUI->put_CheckState (iInspectID == iPressID ? 1 : 0);

		case ID_TOOL_DESIGN:
		{
		bool bOpParked = ((CGeoEditExtension*)g_pTE)->IsOpParked();

			return pICmdUI->put_CheckState (bOpParked ? 1 : 0);
		}

		case ID_TOOL_DESIGNSTOP:
			return pICmdUI->put_CheckState (0);

		default:
			return pICmdUI->put_CheckState (iInspectID == iPressID ? 1 : 0);
	}

	_ASSERTE (false);		// hierhin dürfte keiner mehr kommen
	return E_UNEXPECTED;

} // OnUpdateUI


// --------------------------------------------------------------------------------------------
// 'OnSelect' wird gerufen, wenn ein beschreibender Text für unseren Button benötigt wird
// (ToolTip oder Statuszeile)
 
// Dabei muß in pBuffer eine Zeichenkette geliefert werden, die zuerst den in der Statuszeile
// anzuzeigenden Text enthält. Wenn ein ToolTip angezeigt werden soll, dann muß dieser Text
// anschließend nach einem '\n' in 'pBuffer' geliefert werden:
//		"StatuszeilenText\nToolTipText"
// Wenn 'pulWritten != NULL' ist, dann hier die Anzahl der in 'pBuffer' abgelegten Zeichen
// liefern.
// ACHTUNG: Nicht mehr als 'ulLen' Zeichen schreiben.
HRESULT CUIOwner::OnSelect (ITRiASBar* pIBar, UINT uiID, LPSTR pBuffer, ULONG ulLen,
							ULONG* pulWritten)
{
	if (NULL == pBuffer)	// pIBar kann NULL sein
		return E_POINTER;

	if (0 == ulLen)
		return E_INVALIDARG;

	try
	{
	ResString str (ResID (uiID, &g_pTE->RF()), 128);
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


// --------------------------------------------------------------------------------------------
// 'OnCommand' wird gerufen, wenn unser Button durch den Nutzer gedrückt wurde.

// Dieses herrliche Ereignis muß TRiAS mitgeteilt werden, damit unser Button das aktuelle
// Werkzeug ist (aktuelles Werkzeug == iInspectID)
// pIBar kann NULL sein.
HRESULT CUIOwner::OnCommand (ITRiASBar* pIBar, UINT uiID, int nCode)
{
	if (0 != nCode) return S_FALSE;

	DEX_ChangeActiveTool (uiID);

	return NOERROR;
}
