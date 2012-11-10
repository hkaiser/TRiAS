// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH, NL Potsdam, All rights reserved
// Created: 29.01.2002 09:25:08 
//
// @doc
// @module ClipListe.h | Declaration of the <c CClipListe> class

#if !defined(_CLIPLISTE_H__64A14B43_E427_42EB_8A91_2CB483496669__INCLUDED_)
#define _CLIPLISTE_H__64A14B43_E427_42EB_8A91_2CB483496669__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <ospace/std/list>
#include <ospace/stlex/pointainer.h>

namespace trias_wmgeometry {

///////////////////////////////////////////////////////////////////////////////
// Liste von Schnittobjekten
template <typename KoOrdT>
class WMClipListe :
	public pointainer<list<WMObjekt<KoOrdT> *> >
{
private:
	typedef pointainer<list<WMObjekt<KoOrdT> *> > base_t;

public:
	void insert (WMPunkt<KoOrdT> const &p)
	{
		base_t::push_back(new WMPunkt<KoOrdT>(p));
	}
	void insert (WMKante<KoOrdT> const &k)
	{
		base_t::push_back(new WMKante<KoOrdT>(k));
	}
	void insert (WMFlaeche<KoOrdT> const &f)
	{
		base_t::push_back(new WMFlaeche<KoOrdT>(f));
	}
};

} // namespace trias_wmgeometry

#endif // !defined(_CLIPLISTE_H__64A14B43_E427_42EB_8A91_2CB483496669__INCLUDED_)
