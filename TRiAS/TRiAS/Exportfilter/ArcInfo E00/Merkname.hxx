/*
File: MERKNAME.HXX
Prüfen des zu jedem Merkmal gehörenden Textes

erarbeitet : J. Benkenstein                 Begonnen am 5. Mai 1993
*/

#ifndef _MERKNAME_HXX
#define _MERKNAME_HXX

class MerkmalNameDialog : public DialogWindow {
private:
//  Attribute
    ListBox _MerkmalNameList;
    NameEdit _MerkmalNameEdit;

protected:
//  Event-Handler-Funktionen
    Bool EXPORTFLT QueryClose (Event);
    void EXPORTFLT ButtonClick (ControlEvt CE);
    void EXPORTFLT ListBoxSel (ControlEvt CE);

//  akt. in MerkmalsNamensListe sel. Merkmalsnamen in Edit-Feld setzen
    void SetMerkmalName (void);

//  Merkmalsname überschreiben
    Bool OutputOverwrite (pchar pName);

//  Fehlermeldung für ungültigen Namen ausgeben
    void OutputNoName (void);

//  ListBox mit Merkmalskoden und Kurztexten füllen
    ErrCode FillNameList (Bool DeleteOldEntries = True);
    
public:    
//  Konstruktor/Destruktor
    MerkmalNameDialog (pWindow pParent);
    ~MerkmalNameDialog (void) {}

//  prüfe, ob alle gewählten Namen einzigartig, gebe Fehlermeldung aus,
//  wenn wenigsten ein Name doppelt auftritt.
//  True, wenn alle Namen ok, sonst False
    Bool CheckAllNames (BOOL bOutputError = TRUE);

	//	einzigartige Merkmalsnamen erzeugen
	ErrCode CreateUniqueNames (void);   
};

#endif  //  _MERKNAME_HXX
