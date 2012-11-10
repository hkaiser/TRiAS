// Umklassifizieren aller Objekte verschiedener Objektklassen -----------------
// File: MODIFYID.CXX

#include "triaspre.hxx"
				
#include "triasres.h"

#include <funcs03.h>
#include <ipropseq.hxx>
#include <selidprp.h>
#include <modidprp.h>

#include <DstObWnd.h>

#include <initguid.h>
#include <ObjekteDoppelnGuid.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Objekte eines Idents umklassifizieren --------------------------------------
static const CLSID *cbModIdClsIds[] = {
	&CLSID_SelectIdentObjTyp,
	&CLSID_ModifyIdent,
};
static CALPCLSID calModIdClsIds = {
	sizeof(cbModIdClsIds)/sizeof(cbModIdClsIds[0]),
	cbModIdClsIds,
	NULL,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	NULL,
#endif // _TRIAS_OLDIMPLEMTATION1
};

bool IrisWind::doModIdents (void)
{
ResString resCap (IDS_MODIDENTCAP, 128);

	return SUCCEEDED(RunPropertyActionSequence (
				Handle(API_WINDOW_HWND), resCap, &calModIdClsIds, NULL, NULL, NULL));
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
	pvData,
#endif // _TRIAS_OLDIMPLEMTATION1
};

bool IrisWind::doCopyObjectsIdent (void)
{
ResString resCap (IDS_COPYOBJECTSCAP, 128);
CComVariant v(L"CheckMode=1;Checked=1");

	pvData[2] = &v;		// Initialisierungsdaten setzen
	return SUCCEEDED(RunPropertyActionSequence (
				Handle(API_WINDOW_HWND), resCap, &calCopyObjClsIds, NULL, NULL, NULL));
}

