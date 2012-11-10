// DerivedGrid.cpp : implementation file
//

#include "pheader.h"
#include "odbcext.h"
#include "DerivedGrid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSortedGrid
CSortedGrid::CSortedGrid()
{
	m_wndParent = NULL;
}

CSortedGrid::~CSortedGrid()
{
}


BEGIN_MESSAGE_MAP(CSortedGrid, CGXRecordWnd)
	//{{AFX_MSG_MAP(CSortedGrid)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


class CFieldInfoChanger
{
protected:
	CGXRecordWnd*	m_pGrid;	// welches Grid
	ROWCOL			m_nCol;			// welcher nCol
	CString			m_strOldName;		// der alte Wert

public:
	CFieldInfoChanger(CGXRecordWnd* pGrid, ROWCOL nCol)
	{
		m_pGrid = pGrid;
		m_nCol = nCol;

		if (NULL == m_pGrid) 
			return;

		CGXDbParam* pParam = (CGXDbParam*) m_pGrid->GetParam();
		short nField = (short) m_pGrid->GetFieldFromCol(m_nCol);

#if _MFC_VER >= 0x0420
		CGXFieldInfo& fieldInfo = pParam->m_apFieldInfo[nField];
#else
		CFieldInfo fieldInfo;
		pSet->GetFieldInfo(nField, &fieldInfo);
#endif

		CString strTmp = fieldInfo.strName;
		m_strOldName = strTmp;
		strTmp.TrimRight();
		strTmp.TrimLeft();

		if (CString(_T("[")) != strTmp.Left(1))	// Feldname nicht in Klammern
		{	
			// Namen des Feldes setzen
			fieldInfo.strName = _T("[") + strTmp + _T("]");	// Namen des Feldes ändern
		}
	}
	~CFieldInfoChanger()
	{
		if (NULL == m_pGrid) 
			return;

		CGXDbParam* pParam = (CGXDbParam*) m_pGrid->GetParam();
		short nField = (short) m_pGrid->GetFieldFromCol(m_nCol);

#if _MFC_VER >= 0x0420
		CGXFieldInfo& fieldInfo = pParam->m_apFieldInfo[nField];
#else
		CFieldInfo fieldInfo;
		pSet->GetFieldInfo(nField, &fieldInfo);
#endif
		// und den wert zurücksetzen
		fieldInfo.strName = m_strOldName;
	}
};

/////////////////////////////////////////////////////////////////////////////
// CDerivedGrid message handlers
void CSortedGrid::OnClickedButtonRowCol(ROWCOL nRow, ROWCOL nCol)
{
	CGXRecordWnd::OnClickedButtonRowCol(nRow, nCol);
}

// Parameter : direction 
// Funktion : angabe der Sortierreihenfolge
// Werte	:	1	steigend sortieren
//				0	Auswahl der SOrtierung
//				-1	fallend sortieren (default)
void CSortedGrid::DoSort(ROWCOL nCol, UINT direction)
{
	if (nCol > 0)
	{
		// user double-clicked on a column header

		// Specify column to be sorted (could also be several columns)
		CGXSortInfoArray sortInfo;
		sortInfo.SetSize(1);
		sortInfo[0].nRC = nCol;
		sortInfo[0].sortType = CGXSortInfo::autodetect;  // autodetect if numeric or alphanumeric
		sortInfo[0].bCase = TRUE;  // case sensitive

		// If this column is already sorted, toggle sort order
		if (0 == direction)
		{
		CGXGridParam* pParam = GetParam();
		if (pParam->m_nLastSortedCol != nCol || !pParam->m_bSortAscending)
			direction = 1;
/*		else
			sortInfo[0].sortOrder = CGXSortInfo::descending;*/
		}	
		if (1 == direction)
		{
			sortInfo[0].sortOrder = CGXSortInfo::ascending;
		}
		else
		{
			sortInfo[0].sortOrder = CGXSortInfo::descending;
		}

		// mark column as sorted - header button will check m_nLastSortedCol
		// to determine if it shall draw itsself pressed

		GetParam()->m_nLastSortedCol = nCol;
		LockUpdate(TRUE);
		
		{
			CFieldInfoChanger InfoChanger(this, nCol);	// this will fake the naming bug in OG

			// Sort 
			SortRows(CGXRange().SetTable(), sortInfo);
		}
		LockUpdate(FALSE);
		Redraw();
	}
}

