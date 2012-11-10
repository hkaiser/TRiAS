// VisInfo für MFC ------------------------------------------------------------
// File: VINFOMFC.H

#if !defined(_VINFOMFC_H)
#define _VINFOMFC_H

#if !defined(TPPunkt)
#define TPCustomized	0x00		// nicht DefaultVisInfo
#define TPDefaultInfo	0x80		// DefaultVisInfo

#define TPUnknown	0x00

#define TPPunkt		0x01
#define TPLinie		0x02
#define TPFlaeche	0x04
#define TPText		0x08
#define TPAll		0x0f

#define TPKO		0x10
#define TPSO		0x20
#endif

typedef BYTE ColorVal;

#include <defattr.h>

// Klassen, die die VisualisierungsInfo für Identifikatoren enthalten ---------
#if defined(MSWIND)
typedef struct tagVISINFO 	VISINFO;
typedef struct tagPVISINFO 	PVISINFO;
typedef struct tagLVISINFO 	LVISINFO;
typedef struct tagFVISINFO 	FVISINFO;
typedef struct tagTVISINFO 	TVISINFO;
#endif

enum VisType { VT_Punkt, VT_Linie, VT_Flaeche, VT_Default, VT_Text, };

#if !defined(NOVISTYPE)

class Color {
private:
	ColorVal		R;
	ColorVal		G;
	ColorVal		B;
	ColorVal		_reserved;

public:
	Color (void)
		{ R = 0; G = 0; B = 0; _reserved = 0; }
	Color (ColorVal r, ColorVal g, ColorVal b)
		{ R = r; G = g; B = b; _reserved = 0; }

	ColorVal &	Red (void) { return R; }
	ColorVal &	Green (void) { return G; }
	ColorVal &	Blue (void) { return B; }
	ColorVal &	Reserved (void) { return _reserved; }

	operator COLORREF & (void) { return *reinterpret_cast<COLORREF *>(this); }
	operator const COLORREF & (void) const { return *reinterpret_cast<const COLORREF *>(this); }
};

// InterfaceKlasse ------------------------------------------------------------
struct CVisInfoBase {
// DatenTypen
	virtual VisType isA (void) = 0;
	virtual CVisInfoBase *Copy (void) = 0;		// clone operator
	virtual short isType (void) = 0;
	virtual CVisInfoBase *CopyCustom (void) = 0;	// clone, makes CustomVisInfo 
	virtual void CopyTo (VISINFO &) = 0;
};

// eigentliche Basisklasse ----------------------------------------------------
class VisInfo : public CVisInfoBase {
private:
	short m_Priority;		// Zeichenpriorität
	short m_Style;			// Darstellungsart
	char m_VisName[VISNAMESIZE+1];	// Name des DarstellungsTyps	

#if defined(_USE_NEWVISINFO)
// neu ab V3.00
	bool m_fLocatable;			// recherierbar
	bool m_fVisible;			// derzeit angezeigt
	char m_GeometryName[VISNAMESIZE+1];		// anzuzeigendes GeomtrieFeld
#endif // defined(_USE_NEWVISINFO)

protected:
	Color m_C;			// 1. Farbe (Punkt, Linie, Randfarbe)

public:
	char *VisName (void) { return m_VisName; }
	void SetVisName (char *lpName);
#if defined(_USE_NEWVISINFO)
	void SetGeometryName (LPCSTR pcName);
#endif // defined(_USE_NEWVISINFO)

// Konstruktor
	VisInfo (short Style, short Prio, Color C, char *pName = NULL, char *pcGeomName = NULL);

// C-Schnittstelle
	VisInfo (VISINFO &);

	void CopyTo (VISINFO &);
	
friend VisInfo * VisInfoFromC (VISINFO &, VisType = VT_Default);
friend VISINFO * VISINFOFromCPP (VisInfo *pVITemp);

// Memberfunktionen
	VisType isA (void);
	CVisInfoBase *Copy (void);		// clone operator
	CVisInfoBase *CopyCustom (void);

inline	short isType (void) { return TPCustomized | TPUnknown; }
inline	short &Priority (void) { return m_Priority; }
inline	Color &PrimColor (void) { return m_C; }
inline	short &Style (void) { return m_Style; }
#if defined(_USE_NEWVISINFO)
inline bool IsLocatable() { return m_fLocatable; }
inline void SetLocatable (bool fFlag) { m_fLocatable = fFlag; }
inline bool IsVisible() { return m_fVisible; }
inline void SetVisible (bool fFlag) { m_fVisible = fFlag; }
#endif // defined(_USE_NEWVISINFO)
};

class CDefaultVisInfo : public VisInfo {
public:
	inline	CDefaultVisInfo (void) : VisInfo (DEF_STYLE, DEF_PRIORITY, DEF_COLOR) {}
			
