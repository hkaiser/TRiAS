/*
Datei: MULTIPI.CPP

Der Modul realisiert die Unterteilung (Verwaltung) mehrerer Progressindicatoren.

Erarbeitet:	J. Benkenstein				Stand vom: 4.4.1997
Überarbeitet : J. Günther				ab 14.9.98
				Der SubIndicator verwaltet jetzt den Statustext selbst
*/

#include "trias03p.hxx"				//	vorübersetzter Header
#include "trias03.h"

#include <statguid.h>

//	Projekt-Header
#include "multipi.h"				//	zugeh. Header

//	Konstanten
const ULONG ulMinBereich = 0;		//	min. und	
const ULONG ulMaxBereich = 10000;	//	max. Bereichswerte 

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	CSubIndicator -----------------------------------------------------
CSubIndicator :: CSubIndicator (void)
{
	m_ulActPos = m_ulMinBer = m_ulMinWert = 0;
	m_ulMaxBer = m_ulMaxWert = 1;
}

CSubIndicator :: ~CSubIndicator (void)
{
//	nothing to do
}
//
// IProgressIndicator 
// 
// Basisimplementation : einfach Parameter weiterreichen
// evtl. Probleme bei WasCanceled
STDMETHODIMP_(HWND) CSubIndicator::InitNew(THIS_ HWND hWnd, DWORD dwReserved)
{
	COM_TRY {
		WProgressIndicator PI;
		PI = m_wPI;
		return PI -> InitNew (hWnd, dwReserved);
	} COM_CATCH_RETURN(NULL)
}
STDMETHODIMP CSubIndicator::Restart(THIS_ LONG uiMinPos, LONG ulMaxPos, DWORD dwFlags)
{
	COM_TRY {
		WProgressIndicator PI;
		PI = m_wPI;
		RETURN_FAILED_HRESULT(PI -> Restart(uiMinPos, ulMaxPos, dwFlags));
		return SetStatusText();
	} COM_CATCH
}
STDMETHODIMP CSubIndicator::ChangeText(THIS_ DWORD dwWhichText, LPCSTR pcNewText)
{
	COM_TRY {
		WProgressIndicator PI;
		PI = m_wPI;

		// erstmal generell die verlangte Aktion ausführen
		HRESULT hr = PI -> ChangeText(dwWhichText, pcNewText);

		// wenn der Statustext geändert wird, dann diesen Text ab sofort von hier aus handeln
		if (dwWhichText & PIFLAG_ADJUSTPERCENT || dwWhichText & PIFLAG_STATUS)
		{
			m_strPercentText = pcNewText;
			RETURN_FAILED_HRESULT(SetStatusText());
		}

		return hr;
	} COM_CATCH
}

STDMETHODIMP CSubIndicator::RetrieveText(THIS_ DWORD dwWichText, LPSTR cbText, ULONG uiLen)
{
	COM_TRY {
		WProgressIndicator PI;
		PI = m_wPI;
		return PI -> RetrieveText(dwWichText, cbText, uiLen);
	} COM_CATCH
}

STDMETHODIMP_(int) CSubIndicator::SetPosition(THIS_ LONG uiNewPos)
{
	// Da existiert schon eine Logic
	int iPercent;
	SetPosition(uiNewPos, &iPercent);
	return iPercent;
}
STDMETHODIMP_(BOOL) CSubIndicator::WasCanceled(void)
{
	COM_TRY {
		WProgressIndicator PI;
		PI = m_wPI;
		return PI -> WasCanceled();
	} COM_CATCH_RETURN(FALSE)
}

// #if _MSC_VER >= 1100
STDMETHODIMP CSubIndicator :: InitNew (LONG hWnd, LONG dwReserved, LONG *phWnd)
// #else
//STDMETHODIMP CSubIndicator :: InitNew (HWND hWnd, DWORD dwReserved, HWND *phWnd)
//#endif // _MSC_VER >= 1100
{
	TX_ASSERT (NULL != (IProgressIndicator2 *) m_wPI);
	return m_wPI -> InitNew (hWnd, dwReserved, phWnd);
}

#define NAMEBUFFERSIZE	1024
HRESULT CSubIndicator::SetStatusText()
{
 	// habe ich die Kontrolle über den Statustext ?
	if (0 == m_strPercentText.length())
		return S_OK;

	// ja, ich habe die Kontrolle
	// Puffer anlegen und initialisieren
	char cTmp[NAMEBUFFERSIZE];
	long actProzent = m_ulActPos * 100 / (m_ulMaxWert - m_ulMinWert);
	
	wsprintf(cTmp, m_strPercentText.c_str(), actProzent);


	// da der eigentliche Indicator auch ein wsprintf ausführt,
	// muß jedes vorhandene % Zeichen gedoppelt werden
	string strTmp(cTmp);
	long i = 0;

	while (-1 != (i = strTmp.find(_T("%"), i)))
	{
		strTmp.insert(i, _T("%"));
		i += 2;		// eine Stelle (+1) nach dem eingefügten Zeichen (+1) weitersuchen
	}

	// und weiterreichen
	COM_TRY {
		WProgressIndicator PI = m_wPI;		// throw
		return PI -> ChangeText(PIFLAG_ADJUSTPERCENT, strTmp.c_str());
	} COM_CATCH
}

