// Funktionen fuer DatenBasisObjekt --------------------------------------------
// File: DBOBJEKT.CXX

#include "triaspre.hxx"

#if !defined(WIN32)
#include <io.h>
#else
#include <registry.hxx>
#include <fnamestr.h>
#endif
#include <dirisole.h>
#include <xtensnxx.h>
#include <xtensnd.h>
#include "clbmpobj.hxx"

#include "triasres.h"

#if defined(WIN32)
#include <funcs03.h>
#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <relliste.hxx>
#include "strings.h"
#endif

#include "viewtree.hxx"
#include "Schrift.hxx"
#include "relobj.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// globale Daten
extern short GCancelFlag;

extern HPALETTE hPalette;		// AnwendungsFarbPalette
extern HINSTANCE hInstance;

extern bool PrintEFlag;

extern bool LegendeCFlag;
extern bool LegendToRepaint;
extern bool GenerateLegendOnly;

extern char PbdDBDir[_MAX_PATH+1];

extern short VTypToBits (VisType);
extern short OTypToBits (ObjTyp);

// externe Funktionsdeklarationen ---------------------------------------------
Dimension GetDotsPerMM (HDC hDC);
void EXPORTTRIAS SetNotVisible (void *pObj);
bool WriteTextMerkmal (short iTTyp, long lTarget, long lMCode, char *pText, short iFlags = 0);
long GetHeaderMCode (bool fGenerate, uint resID, LPCSTR pView = NULL, 
		    uint uiResKT = 0, uint uiResLT = 0);

///////////////////////////////////////////////////////////////////////////////
// Konstruktor
DatenBasisObjekt :: DatenBasisObjekt (const GeoDB &DB, unsigned int MTyp, pPen pP, pBrush pB)
	: ExtShapeObject (Point (0, 0), Dimension (), pP, pB)
{
	m_fToClose = true;
	m_fPosTextAtBaseLine = false;
	m_fIsFile = true;
	m_fIsOpening = false;
	m_fCompatibility16 = false;
	m_lActScale = 0L;
	m_pViewWnd = NULL;

	ResetIdentScaleMCodes (true);
	m_lObjGuidMCode = 0L;

	_toPaint = PF_NOTDRAWED;
	_MarkerTyp = MTyp;
	_DBOCont = ObjContainer (0, 0, 0, 0);

	ATLTRY(_pGeoDB = new GeoDB (DB));
	if (NULL != _pGeoDB) {
		ATLTRY(_Idents = new CIdTree (*_pGeoDB));
		ATLTRY(_Shapes = new ObjektListe(*_pGeoDB));
	}
	_pCT = NULL;

	_SightMenu = NULL;
	_SightFlag = false;
	m_pViews = NULL;

	_iDrawSem = false;

	m_pBmp15sw = NULL;
	m_pBmp23sw = NULL;
	m_pBmp32sw = NULL;
	m_iBmpCnt = 0;
	m_fNewPnts = false;
	m_pPunktIDs = NULL;
	m_pClsIdents = NULL;
		
	m_lObjCnt = -1L;

	LoadBitmapBars();

	if (!_Idents || !_Shapes || !_pGeoDB) {
		db_error (EC_NOMEMORY, RC_ctDatenBasisObjekt);
		_toPaint = PF_INVALID;
	} else
		_toPaint = PF_NOTDRAWED;

#if defined(WIN32)
	m_pLoadedOC = NULL;

#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
	{
	CCurrentUser resBkColor ("Software\\uve\\TRiAS\\Config");
	DWORD dwColor = 0x00C0C0C0L;

		resBkColor.GetDWORD ("BackGroundColor", dwColor);
		SetBkColor ((Color &)dwColor);
	} 
#if defined(ENABLE_WIN32S_CODE)
	else
#endif // ENABLE_WIN32S_CODE
#endif // WIN32
#if defined(ENABLE_WIN32S_CODE)
		SetBkColor (Color ((ColorVal)192, (ColorVal)192, (ColorVal)192));
#endif // ENABLE_WIN32S_CODE

	m_fToClose = false;
}

DatenBasisObjekt :: DatenBasisObjekt (void)
	: ExtShapeObject (Point (0, 0), Dimension (), NULL, NULL)
{
	m_fToClose = true;
	m_fPosTextAtBaseLine = false;
	m_fIsFile = true;
	m_fIsOpening = false;
	m_fCompatibility16 = false;
	m_lActScale = 0L;
	m_pViewWnd = NULL;
	m_lObjGuidMCode = 0L;

	ResetIdentScaleMCodes (true);

	_toPaint = PF_INVALID;
	_MarkerTyp = 0;
	_DBOCont = ObjContainer (0, 0, 0, 0);

	ATLTRY(_pGeoDB = new GeoDB);
	if (NULL != _pGeoDB) {
		ATLTRY(_Idents = new CIdTree (*_pGeoDB));
		ATLTRY(_Shapes = new ObjektListe(*_pGeoDB));
	}
	_pCT = NULL;
	
	_SightMenu = NULL;
	_SightFlag = false;
	m_pViews = NULL;

	_iDrawSem = false;

	m_pBmp15sw = NULL;
	m_pBmp23sw = NULL;
	m_pBmp32sw = NULL;
	m_iBmpCnt = 0;	
	m_fNewPnts = false;
	m_pPunktIDs = NULL;
	m_pClsIdents = NULL;

	m_lObjCnt = -1L;
	
	if (!_Idents || !_Shapes || !_pGeoDB) 
		db_error (EC_NOMEMORY, RC_ctDatenBasisObjekt);

#if defined(WIN32)
	m_pLoadedOC = NULL;

#if defined(ENABLE_WIN32S_CODE)
	if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
	{
	CCurrentUser resBkColor ("Software\\uve\\TRiAS\\Config");
	DWORD dwColor = 0x00C0C0C0L;

		resBkColor.GetDWORD ("BackGroundColor", dwColor);
		SetBkColor ((Color &)dwColor);
	} 
#if defined(ENABLE_WIN32S_CODE)
	else
#endif // ENABLE_WIN32S_CODE
#endif // WIN32
#if defined(ENABLE_WIN32S_CODE)
		SetBkColor (Color ((ColorVal)192, (ColorVal)192, (ColorVal)192));
#endif // ENABLE_WIN32S_CODE

	m_fToClose = false;		// jetzt kann geöffnet werden
}

