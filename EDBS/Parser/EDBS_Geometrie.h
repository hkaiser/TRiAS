// EDBS_Geometrie.h : Deklaration von CEDBS_Geometrie

#ifndef __EDBS_GEOMETRIE_H_
#define __EDBS_GEOMETRIE_H_

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CEDBS_Geometrie
class ATL_NO_VTABLE CEDBS_Geometrie : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CEDBS_Geometrie, &CLSID_EDBS_Geometrie>,
	public IDispatchImpl<IEDBS_Geometrie, &IID_IEDBS_Geometrie, &LIBID_TRiAS_EDBS>
{
public:
	CEDBS_Geometrie();
	~CEDBS_Geometrie();

DECLARE_REGISTRY_RESOURCEID(IDR_EDBS_GEOMETRIE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CEDBS_Geometrie)
	COM_INTERFACE_ENTRY(IEDBS_Geometrie)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IEDBS_Geometrie
public:
	STDMETHOD(get_AnzahlKoordinaten)(/*[out, retval]*/ int *pVal);
	STDMETHOD(get_RE)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_RA)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_HE)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_HA)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_Geometrieart)(/*[out, retval]*/ short *pVal);
	long Dim( int iDimension );
	BYTE mbGeometrieart;
	double dblRA;
	double dblHA;
	double dblRE;
	double dblHE;
	long lTT;	

	int miDimension;
	double *padblR;
	double *padblH;

};

#endif //__EDBS_GEOMETRIE_H_
