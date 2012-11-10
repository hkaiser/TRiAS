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

#include <undoguid.h>				// GUID
#include <iunredo.hxx>				// Undo-Interface's

#include <owncombo.hxx>
#include <efont.hxx>

#include "strings.h"
#include "clbmpobj.hxx"
#include "prntabrt.hxx"
#include "printer.hxx"
#include "dcolor.hxx"
#include "palrect.hxx"
#include "colorbox.hxx"
#include "palwind.hxx"
#include "Legdinfo.hxx"

#include "ExtMain3.hxx"
#include "vispara3.hxx"
//#include "objtype.hxx"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
//
#define CNT_MASSTAB		16

#define LOWER_COLUMN	3
#define UPPER_COLUMN	4

///////////////////////////////////////////////////////////////////////////////
//
extern class CLegendeClientWindow *pLegende;
extern bool LegendToRepaint;
extern bool g_fHSB;				// HSB für Farbeinstellung verwenden
extern HPALETTE hPalette;

///////////////////////////////////////////////////////////////////////////////
// globale Funktionen 
short VTypToBits (VisType iVTyp);
VisType BitsToVTyp (int iOTypes);
long myatol (const char *lpStr);			// atol für Maßstab (mit Zwischenpunkten)

static long RetrieveScale (LPCSTR pcScale);
static string FormatScale (long M);

///////////////////////////////////////////////////////////////////////////////
// lokale Funktionsprototypen 
ErrCode ChangePVisInfo (pWindow pW, DatenBasisObjekt &, PVisInfo **pVI, char *CapString, bool fHSB = false, bool fCustom = false);
ErrCode ChangeLVisInfo (pWindow pW, DatenBasisObjekt &, LVisInfo **pVI, char *CapString, bool fHSB = false);
ErrCode ChangeFVisInfo (pWindow pW, DatenBasisObjekt &, FVisInfo **pVI, char *CapString, bool fHSB = false);
ErrCode ChangeTVisInfo (pWindow pW, TVisInfo **pVI, char *CapString, short fCustom = false);

_TRIAS02_ENTRY BOOL EXPORT02 ExpandPalette (HPALETTE hPal, class VisInfo *pVI);
static VisInfo *MakeNewVI (VisInfo *, ObjTyp);

// Funktion, die DialogBox anzeigt und Identifikator auswählt -----------------
ErrCode IrisWind::ChangeIdVisInfo (long ID, bool) 
{
// Dialogfenster generieren
CEierUhr Wait (this);
VisInfoDlg VIDlg (this);

// eigene Page hinzufügen
CVisInfoPage PPage (DBO(), ID, VT_Punkt, ResString (IDS_OBJTYPPUNKT, 16));
CVisInfoPage LPage (DBO(), ID, VT_Linie, ResString (IDS_OBJTYPLINIE, 16));
CVisInfoPage FPage (DBO(), ID, VT_Flaeche, ResString (IDS_OBJTYPFLAECHE, 16));
CVisInfoPage TPage (DBO(), ID, VT_Text, ResString (IDS_OBJTYPTEXT, 16), false);

	VIDlg.AddPage (&FPage);			// eigene Pages lassen
	VIDlg.AddPage (&LPage);
	VIDlg.AddPage (&PPage);
	VIDlg.AddPage (&TPage);

//	LoadPages (VIDlg, g_cbDocKey, g_cbDocSubKey);			// zusätzliche Pages aus Registry laden

	Wait.Hide();
	VIDlg.Show();	// DialogBox anzeigen und Ident/Vistyp auswählen lassen

ErrCode ecResult = VIDlg.Result() ? EC_OKAY : WC_RETURN;

	if (EC_OKAY == ecResult) {
		SetShouldRedraw();
		DEX_RePaint();	// neu zeichnen
	}
	return ecResult;
}

///////////////////////////////////////////////////////////////////////////////
// PropertySheet für Ident/Vistypauswahl
VisInfoDlg::VisInfoDlg (pWindow pWnd)
		   : CPropertySheet (ResString (IDS_VISPARAMCAP, 64), pWnd/*, PSH_NOAPPLYNOW*/)
{
}

VisInfoDlg::~VisInfoDlg (void)
{
}

///////////////////////////////////////////////////////////////////////////////
// eine Page (Punkte/Linien/Flächen/Texte)
// eigentliche Arbeit - Einstellen der Farben entsprechend VisTyp -------------
typedef list<ULONG>	CListULONG;

static UINT GetUndoResID (VisType iVTyp)
{
	switch (iVTyp){
	case VT_Punkt:		return IDS_UNDOVISINFOPUNKT;
	case VT_Linie:		return IDS_UNDOVISINFOLINIE;
	case VT_Flaeche:	return IDS_UNDOVISINFOFLAECHE;
	case VT_Text:		return IDS_UNDOVISINFOTEXT;
	default:
		break;
	}

return IDS_UNDOVISINFODEFAULT;
}

ErrCode CVisInfoPage::ChangeIdVisInfo (VisType iVTyp)
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
CListULONG IdList;
long lIdent = 0L;
short iOTyp = 0;

	if (m_lvIdentList -> GetFirstIdent (lIdent, iOTyp)) {
		do {
			IdList.push_back ((ULONG)lIdent);
		} while (m_lvIdentList -> GetNextIdent(lIdent, iOTyp));
	}

bool fHSB = m_rbHSB.GetState();
#if defined(_FORCE_LEGACY_CODE)
bool fNewDB = (DEX_GetDBVersion() >= VERSION0500000B) ? true : false;
#else
bool fNewDB = true;
#endif // defined(_FORCE_LEGACY_CODE)

	switch (iVTyp) {
	case VT_Punkt:
		RC = ChangePVisInfo (this, DBO(), (PVisInfo **)&pVI, IDString(), fHSB, fNewDB);
		break;

	case VT_Linie:	
		RC = ChangeLVisInfo (this, DBO(), (LVisInfo **)&pVI, IDString(), fHSB);
		break;

	case VT_Flaeche:
		RC = ChangeFVisInfo (this, DBO(), (FVisInfo **)&pVI, IDString(), fHSB);
		break;

	case VT_Text:
		RC = ChangeTVisInfo (this, (TVisInfo **)&pVI, IDString(), fNewDB);
		break;

	case VT_Default:
	default:
		DELETE_OBJ (pVI);
		return EC_OKAY;
	}

	if (RC != EC_OKAY) {
		DELETE_OBJ (pVI);
		return RC;	// Fehler oder abbrechen
	}

	TX_ASSERT(IdList.size() > 0);	// mindestens einer zu bearbeiten

// jetzt alle zu behandelnden Idents auch behandeln
CEierUhr Wait (this);		// EierUhr anzeigen

