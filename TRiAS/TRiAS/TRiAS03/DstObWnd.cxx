// PropertyAction, welche Objekte in RechercheFenster anzeigt -----------------
// File: DSTOBWND.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <Com/VariantHelpers.h>

#include <xtsnguid.h>
#include <eonrguid.h>
#include <statguid.h>

#include <pdataobj.hxx>
#include <funcs03.h>
#include <TrCatIds.h>
#include <clsfyprp.h>

#include <IPropSeq.hxx>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "dstobwnd.hxx"

///////////////////////////////////////////////////////////////////////////////
// Min-Funktion, da Macro aus stdlib offensichtlich überladen ist
template<class T>
inline T tmin (T a, T b) { return (a > b) ? b : a; }

namespace {
// Farbwerte auf korrektes Intervall begerenzen
	inline void
	LimitColor (long &rlColor)
	{
		if (rlColor < 0)
			rlColor = 0;
		if (rlColor > 255)
			rlColor = 255;
	}
}

///////////////////////////////////////////////////////////////////////////////
// benötigte InterfaceWrapper
DefineSmartInterface(DataObject);
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(PropertyActionSequence);

DefineEnumIIDWrapper(LONG);		// CIID_LONGEnum
DefineSmartEnumerator(LONG);	// WEnumLONG

extern char g_pDLLName[_MAX_PATH];		// dieser Modul

