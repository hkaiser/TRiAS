// ViewFenster eines Projektes ------------------------------------------------
// File: IRISWIND.HXX

#if !defined(_IRISWIND_HXX)
#define _IRISWIND_HXX

// Stackdeklaration für Liste der fortlaufenden Bildausschnitte ---------------
Stack (ObjContainer);   // Deklaration der Klassen für einen Stack

// Viewfensterklasse ----------------------------------------------------------
typedef struct tagHANDLEVISINFO HANDLEVISINFO;

#if defined(WIN32)

#include <xtensnxx.h>

///////////////////////////////////////////////////////////////////////////////
// Klassendeklarationen -------------------------------------------------------
class PrinterPars;
class CDBOArray;

///////////////////////////////////////////////////////////////////////////////
// sonstige FunktionsDeklarationen --------------------------------------------
short doPrioritySelect (pWindow, CIdTree &, char *);
short OTypToBits (ObjTyp iOTyp);

///////////////////////////////////////////////////////////////////////////////
// ViewKlasse
class IrisWind : 
	public ChildAppWindow 
{
friend class ExtDirisWindow;
friend class IrisPrinter;

private:
// ScrollBars (WindowScrollBars)
	WndHorzScrollBar *m_pWHS;					// horizontaler WndScrollBar
	KoOrd m_kSX;								// Skalierung des ScrollRangeX	
	WndVertScrollBar *m_pWVS;					// vertikaler WndScrollBar
	KoOrd m_kSY;								// Skalierung des ScrollRangeY

	Brush *_IrisBGBrush;						// Hintergrundpinsel

	long m_lLastIdent;							// letzter neuer Ident
	long m_iDrawSem;
	Point MousePos;								// aktuelle MausPosition
	Point AspectRatio;							// AspectRatio

	ObjektInfoListe ObjInfoListe;				// Liste der ModeLessDialog's

// diverse Flags
	unsigned int m_fFullRedrawOnScroll : 1;		// alles neu zeichnen beim Scrollen
	unsigned int m_fHandleCancelMode : 1;		// bei WM_CANCELMODE zeichnen abbrechen
	unsigned int m_fRePaintFlag : 1;			// Flag, ob gezeichnet werden soll
	unsigned int m_fFirstDrawing : 1;			// erstes Anzeigen des Fensters
	unsigned int m_fReReadCaption : 1;			// Caption muß neu gelesen werden

#if !defined(_OLD_DRAGNDROP)
	unsigned int m_fIsDropSource : 1;			// this window is dropsource

	IDropTarget *m_pDropTgt;
#endif // _OLD_DRAGNDROP

	unsigned int m_fCommitOnClose : 1;			// in Close Commit rufen
	unsigned int m_fCleanedUp : 1;				// bereits aufgeräumt
	
	bool m_fPreventRepaint;						// Neuzeichnen unterbinden

	IrisPrinter *m_pPrinter;					// derzeit wird gedruckt

protected:
	CDragObject *DRO;							// SelektionsObjekt
	Brush *_emptyBrush;							// Pinsel für DrawRechteck
	CDBOArray *m_pDBOs;							// Liste aller offenen GeoDB's
	PrinterPars *m_pPD;							// aktueller Drucker

// Stack der fortlaufenden Vergrößerung (Bildfolge)
	ObjContainerStack actClip;					// Bildausschnittsfolge

public:
///////////////////////////////////////////////////////////////////////////////
// DB-Funktionen
	ErrCode OpenDB (LPCSTR DB, LPCSTR UN, LPCSTR PW, short gfMode = 0, DWORD dwMode = 0L);
	ErrCode OpenDB (LPSTORAGE pIStorage, short gfMode = 0, LPCSTR pcName = NULL);
	bool SaveAsGeoDB (LPCSTR pcAppend = NULL);
	bool ExportAsGeoDB (void);
	bool SaveGeoDB (void);
	bool CloseDocument (void);
	ErrCode CloseDB (bool fCommit, HPROJECT hDesc = 0);		// DB abschließen
	ErrCode AskUserToClose (bool &rfCommit, bool fFlag = true, HPROJECT hPr = 0);
	ErrCode HandleSaveCopy (LPCSTR pcName, bool &rfCommit, bool fSave);
	ErrCode HandleSaveRO (LPCSTR pcName, bool &rfCommit, bool fSave);

	long GetLastIdent (void);
	void SetLastIdent (long lIdent);

	bool IsInitialContainer (ObjContainer &rOC);
	bool InitOverView (ObjContainer &rOC);

#if !defined(_OLD_DRAGNDROP)
///////////////////////////////////////////////////////////////////////////////
// Drag'n Drop
	HRESULT DragEnter (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	HRESULT DragOver (DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	HRESULT DragLeave (void);
	HRESULT Drop (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);

	bool FQueryPasteFromData (IDataObject *pIDataObject);
	bool FPasteFromData (IDataObject *pIDataObject);
	UINT TestDroppablePoint (POINTL *pPt);
	void GiveFeedBack (POINTL *pPt, bool fRemove = false, bool fDraw = true);

	bool IsDropSource (void) { return m_fIsDropSource ? true : false; }
	bool IsDropSourceInst (void);
	bool IsDropSourceORWnd (void) { return ObjInfoListe.IsDropSourceORWnd(); }

	DWORD GetScrollDelay (void) { return g_dwScrollDelay; }
#endif // !_OLD_DRAGNDROP

protected:
///////////////////////////////////////////////////////////////////////////////
// EventHandler
	void MenuCommand (MenuCommandEvt);      // Menu-Kommandoverarbeitung
	void MenuInit (MenuInitEvt);            // Menuinitialisierung

	void Expose (ExposeEvt);                // neu zeichnen
	void ReSize (ReSizeEvt);
	void Move (MoveEvt);

	void MouseButtonDn (MouseEvt);			// MausEvents
	void MouseButtonUp (MouseEvt);
	void MouseDrag (MouseEvt);
	void MouseMove (MouseEvt);
	void MouseButtonDblClk (MouseEvt);

	void VertScroll (ScrollEvt);            // vertikale ScrollEvt's
	void HorizScroll (ScrollEvt);           // horizontale ScrollEvt's
	void Strobe (StrobeEvt);				// TimerEvent
	void FocusChange (FocusChangeEvt);		// Focus hat sich geändert
	void KeyDown (KeyEvt);					// KeyEvents
	void KeyUp (KeyEvt);
	void PaletteChange (PaletteChangeEvt);	// PaletteHandling
	void HelpRequest (HelpRequestEvt e);	// HilfeEvent
	void Close (Event e);					// das letzte vom Tage
	LRESULT Dispatch (Event);

	bool myQueryClose (bool);				// EndeAbfrage
	bool InitWndScrollBars (void);          // ScrollBarParameter

// Drucken etc.
	bool PrintGraphics (char *JobName, const ObjContainer &rOC);	// Bildchen ausgeben
	Point GetAspectRatio (void);
	bool DragFunc (WPARAM);					// Dragging

///////////////////////////////////////////////////////////////////////////////
// MenuKommandos
	bool doSaveDB (void);
	bool doSaveAsGeoDB (void);
	bool doExportAsGeoDB (void);
	bool doEditHeader (void);
	bool doShowIdentSel (void);
	bool doDeleteViews (void);
	bool doRebuild (void);
	bool doDraw (void);
	bool doPreventRepaint (void);
	bool doCancel (void);
	bool doPrint (void);
	bool doTextRech (void);
	bool doCoords (void);
	bool doSelectMasstab (void);
	bool doSaveOpt (void);
	bool doExport (void);
	bool doChangeBKColor (void);
	bool doSymbolPars (void);
	bool doPriority (void);
	bool doCopyClipBoard (void);
	bool doSelSichtCont (void);
	bool doDelSichtCont (void);
	bool doLegende (void);
	bool doOverView (void);
	bool doViewTexts (void);
	bool doSelAusschnitt (void);
	bool doPrevAusschnitt (void);
	bool doSelectView (void);
	bool doZoomOut (void);
	bool doZoomIn (void);
	bool doRestoreContainer (void);
	bool doSelIdents (void);
	bool doDelIdents (void);
	bool doModIdents (void);
	bool doCopyObjectsIdent (void);
	bool doCopyColors (void);
	bool doCoordMode (void);
	bool doGenTextObjects (void);

	bool doDefaultCmd (MenuCommandEvt e);
	bool doHandleTextObjectMenu (MenuCommandEvt e);
	bool doTools (MenuCommandEvt e);

#if !defined(NOPROJEKTION)
	bool doResetPrj (void);
	bool doWorldPrj (void);
#endif

public:
///////////////////////////////////////////////////////////////////////////////
// Konstruktor, Destruktor, Initialisierung
		IrisWind (ExtDirisWindow *pFrame);
		~IrisWind (void);

static IrisWind *CreateInstance (ExtDirisWindow *pFrame, IrisWind *& rpView,
		  LPCSTR pcDBName = NULL, LPCSTR pcUserName = NULL, 
		  LPCSTR pcPassWord = NULL, short gfMode = 0, DWORD dwMode = 0L);

	bool FInit (ExtDirisWindow *pFrame, LPCSTR pcDBName, LPCSTR pcUserName, 
				LPCSTR pcPassWord, short gfMode, DWORD dwMode);

///////////////////////////////////////////////////////////////////////////////
// public Funktionen
	bool RenderGeoDB (RENDERGEODB *pRDB);

// Funktion zur ObjektRecherche
	void ObjektRecherche (DragRectangleObject &DRO, ObjContainer &OC, bool);
	HWND CreateObjektInfo (DEXXCREATEOBJEKTINFO *pcrOI, ExtensionList &rEL);
	HWND CreateObjektInfo (CREATEOBJEKTINFO *pcrOI, ExtensionList &rEL);

	bool ShowIdentSel (void);
	bool ShowEditHeader (void);

	bool DeleteViews (void);
	bool CreateNewGeoDB (int rgMode);		// interactive
	bool EnumProjects (ENUMNOKEY *pK);
	HPROJECT GetProjectHandle (LPCSTR);
	HPROJECT MakeProjectActive (HPROJECT hPr);

#if defined(OLD_MASSTAB)
	bool MenuSelectMasstab (void);
#else
	bool SetMasstab (Rectangle rc);
#endif // OLD_MASSTAB
	bool SetActViewContainer (ObjContainer &rOC);
	bool GetActViewContainer (ObjContainer &rOC);
	bool SetActiveScaling (long lZoom);

// MenuBefehle
	ErrCode ChangeIdVisInfo (long = -1, bool = false);
	short ChangeVisInfoExt (HANDLEVISINFO *);
	
// FloatingMenu für Textobjekte behandeln
	bool HandleTextObjectMenu (unsigned int iItem);
	void TrackTextObjectMenu (Point Pt, long ONr, Rectangle Box);
	bool EditTextObject (pWindow, long ONr);
	void DeleteTextObject (long ONr, Rectangle Box);
	bool InitTextObjectMenu (void);
	long CreateTextObject (Punkt Pt, long lIdent, char *pText);
	bool CopyText (long lONr, Punkt &Pkt, bool fRO, long *plNewONr = NULL);	// Textobjekt doppeln
	bool ChangeTextObjectText (LONG lONr, LPCSTR pcNewText);

	Rectangle RealCanvasRect (void);

	bool ReReadCaption (string &rStrCaption, bool fDelay = false);	// Caption aus zugehörigem DBHeader lesen
	bool RetrieveBasicCaption (string &strText, bool fExpand = true, bool fPureCaption = false);

	bool ZoomIn (void);			// halber Bildschirmausschnitt
	void ZoomOut (void);		// doppelter Bildschirmausschnitt

	bool SelectIdents (void);
	bool ModifyIdents (void);
	bool DeleteIdents (void);

	bool DefineDefaultView (void);
	bool GenObjectProperties (void);

	void ReReadHeader (DatenBasisObjekt &, GeoDB &);
		
	bool SelectView (void);

	void Show (ShowState = Normal);

// liefert die Höhe des aktuellen AusgabeFensters (Druckers etc.)
	CoOrd GetOutputHeight (void);

///////////////////////////////////////////////////////////////////////////////
// Funktionen für ObjektInfos
inline bool LoadExtension (Extension &rExt) { return ObjInfoListe.LoadExtension (rExt); }
inline bool UnLoadExtension (Extension &rExt) { return ObjInfoListe.UnLoadExtension (rExt); }
inline HMENU InstallMenuItem (short iMenuID, short iMenuNum, char *pText) { return ObjInfoListe.InstallMenuItem (iMenuID, iMenuNum, pText); }
inline bool RemoveMenuItem (short iMenuID, short iMenuNum) { return ObjInfoListe.RemoveMenuItem (iMenuID, iMenuNum); }
inline pWindow GetORWindow (HWND hWnd) { return ObjInfoListe.GetORWindow (hWnd); }
inline bool HandleDeleteObject (long lONr) { return ObjInfoListe.HandleDeleteObject (lONr); }
inline bool HandleModifyIdent (long lONr) { return ObjInfoListe.HandleModifyIdent (lONr); }
inline bool HandleCancelMode (bool fCmd) { return ObjInfoListe.HandleCancelMode (fCmd); }
inline HWND SetLastActive (HWND hWnd) { return ObjInfoListe.SetLastActive (hWnd); }
inline long GetSelectedObject (HWND hWnd = NULL) { return ObjInfoListe.GetSelectedObject (hWnd); }
inline HWND GetActiveORWindow (void) { return ObjInfoListe.GetActiveORWindow(); }
inline ULONG GetORCount (void) { return ObjInfoListe.Count(); }
inline ULONG GetORObjCount (void) { return ObjInfoListe.CountObjects(); }
inline LONG GetAllSelectedObjects (LONG *plObjs) { return ObjInfoListe.GetAllSelectedObjects (plObjs); }
inline bool ChangeActiveColor (CHANGEACTIVECOLOR *pCAC) { return ObjInfoListe.ChangeActiveColor (pCAC); }
inline bool EnumSelectedObjects (bool (*pFcn)(long, bool, void *), void *pData, HWND hWnd = NULL) { return ObjInfoListe.EnumSelectedObjects (pFcn, pData, hWnd); }
inline bool EnumSelectedObjectsEx (bool (*pFcn)(long, DWORD, void *), void *pData, DWORD dwData, HWND hWnd = NULL) { return ObjInfoListe.EnumSelectedObjectsEx (pFcn, pData, dwData, hWnd); }
inline bool EnumAllObjects (bool (*fcn)(long, bool, void *), void *pData, HWND hWnd = NULL)  { return ObjInfoListe.EnumAllObjects (fcn, pData, hWnd); }
inline bool EnumORWindows (ENUMNOKEYLONG *pK) { return ObjInfoListe.EnumORWindows (pK); }
inline bool ActivateAllObj (HWND hWnd = NULL) { return ObjInfoListe.ActivateAllObj (hWnd); }
inline void CloseAllORWindows (void) { ObjInfoListe.EveryDelete(); }
inline void CloseORWindow (HWND hWnd) { ObjInfoListe.CloseORWindow (hWnd); }
inline bool HandleModifyFeature (long lONr, LPCSTR pcName) { return ObjInfoListe.HandleModifyFeature(lONr, pcName); }
inline void ShowORWindows (ShowState s) { ObjInfoListe.ShowORWindows(s); }
inline string CorrectCaption (ObjektInfo *pOIDlg, LPCSTR pcTemplate) { return ObjInfoListe.CorrectCaption (pOIDlg, pcTemplate); }

///////////////////////////////////////////////////////////////////////////////
// sonstiges
private:
	void CleanUpView (void);					// abschließendes
	char *GenerateCaptionText (char *pTemplate);

public:
///////////////////////////////////////////////////////////////////////////////
// Inline Funktionen
inline HWND Handle (Service s) { return Window :: Handle (s); }
inline void ValidateWindow (LPRECT pRc = NULL) { ValidateRect (Handle (API_CLIENT_HWND), pRc); }
inline DatenBasisObjekt &DBO (short iIndex) { return m_pDBOs -> DBO(iIndex); }	// ausführliche Variante 
inline DatenBasisObjekt &DBO (HPROJECT hPr) { return m_pDBOs -> DBO(hPr); }	// ausführliche Variante 
inline DatenBasisObjekt &DBO (void) { return m_pDBOs -> DBO(); }			// optimierte Variante
inline HPROJECT IsOpened (LPCSTR pcName) { return m_pDBOs -> IsOpened(pcName); }

inline Brush &emptyBrush (void) { return *_emptyBrush; }
inline ExtDirisWindow *GetFrame (void) { return (ExtDirisWindow *)GetParent(); }
inline bool IsValidView (void) { return m_pDBOs -> Count() > 0 && !DBO().isClosing() && DBO().DB().isOpened(); }
inline void SetExtend (ObjContainer &rOC) { DBO().SetExtend (this, rOC, AspectRatio); }
inline void ReReadHeader (void) { ReReadHeader (DBO(), DBO().DB()); }

inline bool GetPreventRepaint() { return m_fPreventRepaint ? true : false; } 
inline void SetPreventRepaint(bool fPrevent) { m_fPreventRepaint = fPrevent; }

///////////////////////////////////////////////////////////////////////////////
// Friend-Funktionen
friend	bool AddObjects (ObjFeld &rObjs, long lIdent, short iOTyp);
};

// Return values for TestDroppablePoint --------------------------------------
#define UDROP_NONE              0x0000      // Exclusive
#define UDROP_CLIENT            0x0001      // Inclusive
#define UDROP_INSETLEFT         0x0002      // L/R are exclusive
#define UDROP_INSETRIGHT        0x0004
#define UDROP_INSETHORZ         (UDROP_INSETLEFT|UDROP_INSETRIGHT)

#define UDROP_INSETTOP          0x0008      // T/B are exclusive
#define UDROP_INSETBOTTOM       0x0010
#define UDROP_INSETVERT         (UDROP_INSETTOP|UDROP_INSETBOTTOM)

#define UDROP_INSET		(UDROP_INSETHORZ|UDROP_INSETVERT)

///////////////////////////////////////////////////////////////////////////////
// TextRecherche aus Hauptfenster oder ObjektRechercheFenster
bool TextRecherche (HWND hWNd, bool fORWnd = false);
bool GenerateTextObjects (HWND hWnd, bool fORWnd = false); 

#else

class IrisWind : public StrobeWindow {
private:
// ScrollBars (WindowScrollBars)
	WndHorzScrollBar *m_pWHS;	// horizontaler WndScrollBar
	KoOrd m_kSX;			// Skalierung des ScrollRangeX	
	WndVertScrollBar *m_pWVS;	// vertikaler WndScrollBar
	KoOrd m_kSY;			// Skalierung des ScrollRangeY

// lokale Daten
	Menu IrisMenu;			// Menu
	Menu StartMenu;
	Icon IrisIcon;			// Standardikone
	Brush *_IrisBGBrush;		// Hintergrundpinsel
	Accel IrisAcc;			// Acceleratortabelle
	Accel StartAcc;			// StartUp Acceleratoren

// DruckerInfo's
	class PrinterPars *m_pPD;	// aktueller Drucker

protected:
	Point AspectRatio;		// AspectRatio
	bool myQueryClose (bool);	// EndeAbfrage

private:
	void EndCleanUp (void);         // abschließendes

#if !defined(NOGITTER)
	GitterObjekt Gitter;		// Gitternetz
#endif

	Dimension MSize;		// aktuelle Fenstergröße
	Point MOrig;

// diverse Flags
	unsigned short m_fFullRedrawOnScroll : 1;	// alles neu zeichnen beim Scrollen
	unsigned short m_fHandleCancelMode : 1;		// bei WM_CANCELMODE zeichnen abbrechen

	long m_lLastIdent;			// letzter neuer Ident
	bool m_iDrawSem;

#if defined(WIN32)
	LPMRUMENU m_pMRU;
#endif // WIN32
			
	char *GenerateCaptionText (char *pTemplate);
	
public:
// DB eröffnen
	ErrCode OpenDB (char *DB, char *UN, char *PW, short gfMode = 0);
#if defined(WIN32)
	ErrCode OpenDB (LPSTORAGE pIStorage, short gfMode = 0, LPCSTR pcName = NULL);
	bool SaveAsGeoDB (void);
	bool ExportAsGeoDB (void);
#endif // WIN32
	bool SaveGeoDB (void);
	long GetLastIdent (void);
	void SetLastIdent (long lIdent);

protected:
// Behandlung der vorhergehenden DB's
	ErrCode OpenOld (short i);
	void InitOldDBMenu (bool Insert, pMenu pM, short Pos);
	void LastDB (char *DB, char *UN, bool PWDMode, bool ROMode);

// DB abschließen
	ErrCode CloseDB (bool = true, HPROJECT hDesc = 0);

	void MenuCommand (MenuCommandEvt);      // Menu-Kommandoverarbeitung
	void MenuInit (MenuInitEvt);            // Menuinitialisierung

//	bool QueryClose (Event);                // SessionEnde abfragen
	void Expose (ExposeEvt);                // neu zeichnen

// MausEvents
	void MouseButtonDn (MouseEvt);
	void MouseButtonUp (MouseEvt);
	void MouseDrag (MouseEvt);
	void MouseMove (MouseEvt);
	void MouseButtonDblClk (MouseEvt);

	Point MousePos;                         // aktuelle MausPosition

	void ReSize (ReSizeEvt);
	void Move (MoveEvt);

// ScrollEvents
	void VertScroll (ScrollEvt);            // vertikale ScrollEvt's
	void HorizScroll (ScrollEvt);           // horizontale ScrollEvt's

	void InitWndScrollBars (void);          // ScrollBarParameter

// TimerEvent
	void EXPORTTRIAS Strobe (StrobeEvt);

// Focus hat sich geändert
	void FocusChange (FocusChangeEvt);

// KeyEvents
	void KeyDown (KeyEvt);
	void KeyUp (KeyEvt);

// PaletteHandling
	void EXPORTTRIAS  PaletteChange (PaletteChangeEvt);

// DragRechteck
	CDragObject *DRO;
	Brush *_emptyBrush;                     // Pinsel für DrawRechteck

// Stack der fortlaufenden Vergrößerung (Bildfolge)
	ObjContainerStack actClip;              // Bildausschnittsfolge

// Flag, ob gezeichnet werden soll
	bool RePaintFlag;

// Drucken etc.
	bool PrintGraphics (char *JobName);		// Bildchen ausgeben
	bool PrinterMode (void);			// Druckereinstellung
	Point GetAspectRatio (void);

// DateiName des aktuell selektierten RechercheScriptes
	char *SelScriptFile;

// HilfeEvent
	void HelpRequest (HelpRequestEvt e);

// Dragging
	bool DragFunc (WPARAM);
	LRESULT Dispatch (Event);

public:
	void InitMenues (void);
	bool InitProjectMenu (void);

// Konstruktor
		IrisWind (Rectangle &MWnd);

// public Funktionen
	HWND Handle (Service s) { return Window :: Handle (s); }
	void ValidateWindow (LPRECT pRc = NULL) { 
		ValidateRect (Handle (API_CLIENT_HWND), pRc); 
	}

// Funktion zur ObjektRecherche
	ObjektInfoListe ObjInfoListe;           // Liste der ModeLessDialog's
	void ObjektRecherche (DragRectangleObject &DRO, ObjContainer &OC, bool);
	HWND CreateObjektInfo (struct tagDEXXCREATEOBJEKTINFO *pcrOI, ExtensionList &rEL);
	HWND CreateObjektInfo (CREATEOBJEKTINFO *pcrOI, ExtensionList &rEL);

	bool ShowIdentSel (void);
	void ShowEditHeader (void);
	bool ShowTextRecherche (void);
	bool DeleteViews (void);
	bool CreateNewGeoDB (void);		// interactive

// Komplexrecherche
	ErrCode ShowOIRechResults (ObjFeld &);

#if !defined(WIN32)
	void MenuSelectSchrank (void);
	void MenuSelectNomen10 (void);
	void MenuSelectNomen25 (void);
	void MenuSelectNomen50 (void);
#endif // !WIN32

	bool MenuSelectMasstab (void);

// Umgebung
	class CDBOArray *m_pDBOs;
	DatenBasisObjekt &DBO (short iIndex)	// ausführliche Variante 
		{ return m_pDBOs -> DBO(iIndex); }
	DatenBasisObjekt &DBO (void)			// optimierte Variante
		{ return m_pDBOs -> DBO(); }

	Brush &emptyBrush (void) { return *_emptyBrush; }

// Menu liefern
	pMenu MainMenu (void) { return &IrisMenu; }
	pMenu StartUpMenu (void) { return &StartMenu; }
	pAccel MainAcc (void) { return &IrisAcc; }

// KommandozeilenMeldung ausgeben
//	void PrintUsage (void);
	ErrCode ChangeIdVisInfo (long = -1, bool = false);
	short ChangeVisInfoExt (HANDLEVISINFO *);
	
// FloatingMenu für Textobjekte behandeln
	bool HandleTextObjectMenu (unsigned int iItem);
	void TrackTextObjectMenu (Point Pt, long ONr, Rectangle Box);
	void EditTextObject (pWindow, long ONr);
	void DeleteTextObject (long ONr, Rectangle Box);
	bool InitTextObjectMenu (void);
	long CreateTextObject (Punkt Pt, long lIdent, char *pText);

	Rectangle RealCanvasRect (void);

	bool ReReadCaption (void);	// Caption aus zugehörigem DBHeader lesen
	bool EnumProjects (ENUMNOKEY *pK);
	HPROJECT GetProjectHandle (LPCSTR);
	HPROJECT MakeProjectActive (HPROJECT hPr);

	bool ZoomIn (void);		// halber Bildschirmausschnitt
	void ZoomOut (void);		// doppelter Bildschirmausschnitt

	bool SelectIdents (void);
	bool ModifyIdents (void);
	bool DeleteIdents (void);

friend	bool AddObjects (ObjFeld &rObjs, long lIdent, short iOTyp);
	
	bool DefineDefaultView (void);
	bool GenObjectProperties (void);

	void ReReadHeader (DatenBasisObjekt &, GeoDB &);
	bool SetActViewContainer (ObjContainer &rOC);
	bool GetActViewContainer (ObjContainer &rOC);

	bool SelectView (void);

// Destruktor
		~IrisWind (void);

friend class IrisPrinter;

///////////////////////////////////////////////////////////////////////////////
// InlineFunktionen
inline void ReReadHeader (void) { ReReadHeader (DBO(), DBO().DB()); }
};

#endif // WIN32

#endif // _IRISWIND_HXX

