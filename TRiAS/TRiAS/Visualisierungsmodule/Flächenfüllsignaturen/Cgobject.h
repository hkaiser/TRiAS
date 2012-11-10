// Klasse, die ein Objekt mit seiner Geometrie enthält ------------------------
// File: CGOBJECT.H

#if !defined(_CGOBJECT_H)
#define _CGOBJECT_H

// Flags, welche Objektteile verglichen werden sollen -------------------------
#define CMP_IDENT		0x01	// Identifikator vergleichen
#define CMP_OBJTYP		0x02	// ObjektTyp vergleichen
#define CMP_GEOMETRY	0x04	// Geometrie vergleichen
#define CMP_FEATURES	0x08	// Merkmale vergleichen
#define CMP_RELATIONS	0x10	// Relationen vergleichen
#define CMP_ALL			0x1f	// gesamte Objekte vergleichen

class CGObject {
private:
	OBJGEOMETRIE m_ogObj;
	unsigned int m_fInitialized : 1;
	unsigned int m_fConverted : 1;

public:
		CGObject (LONG lONr, bool fConverted = false);
	virtual	~CGObject (void);

	bool FInit (void);
	void FreeObjGeometrie (void);

// Objekte auf Identität vergleichen
	bool isEqual (CGObject &O, int fFlags = CMP_ALL);

// auf Member zugreifen
inline	long lONr (void) { return m_ogObj.lONr; }
inline	long lIdent (void) { return m_ogObj.lIdent; }
inline	short iObjTyp (void) { return m_ogObj.iObjTyp; }
inline	long lCnt (void) { return m_ogObj.lCnt; }
inline	const long *lX (void) { return m_fConverted ? NULL : (long *)m_ogObj.pdblX; }
inline	const long *lY (void) { return m_fConverted ? NULL : (long *)m_ogObj.pdblY; }
inline	const double *dX (void) { return m_fConverted ? (double *)m_ogObj.pdblX : NULL; }
inline	const double *dY (void) { return m_fConverted ? (double *)m_ogObj.pdblY : NULL; }
inline	short iKCnt (void) { return m_ogObj.iKCnt; }
inline	const int *plCnt (void) { return (const int *)m_ogObj.plCnt; }
inline	const char * Text (void) { return ((TEXTGEOMETRIE &)m_ogObj).pText; }
inline	int isA (void) { return m_ogObj.iObjTyp; }
};

#endif // _CGOBJECT_H
