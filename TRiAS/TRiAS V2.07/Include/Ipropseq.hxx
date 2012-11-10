// Eine Folge von abzuarbeitenden IPropertyActions ----------------------------
// File: IPROPSEQ.H

#if !defined(_IPROPSEQ_H)
#define _IPROPSEQ_H

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
} CALPCLSID;
#endif // _CALCLSID_DATA

#undef INTERFACE
#define INTERFACE IPropertyActionSequence

///////////////////////////////////////////////////////////////////////////////
// 0796381B-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IPropertyActionSequence, 0x0796381BL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IPropertyActionSequence, IUnknown)
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
};
typedef IPropertyActionSequence *LPPROPERTYACTIONSEQUENCE;

#endif // _IPROPSEQ_H
