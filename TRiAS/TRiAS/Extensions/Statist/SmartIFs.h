// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.01.2001 11:13:43 
//
// @doc
// @module SmartIFs.h | Declaration of the Smartinterfaces for Statist

#if !defined(_SMARTIFS_H__86ACDD94_9337_4181_AD66_C1FECE48E2F6__INCLUDED_)
#define _SMARTIFS_H__86ACDD94_9337_4181_AD66_C1FECE48E2F6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <igeometr.hxx>
#include <ipropseq.hxx>
#include <dtoolbar.h>

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ConnectionPointContainer);
DefineSmartInterface(DataObject);
DefineSmartInterface(Stream);
DefineSmartInterface(PersistStream);
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(EnumGUID);
DefineSmartInterface(CatInformation);
DefineSmartInterface(ServiceProvider);
DefineSmartInterface(OleObject);

DefineSmartInterface(TRiASSimpleStatistics);

DefineSmartInterface(InitObjektGeometrie);
DefineSmartInterface(ObjektGeometrie);
DefineSmartInterface(ExtendTopRel2);

DefineSmartInterface(TriasXtensionSite);

DefineSmartInterface(TRiASUnitIDs);
DefineSmartInterface(TRiASUnitsOfMeasure);

DefineSmartInterface(ObjectProperty);
DefineSmartInterface(PropertyInfo);
DefineSmartInterface(ObjectProps);
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(EnumObjProps);
DefineSmartInterface(PropertyTemplate);
DefineSmartInterface(InitInnerObject);
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(PropertyAction);

DefineSmartInterface(PopupTree);
DefineSmartInterface(GenericStatistics);
DefineSmartInterface(ValueProvider);
DefineSmartInterface(ValueProviderCallback);

// Toolbars und docking window support
DefineSmartInterface(ManageTabWindows);
DefineSmartInterface(TRiASBarContainer);
DefineSmartInterface(TRiASBar);
DefineSmartInterface(TRiASToolBar);
DefineSmartInterface(TRiASUIOwner);

// GUIDs sollten gecached werden
DefineEnumerator2(GUID, IID_IEnumGUID);

#endif // !defined(_SMARTIFS_H__86ACDD94_9337_4181_AD66_C1FECE48E2F6__INCLUDED_)
