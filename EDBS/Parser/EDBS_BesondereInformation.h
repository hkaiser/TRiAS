// EDBS_BesondereInformation.h : Deklaration von CEDBS_BesondereInformation

#ifndef __EDBS_BESONDEREINFORMATION_H_
#define __EDBS_BESONDEREINFORMATION_H_

#include "resource.h"       // Hauptsymbole
#include "EDBS_Geometrie.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_BesondereInformation
class ATL_NO_VTABLE CEDBS_BesondereInformation : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEDBS_BesondereInformation, &CLSID_EDBS_BesondereInformation>,
	public IDispatchImpl<IEDBS_BesondereInformation, &IID_IEDBS_BesondereInformation, &LIBID_TRiAS_EDBS>
{
public:
	CEDBS_BesondereInformation();
	~CEDBS_BesondereInformation();

DECLARE_REGISTRY_RESOURCEID(IDR_EDBS_BESONDEREINFORMATION)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEDBS_BesondereInformation)
	COM_INTERFACE_ENTRY(IEDBS_BesondereInformation)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IEDBS_BesondereInformation
public:
	STDMETHOD(get_Geometrie)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(get_Informationsart)(/*[out, retval]*/ short *pVal);
	STDMETHOD(get_Objektteilnummer)(/*[out, retval]*/ short *pVal);
	STDMETHOD(get_Textdaten)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Geometrieart)(/*[out, retval]*/ short *pVal);
//	STDMETHOD(put_Geometrieart)(/*[in]*/ short newVal);
	STDMETHOD(get_Objektart)(/*[out, retval]*/ short *pVal);
//	STDMETHOD(put_Objektart)(/*[in]*/ short newVal);

	BYTE  mbArtDerInformation;
	CString mstrKartentyp;
	CString mstrDarstellungsart;
	short msObjektart;
	CString mstrTextdaten;
	short msObjektteilnummer;
	
	CComObject<CEDBS_Geometrie>  *mpobjGeometrie;
};

#endif //__EDBS_BESONDEREINFORMATION_H_
