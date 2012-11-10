// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.10.2000 13:26:05 
//
// @doc
// @module ObjPropImageList.h | Declaration of the <c CObjPropImageList> class

#if !defined(_OBJPROPIMAGELIST_H__A7DF480D_EA51_492D_A59C_53DFB25DB2DF__INCLUDED_)
#define _OBJPROPIMAGELIST_H__A7DF480D_EA51_492D_A59C_53DFB25DB2DF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// Indizies in Imagelist (IDB_OBJPROPTYPES)
#define IMG_FOLDER		1
#define IMG_OPENFOLDER	2
#define IMG_TEXTPROP	3
#define IMG_BOOLPROP	4
#define IMG_DATUMPROP	8
#define IMG_INTEGERPROP	9
#define IMG_UNKNOWNPROP	10
#define IMG_DOUBLEPROP	11

///////////////////////////////////////////////////////////////////////////////
// CObjPropImageList
class CObjPropImageList :
	public CImageList
{
public:
	CObjPropImageList() {}
	~CObjPropImageList() {}

	int GetImageIndex (DWORD dwFlags);
	
protected:

private:
};

#endif // !defined(_OBJPROPIMAGELIST_H__A7DF480D_EA51_492D_A59C_53DFB25DB2DF__INCLUDED_)
