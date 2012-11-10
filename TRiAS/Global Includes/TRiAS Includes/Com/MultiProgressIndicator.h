// $Header: $
// Copyright© 1999 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 18.04.99 09:58:59 
//
// @doc
// @module MultiProgressIndicator.h | Declaration of the <c CMultiProgressIndicator> class

#if !defined(_MULTIPROGRESSINDICATOR_H__AFA90034_F562_11D2_9BF3_422620524153__INCLUDED_)
#define _MULTIPROGRESSINDICATOR_H__AFA90034_F562_11D2_9BF3_422620524153__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include <idl/ProgInd2.h>
#include <IStatus.h>

///////////////////////////////////////////////////////////////////////////////
//	Konstanten
const ULONG ulMinBereich = 0;		//	min. und	
const ULONG ulMaxBereich = 10000;	//	max. Bereichswerte 
const ULONG NAMEBUFFERSIZE = 1024;

///////////////////////////////////////////////////////////////////////////////
//
template<const GUID *piid, WORD wMajor = 1, WORD wMinor = 0> 
class CMultiProgressIndicator;

template<const GUID *piid, WORD wMajor = 1, WORD wMinor = 0>
class CSubIndicator : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public IProgressIndicator,
	public IDispatchImpl<IProgressIndicator2, &IID_IProgressIndicator2, piid, wMajor, wMinor>,
	public ISupportErrorInfoImpl<&IID_IProgressIndicator2>
{
private:
	ULONG m_ulMinBer;		//	Bereichswerte: min. Wert
	ULONG m_ulMaxBer;		//				   max. Wert	
	ULONG m_ulMinWert;		//	akt. min. Wert
	ULONG m_ulMaxWert;		//	akt. max. Wert
	ULONG m_ulActPos;		//	akt. Position

	__Interface<IProgressIndicator2> m_wPI;	// Ausgabe-PI
	string m_strPercentText;	// Text für die Prozente

protected:
	HRESULT SetStatusText()		// JG Hilfsfunktion zum Setzen des Statustextes
	{
		if (0 == m_strPercentText.length())		// habe ich die Kontrolle über den Statustext ?
			return S_OK;

	// ja, ich habe die Kontrolle, Puffer anlegen und initialisieren
	char cTmp[NAMEBUFFERSIZE];
	long actProzent = m_ulActPos * 100 / (m_ulMaxWert - m_ulMinWert);
		
		wsprintf (cTmp, m_strPercentText.c_str(), actProzent);

	// da der eigentliche Indicator auch ein wsprintf ausführt,
	// muß jedes vorhandene % Zeichen gedoppelt werden
	string strTmp(cTmp);
	long i = 0;

		while (-1 != (i = strTmp.find(_T("%"), i))) {
			strTmp.insert(i, _T("%"));
			i += 2;		// eine Stelle (+1) nach dem eingefügten Zeichen (+1) weitersuchen
		}

	// und weiterreichen
		COM_TRY {
			THROW_FAILED_HRESULT(WProgressIndicator(m_wPI) -> ChangeText(PIFLAG_ADJUSTPERCENT, strTmp.c_str()));
		} COM_CATCH
		return S_OK;
	}

public:
	CSubIndicator (void)
	{
		m_ulActPos = m_ulMinBer = m_ulMinWert = 0;
		m_ulMaxBer = m_ulMaxWert = 1;
	}
	~CSubIndicator (void)
	{
	}

// *** IProgressIndicator methods ***
	STDMETHOD_(HWND, InitNew)(THIS_ HWND hWnd, DWORD dwReserved)
	{
		COM_TRY {
			return WProgressIndicator(m_wPI) -> InitNew (hWnd, dwReserved);
		} COM_CATCH_RETURN(NULL);
	}
	STDMETHOD(Restart)(THIS_ ULONG uiMinPos, ULONG ulMaxPos, DWORD dwFlags)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WProgressIndicator(m_wPI) -> Restart(uiMinPos, ulMaxPos, dwFlags));
			THROW_FAILED_HRESULT(SetStatusText());
		} COM_CATCH
		return S_OK;
	}
	STDMETHOD(ChangeText)(THIS_ DWORD dwWhichText, LPCSTR pcNewText)
	{
		COM_TRY {
		// erstmal generell die verlangte Aktion ausführen
			THROW_FAILED_HRESULT(WProgressIndicator (m_wPI) -> ChangeText (dwWhichText, pcNewText));

		// wenn der Statustext geändert wird, dann diesen Text ab sofort von hier aus handeln
			if (dwWhichText & PIFLAG_ADJUSTPERCENT || dwWhichText & PIFLAG_STATUS) {
				m_strPercentText = pcNewText;
				THROW_FAILED_HRESULT(SetStatusText());
			}
		} COM_CATCH
		return S_OK;
	}
	STDMETHOD(RetrieveText)(THIS_ DWORD dwWichText, LPSTR cbText, ULONG uiLen)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WProgressIndicator(m_wPI) -> RetrieveText(dwWichText, cbText, uiLen));
		} COM_CATCH
		return S_OK;
	}

	STDMETHOD_(int, SetPosition)(THIS_ ULONG uiNewPos)
	{
	int iPercent = 0;
		
		SetPosition (uiNewPos, &iPercent);		// da existiert schon eine Logic
		return iPercent;
	}
	STDMETHOD_(BOOL, WasCanceled)(THIS)
	{
		COM_TRY {
			return WProgressIndicator(m_wPI) -> WasCanceled();
		} COM_CATCH_RETURN(FALSE);
	}

