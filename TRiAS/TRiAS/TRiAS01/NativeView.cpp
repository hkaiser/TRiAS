///////////////////////////////////////////////////////////////////////////////
// @doc 
// @module NativeView.cpp | Declaration of <CNativeView> class

#include "trias01p.hxx"

#include <VisInfo_i.c>
#include <VisInfoInterfaces_i.c>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#include <ActDB.h>
#include <ErrInst.hxx>
#include <NativeView.h>
#include "switchkc.h"

#include "syncdb.hxx"
#include "ColorVal.h"

/////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface2(DVisInfo, IID_DVisInfo);
DefineSmartInterface2(DPointVisInfo, IID_DPointVisInfo);
DefineSmartInterface2(DLineVisInfo, IID_DLineVisInfo);
DefineSmartInterface2(DAreaVisInfo, IID_DAreaVisInfo);
DefineSmartInterface2(DTextVisInfo, IID_DTextVisInfo);

namespace trias_nativeview {

///////////////////////////////////////////////////////////////////////////////
// Konstruktor
CNativeView::CNativeView (HPROJECT hPr, LPCSTR pcName)
	: m_hPr(hPr), m_lRecNo(0L), m_lClipObj(0L)
{
	if (NULL != pcName) {
	char cbBuffer[MAXVIEWNAMELEN+1];

		CharToOem (pcName, cbBuffer);	// Zeichensatzkonvertierung
		m_strName = cbBuffer;
	}

// ein gutes Programm sollte tolerant sein :-)
	if (0 == m_strName.length()) {
		TX_ASSERT(m_strName.length() > 0);
		m_strName = "???";
	}
	
// Feststellen, ob Sicht bereits existiert
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB (m_hPr);
DB_ADDR dbaSICHT (m_hPr);			// gesuchte DatenBankadresse

	dbaSICHT.file_no = SICHT;
	{
	ErrInstall EI (WC_NOTFOUND);

		if (EC_OKAY == z_keyfind (&dbaSICHT, SICHTNAME, (LPVOID)m_strName.c_str()))
			m_lRecNo = dbaSICHT.rec_no;	// gesuchter Satz
	}
}

///////////////////////////////////////////////////////////////////////////////
// Liefert alle Ansichten dieser Datenbank
HRESULT CNativeView::EnumViews (HPROJECT hPr, HRESULT (CALLBACK *pFcn)(LPCSTR, DWORD), DWORD dwData)
{
	TX_ASSERT(NULL != hPr);
	SYNC_DBACCESS (g_pDbMutex, hPr);

CActDB ActDB (hPr);
DB_ADDR dba (hPr);
ErrInstall EI (WC_NOTFOUND);

// ersten SichtNamen suchen
ErrCode EC = (ErrCode)z_keyfirst (&dba, SICHTNAME);

	if (EC_OKAY != EC) {
	// Fehler aufgetreten
		if (EC == WC_NOTFOUND) 
			EC = EC_OKAY; 			// nichts gefunden: OK
		return (EC_OKAY == EC) ? S_OK : S_FALSE;	// sonstiger Fehler
	}

// für alle weiteren ID's
char cbSichtName[MAXVIEWNAMELEN+1];
HRESULT hr = S_OK;

	do {
	// Namen der Ansicht aus Schlüsseldatei lesen
		EC = (ErrCode)z_keyread (hPr, cbSichtName);
		if (EC != EC_OKAY) break;

		cbSichtName[MAXVIEWNAMELEN] = '\0';
		OemToChar (cbSichtName, cbSichtName);	// Zeichensatzkonvertierung

		{
		CKeyContext keyCtx;

			hr = pFcn (cbSichtName, dwData);
			if (S_OK != hr) return hr;

			ActDB.ReActivate();
		}
	// nächsten Schlüssel suchen
	} while (EC_OKAY == (ErrCode)z_keynext (&dba, SICHTNAME));

	if (EC == WC_NOTFOUND) 
		EC = EC_OKAY;           // nichts mehr gefunden: OK

	return (EC_OKAY == EC) ? S_OK : S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert alle Entries dieser Ansicht
HRESULT CNativeView::EnumEntries (HRESULT (CALLBACK *pFcn)(LONG, VisType, DWORD), DWORD dwData)
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

CActDB ActDB(m_hPr);
sicht locSicht;			// DatenStruktur (SichtSatz)
DB_ADDR dbaSICHT (m_hPr);	// DatenBankadresse
ErrCode RC;

// SichtSatz einlesen
	if (0 == m_lRecNo)      // Sicht existiert nicht 
		return HRESULT_FROM_ERRCODE(WC_NOTFOUND);

	dbaSICHT.file_no = SICHT;
	dbaSICHT.rec_no = m_lRecNo;
	__ReadHR (dbaSICHT, locSicht);

// Anzahl der Sätze im Set merken
long numTs = locSicht.idnum;         // Anzahl der Targets

// Speicher für Feld anfordern
	if (0 == numTs) 
		return S_OK;

// Identifikatoren einlesen
struct attribs Attr;
DB_ADDR dbaATTRIBS (m_hPr);
HRESULT hr = S_OK;

	dbaATTRIBS.file_no = ATTRIBS; // Dateinummer
	dbaATTRIBS.rec_no = locSicht.idset;

	for (long i = 0; i < numTs; i++) {
	// Kette bis zum bitteren Ende durchgehen
		if (0 == dbaATTRIBS.rec_no) {	// SatzNummer
			numTs = i;      // Set zu Ende, Anzahl korrigieren
			break;
		}

		__ReadHR (dbaATTRIBS, Attr);

	// CallBackFunktion rufen
		if (VT_Default == (VisType)Attr.attFlag) {
		// für jeden zur Ansicht gehörenden Objekttyp einmal rufen
			if (Attr.attDefVis & OTPunkt) {
				hr = pFcn (Attr.attTarget, VT_PunktDef, dwData);
				if (S_OK != hr) break;
			}
			if (Attr.attDefVis & OTLinie) {
				hr = pFcn (Attr.attTarget, VT_LinieDef, dwData);
				if (S_OK != hr) break;
			}
			if (Attr.attDefVis & OTFlaeche) {
				hr = pFcn (Attr.attTarget, VT_FlaecheDef, dwData);
				if (S_OK != hr) break;
			}
			if (Attr.attDefVis & OTText) {
				hr = pFcn (Attr.attTarget, VT_TextDef, dwData);
				if (S_OK != hr) break;
			}

		} else {
			hr = pFcn (Attr.attTarget, (VisType)Attr.attFlag, dwData);
			if (S_OK != hr) break;
		}
		dbaATTRIBS.rec_no = Attr.attSet;	// nächster Satz

		ActDB.ReActivate();
	}
	return hr;
}

static BOOL BitsInVisType (CNativeView::VisType iVTyp, int iBits)
{
	switch (iVTyp) {
	case CNativeView::VT_Punkt:
	case CNativeView::VT_PunktDef:
		return (iBits & TPPunkt) ? TRUE : FALSE;
	
	case CNativeView::VT_Linie:
	case CNativeView::VT_LinieDef:
		return (iBits & TPLinie) ? TRUE : FALSE;

	case CNativeView::VT_Flaeche:
	case CNativeView::VT_FlaecheDef:
		return (iBits & TPFlaeche) ? TRUE : FALSE;

	case CNativeView::VT_Text:
	case CNativeView::VT_TextDef:
		return (iBits & TPText) ? TRUE : FALSE;

	case CNativeView::VT_Default:
	default:
		break;
	}
	return FALSE;
}

#if defined(_DEBUG)
///////////////////////////////////////////////////////////////////////////////
// wird lediglich für ASSERT benötigt
static BOOL IsDefaultVisType (CNativeView::VisType iVTyp)
{
	switch (iVTyp) {
	case CNativeView::VT_PunktDef:
	case CNativeView::VT_LinieDef:
	case CNativeView::VT_FlaecheDef:
	case CNativeView::VT_TextDef:
	case CNativeView::VT_Default:
		return TRUE;		// Standard-Visualisierung (Voreinstellungen) verwenden

	default:
		break;
	}
	return FALSE;
}
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// Funktionen zur Erzeugung eines spezifischen DVisInfo-Objektes aus der DB-Info
#define SETVIS(Vis, Prop, Attr)		THROW_FAILED_HRESULT((Vis) -> put_##Prop(Attr))

HRESULT CNativeView::GetPointViewEntry (
	attribs &rAttr, DVisInfo **ppVI, const CLSID *pClsId, BOOL fDefault)
{
	USES_CONVERSION;
	try {
	TRIASCOLOR SecC = (TRIASCOLOR &)DEF_SECCOLOR;

		if (::LocGetDBVersion(m_hPr) >= VERSION0500000B)
			SecC = ((pattribs &)rAttr).pscolor;

	WDPointVisInfo PVis ((NULL == pClsId) ? CLSID_PointVisInfo : *pClsId);		// throws hr

		SETVIS(PVis, Priority, rAttr.attPrio);
		SETVIS(PVis, Style, rAttr.attStyle);
		SETVIS(PVis, Name, A2OLE(rAttr.attName));
		SETVIS(PVis, MainColor, (TRIASCOLOR &)rAttr.attPColor);

		if (!fDefault) {
			SETVIS(PVis, SizeX, ((pattribs &)rAttr).sizex);
			SETVIS(PVis, SizeY, ((pattribs &)rAttr).sizey);
			SETVIS(PVis, Rotate, ((pattribs &)rAttr).prot);
			SETVIS(PVis, BkColor, SecC);
		} else {
			SETVIS(PVis, SizeX, DEF_SIZE_PUNKT_X);
			SETVIS(PVis, SizeY, DEF_SIZE_PUNKT_Y);
			SETVIS(PVis, Rotate, 0);
			SETVIS(PVis, BkColor, (TRIASCOLOR &)DEF_SECCOLOR);
		}
		*ppVI = PVis.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return fDefault ? S_FALSE : S_OK;
}

HRESULT CNativeView::GetLineViewEntry (
	attribs &rAttr, DVisInfo **ppVI, const CLSID *pClsId, BOOL fDefault)
{
	USES_CONVERSION;
	try {
	WDLineVisInfo LVis ((NULL == pClsId) ? CLSID_LineVisInfo : *pClsId);		// throws hr

		SETVIS(LVis, Priority, rAttr.attPrio);
		SETVIS(LVis, Style, rAttr.attStyle);
		SETVIS(LVis, Name, A2OLE(rAttr.attName));
		SETVIS(LVis, MainColor, (TRIASCOLOR &)rAttr.attPColor);
		if (!fDefault) {
			SETVIS(LVis, Width, ((lattribs &)rAttr).width);
		} else {
			SETVIS(LVis, Width, DEF_WIDTH_LINIE);
		}
		*ppVI = LVis.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return fDefault ? S_FALSE : S_OK;
}

HRESULT CNativeView::GetAreaViewEntry (
	attribs &rAttr, DVisInfo **ppVI, const CLSID *pClsId, BOOL fDefault)
{
	USES_CONVERSION;
	try {
	WDAreaVisInfo FVis ((NULL == pClsId) ? CLSID_AreaVisInfo : *pClsId);		// throws hr
	int iStyle = LOWORD(rAttr.attStyle);

		SETVIS(FVis, Priority, rAttr.attPrio);
		SETVIS(FVis, Style, (iStyle & ~BMOpaque) % 100);
		SETVIS(FVis, Name, A2OLE(rAttr.attName));
		SETVIS(FVis, MainColor, rAttr.attPColor);

		if (!fDefault) {
			SETVIS(FVis, Width, (iStyle & ~BMOpaque) / 100);
			SETVIS(FVis, BkContour, (rAttr.attAttrEx & BMBkConture) ? TRUE : FALSE);
			SETVIS(FVis, BkColor, ((fattribs &)rAttr).bcolor);
			SETVIS(FVis, Opaque, (iStyle & BMOpaque) ? VARIANT_TRUE : VARIANT_FALSE);
		} else {
			SETVIS(FVis, Width, DEF_WIDTH_FRAME);
			SETVIS(FVis, BkContour, FALSE);
			SETVIS(FVis, BkColor, (TRIASCOLOR &)DEF_SECCOLOR);
			SETVIS(FVis, Opaque, FALSE);
		}
		*ppVI = FVis.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return fDefault ? S_FALSE : S_OK;
}

HRESULT CNativeView::GetTextViewEntry (
	attribs &rAttr, DVisInfo **ppVI, const CLSID *pClsId, BOOL fDefault)
{
	USES_CONVERSION;
	try {
	WDTextVisInfo TVis ((NULL == pClsId) ? CLSID_TextVisInfo : *pClsId);		// throws hr

		SETVIS(TVis, Priority, rAttr.attPrio);
		SETVIS(TVis, Style, rAttr.attStyle);
		SETVIS(TVis, Name, A2OLE(rAttr.attName));
		SETVIS(TVis, MainColor, rAttr.attPColor);

		if (!fDefault) {
			SETVIS(TVis, SizeX, ((tattribs &)rAttr).tsizex);
			SETVIS(TVis, SizeY, ((tattribs &)rAttr).tsizey);
			SETVIS(TVis, Rotate, ((tattribs &)rAttr).trot * 20);
			SETVIS(TVis, Slant, ((tattribs &)rAttr).trot * 20);

			SETVIS(TVis, StrikeThrough, (((tattribs &)rAttr).ttype & TV_StrikedThru) ? VARIANT_TRUE : VARIANT_FALSE);
			SETVIS(TVis, Underline, (((tattribs &)rAttr).ttype & TV_Underlined) ? VARIANT_TRUE : VARIANT_FALSE);
			SETVIS(TVis, Italic, (((tattribs &)rAttr).ttype & TV_Italic) ? VARIANT_TRUE : VARIANT_FALSE);
			SETVIS(TVis, Bold, (((tattribs &)rAttr).ttype & TV_Bold) ? VARIANT_TRUE : VARIANT_FALSE);

		int iType = ((tattribs &)rAttr).ttype & 0xff | (rAttr.attAttrEx << 8) & ~0xff;
		int rgStyle = FRAMESTYLE_NoFrame;

			if (iType & TV_Frame)
				rgStyle |= FRAMESTYLE_SimpleFrame;
			if (iType & TV_RoundFrame && iType & TV_Frame)
				rgStyle |= FRAMESTYLE_Rounded;
			if (iType & TV_BKMode) 
				rgStyle |= FRAMESTYLE_TargetColor;

			SETVIS(TVis, FrameStyle, (FRAMESTYLE)rgStyle);

		int rgAlign = ALIGNSTYLE_Left;

			if (iType & TV_RightAlign) 
				rgAlign = ALIGNSTYLE_Right;
			else if (iType & TV_CentreAlign)
				rgAlign = ALIGNSTYLE_Centre;
			else if (iType & TV_Justified)
				rgAlign = ALIGNSTYLE_Full;

			SETVIS(TVis, AlignStyle, (ALIGNSTYLE)rgAlign);

		} else {
			SETVIS(TVis, SizeX, DEF_SIZE_TEXT_X);
			SETVIS(TVis, SizeY, DEF_SIZE_TEXT_Y);
			SETVIS(TVis, Rotate, 0);
			SETVIS(TVis, Slant, 0);

			SETVIS(TVis, StrikeThrough, VARIANT_FALSE);
			SETVIS(TVis, Underline, VARIANT_FALSE);
			SETVIS(TVis, Italic, VARIANT_FALSE);
			SETVIS(TVis, Bold, VARIANT_FALSE);

			SETVIS(TVis, FrameStyle, FRAMESTYLE_NoFrame);
			SETVIS(TVis, AlignStyle, ALIGNSTYLE_Left);
		}
		*ppVI = TVis.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return fDefault ? S_FALSE : S_OK;
}

HRESULT CNativeView::GetDefaultViewEntry (
	attribs &rAttr, DVisInfo **ppVI, const CLSID *pClsId)
{
	USES_CONVERSION;
		
	try {
	WDVisInfo Vis ((NULL == pClsId) ? CLSID_DefaultVisInfo : *pClsId);		// throws hr

		SETVIS(Vis, Priority, rAttr.attPrio);
		SETVIS(Vis, Style, rAttr.attStyle);
		SETVIS(Vis, Name, A2OLE(rAttr.attName));
		SETVIS(Vis, MainColor, rAttr.attPColor);

		*ppVI = Vis.detach();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// FindTarget findet den Eintrag für einen Identifikator (OType == IDTyp) oder
// ein Objekt (OType == ONTyp) und liefert in VI die entsprechenden Attribute
// (sofern VI != NULL). Wenn VI == NULL ist, dann testet FindTarget lediglich
// ob ein Eintrag vorhanden ist (--> RückkehrCode).
//
// iType gibt den gesuchten VisTyp an (Punkt, Linie, Fläche etc.). Ist iType
// nicht gegeben (iType == -1), dann wird der erste gefundene verwendet.
//
// Wird ein bestimmter Satztyp nicht gefunden, dann wird im zugehörigen 
// DefaultSatz nachgesehen, ob dieser Typ überhaupt zur Sicht gehört. Wenn ja
// dann wird eine StandardVisualiserung generiert und WC_RETURN geliefert.
//
HRESULT CNativeView::GetViewEntry (
	LONG lTarget, VisType rgType, DVisInfo **ppVI, const CLSID *pClsId) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

// SichtSatz einlesen
CActDB ActDB(m_hPr);
DB_ADDR dbaSICHT (m_hPr);
sicht locSicht;
ErrCode RC;

	if (0 == m_lRecNo) {		// Sicht existiert nicht 
		if (NULL != ppVI)
			*ppVI = NULL;		// Id ist nicht vertreten
		return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
	}

	dbaSICHT.file_no = SICHT;
	dbaSICHT.rec_no = m_lRecNo;
	__ReadHR (dbaSICHT, locSicht);

// TargetSatz im Set suchen
DB_ADDR dbaATTRIBS(m_hPr);
attribs Attr;
BOOL fGenerateDefault = false;

	dbaATTRIBS.file_no = ATTRIBS;				// Dateinummer
	dbaATTRIBS.rec_no = locSicht.idset;			// SatzNummer

	do {
		if (0 == dbaATTRIBS.rec_no ||
		    ((unsigned long)Attr.attTarget > (unsigned long)lTarget)) 
		{
			if (NULL != ppVI) 
				*ppVI = NULL;		// nichts gefunden
			return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
		}

	// nächsten Satz einlesen
		__ReadHR (dbaATTRIBS, Attr);
		dbaATTRIBS.rec_no = Attr.attSet;

	// suchen bis Target und Typ (wenn gegeben) übereinstimmen
		if (Attr.attTarget != lTarget) 
			continue;	// noch nicht gefunden

		if (VT_DontCare == rgType) 
			break;	// ersten Satz nehmen
		else {
			if (VisType(Attr.attFlag) == (VisType)(rgType & ~VT_MaskDef)) 
				break;	// gefunden
			else if (VT_Default == VisType(Attr.attFlag)) {
				if (!BitsInVisType (rgType, Attr.attDefVis)) {
				// nicht in Sicht vertreten
					if (NULL != ppVI)
						*ppVI = NULL;
					return HRESULT_FROM_ERRCODE(WC_NOTFOUND);
				}
				fGenerateDefault = true;
				break;	// dieser Satz existiert nicht
			}
		} 
	} while (true);

// wenn VI gegeben ist, dann Informationen kopieren (neues Objekt generieren)
	if (!fGenerateDefault) {	// VisInfo kopieren
	// in dieser Ansicht ist zum gewünschten Ident/VisType eine VisInfo gespeichert

		if (NULL == ppVI)
			return S_OK;		// nur nachfragen, ob vorhanden

		switch (Attr.attFlag) {		// HIBYTE enthält zusätzliche Flags ab V5.00.00.011
		case VT_Punkt:		// Punktobjekt
			return GetPointViewEntry (Attr, ppVI, pClsId);

		case VT_Linie:		// Linien-(Kanten-)Objekt
			return GetLineViewEntry (Attr, ppVI, pClsId);

		case VT_Flaeche:	// Flächenobjekt
			return GetAreaViewEntry (Attr, ppVI, pClsId);

		case VT_Text:		// SchriftObjekt
			return GetTextViewEntry (Attr, ppVI, pClsId);

		case VT_Default:	// DefaultWerte, u.U. keine Objektspezifik
		// reine Sichtzugehörigkeit auswerten
			switch (rgType) {
			case VT_PunktDef:
				return GetPointViewEntry (Attr, ppVI, pClsId, TRUE);

			case VT_LinieDef:
				return GetLineViewEntry (Attr, ppVI, pClsId, TRUE);

			case VT_FlaecheDef:
				return GetAreaViewEntry (Attr, ppVI, pClsId, TRUE);

			case VT_TextDef:
				return GetTextViewEntry (Attr, ppVI, pClsId, TRUE);
				
			case VT_Default:
				return GetDefaultViewEntry (Attr, ppVI, pClsId);
			
			default:
				TX_ASSERT(IsDefaultVisType(rgType));	// snh
				break;
			}
			break;

		default:
			TX_ASSERT(FALSE);	// snh
			break;
		}

	} else if (fGenerateDefault) {
	// in dieser Ansicht ist zum gewünschten Ident/VisType lediglich die 
	// Sichtzugehörigkeit definiert

		if (NULL == ppVI) 
			return S_FALSE;			// nur nachfragen, ob vorhanden

	// typgerechte DefaultVisInfo erzeugen
	attribs DefAttr; 
	
		DefAttr.attStyle = DEF_STYLE;
		switch (rgType) {
		case VT_Punkt:		// Punktobjekt
		case VT_PunktDef:
			DefAttr.attPrio = DEF_PRIORITY_PUNKT;
			DefAttr.attStyle = DEF_STYLE_PUNKT;
			return GetPointViewEntry (DefAttr, ppVI, pClsId, TRUE);

		case VT_Linie:		// Linien-(Kanten-)Objekt
		case VT_LinieDef:
			DefAttr.attPrio = DEF_PRIORITY_LINIE;
			return GetLineViewEntry (DefAttr, ppVI, pClsId, TRUE);

		case VT_Flaeche:	// Flächenobjekt
		case VT_FlaecheDef:
			DefAttr.attPrio = DEF_PRIORITY_FLAECHE;
			return GetAreaViewEntry (DefAttr, ppVI, pClsId, TRUE);

		case VT_Text:		// SchriftObjekt
		case VT_TextDef:
			DefAttr.attPrio = DEF_PRIORITY_TEXT;
			DefAttr.attStyle = DEF_STYLE_TEXT;
			return GetTextViewEntry (DefAttr, ppVI, pClsId, TRUE);

		case VT_Default:	// DefaultWerte, keine Objektspezifik
			return GetDefaultViewEntry (DefAttr, ppVI, pClsId);

		default:
			TX_ASSERT(FALSE);	// snh
			break;
		}
	} 
	return E_FAIL;		// irgendwas ist schiefgegangen
}

///////////////////////////////////////////////////////////////////////////////
// Liefert Objekt, an der diese Ansicht geclippt werden soll 
HRESULT CNativeView::GetObjRgn (LONG *plClipObj) 
{
	TX_ASSERT(NULL != m_hPr);
	SYNC_DBACCESS (g_pDbMutex, m_hPr);

	if (NULL == plClipObj) return E_POINTER;

// nur wenn Version neuer als 006 ist
	if (::LocGetDBVersion(m_hPr) <= VERSION05000005) 
		return E_FAIL;

	*plClipObj = 0L;		// für alle Fälle

// SichtKopfSatz einlesen
CActDB ActDB (m_hPr);
sicht locSicht;
DB_ADDR dbaSICHT (m_hPr);

	if (0 == m_lRecNo) 		// Sicht existiert nicht 
		return HRESULT_FROM_ERRCODE((ErrCode)db_error (WC_NOTFOUND, RC_GetObjRgn));

	if (0 != m_lClipObj) {
		*plClipObj = m_lClipObj;
		return S_OK;
	}

// noch nicht gelesen
ErrCode RC;

	dbaSICHT.file_no = SICHT;
	dbaSICHT.rec_no = m_lRecNo;
	__ReadHR(dbaSICHT, locSicht);
	
	m_lClipObj = locSicht.objrgn;		// liefert ObjektNummer
	*plClipObj = m_lClipObj;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Textmerkmal eines Identifikators lesen
HRESULT CNativeView::GetTextMerkmal (INT_PTR lMCode, os_string &rStr)
{
CActDB ActDB(m_hPr);
long lTarget = ::GetMerkmalTarget (m_hPr, (void *)m_strName.c_str(), TT_Sicht);

	if (-1 == lTarget) return E_UNEXPECTED;

char *pT = NULL;

	try {
		THROW_FAILED_HRESULT(::GetTextMerkmal (m_hPr, lMCode, lTarget, TT_Sicht, &pT));
		rStr = pT;

	} catch (_com_error &e) {
		DELETE_VEC(pT);
		return _COM_ERROR(e);
	} catch (...) {
		DELETE_VEC(pT);
		return E_OUTOFMEMORY;
	}

	DELETE_VEC(pT);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Neues Textmerkmal erzeugen
HRESULT CNativeView::PutTextMerkmal (INT_PTR lMCode, LPCSTR pcNewText)
{
CActDB ActDB(m_hPr);
long lTarget = ::GetMerkmalTarget (m_hPr, (void *)m_strName.c_str(), TT_Sicht);

	if (-1 == lTarget) 
		return E_UNEXPECTED;

ErrInstall EI (WC_NOTFOUND);

	::DeleteTextMerkmal (m_hPr, lMCode, lTarget, TT_Objekt);
	return ::PutTextMerkmal (m_hPr, lMCode, lTarget, TT_Sicht, pcNewText);
}

/////////////////////////////////////////////////////////////////////////////
// Textmerkmal löschen
HRESULT CNativeView::DeleteTextMerkmal (INT_PTR lMCode)
{
CActDB ActDB(m_hPr);
long lTarget = ::GetMerkmalTarget (m_hPr, (void *)m_strName.c_str(), TT_Sicht);

	if (-1 == lTarget) 
		return E_UNEXPECTED;

ErrInstall EI (WC_NOTFOUND);

	return ::DeleteTextMerkmal (m_hPr, lMCode, lTarget, TT_Sicht);
}

} // namespace trias_nativeview
