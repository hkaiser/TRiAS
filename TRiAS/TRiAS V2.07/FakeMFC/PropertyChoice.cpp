// PropertyChoice.cpp : implementation file
//

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include <int64.h>
#include <xtsnguid.h>
#include <eonrguid.h>
#include <statguid.h>

#include "strings.h"
#include "PropertyChoice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// benötigte InterfaceWrapper
DefineSmartInterface(DataObject);
DefineEnumIIDWrapper(LONG);		// CIID_LONGEnum
DefineSmartEnumerator(LONG);	// WEnumLONG

DefineSmartInterface(Storage);
DefineSmartInterface(Stream);
DefineSmartInterface(PersistStream);
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(ClassProperty);

#if !defined(_COMERRORMACROS_H__48172D62_AB72_11D1_858D_00600875138A__INCLUDED_)
///////////////////////////////////////////////////////////////////////////////
// lokal verwendete Funktionen 
inline bool IMPL_AND_FAILED (HRESULT hr)
{
	return (FAILED(hr) && !(E_NOTIMPL == GetScode(hr)));
}
#endif // _COMERRORMACROS_H__48172D62_AB72_11D1_858D_00600875138A__INCLUDED_

/////////////////////////////////////////////////////////////////////////////
// CPropertyChoiceDlg property page

IMPLEMENT_DYNCREATE(CPropertyChoiceDlg, CPropertyPage)

CPropertyChoiceDlg *CPropertyChoiceDlg::CreateInstance (
		CPropertyChoice *pBack, LPCTSTR pcCaption)
{
CPropertyChoiceDlg *pDlg = NULL;

	TRY {
		pDlg = new CPropertyChoiceDlg();
		if (NULL == pDlg || !pDlg -> FInit (pBack, pcCaption))
			return NULL;

	} CATCH (CMemoryException, e) {
		return NULL;
	} END_CATCH

return pDlg;
}

bool CPropertyChoiceDlg::FInit (
		CPropertyChoice *pBack, LPCTSTR pcCaption)
{
	ASSERT(NULL == m_pBack);	// nur einmal initialisieren
	m_pBack = pBack;

	try {
		m_strTitle = pcCaption;

	// Caption nachrüsten, da MFC nur ResID für caption unterstützt
		m_strCaption = pcCaption;
		m_psp.pszTitle = m_strCaption;
		m_psp.dwFlags |= PSP_USETITLE;

	} catch (...) {
		return false;
	}

return true;
}

CPropertyChoiceDlg::CPropertyChoiceDlg() : CPropertyPage(CPropertyChoiceDlg::IDD)
{
	//{{AFX_DATA_INIT(CPropertyChoiceDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_dwSheetBttns = 0L;
	m_pBack = NULL;
	m_pSheet = NULL;
	m_fFirstActivation = true;
}

CPropertyChoiceDlg::~CPropertyChoiceDlg()
{
	DELETE(m_pSheet);
}

void CPropertyChoiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyChoiceDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPropertyChoiceDlg, CPropertyPage)
	//{{AFX_MSG_MAP(CPropertyChoiceDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyChoiceDlg message handlers

BOOL CPropertyChoiceDlg::OnSetActive() 
{
BOOL fResult = CPropertyPage::OnSetActive();

// beim ersten aktivate kriegt die aktive Page die PSN_ACTIVATE sowieso
// deshalb nur alle weiteren weiterleiten
	if (!m_fFirstActivation) {
		if (NULL != m_pSheet) 
			m_pSheet -> OnSetActive();		// an alle Childs weiterleiten
	}

	InitSheet();
	m_fFirstActivation = false;
	return fResult;
}

