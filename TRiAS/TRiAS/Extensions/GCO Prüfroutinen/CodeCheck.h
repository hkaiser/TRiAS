// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 06.11.2002 09:34:38
//
// @doc
// @module CodeCheck.h | Declaration of the <c CCodeCheck> class

#if !defined(__CODECHECK_H_)
#define __CODECHECK_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include <Lmcons.h>			// GetUserName

#include <Com/PropertyActionBase.h>

#include <ienumobj.hxx>
#include <ospace/com/iterenum.h>
#include <ospace/std/set>

//#include "CodeCheckDlg.h"

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
// CCodeCheck
class ATL_NO_VTABLE CCodeCheck : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCodeCheck, &CLSID_CodeCheck>,
	public IObjectWithSiteImpl<CCodeCheck>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_NONE
	};

	CCodeCheck() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_CODECHECK)
	{
		m_pStreet = NULL;
		m_lUserName = m_lErrorCode = 0L;

		m_bstrLink = "";
		m_bstrError = "";
		m_bstrGCA = "";
		m_bstrGCO = "";
		m_bstrGCOriginal = "";
		m_bstrErrorText = "";

	}
	~CCodeCheck()
	{
//		DELETE_OBJ(m_pCfgDlg);
	}

	DECLARE_REGISTRY_RESOURCEID(IDR_CODECHECK)

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CCodeCheck)
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
	STDMETHODIMP EndActionTree (TR_STREETSTree *pStreet, OutEnumLONG &rOutIter);

//	STDMETHODIMP SetErrorCodeMap(void);

	bool put_DuplicateObjects(	TR_ObjTree *pDupObj,OutEnumLONG &rOutIter);


	void GetMCodeUserName(long);
	void GetMCodeErrorCode(long);
	void SetUserName(long);
	void SetErrorCode(long,int);
	void SetErrorCodeText(long,int);
	char *GetErrorText ( int);

	void ResetErrorCode (long ,int);
	bool GetTRiASUserName (void);
	void SetPBDMCode(ULONG lMCode, long lONr,const char * pData);
	void SetCodeInformation(long, int);
	string LinkFeature ( void);
	string LinkOriginal ( void);


	TR_STREETSTree * Street(void) { return m_pStreet; }


private:
	SEnumLONG m_Objects;		// zu bearbeitende Objektmenge
	TR_STREETSTree *m_pStreet;	// Objektbaum
	ULONG m_lErrorCode;			// MCode für ErrorCode
	ULONG m_lUserName;			// MCode für UserName
	TCHAR cUserName[UNLEN + 1];

	CComBSTR m_bstrLink;		// Link für SABIS-Kopplung
	CComBSTR m_bstrGCO;			// SABIS-Kopplung/GCO-Code
	CComBSTR m_bstrError;		// Fehlerattribut
	CComBSTR m_bstrErrorText;	// Text Fehlerattribut
	CComBSTR m_bstrGCA;			// Prüfattribut-Vorspann bei Punkten (KurzCode)
	CComBSTR m_bstrGCOriginal;	// Prüfattribut--Original

	// ParameterEingabe
	CComBSTR m_bstrParmGCO;			// GCO-KoppelBegriff - ParameterEingabe
	CComBSTR m_bstrParmOriginal;	// GCO Original - Vorprüfung - ParameterEingabe


};

#endif // !defined(__CODECHECK_H_)
