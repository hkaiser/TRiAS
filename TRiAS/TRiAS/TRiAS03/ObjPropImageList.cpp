// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.10.2000 13:29:39 
//
// @doc
// @module ObjPropImageList.cpp | Definition of the <c CObjPropImageList> class

#include "trias03p.hxx"
#include "trias03.h"

#include <PropName.hxx>
#include <ObjPropImageList.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Index im ImageList aus Flags herausfinden
int CObjPropImageList::GetImageIndex (DWORD dwFlags)
{
	if (dwFlags & PROPCAPS_OBJPROPTYPE_INTEGER)
		return IMG_INTEGERPROP;
	if (dwFlags & PROPCAPS_OBJPROPTYPE_DOUBLE)
		return IMG_DOUBLEPROP;
	if (dwFlags & PROPCAPS_OBJPROPTYPE_BOOL)
		return IMG_BOOLPROP;
	if (dwFlags & PROPCAPS_OBJPROPTYPE_DATE)
		return IMG_DATUMPROP;

	return IMG_TEXTPROP;
}

