// Deklarationen: Nachziehen von mehreren Linien
// File: DragMultiLine.h
// W. Mörtl

#ifndef _DRAGMULTILINE_H_
#define _DRAGMULTILINE_H_


#include "dragline.hxx"		// DragLineObject


///////////////////////////////////////////////////////////////////////////////////////////////
// Klasse für das Zeichnen mehrerer Linien
// IDragObject ist das Interface für CDragMultiLine
class CDragMultiLine : public IDragObject,
					   public CComObjectRoot,
					   public CComCoClass<CDragMultiLine, &CLSID_DragMultiLine>
{
private:
	Window* m_pDrawWnd;
	Point* m_pStartPt;			// Startpunkte der zu zeichnenden Linien
	int m_iLineCount;			// Anzahl der zu zeichnenden Linien
	DragLineObject** m_ppDLO;	// Vektor der zu zeichnenden Linien
	bool m_bScroll;				// die durch Scrollen notwendig gewordene Startpunktkorrektur
								// ist schon ausgeführt worden (true)

public:
	// Konstruktor, Destruktor
	CDragMultiLine (void);
	~CDragMultiLine (void);

	DECLARE_REGISTRY_RESOURCEID(IDR_DRAGMULTILINE)

	BEGIN_COM_MAP(CDragMultiLine)
		COM_INTERFACE_ENTRY(IDragObject)
	END_COM_MAP()

	// IDragObject
	STDMETHOD (AddStartPoint) (POINT PT);
	STDMETHOD (ConstructDragLines) (void);
	STDMETHOD (SetEndPoint) (POINT ptEnd, BOOL bIsPaint, BOOL bWithDel);
	STDMETHOD (DeleteLastSituation) (BOOL bIsPaint);
	STDMETHOD (ModStartPoints) (POINT* pStartPT, int iLineCount);
	STDMETHOD (DragTerminate) (void);
	STDMETHOD (EditWithScrolling) (long lOffset, BOOL bHorz);

};

#endif //_DRAGMULTILINE_H_
