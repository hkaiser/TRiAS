///////////////////////////////////////////////////////////////////////////
// @doc 
// @module VISINFO.HXX | Description goes here

#if !defined(_VISINFO_HXX__517B38C8_E21D_11D2_9BD4_001B20524153__INCLUDED_)
#define _VISINFO_HXX__517B38C8_E21D_11D2_9BD4_001B20524153__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(_DEBUG)
#undef THIS_FILE
#define THIS_FILE __FILE__
#endif // _DEBUG

#if !defined(TPCustomized)
#define TPCustomized	0x00		// nicht DefaultVisInfo
#define TPDefaultInfo	0x80		// DefaultVisInfo
#endif // TPCustomized

#if !defined(TPPunkt)
#define TPUnknown	0x00

#define TPPunkt		OTPunkt
#define TPLinie		OTLinie
#define TPFlaeche	OTFlaeche
#define TPText		OTText
#define TPAll		(OTPunkt|OTLinie|OTFlaeche|OTText)

#define TPKO		OTKO
#define TPSO		OTSachObjekt
#endif // TPPunkt

#include <defattr.h>

#if !defined(__CV__)	// __MFC__
typedef BYTE ColorVal;

class Color 
{
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

class Dimension :
	public CSize
{
public:
	Dimension() : CSize() {}
	Dimension (const Dimension &dim) : CSize (dim.cx, dim.cy) {}
	Dimension (const CSize &dim) : CSize (dim) {}

	long &Width() { return cx; }
	long &Height() { return cy; }
};

#endif // !__CV__

///////////////////////////////////////////////////////////////////////////////
// Klassen, die die VisualisierungsInfo für Identifikatoren enthalten 
typedef struct tagVISINFO 	VISINFO;
typedef struct tagPVISINFO 	PVISINFO;
typedef struct tagLVISINFO 	LVISINFO;
typedef struct tagFVISINFO 	FVISINFO;
typedef struct tagTVISINFO 	TVISINFO;

enum VisType { VT_Punkt, VT_Linie, VT_Flaeche, VT_Default, VT_Text, };

///////////////////////////////////////////////////////////////////////////////
// InterfaceKlasse 
struct CVisInfoBase 
{
// DatenTypen
	virtual VisType isA (void) = 0;
	virtual CVisInfoBase *Copy (void) = 0;		// clone operator
	virtual short isType (void) = 0;
	virtual CVisInfoBase *CopyCustom (void) = 0;	// clone, makes CustomVisInfo 
	virtual void CopyTo (VISINFO &) = 0;
};

///////////////////////////////////////////////////////////////////////////////
// eigentliche Basisklasse 

// Name des Default-GeometrieFeldes
extern "C" const TCHAR __declspec(selectany) g_cbGeometryFieldName[] = TEXT("DefaultGeometry");

class VisInfo : 
	public CVisInfoBase 
{
private:
	short m_Priority;			// Zeichenpriorität
	short m_Style;				// Darstellungsart
	char m_VisName[VISNAMESIZE+1];			// Name des DarstellungsTyps	
	bool m_fLocatable;						// recherierbar
	bool m_fVisible;						// derzeit angezeigt
	char m_GeometryName[VISNAMESIZE+1];		// anzuzeigendes GeomtrieFeld

protected:
	Color m_C;			// 1. Farbe (Punkt, Linie, Randfarbe)

public:
	const char *VisName (void) { return m_VisName; }
	void SetVisName (const char *lpName)
	{
		if (lpName) {
			strncpy (m_VisName, lpName, VISNAMESIZE);	
			m_VisName[VISNAMESIZE] = '\0';
		} else
			m_VisName[0] = '\0';
	}

// Konstruktor
	VisInfo() : 
		m_Priority(DEF_PRIORITY), m_Style(DEF_STYLE), m_C(DEF_COLOR), 
		m_fLocatable(true), m_fVisible(true)
	{ 
		SetVisName (NULL); 
		SetGeometryName (NULL);
	}
	VisInfo (short Style, short Prio, Color C, const char *pName = NULL, const char *pcGeomName = NULL) :
		m_Priority(Prio), m_Style(Style), m_C(C), m_fLocatable(true), m_fVisible(true)
	{
	// Memberwerte setzen
		m_Style = Style;         // Darstellungsart
		m_Priority = Prio;       // Darstellungspriorität
		m_C = C;                 // Farbe (Punkt-, Linien-, Füllfarbe)
		SetVisName (pName);
		SetGeometryName (pcGeomName);
	}

// C-Schnittstelle
	VisInfo (VISINFO &VI)
	{
		TX_ASSERT_POINTER(&VI, VISINFO);
		TX_ASSERT(VI.dwSize >= sizeof(VISINFO));

	// Memberwerte setzen
		m_Style = VI.m_Style;		// Darstellungsart
		m_Priority = VI.m_Priority;	// Darstellungspriorität
		m_C = *(Color *)&VI.m_C;	// Farbe (Punkt-, Linien-, Füllfarbe)
		
		SetLocatable (VI.m_fLocatable);
		SetVisible (VI.m_fVisible);

		SetVisName (VI.m_VisName);
		SetGeometryName (VI.m_GeomName);
	}

	void CopyTo (VISINFO &VI)
	{
		TX_ASSERT(TIsValidAddress(&VI, sizeof(VISINFO), true));
		TX_ASSERT(VI.dwSize >= sizeof(VISINFO));

		VI.m_Style = m_Style;
		VI.m_Priority = m_Priority;
		VI.m_C = *(COLORREF *)&m_C;
		VI.m_fLocatable = IsLocatable();
		VI.m_fVisible = IsVisible();

		memset (VI.m_VisName, '\0', VISNAMESIZE);
		strncpy (VI.m_VisName, m_VisName, VISNAMESIZE);	

		memset (VI.m_GeomName, '\0', VISNAMESIZE);
		strncpy (VI.m_GeomName, m_GeometryName, VISNAMESIZE);	
	}

	friend inline VisInfo * VisInfoFromC (VISINFO &, VisType = VT_Default);
	friend inline VISINFO * VISINFOFromCPP (VisInfo *pVITemp);

// Memberfunktionen
	VisType isA (void) { return VT_Default; }
	CVisInfoBase *CopyCustom (void)		// clone operator
	{ 
	VisInfo *pVI = NULL;

		TX_TRY(pVI = new VisInfo (Style(), Priority(), PrimColor(), VisName(), GeometryName())); 
		if (NULL != pVI) {
			pVI -> SetLocatable (IsLocatable());
			pVI -> SetVisible (IsVisible());
		}
		return pVI;
	}
	CVisInfoBase *Copy (void)
	{ 
		return CopyCustom();
	}

	short isType (void) { return TPCustomized | TPUnknown; }
	short &Priority (void) { return m_Priority; }
	Color &PrimColor (void) { return m_C; }
	short &Style (void) { return m_Style; }

	bool IsLocatable() { return m_fLocatable; }
	void SetLocatable (bool fFlag) { m_fLocatable = fFlag; }
	bool IsVisible() { return m_fVisible; }
	void SetVisible (bool fFlag) { m_fVisible = fFlag; }

	const char *GeometryName() { return (m_GeometryName[0] != '\0') ? m_GeometryName : g_cbGeometryFieldName; }
	void SetGeometryName (LPCSTR pcName)
	{
		if (pcName) {
			TX_ASSERT(TIsValidString(pcName));

			strncpy (m_GeometryName, pcName, VISNAMESIZE);	
			m_GeometryName[VISNAMESIZE] = '\0';
		} else
			m_GeometryName[0] = '\0';
	}
};

class OldVisInfo : 
	public CVisInfoBase 
{
private:
	short m_Priority;			// Zeichenpriorität
	short m_Style;				// Darstellungsart
	char m_VisName[VISNAMESIZE+1];			// Name des DarstellungsTyps	

protected:
	Color m_C;			// 1. Farbe (Punkt, Linie, Randfarbe)

public:
	const char *VisName (void) { return m_VisName; }
	void SetVisName (const char *lpName)
	{
		if (lpName) {
			strncpy (m_VisName, lpName, VISNAMESIZE);	
			m_VisName[VISNAMESIZE] = '\0';
		} else
			m_VisName[0] = '\0';
	}

// Konstruktor
	OldVisInfo() : 
		m_Priority(DEF_PRIORITY), m_Style(DEF_STYLE), m_C(DEF_COLOR)
	{ 
		SetVisName (NULL); 
	}
	OldVisInfo (short Style, short Prio, Color C, const char *pName = NULL, const char *pcGeomName = NULL)
	{
	// Memberwerte setzen
		m_Style = Style;         // Darstellungsart
		m_Priority = Prio;       // Darstellungspriorität
		m_C = C;                 // Farbe (Punkt-, Linien-, Füllfarbe)
		SetVisName (pName);
	}

// C-Schnittstelle
	OldVisInfo (VISINFO &VI)
	{
		TX_ASSERT_POINTER(&VI, VISINFO);
		TX_ASSERT(VI.dwSize >= sizeof(VISINFO));

	// Memberwerte setzen
		m_Style = VI.m_Style;		// Darstellungsart
		m_Priority = VI.m_Priority;	// Darstellungspriorität
		m_C = *(Color *)&VI.m_C;	// Farbe (Punkt-, Linien-, Füllfarbe)

		SetVisName (VI.m_VisName);
	}

	void CopyTo (VISINFO &VI)
	{
		TX_ASSERT(TIsValidAddress(&VI, sizeof(VISINFO), true));
		TX_ASSERT(VI.dwSize >= sizeof(VISINFO));

		VI.m_Style = m_Style;
		VI.m_Priority = m_Priority;
		VI.m_C = *(COLORREF *)&m_C;
		VI.m_fLocatable = true;
		VI.m_fVisible = true;

		memset (VI.m_VisName, '\0', VISNAMESIZE);
		strncpy (VI.m_VisName, m_VisName, VISNAMESIZE);	
	}
	
	friend inline OldVisInfo * OldVisInfoFromC (VISINFO &, VisType = VT_Default);
	friend inline VISINFO * VISINFOFromCPP (OldVisInfo *pVITemp);

// Memberfunktionen
	VisType isA (void) { return VT_Default; }
	CVisInfoBase *CopyCustom (void)		// clone operator
	{ 
		return new OldVisInfo (Style(), Priority(), PrimColor(), VisName()); 
	}
	CVisInfoBase *Copy (void)
	{ 
		return CopyCustom();
	}

	short isType (void) { return TPCustomized | TPUnknown; }
	short &Priority (void) { return m_Priority; }
	Color &PrimColor (void) { return m_C; }
	short &Style (void) { return m_Style; }

	bool IsLocatable() { return true; }
	void SetLocatable (bool fFlag) {}
	bool IsVisible() { return true; }
	void SetVisible (bool fFlag) {}

	const char *GeometryName() { return g_cbGeometryFieldName; }
	void SetGeometryName (LPCSTR pcName) {}
};

#if defined(__WATCOMC__)
#pragma warning 604 4;	// must look ahead to determine wether construct is declaration/type or expression
#pragma warning 595 4;	// contruct resolved as expression
#endif

inline short CorrectPriority (short iPrio)		// #HK960705
{
	return iPrio; //((iPrio >= 0 && iPrio < 1000) ? iPrio : DEF_PRIORITY);
}

template<class T>
class CDefaultVisInfoT : 
	public T 
{
public:
	inline CDefaultVisInfoT (void) : T (DEF_STYLE, DEF_PRIORITY, DEF_COLOR) {}
			
	CVisInfoBase *Copy (void)		// clone operator
	{ 
		return new CDefaultVisInfoT<T>(); 
	}
	inline short isType (void) { return TPDefaultInfo | TPUnknown; }
};

// VisualisierungsInfo für PunktObjekte ---------------------------------------
template<class T>
class PVisInfoT : 
	public T
{
private:
	Dimension m_Size;		// Punktgröße in 0.01 [mm]
	short m_iRot;			// Drehwinkel
	Color m_SecC;			// 2. Farbe

public:
// Konstruktor
	PVisInfoT() : 
		T (DEF_STYLE_PUNKT, DEF_PRIORITY_PUNKT, DEF_COLOR), 
		m_Size(DEF_SIZE_PUNKT), m_iRot(0), m_SecC(DEF_SECCOLOR) 
	{
	}
	PVisInfoT (short Style, short Prio, Color PColor, Dimension Size, const char *pPName = NULL, 
			   short iRot = 0, Color SecC = DEF_SECCOLOR, const char *pcGeomName = NULL)
	  : T (Style, CorrectPriority (Prio), PColor, pPName, pcGeomName)
	{
		m_Size = Size;		// PunktSymbolGröße
		m_iRot = iRot;		// Drehwinkel
		m_SecC = SecC;		// zweite Farbe
	}

// C-Schnittstelle
	PVisInfoT (PVISINFO &PVI) : T (PVI.m_VI)
	{
		TX_ASSERT_POINTER(&PVI, PVISINFO);
		TX_ASSERT(PVI.m_VI.dwSize == sizeof(PVISINFO));

		m_Size = *(Dimension *)&PVI.m_Size;
		m_iRot = PVI.m_iRot;
		m_SecC = (Color &)PVI.m_SecC;
	}
	void CopyTo (VISINFO &PVI)
	{
		TX_ASSERT(TIsValidAddress(&PVI, sizeof(PVISINFO), true));
		TX_ASSERT(PVI.dwSize == sizeof(PVISINFO));

		T::CopyTo (PVI);
		((PVISINFO &)PVI).m_Size = *(SIZE *)&m_Size;
		((PVISINFO &)PVI).m_iRot = m_iRot;
		((PVISINFO &)PVI).m_SecC = (COLORREF &)m_SecC;
	}

// Memberfunktionen
	VisType isA (void) { return VT_Punkt; }
	CVisInfoBase *CopyCustom (void)		// clone operator
	{ 
	PVisInfoT<T> *pPVI = NULL;

		TX_TRY(pPVI = new PVisInfoT<T> (Style(), Priority(), PrimColor(), Size(), PName(), Rotation(), SecColor(), GeometryName())); 
		if (NULL != pPVI) {
			pPVI -> SetLocatable (IsLocatable());
			pPVI -> SetVisible (IsVisible());
		}
		return pPVI;
	}
	CVisInfoBase *Copy (void)
	{ 
		return CopyCustom();
	}

	inline short isType (void) { return TPCustomized | TPPunkt; }

	inline Dimension &Size (void) { return m_Size; }
	inline const char *PName (void) { return VisName(); }
	inline short &Rotation (void) { return m_iRot; }
	inline Color &SecColor (void) { return m_SecC; }
};

template<class T>
class CDefaultPVisInfoT : 
	public PVisInfoT<T> 
{
public:
	inline CDefaultPVisInfoT (void) : 
		PVisInfoT<T> (DEF_STYLE_PUNKT, DEF_PRIORITY_PUNKT, DEF_COLOR, DEF_SIZE_PUNKT) 
	{
	}
			
	CVisInfoBase *Copy (void)	// clone operator
	{ 
		return new CDefaultPVisInfoT<T>(); 
	}
	inline short isType (void) { return TPDefaultInfo | TPPunkt; }
};

// VisualisierungsInfo für LinienObjekte (Kanten) -----------------------------
inline short CorrectLineStyle (short iStyle)
{
	return ((iStyle >= 0) ? iStyle : 0);         // default: PunktTyp 0
}

template<class T>
class LVisInfoT : 
	public T 
{
private:
	short m_Width;			// Strichstärke

public:
// Konstruktor
	LVisInfoT() : T (DEF_STYLE, DEF_PRIORITY_LINIE, DEF_COLOR), m_Width(DEF_WIDTH_LINIE)
	{
	}
	LVisInfoT (short Style, short Prio, Color LColor, short Size, const char *pLName = NULL, const char *pcGeomName = NULL)
		: T (CorrectLineStyle (Style), CorrectPriority (Prio), LColor, pLName, pcGeomName)
	{
		m_Width = Size;           // StrichStärke
	}

// C-Schnittstelle
	LVisInfoT (LVISINFO &LVI) : T (LVI.m_VI)
	{
		TX_ASSERT_POINTER(&LVI, LVISINFO);
		TX_ASSERT(LVI.m_VI.dwSize == sizeof(LVISINFO));

		m_Width = LVI.m_Width;           // StrichStärke
	}
	void CopyTo (VISINFO &LVI)
	{
		TX_ASSERT(TIsValidAddress(&LVI, sizeof(LVISINFO), true));
		TX_ASSERT(LVI.dwSize == sizeof(LVISINFO));

		T::CopyTo (LVI);
		((LVISINFO &)LVI).m_Width = m_Width;
	}

// Memberfunktionen
	VisType isA (void) { return VT_Linie; }
	CVisInfoBase *CopyCustom (void)		// clone operator
	{ 
	LVisInfoT<T> *pLVI = NULL;

		TX_TRY(pLVI = new LVisInfoT<T> (Style(), Priority(), PrimColor(), Width(), LName(), GeometryName())); 
		if (NULL != pLVI) {
			pLVI -> SetLocatable (IsLocatable());
			pLVI -> SetVisible (IsVisible());
		}
		return pLVI;
	}
	CVisInfoBase *Copy (void)
	{ 
		return CopyCustom();
	}

	inline short isType (void) { return TPCustomized | TPLinie; }
	inline short &Width (void) { return m_Width; }
	inline const char *LName (void) { return VisName(); }
};

template<class T>
class CDefaultLVisInfoT : 
	public LVisInfoT<T> 
{
public:
	CDefaultLVisInfoT (void) : 
		LVisInfoT<T> (DEF_STYLE, DEF_PRIORITY_LINIE, DEF_COLOR, DEF_WIDTH_LINIE) 
	{
	}

	CVisInfoBase *Copy (void)	// clone operator
	{ 
		return new CDefaultLVisInfoT<T>(); 
	}
	inline short isType (void) { return TPDefaultInfo | TPLinie; }
};

// VisualisierungsInfo für FlächenObjekte -------------------------------------
const int BMBkConture = 0x0001;			// Kontur wie Hintergrund
const int BMOpaque = int(0x8000);				// Opaque bei Flächen

template<class T>
class FVisInfoT : 
	public T
{
private:
	Color m_FillColor;		// Randfarbe
	short m_iWidth;			// Konturdicke
	short m_iAttrEx;		// zusätzliche Attribute
	
public:
// Konstruktor
	FVisInfoT() : 
		T (DEF_STYLE, DEF_PRIORITY_FLAECHE, DEF_COLOR), 
		m_FillColor(DEF_SECCOLOR)
	{
	}
	FVisInfoT (short iStyle, short Prio, Color FColor, Color BColor, short iAttrEx, 
			   const char *pFName = NULL, const char *pcGeomName = NULL)
		: T (DecomposeStyleFStyle(iStyle), CorrectPriority(Prio), FColor, pFName, pcGeomName)
	{
		m_FillColor = BColor;
		m_iWidth = ((iStyle & ~::BMOpaque) & 0xFFFF) / 100;
		m_iAttrEx = ((iStyle & ::BMOpaque) | (iAttrEx & ~::BMOpaque)) & 0xFFFF;
	}
	static short DecomposeStyleFStyle (short iStyle)
	{
		return ((iStyle & ~::BMOpaque) & 0xFFFF) % 100;
	}

// C-Schnittstelle
	FVisInfoT (FVISINFO &FVI) : T (FVI.m_VI)
	{
		TX_ASSERT_POINTER(&FVI, FVISINFO);
		TX_ASSERT(FVI.m_VI.dwSize == sizeof(FVISINFO));

		m_FillColor = *(Color *)&FVI.m_FC;
		m_iWidth = FVI.m_iWidth;
		m_iAttrEx = FVI.m_iAttrEx;
	}
	void CopyTo (VISINFO &FVI)
	{
		TX_ASSERT(TIsValidAddress(&FVI, sizeof(FVISINFO), true));
		TX_ASSERT(FVI.dwSize == sizeof(FVISINFO));

		T::CopyTo (FVI);
		((FVISINFO &)FVI).m_FC = *(COLORREF *)&m_FillColor;
		((FVISINFO &)FVI).m_iWidth = m_iWidth;
		((FVISINFO &)FVI).m_iAttrEx = m_iAttrEx;
	}

// Memberfunktionen
	VisType isA (void) { return VT_Flaeche; }
	CVisInfoBase *CopyCustom (void)		// clone operator
	{ 
	FVisInfoT<T> *pFVI = NULL;

		TX_TRY(pFVI = new FVisInfoT<T> (OldStyle(), Priority(), PrimColor(), SecColor(), AttrEx(), FName(), GeometryName())); 
		if (NULL != pFVI) {
			pFVI -> SetLocatable (IsLocatable());
			pFVI -> SetVisible (IsVisible());
		}
		return pFVI;
	}
	CVisInfoBase *Copy (void)
	{ 
		return CopyCustom();
	}

	inline short isType (void) { return TPCustomized | TPFlaeche; }

	inline Color &SecColor (void) { return m_FillColor; }
	inline const char *FName (void) { return VisName(); }
	inline short Width (void) { return m_iWidth; }
	inline short Type (void) { return T::Style(); }
	inline bool isBkConture (void) { return (m_iAttrEx & ::BMBkConture) ? true : false; }
	inline bool isOpaque (void) { return (m_iAttrEx & ::BMOpaque) ? true : false; }
	inline void SetWidth (short iW) { m_iWidth = iW; }
	inline short OldStyle (void) { return short((Type() + (100 * Width())) | (isOpaque() ? ::BMOpaque : 0)); }
	inline short AttrEx (void) { return m_iAttrEx; }
	inline void SetAttrEx (short iAttrEx) { m_iAttrEx = iAttrEx; }
};

template<class T>
class CDefaultFVisInfoT : 
	public FVisInfoT<T> 
{
public:
	inline CDefaultFVisInfoT (void)	: 
		FVisInfoT<T> (DEF_STYLE, DEF_PRIORITY_FLAECHE, DEF_COLOR, DEF_COLOR, 0) 
	{
	}
			
	CVisInfoBase *Copy (void)	// clone operator
	{ 
		return new CDefaultFVisInfoT<T> (); 
	}
	inline short isType (void) { return TPDefaultInfo | TPFlaeche; }
};

///////////////////////////////////////////////////////////////////////////////
// VisualisierungsInfo für SchriftObjekte 
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

inline LPCSTR CorrectFontName (short iStyle, LPCSTR pcName)
{
	if (DEF_STYLE_TEXT == iStyle || 0 == iStyle)
		return (NULL != pcName) ? pcName : DEF_FONT_TEXT;
	return pcName;
}

template<class T>
class TVisInfoT : 
	public T 
{
private:
	Dimension m_Size;		// FontGröße
	short m_Type;			// FontArt
	short m_Rot;			// Drehwinkel
	short m_Orient;			// Buchstabendrehwinkel

public:
// Konstruktor
	TVisInfoT() : 
		T (DEF_STYLE_TEXT, DEF_PRIORITY_TEXT, DEF_COLOR, DEF_FONT_TEXT), 
		m_Size(DEF_SIZE_TEXT), m_Type(0), m_Rot(0), m_Orient(0)
	{
	}
	TVisInfoT (short Style, short Prio, Color TColor, Dimension TSize, short Typ, short Rot = 0, 
			   const char *pTName = NULL, const char *pcGeomName = NULL)
		: T (Style, CorrectPriority (Prio), TColor, CorrectFontName(Style, pTName), pcGeomName)
	{
		m_Size = TSize;
		m_Type = Typ;
		m_Rot = Rot;
		m_Orient = Rot;
	}

// C-Schnittstelle
	TVisInfoT (TVISINFO &TVI) : T (TVI.m_VI)
	{
		TX_ASSERT_POINTER(&TVI, TVISINFO);
		TX_ASSERT(TVI.m_VI.dwSize == sizeof(TVISINFO));

		m_Size = *(Dimension *)&TVI.m_Size;
		m_Type = TVI.m_Type;
		m_Rot = TVI.m_Rot;
		m_Orient = TVI.m_Orient;
	}
	void CopyTo (VISINFO &TVI)
	{
		TX_ASSERT(TIsValidAddress(&TVI, sizeof(TVISINFO), true));
		TX_ASSERT(TVI.dwSize == sizeof(TVISINFO));

		T::CopyTo (TVI);
		((TVISINFO &)TVI).m_Size = *(SIZE *)&m_Size;
		((TVISINFO &)TVI).m_Type = m_Type;
		((TVISINFO &)TVI).m_Rot = m_Rot;
		((TVISINFO &)TVI).m_Orient = m_Orient;
	}

// Memberfunktionen
	VisType isA (void) { return VT_Text; }
	CVisInfoBase * CopyCustom (void)	// Clone operator
	{
	TVisInfoT<T> *pTVI = NULL;
	
		TX_TRY(pTVI = new TVisInfoT<T> (Style(), Priority(), PrimColor(), Size(), 
					   Type(), Rotation(), TName(), GeometryName()));
		if (pTVI) {
			pTVI -> SetLocatable (IsLocatable());
			pTVI -> SetVisible (IsVisible());
			pTVI -> Orientation() = Orientation();
		}
		return pTVI;
	}
	CVisInfoBase * Copy(void)
	{
		return CopyCustom();
	}

	inline short isType (void) { return TPCustomized | TPText; }

	inline Dimension &Size(void) { return m_Size; }
	inline short &Type (void) { return m_Type; }
	inline short &Rotation (void) { return m_Rot; }

	inline bool isItalic (void) { return m_Type & ::TV_Italic; }
	inline bool isUnderlined (void) { return m_Type & ::TV_Underlined; }
	inline bool isStrikedthru (void) { return m_Type & ::TV_StrikedThru; }
	inline bool isFixedPitch (void) { return m_Type & ::TV_FixedPitch; }
	inline bool isBold (void) { return m_Type & ::TV_Bold; }
	inline bool isLight (void) { return m_Type & ::TV_Light; }
	inline bool isNormal (void) { return !isLight() && !isBold(); }
	inline bool BKMode (void) { return m_Type & ::TV_BKMode; }
	inline bool FrameMode (void) { return m_Type & ::TV_Frame; }
	inline bool RoundFrame (void) { return (m_Type & ::TV_RoundFrame) && FrameMode(); }

	inline bool LeftAlign (void) { return !(m_Type & ::TV_AlignStyle); }
	inline bool CentreAlign (void) { return m_Type & ::TV_CentreAlign; }
	inline bool RightAlign (void) { return m_Type & ::TV_RightAlign; }
	inline bool Justified (void) { return m_Type & ::TV_Justified; }
	inline short AlignStyle (void) { return m_Type & ::TV_AlignStyle; }
		
	inline const char *TName (void) { return VisName(); }

	inline short &Orientation (void) { return m_Orient; }
	inline short AttrEx (void) { return HIBYTE(m_Type); }	// bisher nur objektbezogen möglich
};

template<class T>
class CDefaultTVisInfoT : 
	public TVisInfoT<T> 
{
public:
	inline	CDefaultTVisInfoT (void) : 
		TVisInfoT<T> (DEF_STYLE, DEF_PRIORITY_TEXT, DEF_COLOR, DEF_SIZE_TEXT, DEF_TYP_TEXT) 
	{
	}
			
	CVisInfoBase *Copy (void)	// clone operator
	{
		return new CDefaultTVisInfoT<T>();
	}
	inline short isType (void) { return TPDefaultInfo | TPText; }
};

#if !defined(_USE_NEWVISINFO)
///////////////////////////////////////////////////////////////////////////////
// alte Namen für alte Datenstrukturen
typedef CDefaultVisInfoT<VisInfo> CDefaultVisInfo;
typedef PVisInfoT<VisInfo> PVisInfo;
typedef CDefaultPVisInfoT<VisInfo> CDefaultPVisInfo;
typedef LVisInfoT<VisInfo> LVisInfo;
typedef CDefaultLVisInfoT<VisInfo> CDefaultLVisInfo;
typedef FVisInfoT<VisInfo> FVisInfo;
typedef CDefaultFVisInfoT<VisInfo> CDefaultFVisInfo;
typedef TVisInfoT<VisInfo> TVisInfo;
typedef CDefaultTVisInfoT<VisInfo> CDefaultTVisInfo;

#else // !defined(_USE_NEWVISINFO)

///////////////////////////////////////////////////////////////////////////////
// alte Namen für neue Datenstrukturen
typedef CDefaultVisInfoT<VisInfo> CDefaultVisInfo;
typedef PVisInfoT<VisInfo> PVisInfo;
typedef CDefaultPVisInfoT<VisInfo> CDefaultPVisInfo;
typedef LVisInfoT<VisInfo> LVisInfo;
typedef CDefaultLVisInfoT<VisInfo> CDefaultLVisInfo;
typedef FVisInfoT<VisInfo> FVisInfo;
typedef CDefaultFVisInfoT<VisInfo> CDefaultFVisInfo;
typedef TVisInfoT<VisInfo> TVisInfo;
typedef CDefaultTVisInfoT<VisInfo> CDefaultTVisInfo;

///////////////////////////////////////////////////////////////////////////////
// neue Namen für alte Datenstrukturen
typedef CDefaultVisInfoT<OldVisInfo> COldDefaultVisInfo;
typedef PVisInfoT<OldVisInfo> POldVisInfo;
typedef CDefaultPVisInfoT<OldVisInfo> COldDefaultPVisInfo;
typedef LVisInfoT<OldVisInfo> LOldVisInfo;
typedef CDefaultLVisInfoT<OldVisInfo> COldDefaultLVisInfo;
typedef FVisInfoT<OldVisInfo> FOldVisInfo;
typedef CDefaultFVisInfoT<OldVisInfo> COldDefaultFVisInfo;
typedef TVisInfoT<OldVisInfo> TOldVisInfo;
typedef CDefaultTVisInfoT<OldVisInfo> COldDefaultTVisInfo;

OldVisInfo *GetOldVI (VisInfo *pVI);
#endif // _USE_NEWVISINFO

///////////////////////////////////////////////////////////////////////////////
//
inline 
VisInfo *VisInfoFromC (VISINFO &rVI, VisType iVTyp)
{
VisInfo *pVI = NULL;

	switch (iVTyp) {
	case VT_Punkt:
		pVI = new PVisInfo ((PVISINFO &)rVI);
		break;
		
	case VT_Linie:
		pVI = new LVisInfo ((LVISINFO &)rVI);
		break;
		
	case VT_Flaeche:
		pVI = new FVisInfo ((FVISINFO &)rVI);
		break;
		
	case VT_Text:
		pVI = new TVisInfo ((TVISINFO &)rVI);
		break;
		
	case VT_Default:
		pVI = new VisInfo (rVI);
		break;
	}		
	return pVI;	
}

inline
VISINFO * VISINFOFromCPP (VisInfo *pVITemp)
{
VISINFO *pVI = NULL;

	switch (pVITemp -> isA()) {
	case VT_Punkt:
		pVI = (VISINFO *)new PVISINFO;
		break;
		
	case VT_Linie:
		pVI = (VISINFO *)new LVISINFO;
		break;
		
	case VT_Flaeche:
		pVI = (VISINFO *)new FVISINFO;
		break;
		
	case VT_Text:
		pVI = (VISINFO *)new TVISINFO;
		break;
		
	case VT_Default:
		pVI = new VISINFO;
		break;

	default:
		TX_ASSERT(false);
		break;
	}
	if (pVI) pVITemp -> CopyTo (*pVI);
	return pVI;	
}

///////////////////////////////////////////////////////////////////////////////
//
#if defined(_USE_NEWVISINFO)
inline
VISINFO * VISINFOFromCPP (OldVisInfo *pVITemp)
{
VISINFO *pVI = NULL;

	switch (pVITemp -> isA()) {
	case VT_Punkt:
		pVI = (VISINFO *)new PVISINFO;
		break;
		
	case VT_Linie:
		pVI = (VISINFO *)new LVISINFO;
		break;
		
	case VT_Flaeche:
		pVI = (VISINFO *)new FVISINFO;
		break;
		
	case VT_Text:
		pVI = (VISINFO *)new TVISINFO;
		break;
		
	case VT_Default:
		pVI = new VISINFO;
		break;

	default:
		TX_ASSERT(false);
		break;
	}
	if (pVI) pVITemp -> CopyTo (*pVI);
	return pVI;	
}

inline
OldVisInfo *OldVisInfoFromC (VISINFO &rVI, VisType iVTyp)
{
OldVisInfo *pVI = NULL;

	switch (iVTyp) {
	case VT_Punkt:
		pVI = new POldVisInfo ((PVISINFO &)rVI);
		break;
		
	case VT_Linie:
		pVI = new LOldVisInfo ((LVISINFO &)rVI);
		break;
		
	case VT_Flaeche:
		pVI = new FOldVisInfo ((FVISINFO &)rVI);
		break;
		
	case VT_Text:
		pVI = new TOldVisInfo ((TVISINFO &)rVI);
		break;
		
	case VT_Default:
		pVI = new OldVisInfo (rVI);
		break;
	}		
	return pVI;	
}

inline
OldVisInfo *GetOldVI (VisInfo *pVI)
{
VISINFO *pVIC = VISINFOFromCPP (pVI);

	if (NULL == pVIC) return NULL;

OldVisInfo *pOldVI = OldVisInfoFromC (*pVIC, pVI -> isA());

	delete pVIC;
	return pOldVI;
}
#endif // !defined(_USE_NEWVISINFO)

#endif // !defined(_VISINFO_HXX__517B38C8_E21D_11D2_9BD4_001B20524153__INCLUDED_)
