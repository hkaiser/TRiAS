// Funktionen fuer DatenBasisObjekt --------------------------------------------
// File: DBOBJEKT.CXX

#include "triaspre.hxx"

#include <registry.hxx>
#include <fnamestr.h>

#include <TRiASMode.h>
#include <dirisole.h>
#include <xtensnxx.h>
#include <xtensnd.h>

#include "triasres.h"

#include <funcs03.h>
#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <relliste.hxx>
#include <Com/PropertyHelper.h>
#include <NativeView.h>
#include <dbmsg.hmc>

#include "strings.h"

#include "ExtMain3.hxx"
#include "clbmpobj.hxx"
#include "viewtree.hxx"
#include "Schrift.hxx"
#include "relobj.hxx"
#include "DrawingStatusWrapper.h"

#if defined(_USE_FLICKERFREE_DRAWING)
#include "DrawCallUpMode.h"
#endif // _USE_FLICKERFREE_DRAWING

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// globale Daten
extern short GCancelFlag;

extern HPALETTE hPalette;		// AnwendungsFarbPalette
extern HINSTANCE hInstance;

extern bool PrintEFlag;
extern DWORD g_iHideFlags;

extern bool LegendToRepaint;
extern bool GenerateLegendOnly;

extern char PbdDBDir[_MAX_PATH+1];

extern short VTypToBits (VisType);
extern short OTypToBits (ObjTyp);

///////////////////////////////////////////////////////////////////////////////
// externe Funktionsdeklarationen 
void EXPORTTRIAS SetNotVisible (void *pObj);

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASViews);		// WTRiASViews
DefineSmartInterface(TRiASView);		// WTRiASView
DefineSmartInterface(TRiASConnections);
DefineSmartInterface(TRiASConnection);
DefineSmartInterface(TRiASViewItems);	// WTRiASViewItems
DefineSmartInterface(TRiASViewItem);	// WTRiASViewItem
DefineSmartInterface2(DVisInfo, IID_DVisInfo);	// WDVisInfo
DefineSmartInterface(TRiASProperties);
DefineSmartInterface(TRiASFeatures);		// WTRiASFeatures
DefineSmartInterface(EnumVARIANT);		// WEnumVARIANT
DefineSmartInterface(TRiASFeature);		// WTRiASFeature
DefineSmartInterface(TRiASSimpleObjects);		// WTRiASSimpleObjects

#if defined(_USE_FLICKERFREE_DRAWING)
///////////////////////////////////////////////////////////////////////////////
// Testen, ob App::Exec gerufen werden soll
bool DatenBasisObjekt::DoIdleLoop(bool fForceDrawCallUp)
{
	if (!(g_dwDrawingMode & DRAWMODE_IdleDuringDraw))
		return false;		// sowieso kein Idle

	if ((g_dwDrawingMode & DRAWMODE_IdleAfterDrawOnly) && fForceDrawCallUp)
		return false;		// nur direkt nach Zeichnen Idle'n

	if (!(g_dwDrawingMode & DRAWMODE_IdleAfterInterval))
		return true;

DWORD dwTicks = m_dwTicks;

	m_dwTicks = ::GetTickCount();
	if (m_dwTicks > dwTicks + g_dwTicksBetweenIdleLoops)
		return true;		// jetzt Appexec rufen

	m_dwTicks = dwTicks;	// bleibt doch beim alten
	return false;
}
#endif // defined(_USE_FLICKERFREE_DRAWING)

///////////////////////////////////////////////////////////////////////////////
// Konstruktor
DatenBasisObjekt::DatenBasisObjekt (void)
	: m_fToClose(true),
	  ExtShapeObject (Point (0, 0), Dimension (), NULL, NULL)
{
	m_fPosTextAtBaseLine = false;
	m_fCompatibility16 = false;
	m_fIsFile = true;
	m_fIsOpening = false;
	m_fIsActiveProject = false;
	m_fIsDeletingView = false;
	m_lActScale = 0L;
	m_pViewWnd = NULL;
	m_lObjGuidMCode = 0L;
	m_fSavingDocument = false;	// true während speichern
	m_fLastDirty = false;
	m_fLimitSearches = false;
	m_fIgnoreSearchResultOptions = false;

	ResetIdentScaleMCodes (true);

	_toPaint = PF_INVALID;
	_DBOCont = ObjContainer (0, 0, 0, 0);

	_pCT = NULL;
	M() = 1.0;
	
	_SightMenu = NULL;
	_SightFlag = false;
	m_pViews = NULL;

	_iDrawSem = false;
	m_ptsToDraw = NULL;
	m_pCoords = NULL;
	m_lCntPts = 0L;

	m_pBmp15sw = NULL;
	m_pBmp23sw = NULL;
	m_pBmp32sw = NULL;
	m_iBmpCnt = 0;	
	m_fNewPnts = false;
	m_pPunktIDs = NULL;
	m_pClsIdents = NULL;

	m_lObjCnt = -1L;
	
	m_pGeoDBs = NULL;
	_Idents = NULL;
	_Shapes = NULL;

	m_pLoadedOC = NULL;

#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
	{
	CCurrentUser resBkColor ("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\Config");
	DWORD dwColor = 0x00C0C0C0L;

		resBkColor.GetDWORD ("BackGroundColor", dwColor);
		SetBkColor ((Color &)dwColor);
	} 
#if defined(ENABLE_WIN32S_CODE)
	else
		SetBkColor (Color ((ColorVal)192, (ColorVal)192, (ColorVal)192));
#endif // ENABLE_WIN32S_CODE

#if defined(_USE_FLICKERFREE_DRAWING)
	m_dwTicks = 0;
#endif // defined(_USE_FLICKERFREE_DRAWING)

	m_fToClose = false;		// jetzt kann geöffnet werden
}

IrisWind *DatenBasisObjekt::AttachViewWindow (IrisWind *pViewWnd)
{
IrisWind *pOldWnd = m_pViewWnd;

	m_pViewWnd = pViewWnd;
	return pOldWnd;
}

///////////////////////////////////////////////////////////////////////////////
//
void DatenBasisObjekt::ResetIdentScaleMCodes (bool fForce)
{
	if (fForce) {
		m_lScaleMCode[VT_Punkt] = 0L;
		m_lScaleMCode[VT_Linie] = 0L;
		m_lScaleMCode[VT_Flaeche] = 0L;
		m_lScaleMCode[VT_Text] = 0L;
	} else {
		if (-1L == m_lScaleMCode[VT_Punkt])
			m_lScaleMCode[VT_Punkt] = 0L;
		if (-1L == m_lScaleMCode[VT_Linie])
			m_lScaleMCode[VT_Linie] = 0L;
		if (-1L == m_lScaleMCode[VT_Flaeche])
			m_lScaleMCode[VT_Flaeche] = 0L;
		if (-1L == m_lScaleMCode[VT_Text])
			m_lScaleMCode[VT_Text] = 0L;
	}
	m_lScaleMCode[VT_Default] = 0L;
}

// BitmapsStreifen für Punktobjekte laden -------------------------------------
bool DatenBasisObjekt::LoadBitmapBars (bool fLookAtHeader) 
{
	if (fLookAtHeader) {
	// an Hand des Headers und des Types entscheiden, ob neue oder alte Punktsymbole
	// Verwendung finden sollen
#if defined(_FORCE_LEGACY_CODE)
		if (DB().GetDBVersion() >= VERSION0500000B) 
#endif // defined(_FORCE_LEGACY_CODE)
		{
		// neue DatenBasis
		HeaderEntry rsOldPts (DB(), IDS_USEOLDPOINTSTYLE);

			if (rsOldPts.EntryLong (0) == 1) return true;	// alte Punkte
		} 
#if defined(_FORCE_LEGACY_CODE)
		else {
		// alte DatenBasis
		HeaderEntry rsNewPts (DB(), IDS_USENEWPOINTSTYLE);

			if (rsNewPts.EntryLong (0) == 0) return true;	// alte Punkte
		}
#endif // defined(_FORCE_LEGACY_CODE)
	}

// neue Punktsymbole verwenden
	DELETE_OBJ (m_pBmp15sw);
	DELETE_OBJ (m_pBmp23sw);
	DELETE_OBJ (m_pBmp32sw);

	m_pBmp15sw = CBitmapBar::CreateInstance (ResID (IDB_BITMAP_15_SW), ResID (IDR_BMPOFFSETS15));
	m_pBmp23sw = CBitmapBar::CreateInstance (ResID (IDB_BITMAP_20_SW), ResID (IDR_BMPOFFSETS23));
	m_pBmp32sw = CBitmapBar::CreateInstance (ResID (IDB_BITMAP_32_SW), ResID (IDR_BMPOFFSETS32));

	DELETE_OBJ (m_pPunktIDs);
	m_pPunktIDs = CMapPunktID::CreateInstance (ResID (IDR_PUNKTIDTABLE));
	
	if (NULL == m_pBmp15sw || NULL == m_pBmp23sw || NULL == m_pBmp32sw || NULL == m_pPunktIDs) 
		return false;

// Anzahl der Punktsymbole feststellen
Dimension dim = m_pBmp15sw -> GetFullSize();
		
	m_iBmpCnt = short(dim.Width()/dim.Height());
	m_fNewPnts = true;
	return true;
}	


// Umschließendes Rechteck -----------------------------------------------------
Rectangle EXPORTTRIAS DatenBasisObjekt::BoundingBox (void) 
{
	Point Pt1 = OCtoDC (_DBOCont.XMin(), _DBOCont.YMin());
	Point Pt2 = OCtoDC (_DBOCont.XMax(), _DBOCont.YMax());

return Rectangle (Pt1, Pt2);
}

void EXPORTTRIAS SetNotVisible (void *pObj) 
{
	((CIdentifikator *)pObj) -> SetInvisible();
}

// Ganzes DBObjekt zeichnen ---------------------------------------------------
void DatenBasisObjekt::DrawEx (DWORD dwData) 
{
	if (!Transformation::IsValid() || isSaving())
		return;							// nichts da, nichts zeichnen

	if (!_iDrawSem) {
		_iDrawSem = true;				// nur einmal gleichzeitig zeichnen

	HDC hDCs[2];
	
		hDCs[0] = Handle (API_DRAWOBJECT_HDC);
		hDCs[1] = Handle (API_TARGET_HDC);

		SaveDC (hDCs[0]);				// alten DC speichern
		DotsPerMM() = GetDotsPerMM (hDCs[1]);

	// ExposedArea in DB-Koordinaten umrechnen
	Rectangle rcEA = EA();
	ObjContainer ocT (rcEA);
	
		SetExpOC (ocT);					// ExposedArea umrechnen
		EvalMasstab (GetCanvas());		// Masstabskoeffizienten berechnen

#if !defined(WIN16)
	// Regions haben in Metafiles nichts zu suchen !?
		if (!PrintEFlag || ::GetObjectType (hDCs[0]) != OBJ_ENHMETADC)
#endif // WIN16
		{
		// CompoundRegion generieren
		Rectangle *pRc = (dwData != 0) ? (Rectangle *)dwData : &rcEA;
		HRGN hRgn = CreatePaintRegion (hDCs[0], *pRc, ClipRegionONr());

			SelectClipRgn (hDCs[0], hRgn);
			DeleteObject (hRgn);		// Region wieder löschen
		}
		FullDCInit() = FDC_NoInit;		// nicht für jedes Objekt DC initialisieren

	// Palette einstellen       
	HPALETTE hOldPalette;

		if (hPalette != NULL) {
			hOldPalette = SelectPalette (hDCs[0], hPalette, false);
			RealizePalette (hDCs[0]);
		}

	int oldBkMode = SetBkMode (hDCs[0], TRANSPARENT);
	int oldFillMode = SetPolyFillMode (hDCs[0], ALTERNATE);

	// alle Idents als nicht gezeichnet markieren wenn Legende neu 
	// gezeichnet werden soll
		if (LegendToRepaint)
			Idents().IdentTree().Every (SetNotVisible);

	// Objektgeometrien Lesen und Zeichnen / nur Zeichnen
		GetAsyncKeyState (VK_ESCAPE);	// Buffer rücksetzen

		DEXN_EraseBackGround (hDCs);	// Hintergrund zeichnen
		App::Exec(ExecIdleOnly);		// UI richten (WIN32)

		SetLoadMode (IsLoadedRect(ocT));

	ErrCode RC = NextDraw (dwData);		// alles andere zeichnen

		if (!IsTRiASDBBased() && !(GCancelFlag & GCFAppClosed)) 	// wenn App nicht geschlossen wurde
			DEXN_PaintTopLayer (hDCs);			// DeckerLayer zeichnen
		
		if (EC_OKAY == RC)		// ohne 'Abbrechen' und ohne Fehler fertig geworden
			AddLoadedRect (ocT);

	// DC rücksetzen
		if (hPalette)
			SelectPalette (hDCs[0], hOldPalette, false);
		SetPolyFillMode (hDCs[0], oldFillMode);
		SetBkMode (hDCs[0], oldBkMode);

		RestoreDC (hDCs[0], -1);		// ursprünglichen DC wiederherstellen

		_iDrawSem = false;
		FreeDrawBuffer();				// 'globalen' TransformationsBuffer freigeben
	}
}

///////////////////////////////////////////////////////////////////////////////
// Impressum anzeigen
bool DatenBasisObjekt::DrawImpressum(HDC hDC, HDC hTargetDC, Rectangle rcCanvas)
{
// Font erzeugen und selektieren
ResString rsArial (IDS_ARIAL, 20);
Dimension mm (GetDotsPerMM (hTargetDC));
Rectangle rc (Point(rcCanvas.Left()+mm.Width(), rcCanvas.Top()-mm.Height()), Dimension(rcCanvas.Width()-2*mm.Width(), 0));

#if !defined(_TRIAS_OLDIMPLEMENTATION2)
CVFont ImprFont (Swiss, Dimension(0, -5*mm.Height()), rsArial);
#else
Font ImprFont (Swiss, Dimension(0, -5*mm.Height()), rsArial);
#endif // !defined(_TRIAS_OLDIMPLEMENTATION2)
	
//	if (fBold) ImprFont.SetBold();
//	if (fItalic) ImprFont.SetItalic();
//	if (fUnderline) ImprFont.SetUnderline();
	ImprFont.Init();
	
HFONT hOldFont = (HFONT)SelectObject (hDC, ImprFont.Handle (API_FONT_HFONT));
int iBkMode = SetBkMode (hDC, TRANSPARENT);

// zuerst im ProjektHeader nachsehen
GEODBHDRENTRY hdrEntry;
char cbBuffer[_MAX_PATH];
bool fReturn = false;

	INITSTRUCT (hdrEntry, GEODBHDRENTRY);
	strncpy (hdrEntry.hdrKey, g_cbImpressum, 16);
	hdrEntry.lphdrText = cbBuffer;
	hdrEntry.hdrTextLen = sizeof(cbBuffer);
	if (EC_OKAY == DEX_ReadGeoDBHdrEntry (hdrEntry)) {
	// Größe festellen und Text ausgeben
		Justify (hDC, hTargetDC, cbBuffer, NULL, (RECT *)&rc, ATLeft, false);
		Justify (hDC, hTargetDC, cbBuffer, NULL, (RECT *)&rc, ATLeft, true);
		SelectObject (hDC, hOldFont);
		fReturn = true;
	} 
	else {
	// dann alle Datenquellen durchgehen
	CRing r (*m_pGeoDBs);

		for (r.First(); r.Valid(); r.Next()) {
		// die erste GeoDB gewinnt
		GeoDBLock l(r);

			TX_ASSERT(NULL != (GeoDB *)l);
			if (l -> isOpened()) { 
				if (EC_OKAY == DEX_ReadHeaderEntry (l -> DBDesc(), hdrEntry)) {
				// Größe festellen und Text ausgeben
					Justify (hDC, hTargetDC, cbBuffer, NULL, (RECT *)&rc, ATLeft, false);
					Justify (hDC, hTargetDC, cbBuffer, NULL, (RECT *)&rc, ATLeft, true);
					fReturn = true;
					break;
				}
			}
		}
	}

// Font wieder zurückstellen
	SelectObject (hDC, hOldFont);
	SetBkMode(hDC, iBkMode);
	return fReturn;
}

///////////////////////////////////////////////////////////////////////////////
// Verwaltung der geladenen GeoDB-Bereiche
bool DatenBasisObjekt::IsLoadedRect (ObjContainer &rOC)
{
	if (NULL == m_pLoadedOC) return false;

// prüfen, ob dieses Rechteck bereits abgedeckt ist
	for (CLoadedRects::iterator it = m_pLoadedOC->begin(); 
		 it != m_pLoadedOC->end(); ++it)
	{
		if (rOC <= *it)	{	// neuer OC ist bereits enthalten
//			TX_TRACE("Found OC\r\n");
			return true;
		}
	}
	return false;
}

bool DatenBasisObjekt::AddLoadedRect (ObjContainer &rOC)
{
	if (NULL == m_pLoadedOC) {
		TX_TRY(m_pLoadedOC = new CLoadedRects());
		if (NULL == m_pLoadedOC) return false;
	}

	if (!IsLoadedRect(rOC)) {
	// evtl. Teilflächen aus Liste entfernen
		for (CLoadedRects::iterator it = m_pLoadedOC->begin(); 
			 it != m_pLoadedOC->end(); /**/)
		{
			if (*it <= rOC) {		// neuer OC überlagert bereits enthaltenen OC
			CLoadedRects::iterator it_tmp = it++;

//				TX_TRACE("Removing overlapped OC ...\r\n");
				m_pLoadedOC->erase (it_tmp);
			} else
				++it;
		}

	// jetzt zur Liste hinzufügen
		m_pLoadedOC -> insert (m_pLoadedOC -> begin(), rOC);
		
//		TX_TRACE1("Added OC - new count: %ld\r\n", m_pLoadedOC->size());
	}
	return true;
}

