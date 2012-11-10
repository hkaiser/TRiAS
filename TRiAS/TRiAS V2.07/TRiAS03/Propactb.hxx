// Basisklasse für IPropertyAction --------------------------------------------
// File: PROPACTB.HXX

#if !defined(_PROPACTB_HXX)
#define _PROPACTB_HXX

// JG
#include "MultiPI.h"
// DefineSmartInterface(ProgressIndicator2);

/////////////////////////////////////////////////////////////////////////////
// Überladen der InitNew-Funktion, um zu verhindern, daß diese Funktion mit
// IPersistStreamInit::InitNew zusammenfällt

class XPersistPropertyBag :
	public IPersistPropertyBag
{
public:
	STDMETHOD(InitNew)(THIS) { return PersistPropertyBag_InitNew(); }
	STDMETHOD(PersistPropertyBag_InitNew)(THIS) PURE;
};

///////////////////////////////////////////////////////////////////////////////
// CPropertyAction immer nur als Basisklasse für die konkrete Implementation
// eines PropertyAction-Objektes verwenden.
// 
// Die benötigten Funktionen müssen überladen werden, alle nicht überladenen
// Funktionen liefern E_NOTIMPL. Funktionen, die überladen werden müssen,
// sind hier noch PURE (= 0).
class CPropertyAction : 
	public IPropertyAction2,
	public IPropertyAction,
	public IClassProperty,
	public IPropertyInfo,
	public IPersistStreamInit,
	public XPersistPropertyBag
{
protected:
		CPropertyAction() : m_fNoShow (false) {}	// nur als Basisklasse verwenden
		~CPropertyAction() {}

public:
// IPropertyAction methods
	STDMETHOD (AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, 
				    LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt);
	STDMETHOD (PreConfigPages) (THIS_ IDataObject *pIDataObject, DWORD dwFlags);
	STDMETHOD (BeginAction) (THIS_ IProgressIndicator *pIProgInd);
	STDMETHOD (DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved);
	STDMETHOD (EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj);

// *** IPropertyAction2 methods
	STDMETHOD (InitFromData) (THIS_ IDataObject *pIDO, BOOL fCreate, DWORD dwReserved);

// IClassProperty specific functions
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags) PURE;
	STDMETHOD(Reset)(THIS);
	STDMETHOD_(ULONG, Count)(THIS);
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, 
						LPSTR pHelpFile, ULONG *pulHelpCtx);
	STDMETHOD(Eval)(THIS_ IEnumLONG *pEnumObj, LPSTR pBuffer, 
					ULONG ulLen, ULONG *pulWritten);
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten);

// IPropertyInfo specific functions 
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pBuffer, DWORD dwFlags) PURE;
	STDMETHOD(SetHelpInfo) (THIS_ LPCSTR pBuffer, LPCSTR pHelpFile, ULONG ulHelpCtx);

// IPersist methods
	STDMETHOD(GetClassID) (THIS_ CLSID *pClsID) PURE;

// IPersistStreamInit methods
	STDMETHOD(IsDirty)(THIS) PURE;
	STDMETHOD(Load)(THIS_ LPSTREAM pStm);
	STDMETHOD(Save)(THIS_ LPSTREAM pStm, BOOL fClearDirty);
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER FAR* pcbSize);
	STDMETHOD(InitNew)(THIS) PURE;

// IPersistPropertyBag
	STDMETHOD(Load)(THIS_ IPropertyBag *pBag, IErrorLog *pLog);
	STDMETHOD(Save)(THIS_ IPropertyBag *pBag, BOOL fClearDirty, BOOL fSaveAllProperties);
	STDMETHOD(PersistPropertyBag_InitNew)(THIS);

// diverse ZugriffsFunktionen
	IUnknown *GetUnknown() { return (IPropertyAction *)this; }
	bool IsNoShow() { return m_fNoShow; }

protected:
	bool m_fNoShow;
};

