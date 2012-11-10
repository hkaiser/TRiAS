// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.07.2000 22:04:13 
//
// @doc
// @module RENDERDB.HXX | Zeichnen eines GeoDB-Ausschnittes in einen beliebigen hDC

#if !defined(_RENDERDB_HXX__D530F861_475B_477A_B3A3_F9419E7A6CC8__INCLUDED_)
#define _RENDERDB_HXX__D530F861_475B_477A_B3A3_F9419E7A6CC8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "PrintBase.h"

///////////////////////////////////////////////////////////////////////////////
// Ausgabe in einen beliebigen DC
class CDirisDCWindow : 
	public CDCWindow 
{
private:
	DatenBasisObjekt &m_rDBO;
	Rectangle m_ClipRect;		// aktuelles ClippingRechteck

	Point m_Aspect;
	ObjContainer m_Extend;		// GeoDB-Auschnitt
	Rectangle m_ActRect;		// Ausschnitt im Zielkontext
		
protected:
	BOOL DCExpose (CDCExposeEvt);

public:
		CDirisDCWindow (RENDERGEODB *pRDB, DatenBasisObjekt &rDBO, Rectangle &rcC, Rectangle &rcClip);
		~CDirisDCWindow (void);
		
	Rectangle &ClipRect (void) { return m_ClipRect; }

	void SetAspect (Point pt) { m_Aspect = pt; }
	void SetActRect (Rectangle rc) { m_ActRect = rc; }
	void SetExtend (ObjContainer oc) { m_Extend = oc; }
};

///////////////////////////////////////////////////////////////////////////////
// Das CanvasRechteck des CDCWindows muß ggf. von 0 bis zur maximalen Koordinate
// gehen, damit der CommonVu-Blödsinn ausgeglichen werden kann
inline Rectangle MakeCDCCanvas (Rectangle &rcR)
{
	return Rectangle (rcR.Top()-rcR.Bottom(), rcR.Left(), 0, rcR.Right());
}

///////////////////////////////////////////////////////////////////////////////
// das gleiche noch mal, diesmal aber für die Druckvorschau
class CPrintPreview :
	public CDirisDCWindow,
	public CPrintBase
{
public:
	CPrintPreview(PRINTPREVIEW *pPP, DatenBasisObjekt &rDBO, Rectangle &rcC, 
				  Rectangle &rcClip, PrinterPars &rPP) :
		CDirisDCWindow(pPP -> pRenderDb, rDBO, rcC, rcClip), 
		CPrintBase(pPP -> pLayout, rDBO, pPP -> m_ptRatio),
		m_rPP(rPP)
	{
	// FormatierungsInfo setzen
		CPrintBase::SetDotsPerMM (rPP.GetDotsPerMM());		// ScalingParameter
		CPrintBase::SetAspect (rPP.GetAspectRatio());
	}
	~CPrintPreview() {}

// cross_cast functions
	HDC Handle (Service s) { return (HDC)CDirisDCWindow::Handle (s); }
	void DrawEx (DrawObject *pDO, DWORD dwData) { CDirisDCWindow::DrawEx(pDO, dwData); }
	pFont ChangeFont (pFont pF) { return CDirisDCWindow::ChangeFont(pF); }
	Rectangle CanvasRect() { return CDirisDCWindow::CanvasRect(); }

protected:
	BOOL DCExpose (CDCExposeEvt);

private:
	PrinterPars &m_rPP;
};

///////////////////////////////////////////////////////////////////////////////
// sonstige FunktionsPrototypen 
Point GetAspectRatio (HDC hDC);
Rectangle EvalCanvasRect (RECTL *pRc, DoublePair dimD);

#endif // !defined(_RENDERDB_HXX__D530F861_475B_477A_B3A3_F9419E7A6CC8__INCLUDED_)
