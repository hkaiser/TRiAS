// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.06.99 20:30:54
//
// @doc
// @module ImportFromXml.cpp | Import Metadata from Xml-format (*.txc)

#include "idntsdbp.hxx"

#include <FormatString.h>
#include <errinstx.hxx>

#include "identres.h"
#include "identsdb.hxx"
#include "Strings.h"

//using namespace xml;

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumVARIANT);

void CIdentsDBExtension::ShowXMLError (xml::IXMLDOMParseError *pIError)
{
	COM_TRY {
	ResString resCap (ResID (IDS_SHOWXMLERROR_CAP, &RF()), 128);
	ResString resText (ResID(IDS_SHOWXMLERROR, &RF()), 255);
	os_string strT;
	CComBSTR bstrReason;
	LONG lLine = 0, lLinePos = 0;

		THROW_FAILED_HRESULT(pIError -> get_reason (&bstrReason));
		THROW_FAILED_HRESULT(pIError -> get_line (&lLine));
		Format (strT, resText, lLine, bstrReason);
	
	MessBox mb (resCap, strT.c_str(), MVWind());

		mb.SetType (OkayButton);
		mb.Show();

	} COM_CATCH_NORETURN;
}

void CIdentsDBExtension::ShowBadTXCFile (LPCSTR pcFName)
{
ResString resCap (ResID (IDS_SHOWXMLERROR_CAP, &RF()), 128);
ResString resText (ResID (IDS_BADTXCFILE, &RF()), 255);
os_string strT;

	Format (strT, resText, pcFName, g_cbTRiAS);

MessBox mb (resCap, strT.c_str(), MVWind());

	mb.SetType (OkayButton);
	mb.Show();
}

bool CIdentsDBExtension::ImportFromXml (
	LPCSTR pcFile, IProgressIndicator *pIStatus, HPROJECT hPr, 
	bool fKeepExisting, bool fRejectUnused, bool fFirst) 
{
	USES_CONVERSION;
	COM_TRY {
	// Dokument einlesen
	__Interface<xml::IXMLDOMDocument> Doc;
	
		if (FAILED(Doc.CreateInstance (CLSID_DOMDocument))) {
		// kein XMLDOM-Parser installiert
		ResString resCap (ResID (IDS_SHOWXMLERROR_CAP, &RF()), 128);
		ResString resText (ResID(IDS_NOXMLDOMPARSER, &RF()), 255);
		os_string strT;

			Format (strT, resText, g_cbTRiAS);

		MessBox mb (resCap, strT.c_str(), MVWind());

			mb.SetType (OkayButton);
			mb.Show();
			return false;
		}

	VARIANT_BOOL fSuccess = VARIANT_FALSE;

		THROW_FAILED_HRESULT(Doc -> put_validateOnParse (VARIANT_TRUE));
		THROW_FAILED_HRESULT(Doc -> raw_load (CComVariant(pcFile), &fSuccess));
		if (!fSuccess) {
		__Interface<xml::IXMLDOMParseError> spError;

			THROW_FAILED_HRESULT(Doc -> get_parseError(spError.ppi()));
			ShowXMLError (spError);
			return false;
		}

	// Import beginnen
	__Interface<xml::IXMLDOMElement> Root;

		THROW_FAILED_HRESULT(Doc -> get_documentElement (Root.ppi()));

	CComBSTR bstrRootName;

		THROW_FAILED_HRESULT(Root -> get_tagName (&bstrRootName));
		if (wcscmp (A2OLE(g_cbTRiASMetadata), bstrRootName)) {
			ShowBadTXCFile (pcFile);
			return false;
		}

		THROW_FAILED_HRESULT(ImportMetaData (pcFile, pIStatus, Root, hPr, fKeepExisting, fRejectUnused, fFirst));

	} COM_CATCH_RETURN(false);
	return true;
}

