// Verwaltung einer Abfolge von IPropertyActions ------------------------------
// File: PROPSEQ.HXX

#if !defined(_PROPSEQ_HXX)
#define _PROPSEQ_HXX

#include <Com/OleClientSiteNotImpl.h>
#include <Com/OleItemContainerSupport.h>

#include <ipropseq.hxx>

#include "propactb.hxx"
#include "triastrans.h"
#include "Strings.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(MultiProgressIndicator);
DefineSmartInterface(PropertyAction);
DefineSmartInterface(DataObject);
DefineSmartInterface(Moniker);

///////////////////////////////////////////////////////////////////////////////
// Streamversionen

// im SequenceStream selbst
#define PROPERTYACTION_FORMATVERSION	0x00100000L
#define MINOR_VERSION_MASK				0xFF

// vor dem SequenceStream zur Versionskontrolle mit dem XML Configfile
// ACHTUNG: mit ole2auto/propactseq.cpp synchronisieren
#define PROPERTYSEQUENCE_VERSION_0100			0x0100
#define PROPERTYSEQUENCE_LASTKNOWNVERSION		PROPERTYSEQUENCE_VERSION_0100
#define PROPERTYSEQUENCE_MINORVERSIONMASK		0xff
#define PROPERTYSEQUENCE_SIGNATURE				0x53505250		// PRPS

///////////////////////////////////////////////////////////////////////////////
// Objekt, welches die Abfolge von ProperyActions steuert 
class CPropertySequence : 
	public IClassProperty,
	public IPropertyAction,
	public IPropertyActionSequence,
	public IPersistStreamInit,
	public COleItemContainerSupport<CPropertySequence>,
	public IOleClientSiteNotImpl,
	public CComObjectRoot,
	public CComCoClass<CPropertySequence, &CLSID_PropertyActionSequence>
{
private:
	typedef list<WPropertyAction> CActionList;
	CActionList m_Actions;	// Liste der auszuführenden Aktionen
	string m_strDesc;		// Beschreibung der gesamten AktionsFolge

	bool m_fIsDirty;		// DirtyFlag
	bool m_fIsInitialized;	// ist fertig initialisiert
	bool m_fPrepared;		// Dialog wurde angezeigt
	bool m_fSetSiteCalled;	// SetSite wurde erfolgreich abgearbeitet

// Variablen für BeginAction/DoAction/EndAction
	CActionList::iterator m_itr;
	WPropertyAction m_ICurrAct;
	WDataObject m_Ctx;		// KontextObjekt
	WProgressIndicator2 m_IProgInd;
	WMultiProgressIndicator m_IMultProgInd;	// JG
	long m_lCurrIndex;						// JG

	LPTRIASTRANSAKTION pTrans;				// TRiAS Undo/Redo-TransAction

// erstes und letztes Objekt mit Dialog merken
	int m_iFirst;
	int m_iLast;

// MonikerSupport
	WMoniker m_ThisMk;						// Moniker dieser Sequence
	DWORD m_dwRegROT;						// ROTCookie dieses Monikers
	os_string m_strVersion;					// XML Versionsnummer
	bool m_fIsWizard97;						// Wizard neuen Typus anzeigen

protected:
	HRESULT CreateAndRegisterMoniker();
	HRESULT UnregisterAndFreeMoniker();

	void EraseActions (void) { m_Actions.erase(m_Actions.begin(), m_Actions.end()); }
	HRESULT ExecuteSequence (HWND hParent, IProgressIndicator *pIStatus,
							 IDataObject *pIData, IDataObject **ppOutData);
	HRESULT SetSiteObjectPointer (void);
	HRESULT FreeSiteObjectPointer (void);
	HRESULT GetNextSubPI(WProgressIndicator& SubPI);

	HRESULT SetStatTexts(void);	// Hilfsfunktion zum Setzen der Texte des Statusindicators
	HRESULT GoOn();				// Hilfsfunktion zum Testen des Abbruchstatus

public:
	BEGIN_COM_MAP(CPropertySequence)
		COM_INTERFACE_ENTRY(IPropertyActionSequence)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersist)
		COM_INTERFACE_ENTRY(IOleItemContainer)			// --> COleItemContainerSupport
		COM_INTERFACE_ENTRY(IOleContainer)				// --> COleItemContainerSupport
		COM_INTERFACE_ENTRY(IParseDisplayName)			// --> COleItemContainerSupport
		COM_INTERFACE_ENTRY(IOleClientSite)
	END_COM_MAP()

	BEGIN_OLEITEMCONTAINERSUPPORT_MAP(CPropertySequence)
		OLEITEMCONTAINERSUPPORT_ENTRY(g_cbMkPropAct, GetPropertyAction)
	END_OLEITEMCONTAINERSUPPORT_MAP()

	DECLARE_AGGREGATABLE(CPropertySequence)
	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_PROPINFO_PROPSEQUENCE)

		CPropertySequence();
		~CPropertySequence() {}

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	HRESULT FinalConstruct();
	void FinalRelease();

