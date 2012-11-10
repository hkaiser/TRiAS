// Veraenderung der VisAttribute von allen Objekten eines Identifikators ------
// File: VISPARAM.CXX

#include "triaspre.hxx"

// STL stuff ------------------------------------------------------------------
#define NOMINMAX
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)         // debug info truncated
#include <ospace/std/list>

#include "triasres.h"

#include <owncombo.hxx>
#include <efont.hxx>

#include "clbmpobj.hxx"
#include "prntabrt.hxx"
#include "printer.hxx"
#include "dcolor.hxx"
#include "palrect.hxx"
#include "colorbox.hxx"
#include "palwind.hxx"

#include "vispara3.hxx"
#include "objtype.hxx"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern class CLegendeWindow *pLegende;
extern bool LegendToRepaint;

extern HPALETTE hPalette;

// globale Funktionen ---------------------------------------------------------
Dimension GetDotsPerMM (HDC hDC);
VisInfo *MakeNewVI (VisType iVTyp);
short VTypToBits (VisType iVTyp);

// lokale Funktionsprototypen -------------------------------------------------
ErrCode ChangePVisInfo (pWindow pW, DatenBasisObjekt &, PVisInfo **pVI, char *CapString, bool fHSB = false, bool fCustom = false);
ErrCode ChangeLVisInfo (pWindow pW, DatenBasisObjekt &, LVisInfo **pVI, char *CapString, bool fHSB = false);
ErrCode ChangeFVisInfo (pWindow pW, DatenBasisObjekt &, FVisInfo **pVI, char *CapString, bool fHSB = false);
ErrCode ChangeTVisInfo (pWindow pW, TVisInfo **pVI, char *CapString, short fCustom = false);

#if defined(OLDADDNEWCOLORSTOPALETTE) // ======================================
static HPALETTE AddNewColorsToPalette (VisInfo *, HPALETTE);
#else
static bool AddNewColorsToPalette (VisInfo *, HPALETTE);
#endif
static VisInfo *MakeNewVI (VisInfo *, ObjTyp);

// Funktion, die DialogBox anzeigt und Identifikator auswählt -----------------
ErrCode IrisWind :: ChangeIdVisInfo (long ID, bool) 
{
// Dialogfenster generieren
CEierUhr Wait (this);
VisInfoDlg VIDlg (this);

// eigene Page hinzufügen
CVisInfoPage PPage (DBO(), ID, VT_Punkt, ResString (IDS_OBJTYPPUNKT, 16));
CVisInfoPage LPage (DBO(), ID, VT_Linie, ResString (IDS_OBJTYPLINIE, 16));
CVisInfoPage FPage (DBO(), ID, VT_Flaeche, ResString (IDS_OBJTYPFLAECHE, 16));
CVisInfoPage TPage (DBO(), ID, VT_Text, ResString (IDS_OBJTYPTEXT, 16));

	VIDlg.AddPage (&FPage);			// eigene Pages lassen
	VIDlg.AddPage (&LPage);
	VIDlg.AddPage (&PPage);
	VIDlg.AddPage (&TPage);

//	LoadPages (VIDlg, g_cbDocKey, g_cbDocSubKey);			// zusätzliche Pages aus Registry laden

	Wait.Hide();
	VIDlg.Show();	// DialogBox anzeigen und Ident/Vistyp auswählen lassen

return VIDlg.Result() ? EC_OKAY : WC_RETURN;
}

///////////////////////////////////////////////////////////////////////////////
// PropertySheet für Ident/Vistypauswahl
VisInfoDlg::VisInfoDlg (pWindow pWnd)
		   : CPropertySheet (ResString (IDS_VISPARAMCAP, 64), pWnd, PSH_NOAPPLYNOW)
{
}

VisInfoDlg::~VisInfoDlg (void)
{
}

///////////////////////////////////////////////////////////////////////////////
// eine Page (Punkte/Linien/Flächen/Texte)
inline long GetIdentFromEntry (char *pBuffer, int iIdBase)
{
	TX_ASSERT(pBuffer);

return strtoul (pBuffer, NULL, iIdBase);
}

