// Funktionen für Erweiterungs-DLL "Objektoperationen mit GeoObjekten"
// File: ObjOper.cxx
// W. Mörtl


#include "ObjOperP.hxx"

#include <resstrg.h>			// IDS_UIFORMAT
#include <initguid.h>			// nur in einem Modul für Linken (*guid.h, CLSID_*) notwendig

#include "ObjOperR.h"			// Ressourcekonstanten für diese Erweiterung (IDM_OPERATIONEN, ...)

#include "GeomDLL.hxx"			// InitGeometrie
#include "geotrias.hxx"			// GeometrieAnTRIAS(), ...
#include "zeichnen.hxx"			// GetDotsPerMM()

#include "SmartInterfaces.h"
#include "Version.h"			// OBJOPER_MAJORVERSION, ...

#include "PropSeq.h"			// GetSubPropSeqStorage(), ...
#include "RegOperatPropAct.h"	// CRegOperatPropAct
#include "LineSplitPropAct.h"	// CLineSplitPropAct
#include "SetsOperatPropAct.h"	// CSetsOperatPropAct
#include "AreaBuildPropAct.h"	// CAreaBuildPropAct
#include "OptionsPropAct.h"		// COptionsPropAct
//#include "ObjekteVereinigen.h"	// CObjekteVereinigen
#include "ObjOper.hxx"			// Klasse für diese Erweiterung

#include <imaschen_i.c>			// CLSID_ExtLinienVerfolgung


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



DEFINE_GUID(CLSID_ProgressIndicator,0x07963819,0x3123,0x101C,0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C);
DEFINE_GUID(IID_IProgressIndicator2,0x079638D1,0x3123,0x101C,0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C);



///////////////////////////////////////////////////////////////////////////////////////////////
// Das Makro OBJECT_ENTRY ordnet einer Klasse (z.B. ObjektOpExtension) den ClassID zu und
// übernimmt außerdem die Registrierung in der RegDB.
BEGIN_OBJECT_MAP(ObjectMap)		// Makro
	OBJECT_ENTRY (CLSID_GeometrieOperationen, ObjektOpExtension)
	OBJECT_ENTRY (CLSID_RegOperatPropAct, CRegOperatPropAct)
	OBJECT_ENTRY (CLSID_LineSplitPropAct, CLineSplitPropAct)
	OBJECT_ENTRY (CLSID_SetsOperatPropAct, CSetsOperatPropAct)
	OBJECT_ENTRY (CLSID_AreaBuildPropAct, CAreaBuildPropAct)
	OBJECT_ENTRY (CLSID_OptionsPropAct, COptionsPropAct)
//	OBJECT_ENTRY (CLSID_ObjekteVereinigen, CObjekteVereinigen)
END_OBJECT_MAP()


// --------------------------------------------------------------------------------------------
// mit der folgenden Funktion wird die ObjectMap in den ClassFactory-Mechanismus dieser
// Erweiterung eingebunden
_ATL_OBJMAP_ENTRY* GetObjectMap (void)
{
	return ObjectMap;
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung sich selbst in der
// RegDB registrieren soll (empfohlen!!).
// Der ProgID (hier 'TRiAS.Operationen.1') ist eine Zeichenkette, die die Erweiterung in der
// RegDB repräsentiert. Das Format sollte beibehalten werden. Die '... .1' steht für die
// VersionsNummer. Der KlassenName (hier die Stringresource hinter IDS_LONGCLASSNAME) ist eine
// normal-lesbare Zeichenkette, die lokalisiert wird (deshalb in der Ressource) und die
// Bezeichnung der Erweiterung definiert.
BOOL UpdateRegistry (BOOL bRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (bRegister)	// RegDB initialisieren
		return ExtOleRegisterExtensionClass (g_hInstance, CLSID_GeometrieOperationen,
											 TEXT("TRiAS.Operationen.1"), IDS_LONGCLASSNAME,
											 OBJOPER_MAJORVERSION, OBJOPER_MINORVERSION,
											 EFUnLoadable|EFVisible);
	else			// RegDB säubern
		return ExtOleUnregisterClass (CLSID_GeometrieOperationen, TEXT("TRiAS.Operationen.1"));

	return true;	// alles ok
}



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern UINT __DexNotify;
extern UINT __DexCmd;
ResourceFile* pRF = NULL;



///////////////////////////////////////////////////////////////////////////////////////////////
// Zählen von Objekten in den geöffneten Recherchefenstern und Rückgabe von
//   lNumber[0]  Anzahl der selektierten (markierten) Objekte außer dem aktivierten (blinkenden) Objekt
//   lNumber[1]  Anzahl der selektierten Flächen (evtl. einschließlich einer aktivierten Fläche)
//   lNumber[2]  Anzahl der selektierten Kanten (evtl. einschließlich einer aktivierten Kante)
//   lNumber[3]  Anzahl der selektierten Punkte (evtl. einschließlich eines aktivierten Punktes)
BOOL _OBJOPER_EXPORT FAR PASCAL CountSelectedObjects (long lONr, BOOL, void* lNumber)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);
	_ASSERTE ((ObjektOpExtension*)g_pTE != NULL);

	if (((ObjektOpExtension*)g_pTE)->ONrAO() != lONr)	// alle außer hier aktiviertem zählen
		((long*)lNumber)[0]++;

int iObjTyp = DEX_GetObjectType (lONr);

	if (OT_FLAECHE == iObjTyp)
		((long*)lNumber)[1]++;
	if (OT_KANTE == iObjTyp)
		((long*)lNumber)[2]++;
	if (OT_PUNKT == iObjTyp)
		((long*)lNumber)[3]++;

	return TRUE;
}


// --------------------------------------------------------------------------------------------
// Anzahl der selektierten (markierten) Objekte in allen geöffneten Recherchefenstern außer
// dem aktivierten (blinkenden) Objekt ermitteln und in lObjAnz zurückgeben
BOOL _OBJOPER_EXPORT FAR PASCAL ObjekteZaehlen (long lONr, BOOL, void* lObjAnz)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);
	_ASSERTE ((ObjektOpExtension*)g_pTE != NULL);

	if (((ObjektOpExtension*)g_pTE)->ONrAO() != lONr)
		(*(long*)lObjAnz)++;

	return TRUE;
}


// --------------------------------------------------------------------------------------------
// alle Merkmalscodes ulMCode eines Objektes geben lassen und die Merkmalsinhalte in einer
// Liste sammeln; Sortierschlüssel ist der MerkmalsKurztext (wegen der Möglichkeit
// verschiedener Datenquellen NICHT mehr der Merkmalscode !)
BOOL _OBJOPER_EXPORT FAR PASCAL EnumFeaturesProc (ulong ulMCode, BOOL, void* pvData)
{
	_ASSERTE (0 != ulMCode);
	_ASSERTE ((ulong)-1 != ulMCode);
	_ASSERTE (NULL != pvData);

MerkmalInfos* pInfo = (MerkmalInfos*)pvData;
long lOrigONr = pInfo->lOrigONr;				// Objektnummer und
HPROJECT hPr = DEX_GetObjectProject (lOrigONr);	// ProjectHandle eines "Eltern"-Objektes
bool bCopyFeat = pInfo->bCopyFeat;				// alle Merkmale oder nur "Elten"-UniqueIdents

#if _TRiAS_VER < 0x0300
	// die Einträge im Merkmal "OldObjUniqueIdent" werden nicht in die Liste mit übernommen,
	// für bCopyFeat == false nur die "Elten"-UniqueIdents
	if (ulMCode == DEX_GetOldUniqueIdentMCode() ||
		(!bCopyFeat && ulMCode != DEX_GetUniqueIdentMCode()))
#else
	// die Einträge der Merkmale "OldObjUniqueIdent" und "Eindeutige Objektkennung" werden
	// nicht in die Liste mit übernommen, für bCopyFeat == false nur die "Elten"-UniqueIdents
	if (ulMCode == DEX_GetOldUniqueIdentMCodeEx (hPr) ||
		(!bCopyFeat && ulMCode != DEX_GetUniqueIdentMCodeEx (hPr)) ||
		ulMCode == DEX_GetObjGuidMCode (DEX_GetObjIdent (lOrigONr)))
#endif // _TRiAS_VER < 0x0300
	return TRUE;

// der Kurztext sMKTListe, unter dem der Text des ulMCode-Merkmals in der Liste abgespeichert
// wird, ist i.d.R. mit dem Kurztext des ulMCode-Merkmals identisch; nur für das Merkmal
// "UniqueIdent" werden die Texte gleich unter dem Kurztext "OldObjUniqueIdent" abgelegt;
// dies ist jetzt erforderlich, da die "Eltern"-Objekte aus verschiedenen Datenquellen
// stammen können und das neue Objekt in noch einer anderen Datenquelle abgespeichert sein kann
string sMKTListe;

	// Kurztext des Merkmalscodes ulMCode ermitteln; auch wenn er nicht ermittelbar ist, kein
	// Abbruch der Enumeration, deshalb Rückgabe von TRUE
	if (!GetKurzText (ulMCode, 'm', sMKTListe))
		return TRUE;	// Kurztext nicht ermittelbar

#if _TRiAS_VER < 0x0300
	if (ulMCode == DEX_GetUniqueIdentMCode() &&
		!GetKurzText (DEX_GetOldUniqueIdentMCode(), 'm', sMKTListe))
#else
	if (ulMCode == DEX_GetUniqueIdentMCodeEx (hPr) &&
		!GetKurzText (DEX_GetOldUniqueIdentMCodeEx (pInfo->hPr), 'm', sMKTListe))
#endif // _TRiAS_VER < 0x0300
		return TRUE;

string sMInhalt;

	//	wenn ulMCode-Merkmal am lOrigONr-Objekt vorhanden und belegt ...
	if (ReadFeatureText (lOrigONr, ulMCode, TT_Objekt, sMInhalt) &&
		"" != sMInhalt)
	{
		_ASSERTE (NULL != pInfo->pListe);

	CMerkmalsListe* pListe = pInfo->pListe;
	CMerkmalsListe_it map_it;

		// ... dann dieses Merkmal in der Map suchen
		map_it = pListe->find (sMKTListe);

		if (map_it != pListe->end())			// Merkmal schon vorhanden
		{
		string* psFind = &(*map_it).second;		// Pointer, damit Veränderungen zurückgereicht
												// werden
			_ASSERTE (NULL != psFind);

			// der neu zu bildenden Merkmalsinhalt wird am Anfang und am Ende mit dem
			// Trennzeichen ergänzt, um beim Test, ob dieser Merkmalstext schon vorhanden ist,
			// nicht durch "Untermengen"-Strings zu einer falschen Aussage zu kommen. In
			// TransmitParentsFeatures() werden diese beiden Trennzeichen wieder entfernt.
			if (NPOS != psFind->find (sMTrenn+sMInhalt+sMTrenn))
				return TRUE;					// Merkmalsinhalt schon vorhanden

			if ("" != *psFind)
				*psFind += sMInhalt+sMTrenn;	// bisherigen Eintrag durch sMInhalt ergänzen
			else
				*psFind = sMTrenn+sMInhalt+sMTrenn;
		}
		else
			pListe->insert (sMKTListe, sMTrenn+sMInhalt+sMTrenn);	// neuen Eintrag in Map erzeugen
	}
		
	return TRUE;
}



