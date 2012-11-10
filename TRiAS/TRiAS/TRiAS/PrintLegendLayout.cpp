// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 10.01.2001 21:27:10 
//
// @doc
// @module PrintLegendLayout.cpp | Definition of the <c CPrintLegendLayoutDlg> class

#include "triaspre.hxx"

#if defined(_USE_LEGEND_LAYOUT)

#include <printer.hxx>

#include "triasres.h"

#include "prntlayt.hxx"
#include "PrintLegendLayout.h"

///////////////////////////////////////////////////////////////////////////////
// CPrintLegendLayoutDlg
#pragma warning (disable:4355)

CPrintLegendLayoutDlg::CPrintLegendLayoutDlg(PrinterPars &rPP, bool &rfLegend) :
	CPropertyPage(IDD_PRINTLAYOUT_LEGEND, ResString (IDS_LEGENDECAP, 32)),
	m_rPP(rPP), m_rfLegend(rfLegend),
	m_ftPosition(this, IDC_STATIC_POSITION),
	m_ftOptions(this, IDC_STATIC_OPTIONS),
	m_delPosition(this, IDC_DELIMITER_POSITION),
	m_delOptions(this, IDC_DELIMITER_OPTIONS),
	m_ftNoLegend(this, IDC_STATIC_NOLEGEND),
	m_ftNoLegendFrame(this, IDC_STATIC_NOLEGEND_FRAME),
	m_rbLU(this, IDC_POSITION_LU),
	m_rbLO(this, IDC_POSITION_LO),
	m_rbRU(this, IDC_POSITION_RU),
	m_rbRO(this, IDC_POSITION_RO),
	m_ftSizes(this, IDC_STATIC_SIZES),
	m_cbSizes(this, IDC_SIZES),
	m_bmpPreview(this, IDC_PREVIEW)
{
	m_rgFormat = PAPERFORMAT_Portrait;
	m_rgPosition = LEGENDPOSITION_RO;
	m_rgSizeIndex = SIZEINDEX_100;
}

#pragma warning (default:4355)

CPrintLegendLayoutDlg::~CPrintLegendLayoutDlg()
{
HBITMAP hBmpOld = m_bmpPreview.SetBitmap(NULL);

	if (NULL != hBmpOld)
		DeleteObject (hBmpOld);
}

bool CPrintLegendLayoutDlg::InitPaperFormat()
{
const DEVMODE *pDevMode = m_rPP.DeviceMode();

	_ASSERTE(NULL != pDevMode);
	if (NULL == pDevMode) 
		return false;

	if (pDevMode -> dmFields & DM_ORIENTATION) {	// Orientierung gegeben
		_ASSERTE(pDevMode -> dmOrientation == DMORIENT_LANDSCAPE || 
				 pDevMode -> dmOrientation == DMORIENT_PORTRAIT);

		if (DMORIENT_PORTRAIT == pDevMode -> dmOrientation)
			m_rgFormat = PAPERFORMAT_Portrait;
		else
			m_rgFormat = PAPERFORMAT_Landscape;
	}
	return true;
}

bool CPrintLegendLayoutDlg::InitSizes()
{
	m_cbSizes.Clear();

ResString resSizes(IDS_LEGENDSIZES, 128);

	_ASSERTE(resSizes.Len() > 0);

os_string strSizes (resSizes);
size_t iPos = strSizes.find_first_of('\n');

	while (os_npos != iPos) {
		m_cbSizes.AddString(strSizes.substr(0, iPos).c_str());
		strSizes = strSizes.substr(iPos+1);
		iPos = strSizes.find_first_of('\n');
	}
	return true;
}