// eigentliche Arbeit - Einstellen der Farben entsprechend VisTyp -------------
ErrCode CVisInfoPage :: ChangeIdVisInfo (VisType iVTyp)
{
// entsprechend ObjektTyp dieses ID's VisInfo einstellen lassen
CTable tId (DBO().Idents().IdentTree());
ErrCode RC;
VisInfo *pVI = NULL;

	if (tId.Find (&m_lID)) {
	CIdentifikatorLock l(tId);

		if (l) pVI = l -> GetVisInfo (iVTyp);
	}

	if (pVI == NULL) {		// in dieser Sicht nicht vorhanden
		pVI = MakeNewVI (iVTyp);
		if (pVI == NULL) {
			EndDlg();
			return EC_NOMEMORY;
		}
	}

short oldPriority = pVI -> Priority();

	if (pVI -> isA() == VT_Default) 
		pVI = MakeNewVI (pVI, VTypToOTyp (iVTyp));

// speichern aller zu bearbeitenden Idents
list<ULONG> IdList;
short iIndex = m_mslbIdentList.GetFirstSelected();
char InBuff[_MAX_PATH];

	TX_ASSERT(iIndex != -1);	// mindestens ein Ident selektiert

	while (iIndex != -1) {
		m_mslbIdentList.GetString (InBuff, iIndex, sizeof(InBuff));
		IdList.push_back ((ULONG)GetIdentFromEntry (InBuff, m_iIdBase));	// Ident holen
		iIndex = m_mslbIdentList.GetNextSelected();
	}	

	switch (iVTyp) {
	case VT_Punkt:
		RC = ChangePVisInfo (this, DBO(), (PVisInfo **)&pVI, IDString(), m_rbHSB.GetState(),
				     DEX_GetDBVersion() >= VERSION0500000B);
		break;

	case VT_Linie:	
		RC = ChangeLVisInfo (this, DBO(), (LVisInfo **)&pVI, IDString(), m_rbHSB.GetState());
		break;

	case VT_Flaeche:
		RC = ChangeFVisInfo (this, DBO(), (FVisInfo **)&pVI, IDString(), m_rbHSB.GetState());
		break;

	case VT_Text:
		RC = ChangeTVisInfo (this, (TVisInfo **)&pVI, IDString(), 
				     DEX_GetDBVersion() >= VERSION0500000B);
		break;

	case VT_Default:
	default:
		DELETE (pVI);
		return EC_OKAY;
	}

	if (RC != EC_OKAY) {
		DELETE (pVI);
		return RC;	// Fehler oder abbrechen
	}

// jetzt alle zu behandelnden Idents auch behandeln
CEierUhr Wait (this);		// EierUhr anzeigen

	for (list<ULONG>::iterator it = IdList.begin(); it != IdList.end(); it++) {
	ULONG lIdent = *it;

		if (tId.Find (&lIdent)) {
		CIdentifikatorLock l(tId);
		
			if (l) {
			// alte Priorität besorgen und VisInfo wegschreiben
			VisInfo *pNewVI = (VisInfo *)pVI -> Copy();

				pNewVI -> Priority() = l -> Priority (iVTyp);
				DBASSERT (DBO().ChangeVisInfo (*l, iVTyp, pNewVI));
			}
		}
	}	
	DELETE (pVI);		// Master wieder beseitigen

return EC_OKAY;
}

// DialogBox, die es erlaubt einen Identifikator auszuwählen ------------------
void CVisInfoPage :: FillEntryList (void)
{
//	m_mslbIdentList.Hide();
//	m_mslbIdentList.Clear();

	DBO().Idents().IdentTree().Every (FillIdentSelBox, this);
//	m_mslbIdentList.Show();
}

bool EXPORTTRIAS FillIdentSelBox (void *pObj, void *pData) 
{
CVisInfoPage *pPage = reinterpret_cast<CVisInfoPage *>(pData);
CIdentifikator *pId = reinterpret_cast<CIdentifikator *>(pObj);

	TX_ASSERT(pPage);
	TX_ASSERT(pId);

DatenBasisObjekt &rDBO = pPage -> DBO();
short iObjTypes = pId -> GetOTypes(rDBO.DB()) & pId -> toPaint();

	if (iObjTypes & VTypToBits (pPage -> VTyp())) {		// nur diese Sicht
	PBD_Ident Id (&(rDBO.PbdDB()), pId -> Id());  // KurzText lesen

		pPage -> AddEntry (pId, Id.GetKurzText());
	}

return true;
}

#pragma warning (disable: 4355)

CVisInfoPage :: CVisInfoPage (DatenBasisObjekt &rDBO, long ID, 
							  VisType rgVTyp, LPCSTR pcCaption)
	    : CPropertyPage (VISPARAMCTRLPAGE, pcCaption),
	      m_mslbIdentList (this, IDL_VISPARAMS),
	      m_pbDefine (this, IDC_DEFINE),
	      m_rbRGB (this, IDR_RGB),
	      m_rbHSB (this, IDR_HSB),
	      m_rDBO (rDBO), m_rgVTyp(rgVTyp)
{
	m_lID = ID;
	m_pIDString = NULL;
	m_iIdBase = DEX_GetIdBase();

	m_fI = true;
	m_fO = true;
}

void CVisInfoPage :: WindowInit (Event)
{
// Controls initialisieren
	m_pbDefine.FInit();
	m_rbRGB.FInit();
	m_rbHSB.FInit();
	m_mslbIdentList.FInit();

// ListBox mit allen Identifikatoren (dieser Sicht) füllen
	FillEntryList();

// wenn ListBox nicht leer ist, dann ersten Eintrag selektieren, 
// ansonsten vorselektieren
	if (m_mslbIdentList.GetCount() > 0) {
		if (m_lID == -1L) {
			m_mslbIdentList.SetCaretIndex (0);
			m_mslbIdentList.ChangeSelected (0, On);
			AdjustButton (0);
		} else {
		char inBuff[20];
		int iIndex = m_mslbIdentList.FindString (ultoa (m_lID, inBuff, m_iIdBase));
		
			if (iIndex == -1L) iIndex = 0;
			m_mslbIdentList.SetCaretIndex (iIndex);
			m_mslbIdentList.ChangeSelected (iIndex, On);
			AdjustButton (iIndex);
		}
	} else
		ChangeButton (false, false);
	
// Farbmodell auswählen
	m_rbRGB.SetState (true);
	m_rbHSB.SetState (false);
}

bool CVisInfoPage :: OnOK (NotifyEvt)
{
	return false;	// always allow operation
}

#pragma warning (default: 4355)

CVisInfoPage :: ~CVisInfoPage (void) 
{
	DELETE (m_pIDString);
}

