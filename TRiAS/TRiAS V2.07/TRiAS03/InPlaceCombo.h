// InPlaceCombo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Liste der Items, mit denen die ComboBox initialisiert wird
// STL-related stuff ----------------------------------------------------------
#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)		// debug info truncated
#include <ospace/std/list>

typedef list<os_string> CStringList;

/////////////////////////////////////////////////////////////////////////////
// CInPlaceCombo window

class CInPlaceCombo : 
	public ControlWindow
{
// Construction
public:
	CInPlaceCombo(pWindow pW, CvID uiID, RECT *prc, DWORD dwStyle);
	bool Create (int iItem, int iSubItem, CStringList &rlstItems, int nSel);

// Attributes
public:
	inline ComboBox *GetComboBox() { return (ComboBox *)GetControl(); }
	inline operator ComboBox *() { return (ComboBox *)GetControl(); }

// Operations
public:
	void OnCloseup();

	void SetHorizontalExtent (int iExtend);
	int SetItemHeight (int iIndex, UINT iHeight);

// Overrides
protected:
	BOOL PreTranslateMsg (MSG* pMsg);
	void FocusChange (FocusChangeEvt e);
	void KeyDown (KeyEvt e);
	LRESULT Dispatch (Event e);

// Implementation
public:
	~CInPlaceCombo();

private:
	DWORD m_dwStyle;
	Font *m_pFont;

	int m_iItem;
	int m_iSubItem;
	bool m_bESC;				// To indicate whether ESC key was pressed
};

/////////////////////////////////////////////////////////////////////////////
