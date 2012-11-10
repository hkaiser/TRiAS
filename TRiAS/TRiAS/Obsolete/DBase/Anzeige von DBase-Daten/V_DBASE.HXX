/*------------------------------------------------------------------------

File: V_DBASE.HXX (Header)

View_dBase -
gibt den Inhalt eines dBase-Files satzweise in eine Listbox aus.

Erarbeitet: J. Benkenstein								 am: 19. Dez. 1991
												  Stand vom: 14. Sept. 1992
---------------------------------------------------------------------------*/

#ifndef V_DBASE_HXX
#define V_DBASE_HXX

// allg. Konstanten
const short BezSpalten	= 13;	 // Anzahl Spalten für Feldname u.
const short FeldSpalten   = 40;	 // Feldinhalt
	
class CodeBase;
class DataMemo;
class DBaseRel;
class Str255;
class dBaseDispatch;
class CGizmoBar;       
class CAliasFieldNameTree;

// Die Klasse "ShowFile" stellt Funktionen für die Darstellung des
// Inhalts eines dBase-Files bereit
class ShowFile : public ModeLessDialog
{
private:
//  Variablen für dBase-Relation: Zeilen-Ansicht
	CAliasFieldNameTree *_pAliasFieldTree;	// Baum speichert Feld- u. zugeh. Aliasnamen
	Str255 FieldVal;			// akt. Feldinhalt
	short RelCount;				// Anz. d. Relationen
	DBaseRel **ppdBaseRel;		// Zeiger auf Slave-DB/Feld

	dBaseDispatch *pDisp;		// Zeiger auf rufenden dBase-Dispatcher
	Menu *pRelMenu;				// Zeiger auf Relations-Menü

	Bool _toDelete;				// Fenster-Lösch-Flag				

	ErrCode RC;					// Operations-Kode

	DBaseObjNummer* pDON;		// ArrayContainer mit gültigen Satznummern
								// speichert Zeiger
	Bool OneRow;				// Zeilen/Spalten-Flag
	Bool _OemToAnsii;			// Texte in Windowstext konvertieren

	MultiLineDialog MemoDialog;	// zeigt Inhalt eines Memofeldes

	CGizmoBar *pRowGizmoBar;	// Zeiger auf GizmoBars
	CGizmoBar *pColGizmoBar;

	long MaxRow,		// Anzahl Sätze im File
		 ActRow,		// akt. Satz
		 NewActRow,
		 ScrollSize;   // Srcoll-Bewegung

	short ActCol,		// akt. Spalte
		  NewActCol,	// nach Ansichtumschaltung
		  MaxCol,
		  _BezBreite;	// Spalten-Breite für Feldnamen	

	CodeBase* pCBase; // Zeiger-Speicher 
	DataMemo* pData;  // Zeiger aus dBase-Daten-File

//  Resourcen-Elemente
	ResourceFile *pRF;

	Menu Menue;

	ExtTabularListBox ListRow, // Listbox-Objekt zeigt Inhalt eines Satzes
					  ListCol; // (Zeile) einer Spalte

	void _DeleteOldRelations (void);			// alten dBase-Relationen lö.
	void _DeleteRelMenu (void);			// löschen
	void _CreateRelMenu (void);			// und aufbauen des Submenüs
	Bool _CreateRowGizmoBar (void);			// Gizmo-Bars erzeugen
	Bool _CreateColGizmoBar (void);

		// akt. Satz in Listbox ausgeben
	void _ShowRow (Bool bForce = False);	// Anzeige forcierend akt.
		// Spaltenanzeige
	void  _ShowColumn (void);
	   // tausche Buttons für Einzel- und Mehrsatzdarstellung, True->Zeile,
	void  _ChangeButtons (Bool Zeile); // sonst Spalte
	   // Inhalt der akt. Listbox ins Clipboard kopieren
	Bool _ListToClip (ExtTabularListBox &List);
	   // Alias-File ins Clipboard ausgeben	
	Bool _CopyFieldAliasNames (void);
		// Umschalten zwischen Zeilen/Spalten-Darstellung
	void _SwitchRowColumn (void);
		// vorigen Eintrag darstellen
	void _PrevEntry (void);
		// nächsten Eintrag darstellen
	void _NextEntry (void);
		// dBase-Relationen lesen
	void _ReadDBaseRel (void);
		// Scroll-Button aktualisieren
	void _ChangeScrollButtons (long NewRow);
	                         
		// Index für das akt. Feld erzeugen	                         
	void _CreateIndex (void);
	
		// Alias-File-Name in Projekt-Ini schreiben
	void _SetAliasFile (void);                     
	                  
		// Anzeige für Zeile-Darstellung akt.	                  
	void _ActRow (void);

protected:
	   // Menü-Event-Handler
   void MenuCommand (MenuCommandEvt);
   void MenuInit (MenuInitEvt);
	   // Selektion der Menübuttons
   void		ButtonClick (ControlEvt);
	   // Selektion eines Listboxelementes
   void ListBoxClk (ControlEvt);
	   // Feldnamen-Selektion
   void ListBoxSel (ControlEvt);
	   // Neuzeichen der Clientarea nach Gräßenänderung
   void		ReSize (ReSizeEvt);
	   // Abfrage-Ende
   Bool QueryClose (Event);
	   // Gizmobar-Events
   void Default (Event);
public:
	   // ListBox u.a. Parameter init.
   ShowFile (pWindow pParent,			// Zeiger auf Elternfenster
			 CodeBase* pCodeBase,   	// Zeiger auf CodeBase-Basis-Objekt
			 pchar pAliasName,			// Alias-Name der Datei
			 pchar pFieldName,			// akt. Feld-Name
			 pchar pFieldVal,			// akt. Feld-Inhalt
			 dBaseDispatch *pDisp,  	// Zeiger auf rufenden dBase-Dispatcher
			 ResourceFile *pResF,   	// Resource-File-Zeiger
			 short ParType,				// Parameter-Typ
			 Point &TransLation);   	// x,y-Verschiebung des Fensters
	   // ListBox u. CodeBase-Klassen löschen
   ~ShowFile (void);
	   // Fileinhalt ausgeben
	void Darstellen ();		
		// Löschflag lesen
	Bool ToDelete (void) { return _toDelete; }		

	ErrCode Result (void) { return RC; }
};

#endif		// V_DBASE_HXX