VisType FGetVisTyp (char *pBuffer)
{
	if (pBuffer == NULL) return VT_Default;

	switch (*pBuffer) {
	case 'P':	return VT_Punkt;
	case 'L':	return VT_Linie;
	case 'F':	return VT_Flaeche;
	case 'T':	return VT_Text;
	case 'U':
	default:
		break;
	}

return VT_Default;
}


// EventHandler ---------------------------------------------------------------
void CVisInfoPage :: ButtonClick (ControlEvt e) 
{
	switch ((uint)e.GetControlID ()) {
	case IDC_DEFINE:
		ChangeVisEntry (m_rgVTyp);
		break;
	}
}

// Einstellung für einen Identifikator (P/L/F/T) ------------------------------
void CVisInfoPage :: ChangeVisEntry (VisType iVTyp)
{
short Index = m_mslbIdentList.GetCaretIndex();
char InBuff[_MAX_PATH];

	if (Index == -1) {
		m_lID = -1;
		return;
	}
	m_mslbIdentList.GetString (InBuff, Index, sizeof(InBuff));

// Werte des zu verändernden ID's holen
long ID = GetIdentFromEntry (InBuff, m_iIdBase);	// Ident holen

	if (ID != 0L) m_lID = ID;
	TX_ASSERT(m_lID != -1);

	DELETE (m_pIDString);

	if (m_mslbIdentList.GetNoSelected() > 1) {	// mehrere Idents
	ResString SelIds (IDS_SELECTEDIDENTS, 40);
	
		m_pIDString = new char [_MAX_PATH];
		if (m_pIDString == NULL) {
			db_error (EC_NOMEMORY, RC_VisInfoDlgEnd);
			EndDlg();
		}
		strcpy (m_pIDString, SelIds);
	} else {
	LPSTR cptr = strrchr (InBuff, ':');
	
		TX_ASSERT(cptr);
	
	LPSTR lpTmp = strrlchr (cptr, ' ');
	ResString resUnkID (IDS_KTUNKNOWNIDENT, 40);
	
		if (lpTmp) *lpTmp = '\0';	// TrimmRight
		if (*++cptr == '\0') 		// KurzText nicht vorhanden
			cptr = (LPSTR)resUnkID.Addr();

		m_pIDString = new char [strlen(cptr)+_MAX_PATH];
		if (m_pIDString == NULL) {
			db_error (EC_NOMEMORY, RC_VisInfoDlgEnd);
			EndDlg();
		}

	char cbCaption[32];

		GetCaption (cbCaption, sizeof(cbCaption));
		if (m_iIdBase == 10)
			wsprintf (m_pIDString, "%s \'%s (%08ld)\'", cbCaption, cptr, m_lID);
		else
			wsprintf (m_pIDString, "%s \'%s (%08lx)\'", cbCaption, cptr, m_lID);
	}

// VisInfo einstellen lassen
	if (ChangeIdVisInfo (iVTyp) == EC_OKAY) {
	// Text richten
		AdjustButton (Index);

	// warten, bis Fenster neu gezeichnet ist
		GetParent() -> Update();
	}
}

// Selektion innerhalb der ListBox --------------------------------------------
void CVisInfoPage :: ChangeButton (bool fI, bool fO)
{
	if (m_fI != fI) {
		if (fI) {
		ResString rsEdit (IDS_VISDEFINE, 20);

			m_pbDefine.SetText (rsEdit.Addr());
		} else {
		ResString rsNew (IDS_VISDEFINENEW, 20);

			m_pbDefine.SetText (rsNew.Addr());
		}
		m_fI = fI;
	}

	if (m_fO != fO) {
	// nur aktivieren, wenn Objekte in Datenbank sind
		if (fO) m_pbDefine.Enable();
		else	m_pbDefine.Disable();

		m_fO = fO;
	}
}

void CVisInfoPage :: ListBoxSel (ControlEvt)
{
	AdjustButton (m_mslbIdentList.GetCaretIndex());
}

void CVisInfoPage :: AdjustButton (short iIndex)
{
	TX_ASSERT(iIndex != -1);

char InBuff[_MAX_PATH];

	m_mslbIdentList.GetString (InBuff, iIndex, sizeof(InBuff));

// Werte des zu verändernden ID's holen
long ID = GetIdentFromEntry (InBuff, m_iIdBase);	// Ident holen
CTable t(DBO().Idents().IdentTree());

	if (t.Find (&ID)) {
	CIdentifikatorLock l(t);

		if (l) {
		short fBits = l -> isCustomized();
		short fOTypes = l -> GetOTypes(DBO().DB()) & l -> toPaint();
		short iOTyp = VTypToBits (m_rgVTyp);

			ChangeButton ((fBits & iOTyp) ? true : false, (fOTypes & iOTyp) ? true : false);
		}
	}
}

// Funktion, welche einen Listboxeintrag generiert ----------------------------
char cVisType (VisType iVTyp)
{
	switch (iVTyp) {
	case VT_Punkt:		return 'P';
	case VT_Linie:		return 'L';
	case VT_Flaeche:	return 'F';
	case VT_Text:		return 'T';
	case VT_Default:
		break;

	default:
		TX_ASSERT(false);
		break;
	}

return '\0';
}

