// Funktionen für Erweiterungs-DLL "Puffer um GeoObjekte"
// File: Buffer.cxx
// W. Mörtl


#include "BufferP.hxx"

#include <ospace/com/iterenum.h>	// IEnum<LONG>

#include <resstrg.h>				// IDS_UIFORMAT

#include "BufferR.h"				// Ressourcekonstanten für diese Erweiterung (IDM_BUFFER, ...)

#include "GeomDLL.hxx"				// InitGeometrie()
#include "GeoTrias.hxx"				// GeometrieAnTRIAS()
#include "DatBank.hxx"				// MerkmaleKopieren()
#include "Koord.hxx"				// BSKoordinaten()
#include "FormatString.hxx"			// Format()

#include <initguid.h>				// wird für *guid.h benötigt
#include "version.h"				// BUFFER_MAJORVERSION

#include "Buffer.hxx"				// BufferExtension


#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif



///////////////////////////////////////////////////////////////////////////////////////////////
// globale Parameter
extern UINT __DexNotify;
extern UINT __DexCmd;



///////////////////////////////////////////////////////////////////////////////////////////////
// An Stelle der Funktionen NewExtension und GetExtensionCLSID muß die Erweiterung jetzt in der
// ATL ObjectMap eingetragen werden (zusammen mit allen anderen ATL-Objekten)
BEGIN_OBJECT_MAP(ObjectMap)		// Makro
	OBJECT_ENTRY(CLSID_BufferExtension, BufferExtension)
END_OBJECT_MAP()


// --------------------------------------------------------------------------------------------
// mit der folgenden Funktion wird die ObjectMap in den ClassFactory-Mechanismus dieser
// Erweiterung eingebunden
_ATL_OBJMAP_ENTRY* GetObjectMap (void)
{
	return ObjectMap;
}


// --------------------------------------------------------------------------------------------
// Die Funktion UpdateRegistry muß definiert werden, wenn die Erweiterung sich selbst in der
// der RegDB registrieren soll (empfohlen!!).
// Der ProgID (hier 'TRiAS.Puffer.1') ist eine Zeichenkette, die die Erweiterung in der RegDB
// repräsentiert. Das Format sollte beibehalten werden. Die '... .1' steht für die
// VersionsNummer.
// Der KlassenName (hier die Stringresource hinter IDS_LONGCLASSNAME) ist eine normal-lesbare
// Zeichenkette, die lokalisiert wird (deshalb in der Ressource) und die Bezeichnung der
// Erweiterung definiert.
BOOL UpdateRegistry (BOOL bRegister)	// RegDB aktualisieren (initialisieren/löschen)
{
	if (bRegister)	// RegDB initialisieren
		return ExtOleRegisterExtensionClass (g_hInstance, CLSID_BufferExtension,
								TEXT("TRiAS.Puffer.1"), IDS_LONGCLASSNAME, BUFFER_MAJORVERSION,
								BUFFER_MINORVERSION, EFUnLoadable|EFVisible);
	else			// RegDB säubern
		return ExtOleUnregisterClass (CLSID_BufferExtension, TEXT("TRiAS.Puffer.1"));

	return true;	// alles ok
}


// --------------------------------------------------------------------------------------------
ResourceFile* pRF = NULL;



// --------------------------------------------------------------------------------------------
// um alle selektierten (markierten) Objekte, deren Objektnummern bez. des in ELK.eKey der
// Struktur ENUMLONGKEY ELK angegebenen Suchschlüssels bereitstellen werden, einen Puffer
// legen
BOOL _BUFFER_EXPORT FAR PASCAL AlleObjektePuffern (long lONr, BOOL, void*)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

	if (0 == lONr || -1 == lONr) return false;	// Objektnummer fehlerhaft

	return ((BufferExtension*)g_pTE)->PufferBilden (lONr);
}





///////////////////////////////////////////////////////////////////////////////////////////////
int ErrHandler (int iWC, int iRoutine, ...);



///////////////////////////////////////////////////////////////////////////////////////////////
// Konstruktor
// Die Erweiterung wird von der Klasse 'CTriasExtension' abgeleitet, welche wiederum als
// einzigen Parameter den ResID des im Hauptfenster einzuhängenden Menüs übergeben bekommt.
BufferExtension :: BufferExtension (void)
				 : CTriasExtension (0, IDM_BUFFERMENU)

#if !defined(__ATL_20_USED__)
				   , m_PPI(this)
#endif // !defined(__ATL_20_USED__)
{
	// Member initialisieren
	m_dwCookie = 0L;		// Nummer des ConnectionPoint

	m_pW = NULL;
	m_pCT = NULL;
    m_bGeoRein = false;		// Ankopplung von GeoRein.ext über Interface noch nicht erfolgt
	m_plONr = NULL;			// Objektnummer-Feld der gebildeten Pufferflächen
	m_lObjInd = 0;			// Laufindex von m_plONr
	_LoeMenAkt = false;		// Lösch-Menüpunkt noch nicht aktiviert
	m_dWidth = dBuffWidth;
	m_iPuffAnzahl = iBuffNum;
	_bTyp = true;			// Puffertyp: echter Puffer
	m_PBau = PBAU_RING;		// Puffer ringförmig
//	m_PBauSave = PBAU_RING;	// Puffer ringförmig
	m_cmMode = BUFF_ARC;	// konvexen Ecken als Kreisbogen
	m_dPrec = dFacEdgeLen * m_dWidth;	// Kantenlänge (in Meter) des n-Ecks an konvexen Ecken
	m_bsSide = BUFF_BOTH;	// Puffer soll beidseitig gebildet werden
	_bPuffLoesch = false;
}


// --------------------------------------------------------------------------------------------
// Destruktor
BufferExtension :: ~BufferExtension (void)
{
    // Interface's wieder freigeben
    m_wGeoRein.Assign (0);
}


///////////////////////////////////////////////////////////////////////////////////////////////
// Im folgenden werden alle durch diese Erweiterung überladenen virtuellen Funktionen definiert

// Folgende Funktion wird einmalig nach der erfolgreichen Installation der Erweiterung durch
// TRiAS gerufen. Hier erfolgen alle notwendigen Initialisierungen.
STDMETHODIMP_(BOOL) BufferExtension :: InitExtension (short iMode)
{
	if (!CTriasExtension :: InitExtension (iMode))
		return false;

	InitGeometrie (hWnd(), __DexNotify, __DexCmd);
	pRF = &RF();
	
	_ASSERTE (pRF != NULL);

ErrCode rcDummy;

	DEX_ErrInstall (rcDummy, WC_MESSAGE_BUFF, ErrHandler, &m_oldEH);

	m_iMode = iMode;
	if (iMode != LoadState())	// Erweiterung war schon teilweise geladen gewesen
		return true;			// jetzt ist sie voll zu sehen

// TRiAS-Messages anfordern (nur 1 Parameter)
// ich interessiere mich für die von TRiAS verschickten Meldungen:
	RegisterNotification (DEX_PROJECTOPEN);		// Schließen eines Projektes
	RegisterNotification (DEX_PROJECTCLOSE);	// Öffnen eines Projektes
	RegisterNotification (DEX_DELOBJECT);
	RegisterNotification (DEX_N_SAVECOMPLETED);

	InitAndOPEN (iMode);

// georein.ext automatisch nachladen
ResString GeoRein (ResID (IDS_GEOREIN, pRF), 20);
	
	DEX_ExternalLoadExtension (GeoRein.Addr());

	return true;
} // InitExtension
	