void DatenBasisObjekt::ResetLoadedRects (void)
{
	if (NULL != m_pLoadedOC) {
//		TX_TRACE("Resetting OC's ...\r\n");
		m_pLoadedOC -> clear();
	}
}

///////////////////////////////////////////////////////////////////////////////
// Testen, ob ein Objekt zur aktuellen Visualisierung gehört 
static bool FMatchGeoTyp (VisType iVTyp, ObjTyp iDefVTyp) 
{
	if (iDefVTyp == OT_KO) return true;		// bei KO alles malen

	switch (iVTyp) {
	case VT_Punkt:
		return iDefVTyp == OT_PUNKT;

	case VT_Linie:
		return iDefVTyp == OT_KANTE;

	case VT_Flaeche:
		return iDefVTyp == OT_FLAECHE || iDefVTyp == OT_KREIS;

	case VT_Text:
		return iDefVTyp == OT_TEXT || iDefVTyp == OT_LABEL;

	case VT_Default:
		break;
	}

	return true;
}

static bool FMatchGeoTyp (VisType iVTyp, int iOTyp) 
{
	if (iOTyp & OTKO) 
		return true;		// bei KO alles malen

	switch (iVTyp) {
	case VT_Punkt:
		return (iOTyp & OTPunkt) ? true : false;

	case VT_Linie:
		return (iOTyp & OTLinie) ? true : false;

	case VT_Flaeche:
		return (iOTyp & OTFlaeche) ? true : false;

	case VT_Text:
		return (iOTyp & OTText) ? true : false;

	case VT_Default:
		break;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Maßstabsbereich testen (nur, wenn Bereich gegeben ist
namespace {
inline 
bool FMatchScales (long lActScale, long lUpperScale, long lLowerScale)
{
	if (0 != lUpperScale && lActScale < lUpperScale)
		return false;

	if (0 != lLowerScale && lActScale > lLowerScale)
		return false;

	return true;
}

}

///////////////////////////////////////////////////////////////////////////////
// Alle Objekte eines Id's einlesen und zeichnen 

ErrCode DatenBasisObjekt::GetGIAll (CIdRefLock &lP, bool fTest, DWORD, bool &rfForceDrawCallUp) 
{
ErrInstall EI_Noon (EC_NOON);
// ErrInstall EI_NoEOK (WC_NOEOK);
ErrCode EC = EC_OKAY;
CIdRef *pP = (CIdRef *)lP;
CIdentifikator *pId = &pP -> rCId();

	if (pId == NULL) return EC_OKAY;		// Ident nicht gefunden

long lIdent = pId -> Id();
bool fIdentIsNative = (HACTPROJECT != pId -> GetObjectsProject()) ? true : false;
//GeoDB &rDB = DB(lIdent);

// Abfragen, ob eine Erweiterung etwas mit diesem Ident zu tun haben will
DRAWIDENTEX DI;

	INITSTRUCT (DI, DRAWIDENTEX);
	DI.m_lIdent = lIdent;
	DEXN_DrawIdentifikatorEx (DI);
	pId -> DType() = DI.m_lResult & DT_DrawingMask;
//	pId -> DType() = DEXN_DrawIdentifikator (lIdent) & DT_DrawingMask;

// Alle Objekte mit diesem Id holen und zeichnen
short iOTypes = 0;		// ObjektTypen dieses Idents

	if (!pId -> InitOTypesEx (iOTypes))	// liest alle Objekte aus der GeoDB
		return WC_NOTFOUND;

// wenn Komplexobjekte da sind, dann alle erlauben
short ivOTypes = iOTypes;	// 'virtuelle' OTypen

	if (iOTypes & TPKO) {
		ivOTypes |= TPAll;
		pId -> SetHasKO();
	} else
		pId -> SetHasKO (false);

// evtl. nicht vorhandene Objekttypen rauswerfen
	pId -> SetOTypes (iOTypes);
	pId -> EnablePainting (pId -> toPaint() & ivOTypes);	// Typen auf Realitäten einschränken
	pId -> SetSpecial (pId -> GetSpecial() & ivOTypes);		// auch nicht visualisierte Typen einschränken

ExtShapeObjectDCreator DOC (Shapes());
ExtShapeObject *pDBO;
CONrTable tabONr (Shapes().ObjNumTree());
Rectangle CRc = GetCanvas() -> CanvasRect();
ObjContainer OC;

	OC = CRc;

bool iAllLoaded = pId -> AreAllLoaded();	// TeilFlag merken
short fFlags = GenerateLegendOnly ? DF_Analyze : 0;
CIdentObjectsLock Objs(*pId);
long lObjNummer;

	if (!Objs || 0 == Objs -> size())
		return WC_NOTFOUND;
	pId -> AllLoaded();						// TeilFlag rücksetzen

#if defined(_USE_FLICKERFREE_DRAWING)
BOOL fFirstObj = (g_dwDrawingMode & DRAWMODE_FirstObjectDraws) ? TRUE : FALSE;		// wenigstens bei jedem ersten Objekt einer Objektmenge zeichnen
#endif // _USE_FLICKERFREE_DRAWING

	for (CIdentObjects::iterator it = Objs -> begin(); it != Objs -> end(); ++it) 
	{
	VisInfo *pVI = NULL;

	// nach Einlesen einer vorgebbaren Menge von Objekten Baum optimieren
		lObjNummer = *it;
		if (NULL == lObjNummer)
			continue;		/// ???

		DEXD_ObjectToDraw (lObjNummer);

	// Sicherstellen, daß dieses Objekt geladen ist (in TRiASDB)
	VisType rgVTyp = pP -> FVisTyp();
	HRESULT hr = pId -> EnsureLoaded (lObjNummer, VTypToBits (rgVTyp), pId -> FGetGeomName(rgVTyp), &OC);

		if (S_OK != hr && S_FALSE != hr) {
			if (TRIASDB_S_OBJECTDOESNOTFIT == hr) {
			// Objekt nicht im Bereich oder nicht passender Geometrietyp
				EC = WC_NOFIT;
				pId -> NotAllLoaded();		// TeilFlag setzen
				continue;
			} else {
				if (!iAllLoaded) 
					pId -> NotAllLoaded();

				TX_ASSERT(SUCCEEDED(hr));	// irgend etwas ist faul
				EC = EC_OKAY;				// FehlerCode rücksetzen
				continue;					// trotzdem weitermachen
			}
		}

	// wenn gefordert, testen, ob Objekt schon geladen ist
		if ((fTest || GetLoadMode()) && tabONr.Find (&lObjNummer)) {
		// Objekt ist bereits geladen, nur zeichnen
		{
		ExtShapeObjectONrLock LockObj (tabONr);

			if (!LockObj) continue;

		ExtShapeObject *pObj = (ExtShapeObject *)LockObj;
		
			if (!FMatchGeoTyp (rgVTyp, pObj -> isTyp())) 
				continue;	// nicht benötigter ObjektTyp
			if (fIdentIsNative && (*pObj) -> Id() != lIdent)
				continue;	// Objekt ist temporär umklassifiziert

			pObj -> SetCanvas (GetCanvas());	// Fenster auf dem gezeichnet werden soll
			if (GenerateLegendOnly && pObj -> isTyp() != OT_TEXT && pObj -> isTyp() != OT_LABEL) {
				pVI = pObj -> SetAttributes (this, pId, tabONr, VT_Default, fFlags);
				if (pVI && pVI != VI_NotChanged) {
					pVI = pId -> ChangeVisInfo (pVI, rgVTyp);
					DELETE_OBJ (pVI);
				}
			} else if ((pVI = pObj -> SetAttributes (this, pId, tabONr, VT_Default, fFlags)) != NULL) {
			// Typgerecht zeichnen bzw. Textgröße messen für Legende
				if (pVI == VI_OtherType) 
					pObj -> TypeDependendDraw (pId, tabONr, DotsPerMM());
				else {
					GetCanvas() -> DrawEx (pObj, reinterpret_cast<DWORD>(this));
					if (pVI != VI_NotChanged) {
						pVI = pId -> ChangeVisInfo (pVI, rgVTyp);
						DELETE_OBJ (pVI);
					}
				}
#if defined(_USE_FLICKERFREE_DRAWING)
			// evtl. derzeitigen Stand neu zeichnen
				rfForceDrawCallUp = !canvas -> DrawCallUp (this, fFirstObj ? DRAWCALLUPMODE_Force : DRAWCALLUPMODE_Normal);
				fFirstObj = FALSE;
#endif // _USE_FLICKERFREE_DRAWING
			}

		} // unlock ExtShapeObject

		// sonst noch was zu tun ?
			if (GCancelFlag == GCFNormal) {
#if defined(_USE_FLICKERFREE_DRAWING)
				if (DoIdleLoop (rfForceDrawCallUp))
#endif // _DEBUG
					App::Exec (ExecWhileEvent);
			}

			if (GCancelFlag != GCFNormal || GetAsyncKeyState (VK_ESCAPE)) {	// abbrechen
				EC = WC_RETURN;
				if (!iAllLoaded) pId -> NotAllLoaded();
				break;
			}
			continue;	// nächstes Objekt
		}

		if (GetLoadMode()) continue;	// NICHTs laden

	// ansonsten Objektgeometrie lesen, _vorab_ jedoch Objekttyp testen
	int iOTyp = TPUnknown;

		if (FAILED(DB(GetObjectDBHandle(lObjNummer)).GetObjectType (lObjNummer, &iOTyp))) {
			if (!iAllLoaded) 
				pId -> NotAllLoaded();
			continue;			// trotzdem weitermachen
		}

		if (!FMatchGeoTyp (rgVTyp, iOTyp)) {
			pId -> NotAllLoaded();	// TeilFlag setzen
			continue;				// nicht benötigter ObjektTyp
		}

		hr = GetGI (lObjNummer, pId -> FGetGeomName(rgVTyp), DOC, &pDBO, NULL /*&OC*/, pId -> Id());
		if (S_OK != hr) {
			if (S_FALSE == hr || TRIASDB_S_OBJECTDOESNOTFIT == hr) {
			// Objekt nicht im Bereich oder unbekannter Geometrietyp
				EC = WC_NOFIT;
				pId -> NotAllLoaded();	// TeilFlag setzen
				continue;
			} else if (TRIASDB_E_BADOBJECTHANDLE == hr) {
				EC = EC_NOON;
				continue;				// gelöschtes Objekt
			} else {
				if (!iAllLoaded) 
					pId -> NotAllLoaded();

				TX_ASSERT(SUCCEEDED(hr));	// irgend etwas ist faul
				EC = EC_OKAY;				// FehlerCode rücksetzen
				continue;					// trotzdem weitermachen
			}
		} else {
		ObjTyp rgOTyp = pDBO -> isTyp();

			Shapes().TimedInsert(DOC, rgOTyp);		// in Baum einfügen, evtl. optimieren
//			Idents().IncrementObjectCount (DB(), lIdent, rgOTyp);

// jetzt _vor_ GetGI
//			if (!FMatchGeoTyp (pP -> FVisTyp(), rgOTyp)) 
//				continue;

		// Zeichenattribute dieses GeoObjektes setzen
			pDBO -> SetCanvas (GetCanvas());	// Fenster auf dem gezeichnet werden soll
			if (GenerateLegendOnly && rgOTyp != OT_TEXT && rgOTyp != OT_LABEL) {
				pVI = pDBO -> SetAttributes (this, pId, tabONr, VT_Default, fFlags);
				if (pVI && pVI != VI_NotChanged) {
					pVI = pId -> ChangeVisInfo (pVI, rgVTyp);
					DELETE_OBJ (pVI);
				}
			} else if ((pVI = pDBO -> SetAttributes (this, pId, tabONr, VT_Default, fFlags)) != NULL) {
			// Typgerecht zeichnen
				if (pVI == VI_OtherType)
					pDBO -> TypeDependendDraw (pId, tabONr, DotsPerMM());
				else {
					GetCanvas() -> DrawEx (pDBO, reinterpret_cast<DWORD>(this));
					if (pVI != VI_NotChanged) {
						pVI = pId -> ChangeVisInfo (pVI, rgVTyp);
						DELETE_OBJ (pVI);
					}
				}
#if defined(_USE_FLICKERFREE_DRAWING)
			// evtl. derzeitigen Stand neu zeichnen
				rfForceDrawCallUp = !canvas -> DrawCallUp (this, fFirstObj ? DRAWCALLUPMODE_Force : DRAWCALLUPMODE_Normal);
				fFirstObj = FALSE;
#endif // _USE_FLICKERFREE_DRAWING
			} 

		// sonst noch was zu tun ?
			if (GCancelFlag == GCFNormal) {
#if defined(_USE_FLICKERFREE_DRAWING)
				if (DoIdleLoop (rfForceDrawCallUp))
#endif // _DEBUG
					App::Exec (ExecWhileEvent);
			}
			if (GCancelFlag != GCFNormal || GetAsyncKeyState (VK_ESCAPE)) {
				pId -> NotAllLoaded();
				EC = WC_RETURN;
				break;
			}
		}
	}
	if (EC == WC_NOFIT) EC = EC_OKAY;
	if (GetLoadMode() && !iAllLoaded) pId -> NotAllLoaded();

	return EC;
}

///////////////////////////////////////////////////////////////////////////////
// Objekte eines Idents zeichnen
ErrCode DatenBasisObjekt::DrawObjectsIteratingIdent (
	CIdRef *pP, bool fGenerateLegendOnly, bool &rfForceDrawCallUp)
{
CIdentTable tabObj (Shapes().ObjIdTree());
CONrTable tabONr (Shapes().ObjNumTree());
CIdentifikator &rId = pP -> rCId();
long lIdent = rId.Id();
ErrCode RC = EC_OKAY;
short fFlags = fGenerateLegendOnly ? DF_Analyze : 0;

#if defined(_USE_FLICKERFREE_DRAWING)
// wenigstens bei jedem ersten Objekt einer Objektmenge zeichnen
bool fFirstObj = (g_dwDrawingMode & DRAWMODE_FirstObjectDraws) ? true : false;
#endif // _USE_FLICKERFREE_DRAWING

	for (tabObj.FindFirst(&lIdent); tabObj.Valid(); tabObj.FindNext(&lIdent)) {
	// für alle Objekte mit diesem Identifikator
	ExtShapeObjectIdentLock LockObj(tabObj);

		if (!LockObj) continue;

	ExtShapeObject *pObj = (ExtShapeObject *)LockObj;
	VisInfo *pVI;
	
		DEXD_ObjectToDraw (pObj -> ObjNr());
		if (!FMatchGeoTyp (pP -> FVisTyp(), pObj -> isTyp()))
			continue;

		pObj -> SetCanvas (GetCanvas());	// Fenster auf dem gezeichnet werden soll
		if (fGenerateLegendOnly && pObj -> isTyp() != OT_TEXT && pObj -> isTyp() != OT_LABEL) {
			pVI = pObj -> SetAttributes (this, &rId, tabONr, VT_Default, fFlags);
			if (pVI && pVI != VI_NotChanged) {
				pVI = rId.ChangeVisInfo (pVI, pP -> FVisTyp());
				DELETE_OBJ (pVI);
			}
		} else if ((pVI = pObj -> SetAttributes (this, &rId, tabONr, VT_Default, fFlags)) != NULL) {
		// Typgerecht zeichnen
			if (pVI == VI_OtherType) 
				pObj -> TypeDependendDraw (&rId, tabONr, DotsPerMM());
			else {
				GetCanvas() -> DrawEx (pObj, reinterpret_cast<DWORD>(this));
				if (pVI != VI_NotChanged) {
					pVI = rId.ChangeVisInfo (pVI, pP -> FVisTyp());
					DELETE_OBJ (pVI);
				}
			}
#if defined(_USE_FLICKERFREE_DRAWING)
		// evtl. derzeitigen Stand neu zeichnen
			rfForceDrawCallUp = !canvas -> DrawCallUp (this, fFirstObj ? DRAWCALLUPMODE_Force : DRAWCALLUPMODE_Normal);
			fFirstObj = false;
#endif // _USE_FLICKERFREE_DRAWING
		}

	// sonst noch was zu tun ?
		if (GCancelFlag == GCFNormal) {
#if defined(_USE_FLICKERFREE_DRAWING)
			if (DoIdleLoop (rfForceDrawCallUp))
#endif // _DEBUG
				App::Exec(ExecWhileEvent);
		}

		if (GCancelFlag != GCFNormal || GetAsyncKeyState (VK_ESCAPE)) {	
		// abbrechen
			RC = WC_RETURN;
			break;
		}
	}
	return RC;
}

///////////////////////////////////////////////////////////////////////////////
// Objekte zeichen, aber Objektweise durchgehen
ErrCode DatenBasisObjekt::DrawObjectsIteratingObjects (
	CIdRef *pP, bool fGenerateLegendOnly, bool &rfForceDrawCallUp)
{
CONrTable tabONr (Shapes().ObjNumTree());
CIdentifikator &rId = pP -> rCId();
ErrCode RC = EC_OKAY;
CIdentObjectsLock Objs(rId);
short fFlags = fGenerateLegendOnly ? DF_Analyze : 0;

	if (!Objs || 0 == Objs -> size())
		return EC_OKAY;

#if defined(_USE_FLICKERFREE_DRAWING)
	// wenigstens bei jedem ersten Objekt einer Objektmenge zeichnen
	bool fFirstObj = (g_dwDrawingMode & DRAWMODE_FirstObjectDraws) ? true : false;
#endif // _USE_FLICKERFREE_DRAWING

	for (CIdentObjects::iterator it = Objs -> begin(); it != Objs -> end(); ++it) {
	long lONr = *it;

		if (!tabONr.Find (&lONr)) 
			continue;

	ExtShapeObjectONrLock LockObj (tabONr);

		if (!LockObj) continue;

	ExtShapeObject *pObj = (ExtShapeObject *)LockObj;
	VisInfo *pVI;
	
		DEXD_ObjectToDraw (pObj -> ObjNr());
		if (!FMatchGeoTyp (pP -> FVisTyp(), pObj -> isTyp()))
			continue;

		pObj -> SetCanvas (GetCanvas());	// Fenster auf dem gezeichnet werden soll
		if (fGenerateLegendOnly && pObj -> isTyp() != OT_TEXT && pObj -> isTyp() != OT_LABEL) {
			pVI = pObj -> SetAttributes (this, &rId, tabONr, VT_Default, fFlags);
			if (pVI && pVI != VI_NotChanged) {
				pVI = rId.ChangeVisInfo (pVI, pP -> FVisTyp());
				DELETE_OBJ (pVI);
			}
		} else if ((pVI = pObj -> SetAttributes (this, &rId, tabONr, VT_Default, fFlags)) != NULL) {
		// Typgerecht zeichnen
			if (pVI == VI_OtherType) 
				pObj -> TypeDependendDraw (&rId, tabONr, DotsPerMM());
			else {
				GetCanvas() -> DrawEx (pObj, reinterpret_cast<DWORD>(this));
				if (pVI != VI_NotChanged) {
					pVI = rId.ChangeVisInfo (pVI, pP -> FVisTyp());
					DELETE_OBJ (pVI);
				}
			}
#if defined(_USE_FLICKERFREE_DRAWING)
		// evtl. derzeitigen Stand neu zeichnen
			rfForceDrawCallUp = !canvas -> DrawCallUp (this, fFirstObj ? DRAWCALLUPMODE_Force : DRAWCALLUPMODE_Normal);
			fFirstObj = false;
#endif // _USE_FLICKERFREE_DRAWING
		}

	// sonst noch was zu tun ?
		if (GCancelFlag == GCFNormal) {
#if defined(_USE_FLICKERFREE_DRAWING)
			if (DoIdleLoop (rfForceDrawCallUp))
#endif // _DEBUG
				App::Exec(ExecWhileEvent);
		}

		if (GCancelFlag != GCFNormal || GetAsyncKeyState (VK_ESCAPE)) {	
		// abbrechen
			RC = WC_RETURN;
			break;
		}
	}
	return RC;
}

///////////////////////////////////////////////////////////////////////////////
// Alle weiteren Male zeichnen 
ErrCode DatenBasisObjekt::NextDraw (DWORD dwData) 
{
CTable tabP(Idents().PrioTree());
CTable tabI(Idents().IdentTree());
bool hasChanged = false;
CIdentTable tabObj (Shapes().ObjIdTree());
CONrTable tabONr (Shapes().ObjNumTree());
ErrCode RC = WC_RETURN;
ErrCode MasstabRC = EC_OKAY;
short fFlags = GenerateLegendOnly ? DF_Analyze : 0;

// Alle Idents als nicht gezeichnet markieren, MetaDC setzen
HDC hDC = Handle (API_DRAWOBJECT_HDC);
HDC hTargetDC = Handle (API_TARGET_HDC);
#if !defined(WIN16)
bool fMetaDC = (::GetObjectType (hDC) == OBJ_ENHMETADC) ? true : false;
#else
bool fMetaDC = (::GetDeviceCaps (hDC, TECHNOLOGY) == DT_METAFILE) ? true : false;
#endif

	for (tabI.First(); tabI.Valid(); tabI.Next()) {
	CIdentifikatorLock l(tabI);
	
		if (l) {
			l -> SetObjectDrawn (0);
			l -> SetMetaDC (fMetaDC);
		}
	}

// LookupWindows an Datenquellen zurücksetzen
	ForceReLoad(RELOADDATABASE_ResetLookupWindow);

// Objekte laden und zeichnen 
bool fForceDrawCallUp = TRUE;	// wenigstens einmal den (leeren) doublebuffer kopieren
bool fDrawn = false;

	{
	CDrawingStatus Status (Idents().PrioTree().Count(), (!GenerateLegendOnly && PrintEFlag) ? true : false);
	double dScale = 1.0;

#if defined(_FORCE_LEGACY_CODE)
		if (GetGeoDBVersion() < VERSION05000004)
			dScale = double(1.0 / M());
		else
#endif // defined(_FORCE_LEGACY_CODE)
			dScale = double(DotsPerMM().Width()) / (100.0*M()) ;

	// es werden nur Idents angefaßt, die gezeichnet werden sollen
	long lLowerScale = 0;
	long lUpperScale = 0;

		for (tabP.First(); tabP.Valid(); tabP.Next()) {
		// wenn wenigstens eine Objektklasse gezeichnet werden soll, dann Flag setzen
		// damit nicht das 'schon gezeichnet Rechteck' gespeichert wird.
			fDrawn = true;

		// für alle Identifikatoren
		CIdRefLock LockP(tabP);

			if (!LockP) continue;

		CIdRef *pP = (CIdRef *)LockP;
		CIdentifikator &rId = pP -> rCId();
		long lIdent = rId.Id();	// lfder Identifikator

		// Status weitersetzen
			Status.StepIt();

		// Maßstabsbereich testen (aktuelle Ansicht)
			RetrieveIdentScaleData (NULL, lIdent, pP -> FVisTyp(), &lUpperScale, &lLowerScale);
			if (!FMatchScales (GetActScale(), lUpperScale, lLowerScale)) {
				MasstabRC = WC_RETURN;		// Bereich nicht als vollständig gezeichnet markieren!
				continue;
			}

		// wenn der GeometrieFeldName seit dem letzten mal geändert wurde, dann alle Objekte neu laden
			if (rId.loaded() && rId.GetGeometryChanged (pP -> FVisTyp())) {
			// aus Speicher löschen
			short fChanged = VTypToBits(pP -> FVisTyp());

				if (DeleteAllObjs (&rId, fChanged, tabObj, tabONr)) {
					DEXD_IdentWasLoaded (lIdent);
					if (!(~fChanged & rId.toPaint()))
						rId.UnLoad();		// keine Objekte dieses Idents mehr im Speicher
					else {
						rId.Load();			// einzelne Objekttypen gibt es schon noch
						rId.NotAllLoaded();
						rId.RemoveGeometryChanged(fChanged);
					}
				}
			}

		// Anzahl der zu zeichnenden Layer berechnen
		int iLayers = pP -> GetLayerCount (dScale);
		bool fBreak = false;

			TX_ASSERT(iLayers >= 1);
			for (int iLayer = 0; iLayer < iLayers; iLayer++) {
			// jetzt soll wirklich gezeichnet werden
				SetActLayer(iLayer);

				rId.AddObjectDrawn (VTypToBits (pP -> FVisTyp()));	// dieser Ident wurde behandelt
				DEXD_IdentToHandle (lIdent);
				if (rId.toPaint()) {		// Id soll gezeichnet werden
					DEXD_IdentToDraw (lIdent);
					if (GetLoadMode() || rId.loaded()) {
					// Objekte bereits (teilweise) geladen
						
						if (!rId.AreAllLoaded()) {
						// nicht alle Objekte dieses Id's sind geladen
							DEXD_IdentIsLoadedPart (lIdent);

							if ((RC = GetGIAll (LockP, true, dwData, fForceDrawCallUp)) == EC_OKAY) {
								if (GetLoadMode())	 	// evtl. was neues dazugeladen
									rId.Load();			// Flag setzen: alle geladen
							} 
							else if (RC == WC_RETURN) {
							// abgebrochen: alles bisherige wieder löschen
								rId.Load();			// Flag's setzen
								rId.NotAllLoaded();
								
								hasChanged = true;
								fBreak = true;
								break;		// abbrechen
							}
							else if (RC != WC_NOTFOUND) {
							// Fehler
								fBreak = true;
								break;
							}
							hasChanged = true;
						} else {
						// Alle Objekte sind geladen
							DEXD_IdentIsLoadedFull (lIdent);
							RC = EC_OKAY;

							if (HACTPROJECT != rId.GetObjectsProject()) 
							// normale Objektklasse
								RC = DrawObjectsIteratingIdent (pP, GenerateLegendOnly, fForceDrawCallUp);
							else 
							// Zuordnungsobjektklasse, die Objekte müssen direkt durchgegangen werden
								RC = DrawObjectsIteratingObjects (pP, GenerateLegendOnly, fForceDrawCallUp);

							if (EC_OKAY != RC)
								fBreak = true;
						}
					} else {
					// erst laden, dann zeichnen
					// trotzdem testen, ob die Objekte schon drin sind
						DEXD_IdentIsNotLoaded (lIdent);
						if ((RC = GetGIAll (LockP, true, dwData, fForceDrawCallUp)) == EC_OKAY) {
							rId.Load();		// Flag setzen
						} else if (RC == WC_RETURN) {
							rId.Load();		// Flag's setzen
							rId.NotAllLoaded();
							
							hasChanged = true;
							fBreak = true;
							break;			// abbrechen
						} else if (RC != WC_NOTFOUND) {
						// Fehler
							fBreak = true;
							break;			// abbrechen
						}
						hasChanged = true;
					}
				} 
			}		// nächster Layer

		// auf nächsten Ident vorbereiten
			rId.ResetResources();	// alle Ressourcen freigeben

		// wenn abgebrochen werden soll, dann dieses tun
			if (fBreak)
				break;	

			if (GCancelFlag == GCFNormal) {
#if defined(_USE_FLICKERFREE_DRAWING)
				if (DoIdleLoop (fForceDrawCallUp))
#endif // _DEBUG
					App::Exec(ExecWhileEvent);	// sonst noch was zu tun ?
			}

			if (GCancelFlag != GCFNormal || GetAsyncKeyState (VK_ESCAPE)) {
				RC = WC_RETURN;
				break;		// abbrechen
			}
		}
	}	// CDrawingStatus geht out of scope

// alle nicht angefaßten Idents prüfen, ob was rausgeworfen werden muß
	for (tabI.First(); tabI.Valid(); tabI.Next()) {
	CIdentifikatorLock l(tabI);
	long lIdent = l -> Id();
	short fDrawn = l -> toPaint();	// GetObjectDrawn();
	
	// Id soll nicht gezeichnet werden
#if defined(_DEBUG)
		if (~fDrawn & l -> GetOTypes())
			DEXD_IdentNotToDraw (lIdent);
#endif // _DEBUG
		if (l -> loaded()) {
		CIdentifikator *pId = (CIdentifikator *)l;

		// aus Speicher löschen, nicht zeichnen
			if (DeleteAllObjs (pId, ~fDrawn, tabObj, tabONr)) {
				DEXD_IdentWasLoaded (lIdent);
				hasChanged = true;
				if (!fDrawn)
					l -> UnLoad();		// keine Objekte dieses Idents mehr im Speicher
				else {
					l -> Load();		// einzelne Objekttypen gibt es schon noch
					l -> NotAllLoaded();
				}
			}
		} 
#if defined(_DEBUG)
		else {
			DEXD_IdentWasNotLoaded (lIdent);	// do nothing else
		}
#endif // _DEBUG

		if (GCancelFlag == GCFNormal && fDrawn) {
#if defined(_USE_FLICKERFREE_DRAWING)
			if (DoIdleLoop (fForceDrawCallUp))
#endif // _DEBUG
				App::Exec(ExecWhileEvent);	// sonst noch was zu tun ?
		}

		if (GCancelFlag != GCFNormal || GetAsyncKeyState (VK_ESCAPE)) {
			RC = WC_RETURN;
			break;		// abbrechen
		}
	}

	if (hasChanged && !(GCancelFlag & GCFAppClosed)) {		// wenn der Baum verändert wurde
		Shapes().ObjIdTree().Optimize();
		Shapes().ObjNumTree().Optimize();
		DEXD_ObjectTreeOptimized (0L);
	}

	if ((EC_OKAY == RC && WC_RETURN == MasstabRC) || !fDrawn)
		RC = WC_RETURN;		// Masstabs-Besonderheiten beachten, bzw, nichts zu zeichnen

#if defined(_USE_FLICKERFREE_DRAWING)
	if (fForceDrawCallUp)
		canvas -> DrawCallUp (this, (EC_OKAY == RC) ? DRAWCALLUPMODE_Finished : DRAWCALLUPMODE_Force);		// den Rest auf den Bildschirm bringen
#endif // _USE_FLICKERFREE_DRAWING

	return RC;
}

bool DatenBasisObjekt::DeleteTempIdents (void)
{
CTable tabP(Idents().PrioTree());
CIdentTable tabObj (Shapes().ObjIdTree());
CONrTable tabONr (Shapes().ObjNumTree());

	for (tabP.First(); tabP.Valid(); ) {
	long lIdent = -1L;
	bool fToDelete = false;

		{
		CIdRefLock l (tabP);
		CIdRef *pP = (CIdRef *)l;
		
			if (pP && pP -> rCId().isTemp()) {
				lIdent = pP -> rCId().Id();	// lfder Identifikator
				fToDelete = true;
			}

		// alle Objekte freigeben
			if (fToDelete && -1 != lIdent) 
				DeleteAllObjs (&pP -> rCId(), TPAll, tabObj, tabONr);
		}

		if (fToDelete && -1 != lIdent) 
			tabP.Delete();
		else
			tabP.Next();
	}

return true;
}

bool DatenBasisObjekt::DeleteAllObjs (
	CIdentifikator *pId, short fToDelete, CIdentTable &tabObj, CONrTable &tabONr)
{
long lIdent = pId -> Id();
bool hasChanged = false;		

	for (tabObj.FindFirst (&lIdent); tabObj.Valid(); ) {
	// für alle Objekte mit diesem Identifikator
	long lONr = -1L;

		{	// Objektnummer holen
		ExtShapeObjectIdentLock l(tabObj);

			if (!l) break;	// Fehler
			if (l -> Id() != lIdent) 
				break;	// fertig mit diesem ID
//			if (l -> Status() == ExtShapeObject::OS_Temp) {
//				Insist = true;
//				break;
//			}
			if (OTypToBits (l -> isTyp()) & fToDelete)
				lONr = l -> ObjNr();	// Objekt rauslöschen
		}

	// löschen, erst nur Baum, dann Baum mit Objekt
		if (lONr != -1L && tabONr.Find (&lONr)) {
//			if (HACTPROJECT != pId -> GetObjectsProject())
				tabONr.Delete();	// nur wirklich rauswerfen, wenns keine Zuordnungsobjektklasse ist
			tabObj.Delete();
//			pId -> MayUnload(lONr);
			hasChanged = true;
		} else
			tabObj.Next();
	}
	return hasChanged;
}


// DBOContainer setzen (projektionsspezifisch)
void DatenBasisObjekt::SetExtend (Window *pW, ObjContainer &R, Point &AspectR, Rectangle *pRc) 
{
	if (R.isValid()) {
	ObjContainer OC (R.XMin(), R.XMax(), R.YMin(), R.YMax());    // temporäre Kopie

	//	(*_Prj)(&OC.XMin(), &OC.YMin());
	//	(*_Prj)(&OC.XMax(), &OC.YMax());
		_DBOCont = OC;
		Scale (pW, OC, AspectR, pRc);		// Bildausschnitt skalieren
	}
}

PaintFlag DatenBasisObjekt::SetPaintFlag (PaintFlag newFlag) 
{
register PaintFlag oldFlag = _toPaint;

	_toPaint = newFlag;
	return oldFlag;
}

///////////////////////////////////////////////////////////////////////////////
// alle Identifikatoren aus der DB lesen und in IdTree speichern 
extern "C" 
BOOL WINAPI FillOneIdent (long lIdent, BOOL, void *pData)
{
// ID in Tree einspeichern
VisInfo *pVI[4];

	pVI[0] = pVI[1] = pVI[2] = pVI[3] = NULL;

DatenBasisObjekt *pDBO = reinterpret_cast<DatenBasisObjekt *>(pData);

	return pDBO -> Idents().AddIdent (*pDBO, lIdent, pVI, 0, hPalette);
}

ErrCode DatenBasisObjekt::FillIdents (bool fRebuild) 
{
	if (fRebuild) {	
		EveryDelete();		// alles vergessen
		ForceReLoad(RELOADDATABASE_Objects);	// Datenquellen ebenfalls auffordern alle Objektklassen zu vergessen
	}

// wenn Idents gefüllt ist, dann wieder raus
	if (Idents().IdentTree().Count() > 0) 
		return EC_OKAY;

// alle Identifikatoren behandeln
BOOL iResult = EnumIdents (HACTCONNECTION, (ENUMNOKEYLONGPROC)FillOneIdent, this);

// beide Bäume optimieren
	Idents().IdentTree().Optimize();
	Idents().PrioTree().Optimize();
	DEXD_IdentTreeOptimized();

	return iResult ? EC_OKAY : EC_NOMEMORY;
}

HRESULT DatenBasisObjekt::ForceReLoad (RELOADDATABASE rgWhat)
{
	TX_ASSERT(NULL != m_pGeoDBs);

CRing r (*m_pGeoDBs);

	for (r.First(); r.Valid(); r.Next()) {
	GeoDBLock l(r);

		TX_ASSERT(NULL != (GeoDB *)l);
		if (l -> isOpened())
		{ 
			RETURN_FAILED_HRESULT(l -> ForceReLoad (rgWhat));
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// alle Objektklassen einer Datenquelle rauswerfen
HRESULT DatenBasisObjekt::RemoveIdentsFromCache (HPROJECT hPr)
{
CIdentTable tabObj (Shapes().ObjIdTree());
CONrTable tabONr (Shapes().ObjNumTree());
CTable t(Idents().IdentTree());

	for (t.First(); t.Valid(); /**/) {
	bool fToDelete = false;
	INT_PTR lIdent = NULL;

		{
		CIdentifikatorLock l (t);

			if (!l)
				continue;
			lIdent = l -> Id();
			if (hPr == DEX_GetObjectsProject(l -> Id())) {
				DEXN_FeatureSetModified(lIdent);				// Objekteigenschaften ungültig machen
				DeleteAllObjs(l, TPAll, tabObj, tabONr);		// Objekte entfernen
				fToDelete = true;
			}
		}
		_ASSERTE(NULL != lIdent);

		if (fToDelete) 
			Idents().DeleteIdent(lIdent);					// Objektklasse rauswerfen
		else
			t.Next();		// der nächste, bitte
	}
	return S_OK;
}

// Destruktor -----------------------------------------------------------------
DatenBasisObjekt::~DatenBasisObjekt (void) 
{
	ResetBase ();		// ExtShapeObject zurücksetzen

	_SightMenu = NULL;
	DELETE_OBJ (_Idents);
	DELETE_OBJ (_Shapes);

	DELETE_OBJ (m_pGeoDBs);

	DELETE_OBJ (m_pViews);
#if defined(_FORCE_LEGACY_CODE)
	m_pbdDB.EveryDelete();
#endif // defined(_FORCE_LEGACY_CODE)
	
	DELETE_OBJ (m_pBmp15sw);
	DELETE_OBJ (m_pBmp23sw);
	DELETE_OBJ (m_pBmp32sw);
	
	DELETE_OBJ (m_pPunktIDs);
	DeleteClsIdentMap();

	FreeDrawBuffer();

#if !defined(WIN16)
	ResetLoadedRects();
	DELETE_OBJ(m_pLoadedOC);
#endif // WIN16
}

void DatenBasisObjekt::EveryDelete (void) 
{
	Shapes().EveryDelete ();
	Idents().AllDelete ();
	_toPaint = PF_INVALID;
#if defined(_FORCE_LEGACY_CODE)
	m_pbdDB.EveryDelete();
#endif // defined(_FORCE_LEGACY_CODE)
}

void DatenBasisObjekt::InitPbd (char *pDir, bool fFlag)
{
#if defined(_FORCE_LEGACY_CODE)
	PbdDB().InitPBD (DB(), pDir, fFlag);
#endif // defined(_FORCE_LEGACY_CODE)
}

ErrCode DatenBasisObjekt::CloseDB (bool fCommit)
{		
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	// zugehörige PBD schließen
	ErrCode RC;

		if (PbdDB().isOpened()) {
			PbdDB().ReleasePBDTempTree();
			DBASSERT (PbdDB().Close (fCommit));
		}

	// Datenbanken(Connections) schließen
		m_pGeoDBs -> FActivateItem (-1);		// nichts mehr aktiv

	CRing r (*m_pGeoDBs);

		for (r.First(); r.Valid(); /**/) {
			{
			GeoDBLock l(r);

				TX_ASSERT(NULL != (GeoDB *)l);
				CloseConnection (*l, fCommit);
			} // Lock goes out of scope

			if (!r.Delete())
				r.Next();		// for_ever vermeiden
		}
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

		if (S_OK == m_Prj -> Close (fCommit ? VARIANT_TRUE : VARIANT_FALSE))
			m_pGeoDBs -> FActivateItem (-1);		// nichts mehr aktiv
	}
	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// Schließt eine GeoDB
ErrCode DatenBasisObjekt::CloseConnection (GeoDB &rDB, bool fCommit)
{
	if (rDB.isOpened()) {
	bool fDelete = rDB.GetTempMode();
	string str (rDB.GetDBName());
	char cbBuffer[_MAX_PATH];
	ErrCode RC;
		
		rDB.GetTempDBName (cbBuffer);
		DBASSERT (rDB.Close(fCommit));
		DEXN_isClosedProject(str.c_str());

		if (fDelete) DeleteFile (cbBuffer);
	}
	return EC_OKAY;
}

HRESULT DatenBasisObjekt::OpenConnection (GeoDB &rDB, ITRiASConnection *pIConn)
{
	TX_ASSERT(IsTRiASDBBased());

	USES_CONVERSION;
	COM_TRY {
	// Testen ob, wir diese Version überhaupt schon unterstützen
	// RIW-Version testen !
	LONG lVersion;

		THROW_FAILED_HRESULT(m_Prj -> get_Version (&lVersion));
		if (lVersion > LASTDBVERSION) {
			db_error (WC_BADDBVERSION, RC_OpenDB);
			return E_UNEXPECTED;
		}

	// Parameter abfragen und einstellen
	CComBSTR bstrName;

		THROW_FAILED_HRESULT(pIConn -> get_Location (CLEARED(&bstrName)));
		rDB.SetDBName (OLE2A(bstrName));

	CONNECTMODE rgRW = CONNECTMODE_OpenReadWrite;	// R/W

		THROW_FAILED_HRESULT(pIConn -> get_Mode (&rgRW));
		rgRW = CONNECTMODE(rgRW & ~CONNECTMODE_ResolutionFlags);
		rDB.SetROMode (CONNECTMODE_OpenReadWrite == rgRW ? false : true);

	// GeoDB fertig initialisieren
		THROW_FAILED_HRESULT(rDB.AttachConnection (pIConn));

	CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

		THROW_FAILED_HRESULT(pIConn -> get_Status (&rgStatus));
		if (CONNECTSTATUS_Opened == rgStatus) 
		{
			TX_ASSERT(HACTCONNECTION != rDB.DBDesc() && HACTPROJECT != rDB.DBDesc() && (HPROJECT)(-2) != rDB.DBDesc());		// muß jetzt offen sein

			MainInitPbd(rDB);			// interne MerkmalsCodes in PBD nachtragen (für GeoDB's)
			rDB.ReReadHeader();			// DB auffordern, sich neu zu initialisieren
		}

		SetPaintFlag (PF_INVALID);

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// nach Öffnen einer Connection neu initialisieren
HRESULT DatenBasisObjekt::RePrepareDBO (IrisWind *pWindow, Point ptAspect, HPROJECT hPr)
{
	if (NULL == pWindow)				// eigenes Fenster verwenden
		pWindow = GetViewWindow();

	DEX_RemoveAllORWnds();				// Recherchefenster zerlegen

	if (HACTCONNECTION == hPr) {
		m_lObjCnt = -1;						// Objektzähler rücksetzen
		FillIdents (true);					// Idents neu einlesen
		InitClsIdentMap();					// OKSMap neu initialisieren
		ReScale (pWindow);					// Koordinatensystem setzen
		DEXN_ReReadObjectProperties (TRUE);	// ObjectProps neu einlesen
	}
	else {
	// nur eine Datenquelle entfernen
		RemoveIdentsFromCache(hPr);			// Objektklassen und zugehörige Objekte rauswerfen
		InitClsIdentMap();					// OKSMap neu initialisieren
		ReScale (pWindow);					// Koordinatensystem setzen
	}

// DatenBasisObjekt Ausschnitt definieren
	{
	ObjContainer ocT = DBCont(true).InflateCont(10);

		SetExtend (pWindow, ocT, ptAspect);
	}
	return S_OK;
}

HRESULT DatenBasisObjekt::AddConnection (IDispatch *pIConn)
{
int iIndex = -1;

	COM_TRY {
	WTRiASConnection Conn (pIConn);

		iIndex = m_pGeoDBs -> FAddItem();
		if (-1 == iIndex) 
			_com_issue_error(E_OUTOFMEMORY);

	// jezt GeoDB wirklich zuordnen
	GeoDB &rDB = m_pGeoDBs -> DB(iIndex);

		THROW_FAILED_HRESULT(OpenConnection (rDB, Conn));

	} COM_CATCH_OP(
		if (-1 != iIndex)
			m_pGeoDBs -> FDelItem (iIndex);		// wieder herausnehmen
	);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert den Namen des zugehörigen Projektes
string DatenBasisObjekt::GetProjectName (void) 
{
// Project ist gesetzt
	if (IsTRiASDBBased()) {
	CComBSTR bstrName;

		if (SUCCEEDED(m_Prj -> get_Name (CLEARED(&bstrName)))) {
			USES_CONVERSION;
			return string(OLE2A(bstrName));
		}
	}

// ansonsten Namen der ersten geöffneten Connection verwenden
string str (g_cbNil);

	if (m_pGeoDBs -> Count())
		str = DB().GetDBName();
	return str;
}

///////////////////////////////////////////////////////////////////////////////
// Modifikation eines Identifikators in der GeoDB und im Speicher 
bool DatenBasisObjekt::ModIdent (long lONr, long newId, long oldId, short iMode) 
{
	if (DEXN_IdentToModify (lONr))
		return false;		// jemand hat was dagegen

	if (!IsValidIdent(oldId))	// alten Ident besorgen
		oldId = RetrieveIdent (lONr, true);

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	CActDB ActDB (DB());

		if (!(iMode & MODIDENT_TEMP) && modid (DB().DBDesc(), lONr, newId) != EC_OKAY) 
			return false;
	} else
#else
	if (!(iMode & MODIDENT_TEMP)) {
		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		WTRiASObjects Objs;
		WTRiASObject Obj;

			THROW_FAILED_HRESULT(GetObjectsFromMap(newId, Objs));
			THROW_FAILED_HRESULT(GetObjectFromMap(lONr, Obj));
			THROW_FAILED_HRESULT(Objs -> Classify (Obj, CLASSIFYMODE_DatasourceOnly));

		} COM_CATCH_RETURN(false);
	}
#endif // 

// ist das erste Objekt mit diesem Ident
	{
	HPROJECT hPr = GetIdentParentHandle(newId);
	CTable t(Idents().IdentTree());
	short aniMode = 0;

		if (iMode & MODIDENT_TEMP) aniMode |= ANI_Temp;
		if (iMode & MODIDENT_ADDTOVIEW) aniMode |= ANI_AddToView;
		if (t.Find (&newId)) {
			AddNewIdent (newId, hPalette, aniMode, (iMode & MODIDENT_TYP), newId);
		} else {
			AddNewIdent (newId, hPalette, aniMode, (iMode & MODIDENT_TYP), oldId);
		}
		Idents().ModifyIdent (lONr, newId, oldId);
	}

// Identifikator auch im Speicher ändern 
	if (!Shapes().ModIdent (lONr, oldId, newId)) {
	// Objekt laden, da es noch nicht im Speicher ist 
		{
		ExtShapeObjectDCreator DOC (Shapes());
		ExtShapeObject *pDBO;

			if (GetGI (lONr, NULL, DOC, &pDBO) != S_OK) 
				return false;
		}

	// hier wurde das bereits in der GeoDB umklassifizierte Objekt geladen		
//	// jetzt umklassifizieren
//		if (!Shapes().ModIdent (lONr, oldId, newId))
//			return false;		// nun ist aber genug
	}

// war das letzte Objekt mit diesem Ident
	{
	CIdentTable t(Shapes().ObjIdTree());

		if (!t.Find (&oldId)) 
			Idents().DeleteIdent (oldId);
	}

// umklassifizierten Ident als nicht vollständig geladen kennzeichnen
	{
	CTable t(Idents().IdentTree());

		if (t.Find (&oldId)) {
		CIdentifikatorLock lID (t);

			if (lID) lID -> NotAllLoaded();
		}
	}

// Objekt wurde erfolgreich umklassifiziert
	DEXN_IdentModified (lONr);
	return true;
}

// Setzen und Rücksetzen der Zeichenattribute eines Objektes des Baumes -------
VisInfo *DatenBasisObjekt::PresetAttributes (Window *pCanvas, long ONr)
{
CONrTable tabON (Shapes().ObjNumTree());
CTable tabId (Idents().IdentTree());
long Ident = RetrieveIdent (ONr);

	SetCanvas (pCanvas);
	
	if (tabON.Find (&ONr) && tabId.Find (&Ident)) {
	ExtShapeObjectONrLock lON(tabON);
	CIdentifikatorLock lId(tabId);

		if (lON && lId) {
		Window *pOldCanvas = lON -> GetCanvas();

			lON -> SetCanvas (pCanvas);
		
		VisInfo *pVI = lON -> SetAttributes (this, lId, tabON, VT_Default, DF_Blinking);
			
			lON -> SetCanvas (pOldCanvas);
			return pVI;
		}
	}
	
	return NULL;
}

bool DatenBasisObjekt::ResetAttributes (long ONr, VisInfo *pVI)
{
CONrTable tabON (Shapes().ObjNumTree());
CTable tabId (Idents().IdentTree());
long Ident = RetrieveIdent (ONr);

	if (tabON.Find (&ONr) && tabId.Find (&Ident)) {
	ExtShapeObjectONrLock lON(tabON);
	CIdentifikatorLock lId (tabId);

		if (lON && lId) {
			lON -> ResetAttributes ();
			lId -> ResetResources();

			if (pVI && pVI != VI_NotChanged && pVI != VI_OtherType) {
				pVI = lId -> ChangeVisInfo (pVI);
				DELETE_OBJ (pVI);
			}
			return true;
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// von einer Ansicht den vorgegebenen Beszugsmaßstab lesen
double DatenBasisObjekt::GetViewBMasstab (LPCSTR pcView)
{
double dMSt = -1.0;

char cbSight[SIGHTMENUITEM+1];

	if (NULL == pcView) {
		if (!GetActiveSightName (cbSight, SIGHTMENUITEM+1))
			return -1.0;	// Fehler oder keine aktuelle Ansicht
		pcView = cbSight;
	}
	if ('\0' == pcView[0])
		return dMSt;		// temporäre Ansicht

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	// Fehlermeldung unterdrücken und Defaultwerte verwenden
	ErrInstall EI (WC_NOTFOUND);

	// zuerst versuchen, aus der Sicht den aktuellen BMaßstab zu bekommen
		if (DB().GetDBVersion() >= VERSION05000008) {
		// nur ab Version 05.00.08
		long lMCode = HeaderEntry (DB(), IDS_HDRSICHTBMASSTAB).EntryLong(0);

			if (lMCode != 0 && pcView[0] != '\0') {
			char *pMText = NULL;
			CActDB ActDB (DB());		// #ActDB
			Sicht S (DB(), pcView);

				S.GetMiText (lMCode, &pMText);
				if (pMText != NULL) {
					dMSt = (long)atol (pMText);
					if (dMSt == 0.0) dMSt = -1.0;
				}
				DELETE_OBJ (pMText);
			}			
		}
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		// Ansicht besorgen
		WTRiASView View;

			THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));

		// alle Properties der Ansicht abfragen
		WTRiASProperties Props;

			THROW_FAILED_HRESULT(WTRiASPropertyBase(View) -> get_Properties (Props.ppi()));
			dMSt = GetPropertyResID (Props, ResID(IDS_HDRSICHTBMASSTAB), dMSt, LOCALE_ENGLISH);

		} COM_CATCH_RETURN (dMSt);
	}
	return dMSt;
}

///////////////////////////////////////////////////////////////////////////////
// an eine Ansicht den vorgegebenen Beszugsmaßstab schreiben
HRESULT DatenBasisObjekt::SetViewBMasstab (double dMSt, LPCSTR pcView)
{
char cbSight[SIGHTMENUITEM+1];

	if (NULL == pcView) {
		if (!GetActiveSightName (cbSight, SIGHTMENUITEM+1))
			return -1.0;	// Fehler oder keine aktuelle Ansicht
		pcView = cbSight;
	}

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	// Fehlermeldung unterdrücken und Defaultwerte verwenden
	ErrInstall EI (WC_NOTFOUND);

	// zuerst versuchen, aus der Sicht den aktuellen BMaßstab zu bekommen
		if (DB().GetDBVersion() >= VERSION05000008) {
		// nur ab Version 05.00.08
		long lMCode = HeaderEntry (DB(), IDS_HDRSICHTBMASSTAB).EntryLong(0);

			if (0 == lMCode) {
				MainInitPbd (DB(), IDS_HDRSICHTBMASSTAB, true);
				lMCode = HeaderEntry (DB(), IDS_HDRSICHTBMASSTAB).EntryLong (0);
			}

			if (lMCode != 0 && pcView[0] != '\0') {
			CActDB ActDB (DB());		// #ActDB
			Sicht S (DB(), pcView);
			CComVariant v(dMSt);

				USES_CONVERSION;
				TX_VERIFY(SUCCEEDED(v.ChangeType (VT_BSTR)));
			
			ErrCode RC = S.PutMiText (lMCode, OLE2A(V_BSTR(&v)));

				if (EC_OKAY != RC)
					return HRESULT_FROM_ERRCODE(RC);
				return S_OK;
			}			
			return HRESULT_FROM_ERRCODE(EC_ILLPARS);
		}
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		// Ansicht besorgen
		WTRiASView View;

			THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));

		// alle Properties der Ansicht abfragen
		WTRiASProperties Props;

			THROW_FAILED_HRESULT(WTRiASPropertyBase(View) -> get_Properties (Props.ppi()));
			THROW_FAILED_HRESULT(SetPropertyResID (Props, ResID(IDS_HDRSICHTBMASSTAB), dMSt, true, LOCALE_ENGLISH));

		} COM_CATCH;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// an eine Ansicht den vorgegebenen Beszugsmaßstab schreiben
HRESULT DatenBasisObjekt::DelViewBMasstab (LPCSTR pcView)
{
char cbSight[SIGHTMENUITEM+1];

	if (NULL == pcView) {
		if (!GetActiveSightName (cbSight, SIGHTMENUITEM+1))
			return -1.0;	// Fehler oder keine aktuelle Ansicht
		pcView = cbSight;
	}

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	// Fehlermeldung unterdrücken und Defaultwerte verwenden
	ErrInstall EI (WC_NOTFOUND);

	// zuerst versuchen, aus der Sicht den aktuellen BMaßstab zu bekommen
		if (DB().GetDBVersion() >= VERSION05000008) {
		// nur ab Version 05.00.08
		long lMCode = HeaderEntry (DB(), IDS_HDRSICHTBMASSTAB).EntryLong(0);

			if (0 == lMCode) {
				MainInitPbd (DB(), IDS_HDRSICHTBMASSTAB, true);
				lMCode = HeaderEntry (DB(), IDS_HDRSICHTBMASSTAB).EntryLong (0);
			}

			if (lMCode != 0 && pcView[0] != '\0') {
			CActDB ActDB (DB());		// #ActDB
			Sicht S (DB(), pcView);
			ErrCode RC = S.DelMiText (lMCode);

				if (EC_OKAY != RC)
					return HRESULT_FROM_ERRCODE(RC);
				return S_OK;
			}			
			return HRESULT_FROM_ERRCODE(EC_ILLPARS);
		}
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		// Ansicht besorgen
		WTRiASView View;

			THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));

		// alle Properties der Ansicht abfragen
		WTRiASProperties Props;

			THROW_FAILED_HRESULT(WTRiASPropertyBase(View) -> get_Properties (Props.ppi()));
			THROW_FAILED_HRESULT(DelProperty (Props, ResID(IDS_HDRSICHTBMASSTAB)));

		} COM_CATCH;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// DarstellungsMaßstab berechnen
void DatenBasisObjekt::EvalMasstab (Window *pW, double *pMasstab) 
{
//	M() = 1.0;	// für alle Fälle
//
double MSt = GetViewBMasstab();		// von akzueller Ansicht BMasstab lesen

// ansonsten Bezugsmasstab aus DB-Header lesen
	if (-1.0 == MSt)
		MSt = CPrjHeaderEntry (DB(), IDS_MASSTAB).EntryDouble (-1.0);

	if (NULL == pCT()) {
		if (pMasstab) {
			pMasstab[0] = MSt;	// BezugsMaßstab
			pMasstab[1] = MSt;	// DarstellungsMaßstab
		}
		return;
	}

// wenn Rechteck entartet ist, dann nichts ändern
Rectangle rcEA = EA();

	if (rcEA.Right() == rcEA.Left()) return;

Rectangle CRc = pW -> CanvasRect();

	if (CRc.Left() == CRc.Right()) return;		// Icon

// für alle Fälle Maßstabsverhältnis rücksetzen 
	M() = 1.0;

// Koordinaten in DB-Koordinaten umsetzen
Point ptT1 = CRc.UpperLeft();
Point ptT2 = CRc.LowerRight();
Punkt LO = DCtoOC (/*EA()*/ptT1);       // Device --> Objekt
Punkt RU = DCtoOC (/*EA()*/ptT2);

// DatenBasis-Skalierung rausrechnen
#if defined(_KOORD_ISDOUBLE)
DoublePair P1 (LO.GetX(), LO.GetY());
DoublePair P2 (RU.GetX(), LO.GetY());	// über X-Koordinate berechnen
#else
double XLO, XRU, YLO, YRU;

	pCT() -> UnScale (LO, &XLO, &YLO);
	pCT() -> UnScale (RU, &XRU, &YRU);

DoublePair P1 (XLO, YLO);
DoublePair P2 (XRU, YLO);	// über X-Koordinate berechnen
#endif // _KOORD_ISDOUBLE

double dX = 1.0;

	if (pCT() -> hasDistEx()) {
	double dY = 1.0;

		pCT() -> CoordTransDistanceEx (&P1, &P2, dX, dY);
	} else
		dX = pCT() -> CoordTransDistance (&P1, &P2);

double tmpM = ((fabs(dX) * 1000.0 * DotsPerMM().Width()) / ((double)(CRc.Right()-CRc.Left())));

// wenn kein Bezugsmaßstab gegeben ist, dann aktuelle Skalierung gleich 1.0 setzen
// ansonsten gleich dem Verhältnis von aktuellem Maßstab (tmpM) und BezugsMaßstab
	if (-1.0 == MSt || 0.0 == MSt) {
		if (pMasstab) {
			pMasstab[0] = 1.0;	// BezugsMaßstab
			pMasstab[1] = tmpM;	// DarstellungsMaßstab
		}
	} else {
		M() = tmpM / MSt;

		if (pMasstab) {
			pMasstab[0] = MSt;	// BezugsMaßstab
			pMasstab[1] = tmpM;	// DarstellungsMaßstab
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Setzen der sichtbezogen anzuzeigenden Objekteigenschaft
HRESULT DatenBasisObjekt::SetObjPropToShow(LPCSTR pcView, LPCSTR pcObjProp, 
	int iFlags)
{
char cbBuffer[MAXVIEWNAMESIZE+1];
bool fChangeActView = true;

	if (NULL == pcView) {
	// aktuelle Ansicht verwenden
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer)-1))
			return E_UNEXPECTED;		// Fehler oder keine aktuelle Ansicht
		pcView = cbBuffer;
	}
	else {
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer)-1)) 
			return E_UNEXPECTED;		// Fehler oder keine aktuelle Ansicht
		fChangeActView = !strcmp(pcView, cbBuffer);
	}

	TX_ASSERT(IsTRiASDBBased());
	COM_TRY {
	// Ansicht besorgen
	WTRiASView View;

		THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));

	// alle Properties der Ansicht abfragen
	WTRiASProperties Props;

		THROW_FAILED_HRESULT(WTRiASPropertyBase(View) -> get_Properties (Props.ppi()));

	// anzuzeigende Objekteigenschaft setzen
		if (NULL != pcObjProp) {
			THROW_FAILED_HRESULT(SetProperty (Props, g_cbObjPropToShow, CComBSTR(pcObjProp), true));
			if (fChangeActView)
				DEX_SetActObjPropName(pcObjProp);
		} 
		else {
			THROW_FAILED_HRESULT(DelProperty (Props, g_cbObjPropToShow));
			if (fChangeActView)
				DEX_SetActObjPropName(NULL);
		}

	// SortAndHideFlags setzen
		if (iFlags != RODefaultFlags && 0 != iFlags) {
			THROW_FAILED_HRESULT(SetProperty (Props, g_cbHideAndSortFlags, iFlags, true));
			if (fChangeActView)
				g_iHideFlags = iFlags;
		}
		else {
			THROW_FAILED_HRESULT(DelProperty (Props, g_cbHideAndSortFlags));
			if (fChangeActView)
				g_iHideFlags = RODefaultFlags;
		}

	} COM_CATCH;
	return S_OK;
}

