// PropertyAction, welche Objekte auf einen auszuwählenden Ident umklassifiziert
// File: MODIDPRP.CXX

#include "trias03p.hxx"
#include "trias03.h"

//#include <int64.h>
#include <xtsnguid.h>
#include <eonrguid.h>
#include <statguid.h>
#include <dirisole.h>

#include <ipropseq.hxx>
#include <pdataobj.hxx>
#include <funcs03.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Strings.h"
#include "DataHelp.h"
#include "modidprp.hxx"

///////////////////////////////////////////////////////////////////////////////
// Min-Funktion, da Macro aus stdlib offensichtlich überladen ist
template<class T>
inline T tmin (T a, T b) { return (a > b) ? b : a; }

///////////////////////////////////////////////////////////////////////////////
// benötigte InterfaceWrapper
DefineSmartInterface(DataObject);
DefineSmartInterface(PropertyActionSequence);
DefineEnumIIDWrapper(LONG);		// CIID_LONGEnum
DefineSmartEnumerator(LONG);	// WEnumLONG
DefineSmartInterface(ClassProperty);

extern char g_pDLLName[_MAX_PATH];		// dieser Modul

// 0E54C9ED-20DE-11CF-BA55-00AA0018497C	
// DEFINE_GUID(CLSID_ModifyIdent, 0x0E54C9EDL, 0x20DE, 0x11CF, 0xBA, 0x55, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C);
// const char c_cbModPrpName[] = "CLSPROP_ROOT\\TRiAS® (allgemein)\\Modifikation der Objektklasse";

CModIDPropAct::CModIDPropAct (void)
{
	m_pCfgDlg = NULL;
	m_fIsDirty = false;
	m_fIsInitialized = false;

	m_fHasInitData = false;
	m_fAddToView = false;
	m_fShowConnections = true;
	m_lIdent = 0L;
	
	m_fCheckMode = FALSE;
	m_fCheckModeChecked = FALSE;
	m_iCopyMode = 0;

	try {
	ResourceFile RF (g_pDLLName);
	ResString resPropInfo (ResID (IDS_PROPINFO_MODIDENT, &RF), 64);

		m_strDesc = resPropInfo;
	} catch (...) {
		TX_ASSERT(false);
	}
}

CModIDPropAct::~CModIDPropAct (void)
{
	DELETE_OBJ(m_pCfgDlg);
}

///////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions 
STDMETHODIMP CModIDPropAct::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
		ULONG ulLen = tmin ((size_t)(wLen-1), m_strDesc.length());

			strncpy (pBuffer, m_strDesc.c_str(), ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return E_FAIL;
	}

// wenn gewünscht, Flags übergeben
	if (pdwFlags) {
		*pdwFlags = PROPCAPS_ACTION_SINK_MULTI|PROPCAPS_ACTION_SOURCE|
					PROPCAPS_ACTION_MUSTREPAINT|PROPCAPS_ACTION_MUSTREPAINTLEGEND;
	}

return NOERROR;
}

STDMETHODIMP CModIDPropAct::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung übergeben
		ResourceFile RF (g_pDLLName);
		ResString resHelp (ResID (IDS_HELPDESC_MODIDENT, &RF), 128);
		ULONG ulLen = tmin ((size_t)(wLen-1), strlen(resHelp));

			strncpy (pBuffer, resHelp, ulLen);
			pBuffer[ulLen] = '\0';
		}
	} catch (...) {
		return E_FAIL;
	}

// HelpFileInfo übergeben
	if (pHelpFile) pHelpFile[0] = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0L;
	
