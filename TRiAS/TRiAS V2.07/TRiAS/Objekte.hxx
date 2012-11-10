// Headerdatei für Objektrecherche - DialogFenster
// File: OBJEKTE.HXX

#if !defined(_OBJEKTE_HXX)
#define _OBJEKTE_HXX

#if !defined(NOOBJINFO)

// nur Blinken, wenn weniger als 200 ms gebraucht werden
#define MAXHIGHLIGHTTIME	200

///////////////////////////////////////////////////////////////////////////////
// MindestGröße der Listbox (Anzahl der Zeichen)
#define COUNT_ITEMS		6
#define COUNT_CHARS		40

class OwnerDrawListBox;
class Extension;
class ExtensionList;
class ObjInfoItemTree;
class ObjFeld;

template<class T> class IEnum;

class ObjektInfoListBox :
	public OwnerDrawListBoxEx
{
private:
	ObjInfoItemTree &m_rData;

public:
		ObjektInfoListBox (pDialogWindow pW, ResID rsc, ObjInfoItemTree &rData);
		~ObjektInfoListBox (void);

	long AddItemEx (LONG lONr, LPCSTR pcText, int iIndex = -1);	// Eintrag hinzufügen
	long DelItemEx (int iIndex = -1);								// Eintrag löschen
	long SetItemEx (LONG lONr, LPCSTR pcText, int iIndex);		// Daten neu setzen
};

