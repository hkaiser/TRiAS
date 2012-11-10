// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 23.11.2000 22:16:57 
//
// @doc
// @module ObjTreesCache.cpp | Definition of the <c CObjTreesCache> class

#include "precomp.hxx"

#include "ObjTreesCache.h"
#include "Obj.hxx"
#include "ObjTrees.hxx"

bool CObjTreesCache::CacheHit(INT_PTR hObj)
{
	if (!m_Cache.HasObject(hObj)) {		// organisiert CacheHit, wenn vorhanden
	// Objekt ist nicht bereits geladen
		if (m_Cache.HasReachedLimit()) {
		// versuchen, was rauszuwerfen
		bool fFirst = true;
		bool fFirstRound = true;
		CObjCache::iterator itLast = m_Cache.GetLastIt();

			for (CObjCache::iterator it = itLast; /**/; it = m_Cache.AdvanceIt()) {
				if (fFirst)
					fFirst = false;			// den allerersten überspringen
				else {
					if (it == itLast) {
						if (fFirstRound)
							fFirstRound = false;
						else
							break;			// maximal zwei Runden machen
					}
				}

				if (!(*it).second.WasRecentlyUsed()) {
				// Objekt aus dem Cache rauswerfen 
				CGeoObject *pObj = m_rTrees.FGetItem((*it).second.GetONr());

					if (NULL == pObj)
						continue;		// das Objekt wird gerade im Baum eingebaut

					if (pObj -> MayRelease()) {
					// Objekt hat nichts dagegen, freigegeben zu werden
						VERIFY(m_rTrees.ReleaseItem((*it).second.GetONr()));
						m_Cache.ReleaseItem(it);
						break;		// for
					}
					else {
					// Objekt lediglich auffordern, FeatureTrees etc. freizugeben
						VERIFY(pObj -> ReleaseItems());
						(*it).second.SetRecentlyUsed (false);		// beim nächsten mal wieder versuchen
						break;		// for
					}
				} else
					(*it).second.SetRecentlyUsed (false);
			}
		} 

	// jetzt neu einfügen
		m_Cache.AddItem(hObj);
	}
	return true;
}
