// Memberfunktionen fuer die Klassen Sicht und VisType
// File: VISINFO.CXX

#include "stdafx.h"               

#include <string.h>
#include <attribs.hxx>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// VisualisierungInfo für Identifikatoren und Objekte -------------------------
// Konstruktoren
VisInfo :: VisInfo (short Style, short Prio, Color C, char *pName) 
{
// Memberwerte setzen
	m_Style = Style;         // Darstellungsart
	m_Priority = Prio;       // Darstellungspriorität
	m_C = C;                 // Farbe (Punkt-, Linien-, Füllfarbe)
	SetVisName (pName);
}


void VisInfo :: SetVisName (char *lpName) 
{
	if (lpName) {
		TX_ASSERT(TIsValidString(lpName));

		strncpy (m_VisName, lpName, VISNAMESIZE);	
		m_VisName[VISNAMESIZE] = '\0';
	} else
		m_VisName[0] = '\0';
}

// Clone operator -------------------------------------------------------------
CVisInfoBase *VisInfo :: Copy (void) 
{ 
	return new VisInfo (Style(), Priority(), PrimColor(), VisName()); 
}
CVisInfoBase *PVisInfo :: Copy (void) 
{ 
	return new PVisInfo (Style(), Priority(), PrimColor(), Size(), PName(), Rotation(), SecColor()); 
}
CVisInfoBase *LVisInfo :: Copy (void) 
{ 
	return new LVisInfo (Style(), Priority(), PrimColor(), Width(), LName()); 
}
CVisInfoBase *FVisInfo :: Copy (void) 
{ 
#if defined(OLDVISINFO)
	return new FVisInfo (Style(), Priority(), PrimColor(), SecColor(), FName()); 
#else
	return new FVisInfo (OldStyle(), Priority(), PrimColor(), SecColor(), AttrEx(), FName()); 
#endif // OLDVISINFO
}
CVisInfoBase *TVisInfo :: Copy (void) 
{
TVisInfo *pTVI = new TVisInfo (Style(), Priority(), PrimColor(), Size(), 
			       Type(), Rotation(), TName());

	if (pTVI) pTVI -> Orientation() = Orientation();

return pTVI;
}

CVisInfoBase *VisInfo :: CopyCustom (void) 
{ 
	return new VisInfo (Style(), Priority(), PrimColor(), VisName()); 
}
CVisInfoBase *PVisInfo :: CopyCustom (void) 
{ 
	return new PVisInfo (Style(), Priority(), PrimColor(), Size(), PName(), Rotation(), SecColor()); 
}
CVisInfoBase *LVisInfo :: CopyCustom (void) 
{ 
	return new LVisInfo (Style(), Priority(), PrimColor(), Width(), LName()); 
}
CVisInfoBase *FVisInfo :: CopyCustom (void) 
{ 
#if defined(OLDVISINFO)
	return new FVisInfo (Style(), Priority(), PrimColor(), SecColor(), FName()); 
#else
	return new FVisInfo (OldStyle(), Priority(), PrimColor(), SecColor(), AttrEx(), FName()); 
#endif // OLDVISINFO
}
CVisInfoBase *TVisInfo :: CopyCustom (void) 
{
TVisInfo *pTVI = new TVisInfo (Style(), Priority(), PrimColor(), Size(), 
			       Type(), Rotation(), TName());

	if (pTVI) pTVI -> Orientation() = Orientation();

return pTVI;
}


CVisInfoBase *CDefaultVisInfo :: Copy (void) 
{ 
	return new CDefaultVisInfo (); 
}
CVisInfoBase *CDefaultPVisInfo :: Copy (void) 
{ 
	return new CDefaultPVisInfo (); 
}
CVisInfoBase *CDefaultLVisInfo :: Copy (void) 
{ 
	return new CDefaultLVisInfo (); 
}
CVisInfoBase *CDefaultFVisInfo :: Copy (void) 
{ 
	return new CDefaultFVisInfo (); 
}

CVisInfoBase *CDefaultTVisInfo :: Copy (void) 
{
	return new CDefaultTVisInfo ();
}

inline short CorrectPtStyle (short iStyle)
{
	return ((iStyle >= 0) ? iStyle : 0);         // default: PunktTyp 0
}

