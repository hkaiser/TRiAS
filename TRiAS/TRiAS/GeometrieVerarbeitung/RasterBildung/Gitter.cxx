// Funktionen für Erweiterungs-DLL "Bilden von Gittern"
// File: Gitter.cxx
// W. Mörtl

#include "RasterP.hxx"

#include <TRiASHelper_i.c>	// CLSID_PropertySequenceService

#include "version.h"		// RASTER_MAJORVERSION, ...
#include <initguid.h>		// wird für RastGuid.h (in Gitter.hxx) benötigt

#include "GeomDLL.hxx"		// InitGeometrie
#include "Koord.hxx"		// BSKoordinaten(), ...
#include "PopupMenu.hxx"	// InstallPopupMenu(), ...

#include "GitterPropAct.h"	// CGitterPropAct
#include "Gitter.hxx"


DefineSmartInterface(PropertySequenceService);	// WPropertySequenceService


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_OBJECT_MAP(ObjectMap)		// Makro
	OBJECT_ENTRY(CLSID_RasterExtension, RasterExtension)
	OBJECT_ENTRY(CLSID_GitterPropAct, CGitterPropAct)
END_OBJECT_MAP()

_ATL_OBJMAP_ENTRY* GetObjectMap (void)
{
	return ObjectMap;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung sich selbst in der
// RegDB registrieren soll (empfohlen!!).
// Der ProgID (hier 'TRiAS.Raster.1') ist eine Zeichenkette, die die Erweiterung in der RegDB
// repräsentiert. Das Format sollte beibehalten werden. Die '... .1' steht für die
// VersionsNummer.
// Der KlassenName (hier die Stringresource hinter IDS_LONGCLASSNAME) ist eine normal-lesbare
// Zeichenkette, die lokalisiert wird (deshalb in der Ressource) und die Bezeichnung der
// Erweiterung definiert.
BOOL UpdateRegistry (BOOL bRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (bRegister)
	{
	// RegDB initialisieren
		return ExtOleRegisterExtensionClass (g_hInstance,
				CLSID_RasterExtension, TEXT("TRiAS.Raster.1"), IDS_LONGCLASSNAME,
				RASTER_MAJORVERSION, RASTER_MINORVERSION,
				EFUnLoadable|EFVisible);
	}
	else
	{
	// RegDB säubern
		return ExtOleUnregisterClass (CLSID_RasterExtension, TEXT("TRiAS.Raster.1"));
	}

	return true;	// alles ok
}



///////////////////////////////////////////////////////////////////////////////////////////////
ResourceFile* pRF = NULL;



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
// Die Erweiterung wird von der Klasse 'CTriasExtension' abgeleitet.
// Durch den übergebenen Parameter (dem ResID des einzuhängenden Menüs) wird sowohl im
// Haupt- als auch im Objektrecherchfenster ein Gitter-Menü-Punkt eingefügt. Ohne diesen
// Parameter erfolgt der Menüeintrag nur im Hauptfenster.
RasterExtension :: RasterExtension (void)
				 : CTriasExtension (0, IDM_GITTERMENU)

#if !defined(__ATL_20_USED__)
				   , m_PPI(this)
#endif // !defined(__ATL_20_USED__)
{
	// Member initialisieren
	m_dwCookie = 0L;			// Nummer des ConnectionPoint

	m_pPopupMenu = NULL;
	m_lGridCnt = 0;				// Anzahl der erzeugten Gitterobjekte
	m_bEnableDelMenu = false;	// Menüpunkt für Löschen der Gitter noch nicht aktiviert
	m_bMenIt = false;			// MenuItem noch nicht installiert
	m_bGridsDeleted = false;
}


// --------------------------------------------------------------------------------------------
// Destruktor
RasterExtension :: ~RasterExtension (void) 
{
	DELETE_OBJ(m_pPopupMenu);
}



///////////////////////////////////////////////////////////////////////////////////////////////
// Im folgenden werden alle durch diese Erweiterung überladenen virtuellen Funktionen definiert

// --------------------------------------------------------------------------------------------
// Folgende Funktion wird einmalig nach der erfolgreichen Installation der Erweiterung durch
// TRiAS gerufen. Hier erfolgen alle notwendigen Initialisierungen.
STDMETHODIMP_(BOOL) RasterExtension :: InitExtension (short iMode)
{
	if (!CTriasExtension :: InitExtension (iMode))
		return false;

	InitGeometrie (hWnd(), __DexNotify, __DexCmd);
	pRF = &RF();
	
	_ASSERTE (NULL != pRF);

	m_iMode = iMode;
	if (iMode != LoadState())	// Erweiterung war schon teilweise geladen gewesen
		return true;			// jetzt ist sie voll zu sehen

	// TRiAS-Messages anfordern (nur 1 Parameter)
	// ich interessiere mich für die von TRiAS verschickten Meldungen:
	RegisterNotification (DEX_PROJECTOPEN);		// Schließen eines Projektes
	RegisterNotification (DEX_PROJECTCLOSE);	// Öffnen eines Projektes
	RegisterNotification (DEX_TXICHANGED);		// Veränderungen in der Identifikator-Datenbank
	RegisterNotification (DEX_DELOBJECT);		// Löschen eines Objektes

	InitAndOPEN (iMode);

	return true;
} // InitExtension


// --------------------------------------------------------------------------------------------
STDMETHODIMP_(BOOL) RasterExtension :: UnLoadExtension (void)
{
	// TRiAS-Messages wieder abmelden
	// ich interessiere mich nicht mehr für die von TRiAS verschickten Meldungen:
	UnRegisterNotification (DEX_DELOBJECT);
	UnRegisterNotification (DEX_TXICHANGED);
	UnRegisterNotification (DEX_PROJECTCLOSE);		// Schließen eines Projektes
	UnRegisterNotification (DEX_PROJECTOPEN);		// Öffnen eines Projektes
	
	// restliche Abmeldungen
	UnLoadAndCLOSE();
	
	return CTriasExtension :: UnLoadExtension();
}


// --------------------------------------------------------------------------------------------
// Diese Funktion dient der Behandlung der MenuKommandos der Erweiterung
STDMETHODIMP_(BOOL) RasterExtension :: MenuCommand (UINT MenuItemID, HWND hWnd)
{
WPropertySequenceService Service (CLSID_PropertySequenceService);
WProgressIndicator Status (CLSID_ProgressIndicator);

	Status -> InitNew (hWnd, PIFLAG_RESULT);

	Service -> put_ResourceModule(CComBSTR(g_pDLLName));

	switch (MenuItemID)
	{
		case IDM_GITTER:
		{
			COM_TRY
			{
				if (hWnd)	// Aufruf kam aus einem Objektrecherchefenster
				{
				WDataObject wDataCtx (CLSID_DataTransferObject);	// definieren eines Kontext-Objektes

					THROW_FAILED_HRESULT (SetHWNDData (hWnd, wDataCtx));	// Fenster-Handle eintragen

					// das eben definierte Kontext-Objekt wird durch die Service-Funktion der
					// nachfolgend gerufenen Sequence zugeordnet 
					THROW_FAILED_HRESULT (Service->putref_ContextData(WTRiASDataObject(wDataCtx)));
				}

				THROW_FAILED_HRESULT (Service->RunActionSequence(reinterpret_cast<INT_PTR>(hWnd),
							  CComBSTR("GridGenerating.xml"), CComBSTR(""), CComBSTR("Gitter"),
							  WProgressIndicator2(Status), NULL, VARIANT_FALSE, NULL));
			}
			COM_CATCH_OP(return false);


			if (m_lGridCnt > 0)
				m_bEnableDelMenu = true;	// Menüpunkt für Löschen der Gitter aktivieren
			else
			{
			ResString Titel (ResID (IDS_LONGCLASSNAME, pRF), 50);
			ResString Text (ResID (IDS_NOGITTER, pRF), 150);
		
				MessageBox (hWnd, Text.Addr(), Titel.Addr(), MB_ICONEXCLAMATION | MB_OK);
				m_bEnableDelMenu = false;
			}
			return true;
		}


		case IDM_LOESCHEN:	// Menüpunkt: neu erzeugte Gitter löschen
		{
		bool bRet = true;	// return-Wert

			COM_TRY
			{
			WProgressIndicator2 wPI (CLSID_ProgressIndicator);	// throws_com_error
			HRESULT hr = InitProgressIndicator (wPI, ResID(IDS_DELOBJECTS, pRF),
												ResID(IDS_DELETE_STATUS, pRF), m_lGridCnt);
			
				if (FAILED(hr)) return false;
				hr = RegisterPI (wPI);
				if (FAILED(hr)) return false;

			}
			COM_CATCH_OP(return false);

			m_bGridsDeleted = true;	// das jetzt ausgeführte Löschen der Gitterobjekte wurde 
									//  über den Menüpunkt "Gitter löschen" ausgelöst; deshalb
									//  ist der Aufruf von DEX_DELOBJECT im Augenblick uninteressant

			for (long l = 0; l < m_lGridCnt; ++l)
			{
			HRESULT hr = GetPIProxy()->IsCanceled();	// Abbruch des Löschens?

				if (FAILED(hr) ||
					S_OK == hr ||	// Abbruch durch den Anwender
					FAILED(GetPIProxy()->IncrementPosition (NULL)))
				{
				ResString resText (ResID (IDS_CANCEL, pRF), 100);				
				ResString resTitel (ResID (IDS_LONGCLASSNAME, pRF), 50);

					MessageBox (hWnd, resText.Addr(), resTitel.Addr(), MB_ICONEXCLAMATION | MB_OK);
					bRet = false;
					break;
				}

				DEX_DeleteObjectEx (m_vlObjNr[l]);

			}

			// wenn ALLE Gitterobjekte gelöscht wurden, Lösch-Menüpunkt deaktivieren
			if (l == m_lGridCnt)
				m_bEnableDelMenu = false;
			else
			{
				for (long ll = 0; ll < m_lGridCnt-l; ++ll)
					m_vlObjNr[ll] = m_vlObjNr[ll+l];
				m_lGridCnt -= l;
			}


			if (FAILED(UnRegisterPI())) return false;

			m_bGridsDeleted = false;	// das über den Menüpunkt "Gitter löschen" ausgelöste
										//  Löschen ist jetzt beendet

		// Bereich nach Löschen neu zeichnen
		Point PLO = BSKoordinaten (m_PaintRecRO, m_PaintRecHO);	// linker oberer bzw.
		Point PRU = BSKoordinaten (m_PaintRecRU, m_PaintRecHU);	//  rechter unterer Eckpunkt im
		Rectangle Rec (PLO, PRU);								//  Point-Format

			DEX_RePaintRectWait (Rec);
			
			return bRet;
		}

		default:
			_ASSERTE (false);
			break;
	}

	DEX_Error (RC_MenuCommandGitter, EC_ERRMENUITEMID);	// Fehlermeldung
	return false;

} // MenuCommand


// --------------------------------------------------------------------------------------------
// Diese Funktion initialisiert das Menü
STDMETHODIMP_(BOOL) RasterExtension :: MenuInit (HMENU hMenu, LPARAM, HWND hWnd)
{
	if (m_bEnableDelMenu) // Menüpunkt für Löschen der neu erzeugten Objekte
		EnableMenuItem (hMenu, IDM_LOESCHEN+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
	else
		EnableMenuItem (hMenu, IDM_LOESCHEN+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

	if (NULL == pExtMenu())
		return false;
	return true;
}


// --------------------------------------------------------------------------------------------
// Diese Funktion wird bei Systemereignissen diverser Natur gerufen, z.B. Projekt öffnen
STDMETHODIMP_(LRESULT) RasterExtension :: Notification (WPARAM iMsg, LPARAM p)
{
	switch (iMsg)
	{
		case DEX_PROJECTOPEN:		// Projekt wird geöffnet
			InitAndOPEN (m_iMode);
			break;
	
		case DEX_PROJECTCLOSE:		// Projekt wird geschlossen
			UnLoadAndCLOSE();
			break;
			
		case DEX_DELOBJECT:		// ein Objekt wurde gelöscht
			// diese Message interessiert nicht, wenn die zuletzt erzeugten Gitter über den
			// Menüpunkt "Gitter löschen" gelöscht werden (m_bGridsDeleted == true) bzw. wenn gar
			// keine Gitter erzeugt wurden (m_lGridCnt == 0)
			if (m_bGridsDeleted || 0 == m_lGridCnt)
				break;

			// für die zuletzt erzeugten Gitter besteht noch Löschmöglichkeit über Menüpunkt
			if (m_lGridCnt > 0)
			{
			bool bLastGrid = false;	// das soeben gelöschte Objekt ist ein ZULETZT erzeugtes
									// Gitter (true)

				for (long l = 0; l < m_lGridCnt; ++l)
				{
					// p ist die Objektnummer des soeben gelöschten Objektes
					if (m_vlObjNr[l] == p)
						bLastGrid = true;	// das soeben gelöschte Objekt gehört zu den
											//  zuletzt erzeugten Gittern
					if (bLastGrid && l < m_lGridCnt-1)
						m_vlObjNr[l] = m_vlObjNr[l+1];	// dann dessen Objektnummer durch
														//  Verschieben löschen
				}
				if (bLastGrid)
					m_lGridCnt--;
			}

			if (0 == m_lGridCnt)	// m_lGridCnt wurde durch vorstehenden Dekrement-Befehl gleich 0
				m_bEnableDelMenu = false;	// Lösch-Menüpunkt inaktivieren
			break;
					
		default:	// Notifikationen der Basisklasse
			break;
	}

	return CTriasExtension :: Notification (iMsg, p);

} // Notification


// --------------------------------------------------------------------------------------------
// Aktionen, die bei InitExtension und DEX_PROJECTOPEN gleich sind
bool RasterExtension :: InitAndOPEN (int iMode)
{
	// IdentList und CoordTransX anlegen
	if (DEX_TestActiveProject())    // ein Projekt ist schon geöffnet
	{
		if (iMode == LEFullLoad && m_bMenIt == false)
		{
			// zusätzliche Menüpunkte im Hauptmenü (false) "Extras" anhängen
#if _TRiAS_VER < 0x0300
			InstallMenuItem (IDM_GITTER, IDS_GITTER, false, EXTRA_MENU_POS);
			InstallMenuItem (IDM_LOESCHEN, IDS_LOESCHEN, false, EXTRA_MENU_POS);
#else
			m_pPopupMenu = new Menu (ResID (IDM_GITTERMENU, pRF));
			if (m_pPopupMenu)
				InstallPopupMenu (hDex(), m_pPopupMenu);
			else
			{
				DEX_Error (RC_Gitter, EC_NOMEMORY);
				return false;
			}
#endif // _TRiAS_VER < 0x0300

			m_bMenIt = true;
		}
	}

	return true;

} // InitAndOPEN


// --------------------------------------------------------------------------------------------
// Aktionen, die bei UnLoadExtension und DEX_PROJECTCLOSE gleich sind
void RasterExtension :: UnLoadAndCLOSE (void)
{
	m_bEnableDelMenu = false;		// Lösch-Menüpunkt deaktivieren

// Menüpunkte entfernen
	if (m_bMenIt)
	{
#if _TRiAS_VER < 0x0300
		RemoveMenuItem (IDM_GITTER, false, EXTRA_MENU_POS);
		RemoveMenuItem (IDM_LOESCHEN, false, EXTRA_MENU_POS);
#else
		RemovePopupMenu (hDex());
#endif // _TRiAS_VER < 0x0300

		m_bMenIt = false;
	}
} // UnLoadAndCLOSE


// --------------------------------------------------------------------------------------------
// Übergeben der Ergebnisse der Gitterbildung von der Geokomponente CGitterPropAct
// - lGridCnt:         Anzahl der erzeugten Gitterobjekte
// - vlObjNr:          Objektnummern
// - PLO, PRU:         Bereich, in dem die Gitterbildung erfolgte
// - dXWidth, dYWidth: Gitterbreite und -höhe (in DB-Verhältnissen)
void RasterExtension :: ReturnResults (long lGridCnt, vector<long> vlObjNr, EPunkt PLO,
									   EPunkt PRU, double dXWidth, double dYWidth)
{
	m_lGridCnt = lGridCnt;

	m_vlObjNr.resize (m_lGridCnt);
	for (long l = 0; l < m_lGridCnt; ++l)
		m_vlObjNr[l] = vlObjNr[l];

	m_PaintRecRO = PLO.X() - DtoL((PLO.Y()-PRU.Y())/2. + 2.*dXWidth);	// Container mit
	m_PaintRecRU = PRU.X() + DtoL((PLO.Y()-PRU.Y())/2. + 2.*dXWidth);	//  "Zugaben"
	m_PaintRecHU = PRU.Y() - DtoL((PRU.X()-PLO.X())/2. + 2.*dYWidth);
	m_PaintRecHO = PLO.Y() + DtoL((PRU.X()-PLO.X())/2. + 2.*dYWidth);
}


// --------------------------------------------------------------------------------------------
// Initialisierung des ProgressIndicators2
HRESULT RasterExtension :: InitProgressIndicator (IProgressIndicator2* pPI, ResID uiTitel,
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
HRESULT RasterExtension :: RegisterPI (IProgressIndicator2* pPI)
{
	COM_TRY
	{
		_ASSERTE (0 == m_dwCookie);
		
	WConnectionPointContainer CPC (this);		// throws_com_error
	WConnectionPoint CP;

		THROW_FAILED_HRESULT(CPC->FindConnectionPoint(IID_IProgressIndicator2, CP.ppi()));
		THROW_FAILED_HRESULT(CP->Advise(pPI, &m_dwCookie));

	}
	COM_CATCH;

	return S_OK;

} // RegisterPI


// --------------------------------------------------------------------------------------------
// Abmeldung des ProgressIndicators2
HRESULT RasterExtension :: UnRegisterPI (void)
{
	if (0 == m_dwCookie) return S_FALSE;	// es wurde kein Advise() ausgeführt 

	COM_TRY
	{
	WConnectionPointContainer CPC (this);	// throws_com_error
	WConnectionPoint CP;

		THROW_FAILED_HRESULT(CPC->FindConnectionPoint(IID_IProgressIndicator2, CP.ppi()));
		THROW_FAILED_HRESULT(CP->Unadvise(m_dwCookie));
		m_dwCookie = 0L;

	}
	COM_CATCH;

	return S_OK;
	
} // UnRegisterPI
