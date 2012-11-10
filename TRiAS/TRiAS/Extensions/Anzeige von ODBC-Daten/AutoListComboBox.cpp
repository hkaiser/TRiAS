// AutoListComboBox.cpp : implementation file
//

#include "pheader.h"
#include "odbcext.h"
#include "AutoListComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoListComboBox

CAutoListComboBox::CAutoListComboBox()
{
}

CAutoListComboBox::~CAutoListComboBox()
{
}


BEGIN_MESSAGE_MAP(CAutoListComboBox, CComboBox)
	//{{AFX_MSG_MAP(CAutoListComboBox)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// Breite des DropDownFensters gleich hier mit anpassen
HBRUSH CAutoListComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);

	switch (nCtlColor) {
	case CTLCOLOR_EDIT:
		break;

	case CTLCOLOR_LISTBOX:
		{             
		// benötigte Breite feststellen
		long iListWidth = 0;
		CDC *pDC = GetDC();
		CFont *pOldFont = pDC -> SelectObject (GetFont());

			for (int i = 0; i < GetCount(); i++) {
			CString str;
			CSize sz;

				GetLBText (i, str);
				GetTextExtentPoint32 (pDC -> GetSafeHdc(), str, str.GetLength(), &sz);
				if (pWnd -> GetStyle() & WS_VSCROLL)
					sz.cx += GetSystemMetrics (SM_CXVSCROLL);
				iListWidth = max (iListWidth, sz.cx);
			}

		// jetzt die neue breite setzen
			if (0 < iListWidth) {
			CRect rect;
				
				pWnd->GetWindowRect(&rect);
				if (rect.Width() < iListWidth) {
				// FensterRahmen und etwas Platz lassen
					rect.right = rect.left + iListWidth + 4*GetSystemMetrics(SM_CXBORDER);
					pWnd->MoveWindow(&rect);
				}
			}
			pDC -> SelectObject (pOldFont);
			ReleaseDC(pDC);
		}
		break;
	}
	return hbr; 
}

