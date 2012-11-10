// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 10.01.2001 21:06:26 
//
// @doc
// @module PrintLegendLayout.h | Declaration of the <c CPrintLegendLayoutDlg> class

#if !defined(_PRINTLEGENDLAYOUT_H__C8AFFE9A_9414_41BF_AAA7_2711379F4F46__INCLUDED_)
#define _PRINTLEGENDLAYOUT_H__C8AFFE9A_9414_41BF_AAA7_2711379F4F46__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// CStaticBitmap

class CStaticBitmap :
	public FixedText
{
public:
	CStaticBitmap(pDialogWindow pParent, ResID resId) :
		FixedText (pParent, resId)
	{
	}
	~CStaticBitmap() {}

	HBITMAP SetBitmap (HBITMAP hBmp)
	{
		return (HBITMAP)ForwardEvent(STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp);
	}
};

///////////////////////////////////////////////////////////////////////////////
// CPrintLegendLayoutDlg

class CPrintLegendLayoutDlg :
	public CPropertyPage
{
public:
	CPrintLegendLayoutDlg(PrinterPars &rPP, bool &rfLegend);
	~CPrintLegendLayoutDlg();

	void ButtonClick (ControlEvt);
	void ListBoxSel (ControlEvt);
	void WindowInit (Event);
	BOOL OnSetActive (NotifyEvt e);
	BOOL OnKillActive (NotifyEvt e);
	BOOL OnOK (NotifyEvt e);

	void SaveEntries() {}

protected:
	bool InitPaperFormat();
	bool InitSizes();
	void AdjustRadios();
	bool AdjustBitmap();
	bool InitControls();
	HBITMAP GetLegendBitmap();
	bool CopyLegendToPreviewBitmap (HBITMAP hBmpPreview, HBITMAP hBmpLegend);

private:
	RadioButton m_rbLO, m_rbLU, m_rbRO, m_rbRU;
	FixedText m_ftSizes;
	ComboBox m_cbSizes;
	CStaticBitmap m_bmpPreview;		// Pseudo 'fixed'

	FixedText m_ftPosition;
	FixedText m_ftOptions;
	FixedText m_delPosition;
	FixedText m_delOptions;

	FixedText m_ftNoLegend;
	FixedText m_ftNoLegendFrame;

	bool &m_rfLegend;

	PrinterPars &m_rPP;
	PAPERFORMAT m_rgFormat;
	LEGENDPOSITION m_rgPosition;
	SIZEINDEX m_rgSizeIndex;
};

#endif // !defined(_PRINTLEGENDLAYOUT_H__C8AFFE9A_9414_41BF_AAA7_2711379F4F46__INCLUDED_)
