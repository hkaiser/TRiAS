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

#include "visparam.hxx"
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

// lokale Funktionsprototypen -------------------------------------------------
ErrCode ChangePVisInfo (pWindow pW, DatenBasisObjekt &, PVisInfo **pVI, char *CapString, bool fHSB = false, bool fCustom = false);
ErrCode ChangeLVisInfo (pWindow pW, DatenBasisObjekt &, LVisInfo **pVI, char *CapString, bool fHSB = false);
ErrCode ChangeFVisInfo (pWindow pW, DatenBasisObjekt &, FVisInfo **pVI, char *CapString, bool fHSB = false);
ErrCode ChangeTVisInfo (pWindow pW, TVisInfo **pVI, char *CapString, short fCustom = false);

static void ChangeButton (PushButton &B, bool fI, bool fO, uint uiEdit, uint uiNew);

#if defined(OLDADDNEWCOLORSTOPALETTE) // ======================================
static HPALETTE AddNewColorsToPalette (VisInfo *, HPALETTE);
#else
static bool AddNewColorsToPalette (VisInfo *, HPALETTE);
#endif
static VisInfo *MakeNewVI (VisInfo *, ObjTyp);

inline long GetIdentFromEntry (char *pBuffer, int iIdBase)
{
	TX_ASSERT(pBuffer);

return strtoul (pBuffer, NULL, iIdBase);
}

// Funktion, die DialogBox anzeigt und Identifikator auswählt -----------------
ErrCode IrisWind :: ChangeIdVisInfo (long ID, bool iChangeType) 
{
CEierUhr Wait (this);
VisInfoDlg VIDlg (this, DBO(), ID, iChangeType);
//ErrCode RC;

	Wait.Hide();
	VIDlg.Show();	// DialogBox anzeigen und Ident auswählen lassen

return EC_OKAY;
}

