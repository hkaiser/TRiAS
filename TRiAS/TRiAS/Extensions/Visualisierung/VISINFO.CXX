// Memberfunktionen fuer die Klassen Sicht und VisType
// File: VISINFO.CXX

#include "visobjp.hxx"

#include <protos.h>

#if defined(_DEBUG)
#define THIS_FILE __FILE__
#endif // _DEBUG

// VisualisierungInfo für Identifikatoren und Objekte -------------------------
// Konstruktoren
VisInfo::VisInfo (short Style, short Prio, Color C, const char *pName, const char *pcGeomName) 
{
// Memberwerte setzen
	m_Style = Style;         // Darstellungsart
	m_Priority = Prio;       // Darstellungspriorität
	m_C = C;                 // Farbe (Punkt-, Linien-, Füllfarbe)
	m_fLocatable = true;
	m_fVisible = true;
	SetVisName (pName);
	SetGeometryName (pcGeomName);
}

void VisInfo::SetVisName (const char *lpName) 
{
	if (lpName) {
		strncpy (m_VisName, lpName, VISNAMESIZE);	
		m_VisName[VISNAMESIZE] = '\0';
	} else
		m_VisName[0] = '\0';
}

OldVisInfo::OldVisInfo (short Style, short Prio, Color C, const char *pName, const char *pcGeomName) 
{
// Memberwerte setzen
	m_Style = Style;         // Darstellungsart
	m_Priority = Prio;       // Darstellungspriorität
	m_C = C;                 // Farbe (Punkt-, Linien-, Füllfarbe)
	SetVisName (pName);
}

void OldVisInfo::SetVisName (const char *lpName) 
{
	if (lpName) {
		strncpy (m_VisName, lpName, VISNAMESIZE);	
		m_VisName[VISNAMESIZE] = '\0';
	} else
		m_VisName[0] = '\0';
}

void VisInfo::SetGeometryName (const char *lpName) 
{
	if (lpName) {
		TX_ASSERT(TIsValidString(lpName));

		strncpy (m_GeometryName, lpName, VISNAMESIZE);	
		m_GeometryName[VISNAMESIZE] = '\0';
	} else
		m_GeometryName[0] = '\0';
}

// Clone operator -------------------------------------------------------------
CVisInfoBase *VisInfo::Copy (void) 
{ 
VisInfo *pVI = NULL;

	TX_TRY(pVI = new VisInfo (Style(), Priority(), PrimColor(), VisName(), GeometryName())); 
	if (NULL != pVI) {
		pVI -> SetLocatable (IsLocatable());
		pVI -> SetVisible (IsVisible());
	}
	return pVI;
}
CVisInfoBase *OldVisInfo::Copy (void) 
{ 
	return new OldVisInfo (Style(), Priority(), PrimColor(), VisName()); 
}

template<class T>
CVisInfoBase *PVisInfoT<T>::Copy (void) 
{ 
	return new PVisInfoT<T> (Style(), Priority(), PrimColor(), Size(), PName(), Rotation(), SecColor(), GeometryName()); 
}
template<class T>
CVisInfoBase *LVisInfoT<T>::Copy (void) 
{ 
	return new LVisInfoT<T> (Style(), Priority(), PrimColor(), Width(), LName(), GeometryName()); 
}
template<class T>
CVisInfoBase *FVisInfoT<T>::Copy (void) 
{ 
	return new FVisInfoT<T> (OldStyle(), Priority(), PrimColor(), SecColor(), AttrEx(), FName(), GeometryName()); 
}
template<class T>
CVisInfoBase *TVisInfoT<T>::Copy (void) 
{
TVisInfoT<T> *pTVI = new TVisInfoT<T> (Style(), Priority(), PrimColor(), Size(), 
			       Type(), Rotation(), TName(), GeometryName());

	if (pTVI) pTVI -> Orientation() = Orientation();

return pTVI;
}

CVisInfoBase *VisInfo::CopyCustom (void) 
{ 
	return new VisInfo (Style(), Priority(), PrimColor(), VisName(), GeometryName()); 
}
CVisInfoBase *OldVisInfo::CopyCustom (void) 
{ 
	return new OldVisInfo (Style(), Priority(), PrimColor(), VisName()); 
}

