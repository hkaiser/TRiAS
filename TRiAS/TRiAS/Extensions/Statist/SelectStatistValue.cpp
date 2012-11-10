// $Header: $
// Copyright© 1999 TRiAS GmbH Potsdam, All rights reserved
// Created: 29.08.99 21:18:39
//
// @doc
// @module SelectStatistValue.cpp | Implementation of the <c CSelectStatistValue> class

#include "stdafx.h"

#include <ObjectPropertyResult.h>

#include "StatistApp.h"
#include "SelectStatistValue.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRYEX(SelectStatistValue)

/////////////////////////////////////////////////////////////////////////////
// CSelectStatistValue
// IPropertyAction 

STDMETHODIMP CSelectStatistValue::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.Clear();
	
	if (NULL != m_pCfgDlg) {
	// nur nach der Konfiguration
		m_strObjProp = m_pCfgDlg -> GetSelectedObjPropName();
		m_strStatFunc = m_pCfgDlg -> GetSelectedStatFuncName();
		m_ObjProp = m_pCfgDlg -> GetObjProp();
		m_StatFunc = m_pCfgDlg -> GetStatFunc();
		m_fEvalRelation = m_pCfgDlg -> GetEvalRelation();
		m_fInvertValue = m_pCfgDlg -> GetInvertValue();
	}
	m_StatFunc -> Reset();		// StatFunc zurücksetzen

	return S_OK;
}

STDMETHODIMP CSelectStatistValue::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{
// Eingabeobjekte einfach mit zu unserer Objektmenge hinzufügen
	COM_TRY {
	WEnumLONG EnumObjs;
	OutEnumLONG iter_out_if (&m_Objects);

		THROW_FAILED_HRESULT(PropActBase::GetEnumObjects (pIDataObj, __uuidof(IEnumLONG), EnumObjs.ppv()));
		copy (InEnumLONG(EnumObjs), InEnumLONG(), iter_out_if);

	} COM_CATCH;
	return S_OK;
}

namespace {
///////////////////////////////////////////////////////////////////////////////
// Klasse, die die Verarbeitung der einzelnen Objekte der Eingabemenge erlaubt
	class CSelectStatistValueWorker 
	{
	public:
		CSelectStatistValueWorker(CSelectStatistValue *pThis) : 
			m_pThis(pThis)
		{
			m_ObjProp = m_pThis -> GetObjProp();
			m_StatFunc = m_pThis -> GetStatFunc();

			_ASSERTE(m_ObjProp.IsValid());
			_ASSERTE(m_StatFunc.IsValid());
		}
		~CSelectStatistValueWorker() {}

	// wird für jedes zu bearbeitende Objekt gerufen
		void operator() (LONG lONr)
		{
			_ASSERTE(NULL != m_pThis);
			m_pThis -> Tick();			// ProgressIndikator weitersetzen
			if (FAILED(m_pThis -> GoOn()))
				_com_issue_error(E_ABORT);

		// Wert berechnen und zur StatFunc hinzufügen
		char cbBuffer[_MAX_PATH];

			if (SUCCEEDED(m_ObjProp -> Eval(lONr, cbBuffer, sizeof(cbBuffer), NULL))) {
			double dVal = atof (cbBuffer);

				m_StatFunc -> AddValue (dVal, vtMissing);
			}
		}

	private:
		CSelectStatistValue *m_pThis;

		WObjectProperty m_ObjProp;
		WGenericStatistics m_StatFunc;
	};
} // namespace

STDMETHODIMP CSelectStatistValue::EndAction (DWORD, IDataObject **ppDataObj)
{
HRESULT hr = S_OK;

	if (NULL != ppDataObj)
		*ppDataObj = NULL;		// liefert niemals eine Objektmenge

	COM_TRY {
	// ProgressIndikator initialisieren
		SetMaxTicks (m_Objects.Count());

	// eigentliche Verarbeitung (aufsammeln der einzelnen Werte)
		for_each(InEnumLONG(&m_Objects), InEnumLONG(), CSelectStatistValueWorker(this));

	// Wert der StatFunc abfragen und in Sequence speichern
	WDataObject DO;
	WPropertyActionSequence Seq;

		THROW_FAILED_HRESULT(GetSite (__uuidof(IPropertyActionSequence), Seq.ppv()));
		THROW_FAILED_HRESULT(Seq -> GetSequenceContext (DO.ppi()));

	CComVariant vVal;

		THROW_FAILED_HRESULT(m_StatFunc -> Calculate(&vVal));

	// zusätzliche Optionen auswerten
		if (m_fEvalRelation) {
		CComVariant vONrTarget;		// Bezugsobjekt

			THROW_FAILED_HRESULT(PropActBase::GetVariantData(DO, &c_feObjPropTarget, &vONrTarget));

		char cbBuffer[_MAX_PATH];

			THROW_FAILED_HRESULT(vONrTarget.ChangeType(VT_I4));
			if (SUCCEEDED(m_ObjProp -> Eval(V_I4(&vONrTarget), cbBuffer, sizeof(cbBuffer), NULL))) {
			double dVal = atof(cbBuffer);

				if (0.0 != dVal)
					V_R8(&vVal) = V_R8(&vVal)/dVal;
				else
					hr = E_FAIL;		// Objekteigenschaft ist nicht berechenbar
			}
			if (SUCCEEDED(hr) && m_fInvertValue) {
				if (0.0 != V_R8(&vVal))
					V_R8(&vVal) = 1.0/V_R8(&vVal);
				else
					hr = E_FAIL;		// Objekteigenschaft ist nicht berechenbar
			}
		}
	
	// ggf. Resultat setzen
		if (SUCCEEDED(hr))
		{
			THROW_FAILED_HRESULT(PropActBase::SetVariantData(vVal, DO, &c_feObjPropResult));
		}
		DELETE_OBJ(m_pCfgDlg);

	} COM_CATCH_NOASSERT_ON(E_ABORT);
	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CSelectStatistValue::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CSelectStatistValue::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));
	RETURN_FAILED_HRESULT(LoadString(pStm, m_strObjProp));
	RETURN_FAILED_HRESULT(LoadString(pStm, m_strStatFunc));
	RETURN_FAILED_HRESULT(LoadData(pStm, m_fEvalRelation));
	RETURN_FAILED_HRESULT(LoadData(pStm, m_fInvertValue));

	SetInitialized();
	return S_OK;
}

