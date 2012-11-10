// Auswahl einer Objekteigenschaft und Klassifikation von Objekten nach dieser
// File: SELOPROP.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <eonrguid.h>
#include <statguid.h>
#include <eieruhr.hxx>

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "SelOProp.h"

/////////////////////////////////////////////////////////////////////////////
// externes
extern char g_pDLLName[_MAX_PATH];

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumObjProps);			// WEnumObjProps
DefineSmartInterface(EnumObjectsByNumber);	// WEnumObjectsByNumber

DefineEnumIIDWrapper(LONG);		// CIID_LONGEnum
DefineSmartEnumerator(LONG);	// WEnumLONG

/////////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CClassifyDlg::CClassifyDlg (
	ResID uiDlg, LPCSTR pcCaption, IObjectProps *pIObjProp)
	      : CPropertyPage (uiDlg, pcCaption), 
		    m_dwFlags(0L), 
			m_ObjProps(pIObjProp),
			m_cbSelAll (this, IDC_CLASSIFYALL)
{
	m_pObjProps = NULL;
	m_PropIt = m_Props.end();	// initialisieren des Iterators
	m_fSelectAll = true;
}

#pragma warning (default: 4355)

CClassifyDlg::~CClassifyDlg (void)
{
	DELETE_OBJ (m_pObjProps);
}

