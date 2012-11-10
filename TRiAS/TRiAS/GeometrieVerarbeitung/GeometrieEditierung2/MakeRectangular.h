// Deklarationen: Fläche rechtwinklig machen
// File: MakeRectangular.h
// W. Mörtl

#ifndef _MAKERECTANGULAR_H_
#define _MAKERECTANGULAR_H_


#include "SmartInterfaces.h"

#include "objgguid.h"	// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie


///////////////////////////////////////////////////////////////////////////////////////////////
// Klasse für das Rechtwinkligmachen einer Fläche
// IModifyOperation ist das Interface, das alle ModifyOperation's für die CObjectModify-Klasse
// bereitstellen, d.h. das Interface, über das die CObjectModify-Klasse die ModifyOperation's
// rufen kann (Gegen-Interface zu IModifyClassSite)
class CMakeRectangular : public IModifyOperation,
						 public CComObjectRoot,
						 public CComCoClass<CMakeRectangular, &CLSID_MakeRectangular>
{
private:
	WEditExtensionSite m_wEdExSite;	// Interface von CGeoEditExtension für EditierOperationen
	WModifyClassSite m_wModClSite;	// Interface der Klasse CObjectModify
	WTopicalObjects m_wTopObjs;		// Interface der Klasse CTopicalObjects

	long m_lAktONr;					// Objektnummer der aktivierten (blinkenden) Fläche, deren
									// Winkel rechtwinkling gemacht werden sollen
	StrWinkel* m_pWink;				// Einteilung der Winkel
	KoOrd* m_plX;					// Koordinaten der
	KoOrd* m_plY;					//  aktivierten Fläche
	KoOrd* m_plUrX;					// Speicher für (teilweises) Retten
	KoOrd* m_plUrY;					//  der Ursprungskoordinaten
	long m_lAInd;					// Index des 1. Stützpunktes der zu behandelnden Kontur
	long m_lEInd;					// Index des letzten Stützpunktes
	long m_lStartInd;				// Index des ersten Stützpunktes der Bezugsstrecke
									// (Startindex)
	long m_lStopInd;				// Endindex für ContourUp() und ContourDown()
	bool m_bGestr;					// es gibt/keine Winkel "nahe" 180° (true/false)
	double m_xm;					// errechneter Mittelpunkt eines "fast" gestreckten
	double m_ym;					// Konturabschnittes
	bool m_bContUp;					// Kontur wird mit steigendem (true) bzw. fallendem Index
									// abgearbeitet
	bool m_bAllgm;					// einen/keinen allgemeinen Winkel erreicht (true/false) 
	double m_dMaxDiv90;				// maximale Abweichung eines Winkels von 90°/270°

	// Memberfunktionen
	RectMode AngleClassification (double dEps90, double dEps180);
	void MakeRightAngles (void);
	HRESULT SaveOriginalCoordinates (int iKInd, long lCnt);
	long NextInterestingUpVertex (long lInd);
	long NextInterestingDownVertex (long lInd);
	void ContourUp (void);
	void ContourDown (void);
	void AngleTest (long j0, long j1, long j2);
	void Angle90 (long j0, long j1, long j2);
	void Angle90Back (long j0, long j1, long j2);
	void SegmentCentre (long j1, long j2, double& xml, double& yml);
	void LineProportions (void);
	void ClearCollinear (long ja, long je);
	bool AddAngleFeature (void);
	bool AddGrabFeature (long lONr, long lVtLoss);
	HRESULT ModifyCommonVertices (long lSaveCnt, int iKInd, double dEpsCom,
					   Rectangle& AllRec, bool& bAllRecInit, IEnumObjectsByNumber** ppEnumOut);
	HRESULT AdjustInsideContours (int iKCnt, long* plCnt, double dEps90, double dEps180,
								  RectMode& rModeIn);
	HRESULT MakeInsideContourRectangular (long lOCStartInd);
	void GetInsideContourStartIndex (long lOCStartInd);
	HRESULT RectangularAreaToTRiAS (IObjektGeometrie* pIOG, long lCnt, Rectangle AllRec,
									bool bAllRecInit);

public:
	// Konstruktor, Destruktor
	CMakeRectangular (void);
	~CMakeRectangular (void);

	DECLARE_REGISTRY_RESOURCEID(IDR_MAKERECTANGULAR)

	BEGIN_COM_MAP(CMakeRectangular)
		COM_INTERFACE_ENTRY(IModifyOperation)
	END_COM_MAP()

	// IModifyOperation
	STDMETHOD (SetModifyClassSite) (IEditExtensionSite* pIEdExSite,
									IModifyClassSite* pIModClSite);
	STDMETHOD (LineElongation) (IEnumObjektGeometrie*, long, long);
	STDMETHOD (AreaPartition) (long, POINT);
	STDMETHOD (IslandAddition) (IEnumObjektGeometrie*);
	STDMETHOD (Rectangularity) (long lONr, int iKInd, long lStartInd, double dEps90,
							 double dEps180, double dEpsCom, IEnumObjectsByNumber** ppEnumOut);
	STDMETHOD (MakeCommonBorder) (IEnumObjektGeometrie*, long, long);
};

#endif //_MAKERECTANGULAR_H_