BOOL CPropertyChoiceDlg::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
// nichtmodalen CPropertySheet erzeugen
	TRY {
	CRect rcClient;

		GetClientRect(&rcClient);
		m_pSheet = new CChoiceParent (rcClient, m_strDesc.c_str()); 
		if (!m_pSheet -> Create(this, WS_VISIBLE|WS_CHILD|DS_CONTROL, 0))
			AfxThrowMemoryException();

	// geforderte Pages einhängen
		for (CPageList::iterator it = m_Pages.begin(); 
			 it != m_Pages.end(); it++) 
		{
			m_pSheet -> SendMessage (PSM_ADDPAGE, 0, LPARAM(HPROPSHEETPAGE(*it)));
		}

		m_pSheet -> CleanUp();		// DummyPage wieder entfernen

	} CATCH(CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CPropertyChoiceDlg::OnWizardBack() 
{
	if (NULL != m_pSheet)
		return m_pSheet -> OnWizardBack(); 
	return CPropertyPage::OnWizardBack();
}

BOOL CPropertyChoiceDlg::OnWizardFinish() 
{
	EvalActPropAction();

	if (NULL != m_pSheet)
		return m_pSheet -> OnWizardFinish(); 
	return CPropertyPage::OnWizardFinish();
}

LRESULT CPropertyChoiceDlg::OnWizardNext() 
{
	EvalActPropAction();

	if (NULL != m_pSheet)
		return m_pSheet -> OnWizardNext(); 
	return CPropertyPage::OnWizardNext();
}

void CPropertyChoiceDlg::OnCancel() 
{
	if (NULL != m_pSheet)
		m_pSheet -> OnCancel(); 
	else
		CPropertyPage::OnCancel();
}

BOOL CPropertyChoiceDlg::OnQueryCancel() 
{
	if (NULL != m_pSheet)
		return m_pSheet -> OnQueryCancel(); 
	return CPropertyPage::OnQueryCancel();
}

LRESULT CPropertyChoiceDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
// normalerweise kriegt eine PropertyPage diese Messages nicht
// hier müssen sie aber nach oben weitergeleitet werden 
// (an den eigentlichen PropertySheet)
	switch(message) {
	case PSM_CANCELTOCLOSE:
	case PSM_PRESSBUTTON:
	case PSM_SETFINISHTEXT:
	case PSM_SETWIZBUTTONS:
	case PSM_SETTITLE:
		GetParent()->SendMessage(message, wParam, lParam);
		break;

	default:
		break;
	}

	return CPropertyPage::WindowProc(message, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// sonstige Member
HRESULT CPropertyChoiceDlg::InitSheet (void)
{
	return NOERROR;
}

// Feststellen, welche Seite derzeit aktiv ist und welches Objekt dazugehört
HRESULT CPropertyChoiceDlg::EvalActPropAction (void)
{
	ASSERT(NULL != m_pSheet);

// derzeit aktive Page
int iActIndex = m_pSheet->GetActiveIndex();

	m_ActAction.Assign(NULL);		// vorhergehende freigeben
	for (CActionList::iterator it = m_pBack -> GetActions().begin(); 
		 it != m_pBack -> GetActions().end(); it++) 
	{
		if (iActIndex >= (*it).FirstPage() && iActIndex <= (*it).LastPage()) {
			m_ActAction = (*it).Action();
			return S_OK;
		}
	}

	return E_FAIL;
}

/////////////////////////////////////////////////////////////////////////////
// Funktionen, die eigentliche PropertyAction ausführen
// Callback-Funktion, die von den IPropertyActions gerufen wird, um ihre
// PropertyPages in unseren Dialog reinzuhängen
bool __stdcall AddConfigPropertyPage (HPROPSHEETPAGE hPage, LPARAM lParam)
{
	try {
	// Page in Liste einhängen
		((CPageList *)lParam) -> push_back(CHPropSheetPage(hPage));

	} catch (...) {
		return false;
	}

return true;
}

HRESULT CPropertyChoiceDlg::AddConfigPages (LPCSTR pcDesc, UINT *puiCnt)
{
// Description merken
	m_strDesc = pcDesc ? pcDesc : m_strTitle;
	m_Pages.erase(m_Pages.begin(), m_Pages.end());

// 2. alle benötigten Pages reinhängen, dazu alle SubProperties befragen
UINT uiCntA = 0;

	for (CActionList::iterator it = m_pBack -> GetActions().begin(); 
		 it != m_pBack -> GetActions().end(); it++) 
	{
	UINT uiCnt = 0;

		(*it).SetFirstPage(uiCntA);		// erste zugehörige Page merken
		
		(*it).Action() -> AddConfigPages (AddConfigPropertyPage, (LPARAM)&m_Pages, NULL, &uiCnt);
		uiCntA += uiCnt;	// bei Fehler, ist uiCnt = 0
		
		(*it).SetLastPage(uiCntA-1);	// letzte zugehörige Page merken
	}
	
	ASSERT(uiCntA == m_Pages.size());	// Anzahl der Seiten gleich Anzahl der ListenElemente

	if (puiCnt) 
		*puiCnt = uiCntA;

return S_OK;
}

HRESULT CPropertyChoiceDlg::PreConfigPages (IDataObject *pIDO, DWORD dwSheetBttns)
{
	m_dwSheetBttns = dwSheetBttns;
	for (CActionList::iterator it = m_pBack -> GetActions().begin(); 
		 it != m_pBack -> GetActions().end(); it++) 
	{
	HRESULT hr = (*it).Action() -> PreConfigPages (pIDO, dwSheetBttns);

		if (IMPL_AND_FAILED(hr)) return hr;
	}

return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Die eigentlichen AktionsFunktionen an die zuletzt aktive Page/Objekt 
// weiterleiten
HRESULT CPropertyChoiceDlg::BeginAction (IProgressIndicator *pIPI)
{
	if (NULL != (IUnknown *)m_ActAction)
		return m_ActAction -> BeginAction(pIPI);
	return E_UNEXPECTED;
}

HRESULT CPropertyChoiceDlg::DoAction (IDataObject *pIDO, DWORD dwReserved)
{
	if (NULL != (IUnknown *)m_ActAction)
		return m_ActAction -> DoAction(pIDO, dwReserved);
	return E_UNEXPECTED;
}

HRESULT CPropertyChoiceDlg::EndAction (DWORD dwReserved, IDataObject **ppIDO)
{
	if (NULL != (IUnknown *)m_ActAction)
		return m_ActAction -> EndAction (dwReserved, ppIDO);
	return E_UNEXPECTED;
}

///////////////////////////////////////////////////////////////////////////////
// Globale Funktionen, welche Initiierung et.al. übernehmen

// Konvertieren eines PropAct-Bezeichners in einen Stream-Namen
static string MakeStreamName (LPCSTR pcDesc)
{
string str (pcDesc, 31);

	for (int i = 0; i < 31; i++) {
	char c = pcDesc[i];

		switch (c) {
		case '.':
		case '\\':
		case '/':
		case ':':
		case '!':
			str[i] = '_';
			break;

		case '\0':		// Ende des Strings
			return str;

		default:
			if (pcDesc[i] > ' ')
				str[i] = c;
			else
				str[i] = '_';
			break;
		}
	}

return str;
}

// Öffnen des PropertySequenceSubStorages
static HRESULT GetSubPropSeqStorage (IStorage **ppIStg)
{
	if (NULL == ppIStg) return E_POINTER;

WStorage IRootStg;

	if (!DEX_GetProjectStorage(*IRootStg.ppv()))
		return E_FAIL;

	USES_CONVERSION;

WStorage IStg;
HRESULT hr = IRootStg -> OpenStorage (A2OLE(g_cbPropertyChoices), NULL, 
					STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
					NULL, 0L, IStg.ppi());
	
	if (FAILED(hr)) {
	// mit Schreibschutz versuchen
		hr = IRootStg -> OpenStorage (A2OLE(g_cbPropertyChoices), NULL, 
						STGM_READ|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
						NULL, 0L, IStg.ppi());
		if (FAILED(hr)) return hr;
	}

CLSID clsId;

	hr = ReadClassStg (IStg, &clsId);
	if (FAILED(hr)) return hr;

	if (!IsEqualCLSID (clsId, CLSID_PropertyChoice))
		return E_FAIL;

	*ppIStg = IStg.detach();

return hr;
}

static HRESULT SavePropSeq (
	LPCSTR pcDesc, IPropertyActionSequence *pISeq, IStorage *pIStg)
{
HRESULT hr = E_FAIL;
WStorage IStg (pIStg);

	USES_CONVERSION;
	if (NULL == pIStg) {	// SubStorage anlegen, da es noch nicht existiert
	WStorage IRootStg;

		if (!DEX_GetProjectStorage(*IRootStg.ppv()))
			return E_FAIL;

		hr = IRootStg -> CreateStorage (A2OLE(g_cbPropertyChoices), 
						STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
						0L, 0L, IStg.ppi());
		if (FAILED(hr)) return hr;

		hr = WriteClassStg (IStg, CLSID_PropertyChoice);
		if (FAILED(hr)) return hr;
	}

	try {
	WStream IStm;
	WPersistStream IPersistStm (pISeq);		// throws hr
	string strName = MakeStreamName(pcDesc);

	// Stream erzeugen
		hr = IStg -> CreateStream (A2OLE(strName.c_str()), 
						STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE, 
						0L, 0L, IStm.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

		hr = OleSaveToStream (IPersistStm, IStm);	// und wegschreiben
		if (FAILED(hr)) _com_issue_error(hr);

		hr = IStm -> Commit (STGC_DEFAULT);
		if (FAILED(hr)) _com_issue_error(hr);

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	hr = IStg -> Commit (STGC_DEFAULT);
	if (SUCCEEDED(hr))
		DEX_SetDirtyGeoDB(true);

return hr;
}

// Erzeugen und initialisieren eines PropertyActionChoice-Objektes, welches die
// vorgegebenen PropertyActions enthält
HRESULT InitPropertyActionChoice (
	LPCSTR pcDesc, CALPCLSID *pcaClsIds, IPropertyActionSequence **ppISeq)
{
	USES_CONVERSION;

	if (NULL == ppISeq) return E_POINTER;
	*ppISeq = NULL;		// für alle Fälle

WPropertyActionSequence ISeq;
HRESULT hr = E_FAIL;
WStorage IStg;

	GetSubPropSeqStorage (IStg.ppi());
	if (NULL != (IStorage *)IStg) {	// evtl. gespeicherten Status laden
	WStream IStm;
	string strName = MakeStreamName(pcDesc);

	// Stream erzeugen
		hr = IStg -> OpenStream (A2OLE(strName.c_str()), NULL, 
						STGM_READ|STGM_SHARE_EXCLUSIVE, 0L, IStm.ppi());

		if (SUCCEEDED(hr)) {
			hr = OleLoadFromStream (IStm, IID_IPropertyActionSequence, ISeq.ppv());
			if (SUCCEEDED(hr)) {
				*ppISeq = ISeq.detach();
				return S_OK;
			}
		}
	}
	
// wenn Status nicht geladen werden kann, dann neu initialisieren
	try {
	// Objekt erzeugen
		ISeq = WPropertyActionSequence (CLSID_PropertyChoice);		// throws hr
		ISeq -> SetDescription (pcDesc);

	// Rücksetzen der AktionsFolge
	WPersistStreamInit Init = ISeq;		// throws hr

		hr = Init -> InitNew();
		if (FAILED(hr)) _com_issue_error(hr);
	
	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

// hinzufügen der einzelnen Aktionen
	hr = ISeq -> AddActionsByCLSID (pcaClsIds);
	if (FAILED(hr)) return hr;

	*ppISeq = ISeq.detach();

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// PropertyAction, welche sämtliche RechercheOptionen abfragt

///////////////////////////////////////////////////////////////////////////////
// Min-Funktion, da Macro aus stdlib offensichtlich überladen ist
template<class T>
inline T tmin (T a, T b) { return (a > b) ? b : a; }

// CLSPROP_ROOT\\TRiAS® (allgemein)\\Auswahl aus mehreren Property-Aktionen
// 0796388A-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(CLSID_PropertyChoice, 0x0796388AL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
CPropertyChoice :: CPropertyChoice (void)
{
	m_pCfgDlg = NULL;
	m_fIsDirty = false;
	m_fIsInitialized = false;

	TRY {
	CString strPropInfo; strPropInfo.LoadString (IDS_SEARCHENGINECHOICE_DESC);

		m_strDesc = strPropInfo;
	} CATCH (CMemoryException, e) {
		ASSERT(false);
	} END_CATCH
}

CPropertyChoice::~CPropertyChoice (void)
{
	DELETE(m_pCfgDlg);
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyActionSequence methods
STDMETHODIMP CPropertyChoice::AddAction (IPropertyAction *pIAct)
{
	if (!m_fIsInitialized) {
	HRESULT hr = InitNew();

		if (FAILED(hr)) return hr;
	}

	try {
		m_Actions.push_back (CAction(pIAct));
		m_fIsDirty = true;

	} catch (...) {
		ASSERT(false);
		return E_FAIL;
	}

return NOERROR;
}

STDMETHODIMP CPropertyChoice::AddActionsByCLSID (CALPCLSID *pcaClsIds)
{
HRESULT hr = E_FAIL;

	if (!m_fIsInitialized) {
		hr = InitNew();
		if (FAILED(hr)) return hr;
	}

// hinzufügen der einzelnen Aktionen
	for (ULONG i = 0; i < pcaClsIds -> cElems; i++) {
		try {
		WPropertyAction WAct (*(pcaClsIds -> ppElems[i]));	// throws hr

			{
			WPersistStreamInit Init = WAct;			// throws hr

				hr = Init -> InitNew();
				if (FAILED(hr)) _com_issue_error(hr);
			}		
			hr = AddAction (WAct);
			if (FAILED(hr)) _com_issue_error(hr);

		} catch (_com_error& hr) {
			return _COM_ERROR(hr);
		}
	}

	return NOERROR;
}

// DoActions wird für PropertyChoice nicht benötigt
STDMETHODIMP CPropertyChoice::DoActions (HWND hParent, IProgressIndicator *pIStatus,
			       IDataObject *pIData, IDataObject **ppOutData)
{
	ATLTRACENOTIMPL("CPropertyChoice::DoActions");
}

// RedoActions wird für PropertyChoice nicht benötigt
STDMETHODIMP CPropertyChoice::RedoActions (HWND hParent, IProgressIndicator *pIStatus,
			       IDataObject *pIData, IDataObject **ppOutData)
{
	ATLTRACENOTIMPL("CPropertyChoice::RedoActions");
}

STDMETHODIMP CPropertyChoice::SetDescription (LPCSTR pcDesc)
{
	if (NULL == pcDesc) return E_POINTER;
	
	m_strDesc = pcDesc;
	return NOERROR;
}

STDMETHODIMP CPropertyChoice::GetDescription (LPSTR pDesc, ULONG ulLen, ULONG *pulWritten)
{
	if (NULL == pDesc) return E_POINTER;
	if (0 == ulLen) return E_INVALIDARG;

	if (!m_fIsInitialized) {
	HRESULT hr = InitNew();

		if (FAILED(hr)) return hr;
	}

ULONG ulL = tmin((ULONG)m_strDesc.length(), ulLen-1);
	
	strncpy (pDesc, m_strDesc.c_str(), ulL);
	pDesc[ulL] = '\0';

	if (pulWritten)
		*pulWritten = ulL;

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions 
STDMETHODIMP CPropertyChoice::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
		ULONG ulLen = tmin ((size_t)(wLen-1), m_strDesc.length());

			strncpy (pBuffer, m_strDesc.c_str(), ulLen);
			pBuffer[ulLen] = '\0';
		}

	// wenn gewünscht, Flags aufsammeln und übergeben
		if (pdwFlags) {
		DWORD dwFlags = 0;

			for (CActionList::iterator it = m_Actions.begin(); 
				 it != m_Actions.end(); it++) 
			{
			WClassProperty IProp = (*it).Action();	// throws hr
			DWORD dw = 0;

				if (SUCCEEDED(IProp -> GetPropInfo (NULL, 0, &dw)))
					dwFlags |= dw;
			}

			*pdwFlags = dwFlags;
		}

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	} catch (...) {
		return E_FAIL;
	}

return NOERROR;
}

STDMETHODIMP CPropertyChoice::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	TRY {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung übergeben
		CString strHelp; strHelp.LoadString (IDS_SEARCHENGINECHOICE_HELPINFO);
		ULONG ulLen = tmin ((size_t)(wLen-1), (size_t)strHelp.GetLength());

			strncpy (pBuffer, strHelp, ulLen);
			pBuffer[ulLen] = '\0';
		}
	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH

// HelpFileInfo übergeben
	if (pHelpFile) pHelpFile[0] = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0L;
	
return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods 
STDMETHODIMP CPropertyChoice::AddConfigPages (
				LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, 
				LPCSTR pcDesc, UINT *puiCnt)
{
char cbCaption[128];

	try {
		if (NULL != pcDesc)		// Caption ist gegeben
			strcpy (cbCaption, pcDesc);
		else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
		DELETE(m_pCfgDlg);	// evtl. vorherigen freigeben
		m_pCfgDlg = CPropertyChoiceDlg::CreateInstance (this, cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

	HPROPSHEETPAGE hPSP = NULL;
	PROPSHEETPAGE psp;
	HRESULT hr = S_OK;

		memcpy (&psp, &m_pCfgDlg->m_psp, sizeof(PROPSHEETPAGE));
		hPSP = CreatePropertySheetPage (&psp);
		ASSERT(NULL != hPSP);
		if (NULL == hPSP) _com_issue_error(E_UNEXPECTED);

	UINT uiCnt = 0L;

		hr = m_pCfgDlg -> AddConfigPages (pcDesc, &uiCnt);
		if (FAILED(hr)) _com_issue_error(hr);

	// gesamte Page nur einhängen, wenn wenigstens eine SubPage 
	// installiert wurde
		if (0 < uiCnt) {
			if (!(*lpfnAddPage) (hPSP, lParam)) 
				_com_issue_error(E_UNEXPECTED);
			if (puiCnt)
				*puiCnt = 1;
		}
		else if (puiCnt) 
			*puiCnt = 0;

	} catch (_com_error& hr_result) {
		DELETE (m_pCfgDlg);
		if (puiCnt) *puiCnt = 0;
		return _COM_ERROR(hr_result);
	}
	
return NOERROR;
}

STDMETHODIMP CPropertyChoice::PreConfigPages (IDataObject *pIDO, DWORD dwFlags)
{
	if (NULL == m_pCfgDlg) return E_UNEXPECTED;

// lediglich an alle SubPages weiterreichen
	return m_pCfgDlg -> PreConfigPages (pIDO, dwFlags);
}

///////////////////////////////////////////////////////////////////////////////
// Die eigentlichen Aktionen werden an das zuletzt aktivierte Objekt 
// (DialogPage) weitergereicht (eben 'Choice')
STDMETHODIMP CPropertyChoice::BeginAction (IProgressIndicator *pPI)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;
	return m_pCfgDlg -> BeginAction (pPI);
}

STDMETHODIMP CPropertyChoice::DoAction (IDataObject *pIDO, DWORD dwReserved)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;
	return m_pCfgDlg -> DoAction (pIDO, dwReserved);
}

STDMETHODIMP CPropertyChoice::EndAction (DWORD dwReserved, IDataObject **ppIDataObj)
{
	if (NULL == m_pCfgDlg) 
		return E_UNEXPECTED;
	return m_pCfgDlg -> EndAction (dwReserved, ppIDataObj);
}

///////////////////////////////////////////////////////////////////////////////
// IClassProperty methods
STDMETHODIMP CPropertyChoice::Eval (IEnumLONG *pEnumObj, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPropertyChoice::Cumulation(LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPropertyChoice::Reset (void)
{
	return E_NOTIMPL;
}

STDMETHODIMP_(ULONG) CPropertyChoice::Count (void)
{
	return 0L;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CPropertyChoice::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_PropertyChoice;
	return NOERROR;
}

// IPersistStreamInit methods
STDMETHODIMP CPropertyChoice::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CPropertyChoice::Load (LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

// alles wieder einlesen: zuerst Version überprüfen
DWORD dwVersion = 0L;
HRESULT hr = pStm -> Read (&dwVersion, sizeof(dwVersion), NULL);

	if (S_OK != hr) return hr;
	if (PROPERTYACTION_FORMATVERSION < dwVersion)
		return STG_E_OLDDLL;	// File was written with a newer version

// BeschreibungsString einlesen
ULONG ulCount = 0;

	hr = pStm -> Read (&ulCount, sizeof(ulCount), NULL);
	if (S_OK != hr) return hr;

	try {
		m_strDesc.resize (ulCount+1);
		hr = pStm -> Read ((void *)m_strDesc.c_str(), ulCount, NULL);
		if (S_OK != hr) return hr;
		m_strDesc.adjustlen();

	} catch (...) {
		return E_OUTOFMEMORY;
	}
	
// Anzahl der Aktionen lesen
	hr = pStm -> Read (&ulCount, sizeof(ulCount), NULL);
	if (S_OK != hr) return hr;

// Aktionen instantiieren
	for (ULONG ul = 0; ul < ulCount; ul++) {
	WPropertyAction PropAct;

		hr = OleLoadFromStream (pStm, IID_IPropertyAction, PropAct.ppv());
		if (SUCCEEDED(hr))
			hr = AddAction (PropAct);
		if (FAILED(hr))
			return hr;
	}

// ok, fertig initialisiert
	m_fIsInitialized = true;
	m_fIsDirty = false;

return NOERROR;
}

STDMETHODIMP CPropertyChoice::Save (LPSTREAM pStm, BOOL fClearDirty)
{
// Version des Formates schreiben
DWORD dwVersion = PROPERTYACTION_FORMATVERSION;
HRESULT hr = pStm -> Write (&dwVersion, sizeof(dwVersion), NULL);

	if (FAILED(hr)) return hr;
	
// Schreiben des BeschreibungsStrings
LONG ulCount = m_strDesc.length() +1;	// Länge des Namens

	hr = pStm -> Write (&ulCount, sizeof(ulCount), NULL);
	if (FAILED(hr)) return hr;
	hr = pStm -> Write (m_strDesc.c_str(), ulCount, NULL);
	if (FAILED(hr)) return hr;

// Schreiben der AktionsFolge
	ulCount = m_Actions.size();	// Anzahl der Aktionen
	hr = pStm -> Write (&ulCount, sizeof(ulCount), NULL);
	if (FAILED(hr)) return hr;

	for (CActionList::iterator it = m_Actions.begin(); 
		 it != m_Actions.end(); it++) 
	{
		try {
		WPersistStream StmInit ((*it).Action());		// throws hr

			hr = OleSaveToStream (StmInit, pStm);
			if (FAILED(hr)) _com_issue_error(hr);

		} catch (_com_error& hr) {
			if (E_NOINTERFACE != _COM_ERROR(hr)) 
				return _COM_ERROR(hr);		// sonstiger Fehler, abbrechen
		}
	}

// DirtyFlag entsprechend Anforderungen behandeln
	if (fClearDirty)
		m_fIsDirty = false;

return NOERROR;
}

STDMETHODIMP CPropertyChoice::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

ULONG ulSize = sizeof(DWORD) + 2*sizeof(ULONG) + m_strDesc.length()+1;
 
	for (CActionList::iterator it = m_Actions.begin(); 
		 it != m_Actions.end(); it++) 
	{
		try {
		WPersistStream StmInit ((*it).Action());		// throws hr
		ULARGE_INTEGER uli;

			ULISet32 (uli, 0L);

		HRESULT hr = StmInit -> GetSizeMax (&uli);

			if (FAILED(hr)) _com_issue_error(hr);
			ulSize += uli.LowPart;

		} catch (_com_error& hr) {
			if (E_NOINTERFACE != _COM_ERROR(hr)) 
				return _COM_ERROR(hr);		// sonstiger Fehler, abbrechen
		}
	}

	ULISet32(*pcbSize, ulSize);

return NOERROR;
}

STDMETHODIMP CPropertyChoice::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

// Reste eines evtl. fehlgeschlagenen Load beseitigen
	m_Actions.erase(m_Actions.begin(), m_Actions.end());
	m_fIsInitialized = true;
	m_fIsDirty = false;
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CPropertyChoice::SetDirty (bool fDirty) { m_fIsDirty = fDirty; }

/////////////////////////////////////////////////////////////////////////////
// CChoiceParent

IMPLEMENT_DYNAMIC(CChoiceParent, CPropertySheet)

CChoiceParent::CChoiceParent(
		CRect& rect, LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	: CPropertySheet(pszCaption, pParentWnd, iSelectPage),
	  m_bNoTabs(false), m_iDistanceFromTop(0)
{
	m_Rect = rect;
	AddPage(&m_Page);
}

CChoiceParent::~CChoiceParent()
{
}

BEGIN_MESSAGE_MAP(CChoiceParent, CPropertySheet)
	//{{AFX_MSG_MAP(CChoiceParent)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChoiceParent message handlers

static int module_piButtons[] = { IDOK, IDCANCEL, ID_APPLY_NOW, IDHELP };

BOOL CChoiceParent::OnInitDialog() 
{
HWND hTabWnd;
CRect rectTabCtrl;

	if (m_Rect.right) {
	// resize the tab control
		hTabWnd = (HWND)::GetDlgItem(m_hWnd, AFX_IDC_TAB_CONTROL);
		ASSERT(hTabWnd != NULL);

		::GetWindowRect(hTabWnd, &rectTabCtrl);  // Tab-control rectangle (screen coordinates)
		ScreenToClient(rectTabCtrl);

	// Is tab-control wider than specified width.
		if (rectTabCtrl.right > (m_Rect.Width() - 3))
		{
			rectTabCtrl.right = m_Rect.Width() - 3; // Set new right position
		}

	// The tab-control does only need to show tabs
		rectTabCtrl.bottom = 32;                 // Height for tabs

	// move tab control
		::MoveWindow( hTabWnd, 0, m_iDistanceFromTop, rectTabCtrl.Width(), rectTabCtrl.bottom, TRUE );

	BOOL bResult = (BOOL)Default();          // Process messages

	// If propertysheet m_bNoTabs = TRUE hide the tabs
		if (m_bNoTabs)
		{
			::ShowWindow(hTabWnd, SW_HIDE);
			::EnableWindow(hTabWnd, FALSE);
		}
   
	// change tab style if scrolling tabs desired (stacked tabs are default)
		if (!m_bStacked)
		{
			hTabWnd = (HWND)SendMessage(PSM_GETTABCONTROL);
			if (hTabWnd != NULL)
			{
				CWnd::ModifyStyle(hTabWnd, TCS_MULTILINE, TCS_SINGLELINE, 0);
			}
		}

	// remove standard buttons 
		for (int i = 0; i < 4; i++)
		{
		HWND hWnd = ::GetDlgItem(m_hWnd, module_piButtons[i]);
			
			if (hWnd != NULL)
			{
				::ShowWindow(hWnd, SW_HIDE);
				::EnableWindow(hWnd, FALSE);
			}
		}

	// Move the propertysheet to specified position
		MoveWindow( m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom /*- cyDiff*/ );
		return bResult;
	}
	return CPropertySheet::OnInitDialog();
}

BOOL CChoiceParent::OnSetActive(void)
{
HWND hWndAct = (HWND)SendMessage(PSM_GETCURRENTPAGEHWND);

	if (NULL != hWndAct) {
	NMHDR nmHdr;

		nmHdr.hwndFrom = m_hWnd;
		nmHdr.idFrom = 0;
		nmHdr.code = PSN_SETACTIVE;
		return ::SendMessage(hWndAct, WM_NOTIFY, 0, (LPARAM)&nmHdr);
	}

// (noch) keine aktive Page, also einfach weitermachen
	return 0;
}

LRESULT CChoiceParent::OnWizardBack (void)
{
HWND hWndAct = (HWND)SendMessage(PSM_GETCURRENTPAGEHWND);

	if (NULL != hWndAct) {
	NMHDR nmHdr;

		nmHdr.hwndFrom = m_hWnd;
		nmHdr.idFrom = ID_WIZBACK;
		nmHdr.code = PSN_WIZBACK;
		return ::SendMessage(hWndAct, WM_NOTIFY, 0, (LPARAM)&nmHdr);
	}

// keine aktive Page 
	ASSERT(NULL != hWndAct);
	return 0;
}

BOOL CChoiceParent::OnWizardFinish (void)
{
HWND hWndAct = (HWND)SendMessage(PSM_GETCURRENTPAGEHWND);

	if (NULL != hWndAct) {
	NMHDR nmHdr;

		nmHdr.hwndFrom = m_hWnd;
		nmHdr.idFrom = ID_WIZFINISH;
		nmHdr.code = PSN_WIZFINISH;
		return !::SendMessage(hWndAct, WM_NOTIFY, 0, (LPARAM)&nmHdr);
	}

// keine aktive Page 
	ASSERT(NULL != hWndAct);
	return 0;
}

LRESULT CChoiceParent::OnWizardNext (void)
{
HWND hWndAct = (HWND)SendMessage(PSM_GETCURRENTPAGEHWND);

	if (NULL != hWndAct) {
	NMHDR nmHdr;

		nmHdr.hwndFrom = m_hWnd;
		nmHdr.idFrom = ID_WIZNEXT;
		nmHdr.code = PSN_WIZNEXT;
		return ::SendMessage(hWndAct, WM_NOTIFY, 0, (LPARAM)&nmHdr);
	}

// keine aktive Page 
	ASSERT(NULL != hWndAct);
	return 0;
}

void CChoiceParent::OnCancel() 
{
HWND hWndAct = (HWND)SendMessage(PSM_GETCURRENTPAGEHWND);

	if (NULL != hWndAct) {
	PSHNOTIFY nmHdr;

		nmHdr.hdr.hwndFrom = m_hWnd;
		nmHdr.hdr.idFrom = IDCANCEL;
		nmHdr.hdr.code = PSN_RESET;
		nmHdr.lParam = true;
		::SendMessage(hWndAct, WM_NOTIFY, 0, (LPARAM)&nmHdr);
		return;
	}

// keine aktive Page 
	ASSERT(NULL != hWndAct);
}

BOOL CChoiceParent::OnQueryCancel() 
{
HWND hWndAct = (HWND)SendMessage(PSM_GETCURRENTPAGEHWND);

	if (NULL != hWndAct) {
	NMHDR nmHdr;

		nmHdr.hwndFrom = m_hWnd;
		nmHdr.idFrom = IDCANCEL;
		nmHdr.code = PSN_QUERYCANCEL;
		return !::SendMessage(hWndAct, WM_NOTIFY, 0, (LPARAM)&nmHdr);
	}

// keine aktive Page 
	ASSERT(NULL != hWndAct);
	return 0;
}

LRESULT CChoiceParent::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch(message) {
	case PSM_CANCELTOCLOSE:
	case PSM_PRESSBUTTON:
	case PSM_SETFINISHTEXT:
	case PSM_SETWIZBUTTONS:
	case PSM_SETTITLE:
		GetParent()->SendMessage(message, wParam, lParam);
		break;

	default:
		break;
	}

	return CPropertySheet::WindowProc(message, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CDummyPage property page

IMPLEMENT_DYNCREATE(CDummyPage, CPropertyPage)

CDummyPage::CDummyPage() : CPropertyPage(CDummyPage::IDD)
{
	//{{AFX_DATA_INIT(CDummyPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDummyPage::~CDummyPage()
{
}

void CDummyPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDummyPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDummyPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDummyPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDummyPage message handlers