///////////////////////////////////////////////////////////////////////////////////////////////
int ErrHandler (int iWC, int iRoutine, ...);



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
// Die Erweiterung wird von der Klasse 'CTriasExtension' abgeleitet, welche wiederum als
// einzigen Parameter den ResID des im Hauptfenster einzuhängenden Menüs übergeben bekommt.
ObjektOpExtension::ObjektOpExtension (void)
				 : CTriasExtension (0, IDM_OPERATMENU)

#if !defined(__ATL_20_USED__)
				     , m_PPI(this)
#endif // !defined(__ATL_20_USED__)
{
	// Member initialisieren
	m_dwCookie = 0L;		// Nummer des ConnectionPoint

	m_pW = NULL;
	m_hWnd = 0;				// Nummer des Hauptfensters

    m_bGeoRein = false;		// Ankopplung von GeoRein.ext über Interface noch nicht erfolgt

	m_OpMode = EINZOBJ;		// Nummer der ausgewählten Operation
	_ulLageAusw = LINN;		// Bitmuster für Auswahl bei Schnittoperationen;
							// (Standard: innerhalb, d.h. _ulLageAusw == LINN)
	_sfSForm = SFORM_PERM;	// permanente Abspeicherung
	_bNeuZeigen = true;		// Recherchefenster der neuen Objekte anzeigen
	_bOrigZeigen = true;	// Recherchefenster der Orginalobjekte anzeigen
	
	_pBO = NULL;			// aktiviertes (blinkenden) d.h. schneidendes Objekt
	_lONrAO = -1;			// Objektnummer
	_ulIdent = 0;			//  bzw. Identifikator des aktivierten Objektes
	_pVFl = NULL;			// Vereinigungsfläche
	m_plNeuObjNr = NULL;	// Feld der Objektnummern der neuen Objekte
	m_lNeuInd = 0;			// Laufindex von m_plNeuObjNr
	m_plOrigObjNr = NULL;	// Feld der Objektnummern der originalen Objekte
	m_lOrigInd = 0;			// Laufindex von m_plOrigObjNr

	m_bCopyFeat = true;		// Merkmale der Originalobjekte sollen übernommen werden

	_bMenLoeNeu = false;	// Menüpunkt für Löschen der neuen Objekte noch nicht aktiviert
	_bMenLoeOrig = false;	// Menüpunkt für Löschen der originalen Objekte noch nicht
							// aktiviert
	_bObjLoesch = false;

	m_dimDots = GetDotsPerMM (NULL);

	COM_TRY
	{
		m_BScript = WExtendBScript (CLSID_MacroScriptExtension);
	}
	COM_CATCH_NORETURN;
}


