// PropertyAction, welche Objekte in RechercheFenster anzeigt -----------------
// File: DSTOBWND.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <xtsnguid.h>
#include <eonrguid.h>
#include <statguid.h>

#include <pdataobj.hxx>
#include <funcs03.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "dstobwnd.hxx"

///////////////////////////////////////////////////////////////////////////////
// Min-Funktion, da Macro aus stdlib offensichtlich überladen ist
template<class T>
inline T tmin (T a, T b) { return (a > b) ? b : a; }

///////////////////////////////////////////////////////////////////////////////
// benötigte InterfaceWrapper
DefineSmartInterface(DataObject);
DefineEnumIIDWrapper(LONG);		// CIID_LONGEnum
DefineSmartEnumerator(LONG);	// WEnumLONG

extern char g_pDLLName[_MAX_PATH];		// dieser Modul

CDestObjWndPropAct :: CDestObjWndPropAct (void)
{
	m_pCfgDlg = NULL;
	m_fIsDirty = false;
	m_fIsInitialized = false;

	m_hWnd = NULL;

	try {
	ResourceFile RF (g_pDLLName);
	ResString resPropInfo (ResID (IDS_PROPINFO_ORWNDDEST, &RF), 64);

		m_strDesc = resPropInfo;
	} catch (...) {
		TX_ASSERT(false);
	}
}

CDestObjWndPropAct :: ~CDestObjWndPropAct (void)
{
	DELETE_OBJ(m_pCfgDlg);
}

// *** IClassProperty specific functions *** ----------------------------------
STDMETHODIMP CDestObjWndPropAct :: GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Namen der Property kopieren
			if (m_strDesc.length() > 0) {
			ULONG ulLen = tmin ((size_t)(wLen-1), m_strDesc.length());

				strncpy (pBuffer, m_strDesc.c_str(), ulLen);
				pBuffer[ulLen] = '\0';
			} else {
			ResourceFile RF (g_pDLLName);
			ResString resPropInfo (ResID (IDS_PROPINFO_ORWNDDEST, &RF), 64);
			ULONG ulLen = tmin ((size_t)(wLen-1), strlen(resPropInfo));

				strncpy (pBuffer, resPropInfo, ulLen);
				pBuffer[ulLen] = '\0';
			}
		}
	} catch (...) {
		return E_FAIL;
	}

// wenn gewünscht, Flags übergeben
	if (pdwFlags) *pdwFlags = PROPCAPS_ACTION_SINK;

return NOERROR;
}