// UndoLevel anlegen
HRESULT hr = NOERROR;
ResString resUndo (GetUndoResID(iVTyp), 128);
LPUNDOREDOVISINFO pIUndo = NULL;

	DEX_BeginUndoLevel (resUndo.Addr());

	for (CListULONG::iterator it = IdList.begin(); it != IdList.end(); it++) {
	ULONG lIdent = *it;

		if (tId.Find (&lIdent)) {
		CIdentifikatorLock l(tId);
		
			if (l) {
				TX_ASSERT(NULL != (CIdentifikator *)l);
				if (!l) continue;

			// Undo-Objekt initialisieren
			int iPrio = l -> Priority (iVTyp);
			HANDLEVISINFO *pHVI = ctHANDLEVISINFO (iVTyp);

				if (NULL != pHVI) {
					pHVI -> m_lIdent = l -> Id();
					pHVI -> m_iVTyp = iVTyp;
					pHVI -> m_fFlags = DO_VisInfoChanged;
					pVI -> CopyTo (*(pHVI -> m_pVI));
					pHVI -> m_pVI -> m_Priority = iPrio;

					pIUndo = NULL;
					hr = UndoCreateInstance (IID_IUndoRedoVisInfo, (LPVOID *)&pIUndo);
					if (SUCCEEDED(hr) && NOERROR == pIUndo -> Init (pHVI, NULL)) 
						DEX_AddUndoRedo (pIUndo);

					if (pIUndo) pIUndo -> Release();
					dtHANDLEVISINFO (pHVI);
				}

			// alte Priorität besorgen und VisInfo wegschreiben
			VisInfo *pNewVI = (VisInfo *)pVI -> Copy();

				pNewVI -> Priority() = iPrio;
				RC = DBO().ChangeVisInfo (*l, iVTyp, pNewVI);
				if (EC_OKAY != RC) {
					DEX_CancelUndoLevel (false);
					return RC;
				}
			}
		}
	}

	DEX_EndUndoLevel();
	DELETE_OBJ (pVI);		// Master wieder beseitigen

return EC_OKAY;
}

// DialogBox, die es erlaubt einen Identifikator auszuwählen ------------------
static DWORD OvlFromVTyp (VisType rgVTyp)
{
	switch (rgVTyp) {
	case VT_Punkt:		return 1;
	case VT_Linie:		return 2;
	case VT_Flaeche:	return 3;
	case VT_Text:		return 4;
	default:
		TX_ASSERT(false);
		break;
	}
	return 0;		// don't know
}

DWORD __stdcall isCustomized (INT_PTR lIdent, DWORD dwData)
{
	TX_ASSERT(0L != dwData);

CVisInfoPage *pPage = reinterpret_cast<CVisInfoPage *>(dwData);
CTable t(pPage -> DBO().Idents().IdentTree());

	if (t.Find (&lIdent)) {
	CIdentifikatorLock l(t);

		if (l) {
		short fBits = l -> isCustomized();
		short iOTyp = VTypToBits (pPage -> VTyp());

			if (fBits & iOTyp) 
				return 0;	// kein Overlay

		// hier durchfallen
		// ...
		}
	}

return OvlFromVTyp(pPage -> VTyp());
}

#pragma warning (disable: 4355)

CVisInfoPage::CVisInfoPage (DatenBasisObjekt &rDBO, long ID, 
	VisType rgVTyp, LPCSTR pcCaption, bool fRGBHSB)
	    : CPropertyPage (IDD_VISPARAMCTRLPAGE, pcCaption),
	      m_lvIdentList (this, IDL_VISPARAMS),
	      m_pbDefine (this, IDC_DEFINE),
		  m_pbSetScaleUpper (this, IDC_SETSCALE_UPPER),
		  m_pbSetScaleLower (this, IDC_SETSCALE_LOWER),
	      m_rbRGB (this, IDR_RGB), m_rbHSB (this, IDR_HSB),
		  m_gbRGBHSB (this, IDC_RGBHSB_GROUP),
	      m_rDBO (rDBO), m_rgVTyp(rgVTyp), m_fRGBHSB(fRGBHSB)
{
	m_lID = ID;
	m_pIDString = NULL;

	m_fI = true;
	m_fO = true;

	m_iColUpper = -1;
	m_iColLower = -1;
}

#pragma warning (default: 4355)

CVisInfoPage::~CVisInfoPage (void) 
{
	DELETE_OBJ (m_pIDString);
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler ---------------------------------------------------------------
void CVisInfoPage::ButtonClick (ControlEvt e) 
{
	switch ((uint)e.GetControlID ()) {
	case IDC_DEFINE:
		ChangeVisEntry (m_rgVTyp);
		break;

	case IDC_SETSCALE_UPPER:
		{
		int iRow = m_lvIdentList.GetLastItemFocus();

			if (iRow >= 0)
				m_lvIdentList.PostEvent (WM_SHOWCOMBO, iRow, m_iColUpper);
		}
		break;

	case IDC_SETSCALE_LOWER:
		{
		int iRow = m_lvIdentList.GetLastItemFocus();

			if (iRow >= 0)
				m_lvIdentList.PostEvent (WM_SHOWCOMBO, iRow, m_iColLower);
		}
		break;
	}
}

void CVisInfoPage::OnItemChanged (NotifyEvt e)
{
NM_LISTVIEW *pNfyData = reinterpret_cast<NM_LISTVIEW *>(e.GetNotifyInfo());

	if (!(pNfyData -> uChanged & LVIF_STATE))
		return;		// Status nicht geändert

// Focus künstlich auf den letzten selektierten Eintrag nachführen
	if (pNfyData -> uNewState & LVIS_SELECTED) 
	{
		m_lvIdentList -> SelectItemFocus (pNfyData -> iItem, true);
	}

// Selektion erhalten/verloren
	if (pNfyData -> uOldState & LVIS_SELECTED ||
		pNfyData -> uNewState & LVIS_SELECTED)
	{
		AdjustButton (m_lvIdentList -> GetItemFocus());
	}
}

// HilfeRoutine ---------------------------------------------------------------
void CVisInfoPage::HelpRequest (HelpRequestEvt e)
{
const HELPINFO *pHI = e.GetHelpInfo();

	TX_ASSERT(pHI);
}

// Initialiserung dieser Page -------------------------------------------------
void CVisInfoPage::WindowInit (Event)
{
CEierUhr Wait (this);

// Controls initialisieren
	m_pbDefine.FInit();
	m_pbSetScaleUpper.FInit();
	m_pbSetScaleLower.FInit();
	m_rbRGB.FInit();
	m_rbHSB.FInit();
	m_gbRGBHSB.FInit();

	if (!m_fRGBHSB) {
		m_rbRGB.Hide();
		m_rbHSB.Hide();
		m_gbRGBHSB.Hide();
	}

	m_lvIdentList.FInit();

//DWORD dwStyle = LVS_REPORT | LVS_OWNERDRAWFIXED |/* LVS_EDITLABELS | */
//				LVS_SORTASCENDING | LVS_SHAREIMAGELISTS | LVS_NOSORTHEADER |
//				WS_BORDER | WS_TABSTOP | LVS_SHOWSELALWAYS;
	
//	m_lvIdentList.SetStyle (dwStyle);

// ListBox mit allen Identifikatoren (dieser Sicht) füllen
DWORD iBits = VTypToBits(m_rgVTyp) | EnumVirtualData;		// virtuelle Objektklassen berücksichtigen
DWORD dwMode = SELIDMODE_SINGLETYPE;

	if (DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) > 1) 
		dwMode |= SELIDMODE_SHOWCONNECTIONS;
	m_lvIdentList -> InitControl (iBits, dwMode, isCustomized, CmpEntries, reinterpret_cast<DWORD>(this));

// new for 'Nashville' (#HK960823)
#if defined(ListView_GetExtendedListViewStyle)
	if (IsWin40()) {
	DWORD dwStyleEx = m_lvIdentList -> GetExtendedStyle();

		m_lvIdentList -> SetExtendedStyle (dwStyleEx | LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP);
	}
#endif

// Maßstabsabhängige Visualisierung
	InitScaleData();
	m_lvIdentList -> FitColumn();

// wenn ListBox nicht leer ist, dann ersten Eintrag selektieren, 
// ansonsten vorselektieren
	ChangeButton (false, false);

	if (m_lvIdentList -> GetItemCount() > 0) {
		if (m_lID == -1L) {
			m_lvIdentList -> SelectItem (0, true);
			m_lvIdentList -> SelectItemFocus (0, true);
			AdjustButton (0);
		} else {
		int iIndex = m_lvIdentList -> SelectIdent (m_lID, iBits, true);

			m_lvIdentList -> SelectItemFocus (iIndex);
			AdjustButton (iIndex);
		}
	}
	
	AdjustHSB (g_fHSB);
}