HRESULT DatenBasisObjekt::GetObjPropToShow(LPCSTR pcView, LPSTR pObjProp, 
	int iLen, int *piFlags)
{
char cbBuffer[MAXVIEWNAMESIZE+1];

	if (NULL == pcView) {
	// aktuelle Ansicht verwenden
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer)-1))
			return E_UNEXPECTED;		// Fehler oder keine aktuelle Ansicht
		pcView = cbBuffer;
	}

	TX_ASSERT(IsTRiASDBBased());
	COM_TRY {
	// Ansicht besorgen
	WTRiASView View;

		THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));

	// alle Properties der Ansicht abfragen
	WTRiASProperties Props;

		THROW_FAILED_HRESULT(WTRiASPropertyBase(View) -> get_Properties (Props.ppi()));

	// anzuzeigende Objekteigenschaft setzen
		if (NULL != pObjProp) {
			USES_CONVERSION;
			_ASSERTE(iLen > 0);

		CComBSTR bstrObjProp = GetProperty (Props, g_cbObjPropToShow, CComBSTR(g_cbNil));
		unsigned int iToCopy = min((unsigned int)(iLen-1), bstrObjProp.Length());

			strncpy (pObjProp, OLE2A(bstrObjProp), iToCopy);
			pObjProp[iToCopy] = '\0';
		} 

	// SortAndHideFlags setzen
		if (NULL != piFlags) 
			*piFlags = GetProperty (Props, g_cbHideAndSortFlags, RODefaultFlags);

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Abfragen der sichtbezogen anzuzeigenden Objekteigenschaft

