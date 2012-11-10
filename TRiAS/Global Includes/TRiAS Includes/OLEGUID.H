// GUID für die OLEAutomation-Erweiterung -------------------------------------
// File: OLEGUID.H

#if !defined(_OLEGUID_H)
#define _OLEGUID_H

// CLSID der Erweiterung selbst (TRiAS.OleAutomation.1) -----------------------
// ED9655C2-3122-101C-BB62-00AA0018497C ---------------------------------------
DEFINE_GUID(CLSID_OleAutoExtension, 0xED9655C2L, 0x3122, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// ED9655EA-3122-101C-BB62-00AA0018497C	
// DEFINE_GUID(CLSID_WrapperExtension, 0xED9655EAL, 0x3122, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

// 89C5F584-4E2B-101B-AAE1-E7E7E7E7E7E7	
DEFINE_GUID(IID_IGetTRiASApplication, 0x89C5F584L, 0x4E2B, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);

// IID des internen ConnectionPoint's -----------------------------------------
// 89C5F583-4E2B-101B-AAE1-E7E7E7E7E7E7	
DEFINE_GUID(IID_INotificationSink2, 0x89C5F583L, 0x4E2B, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7);

///////////////////////////////////////////////////////////////////////////////
// CLSID der PropertyPage für externe Module
// 079638D7-3123-101C-BB62-00AA0018497C	
DEFINE_GUID(CLSID_ManageAddIns, 0x079638D7L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

#endif // _OLEGUID_H