void CPrintLegendLayoutDlg::AdjustRadios ()
{
	m_rbLU.SetState(false);
	m_rbLO.SetState(false);
	m_rbRU.SetState(false);
	m_rbRO.SetState(false);

	if (m_rgSizeIndex == SIZEINDEX_100) {
		m_rbLU.Disable();
		m_rbRU.Disable();
	} else {
		m_rbLU.Enable();
		m_rbRU.Enable();
	}

	switch (m_rgPosition) {
	case LEGENDPOSITION_LO:
		m_rbLO.SetState(true);
		break;

	case LEGENDPOSITION_LU:
		if (m_rgSizeIndex == SIZEINDEX_100)
			m_rbLO.SetState(true);
		else
			m_rbLU.SetState(true);
		break;

	case LEGENDPOSITION_RO:
		m_rbRO.SetState(true);
		break;

	case LEGENDPOSITION_RU:
		if (m_rgSizeIndex == SIZEINDEX_100)
			m_rbRO.SetState(true);
		else
			m_rbRU.SetState(true);
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// die alles entscheidende Funktion ...
namespace {
// Bitmaps (in Abhängigkeit vom Papierformat)
	const UINT s_uibmpPortrait[] = { 
		IDB_LEGEND_LAYOUTH2, 
		IDB_LEGEND_LAYOUTH1, 
		IDB_LEGENDH,
	};
	const UINT s_uibmpLandscape[] = { 
		IDB_LEGEND_LAYOUTQ2, 
		IDB_LEGEND_LAYOUTQ1, 
		IDB_LEGENDQ,
	};
	const int LEGENDINDEX = 2;

// Koordinaten der jeweils linken oberen bzw. unteren Ecke der Legende
	const int s_ibmpPosPortrait[] = {
		83, 25,		// links oben
		83, 179,	// links unten
		168, 25,	// rechts oben
		168, 179,	// rechts unten
	};
	const int s_ibmpPosLandscape[] = {
		26, 28,		// links oben
		26, 175,	// links unten
		205, 28,	// rechts oben
		205, 175,	// rechts unten
	};

// Höhen der Legenden
	const int s_ibmpWidthPortrait = 22;
	const int s_ibmpHeightPortrait[] = {
		154, 115, 77, 54, 38,
	};
	const int s_ibmpWidthLandscape = 45;
	const int s_ibmpHeightLandscape[] = {
		147, 111, 74, 51, 34,
	};
}

HBITMAP CPrintLegendLayoutDlg::GetLegendBitmap()
{
Bitmap bmp (ResID ((PAPERFORMAT_Portrait == m_rgFormat) ? s_uibmpPortrait[LEGENDINDEX] : s_uibmpLandscape[LEGENDINDEX]));

	if (NULL == bmp.Handle(API_BITMAP_HBITMAP))
		return NULL;

Dimension dimBmp (bmp.GetSize());		// Größe des zu kopierenden Legendenbereiches

	dimBmp.Width() /= SIZEINDEX_MAX;
	dimBmp.Height() = (PAPERFORMAT_Portrait == m_rgFormat) ? s_ibmpHeightPortrait[m_rgSizeIndex] : s_ibmpHeightLandscape[m_rgSizeIndex];

HDC hDCTarget = CreateCompatibleDC(NULL);
HBITMAP hBmpTarget = CreateCompatibleBitmap(hDCTarget, dimBmp.Width(), dimBmp.Height());
HDC hDCSrc = CreateCompatibleDC(NULL);

HBITMAP hBmpOld1 = (HBITMAP)SelectObject(hDCSrc, bmp.Handle(API_BITMAP_HBITMAP));
HBITMAP hBmpOld2 = (HBITMAP)SelectObject(hDCTarget, hBmpTarget);

int iWidthSrc = (PAPERFORMAT_Portrait == m_rgFormat) ? s_ibmpWidthPortrait : s_ibmpWidthLandscape;

	BitBlt (hDCTarget, 0, 0, dimBmp.Width(), dimBmp.Height(), hDCSrc, m_rgSizeIndex*iWidthSrc, 0, SRCCOPY);

	SelectObject(hDCTarget, hBmpOld2);
	SelectObject(hDCSrc, hBmpOld1);
	DeleteDC (hDCSrc);
	DeleteDC (hDCTarget);
	return hBmpTarget;
}

bool CPrintLegendLayoutDlg::CopyLegendToPreviewBitmap (HBITMAP hBmpPreview, HBITMAP hBmpLegend)
{
	if (NULL == hBmpPreview || NULL == hBmpLegend)
		return false;

Bitmap bmpLeg (hBmpLegend);
Dimension dimLeg (bmpLeg.GetSize());

HDC hDCTarget = CreateCompatibleDC(NULL);
HDC hDCSrc = CreateCompatibleDC(NULL);

HBITMAP hBmpOld1 = (HBITMAP)SelectObject(hDCSrc, hBmpLegend);
HBITMAP hBmpOld2 = (HBITMAP)SelectObject(hDCTarget, hBmpPreview);

Point ptDest;

	if (SIZEINDEX_100 == m_rgSizeIndex || !(m_rgPosition & LEGENDPOSITION_VertMask)) {
	// oben ansetzen
	int iIndex = (m_rgPosition & LEGENDPOSITION_HorzMask) ? 4 : 0;

		ptDest.X() = (PAPERFORMAT_Portrait == m_rgFormat) ? s_ibmpPosPortrait[iIndex] : s_ibmpPosLandscape[iIndex];
		ptDest.Y() = (PAPERFORMAT_Portrait == m_rgFormat) ? s_ibmpPosPortrait[iIndex+1] : s_ibmpPosLandscape[iIndex+1];
	}
	else {
	// von unten positionieren
	int iIndex = (m_rgPosition & LEGENDPOSITION_HorzMask) ? 6 : 2;

		ptDest.X() = (PAPERFORMAT_Portrait == m_rgFormat) ? s_ibmpPosPortrait[iIndex] : s_ibmpPosLandscape[iIndex];
		ptDest.Y() = (PAPERFORMAT_Portrait == m_rgFormat) ? s_ibmpPosPortrait[iIndex+1] : s_ibmpPosLandscape[iIndex+1];
		ptDest.Y() -= dimLeg.Height();
	}

	BitBlt (hDCTarget, ptDest.GetX(), ptDest.GetY(), dimLeg.Width(), dimLeg.Height(), hDCSrc, 0, 0, SRCCOPY);

	SelectObject(hDCTarget, hBmpOld2);
	SelectObject(hDCSrc, hBmpOld1);
	DeleteDC (hDCSrc);
	DeleteDC (hDCTarget);
	return true;
}

bool CPrintLegendLayoutDlg::AdjustBitmap()
{
int iIndex = int(m_rgPosition & LEGENDPOSITION_HorzMask);
Bitmap bmp (ResID ((PAPERFORMAT_Portrait == m_rgFormat) ? s_uibmpPortrait[iIndex] : s_uibmpLandscape[iIndex]));

// Bitmap der Legende erzeugen
HBITMAP hBmpLegend = GetLegendBitmap();

	_ASSERTE(NULL != hBmpLegend);
	CopyLegendToPreviewBitmap(bmp.Handle(API_BITMAP_HBITMAP), hBmpLegend);
	DeleteObject(hBmpLegend);

// neue Bitmap setzen
HBITMAP hBmpOld = m_bmpPreview.SetBitmap(bmp.Detach());

	if (NULL != hBmpOld)
		DeleteObject (hBmpOld);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// in Abhängigkeit vom Checkstatus der Legende auf der anderen Seite, hier
// die passenden Controls einblenden
bool CPrintLegendLayoutDlg::InitControls()
{
	if (m_rfLegend) {
		m_ftPosition.Show();
		m_ftOptions.Show();
		m_delPosition.Show();
		m_delOptions.Show();
		m_rbLU.Show();
		m_rbLO.Show();
		m_rbRU.Show();
		m_rbRO.Show();
		m_ftSizes.Show();
		m_cbSizes.Show();
		m_bmpPreview.Show();

		m_ftNoLegend.Hide();
		m_ftNoLegendFrame.Hide();
		return true;
	}
	else {
		m_ftPosition.Hide();
		m_ftOptions.Hide();
		m_delPosition.Hide();
		m_delOptions.Hide();
		m_rbLU.Hide();
		m_rbLO.Hide();
		m_rbRU.Hide();
		m_rbRO.Hide();
		m_ftSizes.Hide();
		m_cbSizes.Hide();
		m_bmpPreview.Hide();

		m_ftNoLegend.Show();
		m_ftNoLegendFrame.Show();
		return false;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Message Handler

// Implementation of WindowInit
void CPrintLegendLayoutDlg::WindowInit(Event)
{
	m_ftPosition.FInit();
	m_ftOptions.FInit();
	m_delPosition.FInit();
	m_delOptions.FInit();
	m_ftNoLegend.FInit();
	m_ftNoLegendFrame.FInit();

	m_rbLU.FInit();
	m_rbLO.FInit();
	m_rbRU.FInit();
	m_rbRO.FInit();
	m_ftSizes.FInit();
	m_cbSizes.FInit();
	m_bmpPreview.FInit();

	if (InitControls()) {
		InitPaperFormat();			// Feststellen, obs Hoch- oder Querformat ist
		InitSizes();

		AdjustRadios();
		m_cbSizes.ChangeCurrentIndex(m_rgSizeIndex);

		AdjustBitmap();
	}
}

// Implementation of ButtonClick
void CPrintLegendLayoutDlg::ButtonClick(ControlEvt e)
{
	switch ((UINT)e.GetControlID()) {
	case IDC_POSITION_LU:
		m_rgPosition = LEGENDPOSITION_LU;
		break;

	case IDC_POSITION_LO:
		m_rgPosition = LEGENDPOSITION_LO;
		break;

	case IDC_POSITION_RU:
		m_rgPosition = LEGENDPOSITION_RU;
		break;

	case IDC_POSITION_RO:
		m_rgPosition = LEGENDPOSITION_RO;
		break;
	}

	AdjustRadios();
	AdjustBitmap();
}

// Implementation of ListBoxSel
void CPrintLegendLayoutDlg::ListBoxSel(ControlEvt)
{
int iIndex = m_cbSizes.GetCurrentIndex();

	_ASSERTE(-1 != iIndex && iIndex < SIZEINDEX_MAX);
	m_rgSizeIndex = SIZEINDEX(iIndex);
	AdjustRadios();
	AdjustBitmap();
}

// Implementation of OnSetActive
BOOL CPrintLegendLayoutDlg::OnSetActive(NotifyEvt e)
{
	if (InitControls()) {
		InitPaperFormat();			// Feststellen, obs Hoch- oder Querformat ist
		InitSizes();

		AdjustRadios();
		m_cbSizes.ChangeCurrentIndex(m_rgSizeIndex);

		AdjustBitmap();
	}
	return TRUE;
}

BOOL CPrintLegendLayoutDlg::OnOK(NotifyEvt e)
{
CPrintLayoutSheet *pSheet = (CPrintLayoutSheet *)GetPropertySheet();

	_ASSERTE(NULL != pSheet);

// Resultate am Sheet setzen
	pSheet -> SetPaperFormat(m_rgFormat);
	pSheet -> SetLegendPosition(m_rgPosition);
	pSheet -> SetSizeIndex(m_rgSizeIndex);
	return FALSE;		// allows operation
}

BOOL CPrintLegendLayoutDlg::OnKillActive(NotifyEvt e)
{
CPrintLayoutSheet *pSheet = (CPrintLayoutSheet *)GetPropertySheet();

	_ASSERTE(NULL != pSheet);

// Resultate am Sheet setzen
	pSheet -> SetPaperFormat(m_rgFormat);
	pSheet -> SetLegendPosition(m_rgPosition);
	pSheet -> SetSizeIndex(m_rgSizeIndex);
	return FALSE;		// allows operation
}

#endif // defined(_USE_LEGEND_LAYOUT)
