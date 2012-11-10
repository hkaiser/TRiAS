// PropertySheet für TRiAS.Document.2 -----------------------------------------
// File: DOCPROPS.HXX

#if !defined(_DOCPROPS_HXX)
#define _DOCPROPS_HXX

///////////////////////////////////////////////////////////////////////////////
// verwendete Interfaces
DefineSmartInterface(Storage);
DefineSmartInterface(DataObject);

class CDocumentProperties : 
	public CPropertySheetExt 
{
public:
		CDocumentProperties (pWindow pWnd, LPCSTR pcTitle);
		~CDocumentProperties (void);

friend HRESULT CreateDataObject (WStorage &rIStg, WDataObject &rIDO);
friend HRESULT LoadPages (CPropertySheetExt &, LPCSTR pcKey, LPCSTR pcSubKey, IUnknown *pIUnkSite, LPCSTR pcProgID = NULL, int *piPage = NULL);
};


///////////////////////////////////////////////////////////////////////////////
// Klasse, welche im Container hängt 
class CHeaderEntry {
private:
	os_string m_strKey;
	os_string m_strValue;

	unsigned int m_fSystem : 1;			// SystemEintrag
	unsigned int m_fRO : 1;				// Schreibgeschützt
	unsigned int m_fDynamic : 1;		// Dynamische Property

	unsigned int m_fModified : 1;		// wurde editiert
	unsigned int m_fNotSaved : 1;		// noch nicht gespeicherter Eintrag

public:
		CHeaderEntry (void);
		CHeaderEntry (LPCSTR pcKey, LPCSTR pcValue, DWORD dwFlags);
		CHeaderEntry (const CHeaderEntry &rHdr);
		~CHeaderEntry (void) {}

// sonstige member
	bool isSystem (void) const { return m_fSystem; }
	bool isRO (void) const { return m_fRO; }
	bool isDynamic (void) const { return m_fDynamic; }

	void SetRO (bool fFlag = true) { m_fRO = fFlag ? true : false; SetDirty(); }

	bool isDirty (void) const { return m_fModified; }
	bool isNotSaved (void) const { return m_fNotSaved; }

	void SetDirty (bool fFlag = true) { m_fModified = fFlag ? true : false; }
	void SetNotSaved (bool fFlag = true) { m_fNotSaved = fFlag ? true : false; }

	const os_string &GetKey (void) const { return m_strKey; }
	const os_string &GetValue (void) const { return m_strValue; }

	void SetKey (LPCSTR pcNewKey) { m_strKey = pcNewKey; SetDirty(); }
	void SetValue (LPCSTR pcNewVal) { m_strValue = pcNewVal; SetDirty(); }

// Operatoren für STL
	bool operator== (const CHeaderEntry &r1) const
		{ return m_strKey == r1.m_strKey; }
	bool operator< (const CHeaderEntry &r1) const 
		{ return m_strKey < r1.m_strKey; }
};


///////////////////////////////////////////////////////////////////////////////
// Page zur Anzeige und Editierung des GeoDB-Headers

typedef map<HTREEITEM, CHeaderEntry, less<HTREEITEM> > CEntryList;
typedef CEntryList::value_type CEntryListPair;
typedef set<os_string, less<os_string> > CStringSet;

class CEditHeader : 
	public CPropertyPage 
{
private:
	bool IsSystemEntry (HTREEITEM hItem);
	bool KeyExists (LPCSTR pcNewText, HTREEITEM hItem = NULL);
	bool IsHeaderEntryItem (HTREEITEM hItem);
	void EditLabel (HTREEITEM hItem);
	void AdjustImage (HTREEITEM hItem);
	bool InsertNotSaved (HTREEITEM hItem, const CHeaderEntry &rHE);
	bool AdjustRO (HTREEITEM hItem, bool fRO);
	bool RetrieveRO (HTREEITEM hItem);
	bool RetrieveDynamic (HTREEITEM hItem);
	bool AddNewEntry (void);
	bool DeleteActiveKey (HTREEITEM hItem);
	bool FillTreeView (void);
	bool ChangeItemText (void);
	HTREEITEM MatchPositionToHTreeItem (UINT *puiFlags = NULL);

private:
	CEditCondRO m_mleValue;
	CTreeViewCtrl m_tvKeys;
	PushButton m_pbDelete;
	PushButton m_pbAddNewEntry;
	CheckBox m_cbRO;

	CEntryList m_Entries;		// Liste der Einträge
	HTREEITEM m_hNormal;		// Wurzel der normalen Einträge
	HTREEITEM m_hSystem;		// Wurzel der SystemEinträge

	CStringSet m_Deleted;		// gelöschte Einträge

	SingleLineEdit * m_pSLE;

	CImageList m_ilHdr;
	HMENU m_hPopupMenu;			// aktives Popupmenu

	bool m_fSystemMode;			// SystemMode
	bool m_fRO;					// Datenquelle/Projekt ist schreibgeschützt
	HPROJECT m_hPr;				// BezugsDatenquelle/-Projekt

protected:
	void OnDblClick (NotifyEvt e);
	void EditChange (ControlEvt e);
	void MenuInit (MenuInitEvt e);
	void MenuCommand (MenuCommandEvt e);
	void OnClick (NotifyEvt e);
	void OnItemExpanded (NotifyEvt e);
	void ButtonClick (ControlEvt e);
	BOOL OnOK (NotifyEvt e);
	BOOL OnSelChanging (NotifyEvt e);
	void OnEndLabelEdit (NotifyEvt e);
	BOOL OnBeginLabelEdit (NotifyEvt e);
	void OnSelChanged (NotifyEvt e);
	void WindowInit (Event e);

public:
		CEditHeader (HPROJECT hPr);
		~CEditHeader (void);

	bool AddEntry (LPCSTR pcKey, LPCSTR pcValue, DWORD dwFlags);
	void SetRO (bool fFlag = true);
	HPROJECT GetCtxHandle() { return m_hPr; }
};

// Konstanten für die ImageList -----------------------------------------------
#define	IMG_NONE		0
#define IMG_FOLDER		1
#define IMG_OPENFOLDER	2
#define IMG_STRING		3
#define IMG_NUMERIC		4
#define IMG_STRING_RO	5
#define IMG_NUMERIC_RO	6
#define IMG_OBJECT_RO	18

#endif // _DOCPROPS_HXX