#if defined(WIN32)
IrisWind *DatenBasisObjekt::AttachViewWindow (IrisWind *pViewWnd)
{
IrisWind *pOldWnd = m_pViewWnd;

	m_pViewWnd = pViewWnd;
	return pOldWnd;
}
#endif // WIN32

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
void DatenBasisObjekt :: LoadBitmapBars (void) 
{
	if (GetGeoDBVersion() >= VERSION0500000B) {
	// neue DatenBasis
	HeaderEntry rsOldPts (DB(), IDS_USEOLDPOINTSTYLE);

		if (rsOldPts.EntryLong (0) == 1) return;	// alte Punkte
	} else {
	// alte DatenBasis
	HeaderEntry rsNewPts (DB(), IDS_USENEWPOINTSTYLE);

		if (rsNewPts.EntryLong (0) == 0) return;	// alte Punkte
	}

// neue Punktsymbole verwenden
	DELETE (m_pBmp15sw);
	DELETE (m_pBmp23sw);
	DELETE (m_pBmp32sw);

	m_pBmp15sw = CBitmapBar :: CreateInstance (ResID (IDB_BITMAP_15_SW), ResID (IDR_BMPOFFSETS15));
	m_pBmp23sw = CBitmapBar :: CreateInstance (ResID (IDB_BITMAP_20_SW), ResID (IDR_BMPOFFSETS23));
	m_pBmp32sw = CBitmapBar :: CreateInstance (ResID (IDB_BITMAP_32_SW), ResID (IDR_BMPOFFSETS32));

	DELETE (m_pPunktIDs);
	m_pPunktIDs = CMapPunktID :: CreateInstance (ResID (IDR_PUNKTIDTABLE));
	
	if (m_pBmp15sw && m_pBmp23sw && m_pBmp32sw && m_pPunktIDs) {
	Dimension dim = m_pBmp15sw -> GetFullSize();
		
		m_iBmpCnt = short(dim.Width()/dim.Height());	// Anzahl der Punktsymbole
		m_fNewPnts = true;
	}
}	


