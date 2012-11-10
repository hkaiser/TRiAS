// Daten und Funktionen der Sprungverteilertabelle -----------------------------
// File: JUMPTAB.CPP

#if !defined(_JUMPTAB_H)
#define _JUMPTAB_H

///////////////////////////////////////////////////////////////////////////////
// Sprungverteiler-Tabelle (statisch/compilergeneriert)
typedef void (*ebEXTPROC)(ebHTHREAD, int, ebARGS);
typedef struct tagSTATICEXTPROC {
	ebEXTPROC m_pExtFcn;	// Funktion
	int m_iFcnNum;			// zugehöriger Index
} STATICEXTPROC;

///////////////////////////////////////////////////////////////////////////////
// Sprungverteiler-Tabelle (dynamisch/laufzeitgeneriert)
extern ebEXTPROC *g_pExtFcns;
extern int g_iExtFcnsOffset;		// Offset zum ersten Eintrag
extern int g_iExtFcnsLast;			// erster nicht belegter FuncID

///////////////////////////////////////////////////////////////////////////////
// Funktionen zur Verwaltung der SprungverteilerTabelle
ebEXTPROC *InitJumpTable (int &riMin, int &riMax);
void FreeJumpTable (ebEXTPROC *&);

#endif // _JUMPTAB_H