class ObjektInfo : 
	public OwnerDrawDialogWindow 
{
private:
	ObjektInfoListBox *m_pKurzInfo;	// ListBox
	ObjInfoItemTree *m_pOITree;	// Baum mit Items
	ExtensionList &m_rEL;		// ExtensionListe aus Hauptfenster

	Menu ObjektMenu;			// lokales Menu

	Color m_C;					// Markierungsfarbe
	long m_lActObj;				// aktiviertes Objekt

	HWND m_hWnd;				// FensterHandle
	DatenBasisObjekt &m_rDBO;

#if defined(WIN32) && !defined(_OLD_DRAGNDROP)		// Drag'n Drop
	LPOBJECTPROPERTY m_pIObjProp;
	bool m_fExistsOP;			// bei aufgetretenem Fehler nicht mehr benutzen

	class CORWndDropTarget *m_pDropTgt;
	bool m_fIsDropSource;
	bool m_fIsDropTarget;

	int m_iDropPos;
	int m_iDropIndex;
	HBRUSH m_hBr;
	bool m_fBrushToDelete;

	int m_iCntItems;
	int m_iCntChars;
#endif // WIN32

// private Memberfunktionen zur MerkmalsInformationsAnzeige
	bool doShowOIAttribute (void);		// allgemeine Merkmale
	void ShowOIThematik (void);			// thematische Relationen
	void ShowOITopologie (void);		// topologische Relationen

	void ShowOIObjectArea (void);		// FlächenInhalt
	void ShowOIObjectCentre (void);		// FlächenSchwerpunkt

	bool doObjDelete (void);			// Objekt(e) löschen
	void CreateKObject (void);			// KomplexObjekt bilden
	void DeleteONFromKONr (void);		// Einzelobjekt herauslösen

// Identifikator ändern
	void ModObjIdent (long ONr, long oldId, long newId, int iIndex);
	bool doModAllIdents (void);
	bool doCopyObjects (void);

	bool doZoomIn (void);			// Ausschnitt einstellen
	bool doAddToLegend (void);		// Objekte zu Legende hinzufügen
	bool doComplementObjects (void);		// alle anderen Objekte zeigen
	bool doExportObjects (void);		// Selektierte Objekte exportieren
		
#if defined(_NEWORMENU)
	bool doRemoveAllORWnds (void);	// alle ORWnd's schließen
	bool doCut (void);				// Ausschneiden
	bool doCopy (void);				// Kopieren
	bool doPaste (void);			// Einfügen
	bool doSelectAll (void);		// Alle Einträge selektieren
	bool doReverseSelection (void);	// Selektion umkehren
	bool doObjectProps (void);		// Objekteigenschaften
	bool doHelp (void);				// Hilfe anzeigen
	bool doCancel (void);			// Zeichnen im Hauptfenster abbrechen
	bool doRecherche (void);		// Objektrecherche
	bool doGenTextObjects (void);	// Textobjekte erzeugen
#endif // _NEWORMENU

	bool locQueryClose (void);

public:
	unsigned short m_fAreaEFlag : 1;
	unsigned short m_fCentreEFlag : 1;
	unsigned short m_fShowFlag : 1;	// Flag, ob alle aktiviert werden sollen
	unsigned short m_fNoBlinking : 1;
	unsigned short m_fToDelete : 1;
	unsigned short m_fHighLighted : 1;
	unsigned short m_fHasFocus : 1;
	unsigned short m_fSystem : 1;
	unsigned short m_fInitExtMenus : 1;
	unsigned short m_fInitMenuItems : 1;
	unsigned short m_fCmd : 1;	// Modaler Dialog ist offen
	
	ULONG m_ulActCount;		// Zähler der selektierten Objekte

	short m_iActObjTypes;	// Objekttypen der selektierten Objekte
	
	char *m_pBuffer;
	char *m_pBuffer1;

	short m_iFlags;			// zusätzliche Flags für Rundspruch
	CMPONRPROC m_pCmpProc;		// Vergleichsfunktion
	DWORD m_dwData;			// zugehörige Daten

#if defined(WIN32)
	CRITICAL_SECTION m_CS;	// doppeltes Löschen verhindern
	HACCEL m_hAccel;		// Acceleratoren für dieses Fenster
#endif // WIN32
		
protected:
// Eventbehandlung
	void ListBoxSel (ControlEvt);			// Click auf ListBox
	void ListBoxClk (ControlEvt);			// DoppelClick auf ListBox
	void Move (MoveEvt);					// Fenster verschoben
	void ReSize (ReSizeEvt);					// Fenster vergrößert/verkleinert
	void FocusChange (FocusChangeEvt);		// wenn Focus sich ändert
	bool QueryClose (Event);				// Vor Abschluá rufen
	void MenuCommand (MenuCommandEvt);		// Menu auswerten
	void MenuInit (MenuInitEvt);
	LRESULT EXPORTTRIAS  Dispatch (Event);	// nun doch eigener Dispatcher
#if defined(WIN32)
	bool PreTranslateMsg (MSG *pMsg);		// Accels bearbeiten
	LRESULT OnGetMinMaxInfo (MINMAXINFO *pmmi);
#endif // WIN32

// OwnerDraw EventHandler
	bool EXPORTTRIAS  DeleteItem (DeleteItemEvt);	// ODItem wird gelöscht
	bool EXPORTTRIAS  DrawEntireItem (DrawItemEvt);	// ZeichenFunktionen
	bool EXPORTTRIAS  DrawItemFocus (DrawItemEvt);
	bool EXPORTTRIAS  DrawItemSelect (DrawItemEvt);

	int EXPORTTRIAS  CompareItem (OwnerDrawEvt, void *, void *);	// Vergleichsfunktion
	bool EXPORTTRIAS  MeasureItem (MeasureItemEvt);

	ErrCode GenerateListBox (void);
	void InitExtensionMenus (void);
	void InitMenuItems (void);

	ULONG UpdateActivation (int iChanged = -1);
	void ActivateNextItem (int iOldIndex);

public:
// Konstruktor/Destruktor/Initialisierung
		ObjektInfo (pWindow pW, DatenBasisObjekt &rDBO, ExtensionList &EL, 
			    short iFlags, CMPONRPROC pProc, DWORD dwData
#if defined(WIN32)
			    , LPUNKNOWN pIUnk
#endif
			    );
		~ObjektInfo (void);

static 	ObjektInfo *CreateInstance (pWindow pW, DatenBasisObjekt &rDBO, 
				    ExtensionList &EL, ObjFeld &OF, short iFlags = 0, 
				    CMPONRPROC pProc = NULL, DWORD dwData = 0L
#if defined(WIN32)
				    , LPUNKNOWN pIUnk = NULL
#endif // WIN32
				    );
	bool FInit (ObjFeld &OF);
	
// Memberfunktionen
	void UpdateCaption (void);
	POINT CorrectPosition (class DragRectangleObject &);	// Fensterposition berechnen

	Point m_ptWantedPos;			// gewünschte Fensterposition

	void ActivateObj (long ON, bool fDraw = true, bool Flag = true, bool iAssoc = true);
	void DeActivateObj (bool fDraw = true, bool Flag = true, long ON = -1L, bool iAssoc = true);

// FensterHandle liefern
	HWND Handle (Service s) { return Window :: Handle (s); }

// Enumeration aller Objekte
	bool EnumAllObjects (bool (*pFcn)(long, bool, void *), void *, bool = true);
	bool EnumSelectedObjects (bool (*pFcn)(long, bool, void *), void *);
	bool EnumSelectedObjectsEx (bool (*pFcn)(long, DWORD, void *), void *, DWORD);

	bool EnumIdents (bool (*fcn)(long, bool, void *), void *, 
			 bool fSelected, bool fWithOTypes = false);
	
	Color SetColor  (Color newC);

	bool LoadExtension (Extension &);
	bool UnLoadExtension (Extension &, bool);

	HMENU InstallMenuItem (short iMenuID, short iMenuNum, char *pText);
	bool RemoveMenuItem (short iMenuID, short iMenuNum);

	ExtensionList &EL (void) { return m_rEL; }

	HWND hWnd (void) { return m_hWnd; }
	HWND hWndLB (void) { return m_pKurzInfo ? m_pKurzInfo->Handle(API_WINDOW_HWND) : NULL; }

	ObjInfoItemTree &OITree (void) { return *m_pOITree; }
	ULONG GetCount (void);
	long GetActiveObj (void);	// Objekt mit Focus liefern
   
   	bool ChangeActiveColor (long lONr, Color &newC);  

	void DeleteObjectIndex (short iIndex);
	void DeleteObject (long lONr);

	void ModObjIdentEx (long lONr, long newId, long SeloldId = -1L, short = -1);
   	
	bool HandleDeleteObject (long lONr, bool fUpdateCaption = true);
	bool HandleModifyIdent (long lONr, long lIdent, long lONrNew = 0L);
	HRESULT RetrieveObjInfo (long lONr, int iIndex = -1, int *piNewIndex = NULL);		// ListBox mit KurzInfo füllen
	bool HandleCancelMode (bool fCmd);
	bool RefreshEntry (long lONr);			// Eintrag neu lesen
	bool HandleModifyFeature (long lONr, LPCSTR pcName);

#if defined(WIN32) && !defined(_OLD_DRAGNDROP)
///////////////////////////////////////////////////////////////////////////////
// Drag'n Drop
	HRESULT DragEnter (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	HRESULT DragOver (DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	HRESULT DragLeave (void);
	HRESULT Drop (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);

	HRESULT InitDragDrop (void);
	HRESULT RevokeDragDrop (void);
	LRESULT OnNotify (WPARAM wParam, LPARAM lParam);

	HRESULT DoDragDropAction (DWORD dwFlags);

	UINT TestDroppablePoint (POINTL *pPt);
	bool FQueryPasteFromData (IDataObject *pIDataSource);
	bool FQueryDrop (void); 
	bool FPasteFromData (IDataObject *pIDataObject);
	bool ClipSelEntries (bool fDelete = false);
	bool AddObjectsToWindow (IEnum<LONG> *pIEnumObj, int iIndex);

	bool GiveFeedBack (POINTL *pPt, bool fRemove = false, bool fDraw = true);
	bool DrawDropSelection (Rectangle &rc);
	int FindEntrySize (CoOrd dY, Point pt, Range &rR);

	bool IsDropSource (void) { return m_fIsDropSource ? true : false; }
	void IsDropTarget (bool fFlag = true) { m_fIsDropTarget = fFlag; }
	bool IsDropSourceInst (void);
	bool IsDropSourceORWnd (void);

// ObjectProperty-support
	bool SetNewObjectProp (SHOWOBJPROP *pSOP);
	LRESULT ReplaceObjectInList (REPLACEOBJECT *pRO);
#endif // WIN32

inline 	short GetFlags (void) { return m_iFlags; }

// Friend Klasse
friend class ObjektInfoListe;

friend	void DrawActiveObj (void *);		// zeichnen des aktivierten Obj

// Funktionen für Schlüsselzugriff
friend	void *GetObjInfoKey (void *pObj);
friend	int UShortCmp (void *Key1, void *Key2) 
		{ return (*(unsigned short *)Key1 - *(unsigned short *)Key2); }

// Funktionen zum neuzeichnen
friend 	bool EXPORTTRIAS  RedrawActiveObj (void *pObj, void *pData);
friend 	void BlinkAllObj (void);
friend	void EXPORTTRIAS  Blink (void *);

// friend	bool App_PreTranslateMessage (MSG *pMsg);

#if !defined(WIN32)
// KoordinatenTransformationen
friend long gaugeo (double *, double *, double *, double *);
friend long geogau (long *, long *, double *, double *, double *, double *);
#endif
};

// Funktion, welche das Sortieren ausführt ------------------------------------
extern "C" short PASCAL CompareObjs (long lONr1, long lONr2, DWORD dwData);

#endif // NOOBJINFO

#if !defined(NOOBJINFOLISTE)
class ObjektInfo;
class Extension;

typedef struct tagCHANGEACTIVECOLOR CHANGEACTIVECOLOR;

// Container, der alle ObjInfo-Fenster dieser Klasse enthält ------------------
class ObjektInfoListe : 
	public CTree 
{
private:
	HWND m_hLastActiveWnd;

protected:
	void UserDelete (void *pItem);

public:
// Konstruktor
		ObjektInfoListe (void);

	long GetSelectedObject (HWND = 0);	// liefert aktiviertes Objekt
	long GetAllSelectedObjects (long *);	// liefert alle aktivierten Objekte

// Enumeration aller selektierten Objekte
	bool EnumSelectedObjects (bool (*pFcn)(long, bool, void *), void *pData, HWND = 0);	
	bool EnumSelectedObjectsEx (bool (*pFcn)(long, DWORD, void *), void *pData, DWORD dwData, HWND = 0);	

	bool EnumAllObjects (bool (*fcn)(long, bool, void *), void *, HWND = 0);
	bool EnumORWindows (ENUMNOKEYLONG *pK);

	ulong CountObjects (HWND = 0);

	pWindow GetORWindow (HWND);
	HWND GetActiveORWindow (void);

	bool LoadExtension (Extension &);	// Erweiterung wurde geladen
	bool UnLoadExtension (Extension &);	// Erweiterung wurde freigegeben

	HMENU InstallMenuItem (short iMenuID, short iMenuNum, char *pText);
	bool RemoveMenuItem (short iMenuID, short iMenuNum);

   	bool ChangeActiveColor (CHANGEACTIVECOLOR *);  

	bool HandleDeleteObject (long lONr);
	bool HandleModifyIdent (long lONr);
	bool HandleCancelMode (bool fCmd);
	bool HandleModifyFeature (long lONr, LPCSTR pcName);
	void ShowORWindows (ShowState s);

	HWND SetLastActive (HWND);

	bool ActivateAllObj (HWND hWnd = NULL);
	void BlinkAllObj (void);

	void Enable (bool fEnable);		// alle OR's aktivieren

	string CorrectCaption (ObjektInfo *pOIDlg, LPCSTR pcTemplate);
	bool CaptionExists (ObjektInfo *pOIDlg, LPCSTR pcCaption);

	void CloseORWindow (HWND hWnd);

#if defined(WIN32) && !defined(_OLD_DRAGNDROP)
	bool IsDropSourceORWnd (void);
#endif // !_OLD_DRAGNDROP

	bool CleanUpDeleted (void);

// Destruktor
		~ObjektInfoListe (void);

friend int HWNDCmp (void *, void *);
};

///////////////////////////////////////////////////////////////////////////////
// Zugriffstypen (Lock, Creator) für ObjektInfoListe generieren 
DeclareLock (ObjektInfoListe, ObjektInfo);

#if defined(WIN32) && !defined(_OLD_DRAGNDROP)
extern DWORD g_dwScrollInset;		// globale ProfileWerte für Drag'nDrop
extern DWORD g_dwScrollDelay;
#endif // WIN32

#endif // NOOBJINFOLISTE

#endif // _OBJEKTE_HXX