// -----------------------------------------------------------------------------------------------
STDMETHODIMP_(BOOL) BufferExtension :: UnLoadExtension (void)
{
	// TRiAS-Messages wieder abmelden
	// ich interessiere mich nicht mehr für die von TRiAS verschickten Meldungen:
	UnRegisterNotification (DEX_N_SAVECOMPLETED);
	UnRegisterNotification (DEX_DELOBJECT);
	UnRegisterNotification (DEX_PROJECTCLOSE);		// Schließen eines Projektes
	UnRegisterNotification (DEX_PROJECTOPEN);		// Öffnen eines Projektes

ErrCode rcDummy;

	DEX_ErrInstall (rcDummy, WC_MESSAGE_BUFF, m_oldEH, NULL);
	
	// restliche Abmeldungen
	UnLoadAndCLOSE();

	return CTriasExtension :: UnLoadExtension();
} // UnLoadExtension
							    

// -----------------------------------------------------------------------------------------------
// Diese Funktion dient der Behandlung der MenuKommandos der Erweiterung
STDMETHODIMP_(BOOL) BufferExtension :: MenuCommand (UINT MenuItemID, HWND hWnd)
{
	_hWnd = hWnd;

	switch (MenuItemID)
	{   
		case IDM_BUFFER:	// Menüpunkt: Puffer erzeugen
		{
		Parameter BW (m_pW, ResID (IDD_BUFFER, pRF));

			// die vorhergehende Parameterauswahl wieder einstellen
			BW.VorigeEinstellung (m_dWidth, m_iPuffAnzahl, _bTyp, m_PBau, m_cmMode, m_dPrec);
			BW.Show();  // DialogBox anzeigen

			if (BW.Result())	// Click auf OK-Button
			{
				m_dWidth = BW.GetBreite();
				m_iPuffAnzahl = BW.GetAnzahl();
				_bTyp = BW.GetTyp();		// Puffertyp
				m_PBau = BW.GetRing();		// Puffer ringförmig oder als volle Fläche	
//				m_PBauSave = BW.GetRingSave();// Puffer ringförmig oder als volle Fläche	
				m_cmMode = BW.GetMode();	// Form der kovexen Ecken
				m_dPrec = BW.GetPrec();		// Kantenlänge für Quasi-Kreisbogen

			// Objektnummern aller selektierten (markierten) Objekte bereitstellen
			ENUMLONGKEY ELK;	// Struktur für Enumeration mit einem long-Key (hier: alle
								// selektierten Objekte)
			long lAnzObj = 0;	// Anzahl der selektierten Objekte

				ELK.eKey = (DWORD) 0;			// Suchschlüssel (Fenster-Handle von allen
												// Recherchefenstern)
				ELK.eFcn = (ENUMLONGKEYPROC) AnzSelektObjekte;  // zu rufende Funktion
				ELK.ePtr = (void*) &lAnzObj;	// Anzahl der selektierten (markierten) Objekte
												// durchreichen
				DEX_EnumSelectedObjects (ELK);

				if (0 == lAnzObj)
				{
				ResString Titel (ResID (IDS_LONGCLASSNAME, pRF), 100);
				ResString Text (ResID (IDS_NOMARK, pRF), 80);
			
					MessageBox (hWnd, Text.Addr(), Titel.Addr(), MB_ICONEXCLAMATION | MB_OK);
					return true;
				}

				m_lAnzPuff = m_iPuffAnzahl * lAnzObj;
				DELETE_VEC (m_plONr);			// Feld der Objektnummern der Puffer löschen
				m_plONr = new long[m_lAnzPuff];	// und für die neuen Objektnummern erneut anlegen
				if (! m_plONr)
				{
					DEX_Error (RC_MenuCommandBuffer, EC_NOMEMORY);
					return false;
				}              
				
				m_lObjInd = 0;   // Laufindex für m_plONr

				ELK.eFcn = (ENUMLONGKEYPROC) AlleObjektePuffern;	// zu rufende Funktion
				DEX_EnumSelectedObjects (ELK);

				if (m_lObjInd > 0)	// es wurden Pufferflächen erzeugt
				{
				Rectangle Rec;	// Bereich für Neuzeichnen

					RangeToPaint (Rec);
					DEX_RePaintRectWait (Rec);
					_LoeMenAkt = true;	// Lösch-Menüpunkt im Recherchemenü aktivieren
				}
				else
					_LoeMenAkt = false;
			}
			return true;     // Abbruch-Button == 0: ohne Reaktion
		}


		case IDM_BUFLOESCHEN:       // Menüpunkt: Puffer löschen
			PufferLoeschen();
			return true;


		default:
			_ASSERTE (false);
	}

	DEX_Error (RC_MenuCommandBuffer, EC_ERRMENUITEMID);    // Fehlermeldung
	return false;
} // MenuCommand


// -----------------------------------------------------------------------------------------------
// Diese Funktion initialisiert das Menü
STDMETHODIMP_(BOOL) BufferExtension :: MenuInit (HMENU hMenu, LPARAM, HWND hWnd)
{
	if (hWnd && ORWind (hWnd))	// ORWind() liefert pWindow-Zeiger auf ObjektRechercheFenster
		m_pW = ORWind (hWnd);	// damit können alle weiteren Fenster auf das
								// ObjektRechercheFenster bezogen werden
	else
		m_pW = MWind();			// MWind() liefert pWindow-Zeiger auf HauptFenster
		
	if (_LoeMenAkt)
		EnableMenuItem (hMenu, IDM_BUFLOESCHEN+MenuOffset(), MF_BYCOMMAND|MF_ENABLED);
	else
		EnableMenuItem (hMenu, IDM_BUFLOESCHEN+MenuOffset(), MF_BYCOMMAND|MF_GRAYED);

	if (NULL == pExtMenu())
		return false;
	return true;
} // MenuInit


// -----------------------------------------------------------------------------------------------
// Diese Funktion wird bei Systemereignissen diverser Natur gerufen, z.B. Projekt öffnen
STDMETHODIMP_(LRESULT) BufferExtension :: Notification (WPARAM iMsg, LPARAM p)
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
			// diese Message interessiert nicht, wenn die zuletzt erzeugten Puffer über den
			// Menüpunkt "Puffer löschen" gelöscht werden (_bPuffLoesch == true) bzw. wenn gar
			// keine Puffer erzeugt wurden (m_lObjInd == 0)
			if (_bPuffLoesch || 0 == m_lObjInd)
				break;

			if (m_lObjInd > 0)	// für die zuletzt erzeugten Puffer besteht noch
			{					// Löschmöglichkeit über Menüpunkt
			bool bPuff = false;	// das soeben gelöschte Objekt ist ein/kein zuletzt erzeugter
								// Puffer (true/false)

				for (int i = 0; i < m_lObjInd; i++)
				{
					if (m_plONr && m_plONr[i] == p)	// p ist die Objektnummer des soeben
													// gelöschten Objektes
						bPuff = true;	// das soeben gelöschte Objekt gehört zu den zuletzt
										// erzeugten Puffern
					if (bPuff && i < m_lObjInd-1)
						m_plONr[i] = m_plONr[i+1];	// dann dessen Objektnummer durch
				}									// Verschieben löschen
				if (bPuff)
					m_lObjInd--;
			}
			if (0 == m_lObjInd)	// m_lObjInd wurde durch vorstehenden Dekrement-Befehl gleich 0
				_LoeMenAkt = false;	// Lösch-Menüpunkt inaktivieren
			break;

		case DEX_N_SAVECOMPLETED:
			DELETE_OBJ (m_pCT);
			m_pCT = new CoordTransX();	// Klasse für KoordinatenTransformation
			if (!m_pCT)
				DEX_Error (RC_buffer, EC_NOMEMORY);
			break;
					
		default:	// Notifikationen der Basisklasse
			break;
	}

	return CTriasExtension :: Notification (iMsg, p);

} // Notification


