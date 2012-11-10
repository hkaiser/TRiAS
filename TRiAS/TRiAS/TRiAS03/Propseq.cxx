// Verwaltung einer Abfolge von IPropertyActions ------------------------------
// File: PROPSEQ.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <Com/MkHelper.h>
#include <Atl/Ciid.h>

#include <eieruhr.hxx>

#include <xtsnguid.h>
#include <statguid.h>
#include <dirisole.h>
#include <funcs03.h>

#include "Strings.h"
#include "DataHelp.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "propseq.hxx"
#include "PropSeqData.h"
#include "selidprp.hxx"		// PropertyAction's
#include "modidprp.hxx"
#include "selobwnd.hxx"

#include "MultiPI.h"		// JG 
#include "ownmacros.h"

///////////////////////////////////////////////////////////////////////////////
// Min-Funktion, da Macro aus stdlib offensichtlich überladen ist
template<class T>
inline T tmin (T a, T b) { return (a > b) ? b : a; }

///////////////////////////////////////////////////////////////////////////////
// Name dieses Modules 
extern char g_pDLLName[_MAX_PATH];
extern "C" HWND __hWndM;

const TCHAR g_cbPropertySequences[] = TEXT("PropertySequences");

///////////////////////////////////////////////////////////////////////////////
// benötigte Interface-Wrapper 
DefineSmartInterface(DataObject);
DefineSmartInterface(EnumFORMATETC);
#if !defined(_DEFINED_OBJECTPROPS)
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(ObjectProps);
#define _DEFINED_OBJECTPROPS
#endif // _DEFINED_OBJECTPROPS
DefineSmartInterface(ClassProperty);
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(EnumClassProps);
DefineSmartInterface(PersistStream);
DefineSmartInterface(PersistStreamInit);
DefineSmartInterface(Storage);
DefineSmartInterface(Stream);
DefineSmartInterface(Persist);
DefineSmartInterface(ObjectWithSite);
#if !defined(_TRIAS_OLDIMPLEMTATION1)
DefineSmartInterface(PropertyAction2);
#endif // _TRIAS_OLDIMPLEMTATION1
DefineSmartInterface(PropertyAction3);

///////////////////////////////////////////////////////////////////////////////
// lokal verwendete Funktionen 
//inline bool IMPL_AND_FAILED (HRESULT hr)
//{
//	return (FAILED(hr)&&!(E_NOTIMPL==GetScode(hr)));
//}

///////////////////////////////////////////////////////////////////////////////
// Konvertieren eines PropAct-Bezeichners in einen Stream-Namen
static string MakeStreamName (LPCSTR pcDesc)
{
char str[32];

	for (int i = 0; i < sizeof(str)-1; i++) {
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
			str[i] = '\0';
			return str;

		default:
			if (c > ' ')
				str[i] = c;
			else
				str[i] = '_';
			break;
		}
	}
	str[i] = '\0';
	return str;
}

