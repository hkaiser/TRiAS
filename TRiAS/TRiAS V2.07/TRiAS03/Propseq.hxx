// Verwaltung einer Abfolge von IPropertyActions ------------------------------
// File: PROPSEQ.HXX

#if !defined(_PROPSEQ_HXX)
#define _PROPSEQ_HXX

#define PROPERTYACTION_FORMATVERSION	0x00100000L

#include <ipropseq.hxx>
#include "propactb.hxx"
#include "triastrans.h"

DefineSmartInterface(MultiProgressIndicator);
DefineSmartInterface(PropertyAction);

// Objekt, welches die Abfolge von ProperyActions steuert ---------------------
class CPropertySequence : 
	public IClassProperty,
	public IPropertyAction,
	public IPropertyActionSequence,
	public IPersistStreamInit,
	public CComObjectRoot,
	public CComCoClass<CPropertySequence, &CLSID_PropertyActionSequence>
{
private:
	typedef list<WPropertyAction> CActionList;
	CActionList m_Actions;	// Liste der auszuführenden Aktionen
	string m_strDesc;		// Beschreibung der gesamten AktionsFolge

	bool m_fIsDirty;		// DirtyFlag
	bool m_fIsInitialized;	// ist fertig initialisiert

// Variablen für BeginAction/DoAction/EndAction
	CActionList::iterator m_itr;
	WPropertyAction m_ICurrAct;
	WProgressIndicator2 m_IProgInd;
	WMultiProgressIndicator m_IMultProgInd;	// JG
	long m_lCurrIndex;						// JG

	LPTRIASTRANSAKTION pTrans;				// TRiAS Undo/Redo-TransAction

// erstes und letztes Objekt mit Dialog merken
	int m_iFirst;
	int m_iLast;

protected:
	void EraseActions (void) { m_Actions.erase(m_Actions.begin(), m_Actions.end()); }
	HRESULT ExecuteSequence (HWND hParent, IProgressIndicator *pIStatus,
							 IDataObject *pIData, IDataObject **ppOutData);
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
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CPropertySequence)
	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_PROPINFO_PROPSEQUENCE)

		CPropertySequence();
		~CPropertySequence() {}

// IPropertyActionSequence methods
	STDMETHOD (AddAction) (THIS_ IPropertyAction *pIAct);
	STDMETHOD (AddActionsByCLSID) (THIS_ CALPCLSID *pcaClsIds);
	STDMETHOD (DoActions) (THIS_ HWND hParent, IProgressIndicator *pIStatus,
			       IDataObject *pIData, IDataObject **ppOutData);
	STDMETHOD (GetDescription) (THIS_ LPSTR pDesc, ULONG ulLen, ULONG *pulWritten);
	STDMETHOD (RedoActions) (THIS_ HWND hParent, IProgressIndicator *pIStatus,
			       IDataObject *pIData, IDataObject **ppOutData);

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

#endif // _PROPSEQ_HXX