//	Methoden der Basisklasse
	STDMETHOD(Restart)(ULONG ulMinPos, ULONG ulMaxPos, PIFLAGS Flags)
	{
		_ASSERTE(m_wPI.IsValid());
		_ASSERTE(ulMinPos >= 0);
		_ASSERTE(ulMaxPos > ulMinPos);
		_ASSERTE(m_ulMinBer >= 0);
		_ASSERTE(m_ulMaxBer > m_ulMinBer);

		m_ulActPos = m_ulMinWert = ulMinPos;
		m_ulMaxWert = ulMaxPos;

	int iPercent = 0;

		RETURN_FAILED_HRESULT(m_wPI -> SetPosition (m_ulMinBer, &iPercent));
		RETURN_FAILED_HRESULT(m_wPI -> put_Flags (fFlags));
		RETURN_FAILED_HRESULT(SetStatusText());
		return S_OK;
	}
	STDMETHOD(ChangeText)(PIFLAGS fWhichText, BSTR bstrNewText)
	{
		_ASSERTE(m_wPI.IsValid());

	// erstmal generell die verlangte Aktion ausführen
		RETURN_FAILED_HRESULT(m_wPI -> ChangeText (fWhichText, bstrNewText));

	// wenn der Statustext geändert wird, dann diesen Text ab sofort von hier aus handeln
		if (fWhichText & PIFLAG_ADJUSTPERCENT || fWhichText & PIFLAG_STATUS) {
			USES_CONVERSION;
			m_strPercentText = OLE2A(bstrNewText);
			RETURN_FAILED_HRESULT(SetStatusText());
		}
		return S_OK;
	}
	STDMETHOD(RetrieveText)(PIFLAGS fWichText, BSTR *pbstrText)
	{
		_ASSERTE(m_wPI.IsValid());
		RETURN_FAILED_HRESULT(m_wPI -> RetrieveText (fWichText, pbstrText));
		return S_OK;
	}
	STDMETHOD(IsCanceled)(THIS);
	{
		_ASSERTE(m_wPI.IsValid());
		RETURN_FAILED_HRESULT(m_wPI -> IsCanceled());
		return S_OK;
	}
	STDMETHOD(InitNew)(LONG hWnd, DWORD dwReserved, LONG *phWnd)
	{
		_ASSERTE(m_wPI.IsValid());
		return m_wPI -> InitNew (hWnd, dwReserved, phWnd);
	}
	STDMETHOD(SetPosition)(THIS_ ULONG ulNewPos, INT *piPercent)
	{
		if (NULL == piPercent)
			return E_POINTER;
		*piPercent = NULL;

		_ASSERTE(m_wPI.IsValid());
		_ASSERTE(m_ulMinBer >= 0);
		_ASSERTE(m_ulMaxBer > m_ulMinBer);
		_ASSERTE(m_ulMinWert >= 0);
		_ASSERTE(m_ulMaxWert > m_ulMinWert);

	//	Division durch 0 verhindern
		if (m_ulMinWert == m_ulMaxWert)
			return 0;
		
	double dNewPos = m_ulMinBer + ((double)ulNewPos * (((double)(m_ulMaxBer - m_ulMinBer)) / (m_ulMaxWert - m_ulMinWert)));
	
		m_ulActPos = ulNewPos;			// Position merken
		ulNewPos = ULONG (dNewPos + 0.5);
		
		RETURN_FAILED_HRESULT(m_wPI -> SetPosition (ulNewPos, piPercent));
		RETURN_FAILED_HRESULT(SetStatusText());
		return S_OK;
	}
	STDMETHOD(IncrementPosition)(INT *piPercent)
	{
		if (NULL == piPercent)
			return E_POINTER;
		*piPercent = 0;
		RETURN_FAILED_HRESULT(SetPosition (++m_ulActPos, piPercent));
		return S_OK;
	}
	STDMETHOD(get_Flags)(PIFLAGS *prgFlags)
	{
		_ASSERTE(m_wPI.IsValid());
		RETURN_FAILED_HRESULT(m_wPI -> get_Flags (prgFlags));
		return S_OK;
	}
	STDMETHOD(put_Flags)(PIFLAGS rgFlags)
	{
		_ASSERTE(m_wPI.IsValid());
		RETURN_FAILED_HRESULT(m_wPI -> put_Flags (rgFlags));
		return S_OK;
	}
	STDMETHOD(RetrieveRange)(ULONG *pulMinPos, ULONG *pulMaxPos)
	{
		_ASSERTE(m_wPI.IsValid());
		RETURN_FAILED_HRESULT(m_wPI -> RetrieveRange (pulMinPos, pulMaxPos));
		return S_OK;
	}

	BEGIN_COM_MAP(CSubIndicator)
		COM_INTERFACE_ENTRY(IProgressIndicator)	// JG
		COM_INTERFACE_ENTRY(IProgressIndicator2)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

	friend class CMultiProgressIndicator;
};