template<class T>
CVisInfoBase *PVisInfoT<T>::CopyCustom (void) 
{ 
	return new PVisInfoT<T> (Style(), Priority(), PrimColor(), Size(), PName(), Rotation(), SecColor(), GeometryName()); 
}
template<class T>
CVisInfoBase *LVisInfoT<T>::CopyCustom (void) 
{ 
	return new LVisInfoT<T> (Style(), Priority(), PrimColor(), Width(), LName(), GeometryName()); 
}
template<class T>
CVisInfoBase *FVisInfoT<T>::CopyCustom (void) 
{ 
	return new FVisInfoT<T> (OldStyle(), Priority(), PrimColor(), SecColor(), AttrEx(), FName(), GeometryName()); 
}
template<class T>
CVisInfoBase *TVisInfoT<T>::CopyCustom (void) 
{
TVisInfoT<T> *pTVI = new TVisInfoT<T> (Style(), Priority(), PrimColor(), Size(), 
			       Type(), Rotation(), TName(), GeometryName());

	if (pTVI) pTVI -> Orientation() = Orientation();

return pTVI;
}


template<class T>
CVisInfoBase *CDefaultVisInfoT<T>::Copy (void) 
{ 
	return new CDefaultVisInfoT<T> (); 
}
template<class T>
CVisInfoBase *CDefaultPVisInfoT<T>::Copy (void) 
{ 
	return new CDefaultPVisInfoT<T> (); 
}
template<class T>
CVisInfoBase *CDefaultLVisInfoT<T>::Copy (void) 
{ 
	return new CDefaultLVisInfoT<T> (); 
}
template<class T>
CVisInfoBase *CDefaultFVisInfoT<T>::Copy (void) 
{ 
	return new CDefaultFVisInfoT<T> (); 
}
template<class T>
CVisInfoBase *CDefaultTVisInfoT<T>::Copy (void) 
{
	return new CDefaultTVisInfoT<T> ();
}


// Konstruktoren --------------------------------------------------------------
/*
inline short CorrectPtStyle (short iStyle)
{
	return ((iStyle >= 0) ? iStyle : 0);         // default: PunktTyp 0
}
*/
inline short CorrectPriority (short iPrio)
{	// #HK960705
	return iPrio; //((iPrio >= 0 && iPrio < 1000) ? iPrio : DEF_PRIORITY);
}

template<class T>
PVisInfoT<T>::PVisInfoT (short Style, short Prio, Color PColor, Dimension Size, 
		      const char *pPName, short iRot, Color SecC, const char *pcGeomName) 
	  : T (Style, CorrectPriority (Prio), PColor, pPName, pcGeomName)
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

template<class T>
LVisInfoT<T>::LVisInfoT (short Style, short Prio, Color LColor, short Size, const char *pLName, const char *pcGeomName) 
	  : T (CorrectLineStyle (Style),        // default: LinienTyp 0
		     CorrectPriority (Prio),
		     LColor, pLName, pcGeomName)
{
// eigenen Memberwert setzen
	m_Width = Size;           // StrichStärke
}

template<class T>
FVisInfoT<T>::FVisInfoT (short Style, short Prio, Color FColor, Color BColor, 
		      short iAttrEx, const char *pFName, const char *pcGeomName) 
	  : T ((Style & ~BMOpaque) % 100, 
	  	CorrectPriority (Prio),					// default: 500
		FColor, pFName, pcGeomName)
{
// eigenen Memberwert setzen
	m_FillColor = BColor;
	m_iWidth = (Style & ~BMOpaque) / 100;
	m_iAttrEx = (Style & BMOpaque) | (iAttrEx & ~BMOpaque);
}

template<class T>
TVisInfoT<T>::TVisInfoT (short Style, short Prio, Color TColor, Dimension TSize, 
		      short Typ, short Rot, const char *pTName, const char *pcGeomName)
	  : T (Style, CorrectPriority (Prio), TColor, pTName, pcGeomName)
{
// eigene Memberwerte setzen
	m_Size = TSize;
	m_Type = Typ;
	m_Rot = Rot;
	m_Orient = Rot;
}

// Memberfunktionen -----------------------------------------------------------
VisType VisInfo::isA (void) { return VT_Default; }
VisType OldVisInfo::isA (void) { return VT_Default; }

template<class T>
VisType PVisInfoT<T>::isA (void) { return VT_Punkt; }
template<class T>
VisType LVisInfoT<T>::isA (void) { return VT_Linie; }
template<class T>
VisType FVisInfoT<T>::isA (void) { return VT_Flaeche; }
template<class T>
VisType TVisInfoT<T>::isA (void) { return VT_Text; }

// C - SchnittstellenFunktionen -----------------------------------------------
#if defined(MSWIND)

VisInfo::VisInfo (VISINFO &VI)
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

void VisInfo::CopyTo (VISINFO &VI)
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

