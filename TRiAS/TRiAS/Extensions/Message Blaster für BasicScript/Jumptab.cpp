// Daten und Funktionen der Sprungverteilertabelle -----------------------------
// File: JUMPTAB.CPP

#include "stdafx.h"

#include <limits.h>
#include <eb.h>

#include "MsgBlastExt.h"		// Prototypen
#include "jumptab.h"

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// Sprungverteiler-Tabelle (statisch/compilergeneriert)
static STATICEXTPROC s_StaticExtFcns[] = 
{
	{ refcnt_MessageMap, 1 },
	{ propget_MessageMap_Enabled, 2 },
	{ propset_MessageMap_Enabled, 3 },
	{ propget_MessageMap_HasMsg, 4 },
	{ propget_MessageMap_ToCall, 5 },
	{ propset_MessageMap_ToCall, 6 },
	{ command_MessageMap_RemoveAll, 7 },
	{ function_MessageMap_RemoveMessage, 8 },
	{ function_MessageMap_AddMessage, 9 },

	{ refcnt_Mouse,	10 },
	{ propget_Mouse_GetLastKey, 11 },
	{ propfunc_Mouse_GetPoint, 12 },
	{ propfunc_Mouse_GetPointDrag, 13 },
};
#define NUMEXTPROCS (sizeof(s_StaticExtFcns)/sizeof(s_StaticExtFcns[0]))

///////////////////////////////////////////////////////////////////////////////
// Sprungverteiler-Tabelle (dynamisch/laufzeitgeneriert)
ebEXTPROC *g_pExtFcns = NULL;
int g_iExtFcnsOffset = 0;		// Offset zum ersten Eintrag
int g_iExtFcnsLast = 0;			// erster nicht belegter FuncID

///////////////////////////////////////////////////////////////////////////////
// Funktionen zur Verwaltung der SprungverteilerTabelle
inline int imin (int i1, int i2) { return (i1 < i2) ? i1 : i2; }
inline int imax (int i1, int i2) { return (i1 > i2) ? i1 : i2; }

ebEXTPROC *InitJumpTable (int &riMin, int &riMax)
{
	ASSERT(0 < NUMEXTPROCS);	// mindestens eine Funktion muß existieren

// kleinsten und größten Index finden
int iMin = INT_MAX;
int iMax = 0;
STATICEXTPROC *pTab = s_StaticExtFcns;

	for (int i = 0; i < NUMEXTPROCS; i++, pTab++) {
		iMin = imin (iMin, pTab -> m_iFcnNum);
		iMax = imax (iMax, pTab -> m_iFcnNum);
	}
	ASSERT(iMin != INT_MAX);
	ASSERT(iMax >= iMin);

// dynamische Sprungverteilertabelle anlegen
int iSize = iMax - iMin + 1;
ebEXTPROC *pFuncTab = new ebEXTPROC [iSize];

	if (NULL == pFuncTab) return NULL;

	riMin = iMin;
	riMax = iMax + 1;

// Sprungverteilertabelle initialisieren
ebEXTPROC *pFcn = pFuncTab;
int j = 0;

	for (j = 0; j < iSize; j++, pFcn++) 
		*pFcn = TRiAS_not_supported;

	pTab = s_StaticExtFcns;
	for (j = 0; j < NUMEXTPROCS; j++, pTab++) {
	ebEXTPROC &rNewFcn = pFuncTab[pTab -> m_iFcnNum - iMin];
	
	// dieser Eintrag darf noch nicht belegt sein	
		ASSERT(rNewFcn == TRiAS_not_supported);
		
		rNewFcn = pTab -> m_pExtFcn;		// Funktion setzen
	}

return pFuncTab;
}

void FreeJumpTable (ebEXTPROC *&rpExtFcns)
{
	if (NULL != rpExtFcns) {
		delete[] rpExtFcns;
		rpExtFcns = NULL;
	}
}

