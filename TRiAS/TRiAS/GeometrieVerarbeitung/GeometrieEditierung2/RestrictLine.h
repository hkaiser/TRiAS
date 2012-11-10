// Deklarationen: Hilfslinien für den DesignMode
// File: RestrictLine.h
// W. Mörtl

#ifndef _RESTRICTLINE_H_
#define _RESTRICTLINE_H_


///////////////////////////////////////////////////////////////////////////////////////////////
// Klasse für die Bildung der Hilfslinien für den DesignMode
class CRestrictLine : public IRestrictLine,	// Interface von RestrictLine
					  public CComObjectRoot,
					  public CComCoClass<CRestrictLine, &CLSID_RestrictLine>
{
private:
    pWindow m_pVWnd;		// TRiAS-ViewFenster
	DrawObject* m_pKHL;		// Konstruktionshilfslinie
	Pen m_MyPen1;			// Visualisierung einer Hilfslinie, auf der sich der Cursor bewegen
							// kann
//	Pen m_MyPen2;			// Visualisierung einer Hilfslinie, auf der sich der Cursor NICHT
							// bewegen kann
	Brush m_MyBrush;		// Visualisierung der Innenfläche einer kreisförmigen Hilfslinie
	KoOrd m_lFixX, m_lFixY;	// unveränderliche Parameter der
	double m_dAngle, m_dLength;	//  Konstruktionshilfslinie
	double m_dUFX, m_dUFY;	//  (im Gegensatz zu den bildschirmbezogenen Parametern)
	RestrType m_ResType;	// Form der Konstruktionshilfslinie (GERADE, KREIS, STRECKE)
	Point m_EPt1;			// 1. Endpunkt									}  nur für GERADE
	Point m_EPt2;			// 2. Endpunkt									}  und STRECKE
	Point m_RefPt;			// Bezugspunkt für EllipseObject (der linke		}
							// untere Eckpunkt des umschreibenden Quadrats	}  nur für
	int m_iRad;				// Radius										}  KREIS
	bool m_bUnDraw;			// Konstruktionshilfslinie wurde auf dem Bildschirm gelöscht (true)

	bool BuildStraightLine (KoOrd lFixX, KoOrd lFixY, double dAngle);
	bool BuildCircleLine (KoOrd lFixX, KoOrd lFixY, double dDist);
	bool BuildSegmentLine (KoOrd lFixX, KoOrd lFixY, double dAngle, double dDist);

	HRESULT CursorToSegmentSegment (Point MSPt, Point EPt11, Point EPt21, Point EPt12,
			Point EPt22, POINT* pPTCur);
	HRESULT CursorToSegmentStraight (Point MSPt, Point EPt11, Point EPt21, Point EPt12,
			Point EPt22, POINT* pPTCur);
	HRESULT CursorToSegmentCircle (Point MSPt, Point EPt1, Point EPt2, Point MPt, int iRad,
			POINT* pPTCur);
	HRESULT CursorToStraightStraight (LPARAM lParam, Point EPt11, Point EPt21, Point EPt12,
			Point EPt22, POINT* pPTCur);
	HRESULT CursorToStraightCircle (Point MSPt, Point EPt1, Point EPt2, Point MPt, int iRad,
			POINT* pPTCur);
	HRESULT CursorToCircleCircle (LPARAM lParam, Point MSPt, Point MPt1, int iRad1, Point MPt2,
			int iRad2, POINT* pPTCur);

	void CursorToStraight (Point MSPt, double dLotPX, double dLotPY, Point EPt1, Point EPt2,
			POINT* pPTCur);
	void CursorToNearbyPoint (Point MSPt, Point Pt1, Point Pt2, POINT* pPTCur);
	void ExpandingSreenSection (Point ExtPt1, Point ExtPt2 = Point (0,0));

public:
	// Konstruktor, Destruktor
	CRestrictLine (void);
	~CRestrictLine (void);

	DECLARE_REGISTRY_RESOURCEID(IDR_RESTRICTLINE)

	BEGIN_COM_MAP(CRestrictLine)
		COM_INTERFACE_ENTRY(IRestrictLine)
	END_COM_MAP()

	// IRestrictLine
	STDMETHOD (GetParameters) (RestrType* pResType, POINT* pEPT1, POINT* pEPT2, POINT* pRefPT,
			int* piRad, long* plFixX, long* plFixY, double* pdAngle);
	STDMETHOD (BuildRestrictLine) (LONG lFixX, LONG lFixY, RestrType ResType, double dAngle,
			double dLength, double dUFX, double dUFY);
	STDMETHOD (CursorTo1RestrictLine) (LPARAM lParam, POINT* pPTCur);
	STDMETHOD (CursorTo2RestrictLines) (LPARAM lParam, IRestrictLine* pRestrLine2,
			POINT* pPTCur);
	STDMETHOD (Draw) (void);
	STDMETHOD (UnDraw) (void);

};

#endif //_RESTRICTLINE_H_
