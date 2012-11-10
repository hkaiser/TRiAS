// VisInfo --------------------------------------------------------------------
// File: VISINFO.HXX

#if !defined(_VISINFO_HXX)
#define _VISINFO_HXX

#if !defined(TPPunkt)
#define TPCustomized	0x00		// nicht DefaultVisInfo
#define TPDefaultInfo	0x80		// DefaultVisInfo

#define TPUnknown	0x00

#define TPPunkt		OTPunkt
#define TPLinie		OTLinie
#define TPFlaeche	OTFlaeche
#define TPText		OTText
#define TPAll		(OTPunkt|OTLinie|OTFlaeche|OTText)

#define TPKO		OTKO
#define TPSO		OTSachObjekt
#endif

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

// InterfaceKlasse ------------------------------------------------------------
struct CVisInfoBase {
// DatenTypen
	virtual VisType isA (void) = 0;
	virtual CVisInfoBase *Copy (void) = 0;		// clone operator
	virtual short isType (void) = 0;
	virtual CVisInfoBase *CopyCustom (void) = 0;	// clone, makes CustomVisInfo 
#if defined(MSWIND)
	virtual void CopyTo (VISINFO &) = 0;
#endif // MSWIND
};

// eigentliche Basisklasse ----------------------------------------------------
class VisInfo : public CVisInfoBase {
private:
	short m_Priority;		// Zeichenpriorität
	short m_Style;			// Darstellungsart
	char m_VisName[VISNAMESIZE+1];	// Name des DarstellungsTyps	

protected:
	Color m_C;			// 1. Farbe (Punkt, Linie, Randfarbe)

public:
	char *VisName (void) { return m_VisName; }
_TRIAS02_ENTRY void EXPORT02 SetVisName (char *lpName);

// Konstruktor
	_TRIAS02_ENTRY EXPORT02 VisInfo (short Style, short Prio, 
				  Color C, char *pName = NULL);

#if defined(MSWIND)
// C-Schnittstelle
	_TRIAS02_ENTRY EXPORT02 VisInfo (VISINFO &);

_TRIAS02_ENTRY void EXPORT02 CopyTo (VISINFO &);
	
_TRIAS02_ENTRY friend VisInfo * EXPORT02 VisInfoFromC (VISINFO &, VisType = VT_Default);
_TRIAS02_ENTRY friend VISINFO * EXPORT02 VISINFOFromCPP (VisInfo *pVITemp);
#endif

// Memberfunktionen
_TRIAS02_ENTRY VisType EXPORT02 isA (void);
_TRIAS02_ENTRY CVisInfoBase *EXPORT02 Copy (void);		// clone operator
_TRIAS02_ENTRY CVisInfoBase *EXPORT02 CopyCustom (void);

	short isType (void) { return TPCustomized | TPUnknown; }
	short &Priority (void) { return m_Priority; }
	Color &PrimColor (void) { return m_C; }
	short &Style (void) { return m_Style; }
};

#if defined(__WATCOMC__)
// must look ahead to determine wether construct is declaration/type or expression
#pragma warning 604 4;
// contruct resolved as expression
#pragma warning 595 4;
#endif
class CDefaultVisInfo : public VisInfo {
public:
	inline	CDefaultVisInfo (void) : VisInfo (DEF_STYLE, DEF_PRIORITY, DEF_COLOR) {};
			
_TRIAS02_ENTRY CVisInfoBase *EXPORT02 Copy (void);		// clone operator

inline	short isType (void) { return TPDefaultInfo | TPUnknown; }
};

// VisualisierungsInfo für PunktObjekte ---------------------------------------
class PVisInfo : public VisInfo {
private:
	Dimension m_Size;		// Punktgröße in 0.01 [mm]
	short m_iRot;			// Drehwinkel
	Color m_SecC;			// 2. Farbe

public:
// Konstruktor
	_TRIAS02_ENTRY EXPORT02 PVisInfo (short Style, short Prio, 
		Color C, Dimension Size, char *pPName = NULL, short iRot = 0, 
		Color C2 = DEF_SECCOLOR);

#if defined(MSWIND)
// C-Schnittstelle
	_TRIAS02_ENTRY EXPORT02 PVisInfo (PVISINFO &);

_TRIAS02_ENTRY void EXPORT02 CopyTo (VISINFO &);
#endif

// Memberfunktionen
_TRIAS02_ENTRY VisType EXPORT02 isA (void);     	// PunktInfo
_TRIAS02_ENTRY CVisInfoBase *EXPORT02 Copy (void);		// clone operator
_TRIAS02_ENTRY CVisInfoBase *EXPORT02 CopyCustom (void);
	short isType (void) { return TPCustomized | TPPunkt; }

inline	Dimension &Size (void) { return m_Size; }
inline	char *PName (void) { return VisName(); }
inline	short &Rotation (void) { return m_iRot; }
inline	Color &SecColor (void) { return m_SecC; }
};

