/*
Datei: GIZMOBAR.HXX

Das Modul stellt eine vereinfachte Schnittstelle zur Verwaltung einer
Toolbar bereit.

Erarbeitet: J. Benkenstein				Stand vom 26.1.1994

Hinweis: Da der R�ckkehrwert der Funktion "GBGizmoSendMessage" abh�ngig
von der versendeten Nachricht ist und auch nicht wie im C-API angegeben
bei Fehler immer 0 ist, wird dieser in einigen nicht getesteten Funktionen
nicht ausgewertet.
*/

#ifndef _GIZMOBAR_HXX
#define _GIZMOBAR_HXX

#ifndef NONAKEDEVENT
//  die Klasse realisiert den Zugriff auf das protected wMsg der Klasse Event
class CNakedEvent : public Event {
public:
	uint Msg (void) { return wMsg; }
};
#endif

#ifndef NOGIZMOBAR

// class TOOLDISPLAYDATA;
class CGizmoBar;

// Die Klasse CGizmoBar dient zur Verwaltung einer Toolbar.
class CGizmoBar {
private:
//  Attribute
	TOOLDISPLAYDATA *_pTDD;
	HWND _hWnd;
	HBITMAP _hBmp;
	HINSTANCE _hInst;
	short _GizmoCnt;

protected:
	Bool _CreateGizmo  (uint Ident,				 // Ident f�r Anwendung
						uint Type,				  // Gizmo-Typ
						uint BitmapIndex = 0,	   // Index des Buttons in Datei
						pchar pText = NULL,		 // Textwert
						uint Width = 0,			 // Breite, 0 -> Buttonbreite
						uint Height = 0,			// H�he, 0 -> Buttonh�he
						uint State = GIZMO_NORMAL); // Init.- Zustand

public:
//  Konstruktor/Destruktor
		//  Initialisierung in 2 Stufen
	CGizmoBar (HINSTANCE hInst);

		// Initialisierung:
		// Erzeuge die Toolbar in der client area des Parents unterhalb
		// der Caption �ber die vollst�ndige Breite des Fensters
	Bool Init (pWindow pParent,		 // Elternfenster
			   uint GizmoBarID);		// child window id

		//  Erzeugen eines Objektes
	static CGizmoBar * CreateGizmoBar (HINSTANCE hInst,
									  pWindow pParent,  // Elternfenster
									  uint GizmoBarID); // child window id

	~ CGizmoBar (void);

//  Funktionen f�r den Zugriff auf die Toolbar
	HWND Handle (void) { return _hWnd; }	// owner der Toolbar
	Bool ReSize (uint NewWidth);	//  GizmoBar in seiner Breite ver�ndern
	Bool Hide (void);					//		GizmoBar
	Bool Show (void);					//		darstellen/"verstecken"
	uint Height (void);					//		H�he der ToolBar, bei Fehler 0
	uint BitmapHeight (void);	   //  H�he/Breite einer Bitmap,
	uint BitmapWidth (void);		//  bei Fehler 0
	uint DotsPerInch (void);		//  Aufl�sung lesen, bei Fehler 0
	uint ButtonHeight (void);	   //  H�he/Breite
	uint ButtonWidth (void);		//  eines Standard-Buttons, bei Fehler 0

		// BitmapDatei laden:
		// BitmapID + 0 --> Size 720
		// BitmapID + 1 --> Size 960
		// BitmapID + 2 --> Size 1200
	Bool ReadBitmap (uint BitmapID);   // Bitmap Laden

//  Die durch Create erzeugten Controls/Buttons werden nacheinander
//  in der Reihenfolge ihres Aufruf von links nach rechts in der Toolbar
//  dargestellt.

	Bool CreateSeparator (
						uint Ident = 0,					// Ident f�r die Anwendung
						uint Width = 6);			// Breite des Separators

		// "Normalen" (Text-)Button erzeugen
	Bool CreateTextButton (
						uint Ident,				 // Ident f�r die Anwendung
						pchar pButtText = NULL,	 // Button-Text
						uint Width = 0,			 // Breite, 0 -> Buttonbreite
						uint Height = 0,			// H�he, 0 -> Buttonh�he
						uint State = GIZMO_NORMAL); // Init.- Zustand

		// Command-Button erzeugen
	Bool CreateCommandButton (
						uint Ident,				 // Ident f�r die Anwendung
						uint BitmapIndex = 0,	   // Index des Buttons in Datei
						uint Width = 0,			 // Breite, 0 -> Buttonbreite
						uint Height = 0,			// H�he, 0 -> Buttonh�he
						uint State = GIZMO_NORMAL); // Init.- Zustand

		// Status-Button erzeugen: nicht getestet !
	Bool CreateStateButton (
						uint Ident,				 // Ident f�r die Anwendung
						uint BitmapIndex = 0,	   // Index des Buttons in Datei
						uint Width = 0,			 // Breite, 0 -> Buttonbreite
						uint Height = 0,			// H�he, 0 -> Buttonh�he
						uint State = GIZMO_NORMAL); // Init.- Zustand

		// Gruppen-Button erzeugen (Attribute-Button): nicht getestet !
	Bool CreateGroupButton (
						uint Ident,				 // Ident f�r die Anwendung
						uint BitmapIndex = 0,	   // Index des Buttons in Datei
						uint Width = 0,			 // Breite, 0 -> Buttonbreite
						uint Height = 0,			// H�he, 0 -> Buttonh�he
						uint State = GIZMO_NORMAL); // Init.- Zustand

