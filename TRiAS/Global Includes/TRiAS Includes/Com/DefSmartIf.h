#if !defined(_DEFAULTWRAPPERS_H_B8DB8D00_FD62_11d2_9955_0060085FC1CE)
#define _DEFAULTWRAPPERS_H_B8DB8D00_FD62_11d2_9955_0060085FC1CE

#if !defined(_SMARTIF_H__F5802CB5_D772_11D1_85F2_00600875138A__INCLUDED_)
#error "You must include com/Smartif.h first
#endif

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

DefineSmartInterface(Dispatch)				// WDispatch
DefineSmartInterface(ErrorInfo)				// WErrorInfo

DefineSmartInterface(Font)					// WFont
DefineSmartInterface(FontDisp)				// WFontDisp

DefineSmartInterface(OleObject);			// WOleObject
DefineSmartInterface(OleClientSite)			// WOleClientSite
DefineSmartInterface(ObjectWithSite)		// WObjectWithSite

////////////////////////////////////////////////////////////////////////
// Moniker & Co.
DefineSmartInterface(Moniker)				// WMoniker
DefineSmartInterface(BindCtx);				// WBindCtx

////////////////////////////////////////////////////////////////////////
// Malloc & Co.
DefineSmartInterface(Malloc)				// WMalloc
DefineSmartInterface(MallocSpy)				// WMallocSpy

////////////////////////////////////////////////////////////////////////
// Storage, Stream & Co.
DefineSmartInterface(Storage)				// WStorage
DefineSmartInterface(SequentialStream)		// WSequentialStream
DefineSmartInterface(Stream)				// WStream

////////////////////////////////////////////////////////////////////////
// IPersist & Co.
DefineSmartInterface(Persist)				// WPersist
DefineSmartInterface(PersistStorage)		// WPersistStorage
DefineSmartInterface(PersistFile)			// WPersistFile
DefineSmartInterface(PersistStream)			// WPersistStream
DefineSmartInterface(PersistStreamInit)		// WPersistStreamInit
DefineSmartInterface(PersistMoniker)		// WPersistMoniker

////////////////////////////////////////////////////////////////////////
// Propertypages
DefineSmartInterface(PropertyPage)			// WPropertyPage
DefineSmartInterface(PropertyPageSite)		// WPropertyPageSite
DefineSmartInterface(SpecifyPropertyPages)	// WSpecifyPropertyPages

////////////////////////////////////////////////////////////////////////
// Component-Categories
DefineSmartInterface(CatRegister)
DefineSmartInterface(CatInformation)

////////////////////////////////////////////////////////////////////////
// XML-Dokument (erfordert msxml.dll!)
DefineSmartInterface(XMLElement)
DefineSmartInterface(XMLDocument)
DefineSmartInterface(XMLElementCollection)
DefineSmartInterface(XMLError)
//DefineSmartInterface(XMLElementNotificationSink)

////////////////////////////////////////////////////////////////////////
// grundlegende IEnumXXX entspr. SDK
DefineSmartInterface(EnumUnknown)			// WEnumUnknown
DefineSmartInterface(EnumString)			// WEnumString
DefineSmartInterface(EnumSTATSTG)			// WEnumSTATSTG
DefineSmartInterface(EnumSTATDATA)			// WEnumSTATDATA
DefineSmartInterface(EnumOLEVERB)			// WEnumOLEVERB
DefineSmartInterface(EnumMoniker)			// WEnumMoniker
DefineSmartInterface(EnumFORMATETC)			// WEnumFORMATETC
DefineSmartInterface(EnumVARIANT)			// WEnumVARIANT
DefineSmartInterface(EnumCLSID)				// WEnumCLSID

#endif
