// Verwaltung einer Abfolge von IPropertyActions ------------------------------
// File: PROPSEQ.HXX

#if !defined(_PROPSEQ_HXX)
#define _PROPSEQ_HXX

#define PROPERTYACTION_FORMATVERSION	0x00100000L

#include <ipropseq.hxx>

DefineSmartInterface(PropertyAction);
DefineSmartInterface(ProgressIndicator);

// Objekt, welches die Abfolge von ProperyActions steuert ---------------------
class CPropertySequence : 
	public IClassProperty,
	public IPropertyAction,
	public IPropertyActionSequence,
	public IPersistStreamInit,
	public CComObjectBase<&CLSID_PropertyActionSequence>
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
	WProgressIndicator m_IProgInd;

protected:

public:
	BEGIN_COM_MAP(CPropertySequence)
		COM_INTERFACE_ENTRY(IPropertyActionSequence)
		COM_INTERFACE_ENTRY(IPropertyAction)
		COM_INTERFACE_ENTRY(IClassProperty)
		COM_INTERFACE_ENTRY2(IPersistStream, IPersistStreamInit)
		COM_INTERFACE_ENTRY(IPersistStreamInit)
	END_COM_MAP()

	DECLARE_AGGREGATABLE(CPropertySequence)

		CPropertySequence();
		~CPropertySequence() {}

// IPropertyActionSequence methods
	STDMETHOD (SetDescription) (THIS_ LPCSTR pcDesc);
	STDMETHOD (AddAction) (THIS_ IPropertyAction *pIAct);
	STDMETHOD (AddActionByName) (THIS_ LPCSTR pcPropName);
	STDMETHOD (DoActions) (THIS_ HWND hParent, IProgressIndicator *pIStatus,
			       IDataObject *pIData, IDataObject **ppOutData);

// IPropertyAction methods
	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
								LPARAM lParam, DWORD dwFlags, LPCSTR pcDesc, 
								UINT *puiCnt);
	STDMETHOD (PreConfigPages) (THIS_ IDataObject *pIDataObject);
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
