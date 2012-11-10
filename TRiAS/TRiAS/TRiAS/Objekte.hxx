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
class ObjektInfo;

template<class T> class IEnum;

class ObjektInfoListBox :
	public OwnerDrawListBoxEx
{
private:
	ObjektInfo &m_rORWnd;

public:
		ObjektInfoListBox (pDialogWindow pW, ResID rsc, ObjektInfo &rORWnd);
		~ObjektInfoListBox (void);

	long AddItemEx (LONG lONr, LPCSTR pcText, int iIndex = -1);	// Eintrag hinzufügen
	long DelItemEx (int iIndex = -1);							// Eintrag löschen
	long SetItemEx (LONG lONr, LPCSTR pcText, int iIndex);		// Daten neu setzen

	DWORD AddExtentEntry (LPCSTR psz)
	{
		return LocControl() -> AddExtentEntry(psz);
	}
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

#if !defined(WIN16) && !defined(_OLD_DRAGNDROP)		// Drag'n Drop
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
#endif // WIN16

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
	bool doMinimizeAllORWnds (void);	// alle ORWnd's minimieren
	bool doMaximizeAllORWnds (void);	// alle ORWnd's wiederherstellen
	bool doCut (void);				// Ausschneiden
	bool doCopy (void);				// Kopieren
	bool doPaste (void);			// Einfügen
	bool doSaveObjColl (void);		// Objektmenge speichern
	bool doSelectAll (void);		// Alle Einträge selektieren
	bool doReverseSelection (void);	// Selektion umkehren
	bool doObjectProps (void);		// Objekteigenschaften anzeigen
	bool doDeleteObjProps (void);	// Objekteigenschaften löschen
	bool doHelp (void);				// Hilfe anzeigen
	bool doCancel (void);			// Zeichnen im Hauptfenster abbrechen
	bool doDraw (void);				// Zeichnen im Hauptfenster auslösen
	bool doRebuild (void);			// Zeichnen/Neuaufbau im Hauptfenster auslösen
	bool doRecherche (void);		// Objektrecherche
	bool doReplace (void);			// Suchen und ersetzen
	bool doClassify (void);			// Klassifikation
	bool doGenTextObjects (void);	// Textobjekte erzeugen
	bool doRechResults (void);		// Anzuzeigende Infos auswählen
	bool doCreateConnFilter (void);		// Räumlichen Filter aus Objektgeometrie erzeugen
#endif // _NEWORMENU

	bool locQueryClose (void);

public:
	unsigned int m_fAreaEFlag : 1;
	unsigned int m_fCentreEFlag : 1;
	unsigned int m_fShowFlag : 1;	// Flag, ob alle aktiviert werden sollen
	unsigned int m_fNoBlinking : 1;
	unsigned int m_fToDelete : 1;
	unsigned int m_fHighLighted : 1;
	unsigned int m_fHasFocus : 1;
	unsigned int m_fSystem : 1;
	unsigned int m_fInitExtMenus : 1;
	unsigned int m_fInitMenuItems : 1;
	unsigned int m_fCmd : 1;		// Modaler Dialog ist offen

	unsigned int m_fMustDestroy : 1;
	unsigned int m_fIgnoreObjProp : 1;		// globale Objekteigenschaft ignorieren 
	unsigned int m_fUseEntryCallback : 1;	// Texte erst bei Bedarf berechnen

	long m_lCommandActive;
	
	ULONG m_ulActCount;		// Zähler der selektierten Objekte

	short m_iActObjTypes;	// Objekttypen der selektierten Objekte
	
	char *m_pBuffer;
	char *m_pBuffer1;

	short m_iFlags;			// zusätzliche Flags für Rundspruch
	CMPONRPROC m_pCmpProc;		// Vergleichsfunktion
	DWORD m_dwData;			// zugehörige Daten

#if !defined(WIN16)
	CRITICAL_SECTION m_CS;	// doppeltes Löschen verhindern
	HACCEL m_hAccel;		// Acceleratoren für dieses Fenster
#endif // WIN16
		
protected:
// Eventbehandlung
	void ListBoxSel (ControlEvt);			// Click auf ListBox
	void ListBoxClk (ControlEvt);			// DoppelClick auf ListBox
	void Move (MoveEvt);					// Fenster verschoben
	void ReSize (ReSizeEvt);					// Fenster vergrößert/verkleinert
	void FocusChange (FocusChangeEvt);		// wenn Focus sich ändert
	BOOL QueryClose (Event);				// Vor Abschluá rufen
	void MenuCommand (MenuCommandEvt);		// Menu auswerten
	void MenuInit (MenuInitEvt);
	LRESULT EXPORTTRIAS  Dispatch (Event);	// nun doch eigener Dispatcher
#if !defined(WIN16)
	BOOL PreTranslateMsg (MSG *pMsg);		// Accels bearbeiten
	LRESULT OnGetMinMaxInfo (MINMAXINFO *pmmi);
#endif // WIN16

#if !defined(_NO_ROLLUP_ORWND)
	LRESULT OnNcPaint (Event e);
	LRESULT OnNcActivate (Event e);
	LRESULT OnSetText(Event e);
	LRESULT OnNcHitTest (Event e);
	LRESULT OnNcLButtonDown (Event e);
	LRESULT OnMouseMove (UINT wMsg, WPARAM wParam, LPARAM lParam);
	void MouseButtonUp (MouseEvt e);

	void CalculateButtonRect (Rectangle *prc);
	bool IsMouseInRollUpButton(LPARAM lParam, bool fPointIsClient = false);
	void DrawButton();
	void GetCorrectedRestoreRect (Rectangle *prc);

	bool doToggleRollUp();					// command handler

	bool m_fPushedButton;
	bool m_fIsRolledUp;
	bool m_fMouseCaptured;
	Dimension m_dimBeforeRollUp;
	HMENU m_hMenu;
	long m_lInitialWidth;
#endif // !defined(_NO_ROLLUP_ORWND)

// OwnerDraw EventHandler
	BOOL EXPORTTRIAS  DeleteItem (DeleteItemEvt);	// ODItem wird gelöscht
	BOOL EXPORTTRIAS  DrawEntireItem (DrawItemEvt);	// ZeichenFunktionen
	BOOL EXPORTTRIAS  DrawItemFocus (DrawItemEvt);
	BOOL EXPORTTRIAS  DrawItemSelect (DrawItemEvt);

	int EXPORTTRIAS  CompareItem (OwnerDrawEvt, void *, void *);	// Vergleichsfunktion
	BOOL EXPORTTRIAS  MeasureItem (MeasureItemEvt);

	ErrCode GenerateListBox (void);
	void InitExtensionMenus (void);
	void InitMenuItems (void);
	void RemovePopupMenues();

	ULONG UpdateActivation (int iChanged = -1);
	void ActivateNextItem (int iOldIndex);

public:
// Konstruktor/Destruktor/Initialisierung
		ObjektInfo (pWindow pW, DatenBasisObjekt &rDBO, ExtensionList &EL, 
			    short iFlags, CMPONRPROC pProc, DWORD dwData, LPUNKNOWN pIUnk);
		~ObjektInfo (void);

static 	ObjektInfo *CreateInstance (pWindow pW, DatenBasisObjekt &rDBO, 
				    ExtensionList &EL, ObjFeld &OF, short iFlags = 0, 
				    CMPONRPROC pProc = NULL, DWORD dwData = 0L,
				    LPUNKNOWN pIUnk = NULL);

static 	ObjektInfo *CreateInstance (pWindow pW, DatenBasisObjekt &rDBO, 
				    ExtensionList &EL, INT_PTR *plONr, long lCnt, short iFlags = 0, 
				    CMPONRPROC pProc = NULL, DWORD dwData = 0L,
				    LPUNKNOWN pIUnk = NULL);

	bool FInit (ObjFeld &OF);
	bool FInit (INT_PTR *plONr, long lCnt);
	
	bool FInit1 (long lCnt);
	bool FInit2 (ObjFeld &OF, INT_PTR &rlONr);
	bool FInit2 (INT_PTR *plONr, long lCnt, INT_PTR &rlONr);
	bool FInit3 (INT_PTR lONr);
	
// Memberfunktionen
	void UpdateCaption (void);
	POINT CorrectPosition (class DragRectangleObject &);	// Fensterposition berechnen

	Point m_ptWantedPos;			// gewünschte Fensterposition

	void ActivateObj (long ON, bool fDraw = true, bool Flag = true, bool iAssoc = true);
	void DeActivateObj (bool fDraw = true, bool Flag = true, long ON = -1L, bool iAssoc = true);

// FensterHandle liefern
	HWND Handle (Service s) { return Window :: Handle (s); }

// Enumeration aller Objekte
	BOOL EnumAllObjects (BOOL (*pFcn)(long, BOOL, void *), void *, BOOL = true);
	BOOL EnumSelectedObjects (BOOL (*pFcn)(long, BOOL, void *), void *);
	BOOL EnumSelectedObjectsEx (BOOL (*pFcn)(long, DWORD, void *), void *, DWORD);

	BOOL EnumIdents (BOOL (*fcn)(long, BOOL, void *), void *, 
			 BOOL fSelected, BOOL fWithOTypes = false);
	
	Color SetColor  (Color newC);

	bool LoadExtension (Extension &);
	bool UnLoadExtension (Extension &, bool);

	HMENU InstallMenuItem (short iMenuID, short iMenuNum, short iMenuPos, char *pText, UINT *puiPos = NULL);
	HMENU InstallMenuItem (short iMenuNum, char *pText, HMENU hPopMenu, bool fTopLevel = false, UINT *puiPos = NULL);
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
	int FindObject (long lONr);

	void ModObjIdentEx (long lONr, long newId, long SeloldId = -1L, short = -1);
   	
	bool HandleDeleteObject (long lONr, bool fUpdateCaption = true, bool fUndo = false);
	bool HandleModifyIdent (long lONr, long lIdent, long lONrNew = 0L, bool fUndo = false, bool fDoNotHideExisting = false)
	{
		if (GetUseEntryCallback()) 
			return HandleModifyIdentCallback(lONr, lIdent, lONrNew, fUndo, fDoNotHideExisting);
		return HandleModifyIdentDirect(lONr, lIdent, lONrNew, fUndo, fDoNotHideExisting);
	}
	bool HandleModifyIdentDirect (long lONr, long lIdent, long lONrNew = 0L, bool fUndo = false, bool fDoNotHideExisting = false);
	bool HandleModifyIdentCallback (long lONr, long lIdent, long lONrNew = 0L, bool fUndo = false, bool fDoNotHideExisting = false);

// ListBox mit KurzInfo füllen
	bool GetUseEntryCallback() { return m_fUseEntryCallback; }
	HRESULT RetrieveObjInfo (long lONr, int iIndex = -1, int *piNewIndex = NULL, bool fUndo = false);		
	HRESULT RetrieveObjInfo (long lONr, long lIdent, int iIndex = -1, int *piNewIndex = NULL, bool fUndo = false)
	{
		if (GetUseEntryCallback()) 
			return RetrieveObjInfoCallback(lONr, lIdent, iIndex, piNewIndex, fUndo);
		return RetrieveObjInfoDirect(lONr, lIdent, iIndex, piNewIndex, fUndo);
	}
	HRESULT RetrieveObjInfoDirect (long lONr, long lIdent, int iIndex = -1, int *piNewIndex = NULL, bool fUndo = false);
	HRESULT RetrieveObjInfoCallback (long lONr, long lIdent, int iIndex = -1, int *piNewIndex = NULL, bool fUndo = false);

	HRESULT RetrieveObjInfoCallback(class ObjInfoItem *pItem);

	bool HandleCancelMode (bool fCmd);
	bool RefreshEntry (long lONr, bool fDoNotHideExisting = false);			// Eintrag neu lesen
	bool RefreshAllEntries(bool fDoNotHideExisting = false);				// alle Einträge neu lesen
	bool HandleModifyFeature (long lONr, LPCSTR pcName);

    bool ExecuteSequence();

    LONG QueryObjectCount(IDENTOBJECTCOUNT *pData);

#if !defined(WIN16) && !defined(_OLD_DRAGNDROP)
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
	bool FPasteFromData (IDataObject *pIDataObject, DWORD grfKeyState, POINTL pt);
	bool ClipSelEntries (bool fDelete = false);
	bool DeleteDroppedObjects(IEnum<LONG> *pIEnum);

	bool AddObjectsToWindow (IEnum<LONG> *pIEnumObj, int iIndex);

	bool AddObjectsToNewWindow (IEnum<LONG> *pIEnumObj);
	bool BuildIntersectionInNewWindow (IEnum<LONG> *pIEnumObj);
	bool BuildXorInNewWindow (IEnum<LONG> *pIEnumObj);
	bool BuildDifferenceInNewWindow (IEnum<LONG> *pIEnumObj);
	bool BuildInvDifferenceInNewWindow (IEnum<LONG> *pIEnumObj);
	bool WindowOperations (IEnum<LONG> *pIEnumObj, UINT uiResMain, UINT uiResOR, LPCSTR pcRscOR);

	bool GiveFeedBack (POINTL *pPt, bool fRemove = false, bool fDraw = true);
	bool DrawDropSelection (Rectangle &rc);
	int FindEntrySize (CoOrd dY, Point pt, Range &rR);

	bool IsDropSource (void) { return m_fIsDropSource ? true : false; }
	void IsDropTarget (bool fFlag = true) { m_fIsDropTarget = fFlag; }
	bool IsDropSourceInst (void);
	bool IsDropSourceORWnd (void);

// ObjectProperty-support
	bool SetNewObjectProp (SHOWOBJPROP *pSOP);
	LRESULT ReplaceObjectInList (REPLACEOBJECT *pRO, bool fUndo = false);
#endif // WIN16

inline 	short GetFlags (void) { return m_iFlags; }

// Friend Klasse
friend class ObjektInfoListe;

friend	void DrawActiveObj (void *);		// zeichnen des aktivierten Obj

// Funktionen für Schlüsselzugriff
friend	void *GetObjInfoKey (void *pObj);
friend	int UShortCmp (void *Key1, void *Key2) 
		{ return (*(unsigned short *)Key1 - *(unsigned short *)Key2); }

// Funktionen zum neuzeichnen
friend 	BOOL EXPORTTRIAS  RedrawActiveObj (void *pObj, void *pData);
friend 	void BlinkAllObj (void);
friend	void EXPORTTRIAS  Blink (void *);

// friend	bool App_PreTranslateMessage (MSG *pMsg);

#if defined(WIN16)
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

	long GetSelectedObject (HWND = 0);		// liefert aktiviertes Objekt
	long GetAllSelectedObjects (long *);	// liefert alle aktivierten Objekte

// Enumeration aller selektierten Objekte
	BOOL EnumSelectedObjects (BOOL (*pFcn)(long, BOOL, void *), void *pData, HWND = 0);	
	BOOL EnumSelectedObjectsEx (BOOL (*pFcn)(long, DWORD, void *), void *pData, DWORD dwData, HWND = 0);	

	BOOL EnumAllObjects (BOOL (*fcn)(long, BOOL, void *), void *, HWND = 0);
	BOOL EnumORWindows (ENUMNOKEYLONG *pK);

	ulong CountObjects (HWND = 0);

	pWindow GetORWindow (HWND);
	HWND GetActiveORWindow (void);
	HWND SetActiveORWindow (HWND hWnd);

	bool RefreshObjectEntries (INT_PTR lONr = NULL);

	bool LoadExtension (Extension &);	// Erweiterung wurde geladen
	bool UnLoadExtension (Extension &);	// Erweiterung wurde freigegeben

	HMENU InstallMenuItem (short iMenuID, short iMenuNum, short iMenuPos, char *pText);
	HMENU InstallMenuItem (short iMenuNum, char *pText, HMENU hPopMenu, bool fTopLevel = false);
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

#if !defined(WIN16) && !defined(_OLD_DRAGNDROP)
	HWND GetDropSourceORWnd();
#endif // !_OLD_DRAGNDROP

	bool CleanUpDeleted (void);

// Destruktor
		~ObjektInfoListe (void);

friend int HWNDCmp (void *, void *);
};

///////////////////////////////////////////////////////////////////////////////
// Zugriffstypen (Lock, Creator) für ObjektInfoListe generieren 
DeclareLock (ObjektInfoListe, ObjektInfo);

#if !defined(WIN16) && !defined(_OLD_DRAGNDROP)
extern DWORD g_dwScrollInset;		// globale ProfileWerte für Drag'nDrop
extern DWORD g_dwScrollDelay;
#endif // WIN16

#endif // NOOBJINFOLISTE

#endif // _OBJEKTE_HXX

