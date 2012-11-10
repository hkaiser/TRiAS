// Interface für Textobjektbilden ---------------------------------------------
// File: IGENTEXT.H

#if !defined(_IGENTEXT_H)
#define _IGENTEXT_H

#undef INTERFACE
#define INTERFACE IMaintainTexts

// ED9655C3-3122-101C-BB62-00AA0018497C	
// DEFINE_GUID(CLSID_TextExtension, 0xED9655C3L, 0x3122, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

// 07963807-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IMaintainTexts, 0x07963807L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

DECLARE_INTERFACE_(IMaintainTexts, IUnknown)
{
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef) (THIS)  PURE;
	STDMETHOD_(ULONG, Release) (THIS) PURE;

// *** IMaintainTexts methods ***
	STDMETHOD_(bool, GenerateText)(LONG lONr, ULONG ulMCode, DWORD dwFlags, LONG *plTextONr /*= NULL*/) PURE;
	STDMETHOD_(bool, GenerateText)(LONG lONr, CString sText, DWORD dwFlags, LONG *plTextONr /*= NULL*/) PURE;
	
	STDMETHOD_(bool, GenerateTexts)(ULONG ulIdent, ULONG ulMCode, short iObjTyp, DWORD dwFlags) PURE;
	STDMETHOD_(bool, GenerateTexts)(ULONG ulIdent, CString sText, short iObjTyp, DWORD dwFlags) PURE;

	STDMETHOD_(bool, UnlinkText)(LONG lONr, DWORD dwFlags) PURE;
	STDMETHOD_(bool, UnlinkTexts)(ULONG ulIdent, short iOTyp, DWORD dwFlags) PURE;
};
typedef IMaintainTexts *LPMAINTAINTEXTS;

// Werte für dwFlags ----------------------------------------------------------
typedef enum tagTEXTFLAGS {
	TEXTFLAGS_NOOPTIONS = 0x00,	
	TEXTFLAGS_TEMPORARY = 0x01,		// Textobjekte temporär erzeugen
	TEXTFLAGS_GENLINK = 0x02,
	TEXTFLAGS_DELETEOLD = 0x04,
	TEXTFLAGS_RENAME = 0x08,
} TEXTFLAGS;
	

#endif // _IGENTEXT_H