CDestObjWndPropAct :: CDestObjWndPropAct (void)
{
	m_pCfgDlg = NULL;
	m_fIsDirty = false;
	m_fIsInitialized = false;

	m_hWnd = NULL;
	m_fIsFirstPacket = true;
	m_fPutAllInOne = false;
	m_lPacket = 0;
	m_lMissingPacketOffset = 0;
	m_fShownWarning = false;

	m_cMColor = DEFAULT_MARK_COLOR;
	m_fForceNew = false;

	try {
	ResourceFile RF (g_pDLLName);
	ResString resPropInfo (ResID (IDS_PROPINFO_ORWNDDEST, &RF), 64);
	ResString resCaption (ResID (IDS_NEWOBJCAPTION, &RF), 64);
	ResString resError (ResID (IDS_NOOBJECTSFOUND, &RF), 256);

		m_strDesc = resPropInfo;
		m_strCaption = resCaption;
		m_strErrorMsg = resError;

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

return S_OK;
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
	
return S_OK;
}

// *** IPropertyAction methods ------------------------------------------------
STDMETHODIMP CDestObjWndPropAct::AddConfigPages (
				LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, 
				LPCSTR pcDesc, UINT *puiCnt)
{
	if (NULL != pcDesc)		// Caption ist gegeben, in jedem Fall speichern
		SetPropInfo (pcDesc, 0L);
	
// wenn kein ORFenster geöffnet ist, dann Page nicht anzeiegen
// wenn IsNoShow() gesetzt ist, dann neues Fenster erzeugen
	if (IsNoShow() || 0 == DEX_ActiveObjectsCount()) {
		DELETE_OBJ(m_pCfgDlg);		// evtl. vorherigen freigeben
		if (puiCnt) 
			*puiCnt = 0;	// keine Page !
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

	HPROPSHEETPAGE hPSP = this -> CreatePage(m_pCfgDlg);

		if (NULL == hPSP) return E_HANDLE;
		if (!(*lpfnAddPage) (hPSP, lParam))
			return E_FAIL;

		if (puiCnt) *puiCnt = 1;

	} catch (_com_error& hr_result) {
		DELETE_OBJ (m_pCfgDlg);
		if (puiCnt) *puiCnt = 0;
		return _COM_ERROR(hr_result);
	}
	return S_OK;
}

STDMETHODIMP CDestObjWndPropAct::PreConfigPages (IDataObject *, DWORD dwFlags)
{
	if (NULL != m_pCfgDlg) 
		m_pCfgDlg -> SetFlags (dwFlags);
	m_vecCollectObjects.clear();
	return S_OK;
}

STDMETHODIMP CDestObjWndPropAct::DoAction (IDataObject *pIDataObj, DWORD)
{
WEnumLONG IEnumObj;
HRESULT hr = GetEnumLONGData (pIDataObj, IEnumObj.ppi());

	if (S_OK != hr) 
		return S_OK;		// nothing to do

// Paketnummer sorgt dafür, das jede Sendung in ein eigenes Fenster kommt
// jedoch nur, wenn nicht ein bestimmtes Zielfenster ausgewählt wurde
long lPacket = 0;

	GetPacketNumber (pIDataObj, &lPacket);		// Fehler ignorieren

// u.U. hat eine vorherige GeoKomponente eine voreinzustellende Objekteigenschaft
// hinterlassen
WObjectProperty ObjProp;

	if (FAILED(GetObjectProperty(pIDataObj, ObjProp.ppi()))) {
	WPropertyActionSequence Seq;
	WDataObject CtxDO;

		if (SUCCEEDED(GetSite (IID_IPropertyActionSequence, Seq.ppv())) &&
			SUCCEEDED(Seq -> GetSequenceContext (CtxDO.ppi())))
		{
			GetObjectProperty (CtxDO, ObjProp.ppi());
		}
	}
	return SetEnumLONG (pIDataObj, IEnumObj, lPacket, ObjProp);
}

STDMETHODIMP CDestObjWndPropAct::EndAction (DWORD, IDataObject **ppDataObj)
{
	DELETE_OBJ (m_pCfgDlg);	// DialogPage freigeben
	*ppDataObj = NULL;	// kein output
	return S_OK;		// nicht nochmal rufen
}

///////////////////////////////////////////////////////////////////////////////
// erzeugt ORFenster bzw. fügt zu existierendem hinzu

// ID des View-Fensters 
#define ID_TRIASVIEW_GEODB		0xE900		// AFX_IDW_PANE_FIRST

HRESULT CDestObjWndPropAct::SetEnumLONG (
	IDataObject *pIDO, IEnum<LONG> *pEnum, long lPacket, IObjectProperty *pIObjProp)
{
	++m_lPacket;

ResourceFile RF (g_pDLLName);

// Objektfeld anlegen
long lCnt = pEnum -> Count();
INT_PTR *plObjs = NULL;
HRESULT hr = E_OUTOFMEMORY;

	if (0 == lCnt) {
	// Fehlermeldung ausgeben und raus
	Window Wnd (GetDlgItem(__hWndM, ID_TRIASVIEW_GEODB));
	char cbCaption[128];

		GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

	// evtl. Fehlertext besorgen
	os_string strErrorMsg (m_strErrorMsg);
	CComVariant vErrMsg;

		USES_CONVERSION;
		if (S_OK == GetVariantData(pIDO, const_cast<FORMATETC *>(&c_fePAORWndErrMsg), &vErrMsg) &&
			SUCCEEDED(vErrMsg.ChangeType(VT_BSTR)))
		{ 
			strErrorMsg = OLE2A(V_BSTR(&vErrMsg));
		}

	MessBox mb (cbCaption, strErrorMsg.c_str(), &Wnd);

		mb.SetType (OkayButton|ExclamationIcon);
		mb.Show();
		return S_FALSE;
	}

// Nutzer warnen, wenn er zu viele Fenster erzeugen will
	if (m_fIsFirstPacket) {
		if (lPacket > 10) {
		char cbCaption[128];
		ResString resFmt (ResID (IDS_WARNIFTOMANYORWNDS, &RF), 2*_MAX_PATH);
		char cbBuffer[2*_MAX_PATH];

			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);
			wsprintf (cbBuffer, resFmt, lPacket);
			if (lPacket > MAX_ORWNDS_TOSHOW) {
			// Warnung dahingehend erweitern, daß lediglich MAX_ORWNDS_TOSHOW
			// Fenster angezeigt werden
			char cbAddOn[_MAX_PATH];
			ResString resAddOn (ResID(IDS_WARNIFTOMANYORWNDS_ADDON, &RF), 128);

				wsprintf (cbAddOn, resAddOn, MAX_ORWNDS_TOSHOW);
				strcat (cbBuffer, cbAddOn);
				m_lMissingPacketOffset = lPacket - MAX_ORWNDS_TOSHOW;
			}

		Window Wnd (__hWndM);
		MessBox mb (cbCaption, cbBuffer, &Wnd);

			mb.SetType (YesNoCancelButtons|QuestionMarkIcon);
			switch (mb.Show()) {
			case YesReply:
				break;

			case NoReply:
				m_fPutAllInOne = true;
				break;

			default:
			case CancelReply:
				return E_ABORT;			// ganz abbrechen
			}
		}
		m_fIsFirstPacket = false;		// nur einmal
	}
	else if (!m_fPutAllInOne && m_lPacket > MAX_ORWNDS_TOSHOW) {
	// mehr als 100 Fenster zu erzeugen
		if (!m_fShownWarning) {
		// Warnung ausgeben, daß mehr als 100 Fenster nicht angezeigt werden
		char cbCaption[128];
		ResString resFmt (ResID (IDS_WARNIFREALLYTOMANYORWNDS, &RF), 2*_MAX_PATH);
		char cbBuffer[2*_MAX_PATH];

			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);
			wsprintf (cbBuffer, resFmt, MAX_ORWNDS_TOSHOW);

		Window Wnd (__hWndM);
		MessBox mb (cbCaption, cbBuffer, &Wnd);

			mb.SetType (OkayButton|ExclamationIcon);
			mb.Show();
			m_fShownWarning = true;
		}
		return S_OK;
	}

