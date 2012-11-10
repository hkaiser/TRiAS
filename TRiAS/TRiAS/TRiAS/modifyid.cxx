// Umklassifizieren aller Objekte verschiedener Objektklassen -----------------
// File: MODIFYID.CXX

#include "triaspre.hxx"

#if !defined(_USE_XML_GEOCOMPONENTS)
				
#include "triasres.h"

#include <funcs03.h>
#include <ipropseq.hxx>
#include <selidprp.h>
#include <modidprp.h>

#include <DstObWnd.h>

#include <initguid.h>
#include <ObjekteDoppelnGuid.h>

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#pragma optimize ("", off)

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ProgressIndicator);

///////////////////////////////////////////////////////////////////////////////
// Objekte eines Idents umklassifizieren 
static const CLSID *cbModIdClsIds[] = {
	&CLSID_SelectIdentObjTyp,
	&CLSID_ModifyIdent,
};
#if !defined(_TRIAS_OLDIMPLEMTATION1)
static VARIANT *pvModIdData[] = {
	NULL,
	NULL,
};
#endif // _TRIAS_OLDIMPLEMTATION1
static CALPCLSID calModIdClsIds = {
	sizeof(cbModIdClsIds)/sizeof(cbModIdClsIds[0]),
	cbModIdClsIds,
	NULL,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	const_cast<const VARIANT **>(pvModIdData),
#endif // _TRIAS_OLDIMPLEMTATION1
};

bool IrisWind::doModIdents (void)
{
	COM_TRY {
	ResString resCap (IDS_MODIDENTCAP, 128);
	WProgressIndicator Status;

		Status.CreateInstance(CLSID_ProgressIndicator);
		if (Status.IsValid()) 
			Status ->InitNew (Handle(API_WINDOW_HWND), PIFLAG_RESULT);

	#if !defined(_TRIAS_OLDIMPLEMTATION1)
	CComVariant v (L"CheckMode=0;Checked=0;ShowConnections=0");

		pvModIdData[1] = &v;		// Initialisierungsdaten setzen
	#endif // _TRIAS_OLDIMPLEMTATION1
		return SUCCEEDED(RunPropertyActionSequence (
					Handle(API_WINDOW_HWND), resCap, &calModIdClsIds, NULL, NULL, NULL));
	} COM_CATCH_RETURN(false);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Alle Objekte einer Objektklasse doppeln
static const CLSID *cbCopyObjClsIds[] = {
	&CLSID_SelectIdentObjTyp,
	&CLSID_ObjekteDoppeln,
	&CLSID_ModifyIdent,
	&CLSID_DestinationObjectWindow,
};
#if !defined(_TRIAS_OLDIMPLEMTATION1)
static VARIANT *pvData[] = {
	NULL,
	NULL,
	NULL,
	NULL,
};
#endif // _TRIAS_OLDIMPLEMTATION1
static CALPCLSID calCopyObjClsIds = {
	sizeof(cbCopyObjClsIds)/sizeof(cbCopyObjClsIds[0]),
	cbCopyObjClsIds,
	NULL,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	const_cast<const VARIANT **>(pvData),
#endif // _TRIAS_OLDIMPLEMTATION1
};

bool IrisWind::doCopyObjectsIdent (void)
{
	COM_TRY {
	ResString resCap (IDS_COPYOBJECTSCAP, 128);
	WProgressIndicator Status;

		Status.CreateInstance(CLSID_ProgressIndicator);
		if (Status.IsValid()) 
			Status ->InitNew (Handle(API_WINDOW_HWND), PIFLAG_RESULT);

	#if !defined(_TRIAS_OLDIMPLEMTATION1)
	CComVariant v (L"CheckMode=1;Checked=1;ShowConnections=0");

		pvData[2] = &v;		// Initialisierungsdaten setzen
	#endif // _TRIAS_OLDIMPLEMTATION1
		return SUCCEEDED(RunPropertyActionSequence (
					Handle(API_WINDOW_HWND), resCap, &calCopyObjClsIds, NULL, NULL, NULL));
	} COM_CATCH_RETURN(false);
	return true;
}

#endif // !defined(_USE_XML_GEOCOMPONENTS)