		// Textfeld erzeugen: nicht getestet !
	Bool CreateTextField (
						uint Ident,				 // Ident f�r die Anwendung
						pchar pText,					// notwendiger Text
						uint Width,				 // Breite/H�he des Feldes
						uint Height = 0,			// 0 --> Button-H�he
						uint State = GIZMO_NORMAL); // Init.- Zustand

		//  Edit-Feld erzeugen: nicht getestet !
	Bool CreateEditField (
						uint Ident,				 // Ident f�r die Anwendung
						pchar pText,					// voreingestellter Text
						uint Width = 50,			// Breite/H�he des Feldes
						uint Height = 0,			// 0 --> Button-H�he
						uint State = GIZMO_NORMAL); // Init.- Zustand

		// ListBox erzeugen
	Bool CreateListBox  (
						uint Ident,				 // Ident f�r die Anwendung
						uint Width = 100,		   // Breite/H�he
						uint Height = 100,		  // der ListBox
						uint State = GIZMO_NORMAL); // Init.- Zustand

		// ComboBox erzeugen: l�uft nicht, Fehler in CommonView
	Bool CreateComboBox (
						uint Ident,				 // Ident f�r die Anwendung
						uint Width = 100,		   // Breite/H�he
						uint Height = 100,		  // der ListBox
						uint State = GIZMO_NORMAL); // Init.- Zustand

//  Funktionen f�r die Manipulation einer ListBox/ComboBox

		// Ret: Index von pText, bei Fehler -1
	short ComboBoxAddString (uint Ident, pchar pText);

	short ComboBoxDelString (uint Ident, uint Index);		// bei Fehler -1, n. get.
	short ComboBoxGetCurrentIndex (uint Ident);				// bei Fehler -1

			// Return: neuer Index, bei Fehler -1
	short ComboBoxChangeCurrentIndex (uint Ident, uint NewIndex);

	short ComboBoxGetStringLen (uint Ident, uint Index); // bei Fehler -1
														 // nicht getestet !

			//		Return: Anzahl gelesener Zeichen, bei Fehler -1, nicht getestet !
	short ComboBoxGetString (uint Ident, uint Index, pchar pBuff);

	short ComboBoxClear (uint Ident);			 // alle S�tze in ListBox l�schen
											 // nicht getestet ! (bei Fehler -1)

	short ComboBoxGetCount (uint Ident);	 // bei Fehler -1,
											 // nicht getestet !

//  Funktionen f�r die Manipulation eines Edit-Feldes: alle nicht getestet !

	short EditFieldSetText (uint Ident, pchar pText); // bei Fehler -1

			// Return: Anzahl der gelesenen Zeichen, bei Fehler -1,
			// BuffLen beinhaltet Puffer-Gr��e (einschl. '\0')
	short EditFieldGetText (uint Ident, pchar pBuff, uint BuffLen);

			// max. L�nge des Eingabe-Feldes festlegen
	short EditFieldSetTextLimit (uint Ident, uint MaxLen); // bei Fehler -1
	short EditFieldGetTextLen (uint Ident);	 // bei Fehler -1

	short EditFieldisModified (uint Ident); // -1 Fehler, 0/1 not mod./modified

//  Funktionen f�r den Zugriff auf ein einzelnes "Gizmo": alle nicht getestet

	Bool HideGizmo (uint Ident);	// Gizmo �ber seinen Ident "verstecken"/
	Bool ShowGizmo (uint Ident);	// darstellen; Gizmos werden gepackt/gestreckt
	Bool RemoveGizmo (uint Ident);  // Gizmo entfernen
	void EnableGizmo (uint Ident);
	void DisableGizmo (uint Ident);
	Bool CheckAttributeButton (uint Ident);	 // "checks"/"unchecks" ein
	Bool UnCheckAttributeButton (uint Ident);   // Attribute-Button
	Bool GizmoSetFocus (uint Ident);	// Focus setzen, Separatoren,
					// Attribute/Command-Buttons k�nnen Focus nicht erhalten

	Bool GizmoExist (uint Ident);	   // True, wenn Gizmo vorhanden
	int GizmoGetType (uint Ident);		// GIZMOTYPE_* wenn gef., sonst -1

	DWORD GizmoSetData (uint Ident, DWORD dwGizmoInfo); // an ein Gizmo ein
									// DWORD anh�ngen, return: der vorige Wert

	DWORD GizmoGetData (uint Ident);	// das mit einem Gizmo
										// verbundene DWORD lesen

	Bool GizmoSetNotify (uint Ident, Bool Notify);  // Benachrichtigung
	Bool GizmoGetNotify (uint Ident);			   // setzen lesen

//  folgende 4 Funktionen sind auf Separatoren, Command/Attribute-Button
//  nicht anwendbar: alle nicht getestet !

	Bool GizmoSetText (uint Ident, pchar pText); // Text setzen
	int GizmoGetText (uint Ident, pchar pBuffer, uint BufferSize); // Text
		// eines Gizmos in Puffer lesen, return: Anzahl gelesener Zeichen

	Bool GizmoSetInt (uint Ident, uint Value, Bool Signed = False); // Ziffer
		// in einem Gizmo setzen, Signed = True --> Vorzeichen ist negativ

	uint GizmoGetInt (uint Ident, Bool *pRetFlag, Bool Signed); // Ziffer
		// von einem Gizmo lesen, pRetFlag --> Ergebnis der Konvertierung,
		// Signed --> Vorzeichen, Return ist bei Fehler 0

		// Nachricht an Gizmo senden, bei Fehler -1
		// Separatoren, Command/Attribute-Buttons akzeptieren keine Message
	LRESULT GizmoSendMessage (UINT Ident, UINT iMsg, WPARAM wParam, LPARAM lParam);
};

#endif	  // GizmoBar

#endif	  // _GIZMOBAR_HXX
