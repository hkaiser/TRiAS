// $Header: $
// Copyright© 1999-2001 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.03.2001 14:00:40 
//
// @doc
// @module SidManageTabs.h | Definition of SID's for the TabWindows

#if !defined(_SIDMANAGETABS_H__7D35042D_3E0A_4DBE_9AE9_02F6F8FEE148__INCLUDED_)
#define _SIDMANAGETABS_H__7D35042D_3E0A_4DBE_9AE9_02F6F8FEE148__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

///////////////////////////////////////////////////////////////////////////////
// ProjektTabVerwaltung
// 16D14140-F8A4-4CD8-B3E8-D2F83A7D24AF
EXTERN_C const GUID __declspec(selectany) SID_ManageProjectTabs = 
	{ 0x16D14140, 0xF8A4, 0x4CD8, 0xB3, 0xE8, 0xD2, 0xF8, 0x3A, 0x7D, 0x24, 0xAF };

///////////////////////////////////////////////////////////////////////////////
// OverviewTabVerwaltung
// 16D14141-F8A4-4CD8-B3E8-D2F83A7D24AF
EXTERN_C const GUID __declspec(selectany) SID_ManageOverviewTabs = 
	{ 0x16D14141, 0xF8A4, 0x4CD8, 0xB3, 0xE8, 0xD2, 0xF8, 0x3A, 0x7D, 0x24, 0xAF };

///////////////////////////////////////////////////////////////////////////////
// VBTabVerwaltung (SABiS)
// 16D14142-F8A4-4CD8-B3E8-D2F83A7D24AF
EXTERN_C const GUID __declspec(selectany) SID_ManageSABiSTabs = 
	{ 0x16D14142, 0xF8A4, 0x4CD8, 0xB3, 0xE8, 0xD2, 0xF8, 0x3A, 0x7D, 0x24, 0xAF };
// 16D14143-F8A4-4CD8-B3E8-D2F83A7D24AF
EXTERN_C const GUID __declspec(selectany) SID_ManageSABiSTabs2 = 
	{ 0x16D14143, 0xF8A4, 0x4CD8, 0xB3, 0xE8, 0xD2, 0xF8, 0x3A, 0x7D, 0x24, 0xAF };

///////////////////////////////////////////////////////////////////////////////
// VideoPane
// 16D14144-F8A4-4CD8-B3E8-D2F83A7D24AF
EXTERN_C const GUID __declspec(selectany) SID_ManageVideoTabs = 
	{ 0x16D14144, 0xF8A4, 0x4CD8, 0xB3, 0xE8, 0xD2, 0xF8, 0x3A, 0x7D, 0x24, 0xAF };

#endif // !defined(_SIDMANAGETABS_H__7D35042D_3E0A_4DBE_9AE9_02F6F8FEE148__INCLUDED_)
