// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 28.12.2000 17:40:09
//
// @doc
// @module MathOperationProperty.cpp | Implementation of the <c CMathOperationProperty> class

#include "stdafx.h"

#include "Statist.h"
#include "MathOperationProperty.h"
#include "MathOperationPropertyDlg.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRYEX(MathOperationProperty)

/////////////////////////////////////////////////////////////////////////////
// CMathOperationProperty

// IObjectProperty specifics
STDMETHODIMP CMathOperationProperty::Reset (void)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	
	RETURN_FAILED_HRESULT(m_CumPts -> Reset());
	return CMathOperationProperty::Reset();
}

STDMETHODIMP CMathOperationProperty::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
// erstmal Basisklasse arbeiten lassen	
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	_ASSERT(m_fIsValid && MATHOPERATION_Unknown == m_rgMathOp);

	RETURN_FAILED_HRESULT(CObjectPropertyBase::GetPropInfo (pBuffer, wLen, pdwData));
	if (pdwData) {	
		*pdwData |= PROPCAPS_OBJPROPTYPE_DOUBLE;
		if (!m_fIsValid)
			*pdwData |= PROPCAPS_INTERACTIVE_INIT;	// muß noch initialisiert werden
		else {
		// ggf. Objekttypen ausblenden
			if (!(m_iObjTyp & OTPunkt))
				*pdwData |= PROPCAPS_OBJPROPTYPE_NOT_FOR_POINTS;
			if (!(m_iObjTyp & OTLinie))
				*pdwData |= PROPCAPS_OBJPROPTYPE_NOT_FOR_LINES;
			if (!(m_iObjTyp & OTFlaeche))
				*pdwData |= PROPCAPS_OBJPROPTYPE_NOT_FOR_AREAS;
			if (!(m_iObjTyp & OTText))
				*pdwData |= PROPCAPS_OBJPROPTYPE_NOT_FOR_TEXTS;
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Kumulativer Wert dieser Objekteigenschaft 
STDMETHODIMP CMathOperationProperty::Cumulation (
	LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pBuffer) 
		return E_POINTER;

	_ASSERTE(0 != ulLen);

// TODO: kumulativen Wert dieser Objekteigenschaft als Zeichenkette liefern
//	if (ulLen > ...) {
//		strcpy (pBuffer, ...);
//		if (pulWritten) 
//			*pulWritten = strlen (pBuffer);
//		return S_OK;
//	}
	return E_INVALIDARG;
}

///////////////////////////////////////////////////////////////////////////////
// Berechnen dieser Objekteigenschaft
STDMETHODIMP CMathOperationProperty::Eval (
	LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pBuffer) 
		return E_POINTER;

	if (!m_fIsValid) {
	// Konfigurieren
	}

	_ASSERTE(0 != ulLen);
	if (m_fIsValid && m_iObjTyp == DEX_GetObjectType(lONr)) {
	// Objekteigenschaften ausrechnen
	char cbBuffer[_MAX_PATH];
	double dVal1 = 0.0;
	double dVal2 = 0.0;

		if (FAILED(m_ObjProp1 -> Eval(lONr, cbBuffer, sizeof(cbBuffer), NULL)))
			return E_FAIL;
		dVal1 = atof (cbBuffer);

		if (FAILED(m_ObjProp2 -> Eval(lONr, cbBuffer, sizeof(cbBuffer), NULL)))
			return E_FAIL;
		dVal2 = atof (cbBuffer);

		switch (m_rgMathOp) {
		case MATHOPERATION_Add:
			dVal1 += dVal2;
			break;

		case MATHOPERATION_Subtract:
			dVal1 -= dVal2;
			break;

		case MATHOPERATION_Mulitply:
			dVal1 *= dVal2;
			break;

		case MATHOPERATION_Divide:
			if (0.0 == dVal2)
				return E_FAIL;
			dVal1 /= dVal2;
			break;

		default:
			_ASSERTE(MATHOPERATION_Unknown != m_rgMathOp);
			return E_FAIL;
		}
		sprintf (pBuffer, "%f", dVal1);
		if (pulWritten) 
			*pulWritten = strlen(pBuffer);

	// Infos für Kumulation sammeln
		RETURN_FAILED_HRESULT(m_CumPts -> AddValue (dVal1, vtMissing));
		IncrementCount();			// Zähler der erfolgreichen Aufrufe
		return S_OK;
	}
	return E_FAIL;		// ObjProperty existiert nicht
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CMathOperationProperty::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CMathOperationProperty::Load (IStream *pStm)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (GetInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CObjectPropertyBase::Load (pStm));

// zugehörigen Objekttyp und methmatische Operation
	RETURN_FAILED_HRESULT(LoadData(pStm, m_iObjTyp));
	RETURN_FAILED_HRESULT(LoadData(pStm, m_rgMathOp));

// die beteiligten Objekteigenschaften
os_string strObjProp1, strObjProp2;

	RETURN_FAILED_HRESULT(LoadString(pStm, strObjProp1));			// Objekteigenschaft 1
	RETURN_FAILED_HRESULT(LoadString(pStm, strObjProp2));			// Objekteigenschaft 2

	RETURN_FAILED_HRESULT(GetObjectProperty(strObjProp1.c_str(), m_ObjProp1.ppi()));
	RETURN_FAILED_HRESULT(GetObjectProperty(strObjProp2.c_str(), m_ObjProp2.ppi()));

	SetInitialized();
	return S_OK;
}

STDMETHODIMP CMathOperationProperty::Save (IStream *pStm, BOOL fClearDirty)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	RETURN_FAILED_HRESULT(CObjectPropertyBase::Save (pStm, fClearDirty));

