// Anzeige Kompakt-Informationen
// File: KOMPIAS.HXX

#if !defined(_KOMPIAS_HXX)
#define _KOMPIAS_HXX


#include <itriasap.h>
#include <triastlb.h>


class CObjTree;

class CKompiasExtension : public CTriasExtension {
private:

//------Interface----------------------------
	IObjektGeometrie *m_pIOG;
	IExtendAbstand2 *m_pAbst;
	IExtendTopRel2 *m_pTop;
	IExtendBuffer *m_pPuf;
	IExtendObjOper * m_pObjOp;

	IObjectProperty *m_pObjPropL;
	IObjectProperty *m_pObjPropF;
	IObjectProperty *m_pObjRechts;
	IObjectProperty *m_pObjHoch;

//-----------Basic-----------------------------
	IExtendBScript *m_pScript;
//-------------------------------------------
	_DDocument *m_pDoc;
	
//-------------------------------------------

	class CStatus *m_pStatus;

	CoordTransX *m_pCTF;

	class TR_OBJTree *m_pTRGew;	// TRiAS.Gew.Kataster(ONr)
	class KPTree *m_pGew;		//Gew.Kataster ( GewNr)
	class KPTree *m_pGewKomp;		//Gew.Kataster ( GewNr)
	class KPTree *m_pGewPart;		//Gew.Kataster ( GewNr)
	class KPTree *m_pGewAlle;		//Gew.Kataster ( GewNr)
	class KPTree *m_pGewHyd;		//Gew.Kataster ( Hydraulik)

//---------------------------------------------------

	class KompaktHeader *m_pKH;


	short m_isWork;			// AbarbeitungsStatus

	short m_isShow;			// GewUebersicht aufgebaut
	short m_isInit;			// GewKataster initialisiert
	short m_isActive;		// Kompakt zuschalten oder passivieren
	short m_isCreate;		// GewaesserGeometrie neu anlegen
	short m_isBauw;			// BauwGeometrie anlegen

	short m_isNewOR;			//neues ORFenster anlegen

	short m_iFunction;		// KompaktFunktion
	char * m_pLocDir;		// Projekt
	char * m_pLocProt;		// Projekt-Protokoll
	char * m_pDataPath;		// DatenPfad Gewässerkataster

	short m_iAbfluss;		// Hydraulik vorhanden ja/nein
	short m_iProfile;		// Profile vorhanden ja/nein

	short m_iLeiSchritt;	// Schrittweite bei Leistungsdarstellung
	short m_iDefSchritt;	// Definierte Schrittweite
	short m_iDefPuffer;		// Definierte Pufferzone

	DWORD m_dKPP;			// Parameter Registrierung - Protokoll
	DWORD m_dKPA;			// Parameter Bauwerksabgleich

	FILE *fascii;

	HMENU m_hMenu;
	HWND m_hWnd;
	HWND m_hWndPart;

	CKompaktDLL *m_hLib;		// KompaktDLL
	UINT m_wMsg1;
	UINT m_wMsg2;
	UINT m_wMsg3;
	UINT m_wMsg4;
	UINT m_wMsg5;

	long m_lONr;
	long m_lONrGew;
	long m_lONrBauw;
	long m_lONrDel;

// Vis-Objekte
	long m_lONrStart;
	long m_lONrEnde;
	long m_lONrVis;


	TR_OBJTree *m_pModObj;	// Sammlung modifizierter Objekte
	TS_OBJTree *m_pGewText;	// Sammlung Texte v. kilometr.Punkten

	short m_iCount;
	short m_pStop;	// m_pStatus gestoppt 


// -----Notificationen------------------

	bool m_bMerkmal;	// RegisterNotification (DEX_MODIFYMERKMAL)

	bool m_bChange;	// RegisterNotification (DEX_OBJECTCHANGED)



#if _MSC_VER >= 1100
	HPROJECT m_hPr;
#endif

//	Notvariante
//	KK990803
	DWORD m_pUIOwner;		// AddRef /Release !


	
protected:
// überladene virtuelle Funktion(en)

