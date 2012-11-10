// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.10.2000 17:08:03 
//
// @doc
// @module WindowPosEvent.h | Declaration of the <c CWindowPosEvent> class

#if !defined(_WINDOWPOSEVENT_H__4A47D9D6_A05A_424D_B084_F02CAC84CEA4__INCLUDED_)
#define _WINDOWPOSEVENT_H__4A47D9D6_A05A_424D_B084_F02CAC84CEA4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

class _TRIAS03_ENTRY WindowPosEvt : 
	public Event 
{
public:
	void GetWindowSize (Dimension &);
	void SetWindowSize (Dimension);
	BOOL SizeIsChanging (void);
};

#endif // !defined(_WINDOWPOSEVENT_H__4A47D9D6_A05A_424D_B084_F02CAC84CEA4__INCLUDED_)
