// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 14.09.2000 08:52:33
//
// @doc
// @module DeleteObjectProperty.cpp | Implementation of the <c CDeleteObjectProperty> class

#include "trias03p.hxx"
#include "trias03.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <TrCatIds.h>

#include "Strings.h"
#include "TRiASTrans.h"
#include "DataHelp.h"
#include "DeleteObjectProperty.h"

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ObjectProperty2);
DefineSmartInterface(ObjectProperty3);
DefineSmartInterface(EnumObjProps);

///////////////////////////////////////////////////////////////////////////////
//
extern char g_pDLLName[_MAX_PATH];

/////////////////////////////////////////////////////////////////////////////
// CDeleteObjectProperty
// IPropertyAction 

STDMETHODIMP CDeleteObjectProperty::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.Clear();
	return S_OK;
}

STDMETHODIMP CDeleteObjectProperty::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
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
	class CDeleteObjectPropertyWorker 
	{
	public:
		CDeleteObjectPropertyWorker(
				OutEnumLONG &rOutIter, CDeleteObjectProperty *pThis, list<WObjectProperty> &rlstProps) : 
			m_pThis(pThis), m_rOutIter(rOutIter)
		{
			for (list<WObjectProperty>::iterator it = rlstProps.begin(); it != rlstProps.end(); ++it) {
			WObjectProperty2 ObjProp2;
			WObjectProperty3 ObjProp3;

				if (FAILED((*it) -> QueryInterface(ObjProp3.ppi())))
					(*it) -> QueryInterface(ObjProp2.ppi());
				_ASSERTE(ObjProp2.IsValid() || ObjProp3.IsValid());

				if (ObjProp3.IsValid())
					m_lstProps3.push_back(ObjProp3);
				else
					m_lstProps2.push_back(ObjProp2);
			}
		}
		~CDeleteObjectPropertyWorker() {}

	// wird für jedes zu bearbeitende Objekt gerufen
		void operator() (LONG lONr)
		{
			_ASSERTE(NULL != m_pThis);
			m_pThis -> Tick();			// ProgressIndikator weitersetzen
			if (FAILED(m_pThis -> GoOn()))
				_com_issue_error(E_ABORT);

		// alle Objekteigenschaften durchgehen und löschen
			for (list<WObjectProperty2>::iterator it2 = m_lstProps2.begin(); it2 != m_lstProps2.end(); ++it2)
				(*it2) -> Set (lONr, NULL);

			for (list<WObjectProperty3>::iterator it3 = m_lstProps3.begin(); it3 != m_lstProps3.end(); ++it3)
				(*it3) -> SetWithUndo (lONr, NULL);

			m_rOutIter++ = lONr;		// object is added to the output collections
		}

	private:
		CDeleteObjectProperty *m_pThis;
		OutEnumLONG &m_rOutIter;
		list<WObjectProperty2> m_lstProps2;
		list<WObjectProperty3> m_lstProps3;
	};
} // namespace

STDMETHODIMP CDeleteObjectProperty::EndAction (DWORD, IDataObject **ppDataObj)
{
	COM_TRY {
	// Undo/Redo level aufmachen
	ResourceFile RF (g_pDLLName);
	ResString resUndo (ResID(IDS_UNDO_DELETEPROPERTY, &RF), 64);
	TRiASTransaktion UndoLevel(resUndo);

	// ProgressIndikator initialisieren
		SetMaxTicks (m_Objects.Count());

	// zu löschende Objekteigenschaften aus Dialog abholen
		m_lstProps = m_pCfgDlg -> GetSelectedObjProps();

	// zu löschende Objekteigenschaften besorgen
	list<WObjectProperty> lstProps;

		RETURN_FAILED_HRESULT(GetPropList (lstProps));

	// eigentliche Verarbeitung
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);				// Ausgabeobjektmenge

		{
		OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));

			for_each(InEnumLONG(&m_Objects), InEnumLONG(), CDeleteObjectPropertyWorker(iter_out, this, lstProps));
		} // iter_out goes out of scope

	// Ausgabeobjektmenge in Transfer-Objekt setzen
	__Interface<IDataObject> DO (CLSID_DataTransferObject);

		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));
		*ppDataObj = DO.detach();

	// DialogPage freigeben
		if (NULL != m_pCfgDlg) {
			delete m_pCfgDlg;
			m_pCfgDlg = NULL;
		}

	// Transaktion ist nun gültig
		UndoLevel.End();

	} COM_CATCH_NOASSERT_ON(E_ABORT);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CDeleteObjectProperty::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CDeleteObjectProperty::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));

