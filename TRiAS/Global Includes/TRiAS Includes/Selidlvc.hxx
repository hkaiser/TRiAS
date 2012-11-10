// Eine Listbox, die alle Identifikator/Objekttypen der Datenbasis enthält ----
// File: SELIDLVC.HXX

#if !defined(_SELIDLVC_HXX)
#define _SELIDLVC_HXX

///////////////////////////////////////////////////////////////////////////////
// Modi des ListViewCtrl's
const int SELIDMODE_MULTITYPES = 0x00;		// mehrere ObjektTypen
const int SELIDMODE_SINGLETYPE = 0x01;		// ein ObjektTyp
const int SELIDMODE_ALLIDENTS = 0x02;		// alle Idents der GeoDB
const int SELIDMODE_ALLIDENTSPBD = 0x04;	// alle Idents der Pbd
const int SELIDMODE_IDENTMODE = 0x0F;		// Maske für IdentMode

const int SELIDMODE_NOICONS = 0x8000;		// keine Bildchen
const int SELIDMODE_SHOWCONNECTIONS = 0x4000;	// Connections in separater Spalte anzeigen
const int SELIDMODE_ONLYWRITABLE = 0x2000;	// lediglich beschreibbare Idents anzeigen
const int SELIDMODE_NOQUERYDEFS = 0x1000;	// keine Zuordnungobjektklassen anzeigen (#HK000307)

const int LVEX_CASE = 0;
const int LVEX_NOCASE = 1;
const int LVEX_NUM = 2;		// integer
const int LVEX_NOSORT = 3;
const int LVEX_NUM_FLOAT = 4;
const int LVEX_LAST	= 4;	// increment this if you add more types

///////////////////////////////////////////////////////////////////////////////
// Spaltennummern und BildNummern
#define PICTURE_COLUMN		0
#define IDENT_COLUMN		1
#define KTEXT_COLUMN		2
#define CONNECTION_COLUMN	3

#define IMAGEOVL_FIRST		0
#define IMAGEOVL_LAST		14

#define IMAGESMALL_FIRST	15

#define IMAGELARGE_POINT	4
#define IMAGELARGE_LINE		5
#define IMAGELARGE_AREA		6
#define IMAGELARGE_TEXT		7

#define MINCOLWIDTH		10

inline int GetColIndex (int iOrigIndex, DWORD dwMode)
{
	return (dwMode & SELIDMODE_NOICONS) ? iOrigIndex-1 : iOrigIndex; 
}

///////////////////////////////////////////////////////////////////////////////
// 
typedef DWORD (__stdcall *SELIDOVLPROC)(INT_PTR lIdent, DWORD dwData);		// Liefert OverlayBmpNummer
typedef DWORD (__stdcall *ADDENTRYPROC)(INT_PTR lIdent, DWORD dwTypes, UINT_PTR dwData);

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
	PFNLVCOMPARE m_pFcnCmp;		// CompareFunktion
	ADDENTRYPROC m_pFcnAdd;		// Entscheiden, obs dazugehört
	DWORD m_dwData;
	bool m_fInitialized;
	CSelIdentListViewWindow *m_pControlWnd;

public:
// Konstruktor/Destruktor/Initialisierung
		CSelIdentListView (pDialogWindow pW, ResID uiRes, CSelIdentListViewWindow *pControlWnd = NULL);
		~CSelIdentListView (void);
		
	BOOL InitControl (DWORD dwOTypes, int iMode, 
			SELIDOVLPROC pFcnOvl = NULL, PFNLVCOMPARE pfnCompare = NULL, 
			DWORD dwData = 0L, ADDENTRYPROC pFcnAdd = NULL);

	void SetRedraw (BOOL fRedraw);
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

	void SelectItem (int iIndex, BOOL fSel = true);
	void SelectItemFocus (int iIndex, BOOL fSel = true);
	int GetItemFocus (void);
	BOOL UpdateImage (int iIndex);
	BOOL IsItemSelected (int iIndex);

