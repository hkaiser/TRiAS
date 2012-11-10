// File: KOMPLEXR.HXX
// Begonnen am 9. Juli 1993
// Stand vom 13.11.95

#if !defined(_KOMPLEXR_HXX)
#define _KOMPLEXR_HXX

void OutputError (pchar pErrorText);    //  Fehlermeldung ausgeben
void OutputOK (pchar pText);            //  OK-Meldung ausgeben

class DBaseObjFeld;
class ObjContainer;
class IdentTree;
class KomplexrExtension : public CTriasExtension {
private:
//  Attribute
    pchar _pScriptName;     // Name der selektierten Script-Datei
    RSToDo _toDo;           // was mit gefundenen Objekten gemacht werden soll
    DBaseObjFeld *_pOF;     // Feld der gefundenen Objekte
    ObjContainer *_pOC;     // aktuell selektiertes Gebiet
    uint _EditMsg;          // Nachricht mit TRIAS-ED
    IdentTree *_pIdTree;    // Identifikator-Liste

protected:
//  überladene virtuelle Funktion(en)
	STDMETHOD_(bool, InitExtension) (THIS_ short iMode);
    STDMETHOD_(bool, UnLoadExtension) (THIS);
	STDMETHOD_(bool, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
    STDMETHOD_(bool, MenuCommand) (THIS_ WPARAM wParam, HWND hWnd);
    STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);
	STDMETHOD_(LRESULT, WindowsNotification) (THIS_ UINT wMsg, WPARAM wParam, LPARAM lParam);

//  weitere interne Funktion(en)
    void _OutObjectList (void); 		// Recherche-Ergebnisse in Liste ausgeben
    void _Classify (void);      		// umklassifizieren
    void _CreateStandScript (void);     // Standard-Script erstellen
    Bool _SetScriptName (void); 		// neuen Scriptnamen setzen (aus ClipBoard lesen)

public:
//  Konstruktor / Destruktor
    KomplexrExtension (void);
    ~KomplexrExtension (void);

//  weitere Member-Funktionen
    pchar ScriptName (void) { return _pScriptName; }
    RSToDo &RStatus (void) { return _toDo; }
    DBaseObjFeld &OF (void) { return *_pOF; }
    ObjContainer &OC (void) { return *_pOC; }

//  alle zu einer Sicht gehörenden Objekte lesen
    ErrCode IdFilterNew (char *pSigthName);

//  alle Objekte aus dem Feld löschen, die nicht zur Sicht gehören
    ErrCode IdFilter (char *pSichtName);

//  Alle Objekte über Identfikator-Liste filtern
    ErrCode IdFilterIdents      (void);

//  Neuen Sicht-Identifiaktor in Baum aufnehmen
    Bool AddIdent (long Id);

//  Geometrierecherche durchführen
    ErrCode doGeoRecherche (ObjContainer &);

//  lokale Daten für Recherche init.
    ErrCode InitRecherche (void);

//  Recherche-Ergebnisse auswerten
    ErrCode OutputRecherche (Bool ParseOnly = False);

//  DQLSCR-Pfad einstellen
    void SetScriptPfad (void);
};

class ObjectData {
public:
    DBaseObjFeld *_pOF;
    ErrCode _EC;

    ObjectData (DBaseObjFeld *pOF) { _pOF = pOF; _EC = EC_OKAY; }
    ~ ObjectData (void) {}
};

class Ident {
private:
    long _Id;

public:
    Ident (long Id) { _Id = Id; }
    ~ Ident (void) {}

    long & Id (void) { return _Id; }

    friend int CompareIds (void *, void *);
    friend void * GetId (void *);
};

class IdentTree : public CTree {
protected:
    void UserDelete (void *pObj);

public:
    IdentTree (void);
    ~ IdentTree (void);

    ErrCode AddIdent (long Id);     // neuen Id in Container aufnehmen
    Bool FindIdent (long Id);	    // Ident im Baum suchen
};
DeclareLock (IdentTree, Ident);

class IdentEnumDaten {
public:
    IdentTree *_pIdT;
    ErrCode _EC;

    IdentEnumDaten (IdentTree *pIdT) { _pIdT = pIdT; _EC = EC_OKAY; }
    ~ IdentEnumDaten (void) {}
};

#endif  // _KOMPLEXR_HXX
