// File: ISCRPROP.H

#ifndef _ISCRPROP_H
#define _ISCRPROP_H

#undef INTERFACE
#define INTERFACE IScriptProperty
                
// zum Abspeichern des Scriptes
typedef struct tagebSaveStruct {
	ebHCODE hCode;
	LPSTR pText;
	DWORD dwSaveFlag;
	LPSTR *lplpstrRelScripts;
	UINT  uiCntRelScripts;
} ebSaveStruct;
typedef ebSaveStruct* LPSAVESTRUCT;

// 079638A0-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IScriptProperty, 0x079638A0L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IScriptProperty, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IScriptProperty methods
	STDMETHOD(Set)(LPSAVESTRUCT pStruct) PURE;
	STDMETHOD(Get)(LPSAVESTRUCT pStruct) PURE;
};

// 079638A1-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IStreamInfo, 0x079638A1L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IStreamInfo, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IStreamInfo methods
	STDMETHOD(Set)(BSTR bstr, DWORD) PURE;
	STDMETHOD(Get)(BSTR bstr, DWORD*) PURE;
};

// für SaveStruct
#define CC_SCRIPT			0x0001
#define CC_CODE				0x0002
#define CC_ALL				0x0004
#define CC_RELATEDSCRIPTS	0x0008

#define SUPERITEM 			0x0080
// InfoFlags
#define NEW_SUPERITEM 		0x0010
#define NOT_NEW_SUPERITEM 	0xFFEF
#define NEW_ITEM	 		0x0020
#define NOT_NEW_ITEM		0xFFDF
#define KEYITEM				0x0040

#define STORAGESCRIPT		0x000A
#endif // _ISCRPROP_H