// Schnittstellendefinition für die nachträgliche Implementation
// der Unterstützung eines ProgressIndicators
class IProgressIndicatorUsage
{
public:
	virtual HRESULT Tick() = 0;							// ein Ereignis weiter
	virtual HRESULT SetType(DWORD dwType) = 0;			// den Typ des PI setzen
	virtual HRESULT SetMaxTicks(long lMaxTicks) = 0;	// die obere Bereichsgrenze setzen
	virtual HRESULT TickToEnd() = 0;					// bis zum Ende "ticken"
	virtual HRESULT GoOn() = 0;							// Abbruchtest (Vorsicht: läßt Windows alle anstehenden Msg. abarbeiten (Performance))
};

// Schnittstellendefinition falls die eigentliche Arbeit der Aktion in 
// einer anderen Klasse (z.B. im Dialog) stattfindet
class CPropertyActionExt :
	public CPropertyAction,
	public IProgressIndicatorUsage
{
public:
	STDMETHOD (BeginAction) (THIS_ IProgressIndicator *pIProgInd);
	CPropertyActionExt()
	{
		m_dwType = PIFLAG_ADJUSTPERCENT | PIFLAG_TIME | PIFLAG_STATUS;
		m_aktTick = 0;
		m_maxTick = 0;
	}

// Helpermethods
	HRESULT Tick();									// Call to increment ProgressInfo
	HRESULT SetType(DWORD dwType)
	{
		m_dwType = dwType;
		return S_OK;
	}
	HRESULT SetMaxTicks(long lMaxTicks)
	{
		m_maxTick = lMaxTicks + 1;
		
	// keine Initialisierung möglich
		if (!m_pProgressIndicator == NULL) 
			return S_OK;

		COM_TRY	{
		WProgressIndicator2 t_PI(m_pProgressIndicator);
					
			THROW_FAILED_HRESULT(t_PI -> Restart(0, m_maxTick, static_cast<tagPIFLAGS> (m_dwType)));
		} COM_CATCH;
		return S_OK;
	}
	HRESULT TickToEnd()
	{
		if (!m_pProgressIndicator)
			return S_OK;
		return m_pProgressIndicator -> SetPosition(m_maxTick);
	}
	HRESULT GoOn()
	{
	// Wie soll denn dann abgebrochen werden
		if (!m_pProgressIndicator)
			return S_OK;

	// Abbruch im StatInd ? 
		if (m_pProgressIndicator -> WasCanceled())
			return E_ABORT;

	// Alles klar, weiter so
		return S_OK;
	}

private:
// Member
	WProgressIndicator m_pProgressIndicator;			// wohin sollen Progressinfos geschaufelt werden
	long m_aktTick;
	long m_maxTick;
	DWORD m_dwType;
};

//
// und die zugehörige Adapterklasse des eigentlichen Executors
// reicht alle Aufrufe an den PI einfach weiter (falls ordentlich initialisiert)
class CPropertyActionExtUsage :
	public IProgressIndicatorUsage
{
private:
	IProgressIndicatorUsage * m_pPA;

public:
	CPropertyActionExtUsage(IProgressIndicatorUsage *pPa = NULL)
	{
		m_pPA = pPa;
	}
	void SetAction(IProgressIndicatorUsage * pPA)
	{
		m_pPA = pPA;
	}
	HRESULT SetType(DWORD dwType)
	{
		if (NULL != m_pPA)
			return m_pPA -> SetType(dwType);
		return S_OK;
	}
	HRESULT SetMaxTicks(long lMaxTicks)
	{
		if (NULL != m_pPA)
			return m_pPA -> SetMaxTicks(lMaxTicks);
		return S_OK;
	}
	HRESULT Tick()
	{
		if (NULL != m_pPA)
			return m_pPA -> Tick();
		return S_OK;
	}
	HRESULT TickToEnd()
	{
		if (NULL != m_pPA)
			return m_pPA -> TickToEnd();
		return S_OK;
	}
	HRESULT GoOn()
	{
		if (NULL != m_pPA)
			return m_pPA -> GoOn();
		return S_OK;
	}
};

///////////////////////////////////////////////////////////////////////////////
// Versionskontrolle
#define PROPACTB_VERSION_1_0_0	0x00000001
#define PROPACTB_ACTVERSION		PROPACTB_VERSION_1_0_0

#endif // _PROPACTB_HXX
