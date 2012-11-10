// für Topologische Relationen benötigte SmartInterfaces
// File: SmartInterfaces.h
// W. Mörtl


#ifndef _SMARTINTERFACES_H_
#define _SMARTINTERFACES_H_


#include <triastlb.h>			// IProgressIndicator2
#include "TRelGuid.h"	// CLSID_Topologie
#include "ReinGuid.h"	// CLSID_GeometrieBereinigung, IID_IExtendGeoRein



///////////////////////////////////////////////////////////////////////////////////////////////
// benötigte SmartInterfaces
// durch das Makro DefineSmartInterface() wird z.B. für das Interface IExtendGeoRein
// die Wraper-Klasse WExtendGeoRein erzeugt
DefineSmartInterface (TriasXtensionSite);			// WTriasXtensionSite
DefineSmartInterface (ConnectionPointContainer);	// WConnectionPointContainer
DefineSmartInterface (ConnectionPoint);				// WConnectionPoint
DefineSmartInterface(ProgressIndicator);			// WProgressIndicator
DefineSmartInterface(ProgressIndicator2);			// WProgressIndicator2
//DefineSmartInterface(PropertySequenceService);		// WPropertySequenceService
DefineSmartInterface (EnumLONG);					// WEnumLONG
DefineSmartInterface (DataObject);					// WDataObject
DefineSmartInterface (ExtendGeoRein);				// WExtendGeoRein
DefineSmartInterface (ObjektGeometrie);				// WObjektGeometrie

#endif //_SMARTINTERFACES_H_