// Feld für Objektnummern bereitstellen
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

	if (NULL == m_hWnd && NULL != m_pCfgDlg && !m_fForceNew)
		m_hWnd = m_pCfgDlg -> GetORWindow();
		
// #HK001107: die GeoKomponente kann jetzt mehrere Fenster erzeugen. Das wird in
// Abhängigkeit von der Paketnummer entschieden. Die Paketnummer 0 bewirkt die
// alte Funktionalität, Alle anderen Paketnummern erzeugen jeweils ein Fenster.
	if (NULL == m_hWnd && !m_fPutAllInOne) {
	// Pakete nur dann auswerten, wenn nicht ein bestimmtes Zielfenster ausgewählt wurde
	CPacketWnds::iterator it = m_Wnds.find (lPacket);

		if (it != m_Wnds.end())
			m_hWnd = (*it).second;
	}

// evtl. alte Objekte deselektieren
bool fSelectNew = (NULL != m_pCfgDlg) ? m_pCfgDlg -> FSelectNew() : false;
bool fRetainSelection = (NULL != m_pCfgDlg) ? m_pCfgDlg -> FRetainSel() : true;

	if (NULL != m_hWnd && !fRetainSelection)
		DEXOR_UnselectObject (m_hWnd, -1);	// alles deselektieren

// evtl. Caption besorgen
os_string strCaption (m_strCaption);
CComVariant vCap;

	USES_CONVERSION;
	if (S_OK == GetVariantData(pIDO, const_cast<FORMATETC *>(&c_feORWndCaption), &vCap) &&
		SUCCEEDED(vCap.ChangeType(VT_BSTR)))
	{ 
		strCaption = OLE2A(V_BSTR(&vCap));
	}

// evtl. Farbe besorgen
COLORREF cMColor = m_cMColor;
CComVariant vColor;

	if (S_OK == GetVariantData(pIDO, const_cast<FORMATETC *>(&c_fePAORWndColor), &vColor) &&
		SUCCEEDED(vColor.ChangeType(VT_BSTR)))
	{ 
	long lRed = 255, lGreen = 0, lBlue = 0;

		if (3 == sscanf(OLE2A(V_BSTR(&vColor)), "%d,%d,%d", &lRed, &lGreen, &lBlue)) {
			LimitColor(lRed);
			LimitColor(lGreen);
			LimitColor(lBlue);
			cMColor = RGB(lRed, lGreen, lBlue);
		}
	}

// ggf. anzuzeigende Objekteigenschaft setzen
WObjectProperty ObjProp;

	if (S_OK == GetObjectProperty(pIDO, ObjProp.ppi()))
		pIObjProp = ObjProp;