// Löschen aller oder aller nicht mehr geladener Identifikatoren --------------
bool DatenBasisObjekt::RemoveTempIdents (void) 
{
CTable tID (Idents().IdentTree());

	for (tID.First(); tID.Valid(); ) {
	bool toDelete = false;
	long lIdent = -1L;

		{
		CIdentifikatorLock lID (tID);

			if (!lID) continue;		// Fehler
			if (lID -> isTemp()) {
				if (!lID -> loaded()) {
					toDelete = true;
					lIdent = lID -> Id();
				} else if (ReloadAllObjects (lIdent) == EC_OKAY) {
					toDelete = true;
					lIdent = lID -> Id();
				} else						
					return false;	// Fehler
			}
		}

	// diesen Satz evtl. löschen
		if (toDelete) { 
			if (!Idents().DeleteIdent (lIdent)) return false; 
		} else { 
			if (!tID.Next()) break; 
		}
	}
	return true;
}

// Alle Objekte mit einem Ident frisch laden ----------------------------------
ErrCode DatenBasisObjekt::ReloadAllObjects (long lIdent)
{
CIdentTable tabObj (Shapes().ObjIdTree());
CONrTable tabONr (Shapes().ObjNumTree());
ExtShapeObjectDCreator DOC (Shapes());
ExtShapeObject *pDBO = NULL;
ErrCode EC = EC_OKAY;

	for (tabObj.FindFirst (&lIdent); tabObj.Valid(); tabObj.FindNext(&lIdent)) 
	{
	// alle Objekte mit diesem Identifikator neu laden
	long lONr = -1L;

		{	// Objektnummer holen
		ExtShapeObjectIdentLock l(tabObj);

			lONr = l -> ObjNr();
		}

	// löschen, erst nur Baum, dann Baum mit Objekt
		if (lONr != -1L && tabONr.Find (&lONr)) {
			tabONr.Delete();
			tabObj.Delete();
		}

	// frisch besorgen
	HRESULT hr = GetGI (lONr, NULL, DOC, &pDBO, NULL, lIdent);

		if (S_OK == hr || TRIASDB_S_OBJECTDOESNOTFIT)
		{ 
		ObjTyp rgOTyp = pDBO -> isTyp();

			Shapes().CondOptimize (Shapes().TimedInsert(DOC, rgOTyp));
//			Idents().IncrementObjectCount (DB(), lIdent, rgOTyp);
		} else {
//			DOC.Revoke();
			return EC;
		}
	}
	return EC_OKAY;
}

