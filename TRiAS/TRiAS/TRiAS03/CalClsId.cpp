// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 13.12.2000 19:11:27 
//
// @doc
// @module CalClsId.cpp | Definition of the <c CCalClsId> class

#include "trias03p.hxx"
#include "trias03.h"

#if defined(_USE_XML_GEOCOMPONENTS)

#include <Atl/Ciid.h>
#include <Com/BstrHelpers.h>
#include <Com/VariantHelpers.h>

#include <ipropseq.hxx>
#include <funcs03.h>
#include <xtsnguid.h>
#include <dirisole.h>
#include <CalClsId.h>

#import "tlb/Helper.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids 
//	exclude("IParseRegularExpression", "IParseStringPairs", "IComposeStringPairs") 

#include "Strings.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumVARIANT);
DefineSmartInterface(DataObject);
DefineSmartInterface(PropertyAction);
DefineSmartInterface(PropertyAction2);
DefineSmartInterface(PropertyAction3);
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(ComposeStringPairs);		// WComposeStringPairs

///////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
namespace xml {
// ein bestimmtes Attribut einlesen
#pragma warning (disable: 4101)		// e: Variable defined, but not used
	HRESULT GetAttribute (xml::IXMLDOMNode *pINode, LPCOLESTR pcoleItem, BSTR *pbstrText, bool fMayFail)
	{
		_ASSERTE(NULL != pbstrText);
		COM_TRY {
		__Interface<xml::IXMLDOMNamedNodeMap> Attribs;
		__Interface<xml::IXMLDOMNode> Node;

			THROW_FAILED_HRESULT(pINode -> get_attributes (Attribs.ppi()));
			if (S_OK == Attribs -> raw_getNamedItem (CComBSTR(pcoleItem), Node.ppi())) {
			CComBSTR bstrIdent;

				THROW_FAILED_HRESULT(Node -> get_text (pbstrText));
			} else
				return E_FAIL;

		} COM_CATCH_EX(e) {		// NOT_USED(e)
			if (fMayFail)
				return E_FAIL;

		// Fehler wie normal melden
			COM_TRACECOMERROR(e);
			COM_ASSERT_EX(e);
		} COM_CATCH_ALL;
		return S_OK;
	}
#pragma warning (default: 4101)

// Enumerator aller ChildNodes besorgen
	HRESULT GetEnumNode (xml::IXMLDOMNode *pINode, IEnumVARIANT **ppIEnum)
	{
		COM_TRY {
		__Interface<xml::IXMLDOMNodeList> Nodes;
		WEnumVARIANT Enum;

			THROW_FAILED_HRESULT(pINode -> get_childNodes (Nodes.ppi()));
			THROW_FAILED_HRESULT(Nodes -> get__newEnum (Enum.ppu()));
			*ppIEnum = Enum.detach();

		} COM_CATCH;
		return S_OK;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Initialisierung der CALPCLSID-Struktur aus dem übergebenen Xml-Document
HRESULT CCalClsId::InitDataFromXml (xml::IXMLDOMElement *pIElem)
{
	COM_TRY {
	// diverse Plausibilitätsprüfungen
	CComBSTR bstrRootName;
	int iLevel = 0;

		THROW_FAILED_HRESULT(pIElem -> get_tagName (&bstrRootName));
		if (wcscmp (g_cbGeoComponentSequence, bstrRootName)) 
			_com_issue_error(E_INVALIDARG);		// falsches Dateiformat

	// Name und SaveAs et.al. einlesen
		THROW_FAILED_HRESULT(GetCommonInfo (pIElem));

	// Geocomponenten einlesen
	__Interface<xml::IXMLDOMNodeList> Nodes;
	long lCnt = 0;

		THROW_FAILED_HRESULT(pIElem -> raw_getElementsByTagName(CComBSTR(g_cbGeoComponent), Nodes.ppi()));
		THROW_FAILED_HRESULT(Nodes -> get_length(&lCnt));

		THROW_FAILED_HRESULT(InitClsIds(lCnt));

	long lCurrItem = 0;

		for (long lItem = 0; lItem < lCnt; ++lItem) {
		__Interface<xml::IXMLDOMNode> Node;
		CComBSTR bstrProgId, bstrLevel;

			THROW_FAILED_HRESULT(Nodes -> get_item(lItem, Node.ppi()));
			THROW_FAILED_HRESULT(xml::GetAttribute (Node, g_cbLevel, &bstrLevel));
			if (wcstol (bstrLevel, NULL, 10) > 0)
				continue;		// zuweit die Hierarchie hinunter geraten

			THROW_FAILED_HRESULT(xml::GetAttribute (Node, g_cbProgID, &bstrProgId));
				
		CIID Guid (bstrProgId, CIID::INITCIID_InitFromProgId);

			if (!Guid)
				_com_issue_error(E_INVALIDARG);		// Fehlerhaftes Dateiformat

		// ggf. dieses Objekt bereits instantiieren
		CComBSTR bstrLoad;
		bool fHasInitData = false;

			THROW_FAILED_HRESULT(xml::GetAttribute (Node, g_cbLoad, &bstrLoad));
			if (bstrLoad == g_cbRegistry) {
			// soll hier aus Xml-Info geladen werden
			WPropertyAction PropAct;
			HRESULT hr = LoadPropertyActionsFromRegistry(Guid, Node, PropAct.ppi());

				if (FAILED(hr))
					return hr;
				ppActions[lCurrItem] = PropAct.detach();		// übernimmt RefCnt!
				ppElems[lCurrItem] = NULL;
			} 
			else {
			// wird über normalen Weg intern geladen
				_ASSERTE(bstrLoad == g_cbDirectL);
				m_pClsIds[lCurrItem] = Guid;

			// Typ dieser GeoKomponente analysieren
			CComBSTR bstrType;

				THROW_FAILED_HRESULT(xml::GetAttribute (Node, g_cbType, &bstrType));
				if (bstrType == g_cbAction) {
				// muß über Moniker instantiiert werden
				CComBSTR bstrMkData;

					if (SUCCEEDED(xml::GetAttribute (Node, g_cbMonikerData, &bstrMkData))) 
						const_cast<BSTR>(ppMkData[lCurrItem]) = bstrMkData.Detach();

				// hat ggf. Initialisierungsdaten
				CComVariant vInit;

					if (S_OK == GetInitInfo(Node, &vInit)) {
						vInit.Detach(const_cast<VARIANT *>(ppvData[lCurrItem]));
						fHasInitData = true;
					}

				// ggf. HeaderTitle und HeaderSubTitle laden
				CComBSTR bstrValue;

					if (SUCCEEDED(GetTagValue(Node, CComBSTR(g_cbHeaderTitle), &bstrValue))) {
						const_cast<BSTR>(ppHeaderTitle[lCurrItem]) = bstrValue.Detach();

					// SubTitle bringt nur mit Title Sinn
						if (SUCCEEDED(GetTagValue(Node, CComBSTR(g_cbHeaderSubTitle), &bstrValue))) 
							const_cast<BSTR>(ppHeaderSubTitle[lCurrItem]) = bstrValue.Detach();
					}
				}
				else {
				// ist eine SubSequence
					_ASSERTE(bstrType == g_cbSequence);
				
				WPropertyAction PropAct;
				HRESULT hr = LoadPropertyActionsDirect (Guid, Node, 1, PropAct.ppi());

					if (FAILED(hr))
						return hr;
					ppActions[lCurrItem] = PropAct.detach();		// übernimmt RefCnt!
					ppElems[lCurrItem] = NULL;
				}
			}
			if (!fHasInitData) {
				VariantClear(const_cast<VARIANT *>(ppvData[lCurrItem]));
				ppvData[lCurrItem] = NULL;
			}
			++lCurrItem;
		}
		cElems = lCurrItem;

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// allgemeine Infos über die gesamte Sequence laden
HRESULT CCalClsId::GetCommonInfo (xml::IXMLDOMElement *pIElem)
{
	COM_TRY {
	// Attribute einlesen
	CComBSTR bstrAttr;

		if (S_OK == xml::GetAttribute(pIElem, g_cbProgID, &bstrAttr, true)) {
		// Guid der GeoComponentSequence
		CIID SeqGuid (bstrAttr, CIID::INITCIID_InitFromProgId);

			if (SeqGuid.IsValid())
				m_SeqGuid = SeqGuid;
		}
		if (!m_SeqGuid)
			m_SeqGuid = CLSID_PropertyActionSequence;

	CComBSTR bstrType;

		if (S_OK == xml::GetAttribute(pIElem, g_cbType, &bstrType, true)) {
		// Typ der GeoComponente (Sequence oder Objekteigenschaft)
			if (bstrType == g_cbSequence)
				m_rgSeqType = SEQTYPE_Sequence;
			else if (bstrType == g_cbProperty)
				m_rgSeqType = SEQTYPE_Property;
			else
				m_rgSeqType = SEQTYPE_Unknown;

			_ASSERTE(SEQTYPE_Unknown != m_rgSeqType);
		}

	CComBSTR bstrFlags;

		if (S_OK == xml::GetAttribute(pIElem, g_cbFlags, &bstrFlags, true)) {
		// ggf. Flags für Objekteigenschaft laden
			_ASSERTE(SEQTYPE_Property == m_rgSeqType);		// nur für Objekteigenschaften
			m_dwFlags = wcstol(bstrFlags, NULL, 16);
			m_fHasFlags = true;
		}

	CComBSTR bstrMayFail;

		if (S_OK == xml::GetAttribute(pIElem, g_cbMayFail, &bstrMayFail, true)) {
		// ggf. darf die Instantiierung fehlschlagen
			m_fSeqMayFail = (0 != wcstol(bstrMayFail, NULL, 10)) ? true : false;
		}

	CComBSTR bstrVersion;

		if (S_OK == xml::GetAttribute(pIElem, g_cbVersion, &bstrVersion, true)) {
		// Version dieser XML Datei
			m_bstrVersion = bstrVersion;
		}

	CComBSTR bstrIsWizard97;

		if (S_OK == xml::GetAttribute(pIElem, g_cbIsWizard97, &bstrIsWizard97, true)) {
		// ist dieser Wizard vom neuen Typ?
			m_fIsWizard97 = (0 != wcstol(bstrIsWizard97, NULL, 10)) ? true : false;
		}

	// alle ElementDaten behandlen
	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(xml::GetEnumNode (pIElem, Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			if (FAILED(v.ChangeType (VT_UNKNOWN)))
				continue;

		__Interface<xml::IXMLDOMNode> Node (V_UNKNOWN(&v));
		CComBSTR bstrNodeName;
		DOMNodeType rgType;

			THROW_FAILED_HRESULT(Node -> get_baseName (&bstrNodeName));
			THROW_FAILED_HRESULT(Node -> get_nodeType (&rgType));

			if (!bstrNodeName)
				continue;		// Kommentar 

		// Namen der Sequence einlesen
		CComBSTR bstrValue;

			if (!wcscmp (g_cbName, bstrNodeName)) {
			// Name gegeben
				_ASSERTE(NODE_ELEMENT == rgType);
				if (SUCCEEDED(Node -> get_text (&bstrValue))) 
					m_bstrName = bstrValue;
				continue;
			}

		// ggf. Namen, unter dem zu speichern/laden ist einlesen
			if (!wcscmp (g_cbSaveAs, bstrNodeName)) {
			// Name gegeben
				_ASSERTE(NODE_ELEMENT == rgType);
				if (SUCCEEDED(Node -> get_text (&bstrValue))) 
					m_bstrSaveAs = bstrValue;
				_ASSERTE(m_bstrName.Length() > 0);		// Name kommt immer vor SaveAs
				continue;
			}

		// ggf. entwas ausführlicher Beschreibung des Ganzen lesen
			if (!wcscmp (g_cbDescriptionL, bstrNodeName)) {
				_ASSERTE(NODE_ELEMENT == rgType);
				if (SUCCEEDED(Node -> get_text (&bstrValue))) 
					m_bstrDesc = bstrValue;
				continue;
			}
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Initialisierung des ClsId-Feldes
HRESULT CCalClsId::InitClsIds(long lSize)
{
	_ASSERTE(0 != lSize);
	COM_TRY {
	// alles nochmal freigeben
		DELETE_OBJ(m_pClsIds);
		DELETE_OBJ(ppElems);
		FreeActions();
		FreeInitData();
		DELETE_OBJ(m_pvInitData);

	// Felder neu anlegen
		m_pClsIds = new CLSID [lSize];
		m_pvInitData = new VARIANT [lSize];
		ppElems = new const CLSID *[lSize];
		ppActions = new const IUnknown *[lSize];
		ppvData = new const VARIANT *[lSize];
		ppMkData = new BSTR [lSize];
		ppHeaderTitle = new BSTR [lSize];
		ppHeaderSubTitle = new BSTR [lSize];

		for (long i = 0; i < lSize; ++i) {
			ppElems[i] = &m_pClsIds[i];
			VariantInit(&m_pvInitData[i]);
			ppvData[i] = &m_pvInitData[i];
			ppActions[i] = NULL;
			const_cast<BSTR>(ppMkData[i]) = NULL;
			const_cast<BSTR>(ppHeaderTitle[i]) = NULL;
			const_cast<BSTR>(ppHeaderSubTitle[i]) = NULL;
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Freigeben evtl. instantiierter PropertyActions
void CCalClsId::FreeActions()
{
	if (NULL != ppActions) {
		for (long i = 0; i < cElems; ++i) {
			if (NULL != ppActions[i]) {
				const_cast<IUnknown *>(ppActions[i]) -> Release();
				ppActions[i] = NULL;
			}
		}
		delete ppActions;
		ppActions = NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Freigeben evtl. existierender zusätzlicher Daten
void CCalClsId::FreeInitData()
{
	if (NULL != ppvData) {
		for (long i = 0; i < cElems; ++i) {
			if (NULL != ppvData[i]) {
				VariantClear(const_cast<VARIANT *>(ppvData[i]));
				ppvData[i] = NULL;
			}
		}
		delete ppvData;
		ppvData = NULL;
	}
	if (NULL != ppMkData) {
		for (long i = 0; i < cElems; ++i) {
			if (NULL != ppMkData[i]) {
				SysFreeString(const_cast<BSTR>(ppMkData[i]));
				const_cast<BSTR>(ppMkData[i]) = NULL;
			}
		}
		delete const_cast<BSTR *>(ppMkData);
		ppMkData = NULL;
	}
	if (NULL != ppHeaderTitle) {
		for (long i = 0; i < cElems; ++i) {
			if (NULL != ppHeaderTitle[i]) {
				SysFreeString(const_cast<BSTR>(ppHeaderTitle[i]));
				const_cast<BSTR>(ppHeaderTitle[i]) = NULL;
			}
		}
		delete const_cast<BSTR *>(ppHeaderTitle);
		ppHeaderTitle = NULL;
	}
	if (NULL != ppHeaderSubTitle) {
		for (long i = 0; i < cElems; ++i) {
			if (NULL != ppHeaderSubTitle[i]) {
				SysFreeString(const_cast<BSTR>(ppHeaderSubTitle[i]));
				const_cast<BSTR>(ppHeaderSubTitle[i]) = NULL;
			}
		}
		delete const_cast<BSTR *>(ppHeaderSubTitle);
		ppHeaderSubTitle = NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Eine GeoKomponente instantiieren und initialisieren
HRESULT CCalClsId::LoadPropertyAction (IPropertyActionSequence *pISeq, 
	BSTR bstrProgId, CComVariant *pvInitData, BSTR bstrMkData,
	BSTR bstrHeaderTitle, BSTR bstrHeaderSubTitle)
{
	COM_TRY {
	// ClassID aus Registry besorgen
	WPropertyAction WAct;

		if (NULL != bstrMkData && ::SysStringLen(bstrMkData) > 0) {
		CComBSTR bstrDisplayName (bstrProgId);

			bstrDisplayName.Append(L":");
			bstrDisplayName.AppendBSTR(bstrMkData);

		BIND_OPTS bindOpts;

			bindOpts.cbStruct = sizeof(BIND_OPTS);
			THROW_FAILED_HRESULT(::CoGetObject(bstrDisplayName, &bindOpts, WAct.GetIID(), WAct.ppv()));
		}
		else {
		CIID clsID (bstrProgId, CIID::INITCIID_InitFromProgId);

			if (!clsID) 
				return E_INVALIDARG;		// nichts gefunden

		// Objekt instantiieren
			WAct = WPropertyAction(clsID);		// throws hr
		}

	// Objekt initialisieren
	WPropertyAction2 Init2;

		USES_CONVERSION;
		if (SUCCEEDED(WAct -> QueryInterface(Init2.ppi()))) {
			if (m_DataIn.IsValid()) {
			// ggf. globale Daten gegeben
				if (NULL != pvInitData && V_ISBSTR(pvInitData) && ::SysStringLen(V_BSTR(pvInitData)) > 0) {
				// komponentenspezifische Daten zum globalen Kontext hinzufügen
				FORMATETC c_feProgID = 	{
						RegisterClipboardFormat (OLE2A(bstrProgId)),			// CLIPFORMAT cf
						NULL,										// DVTARGETDEVICE *ptd
						DVASPECT_CONTENT,							// DWORD dwAspect
						-1,											// LONG lindex	
						TYMED_ISTREAM,								// DWORD tymed
					};

				CComVariant vInit;

					if (S_OK != GetVariantData(m_DataIn, &c_feProgID, &vInit)) {
					// nur hinzufügen, wenn nichts diesbezügliches im globalen Kontext 
					// enthalten ist
						THROW_FAILED_HRESULT(SetVariantData(*pvInitData, m_DataIn, &c_feProgID));
					}
				}
				THROW_FAILED_HRESULT(Init2 -> InitFromData (m_DataIn, false, 0L));
			}
			else if (NULL != pvInitData && V_ISBSTR(pvInitData) && ::SysStringLen(V_BSTR(pvInitData)) > 0) {
			// ggf. mit komponentenspezifischen Daten initialisieren
			WDataObject InitData (CLSID_DataTransferObject);
			FORMATETC c_feProgID = 	{
					RegisterClipboardFormat (OLE2A(bstrProgId)),			// CLIPFORMAT cf
					NULL,										// DVTARGETDEVICE *ptd
					DVASPECT_CONTENT,							// DWORD dwAspect
					-1,											// LONG lindex	
					TYMED_ISTREAM,								// DWORD tymed
				};

				THROW_FAILED_HRESULT(SetVariantData(*pvInitData, InitData, &c_feProgID));
				THROW_FAILED_HRESULT(Init2 -> InitFromData (InitData, false, 0L));
			}
			else
				Init2.Assign(NULL);		// InitNew rufen
		}

	// ggf. blanko-Initialisierung
		if (!Init2.IsValid()) {
		WPersistStreamInit Init (WAct);		// throws hr;
		HRESULT hr = Init -> InitNew();

			if (FAILED(hr)) {
				if (hr != E_ABORT)
					return hr;
				return S_FALSE;			// darf mit E_ABORT fehlschlagen
			}
		}

	// ggf. header initialisieren
	WPropertyAction3 InitHdr;

		if (SUCCEEDED(WAct -> QueryInterface(InitHdr.ppi()))) {
			if (NULL != bstrHeaderTitle) {
				THROW_FAILED_HRESULT(InitHdr -> SetHeaderTitle(OLE2A(bstrHeaderTitle)));
				if (NULL != bstrHeaderSubTitle)
				{
					THROW_FAILED_HRESULT(InitHdr -> SetHeaderSubTitle(
						OLE2A(bstrHeaderSubTitle)));
				}
			}
		}

	// zur Sequence hinzufügen
		THROW_FAILED_HRESULT(pISeq -> AddAction (WAct));
		
	} COM_CATCH;
	return S_OK;
}

HRESULT CCalClsId::LoadPropertyActionsFromRegistry (
	REFGUID rGuid, xml::IXMLDOMNode *pIElem, IPropertyAction **ppIAct)
{
	TEST_OUT_PARAM(ppIAct);

	USES_CONVERSION;
	COM_TRY {
	// diverse Infos lesen
	HKEY hRootKey = NULL;
	CComBSTR bstrKey;
	CComBSTR bstrHeaderTitle;
	CComBSTR bstrHeaderSubTitle;
	__Interface<xml::IXMLDOMNode> ErrorInfo;

		THROW_FAILED_HRESULT(GetRegistryLoadInfo (pIElem, &hRootKey, &bstrKey, 
			ErrorInfo.ppi(), &bstrHeaderTitle, &bstrHeaderSubTitle));

	// Objekte erzeugen, initialisieren und zur Sequence hinzufügen
	WPropertyActionSequence Seq (rGuid);	// Objekt instantiieren

	// Registrierte Pages enumerieren
	HKEY hKey = NULL;
	DWORD i = 0, dwCnt = 0;
	char cbEnumKey[_MAX_PATH];
	DWORD retCode = RegOpenKeyEx (hRootKey, OLE2A(bstrKey), 0L, KEY_READ, &hKey);

		if (retCode == ERROR_SUCCESS) {
		// alle registrierten Einträge durchgehen
			while (RegEnumKey (hKey, i, cbEnumKey, _MAX_PATH) == ERROR_SUCCESS) {
			// evtl. Fehler ignorieren
				if (SUCCEEDED(LoadPropertyAction (Seq, CComBSTR(cbEnumKey),
						NULL, NULL, bstrHeaderTitle, bstrHeaderSubTitle)))
				{
					dwCnt++;
				}
				i++;
			}

		// Schlüssel wieder abschließen
			RegCloseKey (hKey);   // Close the key handle.
		}

		if (0 == dwCnt) 
			return ShowErrorInfo (ErrorInfo);

	// die neu erzeugte Sequence zurückliefern
	WPropertyAction PropAct (Seq);

		*ppIAct = PropAct.detach();
		
	} COM_CATCH;
	return S_OK;
}

HRESULT CCalClsId::LoadPropertyActionsDirect (
	REFGUID rGuid, xml::IXMLDOMNode *pIElem, int iLevel, IPropertyAction **ppIAct)
{
	TEST_OUT_PARAM(	ppIAct);

	USES_CONVERSION;
	COM_TRY {
	// Objekte erzeugen, initialisieren und zur Sequence hinzufügen
	WPropertyActionSequence Seq (rGuid);	// Objekt instantiieren

	// ggf. hat diese Sequence eine eigene InitInfo
	__Interface<xml::IXMLDOMElement> Elem (pIElem);
	CComVariant vSeqInitData;

		if (S_OK == GetInitInfo(Elem, &vSeqInitData)) {
		// ggf. über PropertyBag initialisieren
		WPropertyAction2 InitSeq;

			if (SUCCEEDED(Seq -> QueryInterface(InitSeq.GetIID(), InitSeq.ppv())) &&
				SUCCEEDED(vSeqInitData.ChangeType(VT_BSTR))) 
			{
			// hat Initialisierungsdaten und versteht auch welche
			CIID SeqGuid (rGuid);
			WDataObject InitData (CLSID_DataTransferObject);
			FORMATETC c_feProgID = 	{
					RegisterClipboardFormat (SeqGuid.ProgID().c_str()),	// CLIPFORMAT cf
					NULL,										// DVTARGETDEVICE *ptd
					DVASPECT_CONTENT,							// DWORD dwAspect
					-1,											// LONG lindex	
					TYMED_ISTREAM,								// DWORD tymed
				};

				THROW_FAILED_HRESULT(SetVariantData(vSeqInitData, InitData, &c_feProgID));
				THROW_FAILED_HRESULT(InitSeq -> InitFromData (InitData, false, 0L));
			}
		}
		else {
		// ansonsten normal initialisieren
		HRESULT hr = WPersistStreamInit(Seq) -> InitNew();

			if (FAILED(hr)) {
				if (E_ABORT != hr)
					return hr;
				return S_FALSE;		// darf mit E_ABORT fehlschlagen
			}
		}

	// Geocomponenten einlesen
	__Interface<xml::IXMLDOMNodeList> Nodes;
	long lCnt = 0;

		THROW_FAILED_HRESULT(Elem -> raw_getElementsByTagName(CComBSTR(g_cbGeoComponent), Nodes.ppi()));
		THROW_FAILED_HRESULT(Nodes -> get_length(&lCnt));
		for (long lItem = 0; lItem < lCnt; ++lItem) {
		__Interface<xml::IXMLDOMNode> Node;
		CComBSTR bstrProgId, bstrLevel;

			THROW_FAILED_HRESULT(Nodes -> get_item(lItem, Node.ppi()));
			THROW_FAILED_HRESULT(xml::GetAttribute (Node, g_cbLevel, &bstrLevel));
			if (wcstol (bstrLevel, NULL, 10) > iLevel)
				continue;		// zuweit die Hierarchie hinunter geraten

			THROW_FAILED_HRESULT(xml::GetAttribute (Node, g_cbProgID, &bstrProgId));

#if defined(_DEBUG)
		// rekursive Geocomponenten müssen erstmal direkt geladen werden
		CComBSTR bstrLoad;

			THROW_FAILED_HRESULT(xml::GetAttribute(Node, g_cbLoad, &bstrLoad));
			_ASSERTE(bstrLoad == g_cbDirect);
#endif // defined(_DEBUG)

		// den Typ der Geocomponente bestimmen
		CComBSTR bstrType;

			THROW_FAILED_HRESULT(xml::GetAttribute(Node, g_cbType, &bstrType));
			if (bstrType == g_cbAction) {
			// 'normale' GeoComponente, also einfach laden
			CComBSTR bstrMkData;
			bool fHasMkData = false;

				if (SUCCEEDED(xml::GetAttribute (Node, g_cbMonikerData, &bstrMkData))) 
					fHasMkData = true;

			// ggf. Initialisierungsinfo einlesen
			CComVariant vInitData;
			bool fHasInitData = false;

				if (S_OK == GetInitInfo(Node, &vInitData)) {
					THROW_FAILED_HRESULT(vInitData.ChangeType(VT_BSTR));
					fHasInitData = true;
				}

			// ggf. HeaderTitle und HeaderSubTitle laden
			CComBSTR bstrHeaderTitle, bstrHeaderSubTitle;
			bool fHasHeaderTitle = false, fHasHeaderSubTitle = false;

				if (SUCCEEDED(GetTagValue(Node, CComBSTR(g_cbHeaderTitle), &bstrHeaderTitle))) {
					fHasHeaderTitle = true;

				// SubTitle bringt nur mit Title Sinn
					if (SUCCEEDED(GetTagValue(Node, CComBSTR(g_cbHeaderSubTitle), &bstrHeaderSubTitle)))
						fHasHeaderSubTitle = true;
				}

				THROW_FAILED_HRESULT(LoadPropertyAction (Seq, bstrProgId, 
					fHasInitData ? &vInitData : NULL, 
					fHasMkData ? bstrMkData : NULL,
					fHasHeaderTitle ? bstrHeaderTitle : NULL,
					fHasHeaderSubTitle ? bstrHeaderSubTitle  : NULL));
			}
			else {
			// ist eine Subsequence
				_ASSERTE(bstrType == g_cbSequence);

			CIID Guid (bstrProgId, CIID::INITCIID_InitFromProgId);

				if (!Guid)
					_com_issue_error(E_INVALIDARG);

			WPropertyAction SubPropAct;
			HRESULT hr = LoadPropertyActionsDirect(Guid, Node, iLevel+1, SubPropAct.ppi());

				if (FAILED(hr))
					return hr;

			// die neue Sequence zur aktuellen Sequence hinzufügen
				THROW_FAILED_HRESULT(Seq -> AddAction(SubPropAct));
			}
		}

	// die neu erzeugte Sequence zurückliefern
	WPropertyAction PropAct (Seq);

		*ppIAct = PropAct.detach();
		
	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// HeaderTitle, HeaderSubTitle etc. herauslesen
HRESULT CCalClsId::GetTagValue (xml::IXMLDOMNode *pINode, BSTR bstrTagName, 
	BSTR *pbstrValue)
{
	BEGIN_OUT_PARAMS()
		OUT_PARAM(pbstrValue)
	END_OUT_PARAMS()

// SubNode LoadInfo laden
__Interface<xml::IXMLDOMNode> Node;

	if (S_OK != pINode -> raw_selectSingleNode(bstrTagName, Node.ppi()))
		return E_FAIL;		// Tag nicht gegeben

CComBSTR bstrValue;

	if (SUCCEEDED(Node -> get_text (&bstrValue))) 
		*pbstrValue = bstrValue.Detach();

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// LoadInfo aus einem Node herauslesen
HRESULT CCalClsId::GetRegistryLoadInfo (
	xml::IXMLDOMNode *pINode, HKEY *phRootKey, BSTR *pbstrKey, 
	xml::IXMLDOMNode **ppIErrorInfo, 
	BSTR *pbstrHeaderTitle, BSTR *pbstrHeaderSubTitle)
{
	BEGIN_OUT_PARAMS()
		OUT_PARAM(phRootKey)
		OUT_PARAM(pbstrKey)
		OUT_PARAM(ppIErrorInfo)
		OUT_PARAM(pbstrHeaderTitle)
		OUT_PARAM(pbstrHeaderSubTitle)
	END_OUT_PARAMS()

	COM_TRY {
	// Muß aus Registry geladen werden
#if defined(_DEBUG)
	CComBSTR bstrLoadFrom;

		THROW_FAILED_HRESULT(xml::GetAttribute(pINode, g_cbLoad, &bstrLoadFrom));
		_ASSERTE(bstrLoadFrom == g_cbRegistry);
#endif // defined(_DEBUG)

	// SubNode LoadInfo laden
	__Interface<xml::IXMLDOMNode> Node;

		THROW_FAILED_HRESULT(pINode -> raw_selectSingleNode(CComBSTR(g_cbLoadInfo), Node.ppi()));		// wenn LoadInfo nicht gegeben ist, dann ists ein Fehler

	// RegistryRootKey einlesen
	CComBSTR bstrReg;

		if (SUCCEEDED(xml::GetAttribute(Node, g_cbRegistryRoot, &bstrReg, true))) {
			if (bstrReg == g_cbHKCR)
				*phRootKey = HKEY_CLASSES_ROOT;
			else if (bstrReg == g_cbHKCU)
				*phRootKey = HKEY_CURRENT_USER;
			else if (bstrReg == g_cbHKLM)
				*phRootKey = HKEY_LOCAL_MACHINE;
			else
				return E_INVALIDARG;
		}

	// RegistryPath einlesen
		THROW_FAILED_HRESULT(xml::GetAttribute(Node, g_cbRegistryPath, CLEARED(&bstrReg)));
		*pbstrKey = bstrReg.Detach();

	// evtl. existierende ErrorInfo einlesen
	__Interface<xml::IXMLDOMNode> ErrorNode;

		if (S_OK == Node -> raw_selectSingleNode(CComBSTR(g_cbErrorInfo), ErrorNode.ppi()))
			*ppIErrorInfo = ErrorNode.detach();

		if (SUCCEEDED(GetTagValue(Node, CComBSTR(g_cbHeaderTitle), pbstrHeaderTitle)))
			GetTagValue(Node, CComBSTR(g_cbHeaderSubTitle), pbstrHeaderSubTitle);

	} COM_CATCH;
	return S_OK;
}
	
///////////////////////////////////////////////////////////////////////////////
// Fehlermeldung anzeigen, wenn keine Objekte gefunden wurden
HRESULT CCalClsId::ShowErrorInfo (xml::IXMLDOMNode *pINode)
{
	USES_CONVERSION;
	COM_TRY {
	// keine registrierten PropertyActions gefunden
	bool fExpandName = true;
	CComBSTR bstrCaption;
	CComBSTR bstrPrompt;

		if (NULL != pINode) {
		CComBSTR bstrExpand;

			if (S_OK == xml::GetAttribute(pINode, g_cbExpandName, &bstrExpand) && 0 == _wtol(bstrExpand)) 
				fExpandName = false;
			GetErrorStrings (pINode, &bstrCaption, &bstrPrompt);	// Fehler ignorieren
		}

	// ggf. Standardmeldungen anzeigen
	HINSTANCE hTRiAS = GetModuleHandle(NULL);

		if (0 == bstrCaption.Length())
			bstrCaption.LoadString(hTRiAS, IDS_BADREGISTRATION_CAP);
		if (0 == bstrPrompt.Length())
			bstrPrompt.LoadString(hTRiAS, IDS_BADREGISTRATION);

	// Message anzeigen
		if (fExpandName) {
			VMessageBox (NULL, FakeTRiASName(OLE2A(bstrCaption), g_cbTRiAS).c_str(), 
				ExclamationIcon|OkayButton, OLE2A(bstrPrompt), g_cbTRiAS);
		}
		else {
			VMessageBox (NULL, OLE2A(bstrCaption), ExclamationIcon|OkayButton, OLE2A(bstrPrompt));
		}

	} COM_CATCH;
	return E_ABORT;		// immer Fehler liefern
}

HRESULT CCalClsId::GetErrorStrings (xml::IXMLDOMNode *pINode, BSTR *pbstrCaption, BSTR *pbstrPrompt)
{
__Interface<xml::IXMLDOMNode> Node;

	if (S_OK == pINode -> raw_selectSingleNode(CComBSTR(g_cbCaption), Node.ppi()))
		RETURN_FAILED_HRESULT(Node -> get_text(pbstrCaption));

	if (S_OK == pINode -> raw_selectSingleNode(CComBSTR(g_cbPrompt), Node.ppi()))
		RETURN_FAILED_HRESULT(Node -> get_text(pbstrPrompt));

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ggf. exitierende Initialisierungsinfo laden
HRESULT CCalClsId::GetInitInfo(xml::IXMLDOMNode *pINode, VARIANT *pvInitData)
{
	BEGIN_TEST_PARAMS()
		IN_PARAM(pINode)
		OUT_PARAM(pvInitData)
	END_TEST_PARAMS()

HRESULT hr = S_FALSE;

	COM_TRY {
	__Interface<xml::IXMLDOMNode> Node;

		if (S_OK == pINode -> raw_selectSingleNode(CComBSTR(g_cbInitInfo), Node.ppi())) {
		// InitInfo ist gegeben
		__Interface<xml::IXMLDOMNamedNodeMap> NodeMap;

			THROW_FAILED_HRESULT(Node -> get_attributes(NodeMap.ppi()));

		// alle Attribute durgehen und in einem StringPair-Objekt ablegen
		WComposeStringPairs Pairs (CLSID_ParseStringPairs);
		long lCnt = 0;

			THROW_FAILED_HRESULT(NodeMap -> get_length(&lCnt));
			for (long lItem = 0; lItem < lCnt; ++lItem) {
			// nächstes Attribut holen
				THROW_FAILED_HRESULT(NodeMap -> get_item(lItem, Node.ppi()));

			CComBSTR bstrKey;
			CComBSTR bstrValue;

				THROW_FAILED_HRESULT(Node -> get_baseName(&bstrKey));
				THROW_FAILED_HRESULT(Node -> get_text(&bstrValue));
				THROW_FAILED_HRESULT(Pairs -> SetValue(bstrKey, bstrValue, VARIANT_TRUE));
			}

		// jetzt Zeichenkette für die Initialisierung erzeugen
		CComBSTR bstr(g_cbPAPrefix);		// Data müssen mit ";PropActData" anfangen
		CComBSTR bstrInitString;

			THROW_FAILED_HRESULT(Pairs -> get_ComposedData(CComBSTR(g_cbInitPattern), &bstrInitString));

			bstr.AppendBSTR(bstrInitString);
			V_VT(pvInitData) = VT_BSTR;
			V_BSTR(pvInitData) = bstr.Detach();

			hr = S_OK;
		}

	} COM_CATCH;
	return hr;
}

#endif // defined(_USE_XML_GEOCOMPONENTS)
