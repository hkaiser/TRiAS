// Memberfunktionen fuer die Klassen Sicht und VisType
// File: VISINFO.CXX

#include "trias02p.hxx"
#include "Strings.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// VisualisierungInfo für Identifikatoren und Objekte -------------------------
// Konstruktoren
VisInfo :: VisInfo (short Style, short Prio, Color C, const char *pName, const char *pcGeomName) 
{
// Memberwerte setzen
	m_Style = Style;         // Darstellungsart
	m_Priority = Prio;       // Darstellungspriorität
	m_C = C;                 // Farbe (Punkt-, Linien-, Füllfarbe)
	SetVisName (pName);
	SetGeometryName(pcGeomName);
}

void VisInfo :: SetVisName (const char *lpName) 
{
	if (lpName) {
		TX_ASSERT(TIsValidString(lpName));

		strncpy (m_VisName, lpName, VISNAMESIZE);	
		m_VisName[VISNAMESIZE] = '\0';
	} else
		m_VisName[0] = '\0';
}

void VisInfo :: SetGeometryName (const char *lpName) 
{
	if (lpName) {
		TX_ASSERT(TIsValidString(lpName));

		strncpy (m_GeometryName, lpName, VISNAMESIZE);	
		m_GeometryName[VISNAMESIZE] = '\0';
	} else
		m_GeometryName[0] = '\0';
}

// Clone operator -------------------------------------------------------------
CVisInfoBase *VisInfo :: Copy (void) 
{ 
	return new VisInfo (Style(), Priority(), PrimColor(), VisName(), GeometryName()); 
}
CVisInfoBase *PVisInfo :: Copy (void) 
{ 
	return new PVisInfo (Style(), Priority(), PrimColor(), Size(), PName(), Rotation(), SecColor(), GeometryName()); 
}
CVisInfoBase *LVisInfo :: Copy (void) 
{ 
	return new LVisInfo (Style(), Priority(), PrimColor(), Width(), LName(), GeometryName()); 
}
CVisInfoBase *FVisInfo :: Copy (void) 
{ 
	return new FVisInfo (OldStyle(), Priority(), PrimColor(), SecColor(), AttrEx(), FName(), GeometryName()); 
}
CVisInfoBase *TVisInfo :: Copy (void) 
{
TVisInfo *pTVI = new TVisInfo (Style(), Priority(), PrimColor(), Size(), 
			       Type(), Rotation(), TName(), GeometryName());

	if (pTVI) pTVI -> Orientation() = Orientation();

return pTVI;
}

CVisInfoBase *VisInfo :: CopyCustom (void) 
{ 
	return new VisInfo (Style(), Priority(), PrimColor(), VisName(), GeometryName()); 
}
CVisInfoBase *PVisInfo :: CopyCustom (void) 
{ 
	return new PVisInfo (Style(), Priority(), PrimColor(), Size(), PName(), Rotation(), SecColor(), GeometryName()); 
}
CVisInfoBase *LVisInfo :: CopyCustom (void) 
{ 
	return new LVisInfo (Style(), Priority(), PrimColor(), Width(), LName(), GeometryName()); 
}
CVisInfoBase *FVisInfo :: CopyCustom (void) 
{ 
	return new FVisInfo (OldStyle(), Priority(), PrimColor(), SecColor(), AttrEx(), FName(), GeometryName()); 
}
CVisInfoBase *TVisInfo :: CopyCustom (void) 
{
TVisInfo *pTVI = new TVisInfo (Style(), Priority(), PrimColor(), Size(), 
			       Type(), Rotation(), TName(), GeometryName());

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
		      const char *pPName, short iRot, Color SecC, const char *pcGeomName) 
	  : VisInfo (iStyle, CorrectPriority (Prio), PColor, pPName, pcGeomName)
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

LVisInfo :: LVisInfo (short Style, short Prio, Color LColor, short Size, const char *pLName, const char *pcGeomName) 
	  : VisInfo (CorrectLineStyle (Style),        // default: LinienTyp 0
		     CorrectPriority (Prio), LColor, pLName, pcGeomName)
{
// eigenen Memberwert setzen
	m_Width = Size;           // StrichStärke
}