bool CVisInfoPage :: AddEntry (CIdentifikator *pId, char *pKT)
{
long lIdent = pId -> Id();
char OutBuff[_MAX_PATH];

	if (m_iIdBase == 10) 
		wsprintf (OutBuff, "%08ld:%-45s", lIdent, pKT);
	else
		wsprintf (OutBuff, "%08lx:%-45s", lIdent, pKT);

// in ListBox einfügen, gegebenenfalls sofort selektieren
int newIndex = m_mslbIdentList.AddString (OutBuff);

	if (m_lID != -1L && m_lID == lIdent) {
		m_mslbIdentList.SetCaretIndex (newIndex);
		m_mslbIdentList.ChangeSelected (newIndex , On);
	}

return true;
}

// lokale Funktionen ----------------------------------------------------------
ErrCode ChangePVisInfo (pWindow pW, DatenBasisObjekt &rDBO, 
			PVisInfo **pVI, char *pCapString, 
			bool fHSB, bool fCustom) 
{
char lpoldCaption[81];
char lpnewCaption[81];
short oldPriority = *pVI ? (*pVI) -> Priority() : DEF_PRIORITY_PUNKT;
short oldRotation = *pVI ? (*pVI) -> Rotation() : 0;
CEierUhr Wait (pW);
PointPaletteWindow PPW (pW, rDBO,
		*pVI ? (*pVI) -> PrimColor() : DEF_COLOR,
		*pVI ? (*pVI) -> Size() : DEF_SIZE_PUNKT,
		*pVI ? (*pVI) -> Style() : DEF_STYLE_PUNKT,
		fHSB ? true : false, oldRotation,
		*pVI ? (*pVI) -> SecColor() : DEF_SECCOLOR
#if defined(WIN32)
		, fCustom
#endif // WIN32
	);
				
	if (*pVI) {
		delete *pVI;
		*pVI = NULL;
	}

// Der Captiontext wird aus dem in der Ressource enthaltenen FormatString und 
// dem IdentifikatorKurztext zusammengesetzt. Dabei ist zu beachten, daß der 
// Pointer auf den Kurztext nicht hier freigegeben werden darf, da IDString() 
// lediglich eine Kopie des Pointers liefert. Der Kurztext selbst wird 
// innerhalb des VIDlg-Objektes verwaltet.

// Caption der DialogBox anpassen
	if (pCapString == NULL) pCapString = "";
	
	PPW.GetCaption (lpoldCaption, 80);
	wsprintf (lpnewCaption, lpoldCaption, pCapString);
	PPW.SetCaption (lpnewCaption);

// DialogBox anzeigen
	Wait.Hide();
	PPW.Show();
	if (!PPW.Result()) return WC_RETURN;

// alles OK, VisInfo ändern
	*pVI = new PVisInfo (PPW.GetPointSymbol(), oldPriority,
			     PPW.GetMainColor(), PPW.GetSize(), 
			     NULL, PPW.GetRotation(), PPW.Get2ndColor());
	if (*pVI == NULL)
		return (ErrCode)db_error (EC_NOMEMORY, RC_ChangeIdVisInfo);

return EC_OKAY;
}

inline short CorrectedLWidth (LVisInfo *pLVI)
{
	return pLVI ? short(pLVI -> Width()) : DEF_WIDTH_LINIE;
}

inline short CorrectedStyle (LVisInfo *pLVI)
{
	return pLVI ? short (pLVI -> Style()) : DEF_STYLE;
}

ErrCode ChangeLVisInfo (pWindow pW, DatenBasisObjekt &rDBO, LVisInfo **pVI, 
			char *pCapString, bool fHSB)
{
char lpoldCaption[81];
char lpnewCaption[81];
short oldPriority = *pVI ? (*pVI) -> Priority() : DEF_PRIORITY_LINIE;
CEierUhr Wait (pW);
LinePaletteWindow LPW (pW, rDBO,
		*pVI ? (*pVI) -> PrimColor() : DEF_COLOR,
		CorrectedLWidth (*pVI),
		CorrectedStyle (*pVI),
		fHSB ? true : false
	);
				
	if (*pVI) {
		delete *pVI;
		*pVI = NULL;
	}

// Caption der DialogBox anpassen
	if (pCapString == NULL) pCapString = "";
	
	LPW.GetCaption (lpoldCaption, 80);
	wsprintf (lpnewCaption, lpoldCaption, pCapString);
	LPW.SetCaption (lpnewCaption);

// DialogBox anzeigen
	Wait.Hide();
	LPW.Show ();
	if (!LPW.Result()) return WC_RETURN;

// alles OK, VisInfo ändern
	*pVI = new LVisInfo (LPW.GetLineStyle(), oldPriority,
					LPW.GetMainColor(), LPW.GetWidth());
	if (*pVI == NULL)
		return (ErrCode)db_error (EC_NOMEMORY, RC_ChangeIdVisInfo);

return EC_OKAY;
}

inline short CorrectedFWidth (FVisInfo *pFVI)
{
	return pFVI ? short(pFVI -> Width()) : 0;
}

inline short CorrectedType (FVisInfo *pFVI)
{
	return pFVI ? short(pFVI -> Type()) : DEF_STYLE;
}

