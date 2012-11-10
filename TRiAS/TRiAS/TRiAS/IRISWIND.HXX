// ViewFenster eines Projektes ------------------------------------------------
// File: IRISWIND.HXX

#if !defined(_IRISWIND_HXX)
#define _IRISWIND_HXX

// Stackdeklaration für Liste der fortlaufenden Bildausschnitte ---------------
Stack (ObjContainer);   // Deklaration der Klassen für einen Stack

// Viewfensterklasse ----------------------------------------------------------
typedef struct tagHANDLEVISINFO HANDLEVISINFO;

#include <xtensnxx.h>
#if defined(_USE_FLICKERFREE_DRAWING)
#include <MemoryDC.h>
#endif // _USE_FLICKERFREE_DRAWING

#if !defined(_OLD_DRAGNDROP)
#include "DragDropCallback.h"
#endif // !defined(_OLD_DRAGNDROP)

///////////////////////////////////////////////////////////////////////////////
// Klassendeklarationen 
class PrinterPars;
class CDBOArray;

///////////////////////////////////////////////////////////////////////////////
// sonstige FunktionsDeklarationen 
short OTypToBits (ObjTyp iOTyp);
ObjTyp BitsToOTyp (short iBits);

///////////////////////////////////////////////////////////////////////////////
// ViewKlasse
class IrisWind : 
	public ChildAppWindow
#if !defined(_OLD_DRAGNDROP)
	, public CDragDropCallback
#endif // !defined(_OLD_DRAGNDROP)
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

// MouseBttnSupport etc.
	unsigned char m_iLeftButtonSem;				// Semaphor für linke MausTaste
	unsigned char m_iRightButtonSem;			// Semaphor für rechte Maustaste
	unsigned int m_fTrackObjectMenuFlag : 1;	// Semaphore für Floating Mneu

// diverse Flags
	unsigned int m_fFullRedrawOnScroll : 1;		// alles neu zeichnen beim Scrollen
	unsigned int m_fHandleCancelMode : 1;		// bei WM_CANCELMODE zeichnen abbrechen
	unsigned int m_fRePaintFlag : 1;			// Flag, ob gezeichnet werden soll
	unsigned int m_fFirstDrawing : 1;			// erstes Anzeigen des Fensters
	unsigned int m_fReReadCaption : 1;			// Caption muß neu gelesen werden
	unsigned int m_fCommitOnClose : 1;			// in Close Commit rufen
	unsigned int m_fCleanedUp : 1;				// bereits aufgeräumt
	unsigned int m_fHasAspectRatio : 1;			// AspectRatio ist initialisiert

#if !defined(_OLD_DRAGNDROP)
	unsigned int m_fIsDropSource : 1;			// this window is dropsource
	IDropTarget *m_pDropTgt;
#endif // _OLD_DRAGNDROP

	bool m_fPreventRepaint;						// Neuzeichnen unterbinden
	bool  m_fIsClosing;							// Fenster wird derzeit geschlossen

	class CPrintBase *m_pPrinter;				// derzeit wird gedruckt/vorgeschaut

#if defined(_USE_FLICKERFREE_DRAWING)
	CMemoryDC *m_pMemDC;
	HBITMAP m_hCanvasBmp;
	bool m_fShouldRedraw;
	bool m_fShouldRedrawRect;	
#endif // _USE_FLICKERFREE_DRAWING

// Texte editieren
	INT_PTR m_lTextONr;
	HMENU m_hTextMenu;
	Rectangle m_rcTextSel;
	Point m_ptTextPos;

// Menuverwaltung für EditHeader
	UINT m_uiEditHeader;

protected:
	CDragObject *m_pDRO;						// SelektionsObjekt
	Brush *_emptyBrush;							// Pinsel für DrawRechteck
	CDBOArray *m_pDBOs;							// Liste aller offenen GeoDB's
	DWORD m_dwCookie;							// ConnectionCookie for Prj
	DWORD m_dwCookieViews;						// ViewCookie for Prj

	PrinterPars *m_pPD;							// aktueller Drucker

