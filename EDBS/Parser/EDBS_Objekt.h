// OBJ_EDBS.h : Deklaration von COBJ_EDBS

#ifndef __OBJ_EDBS_H_
#define __OBJ_EDBS_H_

#include "resource.h"       // Hauptsymbole
#include "EDBS_Linien.h"
#include "EDBS_BesondereInformationen.h"

/////////////////////////////////////////////////////////////////////////////
// COBJ_EDBS
class ATL_NO_VTABLE CEDBS_Objekt : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEDBS_Objekt, &CLSID_EDBS_Objekt>,
	public IDispatchImpl<IEDBS_Objekt, &IID_IEDBS_Objekt, &LIBID_TRiAS_EDBS>
{
public:
	CEDBS_Objekt();
	~CEDBS_Objekt();

DECLARE_REGISTRY_RESOURCEID(IDR_EDBS_Objekt)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEDBS_Objekt)
	COM_INTERFACE_ENTRY(IEDBS_Objekt)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IOBJ_EDBS
public:
	STDMETHOD(get_FLOE)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_FLOE)(/*[in]*/ BOOL newVal);
	STDMETHOD(get_GrundpunktR)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_GrundpunktR)(/*[in]*/ double newVal);
	STDMETHOD(get_GrundpunktH)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_GrundpunktH)(/*[in]*/ double newVal);
	BOOL mtFLOE;
	short msFolie;
	short msObjektart;
	CString mstrAktualitaet;
	CString mstrObjekttyp;
	CString mstrObjektnummer;
	CString mstrModelltyp;  //nicht im ALK
	CString mstrEntstehungsdatum;
	CString mstrVeraenderungskennung;    //nicht im ALK
	double mdblRA;
	double mdblHA; 
	STDMETHOD(get_Objektnummer)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Objektnummer)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Folie)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_Folie)(/*[in]*/ short newVal);
	STDMETHOD(get_Linien)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(get_BesondereInformationen)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(get_Entstehungsdatum)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Entstehungsdatum)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Veraenderungskennung)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Veraenderungskennung)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Modelltyp)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Modelltyp)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Aktualitaet)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Aktualitaet)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Objekttyp)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Objekttyp)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Objektart)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_Objektart)(/*[in]*/ short newVal);
	CComObject<CEDBS_Linien>  *mpobjsLinien;
	CComObject<CEDBS_BesondereInformationen>  *mpobjsBesondereInformationen;
};

#endif //__OBJ_EDBS_H_