	CVisInfoBase *Copy (void);		// clone operator

inline	short isType (void) { return TPDefaultInfo | TPUnknown; }
};

// VisualisierungsInfo für PunktObjekte ---------------------------------------
class PVisInfo : public VisInfo {
private:
	CSize m_Size;		// Punktgröße in 0.01 [mm]
	short m_iRot;		// Drehwinkel
	Color m_SecC;	// 2. Farbe

public:
// Konstruktor
	PVisInfo (short Style, short Prio, 
		Color C, CSize Size, char *pPName = NULL, short iRot = 0, 
		Color C2 = DEF_SECCOLOR);

// C-Schnittstelle
		PVisInfo (PVISINFO &);
	void CopyTo (VISINFO &);

// Memberfunktionen
	VisType isA (void);     	// PunktInfo
	CVisInfoBase *Copy (void);		// clone operator
	CVisInfoBase *CopyCustom (void);

inline	short isType (void) { return TPCustomized | TPPunkt; }
inline	CSize &Size (void) { return m_Size; }
inline	char *PName (void) { return VisName(); }
inline	short &Rotation (void) { return m_iRot; }
inline	Color &SecColor (void) { return m_SecC; }
};

class CDefaultPVisInfo : public PVisInfo {
public:
	inline	CDefaultPVisInfo (void) : PVisInfo (DEF_STYLE_PUNKT, DEF_PRIORITY_PUNKT, 
						    DEF_COLOR, DEF_SIZE_PUNKT) {}
			
	CVisInfoBase *Copy (void);	// clone operator

inline	short isType (void) { return TPDefaultInfo | TPPunkt; }
};

// VisualisierungsInfo für LinienObjekte (Kanten) -----------------------------
class LVisInfo : public VisInfo {
private:
	short m_Width;			// Strichstärke

public:
// Konstruktor
		LVisInfo (short Style, short Prio, 
				   Color C, short W, char *pLName = NULL);

// C-Schnittstelle
		LVisInfo (LVISINFO &);
	void CopyTo (VISINFO &);

// Memberfunktionen
	VisType isA (void);		// LinienInfo
	CVisInfoBase *Copy (void);		// clone operator
	CVisInfoBase *CopyCustom (void);	

inline	short isType (void) { return TPCustomized | TPLinie; }
inline	short &Width (void) { return m_Width; }
inline	char *LName (void) { return VisName(); }
};

class CDefaultLVisInfo : public LVisInfo {
public:
		CDefaultLVisInfo (void) : LVisInfo (DEF_STYLE, DEF_PRIORITY_LINIE, 
						    DEF_COLOR, DEF_WIDTH_LINIE) {}

	CVisInfoBase *Copy (void);	// clone operator

inline	short isType (void) { return TPDefaultInfo | TPLinie; }
};

// VisualisierungsInfo für FlächenObjekte -------------------------------------
const short BMBkConture = 0x0001;			// Kontur wie Hintergrund
const short BMOpaque = short(0x8000);				// Opaque bei Flächen

// FüllModi (FVisInfo::Type())
enum FILLMODE {
	FILLMODE_HOLLOW = 0,
	FILLMODE_SOLID = 1,
	FILLMODE_BDIAGONAL = 2,		/* ///// */
	FILLMODE_VERTICAL = 3,		/* ||||| */
	FILLMODE_FDIAGONAL = 4,		/* \\\\\ */
	FILLMODE_HORIZONTAL = 5,	/* ----- */
	FILLMODE_CROSS = 6,			/* +++++ */
	FILLMODE_DIACROSS = 7,		/* xxxxx */
};

class FVisInfo : public VisInfo {
private:
	Color m_FillColor;		// Randfarbe
	short m_iWidth;			// Konturdicke
	short m_iAttrEx;		// zusätzliche Attribute
	
public:
// Konstruktor
	FVisInfo (short Style, short Prio, 
				   Color C1, Color C2, 
				   short iAttrEx, char *pFName = NULL);

// C-Schnittstelle
	FVisInfo (FVISINFO &);
	void CopyTo (VISINFO &);

// Memberfunktionen
	VisType isA (void);     		// FlaechenInfo
	CVisInfoBase *Copy (void);		// clone operator
	CVisInfoBase *CopyCustom (void);

inline	short isType (void) { return TPCustomized | TPFlaeche; }
inline	Color &SecColor (void) { return m_FillColor; }
inline	char *FName (void) { return VisName(); }
inline	short Width (void) { return m_iWidth; }
inline	FILLMODE Type (void) { return static_cast<FILLMODE>(VisInfo::Style()); }
inline	bool isBkConture (void) { return (m_iAttrEx & BMBkConture) ? true : false; }
inline	bool isOpaque (void) { return (m_iAttrEx & BMOpaque) ? true : false; }
inline	void SetWidth (short iW) { m_iWidth = iW; }
inline	short OldStyle (void) { return short((Type() + (100 * Width())) | (isOpaque() ? BMOpaque : 0)); }
inline	short AttrEx (void) { return m_iAttrEx; }
};