// OleItemContainerSupport
	HRESULT GetPropertyAction (LPCTSTR pcItem, DWORD dwSpeedNeeded, REFIID riid, LPVOID *ppvObj, bool fTestRunningOnly);

// IOleClientSite
	STDMETHOD (GetMoniker) (THIS_ DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk);

// IPropertyActionSequence methods
	STDMETHOD (AddAction) (THIS_ IPropertyAction *pIAct);
	STDMETHOD (AddActionsByCLSID) (THIS_ CALPCLSID *pcaClsIds);
	STDMETHOD (DoActions) (THIS_ HWND hParent, IProgressIndicator *pIStatus,
			       IDataObject *pIData, IDataObject **ppOutData);
	STDMETHOD (GetDescription) (THIS_ LPSTR pDesc, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD (RedoActions) (THIS_ HWND hParent, IProgressIndicator *pIStatus,
			       IDataObject *pIData, IDataObject **ppOutData);
	STDMETHOD (PrepareActions) (THIS_ HWND hParent, IDataObject *pIData);
	STDMETHOD (GetSequenceContext) (THIS_ IDataObject **ppIData);

	STDMETHOD (GetVersion) (THIS_ LPSTR pDesc, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD (SetVersion) (THIS_ LPCSTR pcDesc);
	STDMETHOD (SetIsWizard97) (THIS_ VARIANT_BOOL fIsWizard97);
	STDMETHOD (GetHeaderTitle) (THIS_ LPSTR pBuffer, ULONG wLen);
	STDMETHOD (SetHeaderTitle) (THIS_ LPCSTR pcHeaderTitle);
	STDMETHOD (GetHeaderSubTitle) (THIS_ LPSTR pSubBuffer, ULONG wLen);
	STDMETHOD (SetHeaderSubTitle) (THIS_ LPCSTR pcHeaderSubTitle);

// IPropertyAction methods
	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
								LPARAM lParam, LPCSTR pcDesc, 
								UINT *puiCnt);
	STDMETHOD (PreConfigPages) (THIS_ IDataObject *pIDataObject, DWORD dwFlags);
	STDMETHOD (BeginAction) (THIS_ IProgressIndicator *pIProgInd);
	STDMETHOD (DoAction) (THIS_ IDataObject *pDataObj, DWORD dwReserved);
	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppOutObj);

// IClassProperty specific functions
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags);
	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, 
						ULONG *pulHelpCtx);
	STDMETHOD(Eval)(THIS_ IEnumLONG *pEnumObj, LPSTR pBuffer, ULONG ulLen, 
					ULONG *pulWritten);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD (SetDescription) (THIS_ LPCSTR pcDesc);

// IPersist methods
	STDMETHOD(GetClassID)(THIS_ LPCLSID lpClassID);

// IPersistStreamInit methods
	STDMETHOD(IsDirty)(THIS);
	STDMETHOD(Load)(THIS_ LPSTREAM pStm);
	STDMETHOD(Save)(THIS_ LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER FAR* pcbSize);
	STDMETHOD(InitNew)(THIS);
};

///////////////////////////////////////////////////////////////////////////////
// diverse globale Funktionen
HRESULT GetSubPropSeqStorage (IStorage **ppIStg);
HRESULT LoadPropertySequence(LPCSTR pcDesc, IStorage *pIStg, LPCOLESTR pcVersion, 
	IPropertyActionSequence **ppISeq);
HRESULT SavePropSeq (LPCSTR pcDesc, IPropertyActionSequence *pISeq, IStorage *pIStg);

#endif // _PROPSEQ_HXX