// Neu initialisieren der DBO-Klasse ------------------------------------------
bool DatenBasisObjekt::ReScale (Window *pW)
{
	if (NULL != _pCT) {
		if (!_pCT -> Reload (true))
			return true;	// muß nicht neu geladen laden

		if (NULL != _pCT) {
			_pCT -> UnAdvise();
			
			delete _pCT;
			_pCT = NULL;
		}
	}

// neu laden
	TX_ASSERT(NULL == _pCT);

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		TX_TRY(_pCT = new CCoordTransServiceObsolete (pW, DB()));
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_TRY(_pCT = new CCoordTransService());
		if (NULL != _pCT && FAILED(((CCoordTransService *)_pCT) -> InitCTFService (WTRiASPropertyBase(m_Prj))))
			return false;
	}

	if (NULL == _pCT) {
		db_error (EC_NOMEMORY, RC_DBOReScale);
		return false;
	}

// Connectionpoint anmelden
	_pCT -> Advise (this);
	return true;
}

bool DatenBasisObjekt::ReReadIdents (void) 
{
// DB auffordern, sich neu zu initialisieren
#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		if (DB().ReReadHeader()) {
			SetIdBase (DB().GetIdentBase());
			SetMkBase (DB().GetMkBase());
		}
	}
#endif // _USE_LEGACY_CODE

	TX_ASSERT(NULL != _Idents);

	FillIdents (true);			// Idents neu einlesen
	InitClsIdentMap();			// OKSMap neu initialisieren
	return true;
}

// Funktionen, die aktuell gezeichneten Ausschnitt liefern --------------------
// ACHTUNG: nur gültig während einer ZeichenAktion 
bool DatenBasisObjekt::QueryExposedOC (ObjContainer *pOC)
{
	if (!isDrawing() || !pOC) 
		return false; 	// es wird nicht gezeichnet

	*pOC = ExpOC();
	return true;
}

bool DatenBasisObjekt::QueryExposedArea (Rectangle *pRc)
{
	if (!isDrawing() || !pRc) 
		return false; 	// es wird nicht gezeichnet

	*pRc = EA();
	return true;
}

bool DatenBasisObjekt::isDrawing()
{ 
#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) 
		return _iDrawSem;
#endif // _USE_LEGACY_CODE

	return _iDrawSem  || GetViewWindow()->IsDrawing(); 
}

bool DatenBasisObjekt::isComFile (void)
{
#if defined(_USE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		return DB().IsComDB() ? true : false;
	} else
#endif // _USE_LEGACY_CODE
	{
		return true;		// so tun als ob
	}
}

#if !defined(WIN16)
///////////////////////////////////////////////////////////////////////////////
// ProjektINI kopieren 
inline string MakeProfileName (string strName)
{
	return get_drive(strName) + get_path(strName) + get_name(strName) + g_cbINI;
}

bool CopyProfileFile (string &rstrSrc, LPCSTR pcDest)
{
	if (NULL == pcDest)	return false;

// INI-Dateinamen ableiten
string strSrcIni (MakeProfileName (rstrSrc));
string strDestIni (MakeProfileName (pcDest));

// INI-Datei kopieren
bool fResult = ::CopyFile (strSrcIni.c_str(), strDestIni.c_str(), false);

// evtl. Schreibschutz aufheben
DWORD dwAttr = ::GetFileAttributes (strDestIni.c_str());

	if (0xFFFFFFFF == dwAttr) {
	// Ini existiert nicht oder Fehler aufgetreten, leere Datei erzeugen
	HANDLE hFile = ::CreateFile(strDestIni.c_str(), GENERIC_WRITE, 
			FILE_SHARE_WRITE|FILE_SHARE_READ,
			NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

		if (INVALID_HANDLE_VALUE != hFile)
			CloseHandle(hFile);
		return true;
	}

	if (dwAttr & FILE_ATTRIBUTE_READONLY) {
		dwAttr &= ~FILE_ATTRIBUTE_READONLY;
		::SetFileAttributes (strDestIni.c_str(), dwAttr);
	}
	return fResult;
}

namespace {

///////////////////////////////////////////////////////////////////////////////
// ConnectModes aller existierenden Verbindungen speichern bzw. setzen
HRESULT GetConnectModes(ITRiASProject *pIPrj, vector<CONNECTMODE> &rModes, 
	CONNECTMODE rgNewMode)
{
	COM_TRY {
	WTRiASConnections Conns;
	LONG lCnt = 0;

		THROW_FAILED_HRESULT(pIPrj -> get_Connections (Conns.ppi()));
		THROW_FAILED_HRESULT(Conns -> get_Count(&lCnt));

		for (long i = 1; i <= lCnt; i++) {
		WTRiASConnection Conn;

			THROW_FAILED_HRESULT(Conns -> Item (CComVariant(i), Conn.ppi()));

		CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

			THROW_FAILED_HRESULT(Conn -> get_Status (&rgStatus));
			if (CONNECTSTATUS_Opened == rgStatus) {
			CONNECTMODE rgMode = CONNECTMODE_UseDefaultMode;

				THROW_FAILED_HRESULT(Conn -> get_Mode(&rgMode));
				rModes.push_back(rgMode);

				rgMode = CONNECTMODE(rgMode & ~CONNECTMODE_CloseResolutionFlags);
				rgMode = CONNECTMODE(rgMode | (rgNewMode & CONNECTMODE_CloseResolutionFlags));
				THROW_FAILED_HRESULT(Conn -> put_Mode(rgMode));
			}
			else
				rModes.push_back(CONNECTMODE_UseDefaultMode);
		}

	// jede Connection muß ihren Mode gespeichert haben
		_ASSERTE(rModes.size() == lCnt);

	} COM_CATCH_OP(rModes.clear());
	return S_OK;
}

HRESULT SetConnectModes(ITRiASProject *pIPrj, vector<CONNECTMODE> &rModes)
{
	COM_TRY {
	WTRiASConnections Conns;
	LONG lCnt = 0;

		THROW_FAILED_HRESULT(pIPrj -> get_Connections (Conns.ppi()));
		THROW_FAILED_HRESULT(Conns -> get_Count(&lCnt));

	vector<CONNECTMODE>::iterator it = rModes.begin();

		for (long i = 1; i <= lCnt; ++i, ++it) {
			_ASSERTE(it != rModes.end());

		WTRiASConnection Conn;

			THROW_FAILED_HRESULT(Conns -> Item (CComVariant(i), Conn.ppi()));

		CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

			THROW_FAILED_HRESULT(Conn -> get_Status (&rgStatus));
			if (CONNECTSTATUS_Opened == rgStatus) {
				THROW_FAILED_HRESULT(Conn -> put_Mode(*it));
			}
		}

		_ASSERTE(it == rModes.end());

	} COM_CATCH;
	return S_OK;
}

}

///////////////////////////////////////////////////////////////////////////////
// Einfach speichern
bool DatenBasisObjekt::SaveGeoDB (bool fAutoSave)
{
	TX_ASSERT(IsTRiASDBBased());
	SaveHeader();

vector<CONNECTMODE> vecModes;

	if (fAutoSave) {
	// in Statuszeile anzeigen, daß Autosave  läuft
		DEX_SetMessageString(ResString(IDS_AUTOSAVEINPROGRESS, 128).Addr());

	// derzeitigen ConnectMode der Connections speichern
		if (FAILED(GetConnectModes (m_Prj, vecModes, CONNECTMODE_CloseAutoResolution)))
			vecModes.clear();
	}

HRESULT hr = m_Prj -> Save();

	if (fAutoSave) {
	// Connectmodes wiedereinstellen
		if (vecModes.size() > 0) 
			SetConnectModes(m_Prj, vecModes);

	// Statuszeile wieder rücksetzen
		DEX_SetMessageString(NULL);		// Rücksetzen
	}

	if (SUCCEEDED(hr))
		DEX_SetDirtyGeoDB (false);
	return SUCCEEDED(hr) ? true : false;
}

namespace {
// stellt sicher, daß die derzeit aktive Ansicht wieder neu eingestellt wird
	class CReInitView 
	{
	public:
		CReInitView() 
		{
		char cbBuffer[_MAX_PATH];

			cbBuffer[0] = '\0';
			if (DEX_GetActiveSight(cbBuffer))
				m_strView = cbBuffer;
			m_fPreventRePaint = DEX_IsPreventRepaintActive();
			DEX_SetPreventRepaint(TRUE);
		}
		~CReInitView()
		{
			DEX_SetPreventRepaint(m_fPreventRePaint);
			if (m_strView.size() > 0) {
				DEX_SelectNewSight(m_strView.c_str());
				DEX_RePaint();
			}
		}
		
	private:
		os_string m_strView;
		BOOL m_fPreventRePaint;
	};
}

// Wegspeichern und Namen auf neue Datei setzen -------------------------------
bool DatenBasisObjekt::SaveAsGeoDB (LPCSTR pcName)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		if (!isComFile()) return false;		// muß COM-File sein

	// GeoDB umkopieren
	IStorage *pIStorage = NULL;
	HRESULT hr = CopyToStorageProject (DB().DBDesc(), pcName, &pIStorage, NULL, NULL);
	ErrInstall EC (EC_NOSPACE, ReportNoSpaceError);
	string strOldName = DB().GetDBName();

		if (SUCCEEDED(hr)) {
		// alle anderen auch auffordern zu Speichern
			if (m_fIsFile) DEXN_RenamingFile(NULL);

			hr = DEXN_SaveOtherStorage (pIStorage);		// in neues Storage speichern
			DEXN_HandsOffStorage();
			if (SUCCEEDED(hr)) 
				hr = DEXN_SaveCompleted (pIStorage);	// es bleibt nicht beim alten Storage

			if (FAILED(hr))
				goto labelErrorReturn;
					
		// PBD umkopieren
			if (!PbdDB().isOpened()) {		// noch nicht eröffnet, also selbiges versuchen
			ErrInstall EI (EC_INVPBDNAME);	// keine Fehlerbehandlung
			CActDB Pbd (PbdDB());
					
					;	// nothing else to do
			}

			if (PbdDB().isOpened()) {
			IStorage *pIPbdStorage = NULL;
			
				hr = pIStorage -> CreateStorage (
							WideString (PbdDB().GetDBName()), 
							STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_TRANSACTED,
							0L, 0L, &pIPbdStorage);
				
				if (SUCCEEDED(hr)) {
					hr = CopyToStorageProject (PbdDB().DBDesc(), PbdDB().GetDBName(), 
											   &pIPbdStorage, &CLSID_TRiASMetaDocument,
											   "TRiAS.MetaDocument.2");
					if (SUCCEEDED(hr)) {
					// alles ok, commit und freigeben
						hr = pIPbdStorage -> Commit (STGC_DEFAULT);
						pIPbdStorage -> Release();
						if (FAILED(hr)) {
							pIStorage -> DestroyElement (WideString (PbdDB().GetDBName()));
							db_error (EC_NOSPACE, RC_CloseDB, PbdDB().GetDBName());
						}
					} else {
					// Fehler, freigeben ohne speichern und löschen des erzeugten SubStorages
						pIPbdStorage -> Release();
						pIStorage -> DestroyElement (WideString (PbdDB().GetDBName()));
						goto labelErrorReturn;
					}
				}
				PbdDB().Close (false);		// kein Commit der alten PbdDB
			} else 
				PbdDB().Close (false);		// Pbd wieder aktivieren

		// neues Storage wegschreiben
			if (SUCCEEDED(hr)) {
				hr = pIStorage -> Commit (STGC_DEFAULT);
				if (FAILED(hr))	goto labelErrorReturn;
			} 

		// jetzt auf neue GeoDB/Pbd setzen
			DB().Close (false);				// kein Commit der alten DB
			DB().SetDBName ((char *)pcName);
			DB().SetTempMode (false);		// nicht mehr temporär
			DB().Open (pIStorage);			// wieder eröffnen

			if (m_fIsFile) DEXN_FileRenamed(DB().DBDesc());
			DEX_SetDirtyGeoDB (false);

		// zugehörige PBD-DB initialisieren
			InitPbd (PbdDBDir);
		}

		if (SUCCEEDED(hr)) 
			CopyProfileFile (strOldName, pcName);

	// hier Fehlerbehandlung
	labelErrorReturn:
		if (pIStorage) 
			pIStorage -> Release();

		if (FAILED(hr)) {
			switch (GetScode(hr)) {
			case STG_E_MEDIUMFULL:
				db_error (EC_NOSPACE, RC_CloseDB, DB().GetDBName());
				break;

			default:
				db_error (EC_NOOPEN, RC_CloseDB);
				break;
			}
			return false;
		}
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	CReInitView View;
	char cbBuffer[_MAX_PATH];
	string strOldName (GetDBName(cbBuffer));

		if (m_fIsFile) DEXN_RenamingFile(NULL);
		if (FAILED(m_Prj -> SaveAs(CComBSTR(pcName))))
			return false;

	// ProjektINI kopieren
		CopyProfileFile (strOldName, pcName);

		if (m_fIsFile) 
			DEXN_FileRenamed(DBDesc());
		m_Prj -> put_Temporary (VARIANT_FALSE);		// auf jeden Fall nicht mehr temporär
		DEX_SetDirtyGeoDB (false);

	// Ansicht neu zusammenbauen, da selbige neu geladen wurde
		DEX_RebuildSight();
	}

