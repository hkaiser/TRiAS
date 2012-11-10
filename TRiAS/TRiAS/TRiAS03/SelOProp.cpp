// Auswahl einer Objekteigenschaft und Klassifikation von Objekten nach dieser
// File: SELOPROP.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <eonrguid.h>
#include <statguid.h>
#include <xtsnguid.h>
#include <eieruhr.hxx>
#include <ipropseq.hxx>

#include <funcs03.h>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Strings.h"
#include "SelOProp.h"
#include "clsfyprp.hxx"

/////////////////////////////////////////////////////////////////////////////
// externes
extern char g_pDLLName[_MAX_PATH];

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumObjProps);			// WEnumObjProps
DefineSmartInterface(EnumObjectsByNumber);	// WEnumObjectsByNumber

DefineEnumIIDWrapper(LONG);		// CIID_LONGEnum
DefineSmartEnumerator(LONG);	// WEnumLONG

DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(DataObject);

/////////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CClassifyDlg::CClassifyDlg (CClsfyPropAct *pParent, ResID uiDlg, LPCSTR pcCaption, IObjectProps *pIObjProp) :
	CPropertyPage (uiDlg, pcCaption), 
	m_dwFlags(0L), 
	m_ObjProps(pIObjProp),
	m_cbSelAll (this, IDC_CLASSIFYALL),
	m_ObjPropSrc (this, IDC_OBJPROPERTY_SRC, IDC_SELECT_OBJPROP_SRC),
	m_cbIgnoreCase (this, IDC_CAPITAL_CLASSIFY),
	m_cbMatchBOB (this , IDC_BEGINOFTEXT_CLASSIFY),
	m_sleCnt (this, IDC_COUNT_CHARS),
	m_Spin (this, IDC_COUNT_CHARS_SPIN),
	m_Props(CCompareForClassify(m_iCntMatch, m_fIgnoreCase)),
	m_DupObjs(CCompareForClassify(m_iCntMatch, m_fIgnoreCase))
{
	m_pSelInfo = NULL;
	m_PropIt = m_Props.end();	// initialisieren des Iterators
	m_iCntMatch = 0;
	m_fIgnoreCase = false;
	m_lPacket = 0;
	m_pParent = pParent;
}

#pragma warning (default: 4355)

CClassifyDlg::~CClassifyDlg (void)
{
}

CClassifyDlg *CClassifyDlg::CreateInstance (
	CClsfyPropAct *pParent, UINT uiDlg, LPCSTR pcCaption, 
	ResourceFile &rRF, IObjectProps *pIObjProp)
{
	try {
	CClassifyDlg *pDlg = NULL;
	
		pDlg = new CClassifyDlg (pParent, ResID (uiDlg, &rRF), pcCaption, pIObjProp);
		if (pDlg == NULL || !pDlg -> FInit (rRF)) {
			DELETE_OBJ (pDlg);
			return NULL;
		}
		return pDlg;

	} catch (...) {
		return NULL;
	}
}

bool CClassifyDlg::FInit (ResourceFile &rRF)
{
	return true;
}
	
///////////////////////////////////////////////////////////////////////////////
// EventHandler 
void CClassifyDlg::WindowInit (Event)
{
CEierUhr Wait (this);		// damit es nicht langweilig wird

	m_cbSelAll.FInit();		// Controls initialisieren
	m_cbSelAll.SetChecked (TRUE);

	m_cbIgnoreCase.FInit();
	m_cbMatchBOB.FInit();
	m_sleCnt.FInit();
	m_Spin.FInit();
//	m_Spin.SetBuddy(&m_sleCnt);
	
	m_ObjPropSrc.FInit();

	m_Spin.SetRange(0, 20);
	
// Objekteigenschaften
	if (NULL != m_pSelInfo &&  m_pSelInfo -> m_strObjProp.size() > 0)
		m_ObjPropSrc.InitFromData(m_pSelInfo -> m_strObjProp.c_str());

	AdjustSelectedInfo();
	AdjustOK();
}

