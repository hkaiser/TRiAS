// @doc
// @module SimpleStatistics.cpp | Implementation of the <c CSimpleStatistics> class

#include "stdafx.h"

#include <ospace/stlex/mathops.h>
#include <Com/SafeArray.h>

#include "StatistApp.h"
#include "TRiASSimpleStatistics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASSimpleStatistics, CSimpleStatistics)

/////////////////////////////////////////////////////////////////////////////
// nützliche Berechnungs-Funktionen
inline double Sqr (double dVal)
{
	return dVal*dVal;
}

inline double Average (ULONG N, double dSum)
{
	_ASSERTE(N > 0);
	return dSum/N;
}

inline double Deviation (long N, double dSqrSum, double dSum)
{
	_ASSERTE(N > 1);
	return sqrt(1.0/(N-1) * (dSqrSum - N * Sqr (Average (N, dSum))));
}

/////////////////////////////////////////////////////////////////////////////
// CSimpleStatistics

STDMETHODIMP CSimpleStatistics::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASSimpleStatistics
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CSimpleStatistics::get_Count(ULONG *pVal)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	CHECKOUTPOINTER(pVal);

	*pVal = m_lCount;
	return S_OK;
}

STDMETHODIMP CSimpleStatistics::get_Sum(double *pVal)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	CHECKOUTPOINTER(pVal);

	*pVal = m_dSum;
	return S_OK;
}

STDMETHODIMP CSimpleStatistics::get_CountNotNull(ULONG *pVal)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	CHECKOUTPOINTER(pVal);

	*pVal = m_lCountNotNull;
	return S_OK;
}

STDMETHODIMP CSimpleStatistics::get_ArithmeticAverage(double *pVal)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	CHECKOUTPOINTER(pVal);
	ERROR_EXPR_FALSE(m_lCount > 0, STATIST_E_BADCOUNTERVALUE);

	*pVal = Average (m_lCount, m_dSum);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Logarithmus für geometrisches Mittel berechnen
struct CLog :
	public unary_function<double, double>
{
	double operator()(double x) 
	{ 
		if (x <= 0.0)
			_com_issue_error(STATIST_E_BADDATAVALUE);
		return log(x); 
	}
};

STDMETHODIMP CSimpleStatistics::get_GeometricAverage(double *pVal)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	CHECKOUTPOINTER(pVal);
	ERROR_EXPR_FALSE(m_lCount > 0, STATIST_E_BADCOUNTERVALUE);

	COM_TRY {
		*pVal = exp(average(m_Values.begin(), m_Values.end(), double(0), CLog()));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CSimpleStatistics::get_Median(double *pVal)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	CHECKOUTPOINTER(pVal);
	ERROR_EXPR_FALSE(m_lCount > 0, STATIST_E_BADCOUNTERVALUE);

// Werte im Set sind sortiert
CValueSet::iterator it = m_Values.begin();

	advance (it, m_Values.size()/2);
	if (m_Values.size() % 2) {
	// ungerade Anzahl von Werten
		*pVal = (*it);
	} else {
	// gerade Anzahl von Werten
	CValueSet::iterator itTmp = it++;

		*pVal = Average (2, (*it) + (*itTmp));
	}
	return S_OK;
}

STDMETHODIMP CSimpleStatistics::get_MinValue(double *pVal)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	CHECKOUTPOINTER(pVal);
	ERROR_EXPR_FALSE(m_lCount > 0, STATIST_E_BADCOUNTERVALUE);

	*pVal = m_dMin;
	return S_OK;
}

STDMETHODIMP CSimpleStatistics::get_MaxValue(double *pVal)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	CHECKOUTPOINTER(pVal);
	ERROR_EXPR_FALSE(m_lCount > 0, STATIST_E_BADCOUNTERVALUE);

	*pVal = m_dMax;
	return S_OK;
}

STDMETHODIMP CSimpleStatistics::get_Range(double *pVal)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	CHECKOUTPOINTER(pVal);
	ERROR_EXPR_FALSE(m_lCount > 0, STATIST_E_BADCOUNTERVALUE);

	*pVal = m_dMax-m_dMin;
	return S_OK;
}