ErrCode ChangeFVisInfo (pWindow pW, DatenBasisObjekt &rDBO, 
			FVisInfo **pVI, char *pCapString, bool fHSB)
{
char lpoldCaption[81];
char lpnewCaption[81];
short oldPriority = *pVI ? (*pVI) -> Priority() : DEF_PRIORITY_FLAECHE;
Color FillColor = *pVI ? (*pVI) -> SecColor() : DEF_COLOR;
Color KColor = *pVI ? (*pVI) -> PrimColor() : DEF_COLOR;

	if (FillColor.Reserved() == 1) {
	// PALETTEINDEX konvertieren 
		GetPaletteEntries (hPalette, FillColor.Red(), 1, 
						(PALETTEENTRY *)&FillColor);
		GetPaletteEntries (hPalette, KColor.Red(), 1, 
						(PALETTEENTRY *)&KColor);
	}
	FillColor.Reserved() = 0;	// jetzt explizite RGB-Farben
	KColor.Reserved() = 0;

CEierUhr Wait (pW);
#if defined(OLDVISINFO)
AreaPaletteWindow APW (pW, rDBO, KColor, FillColor, 
		       *pVI ? (*pVI) -> Style() : DEF_STYLE, 
		       fHSB ? true : false);
#else
AreaPaletteWindow APW (pW, rDBO, KColor, FillColor, 
		       CorrectedType (*pVI), 
		       CorrectedFWidth (*pVI),
		       fHSB ? true : false,
		       *pVI ? (*pVI) -> isBkConture() : false,
		       *pVI ? (*pVI) -> isOpaque() : false
		       );
#endif // OLDVISINFO
	
	if (*pVI) {
		delete *pVI;
		*pVI = NULL;
	}
	
// Caption der DialogBox anpassen
	if (pCapString == NULL) pCapString = "";
		
	APW.GetCaption (lpoldCaption, 80);
	wsprintf (lpnewCaption, lpoldCaption, pCapString);
	APW.SetCaption (lpnewCaption);
	
// DialogBox anzeigen
	Wait.Hide();
	APW.Show ();
	if (!APW.Result()) return WC_RETURN;

// alles OK, VisInfo ändern
	*pVI = new FVisInfo (APW.GetStyle() | APW.GetBkMode(), oldPriority,
			     APW.GetMainColor(), APW.GetFillColor(), 
			     APW.GetBkContureMode());
	if (*pVI == NULL)
		return (ErrCode)db_error (EC_NOMEMORY, RC_ChangeIdVisInfo);

return EC_OKAY;
}

ErrCode ChangeTVisInfo (pWindow pW, TVisInfo **pVI, char *pCapString, short fCustom) 
{
static char lpnewCaption[_MAX_PATH];
HWND hWnd = pW -> Handle(API_CLIENT_HWND);

// Caption der DialogBox anpassen
	if (pCapString == NULL) pCapString = "";
	
	wsprintf (lpnewCaption, ResString (IDS_CHOOSEFONTCAP, 50), pCapString);

// Font generieren
Dimension locDotsPerMM = GetDotsPerMM (NULL);
CoOrd PtX = (CoOrd)((double)locDotsPerMM.Width() * 
		    (double)((*pVI) -> Size().Width()) * 0.3176 + 0.5);
CoOrd PtY = (CoOrd)((double)locDotsPerMM.Height() *
		    (double)((*pVI) -> Size().Height()) * 0.3176 + 0.5);
Font *pF = MakeFont (*pVI, Dimension (PtX, PtY));

	if (pF == NULL) return EC_NOMEMORY;

ActPrinterPars ActPPDev;	// aktiver Drucker

// bei Erfolg ist *pVI bereits geändert
	if (!((ExtFont *)pF) -> ChooseFont (hWnd, lpnewCaption, pVI, ActPPDev, fCustom)) {
		DELETE (pF);
		return WC_RETURN;
	}

// Fontgröße wieder in Punkt umrechnen
	(*pVI) -> Size().Width() = 
				(CoOrd)(((double)((*pVI) -> Size().Width()) / 
					((double)locDotsPerMM.Width() * 0.3176)) + 0.5);
	if ((*pVI) -> Size().Height() > 0) {
		(*pVI) -> Size().Height() = 
				(CoOrd)(((double)((*pVI) -> Size().Height()) / 
					((double)locDotsPerMM.Height() * 0.3176)) + 0.5);
	} else {
		(*pVI) -> Size().Height() = 
				(CoOrd)(((double)((*pVI) -> Size().Height()) /
					((double)locDotsPerMM.Height() * 0.3176)) - 0.5);
	}

// Speicher freigeben
	DELETE (pF);
	
return EC_OKAY;
}

// Neue Farbe(n) zu Palette hinzufügen ----------------------------------------
static inline bool ColorCmp (Color &C1, Color &C2) 
{
bool retVal = false;

	if (C1.Red() == C2.Red() &&
	    C1.Green() == C2.Green() &&
	    C1.Blue() == C2.Blue())
		retVal = true;

return retVal;
}

static void AddEntryToPalette (LOGPALETTE *pPal, Color C, int &num) 
{
	for (short i = 0; i < num; i++) {
		if (ColorCmp (C, *(Color *)&pPal -> palPalEntry[i]))
			break;
	}
	if (i == num) {
		pPal -> palPalEntry[i].peRed = C.Red();
		pPal -> palPalEntry[i].peGreen = C.Green();
		pPal -> palPalEntry[i].peBlue = C.Blue();
		pPal -> palPalEntry[i].peFlags = 0;
		num++;
	}
}

