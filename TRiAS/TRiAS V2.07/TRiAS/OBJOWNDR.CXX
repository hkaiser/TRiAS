// Routinen fuer OwnerDrawListBox ---------------------------------------------
// File: OBJOWNDR.CXX

#include "triaspre.hxx"

#if !defined(WIN32)
extern "C" int WINAPI SetROP2 (HDC, int);
#else	// neue Funktion in WIN32
#undef GetTextExtentPoint
#define GetTextExtentPoint	GetTextExtentPoint32
#endif // WIN32

#include "objowndr.hxx"

// EventHandler für das DialogFenster -----------------------------------------
Bool EXPORTTRIAS ObjektInfo :: DeleteItem (DeleteItemEvt e)	// ODItem wird gelöscht
{
CTable t(*m_pOITree);
long lONr = (long)e.GetItemData();	// Daten lesen

	if (t.Find (&lONr)) {
		t.Delete();		// Item in Baum freigeben
		return TRUE;
	}

return FALSE;
}

static inline COLORREF InvertRGB (Color C)
{
COLORREF hC = GetSysColor (COLOR_HIGHLIGHTTEXT);

	return RGB (GetRValue(hC) - C.Red(), 
		    GetGValue(hC) - C.Green(), 
		    GetBValue(hC) - C.Blue());
}

Bool EXPORTTRIAS ObjektInfo :: DrawEntireItem (DrawItemEvt e)
{
// ZeichenFunktionen
	DrawItemSelect (e);

	if (e.hasFocus())	// evtl. mit Focus versehen
		DrawItemFocus (e);

return TRUE;
}

Bool EXPORTTRIAS ObjektInfo :: DrawItemFocus (DrawItemEvt e)
{
Rectangle Rc = e.ItemSize();			// aktuellen Bereich holen
HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);		// DC holen

	DrawFocusRect (hDC, (RECT *)&Rc);

	InflateRect ((LPRECT)&Rc, -1, -1);	// verkleinern

	if (e.hasFocus()) {
	// Rechteck zeichnen
	HBRUSH hBr = CreateSolidBrush (*(COLORREF *)&m_C);

		FrameRect (hDC, (LPRECT)&Rc, hBr);
		:: DeleteObject (hBr);
	} else {
	// SelektionsRechteck wegmachen
	HBRUSH hBr = (HBRUSH)SelectObject (hDC, GetStockObject (HOLLOW_BRUSH));
	HPEN hPen = CreatePen (PS_SOLID, 1, GetSysColor (e.isSelected() ? COLOR_HIGHLIGHT : COLOR_WINDOW));
	HPEN hOldPen = (HPEN)SelectObject (hDC, hPen);
//	int oldROP =  SetROP2 (hDC, e.isSelected() ? R2_NOTCOPYPEN : R2_COPYPEN);

		DrawRectangle (hDC, Rc.Left(), Rc.Top(), Rc.Right(), Rc.Bottom());
//		SetROP2 (hDC, oldROP);
		SelectObject (hDC, hBr);
		SelectObject (hDC, hOldPen);
		:: DeleteObject (hPen);
	}

return TRUE;
}

Bool EXPORTTRIAS ObjektInfo :: DrawItemSelect (DrawItemEvt e)
{
Rectangle rcItem = e.ItemSize();			// aktuellen Bereich holen
HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);
long lONr = (long)e.GetItemData();
CTable t(*m_pOITree);

	if (!t.Find (&lONr)) return FALSE;

ObjInfoItemLock l(t);
COLORREF oldBKColor;
COLORREF oldTextColor;

	if (e.isSelected()) {
		oldBKColor = SetBkColor (hDC, GetSysColor (COLOR_HIGHLIGHT));
		oldTextColor = SetTextColor (hDC, InvertRGB (l -> StringColor()));
	} else {
		oldBKColor = SetBkColor (hDC, GetSysColor (COLOR_WINDOW));
		oldTextColor = SetTextColor (hDC, *((COLORREF *)&(l -> StringColor())));
	}

// Text in gewünschter Farbe darstellen
char *cptr = l -> ItemText();
int iLen = strlen (cptr);
SIZE szStr;

// Größe des linken Textes bestimmen
	GetTextExtentPoint (hDC, cptr, iLen, &szStr);

Rectangle rc = rcItem;

	rc.Right() = rc.Left() + szStr.cx;
	ExtTextOut (hDC, rc.Left()+1, rc.Top()+1, 
				ETO_CLIPPED|ETO_OPAQUE, (const RECT *)&rc, 
				cptr, iLen, NULL);

// rechten Textteil (Objekteigenschaft) ausgeben
	if (e.isSelected())
		SetTextColor (hDC, InvertRGB (l -> ObjPropColor()));
	else {
	COLORREF cr = (COLORREF &)l -> ObjPropColor();

//		if (l -> ObjPropExists())
			SetTextColor (hDC, cr);
//		else
//			SetBkColor (hDC, cr);
	}

	rc = rcItem;
	rc.Left() = rcItem.Left() + szStr.cx;

char *pObjProp = l -> PropText();

	ExtTextOut (hDC, rc.Left()+1, rc.Top()+1, 
				ETO_CLIPPED|ETO_OPAQUE, (const RECT *)&rc, 
				pObjProp, strlen(pObjProp), NULL);

	SetBkColor (hDC, oldBKColor);
	SetTextColor (hDC, oldTextColor);

return TRUE;
}


int EXPORTTRIAS ObjektInfo :: CompareItem (OwnerDrawEvt, void *pItem1, void *pItem2)
{	// Vergleichsfunktion
long lONr1 = (long)pItem1;
long lONr2 = (long)pItem2;

// wenn eine VergleichsFunktion für dieses Fenster gegeben ist, dann diese rufen
	if (m_pCmpProc) return m_pCmpProc (lONr1, lONr2, m_dwData);
		
// ansonsten nach ObjektNummern sortieren
	if (lONr1 > lONr2) return 1;
	if (lONr1 < lONr2) return -1;
	
return 0;
}