return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods 
STDMETHODIMP CModIDPropAct::AddConfigPages (
				LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, 
			    LPCSTR pcDesc, UINT *puiCnt)
{
char cbCaption[128];

	try {
		if (NULL != pcDesc)		// Caption ist gegeben
			strcpy (cbCaption, pcDesc);
		else	// von zugehöriger ClassProperty unseren Namen besorgen
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

		DELETE_OBJ(m_pCfgDlg);	// evtl. vorherigen freigeben
		m_pCfgDlg = CModifyIdentDlg::CreateInstance (this, 
						ResID (fChoice ? IDD_MODIFYIDS_WIZPP : IDD_MODIFYIDS_WIZ, &RF), cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);

		if (!IsNoShow()) {
		HPROPSHEETPAGE hPSP = this -> CreatePage(m_pCfgDlg);
		
			if (NULL == hPSP) 
				return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_FAIL;
		}

		if (m_fHasInitData) {
			if (IsNoShow()) {
				m_pCfgDlg -> SetSelectedIdent (m_lIdent);
				m_pCfgDlg -> PrepareResultIdent();
			} 
			else {
				m_pCfgDlg -> SetSelectedIdent (m_lIdent);
				m_pCfgDlg -> SetAddToView (m_fAddToView);
				m_pCfgDlg -> SetShowConnections (m_fShowConnections);
				m_pCfgDlg -> SetCheckMode (m_fCheckMode, m_fCheckModeChecked);
				m_pCfgDlg -> SetCopyMode(m_iCopyMode);
			}
		}

		if (NULL != puiCnt) 
			*puiCnt = IsNoShow() ? 0 : 1;

	} catch (_com_error& hr_result) {
		DELETE_OBJ (m_pCfgDlg);
		if (puiCnt) *puiCnt = 0;
		return _COM_ERROR(hr_result);
	}
	
return NOERROR;
}

STDMETHODIMP CModIDPropAct::PreConfigPages (IDataObject *, DWORD dwFlags)
{
	m_pCfgDlg -> SetFlags (dwFlags);
	return NOERROR;
}

STDMETHODIMP CModIDPropAct::DoAction (IDataObject *pIDataObj, DWORD)
{
WEnumLONG IEnumObj;
HRESULT hr = GetEnumLONGData (pIDataObj, IEnumObj.ppi());

	if (S_OK != hr) 
		return S_OK;		// nothing to do

// JG
// hier findet die Verarbeitung statt
	m_pCfgDlg -> SetAction(this);	
	return m_pCfgDlg -> SetEnumLONG (IEnumObj);
}

STDMETHODIMP CModIDPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{
	if (NULL == ppDataObj) 
		return E_POINTER;
	*ppDataObj = NULL;

HRESULT hr = S_OK;
WEnumLONG IEnumObj;
	
	m_pCfgDlg -> GetCheckMode (m_fCheckMode, m_fCheckModeChecked);
	if (!m_fCheckMode || m_fCheckModeChecked || m_iCopyMode != 0) 
		hr = m_pCfgDlg -> GetEnumLONG (IEnumObj.ppi());			// verarbeiten
	else
		hr = m_pCfgDlg -> GetInputEnumLONG (IEnumObj.ppi());	// lediglich weiterreichen
	if (FAILED(hr)) return hr;

// DataObject generieren
	*ppDataObj = NULL;
	try {
	WDataObject IDO (CLSID_DataTransferObject);
	
		THROW_FAILED_HRESULT(SetEnumLONGData (IEnumObj, IDO));
		*ppDataObj = IDO.detach();

	} catch (_com_error& hr_result) {
		hr = _COM_ERROR(hr_result);
	// hier durchfallen
	}

// letzter Enumerator/PropAction erzeugt lediglich eine Objektmenge
	m_lIdent = m_pCfgDlg -> GetSelectedIdent();
	m_fAddToView = m_pCfgDlg -> GetAddToView();
	m_fShowConnections = m_pCfgDlg -> GetShowConnections();

	DELETE_OBJ (m_pCfgDlg);		// DialogPage freigeben
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CModIDPropAct::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_ModifyIdent;
	return NOERROR;
}