inline short CorrectPriority (short iPrio)
{
#if defined(WIN32)
// #HK960705: keine Korrektur der Priorität mehr notwendig
	return iPrio; 
#else // WIN32
	return ((iPrio >= 0 && iPrio < 1000) ? iPrio : DEF_PRIORITY);
#endif // WIN32
}


// Konstruktoren --------------------------------------------------------------
PVisInfo :: PVisInfo (short iStyle, short Prio, Color PColor, Dimension Size, 
		      char *pPName, short iRot, Color SecC) 
	  : VisInfo (iStyle, CorrectPriority (Prio), PColor, pPName)
{
// eigenen Memberwert setzen
	m_Size = Size;		// PunktSymbolGröße
	m_iRot = iRot;		// Drehwinkel
	m_SecC = SecC;		// zweite Farbe
}

inline short CorrectLineStyle (short iStyle)
{
	return ((iStyle >= 0) ? iStyle : 0);         // default: PunktTyp 0
}

LVisInfo :: LVisInfo (short Style, short Prio, Color LColor, short Size, char *pLName) 
	  : VisInfo (CorrectLineStyle (Style),        // default: LinienTyp 0
		     CorrectPriority (Prio), LColor, pLName)
{
// eigenen Memberwert setzen
	m_Width = Size;           // StrichStärke
}

#if defined(OLDVISINFO)
FVisInfo :: FVisInfo (short Style, short iPrio, Color FColor, Color BColor, char *pFName) 
	  : VisInfo (Style, CorrectPriority(iPrio), FColor, pFName)
{
// eigenen Memberwert setzen
	m_FillColor = BColor;
}
#else // OLDVISINFO
FVisInfo :: FVisInfo (short Style, short iPrio, Color FColor, Color BColor, 
		      short iAttrEx, char *pFName) 
	  : VisInfo ((Style & ~BMOpaque) % 100, CorrectPriority (iPrio), FColor, pFName)
{
// eigenen Memberwert setzen
	m_FillColor = BColor;
	m_iWidth = (Style & ~BMOpaque) / 100;
	m_iAttrEx = (Style & BMOpaque) | (iAttrEx & ~BMOpaque);
}
#endif //OLDVISINFO

TVisInfo :: TVisInfo (short Style, short iPrio, Color TColor, Dimension TSize, 
		      short Typ, short Rot, char *pTName)
	  : VisInfo (Style, CorrectPriority(iPrio), TColor, pTName)
{
// eigene Memberwerte setzen
	m_Size = TSize;
	m_Type = Typ;
	m_Rot = Rot;
	m_Orient = Rot;
}

// Memberfunktionen -----------------------------------------------------------
VisType VisInfo :: isA (void) { return VT_Default; }
VisType PVisInfo :: isA (void) { return VT_Punkt; }
VisType LVisInfo :: isA (void) { return VT_Linie; }
VisType FVisInfo :: isA (void) { return VT_Flaeche; }
VisType TVisInfo :: isA (void) { return VT_Text; }

// C - SchnittstellenFunktionen -----------------------------------------------
#if defined(MSWIND)

VisInfo :: VisInfo (VISINFO &VI)
{
	TX_ASSERT_POINTER(&VI, VISINFO);

// Memberwerte setzen
	m_Style = VI.m_Style;		// Darstellungsart
	m_Priority = VI.m_Priority;	// Darstellungspriorität
	m_C = *(Color *)&VI.m_C;	// Farbe (Punkt-, Linien-, Füllfarbe)
	SetVisName (VI.m_VisName);
}

void VisInfo :: CopyTo (VISINFO &VI)
{
	TX_ASSERT(TIsValidAddress(&VI, sizeof(VISINFO), true));

	VI.m_Style = m_Style;
	VI.m_Priority = m_Priority;
	VI.m_C = *(COLORREF *)&m_C;
	memset (VI.m_VisName, '\0', VISNAMESIZE);
	strncpy (VI.m_VisName, m_VisName, VISNAMESIZE);	
}

PVisInfo :: PVisInfo (PVISINFO &PVI)
	  : VisInfo (PVI.m_VI)
{
	TX_ASSERT_POINTER(&PVI, PVISINFO);

	m_Size = *(Dimension *)&PVI.m_Size;
	m_iRot = PVI.m_iRot;
	m_SecC = (Color &)PVI.m_SecC;
}