// ------------------------------------------------------------------------------------------------
// Aktionen, die bei InitExtension und DEX_PROJECTOPEN gleich sind
bool BufferExtension :: InitAndOPEN (int iMode)
{
// CoordTransX anlegen
	if (DEX_TestActiveProject())    // ein Projekt ist schon geöffnet
	{
		DELETE_OBJ (m_pCT);
		m_pCT = new CoordTransX();	// Klasse für KoordinatenTransformation
		if (! m_pCT)
		{                                                                      
			DEX_Error (RC_buffer, EC_NOMEMORY);
			return false;
		}
	}

	return true;
} // InitAndOPEN


// ------------------------------------------------------------------------------------------------
// Aktionen, die bei UnLoadExtension und DEX_PROJECTCLOSE gleich sind
void BufferExtension :: UnLoadAndCLOSE (void)
{
	_LoeMenAkt = false;		// Lösch-Menüpunkt deaktivieren

// dynamische Felder freigeben
	DELETE_OBJ (m_pCT);
	DELETE_VEC (m_plONr);	// Feld der Objektnummern der Puffer löschen

} // UnLoadAndCLOSE


// -----------------------------------------------------------------------------------------------
// Puffer (_bTyp == true) der Breite "m_dWidth" um lONr-GeoObjekt;
// Kreis (_bTyp == false) mit Radius "m_dWidth" um den Container-Mittelpunkt
// ulBIdent: vorgegebener BasisIdentifikator für Pufferung
bool BufferExtension :: PufferBilden (long lONr, ulong ulBIdent, bool bFortAnz)
{
	_ASSERTE (lONr != 0);
	_ASSERTE (lONr != -1);

	if (m_dWidth < 0. && OT_FLAECHE != DEX_GetObjectType (lONr))
	{
	ResString Titel (ResID (IDS_LONGCLASSNAME, pRF), 100);
	ResString Text (ResID (IDS_NEGATIVEWIDTH, pRF), 80);
			
		MessageBox (__hWndM, Text.Addr(), Titel.Addr(), MB_ICONERROR | MB_OK);
		return true;	// "true", damit der Puffer wenigstens für Flächenobjekte  gebildet wird
	}

	GeoReinInterface();
	if (S_FALSE != FehlerhaftesObjekt (m_wGeoRein, lONr))
	{
	string sBuffer;
	ResString resText (ResID (IDS_GEOFEHL, pRF), 150);

		Format (sBuffer, (char*)resText.Addr(), lONr);

	ErrCode rcDummy;

		DEX_SetError (rcDummy, 0, WC_MESSAGE_BUFF, (void*)sBuffer.c_str());
		return false;
	}

CEierUhr Wait (MVWind());
IObjektGeometrie* pIOG = NULL;

	if (FAILED(CreateInterfaceOG (&pIOG, lONr)))
		return false;

bool bRet = true;	// return-Wert dieser Routine

// Parameter des zu puffernden Objektes
ulong ulObjIdent;
short iOT;
long lCnt;
KoOrd* plXK; KoOrd* plYK;
long* plCnt;

	pIOG->GetIdent (&ulObjIdent);
	pIOG->GetObjTyp (&iOT);
	pIOG->GetCnt (&lCnt);
	pIOG->GetX ((void**)&plXK);
	pIOG->GetY ((void**)&plYK);
	pIOG->GetLPCnt (&plCnt);

	switch (iOT)
	{
		case OT_PUNKT:
			bRet = PunktPuffer (lONr, ulObjIdent, plXK, plYK, ulBIdent, bFortAnz);
			break;

		case OT_KANTE:
			bRet = KantenPuffer (lONr, ulObjIdent, plXK, plYK, lCnt, ulBIdent, bFortAnz);
			break;

		case OT_FLAECHE:
			bRet = FlaechenPuffer (lONr, ulObjIdent, plXK, plYK, plCnt, ulBIdent, bFortAnz);
			break;

		default:	// Objekt weder Punkt, Linie noch Fläche
			_ASSERTE (false);
			DEX_Error (RC_PufferBilden, EC_NOGEOOBJEKT);   // Fehlermeldung
			bRet = false;
	} // switch

	pIOG->Release();
	return bRet;

} // PufferBilden


// -----------------------------------------------------------------------------------------------
// gemeinsamer Teil für PunktPuffer(), KantenPuffer() und FlaechenPuffer()
// - Puffer-Nummer setzen
// - Identifikator ulBufIdent eines Puffers ermitteln (ulBIdent ist ein evtl. vorgegebener
//   BasisIdentifikator)
// - Speicherform sfSForm (permanent / temporär) ermitteln
bool BufferExtension :: Vorarbeit (int i, ulong ulBIdent, long lONr, ulong ulObjIdent,
								   ulong& ulBufIdent, SpForm& sfSForm)
{
// Kurztext des Identifikator des zu puffernden Objektes ermitteln
string sKText;

	GetKurzText (ulObjIdent, 'i', sKText);
	
// sowohl für echten Puffer als auch für Mittelpunktskreis den gleichen Kurztext
ResString resText (ResID(IDS_PUFFER, pRF), 100);
string sFormat;

	sFormat = resText.Addr();
	sFormat += "%s";
	Format (m_sBuffer, (char*)sFormat.c_str(), i, sKText.c_str());

	if (0 == ulBIdent || (ulong)-1 == ulBIdent)	// kein BasisIdentifikator vorgegeben
	{
	string sBuffer (m_sBuffer, 0, iKurzTextLen-1);	// vom Kurztext werden nur 32 Zeichen
													// berücksichtigt
#if _TRiAS_VER < 0x0300
		// in TRiAS2 liefert DEX_GetIdentFromClassName() immer 0 zurück; Hartmut will aber an
		// diesem TRiAS nichts mehr machen (15.07.99)
		ulBufIdent = DEX_GetIdentFromClassName (sBuffer.c_str());
		if (0 == ulBufIdent)	// dieser Identifikator ist noch nicht in der PBD
		{
			ulBufIdent = DEX_GetUniqueICode();
			IdentNachtragen (ulBufIdent, m_sBuffer, /*true*/false);	// 08.07.99
		}
#else
	HPROJECT hPr = DEX_GetObjectProject (lONr);

		ulBufIdent = DEX_GetIdentFromClassNameEx (hPr, sBuffer.c_str());
		if (0 == ulBufIdent)	// dieser Identifikator ist noch nicht in der PBD
		{
			ulBufIdent = DEX_GetUniqueICodeEx (hPr);
			IdentNachtragen (ulBufIdent, m_sBuffer, /*true*/false);	// 08.07.99
		}
#endif // _TRiAS_VER < 0x0300
	}
	else
	{
		ulBufIdent = ulBIdent + i - 1;		// 1. BufferIdent entspricht Vorgabe
		IdentNachtragen (ulBufIdent, m_sBuffer, /*true*/false);	// 08.07.99
	}

// Zugriffsmode der Datenquelle bzw. Objektklasse ermitteln
#if _TRiAS_VER < 0x0300
	// Datenbank schreibgeschützt (R/O-Modus)
	if (0 != DEX_GetROMode())
	{
		DEX_Error (RC_buffer, WC_DATASOURCE_ISRO);
		sfSForm = SFORM_TEMP;	// Speicherform: temporär
	}
#else
	if (DEX_GetROModeIdent (ulBufIdent))	// Objektklasse schreibgeschützt (R/O-Modus)
	{
		DEX_Error (RC_buffer, WC_CLASS_ISRO);
		sfSForm = SFORM_TEMP;	// Speicherform: temporär
	}
#endif // _TRiAS_VER < 0x0300

	else						// Datenquelle bzw. Objektklasse nicht schreibgeschützt (R/W-Modus)
		sfSForm = SFORM_PERM;	// Speicherform: permanent

	return true;

} // Vorarbeit


