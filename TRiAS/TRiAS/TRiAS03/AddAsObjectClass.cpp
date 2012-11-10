// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 05.01.2000 21:48:02
//
// @doc
// @module AddAsObjectClass.cpp | Implementation of the <c CAddAsObjectClass> class

#include "trias03p.hxx"
#include "trias03.h"

#include <AddAsClsPrp.h>
#include <ipropseq.hxx>
#include <funcs03.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// include the following only once
#include <Com/PersistPropertyAction.cpp>

#include "Strings.h"
#include "DataHelp.h"
#include "AddAsObjectClass.h"

extern char g_pDLLName[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
//
short OTypToBits (ObjTyp iOTyp);

/////////////////////////////////////////////////////////////////////////////
// CAddAsObjectClass
// IPropertyAction 

STDMETHODIMP CAddAsObjectClass::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.Clear();
	return S_OK;
}

STDMETHODIMP CAddAsObjectClass::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
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

	// alle Infos über eine Objektklasse besorgen
	HRESULT RetrieveObjClassDesc (LONG lIdent, os_string &rStrOKS, os_string &rStrKText, os_string &rStrLText)
	{
	PBDDATA pbdData;
	char cbKText[34] = { '\0' };
	char cbLText[5*_MAX_PATH] = { '\0' };

		INITSTRUCT(pbdData, PBDDATA);
		pbdData.pbdTyp = 'i';
		pbdData.pbdCode = lIdent;
		pbdData.pbdKText = cbKText;
		pbdData.pbdLText = cbLText;
		pbdData.pbdKTextLen = sizeof(cbKText) -1;
		pbdData.pbdLTextLen = sizeof(cbLText) -1;
		
	ErrCode RC = DEX_GetPBDData (pbdData);

		if (EC_OKAY != RC && WC_RETURN != RC)
			return HRESULT_FROM_ERRCODE(WC_NOTFOUND);

		rStrKText = cbKText;
		rStrLText = cbLText;
		
		cbLText[0] = '\0';

	HRESULT hr = ClassFromIdent (lIdent, cbLText);

		rStrOKS = cbLText;
		return hr;
	}

	// sicherstellen, daß in der Zieldatenquelle diese Objektklasse vorhanden ist
	HRESULT EnsureObjClass (LPCSTR pcOKS, LPCSTR pcKText, LPCSTR pcLText, LONG *plIdent)
	{
		COM_TRY {
		LONG lIdent = DEX_GetIdentFromClassNameEx (HACTPROJECT, pcKText);

			if (0 == lIdent) {
			// muß neu erzeugt werden
				IdentFromClass (HACTPROJECT, pcOKS, (ULONG *)&lIdent, TRUE);		// ggf. neuen Ident erzeugen

			// Beschreibungsdaten erzeugen
			PBDDATA pbdData;

				INITSTRUCT(pbdData, PBDDATA);
				pbdData.pbdTyp = 'i';
				pbdData.pbdCode = lIdent;
				pbdData.pbdKText = (LPSTR)pcKText;
				pbdData.pbdLText = (LPSTR)pcLText;
				pbdData.pbdKTextLen = (NULL != pcKText) ? strlen(pcKText) : 0;
				pbdData.pbdLTextLen = (NULL != pcLText) ? strlen(pcLText) : 0;
				DEX_ModPBDDataEx (HACTPROJECT, pbdData);
				lIdent = pbdData.pbdCode;		// kann sich geändert haben
			}
			*plIdent = lIdent;

		} COM_CATCH;
		return  S_OK;
	}

///////////////////////////////////////////////////////////////////////////////
// Klasse, die die Verarbeitung der einzelnen Objekte der Eingabemenge erlaubt
	class CAddAsObjectClassWorker 
	{
	public:
		CAddAsObjectClassWorker(OutEnumLONG &rOutIter, CAddAsObjectClass *pThis) : 
			m_pThis(pThis), m_rOutIter(rOutIter) 
		{
			RetrieveObjClassDesc (m_pThis -> GetDestClass(), m_strOKS, m_strKText, m_strLText);
		}
		~CAddAsObjectClassWorker() {}

	// wird für jedes zu bearbeitende Objekt gerufen
		void operator() (LONG lONr)
		{
			_ASSERTE(NULL != m_pThis);
			m_pThis -> Tick();			// ProgressIndikator weitersetzen
			if (FAILED(m_pThis -> GoOn()))
				_com_issue_error(E_ABORT);
				
		// sicherstellen, daß in der Zieldatenquelle (Projekt) diese Objektklasse vorhanden ist
		LONG lIdent = m_pThis -> GetDestClass();

			if (FAILED(EnsureObjClass (m_strOKS.c_str(), m_strKText.c_str(), m_strLText.c_str(), &lIdent)))
				return;		// irgend ein blöder Fehler
			TX_ASSERT(0 != lIdent && (lIdent == m_pThis -> GetDestClass() || 0 == m_pThis -> GetDestClass()));

		ADDOBJECTTOCLASS AOTC;
		INT_PTR hObjMapped = NULL;

			INITSTRUCT(AOTC, ADDOBJECTTOCLASS);
			AOTC.lONr = lONr;
			AOTC.lIdent = lIdent;
			AOTC.iMode = OTypToBits ((ObjTyp)DEX_GetObjectType(lONr));
			if (m_pThis -> GetAddToView())
				AOTC.iMode |= MODIDENT_ADDTOVIEW;
			AOTC.plNewONr = &hObjMapped;
			AOTC.fUndoRedo = m_pThis -> IsUndoEnabled();

			if (DEX_AddObjectToClass (AOTC) && NULL != hObjMapped)
				m_rOutIter++ = hObjMapped;		// object is added to the output collections
		}

	private:
		CAddAsObjectClass *m_pThis;
		OutEnumLONG &m_rOutIter;
		os_string m_strKText, m_strLText, m_strOKS;
	};

} // namespace

