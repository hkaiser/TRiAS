// Klasse, die ein Objekt mit seiner Geometrie enthält ------------------------
// File: CGOBJECT.HXX

#if !defined(_CGOBJECT_HXX)
#define _CGOBJECT_HXX

// Flags, welche Objektteile verglichen werden sollen -------------------------
#define CMP_IDENT	0x01	// Identifikator vergleichen
#define CMP_OBJTYP	0x02	// ObjektTyp vergleichen
#define CMP_GEOMETRY	0x04	// Geometrie vergleichen
#define CMP_FEATURES	0x08	// Merkmale vergleichen
#define CMP_RELATIONS	0x10	// Relationen vergleichen
#define CMP_ALL		0x1f	// gesamte Objekte vergleichen

class CGObject {
private:
	OBJGEOMETRIE m_ogObj;
	unsigned int m_fInitialized : 1;

protected:
	bool FInit (void);

public:
		CGObject (LONG lONr);
	virtual	~CGObject (void);

	void FreeObjGeometrie (void);

	long lONr (void) { return m_ogObj.lONr; }
	long lIdent (void) { return m_ogObj.lIdent; }
	short iObjTyp (void) { return m_ogObj.iObjTyp; }
	long lCnt (void) { return m_ogObj.lCnt; }
	const void *X (void) { return m_ogObj.pdblX; }
	const void *Y (void) { return m_ogObj.pdblY; }
	short iKCnt (void) { return m_ogObj.iKCnt; }
	const long *plCnt (void) { return m_ogObj.plCnt; }
	const char * Text (void) { return ((TEXTGEOMETRIE &)m_ogObj).pText; }

// Objekte auf Identität vergleichen
	bool isEqual (CGObject &O, int fFlags = CMP_ALL);
};

// sonstige Funktionen --------------------------------------------------------
bool isSelected (HWND hWnd, LONG lONr);	// ist Objekt in ORFenster selektiert ?

#endif // _CGOBJECT_HXX
