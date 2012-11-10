// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 10.07.2000 11:35:13 
//
// @doc
// @module AutoAssignColors.h | Declaration of the <c CAutoAssignColors> class

#if !defined(_AUTOASSIGNCOLORS_H__D4519092_34E7_4AEA_B9AF_3F57B4B83D7F__INCLUDED_)
#define _AUTOASSIGNCOLORS_H__D4519092_34E7_4AEA_B9AF_3F57B4B83D7F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "AutoColors.def"

///////////////////////////////////////////////////////////////////////////////
// Automatisches Zuweisen einer Farbe organisieren
class CAutoAssignColors 
{
public:
	CAutoAssignColors() : m_iActColor(-1) {}
	~CAutoAssignColors() {}

	void Reset() { m_iActColor = -1; }
	COLORREF GetNextColor() 
	{ 
		if (++m_iActColor >= _countof(g_Colors))
			m_iActColor = 0;

		_ASSERTE(0 <= m_iActColor && m_iActColor < _countof(g_Colors));
		return RGB(g_Colors[m_iActColor].rgbRed, g_Colors[m_iActColor].rgbGreen, g_Colors[m_iActColor].rgbBlue); 
	}

private:
	int m_iActColor;
};

#endif // !defined(_AUTOASSIGNCOLORS_H__D4519092_34E7_4AEA_B9AF_3F57B4B83D7F__INCLUDED_)