Bool EXPORTTRIAS ObjektInfo :: MeasureItem (MeasureItemEvt e)
{
TEXTMETRIC tm;
HWND hDlg = e.Handle (API_DLGWINDOW_HWND);
HDC hDC = GetDC (hDlg);

	GetTextMetrics (hDC, &tm);
	e.SetItemHeight (tm.tmHeight);
	ReleaseDC (hDlg, hDC);

return TRUE;
}

// Konstruktor/Destruktor für die Items, die in der ListBox hängen ------------
ObjInfoItem :: ObjInfoItem (long ONr, short iOTyp, const char *pStr, const char *pText,
			    Color C, Color C2, Color C3)
{
	_ONr = ONr;
	m_iOType = iOTyp;
	_pStr = StrDup (pStr, RC_ctObjInfoItem);
	m_pText = StrDup (pText, RC_ctObjInfoItem);
	_C = C;				// StringFarbe
	_ActC = C2;			// AktivierungsFarbe
	m_cObjProp = C3;	// Farbe der Objekteigenschaft
	_isSelected = FALSE;
	_isActive = FALSE;
}

ObjInfoItem :: ObjInfoItem (long ONr) 
{
char lpSearchStr[40];

	wsprintf (lpSearchStr, "%04ld:", ONr);

	_ONr = ONr;
	_pStr = StrDup (lpSearchStr, RC_ctObjInfoItem);
	m_pText = NULL;
	_C = Color (BLACK);
	_isSelected = FALSE;
	_isActive = FALSE;
}

ObjInfoItem :: ~ObjInfoItem (void) 
{
	DELETE (m_pText);
	DELETE (_pStr);
}

Color ObjInfoItem :: ChangeActiveColor (Color newC)
{
Color oldC = _ActC;

	_ActC = newC;
	
return oldC;
}

// Baum, der die Einzelnen Items enthält --------------------------------------
ObjInfoItemTree :: ObjInfoItemTree (void)
		 : CTree (GetONr, CmpONr)
{
	// nothing else to do
}

ObjInfoItemTree :: ~ObjInfoItemTree (void)
{
	EveryDelete();
}

void EXPORTTRIAS ObjInfoItemTree :: UserDelete (void *pObj)
{
	((ObjInfoItem *)pObj) -> /*ObjInfoItem ::*/ ~ObjInfoItem();
}


string ObjInfoItemTree::GetItemString (LONG lONr)
{
CTable t(*this);
string str;

	if (t.Find(&lONr)) {
	ObjInfoItemLock l(t);

		if (!l) return str;
		str = string(l -> ItemText()) + l -> PropText();
	}
	return str;
}

void ObjInfoItemTree::SelectObject (LONG lONr, bool fSelect)
{
CTable t(*this);

	if (0 != lONr) {
	// das eine bearbeiten
		if (t.Find(&lONr)) {
		ObjInfoItemLock l(t);

			if (l) l -> isSelected (fSelect);
		}
	} else {
	// alle bearbeiten
		for (t.First(); t.Valid(); t.Next()) {
		ObjInfoItemLock l(t);

			if (l) l -> isSelected (fSelect);
		}
	}
}

void ObjInfoItemTree::ActivateObject (LONG lONr)
{
CTable t(*this);

// alle deaktivieren
	for (t.First(); t.Valid(); t.Next()) {
	ObjInfoItemLock l(t);

		if (l) l -> isActive (false);
	}

// das eine wieder aktivieren
	if (t.Find(&lONr)) {
	ObjInfoItemLock l(t);

		if (l) l -> isActive (true);
	}
}


// Zugriffs- und VergleichsFunktion -------------------------------------------
void * GetONr (void *pObj)
{
	return & ((ObjInfoItem *)pObj) -> ONr();
}

int CmpONr (void *pObj1, void *pObj2)
{
long ONr1 = ((ObjInfoItem *)pObj1) -> ONr();
long ONr2 = ((ObjInfoItem *)pObj2) -> ONr();

// nach ObjektNummern sortieren
	if (ONr1 > ONr2) return 1;
	if (ONr1 < ONr2) return -1;

return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Erweiterte Listbox mit HorizontalScrolling
ObjektInfoListBox::ObjektInfoListBox (
		pDialogWindow pW, ResID rsc, ObjInfoItemTree &rData)
	: OwnerDrawListBoxEx (pW, rsc), m_rData(rData)
{
	FInitListboxExtents (GetHandle());
}

ObjektInfoListBox::~ObjektInfoListBox (void)
{
	FFreeListboxExtents (GetHandle());
}

long ObjektInfoListBox::AddItemEx (LONG lONr, LPCSTR pcText, int iIndex)
{
	WAddExtentEntry (GetHandle(), pcText);
	return OwnerDrawListBoxEx::AddItem ((void *)lONr, iIndex);
}

long ObjektInfoListBox::DelItemEx (int iIndex)
{
LONG lONr = (LONG)GetItem (iIndex);
string str = m_rData.GetItemString (lONr);

	WRemoveExtentEntry (GetHandle(), str.c_str());
	return OwnerDrawListBoxEx::DelItem(iIndex);
}

long ObjektInfoListBox::SetItemEx (LONG lONr, LPCSTR pcText, int iIndex)
{
string str = m_rData.GetItemString (lONr);

	WRemoveExtentEntry (GetHandle(), str.c_str());
	WAddExtentEntry (GetHandle(), pcText);
	return OwnerDrawListBoxEx::SetItem((void *)lONr, iIndex);
}