#if defined(_FORCE_LEGACY_CODE)
///////////////////////////////////////////////////////////////////////////////
//
BOOL CVisInfoPage::DrawEntireItem (DrawItemEvt e)
{
	if (IDL_VISPARAMS == e.GetCtrlID())
		return m_lvIdentList.DrawEntireItem (e);
	return false;
}

BOOL CVisInfoPage::DrawItemFocus (DrawItemEvt e)
{
	if (IDL_VISPARAMS == e.GetCtrlID())
		return m_lvIdentList.DrawItemFocus (e);
	return false;
}

BOOL CVisInfoPage::DrawItemSelect (DrawItemEvt e)
{
	if (IDL_VISPARAMS == e.GetCtrlID())
		return m_lvIdentList.DrawItemSelect (e);
	return false;
}
#endif // defined(_FORCE_LEGACY_CODE)

LRESULT CVisInfoPage::Dispatch (Event e)
{
	switch (e.Msg()) {
	case WM_NOTIFY:
		if (OnNotify ((NotifyEvt &)e))
			return true;
		break;
	}
	return CPropertyPage::Dispatch (e);
}

bool CVisInfoPage::OnNotify (NotifyEvt e)
{
NMHDR *pNMHDR = e.GetNotifyInfo();
LRESULT lResult = false;

	if (LVN_ENDLABELEDIT == pNMHDR -> code) {
		m_lvIdentList.OnEndLabelEdit (pNMHDR, &lResult);
		SetWindowLong (Handle(API_WINDOW_HWND), DWL_MSGRESULT, lResult);
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//
bool CVisInfoPage::InitScaleData (void)
{
int iCols = m_lvIdentList -> GetColumnCount();

	m_iColUpper = UPPER_COLUMN;
	m_iColLower = LOWER_COLUMN;
	if (DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) > 1) {
		m_iColUpper++;
		m_iColLower++;
	}

	m_lvIdentList.SetColumns (m_iColUpper, m_iColLower);

long lIdent = 0;
short iDummy = 0;
int iIndex = m_lvIdentList -> GetFirstIdentInList (lIdent, iDummy);

	if (-1 == iIndex) 
		return false;

long lUpper = 0, lLower = 0;
char cbBuffer[_MAX_PATH];

	if (NULL == DEX_GetActiveSight(cbBuffer))
		return false;

	do {
		TX_ASSERT(BitsToVTyp(iDummy) == m_rgVTyp);
		if (DBO().RetrieveIdentScaleData (cbBuffer, lIdent, m_rgVTyp, &lUpper, &lLower))
			InitIdentScaleData (iIndex, lUpper, lLower);		// nur, wenn Mastabsdaten existieren

	// der nächste bitte
		iIndex = m_lvIdentList -> GetNextIdentInList (lIdent, iDummy);
	} while (-1 != iIndex);

	return true;
}

///////////////////////////////////////////////////////////////////////////////
//
typedef struct tagSCALEVIEWTEXTS {
	UINT uiHeaderKey;		// ResourceID des HeaderEintrages
	UINT uiViewKText;		// ResourceID des Kurztextes für Sichtmerkmal
} SCALEVIEWTEXTS;

const SCALEVIEWTEXTS s_TextIDs[] = {
	{ IDS_P_SCALEVIEWMCODE, IDS_P_SCALEVIEWMCODE_KT },		// VT_Punkt
	{ IDS_L_SCALEVIEWMCODE, IDS_L_SCALEVIEWMCODE_KT },		// VT_Linie
	{ IDS_A_SCALEVIEWMCODE, IDS_A_SCALEVIEWMCODE_KT },		// VT_Flaeche
	{ 0, 0 },												// VT_Default
	{ IDS_T_SCALEVIEWMCODE, IDS_T_SCALEVIEWMCODE_KT, },		// VT_Text
};

bool DatenBasisObjekt::RetrieveIdentScaleData (
	LPCSTR pcView, long lIdent, VisType rgVTyp, long *plUpper, long *plLower)
{
// Maßstabsbereich für alle Fälle rücksetzen
	TX_ASSERT(NULL != plUpper && NULL != plLower);
	*plUpper = 0;
	*plLower = 0;

// aktuelle Sicht besorgen
char cbView[MAXVIEWNAMESIZE+1] = { '\0' };

	if (!GetActiveSightName (cbView, sizeof(cbView)) && NULL == pcView) 
		return false;		// keine aktive Sicht und keine Ansicht gegeben

char cbBuffer[_MAX_PATH];
long lMCode = -1;

	if (NULL == pcView || !strcmp (pcView, cbView)) {
	// Sichtbezogenes Identifikatormerkmal für aktuelle Ansicht sicherstellen
		if (-1L == m_lScaleMCode[rgVTyp])	// bereits versucht und nicht vorhanden
			return false;

		if (0L == m_lScaleMCode[rgVTyp]) {	// noch nie versucht
			TX_ASSERT(rgVTyp != VT_Default);

		long lVMCode = GetHeaderMCode (false, s_TextIDs[rgVTyp].uiHeaderKey);

			if (-1L == lVMCode)
				return false;

		// Merkmal an der Ansicht lesen
			m_lScaleMCode[rgVTyp] = GetIdentMCodeView (false, pcView, lVMCode);
			if (-1L == m_lScaleMCode[rgVTyp]) 
				return false;
		}
		lMCode = m_lScaleMCode[rgVTyp];

	} else {
	// Sichtbezogenes Identifikatormerkmal für eine andere Ansicht sicherstellen
	long lVMCode = GetHeaderMCode (false, s_TextIDs[rgVTyp].uiHeaderKey, pcView);

		if (-1L == lVMCode)
			return false;

	// Merkmal an der Ansicht lesen
		lMCode = GetIdentMCodeView (false, pcView, lVMCode);
		if (-1L == lMCode) 
			return false;
	}

// Merkmal am Ident lesen
	TX_ASSERT(-1 != lMCode);
	if (!ReadTextMerkmal (TT_Identifikator, lIdent, lMCode, cbBuffer, _MAX_PATH, pcView))
		return false;

// Masstäbe stehen als Strings, Komma getrennt
	TX_ASSERT(NULL != plUpper);
	TX_ASSERT(NULL != plLower);

char *pNext = NULL;

	*plUpper = strtol (cbBuffer, &pNext, 10);
	TX_ASSERT(',' == *pNext);		// die zwei Zahlen sind durch Komma getrennt
	*plLower = strtol (pNext+1, NULL, 10);

// wenn einer gegeben ist, dann ist alles ok
	if ((0 < *plUpper) || (0 < *plLower))
		return true;

// irgend ein Fehler
	TX_ASSERT((0 < *plUpper) || (0 < *plLower));
	WriteTextMerkmal (TT_Identifikator, lIdent, lMCode, NULL, 0, pcView);	// löschen

	return false;		// nichts gefunden
}

bool DatenBasisObjekt::SetIdentScaleData (
	LPCSTR pcView, long lIdent, VisType rgVTyp, long lUpper, long lLower)
{
// aktuelle Sicht besorgen
char cbView[MAXVIEWNAMESIZE+1] = { '\0' };

	if (!GetActiveSightName (cbView, sizeof(cbView)) && NULL == pcView) 
		return false;		// keine aktive Sicht und keine Ansicht gegeben

long lMCode = -1;

	if (NULL == pcView || !strcmp (pcView, cbView)) {
	// Sichtbezogenes Identifikatormerkmal für aktuelle Ansicht sicherstellen
		if (-1L == m_lScaleMCode[rgVTyp])	// bereits versucht und nicht vorhanden
			return false;

		if (0L == m_lScaleMCode[rgVTyp]) {	// noch nie versucht
			TX_ASSERT(rgVTyp != VT_Default);

		long lVMCode = GetHeaderMCode (
				true, s_TextIDs[rgVTyp].uiHeaderKey, pcView,
				s_TextIDs[rgVTyp].uiHeaderKey, s_TextIDs[rgVTyp].uiHeaderKey);

			if (-1 == lVMCode)
				return false;

			m_lScaleMCode[rgVTyp] = GetIdentMCodeView (true, pcView, lVMCode,
				s_TextIDs[rgVTyp].uiViewKText, s_TextIDs[rgVTyp].uiViewKText);

			if (-1L == m_lScaleMCode[rgVTyp]) 
				return false;
		}
		lMCode = m_lScaleMCode[rgVTyp];

	} else {
	// Sichtbezogenes Identifikatormerkmal für eine andere Ansicht sicherstellen
	long lVMCode = GetHeaderMCode (false, s_TextIDs[rgVTyp].uiHeaderKey, pcView);

		if (-1L == lVMCode)
			return false;

	// Merkmal an der Ansicht lesen
		lMCode = GetIdentMCodeView (false, pcView, lVMCode);
		if (-1L == lMCode) 
			return false;
	}

	TX_ASSERT(-1 != lMCode);
	if (0 == lUpper && 0 == lLower) 	// evtl. vorherige Einstellungen löschen
		return WriteTextMerkmal (TT_Identifikator, lIdent, lMCode, NULL, 0, pcView);

// jetzt Merkmal an Ident schreiben
char cbBuffer[64];

	wsprintf (cbBuffer, "%ld,%ld", lUpper, lLower);
	return WriteTextMerkmal (TT_Identifikator, lIdent, lMCode, cbBuffer, 0, pcView);
}

///////////////////////////////////////////////////////////////////////////////
// Maßstab formatieren
static string FormatScale (long M)
{
string str;		// = ResString (IDS_NOSCALELIMIT, 20));

	if (0 == M) return str;		// kein Text, wenn kein Maßstab

char cbBuffer[64];

	if (M < 0) {
		TX_ASSERT(M >= 0);
		M = -M;
	}

	if (M >= 1000000L) {
	int iMill = (int)(M / 1000000L);
	int iTaus = (int)((M % 1000000L) / 1000L);
	int iEin = (int)(M % 1000L);

		wsprintf (cbBuffer, TEXT("1:%d.%03d.%03d"), iMill, iTaus, iEin);
	} else if (M >= 1000L) {
	int iTaus = (int)(M / 1000L);
	int iEin = (int)(M % 1000L);

		wsprintf (cbBuffer, TEXT("1:%d.%03d"), iTaus, iEin);
	} else {
		wsprintf (cbBuffer, TEXT("1:%ld"), M);
	}

	str = cbBuffer;
	return str;
}

static long RetrieveScale (LPCSTR pcScale)
{
	TX_ASSERT(NULL != pcScale);

int iPrefix = strlen(g_cbScalePrefix);

	if (0 < strlen(pcScale))
		return myatol (pcScale + iPrefix);

	return 0L;
}

bool CVisInfoPage::InitIdentScaleData (int iIndex, long lUpper, long lLower)
{
	TX_ASSERT(-1 != m_iColUpper);
	TX_ASSERT(-1 != m_iColLower);
	TX_ASSERT(-1 != iIndex);

LV_ITEM lvi;
string str (FormatScale (lUpper));

	memset (&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.pszText = (char *)str.c_str();
	lvi.iItem = iIndex;
	lvi.iSubItem = m_iColUpper;
	m_lvIdentList -> SetItem (&lvi);

	str = FormatScale (lLower);
	memset (&lvi, 0, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT;
	lvi.pszText = (char *)str.c_str();
	lvi.iItem = iIndex;
	lvi.iSubItem = m_iColLower;
	m_lvIdentList -> SetItem (&lvi);

	return true;
}

bool CVisInfoPage::GetIdentScaleData (int iIndex, long &rlUpper, long &rlLower)
{
	TX_ASSERT(-1 != iIndex);

string strUpper (m_lvIdentList -> GetItemText (iIndex, m_iColUpper));
string strLower (m_lvIdentList -> GetItemText (iIndex, m_iColLower));

	if (0 == strUpper.length() && 0 == strLower.length()) {
		rlUpper = 0L;
		rlLower = 0L;
		return true;		// keine Angaben
	}

	rlUpper = RetrieveScale (strUpper.c_str());
	rlLower = RetrieveScale (strLower.c_str());

	return true;
}

///////////////////////////////////////////////////////////////////////////////
//
BOOL CVisInfoPage::OnOK (NotifyEvt)
{
	if (m_lvIdentList.IsScaleDirty()) {
	// alle Maßstabsbereiche wegschreiben
	long lIdent = 0L;
	short iOTypes = 0L;
	int iIndex = m_lvIdentList -> GetFirstIdentInList (lIdent, iOTypes);
	char cbBuffer[_MAX_PATH];

		if (NULL == DEX_GetActiveSight(cbBuffer))
			return false;

		DBO().ResetIdentScaleMCodes();
		while (-1 != iIndex) {
		long lUpper = 0L, lLower = 0L;
		
			if (GetIdentScaleData (iIndex, lUpper, lLower))
				DBO().SetIdentScaleData (cbBuffer, lIdent, BitsToVTyp(iOTypes), lUpper, lLower);

			iIndex = m_lvIdentList -> GetNextIdentInList (lIdent, iOTypes);
		}
	}
	return false;	// always allow operation
}

int CVisInfoPage::OnSetActive (NotifyEvt)
{
	AdjustHSB (g_fHSB);
	return 0;
}

BOOL CVisInfoPage::OnKillActive (NotifyEvt)
{
	g_fHSB = m_rbHSB.GetState();
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//
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

// Farbmodell auswählen -------------------------------------------------------
void CVisInfoPage::AdjustHSB (bool fHSB)
{
	if (m_fRGBHSB) {
		m_rbRGB.SetState (!fHSB);
		m_rbHSB.SetState (fHSB);
	}
}

// Einstellung für einen Identifikator (P/L/F/T) ------------------------------
void CVisInfoPage::ChangeVisEntry (VisType iVTyp)
{
short iIndex = m_lvIdentList -> GetItemFocus();

	if (iIndex == -1) {
		m_lID = -1;
		return;
	}

// Werte des zu verändernden ID's holen
long ID = 0L;
short iOTyp;

	if (m_lvIdentList -> DecodeEntry (iIndex, ID, iOTyp))		// Ident holen
		m_lID = ID;
	
	TX_ASSERT(m_lID != -1);

	DELETE_OBJ (m_pIDString);

	if (m_lvIdentList -> GetSelectedCount() > 1) {	// mehrere Idents
	ResString SelIds (IDS_SELECTEDIDENTS, 40);
	
		m_pIDString = new char [_MAX_PATH];
		if (m_pIDString == NULL) {
			db_error (EC_NOMEMORY, RC_VisInfoDlgEnd);
			EndDlg();
		}
		strcpy (m_pIDString, SelIds);
	} else {
	char cbInBuff[64];
	char *cptr = cbInBuff;
	ResString resUnkID (IDS_KTUNKNOWNIDENT, 40);
	
		if (!m_lvIdentList -> GetDescription (iIndex, cbInBuff, sizeof(cbInBuff)))
			cptr = (LPSTR)resUnkID.Addr();	 		// KurzText nicht vorhanden

		m_pIDString = new char [strlen(cptr)+_MAX_PATH];
		if (m_pIDString == NULL) {
			db_error (EC_NOMEMORY, RC_VisInfoDlgEnd);
			EndDlg();
		}

	char cbCaption[32];
	char cbBuffer[80];

		GetCaption (cbCaption, sizeof(cbCaption));
		ClassFromIdent (m_lID, cbBuffer, sizeof(cbBuffer));
		wsprintf (m_pIDString, "%s \'%s (%s)\'", cbCaption, cptr, cbBuffer);
	}

// VisInfo einstellen lassen
	if (ChangeIdVisInfo (iVTyp) == EC_OKAY) {
	// Text richten
		AdjustButton (iIndex);
		CancelToClose();

	// warten, bis Fenster neu gezeichnet ist
		GetParent() -> Update();
	}
}

// Selektion innerhalb der ListBox --------------------------------------------
void CVisInfoPage::ChangeButton (bool fI, bool fO)
{
	m_pbSetScaleUpper.Enable();
	m_pbSetScaleLower.Enable();

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
		if (fO) {
			m_pbDefine.Enable();
		} else {
			m_pbDefine.Disable();
			m_pbSetScaleUpper.Disable();
			m_pbSetScaleLower.Disable();
		}
		m_fO = fO;
	}
}

///////////////////////////////////////////////////////////////////////////////
// sonstige Member
void CVisInfoPage::AdjustButton (short iIndex)
{
	if (-1 == iIndex) return;

// Werte des zu verändernden ID's holen
long ID = 0L;
short iSelOTyp;

	if (m_lvIdentList -> DecodeEntry (iIndex, ID, iSelOTyp)) {	// Ident holen
	CTable t(DBO().Idents().IdentTree());

		if (t.Find (&ID)) {
		CIdentifikatorLock l(t);

			if (l) {
			short fBits = l -> isCustomized();
			short fOTypes = l -> InitOTypes() & l -> toPaint();
			short iOTyp = VTypToBits (m_rgVTyp);

				ChangeButton ((fBits & iOTyp) ? true : false, (fOTypes & iOTyp) ? true : false);
				m_lvIdentList -> UpdateImage (iIndex);
			}
		}
	}
}

// Ein Eintrag wurde aus der Liste gelöscht -----------------------------------
void CVisInfoPage::OnDeleteItem (NotifyEvt e)
{
NM_LISTVIEW *pNLV = reinterpret_cast<NM_LISTVIEW *>(e.GetNotifyInfo());

	if (0 == pNLV -> iSubItem)	// ItemData freigeben
		m_lvIdentList -> OnDeleteItem (pNLV);
}

void CVisInfoPage::OnDeleteAllItems (NotifyEvt)
{
	m_lvIdentList -> OnDeleteAllItems();
}

///////////////////////////////////////////////////////////////////////////////
// lokale Funktionen 
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
#if !defined(WIN16)
		, fCustom
#endif // WIN16
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
DoublePair dimD;
Dimension locDotsPerMM (GetDotsPerMM (NULL, &dimD));
CoOrd PtX = (CoOrd)(dimD.Width() * (double)((*pVI) -> Size().Width()) * 0.3176 + 0.5);
CoOrd PtY = (CoOrd)(dimD.Height() * (double)((*pVI) -> Size().Height()) * 0.3176 + 0.5);
pFont pF = MakeFont (*pVI, Dimension (PtX, PtY));

	if (pF == NULL) return EC_NOMEMORY;

ActPrinterPars ActPPDev;	// aktiver Drucker

// bei Erfolg ist *pVI bereits geändert
	if (!((ExtFont *)pF) -> ChooseFont (hWnd, lpnewCaption, pVI, ActPPDev, fCustom)) {
		DELETE_OBJ (pF);
		return WC_RETURN;
	}

// Fontgröße wieder in Punkt umrechnen
	(*pVI) -> Size().Width() = 
				(CoOrd)(((double)((*pVI) -> Size().Width()) / (dimD.Width() * 0.3176)) + 0.5);
	if ((*pVI) -> Size().Height() > 0) {
		(*pVI) -> Size().Height() = 
				(CoOrd)(((double)((*pVI) -> Size().Height()) / (dimD.Height() * 0.3176)) + 0.5);
	} else {
		(*pVI) -> Size().Height() = 
				(CoOrd)(((double)((*pVI) -> Size().Height()) / (dimD.Height() * 0.3176)) - 0.5);
	}

// Speicher freigeben
	DELETE_OBJ (pF);
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

	case OT_LABEL:
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
	DELETE_OBJ (pVI);

return pNewVI;
}


// Externe Schnittstelle zur Einstellung einer VisInfo ------------------------
short IrisWind::ChangeVisInfoExt (HANDLEVISINFO *pHVI)
{
ErrCode RC = EC_OKAY;
VisInfo *pVI = VisInfoFromC (*pHVI -> m_pVI, (VisType)pHVI -> m_iVTyp);
VisInfo *pOldVI = (VisInfo *)pVI -> Copy();
short iResult = DO_UnChanged;

	if (pVI == NULL || pOldVI == NULL) {
		DELETE_OBJ (pVI);
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
		DELETE_OBJ (pVI);			// lokale VI freigeben
		DELETE_OBJ (pOldVI);
		if (fToDeleteWindow) DELETE_OBJ (pW);
		return EC_OKAY;
	}
	if (fToDeleteWindow) DELETE_OBJ (pW);

// neue VI mit alter vergleichen und feststellen, was sich geändert hat
	if (RC == EC_OKAY) {
		pVI -> CopyTo (*pHVI -> m_pVI);			// zurückkopieren

		if (pHVI -> m_iVTyp == VT_Default) 
			((DVISINFO *)(pHVI -> m_pVI)) -> m_iDefTypes = 0;
		
		if (pVI -> Priority() != pOldVI -> Priority()) iResult |= DO_PriorityChanged;
		if ((COLORREF &)pVI -> PrimColor() != (COLORREF &)pOldVI -> PrimColor()) iResult |= DO_PrimColorChanged;
		if (strcmp (pVI -> VisName(), pOldVI -> VisName())) iResult |= DO_NameChanged;
	}
		
	DELETE_OBJ (pVI);				// lokale VI freigeben
	DELETE_OBJ (pOldVI);

// Status der Änderung hinzufügen
	pHVI -> m_fFlags |= iResult;
	
return RC;
}


// Ändern einer Visinfo in einer Sicht für einen Identifikator ----------------
ErrCode DatenBasisObjekt::ChangeVisInfo (
	long lIdent, short iVTyp, VISINFO &rVI, LPCSTR pcView, int fBits, bool fForce)
{
VisInfo *pVI = VisInfoFromC (rVI, (VisType)iVTyp);
CTable tId (Idents().IdentTree());
ErrCode RC = EC_OKAY;

	if (tId.Find (&lIdent)) {
	CIdentifikatorLock l(tId);
		
		if (l) 
			RC = ChangeVisInfo (*l, (VisType)iVTyp, pVI, pcView, fBits);
	} 
	else {
		if (fForce) 
			RC = SaveVI (pVI, pcView, lIdent, (VisType)iVTyp, fBits);
		DELETE_OBJ (pVI);
	}
	if (EC_OKAY == RC)
		m_pViewWnd -> SetShouldRedraw();
	return RC;
}


ErrCode DatenBasisObjekt::ChangeVisInfo (
	CIdentifikator &rId, VisType iVTyp, VisInfo *pVI, LPCSTR pcView, int fBits)
{
	if (NULL == pVI) 
		return EC_NOMEMORY;

ErrCode RC = EC_OKAY;
long lIdent = rId.Id();		// Identifikator

// Palette korrigieren
	ExpandPalette (hPalette, pVI);

// neue VisInfo in Sicht abspeichern
	DBASSERT(SaveVI (pVI, pcView, lIdent, iVTyp, fBits, rId.isTemp()));

// neue VisInfo einstellen, wenn es keine DefaultInfo ist
	if (pVI -> isA() != VT_Default) {
	// dmait ChangePriority richtig arbeitet, behalten wir hier erst mal
	// die alte Priorität bei und äandern diese dann in eben 'ChangePriority'
	short iPrio = pVI -> Priority();

		pVI -> Priority() = rId.Priority (iVTyp);

	VisInfo *poldVI = rId.ChangeVisInfo (pVI, iVTyp);

		if (poldVI) {
		// Priorität nachziehen
			Idents().ChangePriority (lIdent, iPrio, iVTyp, false);
			DELETE_OBJ (poldVI);
		} 
		else {
		// neuer VisualisierungsTyp hinzugekommen
			pVI -> Priority() = iPrio;		// wieder rücksetzen
			Idents().PrioTree().AddEntry (rId, pVI);
		}
	} else {
		DELETE_OBJ (pVI);
	}

// Legende neu anzeigen
	if (pLegende) 
		LegendToRepaint = true;

#if defined(_USE_FLICKERFREE_DRAWING)
	m_pViewWnd -> SetShouldRedraw();
#endif // defined(_USE_FLICKERFREE_DRAWING)
	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// InPlaceComboBox für Maßstäbe anzeigen und verwalten

CSelectIdentList::CSelectIdentList (DialogWindow *pW, UINT uiID, DWORD dwStyle)
	: CSelIdentListViewWindow(pW, uiID, dwStyle),
	  m_iLower(-1), m_iUpper(-1)
{
	m_pList = NULL;
	m_uiID = 99;
	m_fScaleDirty = false;
	m_iLastFocusItem = -1;
}

CSelectIdentList::~CSelectIdentList()
{
	TX_ASSERT(NULL == m_pList);
}

void CSelectIdentList::SetColumns (int iUpper, int iLower)
{
	m_iUpper = iUpper;
	m_iLower = iLower;
}

void CSelectIdentList::MouseButtonDn (MouseEvt e) 
{
	CSelIdentListViewWindow::MouseButtonDn (e);
	if (!e.isLeftButton())
		return;

int index;
int colnum;

	if ((index = HitTestEx ((POINT &)e.Where(), &colnum)) != -1) {
	UINT flag = LVIS_FOCUSED;
	
		if ((GetListCtrl() -> GetItemState (index, flag) & flag) == flag) {
		// Add check for right column
			if (colnum == m_iLower || colnum == m_iUpper)
				PostEvent (WM_SHOWCOMBO, index, colnum);
		} 
	}
}

bool CSelectIdentList::OnShowCombo (int index, int colnum)
{
// Inhalte der Spalten richtig beeinflussen
int iUpperScale = 0;
int iLastIndex = CNT_MASSTAB;

	if (colnum == m_iLower)
		iUpperScale = UpperBoundIndex (index, m_iUpper);
	else {
		TX_ASSERT(colnum == m_iUpper);
		iLastIndex = LowerBoundIndex (index, m_iLower);
	}

// ComboBox erzeugen und füllen
CStringList lstItems;

	lstItems.push_back (os_string(ResString (IDS_NOSCALELIMIT, 20)));
	for (int i = iUpperScale; i < iLastIndex; i++) {
	os_string str (g_cbScalePrefix);

		str += ResString (IDS_MASSTAB250+i, 10);
		lstItems.push_back(str);
	}

	if (0 == lstItems.size())
		MessageBeep (MB_ICONEXCLAMATION);
	else {
		Update();		// evtl. existierende ComboBox sicher ausblenden

	string strInitEntry;
	int iInit = FindIndex (iUpperScale, index, colnum, strInitEntry);

		ShowInPlaceList (index, colnum, lstItems, iInit, strInitEntry.c_str());
	}
	return true;
}

int CSelectIdentList::FindIndex (int iFirst, int iRow, int iCol, string &rStr)
{
string str (GetListCtrl() -> GetItemText (iRow, iCol));

	if (0 == str.length())
		return -1;		// keine Voreinstellung

	for (int i = iFirst; i < CNT_MASSTAB; i++) {
	string strT (g_cbScalePrefix);

		strT += ResString (IDS_MASSTAB250+i, 10);
		if (str == strT)
			return i - iFirst + 1;
	}

	rStr = str;		// custom scale
	return -1;		// keine Voreinstellung
}

int CSelectIdentList::UpperBoundIndex (int iRow, int iCol)
{
string str (GetListCtrl() -> GetItemText (iRow, iCol));

	if (0 == str.length())
		return 0;		// keine Limitierung

long lCmpScale = RetrieveScale (str.c_str());

	for (int i = CNT_MASSTAB-1; i >= 0; i--) {
	string strT (g_cbScalePrefix);

		strT += ResString (IDS_MASSTAB250+i, 10);
		if (RetrieveScale (strT.c_str()) <= lCmpScale)
			return i + 1;
	}
	return 0;		// keine Limitierung
}

int CSelectIdentList::LowerBoundIndex (int iRow, int iCol)
{
string str (GetListCtrl() -> GetItemText (iRow, iCol));

	if (0 == str.length())
		return CNT_MASSTAB;		// keine Limitierung

long lCmpScale = RetrieveScale (str.c_str());

	for (int i = 0; i < CNT_MASSTAB; i++) {
	string strT (g_cbScalePrefix);

		strT += ResString (IDS_MASSTAB250+i, 10);
		if (RetrieveScale (strT.c_str()) >= lCmpScale)
			return i;
	}
	return CNT_MASSTAB;		// keine Limitierung
}

// HitTestEx    - Determine the row index and column index for a point
// Returns      - the row index or -1 if point is not over a row
// point        - point to be tested.
// col          - to hold the column index
int CSelectIdentList::HitTestEx (POINT point, int *col) 
{
RECT rc;

	GetClientRect (m_hWnd, &rc);
	point.y = (rc.bottom-rc.top) - point.y -1;

int colnum = 0;
int row = GetListCtrl() -> HitTest ((Point &)point, NULL);

	if (col) *col = 0;
/*	if (row != -1) 
		return row;
*/
// Make sure that the ListView is in LVS_REPORT
	if ((GetStyle() & LVS_TYPEMASK) != LVS_REPORT)
		return row;

// Get the top and bottom row visible
	row = GetListCtrl() -> GetTopIndex();

int bottom = row + GetListCtrl() -> GetCountPerPage();

	if (bottom > GetListCtrl() -> GetItemCount())
		bottom = GetListCtrl() -> GetItemCount();

// Get the number of columns
int nColumnCount = GetListCtrl() -> GetColumnCount();

	// Loop through the visible rows
	for (/**/ ; row <=bottom; row++) {
	// Get bounding rect of item and check whether point falls in it.
	RECT rect;

		GetListCtrl() -> GetItemRect (row, &rect, LVIR_BOUNDS);
		if (PtInRect (&rect, (POINT &)point)) {
		// Now find the column
			for (colnum = 0; colnum < nColumnCount; colnum++) {
			int colwidth = GetListCtrl() -> GetColumnWidth (colnum);

				if (point.x >= rect.left && point.x <= (rect.left + colwidth))
				{
					if (col) 
						*col = colnum;
					return row;
				}
				rect.left += colwidth;
			}
		}
	}
	return -1;
}

// ShowInPlaceList		- Creates an in-place drop down list for any 
//				- cell in the list view control
// Returns			- A temporary pointer to the combo-box control
// nItem			- The row index of the cell
// nCol				- The column index of the cell
// lstItems			- A list of strings to populate the control with
// nSel				- Index of the initial selection in the drop down list
ComboBox* CSelectIdentList::ShowInPlaceList
	(int nItem, int nCol, CStringList &lstItems, int nSel, LPCSTR pcInitEntry)
{
// The returned pointer should not be saved

// Make sure that the item is visible
	if (!GetListCtrl() -> EnsureVisible (nItem, TRUE)) 
		return NULL;

// Make sure that nCol is valid 
int nColumnCount = GetListCtrl() -> GetColumnCount();

	if (nCol >= nColumnCount || GetListCtrl() -> GetColumnWidth(nCol) < 10) 
		return NULL;

// Get the column offset
int offset = 0;

	for (int i = 0; i < nCol; i++)
		offset += GetListCtrl() -> GetColumnWidth (i);

RECT rect;
	
	GetListCtrl() -> GetItemRect (nItem, &rect, LVIR_BOUNDS);

// Now scroll if we need to expose the column
RECT rcClient;
int nRight = offset + rect.left + GetListCtrl() -> GetColumnWidth (nCol);

	GetClientRect (m_hWnd, &rcClient);
	if (offset + rect.left < 0) {
	Dimension size (offset + rect.left, 0);

		GetListCtrl() -> Scroll (size);
		rect.left -= size.Width();

	} else if (nRight > rcClient.right) {
	Dimension size (min((offset+rect.left) - rcClient.left, nRight - rcClient.right), 0);

		GetListCtrl() -> Scroll (size);
		rect.right -= size.Width();
		rect.left -= size.Width();
	}

	rect.left += offset + 2;
	rect.right = rect.left + GetListCtrl() -> GetColumnWidth (nCol) - 3 ;

int height = rect.bottom-rect.top;

	rect.bottom += 6*height;
	if (rect.right > rcClient.right) 
		rect.right = rcClient.right;

DWORD dwStyle = WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS|CBS_DROPDOWNLIST|CBS_DISABLENOSCROLL;
Point pt (rect.left, (rcClient.bottom-rcClient.top) - rect.bottom + 3);
Dimension dim (rect.right-rect.left, rect.bottom-rect.top);

	TX_ASSERT(NULL == m_pList);
	m_pList = new CInPlaceCombo (this, ++m_uiID, pt, dim, dwStyle);
	m_pList -> Create (nItem, nCol, lstItems, nSel, pcInitEntry);
	m_pList -> SetItemHeight (-1, height);
	if (IsWin40())
		m_pList -> SetHorizontalExtent (GetListCtrl() -> GetColumnWidth (nCol));

	return m_pList -> GetComboBox();
}

void CSelectIdentList::HorizScroll (ScrollEvt e)
{
	if (::GetFocus() != m_hWnd) {
		SetFocus();
		Update();
	}
	CSelIdentListViewWindow::HorizScroll (e);
}

void CSelectIdentList::VertScroll (ScrollEvt e)
{
	if (::GetFocus() != m_hWnd) {
		SetFocus();
		Update();
	}
	CSelIdentListViewWindow::VertScroll (e);
}

void CSelectIdentList::SetScaleText (bool fAnyScale, int iIndex, int iSubItem, LPSTR pText)
{
	if (!fAnyScale)
		GetListCtrl() -> SetItemText (iIndex, iSubItem, pText);
	else
		GetListCtrl() -> SetItemText (iIndex, iSubItem, (LPSTR)g_cbNil);
}

void CSelectIdentList::OnEndLabelEdit (NMHDR *pNMHDR, LRESULT *plResult)
{
	TX_ASSERT(pNMHDR -> idFrom == m_uiID);

LV_DISPINFO *plvDispInfo = (LV_DISPINFO *)pNMHDR;
LV_ITEM	*plvItem = &plvDispInfo->item;	

	if (plvItem->pszText != NULL) {
	ResString resNoScale (IDS_NOSCALELIMIT, 20);
	bool fAnyScale = strcmp (resNoScale, plvItem->pszText) ? false : true;
	bool fFound = false;		// selektierten Eintrag auf jeden Fall behandeln
	int iIndex = GetListCtrl() -> GetFirstSelected();

		while (-1 != iIndex) {
			SetScaleText (fAnyScale, iIndex, plvItem->iSubItem, plvItem->pszText);
			if (iIndex == plvItem->iItem)
				fFound = true;
			iIndex = GetListCtrl() -> GetNextSelected();
		}
		if (!fFound)
			SetScaleText (fAnyScale, plvItem->iItem, plvItem->iSubItem, plvItem->pszText);

		m_fScaleDirty = true;
	}
	m_pList = NULL;
	*plResult = FALSE;
}

void CSelectIdentList::OnCloseup (UINT uiID)
{
	TX_ASSERT(uiID == m_uiID);
	if (NULL != m_pList)	// nur, wenn nicht 'ESC'
		m_pList -> OnCloseup();
}

LRESULT CSelectIdentList::Dispatch (Event e)
{
	switch (e.Msg()) {
	case WM_SHOWCOMBO:
		return OnShowCombo (e.WParam(), e.LParam());

	case WM_DESTROYCOMBO:
		OnCloseup(LOWORD(e.WParam()));
		break;

	case WM_COMMAND:
		if (CBN_CLOSEUP == HIWORD(e.WParam())) 
			PostEvent (WM_DESTROYCOMBO, e.WParam());
		break;
	}
	return CSelIdentListViewWindow::Dispatch (e);
}

void CSelectIdentList::FocusChange (FocusChangeEvt e)
{
	if (!e.gotFocus())
		m_iLastFocusItem = GetListCtrl() -> GetItemFocus();
	else if (NULL != m_pList)
		m_pList -> OnCloseup();

	CSelIdentListViewWindow::FocusChange (e);
}

int CSelectIdentList::InsertColumns (int iCount)		// zusätzliche Spalten einfügen
{
	if (-1 == CSelIdentListViewWindow::InsertColumns (iCount))
		return -1;

	if (-1 == m_iUpper || -1 == m_iLower) {
		m_iUpper = UPPER_COLUMN;
		m_iLower = LOWER_COLUMN;
		if (DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) > 1) {
			m_iUpper++;
			m_iLower++;
		}
	}

ResString strUpper (IDS_UPPERSCALE, 32);
ResString strLower (IDS_LOWERSCALE, 32);

	GetListCtrl() -> InsertColumn (m_iLower, strLower, LVCFMT_LEFT, -1, m_iLower);
	GetListCtrl() -> InsertColumn (m_iUpper, strUpper, LVCFMT_LEFT, -1, m_iUpper);
	return GetListCtrl() -> GetColumnCount();
}

void CSelectIdentList::WindowInit (Event)
{
// new for 'Nashville' (#HK960823)
//#if defined(ListView_GetExtendedListViewStyle)
//	if (IsWin40()) {
//	DWORD dwStyleEx = GetListCtrl() -> GetExtendedStyle();
//
//		GetListCtrl() -> SetExtendedStyle (dwStyleEx | LVS_EX_HEADERDRAGDROP);
//	}
//#endif 
}