// alles ok	
	return true;
}

// Wegspeichern und alten Namen beibehalten -----------------------------------
bool DatenBasisObjekt::ExportAsGeoDB (LPCSTR pcName)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		if (!isComFile()) return false;		// muß COM-File sein

	// GeoDB umkopieren
	IStorage *pIStorage = NULL;
	HRESULT hr = CopyToStorageProject (DB().DBDesc(), pcName, &pIStorage, NULL, NULL);
	ErrInstall EC (EC_NOSPACE, ReportNoSpaceError);
	string strOldName = DB().GetDBName();

		if (SUCCEEDED(hr)) {
		// alle anderen auch auffordern zu Speichern
			hr = DEXN_SaveOtherStorage (pIStorage);	// in neues Storage speichern
			if (SUCCEEDED(hr))
				hr = DEXN_SaveCompleted (NULL);			// es bleibt beim alten Storage

			if (FAILED(hr))
				goto labelErrorReturn;
					
		// PBD umkopieren
			if (!PbdDB().isOpened()) {		// noch nicht eröffnet, also selbiges versuchen
			ErrInstall EI (EC_INVPBDNAME);	// keine Fehlerbehandlung
			CActDB Pbd (PbdDB());
					
					;	// nothing else to do
			}

			if (PbdDB().isOpened()) {
			IStorage *pIPbdStorage = NULL;
			
				hr = pIStorage -> CreateStorage (
							WideString (PbdDB().GetDBName()), 
							STGM_CREATE | STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_TRANSACTED,
							0L, 0L, &pIPbdStorage);
				
				if (SUCCEEDED(hr)) {
					hr = CopyToStorageProject (PbdDB().DBDesc(), PbdDB().GetDBName(), 
											   &pIPbdStorage, &CLSID_TRiASMetaDocument,
											   "TRiAS.MetaDocument.2");
					if (SUCCEEDED(hr)) {
					// alles ok, commit und freigeben
						hr = pIPbdStorage -> Commit (STGC_DEFAULT);
						pIPbdStorage -> Release();
						if (FAILED(hr)) {
							pIStorage -> DestroyElement (WideString (PbdDB().GetDBName()));
							db_error (EC_NOSPACE, RC_CloseDB, PbdDB().GetDBName());
						}
					} else {
					// Fehler, freigeben ohne speichern und löschen des erzeugten SubStorages
						pIPbdStorage -> Release();
						pIStorage -> DestroyElement (WideString (PbdDB().GetDBName()));
					}
				}
			}

		// neues Storage schließen
			if (SUCCEEDED(hr))
				hr = pIStorage -> Commit (STGC_DEFAULT);
		}

		if (SUCCEEDED(hr)) 
			CopyProfileFile (strOldName, pcName);

	labelErrorReturn:
		if (pIStorage) 
			pIStorage -> Release();

		if (FAILED(hr)) {
			switch (GetScode(hr)) {
			case STG_E_MEDIUMFULL:
				db_error (EC_NOSPACE, RC_CloseDB, DB().GetDBName());
				break;

			default:
				db_error (EC_NOOPEN, RC_CloseDB);
				break;
			}
			return false;
		}
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		if (FAILED(m_Prj -> ExportCopyAs(CComBSTR(pcName))))
			return false;

	// ProjektINI kopieren
	char cbBuffer[_MAX_PATH];
	string strOldName (GetDBName(cbBuffer));

		CopyProfileFile (strOldName, pcName);

	// Ansicht neu zusammenbauen, da selbige neu geladen wurde
		DEX_RebuildSight();
	}

// alles ok	
	return true;
}
#endif // WIN16

// Abfragen der HauptFarbe eines Objektes -------------------------------------
static Color ConvertPalette (Color C, HPALETTE hPal)
{
	if (hPal && C.Reserved() != 0) {
		GetPaletteEntries (hPal, C.Red(), 1, (PALETTEENTRY *)&C);
		C.Reserved() = 0;
	}

return C;
}

Color DatenBasisObjekt::GetObjectColor (long lONr)
{
// 1. IdentVisInfo besorgen
VisType iVTyp = OTypToVTyp (RetrieveObjTyp (lONr));	// VisualisierungsTyp
CTable t(Idents().IdentTree());
bool fMetaDC = false;

DRAWOBJECTEX dObj;

	INITSTRUCT(dObj, DRAWOBJECTEX);
	dObj.lObjNr = lONr;			// ObjektNummer
	dObj.lIdent = RetrieveIdent (lONr);

	if (t.Find(&dObj.lIdent)) {
	CIdentifikatorLock l(t);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		dObj.pNewVI = l -> GetVisInfo (iVTyp);
		fMetaDC = l -> GetMetaDCFlag();
	}

// 2. evtl. Objektbezogene Visualisierung dazugenerieren
	dObj.m_fFlags = DF_Analyze;		// nicht zeichnen
	DEXN_DrawObjectEx (dObj);		// alle anderen fragen ...

	if (NULL == dObj.pNewVI) return Color(WHITE);

Color C = WHITE;		// Standard: weiß

	switch (dObj.pNewVI -> isA()) {
//	case VT_Punkt:		// #HK980316
	case VT_Linie:
	case VT_Text:
	case VT_Default:
		if (fMetaDC)
			C = ConvertPalette (dObj.pNewVI -> PrimColor(), hPalette);
		else
			C = dObj.pNewVI -> PrimColor();
		break;

	case VT_Punkt:		// #HK980316
		C = ConvertPalette (((PVisInfo *)dObj.pNewVI) -> SecColor(), hPalette);
		break;

	case VT_Flaeche:
		C = ConvertPalette (((FVisInfo *)dObj.pNewVI) -> SecColor(), hPalette);
		break;

	default:
		TX_ASSERT(false);
		break;
	}
	DELETE_OBJ(dObj.pNewVI);

return C;
}

// Liefert Objekttypen eines Idents in der aktuellen Sicht --------------------
short DatenBasisObjekt::GetActIdentObjTypes (LONG lIdent)
{
CTable tabI(Idents().IdentTree());

	if (tabI.Find (&lIdent)) {
	CIdentifikatorLock l(tabI);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (!l) return 0;

	// ggf. aus GeoDB lesen
		return (l -> toPaint() & l -> InitOTypes()) | (l -> hasKO() ? OTKO : 0);
	}
	return 0;		// nicht in dieser Sicht vertreten
}


#if !defined(WIN16)
// alle Merkmale eines Objektes löschen (mit Undo/Redo) -----------------------
bool DatenBasisObjekt::DeleteFeatures (LONG lONr)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		TX_ASSERT(IsValidONr(DB().DBDesc(), lONr));

	CActDB ActDB (DB());
	MerkmalsListe ML (&DB(), &PbdDB(), lONr, TT_Objekt); //, false);
	CTable t(ML);

		for (t.First(); t.Valid(); t.Next()) {
		PBD_MerkmalLock l(t);

		// keine SystemMerkmale behandeln (das sollen die tun, die sie erzeugt haben)
			TX_ASSERT(NULL != (PBD_Merkmal *)l);

			if (l -> isSystem()) continue;

		// Merkmal löschen
		LPUNDOREDOOBJECTFEATURE pIUndo = NULL;
		HRESULT hr = UndoCreateInstance (IID_IUndoRedoObjectFeature,
						 (LPVOID *)&pIUndo);

			if (SUCCEEDED(hr) && 
				pIUndo -> Init (lONr, l -> GetCode(), "", NULL) == NOERROR) 
			{
				DEX_AddUndoRedo (pIUndo);
			}
			if (pIUndo) pIUndo -> Release();

			if (!WriteTextMerkmal (TT_Objekt, lONr, l -> GetCode(), NULL))
				return false;
		}
		return true;
	} else
#endif // defined(_FORCE_LEGACY_CODE)
	{
		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		WTRiASFeatures Feats;
		WTRiASObject Obj;

			THROW_FAILED_HRESULT(GetObjectFeatures (lONr, Feats.ppi(), Obj.ppi()));

		WEnumVARIANT Enum;
		CComVariant vVal (DISP_E_PARAMNOTFOUND, VT_ERROR);
		CComVariant v;

			THROW_FAILED_HRESULT(Feats -> _NewEnum (Enum.ppu()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
				if (FAILED(v.ChangeType (VT_DISPATCH)))
					continue;

			WTRiASFeature Feat (V_DISPATCH(&v));
			LONG lMCode = 0L;

				THROW_FAILED_HRESULT(Feat -> get_Handle ((INT_PTR *)&lMCode));

			LPUNDOREDOOBJECTFEATURE pIUndo = NULL;
			HRESULT hr = UndoCreateInstance (IID_IUndoRedoObjectFeature, (LPVOID *)&pIUndo);

				if (SUCCEEDED(hr) && S_OK == pIUndo -> Init (lONr, lMCode, "", NULL)) 
				{
					DEX_AddUndoRedo (pIUndo);
				}
				if (pIUndo) pIUndo -> Release();

			// jetzt wirklich löschen
				THROW_FAILED_HRESULT(Feat -> Update (Obj, vVal));
			}
		} COM_CATCH_IGNORE;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// alle Relationen die ein Objekt besitzt auflösen (mit Undo/Redo)
namespace {
	BOOL CALLBACK DeleteRelationProc (long lONr, long lRCode, short iRTyp, void *pData)
	{
	// Relation auflösen
	DELRELATIONEX DR;

		INITSTRUCT(DR, DELRELATIONEX);
		DR.lPONr = *(INT_PTR *)pData;
		DR.lSONr = lONr;
		DR.lRCode = lRCode;
		DR.iRTyp = iRTyp;
		DR.fUndo = TRUE;
		return (EC_OKAY == DEX_DeleteRelation(DR)) ? TRUE : FALSE;
	}
} // namespace

bool DatenBasisObjekt::DeleteRelations (LONG lONr)
{
ENUMRELATIONOBJS ERO;

	INITSTRUCT(ERO, ENUMRELATIONOBJS);
	ERO.lONr = lONr;
	ERO.lRCode = 0L;		// alle Relationen
	ERO.iRTyp = RTKomplexO|RTKomplexU|RTBegleitO|RTBegleitU|RTGleich;
	ERO.eFcn = (ENUMRELOBJPROC)DeleteRelationProc;
	ERO.pData = &lONr;
	return DEX_EnumRelationObjects(ERO);
}

///////////////////////////////////////////////////////////////////////////////
// aktuellen Darstellungsmaßstab setzen 
inline void CondSwap (KoOrd &rlXMin, KoOrd &rlXMax)
{
	if (rlXMin > rlXMax) {
	KoOrd temp = rlXMax;

		rlXMax = rlXMin;
		rlXMin = temp;
	}
}

bool DatenBasisObjekt::SetActiveScaling (
		long lZoom, Rectangle &rRc, Rectangle &rCRc, ObjContainer &rOC)
{
	TX_ASSERT(lZoom > 0);		// Vergrößerung muß größer 1 sein
	if (lZoom <= 0 || NULL == pCT()) 
		return false;

// Koordinaten in DB-Koordinaten umsetzen
Punkt PtMin = DCtoOC (rRc.Left(), rRc.Bottom());       // Device --> Objekt
Punkt PtMax = DCtoOC (rRc.Right(), rRc.Top());
double dXMin, dXMax, dYMin, dYMax;
	
// Koordinaten transformieren (incl. rausrechnen der internen Skalierung)
#if !defined(_KOORD_ISDOUBLE)
	pCT() -> UnScale (PtMin, &dXMin, &dYMin);
	pCT() -> UnScale (PtMax, &dXMax, &dYMax);
#else
	dXMin = PtMin.GetX();
	dYMin = PtMin.GetY();
	dXMax = PtMax.GetX();
	dYMax = PtMax.GetY();
#endif // _KOORD_ISDOUBLE

// MittelpunktsKoordinaten berechnen
DoublePair DP1 (dXMin, dYMax);
DoublePair DP2 (dXMax, dYMax);
DoublePair DP3 (dXMin, dYMin);
double dXDelta = 0.0;
double dYDelta = 0.0;

	if (pCT() -> hasDistEx()) {
	DoublePair DP4 (dXMax, dYMin);

		pCT() -> CoordTransDistanceEx (&DP1, &DP4, dXDelta, dYDelta);
	} else {
		dXDelta = pCT() -> CoordTransDistance (&DP1, &DP2);
		dYDelta = pCT() -> CoordTransDistance (&DP1, &DP3);
	}

	DP1 = DoublePair (dXMin, dYMin);
	DP2 = DoublePair (fabs(dXDelta/2), fabs(dYDelta/2));
	pCT() -> CoordTransRectangle (&DP1, &DP2, &DP3);

// jetzt neuen Ausschnitt über Maßstab rückrechnen
// Größe des FensterAusschnittes besorgen
CoOrd iSizeX = CoOrd(rCRc.Right()-rCRc.Left());		// FensterGröße als Bezug
CoOrd iSizeY = CoOrd(rCRc.Top()-rCRc.Bottom());

// halbe Größe des Ausschnitts
DoublePair mDelta (-((double)lZoom * iSizeX)/(_DotsPerMM.Width()*2000.0),
				   ((double)lZoom * iSizeY)/(_DotsPerMM.Height()*2000.0));

// linke obere Ecke berechnen
	pCT() -> CoordTransRectangle (&DP3, &mDelta, &DP1);

// rechte untere Ecke berechnen
DoublePair Delta (((double)lZoom * iSizeX)/(_DotsPerMM.Width()*1000.0),
				 -((double)lZoom * iSizeY)/(_DotsPerMM.Height()*1000.0));

	pCT() -> CoordTransRectangle (&DP1, &Delta, &DP2);

// neuen DBContainer berechnen
//	pCT() -> InvTransform (&DP1, 1);
//	pCT() -> InvTransform (&DP2, 1);
#if defined(_KOORD_ISDOUBLE)
	rOC.SetXMin(DP1.X());
	rOC.SetYMax(DP1.Y());
	rOC.SetXMax(DP2.X());
	rOC.SetYMin(DP2.Y());
#else
KoOrd x, y;

	pCT() -> Scale (DP1.X(), DP1.Y(), &x, &y);
	rOC.SetXMin(x);
	rOC.SetYMax(y);

	pCT() -> Scale (DP2.X(), DP2.Y(), &x, &y);
	rOC.SetXMax(x);
	rOC.SetYMin(y);
#endif // _KOORD_ISDOUBLE

// Korrektur des neues Ausschnittes (kippen)
	rOC.CondSwapX();
	rOC.CondSwapY();

	return true;
}

#endif // WIN16

long DatenBasisObjekt::GetClipRegionONr (LPCSTR pcView)
{
long lONr = -1L;
char cbBuffer[MAXVIEWNAMESIZE+1];

	if (NULL == pcView) {
	// aktuelle Ansicht verwenden
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer)-1))
			return -1L;		// Fehler oder keine aktuelle Ansicht
		pcView = cbBuffer;
	}

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	Sicht View (DB(), pcView);

		lONr = View.GetObjRgn();	// ClippingObjekt
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		// Ansicht besorgen
		WTRiASView View;

			THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pcView), VARIANT_FALSE, View.ppi()));

		// alle Properties der Ansicht abfragen
		WTRiASProperties Props;

			THROW_FAILED_HRESULT(WTRiASPropertyBase(View) -> get_Properties (Props.ppi()));

		// GetProperty liefert mit AddRef ab!
		WTRiASObject Obj (GetProperty (Props, g_cbObjectRegion, (IDispatch *)NULL), false);

			if (Obj.IsValid()) 
				Obj -> get_Handle ((INT_PTR *)&lONr);

		} COM_CATCH_IGNORE;
	}

	if (0L == lONr)
		lONr = -1L;		// kein Objekt gegeben
	return lONr;
}

