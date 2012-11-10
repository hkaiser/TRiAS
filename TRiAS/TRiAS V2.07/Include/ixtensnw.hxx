// Deklaration diverser SmartInterfaces ---------------------------------------
// File: IXTENSNW.HXX

#if !defined(_IXTENSNW_HXX)
#define _IXTENSNW_HXX

#if defined(WIN32)		// nur für 32 Bit interessant

#include <xtsnguid.h>
#include <oprpguid.h>

#include <ixtensn.hxx>		// InterfaceDeklarationen
#include <ipropseq.hxx>

#include <smartif.h>		// SmartInterface template importieren

// Eigentliche SmartInterfaces ------------------------------------------------

// TRiAS - eigene Interface's -------------------------------------------------
DefineSmartInterface(TriasXtensionSite);

DefineSmartInterface(TriasXtension);
DefineSmartInterface(TriasXtension2);
DefineSmartInterface(ImportGeoData);

DefineSmartInterface(EnumObjProps);
DefineSmartInterface(EnumClassProps);

DefineSmartInterface(ObjectProperty);
DefineSmartInterface(ObjectProperty2);
DefineSmartInterface(PropertyTemplate);
DefineSmartInterface(ClassProperty);
DefineSmartInterface(PropertyAction);
DefineSmartInterface(PropertyActionSequence);
//DefineSmartInterface(EnumLONG);
DefineSmartInterface(ObjectProps);

// DefineSmartInterface(IProgressIndicator);

#endif // WIN32

#endif // _IXTENSNW_HXX
