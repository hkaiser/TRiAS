// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.10.2000 08:05:34 
//
// @doc
// @module ObjPropDestWindow.cpp | Definition of the <c CObjPropDestWindow> class

#include "trias03p.hxx"
#include "trias03.h"

#include <ClipBrd.hxx>
#include <eieruhr.hxx>

#include "ObjPropDestWindow.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// globale Variablen
extern TCHAR g_pDLLName[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// Fensterausgabe der Objekteigenschaften 
#pragma warning (disable: 4355)

CObjPropDestWindow::CObjPropDestWindow (pWindow pW, ResID uiResID, LPCSTR pcText, bool fHeadline) :
	DialogWindow (pW, uiResID),
	m_pbCopy (this, IDC_COPYTOCLIPBOARD),
	m_pbOk (this, IDOK),
	m_Result (this, IDC_OBJPROPDESTWINDOW)
{
	if (NULL == pcText) {
		m_pbCopy.Disable();
		return;
	}

	m_pcText = pcText;		// nur für ClipBoard speichern

	if (!fHeadline)
		m_Result.SetStyle (LVS_NOCOLUMNHEADER);

#if defined(ListView_GetExtendedListViewStyle)
	if (IsWin40())
		m_Result.SetExtendedStyle (m_Result.GetExtendedStyle() | LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_INFOTIP);
#endif 
	InitListViewCtrl (pcText, fHeadline);

// diverse Größenverhältnisse merken
	m_ptCopy = m_pbCopy.GetPosition();
	m_dimCopy = m_pbCopy.GetSize();
	m_ptOk = m_pbOk.GetPosition();
	m_dimOk = m_pbOk.GetSize();
	m_ptResult = m_Result.GetPosition();
	m_dimResult = m_Result.GetSize();

	m_rcCanvas = CanvasRect();
}

void CObjPropDestWindow::ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (1);
		break;

	case IDC_COPYTOCLIPBOARD:
		{
			TX_ASSERT(NULL != m_pcText);

		CClipboard DCB;

			DCB.Clear();
			DCB.Insert (m_pcText);
		}
		break;
	}
}

bool CObjPropDestWindow::InitListViewCtrl (LPCSTR pcText, bool fHeadline)
{
// zeilenweise bearbeiten, jedes feld kommt in eine extra Spalte
CEierUhr Wait (GetParent());
ResourceFile RF (g_pDLLName);
const char *pcT = pcText;
const char *pcField = pcText;
int iColCnt = 0;
int iLineCnt = 0;

	while (*pcT) {
		switch (*pcT) {
		case '\r':
		case '\t':	// FeldEnde
			{
			os_string str (pcField, pcT - pcField);

				if (0 == iLineCnt) {	// erste Zeile
					if (fHeadline) 
						m_Result.InsertColumn (iColCnt, str.c_str(), LVCFMT_LEFT, 120, 0);
					else {
					ResString resColHdr (ResID(IDS_COLUMNHEADER, &RF), 32);
					char cbBuffer[64]; 

						wsprintf (cbBuffer, resColHdr.Addr(), iColCnt+1);
						m_Result.InsertColumn (iColCnt, cbBuffer, LVCFMT_LEFT, 120, iColCnt);
						if (0 == iColCnt)
							m_Result.InsertItem (0, str.c_str());
						else
							m_Result.SetItem(0, iColCnt, LVIF_TEXT, str.c_str(), 0, 0, 0, NULL);
					}
				} 
				else if (0 == iColCnt) {	// neue Zeile
					m_Result.InsertItem (fHeadline ? iLineCnt-1 : iLineCnt, str.c_str());
				}
				else {
				LV_ITEM lvi;

					memset (&lvi, 0, sizeof(LV_ITEM));
					lvi.mask = LVIF_TEXT;
					lvi.pszText = (char *)str.c_str();
					lvi.iItem = fHeadline ? iLineCnt-1 : iLineCnt;
					lvi.iSubItem = iColCnt;
					m_Result.SetItem (&lvi);
				}					
				++iColCnt;
				pcField = pcT+1;	// nächstes Feld
			}

			if ('\r' == *pcT) {	// ZeilenEnde
				++iLineCnt;
				iColCnt = 0;
				if ('\n' == *(pcT+1)) {
					++pcT;			// '\n' überspringen
					++pcField;
				}
			}
			break;

		default:
			break;
		}
		++pcT;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Größe wurde geändert
void CObjPropDestWindow::ReSize (ReSizeEvt e)
{
// Controls neu positionieren
Dimension dimNewSize (e.GetNewSize());
Dimension dimNewResult (
				dimNewSize.Width() - (m_rcCanvas.Width()-m_dimResult.Width()), 
				dimNewSize.Height() - (m_rcCanvas.Height()-m_dimResult.Height()) );

	m_Result.ChangeSize(dimNewResult);

Point ptCopy (
		dimNewSize.Width() - (m_rcCanvas.Right()-m_ptCopy.X()), 
		dimNewSize.Height() - (m_rcCanvas.Top()-m_ptCopy.Y()) );
Point ptOk (
		dimNewSize.Width() - (m_rcCanvas.Right()-m_ptOk.X()), 
		dimNewSize.Height() - (m_rcCanvas.Top()-m_ptOk.Y()) );

	m_pbCopy.ChangePosition(ptCopy);
	m_pbOk.ChangePosition(ptOk);
}

// Implementation of Expose
void CObjPropDestWindow::Expose(ExposeEvt e)
{
HDC hDC = (HDC)Handle(API_DRAWOBJECT_HDC);
Rectangle rc;

	GetClientRect(Handle(API_WINDOW_HWND), (RECT *)&rc);
	rc.Left() = rc.Right() - ::GetSystemMetrics(SM_CXHSCROLL);
	rc.Top() = rc.Bottom() - ::GetSystemMetrics(SM_CYVSCROLL);

	::DrawFrameControl(hDC, (RECT *)&rc, DFC_SCROLL, DFCS_SCROLLSIZEGRIP);
}

// Implementation of Dispatch
LRESULT CObjPropDestWindow::Dispatch(Event e)
{
	switch (e.Msg()) {
	case WM_GETMINMAXINFO:
		GetMinMaxInfo ((MINMAXINFO *)e.LParam());
		break;		// auf jeden Fall weitersenden

	case WM_NCHITTEST:
		{
		LRESULT lResult = FALSE;

			if (NcHitTest (Point(LOWORD(e.LParam()), HIWORD(e.LParam())), &lResult))
				return lResult;
			break;
		}

	default:
		break;
	}
	return DialogWindow::Dispatch(e);
}

// Implementation of WindowPosChanging
void CObjPropDestWindow::GetMinMaxInfo(MINMAXINFO *pMinMaxInfo)
{
	pMinMaxInfo -> ptMinTrackSize.x = 3*m_dimCopy.Width();
	pMinMaxInfo -> ptMinTrackSize.y = 5*m_dimCopy.Height();
}

// Implementation of NcHitTest
BOOL CObjPropDestWindow::NcHitTest(Point pt, LRESULT *pResult)
{
Rectangle rc (CanvasRect());

	ScreenToClient (Handle(API_WINDOW_HWND), (POINT *)&pt);
	if (pt.X() >= rc.Right() - ::GetSystemMetrics(SM_CXHSCROLL) &&
		pt.Y() >= rc.Top() - ::GetSystemMetrics(SM_CYVSCROLL)) 
	{
		*pResult = HTBOTTOMRIGHT;
		return TRUE;
	}
	return FALSE;
}