bool DatenBasisObjekt::SetClipRegionONr (CLIPOBJECTSET *pCOS)
{
long lONr = pCOS -> m_lONr;
long lResult = 0L;

	if (0 == lONr) lONr = -1L;		// ClipObjekt löschen

char cbBuffer[MAXVIEWNAMESIZE+1];
LPCSTR pcView = pCOS -> m_pcView;

	if (NULL == pcView) {
		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer)-1)) 
		// Fehler oder keine aktuelle Ansicht
			return 0L;
		pcView = cbBuffer;
	}

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
	Sicht View (DB(), pCOS -> m_pcView);

		lResult = View.SetObjRgn(lONr);		// ClippingObjekt
		if (m_pViews -> isActView (pcView))	// wenn aktuelle Ansicht
			ClipRegionONr() = lONr;			// dann fürs Zeichnen setzen
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		COM_TRY {
		// Ansicht besorgen
		WTRiASView View;

			THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pCOS -> m_pcView), VARIANT_FALSE, View.ppi()));

		// alle Properties der Ansicht abfragen
		WTRiASProperties Props;

			THROW_FAILED_HRESULT(WTRiASPropertyBase(View) -> get_Properties (Props.ppi()));

		WTRiASObject Obj;

			THROW_FAILED_HRESULT(GetObjectFromMap(lONr, Obj));
			THROW_FAILED_HRESULT(SetProperty (Props, g_cbObjectRegion, Obj, true));

		} COM_CATCH_RETURN(false);
	}

// dummerweise ist lResult entweder ein ErrCode oder 
// eine Objektnummer (>= -1)
	return (lResult >= -1L) ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
// Objektanzahl liefern
LONG DatenBasisObjekt::CountObjects (void)
{
	if (-1L == m_lObjCnt) {
	CRing r (*m_pGeoDBs);

		m_lObjCnt = 0;
		for (r.First(); r.Valid(); r.Next()) {
		GeoDBLock l(r);

			TX_ASSERT(NULL != (GeoDB *)l);
			if (l -> isOpened())
			{ 
				m_lObjCnt += l -> CountObjects();
			}
		}
	}
	return m_lObjCnt;
}

LONG DatenBasisObjekt::GetIdentObjectCount (IDENTOBJECTCOUNT *pData)
{
LONG lCnt = 0;

	COM_TRY {
	WTRiASObjects Objs;
	WTRiASSimpleObjects SimpleObjs;

		THROW_FAILED_HRESULT(GetObjectsFromMap(pData -> ulIdent, Objs));
		if (SUCCEEDED(Objs -> QueryInterface(SimpleObjs.ppi()))) {
		// TRiAS Objektmengen wissen, wieviele Objekte sie haben
			THROW_FAILED_HRESULT(SimpleObjs -> get_Count(
				(OBJECTTYPE)pData -> iOTypes, &lCnt));
		}
		else {
		// alternative Implementation
		// Objektzähler sicherstellen
			if (!Idents().FindId (pData -> ulIdent, NULL))
				return 0L;		// Fehler oder nichts gefunden

		// Anzahl der Objekte zusammenzählen
			if (OTPunkt & pData -> iOTypes)
				lCnt += Idents().GetObjectCount (pData -> ulIdent, OT_PUNKT);
			if (OTLinie & pData -> iOTypes)
				lCnt += Idents().GetObjectCount (pData -> ulIdent, OT_KANTE);
			if (OTFlaeche & pData -> iOTypes)
				lCnt += Idents().GetObjectCount (pData -> ulIdent, OT_FLAECHE);
			if (OTText & pData -> iOTypes)
				lCnt += Idents().GetObjectCount (pData -> ulIdent, OT_TEXT);
		}

	} COM_CATCH;
	return lCnt;
}

LONG DatenBasisObjekt::GetIdentObjectCountEx (IDENTOBJECTCOUNTEX *pData)
{
LONG lCnt = 0;

	COM_TRY {
	WTRiASObjects Objs;
	WTRiASSimpleObjects SimpleObjs;

		THROW_FAILED_HRESULT(GetObjectsFromMap(pData -> ulIdent, Objs));
		if (SUCCEEDED(Objs -> QueryInterface(SimpleObjs.ppi()))) {
		// TRiAS Objektmengen wissen, wieviele Objekte sie haben
			if (OTPunkt & pData -> iOTypes) {
				THROW_FAILED_HRESULT(SimpleObjs -> get_Count(
					OBJECTTYPE_Point, &pData -> lPoints));
			}
			if (OTLinie & pData -> iOTypes) {
				THROW_FAILED_HRESULT(SimpleObjs -> get_Count(
					OBJECTTYPE_Line, &pData -> lLines));
			}
			if (OTFlaeche & pData -> iOTypes) {
				THROW_FAILED_HRESULT(SimpleObjs -> get_Count(
					OBJECTTYPE_Area, &pData -> lAreas));
			}
			if (OTText & pData -> iOTypes) {
				THROW_FAILED_HRESULT(SimpleObjs -> get_Count(
					OBJECTTYPE_Text, &pData -> lTexts));
			}
			THROW_FAILED_HRESULT(SimpleObjs -> get_Count(
				(OBJECTTYPE)pData -> iOTypes, &lCnt));
		}
		else {
		// alternative Implementation
		// Objektzähler sicherstellen
			if (!Idents().FindId (pData -> ulIdent, NULL))
				return 0L;		// Fehler oder nichts gefunden

		// Anzahl der Objekte zusammenzählen
			if (OTPunkt & pData -> iOTypes) {
				pData -> lPoints =  Idents().GetObjectCount (pData -> ulIdent, OT_PUNKT);
				lCnt += pData -> lPoints;
			}
			if (OTLinie & pData -> iOTypes) {
				pData -> lLines = Idents().GetObjectCount (pData -> ulIdent, OT_KANTE);
				lCnt += pData -> lLines;
			}
			if (OTFlaeche & pData -> iOTypes) {
				pData -> lAreas = Idents().GetObjectCount (pData -> ulIdent, OT_FLAECHE);
				lCnt += pData -> lAreas; 
			}
			if (OTText & pData -> iOTypes) {
				pData -> lTexts = Idents().GetObjectCount (pData -> ulIdent, OT_TEXT);
				lCnt += pData -> lTexts;
			}
		}

	} COM_CATCH;
	return lCnt;
}

LONG DatenBasisObjekt::IncrementObjectCount (void)
{
	m_lObjCnt = CountObjects() +1;

	TX_ASSERT(m_lObjCnt > 0);
	return m_lObjCnt;
}

LONG DatenBasisObjekt::DecrementObjectCount (void)
{
	m_lObjCnt = CountObjects() -1;

	TX_ASSERT(m_lObjCnt >= 0);
	return m_lObjCnt;
}

///////////////////////////////////////////////////////////////////////////////
// Priorität ändern/abfragen
using trias_nativeview::CNativeView;

OBJECTTYPE VisTypeToOBJECTTYPE (CNativeView::VisType rgType)
{
	switch (rgType) {
	case CNativeView::VT_Punkt:
	case CNativeView::VT_PunktDef:
		return OBJECTTYPE_Point;

	case CNativeView::VT_Linie:
	case CNativeView::VT_LinieDef:
		return OBJECTTYPE_Line;

	case CNativeView::VT_Flaeche:
	case CNativeView::VT_FlaecheDef:
		return OBJECTTYPE_Area;

	case CNativeView::VT_Text:
	case CNativeView::VT_TextDef:
		return OBJECTTYPE_Text;

	default:
	case CNativeView::VT_Default:
		break;
	}
	return OBJECTTYPE_Unknown;
}

VISINFOTYPE VisTypeToVISINFOTYPE (CNativeView::VisType rgType)
{
	switch (rgType) {
	case CNativeView::VT_Punkt:
	case CNativeView::VT_PunktDef:
		return VISINFOTYPE_Point;

	case CNativeView::VT_Linie:
	case CNativeView::VT_LinieDef:
		return VISINFOTYPE_Line;

	case CNativeView::VT_Flaeche:
	case CNativeView::VT_FlaecheDef:
		return VISINFOTYPE_Area;

	case CNativeView::VT_Text:
	case CNativeView::VT_TextDef:
		return VISINFOTYPE_Text;

	default:
	case CNativeView::VT_Default:
		break;
	}
	return VISINFOTYPE_Default;
}

CNativeView::VisType OBJECTTYPEToVisType (OBJECTTYPE rgType)
{
	if (rgType & OBJECTTYPE_Point)
		return CNativeView::VT_Punkt;

	if (rgType & OBJECTTYPE_Line)
		return CNativeView::VT_Linie;

	if (rgType & OBJECTTYPE_Area)
		return CNativeView::VT_Flaeche;

	if (rgType & OBJECTTYPE_Text)
		return CNativeView::VT_Text;

	return CNativeView::VT_Default;
}

HRESULT DatenBasisObjekt::GetIdentPriority (IDENTPRIORITY *pData)
{
	TEST_E_POINTER("DatenBasisObjekt::GetIdentPriority", pData);

// evtl. Ident besorgen
	if (0 == pData -> ulIdent) {
		pData -> ulIdent = RetrieveIdent (pData -> lONr);
		pData -> iVisType = (int)OTypToVTyp(RetrieveObjTyp (pData -> lONr));
	}

// Priorität auslesen
	if (NULL == pData -> pcView) {		// aktuelle Ansicht
	CTable t(Idents().IdentTree());

		if (t.Find(&(pData -> ulIdent))) {
		CIdentifikatorLock l(t);
		
			TX_ASSERT(NULL != (CIdentifikator *)l);
			if (!l) return E_UNEXPECTED;

			pData -> iPriority = l -> Priority ((VisType)pData -> iVisType);
		} else
			return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);	// Ansicht/Ident existiert nicht

	} else {
#if defined(_FORCE_LEGACY_CODE)
		if (!IsTRiASDBBased()) {
		// irgend eine andere Ansicht
		Sicht View (DB(), pData -> pcView);
		VisInfo *pVI = NULL;

			if (!View.isValid() || 
				EC_OKAY != View.GetIDfromSight (pData -> ulIdent, &pVI, pData -> iVisType))
			{
				return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);	// Ansicht/Ident existiert nicht
			}
			if (NULL == pVI)
				return E_OUTOFMEMORY;

			delete pVI;
		} else
#endif // _FORCE_LEGACY_CODE
		{
			TX_ASSERT(IsTRiASDBBased());
			COM_TRY {
			// Ansicht besorgen
			WTRiASView View;

				THROW_FAILED_HRESULT(m_Prj -> get_View (CComBSTR(pData -> pcView), VARIANT_FALSE, View.ppi()));

			// ViewItem wiederfinden
			WTRiASViewItem ViewItem;
			WTRiASObjects Objs;

				THROW_FAILED_HRESULT(GetObjectsFromMap(pData -> ulIdent, Objs));
				THROW_FAILED_HRESULT(View -> get_ViewItem (CComVariant(Objs), VARIANT_FALSE, CComBSTR(g_cbNil), ViewItem.ppi()));

			// jetzt die geforderte Info abfragen
			WDVisInfo VI;
			OBJECTTYPE rgType = VisTypeToOBJECTTYPE((CNativeView::VisType)pData -> iVisType);

				THROW_FAILED_HRESULT(ViewItem -> get_VisInfo(rgType, VI.ppi()));
				THROW_FAILED_HRESULT(VI -> get_Priority (&pData -> iPriority))

			} COM_CATCH;
		}
	}
	return S_OK;
}

HRESULT DatenBasisObjekt::SetIdentPriority (IDENTPRIORITY *pData)
{
	TEST_E_POINTER("DatenBasisObjekt::SetIdentPriority", pData);
	ATLTRACENOTIMPL("DatenBasisObjekt::SetIdentPriority");
}

bool DatenBasisObjekt::ActivateObj (Window *pWnd, long lONr, COLORREF crAct, bool fAssoc) 
{
CONrTable t(Shapes().ObjNumTree());

	if (!t.Find (&lONr)) return false;

ExtShapeObjectONrLock l(t);

	TX_ASSERT(NULL != (ExtShapeObject *)l);
	
// auf gesamtem Canvasbereich malen
Color oldColor;
ExtShapeObject *pESO = (ExtShapeObject *)l;
Rectangle rcT = pWnd -> CanvasRect();
ObjContainer ocT = rcT;
		
	SetEA (rcT);
	SetExpOC (ocT);

// Hervorheben des gewünschten Objektes
	pESO -> FullDCInit() = FDC_FullInit | FDC_ActivateOnly;

// Attribute für dieses Objekt einstellen
VisInfo *pVI = (VisInfo *)DEX_SetAttributes (lONr);

	if (pVI != NULL) {
	Color ActC = (Color &)crAct;

		switch (pESO -> isTyp()) {
		case OT_PUNKT:	// PunktObjekt
			{
			PunktObjekt *pPO = (PunktObjekt *)pESO;

				oldColor = pPO -> ChangeColor (&ActC);
				pWnd -> DrawEx (pPO, reinterpret_cast<DWORD>(this));
				pPO -> ChangeColor (&oldColor);
			}
			break;

		case OT_LABEL:
		case OT_TEXT:	// SchriftObjekt (immer ohne Rahmen)
			{
			SchriftObjekt *pSO = (SchriftObjekt *)pESO;
			short oldFrameMode = pSO -> ChangeFrame (0);

				oldColor = pSO -> ChangeColor (&ActC);
				pWnd -> DrawEx (pSO, reinterpret_cast<DWORD>(this));
				pSO -> ChangeColor (&oldColor);
				pSO -> ChangeFrame (oldFrameMode);
			}
			break;

		case OT_KO:	// KomplexObjekt
#if defined(_USE_KOMPLEX_OBJECTS)
			{
			RelationsObjekt *pRO = (RelationsObjekt *)pESO;
			ObjektListeIterator KOI (pRO -> KO().OL());
			long lDepONr = KOI.FirstONr();

				while (lDepONr != -1L) {
				// untergeordnete Objekte aktivieren
					ActivateObj (pWnd, lDepONr, crAct, false);		// immer nur eine Etage tief gehen
					lDepONr = KOI.NextONr();
				}
			}
#endif // defined(_USE_KOMPLEX_OBJECTS)
			break;

		case OT_UNKNOWN:
			break;

		case OT_KANTE:
		case OT_FLAECHE:
		case OT_KREIS:
		default:
			{
			ExtPen actPen (SolidLine, 1, ActC);
			pPen oldPen = pESO -> ChangePen (&actPen);

			// Flächen nicht füllen
			Brush Hollow(HollowBrush);
			pBrush oldBrush = pESO -> ChangeBrush (&Hollow);

				pWnd -> DrawEx (pESO, reinterpret_cast<DWORD>(this));
				pESO -> ChangeBrush (oldBrush);            
				pESO -> ChangePen (oldPen);
			}
			break;
		}
		pESO -> FullDCInit() = FDC_ActivateOnly;
	}
	
// Attribute wieder rücksetzen
RESETATTRDATA RAD;

	RAD.lONr = lONr;
	RAD.pVI = pVI;
	DEX_ResetAttributes (&RAD);

// nachsehen, ob Textobjekt dranhängt
	if (fAssoc) {
	ErrInstall EI (EC_DELRECORD);	// für Objektlöschen
	ErrInstall EI2 (EC_INVADDR);	// für temporäre Objekte
	long lAssocON = AssociatedObjekt (lONr, NULL);

		if (lAssocON != 0) {
		short iBits = OTypToBits ((ObjTyp)DEX_GetObjectType (lAssocON));

			if (Idents().toPaint (RetrieveIdent(lAssocON), iBits)) 
				ActivateObj (pWnd, lAssocON, crAct, false);		// Rekursion vermeiden
		}
	}
	return true;		
}

