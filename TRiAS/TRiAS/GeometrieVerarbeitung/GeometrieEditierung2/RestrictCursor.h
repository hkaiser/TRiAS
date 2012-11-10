// Deklarationen: Nachziehen des vom Mauszeiger abgetrennten Cursors (in Kreuzform)
// File: RestrictCursor.h
// W. Mörtl

#ifndef _RESTRICTCURSOR_H_
#define _RESTRICTCURSOR_H_


#include "DragCrossObject.h"		// DragCrossObject


///////////////////////////////////////////////////////////////////////////////////////////////
// Klasse für das Nachziehen des vom Mauszeiger abgetrennten Cursors (in Kreuzform)
class CRestrictCursor : public IRestrictCursor,		// Interface von CRestrictCursor
						public CComObjectRoot,
						public CComCoClass<CRestrictCursor, &CLSID_RestrictCursor>
{
private:
	Window* m_pVWnd;				// TRiAS-ViewFenster
	DragCrossObject* m_pRestrCur;	// abgetrennte Cursor (in Kreuzform)
	Dimension m_MyDim;				// Ausdehung
	BOOL m_bFirst;					// der 1. Aufruf von SetPoint() (true)
	bool m_bDraw;					// Cursor ist gezeichnet (true) bzw. gelöscht (false)

public:
		// Konstruktor, Destruktor
		CRestrictCursor (void);
		~CRestrictCursor (void);

	DECLARE_REGISTRY_RESOURCEID(IDR_RESTRICTCURSOR)

	BEGIN_COM_MAP(CRestrictCursor)
		COM_INTERFACE_ENTRY(IRestrictCursor)
	END_COM_MAP()

	// IRestrictCursor
	STDMETHOD (ConstructRestrictCursor) (void);
	STDMETHOD (SetPoint) (POINT PTCent, BOOL bIsPaint);
	STDMETHOD (SetFirstFlag) (BOOL bFirst) { m_bFirst = bFirst; return S_OK; }
	STDMETHOD (GetBoundingBox) (RECT* pREC);
	STDMETHOD (GetDimension) (long* plWidth, long* plHeight)
		{ *plWidth = m_MyDim.Width(); *plHeight = m_MyDim.Height(); return S_OK; }
	STDMETHOD (UnDraw) (void);

};

#endif //_RESTRICTCURSOR_H_
