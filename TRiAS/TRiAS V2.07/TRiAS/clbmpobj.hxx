// BitmapObject, welches die zwei s/w-Masken für die neuen Punktsymbole
// repräsentiert
// File: CLBMPOBJ.HXX

#if !defined(_CLBMPOBJ_HXX)
#define _CLBMPOBJ_HXX

// Tabelle, in der einzelnen Bitmaps je ein Offset in X und Y-Richtung
// zugeordnet wird, die die genaue Größe des Punktsymboles vorgeben
typedef struct tagBMPOFFSET {
	unsigned char m_cX;
	unsigned char m_cY;
} BMPOFFSET;

class CBmpOffsets {
private:
	BMPOFFSET *m_pOffsets;		// eigentliche Tabelle
	unsigned int m_uiCnt;		// Anzahl der Tabelleneinträge

public:
		CBmpOffsets (void);
		~CBmpOffsets (void);

static CBmpOffsets *CreateInstance (ResID resTab);

	bool FInit (ResID resTab);
	
// ZugriffsFunktionen
	CoOrd FXOffset (unsigned int uiIndex);
	CoOrd FYOffset (unsigned int uiIndex);
inline	Dimension GetSize (unsigned int uiIndex) 
		{ return Dimension (FXOffset(uiIndex), FYOffset(uiIndex)); }
};
char *ReadResource (HINSTANCE hInstance, int iResID, DWORD &dwResSize);

// Klasse, welche aus der farbigen Punktschablone die zwei s/w Masken macht
class CBitmapBar {
private:
	CoOrd m_iHeight; 	// Höhe der Bitmaps
	CoOrd m_iWidth;
	HBITMAP m_hMask1;	// weiße Maske
	HBITMAP m_hMask2;	// schwarze Maske
	CBmpOffsets *m_pOffsets;	// Tabelle der BmpOffsets

public:
		CBitmapBar (void);
		~CBitmapBar (void);

static CBitmapBar *CreateInstance (ResID uiBmpRes, ResID uiBmpOffset);

	bool FInit (Bitmap &BM, ResID uiBmpOffset);

inline	HBITMAP h1stMask (void) { return m_hMask1; }
inline	HBITMAP h2ndMask (void) { return m_hMask2; }
inline	CoOrd FHeight (unsigned int uiIndex)
		{ return m_iHeight - 2*m_pOffsets -> FXOffset(uiIndex); }
inline	CoOrd FWidth (unsigned int uiIndex) 
		{ return m_iHeight - 2*m_pOffsets -> FYOffset(uiIndex); }
inline	CoOrd FXOffset (unsigned int uiIndex) 
		{ return CoOrd(uiIndex * m_iHeight) + m_pOffsets -> FXOffset (uiIndex); }
inline	CoOrd FYOffset (unsigned int uiIndex) 
		{ return m_pOffsets -> FYOffset (uiIndex); }
inline	Dimension GetSize (unsigned int uiIndex) 
		{ return m_pOffsets -> GetSize (uiIndex); }
inline	Dimension GetFullSize (void) { return Dimension (m_iWidth, m_iHeight); }
};

// Klasse, die die Zuordnung von PunktID und BitmapIndex vornimmt -------------
// Mapping des PunktID's zum Index
// Klasse, die das Mapping durchführt
class CIndexPair {
private:
	WORD m_wPunktID;
	int m_iIndex;

public:
		CIndexPair (WORD wPunktID, int iIndex);
		~CIndexPair (void) {}

	WORD &FPunktID (void) { return m_wPunktID; }
	int &FIndex (void) { return m_iIndex; }

friend void *GetPunktID (void *pObj);
friend int PunkIDCmp (void *pObj1, void *pObj2);
};

// eigentlicher Baum
class CIndexMap : public CTree {
protected:
	void UserDelete (void *);

public:
		CIndexMap (void);
		~CIndexMap (void);
	
static CIndexMap *CreateInstance (WORD *pTable, int iCnt);

	bool FInit (WORD *pTable, int iCnt);

	bool FAddItem (WORD wPunktID, int iIndex);
	CIndexPair *FFindItem (WORD wPunktID);
};
DeclareLock (CIndexMap, CIndexPair);

