// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 08/30/1998 01:46:43 PM
//
// @doc
// @module AniWaitCursor.h | Wrapperklasse, um animierte TRiAS-Cursoren anzuzeigen

#if !defined(_ANIWAITCURSOR_H__C49BECB6_3FE3_11D2_9EB8_006008447800__INCLUDED_)
#define _ANIWAITCURSOR_H__C49BECB6_3FE3_11D2_9EB8_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

enum ANICURSOR {
	ANICURSOR_WAIT = 1,
	ANICURSOR_LOAD = 2,
	ANICURSOR_SAVE = 3,
	ANICURSOR_PRINT = 4,
	ANICURSOR_MAX = 4,
};

class CAniWaitCursor
{
private:
	ANICURSOR m_rgType;

public:
	CAniWaitCursor (ANICURSOR rgType = ANICURSOR_WAIT) : m_rgType(rgType)
		{ AfxGetApp()->DoWaitCursor(rgType); }
	~CAniWaitCursor () { AfxGetApp()->DoWaitCursor(-m_rgType); }

// operations
	void Restore() { AfxGetApp()->DoWaitCursor(0); }
};

#endif // !defined(_ANIWAITCURSOR_H__C49BECB6_3FE3_11D2_9EB8_006008447800__INCLUDED_)