// --------------------------------------------------------------------------------------------
// Destruktor
ObjektOpExtension::~ObjektOpExtension (void)
{
    // Interface's wieder freigeben
    m_wGeoRein.Assign (0);
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Im folgenden werden alle durch diese Erweiterung überladenen virtuellen Funktionen definiert

// Folgende Funktion wird einmalig nach der erfolgreichen Installation der Erweiterung
// durch TRiAS gerufen. Hier sollten alle notwendigen Initialisierungen erfolgen.
STDMETHODIMP_(BOOL) ObjektOpExtension::InitExtension (short iMode)
{
	if (!CTriasExtension::InitExtension (iMode))
		return false;

	InitGeometrie (hWnd(), __DexNotify, __DexCmd);
	pRF = &RF();
	
	_ASSERTE (pRF != NULL);

// durch die nachfolgende Konstruktion wird die Routine ErrHandler() gerufen, wenn der
// Fehlercode "WC_MESSAGE_OPER" auftritt (siehe DEX_SetError()) und die bisherige
// Fehlerbehandlung ausgeschaltet, die aber in m_oldEH gerettet wird, um sie dann in
// UnLoadExtension wieder zu rekonstruieren
ErrCode rcDummy;

	DEX_ErrInstall (rcDummy, WC_MESSAGE_OPER, ErrHandler, &m_oldEH);

	m_iMode = iMode;
	if (iMode != LoadState())	// Erweiterung war schon teilweise geladen gewesen
		return true;			// jetzt ist sie voll zu sehen

// TRiAS-Messages anfordern (nur 1 Parameter)
// ich interessiere mich für die von TRiAS verschickten Meldungen:
	RegisterNotification (DEX_PROJECTCLOSE);
	RegisterNotification (DEX_DELOBJECT);

// georein.ext automatisch nachladen
ResString GeoRein (ResID (IDS_GEOREIN, pRF), 20);
	
	DEX_ExternalLoadExtension (GeoRein.Addr());

	return true;
} // InitExtension


// --------------------------------------------------------------------------------------------
STDMETHODIMP_(BOOL) ObjektOpExtension::UnLoadExtension (void)
{
	// TRiAS-Messages wieder abmelden
	UnRegisterNotification (DEX_DELOBJECT);
	UnRegisterNotification (DEX_PROJECTCLOSE);

// durch die nachfolgende Konstruktion wird die vorhergehende Fehlerbehandlung m_oldEH wieder
// eingestellt (siehe auch InitExtension())
ErrCode rcDummy;

	DEX_ErrInstall (rcDummy, WC_MESSAGE_OPER, m_oldEH, NULL);

	// restliche Abmeldungen
	UnLoadAndCLOSE();

	return CTriasExtension::UnLoadExtension();
} // UnLoadExtension


// --------------------------------------------------------------------------------------------
// Diese Funktion dient der Behandlung der Menükommandos der Erweiterung
STDMETHODIMP_(BOOL) ObjektOpExtension::MenuCommand (UINT MenuItemID, HWND hWnd)
{
	m_hWnd = hWnd;

	switch (MenuItemID) 
	{   
		case IDM_OPERATIONEN:
			ObjectOperations (hWnd);
			return true;

		case IDM_OPLOESCHEN:		// Menüpunkt: neu erzeugte Objekte löschen
			ObjekteLoeschen (m_plNeuObjNr, _lAnzNeuObj);
			m_lNeuInd = 0;
			m_veNewObjs.clear();
			return true;

		case IDM_OPORIGLOESCHEN:	// Menüpunkt: ursprüngliche Objekte löschen
			ObjekteLoeschen (m_plOrigObjNr, _lAnzOrigObj);
			m_lOrigInd = 0;
			return true;

		default:
			_ASSERTE (false);
			break;
	}

	DEX_Error (RC_MenuCommandOp, EC_ERRMENUITEMID);
	return false;

} // MenuCommand


// --------------------------------------------------------------------------------------------
// Diese Funktion initialisiert das Menü
bool ObjektOpExtension::FindMenuItem (HMENU hMenu, UINT uiID)
{
	if (NULL == hMenu)
		return false;

UINT uiCnt = GetMenuItemCount(hMenu);

	uiID += MenuOffset();
	for (UINT uiLoop = 0; uiLoop < uiCnt; uiLoop++) {
		if (uiID == GetMenuItemID (hMenu, uiLoop))
			return true;
	}
	return false;		// nichts gefunden
}

STDMETHODIMP_(BOOL) ObjektOpExtension::MenuInit (HMENU hMenu, LPARAM, HWND hWnd)
{
// Menu nur dann beachten, wenn unser Menupunkt drin ist (#HK000209)
	if (!FindMenuItem (hMenu, IDM_OPERATIONEN) && 
		!FindMenuItem (hMenu, IDM_OPLOESCHEN) &&
		!FindMenuItem (hMenu, IDM_OPORIGLOESCHEN))
	{
		return FALSE;	// nicht für uns
	}

	if (pExtMenu() == NULL)
		return FALSE;

	if (hWnd && ORWind (hWnd))	// ORWind() liefert pWindow-Zeiger auf ObjektRechercheFenster
		m_pW = ORWind (hWnd);	// damit können alle weiteren Fenster auf das ObjektRechercheFenster
								//  bezogen werden
	else
		m_pW = MWind();			// MWind() liefert pWindow-Zeiger auf HauptFenster

	if (AcceptanceTestObjOper (hWnd))
		EnableMenuItem (hMenu, IDM_OPERATIONEN+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
	else
		EnableMenuItem (hMenu, IDM_OPERATIONEN+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

	if (_bMenLoeNeu) // Menüpunkt für Löschen der neu erzeugten Objekte
		EnableMenuItem (hMenu, IDM_OPLOESCHEN+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
	else
		EnableMenuItem (hMenu, IDM_OPLOESCHEN+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

	if (_bMenLoeOrig) // Menüpunkt für Löschen der ursprünglichen Objekte
		EnableMenuItem (hMenu, IDM_OPORIGLOESCHEN+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
	else
		EnableMenuItem (hMenu, IDM_OPORIGLOESCHEN+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

	return TRUE;
} // MenuInit


// --------------------------------------------------------------------------------------------
// Diese Funktion wird bei Systemereignissen diverser Natur gerufen
STDMETHODIMP_(LRESULT) ObjektOpExtension::Notification (WPARAM iMsg, LPARAM lParam)
{
	switch (iMsg)
	{
		case DEX_PROJECTCLOSE:		// Projekt wird geschlossen
			UnLoadAndCLOSE();
			_lAnzNeuObj = 0;		// 30.09.98
			m_lNeuInd = 0;			// 30.09.98
			break;

		case DEX_DELOBJECT:		// ein Objekt wurde gelöscht
			// diese Message interessiert nicht, wenn die zuletzt neu erzeugten Objekte über
			// den Menüpunkt "Neu erzeugte Objekte löschen" bzw. deren Elternobjekte über den
			// Menüpunkt "Ursprungsobjekte löschen" gelöscht werden (_bObjLoesch == true) bzw.
			// wenn gar keine Objekte neu erzeugt wurden (m_lNeuInd == 0)
			if (_bObjLoesch || m_lNeuInd == 0)
				break;

			// für die zuletzt neu erzeugten Objekte besteht noch Löschmöglichkeit über Menüpunkt
			if (m_lNeuInd > 0)
			{
			bool bObj = false;	// das soeben gelöschte Objekt ist ein/kein zuletzt neu
								// erzeugtes Objekt (true/false)

				for (long i = 0; i < m_lNeuInd; i++)
				{
					// lParam ist die Objektnummer des soeben gelöschten Objektes
					if (m_plNeuObjNr && m_plNeuObjNr[i] == lParam)
						// das soeben gelöschte Objekt gehört zu den zuletzt neu erzeugten
						// Objekten
						bObj = true;
					if (bObj && i < m_lNeuInd-1)
						// dann dessen Objektnummer durch Verschieben löschen
						m_plNeuObjNr[i] = m_plNeuObjNr[i+1];
				}
				if (bObj)
					m_lNeuInd--;
			}
			if (m_lNeuInd == 0)	// m_lNeuInd == 0 durch vorstehenden Dekrement-Befehl
			{
				_bMenLoeOrig = false;	// Lösch-Menüpunkt inaktivieren (20.10.98)
				_bMenLoeNeu = false;	// Lösch-Menüpunkt inaktivieren
			}

			// für die Elternobjekte der zuletzt neu erzeugten Objekte besteht noch
			// Löschmöglichkeit über Menüpunkt
			if (m_lOrigInd > 0)
			{
			// das soeben gelöschte Objekt ist ein/kein Elternobjekt eines zuletzt neu
			// erzeugten Objektes (true/false)
			bool bObj = false;

				for (long i = 0; i < m_lOrigInd; i++)
				{
					// lParam ist die Objektnummer des soeben gelöschten Objektes
					if (m_plOrigObjNr && m_plOrigObjNr[i] == lParam)
						// das soeben gelöschte Objekt gehört zu den Elternobjekten der zuletzt
						// neu erzeugten Objekte
						bObj = true;
					if (bObj && i < m_lOrigInd-1)
						// dann dessen Objektnummer durch Verschieben löschen
						m_plOrigObjNr[i] = m_plOrigObjNr[i+1];
				}
				if (bObj)
					m_lOrigInd--;
			}
			if (m_lOrigInd == 0)	// m_lOrigInd == 0 durch vorstehenden Dekrement-Befehl
			{
				_bMenLoeOrig = false;	// Lösch-Menüpunkt inaktivieren
				_bMenLoeNeu = false;	// Lösch-Menüpunkt inaktivieren (20.10.98)
			}

			break;
			
		default:	// Notifikationen der Basisklasse
			break;
	}

	return CTriasExtension::Notification (iMsg, lParam);

} // Notification


// --------------------------------------------------------------------------------------------
// Aktionen, die bei UnLoadExtension und DEX_PROJECTCLOSE gleich sind
void ObjektOpExtension::UnLoadAndCLOSE (void)
{
	_bMenLoeNeu = false;	// Lösch-Menüpunkte inaktivieren
	_bMenLoeOrig = false;

// dynamische Felder freigeben
	DELETE_VEC (m_plNeuObjNr);	// Felder löschen, die die Objektnummern der neu erzeugten
	DELETE_VEC (m_plOrigObjNr);	// bzw. der Originalobjekte enthalten
	DELETE_OBJ (_pBO);
	DELETE_OBJ (_pVFl);

} // UnLoadAndCLOSE


// --------------------------------------------------------------------------------------------
// Objektoperationen sind nur möglich, wenn
// - außer dem aktivierten (blinkenden) Objekt noch mindestens eine weiteren Flächen oder
//   Linien selektiert ist und
// - das aktivierte Objekt entweder eine Linie oder eine Fläche ist bzw.
// - mindestens 2 Linien oder mindestens 2 Flächen selektiert wurden
bool ObjektOpExtension::AcceptanceTestObjOper (HWND hWnd)
{
	_lONrAO = DEX_GetActiveObject (hWnd);

	if (0 == _lONrAO || -1 == _lONrAO)
		return false;

	_iOT = DEX_GetObjectType (_lONrAO);

// Objektnummern aller selektierten, d.h. blau markierten Objekte bereitstellen und deren
// Anzahl ermitteln
ENUMLONGKEY ELK;	// Enumeration aller selektierten Objekte

	m_lNumber[0] = 0;	// Anzahl der selektierten Objekte (s. ObjOper.hxx)
	m_lNumber[1] = 0;	// Flächen
	m_lNumber[2] = 0;	// Linien
	m_lNumber[3] = 0;	// Punkte
	ELK.eKey = (DWORD) 0;	// Suchschlüssel (Fenster-Handle von allen Recherchefenstern)
	ELK.eFcn = (ENUMLONGKEYPROC) CountSelectedObjects;	// zu rufende Funktion
	ELK.ePtr = (void*) m_lNumber;						// durchgereichte Daten
	DEX_EnumSelectedObjects (ELK);

	// Spezialfall: Punkt soll Linien schneiden
	if (OT_PUNKT == _iOT &&		// aktiviertes Objekt ist ein Punktobjekt und
		m_lNumber[2] >= 1)		//  mindestens 1 Linie selektiert
		return true;

	// außer dem aktivierten (blinkenden) Objekt keine anderen Flächen oder Linien selektiert
	// oder anders gesagt: alle selektierten Objekte sind Punkte
	if (m_lNumber[0] == m_lNumber[3])
		return false;

	// das aktivierte Objekt ist weder eine Linie noch eine Fläche
	if (OT_KANTE != _iOT && OT_FLAECHE != _iOT)
		return false;

	// sowie höchstens eine Linie und höchstens eine Fläche wurden selektiert
	if (m_lNumber[1] <= 1 && m_lNumber[2] <= 1) {
		if (1 == m_lNumber[1] && 1 == m_lNumber[0] && LineIsClosedPolygon (_lONrAO));
			return true;	// Spezialfall: eine geschlossene Linie
		return false;
	}
	return true;

} // AcceptanceTestObjOper

bool ObjektOpExtension::LineIsClosedPolygon (long lONr)
{
// Test, ob Kante offen oder geschlossen ist
WObjektGeometrie wObj;	// (Interface auf) Objektgeometrie des zu puffernden Objektes

	if (FAILED(CreateInterfaceOG (wObj.ppi(), lONr)))
		return false;

long lCnt;
KoOrd* plXK; KoOrd* plYK;

	wObj -> GetCnt (&lCnt);
	wObj -> GetX ((void**)&plXK);
	wObj -> GetY ((void**)&plYK);
	return (plXK[0] == plXK[lCnt-1] && plYK[0] == plYK[lCnt-1]) ? true : false;
} // LineIsClosedPolygon

// --------------------------------------------------------------------------------------------
// aktiviertes (blinkendes) Objekt ermitteln
bool ObjektOpExtension::AktiviertesObjekt (void)
{
	_lSPA = -1;	// Fehlerfall

bool bRet = true;	// return-Wert
IObjektGeometrie* pIOG = NULL;

	if (FAILED(CreateInterfaceOG (&pIOG, _lONrAO)))
		return false;

// Parameter des aktivierten Objektes
	pIOG->GetIdent (&_ulIdent);
	pIOG->GetObjTyp (&_iOT);

long lSPAnz;
KoOrd* plXK; KoOrd* plYK;

	pIOG->GetCnt (&lSPAnz);
	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);

	DELETE_OBJ (_pBO);

	switch (_iOT)
	{
		case OT_PUNKT:
			_ASSERTE (1 == lSPAnz);

			_lSPA = lSPAnz;		// Gesamtstützpunktanzahl des aktivierten Punktes
			_pBO = new EPunkt (plXK[0], plYK[0]);	// aktivierter Punkt
			break;
			
		case OT_KANTE:
			_lSPA = lSPAnz;		// Gesamtstützpunktanzahl der aktivierten Kante
			_pBO = new EKante (plXK, plYK, lSPAnz);	// aktivierte Kante
			break;
			
		case OT_FLAECHE:
		{
		short iKCnt;	// Größe des Konturfeldes
		long* plK;

			pIOG->GetKCnt (&iKCnt);
			pIOG->GetLPCnt (&plK);

			_pBO = EFlaecheErzeugen (iKCnt, plXK, plYK, plK);	// aktivierte Fläche
			_lSPA = plK[0];		// Stützpunktanzahl der Außenkontur der aktivierten Fläche
		}
			break;
			
		default:	// Textobjekt
			_ASSERTE (false);
			bRet = false;
	}
	
	if (! _pBO)
	{
		DEX_Error (RC_objoper, EC_NOMEMORY);
		bRet = false;
	}

	pIOG->Release();
	return bRet;

} // AktiviertesObjekt


// --------------------------------------------------------------------------------------------
// Reaktion auf den Menüpunkt "Geometrieoperation auswählen ..."
HRESULT ObjektOpExtension::ObjectOperations (HWND hWnd)
{
	COM_TRY {
	// gesamte Folge wSeq von 4 Seiten erzeugen
	WPropertyActionSequence wSeq;
	WStorage wStg;
	ResString strName(ResID (IDS_LONGCLASSNAME, pRF), 50);

	// der letzte Zustand wird aus dem Storage geholt; 
	// eine Neuinitialisierung kann jedoch erzwungen werden, wenn SHIFT- und 
	// CONTROL-Taste gleichzeitig gedrückt sind
		if (GetKeyState (VK_SHIFT) >= 0 || GetKeyState (VK_CONTROL) >= 0)
			GetSubPropSeqStorage (wStg.ppi());

		THROW_FAILED_HRESULT (InitPropertyActionSequence (strName, wStg, wSeq.ppi()));

	// hier wird die Folge abgearbeitet
	WDataObject wDataObj (CLSID_DataTransferObject);

		THROW_FAILED_HRESULT (SetHWNDData (hWnd, wDataObj));

	WDataObject wOutData;

		// 2. Parameter von DoActions(): ProgressIndicator
		THROW_FAILED_HRESULT (wSeq->DoActions (MWind()->Handle(), NULL, wDataObj,
							  wOutData.ppi()));
		Ergebnisanzeige();	// Recherchefenster für Ergebnisobjekte und/oder Originalobjekte

		// Speichern der letzten Nutzerselektion
		RETURN_FAILED_HRESULT (SavePropSeq (strName, wSeq, wStg));

	} COM_CATCH_NOASSERT_ON(E_ABORT);
	return S_OK;

} // ObjectOperations


// --------------------------------------------------------------------------------------------
// Identifikator ulIdent den vereinigten Linienobjekten zuordnen und evtl. Ergebnisse in
// Recherchefenstern anzeigen
bool ObjektOpExtension::IdentAndRechWindows (IEnumObjectsByNumber* pEnumOutput,
									  IEnumObjectsByNumber* pEnumUsed, ulong ulIdent, bool bOK)
{
	// bei Abbruch durch den Anwender gilt pEnumOutput == NULL und pEnumUsed == NULL

ulong ulCnt = 0;

	if (!pEnumOutput || FAILED(pEnumOutput->GetCount (&ulCnt)))
	{
		if (pEnumOutput)
			DEX_Error (RC_objoper, EC_NOCOUNT);
		ulCnt = 0;
	}

	_lAnzNeuObj = ulCnt;

	ObjectsForRechWindows (pEnumUsed);

	// Identifikator ulIdent den vereinigten Linienobjekten zuordnen und evtl. Vorbereitung für
	// Anzeige in einem Recherchefenster treffen
	if (pEnumOutput)
	{
		_ASSERTE (0 != ulIdent);
		_ASSERTE ((ulong)-1 != ulIdent);

	long lONr = 0;
	MODOBJIDENT MOI;	// Struktur für Modifikation des Identifikators

		INITSTRUCT (MOI, MODOBJIDENT);
		MOI.lNewIdent = ulIdent;
		MOI.iMode = MODIDENT_LINIE | MODIDENT_ADDTOVIEW;	// zur Sicht hinzufügen

		for (pEnumOutput->Reset(); S_OK == pEnumOutput->Next (1, &lONr, NULL); ) 
		{
			_ASSERTE (lONr != 0);
			_ASSERTE (lONr != -1);
			_ASSERTE (DEX_GetObjectType (lONr) == OGLinie);

			// in LinesUnion() werden die Objekte nur mit dem Objektklassenschlüssel
			// "Unbekannte Objektklasse" erzeugt und abgespeichert, deshalb hier die Zuordnung
			// des eigentlichen Identifikators
			MOI.lONr = lONr;
			DEX_ModObjectIdentEx (MOI); 

			if (_bNeuZeigen && _lAnzNeuObj > 0)
			{
				m_plNeuObjNr[m_lNeuInd] = lONr;
				m_lNeuInd++;
			}
		}
	}

	// Recherchefenster für Ergebnisobjekte und/oder Originalobjekte
	Ergebnisanzeige();
	
	if (0 == _lAnzNeuObj || !bOK)	// keine neue Objekte oder Abbruch durch den Anwender
	{
	ResString resTitel (ResID (IDS_LONGCLASSNAME, pRF), 50);
	ResString resText (ResID (IDS_BOXTEXT7, pRF), 200);
			
		MessageBox (__hWndM, resText.Addr(), resTitel.Addr(), MB_ICONINFORMATION | MB_OK);
	}

	return true;

} // IdentAndRechWindows


// --------------------------------------------------------------------------------------------
// Objektnummern der neu gebildeten und/oder der originalen Objekte in m_plNeuObjNr bzw.
// m_plOrigObjNr bereitstellen, damit die Objekte in Recherchefenstern angezeigt werden können
HRESULT ObjektOpExtension::ObjectsForRechWindows (IEnumObjectsByNumber* pEnumUsed)
{
	// wenn die neu erzeugten Objekte in einem Recherchefenster angezeigt werden sollen
	// (_bNeuZeigen == true), dann Feld m_plNeuObjNr für deren Objektnummern anlegen
	if (_bNeuZeigen && _lAnzNeuObj > 0)
	{
		DELETE_VEC (m_plNeuObjNr);
		m_plNeuObjNr = new long[_lAnzNeuObj];
		if (! m_plNeuObjNr)
		{
			DEX_Error (RC_objoper, EC_NOMEMORY);
			return E_OUTOFMEMORY;
		}
		m_lNeuInd = 0;   // Laufindex für m_plNeuObjNr
	}


	// wenn die originalen Objekte in einem Recherchefenster angezeigt werden sollen
	// (_bOrigZeigen == true), dann Feld m_plNeuObjNr für deren Objektnummern anlegen
	_lAnzOrigObj = 0;	// Anzahl der Originalobjekte, aus denen die vereinigten
						//  Objekte gebildet wurden

	if (! pEnumUsed) return E_POINTER;

ulong ulCnt = 0;
HRESULT hr = pEnumUsed->GetCount (&ulCnt);

	if (FAILED(hr)) return hr;
	_lAnzOrigObj = ulCnt;

	if (_lAnzOrigObj > 0)
	{
		_bMenLoeOrig = true;     // Menüpunkt aktivieren

		if (_bOrigZeigen)
		{
			DELETE_VEC (m_plOrigObjNr);
			m_plOrigObjNr = new long[_lAnzOrigObj];
			if (! m_plOrigObjNr)
			{
				DEX_Error (RC_objoper, EC_NOMEMORY);
				return E_OUTOFMEMORY;
			}
			m_lOrigInd = 0;   // Laufindex für m_plOrigObjNr

		long lONr = 0;

			for (pEnumUsed->Reset(); S_OK == pEnumUsed->Next (1, &lONr, NULL); ) 
			{
				m_plOrigObjNr[m_lOrigInd] = lONr;
				m_lOrigInd++;
			}
		}
	}

	return S_OK;

} // ObjectsForRechWindows


// --------------------------------------------------------------------------------------------
// Objektnummern der genutzten originalen und der neu gebildeten Objekte in m_plOrigObjNr bzw.
// m_plNeuObjNr bereitstellen, damit die Objekte in Recherchefenstern angezeigt werden können
HRESULT ObjektOpExtension::ObjectsForRechWindows (IEnumLONG* pEnumUsed, IEnumLONG* pEnumNew)
{
	if (pEnumUsed)
	{
		_lAnzOrigObj = pEnumUsed->Count();

		DELETE_VEC (m_plOrigObjNr);
		m_plOrigObjNr = new long[_lAnzOrigObj];
		if (! m_plOrigObjNr)
		{
			DEX_Error (RC_objoper, EC_NOMEMORY);
			return E_OUTOFMEMORY;
		}

		m_lOrigInd = 0;   // Laufindex für m_plOrigObjNr

	long lONr = 0;

		for (pEnumUsed->Reset(); S_OK == pEnumUsed->Next (1, &lONr, NULL); m_lOrigInd++)
			m_plOrigObjNr[m_lOrigInd] = lONr;
	}
	else
	{
		_lAnzOrigObj = 0;
		DELETE_VEC (m_plOrigObjNr);
		m_lOrigInd = 0;
	}

	if (pEnumNew)
	{
		_lAnzNeuObj = pEnumNew->Count();

		DELETE_VEC (m_plNeuObjNr);
		m_plNeuObjNr = new long[_lAnzNeuObj];
		if (! m_plNeuObjNr)
		{
			DEX_Error (RC_objoper, EC_NOMEMORY);
			return E_OUTOFMEMORY;
		}

		m_lNeuInd = 0;   // Laufindex für m_plNeuObjNr

	long lONr = 0;

		for (pEnumNew->Reset(); S_OK == pEnumNew->Next (1, &lONr, NULL); m_lNeuInd++)
			m_plNeuObjNr[m_lNeuInd] = lONr;
	}
	else
	{
		_lAnzNeuObj = 0;
		DELETE_VEC (m_plNeuObjNr);
		m_lNeuInd = 0;
	}

	return S_OK;

} // ObjectsForRechWindows


// --------------------------------------------------------------------------------------------
// Objektnummer abspeichern und Menüpunkt für Löschen der Originalobjekte aktivieren
void ObjektOpExtension::ObjNrSpeichern (long lONr)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);
	_ASSERTE (m_lOrigInd < _lAnzOrigObj);

	m_plOrigObjNr[m_lOrigInd] = lONr;   // Objektnummer abspeichern
	m_lOrigInd++;
	_bMenLoeOrig = true;     // Menüpunkt aktivieren
} // ObjNrSpeichern


// --------------------------------------------------------------------------------------------
// alle Objekte aus ClipListe _CL1 mit ulIdent versehen (wird bei Durchschnitt verwendet)
void ObjektOpExtension::IdentModify (ulong ulIdent)
{
CRing ri1 (_CL1);  // Navigator für ListContainer ClipListe _CL1

	for (ri1.First(); ri1.Valid(); ri1.Next())
	{
	GeoObjektLock ml (ri1);

		if (!ml) continue;	// kein Zugriff möglich
		((GeoObjekt*)ml)->SetIdent (ulIdent);
	}
} // IdentModify


// --------------------------------------------------------------------------------------------
// Ergebnis der Objektoperation an TRiAS übergeben und in Recherchefenstern anzeigen.
// Wenn Operation zu Ende geführt wurde, ist bOK = true.
bool ObjektOpExtension::ObjekteAnTRiAS (HPROJECT hPr, bool bOK)
{
bool bRet1 = true, bRet2 = true;	// return-Werte für ClipListeAnTRIAS()
long lAnzCL1 = _CL1.Count();		// Anzahl der Objekte in ClipListe _CL1
long lAnzCL2 = _CL2.Count();		//  bzw. _CL2

	_lAnzNeuObj = lAnzCL1 + lAnzCL2;	// Gesamtanzahl der neuen Objekte

	if (_lAnzNeuObj > 0)
	{
		DELETE_VEC (m_plNeuObjNr);				// Feld der Objektnummern der neuen Objekte löschen
		m_plNeuObjNr = new long[_lAnzNeuObj];	// Feld für diese neuen Objektnummern anlegen
		if (! m_plNeuObjNr)
		{
			DEX_Error (RC_objoper, EC_NOMEMORY);
			return false;
		}
		m_lNeuInd = 0;   // Laufindex für m_plNeuObjNr

		if (lAnzCL1 > 0)
			bRet1 = ClipListeAnTRIAS (hPr, _CL1);
		if (lAnzCL2 > 0)
			bRet2 = ClipListeAnTRIAS (hPr, _CL2);

#if _TRiAS_VER < 0x0300
//		Ergebnisanzeige();
#endif // _TRiAS_VER < 0x0300
	}
	else	// keine Ergebnisobjekte
		bRet1 = false;	// bRet2 muß nicht auch noch false gesetzt werden

	return (bOK && bRet1 && bRet2);

} // ObjekteAnTRiAS


// --------------------------------------------------------------------------------------------
// Objekte aus ClipListe CL als neue Objekt an TRiAS übergeben und ClipListe löschen
bool ObjektOpExtension::ClipListeAnTRIAS (HPROJECT hPr, ClipListe& CL)
{
	if (0 == CL.Count()) return false;

SpForm sfSForm;		// Speicherform

	// Zugriffsmode der Datenquelle ermitteln
	if (0 == DEX_GetROModeEx (hPr))	// Datenquelle nicht schreibgeschützt (R/W-Modus)
		sfSForm = SFORM_PERM;		// Speicherform: permanent
	else							// Datenquelle schreibgeschützt oder nicht geöffnet
	{
		DEX_Error (RC_ClipListeAnTRIAS, WC_DATASOURCE_ISRO);
		sfSForm = SFORM_TEMP;	// Speicherform: temporär
	}

CRing ri (CL);			// Navigator für ListContainer ClipListe CL
bool bRet = true;		// return-Wert dieser Routine
bool bAllObj = true;	// alle Objekte aus CL werden an TRiAS übergeben
long lNeuONr;			// Objektnummer eines neu erzeugten Objektes

	for (ri.First(); ri.Valid(); ri.Next())
	{
	GeoObjektLock ml (ri);

		if (! ml)	// kein Zugriff möglich
		{
			DEX_Error (RC_ClipListeAnTRIAS, EC_NOLOCK);
			continue;
		}

	ulong ulIdent = ((GeoObjekt*)ml)->Id();

	// ist für die Speicherung eines Objektes die Zieldatenquelle vorgegeben (hPr != 0),
	// sollte der Identifikator 0 sein (unbekannte Objektklasse), weil sonst vorrangig die
	// Zieldatenquelle durch DEX_GetObjectsProject(ulIdent) aus dem Identifikator ermittelt
	// wird (07.07.99)
	HPROJECT hPrLoc = hPr;		// #HK000801: für jedes Objekt Datenquelle neu auswählen

		if (0 != hPrLoc && 0 != ulIdent && hPrLoc != DEX_GetObjectsProject (ulIdent))
			((GeoObjekt*)ml)->SetIdent (0L);

		if (0 == hPrLoc)
		{
			_ASSERTE (0 != ulIdent);
			_ASSERTE ((ulong)-1 != ulIdent);
			hPr = DEX_GetObjectsProject (ulIdent);
		}

#if _TRiAS_VER < 0x0300
		if (!GeometrieAnTRIAS ((GeoObjekt*)ml, sfSForm, lNeuONr))
#else
		if (!GeometrieAnTRIASEx (hPrLoc, (GeoObjekt*)ml, sfSForm, lNeuONr))
#endif // _TRiAS_VER < 0x0300
		{
			bAllObj = false;	// nicht alle Objekte aus CL werden an TRiAS übergeben
			_lAnzNeuObj--;
			continue;
		}

		_ASSERTE (m_lNeuInd < _lAnzNeuObj);

		m_plNeuObjNr[m_lNeuInd] = lNeuONr;	// Objektnummer des neu gebildeten Objektes
		m_lNeuInd++;						// abspeichern

		// bei permanenter Abspeicherung Merkmale der Ursprungsobjektes an Ergebnisobjekte
		// anhängen
		if (SFORM_PERM == sfSForm)     // permanente Abspeicherung
//		{
		// Objektnummer des ml-Objektes vor der Einspeicherung der Geometrie in TRiAS (bei
		// Schnittoperationen ist das die Objektnummer des Originalobjektes; bei Vereinigung
		// bzw. Durchschnitt kann lAltONr == 0 sein
//		long lAltONr = ml->ObjNr();

//			CopyFeatures (lAltONr, lNeuONr);
			CopyFeatures (ml->ObjNr(), lNeuONr);
//		}
	} // for

	if (!bAllObj && 0 == _lAnzNeuObj)	// an TRiAS wird kein Objekt aus CL übergeben
	{
		DEX_Error (RC_ClipListeAnTRIAS, EC_NOGEOANTRIAS);
		bRet = false;
	}

	CL.EveryDelete();		// ClipListe löschen

	_ASSERTE (CL.Count() == 0);

	return bRet;

}  // ClipListeAnTRIAS


// --------------------------------------------------------------------------------------------
// die neu erzeugten Objekte aus CL nach TRiAS speichern, CL löschen sowie Objektnummern der
// neuen Objekte in m_NewObjs speichern
HRESULT ObjektOpExtension::NewObjectsToTRiAS (ClipListe& CL)
{
	if (0 == CL.Count()) return S_FALSE;

CRing ri (CL);			// Navigator für ListContainer ClipListe CL
HRESULT hrRet = S_OK;	// return-Wert dieser Routine
bool bStoreObj = false;	// mindestens ein Objekt aus CL wurde an TRiAS übergeben (true)
long lNeuONr;			// Objektnummer eines neu erzeugten Objektes
SpForm sfSForm;			// Speicherform

	for (ri.First(); ri.Valid(); ri.Next())
	{
	GeoObjektLock ml (ri);

		if (! ml)	// kein Zugriff möglich
		{
			DEX_Error (RC_objoper, EC_NOLOCK);
			continue;
		}

	HPROJECT hPr = DEX_GetObjectsProject (((GeoObjekt*)ml)->Id());

		// Zugriffsmode der Datenquelle ermitteln
		if (0 == DEX_GetROModeEx (hPr))	// Datenquelle nicht schreibgeschützt (R/W-Modus)
			sfSForm = SFORM_PERM;		// Speicherform: permanent
		else							// Datenquelle schreibgeschützt oder nicht geöffnet
		{
			DEX_Error (RC_objoper, WC_DATASOURCE_ISRO);
			sfSForm = SFORM_TEMP;	// Speicherform: temporär
		}


#if _TRiAS_VER < 0x0300
		if (!GeometrieAnTRIAS ((GeoObjekt*)ml, sfSForm, lNeuONr))
#else
		if (!GeometrieAnTRIASEx (hPr, (GeoObjekt*)ml, sfSForm, lNeuONr))
#endif // _TRiAS_VER < 0x0300
			continue;

		bStoreObj = true;
		m_veNewObjs.push_back (lNeuONr);	// Objektnummer des neu gebildeten Objektes retten

		// bei permanenter Abspeicherung Merkmale der Ursprungsobjektes an Ergebnisobjekte
		// anhängen
		if (SFORM_PERM == sfSForm)     // permanente Abspeicherung
			CopyFeatures (ml->ObjNr(), lNeuONr);
	} // for

	// für ObjekteLoeschen() noch umspeichern
	_lAnzNeuObj = m_veNewObjs.size();
	if (_lAnzNeuObj > 0)
	{
		DELETE_VEC (m_plNeuObjNr);				// Feld der Objektnummern der neuen Objekte löschen
		m_plNeuObjNr = new long [_lAnzNeuObj];	// Feld für diese neuen Objektnummern anlegen
		if (! m_plNeuObjNr)
		{
			DEX_Error (RC_objoper, EC_NOMEMORY);
			return E_OUTOFMEMORY;
		}

		for (long i = 0; i < _lAnzNeuObj; i++)
			m_plNeuObjNr[i] = m_veNewObjs[i];

		m_lNeuInd = _lAnzNeuObj;				// Laufindex für m_plNeuObjNr
	}

	if (!bStoreObj)	// an TRiAS wurde kein Objekt aus CL übergeben
	{
		DEX_Error (RC_objoper, EC_NOGEOANTRIAS);
		hrRet = E_UNEXPECTED;
	}

	CL.EveryDelete();		// ClipListe löschen

	return hrRet;

}  // NewObjectsToTRiAS


// --------------------------------------------------------------------------------------------
// Merkmale bei Objektoperationen an das neu erzeugte lNeuONr-Objekt kopieren, wenn
// m_bCopyFeat == true gilt
void ObjektOpExtension::CopyFeatures (long lAltONr, long lNeuONr)
{
	_ASSERTE (lNeuONr != 0);	// bei Vereinigung bzw. Durchschnitt kann lAltONr == 0 sein
	_ASSERTE (lNeuONr != -1);

string sUIText;
ResString resText (ResID (IDS_UIFORMAT, pRF), 20);

	Format (sUIText, (char*)resText.Addr(), lNeuONr);

	switch (m_OpMode)  // akt. gewählte Objektoperation
	{
		// alle Merkmale kopieren
		case EINZOBJ:
		case IDGRUPP:
		case ALLOBJ:
		case SPLITTING:
		case SUBTRAKTION:
		{
		long l = 0;

			for ( ; l < m_lOrigInd; l++)
				if (m_plOrigObjNr[l] == lAltONr)
					break;
			_ASSERTE (l < m_lOrigInd);
			TransmitParentsFeatures (l, l, lNeuONr, sUIText);
			break;
		}

		case DURCHSCHNITT:
		case VEREINIGUNG:
		case GEMKONTUR:
			TransmitParentsFeatures (0, m_lOrigInd-1, lNeuONr, sUIText);
			break;

		default:
			_ASSERTE (false);
			break;
	} // switch
} // CopyFeatures


// --------------------------------------------------------------------------------------------
// Merkmale der Eltern-Objekte m_lOrigInd[lAInd] bis m_lOrigInd[lEInd] an das neu gebildete
// lONr-Objekt übergeben; sUIdent ist der UniqueIdent des neuen Objektes
bool ObjektOpExtension::TransmitParentsFeatures (long lAInd, long lEInd, long lONr,
												 string sUIdent)
{
MerkmalInfos Info;

	m_FeatList.clear();
	Info.pListe = &m_FeatList;
	Info.hPr = DEX_GetObjectProject (lONr);
	Info.bCopyFeat = m_bCopyFeat;

// Merkmale der Eltern-Objekte in m_FeatList zusammenstellen 
ENUMLONGKEYEX ELKE;

	memset (&ELKE, 0, sizeof (ENUMLONGKEYEX));
	ELKE.eFcn = (ENUMLONGKEYEXPROC)EnumFeaturesProc;
	ELKE.ePtr = &Info;
	ELKE.eData = MPObjectFeature;	// nur Objektmerkmale übernehmen (in xtension.h definiert),
									// d.h. z.B. keine Systemmerkmale

	for (long l = lAInd; l <= lEInd; l++)
	{
		ELKE.eKey = m_plOrigObjNr[l];
		Info.lOrigONr = m_plOrigObjNr[l];
		DEX_EnumObjektMerkmaleEx (ELKE);
	}

// m_FeatList an das neu gebildete lONr-Objekt wegschreiben
CMerkmalsListe_it map_it;					// Iterator von m_FeatList
string sMInhalt;							// Merkmalsinhalt
HPROJECT hPr = DEX_GetObjectProject (lONr);	// ProjectHandle und
ulong ulIdent = DEX_GetObjIdent (lONr);		// Identifikator des neuen Objektes

	for (map_it = m_FeatList.begin(); map_it != m_FeatList.end(); map_it++)
	{
	string sKText = (*map_it).first;	// Kurztext

		sMInhalt = (*map_it).second;	// Merkmalsinhalt

		// das 1. und letzte Trennzeichen des neu gebildeten Merkmalsinhaltes entfernen (diese
		// wurden bewußt hinzugenommen, um beim Test, ob dieser Merkmalstext schon vorhanden
		// ist, nicht durch "Untermengen"-Strings zu einer falschen Aussage zu kommen 
		sMInhalt = sMInhalt.substr (1, sMInhalt.length()-2);

#if _TRiAS_VER < 0x0300
	ulong ulMCode = DEX_GetMCodeFromFeatureName (sKText.c_str());

		_ASSERTE (0 != ulMCode);
		_ASSERTE ((ulong)-1 != ulMCode);

		WriteFeatureText (lONr, ulMCode, TT_Objekt, sMInhalt);
#else
	ErrCode EC = EC_OKAY;	// return-Wert von CreateFeatureInPBD()
	ulong ulMCode = DEX_GetMCodeFromFeatureNameEx (hPr, sKText.c_str());

		// Merkmal sKText existiert noch nicht in der Ziel-Datenquelle
		if (0 == ulMCode || (ulong)-1 == ulMCode)
		{
			// neuen Merkmalscode geben lassen und Merkmal in PBD anlegen
			ulMCode = DEX_GetUniqueMCode();
			EC = CreateFeatureInPBD (ulMCode, sKText, sKText.length()+1, false, false,
									 ulIdent);
		}

		if (EC_OKAY == EC)
			WriteFeatureText (lONr, ulMCode, TT_Objekt, sMInhalt);
#endif // _TRiAS_VER < 0x0300
	}

	// sUIdent als UniqueIdent an das neue Objekt wegschreiben
	if (sUIdent.length() > 0)
		sMInhalt = sUIdent;
	else
	{
	ResString UniqueIdent (ResID (IDS_UIFORMAT, pRF), 20);

		Format (sMInhalt, (char*)UniqueIdent.Addr(), lONr);
	}

#if _TRiAS_VER < 0x0300
	return WriteFeatureText (lONr, DEX_GetUniqueIdentMCode(), TT_Objekt, sMInhalt);
#else
	return WriteFeatureText (lONr, DEX_GetUniqueIdentMCodeEx (hPr), TT_Objekt, sMInhalt);
#endif // _TRiAS_VER < 0x0300

} // TransmitParentsFeatures


// --------------------------------------------------------------------------------------------
// Member setzen
HRESULT ObjektOpExtension::SetMembers (IEnumLONG* pEnumOrig, IEnumLONG* pEnumOut)
{
	_ASSERTE (NULL != pEnumOrig);
	_ASSERTE (NULL != pEnumOut);

	_lAnzOrigObj = pEnumOrig->Count();
	m_lOrigInd = _lAnzOrigObj;

	DELETE_VEC (m_plOrigObjNr);		// Feld der Objektnummern der Original-Objekte löschen
	m_plOrigObjNr = new long [_lAnzOrigObj]; // Feld für diese neuen Objektnummern anlegen
	if (! m_plOrigObjNr)
	{
		DEX_Error (RC_objoper, EC_NOMEMORY);
		return E_OUTOFMEMORY;
	}

	pEnumOrig->Reset();

HRESULT hrRet = pEnumOrig->Next (_lAnzOrigObj, m_plOrigObjNr, NULL);

	_lAnzNeuObj = pEnumOut->Count();
	m_lNeuInd = _lAnzNeuObj;

	if (_lAnzNeuObj > 0)		// mindestens 1 Objekt erzeugt
	{
		DELETE_VEC (m_plNeuObjNr);	// Feld der Objektnummern der neuen Objekte löschen
		m_plNeuObjNr = new long [_lAnzNeuObj]; // Feld für diese neuen Objektnummern anlegen
		if (! m_plNeuObjNr)
		{
			DEX_Error (RC_objoper, EC_NOMEMORY);
			return E_OUTOFMEMORY;
		}

		pEnumOut->Reset();
		return pEnumOut->Next (_lAnzNeuObj, m_plNeuObjNr, NULL);
	}

	return hrRet;

} // SetMembers


// --------------------------------------------------------------------------------------------
// Anzeige der bei einer Objektoperation neu gebildeten Objekte und der dahintersteckenden
// Originalobjekte in je einem Recherchefenster;
// bDelete: verwendete Originalobjekte gelöscht (true)
void ObjektOpExtension::Ergebnisanzeige (void)
{
	if (_lAnzNeuObj > 0)	// neue Objekte durch Objektoperationen erzeugt
	{
	POINT pt;				// linker unterer Eckpunkt eines Recherchefensters
	int iRWHoehe = 0;		// Höhe des Recherchefensters (Anfangswert)

		pt.x = iRWZug; pt.y = 0;   // Anfangswerte
	
		if (_bNeuZeigen)						// Recherchefenster für neu erzeugte Objekte
			FensterNeueObjekte (pt, iRWHoehe);	//  generieren

		if (_bOrigZeigen && _lAnzOrigObj > 0)	// Recherchefenster für die ursprünglichen
			FensterAlteObjekte (pt, iRWHoehe);	//  Objekte generieren

// Das Zeichnen erfolgt schon an anderer Stelle (z.B. SchnittAusfuehren); ob das allerdings immer so ist,
// sei noch dahin gestellt (18.05.99)
//		MakeNewObjectsVisible();	// Bereich, in dem die neuen Objekte liegen, zeichnen

		_bMenLoeNeu = true;     // Menüeinträge für Löschen der neu erzeugten bzw.
//		bDelete ? (_bMenLoeOrig = false) : (_bMenLoeOrig = true);	//  Originalobjekte freigeben
		m_plOrigObjNr ? (_bMenLoeOrig = true) : (_bMenLoeOrig = false);	//  Originalobjekte freigeben
	}
	
	else	// keine neuen Objekte durch Objektoperationen erzeugt,
	{
		_bMenLoeNeu = false;     // deshalb Lösch-Menü's
		_bMenLoeOrig = false;    //  nicht freigeben
	}
} // Ergebnisanzeige


// --------------------------------------------------------------------------------------------
// Recherchefenster für neu erzeugte Objekte generieren
void ObjektOpExtension::FensterNeueObjekte (POINT& pt, int& iRWHoehe)
{
	if (! m_plNeuObjNr)
		return;

Rectangle CRc = MVWind()->CanvasRect();	// Größe des Hauptfensters

	pt.y += iRWHoehe + iRWZug;
	if (pt.y + iRWHoehe > CRc.Top())
	{
		pt.y = CRc.Top() - iRWHoehe;
		pt.x += 4*iRWZug;
	}

ResString Text (ResID (IDS_NEUEOBJ, pRF), 70);
CREATEOBJEKTINFOEX3 COI;	// Struktur für Recherchefenster
	
	INITSTRUCT (COI, CREATEOBJEKTINFOEX3);
	COI.lpCaption = (char*) Text.Addr();	// Fensterüberschrift
	COI.plObjs = m_plNeuObjNr;				// Objektnummern, die angezeigt werden sollen
	COI.lNumObjs = (int) _lAnzNeuObj;		// Anzahl der Objektnummern
	COI.cMColor = RGB (0,200,50);			// Markierungsfarbe (rot, grün, blau)
	COI.pntPos = pt;						// Position des Recherchefensters im Hauptfenster

HWND hWnd = DEX_CreateObjektInfo (COI);		// Recherchefenster erzeugen und anzeigen

	if (0 == iRWHoehe)	// Höhe des Recherchefensters ermitteln
	{
	pWindow pRW = ORWind (hWnd);				// Zeiger auf Recherchefenster geben lassen
	Rectangle RWRec = pRW->WindowRect();		// Größe des Recherchefensters

		iRWHoehe = RWRec.Top() - RWRec.Bottom();// Höhe des Recherchefensters 
	}
} // FensterNeueObjekte


// --------------------------------------------------------------------------------------------
// Recherchefenster für ursprüngliche Objekte, aus denen die neuen erzeugt wurden, generieren
void ObjektOpExtension::FensterAlteObjekte (POINT& pt, int& iRWHoehe)
{
	if (! m_plOrigObjNr)
		return;

Rectangle CRc = MVWind()->CanvasRect();	// Größe des Hauptfensters

	pt.y += iRWHoehe + iRWZug;
	if (pt.y + iRWHoehe > CRc.Top())
	{
		pt.y = CRc.Top() - iRWHoehe;
		pt.x += 4*iRWZug;
	}

ResString Text (ResID (IDS_ALTEOBJ, pRF), 70);
CREATEOBJEKTINFOEX3 COI;	// Struktur für Recherchefenster

	INITSTRUCT (COI, CREATEOBJEKTINFOEX3);
	COI.lpCaption = (char*) Text.Addr();	// Fensterüberschrift
	COI.plObjs = m_plOrigObjNr;				// Objektnummern, die angezeigt werden sollen
//	COI.iNumObjs = (int)m_lOrigInd;			// Anzahl der Objektnummern
	COI.lNumObjs = _lAnzOrigObj;			// Anzahl der Objektnummern (06.10.99)
	COI.cMColor = RGB (200,0,200);			// Markierungsfarbe (rot, grün, blau)
	COI.pntPos = pt;						// Position des Recherchefensters im Hauptfenster

HWND hWnd = DEX_CreateObjektInfo (COI);		// Recherchefenster erzeugen und anzeigen

	if (0 == iRWHoehe)	// Höhe des Recherchefensters ermitteln
	{
	pWindow pRW = ORWind (hWnd);			// Zeiger auf Recherchefenster geben lassen
	Rectangle RWRec = pRW->WindowRect();	// Größe des Recherchefensters

		iRWHoehe = RWRec.Top() - RWRec.Bottom();// Höhe des Recherchefensters 
	}
} // FensterAlteObjekte


// --------------------------------------------------------------------------------------------
// Feld für Objektnummern aller selektierten (markierten) Originalobjekte dynamisch anlegen;
// für bAkt == true wird das aktivierte (blinkenden) Objekt (wenn es auch selektiert, d.h.
// markiert ist) mitgezählt, bei false nicht
bool ObjektOpExtension::FeldAktObjNr (long*& plFeld, long& lInd, long& lAnzObj, bool bAkt)
{
// Anzahl der selektierten (markierten) Objekte von allen Recherchefenstern	ermitteln
ENUMLONGKEY ELK;	// Enumeration aller selektierten Objekte

	lAnzObj = 0;    // Anzahl der selektierten Objekte
	lInd = 0;       // Laufindex für plFeld
	ELK.eKey = (DWORD) 0;
	if (bAkt)
		ELK.eFcn = (ENUMLONGKEYPROC) AnzSelektObjekte;
	else
		ELK.eFcn = (ENUMLONGKEYPROC) ObjekteZaehlen;
	ELK.ePtr = (void*) &lAnzObj;
	DEX_EnumSelectedObjects (ELK);

	DELETE_VEC (plFeld);
	plFeld = new long[lAnzObj];
	if (! plFeld)
	{
		DEX_Error (RC_objoper, EC_NOMEMORY);
		return false;
	}
	return true;

} // FeldAktObjNr


// --------------------------------------------------------------------------------------------
// neu erzeugte Objekte nach Abspeicherung durch Neuzeichnen des Bereiches sichtbar machen
void ObjektOpExtension::MakeNewObjectsVisible (void)
{
	if (0 == m_lNeuInd) return;		// keine neuen Objekte

long lCO[4];	// Containerkoordinaten eines Objektes
				// lCO[0] = xmin, lCO[1] = xmax, lCO[2] = ymin, lCO[3] = ymax
long lGesCO[] = { LONG_MAX, LONG_MIN, LONG_MAX, LONG_MIN } ;

	_ASSERTE (m_plNeuObjNr != NULL);

	for (long i = 0; i < m_lNeuInd; i++)
	{
		DEX_GetObjContainer (m_plNeuObjNr[i], lCO);
		lGesCO[0] = min (lGesCO[0], lCO[0]);
		lGesCO[1] = max (lGesCO[1], lCO[1]);
		lGesCO[2] = min (lGesCO[2], lCO[2]);
		lGesCO[3] = max (lGesCO[3], lCO[3]);
	}

Point PLO, PRU;	// linker oberer bzw. rechter unterer Eckpunkt des zu visualisierenden
				// Ausschnitts

	PLO = BSKoordinaten (lGesCO[0], lGesCO[3]);
	PRU = BSKoordinaten (lGesCO[1], lGesCO[2]);
	PLO.X() -= m_dimDots.Width() * iZug;	// zu bildendes Rechteck noch mit Sicherheitszugabe
	PLO.Y() += m_dimDots.Height() * iZug;	//  iZug vergrößern
	PRU.X() += m_dimDots.Width() * iZug;
	PRU.Y() -= m_dimDots.Height() * iZug;
	
Rectangle Rec (PLO, PRU);
	 
	DEX_RePaintRectWait (Rec);

} // MakeNewObjectsVisible


// --------------------------------------------------------------------------------------------
// Objekte, deren Objektnummer in plObjNr stehen, in DB und auf Bildschirm (nur Ausschnitt)
// löschen
void ObjektOpExtension::ObjekteLoeschen (long*& plObjNr, long& lInd)
{
	if (0 == plObjNr || 0 == lInd)	// wo nichts ist, kann nichts gelöscht werden
		return;

	try
	{
	WProgressIndicator2 DPI (CLSID_ProgressIndicator);	// throws_com_error

		THROW_FAILED_HRESULT (InitProgressIndicator (DPI, ResID(IDS_DELOBJECTS, pRF),
													 ResID(IDS_DELETE_STATUS, pRF), lInd));
		THROW_FAILED_HRESULT (RegisterPI (DPI));
	}
	catch (_com_error&)
	{
		return;
	}

long lCO[4];	// Containerkoordinaten eines Objektes
				// lCO[0] = xmin, lCO[1] = xmax, lCO[2] = ymin, lCO[3] = ymax
long lGesCO[] = { LONG_MAX, LONG_MIN, LONG_MAX, LONG_MIN } ;

	_bObjLoesch = true;	// Objekte werden über Menüpunkt und nicht über Werkzeug "Schere" gelöscht

	for (long i = 0; i < lInd; i++)
	{
		DEX_GetObjContainer (plObjNr[i], lCO);
		lGesCO[0] = min (lGesCO[0], lCO[0]);
		lGesCO[1] = max (lGesCO[1], lCO[1]);
		lGesCO[2] = min (lGesCO[2], lCO[2]);
		lGesCO[3] = max (lGesCO[3], lCO[3]);

	HRESULT hr = GetPIProxy()->IsCanceled();	// Abbruch des Löschens?

		if (FAILED(hr) ||
			S_OK == hr ||	// Abbruch durch den Anwender
			FAILED(GetPIProxy()->IncrementPosition (NULL)))
			break;

		DEX_DeleteObjectEx (plObjNr[i]);
	}

	if (FAILED(UnRegisterPI())) return;

	_bObjLoesch = false;

	DELETE_VEC (plObjNr);
	lInd = 0;
	
Point PLO, PRU;	// linker oberer bzw. rechter unterer Eckpunkt des zu löschenden Ausschnitts

	PLO = BSKoordinaten (lGesCO[0], lGesCO[3]);
	PRU = BSKoordinaten (lGesCO[1], lGesCO[2]);
	PLO.X() -= m_dimDots.Width() * iZug;	// zu bildendes Rechteck noch um iZug mm
	PLO.Y() += m_dimDots.Height() * iZug;	// (in opdeklar.hxx definiert) vergrößern
	PRU.X() += m_dimDots.Width() * iZug;
	PRU.Y() -= m_dimDots.Height() * iZug;
	
Rectangle Rec (PLO, PRU);
	 
	DEX_RePaintRectWait (Rec);

	// Lösch-Menüpunkte inaktivieren
	_bMenLoeNeu = false;
	_bMenLoeOrig = false;
} // ObjekteLoeschen


// --------------------------------------------------------------------------------------------
// Bezug zur Erweiterung "GeometrieBereinigung" herstellen, wenn noch m_bGeoRein == false
IExtendGeoRein* ObjektOpExtension::GeoReinInterface (void)
{
//	if (m_bGeoRein) return S_FALSE;
	if (m_bGeoRein)
		return m_wGeoRein;

HRESULT hrRet;

    if (m_pXtnSite)
    	hrRet = m_pXtnSite->GetXtension (CLSID_GeometrieBereinigung, IID_IExtendGeoRein,
    									 (LPVOID*)&m_wGeoRein);
//	else hrRet = E_UNEXPECTED;

    if (FAILED (hrRet) ||	// Fehler, z.B. GeoRein.ext nicht verfügbar
    	! m_pXtnSite)
    {
    ResString resText (ResID (IDS_NOGEOREIN, pRF), 250);
    ResString resCapt (ResID (IDS_LONGCLASSNAME, pRF), 50);
    	
    	MessageBox (__hWndM, resText.Addr(), resCapt.Addr(), MB_ICONEXCLAMATION | MB_OK);
//    	return hrRet;
    	return NULL;
    }

    m_bGeoRein = true;
//	return S_OK;
	return m_wGeoRein;

} // GeoReinInterface   


// --------------------------------------------------------------------------------------------
// Initialisierung des ProgressIndicators2
HRESULT ObjektOpExtension::InitProgressIndicator (IProgressIndicator2* pPI, ResID uiTitel,
												ResID uiAdjust, ulong ulMaxPos, ulong ulMinPos)
{
	_ASSERTE (pPI != NULL);

// Parent setzen
HWND hWnd = NULL;
HRESULT hr = pPI->InitNew ((INT_PTR)MWind()->Handle(), 0L, (LONG *)&hWnd);

	if (FAILED(hr)) return hr; 

// min, max setzen
PIFLAGS rgFlags = (PIFLAGS)(PIFLAGS_STATUS |			// Anzeige der Statuszeile, 
 							PIFLAGS_TIME |				//  der verbleibenden Zeit,
							PIFLAGS_ADJUSTPERCENT |		//  des Prozentwertes und
#if _TRiAS_VER < 0x0300
							PIFLAGS_RESULT |			//	der Objektnummer
#endif
							PIFLAGS_INIT_SHOWWINDOW);	// erst dann Anzeige, wenn etwas zu
														//  sehen ist
	hr = pPI->Restart (ulMinPos, ulMaxPos, rgFlags);
	if (FAILED(hr)) return hr;

// Caption setzen
ResString resTitel (uiTitel, 100);
CComBSTR bstrTitel (resTitel.Addr());	// char* in Bi-String konvertieren

	hr = pPI->ChangeText (PIFLAGS_CAPTION, bstrTitel);
	if (FAILED(hr)) return hr;
			
// Adjust-Text setzen
ResString resAdjust (uiAdjust, 100);
CComBSTR bstrAdjust (resAdjust.Addr());

	hr = pPI->ChangeText (PIFLAGS_ADJUSTPERCENT, bstrAdjust);
	if (FAILED(hr)) return hr;

	return S_OK;
} // InitProgressIndicator


// --------------------------------------------------------------------------------------------
// Registrierung des ProgressIndicators2
HRESULT ObjektOpExtension::RegisterPI (IProgressIndicator2* pPI)
{
	try
	{
		_ASSERTE (m_dwCookie == 0);
		
	WConnectionPointContainer CPC (GetUnknown());	// throws_com_error
	WConnectionPoint CP;

		THROW_FAILED_HRESULT (CPC->FindConnectionPoint(IID_IProgressIndicator2, CP.ppi()));
		THROW_FAILED_HRESULT (CP->Advise(pPI, &m_dwCookie));
	}
	catch (_com_error& e) 
	{
		return _COM_ERROR (e);
	}

	return S_OK;
} // RegisterPI


// --------------------------------------------------------------------------------------------
// Abmeldung des ProgressIndicators2
HRESULT ObjektOpExtension::UnRegisterPI (void)
{
	if (0 == m_dwCookie) return S_FALSE;	// es wurde kein Advise() ausgeführt 

	try
	{
	WConnectionPointContainer CPC (GetUnknown());	// throws_com_error
	WConnectionPoint CP;

		THROW_FAILED_HRESULT (CPC->FindConnectionPoint(IID_IProgressIndicator2, CP.ppi()));
		THROW_FAILED_HRESULT (CP->Unadvise(m_dwCookie));
		m_dwCookie = 0L;
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

	return S_OK;
} // UnRegisterPI


// --------------------------------------------------------------------------------------------
// unabhängig vom Fehlercode iWC und vom Routinencode iRoutine, die in nachfolgend ignoriert
// werden, wird der als 3. Parameter (nach "iRoutine") runtergereichte Text in einer MessageBox
// angezeigt
int ErrHandler (int iWC, int iRoutine, ...)
{
va_list vaArgs;		// Liste der unbenannten Argumente

	va_start (vaArgs, iRoutine);

void* pvData = va_arg (vaArgs, void*);	// Makro, um die unbenannten Argumente herauszuholen

	va_end (vaArgs);

ResString resTitel (ResID (IDS_LONGCLASSNAME, pRF), 50);
				
	MessageBox (__hWndM, (char*)pvData, resTitel.Addr(), MB_ICONINFORMATION | MB_OK);

	return iWC;

} // ErrHandler
