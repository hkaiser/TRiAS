// @doc 
// @module DebugUtil.h | Utility functions for debugging purposes

#if !defined(_DEBUGUTIL_H__92081CBB_C828_11D2_9BA2_006008447800__INCLUDED_)
#define _DEBUGUTIL_H__92081CBB_C828_11D2_9BA2_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(_DEBUG)

///////////////////////////////////////////////////////////////////////////////
// Testen, ob ein Objekt newVal bereits im Enumerator Enum enthalten ist, dabei
// wird sowohl der vom Prädikat pred gelieferte Wert vom Typ V als Vergleichs-
// grundlage verwendet, als auch über die COM-Identität verglichen
template<class E, class pred, class V>
BOOL IsFirstOccurence (E Enum, E::target_t::enum_t newVal, pred f, V *)
{
	COM_TRY {
	E ClonedEnum;
	V cmpVal = NULL;

		THROW_FAILED_HRESULT(Enum -> Clone (ClonedEnum.ppi()));
		THROW_FAILED_HRESULT((newVal ->* f)(&cmpVal));

	E::target_t::enum_t Val;

		for (ClonedEnum -> Reset(); S_OK == ClonedEnum -> Next (1, &Val, NULL); /**/) 
		{
		// Test über COM-Identität
			if (newVal == Val) return FALSE;	// das Objekt selbst ist enthalten

		// Test über gegebenes Prädikat
		V tmpVal = NULL;

			THROW_FAILED_HRESULT((Val ->* f)(&tmpVal));
			if (cmpVal == tmpVal) return FALSE;		// eine Kopie des Objektes ist enthalten
		}

	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}

#endif // defined(_DEBUG)

#endif // !defined(_DEBUGUTIL_H__92081CBB_C828_11D2_9BA2_006008447800__INCLUDED_)
