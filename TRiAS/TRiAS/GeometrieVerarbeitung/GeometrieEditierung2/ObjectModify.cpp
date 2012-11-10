// Definitionen: Geometrie existierender Objekte modifizieren
// File: ObjectModify.cpp
// W. Mörtl


#include "GeoEditP.h"

#include <defattr.h>		// StandardAttribute für Punkte, Linien etc. (DEF_SIZE_PUNKT_X, ...)
#include <hdrentrx.hxx>		// HeaderEntryX
#include <registrx.hxx>		// CCurrentUser

#include "strecke.hxx"

#include "ObjectModify.h"



#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// externe Variable
extern ResourceFile* pRF;



///////////////////////////////////////////////////////////////////////////////////////////////
// statische globale Variable
static void AddMenuOffset (HMENU hMenu, int iOffset);



///////////////////////////////////////////////////////////////////////////////////////////////
// die aktivierten (blinkenden) Objekte aller Recherchefenster durchgehen
BOOL _GEOEDIT_EXPORT FAR PASCAL AktivierteObjekte (LONG hWnd, BOOL, void* pvAktObjs)
{
// Objektnummer des aktivierten Objektes des hWnd-Recherchefensters geben lassen
long lONr = DEX_GetActiveObject (hWnd);

	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

    if (0 != lONr && -1 != lONr)
    {
    	if (SUCCEEDED (((CObjectModify*)pvAktObjs)->TestActObject (lONr)))
    		return true;
    }
    return false;
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
CObjectModify::CObjectModify (void)
{
    m_pVWnd = g_pTE->MVWind();	// TRiAS-ViewFenster
    m_dwCookieN = 0L;
    m_dwCookieSN = 0L;
    m_bGeoRein = false;			// Ankopplung von GeoRein.ext über Interface noch nicht erfolgt
    m_LeftButtonSem = false;	// linke Maustaste noch nicht gedrückt
    m_RightButtonSem = false;	// rechte Maustaste noch nicht gedrückt
    m_lParamOld = 0;			// letzte Mausposition
    m_NewCP = CURSPOS_UNKNOWN;	// aktuelle CursorPosition
    m_OldCP = CURSPOS_UNKNOWN;	// bisherige CursorPosition
    m_bSpezCP = false;			// noch keine spezielle CursorPosition
    m_bMenu = false;			// Menü wird noch nicht angezeigt
	m_bRW = false;				// kein m_wBelowObjs-Objekt gehört zu einer R/W-Objektklasse
}


// --------------------------------------------------------------------------------------------
// Destruktor
CObjectModify::~CObjectModify (void)
{
    // Interface's wieder freigeben
    m_wGeoRein.Assign (NULL);

    if (m_wModOper.IsValid())
	{
		m_wModOper->SetModifyClassSite (NULL, NULL);
		m_wModOper.Assign (NULL);
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Verbindung zur GeoEdit-Erweiterung über deren Interface IEditExtensionSite herstellen
// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectModify::SetEditExtensionSite (IEditExtensionSite* pIEdExSite)
{
    try
    {
    	if (pIEdExSite != NULL)
    	{
    	WUnknown wISite;

    		// Verbindung zu TRiAS über Interface ITriasExtension herstellen
    		THROW_FAILED_HRESULT (pIEdExSite->GetXtensionSite (wISite.ppi()));
    		THROW_FAILED_HRESULT (pIEdExSite->CreateInterfaceTO (m_wTopObjs.ppi()));

    		if (wISite.IsValid()) 		// in TRiAS reinhängen
    		{
    			if (m_dwCookieN != 0L || m_dwCookieSN != 0L)	// anmelden
    				_com_issue_error (E_UNEXPECTED);		// darf noch nicht angemeldet sein

    			m_Site = wISite;			// throws_com_error
    			THROW_FAILED_HRESULT (AtlAdvise (m_Site, (ITRiASNotificationSink*)this,
    								  IID_ITRiASNotificationSink, &m_dwCookieN));

    			THROW_FAILED_HRESULT (AtlAdvise (m_Site, (ITRiASSysNotificationSink*)this,
    								  IID_ITRiASSysNotificationSink, &m_dwCookieSN));
    		}

    		m_wEdExSite = pIEdExSite;

    		m_wTopObjs->SetMarkVis (true);	// Stützpunkte der ausgewählten Objekte sollen
    										//  markiert werden
    	}
    	else
    	{
    		// Stützpunktmarkierungen der ausgewählten Objekte sollen gelöscht werden
    		m_wTopObjs->SetMarkVis (false);

    		// Cursor wieder auf die Standard-Form "PFEIL" zurücksetzen
    		m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);

    		if (m_dwCookieN != 0L || m_dwCookieSN != 0L)		// abmelden
    			THROW_FAILED_HRESULT (DisconnectFromServer());	// gibt uns u.u. frei

    		m_wTopObjs.Assign (NULL);	// freigeben
    		m_wEdExSite.Assign (NULL);	// freigeben
    	}
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // SetEditExtensionSite


// --------------------------------------------------------------------------------------------
// TRiASNotificationSink und TRiASSysNotificationSink bei TRiAS wieder abmelden
HRESULT CObjectModify::DisconnectFromServer (void)
{
// künstliches AddRef, da uns nachfolgendes AtlUnadvise freigeben kann
WUnknown Unk ((IEditOperation*)this);

    AtlUnadvise (m_Site, IID_ITRiASNotificationSink, m_dwCookieN); 
    AtlUnadvise (m_Site, IID_ITRiASSysNotificationSink, m_dwCookieSN); 
    
    m_Site.Assign (NULL);	// freigeben von TRiAS
    m_dwCookieN = 0L;
    m_dwCookieSN = 0L;
    return S_OK;

} // DisconnectFromServer


// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectModify::InformRestrictLinesState (IRestrictLine*, IRestrictLine*)
{
    ATLTRACENOTIMPL("CObjectModify::InformRestrictLinesState");
}

// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectModify::DeleteRestrictedCursor (void)
{
    ATLTRACENOTIMPL("CObjectModify::DeleteRestrictedCursor");
}


///////////////////////////////////////////////////////////////////////////////////////////////
// IMenuHandling
// --------------------------------------------------------------------------------------------
// Behandlung der von der GeoEdit-Erweiterung übergebenen MenuCommand's
STDMETHODIMP CObjectModify::WorkMenuCommand (WPARAM MenuItemID, HWND hWnd)
{
HRESULT hrRet = S_OK;

    switch (MenuItemID)
    {
    	case IDM_VERTEXMOD:		// Stützpunkt verschieben durch Koordinaten ändern
    		ManualVertexModify();// nicht als separates C++-Objekt
    		break;

    	case IDM_VERTEXADD:		// Stützpunkt hinzufügen durch Koordinaten ergänzen
    		ManualVertexAdd();	// nicht als separates C++-Objekt
    		break;

    	case IDM_VERTEXDEL:		// Stützpunkt löschen
    		VertexDelete();		// nicht als separates C++-Objekt
    		break;

    	case IDM_LINEPART:
    		LineSplitting();	// nicht als separates C++-Objekt
    		break;

    	case IDM_LINEELONG:
    		LineElongationStart();
    		break;

    	case IDM_LINETOAREA:
    		LineToArea();		// nicht als separates C++-Objekt
    		break;

    	case IDM_OBJECTROT:
//			ObjectRotateStart();
    		break;

    	case IDM_OBJECTPART:	// Schnittlinie für Flächenteilung bilden
    		AreaPartitionStart();
    		break;

    	case IDM_OBJECTCUT:		// Objekt bei Geometriefehlern auftrennnen
    		ObjectsCut();		// nicht als separates C++-Objekt
    		break;

    	case IDM_ISLANDADD:
    		IslandAddStart();
    		break;

    	case IDM_ISLANDDEL:		// Insel löschen
    		IslandsDelete();	// nicht als separates C++-Objekt
    		break;

    	case IDM_AREATOLINE:	// Fläche aufbrechen
    		AreaToLine();		// nicht als separates C++-Objekt
    		break;

    	case IDM_RECHTWINKL:	// Rechtwinkligkeit bezogen auf die angeklickte Strecke erzeugen
    		MakeAreaRectangular();	// nicht als separates C++-Objekt
    		break;

		case IDM_COMMONBORDER:	// Teil einer Linie bzw. Flächenkontur übernehmen
			CommonBorderStart();
			break;

    	case IDM_OBJECTDEL:		// Objekt(e) löschen
    		ObjectsDelete();	// nicht als separates C++-Objekt
    		break;

    	case IDCANCEL:
    		break;

    	default:
    		_ASSERTE (false);
    		hrRet = S_FALSE;
    }

    return hrRet;

} // WorkMenuCommand
 

// --------------------------------------------------------------------------------------------
// Behandlung des von der GeoEdit-Erweiterung übergebenen MenuInit; kommt, bevor ein Menü auf
// dem Bildschirm angezeigt wird
STDMETHODIMP CObjectModify::WorkMenuInit (HMENU hMenu, LPARAM lParam, HWND hWnd)
{
    if (!m_bMenu)
    	return S_FALSE;		// nicht mein Menü

UINT uiMOffset;		// MenuOffset(); ist in xtencatl.hxx für CTriasExtension definiert

    m_wEdExSite->GetMenuOffset (&uiMOffset);

    // wenn nur LINIENobjekte ausgewählt wurden, dann Menü-Einträge "Linie(n) teilen",
    // "Linie(n) verlängern" und "Linie(n) zu Flächen" einfügen
    if (OTLinie == m_iAllOT)
    {
    	InsertMenu (hMenu, IDM_OBJECTDEL+uiMOffset, MF_BYCOMMAND|MF_STRING,
    				IDM_LINETOAREA+uiMOffset, ResString(ResID(IDS_LINETOAREA,pRF),50).Addr());
    	InsertMenu (hMenu, IDM_LINETOAREA+uiMOffset, MF_BYCOMMAND|MF_STRING,
    				IDM_LINEELONG+uiMOffset, ResString(ResID(IDS_LINEELONG,pRF),50).Addr());
    	InsertMenu (hMenu, IDM_LINEELONG+uiMOffset, MF_BYCOMMAND|MF_STRING,
    				IDM_LINEPART+uiMOffset, ResString(ResID(IDS_LINEPART,pRF),50).Addr());

		InsertMenu (hMenu, 6, MF_BYPOSITION|MF_SEPARATOR, 0 , NULL);

    	// Menüpunkt "Linie(n) verlängern" nur aktivieren, wenn Cursor auf dem ersten bzw.
    	// letzten Stützpunkt eines Linienobjektes steht, keines der Linienobjekte geschlossen
		// ist und alle zur gleichen Datenquelle gehören
    	if (m_bSpezCP && AllOpen() && OneDataSource())
    		EnableMenuItem (hMenu, IDM_LINEELONG+uiMOffset, MF_BYCOMMAND|MF_ENABLED);
    	else
    		EnableMenuItem (hMenu, IDM_LINEELONG+uiMOffset, MF_BYCOMMAND|MF_GRAYED);

    	// Menüpunkt "Linie(n) teilen" nur aktivieren, wenn Cursor nicht auf dem ersten bzw.
    	// letzten Stützpunkt eines Linienobjektes steht
    	if (m_bSpezCP)
    		EnableMenuItem (hMenu, IDM_LINEPART+uiMOffset, MF_BYCOMMAND|MF_GRAYED);
    	else
    		EnableMenuItem (hMenu, IDM_LINEPART+uiMOffset, MF_BYCOMMAND|MF_ENABLED);

    // Menüpunkt "Linie(n) zu Flächen" nur aktivieren, wenn Cursor auf geschlossenem 
	// Linienobjekt steht
	// #hk020719: Linien werden auch umgewandelt, wenn sie nicht geschlossen sind,
	// dazu wird eine Warnung in der eigentlichen Routine ausgegeben
//    	if (AllClosed())
    		EnableMenuItem (hMenu, IDM_LINETOAREA+uiMOffset, MF_BYCOMMAND|MF_ENABLED);
//    	else
//    		EnableMenuItem (hMenu, IDM_LINETOAREA+uiMOffset, MF_BYCOMMAND|MF_GRAYED);
    }


ulong ulBelowCnt;	// Anzahl der Objekte, die unter der Mausspitze liegen

	m_wBelowObjs->GetCount (&ulBelowCnt);

    // wenn nur FLÄCHENobjekte ausgewählt wurden ...
    if (OTFlaeche == m_iAllOT)
    {
    	// ... und alle zur gleichen Datenquelle gehören, dann Menüpunkt "Insel(n) hinzufügen"
		// aktivieren
		if (OneDataSource())
    		EnableMenuItem (hMenu, IDM_ISLANDADD+uiMOffset, MF_BYCOMMAND|MF_ENABLED);

    	// ... und Cursor auf wenigstens einer Innenkontur steht, dann Menüpunkt
		// "Insel(n) löschen" aktivieren
    	if (m_bSpezCP)
    		EnableMenuItem (hMenu, IDM_ISLANDDEL+uiMOffset, MF_BYCOMMAND|MF_ENABLED);

    	// ... und genau EINE Fläche unter der Mausspitze liegt, dann Menüpunkt
		// "Schnittlinie bilden" aktivieren
    	if (1 == ulBelowCnt) {
    		EnableMenuItem (hMenu, IDM_OBJECTPART+uiMOffset, MF_BYCOMMAND|MF_ENABLED);

		// wenn genau eine Fläche unter Mausspitze liegt und diese keine Insel hat
		// dann Menupunkt 'Zu Linie konvertieren' hinzufügen
		WUnknown Unk;

			m_wBelowObjs -> Reset();
			if (S_OK == m_wBelowObjs -> Next (1, Unk.ppi(), NULL)) {
			WObjektGeometrie wObj (Unk);
			short iOT, iKCnt;			// Parameter des wObj-Objektes

	    		wObj -> GetObjTyp (&iOT);
	    		wObj -> GetKCnt (&iKCnt);
				if (OT_FLAECHE == iOT && 1 == iKCnt) {
			    	InsertMenu (hMenu, IDM_OBJECTDEL+uiMOffset, MF_BYCOMMAND|MF_STRING,
    					IDM_AREATOLINE+uiMOffset, ResString(ResID (IDS_AREATOLINE,pRF),50).Addr());
				}
			}
		}
    }


    // wenn nur LINIEN- bzw. FLÄCHENobjekte ausgewählt wurden und Cursor auf einer Strecke
    // steht, dann Menüpunkt "Stützpunkt(e) modifizieren" durch "Stützpunkt(e) hinzufügen"
    // ersetzen
    if (((m_iAllOT & OTLinie || m_iAllOT & OTFlaeche) && 0 == (m_iAllOT & OTPunkt)) &&
    	CURSPOS_LINE == m_NewCP)	// Cursor auf Strecke
    {
    	ModifyMenu (hMenu, IDM_VERTEXMOD+uiMOffset, MF_BYCOMMAND|MF_STRING,
    				IDM_VERTEXADD+uiMOffset, ResString(ResID(IDS_VERTEXADD,pRF),50).Addr());

    	// Menüpunkt "Stützpunkt(e) löschen" deaktivieren
    	EnableMenuItem (hMenu, IDM_VERTEXDEL+uiMOffset, MF_BYCOMMAND|MF_GRAYED);
    }


    // wenn Cursor auf einer Konturstrecke einer einzigen aktivierten Fläche steht und kein
	// Schreibschutz vorliegt, dann Menüpunkt "Rechtwinkligkeit" aktivieren, sonst deaktivieren
    if (CURSPOS_LINE == m_NewCP &&	// Cursor auf Strecke und
    	(m_iAllOT & OTFlaeche))		// mindestens 1 Fläche selektiert
    {
    	m_lAktONr = 0;

    ENUMNOKEYLONG ENKL;		// Enumeration aller Recherchefenster

    	memset (&ENKL, '\0', sizeof (ENUMNOKEYLONG));
    	ENKL.eFcn = (ENUMNOKEYLONGPROC) AktivierteObjekte;
    	ENKL.ePtr = (void*)this;

    bool bRet = DEX_EnumORWindows (ENKL);

    	if (0 != m_lAktONr && -1 != m_lAktONr && bRet)	// Cursor steht an einer einzigen
														//  aktivierten Fläche
    		// Menüpunkt "Rechtwinkligkeit" aktivieren
    		EnableMenuItem (hMenu, IDM_RECHTWINKL+uiMOffset, MF_BYCOMMAND|MF_ENABLED);
    }

	// Menüpunkt "Selbstinzidenzen bereinigen"
	MenuSelfTouch (hMenu);

	// Menüpunkt "Gemeinsame Linie"
	MenuCommonBorder (hMenu);

    // wenn mehrere Objekte unter der Mausspitze liegen, dann die Singular- durch die
    // Plural-Menütexte ersetzen
    if (ulBelowCnt > 1) PluralTexts (hMenu, uiMOffset);

    return S_OK;

} // WorkMenuInit
 

// --------------------------------------------------------------------------------------------
// Behandlung des von der GeoEdit-Erweiterung übergebenen MenuSelect
STDMETHODIMP CObjectModify::WorkMenuSelect (UINT uiMenuID, HMENU hMenu, HWND hWnd)
{
ResString rsText (ResID (IDS_STATKOORDMOD, pRF), 100);		// case IDM_VERTEXMOD

    switch (uiMenuID)
    {
    	case IDM_VERTEXMOD:
    		break;

    	case IDM_VERTEXDEL:	// Stützpunkt löschen
    		rsText = ResString (ResID (IDS_STATVERTDELETE, pRF), 100);
    		break;

    	case IDM_VERTEXADD:		// Stützpunkt hinzufügen
    		rsText = ResString (ResID (IDS_STATVERTADD, pRF), 100);
    		break;

    	case IDM_LINEPART:		// Linie teilen
    		rsText = ResString (ResID (IDS_STATLINIETEIL, pRF), 100);
    		break;

    	case IDM_LINEELONG:		// Linie verlängern
    		rsText = ResString (ResID (IDS_STATLINIEVERL, pRF), 100);
    		break;

    	case IDM_LINETOAREA:		// Linie zu Fläche konvertieren
    		rsText = ResString (ResID (IDS_STATLINETOAREA, pRF), 100);
    		break;

    	case IDM_OBJECTROT:
    		rsText = ResString (ResID (IDS_STATOBJDREHEN, pRF), 100);
    		break;

    	case IDM_OBJECTPART:		// Schnittlinie für Flächenteilung bilden
    		rsText = ResString (ResID (IDS_STATOBJPART, pRF), 100);
    		break;

    	case IDM_OBJECTCUT:			// Objekt bei Geometriefehlern auftrennnen
    		rsText = ResString (ResID (IDS_STATOBJCUT, pRF), 100);
    		break;

    	case IDM_ISLANDADD:
    		rsText = ResString (ResID (IDS_STATADDINSEL, pRF), 100);
    		break;

    	case IDM_ISLANDDEL:
    		rsText = ResString (ResID (IDS_STATSUBINSEL, pRF), 100);
    		break;

    	case IDM_AREATOLINE:
    		rsText = ResString (ResID (IDS_STATAREATOLINE, pRF), 100);
    		break;

    	case IDM_RECHTWINKL:	// Rechtwinkligkeit bezogen auf die angeklickte Strecke erzeugen
    		rsText = ResString (ResID (IDS_STATRECHTWINKL, pRF), 100);
    		break;

    	case IDM_OBJECTDEL:		// Objekt(e) löschen
    		rsText = ResString (ResID (IDS_STATOBJDELETE, pRF), 100);
    		break;

    	case IDCANCEL:
    		rsText = ResString (ResID (IDS_STATABBRUCH, pRF), 100);
    		break;

    	default:
    		DEX_SetMessageStringNoKickIdle ("");
    		return S_FALSE;
    }

    DEX_SetMessageStringNoKickIdle (rsText.Addr());
    return S_OK;

} // WorkMenuSelect



///////////////////////////////////////////////////////////////////////////////////////////////
// IModifyClassSite
// --------------------------------------------------------------------------------------------
// weitere Parameter an ModifyOperation's übergeben
HRESULT CObjectModify::GetParameter (long* plMPX, long* plMPY,
									 IEnumObjektGeometrie** ppBelowObjs)
{
    // aktuelle CursorPosition und die darunter liegenden ausgewählten Objekte ermitteln, da
    // nach einem StützpunktHinzufügen OHNE erneutes MouseMove gleich wieder ein LeftMouseDown
    // für StützpunktVerschieben kommen kann
    RefreshCursorForm();

    *plMPX = m_GrabPkt.X();
    *plMPY = m_GrabPkt.Y();
    *ppBelowObjs = m_wBelowObjs;	// ein weiterer Zugriff auf *ppBelowObjs durch
    (*ppBelowObjs)->AddRef();		// diese Pointerkopie; deshalb AddRef()
	// AddRef() wäre auch für den rechten Operanten "m_wBelowObjs" möglich; damit hätte aber
	// vermutlich der BoundsChecker Probleme, da AddRef() und Release() für die GLEICHE
	// Variable erwartet wird
    return S_OK;

} // GetParameter


// --------------------------------------------------------------------------------------------
// rechteckiger Ausschnitt neu zeichnen, in dem der modifizierte Teil des Objektes pIOG liegt
HRESULT CObjectModify::SectorToDraw (IUnknown* pIOG, long lModPktX, long lModPktY, long lInd,
	 								 BOOL bVtDel, RECT* pSector)
{
    _ASSERTE (pIOG != NULL);

double dQuot = 1.;   // Quotient von Bezugsmaßstab und Darstellungsmaßstab

	if (!DEX_GetActiveScaling (dQuot))
		dQuot = 1.;

    if (dQuot > 0)
		dQuot *= 100.;	
    else
    {
    	_ASSERTE (dQuot > 0);
    	dQuot = 1.;   // um Division durch Null vorzubeugen
    }

Dimension dimDots = GetDotsPerMM (NULL);	// Pixel pro Millimeter für den Bildschirm

int iMarkGr;

    m_wTopObjs->GetMarkerSizeBS (&iMarkGr);

short iOT;
ulong ulIdent = (ulong)-1;
WObjektGeometrie wObj;

	try
	{
		wObj = pIOG;		// mit implizitem QueryInterface
		wObj->GetObjTyp (&iOT);
		wObj->GetIdent (&ulIdent);
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

HANDLEVISINFO HVI;

    INITSTRUCT (HVI, HANDLEVISINFO);	// Initialisierung
    HVI.m_lIdent = ulIdent;				// Identifikator
    HVI.m_pDesc = NULL;					// beschreibender Text
    HVI.m_pView = NULL;					// SichtName (aktuelle Sicht: NULL)

    switch (iOT)
    {
    	case OT_PUNKT:
    	{
    	PVISINFO PVI;
    	SIZE sizePG;
    			
    		HVI.m_iVTyp = VTPunkt;		// VisInfoTyp
    		HVI.m_pVI = &(PVI.m_VI);	// generischer Pointer auf VisInfo
    		if (DEX_GetIdentVisInfo (HVI))	// RückkehrCode ausgewertet
    			sizePG = PVI.m_Size;   // Punktgröße (Eintrag aus der VisInfo)
    		else
    		{
    			sizePG.cx = DEF_SIZE_PUNKT_X;
    			sizePG.cy = DEF_SIZE_PUNKT_Y;
    		}

    	// Größe des Punktsymbols in BS-Pixel in x- bzw. y-Richtung
    	int ixpix = (int) (sizePG.cx * dimDots.Width() / dQuot);
    	int iypix = (int) (sizePG.cy * dimDots.Height() / dQuot);
    	
    		*pSector = SectorDefine (wObj, lModPktX, lModPktY, lInd, bVtDel);
    		pSector->left -= ixpix/2 + iZug;
    		pSector->right += ixpix/2 + iZug; 
    		pSector->top += iypix/2 + iZug;
    		pSector->bottom -= iypix/2 + iZug;
    		break;
    	}


    	case OT_KANTE:
    	{
    	LVISINFO LVI;
    	int iLinBr;

    		HVI.m_iVTyp = VTLinie;		// VisInfoTyp
    		HVI.m_pVI = &(LVI.m_VI);	// generischer Pointer auf VisInfo
    		if (DEX_GetIdentVisInfo (HVI))		// RückkehrCode ausgewertet
    			// LinienBreite (Eintrag aus der Visualisierungsinformation)
    			iLinBr = LVI.m_Width;
    		else
    			iLinBr = DEF_WIDTH_LINIE;

    	// Maximum aus Linienbreite und Größe eines Markers in x- bzw. y-Richtung
    	// der double-Cast vor dem 2. Parameter ist erforderlich weil die max-Routine für beide
    	// Parameter den gleichen Typ erwartet
	 	int iZugX = (int)max (iLinBr * dimDots.Width() / dQuot + iZug, (double)iMarkGr);
	 	int iZugY = (int)max (iLinBr * dimDots.Height() / dQuot + iZug, (double)iMarkGr);
    	
    	
    		*pSector = SectorDefine (wObj, lModPktX, lModPktY, lInd, bVtDel);
    		pSector->left -= iZugX;	// zu bildendes Rechteck noch um Maximun aus Linienbreite
    		pSector->right += iZugY;	//  bzw. Marker-Größe vergrößern
    		pSector->top += iZugX;
    		pSector->bottom -= iZugY;
    		break;
    	}

    		
    	case OT_FLAECHE:
    	{
    	FVISINFO FVI;
    	double dKontBr;
    			
    		HVI.m_iVTyp = VTFlaeche;		// VisInfoTyp
    		HVI.m_pVI = &(FVI.m_VI);		// generischer Pointer auf VisInfo
    		if (DEX_GetIdentVisInfo (HVI))	// RückkehrCode ausgewertet
    			// m_Style ist ein 16-Bit-Wort mit mehreren Informationen; wenn das 16. Bit
    			// ausgeblendet und der Rest durch 100 dividiert wird, liefert das ganzzahligen
    			// Divisionsergebnis die Konturbreite in 0.01 mm, d.h. den Eintrag aus der
    			// Visualisierungsinformation
    			dKontBr = ((FVI.m_VI.m_Style) & 0x7FFF) / 100.;
    		else
    			dKontBr = DEF_WIDTH_FRAME;

    	// Maximum aus Konturbreite und Größe eines Markers in x- bzw. y-Richtung
	 	int iZugX = (int)max (dKontBr * dimDots.Width() / dQuot + iZug, (double)iMarkGr);
	 	int iZugY = (int)max (dKontBr * dimDots.Height() / dQuot + iZug, (double)iMarkGr);
    	
    		*pSector = SectorDefine (wObj, lModPktX, lModPktY, lInd, bVtDel);
    		pSector->left -= iZugX;	// zu bildendes Rechteck noch um Maximun aus Konturbreite
    		pSector->right += iZugY;	//  bzw. Marker-Größe vergrößern
    		pSector->top += iZugX;
    		pSector->bottom -= iZugY;
    		break;
    	}


    	default:
    		_ASSERTE (false);
    		break;
    }
     
    return S_OK;

} // SectorToDraw


// --------------------------------------------------------------------------------------------
// Hilfsroutine für CVertexMove, VertexDelete() und CVertexAdd;
// es wird true zurückgegeben, wenn Objekt gespeichert wurde, sonst false
HRESULT CObjectModify::ModObjSpeicherung (IUnknown* pIOG, long lModPktX, long lModPktY,
	 									 long lInd, BOOL bVtDel, TestRicht trRicht, RECT* pRec)
{
    _ASSERTE (pIOG != NULL);
    _ASSERTE (pRec != NULL);

    if (! pIOG) return E_UNEXPECTED;

WObjektGeometrie wObj;

	try
	{
		wObj = pIOG;	// mit implizitem QueryInterface
	}
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

// mit Schlüssel "GeoFehlerTest" in den projektbezogenen Einträgen des DB-Headers testen ...
// ... ob vor Abspeicherung des wObj-Objektes nach TRiAS auf Geometriefehler getestet werden
//     soll (ja) oder nicht (nein)
// ... Entartung bereinigt werden soll (Bit 4 = 1) oder nicht (Bit 4 = 0)
ResString Schluessel (ResID (IDS_GEOFEHLERTEST, pRF), 30);	
HeaderEntryX HE (Schluessel);
char pcInPuffer[20] = { "\0" };	// Wert des Schlüssels "GeoFehlerTest"

    if (HE.Status() != HE_INVALID)	// Schlüssel "GeoFehlerTest" existiert im DB-Header
    	strcpy (pcInPuffer, HE.EntryText());

HRESULT hrSA = S_OK;	// return-Wert der Routine ShortAnalysis() 
bool bGeoRein = true;	// GeoRein.ext soll angeworfen werden
long lONr;

   	wObj->GetONr (&lONr);

    if (pcInPuffer[0] != 'n' && pcInPuffer[0] != 'N')
    {
    short iOT;

    	// wenn Objekt schon von vornherein fehlerbehaftet ist (Eintrag im Merkmal
    	// "Geometriefehler"), dann kommt nur eine vollständige Geometrieprüfung in Betracht;
    	// andererseits reicht eine Kurzanalyse aus (Unterscheidung in dem OGGeometryIsChecked-
    	// Flag)
    	wObj->GetObjTyp (&iOT);
   		GeoReinInterface();		// (wenn noch nicht, dann) GeoReinInterface für
    							// FehlerhaftesObjekt() und  ShortAnalysis() zuschalten
    	if ((OT_KANTE == iOT || OT_FLAECHE == iOT) &&
    		 S_OK != FehlerhaftesObjekt (m_wGeoRein, lONr))
    	{
    		if (m_wGeoRein.IsValid())
    		{
    			hrSA = m_wGeoRein->ShortAnalysis (wObj, trRicht, &lInd);
    			if (S_OK == hrSA)	// Analyse ergab keinen Geometriefehler
    				bGeoRein = false;	// GeoRein.ext nicht anwerfen
    			else
    			{
    				if (E_FAIL == hrSA)	// Analyse ergab Geometriefehler
    				{
    				// bei Stützpunktmanipulation ist ein Geometriefehler entstanden
    				ResString resText (ResID (IDS_GEOFEHLERMOD, pRF), 150);
    				ResString resCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);
    				
    					MessageBox (__hWndM, resText.Addr(), resCapt.Addr(),
    								MB_ICONEXCLAMATION | MB_OK);
    				}
    				else
    				{
    					// Übergabe von unerlaubten Parametern
    					DEX_Error (RC_ObjectModify, EC_ILLPARS);					
    					MessageBox (__hWndM, "Das veränderte Objekt wurde nicht abgespeichert,\nda unerlaubte Parameter übergeben wurden!",
    								"Achtung:", MB_ICONEXCLAMATION | MB_OK);
    				}
    			}
    		}
    	}
    }
    else
    	bGeoRein = false;	// GeoRein.ext nicht anwerfen

    // Ausschnitt für Neuzeichnen nach Geometrie-Modifikation
    SectorToDraw (wObj, lModPktX, lModPktY, lInd, bVtDel, pRec);

    if (S_OK == hrSA)	// modifiziertes Objekt wird nach TRiAS gespeichert
    {
		// OGModObject:         Geometrie des Objektes soll ersetzt werden
		// OGForceGeometry:     auch außerhalb des aktuellen DBConts abspeichern
		// OGGeometryIsChecked: GeoRein.ext sol nicht angeworfen werden
    	if (bGeoRein)
    		wObj->SetFlags (OGModObject | OGForceGeometry);
    	else
    		wObj->SetFlags (OGModObject | OGForceGeometry | OGGeometryIsChecked);

#if _TRiAS_VER < 0x0300
    	// 1. Parameter von GeometrieAnTRiAS() besagt, daß Undo möglich ist
    	return wObj->GeometrieAnTRiAS (true, pRec);
#else
	INT_PTR hPr = reinterpret_cast<INT_PTR>(DEX_GetObjectProject (lONr));

    	// 2. Parameter von GeometrieAnTRiASEx() besagt, daß Undo möglich ist
    	return wObj->GeometrieAnTRiASEx (hPr, true, pRec);
#endif // _TRiAS_VER < 0x0300
    }

    return hrSA;

} // ModObjSpeicherung


// --------------------------------------------------------------------------------------------
// GrabPunkt m_GrabPkt setzen
HRESULT CObjectModify::SetGrabPoint (long lGPX, long lGPY)
{
    m_GrabPkt.X() = lGPX;
    m_GrabPkt.Y() = lGPY;
    return S_OK;

} // SetGrabPoint


// --------------------------------------------------------------------------------------------
// die CursorForm aktualisieren und den Schreibschutz der geöffneten Datenquellen ermitteln
HRESULT CObjectModify::RefreshCursorForm (void)
{
#if _TRiAS_VER < 0x0300
	m_bRW = true;	// Objektklasse hat R/W-Modus
#else
	m_bRW = false;	// keine Objektklasse mit R/W-Modus
#endif // _TRiAS_VER < 0x0300

	try
	{
		m_wTopObjs->CursorAtTopicalObjects (&m_NewCP, &m_bSpezCP, &m_GrabPkt.X(),
											&m_GrabPkt.Y(), m_wBelowObjs.ppi());
#if _TRiAS_VER >= 0x0300
	WUnknown Unk;
	ulong ulIdent = 0;

		for (m_wBelowObjs->Reset(); S_OK == m_wBelowObjs->Next (1, Unk.ppi(), NULL); )
		{
		// Abfrage, ob zugehörige Objektklassen schreibgeschützt sind oder nicht
		WObjektGeometrie wObj (Unk);

    		wObj->GetIdent (&ulIdent);
			if (0 == DEX_GetROModeIdent (ulIdent))
			{
				m_bRW = true;	// mindestens eine Objektklasse mit R/W-Modus
				break;
			}
		}
#endif // _TRiAS_VER >= 0x0300
	}
   	catch (_com_error&)
   	{
	    return m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);
	}

    if (m_NewCP == m_OldCP)
	{
		if (CURSPOS_UNKNOWN == m_NewCP)
		    return m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);
		return S_OK;
	}

    m_OldCP = m_NewCP;	// bisherige CursorPosition retten

    if (CURSPOS_VERTEX == m_NewCP)		// Cursor im Marker eines Stützpunktes
    {
		if (m_bRW)
		{
    		if (GetKeyState (VK_CONTROL) >= 0)	// CTRL-Taste nicht gedrückt
    			return m_wEdExSite->SetCursor (CURSFORM_STERN, TRUE);
    		return m_wEdExSite->SetCursor (CURSFORM_KREUZ, TRUE);
		}

	// nur R/O-Modus, deshalb Anzeige in der Statuszeile
	ResString rsText (ResID (IDS_ROMODE, pRF), 100);

		DEX_SetMessageStringNoKickIdle (rsText.Addr());
		return m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);
    }

    if (CURSPOS_LINE == m_NewCP)	// Cursor "in der Nähe" einer Strecke
	{
		if (m_bRW)
	    	return m_wEdExSite->SetCursor (CURSFORM_TRENNER, TRUE);

	// nur R/O-Modus, deshalb Anzeige in der Statuszeile
	ResString rsText (ResID (IDS_ROMODE, pRF), 100);

		DEX_SetMessageStringNoKickIdle (rsText.Addr());
		return m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);
	}

    return m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);

} // RefreshCursorForm