// RechercheFenster anlegen
int iDelta = GetSystemMetrics(SM_CYCAPTION) + 3*GetSystemMetrics(SM_CYBORDER);
POINT pt;

	if (!m_fPutAllInOne) {
	// entweder gibt es nur ein Packet und dann muß auch der Offset 0 sein oder
	// es dürfen eben nicht mehr Packete als vorgesehen ankommen (max. MAX_ORWNDS_TOSHOW)
		_ASSERTE((0 == lPacket && 0 == m_lMissingPacketOffset) || 
				 lPacket > m_lMissingPacketOffset);

	long lCorrPacket = lPacket - m_lMissingPacketOffset;

		pt.x = (0 == lCorrPacket) ? 0 : (lCorrPacket-1)/10 * iDelta;
		pt.y = (0 == lCorrPacket) ? 0 : (lCorrPacket-1)%10 * iDelta;

	CREATEOBJEKTINFOEX3 COI;

		INITSTRUCT (COI, CREATEOBJEKTINFOEX3);
		COI.lpCaption = const_cast<char *>(strCaption.c_str());
		COI.plObjs = plObjs;
		COI.lNumObjs = lCnt;
		COI.cMColor = cMColor;
		COI.pntPos = pt;
		COI.m_iFlags = ROSortObjNr|ROAddPureObjects;
		COI.m_hWnd = m_hWnd;
		COI.m_pIObjProp = pIObjProp;

		m_hWnd = DEX_CreateObjektInfo(COI);
		DELETE_OBJ (plObjs);
		if (NULL == m_hWnd) {
			return ResultFromScode (E_FAIL);
		}
	}
	else {
	// alles in ein Fenster ausgeben
		copy(plObjs, plObjs+lCnt, 
			inserter(m_vecCollectObjects, m_vecCollectObjects.end()));

		if (1 >= lPacket) {		
		// bei mehreren Gruppen hat die letzte die Nummer 1, bei einer Gruppe
		// hat diese Gruppe die Nummer 0
		
		// Objekte werden erst mit dem letzten Paket ausgegeben
			pt.x = pt.y = 0;

		CREATEOBJEKTINFOEX3 COI;

			INITSTRUCT (COI, CREATEOBJEKTINFOEX3);
			COI.lpCaption = const_cast<char *>(strCaption.c_str());
			COI.plObjs = (long *)m_vecCollectObjects.begin();
			COI.lNumObjs = m_vecCollectObjects.size();
			COI.cMColor = cMColor;
			COI.pntPos = pt;
			COI.m_iFlags = ROSortObjNr|ROAddPureObjects;
			COI.m_hWnd = m_hWnd;
			COI.m_pIObjProp = pIObjProp;

			m_hWnd = DEX_CreateObjektInfo(COI);
			if (NULL == m_hWnd) {
				DELETE_OBJ (plObjs);
				return ResultFromScode (E_FAIL);
			}
		}
		DELETE_OBJ (plObjs);
	}

// FensterHandle für das nächste Paket speichern
	m_Wnds.insert (CPacketWnds::value_type(lPacket, m_hWnd));
	if (0 != lPacket && !m_fPutAllInOne)
		m_hWnd = NULL;		// das nächste Paket muß ins neue Fenster
	
// neue Objekte selektieren
	if (!fSelectNew) return S_OK;

	if (!m_fPutAllInOne) {
	LONG lONr = 0;

	// JG980914 Anzahl der zu bearbeitenden Elemente bestimmen
	long counter = pEnum -> Count();

		SetMaxTicks(counter);
		for (pEnum -> Reset(); S_OK == pEnum -> Next (1, &lONr, NULL); /**/)
		{
			Tick();
			if (FAILED(GoOn()))
				return E_ABORT;

			DEXOR_SelectObject (m_hWnd, lONr);
		}
		TickToEnd();	// sicherheitshalber bis zum Ende ticken
	}
	else {
	long counter = m_vecCollectObjects.size();
	os_vector<long>::iterator end = m_vecCollectObjects.end();

		SetMaxTicks(counter);
		for (os_vector<long>::iterator it = m_vecCollectObjects.begin(); 
			 it != end; ++it)
		{
			Tick();
			if (FAILED(GoOn()))
				return E_ABORT;

			DEXOR_SelectObject (m_hWnd, *it);
		}
		TickToEnd();	// sicherheitshalber bis zum Ende ticken
	}
	return S_OK;
}		        

///////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit specific functions 
STDMETHODIMP CDestObjWndPropAct::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	COM_TRY {
	ResourceFile RF (g_pDLLName);
	ResString resCaption (ResID (IDS_NEWOBJCAPTION, &RF), 64);
	ResString resError (ResID (IDS_NOOBJECTSFOUND, &RF), 256);

		m_cMColor = DEFAULT_MARK_COLOR;
		m_strCaption = resCaption;
		m_strErrorMsg = resError;
		m_fForceNew = false;

	} COM_CATCH;
	
	m_fIsInitialized = true;
	m_fIsDirty = false;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CDestObjWndPropAct::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_DestinationObjectWindow;
	return S_OK;
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

DWORD dwSignature = 0;
DWORD dwVersion = 0;

	LoadData(pStm, dwSignature);
	if (dwSignature != DESTWINDPA_SIGNATURE)
		return E_UNEXPECTED;
	LoadData(pStm, dwVersion);
	if ((dwVersion & ~DESTWINDPA_MINORVERSIONMASK) > DESTWINDPA_LASTKNOWNVERSION)
		return STG_E_OLDDLL;