class CDefaultPVisInfo : public PVisInfo {
public:
	inline	CDefaultPVisInfo (void) : PVisInfo (DEF_STYLE_PUNKT, DEF_PRIORITY_PUNKT, 
						    DEF_COLOR, DEF_SIZE_PUNKT) {};
			
_TRIAS02_ENTRY CVisInfoBase *EXPORT02 Copy (void);	// clone operator

inline	short isType (void) { return TPDefaultInfo | TPPunkt; }
};

// VisualisierungsInfo für LinienObjekte (Kanten) -----------------------------
class LVisInfo : public VisInfo {
private:
	short m_Width;			// Strichstärke

public:
// Konstruktor
	_TRIAS02_ENTRY EXPORT02 LVisInfo (short Style, short Prio, 
				   Color C, short W, char *pLName = NULL);

#if defined(MSWIND)
// C-Schnittstelle
	_TRIAS02_ENTRY EXPORT02 LVisInfo (LVISINFO &);
_TRIAS02_ENTRY void EXPORT02 CopyTo (VISINFO &);
#endif

// Memberfunktionen
_TRIAS02_ENTRY VisType EXPORT02 isA (void);		// LinienInfo
_TRIAS02_ENTRY CVisInfoBase *EXPORT02 Copy (void);		// clone operator
_TRIAS02_ENTRY CVisInfoBase *EXPORT02 CopyCustom (void);	
inline	short isType (void) { return TPCustomized | TPLinie; }

inline	short &Width (void) { return m_Width; }
inline	char *LName (void) { return VisName(); }
};

class CDefaultLVisInfo : public LVisInfo {
public:
		CDefaultLVisInfo (void) : LVisInfo (DEF_STYLE, DEF_PRIORITY_LINIE, 
						    DEF_COLOR, DEF_WIDTH_LINIE) {};

_TRIAS02_ENTRY CVisInfoBase *EXPORT02 Copy (void);	// clone operator

inline	short isType (void) { return TPDefaultInfo | TPLinie; }
};

// VisualisierungsInfo für FlächenObjekte -------------------------------------
const short BMBkConture = 0x0001;			// Kontur wie Hintergrund
const short BMOpaque = short(0x8000);				// Opaque bei Flächen

#if defined(OLDVISINFO)
class FVisInfo : public VisInfo {
private:
	Color m_FillColor;		// Randfarbe

public:
// Konstruktor
	_TRIAS02_ENTRY EXPORT02 FVisInfo (short Style, short Prio, 
				   Color C1, Color C2, char *pFName = NULL);

#if defined(MSWIND)
// C-Schnittstelle
	_TRIAS02_ENTRY EXPORT02 FVisInfo (FVISINFO &);
_TRIAS02_ENTRY void EXPORT02 CopyTo (VISINFO &);
#endif

// Memberfunktionen
_TRIAS02_ENTRY VisType EXPORT02 isA (void);     		// FlaechenInfo
_TRIAS02_ENTRY CVisInfoBase *EXPORT02 Copy (void);		// clone operator
_TRIAS02_ENTRY CVisInfoBase *EXPORT02 CopyCustom (void);
inline	short isType (void) { return TPCustomized | TPFlaeche; }

inline	Color &SecColor (void) { return m_FillColor; }
inline	char *FName (void) { return VisName(); }
inline	short Width (void) { return short((VisInfo :: Style() & ~BMOpaque) / 100); }
inline	short Type (void) { return short((VisInfo :: Style() & ~BMOpaque) % 100); }
inline	short isOpaque (void) { return short((VisInfo :: Style() & BMOpaque) != 0); }
inline	void SetWidth (short iW) { VisInfo :: Style() = short((iW * 100) | (VisInfo :: Style() & BMOpaque) | Type()); }
};
#else // OLDVISINFO
class FVisInfo : public VisInfo {
private:
	Color m_FillColor;		// Randfarbe
	short m_iWidth;			// Konturdicke
	short m_iAttrEx;		// zusätzliche Attribute
	
public:
// Konstruktor
	_TRIAS02_ENTRY EXPORT02 FVisInfo (short Style, short Prio, 
				   Color C1, Color C2, 
				   short iAttrEx, char *pFName = NULL);

#if defined(MSWIND)
// C-Schnittstelle
	_TRIAS02_ENTRY EXPORT02 FVisInfo (FVISINFO &);
_TRIAS02_ENTRY void EXPORT02 CopyTo (VISINFO &);
#endif

// Memberfunktionen
_TRIAS02_ENTRY VisType EXPORT02 isA (void);     		// FlaechenInfo
_TRIAS02_ENTRY CVisInfoBase *EXPORT02 Copy (void);		// clone operator
_TRIAS02_ENTRY CVisInfoBase *EXPORT02 CopyCustom (void);
inline	short isType (void) { return TPCustomized | TPFlaeche; }

inline	Color &SecColor (void) { return m_FillColor; }
inline	char *FName (void) { return VisName(); }
inline	short Width (void) { return m_iWidth; }
inline	short Type (void) { return VisInfo :: Style(); }
inline	bool isBkConture (void) { return (m_iAttrEx & BMBkConture) ? true : false; }
inline	bool isOpaque (void) { return (m_iAttrEx & BMOpaque) ? true : false; }
inline	void SetWidth (short iW) { m_iWidth = iW; }
inline	short OldStyle (void) 
	{ return short((Type() + (100 * Width())) | (isOpaque() ? BMOpaque : 0)); }
inline	short AttrEx (void) { return m_iAttrEx; }
inline	void SetAttrEx (short iAttrEx) { m_iAttrEx = iAttrEx; }
};
#endif // OLDVISINFO