void PVisInfo :: CopyTo (VISINFO &PVI)
{
	TX_ASSERT(TIsValidAddress(&PVI, sizeof(PVISINFO), true));

	VisInfo :: CopyTo (PVI);
	((PVISINFO &)PVI).m_Size = *(SIZE *)&m_Size;
	((PVISINFO &)PVI).m_iRot = Rotation();
	((PVISINFO &)PVI).m_SecC = (COLORREF &)SecColor();
}

LVisInfo :: LVisInfo (LVISINFO &LVI)
	  : VisInfo (LVI.m_VI)
{
	TX_ASSERT_POINTER(&LVI, LVISINFO);

	m_Width = LVI.m_Width;           // StrichStärke
}

void LVisInfo :: CopyTo (VISINFO &LVI)
{
	TX_ASSERT(TIsValidAddress(&LVI, sizeof(LVISINFO), true));

	VisInfo :: CopyTo (LVI);
	((LVISINFO &)LVI).m_Width = m_Width;
}

#if defined(OLDVISINFO)
FVisInfo :: FVisInfo (FVISINFO &FVI)
	  : VisInfo (FVI.m_VI)
{
	m_FillColor = *(Color *)&FVI.m_FC;
}

void FVisInfo :: CopyTo (VISINFO &FVI)
{
	VisInfo :: CopyTo (FVI);
	((FVISINFO &)FVI).m_FC = *(COLORREF *)&m_FillColor;
}
#else // OLDVISINFO
FVisInfo :: FVisInfo (FVISINFO &FVI)
	  : VisInfo (FVI.m_VI)
{
	TX_ASSERT_POINTER(&FVI, FVISINFO);

	m_FillColor = *(Color *)&FVI.m_FC;
	m_iWidth = FVI.m_iWidth;
	m_iAttrEx = FVI.m_iAttrEx;
}

void FVisInfo :: CopyTo (VISINFO &FVI)
{
	TX_ASSERT(TIsValidAddress(&FVI, sizeof(FVISINFO), true));

	VisInfo :: CopyTo (FVI);
	((FVISINFO &)FVI).m_FC = *(COLORREF *)&m_FillColor;
	((FVISINFO &)FVI).m_iWidth = m_iWidth;
	((FVISINFO &)FVI).m_iAttrEx = m_iAttrEx;
}
#endif // OLDVISINFO

TVisInfo :: TVisInfo (TVISINFO &TVI)
	  : VisInfo (TVI.m_VI)
{
	TX_ASSERT_POINTER(&TVI, TVISINFO);

	m_Size = *(Dimension *)&TVI.m_Size;
	m_Type = TVI.m_Type;
	m_Rot = TVI.m_Rot;
	m_Orient = TVI.m_Orient;
}

void TVisInfo :: CopyTo (VISINFO &TVI)
{
	TX_ASSERT(TIsValidAddress(&TVI, sizeof(TVISINFO), true));

	VisInfo :: CopyTo (TVI);
	((TVISINFO &)TVI).m_Size = *(SIZE *)&m_Size;
	((TVISINFO &)TVI).m_Type = m_Type;
	((TVISINFO &)TVI).m_Rot = m_Rot;
	((TVISINFO &)TVI).m_Orient = m_Orient;
}


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
	
	default:
		TX_ASSERT(false);
		break;
	}

return pVI;	
}


VISINFO * VISINFOFromCPP (VisInfo *pVITemp)
{
VISINFO *pVI = NULL;

	switch (pVITemp -> isA()) {
	case VT_Punkt:
		pVI = (VISINFO *)new PVISINFO;
		memset (pVI, '\0', sizeof(PVISINFO));
		break;
		
	case VT_Linie:
		pVI = (VISINFO *)new LVISINFO;
		memset (pVI, '\0', sizeof(LVISINFO));
		break;
		
	case VT_Flaeche:
		pVI = (VISINFO *)new FVISINFO;
		memset (pVI, '\0', sizeof(FVISINFO));
		break;
		
	case VT_Text:
		pVI = (VISINFO *)new TVISINFO;
		memset (pVI, '\0', sizeof(TVISINFO));
		break;
		
	case VT_Default:
		pVI = new VISINFO;
		memset (pVI, '\0', sizeof(VISINFO));
		break;

	default:
		TX_ASSERT(false);
		break;
	}
	if (pVI) pVITemp -> CopyTo (*pVI);

return pVI;	
}


#endif // MSWIND