static VisInfo *MakeNewVI (VisInfo *pVI, ObjTyp OT) 
{
VisInfo *pNewVI;

	if (pVI == NULL) return NULL;

	switch (OT) {
	case OT_PUNKT:
		pNewVI = new PVisInfo (pVI -> Style(), 
				       pVI -> Priority(), 
				       pVI -> PrimColor(), 
				       Dimension (200, 200)
			     );
		break;

	case OT_KANTE:
		pNewVI = new LVisInfo (pVI -> Style(), 
				       pVI -> Priority(), 
				       pVI -> PrimColor(), 
				       0
			     );
		break;

	case OT_KREIS:
	case OT_FLAECHE:
		pNewVI = new FVisInfo (pVI -> Style(), 
				       pVI -> Priority(), 
				       pVI -> PrimColor(), 
				       pVI -> PrimColor(),
				       0
			     );
		break;

	case OT_TEXT:
		pNewVI = new TVisInfo (pVI -> Style(),
				       pVI -> Priority(),
				       pVI -> PrimColor(),
				       DEF_SIZE_TEXT,
				       0x0, 0
			     );
		break;

	case OT_KO:
	case OT_UNKNOWN:
		pNewVI = NULL;
		break;

	default:
		pNewVI = NULL;
		TX_ASSERT(false);
		break;
	}

// alte VI freigeben
	DELETE (pVI);

return pNewVI;
}


// Externe Schnittstelle zur Einstellung einer VisInfo ------------------------
short IrisWind :: ChangeVisInfoExt (HANDLEVISINFO *pHVI)
{
ErrCode RC = EC_OKAY;
VisInfo *pVI = VisInfoFromC (*pHVI -> m_pVI, (VisType)pHVI -> m_iVTyp);
VisInfo *pOldVI = (VisInfo *)pVI -> Copy();
short iResult = DO_UnChanged;

	if (pVI == NULL || pOldVI == NULL) {
		DELETE (pVI);
		return EC_NOMEMORY;
	}
	
bool fToDeleteWindow = false;
Window *pW = NULL;

	if (pHVI -> dwSize == sizeof(HANDLEVISINFO) && pHVI -> m_hWnd != 0) {
		pW = new Window (pHVI -> m_hWnd);
		if (pW) fToDeleteWindow = true;
		else 
			pW = this;	// initialisierungsFehler
	} else
		pW = this;

	switch (pHVI -> m_iVTyp) {
	case VT_Punkt:
		{
		bool fCustom = pHVI -> m_fFlags & DT_CustomVisualisation;

			RC = ChangePVisInfo (pW, DBO(), (PVisInfo **)&pVI, pHVI -> m_pDesc, pHVI -> m_fFlags & DF_HSBModel, fCustom);
			if (RC != EC_OKAY) break;
			if (pVI -> Style() != pOldVI -> Style()) 
				iResult |= DO_StyleChanged;
			if (((PVisInfo *)pOldVI) -> Size().Width() != ((PVisInfo *)pVI) -> Size().Width() ||
			    ((PVisInfo *)pOldVI) -> Size().Height() != ((PVisInfo *)pVI) -> Size().Height())
				iResult |= DO_SizeChanged;
			if (((PVisInfo *)pOldVI) -> Rotation() != ((PVisInfo *)pVI) -> Rotation())
				iResult |= DO_OthersChanged;
			if ((COLORREF &)((PVisInfo *)pOldVI) -> SecColor() != 
			    (COLORREF &)((PVisInfo *)pVI) -> SecColor())
				iResult |= DO_SecColorChanged;
		}
		break;

	case VT_Linie:	
		RC = ChangeLVisInfo (pW, DBO(), (LVisInfo **)&pVI, pHVI -> m_pDesc, pHVI -> m_fFlags & DF_HSBModel);
		if (RC != EC_OKAY) break;
		if (pVI -> Style() != pOldVI -> Style()) 
			iResult |= DO_StyleChanged;
		if (((LVisInfo *)pOldVI) -> Width() != ((LVisInfo *)pVI) -> Width())
			iResult |= DO_SizeChanged;
		break;

	case VT_Flaeche:
		RC = ChangeFVisInfo (pW, DBO(), (FVisInfo **)&pVI, pHVI -> m_pDesc, pHVI -> m_fFlags & DF_HSBModel);
		if (RC != EC_OKAY) break;
		if (((FVisInfo *)pVI) -> Type() != ((FVisInfo *)pOldVI) -> Type()) 
			iResult |= DO_StyleChanged;
		if (((FVisInfo *)pVI) -> Width() != ((FVisInfo *)pOldVI) -> Width()) 
			iResult |= DO_SizeChanged;
		if (((FVisInfo *)pVI) -> isOpaque() != ((FVisInfo *)pOldVI) -> isOpaque()) 
			iResult |= DO_OthersChanged;
		if (((FVisInfo *)pVI) -> isBkConture() != ((FVisInfo *)pOldVI) -> isBkConture()) 
			iResult |= DO_OthersChanged;
		if ((COLORREF &)((FVisInfo *)pOldVI) -> SecColor() != 
		    (COLORREF &)((FVisInfo *)pVI) -> SecColor())
			iResult |= DO_SecColorChanged;
		break;

	case VT_Text:
		{
		bool fCustom = pHVI -> m_fFlags & DT_CustomVisualisation;
		
			pHVI -> m_fFlags &= ~DT_CustomVisualisation;
			RC = ChangeTVisInfo (pW, (TVisInfo **)&pVI, pHVI -> m_pDesc, fCustom);
			if (RC != EC_OKAY) break;
			if (pVI -> Style() != pOldVI -> Style()) 
				iResult |= DO_StyleChanged;
			if (((TVisInfo *)pOldVI) -> Size().Width() != ((TVisInfo *)pVI) -> Size().Width() ||
			    ((TVisInfo *)pOldVI) -> Size().Height() != ((TVisInfo *)pVI) -> Size().Height())
				iResult |= DO_SizeChanged;
			if (((TVisInfo *)pOldVI) -> Type() != ((TVisInfo *)pVI) -> Type())
				iResult |= DO_OthersChanged;
			if (((TVisInfo *)pOldVI) -> Rotation() != ((TVisInfo *)pVI) -> Rotation())
				iResult |= DO_OthersChanged;
			if (((TVisInfo *)pOldVI) -> Orientation() != ((TVisInfo *)pVI) -> Orientation())
				iResult |= DO_OthersChanged;
		}
		break;

	case VT_Default:
		break;

	default:
		DELETE (pVI);			// lokale VI freigeben
		DELETE (pOldVI);
		if (fToDeleteWindow) DELETE (pW);
		return EC_OKAY;
	}
	if (fToDeleteWindow) DELETE (pW);

// neue VI mit alter vergleichen und feststellen, was sich geändert hat
	if (RC == EC_OKAY) {
		pVI -> CopyTo (*pHVI -> m_pVI);			// zurückkopieren

		if (pHVI -> m_iVTyp == VT_Default) 
			((DVISINFO *)(pHVI -> m_pVI)) -> m_iDefTypes = 0;
		
		if (pVI -> Priority() != pOldVI -> Priority()) iResult |= DO_PriorityChanged;
		if ((COLORREF &)pVI -> PrimColor() != (COLORREF &)pOldVI -> PrimColor()) iResult |= DO_PrimColorChanged;
		if (strcmp (pVI -> VisName(), pOldVI -> VisName())) iResult |= DO_NameChanged;
	}
		
	DELETE (pVI);				// lokale VI freigeben
	DELETE (pOldVI);

// Status der Änderung hinzufügen
	pHVI -> m_fFlags |= iResult;
	
return RC;
}