// IPersistStreamInit methods
STDMETHODIMP CModIDPropAct::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CModIDPropAct::Load (LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

long lSignature = 0L;

	THROW_FAILED_HRESULT(pStm -> Read (&lSignature, sizeof(long), NULL));			// Signatur
	if (MODIDPRP_SIGNATURE != lSignature)
		return E_UNEXPECTED;

// Version lesen und überprüfen
long lVersion = 0;

	RETURN_FAILED_HRESULT(pStm -> Read (&lVersion, sizeof(long), NULL));
	if ((lVersion & ~MODIDPRP_VERSION_MINOR_MASK) > MODIDPRP_VERSION_100)
		return STG_E_OLDDLL;	// File was written with a newer version

// zuerst Bezeichner einlesen
HRESULT hr = CPropertyAction::Load (pStm);

	if (FAILED(hr)) return hr;

// dann selektierte Info der letzten Auswahl
LONG lIdent = 0L;
LONG lAddToView = 0L;
LONG lShowConns = 0L;

	RETURN_FAILED_HRESULT(LoadLong(pStm, lIdent));
	RETURN_FAILED_HRESULT(LoadLong(pStm, lAddToView));

	TX_ASSERT(sizeof(long) == sizeof(BOOL));
	RETURN_FAILED_HRESULT(LoadLong(pStm, (long &)m_fCheckMode));
	RETURN_FAILED_HRESULT(LoadLong(pStm, (long &)m_fCheckModeChecked));

	RETURN_FAILED_HRESULT(LoadLong(pStm, lShowConns));
	RETURN_FAILED_HRESULT(LoadLong(pStm, m_iCopyMode));

	if (NULL == m_pCfgDlg) {
	// Dialog ist noch nicht initialisiert
		m_lIdent = lIdent;
		m_fAddToView = lAddToView ? true : false;
		m_fShowConnections = lShowConns ? true : false;
		m_fHasInitData = true;
	} 
	else {
		m_pCfgDlg -> SelectIdent (lIdent);
		m_pCfgDlg -> SetAddToView (lAddToView ? true : false);
		m_pCfgDlg -> SetShowConnections (lShowConns ? true : false);
		m_pCfgDlg -> SetCheckMode (m_fCheckMode, m_fCheckModeChecked);
		m_pCfgDlg -> SetCopyMode(m_iCopyMode);
	}
	
	m_fIsInitialized = true;
	m_fIsDirty = false;
	return NOERROR;
}

STDMETHODIMP CModIDPropAct::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	RETURN_FAILED_HRESULT(pStm -> Write (&MODIDPRP_SIGNATURE, sizeof(long), NULL));
	RETURN_FAILED_HRESULT(pStm -> Write (&LASTKNOWN_MODIDPRP_VERSION, sizeof(long), NULL));

// zuerst Bezeichner wegschreiben
HRESULT hr = CPropertyAction::Save (pStm, fClearDirty);

	if (FAILED(hr)) return hr;

// dann selektierte Info der letzten Auswahl
	RETURN_FAILED_HRESULT(pStm -> Write (&m_lIdent, sizeof(LONG), NULL));

LONG lAddToView = m_fAddToView ? true : false;

	RETURN_FAILED_HRESULT(SaveLong(pStm, lAddToView));

	RETURN_FAILED_HRESULT(SaveLong(pStm, m_fCheckMode));
	RETURN_FAILED_HRESULT(SaveLong(pStm, m_fCheckModeChecked));

LONG lShowConns = m_fShowConnections ? true : false;

	RETURN_FAILED_HRESULT(SaveLong(pStm, lShowConns));
	RETURN_FAILED_HRESULT(SaveLong(pStm, m_iCopyMode));

	if (fClearDirty) m_fIsDirty = false;
	return NOERROR;
}

STDMETHODIMP CModIDPropAct::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

ULARGE_INTEGER cbSize;
HRESULT hr = CPropertyAction::GetSizeMax (&cbSize);

	if (FAILED(hr)) return hr;

ULARGE_INTEGER liOwnSize;

	liOwnSize.QuadPart = UINT(7 * sizeof(LONG));
	liOwnSize.QuadPart += cbSize.QuadPart;
	*pcbSize = liOwnSize;
	return S_OK;
}

STDMETHODIMP CModIDPropAct::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_lIdent = 0L;
	m_fAddToView = false;
	m_fHasInitData = false;
	m_fShowConnections = true;

	m_fCheckMode = FALSE;
	m_fCheckModeChecked = FALSE;
	m_iCopyMode = 0;

	m_fIsInitialized = true;
	m_fIsDirty = false;

	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CModIDPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags)  
{
	if (NULL == pcBuffer) 
		return E_POINTER;

	m_strDesc = pcBuffer;
	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CModIDPropAct::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyAction::Load (pBag, pLog));

	m_lIdent = 0L;
	m_fAddToView = false;

