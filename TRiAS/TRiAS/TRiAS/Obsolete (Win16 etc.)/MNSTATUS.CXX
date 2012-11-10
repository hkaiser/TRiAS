// StatusZeile für das TRiAS-Hauptfenster -------------------------------------
// File: MNSTATUS.CXX

#include "triaspre.hxx"
#include "mnstatus.hxx"

// Initialisierung/Konstruktor/Destruktor -------------------------------------
CTRiASStatus::CTRiASStatus (pWindow pW)
			 : m_sbMain (pW, ID_TRIASVIEW_STATUSBAR, Point(), Dimension (100, 100)),
			   ControlWindow (&m_sbMain)
{
}

CTRiASStatus::~CTRiASStatus (void)
{
}

///////////////////////////////////////////////////////////////////////////////
// EventHandler
bool CControlBar::OnSizeParent (SIZEPARENTPARAMS *lpLayout)
{
DWORD dwStyle = RecalcDelayShow (lpLayout);

	if ((dwStyle & WS_VISIBLE) && (dwStyle & CBRS_ALIGN_ANY) != 0) {
	// align the control bar
	RECT rect;
	
		CopyRect(&rect, &lpLayout->rect);

	SIZE sizeAvail;
	
		sizeAvail.cx = rect.right-rect.left;  // maximum size available
		sizeAvail.cy = rect.bottom-rect.top;

	// get maximum requested size
	DWORD dwMode = lpLayout->bStretch ? LM_STRETCH : 0;
	
		if ((m_dwStyle & CBRS_SIZE_DYNAMIC) && m_dwStyle & CBRS_FLOATING)
			dwMode |= LM_HORZ | LM_MRUWIDTH;
		else if (dwStyle & CBRS_ORIENT_HORZ)
			dwMode |= LM_HORZ | LM_HORZDOCK;
		else
			dwMode |=  LM_VERTDOCK;

	CSize size = CalcDynamicLayout (-1, dwMode);

		size.cx = min(size.cx, sizeAvail.cx);
		size.cy = min(size.cy, sizeAvail.cy);

		if (dwStyle & CBRS_ORIENT_HORZ)	{
			lpLayout->sizeTotal.cy += size.cy;
			lpLayout->sizeTotal.cx = max(lpLayout->sizeTotal.cx, size.cx);
			
			if (dwStyle & CBRS_ALIGN_TOP)
				lpLayout->rect.top += size.cy;
			else if (dwStyle & CBRS_ALIGN_BOTTOM) {
				rect.top = rect.bottom - size.cy;
				lpLayout->rect.bottom -= size.cy;
			}
		}
		else if (dwStyle & CBRS_ORIENT_VERT) {
			lpLayout->sizeTotal.cx += size.cx;
			lpLayout->sizeTotal.cy = max(lpLayout->sizeTotal.cy, size.cy);
			
			if (dwStyle & CBRS_ALIGN_LEFT)
				lpLayout->rect.left += size.cx;
			else if (dwStyle & CBRS_ALIGN_RIGHT) {
				rect.left = rect.right - size.cx;
				lpLayout->rect.right -= size.cx;
			}
		}
		else {
			TX_ASSERT(FALSE);      // can never happen
		}

		rect.right = rect.left + size.cx;
		rect.bottom = rect.top + size.cy;

	// only resize the window if doing layout and not just rect query
		if (lpLayout->hDWP != NULL)
			RepositionWindow (lpLayout, m_hWnd, &rect);
	}

return false;
}


// alle nicht behandelten Messages hierhin ------------------------------------
LRESULT CTRiASStatus::Default (Event e)
{
NakedEvt &ne = (NakedEvt &)e;

	switch (ne.wmsg()) {
	case WM_SIZEPARENT:
		return OnSizeParent ((SIZEPARENTPARAMS *)ne.lparam());

	default:
		break;
	}

return ControlWindow::Default(e);
}


