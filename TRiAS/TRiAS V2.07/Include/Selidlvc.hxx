// Eine Listbox, die alle Identifikator/Objekttypen der Datenbasis enthält ----
// File: SELIDLVC.HXX

#if !defined(_SELIDLVC_HXX)
#define _SELIDLVC_HXX

typedef DWORD (*SELIDOVLPROC)(long lIdent, DWORD dwData);		// Liefert OverlayBmpNummer

class _TRIAS03_ENTRY CSelIdentItem {
public:
	ULONG m_ulIdent;
	int m_iOTypes;

		CSelIdentItem (ULONG ulIdent, int iOTypes)
			: m_ulIdent(ulIdent), m_iOTypes(iOTypes) {}
};

class CSelIdentListViewWindow;

class _TRIAS03_ENTRY CSelIdentListView : 
	public CListViewCtrl 
{
private:
	char *m_pBuff;				// multi purpose buffer
	long m_lLastIdent;
	short m_iLastTypes;
	int m_iCurrItem;

	DWORD m_iOTypes;			// enthaltene OTypen
	int m_iMode;				// Darstellungsmode
	CImageList m_ilType;		// Bildchen für ListView
	SELIDOVLPROC m_pFcnOvl;		// OverlayNummer liefert
	DWORD m_dwData;
	
	CSelIdentListViewWindow *m_pControlWnd;

public:
// Konstruktor/Destruktor/Initialisierung
		CSelIdentListView (pDialogWindow pW, ResID uiRes, CSelIdentListViewWindow *pControlWnd = NULL);
		~CSelIdentListView (void);
		
	bool InitControl (DWORD dwOTypes, int iMode, 
			SELIDOVLPROC pFcnOvl = NULL, PFNLVCOMPARE pfnCompare = NULL, 
			DWORD dwData = 0L);

	void SetRedraw (bool fRedraw);
	void FitColumn (int iCol = -1);

// ZugriffsFunktionen auf ausgewählte Identifikatoren
	int GetFirstSelected (void);
	int GetNextSelected (void);
	int GetLastSelected (void);
	int GetPrevSelected (void);

	int GetFirstInList (void);
	int GetNextInList (void);
	int GetLastInList (void);
	int GetPrevInList (void);

	void SelectItem (int iIndex, bool fSel = true);
	void SelectItemFocus (int iIndex, bool fSel = true);
	int GetItemFocus (void);
	bool UpdateImage (int iIndex);
	bool IsItemSelected (int iIndex);

// Initialisierungsfunktion der anfangs ausgewählten Idents
	int SelectIdent (long lIdent, short iOTyp, bool fSel = TRUE);
	bool ChangeSelectedAll (bool fSel);

	bool GetFirstIdent (long &rlIdent, short &riOTyp);
	bool GetNextIdent (long &rlIdent, short &riOTyp);
	bool GetFirstIdentEx (long &rlIdent, short &riOTyp, int &riCnt);
	bool GetNextIdentEx (long &rlIdent, short &riOTyp, int &riCnt);

	int GetFirstIdentInList (long &rlIdent, short &riOTyp);
	int GetNextIdentInList (long &rlIdent, short &riOTyp);
	int GetFirstIdentInListEx (long &rlIdent, short &riOTyp, int &riCnt);
	int GetNextIdentInListEx (long &rlIdent, short &riOTyp, int &riCnt);

	bool DecodeEntry (int iIndex, long &rlIdent, short &riOTyp);
	bool GetDescription (int iIndex, char *pBuffer, int iLen);

// EventHandler
	void OnDeleteItem (NM_LISTVIEW *);
	void OnDeleteAllItems (void);

// liefert Spaltenanzahl
	int GetColumnCount(void);

// Einfügen der Spalten
	virtual int InsertColumns (int iCount);  // returns number of existing columns
};

const int SELIDMODE_MULTITYPES = 0x00;		// mehrere ObjektTypen
const int SELIDMODE_SINGLETYPE = 0x01;		// ein ObjektTyp
const int SELIDMODE_ALLIDENTS = 0x02;		// alle Idents der GeoDB
const int SELIDMODE_ALLIDENTSPBD = 0x04;	// alle Idents der Pbd

const int SELIDMODE_NOICONS = 0x8000;		// keine Bildchen

///////////////////////////////////////////////////////////////////////////////
// das selbe, aber subclassed
class _TRIAS03_ENTRY CSelIdentListViewWindow :
	public ControlWindow
{
protected:
	HWND m_hWnd;

public:
	enum EHighlight {
		HIGHLIGHT_NORMAL, 
		HIGHLIGHT_ALLCOLUMNS, 
		HIGHLIGHT_ROW
	};

protected:
	EHighlight m_nHighlight;		// Indicate type of selection highlighting

	void Expose (ExposeEvt e);
	void FocusChange (FocusChangeEvt e);

	LRESULT Dispatch (Event e);

	void RepaintSelectedItems();
	inline DWORD GetStyle (void) { return (DWORD)::GetWindowLong (m_hWnd, GWL_STYLE); }

public:
	bool DrawEntireItem (DrawItemEvt e);
	bool DrawItemFocus (DrawItemEvt e);
	bool DrawItemSelect (DrawItemEvt e);
	
	CSelIdentListViewWindow (DialogWindow *pW, UINT uiID, DWORD dwStyle = 0);
	~CSelIdentListViewWindow (void);

	inline CSelIdentListView *GetListCtrl() { return (CSelIdentListView *)GetControl(); }
	inline CSelIdentListView *operator -> ()  { return GetListCtrl(); }

	EHighlight SetHighlightType (EHighlight hilite);

// Einfügen der Spalten
	virtual int InsertColumns (int iCount);  // returns number of existing columns
};

#endif // _SELIDLVC_HXX
 