STDMETHODIMP CSubIndicator :: ChangeText (PIFLAGS fWhichText, BSTR bstrNewText)
{
	TX_ASSERT (NULL != (IProgressIndicator2 *) m_wPI);

	// erstmal generell die verlangte Aktion ausführen
	HRESULT hr = m_wPI -> ChangeText (fWhichText, 
		(NULL == bstrNewText) ? CComBSTR("") : bstrNewText);		 

	// wenn der Statustext geändert wird, dann diesen Text ab sofort von hier aus handeln
	if (fWhichText & PIFLAG_ADJUSTPERCENT || fWhichText & PIFLAG_STATUS)
	{
		USES_CONVERSION;
		if (NULL == bstrNewText)
			m_strPercentText = "";
		else
			m_strPercentText = OLE2A(bstrNewText);
		RETURN_FAILED_HRESULT(SetStatusText());
	}

	return hr;
}

STDMETHODIMP CSubIndicator :: RetrieveText (PIFLAGS fWichText, BSTR *pbstrText)
{
	TX_ASSERT (NULL != (IProgressIndicator2 *) m_wPI);
	return m_wPI -> RetrieveText (fWichText, pbstrText); 		
}

STDMETHODIMP CSubIndicator :: IsCanceled (VOID)
{
	TX_ASSERT (NULL != (IProgressIndicator2 *) m_wPI);
	return m_wPI -> IsCanceled ();
}

