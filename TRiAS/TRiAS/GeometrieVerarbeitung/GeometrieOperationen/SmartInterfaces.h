// für ObjektOperationen benötigte SmartInterfaces
// File: SmartInterfaces.h
// W. Mörtl


#ifndef _SMARTINTERFACES_H_
#define _SMARTINTERFACES_H_



DEFINE_GUID(CLSID_DataTransferObject, 0xCF883AF6L, 0x553F, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);


#include <TRiASHelper.h>	// IProgressIndicator2

#include <IPropSeq.hxx>		// IPropertyActionSequence
#include <SrChoice.h>		// CLSID_PropertyChoice
#include <propguid.h>		// CLSID_ModifyIdent
#include <ibscript.hxx>		// IExtendBScript
#include <bscrguid.h>		// CLSID_MacroScriptExtension
#include <triastlb.h>		// DGeoObjects
#include <iGeoObjs.h>		// IID_IQueryGeoObjects
#include <ScriptPropActGuid.h>		// CLSID_ScriptPropAct
#include <ObjekteVereinigenGuid.h>	// CLSID_ObjekteVereinigen
#include <imaschen.h>		// CLSID_ExtLinienVerfolgung
#include "objgguid.h"		// CLSID_ObjektGeometrie, IID_IInitObjektGeometrie ...
#include "operguid.h"		// CLSID_GeometrieOperationen
#include "reinguid.h"		// CLSID_GeometrieBereinigung, IID_IExtendGeoRein


///////////////////////////////////////////////////////////////////////////////////////////////
// benötigte SmartInterfaces
// durch das Makro DefineSmartInterface() wird z.B. für das Interface IEnumObjectsByNumber
// die Wraper-Klasse WEnumObjectsByNumber erzeugt
DefineSmartInterface (ConnectionPointContainer);	
DefineSmartInterface (ConnectionPoint);			// WConnectionPoint
DefineSmartInterface (ProgressIndicator2);		// WProgressIndicator2
DefineSmartInterface (EnumObjectsByNumber);		// WEnumObjectsByNumber
DefineSmartInterface (EnumLONG);				// WEnumLONG
DefineSmartInterface (PersistStream);			// WPersistStream
DefineSmartInterface (DataObject);				// WDataObject
DefineSmartInterface (QueryGeoObjects);			// WQueryGeoObjects
DefineSmartInterface2 (DGeoObjects, IID_DGeoObjects);	// WDGeoObjects
DefineSmartInterface (QueryEnumLONG);			// WQueryEnumLONG
DefineSmartInterface (ExtendBScript);			// WExtendBScript
DefineSmartInterface (ExtLinienVerfolgung);		// WExtLinienVerfolgung
DefineSmartInterface (Storage);					// WStorage
DefineSmartInterface (PropertyActionSequence);	// WPropertyActionSequence
DefineSmartInterface (PersistStreamInit);		// WPersistStreamInit
DefineSmartInterface (Stream);					// WStream
DefineSmartInterface (PropertyAction);			// WPropertyAction
DefineSmartInterface (PropertyAction2);			// WPropertyAction2
DefineSmartInterface (ClassProperty);			// WClassProperty
DefineSmartInterface (PropertyInfo);			// WPropertyInfo
#if _TRiAS_VER >= 0x0300
DefineSmartInterface (ExtLinienVerfolgungEx);	// WExtLinienVerfolgung
#endif // _TRiAS_VER >= 0x0300
DefineSmartInterface (InitObjektGeometrie);		// WInitObjektGeometrie
DefineSmartInterface (ObjektGeometrie);			// WObjektGeometrie
DefineSmartInterface (GetGeoOperatOptions);		// WGetGeoOperatOptions
DefineSmartInterface (SetGeoOperatOptionsTarget);	// WSetGeoOperatOptionsTarget
DefineSmartInterface (ExtendGeoRein);			// WExtendGeoRein
DefineSmartInterface (Moniker);					// WMoniker
DefineSmartInterface (BindCtx);					// WBindCtx

#endif //_SMARTINTERFACES_H_