void CClassifyDlg::OnSelChanged (NotifyEvt)
{
	AdjustOK();
}

int CClassifyDlg::OnSetActive (NotifyEvt)
{
	AdjustOK();
	return 0;
}

int CClassifyDlg::OnWizNext (NotifyEvt)
{
	if (PrepareResult()) 		// Ergebnisse zwischenspeichern
		return 0;
	return -1;
}

int CClassifyDlg::OnWizFinish (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern
	return 0;
}

void CClassifyDlg::OnCancel (NotifyEvt)
{
	// evtl. Aufräumarbeiten durchführen
}

void CClassifyDlg::ButtonClick (ControlEvt e)
{
	switch ((UINT)e.GetControlID()) {
	case IDC_SELECT_OBJPROP_SRC:
		if (m_ObjPropSrc.ShowObjPropDlg()) {
		os_string strObjProp;

			m_ObjPropSrc.SaveData(strObjProp);
			AdjustOK();
		}
		break;

	case IDC_BEGINOFTEXT_CLASSIFY:
		m_pSelInfo -> m_fMatchBOB = !m_pSelInfo -> m_fMatchBOB;
		if (!m_pSelInfo -> m_fMatchBOB) {
			m_iCntMatch = m_Spin.GetPos();
			m_Spin.SetPos (0);
//			m_sleCnt.SetText("0");
		}
		else {
//		char cbBuffer[64];

			if (0 == m_iCntMatch)
				m_iCntMatch = 1;		// wenigstens ein Buchstabe muß verglichen werden
			m_Spin.SetPos (m_iCntMatch);
//			m_sleCnt.SetText (ltoa (m_iCntMatch, cbBuffer, 10));
			m_sleCnt.SetFocus();
		}
		AdjustOK();
		break;
	}
}

void CClassifyDlg::VertScroll (ScrollEvt e)
{
	CPropertyPage::VertScroll (e);		// erstmal verarbeiten lassen
	if (m_Spin.GetPos() > 0) {
		m_cbMatchBOB.SetChecked (TRUE);
		m_pSelInfo -> m_fMatchBOB = true;
	} 
	else {
		m_cbMatchBOB.SetChecked (FALSE);
		m_pSelInfo -> m_fMatchBOB = false;
	}
	AdjustOK();
}

void CClassifyDlg::EditChange (ControlEvt e)
{
	if (IDC_COUNT_CHARS == (uint)e.GetControlID()) {
	char cbBuffer[64];

		m_sleCnt.GetText (cbBuffer, sizeof(cbBuffer));

	long lNewCnt = atol (cbBuffer);

		if (lNewCnt > 0) {
			m_Spin.SetPos(lNewCnt);
			m_cbMatchBOB.SetChecked (TRUE);
			m_pSelInfo -> m_fMatchBOB = true;
		} 
		else {
			m_Spin.SetPos(0);
//			m_sleCnt.SetText ("0");
			m_cbMatchBOB.SetChecked (FALSE);
			m_pSelInfo -> m_fMatchBOB = false;
		}
		AdjustOK();
	}
}

