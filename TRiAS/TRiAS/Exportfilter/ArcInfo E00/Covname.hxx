/*
File: COVNAME.HXX
Prüfen des zu jedem Identifikator gehörenden Covernamens.

erarbeitet : J. Benkenstein                 Begonnen am 5. Mai 1993
*/

#ifndef _COVNAME_HXX
#define _COVNAME_HXX

#ifndef NOCOVERNAMEDIALOG
class CoverNameDialog : public DialogWindow {
private:
	// Attribute
    ListBox _CoverNameList;
    NameEdit _CoverNameEdit;

protected:
	// Event-Handler-Funktionen
    Bool EXPORTFLT QueryClose (Event);
    void EXPORTFLT ButtonClick (ControlEvt CE);
    void EXPORTFLT ListBoxSel (ControlEvt CE);

	// akt. in CoverNameListe sel. Covernamen in Edit-Feld setzen
    void SetCoverName (void);

	// Fehlermeldungen ausgeben
    void OutputOpenError (pchar pText);

	// Dateiname überschreiben
    Bool OutputOverwrite (pchar pFileName);

	// ListBox mit Identfikatoren und Kurztexten füllen
    ErrCode FillNameList (Bool DeleteOldEntries = True);
    
    // internen Typ aus ID-String lesen
    char GetTyp (pchar pBuffer);

public:
	// prüfe, ob alle gewählten Namen einzigartig, gebe Fehlermeldung aus,
	// wenn wenigstens ein Name doppelt auftritt.
	// True, wenn alle Namen ok, sonst False
    Bool CheckAllNames (BOOL bOutputError = TRUE);

	// Konstruktor/Destruktor
    CoverNameDialog (pWindow pParent);
    ~CoverNameDialog (void) {}

	// unique CoverNames erzeugen
    ErrCode UniqueCoverNames (void);
};
#endif  // NOCOVERNAMEDIALOG

#ifndef NOCOVERNAME
//  Verwalte einen Covernamen-Eintrag
class CoverName {
private:
	// Attribute
    long _Id;           // TRIAS-ID
    char _Typ;          // interner Typ ('P', 'L', 'F', 'T')
    pchar _pName;       // CoverName
    ErrCode _EC;        // Operation-Flag

public:
	//  Konstruktor/Destruktor
    CoverName (long ID, pchar pCoverName, char Typ);
    ~ CoverName (void);

	//  weitere Member
    long ID (void) { return _Id; }
    char Typ (void) { return _Typ; }
    pchar Name (void) { return _pName; }
    ErrCode OpFlag (void) { return _EC; }

	// friend functions
    friend void* GetCoverName (void *pObj);
};

//  Der Baum verwaltet CoverName-Einträge
class CoverNamesTree : public CTree {
private:
	// Attribute
    short _NotUnique;       // Zähler für nicht einzigartige Einträge

protected:
    void EXPORTFLT UserDelete (void *pObj);

	// Namen verbinden, Zeiger ist explizit freizugeben
    pchar ConcatNames (pchar pOldName, pchar pExt);

public:
	// Konstruktor/Destruktor
    CoverNamesTree (void);
    ~ CoverNamesTree (void);

	// weitere Member
	// neuer Eintrag in Baum: unique Namen erzeugen
    ErrCode AddName (pchar pCoverName, long ID, char Typ);
};
DeclareLock (CoverNamesTree, CoverName);
#endif  // NOCOVERNAME

#endif  //  _COVNAME_HXX