list<os_string>::difference_type ulCnt = 0;

	RETURN_FAILED_HRESULT(LoadData(pStm, ulCnt));
	for (list<os_string>::difference_type ul = 0; ul < ulCnt; ++ul) 
	{
	os_string str;

		RETURN_FAILED_HRESULT(LoadString(pStm, str));
		m_lstProps.push_back(str);
	}

	SetInitialized();
	return S_OK;
}

STDMETHODIMP CDeleteObjectProperty::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));

list<os_string>::difference_type ulCnt = m_lstProps.size();

	RETURN_FAILED_HRESULT(SaveData(pStm, ulCnt));
	for (list<os_string>::iterator it = m_lstProps.begin(); it != m_lstProps.end(); ++it) 
	{
		RETURN_FAILED_HRESULT(SaveString(pStm, *it));
	}
	return S_OK;
}

STDMETHODIMP CDeleteObjectProperty::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));

	pcbSize -> QuadPart += sizeof(list<os_string>::difference_type);
	for (list<os_string>::iterator it = m_lstProps.begin(); it != m_lstProps.end(); ++it) 
	{
		pcbSize -> QuadPart += ::GetSizeMax(*it);
	}
	return S_OK;
}

STDMETHODIMP CDeleteObjectProperty::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

	m_lstProps.clear();
	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CDeleteObjectProperty::AddConfigPages (
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
	ResourceFile RF (g_pDLLName);

		if (NULL != m_pCfgDlg) delete m_pCfgDlg;
		m_pCfgDlg = CDeleteObjectPropertyDlg::CreateInstance(ResID(CDeleteObjectPropertyDlg::IDD, &RF), cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

		if (!IsNoShow()) {
		// Seite hizufügen, wenn selbige angezeigt werden soll
		HPROPSHEETPAGE hPSP = this -> CreatePage(m_pCfgDlg);

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;

			if (puiCnt) *puiCnt = 1;		// wir haben eine Page hinzugefügt
		} 
		m_pCfgDlg -> SetInitialObjProps(m_lstProps);
		
	} COM_CATCH_OP((delete m_pCfgDlg, m_pCfgDlg = NULL));
	return S_OK;
}  

STDMETHODIMP CDeleteObjectProperty::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;

	m_pCfgDlg -> SetFlags(dwFlags);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// die Liste aller auszugebenden Objekteigenschaften bilden
HRESULT CDeleteObjectProperty::GetPropList(list<WObjectProperty> &rLstProps)
{
	COM_TRY {
	WObjectProps Props (m_pCfgDlg -> GetObjectProps());
	WEnumObjProps Enum;

		THROW_FAILED_HRESULT(Props -> EnumObjectProps(Enum.ppi()));

	// jetzt alle selektieretne Namen durchgehen und Objekteigenschaften besorgen
		for (list<os_string>::iterator it = m_lstProps.begin(); it != m_lstProps.end(); ++it) {
		WObjectProperty ObjProp;

			if (SUCCEEDED(Enum -> FindByName((*it).c_str(), ObjProp.ppi())))
			{
				rLstProps.push_back (ObjProp);
			}
		}
	} COM_CATCH;
	return S_OK;
}

