// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 09/11/1998 11:54:47 AM
//
// @doc
// @module TRiASDBDispIds.h | Feste Dispatch Id's

#if !defined(_TRIASDBDISPIDS_H__F7A889E5_C2EA_11D1_85CA_00600875138A__INCLUDED_)
#define _TRIASDBDISPIDS_H__F7A889E5_C2EA_11D1_85CA_00600875138A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////////////////////////
//
#define DISPID_DEFAULT				0			// default property

#define DISPID_APPLICATION			10001		// property Application
#define DISPID_PARENT				10002		// property Parent

///////////////////////////////////////////////////////////////////////////////
// Ein Objekt (IDispatch) welches in einem VariantProperty gespeichert ist, kann
// eine Funktion [id(DISPID_PROPERTYREFRESH)] HRESULT Refresh(); unterstützen.
#define DISPID_PROPERTYREFRESH		10003		// HRESULT Refresh();
#define DISPID_PROPERTYSHUTDOWN		10008		// HRESULT ShutDown();

///////////////////////////////////////////////////////////////////////////////
// ITRiASLockFeature
#define DISPID_LOCKEDFEATURE		10004		// ITRiASLockFeature::Feature
#define DISPID_LOCKEDNAME			10005		// ITRiASLockFeature::Name
#define DISPID_LOCKEDDESCRIPTION	10006		// ITRiASLockFeature::Description
#define DISPID_LOCKEDISRO			10007		// ITRiASLockFeature::IsRO

// last used: 10008

#endif // !defined(_TRIASDBDISPIDS_H__F7A889E5_C2EA_11D1_85CA_00600875138A__INCLUDED_)