FVisInfo :: FVisInfo (short Style, short iPrio, Color FColor, Color BColor, 
		      short iAttrEx, const char *pFName, const char *pcGeomName) 
	  : VisInfo ((Style & ~BMOpaque) % 100, CorrectPriority (iPrio), FColor, pFName, pcGeomName)
{
// eigenen Memberwert setzen
	m_FillColor = BColor;
	m_iWidth = (Style & ~BMOpaque) / 100;
	m_iAttrEx = (Style & BMOpaque) | (iAttrEx & ~BMOpaque);
}

TVisInfo :: TVisInfo (short Style, short iPrio, Color TColor, Dimension TSize, 
		      short Typ, short Rot, const char *pTName, const char *pcGeomName)
	  : VisInfo (Style, CorrectPriority(iPrio), TColor, pTName, pcGeomName)
{
// eigene Memberwerte setzen
	m_Size = TSize;
	m_Type = Typ;
	m_Rot = Rot;
	m_Orient = Rot;

// evtl. FontTyp auf Arial setzen
	if (0 == strlen(VisName())) 
		SetVisName (const_cast<char *>(g_cbArial));
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

void VisInfo :: CopyTo (VISINFO &VI)
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

PVisInfo :: PVisInfo (PVISINFO &PVI)
	  : VisInfo (PVI.m_VI)
{
	TX_ASSERT_POINTER(&PVI, PVISINFO);
	TX_ASSERT(PVI.m_VI.dwSize == sizeof(PVISINFO));

	m_Size = *(Dimension *)&PVI.m_Size;
	m_iRot = PVI.m_iRot;
	m_SecC = (Color &)PVI.m_SecC;
}

void PVisInfo :: CopyTo (VISINFO &PVI)
{
	TX_ASSERT(TIsValidAddress(&PVI, sizeof(PVISINFO), true));
	TX_ASSERT(PVI.dwSize == sizeof(PVISINFO));

	VisInfo :: CopyTo (PVI);
	((PVISINFO &)PVI).m_Size = *(SIZE *)&m_Size;
	((PVISINFO &)PVI).m_iRot = Rotation();
	((PVISINFO &)PVI).m_SecC = (COLORREF &)SecColor();
}

LVisInfo :: LVisInfo (LVISINFO &LVI)
	  : VisInfo (LVI.m_VI)
{
	TX_ASSERT_POINTER(&LVI, LVISINFO);
	TX_ASSERT(LVI.m_VI.dwSize == sizeof(LVISINFO));

	m_Width = LVI.m_Width;           // StrichStärke
}

void LVisInfo :: CopyTo (VISINFO &LVI)
{
	TX_ASSERT(TIsValidAddress(&LVI, sizeof(LVISINFO), true));
	TX_ASSERT(LVI.dwSize == sizeof(LVISINFO));

	VisInfo :: CopyTo (LVI);
	((LVISINFO &)LVI).m_Width = m_Width;
}

FVisInfo :: FVisInfo (FVISINFO &FVI)
	  : VisInfo (FVI.m_VI)
{
	TX_ASSERT_POINTER(&FVI, FVISINFO);
	TX_ASSERT(FVI.m_VI.dwSize == sizeof(FVISINFO));

	m_FillColor = *(Color *)&FVI.m_FC;
	m_iWidth = FVI.m_iWidth;
	m_iAttrEx = FVI.m_iAttrEx;
}

void FVisInfo :: CopyTo (VISINFO &FVI)
{
	TX_ASSERT(TIsValidAddress(&FVI, sizeof(FVISINFO), true));
	TX_ASSERT(FVI.dwSize == sizeof(FVISINFO));

	VisInfo :: CopyTo (FVI);
	((FVISINFO &)FVI).m_FC = *(COLORREF *)&m_FillColor;
	((FVISINFO &)FVI).m_iWidth = m_iWidth;
	((FVISINFO &)FVI).m_iAttrEx = m_iAttrEx;
}

TVisInfo :: TVisInfo (TVISINFO &TVI)
	  : VisInfo (TVI.m_VI)
{
	TX_ASSERT_POINTER(&TVI, TVISINFO);
	TX_ASSERT(TVI.m_VI.dwSize == sizeof(TVISINFO));

	m_Size = *(Dimension *)&TVI.m_Size;
	m_Type = TVI.m_Type;
	m_Rot = TVI.m_Rot;
	m_Orient = TVI.m_Orient;
}

void TVisInfo :: CopyTo (VISINFO &TVI)
{
	TX_ASSERT(TIsValidAddress(&TVI, sizeof(TVISINFO), true));
	TX_ASSERT(TVI.dwSize == sizeof(TVISINFO));

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
		if (pVI) {
			memset (pVI, '\0', sizeof(PVISINFO));
			pVI -> dwSize = sizeof(PVISINFO);
		}
		break;
		
	case VT_Linie:
		pVI = (VISINFO *)new LVISINFO;
		if (pVI) {
			memset (pVI, '\0', sizeof(LVISINFO));
			pVI -> dwSize = sizeof(LVISINFO);
		}
		break;
		
	case VT_Flaeche:
		pVI = (VISINFO *)new FVISINFO;
		if (pVI) {
			memset (pVI, '\0', sizeof(FVISINFO));
			pVI -> dwSize = sizeof(FVISINFO);
		}
		break;
		
	case VT_Text:
		pVI = (VISINFO *)new TVISINFO;
		if (pVI) {
			memset (pVI, '\0', sizeof(TVISINFO));
			pVI -> dwSize = sizeof(TVISINFO);
		}
		break;
		
	case VT_Default:
		pVI = new VISINFO;
		if (pVI) {
			memset (pVI, '\0', sizeof(VISINFO));
			pVI -> dwSize = sizeof(VISINFO);
		}
		break;

	default:
		TX_ASSERT(false);
		break;
	}
	if (pVI) pVITemp -> CopyTo (*pVI);
	return pVI;	
}

