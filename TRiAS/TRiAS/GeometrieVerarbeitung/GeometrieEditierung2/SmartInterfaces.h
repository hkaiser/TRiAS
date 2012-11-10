// Deklarationen: für Geometrie-Editierung benötigte SmartInterfaces
// File: SmartInterfaces.h
// W. Mörtl


#ifndef _SMARTINTERFACES_H_
#define _SMARTINTERFACES_H_


#include <igeoobjs.h>	// IQueryGeoObjects
#include <TRiASHelper.h>// IProgressIndicator2


///////////////////////////////////////////////////////////////////////////////////////////////
// benötigte SmartInterfaces
DefineSmartInterface (TriasXtensionSite);				// WTriasXtensionSite
DefineSmartInterface (TRiASNotificationSink);			// WTRiASNotificationSink
DefineSmartInterface (TRiASSysNotificationSink);		// WTRiASSysNotificationSink
DefineSmartInterface (Dispatch);						// WDispatch
DefineSmartInterface (ConnectionPointContainer);		// WConnectionPointContainer
DefineSmartInterface (ConnectionPoint);					// WConnectionPoint
DefineSmartInterface (ProgressIndicator2);				// WProgressIndicator2
DefineSmartInterface (DataObject);						// WDataObject
DefineSmartInterface (DragDropAction);					// WDragDropAction
DefineSmartInterface (DropSource);						// WDropSource
DefineSmartInterface (Stream);							// WStream
DefineSmartInterface (PersistStream);					// WPersistStream
DefineSmartInterface (TRiASDropTarget);					// WTRiASDropTarget
DefineSmartInterface (ExtendBScript);					// WExtendBScript
DefineSmartInterface (MenuHandling);					// WMenuHandling
DefineSmartInterface2 (DGeoObject, IID_DGeoObject);		// WDGeoObject
DefineSmartInterface2 (DGeoObjects, IID_DGeoObjects);	// WDGeoObjects
DefineSmartInterface (EnumUnknown);						// WEnumUnknown
DefineSmartInterface (EnumLONG);						// WEnumLONG
DefineSmartInterface (EnumObjectsByNumber);				// WEnumObjectsByNumber
DefineSmartInterface (QueryEnumLONG);					// WQueryEnumLONG
DefineSmartInterface (QueryGeoObjects);					// WQueryGeoObjects
DefineSmartInterface (ExtendGeoRein);					// WExtendGeoRein
DefineSmartInterface (ExtendObjOper);					// WExtendObjOper
DefineSmartInterface (InitObjektGeometrie);				// WInitObjektGeometrie
DefineSmartInterface (ObjektGeometrie);					// WObjektGeometrie
DefineSmartInterface (EnumObjektGeometrie);				// WEnumObjektGeometrie
DefineSmartInterface (TopicalObjects);					// WTopicalObjects
DefineSmartInterface (EditOperation);					// WEditOperation
DefineSmartInterface (EditExtensionSite);				// WEditExtensionSite
DefineSmartInterface (ModifyClassSite);					// WModifyClassSite
DefineSmartInterface (ModifyOperation);					// WModifyOperation
DefineSmartInterface (DragObject);						// WDragObject
DefineSmartInterface (RestrictLine);					// WRestrictLine
DefineSmartInterface (RestrictCursor);					// WRestrictCursor

#endif //_SMARTINTERFACES_H_
