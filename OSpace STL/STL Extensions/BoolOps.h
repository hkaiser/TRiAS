///////////////////////////////////////////////////////////////////////////
// @doc 
// @module BoolOps.h | STL Algorithmen für logische Auswertung eines Prädikates
// über allen Elementen eines Containers

#if !defined(_BOOLOPS_H__E2339647_A3F9_11D2_9592_006008447800__INCLUDED_)
#define _BOOLOPS_H__E2339647_A3F9_11D2_9592_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// boolop_or
// Liefert true, wenn das Prädikat für wenigstens ein Element des Containers
// true geliefert hat
template<class ForwardIterator, class UnaryOperation>
inline bool boolop_or (ForwardIterator first, ForwardIterator last, UnaryOperation f)
{
	while (first != last) {
		if (f(*first))
			return true;
		++first;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
// boolop_and
// Liefert true, wenn das Prädikat für alle Elemente des Containers
// true geliefert hat
template<class ForwardIterator, class UnaryOperation>
inline bool boolop_and (ForwardIterator first, ForwardIterator last, UnaryOperation f)
{
	while (first != last) {
		if (!f(*first))
			return false;
		++first;
	}
	return true;
}

#endif // !defined(_BOOLOPS_H__E2339647_A3F9_11D2_9592_006008447800__INCLUDED_)
