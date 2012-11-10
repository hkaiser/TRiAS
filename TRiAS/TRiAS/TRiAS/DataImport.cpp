// @doc
// @module DataImport.cpp | Datenimport aus diversen ASC-Formaten

#include "triaspre.hxx"

#if !defined(_USE_XML_GEOCOMPONENTS)

#include "triasres.h"

#include <funcs03.h>
#include <ipropseq.hxx>

#include <initguid.h>
#include <importprp.h>

#include "extmain3.hxx"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Objekte importieren
static const CLSID *cbImportClsIds[] = {
	&CLSID_ImportDataPropAct,
};
static CALPCLSID calImportClsIds = {
	sizeof(cbImportClsIds)/sizeof(cbImportClsIds[0]),
	cbImportClsIds,
	NULL,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	NULL
#endif // _TRIAS_OLDIMPLEMTATION1
};

bool ExtDirisWindow::doImport (void)
{
ResString resCap (IDS_DATAIMPORTCAP, 128);

	return SUCCEEDED(RunPropertyActionSequence (
				Handle(API_WINDOW_HWND), resCap, &calImportClsIds, NULL, NULL, NULL));
}

#endif // !defined(_USE_XML_GEOCOMPONENTS)
