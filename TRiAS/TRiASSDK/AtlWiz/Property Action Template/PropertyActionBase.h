// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 18.04.99 09:52:17 
//
// @doc
// @module PropertyActionBase.h | Basisklasse für PropertyAction

#if !defined(_PROPERTYACTIONBASE_H__AFA90027_F562_11D2_9BF3_422620524153__INCLUDED_)
#define _PROPERTYACTIONBASE_H__AFA90027_F562_11D2_9BF3_422620524153__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <xtension.h>
#include <Ixtensn.hxx>

#if defined(_EXCLUDE_IPARSE_ETC_FROM_HELPER_TLH)
#import "tlb/Helper.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids \
	exclude("IParseRegularExpression", "IParseStringPairs", "IComposeStringPairs")
#else
#import "tlb/Helper.tlb" raw_interfaces_only raw_dispinterfaces no_namespace named_guids 
#endif // defined(_EXCLUDE_IPARSE_ETC_FROM_HELPER_TLH)

#include <Com/PropertyActionBaseData.h>
#include <Atl/Ciid.h>

#include <ospace/std/set>
#include <ospace/std/algorithm>
#include <ospace/com/iterenum.h>

///////////////////////////////////////////////////////////////////////////////
// Versionskontrolle
#define PROPACTB_VERSION_1_0_0	0x00000001
#define PROPACTB_ACTVERSION		PROPACTB_VERSION_1_0_0

/////////////////////////////////////////////////////////////////////////////
// Helperfunktionen
interface IPropertyActionSequence;

namespace PropActBase {
// Funktionen für Handling des IDataObject's
	HRESULT SetEnumObjects (IUnknown *pEnum, IDataObject *pDataObj);
	HRESULT GetEnumObjects (IDataObject *pIDataObj, REFIID riid, void **ppv);
	HRESULT SetVariantData (CComVariant &rv, IDataObject *pIDO, const FORMATETC *pcfe);
	HRESULT GetVariantData (IDataObject *pIDO, const FORMATETC *pcfe, CComVariant *pv);
	HRESULT InitFromDataFormatETC (IUnknown *pIUnk, IDataObject *pIDO, const FORMATETC *pcfmt);

// Funktionen für das Schreiben/Lesen einer ganzen PropertySequence im Projekt
	HRESULT LoadPropertySequence (BSTR bstrName, IPropertyActionSequence **ppIPropertyActionSequence);
	HRESULT SavePropertySequence (BSTR bstrName, IPropertyActionSequence *pIPropertyActionSequence);
} // namespace PropActBase

// {CF883AF6-553F-101B-AAE1-E7E7E7E7E7E7}
EXTERN_C const CLSID __declspec(selectany) CLSID_DataTransferObject = 
	{0xCF883AF6,0x553F,0x101B,{0xAA,0xE1,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7}};
EXTERN_C const CLSID CLSID_EnumObjectsByNumber;		// {0796381C-3123-101C-BB62-00AA0018497C}
EXTERN_C const CLSID CLSID_PropertyActionSequence;	// {0E54C9EE-20DE-11CF-BA55-00AA0018497C}
EXTERN_C const CLSID CLSID_ProgressIndicator;		// {07963819-3123-101C-BB62-00AA0018497C}

/////////////////////////////////////////////////////////////////////////////
// Überladen der InitNew-Funktion, um zu verhindern, daß diese Funktion mit
// IPersistStreamInit::InitNew zusammenfällt

class XPersistPropertyBagImpl :
	public IPersistPropertyBag
{
public:
	STDMETHOD(InitNew)(THIS) { return PersistPropertyBag_InitNew(); }
	STDMETHOD(PersistPropertyBag_InitNew)(THIS) PURE;
};

