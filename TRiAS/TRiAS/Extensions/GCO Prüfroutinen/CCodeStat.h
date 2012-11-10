// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 04.12.2002 09:44:34
//
// @doc
// @module CCodeStat.h | Declaration of the <c CCCodeStat> class

#if !defined(__CCODESTAT_H_)
#define __CCODESTAT_H_

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

#include "CCodeStatDlg.h"

/////////////////////////////////////////////////////////////////////////////
// Declaration diverser Klassen
#if !defined(_ENUM_LONG_ENUMERATOR_DEFINED)
#define _ENUM_LONG_ENUMERATOR_DEFINED

DefineSortingEnumerator(LONG);		// definiert SEnumLONG
DefineSmartEnumerator2(LONG, __uuidof(IEnumLONG));		// definiert WEnumLONG (Wrapper für IEnum<LONG>)
DefineEnumInputIterator(LONG);		// definiert InEnumLONG
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG 

#endif // _ENUM_LONG_ENUMERATOR_DEFINED

// Map für Fehlerarten
typedef map<INT_PTR, INT_PTR, less<INT_PTR> > CErrorMap;

/////////////////////////////////////////////////////////////////////////////
// CCCodeStat
class ATL_NO_VTABLE CCCodeStat : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCCodeStat, &CLSID_CCodeStat>,
	public IObjectWithSiteImpl<CCCodeStat>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_NONE
	};

	CCCodeStat() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_CCODESTAT)
	{
		m_pCfgDlg = NULL;
		m_iErrorCode = 0;
		m_bUND = 0;
		m_pObjects = NULL;
		m_bstrGCO = "";
		m_bstrGCOriginal = "";
		m_bstrError = "";
		m_bstrCaption = "";
		m_bUseAll = true;
		m_bShowErrors = false;
		m_bErrorStatist = false;


	}
	~CCCodeStat()
	{
		DELETE_OBJ(m_pCfgDlg);
		g_ErrorType.clear();	
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_CCODESTAT)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CCCodeStat)
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
	STDMETHODIMP PreConfigData (void);

	STDMETHODIMP EndActionTree (TR_ObjTree *pObjects, OutEnumLONG &rOutIter);
	STDMETHODIMP ResetActionTree (TR_ObjTree *pObjects);

	HRESULT SetPacketCaption (IDataObject *pIDO, long lPacket );
	HRESULT SetPacketFeature (IDataObject *pIDO);

	
	STDMETHODIMP SetErrorCodeMap(void);
	int FindFirstCode ( int iError);

	bool CheckError (int iErrorIst ,int iErrorSoll);
	int ErrorCode(void) { return m_iErrorCode; }
	void SetErrorCode ( int iErrorCode ) { m_iErrorCode = m_iErrorCode | iErrorCode; }
	void SetPacket ( int iObjError, int iError);
	long GetPacket (void);
	CCCodeStatDlg * ActionDlg(void) { return m_pCfgDlg; }
	TR_ObjTree * Objects(void) { return m_pObjects; }
	CComBSTR ErrorFeature (void) { return m_bstrError; }
	void FindCaption ( int iError);
	void GetErrorCode (void);
	void SetObjectNumber (void);					// Durchsuchte Objekte zählen
	void SetErrorFeatures( int iObjError);			// Fehlerarten zählen
	void ResetErrorFeatures( void);


private:
	SEnumLONG m_Objects;		// zu bearbeitende Objektmenge
	CCCodeStatDlg *m_pCfgDlg;	// Konfigurationsdialog
	int m_iErrorCode;
	TR_ObjTree *m_pObjects;	// Objektbaum

	CComBSTR m_bstrGCO;
	CComBSTR m_bstrGCOriginal;
	CComBSTR m_bstrError;

	CComBSTR m_bstrCaption;

	long m_lPacket;
	bool m_bUND;

	CErrorMap g_ErrorType;

	bool m_bUseAll;
	bool m_bShowErrors;
	bool m_bErrorStatist;


};

#endif // !defined(__CCODESTAT_H_)