// Ändern einer Visinfo in einer Sicht für einen Identifikator ----------------
ErrCode DatenBasisObjekt :: ChangeVisInfo (long lIdent, short iVTyp, 
					   VISINFO &rVI, char *pView, short fBits, bool fForce)
{
VisInfo *pVI = VisInfoFromC (rVI, (VisType)iVTyp);
CTable tId (Idents().IdentTree());
ErrCode RC = EC_OKAY;

	if (tId.Find (&lIdent)) {
	CIdentifikatorLock l(tId);
		
		if (l) 
			RC = ChangeVisInfo (*l, (VisType)iVTyp, pVI, pView, fBits);
	} else {
		if (fForce) 
			RC = SaveVI (pVI, pView, lIdent, (VisType)iVTyp, fBits);
		DELETE (pVI);
	}

return RC;
}


ErrCode DatenBasisObjekt :: ChangeVisInfo (
			CIdentifikator &rId, VisType iVTyp, 
			VisInfo *pVI, char *pView, short fBits)
{
	if (pVI == NULL) return EC_NOMEMORY;

ErrCode RC = EC_OKAY;
long lIdent = rId.Id();		// Identifikator

// Palette korrigieren
	AddNewColorsToPalette (pVI, hPalette);

// neue VisInfo in Sicht abspeichern
	DBASSERT(SaveVI (pVI, pView, lIdent, iVTyp, fBits, rId.isTemp()));

// neue VisInfo einstellen, wenn es keine DefaultInfo ist
	if (pVI -> isA() != VT_Default) {
	VisInfo *poldVI = rId.ChangeVisInfo (pVI, iVTyp);

		if (poldVI) {
			DELETE (poldVI);
		} else {
		// neuer VisualisierungsTyp hinzugekommen
			Idents().PrioTree().AddEntry (rId, pVI);
		}
	} else {
		DELETE (pVI);
	}

// Legende neu anzeigen
	if (pLegende) LegendToRepaint = true;
	
return EC_OKAY;
}

ErrCode DatenBasisObjekt :: SaveVI (VisInfo *pVI, char *pView, long lIdent, 
									VisType iVTyp, short fBits, bool fTemp)
{
char pSichtName[SIGHTMENUITEM +1];
ErrCode RC = EC_OKAY;

	if (!DEX_GetROMode()) {
		if (pView != NULL) {	// Sicht ist gegeben
			TX_ASSERT(TIsValidString(pView));
			strcpy (pSichtName, pView);
		} else			// aktuelle Sicht
			GetActiveSightName (pSichtName, SIGHTMENUITEM +1);

		if (*pSichtName != '\0' && !fTemp) {
		Sicht S (DB(), pSichtName);	// aktuelle/geforderte Sicht

			DBASSERT (S.AddIDtoSight (lIdent, pVI, fBits));

		// in StandardSicht abspeichern, wenn dort dieser ID 
		// nicht vertreten ist
		ResString rsDefault (IDS_DEFAULTVISINFO, 41);

			if (pView == NULL || strcmp (rsDefault, pView)) {
			ErrInstall EI (WC_NOTFOUND);

				if (GetDefaultIDVisInfo (DB(), lIdent, NULL, iVTyp) == WC_NOTFOUND) 
					DBASSERT (AddIDtoDefaultSight (DB(), lIdent, pVI));
			}                                               
		}
	}

return EC_OKAY;
}
				