// -----------------------------------------------------------------------------------------------
// Puffer um lONr-Punktobjekt bilden
// ulObjIdent: Identifikator des zu puffernden Objektes
// ulBIdent:   vorgegebener BasisIdentifikator für Pufferung
bool BufferExtension :: PunktPuffer (long lONr, ulong ulObjIdent, KoOrd* plXK, KoOrd* plYK,
									 ulong ulBIdent, bool bFortAnz)
{
	_ASSERTE (plXK != NULL);
	_ASSERTE (plYK != NULL);

	if (bFortAnz)
	{
	double dSekW = asin(m_dPrec/(2.*m_dWidth));	// halber Sektorwinkel (asin liefert 0 ... Pi)

		_ASSERTE (dSekW > 0.);

	long lCnt = DtoL (Pi / dSekW);	// Anzahl der Stützpunkte des Kreispuffers

		try
		{
		WProgressIndicator2 PI (CLSID_ProgressIndicator);	// throws_com_error
		HRESULT hr = InitProgressIndicator (PI, ResID(IDS_PUFFER_CAPTION, pRF),
											ResID(IDS_STATUS_STAND, pRF), lCnt*m_iPuffAnzahl);

			if (FAILED(hr)) return false;
			hr = RegisterPI (PI);

#if _TRiAS_VER < 0x0300
			hr = GetPIProxy()->SetObjNr (lONr);
			if (FAILED(hr)) return false;
#endif
		}
		catch (_com_error&)
		{
			return false;
		}
	}

bool bRet = true;	// return-Wert dieser Routine

GeoFlaeche* pGO = NULL;		// Puffer
long lNeuONr;				// Objektnummer eines Puffers
ulong ulBufIdent;			// Identifikator eines Puffers
EFlaeche* pInsel = NULL;	// Zwischenspeicher von vorhergehenden Puffer für Insel des
							// aktuellen Puffers
SpForm sfSForm;				// Speicherform (permanent, temporär)

	for (int i = 1; i <= m_iPuffAnzahl; i++)
	{
		if (!Vorarbeit (i, ulBIdent, lONr, ulObjIdent, ulBufIdent, sfSForm))
			return false;

	// Puffer um Punkt
	EFlaeche* pPFl = PointBuffering (plXK[0], plYK[0], m_dWidth*i, m_dPrec, GetPIProxy());
				
		if (pPFl)
		{
			// wenn m_PBau == PBAU_RING, dann ab Bildung des 2. (permanenten!) Puffers den
			// vorhergehenden Puffer als Insel hinzufügen
			if (PBAU_RING == m_PBau && SFORM_PERM == sfSForm)
			{
				if (i > 1)	// 2. sowie weitere Puffer
				{
				int iKCnt = pPFl->KantenAnz();
						
					if (iKCnt > 1)	// wenigstens eine Innenkontur
						pPFl->SubKante (1, iKCnt-1);
					pPFl->AddKante (*pInsel, 1, -1);
				}

				DELETE_OBJ (pInsel);

				pInsel = new EFlaeche (&pPFl->KA(0), 1);   // aktuellen Puffer retten für Insel
				if (! pInsel)							   // des nächsten Puffers
				{
					DEX_Error (RC_buffer, EC_NOMEMORY);
					bRet = false;
					break;
				}
			}

			pGO = new GeoFlaeche (lONr, ulBufIdent, *pPFl);
			if (! pGO)
			{
				DEX_Error (RC_buffer, EC_NOMEMORY);
				bRet = false;
				break;
			}
#if _TRiAS_VER < 0x0300
			if (! GeometrieAnTRIAS (pGO, sfSForm, lNeuONr, m_pCT))
#else
		HPROJECT hPr = DEX_GetObjectsProject (ulBufIdent);

			if (! GeometrieAnTRIASEx (hPr, pGO, sfSForm, lNeuONr, m_pCT))
#endif // _TRiAS_VER < 0x0300
			{
				DEX_Error (RC_buffer, EC_NOBUFFER);
				bRet = false;
				break;
			}
		}
		else
		{
			bRet = false;
			break;
		}
				
		PufferVisualisieren (OT_PUNKT, ulObjIdent, ulBufIdent, i);
				
		_ASSERTE (m_lObjInd < m_lAnzPuff);

		m_plONr[m_lObjInd] = lNeuONr;	// neue Objektnummer des Puffers abspeichern
		m_lObjInd++;

		if (SFORM_PERM == sfSForm)		// für permanente Puffer Merkmale kopieren
		{
		string sUIText;
		ResString resText (ResID (IDS_UIFORMAT, pRF), 20);

			Format (sUIText, (char*)resText.Addr(), lONr, (long)m_dWidth*i);
			MerkmaleKopieren (lONr, lNeuONr, sUIText);

		long plOrigObjNr[1] = { lONr };

			ParentsUniqueIdents (lNeuONr, plOrigObjNr, 1);
		}

		DELETE_OBJ (pPFl);	// in PointBuffering() als EFlaeche dynamisch angelegter Puffer
		DELETE_OBJ (pGO);	// Puffer als GeoFlaeche
	} // for

	DELETE_OBJ (pInsel);
	DELETE_OBJ (pGO);		// falls for-Schleife mit break beendet wurde

	if (FAILED(UnRegisterPI())) return false;

	return bRet;

} // PunktPuffer