STDMETHODIMP CAddAsObjectClass::EndAction (DWORD, IDataObject **ppDataObj)
{
	COM_TRY {
	// ProgressIndikator initialisieren
		SetMaxTicks (m_Objects.Count());

	// letzte Einstellungen hier speichern
		m_lIdent = m_pCfgDlg -> GetSelectedIdent();
		m_fAddToView = m_pCfgDlg -> GetAddToView();

	// Undo initialisieren
	ResourceFile RF (g_pDLLName);
	ResString resUndo (ResID (IDS_ADDASOBJECTCLASS_UNDO, &RF), 128);

		BeginUndoLevel (resUndo);

	// eigentliche Verarbeitung
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);				// Ausgabeobjektmenge

		{
		OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));

			for_each(InEnumLONG(&m_Objects), InEnumLONG(), CAddAsObjectClassWorker(iter_out, this));
		} // iter_out goes out of scope

	// Ausgabeobjektmenge in Transfer-Objekt setzen
	__Interface<IDataObject> DO (CLSID_DataTransferObject);

		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));
		*ppDataObj = DO.detach();

		DELETE_OBJ (m_pCfgDlg);		// DialogPage freigeben

		EndUndoLevel();

	} COM_CATCH_OP_NOASSERT_ON(CancelUndoLevel(false), E_ABORT);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CAddAsObjectClass::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CAddAsObjectClass::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));

LONG lIdent = 0L;
LONG lAddToView = 0L;

	RETURN_FAILED_HRESULT(LoadLong(pStm, lIdent));
	RETURN_FAILED_HRESULT(LoadLong(pStm, lAddToView));

	if (NULL == m_pCfgDlg) {
	// Dialog ist noch nicht initialisiert
		m_lIdent = lIdent;
		m_fAddToView = lAddToView ? true : false;
		m_fHasInitData = true;
	} 
	else {
		m_pCfgDlg -> SelectIdent (lIdent);
		m_pCfgDlg -> SetAddToView (lAddToView ? true : false);
	}
	
	SetInitialized();
	return S_OK;
}

STDMETHODIMP CAddAsObjectClass::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));
	RETURN_FAILED_HRESULT(SaveLong(pStm, m_lIdent));
	RETURN_FAILED_HRESULT(SaveLong(pStm, m_fAddToView ? TRUE : FALSE));
	return S_OK;
}

STDMETHODIMP CAddAsObjectClass::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));
	pcbSize  -> QuadPart += 2*sizeof(LONG);
	return S_OK;
}

STDMETHODIMP CAddAsObjectClass::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

	m_lIdent = 0L;
	m_fAddToView = false;
	m_fHasInitData = false;

	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CAddAsObjectClass::AddConfigPages (
	LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
	if (puiCnt) *puiCnt = 0;		// initialisieren

	COM_TRY {
	char cbCaption[128];

		if (NULL != pcDesc)	{	// Caption ist gegeben
			_ASSERTE(strlen(pcDesc) < sizeof(cbCaption));
			strcpy (cbCaption, pcDesc);
		} else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
		DELETE_OBJ(m_pCfgDlg);		// DialogPage freigeben
		m_pCfgDlg = CAddAsObjectClassDlg::CreateInstance(this, cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

		if (!IsNoShow()) {
		// Seite hizufügen, wenn selbige angezeigt werden soll
		HPROPSHEETPAGE hPSP = this -> CreatePage(m_pCfgDlg);

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;

			if (puiCnt) *puiCnt = 1;		// wir haben eine Page hinzugefügt
		} 

	} COM_CATCH_OP((delete m_pCfgDlg, m_pCfgDlg = NULL));
	return S_OK;
}  

STDMETHODIMP CAddAsObjectClass::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;

	m_pCfgDlg -> SetFlags(dwFlags);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CAddAsObjectClass::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pBag, pLog));

	m_lIdent = 0L;
	m_fAddToView = false;

// sonstige Werte Analysieren

// AddToClass=
CComVariant vAddToClass;
HRESULT hr = pBag -> Read (CComBSTR(g_cbAddToClass), &vAddToClass, pLog);

	if (S_OK == hr && SUCCEEDED(vAddToClass.ChangeType(VT_BSTR))) {
	ULONG ulIdent = 0;

		hr = IdentFromClass (HACTPROJECT, OLE2A(V_BSTR(&vAddToClass)), &ulIdent, FALSE);
		if (S_OK == hr)
			m_lIdent = ulIdent;
	}

CComVariant vAddToView;

	hr = pBag -> Read (CComBSTR("AddToView"), &vAddToView, pLog);
	if (S_OK == hr && SUCCEEDED(vAddToView.ChangeType (VT_BOOL)))
		m_fAddToView = V_BOOL(&vAddToView) ? true : false;

	m_fHasInitData = true;
	return S_OK;
}

