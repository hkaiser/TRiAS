// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 27.01.2003 08:38:45
//
// @doc
// @module CodeLine.h | Declaration of the <c CCodeLine> class

#if !defined(__CODELINE_H_)
#define __CODELINE_H_

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

#include "CodeLineDlg.h"

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
// CCodeLine
class ATL_NO_VTABLE CCodeLine : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCodeLine, &CLSID_CodeLine>,
	public IObjectWithSiteImpl<CCodeLine>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_NONE
	};

	CCodeLine() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_CODELINE)
	{
		m_pCfgDlg = NULL;
		m_pIdents = NULL;

		m_iErrorCode = 0;

		m_bstrLink = "";
		m_bstrError = "";
		m_bstrGCA = "";
		m_bstrGCO = "";
		m_bstrGCOriginal = "";
		m_bstrErrorText = "";


	}
	~CCodeLine()
	{
		DELETE_OBJ(m_pCfgDlg);
		DELETE_OBJ(m_pIdents);
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_CODELINE)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CCodeLine)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
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

//-----------------------------------------------------------------------
	STDMETHODIMP SetSingleConfigData (void);
	STDMETHODIMP InitConfigDataFromRegistry(UINT,UINT,UINT,UINT);
	STDMETHODIMP PreConfigData (void);


	int ErrorCode(void) { return m_iErrorCode; }
	CComBSTR CheckFeature ( void ) { return m_bstrGCO; }
	bool AddIdent(long lIdent,int iErrorCode);
	bool IsOtherClass ();


private:
	SEnumLONG m_Objects;		// zu bearbeitende Objektmenge
	CCodeLineDlg *m_pCfgDlg;	// Konfigurationsdialog
	int m_iErrorCode;

	CComBSTR m_bstrLink;		// Link für SABIS-Kopplung
	CComBSTR m_bstrGCO;			// SABIS-Kopplung/GCO-Code
	CComBSTR m_bstrError;		// Fehlerattribut
	CComBSTR m_bstrErrorText;	// Text Fehlerattribut
	CComBSTR m_bstrGCA;			// Prüfattribut-Vorspann bei Punkten (KurzCode)
	CComBSTR m_bstrGCOriginal;	// Prüfattribut--Original

	// ParameterEingabe
	CComBSTR m_bstrParmGCO;			// GCO-KoppelBegriff - ParameterEingabe
	CComBSTR m_bstrParmOriginal;	// GCO Original - Vorprüfung - ParameterEingabe

	TR_ObjTree *m_pIdents;			// Klassenbaum

};

#endif // !defined(__CODELINE_H_)
