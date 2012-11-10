// Daten und Funktionen der Sprungverteilertabelle -----------------------------
// File: JumpTab.cpp
// H. Kaiser


#include "GeoEditP.h"

#include <limits.h>
#include <eb.h>

#include "GeoEditOutside.h"		// Prototypen
#include "JumpTab.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// Sprungverteiler-Tabelle (statisch/compilergeneriert)
static STATICEXTPROC s_StaticExtFcns[] = 
{
	{ refcnt_geoedit, 1 },
	{ function_geoedit_AddObject, 2 },
	{ function_geoedit_GetObject, 3 },
	{ function_geoedit_RemoveObject, 4 },
	{ function_geoedit_AddObjects, 5 },
	{ function_geoedit_GetObjects, 6 },
	{ function_geoedit_RemoveObjects, 7 },
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
	_ASSERTE (0 < NUMEXTPROCS);	// mindestens eine Funktion muß existieren

// kleinsten und größten Index finden
int iMin = INT_MAX;
int iMax = 0;
STATICEXTPROC *pTab = s_StaticExtFcns;

	for (int i = 0; i < NUMEXTPROCS; i++, pTab++) {
		iMin = imin (iMin, pTab -> m_iFcnNum);
		iMax = imax (iMax, pTab -> m_iFcnNum);
	}
	_ASSERTE (iMin != INT_MAX);
	_ASSERTE (iMax >= iMin);

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
		_ASSERTE (rNewFcn == TRiAS_not_supported);
		
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