STDMETHODIMP CSubIndicator::get_Canceled (VARIANT_BOOL *pfCanceled)
{
	TX_ASSERT (NULL != (IProgressIndicator2 *) m_wPI);
	if (NULL == pfCanceled)
		return E_POINTER;
	*pfCanceled = (S_OK == m_wPI -> IsCanceled()) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CSubIndicator :: get_Flags (PIFLAGS *prgFlags)
{
	TX_ASSERT (NULL != (IProgressIndicator2 *) m_wPI);
	return m_wPI -> get_Flags (prgFlags);
}

STDMETHODIMP CSubIndicator :: put_Flags (PIFLAGS rgFlags)
{
	TX_ASSERT (NULL != (IProgressIndicator2 *) m_wPI);
	return m_wPI -> put_Flags (rgFlags);
}

STDMETHODIMP CSubIndicator :: RetrieveRange (LONG *pulMinPos, LONG *pulMaxPos)
{
	TX_ASSERT (NULL != (IProgressIndicator2 *) m_wPI);
	return m_wPI -> RetrieveRange (pulMinPos, pulMaxPos);
}

//	liefert akt. Prozente
STDMETHODIMP CSubIndicator :: SetPosition (LONG ulNewPos, INT *piPercent)
{
	if (NULL == piPercent)
		return E_POINTER;

	TX_ASSERT (NULL != (IProgressIndicator2 *) m_wPI);
	TX_ASSERT (m_ulMinBer >= 0);
	TX_ASSERT (m_ulMaxBer > m_ulMinBer);
	TX_ASSERT (m_ulMinWert >= 0);
	TX_ASSERT (m_ulMaxWert > m_ulMinWert);

//	Division durch 0 verhindern
	if (m_ulMinWert == m_ulMaxWert)
		return 0;
	
	m_ulActPos = ulNewPos;			// Position merken
	double dNewPos = m_ulMinBer + ((double)ulNewPos * (((double)(m_ulMaxBer - m_ulMinBer)) / (m_ulMaxWert - m_ulMinWert)));
	ulNewPos = ULONG (dNewPos + 0.5);
	
	RETURN_FAILED_HRESULT(m_wPI -> SetPosition (ulNewPos, piPercent));
	return SetStatusText();
}

//	liefert akt. Prozente
STDMETHODIMP CSubIndicator :: IncrementPosition (INT *piPercent)
{
	if (NULL == piPercent)
		return E_POINTER;

	return SetPosition (++m_ulActPos, piPercent);	
};

STDMETHODIMP CSubIndicator :: Restart (LONG ulMinPos, LONG ulMaxPos, PIFLAGS fFlags)
{
	TX_ASSERT (NULL != (IProgressIndicator2 *) m_wPI);
	TX_ASSERT (ulMinPos >= 0);
	TX_ASSERT (ulMaxPos > ulMinPos);
	TX_ASSERT (m_ulMinBer >= 0);
	TX_ASSERT (m_ulMaxBer > m_ulMinBer);

	m_ulActPos = m_ulMinWert = ulMinPos;
	m_ulMaxWert = ulMaxPos;

	int iPercent = 0;
	HRESULT hr = m_wPI -> SetPosition (m_ulMinBer, &iPercent);
	if (SUCCEEDED(hr))
		hr = m_wPI -> put_Flags (fFlags);

	RETURN_FAILED_HRESULT(SetStatusText());
	return hr;
}

STDMETHODIMP CSubIndicator::Show ()
{
	_ASSERTE(m_wPI.IsValid());
	return m_wPI -> Show();
}

STDMETHODIMP CSubIndicator::Hide()
{
	_ASSERTE(m_wPI.IsValid());
	return m_wPI -> Hide();
}

// CMultiProgressIndicator ----------------------------------------------------
CMultiProgressIndicator :: CMultiProgressIndicator (void)
{
	m_ppPI = NULL;
	m_iRangeCnt = 0;
}

CMultiProgressIndicator :: ~CMultiProgressIndicator ()
{
	DeletePIs ();
}

STDMETHODIMP CMultiProgressIndicator :: DeletePIs (void)
{
	if ((m_iRangeCnt <= 0) || (NULL == m_ppPI)) 
		return S_OK;

	for (int i = 0; i < m_iRangeCnt; i++)
		m_ppPI [i] -> Release ();
	
	DELETE_VEC (m_ppPI);
	m_iRangeCnt = 0;

	return S_OK;
}

STDMETHODIMP CMultiProgressIndicator :: get_RangeCnt (int *piRangeCnt)
{
	if (NULL == piRangeCnt)
		return E_POINTER;

	*piRangeCnt = m_iRangeCnt;

	return S_OK;
}

STDMETHODIMP CMultiProgressIndicator :: GetRange (int iRange, IProgressIndicator2 **ppPI)
{
	if (NULL == ppPI)
		return E_POINTER;

	if ((iRange < 0) || (iRange >= m_iRangeCnt))
		return E_INVALIDARG;
	if (0 == m_iRangeCnt)
		return E_UNEXPECTED;

	// *ppPI = m_ppPI [iRange] -> m_wPI;
	*ppPI = m_ppPI [iRange];
	(*ppPI) -> AddRef ();

	return S_OK;
}

STDMETHODIMP CMultiProgressIndicator :: Init (int iRangeCnt, IProgressIndicator2 *pPIInput)
{
//	prüfe Parameter
	if (NULL == pPIInput)
		return E_POINTER;

	if (iRangeCnt <= 0)
		return E_INVALIDARG;

	HRESULT hr = S_OK;

	try
	{
		hr = pPIInput -> Restart (ulMinBereich, ulMaxBereich, (PIFLAGS) 0);
		if (FAILED(hr))
			return hr;
		
	//	alten PIs löschen
		DeletePIs ();

	//	neuen PI-Vektor erzeugen u. init.
		m_ppPI = new CComObject<CSubIndicator>* [iRangeCnt];
		memset (m_ppPI, 0, sizeof (CComObject<CSubIndicator> *));

	//	Faktor berechnen
		double dFaktor = ((double)(ulMaxBereich - ulMinBereich)) / iRangeCnt;			

	//	neuen PIs erzeugen
		m_iRangeCnt = 0;
		double dBereich = 0;
		for (int i = 0; i < iRangeCnt; i++)
		{
		//	PI erzeugen
			CComObject<CSubIndicator> *pPI = NULL;
			hr = CComObject<CSubIndicator>::CreateInstance (&pPI);
			if (FAILED (hr))
				_com_issue_error(hr);
			pPI -> AddRef ();

		//	Zähler erhöhen
			m_iRangeCnt++;	

		//	akt. PI init.
			pPI -> m_wPI = pPIInput;
			dBereich = (i * dFaktor) + ulMinBereich;
			pPI -> m_ulMinBer = ULONG (dBereich + 0.5);
			dBereich = ((i+1) * dFaktor) + ulMinBereich;
			pPI -> m_ulMaxBer = ULONG (dBereich + 0.5);

		//	und Zeiger speichern
			m_ppPI [i] = pPI;
		}
	}
	catch (_com_error& hr)
	{
	//	PIs löschen
		DeletePIs ();
		return _COM_ERROR(hr);
	}
	catch (...)
	{
	//	PIs löschen
		DeletePIs ();
		return E_OUTOFMEMORY;
	}

	return S_OK;
}