bool DatenBasisObjekt::DeActivateObj (Window *pWnd, long lONr, bool fAssoc) 
{
CONrTable t(Shapes().ObjNumTree());

	if (!t.Find (&lONr)) 
		return false;	// unbekanntes Objekt

ExtShapeObjectONrLock l(t);

	TX_ASSERT(NULL != (ExtShapeObject *)l);

// auf gesamtem Canvasbereich malen
ExtShapeObject *pESO = (ExtShapeObject *)l;
Rectangle rcT = pWnd -> CanvasRect();
ObjContainer ocT = rcT;
		
	SetEA (rcT);
	SetExpOC (ocT);

// Attribute für dieses Objekt einstellen
	pESO -> FullDCInit() = FDC_FullInit | FDC_ActivateOnly;

VisInfo *pVI = (VisInfo *)DEX_SetAttributes (lONr);

	if (NULL != pVI) {
		switch (pESO -> isTyp()) {
		case OT_PUNKT:
		// Punktobjekte nur neu malen
			pWnd -> DrawEx (pESO, reinterpret_cast<DWORD>(this));
			break;

		case OT_LABEL:
		case OT_TEXT:
			{
			SchriftObjekt *pSO = (SchriftObjekt *)pESO;
			short oldFrameMode = pSO -> ChangeFrame (0);

				pWnd -> DrawEx (pSO, reinterpret_cast<DWORD>(this));
				pSO -> ChangeFrame (oldFrameMode);
			}
			break;
			
		case OT_KO:
			{
#if defined(_USE_KOMPLEX_OBJECTS)
			RelationsObjekt *pRO = (RelationsObjekt *)pESO;
			ObjektListeIterator KOI (pRO -> KO().OL());
			long lDepONr = KOI.FirstONr();

				while (lDepONr != -1L) {
					DeActivateObj (pWnd, lDepONr, false);	// immer nur eine Etage tief gehen
					lDepONr = KOI.NextONr();
				}
#endif // defined(_USE_KOMPLEX_OBJECTS)
			}
			break;

		case OT_UNKNOWN:
			break;	// do nothing

		default:
		case OT_KANTE:
		case OT_FLAECHE:
		case OT_KREIS:
			{
			// Flächen nicht füllen
			Brush Hollow(HollowBrush);
			pBrush oldBrush = pESO -> ChangeBrush (&Hollow);
			
				pWnd -> DrawEx (pESO, reinterpret_cast<DWORD>(this));	// zeichnen
				pESO -> ChangeBrush (oldBrush);		// wieder herstellen
			}
			break;
		}
		pESO -> FullDCInit() = FDC_NoInit;
	}
	
// Attribute wieder rücksetzen
RESETATTRDATA RAD;

	RAD.lONr = lONr;
	RAD.pVI = pVI;
	DEX_ResetAttributes (&RAD);

// nachsehen, ob TextObjekt dranhängt
	if (fAssoc) {
	ErrInstall EI (EC_DELRECORD);	// für Objektlöschen
	ErrInstall EI2 (EC_INVADDR);	// für temporäre Objekte
	long lAssocON = AssociatedObjekt (lONr, NULL);

		if (lAssocON != 0) {
		short iBits = OTypToBits ((ObjTyp)DEX_GetObjectType (lAssocON));

			if (Idents().toPaint (RetrieveIdent(lAssocON), iBits)) 
				DeActivateObj (pWnd, lAssocON, false);		// Rekursion vermeiden
		}
	}

	return true;				
}

///////////////////////////////////////////////////////////////////////////////
// ObjektGuid verwalten
HRESULT DatenBasisObjekt::GetObjectGuid (OBJECTGUID *pGuid)
{
//	if (VERSION0500000E <= DB().GetDBVersion()) {
		return DB(GetObjectDBHandle(pGuid -> lONr)).GetObjectGUID (pGuid -> lONr, &pGuid -> guid);
//	} else {
//		if (0L == m_lObjGuidMCode)
//			m_lObjGuidMCode = GetHeaderMCode (false, IDS_OBJECTGUIDHDR);
//		if (-1L == m_lObjGuidMCode) 
//			return E_FAIL;
//
//		return DB().GetObjectGUIDFeature (pGuid -> lONr, m_lObjGuidMCode, &pGuid -> guid);
//	}
}

HRESULT DatenBasisObjekt::FindObjectFromGuid (HPROJECT hPr, OBJECTGUID *pGuid)
{
	if (HACTCONNECTION != hPr) {
	// nur in der vorgegebenen Datenquelle suchen
		return DB(hPr).FindObjectFromGUID (pGuid -> guid, &pGuid -> lONr);
	}
	else {
	// in allen Datenquellen suchen
	CRing r (*m_pGeoDBs);

		for (r.First(); r.Valid(); r.Next()) {
		GeoDBLock l(r);

			TX_ASSERT(NULL != (GeoDB *)l);
			if (l -> isOpened()) { 
				if (SUCCEEDED(l->FindObjectFromGUID (pGuid -> guid, &pGuid -> lONr)))
					return S_OK;
			}
		}
		return E_FAIL;
	}
}

HRESULT DatenBasisObjekt::SetObjectGuid (OBJECTGUID *pGuid)
{
HRESULT hr = S_OK;

//	if (VERSION0500000E <= DB().GetDBVersion()) {
		hr = DB(GetObjectDBHandle(pGuid -> lONr)).SetObjectGUID (pGuid -> lONr, pGuid -> guid);
//	} else {
//		if (0L == m_lObjGuidMCode)
//			m_lObjGuidMCode = GetHeaderMCode (true, IDS_OBJECTGUIDHDR, NULL, 
//								IDS_OBJECTGUIDMCODE, IDS_OBJECTGUIDMCODE);
//		if (-1L == m_lObjGuidMCode) 
//			return E_FAIL;
//
//		hr = DB().SetObjectGUIDFeature (pGuid -> lONr, pGuid -> guid, m_lObjGuidMCode);
//	}

	if (HRESULT_FROM_ERRCODE(WC_DUPLICATE) == hr)
		hr = FindObjectFromGuid (DEX_GetObjectProject(pGuid -> lONr), pGuid);
	
	return hr;
}

INT_PTR DatenBasisObjekt::RetrieveObjGuidMCodeIdent (INT_PTR lIdent)
{
	TX_ASSERT(IsValidIdent(lIdent));

HPROJECT hPr = GetIdentParentHandle(lIdent);
INT_PTR lHandle = -1L;

	COM_TRY {
	WTRiASFeature Feat;

		THROW_FAILED_HRESULT(DB(hPr).GetFeature (lIdent, g_cbPrimaryKey, Feat.ppi()));
		THROW_FAILED_HRESULT(Feat -> get_Handle (&lHandle));

	} COM_CATCH_RETURN(-1L);
	return lHandle;
}

///////////////////////////////////////////////////////////////////////////////
// 'globalen TranformationsBuffer behandeln
POINT *DatenBasisObjekt::AllocDrawBuffer (size_t lCntPts)
{
	if (lCntPts > m_lCntPts) {
	// bisherigen Speicher freigeben
		FreeDrawBuffer();

	// Speicher neu anlegen
		TX_TRY(m_ptsToDraw = new POINT [lCntPts]);
		if (NULL == m_ptsToDraw)
			return NULL;

		TX_TRY(m_pCoords = new CSCOORD [lCntPts]);
		if (NULL == m_pCoords)
			return NULL;

		m_lCntPts = lCntPts;
	}
	return m_ptsToDraw;
}

void DatenBasisObjekt::FreeDrawBuffer()
{
	DELETE_OBJ(m_ptsToDraw);
	DELETE_OBJ(m_pCoords);
	m_lCntPts = 0L;
}

CSCOORD *DatenBasisObjekt::GetCoordBuffer()
{
	TX_ASSERT(NULL != m_pCoords);
	return m_pCoords;
}

///////////////////////////////////////////////////////////////////////////////
// Datenquellen verwalten
bool DatenBasisObjekt::EnumDataSources (ENUMNOKEY *pK)
{
CRing r(GetGeoDBs());
char cbBuffer[_MAX_PATH];

	for (r.First(); r.Valid(); ) {
	GeoDBLock l(r);
	bool fLast = !r.Next();

		TX_ASSERT(NULL != (GeoDB *)l);
		if (!l || !l -> isOpened())
			continue;

		strcpy (cbBuffer, l -> GetDBName());
		strupr (cbBuffer);
		if (!(*(ENUMNOKEYCALLBACK)pK -> eFcn)(cbBuffer, fLast, pK -> ePtr))
			return (LRESULT)false;
	}
	return (LRESULT)true;
}

bool DatenBasisObjekt::EnumDataSourceHandles (ENUMNOKEYLONG *pK)
{
CRing r(GetGeoDBs());

	for (r.First(); r.Valid(); ) {
	GeoDBLock l(r);
	bool fLast = !r.Next();

		TX_ASSERT(NULL != (GeoDB *)l);
		if (!l || !l -> isOpened())
			continue;

		if (!(*(ENUMNOKEYLONGCALLBACK)pK -> eFcn)((LONG)(l -> DBDesc()), fLast, pK -> ePtr))
			return (LRESULT)false;
	}
	return (LRESULT)true;
}

HPROJECT DatenBasisObjekt::GetDataSourceHandle (LPCSTR pcName)
{
CRing r(GetGeoDBs());

	for (r.First(); r.Valid(); r.Next()) {
	GeoDBLock l(r);

		TX_ASSERT(NULL != (GeoDB *)l);
		if (!l || !l -> isOpened())
			continue;
		if (!stricmp (l -> GetDBName(), pcName))
			return l -> DBDesc();
	}
	return NULL;
}

HPROJECT DatenBasisObjekt::GetDataSourceFromShortName (LPCSTR pcName)
{
	if (!strcmp (pcName, "__ActProject__"))
		return HACTPROJECT;		// hack for HACTPROJECT

CRing r(GetGeoDBs());
char cbBuffer[_MAX_PATH];

	for (r.First(); r.Valid(); r.Next()) {
	GeoDBLock l(r);

		TX_ASSERT(NULL != (GeoDB *)l);
		if (!l || !l -> isOpened())
			continue;

		if (SUCCEEDED(l -> GetDataSourceName (cbBuffer, sizeof(cbBuffer))) && 
			!strcmp (cbBuffer, pcName))
		{
			return l -> DBDesc();
		}
	}
	return NULL;
}

HPROJECT DatenBasisObjekt::MakeDataSourceActive (HPROJECT hPr)
{
	TX_ASSERT(HACTPROJECT != hPr);
	if (0 == GetGeoDBs().Count()) 
		return NULL;

int iIndex = GetGeoDBs().FFindItem (hPr);

	TX_ASSERT(-1 != iIndex);

int iOldIndex = GetGeoDBs().FActivateItem (iIndex);

	TX_ASSERT(-1 != iOldIndex);
	return GetGeoDBs().DB(iOldIndex).DBDesc();
}

HRESULT DatenBasisObjekt::GetViewCount (LONG *plCnt)
{
	COM_TRY {
	WTRiASViews Views;

		THROW_FAILED_HRESULT(m_Prj -> get_Views (Views.ppi()));
		THROW_FAILED_HRESULT(Views -> get_Count (plCnt));

	} COM_CATCH;
	return S_OK;
}

HRESULT DatenBasisObjekt::GetClassCount(LONG *plCnt)
{
	_ASSERTE(NULL != plCnt);
	*plCnt = 0L;

LONG lCnt = 0;
CRing r(GetGeoDBs());

	for (r.First(); r.Valid(); r.Next()) {
	GeoDBLock l(r);

		TX_ASSERT(NULL != (GeoDB *)l);
		if (!l || !l -> isOpened())
			continue;

		lCnt += l -> CountClasses();
	}

	*plCnt = lCnt;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Importmode behandeln
BOOL DatenBasisObjekt::HandleImportMode (BOOL fImportMode)
{
	if (fImportMode) {
	// Import soll beginnen
	//
	} else {
	// Import ist abgeschlossen
	CRing r(GetGeoDBs());

		for (r.First(); r.Valid(); r.Next()) {
		GeoDBLock l(r);

			TX_ASSERT(NULL != (GeoDB *)l);
			if (!l || !l -> isOpened() || !l -> isDirty())
				continue;

		// Objekteigenschaften neu einlesen
			l -> ForceReLoad(RELOADDATABASE_Features);
		}
	}
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Objekt sinnvoll ins Bild rücken
bool DatenBasisObjekt::ZoomInToObject (INT_PTR lONr)
{
ObjContainer OC, ocT;

	OC.SetXMin(MAXKOORD);	// nicht mit ctor initialisiert, da dieser min < max gewährleistet
	OC.SetXMax(0);
	OC.SetYMin(MAXKOORD);
	OC.SetYMax(0);

	if (!GetObjContainer (lONr, OC)) 
		return false;
	
	ocT = GetExtend();
	if (OC.HasSignificantSize()) {		// gültiger Container
		if (GetKeyState (VK_CONTROL) >= 0 && !DEX_IsHoldZoomActive())
			OC = OC.InflateCont (200);	// 100% größerer Ausschnitt
		else {
		Ausdehnung A = OC - ocT;

			OC = ocT.ShiftCont (A);
		}
	} else {			// PunktContainer
		if (GetKeyState (VK_CONTROL) >= 0 && !DEX_IsHoldZoomActive())
			ocT = ocT.InflateCont (-60);

	Ausdehnung A = OC - ocT;	// 40% des aktuelle Ausschnitts

		OC = ocT.ShiftCont (A);
	}
	
// mit Projekt-Container abgleichen
long lCont[4];
KoOrd dXMin, dXMax, dYMin, dYMax;

	DEX_GetProjectCont (lCont);
	if (!UnScaleCTF (lCont[0], lCont[2], &dXMin, &dYMin) ||
		!UnScaleCTF (lCont[1], lCont[3], &dXMax, &dYMax))
	{
		return false;
	}

ObjContainer dbOC (dXMin, dXMax, dYMin, dYMax);
KoOrd dX, dY;

	OC &= dbOC;

	if (!ScaleCTF (OC.XMin(), OC.YMin(), &dX, &dY))
		return false;
	lCont[0] = dX;
	lCont[2] = dY;

	if (!ScaleCTF (OC.XMax(), OC.YMax(), &dX, &dY))
		return false;
	lCont[1] = dX;
	lCont[3] = dY;

	DEX_SetActiveSightContainer (lCont);
	DEX_RePaint();

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Liefert aktuellen ObjektBeschreibungsString (wie im Recherchefenster)
char *FormatROString (char *pText, RECHOBJECT &rRO);

bool DatenBasisObjekt::GetObjPropDesc(INT_PTR lONr, LPSTR *ppObjDesc)
{
	if (NULL == ppObjDesc)
		return false;
	*ppObjDesc = NULL;

int iObjType = DEX_GetObjectType(lONr);		// ObjektTyp bestimmen
INT_PTR lIdent = DEX_GetObjIdentEx(lONr);

// wenn ObjProp vorgegeben ist, dann diese nutzen, sonst Voreinstellung
HRESULT hr = S_FALSE;
os_string strActOProp;
char cbBuffer[_MAX_PATH];
ExtensionList &rEL = m_pViewWnd -> GetFrame() -> EL();

	if (S_OK == Idents().GetObjectProperty (lIdent, strActOProp))
		hr = rEL.InvokeActObjProp (lONr, cbBuffer, _MAX_PATH, NULL, strActOProp.c_str());
	else if (NULL != rEL.GetActObjPropName()) 
		hr = rEL.InvokeActObjProp (lONr, cbBuffer, _MAX_PATH, NULL);
	else
		hr = S_FALSE;	// auch keine globale ObjProp --> Objektklasse anzeigen

	if (S_OK == hr && !(g_iHideFlags & ROHideDatasource) && DEX_GetOpenConnectionCount (QDCAllOpen|QDCCountQueryDefs) > 1) {
	HPROJECT hPr = DEX_GetObjectsProject(lIdent);
	char cbDSName[_MAX_PATH];

		TX_ASSERT(HACTCONNECTION != hPr);
		if (NULL != DEX_GetDataSourceShortName (hPr, cbDSName)) {
			strcat (cbBuffer, " (");
			strcat (cbBuffer, cbDSName);
			strcat (cbBuffer, ")");
		}
	}

	if (S_OK != hr) {
	// wenn keine OPF gegeben ist, dann IdentKurzText verwenden
	LPCSTR pcKText = GetKurzText(lIdent, !(g_iHideFlags & ROHideDatasource));

		_ASSERTE(NULL != pcKText);
		cbBuffer[0] = '\0';
		if (NULL != pcKText) 
			strncpy (cbBuffer, pcKText, _MAX_PATH);	// default: IdKurzText
		cbBuffer[_MAX_PATH-1] = '\0';
	}

RECHOBJECT RO;

	INITSTRUCT(RO, RECHOBJECT);
	RO.lONr = lONr;
	RO.lIdent = lIdent;
	RO.lpText = cbBuffer;
	RO.iTextLen = _MAX_PATH-1;
	RO.iOTyp = (short)iObjType;
	RO.iFlags = g_iHideFlags & (ROHideFlags|ROShowHidden);			// voreingestellte Bits setzen
	if (DEXN_QueryRechObject (RO))
		return S_FALSE;				// Objekt hat nicht zu recherchierenden Ident oder jemand hat was dagegen

// angezeigten Eintrag zusammenstellen und zu ListBox hinzufügen
LPSTR pObjProp = (LPSTR)::CoTaskMemAlloc(2*_MAX_PATH);

	if (NULL == pObjProp)
		return false;

	if (FormatROString (pObjProp, RO)) {
		strcat (pObjProp, RO.lpText);
		*ppObjDesc = pObjProp;
	}
	return true;
}
