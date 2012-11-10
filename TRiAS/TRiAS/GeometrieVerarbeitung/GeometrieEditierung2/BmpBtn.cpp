// BitmapButton ---------------------------------------------------------------
// File: BmpBtn.cpp

//#include "trias03p.hxx"
#include "GeoEditP.h"

//#include <bmpbtn.hxx>
#include "BmpBtn.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Konstruktoren/Destruktor
CBmpButton::CBmpButton (pDialogWindow parent, ResID resID)
	: PushButton (parent, resID),
	  m_pBitmap(NULL), m_pBitmapSel(NULL),
	  m_pBitmapFocus(NULL), m_pBitmapDisabled(NULL)
{
HWND hCtrl = Handle();

	if (NULL != hCtrl)
		m_fIsBmpBtn = (::GetWindowLong (hCtrl, GWL_STYLE) & BS_BITMAP) ? true : false;
	m_hBmp = NULL;

	_ASSERTE(IsWin40() || !m_fIsBmpBtn);	// BS_BITMAP nur unter Win40 erlaubt
}

CBmpButton::CBmpButton (pWindow pW, CvID id, Point pt, Dimension dim, LPCSTR pcInitText)
	: PushButton (pW, id, pt, dim, pcInitText),
	  m_pBitmap(NULL), m_pBitmapSel(NULL),
	  m_pBitmapFocus(NULL), m_pBitmapDisabled(NULL)
{
HWND hCtrl = Handle();

	if (NULL != hCtrl)
		m_fIsBmpBtn = (::GetWindowLong (hCtrl, GWL_STYLE) & BS_BITMAP) ? true : false;
	m_hBmp = NULL;

	_ASSERTE(IsWin40() || !m_fIsBmpBtn);	// BS_BITMAP nur unter Win40 erlaubt
}

CBmpButton::~CBmpButton (void)
{
	if (m_fIsBmpBtn)
		SetImage (m_hBmp);
	DELETE_OBJ(m_pBitmap);
	DELETE_OBJ(m_pBitmapSel);
	DELETE_OBJ(m_pBitmapFocus);
	DELETE_OBJ(m_pBitmapDisabled);
}

bool CBmpButton::FInit (void)
{
	if (!Control::FInit()) 
		return false;

HWND hCtrl = Handle();

	if (NULL != hCtrl)
		m_fIsBmpBtn = (::GetWindowLong (hCtrl, GWL_STYLE) & BS_BITMAP) ? true : false;

	_ASSERTE(IsWin40() || !m_fIsBmpBtn);	// BS_BITMAP nur unter Win40 erlaubt

return true;
}

///////////////////////////////////////////////////////////////////////////////
// sonstige Member
inline bool IsValid (ResID resID)
{
	return static_cast<uint>(resID) != 0 || static_cast<LPCSTR>(resID) != NULL;
}

// #HK000908: Table used to map default system colors onto the system color identifiers.
static COLORMAP sysColorMap[] = {
//	      b     g     r
	{ RGB(0x00, 0x00, 0x00), GetSysColor(COLOR_BTNTEXT) },
	{ RGB(0x80, 0x80, 0x80), GetSysColor(COLOR_BTNSHADOW) },
	{ RGB(0xc0, 0xc0, 0xc0), GetSysColor(COLOR_BTNFACE) },
	{ RGB(0xff, 0xff, 0xff), GetSysColor(COLOR_BTNHIGHLIGHT) }
};
#define _countof(x)		(sizeof(x)/sizeof(x[0]))

