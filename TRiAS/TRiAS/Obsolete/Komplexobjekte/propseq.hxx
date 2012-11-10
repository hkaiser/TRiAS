// Verwaltung einer Abfolge von IPropertyActions ------------------------------
// File: PROPSEQ.HXX

#if !defined(_PROPSEQ_HXX)
#define _PROPSEQ_HXX

#include <ienumobj.hxx>
#include <ipropseq.hxx>

// Objekt, welches die Abfolge von ProperyActions steuert ---------------------
class CPropertySequence : public IPropertyActionSequence {
private:
	DWORD m_dwRefCnt;

// Liste der auszuführenden Aktionen
	typedef list<WPropertyAction> CActionList;
	CActionList m_Actions;

protected:
		CPropertySequence (void);	// nicht direkt erzeugen

	bool FInit (void);

public:
		~CPropertySequence (void);

static CPropertySequence *CreateInstance (void);

// *** IUnknown methods
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID *ppvObj);
	STDMETHOD_ (ULONG, AddRef) (THIS);
	STDMETHOD_ (ULONG, Release) (THIS);

// *** IPropertyActionSequence methods
	STDMETHOD (Reset) (THIS);
	STDMETHOD (AddAction) (THIS_ IPropertyAction *pIAct);
	STDMETHOD (AddActionByName) (THIS_ LPCSTR pcPropName);
	STDMETHOD (DoActions) (THIS_ HWND hParent, IProgressIndicator *pIStatus,
			       IDataObject *pIData, IDataObject **ppOutData);
};

// Erzeugen einer Instanz dieser Klasse ---------------------------------------
HRESULT PActCreateInstance (REFIID riid, LPVOID *ppvObj);

// Erzeugen einer Instanz dieser Klasse sowie deren Initialisierung -----------
HRESULT InitPropertyActionSequence (ITriasXtensionSite *pIXtnSite,
	    LPCSTR cbActs[], int iCnt, IPropertyActionSequence **ppISeq);

#endif // _PROPSEQ_HXX
