// Definitionen: Funktionen für die Erweiterung "Geometrie-Editierung"
// File: GeoEdit.cpp


#include "GeoEditP.h"

#include <resstrg.h>		// IDS_UIFORMAT

#include "version.h"		// GEOEDIT_MAJORVERSION, ...

// Voraussetzungen für Arbeit mit Toolbars
#include <toolguid.h>		// CLSID_TRiASUIOwner in uiowner.h
#include <itoolbar.h>		// ITRiASUIOwner in uiowner.h
#include "uiowner.h"		// CUIOwner
DefineSmartInterface (TRiASBar);			// WTRiASBar
DefineSmartInterface (TRiASBarContainer);	// WTRiASBarContainer
DefineSmartInterface (TRiASUIOwner);		// WTRiASUIOwner

// weitere Header-Files
#include <initguid.h>		// nur in einem Modul notwendig (zum Linken von IID_* und CLSID_*)
#include <bscrguid.h>		// CLSID_MacroScriptExtension
#include <registrx.hxx>		// CCurrentUser
#include <undoguid.h>		// IID_IUndoRedoCreateText, CLSID_UndoRedoObject

#include <Esnecil.h>

#include "EditDlg.h"			// CEditDlg
#include "EditBaseDlg.h"		// CEditBaseDlg
#include "EditCoordDlg.h"		// CEditCoordDlg
#include "TopicalObjects.h"		// CTopicalObjects
#include "DragMultiLine.h"		// CDragMultiLine
#include "NewPoint.h"			// CNewPoint
#include "NewLine.h"			// CNewLine
#include "NewArea.h"			// CNewArea
#include "ObjectModify.h"		// CObjectModify
#include "VertexMove.h"			// CVertexMove
#include "VertexAdd.h"			// CVertexAdd
#include "LineElongation.h"		// CLineElongation
#include "AreaPartition.h"		// CAreaPartition
#include "IslandAdd.h"			// CIslandAdd
#include "MakeRectangular.h"	// CMakeRectangular
#include "ObjectMove.h"			// CObjectMove
#include "Designing.h"			// CDesigning
#include "RestrictLine.h"		// CRestrictLine
#include "RestrictCursor.h"		// CRestrictCursor
#include "EnumObjektGeometrie.h"

// nur für GeoMedia
//#include "GeometryDigitizeService.h"
//#include "GeometryEditService.h"

#include "GeoEdit.h"		// Header für diese Erweiterung
#include "CommonBorder.h"


#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if _TRiAS_VER < 0x0400
extern DWORD g_dwVer4;
#endif // _TRiAS_VER < 0x0400


///////////////////////////////////////////////////////////////////////////////////////////////
// Das Makro OBJECT_ENTRY ordnet einer Klasse (z.B. CGeoEditExtension) den ClassID zu und
// übernimmt außerdem die Registrierung in der RegDB.
BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_GeometrieEditierung2, CGeoEditExtension)
	OBJECT_ENTRY(CLSID_TopicalObjects, CTopicalObjects)
	OBJECT_ENTRY(CLSID_DragMultiLine, CDragMultiLine)
	OBJECT_ENTRY(CLSID_NewPoint, CNewPoint)
	OBJECT_ENTRY(CLSID_NewLine, CNewLine)
	OBJECT_ENTRY(CLSID_NewArea, CNewArea)
	OBJECT_ENTRY(CLSID_ObjectModify, CObjectModify)
	OBJECT_ENTRY(CLSID_VertexMove, CVertexMove)
	OBJECT_ENTRY(CLSID_VertexAdd, CVertexAdd)
	OBJECT_ENTRY(CLSID_LineElongation, CLineElongation)
	OBJECT_ENTRY(CLSID_AreaPartition, CAreaPartition)
	OBJECT_ENTRY(CLSID_IslandAdd, CIslandAdd)
	OBJECT_ENTRY(CLSID_MakeRectangular, CMakeRectangular)
	OBJECT_ENTRY(CLSID_ObjectMove, CObjectMove)
	OBJECT_ENTRY(CLSID_Designing, CDesigning)
	OBJECT_ENTRY(CLSID_RestrictLine, CRestrictLine)
	OBJECT_ENTRY(CLSID_RestrictCursor, CRestrictCursor)
	OBJECT_ENTRY(CLSID_EnumObjektGeometrie, CEnumObjektGeometrie)
	OBJECT_ENTRY(CLSID_CommonBorder, CCommonBorder)

	// nur für GeoMedia
//	OBJECT_ENTRY(CLSID_GeometryDigitizeService, CGeometryDigitizeService)
//	OBJECT_ENTRY(CLSID_GeometryEditService, CGeometryEditService)

END_OBJECT_MAP()