HRESULT hr = CPropertyAction::Load (pStm);

	if (FAILED(hr)) return hr;

	LoadData(pStm, m_cMColor);
	LoadString(pStm, m_strCaption);
	LoadString(pStm, m_strErrorMsg);
	if (dwVersion >= DESTWINDPA_VERSION_101)
		LoadData(pStm, m_fForceNew);
	else
		m_fForceNew = false;

	m_fIsInitialized = true;
	m_fIsDirty = false;

	return S_OK;
}

STDMETHODIMP CDestObjWndPropAct::Save(IStream *pIStm, BOOL fClearDirty)
{
	SaveData(pIStm, DESTWINDPA_SIGNATURE);
	SaveData(pIStm, DESTWINDPA_LASTKNOWNVERSION);

HRESULT hr = CPropertyAction::Save(pIStm, fClearDirty);

	SaveData (pIStm, m_cMColor);
	SaveString (pIStm, m_strCaption);
	SaveString (pIStm, m_strErrorMsg);
	SaveData (pIStm, m_fForceNew);

	if (fClearDirty)
		m_fIsDirty = false;
	return S_OK;
}

STDMETHODIMP CDestObjWndPropAct::GetSizeMax(ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;
	pcbSize -> QuadPart = 0L;

	RETURN_FAILED_HRESULT(CPropertyAction::GetSizeMax (pcbSize));
	pcbSize -> QuadPart += 2*sizeof(long) + ::GetSizeMax(m_strCaption) 
		+ ::GetSizeMax(m_strErrorMsg) + sizeof(bool);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyInfo specific functions 
STDMETHODIMP CDestObjWndPropAct::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags) 
{
	if (NULL == pcBuffer) return E_POINTER;

	m_strDesc = pcBuffer;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Sonstiges
void CDestObjWndPropAct::SetDirty (bool fDirty) { m_fIsDirty = fDirty; }

/////////////////////////////////////////////////////////////////////////////
// IPersistPropertyBag
STDMETHODIMP CDestObjWndPropAct::Load (IPropertyBag *pBag, IErrorLog *pLog)
{
	USES_CONVERSION;
	RETURN_FAILED_HRESULT(CPropertyAction::Load (pBag, pLog));

	COM_TRY {
	ResourceFile RF (g_pDLLName);
	ResString resCaption (ResID (IDS_NEWOBJCAPTION, &RF), 64);
	ResString resError (ResID (IDS_NOOBJECTSFOUND, &RF), 256);

		m_cMColor = DEFAULT_MARK_COLOR;
		m_strCaption = resCaption;
		m_strErrorMsg = resError;
		m_fForceNew = false;

	} COM_CATCH;

// sonstige Werte Analysieren

// MarkColor=
CComVariant vColor;
HRESULT hr = pBag -> Read (CComBSTR("MarkColor"), &vColor, pLog);

	if (S_OK == hr && SUCCEEDED(vColor.ChangeType(VT_BSTR))) {
	long lRed = 255, lGreen = 0, lBlue = 0;

		if (3 == sscanf(OLE2A(V_BSTR(&vColor)), "%d,%d,%d", &lRed, &lGreen, &lBlue)) {
			LimitColor(lRed);
			LimitColor(lGreen);
			LimitColor(lBlue);
			m_cMColor = RGB(lRed, lGreen, lBlue);
		}
	}

// Caption=
CComVariant vCaption;

	hr = pBag -> Read (CComBSTR("Caption"), &vCaption, pLog);
	if (S_OK == hr && SUCCEEDED(vCaption.ChangeType(VT_BSTR))) 
		m_strCaption = OLE2A(V_BSTR(&vCaption));

// ErrorMsg=
CComVariant vErrorMsg;

	hr = pBag -> Read (CComBSTR("ErrorMsg"), &vErrorMsg, pLog);
	if (S_OK == hr && SUCCEEDED(vErrorMsg.ChangeType(VT_BSTR))) 
		m_strErrorMsg = OLE2A(V_BSTR(&vErrorMsg));

// ForceNew=
CComVariant vForceNew;

	hr = pBag -> Read (CComBSTR("ForceNew"), &vForceNew, pLog);
	if (S_OK == hr && SUCCEEDED(vForceNew.ChangeType(VT_BOOL))) 
		m_fForceNew = V_BOOL(&vForceNew);

	return S_OK;
}