class CMapPunktID {
private:
	WORD *m_pTable;		// Index --> PunktID
	int m_iCnt;		// Anzahl der PunktID's
	CIndexMap *m_pMap;	// PunktID --> Index

public:
// Konstruktor/Destruktor/Initialisierung		
		CMapPunktID (void);
		~CMapPunktID (void);

static CMapPunktID *CreateInstance (ResID uiPktIDs);

	bool FInit (ResID uiPktIDs);

// Memberfunktionen
	int FGetIndex (WORD wPunktID);
	WORD FGetPunktID (int iIndex);

	CIndexMap &GetMap (void) const { return *m_pMap; }
};

// repräsentiert ein PunktSymbol mit allen seinen Eigenschaften ---------------
class CColorBitmapObject : public ShapeObject, public Transformation {
private:
	unsigned int m_uiMarker;	// PunktTyp
	Color m_1stC;			// erste Farbe
	Color m_2ndC;			// sekundäre Farbe
	CBitmapBar &m_rMasks;		// s/w Masken
	unsigned int m_fSwap : 1;	// Y-Achse kippen
#if defined(WIN32)
	unsigned int m_fHalfTone : 1;	// StretchBltMode HALFTONE anstelle von 
					// WHITEONBLACK
#endif
	short m_iRotation;		// Drehung des Punktsymboles

protected:
	void DrawEx (DWORD);       	// ColorBitmap zeichnen
	void DrawWithOutRotation (HDC hDC, HDC hTargetDC, HBITMAP hWhite, HBITMAP hBlack,
			CoOrd iOffsetX, CoOrd iOffsetY, CoOrd iMaskDimX, CoOrd iMaskDimY,
			HPALETTE hPal);

#if defined(WIN32)
	void DrawWithRotation (HDC hDC, HDC hTargetDC, HPALETTE hPal);
#endif // WIN32

	HBITMAP CreateSubMask (HDC hDC, HBITMAP hBmp, int iXOffset, int iYOffset, 
						   int iMaskDimX, int iMaskDimY, DWORD dwROP = SRCCOPY);

public:
// Konstruktoren
inline		CColorBitmapObject (Point P, Dimension D, CBitmapBar &rPM, 
				    Color C, Color C2nd, unsigned int uiMarker,
				    short iRot);

	CoOrd GetHeight (void) { return m_rMasks.FHeight(m_uiMarker); }
	CoOrd GetWidth (void) { return m_rMasks.FWidth(m_uiMarker); }

	HBITMAP WhiteMask (void) { return m_rMasks.h1stMask(); }
	HBITMAP BlackMask (void) { return m_rMasks.h2ndMask(); }

	CoOrd XOffset (void) { return m_rMasks.FXOffset(m_uiMarker); }
	CoOrd YOffset (void) { return m_rMasks.FYOffset(m_uiMarker); }

	bool toSwap (void) { return m_fSwap ? true : false; }
	void SetSwapMode (bool toSwap = true) 
		{ m_fSwap = toSwap ? true : false; }

#if defined(WIN32)
	bool isColored (void) { return m_fHalfTone ? true : false; }
	void SetBlackWhite (bool fBwMode = true) 
		{ m_fHalfTone = fBwMode ? false : true; }
	HBITMAP WhiteMask (HDC hDC, int iXOffset, int iYOffset, int iMaskDimX, int iMaskDimY)
		{ return CreateSubMask (hDC, WhiteMask(), iXOffset, iYOffset, iMaskDimX, iMaskDimY); }
	HBITMAP BlackMask (HDC hDC, int iXOffset, int iYOffset, int iMaskDimX, int iMaskDimY)
		{ return CreateSubMask (hDC, BlackMask(), iXOffset, iYOffset, iMaskDimX, iMaskDimY); }
#endif

	short GetRotation (void) { return m_iRotation; }
};

inline 	CColorBitmapObject :: CColorBitmapObject (
		Point P, Dimension D, CBitmapBar &rPM, 
		Color C, Color C2nd, unsigned int uiMarker, short iRot)
			    : ShapeObject (P, D, NULL, NULL), 
			      m_uiMarker(uiMarker), m_1stC(C),
			      m_2ndC(C2nd), m_rMasks(rPM), m_iRotation(iRot)
{
#if defined(WIN32)
	m_fHalfTone = true;
#endif
	m_fSwap = false;
}

#endif // _CLBMPOBJ_HXX
