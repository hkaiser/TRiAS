// $Header: $
// Copyright© 1999 Fernerkundungszentrum Potsdam GmbH, All rights reserved
//
// @doc
// @module SelectExportObjects.cpp | Implementation of the <c CSelectExportObjects> class

#include "trias03p.hxx"
#include "trias03.h"

#include <funcs03.h>
#include <xtsnguid.h>
#include <eonrguid.h>
#include <bscrguid.h>
#include <statguid.h>
#include <SelectExportObjectsGuid.h>

#include <Com/Thunk.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "SelectExportObjects.h"

#include <Com/PropertyActionBase.cpp>	// include only once

extern char g_pDLLName[_MAX_PATH];		// dieser Modul

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ClassProperty);

///////////////////////////////////////////////////////////////////////////////
// CSelectExportObjects
// IPropertyAction 

STDMETHODIMP CSelectExportObjects::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.Clear();
	return m_pCfgDlg -> GetDataSources (m_setDataSources);
}

class CObjectToCopy :
	unary_function<LONG, bool>
{
public:
	CObjectToCopy(CDataSources &rDS) : m_rDS(rDS) {}
	~CObjectToCopy() {}

	bool operator() (LONG lONr) 
	{
		return m_rDS.find(DEX_GetObjectProject(lONr)) == m_rDS.end();
	}

private:
	CDataSources &m_rDS;
};

STDMETHODIMP CSelectExportObjects::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{
// Eingabeobjekte einfach mit zu unserer Objektmenge hinzufügen
	if (NULL != pIDataObj) {
	// evtl. keine Eingabeobjektmenge gegeben

		COM_TRY {
		// aber nur Objekte der geforderten Datenquellen übernehmen
		WEnumLONG EnumObjs;
		OutEnumLONG iter_out (&m_Objects);

			if (S_OK == GetEnumLONGData (pIDataObj, __uuidof(IEnumLONG), EnumObjs.ppv()))
			{
				remove_copy_if (InEnumLONG(EnumObjs), InEnumLONG(), iter_out, 
					CObjectToCopy(m_setDataSources));
			}

		} COM_CATCH;
	}
	return S_OK;
}

namespace {
///////////////////////////////////////////////////////////////////////////////
// Klasse, die die Verarbeitung der einzelnen Objekte der Eingabemenge erlaubt
	class CSelectExportObjectsWorker 
	{
	public:
		typedef void (__stdcall CSelectExportObjectsWorker::*TMFP)();

		CSelectExportObjectsWorker(OutEnumLONG &rOutIter, CSelectExportObjects *pThis) : 
			m_pPA(pThis), m_rOutIter(rOutIter)
		{
			m_EnumIdents.InitThunk(reinterpret_cast<TMFP>(EnumIdentsCB), this);
			m_EnumObjects.InitThunk(reinterpret_cast<TMFP>(EnumObjectsCB), this);
		}
		~CSelectExportObjectsWorker() {}

	// wird für jedes zu bearbeitende Objekt gerufen
		void operator() (LONG lONr)
		{
			_ASSERTE(NULL != m_pPA);
			m_pPA -> Tick();			// ProgressIndikator weitersetzen
			if (FAILED(m_pPA -> GoOn()))
				_com_issue_error(E_ABORT);
			m_rOutIter++ = lONr;		// object is added to the output collections
		}

		// callback für Enumeration aller Objektklassen
		BOOL CALLBACK EnumIdentsCB (INT_PTR lIdent, BOOL, void *pData)
		{
			_ASSERTE(NULL != m_pPA);
			m_pPA -> Tick();			// ProgressIndikator weitersetzen
			if (FAILED(m_pPA -> GoOn()))
				_com_issue_error(E_ABORT);

		CDataSources *pDS = reinterpret_cast<CDataSources *>(pData);

			if (pDS -> find (DEX_GetObjectsProject(lIdent)) == pDS -> end())
				return TRUE;		// diese Objektklasse nicht behandeln

		ENUMLONGKEY ELK;

			ELK.eKey = lIdent;
			ELK.eFcn = GetEnumObjectsThunk();
			ELK.ePtr = NULL;
			return DEX_EnumIdentObjects (ELK);
		}

	// Callback für Enumeration aller Objekte einer Objektklasse
		BOOL CALLBACK EnumObjectsCB (INT_PTR lONr, BOOL, void *pData)
		{
			m_rOutIter++ = lONr;		// object is added to the output collections
			return TRUE;		// immer weiter enumerieren
		}

