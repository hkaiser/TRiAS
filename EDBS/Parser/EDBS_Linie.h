// EDBS_Linie.h : Deklaration von CEDBS_Linie

#ifndef __EDBS_LINIE_H_
#define __EDBS_LINIE_H_

#include "resource.h"       // Hauptsymbole
#include "EDBS_Geometrie.h"
#include "EDBS_FachparameterDerLinie.h"

/////////////////////////////////////////////////////////////////////////////
// CEDBS_Linie
class ATL_NO_VTABLE CEDBS_Linie : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEDBS_Linie, &CLSID_EDBS_Linie>,
	public ISupportErrorInfo,
	public IDispatchImpl<IEDBS_Linie, &IID_IEDBS_Linie, &LIBID_TRiAS_EDBS>
{
public:
	CEDBS_Linie();
	~CEDBS_Linie();

DECLARE_REGISTRY_RESOURCEID(IDR_EDBS_LINIE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEDBS_Linie)
	COM_INTERFACE_ENTRY(IEDBS_Linie)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IEDBS_Linie
public:
	STDMETHOD(get_Geometrie)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(get_Objektteilnummer)(/*[out, retval]*/ short *pVal);
	STDMETHOD(get_Fachparameter)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(get_Linienteilung)(/*[out, retval]*/ short *pVal);
//	STDMETHOD(put_Linienteilung)(/*[in]*/ short newVal);
	STDMETHOD(get_Geometrieart)(/*[out, retval]*/ short *pVal);
//	STDMETHOD(put_Geometrieart)(/*[in]*/ short newVal);
	STDMETHOD(get_Objektart)(/*[out, retval]*/ short *pVal);
//	STDMETHOD(put_Objektart)(/*[in]*/ short newVal);
	STDMETHOD(get_Folie)(/*[out, retval]*/ short *pVal);
//	STDMETHOD(put_Folie)(/*[in]*/ short newVal);
	short msObjektteilnummer;
	BYTE  mbLinienteilung;
	short msFolie;
	short msObjektart;

	CComObject<CEDBS_Geometrie>  *mpobjGeometrie;
	CComObject<CEDBS_FachparameterDerLinie>  *mpobjsFachparameter;

};

#endif //__EDBS_LINIE_H_
