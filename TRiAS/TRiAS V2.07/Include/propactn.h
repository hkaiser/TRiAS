// Allgemeine Informationen, die von einer PropertyAction zur nächsten gereicht 
// werden
// File: PROPACTN.H

#if !defined(_PROPACTN_H)
#define _PROPACTN_H

// Erzeugte Infos im durchgereichten IDataObject ------------------------------
// 1. IEnumLONG mit allen selektierten Objekten. Dieser Enumerator ist in einen
// Stream serialisiert, der im CDataObject übergeben wird.
// 
// ClipBoardFormat
const char c_cbPASelectedObjects[] = "EnumSelectedObjects";

//
// FORMATETC
const FORMATETC c_feSelectedObjects = {
	RegisterClipboardFormat (c_cbPASelectedObjects),// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

///////////////////////////////////////////////////////////////////////////////
// InitialisierungsInfo für eine PropertyAction
// Wird durch ein gestreamten Variant gespeichert

// ClipBoardFormat
const char c_cbInitPropAct[] = "InitPropActFromData";

const FORMATETC c_feInitPropAct = {
	RegisterClipboardFormat (c_cbInitPropAct),		// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

#endif // _PROPACTN_H
