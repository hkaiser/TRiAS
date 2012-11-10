// Klassendefinitionene fuer Merkmalseditierung
// File: MERKEDIT.HXX

#if !defined(_MERKEDIT_HXX)
#define _MERKEDIT_HXX

#if !defined(NOLISTOBJEKTDLG)

#define KEYLENGTH	64		// max. Länge eines KeyEintrages

#include "editro.hxx"		// EditControl, welches RO/nicht RO sein kann

class ListObjektInfoDialog : public DialogWindow {
private:		// Controls
	ComboBox Merkmale;
	CEditCondRO MWert;
	PushButton OKButton;
	PushButton CancelButton;
	PushButton SaveButton;
	PushButton DelButton;
#if defined(WIN16)
	PushButton HelpButton;
#endif
	FixedText ObjSpec;
	FixedText MName;
	CheckBox StandardName;
	GeoDB &m_rDB;

	char ActEntry[KEYLENGTH+1];

// Private Funktionen
friend int EXPORTTRIAS FillMerkmalsListe (void *pItem, void *);
friend int EXPORTTRIAS WriteBackChanges (void *pItem, void *);

	void ActivateMerkmal (void);
	void SetObjName (pWindow, long);
	Bool AskToSaveReply (void);
	ErrCode SaveEntry (void);
	ErrCode DeleteEntry (void);
	ErrCode CleanUpEntries (void);
	void ReBuildEntries (void);

public:
	long _ON;		// Objektnummer
	Bool _ROMode;		// R/O-Mode der DB

protected:
	void ButtonClick (ControlEvt e);
	void ListBoxSel (ControlEvt e);

public:
// Konstruktor
		ListObjektInfoDialog (pWindow pW, DatenBasisObjekt &rDBO, long ON, long ID, BOOL fSystem = TRUE);

// Member
	MerkmalsListe ML;
	GeoDB &DB() { return m_rDB; }

// Destruktor
		~ListObjektInfoDialog(void);

#if defined(_USE_LEGACY_CODE)
friend ErrCode FillMerkmale (DatenBasisObjekt &rDBO, MerkmalsListe &rML);
#endif // defined(_USE_LEGACY_CODE)
};

#endif // NOLISTOBJEKTDLG
#endif // _MERKEDIT_HXX