// zugehörigen Objekttyp und methmatische Operation
	RETURN_FAILED_HRESULT(SaveData(pStm, m_iObjTyp));
	RETURN_FAILED_HRESULT(SaveData(pStm, m_rgMathOp));

// die beteiligten Objekteigenschaften
os_string strObjProp1, strObjProp2;

	RETURN_FAILED_HRESULT(GetObjectPropertyName(m_ObjProp1, strObjProp1));
	RETURN_FAILED_HRESULT(GetObjectPropertyName(m_ObjProp2, strObjProp2));

	RETURN_FAILED_HRESULT(SaveString(pStm, strObjProp1));			// Objekteigenschaft 1
	RETURN_FAILED_HRESULT(SaveString(pStm, strObjProp2));			// Objekteigenschaft 2

	return S_OK;
}

STDMETHODIMP CMathOperationProperty::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CObjectPropertyBase::GetSizeMax (pcbSize));

os_string strObjProp1, strObjProp2;

	RETURN_FAILED_HRESULT(GetObjectPropertyName(m_ObjProp1, strObjProp1));
	RETURN_FAILED_HRESULT(GetObjectPropertyName(m_ObjProp2, strObjProp2));

	pcbSize -> QuadPart += 
		sizeof(int) + sizeof(MATHOPERATION) + 
		::GetSizeMax(strObjProp1) + ::GetSizeMax(strObjProp2);

	return S_OK;
}

STDMETHODIMP CMathOperationProperty::InitNew()
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	if (GetInitialized())
		return E_UNEXPECTED;

	m_iObjTyp = OGUnknown;
	m_rgMathOp = MATHOPERATION_Unknown;
	m_fIsValid = false;

	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IConfigObjectProperty
STDMETHODIMP CMathOperationProperty::ConfigObjectProperty (HWND hWndParent)
{
	m_fIsValid = false;

os_string strObjProp1, strObjProp2;

	if (m_ObjProp1.IsValid() && m_ObjProp2.IsValid()) {
		RETURN_FAILED_HRESULT(GetObjectPropertyName(m_ObjProp1, strObjProp1));
		RETURN_FAILED_HRESULT(GetObjectPropertyName(m_ObjProp2, strObjProp2));
	}

// Konfigurationsdialog zusammenbauen
CPropertySheet Wnd(IDS_CONFIG_OBJPROP, 0, hWndParent);
CMathOperationPropertyDlg Dlg;

	Dlg.InitFromData (m_rgMathOp, strObjProp1.c_str(), strObjProp2.c_str());

// Konfigurationsdialog anzeigen
	Wnd.SetWizardMode();		// ist ein Wizard
	Wnd.AddPage(Dlg);
	if (IDOK == Wnd.DoModal()) {

		m_rgMathOp = Dlg.GetMathOp();
		strObjProp1 = Dlg.GetObjProp1();
		strObjProp2 = Dlg.GetObjProp2();

		RETURN_FAILED_HRESULT(GetObjectProperty(strObjProp1.c_str(), m_ObjProp1.ppi()));
		RETURN_FAILED_HRESULT(GetObjectProperty(strObjProp2.c_str(), m_ObjProp2.ppi()));

	// Beschreibungstext erzeugen
	UINT uiResId = 0;

		switch (m_rgMathOp) {
		case MATHOPERATION_Unknown:
			_ASSERTE(MATHOPERATION_Unknown != m_rgMathOp);	// snh
			break;

		case MATHOPERATION_Add:
			uiResId = IDS_MATHOPADD;
			break;

		case MATHOPERATION_Subtract:
			uiResId = IDS_MATHOPSUBTRACT;
			break;

		case MATHOPERATION_Mulitply:
			uiResId = IDS_MATHOPMULTIPLY;
			break;

		case MATHOPERATION_Divide:
			uiResId = IDS_MATHOPDIVIDE;
			break;
		}
	
	CString strName;

		_ASSERTE(0 != uiResId);
		strName.Format (uiResId, strObjProp1.c_str(), strObjProp2.c_str());
		
		SetName (strName);
		m_fIsValid = true;
	}
	return S_OK;
}

STDMETHODIMP CMathOperationProperty::get_IsConfigured (VARIANT_BOOL *pfConfigState)
{
	if (NULL == pfConfigState)
		return E_POINTER;
	*pfConfigState = m_fIsValid ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// finden einer Objekteigenschaft
HRESULT CMathOperationProperty::GetObjectProperty (LPCSTR pcName, IObjectProperty **ppIObjProp)
{
WObjectProps ObjProps;
BOOL fMustReInit = DEX_GetObjectProps (ObjProps.ppi());

	if (!ObjProps.IsValid())
		return E_UNEXPECTED;

	if (fMustReInit) {
		ObjProps -> OnNewReferenceObject (-1L);	// alles bisherige löschen
		if (FAILED(ObjProps -> OnNewReferenceObject (0L))) 
			return FALSE;
		DEX_SetMustInitOPFs(FALSE);
	}

WEnumObjProps EnumProps;
HRESULT hr = ObjProps -> EnumObjectProps (EnumProps.ppi());

	if (SUCCEEDED(hr)) 
		hr = EnumProps -> FindByName (pcName, ppIObjProp);
	return hr;
}

HRESULT CMathOperationProperty::GetObjectPropertyName(IObjectProperty *pIObjProp, os_string &rStrName)
{
char cbBuffer[_MAX_PATH];

	RETURN_FAILED_HRESULT(pIObjProp -> GetPropInfo(cbBuffer, sizeof(cbBuffer), NULL));
	rStrName = cbBuffer;
	return S_OK;
}

