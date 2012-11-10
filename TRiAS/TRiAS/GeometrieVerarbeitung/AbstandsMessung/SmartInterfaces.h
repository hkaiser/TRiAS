// für Abstands-Erweiterung benötigte SmartInterfaces
// File: SmartInterfaces.h
// W. Mörtl


#ifndef _SMARTINTERFACES_H_
#define _SMARTINTERFACES_H_


#include "objgguid.h"	// IID_IInitObjektGeometrie
#include "buffguid.h"	// CLSID_BufferExtension, IID_IExtendBuffer


///////////////////////////////////////////////////////////////////////////////////////////////
// benötigte SmartInterfaces
DefineSmartInterface (EnumLONG);			// WEnumLONG
//DefineSmartInterface (InitObjektGeometrie);	// WInitObjektGeometrie
DefineSmartInterface (ObjektGeometrie);		// WObjektGeometrie
DefineSmartInterface (ExtendBuffer);		// WExtendBuffer

#endif //_SMARTINTERFACES_H_



