// Erweiterungsklasse für "ObjektOperationen mit GeoObjekten"
// File: ObjOper.hxx
// W. Mörtl

#ifndef _OBJOPER_HXX
#define _OBJOPER_HXX


#include <TRiASHelper.h>	// tagPIFLAGS in progstat.h, IProgressIndicator2
#include "progstat.h"		// BaseProgressStatus in ProgressProxy.h
#include "ProgressProxy.h"	// CProxyIProgressIndicator2

#include "SmartInterfaces.h"

///////////////////////////////////////////////////////////////////////////////
// LizensierungsKlasse
#if defined(_DEBUG)
extern "C" bool g_fGlobalLic;
#else
#define g_fGlobalLic false
#endif // defined(_DEBUG)

class CMyLicense
{
protected:
	static BOOL VerifyLicenseKey(BSTR bstr)
	{
	CComBSTR bstrKey;

		USES_CONVERSION;
		if ((GetLicenseKey (0, &bstrKey) && !wcscmp (bstrKey, bstr)) ||
			 ::SetLicensed (OLE2A(bstr)))
		{
			return TRUE;
		}
		return FALSE;
	}

	static BOOL GetLicenseKey (DWORD, BSTR *pBstr) 
	{
	CComBSTR bstrKey (_MAX_PATH, (LPCOLESTR)NULL);

		if (!::GetLicenseKey (bstrKey.m_str, _MAX_PATH))
			return FALSE;

		*pBstr = bstrKey.Detach(); 
		return TRUE;
	}

	static BOOL IsLicenseValid() { return g_fGlobalLic || ::GetLicensed(); }
};


typedef map <string, string, CStringComp> CMerkmalsListe;	// Kurztext, Merkmalsinhalt
typedef CMerkmalsListe::iterator CMerkmalsListe_it;


class ObjektOpExtension : public IExtendObjOper,
						  public CTriasExtension,
#if defined(__ATL_20_USED__)
						  public CProxyIProgressIndicator2<ObjektOpExtension>,
						  public IConnectionPointContainerImpl<ObjektOpExtension>,
#else
						  public CComConnectionPointContainerImpl,
