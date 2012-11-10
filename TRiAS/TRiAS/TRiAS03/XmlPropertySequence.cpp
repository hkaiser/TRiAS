// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.12.2000 22:57:35 
//
// @doc
// @module XmlPropertySequence.cpp | Loading and executing PropSeq's from Xml

#include "trias03p.hxx"
#include "trias03.h"

#if defined(_USE_XML_GEOCOMPONENTS)

#include <Com/ComBool.h>

#include <xtsnguid.h>
#include <funcs03.h>
#include <CalClsId.h>
#include <triastlb.h>

#include <eieruhr.hxx>

#include "Strings.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "PropSeq.hxx"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(PropertyAction);
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(Storage);
DefineSmartInterface(Dispatch);
DefineSmartInterface(EnumFORMATETC);
DefineSmartInterface(ObjectWithSite);
DefineSmartInterface(TRiASDataObject);

///////////////////////////////////////////////////////////////////////////////
// Laden einer PropertySequence aus einer Xml-Resource
HRESULT InitPropertyActionSequence (
	LPCSTR pcRsc, LPCSTR pcModule, LPCSTR pcDesc, LPSTR pSaveAs, IStorage *pIStg, 
	IDataObject *pIDataIn, BOOL fLoadFromFile, IPropertyActionSequence **ppISeq)
{
	if (NULL == ppISeq) 
		return E_POINTER;
	*ppISeq = NULL;		// für alle Fälle

	USES_CONVERSION;
	COM_TRY {
	// zuerst Xml-Dokument laden
	WDispatch DocDisp;
	__Interface<TRiASCFG::ILoadXmlService> XmlService(TRiASCFG::CLSID_LoadXmlService);

		if (fLoadFromFile) {
			THROW_FAILED_HRESULT(XmlService -> LoadXmlFromFile(CComBSTR(pcRsc), DocDisp.ppi()));
		}
		else {
			if (NULL != pcModule) {	
			// ggf. aus anderem Modul laden
				THROW_FAILED_HRESULT(XmlService -> put_ResourceModule(CComBSTR(pcModule)));
			}
			THROW_FAILED_HRESULT(XmlService -> LoadXmlFromResource(CComBSTR(pcRsc), DocDisp.ppi()));
		}
				
	// Root des Documentes validieren
	__Interface<xml::IXMLDOMDocument> Doc (DocDisp);
	__Interface<xml::IXMLDOMElement> Root;

		THROW_FAILED_HRESULT(Doc -> get_documentElement(Root.ppi()));

	// Daten einlesen
	CCalClsId calPropSeqData (pIDataIn);
	HRESULT hr = calPropSeqData.InitDataFromXml (Root);

		if (FAILED(hr)) {
			if (E_ABORT == hr)
				return hr;
			THROW_FAILED_HRESULT(hr);
		}

	// das hier muß eine Sequence sein
		_ASSERTE(SEQTYPE_Sequence == calPropSeqData.GetSequenceType());

	// versuchen, alte Sequence zu laden
	WPropertyActionSequence Seq;

		_ASSERTE(NULL != pSaveAs);
		if ('\0' == pSaveAs[0])
			strcpy (pSaveAs, OLE2A(calPropSeqData.GetSaveName()));
		
		if (S_OK != LoadPropertySequence(pSaveAs, pIStg, 
			calPropSeqData.GetVersion(), Seq.ppi())) 
		{
		// wenn Status nicht geladen werden kann, dann neu initialisieren
			if (NULL == pcDesc)
				pcDesc = OLE2A(calPropSeqData.GetName());

		// GeoComponentSequence erzeugen
			THROW_FAILED_HRESULT(Seq.CreateInstance(calPropSeqData.GetSeqGuid()));

		// Rücksetzen der AktionsFolge
		WPersistStreamInit Init (Seq);		// throws hr

			THROW_FAILED_HRESULT(Init -> InitNew());
			THROW_FAILED_HRESULT(Seq -> SetDescription (pcDesc));
			THROW_FAILED_HRESULT(Seq -> SetVersion (OLE2A(calPropSeqData.GetVersion())));
			Seq -> SetIsWizard97 (CComBool(calPropSeqData.GetIsWizard97()));

		// hinzufügen der einzelnen Aktionen
			THROW_FAILED_HRESULT(Seq -> AddActionsByCLSID (calPropSeqData.GetInitInfo()));
		}
		*ppISeq = Seq.detach();

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Kopieren aller Elemente eines DataObject's in ein anderes
HRESULT CopyDataObject(IDataObject *pISrc, IDataObject *pIDst)
{
	COM_TRY {
	WEnumFORMATETC Enum;
	FORMATETC fe;

		THROW_FAILED_HRESULT(pISrc->EnumFormatEtc(DATADIR_GET, Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next(1, &fe, NULL); /**/) {
		STGMEDIUM stg;

			memset (&stg, 0, sizeof(STGMEDIUM));
			if (SUCCEEDED(pISrc -> GetData(&fe, &stg))) {
				if (FAILED(pIDst -> SetData (&fe, &stg, TRUE))) 
					ReleaseStgMedium (&stg);
			}
		}

	} COM_CATCH;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Laden und ausführen einer PropertySequence aus einer Xml-Resource
namespace {
// am Schluß CoFreeUnusedLibraries rufen
	class CFreeUpCom 
	{
	public:
		CFreeUpCom() {}
		~CFreeUpCom() { CoFreeUnusedLibraries(); }
	};
}

HRESULT RunPropertyActionSequence (
	HWND hWnd, LPCSTR pcRsc, LPCSTR pcModule, LPCSTR pcDesc, LPCSTR pcSaveAs, 
	IProgressIndicator *pIStatus, IDataObject *pIInData, IDataObject **ppIOutData, 
	BOOL fInitNew, IDataObject *pICtxData, BOOL fLoadFromFile)
{
CFreeUpCom FreeComWrapper;

	{
	HRESULT hr = S_OK;
	WStorage IStg;
	WPropertyActionSequence ISeq;
	char cbBuffer[64];

		cbBuffer[0] = '\0';
		{
		Window Wnd (hWnd);
		CEierUhr Wait(&Wnd);

		// evtl. Neuinitialisierung erzwingen
			if (!fInitNew && (GetKeyState (VK_SHIFT) >= 0 || GetKeyState (VK_CONTROL) >= 0))
				GetSubPropSeqStorage (IStg.ppi());

			if (NULL != pcSaveAs) {
				_ASSERTE(strlen(pcSaveAs) < sizeof(cbBuffer));
				strcpy (cbBuffer, pcSaveAs);
			}
			hr = InitPropertyActionSequence (pcRsc, pcModule, pcDesc, cbBuffer, 
				IStg, pIInData, fLoadFromFile, ISeq.ppi());
			if (FAILED(hr)) return hr;
		}

		if (NULL != pICtxData) {
		// ggf. Initialisierungsdaten für SequenceCtx übernehmen
		WDataObject Ctx;
		
			if (SUCCEEDED(ISeq->GetSequenceContext(Ctx.ppi()))) 
				CopyDataObject (pICtxData, Ctx);
		}

	// durchführen der gewünschten Aktion
		hr = ISeq -> DoActions (hWnd, pIStatus, pIInData, ppIOutData);
		if (FAILED(hr)) return hr;

	// Speichern der letzten Nutzerselektion
		return SavePropSeq (cbBuffer, ISeq, IStg);
	}
}

#endif // defined(_USE_XML_GEOCOMPONENTS)