bool CBmpButton::LoadBitmaps (ResID resBitmap, 
		ResID resBitmapSel, ResID resBitmapFocus, ResID resBitmapDisabled)
{
	DELETE_OBJ(m_pBitmap);
	DELETE_OBJ(m_pBitmapSel);
	DELETE_OBJ(m_pBitmapFocus);
	DELETE_OBJ(m_pBitmapDisabled);

// erste Bitmap laden
	if (!IsValid (resBitmap)) {
		TX_TRACE0("Failed to load bitmap for normal image.\n");
		return false;		// required bitmap
	}
	m_pBitmap = new Bitmap (resBitmap, sysColorMap, _countof(sysColorMap), 0);
	if (NULL == m_pBitmap || NULL == m_pBitmap -> Handle()) {
		TX_TRACE0("Out of memory loading bitmap for normal image.\n");
		return false;
	}

	if (m_fIsBmpBtn) {
		m_hBmp = SetImage (m_pBitmap -> Handle());
		return true;		// die anderen werden nicht benötigt
	}

// evtl. weitere Bitmaps laden
bool fAllLoaded = true;

	if (IsValid(resBitmapSel)) {
		m_pBitmapSel = new Bitmap (resBitmapSel, sysColorMap, _countof(sysColorMap), 0);
		if (NULL == m_pBitmapSel || NULL == m_pBitmapSel -> Handle()) {
			DELETE_OBJ(m_pBitmapSel);
			TX_TRACE0("Out of memory loading bitmap for select image.\n");
			fAllLoaded = false;
		}
	}
	if (IsValid(resBitmapFocus)) {
		m_pBitmapFocus = new Bitmap (resBitmapFocus, sysColorMap, _countof(sysColorMap), 0);
		if (NULL == m_pBitmapFocus || NULL == m_pBitmapFocus -> Handle()) {
			DELETE_OBJ(m_pBitmapFocus);
			fAllLoaded = false;
		}
	}
	if (IsValid(resBitmapDisabled)) {
		m_pBitmapDisabled = new Bitmap (resBitmapDisabled, sysColorMap, _countof(sysColorMap), 0);
		if (NULL == m_pBitmapDisabled || NULL == m_pBitmapDisabled -> Handle()) {
			DELETE_OBJ(m_pBitmapDisabled);
			fAllLoaded = false;
		}
	}

return fAllLoaded;
}

void CBmpButton::SizeToContent (void)
{
	_ASSERTE(m_pBitmap != NULL && m_pBitmap -> Handle() != NULL);     // required

Dimension dim = m_pBitmap -> GetSize();

	::SetWindowPos (Handle(), NULL, -1, -1, dim.Width(), dim.Height(),
					SWP_NOMOVE|SWP_NOZORDER|SWP_NOREDRAW|SWP_NOACTIVATE);
}

// Autoload will load the bitmap resources based on the text of
//  the button
// Using suffices "U", "D", "F" and "X" for up/down/focus/disabled
bool CBmpButton::AutoLoad (ResourceFile *pRF)
{
char cbBuffer[_MAX_PATH];

	GetWindowText (Handle(), cbBuffer, _MAX_PATH);

string strButtonName (cbBuffer);

	_ASSERTE(strButtonName.length() > 0);      // must provide a title

string strU = strButtonName + TEXT("U");
string strD = strButtonName + TEXT("D");
string strF = strButtonName + TEXT("F");
string strX = strButtonName + TEXT("X");

	LoadBitmaps (ResID(strU.c_str(), pRF), ResID(strD.c_str(), pRF), 
				 ResID(strF.c_str(), pRF), ResID(strX.c_str(), pRF));

// we need at least the primary
	if (NULL == m_pBitmap || m_pBitmap -> Handle() == NULL)
		return false;

	SizeToContent();		// size to content

return true;
}

///////////////////////////////////////////////////////////////////////////////
// Malroutine
bool CBmpButton::DrawItem (DrawItemEvt e)
{
	if (m_fIsBmpBtn) return false;		// should not happen

CvID thisID = GetID();

	if (!(e.GetControlID() == thisID))
		return false;		// nur uns selbst bearbeiten

// must have at least the first bitmap loaded before calling DrawItem
	_ASSERTE(m_pBitmap != NULL && m_pBitmap -> Handle() != NULL);     // required

// use the main bitmap for up, the selected bitmap for down
Bitmap* pBitmap = m_pBitmap;

	if (e.isSelected() && m_pBitmapSel != NULL)
		pBitmap = m_pBitmapSel;
	else if (e.hasFocus() && m_pBitmapFocus != NULL)
		pBitmap = m_pBitmapFocus;	   // third image for focused
	else if (e.isDisabled() && m_pBitmapDisabled != NULL)
		pBitmap = m_pBitmapDisabled;   // last image for disabled

// draw the whole button
HDC hDC = (HDC)e.Handle (API_CONTROL_HDC);
HDC hMemDC = ::CreateCompatibleDC (hDC);
HBITMAP hOldBitmap = (HBITMAP)::SelectObject (hMemDC, pBitmap -> Handle());
Rectangle rc = e.ItemSize();

	::BitBlt (hDC, rc.Left(), rc.Top(), rc.Right()-rc.Left(), rc.Bottom()-rc.Top(),
			  hMemDC, 0, 0, SRCCOPY);
	::SelectObject (hMemDC, hOldBitmap);
	::DeleteDC (hMemDC);

return true;
}