	STDMETHOD_(BOOL, InitExtension) (THIS_ short iMode);
	STDMETHOD_(BOOL, UnLoadExtension) (THIS);
	STDMETHOD_(BOOL, MenuInit) (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (THIS_ UINT uiMenuID, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (THIS_ WPARAM wParam, LPARAM lParam);
	STDMETHOD_(LRESULT, WindowsNotification) (THIS_ UINT wMsg, WPARAM wParam, LPARAM lParam);

public:
// Konstruktor / Destruktor
		CKompiasExtension (void);
		~CKompiasExtension (void);

// Memberfunktionen
	short &isWork (void) { return m_isWork; };			// Kompaktdaten vorhanden
	short &isActive ( void ) { return m_isActive; };	// Kompakt aktiv

// KK010829
	long * ViewHasIdent ( long * pObj);

// KK010731
	void ResetGewInfo(void) { DELETE_OBJ(m_pGewAlle); };

	HRESULT CreateKompDataToolBar(void);
	HRESULT RemoveKompDataToolBar(void);
	long KompaktObjekt (void) { return m_lONr; };
	char *KompaktProtokollPointer ( void) { return m_pLocProt; };
	CKompaktDLL *KompaktDLL (void) { return m_hLib; };
#if _MSC_VER >= 1100
	BOOL Datenquelle(void);
	bool DatenQuelleWechseln(void);
#endif
//KOMPMEM
	void CreateGraphicInformation ( void );
	bool AbgleichFeature (long);
	bool KompaktKatasterDefiniert ( char *);
	bool KompaktKatasterDefiniert_ONr ( long);
	void RestoreBauwAnlegen(bool);

	KPTree * HoleLeistungenVonKompakt ( short);
	KPTree * HoleBauwerkeVonKompakt ( short);
	void LoeschenEinzelBauwerke(TR_OBJTree *);
	KPTree * HoleGewaesserVonKompakt ( short);
	KPTree * HolePunktVonKompakt ( LPARAM);
	bool HolePunkteVonKompakt ( KPTree *, LPARAM);
	void HoleGewaesserVonTRiAS ( void);
	void ZeigeObjektVonTRiAS(HWND,KOORDINATEN *);

	void HoleBauwerkeVonTRiAS ( void);
	short BauwerkeTyp ( long);
	KPTree * Gewaesser ( void) { return m_pGew; };
	TR_OBJTree * Bauwerke ( void) { return m_pTRGew; };
	TR_OBJTree *SammeleAlleBauwerke(TR_OCLTree *);
	void HoleKoordinatenVonTRiAS(HWND ,KOORDINATEN *);
	void SetzeKoordinate(KOORDINATEN *);
	void SetzeStation(KOORDINATEN *);
	long SetzeKompaktPunkt (KOORDINATEN *, long );

	void LadeEinzelGewaesser ( HWND, KOORDINATEN *,short, TR_OCLTree *);
	bool DefiniereBauwerksParameter(TR_OBJTree *);
	void LadeObjektKlasse (short iTyp, TR_OCLTree *);
	bool LadeGewaesserNummer ( ulong, ulong, TR_OCLTree *);
	KPTree *SpeichernGewaesserNummer ( ulong, ulong, TR_OCLTree *);
	void AbgleichGewaesserDaten ( ulong, ulong, TR_OCLTree *);

	KPTree *SpeichernGewaesserNummer_Flaeche ( long, ulong, ulong, TR_OCLTree *, TR_OBJTree *);
	KPTree *HoleGewaesserNummer_Flaeche ( long, ulong, ulong, KPTree *);
	bool ContainerVergleich ( long , long []);
	bool GewaesserRelation ( long, long, Relat *);
	TR_OBJTree * GewaesserVerschnitt ( long, long);
	bool SetPBDClonedMCode(ulong,long);

#if _MSC_VER >= 1100
	void ModifyObjFeature(long , long , char *);
// KK010810
	HPROJECT HandleKompaktProject(void);
#endif

	ulong GetClonedCode(long);
	void SetObjektCloned ( long, ulong);
	long AnzahlTRiASGewaesser( TR_OCLTree *);
	void SetOriginalObjekt ( TR_OBJTree *, KPTree *, long);
	bool AktualisiereGewKataster ( KPTree *, TR_OCLTree *);
	bool OriginalObjekt ( long, TR_OBJTree *, long);
	bool CheckOriginalObjekt ( long lONr );
	bool ClonedObject ( long, ulong );
	void MischeGewKataster ( KPTree *,KPTree *);
	void BildeGewKataster ( KPTree *,KPTree *);
	long KompaktGewaesser ( LPARAM);
	long KompaktUeberschwemmung ( LPARAM);
	char *AktualisiereGewaesserNummer ( long, ulong);
	char *HoleGewaesserNummer ( long, ulong);
	char *HoleHydraulikHoehe ( long, ulong);
	char *HoleGewaesserName ( long, ulong, char *,short);
	char *HoleTRiASGewaesserNummer ( long, ulong);
	char *TRiASGewaesserName ( long,ulong);
	void SetObjektWert ( long,ulong,char *);
	void GetStandardMCode ( long, ulong, char *);
	void RestoreGewNr (long, char *);
	bool SetzeKompaktName (long, short);
	bool Einmuendung (long);
	void LadeGewaesserKataster ( char *,char *, KPTree *);
	void CreateORWindow ( short, short,short,long*,const char *,short,short,short);
	void CreateStandardInformation(void);
	void DeleteStandardInformation(void);
	void ErfasseTempDaten(void);
	bool ObjektIstGewaesser( long );
	bool ObjektIstUeberschwemmung( long );
	bool DefineGewaesserObjekt(long);
	TR_OCLTree *LadeBauwerkeKlassen(void);
	TR_OCLTree *LadeBauwerkeTeilKlassen(char *);
	TR_OBJTree *FindeBauwerkeTeilKlassen(char *, long);
	bool AbgleichGewaesserNummer(void);
	bool AbgleichHydraulikFlaechen (void);
	bool LadeHydraulikHoehe ( long,TR_OCLTree *);
	bool isBauwerk(void);
	bool isGewaesser(void);

// KK010815
	long GesamtGewaesserCount ( TR_OCLTree *);


//KOMPGEO
	void SetNewPBDKlasse(long,short);
	void SetNewPBDMCode ( long,long , ResString );
	bool SpeichereLeistungInTrias ( KPTree *);
	bool SpeichereBauwerkeInTrias ( KPTree *);
	bool SpeicherePunktInTrias ( KPTree *);
	bool PruefeTriasObjekt ( GEWSTRUKTUR *);
	bool LadeTriasObjekt ( GEWSTRUKTUR *);
	bool SpeichereLeistung ( GEWSTRUKTUR *, KP_LATree *);
	bool SpeichereLeistungsCodes ( long, long, long, char *);
// KK010226
	bool SpeichereAnomalie ( long, double, double);
	ulong GetSWAnomalieCode (long );
//	bool SchrittweitenAnalyse( long*, long*, long, long);
	bool SchrittweitenAnalyse( short, long*, long*, long, long);

	bool SpeicherePunkt ( GEWSTRUKTUR *, KP_LATree *);
	bool BildePunkt ( GEWSTRUKTUR *p);
	bool BildeLeistungsArt ( GEWSTRUKTUR *, long, long);
	bool BildeKompaktObjekt ( GEWSTRUKTUR *, long, long);
	bool StuetzPunktAusAbstand ( GEWSTRUKTUR * );
	bool LadeKompaktObjekt ( GEWSTRUKTUR *, IObjektGeometrie *);
	bool LadeEndKompaktObjekt ( GEWSTRUKTUR *, IObjektGeometrie *);
	ulong BildeObjektKlasse ( short, short);
	ulong BildeLeistungsKlasse ( short, short, char *);
	ulong FindePBDUnterGruppe( short, short, char *,short *);
	void SpeichereBauwMerkmal(long);
	void SetPBDIdent ( long, short, short);
	bool LadeMerkmalsWert ( GEWSTRUKTUR *);
	short AnzahlDerLeistungen ( KPTree *);
	void BauwerkeAttribute ( GEWSTRUKTUR *p);
	void ModifiziereMerkmal ( long, ulong, char *);
	void LoescheMerkmal ( long, ulong);
	char * HoleMerkmalsWert(long,ulong);
	bool StartWertKorrekt(long,long,long);
//KOMPIFCE
	bool LadeObjektGeometrie ( long lONr );
	bool CreateInterfaceOG ( IObjektGeometrie ** ppIOG, long lONr );
	bool LadeAbstandsErweiterung ( void );
	bool LadeObjektEigenschaft ( void );
	bool LadeTopRel ( void );
	bool LadePuffer( void );
	bool LadeObjOp ( void );
	bool LadeBasicDocument(void);
	bool LadeBasicScript(void);
	void ReleaseInterface ( void );
// Notifikationen
	void MyRegisterNotification ( UINT, bool &);
	void MyUnRegisterNotification ( UINT, bool &);
	void ExtModifyRegisterNotification ( void);
	void ExtModifyUnRegisterNotification ( void);
	void ExtObjectChangedRegisterNotification (void);
	void ExtObjectChangedUnRegisterNotification (void);
//KPWINOT
	bool HydraulikPunkt ( LPARAM p);
	bool HydraulikPunkte( LPARAM );
	bool MischeHydraulik ( void);
	bool BildeUeberschwemmungsGebiet( KPTree *);
	void ZeigeUeberschwemmungsPunkt ( void );
	bool TopologieTest (long, TR_OCLTree *,TR_OBJTree *);
	void HydroMerge ( TR_OBJTree *,TR_OBJTree *);
	bool PunktInFlaeche ( long, long);
	bool EchterInnenPunkt ( long, TR_OBJTree *, TR_OBJTree *);
//----Ueberschwemmung
	long * EchteRandFlaeche ( double, long);
	bool HydraulikFlaeche( long ,double);
	bool EchteNachbarFlaeche (long,long,long *);
	bool NachbarFlaechen ( long , TR_OBJTree *);

	double HoleHoehe ( long );
	bool DoppelnObjekt ( long *, long, char *);
	void ShowObjsContainer(long *);
	bool FlaechenVereinigung ( long, long *);
	void LoeschenUeberschwemmungsGebiet ( long, char *);
	void AktualisiereHoehenWert ( long );
//KOMPMENU
	void TRiASKompaktLoader(void);

#if _MSC_VER >= 1100
	bool GetKompaktInformation (HPROJECT hPr);
#endif

	KPTree *GesamtGewaesser(void);
	void AktualisiereGesamtGewaesser( long, char *,long);
	bool EinzelGewaesser( KPTree *);
	long HoleEinzelGewaesser ( long, char *);
	bool AbgleichGewKataster(KPTree *, KPTree *);
	short KompaktMenu ( short );		//Fenster Kompakt-Funktionen
	bool LeistungsBearbeitung ( short);
	bool BauwerkeBearbeitung ( short);
	bool KompaktFunktion ( short,HWND);
	void GewaesserVergleich ( short );
	void GewaesserAbgleich ( void );
	bool KatasterLaden(bool iFlag = true);
	bool KatasterAnlegen (void);
	bool KompaktKomponentenTest(char *);
	bool Kompakt1Existenz(char *);
	char *HoleKompaktDatenPfad(void);
	bool SetzeKompaktDatenPfad(char *);
	char *FSTest(void);
//----------------------------------------------------------------
///////////////////////////////////////////////////////////////////
// COBJKOMP
	long GewaesserInWindowZuKataster ( HWND);
	long GewaesserInWindow ( HWND);
	long ModGewaesserInWindow ( HWND);
	void KorrigiereGesamtGewaesser( bool,long, char *,long);
	void KorrigiereEinzelGewaesser( bool,long, char *,long);
	void TopologieRecherche ( long);
	CTop_ObjTree *BildeObjektKlasse ( TR_OCLTree *);
	TR_OBJTree *LadeObjektTeilKlasse (short, long, TR_OCLTree *);
	TR_OBJTree *ObjektKontrolle ( long, TR_OBJTree *, TR_OBJTree *);
	void FlaechenAnalyse ( long);
	void Loeschen ( long *);
	void CTreeLoeschen ( TR_OBJTree *);
	void CTreeLaden ( long *);
	void CTextLoeschen(void);
//	void DeleteAllTextObjects(void);
	void CTextLaden (long, long, long);
	void LoeschenKompaktKlassen ( void);
	bool SucheDifferenzGewaesser( KPTree *pGew);
	// KK010726
	bool GewaesserDiffLaenge(long lDiff, long lMax);
	void DiffLaengenText(char *, short);

	void LoescheGewaesser( KPTree *pGew, char *pGewNr);
	void SichereGewaesser( KPTree *pGew, char *pGewNr);
	long ObjektPuffer ( long);
///////////////////////////////////////////////////////////////////
// TRGEOM
	void GewaesserKuerzen(long,long);
	void GewaesserVerlaengern(long,long);
	bool TesteTRiASObjekt(long);
	bool HoleTRiASObjekt ( GEWSTRUKTUR *);
	bool BildeNeueLaenge ( GEWSTRUKTUR *);
	bool ErweitereLaenge ( GEWSTRUKTUR *);
	bool ModifiziereTRiASObjekt ( IObjektGeometrie *);
	DoublePair KorrigiereLaenge ( long ,long ,long ,long );
//////////////////////////////////////////////////////////////////
// KPBAUW
	long KompaktBauwerk ( LPARAM);
	bool BestimmeBauwerk(HWND, bool);
	bool ObjektIstBauwerk( long );
	bool DefineEreignisObjekt ( long );
	bool ObjektWirdBauwerk( long );
	void StoreIdentFeature(long);
// KK010808
	bool SetInBauwerksKataster ( long lOBauw,long lOGew);

// KPAREA
	void HoleFlaechenVonTRiAS ( LPSTR, short, KPBTree *);
	char *HoleKurzText(long);
	bool LinienTest ( long, LPSTR, KPBTree *,short, TR_OCLTree *);
	bool KlassenTyp (short, long);
	bool TopologieLinieInFlaeche ( long,long, Relat *);
	bool LinieInFlaeche ( long,long, long , short, LPSTR, KPBTree *);
	bool LinieInAusFlaeche ( long,long, short,LPSTR, KPBTree *);
	double FlaechenGroesse ( long);
	long LinienLaenge( long);
	long LinienStartPunkt(long,long);
	long ObjektStartPunkt(long,ulong);
// KPSYMB
	bool ObjektBearbeitung ( bool , HWND);
	bool GewaesserParameter ( long );
	bool GewaesserUmkehr ( long );
	long BildeTextObjekt(long,long,long *,long *);
	bool SpeichereText (long, long);
	bool LinienVisualisierung (long);
	bool GetGeoObjectFromONr ( long, _DGeoObject **);
	bool isCloned(long);
	long StartWertClone(long,long);
	long EndeWertClone(long, long);
// KPBIGAR
	void GrossFlaechenAnalyse(long, HWND);
	TR_IDMTree *TRiASKlassen(long, long*,HWND);
	long ObjektKompaktAnalyse(long,HWND);
	bool FlaechenBlinkeln ( long, long *,char *);
//----------------------------------------------------------------
	KompaktHeader *KPHeader(void) { return m_pKH;};
	void DeleteKPHeader(void) { m_pKH = NULL; };

#if _MSC_VER >= 1100
	HPROJECT AktuellesProjekt (void) {return m_hPr;};
#endif


//----------------------------------------------------------------
//-ToolBar
	HRESULT DefineEreignis ( void);
	HRESULT DefineWasser(void);
	HRESULT DefineObjektEigenschaft(void);
	HRESULT CreateKompDataToolbar(void);
	HRESULT RemoveKompDataToolbar(void);
//----------------------------------------------------------------
};

#endif 	// _KOMPIAS_HXX