class CDefaultFVisInfo : public FVisInfo {
public:
	inline	CDefaultFVisInfo (void)	: FVisInfo (DEF_STYLE, DEF_PRIORITY_FLAECHE, 
						    DEF_COLOR, DEF_COLOR, 0) {}
			
	CVisInfoBase *Copy (void);	// clone operator

inline	short  isType (void) { return TPDefaultInfo | TPFlaeche; }
};

// VisualisierungsInfo für SchriftObjekte -------------------------------------
const short TV_Italic = 0x01;		// FontEigenschaften
const short TV_Underlined = 0x02;
const short TV_StrikedThru = 0x04;
const short TV_FixedPitch = 0x08;
const short TV_Bold = 0x10;
const short TV_Light = 0x20;
const short TV_BKMode = 0x40;
const short TV_Frame = 0x80;

// folgende Typen sind nicht in der DB definierbar, sondern lediglich
// bei der objektbezogenen Visulalisierung verfügbar
const short TV_LeftAlign = 0x0000;	// default: linksbündig
const short TV_CentreAlign = 0x0100;	// zentrieren
const short TV_RightAlign = 0x0200;	// rechtsbündig
const short TV_Justified = 0x0400;	// Blocksatz
const short TV_AlignStyle = 0x0700;	// alle Bits (Maske)
const short TV_RoundFrame = 0x0800;	// Runde Ecken (nur mit TV_Frame)

class TVisInfo : public VisInfo {
private:
	CSize m_Size;		// FontGröße
	short m_Type;			// FontArt
	short m_Rot;			// Drehwinkel
	short m_Orient;			// Buchstabendrehwinkel

public:
// Konstruktor
	TVisInfo (short Style, short Prio, Color C, 
				   CSize D, short Typ, short Rot = 0, 
				   char *pTName = NULL);

// C-Schnittstelle
	TVisInfo (TVISINFO &);
	void CopyTo (VISINFO &);

// Memberfunktionen
	VisType isA (void);	// TextInfo
	CVisInfoBase * Copy (void);	// Clone operator
	CVisInfoBase * CopyCustom (void);

inline	short isType (void) { return TPCustomized | TPText; }
inline	CSize &Size(void) { return m_Size; }
inline	short &Type (void) { return m_Type; }
inline	short &Rotation (void) { return m_Rot; }
inline	bool isItalic (void) { return m_Type & TV_Italic ? true : false; }
inline	bool isUnderlined (void) { return m_Type & TV_Underlined ? true : false; }
inline	bool isStrikedthru (void) { return m_Type & TV_StrikedThru ? true : false; }
inline	bool isFixedPitch (void) { return m_Type & TV_FixedPitch ? true : false; }
inline	bool isBold (void) { return m_Type & TV_Bold ? true : false; }
inline	bool isLight (void) { return m_Type & TV_Light ? true : false; }
inline	bool isNormal (void) { return !isLight() && !isBold() ? true : false; }
inline	bool BKMode (void) { return m_Type & TV_BKMode ? true : false; }
inline	bool FrameMode (void) { return m_Type & TV_Frame ? true : false; }
inline	bool RoundFrame (void) { return (m_Type & TV_RoundFrame) && FrameMode() ? true : false; }
inline	bool LeftAlign (void) { return !(m_Type & TV_AlignStyle) ? true : false; }
inline	bool CentreAlign (void) { return m_Type & TV_CentreAlign ? true : false; }
inline	bool RightAlign (void) { return m_Type & TV_RightAlign ? true : false; }
inline	bool Justified (void) { return m_Type & TV_Justified ? true : false; }
inline	short AlignStyle (void) { return m_Type & TV_AlignStyle; }
inline	char *TName (void) { return VisName(); }
inline	short &Orientation (void) { return m_Orient; }
inline	short AttrEx (void) { return HIBYTE(m_Type); }	// bisher nur objektbezogen möglich
};

class CDefaultTVisInfo : public TVisInfo {
public:
	inline	CDefaultTVisInfo (void)	: TVisInfo (DEF_STYLE, DEF_PRIORITY_TEXT, 
						    DEF_COLOR, DEF_SIZE_TEXT, DEF_TYP_TEXT) 
		{}
			
	CVisInfoBase *Copy (void);	// clone operator

inline	short isType (void) { return TPDefaultInfo | TPText; }
};

#endif // NOVISTYPE

#endif // _VINFOMFC_H
