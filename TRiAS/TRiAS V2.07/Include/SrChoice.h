// Allgemeines zur PropertyAction 'CLSID_PropertyChoice' 
// File: SRCHOICE.H

#if !defined(_SRCHOICE_H)
#define _SRCHOICE_H

// GUID ///////////////////////////////////////////////////////////////////////
// 0796388A-3123-101C-BB62-00AA0018497C	
DEFINE_GUID(CLSID_PropertyChoice, 0x0796388AL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

// Name ///////////////////////////////////////////////////////////////////////
const char c_cbPropertyChoice[] = "CLSPROP_ROOT\\TRiAS® (allgemein)\\Auswahl aus mehreren Property-Aktionen";

// Erzeugte ZusatzInfos ///////////////////////////////////////////////////////
// 1. IEnumLONG enthält alle selektierten Objekte
// ClipBoardFormat und FORMATETC sind global für alle PropertyAction's
#include <propactn.h>

// 2. keine weiteren

#endif // _SRCHOICE_H