HRESULT CIdentsDBExtension::ImportMetaData (
	LPCSTR pcFile, IProgressIndicator *pIStatus, xml::IXMLDOMElement *pIData, 
	HPROJECT hPr, bool fKeepExisting, bool fRejectUnused, bool fFirst)
{
	USES_CONVERSION;
	COM_TRY {
	__Interface<xml::IXMLDOMNodeList> Nodes;

		THROW_FAILED_HRESULT(pIData -> get_childNodes (Nodes.ppi()));

	WEnumVARIANT Enum;
	CComVariant v;
	LONG ulCnt = 0;
	LPOLESTR poleStr = A2OLE(g_cbObjectClass);

		THROW_FAILED_HRESULT(Nodes -> get__newEnum (Enum.ppu()));
		THROW_FAILED_HRESULT(Nodes -> get_length (&ulCnt));
		if (0 < ulCnt) {
			THROW_FAILED_HRESULT(InitializeImportStatus (pIStatus, pcFile, ulCnt, fFirst));
		}

		ulCnt = 0;
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			if (FAILED(v.ChangeType (VT_UNKNOWN)))
				continue;

		// Status aktualisieren
			if (pIStatus -> WasCanceled())
				break;
			pIStatus -> SetPosition (ulCnt++);

		__Interface<xml::IXMLDOMNode> Node (V_UNKNOWN(&v));
		CComBSTR bstrNodeName;

			THROW_FAILED_HRESULT(Node -> get_baseName (&bstrNodeName));
			if (!wcscmp (poleStr, bstrNodeName))
			{
				THROW_FAILED_HRESULT(ImportObjectClass (pcFile, Node, hPr, fKeepExisting, fRejectUnused));
			}
		}

	} COM_CATCH;
	return S_OK;
}