// Initialisierungsfunktion der anfangs ausgewählten Idents
	int SelectIdent (long lIdent, short iOTyp, BOOL fSel = TRUE);
	BOOL ChangeSelectedAll (BOOL fSel);

	BOOL GetFirstIdent (long &rlIdent, short &riOTyp);
	BOOL GetNextIdent (long &rlIdent, short &riOTyp);
	BOOL GetFirstIdentEx (long &rlIdent, short &riOTyp, int &riCnt);
	BOOL GetNextIdentEx (long &rlIdent, short &riOTyp, int &riCnt);

	int GetFirstIdentInList (long &rlIdent, short &riOTyp);
	int GetNextIdentInList (long &rlIdent, short &riOTyp);
	int GetFirstIdentInListEx (long &rlIdent, short &riOTyp, int &riCnt);
	int GetNextIdentInListEx (long &rlIdent, short &riOTyp, int &riCnt);

	BOOL DecodeEntry (int iIndex, long &rlIdent, short &riOTyp);
	BOOL GetDescription (int iIndex, char *pBuffer, int iLen);

// EventHandler
	void OnDeleteItem (NM_LISTVIEW *);
	void OnDeleteAllItems (void);

// liefert Spaltenanzahl
	int GetColumnCount(void);

// Einfügen der Spalten
	virtual int InsertColumns (int iCount);  // returns number of existing columns
	virtual void DeleteAllColumns();

	bool FillWithData (bool fClear = true);		// neu mit Daten füllen
};

///////////////////////////////////////////////////////////////////////////////
// das selbe, aber subclassed
class _TRIAS03_ENTRY CSelIdentListViewWindow :
	public ControlWindow
{
protected:
	HWND m_hWnd;

#if defined(_FORCE_LEGACY_CODE)
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
	void RepaintSelectedItems();
#endif // defined(_FORCE_LEGACY_CODE)

protected:
	LRESULT Dispatch (Event e);

	inline DWORD GetStyle (void) { return (DWORD)::GetWindowLong (m_hWnd, GWL_STYLE); }

// data structure for setdata
	enum SORTORDER {
		SORTORDER_Unknown = -1,
		SORTORDER_Descending = 0,
		SORTORDER_Ascending = 1,
	};
	class ListData
	{
	public:
		ListData(const DWORD dwOld, const string &strTxt) :
			m_dwOldData(dwOld), m_strText(strTxt) {}

	private:
		DWORD m_dwOldData;
		string m_strText;

		friend CSelIdentListViewWindow;
	};
	int m_iSortedColumn;
	SORTORDER m_rgSortOrder;
	unsigned char *m_pTypes;//column sort types
	int m_nNumCols;

// memberfunctions for sortingsupport
	LRESULT OnHeaderClicked (NMHDR *pNMHDR);
	static int CALLBACK Compare (LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

public:
#if defined(_FORCE_LEGACY_CODE)
	BOOL DrawEntireItem (DrawItemEvt e);
	BOOL DrawItemFocus (DrawItemEvt e);
	BOOL DrawItemSelect (DrawItemEvt e);
#endif // defined(_FORCE_LEGACY_CODE)

	CSelIdentListViewWindow (DialogWindow *pW, UINT uiID, DWORD dwStyle = 0);
	~CSelIdentListViewWindow (void);

	inline CSelIdentListView *GetListCtrl() { return (CSelIdentListView *)GetControl(); }
	inline CSelIdentListView *operator -> ()  { return GetListCtrl(); }

#if defined(_FORCE_LEGACY_CODE)
EHighlight SetHighlightType (EHighlight hilite);
#endif // defined(_FORCE_LEGACY_CODE)

// Einfügen/Entfernen der Spalten
	virtual int InsertColumns (int iCount);		 // returns number of existing columns
	virtual void DeleteAllColumns();

	BOOL DeleteAllItems();

// SortSupport
	bool SetColumnTypes (unsigned char *pColTypes, unsigned nColCnt);
};

#endif // _SELIDLVC_HXX
 