// --------------------------------------------------------------------------------------------
// Puffer um lONr-Linienobjekt bilden
// ulObjIdent: Identifikator des zu puffernden Objektes
// ulBIdent:   vorgegebener BasisIdentifikator für Pufferung
bool BufferExtension :: KantenPuffer (long lONr, ulong ulObjIdent, KoOrd* plXK, KoOrd* plYK,
									  long lCnt, ulong ulBIdent, bool bFortAnz)
{
	_ASSERTE (plXK != NULL);
	_ASSERTE (plYK != NULL);

	if (bFortAnz)
	{
		try
		{
		WProgressIndicator2 PI (CLSID_ProgressIndicator);	// throws_com_error
		HRESULT hr = InitProgressIndicator (PI, ResID (IDS_PUFFER_CAPTION, pRF),
										 ResID(IDS_STATUS_STAND, pRF), (lCnt-1)*m_iPuffAnzahl);
		
			if (FAILED(hr)) return false;
			hr = RegisterPI (PI);

#if _TRiAS_VER < 0x0300
			hr = GetPIProxy()->SetObjNr (lONr);
			if (FAILED(hr)) return false;
#endif // _TRiAS_VER < 0x0300
		}
		catch (_com_error&)
		{
			return false;
		}
	}

bool bRet = true;	// return-Wert dieser Routine

GeoFlaeche* pGO = NULL;		// Puffer
long lNeuONr;				// Objektnummer des Puffers
ulong ulBufIdent;			// Identifikator eines Puffers
EFlaeche* pInsel = NULL;	// Zwischenspeicher von vorhergehenden Puffer für Insel des
							// aktuellen Puffers
long lCO[4];				// Containerkoordinaten des zu puffernden Objektes
							// lCO[0] = xmin, lCO[1] = xmax, lCO[2] = ymin, lCO[3] = ymax
SpForm sfSForm;				// Speicherform (permanent, temporär)

	for (int i = 1; i <= m_iPuffAnzahl; i++)
	{
		if (!Vorarbeit (i, ulBIdent, lONr, ulObjIdent, ulBufIdent, sfSForm))
			return false;

	EFlaeche* pPFl = NULL;

		if (_bTyp)	// echter Puffer um Kante
			pPFl = LineBuffering (plXK, plYK, lCnt, m_dWidth*i, m_bsSide, m_cmMode, m_dPrec,
								  GetPIProxy());
		else		// Kreis (_bTyp == false) um Container-Mittelpunkt
		{
			DEX_GetObjContainer (lONr, lCO);

		KoOrd xm = (lCO[0] + lCO[1]) / 2;
		KoOrd ym = (lCO[2] + lCO[3]) / 2;

			pPFl = PointBuffering (xm, ym, m_dWidth*i, m_dPrec, GetPIProxy());
		}
				
		if (pPFl)
		{
			// wenn m_PBau == PBAU_RING, dann ab Bildung des 2. (echten oder permanenten!)
			// Puffers den vorhergehenden Puffer als Insel hinzufügen
			if (PBAU_RING == m_PBau &&
				(_bTyp || SFORM_PERM == sfSForm))	// echter Puffer oder permanent
			{
				if (i > 1)	// 2. sowie weitere Puffer
				{ // 14.07.98
				int iKCnt = pPFl->KantenAnz();
						
					if (iKCnt > 1)	// wenigstens eine Innenkontur
						pPFl->SubKante (1, iKCnt-1);
					pPFl->AddKante (*pInsel, 1, -1);
				}

				DELETE_OBJ (pInsel);

				pInsel = new EFlaeche (&pPFl->KA(0), 1);   // aktuellen Puffer retten für Insel
				if (! pInsel)							   // des nächsten Puffers
				{
					DEX_Error (RC_buffer, EC_NOMEMORY);
					bRet = false;
					break;
				}
			}

			pGO = new GeoFlaeche (lONr, ulBufIdent, *pPFl);
			if (! pGO)
			{
				DEX_Error (RC_buffer, EC_NOMEMORY);
				bRet = false;
				break;
			}
#if _TRiAS_VER < 0x0300
			if (! GeometrieAnTRIAS (pGO, sfSForm, lNeuONr, m_pCT))
#else
	HPROJECT hPr = DEX_GetObjectsProject (ulBufIdent);

			if (! GeometrieAnTRIASEx (hPr, pGO, sfSForm, lNeuONr, m_pCT))
#endif // _TRiAS_VER < 0x0300
			{
				DEX_Error (RC_buffer, EC_NOBUFFER);
				bRet = false;
				break;
			}
		}
		else
		{
			bRet = false;
			break;
		}
				
		PufferVisualisieren (OT_KANTE, ulObjIdent, ulBufIdent, i);
				
		_ASSERTE (m_lObjInd < m_lAnzPuff);

		m_plONr[m_lObjInd] = lNeuONr;	// neue Objektnummer des Puffers abspeichern
		m_lObjInd++;

		if (SFORM_PERM == sfSForm)		// für permanente Puffer Merkmale kopieren
		{
		string sUIText;
		ResString resText (ResID (IDS_UIFORMAT, pRF), 20);

			Format (sUIText, (char*)resText.Addr(), lONr, (long)m_dWidth*i);
			MerkmaleKopieren (lONr, lNeuONr, sUIText);

		long plOrigObjNr[1] = { lONr };

			ParentsUniqueIdents (lNeuONr, plOrigObjNr, 1);
		}

		DELETE_OBJ (pPFl);	// in Buffering() als EFlaeche dynamisch angelegter Puffer
		DELETE_OBJ (pGO);	// Puffer als GeoFlaeche
	} // for

	DELETE_OBJ (pInsel);
	DELETE_OBJ (pGO);		// falls for-Schleife mit break beendet wurde

	if (FAILED(UnRegisterPI())) return false;

	return bRet;

} // KantenPuffer