///////////////////////////////////////////////////////////////////////////////////////////////
// Interface ITRiASNotificationSink: TRiAS-Notification's abfangen
// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectModify::ServerEvent (SERVEREVT se)
{
    ATLTRACE("CObjectModify::ServerEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectModify::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT vProj)
{
    ATLTRACE("CObjectModify::ProjectEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// TRiAS-Notification's abfangen, die für die aktuelle Sicht verschickt werden
STDMETHODIMP CObjectModify::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT vData)
{
    if (m_wModOper.IsValid()) // eine ModifyOperation ist aktiv
    {
    	try
    	{
    	WTRiASNotificationSink wNotSink (m_wModOper);

    		// Weiterleitung an aktive ModifyOperation
    		wNotSink->GeoViewEvent (hPr, ve, vData);
    	}
    	catch (_com_error&)
    	{
		    ATLTRACE("throw-failure in CObjectModify::GeoViewEvent");
    	}

    	return S_OK;
    }

	return S_OK;

} // GeoViewEvent


// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectModify::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
    ATLTRACE("CObjectModify::GeoClassEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectModify::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
    ATLTRACE("CObjectModify::GeoObjectEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectModify::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
    ATLTRACE("CObjectModify::GeoFeatureEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectModify::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
    ATLTRACE("CObjectModify::GeoRelationEvent not implemented");
	return S_OK;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectModify::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
    ATLTRACE("CObjectModify::ObjectWindowEvent not implemented");
	return S_OK;
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Interface ITRiASSysNotificationSink: WindowsNotification's abfangen
// --------------------------------------------------------------------------------------------
STDMETHODIMP CObjectModify::WindowsMessage (long hWnd, long uiMsg, long wParam, long lParam)
{
    switch (uiMsg)
    {
    	case WM_KEYDOWN:
    		KeyDown (hWnd, uiMsg, wParam, lParam);
    		break;
    	
    	case WM_KEYUP:
    		KeyUp (hWnd, uiMsg, wParam, lParam);
    		break;

		case WM_CHAR:
    		WMChar (hWnd, uiMsg, wParam, lParam);
			break;

    	case WM_MOUSEMOVE:
    		MouseMove (hWnd, uiMsg, wParam, lParam);
    		break;

    	case WM_LBUTTONDOWN:
    		LeftMouseDown (hWnd, uiMsg, wParam, lParam);
    		break;

    	case WM_LBUTTONUP:
    		LeftMouseUp (hWnd, uiMsg, wParam, lParam);
    		break;

    	case WM_RBUTTONDOWN:
    		RightMouseDown (hWnd, uiMsg, wParam, lParam);
    		break;

    	case WM_RBUTTONUP:
    		RightMouseUp (hWnd, uiMsg, wParam, lParam);
    		break;

		case WM_LBUTTONDBLCLK:
    		LeftDoubleClick (hWnd, uiMsg, wParam, lParam);
    		break;

		// aktive ModifyOperation abmelden (z.B. LineElongation)
		case WM_WM_OBJMODIFYEND:
			if (m_wModOper.IsValid())
			{
	    		m_wModOper->SetModifyClassSite (NULL, NULL);
				m_wModOper.Assign (NULL);
			}

			break;
    }

    return S_OK;	// immer weiterleiten

} // WindowsMessage


// --------------------------------------------------------------------------------------------
// eine bestimmte Taste der Tastatur wurde gedrückt, z. B. SHIFT, CTRL
HRESULT CObjectModify::KeyDown (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    if (! m_wModOper.IsValid())	// keine ModifyOperation aktiv
    {
    	if (VK_CONTROL == wParam) 				// CTRL-Taste gedrückt und
    	{
    		if (CURSPOS_VERTEX == m_NewCP)		// Cursor im Marker eines Stützpunktes
    			return m_wEdExSite->SetCursor (CURSFORM_KREUZ, TRUE);	// dann KREUZ-Form
    	}
    	else return S_FALSE;	// keine für ObjectModify relevante Taste gedrückt
    }

    else						// eine ModifyOperation aktiv
    {
    	try
    	{
    	WTRiASSysNotificationSink wSysNotSink (m_wModOper);

    		// Weiterleitung der WindowsMessage an aktive ModifyOperation
    		wSysNotSink->WindowsMessage (hWnd, uiMsg, wParam, lParam);
    	}
    	catch (_com_error& e)
    	{
    		return _COM_ERROR (e);
    	}
    }

    return S_OK;

} // KeyDown


// --------------------------------------------------------------------------------------------
// eine Taste der Tastatur wurde losgelassen
HRESULT CObjectModify::KeyUp (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    if (! m_wModOper.IsValid())	// keine ModifyOperation aktiv
    {
    	if (VK_CONTROL == wParam)	// CTRL-Taste losgelassen
    	{
    		if (CURSPOS_VERTEX == m_NewCP)		// Cursor im Marker eines Stützpunktes
    			return m_wEdExSite->SetCursor (CURSFORM_STERN, TRUE);
    		else if (CURSPOS_LINE == m_NewCP)	// Cursor "in der Nähe" einer Strecke
    			return m_wEdExSite->SetCursor (CURSFORM_TRENNER, TRUE);
    		else
    			return m_wEdExSite->SetCursor (CURSFORM_PFEIL, TRUE);
    	}
    	return S_FALSE;		// keine für ObjectModify relevante Taste losgelassen
    }

    else						// eine ModifyOperation aktiv
    {
   	WTRiASSysNotificationSink wSysNotSink (m_wModOper);

    	COM_TRY
    	{
			if (m_wModOper.IsValid())
				wSysNotSink = m_wModOper;

    		// Weiterleitung der WindowsMessage an aktive ModifyOperation
    		wSysNotSink->WindowsMessage (hWnd, uiMsg, wParam, lParam);
    	}
		COM_CATCH;
    }

    return S_OK;

} // KeyUp


// --------------------------------------------------------------------------------------------
// eine bestimmte Taste wurde gedrückt, z. B. TAB
HRESULT CObjectModify::WMChar (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    if (! m_wModOper.IsValid())	// keine ModifyOperation aktiv
    	return S_FALSE;

   	COM_TRY
   	{
   	WTRiASSysNotificationSink wSysNotSink (m_wModOper);

   		// Weiterleitung der WindowsMessage an ModifyOperation
   		wSysNotSink->WindowsMessage (hWnd, uiMsg, wParam, lParam);
   	}
	COM_CATCH;

    return S_OK;

} // WMChar


// --------------------------------------------------------------------------------------------
// Maus wurde bewegt
HRESULT CObjectModify::MouseMove (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	if (NULL == g_pTE->MVWind())	// Projekt wird geschlossen oder kein Projekt geöffnet
    	return S_FALSE;				// NICHT "if (NULL == m_pVWnd)" !!!!

    if (lParam == m_lParamOld) return S_OK;	// keine Mausbewegung

    if (m_bMenu) return S_FALSE;			// Menü wird angezeigt

    m_lParamOld = lParam;

long lCnt = 0;

    m_wTopObjs->GetCount (&lCnt);
    if (0 == lCnt)	// keine ausgewählten Objekte vorhanden
    	return S_FALSE;

    // wenn keine ModifyOperation aktiv ist, dann für CursorForm die Normaleinstellung,
    // ansonsten die Arbeit eben dieser ModifyOperation überlassen
    if (! m_wModOper.IsValid())
    	// aktuelle CursorPosition und die darunter liegenden ausgewählten Objekte ermitteln
    	return RefreshCursorForm();

    // eine ModifyOperation ist aktiv
    try
    {
    WTRiASSysNotificationSink wSysNotSink (m_wModOper);

    	// Weiterleitung der WindowsMessage an aktive ModifyOperation
    	wSysNotSink->WindowsMessage (hWnd, uiMsg, wParam, lParam);
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // MouseMove


// --------------------------------------------------------------------------------------------
// linke Maustaste wurde gedrückt
HRESULT CObjectModify::LeftMouseDown (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    if (m_bMenu ||				// Menü wird angezeigt
		m_LeftButtonSem ||		// linke Maustaste wurde nicht losgelassen
		! m_bRW)				// keine Objektklasse im R/W-Modus
		return S_FALSE;

    m_LeftButtonSem = true;		// linke Maustaste wurde gedrückt

    if (m_wModOper.IsValid())	// eine ModifyOperation ist aktiv (z.B. LineElongation)
    {
    	m_bStopLMUp = false;	// ModifyOperation bei LeftMouseUp nicht beenden

    	try
    	{
    	WTRiASSysNotificationSink wSysNotSink (m_wModOper);

    		// Weiterleitung der WindowsMessage an aktive ModifyOperation
    		wSysNotSink->WindowsMessage (hWnd, uiMsg, wParam, lParam);
    	}
    	catch (_com_error& e)
    	{
    		return _COM_ERROR (e);
    	}

    	return S_OK;
    }

    // es ist keine ModifyOperation aktiv
    m_bStopLMUp = true;		// ModifyOperation bei LeftMouseUp beenden

CursForm CF;	// aktuelle CursorForm

    m_wEdExSite->GetCursor (&CF);

    if (CURSFORM_STERN == CF)
    	VertexMoveStart (hWnd, uiMsg, wParam, lParam);	// "Stützpunkt verschieben" anschieben
    else if (CURSFORM_KREUZ == CF)
	{
    	if (E_FAIL == VertexDelete())		// Stützpunkt löschen
			// wenn Stützpunkt nicht gelöscht werden kann, kommt eine Fehlerausschrift, wodurch
			// LeftMouseUp() übergangen wird; deshalb ein Pseudo-LeftMouseUp() (29.06.99)
			m_LeftButtonSem = false;
	}
    else if (CURSPOS_LINE == m_NewCP)
    	VertexAddStart (hWnd, uiMsg, wParam, lParam);	// "Stützpunkt hinzufügen" anschieben
    else
    	// befindet sich der Cursor beim Drücken der linken Maustaste weder innerhalb einer
    	// Stüztpunktmarkierung noch "in der Nähe" einer Kante, gilt dies wie "linke Maustaste
    	// nicht gedrückt"
    	m_LeftButtonSem = false;

    return S_OK;

} // LeftMouseDown


// --------------------------------------------------------------------------------------------
// linke Maustaste wurde losgelassen
HRESULT CObjectModify::LeftMouseUp (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    if (!m_LeftButtonSem)	// linke Maustaste wurde nicht gedrückt
    	return S_FALSE;

    m_LeftButtonSem = false;		// linke Maustaste wurde losgelassen

    try
    {
    WTRiASSysNotificationSink wSysNotSink (m_wModOper);

    	wSysNotSink->WindowsMessage (hWnd, uiMsg, wParam, lParam);
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    if (m_bStopLMUp && m_wModOper.IsValid())	// ModifyOperation beenden
	{
		m_wModOper->SetModifyClassSite (NULL, NULL);
    	m_wModOper.Assign (NULL);
	}

    return S_OK;

} // LeftMouseUp


// --------------------------------------------------------------------------------------------
// rechte Maustaste wurde gedrückt
HRESULT CObjectModify::RightMouseDown (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    if (m_wModOper.IsValid()) // eine ModifyOperation ist aktiv (z.B. LineElongation)
    {
    	try
    	{
    	WTRiASSysNotificationSink wSysNotSink (m_wModOper);

    		// Weiterleitung der WindowsMessage an aktive ModifyOperation
    		wSysNotSink->WindowsMessage (hWnd, uiMsg, wParam, lParam);
    	}
    	catch (_com_error& e)
    	{
    		return _COM_ERROR (e);
    	}

    	return S_OK;
    }

    // es ist keine ModifyOperation aktiv
    if (m_bMenu) return S_FALSE;	// Menü wird angezeigt

    // wenn sich Cursor nicht im Marker bzw. auf der Strecke eines Objektes befindet, dann wird
    // dies angesehen wie "rechte Maustaste nicht gedrückt"
    if (CURSPOS_VERTEX != m_NewCP && CURSPOS_LINE != m_NewCP)
    	return S_FALSE;

    m_RightButtonSem = true;		// rechte Maustaste wurde gedrückt
	m_ptRM = BSPoint (lParam);		// BS-Punkt, bei dem rechte Maustaste gedrückt wurde

    // die beiden nachfolgenden Aktionen werden für die Linienverlängerung und das
    // Rechtwinkligmachen benötigt
	m_PktRM = DBKoordinaten (m_ptRM);	// DB-Punkt, bei dem rechte Maustaste gedrückt wurde
    m_wTopObjs->GetEpsilon (&m_lEpsilon);

    return S_OK;

} // RightMouseDown


// --------------------------------------------------------------------------------------------
// rechte Maustaste wurde losgelassen
HRESULT CObjectModify::RightMouseUp (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    if (m_wModOper.IsValid()) // eine ModifyOperation ist aktiv (z.B. LineElongation)
    {
    	try
    	{
    	WTRiASSysNotificationSink wSysNotSink (m_wModOper);

    		// Weiterleitung der WindowsMessage an aktive ModifyOperation
    		wSysNotSink->WindowsMessage (hWnd, uiMsg, wParam, lParam);
    	}
    	catch (_com_error& e)
    	{
    		return _COM_ERROR (e);
    	}

    	return S_OK;
    }

    if (!m_RightButtonSem)	// rechte Maustaste wurde nicht gedrückt
    	return S_FALSE;

    m_RightButtonSem = false;		// rechte Maustaste wurde losgelassen

	if (! m_bRW)	// kein Objekt aus einer R/W-Objektklasse
		return S_FALSE;

// y-Koordinate zurückdrehen, da für Anzeige des Menüs Windows(???)-Koordinaten benötigt
// werden (iAway ist in EditKonst.h definiert)
Point Pnt;
Rectangle CRc = m_pVWnd->CanvasRect();

    Pnt.X() = m_ptRM.X() + iAway;
    Pnt.Y() = CRc.Top() - CRc.Bottom() - m_ptRM.Y() + iAway;

Window Wnd(__hWndM);	// TRiAS-Hauptfenster

    GetBelowObjTypes();

    m_bMenu = true;		// Menü wird angezeigt
    switch (m_iAllOT)
    {
    	case OTPunkt:
    	case OTPunkt | OTLinie:
    	case OTPunkt | OTFlaeche:
    	case OTPunkt | OTLinie | OTFlaeche:
    		ObjectModifyMenu (&Wnd, Pnt, IDR_POINTMODMENUE);
    		break;

    	case OTLinie:
    	case OTLinie | OTFlaeche:
    		ObjectModifyMenu (&Wnd, Pnt, IDR_LINEMODMENUE);
    		break;

    	case OTFlaeche:
    		ObjectModifyMenu (&Wnd, Pnt, IDR_AREAMODMENUE);
    		break;
    }

    // wenn IN das Menü geklickt wurde, wird an dieser Stelle WorkMenuCommand() eingeschoben,
    // um den ausgewählten Menüpunkt zu behandeln
    m_pVWnd->Update();		// Hintergrund nach Zerlegen des Menüs sofort zeichnen
    m_bMenu = false;		// Menü wird nicht mehr angezeigt
    // wenn NEBEN das Menü geklickt wurde, wird an dieser Stelle LeftMouseDown() bzw.
    // RightMouseDown() eingeschoben

/* Können die nachfolgenden Zeilen wegen des am 24.02.99 in CGeoEditExtension::WindowsNotification
   (GeoEdit.cpp) eingefügten "case WM_MOUSEMOVE:" jetzt wegfallen ????????
// durch das Hintergrundzeichnen nach dem Zerlegen des Menüs wird die kurzzeitig angezeigte
// Sanduhr durch TRiAS wieder in den letzten Cursor zurück verwandelt; wenn der Anwender mit
// der Mausbedienung zu schnell ist, kann dieses Zurückverwandeln zu spät und damit verkehrt
// erfolgen; deshalb nachfolgende Vorsichtsmaßnahme
CursForm CF;	// aktuelle CursorForm

    m_wEdExSite->GetCursor (&CF);
    m_wEdExSite->SetCursor (CF, TRUE);
*/
	
    return S_OK;

} // RightMouseUp


// --------------------------------------------------------------------------------------------
// Doppelklick auf linke Maustaste
HRESULT CObjectModify::LeftDoubleClick (long hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    if (! m_wModOper.IsValid() || // es ist keine ModifyOperation aktiv
		m_bMenu)		// Menü wird angezeigt
		return S_FALSE;

    // eine ModifyOperation ist aktiv (z.B. LineElongation)
    try
    {
    WTRiASSysNotificationSink wSysNotSink (m_wModOper);

    	// Weiterleitung der WindowsMessage an aktive ModifyOperation
    	wSysNotSink->WindowsMessage (hWnd, uiMsg, wParam, lParam);
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return S_OK;

} // LeftDoubleClick

/*
// --------------------------------------------------------------------------------------------
// Windows-Timer, der aller halbe Sekunden kommt, abfragen
void CObjectModify::WindowsTimer (WPARAM wParam)
{
    if (1 == wParam)	// d.h. TIMER_HALFSECOND
    	m_wEdExSite->SetCursor (m_AktCurForm);
}
*/


// --------------------------------------------------------------------------------------------
// Ermittlung der Typen der ausgewählten Objekte
HRESULT CObjectModify::GetBelowObjTypes (void)
{
HRESULT hrRet = S_OK;	// return-Wert
short iOT;
WUnknown Unk;

    m_iAllOT = 0;
	m_lBelowLACnt = 0;

	try
	{
		for (m_wBelowObjs->Reset(); S_OK == m_wBelowObjs->Next (1, Unk.ppi(), NULL); )
		{
		WObjektGeometrie wObj (Unk);

    		wObj->GetObjTyp (&iOT);

    		if (OT_PUNKT == iOT)
    			m_iAllOT |= OTPunkt;
    		else if (OT_KANTE == iOT)
			{
    			m_iAllOT |= OTLinie;
				m_lBelowLACnt++;
			}
    		else if (OT_FLAECHE == iOT)
			{
    			m_iAllOT |= OTFlaeche;
				m_lBelowLACnt++;
			}
    		else 
    		{
    			_ASSERTE (iOT == OT_PUNKT || iOT == OT_KANTE || iOT == OT_FLAECHE);
    			hrRet = E_UNEXPECTED;	// sonst nur weitermachen
    		}
		}
	}
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

    return hrRet;

} // GetBelowObjTypes


// --------------------------------------------------------------------------------------------
// Testen, ob die m_wBelow-Objekte alles OFFENE Linienobjekte sind; wenn ja, dann ist der
// return-Wert "true"
bool CObjectModify::AllOpen (void)
{
WUnknown Unk;
short iOT;
long lCnt;
KoOrd* plXK; KoOrd* plYK;

    try
    {
    	for (m_wBelowObjs->Reset(); S_OK == m_wBelowObjs->Next (1, Unk.ppi(), NULL); )
    	{
		WObjektGeometrie wObj (Unk);

    		wObj->GetObjTyp (&iOT);

    		if (OT_KANTE != iOT)
    			return false;

    		wObj->GetCnt (&lCnt);
    		wObj->GetX ((void**)&plXK);
    		wObj->GetY ((void**)&plYK);

    		if (plXK[0] == plXK[lCnt-1] && plYK[0] == plYK[lCnt-1])
    			return false;
    	}
    }
    catch (_com_error&)
    {
    	return false;
    }

    return true;

} // AllOpen

// --------------------------------------------------------------------------------------------
// Testen, ob die m_wBelow-Objekte alles GESCHLOSSENE Linienobjekte sind; wenn ja, dann ist der
// return-Wert "true"
bool CObjectModify::AllClosed (void)
{
WUnknown Unk;
short iOT;
long lCnt;
KoOrd* plXK; KoOrd* plYK;

    COM_TRY {
    	for (m_wBelowObjs->Reset(); S_OK == m_wBelowObjs->Next (1, Unk.ppi(), NULL); /**/) {
		WObjektGeometrie wObj (Unk);

    		wObj->GetObjTyp (&iOT);

    		if (OT_KANTE != iOT)
    			return false;

    		wObj->GetCnt (&lCnt);
    		wObj->GetX ((void**)&plXK);
    		wObj->GetY ((void**)&plYK);

    		if (plXK[0] != plXK[lCnt-1] || plYK[0] != plYK[lCnt-1])
    			return false;
    	}
    } COM_CATCH_RETURN(false);
    return true;

} // AllOpen


// --------------------------------------------------------------------------------------------
// Testen, ob die m_wBelow-Objekte alle zur gleichen Datenquelle gehören; wenn ja, dann ist der
// return-Wert "true"
bool CObjectModify::OneDataSource (void)
{
#if _TRiAS_VER < 0x0300
	return true;
#else
ulong ulBelowCnt;	// Anzahl der Objekte, die unter der Mausspitze liegen

	m_wBelowObjs->GetCount (&ulBelowCnt);

	// wenn höchstens 1 Objekt unter der Mausspitze liegt bzw. wenn höchstens eine Datenquelle
	// geöffnet ist, dann ist der Test schon entschieden
	if (ulBelowCnt <= 1 || DEX_GetOpenConnectionCount (QDCAllOpen) <= 1)
		return true;

WUnknown Unk;
long lONr;

    try
    {
	WObjektGeometrie wObj;

   		m_wBelowObjs->Reset();

	HRESULT hr = m_wBelowObjs->Next (1, Unk.ppi(), NULL);

    	if (S_OK == hr) wObj = Unk;
		else return false;

		wObj->GetONr (&lONr);

	HPROJECT hPr = DEX_GetObjectProject (lONr);
		
		for ( ; S_OK == m_wBelowObjs->Next (1, Unk.ppi(), NULL); )
    	{
			wObj = Unk;
    		wObj->GetONr (&lONr);

    		if (hPr != DEX_GetObjectProject (lONr))
    			return false;
    	}
    }
    catch (_com_error&)
    {
    	return false;
    }

    return true;

#endif // _TRiAS_VER < 0x0300
} // OneDataSource
 

// --------------------------------------------------------------------------------------------
// Menüpunkt "Selbstinzidenzen bereinigen" evtl. eintragen, wenn
// - in der Registry der Eintrag "SelfTouch" steht
// - genau ein Linien- bzw. Flächenobjekt recherchiert wurde
// - dieses Objekt einen Selbstinzidenz-Fehler hat (Eintrag im Merkmal "Geometriefehler")
HRESULT CObjectModify::MenuSelfTouch (HMENU hMenu)
{
ResString rsSelfTouch (ResID (IDS_SELFTOUCH, pRF), 30);	
CCurrentUser cuExtConfig (KEY_READ, RegistryExtPathEdit);
DWORD dw;

	if (!cuExtConfig.GetDWORD (rsSelfTouch.Addr(), dw))
		return S_FALSE;		// kein Eintrag in Registry

    if (0 == (m_iAllOT & OTLinie) && 0 == (m_iAllOT & OTFlaeche))
		return S_FALSE;		// nicht nur LINIEN- und FLÄCHENobjekte ausgewählt

ulong ulBelowCnt;	// Anzahl der Objekte, die unter der Mausspitze liegen
long lONr;

	m_wBelowObjs->GetCount (&ulBelowCnt);

	if (ulBelowCnt > 1)
		return S_FALSE;		// es liegen mehrere Objekte unter der Mausspitze

    try
    {
	WUnknown Unk;
	WObjektGeometrie wObj;

   		m_wBelowObjs->Reset();

	HRESULT hr = m_wBelowObjs->Next (1, Unk.ppi(), NULL);

    	if (S_OK == hr) wObj = Unk;
		else _com_issue_error (hr);

		wObj->GetONr (&lONr);
    }
    catch (_com_error& e)
    {
		return _COM_ERROR (e);
    }

	GeoReinInterface();
	if (S_OK != FehlerhaftesObjekt (m_wGeoRein, lONr, '1'))
		return S_FALSE;		// Objekt hat keine Selbstinzidenz

UINT uiMOffset;		// MenuOffset(); ist in xtencatl.hxx für CTriasExtension definiert

    m_wEdExSite->GetMenuOffset (&uiMOffset);

int iItCnt = GetMenuItemCount (hMenu);	// Anzahl der schon vorhandenen Menüeinträge
int i = 0;

    if (OTLinie == m_iAllOT)
    {
		// Menüpunkt vor "Objekt(e) löschen" (genauer gesagt: vor dem Separator, der sich vor
		// dem Menüpunkt "Objekt(e) löschen" befindet) einfügen
    	// Position des Menüpunktes "Objekt(e) löschen" bestimmen
    	for (i = 0; i < iItCnt; i++)
    		if (IDM_OBJECTDEL+uiMOffset == GetMenuItemID (hMenu, i))
    			break;

    	// i ist die Position des Menüpunktes "Objekt(e) löschen"; um den neuen Menüpunkt
    	// "Selbstinzidenzen bereinigen" vor den davor befindlichen Separator einzufügen, wird
    	// in InsertMenu() der 2. Parameter auf i-1 gesetzt
	}
	else	// m_iAllOT == OTFlaeche
    {
		// Menüpunkt vor "Insel hinzufügen" (genauer gesagt: vor dem Separator, der sich vor
		// dem Menüpunkt "Insel hinzufügen" befindet) einfügen
    	for (i = 0; i < iItCnt; i++)
    		if (IDM_ISLANDADD+uiMOffset == GetMenuItemID (hMenu, i))
    			break;
	}

	InsertMenu (hMenu, i-1, MF_BYPOSITION|MF_STRING, IDM_OBJECTCUT+uiMOffset,
				ResString(ResID(IDS_CLEARSELFTOUCH,pRF),50).Addr());

	return S_OK;

} // MenuSelfTouch
 

// --------------------------------------------------------------------------------------------
// Menüpunkt "Gemeinsame Linie" deaktivieren, wenn
// - unter der Mausspitze keine Linie und keine Fläche liegt
// - es nicht noch mindestens eine weitere ausgewählte Linie bzw. Fläche gibt
HRESULT CObjectModify::MenuCommonBorder (HMENU hMenu)
{
short iOT;
long lSelLACnt = 0;	// Anzahl der ausgewählten Linien und Flächen

	COM_TRY
	{
	// alle ausgewählten, d.h. markierten Objekte geben lassen
	WEnumObjektGeometrie wAllSelObjs;

		THROW_FAILED_HRESULT (m_wTopObjs->GetEnumTopicalObjectsGeometry (TRUE, wAllSelObjs.ppi()));
	
	WUnknown Unk;

		for (wAllSelObjs->Reset(); S_OK == wAllSelObjs->Next (1, Unk.ppi(), NULL); )
		{
		WObjektGeometrie wObj (Unk);

			wObj->GetObjTyp (&iOT);
			if (OT_KANTE == iOT || OT_FLAECHE == iOT)
				lSelLACnt++;
			else continue;
		}
	}
	COM_CATCH;

	if (0 == m_lBelowLACnt || lSelLACnt <= m_lBelowLACnt)
	{
	UINT uiMOffset;		// MenuOffset(); ist in xtencatl.hxx für CTriasExtension definiert

		m_wEdExSite->GetMenuOffset (&uiMOffset);
    	EnableMenuItem (hMenu, IDM_COMMONBORDER+uiMOffset, MF_BYCOMMAND|MF_GRAYED);
	}

	return S_OK;

} // MenuCommonBorder


// --------------------------------------------------------------------------------------------
// wenn mehrere Objekte unter der Mausspitze liegen, dann die Singulartexte der Menü-Einträge
// durch Plural-Menütexte ersetzen
void CObjectModify::PluralTexts (HMENU hMenu, UINT uiMOffset)
{
// Stützpunkte modifizieren
UINT uiMenuState = GetMenuState (hMenu, IDM_VERTEXMOD+uiMOffset, MF_BYCOMMAND);

    if (uiMenuState != (UINT)-1)
    	ModifyMenu (hMenu, IDM_VERTEXMOD+uiMOffset, MF_BYCOMMAND|uiMenuState,
    				IDM_VERTEXMOD+uiMOffset, ResString(ResID(IDS_VERTICESMOD,pRF),50).Addr());

    // Stützpunkte hinzufügen
    uiMenuState = GetMenuState (hMenu, IDM_VERTEXADD+uiMOffset, MF_BYCOMMAND);
    if (uiMenuState != (UINT)-1)
    	ModifyMenu (hMenu, IDM_VERTEXADD+uiMOffset, MF_BYCOMMAND|uiMenuState,
    				IDM_VERTEXADD+uiMOffset, ResString(ResID(IDS_VERTICESADD,pRF),50).Addr());

    // Stützpunkte löschen
    uiMenuState = GetMenuState (hMenu, IDM_VERTEXDEL+uiMOffset, MF_BYCOMMAND);
    if (uiMenuState != (UINT)-1)
    	ModifyMenu (hMenu, IDM_VERTEXDEL+uiMOffset, MF_BYCOMMAND|uiMenuState,
    				IDM_VERTEXDEL+uiMOffset, ResString(ResID(IDS_VERTICESDEL,pRF),50).Addr());

    // Objekte drehen
    uiMenuState = GetMenuState (hMenu, IDM_OBJECTROT+uiMOffset, MF_BYCOMMAND);
    if (uiMenuState != (UINT)-1)
    	ModifyMenu (hMenu, IDM_OBJECTROT+uiMOffset, MF_BYCOMMAND|uiMenuState,
    				IDM_OBJECTROT+uiMOffset, ResString(ResID(IDS_OBJECTSROT,pRF),50).Addr());

    // Linien teilen
    uiMenuState = GetMenuState (hMenu, IDM_LINEPART+uiMOffset, MF_BYCOMMAND);
    if (uiMenuState != (UINT)-1)
    	ModifyMenu (hMenu, IDM_LINEPART+uiMOffset, MF_BYCOMMAND|uiMenuState,
    				IDM_LINEPART+uiMOffset, ResString(ResID(IDS_LINESPART,pRF),50).Addr());

    // Linien verlängern
    uiMenuState = GetMenuState (hMenu, IDM_LINEELONG+uiMOffset, MF_BYCOMMAND);
    if (uiMenuState != (UINT)-1)
    	ModifyMenu (hMenu, IDM_LINEELONG+uiMOffset, MF_BYCOMMAND|uiMenuState,
    				IDM_LINEELONG+uiMOffset, ResString(ResID(IDS_LINESELONG,pRF),50).Addr());

    // Linien zu Flächen machen
    uiMenuState = GetMenuState (hMenu, IDM_LINETOAREA+uiMOffset, MF_BYCOMMAND);
    if (uiMenuState != (UINT)-1)
    	ModifyMenu (hMenu, IDM_LINETOAREA+uiMOffset, MF_BYCOMMAND|uiMenuState,
    				IDM_LINETOAREA+uiMOffset, ResString(ResID(IDS_LINESTOAREA,pRF),50).Addr());

    // Inseln hinzufügen
    uiMenuState = GetMenuState (hMenu, IDM_ISLANDADD+uiMOffset, MF_BYCOMMAND);
    if (uiMenuState != (UINT)-1)
    	ModifyMenu (hMenu, IDM_ISLANDADD+uiMOffset, MF_BYCOMMAND|uiMenuState,
    				IDM_ISLANDADD+uiMOffset, ResString(ResID(IDS_ISLANDSADD,pRF),50).Addr());

    // Inseln löschen
    uiMenuState = GetMenuState (hMenu, IDM_ISLANDDEL+uiMOffset, MF_BYCOMMAND);
    if (uiMenuState != (UINT)-1)
    	ModifyMenu (hMenu, IDM_ISLANDDEL+uiMOffset, MF_BYCOMMAND|uiMenuState,
    				IDM_ISLANDDEL+uiMOffset, ResString(ResID(IDS_ISLANDSDEL,pRF),50).Addr());

    // Objekte löschen
    uiMenuState = GetMenuState (hMenu, IDM_OBJECTDEL+uiMOffset, MF_BYCOMMAND);
    if (uiMenuState != (UINT)-1)
    	ModifyMenu (hMenu, IDM_OBJECTDEL+uiMOffset, MF_BYCOMMAND|uiMenuState,
    				IDM_OBJECTDEL+uiMOffset, ResString(ResID(IDS_OBJECTSDEL,pRF),50).Addr());
} // PluralTexts


// --------------------------------------------------------------------------------------------
// Menü generieren
void CObjectModify::ObjectModifyMenu (pWindow pW, Point Pt, uint resID)
{
Menu ModifyMenu (ResID (resID, pRF));
HMENU hMenu = ModifyMenu.Handle (API_MENU_HMENU);

    if (NULL == hMenu) return;	// Ressource nicht gefunden
    
// Menü generieren und Offsets addieren
// mit GetSubMenu() erhält man das Handle für das zu generierende Menü als Sub-Menü von hMenu
HMENU hSubMenu = GetSubMenu (hMenu, 0);	// Sub-Menü holen

UINT uiMOffset;	// MenuOffset(); ist in xtencatl.hxx für CTriasExtension definiert

    m_wEdExSite->GetMenuOffset (&uiMOffset);
    AddMenuOffset (hSubMenu, uiMOffset);

    // Konvertierung der Client-Koordinaten von Pt in Screen-Koordinaten
    ClientToScreen (m_pVWnd->Handle (API_CLIENT_HWND), (LPPOINT)&Pt);

    // Anzeige des Menüs an der Pt-Position und Kennzeichnung der ausgewählten
    // Menü-Einträge; an dieser Stelle wird MenuInit eingeschaltet
    TrackPopupMenu (hSubMenu, 0, Pt.X(), Pt.Y(), 0, pW->Handle (API_CLIENT_HWND), NULL);

} // ObjectModifyMenu


// --------------------------------------------------------------------------------------------
// Bereich ermitteln, in dem das Objekt pIOG modifiziert wurde, um diesen Ausschnitt neu zu
// zeichnen;
// ist pIOG Fläche, wird dafür ein achsenparalleles Rechteck aus der alten, der neuen
// Stützpunktposition und aus dem vorhergehenden und nachfolgenden Stützpunkt der
// entsprechenden Kontur gebildet;
// ist pIOG eine Linie, entfällt für Rechteckbildung der vorhergehende oder nachfolgende
// Stützpunkt, wenn der verschobene Stützpunkt der erste bzw. letzte gewesen ist;
 // ist pIOG ein Punkt wird  der rechteckige Bereich nur aus der alten und der neuen
// Stützpunktposition gebildet;
// bVtDel besagt, daß (k)ein Stützpunkt gelöscht wurde (true/false)
RECT CObjectModify::SectorDefine (IObjektGeometrie* pIOG, long lModPktX, long lModPktY,
    							  long lInd, bool bVtDel)
{
    _ASSERTE (pIOG != NULL);

    if (! pIOG)
    {
    RECT Rec;

    	Rec.left = m_pVWnd->CanvasRect().Left();
    	Rec.top = m_pVWnd->CanvasRect().Top();
    	Rec.right = m_pVWnd->CanvasRect().Right();
    	Rec.bottom = m_pVWnd->CanvasRect().Bottom();

    	return Rec;		// gesamter Bildschirm
    }

short iOT;
long lCnt;
KoOrd* plXK; KoOrd* plYK;

    pIOG->GetObjTyp (&iOT);
    pIOG->GetCnt (&lCnt);
    pIOG->GetX ((void**)&plXK);
    pIOG->GetY ((void**)&plYK);

    _ASSERTE (lInd <= lCnt);

    if (lInd == lCnt)	// passiert bei Löschen des letzten Stützpunktes
    	lInd = lCnt - 1;

KoOrd x = plXK[lInd];			// neue x- bzw.
KoOrd y = plYK[lInd];			//  y-Koordinate des modifizierten Stützpunktes
KoOrd xmin = min (x, lModPktX);	// Vergleich mit den alten Koordinaten des
KoOrd xmax = max (x, lModPktX);	//  modifizierten Punktes
KoOrd ymin = min (y, lModPktY);
KoOrd ymax = max (y, lModPktY);

    switch (iOT)
    {
    	case OT_PUNKT:
    		break;
    		
    	case OT_KANTE:
    		if (lInd > 0)			// es wurde nicht der 1. Stützpunkt modifiziert, dann
    		{						//  Einbeziehung des vorhergehenden Stützpunktes
    			xmin = min (xmin, plXK[lInd-1]);
    			xmax = max (xmax, plXK[lInd-1]);
    			ymin = min (ymin, plYK[lInd-1]);
    			ymax = max (ymax, plYK[lInd-1]);
    		}
    		if (lInd < lCnt-1 &&	// es wurde nicht der letzte Stützpunkt modifiziert und
    			! bVtDel)			//  es wurde kein Stützpunkt gelöscht,
    		{						//  dann Einbeziehung des nachfolgenden Stützpunktes
    			xmin = min (xmin, plXK[lInd+1]);
    			xmax = max (xmax, plXK[lInd+1]);
    			ymin = min (ymin, plYK[lInd+1]);
    			ymax = max (ymax, plYK[lInd+1]);
    		}
			if (plXK[0] == plXK[lCnt-1] && plYK[0] == plYK[lCnt-1])	// Kante geschlossen
			{
				if (0 == lInd)				// der 1. Stützpunkt wurde modifiziert
				{
    				xmin = min (xmin, plXK[lCnt-2]);
    				xmax = max (xmax, plXK[lCnt-2]);
    				ymin = min (ymin, plYK[lCnt-2]);
    				ymax = max (ymax, plYK[lCnt-2]);
				}
				else if (lInd == lCnt - 1)	// der letzte Stützpunkt wurde modifiziert
				{
    				xmin = min (xmin, plXK[1]);
    				xmax = max (xmax, plXK[1]);
    				ymin = min (ymin, plYK[1]);
    				ymax = max (ymax, plYK[1]);
				}
			}
    		break;
    		
    	case OT_FLAECHE:
    	{
    	long lIndv, lIndn;	// Indizes des vorhergehenden bzw. nachfolgenden Stützpunktes
    	
    		pIOG->IndexVorNach (lInd, &lIndv, &lIndn);	
    		
    		xmin = min (xmin, plXK[lIndv]);
    		xmax = max (xmax, plXK[lIndv]);
    		ymin = min (ymin, plYK[lIndv]);
    		ymax = max (ymax, plYK[lIndv]);

    		if (! bVtDel)	// nicht Stützpunkt löschen
    		{
    			xmin = min (xmin, plXK[lIndn]);
    			xmax = max (xmax, plXK[lIndn]);
    			ymin = min (ymin, plYK[lIndn]);
    			ymax = max (ymax, plYK[lIndn]);
    		}
    		break;
    	}

    	default:
    		_ASSERTE (false);
    		break;
    }
    
Point PLO = BSKoordinaten (xmin, ymax);
Point PRU = BSKoordinaten (xmax, ymin);
RECT Rec;

    Rec.left = PLO.X();
    Rec.top = PLO.Y();
    Rec.right = PRU.X();
    Rec.bottom = PRU.Y();

    return Rec;

} // SectorDefine


// --------------------------------------------------------------------------------------------
// Bezug zur Erweiterung "GeometrieBereinigung" herstellen, wenn noch m_bGeoRein == false
HRESULT CObjectModify::GeoReinInterface (void)
{
    if (m_bGeoRein) return S_FALSE;

HRESULT hrRet;

    if (m_Site)
    	hrRet = m_Site->GetXtension (CLSID_GeometrieBereinigung, IID_IExtendGeoRein,
    								 (LPVOID*)&m_wGeoRein);
    else hrRet = E_UNEXPECTED;

    if (FAILED (hrRet) ||	// Fehler, z.B. GeoRein.ext nicht verfügbar
    	! m_Site)
    {
    ResString resText (ResID (IDS_NOGEOREIN, pRF), 250);
    ResString resCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);
    	
    	MessageBox (__hWndM, resText.Addr(), resCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
    	return hrRet;
    }

    m_bGeoRein = true;
    return S_OK;

} // GeoReinInterface   


// --------------------------------------------------------------------------------------------
// Testen, ob der Punkt, bei dem mit der rechten Maustaste das Menü erzeugt wurde, an der
// Strecke des aktivierten (blinkenden) lONr-Objektes steht bzw. ob der betreffende Punkt an
// mehr als einem aktivierten Objekt liegt
// return-Werte:
//   S_OK:	  der rechte-Maustaste-Punkt m_PktRM liegt an dem aktivierten lONr-Objekt; es ist
//            das ERSTE Objekt, das gefunden wurde
//   S_FALSE: das lONr-Objekt ist keine Fläche bzw. m_PktRM liegt nicht an dem aktivierten
//            lONr-Objekt
//   E_FAIL:  der rechte-Maustaste-Punkt m_PktRM liegt an mehr als einem aktivierten Objekt
HRESULT CObjectModify::TestActObject (long lONr)
{
    if (OT_FLAECHE != DEX_GetObjectType (lONr))
    	return S_FALSE;

WObjektGeometrie wObj;	// ObjektGeometrie des lONr-Objektes

    try
    {
    // neues IObjektGeometrie erzeugen und ...
    WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);	// throws_com_error

    	THROW_FAILED_HRESULT (wIObj->InitObjGeometry (lONr));	// ... initialisieren

    	wObj = wIObj;
    }
    catch (_com_error& e)
    {
    	return _COM_ERROR (e);
    }

KoOrd* plXK; KoOrd* plYK;
short iKCnt;	// Anzahl der Konturen
long* plCnt;	// Anzahl der Stützpunkte in den Konturen

    wObj->GetX ((void**)&plXK);
    wObj->GetY ((void**)&plYK);
    wObj->GetKCnt (&iKCnt);
    wObj->GetLPCnt (&plCnt);

KoOrd lAbst;	// Abstand des Punktes m_PktRM von Strecke (x0, y0, x1, y1) in Maximum-Norm
EPunkt LPkt;	// für Routine LotPktStrecke(): wird hier aber nicht ausgewertet
long lAInd = 0;	// Startwert für Anfangsindex einer Kontur
long lEInd = 0;	// Startwert für Endindex einer Kontur (eigentlich richtiger: Anfangsindex der
    			// nächsten Kontur)

    for (int i = 0; i < iKCnt; i++)
    {
    	lEInd += plCnt[i];

    	for (long j = lAInd; j < lEInd-1; j++)
    	{			
    	KoOrd x0 = plXK[j];
    	KoOrd y0 = plYK[j];
    	KoOrd x1 = plXK[j+1];
    	KoOrd y1 = plYK[j+1];

    		// der nachfolgende Test muß mit der gleichen Routine durchgeführt werden, die
    		// hinter ObjektGeometrie::PunktAnStrecke() steckt
    		if (Strecke(x0, y0, x1, y1).LotPktStrecke (m_PktRM, lAbst, LPkt) &&
    			lAbst < m_lEpsilon)
    		{
    			if (0 != m_lAktONr && -1 != m_lAktONr)
    				return E_FAIL;	// m_PktRM liegt an mehr als einem aktivierten Objekt

    			m_lAktONr = lONr;
    			m_iRecKInd = i;
    			m_lRecStInd = j;
    			return S_OK;
    		}
    	}
    	lAInd = lEInd;
    }

    return S_FALSE;

} // TestActObject


///////////////////////////////////////////////////////////////////////////////////////////////
// statische globale Funktion
// --------------------------------------------------------------------------------------------
// Modifikation eines Menü's (addieren des Menüoffsets)
static void AddMenuOffset (HMENU hMenu, int iOffset)
{
    if (0 == hMenu) return;		// nur für gültige Menü's

int nCount = GetMenuItemCount (hMenu);
char MenuEntry[DEX_MENUNAMELEN+1];

    for (int wItem = 0; wItem < nCount; wItem++)
    {
    UINT uiMenuState = GetMenuState (hMenu, wItem, MF_BYPOSITION);
    UINT uiMenuID = GetMenuItemID (hMenu, wItem);

    	if (-1 == uiMenuID)		// PopUpMenu
    	{
    		AddMenuOffset (GetSubMenu (hMenu, wItem), iOffset);	
    		continue;
    	}
    	if (uiMenuState & (MF_MENUBARBREAK | MF_MENUBREAK | MF_SEPARATOR))
    		continue;
    	GetMenuString (hMenu, wItem, MenuEntry, DEX_MENUNAMELEN, MF_BYPOSITION);
    	ModifyMenu (hMenu, wItem, MF_BYPOSITION | uiMenuState, uiMenuID+iOffset, MenuEntry);
    }
} // AddMenuOffset