// Stack der fortlaufenden Vergrößerung (Bildfolge)
	ObjContainerStack actClip;					// Bildausschnittsfolge

// eingestellte Vergrößerung wiederanzeigen
	long m_lFakeZoom;

public:
///////////////////////////////////////////////////////////////////////////////
// DB-Funktionen
	ErrCode OpenDB (LPCSTR DB, LPCSTR UN, LPCSTR PW, short gfMode = 0, DWORD dwMode = 0L);
	ErrCode OpenDB (LPSTORAGE pIStorage, short gfMode = 0, LPCSTR pcName = NULL);
	HRESULT OpenDB (ITRiASProject *pIPrj, OPENMODE rgMode = OPENMODE_Normal);
	HRESULT OpenConnections (ITRiASProject *pIPrj, DatenBasisObjekt &rDBO);

	bool SaveAsGeoDB (LPCSTR pcAppend = NULL);
	bool ExportAsGeoDB (void);
	bool SaveGeoDB (bool fAutoSave = false);
	bool CloseDocument (void);
	bool PrioritySelect (void);

	ErrCode CloseDB (bool fCommit, HPROJECT hDesc = 0);		// DB abschließen
	ErrCode AskUserToClose (bool &rfCommit, bool fForceCleanUp = false, bool fDefaultCommit = true, HPROJECT hPr = 0);
	ErrCode HandleSaveCopy (LPCSTR pcName, bool &rfCommit, bool fSave);
	ErrCode HandleSaveRO (LPCSTR pcName, bool &rfCommit, bool fSave);

	long GetLastIdent (void);
	void SetLastIdent (long lIdent);

	bool IsInitialContainer (ObjContainer &rOC);
	bool InitOverView (ObjContainer &rOC);

