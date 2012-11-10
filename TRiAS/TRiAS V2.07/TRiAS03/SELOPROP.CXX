// Auswahl einer Objekteigenschaft und Klassifikation von Objekten nach dieser
// File: SELOPROP.CXX

#include "trias03p.hxx"
#include "trias03.h"

#include <eieruhr.hxx>

#include "enumonr.hxx"
#include "seloprop.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CClassifyDlg :: CClassifyDlg (ResID uiDlg, LPCSTR pcCaption, DWORD dwFlags, IObjectProps *pIObjProp)
	      : CPropertyPage (uiDlg, pcCaption), m_dwFlags(dwFlags), m_ObjProps(pIObjProp),
	        m_rbEqual(this, IDC_EQUAL), m_rbExists(this, IDC_EXISTS)
{
	m_pObjProps = NULL;
	m_fExists = false;
	m_fEqual = false;

	m_PropIt = m_Props.end();	// initialisieren des Iterators
}

#pragma warning (default: 4355)

CClassifyDlg :: ~CClassifyDlg (void)
{
	DELETE (m_pObjProps);
}

CClassifyDlg *CClassifyDlg :: CreateInstance (UINT uiDlg, LPCSTR pcCaption, 
			DWORD dwFlags, ResourceFile &rRF, IObjectProps *pIObjProp)
{
	try {
	CClassifyDlg *pDlg = NULL;
	
		pDlg = new CClassifyDlg (ResID (uiDlg, &rRF), pcCaption, dwFlags, pIObjProp);
		if (pDlg == NULL || !pDlg -> FInit (rRF)) {
			DELETE (pDlg);
			return NULL;
		}
		return pDlg;
	} catch (...) {
		return NULL;
	}
}

bool CClassifyDlg :: FInit (ResourceFile &rRF)
{
// IdentifikatorListBox füllen
	m_pObjProps = new CSelObjPropTree (this, IDC_OBJPROPS, rRF, m_ObjProps);
	if (m_pObjProps == NULL) return false;

return true;
}
	
///////////////////////////////////////////////////////////////////////////////
// EventHandler ---------------------------------------------------------------
void CClassifyDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDC_EXISTS:
		break;

	case IDC_EQUAL:
		break;
	}
}

void CClassifyDlg :: WindowInit (Event)
{
CEierUhr Wait (this);		// danmit es nicht langweilig wird

// Objekteigenschaften
	if (NULL == m_pObjProps || !m_pObjProps -> InitControl())
		return;

// sonstige Controls initialisieren
	m_rbExists.FInit();
	m_rbEqual.FInit();

	m_rbEqual.SetState (true);
	m_rbExists.SetState (false);

m_rbExists.Disable();

	AdjustOK();
}

void CClassifyDlg :: OnSelChanged (NotifyEvt)
{
	AdjustOK();
}

int CClassifyDlg :: OnSetActive (NotifyEvt)
{
	AdjustOK();
	return 0;
}

int CClassifyDlg :: OnWizNext (NotifyEvt)
{
	if (PrepareResult()) 		// Ergebnisse zwischenspeichern
		return 0;

return -1;
}

int CClassifyDlg :: OnWizFinish (NotifyEvt)
{
	PrepareResult();	// Ergebnisse zwischenspeichern

// wir sind die letzten, also Rückkehrwert aus PropertySheet setzen
CPropertySheet *pSheet = GetPropertySheet();

	if (NULL != pSheet)
		pSheet -> EndDialog(1);	

return 0;
}

void CClassifyDlg :: OnCancel (NotifyEvt)
{
	// evtl. Aufräumarbeiten durchführen
}

///////////////////////////////////////////////////////////////////////////////
// HilfsRoutinen --------------------------------------------------------------
void CClassifyDlg :: AdjustOK (bool fDisableNext)
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

// Ergebnisdaten aus Controls lesen und zwischenspeichern ---------------------
bool CClassifyDlg :: PrepareResult (void)
{
// alten Zustand vergessen
	m_strObjProp.remove();
	m_fExists = false;
	m_fEqual = false;

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
	m_fExists = m_rbExists.GetState() ? true : false;
	m_fEqual = m_rbEqual.GetState() ? true : false;

return true;
}

///////////////////////////////////////////////////////////////////////////////
// übergibt dem Dialog zu bearbeitende Objekte 
static char s_cbBuffer[1024];

