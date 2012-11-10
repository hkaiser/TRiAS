// Allgemeines zur PropertyAction 'CLSID_SelectIdentObjTyp' -------------------
// File: SELIDPRP.H

#if !defined(_SELIDPRP_H)
#define _SELIDPRP_H

///////////////////////////////////////////////////////////////////////////////
// zusätzliches Interfaces um auf die enthaltenen Einträge Einfluß zu nehmen
MIDL_INTERFACE("E51FF080-E5BD-11d2-9BD9-586A20524153")
IAddEntryCallback : public IUnknown
{
public:
	STDMETHOD(AddEntry) (THIS_ INT_PTR lIdent, DWORD dwTypes, DWORD *pdwTypesToAdd) PURE;
};

MIDL_INTERFACE("E51FF081-E5BD-11d2-9BD9-586A20524153")
IInitAddEntryCallback : public IUnknown
{
public:
	STDMETHOD(putref_AddEntryCallback)(THIS_ IAddEntryCallback *pAddEntryCB) PURE;
};

// GUID ///////////////////////////////////////////////////////////////////////
// 0E54C9E0-20DE-11CF-BA55-00AA0018497C	
DEFINE_GUID(CLSID_SelectIdentObjTyp, 0x0E54C9E0L, 0x20DE, 0x11CF, 0xBA, 0x55, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);

// Name ///////////////////////////////////////////////////////////////////////
const char c_cbSelPrpName[] = "CLSPROP_ROOT\\TRiAS® (allgemein)\\Objektauswahl nach Objektklasse und Objekttyp";

// Erzeugte ZusatzInfos ///////////////////////////////////////////////////////
// 1. IEnumLONG enthält alle selektierten Objekte
// ClipBoardFormat und FORMATETC sind global für alle PropertyAction's
#include <propactn.h>

// 2. keine weiteren


#endif // _SELIDPRP_H
