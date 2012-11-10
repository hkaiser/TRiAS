// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 13.12.2000 18:08:53 
//
// @doc
// @module CalClsId.h | Declaration of the <c CCalClsId> class

#if !defined(_CALCLSID_H__B6DFCC95_50BD_4740_8410_0A189C4831D5__INCLUDED_)
#define _CALCLSID_H__B6DFCC95_50BD_4740_8410_0A189C4831D5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if defined(_USE_XML_GEOCOMPONENTS)		// nur bei Bedarf laden

#import "msxml.dll" named_guids rename_namespace("xml")
#import "tlb/TRiASCFG.tlb" raw_interfaces_only raw_dispinterfaces named_guids 

#include <Atl/Ciid.h>

///////////////////////////////////////////////////////////////////////////////
// Daten, die für die Instantiierung einer PropertySequence notwendig sind
interface IPropertyActionSequence;

enum SEQTYPE {
	SEQTYPE_Unknown = 0,
	SEQTYPE_Sequence = 1,
	SEQTYPE_Property = 2,
};

class CCalClsId :
	public CALPCLSID
{
public:
	CCalClsId(IDataObject *pIDataIn = NULL) : 
		m_pClsIds(NULL), m_pvInitData(NULL), m_DataIn(pIDataIn),
		m_rgSeqType(SEQTYPE_Sequence), m_fSeqMayFail(false),
		m_fIsWizard97(false), m_dwFlags(0), m_fHasFlags(false)
	{
		memset (this, 0, sizeof(CALPCLSID));	// Basisklasse initialisieren
	}
	~CCalClsId() 
	{
		DELETE_OBJ(m_pClsIds);
		DELETE_OBJ(ppElems);
		FreeActions();
		FreeInitData();
		DELETE_OBJ(m_pvInitData);
	}

public:
	_TRIAS03_ENTRY HRESULT InitDataFromXml (xml::IXMLDOMElement *pIElem);
	CComBSTR GetSaveName()
	{
		if (m_bstrSaveAs.Length() > 0) 
			return m_bstrSaveAs;
		_ASSERTE(m_bstrName.Length() > 0);
		return m_bstrName;
	}
	BSTR GetName() { return m_bstrName; }
	BSTR GetDesc() { return m_bstrDesc; }
	BSTR GetVersion() { return m_bstrVersion; }

	REFCLSID GetSeqGuid() { return m_SeqGuid; }
	bool GetMayFail() { return m_fSeqMayFail; }
	bool GetIsWizard97() { return m_fIsWizard97; }
	SEQTYPE GetSequenceType() { return m_rgSeqType; }

	CALPCLSID *GetInitInfo() { return this; }
	bool GetFlags (DWORD *pdwFlags)
	{
		if (m_fHasFlags) {
			_ASSERTE(NULL != pdwFlags);
			*pdwFlags = m_dwFlags;
			return true;
		}
		return false;
	}

protected:
	HRESULT GetCommonInfo (xml::IXMLDOMElement *pIElem);

// PropertyActions aus Xml-Info laden
	HRESULT LoadPropertyActionsFromRegistry (REFGUID rGuid, xml::IXMLDOMNode *pIElem, IPropertyAction **pIAct);
	HRESULT LoadPropertyActionsDirect (REFGUID rGuid, xml::IXMLDOMNode *pIElem, int iLevel, IPropertyAction **pIAct);
	HRESULT LoadPropertyAction (IPropertyActionSequence *pISeq, BSTR bstrProgId, 
		CComVariant *pvInitData = NULL, BSTR bstrMkData = NULL, 
		BSTR bstrHeaderTitle = NULL, BSTR bstrHeaderSubTitle = NULL);

	HRESULT InitClsIds(long lSize);
	_TRIAS03_ENTRY void FreeActions();
	_TRIAS03_ENTRY void FreeInitData();

	HRESULT GetRegistryLoadInfo (xml::IXMLDOMNode *pINode, HKEY *phRootKey, 
		BSTR *pbstrKey, xml::IXMLDOMNode **ppIErrorInfo, 
		BSTR *pbstrHeaderTitle, BSTR *pbstrHeaderSubTitle);
	HRESULT ShowErrorInfo (xml::IXMLDOMNode *pINode);
	HRESULT GetErrorStrings (xml::IXMLDOMNode *pINode, BSTR *pbstrCaption, BSTR *pbstrPrompt);
	HRESULT GetInitInfo (xml::IXMLDOMNode *pINode, VARIANT *pvInitData);

	HRESULT GetTagValue (xml::IXMLDOMNode *pINode, BSTR bstrTagName, BSTR *pbstrValue);

private:
	CComBSTR m_bstrName;
	CComBSTR m_bstrSaveAs;
	CComBSTR m_bstrDesc;
	CComBSTR m_bstrVersion;
	DWORD m_dwFlags;
	bool m_fHasFlags;

	CLSID *m_pClsIds;			// Elemente der Sequenz
	VARIANT *m_pvInitData;		// Initialisierungsdaten für die Elemente

	CIID m_SeqGuid;				// Guid der Sequenz
	SEQTYPE m_rgSeqType;		// Typ der Sequenz
	bool m_fSeqMayFail;			// Instantiierung der Sequenz darf u.U. fehlschlagen
	bool m_fIsWizard97;			// Wizard vom neuen Typus (mit HeaderTitle etc.)

	__Interface<IDataObject> m_DataIn;
};

// zusätzlich nützliche Funktionen
namespace xml {
// ein bestimmtes Attribut einlesen
	_TRIAS03_ENTRY HRESULT GetAttribute (xml::IXMLDOMNode *pINode, LPCOLESTR pcoleItem, BSTR *pbstrText, bool fMayFail = false);

// Enumerator aller ChildNodes besorgen
	HRESULT GetEnumNode (xml::IXMLDOMNode *pINode, IEnumVARIANT **ppIEnum);
}

#endif // defined(_USE_XML_GEOCOMPONENTS)

#endif // !defined(_CALCLSID_H__B6DFCC95_50BD_4740_8410_0A189C4831D5__INCLUDED_)