// --------------------------------------------------------------------------------------------
// Puffer um Außenkontur der lONr-Flächen (plXK, plYK, plCnt) bilden
// ulObjIdent: Identifikator des zu puffernden Objektes
// ulBIdent:   vorgegebener BasisIdentifikator für Pufferung
bool BufferExtension :: FlaechenPuffer (long lONr, ulong ulObjIdent, KoOrd* plXK, KoOrd* plYK,
										long* plCnt, ulong ulBIdent, bool bFortAnz)
{
	_ASSERTE (plXK != NULL);
	_ASSERTE (plYK != NULL);
	_ASSERTE (plCnt != NULL);

	if (bFortAnz)
	{
		try
		{
		WProgressIndicator2 PI (CLSID_ProgressIndicator);	// throws_com_error
		HRESULT hr = InitProgressIndicator (PI, ResID (IDS_PUFFER_CAPTION, pRF),
										  ResID(IDS_STATUS_STAND, pRF), (plCnt[0]-1)*m_iPuffAnzahl);
		
			if (FAILED(hr)) return false;
			hr = RegisterPI (PI);

#if _TRiAS_VER < 0x0300
			hr = GetPIProxy()->SetObjNr (lONr);
			if (FAILED(hr)) return false;
#endif // _TRiAS_VER < 0x0300
		}
		catch (_com_error&)
		{
			return false;
		}
	}

bool bRet = true;	// return-Wert dieser Routine

GeoFlaeche* pGO = NULL;		// Puffer
long lNeuONr;				// Objektnummer eines Puffers
ulong ulBufIdent;			// Identifikator eines Puffers
EFlaeche* pInsel = NULL;	// Zwischenspeicher von vorhergehenden Puffer für Insel des
							// aktuellen Puffers
long lCO[4];				// Containerkoordinaten des zu puffernden Objektes
SpForm sfSForm;				// Speicherform (permanent, temporär)
							
	for (int i = 1; i <= m_iPuffAnzahl; i++)
	{
		if (!Vorarbeit (i, ulBIdent, lONr, ulObjIdent, ulBufIdent, sfSForm))
			return false;

	EFlaeche* pPFl = NULL;

		if (_bTyp)	// echter Puffer um Fläche
			pPFl = AreaBuffering (plXK, plYK, plCnt[0], m_dWidth*i, m_bsSide, m_cmMode,
								  m_dPrec, GetPIProxy());
		else    	// Kreis (_bTyp == false) um Container-Mittelpunkt
		{
			DEX_GetObjContainer (lONr, lCO);

		KoOrd xm = (lCO[0] + lCO[1]) / 2;
		KoOrd ym = (lCO[2] + lCO[3]) / 2;

			pPFl = PointBuffering (xm, ym, m_dWidth*i, m_dPrec, GetPIProxy());
		}

		if (pPFl)
		{
			// wenn m_PBau == PBAU_RING, dann ab Bildung des 2. (echten oder permanenten!)
			// Puffers den vorhergehenden Puffer als Insel hinzufügen
			if (PBAU_RING == m_PBau && 
				(_bTyp || SFORM_PERM == sfSForm))	// echter Puffer oder permanent
			{
				if (1 == i && _bTyp)	// 1. Puffer (jedoch nicht bei Puffer um Punkt)
				{
					if (m_dWidth >= 0)	// positive Pufferbreite
						pPFl->AddKante (plXK, plYK, plCnt[0], -1);
					else				// negative Pufferbreite
					{
					EFlaeche EFl = EFlaeche (plXK, plYK, plCnt[0]);

						EFl.AddKante(*pPFl, 1, -1);	// 2. Parameter: Anzahl der hinzuzufügenden Innenkonturen
						*pPFl = EFl;
					}
				}

				if (i > 1)				// 2. sowie weitere Puffer
				{
				int iKCnt = pPFl->KantenAnz();
						
					if (iKCnt > 1)	// wenigstens eine Innenkontur
						pPFl->SubKante (1, iKCnt-1);	// mögliche Innenkonturen der Pufferfläche löschen

					if (m_dWidth >= 0)	// positive Pufferbreite
						pPFl->AddKante (*pInsel, 1, -1);
					else				// negative Pufferbreite
					{
						pInsel->AddKante (*pPFl, 1, -1);
						*pPFl = *pInsel;
					}
				}

				DELETE_OBJ (pInsel);

				// Teil des aktuellen Puffer für Insel des nächsten Puffers retten
				if (m_dWidth >= 0)	// positive Pufferbreite
					pInsel = new EFlaeche (&pPFl->KA(0), 1);
				else				// negative Pufferbreite
					pInsel = new EFlaeche (&pPFl->KA(1), 1);
				if (! pInsel)
				{
					DEX_Error (RC_buffer, EC_NOMEMORY);
					bRet = false;
					break;
				}
			}

			pGO = new GeoFlaeche (lONr, ulBufIdent, *pPFl);
			if (! pGO)
			{
				DEX_Error (RC_buffer, EC_NOMEMORY);
				bRet = false;
				break;
			}
#if _TRiAS_VER < 0x0300
			if (! GeometrieAnTRIAS (pGO, sfSForm, lNeuONr, m_pCT))
#else
		HPROJECT hPr = DEX_GetObjectsProject (ulBufIdent);

			if (! GeometrieAnTRIASEx (hPr, pGO, sfSForm, lNeuONr, m_pCT))
#endif // _TRiAS_VER < 0x0300
			{
				DEX_Error (RC_buffer, EC_NOBUFFER);
				bRet = false;
				break;
			}
		}
		else
		{
			bRet = false;
			break;
		}
				
		PufferVisualisieren (OT_FLAECHE, ulObjIdent, ulBufIdent, i);
			
		_ASSERTE (m_lObjInd < m_lAnzPuff);

		m_plONr[m_lObjInd] = lNeuONr;	// neue Objektnummer des Puffers abspeichern
		m_lObjInd++;

		if (SFORM_PERM == sfSForm)		// für permanente Puffer Merkmale kopieren
		{
		string sUIText;
		ResString resText (ResID (IDS_UIFORMAT, pRF), 20);

			Format (sUIText, (char*)resText.Addr(), lONr, (long)m_dWidth*i);
			MerkmaleKopieren (lONr, lNeuONr, sUIText);

		long plOrigObjNr[1] = { lONr };

			ParentsUniqueIdents (lNeuONr, plOrigObjNr, 1);
		}

		DELETE_OBJ (pPFl);	// in Buffering() als EFlaeche dynamisch angelegter Puffer
		DELETE_OBJ (pGO);	// Puffer als GeoFlaeche
	} // for

	DELETE_OBJ (pInsel);
	DELETE_OBJ (pGO);		// falls for-Schleife mit break beendet wurde

	if (FAILED(UnRegisterPI())) return false;

	return bRet;

} // FlaechenPuffer


// -----------------------------------------------------------------------------------------------
// Die zuletzt gebildeten Puffer aus DB, PBD und auf Bildschirm (nur Ausschnitt) löschen
void BufferExtension :: PufferLoeschen (void)
{
Rectangle Rec;	// Bereich für Neuzeichnen nach Löschen

	RangeToPaint (Rec);

	try
	{
	WProgressIndicator2 DPI (CLSID_ProgressIndicator);	// throws_com_error
	HRESULT hr = InitProgressIndicator (DPI, ResID(IDS_DELOBJECTS, pRF),
										ResID(IDS_DELETE_STATUS, pRF), m_lObjInd);
	
		if (FAILED(hr)) return;
		hr = RegisterPI (DPI);
		if (FAILED(hr)) return;
	}
	catch (_com_error&)
	{
		return;
	}

	_bPuffLoesch = true;	// Puffer werden über Menüpunkt "Puffer löschen" gelöscht

	for (int i = 0; i < m_lObjInd; i++)
	{
	HRESULT hr = GetPIProxy()->IsCanceled();	// Abbruch des Löschens?

		if (FAILED(hr) ||
			S_OK == hr ||	// Abbruch durch den Anwender
			FAILED(GetPIProxy()->IncrementPosition (NULL)))
			break;

	ulong ulBufIdent = DEX_GetObjIdentEx (m_plONr[i]);

		DEX_DeleteObjectEx (m_plONr[i]);	// erst PufferObjekt aus DB, dann
		IdentLoeschen (ulBufIdent);			// PufferIdentifikator aus PBD entfernen
	}

	if (FAILED(UnRegisterPI())) return;

	DEX_RePaintRectWait (Rec);	// Bereich nach löschen neu zeichnen
	_bPuffLoesch = false;
	_LoeMenAkt = false;			// Lösch-Menüpunkt inaktivieren

} // PufferLoeschen


