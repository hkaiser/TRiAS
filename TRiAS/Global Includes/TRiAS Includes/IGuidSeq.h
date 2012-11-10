// Interface, überwelches eine geordnete Menge von Guid's geliefert wird
// File: IGUIDSEQ.H

#if !defined(_IGUIDSEQ_H)
#define _IGUIDSEQ_H

///////////////////////////////////////////////////////////////////////////////
// counted array of CLSID's
#if !defined(_CALCLSID_DATA)
#define _CALCLSID_DATA
typedef struct tagCALPCLSID {
	ULONG cElems;			// Anzahl der CLSID's
	const CLSID **ppElems;	// Feld von Pointern auf CLSID's
	const IPropertyAction **ppActions;	// Feld von bereits instantiierten PropertyActions
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	const VARIANT **ppvData;			// evtl. Initialisierungsdaten für PropertyActions
#endif // _TRIAS_OLDIMPLEMTATION1
} CALPCLSID;
#endif // _CALCLSID_DATA

///////////////////////////////////////////////////////////////////////////////
#undef INTERFACE
#define INTERFACE IGetGuidSequence

// 0796387D-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IGetGuidSequence, 0x0796387DL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
DECLARE_INTERFACE_(IGetGuidSequence, IUnknown)
{
// *** IUnknown methods
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj) PURE;
	STDMETHOD_ (ULONG, AddRef) (THIS) PURE;
	STDMETHOD_ (ULONG, Release) (THIS) PURE;

// *** IGetGuidSequence methods
	STDMETHOD(Initialize) (THIS_ HKEY hKey) PURE;
	STDMETHOD(GetGuidSequence) (THIS_ ULONG *pulCnt, const CLSID **ppGuids) PURE;
};
typedef IGetGuidSequence *LPGETGUIDSEQUENCE;

#endif // _IGUIDSEQ_H
