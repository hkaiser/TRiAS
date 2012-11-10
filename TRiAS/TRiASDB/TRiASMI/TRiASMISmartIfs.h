// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 18.01.2001 12:55:34 
//
// @doc
// @module TRiASMISmartIfs.h | Declaration of smart interface classes

#if !defined(_TRIASMISMARTIFS_H__16173F21_FF93_45F0_89B3_CC117D2C8664__INCLUDED_)
#define _TRIASMISMARTIFS_H__16173F21_FF93_45F0_89B3_CC117D2C8664__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASConnection);
DefineSmartInterface(TRiASDatabase);
DefineSmartInterface(TRiASObject);
DefineSmartInterface(TRiASObjects);
DefineSmartInterface(TRiASObjectsCollection);
DefineSmartInterface(TRiASFeature);
DefineSmartInterface(TRiASFeatures);
DefineSmartInterface(TRiASObjectHandleMap);
DefineSmartInterface(TRiASPropertyMapHandler);
DefineSmartInterface(TRiASPropertyBase);
DefineSmartInterface(TRiASProperties);
DefineSmartInterface(TRiASProperty);
DefineSmartInterface(TRiASPropertyCallback);
DefineSmartInterface(TRiASSearchObjects);

// TRiASCS
DefineSmartInterface(TRiASCS);
DefineSmartInterface(TRiASCSPCS);
DefineSmartInterface(TRiASCSGCS);
DefineSmartInterface(TRiASCSTransform);
DefineSmartInterface(TRiASCSDatumTransformation);
DefineSmartInterface(TRiASTransformGeometry);
DefineSmartInterface(TRiASCSStorageService);

// TDBGeo
DefineSmartInterface(TRiASSimpleRectangle);
DefineSmartInterface(TRiASCloneGeometry);

// TRiASMDS
DefineSmartInterface(TRiASMDSMap);
DefineSmartInterface(TRiASMDSStringColl);

// System
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(Dispatch);
DefineSmartInterface(Moniker);
DefineSmartInterface(EnumVARIANT);
DefineSmartInterface(ObjectWithSite);

#endif // !defined(_TRIASMISMARTIFS_H__16173F21_FF93_45F0_89B3_CC117D2C8664__INCLUDED_)