// --------------------------------------------------------------------------------------------
// Puffer ausgehend von der Farbe des gepufferten Objektes visualisieren
// ulObjIdent: Identifikator des zu puffernden Objektes
// ulBufIdent: Identifikator eines Puffers
void BufferExtension :: PufferVisualisieren (ObjTyp iOT, ulong ulObjIdent, ulong ulBufIdent,
											 int i)
{
	_ASSERTE (ulObjIdent != 0);
	_ASSERTE (ulObjIdent != -1);
	_ASSERTE (ulBufIdent != 0);
	_ASSERTE ((ulong)-1 != ulBufIdent);
	_ASSERTE (i > 0);

HANDLEVISINFO HVI;

	INITSTRUCT (HVI, HANDLEVISINFO);
	HVI.m_lIdent = ulObjIdent;	// Identifikator
	HVI.m_pDesc = NULL;			// beschreibender Text
	HVI.m_pView = NULL;			// SichtName (aktuelle Sicht: NULL)
	
int iPrior;				// Zeichenpriorität und
int rot, gruen, blau;	//  Farben des zu puffernden Objektes

	switch (iOT)
	{
		case OT_PUNKT:
		{
		PVISINFO PVI;
		
			HVI.m_iVTyp = VTPunkt;		// VisInfoTyp
			HVI.m_pVI = &PVI.m_VI;		// generischer Pointer auf VisInfo
			DEX_GetIdentVisInfo (HVI);
			
			iPrior = PVI.m_VI.m_Priority;
			rot = GetRValue (PVI.m_VI.m_C);
			gruen = GetGValue (PVI.m_VI.m_C);
			blau = GetBValue (PVI.m_VI.m_C);
		}
			break;
		
		case OT_KANTE:
		{
		LVISINFO LVI;
		
			HVI.m_iVTyp = VTLinie;		// VisInfoTyp
			HVI.m_pVI = &LVI.m_VI;		// generischer Pointer auf VisInfo
			DEX_GetIdentVisInfo (HVI);
			
			iPrior = LVI.m_VI.m_Priority;
			rot = GetRValue (LVI.m_VI.m_C);
			gruen = GetGValue (LVI.m_VI.m_C);
			blau = GetBValue (LVI.m_VI.m_C);
		}
			break;
		
		case OT_FLAECHE:
		{
		FVISINFO FVI;
		
			HVI.m_iVTyp = VTFlaeche;	// VisInfoTyp
			HVI.m_pVI = &FVI.m_VI;		// generischer Pointer auf VisInfo
			DEX_GetIdentVisInfo (HVI);
			
			iPrior = FVI.m_VI.m_Priority;
			rot = GetRValue (FVI.m_FC);
			gruen = GetGValue (FVI.m_FC);
			blau = GetBValue (FVI.m_FC);
		}
			break;
		
		default:	// andere Objekte, z.B. Textobjekte werden nicht gepuffert
			_ASSERTE (false);
			return;
	}
		
FVISINFO FVIP;	// für Puffer

	memset (&FVIP, '\0', sizeof (FVISINFO));
#if _TRiAS_VER >= 0x0300
	FVIP.m_VI.dwSize = sizeof (tagFVISINFO);
	FVIP.m_VI.m_fLocatable = true;	// Puffer recherchierbar
	FVIP.m_VI.m_fVisible = true;	// Puffer sichtbar
#endif // _TRiAS_VER >= 0x0300
	HVI.m_lIdent = ulBufIdent;			// Identifikator
	HVI.m_iVTyp = VTFlaeche;			// und VisInfoTyp der Pufferfläche
	HVI.m_pVI = &FVIP.m_VI;				// generischer Pointer auf VisInfo
	
	rot = 100 + (rot + 30*i) % 156;		// Farben des i-ten Puffers
	gruen = 100 + (gruen + 100*i) % 156;
	blau = 100 + (blau + 60*i) % 156;
	
	FVIP.m_FC = RGB (rot, gruen, blau);
	FVIP.m_VI.m_Style = 1;				// Füllmode "gefüllt"
	FVIP.m_iWidth = 1;					// Konturbreite
	if (PBAU_RING == m_PBau)			// Zeichenpriorität bei ringförmigen Puffern ...
	{
		if (m_dWidth >= 0)						// ... und positiver Pufferbreite ...
		{
			if (1 != i || OT_FLAECHE == iOT)
				FVIP.m_VI.m_Priority = iPrior;	// = Zeichenpriorität des zu pufferndes Objekt
			else
				FVIP.m_VI.m_Priority = iPrior - 1;// für 1. (Ring-)Puffer um Punkt oder Linie
		}
		else									// ... und negativer Pufferbreite ...
			FVIP.m_VI.m_Priority = iPrior + 1;	// höhere Zeichenpriorität als das zu puffernde Objekt
	}
	else
	{
		if (iPrior > i)	// Zeichenpriorität bei vollständigen Pufferflächen ...
		{
			if (m_dWidth >= 0)						// ... und positiver Pufferbreite ...
				FVIP.m_VI.m_Priority = iPrior - i;	// ... jeweils dekrementieren
			else									// ... und negativer Pufferbreite ...
				FVIP.m_VI.m_Priority = iPrior + i;	// ... jeweils inkrementieren
		}
		else
		{
			DEX_Error (RC_PufferEinfaerben, WC_PRIORITY);	// Priorität kann nicht sinnvoll
															// eingestellt werden
			FVIP.m_VI.m_Priority = 1;	// niedrigste Zeichenpriorität
		}
	}
	FVIP.m_VI.m_C = RGB (0, 0, 0);	// Konturfarbe "schwarz"

	if (!_bTyp)	// Kreis
	{
		FVIP.m_VI.m_Style = 0;		// Füllmode "leer"
		FVIP.m_VI.m_Priority = 999;	// Zeichenpriorität
	}
	
	DEX_ModIdentVisInfo (HVI);

} // PufferVisualisieren


// --------------------------------------------------------------------------------------------
// Bereich für Neuzeichnen nach Pufferbildung bzw. nach Löschen der Puffer bestimmen; das
// Zeichnen selbst erfolgt getrennt von dieser Routine, da beim Löschen die Reihenfolge lautet:
// Bereich bestimmen, Puffer löschen, Bereich zeichnen
void BufferExtension :: RangeToPaint (Rectangle& Rec)
{
// Wenn die Pufferzonen nur um EIN Objekt gelegt werden, würde es für die Ermittlung des zu
// zeichnenden Rechtecks ausreichen, bei einer positiven Pufferbreite den letzten Puffer zu
// Grunde zu legen. Da aber gleichzeitig MEHRERE Objekte gepuffert werden können, gehe ich
// sicherheitshalber alle m_plONr-Objekte durch.
long lCO[4];			// Containerkoordinaten eines Objektes
						// lCO[0] = xmin, lCO[1] = xmax, lCO[2] = ymin, lCO[3] = ymax
KoOrd lXmin = MAXKOORD;	// Koordinaten des neu zu zeichnenden Bereiches
KoOrd lXmax = -1;
KoOrd lYmin = MAXKOORD;
KoOrd lYmax = -1;	

//	for (long i = 0; i < m_lAnzPuff; i++)	// alle m_plONr-Objekte abarbeiten
	for (long i = 0; i < m_lObjInd; i++)	// alle m_plONr-Objekte abarbeiten
    {
		if (m_plONr[i] > 0)	// kann durch "Abbrechen" nicht erfüllt sein
		{
    		DEX_GetObjContainer (m_plONr[i], lCO);
    		if (lCO[0] < lXmin) lXmin = lCO[0];
    		if (lCO[1] > lXmax) lXmax = lCO[1];
    		if (lCO[2] < lYmin) lYmin = lCO[2];
    		if (lCO[3] > lYmax) lYmax = lCO[3];
		}
	}

Point PLO, PRU;	// linker oberer bzw. rechter unterer Eckpunkt des zu löschenden Ausschnitts

	PLO = BSKoordinaten (lXmin, lYmax);
	PRU = BSKoordinaten (lXmax, lYmin);
	Rec.Left() = PLO.X() - iZug;	// zu bildendes Rechteck noch um iZug Pixel
	Rec.Top() = PLO.Y() + iZug;		// (in BuffKonst.hxx definiert) vergrößern
	Rec.Right() = PRU.X() + iZug;
	Rec.Bottom() = PRU.Y() - iZug;

} // RangeToPaint