///////////////////////////////////////////////////////////////////////////////
// Erzeugen einer Instanz dieses Objektes 
HRESULT PActCreateInstance (LPCSTR pcDesc, REFIID riid, LPVOID *ppvObj)
{
IPropertyActionSequence *pISeq = NULL;
HRESULT hr = CPropertySequence::_CreatorClass::CreateInstance (NULL, IID_IPropertyActionSequence, (LPVOID *)&pISeq);

	if (FAILED(hr)) return hr;

	pISeq -> SetDescription (pcDesc);

	hr = pISeq -> QueryInterface (riid, ppvObj);
	pISeq -> Release();

	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// sonstige HelperFunktionen 

// Fehler beim Erzeugen einer PropertyAction: Fehler melden und weiteres ------
// Vorgehen abfragen
static bool ReportAddError (LPCSTR pcName)
{
ResourceFile RF (g_pDLLName);
ResString resCap (ResID (IDS_GENERRORCAP, &RF), 64);
ResString resText (ResID (IDS_ADDERROR, &RF), 64);
ResString resQuery (ResID (IDS_QUERYCONTINUE, &RF), 64);
char cbBuffer[256];

	wsprintf (cbBuffer, resText, pcName);

string str = cbBuffer;

	str += resQuery;
	if (IDYES == MessageBox (__hWndM, str.c_str(), resCap, MB_ICONEXCLAMATION|MB_YESNO))
		return false;	// weitermachen

	return true;	// Abbrechen und nicht weitermachen
}

///////////////////////////////////////////////////////////////////////////////
// Laden einer PropertySequence aus einer Stream
HRESULT LoadPropertySequence(LPCSTR pcDesc, IStorage *pIStg, 
	LPCOLESTR pcVersion, IPropertyActionSequence **ppISeq)
{
HRESULT hr = E_FAIL;

	USES_CONVERSION;
	if (NULL != pIStg) {	// evtl. gespeicherten Status laden
	WStream IStm;
	string strName = MakeStreamName(pcDesc);

	// Stream erzeugen
		hr = pIStg -> OpenStream (A2OLE(strName.c_str()), NULL, 
						STGM_READ|STGM_SHARE_EXCLUSIVE, 0L, IStm.ppi());

		USES_CONVERSION;
		if (SUCCEEDED(hr)) {
		// aktuelle Streamposition speichern
		LARGE_INTEGER liToPos;
		ULARGE_INTEGER liPos;

			liPos.QuadPart = liToPos.QuadPart = 0;
			if (FAILED(hr = IStm -> Seek(liToPos, STREAM_SEEK_CUR, &liPos)))
				return hr;

		// ggf. gegem XML-Version testen
		DWORD dwSignature = 0;
		DWORD dwVersion = 0;
		bool fMustReset = true;

			LoadData(IStm, dwSignature);
			if (dwSignature == PROPERTYSEQUENCE_SIGNATURE) {
				LoadData(IStm, dwVersion);
				if ((dwVersion & ~PROPERTYSEQUENCE_MINORVERSIONMASK) 
					<= PROPERTYSEQUENCE_LASTKNOWNVERSION)
				{
				// Versionsvergleich ist möglich
				os_string strVersion;

					LoadString(IStm, strVersion);
					if (NULL != pcVersion && strVersion != OLE2A(pcVersion))
						return STG_E_OLDDLL;	// neu erzeugen ist notwendig

					fMustReset = false;
				}
			}
			else if (NULL != pcVersion && wcscmp(L"1.0", pcVersion))
				return STG_E_OLDDLL;			// neu erzeugen ist notwendig

			if (fMustReset) {
			// Stream zurückpositionieren, damit alte Streams geladen werden können
				liToPos.QuadPart = liPos.QuadPart;
				if (FAILED(hr = IStm -> Seek(liToPos, STREAM_SEEK_SET, NULL)))
					return hr;
			}

		WPropertyActionSequence Seq;

			hr = OleLoadFromStream (IStm, IID_IPropertyActionSequence, Seq.ppv());
			if (SUCCEEDED(hr)) {
			// der Sequence die zugehörige XML-Version mitteilen
				if (NULL != pcVersion) {
					hr = Seq -> SetVersion(OLE2A(pcVersion));
					if (FAILED(hr)) return hr;
				}

			// Resultat liefern
				*ppISeq = Seq.detach();
				return S_OK;
			}
		}
	}
	return E_FAIL;
}

///////////////////////////////////////////////////////////////////////////////
// Erzeugen und initialisieren einer PropertyActionSequence, welche die
// vorgegebenen PropertyActions enthält

HRESULT InitPropertyActionSequence (
	LPCSTR pcDesc, CALPCLSID *pcaClsIds, IStorage *pIStg, 
	IPropertyActionSequence **ppISeq)
{
	if (NULL == ppISeq) return E_POINTER;

	*ppISeq = NULL;		// für alle Fälle

WPropertyActionSequence ISeq;

	if (S_OK == LoadPropertySequence(pcDesc, pIStg, NULL, ppISeq))
		return S_OK;		// konnte wieder geladen werden

// wenn Status nicht geladen werden kann, dann neu initialisieren
	{
	HRESULT hr = PActCreateInstance (pcDesc, IID_IPropertyActionSequence, ISeq.ppv());

		if (FAILED(hr)) return hr;

	// Rücksetzen der AktionsFolge
		try {
		WPersistStreamInit Init = ISeq;		// throws hr

			hr = Init -> InitNew();
			if (FAILED(hr)) _com_issue_error(hr);
		
		} catch (_com_error& hr) {
			return _COM_ERROR(hr);
		}

	// hinzufügen der einzelnen Aktionen
		hr = ISeq -> AddActionsByCLSID (pcaClsIds);
		if (FAILED(hr)) return hr;
	}

	*ppISeq = ISeq.detach();
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Öffnen des PropertySequenceSubStorages
HRESULT GetSubPropSeqStorage (IStorage **ppIStg)
{
	if (NULL == ppIStg) return E_POINTER;

WStorage IRootStg;

	if (!DEX_GetProjectStorage(*IRootStg.ppv()))
		return E_FAIL;

	USES_CONVERSION;

WStorage IStg;
HRESULT hr = IRootStg -> OpenStorage (A2OLE(g_cbPropertySequences), NULL, 
					STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
					NULL, 0L, IStg.ppi());
	
	if (FAILED(hr)) {
	// mit Schreibschutz versuchen
		hr = IRootStg -> OpenStorage (A2OLE(g_cbPropertySequences), NULL, 
						STGM_READ|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
						NULL, 0L, IStg.ppi());
		if (FAILED(hr)) return hr;
	}

CLSID clsId;

	hr = ReadClassStg (IStg, &clsId);
	if (FAILED(hr)) return hr;

	if (!IsEqualCLSID (clsId, CLSID_PropertyActionSequence))
		return E_FAIL;

	*ppIStg = IStg.detach();

	return hr;
}

HRESULT SavePropSeq (LPCSTR pcDesc, IPropertyActionSequence *pISeq, IStorage *pIStg)
{
HRESULT hr = E_FAIL;
WStorage IStg (pIStg);

	USES_CONVERSION;
	if (NULL == pIStg) {	// SubStorage sicher anlegen, da es noch nicht existiert
	WStorage IRootStg;

		if (!DEX_GetProjectStorage(*IRootStg.ppv()))
			return E_FAIL;

		hr = IRootStg -> CreateStorage (A2OLE(g_cbPropertySequences),  
						STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED|STGM_CREATE, 
						0L, 0L, IStg.ppi());
		if (FAILED(hr)) return hr;

		hr = WriteClassStg (IStg, CLSID_PropertyActionSequence);
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

	// ggf. XML-Version wegschreiben
	char cbBuffer[_MAX_PATH] = { '\0' };

		hr = pISeq -> GetVersion (cbBuffer, sizeof(cbBuffer), NULL);
		if (FAILED(hr)) _com_issue_error(hr);

		SaveData(IStm, PROPERTYSEQUENCE_SIGNATURE);
		SaveData(IStm, PROPERTYSEQUENCE_LASTKNOWNVERSION);
		SaveString (IStm, os_string(cbBuffer));

	// Sequence selbst wegschreiben
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

///////////////////////////////////////////////////////////////////////////////
// Ausführen einer Folge von PropertyActions
HRESULT RunPropertyActionSequence (
	HWND hWnd, LPCSTR pcDesc, CALPCLSID *pcaClsIds, IProgressIndicator *pIStatus,
	IDataObject *pIInData, IDataObject **ppIOutData, BOOL fInitNew)
{
WPropertyActionSequence ISeq;
WStorage IStg;
HRESULT hr = S_OK;

// evtl. Neuinitialisierung erzwingen
	if (!fInitNew && (GetKeyState (VK_SHIFT) >= 0 || GetKeyState (VK_CONTROL) >= 0))
		GetSubPropSeqStorage (IStg.ppi());

	hr = InitPropertyActionSequence (pcDesc, pcaClsIds, IStg, ISeq.ppi());
	if (FAILED(hr)) return hr;

// durchführen der gewünschten Aktion
	hr = ISeq -> DoActions (hWnd, pIStatus, pIInData, ppIOutData);
	if (FAILED(hr)) return hr;

// Speichern der letzten Nutzerselektion
	return SavePropSeq (pcDesc, ISeq, IStg);
}


///////////////////////////////////////////////////////////////////////////////
// CPropertySequence: InterfaceImplementationen
///////////////////////////////////////////////////////////////////////////////
CPropertySequence::CPropertySequence (void)
{
	m_fIsDirty = false;
	m_fIsInitialized = false;
	m_fPrepared = false;
	m_fSetSiteCalled = false;

	m_lCurrIndex = -1;
	m_iLast = m_iFirst = -1;

	m_dwRegROT = 0L;

	m_strVersion = "1.0";
	m_fIsWizard97 = false;
}

HRESULT CPropertySequence::FinalConstruct()
{
	COM_TRY {
	ResourceFile RF (g_pDLLName);
	ResString resPropInfo (ResID (IDS_PROPINFO_PROPSEQUENCE, &RF), 64);

		m_strDesc = resPropInfo;

	// Kontextobjekt erzeugen
		m_Ctx.CreateInstance (CLSID_DataTransferObject);

	// Moniker erzeugen und registrieren
		RETURN_FAILED_HRESULT(CreateAndRegisterMoniker());

	} COM_CATCH;
	return S_OK;
}

void CPropertySequence::FinalRelease()
{
	m_Ctx.Assign (NULL);
	UnregisterAndFreeMoniker();
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyActionSequence methods 
STDMETHODIMP CPropertySequence::SetDescription (LPCSTR pcDesc)
{
	if (NULL == pcDesc) return E_POINTER;
	
	m_strDesc = pcDesc;

// Moniker erzeugen und registrieren
	RETURN_FAILED_HRESULT(CreateAndRegisterMoniker());
	return NOERROR;
}

// JG 980911
// Holen des nächsten SubPI's
HRESULT CPropertySequence::GetNextSubPI(WProgressIndicator& SubPI)
{
	// Sequenz ohne PI
	if (!m_IMultProgInd)
		return S_OK;	

	COM_TRY {
	// Bereichsüberschreitung
	WProgressIndicator2 tmp;
		
		THROW_FAILED_HRESULT(m_IMultProgInd -> GetRange (m_lCurrIndex, tmp.ppi()));
		++m_lCurrIndex;		// und eins weiter
		SubPI = tmp;		// throw ()
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CPropertySequence::GetDescription (LPSTR pDesc, ULONG ulLen, ULONG *pulWritten)
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

//
// Fügt jeweils eine auszuführende Aktion zu der internen Liste hinzu. Die 
// Reihenfolge, in der die Aktionen hinzugefügt werden muß dabei der Reihenfolge
// der auszuführenden Aktionen entsprechen.
//
STDMETHODIMP CPropertySequence::AddAction (IPropertyAction *pIAct)
{
	if (!m_fIsInitialized) {
	HRESULT hr = InitNew();

		if (FAILED(hr)) return hr;
	}

	try {
		m_Actions.push_back (WPropertyAction(pIAct));
		m_fIsDirty = true;

	} catch (...) {
		TX_ASSERT(false);
		return E_FAIL;
	}
	return S_OK;
}

STDMETHODIMP CPropertySequence::AddActionsByCLSID (CALPCLSID *pcaClsIds)
{
HRESULT hr = E_FAIL;

	if (!m_fIsInitialized) {
		hr = InitNew();
		if (FAILED(hr)) return hr;
	}

// hinzufügen der einzelnen Aktionen
	for (ULONG i = 0; i < pcaClsIds -> cElems; i++) {
		try {
			if (NULL != pcaClsIds -> ppElems[i]) {
			WPropertyAction WAct;

				if (NULL != pcaClsIds -> ppMkData && NULL != pcaClsIds -> ppMkData[i]) {
				// Monikerdaten gegeben
				CIID  Guid (*(pcaClsIds -> ppElems[i]));
				CComBSTR bstrDisplayName (Guid.ProgID().c_str());

					bstrDisplayName.Append(L":");
					bstrDisplayName.AppendBSTR(pcaClsIds -> ppMkData[i]);

				BIND_OPTS bindOpts;

					bindOpts.cbStruct = sizeof(BIND_OPTS);
					THROW_FAILED_HRESULT(::CoGetObject(bstrDisplayName, &bindOpts, 
						WAct.GetIID(), WAct.ppv()));
				}
				else {
				// CLSID gegeben
					WAct = WPropertyAction(*(pcaClsIds -> ppElems[i]));		// throws hr
				}

#if !defined(_TRIAS_OLDIMPLEMTATION1)
				if (NULL != pcaClsIds -> ppvData && NULL != pcaClsIds -> ppvData[i]) {
				// evtl. InitialisierungsDaten vorhanden
				WPropertyAction2 Init;

					if (WAct.IsValid() && 
						SUCCEEDED(WAct -> QueryInterface(Init.ppi())))
					{
					WDataObject Data (CLSID_DataTransferObject);	// throws hr
					CComVariant v(*(pcaClsIds -> ppvData[i]));

						THROW_FAILED_HRESULT(SetVariantData (v, Data, &c_feInitPropAct));
						THROW_FAILED_HRESULT(Init -> InitFromData (Data, false, 0L));
					}
				} else 
#endif // _TRIAS_OLDIMPLEMTATION1
				{
				WPersistStreamInit Init (WAct);			// throws hr
					
					THROW_FAILED_HRESULT(Init -> InitNew());
				}

			// ggf. HeaderTitle richten
				if (NULL != pcaClsIds -> ppHeaderTitle && NULL != pcaClsIds -> ppHeaderTitle[i]) {
				WPropertyAction3 InitHdr;

					USES_CONVERSION;
					if (SUCCEEDED(WAct -> QueryInterface(InitHdr.ppi()))) {
					// Header vorhanden
						THROW_FAILED_HRESULT(InitHdr -> SetHeaderTitle(
							OLE2A(pcaClsIds -> ppHeaderTitle[i])));

					// ggf. SubHeader vorhanden
						if (NULL != pcaClsIds -> ppHeaderSubTitle && 
							NULL != pcaClsIds -> ppHeaderSubTitle[i])
						{
							THROW_FAILED_HRESULT(InitHdr -> SetHeaderSubTitle(
								OLE2A(pcaClsIds -> ppHeaderSubTitle[i])));
						}
					}
				}

				THROW_FAILED_HRESULT(AddAction (WAct));
			} 
			else if (NULL != pcaClsIds -> ppActions && NULL != pcaClsIds -> ppActions[i]) 
			{
			// Objekt ist bereits gegeben
				THROW_FAILED_HRESULT(AddAction((IPropertyAction *)pcaClsIds -> ppActions[i]));
			} 
			else {
				TX_ASSERT(NULL != pcaClsIds -> ppElems[i] || NULL != pcaClsIds -> ppActions[i]);
				continue;		// einfach weitermachen
			}

		} catch (_com_error& hr) {
			return _COM_ERROR(hr);
		}
	}

	return NOERROR;
}

// Callback-Funktion, die von den IPropertyActions gerufen wird, um ihre
// PropertyPages in unseren Dialog reinzuhängen
BOOL __stdcall AddConfigPropertyPage (HPROPSHEETPAGE hPage, LPARAM lParam)
{
	return UINT_MAX > ((CPropertySheet *)lParam) -> AddPage (hPage);
}

//
// Führt die bis hierhin über 'AddAction' hinzugefügten Aktionen aus, indem
// evtl. ein KonfigurationsDialog angezeigt wird (in dem die Aktionen ihre
// PropertyPages einhängen können) - hierfür der Parameter hParent, und an-
// schließend nacheinander die einzelnen Aktionen gerufen werden. Der ersten
// dieser Aktionen wird dabei pIEnum übergeben (als Objekt-Startmenge). Die 
// Ausgabe einer Aktion wird dabei als Eingabe für die jeweils nächste Aktion 
// verwendet. Erzeugt eine Aktion mehrere Objektmengen (s. Flags), dann wird 
// die jeweils nächste Aktion entsprechend oft gerufen.
//
STDMETHODIMP CPropertySequence::DoActions (
		HWND hParent, IProgressIndicator *pIStatus, 
		IDataObject *pIData, IDataObject **ppResult)
{
// wenn keine Actions gegeben sind, dann gleich wieder raus
	if (0 == m_Actions.size() || !m_fIsInitialized) 
		return E_UNEXPECTED;

// Parent-Fenster im Kontext speichern
	SetHWND (hParent, m_Ctx, &c_feMainWindow);
	
// jetzt Aktionen vorbereiten und durchführen
HRESULT hr = PrepareActions (hParent, pIData);

	if (SUCCEEDED(hr)) {
		TX_ASSERT(m_fPrepared);
		hr = ExecuteSequence (hParent, pIStatus, pIData, ppResult);
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Routine, die den Konfigurationsdialog zusammenbaut und anzeigt
STDMETHODIMP CPropertySequence::PrepareActions (HWND hParent, IDataObject *pIData)
{
// wenn keine Actions gegeben sind, dann gleich wieder raus
	if (0 == m_Actions.size() || !m_fIsInitialized) 
		return E_UNEXPECTED;

// Fenster (CPropertySheet) erzeugen
UINT uiCntA = 0;		// Anzahl der eingefügten Pages
DWORD dwAddPageFlags = ADDPAGES_FIRSTPAGE|ADDPAGES_LASTPAGE|ADDPAGES_FIRSTPROPERTYACTION|ADDPAGES_LASTPROPERTYACTION;
HRESULT hr = E_FAIL;

	{
	Window wndP (hParent);		// Parent-Fenster
	CPropertySheet CfgDlg (NULL, &wndP, m_fIsWizard97 ? PSH_WIZARD97 : PSH_WIZARD);

		if (m_fIsWizard97) {
		ResourceFile RF (g_pDLLName);

			CfgDlg.SetHeaderBitmap(ResID(IDB_HEADER, &RF));
//			CfgDlg.SetWatermark(ResID(IDB_WATERMARK, &RF));
		}

		{
		CEierUhr Wait (&wndP);		// EierUhr anzeigen
		LPCSTR pcDesc = (m_strDesc.length() > 0) ? m_strDesc.c_str() : NULL;

			hr = AddConfigPages (AddConfigPropertyPage, (LPARAM)&CfgDlg, pcDesc, &uiCntA);
			if (FAILED(hr)) {
				FreeSiteObjectPointer();
				return hr;
			}

		// im Vorfeld schon mal die Ausgangsdaten vorbeischicken
			hr = PreConfigPages (pIData, dwAddPageFlags);
			if (FAILED(hr)) {
				FreeSiteObjectPointer();
				return hr;
			}
		} // end of CEierUhr

		if (0 != uiCntA) {	// Fenster anzeigen und Config vornehmen
		// Back-Pointer sicher setzen
			SetSiteObjectPointer();

		// Dialog anzeigen
			CfgDlg.Show (Centre);
			if (0 == CfgDlg.Result() || IDCANCEL == CfgDlg.Result()) {
				FreeSiteObjectPointer();
				return E_ABORT;	// abgebrochen oder Fehler
			}
		}
	} // end of CfgDlg

	m_fPrepared = true;
	return S_OK;
}

STDMETHODIMP CPropertySequence::RedoActions (
		HWND hParent, IProgressIndicator *pIStatus, 
		IDataObject *pIData, IDataObject **ppResult)
{
// wenn keine Actions gegeben sind, dann gleich wieder raus
	if (0 == m_Actions.size() || !m_fIsInitialized || !m_fPrepared) 
		return E_UNEXPECTED;

// Parent-Fenster im Kontext speichern
	SetHWND (hParent, m_Ctx, &c_feMainWindow);

// Aktion wiederholt ausführen
	return ExecuteSequence (hParent, pIStatus, pIData, ppResult);
}

HRESULT CPropertySequence::ExecuteSequence (
		HWND hParent, IProgressIndicator *pIStatus, 
		IDataObject *pIData, IDataObject **ppResult)
{
// jetzt eigentliche Aktionen ausführen
DWORD dwFlags = PROPCAPS_NONE;

	try {
	Window wndP (hParent);
	CEierUhr Wait (&wndP);
	WDataObject IDataObj (pIData);

	// Back-Pointer sicher setzen
		SetSiteObjectPointer();

	HRESULT hr = BeginAction (pIStatus);

		if (!IMPL_AND_FAILED(hr))
			hr = DoAction (IDataObj, 0L);
		if (IMPL_AND_FAILED(hr)) _com_issue_error(hr);
		
	// die letzte Aktion bekommt soviele EndAction's, wie sie braucht
	// das letzte IDataObject wird zurückgeliefert
		do {
			hr = EndAction (0L, IDataObj.ppi());
			if (IMPL_AND_FAILED(hr)) _com_issue_error(hr);
		} while (S_FALSE == GetScode(hr));

	// die ErgebnisListe an Aufrufer liefern
		if (ppResult) 
			*ppResult = IDataObj.detach();

	// Flags der gesamten AktionsFolge geben lassen
		GetPropInfo (NULL, 0, &dwFlags);

	// jetzt alle RefCntSchleifen auflösen
		FreeSiteObjectPointer();

	} catch (_com_error& hr) {
		FreeSiteObjectPointer();
		return _COM_ERROR(hr);
	}

// evtl. neuzeichnen, wenn eine der Actions das verlangt hat
	if (dwFlags & PROPCAPS_ACTION_MUSTREPAINTLEGEND) {
		DEX_RefreshLegend();
		DEX_RepaintLegend();
	}
	if (dwFlags & PROPCAPS_ACTION_MUSTREPAINT)
		DEX_RePaint();

	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods
STDMETHODIMP CPropertySequence::AddConfigPages (
		LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
	if (!m_fIsInitialized) return E_UNEXPECTED;

// Site Pointer setzen
	SetSiteObjectPointer();

UINT uiCntA = 0;
int iCnt = 0;

	m_iFirst = m_iLast = -1;
	for (CActionList::iterator it = m_Actions.begin(); it != m_Actions.end(); ++it, ++iCnt) {
	// PropertyAction auffordern, ihre ConfigPages hinzuzufügen
	UINT uiCnt = 0;

		(*it) -> AddConfigPages (lpfnAddPage, lParam, pcDesc, &uiCnt);
		uiCntA += uiCnt;

	// erstes/letztes Objekt mit Dialog
		if (0 != uiCnt) {
			m_iLast = iCnt;
			if (-1 == m_iFirst)
				m_iFirst = iCnt;
		}
	}
	if (NULL != puiCnt)		// Gesamtanzahl der installierten Pages liefern
		*puiCnt = uiCntA;

	return NOERROR;
}

// Im Vorfeld schon mal die Ausgangsdaten vorbeigeschickt bekommen ------------
STDMETHODIMP CPropertySequence::PreConfigPages (IDataObject *pIDataObject, DWORD dwAddPageFlags)
{
	if (!m_fIsInitialized) return E_UNEXPECTED;

int iCnt = 0;
int iLast = m_Actions.size()-1;

	for (CActionList::iterator it = m_Actions.begin(); it != m_Actions.end(); ++it, iCnt++) 
	{
	// Ausgangsdaten vorbeischicken
	DWORD dwFlags = dwAddPageFlags & ~(ADDPAGES_FIRSTPAGE|ADDPAGES_LASTPAGE);

	// wenn die letzte PropertyAction
		if (iCnt == iLast && dwAddPageFlags & ADDPAGES_LASTPROPERTYACTION)
			dwFlags |= ADDPAGES_LASTPROPERTYACTION;

	// wenn letzte PropertyAction mit Dialog
		if (iCnt == m_iLast && dwAddPageFlags & ADDPAGES_LASTPAGE)
			dwFlags |= ADDPAGES_LASTPAGE;

	// wenn Erste, ebenfalls
		if (0 == iCnt && dwAddPageFlags & ADDPAGES_FIRSTPROPERTYACTION)
			dwFlags |= ADDPAGES_FIRSTPROPERTYACTION;
		if (iCnt == m_iFirst && dwAddPageFlags & ADDPAGES_FIRSTPAGE)
			dwFlags |= ADDPAGES_FIRSTPAGE;

	HRESULT hr = (*it) -> PreConfigPages (pIDataObject, dwFlags);

		if (IMPL_AND_FAILED(hr)) return hr;
	}
	return NOERROR;
}

// Beginnen der gespeicherten AktionsFolge, dazu der ersten Aktion ein 
// BeginAction vorbeischicken und die internen Variablen initialisieren
STDMETHODIMP CPropertySequence::BeginAction (IProgressIndicator *pIProgInd)
{
	if (!m_fIsInitialized || !m_fPrepared) return E_UNEXPECTED;

HRESULT hr = NOERROR;

	COM_TRY {
		m_itr = m_Actions.begin();
		if (m_itr == m_Actions.end())
			_com_issue_error(E_UNEXPECTED);

		m_ICurrAct = *m_itr;

// JG für alle Sequenzen in der DEBUG-Variante einen ProgressIndicator erzeugen
//#ifdef _DEBUG
//		if (NULL == pIProgInd) {
//			COM_TRY {
//			// Erstmal für alle einen PI erzeugen
//			WProgressIndicator IProgIndTmp (CLSID_ProgressIndicator);
//			HWND hNewWnd = IProgIndTmp -> InitNew (NULL, 0); /*HANDLE(API_WINDOW_HWND)*/
//
//			// wenn Initialisierung gültig war, dann den PI benutzen
//				if (NULL != hNewWnd) 
//					m_IProgInd = IProgIndTmp;
//			} COM_CATCH_IGNORE;	// dann eben ohne PI
//		} else
//#endif //_DEBUG
		{
			m_IProgInd = pIProgInd;	// das gehört immer dazu
		}

	// ProgressIndicator handeln
	WProgressIndicator IProgIndTmp;

		if (m_IProgInd.IsValid())	{
		// JG hier einen MultiPI erzeugen und in m_IMultProgInd Referenz halten
		WMultiProgressIndicator pMPITemp (CLSID_MultiProgressIndicator);

		// MultiPI initialisieren
			RETURN_FAILED_HRESULT(pMPITemp -> Init (m_Actions.size(), m_IProgInd));
			m_IMultProgInd = pMPITemp;		// OK erfolgreiche Initialisierung

		// wir sind am Anfang der Sequenz
			m_lCurrIndex = 0;

		// den ersten SubIndicator holen
			RETURN_FAILED_HRESULT(GetNextSubPI(IProgIndTmp));
		}

	// Start der Sequence / Transaktion
	LPTRIASTRANSAKTION tmpTrans (new TRiASTransaktion (m_strDesc.c_str()));

		pTrans = tmpTrans;		// and pTrans becomes the owner of the new Transaction

	// ProgInd layouten
		RETURN_FAILED_HRESULT(SetStatTexts());

	// die erste Action bekommt erstmal ein BeginAction
		hr = m_ICurrAct -> BeginAction(IProgIndTmp);
		DO_RETURN_IF_FAILED(GoOn());

	} COM_CATCH;
	return hr;
}

// Hier geschieht die eigentliche Arbeit. Die gesamte AktionsFolge wird 
// erledigt.
STDMETHODIMP CPropertySequence::DoAction (IDataObject *pDataObj, DWORD)
{
	if (!m_fIsInitialized || !m_fPrepared) 
		return E_UNEXPECTED;

	COM_TRY {
	// erste Aktion ausführen 
	WDataObject IDataObj (pDataObj);

	// JG ProgInd layouten
		RETURN_FAILED_HRESULT(SetStatTexts());
	
	HRESULT	hrC = m_ICurrAct -> DoAction (IDataObj, 0L);
		
		if (IMPL_AND_FAILED(hrC)) _com_issue_error(hrC);
		DO_RETURN_IF_FAILED(GoOn());

	// die weiteren Aktionen können mehrere Listen erzeugen
		while (++m_itr != m_Actions.end()) {

		// jeweils den nächsten SubPI holen
		WProgressIndicator IProgIndTmp;
		WPropertyAction INextAct (*m_itr);

		// JG ProgInd layouten
			RETURN_FAILED_HRESULT(GetNextSubPI(IProgIndTmp));
			RETURN_FAILED_HRESULT(SetStatTexts());

		HRESULT hrN = INextAct -> BeginAction (IProgIndTmp);

			if (IMPL_AND_FAILED(hrN)) 
				_com_issue_error(hrN);	// wirklicher Fehler
			DO_RETURN_IF_FAILED(GoOn());

			do {
			// JG ProgInd layouten
				RETURN_FAILED_HRESULT(SetStatTexts());

				hrC = m_ICurrAct -> EndAction (0L, IDataObj.ppi());
				if (IMPL_AND_FAILED(hrC)) _com_issue_error(hrC);
			
				if (!IDataObj) 
					break;	// ok fertig

			// JG ProgInd layouten
				RETURN_FAILED_HRESULT(SetStatTexts());
				hrN = INextAct -> DoAction (IDataObj, 0L);
				if (IMPL_AND_FAILED(hrN)) 
					_com_issue_error(hrN);
				DO_RETURN_IF_FAILED(GoOn());

			} while (S_FALSE == GetScode(hrC));

			m_ICurrAct = INextAct;	// der nächste ist jetzt der aktuelle
		}
	
	} catch (const _com_error &e) { 
		if (E_ABORT != _COM_ERROR(e))
		{
			COM_ASSERT_EX(e);		// Assert, wenn anderer Fehler als abgebrochen
		}
		COM_TRACECOMERROR(e); 
		SetLastError(_COM_ERROR(e)); 
		return _COM_ERROR(e); 
	} catch (const BAD_ALLOC &) { 
		COM_TRACEOUTOFMEMORY(); 
		COM_ASSERT_EX2(E_OUTOFMEMORY); 
		SetLastError(E_OUTOFMEMORY); 
		return E_OUTOFMEMORY; 
	} COM_CATCH_ALL
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Site Pointer setzen
HRESULT CPropertySequence::SetSiteObjectPointer()
{
	if (m_fSetSiteCalled) 
		return S_OK;

WObjectWithSite SiteHolder;

	for (CActionList::iterator it = m_Actions.begin(); it != m_Actions.end(); ++it) {
	// Site Pointer setzen
	
		if (SUCCEEDED((*it) -> QueryInterface (IID_IObjectWithSite, SiteHolder.ppv())))
			SiteHolder -> SetSite (GetUnknown());
	}

	m_fSetSiteCalled = true;
	return S_OK;
}

HRESULT CPropertySequence::FreeSiteObjectPointer (void)
{
	if (m_fSetSiteCalled) {
	WObjectWithSite SiteHolder;

		for (CActionList::iterator it = m_Actions.begin(); it != m_Actions.end(); ++it) 
		{
			if (SUCCEEDED((*it) -> QueryInterface (IID_IObjectWithSite, SiteHolder.ppv())))
				SiteHolder -> SetSite (NULL);		// Site wieder loslassen
		}
		m_fSetSiteCalled = false;
	}

// Moniker abmelden
	UnregisterAndFreeMoniker();
	return S_OK;
}

// Zum Abschluß kriegt die letzte Aktion der Aktionsfolge noch ein EndAction.
STDMETHODIMP CPropertySequence::EndAction (DWORD, IDataObject **ppOutObj)
{
	if (!m_fIsInitialized) 
		return E_UNEXPECTED;

HRESULT hrC = E_UNEXPECTED;

	try {
	// der letzte Aktion bekommt ein EndAction
	WDataObject IDataObj;
	
		hrC = m_ICurrAct -> EndAction (0L, IDataObj.ppi());
		if (IMPL_AND_FAILED(hrC)) _com_issue_error(hrC);

	// die ErgebnisListe an Aufrufer liefern
		if (ppOutObj) 
			*ppOutObj = IDataObj.detach();

		if (S_OK == hrC) {
			m_ICurrAct.Assign(NULL);		// Freigeben der InterfacePointers
			m_IProgInd.Assign(NULL);		// (aber nur bei letztem Enum)
		}

	} catch (_com_error& hr) {
		m_ICurrAct.Assign(NULL);
		m_IProgInd.Assign(NULL);
		return _COM_ERROR(hr);
	}

	// das ende ist nah, aber wir waren erfolgreich	-> Transaktionsende 
	if (pTrans.get() != NULL)
		pTrans -> End();

	return hrC;
}

STDMETHODIMP CPropertySequence::GetSequenceContext (IDataObject **ppIData)
{
	if (NULL == ppIData)
		return E_POINTER;

	*ppIData = NULL;
	COM_TRY {
	WDataObject DO (m_Ctx);

		*ppIData = DO.detach();
	} COM_CATCH;
	return S_OK;
}

// #HK010315: XML-Versionskontrolle
STDMETHODIMP CPropertySequence::GetVersion (LPSTR pVersion, ULONG ulLen, ULONG *pulWritten)
{
	if (NULL == pVersion)
		return E_INVALIDARG;

int iToCopy = min(ulLen-1, (ULONG)m_strVersion.size());

	strncpy (pVersion, m_strVersion.c_str(), iToCopy);
	pVersion[iToCopy] = '\0';

	if (NULL != pulWritten)
		*pulWritten = iToCopy;

	return S_OK;
}

STDMETHODIMP CPropertySequence::SetVersion (LPCSTR pcDesc)
{
	if (NULL == pcDesc)
		return E_INVALIDARG;

	m_strVersion = pcDesc;
	return S_OK;
}

STDMETHODIMP CPropertySequence::SetIsWizard97(VARIANT_BOOL fIsWizard97)
{
#if defined(_USE_WIZARD97)
	m_fIsWizard97 = fIsWizard97 ? true : false;
#else
	m_fIsWizard97 = false;
#endif // defined(_USE_WIZARD97)
	return S_OK;
}

STDMETHODIMP CPropertySequence::GetHeaderTitle (LPSTR pBuffer, ULONG wLen)
{
	ATLTRACENOTIMPL(CPropertySequence::GetHeaderTitle);
}

STDMETHODIMP CPropertySequence::SetHeaderTitle (LPCSTR pcHeaderTitle)
{
	ATLTRACENOTIMPL(CPropertySequence::SetHeaderTitle);
}

STDMETHODIMP CPropertySequence::GetHeaderSubTitle (LPSTR pSubBuffer, ULONG wLen)
{
	ATLTRACENOTIMPL(CPropertySequence::GetHeaderSubTitle);
}

STDMETHODIMP CPropertySequence::SetHeaderSubTitle (LPCSTR pcHeaderSubTitle)
{
	ATLTRACENOTIMPL(CPropertySequence::SetHeaderSubTitle);
}


///////////////////////////////////////////////////////////////////////////////
// IPersist methods
STDMETHODIMP CPropertySequence::GetClassID (LPCLSID lpClassID)
{
	if (NULL == lpClassID)
		return E_POINTER;

	*lpClassID = CLSID_PropertyActionSequence;
	return NOERROR;
}

// IPersistStreamInit methods
STDMETHODIMP CPropertySequence::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CPropertySequence::Load (LPSTREAM pStm)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with InitNew

// alles wieder einlesen: zuerst Version überprüfen
DWORD dwVersion = 0L;
HRESULT hr = pStm -> Read (&dwVersion, sizeof(dwVersion), NULL);

	if (S_OK != hr) return hr;
	if (PROPERTYACTION_FORMATVERSION < (dwVersion & ~MINOR_VERSION_MASK))
		return STG_E_OLDDLL;	// File was written with a newer version

// BeschreibungsString einlesen
#if _TRiAS_VER < 0x0300
os_string str;

	hr = LoadString (pStm, str);
	if (S_OK != hr) return hr;

	m_strDesc = str.c_str();
#else
	hr = LoadString (pStm, m_strDesc);
	if (S_OK != hr) return hr;

	RETURN_FAILED_HRESULT(CreateAndRegisterMoniker());
#endif // _TRiAS_VER < 0x0300

// Anzahl der Aktionen lesen
ULONG ulCount = 0;

	hr = pStm -> Read (&ulCount, sizeof(ulCount), NULL);
	if (S_OK != hr) return hr;
	if (0 == ulCount) return E_FAIL;

// Aktionen instantiieren
	for (ULONG ul = 0; ul < ulCount; ul++) {
	WPropertyAction PropAct;

		hr = OleLoadFromStream (pStm, IID_IPropertyAction, PropAct.ppv());
		if (SUCCEEDED(hr))
			hr = AddAction (PropAct);
		
		if (FAILED(hr)) {
		// alle bisher instantiierten Objekte wieder freigeben, damit
		// evtl. anschließendes InitNew nicht fehlschlägt
			EraseActions();
			return hr;
		}
	}

// ok, fertig initialisiert
	m_fIsInitialized = true;
	m_fIsDirty = false;
	m_fPrepared = true;		// auch ohne Dialog verwendbar
	
	return NOERROR;
}

STDMETHODIMP CPropertySequence::Save (LPSTREAM pStm, BOOL fClearDirty)
{
// Version des Formates schreiben
DWORD dwVersion = PROPERTYACTION_FORMATVERSION;
HRESULT hr = pStm -> Write (&dwVersion, sizeof(dwVersion), NULL);

	if (FAILED(hr)) return hr;
	
// Schreiben des BeschreibungsStrings
#if _TRiAS_VER < 0x0300
os_string str (m_strDesc.c_str());

	hr = SaveString (pStm, str);
	if (FAILED(hr)) return hr;
#else
	hr = SaveString (pStm, m_strDesc);
	if (FAILED(hr)) return hr;
#endif // _TRiAS_VER < 0x0300

// Schreiben der AktionsFolge
LONG ulCount = m_Actions.size();	// Anzahl der Aktionen

	hr = pStm -> Write (&ulCount, sizeof(ulCount), NULL);
	if (FAILED(hr)) return hr;

	for (CActionList::iterator it = m_Actions.begin(); it != m_Actions.end(); ++it) 
	{
		try {
		WPersistStream StmInit (*it);		// throws hr

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

STDMETHODIMP CPropertySequence::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize) return E_POINTER;

ULONG ulSize = sizeof(DWORD) + 2*sizeof(ULONG) + m_strDesc.length()+1;
 
	for (CActionList::iterator it = m_Actions.begin(); 
		 it != m_Actions.end(); ++it) 
	{
		try {
		WPersistStream StmInit (*it);		// throws hr
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

STDMETHODIMP CPropertySequence::InitNew (void)
{
	if (m_fIsInitialized)
		return E_UNEXPECTED;		// already initialized with Load

	EraseActions();
	m_fIsInitialized = true;
	m_fIsDirty = false;
	m_fPrepared = false;

	m_strVersion = "1.0";
	m_fIsWizard97 = false;
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// IClassProperty specific functions
STDMETHODIMP CPropertySequence::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwFlags)
{
	COM_TRY {
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
				 it != m_Actions.end(); ++it) 
			{
			WClassProperty IProp = (*it);	// throws hr
			DWORD dw = 0;

				if (SUCCEEDED(IProp -> GetPropInfo (NULL, 0, &dw)))
					dwFlags |= dw;
			}
			dwFlags &= ~PROPCAPS_CONTAINER_IS_CHOICE;
			dwFlags |= PROPCAPS_CONTAINER_IS_SEQUENCE;		// hat hier Vorrang
			*pdwFlags = dwFlags;
		}

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CPropertySequence::Reset (void)
{
	return E_NOTIMPL;
}

STDMETHODIMP_(ULONG) CPropertySequence::Count (void)
{
	return 0L;
}

STDMETHODIMP CPropertySequence::HelpInfo (LPSTR pBuffer, ULONG wLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	COM_TRY {
		if (NULL != pBuffer && wLen > 0) {
		// Beschreibung übergeben
		ResourceFile RF (g_pDLLName);
		ResString resHelp (ResID (IDS_HELPDESC_PROPSEQUENCE, &RF), 128);
		ULONG ulLen = tmin ((size_t)(wLen-1), strlen(resHelp));

			strncpy (pBuffer, resHelp, ulLen);
			pBuffer[ulLen] = '\0';
		}
	} COM_CATCH;

// HelpFileInfo übergeben
	if (pHelpFile) pHelpFile[0] = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0L;
	return S_OK;
}

STDMETHODIMP CPropertySequence::Eval (IEnumLONG *pEnumObj, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	return E_NOTIMPL;
}

STDMETHODIMP CPropertySequence::Cumulation(LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// Private Funktionen
// Abfragen des Beenden-Status
HRESULT CPropertySequence::GoOn()
{
	// Wie soll denn dann abgebrochen werden
	if (!m_IProgInd)
		return S_OK;

	// Abbruch im StatInd ? 
	if (S_OK == m_IProgInd -> IsCanceled())
		return E_ABORT;

	// Alles klar, weiter so
	return S_OK;
}

// Setzen der Textinformation
HRESULT CPropertySequence::SetStatTexts(void)
{
	if (!m_IProgInd)
		return S_OK;

WProgressIndicator wPI;
		
	COM_TRY {
		wPI = m_IProgInd;
	} COM_CATCH	// Ist schon ein Fehler, wenn die Texte nicht gesetzt werden können

// Prozentanzeige
ResourceFile RF (g_pDLLName);
ResString resText (ResID (IDS_STANDARDSTATUSTEXT, &RF), 128);

	RETURN_FAILED_HRESULT(wPI -> ChangeText(PIFLAG_ADJUSTPERCENT, resText.Addr()));
	RETURN_FAILED_HRESULT(wPI -> ChangeText(PIFLAG_CAPTION, m_strDesc.c_str()));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// OleItemContainerSupport
const size_t GUID_LEN = 38;

HRESULT CPropertySequence::GetPropertyAction (
	LPCTSTR pcItem, DWORD dwSpeedNeeded, REFIID riid, LPVOID *ppvObj, 
	bool fTestRunningOnly)
{
	if (!m_fIsInitialized) 
		return MK_E_EXCEEDEDDEADLINE;

HRESULT hr = S_OK;

	USES_CONVERSION;
	COM_TRY {
	// alles bis zum nächsten Trennzeichen sollte ein ClsID sein
	// Pull out param up to end of string
	size_t nParamLen = 0;

		while (pcItem[nParamLen] != OLECHAR('}') && pcItem[nParamLen] != 0)
			++nParamLen;
		if (pcItem[nParamLen] == OLECHAR('}'))
			++nParamLen;

	OLECHAR cbBuffer[GUID_LEN+1];
	int iLen = min(GUID_LEN, nParamLen);

		wcsncpy (cbBuffer, A2OLE(pcItem), iLen);
		cbBuffer[iLen] = 0;
		if (nParamLen != GUID_LEN) 
			_com_issue_error(MK_E_SYNTAX);

	CIID GuidT (cbBuffer);
	WPropertyAction PropAct;

		if (!GuidT) _com_issue_error(MK_E_SYNTAX);

		for (CActionList::iterator it = m_Actions.begin(); it != m_Actions.end(); ++it) 
		{
		WPersist PS (*it);	// throws hr
		CIID Guid;

			if (SUCCEEDED(PS -> GetClassID (&Guid)) && Guid == GuidT)
				PropAct = (*it);		// gefunden
		}
		if (!PropAct.IsValid())
			hr = E_INVALIDARG;

		if (PropAct.IsValid() && !fTestRunningOnly && NULL != ppvObj)	// Objektklasse ist (jetzt) bekannt
		{
			THROW_FAILED_HRESULT(PropAct -> QueryInterface (riid, ppvObj));
		}

	} COM_CATCH;
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// IOleClientSite
STDMETHODIMP CPropertySequence::GetMoniker (DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk)
{
	TEST_OUT_PARAM(ppmk);

	switch (dwWhichMoniker) {
	case OLEWHICHMK_OBJFULL:
	case OLEWHICHMK_OBJREL:
	// This is just the file we're living in.
		if (m_ThisMk.IsValid()) {
		WMoniker mk (m_ThisMk);

			*ppmk = mk.detach();
		}
		break;

	case OLEWHICHMK_CONTAINER:
	default:
		break;
	}
	return (NULL == *ppmk) ? E_FAIL : S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Monikersupport

namespace {
///////////////////////////////////////////////////////////////////////////////
// ItemMoniker für aktuelle process erzeugen
	inline HRESULT CreatePIDMoniker (IMoniker **ppIMk)
	{
	WMoniker mkPID;
	wchar_t cbPID[32];

		_ultow (GetCurrentProcessId(), cbPID, 16);
		RETURN_FAILED_HRESULT(CreateItemMoniker (L"!", cbPID, ppIMk));
		return S_OK;
	}
}

HRESULT CPropertySequence::CreateAndRegisterMoniker()
{
	if (0 != m_dwRegROT) {
		TX_ASSERT(m_ThisMk.IsValid());
		MkRevokeAsRunning (&m_dwRegROT);
		m_ThisMk.Assign(NULL);
	}

	TX_ASSERT(0 == m_dwRegROT);
	TX_ASSERT(!m_ThisMk.IsValid());

// !MkPropSeq!<Description>
WMoniker mk1, mk2, mk3, mkPid;
CComBSTR bstrMkName(g_cbMkPropSeq);

	bstrMkName.Append(L":");
	bstrMkName.Append(m_strDesc.c_str());

	RETURN_FAILED_HRESULT(CreateItemMoniker(L"!", bstrMkName, m_ThisMk.ppi()));
//	RETURN_FAILED_HRESULT(CreateItemMoniker(L"!", L"\\", mk1.ppi()));
//	RETURN_FAILED_HRESULT(m_ThisMk -> ComposeWith (mk1, FALSE, mk2.ppi()));
	
	RETURN_FAILED_HRESULT(CreatePIDMoniker (mkPid.ppi()));
	RETURN_FAILED_HRESULT(mkPid -> ComposeWith (m_ThisMk, FALSE, mk3.ppi()));
	RETURN_FAILED_HRESULT(MkRegisterAsRunning(ROTFLAGS_REGISTRATIONKEEPSALIVE, 
		GetUnknown(), mk3, &m_dwRegROT));

#if defined(_DEBUG)
CComBSTR bstrMk;

	RETURN_FAILED_HRESULT(MkGetDisplayName(mk3, &bstrMk));
#endif // defined(_DEBUG)

FILETIME ft;

	CoFileTimeNow (&ft);
	RETURN_FAILED_HRESULT(MkNoteChangeTime (m_dwRegROT, &ft));
	return S_OK;
}

HRESULT CPropertySequence::UnregisterAndFreeMoniker()
{
	if (m_ThisMk.IsValid()) {
		TX_ASSERT(0 != m_dwRegROT);
		MkRevokeAsRunning (&m_dwRegROT);
		m_ThisMk.Assign(NULL);
	}
	return S_OK;
}

#if _TRiAS_VER < 0x0300
///////////////////////////////////////////////////////////////////////////////
// old stuff
///////////////////////////////////////////////////////////////////////////////
HRESULT RunPropertyActionSequence (
	HWND, LPCSTR, CALPCSTR *, IProgressIndicator *, IDataObject *, IDataObject **)
{
	return E_NOTIMPL;
}

HRESULT RegisterPropertyActions (REGPROPACTPROC pFcnReg, DWORD dwData)
{
	return S_OK;
}
#endif // _TRiAS_VER < 0x0300
