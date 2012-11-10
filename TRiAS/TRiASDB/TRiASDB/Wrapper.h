///////////////////////////////////////////////////////////////////////////
// @doc
// @module Wrapper.h | Definition von diversen Smartinterface's

#if !defined(_WRAPPER_H__AD0D7077_39B0_11d1_96B9_00A024D6F582__INCLUDED_)
#define _WRAPPER_H__AD0D7077_39B0_11d1_96B9_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <iobjman.h>		// ObjektManagement

#define ___DGMPoint_INTERFACE_DEFINED__
#define ___DGMPoints_INTERFACE_DEFINED__
#include <ictf.h>			// CoordTransform

DefineSmartInterface(TRiASDatabase);		// WTRiASDatabase
DefineSmartInterface(TRiASProject);			// WTRiASProject
DefineSmartInterface(TRiASProjects);		// WTRiASProjects
DefineSmartInterface(TRiASConnection);		// WTRiASConnection
DefineSmartInterface(TRiASConnections);		// WTRiASConnections
DefineSmartInterface(TRiASView);			// WTRiASView
DefineSmartInterface(TRiASViews);			// WTRiASViews
DefineSmartInterface(TRiASObject);			// WTRiASObject
DefineSmartInterface(TRiASObjects);			// WTRiASObjects
DefineSmartInterface(TRiASObjectsCollection);	// WTRiASObjectsCollection
DefineSmartInterface(TRiASSimpleObject);	// WTRiASSimpleObject
DefineSmartInterface(TRiASFeature);			// WTRiASFeature
DefineSmartInterface(TRiASFeatures);		// WTRiASFeatures
DefineSmartInterface(TRiASConnectionFilters);	// WTRiASConnectionFilters
DefineSmartInterface(TRiASConnectionFilter);	// WTRiASConnectionFilter

DefineSmartInterface(TRiASProperty);		// WTRiASProperty
DefineSmartInterface(TRiASProperties);		// WTRiASProperties
DefineSmartInterface(TRiASPropertySupport);	// WTRiASPropertySupport
DefineSmartInterface(TRiASPropertyCallback);	// WTRiASPropertyTRiASPropertyCallback
DefineSmartInterface(TRiASPropertyBase);	// WTRiASPropertyBase

DefineSmartInterface(Stream);				// WStream
DefineSmartInterface(Storage);				// WStorage
DefineSmartInterface(PersistStorage);		// WPersistStorage
DefineSmartInterface(PersistStream);		// WPersistStream
DefineSmartInterface(PersistStreamInit);	// WPersistStreamInit
DefineSmartInterface(EnumUnknown);			// WEnumUnknown
DefineSmartInterface(EnumString);			// WEnumString
DefineSmartInterface(EnumVARIANT);			// WEnumVARIANT

DefineSmartInterface(ObjectManagement);		// WObjectManagement
DefineSmartInterface(CoordTransform);		// WCoordTransform

DefineSmartInterface(Dispatch);				// WDispatch
DefineSmartInterface(Moniker);				// WMoniker
DefineSmartInterface(OleObject);			// WOleObject
DefineSmartInterface(BindCtx);				// WBindCtx

#endif // !defined(_WRAPPER_H__AD0D7077_39B0_11d1_96B9_00A024D6F582__INCLUDED_)