STDMETHODIMP CSimpleStatistics::get_StandardDeviation(double *pVal)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	CHECKOUTPOINTER(pVal);
	ERROR_EXPR_FALSE(m_lCount > 1, STATIST_E_BADCOUNTERVALUE);

	*pVal = Deviation (m_lCount, m_dSqrSum, m_dSum);
	return S_OK;
}

STDMETHODIMP CSimpleStatistics::get_Variance(double *pVal)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	CHECKOUTPOINTER(pVal);
	ERROR_EXPR_FALSE(m_lCount > 0, STATIST_E_BADCOUNTERVALUE);
	ERROR_EXPR_FALSE(m_dSum != 0.0, STATIST_E_BADSUMVALUE);

	*pVal = 100.0 * Deviation (m_lCount, m_dSqrSum, m_dSum) / Average (m_lCount, m_dSum);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Methods
STDMETHODIMP CSimpleStatistics::AddValue(double Value, VARIANT vData)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())

	m_Values.insert(Value);

// kumulative Werte korrigieren
	m_dSum += Value;
	m_dSqrSum += Sqr(Value);

// evtl. Minimum und Maximum neu bestimmen
	if (Value < m_dMin)
		m_dMin = Value;
	if (Value > m_dMax)
		m_dMax = Value;

	m_lCount++;
	if (0.0 != Value)
		m_lCountNotNull++;

	return S_OK;
}

STDMETHODIMP CSimpleStatistics::RemoveValue(double Value)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	ERROR_EXPR_FALSE(m_lCount > 0, STATIST_E_BADCOUNTERVALUE);

// aus Wertemenge entfernen
	_ASSERTE(m_Values.find (Value) != m_Values.end());

CValueSet::iterator it = m_Values.find (Value);

	ERROR_EXPR_FALSE(m_Values.find (Value) != m_Values.end(), STATIST_E_VALUENOTFOUND);
	m_Values.erase (it);

// kumulative Werte korrigieren
	m_dSum -= Value;
	m_dSqrSum -= Sqr(Value);

// evtl. Minimum und Maximum neu bestimmen
	if (Value == m_dMin)
		m_dMin = *min_element(m_Values.begin(), m_Values.end());
	if (Value == m_dMax) 
		m_dMax = *max_element(m_Values.begin(), m_Values.end());

	m_lCount--;
	if (0.0 != Value)
		m_lCountNotNull--;
	return S_OK;
}

STDMETHODIMP CSimpleStatistics::Reset()
{
	m_Values.clear();
	m_lCount = 0L;
	m_lCountNotNull = 0L;
	m_dSum = 0.0;
	m_dSqrSum = 0.0;
	m_dMin = DBL_MAX;
	m_dMax = -DBL_MAX;
	return S_OK;
}

STDMETHODIMP CSimpleStatistics::RangesByEqualCount(
	ULONG NumberOfRanges, SAFEARRAY **pMinBounds, SAFEARRAY **pMaxBounds, 
	SAFEARRAY **pCounts, SAFEARRAY **pData)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	ERROR_EXPR_FALSE(m_lCount > 0, STATIST_E_BADCOUNTERVALUE);