void CSortedGrid::OnInitialUpdate()
{
	CGXRecordWnd::OnInitialUpdate();	// Baseclass callen

	RegisterControl(IDS_CTRL_HEADER, new CHeaderBtnControl(this));	// Register my own headerstyle

	// globale Eigenschaften
	GetParam()->EnableMoveRows(TRUE);			// Records nach Belieben selber sortieren
//	GetParam()->EnableSelection(TRUE);
	GetParam()->SetNewGridLineMode(TRUE);
	GetParam()->EnableMoveCols(TRUE);
	GetParam()->SetSortRowsOnDblClk(FALSE);		// not in this way
//	ChangeStandardStyle(CGXStyle().SetBorders(gxBorderAll, CGXPen()
//															.SetColor(::GetSysColor(COLOR_BTNFACE))
//															.SetWidth(0)
//											 ));
//	GetParam()->SetGridLineStyle(PS_DOT);		// use dotted grid lines

//	Properties
	CGXProperties* pProp = GetParam( )->GetProperties( );
	if (NULL != pProp)
	{
		pProp->SetMarkRowHeader(TRUE);
		pProp->SetMarkColHeader(TRUE);
//		pProp->SetDisplay3dButtons(TRUE);
		pProp->SetColor(GX_COLOR_GRIDLINES, ::GetSysColor(COLOR_BTNFACE));	// Linienfarbe anpassen (dann siewht man aber keinen Rand mehr unten)
		pProp->SetColor(GX_COLOR_BACKGROUND, RGB(255, 255, 255));			// kjetzt sehen wir ihn wieder, der Hintergrund ist weiss
	}
	// setting up the Font
	CFont font;	// where we place all the stuff
	LOGFONT logFont;

	memset(&logFont, 0, sizeof(logFont));

	if (!::GetSystemMetrics(SM_DBCSENABLED)) {
	// Since design guide says toolbars are fixed height so is the font.
#ifndef _MAC
		logFont.lfHeight = -12;
#else
		logFont.lfHeight = -14;     // looks better than 12 on Mac
#endif
		logFont.lfWeight = FW_NORMAL;
		logFont.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;

	CString strDefaultFont;

		VERIFY(strDefaultFont.LoadString(IDS_DEFAULT_FONT));
		lstrcpy (logFont.lfFaceName, strDefaultFont);
		if (!font.CreateFontIndirect(&logFont))
			TRACE0("Could Not create font for controls.\n");
	} 
	
	if (NULL == (HFONT)font) {
		font.Attach (::GetStockObject(SYSTEM_FONT));
	}

	// now thers all available Info stored in font
	font.GetLogFont(&logFont);	// now in LOGFONT

 	StandardStyle()
 		.SetFont( CGXFont(logFont)
/* 			.SetFaceName(font.)*/
/* 			.SetSize(9)*/ );

	// Font auch für InfoBeam einstellen
	font.GetLogFont(&logFont);
	int oldfontHeight = logFont.lfHeight;
	logFont.lfHeight = oldfontHeight * 2 / 3;

	font.Detach();
	if (!font.CreateFontIndirect(&logFont))
		TRACE0("Could Not create font for controls.\n");
	CWnd* pWnd = GetParent();
	if (pWnd)
		pWnd ->SetFont(&font);

	logFont.lfHeight = oldfontHeight;
	// turn off horizontal lines
//	GetParam()->GetProperties()->SetDisplayHorzLines(FALSE);	// keine hor. Linien
	GetParam()->SetSmartResize(FALSE);		// immer alles neu zeichnen
	SetDrawingTechnique(gxDrawUsingMemDC);	// flickefreier

	// ColHeader Manipulating 
	ColHeaderStyle().SetControl(IDS_CTRL_HEADER);	// UserCtrl
	ColHeaderStyle().SetEnabled(TRUE);				// Aktivieren
	ColHeaderStyle().SetWrapText(FALSE);			// eine zeile (wie im Access)
	ColHeaderStyle().SetFont(CGXFont()				// dünnen text im Header
								.SetBold(false) );

	ChangeColHeaderStyle(CGXStyle().SetBorders(gxBorderAll, CGXPen().SetStyle(PS_NULL)));

	// RowHeader
	RowHeaderStyle().SetControl(IDS_CTRL_HEADER);	// UserCtrl
	ChangeRowHeaderStyle(CGXStyle().SetBorders(gxBorderAll, CGXPen().SetStyle(PS_NULL)));

	// Typedependent
	BaseStyle(GetDbParam()->m_bsBinary).ChangeStyle(
		 CGXStyle()
		.SetReadOnly(TRUE)
		.SetFont(CGXFont().SetItalic(TRUE))
 			, gxOverride);

	
	BaseStyle(GetDbParam()->m_bsDate).ChangeStyle(
		 CGXStyle()
		.SetControl(GX_IDS_CTRL_DATETIME)
//		.SetReadOnly(FALSE)
		.SetFont( CGXFont(logFont))
			, gxOverride);
	
	

	// Just to be sure that everything is redrawn
	Invalidate();

	
	// Enable Objective Grid internal update-hint mechanism

	// You should put this line as last command into OnInitialUpdate,
	// becaus as long as EnableHints is not called, the modified flag
	// of the document will not be changed.
	EnableHints();
}

BOOL CSortedGrid::OnRButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt)
{
	// Ereignis auslösen
		// Klick in Spaltenkopf
	if (0 == nRow && 0 < nCol)
	{
		DoSort(nCol);
	}
	else
	{
		// unreferenced parameters
 		nRow, nCol, nFlags;

		CMenu menu;
		VERIFY(menu.LoadMenu(IDM_VIEW_FRAME));
 
		CMenu* pPopup = menu.GetSubMenu( 0 );
		ASSERT( pPopup != NULL );
 
/*		CWorkMenu menu;
		*/
		CWnd* pWndPopupOwner = this;
		if (m_wndParent)
			pWndPopupOwner = m_wndParent;

		// display the menu
		ClientToScreen(&pt);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
			pt.x, pt.y, pWndPopupOwner);
	}




	// we processed the message
	return TRUE;
}

