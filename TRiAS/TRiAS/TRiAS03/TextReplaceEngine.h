// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 06.09.2000 18:04:49
//
// @doc
// @module TextReplaceEngine.h | Declaration of the <c CTextReplaceEngine> class

#if !defined(_TEXTREPLACEENGINE_H__7F1AF622_2C92_4AEA_8E58_ECD64DA77A4B__INCLUDED_)
#define _TEXTREPLACEENGINE_H__7F1AF622_2C92_4AEA_8E58_ECD64DA77A4B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "TRiAS03.h"       // main symbols

#include <Com/PropertyActionBase.h>

#include <ienumobj.hxx>
#include <ospace/com/iterenum.h>
#include <ospace/std/set>
#include <ospace/string/regexp.h>

#include "TextReplaceEngineDlg.h"
#if defined(_USE_CONFIRMREPLACE_DIALOG)
#include "ConfirmReplace.h"
#endif // defined(_USE_CONFIRMREPLACE_DIALOG)

/////////////////////////////////////////////////////////////////////////////
// Declaration diverser Klassen
#if !defined(_ENUM_LONG_ENUMERATOR_DEFINED)
#define _ENUM_LONG_ENUMERATOR_DEFINED

DefineSortingEnumerator(LONG);		// definiert SEnumLONG
DefineSmartEnumerator2(LONG, __uuidof(IEnumLONG));		// definiert WEnumLONG (Wrapper für IEnum<LONG>)
DefineEnumInputIterator(LONG);		// definiert InEnumLONG
DefineEnumOutputIterator(LONG);		// definiert OutEnumLONG 

#endif // _ENUM_LONG_ENUMERATOR_DEFINED

namespace {
// forward decls only
	class CTextReplaceEngineWorker;
	class CTextReplaceEngineWorkerNoMatch;
}

/////////////////////////////////////////////////////////////////////////////
// CTextReplaceEngine
class ATL_NO_VTABLE CTextReplaceEngine : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTextReplaceEngine, &CLSID_TextReplaceEngine>,
	public IObjectWithSiteImpl<CTextReplaceEngine>,
	public CPropertyActionImpl
{
public:
	enum { 
		PA_TYPEFLAGS = 
			PROPCAPS_ACTION_SINK |
			PROPCAPS_ACTION_SOURCE
	};

	CTextReplaceEngine() : 
		CPropertyActionImpl (PA_TYPEFLAGS, IDS_DESCRIPTION_TEXTREPLACEENGINE)
	{
		m_pCfgDlg = NULL;
#if defined(_USE_CONFIRMREPLACE_DIALOG)
		m_pConfirm = NULL;
		m_ptDlgPos = Point(0, 0);
#endif // defined(_USE_CONFIRMREPLACE_DIALOG)
	}
	~CTextReplaceEngine()
	{
		DELETE_OBJ(m_pCfgDlg);
#if defined(_USE_CONFIRMREPLACE_DIALOG)
		DELETE_OBJ(m_pConfirm);
#endif // defined(_USE_CONFIRMREPLACE_DIALOG)
	}

//	DECLARE_REGISTRY_RESOURCEID(IDR_TEXTREPLACEENGINE)
	static HRESULT WINAPI UpdateRegistry(BOOL bRegister);

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	BEGIN_COM_MAP(CTextReplaceEngine)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IPropertyAction2)
		COM_INTERFACE_ENTRY(IPropertyAction3)
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
	STDMETHOD(Load)(THIS_ IStream *pStm);
	STDMETHOD(Save)(THIS_ IStream *pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize);
	STDMETHOD(InitNew) (THIS);

protected:
	HRESULT GetMatchObject (DMatchString2 **ppIMatch);
	HRESULT GetMatchProperties (IObjectProps **ppIProps, IObjectProperty **ppIOPSrc, IObjectProperty **ppIOPDest);
	HRESULT TryToSearch (IObjectProperty *pIOP, ULONG ulCnt, IEnumObjectsByNumber **ppIEnum);
	HRESULT GenerateOutput (INT_PTR lONr, IEnumObjProps *pEnum, BSTR *pbstr);
	HRESULT MatchAndReplaceString (INT_PTR lONr, DMatchString2 *pMatch, IObjectProperty *pPropSrc, BSTR bstrToReplace, IObjectProperty2 *pPropDest) throw(_com_error);

	friend class CTextReplaceEngineWorker;
	friend class CTextReplaceEngineWorkerNoMatch;

private:
	SEnumLONG m_Objects;				// zu bearbeitende Objektmenge
	CTextReplaceEngineDlg *m_pCfgDlg;	// Konfigurationsdialog
	CTextReplaceEngineDlg::CDlgStatus m_Status;
#if defined(_USE_CONFIRMREPLACE_DIALOG)
	CConfirmReplaceDlg *m_pConfirm;		// Nachfragen beim Nutzer
	Point m_ptDlgPos;
#endif // defined(_USE_CONFIRMREPLACE_DIALOG)
};

#endif // !defined(_TEXTREPLACEENGINE_H__7F1AF622_2C92_4AEA_8E58_ECD64DA77A4B__INCLUDED_)