CSafeArray saMinBounds (VT_R8);
CSafeArray saMaxBounds (VT_R8);
CSafeArray saCounts (VT_I4);

	ERROR_EXPR_FALSE(NULL != pMinBounds && saMinBounds.Attach (*pMinBounds, true), STATIST_E_BADMINBOUNDSARRAY);
	ERROR_EXPR_FALSE(NULL != pMaxBounds && saMaxBounds.Attach (*pMaxBounds, true), STATIST_E_BADMAXBOUNDSARRAY);
	ERROR_EXPR_FALSE(NULL != pCounts && saCounts.Attach (*pCounts, true), STATIST_E_BADCOUNTSARRAY);

	{
	CSafeArrayLock<double> MinBounds(saMinBounds);
	CSafeArrayLock<double> MaxBounds(saMaxBounds);
	CSafeArrayLock<ULONG> Counts(saCounts);

	// als erstes die Bereichsgrenzen bestimmen
	ULONG lCnt = m_lCount/NumberOfRanges;		// Anzahl der Werte in einem Intervall
	CValueSet::iterator it = m_Values.begin();
	ULONG iAct = 0;

		while (it != m_Values.end()) {
			if (iAct < NumberOfRanges) 
				MinBounds[iAct] = *it;
			if (iAct > 0)
				MaxBounds[iAct-1] = *it;

			Counts[iAct] = 0;
		
		// die nächste Bereichsgrenze bitte
		double dAct = *it;

			advance (it, lCnt);	// mindesten die geforderte Anzahl der Elemente überspringen
			while (it != m_Values.end() && *it == dAct)
				++it;			// gehört noch zum vorhergehenden Intervall
			iAct++;
		}
		if (iAct > 0)			// den letzten Wert nicht vergessen
			MaxBounds[iAct-1] = m_dMax;

	// evtl. noch überzählige Bereiche initialisieren
		while (iAct < NumberOfRanges) {
			if (iAct < NumberOfRanges) 
				MinBounds[iAct] = 0.0;
			if (iAct > 0)
				MaxBounds[iAct-1] = 0.0;
			iAct++;
		}
		_ASSERTE(iAct == NumberOfRanges);

#if defined(_DEBUG)
	// testen, ob die Bereiche gültig sind
		for (ULONG iDebug = 0; iDebug < NumberOfRanges; iDebug++) {
			_ASSERTE(MinBounds[iDebug] <= MaxBounds[iDebug]);
			_ASSERTE(iDebug == 0 || (MinBounds[iDebug] == MaxBounds[iDebug-1]));
		}
#endif // _DEBUG

	// Werte auf die Bereiche verteilen und deren Anzahl bestimmen
		for (it = m_Values.begin(); it != m_Values.end(); ++it) {
			for (ULONG i = 0; i < NumberOfRanges; i++) {
				if (MinBounds[i] <= *it && *it < MaxBounds[i]) {
					Counts[i]++;
					break;			// der nächste bitte
				}
			}
		}
		_ASSERTE(iAct == NumberOfRanges);

#if defined(_DEBUG)
	// nachzählen, ob alle Werte zugeordnet wurden
	ULONG lCountDeb = 0;

		for (ULONG iDebug2 = 0; iDebug2 < NumberOfRanges; iDebug2++) 
			lCountDeb += Counts[iDebug2];
		_ASSERTE(lCountDeb == m_Values.size());		// alle erwischt ?
#endif // _DEBUG
	}
	return S_OK;
}

STDMETHODIMP CSimpleStatistics::RangesByEqualRange(
	ULONG NumberOfRanges, double dStartValue, double dEndValue, 
	SAFEARRAY **pMinBounds, SAFEARRAY **pMaxBounds, 
	SAFEARRAY **pCounts, SAFEARRAY **pData)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	ERROR_EXPR_FALSE(m_lCount > 0, STATIST_E_BADCOUNTERVALUE);