#endif // defined(__ATL_20_USED__)
						  public CComCoClass<ObjektOpExtension, &CLSID_GeometrieOperationen>
{
private:
#if defined(__ATL_20_USED__)
	typedef CProxyIProgressIndicator2<ObjektOpExtension> CPIProxy;
	CPIProxy *GetPIProxy() { return this; }
#else
	CProxyIProgressIndicator2 m_PPI;
	typedef CProxyIProgressIndicator2 CPIProxy;
	CPIProxy *GetPIProxy() { return &m_PPI; }
#endif // !defined(__ATL_20_USED__)
	DWORD m_dwCookie;	// Nummer des ConnectionPoint

	ERRHANDLER m_oldEH;	// alte Fehlerbehandlungs-Methode

	pWindow m_pW;		// Zeiger auf ein Fenster (ObjektRechercheFenster oder HauptFenster)
	HWND m_hWnd;		// Nummer des Hauptfensters
	short m_iMode;		// Parameter von InitExtension()

	WExtendGeoRein m_wGeoRein;	// Interface für Ankopplung von GeoRein.ext	
	bool m_bGeoRein;			// Ankopplung von GeoRein.ext ist erfolgt (true)

	ObjOp m_OpMode;		// ausgewählte Operation
	EObjekt* _pBO;		// aktiviertes (blinkendes), d.h. Bezugsobjekt
	short _iOT;			// Objekttyp,
	long _lONrAO;   	//  Objektnummer,
	ulong _ulIdent;		//  Identifikator
	long _lSPA;			//  bzw. Stützpunktanzahl des aktivierten (blinkendes) Objektes

	bool m_bUnion;		// Vereinigung durchgeführt (true)
	EFlaeche* _pVFl;	// Vereinigungsfläche
	ClipListe _CL1;		// Liste der neuen Objekte nach einer Operation
	ClipListe _CL2;		// Liste für Objekte, die als Zwischenergebnis entstehen
	ulong _ulLageAusw; 	// Bitmuster für Auswahl bei Schnittoperationen; es können beliebig
						// kombiniert werde
						//   LINN:  die innerhalb (Standard),
						//   LAUSS: außerhalb oder 
						//   LKONT: auf der Kontur der schneidenden Fläche liegenden Teilobjekte
	SpForm _sfSForm;	// Speicherform
	bool _bNeuZeigen;   // Recherchefenster mit neuen Objekte anzeigen (true)
	bool _bOrigZeigen;  // Recherchefenster mit Orginalobjekte anzeigen (true)
	long m_lNumber[4];	// m_lNumber[0]: Anzahl der selektierten (markierten) Objekte
						// (ausschließlich dem aktivierten, d.h. blinkenden Objekt)
						// m_lNumber[1]: Anzahl der selektierten Flächen (einschl. der aktivierten Fläche)
						// m_lNumber[2]: Anzahl der selektierten Kanten (einschl. der aktivierten Kante)
						// m_lNumber[3]: Anzahl der selektierten Punkte (einschl. des aktivierten Punktes)

	typedef vector<long> NewObjsVec;
	NewObjsVec m_veNewObjs;	// neu gebildeten Objekte

	long* m_plNeuObjNr;	// Feld der Objektnummern der neu gebildeten Objekte
	long m_lNeuInd;		// Laufindex von m_plNeuObjNr
	long* m_plOrigObjNr;// Feld der Objektnummern der originalen Objekte, aus denen die neuen
						// Objekte gebildet wurden
	long m_lOrigInd;	// Laufindex von m_plOrigObjNr
	long _lAnzOrigObj;	// Anzahl der Objekte, mit denen entspr. Operation durchgeführt werden soll
	long _lAnzNeuObj;	// Anzahl der Objekte, die neu in die Datenbank aufgenommen werden

	bool m_bCopyFeat;	// Merkmale der Originalobjekte sollen übernommen werden (true)

	bool _bMenLoeNeu;	// Menüpunkt für Löschen der neu erzeugten Objekte aktiviert (true)
	bool _bMenLoeOrig;	// Menüpunkt für Löschen der ursprünglichen Objekte aktiviert (true)
	bool _bObjLoesch;	// Objekte werden über Menüpunkt und nicht über Werkzeug "Schere"
						// gelöscht (true)

	CMerkmalsListe m_FeatList;	// Baum für alle Merkmale der an einer Objektoperation
								// beteiligten Objekte

	Dimension m_dimDots;	// DotsPerMM für den Bildschirm

	// Member für IPropertyAction-Methoden
	WExtendBScript m_BScript;
	typedef list<WEnumLONG> COutObjs;
	COutObjs m_OutObjs;		// die vereinigten Flächenobjekte
	COutObjs::iterator m_OutObjsIter;	// dazu den Iterator
	COutObjs m_OrigObjs;	// die Flächenobjekte, die zur Vereinigung beigetragen haben
	COutObjs::iterator m_OrigObjsIter;
//	WProgressIndicator2 m_wProgInd;	// eigener ProgressIndicator, wenn keiner runtergereicht wird
//	PIFLAGS m_rgFlags;				// Flags des eigenen ProgressIndicator


	// Memberfunctions
	void UnLoadAndCLOSE (void);

	bool AcceptanceTestObjOper (HWND hWnd);
	bool LineIsClosedPolygon (long lONr);

	bool AktiviertesObjekt (void);
	HRESULT ObjectOperations (HWND hWnd);
	bool IdentAndRechWindows (IEnumObjectsByNumber* pEnumOutput,
							  IEnumObjectsByNumber* pEnumUsed, ulong ulIdent, bool bOK);
	HRESULT ObjectsForRechWindows (IEnumObjectsByNumber* pEnumUsed);
	HRESULT ObjectsForRechWindows (IEnumLONG* pEnumUsed, IEnumLONG* pEnumNew);
	bool ObjekteAnTRiAS (HPROJECT hPr, bool bOK);
	bool ClipListeAnTRIAS (HPROJECT hPr, ClipListe& CL);
	HRESULT NewObjectsToTRiAS (ClipListe& CL);
	void Ergebnisanzeige (void);
	void FensterNeueObjekte (POINT& pt, int& iRWHoehe);
	void FensterAlteObjekte (POINT& pt, int& iRWHoehe);
	bool FeldAktObjNr (long*& lpFeld, long& lInd, long& lAnzObj, bool bSel);
	void MakeNewObjectsVisible (void);

	long StuetzpunktAnzahl1 (void);
	long StuetzpunktAnzahl2 (void);
	double Fangbereich (void);

	HRESULT SchnittAusfuehren (HPROJECT hPr, bool bFortAnz, IEnumLONG** ppEnumOut);
	bool GemeinsameRoutine1 (IEnumLONG* pEnumIn, SpForm sfSForm, bool bFortAnz, long& lSumme);
	HRESULT GemeinsameRoutine2 (HPROJECT hPr, IEnumLONG** ppEnumOut);
	HRESULT ExklOderAusfuehren (bool bFortAnz, IEnumLONG** ppEnumOut);
	HRESULT GetObjNummern (IEnumLONG* pEnumIn, bool bBObj = false);
	HRESULT PointCutOneLine (KoOrd lTX, KoOrd lTY, bool bOrigPt, IObjektGeometrie* pIOG,
							 long lONr);

	HRESULT InitProgressIndicator (IProgressIndicator2* pPI, ResID uiTitel, ResID uiAdjust,
								   ulong ulMaxPos, ulong ulMinPos = 1);
	HRESULT RegisterPI (IProgressIndicator2* pPI);
	HRESULT UnRegisterPI (void);

	bool FindMenuItem (HMENU hMenu, UINT uiID);

protected:
	// überladene virtuelle Funktionen
	STDMETHOD_(BOOL, InitExtension) (short iMode);
	STDMETHOD_(BOOL, MenuInit) (HMENU hMenu, LPARAM lParam, HWND hWnd);
	STDMETHOD_(BOOL, MenuCommand) (UINT uiMenuID, HWND hWnd);
	STDMETHOD_(LRESULT, Notification) (WPARAM wParam, LPARAM lParam);
	STDMETHOD_(BOOL, UnLoadExtension) (void);
	
public:
// Konstruktor / Destruktor
		ObjektOpExtension (void);
		~ObjektOpExtension (void);

	BEGIN_COM_MAP(ObjektOpExtension)		// Makro
		COM_INTERFACE_ENTRY(ITriasXtension2)
		COM_INTERFACE_ENTRY(ITriasXtension)
		COM_INTERFACE_ENTRY(IExtendObjOper)
#if defined(__ATL_20_USED__)
		COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
#else
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
#endif // !defined(__ATL_20_USED__)
	END_COM_MAP()
	DECLARE_NO_REGISTRY()

	DECLARE_NOT_AGGREGATABLE_SINGLE(ObjektOpExtension, g_pTE)
	DECLARE_CLASSFACTORY2(CMyLicense)

	BEGIN_CONNECTION_POINT_MAP(ObjektOpExtension)	// Makro
#if defined(__ATL_20_USED__)
		CONNECTION_POINT_ENTRY(IID_IProgressIndicator2)
#else
		CONNECTION_POINT_ENTRY(m_PPI)
#endif // !defined(__ATL_20_USED__)
	END_CONNECTION_POINT_MAP()

// Memberfunktionen
	long ONrAO (void) const { return _lONrAO; }
	bool ExklusivOder (HPROJECT hPr, bool bCopyFeat, bool bOrigZeigen, bool bNeuZeigen,
					   IEnumLONG** ppEnumUsed = 0, IEnumLONG** ppEnumNew = 0);
	bool EinzObjSchneiden (long lONr);
	bool ObjektSchneiden (long lONr);
	long StuetzpunkteAussen (long lONr);
	bool EinzObjDurchschnitt (long lONr);
	bool ObjektDurchschnitt (long lONr);
	bool EinzFlaeVereinigen (long lONr);
	bool FlaeVereinigen (long lONr);
	bool EinzObjExklOder (long lONr);
	bool ObjektExklOder (long lONr);
	bool GemeinsameKante (long lONr1, long lONr2);
	void ObjNrSpeichern (long lONr);
	void IdentModify (ulong ulIdent);
	void CopyFeatures (long lAltONr, long lNeuONr);
	bool TransmitParentsFeatures (long lAInd, long lEInd, long lONr, string sUISubst);
	HRESULT SetMembers (IEnumLONG* pEnumOrig, IEnumLONG* pEnumOut);
	void ObjekteLoeschen (long*& lpObjNr, long& lInd);
	void OptionsAnalyse (DWORD dwOptions);
	void MarkObject (void);
    IExtendGeoRein* GeoReinInterface (void);


	HRESULT SchnittObjObjekte_ONr (HPROJECT hPr, long lONr, IEnumLONG* pEnumTarget,
					   ulong ulLageAusw, SpForm sfSForm, bool bFortAnz, IEnumLONG** ppEnumNew);
	HRESULT SchnittObjObjekte_Geom (IObjektGeometrie* pIOG, IEnumLONG* pEnumIn,
					   ulong ulLageAusw, SpForm sfSForm, bool bFortAnz, IEnumLONG** ppEnumOut);
	HRESULT PointCutsLines (IObjektGeometrie* pIOG, bool bOrigPt, IEnumLONG** ppEnumOut);
	HRESULT SchnittKanteObj_Geom (HPROJECT hPr, IObjektGeometrie* pIOG, long lONr,
								  bool bFortAnz, IEnumLONG** ppEnumOut);
	HRESULT DurchschnittsFlaeche (HPROJECT hPr, IEnumLONG* pEnumIn, ulong ulIdent,
						 bool bCopyFeat, SpForm sfSForm, bool bFortAnz, IEnumLONG** ppEnumOut);
	HRESULT VereinigungsFlaeche (IEnumLONG* pEnumIn, ulong ulIdent, SpForm sfSForm,
								 bool bFortAnz, IEnumLONG** ppEnumOut);
	HRESULT ExklusivFlaeche_ONr (long lONr, IEnumLONG* pEnumIn, SpForm sfSForm, bool bFortAnz,
								 IEnumLONG** ppEnumOut);
	HRESULT ExklusivFlaeche_Geom (IObjektGeometrie* pIOG, IEnumLONG* pEnumIn, SpForm sfSForm,
								  bool bFortAnz, IEnumLONG** ppEnumOut);
	HRESULT GemeinsameKontur_ONr (long lONr, ulong ulIdent, IEnumLONG* pEnumIn,
					   ulong ulLageAusw, SpForm sfSForm, bool bFortAnz, IEnumLONG** ppEnumOut);
	HRESULT GemeinsameKontur_Geom (IObjektGeometrie* pIOG, ulong ulIdent, IEnumLONG* pEnumIn,
					   ulong ulLageAusw, SpForm sfSForm, bool bFortAnz, IEnumLONG** ppEnumOut);
	HRESULT AreasUniting (HPROJECT hPr, IEnumLONG* pEnumIn, string sOCName, bool bCopyFeat,
			IEnumLONG** ppOrigEnumOut, IEnumLONG** ppUniEnumOut, IProgressIndicator2* pPI = 0);
	HRESULT LinesUniting (HPROJECT hPr, IEnumLONG* pEnumIn, double dTol, bool bCopyFeat,
						  bool bAsArea, ulong ulIdent, IEnumLONG** ppOrigEnumOut,
						  IEnumLONG** ppUniEnumOut, IProgressIndicator2* pPI = 0);
	HRESULT LinienZusammenfassung (IEnumLONG* pEnumIn, ulong ulIdent, double dTol,
								   bool bAsArea, IEnumLONG** ppEnumOut);
	HRESULT LinienZusammenfassung (IObjektGeometrie* pIOGIn1, IObjektGeometrie* pIOGIn2,
					double dFill, bool bAsArea, ulong ulIdent, IObjektGeometrie** ppIOGOut);
	HRESULT SplittingBase (HPROJECT hPr, IEnumLONG* pEnumIn, KoOrd lFuzzyX, KoOrd lFuzzyYULONG,
		KoOrd lDangle, IEnumLONG** ppEnumOutAtom, IEnumLONG** ppEnumOutMod,
		IEnumLONG** ppEnumOutNotTouched = NULL);
	HRESULT LinienVerschiebung_ONr (long lONr, KoOrd lXB, KoOrd lYB, KoOrd lXA, KoOrd lYA,
						KoOrd lXE, KoOrd lYE, MoveDir MD, bool bVerlA, bool bVerlE, KoOrd lEps,
						KoOrd lXMin, KoOrd lYMin, KoOrd lXMax, KoOrd lYMax, long* plONr);
	bool LineElongation (IObjektGeometrie* pIOG, bool bAnf, KoOrd lXMin, KoOrd lYMin,
						 KoOrd lXMax, KoOrd lYMax);

	// IExtendObjOper-Methoden
	STDMETHOD_ (HRESULT, SectionObjObjs_ONr) (LONG lONr, IEnumLONG* pEnumIn, DWORD dwLageAusw,
											  SpForm sfSForm, IEnumLONG** ppEnumOut);
	STDMETHOD_ (HRESULT, ObjectSection) (HPROJECT hPr, IEnumLONG* pEnumRegard,
								 IEnumLONG* pEnumTarget, DWORD dwLage, BOOL bCopyFeat,
								 BOOL bFortAnz, IEnumLONG** ppEnumUsed, IEnumLONG** ppEnumNew);
	STDMETHOD_ (HRESULT, SectionObjObjs_Geom) (IObjektGeometrie* pIOG, IEnumLONG* pEnumIn,
									  DWORD dwLageAusw, SpForm sfSForm, IEnumLONG** ppEnumOut);
	STDMETHOD_ (HRESULT, SectionObjOClass_ONr) (LONG lONr, ULONG ulIdent, DWORD dwLageAusw,
											    SpForm sfSForm, IEnumLONG** ppEnumOut);
	STDMETHOD_ (HRESULT, SectionObjOClass_Geom) (IObjektGeometrie* pIOG, ULONG ulIdent,
									  DWORD dwLageAusw, SpForm sfSForm, IEnumLONG** ppEnumOut);
	STDMETHOD_ (HRESULT, SectionLineObj_Geom) (IObjektGeometrie* pIOG, LONG lONr,
											   IEnumLONG** ppEnumOut);
	STDMETHOD_ (HRESULT, SectionLineObjs_Geom) (IObjektGeometrie* pIOG, ULONG ulIdent,
												IEnumLONG** ppEnumOut);
	STDMETHOD_ (HRESULT, AndArea) (IEnumLONG* pEnumIn, ULONG ulIdent, SpForm sfSForm,
								   IEnumLONG** ppEnumOut);
	STDMETHOD_ (HRESULT, OrArea) (IEnumLONG* pEnumIn, ULONG ulIdent, SpForm sfSForm,
								  IEnumLONG** ppEnumOut);
	STDMETHOD_ (HRESULT, XorArea_ONr) (LONG lONr, IEnumLONG* pEnumIn, SpForm sfSForm,
									   IEnumLONG** ppEnumOut);
	STDMETHOD_ (HRESULT, XorArea_Geom) (IObjektGeometrie* pIOG, IEnumLONG* pEnumIn,
										SpForm sfSForm, IEnumLONG** ppEnumOut);
	STDMETHOD_ (HRESULT, CommonContour_ONr) (LONG lONr, ULONG ulIdent, IEnumLONG* pEnumIn,
									  DWORD dwLageAusw, SpForm sfSForm, IEnumLONG** ppEnumOut);
	STDMETHOD_ (HRESULT, CommonContour_Geom) (IObjektGeometrie* pIOG, ULONG ulIdent,
				  IEnumLONG* pEnumIn, DWORD dwLageAusw, SpForm sfSForm, IEnumLONG** ppEnumOut);
	STDMETHOD_ (HRESULT, LinesUnion) (IEnumLONG* pEnumIn, ULONG ulIdent, ULONG ulFill,
									  BOOL bAsArea, SpForm sfSForm, IEnumLONG** ppEnumOut);
	STDMETHOD_ (HRESULT, LinesUnion_Geom) (IObjektGeometrie* pIOGIn1,
										 IObjektGeometrie* pIOGIn2, ULONG ulFill, BOOL bAsArea,
										 ULONG ulIdent, IObjektGeometrie** ppIOGOut);
	STDMETHOD_ (HRESULT, Splitting) (IEnumLONG* pEnumIn, ULONG ulFuzzyX, ULONG ulFuzzyY,
									 ULONG ulDangle, IEnumLONG** ppEnumOutAtom,
									 IEnumLONG** ppEnumOutMod);
	STDMETHOD_ (HRESULT, LineShifting_ONr) (LONG lONr, LONG lXB, LONG lYB, LONG lXA, LONG lYA,
						   LONG lXE, LONG lYE, MoveDir MD, BOOL bVerlA, BOOL bVerlE, LONG lEps,
						   LONG lXMin, LONG lYMin, LONG lXMax, LONG lYMax, LONG* plONr);
	STDMETHOD_ (HRESULT, LineShifting_Geom) (IObjektGeometrie* pIOG, LONG lXB, LONG lYB,
				  LONG lXA, LONG lYA, LONG lXE, LONG lYE, MoveDir MD, BOOL bVerlA, BOOL bVerlE,
				  LONG lEps, LONG lXMin, LONG lYMin, LONG lXMax, LONG lYMax, LONG* plONr);

// IPropertyAction methods
	STDMETHOD (BeginAction) (THIS_ HPROJECT hPr, string sOCName,
							 IProgressIndicator* pIProgInd = 0);
	STDMETHOD (DoAction) (HPROJECT hPr, IEnumLONG* pEnumIn);
	STDMETHOD (EndAction) (HPROJECT hPr, IEnumLONG** ppOrigEnum, IEnumLONG** ppEnumOut);
	STDMETHOD (SetDeleteFlag) (HPROJECT hPr, BOOL bDelete);
	STDMETHOD (CleanUpScript) (void);
};