///////////////////////////////////////////////////////////////////////////////
// Helper für VisInfo
_TRIAS02_ENTRY 
VisInfo *MakeNewVI (VisType iVTyp) 
{
VisInfo *pNewVI = NULL;

	switch (iVTyp) {
	case VT_Punkt:
		pNewVI = new CDefaultPVisInfo();
		break;

	case VT_Linie:
		pNewVI = new CDefaultLVisInfo();
		break;

	case VT_Flaeche:
		pNewVI = new CDefaultFVisInfo();
		break;

	case VT_Text:
		pNewVI = new CDefaultTVisInfo();
		break;

	case VT_Default:
		pNewVI = new CDefaultVisInfo();
		break;
	}

return pNewVI;
}

// Funktion, die DefaultVisInfo typgerecht generiert --------------------------
_TRIAS02_ENTRY 
short MakeCompleteNewVisInfo (VisInfo **ppVI, short iBits, BOOL fSpecial)
{
// wenn alle gebraucht werden, aber keiner da ist, dann EINEN DefaultSatz 
// generieren
short fRet = 0;

	if (iBits == TPAll && fSpecial &&
	    ppVI[0] == NULL && ppVI[1] == NULL &&
	    ppVI[2] == NULL && ppVI[3] == NULL)
	{
		ppVI[0] = MakeNewVI (VT_Default);
		return TPAll;		// ACHTUNG: SonderFall
	} 
	if (ppVI[0] == NULL && iBits & TPPunkt) {
		ppVI[0] = MakeNewVI (VT_Punkt);
		fRet |= TPPunkt;
	}
	if (ppVI[1] == NULL && iBits & TPLinie) {
		ppVI[1] = MakeNewVI (VT_Linie);
		fRet |= TPLinie;
	}
	if (ppVI[2] == NULL && iBits & TPFlaeche) {
		ppVI[2] = MakeNewVI (VT_Flaeche);
		fRet |= TPFlaeche;
	}
	if (ppVI[3] == NULL && iBits & TPText) {
		ppVI[3] = MakeNewVI (VT_Text);
		fRet |= TPText;
	}
	return fRet;	// normaler Verlauf
}

#endif // MSWIND