///////////////////////////////////////////////////////////////////////////////
// HilfsRoutinen 
void CClassifyDlg::AdjustOK (bool fDisableNext)
{
DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns |= PSWIZB_BACK;

// darf kein Child haben
	if (!fDisableNext && !GetDisableNextPage()) {
		if (m_dwFlags & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte seite
	} 
	else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;
		
	SetSheetWizardButtons (dwBttns);
}

BOOL CClassifyDlg::GetDisableNextPage()
{
	if (!m_ObjPropSrc.hasSelection())
		return TRUE;	// Quelle und Ziel müssen gegeben sein

	if (m_pSelInfo -> m_fMatchBOB && 0 == m_Spin.GetPos())
		return TRUE;	// am Textanfang 0 Zeichen zu vergleichen ist Blödsinn
		
	return FALSE;
}

void CClassifyDlg::AdjustSelectedInfo()
{
	m_cbSelAll.SetChecked (m_pSelInfo -> m_fSelectAll);
	m_cbIgnoreCase.SetChecked(m_fIgnoreCase);
	m_cbMatchBOB.SetChecked(m_pSelInfo -> m_fMatchBOB);

	if (!m_pSelInfo -> m_fMatchBOB) {
		m_iCntMatch = 0;
		m_Spin.SetPos (0);
//		m_sleCnt.SetText("0");
	}
	else {
//	char cbBuffer[64];

//		m_sleCnt.SetText (ltoa(m_iCntMatch, cbBuffer, 10));
		m_Spin.SetPos (m_iCntMatch);
	}
}

// Ergebnisdaten aus Controls lesen und zwischenspeichern ---------------------
bool CClassifyDlg::PrepareResult (void)
{
// alten Zustand vergessen
	m_pSelInfo -> m_strObjProp.remove();

// neues Item besorgen (vollständigen ObjPropName)
	m_ObjPropSrc.SaveData (m_pSelInfo -> m_strObjProp);
	m_pSelInfo -> m_fSelectAll = m_cbSelAll.isChecked();
	m_pSelInfo -> m_fIgnoreCase = m_fIgnoreCase = m_cbIgnoreCase.isChecked();
	m_pSelInfo -> m_fMatchBOB = m_cbMatchBOB.isChecked();
	if (m_pSelInfo -> m_fMatchBOB) 
		m_pSelInfo -> m_iCntMatch = m_iCntMatch = m_Spin.GetPos();
	else
		m_pSelInfo -> m_iCntMatch = m_iCntMatch = 0;

// ausgewählte Objekteigenschaft im Kontext ablegen
WPropertyActionSequence Seq;
WDataObject CtxDO;

	if (SUCCEEDED(m_pParent -> GetSite(IID_IPropertyActionSequence, Seq.ppv())) &&
		SUCCEEDED(Seq -> GetSequenceContext (CtxDO.ppi())))
	{
		SetObjectProperty(CtxDO, m_pSelInfo -> m_strObjProp.c_str());
	}
	return true;
}

HRESULT CClassifyDlg::SetSelectedInfo (OBJPROPRESULT *pSelInfo, bool fNoShow)
{
// AnfangsInitialisierung
	if (NULL == pSelInfo) 
		return E_POINTER;

	m_pSelInfo = pSelInfo;
	m_fIgnoreCase = m_pSelInfo -> m_fIgnoreCase;
	m_iCntMatch = m_pSelInfo -> m_iCntMatch;
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// übergibt dem Dialog zu bearbeitende Objekte 
HRESULT CClassifyDlg::SetEnumLONG (IEnum<LONG> *pInEnum)
{
	if (NULL == pInEnum) 	// wird brauchen eine Eingabe !
		return E_NOTIMPL;

// Objekteigenschaft besorgen
WObjectProperty IObjProp;
HRESULT hr = E_FAIL;

	{
	WEnumObjProps IEnum;

		hr = m_ObjProps -> EnumObjectProps (IEnum.ppi());
		if (FAILED(hr)) return hr;

		hr = IEnum -> FindByName (m_pSelInfo -> m_strObjProp.c_str(), IObjProp.ppi());
		if (FAILED(hr)) return hr;
	}	// IEnum goes out of scope

// alle übergebenen Objekte in internen Strukturen speichern
LONG lONr = 0;
char cbBuffer[1024];
ResourceFile RF (g_pDLLName);
ResString resNoValue (ResID(IDS_NOVALUE, &RF), 32);

	IObjProp -> Reset();		// Objekteigenschaft rücksetzen

	for (pInEnum -> Reset(); 
	     S_OK == pInEnum -> Next (1, &lONr, NULL); /**/)
	{
		Tick();		// JG 980914
		if (FAILED(GoOn()))
			return E_ABORT;

		hr = IObjProp -> Eval (lONr, cbBuffer, sizeof(cbBuffer), NULL);
		if (FAILED(hr)) {
			if (m_pSelInfo -> m_fSelectAll && E_FAIL == hr) 
				strcpy (cbBuffer, resNoValue);		// kein Wert ist _ein_ Wert
			else
				continue;	// Fehler, wenn nicht alle berücksichtigen
		}

	os_string str (cbBuffer);
	CProperties::const_iterator it = m_Props.find (str);

		if (it != m_Props.end()) {	// nicht erstes Vorkommen dieses Textes
//		CDupObjects::const_iterator itr = m_DupObjs.find (str);
//
//			if (itr == m_DupObjs.end())
//				m_DupObjs.insert (*it);		// den ersten auch hier speichern
			
			m_DupObjs.insert (make_pair (str, lONr));
		} else {
			m_Props.insert (make_pair (str, lONr));
			m_DupObjs.insert (make_pair (str, lONr));
		}
	}

	IObjProp -> Reset();		// Objekteigenschaft wieder rücksetzen

// Iterator auf Anfang stellen, damit eine Abfrage an der richtigen Stelle beginnen kann
	m_PropIt = m_Props.begin();
	m_lPacket = m_Props.size();
	return S_OK;
}

// Fragt den Dialog nach seinen Daten -----------------------------------------
HRESULT CClassifyDlg::GetNextEnumLONG (IEnum<LONG> **ppOutEnum, os_string &rstr, long &rlPacket)
{
	if (NULL == ppOutEnum) 
		return E_POINTER;

	if (m_Props.size() > 0 && m_PropIt == m_Props.end())
		return E_UNEXPECTED;

HRESULT hr = E_FAIL;
EnumObjectNumbers *pEnum = NULL;

	*ppOutEnum = NULL;		// für den Fall, daß nichts gefunden wird

// gibt's überhaupt mehrfache Objekteigenschaften
	if (0 == m_Props.size() || 0 == m_DupObjs.size()) {
		m_Props.erase();		// alles wieder freigeben
		m_DupObjs.erase();

	// PI schalten
		SetMaxTicks(1);
		TickToEnd();
		return S_OK;
	}

	if (m_PropIt == m_Props.begin()) {
	// JG980914 Anzahl der zu bearbeitenden Elemente bestimmen
	// aber nur beim ersten Aufruf
	// hier wird die anzahl der Eigenschaften genommen, da alles über alles andere keine Informationen vorliegen
	long counter = m_Props.size();

		SetMaxTicks(counter);
	}

	try {
	CDupObjects::const_iterator it = m_DupObjs.lower_bound ((*m_PropIt).first);
	CDupObjects::const_iterator itend = m_DupObjs.upper_bound ((*m_PropIt).first);

	// alle Objekte mit dieser ObjektEigenschaft in EnumLONG kopieren
		_ASSERTE(it != m_DupObjs.end());

	// alle Objekte mit dieser Objekteigenschaft speichern
	WEnumObjectsByNumber Enum (CLSID_EnumObjectsByNumber);
	bool fFirst = true;
	
		while (it != itend) {
			if (fFirst) {
			// zugehörigen Wert speichern
				TX_ASSERT((*it).first.size() > 0);	// String muß gültig sein

				rstr = m_DupObjs.key_comp().GetActualKey((*it).first);
				rlPacket = m_lPacket--;				// Paketnummer rückwärts zählen
				fFirst = false;
			}
			Enum -> AddItem ((*it).second);
			++it;
		}

	WEnumLONG EnumOut (Enum);

		*ppOutEnum = reinterpret_cast<IEnum<LONG> *>(EnumOut.detach());
		++m_PropIt;		// beim nächsten weitermachen

	// JG 980916: Ticker weiterschalten	
		Tick();
		if (FAILED(GoOn()))
			return E_ABORT;

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}

// S_FALSE heißt hier, 'es kommen noch mehr, bitte noch mal rufen'
	if (m_PropIt == m_Props.end()) {
		_ASSERTE(0 == m_lPacket);

		m_Props.erase();		// alles wieder freigeben
		m_DupObjs.erase();
		TickToEnd();
		return S_OK;
	}
	return S_FALSE;
}