HRESULT CClassifyDlg :: SetEnumLONG (IEnum<LONG> *pInEnum)
{
	if (NULL == pInEnum) 	// wird brauchen eine Eingabe !
		return ResultFromScode (E_NOTIMPL);

// Objekteigenschaft besorgen
WObjectProperty IObjProp;
HRESULT hr = ResultFromScode (E_FAIL);

	{
	WEnumObjProps IEnum;

		hr = m_ObjProps -> EnumObjectProps (IEnum.ppi());
		if (FAILED(hr)) return hr;

		hr = IEnum -> FindByName (m_strObjProp.c_str(), IObjProp.ppi());
		if (FAILED(hr)) return hr;
	}	// IEnum goes out of scope

// alle übergebenen Objekte in internen Strukturen speichern
LONG lONr = 0;

	IObjProp -> Reset();		// Objekteigenschaft rücksetzen

	for (pInEnum -> Reset(); 
	     S_OK == pInEnum -> Next (1, &lONr, NULL); /**/)
	{
		hr = IObjProp -> Eval (lONr, s_cbBuffer, sizeof(s_cbBuffer), NULL);
		if (FAILED(hr)) continue;	// Fehler

	os_string str (s_cbBuffer);
	CProperties::const_iterator it = m_Props.find (str);

		if (it != m_Props.end()) {	// nicht erstes Vorkommen dieses Textes
		CDupObjects::const_iterator itr = m_DupObjs.find (str);

			if (itr == m_DupObjs.end())
				m_DupObjs.insert (*it);		// den ersten auch hier speichern
			
			m_DupObjs.insert (make_pair (str, lONr));
		} else
			m_Props.insert (make_pair (str, lONr));
	}

	IObjProp -> Reset();		// Objekteigenschaft wieder rücksetzen

// Iterator auf Anfang stellen, damit eine Abfrage an der richtigen Stelle beginnen kann
	m_PropIt = m_Props.begin();

return NOERROR;
}

// Fragt den Dialog nach seinen Daten -----------------------------------------
HRESULT CClassifyDlg :: GetNextEnumLONG (IEnum<LONG> **ppOutEnum, os_string &rstr)
{
	if (NULL == ppOutEnum) return ResultFromScode (E_POINTER);

	if (m_PropIt == m_Props.end())
		return ResultFromScode (E_UNEXPECTED);

HRESULT hr = ResultFromScode (E_FAIL);
CEnumObjectNumbers *pEnum = NULL;

	*ppOutEnum = NULL;		// für den Fall, daß nichts gefunden wird

// gibt's überhaupt mehrfache Objekteigenschaften
	if (0 == m_Props.size() || 0 == m_DupObjs.size()) {
		m_Props.erase();		// alles wieder freigeben
		m_DupObjs.erase();
		return NOERROR;
	}
		
	try {
		do {
		CDupObjects::const_iterator it = m_DupObjs.find ((*m_PropIt).first);

		// alle Objekte mit dieser ObjektEigenschaft in EnumLONG kopieren
			if (it != m_DupObjs.end()) {
			// mehrfaches Vorkommen dieses Textes
				pEnum = CEnumObjectNumbers::CreateInstance();
				if (NULL == pEnum) throw (hr = ResultFromScode(E_OUTOFMEMORY));

			// alle Objekte mit dieser Objekteigenschaft speichern
			bool fFirst = true;

				while (it != m_DupObjs.end() && (*it).first == (*m_PropIt).first) {
					if (fFirst) {
					// zugehörigen Wert speichern
						TX_ASSERT((*it).first.size() > 0);	// String muß gültig sein

						rstr = (*it).first;
						fFirst = false;
					}
					pEnum -> AddObject ((*it).second);
					++it;
				}

				hr = pEnum -> QueryInterface (IID_IEnumLONG, (LPVOID *)ppOutEnum);
				if (FAILED(hr)) throw hr;

				RELEASE(pEnum);
				++m_PropIt;		// beim nächsten weitermachen
				break;			// ok, Enum ist gefüllt
			} 

		// weitermachen, bis mehrfache ObjEigenschaften oder Ende
		} while (++m_PropIt != m_Props.end());

	} catch (...) {
		RELEASE(pEnum);
		return hr;
	}

// S_FALSE heißt hier, 'es kommen noch mehr, bitte noch mal rufen'
	if (m_PropIt == m_Props.end()) {
		m_Props.erase();		// alles wieder freigeben
		m_DupObjs.erase();
		return NOERROR;
	}
			
return ResultFromScode (S_FALSE);
}

