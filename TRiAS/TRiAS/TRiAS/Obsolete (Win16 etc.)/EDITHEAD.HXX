// GeoDB-Header editieren -- Klassendefinitionen
// File: EDITHEAD.HXX

// IRISWIN: %W%	%E%

#ifndef _EDITHEAD_HXX
#define _EDITHEAD_HXX

#include "hdrentry.hxx"

inline void *GetEntryKey (void *pObj);

#if !defined(NOHEADERSATZLISTE)
// Liste der HeaderEintr�ge ---------------------------------------------------
class HeaderSatzListe : public CTree {
protected:
	void UserDelete (void *);	// Beseitigen eines HeaderEintrages

public:
// Konstruktor
		HeaderSatzListe (void) :
			CTree (GetEntryKey, StrCmp) {}

// Destruktor
		~HeaderSatzListe (void) { EveryDelete (); }
};

#if !defined(NOEXTTABLE)
// Klasse ExtTable erlaubt Zugriff auf den aktuellen Eintrag im KeyContainer
class ExtTable : public CTable {
public:
// Konstruktoren
		ExtTable (CKeyContainer &K) : CTable (K) {}
		ExtTable (CTable &T) : CTable (T) {}

// zus�tzliche Memberfunktion
	CNode * CurrentNode (void) { return m_pCurrentNode; }
};
#endif // NOEXTTABLE

// Deklaration der zus�tzlich notwendigen Klassen -----------------------------
// (HeaderEntryCreator und HeaderEntryLock)
DeclareLock (HeaderSatzListe, HeaderEntry);

#endif // NOHEADERSATZLISTE

#if !defined(NOEDITHEADERDLG)
// GeoDB-Header editieren -- Dialogfensterklasse ------------------------------
class EditHeaderDialog : public DialogWindow {
// ListBox f�r HeaderKey's
	ListBox KeyList;
// Buttons
	PushButton OKButton, CancelButton, SaveButton, DeleteButton;
#if !defined(WIN32)
	PushButton HelpButton;
#endif // WIN32

// EditFenster
	SingleLineEdit SLE_HeaderKey;
	MultiLineEdit MLE_HeaderText;
// Statischer Text
	FixedText GeoDBName;
// Zwischenspeicher f�r alte Fehlermodi
	INT_FUNC *e_badlen, *w_notfound;
// ROMode der aktuellen DB
	short _ROMode;

	GeoDB &_DB;		// BezugsDB

// EventHandler
	void ListBoxSel (ControlEvt e);		// Click in ListBox
	void ListBoxClk (ControlEvt e);		// DoubleClick in ListBox
	void ButtonClick (ControlEvt e);	// Button bet�tigt
	void EditChange (ControlEvt e);		// EditControl ver�ndert
	void EditFocusChg (EditFocusChgEvt e);	// Focus zu/von EditControl 

// Liste der HeaderEintr�ge
	HeaderSatzListe _Header;	// Liste der editierten Headereintr�ge

// sonstige Memberfunktionen
	char *RetrieveHeaderText (char *Key);	// HeaderText zu Key suchen
	void DeleteEntry (void);	// EntryEintrag l�schen
	void SaveEntry (void);		// EntryEintrag abspeichern
inline void DeleteKeyList (void);	// ListBoxEintr�ge in KeyList l�schen
	Bool AsktoSaveHeaderEntry (void);	// Headerntry speichern, wenn
						// er ge�ndert wurde
								
public:
// Konstruktoren
		EditHeaderDialog (pWindow parentWnd, DatenBasisObjekt &DBO);

// Memberfunktionen
	ErrCode ScanGeoDBHeader (void);		// HeaderSatzListe aufbauen
// Parameter f�r Virtual Function Every f�r Container
friend 	void EXPORTTRIAS FillKeyList (void *);		// Item zu ListBox hinzuf�gen
friend	void EXPORTTRIAS WriteHeaderEntry (void *);		// Item in geoDB schreiben

// Destruktor
		~EditHeaderDialog (void);
};
#endif // NOEDITHEADERDLG

#if !defined(NOEXTCONTROLEVT)
// Erweiterte EventKlasse, die Zugriff auf Eventelemente erlaubt --------------
class ExtControlEvt : public ControlEvt {
public:
// Memberfunktionen
	uint wMsg (void)	{ return Event :: wMsg; }
	uint wParam (void) 	{ return Event :: wParam; }
	ulong lParam (void)	{ return Event :: lParam; }
	void *EvtXtra (void) 	{ return Event :: EvtExtra; }
};
#endif // NOEXTCONTROLEVT

#endif // _EDITHEAD_HXX