		ENUMNOKEYLONGPROC GetEnumIdentsThunk() 
			{ return reinterpret_cast<ENUMNOKEYLONGPROC>(m_EnumIdents.GetThunk()); }
		ENUMLONGKEYPROC GetEnumObjectsThunk()
			{ return reinterpret_cast<ENUMLONGKEYPROC>(m_EnumObjects.GetThunk()); }

	private:
		IProgressIndicatorUsage *m_pPA;
		OutEnumLONG &m_rOutIter;

		CStdThunk<CSelectExportObjectsWorker> m_EnumIdents;
		CStdThunk<CSelectExportObjectsWorker> m_EnumObjects;
	};
} // namespace

STDMETHODIMP CSelectExportObjects::EndAction (DWORD, IDataObject **ppDataObj)
{
	COM_TRY {
	// eigentliche Verarbeitung
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);				// Ausgabeobjektmenge
	OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));
	CSelectExportObjectsWorker Worker (iter_out, this);

		if (0 == m_Objects.Count()) { 
		// Objekte der gegebenen Datenquellen zusammensuchen
			TX_ASSERT(m_setDataSources.size() > 0);
			SetMaxTicks (m_setDataSources.size());	// ProgressIndikator initialisieren (Anzahl der Datenquellen)

		ENUMNOKEYLONG ENK;

			ENK.eFcn = Worker.GetEnumIdentsThunk();
			ENK.ePtr = &m_setDataSources;
			DEX_EnumIdents (ENK);

		} else {
		// in Ausgabeobjektmenge übernehmen
			SetMaxTicks (m_Objects.Count());		// ProgressIndikator initialisieren (Anzahl der Objekte)
			for_each(InEnumLONG(&m_Objects), InEnumLONG(), Worker);
		}

	// Ausgabeobjektmenge in Transfer-Objekt setzen
	__Interface<IDataObject> DO (CLSID_DataTransferObject);

		THROW_FAILED_HRESULT(SetEnumLONGData (EnumOut, DO));
		*ppDataObj = DO.detach();

		DELETE_OBJ (m_pCfgDlg);		// DialogPage freigeben

	} COM_CATCH_NOASSERT_ON(E_ABORT);
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CSelectExportObjects::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CSelectExportObjects::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));

// TODO: Load your own data from the stream
	SetInitialized();
	return S_OK;
}

STDMETHODIMP CSelectExportObjects::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));

// TODO: Save your own data to the stream
	return S_OK;
}

STDMETHODIMP CSelectExportObjects::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));

// TODO: Add the size of your data to pcbSize
//	pcbSize  -> QuadPart += ...;
	return S_OK;
}

STDMETHODIMP CSelectExportObjects::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

// TODO: initialize your data
	SetInitialized();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP CSelectExportObjects::AddConfigPages (
	LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
	if (puiCnt) *puiCnt = 0;		// initialisieren

	COM_TRY {
	char cbCaption[128];

		if (NULL != pcDesc)	{	// Caption ist gegeben
			TX_ASSERT(strlen(pcDesc) < sizeof(cbCaption));
			strcpy (cbCaption, pcDesc);
		} else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// Kontext des Dialoges feststellen
	WClassProperty Cls;
	bool fChoice = false;

		if (SUCCEEDED(GetSite (IID_IClassProperty, Cls.ppv()))) {
		// Kontext ist entweder PropertyChoice oder PropertySequence 
		DWORD dwFlags = 0;

			if (SUCCEEDED(Cls -> GetPropInfo (NULL, 0, &dwFlags)))
				fChoice = (dwFlags & PROPCAPS_CONTAINER_IS_CHOICE) ? true : false;
		}

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
	ResourceFile RF (g_pDLLName);
	ResID resDlg (fChoice ? CSelectExportObjectsDlg::IDD_PP : CSelectExportObjectsDlg::IDD, &RF);

		DELETE_OBJ(m_pCfgDlg);
		m_pCfgDlg = CSelectExportObjectsDlg::CreateInstance(resDlg, cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

		if (!IsNoShow()) {
		// Seite hizufügen, wenn selbige angezeigt werden soll
		HPROPSHEETPAGE hPSP = this -> CreatePage(m_pCfgDlg);

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_UNEXPECTED;

			if (puiCnt) *puiCnt = 1;		// wir haben eine Page hinzugefügt
		} 
	} COM_CATCH_OP((delete m_pCfgDlg, m_pCfgDlg = NULL));
	return S_OK;
}  

STDMETHODIMP CSelectExportObjects::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;

	m_pCfgDlg -> SetFlags(dwFlags);
	return S_OK;
}