STDMETHODIMP CSelectStatistValue::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));
	RETURN_FAILED_HRESULT(SaveString(pStm, m_strStatFunc));
	RETURN_FAILED_HRESULT(SaveString(pStm, m_strObjProp));
	RETURN_FAILED_HRESULT(SaveData(pStm, m_fEvalRelation));
	RETURN_FAILED_HRESULT(SaveData(pStm, m_fInvertValue));

	return S_OK;
}

STDMETHODIMP CSelectStatistValue::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));
	pcbSize -> QuadPart += ::GetSizeMax(m_strObjProp);
	pcbSize -> QuadPart += ::GetSizeMax(m_strStatFunc);
	pcbSize -> QuadPart += 2*sizeof(bool);

	return S_OK;
}

STDMETHODIMP CSelectStatistValue::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

	m_strObjProp.erase();
	m_strStatFunc.erase();
	m_fEvalRelation = false;
	m_fInvertValue = false;

	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CSelectStatistValue::AddConfigPages (
	LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState());
	if (puiCnt) *puiCnt = 0;		// initialisieren

	COM_TRY {
	char cbCaption[128];

		if (NULL != pcDesc)	{	// Caption ist gegeben
			_ASSERTE(strlen(pcDesc) < sizeof(cbCaption));
			strcpy (cbCaption, pcDesc);
		} else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
		m_pCfgDlg = CSelectStatistValueDlg::CreateInstance(cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

		if (!IsNoShow()) {
		// Seite hizufügen, wenn selbige angezeigt werden soll
		PROPSHEETPAGE psp;

			memcpy(&psp, &m_pCfgDlg->m_psp, sizeof(PROPSHEETPAGE));
		
		HPROPSHEETPAGE hPSP = ::CreatePropertySheetPage (&psp);

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;

			if (puiCnt) 
				*puiCnt = 1;		// wir haben eine Page hinzugefügt

		// Initialisierungsdaten
			m_pCfgDlg -> SetInitData (m_strObjProp.c_str(), m_strStatFunc.c_str(), m_fEvalRelation, m_fInvertValue);
		} 
		
	} COM_CATCH_OP(delete m_pCfgDlg);
	return S_OK;
}  

STDMETHODIMP CSelectStatistValue::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;

	m_pCfgDlg -> SetFlags(dwFlags);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
namespace {

	typedef struct tagSTATFUNCNAME {
		char const *pShortName;
		UINT uiLongName;
	} STATFUNCNAME;

	STATFUNCNAME g_StatFuncs[] = {
		{ "Count", IDS_STATISTCOUNT_NAME },
		{ "CountNotNull", IDS_STATISTCOUNTNOTNULL_NAME },
		{ "Sum", IDS_STATISTSUM_NAME },
		{ "ArithmeticAverage", IDS_STATISTARITHAVERAGE_NAME },
		{ "GeometricAverage", IDS_STATISTGEOMAVERAGE_NAME },
		{ "Median", IDS_STATISTMEDIAN_NAME },
		{ "MinValue", IDS_STATISTMINVALUE_NAME },
		{ "MaxValue", IDS_STATISTMAXVALUE_NAME },
		{ "Range", IDS_STATISTRANGE_NAME },
		{ "StandardDeviation", IDS_STATISTDEVIATION_NAME },
		{ "Variance", IDS_STATISTVARIANCE_NAME },
		{ NULL, 0 },
	};
}

STDMETHODIMP CSelectStatistValue::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pBag, pLog));

	m_fInvertValue = false;
	m_fEvalRelation = false;
	m_strStatFunc.erase();

// StatFunc=
CComVariant vStatFunc;
HRESULT hr = pBag -> Read (CComBSTR("StatFunc"), &vStatFunc, pLog);

	if (S_OK == hr && SUCCEEDED(vStatFunc.ChangeType(VT_BSTR))) {
	CString strStatFunc = OLE2A(V_BSTR(&vStatFunc));
	STATFUNCNAME *pFunc = g_StatFuncs;

		while (NULL != pFunc->pShortName) {
			if (strStatFunc == pFunc->pShortName) {
			CString strLongName;

				strLongName.LoadString(pFunc->uiLongName);
				_ASSERTE(strLongName.GetLength() > 0);
				m_strStatFunc = strLongName;
			}
		}		
	}

// CalcInverseValue=
CComVariant vCalcInverseValue;

	hr = pBag -> Read (CComBSTR("CalcInverseValue"), &vCalcInverseValue, pLog);
	if (S_OK == hr && SUCCEEDED(vCalcInverseValue.ChangeType(VT_BOOL))) 
		m_fInvertValue = V_BOOL(&vCalcInverseValue);

// CalcRelativeToTarget=
CComVariant vCalcRelativeToTarget;

	hr = pBag -> Read (CComBSTR("CalcRelativeToTarget"), &vCalcRelativeToTarget, pLog);
	if (S_OK == hr && SUCCEEDED(vCalcRelativeToTarget.ChangeType(VT_BOOL))) 
		m_fEvalRelation = V_BOOL(&vCalcRelativeToTarget);

	return S_OK;
}

