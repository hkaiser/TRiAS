#if !defined(_DEFAULTWRAPPERS_H_B8DB8D00_FD62_11d2_9955_0060085FC1CE)
#define _DEFAULTWRAPPERS_H_B8DB8D00_FD62_11d2_9955_0060085FC1CE

#if !defined(_SMARTIF_H__F5802CB5_D772_11D1_85F2_00600875138A__INCLUDED_)
#error "You must include com/Smartif.h first
#endif

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

DefineSmartInterface(Dispatch)
DefineSmartInterface(ErrorInfo)

DefineSmartInterface(OleObject);			// WOleObject
DefineSmartInterface(OleClientSite)			// WOleClientSite
DefineSmartInterface(ObjectWithSite)		// WObjectWithSite

DefineSmartInterface(Moniker)				// WMoniker
DefineSmartInterface(BindCtx);				// WBindCtx

DefineSmartInterface(Malloc)
DefineSmartInterface(MallocSpy)

DefineSmartInterface(Stream)
DefineSmartInterface(Persist)				// 
DefineSmartInterface(PersistStream)			// 
DefineSmartInterface(PersistStreamInit);		// WPersistStreamInit

DefineSmartInterface(PropertyPage)
DefineSmartInterface(PropertyPageSite)
DefineSmartInterface(SpecifyPropertyPages)

#endif