// --------------------------------------------------------------------------------------------
// mit der folgenden Funktion wird die ObjectMap in den ClassFactory-Mechanismus dieser
// Erweiterung eingebunden
_ATL_OBJMAP_ENTRY* GetObjectMap (void)
{
	return ObjectMap;	// liefert ObjectMap
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Der ProgID (hier 'TRiAS.Editierung.2') ist eine Zeichenkette, die die Erweiterung in der
// RegDB repräsentiert. Das Format sollte beibehalten werden. Die '... .2' steht für die
// VersionsNummer. Der KlassenName (hier die Stringresource hinter IDS_LONGCLASSNAME) ist eine
// normal-lesbare Zeichenkette, die lokalisiert wird (deshalb in der Ressource) und die
// Bezeichnung der Erweiterung definiert.
BOOL UpdateRegistry (BOOL bRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (bRegister)	// RegDB initialisieren ...
	{
	bool bRet = ExtOleRegisterExtensionClass (g_hInstance, CLSID_GeometrieEditierung2,
											  TEXT("TRiAS.Editierung.2"), IDS_LONGCLASSNAME,
											  GEOEDIT_MAJORVERSION, GEOEDIT_MINORVERSION,
											  EFPreLoad
	// Durch die Herausnahme der beiden nachfolgenden Flags wird die Erweiterung nicht
	// entladbar und systemintern
	//										  |EFUnLoadable|EFVisible
											  );

	CCurrentUser cuExtConfig (RegistryExtPathEdit, true);

	// ... durch Eintrag der Schlüssel "MinMarkGroesse" bzw. "MaxMarkGroesse" für Unter- bzw.
	// Obergrenze der Pixelgröße der Markierungsquadrate
	ResourceFile RF (g_pDLLName);
	ResString UMarkGroesse (ResID (IDS_UMARKGROESSE, &RF), 30);
	ResString OMarkGroesse (ResID (IDS_OMARKGROESSE, &RF), 30);

	DWORD dwUWert = iUGr;	// default-Wert des Schlüssels "MinMarkGroesse"
	DWORD dwOWert = iOGr;	//  bzw. des Schlüssels "MaxMarkGroesse" (aus EditKonst.h)

		// wenn Schlüssel "MinMarkGroesse" bzw. "MaxMarkGroesse" bisher noch nicht in der RegDB
		// existieren, dann jetzt anlegen
		if (!cuExtConfig.GetDWORD (UMarkGroesse.Addr(), dwUWert))
			cuExtConfig.SetDWORD (UMarkGroesse.Addr(), dwUWert);

		if (!cuExtConfig.GetDWORD (OMarkGroesse.Addr(), dwOWert))
			cuExtConfig.SetDWORD (OMarkGroesse.Addr(), dwOWert);

	// Eintrag der Schlüssel "MarkColor", "MarkColorBegin", "MarkColorEnd" und
	// "MarkColorThickness" für farbliche Gestaltung der Markierungsquadrate
	ResString resMarkColor (ResID (IDS_MARKCOLOR, &RF), 30);
	ResString resMarkColorBegin (ResID (IDS_MARKCOLORBEGIN, &RF), 30);
	ResString resMarkColorEnd (ResID (IDS_MARKCOLOREND, &RF), 30);
	ResString resMarkBoundThick (ResID (IDS_MARKBOUNDTHICK, &RF), 30);

	DWORD dwColor0 = ulGW0;	// default-Werte (aus EditKonst.h)
	DWORD dwColor1 = ulGW1;
	DWORD dwColor2 = ulGW2;
	DWORD dwThickness = iThick;

		if (!cuExtConfig.GetDWORD(resMarkColor.Addr(), dwColor0))
			cuExtConfig.SetDWORD(resMarkColor.Addr(), dwColor0);

		if (!cuExtConfig.GetDWORD(resMarkColorBegin.Addr(), dwColor1))
			cuExtConfig.SetDWORD (resMarkColorBegin.Addr(), dwColor1);

		if (!cuExtConfig.GetDWORD(resMarkColorEnd.Addr(), dwColor2))
			cuExtConfig.SetDWORD(resMarkColorEnd.Addr(), dwColor2);

		if (!cuExtConfig.GetDWORD(resMarkBoundThick.Addr(), dwThickness))
			cuExtConfig.SetDWORD(resMarkBoundThick.Addr(), dwThickness);
		
		return bRet;
	}

	else			// RegDB säubern
		// die eigenen Einträge müßten hier wieder gelöscht werden !!!
		return ExtOleUnregisterClass (CLSID_GeometrieEditierung2, TEXT("TRiAS.Editierung.2"));

	return true;	// alles ok
}



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
ResourceFile* pRF = NULL;



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
// Die nutzerdefinierte Erweiterung muß von der Klasse 'CTriasExtension' abgeleitet sein,
// welche wiederum (wenn erforderlich) als einzige Parameter die ResID's der im Hauptfenster
// und ORFenster einzuhängenden Menüs übergeben bekommt.
CGeoEditExtension::CGeoEditExtension (void)
				 : CTriasExtension()		// keine separaten Menüs
{
// Member initialisieren
	m_bEditTBarInst = false;	// Editierwerkzeuge sind (noch) nicht installiert
	m_bDesignTBarInst = false;	// Designingwerkzeuge sind (noch) nicht installiert
	m_bExtActive = false;		// Erweiterung ist (noch) nicht aktiviert
	m_iPrevTool = 0;			// "Pfeil"-ToolButton
	m_bVtIndicate = false;		// Stützpunkte sind noch nicht markiert
	m_lRegONr1 = 0;				// Objektnummern der Bezugsobjekte für
	m_lRegONr2 = 0;				//  Konstruktionshilfslinien
	m_iROInd = 1;				// Index für Konstruktionshilfslinien
	m_bOpParked = false;		// keine EditierOperation geparkt

	m_CF = CURSFORM_PFEIL;
	m_EditCursor = NULL;		// Cursor für Editierung
	m_VertexCursor = NULL;		// Cursor auf Stützpunkt (Geometrie-Modifizierung)
	m_LineCursor = NULL;		// Cursor auf Strecke
	m_DeleteCursor = NULL;		// Cursor auf Stützpunkt und CTRL-Taste gedrückt
	m_InsideCursor = NULL;		// Cursor innerhalb eines markierten Objektes
	m_GrabCursor = NULL;		// Cursor auf Stützpunkt (Stützpunkt-Angrabben)
	m_OldCursor = NULL;			// vorhergehender eigener Cursor
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Im folgenden werden alle durch diese Erweiterung überladenen virtuellen Funktionen definiert

// --------------------------------------------------------------------------------------------
// Folgende Funktion wird einmalig nach der erfolgreichen Installation der Erweiterung durch
// TRiAS gerufen. Hier erfolgen alle notwendigen Initialisierungen.
STDMETHODIMP_(BOOL) CGeoEditExtension::InitExtension (short iMode) 
{
	// globale Parameter initialisieren
	pRF = &RF();

char cSichtName[MAXVIEWNAMESIZE+1] = { '\0' };     // Name der Sicht (NICHT mit "string")

	if (DEX_TestActiveProject() &&    // ein Projekt ist schon geöffnet
		0 != DEX_GetActiveSight (cSichtName))
		m_bSight = true;		// eine Sicht ist schon ausgewählt
	else
		m_bSight = false;		// noch keine Sicht ausgewählt

	// eigene Windows-Message anmelden (2 Parameter)
	RegisterNotification (WM_MOUSEMOVE, false);
	RegisterNotification (WM_WM_DESIGNBUILDEND, false);

	// TRiAS-Messages anfordern (nur 1 Parameter)
	// ich interessiere mich für die von TRiAS verschickten Meldungen, für
	RegisterNotification (DEX_SETACTIVETOOL);	// neues Werkzeug selektiert
	RegisterNotification (DEX_PROJECTOPEN);		// Projekt wird geöffnet
	RegisterNotification (DEX_SIGHTSELECTED);	// eine Sicht wird ausgewählt
	RegisterNotification (DEX_PROJECTCLOSE);	// Projekt wird geschlossen
	RegisterNotification (DEX_OBJECTDEACTIVATED);
	RegisterNotification (DEX_DELOBJECT);

	// Cursoren anlegen
	DELETE_OBJ (m_EditCursor);
	DELETE_OBJ (m_VertexCursor);
	DELETE_OBJ (m_LineCursor);
	DELETE_OBJ (m_DeleteCursor);
	DELETE_OBJ (m_InsideCursor);
	DELETE_OBJ (m_GrabCursor);
	m_EditCursor = new Pointer (ResID (IDC_CUREDIT, pRF));
	m_VertexCursor = new Pointer (ResID (IDC_CURVERTEX, pRF));
	m_LineCursor = new Pointer (ResID (IDC_CURLINE, pRF));
	m_DeleteCursor = new Pointer (ResID (IDC_CURDELETE, pRF));
	m_InsideCursor = new Pointer (ResID (IDC_CURINSIDE, pRF));
	m_GrabCursor = new Pointer (ResID (IDC_CURGRAB, pRF));
	if (!m_EditCursor || !m_VertexCursor || !m_LineCursor || !m_DeleteCursor ||
		!m_InsideCursor || !m_GrabCursor)
	{
		DELETE_OBJ (m_EditCursor);
		DELETE_OBJ (m_VertexCursor);
		DELETE_OBJ (m_LineCursor);
		DELETE_OBJ (m_DeleteCursor);
		DELETE_OBJ (m_InsideCursor);
		DEX_Error (RC_geoedit, EC_NOMEMORY);
		return false;
	}

	try
	{
		// Objekt erzeugen, welches die ausgewählten TRiAS-GeometrieObjekte enthält
		m_wTopObjs = WTopicalObjects (CLSID_TopicalObjects);
		m_wTopObjs->SetXtensionSite (m_pXtnSite);
	}
	catch (...)
	{
		return false;
	}

	// neue Werkzeuge installieren
	if (!m_bEditTBarInst) {
		if (SUCCEEDED(InstallEditToolbar()))
			m_bEditTBarInst = true;
	}

	if (!m_bDesignTBarInst) {
	// #HK000906: TRiAS4 hat Konstruktionswerkzeuge standardmäßig
#if _TRiAS_VER < 0x0400
	CCurrentUser regCfg (KEY_READ, g_cbRegConfig);
	DWORD dwVer4 = 0;

		if (regCfg.GetDWORD (TEXT("FakeTRiAS4"), dwVer4) && 0 != dwVer4) {
		// schon jetzt so tun, als obs die TRiAS4 wäre
			if (SUCCEEDED(InstallDesignToolbar()))
				m_bDesignTBarInst = true;
		}
		else {
		// wie bisher nach speziellem Registryeintrag suchen
		ResString rsDesignMode (ResID (IDS_DESIGNMODE, pRF), 30);	
		CCurrentUser cuExtConfig (KEY_READ, RegistryExtPathEdit);
		DWORD dwKey = -1;

			if (cuExtConfig.GetDWORD (rsDesignMode.Addr(), dwKey) &&
				DESIGNKEY == dwKey)		// 08.06.99
			{
				InstallDesignToolbar();
				m_bDesignTBarInst = true;
			}
		}
#else
		if (SUCCEEDED(InstallDesignToolbar()))
			m_bDesignTBarInst = true;
#endif // _TRiAS_VER < 0x0400
	}

// GeoRein.ext automatisch nachladen
ResString resGeoRein (ResID (IDS_GEOREIN, pRF), 20);

	DEX_ExternalLoadExtension (resGeoRein.Addr());

// bei BScript anmelden
	RegisterBScriptExtension();

	return CTriasExtension::InitExtension(iMode);
} // InitExtension


///////////////////////////////////////////////////////////////////////////////////////////////
//
bool CGeoEditExtension::RegisterBScriptExtension (void)
{
	try
	{
		// diese Erweiterung als public BasicExtension registrieren
		m_wBScript = WExtendBScript (CLSID_MacroScriptExtension);
		THROW_FAILED_HRESULT (m_wBScript->RegisterExtModule (g_pDLLName));

	}
	catch (_com_error&)
	{
		return false;
	}

	return true;
}


// --------------------------------------------------------------------------------------------
STDMETHODIMP_(BOOL) CGeoEditExtension::UnLoadExtension (void)
{
	// Interface's wieder freigeben
	m_wBScript.Assign(NULL);	// BScript freigeben
	m_wObjOper.Assign (NULL);	// ObjOper freigeben

	// TRiAS-Messages wieder abmelden
	// ich interessiere mich nicht mehr für die von TRiAS verschickten Meldungen
	UnRegisterNotification (DEX_DELOBJECT);
	UnRegisterNotification (DEX_OBJECTDEACTIVATED);
	UnRegisterNotification (DEX_PROJECTCLOSE);		// Projekt wird geschlossen
	UnRegisterNotification (DEX_SIGHTSELECTED);		// eine Sicht wird ausgewählt
	UnRegisterNotification (DEX_PROJECTOPEN);		// Projekt wird geöffnet
	UnRegisterNotification (DEX_SETACTIVETOOL);		// Auswahl einer Editier-Icone

	// eigene Windows-Message wieder abmelden (2 Parameter)
	UnRegisterNotification (WM_WM_DESIGNBUILDEND, false);
	UnRegisterNotification (WM_MOUSEMOVE, false);

	if (m_wTopObjs.IsValid())
	{
	long lTOCnt = 0;	// Anzahl der ausgewählten Objekte

		m_wTopObjs->GetCount (&lTOCnt);

		// wenn die Erweiterung zwar entladen, das Projekt aber noch nicht geschlossen wird
		if (lTOCnt > 0 &&					// und mindestens 1 Objekt ausgewählt ist und
			m_bVtIndicate)					// und Stützpunkte markiert sind,
			m_wTopObjs->VerticesUnIndicate();	// dann Stützpunktmarkierungen löschen

		m_bVtIndicate = false;
	}

	// Werkzeuge wieder entfernen
	if (m_bEditTBarInst)
	{
		RemoveEditToolbar();
		m_bEditTBarInst = false;
	}

	if (m_bDesignTBarInst)
	{
		RemoveDesignToolbar();
		m_bDesignTBarInst = false;
	}

	// Standard-Cursor wieder einstellen
	DELETE_OBJ (m_EditCursor);
	DELETE_OBJ (m_VertexCursor);
	DELETE_OBJ (m_LineCursor);
	DELETE_OBJ (m_DeleteCursor);
	DELETE_OBJ (m_InsideCursor);
	DELETE_OBJ (m_GrabCursor);
	if (CURSFORM_PFEIL != m_CF) SetCursor();

	// Interface's wieder freigeben
	if (m_wTopObjs.IsValid())
	{
		m_wTopObjs->SetXtensionSite (NULL);
		m_wTopObjs.Assign (NULL);
	}

	if (m_wEditOper.IsValid())
	{
		m_wEditOper->SetEditExtensionSite (NULL);
		m_wEditOper.Assign (NULL);
	}

	m_wRestrLine1.Assign (NULL);
	m_wRestrLine2.Assign (NULL);


	return CTriasExtension::UnLoadExtension();

} // UnLoadExtension


// --------------------------------------------------------------------------------------------
// Diese Funktion dient der Behandlung der MenüKommandos der Erweiterung
STDMETHODIMP_(BOOL) CGeoEditExtension::MenuCommand (WPARAM wParam, HWND hWnd)
{
	try
	{
	WMenuHandling wMenuHandl (m_wEditOper);

		THROW_FAILED_HRESULT (wMenuHandl->WorkMenuCommand (wParam, hWnd));
	}
	catch (_com_error&)
	{		
		return false;
	}
	return true;
}
 

// --------------------------------------------------------------------------------------------
// Diese Funktion wird gerufen, wenn ein Menü auf dem Bildschirm erscheinen soll
STDMETHODIMP_(BOOL) CGeoEditExtension::MenuInit (HMENU hMenu, LPARAM lParam, HWND hWnd)
{
	try
	{
	WMenuHandling wMenuHandl (m_wEditOper);

		THROW_FAILED_HRESULT (wMenuHandl->WorkMenuInit (hMenu, lParam, hWnd));
	}
	catch (_com_error&)
	{		
		return false;
	}
	return true;
}
 

// --------------------------------------------------------------------------------------------
// Diese Funktion wird gerufen, wenn der Cursor über die Menü-Einträge gezogen wird
STDMETHODIMP_(BOOL) CGeoEditExtension::MenuSelect (UINT uiMenuID, HMENU hMenu, HWND hWnd)
{
	try
	{
	WMenuHandling wMenuHandl (m_wEditOper);

		THROW_FAILED_HRESULT (wMenuHandl->WorkMenuSelect (uiMenuID, hMenu, hWnd));
	}
	catch (_com_error&)
	{		
		return false;
	}
	return true;
}


// --------------------------------------------------------------------------------------------
// Diese Funktion wird bei Systemereignissen diverser Natur gerufen, z.B. bei Anklicken sowohl
// der neuen als auch der anderen Iconen
STDMETHODIMP_(LRESULT) CGeoEditExtension::Notification (WPARAM wMsg, LPARAM lParam)
{	
	switch (wMsg)
	{
		case DEX_SETACTIVETOOL:
			SetActiveTool (lParam);
			break;

		case DEX_PROJECTOPEN:		// Projekt wird geöffnet
			CursorForEditTool();
			break;

		case DEX_SIGHTSELECTED:
			if (lParam != 0)
				m_bSight = true;
			else
				m_bSight = false;
			break;

		case DEX_PROJECTCLOSE:		// Projekt wird geschlossen
			ResetTopicalObjects();			
			DeleteRestrictLines();
			ReactivateParkedOperation();
			break;

		case DEX_OBJECTDEACTIVATED:	// ein Objekt wurde deselektiert (DEX_OBJECTDEACTIVATED ist
									// dafür richtig und NICHT etwa DEX_OBJECTUNSELECTED !!!!)
		case DEX_DELOBJECT:			// bzw. ein Objekt wurde gelöscht
			// lParam ist die Objektnummer des soeben deselektierten bzw. gelöschten Objektes
			if (lParam == m_lRegONr1)
			{
				if (m_wEditOper.IsValid()) m_wEditOper->DeleteRestrictedCursor();
				if (m_wRestrLine1.IsValid())
				{
					m_wRestrLine1->UnDraw();
					m_wRestrLine1.Assign (NULL);
				}
				m_iROInd = 1;
				m_lRegONr1 = 0;
			}
			if (lParam == m_lRegONr2)	// NICHT "else if", da m_lRegONr1 == m_lRegONr2 sein kann
			{
				if (m_wEditOper.IsValid()) m_wEditOper->DeleteRestrictedCursor();
				if (m_wRestrLine2.IsValid())
				{
					m_wRestrLine2->UnDraw();
					m_wRestrLine2.Assign (NULL);
				}
				(m_lRegONr1) ? (m_iROInd = 2) : (m_iROInd = 1);
				m_lRegONr2 = 0;
			}
			if (m_wEditOper.IsValid())
				m_wEditOper->InformRestrictLinesState (m_wRestrLine1, m_wRestrLine2);

			if (ID_TOOL_PUNKTEDIT == m_iPrevTool || ID_TOOL_LINIENEDIT == m_iPrevTool ||
				ID_TOOL_FLAECHENEDIT == m_iPrevTool || ID_TOOL_DESIGN == m_iPrevTool ||
				ID_TOOL_DESIGNSTOP == m_iPrevTool)
				SetCursor (CURSFORM_CROSS);	// eigentlich ausführlicher: RefreshCursorForm(), indem getestet
											// wird, ob sich Cursor in der Nähe einer Strecke, in einem
											// Stützpunkt usw. befindet !!!!!!!!!!!!!!!!!!!!
			else
				SetCursor();	// wieder Standard-Cursor einstellen


			break;


		default:	// Notification's der Basisklasse
			break;
	}

	return CTriasExtension::Notification (wMsg, lParam);

} // Notification


// --------------------------------------------------------------------------------------------
STDMETHODIMP_(LRESULT) CGeoEditExtension::WindowsNotification (UINT wMsg, WPARAM, LPARAM)
{
	switch (wMsg)
	{
		case WM_MOUSEMOVE:
		{
		// mit jedem MouseMove wird die von mir vorgegebene CursorForm vorsichtshalber noch
		// einmal rekonstruiert, da sie durch Hintergrundzeichnen verändert worden sein kann
		CursForm CF;
 
			GetCursor (&CF);
			SetCursor (CF, FALSE);
			break;
		}

		// "Hilfslinie bilden" beenden, d.h. die Editierung erfolgt jetzt auf den Hilfslinien
		// (die Hilfslinien selbst werden also logischerweise an dieser Stelle NICHT gelöscht)
		case WM_WM_DESIGNBUILDEND:
			ReactivateParkedOperation();
			break;

		default:
			_ASSERTE (false);
			break;
	}
	
	return false;

} // WindowsNotification


// --------------------------------------------------------------------------------------------
// Anzahl der ausgewählten Objekte bestimmen
long CGeoEditExtension::TopicalObjsCount (void)
{
long lTOCnt = 0;

	_ASSERTE (m_wTopObjs.IsValid());

	if (m_wTopObjs.IsValid()) m_wTopObjs->GetCount (&lTOCnt);
	return lTOCnt;

} // TopicalObjsCount


///////////////////////////////////////////////////////////////////////////////
// #HK020307
bool CGeoEditExtension::ResetTopicalObjects()
{
	if (m_wTopObjs.IsValid()) {
	long lTOCnt;		// Anzahl der ausgewählten Objekte

		m_wTopObjs->GetCount (&lTOCnt);
		if (lTOCnt > 0 &&		// wenn mindestens 1 Objekt ausgewählt ist und
			m_bVtIndicate)		// Stützpunkte markiert sind,
			m_wTopObjs->VerticesUnIndicate();	//  dann Stützpunktmarkierungen löschen

		m_bVtIndicate = false;
		m_wTopObjs->DeleteTopicalObjects (TRUE);		// bisherigen Inhalt löschen
		return true;
	}
	return false;
}

// --------------------------------------------------------------------------------------------
// Test, ob mindestens eine Konstruktionshilfslinie existiert, dann Rückgabe von true
bool CGeoEditExtension::IsRestrictLineExist (void)
{
	if (m_wRestrLine1.IsValid() || m_wRestrLine2.IsValid())
		return true;
	return false;
}



// --------------------------------------------------------------------------------------------
// ein Tool wurde aktiviert/passiviert
HRESULT CGeoEditExtension::SetActiveTool (long lTool)
{
	// ein EditierTool wurde ausgewählt (GeoEditierung ist damit aktiviert)
	if (ID_TOOL_PUNKTEDIT == lTool || ID_TOOL_LINIENEDIT == lTool ||
		ID_TOOL_FLAECHENEDIT == lTool || ID_TOOL_MODIFYOBJ == lTool ||
		ID_TOOL_MOVEOBJ == lTool ||
		ID_TOOL_DESIGN == lTool || ID_TOOL_DESIGNSTOP == lTool)
	{
		RETURN_FAILED_HRESULT (EditToolChecked (lTool));
	}

	// es wurde kein EditierTool ausgewählt (GeoEditierung ist damit passiviert)
	else if (m_bExtActive)		// (bis jetzt war aber eins ausgewählt)
	{
		DeleteRestrictLines();
		ReactivateParkedOperation();	// eine evtl. geparkte EditierOperation wieder ausparken
		m_bOpParked = false;	// keine EditierOperation mehr geparkt

		if (m_wEditOper.IsValid())
		{
			m_wEditOper->SetEditExtensionSite (NULL);
			m_wEditOper.Assign (NULL);
		}

		SetCursor();	// wieder Standard-Cursor einstellen

	long lTOCnt;		// Anzahl der ausgewählten Objekte

		m_wTopObjs->GetCount (&lTOCnt);

		if (lTOCnt > 0 &&		// wenn mindestens 1 Objekt ausgewählt ist und
			m_bVtIndicate)		// Stützpunkte markiert sind,
			m_wTopObjs->VerticesUnIndicate();	//  dann Stützpunktmarkierungen löschen

		m_bVtIndicate = false;
		m_bExtActive = false;	// Erweiterung wurde passiviert
	}

	m_iPrevTool = lTool;	// aktuelles Werkzeug retten für den Fall, daß Aktivierung
							// fehlgeschlagen ist
	return S_OK;

} // SetActiveTool


// --------------------------------------------------------------------------------------------
// es wurde ein EditierTool ausgewählt
HRESULT CGeoEditExtension::EditToolChecked (long lTool)
{
	m_bExtActive = true;	// Erweiterung wurde aktiviert

	try
	{
		switch (lTool)
		{
			case ID_TOOL_PUNKTEDIT:		// Punktobjekt erfassen
			{
				// eine (möglicherweise bis jetzt) aktive IEditOperation abmelden
				if (m_wEditOper.IsValid())
				{
					m_wEditOper->SetEditExtensionSite (NULL);
					m_wEditOper.Assign(NULL);
					if (ID_TOOL_DESIGN == m_iPrevTool) TerminateParkedOperation();
				}

			WEditOperation wEditOper (CLSID_NewPoint);		// throws_com_error

				THROW_FAILED_HRESULT (wEditOper->SetEditExtensionSite (this));
				m_wEditOper = wEditOper;
				m_wTDropTarget.Assign(NULL);
				break;
			}

			case ID_TOOL_LINIENEDIT:	// Linienobjekt erfassen
			{
				// eine (möglicherweise bis jetzt) aktive IEditOperation abmelden
				if (m_wEditOper.IsValid())
				{
					m_wEditOper->SetEditExtensionSite (NULL);
					m_wEditOper.Assign(NULL);
					if (ID_TOOL_DESIGN == m_iPrevTool) TerminateParkedOperation();
				}

			WEditOperation wEditOper (CLSID_NewLine);		// throws_com_error

				THROW_FAILED_HRESULT (wEditOper->SetEditExtensionSite (this));
				m_wEditOper = wEditOper;
				m_wTDropTarget.Assign(NULL);
				break;
			}

			case ID_TOOL_FLAECHENEDIT:	// Flächenobjekt erfassen
			{
				// eine (möglicherweise bis jetzt) aktive IEditOperation abmelden
				if (m_wEditOper.IsValid())
				{
					m_wEditOper->SetEditExtensionSite (NULL);
					m_wEditOper.Assign(NULL);
					if (ID_TOOL_DESIGN == m_iPrevTool) TerminateParkedOperation();
				}

			WEditOperation wEditOper (CLSID_NewArea);		// throws_com_error

				THROW_FAILED_HRESULT (wEditOper->SetEditExtensionSite (this));
				m_wEditOper = wEditOper;
				m_wTDropTarget.Assign(NULL);
				break;
			}

			case ID_TOOL_MODIFYOBJ:		// Geometrie modifizieren
			{
				// eine (möglicherweise bis jetzt) aktive IEditOperation abmelden
				if (m_wEditOper.IsValid())
				{
					m_wEditOper->SetEditExtensionSite (NULL);
					m_wEditOper.Assign(NULL);
					if (ID_TOOL_DESIGN == m_iPrevTool) TerminateParkedOperation();
				}

			WEditOperation wEditOper (CLSID_ObjectModify);	// throws_com_error

				THROW_FAILED_HRESULT (wEditOper->SetEditExtensionSite (this));
				m_wEditOper = wEditOper;
				m_wTDropTarget.Assign(NULL);
				break;
			}

			case ID_TOOL_MOVEOBJ:		// Objekt kopieren/verschieben
			{
				// eine (möglicherweise bis jetzt) aktive IEditOperation abmelden
				if (m_wEditOper.IsValid())
				{
					m_wEditOper->SetEditExtensionSite (NULL);
					m_wEditOper.Assign(NULL);
					if (ID_TOOL_DESIGN == m_iPrevTool) TerminateParkedOperation();
				}

			WEditOperation wEditOper (CLSID_ObjectMove);	// throws_com_error

				THROW_FAILED_HRESULT (wEditOper->SetEditExtensionSite (this));
				m_wEditOper = wEditOper;

				THROW_FAILED_HRESULT (m_wEditOper->QueryInterface (IID_ITRiASDropTarget,
																   m_wTDropTarget.ppv()));
				_ASSERTE (m_wTDropTarget.IsValid());

				break;
			}

			case ID_TOOL_DESIGN:		// Hilfslinien bilden
			{
			// Lizensierung testen
			#if _TRiAS_VER < 0x0400
				if (0 != g_dwVer4) 
			#endif // _TRiAS_VER < 0x0400
				{
				VERIFYLICENSE VL;

					INITSTRUCT(VL, VERIFYLICENSE);
					VL.iMode = VERIFYMODE_LessOrEqual;
					VL.lLevelOrOption = CKILEVEL_PLUS;
					if (!DEX_VerifyLicenseLevel(VL))
						return E_FAIL;
				}

				if (m_wEditOper.IsValid())
				{
					m_wParkEditOper = m_wEditOper;
					m_bOpParked = true;	// EditierOperation erst einmal bzw. immer noch geparkt

					m_wEditOper->SetEditExtensionSite (NULL);
					m_wEditOper.Assign(NULL);
				}

			WEditOperation wEditOper (CLSID_Designing);	// throws_com_error (ab zum Konstruktor)

				THROW_FAILED_HRESULT (wEditOper->SetEditExtensionSite (this));
				m_wEditOper = wEditOper;
				m_wTDropTarget.Assign(NULL);
				m_bVtIndicate = false;
				break;
			}

			case ID_TOOL_DESIGNSTOP:	// Editierung auf Hilfslinien beenden
			{
			// Lizensierung testen
			#if _TRiAS_VER < 0x0400
				if (0 != g_dwVer4) 
			#endif // _TRiAS_VER < 0x0400
				{
				VERIFYLICENSE VL;

					INITSTRUCT(VL, VERIFYLICENSE);
					VL.iMode = VERIFYMODE_LessOrEqual;
					VL.lLevelOrOption = CKILEVEL_PLUS;
					if (!DEX_VerifyLicenseLevel(VL))
						return E_FAIL;
				}

				_ASSERTE (ID_TOOL_DESIGN == m_iPrevTool);
				_ASSERTE (m_wEditOper.IsValid());

				DeleteRestrictLines();
				m_wEditOper->InformRestrictLinesState (m_wRestrLine1, m_wRestrLine2);
				SetCursor (CURSFORM_CROSS);
				break;
			}

			default:
				_ASSERTE (false);

		} // switch
	}

	catch (_com_error& e)
	{
		// wenn Aktivierung fehlschlägt, dann das vorhergehende Tool wieder aktivieren
		DEX_ChangeActiveTool (m_iPrevTool);

		if (m_wEditOper.IsValid())
		{
			m_wEditOper->SetEditExtensionSite (NULL);
			m_wEditOper.Assign(NULL);
		}

		return _COM_ERROR (e);
	}

long lTOCnt;	// Anzahl der ausgewählten Objekte

	m_wTopObjs->GetCount (&lTOCnt);

	if (lTOCnt > 0)						// wenn mindestens 1 Objekt selektiert ist
	{
		if (ID_TOOL_MOVEOBJ != lTool)	//  und NICHT "Objekte verschiebene/kopieren" ausgewählt wurde
		{
			RemoveObjects();					// Selektion neu einlesen
			if (! m_bVtIndicate)
			{
				m_wTopObjs->VerticesIndicate();	//  dann Stützpunkte markieren
				m_bVtIndicate = true;
			}
		}
		else if (m_bVtIndicate)
		{
			m_wTopObjs->VerticesUnIndicate();		// sonst Markierungen löschen
			RemoveObjects();						// Selektion neu einlesen
			m_bVtIndicate = false;
		}
	}

	return S_OK;

} // EditToolChecked


// --------------------------------------------------------------------------------------------
// Editiert-Cursor einstellen, wenn beim Öffnen eines Projektes schon eines der Tools für die
// Neueditierung ausgewählt wurde; dann return-Wert "true"; wurde Cursor nicht modifiziert, ist
// der return-Wert "false"
bool CGeoEditExtension::CursorForEditTool (void)
{
int iActTool = DEX_GetActiveTool();		// aktiviertes Tool

	if (m_bExtActive &&		// Erweiterung ist aktiviert
		m_bEditTBarInst &&	// Editierwerkzeuge sind installiert
		(ID_TOOL_PUNKTEDIT == iActTool ||	// ein Tool für Neueditierung ausgewählt
		 ID_TOOL_LINIENEDIT == iActTool || ID_TOOL_FLAECHENEDIT == iActTool))
	{
		SetCursor (CURSFORM_CROSS);
		return true;
	}
	return false;

} // CursorForEditTool


// --------------------------------------------------------------------------------------------
// die geparkte EditierOperation wieder aktivieren
void CGeoEditExtension::ReactivateParkedOperation (void)
{
	if (ID_TOOL_DESIGN != m_iPrevTool)
		return;

	if (m_wParkEditOper.IsValid())
	{
		// die bis jetzt aktive IEditOperation "Hilfslinien bilden" abmelden ...
		if (m_wEditOper.IsValid()) m_wEditOper->SetEditExtensionSite (NULL);
		m_wEditOper.Assign(NULL);

		// ... und die geparkte IEditOperation "Erfassung" wieder aktivieren
		m_wEditOper = m_wParkEditOper;
		m_wEditOper->SetEditExtensionSite (this);
		m_wEditOper->InformRestrictLinesState (m_wRestrLine1, m_wRestrLine2);

		// das erneute Zeichen der Konstruktionshilfslinien ist an dieser Stelle für den Fall
		// notwendig, daß die 1. Hilfslinie durch den Dialog für die 2. Hilfslinie teilweise
		// gelöscht wird
		if (m_wRestrLine1.IsValid() && m_wRestrLine2.IsValid())
		{
			m_wRestrLine1->Draw();
			m_wRestrLine2->Draw();
		}
	}
	else
		_ASSERTE (m_wParkEditOper.IsValid());

	m_bOpParked = false;

} // ReactivateParkedOperation


// --------------------------------------------------------------------------------------------
// eine evtl. geparkte EditOperation "vergessen"
void CGeoEditExtension::TerminateParkedOperation (void)
{
	DeleteRestrictLines();

	m_bOpParked = false;	// eine evt. geparkte IEditOperation ignorieren

// rudimentäre temporäre Objekte auf dem Bildschirm löschen
KoOrd lXmin, lXmax, lYmin, lYmax;

	if (S_FALSE == m_wTopObjs->GetTopicalObjectsRectangle (FALSE, &lXmin, &lXmax, &lYmin, &lYmax))
		return;		// es gibt keine temporären Objekte
	
Point PLU = BSKoordinaten (lXmin, lYmin);
Point PRO = BSKoordinaten (lXmax, lYmax);
int iMarkGr;

    m_wTopObjs->GetMarkerSizeBS (&iMarkGr);

Rectangle Rec;

	Rec.Left()   = PLU.X() - iMarkGr - iSicher;
	Rec.Right()  = PRO.X() + iMarkGr + iSicher;
	Rec.Top()    = PRO.Y() + iMarkGr + iSicher;
	Rec.Bottom() = PLU.Y() - iMarkGr - iSicher;
    DEX_RePaintRectWait (Rec);
    MWind()->Update();		// sofort löschen

// rudimentäre temporäre Objekte aus den Topical-Objekten löschen
    m_wTopObjs->DeleteTopicalObjects (FALSE);

} // TerminateParkedOperation


// --------------------------------------------------------------------------------------------
// Text in der Statuszeile entsprechend der CursorForm modifizieren
void CGeoEditExtension::StatuszeileModifizieren (CursForm CF)
{
ResString rsText (ResID (IDS_CURVERTEXMOVE, pRF), 100);		// case CURSFORM_STERN

	switch (CF)
	{
		case CURSFORM_CROSS:
			rsText = ResString (ResID (IDS_CUREDIT, pRF), 100);
			break;

		case CURSFORM_TRENNER:
			rsText = ResString (ResID (IDS_CURVERTEXADD, pRF), 100);
			break;

		case CURSFORM_KREUZ:
			rsText = ResString (ResID (IDS_CURVERTEXDEL, pRF), 100);
			break;

		case CURSFORM_INOBJEKT:
			rsText = ResString (ResID (IDS_CUROBJECTMOVE, pRF), 100);
			break;

		case CURSFORM_FANGEN:
			rsText = ResString (ResID (IDS_INMARKER, pRF), 100);
			break;
	}

	DEX_SetMessageStringNoKickIdle (rsText.Addr());

} // StatuszeileModifizieren



///////////////////////////////////////////////////////////////////////////////////////////////
// IEditExtensionSite-Methoden

STDMETHODIMP CGeoEditExtension::GetXtensionSite (IUnknown** ppIUnk)
{
	if (NULL == ppIUnk)
		return E_POINTER;

WTriasXtensionSite wSite;

	if (SUCCEEDED(CTriasExtension::GetXtensionSite (wSite.ppi())))
	{
		// "detach": Weiterreichen des Pointers ohne Release() und erneutes AddRef()
		*ppIUnk = wSite.detach();
		return S_OK;
	}
	return E_NOINTERFACE;
}


// --------------------------------------------------------------------------------------------
// MenuOffset geben lassen
STDMETHODIMP CGeoEditExtension::GetMenuOffset (UINT* pMenuOffset)
{
	*pMenuOffset = MenuOffset();
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// neuen Cursor einstellen und Anzeige in Statuszeile entsprechend der CursorForm modifizieren
STDMETHODIMP CGeoEditExtension::SetCursor (CursForm CF, BOOL bPseudoMove)
{
	if (NULL == MVWind())	// Projekt wird geschlossen oder kein Projekt geöffnet
		return S_FALSE;

	if (CURSFORM_PFEIL == CF)	// Cursor soll auf Standardform "Pfeil" zurückgestellt werden
	{
		if (NULL != MVWind()->GetPointer())
		{
			m_OldCursor = MVWind()->ChangePointer (NULL);
			DEX_SetMessageStringNoKickIdle ("");
		}
	}

	else						// Cursor soll Sonderform bekommen
	{
	Pointer* pCursor = NULL;

		if (CURSFORM_CROSS == CF) pCursor = m_EditCursor;
		else if (CURSFORM_STERN == CF) pCursor = m_VertexCursor;
		else if (CURSFORM_TRENNER == CF) pCursor = m_LineCursor;
		else if (CURSFORM_KREUZ == CF) pCursor = m_DeleteCursor;
		else if (CURSFORM_INOBJEKT == CF) pCursor = m_InsideCursor;
		else if (CURSFORM_FANGEN == CF) pCursor = m_GrabCursor;
		else
		{
			_ASSERTE (false);
			return E_UNEXPECTED;
		}

		if (pCursor != MVWind()->GetPointer())
		{
			m_OldCursor = MVWind()->ChangePointer (pCursor);
			pCursor->Show();
			StatuszeileModifizieren (CF);
		}
	}

	m_CF = CF;		// aktuelle CursorForm retten

	if (bPseudoMove)
	{
	POINT PT;

		GetCursorPos (&PT);			// Pseudo-MouseMove
		SetCursorPos (PT.x, PT.y);
	}

	return S_OK;

} // SetCursor


// --------------------------------------------------------------------------------------------
STDMETHODIMP CGeoEditExtension::GetCursor (CursForm* pCursor)
{
	*pCursor = m_CF;
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Liefert die ausgewählten Objekte
STDMETHODIMP CGeoEditExtension::CreateInterfaceTO (ITopicalObjects** ppITO)
{
	if (NULL == ppITO)
		return E_POINTER;

	try
	{
	WTopicalObjects wITO (m_wTopObjs);

		*ppITO = wITO.detach();
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}
	return S_OK;
}


// --------------------------------------------------------------------------------------------
// EditierDialog anzeigen;
// in ulCnt wird die Anzahl und in ppIOG werden die ObjektGeometrien der aktuell editierten
// Objekte übergeben;
// wenn Linienobjekte verlängert werden sollen, werden in iCloseCnt, plCloseX und plCloseY
// die Anzahl und die Koordinaten der Endpunkte dieser Linienobjekte erwartet;
// in piResult wird das Ergebnis der DialogBedienung (OK, Abbrechen, Fortsetzen, Inselbeginn)
// zurückgegeben
STDMETHODIMP CGeoEditExtension::ShowEditDialog (LPCSTR pcCapt, LPCSTR pcRegKey, ulong ulCnt,
	 IUnknown** ppIOG, int* piGrabCnt, long* pGrabPktX, long* pGrabPktY, HRESULT hrComBorder,
	 long lComONr, int iCloseCnt, long* plCloseX, long* plCloseY, int* piResult)
{
	_ASSERTE (pcRegKey != NULL);
	_ASSERTE (piResult != NULL);

// Neueditierung (true) oder Modifizierung (false), also z.B. Linienverlängerung bzw.
// Inselergänzung
bool bNewEdit = (0 == strcmp (g_cbGeoEditNewPoint, pcRegKey) ||
				 0 == strcmp (g_cbGeoEditNewLine, pcRegKey) ||
				 0 == strcmp (g_cbGeoEditNewArea, pcRegKey));

// !!!! es wird vorläufig nur EIN ppIOG-Objekt berücksichtigt !!!!!
WObjektGeometrie wObj = *ppIOG;		// mit implizitem QueryInterface

CEditDlg sheetED (pcCapt, wObj, lComONr, piGrabCnt);
// eigene Pages zum	Einfügen in sheetED
CEditBaseDlg pageEB (pGrabPktX, pGrabPktY, hrComBorder, iCloseCnt,
					 plCloseX, plCloseY, bNewEdit);
CEditCoordDlg pageEC (iCloseCnt, plCloseX, plCloseY);

	sheetED.AddPage (&pageEB);	// 1. Page einfügen
	sheetED.AddPage (&pageEC);	// nächste Page hinzufügen

	// zusätzliche Pages über die Registry nachladen
	sheetED.LoadExtPagesFromRegistry (pcRegKey, ulCnt, ppIOG);

	sheetED.Show();

	if (piGrabCnt) *piGrabCnt = sheetED.GetGrabCnt();

	*piResult = sheetED.Result();

int iMarkGr;	// Markergröße
Rectangle Rec;	// rechteckiger Bereich, der (evtl.) gezeichnet werden soll

	m_wTopObjs->GetMarkerSizeBS (&iMarkGr);
	wObj->RectangleToDraw2 ((RECT*)&Rec, iMarkGr);

HRESULT hrRet = S_OK;

	switch (*piResult)
	{
		case IDOK:
			if (bNewEdit)
			{
			BSTR bsObjName = A2BSTR("");	// noch leerer Objektname  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

				hrRet = StoreNewObject (wObj, bsObjName);
				if (S_FALSE == hrRet) {
				// Objekt wurde wieder gelöscht, IDCANCEL simulieren
					if (piGrabCnt) 
						*piGrabCnt = 0;
					DEX_RePaintRectWait (Rec);	// Objekt auf Bildschirm durch Zeichnen löschen
					*piResult = IDCANCEL;
					return S_FALSE;
				}
			}
			// die Linienverlängerungen werden in LineElongation.cpp abgespeichert;
			// Flächenobjekte mit hinzugefügten Inseln werden in IslandAdd.cpp abgespeichert
			else if	(0 != strcmp (g_cbGeoEditLineElongat, pcRegKey) &&
					 0 != strcmp (g_cbGeoEditIslandAdd, pcRegKey))
			{
				_ASSERTE (false);
				hrRet = E_UNEXPECTED;
			}

			if (piGrabCnt) *piGrabCnt = 0;

			// für "Insel hinzufügen" erfolgt das Zeichnen wegen evtl. Geometriefehler auf
			// jeden Fall in StoreAreaWithNewIsland()
			if (0 != strcmp (g_cbGeoEditIslandAdd, pcRegKey))
				DEX_RePaintRectWait (Rec);
			break;

		case IDCANCEL:
			if (piGrabCnt) *piGrabCnt = 0;
			DEX_RePaintRectWait (Rec);	// Objekt auf Bildschirm durch Zeichnen löschen
			break;

		case IDB_CONTINUE:
		case IDB_ISLAND:
			break;

		default:
			_ASSERTE (false);
			hrRet = E_UNEXPECTED;
			break;
	}

	return hrRet;

} // ShowEditDialog


// --------------------------------------------------------------------------------------------
// neue Objekt(e) nach TRiAS speichern
STDMETHODIMP CGeoEditExtension::StoreNewObject (IUnknown* pIOG, BSTR bsObjName)
{
	_ASSERTE (pIOG != NULL);

	USES_CONVERSION;	// legt _convert für OLE2A() an

WObjektGeometrie wObj;

	try
	{
		wObj = pIOG;		// mit implizitem QueryInterface
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

CEierUhr Wait (MVWind());

ulong ulIdent = (ulong)-1;

	wObj->GetIdent (&ulIdent);	// Identifikator abfragen

#if _TRiAS_VER < 0x0300
	if (0 == DEX_GetROMode())				// Datenbank nicht schreibgeschützt (R/W-Modus)
#else
	if (0 == DEX_GetROModeIdent (ulIdent))	// Objektklasse nicht schreibgeschützt
#endif // _TRiAS_VER < 0x0300

		// OGNewObject:     permanentes Objekt in Datenbank aufnehmen
		// OGForceGeometry: auch außerhalb des aktuellen Projekt-Containers speichern
		// OGForceGeoError: Objekt wird bei Geometriefehler von GEOREIN abgewiesen
		// OGAskWhenError:  im Fehlerfall wird Anwender vor dem Abspeichern noch einmal gefragt
		// OGAddToView:     Identifikator zur Sicht hinzufügen
		wObj->SetFlags (OGNewObject | OGForceGeometry | OGForceGeoError | OGAskWhenError |
						OGAddToView);
	else
		// OGTempObject:	temporäres Objekt
		wObj->SetFlags (OGTempObject);

#if _TRiAS_VER < 0x0300
HRESULT hrRet = wObj->GeometrieAnTRiAS (true, NULL);
#else
INT_PTR hPr = reinterpret_cast<INT_PTR>(DEX_GetObjectsProject (ulIdent));
HRESULT hrRet = wObj->GeometrieAnTRiASEx (hPr, true, NULL);
#endif // _TRiAS_VER < 0x0300
	
	// wenn Objekt in DB eingespeichert wurde (hrRet == S_OK oder S_FALSE), dann auch
	// Objektname und UniqueIdent wegschreiben
	if (SUCCEEDED(hrRet))
	{
	long lNeuON;    // neue Objektnummer (von TRiAS bei Einspeicherung vergeben)
			
		wObj->GetONr (&lNeuON);	// neue Objektnummer abfragen

		// Objektname eintragen
		WriteFeatureText (lNeuON, DEX_GetObjNameMCode(ulIdent), TT_Objekt, OLE2A(bsObjName));

		// hr == S_OK bedeutet, daß Objekt fehlerfrei abgespeichert wurde;
		// hr == S_FALSE bedeutet, daß Objekt fehlerhaft abgespeichert wurde, in diesem Fall
		// wurde durch GeoRein.ext schon ein UniqueIdent vergeben
		if (S_OK == hrRet)		// UniqueIdent ergänzen
		{
		string sUIText;
		ResString resText (ResID (IDS_UIFORMAT, pRF), 20);

			Format (sUIText, (char*)resText.Addr(), lNeuON);
#if _TRiAS_VER < 0x0300
			WriteFeatureText (lNeuON, DEX_GetUniqueIdentMCode(), TT_Objekt, sUIText);
#else
			WriteFeatureText (lNeuON, DEX_GetUniqueIdentMCodeEx (DEX_GetObjectProject(lNeuON)),
																 TT_Objekt, sUIText);
#endif // _TRiAS_VER < 0x0300
		}

	// Mitteilung, daß NeuEditierung beendet
		if (DEXN_ObjectCreated (lNeuON)) {
		// jemand hatte nun doch noch was dagegen
			DEX_DeleteObject(lNeuON);		// wieder löschen
			return S_FALSE;
		}
	}
				
	return hrRet;

} // StoreNewObject


// --------------------------------------------------------------------------------------------
// GeoEdit liefert Pointer für Konstruktionshilfslinie an die EditierOperation
STDMETHODIMP CGeoEditExtension::GetRestrictLine (IRestrictLine** ppRestrLine)
{
	if (NULL == ppRestrLine)
		return E_POINTER;

HRESULT hrRet = S_OK;

	if (3 == m_iROInd) m_iROInd = 1;	// höchstens 2 Konstruktionshilfslinien

	if (1 == m_iROInd)
	{
		if (m_wEditOper.IsValid()) m_wEditOper->DeleteRestrictedCursor();
		if (m_wRestrLine1.IsValid())
		{
			m_wRestrLine1->UnDraw();
			m_wRestrLine1.Assign (NULL);
		}
		*ppRestrLine = m_wRestrLine1.detach();
		m_lRegONr1 = 0;
	}
	else if (2 == m_iROInd)
	{
		if (m_wEditOper.IsValid()) m_wEditOper->DeleteRestrictedCursor();
		if (m_wRestrLine2.IsValid())
		{
			m_wRestrLine2->UnDraw();
			m_wRestrLine2.Assign (NULL);
		}
		*ppRestrLine = m_wRestrLine2.detach();
		m_lRegONr2 = 0;
	}
	else
	{
		_ASSERTE (m_iROInd == 1 || m_iROInd == 2);
		hrRet = E_UNEXPECTED;
	}

	return hrRet;

} // GetRestrictLine


// --------------------------------------------------------------------------------------------
// GeoEdit bekommt von der EditierOperation die Objektnummer des Bezugsobjektes und die
// initialisierte Konstruktionshilfslinie zurück
STDMETHODIMP CGeoEditExtension::SetRestrictLine (long lRegONr, IRestrictLine* pRestrLine)
{
	if (1 == m_iROInd)
	{
		m_lRegONr1 = lRegONr;
		m_wRestrLine1.Assign (NULL);
		m_wRestrLine1 = pRestrLine;
	}
	else if (2 == m_iROInd)
	{
		m_lRegONr2 = lRegONr;
		m_wRestrLine2.Assign (NULL);
		m_wRestrLine2 = pRestrLine;
	}
	else
		_ASSERTE (m_iROInd == 1 || m_iROInd == 2);

	m_iROInd++;

	return S_OK;

} // SetRestrictLine


// --------------------------------------------------------------------------------------------
// Löschen der Konstruktionshilfslinien in GeoEdit
STDMETHODIMP CGeoEditExtension::DeleteRestrictLines (void)
{
	if (m_wEditOper.IsValid()) m_wEditOper->DeleteRestrictedCursor();

	if (m_wRestrLine1.IsValid())
	{
		m_wRestrLine1->UnDraw();
		m_wRestrLine1.Assign (NULL);
	}
	if (m_wRestrLine2.IsValid())
	{
		m_wRestrLine2->UnDraw();
		m_wRestrLine2.Assign (NULL);
	}

	m_lRegONr1 = 0;
	m_lRegONr2 = 0;
	m_iROInd = 1;

	return S_OK;

} // DeleteRestrictLines



///////////////////////////////////////////////////////////////////////////////////////////////
// IEditExternalObjects-Methoden

// Fügt ein Objekt zur Menge der ausgewählten Objekte hinzu
STDMETHODIMP CGeoEditExtension::AddObject (void)
{
	return E_NOTIMPL;
}


// --------------------------------------------------------------------------------------------
// Liefert ein Objekt aus der Menge der ausgewählten Objekte
STDMETHODIMP CGeoEditExtension::GetObject (void)
{
	return E_NOTIMPL;
}


// --------------------------------------------------------------------------------------------
// Löscht ein Objekt aus der Menge der ausgewählten Objekte
STDMETHODIMP CGeoEditExtension::RemoveObject (void)
{
	return E_NOTIMPL;
}


// --------------------------------------------------------------------------------------------
// Fügt extern bereitgestellte Objekte zu den ausgewählten Objekten hinzu
STDMETHODIMP CGeoEditExtension::AddObjects (IDispatch* pIDisp)
{
	try
	{
	WQueryEnumLONG QE (pIDisp);
	WEnumLONG Enum;

		THROW_FAILED_HRESULT(QE->QueryEnumLONG (Enum.ppi()));

		return m_wTopObjs->InitWithExternalObjects (WEnumObjectsByNumber(Enum));
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

} // AddObjects


// --------------------------------------------------------------------------------------------
// Liefert die ausgewählten Objekte
STDMETHODIMP CGeoEditExtension::GetObjects (IDispatch** ppIDisp, long lObjTypes)
{
HRESULT hrRet = S_OK;	// return-Wert
WEnumObjectsByNumber wEnum;
HRESULT hr = m_wTopObjs->GetEnumTopicalObjects (wEnum.ppi());

	if (FAILED(hr)) return hr;

WObjektGeometrie wObj;
short iOTyp;
long lONr;

	try
	{
	// Objektnummern der Objekte, die zurückgegeben werden
	WEnumObjectsByNumber wObjsNum (CLSID_EnumObjectsByNumber);
	WInitObjektGeometrie wIObj (CLSID_ObjektGeometrie);

		for (wEnum->Reset(); S_OK == wEnum->Next (1, &lONr, NULL); )
		{
			THROW_FAILED_HRESULT (wIObj->InitObjGeometry (lONr));

			wObj = wIObj;
			wObj->GetObjTyp (&iOTyp);

			_ASSERTE (lONr != 0);
			_ASSERTE (lONr != -1);

			switch (iOTyp)
			{
				case OT_PUNKT:
					if (0 == (lObjTypes & OTPunkt))	// Punktobjekte sind diesmal nicht gefragt
						continue;		// weiter zum nächsten TopicalObject
					break;

				case OT_KANTE:
					if (0 == (lObjTypes & OTLinie))		// Linienobjekte nicht gefragt
						continue;
					break;

				case OT_FLAECHE:
					if (0 == (lObjTypes & OTFlaeche))	// Flächenobjekte nicht gefragt
						continue;
					break;

				case OT_TEXT:
				case OT_LABEL:		// indirektes Textobjekt
					if (0 == (lObjTypes & OTText))		// Textobjekte nicht gefragt
						continue;
					break;

				default:
					_ASSERTE (iOTyp == OT_PUNKT || iOTyp == OT_KANTE ||
							   iOTyp == OT_FLAECHE || iOTyp == OT_TEXT || iOTyp == OT_LABEL);
					hr = S_FALSE;	// sonst nur weitermachen
					continue;
			}

			wObjsNum->AddItem (lONr);
		} // for

	WQueryGeoObjects wQObjs (wObjsNum);

		wQObjs->GetGeoObjects ((DGeoObjects**)ppIDisp);
	}

	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}	

	return hrRet;

} // GetObjects


// --------------------------------------------------------------------------------------------
// Rücknahme der extern bereitgestellten ausgewählten Objekte
STDMETHODIMP CGeoEditExtension::RemoveObjects (void)
{
	m_wTopObjs->DeleteTopicalObjects (TRUE);		// bisherigen Inhalt löschen
	return m_wTopObjs->InitWithSelectedObjects();	// die über Recherchefenster ausgewählten
													// Objekte wieder hinzufügen
} // RemoveObjects


// --------------------------------------------------------------------------------------------
// DragEnter an die aktuelle IEditOperation m_wEditOper weiterleiten, wenn diese das Interface
// ITRiASDropTarget unterstützt
STDMETHODIMP CGeoEditExtension::DragEnter (DRAGDROPTYPE rgType, HWND hWnd,
					IDataObject* pIDataSource, DWORD grfKeyState, POINTL ptl, DWORD* pdwEffect)
{
	if (! m_wTDropTarget.IsValid())	// aktuelle IEditOperation unterstützt nicht ITRiASDropTarget
		return S_FALSE;		// weiterreichen, da ich dieses Drag-and-Drop nicht ausführe

	return m_wTDropTarget->DragEnter (rgType, hWnd, pIDataSource, grfKeyState, ptl, pdwEffect);
}


// --------------------------------------------------------------------------------------------
// DragOveran die aktuelle IEditOperation m_wEditOper weiterleiten, wenn diese das Interface
// ITRiASDropTarget unterstützt
STDMETHODIMP CGeoEditExtension::DragOver (DRAGDROPTYPE rgType, HWND hWnd, DWORD grfKeyState,
										  POINTL ptl, DWORD* pdwEffect)
{
	if (! m_wTDropTarget.IsValid())	// aktuelle IEditOperation unterstützt nicht ITRiASDropTarget
		return S_FALSE;		// weiterreichen, da ich dieses Drag-and-Drop nicht ausführe

	return m_wTDropTarget->DragOver (rgType, hWnd, grfKeyState, ptl, pdwEffect);
}


// --------------------------------------------------------------------------------------------
// DragLeave an die aktuelle IEditOperation m_wEditOper weiterleiten, wenn diese das Interface
// ITRiASDropTarget unterstützt
STDMETHODIMP CGeoEditExtension::DragLeave (DRAGDROPTYPE rgType, HWND hWnd)
{
	if (! m_wTDropTarget.IsValid())	// aktuelle IEditOperation unterstützt nicht ITRiASDropTarget
		return S_FALSE;		// weiterreichen, da ich dieses Drag-and-Drop nicht ausführe

	return m_wTDropTarget->DragLeave (rgType, hWnd);
}


// --------------------------------------------------------------------------------------------
// Drop an die aktuelle IEditOperation m_wEditOper weiterleiten, wenn diese das Interface
// ITRiASDropTarget unterstützt
STDMETHODIMP CGeoEditExtension::Drop (DRAGDROPTYPE rgType, HWND hWnd,
					IDataObject* pIDataSource, DWORD grfKeyState, POINTL ptl, DWORD* pdwEffect)
{
	if (! m_wTDropTarget.IsValid())	// aktuelle IEditOperation unterstützt nicht ITRiASDropTarget
		return S_FALSE;		// weiterreichen, da ich dieses Drag-and-Drop nicht ausführe

	return m_wTDropTarget->Drop (rgType, hWnd, pIDataSource, grfKeyState, ptl, pdwEffect);
}
