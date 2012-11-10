// $Header: $
// Copyright© 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 10/20/1998 10:41:44 PM
//
// @doc
// @module PersistEnum.h | Wrapper-Header für Speichern/Laden von Elementen einer
// Collection

#if !defined(_PERSISTENUM_H__21005235_6792_11D2_9EDE_006008447800__INCLUDED_)
#define _PERSISTENUM_H__21005235_6792_11D2_9EDE_006008447800__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#if defined(_USE_PROPERTYSTORAGE)
#include <Com/PersistEnumPropStream.h>		// Speichern mit IPropertyStorage/IStream
#include <Com/PersistEnumPropStg.h>		// Speichern mit IPropertyStorage/IStorage
#else
#include <Com/PersistEnum.h>			// direktes Speichern in einem Stream
#endif // defined(_USE_PROPERTYSTORAGE)

#endif // !defined(_PERSISTENUM_H__21005235_6792_11D2_9EDE_006008447800__INCLUDED_)
