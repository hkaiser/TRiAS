// Erweiterungsklasse für "Geometriebereinigung"
// File: GEOREIN.HXX
// W. Mörtl

#if !defined(_GEOREIN_HXX)
#define _GEOREIN_HXX


#include "SmartInterfaces.h"


class GeoReinExtension : public IExtendGeoRein,
						 public IAdjustValues,
						 public CTriasExtension,
						 public CComCoClass<GeoReinExtension, &CLSID_GeometrieBereinigung>
{
private:
	ERRHANDLER m_oldEH;		// alte Fehlerbehandlungs-Methode

	short m_iMode;			// Parameter von InitExtension()

	CoordTransX* m_pCT;
	bool m_bMetric;			// metrische (true) oder geodätische Datenbank

	ulong m_ulMCodeGeoErr;		// MerkmalsCode für Geometriefehler
	ulong m_ulMCodeGeoClear;	// MerkmalsCode für bereinigten Geometriefehler
	ulong m_ulMCodeInterSect;	// MerkmalsCode für Verschnitt
	long m_lSem;				// Semaphor

	bool m_bAnzeige;	// Anzeige bei KoOrd-Koordinaten noch nicht erfolgt
	int m_iOT;			// Typ des zu testenden Objektes (kann bei Entartungen umgewandelt
						// werden)
	bool m_bClear;		// Wert des Schlüssels "AutoClear"
	double m_dDPEps;	// Grenzwert (in Meter) für Test auf "doppelte Punkte"
	double m_dSpEps;	// Grenzwert (in Gradmaß) für Test auf "Spitze"
	int m_iLoopLen;		// min. Stützpunktanzahl für eine abzutrennende Schleife am Ende einer Kante
	double m_dReduz;	// Wert (0.0 ... 1.0) für die Reduzierung der Stützpunktanzahl bei der
						// Polygonapproximation

	bool InitAndOPEN (int iMode);
	void UnLoadAndCLOSE (void);
	void AdjustValuesToRegistry (void);

	WExtendAbstand2 m_wAbstand;	// Interface für Ankopplung von Abstand.ext
	WExtendTopRel2 m_wTopoRel;	// Interface für Ankopplung von TopoRel.ext


	void SetFeatureWithError (long lONr, EObjekt* pEO, OBJGEOMETRIE* pOG, bool bDblCoord,
							  int& iFlags, bool& bEIO, string sAnalyseText, string sUIdent);
	void SetFeatureWithoutError (long lONr, EObjekt* pEO, OBJGEOMETRIE* pOG, bool bDblCoord,
		    int& iFlags, bool& bEIO, string sAnalyseText, string sUIdent, GeoFehlerListe& GFL);
	bool GeometrieCheck (OBJGEOMETRIE *pOG, IUnknown *pICS = NULL);
	bool GeometrieTest (GeoFehlerListe& GFL, EObjekt& EO, bool bDblCoord, int iFlags,
						string& sAnalyseText);
	bool GeoAnalyse (EPunkt& Pt, GeoFehlerListe&, long j=-1, int i=-1);
	bool GeoAnalyse (EKante& Kt, GeoFehlerListe& GFL, bool& bSInz, bool& bEntart,
					 int i = -1);
	bool ExtraTestClosedLine (EKante& Kt, GeoFehlerListe& GFL, int i, DoublePair dpUF);
	bool GeoAnalyse (EFlaeche& Fl, bool bDblCoord, GeoFehlerListe&);
	bool KonturTausch (EFlaeche& Fl, bool bKontInzid, bool& bOutside, GeoFehlerListe& GFL);
	bool KurzGeoAnalyse (EKante* pKt, TestRicht trRicht, long& lSInd, int iKInd = -1);
	bool KurzGeoAnalyse (EFlaeche* pFl, TestRicht trRicht, long& lSInd, int iKInd,
						 bool& bObjMod);
	bool KonturInzidenzfrei1 (EFlaeche* pFl, long lInd1, long lInd2, int iKInd);
	bool KonturInzidenzfrei2 (EFlaeche* pFl, long lInd1, long lInd2, int iKInd, int ii,
							  long& lKInzOS);

	bool GeometriePutzen (IObjektGeometrie* pIOG);
	bool GeometrieAnalysieren (IObjektGeometrie* pIOG);
	bool PointAnalysis (EPunkt& Pt);
	bool LineAnalysis (EKante& Kt, long lCnt, int i = -1);
	bool AreaAnalysis (EFlaeche& Fl, short iKCnt);
	bool ExtraTestClosedLine (EKante& Kt, int i, DoublePair dpUF);
	bool KurzAnalyse (IObjektGeometrie* pIOG, TestRicht trRicht, long& lSInd);

	HRESULT InterGeometryTest (IObjektGeometrie* pIOG1, int iOT1, IObjektGeometrie* pIOG2,
							   int iOT2, ErrorTextMode etText, BOOL* pbSucc);
	HRESULT VerticesLoops (IObjektGeometrie* pIOG1, int iOT1, IObjektGeometrie* pIOG2,
						   int iOT2, string sObjName1, string sObjName2,
						   ErrorTextMode etText, bool& bNear, bool& bSucc);
	bool isNear (double dEps, DoublePair dpUF, bool bMetric, KoOrd x1, KoOrd y1, KoOrd x2,
				 KoOrd y2);
	bool AcuteAngle (double dSpEps, IObjektGeometrie* pIOG1, int iOT1, long lCn1,
					 KoOrd* plXK1,KoOrd* plYK1, long j1, IObjektGeometrie* pIOG2,
					 int iOT2, long lCnt2, KoOrd* plXK2, KoOrd* plYK2, long j2);
	bool isAcute (double dSpEps, KoOrd x1, KoOrd y1, KoOrd x2, KoOrd y2, KoOrd x3, KoOrd y3,
				  bool bSingle);
	void AnalysePuffern (string& sAnalyseText, KoOrd x1, KoOrd y1, KoOrd x2 = 0, KoOrd y2 = 0);
	HRESULT SmallDistance (IObjektGeometrie* pIOG1, IObjektGeometrie* pIOG2, string sObjName1,
						   string sObjName2, ErrorTextMode etText, bool& bSucc);
	HRESULT OverLapping (IObjektGeometrie* pIOG1, IObjektGeometrie* pIOG2, string sObjName1,
						 string sObjName2, ErrorTextMode etText, bool& bSucc);
	HRESULT EnclosingTest (IObjektGeometrie* pIOG1, IObjektGeometrie* pIOG2, string sObjName1,
						   string sObjName2, ErrorTextMode etText, bool& bSucc);
	HRESULT InterErrorToFeature (IObjektGeometrie* pIOG, string sAnalyseText, string sObjName);
	void ObjNameInsert (string& sAnalyseText, string sObjName);
	HRESULT AbstandInterface (IUnknown** ppIAbstand);
	HRESULT TopoRelInterface (IUnknown** ppITopoRel);
	bool Approximation32 (OBJGEOMETRIE* pOG);
	bool IsLineWithLoop (GeoFehlerListe& GFL, long lIdent, int iFlags, string sUIdent);

		
protected:
// überladene virtuelle Funktionen
	STDMETHOD_(BOOL, InitExtension) (short iMode);
	STDMETHOD_(LRESULT, Notification) (WPARAM wParam, LPARAM lParam);
	STDMETHODIMP_(LRESULT) WindowsNotification (UINT wMsg, WPARAM, LPARAM p);
	STDMETHOD_(BOOL, UnLoadExtension) (void);

	bool GeometryErrorToFeature (OBJGEOMETRIE* pOG, uint uiResKey, uint uiResKT, uint uiResLT,
								 ulong& ulMCode, string sAnalyseText, string sUIdent);
	void FehlerMerkmalLoeschen (long lONr);
	bool _GetDebugOutputFlag (void);

public:
// Konstruktor / Destruktor
		GeoReinExtension (void);
		~GeoReinExtension (void);

	BEGIN_COM_MAP(GeoReinExtension)		// Makro
		COM_INTERFACE_ENTRY(ITriasXtension2)
		COM_INTERFACE_ENTRY(ITriasXtension)
		COM_INTERFACE_ENTRY(IExtendGeoRein)
		COM_INTERFACE_ENTRY(IAdjustValues)
	END_COM_MAP()
	DECLARE_NO_REGISTRY()

	DECLARE_NOT_AGGREGATABLE_SINGLE(GeoReinExtension, g_pTE)

	// IExtendGeoRein-Methoden
	STDMETHOD_ (HRESULT, WholeAnalysis_ONr) (LONG lONr, BOOL* pbSucc);
	STDMETHOD_ (HRESULT, WholeAnalysis_Geom) (IObjektGeometrie* pIOG, BOOL* pbSucc);
	STDMETHOD_ (HRESULT, ShortAnalysis) (IObjektGeometrie* pIOG, TestRicht trRicht,
										 LONG* plSInd);
	STDMETHOD_ (HRESULT, InterObjectsAnalysis_ONr) (LONG lONr1, LONG lONr2,
													ErrorTextMode etText, BOOL* pbSucc);
	STDMETHOD_ (HRESULT, InterObjectsAnalysis_Geom) (IObjektGeometrie* pIOG1,
								  IObjektGeometrie* pIOG2, ErrorTextMode etText, BOOL* pbSucc);
	STDMETHOD_ (HRESULT, ReducedGeometryCleaning) (IObjektGeometrie* pIOG);


	// IAdjustValues-Methoden
	STDMETHOD_ (HRESULT, GetAdjustValue) (AdjValue avKey, LONG* plValue);
	STDMETHOD_ (HRESULT, SetAdjustValue) (AdjValue avKey, LONG lValue);

};


// Struktur für Datenübergabe der Routine DEX_SetError()
struct ErrBox
{
	string sErrText;		// Fehlertext für Dialogbox
	bool bAnsw;				// Antwort (Ja: bAnsw = true, Nein: bAnsw = false)
};

#endif  // _GEOREIN_HXX