STDMETHODIMP CDestObjWndPropAct::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	try {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung übergeben
		ResourceFile RF (g_pDLLName);
		ResString resHelp (ResID (IDS_HELPDESC_ORWNDDEST, &RF), 128);
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

// *** IPropertyAction methods ------------------------------------------------
STDMETHODIMP CDestObjWndPropAct::AddConfigPages (
				LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, 
				LPCSTR pcDesc, UINT *puiCnt)
{
	if (NULL != pcDesc)		// Caption ist gegeben, in jedem Fall speichern
		SetPropInfo (pcDesc, 0L);
	
// wenn kein ORFenster geöffnet ist, dann Page nicht anzeiegen
	if (0 == DEX_ActiveObjectsCount()) {
		DELETE_OBJ(m_pCfgDlg);	// evtl. vorherigen freigeben

		if (puiCnt) *puiCnt = 0;		// keine Page !
		return S_OK;
	}

// Dialog anlegen
	try {
	// nun von zugehöriger ClassProperty unseren Namen besorgen
	char cbCaption[128];

		GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
	ResourceFile RF (g_pDLLName);

		DELETE_OBJ(m_pCfgDlg);	// evtl. vorherigen freigeben
		m_pCfgDlg = CDestObjWndDlg::CreateInstance (this, ResID (IDD_DESTOBJWND_WIZ, &RF), cbCaption);
		if (NULL == m_pCfgDlg) _com_issue_error(E_OUTOFMEMORY);
	//
	// Achtung MFC-Falle !
	// Normalerweise müßte an dieser Stelle lpfnAddPage mit unserem 
	// HPROPERTYPAGE gerufen werden, wir aber wissen (darf man das ?), daß
	// sich hinter dem eigentlich durchzureichendem lParam der Pointer auf
	// unsern PropertySheet verbirgt.
	//
		if (UINT_MAX == ((CPropertySheet *)lParam) -> AddPage (m_pCfgDlg))
			_com_issue_error(E_UNEXPECTED);

		if (puiCnt) *puiCnt = 1;

	} catch (_com_error& hr_result) {
		DELETE_OBJ (m_pCfgDlg);
		if (puiCnt) *puiCnt = 0;
		return _COM_ERROR(hr_result);
	}
	
return NOERROR;
}

STDMETHODIMP CDestObjWndPropAct::PreConfigPages (IDataObject *, DWORD dwFlags)
{
	if (NULL != m_pCfgDlg) m_pCfgDlg -> SetFlags (dwFlags);
	return NOERROR;
}

STDMETHODIMP CDestObjWndPropAct::DoAction (IDataObject *pIDataObj, DWORD)
{
WEnumLONG IEnumObj;
HRESULT hr = GetEnumLONGData (pIDataObj, IEnumObj.ppi());

	if (FAILED(hr)) return hr;
	return SetEnumLONG (IEnumObj);
}

STDMETHODIMP CDestObjWndPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{
	DELETE_OBJ (m_pCfgDlg);	// DialogPage freigeben
	*ppDataObj = NULL;	// kein output

return NOERROR;		// nicht nochmal rufen
}

///////////////////////////////////////////////////////////////////////////////
// erzeugt ORFenster bzw. fügt zu existierendem hinzu
HRESULT CDestObjWndPropAct::SetEnumLONG (IEnum<LONG> *pEnum)
{
// Objektfeld anlegen
long lCnt = pEnum -> Count();
long *plObjs = NULL;
HRESULT hr = E_OUTOFMEMORY;

	if (0 == lCnt) {
	// Fehlermeldung ausgeben und raus
	Window Wnd (__hWndM);
	char cbCaption[128];

		GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	ResourceFile RF (g_pDLLName);
	ResString resText (ResID (IDS_NOOBJECTSFOUND, &RF), 255);
	MessBox mb (cbCaption, resText, &Wnd);

		mb.SetType (OkayButton|ExclamationIcon);
		mb.Show();
		return S_FALSE;
	}
	try {
		TX_TRY(plObjs = new long [lCnt]);
		if (NULL == plObjs) _com_issue_error(E_OUTOFMEMORY);
		
		pEnum -> Reset();
		if (S_OK != pEnum -> Next(lCnt, plObjs, NULL))
			_com_issue_error(E_UNEXPECTED);
		
	} catch (_com_error& hr) {
		DELETE_OBJ(plObjs);
		return _COM_ERROR(hr);
	}

// evtl. alte Objekte deselektieren
	if (NULL == m_hWnd && NULL != m_pCfgDlg)
		m_hWnd = m_pCfgDlg -> GetORWindow();

bool fSelectNew = (NULL != m_pCfgDlg) ? m_pCfgDlg -> FSelectNew() : false;
bool fRetainSelection = (NULL != m_pCfgDlg) ? m_pCfgDlg -> FRetainSel() : true;

	if (NULL != m_hWnd && !fRetainSelection)
		DEXOR_UnselectObject (m_hWnd, -1);	// alles deselektieren

// RechercheFenster anlegen
CREATEOBJEKTINFOEX2 COI;
ResourceFile RF (g_pDLLName);
ResString resCaption (ResID (IDS_NEWOBJCAPTION, &RF), 64);
POINT pt;

	pt.x = 0, pt.y = 0;
	
	INITSTRUCT (COI, CREATEOBJEKTINFOEX2);
	COI.lpCaption = (char *)resCaption.Addr();
	COI.plObjs = plObjs;
	COI.iNumObjs = short(lCnt);
	COI.cMColor = RGB(255, 0, 0);
	COI.pntPos = pt;
	COI.m_iFlags = ROSortText;
	COI.m_hWnd = m_hWnd;

	m_hWnd = DEX_CreateObjektInfo(COI);
	if (NULL == m_hWnd) {
		DELETE_OBJ (plObjs);
		return ResultFromScode (E_FAIL);
	}

// neue Objekte selektieren
	DELETE_OBJ (plObjs);
	if (!fSelectNew) return NOERROR;

LONG lONr = 0;

// JG980914 Anzahl der zu bearbeitenden Elemente bestimmen
	long counter = pEnum -> Count();
	SetMaxTicks(counter);

	for (pEnum -> Reset(); 
	     S_OK == pEnum -> Next (1, &lONr, NULL); Tick()/*JG*/)
	{
		DEXOR_SelectObject (m_hWnd, lONr);
	}
	// sicherheitshalber bis zum Ende ticken
	TickToEnd();

return NOERROR;
}		        

///////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit specific functions 
STDMETHODIMP CDestObjWndPropAct::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	m_fIsInitialized = true;
	m_fIsDirty = false;

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CDestObjWndPropAct::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_DestinationObjectWindow;
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPersistStream methods
STDMETHODIMP CDestObjWndPropAct::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CDestObjWndPropAct::Load (LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

HRESULT hr = CPropertyAction::Load (pStm);

	if (FAILED(hr)) return hr;

	m_fIsInitialized = true;
	m_fIsDirty = false;

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CDestObjWndPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags) 
{
	if (NULL == pcBuffer) return E_POINTER;

	m_strDesc = pcBuffer;
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CDestObjWndPropAct::SetDirty (bool fDirty) { m_fIsDirty = fDirty; }
