// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.07.2000 20:26:06 
//
// @doc
// @module PrintBase.h | Declaration of the <c CPrintBase> class

#if !defined(_PRINTBASE_H__2F218452_8E33_4D0F_AC64_04BC9CEB45ED__INCLUDED_)
#define _PRINTBASE_H__2F218452_8E33_4D0F_AC64_04BC9CEB45ED__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "PrLayout.hxx"
#include "LayoutStyles.h"

///////////////////////////////////////////////////////////////////////////////
// basisklasse für Drucken und Druckvorschau, die die eigentliche Ausgaben macht
class CPrintBase
{
public:
	CPrintBase(PrintLayout *pPL, DatenBasisObjekt &rDBO);
	CPrintBase(PRINTLAYOUT *pPL, DatenBasisObjekt &rDBO, POINT &ptRatio);
	~CPrintBase();

// call up for cross_cast
	virtual HDC Handle(Service s) = 0;
	virtual void DrawEx (pDrawObject, DWORD) = 0;
	virtual pFont ChangeFont (pFont pF) = 0;
	virtual Rectangle CanvasRect() = 0;

	Point GetAspect() { return m_Aspect; }
	void SetAspect (Point pt) { m_Aspect = pt; }
	ObjContainer GetExtend() { return m_Extend; }
	void SetExtend (ObjContainer oc) { m_Extend = oc; }
	Rectangle GetActRect() { return m_ActRect; }
	void SetActRect (Rectangle rc) { m_ActRect = rc; }

// Reinitialise
	void SetRatio (int ix, int iy) 
	{
		m_Ratio.Width() = ix;
		m_Ratio.Height() = iy;
	}

// zusätzliche Initialisierungsfunktionen
	void SetDotsPerMM (DoublePair dblDots) { m_DotsPerMM = dblDots; }

	BOOL Expose (Window *pW, Rectangle rcEA, PrinterPars &rPP);

protected:
// Methoden
	BOOL CalcLinksObenRect (CLegSizeCache &rCache, Rectangle &rRc, int iCnt, Rectangle *prc);
	BOOL CalcRechtsObenRect (CLegSizeCache &rCache, Rectangle &rRc, int iCnt, Rectangle *prc);
	BOOL CalcLinksUntenRect (CLegSizeCache &rCache, Rectangle &rRc, int iCnt, Rectangle *prc);
	BOOL CalcRechtsUntenRect (CLegSizeCache &rCache, Rectangle &rRc, int iCnt, Rectangle *prc);

	BOOL PaintTextRect (LPCSTR pcText, int rgPos,
			Rectangle &rRc, int iFamily, LPCSTR pcFont, int iSizeY, 
			BOOL fBold, BOOL fItalic, BOOL fUnderline, BOOL fOpaque);

//	void PrintRefPoint (Punkt &P, DoublePair &D) const;
//	char *CnvrtOCtoRC (char *Str, int Len, KoOrd X, KoOrd Y);
	void PaintHeadLine (Rectangle &, LPCSTR pText);
	void PaintMasstab (CLegSizeCache &rCache);
	void PaintRahmen (Rectangle &rRC, int iWidth);	// Breite in 1/100 mm
	void FillRahmen (Rectangle &rRC);
	void PaintEdges (Rectangle &rRC);
	void PaintMeander (HDC hDC, int iTyp, Point pt, int dX, int dY, int iWidth, long lMax, int iZ, int iLine);
	void PaintFirmLogo (CLegSizeCache &rCache, Rectangle &rc, int iCnt);
	BOOL PaintFirmLogoFeld (CLegSizeCache &rCache, Rectangle &rRc, int rgPos, int iCnt, BOOL fOpaque);
	void PaintTRiASLogo (Rectangle &rRC);

// Daten
	DatenBasisObjekt &m_rDBO;
	CIdTree &m_Idents;
	class CLegendeObjekt *m_pLO;

// FormatierungsDaten (vom Ausgabegerät)
	DoublePair m_DotsPerMM;
	Point m_Aspect;

// AusgabeLayout (vom Dialog)
	Rectangle m_ActRect;
	ObjContainer m_Extend;
	Rectangle m_RcLegende;
	Rectangle m_RcMasstab;
	Rectangle m_RcFrame;
	Rectangle m_RcHeadLine;
	FrameStyle m_fsFrame;
	LegendStyle m_lsLegende;
	MasstabStyle m_msMasstab;
	char *m_lpHeadLine;
	long m_lMasstab;

	Rectangle m_rcPageSize;		// gesamter Druckbereich
	Rectangle m_rcPageBase;		// BezugsMaße (gesamtes Papier)

	Rectangle m_rcLogo;			// LogoBereich (Überschrift)
	Rectangle m_rcFirmLogos[MAX_LOGOFELD];	// FirmenLogos (unten)
	bool m_fLogos[MAX_LOGOFELD];

	unsigned short m_iHeadLine : 1;
	unsigned short m_fLogo : 1;
	unsigned short m_fRounded : 1;
	unsigned short m_fLegendOnly : 1;

// HilfsInfos
	Dimension m_Ratio;
};

#endif // !defined(_PRINTBASE_H__2F218452_8E33_4D0F_AC64_04BC9CEB45ED__INCLUDED_)
