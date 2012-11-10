// Daten und Funktionen der Sprungverteilertabelle -----------------------------
// File: JUMPTAB.CPP

#include "stdafx.h"

#include <limits.h>
#include <eb.h>

#include "ColorsExt.h"		// Prototypen
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
	{ refcnt_DoubleColor, 1 },
	{ DoubleColor_RGB_propget, 19 },
	{ DoubleColor_RGB_propset, 20 },

	{ DoubleColor_Red_propget, 2 },
	{ DoubleColor_Green_propget, 3 },
	{ DoubleColor_Blue_propget, 4 },
	{ DoubleColor_Hue_propget, 8 },
	{ DoubleColor_Saturation_propget, 9 },
	{ DoubleColor_Brightness_propget, 10 },
	{ DoubleColor_Red_propset, 5 },
	{ DoubleColor_Green_propset, 6 },
	{ DoubleColor_Blue_propset, 7 },
	{ DoubleColor_Hue_propset, 11 },
	{ DoubleColor_Saturation_propset, 12 },
	{ DoubleColor_Brightness_propset, 13 },
	{ DoubleColor_InitRGB_command, 14 },
	{ DoubleColor_InitHSB_command, 15 },

	{ DoubleColor_Complement_propget, 21 },
	{ DoubleColor_Saturated_propget, 22 },
	{ DoubleColor_Grayed_propget, 23 },
	{ DoubleColor_Pure_propget, 24 },

	{ refcnt_ColorLookUp, 16 },
	{ ColorLookUp_Init_command, 17 },
	{ ColorLookUp_GetColor_function, 18 },
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

