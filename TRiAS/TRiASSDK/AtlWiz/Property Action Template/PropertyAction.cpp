[!if=(FileExists, "FALSE")]
// $Header: $
// Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: [!DateAndTime]
//
// @doc
// @module [!CPPName] | Implementation of the <c [!ClassName]> class

[!crlf]
#include "stdafx.h"

[!crlf]
#include "[!ProjectName].h"
#include "[!HeaderName]"
[!else]
[!AddIncludeFile(TargetFile, "stdafx.h")]
[!AddStringToSymbol(ProjectName.h, ProjectName, ".h")]
[!AddIncludeFile(TargetFile, ProjectName.h)]
[!AddIncludeFile(TargetFile, HeaderName)]
[!endif]

[!crlf]
/////////////////////////////////////////////////////////////////////////////
// [!ClassName]

// IPropertyAction 
[!crlf]
STDMETHODIMP [!ClassName]::BeginAction (IProgressIndicator *pIProgInd)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::BeginAction (pIProgInd));
	m_Objects.Clear();
	return S_OK;
}

[!crlf]
STDMETHODIMP [!ClassName]::DoAction (IDataObject *pIDataObj, DWORD dwReserved)
{
// Eingabeobjekte einfach mit zu unserer Objektmenge hinzufügen
	COM_TRY {
	WEnumLONG EnumObjs;
	OutEnumLONG iter_out_if (&m_Objects);

[!crlf]
		THROW_FAILED_HRESULT(PropActBase::GetEnumObjects (pIDataObj, __uuidof(IEnumLONG), EnumObjs.ppv()));
		copy (InEnumLONG(EnumObjs), InEnumLONG(), iter_out_if);

[!crlf]
	} COM_CATCH;
	return S_OK;
}

[!crlf]
namespace {
///////////////////////////////////////////////////////////////////////////////
// Klasse, die die Verarbeitung der einzelnen Objekte der Eingabemenge erlaubt
	class [!ClassName]Worker 
	{
	public:
		[!ClassName]Worker(OutEnumLONG &rOutIter, [!ClassName] *pThis) : 
			m_pPA(pThis), m_rOutIter(rOutIter)
		{
		}
		~[!ClassName]Worker() {}

[!crlf]
	// wird für jedes zu bearbeitende Objekt gerufen
		void operator() (LONG lONr)
		{
			_ASSERTE(NULL != m_pPA);
			m_pPA -> Tick();			// ProgressIndikator weitersetzen
			if (FAILED(m_pPA -> GoOn()))
				_com_issue_error(E_ABORT);
[!crlf]
		// TODO: Add your own precessing here
			m_rOutIter++ = lONr;		// object is added to the output collections
		}

[!crlf]
	private:
		IProgressIndicatorUsage *m_pPA;
		OutEnumLONG &m_rOutIter;
	};
} // namespace

[!crlf]
STDMETHODIMP [!ClassName]::EndAction (DWORD, IDataObject **ppDataObj)
{
	COM_TRY {
	// ProgressIndikator initialisieren
		SetMaxTicks (m_Objects.Count());

[!crlf]
	// eigentliche Verarbeitung
	WEnumLONG EnumOut (CLSID_EnumObjectsByNumber);				// Ausgabeobjektmenge

[!crlf]
		{
		OutEnumLONG iter_out (static_cast<IEnum<LONG> *>(EnumOut));

[!crlf]
			for_each(InEnumLONG(&m_Objects), InEnumLONG(), [!ClassName]Worker(iter_out, this));
		} // iter_out goes out of scope

[!crlf]
	// Ausgabeobjektmenge in Transfer-Objekt setzen
	__Interface<IDataObject> DO (CLSID_DataTransferObject);

[!crlf]
		THROW_FAILED_HRESULT(PropActBase::SetEnumObjects (EnumOut, DO));
		*ppDataObj = DO.detach();

[!crlf]
	// DialogPage freigeben
		if (NULL != m_pCfgDlg) {
			delete m_pCfgDlg;
			m_pCfgDlg = NULL;
		}

[!crlf]
	} COM_CATCH_NOASSERT_ON(E_ABORT);
	return S_OK;
}

[!crlf]
/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP [!ClassName]::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return S_OK;
}

[!if=(IPERSISTSTREAMINIT, "TRUE")]
[!crlf]
/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP [!ClassName]::Load (IStream *pStm)
{
	if (IsInitialized())
		return E_UNEXPECTED;

[!crlf]
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Load (pStm));

[!crlf]
// TODO: Load your own data from the stream
	SetInitialized();
	return S_OK;
}

[!crlf]
STDMETHODIMP [!ClassName]::Save (IStream *pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(CPropertyActionImpl::Save (pStm, fClearDirty));

[!crlf]
// TODO: Save your own data to the stream
	return S_OK;
}

[!crlf]
STDMETHODIMP [!ClassName]::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

[!crlf]
	RETURN_FAILED_HRESULT(CPropertyActionImpl::GetSizeMax (pcbSize));

[!crlf]
// TODO: Add the size of your data to pcbSize
//	pcbSize  -> QuadPart += ...;
	return S_OK;
}

[!crlf]
STDMETHODIMP [!ClassName]::InitNew()
{
	if (IsInitialized())
		return E_UNEXPECTED;

[!crlf]
// TODO: initialize your data
	SetInitialized();
	return S_OK;
}
[!endif]

[!if=(PropActHasUI, "TRUE")]
[!crlf]
///////////////////////////////////////////////////////////////////////////////
// Geokomponente hat eigenen Dialog
STDMETHODIMP [!ClassName]::AddConfigPages (
	LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	if (puiCnt) *puiCnt = 0;		// initialisieren

[!crlf]
	COM_TRY {
	char cbCaption[128];

[!crlf]
		if (NULL != pcDesc)	{	// Caption ist gegeben
			ASSERT(strlen(pcDesc) < sizeof(cbCaption));
			strcpy (cbCaption, pcDesc);
		} else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

[!crlf]
	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
		if (NULL != m_pCfgDlg) delete m_pCfgDlg;
		m_pCfgDlg = [!DlgClassName]::CreateInstance(cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

[!crlf]
		if (!IsNoShow()) {
		// Seite hizufügen, wenn selbige angezeigt werden soll
		PROPSHEETPAGE psp;

[!crlf]
			memcpy(&psp, &m_pCfgDlg->m_psp, sizeof(PROPSHEETPAGE));
		
[!crlf]
		HPROPSHEETPAGE hPSP = ::CreatePropertySheetPage (&psp);

[!crlf]
			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;

[!crlf]
			if (puiCnt) *puiCnt = 1;		// wir haben eine Page hinzugefügt
		} 
	} COM_CATCH_OP((delete m_pCfgDlg, m_pCfgDlg = NULL));
	return S_OK;
}  

[!crlf]
STDMETHODIMP [!ClassName]::PreConfigPages (IDataObject *pIDataObject, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;

[!crlf]
	m_pCfgDlg -> SetFlags(dwFlags);
	return S_OK;
}
[!endif]
