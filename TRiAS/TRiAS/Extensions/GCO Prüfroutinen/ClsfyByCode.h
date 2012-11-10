// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 28.01.2003 11:54:08
//
// @doc
// @module ClsfyByCode.h | Declaration of the <c CClsfyByCode> class

#if !defined(__CLSFYBYCODE_H_)
#define __CLSFYBYCODE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols

#include <Com/PropertyActionBase.h>

#include <ienumobj.hxx>
#include <ospace/com/iterenum.h>
#include <ospace/std/set>

#include "ClsfyByCodeDlg.h"

/////////////////////////////////////////////////////////////////////////////
// Declaration diverser Klassen
#if !defined(_ENUM_LONG_ENUMERATOR_DEFINED)
#define _ENUM_LONG_ENUMERATOR_DEFINED

DefineSortingEnumerator(LONG);		// definiert SEnumLONG
DefineSmartEnumerator2(LONG, __uuidof(IEnumLONG));		// definiert WEnumLONG (Wrapper für IEnum<LONG>)
DefineEnumInputIterator(LONG);		// definiert InEnumLONG
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG 

#endif // _ENUM_LONG_ENUMERATOR_DEFINED

/////////////////////////////////////////////////////////////////////////////
// CClsfyByCode
class ATL_NO_VTABLE CClsfyByCode : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CClsfyByCode, &CLSID_ClsfyByCode>,
	public IObjectWithSiteImpl<CClsfyByCode>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_NONE
	};

	CClsfyByCode() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_CLSFYBYCODE)
	{
		m_pCfgDlg = NULL;

		m_iAreaCtrl = 0;

		m_bstrLink = "";
		m_bstrError = "";
		m_bstrGCA = "";
		m_bstrGCO = "";
		m_bstrGCOriginal = "";
		m_bstrErrorText = "";
		m_pMesh = NULL;
		m_iListIndex = 0;

	}
	~CClsfyByCode()
	{
		DELETE_OBJ(m_pCfgDlg);
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_CLSFYBYCODE)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CClsfyByCode)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersistPropertyBag)
		COM_INTERFACE_ENTRY(IPropertyInfo)
		COM_INTERFACE_ENTRY(IObjectWithSite)
	END_COM_MAP()

// IPropertyAction 
public:
	STDMETHOD(BeginAction) (THIS_ IProgressIndicator *pIProgInd);
	STDMETHOD(DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD(EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

// Geokomponente hat eigenen Dialog
	STDMETHOD(PreConfigPages)(THIS_ IDataObject *pIDataObject, DWORD dwFlags);
	STDMETHOD(AddConfigPages)(THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);

// IPersist
	STDMETHOD(GetClassID) (THIS_ CLSID *pClsID);
// IPersistStreamInit
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD(InitNew) (THIS);

// IPersistPropertyBag
	STDMETHOD(Load)(IPropertyBag *pBag, IErrorLog *pLog);
//-----------------------------------------------------------------------
	STDMETHODIMP SetSingleConfigData (void);
	STDMETHODIMP InitConfigDataFromRegistry(UINT,UINT,UINT,UINT);
	STDMETHODIMP PreConfigData (void);
	STDMETHODIMP EndActionTree (TR_MESHTree *pMesh, OutEnumLONG &rOutIter);
	STDMETHODIMP ResetActionTree (void);

	HRESULT SetPacketFeature (IDataObject *pIDO );
	HRESULT SetPacketCaption (IDataObject *pIDO, long lPacket );

	TR_MESHTree * Mesh(void) { return m_pMesh; }
	int AreaType (void ) { return m_iAreaCtrl; }
	int Index (void ) { return m_iListIndex; }
	string LinkFeature ( void);
	bool put_Objects( TR_ObjTree *pObj, OutEnumLONG &rOutIter);

private:
	SEnumLONG m_Objects;		// zu bearbeitende Objektmenge
	CClsfyByCodeDlg *m_pCfgDlg;	// Konfigurationsdialog

	CComBSTR m_bstrLink;		// Link für SABIS-Kopplung
	CComBSTR m_bstrGCO;			// SABIS-Kopplung/GCO-Code
	CComBSTR m_bstrError;		// Fehlerattribut
	CComBSTR m_bstrErrorText;	// Text Fehlerattribut
	CComBSTR m_bstrGCA;			// Prüfattribut-Vorspann bei Punkten (KurzCode)
	CComBSTR m_bstrGCOriginal;	// Prüfattribut--Original

	// ParameterEingabe
	CComBSTR m_bstrParmGCO;			// GCO-KoppelBegriff - ParameterEingabe
	CComBSTR m_bstrParmOriginal;	// GCO Original - Vorprüfung - ParameterEingabe

	int m_iAreaCtrl;
	long m_lPacket;

	CComBSTR m_bstrKey;

	TR_MESHTree *m_pMesh;		// Objektbaum

	int m_iListIndex;

};

#endif // !defined(__CLSFYBYCODE_H_)
