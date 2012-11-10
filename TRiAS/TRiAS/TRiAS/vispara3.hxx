// Veraendern der VisAttribute eines Identifikators ---------------------------
// File: VISPARAM.HXX

#if !defined(_VISPARAM_HXX)
#define _VISPARAM_HXX

///////////////////////////////////////////////////////////////////////////////
// verwendete Interfaces
//DefineSmartInterface(Storage);
//DefineSmartInterface(DataObject);

class DatenBasisObjekt;

class VisInfoDlg : 
	public CPropertySheet 
{
public:
		VisInfoDlg (pWindow pW);
		~VisInfoDlg (void);

//friend HRESULT CreateDataObject (WStorage &rIStg, WDataObject &rIDO);
//friend HRESULT LoadPages (CPropertySheetExt &, LPCSTR pcKey, LPCSTR pcSubKey);
};

///////////////////////////////////////////////////////////////////////////////
// eine Page

#include <selidlvc.hxx>
#include <InPlaceCombo.h>

#define WM_SHOWCOMBO	(WM_USER+2000)
#define WM_DESTROYCOMBO	(WM_USER+2001)

class CSelectIdentList :
	public CSelIdentListViewWindow
{
private:
	int m_iUpper;
	int m_iLower;
	UINT m_uiID;
	int m_iLastFocusItem;
	bool m_fScaleDirty;

	CInPlaceCombo *m_pList;

protected:
	int HitTestEx(POINT point, int *col);

	void MouseButtonDn (MouseEvt e);
	void HorizScroll (ScrollEvt e);
	void VertScroll (ScrollEvt e);
	LRESULT Dispatch (Event e);
	void FocusChange (FocusChangeEvt e);
	void WindowInit (Event e);

	int UpperBoundIndex (int iRow, int iCol);
	int LowerBoundIndex (int iRow, int iCol);
	int FindIndex (int iFirst, int iRow, int iCol, string &rStr);
	void SetScaleText (bool fAnyScale, int iIndex, int iSubItem, LPSTR pText);

public:
	CSelectIdentList (DialogWindow *pW, UINT uiID, DWORD dwStyle = 0);
	~CSelectIdentList();

	ComboBox* ShowInPlaceList (int nItem, int nCol, CStringList &lstItems, int nSel, LPCSTR pcInitEntry);

	void OnEndLabelEdit (NMHDR *pNMHDR, LRESULT *plResult);
	void OnCloseup (UINT uiID);
	bool OnShowCombo (int index, int colnum);

	void SetColumns (int iUpper, int iLower);

	bool IsScaleDirty() { return m_fScaleDirty ? true : false; }
	int GetLastItemFocus() { return m_iLastFocusItem; }

	int InsertColumns (int iCount);		// zusätzliche Spalten einfügen
};

class CVisInfoPage : 
	public CPropertyPage 
{
private:
	PushButton m_pbDefine;
	PushButton m_pbSetScaleUpper;
	PushButton m_pbSetScaleLower;
	RadioButton m_rbRGB;
	RadioButton m_rbHSB;
	CSelectIdentList m_lvIdentList;
	GroupBox m_gbRGBHSB;
	
	long m_lID;
	char *m_pIDString;
	DatenBasisObjekt &m_rDBO;

	VisType m_rgVTyp;			// behandelter Objekttyp

	bool m_fI;
	bool m_fO;
	bool m_fRGBHSB;

	int m_iColUpper;
	int m_iColLower;

private:	// functions
	void AdjustHSB (bool fHSB);

protected:
	void ButtonClick (ControlEvt);
	void OnItemChanged (NotifyEvt);		// ListView

//	void FillEntryList (void);
//	Bool AddEntry (CIdentifikator *pId, char *pKT);
	void ChangeVisEntry (VisType iVTyp);

	void WindowInit (Event);
	BOOL OnOK (NotifyEvt);
	void OnDeleteItem (NotifyEvt);
	void OnDeleteAllItems (NotifyEvt);
	void HelpRequest (HelpRequestEvt);

	int OnSetActive (NotifyEvt);
	BOOL OnKillActive (NotifyEvt);

#if defined(_FORCE_LEGACY_CODE)
	BOOL DrawEntireItem (DrawItemEvt e);
	BOOL DrawItemFocus (DrawItemEvt e);
	BOOL DrawItemSelect (DrawItemEvt e);
#endif // defined(_FORCE_LEGACY_CODE)

	void AdjustButton (short iIndex);
	void ChangeButton (bool fI, bool fO);

	LRESULT Dispatch (Event e);
	bool OnNotify (NotifyEvt e);

friend bool EXPORTTRIAS FillIdentSelBox (void *pObj, void *pData);

public:
// Konstruktor/Destruktor
		CVisInfoPage (DatenBasisObjekt &, long Id, VisType rgVTyp, 
					  LPCSTR pcCation, bool fRGBHSB = true);
		~CVisInfoPage (void);

// sonstige Memberfunktionen
	long GetVisIdent (void) { return m_lID; }
	char *IDString (void) { return m_pIDString; }
	ErrCode ChangeIdVisInfo (VisType = VT_Default);
	DatenBasisObjekt & DBO (void) { return m_rDBO; }
	VisType VTyp (void) { return m_rgVTyp; }

// Maßstäbe behandlen
	bool InitScaleData (void);
	bool InitIdentScaleData (int iIndex, long lUpper, long lLower);
	bool GetIdentScaleData (int iIndex, long &rlUpper, long &rlLower);
};

HANDLEVISINFO *ctHANDLEVISINFO (short iVTyp);
void dtHANDLEVISINFO (HANDLEVISINFO *& pHVI);

#endif // _VISPARAM_HXX

