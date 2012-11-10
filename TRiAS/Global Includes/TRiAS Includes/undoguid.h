// GUID für IUndoRedo ---------------------------------------------------------
// File: UNDOGUID.H

#if !defined(_UNDIGUID_H)
#define _UNDIGUID_H

///////////////////////////////////////////////////////////////////////////////
// 07963808-3123-101C-BB62-00AA0018497C	
DEFINE_GUID(IID_IUndoRedo, 0x07963808L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// 07963809-3123-101C-BB62-00AA0018497C	
DEFINE_GUID(IID_IUndoRedoList, 0x07963809L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

///////////////////////////////////////////////////////////////////////////////
// B16261A0-856C-11CE-8CC3-444553540000	
DEFINE_GUID(CLSID_UndoRedoClassFactory, 0xB16261A0L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
// B16261A1-856C-11CE-8CC3-444553540000	
DEFINE_GUID(CLSID_UndoRedoObject, 0xB16261A1L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

// Merkmal löschen, erzeugen oder modifizieren --------------------------------
// B16261A2-856C-11CE-8CC3-444553540000	
DEFINE_GUID(IID_IUndoRedoObjectFeature, 0xB16261A2L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

// Relation löschen -----------------------------------------------------------
// B16261A3-856C-11CE-8CC3-444553540000	
DEFINE_GUID(IID_IUndoRedoDeleteObjectRelation, 0xB16261A3L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

// Relation erzeugen ----------------------------------------------------------
// B16261A4-856C-11CE-8CC3-444553540000	
DEFINE_GUID(IID_IUndoRedoCreateObjectRelation, 0xB16261A4L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

// Textobjekt löschen ---------------------------------------------------------
// B16261A5-856C-11CE-8CC3-444553540000	
DEFINE_GUID(IID_IUndoRedoDeleteText, 0xB16261A5L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

// Textobjekt erzeugen --------------------------------------------------------
// B16261A6-856C-11CE-8CC3-444553540000	
DEFINE_GUID(IID_IUndoRedoCreateText, 0xB16261A6L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

// Objekt aus OR-Fenster entfernen --------------------------------------------
// B16261A7-856C-11CE-8CC3-444553540000	
DEFINE_GUID(IID_IUndoRedoDeleteObjectWnd, 0xB16261A7L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
// B16261AE-856C-11CE-8CC3-444553540000	
DEFINE_GUID(IID_IUndoRedoReplaceObjectWnd, 0xB16261AEL, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
// B16261AF-856C-11CE-8CC3-444553540000	
DEFINE_GUID(IID_IUndoRedoAddToObjectWnd, 0xB16261AFL, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

// Normales Objekt löschen ----------------------------------------------------
// B16261A8-856C-11CE-8CC3-444553540000	
DEFINE_GUID(IID_IUndoRedoDeleteObject, 0xB16261A8L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

// Normales Objekt modifizieren -----------------------------------------------
// B16261A9-856C-11CE-8CC3-444553540000	
DEFINE_GUID(IID_IUndoRedoModifyObject, 0xB16261A9L, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

// Normales Objekt erzeugen -----------------------------------------------
// B16261AD-856C-11CE-8CC3-444553540000	
DEFINE_GUID(IID_IUndoRedoCreateObject, 0xB16261ADL, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

// PBD-Eintrag löschen, erzeugen, modifizieren --------------------------------
// B16261AA-856C-11CE-8CC3-444553540000	
DEFINE_GUID(IID_IUndoRedoPBDData, 0xB16261AAL, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

// Visualisierung modifizieren ------------------------------------------------
// B16261AB-856C-11CE-8CC3-444553540000	
DEFINE_GUID(IID_IUndoRedoVisInfo, 0xB16261ABL, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

// Identifikator eines Objektes modifizieren ----------------------------------
// B16261AC-856C-11CE-8CC3-444553540000	
DEFINE_GUID(IID_IUndoRedoModIdent, 0xB16261ACL, 0x856C, 0x11CE, 0x8C, 0xC3, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

// Neue Objektnummer abfragen bzw. weitergeben
// {9A55E460-24EB-11D3-94F1-0080C786297B}
extern "C" const IID __declspec(selectany) IID_IPropagateObjectNumber = 
	{0x9a55e460,0x24eb,0x11d3,{0x94,0xf1,0x00,0x80,0xc7,0x86,0x29,0x7b}};

#endif // _UNDIGUID_H