// eigentliche Arbeit - Einstellen der Farben entsprechend VisTyp -------------
ErrCode VisInfoDlg :: ChangeIdVisInfo (VisType iVTyp)
{
// entsprechend ObjektTyp dieses ID's VisInfo einstellen lassen
CTable tId (DBO().Idents().IdentTree());
ErrCode RC;
VisInfo *pVI = NULL;

	if (tId.Find (&_ID)) {
	CIdentifikatorLock l(tId);

		if (l) pVI = l -> GetVisInfo (iVTyp);
	}

	if (pVI == NULL) {
	// in dieser Sicht nicht vorhanden
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
short iIndex = IdentList.GetFirstSelected();
char InBuff[61];

	TX_ASSERT(iIndex != -1);	// mindestens ein Ident selektiert

	while (iIndex != -1) {
		IdentList.GetString (InBuff, iIndex, 61);
		IdList.push_back ((ULONG)GetIdentFromEntry (InBuff, m_iIdBase));	// Ident holen
		iIndex = IdentList.GetNextSelected();
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
typedef struct tagFILLIDENTLISTDATA {
	DatenBasisObjekt *m_pDBO;
	VisInfoDlg *m_pVIDlg;
} FILLIDENTLISTDATA;

void VisInfoDlg :: FillEntryList (void)
{
	IdentList.Hide();
	IdentList.Clear();

FILLIDENTLISTDATA FILD;

	FILD.m_pVIDlg = this;		// dieses DialogFenster
	FILD.m_pDBO = &DBO();

	DBO().Idents().IdentTree().Every (FillIdentSelBox, &FILD);
	IdentList.Show();
}


#pragma warning (disable: 4355)

VisInfoDlg :: VisInfoDlg (pWindow pW, DatenBasisObjekt &DBO, long ID, 
			  bool iChangeType) 
	    : DialogWindow (pW, VISPARAMCTRL),
	      IdentList (this, IDL_VISPARAMS),
	      CancelButton (this, IDCANCEL),
	      PButton (this, IDB_VISPUNKT),
	      LButton (this, IDB_VISLINIE),
	      FButton (this, IDB_VISFLAECHE),
	      TButton (this, IDB_VISTEXT),
	      m_rbRGB (this, IDR_RGB),
	      m_rbHSB (this, IDR_HSB),
	      _DBO (DBO)
{
	_ID = ID;
	_IDString = NULL;
	m_fChangeType = iChangeType;
	m_iIdBase = DEX_GetIdBase();

// ListBox mit allen Identifikatoren (dieser Sicht) füllen
	FillEntryList();

// wenn ListBox nicht leer ist, dann ersten Eintrag selektieren, 
// ansonsten vorselektieren
	if (IdentList.GetCount() > 0) {
		if (ID == -1L) {
			IdentList.SetCaretIndex (0);
			IdentList.ChangeSelected (0, On);
			AdjustButtons (0);
		} else {
		char inBuff[20];
		int iIndex = IdentList.FindString (ultoa (ID, inBuff, m_iIdBase));
		
			if (iIndex == -1L) iIndex = 0;
			IdentList.SetCaretIndex (iIndex);
			IdentList.ChangeSelected (iIndex, On);
			AdjustButtons (iIndex);
		}
	} else {
		ChangeButton (PButton, false, false, IDS_VISPUNKT, IDS_VISPUNKTNEU);
		ChangeButton (LButton, false, false, IDS_VISLINIE, IDS_VISLINIENEU);
		ChangeButton (FButton, false, false, IDS_VISFLAECHE, IDS_VISFLAECHENEU);
		ChangeButton (TButton, false, false, IDS_VISTEXT, IDS_VISTEXTNEU);
	}
	
// Farbmodell auswählen
	m_rbRGB.SetState (true);
	m_rbHSB.SetState (false);
}

#pragma warning (default: 4355)

VisInfoDlg :: ~VisInfoDlg (void) 
{
	DELETE (_IDString);
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
void VisInfoDlg :: ButtonClick (ControlEvt e) 
{
	switch ((uint)e.GetControlID ()) {
	case IDB_VISPUNKT:
		ChangeVisEntry (VT_Punkt);
		break;

	case IDB_VISLINIE:
		ChangeVisEntry (VT_Linie);
		break;

	case IDB_VISFLAECHE:
		ChangeVisEntry (VT_Flaeche);
		break;

	case IDB_VISTEXT:
		ChangeVisEntry (VT_Text);
		break;

	case IDCANCEL:
		EndDlg();
		break;
	}
}

// Einstellung für einen Identifikator (P/L/F/T) ------------------------------
void VisInfoDlg :: ChangeVisEntry (VisType iVTyp)
{
short Index = IdentList.GetCaretIndex();
char InBuff[61];

	if (Index == -1) {
		_ID = -1;
		return;
	}
	IdentList.GetString (InBuff, Index, 61);

// Werte des zu verändernden ID's holen
long ID = GetIdentFromEntry (InBuff, m_iIdBase);	// Ident holen

	if (ID != 0L) _ID = ID;
	TX_ASSERT(_ID != -1);

	DELETE (_IDString);

	if (IdentList.GetNoSelected() > 1) {	// mehrere Idents
	ResString SelIds (IDS_SELECTEDIDENTS, 40);
	
		_IDString = new char [60];
		if (_IDString == NULL) {
			db_error (EC_NOMEMORY, RC_VisInfoDlgEnd);
			EndDlg();
		}
		strcpy (_IDString, SelIds);
	} else {
	LPSTR cptr = strrchr (InBuff, ':');
	
		TX_ASSERT(cptr);
	
	LPSTR lpTmp = strrlchr (cptr, ' ');
	ResString resUnkID (IDS_KTUNKNOWNIDENT, 40);
	
		if (lpTmp) *lpTmp = '\0';	// TrimmRight
		if (*++cptr == '\0') 		// KurzText nicht vorhanden
			cptr = (LPSTR)resUnkID.Addr();

		_IDString = new char [strlen(cptr)+20];
		if (_IDString == NULL) {
			db_error (EC_NOMEMORY, RC_VisInfoDlgEnd);
			EndDlg();
		}

		if (m_iIdBase == 10)
			wsprintf (_IDString, "\'%s (%08ld)\'", cptr, _ID);
		else
			wsprintf (_IDString, "\'%s (%08lx)\'", cptr, _ID);
	}

// VisInfo einstellen lassen
	if (ChangeIdVisInfo (iVTyp) == EC_OKAY) {
	// Text richten
		CancelButton.SetText (ResString (IDS_CLOSEBUTTON, 12));
		AdjustButtons (Index);

	// warten, bis Fenster neu gezeichnet ist
//		GetParent() -> RePaint();
		GetParent() -> Update();
	}
}

// Selektion innerhalb der ListBox --------------------------------------------
static void ChangeButton (PushButton &B, bool fI, bool fO, uint uiEdit, uint uiNew)
{
	if (fI) {
	ResString rsEdit (uiEdit, 20);

		B.SetText (rsEdit.Addr());
	} else {
	ResString rsNew (uiNew, 20);

		B.SetText (rsNew.Addr());
	}
	
// nur aktivieren, wenn Objekte in Datenbank sind
	if (fO) B.Enable();
	else	B.Disable();
}


void VisInfoDlg :: ListBoxSel (ControlEvt)
{
	AdjustButtons (IdentList.GetCaretIndex());
}

void VisInfoDlg :: AdjustButtons (short iIndex)
{
	TX_ASSERT(iIndex != -1);

char InBuff[61];

	IdentList.GetString (InBuff, iIndex, 61);

// Werte des zu verändernden ID's holen
long ID = GetIdentFromEntry (InBuff, m_iIdBase);	// Ident holen
CTable t(DBO().Idents().IdentTree());

	if (t.Find (&ID)) {
	CIdentifikatorLock l(t);

		if (l) {
		short fBits = l -> isCustomized();
		short fOTypes = l -> GetOTypes(DBO().DB()) & l -> toPaint();
		
			ChangeButton (PButton, fBits & TPPunkt, fOTypes & TPPunkt, IDS_VISPUNKT, IDS_VISPUNKTNEU);
			ChangeButton (LButton, fBits & TPLinie, fOTypes & TPLinie, IDS_VISLINIE, IDS_VISLINIENEU);
			ChangeButton (FButton, fBits & TPFlaeche, fOTypes & TPFlaeche, IDS_VISFLAECHE, IDS_VISFLAECHENEU);
			ChangeButton (TButton, fBits & TPText, fOTypes & TPText, IDS_VISTEXT, IDS_VISTEXTNEU);
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


bool VisInfoDlg :: AddEntry (CIdentifikator *pId, char *pKT)
{
long lIdent = pId -> Id();
char OutBuff[61];

	if (m_iIdBase == 10) 
		wsprintf (OutBuff, "%08ld:%-45s", lIdent, pKT);
	else
		wsprintf (OutBuff, "%08lx:%-45s", lIdent, pKT);

// in ListBox einfügen, gegebenenfalls sofort selektieren
int newIndex = IdentList.AddString (OutBuff);

	if (_ID != -1L && _ID == lIdent) {
		IdentList.SetCaretIndex (newIndex);
		IdentList.ChangeSelected (newIndex , On);
	}

return true;
}


bool EXPORTTRIAS FillIdentSelBox (void *pObj, void *pData) 
{
	TX_ASSERT(pData);

FILLIDENTLISTDATA *pFILD = (FILLIDENTLISTDATA *)pData;

	TX_ASSERT(pFILD -> m_pVIDlg);
	TX_ASSERT(pFILD -> m_pDBO);

CIdentifikator *pId = (CIdentifikator *)pObj;

	if (pId -> toPaint()) {		// nur diese Sicht
	PBD_Ident Id (&(pFILD -> m_pDBO -> PbdDB()), pId -> Id());  // KurzText lesen

		pFILD -> m_pVIDlg -> AddEntry (pId, Id.GetKurzText());
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