class CDefaultFVisInfo : public FVisInfo {
public:
	inline	CDefaultFVisInfo (void)	: FVisInfo (DEF_STYLE, DEF_PRIORITY_FLAECHE, 
						    DEF_COLOR, DEF_COLOR, 0) {};
			
_TRIAS02_ENTRY CVisInfoBase *EXPORT02 Copy (void);	// clone operator

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
	Dimension m_Size;		// FontGröße
	short m_Type;			// FontArt
	short m_Rot;			// Drehwinkel
	short m_Orient;			// Buchstabendrehwinkel

public:
// Konstruktor
	_TRIAS02_ENTRY EXPORT02 TVisInfo (short Style, short Prio, Color C, 
				   Dimension D, short Typ, short Rot = 0, 
				   char *pTName = NULL);

#if defined(MSWIND)
// C-Schnittstelle
	_TRIAS02_ENTRY EXPORT02 TVisInfo (TVISINFO &);
_TRIAS02_ENTRY void EXPORT02 CopyTo (VISINFO &);
#endif

// Memberfunktionen
_TRIAS02_ENTRY VisType EXPORT02 isA (void);	// TextInfo
_TRIAS02_ENTRY CVisInfoBase * EXPORT02 Copy (void);	// Clone operator
_TRIAS02_ENTRY CVisInfoBase * EXPORT02 CopyCustom (void);
inline	short isType (void) { return TPCustomized | TPText; }

inline	Dimension &Size(void) { return m_Size; }
inline	short &Type (void) { return m_Type; }
inline	short &Rotation (void) { return m_Rot; }

inline	bool isItalic (void) { return m_Type & TV_Italic; }
inline	bool isUnderlined (void) { return m_Type & TV_Underlined; }
inline	bool isStrikedthru (void) { return m_Type & TV_StrikedThru; }
inline	bool isFixedPitch (void) { return m_Type & TV_FixedPitch; }
inline	bool isBold (void) { return m_Type & TV_Bold; }
inline	bool isLight (void) { return m_Type & TV_Light; }
inline	bool isNormal (void) { return !isLight() && !isBold(); }
inline	bool BKMode (void) { return m_Type & TV_BKMode; }
inline	bool FrameMode (void) { return m_Type & TV_Frame; }
inline	bool RoundFrame (void) { return (m_Type & TV_RoundFrame) && FrameMode(); }

inline	bool LeftAlign (void) { return !(m_Type & TV_AlignStyle); }
inline	bool CentreAlign (void) { return m_Type & TV_CentreAlign; }
inline	bool RightAlign (void) { return m_Type & TV_RightAlign; }
inline	bool Justified (void) { return m_Type & TV_Justified; }
inline	short AlignStyle (void) { return m_Type & TV_AlignStyle; }
	
inline	char *TName (void) { return VisName(); }

inline	short &Orientation (void) { return m_Orient; }
#if !defined(OLDVISINFO)
inline	short AttrEx (void) { return HIBYTE(m_Type); }	// bisher nur objektbezogen möglich
#endif // !OLDVISINFO
};

class CDefaultTVisInfo : public TVisInfo {
public:
	inline	CDefaultTVisInfo (void)	: TVisInfo (DEF_STYLE, DEF_PRIORITY_TEXT, 
						    DEF_COLOR, DEF_SIZE_TEXT, DEF_TYP_TEXT) 
		{};
			
_TRIAS02_ENTRY CVisInfoBase *EXPORT02 Copy (void);	// clone operator
inline	short isType (void) { return TPDefaultInfo | TPText; }
};

#endif // NOVISTYPE

#endif // _VISINFO_HXX