// Umschließendes Rechteck -----------------------------------------------------
Rectangle EXPORTTRIAS DatenBasisObjekt :: BoundingBox (void) 
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
	if (!_iDrawSem) {
		_iDrawSem = true;				// nur einmal gleichzeitig zeichnen

	HDC hDCs[2];
	
		hDCs[0] = Handle (API_DRAWOBJECT_HDC);
		hDCs[1] = Handle (API_TARGET_HDC);

		SaveDC (hDCs[0]);				// alten DC speichern
		DotsPerMM() = GetDotsPerMM (hDCs[1]);

	// ExposedArea in DB-Koordinaten umrechnen
	Rectangle rcEA = EA();
	ObjContainer ocT = rcEA;
	
		SetExpOC (ocT);					// ExposedArea umrechnen
		EvalMasstab (GetCanvas());		// Masstabskoeffizienten berechnen

#if defined(WIN32)
	// Regions haben in Metafiles nichts zu suchen !?
		if (!PrintEFlag || GetObjectType (hDCs[0]) != OBJ_ENHMETADC)
#endif // WIN32
		{
		// CompoundRegion generieren
		Rectangle *pRc = (dwData != 0) ? (Rectangle *)dwData : &rcEA;
		HRGN hRgn = CreatePaintRegion (hDCs[1], *pRc, ClipRegionONr());

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

		if (!(GCancelFlag & GCFAppClosed)) 	// wenn App nicht geschlossen wurde
			DEXN_PaintTopLayer (hDCs);		// DeckerLayer zeichnen

		if (EC_OKAY == RC)		// ohne 'Abbrechen' und ohne Fehler fertig geworden
			AddLoadedRect (ocT);

	// DC rücksetzen
		if (hPalette)
			SelectPalette (hDCs[0], hOldPalette, false);
		SetPolyFillMode (hDCs[0], oldFillMode);
		SetBkMode (hDCs[0], oldBkMode);

		RestoreDC (hDCs[0], -1);		// ursprünglichen DC wiederherstellen

		_iDrawSem = false;
	}
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
		try {
			m_pLoadedOC = new CLoadedRects();
		} catch (bad_alloc) {
			m_pLoadedOC = NULL;
			return false;
		}
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
static bool FMatchScales (long lActScale, long lUpperScale, long lLowerScale)
{
	if (0 != lUpperScale && lActScale < lUpperScale)
		return false;

	if (0 != lLowerScale && lActScale > lLowerScale)
		return false;

	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Alle Objekte eines Id's einlesen und zeichnen 

ErrCode DatenBasisObjekt::GetGIAll (CIdRefLock &lP, bool fTest, DWORD) 
{
ErrInstall EI_Noon (EC_NOON);
// ErrInstall EI_NoEOK (WC_NOEOK);
ErrCode EC = EC_OKAY;
CIdRef *pP = (CIdRef *)lP;
CIdentifikator *pId = &pP -> rCId();

	if (pId == NULL) return EC_OKAY;		// Ident nicht gefunden

long lIdent = pId -> Id();

// Abfragen, ob eine Erweiterung etwas mit diesem Ident zu tun haben will
DRAWIDENTEX DI;

	INITSTRUCT (DI, DRAWIDENTEX);
	DI.m_lIdent = lIdent;
	DEXN_DrawIdentifikatorEx (DI);
	pId -> DType() = DI.m_lResult & DT_DrawingMask;
//	pId -> DType() = DEXN_DrawIdentifikator (lIdent) & DT_DrawingMask;

// Alle Objekte mit diesem Id holen und zeichnen
short iOTypes = 0;		// ObjektTypen dieses Idents

	if (!pId -> GetOTypesEx (DB(), iOTypes))
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

#if !defined(WIN32)
DWORD dwDelta = 0;
#endif // !WIN32
ExtShapeObjectDCreator DOC (Shapes());
ExtShapeObject *pDBO;
CTable tabONr (Shapes().ObjNumTree());
Rectangle CRc = GetCanvas() -> CanvasRect();
ObjContainer OC;

	OC = CRc;

bool iAllLoaded = pId -> AreAllLoaded();	// TeilFlag merken
short fFlags = GenerateLegendOnly ? DF_Analyze : 0;
CIdentObjects Objs;
long lObjNummer;

	if (!pId -> GetObjectList (Objs) || 0 == Objs.size())
		return WC_NOTFOUND;
	pId -> AllLoaded();						// TeilFlag rücksetzen

	for (CIdentObjects::iterator it = Objs.begin(); it != Objs.end(); ++it) 
	{
	VisInfo *pVI = NULL;

	// nach einlesen einer vorgebbaren Menge von Objekten Baum optimieren
		lObjNummer = *it;
#if !defined(WIN32)
		Shapes().CondOptimize(dwDelta);
#endif // !WIN32
		DEXD_ObjectToDraw (lObjNummer);

	// wenn gefordert, testen, ob Objekt schon geladen ist
		if ((fTest || GetLoadMode()) && tabONr.Find (&lObjNummer)) {
		// Objekt ist bereits geladen, nur zeichnen
		{
		ExtShapeObjectLock LockObj (tabONr);

			if (!LockObj) continue;

		ExtShapeObject *pObj = (ExtShapeObject *)LockObj;
		
			if (!FMatchGeoTyp (pP -> FVisTyp(), pObj -> isTyp())) 
				continue;	// nicht benötigter ObjektTyp
//			if ((pObj -> operator GeoObjekt *()) -> Id() != lIdent)
			if ((*pObj) -> Id() != lIdent)
				continue;	// Objekt ist temporär umklassifiziert

			pObj -> SetCanvas (GetCanvas());	// Fenster auf dem gezeichnet werden soll
//			if (0 == GetActLayer()) {
				if (GenerateLegendOnly && pObj -> isTyp() != OT_TEXT && pObj -> isTyp() != OT_LABEL) {
					pVI = pObj -> SetAttributes (pId, DotsPerMM(), tabONr, VT_Default, fFlags);
					if (pVI && pVI != VI_NotChanged) {
						pVI = pId -> ChangeVisInfo (pVI, pP -> FVisTyp());
						DELETE (pVI);
					}
				} else if ((pVI = pObj -> SetAttributes (pId, DotsPerMM(), tabONr, VT_Default, fFlags)) != NULL) {
				// Typgerecht zeichnen bzw. Textgröße messen für Legende
					if (pVI == VI_OtherType)
						pObj -> TypeDependendDraw (pId, tabONr, DotsPerMM());
					else {
						GetCanvas() -> DrawEx (pObj, (DWORD)this);
						if (pVI != VI_NotChanged) {
							pVI = pId -> ChangeVisInfo (pVI, pP -> FVisTyp());
							DELETE (pVI);
						}
					}
				}
/*			} else {
			// alle weiteren Layer
				GetCanvas() -> DrawEx (pObj, (DWORD)this);
			}
*/		} // unlock ExtShapeObject

		// sonst noch was zu tun ?
			if (GCancelFlag == GCFNormal)
				App :: Exec (ExecWhileEvent);

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

		if (EC_OKAY != DB().GetObjectType (lObjNummer, &iOTyp)) {
			if (!iAllLoaded) 
				pId -> NotAllLoaded();
			continue;			// trotzdem weitermachen
		}

		if (!FMatchGeoTyp (pP -> FVisTyp(), iOTyp)) {
			pId -> NotAllLoaded();	// TeilFlag setzen
			continue;				// nicht benötigter ObjektTyp
		}

		if ((EC = GetGI (lObjNummer, DOC, &pDBO, &OC)) != EC_OKAY) {
			if (EC == WC_NOFIT) {
				pId -> NotAllLoaded();	// TeilFlag setzen
				continue;
			} else if (EC == EC_NOON) {
				continue;			// gelöschtes Objekt
			} else {
				if (!iAllLoaded) 
					pId -> NotAllLoaded();

				TX_ASSERT(EC != EC_OKAY);	// irgend etwas ist faul
				EC = EC_OKAY;		// FehlerCode rücksetzen
				continue;			// trotzdem weitermachen
			}
		} else {
		ObjTyp rgOTyp = pDBO -> isTyp();

#if defined(WIN32)
			Shapes().TimedInsert(DOC, rgOTyp);		// in Baum einfügen, evtl. optimieren
#else
			dwDelta = Shapes().TimedInsert(DOC, rgOTyp);		// in Baum einfügen
#endif // WIN32
//			Idents().IncrementObjectCount (DB(), lIdent, rgOTyp);

// jetzt _vor_ GetGI
//			if (!FMatchGeoTyp (pP -> FVisTyp(), rgOTyp)) 
//				continue;

		// Zeichenattribute dieses GeoObjektes setzen
			pDBO -> SetCanvas (GetCanvas());	// Fenster auf dem gezeichnet werden soll
//			if (0 == GetActLayer()) {
				if (GenerateLegendOnly && rgOTyp != OT_TEXT && rgOTyp != OT_LABEL) {
					pVI = pDBO -> SetAttributes (pId, DotsPerMM(), tabONr, VT_Default, fFlags);
					if (pVI && pVI != VI_NotChanged) {
						pVI = pId -> ChangeVisInfo (pVI, pP -> FVisTyp());
						DELETE (pVI);
					}
				} else if ((pVI = pDBO -> SetAttributes (pId, DotsPerMM(), tabONr, VT_Default, fFlags)) != NULL) {
				// Typgerecht zeichnen
					if (pVI == VI_OtherType)
						pDBO -> TypeDependendDraw (pId, tabONr, DotsPerMM());
					else {
						GetCanvas() -> DrawEx (pDBO, (DWORD)this);
						if (pVI != VI_NotChanged) {
							pVI = pId -> ChangeVisInfo (pVI, pP -> FVisTyp());
							DELETE (pVI);
						}
					}
				} 
/*			} else {
			// alle weiteren Layer zeichnen
				GetCanvas() -> DrawEx (pDBO, (DWORD)this);
			}
*/
		// sonst noch was zu tun ?
			if (GCancelFlag == GCFNormal)
				App :: Exec (ExecWhileEvent);
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

// Alle weiteren Male zeichnen ------------------------------------------------
ErrCode DatenBasisObjekt::NextDraw (DWORD dwData) 
{
CTable tabP(Idents().PrioTree());
CTable tabI(Idents().IdentTree());
bool hasChanged = false;
CTable tabObj (Shapes().ObjIdTree());
CTable tabONr (Shapes().ObjNumTree());
ErrCode RC = WC_RETURN; 
ErrCode MasstabRC = EC_OKAY;
short fFlags = GenerateLegendOnly ? DF_Analyze : 0;

// Alle Idents als nicht gezeichnet markieren, MetaDC setzen
#if defined(WIN32)
bool fMetaDC = (::GetObjectType (Handle (API_DRAWOBJECT_HDC)) == OBJ_ENHMETADC) ? true : false;
#else
bool fMetaDC = (::GetDeviceCaps (Handle (API_DRAWOBJECT_HDC), TECHNOLOGY) == DT_METAFILE) ? true : false;
#endif

	for (tabI.First(); tabI.Valid(); tabI.Next()) {
	CIdentifikatorLock l(tabI);
	
		if (l) {
			l -> SetObjectDrawn (0);
			l -> SetMetaDC (fMetaDC);
		}
	}
		
// Objekte laden und zeichnen -------------------------------------------------
// es werden nur Idents angefaßt, die gezeichnet werden sollen
long lLowerScale = 0;
long lUpperScale = 0;

	for (tabP.First(); tabP.Valid(); tabP.Next()) {
	// für alle Identifikatoren
	CIdRefLock LockP(tabP);

		if (!LockP) continue;

	CIdRef *pP = (CIdRef *)LockP;
	CIdentifikator &rId = pP -> rCId();
	long lIdent = rId.Id();	// lfder Identifikator
	
	// Maßstabsbereich testen (aktuelle Ansicht)
		RetrieveIdentScaleData (NULL, lIdent, pP -> FVisTyp(), &lUpperScale, &lLowerScale);
		if (!FMatchScales (GetActScale(), lUpperScale, lLowerScale)) {
			MasstabRC = WC_RETURN;		// Bereich nicht als vollständig gezeichnet markieren!
			continue;
		}

	// Anzahl der zu zeichnenden Layer berechnen
	double dScale = 1.0;

		if (GetGeoDBVersion() >= VERSION05000004)
			dScale = double(DotsPerMM().Width()) / (100.0*M()) ;
		else
			dScale = double(1.0 / M());

	int iLayers = pP -> GetLayerCount (dScale);
	bool fBreak = false;

		TX_ASSERT(iLayers >= 1);
		for (int iLayer = 1; iLayer <= iLayers; iLayer++) {
		// jetzt soll wirklich gezeichnet werden
			SetActLayer(iLayer-1);

			rId.AddObjectDrawn (VTypToBits (pP -> FVisTyp()));	// dieser Ident wurde behandelt
			DEXD_IdentToHandle (lIdent);
			if (rId.toPaint()) {		// Id soll gezeichnet werden
				DEXD_IdentToDraw (lIdent);
				if (GetLoadMode() || rId.loaded()) {
				// Objekte bereits (teilweise) geladen
					
					if (!rId.AreAllLoaded()) {
					// nicht alle Objekte dieses Id's sind geladen
						DEXD_IdentIsLoadedPart (lIdent);

						if ((RC = GetGIAll (LockP, true, dwData)) == EC_OKAY) {
							if (GetLoadMode())	// evtl. was neues dazugeladen
								rId.Load();		// Flag setzen: alle geladen
						} 
						else if (RC == WC_RETURN) {
						// abgebrochen: alles bisherige wieder löschen
							rId.Load();			// Flag's setzen
							rId.NotAllLoaded();
							
							hasChanged = true;
//							if (iLayer == iLayers) 
//								rId.ResetResources();	// alle Ressourcen freigeben
							fBreak = true;
							break;		// abbrechen
						}
						else if (RC != WC_NOTFOUND) {
						// Fehler
//							if (iLayer == iLayers) 
//								rId.ResetResources();	// alle Ressourcen freigeben
							fBreak = true;
							break;
						}
						hasChanged = true;
					} else {
					// Alle Objekte sind geladen
						DEXD_IdentIsLoadedFull (lIdent);
						
						for (tabObj.FindFirst(&lIdent); 
							 tabObj.Valid(); tabObj.FindNext(&lIdent)) 
						{
						// für alle Objekte mit diesem Identifikator
						ExtShapeObjectLock LockObj(tabObj);

							if (!LockObj) continue;

						ExtShapeObject *pObj = (ExtShapeObject *)LockObj;
						VisInfo *pVI;
						
							DEXD_ObjectToDraw (pObj -> ObjNr());
							if (!FMatchGeoTyp (pP -> FVisTyp(), pObj -> isTyp()))
								continue;

							pObj -> SetCanvas (GetCanvas());	// Fenster auf dem gezeichnet werden soll
//							if (0 == iLayer) {
								if (GenerateLegendOnly && (pObj -> isTyp() != OT_TEXT && pObj -> isTyp() != OT_LABEL)) {
									pVI = pObj -> SetAttributes (&rId, DotsPerMM(), tabONr, VT_Default, fFlags);
									if (pVI && pVI != VI_NotChanged) {
										pVI = rId.ChangeVisInfo (pVI, pP -> FVisTyp());
										DELETE (pVI);
									}
								} else if ((pVI = pObj -> SetAttributes (&rId, DotsPerMM(), tabONr, VT_Default, fFlags)) != NULL) {
								// Typgerecht zeichnen
									if (pVI == VI_OtherType)
										pObj -> TypeDependendDraw (&rId, tabONr, DotsPerMM());
									else {
										GetCanvas() -> DrawEx (pObj, (DWORD)this);
										if (pVI != VI_NotChanged) {
											pVI = rId.ChangeVisInfo (pVI, pP -> FVisTyp());
											DELETE (pVI);
										}
									}
								}
/*							} else {
							// alle weiteren Layer einfach nur zeichnen
								GetCanvas() -> DrawEx (pObj, (DWORD)this);
							}
*/
						// sonst noch was zu tun ?
							if (GCancelFlag == GCFNormal)
								App :: Exec(ExecWhileEvent);

							if (GCancelFlag != GCFNormal || GetAsyncKeyState (VK_ESCAPE)) {	
							// abbrechen
//								if (iLayer == iLayers) 
//									rId.ResetResources();	// alle Ressourcen freigeben
								RC = WC_RETURN;
								fBreak = true;
								break;
							}
						}
					}
				} else {
				// erst laden, dann zeichnen
					DEXD_IdentIsNotLoaded (lIdent);
					if ((RC = GetGIAll (LockP, false, dwData)) == EC_OKAY) {
						rId.Load();		// Flag setzen
					} else if (RC == WC_RETURN) {
						rId.Load();		// Flag's setzen
						rId.NotAllLoaded();
						
						hasChanged = true;
//						if (iLayer == iLayers) 
//							rId.ResetResources();	// alle Ressourcen freigeben
						fBreak = true;
						break;			// abbrechen
					} else if (RC != WC_NOTFOUND) {
					// Fehler
//						if (iLayer == iLayers) 
//							rId.ResetResources();	// alle Ressourcen freigeben
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

		if (GCancelFlag == GCFNormal)
			App :: Exec(ExecWhileEvent);	// sonst noch was zu tun ?

		if (GCancelFlag != GCFNormal || GetAsyncKeyState (VK_ESCAPE)) {
			RC = WC_RETURN;
			break;		// abbrechen
		}
	}
	
// alle nicht angefaßten Idents prüfen, ob was rausgeworfen werden muß
	for (tabI.First(); tabI.Valid(); tabI.Next()) {
	CIdentifikatorLock l(tabI);
	long lIdent = l -> Id();
	short fDrawn = l -> toPaint();	// GetObjectDrawn();
	
	// Id soll nicht gezeichnet werden
#if defined(_DEBUG)
		if (~fDrawn & l -> GetOTypes())
			DEXD_IdentNotToDraw (lIdent);
#endif // WIN32
		if (l -> loaded()) {
		// aus Speicher löschen, nicht zeichnen
			if (DeleteAllObjs (lIdent, ~fDrawn, tabObj, tabONr)) {
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
		if (GCancelFlag == GCFNormal)
			App :: Exec(ExecWhileEvent);	// sonst noch was zu tun ?

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

	if (EC_OKAY == RC && WC_RETURN == MasstabRC)
		RC = WC_RETURN;		// Masstabs-Besonderheiten beachten
	return RC;
}


bool DatenBasisObjekt :: DeleteTempIdents (void)
{
CTable tabP(Idents().PrioTree());
CTable tabObj (Shapes().ObjIdTree());
CTable tabONr (Shapes().ObjNumTree());

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
		}
		if (fToDelete && lIdent != -1) {
			DeleteAllObjs (lIdent, TPAll, tabObj, tabONr);
			tabP.Delete();
		} else
			tabP.Next();
	}

return true;
}


bool DatenBasisObjekt :: DeleteAllObjs (long lIdent, short fToDelete, 
					CTable &tabObj, CTable &tabONr)
{
bool hasChanged = false;		

	for (tabObj.FindFirst (&lIdent); tabObj.Valid(); ) {
	// für alle Objekte mit diesem Identifikator
	long lONr = -1L;

		{	// Objektnummer holen
		ExtShapeObjectLock l(tabObj);

			if (!l) break;	// Fehler
			if (l -> Id() != lIdent) 
				break;	// fertig mit diesem ID
//			if (l -> Status() == ExtShapeObject :: OS_Temp) {
//				Insist = true;
//				break;
//			}
			if (OTypToBits (l -> isTyp()) & fToDelete)
				lONr = l -> ObjNr();	// Objekt rauslöschen
		}

	// löschen, erst nur Baum, dann Baum mit Objekt
		if (lONr != -1L && tabONr.Find (&lONr)) {
			tabONr.Delete();
			tabObj.Delete();
			hasChanged = true;
		} else
			tabObj.Next();
	}

return hasChanged;
}


// DBOContainer setzen (projektionsspezifisch)
void DatenBasisObjekt :: SetExtend (Window *pW, ObjContainer &R, Point &AspectR) 
{
ObjContainer OC = R;    // temporäre Kopie

//	(*_Prj)(&OC.XMin(), &OC.YMin());
//	(*_Prj)(&OC.XMax(), &OC.YMax());
	Scale (pW, _DBOCont = OC, AspectR);  // Bildausschnitt skalieren
}


PaintFlag DatenBasisObjekt :: SetPaintFlag (PaintFlag newFlag) 
{
register PaintFlag oldFlag = _toPaint;

	_toPaint = newFlag;

return oldFlag;
}

// alle Identifikatoren aus der DB lesen und in IdTree speichern --------------
extern "C" {

bool WINAPI FillOneIdent (long lIdent, bool, void *pData)
{
// ID in Tree einspeichern
VisInfo *pVI[4];

	pVI[0] = pVI[1] = pVI[2] = pVI[3] = NULL;
//	MakeCompleteNewVisInfo ((VisInfo **)pVI, TPAll);

return ((CIdTree *)pData) -> AddIdent (lIdent, pVI, 0, hPalette);
}

}

ErrCode DatenBasisObjekt :: FillIdents (void) 
{
// wenn Idents gefüllt ist, dann wieder raus
	if (Idents().IdentTree().Count() > 0) return EC_OKAY;

// alle Identifikatoren behandeln
bool iResult = DB().EnumIdents ((ENUMNOKEYLONGPROC)FillOneIdent, &Idents());

// beide Bäume optimieren
	Idents().IdentTree().Optimize();
	Idents().PrioTree().Optimize();
	DEXD_IdentTreeOptimized();

return iResult ? EC_OKAY : EC_NOMEMORY;
}

// Destruktor -----------------------------------------------------------------
DatenBasisObjekt :: ~DatenBasisObjekt (void) 
{
	ResetBase ();		// ExtShapeObject zurücksetzen

	_SightMenu = NULL;
	DELETE (_Idents);
	DELETE (_Shapes);

	DELETE (_pGeoDB);

	DELETE (m_pViews);
	m_pbdDB.EveryDelete();
	
	DELETE (m_pBmp15sw);
	DELETE (m_pBmp23sw);
	DELETE (m_pBmp32sw);
	
	DELETE (m_pPunktIDs);
	DeleteClsIdentMap();

#if defined(WIN32)
	ResetLoadedRects();
	DELETE(m_pLoadedOC);
#endif // WIN32
}

void DatenBasisObjekt :: EveryDelete (void) 
{
	Shapes().EveryDelete ();
	Idents().AllDelete ();
	_toPaint = PF_NOTDRAWED;
	m_pbdDB.EveryDelete();
}

void DatenBasisObjekt :: InitPbd (char *pDir, bool fFlag)
{
	PbdDB().InitPBD (DB(), pDir, fFlag);
}


ErrCode DatenBasisObjekt :: CloseDB (bool fCommit)
{		
// zugehörige PBD schließen
ErrCode RC;

	if (PbdDB().isOpened()) {
		PbdDB().ReleasePBDTempTree();
		DBASSERT (PbdDB().Close (fCommit));
	}

// Datenbasis schließen
	if (DB().isOpened()) {
	string str = DB().GetDBName();
	bool fDelete = DB().GetTempMode();
	string strT (_MAX_PATH, default_size);
	
		DB().GetTempDBName ((char *)strT.c_str());
		strT.adjustlen();

		DBASSERT (DB().Close(fCommit));

		DEXN_isClosedProject(str.c_str());
//		toClose (false);	// jetzt bereits geschlossen

		if (fDelete) 
#if defined(WIN32)
			DeleteFile (strT.c_str());
#else
			_unlink (strT.c_str());
#endif // WIN32
	}
	
return EC_OKAY;
}

// Modifikation eines Identifikators in der GeoDB und im Speicher -------------
bool DatenBasisObjekt :: ModIdent (long lONr, long newId, long oldId, short iMode) 
{
	if (DEXN_IdentToModify (lONr))
		return false;		// jemand hat was dagegen

CActDB ActDB (DB());

	if (!IsValidIdent(oldId))	// alten Ident besorgen
		oldId = RetrieveIdent (lONr);

	if (!(iMode & MODIDENT_TEMP) && modid (DB().DBDesc(), lONr, newId) != EC_OKAY) 
		return false;

// ist das erste Objekt mit diesem Ident
	{
	CTable t(Idents().IdentTree());
	short aniMode = 0;

		if (iMode & MODIDENT_TEMP) aniMode |= ANI_Temp;
		if (iMode & MODIDENT_ADDTOVIEW) aniMode |= ANI_AddToView;
		if (t.Find (&newId)) {
			Idents().AddNewIdent (newId, hPalette,
				aniMode, (iMode & MODIDENT_TYP), 
				newId);
		} else {
			Idents().AddNewIdent (newId, hPalette,
				aniMode, (iMode & MODIDENT_TYP), 
				oldId);
		}
		Idents().ModifyIdent (DB(), lONr, newId, oldId);
	}

// Identifikator auch im Speicher ändern 
	if (!Shapes().ModIdent (lONr, oldId, newId)) {
	// Objekt laden, da es noch nicht im Speicher ist 
		{
		ExtShapeObjectDCreator DOC (Shapes());
		ExtShapeObject *pDBO;

			if (GetGI (lONr, DOC, &pDBO, NULL) != EC_OKAY) 
				return false;
		}

	// hier wurde das bereits in der GeoDB umklassifizierte Objekt geladen		
//	// jetzt umklassifizieren
//		if (!Shapes().ModIdent (lONr, oldId, newId))
//			return false;		// nun ist aber genug
	}

// war das letzte Objekt mit diesem Ident
	{
	CTable t(Shapes().ObjIdTree());

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
VisInfo *DatenBasisObjekt :: PresetAttributes (Window *pCanvas, long ONr)
{
CTable tabON (Shapes().ObjNumTree());
CTable tabId (Idents().IdentTree());
long Ident = RetrieveIdent (ONr);

	SetCanvas (pCanvas);
	
	if (tabON.Find (&ONr) && tabId.Find (&Ident)) {
	ExtShapeObjectLock lON(tabON);
	CIdentifikatorLock lId(tabId);

		if (lON && lId) {
		Window *pOldCanvas = lON -> GetCanvas();

			lON -> SetCanvas (pCanvas);
		
		VisInfo *pVI = lON -> SetAttributes (lId, DotsPerMM(), tabON, 
			       			     VT_Default, DF_Blinking);
			lON -> SetCanvas (pOldCanvas);
			return pVI;
		}
	}
	
	return NULL;
}

bool DatenBasisObjekt :: ResetAttributes (long ONr, VisInfo *pVI)
{
CTable tabON (Shapes().ObjNumTree());
CTable tabId (Idents().IdentTree());
long Ident = RetrieveIdent (ONr);

	if (tabON.Find (&ONr) && tabId.Find (&Ident)) {
	ExtShapeObjectLock lON(tabON);
	CIdentifikatorLock lId (tabId);

		if (lON && lId) {
			lON -> ResetAttributes ();
			lId -> ResetResources();

			if (pVI && pVI != VI_NotChanged && pVI != VI_OtherType) {
				pVI = lId -> ChangeVisInfo (pVI);
				DELETE (pVI);
			}
			return true;
		}
	}
	return false;
}

void DatenBasisObjekt :: EvalMasstab (Window *pW, double *pMasstab) 
{
	M() = 1.0;	// für alle Fälle

// wenn Rechteck entartet ist, dann nichts ändern
Rectangle rcEA = EA();

	if (rcEA.Right() == rcEA.Left()) return;

Rectangle CRc = pW -> CanvasRect();

	if (CRc.Left() == CRc.Right()) return;		// Icon

double MSt = -1.0;

	{
	// Fehlermeldung unterdrücken und Defaultwerte verwenden
	ErrInstall EI (WC_NOTFOUND);

	// zuerst versuchen, aus der Sicht den aktuellen BMaßstab zu bekommen
		if (DB().GetDBVersion() >= VERSION05000008) {
		// nur ab Version 05.00.08
		long lMCode = HeaderEntry (DB(), IDS_HDRSICHTBMASSTAB).EntryLong(0);
		char ActSight[SIGHTMENUITEM+1];

			GetActiveSightName (ActSight, SIGHTMENUITEM+1);
			if (lMCode != 0 && *ActSight != '\0') {
			char *pMText = NULL;
			CActDB ActDB (DB());		// #ActDB
			Sicht S (DB(), ActSight);

				S.GetMiText (lMCode, &pMText);
				if (pMText != NULL) {
					MSt = (long)atol (pMText);
					if (MSt == 0.0) MSt = -1.0;
				}
				DELETE (pMText);
			}			
		}
	// ansonsten Bezugsmasstab aus DB-Header lesen
		if (MSt == -1.0)
			MSt = HeaderEntry (DB(), IDS_MASSTAB).EntryDouble (-1.0);

	} // Fehlermeldung wieder in alten Zustand schalten

// Koordinaten in DB-Koordinaten umsetzen
Point ptT1 = CRc.UpperLeft();
Point ptT2 = CRc.LowerRight();
Punkt LO = DCtoOC (/*EA()*/ptT1);       // Device --> Objekt
Punkt RU = DCtoOC (/*EA()*/ptT2);

// DatenBasis-Skalierung rausrechnen
double XLO, XRU, YLO, YRU;

	pCT() -> UnScale (LO, &XLO, &YLO);
	pCT() -> UnScale (RU, &XRU, &YRU);

DoublePair P1 (XLO, YLO);
DoublePair P2 (XRU, YLO);	// über X-Koordinate berechnen
double dX = 1.0;

	if (pCT() -> hasDistEx()) {
	double dY = 1.0;

		pCT() -> CoordTransDistanceEx (&P1, &P2, dX, dY);
	} else
		dX = pCT() -> CoordTransDistance (&P1, &P2);

double tmpM = ((dX * 1000.0 * DotsPerMM().Width()) / ((double)(CRc.Right()-CRc.Left())));

// wenn kein Bezugsmaßstab gegeben ist, dann aktuelle Skalierung gleich 1.0 setzen
// ansonsten gleich dem Verhältnis von aktuellem Maßstab (tmpM) und BezugsMaßstab
	if (MSt == -1.0 || MSt == 0.0) {
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

// Löschen aller oder aller nicht mehr geladener Identifikatoren --------------
bool DatenBasisObjekt :: RemoveTempIdents (void) 
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
ErrCode DatenBasisObjekt :: ReloadAllObjects (long lIdent)
{
CTable tabObj (Shapes().ObjIdTree());
CTable tabONr (Shapes().ObjNumTree());
ExtShapeObjectDCreator DOC (Shapes());
ExtShapeObject *pDBO = NULL;
ErrCode EC = EC_OKAY;

	for (tabObj.FindFirst (&lIdent); 
	     tabObj.Valid(); tabObj.FindNext(&lIdent)) 
	{
	// alle Objekte mit diesem Identifikator neu laden
	long lONr = -1L;

		{	// Objektnummer holen
		ExtShapeObjectLock l(tabObj);

			lONr = l -> ObjNr();
		}

	// löschen, erst nur Baum, dann Baum mit Objekt
		if (lONr != -1L && tabONr.Find (&lONr)) {
			tabONr.Delete();
			tabObj.Delete();
		}

	// frisch besorgen
		if ((EC = GetGI (lONr, DOC, &pDBO, NULL)) == EC_OKAY || 
		    EC == WC_NOFIT)
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
bool DatenBasisObjekt :: ReScale (Window *pW)
{
	if (NULL != _pCT) {
		if (!_pCT -> Reload (true))
			return true;	// muß nicht neu geladen laden

		DELETE(_pCT);
	}

// neu laden
	TX_ASSERT(NULL == _pCT);

	_pCT = new CoordTrans (pW, DB());
	if (NULL == _pCT) {
			db_error (EC_NOMEMORY, RC_DBOReScale);
			return false;
	}

return true;
}

bool DatenBasisObjekt :: ReReadIdents (void) 
{
// Zahlenbasis der Idents holen
	{
	HeaderEntry IdBase (DB(), IDS_IDENTBASE);
	int iDefault = isComFile() ? 16 : 10;
	short sBase = (short)IdBase.EntryLong (iDefault);

		if (sBase != 10 && sBase != 16) 
			sBase = iDefault;
		SetIdBase (sBase);
	}

// Zahlenbasis der MCodes holen
	{
	HeaderEntry MkBase (DB(), IDS_MCODEBASE);
	short sBase = (short)MkBase.EntryLong (10);

		if (sBase != 10 && sBase != 16) sBase = 10;
		SetMkBase (sBase);
	}

	DELETE (_Idents);		// IdentTree löschen
	_Idents = new CIdTree (DB());	// und neu anlegen
	if (_Idents == NULL) {
		db_error (EC_NOMEMORY, RC_DBOReReadIdents);
		return false;
	}
	FillIdents();			// Idents neu einlesen

return true;
}

// Funktionen, die aktuell gezeichneten Ausschnitt liefern --------------------
// ACHTUNG: nur gültig während einer ZeichenAktion 
bool DatenBasisObjekt :: QueryExposedOC (ObjContainer *pOC)
{
	if (!_iDrawSem || !pOC) 
		return false; 	// es wird nicht gezeichnet

	*pOC = ExpOC();

return true;
}

bool DatenBasisObjekt :: QueryExposedArea (Rectangle *pRc)
{
	if (!_iDrawSem || !pRc) 
		return false; 	// es wird nicht gezeichnet

	*pRc = EA();

return true;
}

bool DatenBasisObjekt :: isComFile (void)
{
LPSTORAGE pIStorage = NULL;

	if (DB().GetProjectStorage (&pIStorage)) {
		pIStorage -> Release();
		return true;
	}

return false;
}

#if defined(WIN32)
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
string strSrcIni = MakeProfileName (rstrSrc);
string strDestIni = MakeProfileName (pcDest);

// INI-Datei kopieren
bool fResult = ::CopyFile (strSrcIni.c_str(), strDestIni.c_str(), false);

// evtl. Schreibschutz aufheben
DWORD dwAttr = ::GetFileAttributes (strDestIni.c_str());

	if (0xFFFFFFFF == dwAttr)
		return false;		// Fehler aufgetreten

	if (dwAttr & FILE_ATTRIBUTE_READONLY) {
		dwAttr &= ~FILE_ATTRIBUTE_READONLY;
		::SetFileAttributes (strDestIni.c_str(), dwAttr);
	}
	return fResult;
}

// Wegspeichern und Namen auf neue Datei setzen -------------------------------
bool DatenBasisObjekt :: SaveAsGeoDB (LPCSTR pcName)
{
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

// alles ok	
return true;
}

// Wegspeichern und alten Namen beibehalten -----------------------------------
bool DatenBasisObjekt :: ExportAsGeoDB (LPCSTR pcName)
{
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

// alles ok	
return true;
}
#endif // WIN32

// Abfragen der HauptFarbe eines Objektes -------------------------------------
static Color ConvertPalette (Color C, HPALETTE hPal)
{
	if (hPal && C.Reserved() != 0) {
		GetPaletteEntries (hPal, C.Red(), 1, (PALETTEENTRY *)&C);
		C.Reserved() = 0;
	}

return C;
}

Color DatenBasisObjekt :: GetObjectColor (long lONr)
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
	DELETE(dObj.pNewVI);

return C;
}

// Liefert Objekttypen eines Idents in der aktuellen Sicht --------------------
short DatenBasisObjekt :: GetActIdentObjTypes (LONG lIdent)
{
CTable tabI(Idents().IdentTree());

	if (tabI.Find (&lIdent)) {
	CIdentifikatorLock l(tabI);

		TX_ASSERT(NULL != (CIdentifikator *)l);
		if (!l) return 0;

	// ggf. aus GeoDB lesen
		return (l -> toPaint() & l -> GetOTypes(DB())) | (l -> hasKO() ? OTKO : 0);
	}

return 0;		// nicht in dieser Sicht vertreten
}


#if defined(WIN32)
// alle Merkmale eines Objektes löschen (mit Undo/Redo) -----------------------
bool DatenBasisObjekt :: DeleteFeatures (LONG lONr)
{
	TX_ASSERT(IsValidONr(DB().DBDesc(), lONr));

CActDB ActDB (DB());
MerkmalsListe ML (&DB(), &PbdDB(), lONr, TT_Objekt); //, false);
CTable t(ML);

	for (t.First(); t.Valid(); t.Next()) {
	PBD_MerkmalLock l(t);

	// keine SystemMerkmale behandeln (das sollen die tun, die sie erzeugt haben
		TX_ASSERT(NULL != (PBD_Merkmal *)l);

		if (l -> isSystem()) continue;

	// Merkmal löschen
	LPUNDOREDOOBJECTFEATURE pIUndo = NULL;
	HRESULT hr = UndoCreateInstance (IID_IUndoRedoObjectFeature,
					 (LPVOID *)&pIUndo);
//	HRESULT hr = CoCreateInstance (CLSID_UndoRedoObject, NULL,
//			CLSCTX_INPROC_SERVER, IID_IUndoRedoObjectFeature,
//			(LPVOID *)&pIUndo);

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
}


// alle Relationen die ein Objekt besitzt auflösen (mit Undo/Redo) ------------
bool DatenBasisObjekt :: DeleteRelations (LONG lONr)
{
	TX_ASSERT(IsValidONr(DB().DBDesc(), lONr));

CActDB ActDB (DB());
ObjRelFeld RelC;        // RCodeInfo für ein Objekt
ErrInstall EI (WC_NOTFOUND);
// alle Relationen

	if (DB().RelInfo (lONr, RelC) != EC_OKAY)
		return false;

CRing r(RelC);

	for (r.First(); r.Valid(); r.Next()) {
	ObjRelNummerLock l(r);

		TX_ASSERT(NULL != (ObjRelNummer *)l);

	// Relation auflösen
		if (DelRelation (DB().DBDesc(), lONr, l -> _ON, l -> RelCode(), l -> RelTyp()) == EC_OKAY) {
		// Undo/Redo vorbereiten
		LPUNDOREDODELETEOBJECTRELATION pIUndo = NULL;
		HRESULT hr = UndoCreateInstance (IID_IUndoRedoDeleteObjectRelation,
						 (LPVOID *)&pIUndo);
//		HRESULT hr = CoCreateInstance (CLSID_UndoRedoObject, NULL,
//				CLSCTX_INPROC_SERVER, IID_IUndoRedoDeleteObjectRelation,
//				(LPVOID *)&pIUndo);

			if (SUCCEEDED(hr) && 
			    pIUndo -> Init (lONr, l -> _ON, l -> RelCode(), l -> RelTyp()) == NOERROR) 
			{
				DEX_AddUndoRedo (pIUndo);
			}
			if (pIUndo) pIUndo -> Release();
		}
	}

return true;
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
	if (lZoom <= 0) return false;

// Koordinaten in DB-Koordinaten umsetzen
Punkt PtMin = DCtoOC (rRc.Left(), rRc.Bottom());       // Device --> Objekt
Punkt PtMax = DCtoOC (rRc.Right(), rRc.Top());
double dXMin, dXMax, dYMin, dYMax;
	
// Koordinaten transformieren (incl. rausrechnen der internen Skalierung)
	pCT() -> UnScale (PtMin, &dXMin, &dYMin);
	pCT() -> UnScale (PtMax, &dXMax, &dYMax);

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
	DP2 = DoublePair (dXDelta/2, dYDelta/2);
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

	pCT() -> Scale (DP1.X(), DP1.Y(), &rOC.XMin(), &rOC.YMin());
	pCT() -> Scale (DP2.X(), DP2.Y(), &rOC.XMax(), &rOC.YMax());

// Korrektur des neues Ausschnittes (kippen)
	CondSwap (rOC.XMin(), rOC.XMax());
	CondSwap (rOC.YMin(), rOC.YMax());

	return true;
}

#endif // WIN32

long DatenBasisObjekt::GetClipRegionONr (LPCSTR pcView)
{
long lONr = 0L;

	if (NULL == pcView) {
	// aktuelle Ansicht verwenden
	char cbBuffer[MAXVIEWNAMESIZE+1];

		if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer)-1))
			return 0L;		// Fehler oder keine aktuelle Ansicht

	Sicht View (DB(), cbBuffer);

		lONr = View.GetObjRgn();	// ClippingObjekt
	} else {
	Sicht View (DB(), pcView);

		lONr = View.GetObjRgn();	// ClippingObjekt
	}

	if (-1L == lONr)
		lONr = 0L;		// kein Objekt gegeben

return lONr;
}

bool DatenBasisObjekt::SetClipRegionONr (CLIPOBJECTSET *pCOS)
{
long lONr = pCOS -> m_lONr;
long lResult = 0L;

	if (0 == lONr) lONr = -1L;		// ClipObjekt löschen

char cbBuffer[MAXVIEWNAMESIZE+1];
bool fNoActView = false;

	if (!GetActiveSightName (cbBuffer, sizeof(cbBuffer)-1)) {
	// Fehler oder keine aktuelle Ansicht
		cbBuffer[0] = '\0';
		fNoActView = true;
	}

	if (NULL == pCOS -> m_pcView) {
	// aktuelle Ansicht verwenden
		if (fNoActView) return 0L;

	Sicht View (DB(), cbBuffer);

		lResult = View.SetObjRgn(lONr);	// ClippingObjekt
		ClipRegionONr() = lONr;			// fürs Zeichnen setzen
	} else {
	Sicht View (DB(), pCOS -> m_pcView);

		lResult = View.SetObjRgn(lONr);	// ClippingObjekt
		
		if (!fNoActView && !strcmp(pCOS -> m_pcView, cbBuffer))	// aktuelle Ansicht
			ClipRegionONr() = lONr;			// fürs Zeichnen setzen
	}

// dummerweise ist lResult entweder ein ErrCode oder 
// eine Objektnummer (>= -1)
	return (lResult >= -1L) ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
// Objektanzahl liefern
LONG DatenBasisObjekt::CountObjects (void)
{
	if (-1L == m_lObjCnt) 
		m_lObjCnt = DB().CountObjects();
	return m_lObjCnt;
}

LONG DatenBasisObjekt::GetIdentObjectCount (IDENTOBJECTCOUNT *pData)
{
LONG lCnt = 0;

	if (OTPunkt & pData -> iOTypes)
		lCnt += Idents().GetObjectCount (pData -> ulIdent, OT_PUNKT);
	if (OTLinie & pData -> iOTypes)
		lCnt += Idents().GetObjectCount (pData -> ulIdent, OT_KANTE);
	if (OTFlaeche & pData -> iOTypes)
		lCnt += Idents().GetObjectCount (pData -> ulIdent, OT_FLAECHE);
	if (OTText & pData -> iOTypes)
		lCnt += Idents().GetObjectCount (pData -> ulIdent, OT_TEXT);
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

		pData -> iPriority = pVI -> Priority();
		delete pVI;
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
CTable t(Shapes().ObjNumTree());

	if (!t.Find (&lONr)) return false;

ExtShapeObjectLock l(t);

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
				pWnd -> DrawEx (pPO, (DWORD)this);
				pPO -> ChangeColor (&oldColor);
			}
			break;

		case OT_LABEL:
		case OT_TEXT:	// SchriftObjekt (immer ohne Rahmen)
			{
			SchriftObjekt *pSO = (SchriftObjekt *)pESO;
			short oldFrameMode = pSO -> ChangeFrame (0);

				oldColor = pSO -> ChangeColor (&ActC);
				pWnd -> DrawEx (pSO, (DWORD)this);
				pSO -> ChangeColor (&oldColor);
				pSO -> ChangeFrame (oldFrameMode);
			}
			break;

		case OT_KO:	// KomplexObjekt
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

				pWnd -> DrawEx (pESO, (DWORD)this);
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
	long lAssocON = labs (AssociatedObjekt (DB().DBDesc(), lONr));

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
CTable t(Shapes().ObjNumTree());

	if (!t.Find (&lONr)) 
		return false;	// unbekanntes Objekt

ExtShapeObjectLock l(t);

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
			pWnd -> DrawEx (pESO, (DWORD)this);
			break;

		case OT_LABEL:
		case OT_TEXT:
			{
			SchriftObjekt *pSO = (SchriftObjekt *)pESO;
			short oldFrameMode = pSO -> ChangeFrame (0);

				pWnd -> DrawEx (pSO, (DWORD)this);
				pSO -> ChangeFrame (oldFrameMode);
			}
			break;
			
		case OT_KO:
			{
			RelationsObjekt *pRO = (RelationsObjekt *)pESO;
			ObjektListeIterator KOI (pRO -> KO().OL());
			long lDepONr = KOI.FirstONr();

				while (lDepONr != -1L) {
					DeActivateObj (pWnd, lDepONr, false);	// immer nur eine Etage tief gehen
					lDepONr = KOI.NextONr();
				}
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
			
				pWnd -> DrawEx (pESO, (DWORD)this);	// zeichnen
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
	long lAssocON = labs(AssociatedObjekt (DB().DBDesc(), lONr));

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
	if (VERSION0500000E <= DB().GetDBVersion()) {
		return DB().GetObjectGUID (pGuid -> lONr, &pGuid -> guid);
	} else {
		if (0L == m_lObjGuidMCode)
			m_lObjGuidMCode = GetHeaderMCode (false, IDS_OBJECTGUIDHDR);
		if (-1L == m_lObjGuidMCode) 
			return E_FAIL;

		return DB().GetObjectGUIDFeature (pGuid -> lONr, m_lObjGuidMCode, &pGuid -> guid);
	}
}

HRESULT DatenBasisObjekt::FindObjectFromGuid (OBJECTGUID *pGuid)
{
	if (VERSION0500000E <= DB().GetDBVersion()) {
		return DB().FindObjectFromGUID (pGuid -> guid, &pGuid -> lONr);
	} else {
		if (0L == m_lObjGuidMCode)
			m_lObjGuidMCode = GetHeaderMCode (false, IDS_OBJECTGUIDHDR);
		if (-1L == m_lObjGuidMCode) 
			return E_FAIL;

		return DB().FindObjectFromGUIDFeature (pGuid -> guid, m_lObjGuidMCode, &pGuid -> lONr);
	}
}

HRESULT DatenBasisObjekt::SetObjectGuid (OBJECTGUID *pGuid)
{
HRESULT hr = S_OK;

	if (VERSION0500000E <= DB().GetDBVersion()) {
		hr = DB().SetObjectGUID (pGuid -> lONr, pGuid -> guid);
	} else {
		if (0L == m_lObjGuidMCode)
			m_lObjGuidMCode = GetHeaderMCode (true, IDS_OBJECTGUIDHDR, NULL, 
								IDS_OBJECTGUIDMCODE, IDS_OBJECTGUIDMCODE);
		if (-1L == m_lObjGuidMCode) 
			return E_FAIL;

		hr = DB().SetObjectGUIDFeature (pGuid -> lONr, pGuid -> guid, m_lObjGuidMCode);
	}

	if (HRESULT_FROM_ERRCODE(WC_DUPLICATE) == hr)
		hr = FindObjectFromGuid (pGuid);
	
	return hr;
}