OldVisInfo::OldVisInfo (VISINFO &VI)
{
	TX_ASSERT_POINTER(&VI, VISINFO);
	TX_ASSERT(VI.dwSize >= sizeof(VISINFO));

// Memberwerte setzen
	m_Style = VI.m_Style;		// Darstellungsart
	m_Priority = VI.m_Priority;	// Darstellungspriorität
	m_C = *(Color *)&VI.m_C;	// Farbe (Punkt-, Linien-, Füllfarbe)

	SetVisName (VI.m_VisName);
}

void OldVisInfo::CopyTo (VISINFO &VI)
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

template<class T>
PVisInfoT<T>::PVisInfoT (PVISINFO &PVI)
	  : T (PVI.m_VI)
{
	TX_ASSERT_POINTER(&PVI, PVISINFO);
	TX_ASSERT(PVI.m_VI.dwSize == sizeof(PVISINFO));

	m_Size = *(Dimension *)&PVI.m_Size;
	m_iRot = PVI.m_iRot;
	m_SecC = (Color &)PVI.m_SecC;
}

template<class T>
void PVisInfoT<T>::CopyTo (VISINFO &PVI)
{
	TX_ASSERT(TIsValidAddress(&PVI, sizeof(PVISINFO), true));
	TX_ASSERT(PVI.dwSize == sizeof(PVISINFO));

	T::CopyTo (PVI);
	((PVISINFO &)PVI).m_Size = *(SIZE *)&m_Size;
	((PVISINFO &)PVI).m_iRot = m_iRot;
	((PVISINFO &)PVI).m_SecC = (COLORREF &)m_SecC;
}

template<class T>
LVisInfoT<T>::LVisInfoT (LVISINFO &LVI)
	  : T (LVI.m_VI)
{
	TX_ASSERT_POINTER(&LVI, LVISINFO);
	TX_ASSERT(LVI.m_VI.dwSize == sizeof(LVISINFO));

	m_Width = LVI.m_Width;           // StrichStärke
}

template<class T>
void LVisInfoT<T>::CopyTo (VISINFO &LVI)
{
	TX_ASSERT(TIsValidAddress(&LVI, sizeof(LVISINFO), true));
	TX_ASSERT(LVI.dwSize == sizeof(LVISINFO));

	T::CopyTo (LVI);
	((LVISINFO &)LVI).m_Width = m_Width;
}

template<class T>
FVisInfoT<T>::FVisInfoT (FVISINFO &FVI)
	  : T (FVI.m_VI)
{
	TX_ASSERT_POINTER(&FVI, FVISINFO);
	TX_ASSERT(FVI.m_VI.dwSize == sizeof(FVISINFO));

	m_FillColor = *(Color *)&FVI.m_FC;
	m_iWidth = FVI.m_iWidth;
	m_iAttrEx = FVI.m_iAttrEx;
}

template<class T>
void FVisInfoT<T>::CopyTo (VISINFO &FVI)
{
	TX_ASSERT(TIsValidAddress(&FVI, sizeof(FVISINFO), true));
	TX_ASSERT(FVI.dwSize == sizeof(FVISINFO));

	T::CopyTo (FVI);
	((FVISINFO &)FVI).m_FC = *(COLORREF *)&m_FillColor;
	((FVISINFO &)FVI).m_iWidth = m_iWidth;
	((FVISINFO &)FVI).m_iAttrEx = m_iAttrEx;
}

template<class T>
TVisInfoT<T>::TVisInfoT (TVISINFO &TVI)
	  : T (TVI.m_VI)
{
	TX_ASSERT_POINTER(&TVI, TVISINFO);
	TX_ASSERT(TVI.m_VI.dwSize == sizeof(TVISINFO));

	m_Size = *(Dimension *)&TVI.m_Size;
	m_Type = TVI.m_Type;
	m_Rot = TVI.m_Rot;
	m_Orient = TVI.m_Orient;
}

template<class T>
void TVisInfoT<T>::CopyTo (VISINFO &TVI)
{
	TX_ASSERT(TIsValidAddress(&TVI, sizeof(TVISINFO), true));
	TX_ASSERT(TVI.dwSize == sizeof(TVISINFO));

	T::CopyTo (TVI);
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
	}		

return pVI;	
}

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

OldVisInfo *GetOldVI (VisInfo *pVI)
{
VISINFO *pVIC = VISINFOFromCPP (pVI);

	if (NULL == pVIC) return NULL;

OldVisInfo *pOldVI = OldVisInfoFromC (*pVIC, pVI -> isA());

	DELETE_OBJ(pVIC);
	return pOldVI;
}

#endif // MSWIND