/////////////////////////////////////////////////////////////////////////////
// Schnittstellendefinition für die nachträgliche Implementation
// der Unterstützung eines ProgressIndicators
#if !defined(_IPROGRESSINDICATORUSAGE_DEFINED)
#define _IPROGRESSINDICATORUSAGE_DEFINED
class IProgressIndicatorUsage
{
public:
	virtual HRESULT Tick() = 0;							// ein Ereignis weiter
	virtual HRESULT SetType(DWORD dwType) = 0;			// den Typ des PI setzen
	virtual HRESULT GetType(DWORD* pdwType) = 0;
	virtual HRESULT SetMaxTicks(long lMaxTicks) = 0;	// die obere Bereichsgrenze setzen
	virtual HRESULT TickToEnd() = 0;					// bis zum Ende "ticken"
	virtual HRESULT GoOn() = 0;							// Abbruchtest (Vorsicht: läßt Windows alle anstehenden Msg. abarbeiten (Performance))
};
#endif // _IPROGRESSINDICATORUSAGE_DEFINED

/////////////////////////////////////////////////////////////////////////////
// und die zugehörige Adapterklasse des eigentlichen Executors
// reicht alle Aufrufe an den PI einfach weiter (falls ordentlich initialisiert)
class CPropertyActionUsageImpl :
	public IProgressIndicatorUsage
{
private:
	IProgressIndicatorUsage *m_pPA;

public:
	CPropertyActionUsageImpl(IProgressIndicatorUsage *pPa = NULL)
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
	HRESULT GetType(DWORD* pdwType) 
	{
		if (NULL == pdwType)
			return E_POINTER;

		if (NULL != m_pPA)
			return m_pPA -> GetType (pdwType);
		
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
// CPropertyActionBase immer nur als Basisklasse für die konkrete Implementation
// eines PropertyAction-Objektes verwenden.
// 
// Die benötigten Funktionen müssen überladen werden, alle nicht überladenen
// Funktionen liefern E_NOTIMPL. Funktionen, die überladen werden müssen,
// sind hier noch PURE (= 0).

class CPropertyActionBase : 
	public IPropertyAction2,
	public IPropertyAction,
	public IClassProperty,
	public IPropertyInfo,
	public IPersistStreamInit,
	public XPersistPropertyBagImpl
{
protected:
		CPropertyActionBase (DWORD dwFlags, UINT uiHelpID) : 	// nur als Basisklasse verwenden
			m_fNoShow (false), m_fIsDirty(false), m_fIsInitialized(false),
			m_dwFlags (dwFlags), m_uiHelpID(uiHelpID)
		{
		}	// nur als Basisklasse verwenden
		~CPropertyActionBase() {}

public:
// IPropertyAction methods
	STDMETHOD(AddConfigPages) (THIS_ LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
	{
		ATLTRACENOTIMPL("CPropertyActionBase::AddConfigPages");
	}
	STDMETHOD(PreConfigPages) (THIS_ IDataObject *pIDataObject, DWORD dwFlags)
	{
		ATLTRACENOTIMPL("CPropertyActionBase::PreConfigPages");
	}
	STDMETHOD(BeginAction) (THIS_ IProgressIndicator *pIProgInd)
	{
		ATLTRACENOTIMPL("CPropertyActionBase::BeginAction");
	}
	STDMETHOD(DoAction) (THIS_ IDataObject *pEnumObj, DWORD dwReserved)
	{
		ATLTRACENOTIMPL("CPropertyActionBase::DoAction");
	}
	STDMETHOD(EndAction) (THIS_ DWORD dwReserved, IDataObject **ppEnumObj)
	{
		ATLTRACENOTIMPL("CPropertyActionBase::EndAction");
	}

// *** IPropertyAction2 methods
	STDMETHOD(InitFromData) (THIS_ IDataObject *pIDO, BOOL fCreate, DWORD dwReserved)
	{
		if (NULL == pIDO) {
			if (fCreate)
				return S_OK;	// can attempt to initialize it self
			else
				return S_FALSE;	// can't attempt to replace internal data
		}

		COM_TRY {
		// evtl. liegt objektbezogene Initialisierungsinfo vor, ClipBoardFormat zusammenstellen
		CIID Guid;
		__Interface<IPersist> Persist;
		HRESULT hr = E_FAIL;

			if (SUCCEEDED(QueryInterface(Persist.ppi())) && SUCCEEDED(Persist -> GetClassID (&Guid))) {
			FORMATETC c_feProgID = 	{
					RegisterClipboardFormat (Guid.ProgID().c_str()),	// CLIPFORMAT cf
					NULL,											// DVTARGETDEVICE *ptd
					DVASPECT_CONTENT,								// DWORD dwAspect
					-1,												// LONG lindex	
					TYMED_ISTREAM,									// DWORD tymed
				};
				hr = PropActBase::InitFromDataFormatETC (GetUnknown(), pIDO, &c_feProgID);	// Fehler ignorieren
			}

		// Versuchen aus globaler Initialisierungsinformation zu initialisieren
			if (S_OK != hr)
				PropActBase::InitFromDataFormatETC (GetUnknown(), pIDO, &c_feInitPropAct);

		} COM_CATCH;
		return S_OK;
	}

// IClassProperty specific functions
	STDMETHOD(GetPropInfo) (THIS_ LPSTR pBuffer, WORD wLen, DWORD *pdwFlags) 
	{
		COM_TRY {
			if (NULL != pBuffer && wLen > 0) {
			// Namen der Property kopieren
			ULONG ulLen = min((size_t)(wLen-1), m_strDesc.length());

				strncpy (pBuffer, m_strDesc.c_str(), ulLen);
				pBuffer[ulLen] = '\0';
			}
		} COM_CATCH;

	// wenn gewünscht, Flags übergeben
		if (pdwFlags) 
			*pdwFlags = m_dwFlags;
		return S_OK;
	}
	STDMETHOD(Reset)(THIS)
	{
		ATLTRACENOTIMPL("CPropertyActionBase::Reset");
	}
	STDMETHOD_(ULONG, Count)(THIS)
	{
		return 0L;
	}
	STDMETHOD(HelpInfo)(THIS_ LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
	{
		if (NULL != pBuffer && ulLen > 0) {
			USES_CONVERSION;

		// Beschreibung übergeben
		CComBSTR bstrHelp;

			if (!bstrHelp.LoadString (m_uiHelpID))
				return E_FAIL;
			
		LPSTR pHelp = OLE2A(bstrHelp);
		ULONG ulLenT = min((size_t)(ulLen-1), strlen(pHelp));

			strncpy (pBuffer, pHelp, ulLenT);
			pBuffer[ulLenT] = '\0';
		} 

	// HelpFileInfo übergeben
		if (pHelpFile) pHelpFile[0] = '\0';
		if (pulHelpCtx) *pulHelpCtx = 0L;
		return S_OK;
	}
	STDMETHOD(Eval)(THIS_ IEnumLONG *pEnumObj, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
	{
		ATLTRACENOTIMPL("CPropertyActionBase::Eval");
	}
	STDMETHOD(Cumulation)(THIS_ LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
	{
		ATLTRACENOTIMPL("CPropertyActionBase::Cumulation");
	}

// IPropertyInfo specific functions 
	STDMETHOD(SetPropInfo) (THIS_ LPCSTR pcBuffer, DWORD dwFlags) 
	{
		if (NULL == pcBuffer) 
			return E_INVALIDARG;

		m_strDesc = pcBuffer;
		m_dwFlags = dwFlags;
		return S_OK;
	}
	STDMETHOD(SetHelpInfo) (THIS_ LPCSTR pBuffer, LPCSTR pHelpFile, ULONG ulHelpCtx)
	{
		ATLTRACENOTIMPL("CPropertyAction::SetHelpInfo");
	}

// IPersist methods
	STDMETHOD(GetClassID) (THIS_ CLSID *pClsID) PURE;

// IPersistStreamInit methods
	STDMETHOD(IsDirty)(THIS)
	{
		return m_fIsDirty ? S_OK : S_FALSE;
	}
	STDMETHOD(Load)(THIS_ LPSTREAM pStm)
	{
		if (m_fIsInitialized)
			return E_UNEXPECTED;

	// Version lesen und überprüfen
	DWORD dwVersion = 0;

		RETURN_FAILED_HRESULT(pStm -> Read (&dwVersion, sizeof(DWORD), NULL));
		if (dwVersion > PROPACTB_ACTVERSION)
			return STG_E_OLDDLL;	// File was written with a newer version

	// Daten einlesen
	ULONG ulLen = 0;
	char cbBuffer[_MAX_PATH];

		RETURN_FAILED_HRESULT(pStm -> Read (&ulLen, sizeof(ULONG), NULL));

		_ASSERTE(ulLen <= _MAX_PATH);
		RETURN_FAILED_HRESULT(pStm -> Read (cbBuffer, ulLen, NULL));

	DWORD dwFlags = 0;

		RETURN_FAILED_HRESULT(pStm -> Read (&dwFlags, sizeof(DWORD), NULL));
		RETURN_FAILED_HRESULT(SetPropInfo (cbBuffer, dwFlags));

		m_fIsInitialized = true;
		return S_OK;
	}
	STDMETHOD(Save)(THIS_ LPSTREAM pStm, BOOL fClearDirty)
	{
	// Versionsnummer wegschreiben
	DWORD dwVersion = PROPACTB_VERSION_1_0_0;

		RETURN_FAILED_HRESULT(pStm -> Write (&dwVersion, sizeof(DWORD), NULL));
		
	// Bezeichner wegschreiben
	char cbBuffer[_MAX_PATH];
	DWORD dwFlags = 0L;

		RETURN_FAILED_HRESULT(GetPropInfo (cbBuffer, sizeof(cbBuffer), &dwFlags));

	ULONG ulLen = strlen(cbBuffer)+1;

		RETURN_FAILED_HRESULT(pStm -> Write (&ulLen, sizeof(ULONG), NULL));
		RETURN_FAILED_HRESULT(pStm -> Write (cbBuffer, ulLen, NULL));
		RETURN_FAILED_HRESULT(pStm -> Write (&dwFlags, sizeof(DWORD), NULL));

		if (fClearDirty)
			SetDirty (false);
		return S_OK;
	}
	STDMETHOD(GetSizeMax)(THIS_ ULARGE_INTEGER *pcbSize)
	{
	char cbBuffer[_MAX_PATH];

		RETURN_FAILED_HRESULT(GetPropInfo (cbBuffer, sizeof(cbBuffer), NULL));
		pcbSize -> QuadPart = 2*sizeof(DWORD)+sizeof(ULONG)+strlen(cbBuffer)+1;
		return S_OK;
	}
	STDMETHOD(InitNew)(THIS)
	{
		if (m_fIsInitialized)
			return E_UNEXPECTED;
		m_fIsInitialized = true;
		return S_OK;
	}

// IPersistPropertyBag
	STDMETHOD(Load)(THIS_ IPropertyBag *pBag, IErrorLog *pLog)
	{
		USES_CONVERSION;
		m_fNoShow = false;

	// wenigstens den Namen der PropertyAction einlesen
	CComVariant vName;
	HRESULT hr = pBag -> Read (CComBSTR(L"Name"), &vName, pLog);

		if (S_OK == hr && SUCCEEDED(vName.ChangeType (VT_BSTR)))
		{
			RETURN_FAILED_HRESULT(SetPropInfo (OLE2A(V_BSTR(&vName)), 0L));
		}

	// und noch einlesen, ob der Dialog evtl. _nicht_ angezeigt werden soll
	CComVariant vNoShow;

		hr = pBag -> Read (CComBSTR(L"NoShow"), &vNoShow, pLog);
		if (S_OK == hr && SUCCEEDED(vNoShow.ChangeType (VT_BOOL)))
			m_fNoShow = V_BOOL(&vNoShow) ? true : false;
		return hr;
	}
	STDMETHOD(Save)(THIS_ IPropertyBag *pBag, BOOL fClearDirty, BOOL fSaveAllProperties)
	{
		return E_NOTIMPL;	// Save wird hier (noch) nicht gebraucht
	}
	STDMETHOD(PersistPropertyBag_InitNew)(THIS)
	{
		return S_OK;		// tut einfach nichts
	}

// diverse ZugriffsFunktionen
	IUnknown *GetUnknown() { return static_cast<IPropertyAction *>(this); }

	bool IsNoShow() { return m_fNoShow; }
	void SetDirty (bool fIsDirty) { m_fIsDirty = fIsDirty; }
	bool IsInitialized() { return m_fIsInitialized; }
	void SetInitialized (bool fIsInitialized = true) { m_fIsInitialized = fIsInitialized; }

protected:
	bool m_fNoShow;
	bool m_fIsDirty;
	bool m_fIsInitialized;

	string m_strDesc;		// Name der GeoKomponente
	DWORD m_dwFlags;		// operation modi
	UINT m_uiHelpID;		// ResourceID des HelpStrings
};

// Schnittstellendefinition falls die eigentliche Arbeit der Aktion in 
// einer anderen Klasse (z.B. im Dialog) stattfindet
class CPropertyActionImpl :
	public CPropertyActionBase,
	public IProgressIndicatorUsage
{
public:
	CPropertyActionImpl(DWORD dwFlags, UINT uiHelpID)
		: CPropertyActionBase(dwFlags, uiHelpID)
	{
		m_dwType = PIFLAG_ADJUSTPERCENT | PIFLAG_TIME | PIFLAG_STATUS;
		m_aktTick = 0;
		m_maxTick = 0;
	}

// eigenes BeginAction
	STDMETHOD(BeginAction) (THIS_ IProgressIndicator *pIProgInd)
	{
	// 	speichern des PI's
		COM_TRY	{
			m_pProgressIndicator = pIProgInd;
		} COM_CATCH
		return S_OK;
	}

// Helpermethods
	HRESULT Tick()									// Call to increment ProgressInfo
	{
		// wenn noch möglich, dann weiterschalten
		if ((m_pProgressIndicator != NULL) && (m_aktTick < m_maxTick)) {
			++m_aktTick;	// noch'n Tick
			return m_pProgressIndicator -> SetPosition(m_aktTick);
		}
		return S_OK;		// auch nicht schlimm, dann eben ohne ProgInd
	}
	HRESULT SetType(DWORD dwType)
	{
		m_dwType = dwType;
		return S_OK;
	}
	HRESULT GetType (DWORD *pdwType) 
	{
		if (NULL == pdwType) 
			return E_POINTER;

		*pdwType = m_dwType;
		return S_OK;
	}
	HRESULT SetMaxTicks(long lMaxTicks)
	{
		m_maxTick = lMaxTicks + 1;
		
	// keine Initialisierung möglich
		if (!m_pProgressIndicator) 
			return S_OK;

		COM_TRY	{
		__Interface<IProgressIndicator2> t_PI(m_pProgressIndicator);
					
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

// UndoRedo-Verwaltung
	BOOL IsUndoEnabled() { return TRUE; }	// erstmal immer zuschalten

	HRESULT BeginUndoLevel (LPCSTR pcDesc) { return IsUndoEnabled() ? DEX_BeginUndoLevel(pcDesc) : S_OK; }
	HRESULT EndUndoLevel () { return IsUndoEnabled() ? DEX_EndUndoLevel() : S_OK; }
	HRESULT CancelUndoLevel (BOOL fUndo) { return IsUndoEnabled() ? DEX_CancelUndoLevel (fUndo) : S_OK; }

protected:
// Member
	__Interface<IProgressIndicator> m_pProgressIndicator;			// wohin sollen Progressinfos geschaufelt werden

private:
	LONG m_aktTick;
	LONG m_maxTick;
	DWORD m_dwType;
};

#endif // !defined(_PROPERTYACTIONBASE_H__AFA90027_F562_11D2_9BF3_422620524153__INCLUDED_)
