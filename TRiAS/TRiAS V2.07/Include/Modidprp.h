// Allgemeines zur PropertyAction 'CLSID_ModifyIdent' -------------------------
// File: MODIDPRP.H

#if !defined(_MODIDPRP_H)
#define _MODIDPRP_H

// GUID ///////////////////////////////////////////////////////////////////////
// 0E54C9ED-20DE-11CF-BA55-00AA0018497C	
DEFINE_GUID(CLSID_ModifyIdent, 0x0E54C9EDL, 0x20DE, 0x11CF, 0xBA, 0x55, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

// Name ///////////////////////////////////////////////////////////////////////
const char c_cbModPrpName[] = "CLSPROP_ROOT\\TRiAS® (allgemein)\\Modifikation der Objektklasse von Objekten";

// Erzeugte ZusatzInfos ///////////////////////////////////////////////////////
// 1. IEnum<LONG> enthält alle umklassifizierten Objekte
// ClipBoardFormat und FORMATETC sind global für alle PropertyAction's
#include <propactn.h>

// 2. keine weiteren

#endif // _MODIDPRP_H