CClassifyDlg *CClassifyDlg::CreateInstance (
	UINT uiDlg, LPCSTR pcCaption, ResourceFile &rRF, IObjectProps *pIObjProp)
{
	try {
	CClassifyDlg *pDlg = NULL;
	
		pDlg = new CClassifyDlg (ResID (uiDlg, &rRF), pcCaption, pIObjProp);
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
// IdentifikatorListBox füllen
	TX_TRY(m_pObjProps = new CSelectObjectPropTree (this, IDC_OBJPROPS, rRF, m_ObjProps));
	if (m_pObjProps == NULL) return false;

	return true;
}
	
///////////////////////////////////////////////////////////////////////////////
// EventHandler 
void CClassifyDlg::WindowInit (Event)
{
CEierUhr Wait (this);		// damit es nicht langweilig wird

	m_cbSelAll.FInit();		// Controls initialisieren
	m_cbSelAll.SetChecked (TRUE);

// Objekteigenschaften
	if (NULL == m_pObjProps || !m_pObjProps -> InitControl())
		return;

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

///////////////////////////////////////////////////////////////////////////////
// HilfsRoutinen --------------------------------------------------------------
void CClassifyDlg::AdjustOK (bool fDisableNext)
{
CPropertySheet *pSheet = GetPropertySheet();

	if (NULL == pSheet || NULL == m_pObjProps) return;

DWORD dwBttns = 0;
HTREEITEM hItem = m_pObjProps -> GetSelectedItem();

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns |= PSWIZB_BACK;

// darf kein Child haben
	if (NULL != hItem && !fDisableNext &&
	    NULL == m_pObjProps -> GetChildItem (hItem)) 
	{
		if (m_dwFlags & ADDPAGES_LASTPAGE)
			dwBttns |= PSWIZB_FINISH;
		else
			dwBttns |= PSWIZB_NEXT;
	}

	pSheet -> SetWizardButtons (dwBttns);
}

void CClassifyDlg::AdjustSelectedInfo()
{
	m_cbSelAll.SetChecked (m_fSelectAll);
	m_pObjProps -> SelectObjProp (m_strObjProp.c_str());
}

// Ergebnisdaten aus Controls lesen und zwischenspeichern ---------------------
bool CClassifyDlg::PrepareResult (void)
{
// alten Zustand vergessen
	m_strObjProp.remove();

// neues Item besorgen (vollständigen ObjPropName)
HTREEITEM hItem, hParent;
string str;

	hItem = m_pObjProps -> GetSelectedItem();
	if (NULL == hItem) return false;

	hParent = m_pObjProps -> GetParentItem (hItem);
	if (NULL == hParent) return false;

	do {
	string strT = m_pObjProps -> GetItemText (hParent);

		str = strT + str;
		str += '\\';
		hParent = m_pObjProps -> GetParentItem (hParent);
	} while (NULL != hParent);
	
	str = "OBJPROP_ROOT\\" + str;
	str += m_pObjProps -> GetItemText (hItem);

	m_strObjProp = str.c_str();
	m_fSelectAll = m_cbSelAll.isChecked();

	return true;
}

HRESULT CClassifyDlg::SetSelectedInfo (OBJPROPRESULT *pSelInfo, bool fNoShow)
{
// AnfangsInitialisierung
//	m_fResultPrepared = fNoShow;

	if (NULL == pSelInfo) return E_POINTER;

	COM_TRY {
		m_strObjProp = pSelInfo -> m_strObjProp;		// umkopieren
		m_fSelectAll = pSelInfo -> m_fSelectAll;
	} COM_CATCH;

	AdjustSelectedInfo();
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

		hr = IEnum -> FindByName (m_strObjProp.c_str(), IObjProp.ppi());
		if (FAILED(hr)) return hr;
	}	// IEnum goes out of scope

// alle übergebenen Objekte in internen Strukturen speichern
LONG lONr = 0;
char cbBuffer[1024];
ResourceFile RF (g_pDLLName);
ResString resNoValue (ResID(IDS_NOVALUE, &RF), 32);

	IObjProp -> Reset();		// Objekteigenschaft rücksetzen

	for (pInEnum -> Reset(); 
	     S_OK == pInEnum -> Next (1, &lONr, NULL); Tick()/* JG 980914*/)
	{
		hr = IObjProp -> Eval (lONr, cbBuffer, sizeof(cbBuffer), NULL);
		if (FAILED(hr)) {
			if (m_fSelectAll && E_FAIL == hr) 
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
	return S_OK;
}

// Fragt den Dialog nach seinen Daten -----------------------------------------
HRESULT CClassifyDlg::GetNextEnumLONG (IEnum<LONG> **ppOutEnum, os_string &rstr)
{
	if (NULL == ppOutEnum) return ResultFromScode (E_POINTER);

	if (m_PropIt == m_Props.end())
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

	if (m_PropIt == m_Props.begin())
	{
		// JG980914 Anzahl der zu bearbeitenden Elemente bestimmen
		// aber nur beim ersten Aufruf
		// hier wird die anzahl der Eigenschaften genommen, da alles über alles andere keine Informationen vorliegen
		long counter = m_Props.size();
		SetMaxTicks(counter);
	}

	try {
		do {
		CDupObjects::const_iterator it = m_DupObjs.find ((*m_PropIt).first);

		// alle Objekte mit dieser ObjektEigenschaft in EnumLONG kopieren
			if (it != m_DupObjs.end()) {
			// mehrfaches Vorkommen dieses Textes
			WEnumObjectsByNumber Enum (CLSID_EnumObjectsByNumber);

			// alle Objekte mit dieser Objekteigenschaft speichern
			bool fFirst = true;

				while (it != m_DupObjs.end() && (*it).first == (*m_PropIt).first) {
					if (fFirst) {
					// zugehörigen Wert speichern
						TX_ASSERT((*it).first.size() > 0);	// String muß gültig sein

						rstr = (*it).first;
						fFirst = false;
					}
					Enum -> AddItem ((*it).second);
					++it;
				}

			WEnumLONG EnumOut (Enum);

				*ppOutEnum = reinterpret_cast<IEnum<LONG> *>(EnumOut.detach());
				++m_PropIt;		// beim nächsten weitermachen
				break;			// ok, Enum ist gefüllt
			}

			// JG 980916
			// Ticker weiterschalten	
			Tick();

		// weitermachen, bis mehrfache ObjEigenschaften oder Ende
		} while (++m_PropIt != m_Props.end());

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}

// S_FALSE heißt hier, 'es kommen noch mehr, bitte noch mal rufen'
	if (m_PropIt == m_Props.end()) {
		m_Props.erase();		// alles wieder freigeben
		m_DupObjs.erase();
		TickToEnd();
		return S_OK;
	}
	return S_FALSE;
}

