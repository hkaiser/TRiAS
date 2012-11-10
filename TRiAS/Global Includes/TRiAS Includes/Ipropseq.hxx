// @doc 
// @module Ipropseq.hxx | Eine Folge von abzuarbeitenden IPropertyActions

#if !defined(_IPROPSEQ_HXX__D6FF685E_F307_11D2_9BEE_F4F020524153__INCLUDED_)
#define _IPROPSEQ_HXX__D6FF685E_F307_11D2_9BEE_F4F020524153__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#if _MSC_VER < 1100 && !defined(DECLSPEC_UUID)
#define DECLSPEC_UUID()
#endif // _MSC_VER < 1100 && !defined(DECLSPEC_UUID)

///////////////////////////////////////////////////////////////////////////////
// forward declaration only
interface IProgressIndicator;
interface IPropertyAction;

///////////////////////////////////////////////////////////////////////////////
// counted array of CLSID's
#if !defined(_CALCLSID_DATA)
#define _CALCLSID_DATA
typedef struct tagCALPCLSID {
	ULONG cElems;						// Anzahl der CLSID's/PropActs
	const CLSID **ppElems;				// Feld von Pointern auf CLSID's
	const IPropertyAction **ppActions;	// Feld von bereits instantiierten PropertyActions
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	const VARIANT **ppvData;			// evtl. Initialisierungsdaten für PropertyActions
#endif // _TRIAS_OLDIMPLEMTATION1
	const BSTR *ppMkData;				// evtl. zusätzliche Monikerdaten
	const BSTR *ppHeaderTitle;			// evtl. zusätzliche HeaderTitle's
	const BSTR *ppHeaderSubTitle;		// evtl. zusätzliche HeaderSubTitle's
} CALPCLSID;
#endif // _CALCLSID_DATA

#undef INTERFACE
#define INTERFACE IPropertyActionSequence

///////////////////////////////////////////////////////////////////////////////
// 0796381B-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IPropertyActionSequence, 0x0796381BL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
interface DECLSPEC_UUID("0796381B-3123-101C-BB62-00AA0018497C")
IPropertyActionSequence : public IUnknown
{
// *** IUnknown methods
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
	STDMETHOD_ (ULONG, AddRef) (THIS) PURE;
	STDMETHOD_ (ULONG, Release) (THIS) PURE;

// *** IPropertyActionSequence methods
	STDMETHOD (SetDescription) (THIS_ LPCSTR pcDesc) PURE;
	STDMETHOD (AddAction) (THIS_ IPropertyAction *pIAct) PURE;
	STDMETHOD (AddActionsByCLSID) (THIS_ CALPCLSID *pcaClsIds) PURE;
	STDMETHOD (DoActions) (THIS_ HWND hParent, IProgressIndicator *pIStatus, 
			       IDataObject *pIData, IDataObject **ppOutData) PURE;
	STDMETHOD (GetDescription) (THIS_ LPSTR pDesc, ULONG ulLen, ULONG *pulWritten) PURE;
	STDMETHOD (RedoActions) (THIS_ HWND hParent, IProgressIndicator *pIStatus, 
					IDataObject *pIData, IDataObject **ppOutData) PURE;
	STDMETHOD (PrepareActions) (THIS_ HWND hParent, IDataObject *pIData) PURE;
	STDMETHOD (GetSequenceContext) (THIS_ IDataObject **ppIData) PURE;

// #HK010315
	STDMETHOD (GetVersion) (THIS_ LPSTR pDesc, ULONG ulLen, ULONG *pulWritten) PURE;
	STDMETHOD (SetVersion) (THIS_ LPCSTR pcDesc) PURE;
	STDMETHOD (SetIsWizard97) (THIS_ VARIANT_BOOL fIsWizard97) PURE;
	STDMETHOD (GetHeaderTitle) (THIS_ LPSTR pBuffer, ULONG wLen) PURE;	
	STDMETHOD (SetHeaderTitle) (THIS_ LPCSTR pcHeaderTitle) PURE;
	STDMETHOD (GetHeaderSubTitle) (THIS_ LPSTR pSubBuffer, ULONG wLen) PURE;	
	STDMETHOD (SetHeaderSubTitle) (THIS_ LPCSTR pcHeaderSubTitle) PURE;
};
typedef IPropertyActionSequence *LPPROPERTYACTIONSEQUENCE;

///////////////////////////////////////////////////////////////////////////////
// Bis dato bekannte Daten, die im Kontextobjekt gespeichert sein können

// Handle der Datenquelle, in welche evtl. neu erzeugte Objekte gespeichert 
// werden sollen. Wird als Variant(VT_I4) gespeichert.
// ClipBoardFormat
const char c_cbDataSourceHandle[] = "DataSourceHandle";

// FORMATETC
const FORMATETC c_feDataSourceHandle = {
	RegisterClipboardFormat (c_cbDataSourceHandle),	// CLIPFORMAT cf
	NULL,											// DVTARGETDEVICE *ptd
	DVASPECT_CONTENT,								// DWORD dwAspect
	-1,												// LONG lindex	
	TYMED_ISTREAM,									// DWORD tymed
};

#endif // !defined(_IPROPSEQ_HXX__D6FF685E_F307_11D2_9BEE_F4F020524153__INCLUDED_)
