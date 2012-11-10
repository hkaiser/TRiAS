// Allgemeines zur PropertyAction 'CLSID_CreateTextObjects' -------------------------
// File: TXTOBPRP.H

#if !defined(_TXTOBPRP_H)
#define _TXTOBPRP_H

// GUID ///////////////////////////////////////////////////////////////////////
// 079638DF-3123-101C-BB62-00AA0018497C	
DEFINE_GUID(CLSID_CreateTextObjects, 0x079638DFL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

// Name ///////////////////////////////////////////////////////////////////////
const char c_cbModPrpName[] = "CLSPROP_ROOT\\TRiAS® (allgemein)\\Erzeugen von Textobjekten über Objekteigenschaft";

// Erzeugte ZusatzInfos ///////////////////////////////////////////////////////
// 1. IEnum<LONG> enthält alle umklassifizierten Objekte
// ClipBoardFormat und FORMATETC sind global für alle PropertyAction's
#include <propactn.h>

// 2. keine weiteren

#endif // _TXTOBPRP_H