// Erweitern einer Palette um die in einer VisInfo gegebenen Farben
#if defined(OLDADDNEWCOLORSTOPALETTE) // ======================================
static HPALETTE AddNewColorsToPalette (VisInfo *pVI, HPALETTE hPal) 
{
int numColors, oldNumColors;

// wenn keine alte Palette existiert, dann nichts machen
	if (hPal == NULL)
		return NULL;

	GetObject (hPal, sizeof(int), (LPSTR)&numColors);
	oldNumColors = numColors++;		// PrimColor kommt hinzu
	if (pVI -> isA() == VT_Flaeche)
		numColors++;	// SecColor kommt auch noch hinzu

LOGPALETTE *pPal = (LOGPALETTE *)new char [sizeof(LOGPALETTE) + 
					   numColors*sizeof(PALETTEENTRY)];
	if (pPal == NULL) {
		db_error (EC_NOMEMORY, RC_AddNewColorsToPalette);
		return NULL;
	}

// Palette initialisieren
//	pPal -> palNumEntries = (unsigned short)numColors;
	pPal -> palVersion = PALVERSION;

// alte Palette einlesen und freigeben
	GetPaletteEntries (hPal, 0, oldNumColors, pPal -> palPalEntry);
	DeleteObject (hPal);

// neue Palette bilden
	AddEntryToPalette (pPal, pVI -> PrimColor(), oldNumColors);
	if (pVI -> isA() == VT_Flaeche) 
		AddEntryToPalette (pPal, ((FVisInfo *)pVI) -> SecColor(), oldNumColors);
		
	pPal -> palNumEntries = (unsigned short)oldNumColors;
	hPal = CreatePalette (pPal);

// Speicherfreigeben
	if (pPal) {
		delete (char *)pPal;
		pPal = NULL;
	}

return hPal;
}
#else
inline void ConvertPaletteIndex (HPALETTE hPal, Color &C)
{
	if (hPal && C.Reserved() != 0) {
		GetPaletteEntries (hPal, C.Red(), 1, (PALETTEENTRY *)&C);
		C.Reserved() = 0;
	}
}

inline void ConvertColor (HPALETTE hPal, Color &C)
{
	if (hPal && C.Reserved() == 0) {
	PALETTEENTRY *pCRef = (PALETTEENTRY *)&C;
	long lIndex = PALETTEINDEX(GetNearestPaletteIndex (hPal, *(COLORREF *)pCRef));
	
		C = *(Color *)&lIndex;
	}
}

static bool AddNewColorsToPalette (VisInfo *pVI, HPALETTE hPal)
{
int iNumEntries;

// 1. Größe der Palette festellen
	if (!hPal) return 0;
	GetObject (hPal, sizeof(int), (LPSTR)&iNumEntries);
	if (iNumEntries == 0) return false;

PALETTEENTRY PalEntry[2];
int iNewEntries = iNumEntries;

// 2. allgemeine Farbe testen
Color C = pVI -> PrimColor();
VisType VT = pVI -> isA();

	if (VT == VT_Flaeche || VT == VT_Punkt)
		ConvertPaletteIndex (hPal, C);
	
PALETTEENTRY *pCRef = (PALETTEENTRY *)&C;
int iIndex = GetNearestPaletteIndex (hPal, *(COLORREF *)pCRef);

	GetPaletteEntries (hPal, iIndex, 1, &PalEntry[0]);
	if (*(COLORREF *)pCRef != *(COLORREF *)&PalEntry[0]) {
		iNewEntries++;
		*(COLORREF *)&PalEntry[0] = *(COLORREF *)pCRef;
	}

// 3. wenn FlächenVisInfo vorliegt, Füllfarbe testen
	if (pVI -> isA() ==  VT_Flaeche) {
		C = ((FVisInfo *)pVI) -> SecColor();
		ConvertPaletteIndex (hPal, C);

		pCRef = (PALETTEENTRY *)&C;
		iIndex = GetNearestPaletteIndex (hPal, *(COLORREF *)pCRef);

		GetPaletteEntries (hPal, iIndex, 1, &PalEntry[1]);
		if (*(COLORREF *)pCRef != *(COLORREF *)&PalEntry[1]) {
			*(COLORREF *)&PalEntry[iNewEntries-iNumEntries] = *(COLORREF *)pCRef;
			iNewEntries++;
		}
	}
	else if (pVI -> isA() ==  VT_Punkt) {
	// 4. wenn PunktVisInfo vorliegt, Füllfarbe testen
		C = ((PVisInfo *)pVI) -> SecColor();
		ConvertPaletteIndex (hPal, C);

		pCRef = (PALETTEENTRY *)&C;
		iIndex = GetNearestPaletteIndex (hPal, *(COLORREF *)pCRef);

		GetPaletteEntries (hPal, iIndex, 1, &PalEntry[1]);
		if (*(COLORREF *)pCRef != *(COLORREF *)&PalEntry[1]) {
			*(COLORREF *)&PalEntry[iNewEntries-iNumEntries] = *(COLORREF *)pCRef;
			iNewEntries++;
		}
	}

	TX_ASSERT(iNewEntries <= iNumEntries+2);	// max. 2 neue Einträge

	if (iNewEntries > iNumEntries) {
	// Palette vergrößern
		ResizePalette (hPal, iNewEntries);
		SetPaletteEntries (hPal, iNumEntries, 
				   iNewEntries-iNumEntries, PalEntry);
		return true;
	}

return false;	// Palette wurde nicht erweitert
}
#endif // =====================================================================

