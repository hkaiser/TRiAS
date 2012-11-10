// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.07.2000 23:14:01 
//
// @doc
// @module DBOContext.h | Declaration of the <c CDBOContext> class

#if !defined(_DBOCONTEXT_H__C37FD5A8_463B_4A73_98E3_F6626A31DEB0__INCLUDED_)
#define _DBOCONTEXT_H__C37FD5A8_463B_4A73_98E3_F6626A31DEB0__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

extern bool PrintEFlag;

///////////////////////////////////////////////////////////////////////////////
// Zwischenspeichern der aktuellen Bildschirm-Einstellungen
class CDBOContext 
{
private:
	Window *m_pW;
	DatenBasisObjekt &m_rDBO;
	Point m_ptAspect;
	bool m_fDisable;

	ObjContainer m_oc;
	Rectangle m_rcEA;

public:
	CDBOContext (pWindow pW, DatenBasisObjekt &rDBO, Point ptAspect, bool fDisable = true) :
		m_pW(pW), m_rDBO(rDBO), m_ptAspect(ptAspect), m_fDisable(fDisable), 
		m_oc(rDBO.GetExtend()), m_rcEA(rDBO.EA())
	{
		PrintEFlag = false;             // MenuPunkt passivieren
		if (fDisable)
			pW -> Disable();
	}
	~CDBOContext (void)
	{
		m_rDBO.SetExtend(m_pW, m_oc, m_ptAspect);
		m_rDBO.SetEA(m_rcEA);
		m_rDBO.EvalMasstab (m_pW);		// Masstabskoeffizienten berechnen

		PrintEFlag = true;
		if (m_fDisable) {
			m_pW -> Enable();			// Fenster wieder zu gebrauchen
			m_pW -> SetFocus();
		}
	}
};

#endif // !defined(_DBOCONTEXT_H__C37FD5A8_463B_4A73_98E3_F6626A31DEB0__INCLUDED_)
