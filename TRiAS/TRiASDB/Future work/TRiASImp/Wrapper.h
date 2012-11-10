///////////////////////////////////////////////////////////////////////////
// @doc
// @module Wrapper.h | Definition von diversen Smartinterface's

#if !defined(_WRAPPER_H__AD0D7077_39B0_11d1_96B9_00A024D6F582__INCLUDED_)
#define _WRAPPER_H__AD0D7077_39B0_11d1_96B9_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TRiASDB.h"
#include <iobjman.h>		// ObjektManagement
#include <ictf.h>			// CoordTransform

#include <TRiAStlb.h>		// TriasXtensionSite
#include <Xtension.h>
#include <IXtensn.hxx>		// ITriasXtension...

#include <Helper.h>

DefineSmartInterface(TRiASDatabase);		// WTRiASDatabase
DefineSmartInterface(TRiASProject);			// WTRiASProject
DefineSmartInterface(TRiASProjects);		// WTRiASProjects
DefineSmartInterface(TRiASConnection);		// WTRiASConnection
DefineSmartInterface(TRiASConnections);		// WTRiASConnections
DefineSmartInterface(TRiASView);			// WTRiASView
DefineSmartInterface(TRiASViews);			// WTRiASViews

DefineSmartInterface(TRiASProperty);		// WTRiASProperty
DefineSmartInterface(TRiASProperties);		// WTRiASProperties
DefineSmartInterface(TRiASPropertySupport);	// WTRiASPropertySupport

DefineSmartInterface(Stream);				// WStream
DefineSmartInterface(Storage);				// WStorage
DefineSmartInterface(PersistStorage);		// WPersistStorage
DefineSmartInterface(EnumUnknown);			// WEnumUnknown

DefineSmartInterface(ObjectManagement);		// WObjectManagement
DefineSmartInterface(CoordTransform);		// WCoordTransform

DefineSmartInterface(CatInformation);
DefineSmartInterface(EnumGUID);

DefineSmartInterface(ParseStringPairs);

// TRiAS - eigene Interface's -------------------------------------------------
DefineSmartInterface(TriasXtensionSite);

DefineSmartInterface(TriasXtension);
DefineSmartInterface(TriasXtension2);
DefineSmartInterface(ImportGeoData);

#endif // !defined(_WRAPPER_H__AD0D7077_39B0_11d1_96B9_00A024D6F582__INCLUDED_)