// Helperfunktionen
#pragma warning (disable: 4101)		// e: Variable defined, but not used
HRESULT GetAttribute (xml::IXMLDOMNode *pINode, BSTR bstrItem, BSTR *pbstrText, bool fMayFail = false)
{
	TX_ASSERT(NULL != pbstrText);
	COM_TRY {
	__Interface<xml::IXMLDOMNamedNodeMap> Attribs;
	__Interface<xml::IXMLDOMNode> Node;

		THROW_FAILED_HRESULT(pINode -> get_attributes (Attribs.ppi()));
		if (SUCCEEDED(Attribs -> raw_getNamedItem (bstrItem, Node.ppi()))) {
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

// eine Objektklasse importieren
HRESULT CIdentsDBExtension::ImportObjectClass (
	LPCSTR pcFile, xml::IXMLDOMNode *pINode, HPROJECT hPr, bool fKeepExisting, bool fRejectUnused)
{
	USES_CONVERSION;
	COM_TRY {
	// Objektklasse importieren
	INT_PTR lIdentAttrib = 0L;

	// zusammengesammelte Infos
	CComBSTR bstrOKS;
	CComBSTR bstrName;
	CComBSTR bstrDesc;
	CComBSTR bstrTableName;
	__Interface<xml::IXMLDOMNode> Feats;
	bool fHasOKS = false;
	bool fHasName = false;
	bool fHasDesc = false;
	bool fHasTableName = false;
	bool fHasFeats = false;

	// Objekteigenschaftsbeschreibungen zusammensuchen
	CComBSTR bstrIdent;

		if (SUCCEEDED(GetAttribute (pINode, CComBSTR(g_cbIdent), &bstrIdent))) {
			if (L'0' == bstrIdent[0] && (L'x' == bstrIdent[1] || L'X' == bstrIdent[1]))
				lIdentAttrib = (INT_PTR)wcstoul (bstrIdent, NULL, 16);
			else
				lIdentAttrib = (INT_PTR)wcstoul (bstrIdent, NULL, 10);
		}

	// alle ElementDaten behandlen
	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(GetEnumNode (pINode, Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			if (FAILED(v.ChangeType (VT_UNKNOWN)))
				continue;

		__Interface<xml::IXMLDOMNode> Node (V_UNKNOWN(&v));
		CComBSTR bstrNodeName;
		DOMNodeType rgType;

			THROW_FAILED_HRESULT(Node -> get_baseName (&bstrNodeName));
			THROW_FAILED_HRESULT(Node -> get_nodeType (&rgType));

		LPCSTR pcNodeName = OLE2A(bstrNodeName);
		CComBSTR bstrValue;

			if (!strcmp (g_cbOKS, pcNodeName)) {
			// OKS gegeben
				TX_ASSERT(NODE_ELEMENT == rgType);
				if (SUCCEEDED(Node -> get_text (&bstrValue))) {
					bstrOKS = bstrValue;
					fHasOKS = true;
				}
			}
			else if (!strcmp (g_cbName, pcNodeName)) {
			// KurzText gegeben
				TX_ASSERT(NODE_ELEMENT == rgType);

			VARIANT_BOOL fIsDefault = VARIANT_FALSE;
			CComBSTR bstrIsDefault;

				if (SUCCEEDED(GetAttribute (Node, CComBSTR(g_cbIsDefault), &bstrIsDefault, true))) {
					if (bstrIsDefault.Length() > 0)
						fIsDefault = (0 != _wtol(bstrIsDefault)) ? VARIANT_TRUE : VARIANT_FALSE;
				}
				if (!fIsDefault && SUCCEEDED(Node -> get_text (&bstrValue))) {
					bstrName = bstrValue;
					fHasName = true;
				}
			}
			else if (!strcmp (g_cbDescription, pcNodeName)) {
			// Langtext gegeben
				TX_ASSERT(NODE_ELEMENT == rgType);
				if (SUCCEEDED(Node -> get_text (&bstrValue))) {
					bstrDesc = bstrValue;
					fHasDesc = true;
				}
			}
			else if (!strcmp (g_cbTableName, pcNodeName)) {
			// TabellenName gegeben
				TX_ASSERT(NODE_ELEMENT == rgType);
				if (SUCCEEDED(Node -> get_text (&bstrValue))) {
					bstrTableName = bstrValue;
					fHasTableName = true;
				}
			}
			else if (!strcmp (g_cbObjectFeatures, pcNodeName)) {
			// Objekteigenschaften gegeben
				Feats = Node;
				fHasFeats = true;
			}
			else {
				ShowBadTXCFile (pcFile);
				return E_UNEXPECTED;
			}
		}

	// jetzt wirklich importieren
	HRESULT hr = E_FAIL;
	LPCSTR pcOKS = NULL;
	char cbOKS[64];

		if (fHasOKS) 
			pcOKS = OLE2A(bstrOKS);		// OKS gegeben
		else {
		// lIdentAttrib als OKS verwenden
			_ltoa (lIdentAttrib, cbOKS, 16);
			pcOKS = cbOKS;
		}

	INT_PTR lIdent = 0;

		THROW_FAILED_HRESULT(hr = IdentFromClassX (hPr, pcOKS, (ULONG *)&lIdent));
		if (S_OK != hr && fRejectUnused && !DEX_isIdentUsedEx(hPr, lIdent))
			return S_OK;		// nicht existierende nicht importieren

		if (S_FALSE == hr && (-1L == lIdent || !DEX_isIdentUsedEx(hPr, lIdent))) {
		// OKS existiert noch nicht: erzeugen

			lIdent = -1L;
			if (!DEX_GetTRiASDataSourceEx(hPr)) {
			// keine TRiAS-Datenquelle, versuchen ¸ber Namen die Tabelle wiederzufinden
				if (fHasName || fHasTableName) {
					if (fHasName)	// Kurztext hat Vorrang
						lIdent = DEX_GetIdentFromClassNameEx(hPr, OLE2A(bstrName));
					if ((0 == lIdent || -1L == lIdent) && fHasTableName)
						lIdent = DEX_GetIdentFromClassNameEx(hPr, OLE2A(bstrTableName));

				// zu bestimmtem Ident den OKS speichern
					if (0 != lIdent && -1L != lIdent) {
					MODOBJCLASSCODE MOCC;

						INITSTRUCT(MOCC, MODOBJCLASSCODE);
						MOCC.ulIdent = lIdent;
						MOCC.pcClass = pcOKS;
						MOCC.fOverWrite = !fKeepExisting;
						hr = DEX_ModObjectClassCodeEx(hPr, MOCC);
						if (FAILED(hr) && E_ACCESSDENIED != hr)
							return hr;		// Fehler
					}
				} 
			} 

		// wenn immer noch kein Ident da ist, dann selbigen eben neu erzeugen
			if (0 == lIdent || -1L == lIdent)
				THROW_FAILED_HRESULT(IdentFromClassX (hPr, pcOKS, (ULONG *)&lIdent, true));
		}

	// nicht benutzte nicht importieren
		if (fRejectUnused && !DEX_isIdentUsedEx(hPr, lIdent)) 
			return S_OK;

	// Eintrag in TRiAS setzen
	PBDDATA pbdData;
	ErrInstall EI (WC_NOIDENT);
	bool fMustImport = false;

		INITSTRUCT (pbdData, PBDDATA);
		pbdData.pbdTyp = 'i';
		pbdData.pbdCode = lIdent;
	
	// Testen, ob dieser Eintrag bereits existiert
		if (!fKeepExisting || (EC_OKAY != DEX_GetPBDDataEx (hPr, pbdData))) {
		// jetzt Pbd schreiben
			pbdData.pbdKText = fHasName ? OLE2A(bstrName) : NULL;
			pbdData.pbdLText = fHasDesc ? OLE2A(bstrDesc) : NULL;

			if (NULL != pbdData.pbdKText || NULL != pbdData.pbdLText) {
				pbdData.pbdTemp = false;
				pbdData.pbdKTextLen = fHasName ? bstrName.Length() : 0;
				pbdData.pbdLTextLen = fHasDesc ? bstrDesc.Length() : 0;

			ErrCode RC = DEX_ModPBDDataEx (hPr, pbdData);

				fMustImport = (EC_OKAY == RC || WC_RETURN == RC) ? true : false;
				if (WC_RETURN == RC)
					lIdent = pbdData.pbdCode;	// Ident neu vergeben
			}
		}

	// ggf. zugehˆrige Objekteigenschaften importieren
		if (fMustImport) 
		{
			THROW_FAILED_HRESULT(ImportObjectFeatures (pcFile, lIdent, Feats, fKeepExisting));
		}

	} COM_CATCH;
	return S_OK;
}

HRESULT CIdentsDBExtension::ImportObjectFeatures (
	LPCSTR pcFile, INT_PTR lIdent, xml::IXMLDOMNode *pINode, bool fKeepExisting)
{
	COM_TRY {
	// alle ElementDaten behandlen
	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(GetEnumNode (pINode, Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			if (FAILED(v.ChangeType (VT_UNKNOWN)))
				continue;

		// eine Objekteigenschaft
		__Interface<xml::IXMLDOMNode> Node (V_UNKNOWN(&v));
		CComBSTR bstrNodeName;
		DOMNodeType rgType;

			THROW_FAILED_HRESULT(Node -> get_baseName (&bstrNodeName));
			THROW_FAILED_HRESULT(Node -> get_nodeType (&rgType));
			TX_ASSERT(NODE_ELEMENT == rgType);

		// Wenn der Node nicht "Feature" heiﬂt, dann ist was falsch
			USES_CONVERSION;
			if (strcmp (g_cbFeature, OLE2A(bstrNodeName))) {
				ShowBadTXCFile (pcFile);
				return E_UNEXPECTED;
			}

		// jetzt diese Objekteigenschaft importieren
			THROW_FAILED_HRESULT(ImportObjectFeature (pcFile, lIdent, Node, fKeepExisting));
		}

	} COM_CATCH;
	return S_OK;
}

// eine Objekteigenschaft importieren
HRESULT CIdentsDBExtension::ImportObjectFeature (
	LPCSTR pcFile, INT_PTR lIdent, xml::IXMLDOMNode *pINode, bool fKeepExisting)
{
	COM_TRY {
	HPROJECT hPr = DEX_GetObjectsProject(lIdent);

	WEnumVARIANT Enum;
	CComVariant v;
	CComBSTR bstrValue;

	CComBSTR bstrName;
	CComBSTR bstrDesc;
	bool fHasName = false;
	bool fHasDesc = false;
	int iLength = _MAX_PATH;
	int iType = 'a';

	// evtl. MCode
	INT_PTR lMCode = 0L;
	CComBSTR bstrMCode;

		if (SUCCEEDED(GetAttribute (pINode, CComBSTR(g_cbMCode), &bstrMCode))) {
			if (L'0' == bstrMCode[0] && (L'x' == bstrMCode[1] || L'X' == bstrMCode[1]))
				lMCode = wcstol (bstrMCode, NULL, 16);
			else
				lMCode = wcstol (bstrMCode, NULL, 10);
		}

		if (NULL != lMCode) {
		MAPMCODETOHANDLE MTH;
		INT_PTR lMappedMCode = 0L;
		BOOL fCreated = FALSE;

			INITSTRUCT(MTH, MAPMCODETOHANDLE);
			MTH.lIdent = lIdent;
			MTH.lMCode = lMCode;
			MTH.plHandle = &lMappedMCode;
			MTH.fCreate = true;
			MTH.pfCreated = &fCreated;
			if (DEX_MapOrCreateMCodeToHandle(hPr, MTH) && 0L != lMappedMCode)
				lMCode = lMappedMCode;
		}
		if (NULL == lMCode)
			lMCode = DEX_GetUniqueMCode();

	// einzelne Werte zusammensuchen
		USES_CONVERSION;
		THROW_FAILED_HRESULT(GetEnumNode (pINode, Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) {
			if (FAILED(v.ChangeType (VT_UNKNOWN)))
				continue;

		__Interface<xml::IXMLDOMNode> Node (V_UNKNOWN(&v));
		CComBSTR bstrNodeName;
		DOMNodeType rgType;

			THROW_FAILED_HRESULT(Node -> get_baseName (&bstrNodeName));
			THROW_FAILED_HRESULT(Node -> get_nodeType (&rgType));

		LPCSTR pcNodeName = OLE2A(bstrNodeName);

			if (!strcmp (g_cbName, pcNodeName)) {
			// Kurztext ist gegeben
				TX_ASSERT(NODE_ELEMENT == rgType);

			VARIANT_BOOL fIsDefault = VARIANT_FALSE;
			CComBSTR bstrIsDefault;

				if (SUCCEEDED(GetAttribute (Node, CComBSTR(g_cbIsDefault), &bstrIsDefault, true))) {
					if (bstrIsDefault.Length() > 0)
						fIsDefault = (0 != _wtol(bstrIsDefault)) ? VARIANT_TRUE : VARIANT_FALSE;
				}
				if (!fIsDefault && SUCCEEDED(Node -> get_text (&bstrValue))) {
				ResString resDefName (ResID (IDS_DEFAULTFEATURENAME, &RF()), 32);

					if (wcsncmp (bstrValue, A2OLE(resDefName.Addr()), resDefName.Len())) {		// hack f¸r 'altes' Format: 'Objekteigenschaft (%ld)'
						bstrName = bstrValue;
						fHasName = true;
					}
				}
			}
			else if (!strcmp (g_cbDescription, pcNodeName)) {
			// Langtext ist gegeben
				TX_ASSERT(NODE_ELEMENT == rgType);
				if (SUCCEEDED(Node -> get_text (&bstrValue))) {
					bstrDesc = bstrValue;
					fHasDesc = true;
				}
			}
			else if (!strcmp (g_cbLength, pcNodeName)) {
			// max. Attributl‰nge
				TX_ASSERT(NODE_ELEMENT == rgType);
				if (SUCCEEDED(Node -> get_text (&bstrValue))) {
				long iLen = _wtol(bstrValue);

					if (iLen > 0) iLength = iLen;
				}
			}
			else if (!strcmp (g_cbType, pcNodeName)) {
			// Typ der Objekteigenschaft ist gegeben
				TX_ASSERT(NODE_ELEMENT == rgType);
				if (SUCCEEDED(Node -> get_text (&bstrValue))) {
					if (bstrValue.Length() > 0)
						iType = towlower(bstrValue[0]);
					if (bstrValue.Length() > 1) {
						if ('r' == towlower(bstrValue[1]))
							iType |= MPReadOnlyFeatures;
					}
				}
			}
			else {
				ShowBadTXCFile (pcFile);
				return E_UNEXPECTED;
			}
		}
//		_ASSERTE(fHasName);		// Kurztext muﬂ gegeben sein

	// verhindern, daﬂ zwei Objekteigenschaften einen identischen Kurztext haben
	LONG lExistentMCode = fHasName ? DEX_GetMCodeFromFeatureNameEx(hPr, OLE2A(bstrName)) : -1;

		if (-1 == lExistentMCode || 0 == lExistentMCode) {
		// Erzeugen/Abgleichen einer Objekteigenschaft
		PBDMERKMALEX pbdData;
		ErrInstall EI (WC_NOMERKMAL);
		bool fMustImport = false;

			INITSTRUCT (pbdData, PBDMERKMALEX);
			pbdData.pbdTyp = 'm';
			pbdData.pbdCode = lMCode;
			pbdData.ipbdMTyp = iType;
			pbdData.ipbdMLen = iLength;
			pbdData.lIdent = lIdent;
		
		// Testen, ob dieser Eintrag bereits existiert
			if (!fKeepExisting || (EC_OKAY != DEX_GetPBDDataEx (hPr, pbdData))) {
			// jetzt Pbd schreiben
				USES_CONVERSION;
				pbdData.pbdKText = fHasName ? OLE2A(bstrName) : NULL;
				pbdData.pbdLText = fHasDesc ? OLE2A(bstrDesc) : NULL;

				if (NULL != pbdData.pbdKText || NULL != pbdData.pbdLText) {
					pbdData.pbdKTextLen = fHasName ? bstrName.Length() : 0;
					pbdData.pbdLTextLen = fHasDesc ? bstrDesc.Length() : 0;
					DEX_ModPBDDataEx (hPr, pbdData);
				}
			}
		}

	} COM_CATCH;
	return S_OK;
}