template<const GUID *piid, WORD wMajor = 1, WORD wMinor = 0>
class CMultiProgressIndicator : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<CMultiProgressIndicator, &CLSID_MultiProgressIndicator>,
	public IDispatchImpl<IMultiProgressIndicator, &IID_IMultiProgressIndicator, piid, wMajor, wMinor>,
	public ISupportErrorInfoImpl<&IID_IMultiProgressIndicator>
{
private:
	typedef CSubIndicator<piid, wMajor, wMinor> CSubIndicatorImpl;
	int m_iRangeCnt;					//	Anzahl der verwalteten Bereiche
	CComObject<CSubIndicatorImpl> **m_ppPI;	//	Zeiger auf Vektor der verwalteten PIs
	
public:
	CMultiProgressIndicator (void)
	{
		m_ppPI = NULL;
		m_iRangeCnt = 0;
	}
	~CMultiProgressIndicator (void)
	{
		DeletePIs ();
	}

	STDMETHOD(Init)(int iRangeCnt, IProgressIndicator2 *pPI)			//	Init: Ausgabe-PI
	{
	//	prüfe Parameter
		if (NULL == pPIInput)
			return E_POINTER;
		*pPOInput = NULL;

		if (iRangeCnt <= 0)
			return E_INVALIDARG;

		COM_TRY {
			THROW_FAILED_HRESULT(pPIInput -> Restart (ulMinBereich, ulMaxBereich, (PIFLAGS) 0));
			
		// alten PIs löschen
			DeletePIs ();

		// neuen PI-Vektor erzeugen u. init.
			m_ppPI = new CComObject<CSubIndicatorImpl>* [iRangeCnt];
			memset (m_ppPI, 0, sizeof (CComObject<CSubIndicatorImpl> *));

		// Faktor berechnen
		double dFaktor = ((double)(ulMaxBereich - ulMinBereich)) / iRangeCnt;			

		// neuen PIs erzeugen
		double dBereich = 0;

			m_iRangeCnt = 0;
			for (int i = 0; i < iRangeCnt; i++)	{
			// PI erzeugen
			CComObject<CSubIndicatorImpl> *pPI = NULL;
			
				THROW_FAILED_HRESULT(CComObject<CSubIndicatorImpl>::CreateInstance (&pPI));

				m_iRangeCnt++;	

			// akt. PI init.
				pPI -> m_wPI = pPIInput;
				dBereich = (i * dFaktor) + ulMinBereich;
				pPI -> m_ulMinBer = ULONG (dBereich + 0.5);
				dBereich = ((i+1) * dFaktor) + ulMinBereich;
				pPI -> m_ulMaxBer = ULONG (dBereich + 0.5);

			// und Zeiger speichern
				m_ppPI[i] = pPI;
				m_ppPI[i] -> AddRef();
			}
		} COM_CATCH_OP(DeletePIs());
		return S_OK;
	}
	STDMETHOD(GetRange)(int iRange, IProgressIndicator2 **ppPI);		// PI zum Bereich lesen
	{
		if (NULL == ppPI)
			return E_POINTER;
		*ppPI = NULL;

		if ((iRange < 0) || (iRange >= m_iRangeCnt))
			return E_INVALIDARG;
		if (0 == m_iRangeCnt)
			return E_UNEXPECTED;

		*ppPI = m_ppPI[iRange];
		if (NULL == *ppPI)
			return E_UNEXPECTED;

		(*ppPI) -> AddRef();
		return S_OK;
	}
	STDMETHOD(get_RangeCnt)(int *piRangeCnt)							// lese Bereischsanzahl
	{
		if (NULL == piRangeCnt)
			return E_POINTER;
		*piRangeCnt = m_iRangeCnt;
		return S_OK;
	}

	DECLARE_STATIC_REGISTRY_RESOURCEID(IDR_MULTIPI_RGS);

	BEGIN_COM_MAP(CMultiProgressIndicator)
		COM_INTERFACE_ENTRY(IMultiProgressIndicator)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

protected:
	HRESULT DeletePIs (void)
	{
		if ((m_iRangeCnt <= 0) || (NULL == m_ppPI)) 
			return S_OK;

		for (int i = 0; i < m_iRangeCnt; i++)
			m_ppPI[i] -> Release();
		
		DELETE_VEC (m_ppPI);
		m_iRangeCnt = 0;
		return S_OK;
	}
};

#endif // !defined(_MULTIPROGRESSINDICATOR_H__AFA90034_F562_11D2_9BF3_422620524153__INCLUDED_)