// --------------------------------------------------------------------------------------------
HRESULT BufferExtension :: Pufferbildung_ONr (long lONr, double dWidth, int iPuffAnzahl,
										  PuffBau bPBau, SpForm sfSForm, bool bTyp,
										  ulong ulBIdent, bool bFortAnz, IEnumLONG** ppEnumOut)
{
	m_pW = MWind();				// MWind() liefert pWindow-Zeiger auf HauptFenster
	m_dWidth = dWidth;			// Pufferbreite
	m_bsSide = BUFF_BOTH;		// Puffer soll beidseitig gebildet werden
	m_cmMode = BUFF_KITE;		// konvexen Ecken als Drachenviereck
	m_dPrec = -1;				// Kantenlänge (in Meter) des n-Ecks an konvexen Ecken
	m_iPuffAnzahl = iPuffAnzahl;// Anzahl der zu bilden Puffer
	_bTyp = bTyp;      			// Puffertyp (echter Puffer, Kreis)
	m_PBau = bPBau;				// Puffer ringförmig / als volle Fläche
	m_lAnzPuff = m_iPuffAnzahl;
	DELETE_VEC (m_plONr);			// Feld der Objektnummern der Puffer löschen
	m_plONr = new long[m_lAnzPuff];	// und für die neuen Objektnummern erneut anlegen
	if (! m_plONr)
	{
		DEX_Error (RC_buffer, EC_NOMEMORY);
		return E_OUTOFMEMORY;
	}
	m_lObjInd = 0;   // Laufindex für m_plONr

	if (!PufferBilden (lONr, ulBIdent, bFortAnz))
		return E_FAIL;

	try
	{
	WEnumLONG wOutput (CLSID_EnumObjectsByNumber);

		_ASSERTE (wOutput.IsValid());

		// Übertragen der Objektnummern der erzeugten Puffer aus m_plONr in wOutput
		for (int i = 0; i < iPuffAnzahl; i++)
			((IEnum<LONG>*)(IEnumLONG*)wOutput)->AddItem (m_plONr[i]);

		*ppEnumOut = wOutput.detach();
	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

	return S_OK;

} // Pufferbildung_ONr


// --------------------------------------------------------------------------------------------
HRESULT BufferExtension :: Pufferbildung_Geom (IObjektGeometrie* pIOG, double dWidth,
								   int iPuffAnzahl, PuffBau bPBau, SpForm sfSForm, bool bTyp,
								   ulong ulBIdent, bool bFortAnz, IEnumLONG** ppEnumOut)
{
	_ASSERTE (pIOG != NULL);

long lONr = -1;

	pIOG->GetONr (&lONr);
	
	if (0 != lONr && -1 != lONr)
		return Pufferbildung_ONr (lONr, dWidth, iPuffAnzahl, bPBau, sfSForm, bTyp, ulBIdent,
								  bFortAnz, ppEnumOut);

// ohne Objektnummer
	m_pW = MWind();				// MWind() liefert pWindow-Zeiger auf HauptFenster
	m_dWidth = dWidth;			// Pufferbreite
	m_bsSide = BUFF_BOTH;		// Puffer soll beidseitig gebildet werden
	m_cmMode = BUFF_KITE;		// konvexen Ecken als Drachenviereck
	m_dPrec = -1;				// Kantenlänge (in Meter) des n-Ecks an konvexen Ecken
	m_iPuffAnzahl = iPuffAnzahl;// Anzahl der zu bilden Puffer
	_bTyp = bTyp;      			// Puffertyp (echter Puffer, Kreis)
	m_PBau = bPBau;				// Puffer ringförmig / als volle Fläche
	m_lAnzPuff = m_iPuffAnzahl;
	DELETE_VEC (m_plONr);			// Feld der Objektnummern der Puffer löschen
	m_plONr = new long[m_lAnzPuff];	// und für die neuen Objektnummern erneut anlegen
	if (! m_plONr)
	{
		DEX_Error (RC_buffer, EC_NOMEMORY);
		return E_OUTOFMEMORY;
	}
	m_lObjInd = 0;   // Laufindex für m_plONr

	// !!!!!!!! Baustelle: das Wesentliche fehlt hier noch !!!!!!!!!!!!!!!!!
	return E_NOTIMPL;

} // Pufferbildung_Geom


// --------------------------------------------------------------------------------------------
// Bezug zur Erweiterung "GeometrieBereinigung" herstellen, wenn noch m_bGeoRein == false
HRESULT BufferExtension :: GeoReinInterface (void)
{
    if (m_bGeoRein) return S_FALSE;

HRESULT hrRet;

    if (m_pXtnSite)
    	hrRet = m_pXtnSite->GetXtension (CLSID_GeometrieBereinigung, IID_IExtendGeoRein,
    									(LPVOID*)&m_wGeoRein);
    else hrRet = E_UNEXPECTED;

    if (FAILED (hrRet) ||	// Fehler, z.B. GeoRein.ext nicht verfügbar
    	! m_pXtnSite)
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
// Initialisierung des ProgressIndicators2
HRESULT BufferExtension :: InitProgressIndicator (IProgressIndicator2* pPI, ResID uiTitel,
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
							PIFLAGS_FILENAME |
#if _TRiAS_VER < 0x0300
							PIFLAGS_RESULT |			//	der Objektnummer
#endif // _TRiAS_VER < 0x0300
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
HRESULT BufferExtension :: RegisterPI (IProgressIndicator2* pPI)
{
	try
	{
		_ASSERTE (m_dwCookie == 0);
		
	WConnectionPointContainer CPC (GetUnknown());		// throws_com_error
	WConnectionPoint CP;

		THROW_FAILED_HRESULT(CPC->FindConnectionPoint(IID_IProgressIndicator2, CP.ppi()));
		THROW_FAILED_HRESULT(CP->Advise(pPI, &m_dwCookie));

	}
	catch (_com_error& e) 
	{
		return _COM_ERROR (e);
	}

	return S_OK;
} // RegisterPI


// --------------------------------------------------------------------------------------------
// Abmeldung des ProgressIndicators2
HRESULT BufferExtension :: UnRegisterPI (void)
{
	if (0 == m_dwCookie) return S_FALSE;	// es wurde kein Advise() ausgeführt 

	try
	{
	WConnectionPointContainer CPC (GetUnknown());		// throws_com_error
	WConnectionPoint CP;

		THROW_FAILED_HRESULT(CPC->FindConnectionPoint(IID_IProgressIndicator2, CP.ppi()));
		THROW_FAILED_HRESULT(CP->Unadvise(m_dwCookie));
		m_dwCookie = 0L;

	}
	catch (_com_error& e)
	{
		return _COM_ERROR (e);
	}

	return S_OK;
} // UnRegisterPI


// --------------------------------------------------------------------------------------------
// Reaktion auf Fehlercode iWC
int ErrHandler (int iWC, int iRoutine, ...)
{
va_list vaArgs;		// Liste der unbenannten Argumente

	va_start (vaArgs, iRoutine);

void* pvData = va_arg (vaArgs, void*);	// Makro, um die unbenannten Argumente herauszuholen

	va_end (vaArgs);

ResString resTitel (ResID (IDS_LONGCLASSNAME, pRF), 50);
				
	MessageBox (__hWndM, (char*)pvData, resTitel.Addr(), MB_ICONEXCLAMATION | MB_OK);

	return iWC;

} // ErrHandler
