// Anfordern verschiedener Interface - Pointer von TRIAS ----------------------
// File: TENUMS.H

#if !defined (_TENUMS_H)
#define _TENUMS_H

// Mögliche Typen von ObjektEnumeratoren --------------------------------------
enum ENUMOBJECTTYPE {
	ENUMOBJECTTYPE_IDENT = 1,	// alle Objekte eines Idents
	ENUMOBJECTTYPE_VIEW = 2,	// alle Objekte einer Sicht

	ENUMOBJECTTYPE_SELECTED = 3,	// alle selektierten Objekte
	ENUMOBJECTTYPE_ACTIVATED = 4,	// alle aktivierten Objekte
	ENUMOBJECTTYPE_LISTED = 5,	// alle recherchierten Objekte

	ENUMOBJECTTYPE_INCOMPLEX = 6,	// alle Objekte eines Komplexobjektes
	ENUMOBJECTTYPE_RELATION = 7,	// alle Objekte mit einer Relation
	
	ENUMOBJECTTYPE_REGION = 8,	// alle Objekte innerhalb eines Bereiches
	ENUMOBJECTTYPE_FEATURE = 9,	// alle Objekte mit einem Merkmalswert
};


// Mögliche Typen von StringEnumeratoren --------------------------------------
enum ENUMSTRINGTYPE {
	ENUMSTRINGTYPE_FNAMES = 1,	// DateiNamen aus einer OpenBox
};

// Functions that creates one of these enumerators ----------------------------
#if !defined(WIN16)
template<class T> class IEnum;		// forward declaration only
BOOL EXPORTTRIAS WINAPI CreateObjEnumerator (IEnum<LONG> **, ENUMOBJECTTYPE, DWORD);
#else
BOOL EXPORTTRIAS WINAPI CreateObjEnumerator (IEnumLONG **, ENUMOBJECTTYPE, DWORD);
#endif

BOOL EXPORTTRIAS WINAPI CreateStringEnumerator (IEnumString **, ENUMSTRINGTYPE, DWORD);

#endif // _TENUMS_H