// Die nachfolgenden Funktionen kommen evtl. später in die GeoDLL
bool BuildMarkLine (void);
HRESULT Verschnitt (HPROJECT hPr, long lOrigObjNr1, long* plOrigObjNr, long lAnzOrigObj,
	KoOrd lFuzzyX, KoOrd lFuzzyY, KoOrd lDangle, IEnumLONG** ppEnumOutAtom, 
	IEnumLONG** ppEnumOutMod, IEnumLONG** ppEnumOutNotTouched = NULL);
void VektorErweiterung (KoOrd* plXK1, KoOrd* plYK1, long lSize1, MarkLine*& pML,
						IObjektGeometrie* pKante2, KoOrd lFuzzyX, KoOrd lFuzzyY, bool bSelf,
						bool& bCommon);
long EinfIndex (KoOrd* pXK, KoOrd* pYK, long lInd, MarkLine* pML, DoublePair ZP);
bool EinfMarkPunkt (MarkLine*& pML, DoublePair DP, long lIndex);
bool TeilobjekteBilden (HPROJECT hPr, MarkLine* pML, long lAltObjNr, long lDangle,
						IEnumLONG* pEnumOut);
bool DangleObject (MarkLine* pML, long lAInd, long lEInd, long lDangle);
bool NeuesTeilobjekt (HPROJECT hPr, MarkLine* pML, long lAInd, long lEInd, long lDangle,
					  long lAltObjNr, long& lNeuONr);
bool TeilobjektSpeichern (HPROJECT hPr, IObjektGeometrie* pIOG, long lAltObjNr, long& lNeuONr);



///////////////////////////////////////////////////////////////////////////////////////////////
// Struktur für Datenübergabe an Routine EnumMerkmaleProc()
struct MerkmalInfos 
{
	CMerkmalsListe* pListe;
	long lOrigONr;		// Objektnummer eines "Eltern"-Objektes
	HPROJECT hPr;		// ProjectHandle des neu erzeugten Objektes
	bool bCopyFeat;		// alle Objektmerkmale kopieren (true) bzw. nur die
						// "Elten"-UniqueIdents übernehmen (false)
};

#endif  // _OBJOPER_HXX
