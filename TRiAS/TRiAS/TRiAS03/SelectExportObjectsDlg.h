// $Header: $
// Copyright© 1999 Fernerkundungszentrum Potsdam GmbH, All rights reserved
//
// @doc
// @module SelectExportObjectsDlg.h | Declaration of the <c CSelectExportObjectsDlg> class

#if !defined(__SELECTEXPORTOBJECTSDLG_H_)
#define __SELECTEXPORTOBJECTSDLG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TRiAS03.h"       // main symbols
#include <DatasourceIcon.h>

/////////////////////////////////////////////////////////////////////////////
// CSelectExportObjectsDlg dialog

/////////////////////////////////////////////////////////////////////////////
// Satz von vorgegebenen Datenquellen 
typedef set<HPROJECT> CDataSources;

class CSelectExportObjectsDlg : 
	public CPropertyPage
{
// Construction
public:
	CSelectExportObjectsDlg(ResID uiDlg, LPCSTR pcCaption);
	~CSelectExportObjectsDlg();

// Dialog Data
	enum { IDD = IDD_SELECTFROMDS_WIZ, IDD_PP = IDD_SELECTFROMDS_WIZPP };

public:
	void SetFlags (DWORD dwFlags) { m_dwFlags = dwFlags; }
	static CSelectExportObjectsDlg *CreateInstance (ResID uiDlg, LPCSTR pcCaption);

	BOOL FInit() { return TRUE; }
	HPROPSHEETPAGE CreatePage (void) { return CPropertyPage::CreatePage(); }

	HRESULT GetDataSources (CDataSources &rDS);

// Implementation
protected:
	void WindowInit (Event e);
	void ButtonClick (ControlEvt e);
	void OnItemChanged (NotifyEvt e);
	int OnWizNext (NotifyEvt e);
	int OnWizFinish (NotifyEvt e);
	int OnSetActive (NotifyEvt e);

	void AdjustSheetButtons();
	BOOL GetDisableNextPage();
	BOOL FillDataSources();
	HRESULT PrepareResult (void);

private:
// Listcontrol, welches annähernd wie eine MultiSelListbox aussieht
	class COpenProjects :
		public CListViewCtrl
	{
	public:
		COpenProjects(pDialogWindow parent, ResID id);
		~COpenProjects();

	// MultiSelListBox interface
		int GetCount()
		{
			return GetItemCount();
		}
		int GetNoSelected (void)
		{
			return GetSelectedCount();
		}
		int GetFirstSelected (void)
		{
			m_iLast = GetNextItem(-1, LVNI_ALL|LVNI_SELECTED);
			return m_iLast;
		}
		int GetNextSelected (void)
		{
			m_iLast = GetNextItem(m_iLast, LVNI_ALL|LVNI_SELECTED);
			return m_iLast;
		}
		void ChangeSelected (Range r, bool fSelect = true)
		{
			for (int iIndex = r.Min(); iIndex <= r.Max(); ++iIndex)
				SetItemState(iIndex, fSelect ? LVIS_SELECTED : 0, LVIS_SELECTED);
		}
		int AddString (const char *pStringToAdd, int iPos = -1)
		{
			if (-1 == iPos)
				iPos = GetItemCount();
			return InsertItem(iPos, pStringToAdd);
		}
		int SetItemData (int iIndex, DWORD dwData)
		{
		// Bildchen berechnen und Daten ans Item hängen
		DWORD dwBmp = datasource_icon::GetBitmapIndex(HPROJECT(dwData));

			return SetItem (iIndex, 0, LVIF_IMAGE|LVIF_PARAM, NULL, dwBmp, 0, 0, dwData);
		}

		BOOL FInit();
		void FitColumn (int iCol = 0);

	protected:
		void SetRedraw (BOOL fRedraw);
		int GetColumnCount(void);

	private:
		CImageList m_ilProjects;
		int m_iLast;
	};

	COpenProjects m_lbDataSources;
	PushButton m_pbSelectAll;

	DWORD m_dwFlags;
	long m_lCntOpen;

	CDataSources m_DS;		// Datenquellen-Ergebnismenge 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__SELECTEXPORTOBJECTSDLG_H_)
