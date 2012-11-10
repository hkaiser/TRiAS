// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 17.10.2000 17:09:07 
//
// @doc
// @module WindowPosEvent.cpp | Definition of the <c CWindowPosEvent> class

#include "trias03p.hxx"

#include <WindowPosEvent.h>

void WindowPosEvt::GetWindowSize (Dimension &dim)
{
	dim.Width() = ((WINDOWPOS *)lParam) -> cx;
	dim.Height() = ((WINDOWPOS *)lParam) -> cy;
}

void WindowPosEvt::SetWindowSize (Dimension dim)
{
	((WINDOWPOS *)lParam) -> cx = dim.Width();
	((WINDOWPOS *)lParam) -> cy = dim.Height();
}

BOOL WindowPosEvt::SizeIsChanging (void)
{
	return (((WINDOWPOS *)lParam) -> flags & SWP_NOSIZE) ? FALSE : TRUE;
}

