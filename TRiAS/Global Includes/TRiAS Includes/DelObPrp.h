// Allgemeines zur PropertyAction 'CLSID_DeleteObjects' 
// File: DELOBPRP.H

#if !defined(_DELOBPRP_H)
#define _DELOBPRP_H

// GUID ///////////////////////////////////////////////////////////////////////
// 079638DC-3123-101C-BB62-00AA0018497C	
DEFINE_GUID(CLSID_DeleteObjects, 0x079638DCL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

// Name ///////////////////////////////////////////////////////////////////////
const char c_cbDelObjName[] = "CLSPROP_ROOT\\TRiAS® (allgemein)\\Objekte löschen";

// Erzeugte ZusatzInfos ///////////////////////////////////////////////////////
// 1. IEnumLONG enthält alle selektierten Objekte
// ClipBoardFormat und FORMATETC sind global für alle PropertyAction's
#include <propactn.h>

// 2. keine weiteren

#endif // _DELOBPRP_H