#if !defined(_OLD_DRAGNDROP)
///////////////////////////////////////////////////////////////////////////////
// Drag'n Drop
// CDragDropCallback
	HRESULT DragEnter (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	HRESULT DragOver (DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	HRESULT DragLeave (void);
	HRESULT Drop (IDataObject *pIDataSource, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);

	bool FQueryPasteFromData (IDataObject *pIDataObject);
	bool FPasteFromData (IDataObject *pIDataObject);
	UINT TestDroppablePoint (POINTL *pPt);
	void GiveFeedBack (POINTL *pPt, bool fRemove = false, bool fDraw = true);
	bool IsDropSourceInst (void);

// supporting functions
	bool IsDropSource (void) { return m_fIsDropSource ? true : false; }
	HWND GetDropSourceORWnd() { return ObjInfoListe.GetDropSourceORWnd(); }
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
#if defined(_USE_FLICKERFREE_DRAWING)
	BOOL DrawCallUp (DrawObject *pDO, BOOL fForce);
#endif // _USE_FLICKERFREE_DRAWING

	bool myQueryClose (bool fForceCleanUp);	// EndeAbfrage
	bool InitWndScrollBars (void);          // ScrollBarParameter

// Drucken etc.
	bool PrintGraphics (char *JobName, const ObjContainer &rOC);	// Bildchen ausgeben
	int ShowPrintLayoutDialog (PRINTLAYOUTDIALOG *pLDlg);
	int ShowPrintLayoutDialog (Window *pW, const ObjContainer &rOC, class PrintLayout **ppPL, bool fPreview = false);
	int PrintPreview (PRINTPREVIEW *pPP);
	int EndPrintPreview (PRINTPREVIEW *pPP);
	
	bool DragFunc (WPARAM);					// Dragging

///////////////////////////////////////////////////////////////////////////////
// MenuKommandos
	bool doSaveDB (void);
	bool doAutoSaveDB (void);
	bool doSaveAsGeoDB (void);
	bool doExportAsGeoDB (void);
	bool doEditHeader (void);
	bool doShowIdentSel (void);
	bool doDeleteViews (void);
	bool doRebuild (HPROJECT hPr = HACTCONNECTION);
	bool doDraw (void);
	bool doPreventRepaint (void);
	bool doCancel (void);
	bool doPrint (void);
	bool doTextRech (void);
	bool doTextReplace (void);
	bool doClassify (void);			// #HK001107
	bool doCoords (void);
	bool doSelectMasstab (void);
//	bool doSaveOpt (void);
	bool doExport (void);
	bool doChangeBKColor (void);
	bool doSymbolPars (void);
	bool doPriority (void);
	bool doCopyClipBoard (void);
	bool doSelSichtCont (void);
	bool doDelSichtCont (void);
	bool doLegende (MenuCommandEvt e);
	bool doOverView (MenuCommandEvt e);
	bool doViewTexts (void);
	bool doSelAusschnitt (void);
	bool doPrevAusschnitt (void);
	bool doSelectView (void);
	bool doZoomOut (void);
	bool doZoomIn (Punkt *pPt = NULL);
	bool doRestoreContainer (void);
	bool doSelIdents (void);
	bool doDelIdents (void);
	bool doModIdents (void);
	bool doCopyObjectsIdent (void);
	bool doCopyColors (void);
	bool doCoordMode (void);
	bool doGenTextObjects (void);
	bool doDeleteObjProps (void);

	bool doDefaultCmd (MenuCommandEvt e);
	bool doHandleTextObjectMenu (MenuCommandEvt e);
	bool doTools (MenuCommandEvt e);

#if !defined(NOPROJEKTION)
	bool doResetPrj (void);
	bool doWorldPrj (void);
#endif

	bool InitEditHeaderMenu (HMENU hMenu, HMENU hActMenu);
	bool doEditHeader (int iDataSource);

public:
///////////////////////////////////////////////////////////////////////////////
// Konstruktor, Destruktor, Initialisierung
		IrisWind (ExtDirisWindow *pFrame);
		~IrisWind (void);

static IrisWind *CreateInstance (ExtDirisWindow *pFrame, IrisWind *& rpView, BSTR bstrName);

	bool FInit (BSTR bstrName);
	bool InitializeView (ExtDirisWindow *pFrame, ITRiASProject *pIPrj, OPENMODE rgMode = OPENMODE_Normal);

#if defined(_USE_LEGACY_CODE)
static IrisWind *CreateInstance (ExtDirisWindow *pFrame, IrisWind *& rpView, LPCSTR pcDBName = NULL, LPCSTR pcUserName = NULL, LPCSTR pcPassWord = NULL, short gfMode = 0, DWORD dwMode = 0L);

	bool FInit (ExtDirisWindow *pFrame, LPCSTR pcDBName, LPCSTR pcUserName, LPCSTR pcPassWord, short gfMode, DWORD dwMode);
#endif // defined(_USE_LEGACY_CODE)

///////////////////////////////////////////////////////////////////////////////
// public Funktionen
	bool RenderGeoDB (RENDERGEODB *pRDB);
	Point GetAspectRatio (void);

// Funktion zur ObjektRecherche
	void ObjektRecherche (DragRectangleObject &DRO, ObjContainer &OC, bool);
	HWND CreateObjektInfo (DEXXCREATEOBJEKTINFO *pcrOI, ExtensionList &rEL);
	HWND CreateObjektInfo (CREATEOBJEKTINFO *pcrOI, ExtensionList &rEL);

	bool ShowIdentSel (void);
	bool ShowEditHeader (IUnknown *pIUnkSite, HPROJECT hPr);

	bool DeleteViews (void);
	bool EnumProjects (ENUMNOKEY *pK);
	HPROJECT GetProjectHandle (LPCSTR);
	HPROJECT MakeProjectActive (HPROJECT hPr);

#if defined(_USE_LEGACY_CODE)
	bool CreateNewGeoDB (int rgMode);		// interactive
#endif // defined(_USE_LEGACY_CODE)

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
	bool TrackTextObjectMenu (Point Pt, long ONr, Rectangle Box);
	bool EditTextObject (pWindow, long ONr);
	void DeleteTextObject (long ONr, Rectangle Box);
	bool InitTextObjectMenu (void);
	long CreateTextObject (Punkt Pt, long lIdent, const char *pText, TextObjTyp rgToTyp = TOT_TEXT);
	bool GetTextObject (long lONr, Punkt &rPt, long &lIdent, string &rStrText, TextObjTyp &rToTyp);
	bool CopyText (long lONr, Punkt &Pkt, bool fRO, long *plNewONr = NULL);	// Textobjekt doppeln
	bool CopyFeatures(INT_PTR lONrDest, INT_PTR lONrSrc);

	bool ChangeTextObjectText (LONG lONr, LPCSTR pcNewText);
	bool GenerateUniqueIdent (long lONr);
	bool RePaintTextObject (long lONr, LPCSTR pcNewText = NULL);

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

	long IsDrawing() { return m_iDrawSem; }

	void ResetMouseFlags()
	{
		m_iLeftButtonSem = 0;			// Semaphor für linke MausTaste
		m_iRightButtonSem = 0;			// Semaphor für rechte Maustaste
	}

///////////////////////////////////////////////////////////////////////////////
// Funktionen für ObjektInfos
inline bool LoadExtension (Extension &rExt) { return ObjInfoListe.LoadExtension (rExt); }
inline bool UnLoadExtension (Extension &rExt) { return ObjInfoListe.UnLoadExtension (rExt); }
inline HMENU InstallMenuItem (short iMenuID, short iMenuNum, short iMenuPos, char *pText) { return ObjInfoListe.InstallMenuItem (iMenuID, iMenuNum, iMenuPos, pText); }
inline bool RemoveMenuItem (short iMenuID, short iMenuNum) { return ObjInfoListe.RemoveMenuItem (iMenuID, iMenuNum); }
inline pWindow GetORWindow (HWND hWnd) { return ObjInfoListe.GetORWindow (hWnd); }
inline bool HandleDeleteObject (long lONr) { return ObjInfoListe.HandleDeleteObject (lONr); }
inline bool HandleModifyIdent (long lONr) { return ObjInfoListe.HandleModifyIdent (lONr); }
inline bool HandleCancelMode (bool fCmd) { return ObjInfoListe.HandleCancelMode (fCmd); }
inline HWND SetLastActive (HWND hWnd) { return ObjInfoListe.SetLastActive (hWnd); }
inline long GetSelectedObject (HWND hWnd = NULL) { return ObjInfoListe.GetSelectedObject (hWnd); }
inline HWND GetActiveORWindow (void) { return ObjInfoListe.GetActiveORWindow(); }
inline HWND SetActiveORWindow (HWND hWnd) { return ObjInfoListe.SetActiveORWindow(hWnd); }
inline ULONG GetORCount (void) { return ObjInfoListe.Count(); }
inline ULONG GetORObjCount (void) { return ObjInfoListe.CountObjects(); }
inline LONG GetAllSelectedObjects (LONG *plObjs) { return ObjInfoListe.GetAllSelectedObjects (plObjs); }
inline bool ChangeActiveColor (CHANGEACTIVECOLOR *pCAC) { return ObjInfoListe.ChangeActiveColor (pCAC); }
inline BOOL EnumSelectedObjects (BOOL (*pFcn)(long, BOOL, void *), void *pData, HWND hWnd = NULL) { return ObjInfoListe.EnumSelectedObjects (pFcn, pData, hWnd); }
inline BOOL EnumSelectedObjectsEx (BOOL (*pFcn)(long, DWORD, void *), void *pData, DWORD dwData, HWND hWnd = NULL) { return ObjInfoListe.EnumSelectedObjectsEx (pFcn, pData, dwData, hWnd); }
inline BOOL EnumAllObjects (BOOL (*fcn)(long, BOOL, void *), void *pData, HWND hWnd = NULL)  { return ObjInfoListe.EnumAllObjects (fcn, pData, hWnd); }
inline BOOL EnumORWindows (ENUMNOKEYLONG *pK) { return ObjInfoListe.EnumORWindows (pK); }
inline bool ActivateAllObj (HWND hWnd = NULL) { return ObjInfoListe.ActivateAllObj (hWnd); }
inline void CloseAllORWindows (void) { ObjInfoListe.EveryDelete(); }
inline void CloseORWindow (HWND hWnd) { ObjInfoListe.CloseORWindow (hWnd); }
inline bool HandleModifyFeature (long lONr, LPCSTR pcName) { return ObjInfoListe.HandleModifyFeature(lONr, pcName); }
inline void ShowORWindows (ShowState s) { ObjInfoListe.ShowORWindows(s); }
inline string CorrectCaption (ObjektInfo *pOIDlg, LPCSTR pcTemplate) { return ObjInfoListe.CorrectCaption (pOIDlg, pcTemplate); }
inline bool RefreshObjectEntries (INT_PTR lONr = NULL) { return ObjInfoListe.RefreshObjectEntries(lONr); }

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
inline bool IsValidView (void) { return (NULL != m_pDBOs) && (m_pDBOs -> Count() > 0) && DBO().IsValidDocument(); }	// Projekt und Datasource ok
inline bool IsValidProject (void) { return (NULL != m_pDBOs) && (m_pDBOs -> Count() > 0); }	// Projekt ok
inline void SetExtend (ObjContainer &rOC, long lFakeZoom = 0) 
	{ 
		m_lFakeZoom = lFakeZoom;
		DBO().SetExtend (this, rOC, AspectRatio); 
		SetShouldRedraw(); 
	}
inline void ReReadHeader (void) { ReReadHeader (DBO(), DBO().DB()); }
inline void ResetObjContainerStack() { while (actClip.Top().isValid()) actClip.Pop(); }

inline void SetFullRedrawOnScroll (bool fFlag) { m_fFullRedrawOnScroll = fFlag; }
inline bool GetFullRedrawOnScroll() { return m_fFullRedrawOnScroll; }
inline void SetBackground (Brush *pB)
	{ Brush *pOld = ChangeBackground (pB); if (NULL != pOld && pOld != _IrisBGBrush) delete pOld;	}

inline bool GetPreventRepaint() { return m_fPreventRepaint ? true : false; } 
inline void SetPreventRepaint(bool fPrevent) { m_fPreventRepaint = fPrevent; }

inline void ResetSelectionRect() { DELETE_OBJ(m_pDRO); }

#if defined(_USE_FLICKERFREE_DRAWING)
inline void SetShouldRedraw (bool fDeleteBmp = true) 
	{ 
		m_fShouldRedraw = true; 
		if (fDeleteBmp && NULL != m_hCanvasBmp) { 
		// Bitmap vollständig löschen
			::DeleteObject (m_hCanvasBmp); 
			m_hCanvasBmp = NULL; 
		} else
			m_fShouldRedrawRect = true;
	}
inline bool GetShouldRedraw() { return m_fShouldRedraw; }
#else
inline void SetShouldRedraw(bool fDeleteBmp = true) {}
inline bool GetShouldRedraw() { return true; }
#endif // defined(_USE_FLICKERFREE_DRAWING)

///////////////////////////////////////////////////////////////////////////////
// Friend-Funktionen
friend	bool AddObjects (ObjFeld &rObjs, long lIdent, short iOTyp);

///////////////////////////////////////////////////////////////////////////////
// Friend-Klassen
friend class DatenBasisObjekt;
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

#endif // _IRISWIND_HXX