CSafeArray saMinBounds (VT_R8);
CSafeArray saMaxBounds (VT_R8);
CSafeArray saCounts (VT_I4);

	ERROR_EXPR_FALSE(NULL != pMinBounds && saMinBounds.Attach (*pMinBounds, true), STATIST_E_BADMINBOUNDSARRAY);
	ERROR_EXPR_FALSE(NULL != pMaxBounds && saMaxBounds.Attach (*pMaxBounds, true), STATIST_E_BADMAXBOUNDSARRAY);
	ERROR_EXPR_FALSE(NULL != pCounts && saCounts.Attach (*pCounts, true), STATIST_E_BADCOUNTSARRAY);

	{
	CSafeArrayLock<double> MinBounds(saMinBounds);
	CSafeArrayLock<double> MaxBounds(saMaxBounds);
	CSafeArrayLock<ULONG> Counts(saCounts);

	// als erstes die Bereichsgrenzen bestimmen
	double dDelta = (dEndValue-dStartValue)/NumberOfRanges;
	ULONG iAct = 0;

		for (double dMin = dStartValue; dMin < dEndValue; dMin += dDelta, iAct++) {
			MinBounds[iAct] = dMin;
			MaxBounds[iAct] = dMin + dDelta;
			Counts[iAct] = 0L;
		}
		_ASSERTE(iAct == NumberOfRanges);

	// Werte auf die Bereiche verteilen und deren Anzahl bestimmen
		for (CValueSet::iterator it = m_Values.begin(); it != m_Values.end(); ++it) {
		LONG iIndex = static_cast<LONG>(((*it) - dStartValue) / dDelta);	// abrunden

			_ASSERTE(0 <= iIndex && iIndex < NumberOfRanges);
			Counts[iIndex]++;		// Wert zählen
		}

#if defined(_DEBUG)
	// nachzählen, ob alle Werte zugeordnet wurden
	ULONG lCountDeb = 0;

		for (ULONG iDebug2 = 0; iDebug2 < NumberOfRanges; iDebug2++) 
			lCountDeb += Counts[iDebug2];
		_ASSERTE(lCountDeb == m_Values.size());		// alle erwischt ?
#endif // _DEBUG
	}
	return S_OK;
}

STDMETHODIMP CSimpleStatistics::RangesByStandardDeviation(
	ULONG NumberOfRanges, SAFEARRAY **pMinBounds, SAFEARRAY **pMaxBounds, 
	SAFEARRAY **pCounts, SAFEARRAY **pData)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	ERROR_EXPR_FALSE(m_lCount > 0, STATIST_E_BADCOUNTERVALUE);

CSafeArray saMinBounds (VT_R8);
CSafeArray saMaxBounds (VT_R8);
CSafeArray saCounts (VT_I4);

	ERROR_EXPR_FALSE(NULL != pMinBounds && saMinBounds.Attach (*pMinBounds, true), STATIST_E_BADMINBOUNDSARRAY);
	ERROR_EXPR_FALSE(NULL != pMaxBounds && saMaxBounds.Attach (*pMaxBounds, true), STATIST_E_BADMAXBOUNDSARRAY);
	ERROR_EXPR_FALSE(NULL != pCounts && saCounts.Attach (*pCounts, true), STATIST_E_BADCOUNTSARRAY);

	{
	CSafeArrayLock<double> MinBounds(saMinBounds);
	CSafeArrayLock<double> MaxBounds(saMaxBounds);
	CSafeArrayLock<ULONG> Counts(saCounts);

	// als erstes die Bereichsgrenzen bestimmen
	double dDev = Deviation (m_lCount, m_dSqrSum, m_dSum);
	double dAve = Average (m_lCount, m_dSum);
	double dMin = dAve - (NumberOfRanges/2) * dDev;
	double dMax = dAve + (NumberOfRanges/2 + NumberOfRanges%2) * dDev;
	ULONG iAct = 0;

		for (double dCurr = dMin; dCurr < dMax; dCurr += dDev, iAct++) {
			MinBounds[iAct] = dCurr;
			MaxBounds[iAct] = dCurr + dDev;
			Counts[iAct] = 0L;
		}
		_ASSERTE(iAct == NumberOfRanges);

	// Werte auf die Bereiche verteilen und deren Anzahl bestimmen
		for (CValueSet::iterator it = m_Values.begin(); it != m_Values.end(); ++it) {
		LONG iIndex = static_cast<LONG>(((*it) - dAve) / dDev) + NumberOfRanges/2;	// abrunden

			_ASSERTE(0 <= iIndex && iIndex < NumberOfRanges);
			Counts[iIndex]++;		// Wert zählen
		}

#if defined(_DEBUG)
	// nachzählen, ob alle Werte zugeordnet wurden
	ULONG lCountDeb = 0;

		for (ULONG iDebug2 = 0; iDebug2 < NumberOfRanges; iDebug2++) 
			lCountDeb += Counts[iDebug2];
		_ASSERTE(lCountDeb == m_Values.size());		// alle erwischt ?
#endif // _DEBUG
	}
	return S_OK;
}
