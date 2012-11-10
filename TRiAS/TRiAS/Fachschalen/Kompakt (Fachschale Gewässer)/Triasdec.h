// Konstantendefinitionen für ErweiterungsRessourcen
// File: TRIASDEC.H

#if !defined(_TRIASDEC_H)
#define _TRIASDEC_H

#include "KOMPDEF.H"

//////////////////////////////////////////////////////////////////
class TR_IDMTree;

//Multi-Flaechen

typedef struct tagTRIASKLASSE {
	long lONF;
	TR_IDMTree *pIDM;
	IExtendTopRel2 *pTop;
} TRIASKLASSE;


///////////////////////////////////////////////////////////////////

#endif 	// _TRIASDEC_H