// sonstige Werte Analysieren
// Name=
//CComVariant vDataName;
//HRESULT hr = pBag -> Read (CComBSTR(g_cbPAName), &vDataName, pLog);
//HPROJECT hPrDest = NULL;
//
//	if (S_OK == hr && SUCCEEDED(vDataName.ChangeType (VT_BSTR))) 
//		m_strDesc = OLE2A(V_BSTR(&vDataName));

// DataSource=
CComVariant vDataSrc;
HRESULT hr = pBag -> Read (CComBSTR(g_cbDataSource), &vDataSrc, pLog);
HPROJECT hPrDest = NULL;

	if (S_OK == hr && SUCCEEDED(vDataSrc.ChangeType (VT_BSTR))) 
		hPrDest = DEX_GetDataSourceHandleFromShortName(OLE2A(V_BSTR(&vDataSrc)));

// ModifyTo=
CComVariant vModifyTo;

	hr = pBag -> Read (CComBSTR(g_cbModifyTo), &vModifyTo, pLog);
	if (S_OK == hr && SUCCEEDED(vModifyTo.ChangeType(VT_BSTR))) {
	ULONG ulIdent = 0;

		hr = IdentFromClass (hPrDest, OLE2A(V_BSTR(&vModifyTo)), &ulIdent, FALSE);
		if (S_OK == hr)
			m_lIdent = ulIdent;
	}

// CheckMode=
CComVariant vParam;

	hr = pBag -> Read (CComBSTR(g_cbCheckMode), &vParam, pLog);
	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BOOL)))
	{
		m_fCheckMode = V_BOOL(&vParam) ? TRUE : FALSE;
	}

// Checked=
	if (m_fCheckMode) {
		vParam.Clear();
		hr = pBag -> Read (CComBSTR(g_cbCheckModeChecked), &vParam, pLog);
		if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BOOL)))
		{
			m_fCheckModeChecked = V_BOOL(&vParam) ? TRUE : FALSE;
		}
	} else
		m_fCheckModeChecked = FALSE;

CComVariant vAddToView;

	hr = pBag -> Read (CComBSTR("AddToView"), &vAddToView, pLog);
	if (S_OK == hr && SUCCEEDED(vAddToView.ChangeType (VT_BOOL)))
		m_fAddToView = V_BOOL(&vAddToView) ? true : false;

// ShowConnections=
	vParam.Clear();
	hr = pBag -> Read (CComBSTR("ShowConnections"), &vParam, pLog);
	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_BOOL)))
	{
		m_fShowConnections = V_BOOL(&vParam) ? TRUE : FALSE;
	}

// CopyMode=
	vParam.Clear();
	hr = pBag -> Read (CComBSTR("CopyMode"), &vParam, pLog);
	if (S_OK == hr && SUCCEEDED(vParam.ChangeType (VT_I4)))
	{
		m_iCopyMode = V_I4(&vParam);
	}

	m_fHasInitData = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CModIDPropAct::SetDirty (bool fDirty) { m_fIsDirty = fDirty; }

// Versuchen aus globalem DataObjekt neu zu initialisieren
HRESULT CModIDPropAct::ReInitFromData ()
{
	COM_TRY {
	WPropertyActionSequence Seq;
	WDataObject CtxDO;

		THROW_FAILED_HRESULT(GetSite (IID_IPropertyActionSequence, Seq.ppv()));
		THROW_FAILED_HRESULT(Seq -> GetSequenceContext (CtxDO.ppi()));
		if (SUCCEEDED(InitFromData (CtxDO, FALSE, 0L))) {
			m_pCfgDlg -> SetSelectedIdent (m_lIdent);
			m_pCfgDlg -> SetAddToView (m_fAddToView);
			m_pCfgDlg -> SetCheckMode (m_fCheckMode, m_fCheckModeChecked);
			m_pCfgDlg -> SetShowConnections(m_fShowConnections);
			m_pCfgDlg -> SetCopyMode(m_iCopyMode);
//			m_pCfgDlg -> SetCaption(m_strDesc.c_str());
			m_pCfgDlg -> ReInitList();
		}

	} COM_CATCH;
	return S_OK;
}

