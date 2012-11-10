// Dialogfenster zur Einstellung der Darstellungsreihenfolge ------------------
// File: SELPRIO.HXX

#if !defined(_SELPRIO_HXX)
#define _SELPRIO_HXX

#include <selidlvc.hxx>
#include <bmpbtn.hxx>

class CPriorityEntry {
private:
	int m_iPriority;
	long m_lIdent;
	VisType m_rgVTyp;

public:
		CPriorityEntry (void)
			: m_iPriority(0), m_lIdent(0), m_rgVTyp(VT_Default) {}
		CPriorityEntry (int iPriority, long lIdent, VisType rgVTyp)
			: m_iPriority(iPriority), m_lIdent(lIdent), m_rgVTyp(rgVTyp) {}
		~CPriorityEntry (void) {}

// die operatoren werden in einer Liste nicht gebraucht
friend int operator== (const CPriorityEntry &, const CPriorityEntry &)	{ return false; }
friend int operator< (const CPriorityEntry &, const CPriorityEntry &) { return false; }

	int GetPriority (void) { return m_iPriority; }
	long GetIdent (void) { return m_lIdent; }
	VisType FVisTyp (void) { return m_rgVTyp; }
};

typedef list<CPriorityEntry> CPriorities;

class CPrioritySelDlg : public DialogWindow {
private:	// private functions
	bool RestorePriorities (void);
	bool ApplyPriorities (void);
	bool ApplyPrioritiesWithUndo (void);
	void FillPrioList (void);

private:	// private data
	CBmpButton m_pbUp;
	CBmpButton m_pbDown;
	CSelIdentListView m_lvIdentList;
	PushButton m_pbOK;
	PushButton m_pbTest;

	CIdTree &m_rIds;
	bool m_fUp;
	bool m_fDown;
	CPriorities m_PrioList;

protected:	// protected functions
	bool SwapItems (int iIndexO, int iIndexN);

// EventHandler
	void ButtonClick (ControlEvt);
	void OnItemChanged (NotifyEvt);		// ListView
	bool DrawEntireItem (DrawItemEvt);	// Element vollständig malen
	bool DrawItemFocus (DrawItemEvt);	// Element mit Focus zeichnen
	bool DrawItemSelect (DrawItemEvt);	// Element ausgewählt zeichnen
	void HelpRequest(HelpRequestEvt);	// Help gefordert
	void OnDeleteItem (NotifyEvt);
	void OnDeleteAllItems (NotifyEvt);

	void AdjustUpDown (void);

public:		// Implementation
	bool MoveItemDown (void);
	bool MoveItemUp (void);

public:
// Konstruktor/Destruktor
		CPrioritySelDlg (pWindow pW, CIdTree &rIds);
		~CPrioritySelDlg (void);

inline CIdTree &IdTree (void) { return m_rIds; }
};

HANDLEVISINFO *ctHANDLEVISINFO (short iVTyp);
void dtHANDLEVISINFO (HANDLEVISINFO *& pHVI);

#endif // _SELPRIO_HXX
